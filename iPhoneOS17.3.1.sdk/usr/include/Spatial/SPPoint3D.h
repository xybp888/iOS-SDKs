#ifndef Spatial_SPPoint3D_h
#define Spatial_SPPoint3D_h

#include <Spatial/Structures.h>
#include <Spatial/SPProjectiveTransform3D.h>
#include <Spatial/SPAffineTransform3D.h>

// MARK: - Public API

/*!
 @abstract Creates a point with the specified coordinates.
 
 @param x The x coordinate.
 @param y The y coordinate.
 @param z The z coordinate.
 @returns A new point.
*/
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPPoint3D SPPoint3DMake(double x, double y, double z)
__API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0));

/*!
 @abstract Creates a point with coordinates specified as a 3-element SIMD vector.
 
 @param xyz The source vector.
 @returns A new point.
*/
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPPoint3D SPPoint3DMakeWithVector(simd_double3 xyz)
__API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0));

/*!
 @abstract Creates a point with coordinates specified as a Spatial vector.
 
 @param xyz The source vector.
 @returns A new point.
*/
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPPoint3D SPPoint3DMakeWithVector(SPVector3D xyz)
__API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0));


/*!
 @abstract Creates a point with coordinates specified as a dimensions of a size structure.
 
 @param size The source size.
 @returns A new point.
*/
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPPoint3D SPPoint3DMakeWithSize(SPSize3D size)
__API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0));

/*!
 @abstract Returns a point that's rotated by the specified quaternion around the origin.
 
 @param point The source point.
 @param quaternion The quaternion that defines the rotation.
 @returns A point that's rotated by the specified rotation.
 @discussion This function is equivalent to calling @p SPPoint3DRotateByQuaternionAroundPoint with a zero vector for the pivot.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPPoint3D SPPoint3DRotateByQuaternion(SPPoint3D point, simd_quatd quaternion)
__API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0));

/*!
 @abstract Returns a point that's rotated by the specified rotation around the origin.
 
 @param point The source point.
 @param rotation The rotation.
 @returns A point that's rotated by the specified rotation.
 @discussion This function is equivalent to calling @p SPPoint3DRotateAroundPoint with a zero vector
 for the pivot.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPPoint3D SPPoint3DRotate(SPPoint3D point, SPRotation3D rotation)
__API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0));

/*!
 @abstract Returns a point that's rotated by a rotation around a specified pivot.
 
 @param point The source point.
 @param rotation The rotation.
 @param pivot The center of rotation.
 @returns A point that's rotated by the specified rotation.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPPoint3D SPPoint3DRotateAroundPoint(SPPoint3D point, SPRotation3D rotation, SPPoint3D pivot)
__API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0));

/*!
 @abstract Returns a point that's rotated by a quaternion around a specified pivot.
 
 @param point The source point.
 @param quaternion The quaternion that defines the rotation.
 @param pivot The center of rotation.
 @returns A point that's rotated by the specified rotation.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPPoint3D SPPoint3DRotateByQuaternionAroundPoint(SPPoint3D point, simd_quatd quaternion, SPPoint3D pivot)
__API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0));

/*!
 @abstract Returns a point with an origin that is offset from that of the source point.
 
 @param point The source point.
 @param offset A size structure that defines the offset.
 @returns A point that's offset by the @p width, @p height, and @p depth of the size.
*/
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPPoint3D SPPoint3DTranslate(SPPoint3D point, SPSize3D offset)
__API_DEPRECATED("Use `SPVector3D` variant.",
                 macos(13.0, 13.0),
                 ios(16.0, 16.0),
                 watchos(9.0, 9.0),
                 tvos(16.0, 16.0));

/*!
 @abstract Returns a point with an origin that is offset from that of the source point.
 
 @param point The source point.
 @param offset A vector that defines the offset.
 @returns A point that's offset by the @p x, @p y, and @p z of the vector.
*/
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPPoint3D SPPoint3DTranslate(SPPoint3D point, SPVector3D offset)
__API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0));

/*!
 @abstract Returns the position of the entity's origin.
 
 @param point The source point.
 @returns For point structures, this function returns a point that's identical to the source point.
*/
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPPoint3D SPPoint3DGetOrigin(SPPoint3D point)
__API_DEPRECATED("This function is deprecated.",
                 macos(13.0, 13.0),
                 ios(16.0, 16.0),
                 watchos(9.0, 9.0),
                 tvos(16.0, 16.0));

/*!
 @abstract Returns the distance between the origins of two points.
 
 @param point The first point.
 @param other The second point.
 @returns The distance between the two points.
*/
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
double SPPoint3DDistanceToPoint(SPPoint3D point, SPPoint3D other)
__API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0));

