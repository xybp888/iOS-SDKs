#if (defined(USE_ARKIT_PUBLIC_HEADERS) && USE_ARKIT_PUBLIC_HEADERS) || !__has_include(<ARKitCore/ARCamera.h>)
//
//  ARCamera.h
//  ARKit
//
//  Copyright © 2016-2021 Apple Inc. All rights reserved.
//

#import <TargetConditionals.h>

#import <ARKit/ARTrackingStatusTypes.h>
#import <CoreGraphics/CoreGraphics.h>
#import <Foundation/Foundation.h>
#import <simd/simd.h>

NS_ASSUME_NONNULL_BEGIN

API_UNAVAILABLE_BEGIN(visionos)

/**
 Information about the camera position and imaging characteristics for a given frame.

 You get camera information from the `ARFrame.camera` property of each `ARFrame` ARKit delivers.
 */
API_AVAILABLE(ios(11.0))
NS_SWIFT_SENDABLE
@interface ARCamera : NSObject <NSCopying>

/**
 The position and orientation of the camera in world coordinate space.

 World coordinate space in ARKit always follows a right-handed convention, but is oriented based on the session configuration. For details, see
 <doc:understanding-world-tracking>.

 This transform creates a local coordinate space for the camera that is constant with respect to device orientation.
 In camera space, the x-axis points to the right when the device is in
 <doc://com.apple.documentation/documentation/uikit/uideviceorientation/landscapeleft> orientation—that is, the x-axis always points along the long
 axis of the device, from the front-facing camera toward the Home button. The y-axis points upward (with respect to
 <doc://com.apple.documentation/documentation/uikit/uideviceorientation/landscapeleft> orientation), and the z-axis points away from the device on the
 screen side.
 */
@property (nonatomic, readonly) simd_float4x4 transform;

/**
 The orientation of the camera, expressed as roll, pitch, and yaw values.

 The order of components in this vector matches the axes of rotation:
    1. Pitch (the x component) is the rotation about the node’s x-axis (in radians)
    2. Yaw   (the y component) is the rotation about the node’s y-axis (in radians)
    3. Roll  (the z component) is the rotation about the node’s z-axis (in radians)
 ARKit applies these rotations in the following order:
    1. first roll
    2. then pitch
    3. then yaw
 */
@property (nonatomic, readonly) simd_float3 eulerAngles;

/**
 The general quality of position tracking available when the camera captured a frame.
 */
@property (nonatomic, readonly) ARTrackingState trackingState NS_REFINED_FOR_SWIFT;

/**
 A possible diagnosis for limited position-tracking quality as of when the camera captured a frame.
 */
@property (nonatomic, readonly) ARTrackingStateReason trackingStateReason NS_REFINED_FOR_SWIFT;

/**
 A matrix that converts between the 2D camera plane and 3D world coordinate space.

 The intrinsic matrix (commonly represented in equations as `K`) is based on physical characteristics of the device camera and a pinhole camera model.
 You can use the matrix to transform 3D coordinates to 2D coordinates on an image plane.

 The matrix has the following contents:
 fx 0   px
 0  fy  py
 0  0   1
 The values `fx` and `fy` are the pixel focal length, and are identical for square pixels. The values `px` and `py` are the coordinates of the
 principal point—the offsets of the principal point from the top-left corner of the image frame. All values are expressed in pixels. The origin is at
 the center of the upper-left pixel.
*/
@property (nonatomic, readonly) simd_float3x3 intrinsics;

/**
 The width and height, in pixels, of the captured camera image.

 This size describes the image in the `ARFrame.capturedImage` buffer, which contains image data in the camera device's native sensor orientation. To
 convert image coordinates to match a specific display orientation of that image, use the ``viewMatrixForOrientation:`` or
 ``projectPoint:orientation:viewportSize:`` method.
 */
@property (nonatomic, readonly) CGSize imageResolution;

/**
 A value you use to effect motion blur when rendering your app's virtual content.

 If you display an AR experience using a custom Metal renderer, use this value to determine how much motion blur to apply to your virtual content.

 If `ARSCNView` is your renderer, SceneKit automatically applies motion blur to your virtual content. For more information, see
 `ARSCNView.rendersMotionBlur`.
 */
@property (nonatomic, readonly) NSTimeInterval exposureDuration API_AVAILABLE(ios(13.0));

/**
 A value you supply to your custom renderer to light your scene.

 If your app displays an AR experience using a custom Metal renderer, use this value to light your scene during its post-processed lighting stage.

 Lighting a scene using ``exposureOffset`` is normally more performant than scaling each light source in your scene based on the value of the frame's
 `ARFrame.lightEstimate`.
 */
@property (nonatomic, readonly) float exposureOffset API_AVAILABLE(ios(13.0));

