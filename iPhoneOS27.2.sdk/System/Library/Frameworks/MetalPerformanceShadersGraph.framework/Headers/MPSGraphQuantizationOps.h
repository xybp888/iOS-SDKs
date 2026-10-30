//
//  MPSGraphQuantizationOps.h
//  MPSGraphQuantizationOps
//
//  Created on 9/30/21.
//  Copyright © 2021 Apple Inc. All rights reserved.
//

#ifndef MPSGraphQuantizationOps_h
#define MPSGraphQuantizationOps_h

#import <MetalPerformanceShadersGraph/MPSGraph.h>

NS_ASSUME_NONNULL_BEGIN

@interface MPSGraph(MPSGraphQuantizationOps)

/// Creates a Quantize operation and returns the result tensor.
///
/// Convert the float `tensor` to a quantized tensor by applying a scale + bias transform:
/// result = round(tensor / scale) + zeroPoint
///
/// - Parameters:
///   - tensor: Input tensor to be quantized
///   - scale: Scale scalar parameter
///   - zeroPoint: Bias scalar parameter (converted to dataType of resultTensor)
///   - dataType: Data type of the result tensor. Supports ``MPSDataTypeInt8``, ``MPSDataTypeUInt8``,
///     ``MPSDataTypeFloat8E4M3``, and ``MPSDataTypeFloat8E5M2``. Float8 output requires symmetric
///     quantization (zeroPoint = 0).
///   - name: The name for the operation.
/// - Returns: A valid MPSGraphTensor array of datatype dataType
-(MPSGraphTensor*) quantizeTensor:(MPSGraphTensor*)tensor
                            scale:(double)scale
                        zeroPoint:(double)zeroPoint
                         dataType:(MPSDataType)dataType
                             name:(NSString * _Nullable) name
MPS_AVAILABLE_STARTING(macos(13.1), ios(16.2), tvos(16.2))
MPS_SWIFT_NAME( quantize(_:scale:zeroPoint:dataType:name:) );

/// Creates Dequantize operation and returns the result tensor.
///
/// Convert the quantized `tensor` to a float tensor by applying a scale + bias transform:
/// result = scale * (tensor - zeroPoint)
///
/// Supported input types: ``MPSDataTypeInt4``, ``MPSDataTypeUInt4``,
/// ``MPSDataTypeInt8``, ``MPSDataTypeUInt8``,
/// ``MPSDataTypeFloat8E4M3``, ``MPSDataTypeFloat8E5M2``.
/// The scale type and `dataType` must match (``MPSDataTypeFloat16``, ``MPSDataTypeFloat32``,
/// or ``MPSDataTypeBFloat16``).
///
/// - Parameters:
///   - tensor: Input tensor to be dequantized
///   - scale: Scale scalar parameter
///   - zeroPoint: Bias scalar parameter (converted to dataType of tensor)
///   - dataType: Float data type of the result tensor.
///   - name: The name for the operation.
/// - Returns: A valid MPSGraphTensor array of datatype dataType
-(MPSGraphTensor*) dequantizeTensor:(MPSGraphTensor*)tensor
                              scale:(double)scale
                          zeroPoint:(double)zeroPoint
                           dataType:(MPSDataType)dataType
                               name:(NSString * _Nullable) name
MPS_AVAILABLE_STARTING(macos(13.1), ios(16.2), tvos(16.2))
MPS_SWIFT_NAME( dequantize(_:scale:zeroPoint:dataType:name:) );

/// Creates a Quantize operation and returns the result tensor.
///
/// Convert the float `tensor` to a quantized tensor by applying a scale + bias transform:
/// result = round(tensor / scaleTensor) + zeroPoint
///
/// - Parameters:
///   - tensor: Input tensor to be quantized
///   - scaleTensor: Scale 1D Tensor parameter with size == tensor.shape[axis]
///   - zeroPoint: Bias scalar parameter (converted to dataType of resultTensor)
///   - dataType: Data type of the result tensor. Supports ``MPSDataTypeInt8``, ``MPSDataTypeUInt8``,
///     ``MPSDataTypeFloat8E4M3``, and ``MPSDataTypeFloat8E5M2``. Float8 output requires symmetric
///     quantization (zeroPoint = 0).
///   - axis: Axis on which the scale 1D value is being broadcasted
///   - name: The name for the operation.
/// - Returns: A valid MPSGraphTensor array of datatype dataType
-(MPSGraphTensor*) quantizeTensor:(MPSGraphTensor*)tensor
                      scaleTensor:(MPSGraphTensor*)scaleTensor
                        zeroPoint:(double)zeroPoint
                         dataType:(MPSDataType)dataType
                             axis:(NSInteger)axis
                             name:(NSString * _Nullable) name
