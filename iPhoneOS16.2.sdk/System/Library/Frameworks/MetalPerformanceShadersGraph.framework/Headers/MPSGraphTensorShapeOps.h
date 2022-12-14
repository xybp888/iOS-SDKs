//
//  MPSGraphTensorShapeOps.h
//  MetalPerformanceShadersGraph
//
//  Created on 12/16/19.
//  Copyright © 2019 Apple Inc. All rights reserved.
//

#ifndef MPSGraphTensorShapeOps_h
#define MPSGraphTensorShapeOps_h


#import <MetalPerformanceShadersGraph/MPSGraph.h>

NS_ASSUME_NONNULL_BEGIN

MPS_CLASS_AVAILABLE_STARTING(macos(11.0), ios(14.0), tvos(14.0))
@interface MPSGraph(MPSGraphTensorShapeOps)

/*!
 *  @abstract   Create Reshape op and return the result tensor
 *  @discussion Reshape the input tensor to the target shape
 *              The shape must be compatible with the input tensor shape
 *              shape is allowed to contain dynamic dimensions (-1) when the result type can be inferred unambiguously
 *
 *  @param      tensor                  Tensor to be reshaped.
 *  @param      shape                    The result tensor shape
 *  @param      name                      The name for the operation
 *
 *  @return     A valid MPSGraphTensor object
 */
-(MPSGraphTensor *) reshapeTensor:(MPSGraphTensor *) tensor
                        withShape:(MPSShape *) shape
                             name:(NSString * _Nullable) name
MPS_SWIFT_NAME( reshape(_:shape:name:) );

/*!
 *  @abstract   Create Reshape op and return the result tensor
 *  @discussion Reshape the input tensor to the target shapeTensor
 *              The shape must be compatible with the input tensor shape
 *              shapeTensor is allowed to contain dynamic dimensions (-1) when the result type can be inferred unambiguously
 *
 *  @param      tensor                  Tensor to be reshaped.
 *  @param      shapeTensor       1D Int32 or Int64 tensor. The result tensor shape
 *  @param      name                      The name for the operation
 *
 *  @return     A valid MPSGraphTensor object
 */
-(MPSGraphTensor *) reshapeTensor:(MPSGraphTensor *) tensor
                  withShapeTensor:(MPSGraphTensor *) shapeTensor
                             name:(NSString * _Nullable) name
MPS_AVAILABLE_STARTING(macos(12.0), ios(15.0), tvos(15.0))
MPS_SWIFT_NAME( reshape(_:shapeTensor:name:) );

-(MPSGraphTensor *) transposeTensor:(MPSGraphTensor *) tensor
                          dimension:(NSUInteger) dimensionIndex
                      withDimension:(NSUInteger) dimensionIndex2
                               name:(NSString * _Nullable) name;

-(MPSGraphTensor *) transposeTensor:(MPSGraphTensor *) tensor
                        permutation:(NSArray<NSNumber *> *) permutation
                               name:(NSString * _Nullable) name
MPS_AVAILABLE_STARTING(macos(13.0), ios(16.0), tvos(16.0))
MPS_SWIFT_NAME( transpose(_:permutation:name:) );

-(MPSGraphTensor *) sliceTensor:(MPSGraphTensor *) tensor
                      dimension:(NSUInteger) dimensionIndex
                          start:(NSInteger) start
                         length:(NSInteger) length
                           name:(NSString * _Nullable) name;

/*!
 *  @abstract   Create strided slice op and return the result tensor
 *  @discussion Slices a tensor starting from `starts`, stopping short before `ends` stepping
 *              `strides` paces between each value. Semantics based on
 *              https://www.tensorflow.org/api_docs/python/tf/strided_slice.
 *
 *  @param      tensor      Tensor to be sliced
 *  @param      starts      Array of numbers specifying starting point per dimension
 *  @param      ends          Array of numbers specifying ending point per dimension
 *  @param      strides   Array of numbers specifying strides per dimension
 *  @param      name           The name for the operation
 *
 *  @return     A valid MPSGraphTensor object
 */

-(MPSGraphTensor *) sliceTensor:(MPSGraphTensor *) tensor
                         starts:(NSArray<NSNumber *> *) starts
                           ends:(NSArray<NSNumber *> *) ends
                        strides:(NSArray<NSNumber *> *) strides
                           name:(NSString * _Nullable) name;

/*!
 *  @abstract   Create strided slice op and return the result tensor
 *  @discussion Slices a tensor starting from `starts`, stopping short before `ends` stepping
 *              `strides` paces between each value. Semantics based on
 *              https://www.tensorflow.org/api_docs/python/tf/strided_slice.
 *
 *  @param      tensor              Tensor to be sliced
 *  @param      starts              Array of numbers specifying starting point per dimension
 *  @param      ends                  Array of numbers specifying ending point per dimension
 *  @param      strides           Array of numbers specifying strides per dimension
 *  @param      startMask       Bitmask indicating dimensions whose `starts` values should be ignored.
 *  @param      endMask           Bitmask indicating dimensions whose `ends` values should be ignored.
 *  @param      squeezeMask   Bitmask indicating dimensions that should be squeezed out from the result.
 *  @param      name                  The name for the operation
 *
 *  @return     A valid MPSGraphTensor object
 */

