//
//  MPSGraphExecutable.h
//  MPSGraph
//
//  Created on 4/11/21.
//  Copyright © 2021 Apple Inc. All rights reserved.
//

#ifndef MPSGraphExecutable_h
#define MPSGraphExecutable_h

#import <MetalPerformanceShadersGraph/MPSGraph.h>

NS_ASSUME_NONNULL_BEGIN

/// A notification when graph executable execution has finished.
///
/// - Parameters:
///   - results: If no error, the results produced by the graph operation. If Graph has not yet allocated the results this will be NSNull
///   - error: If an error occurs, more information might be found here.
MPS_AVAILABLE_STARTING(macos(12.0), ios(15.0), tvos(15.0))
typedef void (^MPSGraphExecutableCompletionHandler)(NSArray<MPSGraphTensorData *> * results,
                                                    NSError * _Nullable error);

/// A notification when graph executable execution has been scheduled.
///
/// - Parameters:
///   - results: If no error, the results produced by the graph operation.
///   - error: If an error occurs, more information might be found here.
MPS_AVAILABLE_STARTING(macos(12.0), ios(15.0), tvos(15.0))
typedef void (^MPSGraphExecutableScheduledHandler)(NSArray<MPSGraphTensorData *> * results,
                                                   NSError * _Nullable error);

MPS_CLASS_AVAILABLE_STARTING(macos(12.0), ios(15.0), tvos(15.0))
@interface MPSGraphExecutableExecutionDescriptor : MPSGraphObject<NSCopying>

/// ScheduledHandler for the graph executable, default value is nil.
@property (readwrite, atomic) MPSGraphExecutableScheduledHandler scheduledHandler;

/// CompletionHandler for the graph executable, default value is nil.
@property (readwrite, atomic) MPSGraphExecutableCompletionHandler completionHandler;

/// Flag for the graph executable to wait till the execution has completed, default value is false.
@property (readwrite, atomic) BOOL waitUntilCompleted;

/// Executable waits on these shared events before scheduling execution on the HW, this does not include encoding which can still continue.
///
/// - Parameters:
///   - event: Shared event to wait on.
///   - value: Value for shared event to wait on.
-(void) waitForEvent:(id<MTLSharedEvent>) event
               value:(uint64_t) value
MPS_AVAILABLE_STARTING(macos(13.0), ios(16.0), tvos(16.0));

/// Executable signals these shared events at execution stage and immediately proceeds.
///
/// - Parameters:
///   - event: Shared event to signal.
///   - executionStage: Execution stage to signal event at.
///   - value: Value for shared event to wait on.
-(void) signalEvent:(id<MTLSharedEvent>) event
   atExecutionEvent:(MPSGraphExecutionStage) executionStage
              value:(uint64_t) value
MPS_AVAILABLE_STARTING(macos(13.0), ios(16.0), tvos(16.0));

@end

/// The options available to a graph.
typedef NS_ENUM(uint64_t, MPSGraphDeploymentPlatform)
{
    /// Deployment platofmr for macOS.
    MPSGraphDeploymentPlatformMacOS                                        MPS_ENUM_AVAILABLE_STARTING(macos(14.0), ios(17.0), tvos(17.0)) MPS_SWIFT_NAME(macOS) = 0L,
    /// Deployment target for iOS.
    MPSGraphDeploymentPlatformIOS                                          MPS_ENUM_AVAILABLE_STARTING(macos(14.0), ios(17.0), tvos(17.0)) MPS_SWIFT_NAME(iOS)   = 1L,
    /// Deployment target for tvOS.
    MPSGraphDeploymentPlatformTvOS                                         MPS_ENUM_AVAILABLE_STARTING(macos(14.0), ios(17.0), tvos(17.0)) MPS_SWIFT_NAME(tvOS)  = 2L,
};


MPS_CLASS_AVAILABLE_STARTING(macos(14.0), ios(17.0), tvos(17.0))
@interface MPSGraphExecutableSerializationDescriptor : MPSGraphObject

