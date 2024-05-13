// Copyright © 2023 Apple Inc. All rights reserved.

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/// A helper class to provide static utility methods for quick access to settings related to credential providers.
API_AVAILABLE(ios(17.0), macos(14.0)) API_UNAVAILABLE(tvos, watchos)
@interface ASSettingsHelper : NSObject

/// Calling this method will open the Settings app and navigate directly to the AutoFill provider settings.
+ (void)openCredentialProviderAppSettingsWithCompletionHandler:(nullable void (^)(NSError * _Nullable error))completionHandler NS_SWIFT_ASYNC_NAME(openCredentialProviderAppSettings());

/// Calling this method will open the Settings app and navigate directly to the Verification Code provider settings.
+ (void)openVerificationCodeAppSettingsWithCompletionHandler:(nullable void (^)(NSError * _Nullable error))completionHandler NS_SWIFT_ASYNC_NAME(openVerificationCodeAppSettings());

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
