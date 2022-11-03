#ifndef Spatial_Structures_h
#define Spatial_Structures_h
#include <Spatial/Base.h>
#include <simd/simd.h>
#include <stdbool.h>

// MARK: - SPAngle Structure

/// A geometric angle whose value you access in either radians or degrees.
typedef struct {
    /// The angle in radians.
    double radians;
} SPAngle
SPATIAL_SWIFT_NAME(Angle2D)
__API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0));

// MARK: - Axis Structure

/// A 3D axis.
typedef
union {
    struct {
        /// The x-axis value.
        SPATIAL_REFINED_FOR_SWIFT
        double x;
        
        /// The y-axis value.
        SPATIAL_REFINED_FOR_SWIFT
        double y;
        
        /// The z-axis value.
        SPATIAL_REFINED_FOR_SWIFT
        double z;
    };
    simd_double3 vector;
} SPRotationAxis3D
__attribute__((__aligned__(16)))
SPATIAL_SWIFT_NAME(RotationAxis3D)
__API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0));

// MARK: - Rotation Structure

/// A structure that represents a rotation in three dimensions.
typedef
union {
    struct {
        /// The underlying vector of the quaternion..
        simd_double4 vector;
    };
    simd_quatd quaternion;
} SPRotation3D
__attribute__((__aligned__(16)))
SPATIAL_SWIFT_NAME(Rotation3D)
__API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0));

// MARK: - 3D Point Structure

/// A structure that contains a point in a three-dimensional coordinate system.
typedef
union {
    struct {
        /// The x-coordinate of the point.
        double x;
        
        /// The y-coordinate of the point.
        double y;
        
        /// The z-coordinate of the point.
        double z;
    };
    simd_double3 vector;
} SPPoint3D
__attribute__((__aligned__(16)))
SPATIAL_SWIFT_NAME(Point3D)
__API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0));

// MARK: - 3D Vector Structure

/// A structure that defines a three-element vector
typedef
union {
    struct {
        /// The first element of the vector.
        double x;
        
        /// The second element of the vector.
        double y;
        
        /// The third element of the vector.
        double z;
    };
    simd_double3 vector;
} SPVector3D
__attribute__((__aligned__(16)))
SPATIAL_SWIFT_NAME(Vector3D)
__API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0));

// MARK: - 3D Size Structure

/// A structure that contains width, height, and depth values.
typedef
union {
    struct {
        /// The width of the size.
        double width;
        
        /// The height of the size.
        double height;
        
        /// The depth of the size.
        double depth;
    };
    simd_double3 vector;
} SPSize3D
__attribute__((__aligned__(16)))
SPATIAL_SWIFT_NAME(Size3D)
__API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0));

// MARK: - 3D Rectangle Structure

/// A structure that contains the location and dimensions of a 3D rectangle.
typedef struct {
    /// The origin of the rectangle.
    SPPoint3D origin;
    
    /// The size of the rectangle.
   SPSize3D size;
} SPRect3D
SPATIAL_SWIFT_NAME(Rect3D)
__API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0));

// MARK: - 3D Ray Structure

/// A structure that contains the origin and direction of a 3D ray.
typedef struct {
    /// The origin of the ray.
    SPPoint3D origin;
    
    /// The direction of the ray.
    SPVector3D direction;
} SPRay3D
SPATIAL_SWIFT_NAME(Ray3D)
__API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0));

// MARK: - 3D Pose Structure

/// A structure that contains a position and rotation.
typedef struct {
    /// The position
    SPPoint3D position;
    
    /// The rotation
    SPRotation3D rotation;
} SPPose3D
SPATIAL_SWIFT_NAME(Pose3D)
__API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0));

// MARK: - 3D Affine Transform Structure

/*!
 @abstract A 3D affine transformation matrix.
 
 @field matrix The 4x3 matrix that describes the affine transfrom.
 */
typedef struct {
    simd_double4x3 matrix;
} SPAffineTransform3D
SPATIAL_SWIFT_NAME(AffineTransform3D)
__API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0));

// MARK: - 3D Projective Transform Structure

