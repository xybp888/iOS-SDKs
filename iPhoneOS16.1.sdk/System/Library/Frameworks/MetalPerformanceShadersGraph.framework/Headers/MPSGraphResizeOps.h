//
//  MPSGraphResizeOps.h
//  MPSGraph
//
//  Created on 3/13/20.
//  Copyright © 2020 Apple Inc. All rights reserved.
//

#ifndef MPSGraphResizeOps_h
#define MPSGraphResizeOps_h

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSUInteger, MPSGraphResizeMode)
{
    MPSGraphResizeNearest        MPS_ENUM_AVAILABLE_STARTING(macos(11.0), ios(14.0), tvos(14.0)) MPS_SWIFT_NAME(nearest)   =  0L,
    MPSGraphResizeBilinear       MPS_ENUM_AVAILABLE_STARTING(macos(11.0), ios(14.0), tvos(14.0))                           =  1L,
};

typedef NS_ENUM(NSUInteger, MPSGraphResizeNearestRoundingMode)
{
    MPSGraphResizeNearestRoundingModeRoundPreferCeil        MPS_ENUM_AVAILABLE_STARTING(macos(13.0), ios(16.0), tvos(16.0)) MPS_SWIFT_NAME(roundPreferCeil)   =  0L,
    MPSGraphResizeNearestRoundingModeRoundPreferFloor       MPS_ENUM_AVAILABLE_STARTING(macos(13.0), ios(16.0), tvos(16.0))                                    =  1L,
    MPSGraphResizeNearestRoundingModeCeil                   MPS_ENUM_AVAILABLE_STARTING(macos(13.0), ios(16.0), tvos(16.0))                                    =  2L,
    MPSGraphResizeNearestRoundingModeFloor                  MPS_ENUM_AVAILABLE_STARTING(macos(13.0), ios(16.0), tvos(16.0))                                    =  3L,
};

MPS_CLASS_AVAILABLE_STARTING(macos(11.0), ios(14.0), tvos(14.0))
@interface MPSGraph(MPSGraphResizeOps)

/*!
 *  @abstract   Create Resize op and return the result tensor
 *  @discussion Resamples input images to given size. Result images will be distorted if size is of different aspect ratio.
 *              Resize supports the following modes:
 *                  Nearest Neighbor - values are interpolated using the closest neighbor pixel
 *                  Bilinear - values are computed using bilinear interpolation of 4 neighboring pixels
 *
 *              Destination indices are computed using direct index scaling by default, with no offset added.
 *              If the centerResult parameter is true, the destination indices will be scaled and shifted to be centered
 *              on the input image.
 *              If the alignCorners parameter is true, the corners of the result images will match the input images.
 *              Scaling will be modified to a factor of (size - 1) / (inputSize - 1). When alignCorners is true, the
 *              centerResult parameter does nothing.
 *
 *              In order to achieve the same behavior as OpenCV's resize and TensorFlowV2's resize,
 *              @code
 *                  centerResult = YES;
 *                  alginCorners = NO;
 *              @endcode
 *
 *              To achieve the same behavior as TensorFlowV1 resize
 *              @code
 *                  centerResult = NO;
 *              @endcode
 *
 *  @param      imagesTensor    Tensor containing input images.
 *  @param      size                      A 2-element shape as [newHeight, newWidth]
 *  @param      mode                      The resampling mode to use.  If nearest sampling is specifed, RoundPreferCeil mode will be used.
 *  @param      centerResult    Controls if the result image is centered on the input image. When NO, the result will have the top left corner aligned
 *  @param      alignCorners    When YES, the result image will have the same value as the input image in the corners
 *  @param      layout                  Specifies what layout the provided tensor is in. The returned tensor will follow the same layout.
 *                            Valid layouts are NHWC, NCHW, HWC, CHW, and HW.
 *  @param      name                      The name for the operation
 *
 *  @return     A valid MPSGraphTensor object
 */