/**
 A transform matrix appropriate for rendering 3D content to match the image captured by the camera.

 Reading this property's value is equivalent to calling the ``projectionMatrixForOrientation:viewportSize:zNear:zFar:`` method, using the camera's
 ``imageResolution`` and ``intrinsics`` properties to derive size and orientation, and passing default values of `0.001` and `1000.0` for the near and
 far clipping planes.

 The projection matrix assumes no far clipping plane limit.
*/
@property (nonatomic, readonly) simd_float4x4 projectionMatrix;


/**
 Interface orientation enumeration type (from UIKit).
 */
typedef NS_ENUM(NSInteger, UIInterfaceOrientation);

/**
 Returns a transform matrix appropriate for rendering 3D content to match the image captured by the camera, using the specified parameters.

 This method has no effect on ARKit, and the `zNear` and `zFar` parameters have no relationships to ARKit camera state. Instead, this method uses
 those parameters as well as the camera's state to construct a projection matrix for use in your own rendering code.

 The projection matrix returned provides an aspect fill for the provided viewport size and orientation.
 If zFar is set to 0, an infinite projection matrix will be returned.

 - Parameters:
   - orientation: The orientation in which the camera image is to be presented.
   - viewportSize: The size, in points, of the view in which the camera image is to be presented.
   - zNear: The distance from the camera to the near clipping plane.
   - zFar: The distance from the camera to the far clipping plane.

 - Returns: A projection matrix that provides an aspect fill and rotation for the provided viewport size and orientation.
*/
- (simd_float4x4)projectionMatrixForOrientation:(UIInterfaceOrientation)orientation
                                   viewportSize:(CGSize)viewportSize
                                          zNear:(CGFloat)zNear
                                           zFar:(CGFloat)zFar
    API_DEPRECATED("Use projectionMatrixForViewRotationAngle:viewportSize:zNear:zFar:", ios(11.0, 27.0));

/**
 Creates a projection matrix for the camera given rendering parameters.

 The projection matrix returned provides an aspect fill for the provided viewport size and view angle.
 If zFar is set to 0, an infinite projection matrix will be returned.

 The view angle, in degrees, is the clockwise rotation needed to keep the camera image level with the horizon
 (`0` LandscapeRight, `90` Portrait, `180` LandscapeLeft, `270` PortraitUpsideDown). Obtain it from
 `ARSession.viewRotationAngle`.

 - Parameters:
   - viewRotationAngle: View rotation angle in degrees.
   - viewportSize: Viewport size.
   - zNear: Near depth limit.
   - zFar: Far depth limit.

 - Returns: The projection matrix for the given parameters.
*/
- (simd_float4x4)projectionMatrixForViewRotationAngle:(CGFloat)viewRotationAngle
                                         viewportSize:(CGSize)viewportSize
                                                zNear:(CGFloat)zNear
                                                 zFar:(CGFloat)zFar NS_SWIFT_NAME(projectionMatrix(viewRotationAngle:viewportSize:zNear:zFar:))
                                                          API_AVAILABLE(ios(27.0));

/**
 Returns the projection of a point from the 3D world space detected by ARKit into the 2D space of a view rendering the scene.

 If you display AR content with SceneKit, the `ARSCNView` class provides an otherwise equivalent
 <doc://com.apple.documentation/documentation/scenekit/scnscenerenderer/projectpoint(_:)> method that requires fewer parameters (because the view can
 infer its orientation and size).

 - Parameters:
   - point: The 3D world-space point to project into 2D view space.
   - orientation: The orientation in which the camera image is to be presented.
   - viewportSize: The size, in points, of the view in which the camera image is to be presented.

 - Returns: The projection of the specified point into a 2D pixel coordinate space whose origin is in the upper left corner and whose size matches
 that of the `viewportSize` parameter.
*/
- (CGPoint)projectPoint:(simd_float3)point
            orientation:(UIInterfaceOrientation)orientation
           viewportSize:(CGSize)viewportSize API_DEPRECATED("Use projectPoint:viewRotationAngle:viewportSize:", ios(11.0, 27.0));

/**
 Project a 3D point in world coordinate system into 2D viewport space.

 The view angle, in degrees, is the clockwise rotation needed to keep the camera image level with the horizon
 (`0` LandscapeRight, `90` Portrait, `180` LandscapeLeft, `270` PortraitUpsideDown). Obtain it from
 `ARSession.viewRotationAngle`.

 - Parameters:
   - point: 3D point in world coordinate system.
   - viewRotationAngle: View rotation angle in degrees.
   - viewportSize: Viewport (or image) size.

 - Returns: 2D point in viewport coordinate system with origin at top-left.
*/
- (CGPoint)projectPoint:(simd_float3)point viewRotationAngle:(CGFloat)viewRotationAngle viewportSize:(CGSize)viewportSize API_AVAILABLE(ios(27.0));