-(MPSGraphTensor *) sliceTensor:(MPSGraphTensor *) tensor
                         starts:(NSArray<NSNumber *> *) starts
                           ends:(NSArray<NSNumber *> *) ends
                        strides:(NSArray<NSNumber *> *) strides
                      startMask:(uint32_t) startMask
                        endMask:(uint32_t) endMask
                    squeezeMask:(uint32_t) squeezeMask
                           name:(NSString * _Nullable) name;

/*!
 *  @abstract   Create strided slice gradient op and return the result tensor
 *
 *  @param      inputGradientTensor      Input gradient
 *  @param      fwdInShapeTensor    Shape of the forward pass input = shape of gradient output
 *  @param      starts      Array of numbers specifying starting point per dimension
 *  @param      ends          Array of numbers specifying ending point per dimension
 *  @param      strides   Array of numbers specifying strides per dimension
 *  @param      name           The name for the operation
 *
 *  @return     A valid MPSGraphTensor object
 */

-(MPSGraphTensor *) sliceGradientTensor:(MPSGraphTensor *) inputGradientTensor
                       fwdInShapeTensor:(MPSGraphTensor *) fwdInShapeTensor
                                 starts:(NSArray<NSNumber *> *) starts
                                   ends:(NSArray<NSNumber *> *) ends
                                strides:(NSArray<NSNumber *> *) strides
                                   name:(NSString * _Nullable) name;

/*!
 *  @abstract   Create strided slice gradient op and return the result tensor
 *
 *  @param      inputGradientTensor      Input gradient
 *  @param      fwdInShapeTensor    Shape of the forward pass input = shape of gradient output
 *  @param      starts              Array of numbers specifying starting point per dimension
 *  @param      ends                  Array of numbers specifying ending point per dimension
 *  @param      strides           Array of numbers specifying strides per dimension
 *  @param      startMask       Bitmask indicating dimensions whose `starts` values should be ignored.
 *  @param      endMask           Bitmask indicating dimensions whose `ends` values should be ignored.
 *  @param      squeezeMask   Bitmask indicating dimensions that should be squeezed out from the result.
 *  @param      name                  The name for the operation
 *
 *  @return     A valid MPSGraphTensor object
 */

-(MPSGraphTensor *) sliceGradientTensor:(MPSGraphTensor *) inputGradientTensor
                       fwdInShapeTensor:(MPSGraphTensor *) fwdInShapeTensor
                                 starts:(NSArray<NSNumber *> *) starts
                                   ends:(NSArray<NSNumber *> *) ends
                                strides:(NSArray<NSNumber *> *) strides
                              startMask:(uint32_t) startMask
                                endMask:(uint32_t) endMask
                            squeezeMask:(uint32_t) squeezeMask
                                   name:(NSString * _Nullable) name;

/*!
 *  @abstract   Create concat  op and return the result tensor
 *  @discussion Concatenate two input tensors along sepecified dimension. Tensors must be broadcast
 *              compatible along all other dimensions, and have the same type.
 *
 *  @param      tensor                         First tensor to concatenate
 *  @param      tensor2                       Second tensor to concatenate
 *  @param      dimensionIndex        The dimension to concatenate across, must be in range - rank <= dimension < rank
 *  @param      name                              The name for the operation
 *
 *  @return     A valid MPSGraphTensor object
 */

-(MPSGraphTensor *) concatTensor:(MPSGraphTensor *) tensor
                      withTensor:(MPSGraphTensor *) tensor2
                       dimension:(NSInteger) dimensionIndex
                            name:(NSString * _Nullable) name;

/*!
 *  @abstract   Create concat op and return the result tensor
 *  @discussion Concatenate all input tensors along specified dimension. All inputs must be broadcast
 *              compatible along all other dimensions, and have the same type.
 *
 *  @param      tensors                      Tensors to concatenate
 *  @param      dimensionIndex       The dimension to concatenate across, must be in range - rank <= dimension < rank
 *  @param      name                             The name for the operation
 *
 *  @return     A valid MPSGraphTensor object
 */
-(MPSGraphTensor *) concatTensors:(NSArray<MPSGraphTensor *> *) tensors
                        dimension:(NSInteger) dimensionIndex
                             name:(NSString * _Nullable) name;

/*!
 *  @abstract   Create concat op and return the result tensor
 *  @discussion Concatenate all input tensors along specified dimension. All inputs must be broadcast
 *              compatible along all other dimensions, and have the same type.
 *              When interleave is specified, all tensors will be interleaved. To interleave, all inputs must
 *              be broadcast compatible along the specified dimension as well.
 *              Example,
 *              @code
 *              operand0 = [1, 2, 3]
 *              operand1 = [4, 5, 6]
 *              concat([operand0, operand1], axis = 0, interleave = YES) = [1, 4, 2, 5, 3, 6]
 *              @endcode
 *
 *  @param      tensors                      Tensors to concatenate
 *  @param      dimensionIndex       The dimension to concatenate across, must be in range - rank <= dimension < rank
 *  @param      interleave                Interleave input tensors
 *  @param      name                             The name for the operation
 *
 *  @return     A valid MPSGraphTensor object
 */
