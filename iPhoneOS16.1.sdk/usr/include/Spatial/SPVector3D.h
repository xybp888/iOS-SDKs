#ifndef SPVector3D_h
#define SPVector3D_h

#include <Spatial/Structures.h>
#include <Spatial/SPAffineTransform3D.h>
#include <Spatial/SPProjectiveTransform3D.h>
#include <Spatial/SPPoint3D.h>

// MARK: - SPVector3DMake

/*!
 @abstract Creates a point with the specified coordinates.
 
 @param x The first element of the vector.
 @param y The second element of the vector.
 @param z The third element of the vector.
 @returns A new vector.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPVector3D SPVector3DMake(double x, double y, double z)
__API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPVector3D SPVector3DMake(double x, double y, double z) {
    return (SPVector3D){ .x = x, .y = y, .z = z };
}

// MARK: - SPVector3DMakeWithVector

/*!
 @abstract Creates a vector with elements specified as a 3-element SIMD vector.
 
 @param xyz The source simd vector.
 @returns A new vector.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPVector3D SPVector3DMakeWithVector(simd_double3 xyz)
__API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPVector3D SPVector3DMakeWithVector(simd_double3 xyz) {
    return (SPVector3D){ .vector = xyz};
}

// MARK: - SPPoint3DMakeWithRotationAxis

/*!
 @abstract Creates a vector with elements specified as dimensions of a rotation axis structure.
 
 @param axis The source rotation axis.
 @returns A new vector.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPVector3D SPVector3DMakeWithRotationAxis(SPRotationAxis3D axis)
__API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPVector3D SPVector3DMakeWithRotationAxis(SPRotationAxis3D axis) {
    return (SPVector3D){ .vector = axis.vector };
}

// MARK: - SPPoint3DMakeWithSize

/*!
 @abstract Creates a vector with elements specified as dimensions of a size structure.
 
 @param size The source size.
 @returns A new vector.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPVector3D SPVector3DMakeWithSize(SPSize3D size)
__API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPVector3D SPVector3DMakeWithSize(SPSize3D size) {
    return (SPVector3D){ .vector = size.vector };
}

// MARK: - SPPoint3DMakeWithPoint

/*!
 @abstract Creates a vector with elements specified a coordinates of a point structure.
 
 @param point The source point.
 @returns A new vector.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPVector3D SPVector3DMakeWithPoint(SPPoint3D point)
__API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPVector3D SPVector3DMakeWithPoint(SPPoint3D point) {
    return (SPVector3D){ .vector = point.vector};
}

// MARK: - SPVector3DEqualToPoint

/// Returns @p true if both points are equal.
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
bool SPVector3DEqualToVector(SPVector3D vector1, SPVector3D vector2)
__API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
bool SPVector3DEqualToVector(SPVector3D vector1, SPVector3D vector2) {
    return simd_equal(vector1.vector, vector2.vector);
}

// MARK: - SPVector3DScaleBy

/*!
 @abstract Returns a vector with elements scaled by the specified values.
 
 @param vector The source vector.
 @param x The scale value for the @p x element.
 @param y The scale value for the @p y element.
 @param z The scale value for the @p z element.
 @returns A vector that's scaled by the specified values.
*/
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPVector3D SPVector3DScaleBy(SPVector3D vector, double x, double y, double z)
__API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPVector3D SPVector3DScaleBy(SPVector3D vector, double x, double y, double z) {
    
    return (SPVector3D){ .vector = vector.vector * simd_make_double3(x, y, z)};
}


// MARK: - SPVector3DApplyAffineTransform