-(MPSGraphTensor *) resizeTensor:(MPSGraphTensor *) imagesTensor
                            size:(MPSShape *) size
                            mode:(MPSGraphResizeMode) mode
                    centerResult:(BOOL) centerResult
                    alignCorners:(BOOL) alignCorners
                          layout:(MPSGraphTensorNamedDataLayout) layout
                            name:(NSString * _Nullable) name
MPS_SWIFT_NAME( resize(_:size:mode:centerResult:alignCorners:layout:name:) );

/*!
 *  @abstract   Create Resize op and return the result tensor
 *  @discussion Resamples input images to given size. Result images will be distorted if size is of different aspect ratio.
 *              Resize supports the following modes:
 *                  Nearest Neighbor - values are interpolated using the closest neighbor pixel
 *                  Bilinear - values are computed using bilinear interpolation of 4 neighboring pixels
 *
 *              Destination indices are computed using direct index scaling by default, with no offset added.
 *              If the centerResult parameter is true, the destination indices will be scaled and shifted to be centered
 *              on the input image.
 *              If the alignCorners parameter is true, the corners of the result images will match the input images.
 *              Scaling will be modified to a factor of (size - 1) / (inputSize - 1). When alignCorners is true, the
 *              centerResult parameter does nothing.
 *
 *              In order to achieve the same behavior as OpenCV's resize and TensorFlowV2's resize,
 *              @code
 *                  centerResult = YES;
 *                  alginCorners = NO;
 *              @endcode
 *
 *              To achieve the same behavior as TensorFlowV1 resize
 *              @code
 *                  centerResult = NO;
 *              @endcode
 *
 *  @param      imagesTensor                   Tensor containing input images.
 *  @param      size                                     1D Int32 or Int64 tensor. A 2-element shape as [newHeight, newWidth]
 *  @param      mode                                     The resampling mode to use. If nearest sampling is specifed, RoundPreferCeil mode will be used.
 *  @param      centerResult                    Controls if the result image is centered on the input image. When NO, the result will have the top left corner aligned
 *  @param      alignCorners                    When YES, the result image will have the same value as the input image in the corners
 *  @param      layout                                  Specifies what layout the provided tensor is in. The returned tensor will follow the same layout.
 *                                   Valid layouts are NHWC, NCHW, HWC, CHW, and HW.
 *  @param      name                                      The name for the operation
 *
 *  @return     A valid MPSGraphTensor object
 */
-(MPSGraphTensor *) resizeTensor:(MPSGraphTensor *) imagesTensor
                      sizeTensor:(MPSGraphTensor *) size
                            mode:(MPSGraphResizeMode) mode
                    centerResult:(BOOL) centerResult
                    alignCorners:(BOOL) alignCorners
                          layout:(MPSGraphTensorNamedDataLayout) layout
                            name:(NSString * _Nullable) name
MPS_AVAILABLE_STARTING(macos(12.0), ios(15.0), tvos(15.0))
MPS_SWIFT_NAME( resize(_:sizeTensor:mode:centerResult:alignCorners:layout:name:) );

/*!
 *  @abstract   Create Resize op and return the result tensor
 *  @discussion Resamples input images to given size using nearest neighbor sampling. This API allows for
 *              the rounding mode to be specified.
 *              See above discussion for more details.
 *
 *  @param      imagesTensor                   Tensor containing input images.
 *  @param      size                                     1D Int32 or Int64 tensor. A 2-element shape as [newHeight, newWidth]
 *  @param      nearestRoundingMode    The rounding mode to use when using nearest resampling. Default is roundPreferCeil.
 *  @param      centerResult                    Controls if the result image is centered on the input image. When NO, the result will have the top left corner aligned
 *  @param      alignCorners                    When YES, the result image will have the same value as the input image in the corners
 *  @param      layout                                  Specifies what layout the provided tensor is in. The returned tensor will follow the same layout.
 *                                   Valid layouts are NHWC, NCHW, HWC, CHW, and HW.
 *  @param      name                                      The name for the operation
 *
 *  @return     A valid MPSGraphTensor object
 */
