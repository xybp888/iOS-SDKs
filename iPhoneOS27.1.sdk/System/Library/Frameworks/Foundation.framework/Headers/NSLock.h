/*	NSLock.h
	Copyright (c) 1994-2019, Apple Inc. All rights reserved.
*/

#import <Foundation/NSObject.h>

@class NSDate;

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

/// The elementary methods adopted by classes that define lock objects.
@protocol NSLocking

/// Attempts to acquire a lock, blocking a thread's execution until the lock can be acquired.
- (void)lock NS_SWIFT_UNAVAILABLE_FROM_ASYNC("Use async-safe scoped locking instead");

/// Relinquishes a previously acquired lock.
- (void)unlock NS_SWIFT_UNAVAILABLE_FROM_ASYNC("Use async-safe scoped locking instead");

@end

/// An object that coordinates the operation of multiple threads of execution within the same application.
NS_SWIFT_SENDABLE
@interface NSLock : NSObject <NSLocking>

#if !0
/// Attempts to acquire a lock and immediately returns a Boolean value that indicates whether the attempt was successful.
- (BOOL)tryLock NS_SWIFT_UNAVAILABLE_FROM_ASYNC("Use async-safe scoped locking instead");

/// Attempts to acquire a lock before a given date and returns a Boolean value indicating whether the attempt was successful.
- (BOOL)lockBeforeDate:(NSDate *)limit NS_SWIFT_UNAVAILABLE_FROM_ASYNC("Use async-safe scoped locking instead");
#endif 

/// The name associated with the receiver.
@property (nullable, copy) NSString *name API_AVAILABLE(macos(10.5), ios(2.0), watchos(2.0), tvos(9.0));

@end

#if !0
/// A lock that can be associated with specific, user-defined conditions.
NS_SWIFT_SENDABLE
@interface NSConditionLock : NSObject <NSLocking>

/// Initializes a newly allocated ``NSConditionLock`` object and sets its condition.
- (instancetype)initWithCondition:(NSInteger)condition NS_DESIGNATED_INITIALIZER;

/// The condition associated with the receiver.
@property (readonly) NSInteger condition;

/// Attempts to acquire a lock when the receiver's condition is equal to a specific value.
- (void)lockWhenCondition:(NSInteger)condition NS_SWIFT_UNAVAILABLE_FROM_ASYNC("Use async-safe scoped locking instead");

/// Attempts to acquire a lock and immediately returns a Boolean value that indicates whether the attempt was successful.
- (BOOL)tryLock NS_SWIFT_UNAVAILABLE_FROM_ASYNC("Use async-safe scoped locking instead");

/// Attempts to acquire a lock if the receiver's condition is equal to a specific value and immediately returns a Boolean value that indicates whether the attempt was successful.
- (BOOL)tryLockWhenCondition:(NSInteger)condition NS_SWIFT_UNAVAILABLE_FROM_ASYNC("Use async-safe scoped locking instead");

/// Relinquishes the lock and sets the receiver's condition.
- (void)unlockWithCondition:(NSInteger)condition NS_SWIFT_UNAVAILABLE_FROM_ASYNC("Use async-safe scoped locking instead");

/// Attempts to acquire a lock before a given date and returns a Boolean value indicating whether the attempt was successful.
- (BOOL)lockBeforeDate:(NSDate *)limit NS_SWIFT_UNAVAILABLE_FROM_ASYNC("Use async-safe scoped locking instead");

/// Attempts to acquire a lock when the receiver's condition is equal to a specific value, and returns before a given date.
- (BOOL)lockWhenCondition:(NSInteger)condition beforeDate:(NSDate *)limit NS_SWIFT_UNAVAILABLE_FROM_ASYNC("Use async-safe scoped locking instead");

/// The name associated with the receiver.
@property (nullable, copy) NSString *name API_AVAILABLE(macos(10.5), ios(2.0), watchos(2.0), tvos(9.0));

@end

/// A lock that may be acquired multiple times by the same thread without causing a deadlock.
NS_SWIFT_SENDABLE
@interface NSRecursiveLock : NSObject <NSLocking>

/// Attempts to acquire a lock and immediately returns a Boolean value that indicates whether the attempt was successful.
- (BOOL)tryLock NS_SWIFT_UNAVAILABLE_FROM_ASYNC("Use async-safe scoped locking instead");

/// Attempts to acquire a lock before a given date and returns a Boolean value indicating whether the attempt was successful.
- (BOOL)lockBeforeDate:(NSDate *)limit NS_SWIFT_UNAVAILABLE_FROM_ASYNC("Use async-safe scoped locking instead");

/// The name associated with the receiver.
@property (nullable, copy) NSString *name API_AVAILABLE(macos(10.5), ios(2.0), watchos(2.0), tvos(9.0));

@end


/// A condition variable whose semantics follow those used for POSIX-style conditions.
NS_SWIFT_SENDABLE
API_AVAILABLE(macos(10.5), ios(2.0), watchos(2.0), tvos(9.0))
@interface NSCondition : NSObject <NSLocking>

/// Blocks the current thread until the condition is signaled.
- (void)wait NS_SWIFT_UNAVAILABLE_FROM_ASYNC("Use async-safe scoped locking instead");

/// Blocks the current thread until the condition is signaled or the specified time limit is reached.
- (BOOL)waitUntilDate:(NSDate *)limit NS_SWIFT_UNAVAILABLE_FROM_ASYNC("Use async-safe scoped locking instead");

/// Signals the condition, waking up one waiting thread.
- (void)signal NS_SWIFT_UNAVAILABLE_FROM_ASYNC("Use async-safe scoped locking instead");

/// Signals the condition, waking up all waiting threads.
- (void)broadcast;

/// The name associated with the receiver.
@property (nullable, copy) NSString *name API_AVAILABLE(macos(10.5), ios(2.0), watchos(2.0), tvos(9.0));

@end
#endif 

NS_HEADER_AUDIT_END(nullability, sendability)
