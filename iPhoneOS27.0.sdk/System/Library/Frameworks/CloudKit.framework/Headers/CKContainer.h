//
//  CKContainer.h
//  CloudKit
//
//  Copyright (c) 2014 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

#import <CloudKit/CKDatabase.h>
#import <CloudKit/CKDefines.h>
#import <CloudKit/CKOperation.h>

@class CKRecordID, CKUserIdentity, CKShareParticipant, CKShare, CKShareMetadata;

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

/// A constant that provides the current user's default name.
CK_EXTERN NSString * const CKCurrentUserDefaultName API_AVAILABLE(macos(10.12), ios(10.0), tvos(10.0), watchos(3.0));

/// A constant that provides the default owner's name.
CK_EXTERN NSString * const CKOwnerDefaultName API_DEPRECATED_WITH_REPLACEMENT("CKCurrentUserDefaultName", macos(10.10, 10.12), ios(8.0, 10.0), tvos(9.0, 10.0), watchos(3.0, 3.0));

/// A conduit to your app's databases.
///
/// A container manages all explicit and implicit attempts to access its contents.
///
/// Every app has a default container that manages its own content. If you develop a suite of apps, you can access any containers that you have the appropriate entitlements for. Each new container distinguishes between public and private data. CloudKit always stores private data in the appropriate container directory in the user's iCloud account.
///
/// - Note: `CKContainer` instances operate with a <doc://com.apple.documentation/documentation/foundation/qualityofservice/userinitiated> quality of service level by default. For information about quality of service, see [Prioritize Work with Quality of Service Classes](https://developer.apple.com/library/archive/documentation/Performance/Conceptual/EnergyGuide-iOS/PrioritizeWorkWithQoS.html#//apple_ref/doc/uid/TP40015243-CH39) in [Energy Efficiency Guide for iOS Apps](https://developer.apple.com/library/archive/documentation/Performance/Conceptual/EnergyGuide-iOS/index.html#//apple_ref/doc/uid/TP40015243) and [Prioritize Work at the Task Level](https://developer.apple.com/library/archive/documentation/Performance/Conceptual/power_efficiency_guidelines_osx/PrioritizeWorkAtTheTaskLevel.html#//apple_ref/doc/uid/TP40013929-CH35) in [Energy Efficiency Guide for Mac Apps](https://developer.apple.com/library/archive/documentation/Performance/Conceptual/power_efficiency_guidelines_osx/index.html#//apple_ref/doc/uid/TP40013929).
///
/// ### Interacting with a Container
///
/// A container coordinates all interactions between your app and the server. Most of these interactions involve the following tasks:
///
/// - Determining whether the user has an iCloud account, which lets you know if you can write data to the user's personal storage.
/// - With the user's permission, discovering other users who the current user knows, and making the current user's information discoverable.
/// - Getting the container or one of its databases to use with an operation.
///
/// ### Public and Private Databases
///
/// Each container provides a public and a private database for storing data. The contents of the public database are accessible to all users of the app, whereas the contents of the private database are, by default, visible only to the current user. Content that is specific to a single user usually belongs in that user's private database, whereas app-related content that you provide (or that users want to share) belongs in the public database.
///
/// The public database is always available, regardless of whether the device has an active iCloud account. When there isn't an iCloud account, your app can fetch records from and query the public database, but it can't save changes. Saving records to the public database requires an active iCloud account to identify the owner of those records. Access to the private database always requires an active iCloud account on the device.
///
/// - Note: The data in a public database counts toward the iCloud storage quota of the app that owns the container. That data doesn't count toward the storage quota of any single user. Data in the private database counts toward the user's iCloud storage quota.
///
/// ### Using iCloud
///
/// Whenever possible, design your app to run gracefully with or without an active iCloud account. Even without an active iCloud account, apps can fetch records from the public database and display that information to the user. If your app requires the ability to write to the public database or requires access to the private database, notify the user of the reason and encourage them to enable iCloud. You can even provide a button that takes the user directly to Settings so that they can enable iCloud. To implement such a button, have the button's action open the URL that the <doc://com.apple.documentation/documentation/uikit/uiapplication/opensettingsurlstring> constant provides.
///
/// ### User Records and Permissions
///
/// When a user accesses a container for the first time, CloudKit assigns them a unique identifier and uses it to create two user records — one in the app's public database and another in that user's private database. By default, these records don't contain any identifying personal information, but you can use the record in the user's private database to store additional, nonsensitive information about that user. Because the public database's user record is accessible to all users of your app, don't use it to store information about the user.
///
/// While a user record isn't the same as the user's ``CKUserIdentity``, the identity does provide the identifier of their user record that you can use to fetch that record from either the public database or the user's private database. For more information, see ``CKUserIdentity/userRecordID``.
///
/// ### Testing Your Code Using the Development Container
///
/// At runtime, CloudKit uses your app's `com.apple.developer.icloud-container-environment` entitlement to discover whether you're using a `Development` or `Production` version of your provisioning profile. When you configure the entitlement for development, CloudKit configures the app's containers to use the development server. The development environment is a safe place to make changes during the development process without disrupting users of your app. You can add new fields to records programmatically, and you can delete or modify fields using iCloud Dashboard.
///
/// Before shipping your app, always test your app's behavior in the production environment. The production server generates errors when your app tries to add record types or add new fields to existing record types. Testing in the production environment helps you find and fix the places in your code where you're making those types of changes. You can use CloudKit Dashboard to modify record types in the development environment, and then migrate those changes to the production environment.
///
/// - Note: Simulator works only with the development environment. When you're ready to test your app in a production environment, do so from a device.
API_AVAILABLE(macos(10.10), ios(8.0), watchos(3.0))
// This class should not be subclassed. If it is, Sendable may no longer apply.
NS_SWIFT_SENDABLE
@interface CKContainer : NSObject

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

