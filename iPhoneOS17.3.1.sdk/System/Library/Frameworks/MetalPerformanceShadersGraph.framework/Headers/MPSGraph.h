//
//  MPSGraph.h
//  MetalPerformanceShadersGraph
//
//  Created on 11/10/19.
//  Copyright © 2019 Apple Inc. All rights reserved.
//

#ifndef MPSGraph_h
#define MPSGraph_h

#import <MetalPerformanceShadersGraph/MPSGraphCore.h>
#import <MetalPerformanceShadersGraph/MPSGraphDevice.h>
#import <MetalPerformanceShadersGraph/MPSGraphTensor.h>
#import <MetalPerformanceShadersGraph/MPSGraphTensorData.h>
#import <MetalPerformanceShadersGraph/MPSGraphOperation.h>

NS_ASSUME_NONNULL_BEGIN

@class MPSGraphExecutable;

/// The options available to a graph.
typedef NS_ENUM(uint64_t, MPSGraphOptions)
{
    /// No Options.
    MPSGraphOptionsNone                                            MPS_ENUM_AVAILABLE_STARTING(macos(11.0), ios(14.0), tvos(14.0)) MPS_SWIFT_NAME(none) =   0,
    /// The graph synchronizes results to the CPU using a blit encoder if on a discrete GPU at the end of execution.
    MPSGraphOptionsSynchronizeResults                              MPS_ENUM_AVAILABLE_STARTING(macos(11.0), ios(14.0), tvos(14.0))                      =   1L,
    /// The framework prints more logging info.
    MPSGraphOptionsVerbose                                         MPS_ENUM_AVAILABLE_STARTING(macos(11.0), ios(14.0), tvos(14.0))                      =   2L,
    /// The framework uses these options as default if not overriden.
    MPSGraphOptionsDefault                                         MPS_ENUM_AVAILABLE_STARTING(macos(11.0), ios(14.0), tvos(14.0))                      =   MPSGraphOptionsSynchronizeResults,
};

/// Optimization levels to tradeoff compilation time for even more runtime performance by running more passes.
typedef NS_ENUM(uint64_t, MPSGraphOptimization)
{
    /// Graph performs core optimizations only.
    MPSGraphOptimizationLevel0                        MPS_ENUM_AVAILABLE_STARTING(macos(12.3), ios(15.4), tvos(15.4)) MPS_SWIFT_NAME(level0) =   0,
    /// Graph performs additional Optimizations, like using the placement pass to dispatch across different HW blocks like the NeuralEngine and CPU along with the GPU.
    MPSGraphOptimizationLevel1                        MPS_ENUM_AVAILABLE_STARTING(macos(12.3), ios(15.4), tvos(15.4))                        =   1L,
};

/// Optimization profile used as heuristic as graph compiler optimizes network.
typedef NS_ENUM(uint64_t, MPSGraphOptimizationProfile)
{
    /// Default, graph optimized for performance.
    MPSGraphOptimizationProfilePerformance                        MPS_ENUM_AVAILABLE_STARTING(macos(12.3), ios(15.4), tvos(15.4)) MPS_SWIFT_NAME(performance) =   0,
    /// Graph optimized for power efficiency.
    MPSGraphOptimizationProfilePowerEfficiency                    MPS_ENUM_AVAILABLE_STARTING(macos(12.3), ios(15.4), tvos(15.4))                             =   1L,
};

/// Execution events that can be used with shared events.
typedef NS_ENUM(uint64_t, MPSGraphExecutionStage)
{
    /// stage when execution of the graph completes.
    MPSGraphExecutionStageCompleted                        MPS_ENUM_AVAILABLE_STARTING(macos(13.0), ios(16.0), tvos(16.0)) MPS_SWIFT_NAME(completed) =   0L,
};

/// A dictionary of tensors and correspondiing tensorData for them.
MPS_AVAILABLE_STARTING(macos(11.0), ios(14.0), tvos(14.0))
typedef NSDictionary<MPSGraphTensor*, MPSGraphTensorData *> MPSGraphTensorDataDictionary;

