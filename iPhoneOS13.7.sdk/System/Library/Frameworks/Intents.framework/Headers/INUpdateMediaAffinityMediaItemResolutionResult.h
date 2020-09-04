//
//  INUpdateMediaAffinityMediaItemResolutionResult.h
//  Intents
//
//  Copyright (c) 2016-2020 Apple Inc. All rights reserved.
//

#import <Intents/INMediaItemResolutionResult.h>

typedef NS_ENUM(NSInteger, INUpdateMediaAffinityMediaItemUnsupportedReason) {
    INUpdateMediaAffinityMediaItemUnsupportedReasonLoginRequired = 1,
    INUpdateMediaAffinityMediaItemUnsupportedReasonSubscriptionRequired,
    INUpdateMediaAffinityMediaItemUnsupportedReasonUnsupportedMediaType,
    INUpdateMediaAffinityMediaItemUnsupportedReasonExplicitContentSettings,
    INUpdateMediaAffinityMediaItemUnsupportedReasonCellularDataSettings,
    INUpdateMediaAffinityMediaItemUnsupportedReasonRestrictedContent,
} API_AVAILABLE(ios(13.0), watchos(6.0)) API_UNAVAILABLE(macos, tvos);

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(13.0), watchos(6.0))
API_UNAVAILABLE(macos, tvos)
@interface INUpdateMediaAffinityMediaItemResolutionResult : INMediaItemResolutionResult

+ (instancetype)unsupportedForReason:(INUpdateMediaAffinityMediaItemUnsupportedReason)reason NS_SWIFT_NAME(unsupported(forReason:));

- (instancetype)initWithMediaItemResolutionResult:(INMediaItemResolutionResult *)mediaItemResolutionResult;

@end

NS_ASSUME_NONNULL_END
