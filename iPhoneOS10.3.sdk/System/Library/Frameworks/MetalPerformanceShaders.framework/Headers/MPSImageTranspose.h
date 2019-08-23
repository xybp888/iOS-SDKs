/*!
 *  @header MPSImageTranspose.h
 *  @framework MetalPerformanceShaders.framework
 *
 *  @copyright Copyright (c) 2015 Apple Inc. All rights reserved.
 *  @abstract MetalPerformanceShaders transpose filters
 */

#ifndef MPS_MPSImageTranspose_h
#define MPS_MPSImageTranspose_h

#include <MetalPerformanceShaders/MPSImageKernel.h>

/*!
 *  @class      MPSImageTranspose
 *  @discussion The MPSImageTranspose transposes an image
 *
 */
MPS_CLASS_AVAILABLE_STARTING( __MAC_10_11, __IPHONE_9_0, __TVOS_9_0)
@interface  MPSImageTranspose : MPSUnaryImageKernel

@end    /* MPSImageTranspose */


#endif  /* MPS_MSImageTranspose_h */