MPS_AVAILABLE_STARTING(macos(13.1), ios(16.2), tvos(16.2))
MPS_SWIFT_NAME( quantize(_:scaleTensor:zeroPoint:dataType:axis:name:) );

/// Creates Dequantize operation and returns the result tensor.
///
/// Convert the quantized `tensor` to a float tensor by applying a scale + bias transform:
/// result = scaleTensor * (tensor - zeroPoint)
///
/// Supported input types: ``MPSDataTypeInt4``, ``MPSDataTypeUInt4``,
/// ``MPSDataTypeInt8``, ``MPSDataTypeUInt8``,
/// ``MPSDataTypeFloat8E4M3``, ``MPSDataTypeFloat8E5M2``.
/// The `scaleTensor` type and `dataType` must match (``MPSDataTypeFloat16``,
/// ``MPSDataTypeFloat32``, or ``MPSDataTypeBFloat16``).
///
/// - Parameters:
///   - tensor: Input tensor to be dequantized
///   - scaleTensor: Scale scalar or 1D Tensor parameter with size == tensor.shape[axis]
///   - zeroPoint: Bias scalar parameter (converted to dataType of tensor)
///   - dataType: Float data type of the result tensor.
///   - axis: Axis on which the scale 1D value is being broadcasted
///   - name: The name for the operation.
/// - Returns: A valid MPSGraphTensor array of datatype dataType
-(MPSGraphTensor*) dequantizeTensor:(MPSGraphTensor*)tensor
                        scaleTensor:(MPSGraphTensor*)scaleTensor
                          zeroPoint:(double)zeroPoint
                           dataType:(MPSDataType)dataType
                               axis:(NSInteger)axis
                               name:(NSString * _Nullable) name
MPS_AVAILABLE_STARTING(macos(13.1), ios(16.2), tvos(16.2))
MPS_SWIFT_NAME( dequantize(_:scaleTensor:zeroPoint:dataType:axis:name:) );

/// Creates a Quantize operation and returns the result tensor.
///
/// Convert the float `tensor` to a quantized tensor by applying a scale + bias transform:
/// result = round(tensor / scaleTensor) + zeroPointTensor
///
/// - Parameters:
///   - tensor: Input tensor to be quantized
///   - scaleTensor: Scale scalar or 1D Tensor parameter with size == tensor.shape[axis]
///   - zeroPointTensor: Bias scalar or 1D Tensor parameter with size == tensor.shape[axis]
///   - dataType: Data type of the result tensor. Supports ``MPSDataTypeInt8``, ``MPSDataTypeUInt8``,
///     ``MPSDataTypeFloat8E4M3``, and ``MPSDataTypeFloat8E5M2``. Float8 output requires symmetric
///     quantization (zeroPointTensor = 0).
///   - axis: Axis on which the scale 1D value is being broadcasted
///   - name: The name for the operation.
/// - Returns: A valid MPSGraphTensor array of datatype dataType
-(MPSGraphTensor*) quantizeTensor:(MPSGraphTensor*)tensor
                      scaleTensor:(MPSGraphTensor*)scaleTensor
                  zeroPointTensor:(MPSGraphTensor*)zeroPointTensor
                         dataType:(MPSDataType)dataType
                             axis:(NSInteger)axis
                             name:(NSString * _Nullable) name
MPS_AVAILABLE_STARTING(macos(13.1), ios(16.2), tvos(16.2))
MPS_SWIFT_NAME( quantize(_:scaleTensor:zeroPointTensor:dataType:axis:name:) );

/// Creates a dequantize operation and returns the result tensor.
///
/// Convert the quantized `tensor` to a float tensor by applying a scale + bias transform:
/// result = scaleTensor * (tensor - zeroPointTensor)
///
/// Supported input types: ``MPSDataTypeInt4``, ``MPSDataTypeUInt4``,
/// ``MPSDataTypeInt8``, ``MPSDataTypeUInt8``,
/// ``MPSDataTypeFloat8E4M3``, ``MPSDataTypeFloat8E5M2``.
/// The `scaleTensor` type and `dataType` must match (``MPSDataTypeFloat16``,
/// ``MPSDataTypeFloat32``, or ``MPSDataTypeBFloat16``).
///
/// - Parameters:
///   - tensor: Input tensor to be dequantized
///   - scaleTensor: Scale scalar or 1D Tensor parameter with size == tensor.shape[axis]
///   - zeroPointTensor: Bias scalar or 1D Tensor parameter with size == tensor.shape[axis]
///   - dataType: Float data type of the result tensor.
///   - axis: Axis on which the scale 1D value is being broadcasted
///   - name: The name for the operation.
/// - Returns: A valid MPSGraphTensor array of datatype dataType
-(MPSGraphTensor*) dequantizeTensor:(MPSGraphTensor*)tensor
                        scaleTensor:(MPSGraphTensor*)scaleTensor
                    zeroPointTensor:(MPSGraphTensor*)zeroPointTensor
                           dataType:(MPSDataType)dataType
                               axis:(NSInteger)axis
                               name:(NSString * _Nullable) name