-(MPSGraphTensor *) resizeNearestWithTensor:(MPSGraphTensor *) imagesTensor
                                 sizeTensor:(MPSGraphTensor *) size
                        nearestRoundingMode:(MPSGraphResizeNearestRoundingMode) nearestRoundingMode
                               centerResult:(BOOL) centerResult
                               alignCorners:(BOOL) alignCorners
                                     layout:(MPSGraphTensorNamedDataLayout) layout
                                       name:(NSString * _Nullable) name
MPS_AVAILABLE_STARTING(macos(13.0), ios(16.0), tvos(16.0))
MPS_SWIFT_NAME( resizeNearest(_:sizeTensor:nearestRoundingMode:centerResult:alignCorners:layout:name:) );

/*!
 *  @abstract   Create Resize op and return the result tensor
 *  @discussion Resamples input images to given size using bilinear sampling.
 *              See above discussion for more details.
 *
 *  @param      imagesTensor                   Tensor containing input images.
 *  @param      size                                     1D Int32 or Int64 tensor. A 2-element shape as [newHeight, newWidth]
 *  @param      centerResult                    Controls if the result image is centered on the input image. When NO, the result will have the top left corner aligned
 *  @param      alignCorners                    When YES, the result image will have the same value as the input image in the corners
 *  @param      layout                                  Specifies what layout the provided tensor is in. The returned tensor will follow the same layout.
 *                                   Valid layouts are NHWC, NCHW, HWC, CHW, and HW.
 *  @param      name                                      The name for the operation
 *
 *  @return     A valid MPSGraphTensor object
 */
-(MPSGraphTensor *) resizeBilinearWithTensor:(MPSGraphTensor *) imagesTensor
                                  sizeTensor:(MPSGraphTensor *) size
                                centerResult:(BOOL) centerResult
                                alignCorners:(BOOL) alignCorners
                                      layout:(MPSGraphTensorNamedDataLayout) layout
                                        name:(NSString * _Nullable) name
MPS_AVAILABLE_STARTING(macos(13.0), ios(16.0), tvos(16.0))
MPS_SWIFT_NAME( resizeBilinear(_:sizeTensor:centerResult:alignCorners:layout:name:) );

/*!
 *  @abstract   Create Resize op and return the result tensor
 *  @discussion Resamples input images to given size using the provided scale and offset.
 *              Destination indices are computed using
 *              @code
 *                  dst_indices = (src_indices * scale) + offset
 *              @endcode
 *              For most use cases passing the scale and offset directly is unnecessary, and it is
 *              preferable to use the API specifying centerResult and alignCorners.
 *
 *  @param      imagesTensor                   Tensor containing input images.
 *  @param      size                                     1D Int32 or Int64 tensor. A 2-element shape as [newHeight, newWidth]
 *  @param      scaleOffset                      1D float tensor. A 4-element shape as [scaleY, scaleX, offsetY, offsetX]
 *  @param      mode                                     The resampling mode to use. If nearest sampling is specifed, RoundPreferCeil mode will be used.
 *  @param      layout                                  Specifies what layout the provided tensor is in. The returned tensor will follow the same layout.
 *                                   Valid layouts are NHWC, NCHW, HWC, CHW, and HW.
 *  @param      name                                      The name for the operation
 *
 *  @return     A valid MPSGraphTensor object
 */
-(MPSGraphTensor *) resizeTensor:(MPSGraphTensor *) imagesTensor
                      sizeTensor:(MPSGraphTensor *) size
               scaleOffsetTensor:(MPSGraphTensor *) scaleOffset
                            mode:(MPSGraphResizeMode) mode
                          layout:(MPSGraphTensorNamedDataLayout) layout
                            name:(NSString * _Nullable) name