/// A 3D projective transformation matrix.
typedef struct {
    simd_double4x4 matrix;
} SPProjectiveTransform3D
SPATIAL_SWIFT_NAME(ProjectiveTransform3D)
__API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0));

// MARK: - Shear enumeration

/// Enumerations that describe an axis.
typedef enum : uint32_t {
    
    /// The operation is along the x-axis.
    SPAxisX SPATIAL_REFINED_FOR_SWIFT __API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0)) = 0x0001,
    
    /// The operation is along the y-axis.
    SPAxisY SPATIAL_REFINED_FOR_SWIFT __API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0)) = 0x0002,
    
    /// The operation is along the z-axis.
    SPAxisZ SPATIAL_REFINED_FOR_SWIFT __API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0)) = 0x0004
 
}
SPAxis
SPATIAL_SWIFT_NAME(Axis3D);


// MARK: - Special Values

/// The angle with the value zero.
__API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0))
SPATIAL_SWIFT_NAME(Angle2D.zero)
static const SPAngle SPAngleZero  = { 0 };

/// The axis whose x, y, and z values are all zero.
__API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0))
SPATIAL_SWIFT_NAME(RotationAxis3D.zero)
static const SPRotationAxis3D SPRotationAxis3DZero = { 0 };

/// The rotation with an angle of zero.
__API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0))
SPATIAL_SWIFT_NAME(Rotation3D.zero)
static const SPRotation3D SPRotation3DZero = { 0 };

/// A rotation that represents an invalid rotation.
__API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0))
SPATIAL_REFINED_FOR_SWIFT
static const SPRotation3D SPRotation3DInvalid = {
    { .vector = {INFINITY, INFINITY, INFINITY, INFINITY }}
};

/// A pose that represents an invalid pose.
__API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0))
SPATIAL_REFINED_FOR_SWIFT
static const SPPose3D SPPose3DInvalid = {
    .position = {INFINITY, INFINITY, INFINITY},
    .rotation = (SPRotation3D){ .vector = {INFINITY, INFINITY, INFINITY, INFINITY }}
};

/// The point with the value zero.
__API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0))
SPATIAL_SWIFT_NAME(Point3D.zero)
static const SPPoint3D SPPoint3DZero = { 0, 0, 0 };

/// The point with location @p (infinity,infinity,infinity) .
__API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0))
SPATIAL_SWIFT_NAME(Point3D.infinity)
static const SPPoint3D SPPoint3DInfinity = { INFINITY, INFINITY, INFINITY };

/// The vector with the value zero.
__API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0))
SPATIAL_SWIFT_NAME(Vector3D.zero)
static const SPVector3D SPVector3DZero = { 0, 0, 0 };

/// The vector with values @p (infinity,infinity,infinity) .
__API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0))
SPATIAL_SWIFT_NAME(Vector3D.infinity)
static const SPVector3D SPVectorInfinity = { INFINITY, INFINITY, INFINITY };

/// The size with the value zero.
__API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0))
SPATIAL_SWIFT_NAME(Size3D.zero)
static const SPSize3D SPSize3DZero = { 0 };

/// The size with dimensions @p (infinity,infinity,infinity) .
__API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0))
SPATIAL_SWIFT_NAME(Size3D.infinity)
static const SPSize3D SPSize3DInfinity = { INFINITY, INFINITY, INFINITY };

/// A size that represents an invalid size.
__API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0))
SPATIAL_REFINED_FOR_SWIFT
static const SPSize3D SPSize3DInvalid = {
    INFINITY, INFINITY, INFINITY
};

/// The rect with the value zero.
__API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0))
SPATIAL_SWIFT_NAME(Rect3D.zero)
static const SPRect3D SPRect3DZero = { 0 };

/// The rect with dimensions @p (infinity,infinity,infinity) .
__API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0))
SPATIAL_SWIFT_NAME(Rect3D.infinity)
static const SPRect3D SPRect3DInfinity = {
    .origin = { INFINITY, INFINITY, INFINITY },
    .size = { INFINITY, INFINITY, INFINITY }
};

