//
//  INAddMediaMediaDestinationResolutionResult.h
//  Intents
//
//  Copyright (c) 2016-2020 Apple Inc. All rights reserved.
//

#import <Intents/INMediaDestinationResolutionResult.h>

typedef NS_ENUM(NSInteger, INAddMediaMediaDestinationUnsupportedReason) {
    INAddMediaMediaDestinationUnsupportedReasonPlaylistNameNotFound = 1,
} API_AVAILABLE(ios(13.0), watchos(6.0)) API_UNAVAILABLE(macos, tvos);

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(13.0), watchos(6.0))
API_UNAVAILABLE(macos, tvos)
@interface INAddMediaMediaDestinationResolutionResult : INMediaDestinationResolutionResult

+ (instancetype)unsupportedForReason:(INAddMediaMediaDestinationUnsupportedReason)reason NS_SWIFT_NAME(unsupported(forReason:));

- (instancetype)initWithMediaDestinationResolutionResult:(INMediaDestinationResolutionResult *)mediaDestinationResolutionResult;

@end

NS_ASSUME_NONNULL_END
