//
//  INRestaurantResolutionResult.h
//  Intents
//
//  Copyright © 2016 Apple. All rights reserved.
//
//  This API requires you to work with Apple Maps before your application can use it. For information on how to get started, please go to MapsConnect.
//
//  http://mapsconnect.apple.com/info/extensions

#import <Intents/INIntentResolutionResult.h>

@class INRestaurant;

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(10.0))
API_UNAVAILABLE(watchos)
@interface INRestaurantResolutionResult : INIntentResolutionResult

+ (instancetype)successWithResolvedRestaurant:(INRestaurant *)resolvedRestaurant NS_SWIFT_NAME(success(with:));

+ (instancetype)disambiguationWithRestaurantsToDisambiguate:(NSArray<INRestaurant *> *)restaurantsToDisambiguate NS_SWIFT_NAME(disambiguation(with:));

+ (instancetype)confirmationRequiredWithRestaurantToConfirm:(nullable INRestaurant *)restaurantToConfirm NS_SWIFT_NAME(confirmationRequired(with:));

@end

NS_ASSUME_NONNULL_END