MPS_AVAILABLE_STARTING(macos(13.1), ios(16.2), tvos(16.2))
MPS_SWIFT_NAME( dequantize(_:scaleTensor:zeroPointTensor:dataType:axis:name:) );

/// Creates a dequantize operation and returns the result tensor.
///
/// Convert the quantized `tensor` to a float tensor by applying a scale and bias transform:
/// ```md
/// result = scaleTensor * (tensor - zeroPointTensor)
/// ```
///
/// The quantization mode is determined by the element type of `scaleTensor`:
///
/// **Regular blockwise** (`scaleTensor` type is an MPSGraph float type):
/// - Supported input types: ``MPSDataTypeInt4``, ``MPSDataTypeUInt4``,
///   ``MPSDataTypeInt8``, ``MPSDataTypeUInt8``,
///   ``MPSDataTypeFloat8E4M3``, ``MPSDataTypeFloat8E5M2``.
/// - `zeroPointTensor` type must match the input `tensor` type.
/// - `scaleTensor` shape: leading dims of `tensor` with the last dim replaced by
///   `tensor.shape[last] / blockSize`.
///
/// **MX mode** (`scaleTensor` type is ``MPSDataTypeFloat8E8M0``):
/// - Supported input types: ``MPSDataTypeFloat4E2M1``, ``MPSDataTypeFloat8E4M3``, ``MPSDataTypeFloat8E5M2``.
/// - Block size 32, symmetric (zero point must be 0).
///
/// **F4 with F8E4M3 scale** (`scaleTensor` type is ``MPSDataTypeFloat8E4M3``,
/// input type is ``MPSDataTypeFloat4E2M1``):
/// - Block size 16, symmetric (zero point must be 0).
///
/// - Parameters:
///   - tensor: Input tensor to be dequantized.
///   - scaleTensor: The scale tensor with groups support.
///   - zeroPointTensor: The bias tensor with groups support.
///   - dataType: Float data type of the result tensor.
///   - name: The name for the operation.
/// - Returns: A valid ``MPSGraphTensor`` array of datatype `dataType`.
-(MPSGraphTensor*) dequantizeTensor:(MPSGraphTensor*)tensor
                        scaleTensor:(MPSGraphTensor*)scaleTensor
                    zeroPointTensor:(MPSGraphTensor*)zeroPointTensor
                           dataType:(MPSDataType)dataType
                               name:(NSString * _Nullable) name
MPS_AVAILABLE_STARTING(macos(15.0), ios(18.0), macCatalyst(18.0), tvos(18.0))
MPS_SWIFT_NAME( dequantize(_:scaleTensor:zeroPointTensor:dataType:name:) );

/// Creates a dequantize operation and returns the result tensor.
///
/// Converts the quantized `tensor` to a float tensor by applying a scale transform
/// (symmetric — zero point is implicitly 0):
/// ```md
/// result = scaleTensor * tensor
/// ```
///
/// The quantization mode is determined by the element type of `scaleTensor`:
///
/// **Regular blockwise** (`scaleTensor` type is an MPSGraph float type):
/// - Supported input types: ``MPSDataTypeInt4``, ``MPSDataTypeUInt4``,
///   ``MPSDataTypeInt8``, ``MPSDataTypeUInt8``,
///   ``MPSDataTypeFloat8E4M3``, ``MPSDataTypeFloat8E5M2``.
/// - `scaleTensor` shape: leading dims of `tensor` with the last dim replaced by
///   `tensor.shape[last] / blockSize`.
///
/// **MX mode** (`scaleTensor` type is ``MPSDataTypeFloat8E8M0``):
/// - Supported input types: ``MPSDataTypeFloat4E2M1``, ``MPSDataTypeFloat8E4M3``, ``MPSDataTypeFloat8E5M2``.
/// - Block size 32.
///
/// **F4 with F8E4M3 scale** (`scaleTensor` type is ``MPSDataTypeFloat8E4M3``,
/// input type is ``MPSDataTypeFloat4E2M1``):
/// - Block size 16.
///
/// - Parameters:
///   - tensor: Input tensor to be dequantized.
///   - scaleTensor: Scale Tensor parameter with groups support.
///   - dataType: Float data type of the result tensor.
///   - name: The name for the operation.
/// - Returns: A valid ``MPSGraphTensor`` array of datatype `dataType`.
-(MPSGraphTensor*) dequantizeTensor:(MPSGraphTensor*)tensor
                        scaleTensor:(MPSGraphTensor*)scaleTensor
                           dataType:(MPSDataType)dataType
                               name:(NSString * _Nullable) name
