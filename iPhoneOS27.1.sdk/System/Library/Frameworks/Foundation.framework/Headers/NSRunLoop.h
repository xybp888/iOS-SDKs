/*	NSRunLoop.h
	Copyright (c) 1994-2019, Apple Inc. All rights reserved.
*/

#import <Foundation/NSObject.h>
#import <Foundation/NSDate.h>
#import <CoreFoundation/CFRunLoop.h>

@class NSTimer, NSPort, NSArray<ObjectType>, NSString;

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

/// The mode set to handle input sources other than connection objects.
///
/// This is the most commonly used run-loop mode.
FOUNDATION_EXPORT NSRunLoopMode const NSDefaultRunLoopMode;
/// A pseudo-mode that includes one or more other run loop modes.
///
/// You can use this mode to add an object to all the common modes. For details on how to add modes to this group, see `CFRunLoopAddCommonMode`.
FOUNDATION_EXPORT NSRunLoopMode const NSRunLoopCommonModes API_AVAILABLE(macos(10.5), ios(2.0), watchos(2.0), tvos(9.0));

/// The programmatic interface to objects that manage input sources.
///
/// A ``RunLoop`` object processes input for sources, such as mouse and keyboard events from the window system and ``Port`` objects. A ``RunLoop`` object also processes ``Timer`` events.
///
/// Your application neither creates nor explicitly manages ``RunLoop`` objects. The system creates a ``RunLoop`` object as needed for each ``Thread`` object, including the application's main thread. If you need to access the current thread's run loop, use the class method ``current``.
///
/// Note that from the perspective of ``RunLoop``, ``Timer`` objects aren't "input"—they're a special type, and they don't cause the run loop to return when they fire.
///
/// > Warning:
/// > The ``RunLoop`` class is generally not thread-safe, and you must call its methods only within the context of the current thread. Don't call the methods of a ``RunLoop`` object running in a different thread, which might cause unexpected results.
@interface NSRunLoop : NSObject

/// Returns the run loop for the current thread.
///
/// If a run loop does not yet exist for the thread, one is created and returned.
@property (class, readonly, strong) NSRunLoop *currentRunLoop NS_SWIFT_UNAVAILABLE_FROM_ASYNC("currentRunLoop cannot be used from async contexts.");
/// Returns the run loop of the main thread.
@property (class, readonly, strong) NSRunLoop *mainRunLoop API_AVAILABLE(macos(10.5), ios(2.0), watchos(2.0), tvos(9.0));

/// The receiver's current input mode.
///
/// This property contains the current input mode only while the receiver is running; otherwise, it returns `nil`. The current mode is set by the methods that run the run loop, such as ``RunLoop/acceptInput(forMode:before:)`` and ``RunLoop/run(mode:before:)``.
@property (nullable, readonly, copy) NSRunLoopMode currentMode;

/// Returns the receiver's underlying `CFRunLoop` object.
///
/// You can use the returned run loop to configure the current run loop using Core Foundation function calls, for example, to set up a run loop observer.
- (CFRunLoopRef)getCFRunLoop CF_RETURNS_NOT_RETAINED;

/// Registers a given timer with a given input mode.
///
/// - Parameters:
///   - timer: The timer to register with the receiver.
///   - mode: The mode in which to add the timer. You may specify a custom mode or use one of the modes listed in ``RunLoop/Mode``.
///
/// You can add a timer to multiple input modes. While running in the designated mode, the receiver causes the timer to fire on or after its scheduled fire date. Upon firing, the timer invokes its associated handler routine, which is a selector on a designated object.
///
/// The receiver retains `aTimer`. To remove a timer from all run loop modes on which it is installed, send an ``Timer/invalidate()`` message to the timer.
- (void)addTimer:(NSTimer *)timer forMode:(NSRunLoopMode)mode;

/// Adds a port as an input source to the specified mode of the run loop.
///
/// - Parameters:
///   - aPort: The port to add to the receiver.
///   - mode: The mode in which to add the port. You may specify a custom mode or use one of the modes listed in ``RunLoop/Mode``.
///
/// This method schedules the port with the receiver. You can add a port to multiple input modes. When the receiver is running in the specified mode, it dispatches messages destined for that port to the port's designated handler routine.
- (void)addPort:(NSPort *)aPort forMode:(NSRunLoopMode)mode;
/// Removes a port from the specified input mode of the run loop.
///
/// - Parameters:
///   - aPort: The port to remove from the receiver.
///   - mode: The mode from which to remove the port. You may specify a custom mode or use one of the modes listed in ``RunLoop/Mode``.
///
/// If you added the port to multiple input modes, you must remove it from each mode separately.
- (void)removePort:(NSPort *)aPort forMode:(NSRunLoopMode)mode;

