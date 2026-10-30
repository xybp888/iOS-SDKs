//
//  ARPlaneGeometry.h
//  ARKit
//
//  Copyright © 2016-2021 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <simd/simd.h>

@protocol MTLDevice;

NS_ASSUME_NONNULL_BEGIN

API_UNAVAILABLE_BEGIN(visionos)

/**
 A 3D mesh describing the shape of a detected plane in world-tracking AR sessions.

 This class provides the estimated general shape of a detected plane, in the form of a detailed 3D mesh appropriate for use with various rendering
 technologies or for exporting 3D assets. (For a quick way to visualize a plane geometry using SceneKit, see the ``ARSCNPlaneGeometry`` class.)

 Unlike the ``ARPlaneAnchor`` ``ARPlaneAnchor/center`` and ``ARPlaneAnchor/planeExtent`` properties, which estimate only a rectangular area for a
 detected plane, a plane anchor's ``ARPlaneAnchor/geometry`` property provides a more detailed estimate of the 2D area covered by that plane. For
 example, if ARKit detects a circular tabletop, the resulting ``ARPlaneGeometry`` objects roughly match the general shape of the table. As the session
 continues to run, ARKit provides updated plane anchors whose associated geometry refines the estimated shape of the plane.

 You can use this model to more precisely place 3D content that should appear only on a detected flat surface. For example, to ensure that virtual
 objects don't fall off the edge of a table. You can also use this model to create occlusion geometry, which hides other virtual content behind the
 detected surface in the camera image.

 The shape of a plane geometry is always convex. That is, the boundary polygon for a plane geometry is a minimal convex hull enclosing all points that
 ARKit recognizes or estimates are part of the plane.
*/
API_AVAILABLE(ios(11.3))
NS_SWIFT_SENDABLE
@interface ARPlaneGeometry : NSObject <NSSecureCoding>

/**
 The number of elements in the ``ARPlaneGeometry/vertices-3kgkm`` buffer.
 */
@property (nonatomic, readonly) NSUInteger vertexCount NS_REFINED_FOR_SWIFT;

/**
 A buffer of vertex positions for each point in the plane mesh.

 Each `float3` value in this buffer represents the position of a vertex in the mesh. The owning plane anchor's ``ARAnchor/transform`` matrix defines
 the coordinate system for these points.

 The ``ARPlaneGeometry/vertexCount`` property provides the number of elements in the buffer.

 This buffer, together with the ``ARPlaneGeometry/triangleIndices-1azi3`` buffer, describes a mesh covering the entire surface of the plane. Use this
 mesh for purposes that involve the filled shape, such as rendering a solid 3D representation of the surface. If, instead, you only need to know the
 outline of the shape, see the ``ARPlaneGeometry/boundaryVertices-6nbee`` property.
 */
@property (nonatomic, readonly) const simd_float3 *vertices NS_REFINED_FOR_SWIFT;

/**
 The number of elements in the ``ARPlaneGeometry/textureCoordinates-91pbc`` buffer.
 */
@property (nonatomic, readonly) NSUInteger textureCoordinateCount NS_REFINED_FOR_SWIFT;

/**
 A buffer of texture coordinate values for each point in the plane mesh.

 Each `float2` value in this buffer represents the UV texture coordinates for the vertex at the corresponding index in the
 ``ARPlaneGeometry/vertices-3kgkm`` buffer.
 */
@property (nonatomic, readonly) const simd_float2 *textureCoordinates NS_REFINED_FOR_SWIFT;

/**
 The number of triangles described by the ``ARPlaneGeometry/triangleIndices-1azi3`` buffer.

 Each set of three indices forms a triangle, so the number of indices in the ``ARPlaneGeometry/triangleIndices-1azi3`` buffer is three times the
 ``ARPlaneGeometry/triangleCount`` value.
 */
@property (nonatomic, readonly) NSUInteger triangleCount;

/**
 A buffer of indices describing the triangle mesh formed by the plane geometry's vertex data.

 Each 16-bit integer value in this buffer represents an index into the ``ARPlaneGeometry/vertices-3kgkm`` and
 ``ARPlaneGeometry/textureCoordinates-91pbc`` buffers. Each set of three indices identifies the vertices that form a single triangle in the mesh. You
 can use this buffer as an index buffer for a triangle mesh in GPU-based rendering or to create 3D model asset files.

 Each set of three indices forms a triangle, so the number of indices in the ``ARPlaneGeometry/triangleIndices-1azi3`` buffer is three times the
 ``ARPlaneGeometry/triangleCount`` value.
 */
@property (nonatomic, readonly) const int16_t *triangleIndices NS_REFINED_FOR_SWIFT;

/**
 The number of elements in the ``ARPlaneGeometry/boundaryVertices-6nbee`` buffer.
 */
@property (nonatomic, readonly) NSUInteger boundaryVertexCount NS_REFINED_FOR_SWIFT;

/**
 A buffer of vertex positions for each point along the plane's boundary.

 Each `float3` value in this buffer represents the position of a vertex along the boundary polygon of the estimated plane. The owning plane anchor's
 ``ARAnchor/transform`` matrix defines the coordinate system for these points.

 The ``ARPlaneGeometry/boundaryVertexCount`` property provides the number of elements in the buffer.

 This buffer defines the boundary polygon of the plane. Use it for purposes that require only that polygon's definition, such as rendering an outline
 of the plane's estimated shape or testing whether a point is inside the bounded region. If, instead, you need the filled shape (for example, to
 render a solid 3D representation of the surface), see the ``ARPlaneGeometry/vertices-3kgkm`` property.
 */
@property (nonatomic, readonly) const simd_float3 *boundaryVertices NS_REFINED_FOR_SWIFT;

/**
 Unavailable. ARPlaneGeometry objects are created by the system.

 - Returns: This method is unavailable.
*/
- (instancetype)init NS_UNAVAILABLE;

/**
 Unavailable. ARPlaneGeometry objects are created by the system.

 - Returns: This method is unavailable.
*/
+ (instancetype)new NS_UNAVAILABLE;

@end

API_UNAVAILABLE_END

NS_ASSUME_NONNULL_END
