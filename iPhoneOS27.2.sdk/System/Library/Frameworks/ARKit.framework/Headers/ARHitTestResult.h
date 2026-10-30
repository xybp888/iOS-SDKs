#if (defined(USE_ARKIT_PUBLIC_HEADERS) && USE_ARKIT_PUBLIC_HEADERS) || !__has_include(<ARKitCore/ARHitTestResult.h>)
//
//  ARHitTestResult.h
//  ARKit
//
//  Copyright © 2017 Apple Inc. All rights reserved.
//

#import <CoreGraphics/CGGeometry.h>
#import <Foundation/Foundation.h>
#import <simd/simd.h>

@class ARAnchor;

/**
 Possible types for specifying a hit-test search, or for the result of a hit-test search.
 */
API_DEPRECATED("Use raycasting", ios(11.0, 14.0))
typedef NS_OPTIONS(NSUInteger, ARHitTestResultType) {
    /**
     A point on a surface detected by ARKit, but not part of any detected planes.

     During a world-tracking AR session, ARKit builds a coarse point cloud representing its rough
     understanding of the 3D world around the user (see ``ARFrame/rawFeaturePoints``). Individual
     feature points represent parts of the camera image likely to be part of a real-world surface,
     but not necessarily a planar surface.

     When you search using this hit-test option, ARKit finds the feature point nearest to the
     hit-test ray (the extension of the 2D hit-test point into 3D world space), then returns the
     point on the ray nearest to that feature point.
     */
    ARHitTestResultTypeFeaturePoint = (1 << 0),

    /**
     A point on a real-world planar surface detected during the search, whose orientation is
     perpendicular to gravity.

     ARKit provides two ways to locate real-world flat surfaces in a scene. _Plane detection_
     (enabled with ``ARWorldTrackingConfiguration/planeDetection`` on your session configuration) is
     an ongoing process, continuously analyzing the scene to accurately map the position and extent
     of any planes in view. Because plane detection takes time, you can fall back to _plane
     estimation_ to get an instant, but less accurate, indication of whether a 2D point in the
     camera image corresponds to a real-world flat surface.

     Because plane detection results are more accurate than plane estimation results, ARKit prefers
     the former when searching for both. If your hit-test search includes both
     ``ARHitTestResult/ResultType/estimatedHorizontalPlane`` and one or more
     ``ARHitTestResult/ResultType/existingPlane`` types, and the search finds any already detected
     plane anchors, the search returns only the existing plane(s) and no estimated plane.

     An estimated plane search returns at most one result—the best estimate for a horizontal plane
     intersecting the hit-test ray.
     */
    ARHitTestResultTypeEstimatedHorizontalPlane = (1 << 1),

    /**
     A point on a real-world planar surface detected during the search, whose orientation is
     parallel to gravity.

     ARKit provides two ways to locate real-world flat surfaces in a scene. _Plane detection_
     (enabled with ``ARWorldTrackingConfiguration/planeDetection`` on your session configuration) is
     an ongoing process, continuously analyzing the scene to accurately map the position and extent
     of any planes in view. Because plane detection takes time, you can fall back to _plane
     estimation_ to get an instant, but less accurate, indication of whether a 2D point in the
     camera image corresponds to a real-world flat surface.

     Because plane detection results are more accurate than plane estimation results, ARKit prefers
     the former when searching for both. If your hit-test search includes both
     ``ARHitTestResult/ResultType/estimatedVerticalPlane`` and one or more
     ``ARHitTestResult/ResultType/existingPlane`` types, and the search finds any already detected
     plane anchors, the search returns only the existing plane(s) and no estimated plane.

     An estimated plane search returns at most one result—the best estimate for a vertical plane
     intersecting the hit-test ray.
     */
    ARHitTestResultTypeEstimatedVerticalPlane API_AVAILABLE(ios(11.3)) = (1 << 2),

    /**
     A point on a real-world plane (already detected with the
     ``ARWorldTrackingConfiguration/planeDetection`` option), without considering the plane's size.

     When searching for this result type, ARKit can return any point coplanar with an already
     detected plane, regardless of whether that plane's already detected ``ARPlaneAnchor/extent`` or
     ``ARPlaneAnchor/geometry`` includes that point. (That is, this result type searches the infinite
     extensions of detected planes.)

     An existing plane search can return any number of results, depending on how many
     already-detected planes the hit test ray intersects (if any).
     */
    ARHitTestResultTypeExistingPlane = (1 << 3),

    /**
     A point on a real-world plane (already detected with the
     ``ARWorldTrackingConfiguration/planeDetection`` option), respecting the plane's estimated size.

     When searching for this result type, ARKit returns a point coplanar with an already detected
     plane only if that point lies within the area defined by the plane's ``ARPlaneAnchor/center``
     and ``ARPlaneAnchor/extent`` properties. Those properties (together with the anchor's
     ``ARAnchor/transform``) define the smallest rectangular area that includes all regions ARKit
     estimates to be a part of the plane.

     However, that rectangular area may contain regions that are not part of the same real-world
     surface. There may also be parts of the same real-world surface that lie outside the rectangle
     because ARKit has not yet recognized them as part of the same plane. To get a more precise
     result that follows the plane's actual shape, test with the
     ``ARHitTestResult/ResultType/existingPlaneUsingGeometry`` type. To ignore the plane's estimated
     size and treat it as an infinite plane, test with the
     ``ARHitTestResult/ResultType/existingPlane`` type.

     An existing plane search can return any number of results, depending on how many
     already-detected planes the hit test ray intersects (if any).
     */
    ARHitTestResultTypeExistingPlaneUsingExtent = (1 << 4),

    /**
     A point on a real-world plane (already detected with the
     ``ARWorldTrackingConfiguration/planeDetection`` option), respecting the plane's estimated size
     and shape.

     When searching for this result type, ARKit returns a point coplanar with an already detected
     plane only if that point lies within the area defined by the plane's ``ARPlaneAnchor/geometry``.
     That property (together with the anchor's ``ARAnchor/transform``) defines the smallest polygonal
     area that includes all regions ARKit estimates to be a part of the plane.

     Because that polygon is always convex, it may contain regions that are not part of the same
     real-world surface. (It does, however, provide a more precise estimate than a bounding rectangle
     provided by the ``ARHitTestResult/ResultType/existingPlaneUsingExtent`` type.) There may also be
     parts of the same real-world surface that lie outside the polygon because ARKit has not yet
     recognized them as part of the same plane. You extend your hit test to an infinite plane by
     using the ``ARHitTestResult/ResultType/existingPlane`` type.

     An existing plane search can return any number of results, depending on how many
     already-detected planes the hit test ray intersects (if any).
     */
    ARHitTestResultTypeExistingPlaneUsingGeometry API_AVAILABLE(ios(11.3)) = (1 << 5),
} NS_SWIFT_NAME(ARHitTestResult.ResultType);

