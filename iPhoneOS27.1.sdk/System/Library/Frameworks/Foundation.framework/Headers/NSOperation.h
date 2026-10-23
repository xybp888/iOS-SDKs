/*	NSOperation.h
	Copyright (c) 2006-2019, Apple Inc. All rights reserved.
*/

#import <Foundation/NSObject.h>
#import <Foundation/NSException.h>
#import <Foundation/NSProgress.h>
#import <sys/qos.h>
#import <dispatch/dispatch.h>

@class NSArray<ObjectType>, NSSet;

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

#define NSOperationQualityOfService NSQualityOfService
#define NSOperationQualityOfServiceUserInteractive NSQualityOfServiceUserInteractive
#define NSOperationQualityOfServiceUserInitiated NSQualityOfServiceUserInitiated
#define NSOperationQualityOfServiceUtility NSQualityOfServiceUtility
#define NSOperationQualityOfServiceBackground NSQualityOfServiceBackground

/// An abstract class that represents the code and data associated with a single task.
///
/// Because the ``Operation`` class is an abstract class, you do not use it directly but instead subclass or use one of the system-defined subclasses (``NSInvocationOperation`` or ``BlockOperation``) to perform the actual task. Despite being abstract, the base implementation of ``Operation`` does include significant logic to coordinate the safe execution of your task. The presence of this built-in logic allows you to focus on the actual implementation of your task, rather than on the glue code needed to ensure it works correctly with other system objects.
///
/// An operation object is a single-shot object—that is, it executes its task once and cannot be used to execute it again. You typically execute operations by adding them to an operation queue (an instance of the ``OperationQueue`` class). An operation queue executes its operations either directly, by running them on secondary threads, or indirectly using the `libdispatch` library (also known as Grand Central Dispatch). For more information about how queues execute operations, see ``OperationQueue``.
///
/// If you do not want to use an operation queue, you can execute an operation yourself by calling its ``start()`` method directly from your code. Executing operations manually does put more of a burden on your code, because starting an operation that is not in the ready state triggers an exception. The ``isReady`` property reports on the operation's readiness.
///
/// ### Operation Dependencies
///
/// Dependencies are a convenient way to execute operations in a specific order. You can add and remove dependencies for an operation using the ``addDependency(_:)`` and ``removeDependency(_:)`` methods. By default, an operation object that has dependencies is not considered ready until all of its dependent operation objects have finished executing. Once the last dependent operation finishes, however, the operation object becomes ready and able to execute.
///
/// The dependencies supported by `NSOperation` make no distinction about whether a dependent operation finished successfully or unsuccessfully. (In other words, canceling an operation similarly marks it as finished.) It is up to you to determine whether an operation with dependencies should proceed in cases where its dependent operations were cancelled or did not complete their task successfully. This may require you to incorporate some additional error tracking capabilities into your operation objects.
///
/// ### KVO-Compliant Properties
///
/// The `NSOperation` class is key-value coding (KVC) and key-value observing (KVO) compliant for several of its properties. As needed, you can observe these properties to control other parts of your application. To observe the properties, use the following key paths:
///
/// - `isCancelled` - read-only
/// - `isAsynchronous` - read-only
/// - `isExecuting` - read-only
/// - `isFinished` - read-only
/// - `isReady` - read-only
/// - `dependencies` - read-only
/// - `queuePriority` - readable and writable
/// - `completionBlock` - readable and writable
///
/// Although you can attach observers to these properties, you should not use Cocoa bindings to bind them to elements of your application's user interface. Code associated with your user interface typically must execute only in your application's main thread. Because an operation may execute in any thread, KVO notifications associated with that operation may similarly occur in any thread.
///
/// If you provide custom implementations for any of the preceding properties, your implementations must maintain KVC and KVO compliance. If you define additional properties for your `NSOperation` objects, it is recommended that you make those properties KVC and KVO compliant as well. For information on how to support key-value coding, see [Key-Value Coding Programming Guide](https://developer.apple.com/library/archive/documentation/Cocoa/Conceptual/KeyValueCoding/index.html#//apple_ref/doc/uid/10000107i). For information on how to support key-value observing, see [Key-Value Observing Programming Guide](https://developer.apple.com/library/archive/documentation/Cocoa/Conceptual/KeyValueObserving/KeyValueObserving.html#//apple_ref/doc/uid/10000177i).
///
/// ### Multicore Considerations
///
/// The `NSOperation` class is itself multicore aware. It is therefore safe to call the methods of an `NSOperation` object from multiple threads without creating additional locks to synchronize access to the object. This behavior is necessary because an operation typically runs in a separate thread from the one that created and is monitoring it.
///
/// When you subclass `NSOperation`, you must make sure that any overridden methods remain safe to call from multiple threads. If you implement custom methods in your subclass, such as custom data accessors, you must also make sure those methods are thread-safe. Thus, access to any data variables in the operation must be synchronized to prevent potential data corruption. For more information about synchronization, see [Threading Programming Guide](https://developer.apple.com/library/archive/documentation/Cocoa/Conceptual/Multithreading/Introduction/Introduction.html#//apple_ref/doc/uid/10000057i).
///
/// ### Asynchronous Versus Synchronous Operations
///
/// If you plan on executing an operation object manually, instead of adding it to a queue, you can design your operation to execute in a synchronous or asynchronous manner. Operation objects are synchronous by default. In a synchronous operation, the operation object does not create a separate thread on which to run its task. When you call the ``start()`` method of a synchronous operation directly from your code, the operation executes immediately in the current thread. By the time the ``start()`` method of such an object returns control to the caller, the task itself is complete.
///
/// When you call the ``start()`` method of an asynchronous operation, that method may return before the corresponding task is completed. An asynchronous operation object is responsible for scheduling its task on a separate thread. The operation could do that by starting a new thread directly, by calling an asynchronous method, or by submitting a block to a dispatch queue for execution. It does not actually matter if the operation is ongoing when control returns to the caller, only that it could be ongoing.
///
/// If you always plan to use queues to execute your operations, it is simpler to define them as synchronous. If you execute operations manually, though, you might want to define your operation objects as asynchronous. Defining an asynchronous operation requires more work, because you have to monitor the ongoing state of your task and report changes in that state using KVO notifications. But defining asynchronous operations is useful in cases where you want to ensure that a manually executed operation does not block the calling thread.
///
/// When you add an operation to an operation queue, the queue ignores the value of the ``isAsynchronous`` property and always calls the ``start()`` method from a separate thread. Therefore, if you always run operations by adding them to an operation queue, there is no reason to make them asynchronous.
///
/// For information on how to define both synchronous and asynchronous operations, see the subclassing notes.
///
/// ### Subclassing Notes
///
/// The `NSOperation` class provides the basic logic to track the execution state of your operation but otherwise must be subclassed to do any real work. How you create your subclass depends on whether your operation is designed to execute concurrently or non-concurrently.
///
/// #### Methods to Override
///
/// For non-concurrent operations, you typically override only one method:
///
/// - ``main()``
///
/// Into this method, you place the code needed to perform the given task. Of course, you should also define a custom initialization method to make it easier to create instances of your custom class. You might also want to define getter and setter methods to access the data from the operation. However, if you do define custom getter and setter methods, you must make sure those methods can be called safely from multiple threads.
///
/// If you are creating a concurrent operation, you need to override the following methods and properties at a minimum:
///
/// - ``start()``
/// - ``isAsynchronous``
/// - ``isExecuting``
/// - ``isFinished``
///
/// In a concurrent operation, your ``start()`` method is responsible for starting the operation in an asynchronous manner. Whether you spawn a thread or call an asynchronous function, you do it from this method. Upon starting the operation, your ``start()`` method should also update the execution state of the operation as reported by the ``isExecuting`` property. You do this by sending out KVO notifications for the ``isExecuting`` key path, which lets interested clients know that the operation is now running. Your ``isExecuting`` property must also provide the status in a thread-safe manner.
///
/// Upon completion or cancellation of its task, your concurrent operation object must generate KVO notifications for both the `isExecuting` and `isFinished` key paths to mark the final change of state for your operation. (In the case of cancellation, it is still important to update the `isFinished` key path, even if the operation did not completely finish its task. Queued operations must report that they are finished before they can be removed from a queue.) In addition to generating KVO notifications, your overrides of the ``isExecuting`` and ``isFinished`` properties should also continue to report accurate values based on the state of your operation.
///
/// For additional information and guidance on how to define concurrent operations, see [Concurrency Programming Guide](https://developer.apple.com/library/archive/documentation/General/Conceptual/ConcurrencyProgrammingGuide/Introduction/Introduction.html#//apple_ref/doc/uid/TP40008091).
///
/// > Important:
/// > At no time in your ``start()`` method should you ever call `super`. When you define a concurrent operation, you take it upon yourself to provide the same behavior that the default ``start()`` method provides, which includes starting the task and generating the appropriate KVO notifications. Your ``start()`` method should also check to see if the operation itself was cancelled before actually starting the task. For more information about cancellation semantics, see <doc:#Responding-to-the-Cancel-Command>.
///
/// Even for concurrent operations, there should be little need to override methods other than those described above. However, if you customize the dependency features of operations, you might have to override additional methods and provide additional KVO notifications. In the case of dependencies, this would likely only require providing notifications for the `isReady` key path. Because the ``dependencies`` property contains the list of dependent operations, changes to it are already handled by the default `NSOperation` class.
///
/// #### Maintaining Operation Object States
///
/// Operation objects maintain state information internally to determine when it is safe to execute and also to notify external clients of the progression through the operation's life cycle. Your custom subclasses maintains this state information to ensure the correct execution of operations in your code. The key paths associated with an operation's states are:
///
/// - term **`isReady`**: The `isReady` key path lets clients know when an operation is ready to execute. The ``isReady`` property contains the value `true` when the operation is ready to execute now or `false` if there are still unfinished operations on which it is dependent.
///
/// In most cases, you do not have to manage the state of this key path yourself. If the readiness of your operations is determined by factors other than dependent operations, however—such as by some external condition in your program—you can provide your own implementation of the ``isReady`` property and track your operation's readiness yourself. It is often simpler though just to create operation objects only when your external state allows it.
///
/// In macOS 10.6 and later, if you cancel an operation while it is waiting on the completion of one or more dependent operations, those dependencies are thereafter ignored and the value of this property is updated to reflect that it is now ready to run. This behavior gives an operation queue the chance to flush cancelled operations out of its queue more quickly.
/// - term **`isExecuting`**: The `isExecuting` key path lets clients know whether the operation is actively working on its assigned task. The ``isExecuting`` property must report the value `true` if the operation is working on its task or `false` if it is not.
///
/// If you replace the ``start()`` method of your operation object, you must also replace the ``isExecuting`` property and generate KVO notifications when the execution state of your operation changes.
/// - term **`isFinished`**: The `isFinished` key path lets clients know that an operation finished its task successfully or was cancelled and is exiting. An operation object does not clear a dependency until the value at the `isFinished` key path changes to `true`. Similarly, an operation queue does not dequeue an operation until the ``isFinished`` property contains the value `true`. Thus, marking operations as finished is critical to keeping queues from backing up with in-progress or cancelled operations.
///
/// If you replace the ``start()`` method or your operation object, you must also replace the ``isFinished`` property and generate KVO notifications when the operation finishes executing or is cancelled.
/// - term **`isCancelled`**: The `isCancelled` key path lets clients know that the cancellation of an operation was requested. Support for cancellation is voluntary but encouraged and your own code should not have to send KVO notifications for this key path. The handling of cancellation notices in an operation is described in more detail in <doc:#Responding-to-the-Cancel-Command>.
///
/// #### Responding to the Cancel Command
///
/// Once you add an operation to a queue, the operation is out of your hands. The queue takes over and handles the scheduling of that task. However, if you decide later that you do not want to execute the operation after all—because the user pressed a cancel button in a progress panel or quit the application, for example—you can cancel the operation to prevent it from consuming CPU time needlessly. You do this by calling the ``cancel()`` method of the operation object itself or by calling the ``OperationQueue/cancelAllOperations()`` method of the ``OperationQueue`` class.
///
/// Canceling an operation does not immediately force it to stop what it is doing. Although respecting the value in the ``isCancelled`` property is expected of all operations, your code must explicitly check the value in this property and abort as needed. The default implementation of `NSOperation` includes checks for cancellation. For example, if you cancel an operation before its ``start()`` method is called, the ``start()`` method exits without starting the task.
///
/// > Note:
/// > In macOS 10.6 and later, if you call the ``cancel()`` method on an operation that is in an operation queue and has unfinished dependent operations, those dependent operations are subsequently ignored. Because the operation is already cancelled, this behavior allows the queue to call the operation's ``start()`` method to remove the operation from the queue without calling its ``main()`` method. If you call the ``cancel()`` method on an operation that is not in a queue, the operation is immediately marked as being cancelled. In each case, marking the operation as ready or finished results in the generation of the appropriate KVO notifications.
///
/// You should always support cancellation semantics in any custom code you write. In particular, your main task code should periodically check the value of the ``isCancelled`` property. If the property reports the value <doc://com.apple.documentation/documentation/swift/true>, your operation object should clean up and exit as quickly as possible. If you implement a custom ``start()`` method, that method should include early checks for cancellation and behave appropriately. Your custom ``start()`` method must be prepared to handle this type of early cancellation.
///
/// In addition to simply exiting when an operation is cancelled, it is also important that you move a cancelled operation to the appropriate final state. Specifically, if you manage the values for the ``isFinished`` and ``isExecuting`` properties yourself (perhaps because you are implementing a concurrent operation), you must update those properties accordingly. Specifically, you must change the value returned by ``isFinished`` to <doc://com.apple.documentation/documentation/swift/true> and the value returned by ``isExecuting`` to <doc://com.apple.documentation/documentation/swift/false>. You must make these changes even if the operation was cancelled before it started executing.
NS_SWIFT_SENDABLE
API_AVAILABLE(macos(10.5), ios(2.0), watchos(2.0), tvos(9.0))
@interface NSOperation : NSObject
#if !__OBJC2__
{
@private
    id _private;
    int32_t _private1;
#if __LP64__
    int32_t _private1b;
#endif
}
#endif