/// Returns the app's default container.
///
/// Use this method to retrieve your app's default container. This is the one you typically use to store your app's data. If you want the container for a different app, create a container using the ``CKContainer/init(identifier:)`` method.
///
/// During development, the container uses the development environment. When you release your app, the container uses the production environment.
+ (CKContainer *)defaultContainer;

/// Creates a container for the specified identifier.
///
/// - Parameters:
///   - containerIdentifier: The bundle identifier of the app with the container that you want to access. The bundle identifier must be in the app's `com.apple.developer.icloud-container-identifiers` entitlement. This parameter must not be `nil`.
///
/// The specified identifier must correspond to one of the containers in the iCloud capabilities section of your Xcode project. Including the identifier with your app's capabilities adds the corresponding entitlements to your app. To access your app's default container, use the ``CKContainer/default()`` method instead.
+ (CKContainer *)containerWithIdentifier:(NSString *)containerIdentifier;

/// The container's unique identifier.
///
/// Use this property's value to distinguish different containers in your app.
@property (nullable, readonly, copy, nonatomic) NSString *containerIdentifier;

/// Adds an operation to the container's queue.
///
/// - Parameters:
///   - operation: The operation to add to the queue. Make sure you fully configure the operation and have it ready to execute. Don't change the operation's configuration after you queue it.
///
/// This method adds the operation to a queue that the container manages. The queue's operations execute on background threads concurrently, and with default priorities. When you add an operation to the queue, its container becomes the current container.
- (void)addOperation:(CKOperation *)operation;

@end

@interface CKContainer (Database)

/// The user's private database.
///
/// The user's private database is only available if the device has an iCloud account. Only the user can access their private database, by default. They own all of the database's content and can view and modify that content. Data in the private database isn't visible in the developer portal.
///
/// Data in the private database counts toward the user's iCloud storage quota.
///
/// If there isn't an iCloud account on the user's device, this property still returns a database, but any attempt to use it results in an error. To determine if there is an iCloud account on the device, use the ``CKContainer/accountStatus(completionHandler:)`` method.
@property (readonly, strong, nonatomic) CKDatabase *privateCloudDatabase;

/// The app's public database.
///
/// This database is available regardless of whether the user's device has an iCloud account. The contents of the public database are readable by all users of the app, and users have write access to the records, and other objects, they create. The public database's contents are visible in the developer portal, where you can assign roles to users and restrict access as necessary.
///
/// Data in the public database counts toward your app's iCloud storage quota.
@property (readonly, strong, nonatomic) CKDatabase *publicCloudDatabase;

