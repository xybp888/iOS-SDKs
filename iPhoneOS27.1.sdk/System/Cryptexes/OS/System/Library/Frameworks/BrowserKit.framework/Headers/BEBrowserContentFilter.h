// Copyright © 2026 Apple Inc. All rights reserved.

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(27.0), macos(27.0))
API_UNAVAILABLE(tvos, watchos, macCatalyst, visionos)
@interface BEBrowserContentFilter : NSObject
/**
 @abstract Evaluates whether a URL should be blocked.
 @param url The URL to be evaluated.
 @param completionHandler The completion block to be invoked with result when
 evaluation is complete. Result is YES if the url should be blocked, and NO if it isn't.
 */
- (void)evaluateURL:(NSURL *)url completionHandler:(void (^)(BOOL shouldBlock))completionHandler;
@end

NS_ASSUME_NONNULL_END
