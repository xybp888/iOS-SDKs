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

/*! @class CKDiscoverAllUserIdentitiesOperation
 *
 *  @abstract Finds all discoverable users in the device's contacts database. No Contacts access dialog will be displayed.
 *
 *  @discussion This operation scales linearly with the number of email addresses and phone numbers in the device's address book.  It may take some time to complete.
 */
API_AVAILABLE(macos(10.12), ios(10.0), watchos(3.0))
API_UNAVAILABLE(tvos)
@interface CKDiscoverAllUserIdentitiesOperation : CKOperation

- (instancetype)init NS_DESIGNATED_INITIALIZER;

/*! @abstract Called once for each successfully-discovered user identity from the device's address book.
 *
 *  @discussion Each @c CKOperation instance has a private serial queue. This queue is used for all callback block invocations.
 *  This block may share mutable state with other blocks assigned to this operation, but any such mutable state
 *  should not be concurrently used outside of blocks assigned to this operation.
 */
@property (nonatomic, copy, nullable) void (^userIdentityDiscoveredBlock)(CKUserIdentity *identity);

/*! @abstract This block is called when the operation completes.
 *
 *  @discussion The @code -[NSOperation completionBlock] @endcode will also be called if both are set.
 *  Each @c CKOperation instance has a private serial queue. This queue is used for all callback block invocations.
 *  This block may share mutable state with other blocks assigned to this operation, but any such mutable state
 *  should not be concurrently used outside of blocks assigned to this operation.
 */
@property (nonatomic, copy, nullable) void (^discoverAllUserIdentitiesCompletionBlock)(NSError * _Nullable operationError)
CK_SWIFT_DEPRECATED("Use discoverAllUserIdentitiesResultBlock instead", macos(10.12, 12.0), ios(10.0, 15.0), watchos(3.0, 8.0));

@end

NS_HEADER_AUDIT_END(nullability, sendability)
