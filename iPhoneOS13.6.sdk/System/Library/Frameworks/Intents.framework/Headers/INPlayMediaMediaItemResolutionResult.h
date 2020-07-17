//
//  INPlayMediaMediaItemResolutionResult.h
//  Intents
//
//  Copyright (c) 2016-2020 Apple Inc. All rights reserved.
//

#import <Intents/INMediaItemResolutionResult.h>

typedef NS_ENUM(NSInteger, INPlayMediaMediaItemUnsupportedReason) {
    INPlayMediaMediaItemUnsupportedReasonLoginRequired = 1,
    INPlayMediaMediaItemUnsupportedReasonSubscriptionRequired,
    INPlayMediaMediaItemUnsupportedReasonUnsupportedMediaType,
    INPlayMediaMediaItemUnsupportedReasonExplicitContentSettings,
    INPlayMediaMediaItemUnsupportedReasonCellularDataSettings,
    INPlayMediaMediaItemUnsupportedReasonRestrictedContent,
} API_AVAILABLE(ios(13.0), watchos(6.0)) API_UNAVAILABLE(macos, tvos);

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(13.0), watchos(6.0))
API_UNAVAILABLE(macos, tvos)
@interface INPlayMediaMediaItemResolutionResult : INMediaItemResolutionResult

+ (instancetype)unsupportedForReason:(INPlayMediaMediaItemUnsupportedReason)reason NS_SWIFT_NAME(unsupported(forReason:));

- (instancetype)initWithMediaItemResolutionResult:(INMediaItemResolutionResult *)mediaItemResolutionResult;

@end

NS_ASSUME_NONNULL_END
