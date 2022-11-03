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

/*!
 *  @abstract   Create  MatMul op and return the result tensor, it supports broadcasting as well
 *
 *  @code
 *              resultTensor = matmul(primaryTensor, secondaryTensor)
 *  @endcode
 *
 *  @param      primaryTensor          LHS tensor of the binary Op
 *  @param      secondaryTensor      RHS tensor of the binary Op
 *  @param      name                              name for the operation
 *
 *  @return     A valid MPSGraphTensor object.
 */
-(MPSGraphTensor *) matrixMultiplicationWithPrimaryTensor:(MPSGraphTensor *) primaryTensor
                                          secondaryTensor:(MPSGraphTensor *) secondaryTensor
                                                     name:(NSString * _Nullable) name
MPS_SWIFT_NAME( matrixMultiplication(primary:secondary:name:) );

/*!
 *  @abstract   Create a  Hamming Distance op and return the result tensor, it supports broadcasting as well.
 *  @discussion The Hamming Distance is computed between sets of vectors and the last dimension(s) of each
 *              input tensor is considered a vector. If the shape of @ref primaryTensor is `[Na, M, K]` and the shape
 *              of @ref secondaryTensor is `[Nb, N, K]`, with Na, Nb being any batch dimensions,
 *              then the result shape is `[Na/Nb, M, N]`, where `Na/Nb` are the broadcasted batch dimensions.
 *              The result datatype is either MPSDataTypeUInt32 or MPSDataTypeUInt16.
 *
 *  @param      primaryTensor          LHS tensor of the binary Op
 *  @param      secondaryTensor      RHS tensor of the binary Op
 *  @param      resultDataType        Must be either MPSDataTypeUInt32 or MPSDataTypeUInt16
 *  @param      name                              name for the operation
 *
 *  @return     A valid MPSGraphTensor object.
 */
-(MPSGraphTensor *) HammingDistanceWithPrimaryTensor:(MPSGraphTensor *) primaryTensor
                                     secondaryTensor:(MPSGraphTensor *) secondaryTensor
                                      resultDataType:(MPSDataType) resultDataType
                                                name:(NSString * _Nullable) name
MPS_SWIFT_NAME( HammingDistance(primary:secondary:resultDataType:name:) )
MPS_AVAILABLE_STARTING(macos(13.0), ios(16.0), tvos(16.0));


@end


NS_ASSUME_NONNULL_END

#endif /* MPSGraphMatrixMultiplicationOps_h */
