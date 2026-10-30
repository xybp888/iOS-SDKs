/*	NSNotification.h
	Copyright (c) 1994-2019, Apple Inc. All rights reserved.
*/

#import <Foundation/NSObject.h>

/// A structure that defines the name of a notification.
typedef NSString *NSNotificationName NS_TYPED_EXTENSIBLE_ENUM;

@class NSString, NSDictionary, NSOperationQueue;

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

/* ***************	Notifications	****************/

/// A container for information broadcast through a notification center to all registered observers.
///
/// In Swift, this object bridges to ``Notification``; use ``NSNotification`` when you need reference semantics or other Foundation-specific behavior.
///
/// A notification contains a name, an object, and an optional dictionary, and is broadcast to by instances of  ``NotificationCenter`` or ``DistributedNotificationCenter``. The name is a tag identifying the notification. The object is any object that the poster of the notification wants to send to observers of that notification (typically, the object posting the notification). The dictionary stores other related objects, if any. ``NSNotification`` objects are immutable.
///
/// You don't usually create your own notifications directly, but instead call the ``NotificationCenter`` methods ``NotificationCenter/post(name:object:)`` and ``NotificationCenter/post(name:object:userInfo:)``.
///
/// > Important:
/// > The Swift overlay to the Foundation framework provides the ``Notification`` structure, which bridges to the ``NSNotification`` class. For more information about value types, see <doc://com.apple.documentation/documentation/swift/working-with-foundation-types>.
///
///
///
/// ### Object Comparison
///
/// The objects of a notification are compared using pointer equality for local notifications. Distributed notifications use strings as their objects, and those strings are compared using <doc://com.apple.documentation/documentation/objectivec/nsobjectprotocol/isequal(_:)>, because pointer equality doesn't make sense across process boundaries.
///
/// ### Creating Subclasses
///
/// You can subclass ``NSNotification`` to contain information in addition to the notification name, object, and dictionary. This extra data must be agreed upon between notifiers and observers.
///
/// ``NotificationCenter`` is a class cluster with no instance variables. As such, you must subclass ``NSNotification`` and override the primitive methods ``name``, ``object``, and ``userInfo``. You can choose any designated initializer you like, but be sure that your initializer does not call ``init`` on `super` (``NSNotification`` is not meant to be instantiated directly, and its `init` method raises an exception).
@interface NSNotification : NSObject <NSCopying, NSCoding>

/// The name of the notification.
///
/// Typically you use this property to find out what kind of notification you are dealing with when you receive a notification.
///
/// Notification names can be any string. To avoid name collisions, you might want to use a prefix that's specific to your application.
@property (readonly, copy) NSNotificationName name;

/// The object associated with the notification.
///
/// This is often the object that posted this notification. It may be `nil`.
///
/// Typically you use this method to find out what object a notification applies to when you receive a notification.
@property (nullable, readonly, retain) id object;

/// The user information dictionary associated with the notification.
///
/// This may be `nil`. The user information dictionary stores any additional objects that objects receiving the notification might use.
@property (nullable, readonly, copy) NSDictionary *userInfo;

/// Initializes a notification with a specified name, object, and user information.
///
/// - Parameters:
///   - name: The name for the new notification. May not be `nil`.
///   - object: The object for the new notification.
///   - userInfo: The user information dictionary for the new notification. May be `nil`.
- (instancetype)initWithName:(NSNotificationName)name object:(nullable id)object userInfo:(nullable NSDictionary *)userInfo API_AVAILABLE(macos(10.6), ios(4.0), watchos(2.0), tvos(9.0)) NS_DESIGNATED_INITIALIZER;

/// Initializes a notification with the data from an unarchiver.
- (nullable instancetype)initWithCoder:(NSCoder *)coder NS_DESIGNATED_INITIALIZER;
@end

@interface NSNotification (NSNotificationCreation)

/// Returns a new notification object with a specified name and object.
///
/// - Parameters:
///   - aName: The name for the new notification. May not be `nil`.
///   - anObject: The object for the new notification.
+ (instancetype)notificationWithName:(NSNotificationName)aName object:(nullable id)anObject;

/// Returns a notification object with a specified name, object, and user information.
///
/// - Parameters:
///   - aName: The name for the new notification. May not be `nil`.
///   - anObject: The object for the new notification.
///   - aUserInfo: The user information dictionary for the new notification. May be `nil`.
+ (instancetype)notificationWithName:(NSNotificationName)aName object:(nullable id)anObject userInfo:(nullable NSDictionary *)aUserInfo;

/// Initializes an empty notification.
- (instancetype)init /*API_UNAVAILABLE(macos, ios, watchos, tvos)*/;	/* do not invoke; not a valid initializer for this class */

@end

/* ***************	Notification Center	****************/

