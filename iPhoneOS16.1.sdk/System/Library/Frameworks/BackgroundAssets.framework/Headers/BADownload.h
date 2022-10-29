//
//  BADownload.h
//  BackgroundAssets
//
//  Copyright (c) 2022, Apple Inc.
//  All rights reserved.
//

#import <BackgroundAssets/BackgroundAssets.h>

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(macos(13.0), macCatalyst(16.0), ios(16.1)) API_UNAVAILABLE(tvos, watchos)
@interface BADownload : NSObject<NSCoding, NSSecureCoding, NSCopying>

/// @brief The current state of the respresented download.
@property (readonly, nonatomic) BADownloadState state
API_AVAILABLE(macos(13.0), macCatalyst(16.0), ios(16.1)) API_UNAVAILABLE(tvos, watchos);

/// @brief A client defined identifier that uniquely identifies this asset.
@property (readonly, nonatomic) NSString    *identifier
API_AVAILABLE(macos(13.0), macCatalyst(16.0), ios(16.1)) API_UNAVAILABLE(tvos, watchos);

/// @brief A UUID that uniquely identifies the download object.
@property (readonly, nonatomic) NSString  *uniqueIdentifier
API_AVAILABLE(macos(13.0), macCatalyst(16.0), ios(16.1)) API_UNAVAILABLE(tvos, watchos);

/// @brief A client set priority to try to order downloads in order of importance
@property (readonly) BADownloaderPriority priority
API_AVAILABLE(macos(13.0), macCatalyst(16.0), ios(16.1)) API_UNAVAILABLE(tvos, watchos);

- (instancetype)init
NS_UNAVAILABLE;

+ (instancetype)new
NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
