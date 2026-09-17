/*	NSThread.h
	Copyright (c) 1994-2019, Apple Inc. All rights reserved.
*/

#import <Foundation/NSObject.h>
#import <Foundation/NSDate.h>
#import <Foundation/NSNotification.h>

@class NSArray<ObjectType>, NSMutableDictionary, NSDate, NSNumber, NSString;

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

/// A thread of execution.
///
/// Use this class when you want to have an Objective-C method run in its own thread of execution. Threads are especially useful when you need to perform a lengthy task, but don't want it to block the execution of the rest of the application. In particular, you can use threads to avoid blocking the main thread of the application, which handles user interface and event-related actions. Threads can also be used to divide a large job into several smaller jobs, which can lead to performance increases on multi-core computers.
///
/// The ``Thread`` class supports semantics similar to those of ``Operation`` for monitoring the runtime condition of a thread. You can use these semantics to cancel the execution of a thread or determine if the thread is still executing or has finished its task. Canceling a thread requires support from your thread code; see the description for ``cancel()`` for more information.
///
/// ### Subclassing Notes
///
/// You can subclass ``Thread`` and override the ``main()`` method to implement your thread's main entry point. If you override ``main()``, you do not need to invoke the inherited behavior by calling `super`.
@interface NSThread : NSObject  {
@private
    id _private;
    uint8_t _bytes[44];
}

/// Returns the thread object representing the current thread of execution.
@property (class, readonly, strong) NSThread *currentThread NS_SWIFT_UNAVAILABLE_FROM_ASYNC("Thread.current cannot be used from async contexts.");

+ (void)detachNewThreadWithBlock:(void (NS_SWIFT_SENDABLE ^)(void))block API_AVAILABLE(macosx(10.12), ios(10.0), watchos(3.0), tvos(10.0)) NS_SWIFT_DISABLE_ASYNC;

/// Detaches a new thread and uses the specified selector as the thread entry point.
///
/// The objects `aTarget` and `anArgument` are retained during the execution of the detached thread, then released. The detached thread is exited (using the `exit` class method) as soon as `aTarget` has completed executing the `aSelector` method.
///
/// If this thread is the first thread detached in the application, this method posts the `NSWillBecomeMultiThreaded` notification with object `nil` to the default notification center.
///
/// - Parameters:
///   - selector: The selector for the message to send to the target. This selector must take only one argument and must not have a return value.
///   - target: The object that will receive the message `aSelector` on the new thread.
///   - argument: The single argument passed to the target. May be `nil`.
+ (void)detachNewThreadSelector:(SEL)selector toTarget:(id)target withObject:(nullable id)argument;

/// Returns whether the application is multithreaded.
///
/// An application is considered multithreaded if a thread was ever detached from the main thread using either `detachNewThreadSelector:toTarget:withObject:` or `start`. If you detached a thread in your application using a non-Cocoa API, such as the POSIX or Multiprocessing Services APIs, this method could still return `NO`. The detached thread does not have to be currently running for the application to be considered multithreaded -- this method only indicates whether a single thread has been spawned.
///
/// - Returns: `YES` if the application is multithreaded, otherwise `NO`.
+ (BOOL)isMultiThreaded;

/// The thread object's dictionary.
///
/// You can use the returned dictionary to store thread-specific data. The thread dictionary is not used during any manipulations of the `NSThread` object -- it is simply a place where you can store any interesting data. For example, Foundation uses it to store the thread's default `NSConnection` and `NSAssertionHandler` instances. You may define your own keys for the dictionary.
@property (readonly, retain) NSMutableDictionary *threadDictionary;

/// Blocks the current thread until the time specified.
///
/// No run loop processing occurs while the thread is blocked.
///
/// - Parameter date: The time at which to resume processing.
+ (void)sleepUntilDate:(NSDate *)date NS_SWIFT_UNAVAILABLE_FROM_ASYNC("Use Task.sleep(until:clock:) instead.");

/// Sleeps the thread for a given time interval.
///
/// No run loop processing occurs while the thread is blocked.
///
/// - Parameter ti: The duration of the sleep.
+ (void)sleepForTimeInterval:(NSTimeInterval)ti NS_SWIFT_UNAVAILABLE_FROM_ASYNC("Use Task.sleep(until:clock:) instead.");

/// Terminates the current thread.
///
/// This method uses the `currentThread` class method to access the current thread. Before exiting the thread, this method posts the `NSThreadWillExit` notification with the thread being exited to the default notification center. Because notifications are delivered synchronously, all observers of `NSThreadWillExit` are guaranteed to receive the notification before the thread exits.
///
/// Invoking this method should be avoided as it does not give your thread a chance to clean up any resources it allocated during its execution.
+ (void)exit NS_SWIFT_UNAVAILABLE_FROM_ASYNC("Threads used in asynchronous contexts cannot be explicitly exited.");

/// Returns the current thread's priority.
///
/// The priorities in this range are mapped to the operating system's priority values. A "typical" thread priority might be 0.5, but because the priority is determined by the kernel, there is no guarantee what this value actually will be.
///
/// - Returns: The current thread's priority, which is specified by a floating point number from 0.0 to 1.0, where 1.0 is highest priority.
+ (double)threadPriority NS_SWIFT_UNAVAILABLE_FROM_ASYNC("Threads used in asynchronous context cannot get priorities.");

