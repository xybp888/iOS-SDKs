#if (defined(USE_ARKIT_PUBLIC_HEADERS) && USE_ARKIT_PUBLIC_HEADERS) || !__has_include(<ARKitCore/ARVideoFormat.h>)
//
//  ARVideoFormat.h
//  ARKit
//
//  Copyright © 2016-2021 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreGraphics/CoreGraphics.h>
#import <AVFoundation/AVCaptureDevice.h>

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(11.3))
NS_SWIFT_NAME(ARConfiguration.VideoFormat)
@interface ARVideoFormat : NSObject <NSCopying>

/**
 Indicates the physical position of an AVCaptureDevice's hardware on the system.
 */
@property (nonatomic, readonly) AVCaptureDevicePosition captureDevicePosition
API_AVAILABLE(ios(13.0));

/**
 Indicates the type of AVCaptureDevice.
 */
@property (nonatomic, readonly) AVCaptureDeviceType captureDeviceType
API_AVAILABLE(ios(14.5));

/**
 Image resolution.
 */
@property (nonatomic, readonly) CGSize imageResolution;

/**
 Frame rate.
 */
@property (nonatomic, readonly) NSInteger framesPerSecond;

/**
 Indicates if the video format is recommended for capturing high resolution frames.
 */
@property (nonatomic, readonly) BOOL isRecommendedForHighResolutionFrameCapturing API_AVAILABLE(ios(16.0));

/**
 Indicates if the video format supports high dynamic range (HDR) streaming.
 */
@property (nonatomic, readonly, getter=isVideoHDRSupported) BOOL videoHDRSupported API_AVAILABLE(ios(16.0));

/** Unavailable */
- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
#else
#import <ARKitCore/ARVideoFormat.h> 
#endif // #if (defined(USE_ARKIT_PUBLIC_HEADERS) \&\& USE_ARKIT_PUBLIC_HEADERS) || !__has_include(<ARKitCore/ARVideoFormat.h>)