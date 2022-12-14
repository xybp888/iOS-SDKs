//
//  BAURLDownload.h
//  BackgroundAssets
//
//  Copyright (c) 2022, Apple Inc.
//  All rights reserved.
//

#import <BackgroundAssets/BackgroundAssets.h>

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(macos(13.0), macCatalyst(16.0), ios(16.1)) API_UNAVAILABLE(tvos, watchos)
@interface BAURLDownload : BADownload

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;


/// @brief Inits a download object to represent the download of a asset at a url represented in @c request
/// @discussion Inits a download object to represent a download of a asset at a url wrapped in @c request. This URL most be of the scheme https.
/// The download object then holds onto the state and callbacks for managing the states of download while the service handles.
/// @param request The request to use to start the download.
/// @param applicationGroupIdentifier The identifier of the application group that should used to store the finished download.
- (instancetype)initWithIdentifier:(NSString * )identifier
                           request:(NSURLRequest *)request
        applicationGroupIdentifier:(NSString *)applicationGroupIdentifier
API_AVAILABLE(macos(13.0), macCatalyst(16.0), ios(16.1)) API_UNAVAILABLE(tvos, watchos);

/// @brief Inits a download object to represent the download of a asset at a url represented in @c request
/// @discussion Inits a download object to represent a download of a asset at a url wrapped in @c request. This URL most be of the scheme https.
/// The download object then holds onto the state and callbacks for managing the states of download while the service handles.
/// @param request The request to use to start the download.
/// @param applicationGroupIdentifier The identifier of the application group that should used to store the finished download.
/// @param priority A unsigned integer priority between BADownloaderPriorityMin - BADownloaderPriorityMax which is used to order the downloads for this process.
- (instancetype)initWithIdentifier:(NSString * )identifier
                           request:(NSURLRequest *)request
        applicationGroupIdentifier:(NSString *)applicationGroupIdentifier
                          priority:(BADownloaderPriority)priority
NS_DESIGNATED_INITIALIZER
API_AVAILABLE(macos(13.0), macCatalyst(16.0), ios(16.1)) API_UNAVAILABLE(tvos, watchos);

@end

NS_ASSUME_NONNULL_END
