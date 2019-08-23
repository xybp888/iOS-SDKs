/*!
 *  @header MPSMatrixMultiplication.h
 *  @framework MetalPerformanceShaders.framework
 *
 *  @copyright Copyright (c) 2016 Apple Inc. All rights reserved.
 *  @abstract MetalPerformanceShaders filter base classes
 */
#ifndef MPSMatrixMultiplication_h
#define MPSMatrixMultiplication_h

#import <MetalPerformanceShaders/MPSKernel.h>
#import <MetalPerformanceShaders/MPSMatrix.h>

/*!
 *  @class      MPSMatrixMultiplication
 *
 *  @dependency This depends on Metal.framework.
 *
 *  @abstract   A matrix multiplication kernel.
 *
 *  @discussion A MPSMatrixMultiplication object computes:
 *
 *                  C = alpha * op(A) * op(B) + beta * C
 *
 *              A, B, and C are matrices which are represented by MPSMatrix
 *              objects. alpha and beta are scalar values (of the same data type
 *              as values of C) which are applied as shown above.  A and B may
 *              each have an optional transposition operation applied.
 *
 *              A, B, and C (also referred to in later discussions as the left input
 *              matrix, the right input matrix, and the result matrix respectively).
 *
 *              A MPSMatrixMultiplication object is initialized with the transpose
 *              operators to apply to A and B, sizes for the operation to perform,
 *              and the scalar values alpha and beta.
 *
 */
MPS_CLASS_AVAILABLE_STARTING( __MAC_10_12, __IPHONE_10_0, __TVOS_10_0)
@interface MPSMatrixMultiplication : MPSKernel
/*! @property   resultMatrixOrigin
 *
 *  @discussion The origin, relative to [0, 0] in the result matrix, at which to
 *              start writing (and reading if necessary) results.  This property is
 *              modifiable and defaults to [0, 0] at initialization time.  If a
 *              different origin is desired then this should be modified prior to
 *              encoding the kernel.  The z value must be 0.
 */
@property (readwrite, nonatomic) MTLOrigin resultMatrixOrigin;

/*! @property   leftMatrixOrigin
 *
 *  @discussion The origin, relative to [0, 0] in the left input matrix, at which to
 *              start reading values.  This property is modifiable and defaults to
 *              [0, 0] at initialization time.  If a different origin is desired then
 *              this should be modified prior to encoding the kernel.  The z value
 *              must be 0.
 */
@property (readwrite, nonatomic) MTLOrigin leftMatrixOrigin;

/*! @property   rightMatrixOrigin
 *
 *  @discussion The origin, relative to [0, 0] in the right input matrix, at which to
 *              start reading values.  This property is modifiable and defaults to
 *              [0, 0] at initialization time.  If a different origin is desired then
 *              this should be modified prior to encoding the kernel.  The z value
 *              must be 0.
 */
@property (readwrite, nonatomic) MTLOrigin rightMatrixOrigin;

/*!
 *  @abstract   Initialize an MPSMatrixMultiplication object on a device for a given size
 *              and desired transpose and scale values.
 *
 *  @param      device          The device on which the kernel will execute.
 *
 *  @param      transposeLeft   A boolean value which indicates if the left input matrix should be
 *                              used in transposed form.  If 'YES' then op(A) = A**T, otherwise
 *                              op(A) = A.
 *
 *  @param      transposeRight  A boolean value which indicates if the right input matrix should be
 *                              used in transposed form.  If 'YES' then op(B) = B**T, otherwise
 *                              op(B) = B.
 *
 *  @param      resultRows      The number of rows in the result matrix, M in BLAS GEMM description.
 *
 *  @param      resultColumns   The number of columns in the result matrix, N in BLAS GEMM description.
 *
 *  @param      interiorColumns The number of columns of the left input matrix after the
 *                              appropriate transpose operation has been applied. K in BLAS
 *                              GEMM description.
 *
 *  @param      alpha           The scale factor to apply to the product.  Specified in double
 *                              precision.  Will be converted to the appropriate precision in the
 *                              implementation subject to rounding and/or clamping as necessary.
 *
 *  @param      beta            The scale factor to apply to the initial values of C.  Specified
 *                              in double precision.  Will be converted to the appropriate precision in the
 *                              implementation subject to rounding and/or clamping as necessary.
 *
 *  @return     A valid MPSMatrixMultiplication object or nil, if failure.
 */
-(nonnull instancetype) initWithDevice: (nonnull id<MTLDevice>) device
                         transposeLeft: (BOOL) transposeLeft
                        transposeRight: (BOOL) transposeRight
                            resultRows: (NSUInteger) resultRows
                         resultColumns: (NSUInteger) resultColumns
                       interiorColumns: (NSUInteger) interiorColumns
                                 alpha: (double) alpha
                                  beta: (double) beta;

/*!
 @discussion Use the above initialization method instead.
 */
-(nonnull instancetype) initWithDevice: (nonnull id <MTLDevice>) device NS_UNAVAILABLE;

/*!
 *  @abstract   Encode a MPSMatrixMultiplication object to a command buffer.
 *
 *  @param      commandBuffer   A valid MTLCommandBuffer to receive the encoded kernel.
 *
 *  @param      leftMatrix      A valid MPSMatrix object which specifies the left input matrix.
 *
 *  @param      rightMatrix     A valid MPSMatrix object which specifies the right input matrix.
 *
 *  @param      resultMatrix    A valid MPSMatrix object which specifies the addend matrix which will
 *                              also be overwritten by the result.
 *
 *  @discussion Certain constraints apply to the sizes of the matrices depending on the transposition
 *              operations and sizes requested at initialization time as well as the origins at the time
 *              this routine is called:
 *
 *              The left input matrix must be large enough to hold an array of size resultRows x interiorColumns
 *              elements beginning at leftMatrixOrigin.
 *
 *              The right input matrix must be large enough to hold an array of size interiorColumns x resultColumns
 *              elements beginning at rightMatrixOrigin.
 *
 *              The result matrix must be large enough to hold an array of size resultRows x resultColumns
 *              elements beginning at resultMatrixOrigin.
 */
-(void) encodeToCommandBuffer: (nonnull id <MTLCommandBuffer>) commandBuffer
                   leftMatrix: (MPSMatrix const* __nonnull) leftMatrix
                  rightMatrix: (MPSMatrix const* __nonnull) rightMatrix
                 resultMatrix: (MPSMatrix* __nonnull) resultMatrix
                    MPS_SWIFT_NAME(encode(commandBuffer:leftMatrix:rightMatrix:resultMatrix:));



@end // MPSMatrixMultiplication


#endif /* MPSMatrixMultiplication_h */
