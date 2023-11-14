//
//  MPSGraphTopKOps.h
//  MPSGraph
//
//  Created on 9/21/20.
//  Copyright © 2020 Apple Inc. All rights reserved.
//

#ifndef MPSGraphTopKOps_h
#define MPSGraphTopKOps_h

#import <MetalPerformanceShadersGraph/MPSGraph.h>

NS_ASSUME_NONNULL_BEGIN

MPS_CLASS_AVAILABLE_STARTING(macos(12.0), ios(15.0), tvos(15.0))
@interface MPSGraph(MPSGraphTopKOps)

/// Creates TopK op and return the value and indices tensors
///
/// Finds the k largest values along the minor dimension of the input. The source must have 
/// at least k elements along its minor dimension. 
/// The first element of the result array corresponds to the top values, and the second element of
/// the result array corresponds to the indices of the top values.
///
/// - Parameters:
///   - source: Tensor containing source data
///   - k: The number of largest values to return
///   - name: The name for the operation
/// - Returns: A valid MPSGraphTensor array of size 2
-(NSArray<MPSGraphTensor *> *) topKWithSourceTensor:(MPSGraphTensor *) source
                                                  k:(NSUInteger) k
                                               name:(NSString * _Nullable) name
MPS_SWIFT_NAME( topK(_:k:name:) );

/// Creates TopK op and return the result tensor.
///
/// Finds the k largest values along the minor dimension of the input. The source must have 
/// at least k elements along its minor dimension. 
/// The first element of the result array corresponds to the top values, and the second element of
/// the result array corresponds to the indices of the top values.
///
/// - Parameters:
///   - source: Tensor containing source data.
///   - kTensor: Tensor of the number of largest values to return.
///   - name: The name for the operation.
/// - Returns: A valid MPSGraphTensor array of size 2.
-(NSArray<MPSGraphTensor *> *) topKWithSourceTensor:(MPSGraphTensor *) source
                                            kTensor:(MPSGraphTensor *) kTensor
                                               name:(NSString * _Nullable) name
MPS_SWIFT_NAME( topK(_:kTensor:name:) );

/// Creates TopK op and return the value and indices tensors.
///
/// Finds the k largest values along the minor dimension of the input. The source must have
/// at least k elements along its minor dimension.
/// The first element of the result array corresponds to the top values, and the second
/// array corresponds to the indices of the top values.
///
/// - Parameters:
///   - source: Tensor containing source data.
///   - axis: The dimension along which to compute the TopK values.
///   - k: The number of largest values to return.
///   - name: The name for the operation.
/// - Returns: A valid MPSGraphTensor array of size 2.
-(NSArray<MPSGraphTensor *> *) topKWithSourceTensor:(MPSGraphTensor *) source
                                               axis:(NSInteger) axis
                                                  k:(NSUInteger) k
                                               name:(NSString * _Nullable) name
MPS_SWIFT_NAME( topK(_:axis:k:name:) )
MPS_AVAILABLE_STARTING(macos(14.0), ios(17.0), tvos(17.0));

/// Create BottomK op and return the value and indices tensors.
///
/// Finds the k smallest values along the minor dimension of the input. The source must have
/// at least k elements along its minor dimension.
/// The first element of the result array corresponds to the bottom values, and the second
/// array corresponds to the indices of the bottom values.
///
/// - Parameters:
///   - source: Tensor containing source data.
///   - axis: The dimension along which to compute the BottomK values.
///   - k: The number of largest values to return.
///   - name: The name for the operation.
/// - Returns: A valid MPSGraphTensor array of size 2.
-(NSArray<MPSGraphTensor *> *) bottomKWithSourceTensor:(MPSGraphTensor *) source
                                                  axis:(NSInteger) axis
                                                     k:(NSUInteger) k
                                                  name:(NSString * _Nullable) name