MPS_AVAILABLE_STARTING(macos(15.0), ios(18.0), macCatalyst(18.0), tvos(18.0))
MPS_SWIFT_NAME( dequantize(_:scaleTensor:dataType:name:) );

/// Creates a lookup-table based dequantize operation and returns the result tensor.
///
/// Converts a `tensor` of integer indices to a float tensor by applying a lookup operation:
/// ```md
/// result[i1,...,in] = LUTTensor[i1',...,in',tensor[i1,...,in]].
/// ```
///
/// Supported `tensor` index types and required last-dimension size of `LUTTensor`:
/// - ``MPSDataTypeUInt4``: 16 entries
/// - ``MPSDataTypeUInt8``: 256 entries
///
/// `LUTTensor` (and result) element types: ``MPSDataTypeFloat16``, ``MPSDataTypeFloat32``,
/// ``MPSDataTypeBFloat16``, ``MPSDataTypeFloat8E4M3``, ``MPSDataTypeFloat8E5M2``, ``MPSDataTypeInt8``.
/// The input `tensor` must be a graph constant.
/// The operation supports LUT groups up to the last 3 dimensions for `tensor`.
///
/// - Parameters:
///   - tensor: Input constant integer-index tensor to be dequantized.
///   - LUTTensor: The lookup table to use.
///   - name: The name for the operation.
/// - Returns: A valid ``MPSGraphTensor`` object.
-(MPSGraphTensor *) dequantizeTensor:(MPSGraphTensor *) tensor
                           LUTTensor:(MPSGraphTensor *) LUTTensor
                                name:(NSString * _Nullable) name
MPS_SWIFT_NAME( dequantize(_:LUTTensor:name:) )
MPS_AVAILABLE_STARTING(macos(15.0), ios(18.0), macCatalyst(18.0), tvos(18.0));

/// Creates a vector lookup-table based dequantize operation and returns the result tensor.
///
/// Converts a `tensor` of integer indices to a float tensor by applying a lookup operation,
/// where each input index defines a vector of values. The operation reads the vector values
/// from the last dimension of the lookup table tensor and stores them into the dimension
/// defined by `axis` on the result tensor.
/// ```md
/// result[i1, ... , i_axis, ..., in] = LUTTensor[i1', ..., in', tensor[i1, ..., in], i_axis]
/// ```
///
/// Supported `tensor` index types and required second-to-last-dimension size of `LUTTensor`:
/// - ``MPSDataTypeUInt4``: 16 entries
/// - ``MPSDataTypeUInt8``: 256 entries
///
/// `LUTTensor` (and result) element types: ``MPSDataTypeFloat16``, ``MPSDataTypeFloat32``,
/// ``MPSDataTypeBFloat16``, ``MPSDataTypeFloat8E4M3``, ``MPSDataTypeFloat8E5M2``, ``MPSDataTypeInt8``.
/// The input `tensor` must be a graph constant.
/// The operation supports LUT groups up to the last 2 dimensions for `tensor`.
///
/// - Parameters:
///   - tensor: Input constant integer-index tensor to be dequantized.
///   - LUTTensor: The lookup table to use.
///   - axis: The result axis into which the LUT vector values are written.
///   - name: The name for the operation.
/// - Returns: A valid ``MPSGraphTensor`` object.
-(MPSGraphTensor *) dequantizeTensor:(MPSGraphTensor *) tensor
                           LUTTensor:(MPSGraphTensor *) LUTTensor
                                axis:(NSInteger) axis
                                name:(NSString * _Nullable) name
MPS_SWIFT_NAME( dequantize(_:LUTTensor:axis:name:) )
MPS_AVAILABLE_STARTING(macos(15.0), ios(18.0), macCatalyst(18.0), tvos(18.0));

@end


NS_ASSUME_NONNULL_END

#endif /* MPSGraphQuantizationOps_h */
