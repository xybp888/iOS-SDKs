//
//  CKModifyBadgeOperation.h
//  CloudKit
//
//  Copyright (c) 2014 Apple Inc. All rights reserved.
//

#import <CloudKit/CKOperation.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

API_DEPRECATED("No longer supported, will cease working at some point in the future", macos(10.10, 10.13), ios(8.0, 11.0), tvos(9.0, 11.0), watchos(3.0, 4.0))
@interface CKModifyBadgeOperation : CKOperation

- (instancetype)init NS_DESIGNATED_INITIALIZER;
- (instancetype)initWithBadgeValue:(NSUInteger)badgeValue;

@property (assign, nonatomic) NSUInteger badgeValue;

/*! @abstract This block is called when the operation completes.
 *
 *  @discussion The @code -[NSOperation completionBlock] @endcode will also be called if both are set.
 *  Each @c CKOperation instance has a private serial queue. This queue is used for all callback block invocations.
 *  This block may share mutable state with other blocks assigned to this operation, but any such mutable state
 *  should not be concurrently used outside of blocks assigned to this operation.
 */
@property (nullable, copy, nonatomic) void (^modifyBadgeCompletionBlock)(NSError * _Nullable operationError);

@end

NS_HEADER_AUDIT_END(nullability, sendability)