/// The database that contains shared data.
///
/// This database is only available if the device has an iCloud account. Permissions on the database are available only to the user according to the permissions of the enclosing ``CKShare`` instance, which represents the shared record. The current user doesn't own the content in the shared database, and can view and modify that content only if the necessary permissions exist. Data in the shared database isn't visible in the developer portal or to any user who doesn't have access.
///
/// Data in the shared database counts toward your app's iCloud storage quota.
///
/// If there isn't an iCloud account on the user's device, this property still returns a database, but any attempt to use it results in an error. To determine if there is an iCloud account on the device, use the ``CKContainer/accountStatus(completionHandler:)`` method.
@property (readonly, strong, nonatomic) CKDatabase *sharedCloudDatabase API_AVAILABLE(macos(10.12), ios(10.0), tvos(10.0), watchos(3.0));

/// Returns the database with the specified scope.
///
/// - Parameters:
///   - databaseScope: The database's scope. See ``CKDatabase/Scope`` for the available options.
- (CKDatabase *)databaseWithDatabaseScope:(CKDatabaseScope)databaseScope API_AVAILABLE(macos(10.12), ios(10.0), tvos(10.0), watchos(3.0));

@end

/// Constants that indicate the availability of the user's iCloud account.
typedef NS_ENUM(NSInteger, CKAccountStatus) {
    /// CloudKit can't determine the status of the user's iCloud account.
    CKAccountStatusCouldNotDetermine                                                                      = 0,

    /// The user's iCloud account is available.
    CKAccountStatusAvailable                                                                              = 1,

    /// The system denies access to the user's iCloud account.
    ///
    /// Your app can't access the user's iCloud account due to restrictions that Parental Controls or Mobile Device Management impose.
    CKAccountStatusRestricted                                                                             = 2,

    /// The device doesn't have an iCloud account.
    CKAccountStatusNoAccount                                                                              = 3,

    /// The user's iCloud account is temporarily unavailable.
    ///
    /// You receive this account status when the user's iCloud account is available, but isn't ready to support CloudKit operations. Don't delete any cached data and don't enqueue any CloudKit operations after receipt of this account status. Instead, use the <doc://com.apple.documentation/documentation/foundation/nsnotification/name-swift.struct/ckaccountchanged> notification to listen for when the status changes to ``CKAccountStatus/available``.
    CKAccountStatusTemporarilyUnavailable API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0), watchos(8.0)) = 4
} API_AVAILABLE(macos(10.10), ios(8.0), watchos(3.0));

/// A notification that a container posts when the status of an iCloud account changes.
///
/// Create an instance of ``CKContainer`` to receive this notification. The container posts the notification using an arbitrary queue. Use the ``CKContainer/accountStatus(completionHandler:)`` method to obtain the account's status.
CK_EXTERN NSString * const CKAccountChangedNotification API_AVAILABLE(macos(10.11), ios(9.0), watchos(3.0));

@interface CKContainer (AccountStatus)

/// Determines whether the system can access the user's iCloud account.
///
/// - Parameters:
///   - completionHandler: The handler to execute when the call completes.
///
/// The closure has no return value and takes the following parameters:
///
/// - The status of the user's iCloud account.
/// - An error that describes the failure, or `nil` if the system successfully determines the status.
///
/// This method determines the status of the user's iCloud account asynchronously, passing the results to the closure that you provide. Call this method before accessing the private database to determine whether that database is available. While your app is running, use the <doc://com.apple.documentation/documentation/foundation/nsnotification/name-swift.struct/ckaccountchanged> notification to detect account changes, and call this method again to determine the status of the new account.
- (void)accountStatusWithCompletionHandler:(void (NS_SWIFT_SENDABLE ^)(CKAccountStatus accountStatus, NSError * _Nullable error))completionHandler;

@end

/// Constants that represent the permissions that a user grants.
typedef NS_OPTIONS(NSUInteger, CKApplicationPermissions) {
    /// The user is discoverable using their email address.
    CKApplicationPermissionUserDiscoverability API_DEPRECATED("No longer supported. Please see Sharing CloudKit Data with Other iCloud Users.", macos(10.0, 14.0), ios(8.0, 17.0), tvos(9.0, 17.0), watchos(3.0, 10.0)) = 1 << 0,
} API_AVAILABLE(macos(10.10), ios(8.0), watchos(3.0));

/// Constants that represent the status of a permission.
typedef NS_ENUM(NSInteger, CKApplicationPermissionStatus) {
    /// The app is yet to request the permission.
    CKApplicationPermissionStatusInitialState          = 0,

    /// An error that occurs while processing the permission request.
    CKApplicationPermissionStatusCouldNotComplete      = 1,

    /// The user denies the permission.
    CKApplicationPermissionStatusDenied                = 2,

    /// The user grants the permission.
    CKApplicationPermissionStatusGranted               = 3,
} API_DEPRECATED("No longer supported. Please see Sharing CloudKit Data with Other iCloud Users.", macos(10.10, 14.0), ios(8.0, 17.0), tvos(9.0, 17.0), watchos(3.0, 10.0));

