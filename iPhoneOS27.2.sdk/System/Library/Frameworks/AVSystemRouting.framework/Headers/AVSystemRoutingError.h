/*
    File:  AVSystemRoutingError.h

    Framework:  AVSystemRouting

    Copyright © 2026 Apple Inc. All rights reserved.
*/

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/// The error domain for AVSystemRouting errors.
API_AVAILABLE(ios(27.0)) API_UNAVAILABLE(tvos, watchos, macos, macCatalyst, visionos)
NS_REFINED_FOR_SWIFT
extern NSErrorDomain const AVSystemRoutingErrorDomain;

/// An error that an AVSystemRouting operation throws when it fails.
API_AVAILABLE(ios(27.0)) API_UNAVAILABLE(tvos, watchos, macos, macCatalyst, visionos)
NS_REFINED_FOR_SWIFT
typedef NS_ERROR_ENUM(AVSystemRoutingErrorDomain, AVSystemRoutingError) {
    /// A connection failure with the remote application.
    AVSystemRoutingErrorConnectionFailed = -73985,
};

NS_ASSUME_NONNULL_END
