//
//  CKNotification.h

//  CloudKit
//
//  Copyright (c) 2014 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

#import <CloudKit/CKDatabase.h>
#import <CloudKit/CKRecord.h>

@class CKRecordID, CKRecordZoneID;

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

/// An object that uniquely identifies a push notification that a container sends.
///
/// You don't create notification IDs directly. The server creates them when it creates instances of ``CKNotification`` that correspond to the push notifications that CloudKit sends to your app. You can compare two IDs using the <doc://com.apple.documentation/documentation/objectivec/nsobjectprotocol/isequal(_:)> method to determine whether two notifications are the same. This class defines no methods or properties.
API_AVAILABLE(macos(10.10), ios(8.0), watchos(3.0))
CK_SUBCLASSING_DEPRECATED // should not be subclassed, or Sendable may no longer apply
// NS_SWIFT_SENDABLE on swift(4.2)
@interface CKNotificationID : NSObject <NSCopying, NSSecureCoding>
@end

/// Constants that indicate the type of event that generates the push notification.
typedef NS_ENUM(NSInteger, CKNotificationType) {
    /// A notification that CloudKit generates from a query subscription's predicate.
    CKNotificationTypeQuery            = 1,

    /// A notification that CloudKit generates when the contents of a record zone change.
    CKNotificationTypeRecordZone       = 2,

    /// A notification that your app marks as read.
    CKNotificationTypeReadNotification = 3,

    /// A notification that CloudKit generates when the contents of a database change.
    CKNotificationTypeDatabase         API_AVAILABLE(macos(10.12), ios(10.0), tvos(10.0), watchos(3.0)) = 4,
} API_AVAILABLE(macos(10.10), ios(8.0), watchos(3.0));

/// The abstract base class for CloudKit notifications.
///
/// Use subclasses of `CKNotification` to extract data from push notifications that the system receives, or to fetch a container's previous push notifications. In both cases, the object indicates the changed data.
///
/// `CKNotification` is an abstract class. When you create a notification from a payload dictionary, the ``init(fromRemoteNotificationDictionary:)`` method returns an instance of the appropriate subclass. Similarly, when you fetch notifications from a container, you receive instances of a concrete subclass. `CKNotification` provides information about the push notification and its method of delivery. Subclasses contain specific data that provides the changes.
///
/// The system delivers notifications with alerts, badges, or sounds via the `UserNotifications` framework, in the form of a `UNNotification`.
///
/// Applications should use the `UserNotifications` framework to interact with the alert, badge, and sound properties of the notification.
///
/// Applications may create a ``CKNotification`` from a `UNNotification` in their `UNUserNotificationCenterDelegate`:
///
/// ```swift
///  func userNotificationCenter(
///      _ center: UNUserNotificationCenter, willPresent notification: UNNotification
///  ) async -> UNNotificationPresentationOptions {
///     let ckNotification = CKNotification(fromRemoteNotificationDictionary: notification.request.content.userInfo)
/// }
///```
///
/// Notifications without alerts, badges, or sounds are delivered via an application delegate, in the form of a remote notification.
///
/// For example: `UIApplicationDelegate.application(_:didReceiveRemoteNotification:) async`
///
/// Applications may create a ``CKNotification`` from the remote notification in their `UIApplicationDelegate`:
///
/// ```swift
/// func application(
///     _ application: UIApplication, didReceiveRemoteNotification userInfo: [AnyHashable : Any]
/// ) async -> UIBackgroundFetchResult {
///     let ckNotification = CKNotification(fromRemoteNotificationDictionary: userInfo)
/// }
/// ```
API_AVAILABLE(macos(10.10), ios(8.0), watchos(3.0))
// This class should not be subclassed. If it is, Sendable may no longer apply.
NS_SWIFT_SENDABLE
@interface CKNotification : NSObject

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

