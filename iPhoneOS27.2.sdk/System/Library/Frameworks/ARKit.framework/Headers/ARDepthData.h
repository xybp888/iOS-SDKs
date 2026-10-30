#if (defined(USE_ARKIT_PUBLIC_HEADERS) && USE_ARKIT_PUBLIC_HEADERS) || !__has_include(<ARKitFoundation/ARDepthData.h>)
//
//  ARDepthData.h
//  ARKit
//
//  Copyright © 2020 Apple Inc. All rights reserved.
//

#import <CoreVideo/CoreVideo.h>
#import <Foundation/Foundation.h>

API_UNAVAILABLE_BEGIN(visionos)

NS_ASSUME_NONNULL_BEGIN
/**
 Degrees to which the framework is confident about depth-data accuracy.
 */
typedef NS_ENUM(NSInteger, ARConfidenceLevel) {
    /**
     Depth-value accuracy in which the framework is less confident.
     */
    ARConfidenceLevelLow,
    /**
     Depth-value accuracy in which the framework is moderately confident.
     */
    ARConfidenceLevelMedium,
    /**
     Depth-value accuracy in which the framework is fairly confident.
     */
    ARConfidenceLevelHigh,
} API_AVAILABLE(ios(14.0));

/**
 An object that describes the distance to regions of the real world from the plane of the camera.

 This object contains the following depth information that the LiDAR scanner captures at runtime:

 - Every pixel in the ``depthMap`` maps to a region of the visible scene (``ARFrame/capturedImage``), where the pixel value defines that region's
 distance from the plane of the camera in meters.
 - The ``confidenceMap`` property measures the accuracy of the corresponding depth data in ``depthMap``, and is useful in filtering out lower-accuracy
 depth values if an app's algorithm required it.

 ``ARWorldTrackingConfiguration`` exposes this depth information in the ``ARFrame/sceneDepth`` property which it updates every frame. To enable scene
 depth, add the ``ARConfiguration/FrameSemantics/sceneDepth`` frame semantic to a world-tracking configuration's ``ARConfiguration/frameSemantics``
 and frames vended by the session contain ``ARDepthData`` captured by the LiDAR scanner.
 */
API_AVAILABLE(ios(14.0))
NS_SWIFT_SENDABLE
@interface ARDepthData : NSObject

/**
 The estimated distance from the device to its environment, in meters.

 For custom renderers, if you create a texture to send depth data to the GPU, choose a
 <doc://com.apple.documentation/documentation/metal/mtlpixelformat> according to the ``ARDepthData/depthMap`` pixel format. Call
 <doc://com.apple.documentation/documentation/corevideo/cvpixelbuffergetpixelformattype(_:)> on the ``ARDepthData/depthMap`` to get its format. For
 example, if at runtime the ``ARDepthData/depthMap`` format is <doc://com.apple.documentation/documentation/corevideo/kcvpixelformattype_depthfloat32>
 (<doc://com.apple.documentation/documentation/kernel/ostype> \``fdep`\`), use
 <doc://com.apple.documentation/documentation/metal/mtlpixelformat/r32float>.
 */
@property (nonatomic, assign, readonly) CVPixelBufferRef depthMap;

/**
 The framework's confidence in the accuracy of the depth-map data.

 The natural light of the physical environment affects the ``ARDepthData/depthMap`` property such that ARKit is less confident about the accuracy of
 the LiDAR Scanner's depth measurements for surfaces that are highly reflective, or that have high light absorption. This property measures the
 accuracy of the scene depth-data by containing an ``ARConfidenceLevel`` raw-value for every component in ``ARDepthData/depthMap``.

 Custom renderers that process confidence data on the GPU should choose a <doc://com.apple.documentation/documentation/metal/mtlpixelformat> according
 to the ``ARDepthData/confidenceMap`` pixel format the app reads at runtime. Call
 <doc://com.apple.documentation/documentation/corevideo/cvpixelbuffergetpixelformattype(_:)> on the ``ARDepthData/confidenceMap`` to get its format.
 If, for example, the ``ARDepthData/confidenceMap`` format is <doc://com.apple.documentation/documentation/corevideo/kcvpixelformattype_onecomponent8>
 (<doc://com.apple.documentation/documentation/kernel/ostype> \``L008`\`), create a Metal texture with format
 <doc://com.apple.documentation/documentation/metal/mtlpixelformat/r8uint> to send confidence data to the GPU.
 @see ARConfidenceLevel
 */
@property (nonatomic, assign, nullable, readonly) CVPixelBufferRef confidenceMap;

@end

API_UNAVAILABLE_END

NS_ASSUME_NONNULL_END
#else
#import <ARKitFoundation/ARDepthData.h> 
#endif // #if (defined(USE_ARKIT_PUBLIC_HEADERS) \&\& USE_ARKIT_PUBLIC_HEADERS) || !__has_include(<ARKitFoundation/ARDepthData.h>)