/// Begins the execution of the operation.
///
/// The default implementation of this method updates the execution state of the operation and calls the receiver's
/// ``main`` method. This method also performs several checks to ensure that the operation can actually run. For
/// example, if the receiver was cancelled or is already finished, this method simply returns without calling
/// ``main``. If the operation is currently executing or is not ready to execute, this method throws an
/// `NSInvalidArgumentException` exception.
///
/// If you are implementing a concurrent operation, you must override this method and use it to initiate your
/// operation. Your custom implementation must not call `super` at any time. In addition to configuring the execution
/// environment for your task, your implementation of this method must also track the state of the operation and
/// provide appropriate state transitions. When the operation executes and subsequently finishes its work, it should
/// generate KVO notifications for the `isExecuting` and `isFinished` key paths respectively.
///
/// You can call this method explicitly if you want to execute your operations manually. However, it is a programmer
/// error to call this method on an operation object that is already in an operation queue or to queue the operation
/// after calling this method. Once you add an operation object to a queue, the queue assumes all responsibility for it.
- (void)start;

/// Performs the receiver's non-concurrent task.
///
/// The default implementation of this method does nothing. You should override this method to perform the desired
/// task. In your implementation, do not invoke `super`. This method will automatically execute within an autorelease
/// pool provided by `NSOperation`, so you do not need to create your own autorelease pool block in your
/// implementation.
///
/// If you are implementing a concurrent operation, you are not required to override this method but may do so if you
/// plan to call it from your custom ``start`` method.
- (void)main;

