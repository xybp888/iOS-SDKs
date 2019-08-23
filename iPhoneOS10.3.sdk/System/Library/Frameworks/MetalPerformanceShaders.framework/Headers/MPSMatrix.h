#ifndef MPSMatrix_h
#define MPSMatrix_h

#include <MetalPerformanceShaders/MPSTypes.h>

#ifdef __cplusplus
extern "C" {
#endif

/*!
 *  @class      MPSMatrixDescriptor
 *
 *  @dependency This depends on Metal.framework
 *
 *  @discussion A MPSMatrixDescriptor describes the sizes, strides, and data type of a
 *              2-dimensional array of data.  All storage is assumed to be in row-major
 *              order.
 */
MPS_CLASS_AVAILABLE_STARTING( __MAC_10_12, __IPHONE_10_0, __TVOS_10_0)
@interface MPSMatrixDescriptor: NSObject

/*! @property   rows
 *  @discussion The number of rows in the matrix.
 */
@property (readwrite, nonatomic) NSUInteger rows;

/*! @property   columns
 *  @discussion The number of columns in the matrix.
 */
@property (readwrite, nonatomic) NSUInteger columns;

/*! @property   dataType
 *  @discussion The type of the data which makes up the values of the matrix.
 */
@property (readwrite, nonatomic) MPSDataType dataType;

/*! @property   rowBytes
 *  @discussion The stride, in bytes, between corresponding elements of
 *              consecutive rows.  Must be a multiple of the element size.
 */
@property (readwrite, nonatomic) NSUInteger rowBytes;

/*!
 *  @abstract   Create a MPSMatrixDescriptor with the specified dimensions and data type.
 *
 *  @param      rows                The number of rows of the matrix.
 *
 *  @param      columns             The number of columns of the matrix.
 *
 *  @param      rowBytes            The number of bytes between starting elements of consecutive
 *                                  rows.  Must be a multiple of the element size.
 *
 *  @param      dataType            The type of the data to be stored in the matrix.
 *
 *  @discussion For performance considerations the optimal row stride may not necessarily be equal
 *              to the number of columns in the matrix.  The MPSMatrix class provides a method which
 *              may be used to determine this value, see the rowBytesFromColumns API in the MPSMatrix
 *              class.
 */
+(__nonnull instancetype) matrixDescriptorWithDimensions: (NSUInteger)              rows
                                                 columns: (NSUInteger)              columns
                                                rowBytes: (NSUInteger)              rowBytes
                                                dataType: (MPSDataType)             dataType;

/*!
 *  @abstract   Return the recommended row stride, in bytes, for a given number of
 *              columns.
 *
 *  @param      columns         The number of columns in the matrix for which the recommended
 *                              row stride, in bytes, is to be determined.
 *
 *  @param      dataType        The type of matrix data values.
 *
 *  @discussion To achieve best performance the optimal stride between rows of a matrix is not
 *              necessarily equivalent to the number of columns.  This method returns the row stride, in
 *              bytes, which gives best performance for a given number of columns.  Using this row stride
 *              to construct your array is recommended, but not required (provided that the stride
 *              used is still large enough to allocate a full row of data).
 */
+(size_t) rowBytesFromColumns: (NSUInteger) columns
                     dataType: (MPSDataType) dataType;

@end // MPSMatrixDescriptor

/*!
 *  @class      MPSMatrix
 *
 *  @dependency This depends on Metal.framework
 *
 *  @discussion A MPSMatrix object describes a 2-dimensional array of data and provides storage
 *              for its values.  MPSMatrix objects serve as inputs and outputs of MPSMatrixKernel
 *              objects.
 *
 *              Implementation note:
 *              A MPSMatrix object maintains its internal storage using a MTLBuffer object and thus
 *              the same rules for maintaining coherency of a MTLBuffer's data between CPU memory and GPU
 *              memory apply to a MPSMatrix.  Data is assumed to be stored in row-major layout.
 */
MPS_CLASS_AVAILABLE_STARTING( __MAC_10_12, __IPHONE_10_0, __TVOS_10_0)
@interface MPSMatrix: NSObject

/*! @property   device
 *  @discussion The device on which the MPSMatrix will be used.
 */
@property (readonly, retain, nonatomic, nonnull) id<MTLDevice> device;

/*! @property   rows
 *  @discussion The number of rows in the MPSMatrix.
 */
@property (readonly, nonatomic) NSUInteger rows;

/*! @property   columns
 *  @discussion The number of columns in the MPSMatrix.
 */
@property (readonly, nonatomic) NSUInteger columns;

/*! @property   dataType
 *  @discussion The type of the MPSMatrix data.
 */
@property (readonly, nonatomic) MPSDataType dataType;

/*! @property   rowBytes
 *  @discussion The stride, in bytes, between corresponding elements of
 *              consecutive rows.
 */
@property (readonly, nonatomic) NSUInteger rowBytes;

/*! @property   data
 *  @discussion An MTLBuffer to store the data.
 */
@property (readonly, nonnull, nonatomic) id<MTLBuffer> data;

/*!
 *  @abstract   Initialize a MPSMatrix object with a MTLBuffer.
 *
 *  @param      buffer          The MTLBuffer object which contains the data to use for the
 *                              MPSMatrix. May not be NULL.
 *
 *  @param      descriptor      The MPSMatrixDescriptor. May not be NULL.
 *
 *  @return     A valid MPSMatrix object or nil, if failure.
 *
 *  @discussion This function returns a MPSMatrix object which uses the supplied MTLBuffer.  The
 *              dimensions and stride of the matrix are specified by the MPSMatrixDescriptor object.
 *
 *              The provided MTLBuffer must have enough storage to hold
 *
 *                  (descriptor.rows-1) * descriptor.rowBytes + descriptor.columns * (element size) bytes.
 *
 */
-(nonnull instancetype) initWithBuffer: (nonnull id<MTLBuffer>) buffer
                            descriptor: (nonnull MPSMatrixDescriptor*) descriptor;

/*
 * Use one of the above initialization methods instead.
 */
-(nonnull instancetype) init NS_UNAVAILABLE;

@end // MPSMatrix

#ifdef __cplusplus
}   // extern "C"
#endif

#endif /* MPSMatrix_h */
