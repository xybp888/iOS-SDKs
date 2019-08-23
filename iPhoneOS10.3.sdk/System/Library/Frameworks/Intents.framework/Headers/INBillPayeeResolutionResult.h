//
//  INBillPayeeResolutionResult.h
//  Intents
//
//  Copyright © 2016 Apple. All rights reserved.
//

#import <Intents/INIntentResolutionResult.h>

@class INBillPayee;

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(10.3), watchos(3.2))
@interface INBillPayeeResolutionResult : INIntentResolutionResult

// This resolution result is for when the app extension wants to tell Siri to proceed, with a given bill payee. The resolvedBillPayee can be different than the original bill payee. This allows app extensions to apply business logic constraints.
// Use +notRequired to continue with a 'nil' value.
+ (instancetype)successWithResolvedBillPayee:(INBillPayee *)resolvedBillPayee NS_SWIFT_NAME(success(with:));

// This resolution result is to ask Siri to disambiguate between the provided bill payees.
+ (instancetype)disambiguationWithBillPayeesToDisambiguate:(NSArray<INBillPayee *> *)billPayeesToDisambiguate NS_SWIFT_NAME(disambiguation(with:));

// This resolution result is to ask Siri to confirm if this is the bill payee with which the user wants to continue.
+ (instancetype)confirmationRequiredWithBillPayeeToConfirm:(nullable INBillPayee *)billPayeeToConfirm NS_SWIFT_NAME(confirmationRequired(with:));

@end

NS_ASSUME_NONNULL_END