/// A Boolean value indicating whether the operation has been cancelled.
///
/// The default value of this property is `NO`. Calling the ``cancel`` method of this object sets the value of this
/// property to `YES`. Once canceled, an operation must move to the finished state.
///
/// Canceling an operation does not actively stop the receiver's code from executing. An operation object is
/// responsible for calling this method periodically and stopping itself if the method returns `YES`.
///
/// You should always check the value of this property before doing any work towards accomplishing the operation's
/// task, which typically means checking it at the beginning of your custom ``main`` method. It is possible for an
/// operation to be cancelled before it begins executing or at any time while it is executing.
@property (readonly, getter=isCancelled) BOOL cancelled;

/// Advises the operation object that it should stop executing its task.
///
/// This method does not force your operation code to stop. Instead, it updates the object's internal flags to
/// reflect the change in state. If the operation has already finished executing, this method has no effect.
/// Canceling an operation that is currently in an operation queue, but not yet executing, makes it possible to
/// remove the operation from the queue sooner than usual.
- (void)cancel;

/// A Boolean value indicating whether the operation is currently executing.
///
/// The value of this property is `YES` if the operation is currently executing its main task or `NO` if it is not.
///
/// When implementing a concurrent operation object, you must override the implementation of this property so that
/// you can return the execution state of your operation. In your custom implementation, you must generate KVO
/// notifications for the `isExecuting` key path whenever the execution state of your operation object changes.
@property (readonly, getter=isExecuting) BOOL executing;