/*!
 @abstract Returns a vector that's transformed by the specified affine transform.
 
 @param vector The source vector.
 @param transform The affine transform that the function applies to the vector.
 @returns The transformed vector.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPVector3D SPVector3DApplyAffineTransform(SPVector3D vector,
                                          SPAffineTransform3D transform)
__API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPVector3D SPVector3DApplyAffineTransform(SPVector3D vector,
                                          SPAffineTransform3D transform) {
    
    simd_double4 rhs = simd_make_double4(vector.vector, 0);
    
    simd_double3 transformed = simd_mul(transform.matrix, rhs).xyz;
    
    return (SPVector3D){ .vector = transformed };
}

// MARK: - SPVector3DApplyProjectiveTransform

/*!
 @abstract Returns a vector that's transformed by the specified projective transform.
 
 @param vector The source vector.
 @param transform The projective transform that the function applies to the vector.
 @returns The transformed vector.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPVector3D SPVector3DApplyProjectiveTransform(SPVector3D vector,
                                              SPProjectiveTransform3D transform)
__API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPVector3D SPVector3DApplyProjectiveTransform(SPVector3D vector,
                                              SPProjectiveTransform3D transform) {
    
    simd_double4 rhs = simd_make_double4(vector.vector, 0);
    
    simd_double3 transformed = simd_mul(transform.matrix, rhs).xyz;
    
    return (SPVector3D){ .vector = transformed };
}

// MARK: - SPVector3DUnapplyAffineTransform

/*!
 @abstract Returns a vector that's transformed by the inverse of the specified affine transform.
 
 @param vector The source vector.
 @param transform The affine transform whose inverse is to be applied to the vector.
 @returns The transformed vector.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPVector3D SPVector3DUnapplyAffineTransform(SPVector3D vector,
                                            SPAffineTransform3D transform)
__API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPVector3D SPVector3DUnapplyAffineTransform(SPVector3D vector,
                                            SPAffineTransform3D transform) {
    
    SPAffineTransform3D invertedTransform = SPAffineTransform3DInverted(transform);
    
    return SPVector3DApplyAffineTransform(vector, invertedTransform);
}

// MARK: - SPVector3DUnapplyProjectiveTransform

/*!
 @abstract Returns a vector that's transformed by the inverse of the specified projective transform.
 
 @param vector The source vector.
 @param transform The projective transform whose inverse is to be applied to the vector.
 @returns The transformed vector.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPVector3D SPVector3DUnapplyProjectiveTransform(SPVector3D vector,
                                                SPProjectiveTransform3D transform)
__API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPVector3D SPVector3DUnapplyProjectiveTransform(SPVector3D vector,
                                                SPProjectiveTransform3D transform) {
    
    SPProjectiveTransform3D invertedTransform = SPProjectiveTransform3DInverted(transform);
    
    return SPVector3DApplyProjectiveTransform(vector, invertedTransform);
}

// MARK: - SPVector3DRotationToVector

/*!
 @abstract Returns the rotation from the normalized first vector to the normalized second vector.
 
 @param vector The first vector.
 @param other The second vector.
 @returns A rotation structure that represents the rotation.
*/
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPRotation3D SPVector3DRotationToVector(SPVector3D vector, SPVector3D other)
__API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPRotation3D SPVector3DRotationToVector(SPVector3D vector, SPVector3D other) {
    
    simd_quatd quaternion = simd_quaternion(simd_normalize(vector.vector),
                                            simd_normalize(other.vector));
    
    return (SPRotation3D) { .quaternion = quaternion };
}

// MARK: - shear

/*!
 @abstract Returns a vector that's sheared over an axis by shear factors for the other two axes.
 
 @param vector The source vector.
 @param shearAxis The shear axis.
 @param shearFactor0 The first shear factor.
 @param shearFactor1 The second shear factor.
 @returns The transformed vector.
 @discussion
 When the shear axis is @p x , @p shearFactor0 is the @p y shear factor and @p shearFactor0 is the @p z shear factor.
 
 When the shear axis is @p y , @p shearFactor0 is the @p x  shear factor and @p shearFactor0 is the @p z shear factor.
 
 When the shear axis is @p z , @p shearFactor0 is the @p x  shear factor and @p shearFactor0 is the @p y shear factor.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPVector3D SPVector3DShear(SPVector3D vector,
                           SPAxis shearAxis,
                           double shearFactor0,
                           double shearFactor1)
__API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPVector3D SPVector3DShear(SPVector3D vector,
                           SPAxis shearAxis,
                           double shearFactor0,
                           double shearFactor1) {
    
    SPAffineTransform3D shearTransform = SPAffineTransform3DMakeShear(shearAxis,
                                                                      shearFactor0,
                                                                      shearFactor1);
    
    return SPVector3DApplyAffineTransform(vector, shearTransform);
}

// MARK: - SPVector3DScaleBySize

/*!
 @abstract Returns a vector with elements scaled by the specified size.
 
 @param vector The source vector.
 @param scale The scale value.
 @returns A vector that's scaled by the specified value.
*/
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPVector3D SPVector3DScaleBySize(SPVector3D vector, SPSize3D scale)
__API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPVector3D SPVector3DScaleBySize(SPVector3D vector, SPSize3D scale) {
    
    return (SPVector3D){ .vector = vector.vector * scale.vector };
}

// MARK: - SPVector3DScaleUniform

/*!
 @abstract Returns a vector with elements uniformly scaled by the specified value.
 
 @param vector The source vector.
 @param scale The scale value.
 @returns A vector that's uniformly scaled by the specified value.
*/
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPVector3D SPVector3DScaleUniform(SPVector3D vector, double scale)
__API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPVector3D SPVector3DScaleUniform(SPVector3D vector, double scale) {
    
    return (SPVector3D){ .vector = vector.vector * scale };
}

// MARK: - SPVector3DRotate