/// A dictionary of tensors and correspondiing shapes for them.
MPS_AVAILABLE_STARTING(macos(11.0), ios(14.0), tvos(14.0))
typedef NSDictionary<MPSGraphTensor*, MPSGraphShapedType *> MPSGraphTensorShapedTypeDictionary;

/// A notification when graph execution: has finished.
///
/// - Parameters:
///   - resultsDictionary: If no error, the results dictionary produced by the graph operation.
///   - error: If an error occurs, more information might be found here.
typedef void (^MPSGraphCompletionHandler)(MPSGraphTensorDataDictionary * resultsDictionary,
                                          NSError * _Nullable error);

/// A notification when graph execution: has been scheduled.
///
/// - Parameters:
///   - resultsDictionary: If no error, the results dictionary produced by the graph operation. If Graph has not yet allocated the results will be NSNull.
///   - error: If an error occurs, more information might be found here.
typedef void (^MPSGraphScheduledHandler)(MPSGraphTensorDataDictionary * resultsDictionary,
                                         NSError * _Nullable error);

/// A notification when compilation: has finished.
///
/// - Parameters:
///   - executable: If no error, the executable produced by the compilation.
///   - error: If an error occurs, more information might be found here.
typedef void (^MPSGraphCompilationCompletionHandler)(MPSGraphExecutable* executable,
                                                     NSError * _Nullable error);

/// This is a class that consists of all the levers for compiling graphs.
MPS_CLASS_AVAILABLE_STARTING(macos(12.0), ios(15.0), tvos(15.0))
@interface MPSGraphCompilationDescriptor : MPSGraphObject <NSCopying>

/// Turns off type inference and relies on type inference during runtime.
-(void) disableTypeInference;

/// The optimization level for the graph execution, default is MPSGraphOptimizationLevel1.
@property (readwrite, nonatomic) MPSGraphOptimization optimizationLevel MPS_AVAILABLE_STARTING(macos(12.3), ios(15.4), tvos(15.4));

/// Flag that makes the compile or specialize call blocking till the entire compilation is complete, defaults to NO.
@property (readwrite, nonatomic) BOOL waitForCompilationCompletion MPS_AVAILABLE_STARTING(macos(13.0), ios(16.0), tvos(16.0));

/// The graph calls this handler at the completion of the compilation, default value is nil.
@property (readwrite, atomic) MPSGraphCompilationCompletionHandler compilationCompletionHandler MPS_AVAILABLE_STARTING(macos(13.0), ios(16.0), tvos(16.0));

/// The dispatch queue used for the compilation, default value is nil.
@property (readwrite, atomic, retain) dispatch_queue_t dispatchQueue MPS_AVAILABLE_STARTING(macos(13.0), ios(16.0), tvos(16.0));

/// The optimization profile for the graph optimization, default is MPSGraphOptimizationProfilePerformance.
@property (readwrite, nonatomic) MPSGraphOptimizationProfile optimizationProfile
MPS_AVAILABLE_STARTING_BUT_DEPRECATED("MPSGraph will automatically provide the best performance and power efficiency with MPSGraphOptimizationLevel1.",
                                      macos(12.3, 14.0), ios(15.4, 17.0), tvos(15.4, 17.0));

@end

/// This is a class that consists of all the levers  to synchronize and schedule graph execution.
MPS_CLASS_AVAILABLE_STARTING(macos(11.0), ios(14.0), tvos(14.0))
@interface MPSGraphExecutionDescriptor : MPSGraphObject

/// The graph calls this handler when it schedules the execution, default value is nil.
@property (readwrite, atomic) MPSGraphScheduledHandler scheduledHandler;

/// The graph calls this handler at the completion of the execution, default value is nil.
@property (readwrite, atomic) MPSGraphCompletionHandler completionHandler;

/// Flag that makes the execution call blocking till the entire compilation is complete, defaults to NO.
@property (readwrite, atomic) BOOL waitUntilCompleted;

/// compilationDescriptor for the graph, default value is nil.
@property (readwrite, atomic, copy, nullable) MPSGraphCompilationDescriptor *compilationDescriptor
MPS_AVAILABLE_STARTING(macos(12.3), ios(15.4), tvos(15.4));