/// A Boolean value indicating whether the operation has finished executing its task.
///
/// The value of this property is `YES` if the operation has finished its main task or `NO` if it is executing that
/// task or has not yet started it.
///
/// When implementing a concurrent operation object, you must override the implementation of this property so that
/// you can return the finished state of your operation. In your custom implementation, you must generate KVO
/// notifications for the `isFinished` key path whenever the finished state of your operation object changes.
@property (readonly, getter=isFinished) BOOL finished;

/// A Boolean value indicating whether the operation executes its task asynchronously.
///
/// Use the ``asynchronous`` property instead.
///
/// The default value of this property is `NO`. In macOS 10.6 and later, operation queues ignore the value in this
/// property and always start operations on a separate thread.
@property (readonly, getter=isConcurrent) BOOL concurrent; // To be deprecated; use and override 'asynchronous' below

/// A Boolean value indicating whether the operation executes its task asynchronously.
///
/// The default value of this property is `NO`. When implementing an asynchronous operation object, you must
/// implement this property and return `YES`.
@property (readonly, getter=isAsynchronous) BOOL asynchronous API_AVAILABLE(macos(10.8), ios(7.0), watchos(2.0), tvos(9.0));

/// A Boolean value indicating whether the operation can be performed now.
///
/// The readiness of operations is determined by their dependencies on other operations and potentially by custom
/// conditions that you define. The `NSOperation` class manages dependencies on other operations and reports the
/// readiness of the receiver based on those dependencies.
///
/// If you want to use custom conditions to define the readiness of your operation object, reimplement this property
/// and return a value that accurately reflects the readiness of the receiver. If you do so, your custom
/// implementation must get the default property value from `super` and incorporate that readiness value into the new
/// value of the property. In your custom implementation, you must generate KVO notifications for the `isReady` key
/// path whenever the ready state of your operation object changes.
@property (readonly, getter=isReady) BOOL ready;

/// Makes the receiver dependent on the completion of the specified operation.
///
/// The receiver is not considered ready to execute until all of its dependent operations have finished executing. If
/// the receiver is already executing its task, adding dependencies has no practical effect. This method may change
/// the `isReady` and `dependencies` properties of the receiver.
///
/// It is a programmer error to create any circular dependencies among a set of operations. Doing so can cause a
/// deadlock among the operations and may freeze your program.
///
/// - Parameter op: The operation on which the receiver should depend. The same dependency should not be added more
///   than once to the receiver, and the results of doing so are undefined.
- (void)addDependency:(NSOperation *)op;

/// Removes the receiver's dependence on the specified operation.
///
/// This method may change the `isReady` and `dependencies` properties of the receiver.
///
/// - Parameter op: The dependent operation to be removed from the receiver.
- (void)removeDependency:(NSOperation *)op;

/// An array of the operation objects that must finish executing before the current object can begin executing.
///
/// This property contains an array of `NSOperation` objects. To add an object to this array, use the
/// ``addDependency:`` method.
///
/// An operation object must not execute until all of its dependent operations finish executing. Operations are not
/// removed from this dependency list as they finish executing. You can use this list to track all dependent
/// operations, including those that have already finished executing. The only way to remove an operation from this
/// list is to use the ``removeDependency:`` method.
@property (readonly, copy) NSArray<NSOperation *> *dependencies;

/// These constants let you prioritize the order in which operations execute.
typedef NS_ENUM(NSInteger, NSOperationQueuePriority) {
	/// Operations receive very low priority for execution.
	NSOperationQueuePriorityVeryLow = -8L,
	/// Operations receive low priority for execution.
	NSOperationQueuePriorityLow = -4L,
	/// Operations receive the normal priority for execution.
	NSOperationQueuePriorityNormal = 0,
	/// Operations receive high priority for execution.
	NSOperationQueuePriorityHigh = 4,
	/// Operations receive very high priority for execution.
	NSOperationQueuePriorityVeryHigh = 8
};