/**
 Returns the projection of a point from the 2D space of a view rendering the scene onto a plane in the 3D world space detected by ARKit.

 A 2D point in the viewport coordinate space can refer to any point along a line segment in the 3D coordinate space. Unprojecting calculates the 3D
 position of the point along this line segment that intersects the provided plane.

 If you display AR content with SceneKit, the `ARSCNView` class provides an otherwise equivalent `ARSCNView.unprojectPoint(_:ontoPlane:)` method that
 requires fewer parameters (because the view can infer its orientation and size).

 - Parameters:
   - point: The point in 2D view space to project onto a plane.

     The coordinate space for this point has its origin in the upper left corner and a size matching the `viewportSize` parameter.
   - planeTransform: A transform matrix specifying the position and orientation of a plane (with infinite extent) in 3D world space. The plane is the
 xz-plane of the local coordinate space this transform defines.
   - orientation: The orientation in which the camera image is to be presented.
   - viewportSize: The size, in points, of the view in which the camera image is to be presented.

 - Returns: The 3D point in world space where a ray projected from the specified 2D point intersects the specified plane. If the ray does not
 intersect the plane, this method returns a `float3` vector where all elements are `NaN`.
*/
- (simd_float3)unprojectPoint:(CGPoint)point
       ontoPlaneWithTransform:(simd_float4x4)planeTransform
                  orientation:(UIInterfaceOrientation)orientation
                 viewportSize:(CGSize)viewportSize
    API_DEPRECATED("Use unprojectPoint:ontoPlaneWithTransform:viewRotationAngle:viewportSize:", ios(12.0, 27.0))NS_REFINED_FOR_SWIFT;

/**
 Unproject a 2D point from the viewport onto a plane in 3D world coordinates.

 A 2D point in the viewport coordinate space can refer to any point along a line segment in the 3D coordinate space.
 Unprojecting calculates the 3D position of the point along this line segment that intersects the provided plane.

 The view angle, in degrees, is the clockwise rotation needed to keep the camera image level with the horizon
 (`0` LandscapeRight, `90` Portrait, `180` LandscapeLeft, `270` PortraitUpsideDown). Obtain it from
 `ARSession.viewRotationAngle`.

 - Parameters:
   - point: A point in the viewport coordinate system with origin at top-left.
   - planeTransform: The transform used to define the coordinate system of the plane.
     The coordinate system's positive Y axis is assumed to be the normal of the plane.
   - viewRotationAngle: View rotation angle in degrees.
   - viewportSize: The size of the viewport.

 - Returns: 3D position in world coordinates or `NAN` values if unprojection is not possible.
*/
- (simd_float3)unprojectPoint:(CGPoint)point
       ontoPlaneWithTransform:(simd_float4x4)planeTransform
            viewRotationAngle:(CGFloat)viewRotationAngle
                 viewportSize:(CGSize)viewportSize API_AVAILABLE(ios(27.0))NS_REFINED_FOR_SWIFT;

/**
 Returns a transform matrix for converting from world space to camera space.

 This method has no effect on ARKit. Instead, this method uses the orientation parameter and the camera's state to construct a view matrix for your
 own rendering code.

 The view matrix can be used to transform geometry from world space into camera space for a given orientation.

 - Parameter orientation: The orientation in which the camera image is to be presented.

 - Returns: A view matrix appropriate for the camera with the specified orientation.
*/
- (simd_float4x4)viewMatrixForOrientation:(UIInterfaceOrientation)orientation API_DEPRECATED("Use viewMatrixForViewRotationAngle:", ios(11.0, 27.0));

/**
 Returns the view matrix for the camera with a given view angle.

 The view matrix can be used to transform geometry from world space into camera space for a given view angle.

 The view angle, in degrees, is the clockwise rotation needed to keep the camera image level with the horizon
 (`0` LandscapeRight, `90` Portrait, `180` LandscapeLeft, `270` PortraitUpsideDown). Obtain it from
 `ARSession.viewRotationAngle`.

 - Parameter viewRotationAngle: The view rotation angle, in degrees, that will be used to render the camera's view.

 - Returns: The view matrix for the given view angle.
*/
- (simd_float4x4)viewMatrixForViewRotationAngle:(CGFloat)viewRotationAngle NS_SWIFT_NAME(viewMatrix(viewRotationAngle:)) API_AVAILABLE(ios(27.0));


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
#import <ARKitCore/ARCamera.h> 
#endif // #if (defined(USE_ARKIT_PUBLIC_HEADERS) \&\& USE_ARKIT_PUBLIC_HEADERS) || !__has_include(<ARKitCore/ARCamera.h>)