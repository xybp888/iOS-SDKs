//
//  MPSGraphCumulativeOps.h
//  MetalPerformanceShadersGraph
//
//  Created on 06/12/22.
//  Copyright © 2022 Apple Inc. All rights reserved.
//

#ifndef MPSGraphScanOps_h
#define MPSGraphScanOps_h

#import <MetalPerformanceShadersGraph/MPSGraph.h>

NS_ASSUME_NONNULL_BEGIN

MPS_CLASS_AVAILABLE_STARTING(macos(11.0), ios(14.0), tvos(14.0))
@interface MPSGraph(MPSGraphCumulativeOps)

/*!
 *  @abstract   Create the cumulative sum op and return the result tensor.
 *
 *  @param      tensor          input tensor
 *  @param      axis              the tensor dimension over which the cumulative operation occurs
 *  @param      exclusive   if true, performs the exclusive cumulative sum operation, and the first element will be equal to zero.
 *  @param      reverse       reverse the direction of the cumulative sum operation along the given axis
 *  @param      name              name for the operation
 *
 *  @return     A valid MPSGraphTensor object.
 */
-(MPSGraphTensor *) cumulativeSumWithTensor:(MPSGraphTensor *) tensor
                                       axis:(NSInteger) axis
                                  exclusive:(BOOL) exclusive
                                    reverse:(BOOL) reverse
                                       name:(NSString * _Nullable) name
MPS_SWIFT_NAME( cumulativeSum(_:axis:exclusive:reverse:name:))
MPS_AVAILABLE_STARTING(macos(13.0), ios(16.0), tvos(16.0));

/*!
 *  @abstract   Create the cumulative sum op and return the result tensor.
 *
 *  @param      tensor              input tensor
 *  @param      axisTensor     the tensor dimension over which the cumulative operation occurs
 *  @param      exclusive       if true, performs the exclusive cumulative sum operation, and the first element will be equal to zero.
 *  @param      reverse           reverse the direction of the cumulative sum operation along the given axis
 *  @param      name                  name for the operation
 *
 *  @return     A valid MPSGraphTensor object.
 */
-(MPSGraphTensor *) cumulativeSumWithTensor:(MPSGraphTensor *) tensor
                                 axisTensor:(MPSGraphTensor *) axisTensor
                                  exclusive:(BOOL) exclusive
                                    reverse:(BOOL) reverse
                                       name:(NSString * _Nullable) name
MPS_SWIFT_NAME( cumulativeSum(_:axisTensor:exclusive:reverse:name:))
MPS_AVAILABLE_STARTING(macos(13.0), ios(16.0), tvos(16.0));

/*!
 *  @abstract   Create the inclusive cumulative sum op and return the result tensor.
 *
 *  @param      tensor          input tensor
 *  @param      axis              the tensor dimension over which the cumulative operation occurs
 *  @param      name              name for the operation
 *
 *  @return     A valid MPSGraphTensor object.
 */
-(MPSGraphTensor *) cumulativeSumWithTensor:(MPSGraphTensor *) tensor
                                       axis:(NSInteger) axis
                                       name:(NSString * _Nullable) name
MPS_SWIFT_NAME( cumulativeSum(_:axis:name:))
MPS_AVAILABLE_STARTING(macos(13.0), ios(16.0), tvos(16.0));

/*!
 *  @abstract   Create the inclusive cumulative sum op and return the result tensor.
 *
 *  @param      tensor             input tensor
 *  @param      axisTensor    the tensor dimension over which the cumulative operation occurs
 *  @param      name                 name for the operation
 *
 *  @return     A valid MPSGraphTensor object.
 */
-(MPSGraphTensor *) cumulativeSumWithTensor:(MPSGraphTensor *) tensor
                                 axisTensor:(MPSGraphTensor *) axisTensor
                                       name:(NSString * _Nullable) name
MPS_SWIFT_NAME( cumulativeSum(_:axisTensor:name:))
MPS_AVAILABLE_STARTING(macos(13.0), ios(16.0), tvos(16.0));

/*!
 *  @abstract   Create the cumulative product op and return the result tensor.
 *
 *  @param      tensor          input tensor
 *  @param      axis              the tensor dimension over which the cumulative operation occurs
 *  @param      exclusive   if true, performs the exclusive cumulative product operation, and the first element will be equal to one.
 *  @param      reverse       reverse the direction of the cumulative product operation along the given axis
 *  @param      name              name for the operation
 *
 *  @return     A valid MPSGraphTensor object.
 */
-(MPSGraphTensor *) cumulativeProductWithTensor:(MPSGraphTensor *) tensor
                                           axis:(NSInteger) axis
                                      exclusive:(BOOL) exclusive
                                        reverse:(BOOL) reverse
                                           name:(NSString * _Nullable) name