/// Executable waits on these shared events before scheduling execution on the HW, this does not include encoding which can still continue.
///
/// - Parameters:
///   - event: shared event graph waits on.
///   - value: value of shared event graph waits on.
-(void) waitForEvent:(id<MTLSharedEvent>) event
               value:(uint64_t) value
MPS_AVAILABLE_STARTING(macos(13.0), ios(16.0), tvos(16.0));

/// Executable signals these shared events at execution stage and immediately proceeds.
///
/// - Parameters:
///   - event: shared event to signal.
///   - executionStage: execution stage to signal event at.
///   - value: value for shared event to wait on.
-(void) signalEvent:(id<MTLSharedEvent>) event
   atExecutionEvent:(MPSGraphExecutionStage) executionStage
              value:(uint64_t) value
MPS_AVAILABLE_STARTING(macos(13.0), ios(16.0), tvos(16.0));

@end

/// Optimized representation of a compute graph of MPSGraphOperations and MPSGraphTensors.
///
/// An MPSGraph is a symbolic representation of operations to be utilized to execute compute graphs on a device.
MPS_CLASS_AVAILABLE_STARTING(macos(11.0), ios(14.0), tvos(14.0))
@interface MPSGraph : MPSGraphObject

/// Options for the graph, the default value is MPSGraphOptionsDefault.
@property (readwrite, atomic) MPSGraphOptions options;

/// Create a new MPSGraph to insert nodes in.
+(instancetype) new;

/// Initialize an MPSGraph to insert nodes in.
-(instancetype) init;

/// Array of all the placeholder tensors.
@property (readonly, nonnull, nonatomic) NSArray<MPSGraphTensor *> *placeholderTensors;

/// Compiles the graph for given feeds to return targetTensor values, ensuring all target operations would be executed.
///
/// This call blocks till execution has completed. The compilation descriptor helps specialize the executable returned.
///
/// - Parameters:
///   - device: MPSGraph device to optimize for.
///   - feeds: Feeds dictionary for the placeholder tensors.
///   - targetTensors: Tensors for which the caller wishes MPSGraphTensorData to be returned.
///   - targetOperations: Operations to be completed at the end of the run.
///   - compilationDescriptor: compilation descriptor to set different compilation parameters.
/// - Returns: A valid MPSGraphExecutable object
-(MPSGraphExecutable *) compileWithDevice:(MPSGraphDevice * _Nullable) device
                                    feeds:(MPSGraphTensorShapedTypeDictionary *) feeds
                            targetTensors:(NSArray<MPSGraphTensor *> *) targetTensors
                         targetOperations:(NSArray<MPSGraphOperation *> * _Nullable) targetOperations
                    compilationDescriptor:(MPSGraphCompilationDescriptor * _Nullable) compilationDescriptor MPS_AVAILABLE_STARTING(macos(12.0), ios(15.0), tvos(15.0));

/// Runs the graph for given feeds to return targetTensor values, ensuring all target operations also executed.
///
/// This call blocks till execution has completed.
///
/// - Parameters:
///   - feeds: Feeds dictionary for the placeholder tensors.
///   - targetTensors: Tensors for which the caller wishes MPSGraphTensorData to be returned.
///   - targetOperations: Operations to be completed at the end of the run.
/// - Returns: A valid MPSGraphTensor : MPSGraphTensorData dictionary with results synchronized to the CPU memory.
-(MPSGraphTensorDataDictionary *) runWithFeeds:(MPSGraphTensorDataDictionary *) feeds
                                 targetTensors:(NSArray<MPSGraphTensor *> *) targetTensors
                              targetOperations:(NSArray<MPSGraphOperation *> * _Nullable) targetOperations
MPS_SWIFT_NAME( run(feeds:targetTensors:targetOperations:) );

