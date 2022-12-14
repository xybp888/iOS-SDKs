//
//  MPSGraphQuantizationOps.h
//  MPSGraphQuantizationOps
//
//  Created by stevenlariau on 9/30/21.
//  Copyright © 2021 Apple Inc. All rights reserved.
//

#ifndef MPSGraphQuantizationOps_h
#define MPSGraphQuantizationOps_h

#import <MetalPerformanceShadersGraph/MPSGraph.h>

NS_ASSUME_NONNULL_BEGIN

#define MPSGRAPH_QUANTIZATION_AVAILABLE

@interface MPSGraph(MPSGraphQuantizationOps)

/*!
 *  @abstract   Create Quantize op and return the result tensor
 *  @discussion Convert the float `tensor` to an i8 or u8 tensor by applying a scale + bias transform:
 *              result = (tensor / scale) + zeroPoint
 *
 *  @param      tensor                                  Input tensor to be quantized
 *  @param      scale                                    Scale scalar parameter
 *  @param      zeroPoint                           Bias scalar parameter (converted to dataType of resultTensor)
 *  @param      dataType                             Integer data type of the result tensor
 *  @param      name                                      The name for the operation
 *
 *  @return     A valid MPSGraphTensor array of datatype dataType
 */
-(MPSGraphTensor*) quantizeTensor:(MPSGraphTensor*)tensor
                            scale:(double)scale
                        zeroPoint:(double)zeroPoint
                         dataType:(MPSDataType)dataType
                             name:(NSString * _Nullable) name
MPS_AVAILABLE_STARTING(macos(13.1), ios(16.2), tvos(16.2))
MPS_SWIFT_NAME( quantize(_:scale:zeroPoint:dataType:name:) );

/*!
 *  @abstract   Create Dequantize op and return the result tensor
 *  @discussion Convert the i8 or u8 `tensor` to a float tensor by applying a scale + bias transform:
 *              result =  scale * (tensor - zeroPoint)
 *
 *  @param      tensor                                  Input tensor to be dequantized
 *  @param      scale                                    Scale scalar parameter
 *  @param      zeroPoint                           Bias scalar parameter (converted to dataType of tensor)
 *  @param      dataType                             Float data type of the result tensor
 *  @param      name                                      The name for the operation
 *
 *  @return     A valid MPSGraphTensor array of datatype dataType
 */
-(MPSGraphTensor*) dequantizeTensor:(MPSGraphTensor*)tensor
                              scale:(double)scale
                          zeroPoint:(double)zeroPoint
                           dataType:(MPSDataType)dataType
                               name:(NSString * _Nullable) name
MPS_AVAILABLE_STARTING(macos(13.1), ios(16.2), tvos(16.2))
MPS_SWIFT_NAME( dequantize(_:scale:zeroPoint:dataType:name:) );

/*!
 *  @abstract   Create Quantize op and return the result tensor
 *  @discussion Convert the float `tensor` to an i8 or u8 tensor by applying a scale + bias transform:
 *              result = (tensor / scaleTensor) + zeroPoint
 *
 *  @param      tensor                                  Input tensor to be quantized
 *  @param      scaleTensor                       Scale 1D Tensor parameter with size == tensor.shape[axis]
 *  @param      zeroPoint                           Bias scalar parameter (converted to dataType of resultTensor)
 *  @param      dataType                              Integer data type of the result tensor
 *  @param      axis                                      Axis on which the scale 1D value is being broadcasted
 *  @param      name                                      The name for the operation
 *
 *  @return     A valid MPSGraphTensor array of datatype dataType
 */
-(MPSGraphTensor*) quantizeTensor:(MPSGraphTensor*)tensor
                      scaleTensor:(MPSGraphTensor*)scaleTensor
                        zeroPoint:(double)zeroPoint
                         dataType:(MPSDataType)dataType
                             axis:(NSInteger)axis
                             name:(NSString * _Nullable) name
MPS_AVAILABLE_STARTING(macos(13.1), ios(16.2), tvos(16.2))
MPS_SWIFT_NAME( quantize(_:scaleTensor:zeroPoint:dataType:axis:name:) );