/// Sets the current thread's priority.
///
/// The priorities in this range are mapped to the operating system's priority values.
///
/// - Parameter p: The new priority, specified with a floating point number from 0.0 to 1.0, where 1.0 is highest priority.
/// - Returns: `YES` if the priority assignment succeeded, `NO` otherwise.
+ (BOOL)setThreadPriority:(double)p NS_SWIFT_UNAVAILABLE_FROM_ASYNC("Threads used in asynchronous context cannot set priorities.");

/// The receiver's priority.
///
/// The thread's priority, which is specified by a floating point number from 0.0 to 1.0, where 1.0 is highest priority. The priorities in this range are mapped to the operating system's priority values. A "typical" thread priority might be 0.5, but because the priority is determined by the kernel, there is no guarantee what this value actually will be.
@property double threadPriority API_AVAILABLE(macos(10.6), ios(4.0), watchos(2.0), tvos(9.0)); // To be deprecated; use qualityOfService below

@property NSQualityOfService qualityOfService API_AVAILABLE(macos(10.10), ios(8.0), watchos(2.0), tvos(9.0)); // read-only after the thread is started

/// Returns an array containing the call stack return addresses.
///
/// Each element is an `NSNumber` object containing an `NSUInteger` value.
@property (class, readonly, copy) NSArray<NSNumber *> *callStackReturnAddresses API_AVAILABLE(macos(10.5), ios(2.0), watchos(2.0), tvos(9.0));

/// Returns an array containing the call stack symbols.
///
/// Each element is an `NSString` object with a value in a format determined by the `backtrace_symbols()` function.
///
/// The return value describes the call stack backtrace of the current thread at the moment this method was called.
@property (class, readonly, copy) NSArray<NSString *> *callStackSymbols API_AVAILABLE(macos(10.6), ios(4.0), watchos(2.0), tvos(9.0));

/// The name of the receiver.
@property (nullable, copy) NSString *name API_AVAILABLE(macos(10.5), ios(2.0), watchos(2.0), tvos(9.0));

/// The stack size of the receiver, in bytes.
///
/// This value must be in bytes and a multiple of 4KB.
///
/// To change the stack size, you must set this property before starting your thread. Setting the stack size after the thread has started changes the attribute size (which is reflected by the `stackSize` method), but it does not affect the actual number of pages set aside for the thread.
@property NSUInteger stackSize API_AVAILABLE(macos(10.5), ios(2.0), watchos(2.0), tvos(9.0));

/// A Boolean value that indicates whether the receiver is the main thread.
@property (readonly) BOOL isMainThread API_AVAILABLE(macos(10.5), ios(2.0), watchos(2.0), tvos(9.0));

/// Returns a Boolean value that indicates whether the current thread is the main thread.
@property (class, readonly) BOOL isMainThread API_AVAILABLE(macos(10.5), ios(2.0), watchos(2.0), tvos(9.0)) NS_SWIFT_UNAVAILABLE_FROM_ASYNC("Work intended for the main actor should be marked with @MainActor"); // reports whether current thread is main

/// Returns the `NSThread` object representing the main thread.
@property (class, readonly, strong) NSThread *mainThread API_AVAILABLE(macos(10.5), ios(2.0), watchos(2.0), tvos(9.0));

/// Returns an initialized `NSThread` object.
///
/// This is the designated initializer for `NSThread`.
- (instancetype)init API_AVAILABLE(macos(10.5), ios(2.0), watchos(2.0), tvos(9.0)) NS_DESIGNATED_INITIALIZER;

/// Returns an `NSThread` object initialized with the given arguments.
///
/// The objects `target` and `argument` are retained during the execution of the detached thread. They are released when the thread finally exits.
///
/// - Parameters:
///   - target: The object to which the message specified by `selector` is sent.
///   - selector: The selector for the message to send to `target`. This selector must take only one argument and must not have a return value.
///   - argument: The single argument passed to the target. May be `nil`.
- (instancetype)initWithTarget:(id)target selector:(SEL)selector object:(nullable id)argument API_AVAILABLE(macos(10.5), ios(2.0), watchos(2.0), tvos(9.0));
- (instancetype)initWithBlock:(void (NS_SWIFT_SENDABLE ^)(void))block API_AVAILABLE(macosx(10.12), ios(10.0), watchos(3.0), tvos(10.0));

/// A Boolean value that indicates whether the receiver is executing.
@property (readonly, getter=isExecuting) BOOL executing API_AVAILABLE(macos(10.5), ios(2.0), watchos(2.0), tvos(9.0));

/// A Boolean value that indicates whether the receiver has finished execution.
@property (readonly, getter=isFinished) BOOL finished API_AVAILABLE(macos(10.5), ios(2.0), watchos(2.0), tvos(9.0));

