/*!
 *  @header MPSImageKernel.h
 *  @framework MetalPerformanceShaders.framework
 *
 *  @copyright Copyright (c) 2015 Apple Inc. All rights reserved.
 *  @abstract Metal Image filter base classes
 */

#ifndef _MPS_MPSImageKernel_
#define _MPS_MPSImageKernel_

#import <MetalPerformanceShaders/MPSKernel.h>

/*!
 *  @class      MPSUnaryImageKernel
 *  @dependency This depends on Metal.framework
 *  @discussion A MPSUnaryImageKernel consumes one MTLTexture and produces one MTLTexture.
 */
NS_CLASS_AVAILABLE( NA, 9_0  )
@interface MPSUnaryImageKernel : MPSKernel


/*! @property   offset
 *  @abstract   The position of the destination clip rectangle origin relative to the source buffer.
 *  @discussion The offset is defined to be the position of clipRect.origin in source coordinates.
 *              Default: {0,0,0}, indicating that the top left corners of the clipRect and source image align.
 *
 *              See Also: @ref subsubsection_mioffset
 */
@property (readwrite, nonatomic) MPSOffset                offset;

/*! @property   clipRect
 *  @abstract   An optional clip rectangle to use when writing data. Only the pixels in the rectangle will be overwritten.
 *  @discussion A MTLRegion that indicates which part of the destination to overwrite. If the clipRect does not lie
 *              completely within the destination image, the intersection between clip rectangle and destination bounds is
 *              used.   Default: MPSRectNoClip (MPSKernel::MPSRectNoClip) indicating the entire image.
 *
 *              See Also: @ref subsubsection_clipRect
 */
@property (readwrite, nonatomic) MTLRegion               clipRect;


/*! @property   edgeMode
 *  @abstract   The MPSImageEdgeMode to use when texture reads stray off the edge of an image
 *  @discussion Most MPSKernel objects can read off the edge of the source image. This can happen because of a
 *              negative offset property, because the offset + clipRect.size is larger than the
 *              source image or because the filter looks at neighboring pixels, such as a Convolution
 *              or morphology filter.   Default: usually MPSImageEdgeModeZero. (Some MPSKernel types default
 *              to MPSImageEdgeModeClamp, because MPSImageEdgeModeZero is either not supported or
 *              would produce unexpected results.)
 *
 *              See Also: @ref subsubsection_edgemode
 */
@property (readwrite, nonatomic) MPSImageEdgeMode        edgeMode;



