//
//  MPSFunction.h
//  MPSFunction
//
//  Created on 3/23/26.
//  Copyright © 2017 Apple. All rights reserved.

#ifndef _MPS_Functions_h
#define _MPS_Functions_h

#if defined(__METAL_VERSION__)
// Metal Kernel usage
#   include <MPSFunctions/MPSFunctionTypes.h>
#   include <MPSFunctions/MPSFColorConversionKernel.h>

#else
// CPU side headers
#   include <MPSFunctions/MPSFunctionTypes.h>
#   include <MPSFunctions/MPSFColorConversion.h>

#endif

#endif /* _MPS_Function_h */