/// A Boolean value that indicates whether the receiver is cancelled.
///
/// If your thread supports cancellation, it should check this property periodically and exit if it ever returns `YES`.
@property (readonly, getter=isCancelled) BOOL cancelled API_AVAILABLE(macos(10.5), ios(2.0), watchos(2.0), tvos(9.0));

/// Changes the cancelled state of the receiver to indicate that it should exit.
///
/// The semantics of this method are the same as those used for `NSOperation`. This method sets state information in the receiver that is then reflected by the `isCancelled` property. Threads that support cancellation should periodically call the `isCancelled` method to determine if the thread has in fact been cancelled, and exit if it has been.
- (void)cancel API_AVAILABLE(macos(10.5), ios(2.0), watchos(2.0), tvos(9.0));

/// Starts the receiver.
///
/// This method asynchronously spawns the new thread and invokes the receiver's `main` method on the new thread. The `isExecuting` property returns `YES` once the thread starts executing, which may occur after the `start` method returns.
///
/// If you initialized the receiver with a target and selector, the default `main` method invokes that selector automatically.
///
/// If this thread is the first thread detached in the application, this method posts the `NSWillBecomeMultiThreaded` notification with object `nil` to the default notification center.
- (void)start API_AVAILABLE(macos(10.5), ios(2.0), watchos(2.0), tvos(9.0));

/// The main entry point routine for the thread.
///
/// The default implementation of this method takes the target and selector used to initialize the receiver and invokes the selector on the specified target. If you subclass `NSThread`, you can override this method and use it to implement the main body of your thread instead. If you do so, you do not need to invoke `super`.
///
/// You should never invoke this method directly. You should always start your thread by invoking the `start` method.
- (void)main API_AVAILABLE(macos(10.5), ios(2.0), watchos(2.0), tvos(9.0));	// thread body method

@end

/// Posted when the first thread is detached from the current thread.
///
/// The `NSThread` class posts this notification at most once --- the first time a thread is detached using `detachNewThreadSelector(_:toTarget:with:)` or the `start()` method. Subsequent invocations of those methods do not post this notification. Observers of this notification have their notification method invoked in the main thread, not the new thread. The observer notification methods always execute before the new thread begins executing. This notification does not contain a notification object or a `userInfo` dictionary.
FOUNDATION_EXPORT NSNotificationName const NSWillBecomeMultiThreadedNotification API_DEPRECATED("This notification does not protect against data races", macos(10.0, 26.0), ios(2.0, 26.0), watchos(2.0, 26.0), tvos(9.0, 26.0), visionos(1.0, 26.0));
/// Not implemented.
FOUNDATION_EXPORT NSNotificationName const NSDidBecomeSingleThreadedNotification API_DEPRECATED("Programs no longer transition to single-threaded mode from threaded environments", macos(10.0, 26.0), ios(2.0, 26.0), watchos(2.0, 26.0), tvos(9.0, 26.0), visionos(1.0, 26.0));
/// Posted when a thread receives the `exit()` message, before the thread exits.
///
/// The notification object is the exiting `NSThread` object. This notification does not contain a `userInfo` dictionary. Observer methods invoked to receive this notification execute in the exiting thread, before it exits.
FOUNDATION_EXPORT NSNotificationName const NSThreadWillExitNotification API_DEPRECATED("This notification does not protect against data races", macos(10.0, 26.0), ios(2.0, 26.0), watchos(2.0, 26.0), tvos(9.0, 26.0), visionos(1.0, 26.0));

@interface NSObject (NSThreadPerformAdditions)

- (void)performSelectorOnMainThread:(SEL)aSelector withObject:(nullable id)arg waitUntilDone:(BOOL)wait modes:(nullable NSArray<NSString *> *)array NS_SWIFT_UNAVAILABLE_FROM_ASYNC("Work intended for the main actor should be marked with @MainActor");

- (void)performSelectorOnMainThread:(SEL)aSelector withObject:(nullable id)arg waitUntilDone:(BOOL)wait NS_SWIFT_UNAVAILABLE_FROM_ASYNC("Work intended for the main actor should be marked with @MainActor");
	// equivalent to the first method with kCFRunLoopCommonModes

- (void)performSelector:(SEL)aSelector onThread:(NSThread *)thr withObject:(nullable id)arg waitUntilDone:(BOOL)wait modes:(nullable NSArray<NSString *> *)array API_AVAILABLE(macos(10.5), ios(2.0), watchos(2.0), tvos(9.0)) NS_SWIFT_UNAVAILABLE_FROM_ASYNC("Asynchronous work should be called from isolation from an actor");

- (void)performSelector:(SEL)aSelector onThread:(NSThread *)thr withObject:(nullable id)arg waitUntilDone:(BOOL)wait API_AVAILABLE(macos(10.5), ios(2.0), watchos(2.0), tvos(9.0)) NS_SWIFT_UNAVAILABLE_FROM_ASYNC("Asynchronous work should be called from isolation from an actor");
	// equivalent to the first method with kCFRunLoopCommonModes

- (void)performSelectorInBackground:(SEL)aSelector withObject:(nullable id)arg API_AVAILABLE(macos(10.5), ios(2.0), watchos(2.0), tvos(9.0));

@end

NS_HEADER_AUDIT_END(nullability, sendability)