/*!
 *  This method attempts to apply the MPSKernel in place on a texture.
 *
 *          In-place operation means that the same texture is used both to hold the input
 *          image and the results. Operating in-place can be an excellent way to reduce
 *          resource utilization, and save time and energy. While simple Metal kernels can
 *          not operate in place because textures can not be readable and writable at the
 *          same time, some MPSKernels can operate in place because they use
 *          multi-pass algorithms. Whether a MPSKernel can operate in-place can
 *          depend on current hardware, operating system revision and the parameters
 *          and properties passed to it. You should never assume that a MPSKernel will
 *          continue to work in place, even if you have observed it doing so before.
 *
 *  If the operation succeeds in-place, YES is returned.  If the in-place operation
 *  fails and no copyAllocator is provided, then NO is returned. Without a fallback
 *  MPSCopyAllocator, in neither case is the pointer held at *texture modified.
 *
 *  Failure during in-place operation is very common and will occur inconsistently across
 *  different hardware platforms and OS releases. Without a fallback MPSCopyAllocator,
 *  operating in place may require significant error handling code to accompany each
 *  call to -encodeToCommandBuffer:..., complicating your code.
 *
 *  You may find it simplifies your code to provide a fallback MPSCopyAllocator so
 *  that the operation can proceed reliably even when it can not proceed in-place.
 *  When an in-place filter fails, the MPSCopyAllocator (if any) will be
 *  invoked to create a new texture in which to write the results, allowing the
 *  filter to proceed reliably out-of-place. The original texture will be released,
 *  replaced with a pointer to the new texture and YES will be returned. If the
 *  allocator returns an invalid texture, it is released, *texture remains unmodified
 *  and NO is returned.  Please see the MPSCopyAllocator definition for a sample allocator
 *  implementation.
 *
 *  Sample usage with a copy allocator:
 *  @code
 *  id <MTLTexture> inPlaceTex = ...;
 *  MPSImageSobel *sobelFiler = [[MPSImageSobel alloc] initWithDevice: my_device];
 *
 *  // With a fallback MPSCopyAllocator, failure should only occur in exceptional
 *  // conditions such as MTLTexture allocation failure or programmer error.
 *  // That is, the operation is roughly as robust as the MPSCopyAllocator.
 *  // Depending on the quality of that, we might decide we are justified here
 *  // in not checking the return value.
 *  [sobelFilter encodeToCommandBuffer: my_command_buffer
 *                      inPlaceTexture: &inPlaceTex  // may be replaced!
 *               fallbackCopyAllocator: myAllocator];
 *
 *  // If myAllocator was not called:
 *  //
 *  //      inPlaceTex holds the original texture with the result pixels in it
 *  //
 *  // else,
 *  //
 *  //      1) myAllocator creates a new texture.
 *  //      2) The new texture pixel data is overwritten by MPSUnaryImageKernel.
 *  //      3) The old texture passed in *inPlaceTex is released once.
 *  //      4) *inPlaceTex = the new texture
 *  //
 *  // In either case, the caller should now hold one reference to the texture now held in
 *  // inPlaceTex, whether it was replaced or not. Most of the time that means that nothing
 *  // further needs to be done here, and you can proceed to the next image encoding operation.
 *  // However, if other agents held references to the original texture, they still hold them
 *  // and may need to be alerted that the texture has been replaced so that they can retain
 *  // the new texture and release the old one.
 *
 *  [sobelFilter release];  // if not ARC, clean up the MPSImageSobel object
 *  @endcode
 *
 *
 *  @abstract   Attempt to apply a MPSKernel to a texture in place.
 *  @param      commandBuffer       A valid MTLCommandBuffer to receive the encoded filter
 *  @param      texture             A pointer to a valid MTLTexture containing source image.
 *                                  On success, the image contents and possibly texture itself
 *                                  will be replaced with the result image.
 *  @param      copyAllocator       An optional block to allocate a new texture to hold the
 *                                  results, in case in-place operation is not possible. The
 *                                  allocator may use a different MTLPixelFormat or size than
 *                                  the original texture. You may enqueue operations on the
 *                                  provided MTLCommandBuffer using the provided
 *                                  MTLComputeCommandEncoder to initialize the texture contents.
 *  @return     On success, YES is returned. The texture may have been replaced with a new
 *              texture if a copyAllocator was provided.  On failure, NO is returned. The
 *              texture is unmodified.
 */
-(BOOL)    encodeToCommandBuffer: (nonnull id <MTLCommandBuffer>)commandBuffer
                  inPlaceTexture: (__nonnull id <MTLTexture> __strong * __nonnull) texture
           fallbackCopyAllocator: (nullable MPSCopyAllocator) copyAllocator;


/*!
 *  @abstract   Encode a MPSKernel into a command Buffer.  The operation shall proceed out-of-place.
 *  @param      commandBuffer       A valid MTLCommandBuffer to receive the encoded filter
 *  @param      sourceTexture       A valid MTLTexture containing the source image.
 *  @param      destinationTexture  A valid MTLTexture to be overwritten by result image. DestinationTexture may not alias sourceTexture.
 */
-(void) encodeToCommandBuffer: (nonnull id <MTLCommandBuffer>) commandBuffer
                sourceTexture: (nonnull id <MTLTexture>) sourceTexture
           destinationTexture: (nonnull id <MTLTexture>) destinationTexture;


/*!
 *  sourceRegionForDestinationSize: is used to determine which region of the
 *  sourceTexture will be read by encodeToCommandBuffer:sourceTexture:destinationTexture
 *  (and similar) when the filter runs. This information may be needed if the
 *  source image is broken into multiple textures.  The size of the full
 *  (untiled) destination image is provided. The region of the full (untiled)
 *  source image that will be read is returned. You can then piece together an
 *  appropriate texture containing that information for use in your tiled context.
 *
 *  The function will consult the MPSUnaryImageKernel offset and clipRect parameters, 
 *  to determine the full region read by the function. Other parameters such as
 *  sourceClipRect, kernelHeight and kernelWidth will be consulted as necessary.
 *  All properties should be set to intended values prior to calling 
 *  sourceRegionForDestinationSize:.
 *
 *      Caution: This function operates using global image coordinates, but
 *      -encodeToCommandBuffer:... uses coordinates local to the source and
 *      destination image textures. Consequently, the offset and clipRect 
 *      attached to this object will need to be updated using a global to 
 *      local coordinate transform before -encodeToCommandBuffer:... is 
 *      called.
 *
 *  @abstract   Determine the region of the source texture that will be read for a encode operation 
 *  @param      destinationSize The size of the full virtual destination image.
 *  @return     The area in the virtual source image that will be read.
 */