/*!
 *  @abstract   Create Dequantize op and return the result tensor
 *  @discussion Convert the i8 or u8 `tensor` to a float tensor by applying a scale + bias transform:
 *              result =  scaleTensor * (tensor - zeroPoint)
 *
 *  @param      tensor                                  Input tensor to be dequantized
 *  @param      scaleTensor                       Scale scalar or 1D Tensor parameter with size == tensor.shape[axis]
 *  @param      zeroPoint                           Bias scalar parameter (converted to dataType of tensor)
 *  @param      dataType                             Float data type of the result tensor
 *  @param      axis                                      Axis on which the scale 1D value is being broadcasted
 *  @param      name                                      The name for the operation
 *
 *  @return     A valid MPSGraphTensor array of datatype dataType
 */
-(MPSGraphTensor*) dequantizeTensor:(MPSGraphTensor*)tensor
                        scaleTensor:(MPSGraphTensor*)scaleTensor
                          zeroPoint:(double)zeroPoint
                           dataType:(MPSDataType)dataType
                               axis:(NSInteger)axis
                               name:(NSString * _Nullable) name
MPS_AVAILABLE_STARTING(macos(13.1), ios(16.2), tvos(16.2))
MPS_SWIFT_NAME( dequantize(_:scaleTensor:zeroPoint:dataType:axis:name:) );

/*!
 *  @abstract   Create Quantize op and return the result tensor
 *  @discussion Convert the float `tensor` to an i8 or u8 tensor by applying a scale + bias transform:
 *              result = (tensor / scaleTensor) + zeroPointTensor
 *
 *  @param      tensor                                  Input tensor to be quantized
 *  @param      scaleTensor                       Scale scalar or 1D Tensor parameter with size == tensor.shape[axis]
 *  @param      zeroPointTensor              Bias scalar or 1D Tensor parameter with size == tensor.shape[axis]
 *  @param      dataType                              Integer data type of the result tensor
 *  @param      axis                                      Axis on which the scale 1D value is being broadcasted
 *  @param      name                                      The name for the operation
 *
 *  @return     A valid MPSGraphTensor array of datatype dataType
 */
-(MPSGraphTensor*) quantizeTensor:(MPSGraphTensor*)tensor
                      scaleTensor:(MPSGraphTensor*)scaleTensor
                  zeroPointTensor:(MPSGraphTensor*)zeroPointTensor
                         dataType:(MPSDataType)dataType
                             axis:(NSInteger)axis
                             name:(NSString * _Nullable) name
MPS_AVAILABLE_STARTING(macos(13.1), ios(16.2), tvos(16.2))
MPS_SWIFT_NAME( quantize(_:scaleTensor:zeroPointTensor:dataType:axis:name:) );

/*!
 *  @abstract   Create Dequantize op and return the result tensor
 *  @discussion Convert the i8 or u8 `tensor` to a float tensor by applying a scale + bias transform:
 *              result =  scaleTensor * (tensor - zeroPointTensor)
 *
 *  @param      tensor                                  Input tensor to be dequantized
 *  @param      scaleTensor                       Scale scalar or 1D Tensor parameter with size == tensor.shape[axis]
 *  @param      zeroPointTensor              Bias scalar or 1D Tensor parameter with size == tensor.shape[axis]
 *  @param      dataType                             Float data type of the result tensor
 *  @param      axis                                      Axis on which the scale 1D value is being broadcasted
 *  @param      name                                      The name for the operation
 *
 *  @return     A valid MPSGraphTensor array of datatype dataType
 */
-(MPSGraphTensor*) dequantizeTensor:(MPSGraphTensor*)tensor
                        scaleTensor:(MPSGraphTensor*)scaleTensor
                    zeroPointTensor:(MPSGraphTensor*)zeroPointTensor
                           dataType:(MPSDataType)dataType
                               axis:(NSInteger)axis
                               name:(NSString * _Nullable) name
MPS_AVAILABLE_STARTING(macos(13.1), ios(16.2), tvos(16.2))
MPS_SWIFT_NAME( dequantize(_:scaleTensor:zeroPointTensor:dataType:axis:name:) );

@end


NS_ASSUME_NONNULL_END

#endif /* MPSGraphQuantizationOps_h */
