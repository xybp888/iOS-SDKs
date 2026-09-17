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

/// A type that indicates the purpose of a content download request.
typedef NS_ENUM(NSInteger, BAContentRequest) {
    /// A content request resulting from the installation of the app.
    BAContentRequestInstall = 1,
    /// A content request resulting from an update of the app.
    BAContentRequestUpdate,
    /// A content request resulting from a system request for updated content within the app.
    BAContentRequestPeriodic,
    /// A content request resulting from someone changing the app's preferred language.
    BAContentRequestLanguageChange API_AVAILABLE(ios(27), macos(27), tvos(27), visionos(27))
} API_AVAILABLE(ios(16.1), macos(13), tvos(18.4), visionos(2.4)) API_UNAVAILABLE(watchos);

NS_ASSUME_NONNULL_END