/// Creates a new notification using the specified payload data.
///
/// - Parameters:
///   - notificationDictionary: The push notification's payload data. Use the dictionary that the system provides to your app delegate's <doc://com.apple.documentation/documentation/uikit/uiapplicationdelegate/application(_:didreceiveremotenotification:fetchcompletionhandler:)> method. This parameter must not be `nil`.
+ (nullable instancetype)notificationFromRemoteNotificationDictionary:(NSDictionary *)notificationDictionary;

/// The type of event that generates the notification.
///
/// Different notification types correspond to different subclasses of ``CKNotification``, so you can use the value in this property to determine how to handle the notification data.
@property (readonly, assign, nonatomic) CKNotificationType notificationType;

/// The notification's ID.
///
/// Use this property to differentiate notifications.
@property (nullable, readonly, copy, nonatomic) CKNotificationID *notificationID;

/// The ID of the container with the content that triggers the notification.
///
/// Use this property to determine the location of the changed content.
@property (nullable, readonly, copy, nonatomic) NSString *containerIdentifier;

/// The ID of the user record that creates the subscription that generates the push notification.
///
/// On a system that supports multiple users, such as tvOS, use this identifier to check whether the pending content is for the current user. If your app always fetches data from CloudKit on launch, you may improve efficiency by disregarding notifications for other users.
///
/// For more information about supporting a multiuser environment, see <doc://com.apple.documentation/documentation/tvservices/personalizing-your-app-for-each-user-on-apple-tv>.
@property (nullable, readonly, copy, nonatomic) CKRecordID *subscriptionOwnerUserRecordID API_AVAILABLE(macos(10.15), ios(13.0), tvos(13.0), watchos(6.0));

/// A Boolean value that indicates whether the system removes some push notification content before delivery.
///
/// The server may truncate the payload data of a push notification if the size of that data exceeds the allowed maximum. For notifications you create using a payload dictionary, the value of this property is <doc://com.apple.documentation/documentation/swift/true> if the payload data doesn't contain all information regarding the change. The value is <doc://com.apple.documentation/documentation/swift/false> if the payload data is complete.
///
/// For notifications you fetch from the database using a `CKFetchNotificationChangesOperation` operation, this property's value is always <doc://com.apple.documentation/documentation/swift/true>.
///
/// When CloudKit must remove payload data, it removes it in a specific order. This class's properties are among the last that CloudKit removes because they define information about how to deliver the push notification. The following list shows the properties that CloudKit removes, and the order for removing them:
///
/// 1. ``CKNotification/containerIdentifier``
/// 2. Keys that subclasses of `CKNotification` define.
/// 3. ``CKNotification/soundName``
/// 4. ``CKNotification/alertLaunchImage``
/// 5. ``CKNotification/alertActionLocalizationKey``
/// 6. ``CKNotification/alertBody``
/// 7. ``CKNotification/alertLocalizationArgs``
/// 8. ``CKNotification/alertLocalizationKey``
/// 9. ``CKNotification/badge``
/// 10. ``CKNotification/notificationID``
@property (readonly, assign, nonatomic) BOOL isPruned;

/// The ID of the subscription that triggers the notification.
@property (nullable, readonly, copy, nonatomic) CKSubscriptionID subscriptionID API_AVAILABLE(macos(10.11), ios(9.0), watchos(3.0));

@end

API_DEPRECATED_BEGIN("Interact with UI elements of a CloudKit-server-generated push message via UserNotifications.framework", macos(10.10, 14.0), ios(8.0, 17.0), tvos(9.0, 17.0), watchos(3.0, 10.0))
@interface CKNotification (DeprecatedAPSProperties)

/// The notification's alert body.
///
/// This property contains the nonlocalized text that the notification's alert displays.
@property (nullable, readonly, copy, nonatomic) NSString *alertBody __TVOS_PROHIBITED;

/// The key that identifies the localized text for the alert body.
///
/// When the system delivers a push notification to your app, it gets the text for the alert body by looking up the specified key in your app's `Localizable.strings` file. CloudKit ignores the value in ``CKNotification/alertBody`` if you set this property.
@property (nullable, readonly, copy, nonatomic) NSString *alertLocalizationKey __TVOS_PROHIBITED;

