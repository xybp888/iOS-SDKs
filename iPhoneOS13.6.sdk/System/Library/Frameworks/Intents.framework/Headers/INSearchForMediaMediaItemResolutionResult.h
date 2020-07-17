//
//  INSearchForMediaMediaItemResolutionResult.h
//  Intents
//
//  Copyright (c) 2016-2020 Apple Inc. All rights reserved.
//

#import <Intents/INMediaItemResolutionResult.h>

typedef NS_ENUM(NSInteger, INSearchForMediaMediaItemUnsupportedReason) {
    INSearchForMediaMediaItemUnsupportedReasonLoginRequired = 1,
    INSearchForMediaMediaItemUnsupportedReasonSubscriptionRequired,
    INSearchForMediaMediaItemUnsupportedReasonUnsupportedMediaType,
    INSearchForMediaMediaItemUnsupportedReasonExplicitContentSettings,
    INSearchForMediaMediaItemUnsupportedReasonCellularDataSettings,
    INSearchForMediaMediaItemUnsupportedReasonRestrictedContent,
} API_AVAILABLE(ios(13.0), watchos(6.0)) API_UNAVAILABLE(macos, tvos);

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(13.0), watchos(6.0))
API_UNAVAILABLE(macos, tvos)
@interface INSearchForMediaMediaItemResolutionResult : INMediaItemResolutionResult

+ (instancetype)unsupportedForReason:(INSearchForMediaMediaItemUnsupportedReason)reason NS_SWIFT_NAME(unsupported(forReason:));

- (instancetype)initWithMediaItemResolutionResult:(INMediaItemResolutionResult *)mediaItemResolutionResult;

@end

NS_ASSUME_NONNULL_END