-(MPSRegion) sourceRegionForDestinationSize: (MTLSize) destinationSize;

@end



/*!
 *  @class      MPSBinaryImageKernel
 *  @dependency This depends on Metal.framework
 *  @discussion A MPSBinaryImageKernel consumes two MTLTextures and produces one MTLTexture.
 */
NS_CLASS_AVAILABLE( NA, 9_0  )
@interface MPSBinaryImageKernel : MPSKernel

/*! @property   primaryOffset
 *  @abstract   The position of the destination clip rectangle origin relative to the primary source buffer.
 *  @discussion The offset is defined to be the position of clipRect.origin in source coordinates.
 *              Default: {0,0,0}, indicating that the top left corners of the clipRect and primary source image align.
 *
 *              See Also: @ref subsubsection_mioffset
 */
@property (readwrite, nonatomic) MPSOffset                primaryOffset;

/*! @property   secondaryOffset
 *  @abstract   The position of the destination clip rectangle origin relative to the secondary source buffer.
 *  @discussion The offset is defined to be the position of clipRect.origin in source coordinates.
 *              Default: {0,0,0}, indicating that the top left corners of the clipRect and primary source image align.
 *
 *              See Also: @ref subsubsection_mioffset
 */
@property (readwrite, nonatomic) MPSOffset                secondaryOffset;


/*! @property   primaryEdgeMode
 *  @abstract   The MPSImageEdgeMode to use when texture reads stray off the edge of the primary source image
 *  @discussion Most MPSKernel objects can read off the edge of a source image. This can happen because of a
 *              negative offset property, because the offset + clipRect.size is larger than the
 *              source image or because the filter looks at neighboring pixels, such as a Convolution
 *              or morphology filter.   Default: usually MPSImageEdgeModeZero. (Some MPSKernel types default
 *              to MPSImageEdgeModeClamp, because MPSImageEdgeModeZero is either not supported or
 *              would produce unexpected results.)
 *
 *              See Also: @ref subsubsection_edgemode
 */
@property (readwrite, nonatomic) MPSImageEdgeMode        primaryEdgeMode;

/*! @property   secondaryEdgeMode
 *  @abstract   The MPSImageEdgeMode to use when texture reads stray off the edge of the secondary source image
 *  @discussion Most MPSKernel objects can read off the edge of a source image. This can happen because of a
 *              negative offset property, because the offset + clipRect.size is larger than the
 *              source image or because the filter looks at neighboring pixels, such as a Convolution
 *              or morphology filter.   Default: usually MPSImageEdgeModeZero. (Some MPSKernel types default
 *              to MPSImageEdgeModeClamp, because MPSImageEdgeModeZero is either not supported or
 *              would produce unexpected results.)
 *
 *              See Also: @ref subsubsection_edgemode
 */
@property (readwrite, nonatomic) MPSImageEdgeMode        secondaryEdgeMode;

/*! @property   clipRect
 *  @abstract   An optional clip rectangle to use when writing data. Only the pixels in the rectangle will be overwritten.
 *  @discussion A MTLRegion that indicates which part of the destination to overwrite. If the clipRect does not lie
 *              completely within the destination image, the intersection between clip rectangle and destination bounds is
 *              used.   Default: MPSRectNoClip (MPSKernel::MPSRectNoClip) indicating the entire image.
 *
 *              See Also: @ref subsubsection_clipRect
 */
@property (readwrite, nonatomic) MTLRegion               clipRect;




