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
 An anchor that tracks the position and movement of a human body in the rear-facing camera.

 This ``ARAnchor`` subclass tracks the movement of a single person. You enable body tracking by running your session using
 ``ARBodyTrackingConfiguration``.

 When ARKit recognizes a person in the back camera feed, it calls your delegate's ``ARSessionDelegate/session(_:didAdd:)`` function with
 ``ARBodyAnchor``. A body anchor's ``ARAnchor/transform`` position defines the world position of the body's hip joint.

 You can also check within the frame's ``ARFrame/anchors`` for a body that ARKit is tracking.

 ### Place a Skeleton on a Surface

 Because a body anchor's origin maps to the hip joint, you calculate the current offset of the feet to the hip to place the body's skeleton on a
 surface. By passing the foot joint index to ``ARSkeleton3D/jointModelTransforms-dno4``, you get the foot's offset from skeleton's origin.

 ```swift
 static var hipToFootOffset: Float {
     // Get an index for a foot.
     let footIndex = ARSkeletonDefinition.defaultBody3D.index(for: .leftFoot)
     // Get the foot's world-space offset from the hip.
     let footTransform = ARSkeletonDefinition.defaultBody3D.neutralBodySkeleton3D!.jointModelTransforms[footIndex]
     // Return the height by getting just the y-value.
     let distanceFromHipOnY = abs(footTransform.columns.3.y)
     return distanceFromHipOnY
 }
 ```
 */
API_AVAILABLE(ios(13.0))
NS_SWIFT_SENDABLE
@interface ARBodyAnchor : ARAnchor <ARTrackable>

/**
 The tracked body in 3D.

 Use this property to interpret motion information in 3D space.

 - Note: The default height of this skeleton, measured from lowest to highest joint in standing position, is defined to be 1.71 meters.
*/
@property (nonatomic, strong, readonly) ARSkeleton3D *skeleton;

/**
 A factor that relates the body's default height with the height ARKit estimates at runtime.

 The default value is 1.0. If you set ``ARBodyTrackingConfiguration/automaticSkeletonScaleEstimationEnabled`` to
 <doc://com.apple.documentation/documentation/swift/true> on ``ARBodyTrackingConfiguration``, ARKit sets this property to a scale factor that
 relates the estimated height of the person in the camera feed to the default body height.

 ARKit must know the height of a person in the camera feed to estimate an accurate world position for the person's body anchor. ARKit uses the value
 of ``ARBodyAnchor/estimatedScaleFactor`` to correct the body anchor's position in the physical environment.

 The default body is 1.71 meters tall.

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