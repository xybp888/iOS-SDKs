//
//  CKModifySubscriptionsOperation.h
//  CloudKit
//
//  Copyright (c) 2014 Apple Inc. All rights reserved.
//

#import <CloudKit/CKDatabaseOperation.h>

#import <CloudKit/CKSubscription.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

/// An operation for modifying one or more subscriptions.
///
/// After you create or change the configuration of a subscription, use this operation to save those changes to the server. You can also use this operation to permanently delete subscriptions.
///
/// If you assign a handler to the <doc://com.apple.documentation/documentation/foundation/operation/completionblock> property, the operation calls it after it executes and passes it the results. Use the handler to perform any housekeeping tasks for the operation. The handler you specify should manage any failures, whether due to an error or an explicit cancellation.
API_AVAILABLE(macos(10.10), ios(8.0), watchos(6.0))
@interface CKModifySubscriptionsOperation : CKDatabaseOperation

/// Creates an empty modify subscriptions operation.
- (instancetype)init NS_DESIGNATED_INITIALIZER;

/// Creates an operation for saving and deleting the specified subscriptions.
///
/// - Parameters:
///   - subscriptionsToSave: The subscriptions to save or update. You can specify `nil` for this parameter.
///   - subscriptionIDsToDelete: The IDs of the subscriptions to delete. You can specify `nil` for this parameter.
///
/// The subscriptions that you want to save or delete must reside in the same container. CloudKit creates a subscription if you save one that doesn't already exist. CloudKit returns an error if you try to delete a subscription that doesn't exist.
- (instancetype)initWithSubscriptionsToSave:(nullable NSArray<CKSubscription *> *)subscriptionsToSave subscriptionIDsToDelete:(nullable NSArray<CKSubscriptionID> *)subscriptionIDsToDelete;

/// The subscriptions to save to the database.
///
/// This property contains the subscriptions that you want to save. Its initial value is the array that you pass to the ``CKModifySubscriptionsOperation/init(subscriptionsToSave:subscriptionIDsToDelete:)`` method. Modify this property as necessary before you execute the operation or submit it to a queue. After CloudKit saves the subscriptions, it begins generating push notifications according to their criteria.
@property (nullable, copy, nonatomic) NSArray<CKSubscription *> *subscriptionsToSave;

/// The IDs of the subscriptions that you want to delete.
///
/// This property contains the IDs of the subscriptions that you want to delete. Its initial value is the array that you pass to the ``CKModifySubscriptionsOperation/init(subscriptionsToSave:subscriptionIDsToDelete:)`` method. Modify this property as necessary before you execute the operation or submit it to a queue.
@property (nullable, copy, nonatomic) NSArray<CKSubscriptionID> *subscriptionIDsToDelete;

/// The closure to execute when CloudKit saves a subscription.
///
/// This property is a closure that returns no value and has the following parameters:
///
/// - The ID of the subscription that CloudKit saves.
/// - The subscription that CloudKit saves, or `nil` if CloudKit can't save the subscription.
/// - If CloudKit can't save the subscription, an error that provides information about the failure; otherwise, `nil`.
///
/// The closure executes once for each subscription in the ``CKModifySubscriptionsOperation/subscriptionsToSave`` property. Each time the closure executes, it executes serially with respect to the other subscription completion blocks of the operation.
///
/// If you intend to use this closure to process results, set it before you execute the operation or submit the operation to a queue.
@property (nullable, copy, nonatomic) void (^perSubscriptionSaveBlock)(CKSubscriptionID subscriptionID, CKSubscription * _Nullable subscription, NSError * _Nullable error) API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0), watchos(8.0)) NS_REFINED_FOR_SWIFT;

/// The closure to execute when CloudKit deletes a subscription.
///
/// This property is a closure that returns no value and has the following parameters:
///
/// - The ID of the subscription that CloudKit deletes.
/// - If CloudKit can't delete the subscription, an error that provides information about the failure; otherwise, `nil`.
///
/// The closure executes once for each subscription in the ``CKModifySubscriptionsOperation/subscriptionIDsToDelete-14x82`` property. Each time the closure executes, it executes serially with respect to the other subscription completion blocks of the operation.
///
/// If you intend to use this closure to process results, set it before you execute the operation or submit the operation to a queue.
@property (nullable, copy, nonatomic) void (^perSubscriptionDeleteBlock)(CKSubscriptionID subscriptionID, NSError * _Nullable error) API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0), watchos(8.0)) NS_REFINED_FOR_SWIFT;

/// The block to execute after the operation modifies the subscriptions.
///
/// The block returns no value and takes the following parameters:
///
///   - term `savedSubscriptions`: The subscriptions to save.
///   - term `deletedSubscriptionIDs`: The IDs of the subscriptions to delete.
///   - term `operationError`: An error that contains information about a problem, or `nil` if CloudKit successfully modifies the subscriptions.
///
/// The operation executes this block only once, and it's your only opportunity to process the results. The block executes on a background queue, so any tasks that require access to the main queue must dispatch accordingly.
///
/// The block reports an error of type ``CKError/Code/partialFailure`` when it can't modify some of the subscriptions. The <doc://com.apple.documentation/documentation/foundation/nserror/userinfo> dictionary of the error contains a ``CKPartialErrorsByItemIDKey`` key that has a dictionary as its value. The keys of the dictionary are the IDs of the subscriptions that CloudKit can't modify, and the corresponding values are errors that contain information about the failures.
///
/// Set this property's value before you execute the operation or submit it to a queue.
@property (nullable, copy, nonatomic) void (^modifySubscriptionsCompletionBlock)(NSArray<CKSubscription *> * _Nullable savedSubscriptions, NSArray<CKSubscriptionID> * _Nullable deletedSubscriptionIDs, NSError * _Nullable operationError);

@end

NS_HEADER_AUDIT_END(nullability, sendability)
