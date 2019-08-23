//
//  CXCallController.h
//  CallKit
//
//  Copyright © 2015 Apple. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CallKit/CXBase.h>

NS_ASSUME_NONNULL_BEGIN

@class CXCallObserver;
@class CXTransaction;

CX_CLASS_AVAILABLE(ios(10.0))
@interface CXCallController : NSObject

/// Initialize call controller with a private, serial queue.
- (instancetype)init;

/// Initialize call controller with specified queue, which is used for calling completion blocks.
- (instancetype)initWithQueue:(dispatch_queue_t)queue NS_DESIGNATED_INITIALIZER;

@property (nonatomic, readonly, strong) CXCallObserver *callObserver;

/// Request a transaction to be performed by the in-app provider.
///
/// If the completion block is called with a nil error, then the transaction will be passed back via the executeTransaction delegate callback.
/// A non-nil error indicates that the requested transaction could not be executed.
///
/// Completion block is performed on the queue supplied to designated initializer.
- (void)requestTransaction:(CXTransaction *)transaction completion:(void (^)(NSError *_Nullable error))completion;

@end

NS_ASSUME_NONNULL_END
