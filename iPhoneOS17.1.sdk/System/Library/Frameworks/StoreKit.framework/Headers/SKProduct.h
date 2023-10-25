//
//  SKProduct.h
//  StoreKit
//
//  Copyright 2009 Apple, Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <StoreKit/StoreKitDefines.h>

@class SKProductDiscount;

typedef NS_ENUM(NSUInteger, SKProductPeriodUnit) {
    SKProductPeriodUnitDay,
    SKProductPeriodUnitWeek,
    SKProductPeriodUnitMonth,
    SKProductPeriodUnitYear
} NS_SWIFT_NAME(SKProduct.PeriodUnit) API_AVAILABLE(ios(11.2), macos(10.13.2), watchos(6.2), visionos(1.0));

NS_ASSUME_NONNULL_BEGIN

SK_EXTERN_CLASS API_AVAILABLE(ios(11.2), macos(10.13.2), watchos(6.2), visionos(1.0)) NS_SWIFT_SENDABLE @interface SKProductSubscriptionPeriod : NSObject {
@private
    id _internal;
}

@property(nonatomic, readonly) NSUInteger numberOfUnits API_AVAILABLE(ios(11.2), macos(10.13.2), watchos(6.2), visionos(1.0));

@property(nonatomic, readonly) SKProductPeriodUnit unit API_AVAILABLE(ios(11.2), macos(10.13.2), watchos(6.2), visionos(1.0));

@end

SK_EXTERN_CLASS API_AVAILABLE(ios(3.0), macos(10.7), watchos(6.2), visionos(1.0)) NS_SWIFT_SENDABLE @interface SKProduct : NSObject {
@private
    id _internal;
}

@property(nonatomic, readonly) NSString *localizedDescription API_AVAILABLE(ios(3.0), macos(10.7), watchos(6.2), visionos(1.0));

@property(nonatomic, readonly) NSString *localizedTitle API_AVAILABLE(ios(3.0), macos(10.7), watchos(6.2), visionos(1.0));

@property(nonatomic, readonly) NSDecimalNumber *price API_AVAILABLE(ios(3.0), macos(10.7), watchos(6.2), visionos(1.0));

@property(nonatomic, readonly) NSLocale *priceLocale API_AVAILABLE(ios(3.0), macos(10.7), watchos(6.2), visionos(1.0));

@property(nonatomic, readonly) NSString *productIdentifier API_AVAILABLE(ios(3.0), macos(10.7), watchos(6.2), visionos(1.0));

// YES if this product has content downloadable using SKDownload
@property(nonatomic, readonly) BOOL isDownloadable API_AVAILABLE(ios(6.0), macos(10.15), watchos(6.2), visionos(1.0));
@property(nonatomic, readonly) BOOL downloadable API_DEPRECATED_WITH_REPLACEMENT("-[SKProduct isDownloadable]", macos(10.8, 10.15)) API_UNAVAILABLE(ios, watchos, visionos);

// YES if this product allows for sharing among family members
@property(nonatomic, readonly) BOOL isFamilyShareable API_AVAILABLE(ios(14.0), macos(11.0), watchos(7.0), visionos(1.0));

// Sizes in bytes (NSNumber [long long]) of the downloads available for this product
@property(nonatomic, readonly) NSArray<NSNumber *> *contentLengths API_DEPRECATED_WITH_REPLACEMENT("-[SKProduct downloadContentLengths]", macos(10.8, 10.14)) API_UNAVAILABLE(ios, tvos, watchos, visionos);
@property(nonatomic, readonly) NSArray<NSNumber *> *downloadContentLengths API_AVAILABLE(ios(6.0), macos(10.14), watchos(6.2), visionos(1.0));

// Version of the downloadable content
@property(nonatomic, readonly) NSString *contentVersion API_DEPRECATED_WITH_REPLACEMENT("-[SKProduct downloadContentVersion]", macos(10.8, 10.14)) API_UNAVAILABLE(visionos);
@property(nonatomic, readonly) NSString *downloadContentVersion API_AVAILABLE(ios(6.0), macos(10.14), watchos(6.2), visionos(1.0));

@property(nonatomic, readonly, nullable) SKProductSubscriptionPeriod *subscriptionPeriod API_AVAILABLE(ios(11.2), macos(10.13.2), watchos(6.2), visionos(1.0));

@property(nonatomic, readonly, nullable) SKProductDiscount *introductoryPrice API_AVAILABLE(ios(11.2), macos(10.13.2), watchos(6.2), visionos(1.0));

@property(nonatomic, readonly, nullable) NSString *subscriptionGroupIdentifier API_AVAILABLE(ios(12.0), macos(10.14), watchos(6.2), visionos(1.0));

@property(nonatomic, readonly) NSArray<SKProductDiscount *> *discounts API_AVAILABLE(ios(12.2), macos(10.14.4), watchos(6.2), visionos(1.0));

@end

NS_ASSUME_NONNULL_END
