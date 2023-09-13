//
//  MPSGraphReductionOps.h
//  MetalPerformanceShadersGraph
//
//  Created on 12/13/19.
//  Copyright © 2019 Apple Inc. All rights reserved.
//

#ifndef MPSGraphReductionOps_h
#define MPSGraphReductionOps_h

#import <MetalPerformanceShadersGraph/MPSGraph.h>

NS_ASSUME_NONNULL_BEGIN

MPS_CLASS_AVAILABLE_STARTING(macos(11.0), ios(14.0), tvos(14.0))
@interface MPSGraph(MPSGraphReductionOps)

/// Create reduction sum op and return the result tensor.
///
/// - Parameters:
///   - tensor: input tensor
///   - axis: axis of reduction
///   - name: name for the operation
/// - Returns: A valid MPSGraphTensor object.
- (MPSGraphTensor *) reductionSumWithTensor:(MPSGraphTensor *) tensor
                                       axis:(NSInteger) axis
                                       name:(NSString * _Nullable) name;

/// Create reduction sum op and return the result tensor.
///
/// - Parameters:
///   - tensor: input tensor
///   - axes: axes of reduction
///   - name: name for the operation
/// - Returns: A valid MPSGraphTensor object.
- (MPSGraphTensor *) reductionSumWithTensor:(MPSGraphTensor *)tensor
                                       axes:(NSArray<NSNumber *> *_Nullable)axes
                                       name:(NSString *_Nullable)name;

/// Create reduction max op and return the result tensor.
///
/// - Parameters:
///   - tensor: input tensor
///   - axis: axis of reduction
///   - name: name for the operation
/// - Returns: A valid MPSGraphTensor object.
-(MPSGraphTensor *) reductionMaximumWithTensor:(MPSGraphTensor *) tensor
                                          axis:(NSInteger) axis
                                          name:(NSString * _Nullable) name;

/// Create reduction max op and return the result tensor.
///
/// - Parameters:
///   - tensor: input tensor
///   - axes: axes of reduction
///   - name: name for the operation
/// - Returns: A valid MPSGraphTensor object.
- (MPSGraphTensor *) reductionMaximumWithTensor:(MPSGraphTensor *)tensor
                                           axes:(NSArray<NSNumber *> *_Nullable)axes
                                           name:(NSString *_Nullable)name;

/// Create reduction minimum op and return the result tensor.
///
/// - Parameters:
///   - tensor: input tensor
///   - axis: axis of reduction
///   - name: name for the operation
/// - Returns: A valid MPSGraphTensor object.
- (MPSGraphTensor *) reductionMinimumWithTensor:(MPSGraphTensor *) tensor
                                           axis:(NSInteger) axis
                                           name:(NSString * _Nullable) name;

/// Create reduction min op and return the result tensor.
///
/// - Parameters:
///   - tensor: input tensor
///   - axes: axes of reduction
///   - name: name for the operation
/// - Returns: A valid MPSGraphTensor object.
-(MPSGraphTensor *) reductionMinimumWithTensor:(MPSGraphTensor *)tensor
                                          axes:(NSArray<NSNumber *> *_Nullable)axes
                                          name:(NSString *_Nullable)name;

/// Create reduction max propagate NaN op and return the result tensor.
///
/// - Parameters:
///   - tensor: input tensor
///   - axis: axis of reduction
///   - name: name for the operation
/// - Returns: A valid MPSGraphTensor object.
- (MPSGraphTensor *) reductionMaximumPropagateNaNWithTensor:(MPSGraphTensor *) tensor
                                                       axis:(NSInteger) axis
                                                       name:(NSString * _Nullable) name;

/// Create reduction max propagate NaN op and return the result tensor.
///
/// - Parameters:
///   - tensor: input tensor
///   - axes: axes of reduction
///   - name: name for the operation
/// - Returns: A valid MPSGraphTensor object.
- (MPSGraphTensor *) reductionMaximumPropagateNaNWithTensor:(MPSGraphTensor *)tensor
                                                       axes:(NSArray<NSNumber *> *_Nullable)axes
                                                       name:(NSString *_Nullable)name;

/// Create reduction min propagate NaN op and return the result tensor.
///
/// - Parameters:
///   - tensor: input tensor
///   - axis: axis of reduction
///   - name: name for the operation
/// - Returns: A valid MPSGraphTensor object.
- (MPSGraphTensor *) reductionMinimumPropagateNaNWithTensor:(MPSGraphTensor *) tensor
                                                       axis:(NSInteger) axis
                                                       name:(NSString * _Nullable) name;

