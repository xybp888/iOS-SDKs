#if (defined(USE_ARKIT_PUBLIC_HEADERS) && USE_ARKIT_PUBLIC_HEADERS) || !__has_include(<ARKitCore/ARVideoFormat.h>)
//
//  ARVideoFormat.h
//  ARKit
//
//  Copyright © 2016-2021 Apple Inc. All rights reserved.
//

#import <AVFoundation/AVCaptureDevice.h>
#import <CoreGraphics/CoreGraphics.h>
#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

API_UNAVAILABLE_BEGIN(visionos)

@class AVCapturePhotoSettings;

/**
 A video size and frame rate specification for use with an AR session.

 This class is immutable; to set the frame rate and video resolution for an AR session, set your configuration's ``ARConfiguration/videoFormat``
 property to one of the formats in the ``ARConfiguration/supportedVideoFormats`` array.
 */
API_AVAILABLE(ios(11.3))
NS_SWIFT_NAME(ARConfiguration.VideoFormat)
@interface ARVideoFormat : NSObject <NSCopying>

/**
 The position of the capture device.
 */
@property (nonatomic, readonly) AVCaptureDevicePosition captureDevicePosition API_AVAILABLE(ios(13.0));

/**
 The camera that supplies the video format.

 To specify a particular video format, select from your configuration's ``ARConfiguration/supportedVideoFormats`` and set the desired format to the
 configuration's ``ARConfiguration/videoFormat`` property.

 For example, to specify the ultra-wide camera in a face-tracking session, search the supported video formats for the
 <doc://com.apple.documentation/documentation/avfoundation/avcapturedevice/devicetype-swift.struct/builtinultrawidecamera> capture device.

 ```swift
 let config = ARFaceTrackingConfiguration()
 for videoFormat in ARFaceTrackingConfiguration.supportedVideoFormats {
     if videoFormat.captureDeviceType == .builtInUltraWideCamera {
         config.videoFormat = videoFormat
         break
     }
 }
 session.run(config)
 ```

 > Important:
 > AR frames only contain depth data (``ARFrame/capturedDepthData``) in face-tracking sessions that use the TrueDepth camera.
 */
@property (nonatomic, readonly) AVCaptureDeviceType captureDeviceType API_AVAILABLE(ios(14.5));

/**
 The size, in pixels, of video images captured in the session.

 Video format sizes are relative to the native sensor orientation of the device camera, and as such are always landscape-oriented.
 */
@property (nonatomic, readonly) CGSize imageResolution;

/**
 The rate at which the session captures video and provides AR frame information.
 */
@property (nonatomic, readonly) NSInteger framesPerSecond;

/**
 Determines whether the framework considers a format suitable for high-resolution frame capture.
 */
@property (nonatomic, readonly) BOOL isRecommendedForHighResolutionFrameCapturing API_AVAILABLE(ios(16.0));

/**
 Determines whether the format supports high dynamic range (HDR).

 Read this property before setting ``ARConfiguration/videoHDRAllowed`` to `true` to first check whether a video format supports HDR.
 */
@property (nonatomic, readonly, getter=isVideoHDRSupported) BOOL videoHDRSupported API_AVAILABLE(ios(16.0));

/**
 The color space ARKit uses to configure the capture session when this video format is selected.
 */
@property (nonatomic, readonly) AVCaptureColorSpace defaultColorSpace API_AVAILABLE(ios(26.0)) API_UNAVAILABLE(visionos);

/**
 The default AVCapturePhotoSettings object that ARKit uses when capturing a high resolution frame using this video format.

 Calling this getter will return a new instance that may be mutated to customize settings. Pass that instance to
 `captureHighResolutionFrameUsingPhotoSettings:completion:` to capture a high resolution frame with custom settings.

 - Returns: An `AVCapturePhotoSettings` object.

 - SeeAlso: ``ARSession/captureHighResolutionFrameUsingPhotoSettings:completion:``
*/
@property (nonatomic, readonly) AVCapturePhotoSettings *defaultPhotoSettings API_AVAILABLE(ios(26.0)) API_UNAVAILABLE(visionos);

/**
 Unavailable.

 - Returns: This method is unavailable.
*/
- (instancetype)init NS_UNAVAILABLE;

/**
 Unavailable.

 - Returns: This method is unavailable.
*/
+ (instancetype)new NS_UNAVAILABLE;

@end

API_UNAVAILABLE_END

NS_ASSUME_NONNULL_END
#else
#import <ARKitCore/ARVideoFormat.h> 
#endif // #if (defined(USE_ARKIT_PUBLIC_HEADERS) \&\& USE_ARKIT_PUBLIC_HEADERS) || !__has_include(<ARKitCore/ARVideoFormat.h>)