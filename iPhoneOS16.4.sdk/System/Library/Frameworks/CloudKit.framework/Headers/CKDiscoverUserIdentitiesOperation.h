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

API_AVAILABLE(macos(10.12), ios(10.0), tvos(10.0), watchos(3.0))
@interface CKDiscoverUserIdentitiesOperation : CKOperation

- (instancetype)init NS_DESIGNATED_INITIALIZER;
- (instancetype)initWithUserIdentityLookupInfos:(NSArray<CKUserIdentityLookupInfo *> *)userIdentityLookupInfos;

@property (nonatomic, copy) NSArray<CKUserIdentityLookupInfo *> *userIdentityLookupInfos;

/*! @abstract Called once for each user identity lookup info that was successfully discovered on the server
 *
 *  @discussion Each @c CKOperation instance has a private serial queue. This queue is used for all callback block invocations.
 *  This block may share mutable state with other blocks assigned to this operation, but any such mutable state
 *  should not be concurrently used outside of blocks assigned to this operation.
 */
@property (nonatomic, copy, nullable) void (^userIdentityDiscoveredBlock)(CKUserIdentity *identity, CKUserIdentityLookupInfo * lookupInfo);

/*! @abstract This block is called when the operation completes.
 *
 *  @discussion The @code -[NSOperation completionBlock] @endcode will also be called if both are set.
 *  Each @c CKOperation instance has a private serial queue. This queue is used for all callback block invocations.
 *  This block may share mutable state with other blocks assigned to this operation, but any such mutable state
 *  should not be concurrently used outside of blocks assigned to this operation.
 */
@property (nonatomic, copy, nullable) void (^discoverUserIdentitiesCompletionBlock)(NSError * _Nullable operationError)
CK_SWIFT_DEPRECATED("Use discoverUserIdentitiesResultBlock instead", macos(10.12, 12.0), ios(10.0, 15.0), tvos(10.0, 15.0), watchos(3.0, 8.0));

@end

NS_HEADER_AUDIT_END(nullability, sendability)
