//
//  MPSGraphSortOps.h
//  MPSGraph
//
//  Created by Matteo Franciolini on 6/30/22.
//  Copyright © 2022 Apple Inc. All rights reserved.
//

#ifndef MPSGraphSortOps_h
#define MPSGraphSortOps_h

#import <MetalPerformanceShadersGraph/MPSGraph.h>

NS_ASSUME_NONNULL_BEGIN

MPS_CLASS_AVAILABLE_STARTING(macos(11.0), ios(14.0), tvos(14.0))
@interface MPSGraph(MPSGraphSortOps)

/*!
 *  @abstract   Create a sort operation and return the result tensor.
 *
 *  @param      tensor              input tensor
 *  @param      axis                  the tensor dimension over which the sort occurs
 *  @param      descending     wether to sort or not in descending order
 *  @param      name                  name for the operation
 *
 *  @return     A valid MPSGraphTensor object.
 */
-(MPSGraphTensor *) sortWithTensor:(MPSGraphTensor *) tensor
                              axis:(NSInteger) axis
                        descending:(BOOL) descending
                              name:(NSString * _Nullable) name
MPS_SWIFT_NAME( sort(_:axis:descending:name:))
MPS_AVAILABLE_STARTING(macos(13.0), ios(16.0), tvos(16.0));

/*!
 *  @abstract   Create a sort operation and return the result tensor.
 *
 *  @param      tensor              input tensor
 *  @param      axisTensor     the tensor dimension over which the sort occurs
 *  @param      descending     wether to sort or not in descending order
 *  @param      name                  name for the operation
 *
 *  @return     A valid MPSGraphTensor object.
 */
-(MPSGraphTensor *) sortWithTensor:(MPSGraphTensor *) tensor
                        axisTensor:(MPSGraphTensor *) axisTensor
                        descending:(BOOL) descending
                              name:(NSString * _Nullable) name
MPS_SWIFT_NAME( sort(_:axisTensor:descending:name:))
MPS_AVAILABLE_STARTING(macos(13.0), ios(16.0), tvos(16.0));

/*!
 *  @abstract   Create an ascending sort operation and return the result tensor.
 *
 *  @param      tensor        input tensor
 *  @param      axis            the tensor dimension over which the sort occurs
 *  @param      name            name for the operation
 *
 *  @return     A valid MPSGraphTensor object.
 */
-(MPSGraphTensor *) sortWithTensor:(MPSGraphTensor *) tensor
                              axis:(NSInteger) axis
                              name:(NSString * _Nullable) name
MPS_SWIFT_NAME( sort(_:axis:name:))
MPS_AVAILABLE_STARTING(macos(13.0), ios(16.0), tvos(16.0));

/*!
 *  @abstract   Create an ascending sort operation and return the result tensor.
 *
 *  @param      tensor            input tensor
 *  @param      axisTensor   the tensor dimension over which the sort occurs
 *  @param      name                name for the operation
 *
 *  @return     A valid MPSGraphTensor object.
 */
-(MPSGraphTensor *) sortWithTensor:(MPSGraphTensor *) tensor
                        axisTensor:(MPSGraphTensor *) axisTensor
                              name:(NSString * _Nullable) name
MPS_SWIFT_NAME( sort(_:axisTensor:name:))
MPS_AVAILABLE_STARTING(macos(13.0), ios(16.0), tvos(16.0));

/*!
 *  @abstract   Create an argSort operation and return the result tensor of signed
 *              32-bit integers.
 *
 *  @param      tensor              input tensor
 *  @param      axis                  the tensor dimension over which the sort occurs
 *  @param      descending     whether or not to sort in descending order
 *  @param      name                  name for the operation
 *
 *  @return     A valid MPSGraphTensor object.
 */
-(MPSGraphTensor *) argSortWithTensor:(MPSGraphTensor *) tensor
                                 axis:(NSInteger) axis
                           descending:(BOOL) descending
                                 name:(NSString * _Nullable) name
MPS_SWIFT_NAME( argSort(_:axis:descending:name:))
MPS_AVAILABLE_STARTING(macos(13.0), ios(16.1), tvos(16.1));

/*!
 *  @abstract   Create an argSort operation and return the result tensor of signed
 *              32-bit integers.
 *
 *  @param      tensor              input tensor
 *  @param      axisTensor     the tensor dimension over which the sort occurs
 *  @param      descending     whether or not to sort in descending order
 *  @param      name                  name for the operation
 *
 *  @return     A valid MPSGraphTensor object.
 */
-(MPSGraphTensor *) argSortWithTensor:(MPSGraphTensor *) tensor
                           axisTensor:(MPSGraphTensor *) axisTensor
                           descending:(BOOL) descending
                                 name:(NSString * _Nullable) name
MPS_SWIFT_NAME( argSort(_:axisTensor:descending:name:))
MPS_AVAILABLE_STARTING(macos(13.0), ios(16.1), tvos(16.1));

/*!
 *  @abstract   Create an argSort operation and return the result tensor of signed
 *              32-bit integers.
 *
 *  @param      tensor        input tensor
 *  @param      axis            the tensor dimension over which the sort occurs
 *  @param      name            name for the operation
 *
 *  @return     A valid MPSGraphTensor object.
 */
-(MPSGraphTensor *) argSortWithTensor:(MPSGraphTensor *) tensor
                                 axis:(NSInteger) axis
                                 name:(NSString * _Nullable) name
MPS_SWIFT_NAME( argSort(_:axis:name:))
MPS_AVAILABLE_STARTING(macos(13.0), ios(16.1), tvos(16.1));

/*!
 *  @abstract   Create an argSort operation and return the result tensor of signed
 *              32-bit integers.
 *
 *  @param      tensor            input tensor
 *  @param      axisTensor   the tensor dimension over which the sort occurs
 *  @param      name                name for the operation
 *
 *  @return     A valid MPSGraphTensor object.
 */
-(MPSGraphTensor *) argSortWithTensor:(MPSGraphTensor *) tensor
                           axisTensor:(MPSGraphTensor *) axisTensor
                                 name:(NSString * _Nullable) name
MPS_SWIFT_NAME( argSort(_:axisTensor:name:))
MPS_AVAILABLE_STARTING(macos(13.0), ios(16.1), tvos(16.1));

@end

NS_ASSUME_NONNULL_END

#endif /* MPSGraphArgSortOps_h */
