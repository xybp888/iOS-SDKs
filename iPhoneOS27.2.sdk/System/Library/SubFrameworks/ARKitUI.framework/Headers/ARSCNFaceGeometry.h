//
//  ARSCNFaceGeometry.h
//  ARKit
//
//  Copyright © 2016-2021 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <SceneKit/SCNGeometry.h>

@protocol MTLDevice;

API_UNAVAILABLE_BEGIN(visionos)

@class ARFaceGeometry;

NS_ASSUME_NONNULL_BEGIN

/**
 A SceneKit representation of face topology for use with face information that an AR session provides.

 This class is a subclass of <doc://com.apple.documentation/documentation/scenekit/scngeometry> that wraps the mesh data provided by the
 ``ARFaceGeometry`` class. You can use ``ARSCNFaceGeometry`` to quickly and easily visualize face topology and facial expressions provided by ARKit in
 a SceneKit view.

 > Important:
 > ``ARSCNFaceGeometry`` is available only in SceneKit views or renderers that use Metal. This class is not supported for OpenGL-based SceneKit
 rendering.

 Face mesh topology is constant for the lifetime of an ``ARSCNFaceGeometry`` object. That is, the geometry's single
 <doc://com.apple.documentation/documentation/scenekit/scngeometryelement> object always describes the same arrangement of vertices, and the
 <doc://com.apple.documentation/documentation/scenekit/scngeometrysource/semantic-swift.struct/texcoord> geometry source always maps the same vertices
 to the same texture coordinates.

 When you modify the geometry with the ``update(from:)`` method, only the contents of the
 <doc://com.apple.documentation/documentation/scenekit/scngeometrysource/semantic-swift.struct/vertex> geometry source change, indicating the
 difference in vertex positions as ARKit adapts the mesh to the shape and expression of the user's face.
 */
API_AVAILABLE(ios(11.0))
@interface ARSCNFaceGeometry : SCNGeometry

/**
 Creates a SceneKit face geometry for rendering with the specified Metal device object.

 A newly created ``ARSCNFaceGeometry`` instance represents a neutral, generic face; use the ``ARSCNFaceGeometry/update(from:)`` method to deform the
 geometry to match a specific facial expression or face shape.

 The geometry contains a single geometry element; as such, assigning more than one material has no visible effect (see the inherited
 <doc://com.apple.documentation/documentation/scenekit/scngeometry/materials> property).

 Calling this initializer is equivalent to calling the ``ARSCNFaceGeometry/init(device:fillMesh:)`` initializer and passing
 <doc://com.apple.documentation/documentation/swift/false> for the `fillMesh` parameter.

 - Parameter device: The Metal device to use for rendering the geometry.
*/
+ (nullable instancetype)faceGeometryWithDevice:(id<MTLDevice>)device;

/**
 Creates a SceneKit face geometry, optionally filling in gaps in the mesh for the eyes and mouth.

 A newly created ``ARSCNFaceGeometry`` instance represents a neutral, generic face; use the ``ARSCNFaceGeometry/update(from:)`` method to deform the
 geometry to match a specific facial expression or face shape.

 If the `fillMesh` parameter is <doc://com.apple.documentation/documentation/swift/false>, the geometry contains a single geometry element. If the
 `fillMesh` parameter is <doc://com.apple.documentation/documentation/swift/true>, the geometry contains four elements in the following order: the
 face itself, the left and right eyes, and the mouth. (When a SceneKit geometry contains multiple elements, the number and order of materials you
 assign to its <doc://com.apple.documentation/documentation/scenekit/scngeometry/materials> array determines whether the entire surface has a uniform
 appearance or different appearances for each geometry element.)

 - Parameters:
   - device: The Metal device to use for rendering the geometry.
   - fillMesh: If <doc://com.apple.documentation/documentation/swift/false>, the mesh doesn't include the eye and mouth areas of the face topology—as
 a result, if you render the face geometry for a face anchor atop the camera feed in an AR session, the user's eyes and the inside of the user's mouth
 (when open) are visible through the gaps in the 3D model.

     If <doc://com.apple.documentation/documentation/swift/true>, the mesh fills in the gaps for the eyes and mouth. This option can be useful when
 using the face geometry for occlusion only—that is, to prevent other 3D content from rendering behind it, while still showing the camera image
 beneath.
*/
+ (nullable instancetype)faceGeometryWithDevice:(id<MTLDevice>)device fillMesh:(BOOL)fillMesh;

/**
 Deforms the SceneKit geometry to match the specified face mesh.

 To update a SceneKit model of a face actively tracked in an AR session, call this method in your ``ARSCNViewDelegate`` object's
 ``ARSCNViewDelegate/renderer(_:didUpdate:for:)`` callback, passing the ``ARFaceAnchor/geometry`` property from the ``ARFaceAnchor`` object that
 callback provides.

 Alternatively, you can create, configure, and visualize face models independent of an AR session by creating face geometry objects using the
 ``ARFaceGeometry`` ``ARFaceGeometry/init(blendShapes:)`` initializer and passing them to this method.

 - Parameter faceGeometry: A coarse mesh representation of a face's topology, dimensions, and expression.
*/
- (void)updateFromFaceGeometry:(ARFaceGeometry *)faceGeometry;

/**
 Unavailable. ARSCNFaceGeometry objects are created by the system.

 - Returns: This method is unavailable.
*/
- (instancetype)init NS_UNAVAILABLE;

/**
 Unavailable. ARSCNFaceGeometry objects are created by the system.

 - Returns: This method is unavailable.
*/
+ (instancetype)new NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END

API_UNAVAILABLE_END