/// A closure that processes the outcome of a permissions request.
///
/// When you request or determine the status of a permission, use this closure to process the result. The closure has no return value and takes the following parameters:
///
/// - The permission's status. For a list of possible values, see ``CKContainer/ApplicationPermissionStatus``.
/// - An error if the system can't fulfill the request, or `nil` if it successfully determines the status.
typedef void (^CKApplicationPermissionBlock)(CKApplicationPermissionStatus applicationPermissionStatus, NSError * _Nullable error) API_DEPRECATED("No longer supported. Please see Sharing CloudKit Data with Other iCloud Users.", macos(10.10, 14.0), ios(8.0, 17.0), tvos(9.0, 17.0), watchos(3.0, 10.0));

@interface CKContainer (ApplicationPermission)

/// Determines the authorization status of the specified permission.
///
/// - Parameters:
///   - applicationPermission: The permission to check. For a list of possible values, see ``CKContainer/ApplicationPermissions``.
///   - completionHandler: The handler to execute with the outcome.
///
/// Use this method to determine the extra capabilities that the user grants to your app. If your app doesn't have a specific permission, calling this method yields ``CKContainer/ApplicationPermissionStatus/initialState``. In response, call the ``CKContainer/requestApplicationPermission:completionHandler:`` method to prompt the user to provide their permission.
- (void)statusForApplicationPermission:(CKApplicationPermissions)applicationPermission completionHandler:(NS_SWIFT_SENDABLE CKApplicationPermissionBlock)completionHandler NS_SWIFT_ASYNC_NAME(applicationPermissionStatus(for:)) API_DEPRECATED("No longer supported. Please see Sharing CloudKit Data with Other iCloud Users.", macos(10.0, 14.0), ios(8.0, 17.0), tvos(9.0, 17.0), watchos(3.0, 10.0));

/// Prompts the user to authorize the specified permission.
///
/// - Parameters:
///   - applicationPermission: The permission to request. This permission applies only to the current container. For a list of possible values, see ``CKContainer/ApplicationPermissions``.
///   - completionHandler: The handler to execute with the outcome.
///
/// To implement social features in your app, it's possible to correlate a user record with the user's actual name, but your app must get permission from the user to do so. Making a user record discoverable to the contacts of that user involves calling the ``CKContainer/requestApplicationPermission:completionHandler:`` method and asking for the ``CKContainer/ApplicationPermissions/userDiscoverability`` permission. When you call that method, CloudKit asks the user whether the user record can become discoverable. If the user grants the request, that user's contacts can discover that user's true identity when running the app. To discover the contacts of the current user, you use the `discoverAllContactUserInfos(completionHandler:)` method or one of several other methods to get the related user information.
///
/// The first time you request a permission on any of the user's devices, the user receives a prompt to grant or deny the request. After the user grants or denies a permission, subsequent requests for the same permission (on the same or separate devices), don't prompt the user again.
///
/// This method runs asynchronously, and the system calls your completion handler on an arbitrary queue and provides the outcome.
- (void)requestApplicationPermission:(CKApplicationPermissions)applicationPermission completionHandler:(NS_SWIFT_SENDABLE CKApplicationPermissionBlock)completionHandler API_DEPRECATED("No longer supported. Please see Sharing CloudKit Data with Other iCloud Users.", macos(10.0, 14.0), ios(8.0, 17.0), tvos(9.0, 17.0), watchos(3.0, 10.0));

@end

@interface CKContainer (UserRecords)

/// Fetches the user record ID of the current user.
///
/// - Parameters:
///   - completionHandler: The handler to execute with the fetch results.
///
/// The closure doesn't return a value and takes the following parameters:
///   - The user record ID, or `nil` if the user disables iCloud or the device doesn't have an iCloud account.
///   - An error if a problem occurs, or `nil` if CloudKit successfully retrieves the user record ID.
///
/// CloudKit returns a ``CKError/Code/notAuthenticated`` error when any of the following conditions are met:
/// - The device has an iCloud account but the user disables iCloud.
/// - The device has an iCloud account with restricted access.
/// - The device doesn't have an iCloud account.
///
/// - Note: At startup, fetching the user record ID may take longer while CloudKit makes the initial iCloud account request. After the initial fetch, accessing the ID generally takes less time.
- (void)fetchUserRecordIDWithCompletionHandler:(void (NS_SWIFT_SENDABLE ^)(CKRecordID * _Nullable recordID, NSError * _Nullable error))completionHandler NS_SWIFT_ASYNC_NAME(userRecordID());

