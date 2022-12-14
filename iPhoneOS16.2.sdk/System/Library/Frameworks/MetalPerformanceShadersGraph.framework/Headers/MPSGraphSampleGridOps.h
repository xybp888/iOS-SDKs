//
//  MPSGraphSampleGrid.h
//  MPSGraph
//
//  Created on 10/3/22.
//  Copyright © 2022 Apple Inc. All rights reserved.
//

#ifndef MPSGraphSampleGrid_h
#define MPSGraphSampleGrid_h

NS_ASSUME_NONNULL_BEGIN

@interface MPSGraph(MPSGraphSampleGrid)

/*!
 *  @abstract   Samples a tensor using the coordinates provided.
 *  @discussion Given an input tensor (N, H1, W1, C) or (N, C, H1, W1) and coordinates tensor (N, H2, W2, 2) this operation outputs a tensor of
 *              size (N, H2, W2, C) or (N, C, H2, W2) by sampling the input tensor at the coordinates provided by the coordinates tensor.
 *
 *  @param      source   Tensor containing source data
 *  @param      coordinates  a tensor (N, Hout, Wout, 2) that contains the coordinates of the samples in the source tensor
 *              that constitute the output tensor.
 *  @param      layout Specifies what layout the provided tensor is in. The returned tensor will follow the same layout.
 *              Valid layouts are NHWC and NCHW.
 *  @param      normalizeCoordinates If true, coordinates are within [-1, 1] x [-1, 1] otherwise they are in pixels in the input tensor.
 *  @param      relativeCoordinates If true, coordinates are relative to the postion of the pixel in the output tensor and scaled back to the input tensor size
 *  @param      alignCorners If true, coordinate extrema are equal to the center of edge pixels, otherwise extrema are equal to outer edge of edge pixels
 *  @param      paddingMode determines how samples outside the inputTensor are evaluated (only constant, reflect, symmetric and clampToEdge are supported)
 *  @param      samplingMode Can be either MPSGraphResizeNearest or MPSGraphResizeBilinear. Nearest sampling will use roundPreferCeil.
 *  @param      constantValue If paddingMode is MPSGraphPaddingModeConstant, then this constant is used for samples outside
 *              the input tensor.
 *  @param      name        The name for the operation
 *
 *  @return     A valid MPSGraphTensor object
 */
-(MPSGraphTensor *) sampleGridWithSourceTensor:(MPSGraphTensor *) source
                              coordinateTensor:(MPSGraphTensor *) coordinates
                                        layout:(MPSGraphTensorNamedDataLayout) layout
                          normalizeCoordinates:(BOOL) normalizeCoordinates
                           relativeCoordinates:(BOOL) relativeCoordinates
                                  alignCorners:(BOOL) alignCorners
                                   paddingMode:(MPSGraphPaddingMode) paddingMode
                                  samplingMode:(MPSGraphResizeMode) samplingMode
                                 constantValue:(double) constantValue
                                          name:(NSString * _Nullable) name
MPS_AVAILABLE_STARTING(macos(13.1), ios(16.2), tvos(16.2));

/*!
 *  @abstract   Samples a tensor using the coordinates provided, using nearest neighbor sampling with specified rounding mode.
 *  @discussion Given an input tensor (N, H1, W1, C) or (N, C, H1, W1) and coordinates tensor (N, H2, W2, 2) this operation outputs a tensor of
 *              size (N, H2, W2, C) or (N, C, H2, W2) by sampling the input tensor at the coordinates provided by the coordinates tensor.
 *
 *  @param      source   Tensor containing source data
 *  @param      coordinates  a tensor (N, Hout, Wout, 2) that contains the coordinates of the samples in the source tensor
 *              that constitute the output tensor.
 *  @param      layout Specifies what layout the provided tensor is in. The returned tensor will follow the same layout.
 *              Valid layouts are NHWC and NCHW.
 *  @param      normalizeCoordinates If true, coordinates are within [-1, 1] x [-1, 1] otherwise they are in pixels in the input tensor.
 *  @param      relativeCoordinates If true, coordinates are relative to the postion of the pixel in the output tensor and scaled back to the input tensor size
 *  @param      alignCorners If true, coordinate extrema are equal to the center of edge pixels, otherwise extrema are equal to outer edge of edge pixels
 *  @param      paddingMode determines how samples outside the inputTensor are evaluated (only constant, reflect, symmetric and clampToEdge are supported)
 *  @param      nearestRoundingMode The rounding mode to use for determining the nearest neighbor. Valid modes are roundPreferCeil, roundPreferFloor, ceil, and floor.
 *  @param      constantValue If paddingMode is MPSGraphPaddingModeConstant, then this constant is used for samples outside
 *              the input tensor.
 *  @param      name        The name for the operation
 *
 *  @return     A valid MPSGraphTensor object
 */
-(MPSGraphTensor *) sampleGridWithSourceTensor:(MPSGraphTensor *) source
                              coordinateTensor:(MPSGraphTensor *) coordinates
                                        layout:(MPSGraphTensorNamedDataLayout) layout
                          normalizeCoordinates:(BOOL) normalizeCoordinates
                           relativeCoordinates:(BOOL) relativeCoordinates
                                  alignCorners:(BOOL) alignCorners
                                   paddingMode:(MPSGraphPaddingMode) paddingMode
                           nearestRoundingMode:(MPSGraphResizeNearestRoundingMode) nearestRoundingMode
                                 constantValue:(double) constantValue
                                          name:(NSString * _Nullable) name
MPS_AVAILABLE_STARTING(macos(13.1), ios(16.2), tvos(16.2));

@end

NS_ASSUME_NONNULL_END

#endif /* MPSGraphSampleGrid_h */