MPS_SWIFT_NAME( bottomK(_:axis:k:name:) )
MPS_AVAILABLE_STARTING(macos(14.0), ios(17.0), tvos(17.0));

/// Creates TopK op and return the result tensor..
///
/// Finds the k largest values along the minor dimension of the input. The source must have
/// at least k elements along its minor dimension.
/// The first element of the result array corresponds to the top values, and the second
/// array corresponds to the indices of the top values.
///
/// - Parameters:
///   - source: Tensor containing source data.
///   - axisTensor: Tensor containing the dimension along which to compute the TopK values.
///   - kTensor: Tensor of the number of largest values to return.
///   - name: The name for the operation.
/// - Returns: A valid MPSGraphTensor array of size 2.
-(NSArray<MPSGraphTensor *> *) topKWithSourceTensor:(MPSGraphTensor *) source
                                         axisTensor:(MPSGraphTensor *) axisTensor
                                            kTensor:(MPSGraphTensor *) kTensor
                                               name:(NSString * _Nullable) name
MPS_SWIFT_NAME( topK(_:axisTensor:kTensor:name:) )
MPS_AVAILABLE_STARTING(macos(14.0), ios(17.0), tvos(17.0));

/// Create BottomK op and return the result tensor.
///
/// Finds the k smallest values along the minor dimension of the input. The source must have
/// at least k elements along its minor dimension.
/// The first element of the result array corresponds to the bottom values, and the second
/// array corresponds to the indices of the bottom values.
///
/// - Parameters:
///   - source: Tensor containing source data.
///   - axisTensor: Tensor containing the dimension along which to compute the BottomK values.
///   - kTensor: Tensor of the number of largest values to return.
///   - name: The name for the operation.
/// - Returns: A valid MPSGraphTensor array of size 2.
-(NSArray<MPSGraphTensor *> *) bottomKWithSourceTensor:(MPSGraphTensor *) source
                                            axisTensor:(MPSGraphTensor *) axisTensor
                                               kTensor:(MPSGraphTensor *) kTensor
                                                  name:(NSString * _Nullable) name
MPS_SWIFT_NAME( bottomK(_:axisTensor:kTensor:name:) )
MPS_AVAILABLE_STARTING(macos(14.0), ios(17.0), tvos(17.0));

@end

@interface MPSGraph(MPSGraphTopKGradientOps)

/// Create TopKGradient op and return the result tensor.
///
/// Finds the K largest values along the minor dimension of the input. The input must have
/// at least K elements along its minor dimension.
///
/// - Parameters:
///   - gradient: Tensor containing the incoming gradient.
///   - source: Tensor containing source data.
///   - k: The number of largest values to return.
///   - name: The name for the operation.
/// - Returns: A valid MPSGraphTensor object.
-(MPSGraphTensor *) topKWithGradientTensor:(MPSGraphTensor *) gradient
                                    source:(MPSGraphTensor *) source
                                         k:(NSUInteger) k
                                      name:(NSString * _Nullable) name
MPS_SWIFT_NAME( topKGradient(_:input:k:name:) );

/// Create TopKGradient op and return the result tensor.
///
/// Finds the K largest values along the minor dimension of the input. The input must have
/// at least K elements along its minor dimension.
///
/// - Parameters:
///   - gradient: Tensor containing the incoming gradient.
///   - source: Tensor containing source data.
///   - axis: The dimension along which to compute the TopK values..
///   - k: The number of largest values to return.
///   - name: The name for the operation.
/// - Returns: A valid MPSGraphTensor object.
-(MPSGraphTensor *) topKWithGradientTensor:(MPSGraphTensor *) gradient
                                    source:(MPSGraphTensor *) source
                                      axis:(NSInteger) axis
                                         k:(NSUInteger) k
                                      name:(NSString * _Nullable) name
MPS_SWIFT_NAME( topKGradient(_:source:axis:k:name:) )
MPS_AVAILABLE_STARTING(macos(14.0), ios(17.0), tvos(17.0));

