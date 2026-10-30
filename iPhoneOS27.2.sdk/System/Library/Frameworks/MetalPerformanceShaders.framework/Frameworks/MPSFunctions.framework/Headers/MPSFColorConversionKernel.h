//
//  MPSFColorConversionKernel.h
//  MPSFunctions
//
//  Created on 3/23/26.
//  Copyright © 2017 Apple. All rights reserved.


#ifndef MPSFColorConversionKernel_h
#define MPSFColorConversionKernel_h

#if defined(__METAL_VERSION__)

#include <metal_stdlib>

using namespace metal;

typedef struct mpsf_color_conversion_data
{
    texture1d<float, access::sample> tex1d_1;  // may be NULL
    texture3d<float, access::sample> tex3d_1;  // may be NULL
    texture3d<float, access::sample> tex3d_2;  // may be NULL
}mpsf_color_conversion_data;

// The conversion will have one of these two function prototypes.
typedef float4 MPSFColorConversion_conversion_func32( float4 v, thread mpsf_color_conversion_data & conversion_data);
typedef half4 MPSFColorConversion_conversion_func16( half4 v, thread mpsf_color_conversion_data & conversion_data);

#define _MPSFCOLORCONVERSION_CONCATENATE(x, y)  x ## y
#define MPSFCOLORCONVERSION_CONCATENATE(x, y)  _MPSFCOLORCONVERSION_CONCATENATE(x, y)
#define MPSFCOLORCONVERSION_EVALUATE( x ) x

#define MPSF_DECLARE_COLOR_CONVERSION( _funcName )  \
    inline float4 __attribute__((__always_inline__)) _funcName( float4 v, thread mpsf_color_conversion_data & d )           \
    {                                                                                                                       \
        [[visible]] float4 __attribute__((__always_inline__)) MPSFCOLORCONVERSION_CONCATENATE( _funcName, _f32)(            \
                float4 v,                                                                                                   \
                texture1d<float, access::sample> tex1d_1,                                                                   \
                texture3d<float, access::sample> tex3d_1,                                                                   \
                texture3d<float, access::sample> tex3d_2);                                                                  \
        return MPSFCOLORCONVERSION_CONCATENATE(_funcName, _f32)(v, d.tex1d_1, d.tex3d_1, d.tex3d_2);                        \
    }                                                                                                                       \
    inline half4 __attribute__((__always_inline__)) _funcName( half4 v, thread mpsf_color_conversion_data & conversion_data ) \
    {                                                                                                                       \
        return half4(_funcName( float4(v), conversion_data));                                                               \
    }                                                                                                                       \


#endif /* __METAL_VERSION__ */

#endif /* MPSFColorConversionKernel_h */