/// The execution priority of the operation in an operation queue.
///
/// This property contains the relative priority of the operation. This value is used to influence the order in which
/// operations are dequeued and executed.
///
/// You should use priority values only as needed to classify the relative priority of non-dependent operations.
/// Priority values should not be used to implement dependency management among different operation objects. If you
/// need to establish dependencies between operations, use the ``addDependency:`` method instead.
@property NSOperationQueuePriority queuePriority;

/// The block to execute after the operation's main task is completed.
///
/// The completion block takes no parameters and has no return value.
///
/// The exact execution context for your completion block is not guaranteed but is typically a secondary thread.
/// Therefore, you should not use this block to do any work that requires a very specific execution context. Instead,
/// you should shunt that work to your application's main thread or to the specific thread that is capable of doing it.
///
/// Because the completion block executes after the operation indicates it has finished its task, you must not use a
/// completion block to queue additional work considered to be part of that task. A finished operation may finish
/// either because it was cancelled or because it successfully completed its task. You should take that fact into
/// account when writing your block code.
///
/// In iOS 8 and later and macOS 10.10 and later, this property is set to `nil` after the completion block begins
/// executing.
@property (nullable, copy) void (NS_SWIFT_SENDABLE ^completionBlock)(void) API_AVAILABLE(macos(10.6), ios(4.0), watchos(2.0), tvos(9.0));

/// Blocks execution of the current thread until the operation object finishes its task.
///
/// An operation object must never call this method on itself and should avoid calling it on any operations submitted
/// to the same operation queue as itself. Doing so can cause the operation to deadlock. It is generally safe to call
/// this method on an operation that is in a different operation queue, although it is still possible to create
/// deadlocks if each operation waits on the other.
- (void)waitUntilFinished API_AVAILABLE(macos(10.6), ios(4.0), watchos(2.0), tvos(9.0)) NS_SWIFT_UNAVAILABLE_FROM_ASYNC("Use completionBlock or a dependent Operation instead");

/// The thread priority to use when executing the operation.
///
/// Use `qualityOfService` instead.
@property double threadPriority API_DEPRECATED("Not supported", macos(10.6,10.10), ios(4.0,8.0), watchos(2.0,2.0), tvos(9.0,9.0));

/// The relative amount of importance for granting system resources to the operation.
///
/// Service levels affect the priority with which an operation object is given access to system resources such as CPU
/// time, network resources, disk resources, and so on. Operations with a higher quality of service level are given
/// greater priority over system resources so that they may perform their task more quickly.
@property NSQualityOfService qualityOfService API_AVAILABLE(macos(10.10), ios(8.0), watchos(2.0), tvos(9.0));

/// The name of the operation.
///
/// Assign a name to the operation object to help identify it during debugging.
@property (nullable, copy) NSString *name API_AVAILABLE(macos(10.10), ios(8.0), watchos(2.0), tvos(9.0));

@end


/// An operation that manages the concurrent execution of one or more blocks.
///
/// The ``BlockOperation`` class is a concrete subclass of ``Operation`` that manages the concurrent execution of one or more blocks. You can use this object to execute several blocks at once without having to create separate operation objects for each. When executing more than one block, the operation itself is considered finished only when all blocks have finished executing.
///
/// Blocks added to a block operation are dispatched with default priority to an appropriate work queue. The blocks themselves should not make any assumptions about the configuration of their execution environment.
///
/// For more information about blocks, see [Blocks Programming Topics](https://developer.apple.com/library/archive/documentation/Cocoa/Conceptual/Blocks/Articles/00_Introduction.html#//apple_ref/doc/uid/TP40007502).
NS_SWIFT_SENDABLE
API_AVAILABLE(macos(10.6), ios(4.0), watchos(2.0), tvos(9.0))
@interface NSBlockOperation : NSOperation

/// Creates and returns an `NSBlockOperation` object and adds the specified block to it.
///
/// - Parameter block: The block to add to the new block operation object's list. The block should take no parameters
///   and have no return value.
/// - Returns: A new block operation object.
+ (instancetype)blockOperationWithBlock:(void (NS_SWIFT_SENDABLE ^)(void))block;

/// Adds the specified block to the receiver's list of blocks to perform.
///
/// The specified block should not make any assumptions about its execution environment.
///
/// Calling this method while the receiver is executing or has already finished causes an
/// `NSInvalidArgumentException` exception to be thrown.
///
/// - Parameter block: The block to add to the receiver's list. The block should take no parameters and have no
///   return value.
- (void)addExecutionBlock:(void (NS_SWIFT_SENDABLE ^)(void))block;

/// The blocks associated with the receiver.
///
/// The blocks in this array are copies of those originally added using the ``addExecutionBlock:`` method.
@property (readonly, copy) NSArray<void (NS_SWIFT_SENDABLE ^)(void)> *executionBlocks;

@end


/// An operation that manages the execution of a single encapsulated task specified as an invocation.
///
/// The ``NSInvocationOperation`` class is a concrete subclass of ``Operation`` that you use to initiate an operation that consists of invoking a selector on a specified object. This class implements a non-concurrent operation.
///
/// For more information on concurrent versus non-concurrent operations, see ``Operation``.
API_AVAILABLE(macos(10.5), ios(2.0), watchos(2.0), tvos(9.0))
NS_SWIFT_UNAVAILABLE("NSInvocation and related APIs not available")
@interface NSInvocationOperation : NSOperation

