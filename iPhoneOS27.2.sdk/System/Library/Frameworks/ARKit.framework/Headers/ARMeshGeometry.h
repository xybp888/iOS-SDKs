#if (defined(USE_ARKIT_PUBLIC_HEADERS) && USE_ARKIT_PUBLIC_HEADERS) || !__has_include(<ARKitCore/ARMeshGeometry.h>)
//
//  ARMeshGeometry.h
//  ARKit
//
//  Copyright © 2019 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <Metal/Metal.h>

NS_ASSUME_NONNULL_BEGIN

API_UNAVAILABLE_BEGIN(visionos)

/**
 Mesh data in a buffer-based array.

 Mesh-anchor geometry (``ARMeshGeometry``) uses geometry sources to hold 3D data like vertices, and normals, in an efficient, array-like format. A
 Metal buffer wraps the data, and other properties specify how to interpret that data.

 In the case that ``componentsPerVector`` is greater than 1, the element type of the geometry-source array is itself a sequence (pairs, triplets, and
 so on).
 */
API_AVAILABLE(ios(13.4))
NS_SWIFT_SENDABLE
@interface ARGeometrySource : NSObject <NSSecureCoding>

/**
 A Metal buffer that contains a list of vectors.

 Each vector in the buffer is of the type defined by ``ARGeometrySource/format``. Every vector may itself contain multiple scalars, defined by
 ``ARGeometrySource/componentsPerVector``.

 The buffer's <doc://com.apple.documentation/documentation/metal/mtlresource/storagemode> is
 <doc://com.apple.documentation/documentation/metal/mtlstoragemode/shared> which allows it to be accessed on both, the CPU, and GPU.
 */
@property (nonatomic, strong, readonly) id<MTLBuffer> buffer;

/**
 The number of vectors in the buffer.
 */
@property (nonatomic, assign, readonly) NSInteger count;

/**
 The type of vector data in the buffer.
 */
@property (nonatomic, assign, readonly) MTLVertexFormat format;

/**
 The number of scalar components in each vector.

 In the case that ``ARGeometrySource/componentsPerVector`` is greater than 1, the element type of the geometry-source array is itself, a sequence.
 */
@property (nonatomic, assign, readonly) NSInteger componentsPerVector;

/**
 The offset, in bytes, from the beginning of the buffer.
 */
@property (nonatomic, assign, readonly) NSInteger offset;

/**
 The length, in bytes, of the start of one vector in the buffer to the start of the next vector.

 Stride may contain padding, so it's not always equal to the vector-format's total size in bytes.
 */
@property (nonatomic, assign, readonly) NSInteger stride;

/**
 Unavailable. ARGeometrySource objects are created by the system.

 - Returns: This method is unavailable.
*/
- (instancetype)init NS_UNAVAILABLE;

/**
 Unavailable. ARGeometrySource objects are created by the system.

 - Returns: This method is unavailable.
*/
+ (instancetype)new NS_UNAVAILABLE;

@end

/**
 The kind of connection between vertices.

 When you enable ``ARWorldTrackingConfiguration/sceneReconstruction`` on a world-tracking configuration, ARKit provides a wireframe mesh that models
 the shape of the real world using a collection of connected vertices. ARKit uses ``ARGeometryPrimitiveType`` to indicate how a particular property of
 that mesh is interpreted. For example, a mesh geometry's ``ARMeshGeometry/faces`` property specifies that each face within the geometry is of type
 ``triangle``.
*/
API_AVAILABLE(ios(13.4))
typedef NS_ENUM(NSInteger, ARGeometryPrimitiveType) {
    /** A line segment in which a line connects two vertices. */
    ARGeometryPrimitiveTypeLine,
    /** Three vertices that connect to form a triangle. */
    ARGeometryPrimitiveTypeTriangle
};