/// Fetches all user identities that match entries in the user's Contacts.
///
/// - Parameters:
///   - completionHandler: The handler to execute with the fetch results.
///
/// The closure doesn't return a value and takes the following parameters:
///
/// - The user identities that match entries in the user's Contacts.
/// - An error if a problem occurs, or `nil` if the system successfully completes the request.
///
/// This method searches for the users asynchronously and with a low priority. If you want the task to execute with a higher priority, create an instance of ``CKDiscoverAllUserIdentitiesOperation`` and configure it to use the necessary priority.
- (void)discoverAllIdentitiesWithCompletionHandler:(void (NS_SWIFT_SENDABLE ^)(NSArray<CKUserIdentity *> * _Nullable userIdentities, NSError * _Nullable error))completionHandler API_DEPRECATED("No longer supported. Please see Sharing CloudKit Data with Other iCloud Users.", macos(10.12, 14.0), ios(10.0, 17.0), watchos(3.0, 10.0)) API_UNAVAILABLE(tvos) NS_REFINED_FOR_SWIFT_ASYNC(1);

/// Fetches the user identity for the specified email address.
///
/// - Parameters:
///   - email: The user's email address.
///   - completionHandler: The handler to execute with the fetch results.
///
/// This closure doesn't return a value and takes the following parameters:
///
/// - The user identity for the email address, or `nil` if CloudKit can't find an identity.
/// - An error if a problem occurs, or `nil` if CloudKit successfully fetches a user identity.
///
/// Use this method to retrieve the identity of a user who the current user knows. The user you're searching for must meet the following criteria:
/// - The user has run the app.
/// - The user grants the ``CKContainer/ApplicationPermissions/userDiscoverability`` permission for the container.
///
/// This method searches for the user asynchronously and with a low priority. If you want the task to execute the request with a higher priority, create an instance of ``CKDiscoverUserIdentitiesOperation`` and configure it to use the necessary priority.
- (void)discoverUserIdentityWithEmailAddress:(NSString *)email completionHandler:(void (NS_SWIFT_SENDABLE ^)(CKUserIdentity * _Nullable_result userInfo, NSError * _Nullable error))completionHandler API_DEPRECATED("No longer supported. Please see Sharing CloudKit Data with Other iCloud Users.", macos(10.12, 14.0), ios(10.0, 17.0), tvos(10.0, 17.0), watchos(3.0, 10.0)) NS_REFINED_FOR_SWIFT_ASYNC(2);

/// Fetches the user identity for the specified phone number.
///
/// - Parameters:
///   - phoneNumber: The user's phone number.
///   - completionHandler: The handler to execute with the fetch results.
///
/// This closure doesn't return a value and takes the following parameters:
///
/// - The user identity for the phone number, or `nil` if CloudKit can't find an identity.
/// - An error if a problem occurs, or `nil` if CloudKit successfully fetches a user identity.
///
/// Use this method to retrieve the identity of a user who the current user knows. The user you're searching for must meet the following criteria:
/// - The user has run the app.
/// - The user grants the ``CKContainer/ApplicationPermissions/userDiscoverability`` permission for the container.
///
/// This method searches for the user asynchronously and with a low priority. If you want the task to execute the request with a higher priority, create an instance of ``CKDiscoverUserIdentitiesOperation`` and configure it to use the necessary priority.
- (void)discoverUserIdentityWithPhoneNumber:(NSString *)phoneNumber completionHandler:(void (NS_SWIFT_SENDABLE ^)(CKUserIdentity * _Nullable_result userInfo, NSError * _Nullable error))completionHandler API_DEPRECATED("No longer supported. Please see Sharing CloudKit Data with Other iCloud Users.", macos(10.12, 14.0), ios(10.0, 17.0), tvos(10.0, 17.0), watchos(3.0, 10.0)) NS_REFINED_FOR_SWIFT_ASYNC(2);