NS_ASSUME_NONNULL_BEGIN

API_UNAVAILABLE_BEGIN(visionos)

/**
 Information about a real-world surface found by examining a point on the screen.

 If you use SceneKit or SpriteKit as your renderer, you can search for real-world surfaces at a
 screen point using:

 - ``ARSCNView`` ``ARSCNView/hitTest(_:types:)``
 - ``ARSKView`` ``ARSKView/hitTest(_:types:)``

 Otherwise, you can search the camera image for real-world content using the ``ARFrame``
 ``ARFrame/hitTest(_:types:)`` method. Because a frame is independent of a view, for this method you
 pass a point specified in normalized image coordinates (where `(0,0)` is the top left corner of the
 image and `(1,1)` is the lower right).

 All these methods return an array of ``ARHitTestResult`` objects describing the content found. The
 number and order of results in the array depends on the search types you specify and the order you
 specify them in. For example, consider the code below:

 ```swift
 let results = view.hitTest(point, [.existingPlaneUsingGeometry, .estimatedHorizontalPlane])
 ```

 This ``ARSCNView/hitTest(_:types:)`` call searches first for plane anchors already present in the
 session (according to the session configuration's ``ARWorldTrackingConfiguration/planeDetection``
 settings); returning any such results (in order of distance from the camera) as the first elements
 in the array. This call also (due to the ``ResultType/estimatedHorizontalPlane`` request) attempts
 to determine whether the hit test ray intersects any horizontal surface not already found by plane
 detection, and returns that result (if any) as the last element in the array.
 */
API_DEPRECATED("Use raycasting", ios(11.0, 14.0))
@interface ARHitTestResult : NSObject

/**
 The kind of detected feature the search result represents.

 You specify one or more result types to search for when calling a hit-testing method. A result
 object has only one result type.
 */
@property (nonatomic, readonly) ARHitTestResultType type;

/**
 The distance, in meters, from the camera to the detected surface.
 */
@property (nonatomic, readonly) CGFloat distance;

/**
 The position and orientation of the result relative to the nearest anchor or feature point.

 This transform matrix indicates the intersection point between the detected surface and the ray
 that created the hit-test result. A hit-test projects a 2D point in the image or view coordinate
 system along a ray into the 3D world space and reports results where that line intersects detected
 surfaces.
 */
@property (nonatomic, readonly) simd_float4x4 localTransform;

/**
 The position and orientation of the result relative to the world coordinate system.

 This transform matrix indicates the intersection point between the detected surface and the ray
 that created the hit-test result. A hit-test projects a 2D point in the image or view coordinate
 system along a ray into the 3D world space and reports results where that line intersects detected
 surfaces.

 The session configuration's ``ARConfiguration/worldAlignment`` property defines the world
 coordinate system.
 */
@property (nonatomic, readonly) simd_float4x4 worldTransform;

/**
 The anchor representing the detected surface, if any.

 ARKit provides an anchor only for existing-plane result types. Feature-point and estimated-plane results don't include an anchor.
*/
@property (nonatomic, strong, nullable, readonly) ARAnchor *anchor;

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
#import <ARKitCore/ARHitTestResult.h> 
#endif // #if (defined(USE_ARKIT_PUBLIC_HEADERS) \&\& USE_ARKIT_PUBLIC_HEADERS) || !__has_include(<ARKitCore/ARHitTestResult.h>)