/// Flag to append to an existing .mpsgraphpackage if found at provided url.
///
/// If false, the exisiting .mpsgraphpackage will be overwritten.
@property (readwrite, atomic) BOOL append;

/// The deployment platform used to serialize the MPSGraphExecutable.
///
/// Defaults to the current platform.
@property (readwrite, atomic) MPSGraphDeploymentPlatform deploymentPlatform;

/// The minimum deployment target to serialize the MPSGraphExecutable.
///
/// Defaults to the current sdk.
@property (readwrite, atomic) NSString* minimumDeploymentTarget;

@end

/// Compiled representation of a compute graph executable.
///
/// An MPSGraphExecutable is a compiled graph for specific feeds for specific targetTensors and target operations.
MPS_CLASS_AVAILABLE_STARTING(macos(12.0), ios(15.0), tvos(15.0))
@interface MPSGraphExecutable : MPSGraphObject

/// Options for the graph executable.
///
/// Default value is `MPSGraphOptionsDefault`.
@property (readwrite, atomic) MPSGraphOptions options;

/// Feed tensors for the graph, can be used to order the inputs when executable was created with an MPSGraph
@property (readonly, atomic, nullable) NSArray<MPSGraphTensor *> *feedTensors;

/// Target tensors for the graph, can be used to order the outputs when executable was created with an MPSGraph
@property (readonly, atomic, nullable) NSArray<MPSGraphTensor *> *targetTensors;

/// Specialize the MPSGraphExecutable and optimize it, use this method to choose when specialization happens, else it occurs at encode time automatically.
///
/// - Parameters:
///   - device: optional MPSGraph device to compile with
///   - inputTypes: input types
///   - compilationDescriptor: compilationDescriptor to be used to specialize, since the executable was created with a compilationDescriptor already this one overrides those settings to the extent it can.
-(void) specializeWithDevice:(MPSGraphDevice * _Nullable) device
                  inputTypes:(NSArray<MPSGraphType *> *) inputTypes
       compilationDescriptor:(MPSGraphCompilationDescriptor * _Nullable) compilationDescriptor;

/// Get output shapes for a specialized MPSGraphExecutable - in case specialization has not been done yet then calling this function will specialize for the given input shapes.
///
/// - Parameters:
///   - device: optional MPSGraph device to compile with
///   - inputTypes: input types
///   - compilationDescriptor: compilationDescriptor to be used to specialize, since the executable was created with a compilationDescriptor already this one overrides those settings to the extent it can.
-(NSArray<MPSGraphShapedType *> * _Nullable) getOutputTypesWithDevice:(MPSGraphDevice * _Nullable) device
                                                           inputTypes:(NSArray<MPSGraphType *> *) inputTypes
                                                compilationDescriptor:(MPSGraphCompilationDescriptor * _Nullable) compilationDescriptor
MPS_AVAILABLE_STARTING(macos(13.2), ios(16.3), tvos(16.3));

/// Runs the graph for given feeds to return targetTensor values, ensuring all target operations also executed. 
/// This call is synchronous and will return on completion of execution.
///
/// - Parameters:
///   - commandQueue: CommandQueue passed to exectute the graph on.
///   - inputsArray: Feeds tensorData for the placeholder tensors, same order as arguments of main function.
///   - resultsArray: Results tensorData for which the caller wishes MPSGraphTensorData to be returned.
/// - Returns: A valid MPSGraphTensorData array with results synchronized to the CPU memory if MPSGraphOptionsSynchronizeResults set.
-(NSArray<MPSGraphTensorData *> *) runWithMTLCommandQueue:(id<MTLCommandQueue>) commandQueue
                                              inputsArray:(NSArray<MPSGraphTensorData *> *) inputsArray
                                             resultsArray:(NSArray<MPSGraphTensorData *> * _Nullable) resultsArray
                                      executionDescriptor:(MPSGraphExecutableExecutionDescriptor * _Nullable) executionDescriptor
