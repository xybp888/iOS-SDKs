/*!
 *  @header MPSTypes.h
 *  @framework MetalPerformanceShaders
 *  @copyright Copyright (c) 2015 Apple Inc. All rights reserved.
 *  @discussion   Types common to MetalPerformanceShaders.framework
 */

#ifndef MPS_Types_h
#define MPS_Types_h

#ifdef __cplusplus
extern "C" {
#endif
    
#import <Foundation/NSObjCRuntime.h>
#import <Metal/Metal.h>

    
#ifndef __has_attribute          /* clang will define this. Other compilers maybe not. */
#    define __has_attribute(a)   0
#endif
#ifndef __has_feature           /* clang will define this. Other compilers maybe not. */
#    define __has_feature(f)     0
#endif
#ifndef __has_extension         /* clang will define this. Other compilers maybe not. */
#    define __has_extension(e)   0
#endif
#if __has_extension(enumerator_attributes)
#    ifdef __IPHONE_OS_VERSION_MIN_REQUIRED
#        define MPS_ENUM_AVAILABLE_STARTING(_osx, _ios)   __AVAILABILITY_INTERNAL##_ios
#        define MPS_AVAILABLE_STARTING(_osx, _ios)        __AVAILABILITY_INTERNAL##_ios
#    elif defined(__MAC_OS_X_VERSION_MIN_REQUIRED)
#        define MPS_ENUM_AVAILABLE_STARTING(_osx, _ios)   __AVAILABILITY_INTERNAL##_osx
#        define MPS_AVAILABLE_STARTING(_osx, _ios)        __AVAILABILITY_INTERNAL##_osx
#    else
#        define MPS_ENUM_AVAILABLE_STARTING(_osx, _ios)
#        define MPS_AVAILABLE_STARTING(_osx, _ios)
#    endif
#else
#    define MPS_ENUM_AVAILABLE_STARTING( _a, _b )
#endif


/*! @typedef    MPSKernelOptions
 *  @memberof   MPSKernel
 *  @abstract   Options used when creating MPSKernel objects
 *
 *          MPSKernelOptionsNone                    Use default options
 *
 *          MPSKernelOptionsSkipAPIValidation       Most MetalImage functions will sanity check their arguments. This has a small but
 *                                                  non-zero CPU cost. Setting the MPSKernelOptionsSkipAPIValidation will skip these checks.
 *                                                  MPSKernelOptionsSkipAPIValidation does not skip checks for memory allocation failure.
 *                                                  Caution:  turning on MPSKernelOptionsSkipAPIValidation can result in undefined behavior
 *                                                  if the requested operation can not be completed for some reason. Most error states
 *                                                  will be passed through to Metal which may do nothing or abort the program if Metal
 *                                                  API validation is turned on.
 *
 *          MPSKernelOptionsAllowReducedPrecision   When possible, MPSKernels use a higher precision data representation internally than
 *                                                  the destination storage format to avoid excessive accumulation of computational
 *                                                  rounding error in the result. MPSKernelOptionsAllowReducedPrecision advises the
 *                                                  MPSKernel that the destination storage format already has too much precision for
 *                                                  what is ultimately required downstream, and the MPSKernel may use reduced precision
 *                                                  internally when it feels that a less precise result would yield better performance.  
 *                                                  The expected performance win is often small, perhaps 0-20%. When enabled, the
 *                                                  precision of the result may vary by hardware and operating system.
 */
typedef NS_OPTIONS(NSUInteger, MPSKernelOptions)
{
    MPSKernelOptionsNone                         MPS_ENUM_AVAILABLE_STARTING( __MAC_NA, __IPHONE_9_0)  = 0,
    MPSKernelOptionsSkipAPIValidation            MPS_ENUM_AVAILABLE_STARTING( __MAC_NA, __IPHONE_9_0)  = 1 << 0,
    MPSKernelOptionsAllowReducedPrecision        MPS_ENUM_AVAILABLE_STARTING( __MAC_NA, __IPHONE_9_0)  = 1 << 1,
};
    
/*! @typedef    MPSImageEdgeMode
 *  @memberof   MPSKernel
 *  @abstract   Options used to control edge behaviour of filter when filter reads beyond boundary of src image
 *
 *          MPSImageEdgeModeClamp        Out of bound pixels are clamped to nearest edge pixel
 *
 *          MPSImageEdgeModeZero         Out of bound pixels are (0,0,0,1) for image with pixel format without alpha channel
 *                                       and (0,0,0,0) for image with pixel format that has an alpha channel
 */
typedef NS_ENUM(NSUInteger, MPSImageEdgeMode)
{
    MPSImageEdgeModeZero                MPS_ENUM_AVAILABLE_STARTING(__MAC_NA, __IPHONE_9_0)  = 0,
    MPSImageEdgeModeClamp               MPS_ENUM_AVAILABLE_STARTING(__MAC_NA, __IPHONE_9_0)  = 1,
};
    
/*!
 *  @typedef    MPSOffset
 *  @memberof   MPSKernel
 *  @abstract   A signed coordinate with x, y and z components
 *  @field      x       The horizontal component of the offset. Units: pixels
 *  @field      y       The vertical component of the offset. Units: pixels
 *  @field      z       The depth component of the offset. Units: pixels
 */
typedef struct
{
    NSInteger x;    /**<    The horizontal component of the offset. Units: pixels   */
    NSInteger y;    /**<    The vertical component of the offset. Units: pixels     */
    NSInteger z;    /**<    The depth component of the offset. Units: pixels        */
}MPSOffset;

/*!
 *  @typedef    MPSOrigin
 *  @memberof   MPSKernel
 *  @abstract   A position in an image
 *  @field      x   The x coordinate of the position
 *  @field      y   The y coordinate of the position
 *  @field      z   The z coordinate of the position
 */
typedef struct
{
    double  x;
    double  y;
    double  z;
}MPSOrigin;

/*!
 *  @typedef    MPSSize
 *  @memberof   MPSKernel
 *  @abstract   A size of a region in an image
 *  @field      width       The width of the region
 *  @field      height      The height of a region
 *  @field      depth       The depth of a region (usually 1)
 */
typedef struct
{
    double  width;
    double  height;
    double  depth;
}MPSSize;

/*!
 *  @typedef    MPSRegion
 *  @memberof   MPSKernel
 *  @abstract   A region of an image
 *  @field      origin  The top left corner of the region.  Units: pixels
 *  @field      size    The size of the region.             Units: pixels
 */
typedef struct
{
    MPSOrigin       origin;                 /**< The top left corner of the region.  Units: pixels */
    MPSSize         size;                   /**< The size of the region. Units: pixels */
}MPSRegion;
    
/*!
 *  @memberof   MPSKernel
 *  @constant   MPSRectNoClip
 *  @discussion This is a special constant to indicate no clipping is to be done.
 *              The entire image will be used.
 *              This is the default clipping rectangle or the input extent for MPSKernels.
 */
extern const MTLRegion  MPSRectNoClip;
    
/*!
 *  @typedef    MPSScaleTransform
 *  @memberof   MPSImageLanczosScale
 *  @abstract   Transform matrix for explict control over resampling in MPSImageLanczosScale
 */
typedef struct MPSScaleTransform
{
    double  scaleX, scaleY;
    double  translateX, translateY;
}MPSScaleTransform;

@class MPSKernel;
    
/*!
 *  @typedef    MPSCopyAllocator
 *  @memberof   MPSKernel
 *  @abstract   A block to make a copy of sourceTexture for MPSKernels that can only execute out of place.
 *  @discussion Some MPSKernel objects may not be able to operate in place. When that occurs, and in-place
 *              operation is requested, MetalImage will call back to this block to get a new texture
 *              to return instead. To avoid spending long periods of time allocating pages to back the
 *              MTLTexture, the block should attempt to reuse textures. The texture returned from the
 *              MPSCopyAllocator will be returned instead of the sourceTexture from the MPSKernel method 
 *              on return.
 *              @code
 *              // A MPSCopyAllocator to handle cases where in-place operation fails.
 *              MPSCopyAllocator myAllocator = ^id <MTLTexture>( MPSKernel * __nonnull filter,
 *                                                              __nonnull id <MTLCommandBuffer> cmdBuf,
 *                                                              __nonnull id <MTLTexture> sourceTexture)
 *              {
 *                  MTLPixelFormat format = sourceTexture.pixelFormat;  // FIXME: is this format writable?
 *                  MTLTextureDescriptor *d = [MTLTextureDescriptor texture2DDescriptorWithPixelFormat: format
 *                                               width: sourceTexture.width
 *                                              height: sourceTexture.height
 *                                           mipmapped: NO];
 *
 *                  //FIXME: Allocating a new texture each time is slow. They take up to 1 ms each.
 *                  //       There are not too many milliseconds in a video frame! You can recycle
 *                  //       old textures (or MTLBuffers and make textures from them) and reuse
 *                  //       the memory here.
 *                  id <MTLTexture> result = [cmdBuf.device newTextureWithDescriptor: d];
 *
 *                  // FIXME: If there is any metadata associated with sourceTexture such as colorspace
 *                  //        information, MTLResource.label, MTLResource.cpuCacheMode mode,
 *                  //        MTLResource.MTLPurgeableState, etc., it may need to be similarly associated
 *                  //        with the new texture to avoid losing your metadata.
 *
 *                  // FIXME: If filter.clipRect doesn't cover the entire image, you may need to copy
 *                  //        pixels from sourceTexture to the new texture or regions of the new texture
 *                  //        will be uninitialized. You can make a MTLCommandEncoder to encode work on
 *                  //        the MTLCommandBuffer here to do that work, if necessary. It will be
 *                  //        scheduled to run immediately before the MPSKernel work. Do may call
 *                  //        [MTLCommandBuffer enqueue/commit/waitUntilCompleted/waitUntilScheduled]
 *                  //        in the MPSCopyAllocator block. Make sure to call -endEncoding on the
 *                  //        MTLCommandEncoder so that the MTLCommandBuffer has no active encoder
 *                  //        before returning.
 *
 *                  // CAUTION: The next command placed on the MTLCommandBuffer after the MPSCopyAllocator 
 *                  //          returns is almost assuredly going to be encoded with a MTLComputeCommandEncoder. 
 *                  //          Creating any other type of encoder in the MPSCopyAllocator will probably cost
 *                  //          an additional 0.5 ms of both CPU _AND_ GPU time (or more!) due to a double 
 *                  //          mode switch penalty.
 *
 *                  // CAUTION: If other objects (in addition to the caller of -encodeToCommandBuffer:inPlaceTexture:...)
 *                  //          own a reference to sourceTexture, they may need to be notified that
 *                  //          sourceTexture has been replaced so that they can release that resource
 *                  //          and adopt the new texture. 
 *
 *                  //          The reference to sourceTexture owned by the caller of
 *                  //          -encodeToCommandBuffer:inPlaceTexture... will be released by 
 *                  //          -encodeToCommandBuffer:inPlaceTexture:... after the kernel is encoded if 
 *                  //          and only if the MPSCopyAllocator is called, and the operation is successfully 
 *                  //          encoded out of place.
 *
 *                  return result;
 *                  // d is autoreleased
 *              };
 *              @endcode
 *              If nil is returned by the allocator, NO will be returned by the calling function.
 *
 *              When the MPSCopyAllocator is called, no MTLCommandEncoder is active on the commandBuffer.
 *              You may create a MTLCommandEncoder in the block to initialize the texture. Make sure
 *              to call -endEncoding on it before returning, if you do.
 *             
 *                  The next command placed on the MTLCommandBuffer after the MPSCopyAllocator returns is
 *                  almost assuredly going to be encoded with a MTLComputeCommandEncoder. Using any other
 *                  type of encoder in the MPSCopyAllocator will probably cost you an additional 0.5 ms
 *                  of both CPU _AND_ GPU time (or more!) due to a double mode switch penalty.
 *
 *
 *  @param      filter          A valid pointer to the MPSKernel that is calling the MPSCopyAllocator. From
 *                              it you can get the clipRect of the intended operation.
 *  @param      commandBuffer   A valid MTLCommandBuffer. It can be used to obtain the device against
 *                              which to allocate the new texture. You may also enqueue operations on
 *                              the commandBuffer to initialize the texture on a encoder allocated in the
 *                              block. You may not submit, enqueue or wait for scheduling/completion of 
 *                              the command buffer.
 *  @param      sourceTexture   The texture that is providing the source image for the filter. You may
 *                              wish to use its size and MTLPixelFormat for the new texture, but it is
 *                              not requred.
 *
 *  @return     A new valid MTLTexture to use as the destination for the MPSKernel. If the calling function
 *              succeeds, its texture parameter will be overwritten with a pointer to this texture. If the
 *              calling function fails (highly unlikely, except for user error) then the texture
 *              will be released before the calling function returns.
 */
    
/* Warning here for ns_returns_retained is clang rdar://problem/20130079 */
typedef id <MTLTexture> __nonnull NS_RETURNS_RETAINED (^MPSCopyAllocator)( MPSKernel * __nonnull filter,
                                                                          id <MTLCommandBuffer> __nonnull commandBuffer,
                                                                          id <MTLTexture> __nonnull sourceTexture);
    

#ifdef __cplusplus
}
#endif


#endif /* MPS_Types_h */

