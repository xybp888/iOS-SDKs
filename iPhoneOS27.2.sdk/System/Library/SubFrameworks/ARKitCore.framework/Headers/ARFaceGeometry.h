//
//  ARFaceGeometry.h
//  ARKit
//
//  Copyright © 2016-2021 Apple Inc. All rights reserved.
//

#import <ARKitCore/ARFaceAnchor.h>
#import <Foundation/Foundation.h>

@protocol MTLBuffer;
@protocol MTLDevice;
@class ARFaceAnchor;

NS_ASSUME_NONNULL_BEGIN

API_UNAVAILABLE_BEGIN(visionos)

/**
 A 3D mesh describing face topology for use in face-tracking AR sessions.

 This class provides a general model for the detailed topology of a face, in the form of a 3D mesh appropriate for use with various rendering
 technologies or for exporting 3D assets. (For a quick way to visualize a face geometry using SceneKit, see the ``ARSCNFaceGeometry`` class.)

 When you obtain a face geometry from an ``ARFaceAnchor`` object in a face-tracking AR session, the model conforms to match the dimensions, shape, and
 current expression of the detected face. You can also create a face mesh using a dictionary of named blend shape coefficients, which provides a
 detailed, but more efficient, description of the face's current expression.

 In an AR session, you can use this model as the basis for overlaying content that follows the shape of the user's face—for example, to apply virtual
 makeup or tattoos. You can also use this model to create occlusion geometry, which hides other virtual content behind the 3D shape of the detected
 face in the camera image.

 > Note:
 > Face mesh topology is constant across ``ARFaceGeometry`` instances. That is, the values of the ``vertexCount``, ``textureCoordinateCount``, and
 ``triangleCount`` properties never change, the ``triangleIndices-3tb1o`` buffer always describes the same arrangement of vertices, and the
 ``textureCoordinates-8ahq1`` buffer always maps the same vertex indices to the same texture coordinates.
 >
 > Only the ``vertices-fhdb`` buffer changes between face meshes provided by an AR session, indicating the change in vertex positions as ARKit adapts
 the mesh to the shape and expression of the user's face.
*/
API_AVAILABLE(ios(11.0))
NS_SWIFT_SENDABLE
@interface ARFaceGeometry : NSObject <NSSecureCoding, NSCopying>

/**
 The number of elements in the ``ARFaceGeometry/vertices-fhdb`` buffer.

 Face mesh topology is constant across ``ARFaceGeometry`` instances, so the value of this property is the same for all instances.
 */
@property (nonatomic, readonly) NSUInteger vertexCount NS_REFINED_FOR_SWIFT;

/**
 A buffer of vertex positions for each point in the face mesh.

 Each `float3` value in this buffer represents the position of a vertex in the mesh, in face coordinates. (See
 <doc:ARFaceAnchor#Tracking-Face-Position-and-Orientation>.)

 The ``ARFaceGeometry/vertexCount`` property provides the number of elements in the buffer.
 */
@property (nonatomic, readonly) const simd_float3 *vertices NS_REFINED_FOR_SWIFT;

/**
 The number of elements in the ``ARFaceGeometry/textureCoordinates-8ahq1`` buffer.

 Face mesh topology is constant across ``ARFaceGeometry`` instances, so the value of this property is the same for all instances.
 */
@property (nonatomic, readonly) NSUInteger textureCoordinateCount NS_REFINED_FOR_SWIFT;

/**
 A buffer of texture coordinate values for each point in the face mesh.

 Each `float2` value in this buffer represents the UV texture coordinates for the vertex at the corresponding index in the
 ``ARFaceGeometry/vertices-fhdb`` buffer.

 The ``ARFaceGeometry/textureCoordinateCount`` property provides the number of elements in the buffer.

 Face mesh topology is constant across ``ARFaceGeometry`` instances, so the data in this buffer always maps the same vertex indices to the same
 texture coordinates.
 */
@property (nonatomic, readonly) const simd_float2 *textureCoordinates NS_REFINED_FOR_SWIFT;

/**
 The number of triangles described by the ``ARFaceGeometry/triangleIndices-3tb1o`` buffer.

 Each set of three indices forms a triangle, so the number of indices in the ``ARFaceGeometry/triangleIndices-3tb1o`` buffer is three times the
 ``ARFaceGeometry/triangleCount`` value.

 Face mesh topology is constant across ``ARFaceGeometry`` instances, so the value of this property is the same for all instances.
 */
@property (nonatomic, readonly) NSUInteger triangleCount;

/**
 A buffer of indices describing the triangle mesh formed by the face geometry's vertex data.

 Each 16-bit integer value in this buffer represents an index into the ``ARFaceGeometry/vertices-fhdb`` and
 ``ARFaceGeometry/textureCoordinates-8ahq1`` buffers. Each set of three indices identifies the vertices that form a single triangle in the mesh. (That
 is, this buffer is appropriate for use as an index buffer for a triangle mesh in GPU-based rendering or creating 3D model asset files.)

 Each set of three indices forms a triangle, so the number of indices in the ``ARFaceGeometry/triangleIndices-3tb1o`` buffer is three times the
 ``ARFaceGeometry/triangleCount`` value.

 Face mesh topology is constant across ``ARFaceGeometry`` instances, so this buffer always describes the same arrangement of vertices. Only the
 ``ARFaceGeometry/vertices-fhdb`` buffer changes between face meshes provided by an AR session, indicating the change in vertex positions as ARKit
 adapts the mesh to the shape and expression of the user's face.
 */
@property (nonatomic, readonly) const int16_t *triangleIndices NS_REFINED_FOR_SWIFT;

/**
 Creates a face geometry matching the facial expression described in the specified dictionary.

 Each key in the `blendShapes` dictionary is an ``ARFaceAnchor/BlendShapeLocation`` constant identifying a facial feature. The corresponding value is
 the position of that feature relative to its neutral configuration, ranging from `0.0` (neutral) to `1.0` (maximum movement).

 The format of this dictionary is identical to that provided by the ``ARFaceAnchor`` ``ARFaceAnchor/blendShapes`` property. You can use that property
 and this initializer to efficiently save and restore facial expression data; the serialized form of a blend shapes dictionary is more portable than
 that of the face mesh those coefficients describe.

 - Parameter blendShapes: A dictionary of blend shape coefficients describing a facial expression in terms of the positions of specific facial
 features. For any coefficient not specified in this dictionary, ARKit assumes a value of `0.0`.
*/
- (nullable instancetype)initWithBlendShapes:(NSDictionary<ARBlendShapeLocation, NSNumber *> *)blendShapes;

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