/*!
 @abstract Returns a vector that's rotated by the specified rotation around the origin.
 
 @param vector The source vector.
 @param rotation The rotation.
 @returns A vector that's rotated by the specified rotation.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPVector3D SPVector3DRotate(SPVector3D vector, SPRotation3D rotation)
__API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPVector3D SPVector3DRotate(SPVector3D vector, SPRotation3D rotation) {
    
    SPAffineTransform3D transform = SPAffineTransform3DMakeRotation(rotation);
    
    return SPVector3DApplyAffineTransform(vector, transform);
}

// MARK: - SPVector3DRotateByQuaternion

/*!
 @abstract Returns a vector that's rotated by the specified quaternion around the origin.
 
 @param vector The source vector.
 @param quaternion The quaternion that defines the rotation.
 @returns A vector that's rotated by the specified quaternion.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPVector3D SPVector3DRotateByQuaternion(SPVector3D vector, simd_quatd quaternion)
__API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPVector3D SPVector3DRotateByQuaternion(SPVector3D vector, simd_quatd quaternion) {
    
    SPRotation3D rotation = SPRotation3DMakeWithQuaternion(quaternion);
    
    return SPVector3DRotate(vector, rotation);
}

// MARK: - Geometry functions

/*!
 @abstract Returns the dot product of two vectors.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
double SPVector3DDotProduct(SPVector3D x, SPVector3D y)
__API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
double SPVector3DDotProduct(SPVector3D x, SPVector3D y) {
    
    double d = simd_dot(x.vector, y.vector);
    return d;
}

/*!
 @abstract Returns the cross product of two vectors.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPVector3D SPVector3DCrossProduct(SPVector3D x, SPVector3D y)
__API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPVector3D SPVector3DCrossProduct(SPVector3D x, SPVector3D y) {
    
    simd_double3 d = simd_cross(x.vector, y.vector);
    return (SPVector3D){ .vector = d };
}

/*!
 @abstract Returns a vector pointing in the same direction of the supplied vector with a length of 1.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPVector3D SPVector3DNormalize(SPVector3D x)
__API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPVector3D SPVector3DNormalize(SPVector3D x) {
    
    simd_double3 d = simd_normalize(x.vector);
    return (SPVector3D){ .vector = d };
}

/*!
 @abstract Returns the first vector projected onto the second vector.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPVector3D SPVector3DProject(SPVector3D x, SPVector3D y)
__API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPVector3D SPVector3DProject(SPVector3D x, SPVector3D y) {
    
    simd_double3 d = simd_project(x.vector, y.vector);
    return (SPVector3D){ .vector = d };
}

/*!
 @abstract Returns the reflection direction of an incident vector and a unit normal vector.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPVector3D SPVector3DReflect(SPVector3D x, SPVector3D y)
__API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPVector3D SPVector3DReflect(SPVector3D x, SPVector3D y) {
    
    simd_double3 d = simd_project(x.vector, y.vector);
    return (SPVector3D){ .vector = d };
}

/*!
 @abstract Returns the length of the vector.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
double SPVector3DLength(SPVector3D x)
__API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
double SPVector3DLength(SPVector3D x) {

    return simd_length(x.vector);
}

/*!
 @abstract Returns the squared length of the vector.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
double SPVector3DLengthSquared(SPVector3D x)
__API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
double SPVector3DLengthSquared(SPVector3D x) {

    return simd_length_squared(x.vector);
}

// MARK: - Transform by Pose

/*!
 @abstract Returns a vector that's transformed by the specified pose.
 
 @param vector The source vector.
 @param pose The pose that the function applies to the vector.
 @returns The transformed vector.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPVector3D SPVector3DApplyPose(SPVector3D vector,
                               SPPose3D pose)
__API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPVector3D SPVector3DApplyPose(SPVector3D vector,
                               SPPose3D pose) {
  
    simd_double3 transformed = simd_act(simd_normalize(pose.rotation.quaternion),
                                        vector.vector);
    
    return (SPVector3D){ .vector = transformed };
}

/*!
 @abstract Returns a vector that's transformed by the inverse of the specified pose.
 
 @param vector The source vector.
 @param pose The pose that the function unapplies to the vector.
 @returns The transformed vector.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPVector3D SPVector3DUnapplyPose(SPVector3D vector,
                                 SPPose3D pose)
__API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPVector3D SPVector3DUnapplyPose(SPVector3D vector,
                                 SPPose3D pose) {
    
    simd_double4 v = simd_make_double4(vector.vector, 0);
    simd_double4x4 m = simd_matrix4x4(pose.rotation.quaternion);
    m.columns[3].xyz = pose.position.vector;
    m = simd_inverse(m);
    
    simd_double3 transformed = simd_mul(m, v).xyz;
    
    return (SPVector3D){ .vector = transformed };
}

#endif /* SPVector3D_h */
