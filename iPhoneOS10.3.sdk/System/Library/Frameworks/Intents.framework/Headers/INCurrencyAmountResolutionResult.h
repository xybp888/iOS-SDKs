//
//  INCurrencyAmountResolutionResult.h
//  Intents
//
//  Copyright © 2016 Apple. All rights reserved.
//

#import <Intents/INIntentResolutionResult.h>

@class INCurrencyAmount;

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(10.0), watchos(3.2)) API_UNAVAILABLE(macosx)
@interface INCurrencyAmountResolutionResult : INIntentResolutionResult

// This resolution result is for when the app extension wants to tell Siri to proceed, with a given INCurrencyAmount. The resolvedCurrencyAmount can be different than the original INCurrencyAmount. This allows app extension to apply business logic constraints. For example, the extension could round the amount to the nearest dollar.
// Use +notRequired to continue with a 'nil' value.
+ (instancetype)successWithResolvedCurrencyAmount:(INCurrencyAmount *)resolvedCurrencyAmount NS_SWIFT_NAME(success(with:));

// This resolution result is to ask Siri to disambiguate between the provided currency amounts.
+ (instancetype)disambiguationWithCurrencyAmountsToDisambiguate:(NSArray<INCurrencyAmount *> *)currencyAmountsToDisambiguate NS_SWIFT_NAME(disambiguation(with:));

// This resolution result is to ask Siri to confirm if this is the currency amount with which the user wants to continue.
+ (instancetype)confirmationRequiredWithCurrencyAmountToConfirm:(nullable INCurrencyAmount *)currencyAmountToConfirm NS_SWIFT_NAME(confirmationRequired(with:));

@end

NS_ASSUME_NONNULL_END
