//
//  BAAppExtensionInfo.h
//  BackgroundAssets
//
//  Copyright (c) 2022, Apple Inc.
//  All rights reserved.
//

#import <BackgroundAssets/BackgroundAssets.h>

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(macos(13.0), macCatalyst(16.0), ios(16.1)) API_UNAVAILABLE(tvos, watchos)
NS_SWIFT_SENDABLE
@interface BAAppExtensionInfo : NSObject <NSSecureCoding>

/// @brief The number of bytes remaining that can be scheduled if the total download size is restricted.
/// @discussion When a download is restricted, your extension can only schedule up to its `BAInitialDownloadAllowance`
/// defined in your app's `Info.plist`. This result tells you the number of bytes remaining that can be scheduled
/// before the application is launched. Once the application is launched, this restriction is removed.
/// @result The result is `nil` if downloads are not restricted. It returns a valid number with the remaining available download size otherwise.
@property (readonly, strong, nullable) NSNumber *restrictedDownloadSizeRemaining
NS_REFINED_FOR_SWIFT;

- (instancetype)init
NS_UNAVAILABLE;

+ (instancetype)new
NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
