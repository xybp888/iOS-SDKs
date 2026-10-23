//
//  CKDiscoverUserIdentitiesOperation.h
//  CloudKit
//
//  Copyright (c) 2016 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

#import <CloudKit/CKOperation.h>

@class CKRecordID, CKUserIdentity, CKUserIdentityLookupInfo;

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

/// An operation that uses the provided criteria to search for discoverable iCloud users.
///
/// Use this operation to discover one or more iCloud users that match identity information you provide, such as email addresses and phone numbers.
///
/// Before CloudKit can return a user's identity, you must ask for their permission by calling ``CKContainer/requestApplicationPermission:completionHandler:``. Do this as part of any onboarding where you can highlight the benefits of being discoverable within the context of your app.
///
/// The operation executes the handlers you provide on an internal queue it manages. You must provide handlers capable of executing on a background queue. Tasks that need access to the main queue must redirect as appropriate.
///
/// The operation calls ``discoverUserIdentitiesCompletionBlock`` after it executes and returns results. Use the completion handler to perform housekeeping tasks for the operation. It should also manage any failures, whether due to an error or an explicit cancellation.
///
/// - Note: Because this class inherits from <doc://com.apple.documentation/documentation/foundation/operation>, you can also set the <doc://com.apple.documentation/documentation/foundation/operation/completionblock> property. The operation calls both completion handlers if they're both set.
///
/// CloudKit operations have a default QoS of <doc://com.apple.documentation/documentation/foundation/qualityofservice/default>. Operations with this service level are discretionary. The system schedules their execution at an optimal time according to battery level and network conditions, among other factors. Use the <doc://com.apple.documentation/documentation/foundation/operation/qualityofservice> property to set a more appropriate QoS for the operation.
///
/// The following example shows how to create the operation, configure its callbacks, and execute it using the default container's queue:
///
/// ```swift
/// func fetchUserIdentities(withEmails emails: [String],
///     completion: @escaping (Result<[CKUserIdentity], any Error>) -> Void) {
///
///     var identities = [CKUserIdentity]()
///
///     // Convert the email addresses into instances of
///     // CKUserIdentity.LookupInfo, which CloudKit uses
///     // to discover identities.
///     let lookupInfos =
///         CKUserIdentity.LookupInfo.lookupInfos(withEmails: emails)
///
///     // Create the operation using the array of lookup objects.
///     let operation = CKDiscoverUserIdentitiesOperation(
///         userIdentityLookupInfos: lookupInfos)
///
///     // Cache the user identities as CloudKit discovers them.
///     operation.userIdentityDiscoveredBlock = { userIdentity, _ in
///         identities.append(userIdentity)
///     }
///
///     // If the operation fails, return the error to the caller.
///     // Otherwise, return the array of discovered user identities.
///     operation.discoverUserIdentitiesCompletionBlock = { error in
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
API_DEPRECATED("No longer supported. Please see Sharing CloudKit Data with Other iCloud Users.", macos(10.12, 14.0), ios(10.0, 17.0), tvos(10.0, 17.0), watchos(3.0, 10.0))
@interface CKDiscoverUserIdentitiesOperation : CKOperation

/// Creates an operation for discovering user identities.
///
/// You can use the operation only once. Create a new operation for each subsequent search.
- (instancetype)init NS_DESIGNATED_INITIALIZER;

/// Creates an operation for discovering the user identities of the specified lookup infos.
///
/// - Parameters:
///   - userIdentityLookupInfos: An array that contains instances of ``CKUserIdentity/LookupInfo``. CloudKit uses this parameter as the default value for the ``CKDiscoverUserIdentitiesOperation/userIdentityLookupInfos`` property. If you specify `nil`, you must assign a value to that property before you execute the operation.
///
/// After you create the operation, assign a handler to ``CKDiscoverUserIdentitiesOperation/discoverUserIdentitiesCompletionBlock`` so that you can process the search results.
- (instancetype)initWithUserIdentityLookupInfos:(NSArray<CKUserIdentityLookupInfo *> *)userIdentityLookupInfos;

/// The lookup info for discovering user identities.
///
/// Use this property to view or change the lookup info that CloudKit uses to discover user identities. If you intend to modify this property's value, do so before you execute the operation or submit it to a queue.
@property (copy, nonatomic) NSArray<CKUserIdentityLookupInfo *> *userIdentityLookupInfos;

/// The closure to execute for each user identity.
///
/// The closure doesn't return a value and takes the following parameters:
///
/// - The user identity.
/// - The lookup info that corresponds to the user identity.
///
/// The operation executes this closure one or more times for each user identity it discovers. Each time the closure executes, it executes serially with respect to the other closures of the operation.
///
/// If you intend to use this closure to process results, set it before you execute the operation or add the operation to a queue.
@property (nullable, copy, nonatomic) void (^userIdentityDiscoveredBlock)(CKUserIdentity *identity, CKUserIdentityLookupInfo * lookupInfo);

/// The closure to execute when the operation finishes.
///
/// The closure doesn't return a value and takes the following parameter:
///
/// - An error if a problem occurs, or `nil` if CloudKit successfully fetches the user identities.
///
/// This closure executes only once, after all of the individual discovery closures finish. The closure executes serially with respect to the operation's other closures. If you intend to use this closure to process results, update the property's value before you execute the operation or submit it to a queue.
@property (nullable, copy, nonatomic) void (^discoverUserIdentitiesCompletionBlock)(NSError * _Nullable operationError)
CK_SWIFT_DEPRECATED("Use discoverUserIdentitiesResultBlock instead", macos(10.12, 12.0), ios(10.0, 15.0), tvos(10.0, 15.0), watchos(3.0, 8.0));

@end

NS_HEADER_AUDIT_END(nullability, sendability)