/*!
 *  This method attempts to apply the MPSKernel in place on a texture.
 *
 *          In-place operation means that the same texture is used both to hold the input
 *          image and the results. Operating in-place can be an excellent way to reduce
 *          resource utilization, and save time and energy. While simple Metal kernels can
 *          not operate in place because textures can not be readable and writable at the
 *          same time, some MPSKernels can operate in place because they use
 *          multi-pass algorithms. Whether a MPSKernel can operate in-place can
 *          depend on current hardware, operating system revision and the parameters
 *          and properties passed to it. You should never assume that a MPSKernel will
 *          continue to work in place, even if you have observed it doing so before.
 *
 *  If the operation succeeds in-place, YES is returned.  If the in-place operation
 *  fails and no copyAllocator is provided, then NO is returned. In neither
 *  case is the pointer held at *texture modified.
 *
 *  Failure during in-place operation is common. You may find it simplifies your
 *  code to provide a copyAllocator. When an in-place filter fails, your
 *  copyAllocator will be invoked to create a new texture in which to write
 *  the results, allowing the filter to proceed reliably out-of-place. The
 *  original texture will be released, replaced with a pointer to the new texture
 *  and YES will be returned. If the allocator returns an invalid texture, it is
 *  released, *texture remains unmodified and NO is returned.  Please see the
 *  MPSCopyAllocator definition for a sample allocator implementation.
 *
 *  @abstract   Attempt to apply a MPSKernel to a texture in place.
 *  @param      commandBuffer           A valid MTLCommandBuffer to receive the encoded filter
 *  @param      primaryTexture          A pointer to a valid MTLTexture containing the
 *                                      primary source image. It will not be overwritten.
 *  @param      inPlaceSecondaryTexture A pointer to a valid MTLTexture containing secondary image.
 *                                      On success, the image contents and possibly texture itself
 *                                      will be replaced with the result image.
 *  @param      copyAllocator           An optional block to allocate a new texture to hold the
 *                                      results, in case in-place operation is not possible. The
 *                                      allocator may use a different MTLPixelFormat or size than
 *                                      the original texture. You may enqueue operations on the
 *                                      provided MTLCommandBuffer using the provided
 *                                      MTLComputeCommandEncoder to initialize the texture contents.
 *  @return     On success, YES is returned. The texture may have been replaced with a new
 *              texture if a copyAllocator was provided.  On failure, NO is returned. The
 *              texture is unmodified.
 */
-(BOOL)    encodeToCommandBuffer: (nonnull id <MTLCommandBuffer>)commandBuffer
                  primaryTexture: (nonnull id <MTLTexture>) primaryTexture
         inPlaceSecondaryTexture: (__nonnull id <MTLTexture> __strong * __nonnull) inPlaceSecondaryTexture
           fallbackCopyAllocator: (nullable MPSCopyAllocator) copyAllocator;

/*!
 *  This method attempts to apply the MPSKernel in place on a texture.
 *
 *          In-place operation means that the same texture is used both to hold the input
 *          image and the results. Operating in-place can be an excellent way to reduce
 *          resource utilization, and save time and energy. While simple Metal kernels can
 *          not operate in place because textures can not be readable and writable at the
 *          same time, some MPSKernels can operate in place because they use
 *          multi-pass algorithms. Whether a MPSKernel can operate in-place can
 *          depend on current hardware, operating system revision and the parameters
 *          and properties passed to it. You should never assume that a MPSKernel will
 *          continue to work in place, even if you have observed it doing so before.
 *
 *  If the operation succeeds in-place, YES is returned.  If the in-place operation
 *  fails and no copyAllocator is provided, then NO is returned. In neither
 *  case is the pointer held at *texture modified.
 *
 *  Failure during in-place operation is common. You may find it simplifies your
 *  code to provide a copyAllocator. When an in-place filter fails, your
 *  copyAllocator will be invoked to create a new texture in which to write
 *  the results, allowing the filter to proceed reliably out-of-place. The
 *  original texture will be released, replaced with a pointer to the new texture
 *  and YES will be returned. If the allocator returns an invalid texture, it is
 *  released, *texture remains unmodified and NO is returned.  Please see the
 *  MPSCopyAllocator definition for a sample allocator implementation.
 *
 *  @abstract   Attempt to apply a MPSKernel to a texture in place.
 *  @param      commandBuffer           A valid MTLCommandBuffer to receive the encoded filter
 *  @param      inPlacePrimaryTexture   A pointer to a valid MTLTexture containing secondary image.
 *                                      On success, the image contents and possibly texture itself
 *                                      will be replaced with the result image.
 *  @param      secondaryTexture        A pointer to a valid MTLTexture containing the
 *                                      primary source image. It will not be overwritten.
 *  @param      copyAllocator           An optional block to allocate a new texture to hold the
 *                                      results, in case in-place operation is not possible. The
 *                                      allocator may use a different MTLPixelFormat or size than
 *                                      the original texture. You may enqueue operations on the
 *                                      provided MTLCommandBuffer using the provided
 *                                      MTLComputeCommandEncoder to initialize the texture contents.
 *  @return     On success, YES is returned. The texture may have been replaced with a new
 *              texture if a copyAllocator was provided.  On failure, NO is returned. The
 *              texture is unmodified.
 */
