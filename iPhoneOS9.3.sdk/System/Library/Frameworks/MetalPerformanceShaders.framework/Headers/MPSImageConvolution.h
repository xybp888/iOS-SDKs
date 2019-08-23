/*!
 *  @header MPSImageConvolution.h
 *  @framework MetalPerformanceShaders
 *  @copyright Copyright (c) 2015 Apple Inc. All rights reserved.
 *
 *  @abstract MetalPerformanceShaders Convolution Filters
 */

#ifndef MPS_MSImageConvolution_h
#define MPS_MSImageConvolution_h

#include <MetalPerformanceShaders/MPSImageKernel.h>

/*!
 *  @class      MPSImageConvolution
 *  @discussion The MPSImageConvolution convolves an image with given filter of odd width and height.
 *              Filter width/height can be either 3,5,7 or 9.
 *              For a separable filter, it will be more performant to run this filter as a 1-dimensional
 *              filter in each dimension separately.
 *              If there are multiple channels in the source image, each channel is processed independently.
 *  
 *  @performance Separable convolution filters may perform better when done in two passes. A convolution filter
 *              is separable if the ratio of filter values between all rows is constant over the whole row. For
 *              example, this edge detection filter:
 *                  @code
 *                      -1      0       1
 *                      -2      0       2
 *                      -1      0       1
 *                  @endcode
 *              can be separated into the product of two vectors:
 *                  @code
 *                      1
 *                      2      x    [-1  0   1]
 *                      1
 *                  @endcode
 *              and consequently can be done as two, one-dimensional convolution passes back to back on the same image. 
 *              In this way, the number of multiplies (ignoring the fact that we could skip zeros here) is reduced from
 *              3*3=9 to 3+3 = 6. There are similar savings for addition. For large filters, the savings can be profound.
 *
 */

NS_CLASS_AVAILABLE( NA, 9_0  )
@interface  MPSImageConvolution : MPSUnaryImageKernel

/*! @property kernelHeight
 *  @abstract  The height of the filter window. Must be an odd number.
 */
@property (readonly, nonatomic)   NSUInteger  kernelHeight;

/*! @property kernelWidth
 *  @abstract  The width of the filter window. Must be an odd number.
 */
@property (readonly, nonatomic)   NSUInteger  kernelWidth;


/*! @property    bias
 *  @discussion  The bias is a value to be added to convolved pixel before it is converted back to the storage format.
 *               It can be used to convert negative values into a representable range for a unsigned MTLPixelFormat.
 *               For example, many edge detection filters produce results in the range [-k,k]. By scaling the filter
 *               weights by 0.5/k and adding 0.5, the results will be in range [0,1] suitable for use with unorm formats. 
 *               It can be used in combination with renormalization of the filter weights to do video ranging as part 
 *               of the convolution effect. It can also just be used to increase the brightness of the image.
 *
 *               Default value is 0.0f.
 */
@property (readwrite, nonatomic) float bias;

/*!
 *  @abstract  Initialize a convolution filter
 *  @param      device          The device the filter will run on
 *  @param      kernelWidth     the width of the kernel
 *  @param      kernelHeight    the height of the kernel
 *  @param      kernelWeights   A pointer to an array of kernelWidth * kernelHeight values to be used as the kernel.
 *                              These are in row major order.
 *  @return     A valid MPSImageConvolution object or nil, if failure.
 */

-(nonnull instancetype) initWithDevice: (nonnull id <MTLDevice>) device
                           kernelWidth: (NSUInteger)kernelWidth
                          kernelHeight: (NSUInteger)kernelHeight
                               weights: (nonnull const float*)kernelWeights     NS_DESIGNATED_INITIALIZER;


@end


/*!
 *  @class      MPSImageBox
 *  @discussion The MPSImageBox convolves an image with given filter of odd width and height. The kernel elements
 *              all have equal weight, achieving a blur effect. (Each result is the unweighted average of the
 *              surrounding pixels.) This allows for much faster algorithms, espcially for for larger blur radii.
 *              The box height and width must be odd numbers. The box blur is a separable filter. The implementation 
 *              is aware of this and will act accordingly to give best performance for multi-dimensional blurs.
 */

NS_CLASS_AVAILABLE( NA, 9_0  )
@interface  MPSImageBox : MPSUnaryImageKernel


/*! @property kernelHeight
 *  @abstract  The height of the filter window.
 */
@property (readonly, nonatomic)   NSUInteger  kernelHeight;

/*! @property kernelWidth
 *  @abstract  The width of the filter window.
 */
@property (readonly, nonatomic)   NSUInteger  kernelWidth;

/*! @abstract   Initialize a filter for a particular kernel size and device
 *  @param      device  The device the filter will run on
 *  @param      kernelWidth  the width of the kernel.  Must be an odd number.
 *  @param      kernelHeight the height of the kernel. Must be an odd number.
 *  @return     A valid object or nil, if failure.
 */

-(nonnull instancetype) initWithDevice: (nonnull id <MTLDevice>) device
                           kernelWidth: (NSUInteger)kernelWidth
                          kernelHeight: (NSUInteger)kernelHeight        NS_DESIGNATED_INITIALIZER;

/* You must use initWithDevice:kernelWidth:kernelHeight: instead. */
-(nonnull instancetype) initWithDevice:(nonnull id<MTLDevice>)device    NS_UNAVAILABLE;
@end