-(MPSGraphTensor *) concatTensors:(NSArray<MPSGraphTensor *> *) tensors
                        dimension:(NSInteger) dimensionIndex
                       interleave:(BOOL) interleave
                             name:(NSString * _Nullable) name;

-(MPSGraphTensor *) tileTensor:(MPSGraphTensor *) tensor
                withMultiplier:(MPSShape *) multiplier
                          name:(NSString * _Nullable) name;

-(MPSGraphTensor *) tileGradientWithIncomingGradientTensor:(MPSGraphTensor *) incomingGradientTensor
                                              sourceTensor:(MPSGraphTensor *) sourceTensor
                                            withMultiplier:(MPSShape *) multiplier
                                                      name:(NSString * _Nullable) name;


-(MPSGraphTensor *)padTensor:(MPSGraphTensor *) tensor
             withPaddingMode:(MPSGraphPaddingMode)paddingMode
                 leftPadding:(MPSShape *) leftPadding
                rightPadding:(MPSShape *) rightPadding
               constantValue:(double)constantValue
                        name:(NSString * _Nullable) name;
                        
-(MPSGraphTensor *)padGradientWithIncomingGradientTensor:(MPSGraphTensor *) incomingGradientTensor
                                            sourceTensor:(MPSGraphTensor *) sourceTensor
                                             paddingMode:(MPSGraphPaddingMode)paddingMode
                                             leftPadding:(MPSShape *) leftPadding
                                            rightPadding:(MPSShape *) rightPadding
                                                    name:(NSString * _Nullable) name;

/*!
 *  @abstract   Create space-to-depth2d op and return the result tensor
 *  @discussion This operation outputs a copy of the `input` tensor, where values from the
 *              `widthAxis` and `heightAxis` dimensions are moved in spatial blocks of size
 *              `blockSize` to the `depthAxis` dimension. `usePixelShuffleOrder` can be
 *              used to control how the data within spatial blocks is ordered in the
 *              `depthAxis` dimension: with `usePixelShuffleOrder=YES` the values within the
 *              spatial blocks are stored contiguosly within the `depthAxis` dimension whereas
 *              otherwise they are stored interleaved with existing values in the `depthAxis`
 *              dimension.
 *              This operation is the inverse of `depthToSpace2D`.
 *
 *  @param      tensor                                      The input tensor.
 *  @param      widthAxis                               Axis that defines the fastest running dimension within the block.
 *  @param      heightAxis                             Axis that defines the 2nd fastest running dimension within the block.
 *  @param      depthAxis                               Axis that defines the destination dimension, where to copy the blocks.
 *  @param      blockSize                               Size of the square spatial sub-block.
 *  @param      usePixelShuffleOrder       Controls layout of the sub-blocks within the depth dimension.
 *  @param      name                                           The name for the operation.
 *
 *  @return     A valid MPSGraphTensor object
 */
-(MPSGraphTensor *)spaceToDepth2DTensor:(MPSGraphTensor *) tensor
                              widthAxis:(NSUInteger) widthAxis
                             heightAxis:(NSUInteger) heightAxis
                              depthAxis:(NSUInteger) depthAxis
                              blockSize:(NSUInteger) blockSize
                   usePixelShuffleOrder:(BOOL)usePixelShuffleOrder
                                   name:(NSString * _Nullable) name
MPS_AVAILABLE_STARTING(macos(12.0), ios(15.0), tvos(15.0));

-(MPSGraphTensor *)spaceToDepth2DTensor:(MPSGraphTensor *) tensor
                        widthAxisTensor:(MPSGraphTensor *) widthAxisTensor
                       heightAxisTensor:(MPSGraphTensor *) heightAxisTensor
                        depthAxisTensor:(MPSGraphTensor *) depthAxisTensor
                              blockSize:(NSUInteger)blockSize
                   usePixelShuffleOrder:(BOOL)usePixelShuffleOrder
                                   name:(NSString * _Nullable) name
MPS_AVAILABLE_STARTING(macos(12.0), ios(15.0), tvos(15.0));

/*!
 *  @abstract   Create depth-to-space2d op and return the result tensor
 *  @discussion This operation outputs a copy of the input tensor, where values from the
 *              `depthAxis` dimension are moved in spatial blocks of size `blockSize` to the
 *              `heightAxis` and `widthAxis` dimensions. `usePixelShuffleOrder` can be
 *              used to control how the data within spatial blocks is ordered in the
 *              `depthAxis` dimension: with `usePixelShuffleOrder = YES` the values within the
 *              spatial block are stored contiguosly within the `depthAxis` dimension whereas
 *              without it they are stored interleaved with existing values in the `depthAxisTensor`
 *              dimension.
 *              This operation is the inverse of `spaceToDepth2D`
 *
 *  @param      tensor                                      The input tensor.
 *  @param      widthAxis                               Axis that defines the fastest running dimension within the block.
 *  @param      heightAxis                             Axis that defines the 2nd fastest running dimension within the block.
 *  @param      depthAxis                               Axis that defines the source dimension, from which to copy the blocks.
 *  @param      blockSize                               Size of the square spatial sub-block.
 *  @param      usePixelShuffleOrder       Controls layout of the sub-blocks within the depth dimension.
 *  @param      name                                           The name for the operation.
 *
 *  @return     A valid MPSGraphTensor object.
 */
