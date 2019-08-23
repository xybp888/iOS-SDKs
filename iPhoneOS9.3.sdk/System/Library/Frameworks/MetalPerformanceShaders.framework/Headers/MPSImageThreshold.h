/*!
 *  @header MPSImageThreshold.h
 *  @framework MetalPerformanceShaders
 *
 *  @copyright Copyright (c) 2015 Apple Inc. All rights reserved.
 *  @abstract Metal Image thresholding filters
 */

#ifndef MPS_MPSImageThreshold_h
#define MPS_MPSImageThreshold_h

#include <MetalPerformanceShaders/MPSImageKernel.h>

/*!
 *  @class      MPSImageThresholdBinary
 *  @discussion The MIThreshold filter applies a fixed-level threshold to each pixel in the image.
 *              The threshold functions convert a single channel image to a binary image.
 *              If the input image is not a single channel image, convert the inputimage to a single channel
 *              luminance image using the linearGrayColorTransform and then apply the threshold.
 *              The ThresholdBinary function is:
 *                  destinationPixelValue = sourcePixelValue > thresholdValue ? maximumValue : 0
 */
NS_CLASS_AVAILABLE( NA, 9_0  )
@interface  MPSImageThresholdBinary : MPSUnaryImageKernel

/*!
 *  @abstract   initialize a MPSImageThresholdBinary filter
 *  @param      device          The device the filter will run on
 *  @param      thresholdValue  The threshold value to use
 *  @param      maximumValue    The maximum value to use
 *  @param      transform       This matrix is an array of 3 floats.
 *                              The default if no transform is specifed is BT.601/JPEG: {0.299f, 0.587f, 0.114f};
 */
-(nonnull instancetype) initWithDevice: (nonnull id <MTLDevice>) device
                        thresholdValue: (float)thresholdValue
                          maximumValue: (float)maximumValue
              linearGrayColorTransform: (nullable const float *)transform       NS_DESIGNATED_INITIALIZER;

/* You must use initWithDevice:thresholdValue:maximumValue:linearGrayColorTransform: instead */
-(nonnull instancetype) initWithDevice:(nonnull id<MTLDevice>)device            NS_UNAVAILABLE;

/*! @property thresholdValue
 *  @discussion The threshold value used to init the threshold filter
 */
@property (readonly, nonatomic) float   thresholdValue;

/*! @property maximumValue
 *  @discussion The maximum value used to init the threshold filter
 */
@property (readonly, nonatomic) float   maximumValue;

/*! @property transform
 *  @discussion The color transform used to init the threshold filter
 */
@property (readonly, nonatomic, nonnull) const float *transform;


@end  /* MPSImageThresholdBinary */

/*!
 *  @class      MPSImageThresholdBinaryInverse
 *  @discussion The MPSImageThresholdBinaryInverse filter applies a fixed-level threshold to each pixel in the image.
 *              The threshold functions convert a single channel image to a binary image.
 *              If the input image is not a single channel image, convert the inputimage to a single channel
 *              luminance image using the linearGrayColorTransform and then apply the threshold.
 *              The ThresholdBinaryInverse function is:
 *                  destinationPixelValue = sourcePixelValue > thresholdValue ? 0 : maximumValue
 */
NS_CLASS_AVAILABLE( NA, 9_0  )
@interface  MPSImageThresholdBinaryInverse : MPSUnaryImageKernel

/*!
 *  @abstract   initialize a MPSImageThresholdBinaryInverse filter
 *  @param      device          The device the filter will run on
 *  @param      thresholdValue  The threshold value to use
 *  @param      maximumValue    The maximum value to use
 *  @param      transform       This matrix is an array of 3 floats.
 *                              The default if no transform is specifed is BT.601/JPEG: {0.299f, 0.587f, 0.114f};
 */
-(nonnull instancetype) initWithDevice: (nonnull id <MTLDevice>) device
                        thresholdValue: (float)thresholdValue
                          maximumValue: (float)maximumValue
              linearGrayColorTransform: (nullable const float *)transform       NS_DESIGNATED_INITIALIZER;

/* You must use initWithDevice:thresholdValue:maximumValue:linearGrayColorTransform: instead */
-(nonnull instancetype) initWithDevice:(nonnull id<MTLDevice>)device            NS_UNAVAILABLE;

/*! @property thresholdValue
 *  @discussion The threshold value used to init the threshold filter
 */
@property (readonly, nonatomic) float   thresholdValue;

/*! @property maximumValue
 *  @discussion The maximum value used to init the threshold filter
 */
@property (readonly, nonatomic) float   maximumValue;

/*! @property transform
 *  @discussion The color transform used to init the threshold filter
 */
@property (readonly, nonatomic, nonnull) const float *transform;

@end  /* MPSImageThresholdBinaryInverse */

/*!
 *  @class      MPSImageThresholdTruncate
 *  @discussion The MPSImageThresholdTruncate filter applies a fixed-level threshold to each pixel in the image:
 *              The threshold functions convert a single channel image to a binary image.
 *              If the input image is not a single channel image, convert the inputimage to a single channel
 *              luminance image using the linearGrayColorTransform and then apply the threshold.
 *              The ThresholdTruncate function is:
 *                  destinationPixelValue = sourcePixelValue > thresholdValue ? thresholdValue : sourcePixelValue
 */
