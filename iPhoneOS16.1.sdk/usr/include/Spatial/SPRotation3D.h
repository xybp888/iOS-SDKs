#ifndef Spatial_SPRotation3D_h
#define Spatial_SPRotation3D_h

#include <Spatial/Structures.h>
#include <Spatial/SPRotationAxis3D.h>
#include <Spatial/SPAngle.h>
#include <math.h>

// MARK: - Public API

/*!
 @abstract Returns a rotation over the specified axis with the specified angle.
 
 @param axis The axis of the rotation.
 @param angle The angle of the rotation.
 @returns A new rotation stucture.
*/
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPRotation3D SPRotation3DMake(SPRotationAxis3D axis, SPAngle angle)
__API_DEPRECATED("Use `SPRotation3DMake(SPAngle angle, SPRotationAxis3D axis)`.",
                 macos(13.0, 13.0),
                 ios(16.0, 16.0),
                 watchos(9.0, 9.0),
                 tvos(16.0, 16.0));

/*!
 @abstract Returns a rotation over the specified axis with the specified angle.
 
 @param angle The angle of the rotation.
 @param axis The axis of the rotation.
 @returns A new rotation stucture.
*/
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPRotation3D SPRotation3DMake(SPAngle angle, SPRotationAxis3D axis)
__API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0));

/*!
 @abstract  Returns the rotation represented as a normalized quaternion.
 
 @param rotation The source rotation.
 @returns A quaternion with an axis and angle derived from the source rotation.
*/
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
simd_quatd SPRotation3DGetQuaternion(SPRotation3D rotation)
__API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0));

/*!
 @abstract Returns a rotation from the specified quaternion.
 
 @param quaternion The source quaternion.
 @returns A new rotation stucture.
*/
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPRotation3D SPRotation3DMakeWithQuaternion(simd_quatd quaternion)
__API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0));

/// Returns @p true if both rotations are equal.
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
bool SPRotation3DEqualToRotation(SPRotation3D rotation1, SPRotation3D rotation2)
__API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0));

// MARK: - Header inline implementations

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPRotation3D SPRotation3DMakeWithQuaternion(simd_quatd quaternion) {
  
    return (SPRotation3D) { .quaternion = quaternion };
}

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPRotation3D SPRotation3DMake(SPRotationAxis3D axis, SPAngle angle) {

    simd_quatd q = simd_quaternion(angle.radians, axis.vector);
    
    return (SPRotation3D){
        .quaternion = q
    };
}

SPATIAL_SWIFT_NAME(Rotation3D.init(angle:axis:))
SPATIAL_OVERLOADABLE
SPRotation3D SPRotation3DMake(SPAngle angle, SPRotationAxis3D axis) {

    simd_quatd q = simd_quaternion(angle.radians, axis.vector);
    
    return (SPRotation3D){
        .quaternion = q
    };
}

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
simd_quatd SPRotation3DGetQuaternion(SPRotation3D rotation) {
    return rotation.quaternion;
}

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
bool SPRotation3DEqualToRotation(SPRotation3D rotation1, SPRotation3D rotation2) {
    
    return simd_equal(rotation1.quaternion.vector, rotation2.quaternion.vector) ||
    simd_equal(rotation1.quaternion.vector, simd_negate(rotation2.quaternion).vector);
}


// MARK: - Look At

/*!
 @abstract Returns a rotation that's the look at direction from the position position to the target.
 
 @param position The eye position.
 @param target The point that the rotation looks at.
 @param up The up direction.
 @returns A new rotation stucture.
 @note This function creates a rotation where @p +z is forward.
*/
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPRotation3D SPRotation3DMakeLookAt(SPPoint3D position, SPPoint3D target, SPVector3D up)
__API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPRotation3D SPRotation3DMakeLookAt(SPPoint3D position, SPPoint3D target, SPVector3D up) {
    
    simd_double3 axisZ = simd_normalize(target.vector - position.vector);
    simd_double3 axisX = simd_normalize(simd_cross(axisZ, simd_normalize(up.vector)));
    simd_double3 axisY = simd_normalize(simd_cross(axisX, axisZ));
    
    simd_double3x3 m = simd_matrix(-axisX, axisY, axisZ);
    simd_quatd q = simd_normalize(simd_quaternion(m));
    
    return SPRotation3DMakeWithQuaternion(q);
}