-(MPSGraphTensor *)depthToSpace2DTensor:(MPSGraphTensor *) tensor
                              widthAxis:(NSUInteger) widthAxis
                             heightAxis:(NSUInteger) heightAxis
                              depthAxis:(NSUInteger) depthAxis
                              blockSize:(NSUInteger)blockSize
                   usePixelShuffleOrder:(BOOL)usePixelShuffleOrder
                                   name:(NSString * _Nullable) name
MPS_AVAILABLE_STARTING(macos(12.0), ios(15.0), tvos(15.0));

-(MPSGraphTensor *)depthToSpace2DTensor:(MPSGraphTensor *) tensor
                        widthAxisTensor:(MPSGraphTensor *) widthAxisTensor
                       heightAxisTensor:(MPSGraphTensor *) heightAxisTensor
                        depthAxisTensor:(MPSGraphTensor *) depthAxisTensor
                              blockSize:(NSUInteger)blockSize
                   usePixelShuffleOrder:(BOOL)usePixelShuffleOrder
                                   name:(NSString * _Nullable) name
MPS_AVAILABLE_STARTING(macos(12.0), ios(15.0), tvos(15.0));

/*!
 *  @abstract   Create space-to-batch op and return the result tensor.
 *  @discussion This operation outputs a copy of the `input` tensor, where values from the
 *              `spatialAxes` (for `usePixelShuffleOrder=YES`1,2 or 3 axes supported, otherwise
 *              limited only by MPSNDArray rank limitations) dimensions are moved in spatial blocks with
 *              rectangular size defined by `blockDimensions` to the `batchAxis` dimension.
 *              `usePixelShuffleOrder` can be used to control how the data within spatial blocks is ordered
 *              in the `batchAxis` dimension: with `usePixelShuffleOrder=YES` the values within the
 *              spatial blocks are stored contiguosly within the `batchAxis` dimension whereas
 *              otherwise they are stored interleaved with existing values in the `batchAxis`
 *              dimension.
 *              Note: This operation is the inverse of `batchToSpace`.
 *              Note: This operation is a generalization of `depthToSpace2D`.
 *
 *  @param      tensor                                      The input tensor.
 *  @param      spatialAxes                           Axes that define the dimensions containing the spatial blocks.
 *  @param      batchAxis                               Axis that defines the destination dimension, where to copy the blocks.
 *  @param      blockDimensions                  Defines the size of the rectangular spatial sub-block.
 *  @param      usePixelShuffleOrder       Controls layout of the sub-blocks within the batch dimension.
 *  @param      name                                           The name for the operation.
 *
 *  @return     A valid MPSGraphTensor object.
 */
-(MPSGraphTensor *)spaceToBatchTensor:(MPSGraphTensor *) tensor
                          spatialAxes:(NSArray<NSNumber *> *) spatialAxes
                            batchAxis:(NSInteger) batchAxis
                      blockDimensions:(NSArray<NSNumber *> *) blockDimensions
                 usePixelShuffleOrder:(BOOL)usePixelShuffleOrder
                                 name:(NSString * _Nullable) name
MPS_AVAILABLE_STARTING(macos(13.0), ios(16.1), tvos(16.1))
MPS_SWIFT_NAME( spaceToBatch(_:spatialAxes:batchAxis:blockDimensions:usePixelShuffleOrder:name:));

-(MPSGraphTensor *)spaceToBatchTensor:(MPSGraphTensor *) tensor
                    spatialAxesTensor:(MPSGraphTensor *) spatialAxesTensor
                      batchAxisTensor:(MPSGraphTensor *) batchAxisTensor
                blockDimensionsTensor:(MPSGraphTensor *) blockDimensionsTensor
                 usePixelShuffleOrder:(BOOL)usePixelShuffleOrder
                                 name:(NSString * _Nullable) name
MPS_AVAILABLE_STARTING(macos(13.0), ios(16.1), tvos(16.1))
MPS_SWIFT_NAME( spaceToBatch(_:spatialAxesTensor:batchAxisTensor:blockDimensionsTensor:usePixelShuffleOrder:name:));