/// The fields for building a notification's alert.
///
/// This property is an array of field names that CloudKit uses to extract the corresponding values from the record that triggers the push notification. The values are strings, numbers, or dates. CloudKit may truncate strings with a length greater than 100 characters when it adds them to a notification's payload.
///
/// If you use `%@` for your substitution variables, CloudKit replaces those variables by traversing the array in order. If you use variables of the form `%n$@`, where `n` is an integer, `n` represents the index (starting at 1) of the item in the array to use. So, the first item in the array replaces the variable `%1$@`, the second item replaces the variable `%2$@`, and so on. You can use indexed substitution variables to change the order of items in the resulting string, which might be necessary when you localize your app's content.
@property (nullable, readonly, copy, nonatomic) NSArray<NSString *> *alertLocalizationArgs __TVOS_PROHIBITED;

/// The notification's title.
///
/// The system ignores this property if ``CKNotification/titleLocalizationKey`` has a value.
@property (nullable, readonly, copy, nonatomic) NSString *title __TVOS_PROHIBITED API_AVAILABLE(macos(10.13), ios(11.0), watchos(4.0));

/// The key that identifies the localized string for the notification's title.
///
/// This property takes precedence over ``CKNotification/title``.
@property (nullable, readonly, copy, nonatomic) NSString *titleLocalizationKey __TVOS_PROHIBITED API_AVAILABLE(macos(10.13), ios(11.0), watchos(4.0));

/// The fields for building a notification's title.
///
/// This property is an array of field names that CloudKit uses to extract the corresponding values from the record that triggers the push notification. The values are strings, numbers, or dates. CloudKit may truncate strings with a length greater than 100 characters when it adds them to a notification's payload.
///
/// If you use `%@` for your substitution variables, CloudKit replaces those variables by traversing the array in order. If you use variables of the form `%n$@`, where `n` is an integer, `n` represents the index (starting at 1) of the item in the array to use. So, the first item in the array replaces the variable `%1$@`, the second item replaces the variable `%2$@`, and so on. You can use indexed substitution variables to change the order of items in the resulting string, which might be necessary when you localize your app's content.
@property (nullable, readonly, copy, nonatomic) NSArray<NSString *> *titleLocalizationArgs __TVOS_PROHIBITED API_AVAILABLE(macos(10.13), ios(11.0), watchos(4.0));

/// The notification's subtitle.
///
/// The system ignores this property if ``CKNotification/subtitleLocalizationKey`` has a value.
@property (nullable, readonly, copy, nonatomic) NSString *subtitle __TVOS_PROHIBITED API_AVAILABLE(macos(10.13), ios(11.0), watchos(4.0));

/// The key that identifies the localized string for the notification's subtitle.
///
/// This property takes precedence over ``CKNotification/subtitle``.
@property (nullable, readonly, copy, nonatomic) NSString *subtitleLocalizationKey __TVOS_PROHIBITED API_AVAILABLE(macos(10.13), ios(11.0), watchos(4.0));

/// The fields for building a notification's subtitle.
///
/// This property is an array of field names that CloudKit uses to extract the corresponding values from the record that triggers the push notification. The values are strings, numbers, or dates. CloudKit may truncate strings with a length greater than 100 characters when it adds them to a notification's payload.
///
/// If you use `%@` for your substitution variables, CloudKit replaces those variables by traversing the array in order. If you use variables of the form `%n$@`, where `n` is an integer, `n` represents the index (starting at 1) of the item in the array to use. So, the first item in the array replaces the variable `%1$@`, the second item replaces the variable `%2$@`, and so on. You can use indexed substitution variables to change the order of items in the resulting string, which might be necessary when you localize your app's content.
@property (nullable, readonly, copy, nonatomic) NSArray<NSString *> *subtitleLocalizationArgs __TVOS_PROHIBITED API_AVAILABLE(macos(10.13), ios(11.0), watchos(4.0));