/**
 A container for index data, such as vertex indices of a face.

 ``ARMeshGeometry`` uses geometry-elements to store face data (see ``ARMeshGeometry/faces``). Each face is defined by the primitive type, for example,
 ``ARGeometryPrimitiveType/triangle``.

 To demonstrate, an ``ARMeshGeometry`` instance with two triangle-type faces results in the following configuration:

 - `faces` ``count`` `= 2`
 - `faces` ``indexCountPerPrimitive`` `= 3` (because ``primitiveType`` is ``ARGeometryPrimitiveType/triangle``)
 - `faces` ``bytesPerIndex`` `= 4` (because vertex indices are the type <doc://com.apple.documentation/documentation/swift/uint32>)
 - The buffer's total size in bytes `=` ``count`` `*` ``indexCountPerPrimitive`` `*` ``bytesPerIndex`` (which in this case, is `2 * 3 * 4 = 24` bytes)
 */
API_AVAILABLE(ios(13.4))
NS_SWIFT_SENDABLE
@interface ARGeometryElement : NSObject <NSSecureCoding>

/**
 A Metal buffer containing primitive data.
 */
@property (nonatomic, strong, readonly) id<MTLBuffer> buffer;

/**
 The number of primitives in the buffer.
 */
@property (nonatomic, assign, readonly) NSInteger count;

/**
 The number of bytes for each index.
 */
@property (nonatomic, assign, readonly) NSInteger bytesPerIndex;

/**
 The number of indices for each primitive.

 The value of this property relates to the ``ARGeometryElement/primitiveType``. For ``ARGeometryPrimitiveType/triangle``, the value is 3. For more
 information, see ``ARGeometryPrimitiveType``.
*/
@property (nonatomic, assign, readonly) NSInteger indexCountPerPrimitive;

/**
 The geometry's type of data (triangle, or line).
 */
@property (nonatomic, assign, readonly) ARGeometryPrimitiveType primitiveType;

/**
 Unavailable. ARGeometryElement objects are created by the system.

 - Returns: This method is unavailable.
*/
- (instancetype)init NS_UNAVAILABLE;

/**
 Unavailable. ARGeometryElement objects are created by the system.

 - Returns: This method is unavailable.
*/
+ (instancetype)new NS_UNAVAILABLE;

@end

/**
 Enumeration of different classes of real-world objects that ARKit can identify.

 When you enable ``ARWorldTrackingConfiguration/sceneReconstruction`` on a world-tracking configuration, ARKit provides several mesh anchors
 (``ARMeshAnchor``) that collectively estimate the shape of the physical environment. Within that model of the real world, ARKit may identify specific
 objects, like seats, windows, tables, or walls. ARKit shares that information by exposing one or more ``ARMeshClassification`` instances in a mesh's
 ``ARMeshAnchor/geometry`` property.

 For a sample app that demonstrates mesh classification, see <doc:visualizing-and-interacting-with-a-reconstructed-scene>.
 */
API_AVAILABLE(ios(13.4))
typedef NS_ENUM(NSInteger, ARMeshClassification) {
    /** A face ARKit can't classify. */
    ARMeshClassificationNone = 0,
    /** The face is a part of a real-world wall. */
    ARMeshClassificationWall,
    /** The face is a part of a real-world floor. */
    ARMeshClassificationFloor,
    /** The face is a part of a real-world ceiling. */
    ARMeshClassificationCeiling,
    /** The face is a part of a real-world table. */
    ARMeshClassificationTable,
    /** The face is a part of a real-world seat. */
    ARMeshClassificationSeat,
    /** The face is a part of a real-world window. */
    ARMeshClassificationWindow,
    /** The face is a part of a real-world door. */
    ARMeshClassificationDoor,
};

/**
 Mesh information stored in an efficient, array-based format.

 The information in this class holds the geometry data for a single anchor of the scene mesh. Each vertex in the anchor's mesh represents one
 connection point. Every three-vertex combination forms a unique triangle called a _face_. Each face includes an outside-directional normal and a
 ``classification``. If ARKit cannot classify a particular face, the value is `0` — the raw value for ``ARMeshClassification/none``.
*/
API_AVAILABLE(ios(13.4))
NS_SWIFT_SENDABLE
@interface ARMeshGeometry : NSObject <NSSecureCoding>

