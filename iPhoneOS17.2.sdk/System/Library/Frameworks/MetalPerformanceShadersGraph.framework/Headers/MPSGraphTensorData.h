//
//  MPSGraphTensorData.h
//  MPSGraph
//
//  Created on 2/4/20.
//  Copyright © 2020 Apple Inc. All rights reserved.
//

#ifndef MPSGraphTensorData_h
#define MPSGraphTensorData_h

#import <MetalPerformanceShadersGraph/MPSGraphCore.h>
#import <MetalPerformanceShadersGraph/MPSGraphDevice.h>

NS_ASSUME_NONNULL_BEGIN

/// Representation of a compute datatype
///
/// MPSGraphTensorData is how we pass data to an MPSGraph, a reference will be taken to your data and used just in time when MPSGraph is run.
MPS_CLASS_AVAILABLE_STARTING(macos(11.0), ios(14.0), tvos(14.0))
@interface MPSGraphTensorData : MPSGraphObject

/// shape of the tensorData
@property (readonly, copy, nonatomic) MPSShape *shape;

/// dataType of the tensorData
@property (readonly, nonatomic) MPSDataType dataType;

/// device of the tensorData
@property (readonly, nonatomic) MPSGraphDevice * device;

/// Initialize an MPSGraphTensorData with an NSData on an MPSDevice
///
/// - Parameters:
///   - device: MPSDevice on which the MPSGraphTensorData exists
///   - data: NSData from which to copy the contents
///   - shape: shape of the output tensor
///   - dataType: dataType of the placeholder tensor
/// - Returns: A valid MPSGraphTensorData, or nil if allocation failure.

-(instancetype) initWithDevice:(MPSGraphDevice *) device
                          data:(NSData *) data
                         shape:(MPSShape *) shape
                      dataType:(MPSDataType) dataType;

/// Initialize an MPSGraphTensorData with an MTLBuffer 
/// The device of the MTLBuffer will be used to get the MPSDevice for this MPSGraphTensorData.
///
/// - Parameters:
///   - buffer: MTLBuffer to be used within the MPSGraphTensorData
///   - shape: shape of the output tensor
///   - dataType: dataType of the placeholder tensor
/// - Returns: A valid MPSGraphTensorData, or nil if allocation failure.
-(instancetype) initWithMTLBuffer:(id<MTLBuffer>) buffer
                            shape:(MPSShape *) shape
                         dataType:(MPSDataType) dataType
MPS_SWIFT_NAME( init(_:shape:dataType:) );

/// Initialize an MPSGraphTensorData with an MTLBuffer 
/// The device of the MTLBuffer will be used to get the MPSDevice for this MPSGraphTensorData.
///
/// - Parameters:
///   - buffer: MTLBuffer to be used within the MPSGraphTensorData
///   - shape: shape of the output tensor
///   - dataType: dataType of the placeholder tensor
///   - rowBytes: rowBytes for the fastest moving dimension, must be larger than or equal to sizeOf(dataType)shape[rank - 1] and must be a multiple of sizeOf(dataType)
/// - Returns: A valid MPSGraphTensorData, or nil if allocation failure.
-(instancetype) initWithMTLBuffer:(id<MTLBuffer>) buffer
                            shape:(MPSShape *) shape
                         dataType:(MPSDataType) dataType
                         rowBytes:(NSUInteger) rowBytes
MPS_SWIFT_NAME( init(_:shape:dataType:rowBytes:) )
MPS_AVAILABLE_STARTING(macos(12.3), ios(15.4), tvos(15.4));

/// Initialize an MPSGraphTensorData with an MPSMatrix 
/// The device of the MPSMatrix will be used to get the MPSDevice for this MPSGraphTensorData.
///
/// - Parameters:
///   - matrix: MPSMatrix to be used within the MPSGraphTensorData
/// - Returns: A valid MPSGraphTensorData, or nil if allocation failure.
-(instancetype) initWithMPSMatrix:(MPSMatrix *) matrix
MPS_SWIFT_NAME( init(_:) );

/// Initialize an MPSGraphTensorData with an MPSMatrix enforcing rank of the result. 
/// The device of the MPSMatrix will be used to get the MPSDevice for this MPSGraphTensorData.
///
/// - Parameters:
///   - matrix: MPSMatrix to be used within the MPSGraphTensorData
///   - rank: The rank of the resulting TensorData tensor. NOTE: must be within { 1, ... ,16 }.
/// - Returns: A valid MPSGraphTensorData of given rank, or nil if allocation failure.
-(instancetype) initWithMPSMatrix:(MPSMatrix *) matrix
                             rank:(NSUInteger) rank
MPS_SWIFT_NAME( init(_:rank:) );



/// Initialize an MPSGraphTensorData with an MPSVector 
/// The device of the MPSVector will be used to get the MPSDevice for this MPSGraphTensorData.
///
/// - Parameters:
///   - vector: MPSVector to be used within the MPSGraphTensorData
/// - Returns: A valid MPSGraphTensorData, or nil if allocation failure.
-(instancetype) initWithMPSVector:(MPSVector *) vector
MPS_SWIFT_NAME( init(_:) );

/// Initialize an MPSGraphTensorData with an MPSVector enforcing rank of the result. 
/// The device of the MPSVector will be used to get the MPSDevice for this MPSGraphTensorData.
///
/// - Parameters:
///   - vector: MPSVector to be used within the MPSGraphTensorData
///   - rank: The rank of the resulting TensorData tensor. NOTE: must be within { 1, ... ,16 }.
/// - Returns: A valid MPSGraphTensorData, or nil if allocation failure.
-(instancetype) initWithMPSVector:(MPSVector *) vector
                             rank:(NSUInteger) rank
MPS_SWIFT_NAME( init(_:rank:) );



/// Initialize an MPSGraphTensorData with an MPSNDArray 
/// The device of the MPSNDArray will be used to get the MPSDevice for this MPSGraphTensorData.
///
/// - Parameters:
///   - ndarray: MPSNDArray to be used within the MPSGraphTensorData
/// - Returns: A valid MPSGraphTensorData, or nil if allocation failure.
-(instancetype) initWithMPSNDArray:(MPSNDArray *) ndarray
MPS_SWIFT_NAME( init(_:) );

/// Initialize an MPSGraphTensorData with an MPSImage batch, the dataLayout used will be NHWC, 
/// call a transpose or permute to change to a layout of your choice.
///
/// - Parameters:
///   - imageBatch: The device on which the kernel will run, unorm8 and unorm16 images will create a float32 tensorData
/// - Returns: A valid MPSGraphTensorData, or nil if allocation failure.
-(instancetype) initWithMPSImageBatch:(MPSImageBatch *) imageBatch
MPS_SWIFT_NAME( init(_:) );

/// Return an mpsndarray object will copy contents if the contents are not stored in an MPSNDArray
///
/// - Returns: A valid MPSNDArray, or nil if allocation fails.
-(MPSNDArray *)mpsndarray;

@end

NS_ASSUME_NONNULL_END


#endif /* MPSGraphTensorData_h */