/*!
 *  @abstract   Create a batch-to-space3d op and return the result tensor.
 *  @discussion This operation outputs a copy of the input tensor, where values from the
 *              `batchAxis` dimension are moved in spatial blocks of size `blockDimensions` to the
 *              `spatialAxes` dimensions (for `usePixelShuffleOrder=YES`1,2 or 3 axes supported,
 *              otherwise limited only by MPSNDArray rank limitations). `usePixelShuffleOrder`
 *              can be used to control how the data within spatial blocks is ordered in the
 *              `batchAxis` dimension: with `usePixelShuffleOrder = YES` the values within the
 *              spatial block are stored contiguosly within the `batchAxis` dimension whereas
 *              without it they are stored interleaved with existing values in the `batchAxis`
 *              dimension.
 *              Note: This operation is the inverse of `spaceToBatch`.
 *              Note: This operation is a generalization of `depthToSpace2D`.
 *
 *  @param      tensor                                      The input tensor.
 *  @param      spatialAxes                           Axes that define the dimensions containing the spatial blocks.
 *  @param      batchAxis                               Axis that defines the source dimension, from which to copy the blocks.
 *  @param      blockDimensions                  Defines the size of the rectangular spatial sub-block.
 *  @param      usePixelShuffleOrder       Controls layout of the sub-blocks within the batch dimension.
 *  @param      name                                           The name for the operation.
 *
 *  @return     A valid MPSGraphTensor object.
 */
-(MPSGraphTensor *)batchToSpaceTensor:(MPSGraphTensor *) tensor
                          spatialAxes:(NSArray<NSNumber *> *) spatialAxes
                            batchAxis:(NSInteger) batchAxis
                      blockDimensions:(NSArray<NSNumber *> *) blockDimensions
                 usePixelShuffleOrder:(BOOL)usePixelShuffleOrder
                                 name:(NSString * _Nullable) name
MPS_AVAILABLE_STARTING(macos(13.0), ios(16.1), tvos(16.1))
MPS_SWIFT_NAME( batchToSpace(_:spatialAxes:batchAxis:blockDimensions:usePixelShuffleOrder:name:));

-(MPSGraphTensor *)batchToSpaceTensor:(MPSGraphTensor *) tensor
                    spatialAxesTensor:(MPSGraphTensor *) spatialAxesTensor
                      batchAxisTensor:(MPSGraphTensor *) batchAxisTensor
                blockDimensionsTensor:(MPSGraphTensor *) blockDimensionsTensor
                 usePixelShuffleOrder:(BOOL)usePixelShuffleOrder
                                 name:(NSString * _Nullable) name
MPS_AVAILABLE_STARTING(macos(13.0), ios(16.1), tvos(16.1))
MPS_SWIFT_NAME( batchToSpace(_:spatialAxesTensor:batchAxisTensor:blockDimensionsTensor:usePixelShuffleOrder:name:));

/*!
 *  @abstract   Create reverse op and return the result tensor
 *  @discussion Reverses a tensor on given axes
 *              https://www.tensorflow.org/api_docs/python/tf/reverse.
 *
 *  @param      tensor              Tensor to be reversed
 *  @param      axesTensor     Tensor that specifies axes to be reversed (Axes must be unique and within normal axis range).
 *  @param      name                  The name for the operation
 *
 *  @return     A valid MPSGraphTensor object
 */

-(MPSGraphTensor *) reverseTensor:(MPSGraphTensor *) tensor
                       axesTensor:(MPSGraphTensor *) axesTensor
                             name:(NSString * _Nullable) name
MPS_AVAILABLE_STARTING(macos(12.0), ios(15.0), tvos(15.0));

/*!
 *  @abstract   Create reverse op and return the result tensor
 *  @discussion Reverses a tensor on given axes
 *              https://www.tensorflow.org/api_docs/python/tf/reverse.
 *
 *  @param      tensor              Tensor to be reversed
 *  @param      axes                  Axes to be reversed (Axes must be unique and within normal axis range).
 *  @param      name                  The name for the operation
 *
 *  @return     A valid MPSGraphTensor object
 */

-(MPSGraphTensor *) reverseTensor:(MPSGraphTensor *) tensor
                             axes:(NSArray<NSNumber *> *) axes
                             name:(NSString * _Nullable) name
MPS_AVAILABLE_STARTING(macos(12.0), ios(15.0), tvos(15.0));

/*!
 *  @abstract   Create reverse op and return the result tensor
 *  @discussion Reverses a tensor on all axes
 *              https://www.tensorflow.org/api_docs/python/tf/reverse.
 *
 *  @param      tensor              Tensor to be reversed
 *  @param      name                  The name for the operation
 *
 *  @return     A valid MPSGraphTensor object
 */

-(MPSGraphTensor *) reverseTensor:(MPSGraphTensor *) tensor
                             name:(NSString * _Nullable) name
MPS_AVAILABLE_STARTING(macos(12.0), ios(15.0), tvos(15.0));


/*!
 *  @abstract   Create flatten2d op and return the result tensor
 *  @discussion Flattens dimensions before `axis` to `result[0]` and dimensions starting
 *              from `axis` to `result[1]` and returns a rank-2 tensor as result.
 *
 *  @param      tensor          Tensor to be flattened
 *  @param      axis            Axis around which to flatten
 *  @param      name            The name for the operation
 *
 *  @return     A valid MPSGraphTensor object
 */

-(MPSGraphTensor *) flatten2DTensor:(MPSGraphTensor *) tensor
                               axis:(NSInteger) axis
                               name:(NSString * _Nullable) name