/**
 The vertices of the mesh.

 The ``ARGeometrySource/count`` equals the total number of vertices. Since each vertex is the type `SIMD3<Float>`,
 ``ARGeometrySource/componentsPerVector`` is three.

 The following code demonstrates retrieving a vertex at a particular index.

 ```swift
 extension ARMeshGeometry {
     func vertex(at index: UInt32) -> SIMD3<Float> {
         assert(vertices.format == MTLVertexFormat.float3, "Expected three floats (twelve bytes) per vertex.")
         let vertexPointer = vertices.buffer.contents().advanced(by: vertices.offset + (vertices.stride * Int(index)))
         let vertex = vertexPointer.assumingMemoryBound(to: SIMD3<Float>.self).pointee
         return vertex
     }
 }
 ```
 */
@property (nonatomic, strong, readonly) ARGeometrySource *vertices;

/**
 Rays that define which direction is outside for each vertex.
 */
@property (nonatomic, strong, readonly) ARGeometrySource *normals;

/**
 An object that contains a buffer of vertex indices of the geometry's faces.

 Each element of the buffer-based array is a three-index combination that forms a unique triangle, or _face_. The index refers to that vertex's
 position in the ``ARMeshGeometry/vertices`` array. The ``ARGeometryElement/count`` of this property represents the number of faces.

 The following code demonstrates getting the vertices of a particular face:

 ```swift
 extension ARMeshGeometry {
     func vertexIndicesOf(faceWithIndex index: Int) -> [Int] {
         let indicesPerFace = faces.indexCountPerPrimitive
         let facesPointer = faces.buffer.contents()
         var vertexIndices = [Int]()
         for offset in 0..<indicesPerFace {
             let vertexIndexAddress = facesPointer.advanced(by: (index * indicesPerFace + offset) * MemoryLayout<UInt32>.size)
             vertexIndices.append(Int(vertexIndexAddress.assumingMemoryBound(to: UInt32.self).pointee))
         }
         return vertexIndices
     }
 }
 ```
 */
@property (nonatomic, strong, readonly) ARGeometryElement *faces;

/**
 Classification for each face in the mesh.

 Each element of the array is a face classification value (``ARMeshClassification``) that corresponds to one face in the geometry. The
 ``ARGeometrySource/count`` of this property represents the number of faces in the geometry. The default value at each index is `0` — the raw value
 for ``ARMeshClassification/none``.

 The following code demonstrates retrieving a classification for a particular face:

 ```swift
 extension ARMeshGeometry {
     func classificationOf(faceWithIndex index: Int) -> ARMeshClassification {
         guard let classification = classification else { return .none }
         let classificationAddress = classification.buffer.contents().advanced(by: index)
         let classificationValue = Int(classificationAddress.assumingMemoryBound(to: UInt8.self).pointee)
         return ARMeshClassification(rawValue: classificationValue) ?? .none
     }
 }
 ```

 For a sample app that demonstrates classification, see <doc:visualizing-and-interacting-with-a-reconstructed-scene>.
 */
@property (nonatomic, strong, readonly, nullable) ARGeometrySource *classification;

/**
 Unavailable. ARMeshGeometry objects are created by the system.

 - Returns: This method is unavailable.
*/
- (instancetype)init NS_UNAVAILABLE;

/**
 Unavailable. ARMeshGeometry objects are created by the system.

 - Returns: This method is unavailable.
*/
+ (instancetype)new NS_UNAVAILABLE;

@end

API_UNAVAILABLE_END

NS_ASSUME_NONNULL_END
#else
#import <ARKitCore/ARMeshGeometry.h> 
#endif // #if (defined(USE_ARKIT_PUBLIC_HEADERS) \&\& USE_ARKIT_PUBLIC_HEADERS) || !__has_include(<ARKitCore/ARMeshGeometry.h>)