/// Fetches the user identity for the specified user record ID.
///
/// - Parameters:
///   - userRecordID: The user record's ID.
///   - completionHandler: The handler to execute with the fetch results.
///
/// This closure doesn't return a value and takes the following parameters:
///
/// - The user identity for the user record ID, or `nil` if CloudKit can't find an identity.
/// - An error if a problem occurs, or `nil` if CloudKit successfully fetches a user identity.
///
/// Use this method to retrieve the identity of a user who you already have a user record ID for. The user you're searching for must meet the following criteria:
/// - The user has run the app.
/// - The user grants the ``CKContainer/ApplicationPermissions/userDiscoverability`` permission for the container.
///
/// This method searches for the user asynchronously and with a low priority. If you want the task to execute the request with a higher priority, create an instance of ``CKDiscoverUserIdentitiesOperation`` and configure it to use the necessary priority.
- (void)discoverUserIdentityWithUserRecordID:(CKRecordID *)userRecordID completionHandler:(void (NS_SWIFT_SENDABLE ^)(CKUserIdentity * _Nullable_result userInfo, NSError * _Nullable error))completionHandler API_DEPRECATED("No longer supported. Please see Sharing CloudKit Data with Other iCloud Users.", macos(10.12, 14.0), ios(10.0, 17.0), tvos(10.0, 17.0), watchos(3.0, 10.0)) NS_REFINED_FOR_SWIFT_ASYNC(2);

@end

@interface CKContainer (Sharing)

/// Fetches the share participant with the specified email address.
///
/// - Parameters:
///   - emailAddress: The share participant's email address.
///   - completionHandler: The handler to execute with the fetch results.
///
/// The closure doesn't return a value and takes the following parameters:
///   - The share participant, or `nil` if CloudKit can't find the participant.
///   - An error if a problem occurs, or `nil` if CloudKit successfully retrieves the participant.
///
/// CloudKit can translate any valid email address into a share participant.  If the email address doesn't correspond to a known iCloud account, then at share-accept-time, CloudKit offers the accepting participant a vetting process. The accepting participant uses this vetting process to link the email address to an iCloud account.
///
/// This method searches for the share participant asynchronously and with a low priority. If you want the task to execute with a higher priority, create an instance of ``CKFetchShareParticipantsOperation`` and configure it to use the necessary priority.
- (void)fetchShareParticipantWithEmailAddress:(NSString *)emailAddress completionHandler:(void (NS_SWIFT_SENDABLE ^)(CKShareParticipant * _Nullable shareParticipant, NSError * _Nullable error))completionHandler API_AVAILABLE(macos(10.12), ios(10.0), tvos(10.0), watchos(3.0)) NS_REFINED_FOR_SWIFT_ASYNC(2);

/// Fetches the share participant with the specified phone number.
///
/// - Parameters:
///   - phoneNumber: The share participant's phone number.
///   - completionHandler: The handler to execute with the fetch results.
///
/// The closure doesn't return a value and takes the following parameters:
///   - The share participant, or `nil` if CloudKit can't find the participant.
///   - An error if a problem occurs, or `nil` if CloudKit successfully retrieves the participant.
///
/// CloudKit can translate any valid phone number into a share participant.  If the phone number doesn't correspond to a known iCloud account, then at share-accept-time, CloudKit offers the accepting participant a vetting process. The accepting participant uses this vetting process to link the phone number to an iCloud account.
///
/// This method searches for the share participant asynchronously and with a low priority. If you want the task to execute with a higher priority, create an instance of ``CKFetchShareParticipantsOperation`` and configure it to use the necessary priority.
- (void)fetchShareParticipantWithPhoneNumber:(NSString *)phoneNumber completionHandler:(void (NS_SWIFT_SENDABLE ^)(CKShareParticipant * _Nullable shareParticipant, NSError *_Nullable error))completionHandler API_AVAILABLE(macos(10.12), ios(10.0), tvos(10.0), watchos(3.0)) NS_REFINED_FOR_SWIFT_ASYNC(2);

/// Fetches the share participant with the specified user record ID.
///
/// - Parameters:
///   - userRecordID: The share participant's user record ID.
///   - completionHandler: The handler to execute with the fetch results.
///
/// The closure doesn't return a value and takes the following parameters:
///   - The share participant, or `nil` if CloudKit can't find the participant.
///   - An error if a problem occurs, or `nil` if CloudKit successfully retrieves the participant.
///
/// This method searches for the share participant asynchronously and with a low priority. If you want the task to execute with a higher priority, create an instance of ``CKFetchShareParticipantsOperation`` and configure it to use the necessary priority.
- (void)fetchShareParticipantWithUserRecordID:(CKRecordID *)userRecordID completionHandler:(void (NS_SWIFT_SENDABLE ^)(CKShareParticipant *_Nullable shareParticipant, NSError *_Nullable error))completionHandler API_AVAILABLE(macos(10.12), ios(10.0), tvos(10.0), watchos(3.0)) NS_REFINED_FOR_SWIFT_ASYNC(2);

