//
//  CKDiscoverAllUserIdentitiesOperation.h
//  CloudKit
//
//  Copyright (c) 2016 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

#import <CloudKit/CKOperation.h>

@class CKUserIdentity;

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

/// An operation that uses the device's contacts to search for discoverable iCloud users.
///
/// Use this operation to discover iCloud users that match entries in the device's Contacts database. CloudKit uses the email addresses and phone numbers in each Contact record to search for a matching iCloud account.
///
/// Although your app doesn't need authorization to use the Contacts database to execute this operation, if it has authorization, you can use the ``CKUserIdentity/contactIdentifiers`` property on any returned user identity to fetch the corresponding Contact record from the database.
///
/// - Note: This operation scales linearly with the number of email addresses and phone numbers in the device's Contacts database, and may take some time to complete.
///
/// Before CloudKit can return a user's identity, you must ask for their permission by calling ``CKContainer/requestApplicationPermission:completionHandler:``. Do this as part of any onboarding where you can highlight the benefits of being discoverable within the context of your app.
///
/// The operation executes the handlers you provide on an internal queue it manages. You must provide handlers capable of executing on a background queue. Tasks that need access to the main queue must redirect as appropriate.
///
/// The operation calls ``discoverAllUserIdentitiesCompletionBlock`` after it executes and returns results. Use the completion handler to perform housekeeping tasks for the operation. It should also manage any failures, whether due to an error or an explicit cancellation.
///
/// - Note: Because this class inherits from <doc://com.apple.documentation/documentation/foundation/operation>, you can also set the <doc://com.apple.documentation/documentation/foundation/operation/completionblock> property. The operation calls both completion handlers if they're both set.
///
/// CloudKit operations have a default QoS of <doc://com.apple.documentation/documentation/foundation/qualityofservice/default>. Operations with this service level are discretionary. The system schedules their execution at an optimal time according to battery level and network conditions, among other factors. Use the <doc://com.apple.documentation/documentation/foundation/operation/qualityofservice> property to set a more appropriate QoS for the operation.
///
/// The following example shows how to create the operation, configure its callbacks, and execute it using the default container's queue:
///
/// ```swift
/// func fetchUserIdentities(
///     completion: @escaping (Result<[CKUserIdentity], any Error>) -> Void) {
///
///     var identities = [CKUserIdentity]()
///
///     // Create an operation to discover all the iCloud users
///     // in the user's Contacts database that use the app, and
///     // opt in to being discoverable.
///     let operation = CKDiscoverAllUserIdentitiesOperation()
///
///     // Cache the user identities as CloudKit discovers them.
///     operation.userIdentityDiscoveredBlock = { userIdentity in
///         identities.append(userIdentity)
///     }
///
///     // If the operation fails, return the error to the caller.
///     // Otherwise, return the array of discovered user identities.
///     operation.discoverAllUserIdentitiesCompletionBlock = { error in
///         if let error = error {
///             completion(.failure(error))
///         } else {
///             completion(.success(identities))
///         }
///     }
///
///     // Set an appropriate QoS and add the operation to the
///     // default container's queue to execute it.
///     operation.qualityOfService = .userInitiated
///     CKContainer.default().add(operation)
/// }
/// ```
API_DEPRECATED("No longer supported. Please see Sharing CloudKit Data with Other iCloud Users.", macos(10.12, 14.0), ios(10.0, 17.0), watchos(3.0, 10.0))
API_UNAVAILABLE(tvos)
@interface CKDiscoverAllUserIdentitiesOperation : CKOperation

/// Creates an operation for searching the device's contacts.
///
/// You can use the operation only once. Create a new operation for each subsequent search.
- (instancetype)init NS_DESIGNATED_INITIALIZER;

/// The closure to execute for each user identity.
///
/// The closure doesn't return a value and takes the following parameter:
///
/// - The user identity that matches an entry in the device's Contacts.
///
/// The operation executes this closure one or more times for each user identity it discovers. Each time the closure executes, it executes serially with respect to the other closures of the operation.
///
/// If you intend to use this closure to process results, set it before you execute the operation or add the operation to a queue.
@property (nullable, copy, nonatomic) void (^userIdentityDiscoveredBlock)(CKUserIdentity *identity);

/// The closure to execute when the operation finishes.
///
/// The closure doesn't return a value and takes the following parameter:
///
/// - An error if a problem occurs, or `nil` if CloudKit successfully fetches the user identities.
///
/// This closure executes only once, after all of the individual discovery closures finish. The closure executes serially with respect to the operation's other closures. If you intend to use this closure to process results, update the property's value before you execute the operation or submit it to a queue.
@property (nullable, copy, nonatomic) void (^discoverAllUserIdentitiesCompletionBlock)(NSError * _Nullable operationError)
CK_SWIFT_DEPRECATED("Use discoverAllUserIdentitiesResultBlock instead", macos(10.12, 12.0), ios(10.0, 15.0), watchos(3.0, 8.0));

@end

NS_HEADER_AUDIT_END(nullability, sendability)
