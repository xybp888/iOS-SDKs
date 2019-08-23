/*!
 *  @header MPSKernel.h
 *  @framework MetalPerformanceShaders.framework
 *  @copyright Copyright (c) 2015 Apple Inc. All rights reserved.
 *
 *  @discussion  MPSKernel objects encode tuned image processing operations into a MTLCommandBuffer.
 */


#ifndef MPS_MPSKernel_h
#define MPS_MPSKernel_h

#include <MetalPerformanceShaders/MPSTypes.h>

#ifdef __cplusplus
extern "C" {
#endif

/*!
 *  MPSSupportsMTLDevice
 *  @abstract   Determine whether a MetalPerformanceShaders.framework  supports a MTLDevice.
 *  @discussion Use this function to determine whether a MTLDevice can be used with interfaces in MetalPerformanceShaders.framework.
 *  @param      device          A valid MTLDevice
 *  @return     YES             The device is supported.
 *              NO              The device is not supported
 */
BOOL    MPSSupportsMTLDevice( __nullable id <MTLDevice> device )  MPS_AVAILABLE_STARTING( __MAC_10_11, __IPHONE_9_0, __TVOS_9_0);


/*!
 *  @class      MPSKernel
 *  @dependency This depends on Metal.framework
 *  @discussion The MPSKernel class is the base class for all MPS objects.  It defines a standard interface for
 *              MPS kernels.   You should not use the MPSKernel class directly. Instead, a  number of MPSKernel 
 *              subclasses are available in MetalPerformanceShaders.framework that define specific high-performance
 *              image processing operations.
 *
 *              The basic sequence for applying a MPSKernel to an image is as follows:
 *
 *              1.  Create a MPSKernel corresponding to the operation you wish to perform:
 *                  @code
 *                  MPSImageSobel *sobel = [[MPSImageSobel alloc] initWithDevice: mtlDevice];
 *                  @endcode
 *
 *              2.  Encode the filter into a command buffer:
 *                  @code
 *                  sobel.offset = ...;
 *                  sobel.clipRect = ...;
 *                  sobel.options = ...;
 *                  [sobel encodeToCommandBuffer: commandBuffer
 *                                 sourceTexture: inputImage
 *                            destinationTexture: resultImage ];
 *                  
 *                  if( returnVal < 0 )
 *                      MyShowError( returnVal );
 *                  @endcode
 *                  Encoding the kernel merely encodes the operation into a MTLCommandBuffer. It does not modify any pixels, yet.
 *                  All MPSKernel state has been copied to the command buffer. MPSKernels may be reused.  If the texture was previously
 *                  operated on by another command encoder (e.g. MTLRenderCommandEncoder), you should call -endEncoding on the other
 *                  encoder before encoding the filter.
 *
 *                  Some MPS filters work in place (inputImage = resultImage) even in situations where Metal might not
 *                  normally allow in place operation on textures. If in-place operation is desired, you may attempt to call
 *                  [MPSKernel encodeKernelInPlace...]. If the operation can not be completed in place, then
 *                  NO will be returned and you will have to create a new result texture and try again. To make an in-place
 *                  image filter reliable, pass a fallback MPSCopyAllocator to the method to create a new texture to write
 *                  to in the event that a filter can not operate in place.
 *
 *                  (Repeat steps 2 for more filters, as desired.)
 *
 *                      It should be self evident that step 2 may not be thread safe. That is, you can not have
 *                      multiple threads manipulating the same properties on the same MPSKernel object at the
 *                      same time and achieve coherent output. In common usage, the MPSKernel properties don't
 *                      often need to be changed from their default values, but if you need to apply the same
 *                      filter to multiple images on multiple threads with cropping / tiling, make additional
 *                      MPSKernel objects per thread. They are cheap. You can use multiple MPSKernel objects on
 *                      multiple threads, as long as only one thread is operating on any particular MPSKernel
 *                      object at a time.
 *
 *              3.  After encoding any additional work to the command buffer using other encoders, submit the MTLCommandBuffer
 *                  to your MTLCommandQueue, using:
 *                  @code
 *                  [mtlCommandBuffer commit];
 *                  @endcode
 */

MPS_CLASS_AVAILABLE_STARTING( __MAC_10_11, __IPHONE_9_0, __TVOS_9_0)
@interface MPSKernel  : NSObject <NSCopying>

/****************
 *  Properties  *
 ****************/

/*! @property   options
 *  @abstract   The set of options used to run the kernel.
 *  @ref        subsubsection_options
 */
@property (readwrite, nonatomic) MPSKernelOptions                   options;

/*! @property device
 *  @abstract  The device on which the kernel will be used
 */
@property (readonly, retain, nonatomic, nonnull)  id <MTLDevice>    device;

/*!
 @property label
 @abstract A string to help identify this object.
 */
@property (copy, atomic, nullable)  NSString *                      label;

/*********************
 *  Object creation  *
 *********************/


/*!
 *  @abstract   Standard init with default properties per filter type
 *  @param      device      The device that the filter will be used on. May not be NULL.
 *  @result     a pointer to the newly initialized object. This will fail, returning
 *              nil if the device is not supported. Devices must be 
 *              MTLFeatureSet_iOS_GPUFamily2_v1 or later.
 */
-(nonnull instancetype) initWithDevice: (nonnull id <MTLDevice>) device
                        NS_DESIGNATED_INITIALIZER;


/*!
 *  @abstract   Make a copy of this MPSKernel for a new device
 *  @discussion -copyWithZone: will call this API to make a copy of the
 *              MPSKernel on the same device.  This interface may also be
 *              called directly to make a copy of the MPSKernel on a new
 *              device. Typically, the same MPSKernels should not be used
 *              to encode kernels on multiple command buffers from multiple
 *              threads. Many MPSKernels have mutable properties that might 
 *              be changed by the other thread while this one is trying to 
 *              encode. If you need to use a MPSKernel from multiple threads
 *              make a copy of it for each additional thread using -copyWithZone:
 *              or -copyWithZone:device:
 *  @param      zone        The NSZone in which to allocate the object
 *  @param      device      The device for the new MPSKernel. If nil, then use
 *                          self.device.
 *  @result     a pointer to a copy of this MPSKernel. This will fail, returning
 *              nil if the device is not supported. Devices must be
 *              MTLFeatureSet_iOS_GPUFamily2_v1 or later.
 */
- (nonnull instancetype) copyWithZone:(nullable NSZone *)zone
                               device:(nullable id <MTLDevice>) device;

@end


#ifdef __cplusplus
    }       /* extern "C" */
#endif

#endif  /* MPS_MPSKernel_h */
