/*!
 *  @header MPSCNN.h
 *  @framework MetalPerformanceShaders.framework
 *
 *  @copyright Copyright (c) 2015 Apple Inc. All rights reserved.
 *  @discussion Metal Performance Shaders CNN kernels
 */

#ifndef MPS_MPSCNN_h
#define MPS_MPSCNN_h

#include <MetalPerformanceShaders/MPSKernel.h>
#include <MetalPerformanceShaders/MPSImage.h>
#include <simd/simd.h>

#ifdef __cplusplus
extern "C" {
#endif


#pragma mark MPSCNNKernel


/*!
 *  @class      MPSCNNKernel
 *  @dependency This depends on Metal.framework
 *  @abstract   Describes a convolution neural network kernel.
 *  @discussion A MPSCNNKernel consumes one MPSImage and produces one MPSImage.
 *
 *              The region overwritten in the destination MPSImage is described 
 *              by the clipRect.  The top left corner of the region consumed (ignoring
 *              adjustments for filter size -- e.g. convolution filter size) is given
 *              by the offset. The size of the region consumed is a function of the 
 *              clipRect size and any subsampling caused by pixel strides at work,
 *              e.g. MPSCNNPooling.strideInPixelsX/Y.  Where the offset + clipRect
 *              would cause a {x,y} pixel address not in the image to be read, the
 *              edgeMode is used to determine what value to read there.
 *
 *              The Z/depth component of the offset, clipRect.origin and clipRect.size
 *              indexes which images to use. If the MPSImage contains only a single image
 *              then these should be offset.z = 0, clipRect.origin.z = 0
 *              and clipRect.size.depth = 1. If the MPSImage contains multiple images,
 *              clipRect.size.depth refers to number of images to process. Both source 
 *              and destination MPSImages must have at least this many images. offset.z 
 *              refers to starting source image index. Thus offset.z + clipRect.size.depth must
 *              be <= source.numberOfImages. Similarly, clipRect.origin.z refers to starting 
 *              image index in destination. So clipRect.origin.z + clipRect.size.depth must be
 *              <= destination.numberOfImage.
 *
 *              destinationFeatureChannelOffset property can be used to control where the MPSKernel will
 *              start writing in feature channel dimension. For example, if the destination image has
 *              64 channels, and MPSKernel outputs 32 channels, by default channels 0-31 of destination
 *              will be populated by MPSKernel. But if we want this MPSKernel to populate channel 32-63
 *              of the destination, we can set destinationFeatureChannelOffset = 32.
 *              A good example of this is concat (concatenation) operation in Tensor Flow. Suppose
 *              we have a src = w x h x Ni which goes through CNNConvolution_0 which produces
 *              output O0 = w x h x N0 and CNNConvolution_1 which produces output O1 = w x h x N1 followed
 *              by concatenation which produces O = w x h x (N0 + N1). We can achieve this by creating
 *              an MPSImage with dimensions O = w x h x (N0 + N1) and using this as destination of
 *              both convolutions as follows
 *                  CNNConvolution0: destinationFeatureChannelOffset = 0, this will output N0 channels starting at
 *                                   channel 0 of destination thus populating [0,N0-1] channels.
 *                  CNNConvolution1: destinationFeatureChannelOffset = N0, this will output N1 channels starting at
 *                                   channel N0 of destination thus populating [N0,N0+N1-1] channels.
 *
 *
 */
MPS_CLASS_AVAILABLE_STARTING( __MAC_10_12, __IPHONE_10_0, __TVOS_10_0)
@interface MPSCNNKernel : MPSKernel


/*! @property   offset
 *  @abstract   The position of the destination clip rectangle origin relative to the source buffer.
 *  @discussion The offset is defined to be the position of clipRect.origin in source coordinates.
 *              Default: {0,0,0}, indicating that the top left corners of the clipRect and source image align.
 *              offset.z is the index of starting source image in batch processing mode.
 *
 *              See Also: @ref subsubsection_mpsoffset
 */
@property (readwrite, nonatomic) MPSOffset                offset;

/*! @property   clipRect
 *  @abstract   An optional clip rectangle to use when writing data. Only the pixels in the rectangle will be overwritten.
 *  @discussion A MTLRegion that indicates which part of the destination to overwrite. If the clipRect does not lie
 *              completely within the destination image, the intersection between clip rectangle and destination bounds is
 *              used.   Default: MPSRectNoClip (MPSKernel::MPSRectNoClip) indicating the entire image.
 *              clipRect.origin.z is the index of starting destination image in batch processing mode. clipRect.size.depth
 *              is the number of images to process in batch processing mode.
 *
 *              See Also: @ref subsubsection_clipRect
 */
@property (readwrite, nonatomic) MTLRegion               clipRect;


/*! @property   destinationFeatureChannelOffset
 *  @abstract   The number of channels in the destination MPSImage to skip before writing output.
 *  @discussion This is the starting offset into the destination image in the feature channel dimension
 *              at which destination data is written.
 *              This allows an application to pass a subset of all the channels in MPSImage as output of MPSKernel.
 *              E.g. Suppose MPSImage has 24 channels and a MPSKernel outputs 8 channels. If
 *              we want channels 8 to 15 of this MPSImage to be used as output, we can set destinationFeatureChannelOffset = 8.
 *              Note that this offset applies independently to each image when the MPSImage
 *              is a container for multiple images and the MPSCNNKernel is processing multiple images (clipRect.size.depth > 1).
 *              The default value is 0 and any value specifed shall be a multiple of 4. If MPSKernel outputs N channels,
 *              destination image MUST have at least destinationFeatureChannelOffset + N channels. Using a destination
 *              image with insufficient number of feature channels result in an error.
 *              E.g. if the MPSCNNConvolution outputs 32 channels, and destination has 64 channels, then it is an error to set
 *              destinationFeatureChannelOffset > 32.
 */
@property (readwrite, nonatomic) NSUInteger              destinationFeatureChannelOffset;

/*! @property   edgeMode
 *  @abstract   The MPSImageEdgeMode to use when texture reads stray off the edge of an image
 *  @discussion Most MPSKernel objects can read off the edge of the source image. This can happen 
 *              because of a negative offset property, because the offset + clipRect.size is larger 
 *              than the source image or because the filter looks at neighboring pixels, such as a 
 *              Convolution filter.   Default:  MPSImageEdgeModeZero. 
 *
 *              See Also: @ref subsubsection_edgemode
 *              Note: For @ref MPSCNNPoolingAverage specifying edge mode @ref MPSImageEdgeModeClamp
 *                      is interpreted as a "shrink-to-edge" operation, which shrinks the effective
 *                      filtering window to remain within the source image borders.
 */
@property (readwrite, nonatomic) MPSImageEdgeMode        edgeMode;


/*!
 *  @abstract   Encode a MPSCNNKernel into a command Buffer.  The operation shall proceed out-of-place.
 *  @param      commandBuffer       A valid MTLCommandBuffer to receive the encoded filter
 *  @param      sourceImage         A valid MPSImage object containing the source image.
 *  @param      destinationImage    A valid MPSImage to be overwritten by result image. destinationImage may not alias sourceImage.
 */
-(void) encodeToCommandBuffer: (nonnull id <MTLCommandBuffer>) commandBuffer
                  sourceImage: (MPSImage * __nonnull) sourceImage
             destinationImage: (MPSImage * __nonnull) destinationImage
                MPS_SWIFT_NAME( encode(commandBuffer:sourceImage:destinationImage:));

/*!
 *  sourceRegionForDestinationSize: is used to determine which region of the
 *  sourceTexture will be read by encodeToCommandBuffer:sourceImage:destinationImage
 *  (and similar) when the filter runs. This information may be needed if the
 *  source image is broken into multiple textures.  The size of the full
 *  (untiled) destination image is provided. The region of the full (untiled)
 *  source image that will be read is returned. You can then piece together an
 *  appropriate texture containing that information for use in your tiled context.
 *
 *  The function will consult the MPSCNNKernel offset and clipRect parameters,
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
-(MPSRegion) sourceRegionForDestinationSize: (MTLSize) destinationSize
                  MPS_SWIFT_NAME( sourceRegion(destinationSize:));
@end


#pragma mark MPSCNNNeuron

/*!
 *  @class      MPSCNNNeuron
 *  @dependency This depends on Metal.framework
 *  @discussion This filter applies a neuron activation function.
                You must use one of the sub-classes of MPSCNNNeuron
 */
MPS_CLASS_AVAILABLE_STARTING( __MAC_10_12, __IPHONE_10_0, __TVOS_10_0)
@interface  MPSCNNNeuron : MPSCNNKernel

@end    /* MPSCNNNeuron */


/*!
 *  @class      MPSCNNNeuronLinear
 *  @dependency This depends on Metal.framework
 *  @discussion Specifies the linear neuron filter. For each pixel, applies the following function: f(x) = a * x + b
 */
MPS_CLASS_AVAILABLE_STARTING( __MAC_10_12, __IPHONE_10_0, __TVOS_10_0)
@interface  MPSCNNNeuronLinear : MPSCNNNeuron

@property (readonly, atomic) float a;
@property (readonly, atomic) float b;

/*!
 *  @abstract  Initialize the linear neuron filter
 *  @param     device   The device the filter will run on
 *  @param     a        Filter property "a". See lass discussion.
 *  @param     b        Filter property "b". See class discussion.
 *  @return    A valid MPSCNNNeuronLinear object or nil, if failure.
 */
-(nonnull instancetype) initWithDevice: (nonnull id <MTLDevice>) device
                                     a: (float) a
                                     b: (float) b NS_DESIGNATED_INITIALIZER;

/*
 * You must use initWithDevice:a:b instead
 */
-(nonnull instancetype) initWithDevice: (nonnull id <MTLDevice>) device NS_UNAVAILABLE;

@end    /* MPSCNNNeuronLinear */


/*!
 *  @class MPSCNNNeuronReLU
 *  @dependency This depends on Metal.framework
 *  @discussion Specifies the ReLU neuron filter.
 *              For each pixel, applies the following function: f(x) = x, if x >= 0
 *                                                                   = a * x if x < 0
 *              This is called Leaky ReLU in literature. Some literature defines
 *              classical ReLU as max(0, x). If you want this behavior, simply pass a = 0
 */
MPS_CLASS_AVAILABLE_STARTING( __MAC_10_12, __IPHONE_10_0, __TVOS_10_0)
@interface  MPSCNNNeuronReLU : MPSCNNNeuron

@property (readonly, atomic) float a;

/*!
 *  @abstract  Initialize the ReLU neuron filter
 *  @param     device           The device the filter will run on
 *  @param     a                Filter property "a". See class discussion.
 *  @return    A valid MPSCNNNeuronReLU object or nil, if failure.
 */
-(nonnull instancetype) initWithDevice: (nonnull id <MTLDevice>) device
                                     a: (float) a NS_DESIGNATED_INITIALIZER;

/*
 * Use initWithDevice:a: instead
 */
-(nonnull instancetype) initWithDevice: (nonnull id <MTLDevice>) device NS_UNAVAILABLE;

@end    /* MPSCNNNeuronReLU */


/*!
 *  @class MPSCNNNeuronSigmoid
 *  @dependency This depends on Metal.framework
 *  @discussion Specifies the sigmoid neuron filter.  For each pixel, applies the following function: f(x) = 1 / (1 + e^-x)
 */
MPS_CLASS_AVAILABLE_STARTING( __MAC_10_12, __IPHONE_10_0, __TVOS_10_0)
@interface  MPSCNNNeuronSigmoid : MPSCNNNeuron

/*!
 *  @abstract  Initialize a neuron filter
 *  @param      device          The device the filter will run on
 *  @return     A valid MPSCNNNeuronSigmoid object or nil, if failure.
 */
-(nonnull instancetype) initWithDevice: (nonnull id <MTLDevice>) device NS_DESIGNATED_INITIALIZER;

@end    /* MPSCNNNeuronSigmoid */


/*!
 *  @class MPSCNNNeuronTanH
 *  @dependency This depends on Metal.framework
 *  @discussion Specifies the hyperbolic tangent neuron filter.
 *              For each pixel, applies the following function: f(x) = a * tanh(b * x)
 */
MPS_CLASS_AVAILABLE_STARTING( __MAC_10_12, __IPHONE_10_0, __TVOS_10_0)
@interface  MPSCNNNeuronTanH : MPSCNNNeuron

@property (readonly, atomic) float a;
@property (readonly, atomic) float b;

/*!
 *  @abstract  Initialize the hyperbolic tangent neuron filter
 *  @param     device           The device the filter will run on
 *  @param     a                Filter property "a". See class discussion.
 *  @param     b                Filter property "b". See class discussion.
 *  @return    A valid MPSCNNNeuronTanH object or nil, if failure.
 */
-(nonnull instancetype) initWithDevice: (nonnull id <MTLDevice>) device
                                     a: (float) a
                                     b: (float) b NS_DESIGNATED_INITIALIZER;
/*
 * Use initWithDevice:a:b: instead
 */
-(nonnull instancetype) initWithDevice: (nonnull id <MTLDevice>) device NS_UNAVAILABLE;

@end    /* MPSCNNNeuronTanH */

/*!
 *  @class MPSCNNNeuronAbsolute
 *  @dependency This depends on Metal.framework
 *  @discussion Specifies the absolute neuron filter.  For each pixel, applies the following function: f(x) = | x |
 */
MPS_CLASS_AVAILABLE_STARTING( __MAC_10_12, __IPHONE_10_0, __TVOS_10_0)
@interface  MPSCNNNeuronAbsolute : MPSCNNNeuron

/*!
 *  @abstract  Initialize a neuron filter
 *  @param      device          The device the filter will run on
 *  @return     A valid MPSCNNNeuronAbsolute object or nil, if failure.
 */
-(nonnull instancetype) initWithDevice: (nonnull id <MTLDevice>) device NS_DESIGNATED_INITIALIZER;

@end    /* MPSCNNNeuronAbsolute */


#pragma mark MPSCNNConvolution


/*!
 *  @class      MPSCNNConvolutionDescriptor
 *  @dependency This depends on Metal.framework
 *  @discussion The MPSCNNConvolutionDescriptor specifies a convolution descriptor
 */
MPS_CLASS_AVAILABLE_STARTING( __MAC_10_12, __IPHONE_10_0, __TVOS_10_0)
@interface MPSCNNConvolutionDescriptor : NSObject <NSCopying>

/*! @property   kernelWidth
 *  @abstract   The width of the filter window.  The default value is 3.
 *              Any positive non-zero value is valid, including even values. 
 *              The position of the left edge of the filter window is given
 *              by offset.x - (kernelWidth>>1)
 */
@property(readwrite, nonatomic) NSUInteger       kernelWidth;

/*! @property   kernelHeight
 *  @abstract   The height of the filter window.  The default value is 3.
 *              Any positive non-zero value is valid, including even values.
 *              The position of the top edge of the filter window is given
 *              by offset.y - (kernelHeight>>1)
 */
@property(readwrite, nonatomic) NSUInteger       kernelHeight;

/*! @property   inputFeatureChannels
 *  @abstract   The number of feature channels per pixel in the input image.
 */
@property(readwrite, nonatomic) NSUInteger       inputFeatureChannels;

/*! @property   outputFeatureChannels
 *  @abstract   The number of feature channels per pixel in the output image.
 */
@property(readwrite, nonatomic) NSUInteger       outputFeatureChannels;

/*! @property   strideInPixelsX
 *  @abstract   The output stride (downsampling factor) in the x dimension. The default value is 1.
 */
@property(readwrite, nonatomic) NSUInteger      strideInPixelsX;

/*! @property   strideInPixelsY
 *  @abstract   The output stride (downsampling factor) in the y dimension. The default value is 1.
 */
@property(readwrite, nonatomic) NSUInteger      strideInPixelsY;

/*! @property   groups
 *  @abstract   Number of groups input and output channels are divided into. The default value is 1.
 *              Groups lets you reduce the parametrization. If groups is set to n, input is divided into n
 *              groups with inputFeatureChannels/n channels in each group. Similarly output is divided into
 *              n groups with outputFeatureChannels/n channels in each group. ith group in input is only 
 *              connected to ith group in output so number of weights (parameters) needed is reduced by factor
 *              of n. Both inputFeatureChannels and outputFeatureChannels must be divisible by n and number of
 *              channels in each group must be multiple of 4.
 */
@property(readwrite, nonatomic) NSUInteger      groups;

/*! @property   neuron
 *  @abstract   MPSCNNNeuron filter to be applied as part of convolution.
 *              Default is nil.
 */
@property(readwrite, nonatomic, retain) const MPSCNNNeuron * __nullable  neuron;

/*!
 *  @abstract   Creates a convolution descriptor with a neuron filter
 *  @param      kernelWidth             The width of the filter window.  Must be > 0. Large values will take a long time.
 *  @param      kernelHeight            The height of the filter window.   Must be > 0. Large values will take a long time.
 *  @param      inputFeatureChannels    The number of feature channels in the input image. Must be >= 1.
 *  @param      outputFeatureChannels   The number of feature channels in the output image. Must be >= 1.
 *  @param      neuronFilter            An optional neuron filter that can be applied to the output of convolution.
 *  @return     A valid MPSCNNConvolutionDescriptor object or nil, if failure.
 */
+(nonnull instancetype) cnnConvolutionDescriptorWithKernelWidth: (NSUInteger) kernelWidth
                                                   kernelHeight: (NSUInteger) kernelHeight
                                           inputFeatureChannels: (NSUInteger) inputFeatureChannels
                                          outputFeatureChannels: (NSUInteger) outputFeatureChannels
                                                   neuronFilter: (const MPSCNNNeuron * __nullable) neuronFilter;

@end    /* MPSCNNConvolutionDescriptor */

/*! @enum       MPSCNNConvolutionFlags
 *  @abstract   Options used to control how kernel weights are stored and used in the CNN kernels.
 *              For future expandability.
 */
#if defined(DOXYGEN)
typedef enum MPSCNNConvolutionFlags
#else
typedef NS_ENUM(NSUInteger, MPSCNNConvolutionFlags)
#endif
{
    /*! Use default options */
    MPSCNNConvolutionFlagsNone      MPS_ENUM_AVAILABLE_STARTING( __MAC_10_12, __IPHONE_10_0, __TVOS_10_0)  = 0,
};

/*!
 *  @class      MPSCNNConvolution
 *  @dependency This depends on Metal.framework
 *  @discussion The MPSCNNConvolution specifies a convolution.
 *              The MPSCNNConvolution convolves the input image with a set of filters, each producing one feature map in the output image.
 */
MPS_CLASS_AVAILABLE_STARTING( __MAC_10_12, __IPHONE_10_0, __TVOS_10_0)
@interface  MPSCNNConvolution : MPSCNNKernel

/*! @property   kernelWidth
 *  @abstract   The width of the filter window.
 *              The position of the left edge of the filter window is given
 *              by offset.x - (kernelWidth>>1)
 */
@property(readonly, nonatomic) NSUInteger       kernelWidth;

/*! @property   kernelHeight
 *  @abstract   The height of the filter window.
 *              Any positive non-zero value is valid, including even values.
 *              The position of the top edge of the filter window is given
 *              by offset.y - (kernelHeight>>1)
 */
@property(readonly, nonatomic) NSUInteger       kernelHeight;

/*! @property   inputFeatureChannels
 *  @abstract   The number of feature channels per pixel in the input image.
 */
@property(readonly, nonatomic) NSUInteger       inputFeatureChannels;

/*! @property   outputFeatureChannels
 *  @abstract   The number of feature channels per pixel in the output image.
 */
@property(readonly, nonatomic) NSUInteger       outputFeatureChannels;

/*! @property   strideInPixelsX
 *  @abstract   The output stride (downsampling factor) in the x dimension. The default value is 1.
 */
@property(readonly, nonatomic) NSUInteger      strideInPixelsX;

/*! @property   strideInPixelsY
 *  @abstract   The output stride (downsampling factor) in the y dimension. The default value is 1.
 */
@property(readonly, nonatomic) NSUInteger      strideInPixelsY;

/*! @property   groups
 *  @abstract   Number of groups input and output channels are divided into.
 */
@property(readonly, nonatomic) NSUInteger      groups;

/*! @property   neuron
 *  @abstract   MPSCNNNeuron filter to be applied as part of convolution.
 *              Can be nil in wich case no neuron activation fuction is applied.
 */
@property(readonly, nonatomic) const MPSCNNNeuron * __nullable  neuron;

/*!
 *  @abstract   Initializes a convolution kernel
 *  @param      device                          The MTLDevice on which this MPSCNNConvolution filter will be used
 *  @param      convolutionDescriptor           A pointer to a MPSCNNConvolutionDescriptor.
 *  @param      kernelWeights                   A pointer to a weights array.  Each entry is a float value. The number of entries is =
 *                                              inputFeatureChannels * outputFeatureChannels * kernelHeight * kernelWidth
 *                                              The layout of filter weight is so that it can be reinterpreted as 4D tensor (array)
 *                                              weight[ outputChannels ][ kernelHeight ][ kernelWidth ][ inputChannels / groups ]
 *                                              Weights are converted to half float (fp16) internally for best performance.
 *  @param      biasTerms                       A pointer to bias terms to be applied to the convolution output.  Each entry is a float value.
 *                                              The number of entries is = numberOfOutputFeatureMaps
 *  @param      flags                           Currently unused. Pass MPSCNNConvolutionFlagsNone
 *
 *  @return     A valid MPSCNNConvolution object or nil, if failure.
 */
-(nonnull instancetype) initWithDevice: (nonnull id <MTLDevice>) device
                 convolutionDescriptor: (const MPSCNNConvolutionDescriptor * __nonnull) convolutionDescriptor
                         kernelWeights: (const float * __nonnull) kernelWeights
                             biasTerms: (const float * __nullable) biasTerms
                                 flags: (MPSCNNConvolutionFlags) flags        NS_DESIGNATED_INITIALIZER;

/*
 * Use initWithDevice:convolutionDescriptor:kernelWeights:biasTerms instead
 */
-(nonnull instancetype) initWithDevice: (nonnull id <MTLDevice>) device NS_UNAVAILABLE;

@end    /* MPSCNNConvolution */
    
/*!
 *  @class      MPSCNNFullyConnected
 *  @dependency This depends on Metal.framework
 *  @discussion The MPSCNNFullyConnected specifies a fully connected convolution layer a.k.a. Inner product 
 *              layer. A fully connected CNN layer is one where every input channel is connected
 *              to every output channel. The kernel width is equal to width of source image
 *              and the kernel height is equal to the height of source image. Width and height of the output 
 *              is 1x1. Thus, it takes a srcW x srcH x Ni MPSCNNImage, convolves it with Weights[No][SrcW][srcH][Ni]
 *              and produces a 1 x 1 x No output. The following must be true:
 *@code
 *                         kernelWidth  == source.width
 *                         kernelHeight == source.height
 *                         clipRect.size.width == 1
 *                         clipRect.size.height == 1
 *@endcode
 *              One can think of a fully connected layer as a matrix multiplication that flattens an image into a vector of length
 *              srcW*srcH*Ni. The weights are arragned in a matrix of dimension No x (srcW*srcH*Ni) for product output vectors
 *              of length No. The strideInPixelsX, strideInPixelsY, and group must be 1. Offset is not applicable and is ignored. 
 *              Since clipRect is clamped to the destination image bounds, if the destination is 1x1, one doesn't need to set the
 *              clipRect.
 *
 *              Note that one can implement an inner product using MPSCNNConvolution by setting
 *@code
 *                     offset = (kernelWidth/2,kernelHeight/2)
 *                     clipRect.origin = (ox,oy), clipRect.size = (1,1)
 *                     strideX = strideY = group = 1
 *@endcode
 *              However, using the MPSCNNFullyConnected for this is better for performance as it lets us choose the most 
 *              performant method which may not be possible when using a general convolution. For example,
 *              we may internally use matrix multiplication or special reduction kernels for a specific platform.
*/
MPS_CLASS_AVAILABLE_STARTING( __MAC_10_12, __IPHONE_10_0, __TVOS_10_0)
@interface  MPSCNNFullyConnected : MPSCNNConvolution

/*!
 *  @abstract   Initializes a fully connected kernel.
 *
 *  @param      device                          The MTLDevice on which this MPSCNNFullyConnected filter will be used
 *  @param      fullyConnectedDescriptor        A pointer to a MPSCNNConvolutionDescriptor. strideInPixelsX, strideInPixelsY and group
 *                                              properties of fullyConnectedDescriptor must be set to 1 (default).
 *  @param      kernelWeights                   A pointer to a weights array.  Each entry is a float value. The number of entries is =
 *                                              inputFeatureChannels * outputFeatureChannels * kernelHeight * kernelWidth
 *                                              The layout of filter weight is so that it can be reinterpreted as 4D tensor (array)
 *                                              weight[ outputChannels ][ kernelHeight ][ kernelWidth ][ inputChannels / groups ]
 *                                              Weights are converted to half float (fp16) internally for best performance.
 *  @param      biasTerms                       A pointer to bias terms to be applied to the convolution output.  Each entry is a float value.
 *                                              The number of entries is = numberOfOutputFeatureMaps
 *  @param      flags                           Currently unused. Pass MPSCNNConvolutionFlagsNone
 *
 *  @return     A valid MPSCNNConvolution object or nil, if failure.
 */
-(nonnull instancetype) initWithDevice: (nonnull id <MTLDevice>) device
                 convolutionDescriptor: (const MPSCNNConvolutionDescriptor * __nonnull) fullyConnectedDescriptor
                         kernelWeights: (const float * __nonnull) kernelWeights
                             biasTerms: (const float * __nullable) biasTerms
                                 flags: (MPSCNNConvolutionFlags) flags  NS_DESIGNATED_INITIALIZER;

/*
 * Use initWithDevice:convolutionDescriptor:kernelWeights:biasTerms instead
 */
-(nonnull instancetype) initWithDevice: (nonnull id <MTLDevice>) device NS_UNAVAILABLE;

/*!
 * NOTE:    The encodeToCommandBuffer API in MPSCNNKernel can be used to encode a inner product kernel to a MTLCommandBuffer.
 *          The source and destination must be MPSImage.
 */

@end    /* MPSCNNFullyConnected */
    
#pragma mark MPSCNNPooling

/*!
 *  @class      MPSCNNPooling
 *  @dependency This depends on Metal.framework
 *  @discussion Pooling is a form of non-linear sub-sampling. Pooling partitions the input image into a set of
 *              rectangles (overlapping or non-overlapping) and, for each such sub-region, outputs a value.
 *              The pooling operation is used in computer vision to reduce the dimensionality of intermediate representations.
 */
MPS_CLASS_AVAILABLE_STARTING( __MAC_10_12, __IPHONE_10_0, __TVOS_10_0)
@interface  MPSCNNPooling : MPSCNNKernel

/*! @property   kernelWidth
 *  @abstract   The width of the filter window
 */
@property(readonly, nonatomic) NSUInteger       kernelWidth;

/*! @property   kernelHeight
 *  @abstract   The height of the filter window
 */
@property(readonly, nonatomic) NSUInteger       kernelHeight;

/*! @property   strideInPixelsX
 *  @abstract   The output stride (downsampling factor) in the x dimension.  The default value is 1.
 */

@property(readonly, nonatomic) NSUInteger      strideInPixelsX;

/*! @property   strideInPixelsY
 *  @abstract   The output stride (downsampling factor) in the y dimension.  The default value is 1.
 */
@property(readonly, nonatomic) NSUInteger      strideInPixelsY;

/*!
 *  @abstract  Initialize a pooling filter
 *  @param      device              The device the filter will run on
 *  @param      kernelWidth         The width of the kernel.  Can be an odd or even value.
 *  @param      kernelHeight        The height of the kernel.  Can be an odd or even value.
 *  @return     A valid MPSCNNPooling object or nil, if failure.
 *
 */
-(nonnull instancetype) initWithDevice: (nonnull id <MTLDevice>) device
                           kernelWidth: (NSUInteger) kernelWidth
                          kernelHeight: (NSUInteger) kernelHeight;

/*!
 *  @abstract  Initialize a pooling filter
 *  @param      device              The device the filter will run on
 *  @param      kernelWidth         The width of the kernel.  Can be an odd or even value.
 *  @param      kernelHeight        The height of the kernel.  Can be an odd or even value.
 *  @param      strideInPixelsX     The output stride (downsampling factor) in the x dimension.
 *  @param      strideInPixelsY     The output stride (downsampling factor) in the y dimension.
 *  @return     A valid MPSCNNPooling object or nil, if failure.
 *
 */
-(nonnull instancetype) initWithDevice: (nonnull id <MTLDevice>) device
                           kernelWidth: (NSUInteger) kernelWidth
                          kernelHeight: (NSUInteger) kernelHeight
                       strideInPixelsX: (NSUInteger) strideInPixelsX
                       strideInPixelsY: (NSUInteger) strideInPixelsY NS_DESIGNATED_INITIALIZER;

/*
 * Use initWithDevice:kernelWidth:kernelHeight:strideInPixelsX:strideInPixelsY: instead
 */
-(nonnull instancetype) initWithDevice: (nonnull id <MTLDevice>) device NS_UNAVAILABLE;


/*!
 *          Pooling window notes
 *          ====================
 *          The encodeToCommandBuffer API in MPSCNNKernel can be used to encode a MPSCNNPooling kernel
 *          to a MTLCommandBuffer. The exact location of the pooling window for each output value is determined
 *          as follows: The pooling window center for the first (top left) output pixel of the clipping
 *          rectangle is at spatial coordinates (offset.x, offset.y) in the input image. From this
 *          the top left corner of the pooling window is at
 *              (offset.x - floor(kernelWidth/2), offset.y - floor(kernelHeight/2)) and
 *          extends of course (kernelWidth, kernelHeight) pixels to the right and down direction, which means
 *          that the last pixel to be included into the pooling window is at:
 *              (offset.x + floor((kernelWidth-1)/2), offset.y + floor((kernelHeight-1)/2)),
 *          so that for even kernel sizes the pooling window is extends one pixel more into the left and up
 *          directions.
 *          The following pooling windows can be then easily deduced from the first one by simple shifting
 *          the source coordinates according to values of @ref strideInPixelsX and @ref strideInPixelsY.
 *          For example the pooling window center w(x,y) for the output value at coordinate (x,y) of the
 *          destination clip rectangle ((x,y) computed wrt. clipping rectangle origin) is at:
 *              w(x,y) = ( offset.x + strideInPixelsX * x , offset.y + strideInPixelsY * y ).
 *
 *          Quite often it is desirable to distribute the pooling windows as evenly as possible in the
 *          input image. As explained above, if offset is zero, then the center of the first pooling
 *          window is at the top left corner of the input image, which means that the left and top stripes
 *          of the pooling window are read from outside the input image boundaries (when filter size is
 *          larger than unity). Also it may mean that some values from the bottom and right stripes are
 *          not included at all in the pooling resulting in loss of valuable information.
 *
 *          A scheme used in some common libraries is to shift the source offset according to the following
 *          formula:
 *              offset.xy += { (int)ceil( ((L.xy - 1) % s.xy) / 2 ), for odd f.xy
 *                           { (int)floor( ((L.xy - 1) % s.xy) / 2 ) + 1, for even f.xy, where
 *          L is the size of the input image (or more accurately the size corresponding to the scaled cliprect
 *          in source coordinates, which commonly coincides with the source image itself),
 *          s.xy is (strideInPixelsX, strideInPixelsY) and f.xy is (kernelWidth, kernelHeight).
 *          This offset distributes the pooling window centers evenly in the effective source cliprect,
 *          when the output size is rounded up wrt. stride ( output size = ceil( input size / stride ) )
 *          and is commonly used in CNN libraries (for example TensorFlow uses this offset scheme
 *          in its maximum pooling implementation tf.nn.max_pool with 'SAME' - padding, for 'VALID'
 *          padding one can simply set offset.xy += floor(f.xy/2) to get the first pooling window
 *          inside the source image completely).
 *          For @ref MPSCNNPoolingMax the way the input image borders are handled (see @ref edgeMode)
 *          can become important: if there are negative values in the source image near the borders of the
 *          image and the pooling window crosses the borders, then using @ref MPSImageEdgeModeZero may
 *          cause the maximum pooling operation to override the negative input data values with zeros
 *          coming from outside the source image borders, resulting in large boundary effects. A simple
 *          way to avoid this is to use @ref MPSImageEdgeModeClamp for @ref edgeMode, which for
 *          @ref MPSCNNPoolingMax effectively causes all pooling windows to remain within the source image.
 *
 *          Below are a couple of examples that can be used to visualize the effects of different
 *          offset values for pooling. The illustrations show the pooling window placements inside a
 *          single feature channel of a source image. In the first examples we use strides that are
 *          larger than the pooling window sizes in order to clarify the placement of each
 *          individual pooling window.
 *@code
 *              Source image: width = 8, height = 5
 *              Destination cliprect: width = 3, height = 2
 *              o - source pixel center, one for each destination cliprect pixel
 *              x - filter taps in the pooling windows
 *@endcode
 *          1) Filter size = 2x2, stride = 3x3, offset = (0,0)
 *@code
 *              x  x     x  x     x  x
 *                |-----------------------|
 *              x |xo|  |x |xo|  |x |xo|  |
 *                |-----------------------|
 *                |  |  |  |  |  |  |  |  |
 *                |-----------------------|
 *              x |x |  |x |x |  |x |x |  |
 *                |-----------------------|
 *              x |xo|  |x |xo|  |x |xo|  |
 *                |-----------------------|
 *                |  |  |  |  |  |  |  |  |
 *                |-----------------------|
 *@endcode
 *          One can use @ref offset to move the pooling windows within the source image:
 *          Using the formula offset.xy += (int)floor( ((L.xy - 1) % s.xy) / 2 ) + 1 from above
 *          for even filter sizes gives:
 *@code
 *              offset.x = floor( (7 % 3) / 2) + 1 = 0 + 1 = 1 and
 *              offset.y = floor( (4 % 3) / 2) + 1 = 0 + 1 = 1.
 *@endcode
 *          2) Filter size = 2x2, stride = 3x3, offset = (1,1)
 *@code
 *                |-----------------------|
 *                |x |x |  |x |x |  |x |x |
 *                |-----------------------|
 *                |x |xo|  |x |xo|  |x |xo|
 *                |-----------------------|
 *                |  |  |  |  |  |  |  |  |
 *                |-----------------------|
 *                |x |x |  |x |x |  |x |x |
 *                |-----------------------|
 *                |x |xo|  |x |xo|  |x |xo|
 *                |-----------------------|
 *@endcode
 *
 *          Our third example shows the placement of additional taps when we increase
 *          the size of the pooling window to 3x3.
 *          In this case the recommended formula for offsets with odd filter sizes gives:
 *@code
 *              offset.x = ceil( (7 % 3) / 2) = 1 and
 *              offset.y = ceil( (4 % 3) / 2) = 1.
 *@endcode
 *          3) Filter size = 3x3, stride = 3x3, offset = (1,1)
 *@code
 *                |-----------------------|
 *                |x |x |x |x |x |x |x |x |x
 *                |-----------------------|
 *                |x |xo|x |x |xo|x |x |xo|x
 *                |-----------------------|
 *                |x |x |x |x |x |x |x |x |x
 *                |-----------------------|
 *                |x |x |x |x |x |x |x |x |x
 *                |-----------------------|
 *                |x |xo|x |x |xo|x |x |xo|x
 *                |-----------------------|
 *                 x  x  x  x  x  x  x  x  x
 *@endcode
 *          In order to avoid large boundary effects with max pooling in examples 1) and 3) the user can use
 *          @ref MPSImageEdgeModeClamp for @ref edgeMode, which has the same effect as constraining the pooling
 *          windows to be confined completely within the source image.
 *
 */

@end    /* MPSCNNPooling */


/*!
 *  @class MPSCNNPoolingMax
 *  @dependency This depends on Metal.framework
 *  @discussion Specifies the max pooling filter.  For each pixel, returns the maximum value of pixels
 *              in the kernelWidth x kernelHeight filter region.
 */
MPS_CLASS_AVAILABLE_STARTING( __MAC_10_12, __IPHONE_10_0, __TVOS_10_0)
@interface  MPSCNNPoolingMax : MPSCNNPooling
@end    /* MPSCNNPoolingMax */


/*!
 *  @class MPSCNNPoolingAverage
 *  @dependency This depends on Metal.framework
 *  @discussion Specifies the average pooling filter.  For each pixel, returns the mean value of pixels
 *              in the kernelWidth x kernelHeight filter region.
 *              When @ref edgeMode is @ref MPSImageEdgeModeClamp the filtering window is shrunk to remain
 #              within the source image borders. What this means is that close to image borders the filtering window
 *              will be smaller in order to fit inside the source image and less values will be used to compute the
 *              average. In case the filtering window is entirely outside the source image border the
 *              outputted value will be zero.
 */
MPS_CLASS_AVAILABLE_STARTING( __MAC_10_12, __IPHONE_10_0, __TVOS_10_0)
@interface  MPSCNNPoolingAverage : MPSCNNPooling
@end    /* MPSCNNPoolingAverage */



#pragma mark MPSCNNNormalization

/*!
 *  @class MPSCNNSpatialNormalization
 *  @dependency This depends on Metal.framework
 *  @discussion Specifies the spatial normalization filter.
 *              The spatial normalization for a feature channel applies the filter over local regions which extend
 *              spatially, but are in separate feature channels (i.e., they have shape 1 x kernelWidth x kernelHeight).
 *              For each feature channel, the function computes the sum of squares of X inside each rectangle, N2(i,j).
 *              It then divides each element of X as follows:
 *                  Y(i,j) = X(i,j) / (delta + alpha/(kw*kh) * N2(i,j))^beta,
 *              where kw and kh are the kernelWidth and the kernelHeight.
 *              It is the end-users responsibility to ensure that the combination of the
 *              parameters delta and alpha does not result in a situation where the denominator
 *              becomes zero - in such situations the resulting pixel-value is undefined.
 */
NS_CLASS_AVAILABLE( 10_12, 10_0 )
@interface MPSCNNSpatialNormalization : MPSCNNKernel

/*! @property   alpha
 *  @abstract   The value of alpha.  Default is 1.0. Must be non-negative.
 */
@property (readwrite, nonatomic) float   alpha;

/*! @property   beta
 *  @abstract   The value of beta.  Default is 5.0
 */
@property (readwrite, nonatomic) float   beta;

/*! @property   delta
 *  @abstract   The value of delta.  Default is 1.0
 */
@property (readwrite, nonatomic) float   delta;

/*! @property   kernelWidth
 *  @abstract   The width of the filter window
 */
@property(readonly, nonatomic) NSUInteger       kernelWidth;

/*! @property   kernelHeight
 *  @abstract   The height of the filter window
 */
@property(readonly, nonatomic) NSUInteger       kernelHeight;

/*!
 *  @abstract  Initialize a spatial normalization filter
 *  @param      device              The device the filter will run on
 *  @param      kernelWidth         The width of the kernel
 *  @param      kernelHeight        The height of the kernel
 *  @return     A valid MPSCNNSpatialNormalization object or nil, if failure.
 *
 *  NOTE:  For now, kernelWidth must be equal to kernelHeight
 */
-(nonnull instancetype) initWithDevice: (nonnull id <MTLDevice>) device
                           kernelWidth: (NSUInteger) kernelWidth
                          kernelHeight: (NSUInteger) kernelHeight NS_DESIGNATED_INITIALIZER;

/*
 * Use initWithDevice:kernelWidth:kernelHeight instead
 */
-(nonnull instancetype) initWithDevice: (nonnull id <MTLDevice>) device NS_UNAVAILABLE;

/*!
 * NOTE:    The encodeToCommandBuffer API in MPSUnaryImageKernel can be used to encode a
 *          MPSCNNSpatialNormalization filter to a MTLCommandBuffer.
 */
@end    /* MPSCNNSpatialNormalization */

/*!
 *  @class MPSCNNLocalContrastNormalization
 *  @dependency This depends on Metal.framework
 *  @discussion Specifies the local contrast normalization filter.
 *              The local contrast normalization is quite similar to spatial normalization
 *              (see @ref MPSCNNSpatialNormalization) in that it applies the filter over local regions which extend
 *              spatially, but are in separate feature channels (i.e., they have shape 1 x kernelWidth x kernelHeight),
 *              but instead of dividing by the local "energy" of the feature, the denominator uses the local variance
 *              of the feature - effectively the mean value of the feature is subtracted from the signal.
 *              For each feature channel, the function computes the variance VAR(i,j) and
 *              mean M(i,j) of X(i,j) inside each rectangle around the spatial point (i,j).
 *
 *              Then the result is computed for each element of X as follows:
 *
 *                  Y(i,j) = pm + ps * ( X(i,j) - p0 * M(i,j)) / (delta + alpha * VAR(i,j))^beta,
 *
 *              where kw and kh are the kernelWidth and the kernelHeight and pm, ps and p0 are parameters that
 *              can be used to offset and scale the result in various ways. For example setting
 *              pm=0, ps=1, p0=1, delta=0, alpha=1.0 and beta=0.5 scales input data so that the result has
 *              unit variance and zero mean, provided that input variance is positive.
 *              It is the end-users responsibility to ensure that the combination of the
 *              parameters delta and alpha does not result in a situation where the denominator
 *              becomes zero - in such situations the resulting pixel-value is undefined. A good way to guard
 *              against tiny variances is to regulate the expression with a small value for delta, for example
 *              delta = 1/1024 = 0.0009765625.
 */
MPS_CLASS_AVAILABLE_STARTING( __MAC_10_12, __IPHONE_10_0, __TVOS_10_0)
@interface MPSCNNLocalContrastNormalization : MPSCNNKernel

/*! @property   alpha
 *  @abstract   The value of alpha.  Default is 1.0
 */
@property (readwrite, nonatomic) float   alpha;

/*! @property   beta
 *  @abstract   The value of beta.  Default is 0.5
 */
@property (readwrite, nonatomic) float   beta;

/*! @property   delta
 *  @abstract   The value of delta.  Default is 1/1024
 */
@property (readwrite, nonatomic) float   delta;

/*! @property   p0
 *  @abstract   The value of p0.  Default is 1.0
 */
@property (readwrite, nonatomic) float   p0;

/*! @property   pm
 *  @abstract   The value of pm.  Default is 0.0
 */
@property (readwrite, nonatomic) float   pm;

/*! @property   ps
 *  @abstract   The value of ps.  Default is 1.0
 */
@property (readwrite, nonatomic) float   ps;


/*! @property   kernelWidth
 *  @abstract   The width of the filter window
 */
@property(readonly, nonatomic) NSUInteger       kernelWidth;

/*! @property   kernelHeight
 *  @abstract   The height of the filter window
 */
@property(readonly, nonatomic) NSUInteger       kernelHeight;

/*!
 *  @abstract  Initialize a local contrast normalization filter
 *  @param      device              The device the filter will run on
 *  @param      kernelWidth         The width of the kernel
 *  @param      kernelHeight        The height of the kernel
 *  @return     A valid MPSCNNLocalContrastNormalization object or nil, if failure.
 *
 *  NOTE:  For now, kernelWidth must be equal to kernelHeight
 */
-(nonnull instancetype) initWithDevice: (nonnull id <MTLDevice>) device
                           kernelWidth: (NSUInteger) kernelWidth
                          kernelHeight: (NSUInteger) kernelHeight NS_DESIGNATED_INITIALIZER;

/*
 * Use initWithDevice:kernelWidth:kernelHeight instead
 */
-(nonnull instancetype) initWithDevice: (nonnull id <MTLDevice>) device NS_UNAVAILABLE;

/*!
 * NOTE:    The encodeToCommandBuffer API in MPSUnaryImageKernel can be used to encode a
 *          MPSCNNLocalContrastNormalization filter to a MTLCommandBuffer.
 */
@end    /* MPSCNNLocalContrastNormalization */


/*!
 *  @class MPSCNNCrossChannelNormalization
 *  @dependency This depends on Metal.framework
 *  @discussion Specifies the normalization filter across feature channels.
 *               This normalization filter applies the filter to a local region across nearby feature channels,
 *              but with no spatial extent (i.e., they have shape kernelSize x 1 x 1).
 *              The normalized output is given by:
 *                  Y(i,j,k) = X(i,j,k) / L(i,j,k)^beta,
 *              where the normalizing factor is:
 *                  L(i,j,k) = delta + alpha/N * (sum_{q in Q(k)} X(i,j,q)^2, where
 *              N is the kernel size. The window Q(k) itself is defined as:
 *                  Q(k) = [max(0, k-floor(N/2)), min(D-1, k+floor((N-1)/2)], where
 *
 *              k is the feature channel index (running from 0 to D-1) and
 *              D is the number of feature channels, and alpha, beta and delta are paremeters.
 *              It is the end-users responsibility to ensure that the combination of the
 *              parameters delta and alpha does not result in a situation where the denominator
 *              becomes zero - in such situations the resulting pixel-value is undefined.
 */
MPS_CLASS_AVAILABLE_STARTING( __MAC_10_12, __IPHONE_10_0, __TVOS_10_0)
@interface MPSCNNCrossChannelNormalization : MPSCNNKernel

/*! @property   alpha
 *  @abstract   The value of alpha.  Default is 1.0. Must be non-negative.
 */
@property (readwrite, nonatomic) float   alpha;

/*! @property   beta
 *  @abstract   The value of beta.  Default is 5.0
 */
@property (readwrite, nonatomic) float   beta;

/*! @property   delta
 *  @abstract   The value of delta.  Default is 1.0
 */
@property (readwrite, nonatomic) float   delta;

/*! @property   kernelSize
 *  @abstract   The size of the square filter window.  Default is 5
 */
@property(readonly, nonatomic) NSUInteger       kernelSize;

/*!
 *  @abstract  Initialize a local response normalization filter in a channel
 *  @param      device              The device the filter will run on
 *  @param      kernelSize          The kernel filter size in each dimension.
 *  @return     A valid MPSCNNCrossFeatureMapNormalization object or nil, if failure.
 *
 */
-(nonnull instancetype) initWithDevice: (nonnull id <MTLDevice>) device
                            kernelSize: (NSUInteger) kernelSize NS_DESIGNATED_INITIALIZER;

/*
 * Use initWithDevice:kernelSize: instead
 */
-(nonnull instancetype) initWithDevice: (nonnull id <MTLDevice>) device NS_UNAVAILABLE;

/*!
 * NOTE:    The encodeToCommandBuffer API in MPSUnaryImageKernel can be used to encode a
 *          MPSCNNCrossChannelNormalization filter to a MTLCommandBuffer.
 */
@end    /* MPSCNNCrossChannelNormalization */


/*!
 *  @class      MPSCNNSoftMax
 *  @dependency This depends on Metal.framework
 *  @discussion The softmax filter is a neural transfer function and is useful for classification tasks.
 *              The softmax filter is applied across feature channels and in a convolutional manner at all
 *              spatial locations. The softmax filter can be seen as the combination of an
 *              activation function (exponential) and a normalization operator.
 *              For each feature channel per pixel in an image in a feature map, the softmax filter computes the following:
 *                  result channel in pixel = exp(pixel(x,y,k))/sum(exp(pixel(x,y,0)) ... exp(pixel(x,y,N-1))
 *                      where N is the number of feature channels
 *
 */
MPS_CLASS_AVAILABLE_STARTING( __MAC_10_12, __IPHONE_10_0, __TVOS_10_0)
@interface MPSCNNSoftMax : MPSCNNKernel

@end    /* MPSCNNSoftMax */

/*!
 *  @class      MPSCNNLogSoftMax
 *  @dependency This depends on Metal.framework
 *  @discussion The logarithmic softmax filter can be achieved by taking the natural logarithm of the
 *              the result of the softmax filter. The results are often used to construct a loss function to be
 *              minimized when training neural networks.
 *              For each feature channel per pixel in an image in a feature map, the logarithmic softmax filter
 *              computes the following:
 *                  result channel in pixel = pixel(x,y,k)) - ln{sum(exp(pixel(x,y,0)) ... exp(pixel(x,y,N-1))}
 *                      where N is the number of feature channels and y = ln{x} satisfies e^y = x.
 *
 */
MPS_CLASS_AVAILABLE_STARTING( __MAC_10_12, __IPHONE_10_0, __TVOS_10_0)
@interface MPSCNNLogSoftMax : MPSCNNKernel

@end    /* MPSCNNLogSoftMax */




#ifdef __cplusplus
}       /* extern "C" */
#endif


#endif  /* MPS_MPSCNN_h */