/// Returns an `NSInvocationOperation` object initialized with the specified target and selector.
///
/// If you specify a selector with a non-void return type, you can get the return value by calling the `result` property after the operation finishes executing. The receiver tells the invocation object to retain its arguments.
///
/// - Parameter target: The object defining the specified selector.
/// - Parameter sel: The selector to invoke when running the operation.
/// - Parameter arg: The parameter object to pass to the selector. If the selector does not take an argument, specify `nil`.
- (nullable instancetype)initWithTarget:(id)target selector:(SEL)sel object:(nullable id)arg;
/// Returns an `NSInvocationOperation` object initialized with the specified invocation object.
///
/// This method is the designated initializer. The receiver tells the invocation object to retain its arguments.
///
/// - Parameter inv: The invocation object identifying the target object, selector, and parameter objects.
- (instancetype)initWithInvocation:(NSInvocation *)inv NS_DESIGNATED_INITIALIZER;

/// The receiver's invocation object.
///
/// The invocation object identifying the target object, selector, and parameters to use to execute the operation's task.
@property (readonly, retain) NSInvocation *invocation;

/// The result of the invocation or method.
///
/// The object returned by the method or an `NSValue` object containing the return value if it is not an object. `nil` if the method or invocation is not finished executing.
@property (nullable, readonly, retain) id result;

@end

/// Name of an exception raised when the result of an `NSInvocationOperation` is requested for an invocation method with a `void` return type.
FOUNDATION_EXPORT NSExceptionName const NSInvocationOperationVoidResultException API_AVAILABLE(macos(10.5), ios(2.0), watchos(2.0), tvos(9.0));
/// Name of an exception raised when the result of an `NSInvocationOperation` is requested after the operation was cancelled.
FOUNDATION_EXPORT NSExceptionName const NSInvocationOperationCancelledException API_AVAILABLE(macos(10.5), ios(2.0), watchos(2.0), tvos(9.0));

/// The default maximum number of operations to invoke concurrently in a queue.
///
/// The operation queue determines this number dynamically based on current system conditions.
static const NSInteger NSOperationQueueDefaultMaxConcurrentOperationCount = -1;

/// A queue that regulates the execution of operations.
///
/// An operation queue invokes its queued ``Operation`` objects based on their priority and readiness. After you add an operation to a queue, it remains in the queue until the operation finishes its task. You can't directly remove an operation from a queue after you add it.
///
/// > Note:
/// > Operation queues retain operations until the operations finish, and queues themselves are retained until all operations are finished. Suspending an operation queue with operations that aren't finished can result in a memory leak.
///
///
///
/// For more information about using operation queues, see the [Concurrency Programming Guide](https://developer.apple.com/library/archive/documentation/General/Conceptual/ConcurrencyProgrammingGuide/Introduction/Introduction.html#//apple_ref/doc/uid/TP40008091).
///
/// ### Determine the Execution Order
///
/// An operation queue organizes and invokes its operations according to their readiness, priority level, and interoperation dependencies. If all of the queued operations have the same ``Operation/queuePriority`` and the ``Operation/isReady`` property returns <doc://com.apple.documentation/documentation/swift/true>, the queue invokes them in the order you added them. Otherwise, the operation queue always invokes the operation with the highest priority relative to the other ready operations.
///
/// However, don't rely on queue semantics to ensure a specific execution order of operations  because changes in the readiness of an operation can change the resulting execution order. Interoperation dependencies provide an absolute execution order for operations, even if those operations are located in different operation queues. An operation object isn't ready to run until all of its dependent operations have finished running.
///
/// For details on how to set priority levels and dependencies, see Managing Dependencies in ``Operation``.
///
/// ### Respond to Operation Cancelation
///
/// Finishing its task doesn't necessarily mean that the operation performed that task to completion; an operation can also be canceled. Canceling an operation object leaves the object in the queue but notifies the object that it should stop its task as quickly as possible. For currently executing operations, this means that the operation object's work code must check the cancellation state, stop what it is doing, and mark itself as finished. For operations that are queued but not yet executing, the queue must still call the operation object's ``Operation/start()`` method so that it can processes the cancellation event and mark itself as finished.
///
/// > Note:
/// > Canceling an operation causes the operation to ignore any dependencies it may have. This behavior makes it possible for the queue to invoke the operation's ``Operation/start()`` method as soon as possible. The ``Operation/start()`` method, in turn, moves the operation to the finished state so that it can be removed from the queue.
///
/// For more information about operation cancellation, see <doc:Operation#Responding-to-the-Cancel-Command> in ``Operation``.
///
/// ### Observe Operations Using Key-Value Observing
///
/// The ``OperationQueue`` class is key-value coding (KVC) and key-value observing (KVO) compliant. You can observe these properties to control other parts of your application. To observe the properties, use the following key paths:
///
/// - ``operations`` — Read-only
/// - ``operationCount`` — Read-only
/// - ``maxConcurrentOperationCount`` — Readable and writable
/// - ``isSuspended`` — Readable and writable
/// - ``name`` — Readable and writable
///
/// Although you can attach observers to these properties, don't use Cocoa bindings to bind these properties to elements of your application's user interface. Code associated with your user interface typically must run only in your app's main thread. However, KVO notifications associated with an operation queue may occur in any thread.
///
/// For more information about KVO and how to attach observers to an object, see the [Key-Value Observing Programming Guide](https://developer.apple.com/library/archive/documentation/Cocoa/Conceptual/KeyValueObserving/KeyValueObserving.html#//apple_ref/doc/uid/10000177i).
///
/// ### Plan for Thread Safety
///
/// You can safely use a single ``OperationQueue`` object from multiple threads without creating additional locks to synchronize access to that object.
///
/// Operation queues use the <doc://com.apple.documentation/documentation/dispatch> framework to initiate the execution of their operations. As a result, queues always invoke operations on a separate thread, regardless of whether the operation is synchronous or asynchronous.
NS_SWIFT_SENDABLE
API_AVAILABLE(macos(10.5), ios(2.0), watchos(2.0), tvos(9.0))
@interface NSOperationQueue : NSObject <NSProgressReporting>