/*!
 *  @class      MPSImageTent
 *  @discussion The box filter, while fast, may yield square-ish looking blur effects. However, multiple
 *              passes of the box filter tend to smooth out with each additional pass. For example, two 3-wide
 *              box blurs produces the same effective convolution as a 5-wide tent blur:
 *              @code
 *                      1   1   1
 *                          1   1   1
 *                      +       1   1   1
 *                      =================
 *                      1   2   3   2   1
 *              @endcode
 *              Addition passes tend to approximate a gaussian line shape.
 *
 *              The MPSImageTent convolves an image with a tent filter. These form a tent shape with incrementally
 *              increasing sides, for example:
 *
 *                  1   2   3   2   1
 *
 *
 *                  1   2   1
 *                  2   4   2
 *                  1   2   1
 *
 *              Like the box filter, this arrangement allows for much faster algorithms, espcially for for larger blur
 *              radii but with a more pleasing appearance.
 *
 *              The tent blur is a separable filter. The implementation is aware of this and will act accordingly
 *              to give best performance for multi-dimensional blurs.
 */
@interface MPSImageTent : MPSImageBox

@end

/*!
 *  @class      MPSImageGaussianBlur
 *  @discussion The MPSImageGaussianBlur convolves an image with gaussian of given sigma in both x and y direction.
 *
 *                  The MPSImageGaussianBlur utilizes a very fast algorith that typically runs at approximately
 *                  1/2 of copy speeds. Notably, it is faster than either the tent or box blur except perhaps
 *                  for very large filter windows. Mathematically, it is an approximate gaussian. Some
 *                  non-gaussian behavior may be detectable with advanced analytical methods such as FFT.  
 *                  If a analytically clean gaussian filter is required, please use the MPSImageConvolution 
 *                  filter instead with an appropriate set of weights. The MPSImageGaussianBlur is intended
 *                  to be suitable for all common image processing needs demanding ~10 bits of precision or
 *                  less.
 */
NS_CLASS_AVAILABLE( NA, 9_0  )
@interface  MPSImageGaussianBlur : MPSUnaryImageKernel

/*! @abstract   Initialize a gaussian blur filter for a particular sigma and device
 *  @param      device  The device the filter will run on
 *  @param      sigma   The standard deviation of gaussian blur filter. 
 *                      Gaussian weight, centered at 0, at integer grid i is given as 
 *                            w(i) = 1/sqrt(2*pi*sigma) * exp(-i^2/2*sigma^2)
 *                      If we take cut off at 1% of w(0) (max weight) beyond which weights
 *                      are considered 0, we have 
 *                              ceil (sqrt(-log(0.01)*2)*sigma) ~ ceil(3.7*sigma) 
 *                      as rough estimate of filter width
 *  @return     A valid object or nil, if failure.
 */

-(nonnull instancetype) initWithDevice: (nonnull id <MTLDevice>) device
                                 sigma: (float)sigma                   NS_DESIGNATED_INITIALIZER;

/* You must use initWithDevice:sigma: instead. */
-(nonnull instancetype) initWithDevice:(nonnull id<MTLDevice>)device    NS_UNAVAILABLE;

/*! @property sigma
 *  @abstract Read-only sigma value with which filter was created
 */
@property (readonly, nonatomic) float sigma;

@end

/*!
 *  @class      MPSImageSobel
 *  @discussion The MPSImageSobel implements the Sobel filter.
 *              When the color model (e.g. RGB, two-channel, grayscale, etc.) of source 
 *              and destination textures match, the filter is applied to each channel 
 *              separately. If the destination is monochrome (single channel) but source 
 *              multichannel, the pixel values are converted to grayscale before applying Sobel
 *              operator using the linear gray color transform vector (v).
 *
 *                  Luminance = v[0] * pixel.x + v[1] * pixel.y + v[2] * pixel.z;
 */
NS_CLASS_AVAILABLE( NA, 9_0  )
@interface  MPSImageSobel : MPSUnaryImageKernel

/*! @abstract   Initialize a Sobel filter on a given device using the default color 
 *              transform. Default: BT.601/JPEG {0.299f, 0.587f, 0.114f}
 *
 *              For non-default conversion matrices, use -initWithDevice:linearGrayColorTransform:
 *
 *  @param      device  The device the filter will run on
 *  @return     A valid object or nil, if failure.
 */
-(nonnull instancetype) initWithDevice: (nonnull id <MTLDevice>) device;

/*! @abstract   Initialize a Sobel filter on a given device with a non-default color transform
 *  @param      device          The device the filter will run on
 *  @param      transform       Array of three floats describing the rgb to gray scale color transform.
 *
 *                          Luminance = transform[0] * pixel.x + transform[1] * pixel.y + transform[2] * pixel.z;
 *
 *  @return     A valid object or nil, if failure.
 */
-(nonnull instancetype) initWithDevice: (nonnull id <MTLDevice>) device
              linearGrayColorTransform: (nonnull const float *) transform      NS_DESIGNATED_INITIALIZER;

/*! @property    colorTransform
 *  @discussion  Returns a pointer to the array of three floats used to convert RGBA, RGB or RG images
 *               to the destination format when the destination is monochrome.
 */
@property (readonly, nonatomic, nonnull) const float* colorTransform;

@end  /* MPSImageSobel */

#endif    /* MPS_MSImageConvolution_h */
