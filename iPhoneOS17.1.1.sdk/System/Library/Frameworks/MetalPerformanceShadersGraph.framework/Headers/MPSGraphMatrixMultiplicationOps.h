//
//  MPSGraphMatrixMultiplicationOps.h
//  MetalPerformanceShadersGraph
//
//  Created on 12/8/19.
//  Copyright © 2019 Apple Inc. All rights reserved.
//

#ifndef MPSGraphMatrixMultiplicationOps_h
#define MPSGraphMatrixMultiplicationOps_h

#import <MetalPerformanceShadersGraph/MPSGraph.h>

NS_ASSUME_NONNULL_BEGIN

MPS_CLASS_AVAILABLE_STARTING(macos(11.0), ios(14.0), tvos(14.0))
@interface MPSGraph(MPSGraphMatrixMultiplicationOps)

/// Computes the matrix multiplication of 2 input tensors with support for broadcasting.
///
/// - Parameters:
///   - primaryTensor: The left-hand side tensor.
///   - secondaryTensor: The right-hand side tensor.
///   - name: The name for the operation.
/// - Returns: A valid tensor containing the product of the input matrices.
-(MPSGraphTensor *) matrixMultiplicationWithPrimaryTensor:(MPSGraphTensor *) primaryTensor
                                          secondaryTensor:(MPSGraphTensor *) secondaryTensor
                                                     name:(NSString * _Nullable) name
MPS_SWIFT_NAME( matrixMultiplication(primary:secondary:name:) );

/// Computes the hamming distance of 2 input tensors with support for broadcasting.
///
/// The hamming distance is computed between 2 sets of vectors and the last dimension(s) of each 
/// input tensor is considered a vector.
///
/// - Parameters:
///   - primaryTensor: The first input tensor.
///   - secondaryTensor: The second input tensor.
///   - resultDataType: The datatype of the return MPSGraphTensor. Must be either ``MPSDataTypeUInt32`` or ``MPSDataTypeUInt16``.
///   - name: The name for the operation
/// - Returns: A valid tensor containing the hamming distance between the input tensors.
-(MPSGraphTensor *) HammingDistanceWithPrimaryTensor:(MPSGraphTensor *) primaryTensor
                                     secondaryTensor:(MPSGraphTensor *) secondaryTensor
                                      resultDataType:(MPSDataType) resultDataType
                                                name:(NSString * _Nullable) name
MPS_SWIFT_NAME( HammingDistance(primary:secondary:resultDataType:name:) )
MPS_AVAILABLE_STARTING(macos(13.0), ios(16.0), tvos(16.0));


@end


NS_ASSUME_NONNULL_END

#endif /* MPSGraphMatrixMultiplicationOps_h */