MPS_SWIFT_NAME( flatten2D(_:axis:name:) )
MPS_AVAILABLE_STARTING(macos(12.0), ios(15.0), tvos(15.0));

/*!
 *  @abstract   Create flatten2d op and return the result tensor
 *  @discussion Flattens dimensions before `axis` to `result[0]` and dimensions starting
 *              from `axis` to `result[1]` and returns a rank-2 tensor as result.
 *
 *  @param      tensor              Tensor to be flattened
 *  @param      axisTensor          Axis around which to flatten
 *  @param      name                The name for the operation
 *
 *  @return     A valid MPSGraphTensor object
 */

-(MPSGraphTensor *) flatten2DTensor:(MPSGraphTensor *) tensor
                         axisTensor:(MPSGraphTensor *) axisTensor
                               name:(NSString * _Nullable) name
MPS_SWIFT_NAME( flatten2D(_:axisTensor:name:) )
MPS_AVAILABLE_STARTING(macos(12.0), ios(15.0), tvos(15.0));

/*!
 *  @abstract   Create broadcast op and return the result tensor
 *  @discussion Broadcast values inside the tensor, starting from the trailing dimensions, to give it the correct shape.
 *              This is equivalent to the broadcasting for arithmetic operations when operands have different shapes.
 *
 *  @param      tensor        Tensor to be broadcasted
 *  @param      shape          Shape of the result tensor
 *  @param      name            The name for the operation
 *
 *  @return     A valid MPSGraphTensor object
 */

-(MPSGraphTensor *) broadcastTensor:(MPSGraphTensor *) tensor
                            toShape:(MPSShape *) shape
                               name:(NSString * _Nullable) name
MPS_SWIFT_NAME( broadcast(_:shape:name:) )
MPS_AVAILABLE_STARTING(macos(12.0), ios(15.0), tvos(15.0));

/*!
 *  @abstract   Create broadcast op and return the result tensor
 *  @discussion Broadcast values inside the tensor, starting from the trailing dimensions, to give it the correct shape.
 *              This is equivalent to the broadcasting for arithmetic operations when operands have different shapes.
 *
 *  @param      tensor                Tensor to be broadcasted
 *  @param      shapeTensor     1D Int32 or Int64 tensor. Shape of the result tensor
 *  @param      name                     The name for the operation
 *
 *  @return     A valid MPSGraphTensor object
 */

-(MPSGraphTensor *) broadcastTensor:(MPSGraphTensor *) tensor
                      toShapeTensor:(MPSGraphTensor *) shapeTensor
                               name:(NSString * _Nullable) name
MPS_SWIFT_NAME( broadcast(_:shapeTensor:name:) )
MPS_AVAILABLE_STARTING(macos(12.0), ios(15.0), tvos(15.0));

/*!
 *  @abstract   Create shapeof op and return the result tensor
 *  @discussion Returns a 1D Int32 tensor with value the static shape of the input tensor
 *
 *  @param      tensor        Input tensor
 *  @param      name            The name for the operation
 *
 *  @return     A valid MPSGraphTensor object
 */

-(MPSGraphTensor *) shapeOfTensor:(MPSGraphTensor *) tensor
                             name:(NSString * _Nullable) name
MPS_SWIFT_NAME( shapeOf(_:name:) )
MPS_AVAILABLE_STARTING(macos(12.0), ios(15.0), tvos(15.0));

/*!
 *  @abstract   Create cast op and return the result tensor
 *  @discussion Returns input tensor casted to the dataType passed in
 *
 *  @param      tensor        Input tensor
 *  @param      type        Input tensor
 *  @param      name            The name for the operation
 *
 *  @return     A valid MPSGraphTensor object
 */
-(MPSGraphTensor *)castTensor:(MPSGraphTensor *)tensor
                       toType:(MPSDataType)type
                         name:(NSString * _Nullable)name
MPS_AVAILABLE_STARTING(macos(12.0), ios(15.0), tvos(15.0));

/*!
 *  @abstract   Create stack op and return the result
 *  @discussion Stacks all input tensors along `axis` into a result tensor of rank + 1. Tensors must be broadcast
 *              compatible along all dimensions, and have the same type.
 *
 *  @param      inputTensors        Input tensors
 *  @param      axis            The dimension to stack tensors into result. Must be in range - rank + 1 <= dimension < rank + 1
 *  @param      name            The name for the operation
 *
 *  @return     A valid MPSGraphTensor object
 */
-(MPSGraphTensor *) stackTensors:(NSArray<MPSGraphTensor *> *) inputTensors
                            axis:(NSInteger) axis
                            name:(NSString * _Nullable) name
MPS_SWIFT_NAME( stack(_:axis:name:) )
MPS_AVAILABLE_STARTING(macos(12.3), ios(15.4), tvos(15.4));

/*!
 *  @abstract   Create split op and return the result
 *  @discussion Splits the input tensor along `axis` into multiple result tensors of size determined by `splitSizes`.
 *              Requires that the sum of `splitSizes` is equal to the lenth of the input along `axis`.
 *
 *  @param      tensor        Input tensor
 *  @param      splitSizes        The length of the result tensors along the split axis
 *  @param      axis        The dimension to split the input along
 *  @param      name            The name for the operation
 *
 *  @return     A valid MPSGraphTensor object
 */
