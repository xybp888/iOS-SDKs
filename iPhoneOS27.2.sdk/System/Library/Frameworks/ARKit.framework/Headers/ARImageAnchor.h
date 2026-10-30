#if (defined(USE_ARKIT_PUBLIC_HEADERS) && USE_ARKIT_PUBLIC_HEADERS) || !__has_include(<ARKitCore/ARImageAnchor.h>)
//
//  ARImageAnchor.h
//  ARKit
//
//  Copyright © 2016-2021 Apple Inc. All rights reserved.
//

#import <ARKit/ARAnchor.h>
#import <CoreGraphics/CoreGraphics.h>

@class ARReferenceImage;

NS_ASSUME_NONNULL_BEGIN

API_UNAVAILABLE_BEGIN(visionos)

/**
 An anchor for a known image that ARKit detects in the physical environment.

 When you run a world-tracking AR session and specify ``ARReferenceImage`` objects for the session configuration's
 ``ARWorldTrackingConfiguration/detectionImages`` property, ARKit searches for those images in the real-world environment. When the session recognizes
 an image, it automatically adds an ``ARImageAnchor`` for each detected image to its list of anchors.

 To find the extent of a recognized image in the scene, use the inherited ``ARAnchor/transform`` property together with the
 ``ARReferenceImage/physicalSize`` of the anchor's ``referenceImage``.
 */
API_AVAILABLE(ios(11.3))
NS_SWIFT_SENDABLE
@interface ARImageAnchor : ARAnchor <ARTrackable>

/**
 The detected image referenced by the image anchor.

 This object is always one of the ``ARReferenceImage`` objects you provided in the ``ARWorldTrackingConfiguration/detectionImages`` array when
 configuring the session.
 */
@property (nonatomic, strong, readonly) ARReferenceImage *referenceImage;

/**
 A factor between the initial size and the estimated physical size.

 The default value is 1.0, which means that a version of this image that ARKit recognizes in the physical environment exactly matches its reference
 image ``ARReferenceImage/physicalSize``. ARKit only estimates this value when you set
 ``ARWorldTrackingConfiguration/automaticImageScaleEstimationEnabled`` to `true`; otherwise it remains 1.0.

 ARKit automatically corrects the image anchor's transform when `estimatedScaleFactor` is a value other than 1.0. This adjustment, in turn,
 corrects ARKit's understanding of where the image anchor is located in the physical environment.

 See ``ARWorldTrackingConfiguration/automaticImageScaleEstimationEnabled``.
*/
@property (nonatomic, readonly) CGFloat estimatedScaleFactor API_AVAILABLE(ios(13.0));

/**
 Unavailable.

 - Parameter transform: The transformation matrix.

 - Returns: This method is unavailable.
*/
- (instancetype)initWithTransform:(simd_float4x4)transform NS_UNAVAILABLE;

/**
 Unavailable.

 - Parameters:
   - name: The anchor name.
   - transform: The transformation matrix.

 - Returns: This method is unavailable.
*/
- (instancetype)initWithName:(NSString *)name transform:(simd_float4x4)transform NS_UNAVAILABLE;

@end

API_UNAVAILABLE_END

NS_ASSUME_NONNULL_END
#else
#import <ARKitCore/ARImageAnchor.h> 
#endif // #if (defined(USE_ARKIT_PUBLIC_HEADERS) \&\& USE_ARKIT_PUBLIC_HEADERS) || !__has_include(<ARKitCore/ARImageAnchor.h>)