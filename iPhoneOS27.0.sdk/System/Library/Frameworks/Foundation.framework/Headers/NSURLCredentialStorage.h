/*	
    NSURLCredentialStorage.h
    Copyright (c) 2003-2019, Apple Inc. All rights reserved.    
    
    Public header file.
*/

#import <Foundation/NSObject.h>
#import <Foundation/NSURLProtectionSpace.h>
#import <Foundation/NSNotification.h>

@class NSDictionary<KeyType, ObjectType>;
@class NSString;
@class NSURLCredential;
@class NSURLSessionTask;

@class NSURLCredentialStorageInternal;

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

/// The manager of a shared credentials cache.
///
/// The shared cache stores and retrieves instances of ``URLCredential``. You can store password-based credentials permanently, based on the ``URLCredential/Persistence`` they were created with. Certificate-based credentials are never stored permanently.
///
/// ### Subclassing notes
///
/// The ``URLCredentialStorage`` class is meant to be used as-is, but you can subclass it if you have specific needs, such as screening which credentials are stored.
///
/// When overriding methods of this class, be aware that methods that take a `task` parameter are preferred to equivalent methods that do not. Therefore, you should override the task-based methods when subclassing, as follows:
///
/// - Setting credentials — Override ``set(_:for:task:)`` instead of or in addition to ``set(_:for:)``.
/// - Getting credentials — Override ``getCredentials(for:task:completionHandler:)`` instead of or in addition to ``credentials(for:)``.
/// - Removing credentials — Override ``remove(_:for:options:task:)`` instead of or in addition to ``remove(_:for:options:)`` and ``remove(_:for:)``.
/// - Setting default credentials — Override ``setDefaultCredential(_:for:task:)`` instead of or in addition to ``setDefaultCredential(_:for:)``.
/// - Getting default credentials — Override ``getDefaultCredential(for:task:completionHandler:)`` instead of or in addition to ``defaultCredential(for:)``.
NS_SWIFT_SENDABLE
API_AVAILABLE(macos(10.2), ios(2.0), watchos(2.0), tvos(9.0))
@interface NSURLCredentialStorage : NSObject
{
    @private
    NSURLCredentialStorageInternal *_internal;
}

/// The shared singleton authentication storage.
@property (class, readonly, strong) NSURLCredentialStorage *sharedCredentialStorage;

/// Gets a dictionary mapping usernames to credentials for the specified protection space.
///
/// - Parameter space: An `NSURLProtectionSpace` indicating the protection space for which to get credentials.
/// - Returns: A dictionary where the keys are usernames and the values are the corresponding `NSURLCredential` instances.
- (nullable NSDictionary<NSString *, NSURLCredential *> *)credentialsForProtectionSpace:(NSURLProtectionSpace *)space;

/// The credentials for all available protection spaces.
///
/// The dictionary has keys corresponding to `NSURLProtectionSpace` instances. The values are dictionaries where the
/// keys are user name strings, and each value is the corresponding `NSURLCredential` instance.
@property (readonly, copy) NSDictionary<NSURLProtectionSpace *, NSDictionary<NSString *, NSURLCredential *> *> *allCredentials;

/// Adds a new credential to the set for the specified protection space or replaces an existing one.
///
/// - Parameter credential: The credential to set.
/// - Parameter space: The protection space for which to add it.
///
/// Multiple credentials may be set for a given protection space, but each must have a distinct user. If a credential
/// with the same user is already set for the protection space, the new one will replace it.
- (void)setCredential:(NSURLCredential *)credential forProtectionSpace:(NSURLProtectionSpace *)space;

/// Removes the credential from the set for the specified protection space.
///
/// - Parameter credential: The credential to remove.
/// - Parameter space: The protection space for which a credential should be removed.
///
/// The credential is removed from both persistent and temporary storage. A credential that has a persistence
/// policy of `NSURLCredentialPersistenceSynchronizable` will fail. See `removeCredential:forProtectionSpace:options:`.
- (void)removeCredential:(NSURLCredential *)credential forProtectionSpace:(NSURLProtectionSpace *)space;