MPS_SWIFT_NAME( run(with:inputs:results:executionDescriptor:) );

/// Runs the graph for given feeds to return targetTensor values, ensuring all target operations also executed. 
/// This call is asynchronous and will return immediately.
///
/// - Parameters:
///   - commandQueue: CommandQueue passed to exectute the graph on.
///   - inputsArray: Feeds tensorData for the placeholder tensors, same order as arguments of main function.
///   - resultsArray: Tensors for which the caller wishes MPSGraphTensorData to be returned.
///   - executionDescriptor: ExecutionDescriptor to be passed in and used.
/// - Returns: A valid MPSGraphTensorData array with results synchronized to the CPU memory if MPSGraphOptionsSynchronizeResults set.
-(NSArray<MPSGraphTensorData *> *) runAsyncWithMTLCommandQueue:(id<MTLCommandQueue>) commandQueue
                                                   inputsArray:(NSArray<MPSGraphTensorData *> *) inputsArray
                                                  resultsArray:(NSArray<MPSGraphTensorData *> * _Nullable) resultsArray
                                           executionDescriptor:(MPSGraphExecutableExecutionDescriptor * _Nullable) executionDescriptor
MPS_SWIFT_NAME( runAsync(with:inputs:results:executionDescriptor:) );

/// Runs the graph for given feeds to return targetTensor values, ensuring all target operations also executed. 
/// This call is asynchronous and will return immediately after finishing encoding.
///
/// - Parameters:
///   - commandBuffer: CommandBuffer passed to exectute the graph on, commitAndContinue might be called, please don't rely on underlying MTLCommandBuffer to remain uncommitted
///   - inputsArray: Feeds tensorData for the placeholder tensors, same order as arguments of main function
///   - resultsArray: Tensors for which the caller wishes MPSGraphTensorData to be returned
///   - executionDescriptor: ExecutionDescriptor to be passed in and used,
/// - Returns: A valid MPSGraphTensorData array with results synchronized to the CPU memory if MPSGraphOptionsSynchronizeResults set.
-(NSArray<MPSGraphTensorData *> *) encodeToCommandBuffer:(MPSCommandBuffer *) commandBuffer
                                             inputsArray:(NSArray<MPSGraphTensorData *> *) inputsArray
                                            resultsArray:(NSArray<MPSGraphTensorData *> * _Nullable) resultsArray
                                     executionDescriptor:(MPSGraphExecutableExecutionDescriptor * _Nullable) executionDescriptor
MPS_SWIFT_NAME( encode(to:inputs:results:executionDescriptor:) );

/// Serialize the MPSGraph executable at the provided url.
///
/// - Parameters:
///   - url: The URL where to serialize the MPSGraph executable.
///   - descriptor: The descriptor to be used to serialize the graph.
-(void) serializeToMPSGraphPackageAtURL:(NSURL *) url
                             descriptor:(MPSGraphExecutableSerializationDescriptor *_Nullable) descriptor
MPS_SWIFT_NAME( serialize(package:descriptor:) )
MPS_AVAILABLE_STARTING(macos(14.0), ios(17.0), tvos(17.0));

/// Initialize the MPSGraph executable with the package at the provided url.
///
/// - Parameters:
///   - mpsgraphPackageURL: The URL where to read the serialized MPSGraphExecutable.
///   - compilationDescriptor: Compilation descriptor to be used to specialize, since the executable was created with a compilationDescriptor already this one overrides those settings to the extent it can.
-(instancetype) initWithMPSGraphPackageAtURL:(NSURL *)mpsgraphPackageURL
                       compilationDescriptor:(MPSGraphCompilationDescriptor * _Nullable) compilationDescriptor
MPS_SWIFT_NAME( init(package:descriptor:) )
MPS_AVAILABLE_STARTING(macos(14.0), ios(17.0), tvos(17.0));

@end

NS_ASSUME_NONNULL_END

#endif /* MPSGraphExecutable_h */