MPS_AVAILABLE_STARTING(macos(13.0), ios(16.0), tvos(16.0))
MPS_SWIFT_NAME( resize(_:sizeTensor:scaleOffsetTensor:mode:layout:name:) );

/*!
 *  @abstract   Create Resize op and return the result tensor
 *  @discussion Resamples input images to given size using the provided scale and offset and nearest neighbor sampling
 *              See above discussion for more details.
 *
 *  @param      imagesTensor                   Tensor containing input images.
 *  @param      size                                     1D Int32 or Int64 tensor. A 2-element shape as [newHeight, newWidth]
 *  @param      scaleOffset                      1D float tensor. A 4-element shape as [scaleY, scaleX, offsetY, offsetX]
 *  @param      nearestRoundingMode    The rounding mode to use when using nearest resampling.
 *  @param      layout                                  Specifies what layout the provided tensor is in. The returned tensor will follow the same layout.
 *                                   Valid layouts are NHWC, NCHW, HWC, CHW, and HW.
 *  @param      name                                      The name for the operation
 *
 *  @return     A valid MPSGraphTensor object
 */
-(MPSGraphTensor *) resizeNearestWithTensor:(MPSGraphTensor *) imagesTensor
                                 sizeTensor:(MPSGraphTensor *) size
                          scaleOffsetTensor:(MPSGraphTensor *) scaleOffset
                        nearestRoundingMode:(MPSGraphResizeNearestRoundingMode) nearestRoundingMode
                                     layout:(MPSGraphTensorNamedDataLayout) layout
                                       name:(NSString * _Nullable) name
MPS_AVAILABLE_STARTING(macos(13.0), ios(16.0), tvos(16.0))
MPS_SWIFT_NAME( resizeNearest(_:sizeTensor:scaleOffsetTensor:nearestRoundingMode:layout:name:) );

/*!
 *  @abstract   Create Resize op and return the result tensor
 *  @discussion Resamples input images to given size using the provided scale and offset and bilinear sampling
 *              See above discussion for more details.
 *
 *  @param      imagesTensor                   Tensor containing input images.
 *  @param      size                                     1D Int32 or Int64 tensor. A 2-element shape as [newHeight, newWidth]
 *  @param      scaleOffset                      1D float tensor. A 4-element shape as [scaleY, scaleX, offsetY, offsetX]
 *  @param      nearestRoundingMode    The rounding mode to use when using nearest resampling.
 *  @param      layout                                  Specifies what layout the provided tensor is in. The returned tensor will follow the same layout.
 *                                   Valid layouts are NHWC, NCHW, HWC, CHW, and HW.
 *  @param      name                                      The name for the operation
 *
 *  @return     A valid MPSGraphTensor object
 */
-(MPSGraphTensor *) resizeBilinearWithTensor:(MPSGraphTensor *) imagesTensor
                                  sizeTensor:(MPSGraphTensor *) size
                           scaleOffsetTensor:(MPSGraphTensor *) scaleOffset
                                      layout:(MPSGraphTensorNamedDataLayout) layout
                                        name:(NSString * _Nullable) name
MPS_AVAILABLE_STARTING(macos(13.0), ios(16.0), tvos(16.0))
MPS_SWIFT_NAME( resizeBilinear(_:sizeTensor:scaleOffsetTensor:layout:name:) );

/*!
 *  @abstract   Create Resize gradient op and return the result tensor
 *  @discussion Computes the gradient for the forward pass Resize op with identical parameters.
 *              See discussion of resizeTensor for more in depth description of resize paramters.
 *
 *  @param      gradient                             Incoming gradient tensor
 *  @param      input                                   Forward pass input tensor
 *  @param      mode                                     The resampling mode to use. If nearest sampling is specifed, RoundPreferCeil mode will be used.
 *  @param      centerResult                    Controls if the result image is centered on the input image. When NO, the result will have the top left corner aligned
 *  @param      alignCorners                    When YES, the result image will have the same value as the input image in the corners
 *  @param      layout                                 Specifies what layout the provided tensor is in. The returned tensor will follow the same layout.
 *                                   Valid layouts are NHWC, NCHW, HWC, CHW, and HW.
 *  @param      name                                      The name for the operation
 *
 *  @return     A valid MPSGraphTensor object
 */
