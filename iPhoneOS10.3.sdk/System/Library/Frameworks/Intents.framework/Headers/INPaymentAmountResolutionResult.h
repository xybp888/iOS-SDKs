//
//  INPaymentAmountResolutionResult.h
//  Intents
//
//  Copyright © 2016 Apple. All rights reserved.
//

#import <Intents/INIntentResolutionResult.h>

@class INPaymentAmount;

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(10.3), watchos(3.2))
@interface INPaymentAmountResolutionResult : INIntentResolutionResult

// This resolution result is for when the app extension wants to tell Siri to proceed, with a given payment amount. The resolvedPaymentAmount can be different than the original payment amount. This allows app extensions to apply business logic constraints.
// Use +notRequired to continue with a 'nil' value.
+ (instancetype)successWithResolvedPaymentAmount:(INPaymentAmount *)resolvedPaymentAmount NS_SWIFT_NAME(success(with:));

// This resolution result is to ask Siri to disambiguate between the provided payment amounts.
+ (instancetype)disambiguationWithPaymentAmountsToDisambiguate:(NSArray<INPaymentAmount *> *)paymentAmountsToDisambiguate NS_SWIFT_NAME(disambiguation(with:));

// This resolution result is to ask Siri to confirm if this is the payment amount with which the user wants to continue.
+ (instancetype)confirmationRequiredWithPaymentAmountToConfirm:(nullable INPaymentAmount *)paymentAmountToConfirm NS_SWIFT_NAME(confirmationRequired(with:));

@end

NS_ASSUME_NONNULL_END