/// The null rectangle, representing an invalid value.
__API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0))
SPATIAL_REFINED_FOR_SWIFT
static const SPRect3D SPRect3DNull = {
    .origin = { INFINITY, INFINITY, INFINITY },
    .size = { 0 }
};

/// The identity transform.
__API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0))
SPATIAL_SWIFT_NAME(AffineTransform3D.identity)
static const SPAffineTransform3D SPAffineTransform3DIdentity = {
    .matrix = {
        (simd_double3){1, 0, 0},
        (simd_double3){0, 1, 0},
        (simd_double3){0, 0, 1},
        (simd_double3){0, 0, 0}
    }
};

/// An affine transform that represents an invalid transform.
__API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0))
SPATIAL_REFINED_FOR_SWIFT
static const SPAffineTransform3D SPAffineTransform3DInvalid = {
    (simd_double3) {INFINITY, INFINITY, INFINITY},
    (simd_double3) {INFINITY, INFINITY, INFINITY},
    (simd_double3) {INFINITY, INFINITY, INFINITY},
    (simd_double3) {INFINITY, INFINITY, INFINITY}
};

/// The identity transform.
__API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0))
SPATIAL_SWIFT_NAME(ProjectiveTransform3D.identity)
static const SPProjectiveTransform3D SPProjectiveTransform3DIdentity = {
    .matrix = {
        (simd_double4){1, 0, 0, 0},
        (simd_double4){0, 1, 0, 0},
        (simd_double4){0, 0, 1, 0},
        (simd_double4){0, 0, 0, 1}
    }
};

/// A projective transform that represents an invalid transform.
__API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0))
SPATIAL_REFINED_FOR_SWIFT
static const SPProjectiveTransform3D SPProjectiveTransform3DInvalid = {
    (simd_double4) {INFINITY, INFINITY, INFINITY, INFINITY},
    (simd_double4) {INFINITY, INFINITY, INFINITY, INFINITY},
    (simd_double4) {INFINITY, INFINITY, INFINITY, INFINITY},
    (simd_double4) {INFINITY, INFINITY, INFINITY, INFINITY}
};

// MARK: - Checking Special Values

/*!
 @abstract Returns a Boolean value that indicates whether the rotation axis is zero.
 
 @param axis The source rotation axis.
 @returns A Boolean value that indicates whether the rotation axis is zero.
*/
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
bool SPRotationAxis3DIsZero(SPRotationAxis3D axis)
__API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0));

SPATIAL_SWIFT_NAME(getter:RotationAxis3D.isZero(self:))
SPATIAL_OVERLOADABLE
bool SPRotationAxis3DIsZero(SPRotationAxis3D axis) {
    simd_double3 p = (simd_double3){axis.x, axis.y, axis.z};
    return simd_equal(p, 0);
}

/*!
 @abstract Returns a Boolean value that indicates whether the point is zero.
 
 @param point The source point.
 @returns A Boolean value that indicates whether the point is zero.
*/
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
bool SPPoint3DIsZero(SPPoint3D point)
__API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0));

SPATIAL_SWIFT_NAME(getter:Point3D.isZero(self:))
SPATIAL_OVERLOADABLE
bool SPPoint3DIsZero(SPPoint3D point) {
    simd_double3 p = (simd_double3){point.x, point.y, point.z};
    return simd_equal(p, 0);
}

/*!
 @abstract Returns a Boolean value that indicates whether all of the coordinates of the point are finite.
 
 @param point The source point.
 @returns A Boolean value that indicates whether all of the coordinates of the point are finite.
*/
SPATIAL_INLINE
bool SPPoint3DIsFinite(SPPoint3D point)
SPATIAL_OVERLOADABLE
__API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0));

SPATIAL_SWIFT_NAME(getter:Point3D.isFinite(self:))
SPATIAL_OVERLOADABLE
bool SPPoint3DIsFinite(SPPoint3D point) {
    simd_double3 p = (simd_double3){point.x, point.y, point.z};
    
    return simd_all(_sp_simd_isfinite(p));
}