/// The key that identifies the localized string for the notification's action.
///
/// The system uses this property's value to find the matching string in your app's `Localizable.strings` file. It uses the string as the text of the button that opens your app, which the notification alert displays.
///
/// If this property's value is `nil`, the system displays a single button to dismiss the alert.
@property (nullable, readonly, copy, nonatomic) NSString *alertActionLocalizationKey __TVOS_PROHIBITED;

/// The filename of an image to use as a launch image.
///
/// The system uses this property's value to locate an image in the app's bundle, and displays it as a launch image when the user launches the app after receiving a push notification.
@property (nullable, readonly, copy, nonatomic) NSString *alertLaunchImage __TVOS_PROHIBITED;

/// The value that the app icon's badge displays.
@property (nullable, readonly, copy, nonatomic) NSNumber *badge API_AVAILABLE(tvos(10.0));

/// The name of the sound file to play when a notification arrives.
///
/// The system uses this property's value to locate a sound file in the app's bundle. The sound plays when the system receives a push notification. If the system can't find the specified file, or if the property's value is the string `default`, the system plays the default sound.
@property (nullable, readonly, copy, nonatomic) NSString *soundName __TVOS_PROHIBITED;

/// The name of the action group that corresponds to this notification.
///
/// Categories allow you to present custom actions to the user on your push notifications. For more information, see <doc://com.apple.documentation/documentation/uikit/uimutableusernotificationcategory>.
@property (nullable, readonly, copy, nonatomic) NSString *category __TVOS_PROHIBITED API_AVAILABLE(macos(10.11), ios(9.0), watchos(3.0));

@end
API_DEPRECATED_END // macos(10.10, 14.0), ios(8.0, 17.0), tvos(9.0, 17.0), watchos(3.0, 10.0))

/// Constants that indicate the event that triggers the notification.
typedef NS_ENUM(NSInteger, CKQueryNotificationReason) {
    /// A notification that indicates the creation of a record matching the subscription's predicate.
    CKQueryNotificationReasonRecordCreated = 1,

    /// A notification that indicates the update of a record matching the subscription's predicate.
    CKQueryNotificationReasonRecordUpdated,

    /// A notification that indicates the deletion of a record matching the subscription's predicate.
    CKQueryNotificationReasonRecordDeleted,
} API_AVAILABLE(macos(10.10), ios(8.0), watchos(3.0));

/// A notification that triggers when a record that matches the subscription's predicate changes.
///
/// Query subscriptions execute when a record that matches the subscription's predicate changes, for example, when the user modifies a field's value in the record. When CloudKit registers the change, it sends push notifications to the user's devices to inform your app about the change. You can then fetch the changes and cache them on-device. When appropriate, CloudKit excludes the device where the change originates.
///
/// You configure a subscription's notifications by setting its ``CKSubscription/notificationInfo`` property. Do this before you save it to the server. A subscription generates either high-priority or medium-priority push notifications. CloudKit delivers medium-priority notifications to your app in the background. High-priority notifications are visual and the system displays them to the user. Visual notifications need the user's permission. For more information, see <doc://com.apple.documentation/documentation/usernotifications/asking-permission-to-use-notifications>.
///
/// A subscription uses ``CKSubscription/NotificationInfo`` to configure its notifications. For background delivery, set only its ``CKSubscription/NotificationInfo/shouldSendContentAvailable`` property to <doc://com.apple.documentation/documentation/swift/true>. If you set any other property, CloudKit treats the notification as high-priority.
///
/// - Note: To receive silent push notifications, add the Background Modes capability to your Xcode project, and select the "Background fetch" and "Remote notifications" options.
///
/// Don't rely on push notifications for changes because the system can coalesce them. CloudKit can omit data to keep the notification's payload size under the APNs size limit. If you use ``CKSubscription/NotificationInfo/desiredKeys`` to include extra data in the payload, the server removes that first. A notification's ``CKNotification/isPruned`` property is <doc://com.apple.documentation/documentation/swift/true> if CloudKit omits data.
///
/// Consider notifications an indication of remote changes. Use ``CKDatabaseNotification/databaseScope`` to determine which database contains the changed record. To fetch the changes, configure an instance of ``CKQueryOperation`` to match the subscription and then execute it in the database. CloudKit returns all records that match the predicate, including the changed record. Dispose of any records you cache on-device and use the operation's results instead.
///
/// You don't instantiate this class. Instead, implement <doc://com.apple.documentation/documentation/uikit/uiapplicationdelegate/application(_:didreceiveremotenotification:fetchcompletionhandler:)> in your app delegate. Initialize ``CKNotification`` with the `userInfo` dictionary that CloudKit passes to the method. This returns an instance of the appropriate subclass. Use the ``CKNotification/notificationType`` property to determine the type. Then cast to that type to access type-specific properties and methods.
API_AVAILABLE(macos(10.10), ios(8.0), watchos(3.0))
CK_SUBCLASSING_DEPRECATED // should not be subclassed, or Sendable may no longer apply
NS_SWIFT_SENDABLE
@interface CKQueryNotification : CKNotification