-(NSArray<MPSGraphTensor *> *) splitTensor:(MPSGraphTensor *) tensor
                                splitSizes:(NSArray<NSNumber *> *) splitSizes
                                      axis:(NSInteger) axis
                                      name:(NSString * _Nullable) name
MPS_SWIFT_NAME( split(_:splitSizes:axis:name:) )
MPS_AVAILABLE_STARTING(macos(12.3), ios(15.4), tvos(15.4));

/*!
 *  @abstract   Create split op and return the result
 *  @discussion Splits the input tensor along `axis` into multiple result tensors of size determined by `splitSizes`.
 *              Requires that the sum of `splitSizesTensor` is equal to the lenth of the input along `axis`.
 *
 *  @param      tensor        Input tensor
 *  @param      splitSizesTensor        The length of the result tensors along the split axis
 *  @param      axis        The dimension to split the input along
 *  @param      name            The name for the operation
 *
 *  @return     A valid MPSGraphTensor object
 */
-(NSArray<MPSGraphTensor *> *) splitTensor:(MPSGraphTensor *) tensor
                          splitSizesTensor:(MPSGraphTensor *) splitSizesTensor
                                      axis:(NSInteger) axis
                                      name:(NSString * _Nullable) name
MPS_SWIFT_NAME( split(_:splitSizesTensor:axis:name:) )
MPS_AVAILABLE_STARTING(macos(12.3), ios(15.4), tvos(15.4));

/*!
 *  @abstract   Create split op and return the result
 *  @discussion Splits the input tensor along `axis` into `numsplits` result tensors of equal size.
 *              Requires that the lenth of the input along `axis` is divisible by `num_splits`.
 *
 *  @param      tensor        Input tensor
 *  @param      numSplits        The number of result tensors to split to
 *  @param      axis        The dimension to split the input along
 *  @param      name            The name for the operation
 *
 *  @return     A valid MPSGraphTensor object
 */
-(NSArray<MPSGraphTensor *> *) splitTensor:(MPSGraphTensor *) tensor
                                 numSplits:(NSUInteger) numSplits
                                      axis:(NSInteger) axis
                                      name:(NSString * _Nullable) name
MPS_SWIFT_NAME( split(_:numSplits:axis:name:) )
MPS_AVAILABLE_STARTING(macos(12.3), ios(15.4), tvos(15.4));

/*!
 *  @abstract   Create squeeze op and return the result
 *  @discussion Squeezes the tensor, removing any dimensions with size 1.
 *
 *  @param      tensor        Input tensor
 *  @param      name            The name for the operation
 *
 *  @return     A valid MPSGraphTensor object
 */
-(MPSGraphTensor *) squeezeTensor:(MPSGraphTensor *) tensor
                             name:(NSString * _Nullable) name
MPS_SWIFT_NAME( squeeze(_:name:) )
MPS_AVAILABLE_STARTING(macos(12.3), ios(15.4), tvos(15.4));

/*!
 *  @abstract   Create squeeze op and return the result
 *  @discussion Squeezes the tensor, removing a dimension with size 1 at specified axis.
 *              Size must be 1 at specified axis.
 *
 *  @param      tensor        Input tensor
 *  @param      axis            The axis to squeeze
 *  @param      name            The name for the operation
 *
 *  @return     A valid MPSGraphTensor object
 */
-(MPSGraphTensor *) squeezeTensor:(MPSGraphTensor *) tensor
                             axis:(NSInteger) axis
                             name:(NSString * _Nullable) name
MPS_SWIFT_NAME( squeeze(_:axis:name:) )
MPS_AVAILABLE_STARTING(macos(12.3), ios(15.4), tvos(15.4));

/*!
 *  @abstract   Create squeeze op and return the result
 *  @discussion Squeezes the tensor, removing dimensions with size 1 at specified axes.
 *              Size must be 1 at all specified axes.
 *
 *  @param      tensor        Input tensor
 *  @param      axes            The axes to squeeze
 *  @param      name            The name for the operation
 *
 *  @return     A valid MPSGraphTensor object
 */
-(MPSGraphTensor *) squeezeTensor:(MPSGraphTensor *) tensor
                             axes:(NSArray<NSNumber *> *) axes
                             name:(NSString * _Nullable) name
MPS_SWIFT_NAME( squeeze(_:axes:name:) )
MPS_AVAILABLE_STARTING(macos(12.3), ios(15.4), tvos(15.4));

-(MPSGraphTensor *) squeezeTensor:(MPSGraphTensor *) tensor
                       axesTensor:(MPSGraphTensor *) axesTensor
                             name:(NSString * _Nullable) name
MPS_SWIFT_NAME( squeeze(_:axesTensor:name:) )
MPS_AVAILABLE_STARTING(macos(12.3), ios(15.4), tvos(15.4));