/// Create reduction min propagate NaN op and return the result tensor.
///
/// - Parameters:
///   - tensor: input tensor
///   - axes: axes of reduction
///   - name: name for the operation
/// - Returns: A valid MPSGraphTensor object.
- (MPSGraphTensor *) reductionMinimumPropagateNaNWithTensor:(MPSGraphTensor *)tensor
                                                       axes:(NSArray<NSNumber *> *_Nullable)axes
                                                       name:(NSString *_Nullable)name;

/// Create reduction product op and return the result tensor.
///
/// - Parameters:
///   - tensor: input tensor
///   - axis: axis of reduction
///   - name: name for the operation
/// - Returns: A valid MPSGraphTensor object.
-(MPSGraphTensor *) reductionProductWithTensor:(MPSGraphTensor *) tensor
                                          axis:(NSInteger) axis
                                          name:(NSString * _Nullable) name;


/// Create reduction product op and return the result tensor.
///
/// - Parameters:
///   - tensor: input tensor
///   - axes: axes of reduction
///   - name: name for the operation
/// - Returns: A valid MPSGraphTensor object.
- (MPSGraphTensor *) reductionProductWithTensor:(MPSGraphTensor *)tensor
                                           axes:(NSArray<NSNumber *> *_Nullable)axes
                                           name:(NSString *_Nullable)name;

/// Create reduction argMax op and return the result tensor.
///
/// - Parameters:
///   - tensor: input tensor
///   - axis: axis of reduction
///   - name: name for the operation
/// - Returns: A valid MPSGraphTensor object.
- (MPSGraphTensor *) reductionArgMaximumWithTensor:(MPSGraphTensor *)tensor
                                              axis:(NSInteger)axis
                                              name:(NSString *_Nullable)name
MPS_AVAILABLE_STARTING(macos(12.0), ios(15.0), macCatalyst(15.0), tvos(15.0));

/// Create reduction argMin op and return the result tensor.
///
/// - Parameters:
///   - tensor: input tensor
///   - axis: axis of reduction
///   - name: name for the operation
/// - Returns: A valid MPSGraphTensor object.
-(MPSGraphTensor *) reductionArgMinimumWithTensor:(MPSGraphTensor *)tensor
                                             axis:(NSInteger)axis
                                             name:(NSString *_Nullable)name
MPS_AVAILABLE_STARTING(macos(12.0), ios(15.0), macCatalyst(15.0), tvos(15.0));

/// Create reduction and op and return the result tensor.
///
/// - Parameters:
///   - tensor: input tensor
///   - axis: axis of reduction
///   - name: name for the operation
/// - Returns: A valid MPSGraphTensor object.
- (MPSGraphTensor *) reductionAndWithTensor:(MPSGraphTensor *) tensor
                                       axis:(NSInteger) axis
                                       name:(NSString * _Nullable) name
MPS_AVAILABLE_STARTING(macos(12.2), ios(15.3), macCatalyst(15.3), tvos(15.3));


/// Create reduction and op and return the result tensor.
///
/// - Parameters:
///   - tensor: input tensor
///   - axes: axes of reduction
///   - name: name for the operation
/// - Returns: A valid MPSGraphTensor object.
- (MPSGraphTensor *) reductionAndWithTensor:(MPSGraphTensor *)tensor
                                       axes:(NSArray<NSNumber *> *_Nullable)axes
                                       name:(NSString *_Nullable)name
MPS_AVAILABLE_STARTING(macos(12.2), ios(15.3), macCatalyst(15.3), tvos(15.3));

/// Create reduction or op and return the result tensor.
///
/// - Parameters:
///   - tensor: input tensor
///   - axis: axis of reduction
///   - name: name for the operation
/// - Returns: A valid MPSGraphTensor object.
- (MPSGraphTensor *) reductionOrWithTensor:(MPSGraphTensor *) tensor
                                      axis:(NSInteger) axis
                                      name:(NSString * _Nullable) name
MPS_AVAILABLE_STARTING(macos(12.2), ios(15.3), macCatalyst(15.3), tvos(15.3));


/// Create reduction or op and return the result tensor.
///
/// - Parameters:
///   - tensor: input tensor
///   - axes: axes of reduction
///   - name: name for the operation
/// - Returns: A valid MPSGraphTensor object.
- (MPSGraphTensor *) reductionOrWithTensor:(MPSGraphTensor *)tensor
                                      axes:(NSArray<NSNumber *> *_Nullable)axes
                                      name:(NSString *_Nullable)name
MPS_AVAILABLE_STARTING(macos(12.2), ios(15.3), macCatalyst(15.3), tvos(15.3));

@end

NS_ASSUME_NONNULL_END

#endif /* MPSGraphReductionOps_h */
