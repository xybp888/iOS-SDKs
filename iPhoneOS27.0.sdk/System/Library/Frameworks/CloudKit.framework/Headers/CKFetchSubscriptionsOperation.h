//
//  CKFetchSubscriptionsOperation.h
//  CloudKit
//
//  Copyright (c) 2014 Apple Inc. All rights reserved.
//

#import <CloudKit/CKDatabaseOperation.h>

#import <CloudKit/CKDefines.h>
#import <CloudKit/CKSubscription.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

/// An operation for fetching subscriptions.
///
/// A fetch subscriptions operation retrieves subscriptions (with IDs you already know) from iCloud and can fetch all subscriptions for the current user.
///
/// You might fetch subscriptions so you can examine or modify their parameters — for example, to adjust the delivery options for push notifications that the subscription generates.
///
/// If you assign a handler to the <doc://com.apple.documentation/documentation/foundation/operation/completionblock> property, the operation calls it after it executes and passes it the results. Use the handler to perform any housekeeping tasks for the operation. The handler you specify should manage any failures, whether due to an error or an explicit cancellation.
API_AVAILABLE(macos(10.10), ios(8.0), watchos(6.0))
@interface CKFetchSubscriptionsOperation : CKDatabaseOperation

/// Returns an operation that fetches all of the user's subscriptions.
///
/// After creating the operation, set the ``CKFetchSubscriptionsOperation/fetchSubscriptionCompletionBlock-207ep`` property to process the results.
+ (instancetype)fetchAllSubscriptionsOperation;

/// Creates an empty fetch subscriptions operation.
///
/// You must set the ``CKFetchSubscriptionsOperation/subscriptionIDs-714ct`` property before you execute the operation.
- (instancetype)init NS_DESIGNATED_INITIALIZER;

/// Creates an operation for fetching the specified subscriptions.
///
/// - Parameters:
///   - subscriptionIDs: An array of strings where each one is an ID of a subscription that you want to retrieve. This parameter sets the ``CKFetchSubscriptionsOperation/subscriptionIDs-714ct`` property's value. If you specify `nil`, you must set the `subscriptionIDs` property before you execute the operation.
///
/// After creating the operation, assign a block to the ``CKFetchSubscriptionsOperation/fetchSubscriptionCompletionBlock-207ep`` property to process the results.
- (instancetype)initWithSubscriptionIDs:(NSArray<CKSubscriptionID> *)subscriptionIDs;

/// The IDs of the subscriptions to fetch.
///
/// Use this property to view or change the IDs of the subscriptions to fetch. Each element of the array is a string that represents the ID of a subscription. If you intend to modify this property's value, do so before you execute the operation or submit it to a queue.
///
/// If you use the ``CKFetchSubscriptionsOperation/fetchAllSubscriptionsOperation()`` method to create the operation, CloudKit ignores this property's value and sets it to `nil`.
@property (nullable, copy, nonatomic) NSArray<CKSubscriptionID> *subscriptionIDs;

/// The closure to execute as the operation fetches individual subscriptions.
///
/// The closure returns no value and takes the following parameters:
///
/// - The ID of the subscription.
/// - The subscription, or `nil` if CloudKit can't fetch the subscription.
/// - If CloudKit can't fetch the subscription, this parameter provides information about the failure; otherwise, it's `nil`.
///
/// The operation executes this closure once for each subscription ID in the ``CKFetchSubscriptionsOperation/subscriptionIDs-714ct`` property. Each time the closure executes, it executes serially with respect to the other closures of the operation.
///
/// If you intend to use this closure to process results, set it before you execute the operation or submit the operation to a queue.
@property (nullable, copy, nonatomic) void (^perSubscriptionCompletionBlock)(CKSubscriptionID subscriptionID, CKSubscription * _Nullable subscription, NSError * _Nullable error) API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0), watchos(8.0)) NS_REFINED_FOR_SWIFT;

/// The block to execute after the operation fetches the subscriptions.
///
/// The block returns no value and takes the following parameters:
///
/// - term `subscriptionsBySubscriptionID`: A dictionary with keys that are the IDs of the subscriptions you request, and values that are the corresponding subscriptions.
/// - term `operationError`: An error that contains information about a problem, or `nil` if the system successfully fetches the subscriptions.
///
/// The operation executes this block only once, and it's your only opportunity to process the results. The block executes on a background queue, so any tasks that require access to the main queue must dispatch accordingly.
///
/// The block reports an error of type ``CKError/Code/partialFailure`` when it retrieves only some of the subscriptions successfully. The <doc://com.apple.documentation/documentation/foundation/nserror/userinfo> dictionary of the error contains a ``CKPartialErrorsByItemIDKey`` key that has a dictionary as its value. The keys of the dictionary are the IDs of the subscriptions that the operation can't fetch, and the corresponding values are errors that contain information about the failures.
///
/// Set this property's value before you execute the operation or submit it to a queue.
@property (nullable, copy, nonatomic) void (^fetchSubscriptionCompletionBlock)(NSDictionary<CKSubscriptionID, CKSubscription *> * _Nullable subscriptionsBySubscriptionID, NSError * _Nullable operationError)
CK_SWIFT_DEPRECATED("Use fetchSubscriptionsResultBlock instead", macos(10.10, 12.0), ios(8.0, 15.0), tvos(9.0, 15.0), watchos(6.0, 8.0));

@end

NS_HEADER_AUDIT_END(nullability, sendability)
