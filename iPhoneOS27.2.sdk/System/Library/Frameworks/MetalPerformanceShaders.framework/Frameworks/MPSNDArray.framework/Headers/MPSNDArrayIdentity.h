//
//  MPSNDArrayIdentity.h
//  MPS
//
//  Created by Dhruv Saksena on 8/3/19.
//  Copyright © 2019 Apple. All rights reserved.
//

#ifndef MPSNDArrayIdentity_h
#define MPSNDArrayIdentity_h

#import <MPSNDArray/MPSNDArrayKernel.h>

#pragma mark - Base class Identity Kernels

/*!
 *  @class      MPSNDArrayIdentityKernel
 *
 *  @dependency This depends on Metal.framework.
 *  @abstract   An efficient kernel to handle copies, transposed-copies and reshapes.
 *
 *
 */
MPS_CLASS_AVAILABLE_STARTING( macos(15.0), ios(18.0), macCatalyst(18.0), tvos(18.0), visionos(2.0) )
@interface MPSNDArrayIdentity : MPSNDArrayUnaryKernel

-(nonnull instancetype) initWithDevice: (nonnull id <MTLDevice>) device NS_DESIGNATED_INITIALIZER;

/*! @abstract   Do a reshape operation, either by trying to alias the array, returning an arrayview, or by copying.
 *  @param      cmdBuf              `MTLCommandBuffer` into which to encode the kernel, or to create a temporary array alias.
 *  @param      sourceArray         Source array. If this function returns a non-nil result, then the readCount of `sourceArray` is decremented.
 *  @param      shape               The new shape, given in TF dimension ordering (as always with MPSShape).
 *  @param      destinationArray    If not nil, then the result of reshape will be copied to this. Shape of `destinationArray` must match `shape`.
 *  @result     If `destinationArray` is not nil, then `destinationArray`. Otherwise aliasing is tried, and if aliasing is not possible
 *              due to existing slices or transposes nil is returned. If aliasing is successful, then a new arrayview of `sourceArray`
 *              is returned; If `sourceArray` is a `MPSTemporaryArray` then a `MPSTemporaryArray` is returned referencing the same data,
 *              otherwise a `MPSNDArray` type result is returned.
 *   */
-(MPSNDArray * __nullable) reshapeWithCommandBuffer: (__nullable id <MTLCommandBuffer>) cmdBuf
                                        sourceArray: (MPSNDArray * __nonnull) sourceArray
                                              shape: (MPSShape * __nonnull) shape
                                   destinationArray: (MPSNDArray * __nullable) destinationArray;

/*! @abstract   Do a reshape operation, either by trying to alias the array, returning an arrayview, or by copying.
 *  @param      cmdBuf              `MTLCommandBuffer` into which to encode the kernel, or to create a temporary array alias.
 *  @param      sourceArray         Source array. If this function returns a non-nil result, then the readCount of `sourceArray` is decremented.
 *  @param      numberOfDimensions  The number of dimensions of the NDArray.
 *  @param      dimensionSizes      The extents of each dimensions of the NDArray.
 *  @param      destinationArray    If not nil, then the result of reshape will be copied to this. Shape of `destinationArray` must match `shape`.
 *  @result     If `destinationArray` is not nil, then `destinationArray`. Otherwise aliasing is tried, and if aliasing is not possible
 *              due to existing slices or transposes nil is returned. If aliasing is successful, then a new arrayview of `sourceArray`
 *              is returned; If `sourceArray` is a `MPSTemporaryArray` then a `MPSTemporaryArray` is returned referencing the same data,
 *              otherwise a `MPSNDArray` type result is returned.
 *   */
-(MPSNDArray * __nullable) reshapeWithCommandBuffer: (__nullable id <MTLCommandBuffer>) cmdBuf
                                        sourceArray: (MPSNDArray * __nonnull) sourceArray
                                     dimensionCount: (NSUInteger) numberOfDimensions
                                     dimensionSizes: (NSUInteger*__nonnull) dimensionSizes
                                   destinationArray: (MPSNDArray * __nullable) destinationArray;

/*! @abstract   Do a reshape operation, either by trying to alias the array, returning an arrayview, or by copying.
 *  @param      encoder             The `MTLComputeCommandEncoder` that the kernel will be encoded with.
 *  @param      cmdBuf              `MTLCommandBuffer` into which to encode the kernel, or to create a temporary array alias.
 *  @param      sourceArray         Source array. If this function returns a non-nil result, then the readCount of `sourceArray` is decremented.
 *  @param      shape               The new shape, given in TF dimension ordering (as always with MPSShape).
 *  @param      destinationArray    If not nil, then the result of reshape will be copied to this. Shape of `destinationArray` must match `shape`.
 *  @result     If `destinationArray` is not nil, then `destinationArray`. Otherwise aliasing is tried, and if aliasing is not possible
 *              due to existing slices or transposes nil is returned. If aliasing is successful, then a new arrayview of `sourceArray`
 *              is returned; If `sourceArray` is a `MPSTemporaryArray` then a `MPSTemporaryArray` is returned referencing the same data,
 *              otherwise a `MPSNDArray` type result is returned.
 *   */