/// Create BottomKGradient op and return the result tensor.
///
/// Finds the K smallest values along the minor dimension of the input. The input must have
/// at least K elements along its minor dimension. 
///
/// - Parameters:
///   - gradient: Tensor containing the incoming gradient.
///   - source: Tensor containing source data.
///   - axis: The dimension along which to compute the BottomK values.
///   - k: The number of largest values to return.
///   - name: The name for the operation.
/// - Returns: A valid MPSGraphTensor object.
-(MPSGraphTensor *) bottomKWithGradientTensor:(MPSGraphTensor *) gradient
                                       source:(MPSGraphTensor *) source
                                         axis:(NSInteger) axis
                                            k:(NSUInteger) k
                                         name:(NSString * _Nullable) name
MPS_SWIFT_NAME( bottomKGradient(_:source:axis:k:name:) )
MPS_AVAILABLE_STARTING(macos(14.0), ios(17.0), tvos(17.0));

/// Create TopKGradient op and return the result tensor.
///
/// Finds the K largest values along the minor dimension of the input. The input must have
/// at least K elements along its minor dimension.
///
/// - Parameters:
///   - gradient: Tensor containing the incoming gradient.
///   - source: Tensor containing source data.
///   - kTensor: Tensor of the number of largest values to return.
///   - name: The name for the operation.
/// - Returns: A valid MPSGraphTensor object.
-(MPSGraphTensor *) topKWithGradientTensor:(MPSGraphTensor *) gradient
                                    source:(MPSGraphTensor *) source
                                   kTensor:(MPSGraphTensor *) kTensor
                                      name:(NSString * _Nullable) name
MPS_SWIFT_NAME( topKGradient(_:input:kTensor:name:) );

/// Create TopKGradient op and return the result tensor.
///
/// Finds the K largest values along the minor dimension of the input. The input must have
/// at least K elements along its minor dimension.
///
/// - Parameters:
///   - gradient: Tensor containing the incoming gradient.
///   - source: Tensor containing source data.
///   - axisTensor: Tensor containing the dimension along which to compute the TopK values.
///   - kTensor: Tensor of the number of largest values to return.
///   - name: The name for the operation.
/// - Returns: A valid MPSGraphTensor object.
-(MPSGraphTensor *) topKWithGradientTensor:(MPSGraphTensor *) gradient
                                    source:(MPSGraphTensor *) source
                                axisTensor:(MPSGraphTensor *) axisTensor
                                   kTensor:(MPSGraphTensor *) kTensor
                                      name:(NSString * _Nullable) name
MPS_SWIFT_NAME( topKGradient(_:source:axisTensor:kTensor:name:) )
MPS_AVAILABLE_STARTING(macos(14.0), ios(17.0), tvos(17.0));

/// Create BottomKGradient op and return the result tensor.
///
/// Finds the K smallest values along the minor dimension of the input. The input must have
/// at least K elements along its minor dimension. 
///
/// - Parameters:
///   - gradient: Tensor containing the incoming gradient.
///   - source: Tensor containing source data.
///   - axisTensor: Tensor containing the dimension along which to compute the BottomK values.
///   - kTensor: Tensor of the number of largest values to return.
///   - name: The name for the operation.
/// - Returns: A valid MPSGraphTensor object.
-(MPSGraphTensor *) bottomKWithGradientTensor:(MPSGraphTensor *) gradient
                                       source:(MPSGraphTensor *) source
                                   axisTensor:(MPSGraphTensor *) axisTensor
                                      kTensor:(MPSGraphTensor *) kTensor
                                         name:(NSString * _Nullable) name
MPS_SWIFT_NAME( bottomKGradient(_:source:axisTensor:kTensor:name:) )
MPS_AVAILABLE_STARTING(macos(14.0), ios(17.0), tvos(17.0));

@end

NS_ASSUME_NONNULL_END

#endif /* MPSGraphTopKOps_h */