-(MPSGraphTensor *) resizeWithGradientTensor:(MPSGraphTensor *) gradient
                                       input:(MPSGraphTensor *) input
                                        mode:(MPSGraphResizeMode) mode
                                centerResult:(BOOL) centerResult
                                alignCorners:(BOOL) alignCorners
                                      layout:(MPSGraphTensorNamedDataLayout) layout
                                        name:(NSString * _Nullable) name;

/*!
 *  @abstract   Create Resize gradient op and return the result tensor
 *  @discussion Computes the gradient for the forward pass Resize op with identical parameters.
 *              See discussion of resizeTensor for more in depth description of resize paramters.
 *
 *  @param      gradient                             Incoming gradient tensor
 *  @param      input                                   Forward pass input tensor
 *  @param      nearestRoundingMode    The rounding mode to use when using nearest resampling.
 *  @param      centerResult                    Controls if the result image is centered on the input image. When NO, the result will have the top left corner aligned
 *  @param      alignCorners                    When YES, the result image will have the same value as the input image in the corners
 *  @param      layout                                 Specifies what layout the provided tensor is in. The returned tensor will follow the same layout.
 *                                   Valid layouts are NHWC, NCHW, HWC, CHW, and HW.
 *  @param      name                                      The name for the operation
 *
 *  @return     A valid MPSGraphTensor object
 */
-(MPSGraphTensor *) resizeNearestWithGradientTensor:(MPSGraphTensor *) gradient
                                              input:(MPSGraphTensor *) input
                                nearestRoundingMode:(MPSGraphResizeNearestRoundingMode) nearestRoundingMode
                                       centerResult:(BOOL) centerResult
                                       alignCorners:(BOOL) alignCorners
                                             layout:(MPSGraphTensorNamedDataLayout) layout
                                               name:(NSString * _Nullable) name
MPS_AVAILABLE_STARTING(macos(13.0), ios(16.0), tvos(16.0));

/*!
 *  @abstract   Create Resize gradient op and return the result tensor
 *  @discussion Computes the gradient for the forward pass Resize op with identical parameters.
 *              See discussion of resizeTensor for more in depth description of resize paramters.
 *
 *  @param      gradient                             Incoming gradient tensor
 *  @param      input                                   Forward pass input tensor
 *  @param      centerResult                    Controls if the result image is centered on the input image. When NO, the result will have the top left corner aligned
 *  @param      alignCorners                    When YES, the result image will have the same value as the input image in the corners
 *  @param      layout                                 Specifies what layout the provided tensor is in. The returned tensor will follow the same layout.
 *                                   Valid layouts are NHWC, NCHW, HWC, CHW, and HW.
 *  @param      name                                      The name for the operation
 *
 *  @return     A valid MPSGraphTensor object
 */
-(MPSGraphTensor *) resizeBilinearWithGradientTensor:(MPSGraphTensor *) gradient
                                               input:(MPSGraphTensor *) input
                                        centerResult:(BOOL) centerResult
                                        alignCorners:(BOOL) alignCorners
                                              layout:(MPSGraphTensorNamedDataLayout) layout
                                                name:(NSString * _Nullable) name
MPS_AVAILABLE_STARTING(macos(13.0), ios(16.0), tvos(16.0));