/*!
 *  @abstract   Create expand_dims op and return the result
 *  @discussion Expands the tensor, inserting a dimension with size 1 at specified axis.
 *
 *  @param      tensor        Input tensor
 *  @param      axis            The axis to expand
 *  @param      name            The name for the operation
 *
 *  @return     A valid MPSGraphTensor object
 */
-(MPSGraphTensor *) expandDimsOfTensor:(MPSGraphTensor *) tensor
                                  axis:(NSInteger) axis
                                  name:(NSString * _Nullable) name
MPS_SWIFT_NAME( expandDims(_:axis:name:) )
MPS_AVAILABLE_STARTING(macos(12.3), ios(15.4), tvos(15.4));

/*!
 *  @abstract   Create expand_dims op and return the result
 *  @discussion Expands the tensor, inserting dimensions with size 1 at specified axes.
 *
 *  @param      tensor        Input tensor
 *  @param      axes            The axes to expand
 *  @param      name            The name for the operation
 *
 *  @return     A valid MPSGraphTensor object
 */
-(MPSGraphTensor *) expandDimsOfTensor:(MPSGraphTensor *) tensor
                                  axes:(NSArray<NSNumber *> *) axes
                                  name:(NSString * _Nullable) name
MPS_SWIFT_NAME( expandDims(_:axes:name:) )
MPS_AVAILABLE_STARTING(macos(12.3), ios(15.4), tvos(15.4));

-(MPSGraphTensor *) expandDimsOfTensor:(MPSGraphTensor *) tensor
                            axesTensor:(MPSGraphTensor *) axesTensor
                                  name:(NSString * _Nullable) name
MPS_SWIFT_NAME( expandDims(_:axesTensor:name:) )
MPS_AVAILABLE_STARTING(macos(12.3), ios(15.4), tvos(15.4));

/*!
 *  @abstract   Create get coord op and return the result
 *  @discussion Creates a tensor of specified shape with value at index @code [i_0, i_1, ... , i_N] = i_axis @endcode
 *              For example,
 *              @code
 *              coordinateAlongAxis(0, withShape=[5]) = [0, 1, 2, 3, 4]
 *              coordinateAlongAxis(1, withShape=[3,2]) = [[0, 0],
 *                                                         [1, 1],
 *                                                         [2, 2]]
 *              @endcode
 *
 *  @param      axis            The coordinate axis an element's value is set to. Negative values wrap around
 *  @param      shape           The shape of the result tensor
 *  @param      name            The name for the operation
 *
 *  @return     A valid MPSGraphTensor object
 */
-(MPSGraphTensor *) coordinateAlongAxis:(NSInteger) axis
                              withShape:(MPSShape *) shape
                                   name:(NSString * _Nullable) name
MPS_AVAILABLE_STARTING(macos(12.3), ios(15.4), tvos(15.4));

/*!
 *  @abstract   Create get coord op and return the result
 *  @discussion See above discussion of getCoordinateValueWithShape: axis: name:
 *
 *  @param      axisTensor            Scalar Int32 tensor. The coordinate axis an element's value is set to.  Negative values wrap around
 *  @param      shape           The shape of the result tensor
 *  @param      name            The name for the operation
 *
 *  @return     A valid MPSGraphTensor object
 */
-(MPSGraphTensor *) coordinateAlongAxisTensor:(MPSGraphTensor *) axisTensor
                                    withShape:(MPSShape *) shape
                                         name:(NSString * _Nullable) name
MPS_AVAILABLE_STARTING(macos(12.3), ios(15.4), tvos(15.4));

/*!
 *  @abstract   Create get coord op and return the result
 *  @discussion See above discussion of getCoordinateValueWithShape: axis: name:
 *
 *  @param      axis            The coordinate axis an element's value is set to.  Negative values wrap around
 *  @param      shapeTensor           1D Int32 or Int64 tensor. The shape of the result tensor.
 *  @param      name            The name for the operation
 *
 *  @return     A valid MPSGraphTensor object
 */
-(MPSGraphTensor *) coordinateAlongAxis:(NSInteger) axis
                        withShapeTensor:(MPSGraphTensor *) shapeTensor
                                   name:(NSString * _Nullable) name
MPS_AVAILABLE_STARTING(macos(12.3), ios(15.4), tvos(15.4));

/*!
 *  @abstract   Create get coord op and return the result
 *  @discussion See above discussion of getCoordinateValueWithShape: axis: name:
 *
 *  @param      axisTensor            Scalar Int32 tensor. The coordinate axis an element's value is set to.  Negative values wrap around
 *  @param      shapeTensor           1D Int32 or Int64 tensor. The shape of the result tensor.
 *  @param      name            The name for the operation
 *
 *  @return     A valid MPSGraphTensor object
 */
-(MPSGraphTensor *) coordinateAlongAxisTensor:(MPSGraphTensor *) axisTensor
                              withShapeTensor:(MPSGraphTensor *) shapeTensor
                                         name:(NSString * _Nullable) name
MPS_AVAILABLE_STARTING(macos(12.3), ios(15.4), tvos(15.4));

@end

NS_ASSUME_NONNULL_END

#endif /* MPSGraphTensorShapeOps_h */