/// Removes the credential from the set for the specified protection space based on options.
///
/// - Parameter credential: The credential to remove.
/// - Parameter space: The protection space for which a credential should be removed.
/// - Parameter options: A dictionary containing options to consider when removing the credential. This should be used
///   when trying to delete a credential that has the `NSURLCredentialPersistenceSynchronizable` policy. When such
///   credentials are removed, the credential will be removed on all devices that contain this credential.
///
/// The credential is removed from both persistent and temporary storage.
- (void)removeCredential:(NSURLCredential *)credential forProtectionSpace:(NSURLProtectionSpace *)space options:(nullable NSDictionary<NSString *, id> *)options API_AVAILABLE(macos(10.9), ios(7.0), watchos(2.0), tvos(9.0));

/// Gets the default credential for the specified protection space.
///
/// - Parameter space: The protection space for which to get the default credential.
- (nullable NSURLCredential *)defaultCredentialForProtectionSpace:(NSURLProtectionSpace *)space;

/// Sets the default credential for the specified protection space.
///
/// - Parameter credential: The credential to set as default.
/// - Parameter space: The protection space for which the credential should be set as default.
///
/// If the credential is not yet in the set for the protection space, it will be added to it.
- (void)setDefaultCredential:(NSURLCredential *)credential forProtectionSpace:(NSURLProtectionSpace *)space;

@end

@interface NSURLCredentialStorage (NSURLSessionTaskAdditions)
/// Fetches credentials for the specified protection space and task, passing them to the completion handler.
- (void)getCredentialsForProtectionSpace:(NSURLProtectionSpace *)protectionSpace task:(NSURLSessionTask *)task completionHandler:(void (NS_SWIFT_SENDABLE ^) (NSDictionary<NSString *, NSURLCredential *> * _Nullable credentials))completionHandler API_AVAILABLE(macos(10.10), ios(8.0), watchos(2.0), tvos(9.0)) NS_SWIFT_ASYNC_NAME(credentials(for:task:));
/// Sets a credential for the specified protection space and task.
- (void)setCredential:(NSURLCredential *)credential forProtectionSpace:(NSURLProtectionSpace *)protectionSpace task:(NSURLSessionTask *)task API_AVAILABLE(macos(10.10), ios(8.0), watchos(2.0), tvos(9.0));
/// Removes a credential for the specified protection space, options, and task.
- (void)removeCredential:(NSURLCredential *)credential forProtectionSpace:(NSURLProtectionSpace *)protectionSpace options:(nullable NSDictionary<NSString *, id> *)options task:(NSURLSessionTask *)task API_AVAILABLE(macos(10.10), ios(8.0), watchos(2.0), tvos(9.0));
/// Fetches the default credential for the specified protection space and task, passing it to the completion handler.
- (void)getDefaultCredentialForProtectionSpace:(NSURLProtectionSpace *)space task:(NSURLSessionTask *)task completionHandler:(void (NS_SWIFT_SENDABLE ^) (NSURLCredential * _Nullable credential))completionHandler API_AVAILABLE(macos(10.10), ios(8.0), watchos(2.0), tvos(9.0));
/// Sets the default credential for the specified protection space and task.
- (void)setDefaultCredential:(NSURLCredential *)credential forProtectionSpace:(NSURLProtectionSpace *)protectionSpace task:(NSURLSessionTask *)task API_AVAILABLE(macos(10.10), ios(8.0), watchos(2.0), tvos(9.0));
@end

/// This notification is sent on the main thread whenever the set of stored credentials changes.
FOUNDATION_EXPORT NSNotificationName const NSURLCredentialStorageChangedNotification API_DEPRECATED("Notification is never posted", macos(10.2, 10.14), ios(2.0, 12.0), watchos(2.0, 5.0), tvos(9.0, 12.0));

/// The corresponding value is an `NSNumber` object representing a Boolean value that indicates whether credentials which contain the ``URLCredential/Persistence/synchronizable`` attribute should be removed.
///
/// If the key is missing or the value is `@NO`, then no attempt will be made to remove such a credential.
FOUNDATION_EXPORT NSString *const NSURLCredentialStorageRemoveSynchronizableCredentials API_AVAILABLE(macos(10.9), ios(7.0), watchos(2.0), tvos(9.0));

NS_HEADER_AUDIT_END(nullability, sendability)
