#if (defined(USE_ARKIT_PUBLIC_HEADERS) && USE_ARKIT_PUBLIC_HEADERS) || !__has_include(<ARKitCore/ARRaycastQuery.h>)
//
//  ARRaycastQuery.h
//  ARKit
//
//  Copyright © 2018 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <simd/simd.h>

NS_ASSUME_NONNULL_BEGIN

API_UNAVAILABLE_BEGIN(visionos)

/**
 The types of surface you allow a raycast to intersect with.

 The available target types are plane, infinite plane, and estimated plane.
 */
API_AVAILABLE(ios(13.0))
typedef NS_ENUM(NSInteger, ARRaycastTarget) {
    /** A raycast target that requires a plane to have a definitive size and shape. */
    ARRaycastTargetExistingPlaneGeometry,

    /** A raycast target that specifies a detected plane, regardless of its size and shape. */
    ARRaycastTargetExistingPlaneInfinite,

    /**
     A raycast target that specifies nonplanar surfaces, or planes about which ARKit can only estimate.

     A raycast with this target intersects feature points around the ray that ARKit estimates may be a real-world surface.

     When combined with ``ARRaycastQuery/TargetAlignment/any``, ARKit bases estimated plane alignment on the normal of the surface.

     When you set your world-tracking configuration's ``ARWorldTrackingConfiguration/sceneReconstruction`` to one of the `mesh` options, ARKit allows
     a raycast with this target (and target-alignment ``ARRaycastQuery/TargetAlignment/any``) to intersect the scene mesh. Then the raycast result can
     include points even on nonplanar surfaces or surfaces that have few or no features, such as a white wall. If you set
     ``ARWorldTrackingConfiguration/sceneReconstruction`` to ``ARSceneReconstruction/ARSceneReconstructionNone``, raycasts ignore the scene mesh.
     */
    ARRaycastTargetEstimatedPlane,
} NS_SWIFT_NAME(ARRaycastQuery.Target);

/**
 A specification that indicates a target's alignment with respect to gravity.

 A raycast ignores potential targets with an alignment different than the one you specify in the raycast query.
 */
API_AVAILABLE(ios(13.0))
typedef NS_ENUM(NSInteger, ARRaycastTargetAlignment) {
    /** The case that indicates a target is aligned horizontally with respect to gravity. */
    ARRaycastTargetAlignmentHorizontal,

    /** The case that indicates a target is aligned vertically with respect to gravity. */
    ARRaycastTargetAlignmentVertical,

    /** The case that indicates a target may be aligned in any way with respect to gravity. */
    ARRaycastTargetAlignmentAny

} NS_SWIFT_NAME(ARRaycastQuery.TargetAlignment);

/**
 A mathematical ray you use to find 3D positions on real-world surfaces.

 You create a raycast query by providing a 3D vector and starting place.

 To create a raycast query using a 2D screen location and default vector that casts outward in the z-direction from the user, use the convenience
 functions, <doc://com.apple.documentation/documentation/realitykit/arview/makeraycastquery(from:allowing:alignment:)> on
 <doc://com.apple.documentation/documentation/realitykit/arview>, or ``ARSCNView/raycastQuery(from:allowing:alignment:)`` on ``ARSCNView``.

 Raycasts can intersect with planes (flat surfaces) or meshes (uneven surfaces). To intersect with planes, see ``Target``. To intersect with meshes,
 see ``Target/estimatedPlane``.
*/
API_AVAILABLE(ios(13.0))
@interface ARRaycastQuery : NSObject

/**
 A 3D coordinate that defines the ray's starting place.
 */
@property (nonatomic, readonly) simd_float3 origin;

/**
 A vector that describes the ray's trajectory in 3D space.
 */
@property (nonatomic, readonly) simd_float3 direction;

/**
 A plane type that allows the raycast to terminate if it's encountered.

 The available target types are plane, infinite plane, and estimated plane.
 */
@property (nonatomic, readonly) ARRaycastTarget target;

/**
 The target's alignment with respect to gravity.

 The available options are horizontal, vertical, or any.
 */
@property (nonatomic, readonly) ARRaycastTargetAlignment targetAlignment;

/**
 Creates a new raycast query.

 This creates a query by supplying a 3D starting place and vector. To acquire a raycast query using a screen point and vector that points outward from
 the user, call ``ARSCNView/raycastQuery(from:allowing:alignment:)`` on ``ARSCNView``.

 - Parameters:
   - origin: A 3D position that describes the raycast's starting point.
   - direction: A 3D vector that describes the raycast's direction.
   - target: The type of plane with which you allow the raycast to intersect.
   - alignment: The target's alignment with respect to gravity with which you allow the raycast to intersect.
*/
- (instancetype)initWithOrigin:(simd_float3)origin
                     direction:(simd_float3)direction
                allowingTarget:(ARRaycastTarget)target
                     alignment:(ARRaycastTargetAlignment)alignment;

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
#import <ARKitCore/ARRaycastQuery.h> 
#endif // #if (defined(USE_ARKIT_PUBLIC_HEADERS) \&\& USE_ARKIT_PUBLIC_HEADERS) || !__has_include(<ARKitCore/ARRaycastQuery.h>)