/// An object that represents the total progress of the operations executing in the queue.
///
/// By default, ``NSOperationQueue`` doesn't report progress until the `totalUnitCount` of the progress is set. When `totalUnitCount` is set, the queue begins reporting progress. Each operation in the queue contributes one unit of completion to the overall progress of the queue for operations that are finished by the end of `main`. Operations that override `start` and don't invoke super don't contribute to the queue's progress.
///
/// > Warning:
/// > Be careful to avoid race conditions and backward progress when updating `totalUnitCount`. Consider a queue with a progress that has a `completedUnitCount` equal to `5` and a `totalUnitCount` equal to `10`, representing 50% completion. If you add 90 more operations to the queue, the `totalUnitCount` is now `100`, and the progress completion reports 5%. If the progress object is connected to a progress bar, the bar would visibly jump backward from 50% to 5%, which may not be desirable.
///
/// To update `totalUnitCount` in a thread-safe manner, use the `addBarrierBlock:` method. This method ensures that the operation queue completes the operations in the queue, preventing an inadvertent backward jump in progress.
@property (readonly, strong) NSProgress *progress API_AVAILABLE(macos(10.15), ios(13.0), tvos(13.0), watchos(6.0));

/// Adds the specified operation to the receiver.
///
/// Once added, the specified operation remains in the queue until it finishes executing.
///
/// An operation object can be in at most one operation queue at a time and this method throws an
/// `NSInvalidArgumentException` exception if the operation is already in another queue. Similarly, this method throws
/// an `NSInvalidArgumentException` exception if the operation is currently executing or has already finished executing.
///
/// - Parameter op: The operation to be added to the queue.
- (void)addOperation:(NSOperation *)op;

/// Adds the specified operations to the queue.
///
/// An operation object can be in at most one operation queue at a time and cannot be added if it is currently
/// executing or finished. This method throws an `NSInvalidArgumentException` exception if any of those error
/// conditions are true for any of the operations in the `ops` parameter.
///
/// - Parameters:
///   - ops: The operations to be added to the queue.
///   - wait: If `YES`, the current thread is blocked until all of the specified operations finish executing. If
///     `NO`, the operations are added to the queue and control returns immediately to the caller.
- (void)addOperations:(NSArray<NSOperation *> *)ops waitUntilFinished:(BOOL)wait API_AVAILABLE(macos(10.6), ios(4.0), watchos(2.0), tvos(9.0)) NS_SWIFT_UNAVAILABLE_FROM_ASYNC("Use addBarrierBlock or a dependent Operations instead");

/// Wraps the specified block in an operation and adds it to the receiver.
///
/// This method adds a single block to the receiver by first wrapping it in an operation object. You should not
/// attempt to get a reference to the newly created operation object or determine its type information.
///
/// - Parameter block: The block to execute from the operation. The block takes no parameters and has no return value.
- (void)addOperationWithBlock:(void (NS_SWIFT_SENDABLE ^)(void))block API_AVAILABLE(macos(10.6), ios(4.0), watchos(2.0), tvos(9.0)) NS_SWIFT_DISABLE_ASYNC;

/// Invokes a block when the queue finishes all enqueued operations, and prevents subsequent operations from starting until the block has completed.
///
/// This method is similar to `dispatch_barrier_async`.
///
/// - Parameters:
///   - barrier: The block to invoke after all currently enqueued operations have finished. Operations you add after the barrier block don't start until the block has completed.
- (void)addBarrierBlock:(void (NS_SWIFT_SENDABLE ^)(void))barrier API_AVAILABLE(macos(10.15), ios(13.0), tvos(13.0), watchos(6.0));

/// The maximum number of queued operations that can run at the same time.
///
/// The value in this property affects only the operations that the current queue has executing at the same time.
/// Other operation queues can also execute their maximum number of operations in parallel.
///
/// Reducing the number of concurrent operations does not affect any operations that are currently executing.
/// Specifying the value `NSOperationQueueDefaultMaxConcurrentOperationCount` (which is recommended) causes the
/// system to set the maximum number of operations based on system conditions.
///
/// The default value of this property is ``NSOperationQueueDefaultMaxConcurrentOperationCount``.
@property NSInteger maxConcurrentOperationCount;

/// A Boolean value indicating whether the queue is actively scheduling operations for execution.
///
/// When the value of this property is `NO`, the queue actively starts operations that are in the queue and ready to
/// execute. Setting this property to `YES` prevents the queue from starting any queued operations, but already
/// executing operations continue to execute. You may continue to add operations to a queue that is suspended but
/// those operations are not scheduled for execution until you change this property to `NO`.
///
/// Operations are removed from the queue only when they finish executing. However, in order to finish executing, an
/// operation must first be started. Because a suspended queue does not start any new operations, it does not remove
/// any operations (including cancelled operations) that are currently queued and not executing.
///
/// The default value of this property is `NO`.
@property (getter=isSuspended) BOOL suspended;

