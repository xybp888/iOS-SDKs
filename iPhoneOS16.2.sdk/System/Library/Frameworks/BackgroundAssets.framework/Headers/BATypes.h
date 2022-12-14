//
//  BATypes.h
//  BackgroundAssets
//
//  Copyright (c) 2022, Apple Inc.
//  All rights reserved.
//

#import <Foundation/Foundation.h>
#import <BackgroundAssets/BackgroundAssets.h>

NS_ASSUME_NONNULL_BEGIN

/// @typedef Download state
typedef NS_ENUM(NSInteger, BADownloadState) {
    BADownloadStateFailed = -1,
    BADownloadStateCreated = 0,
    BADownloadStateWaiting,
    BADownloadStateDownloading,
    BADownloadStateFinished,
};

/// @brief A downloads priority
/// @discussion A priority to which the a given download or group of downloads. This is a range from `BADownloaderPriorityMin` to `BADownloaderPriorityMax`.
/// The priority only applies to how downloads are ordered for your application. Higher priority items will be enqued for download before lower priority items regardless of order in which they are scheduled.
typedef NSInteger BADownloaderPriority NS_TYPED_EXTENSIBLE_ENUM;

/// @brief A value that represents the lowest priority for a download.
FOUNDATION_EXPORT const BADownloaderPriority BADownloaderPriorityMin
API_AVAILABLE(macos(13.0), macCatalyst(16.0), ios(16.1)) API_UNAVAILABLE(tvos, watchos);

/// @brief A value that represents average priority for a download.
FOUNDATION_EXPORT const BADownloaderPriority BADownloaderPriorityDefault
API_AVAILABLE(macos(13.0), macCatalyst(16.0), ios(16.1)) API_UNAVAILABLE(tvos, watchos);

/// @brief A value that represents the highest priority for a download.
FOUNDATION_EXPORT const BADownloaderPriority BADownloaderPriorityMax
API_AVAILABLE(macos(13.0), macCatalyst(16.0), ios(16.1)) API_UNAVAILABLE(tvos, watchos);

/// @abstract The content request type used in the BADownloaderExtension.
/// @constant BAContentRequestInstall  Content is being requested because the application was installed.
/// @constant BAContentRequestUpdate Content is being requested because the application was updated.
/// @constant BAContentRequestPeriodic Content is being requested because the system is asking for updated content for your application.
typedef NS_ENUM(NSInteger, BAContentRequest) {
    BAContentRequestInstall = 1,
    BAContentRequestUpdate,
    BAContentRequestPeriodic,
};

NS_ASSUME_NONNULL_END
