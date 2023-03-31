//
//  CKMarkNotificationsReadOperation.h
//  CloudKit
//
//  Copyright (c) 2014 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

#import <CloudKit/CKOperation.h>

@class CKNotificationID;

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

API_DEPRECATED("Instead of iterating notifications, consider using CKDatabaseSubscription, CKFetchDatabaseChangesOperation, and CKFetchRecordZoneChangesOperation as appropriate", macos(10.10, 10.13), ios(8.0, 11.0), tvos(9.0, 11.0), watchos(3.0, 4.0))
@interface CKMarkNotificationsReadOperation : CKOperation

- (instancetype)init NS_DESIGNATED_INITIALIZER;
- (instancetype)initWithNotificationIDsToMarkRead:(NSArray<CKNotificationID *> *)notificationIDs;

@property (nonatomic, copy, nullable) NSArray<CKNotificationID *> *notificationIDs;

/*! @abstract This block is called when the operation completes.
 *
 *  @discussion The @code -[NSOperation completionBlock] @endcode will also be called if both are set.
 *  Each @c CKOperation instance has a private serial queue. This queue is used for all callback block invocations.
 *  This block may share mutable state with other blocks assigned to this operation, but any such mutable state
 *  should not be concurrently used outside of blocks assigned to this operation.
 */
@property (nonatomic, copy, nullable) void (^markNotificationsReadCompletionBlock)(NSArray<CKNotificationID *> * _Nullable notificationIDsMarkedRead, NSError * _Nullable operationError);

@end

NS_HEADER_AUDIT_END(nullability, sendability)