/// Runs the graph for given feeds to return targetTensor values, ensuring all target operations also executed. This call blocks till execution has completed.
///
/// - Parameters:
///   - commandQueue: CommandQueue passed to exectute the graph on.
///   - feeds: Feeds dictionary for the placeholder tensors.
///   - targetTensors: Tensors for which the caller wishes MPSGraphTensorData to be returned.
///   - targetOperations: Operations to be completed at the end of the run.
/// - Returns: A valid MPSGraphTensor : MPSGraphTensorData dictionary with results synchronized to the CPU memory.
-(MPSGraphTensorDataDictionary *) runWithMTLCommandQueue:(id<MTLCommandQueue>) commandQueue
                                                   feeds:(MPSGraphTensorDataDictionary *) feeds
                                           targetTensors:(NSArray<MPSGraphTensor *> *) targetTensors
                                        targetOperations:(NSArray<MPSGraphOperation *> * _Nullable) targetOperations
MPS_SWIFT_NAME( run(with:feeds:targetTensors:targetOperations:) );

/// Runs the graph for given feeds to return targetTensor values in the resultsDictionary provided by the user.
///
/// It also ensures all target operations also executed. This call blocks till execution has completed.
///
/// - Parameters:
///   - commandQueue: CommandQueue passed to exectute the graph on.
///   - feeds: Feeds dictionary for the placeholder tensors.
///   - targetOperations: Operations to be completed at the end of the run.
///   - resultsDictionary: MPSGraphTensors dictionary passed by user, these will be filled with graph output data.
-(void) runWithMTLCommandQueue:(id<MTLCommandQueue>) commandQueue
                         feeds:(MPSGraphTensorDataDictionary *) feeds
              targetOperations:(NSArray<MPSGraphOperation *> * _Nullable) targetOperations
             resultsDictionary:(MPSGraphTensorDataDictionary *) resultsDictionary
MPS_SWIFT_NAME( run(with:feeds:targetOperations:resultsDictionary:) );


// Async methods

/// Runs the graph for given feeds to return targetTensor values, ensuring all target operations also executed. 
///
/// This call is asynchronous and will return immediately if a completionHandler is set.
///
/// - Parameters:
///   - feeds: Feeds dictionary for the placeholder tensors.
///   - targetTensors: Tensors for which the caller wishes MPSGraphTensorData to be returned.
///   - targetOperations: Operations to be completed at the end of the run.
///   - executionDescriptor: ExecutionDescriptor to be passed in and used.
/// - Returns: A valid MPSGraphTensor : MPSGraphTensorData dictionary with results synchronized to the CPU memory.
-(MPSGraphTensorDataDictionary *) runAsyncWithFeeds:(MPSGraphTensorDataDictionary *) feeds
                                      targetTensors:(NSArray<MPSGraphTensor *> *) targetTensors
                                   targetOperations:(NSArray<MPSGraphOperation *> * _Nullable) targetOperations
                                executionDescriptor:(MPSGraphExecutionDescriptor * _Nullable) executionDescriptor
MPS_SWIFT_NAME( runAsync(feeds:targetTensors:targetOperations:executionDescriptor:) );


/// Runs the graph for given feeds to return targetTensor values, ensuring all target operations also executed. 
///
/// This call is asynchronous and will return immediately if a completionHandler is set.
///
/// - Parameters:
///   - commandQueue: CommandQueue passed to exectute the graph on.
///   - feeds: Feeds dictionary for the placeholder tensors.
///   - targetTensors: Tensors for which the caller wishes MPSGraphTensorData to be returned.
///   - targetOperations: Operations to be completed at the end of the run.
///   - executionDescriptor: ExecutionDescriptor to be passed in and used.
/// - Returns: A valid MPSGraphTensor : MPSGraphTensorData dictionary with results synchronized to the CPU memory if MPSGraphOptionsSynchronizeResults set.
-(MPSGraphTensorDataDictionary *) runAsyncWithMTLCommandQueue:(id<MTLCommandQueue>) commandQueue
                                                        feeds:(MPSGraphTensorDataDictionary *) feeds
                                                targetTensors:(NSArray<MPSGraphTensor *> *) targetTensors
                                             targetOperations:(NSArray<MPSGraphOperation *> * _Nullable) targetOperations
                                          executionDescriptor:(MPSGraphExecutionDescriptor * _Nullable) executionDescriptor
