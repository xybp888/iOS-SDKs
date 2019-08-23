/*!
 *  @header MPSImageMedian.h
 *  @framework MetalPerformanceShaders.framework
 *
 *  @copyright Copyright (c) 2015 Apple Inc. All rights reserved.
 *  @abstract MetalPerformanceShaders median filters
 */

#ifndef MPS_MPSImageMedian_h
#define MPS_MPSImageMedian_h

#include <MetalPerformanceShaders/MPSImageKernel.h>


/*!
 *  @class      MPSImageMedian
 *  @discussion The MPSImageMedian applies a median filter to an image.  A median filter finds the 
 *              median color value for each channel within a kernelDiameter x kernelDiameter 
 *              window surrounding the pixel of interest.  It is a common means of noise reduction
 *              and also as a smoothing filter with edge preserving qualities.
 *
 *              NOTE: The MPSImageMedian filter currently only supports images with <= 8 bits/channel.
 *
 */
MPS_CLASS_AVAILABLE_STARTING( __MAC_10_11, __IPHONE_9_0, __TVOS_9_0)
@interface  MPSImageMedian : MPSUnaryImageKernel

/*! @property   kernelDiameter
 *  @abstract   The diameter in pixels of the filter window.
 *  @discussion The median filter is applied to a kernelDiameter x kernelDiameter window
 *              of pixels centered on the corresponding source pixel for each destination
 *              pixel.  The kernel diameter must be an odd number.
 */
@property (readonly, nonatomic) NSUInteger kernelDiameter;


/*! @abstract   Initialize a filter for a particular kernel size and device
 *  @param      device          The device the filter will run on
 *  @param      kernelDiameter  Diameter of the median filter. Must be an odd number.
 *  @return     A valid object or nil, if failure.
 */

-(nonnull instancetype) initWithDevice: (nonnull id <MTLDevice>) device
                        kernelDiameter: (NSUInteger)kernelDiameter   NS_DESIGNATED_INITIALIZER;

/* You must use initWithDevice:kernelDiameter: instead. */
-(nonnull instancetype) initWithDevice:(nonnull id<MTLDevice>)device    NS_UNAVAILABLE;


/*! @abstract   The maximum diameter in pixels of the filter window supported by the median filter.
 */
+(NSUInteger) maxKernelDiameter;

/*! @abstract   The minimum diameter in pixels of the filter window supported by the median filter.
 */
+(NSUInteger) minKernelDiameter;

@end  /* MPSImageMedian */

#endif  /* MPS_MSImageMedian_h */

