#if (defined(USE_ARKIT_PUBLIC_HEADERS) && USE_ARKIT_PUBLIC_HEADERS) || !__has_include(<ARKitCore/ARBodyAnchor.h>)
//
//  ARBodyAnchor.h
//  ARKit
//
//  Copyright © 2019 Apple Inc. All rights reserved.
//

#import <ARKit/ARAnchor.h>
#import <CoreGraphics/CGGeometry.h>

NS_ASSUME_NONNULL_BEGIN

API_UNAVAILABLE_BEGIN(visionos)

@class ARBody2D;
@class ARSkeleton3D;

/**
 An anchor representing a body in the world.
 */
API_AVAILABLE(ios(13.0))
NS_SWIFT_SENDABLE
@interface ARBodyAnchor : ARAnchor <ARTrackable>

/**
 The tracked skeleton in 3D.
 - Note: The default height of this skeleton, measured from lowest to highest joint in standing position, is defined to be 1.71 meters.
*/
@property (nonatomic, strong, readonly) ARSkeleton3D *skeleton;

/**
 The factor between estimated physical size and default size of the skeleton.

 This value will be estimated if `automaticSkeletonScaleEstimationEnabled` is set to `true` on the `ARBodyTrackingConfiguration`.
 It is used to correct the transform's translation. Default value is `1.0`.

 - SeeAlso: ``ARSkeletonDefinition/neutralBodySkeleton3D``
*/
@property (nonatomic, readonly) CGFloat estimatedScaleFactor;

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
#import <ARKitCore/ARBodyAnchor.h> 
#endif // #if (defined(USE_ARKIT_PUBLIC_HEADERS) \&\& USE_ARKIT_PUBLIC_HEADERS) || !__has_include(<ARKitCore/ARBodyAnchor.h>)