/// A notification dispatch mechanism that enables the broadcast of information to registered observers.
///
/// Callers register with a notification center to receive one or both of the following:
///
/// * ``NSNotification`` objects, when working in Objective-C or with frameworks that only support ``NSNotification``. Objects register with a notification center to receive notifications (``NSNotification`` objects) using the ``addObserver(_:selector:name:object:)`` or ``addObserver(forName:object:queue:using:)`` methods, specifying a notification name and optionally a source object. When a caller adds itself as an observer, it specifies which notifications it should receive.
///
/// * ``MainActorMessage`` and ``AsyncMessage`` instances for use with Swift code, providing strong typing, appropriate actor isolation, and a more idiomatic Swift experience. Callers register with the notification center using the various flavors of the `addObserver(of:for:using:)` method, specifying either a message type or a convenience ``MessageIdentifier`` to identify the notification messages to receive. See <doc:notification-center-messages> for more information about this API.
///
/// Callers may add observers for many different notifications, or even the same notification name or message type as produced by different source objects.
///
/// Each running app has a ``default`` notification center, and you can create new notification centers to organize communications in particular contexts.
///
/// A notification center can deliver notifications only within a single program. On macOS, if you want to post a notification to other processes or receive notifications from other processes, use ``DistributedNotificationCenter`` instead.
NS_SWIFT_SENDABLE
@interface NSNotificationCenter : NSObject

/// The app's default notification center.
@property (class, readonly, strong) NSNotificationCenter *defaultCenter;

/// Adds an entry to the notification center to call the provided selector
/// with the notification.
///
/// - Parameters:
///   - observer: Object registering as an observer.
///   - aSelector: Selector that specifies the message the receiver sends
///     the observer when posting the notification. The method must have one
///     and only one argument (an instance of `NSNotification`).
///   - aName: The name of the notification for which to register the
///     observer; that is, only notifications with this name are used to add
///     the block to the operation queue. Pass `nil` to receive notifications
///     with any name.
///   - anObject: The object whose notifications the observer wants to
///     receive; that is, only notifications sent by this sender are
///     delivered to the observer. Pass `nil` to receive notifications from
///     any sender.
- (void)addObserver:(id)observer selector:(SEL)aSelector name:(nullable NSNotificationName)aName object:(nullable id)anObject;

/// Posts a given notification to the notification center.
///
/// - Parameter notification: The notification to post.
- (void)postNotification:(NSNotification *)notification;

/// Creates a notification with a given name and sender and posts it to the
/// notification center.
///
/// - Parameters:
///   - aName: The name of the notification.
///   - anObject: The object posting the notification.
- (void)postNotificationName:(NSNotificationName)aName object:(nullable id)anObject;

/// Creates a notification with a given name, sender, and information and
/// posts it to the notification center.
///
/// - Parameters:
///   - aName: The name of the notification.
///   - anObject: The object posting the notification.
///   - aUserInfo: Optional information about the notification.
- (void)postNotificationName:(NSNotificationName)aName object:(nullable id)anObject userInfo:(nullable NSDictionary *)aUserInfo;

/// Removes all entries specifying an observer from the notification
/// center's dispatch table.
///
/// - Parameter observer: The notification observer to remove.
- (void)removeObserver:(id)observer;

/// Removes matching entries from the notification center's dispatch table.
///
/// - Parameters:
///   - observer: The notification observer to remove.
///   - aName: The name of the notification to remove from the dispatch
///     table. Pass `nil` to remove all entries for the observer.
///   - anObject: The sender to remove from the dispatch table. Pass `nil`
///     to remove the observer regardless of the sender.
- (void)removeObserver:(id)observer name:(nullable NSNotificationName)aName object:(nullable id)anObject;

#if !0
/// Adds an entry to the notification center to receive notifications that
/// passed to the provided block.
///
/// - Parameters:
///   - name: The name of the notification for which to register the
///     observer. Pass `nil` to receive notifications with any name.
///   - obj: The object whose notifications the observer wants to receive.
///     Pass `nil` to receive notifications from any sender.
///   - queue: The operation queue to which the block is added. Pass `nil`
///     to run the block synchronously on the posting thread.
///   - block: The block to be executed when the notification is received.
/// - Returns: An opaque object to act as the observer, which you use to
///   deregister the observer with ``removeObserver:``.
- (id <NSObject>)addObserverForName:(nullable NSNotificationName)name object:(nullable id)obj queue:(nullable NSOperationQueue *)queue usingBlock:(void (NS_SWIFT_SENDABLE ^)(NSNotification *notification))block API_AVAILABLE(macos(10.6), ios(4.0), watchos(2.0), tvos(9.0));
#endif

@end

NS_HEADER_AUDIT_END(nullability, sendability)
