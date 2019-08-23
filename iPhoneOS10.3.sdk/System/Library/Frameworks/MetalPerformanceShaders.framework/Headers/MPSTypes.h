/*!
 *  @header     MPSTypes.h
 *  @framework  MetalPerformanceShaders
 *  @copyright  Copyright (c) 2015 Apple Inc. All rights reserved.
 *  @discussion Types common to MetalPerformanceShaders.framework
 */

#ifndef MPS_Types_h
#define MPS_Types_h

#import <Foundation/NSObjCRuntime.h>
#import <Metal/Metal.h>

#ifdef __cplusplus
extern "C" {
#endif

    
#ifndef __has_attribute          /* clang will define this. Other compilers maybe not. */
#    define __has_attribute(a)   0
#endif
#ifndef __has_feature           /* clang will define this. Other compilers maybe not. */
#    define __has_feature(f)     0
#endif
#ifndef __has_extension         /* clang will define this. Other compilers maybe not. */
#    define __has_extension(e)   0
#endif
    
#ifdef MPS_HIDE_AVAILABILITY
#    define MPS_ENUM_AVAILABLE_STARTING(_osx, _ios, _tvos)
#    define MPS_CLASS_AVAILABLE_STARTING(_osx, _ios, _tvos)
#    define MPS_AVAILABLE_STARTING(_osx, _ios, _tvos)
#else
#    ifdef __IPHONE_OS_VERSION_MIN_REQUIRED
#        define MPS_CLASS_AVAILABLE_STARTING(_osx, _ios, _tvos)  __attribute__((visibility("default"))) __AVAILABILITY_INTERNAL##_ios
#        define MPS_AVAILABLE_STARTING(_osx, _ios, _tvos)        __AVAILABILITY_INTERNAL##_ios
#    elif defined(__MAC_OS_X_VERSION_MIN_REQUIRED)
#        define MPS_CLASS_AVAILABLE_STARTING(_osx, _ios, _tvos)  __attribute__((visibility("default"))) __AVAILABILITY_INTERNAL##_osx
#        define MPS_AVAILABLE_STARTING(_osx, _ios, _tvos)        __AVAILABILITY_INTERNAL##_osx
#    elif __has_feature(attribute_availability_tvos)
#        define MPS_CLASS_AVAILABLE_STARTING(_osx, _ios, _tvos)  __attribute__((visibility("default"))) __OS_AVAILABILITY(_tvos,introduced=_vers)
#        define MPS_AVAILABLE_STARTING(_osx, _ios, _tvos)        __OS_AVAILABILITY(_tvos,introduced=_vers)
#    elif __has_feature(attribute_availability_watchos)
#        define MPS_CLASS_AVAILABLE_STARTING(_osx, _ios, _tvos)  __attribute__((visibility("default"))) __OS_AVAILABILITY(watchos,unavailable)
#        define MPS_AVAILABLE_STARTING(_osx, _ios, _tvos)        __OS_AVAILABILITY(watchos,unavailable)
#    else
#        define MPS_CLASS_AVAILABLE_STARTING(_osx, _ios, _tvos)
#        define MPS_AVAILABLE_STARTING(_osx, _ios, _tvos)
#    endif
#
#    if __has_extension(enumerator_attributes)
#       ifdef __IPHONE_OS_VERSION_MIN_REQUIRED
#           define MPS_ENUM_AVAILABLE_STARTING(_osx, _ios, _tvos)   __AVAILABILITY_INTERNAL##_ios
#       elif defined(__MAC_OS_X_VERSION_MIN_REQUIRED)
#           define MPS_ENUM_AVAILABLE_STARTING(_osx, _ios, _tvos)   __AVAILABILITY_INTERNAL##_osx
#       elif __has_feature(attribute_availability_tvos)
#           define MPS_ENUM_AVAILABLE_STARTING(_osx, _ios, _tvos)   __OS_AVAILABILITY(_tvos,introduced=_vers)
#       elif __has_feature(attribute_availability_watchos)
#           define MPS_ENUM_AVAILABLE_STARTING(_osx, _ios, _tvos)   __OS_AVAILABILITY(watchos,unavailable)
#       else
#           define MPS_ENUM_AVAILABLE_STARTING(_osx, _ios, _tvos)
#       endif
#    else
#       define MPS_ENUM_AVAILABLE_STARTING(_osx, _ios, _tvos)
#    endif
#endif

#if __has_feature(objc_class_property)
#   define  MPS_SWIFT_NAME(_name)    CF_SWIFT_NAME(_name)
#else
#   define  MPS_SWIFT_NAME(_name)
#endif

/*! @enum       MPSKernelOptions
 *  @memberof   MPSKernel
 *  @abstract   Options used when creating MPSKernel objects
 */
#if defined(DOXYGEN)
typedef enum MPSKernelOptions
#else
typedef NS_OPTIONS(NSUInteger, MPSKernelOptions)
#endif
{
    /*! Use default options */
    MPSKernelOptionsNone                         MPS_ENUM_AVAILABLE_STARTING( __MAC_10_11, __IPHONE_9_0, __TVOS_9_0)  = 0,
    
    /*! Most MPS functions will sanity check their arguments. This has a small but
     *  non-zero CPU cost. Setting the MPSKernelOptionsSkipAPIValidation will skip these checks.
     *  MPSKernelOptionsSkipAPIValidation does not skip checks for memory allocation failure.
     *  Caution:  turning on MPSKernelOptionsSkipAPIValidation can result in undefined behavior
     *  if the requested operation can not be completed for some reason. Most error states
     *  will be passed through to Metal which may do nothing or abort the program if Metal
     *  API validation is turned on. */
    MPSKernelOptionsSkipAPIValidation            MPS_ENUM_AVAILABLE_STARTING( __MAC_10_11, __IPHONE_9_0, __TVOS_9_0)  = 1 << 0,
    
    /*! When possible, MPSKernels use a higher precision data representation internally than
     *  the destination storage format to avoid excessive accumulation of computational
     *  rounding error in the result. MPSKernelOptionsAllowReducedPrecision advises the
     *  MPSKernel that the destination storage format already has too much precision for
     *  what is ultimately required downstream, and the MPSKernel may use reduced precision
     *  internally when it feels that a less precise result would yield better performance.
     *  The expected performance win is often small, perhaps 0-20%. When enabled, the
     *  precision of the result may vary by hardware and operating system. */
    MPSKernelOptionsAllowReducedPrecision        MPS_ENUM_AVAILABLE_STARTING( __MAC_10_11, __IPHONE_9_0, __TVOS_9_0)  = 1 << 1,
    
    /*! Some MPSKernels may automatically split up the work internally into multiple tiles.
     *  This improves performance on larger textures and reduces the amount of memory needed by
     *  MPS for temporary storage. However, if you are using your own tiling scheme to achieve
     *  similar results, your tile sizes and MPS's choice of tile sizes may interfere with
     *  one another causing MPS to subdivide your tiles for its own use inefficiently. Pass
     *  MPSKernelOptionsDisableInternalTiling to force MPS to process your data tile as a
     *  single chunk.   */
    MPSKernelOptionsDisableInternalTiling        MPS_ENUM_AVAILABLE_STARTING( __MAC_10_12, __IPHONE_10_0, __TVOS_10_0) = 1 << 2,
    
    /*! Enabling this bit will cause various -encode... methods to call MTLCommandEncoder
     *  push/popDebugGroup.  The debug string will be drawn from MPSKernel.label, if any
     *  or the name of the class otherwise. */
    MPSKernelOptionsInsertDebugGroups            MPS_ENUM_AVAILABLE_STARTING( __MAC_10_12, __IPHONE_10_0, __TVOS_10_0) = 1 << 3,
};
    
/*! @enum       MPSImageEdgeMode
 *  @memberof   MPSKernel
 *  @abstract   Options used to control edge behaviour of filter when filter reads beyond boundary of src image
 */
#if defined(DOXYGEN)
typedef enum MPSImageEdgeMode
#else
typedef NS_ENUM(NSUInteger, MPSImageEdgeMode)
#endif
{
    /*! Out of bound pixels are clamped to nearest edge pixel */
    MPSImageEdgeModeZero                MPS_ENUM_AVAILABLE_STARTING(__MAC_10_11, __IPHONE_9_0, __TVOS_9_0)  = 0,
    
    /*! Out of bound pixels are (0,0,0,1) for image with pixel format without alpha channel
     *  and (0,0,0,0) for image with pixel format that has an alpha channel */
    MPSImageEdgeModeClamp               MPS_ENUM_AVAILABLE_STARTING(__MAC_10_11, __IPHONE_9_0, __TVOS_9_0)  = 1,
};
    
   
/*! @typedef MPSAlphaType
 *  @abstract Premultiplication description for the color channels of a texture
 *  @discussion Some image data is premultiplied. That is to say that the color channels
 *              are stored instead as color * alpha. This is an optimization for image compositing
 *              (alpha blending), but it can get in the way of most other image filters,
 *              especially those that apply non-linear affects like the MPSImageParametricCurveTransform
 *              multidimensional lookup tables, and functions like convolution or resampling filters
 *              that look at adjacent pixels, where the alpha may not be the same.
 *  @code
 *              Some basic conversion cases:
 *                  source                              destination                         operation
 *                  ------                              -----------                         ---------
 *                  MPSAlphaTypeNonPremultiplied        MPSAlphaTypeNonPremultiplied        <none>
 *                  MPSAlphaTypeNonPremultiplied        MPSAlphaTypeAlphaIsOne              composite with opaque background color
 *                  MPSAlphaTypeNonPremultiplied        MPSAlphaTypePremultiplied           multiply color channels by alpha
 *                  MPSAlphaTypeAlphaIsOne              MPSAlphaTypeNonPremultiplied        set alpha to 1
 *                  MPSAlphaTypeAlphaIsOne              MPSAlphaTypeAlphaIsOne              set alpha to 1
 *                  MPSAlphaTypeAlphaIsOne              MPSAlphaTypePremultiplied           set alpha to 1
 *                  MPSAlphaTypePremultiplied           MPSAlphaTypeNonPremultiplied        divide color channels by alpha
 *                  MPSAlphaTypePremultiplied           MPSAlphaTypeAlphaIsOne              composite with opaque background color
 *                  MPSAlphaTypePremultiplied           MPSAlphaTypePremultiplied           <none>
 *  @endcode
 *
 *              Color space conversion operations require the format to be either MPSPixelAlpha_NonPremultiplied or
 *              MPSPixelAlpha_AlphaIsOne to work correctly. A number of MPSKernels have similar requirements. If
 *              premultiplied data is provided or requested, extra operations will be added to the conversion to
 *              ensure correct operation. Fully opaque images should use MPSAlphaTypeAlphaIsOne.
 *
 *  @constant   MPSAlphaTypeNonPremultiplied   Image is not premultiplied by alpha. Alpha is not guaranteed to be 1. (kCGImageAlphaFirst/Last)
 *  @constant   MPSAlphaTypeAlphaIsOne         Alpha is guaranteed to be 1, even if it is not encoded as 1 or not encoded at all. (kCGImageAlphaNoneSkipFirst/Last, kCGImageAlphaNone)
 *  @constant   MPSAlphaTypePremultiplied      Image is premultiplied by alpha. Alpha is not guaranteed to be 1. (kCGImageAlphaPremultipliedFirst/Last)
 */

typedef NS_ENUM( NSUInteger, MPSAlphaType )
{
    MPSAlphaTypeNonPremultiplied   MPS_ENUM_AVAILABLE_STARTING(__MAC_10_12, __IPHONE_10_0, __TVOS_10_0)  = 0,
    MPSAlphaTypeAlphaIsOne         MPS_ENUM_AVAILABLE_STARTING(__MAC_10_12, __IPHONE_10_0, __TVOS_10_0)  = 1,
    MPSAlphaTypePremultiplied      MPS_ENUM_AVAILABLE_STARTING(__MAC_10_12, __IPHONE_10_0, __TVOS_10_0)  = 2
};

    
/*! @enum       MPSImageFeatureChannelFormat
 *  @memberof   MPSImage
 *  @abstract   Encodes the representation of a single channel within a MPSImage.
 *  @discussion A MPSImage pixel may have many channels in it, sometimes many more than 4, the
 *              limit of what MTLPixelFormats encode. The storage format for a single channel 
 *              within a pixel can be given by the MPSImageFeatureChannelFormat. The number
 *              of channels is given by the featureChannels parameter of appropriate MPSImage
 *              APIs. The size of the pixel is size of the channel format multiplied by the
 *              number of feature channels. No padding is allowed, except to round out to a full
 *              byte.
 */
typedef NS_ENUM(NSUInteger, MPSImageFeatureChannelFormat)
{
    /*! invalid format */
    MPSImageFeatureChannelFormatInvalid     MPS_ENUM_AVAILABLE_STARTING(__MAC_10_12, __IPHONE_10_0, __TVOS_10_0)  = 0,

    /*! uint8_t with value [0,255] encoding [0,1.0] */
    MPSImageFeatureChannelFormatUnorm8     MPS_ENUM_AVAILABLE_STARTING(__MAC_10_12, __IPHONE_10_0, __TVOS_10_0)   = 1,
    
    /*! uint16_t with value [0,65535] encoding [0,1.0] */
    MPSImageFeatureChannelFormatUnorm16     MPS_ENUM_AVAILABLE_STARTING(__MAC_10_12, __IPHONE_10_0, __TVOS_10_0)  = 2,
    
    /*! IEEE-754 16-bit floating-point value. "half precision" Representable normal range is +-[2**-14, 65504], 0, Infinity, NaN. 11 bits of precision + exponent. */
    MPSImageFeatureChannelFormatFloat16     MPS_ENUM_AVAILABLE_STARTING(__MAC_10_12, __IPHONE_10_0, __TVOS_10_0)  = 3,
    
    /*! IEEE-754 32-bit floating-point value.  "single precision" (standard float type in C) 24 bits of precision + exponent */
    MPSImageFeatureChannelFormatFloat32     MPS_ENUM_AVAILABLE_STARTING(__MAC_10_12, __IPHONE_10_0, __TVOS_10_0)  = 4,
    
};
   
/*! @typedef    MPSDataType
 *  @discussion A value to specify a type of data.
 *
 *  @constant   MPSDataTypeFloatBit     A common bit for all floating point data types.
 *  @constant   MSPDataTypeFloat32      32-bit floating point (single-precision).
 */
typedef NS_ENUM(uint32_t, MPSDataType)
{
    MPSDataTypeFloatBit MPS_ENUM_AVAILABLE_STARTING( __MAC_10_12, __IPHONE_10_0, __TVOS_10_0) = 0x10000000,
    MPSDataTypeFloat32  MPS_ENUM_AVAILABLE_STARTING( __MAC_10_12, __IPHONE_10_0, __TVOS_10_0) = MPSDataTypeFloatBit | 32
};
    
/*!
 *  @struct     MPSOffset
 *  @memberof   MPSKernel
 *  @abstract   A signed coordinate with x, y and z components
 */
typedef struct
{
    NSInteger x;    /**<    The horizontal component of the offset. Units: pixels   */
    NSInteger y;    /**<    The vertical component of the offset. Units: pixels     */
    NSInteger z;    /**<    The depth component of the offset. Units: pixels        */
}MPSOffset;

/*!
 *  @struct     MPSOrigin
 *  @memberof   MPSKernel
 *  @abstract   A position in an image
 */
typedef struct MPSOrigin
{
    double  x;  /**< The x coordinate of the position       */
    double  y;  /**< The y coordinate of the position       */
    double  z;  /**< The z coordinate of the position       */
}MPSOrigin;

/*!
 *  @struct     MPSSize
 *  @memberof   MPSKernel
 *  @abstract   A size of a region in an image
 */
typedef struct MPSSize
{
    double  width;      /**< The width of the region    */
    double  height;     /**< The height of the region   */
    double  depth;      /**< The depth of the region    */
}MPSSize;

/*!
 *  @struct     MPSRegion
 *  @memberof   MPSKernel
 *  @abstract   A region of an image
 */
typedef struct MPSRegion
{
    MPSOrigin       origin;     /**< The top left corner of the region.  Units: pixels  */
    MPSSize         size;       /**< The size of the region. Units: pixels              */
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
 *  @struct         MPSScaleTransform
 *  @abstract       Transform matrix for explict control over resampling in MPSImageLanczosScale.
 *  @discussion     The MPSScaleTransform is equivalent to:
 *       @code
 *          (CGAffineTransform) {
 *               .a = scaleX,        .b = 0,
 *               .c = 0,             .d = scaleY,
 *               .tx = translateX,   .ty = translateY
 *           }
 *       @endcode
 *
 *  @memberof       MPSImageLanczosScale
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
 *              operation is requested, MPS will call back to this block to get a new texture
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
 *                  d.usage = MTLTextureUsageShaderRead | MTLTextureUsageShaderWrite;
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
 *                  //        scheduled to run immediately before the MPSKernel work. Do not call
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

