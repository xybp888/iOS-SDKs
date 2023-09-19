//
//  SKReceiptRefreshRequest.h
//  StoreKit
//
//  Copyright (c) 2013 Apple, Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <StoreKit/SKRequest.h>
#import <StoreKit/StoreKitDefines.h>

NS_ASSUME_NONNULL_BEGIN

SK_EXTERN_CLASS API_AVAILABLE(ios(7.0), macos(10.9), watchos(6.2), visionos(1.0)) NS_SWIFT_NONSENDABLE @interface SKReceiptRefreshRequest : SKRequest {
@private
    NSDictionary *_properties;
}

- (instancetype)initWithReceiptProperties:(nullable NSDictionary<NSString *, id> *)properties API_AVAILABLE(ios(7.0), macos(10.9), watchos(6.2), visionos(1.0));
@property (nonatomic, readonly, nullable) NSDictionary<NSString *, id> *receiptProperties API_AVAILABLE(ios(7.0), macos(10.9), watchos(6.2), visionos(1.0));

@end

SK_EXTERN void SKTerminateForInvalidReceipt(void) API_AVAILABLE(ios(7.1), macos(10.14), watchos(6.2), visionos(1.0));

// Receipt properties for sandbox testing:
SK_EXTERN NSString * const SKReceiptPropertyIsExpired API_AVAILABLE(ios(7.0), macos(10.9), watchos(6.2), visionos(1.0));  // NSNumber BOOL, defaults to NO
SK_EXTERN NSString * const SKReceiptPropertyIsRevoked API_AVAILABLE(ios(7.0), macos(10.9), watchos(6.2), visionos(1.0));  // NSNumber BOOL, defaults to NO
SK_EXTERN NSString * const SKReceiptPropertyIsVolumePurchase API_AVAILABLE(ios(7.0), macos(10.9), watchos(6.2), visionos(1.0));  // NSNumber BOOL, defaults to NO

NS_ASSUME_NONNULL_END
