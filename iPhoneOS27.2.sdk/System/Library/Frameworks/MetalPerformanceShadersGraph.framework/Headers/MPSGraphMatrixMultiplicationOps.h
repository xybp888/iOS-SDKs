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

/// A descriptor that configures a scaled dot product attention (SDPA) operation.
///
/// Use this descriptor with
/// ``MPSGraph/scaledDotProductAttentionWithQueryTensor:keyTensor:valueTensor:descriptor:name:``
/// to specify optional features such as an attention mask, causal masking, and attention sinks.
MPS_CLASS_AVAILABLE_STARTING(macos(27.0), ios(27.0), macCatalyst(27.0), tvos(27.0))
@interface MPSGraphSDPADescriptor : MPSGraphObject

/// The scale applied to the result of the query–key matrix multiply before softmax.
/// Typically set to ``1/sqrt(headDimension)``.
@property(nonatomic) float scale;

/// An optional additive mask tensor applied to the scaled QK^T scores before softmax.
/// Must be broadcast-compatible with shape ``[batch, heads, T_q, T_kv]``.
/// Mutually exclusive with ``isCausal``.
@property(nonatomic, retain, nullable) MPSGraphTensor *maskTensor;

/// When YES, a causal (lower-triangular) mask is applied so that each query position
/// attends only to key positions at or before it. Mutually exclusive with ``maskTensor``.
@property(nonatomic) BOOL isCausal;

/// An optional attention-sinks tensor of shape ``[nHeads]``. Each element seeds the
/// online-softmax accumulator for the corresponding query head with a virtual token logit,
/// causing real-token attention weights to sum to less than one.
@property(nonatomic, retain, nullable) MPSGraphTensor *sinksTensor;

/// Creates a descriptor with the given scale and all other properties set to their defaults
/// (no mask, isCausal = NO, no sinks).
+ (instancetype)descriptorWithScale:(float)scale;

@end

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

/// Computes the hamming distance of two input tensors with support for broadcasting.
///
/// The hamming distance is computed between 2 sets of vectors and the last dimension(s) of each 
/// input tensor is considered a vector.
///
/// - Parameters:
///   - primaryTensor: The first input tensor.
///   - secondaryTensor: The second input tensor.
///   - resultDataType: The datatype of the return MPSGraphTensor. Must be either ``MPSDataTypeUInt32`` or ``MPSDataTypeUInt16``.
///   - name: The name for the operation.
/// - Returns: A valid tensor containing the hamming distance between the input tensors.
-(MPSGraphTensor *) HammingDistanceWithPrimaryTensor:(MPSGraphTensor *) primaryTensor
                                     secondaryTensor:(MPSGraphTensor *) secondaryTensor
                                      resultDataType:(MPSDataType) resultDataType
                                                name:(NSString * _Nullable) name
MPS_SWIFT_NAME( HammingDistance(primary:secondary:resultDataType:name:) )
MPS_AVAILABLE_STARTING(macos(13.0), ios(16.0), tvos(16.0));

/// Creates a scaled dot product attention (SDPA) operation and returns the result tensor.
///
/// SDPA Op computes attention by computing softmax(scale * QK^T + M)V.
/// queryTensor Q with shape [B, Hq, Nq, F] and keyTensor K with shape [B, Hq, Nkv, F],
/// with Q's H dimension expandable to satisfy matmul QK^T. maskTensor M's shape
/// should be broadcast compatible to satisfy (QK^T + M). valueTensor V with shape
/// [B, Hv, Nkv, F] should satisfy the matmul (QK^T + M)V.
///
/// - Parameters:
///   - queryTensor: A tensor that represents the query projection.
///   - keyTensor: A tensor that represents the key projection.
///   - valueTensor: A tensor that represents the value projection.
///   - maskTensor: An optional tensor that contains a mask that is applied to the scaled, matrix
///   multiplied query and value matrices. If mask tensor is nil, the QK^T is not element-wise masked.
///   - scale: A scale that is applied to the result of query and value matrix multiply.
///   - name: The name for the operation.
/// - Returns: A valid MPSGraphTensor object.
- (MPSGraphTensor *)scaledDotProductAttentionWithQueryTensor:(MPSGraphTensor *)queryTensor
                                                   keyTensor:(MPSGraphTensor *)keyTensor
                                                 valueTensor:(MPSGraphTensor *)valueTensor
                                                  maskTensor:(MPSGraphTensor *_Nullable)maskTensor
                                                       scale:(float)scale
                                                        name:(NSString *_Nullable)name
    MPS_SWIFT_NAME(scaledDotProductAttention(query:key:value:mask:scale:name:) )
MPS_AVAILABLE_STARTING(macos(15.0), ios(18.0), macCatalyst(18.0), tvos(18.0));

/// Creates a scaled dot product attention (SDPA) operation (without a mask) and returns the result tensor.
///
/// - Parameters:
///   - queryTensor: A tensor that represents the query projection.
///   - keyTensor: A tensor that represents the key projection.
///   - valueTensor: A tensor that represents the value projection.
///   - scale: A scale that is applied on the result of query and value matrix multiply.
///   - name: The name for the operation.
/// - Returns: A valid MPSGraphTensor object.
- (MPSGraphTensor *)scaledDotProductAttentionWithQueryTensor:(MPSGraphTensor *)queryTensor
                                                   keyTensor:(MPSGraphTensor *)keyTensor
                                                 valueTensor:(MPSGraphTensor *)valueTensor
                                                       scale:(float)scale
                                                        name:(NSString *_Nullable)name
    MPS_SWIFT_NAME(scaledDotProductAttention(query:key:value:scale:name:) )
MPS_AVAILABLE_STARTING(macos(15.0), ios(18.0), macCatalyst(18.0), tvos(18.0));

/// Creates a scaled dot product attention (SDPA) operation using a descriptor and returns the result tensor.
///
/// The descriptor allows configuring an optional attention mask, causal masking, and attention sinks
/// without requiring a separate API method for each combination of features.
///
/// - Parameters:
///   - queryTensor: A tensor that represents the query projection.
///   - keyTensor: A tensor that represents the key projection.
///   - valueTensor: A tensor that represents the value projection.
///   - descriptor: A descriptor specifying scale and optional features (mask, isCausal, sinks).
///   - name: The name for the operation.
/// - Returns: A valid MPSGraphTensor object.
- (MPSGraphTensor *)scaledDotProductAttentionWithQueryTensor:(MPSGraphTensor *)queryTensor
                                                   keyTensor:(MPSGraphTensor *)keyTensor
                                                 valueTensor:(MPSGraphTensor *)valueTensor
                                                  descriptor:(MPSGraphSDPADescriptor *)descriptor
                                                        name:(NSString *_Nullable)name
    MPS_SWIFT_NAME(scaledDotProductAttention(query:key:value:descriptor:name:))
        MPS_AVAILABLE_STARTING(macos(27.0), ios(27.0), macCatalyst(27.0), tvos(27.0));
@end


NS_ASSUME_NONNULL_END

#endif /* MPSGraphMatrixMultiplicationOps_h */
