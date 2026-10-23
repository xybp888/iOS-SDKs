/*	NSNotificationQueue.h
	Copyright (c) 1994-2019, Apple Inc. All rights reserved.
*/

#import <Foundation/NSObject.h>
#import <Foundation/NSRunLoop.h>

@class NSNotification, NSNotificationCenter, NSArray<ObjectType>, NSString;

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

/// The constants that specify when notifications are posted.
///
/// These constants are used by the ``NotificationQueue/enqueue(_:postingStyle:)`` and ``NotificationQueue/enqueue(_:postingStyle:coalesceMask:forModes:)`` methods.
typedef NS_ENUM(NSUInteger, NSPostingStyle) {
    /// The notification is posted at the end of the current notification callout or timer.
    NSPostWhenIdle = 1,
    /// The notification is posted at the end of the current event processing cycle.
    NSPostASAP = 2,
    /// The notification is posted immediately after coalescing.
    NSPostNow = 3
};

/// The constants that specify how notifications are coalesced.
///
/// These constants are used by the ``NotificationQueue/enqueue(_:postingStyle:coalesceMask:forModes:)`` method.
typedef NS_OPTIONS(NSUInteger, NSNotificationCoalescing) {
    /// Do not coalesce notifications in the queue.
    NSNotificationNoCoalescing = 0,
    /// Coalesce notifications with the same name.
    NSNotificationCoalescingOnName = 1,
    /// Coalesce notifications with the same object (sender).
    NSNotificationCoalescingOnSender = 2
};

/// A notification center buffer.
///
/// Whereas a notification center distributes notifications when posted, notifications placed into the queue can be delayed until the end of the current pass through the run loop or until the run loop is idle. Duplicate notifications can be coalesced so that only one notification is sent although multiple notifications are posted.
///
/// A notification queue maintains notifications in first in, first out (FIFO) order. When a notification moves to the front of the queue, the queue posts it to the notification center, which in turn dispatches the notification to all objects registered as observers.
///
/// Every thread has a default notification queue, which is associated with the default notification center for the process. You can create your own notification queues and have multiple queues per center and thread.
@interface NSNotificationQueue : NSObject

/// Returns the default notification queue for the current thread.
///
/// This notification queue uses the default notification center.
@property (class, readonly, strong) NSNotificationQueue *defaultQueue;

/// Initializes and returns a notification queue for the specified notification center.
- (instancetype)initWithNotificationCenter:(NSNotificationCenter *)notificationCenter NS_DESIGNATED_INITIALIZER;

/// Adds a notification to the notification queue with a specified posting style.
- (void)enqueueNotification:(NSNotification *)notification postingStyle:(NSPostingStyle)postingStyle;

/// Adds a notification to the notification queue with a specified posting style, criteria for coalescing, and run loop mode.
///
/// The notification queue will only post the notification to its notification center if the run loop is in one of the modes provided in the array. The modes parameter may be nil, in which case it defaults to NSDefaultRunLoopMode.
- (void)enqueueNotification:(NSNotification *)notification postingStyle:(NSPostingStyle)postingStyle coalesceMask:(NSNotificationCoalescing)coalesceMask forModes:(nullable NSArray<NSRunLoopMode> *)modes;

/// Removes all notifications from the queue that match a provided notification using provided matching criteria.
- (void)dequeueNotificationsMatching:(NSNotification *)notification coalesceMask:(NSUInteger)coalesceMask;

@end

NS_HEADER_AUDIT_END(nullability, sendability)
