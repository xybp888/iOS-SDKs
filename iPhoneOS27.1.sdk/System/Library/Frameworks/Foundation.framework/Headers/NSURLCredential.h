/*	
    NSURLCredential.h
    Copyright (c) 2003-2019, Apple Inc. All rights reserved.    
    
    Public header file.
*/

#import <Foundation/NSObject.h>
#import <Security/Security.h>

@class NSString;
@class NSArray;

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

/// Constants defining how long a credential will be kept around.
///
/// - `NSURLCredentialPersistenceNone`: This credential won't be saved.
/// - `NSURLCredentialPersistenceForSession`: This credential will only be stored for this session.
/// - `NSURLCredentialPersistencePermanent`: This credential will be stored permanently. Note: Whereas in Mac OS X any application
///   can access any credential provided the user gives permission, in iPhone OS an application can access only its own credentials.
/// - `NSURLCredentialPersistenceSynchronizable`: This credential will be stored permanently. Additionally, this credential will be
///   distributed to other devices based on the owning AppleID.

typedef NS_ENUM(NSUInteger, NSURLCredentialPersistence) {
    /// The credential should not be stored.
    NSURLCredentialPersistenceNone,
    /// The credential should be stored only for this session.
    NSURLCredentialPersistenceForSession,
    /// The credential should be stored in the keychain.
    NSURLCredentialPersistencePermanent,
    /// The credential should be stored permanently in the keychain, and in addition should be distributed to other devices based on the owning Apple ID.
    NSURLCredentialPersistenceSynchronizable API_AVAILABLE(macos(10.8), ios(6.0), watchos(2.0), tvos(9.0))
};

@class NSURLCredentialInternal;

/// An authentication credential consisting of information specific to the type of credential and the type of persistent storage to use, if any.
///
/// The URL Loading System supports password-based user credentials, certificate-based user credentials, and certificate-based server credentials.
///
/// When you create a credential, you can specify it for a single request, persist it temporarily (until your app quits), or persist it permanently. Permanent persistence can be local persistence in the keychain, or synchronized persistence across the user's devices, based on their Apple ID.
///
/// > Note:
/// > Permanent storage of credentials is only available for password-based credentials. TLS credentials are never stored permanently by ``URLCredentialStorage``. In general, use for-session persistence for TLS credentials.
NS_SWIFT_SENDABLE
API_AVAILABLE(macos(10.2), ios(2.0), watchos(2.0), tvos(9.0))
@interface NSURLCredential : NSObject <NSSecureCoding, NSCopying>
{
    @private
    __strong NSURLCredentialInternal *_internal;
}

/// The credential's persistence setting.
@property (readonly) NSURLCredentialPersistence persistence;

@end

/// This category defines the methods available to an `NSURLCredential` created to represent an internet password credential.
///
/// These are most commonly used for resources that require a username and password combination.
@interface NSURLCredential(NSInternetPassword)

/// Creates a URL credential instance initialized with a given user name and password, using a given persistence setting.
///
/// - Parameter user: The user for the credential.
/// - Parameter password: The password for `user`.
/// - Parameter persistence: A value indicating whether the credential should be stored permanently, for the duration of the current session, or not at all.
- (instancetype)initWithUser:(NSString *)user password:(NSString *)password persistence:(NSURLCredentialPersistence)persistence;

/// Creates a new `NSURLCredential` with a user and password.
///
/// - Parameter user: The user for the credential.
/// - Parameter password: The password for `user`.
/// - Parameter persistence: A value indicating whether the credential should be stored permanently, for the duration of the current session, or not at all.
/// - Returns: The new autoreleased `NSURLCredential`.
+ (NSURLCredential *)credentialWithUser:(NSString *)user password:(NSString *)password persistence:(NSURLCredentialPersistence)persistence;

/// The credential's user name.
@property (nullable, readonly, copy) NSString *user;