/// The name of the operation queue.
///
/// Names provide a way for you to identify your operation queues at run time. Tools may also use this name to
/// provide additional context during debugging or analysis of your code.
///
/// The default value of this property is a string containing the memory address of the operation queue.
@property (nullable, copy) NSString *name API_AVAILABLE(macos(10.6), ios(4.0), watchos(2.0), tvos(9.0));

/// The default service level to apply to operations that the queue invokes.
///
/// This property specifies the service level applied to operation objects added to the queue. If the operation object
/// has an explicit service level set, that value is used instead. For queues you create yourself, the default value
/// is `NSOperationQualityOfServiceBackground`. For the queue returned by the `mainQueue` method, the default value
/// is `NSOperationQualityOfServiceUserInteractive` and cannot be changed.
@property NSQualityOfService qualityOfService API_AVAILABLE(macos(10.10), ios(8.0), watchos(2.0), tvos(9.0));

/// The dispatch queue that the operation queue uses to invoke operations.
///
/// The default value of this property is `nil`. You can set the value of this property to an existing dispatch queue
/// to have enqueued operations interspersed with blocks submitted to that dispatch queue.
///
/// The value of this property should only be set if there are no operations in the queue; setting the value of this
/// property when `operationCount` is not equal to `0` raises an `NSInvalidArgumentException`. The value of this
/// property must not be the value returned by `dispatch_get_main_queue`. The quality-of-service level set for the
/// underlying dispatch queue overrides any value set for the operation queue's `qualityOfService` property.
@property (nullable, assign /* actually retain */) dispatch_queue_t underlyingQueue API_AVAILABLE(macos(10.10), ios(8.0), watchos(2.0), tvos(9.0));

/// Cancels all queued and executing operations.
///
/// This method calls the `cancel` method on all operations currently in the queue.
///
/// Canceling the operations does not automatically remove them from the queue or stop those that are currently
/// executing. For operations that are queued and waiting execution, the queue must still attempt to execute the
/// operation before recognizing that it is canceled and moving it to the finished state. For operations that are
/// already executing, the operation object itself must check for cancellation and stop what it is doing so that it
/// can move to the finished state.
- (void)cancelAllOperations;

/// Blocks the current thread until all the receiver's queued and executing operations finish executing.
///
/// When called, this method blocks the current thread and waits for the receiver's current and queued operations to
/// finish executing. While the current thread is blocked, the receiver continues to launch already queued operations
/// and monitor those that are executing. During this time, the current thread cannot add operations to the queue, but
/// other threads may. Once all of the pending operations are finished, this method returns.
///
/// If there are no operations in the queue, this method returns immediately.
- (void)waitUntilAllOperationsAreFinished NS_SWIFT_UNAVAILABLE_FROM_ASYNC("Use addBarrierBlock or a dependent Operations instead");

/// Returns the operation queue that launched the current operation.
///
/// You can use this method from within a running operation object to get a reference to the operation queue that
/// started it. Calling this method from outside the context of a running operation typically results in `nil` being
/// returned.
@property (class, readonly, strong, nullable) NSOperationQueue *currentQueue API_AVAILABLE(macos(10.6), ios(4.0), watchos(2.0), tvos(9.0));

/// Returns the operation queue associated with the main thread.
///
/// The returned queue executes one operation at a time on the app's main thread. The execution of operations on the
/// main thread is interleaved with the other tasks that must execute on the main thread, such as the servicing of
/// events and the updating of an app's user interface.
@property (class, readonly, strong) NSOperationQueue *mainQueue API_AVAILABLE(macos(10.6), ios(4.0), watchos(2.0), tvos(9.0));

@end

@interface NSOperationQueue (NSDeprecated)

// These two functions are inherently a race condition and should be avoided if possible

/// The operations currently in the queue.
///
/// The array in this property contains zero or more `NSOperation` objects in the order you added them to the queue.
/// This order doesn't necessarily reflect the order in which the queue invokes those operations.
@property (readonly, copy) NSArray<__kindof NSOperation *> *operations API_DEPRECATED("access to operations is inherently a race condition, it should not be used. For barrier style behaviors please use addBarrierBlock: instead", macos(10.5, API_TO_BE_DEPRECATED), ios(2.0, API_TO_BE_DEPRECATED), watchos(2.0, API_TO_BE_DEPRECATED), tvos(9.0, API_TO_BE_DEPRECATED));

/// The number of operations currently in the queue.
///
/// Because the number of operations in the queue changes as those operations finish executing, the value returned by
/// this property reflects the instantaneous number of operations at the time the property was accessed. By the time
/// you use the value, the actual number of operations may be different. As a result, do not use this value for object
/// enumerations or other precise calculations.
@property (readonly) NSUInteger operationCount API_DEPRECATED_WITH_REPLACEMENT("progress.completedUnitCount", macos(10.6, API_TO_BE_DEPRECATED), ios(4.0, API_TO_BE_DEPRECATED), watchos(2.0, API_TO_BE_DEPRECATED), tvos(9.0, API_TO_BE_DEPRECATED));

@end

NS_HEADER_AUDIT_END(nullability, sendability)