NS_CLASS_AVAILABLE( NA, 9_0  )
@interface  MPSImageThresholdTruncate : MPSUnaryImageKernel

/*! 
 *  @abstract   initialize a MPSImageThresholdTruncate filter
 *  @param      device          The device the filter will run on
 *  @param      thresholdValue The threshold value to use
 *  @param      transform       This matrix is an array of 3 floats.
 *                              The default if no transform is specifed is BT.601/JPEG: {0.299f, 0.587f, 0.114f};
 */
-(nonnull instancetype) initWithDevice: (nonnull id <MTLDevice>) device
                        thresholdValue: (float)thresholdValue
              linearGrayColorTransform: (nullable const float *)transform       NS_DESIGNATED_INITIALIZER;

/* You must use initWithDevice:thresholdValue:linearGrayColorTransform: instead */
-(nonnull instancetype) initWithDevice:(nonnull id<MTLDevice>)device            NS_UNAVAILABLE;

/*! @property thresholdValue
 *  @discussion The threshold value used to init the threshold filter
 */
@property (readonly, nonatomic) float   thresholdValue;

/*! @property transform
 *  @discussion The color transform used to init the threshold filter
 */
@property (readonly, nonatomic, nonnull) const float *transform;

@end  /* MPSImageThresholdTruncate */


/*!
 *  @class      MPSImageThresholdToZero
 *  @discussion The MPSImageThresholdToZero filter applies a fixed-level threshold to each pixel in the image.
 *              The threshold functions convert a single channel image to a binary image.
 *              If the input image is not a single channel image, convert the inputimage to a single channel
 *              luminance image using the linearGrayColorTransform and then apply the threshold.
 *              The ThresholdToZero function is:
 *                  destinationPixelValue = sourcePixelValue > thresholdValue ? sourcePixelValue : 0
 */
NS_CLASS_AVAILABLE( NA, 9_0  )
@interface  MPSImageThresholdToZero : MPSUnaryImageKernel

/*!
 *  @abstract   initialize a MPSImageThresholdToZero filter
 *  @param      device          The device the filter will run on
 *  @param      thresholdValue  The threshold value to use
 *  @param      transform       This matrix is an array of 3 floats.
 *                              The default if no transform is specifed is BT.601/JPEG: {0.299f, 0.587f, 0.114f};
 */
-(nonnull instancetype) initWithDevice: (nonnull id <MTLDevice>) device
                        thresholdValue: (float)thresholdValue
              linearGrayColorTransform: (nullable const float *)transform       NS_DESIGNATED_INITIALIZER;

/* You must use initWithDevice:thresholdValue:linearGrayColorTransform: instead */
-(nonnull instancetype) initWithDevice:(nonnull id<MTLDevice>)device            NS_UNAVAILABLE;

/*! @property thresholdValue
 *  @discussion The threshold value used to init the threshold filter
 */
@property (readonly, nonatomic) float   thresholdValue;

/*! @property transform
 *  @discussion The color transform used to init the threshold filter
 */
@property (readonly, nonatomic, nonnull) const float *transform;

@end  /* MPSImageThresholdToZero */

/*!
 *  @class      MPSImageThresholdToZeroInverse
 *  @discussion The MPSImageThresholdToZeroInverse filter applies a fixed-level threshold to each pixel in the image.
 *              The threshold functions convert a single channel image to a binary image.
 *              If the input image is not a single channel image, convert the inputimage to a single channel
 *              luminance image using the linearGrayColorTransform and then apply the threshold.
 *              The ThresholdToZeroINverse function is:
 *                  destinationPixelValue = sourcePixelValue > thresholdValue ? 0 : sourcePixelValue
 */
NS_CLASS_AVAILABLE( NA, 9_0  )
@interface  MPSImageThresholdToZeroInverse : MPSUnaryImageKernel

/*!
 *  @abstract  initialize a MPSImageThresholdToZeroInverse filter
 *  @param      device          The device the filter will run on
 *  @param      thresholdValue The threshold value to use
 *  @param      transform       This matrix is an array of 3 floats.
 *                              The default if no transform is specifed is BT.601/JPEG: {0.299f, 0.587f, 0.114f};
 */
-(nonnull instancetype) initWithDevice: (nonnull id <MTLDevice>) device
                        thresholdValue: (float)thresholdValue
              linearGrayColorTransform: (nullable const float *)transform       NS_DESIGNATED_INITIALIZER;

/* You must use initWithDevice:thresholdValue:linearGrayColorTransform: instead */
-(nonnull instancetype) initWithDevice:(nonnull id<MTLDevice>)device            NS_UNAVAILABLE;

/*! @property thresholdValue
 *  @discussion The threshold value used to init the threshold filter
 */
@property (readonly, nonatomic) float   thresholdValue;

/*! @property transform
 *  @discussion The color transform used to init the threshold filter
 */
@property (readonly, nonatomic, nonnull) const float *transform;

@end  /* MPSImageThresholdToZeroInverse */

#endif  /* MPS_MSImageThreshold_h */
