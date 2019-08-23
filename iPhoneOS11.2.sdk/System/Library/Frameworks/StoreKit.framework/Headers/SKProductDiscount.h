//
//  SKProductDiscount.h
//  StoreKit
//
//  Copyright © 2017 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <StoreKit/StoreKitDefines.h>

@class SKProductSubscriptionPeriod;

typedef NS_ENUM(NSUInteger, SKProductDiscountPaymentMode) {
    SKProductDiscountPaymentModePayAsYouGo,
    SKProductDiscountPaymentModePayUpFront,
    SKProductDiscountPaymentModeFreeTrial
} NS_SWIFT_NAME(SKProductDiscount.PaymentMode);

NS_ASSUME_NONNULL_BEGIN

SK_EXTERN_CLASS_AVAILABLE(11_2) @interface SKProductDiscount : NSObject

@property(nonatomic, readonly) NSDecimalNumber *price NS_AVAILABLE_IOS(11_2);

@property(nonatomic, readonly) NSLocale *priceLocale NS_AVAILABLE_IOS(11_2);

@property(nonatomic, readonly) SKProductSubscriptionPeriod *subscriptionPeriod NS_AVAILABLE_IOS(11_2);

@property(nonatomic, readonly) NSUInteger numberOfPeriods NS_AVAILABLE_IOS(11_2);

@property(nonatomic, readonly) SKProductDiscountPaymentMode paymentMode NS_AVAILABLE_IOS(11_2);

@end

NS_ASSUME_NONNULL_END