/*!
 @abstract Returns the rotation around @p (0,0,0)  from the normalized first point to the normalized second point.
 
 @param point The first point.
 @param other The second point.
 @returns A rotation structure that represents the rotation.
*/
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPRotation3D SPPoint3DRotationToPoint(SPPoint3D point, SPPoint3D other)
__API_DEPRECATED("Use `SPVector3DRotationToVector`.",
                 macos(13.0, 14.0),
                 ios(16.0, 17.0),
                 watchos(9.0, 10.0),
                 tvos(16.0, 17.0));

/*!
 @abstract Returns the @p x, @p y, and @p z components of the point expressed as a simd vector.
 
 @param point The source point.
 @returns A vector that represents the point.
*/
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
simd_double3 SPPoint3DGetVector(SPPoint3D point)
__API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0));

/*!
 @abstract Returns a point that's transformed by the specified affine transform.
 
 @param point The source point.
 @param transform The affine transform that the function applies to the point.
 @returns The transformed point,
*/
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPPoint3D SPPoint3DApplyAffineTransform(SPPoint3D point,
                                        SPAffineTransform3D transform)
__API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0));

/*!
 @abstract Returns a point that's transformed by the specified projective transform.
 
 @param point The source point.
 @param transform The projective transform that the function applies to the point.
 @returns The transformed point.
*/
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPPoint3D SPPoint3DApplyProjectiveTransform(SPPoint3D point,
                                            SPProjectiveTransform3D transform)
__API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0));

/*!
 @abstract Returns a point that's transformed by the inverse of the specified affine transform.
 
 @param point The source point.
 @param transform The affine transform that the function unapplies to the point.
 @returns The transformed point.
*/
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPPoint3D SPPoint3DUnapplyAffineTransform(SPPoint3D point,
                                          SPAffineTransform3D transform)
__API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0));

/*!
 @abstract Returns a point that's transformed by the inverse of the specified projective transform.
 
 @param point The source point.
 @param transform The projective transform that the function unapplies to the point.
 @returns The transformed point.
*/
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPPoint3D SPPoint3DUnapplyProjectiveTransform(SPPoint3D point,
                                              SPProjectiveTransform3D transform)
__API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0));

/// Returns @p true if both points are equal.
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
bool SPPoint3DEqualToPoint(SPPoint3D point1, SPPoint3D point2)
__API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0));

// MARK: - Header inline implementations

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
simd_double3 SPPoint3DGetVector(SPPoint3D point) {
    return point.vector;
}

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPPoint3D SPPoint3DMake(double x, double y, double z) {
    return (SPPoint3D){ .x = x, .y = y, .z = z };
}

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPPoint3D SPPoint3DMakeWithVector(simd_double3 xyz) {
    return (SPPoint3D){ .vector = xyz};
}

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPPoint3D SPPoint3DMakeWithVector(SPVector3D xyz) {
    return (SPPoint3D){ .vector = xyz.vector};
}

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPPoint3D SPPoint3DMakeWithSize(SPSize3D size) {
    return (SPPoint3D){ .vector = size.vector};
}

SPATIAL_SWIFT_NAME(Point3D.rotated(self:by:))
SPATIAL_OVERLOADABLE
SPPoint3D SPPoint3DRotate(SPPoint3D point, SPRotation3D rotation) {
    
    SPAffineTransform3D transform = SPAffineTransform3DMakeRotation(rotation);
    
    return SPPoint3DApplyAffineTransform(point, transform);
}

SPATIAL_SWIFT_NAME(Point3D.rotated(self:by:around:))
SPATIAL_OVERLOADABLE
SPPoint3D SPPoint3DRotateAroundPoint(SPPoint3D point, SPRotation3D rotation, SPPoint3D pivot) {
    
    SPAffineTransform3D transform = SPAffineTransform3DMakeRotation(rotation);
    
    point = (SPPoint3D){ .vector = point.vector - pivot.vector } ;
    point = SPPoint3DApplyAffineTransform(point, transform);
    
    return (SPPoint3D){ .vector = point.vector + pivot.vector } ;
}

SPATIAL_SWIFT_NAME(Point3D.rotated(self:by:))
SPATIAL_OVERLOADABLE
SPPoint3D SPPoint3DRotateByQuaternion(SPPoint3D point, simd_quatd quaternion) {
    
    SPRotation3D rotation = SPRotation3DMakeWithQuaternion(quaternion);
    
    
    return SPPoint3DRotate(point, rotation);
}

SPATIAL_SWIFT_NAME(Point3D.rotated(self:by:around:))
SPATIAL_OVERLOADABLE
SPPoint3D SPPoint3DRotateByQuaternionAroundPoint(SPPoint3D point, simd_quatd quaternion, SPPoint3D pivot) {
    
    SPRotation3D rotation = SPRotation3DMakeWithQuaternion(quaternion);
    
    
    return SPPoint3DRotateAroundPoint(point, rotation, pivot);
}

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPPoint3D SPPoint3DTranslate(SPPoint3D point, SPSize3D offset) {
    
    return (SPPoint3D) { .vector = point.vector + offset.vector};
}

