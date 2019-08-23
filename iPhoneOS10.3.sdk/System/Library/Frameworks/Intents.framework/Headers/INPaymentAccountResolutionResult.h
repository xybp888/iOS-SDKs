//
//  INPaymentAccountResolutionResult.h
//  Intents
//
//  Copyright © 2016 Apple. All rights reserved.
//

#import <Intents/INIntentResolutionResult.h>

@class INPaymentAccount;

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(10.3), watchos(3.2))
@interface INPaymentAccountResolutionResult : INIntentResolutionResult

// This resolution result is for when the app extension wants to tell Siri to proceed, with a given payment account. The resolvedPaymentAccount can be different than the original payment account. This allows app extensions to apply business logic constraints.
// Use +notRequired to continue with a 'nil' value.
+ (instancetype)successWithResolvedPaymentAccount:(INPaymentAccount *)resolvedPaymentAccount NS_SWIFT_NAME(success(with:));

// This resolution result is to ask Siri to disambiguate between the provided payment accounts.
+ (instancetype)disambiguationWithPaymentAccountsToDisambiguate:(NSArray<INPaymentAccount *> *)paymentAccountsToDisambiguate NS_SWIFT_NAME(disambiguation(with:));

// This resolution result is to ask Siri to confirm if this is the payment account with which the user wants to continue.
+ (instancetype)confirmationRequiredWithPaymentAccountToConfirm:(nullable INPaymentAccount *)paymentAccountToConfirm NS_SWIFT_NAME(confirmationRequired(with:));

@end

NS_ASSUME_NONNULL_END
