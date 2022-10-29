//
//  CKSystemSharingUIObserver.h
//  CloudKit
//
//  Copyright © 2022 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

#import <CloudKit/CKDefines.h>

@class CKContainer, CKShare, CKRecordID;

NS_ASSUME_NONNULL_BEGIN

CK_EXTERN
API_AVAILABLE(macos(13.0), ios(16.0))
API_UNAVAILABLE(watchos, tvos)
@interface CKSystemSharingUIObserver : NSObject

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

- (instancetype)initWithContainer:(CKContainer *)container NS_DESIGNATED_INITIALIZER;

/*! @abstract Called on success or failure of a @c CKShare save after user modifications via the system sharing UI
 *
 *  @discussion Following a successful share save by the system sharing UI in the provided @c CKContainer, this callback will be invoked with a nonnull @c recordID, a nonnull @c share, and a nil @c error.
 *  Following a save failure due to a per-item error (@c CKErrorServerRecordChanged, for example), this callback will be invoked with a nonnull @c recordID, a nil @c share, and a nonnull @c error
 *  Each @c CKSystemSharingUIObserver instance has a private serial queue. This queue is used for all callback block invocations.
 */
@property (atomic, copy, nullable) void (^systemSharingUIDidSaveShareBlock)(CKRecordID *recordID, CKShare * _Nullable share, NSError * _Nullable error) NS_REFINED_FOR_SWIFT;

/*! @abstract Called on success or failure of a @c CKShare delete when the user decides to stop sharing via the system sharing UI
 *
 *  @discussion Each @c CKSystemSharingUIObserver instance has a private serial queue. This queue is used for all callback block invocations.
 */
@property (atomic, copy, nullable) void (^systemSharingUIDidStopSharingBlock)(CKRecordID *recordID, NSError * _Nullable error) NS_REFINED_FOR_SWIFT;

@end

NS_ASSUME_NONNULL_END