/// Fetches the share metadata for the specified share URL.
///
/// - Parameters:
///   - url: The share URL that CloudKit uses to locate the metadata.
///   - completionHandler: The handler to execute with the fetch results.
///
/// The closure doesn't return a value and takes the following parameters:
///   - The share metadata, or `nil` if CloudKit can't find the metadata.
///   - An error if a problem occurs, or `nil` if CloudKit successfully retrieves the metadata.
- (void)fetchShareMetadataWithURL:(NSURL *)url completionHandler:(void (NS_SWIFT_SENDABLE ^)(CKShareMetadata *_Nullable metadata, NSError * _Nullable error))completionHandler API_AVAILABLE(macos(10.12), ios(10.0), tvos(10.0), watchos(3.0)) NS_REFINED_FOR_SWIFT_ASYNC(2);

/// Accepts the specified share metadata.
///
/// - Parameters:
///   - metadata: The metadata of the share to accept.
///   - completionHandler: The handler to execute when the process finishes.
///
/// The closure doesn't return a value and takes the following parameters:
///
/// - The corresponding share, or `nil` if CloudKit can't accept the metadata.
/// - An error if a problem occurs, or `nil` if CloudKit successfully accepts the metadata.
- (void)acceptShareMetadata:(CKShareMetadata *)metadata completionHandler:(void (NS_SWIFT_SENDABLE ^)(CKShare *_Nullable acceptedShare, NSError *_Nullable error))completionHandler API_AVAILABLE(macos(10.12), ios(10.0), tvos(10.0), watchos(3.0)) NS_REFINED_FOR_SWIFT_ASYNC(2);

@end

@interface CKContainer (CKLongLivedOperations)
/// Fetches the IDs of any long-lived operations that are running.
///
/// - Parameters:
///   - completionHandler: The block doesn't return a value and takes the following parameters:
///
///     - term `outstandingOperationsByIDs`: The IDs of all of the long-lived operations that are running.
///     - term `error`: An error if a problem occurs, or `nil` if CloudKit successfully retrieves the IDs.
///
/// A long-lived operation is one that continues to run after the user closes the app. When a long-lived operation completes, or your app or the system cancels it, it's no longer active and CloudKit doesn't include its ID in `outstandingOperationsByIDs`. An operation is complete when the system calls its completion handler.
///
/// Use the ``CKContainer/fetchLongLivedOperationWithID:completionHandler:`` method to fetch the operation for a specific ID.
- (void)fetchAllLongLivedOperationIDsWithCompletionHandler:(void (NS_SWIFT_SENDABLE ^)(NSArray<CKOperationID> * _Nullable outstandingOperationIDs, NSError * _Nullable error))completionHandler API_AVAILABLE(macos(10.12), ios(9.3), tvos(9.2), watchos(3.0)) NS_REFINED_FOR_SWIFT_ASYNC(1);

/// Fetches the long-lived operation for the specified operation ID.
///
/// - Parameters:
///   - operationID: The operation's ID.
///   - completionHandler: The block doesn't return a value and takes the following parameters:
///
///     - term `outstandingOperation`: The long-lived operation. If the operation completes, or your app or the system cancels it, this parameter is `nil`.
///     - term `error`: An error if a problem occurs, or `nil` if CloudKit successfully retrieves the operation.
///
/// A long-lived operation is one that continues to run after the user closes your app. When a long-lived operation completes, the system calls its completion block to notify you.
- (void)fetchLongLivedOperationWithID:(CKOperationID)operationID completionHandler:(void (NS_SWIFT_SENDABLE ^)(CKOperation * _Nullable_result outstandingOperation, NSError * _Nullable error))completionHandler API_AVAILABLE(macos(10.12), ios(9.3), tvos(9.2), watchos(3.0)) NS_REFINED_FOR_SWIFT_ASYNC(2);
@end

NS_HEADER_AUDIT_END(nullability, sendability)