-(MPSNDArray * __nullable) reshapeWithCommandEncoder: (__nullable id <MTLComputeCommandEncoder>) encoder
                                       commandBuffer: (__nullable id <MTLCommandBuffer>) cmdBuf
                                        sourceArray: (MPSNDArray * __nonnull) sourceArray
                                              shape: (MPSShape * __nonnull) shape
                                   destinationArray: (MPSNDArray * __nullable) destinationArray;

/*! @abstract   Do a reshape operation, either by trying to alias the array, returning an arrayview, or by copying.
 *  @param      encoder             The `MTLComputeCommandEncoder` that the kernel will be encoded with.
 *  @param      cmdBuf              `MTLCommandBuffer` into which to encode the kernel, or to create a temporary array alias.
 *  @param      sourceArray         Source array. If this function returns a non-nil result, then the readCount of `sourceArray` is decremented.
 *  @param      numberOfDimensions  The number of dimensions of the NDArray.
 *  @param      dimensionSizes      The extents of each dimensions of the NDArray.
 *  @param      destinationArray    If not nil, then the result of reshape will be copied to this. Shape of `destinationArray` must match `shape`.
 *  @result     If `destinationArray` is not nil, then `destinationArray`. Otherwise aliasing is tried, and if aliasing is not possible
 *              due to existing slices or transposes nil is returned. If aliasing is successful, then a new arrayview of `sourceArray`
 *              is returned; If `sourceArray` is a `MPSTemporaryArray` then a `MPSTemporaryArray` is returned referencing the same data,
 *              otherwise a `MPSNDArray` type result is returned.
 *   */
-(MPSNDArray * __nullable) reshapeWithCommandEncoder: (__nullable id <MTLComputeCommandEncoder>) encoder
                                       commandBuffer: (__nullable id <MTLCommandBuffer>) cmdBuf
                                        sourceArray: (MPSNDArray * __nonnull) sourceArray
                                     dimensionCount: (NSUInteger) numberOfDimensions
                                     dimensionSizes: (NSUInteger*__nonnull) dimensionSizes
                                   destinationArray: (MPSNDArray * __nullable) destinationArray;

/*! @abstract   Do a reshape operation on the CPU.
 *  @param      sourceArray         The source NDArray.
 *  @param      shape               The new shape in Tensorflow dimension order.
 *  @result     A new array view of `sourceArray` is returned. Or `nil` If aliasing is not possible.
 *   */
-(nullable MPSNDArray *) reshapeWithSourceArray: (nonnull MPSNDArray *) sourceArray
                                          shape: (nonnull MPSShape *) shape
MPS_AVAILABLE_STARTING(macos(27.0), ios(27.0), tvos(27.0));

#if !TARGET_IPHONE_SIMULATOR

/*! @abstract   Encode a reshape operation.
 *              The encoder associates the commands with MTLStageDispatch. Synchronize your
 *              workloads against this stage when using this function to prevent race conditions.
 *  @param      encoder          The MTL4ComputeCommandEncoder to encode the kernel with.
 *  @param      sourceArray      The source NDArray.
 *  @param      shape            The new shape in Tensorflow dimension order.
 *  @param      destinationArray The destination NDArray. The shape of `destinationArray` must match `shape`.
 *   */
-(void) reshapeWithMTL4CommandEncoder: (nonnull id <MTL4ComputeCommandEncoder>) encoder
                          sourceArray: (nonnull MPSNDArray *) sourceArray
                                shape: (nonnull MPSShape *) shape
                     destinationArray: (nonnull MPSNDArray *) destinationArray
MPS_AVAILABLE_STARTING(macos(27.0), ios(27.0), tvos(27.0));

/*! @abstract   Encode a reshape operation.
 *              The encoder associates the commands with MTLStageDispatch. Synchronize your
 *              workloads against this stage when using this function to prevent race conditions.
 *  @param      encoder            The MTL4ComputeCommandEncoder to encode the kernel with.
 *  @param      sourceArray        The source NDArray.
 *  @param      numberOfDimensions The NDArray's dimension count.
 *  @param      dimensionSizes     The extents of each dimension of the NDArray.
 *  @param      destinationArray   The destination NDArray. The shape of `destinationArray` must match `numberOfDimensions`
                                   and `dimensionSizes`.
 *   */
-(void) reshapeWithMTL4CommandEncoder: (nonnull id <MTL4ComputeCommandEncoder>) encoder
                          sourceArray: (nonnull MPSNDArray *) sourceArray
                       dimensionCount: (NSUInteger) numberOfDimensions
                       dimensionSizes: (nonnull NSUInteger *) dimensionSizes
                     destinationArray: (nonnull MPSNDArray *) destinationArray
MPS_AVAILABLE_STARTING(macos(27.0), ios(27.0), tvos(27.0));

#endif

@end    // MPSNDArrayIdentity

#endif /* MPSNDArrayIdentity_h */