-(BOOL)    encodeToCommandBuffer: (nonnull id <MTLCommandBuffer>)commandBuffer
           inPlacePrimaryTexture: (__nonnull id <MTLTexture> __strong * __nonnull) inPlacePrimaryTexture
                secondaryTexture: (nonnull id <MTLTexture>) secondaryTexture
           fallbackCopyAllocator: (nullable MPSCopyAllocator) copyAllocator;


/*!
 *  @abstract   Encode a MPSKernel into a command Buffer.  The operation shall proceed out-of-place.
 *  @param      commandBuffer       A valid MTLCommandBuffer to receive the encoded filter
 *  @param      primaryTexture      A valid MTLTexture containing the primary source image.
 *  @param      secondaryTexture    A valid MTLTexture containing the secondary source image.
 *  @param      destinationTexture  A valid MTLTexture to be overwritten by result image. destinationTexture may not alias sourceTexture.
 */
-(void) encodeToCommandBuffer: (nonnull id <MTLCommandBuffer>) commandBuffer
               primaryTexture: (nonnull id <MTLTexture>) primaryTexture
             secondaryTexture: (nonnull id <MTLTexture>) secondaryTexture
           destinationTexture: (nonnull id <MTLTexture>) destinationTexture;

/*!
 *  primarySourceRegionForDestinationSize: is used to determine which region of the
 *  primaryTexture will be read by encodeToCommandBuffer:primaryTexture:secondaryTexture:destinationTexture
 *  (and in-place variants) when the filter runs. This information may be needed if the
 *  primary source image is broken into multiple textures.  The size of the full
 *  (untiled) destination image is provided. The region of the full (untiled)
 *  source image that will be read is returned. You can then piece together an
 *  appropriate texture containing that information for use in your tiled context.
 *
 *  The function will consult the MPSBinaryImageKernel primaryOffset and clipRect parameters,
 *  to determine the full region read by the function. Other parameters such as
 *  kernelHeight and kernelWidth will be consulted as necessary. All properties
 *  should be set to intended values prior to calling primarySourceRegionForDestinationSize:.
 *
 *      Caution: This function operates using global image coordinates, but
 *      -encodeToCommandBuffer:... uses coordinates local to the source and
 *      destination image textures. Consequently, the primaryOffset and clipRect
 *      attached to this object will need to be updated using a global to
 *      local coordinate transform before -encodeToCommandBuffer:... is
 *      called.
 *
 *  @abstract   Determine the region of the source texture that will be read for a encode operation
 *  @param      destinationSize     The size of the full virtual destination image.
 *  @return     The area in the virtual source image that will be read.
 */
-(MPSRegion) primarySourceRegionForDestinationSize: (MTLSize) destinationSize;

/*!
 *  secondarySourceRegionForDestinationSize: is used to determine which region of the
 *  sourceTexture will be read by encodeToCommandBuffer:primaryTexture:secondaryTexture:destinationTexture
 *  (and in-place variants) when the filter runs. This information may be needed if the
 *  secondary source image is broken into multiple textures.  The size of the full
 *  (untiled) destination image is provided. The region of the full (untiled)
 *  secondary source image that will be read is returned. You can then piece together an
 *  appropriate texture containing that information for use in your tiled context.
 *
 *  The function will consult the MPSBinaryImageKernel secondaryOffset and clipRect
 *  parameters, to determine the full region read by the function. Other parameters
 *  such as kernelHeight and kernelWidth will be consulted as necessary.  All properties
 *  should be set to intended values prior to calling secondarySourceRegionForDestinationSize:.
 *
 *      Caution: This function operates using global image coordinates, but
 *      -encodeToCommandBuffer:... uses coordinates local to the source and
 *      destination image textures. Consequently, the secondaryOffset and clipRect
 *      attached to this object will need to be updated using a global to
 *      local coordinate transform before -encodeToCommandBuffer:... is
 *      called.
 *
 *  @abstract   Determine the region of the source texture that will be read for a encode operation
 *  @param      destinationSize     The size of the full virtual destination image.
 *  @return     The area in the virtual source image that will be read.
 */
-(MPSRegion) secondarySourceRegionForDestinationSize: (MTLSize) destinationSize;



@end

#endif /* defined(_MetalSmartShaders_MSImageKernel_) */