MPS_SWIFT_NAME( cumulativeProduct(_:axis:exclusive:reverse:name:))
MPS_AVAILABLE_STARTING(macos(13.0), ios(16.0), tvos(16.0));

/*!
 *  @abstract   Create the cumulative product op and return the result tensor.
 *
 *  @param      tensor              input tensor
 *  @param      axisTensor     the tensor dimension over which the cumulative operation occurs
 *  @param      exclusive       if true, performs the exclusive cumulative product operation, and the first element will be equal to one.
 *  @param      reverse           reverse the direction of the cumulative product operation along the given axis
 *  @param      name                  name for the operation
 *
 *  @return     A valid MPSGraphTensor object.
 */
-(MPSGraphTensor *) cumulativeProductWithTensor:(MPSGraphTensor *) tensor
                                     axisTensor:(MPSGraphTensor *) axisTensor
                                      exclusive:(BOOL) exclusive
                                        reverse:(BOOL) reverse
                                           name:(NSString * _Nullable) name
MPS_SWIFT_NAME( cumulativeProduct(_:axisTensor:exclusive:reverse:name:))
MPS_AVAILABLE_STARTING(macos(13.0), ios(16.0), tvos(16.0));

/*!
 *  @abstract   Create the inclusive cumulative product op and return the result tensor.
 *
 *  @param      tensor          input tensor
 *  @param      axis              the tensor dimension over which the cumulative operation occurs
 *  @param      name              name for the operation
 *
 *  @return     A valid MPSGraphTensor object.
 */
-(MPSGraphTensor *) cumulativeProductWithTensor:(MPSGraphTensor *) tensor
                                           axis:(NSInteger) axis
                                           name:(NSString * _Nullable) name
MPS_SWIFT_NAME( cumulativeProduct(_:axis:name:))
MPS_AVAILABLE_STARTING(macos(13.0), ios(16.0), tvos(16.0));

/*!
 *  @abstract   Create the inclusive cumulative product op and return the result tensor.
 *
 *  @param      tensor              input tensor
 *  @param      axisTensor     the tensor dimension over which the cumulative operation occurs
 *  @param      name                  name for the operation
 *
 *  @return     A valid MPSGraphTensor object.
 */
-(MPSGraphTensor *) cumulativeProductWithTensor:(MPSGraphTensor *) tensor
                                     axisTensor:(MPSGraphTensor *) axisTensor
                                           name:(NSString * _Nullable) name
MPS_SWIFT_NAME( cumulativeProduct(_:axisTensor:name:))
MPS_AVAILABLE_STARTING(macos(13.0), ios(16.0), tvos(16.0));

/*!
 *  @abstract   Create the cumulative minimum op and return the result tensor.
 *
 *  @param      tensor          input tensor
 *  @param      axis              the tensor dimension over which the cumulative operation occurs
 *  @param      exclusive   if true, performs the exclusive cumulative minimum operation, and the first element will be equal to the highest value of data type.
 *  @param      reverse       reverse the direction of the cumulative minimum operation along the given axis
 *  @param      name              name for the operation
 *
 *  @return     A valid MPSGraphTensor object.
 */
-(MPSGraphTensor *) cumulativeMinimumWithTensor:(MPSGraphTensor *) tensor
                                           axis:(NSInteger) axis
                                      exclusive:(BOOL) exclusive
                                        reverse:(BOOL) reverse
                                           name:(NSString * _Nullable) name
MPS_SWIFT_NAME( cumulativeMinimum(_:axis:exclusive:reverse:name:))
MPS_AVAILABLE_STARTING(macos(13.0), ios(16.0), tvos(16.0));

/*!
 *  @abstract   Create the cumulative minimum op and return the result tensor.
 *
 *  @param      tensor              input tensor
 *  @param      axisTensor     the tensor dimension over which the cumulative operation occurs
 *  @param      exclusive       if true, performs the exclusive cumulative minimum operation, and the first element will be equal to the highest value of data type.
 *  @param      reverse           reverse the direction of the cumulative minimum operation along the given axis
 *  @param      name                  name for the operation
 *
 *  @return     A valid MPSGraphTensor object.
 */
-(MPSGraphTensor *) cumulativeMinimumWithTensor:(MPSGraphTensor *) tensor
                                     axisTensor:(MPSGraphTensor *) axisTensor
                                      exclusive:(BOOL) exclusive
                                        reverse:(BOOL) reverse
                                           name:(NSString * _Nullable) name
MPS_SWIFT_NAME( cumulativeMinimum(_:axisTensor:exclusive:reverse:name:))
MPS_AVAILABLE_STARTING(macos(13.0), ios(16.0), tvos(16.0));

/*!
 *  @abstract   Create the inclusive cumulative minimum op and return the result tensor.
 *
 *  @param      tensor          input tensor
 *  @param      axis              the tensor dimension over which the cumulative operation occurs
 *  @param      name              name for the operation
 *
 *  @return     A valid MPSGraphTensor object.
 */