/// Performs one pass through the run loop in the specified mode and returns the date at which the next timer is scheduled to fire.
///
/// - Parameter mode: The run loop mode to search. You may specify a custom mode or use one of the modes listed in ``RunLoop/Mode``.
/// - Returns: The date at which the next timer is scheduled to fire, or `nil` if there are no input sources for this mode.
///
/// The run loop is entered with an immediate timeout, so the run loop does not block, waiting for input, if no input sources need processing.
- (nullable NSDate *)limitDateForMode:(NSRunLoopMode)mode;

/// Runs the loop once or until the specified date, accepting input only for the specified mode.
///
/// - Parameters:
///   - mode: The mode in which to run. You may specify a custom mode or use one of the modes listed in ``RunLoop/Mode``.
///   - limitDate: The date up until which to run.
///
/// If no input sources or timers are attached to the run loop, this method exits immediately; otherwise, it runs the run loop once, returning as soon as one input source processes a message or the specified time elapses.
///
/// > Note:
/// > A timer is not considered an input source and may fire multiple times when waiting for this method to return.
///
/// Manually removing all known input sources and timers from the run loop is not a guarantee that the run loop will exit. macOS can install and remove additional input sources as needed to process requests targeted at the receiver's thread. Those sources could therefore prevent the run loop from exiting.
- (void)acceptInputForMode:(NSRunLoopMode)mode beforeDate:(NSDate *)limitDate NS_SWIFT_UNAVAILABLE_FROM_ASYNC("acceptInput(for:before:) cannot be used from async contexts.");

@end

@interface NSRunLoop (NSRunLoopConveniences)

/// Puts the receiver into a permanent loop, during which time it processes data from all attached input sources.
///
/// If no input sources or timers are attached to the run loop, this method exits immediately; otherwise, it runs the receiver in the ``RunLoop/Mode/default`` mode by repeatedly invoking ``RunLoop/run(mode:before:)``. In other words, this method effectively begins an infinite loop that processes data from the run loop's input sources and timers.
///
/// Manually removing all known input sources and timers from the run loop is not a guarantee that the run loop will exit. macOS can install and remove additional input sources as needed to process requests targeted at the receiver's thread. Those sources could therefore prevent the run loop from exiting.
///
/// If you want the run loop to terminate, you shouldn't use this method. Instead, use one of the other run methods and also check other arbitrary conditions of your own, in a loop. A simple example would be:
///
/// ```objc
/// BOOL shouldKeepRunning = YES; // global
/// NSRunLoop *theRL = [NSRunLoop currentRunLoop];
/// while (shouldKeepRunning && [theRL runMode:NSDefaultRunLoopMode beforeDate:[NSDate distantFuture]]);
/// ```
- (void)run NS_SWIFT_UNAVAILABLE_FROM_ASYNC("run cannot be used from async contexts.");

/// Runs the loop until the specified date, during which time it processes data from all attached input sources.
///
/// - Parameter limitDate: The date up until which to run.
///
/// If no input sources or timers are attached to the run loop, this method exits immediately; otherwise, it runs the receiver in the ``RunLoop/Mode/default`` mode by repeatedly invoking ``RunLoop/run(mode:before:)`` until the specified expiration date.
- (void)runUntilDate:(NSDate *)limitDate NS_SWIFT_UNAVAILABLE_FROM_ASYNC("run(until:) cannot be used from async contexts.");

/// Runs the loop once, blocking for input in the specified mode until a given date.
///
/// - Parameters:
///   - mode: The mode in which to run. You may specify a custom mode or use one of the modes listed in ``RunLoop/Mode``.
///   - limitDate: The date until which to block.
/// - Returns: `YES` if the run loop ran and processed an input source or if the specified timeout value was reached; otherwise, `NO` if the run loop could not be started.
///
/// If no input sources or timers are attached to the run loop, this method exits immediately and returns `NO`; otherwise, it returns after either the first input source is processed or `limitDate` is reached.
///
/// > Note:
/// > A timer is not considered an input source and may fire multiple times when waiting for this method to return. Manually removing all known input sources and timers from the run loop does not guarantee that the run loop will exit immediately.
- (BOOL)runMode:(NSRunLoopMode)mode beforeDate:(NSDate *)limitDate NS_SWIFT_UNAVAILABLE_FROM_ASYNC("run(_:before:) cannot be used from async contexts.");

