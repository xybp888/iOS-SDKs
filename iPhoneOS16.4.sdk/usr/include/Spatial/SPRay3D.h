#ifndef SPRay3D_h
#define SPRay3D_h

#include <Spatial/Structures.h>
#include <Spatial/SPPoint3D.h>
#include <Spatial/SPVector3D.h>
#include <Spatial/SPRect3D.h>

// MARK: - Public API

// MARK: - Creating a ray from Spatial primitives

/*!
 @abstract Returns a ray at the specified origin.
 
 @param origin A point structure that specifies the origin of the ray.
 @param direction A Spatial vector that specifies the direction of the ray.
 @note This function normalizes the direction vector.
 @returns A new ray stucture.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPRay3D SPRay3DMake(SPPoint3D origin,
                    SPVector3D direction)
__API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPRay3D SPRay3DMake(SPPoint3D origin,
                    SPVector3D direction) {
    
    return (SPRay3D){
        .origin = origin,
        .direction = SPVector3DNormalize(direction)
    };
    
}

// MARK: - Creating a ray from simd vectors

/*!
 @abstract Returns a ray at the specified origin.
 
 @param origin A point structure that specifies the origin of the ray.
 @param direction A Spatial vector that specifies the direction of the ray.
 @note This function normalizes the direction vector.
 @returns A new ray stucture.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPRay3D SPRay3DMakeWithVector(simd_double3 origin,
                              simd_double3 direction)
__API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPRay3D SPRay3DMakeWithVector(simd_double3 origin,
                              simd_double3 direction) {
    
    return (SPRay3D){
        .origin.vector = origin,
        .direction.vector = simd_normalize(direction)
    };
    
}

// MARK: - Comparing Rays

/// Returns @p true if both rays are equal.
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
bool SPRay3DEqualToRay(SPRay3D ray1, SPRay3D ray2)
__API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
bool SPRay3DEqualToRay(SPRay3D ray1, SPRay3D ray2) {
    
    return (
            SPPoint3DEqualToPoint(ray1.origin, ray2.origin) &&
            SPVector3DEqualToVector(ray1.direction, ray2.direction)
            );
}

// MARK: - Translation

/*!
 @abstract Returns a ray with an origin that is offset from that of the source ray.
 
 @param ray The source ray.
 @param offset A vector that defines the offset.
 @returns A ray that's offset by the @p x, @p y, and @p z of the vector.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPRay3D SPRay3DTranslate(SPRay3D ray, SPVector3D offset)
__API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0));

SPATIAL_SWIFT_NAME(Ray3D.translated(self:by:))
SPATIAL_OVERLOADABLE
SPRay3D SPRay3DTranslate(SPRay3D ray, SPVector3D offset) {
    
    SPRay3D r = SPRay3DMake(SPPoint3DTranslate(ray.origin, offset),
                            ray.direction);
    
    return r;
}

SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPRay3D SPRay3DTranslate(SPRay3D ray, SPSize3D offset)
__API_DEPRECATED("Use `SPVector3D` variant.",
                 macos(13.0, 13.0),
                 ios(16.0, 16.0),
                 watchos(9.0, 9.0),
                 tvos(16.0, 16.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPRay3D SPRay3DTranslate(SPRay3D ray, SPSize3D offset) {
    return SPRay3DTranslate(
                            ray,
                            (SPVector3D){ .vector = offset.vector }
                            );
}

// MARK: - Rotation

/*!
 @abstract Returns a ray that's rotated by the specified quaternion.

 @param ray The source ray.
 @param quaternion The quaternion that defines the rotation.
 @returns A ray with a direction that's rotated by the specified quaternion.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPRay3D SPRay3DRotateByQuaternion(SPRay3D ray, simd_quatd quaternion)
__API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPRay3D SPRay3DRotateByQuaternion(SPRay3D ray, simd_quatd quaternion) {
    
    SPPoint3D origin = SPPoint3DRotateByQuaternion(ray.origin, quaternion);
    SPVector3D direction = SPVector3DRotateByQuaternion(ray.direction, quaternion);

    SPRay3D r = SPRay3DMake(origin, direction);
    
    return r;
}

/*!
 @abstract Returns a ray that's rotated by the specified rotation.

 @param ray The source ray.
 @param rotation The rotation.
 @returns A ray with a direction that's rotated by the specified quaternion.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPRay3D SPRay3DRotate(SPRay3D ray, SPRotation3D rotation)
__API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPRay3D SPRay3DRotate(SPRay3D ray, SPRotation3D rotation) {
    
    return SPRay3DRotateByQuaternion(ray, rotation.quaternion);
}

/*!
 @abstract Returns a ray that's transformed by the specified pose.
 
 @param ray The source ray.
 @param pose The pose that the function applies to the ray.
 @returns The transformed ray.
 @note This function rotates the ray's direction by the pose's rotation and offsets the ray's origin
 by the pose's position.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPRay3D SPRay3DApplyPose(SPRay3D ray,
                               SPPose3D pose)
__API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPRay3D SPRay3DApplyPose(SPRay3D ray,
                               SPPose3D pose) {
    
    ray = SPRay3DRotate(ray, pose.rotation);
    ray = SPRay3DTranslate(ray, (SPVector3D){ .vector = pose.position.vector});
    
    return ray;
}

// MARK: - Test for intersection with rectangle

/*!
 @abstract Returns a Boolean value that indicates whether the ray intersects a specified rectangle.

 @param ray The ray.
 @param rect The rectangle.
 @returns A  Boolean value that indicates whether the ray intersects a specified rectangle.
 */
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
bool SPRay3DIntersectsRect(SPRay3D ray, SPRect3D rect)
__API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
bool SPRay3DIntersectsRect(SPRay3D ray, SPRect3D rect) {
    
    simd_double3 direction = ray.direction.vector;
    simd_double3 origin = ray.origin.vector;
    
    simd_double3 invDirection = 1.0 / direction;
    
    simd_double3 bounds[] = {
        SPRect3DGetMinimum(rect).vector,
        SPRect3DGetMaximum(rect).vector,
    };
    
    simd_int3 sign = {
        invDirection.x < 0 ? 1 : 0,
        invDirection.y < 0 ? 1 : 0,
        invDirection.z < 0 ? 1 : 0
    };
    
    double tx0 = (bounds[  sign.x].x - origin.x) * invDirection.x;
    double tx1 = (bounds[1-sign.x].x - origin.x) * invDirection.x;
    double ty0 = (bounds[  sign.y].y - origin.y) * invDirection.y;
    double ty1 = (bounds[1-sign.y].y - origin.y) * invDirection.y;
    double tz0 = (bounds[  sign.z].z - origin.z) * invDirection.z;
    double tz1 = (bounds[1-sign.z].z - origin.z) * invDirection.z;
    
    double tmin = fmax(fmax(fmin(tx0, tx1), fmin(ty0, ty1)), fmin(tz0, tz1));
    double tmax = fmin(fmin(fmax(tx0, tx1), fmax(ty0, ty1)), fmax(tz0, tz1));
    
    return tmax >= tmin;
}

#endif /* SPRay3D_h */