/// The event that triggers the push notification.
///
/// Subscription notifications result from the creation, deletion, or updating of a single record. The record in question must match the subscription's predicate for an event to trigger.
@property (readonly, assign, nonatomic) CKQueryNotificationReason queryNotificationReason;

/// A dictionary of fields that have changes.
///
/// For record updates and creations, this property contains the subscription's desired keys. When you configure the notification info of a subscription, you specify the names of one or more fields in the ``CKSubscription/NotificationInfo/desiredKeys`` property. When a push notification triggers, CloudKit retrieves the values for each of those keys from the record and includes them in the notification's payload.
///
/// For query notifications that you fetch from a container, all keys and values are present. For query notifications that you create from push notifications, one or more keys and values may be missing. Push notification payloads have a size limit, and CloudKit can exclude record fields when a payload exceeds that limit. For information about the order, see the overview of this class.
@property (nullable, readonly, copy, nonatomic) NSDictionary<NSString *, id> *recordFields;

/// The ID of the record that CloudKit creates, updates, or deletes.
///
/// Use this value to fetch the record.
@property (nullable, readonly, copy, nonatomic) CKRecordID *recordID;

/// The type of database for the record zone.
///
/// This property's value is one of the constants that ``CKDatabase/Scope`` defines.
@property (readonly, assign, nonatomic) CKDatabaseScope databaseScope API_AVAILABLE(macos(10.12), ios(10.0), tvos(10.0), watchos(3.0));

@end


/// A notification that triggers when the contents of a record zone change.
///
/// A record zone subscription executes when a user, or in certain scenarios, CloudKit, modifies a record in that zone, for example, when a field's value changes in a record. When CloudKit registers the change, it sends push notifications to the user's devices to inform your app about the change. You can then fetch the changes and cache them on-device. When appropriate, CloudKit excludes the device where the change originates.
///
/// You configure a subscription's notifications by setting its ``CKSubscription/notificationInfo`` property. Do this before you save it to the server. A subscription generates either high-priority or medium-priority push notifications. CloudKit delivers medium-priority notifications to your app in the background. High-priority notifications are visual and the system displays them to the user. Visual notifications need the user's permission. For more information, see <doc://com.apple.documentation/documentation/usernotifications/asking-permission-to-use-notifications>.
///
/// A subscription uses ``CKSubscription/NotificationInfo`` to configure its notifications. For background delivery, set only its ``CKSubscription/NotificationInfo/shouldSendContentAvailable`` property to <doc://com.apple.documentation/documentation/swift/true>. If you set any other property, CloudKit treats the notification as high-priority.
///
/// - Note: To receive silent push notifications, add the Background Modes capability to your Xcode project, and select the "Background fetch" and "Remote notifications" options.
///
/// Don't rely on push notifications for specific changes to records because the system can coalesce them. CloudKit can omit data to keep the notification's payload size under the APNs size limit. Consider notifications an indication of remote changes. Use ``databaseScope`` to determine which database contains the changed record zone, and ``recordZoneID`` to determine which zone contains changed records. You can then fetch just those changes using ``CKFetchRecordZoneChangesOperation``. A notification's ``CKNotification/isPruned`` property is <doc://com.apple.documentation/documentation/swift/true> if CloudKit omits data.
///
/// You don't instantiate this class. Instead, implement <doc://com.apple.documentation/documentation/uikit/uiapplicationdelegate/application(_:didreceiveremotenotification:fetchcompletionhandler:)> in your app delegate. Initialize ``CKNotification`` with the `userInfo` dictionary that CloudKit passes to the method. This returns an instance of the appropriate subclass. Use the ``CKNotification/notificationType`` property to determine the type. Then cast to that type to access type-specific properties and methods.
API_AVAILABLE(macos(10.10), ios(8.0), watchos(3.0))
CK_SUBCLASSING_DEPRECATED // should not be subclassed, or Sendable may no longer apply
NS_SWIFT_SENDABLE
@interface CKRecordZoneNotification : CKNotification