#if TARGET_OS_OSX
/// Deprecated. Does nothing.
- (void)configureAsServer API_DEPRECATED("Not supported", macos(10.0,10.5), ios(2.0,2.0), watchos(2.0,2.0), tvos(9.0,9.0));
#endif

/// Schedules the execution of a block on the target run loop in given modes.
/// - parameter: modes   An array of input modes for which the block may be executed.
/// - parameter: block   The block to execute
- (void)performInModes:(NSArray<NSRunLoopMode> *)modes block:(void (NS_SWIFT_SENDABLE ^)(void))block API_AVAILABLE(macosx(10.12), ios(10.0), watchos(3.0), tvos(10.0));

/// Schedules the execution of a block on the target run loop.
/// - parameter: block   The block to execute
- (void)performBlock:(void (NS_SWIFT_SENDABLE ^)(void))block API_AVAILABLE(macosx(10.12), ios(10.0), watchos(3.0), tvos(10.0));

@end

/* *************** 	Delayed perform	 ******************/

@interface NSObject (NSDelayedPerforming)

- (void)performSelector:(SEL)aSelector withObject:(nullable id)anArgument afterDelay:(NSTimeInterval)delay inModes:(NSArray<NSRunLoopMode> *)modes;
- (void)performSelector:(SEL)aSelector withObject:(nullable id)anArgument afterDelay:(NSTimeInterval)delay;
+ (void)cancelPreviousPerformRequestsWithTarget:(id)aTarget selector:(SEL)aSelector object:(nullable id)anArgument;
+ (void)cancelPreviousPerformRequestsWithTarget:(id)aTarget;

@end

@interface NSRunLoop (NSOrderedPerform)

/// Schedules the sending of a message on the receiver.
///
/// - Parameters:
///   - aSelector: A selector that identifies the method to invoke. The method should not have a significant return value and should take a single argument of type `id`.
///   - target: The object that defines the selector in `aSelector`.
///   - arg: The argument to pass to the method when it is performed. Pass `nil` if the method does not take an argument.
///   - order: The priority for the message. If multiple messages are scheduled, the messages with a lower order value are sent first.
///   - modes: An array of input modes for which the message may be sent. You may specify custom modes or use one of the modes listed in ``RunLoop/Mode``.
///
/// This method sets up a timer to perform the `aSelector` message on the receiver at the start of the next run loop iteration, according to the specified modes. The timer is configured to run in the modes specified by the `modes` parameter. When the timer fires, the thread attempts to dequeue the message from the run loop and perform the selector. It succeeds if the run loop is running and in one of the specified modes; otherwise, the timer waits until the run loop is in one of those modes.
///
/// This method returns before the `aSelector` message is sent. The receiver retains the `target` and `arg` objects until the timer for the selector fires, and then releases them as part of cleanup.
///
/// Use this method if you want multiple messages to be sent after the current event has been processed and you want to make sure these messages are sent in a certain order.
- (void)performSelector:(SEL)aSelector target:(id)target argument:(nullable id)arg order:(NSUInteger)order modes:(NSArray<NSRunLoopMode> *)modes;
/// Cancels the sending of a previously scheduled message.
///
/// - Parameters:
///   - aSelector: The previously-specified selector.
///   - target: The previously-specified target.
///   - arg: The previously-specified argument.
///
/// You can use this method to cancel a message previously scheduled with the ``RunLoop/perform(_:target:argument:order:modes:)`` method. The parameters identify the message uniquely. This method removes the perform request from all modes of the run loop.
- (void)cancelPerformSelector:(SEL)aSelector target:(id)target argument:(nullable id)arg;
/// Cancels all outstanding ordered performs scheduled with a given target.
///
/// - Parameter target: The previously-specified target.
///
/// This method cancels the previously scheduled messages associated with the target, ignoring the selector and argument of the scheduled operation. This is in contrast to ``RunLoop/cancelPerform(_:target:argument:)``, which requires you to match the selector and argument as well as the target. This method removes the perform requests from all modes of the run loop.
- (void)cancelPerformSelectorsWithTarget:(id)target;

@end

NS_HEADER_AUDIT_END(nullability, sendability)
