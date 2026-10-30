#pragma once

#include <ComputeGraph/ComputeGraphTypes.h>

/// Declarations for types that are implemented by modules, but aren't
/// needed as part of the ComputeGraph API


/// Parameters describing mouse interaction in 3D space.
///
/// This structure captures both the position and direction of a mouse cursor
/// projected into 3D coordinates, commonly used for ray casting or spatial interactions.
struct MouseParams
{
    /// The 3D position of the mouse cursor in local space, converted to the
    /// simulation's coordinate system.
    simd_float3 position;
    
    /// The normalized direction vector of the mouse ray, converted to the
    /// simulation's coordinate system.
    simd_float3 direction;
    
    /// Indicates whether valid mouse parameters are available.
    ///
    /// When `false`, the `position` and `direction` values should not be used.
    bool has_value;
};

/// Camera viewpoint parameters in 3D space.
///
/// This structure represents a camera or observer's position and viewing direction,
/// with optional availability flags for each component. This allows partial viewpoint
/// information to be represented when only position or direction is known.
struct Viewpoint
{
    /// The 3D position of the camera or viewpoint, in the simulation's coordinate system.
    simd_float3 position;
    
    /// The normalized direction vector indicating where the camera is looking,
    /// in the simulation's coordinate system
    simd_float3 direction;

    /// Indicates whether a valid position is available.
    ///
    /// When `false`, the `position` value should not be used.
    bool has_position;
    
    /// Indicates whether a valid direction is available.
    ///
    /// When `false`, the `direction` value should not be used.
    bool has_direction;
};