MPS_SWIFT_NAME( runAsync(with:feeds:targetTensors:targetOperations:executionDescriptor:) );

/// Encodes the graph for given feeds to return targetTensor values in the resultsDictionary provided by the user.
///
/// It ensures all target operations also executed. This call is asynchronous and will return immediately if a completionHandler is set.
///
/// - Parameters:
///   - commandQueue: CommandQueue passed to exectute the graph on.
///   - feeds: Feeds dictionary for the placeholder tensors.
///   - targetOperations: Operations to be completed at the end of the run.
///   - resultsDictionary: MPSGraphTensors dictionary passed by user, these will be filled with graph output data.
///   - executionDescriptor: ExecutionDescriptor to be passed in and used.
-(void) runAsyncWithMTLCommandQueue:(id<MTLCommandQueue>) commandQueue
                              feeds:(MPSGraphTensorDataDictionary *) feeds
                   targetOperations:(NSArray<MPSGraphOperation *> * _Nullable) targetOperations
                  resultsDictionary:(MPSGraphTensorDataDictionary *) resultsDictionary
                executionDescriptor:(MPSGraphExecutionDescriptor * _Nullable) executionDescriptor
MPS_SWIFT_NAME( runAsync(with:feeds:targetOperations:resultsDictionary:executionDescriptor:) );

/// Encodes graph for given feeds to return targetTensor values, ensuring all target operations also executed. 
///
/// This call is asynchronous and will return immediately if a completionHandler is set.
///
/// - Parameters:
///   - commandBuffer: commandBuffer passed to exectute the graph on, it is an MPSCommandBuffer, commitAndContinue might be called, please don't rely on underlying MTLCommandBuffer to remain uncommitted.
///   - feeds: Feeds dictionary for the placeholder tensors.
///   - targetTensors: Tensors for which the caller wishes MPSGraphTensorData to be returned.
///   - targetOperations: Operations to be completed at the end of the run.
///   - executionDescriptor: ExecutionDescriptor to be passed in and used.
/// - Returns: A valid MPSGraphTensor : MPSGraphTensorData dictionary with results synchronized to the CPU memory if MPSGraphOptionsSynchronizeResults set.
-(MPSGraphTensorDataDictionary *) encodeToCommandBuffer:(MPSCommandBuffer *) commandBuffer
                                                  feeds:(MPSGraphTensorDataDictionary *) feeds
                                          targetTensors:(NSArray<MPSGraphTensor *> *) targetTensors
                                       targetOperations:(NSArray<MPSGraphOperation *> * _Nullable) targetOperations
                                    executionDescriptor:(MPSGraphExecutionDescriptor * _Nullable) executionDescriptor
MPS_SWIFT_NAME( encode(to:feeds:targetTensors:targetOperations:executionDescriptor:) );

/// Encodes the graph for given feeds to return targetTensor values in the resultsDictionary provided by the user.
///
/// It ensures all target operations also executed. This call is asynchronous and will return immediately if a completionHandler is set.
///
/// - Parameters:
///   - commandBuffer: commandBuffer passed to execute the graph on, commitAndContinue might be called, please don't rely on underlying MTLCommandBuffer to remain uncommitted.
///   - feeds: Feeds dictionary for the placeholder tensors.
///   - targetOperations: Operations to be completed at the end of the run.
///   - resultsDictionary: MPSGraphTensors dictionary passed by user, these will be filled with graph output data.
///   - executionDescriptor: ExecutionDescriptor to be passed in and used.
-(void) encodeToCommandBuffer:(MPSCommandBuffer *) commandBuffer
                        feeds:(MPSGraphTensorDataDictionary *) feeds
             targetOperations:(NSArray<MPSGraphOperation *> * _Nullable) targetOperations
            resultsDictionary:(MPSGraphTensorDataDictionary *) resultsDictionary
          executionDescriptor:(MPSGraphExecutionDescriptor * _Nullable) executionDescriptor
MPS_SWIFT_NAME( encode(to:feeds:targetOperations:resultsDictionary:executionDescriptor:) );


@end

NS_ASSUME_NONNULL_END

#endif /* MPSGraph_h */