/*!
 @abstract Returns a Boolean value that indicates whether the point contains any NaN values.
 
 @param point The source point.
 @returns A Boolean value that indicates whether the point contains any NaN values.
*/
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
bool SPPoint3DIsNaN(SPPoint3D point)
__API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0));

SPATIAL_SWIFT_NAME(getter:Point3D.isNaN(self:))
SPATIAL_OVERLOADABLE
bool SPPoint3DIsNaN(SPPoint3D point) {
    simd_double3 p = (simd_double3){point.x, point.y, point.z};
    return simd_any(_sp_simd_isnan(p));
}



/*!
 @abstract Returns a Boolean value that indicates whether the vector is zero.
 
 @param vector The source vector.
 @returns A Boolean value that indicates whether the vector is zero.
*/
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
bool SPVector3DIsZero(SPVector3D vector)
__API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0));

SPATIAL_SWIFT_NAME(getter:Vector3D.isZero(self:))
SPATIAL_OVERLOADABLE
bool SPVector3DIsZero(SPVector3D vector) {
    simd_double3 v = (simd_double3){vector.x, vector.y, vector.z};
    return simd_equal(v, 0);
}

/*!
 @abstract Returns a Boolean value that indicates whether all of the elements of the vector are finite.
 
 @param vector The source vector.
 @returns A Boolean value that indicates whether all of the coordinates of the point are finite.
*/
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
bool SPVector3DIsFinite(SPVector3D vector)
__API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0));

SPATIAL_SWIFT_NAME(getter:Vector3D.isFinite(self:))
SPATIAL_OVERLOADABLE
bool SPVector3DIsFinite(SPVector3D vector) {
    simd_double3 v = (simd_double3){vector.x, vector.y, vector.z};
    
    return simd_all(_sp_simd_isfinite(v));
}

/*!
 @abstract Returns a Boolean value that indicates whether the vector contains any NaN values.
 
 @param vector The source point.
 @returns A Boolean value that indicates whether the point contains any NaN values.
*/
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
bool SPVector3DIsNaN(SPVector3D vector)
__API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0));

SPATIAL_SWIFT_NAME(getter:Vector3D.isNaN(self:))
SPATIAL_OVERLOADABLE
bool SPVector3DIsNaN(SPVector3D vector) {
    simd_double3 v = (simd_double3){vector.x, vector.y, vector.z};
    return simd_any(_sp_simd_isnan(v));
}



/*!
 @abstract Returns a Boolean value that indicates whether the size is zero.
 
 @param size The source size.
 @returns A Boolean value that indicates whether the size is zero.
*/
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
bool SPSize3DIsZero(SPSize3D size)
__API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0));

/*!
 @abstract Returns a Boolean value that indicates whether all of the dimensions of the size are finite.
 
 @param size The source size.
 @returns A Boolean value that indicates whether all of the dimensions of the size are finite.
*/
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
bool SPSize3DIsFinite(SPSize3D size)
__API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0));

/*!
 @abstract Returns a Boolean value that indicates whether the size contains any NaN values.
 
 @param size The source size.
 @returns A Boolean value that indicates whether the size contains any NaN values.
*/
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
bool SPSize3DIsNaN(SPSize3D size)
__API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0));

SPATIAL_SWIFT_NAME(getter:Size3D.isZero(self:))
SPATIAL_OVERLOADABLE
bool SPSize3DIsZero(SPSize3D size) {
    simd_double3 v = (simd_double3){size.width, size.height, size.depth};
    return simd_equal(v, 0);
}

SPATIAL_SWIFT_NAME(getter:Size3D.isFinite(self:))
SPATIAL_OVERLOADABLE
bool SPSize3DIsFinite(SPSize3D size) {
    simd_double3 v = (simd_double3){size.width, size.height, size.depth};
    return simd_all(_sp_simd_isfinite(v));
}

SPATIAL_SWIFT_NAME(getter:Size3D.isNaN(self:))
SPATIAL_OVERLOADABLE
bool SPSize3DIsNaN(SPSize3D size) {
    simd_double3 v = (simd_double3){size.width, size.height, size.depth};
    return simd_any(_sp_simd_isnan(v));
}