SPATIAL_SWIFT_NAME(Point3D.translated(self:by:))
SPATIAL_OVERLOADABLE
SPPoint3D SPPoint3DTranslate(SPPoint3D point, SPVector3D offset) {
    
    return (SPPoint3D) { .vector = point.vector + offset.vector};
}

SPATIAL_SWIFT_NAME(Point3D.rotation(self:to:))
SPATIAL_OVERLOADABLE
SPRotation3D SPPoint3DRotationToPoint(SPPoint3D point, SPPoint3D other) {
    
    simd_quatd quaternion = simd_quaternion(simd_normalize(point.vector),
                                            simd_normalize(other.vector));

    return (SPRotation3D) { .quaternion = quaternion };
}

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPPoint3D SPPoint3DGetOrigin(SPPoint3D point) {
    return point;
}

SPATIAL_SWIFT_NAME(Point3D.distance(self:to:))
SPATIAL_OVERLOADABLE
double SPPoint3DDistanceToPoint(SPPoint3D point, SPPoint3D other) {
    return simd_distance(point.vector, other.vector);
}

SPATIAL_SWIFT_NAME(Point3D.unapplying(self:_:))
SPATIAL_OVERLOADABLE
SPPoint3D SPPoint3DUnapplyAffineTransform(SPPoint3D point, SPAffineTransform3D transform) {
    SPAffineTransform3D invertedTransform = SPAffineTransform3DInverted(transform);
    
    return SPPoint3DApplyAffineTransform(point, invertedTransform);
}

SPATIAL_SWIFT_NAME(Point3D.unapplying(self:_:))
SPATIAL_OVERLOADABLE
SPPoint3D SPPoint3DUnapplyProjectiveTransform(SPPoint3D point, SPProjectiveTransform3D transform) {
    SPProjectiveTransform3D invertedTransform = SPProjectiveTransform3DInverted(transform);
    
    return SPPoint3DApplyProjectiveTransform(point, invertedTransform);
}

SPATIAL_SWIFT_NAME(Point3D.applying(self:_:))
SPATIAL_OVERLOADABLE
SPPoint3D SPPoint3DApplyAffineTransform(SPPoint3D point, SPAffineTransform3D transform) {
 
    simd_double4 rhs = simd_make_double4(point.vector, 1);
    
    simd_double3 transformed = simd_mul(transform.matrix, rhs).xyz;
    
    return (SPPoint3D){ .vector = transformed };
}

SPATIAL_SWIFT_NAME(Point3D.applying(self:_:))
SPATIAL_OVERLOADABLE
SPPoint3D SPPoint3DApplyProjectiveTransform(SPPoint3D point, SPProjectiveTransform3D transform) {

    simd_double4 rhs = simd_make_double4(point.vector, 1);
    
    simd_double3 transformed = simd_mul(transform.matrix, rhs).xyz;
    
    return (SPPoint3D){ .vector = transformed };
}

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
bool SPPoint3DEqualToPoint(SPPoint3D point1, SPPoint3D point2) {
    return simd_equal(point1.vector, point2.vector);
}

// MARK: - Transform by Pose

/*!
 @abstract Returns a point that's transformed by the specified pose.
 
 @param point The source point.
 @param pose The pose that the function applies to the point.
 @returns The transformed point.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPPoint3D SPPoint3DApplyPose(SPPoint3D point,
                             SPPose3D pose)
__API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPPoint3D SPPoint3DApplyPose(SPPoint3D point,
                             SPPose3D pose) {
    
    simd_double4 v = simd_make_double4(point.vector, 1);
    simd_double4x4 m = simd_matrix4x4(pose.rotation.quaternion);
    m.columns[3].xyz = pose.position.vector;
    
    simd_double3 transformed = simd_mul(m, v).xyz;
    
    return (SPPoint3D){ .vector = transformed };
}

/*!
 @abstract Returns a point that's transformed by the inverse of the specified pose.
 
 @param point The source point.
 @param pose The pose that the function unapplies to the point.
 @returns The transformed point.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPPoint3D SPPoint3DUnapplyPose(SPPoint3D point,
                               SPPose3D pose)
__API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPPoint3D SPPoint3DUnapplyPose(SPPoint3D point,
                               SPPose3D pose) {
    
    simd_double4 v = simd_make_double4(point.vector, 1);
    simd_double4x4 m = simd_matrix4x4(pose.rotation.quaternion);
    m.columns[3].xyz = pose.position.vector;
    m = simd_inverse(m);
    
    simd_double3 transformed = simd_mul(m, v).xyz;
    
    return (SPPoint3D){ .vector = transformed };
}

#endif /* Spatial_SPPoint3D_h */
