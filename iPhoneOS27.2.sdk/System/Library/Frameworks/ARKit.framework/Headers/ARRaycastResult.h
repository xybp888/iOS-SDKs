#if (defined(USE_ARKIT_PUBLIC_HEADERS) && USE_ARKIT_PUBLIC_HEADERS) || !__has_include(<ARKitCore/ARRaycastResult.h>)
//
//  ARRaycastResult.h
//  ARKit
//
//  Copyright © 2018 Apple Inc. All rights reserved.
//

#import <ARKit/ARRaycastQuery.h>
#import <Foundation/Foundation.h>
#import <simd/simd.h>

@class ARAnchor;

NS_ASSUME_NONNULL_BEGIN

API_UNAVAILABLE_BEGIN(visionos)

/**
 Information about a real-world surface found by examining a point on the screen.

 A raycast projects a ray from a screen point into the physical environment and returns an ``ARRaycastResult`` describing each real-world surface the
 ray intersects.

 If you use <doc://com.apple.documentation/documentation/realitykit/arview> as your renderer, you can raycast from a screen point directly with
 <doc://com.apple.documentation/documentation/realitykit/arview/raycast(from:allowing:alignment:)>. With ``ARSCNView`` or a custom renderer, you
 first build a query and then run it:

 - Create a query with ``ARSCNView/raycastQuery(from:allowing:alignment:)`` or ``ARFrame/raycastQuery(from:allowing:alignment:)``.
 - Search for surfaces by passing that query to ``ARSession/raycast(_:)``.

 For tracked raycasting, you call ``ARSession/trackedRaycast(_:updateHandler:)`` on your app's current ``ARSession``.
 */
API_AVAILABLE(ios(13.0))
@interface ARRaycastResult : NSObject

/**
 The position, rotation, and scale, of the ray's intersection with the target.
 */
@property (nonatomic, readonly) simd_float4x4 worldTransform;

/**
 The type of surface that the ray intersects.
 */
@property (nonatomic, readonly, assign) ARRaycastTarget target;

/**
 The alignment of the plane that the ray intersected.
 */
@property (nonatomic, readonly, assign) ARRaycastTargetAlignment targetAlignment;

/**
 The anchor for the plane that the ray intersected.

 If you chose an existing plane target, ARKit provides its anchor. If you choose an estimated plane target, ARKit provides an anchor only if the ray
 intersects an existing plane.
*/
@property (nonatomic, readonly, strong, nullable) ARAnchor *anchor;

/**
 Unavailable. Raycast results are created by the system.

 - Returns: This method is unavailable.
*/
- (instancetype)init NS_UNAVAILABLE;

/**
 Unavailable. Raycast results are created by the system.

 - Returns: This method is unavailable.
*/
+ (instancetype)new NS_UNAVAILABLE;

@end

API_UNAVAILABLE_END

NS_ASSUME_NONNULL_END
#else
#import <ARKitCore/ARRaycastResult.h> 
#endif // #if (defined(USE_ARKIT_PUBLIC_HEADERS) \&\& USE_ARKIT_PUBLIC_HEADERS) || !__has_include(<ARKitCore/ARRaycastResult.h>)