/*!
 @abstract Returns a rotation that's the look at direction from the origin to the target.
 
 @param target The point that the rotation looks at.
 @param up The up direction.
 @returns A new rotation stucture.
 @note This function creates a rotation where @p +z is forward.
*/
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPRotation3D SPRotation3DMakeLookAt(SPPoint3D target, SPVector3D up)
__API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPRotation3D SPRotation3DMakeLookAt(SPPoint3D target, SPVector3D up) {
 
    SPPoint3D position = (SPPoint3D){ .x = 0, .y = 0, .z = 0 };
    
    return SPRotation3DMakeLookAt(position, target, up);
}

/*!
 @abstract Returns a rotation with the specified forward and up vectors.
 
 @param forward The forward direction.
 @param up The up direction.
 @returns A new rotation stucture.
 @note This function creates a rotation where @p +z is forward.
*/
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPRotation3D SPRotation3DMakeLookAt(SPVector3D forward, SPVector3D up)
__API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0));

SPATIAL_SWIFT_NAME(Rotation3D.init(forward:up:))
SPATIAL_OVERLOADABLE
SPRotation3D SPRotation3DMakeLookAt(SPVector3D forward, SPVector3D up) {
 
    SPPoint3D position = (SPPoint3D){ .x = 0, .y = 0, .z = 0 };
    
    SPPoint3D target = (SPPoint3D) { .vector = forward.vector };
    
    return SPRotation3DMakeLookAt(position, target, up);
}

// MARK: EULER headers

/*!
 @abstract Constants that specify the Euler angle order.
*/
typedef enum: uint32_t {
    /*!
     @abstract Pitch-Yaw-Roll
     
     @discussion
     The order of components in the vector matches the axes of rotation:
     
     Pitch (the @p x component) is the rotation about the node's x-axis.
     
     Yaw (the @p y component) is the rotation about the node's y-axis.
     
     Roll (the @p z component) is the rotation about the node's z-axis.
     
     Spatial applies these rotations in the reverse order of the components: first roll, then yaw, then pitch.
     */
    SPEulerPitchYawRoll SPATIAL_REFINED_FOR_SWIFT __API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0)) = 0x0001,
} SPEulerAngleOrder
SPATIAL_REFINED_FOR_SWIFT
__API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0));

/*!
 @abstract A structure that represents Euler angles and ordering.
*/
typedef struct {
    simd_double3 angles;
    SPEulerAngleOrder order;
} SPEulerAngles
SPATIAL_SWIFT_NAME(EulerAngles)
__API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0));

/*!
 @abstract Returns a rotation structure from the specified Euler angles.
 
 @param eulerAngles The source Euler angles.
 @returns A rotation structure.
*/
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPRotation3D SPRotation3DMakeWithEulerAngles(SPEulerAngles eulerAngles)
__API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0));

/*!
 @abstract Returns the Euler angles from the specified rotation structure.
 
 @param rotation The source rotation structure.
 @param order The Euler angle ordering.
 @returns A rotation structure.
*/
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPEulerAngles SPRotation3DGetEulerAngles(SPRotation3D rotation, SPEulerAngleOrder order)
__API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0));


SPATIAL_SWIFT_NAME(Rotation3D.init(eulerAngles:))
SPATIAL_OVERLOADABLE
SPRotation3D SPRotation3DMakeWithEulerAngles(SPEulerAngles eulerAngles) {
    
    SPEulerAngleOrder order = eulerAngles.order;
    
    if (order != SPEulerPitchYawRoll) {
        return SPRotation3DInvalid;
    }

    simd_double3 halves = (simd_double3){0.5, 0.5, 0.5} * eulerAngles.angles;
    simd_double3 cosines = _sp_simd_cos(halves).xyz;
    simd_double3 sines = _sp_simd_sin(halves).xyz;
    
    double cr = cosines.x;
    double cp = cosines.y;
    double cy = cosines.z;
    
    double sr = sines.x;
    double sp = sines.y;
    double sy = sines.z;
    
    double cpcy = cp * cy;
    double spsy = sp * sy;
    
    simd_double4 v = (simd_double4){
        sr * cpcy - cr * spsy,
        cr * sp * cy + sr * cp * sy,
        cr * cp * sy - sr * sp * cy,
        cr * cpcy + sr * spsy
    };
    
    return SPRotation3DMakeWithQuaternion(simd_quaternion(v));
}