/*!
 *  @abstract   Create Resize gradient op and return the result tensor
 *  @discussion Computes the gradient for the forward pass Resize op with identical parameters.
 *              See discussion of resizeTensor for more in depth description of resize paramters.
 *
 *  @param      gradient                             Incoming gradient tensor
 *  @param      input                                   Forward pass input tensor
 *  @param      scaleOffset                      1D float tensor. A 4-element shape as [scaleY, scaleX, offsetY, offsetX]
 *  @param      mode                                     The resampling mode to use. If nearest sampling is specifed, RoundPreferCeil mode will be used.
 *  @param      layout                                 Specifies what layout the provided tensor is in. The returned tensor will follow the same layout.
 *                                   Valid layouts are NHWC, NCHW, HWC, CHW, and HW.
 *  @param      name                                      The name for the operation
 *
 *  @return     A valid MPSGraphTensor object
 */
-(MPSGraphTensor *) resizeWithGradientTensor:(MPSGraphTensor *) gradient
                                       input:(MPSGraphTensor *) input
                           scaleOffsetTensor:(MPSGraphTensor *) scaleOffset
                                        mode:(MPSGraphResizeMode) mode
                                      layout:(MPSGraphTensorNamedDataLayout) layout
                                        name:(NSString * _Nullable) name
MPS_AVAILABLE_STARTING(macos(13.0), ios(16.0), tvos(16.0));

/*!
 *  @abstract   Create Resize gradient op and return the result tensor
 *  @discussion Computes the gradient for the forward pass Resize op with identical parameters.
 *              See discussion of resizeTensor for more in depth description of resize paramters.
 *
 *  @param      gradient                             Incoming gradient tensor
 *  @param      input                                   Forward pass input tensor
 *  @param      scaleOffset                      1D float tensor. A 4-element shape as [scaleY, scaleX, offsetY, offsetX]
 *  @param      nearestRoundingMode    The rounding mode to use when using nearest resampling.
 *  @param      layout                                 Specifies what layout the provided tensor is in. The returned tensor will follow the same layout.
 *                                   Valid layouts are NHWC, NCHW, HWC, CHW, and HW.
 *  @param      name                                      The name for the operation
 *
 *  @return     A valid MPSGraphTensor object
 */
-(MPSGraphTensor *) resizeNearestWithGradientTensor:(MPSGraphTensor *) gradient
                                              input:(MPSGraphTensor *) input
                                  scaleOffsetTensor:(MPSGraphTensor *) scaleOffset
                                nearestRoundingMode:(MPSGraphResizeNearestRoundingMode) nearestRoundingMode
                                             layout:(MPSGraphTensorNamedDataLayout) layout
                                               name:(NSString * _Nullable) name
MPS_AVAILABLE_STARTING(macos(13.0), ios(16.0), tvos(16.0));

/*!
 *  @abstract   Create Resize gradient op and return the result tensor
 *  @discussion Computes the gradient for the forward pass Resize op with identical parameters.
 *              See discussion of resizeTensor for more in depth description of resize paramters.
 *
 *  @param      gradient                             Incoming gradient tensor
 *  @param      input                                   Forward pass input tensor
 *  @param      scaleOffset                      1D float tensor. A 4-element shape as [scaleY, scaleX, offsetY, offsetX]
 *  @param      nearestRoundingMode    The rounding mode to use when using nearest resampling.
 *  @param      layout                                 Specifies what layout the provided tensor is in. The returned tensor will follow the same layout.
 *                                   Valid layouts are NHWC, NCHW, HWC, CHW, and HW.
 *  @param      name                                      The name for the operation
 *
 *  @return     A valid MPSGraphTensor object
 */
-(MPSGraphTensor *) resizeBilinearWithGradientTensor:(MPSGraphTensor *) gradient
                                               input:(MPSGraphTensor *) input
                                   scaleOffsetTensor:(MPSGraphTensor *) scaleOffset
                                              layout:(MPSGraphTensorNamedDataLayout) layout
                                                name:(NSString * _Nullable) name
MPS_AVAILABLE_STARTING(macos(13.0), ios(16.0), tvos(16.0));

@end

NS_ASSUME_NONNULL_END


#endif /* MPSGraphResizeOps_h */