/// The credential's password.
///
/// You should only access this property if you need the actual password value. If you only need to know if there is
/// a password, use `hasPassword`. Accessing this property may result in prompting the user for access.
@property (nullable, readonly, copy) NSString *password;

/// A Boolean value that indicates whether the credential has a password.
///
/// This method does not attempt to retrieve the password. If this credential's password is stored in the user's
/// keychain, the `password` property may return `nil` even if this method returns `YES` -- getting the password may
/// fail, or the user may refuse access.
@property (readonly) BOOL hasPassword;

@end

/// This category defines the methods available to an `NSURLCredential` created to represent a client certificate credential.
///
/// Client certificates are commonly stored on the user's computer in the keychain and must be presented to the server during a handshake.
@interface NSURLCredential(NSClientCertificate)

/// Creates a URL credential instance for resolving a client certificate authentication challenge.
///
/// - Parameter identity: A `SecIdentityRef` object.
/// - Parameter certArray: An array containing at least one `SecCertificateRef` objects, or `nil` if the server
///   does not need any intermediate certificates to authenticate the client.
/// - Parameter persistence: A value indicating whether the credential should be stored permanently, for the duration of the current session, or not at all.
- (instancetype)initWithIdentity:(SecIdentityRef)identity certificates:(nullable NSArray *)certArray persistence:(NSURLCredentialPersistence)persistence API_AVAILABLE(macos(10.6), ios(3.0), watchos(2.0), tvos(9.0));

/// Creates a new `NSURLCredential` with an identity and certificate array.
///
/// - Parameter identity: A `SecIdentityRef` object.
/// - Parameter certArray: An array containing at least one `SecCertificateRef` objects.
/// - Parameter persistence: A value indicating whether the credential should be stored permanently, for the duration of the current session, or not at all.
/// - Returns: The new autoreleased `NSURLCredential`.
+ (NSURLCredential *)credentialWithIdentity:(SecIdentityRef)identity certificates:(nullable NSArray *)certArray persistence:(NSURLCredentialPersistence)persistence API_AVAILABLE(macos(10.6), ios(3.0), watchos(2.0), tvos(9.0));

/// The identity of this credential if it is a client certificate credential.
///
/// This value is `nil` if the credential is not a client certificate credential.
@property (nullable, readonly) SecIdentityRef identity;

/// The intermediate certificates of the credential, if it is a client certificate credential.
///
/// The certificates are `SecCertificateRef` objects. This value is `nil` if this is not a client certificate credential.
@property (readonly, copy) NSArray *certificates API_AVAILABLE(macos(10.6), ios(3.0), watchos(2.0), tvos(9.0));

@end

@interface NSURLCredential(NSServerTrust)

/// Creates a URL credential instance for server trust authentication, initialized with an accepted trust.
///
/// - Parameter trust: The accepted trust.
- (instancetype)initWithTrust:(SecTrustRef)trust API_AVAILABLE(macos(10.6), ios(3.0), watchos(2.0), tvos(9.0));

/// Creates a URL credential instance for server trust authentication with a given accepted trust.
///
/// Before creating a server trust credential, it is the responsibility of the delegate of an ``NSURLConnection`` instance or an ``NSURLDownload`` instance to evaluate the trust. Do this by calling `SecTrustEvaluate`, passing it the trust obtained from the `serverTrust` method of the server's ``NSURLProtectionSpace`` instance. If the trust is invalid, the authentication challenge should be cancelled with the ``NSURLAuthenticationChallengeSender`` protocol's `cancelAuthenticationChallenge:` method.
///
/// - Parameter trust: The accepted trust.
/// - Returns: A new URL credential object, containing the accepted server trust.
+ (NSURLCredential *)credentialForTrust:(SecTrustRef)trust API_AVAILABLE(macos(10.6), ios(3.0), watchos(2.0), tvos(9.0));

@end

NS_HEADER_AUDIT_END(nullability, sendability)