/*!
 @abstract Returns a Boolean value that indicates whether a size structure represents a valid size.
 
 @param size The source size.
 @returns A Boolean value that indicates whether a size structure represents a valid size.
*/
SPATIAL_INLINE
SPATIAL_OVERLOADABLE
bool SPSize3DIsValid(SPSize3D size)
__API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0));

SPATIAL_REFINED_FOR_SWIFT
SPATIAL_OVERLOADABLE
bool SPSize3DIsValid(SPSize3D size) {
    return !(size.width == INFINITY &&
             size.height == INFINITY &&
             size.depth == INFINITY);
}

/*!
 @abstract Returns a Boolean value that indicates whether a rotation structure represents a valid rotation.
 
 @param rotation The source rotation.
 @returns A Boolean value that indicates whether a rotation structure represents a valid rotation.
*/
SPATIAL_INLINE
bool SPRotation3DIsValid(SPRotation3D rotation)
__API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0));

SPATIAL_REFINED_FOR_SWIFT
bool SPRotation3DIsValid(SPRotation3D rotation) {

    return simd_all(_sp_simd_isfinite(rotation.quaternion.vector));
}

/*!
 @abstract Returns a Boolean value that indicates whether a pose structure represents a valid pose.
 
 @param pose The source pose.
 @returns A Boolean value that indicates whether a size structure represents a valid size.
*/
SPATIAL_INLINE
bool SPPose3DIsValid(SPPose3D pose)
__API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0));

SPATIAL_REFINED_FOR_SWIFT
bool SPPose3DIsValid(SPPose3D pose) {
    return SPRotation3DIsValid(pose.rotation) && SPPoint3DIsFinite(pose.position);
}

/*!
 @abstract Returns a Boolean value that indicates whether the rectangle represents an invalid value.
 
 @param rect The source rectangle.
 @returns A Boolean value that indicates whether the rectangle is invalid.
*/
SPATIAL_INLINE
bool SPRect3DIsNull(SPRect3D rect)
__API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0));

SPATIAL_REFINED_FOR_SWIFT
bool SPRect3DIsNull(SPRect3D rect) {
    return SPSize3DIsZero(rect.size) && !SPPoint3DIsFinite(rect.origin);
}

/*!
 @abstract Returns a Boolean value that indicates whether the rectangle is zero.
 
 @param rect The source rectangle.
 @returns A Boolean value that indicates whether the rectangle is zero.
*/
SPATIAL_INLINE
bool SPRect3DIsZero(SPRect3D rect)
__API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0));

SPATIAL_SWIFT_NAME(getter:Rect3D.isZero(self:))
bool SPRect3DIsZero(SPRect3D rect) {
    return SPPoint3DIsZero(rect.origin) && SPSize3DIsZero(rect.size);
}

/*!
 @abstract Returns a Boolean value that indicates whether all of the coordinates and dimensions of the rectangle are finite.
 
 @param rect The source rectangle.
 @returns A Boolean value that indicates whether all of the coordinates and dimensions of the rectangle are finite.
*/
SPATIAL_INLINE
bool SPRect3DIsFinite(SPRect3D rect)
__API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0));

SPATIAL_SWIFT_NAME(getter:Rect3D.isFinite(self:))
bool SPRect3DIsFinite(SPRect3D rect) {
    return SPPoint3DIsFinite(rect.origin) && SPSize3DIsFinite(rect.size);
}

/*!
 @abstract Returns a Boolean value that indicates whether any of the coordinates and dimensions of the rectangle are NaN.
 
 @param rect The source rectangle.
 @returns A Boolean value that indicates whether any of the coordinates and dimensions of the rectangle are NaN.
*/
SPATIAL_INLINE
bool SPRect3DIsNaN(SPRect3D rect)
__API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0));

SPATIAL_SWIFT_NAME(getter:Rect3D.isNaN(self:))
bool SPRect3DIsNaN(SPRect3D rect) {
    return SPPoint3DIsNaN(rect.origin) || SPSize3DIsNaN(rect.size);
}

#endif /* Spatial_Structures_h */
