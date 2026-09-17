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
 An object representing the geometry of a face.

 The face geometry will have a constant number of triangles
 and vertices, updating only the vertex positions from frame to frame.
*/
API_AVAILABLE(ios(11.0))
NS_SWIFT_SENDABLE
@interface ARFaceGeometry : NSObject <NSSecureCoding, NSCopying>

/**
The number of mesh vertices of the geometry.
 */
@property (nonatomic, readonly) NSUInteger vertexCount NS_REFINED_FOR_SWIFT;

/**
 The mesh vertices of the geometry.
 */
@property (nonatomic, readonly) const simd_float3 *vertices NS_REFINED_FOR_SWIFT;

/**
 The number of texture coordinates of the face geometry.
 */
@property (nonatomic, readonly) NSUInteger textureCoordinateCount NS_REFINED_FOR_SWIFT;

/**
 The texture coordinates of the geometry.
 */
@property (nonatomic, readonly) const simd_float2 *textureCoordinates NS_REFINED_FOR_SWIFT;

/**
 The number of triangles of the face geometry.
 */
@property (nonatomic, readonly) NSUInteger triangleCount;

/**
 The triangle indices of the geometry.
 */
@property (nonatomic, readonly) const int16_t *triangleIndices NS_REFINED_FOR_SWIFT;

/**
 Creates and returns a face geometry by applying a set of given blend shape coefficients.

 An empty dictionary can be provided to create a neutral face geometry.

 - Parameter blendShapes: A dictionary of blend shape coefficients.

 - Returns: Face geometry after applying the blend shapes.
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