-(MPSGraphTensor *) cumulativeMinimumWithTensor:(MPSGraphTensor *) tensor
                                           axis:(NSInteger) axis
                                           name:(NSString * _Nullable) name
MPS_SWIFT_NAME( cumulativeMinimum(_:axis:name:))
MPS_AVAILABLE_STARTING(macos(13.0), ios(16.0), tvos(16.0));

/*!
 *  @abstract   Create the inclusive cumulative minimum op and return the result tensor.
 *
 *  @param      tensor              input tensor
 *  @param      axisTensor     the tensor dimension over which the cumulative operation occurs
 *  @param      name                  name for the operation
 *
 *  @return     A valid MPSGraphTensor object.
 */
-(MPSGraphTensor *) cumulativeMinimumWithTensor:(MPSGraphTensor *) tensor
                                     axisTensor:(MPSGraphTensor *) axisTensor
                                           name:(NSString * _Nullable) name
MPS_SWIFT_NAME( cumulativeMinimum(_:axisTensor:name:))
MPS_AVAILABLE_STARTING(macos(13.0), ios(16.0), tvos(16.0));

/*!
 *  @abstract   Create the cumulative maximum op and return the result tensor.
 *
 *  @param      tensor          input tensor
 *  @param      axis              the tensor dimension over which the cumulative operation occurs
 *  @param      exclusive   if true, performs the exclusive cumulative maximum operation, and the first element will be equal to the lowest value of data type.
 *  @param      reverse       reverse the direction of the cumulative maximum operation along the given axis
 *  @param      name              name for the operation
 *
 *  @return     A valid MPSGraphTensor object.
 */
-(MPSGraphTensor *) cumulativeMaximumWithTensor:(MPSGraphTensor *) tensor
                                           axis:(NSInteger) axis
                                      exclusive:(BOOL) exclusive
                                        reverse:(BOOL) reverse
                                           name:(NSString * _Nullable) name
MPS_SWIFT_NAME( cumulativeMaximum(_:axis:exclusive:reverse:name:))
MPS_AVAILABLE_STARTING(macos(13.0), ios(16.0), tvos(16.0));

/*!
 *  @abstract   Create the cumulative maximum op and return the result tensor.
 *
 *  @param      tensor              input tensor
 *  @param      axisTensor     the tensor dimension over which the cumulative operation occurs
 *  @param      exclusive       if true, performs the exclusive cumulative maximum operation, and the first element will be equal to the lowest value of data type.
 *  @param      reverse           reverse the direction of the cumulative maximum operation along the given axis
 *  @param      name                  name for the operation
 *
 *  @return     A valid MPSGraphTensor object.
 */
-(MPSGraphTensor *) cumulativeMaximumWithTensor:(MPSGraphTensor *) tensor
                                     axisTensor:(MPSGraphTensor *) axisTensor
                                      exclusive:(BOOL) exclusive
                                        reverse:(BOOL) reverse
                                           name:(NSString * _Nullable) name
MPS_SWIFT_NAME( cumulativeMaximum(_:axisTensor:exclusive:reverse:name:))
MPS_AVAILABLE_STARTING(macos(13.0), ios(16.0), tvos(16.0));

/*!
 *  @abstract   Create the inclusive cumulative maximum op and return the result tensor.
 *
 *  @param      tensor          input tensor
 *  @param      axis              the tensor dimension over which the cumulative operation occurs
 *  @param      name              name for the operation
 *
 *  @return     A valid MPSGraphTensor object.
 */
-(MPSGraphTensor *) cumulativeMaximumWithTensor:(MPSGraphTensor *) tensor
                                           axis:(NSInteger) axis
                                           name:(NSString * _Nullable) name
MPS_SWIFT_NAME( cumulativeMaximum(_:axis:name:))
MPS_AVAILABLE_STARTING(macos(13.0), ios(16.0), tvos(16.0));

/*!
 *  @abstract   Create the inclusive cumulative maximum op and return the result tensor.
 *
 *  @param      tensor              input tensor
 *  @param      axisTensor     the tensor dimension over which the cumulative operation occurs
 *  @param      name                  name for the operation
 *
 *  @return     A valid MPSGraphTensor object.
 */
-(MPSGraphTensor *) cumulativeMaximumWithTensor:(MPSGraphTensor *) tensor
                                     axisTensor:(MPSGraphTensor *) axisTensor
                                           name:(NSString * _Nullable) name
MPS_SWIFT_NAME( cumulativeMaximum(_:axisTensor:name:))
MPS_AVAILABLE_STARTING(macos(13.0), ios(16.0), tvos(16.0));

@end

NS_ASSUME_NONNULL_END

#endif /* MPSGraphCumulativeOps_h */
