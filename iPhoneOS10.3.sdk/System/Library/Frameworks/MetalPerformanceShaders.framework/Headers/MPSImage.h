/*!
 *  @header MPSImage.h
 *  @framework MetalPerformanceShaders.framework
 *
 *  @copyright Copyright (c) 2015 Apple Inc. All rights reserved.
 *  @discussion A MPSImage is a MTLTexture abstraction that allows for more than 4 channels, and
 *              for temporary images.
 */

#ifndef MPSImage_h
#define MPSImage_h


#include <MetalPerformanceShaders/MPSTypes.h>

#ifdef __cplusplus
extern "C" {
#endif

#pragma mark MPSImage

/*!
 *  @class      MPSImageDescriptor
 *  @dependency This depends on Metal.framework
 *  @abstract   A MPSImageDescriptor object describes a attributes of MPSImage and is used to
 *              create one (see MPSImage discussion below)
 */
MPS_CLASS_AVAILABLE_STARTING( __MAC_10_12, __IPHONE_10_0, __TVOS_10_0)
@interface MPSImageDescriptor : NSObject
/*! @property   width
 *  @abstract   The width of the CNN image.
 *  @discussion The formal width of the CNN image in pixels.  Default = 1.
 */
@property (readwrite, nonatomic) NSUInteger width;

/*! @property   height
 *  @abstract   The height of the CNN image.
 *  @discussion The formal height of the CNN image in pixels. Default = 1.
 */
@property (readwrite, nonatomic) NSUInteger height;

/*! @property   featureChannels
 *  @abstract   The number of feature channels per pixel.  Default = 1.
 */
@property (readwrite, nonatomic) NSUInteger featureChannels;

/*! @property   numberOfImages
 *  @abstract   The number of images for batch processing.   Default = 1.
 */
@property (readwrite, nonatomic) NSUInteger numberOfImages;

/*! @property   pixelFormat
 *  @abstract   The MTLPixelFormat expected for the underlying texture.
 */
@property (readonly, nonatomic) MTLPixelFormat pixelFormat;


/*! @property   channelFormat
 *  @abstract   The storage format to use for each channel in the image.
 */
@property (readwrite, nonatomic) MPSImageFeatureChannelFormat channelFormat;

/*!
 @property cpuCacheMode
 @abstract Options to specify CPU cache mode of texture resource. Default = MTLCPUCacheModeDefaultCache
 */
@property (readwrite, nonatomic) MTLCPUCacheMode cpuCacheMode;

/*!
 @property storageMode
 @abstract To specify storage mode of texture resource. 
           Default = MTLStorageModeShared on iOS
                     MTLStorageModeManaged on Mac OSX
           MTLStorageModeShared not supported on Mac OSX. 
           See Metal headers for synchronization requirements when using StorageModeManaged
 */
@property (readwrite, nonatomic) MTLStorageMode storageMode;

/*!
 *  @property   usage
 *  @abstract   Description of texture usage.  Default = MTLTextureUsageShaderRead/Write
 */
@property (readwrite, nonatomic) MTLTextureUsage usage;

/*! @abstract   Create a MPSImageDescriptor for a single read/write cnn image.
 */
+(__nonnull instancetype) imageDescriptorWithChannelFormat: (MPSImageFeatureChannelFormat)channelFormat
                                                     width: (NSUInteger)width
                                                    height: (NSUInteger)height
                                           featureChannels: (NSUInteger)featureChannels;

/*! @abstract   Create a MPSImageDescriptor for a read/write cnn image with option to set usage and batch size (numberOfImages).
 */
+(__nonnull instancetype) imageDescriptorWithChannelFormat: (MPSImageFeatureChannelFormat)channelFormat
                                                     width: (NSUInteger)width
                                                    height: (NSUInteger)height
                                           featureChannels: (NSUInteger)featureChannels
                                            numberOfImages: (NSUInteger)numberOfImages
                                                     usage: (MTLTextureUsage)usage;

@end

typedef NS_ENUM(NSUInteger, MPSPurgeableState)
{
    MPSPurgeableStateAllocationDeferred MPS_ENUM_AVAILABLE_STARTING( __MAC_10_12, __IPHONE_10_0, __TVOS_10_0) = 0,                // The buffer hasn't been allocated yet. Attempts to set purgeability will be ignored.
    MPSPurgeableStateKeepCurrent        MPS_ENUM_AVAILABLE_STARTING( __MAC_10_12, __IPHONE_10_0, __TVOS_10_0) = MTLPurgeableStateKeepCurrent,
    
    MPSPurgeableStateNonVolatile        MPS_ENUM_AVAILABLE_STARTING( __MAC_10_12, __IPHONE_10_0, __TVOS_10_0) = MTLPurgeableStateNonVolatile,
    MPSPurgeableStateVolatile           MPS_ENUM_AVAILABLE_STARTING( __MAC_10_12, __IPHONE_10_0, __TVOS_10_0) = MTLPurgeableStateVolatile,
    MPSPurgeableStateEmpty              MPS_ENUM_AVAILABLE_STARTING( __MAC_10_12, __IPHONE_10_0, __TVOS_10_0) = MTLPurgeableStateEmpty,
} NS_ENUM_AVAILABLE(10_11, 8_0);

/*!
 *  @class      MPSImage
 *  @dependency This depends on Metal.framework
 *  @abstract   A MPSImage object describes a MTLTexture that may have more than 4 channels.
 *  @discussion Some image types, such as those found in convolutional neural networks (CNN) 
 *              image differs from a standard texture in that it may have more than 4 channels 
 *              per image. While the channels could hold RGBA data, they will more commonly 
 *              hold a number of structural permutations upon a RGBA image as the neural 
 *              network progresses. It is not uncommon for each pixel to have 32 or 64 channels 
 *              in it.
 *
 *              Since a standard MTLTexture may have no more than 4 channels, the additional
 *              channels are stored in slices of 2d texture array (i.e. texture type is MTLTextureType2DArray) 
 *              such that 4 consecutive channels are stored in each slice of this array.
 *              If the number of feature channels is N, number of array slices needed is (N+3)/4.
 *              E.g. a CNN image with width 3 and height 2 with 9 channels will be stored as
 * @code
 *              slice 2         R???   R???   R???
 *                              R???   R???   R???
 *
 *              slice 1      RGBA   RGBA   RGBA
 *                           RGBA   RGBA   RGBA         (ASCII art /diagonal offset/ intended to show a Z dimension)
 *
 *              slice 0   RGBA   RGBA  RGBA
 *                        RGBA   RGBA  RGBA
 *@endcode
 *              Thus width and height of underlying 2d texture array is same as width and height of MPSImage
 *              and array length is equal to (featureChannels + 3) / 4. Channels marked with ? are just
 *              for padding and should not contain NaNs or Infs.
 *
 *              MPSImage can be container of multiple CNN images for batch processing. In order to create
 *              MPSImage that contains N images, create MPSImageDescriptror with numberOfImages set to N.
 *
 *              Length of 2d texture array (i.e. number of slices) will be equal to ((featureChannels +3)/4)*numberOfImage
 *              where consecutive (featureChannels+3)/4 slices of this array represent one image.
 *
 *              Although MPSImage can contain numberOfImages > 1, the actual number of images among these processed by MPSCNNKernel
 *              is controlled by z-dimension of clipRect. MPSCNNKernel processes n=clipRect.size.depth images from this collection.
 *              Starting index of image to process from source MPSImage is given by offset.z. Starting index of image in destination
 *              MPSImage where this processed image is written to is given by clipRect.origin.z. Thus MPSCNNKernel takes n=clipRect.size.depth
 *              image from source at indices [offset.z, offset.z+n], processed each independently and
 *              stores the result in destination at indices [clipRect.origin.z, clipRect.origin.z+n] respectively.
 *              Thus offset.z+n should be <= [src numberOfImage] and clipRect.origin.z+n should be <= [dest numberOfImages] and offset.z must
 *              be >= 0. 
 *              Example: Suppose MPSCNNConvolution takes an input image with 16 channels and outputs an image with 32 channels. This number of
 *              slices needed in source 2d texture array is 2 and number of slices nneded in destination 2d array is 4. Suppose source batch size is
 *              5 and desination batch size is 4. Thus number of source slices will be 2*5=10 and number of destination slices will be 4*4=16. If
 *              you want to process image 2 and 3 of source and store the result at index 1 and 2 in destination, you can achieve this by setting
 *              offset.z=2, clipRect.origin.z=1 and clipRect.size.depth=2. MPSCNNConvoluiton will take, in this case, slice 4 and 5 of source and
 *              produce slice 4 to 7 of destination. Similarly slice 6 and 7 will be used to produce slice 8 to 11 of destination.
 *
 *              All MPSCNNKernels process images in the batch independently. That is, calling a MPSCNNKernel on an
 *              batch is formally the same as calling it on each image in the batch sequentially.
 *              Computational and GPU work submission overhead will be amortized over more work if batch processing is used. This is especially 
 *              important for better performance on small images.
 *
 *              If the number of feature channel is <= 4 and numberOfImages=1 i.e. only one slice is needed by represent MPSImage, underlying
 *              metal texture type is choosen to be MTLTextureType2D rather than MTLTextureType2DArray as explained above.
 *
 *              There are also MPSTemporaryImages,
 *              intended for use for very short-lived image data that is produced and consumed
 *              immediately in the same MTLCommandBuffer. They are a useful way to minimize CPU-side
 *              texture allocation costs and greatly reduce the amount of memory used by your image
 *              pipeline.
 *
 *              Creation of the underlying texture may in some cases occur lazily.  You should
 *              in general avoid calling MPSImage.texture except when unavoidable to avoid
 *              materializing memory for longer than necessary. When possible, use the other MPSImage
 *              properties to get information about the MPSImage instead.
 */
MPS_CLASS_AVAILABLE_STARTING( __MAC_10_12, __IPHONE_10_0, __TVOS_10_0)
@interface MPSImage :  NSObject

/*! @property device
 *  @abstract  The device on which the MPSImage will be used
 */
@property (readonly, retain, nonatomic, nonnull)  id <MTLDevice>    device;

/*! @property   width
 *  @abstract   The formal width of the image in pixels.
 */
@property (readonly, nonatomic) NSUInteger width;

/*! @property   height
 *  @abstract   The formal height of the image in pixels.
 */
@property (readonly, nonatomic) NSUInteger height;

/*! @property   featureChannels
 *  @abstract   The number of feature channels per pixel.
 */
@property (readonly, nonatomic) NSUInteger featureChannels;

/*! @property   numberOfImages
 *  @abstract   numberOfImages for batch processing
 */
@property (readonly, nonatomic) NSUInteger numberOfImages;

/*! @property   textureType
 *  @abstract   The type of the underlying texture, typically MTLTextureType2D
 *              or MTLTextureType2DArray
 */
@property (readonly, nonatomic) MTLTextureType textureType;

/*! @property   pixelFormat
 *  @abstract   The MTLPixelFormat of the underlying texture
 */
@property (readonly, nonatomic) MTLPixelFormat pixelFormat;

/*! @property   precision
 *  @abstract   The number of bits of numeric precision available for each feature channel.
 *  @discussion This is precision, not size.  That is, float is 24 bits, not 32. half
 *              precision floating-point is 11 bits, not 16. SNorm formats have one less
 *              bit of precision for the sign bit, etc. For formats like MTLPixelFormatB5G6R5Unorm
 *              it is the precision of the most precise channel, in this case 6.  When this
 *              information is unavailable, typically compressed formats, 0 will be returned.
 */
@property (readonly, nonatomic) NSUInteger precision;

/*!
 *  @property   usage
 *  @abstract   Description of texture usage.
 */
@property (readonly, nonatomic) MTLTextureUsage usage;

/*!
 *  @property   pixelSize
 *  @abstract   Number of bytes from the first byte of one pixel to the first byte of the next 
 *              pixel in storage order.  (Includes padding.)
 */
@property (readonly, nonatomic) size_t  pixelSize;


/*! @property   texture
 *  @abstract   The associated MTLTexture object.
 *              This is a 2D texture if numberOfImages is 1 and number of feature channels <= 4.
 *              It is a 2D texture array otherwise.
 *  @discussion To avoid the high cost of premature allocation of the underlying texture, avoid calling this
 *              property except when strictly necessary. [MPSCNNKernel encode...] calls typically cause
 *              their arguments to become allocated. Likewise, MPSImages initialized with -initWithTexture:
 *              featureChannels: have already been allocated.
 */
@property (readonly, nonnull, nonatomic) id <MTLTexture> texture;

/*!
 @property label
 @abstract A string to help identify this object.
 */
@property (copy, atomic, nullable)  NSString *label;

/*!
 *  @abstract   Initialize an empty image object
 *  @param      device              The device that the image will be used. May not be NULL.
 *  @param      imageDescriptor     The MPSImageDescriptor. May not be NULL.
 *  @return     A valid MPSImage object or nil, if failure.
 *  @discussion Storage to store data needed is allocated lazily on first use of MPSImage or
 *              when application calls MPSImage.texture
 *
 */
-(nonnull instancetype) initWithDevice: (nonnull id <MTLDevice>) device
                       imageDescriptor: (const MPSImageDescriptor * __nonnull) imageDescriptor;

/*!
 *  @abstract   Initialize an MPSImage object using Metal texture. Metal texture has been created by
 *              user for specific number of feature channels and number of images.
 *  @param      texture          The MTLTexture allocated by the user to be used as backing for MPSImage.
 *  @param      featureChannels  Number of feature channels this texture contains.
 *  @return     A valid MPSImage object or nil, if failure.
 *  @discussion Application can let MPS framework allocate texture with properties specified in imageDescriptor 
 *              using initWithDevice:MPSImageDescriptor API above. However in memory intensive application, 
 *              you can save memory (and allocation/deallocation time) by using MPSTemporaryImage where MPS 
 *              framework aggressively reuse memory underlying textures on same command buffer. See MPSTemporaryImage
 *              class for details below. However, in certain cases, application developer may want more control
 *              on allocation, placement, reusing/recycling of memory backing textures used in application using
 *              Metal Heaps API. In this case, application can create MPSImage from pre-allocated texture using 
 *              initWithTexture:featureChannels.
 *
 *              MTLTextureType of texture can be MTLTextureType2D ONLY if featureChannels <= 4 in which case
 *              MPSImage.numberOfImages is set to 1. Else it should be MTLTextureType2DArray with
 *              arrayLength == numberOfImage * ((featureChannels + 3)/4). MPSImage.numberOfImages is set to
 *              texture.arrayLength / ((featureChannels + 3)/4).
 *
 *              For MTLTextures containing typical image data which application may obtain from MetalKit or 
 *              other libraries such as that drawn from a JPEG or PNG, featureChannels should
 *              be set to number of valid color channel e.g. for RGB data, even thought MTLPixelFormat will be
 *              MTLPixelFormatRGBA, featureChannels should be set to 3.
 *
 */
-(nonnull instancetype) initWithTexture: (nonnull id <MTLTexture>) texture
                        featureChannels: (NSUInteger) featureChannels;


/*
 * Use initWithDevice:texture: or initWithDevice:imageDescriptor: instead
 */
-(nonnull instancetype) init NS_UNAVAILABLE;

/*!
 *  @method         setPurgeableState
 *  @abstract       Set (or query) the purgeability state of a MPSImage
 *  @discussion     Usage is per [MTLResource setPurgeableState:], except that the MTLTexture might be
 *                  MPSPurgeableStateAllocationDeferred, which means there is no texture to mark volatile / nonvolatile.
 *                  Attempts to set purgeability on MTLTextures that have not been allocated will be ignored.
 */
- (MPSPurgeableState)setPurgeableState:(MPSPurgeableState)state;

@end

/*!
 *  @class      MPSTemporaryImage
 *  @dependency MPSImage
 *  @abstract   MPSTemporaryImages are provided as a fast way to store transient data
 *              that will be used promptly and discarded.
 *
 *  @discussion MPSTemporaryImages can provide for profound reduction in the aggregate 
 *              texture memory and associated CPU-side allocation cost in your application. 
 *              MPS achieves this by automatically identifying MPSTemporaryImages that
 *              do not overlap in time over the course of a MTLCommandBuffer and so can 
 *              reuse the same memory. MPSTemporaryImages leverage MPS's internal cache
 *              of preallocated reusable memory to hold pixel data to avoid typical 
 *              memory allocation performance penalties common to ordinary MPSImages and 
 *              MTLTextures.
 *
 *              To avoid data corruption due to aliasing, MPSTemporaryImages impose some
 *              important restrictions:
 *
 *              - The textures are MTLStorageModePrivate. You can not, for example, use
 *                [MTLTexture getBytes...] or [MTLTexture replaceRegion...] with them. 
 *                MPSTemporaryImages are strictly read and written by the GPU.
 *
 *              - The temporary image may be used only on a single MTLCommandBuffer.
 *                This limits the chronology to a single linear time stream.
 *
 *              - The readCount property must be managed correctly. Please see
 *                the description of the readCount property for full details.
 *
 *              - see also pixel format restrictions for MPSImages in general.
 *
 *              Since MPSTemporaryImages can only be used with a single MTLCommandBuffer,
 *              and can not be used off the GPU, they generally should not be kept 
 *              around past the completion of the MTLCommandBuffer. The lifetime of
 *              MPSTemporaryImages is expected to be typically extremely short, perhaps 
 *              only a few lines of code.
 *
 *              To keep the lifetime of the underlying texture allocation as short as 
 *              possible, the underlying texture is not allocated until the first time
 *              the MPSTemporaryImage is used by a MPSCNNKernel or the .texture property
 *              is read. The readCount property serves to limit the lifetime on the
 *              other end.
 *
 *              You may use the MPSTemporaryImage.texture with MPSUnaryImageKernel -encode... methods,
 *              iff featureChannels <= 4 and the MTLTexture conforms to requirements of that MPSKernel.
 *              In such cases, the readCount is not modified, since the enclosing object
 *              is not available. There is no locking mechanism provided to prevent a MTLTexture
 *              returned from the .texture property from becoming invalid when the
 *              readCount reaches 0.
 *
 *              MPSTemporaryImages can otherwise be used wherever MPSImages are used.
 *
 *
 */
MPS_CLASS_AVAILABLE_STARTING( __MAC_10_12, __IPHONE_10_0, __TVOS_10_0)
@interface  MPSTemporaryImage : MPSImage


/*!
 *  @abstract   Initialize a MPSTemporaryImage for use on a MTLCommandBuffer
 *
 *  @param      commandBuffer   The MTLCommandBuffer on which the MPSTemporaryImage will be exclusively used
 *
 *  @param      imageDescriptor A valid imageDescriptor describing the MPSImage format to create.
 *
 *  @return     A valid MPSTemporaryImage.  The object will be released when the command buffer
 *              is committed. The underlying texture will become invalid before this time
 *              due to the action of the readCount property.
 *
 */
+(nonnull instancetype) temporaryImageWithCommandBuffer: (nonnull id <MTLCommandBuffer>) commandBuffer
                                        imageDescriptor: (const MPSImageDescriptor * __nonnull) imageDescriptor;


/*!
 *  @abstract       Low level interface for creating a MPSTemporaryImage using a MTLTextureDescriptor
 *  @discussion     This function provides access to MTLPixelFormats not typically covered by -initForCommandBuffer:imageDescriptor:
 *                  The feature channels will be inferred from the MTLPixelFormat without changing the width. 
 *                  The following restrictions apply:
 *  
 *                      MTLTextureType must be MTLTextureType2D or MTLTextureType2DArray
 *                      MTLTextureUsage must contain at least one of MTLTextureUsageShaderRead, MTLTextureUsageShaderWrite
 *                      MTLStorageMode must be MTLStorageModePrivate
 *                      depth must be 1
 *
 *  @param commandBuffer        The command buffer on which the MPSTemporaryImage may be used
 *  @param textureDescriptor    A texture descriptor describing the MPSTemporaryImage texture
 *
 *  @return     A valid MPSTemporaryImage.  The object will be released when the command buffer
 *              is committed. The underlying texture will become invalid before this time
 *              due to the action of the readCount property.
 */
+(nonnull instancetype) temporaryImageWithCommandBuffer: (nonnull id <MTLCommandBuffer>) commandBuffer
                                      textureDescriptor: (const MTLTextureDescriptor * __nonnull) textureDescriptor;


/*!
 *  @abstract       Help MPS decide which allocations to make ahead of time
 *  @discussion     The texture cache that underlies the MPSTemporaryImage can automatically allocate new storage as
 *                  needed as you create new temporary images.  However, sometimes a more global view of what you
 *                  plan to make is useful for maximizing memory reuse to get the most efficient operation.
 *                  This class method hints to the cache what the list of images will be.
 *
 *                  It is never necessary to call this method. It is purely a performance and memory optimization.
 *
 *  @param commandBuffer        The command buffer on which the MPSTemporaryImages will be used
 *  @param descriptorList       A NSArray of MPSImageDescriptors, indicating images that will be created
 */
+(void) prefetchStorageWithCommandBuffer: (nonnull id <MTLCommandBuffer>) commandBuffer
                     imageDescriptorList: (NSArray <MPSImageDescriptor*> * __nonnull) descriptorList;

/*! Unavailable. Use temporaryImageForCommandBuffer:textureDescriptor: or -temporaryImageForCommandBuffer:imageDescriptor: instead. */
-(nonnull instancetype) initWithTexture: (nonnull id <MTLTexture>) texture
                        featureChannels: (NSUInteger) featureChannels NS_UNAVAILABLE;

/*! Unavailable. Use itemporaryImageForCommandBuffer:textureDescriptor: instead. */
-(nonnull instancetype) initWithDevice: (nonnull id <MTLDevice>) device
                       imageDescriptor: (const MPSImageDescriptor * __nonnull) imageDescriptor      NS_UNAVAILABLE;

/*
 *  @abstract       The number of times a temporary image may be read by a MPSCNNKernel
 *                  before its contents become undefined.
 *
 *  @discussion     MPSTemporaryImages must release their underlying textures for reuse
 *                  immediately after last use. So as to facilitate *prompt* convenient 
 *                  memory recycling, each time a MPSTemporaryImage is read by a 
 *                  MPSCNNKernel -encode... method, its readCount is automatically 
 *                  decremented. When the readCount reaches 0, the underlying texture is 
 *                  automatically made available for reuse to MPS for its own needs and for 
 *                  other MPSTemporaryImages prior to return from the -encode.. function.  
 *                  The contents of the texture become undefined at this time. 
 *
 *                  By default, the readCount is initialized to 1, indicating a image that
 *                  may be overwritten any number of times, but read only once.
 *
 *                  You may change the readCount as desired to allow MPSCNNKernels to read
 *                  the MPSTemporaryImage additional times. However, it is an error to change
 *                  the readCount once it is zero. It is an error to read or write to a
 *                  MPSTemporaryImage with a zero readCount. You may set the readCount to 0
 *                  yourself to cause the underlying texture to be returned to MPS. Writing
 *                  to a MPSTemporaryImage does not adjust the readCount.
 *
 *                  The Metal API Validation layer will assert if a MPSTemporaryImage is
 *                  deallocated with non-zero readCount to help identify cases when resources
 *                  are not returned promptly.
 */
@property (readwrite, nonatomic)  NSUInteger  readCount;


@end

#ifdef __cplusplus
}   // extern "C"
#endif


#endif /* MPSImage_h */
