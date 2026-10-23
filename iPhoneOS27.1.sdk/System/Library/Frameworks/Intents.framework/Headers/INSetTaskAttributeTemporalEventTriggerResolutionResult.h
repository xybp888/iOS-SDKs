//
//  INSetTaskAttributeTemporalEventTriggerResolutionResult.h
//  Intents
//
//  Copyright (c) 2016-2025 Apple Inc. All rights reserved.
//

#import <Intents/INTemporalEventTriggerResolutionResult.h>

typedef NS_ENUM(NSInteger, INSetTaskAttributeTemporalEventTriggerUnsupportedReason) {
    INSetTaskAttributeTemporalEventTriggerUnsupportedReasonTimeInPast = 1,
    INSetTaskAttributeTemporalEventTriggerUnsupportedReasonInvalidRecurrence,
} API_DEPRECATED("", ios(13.0, 27.0), watchos(6.0, 27.0)) API_UNAVAILABLE(macos, tvos);

NS_ASSUME_NONNULL_BEGIN

API_DEPRECATED("", ios(13.0, 27.0), watchos(6.0, 27.0))
API_UNAVAILABLE(macos, tvos)
@interface INSetTaskAttributeTemporalEventTriggerResolutionResult : INTemporalEventTriggerResolutionResult

+ (instancetype)unsupportedForReason:(INSetTaskAttributeTemporalEventTriggerUnsupportedReason)reason NS_SWIFT_NAME(unsupported(forReason:));

- (instancetype)initWithTemporalEventTriggerResolutionResult:(INTemporalEventTriggerResolutionResult *)temporalEventTriggerResolutionResult;

@end

NS_ASSUME_NONNULL_END