SPATIAL_SWIFT_NAME(Rotation3D.eulerAngles(self:order:))
SPATIAL_OVERLOADABLE
SPEulerAngles SPRotation3DGetEulerAngles(SPRotation3D rotation, SPEulerAngleOrder order) {
    
    if (order != SPEulerPitchYawRoll) {
        return (SPEulerAngles){ { NAN, NAN, NAN }, order};
    }
    
    simd_double4 qv = SPRotation3DGetQuaternion(rotation).vector;
    simd_double4 sqv = qv * qv;
    
    double unit = simd_reduce_add(sqv);
    simd_double3 e = (simd_double3){ 0, 0, 0};
    
    if (fabs(unit) < SPDefaultTolerance) {
        return (SPEulerAngles){ e, order };
    }
    
    double test = (qv.x * qv.z - qv.y * qv.w) / unit;
    double limit = 5 - SPDefaultTolerance;

    if (test > limit) { // singularity at north pole
        e.x = 2 * atan2(qv.x, qv.w);
        e.y = M_PI * 0.5;
        e.z = 0;
        return  (SPEulerAngles){ e, order };
    }
    if (test < -limit) { // singularity at south pole
        e.x = -2 * atan2(qv.x, qv.w);
        e.y = -M_PI * 0.5;
        e.z = 0;
        return (SPEulerAngles){ e, order };
    }

    e.z = atan2(2 * (qv.x * qv.y + qv.z * qv.w), ( sqv.x - sqv.y - sqv.z + sqv.w));
    e.x = atan2(2 * (qv.y * qv.z + qv.x * qv.w), (-sqv.x - sqv.y + sqv.z + sqv.w));
    e.y = asin(-2 * test);
    return (SPEulerAngles){ e, order };

}

// MARK: - Angle and axis components of the angle and axis form.

/*!
 @abstract Returns the angle, in radians, of the normalized underlying quaternion.
 
 @param rotation The source rotation.
 @returns An angle structure.
*/
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPAngle SPRotation3DGetAngle(SPRotation3D rotation)
__API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPAngle SPRotation3DGetAngle(SPRotation3D rotation) {
    
    double radians = simd_angle(rotation.quaternion);
    
    return SPAngleMakeWithRadians(radians);
}

/*!
 @abstract Sets the angle on the specified rotation structure.
 
 @param rotation A pointer to the rotation structure.
 @param angle The angle structure.
 */

SPATIAL_INLINE
SPATIAL_OVERLOADABLE
void SPRotation3DSetAngle(SPRotation3D *rotation, SPAngle angle)
__API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
void SPRotation3DSetAngle(SPRotation3D *rotation, SPAngle angle) {
    
    simd_double3 axis = simd_axis(rotation->quaternion);
    
    simd_quatd quaternion = simd_quaternion(angle.radians, axis);
    
    rotation->quaternion = quaternion;
}

/*!
 @abstract Returns the axis of the normalized underlying quaternion.
 
 @param rotation The source rotation.
 @returns An angle structure.
*/
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
SPRotationAxis3D SPRotation3DGetAxis(SPRotation3D rotation)
__API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
SPRotationAxis3D SPRotation3DGetAxis(SPRotation3D rotation) {
    
    simd_double3 axis = simd_axis(rotation.quaternion);
    
    return SPRotationAxis3DMakeWithVector(axis);
}


/*!
 @abstract Sets the axis on the specified rotation structure.
 
 @param rotation A pointer to the rotation structure.
 @param axis The axis structure.
 */

SPATIAL_INLINE
SPATIAL_OVERLOADABLE
void SPRotation3DSetAxis(SPRotation3D *rotation, SPRotationAxis3D axis)
__API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
void SPRotation3DSetAxis(SPRotation3D *rotation, SPRotationAxis3D axis) {
    
    double angle = simd_angle(rotation->quaternion);
    
    simd_quatd quaternion = simd_quaternion(angle, axis.vector);
    
    rotation->quaternion = quaternion;
}

/*!
 @abstract Returns a Boolean value that indicates whether the rotation's angle is zero.
 
 @param rotation The source rotation.
 @returns A Boolean value that indicates whether the rotation is zero.
*/
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
bool SPRotation3DIsZero(SPRotation3D rotation)
__API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0));

SPATIAL_SWIFT_NAME(getter:Rotation3D.isZero(self:))
SPATIAL_OVERLOADABLE
bool SPRotation3DIsZero(SPRotation3D rotation) {

    SPAngle angle = SPRotation3DGetAngle(rotation);
    
    return angle.radians == 0;
}

#endif /* Spatial_SPRotation3D_h */