/// The ID of the record zone that has changes.
@property (nullable, readonly, copy, nonatomic) CKRecordZoneID *recordZoneID;

/// The type of database for the record zone.
///
/// This property's value is one of the constants that ``CKDatabase/Scope`` defines.
@property (readonly, assign, nonatomic) CKDatabaseScope databaseScope API_AVAILABLE(macos(10.12), ios(10.0), tvos(10.0), watchos(3.0));

@end


/// A notification that triggers when the contents of a database change.
///
/// Database subscriptions execute when changes happen in any of a database's record zones, for example, when CloudKit saves a new record. When the subscription registers a change, it sends push notifications to the user's devices to inform your app about the change. You can then fetch the changes and cache them on-device. When appropriate, CloudKit excludes the device where the change originates.
///
/// You configure a subscription's notifications by setting its ``CKSubscription/notificationInfo`` property. Do this before you save it to the server. A subscription generates either high-priority or medium-priority push notifications. CloudKit delivers medium-priority notifications to your app in the background. High-priority notifications are visual and the system displays them to the user. Visual notifications need the user's permission. For more information, see <doc://com.apple.documentation/documentation/usernotifications/asking-permission-to-use-notifications>.
///
/// A subscription uses ``CKSubscription/NotificationInfo`` to configure its notifications. For background delivery, set only its ``CKSubscription/NotificationInfo/shouldSendContentAvailable`` property to <doc://com.apple.documentation/documentation/swift/true>. If you set any other property, CloudKit treats the notification as high-priority.
///
/// - Note: To receive silent push notifications, add the Background Modes capability to your Xcode project, and select the "Background fetch" and "Remote notifications" options.
///
/// Don't rely on push notifications for specific changes because the system can coalesce them. CloudKit can omit data to keep the notification's payload size under the APNs size limit. Consider notifications an indication of remote changes. Use ``databaseScope`` to determine which database has changes, and then ``CKFetchDatabaseChangesOperation`` to fetch those changes. A notification's ``CKNotification/isPruned`` property is <doc://com.apple.documentation/documentation/swift/true> if CloudKit omits data.
///
/// You don't instantiate this class. Instead, implement <doc://com.apple.documentation/documentation/uikit/uiapplicationdelegate/application(_:didreceiveremotenotification:fetchcompletionhandler:)> in your app delegate. Initialize ``CKNotification`` with the `userInfo` dictionary that CloudKit passes to the method. This returns an instance of the appropriate subclass. Use the ``CKNotification/notificationType`` property to determine the type. Then cast to that type to access type-specific properties and methods.
API_AVAILABLE(macos(10.12), ios(10.0), tvos(10.0), watchos(3.0))
CK_SUBCLASSING_DEPRECATED // should not be subclassed, or Sendable may no longer apply
NS_SWIFT_SENDABLE
@interface CKDatabaseNotification : CKNotification

/// The type of database.
///
/// This property's value is one of the constants that ``CKDatabase/Scope`` defines.
@property (readonly, assign, nonatomic) CKDatabaseScope databaseScope;

@end

NS_HEADER_AUDIT_END(nullability, sendability)
