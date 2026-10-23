//
//  MPSFunctionTypes.h
//  MPSFunctions
//
//  Created on 3/23/26.
//  Copyright © 2017 Apple. All rights reserved.

#ifndef MPSFunctionTypes_h
#define MPSFunctionTypes_h

// Shared Metal / framework types


#ifdef __METAL_VERSION__
// Metal specific types

#else
// Framework only types

#include <stdint.h>
#include <Availability.h>
#include <Metal/Metal.h>
#include <simd/simd.h>


#ifdef MPS_HIDE_AVAILABILITY
#    define MPSF_AVAILABLE_STARTING(...)
#else
#    define MPSF_AVAILABLE_STARTING(...)                         __API_AVAILABLE(__VA_ARGS__)
#endif

#define MPSF_AVAILABILITY_v1            MPSF_AVAILABLE_STARTING(macos(27.0), ios(27.0), tvos(27.0), visionos(27.0))



/*! @abstract Axis aligned bounding box for color gamut */
typedef struct
{
    vector_float4   max;    /// maximum representable per channel values
    vector_float4   min;    /// minimum  representable per channel values
}MPSFunctions_AABB;

#endif  /* __METAL_VERSION__ */

#endif /* MPSFunctionTypes_h */
