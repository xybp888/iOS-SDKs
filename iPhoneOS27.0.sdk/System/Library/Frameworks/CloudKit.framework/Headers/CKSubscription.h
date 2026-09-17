//
//  CKSubscription.h
//  CloudKit
//
//  Copyright (c) 2014 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

#import <CloudKit/CKDefines.h>
#import <CloudKit/CKRecord.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

/// Constants that identify a subscription's behavior.
typedef NS_ENUM(NSInteger, CKSubscriptionType) {
    /// A constant that indicates the subscription is query-based.
    CKSubscriptionTypeQuery                                     = 1,

    /// A constant that indicates the subscription is zone-based.
    CKSubscriptionTypeRecordZone                                = 2,

    /// A constant that indicates the subscription is database-based.
    CKSubscriptionTypeDatabase API_AVAILABLE(macos(10.12), ios(10.0), tvos(10.0), watchos(3.0))   = 3,
} API_AVAILABLE(macos(10.10), ios(8.0), watchos(6.0));

@class CKNotificationInfo, CKRecordZoneID;

/// A type that represents a subscription's identifier.
typedef NSString *CKSubscriptionID;

/// An abstract base class for subscriptions.
///
/// A subscription acts like a persistent query on the server that can track the creation, deletion, and modification of records. When changes occur, they trigger the delivery of push notifications so that your app can respond appropriately.
///
/// Subscriptions don't become active until you save them to the server and the server has time to index them. To save a subscription, use an instance of ``CKModifySubscriptionsOperation`` or the ``CKDatabase/save(_:completionHandler:)-9pona`` method of ``CKDatabase``. To cancel a subscription, delete the corresponding subscription from the server.
///
/// - Note: You don't need to enable push notifications for the app's explicit App ID in your developer account at [developer.apple.com](https://developer.apple.com) to receive subscription notifications. Xcode automatically adds the APNs entitlement to your entitlement file when you enable CloudKit. To learn about enabling CloudKit, see [Enabling CloudKit in Your App](https://developer.apple.com/library/archive/documentation/DataManagement/Conceptual/CloudKitQuickStart/EnablingiCloudandConfiguringCloudKit/EnablingiCloudandConfiguringCloudKit.html#//apple_ref/doc/uid/TP40014987-CH2).
///
/// Most of a subscription's configuration happens at initialization time. You must, however, specify how to deliver push notifications to the user's device. Use the ``notificationInfo`` property to configure the delivery options. You must save the subscription before the changes take effect.
///
/// - Note: Create subscriptions in the development environment first and then promote them to production. Attempting to create a subscription directly in the production environment results in an error.
///
/// ### Handling the Resulting Push Notifications
///
/// When CloudKit modifies a record and triggers a subscription, the server sends push notifications to all devices with that subscription except for the one that makes the original changes. For subscription-based push notifications, the server can add data to the notification payload that indicates the condition that triggers the notification. In the <doc://com.apple.documentation/documentation/uikit/uiapplicationdelegate/application(_:didreceiveremotenotification:fetchcompletionhandler:)> method of your app delegate, create a ``CKNotification`` object from the provided `userInfo` dictionary. You can then query it for the information that's relevant to the notification.
///
/// In addition to sending a record ID with a push notification, you can ask the server to send a limited amount of data from the record that triggers the notification. Use the ``NotificationInfo/desiredKeys`` property of the object you assign to ``notificationInfo`` to specify the keys to include.
///
/// APNs limits the size of a push notification's payload and CloudKit may omit keys and other pieces of data to keep the payload's size under that limit. If this happens, you can fetch the entire payload from the server using an instance of `CKFetchNotificationChangesOperation`. This operation provides instances of ``CKQueryNotification`` or ``CKRecordZoneNotification``, which contain information about the push notifications that CloudKit delivers to your app.
API_AVAILABLE(macos(10.10), ios(8.0), watchos(3.0))
// This class should not be subclassed. If it is, Sendable may no longer apply.
// NS_SWIFT_SENDABLE on macos(14.0), ios(17.0), tvos(17.0), watchos(10.0)
@interface CKSubscription : NSObject <NSSecureCoding, NSCopying>

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

/// The subscription's unique identifier.
///
/// This property's value is the subscription ID that you provide to the `initWithRecordType:predicate:subscriptionID:options:` or `initWithZoneID:subscriptionID:options:` methods when you create the subscription. If you use a different method to create the subscription, CloudKit automatically assigns a UUID as the subscription ID.
@property (readonly, copy) CKSubscriptionID subscriptionID API_AVAILABLE(watchos(6.0));

/// The behavior that a subscription provides.
@property (readonly, assign) CKSubscriptionType subscriptionType API_AVAILABLE(watchos(6.0));

/// The configuration for a subscription's push notifications.
///
/// If you want the system to display your subscription's push notifications, assign a value to this property. The server uses the configuration you provide to determine the delivery options for notifications. For example, you can specify the text to display to the user, and the sound to play. You can also specify which fields of the record to include in the notification's payload.
///
/// If you don't assign a value to this property, CloudKit still sends push notifications, but the system doesn't display them to the user. The default value of this property is `nil`.
@property (nullable, copy) CKNotificationInfo *notificationInfo API_AVAILABLE(watchos(6.0));

@end


/// Configuration options for a query subscription.
typedef NS_OPTIONS(NSUInteger, CKQuerySubscriptionOptions) {
    /// An option that instructs CloudKit to send a push notification when it creates a record that matches a subscription's criteria.
    CKQuerySubscriptionOptionsFiresOnRecordCreation     = 1 << 0,

    /// An option that instructs CloudKit to send a push notification when it modifies a record that matches a subscription's criteria.
    CKQuerySubscriptionOptionsFiresOnRecordUpdate       = 1 << 1,

    /// An option that instructs CloudKit to send a push notification when it deletes a record that matches a subscription's criteria.
    CKQuerySubscriptionOptionsFiresOnRecordDeletion     = 1 << 2,

    /// An option that instructs CloudKit to send a push notification only once.
    ///
    /// You combine this option with one or more of the other subscription options. This option applies only to query-based subscriptions. CloudKit deletes the subscription after it sends the push notification. If you want to generate subsequent push notifications using the same criteria, create and save a new subscription.
    CKQuerySubscriptionOptionsFiresOnce                 = 1 << 3,
} API_AVAILABLE(macos(10.12), ios(10.0), tvos(10.0), watchos(6.0));

/// A subscription that generates push notifications when CloudKit modifies records that match a predicate.
///
/// Subscriptions track the creation, modification, and deletion of records in a database, and are fundamental in keeping data on the user's device up to date. A subscription applies only to the user that creates it. When a subscription registers a change, such as CloudKit saving a new record, it sends push notifications to the user's devices to inform your app about the change. You can then fetch the changes and cache them on-device. When appropriate, the server excludes the device where the change originates.
///
/// - Note: You don't need to explicitly enable push notifications for your App ID to receive subscription notifications. Xcode automatically adds the entitlement when you enable the CloudKit capability. For more information, see <doc:enabling-cloudkit-in-your-app>. To use silent push notifications, add the Background Modes capability in your Xcode project and then select the "Background fetch" and "Remote notifications" options.
///
/// Query subscriptions execute whenever a change occurs in a database that matches the predicate and options you specify. You scope a query subscription to an individual record type that you provide during initialization. You can set the subscription's ``zoneID`` property to further specialize the subscription to a specific record zone in the database. This limits the scope of the subscription to only track changes in that record zone and reduces the number of notifications it generates. For more information about defining CloudKit-compatible predicates, see ``CKQuery``.
///
/// - Note: Only public and private databases support query subscriptions. If you attempt to save a database subscription in the shared database, CloudKit returns an error.
///
/// Create any subscriptions on your app's first launch. After you initialize a subscription, save it to the server using ``CKModifySubscriptionsOperation``. When the operation completes, record that state on-device (in <doc://com.apple.documentation/documentation/foundation/userdefaults>, for example). You can then check that state on subsequent launches to prevent unnecessary trips to the server.
///
/// To configure the notification the subscription generates, set the subscription's ``CKSubscription/notificationInfo`` property. Because the system coalesces notifications, don't rely on them for specific changes. CloudKit can omit data to keep the payload size under the APNs size limit. Consider notifications an indication of remote changes and use ``CKQueryOperation`` to fetch the changed records. Create the operation with an instance of ``CKQuery`` that you configure with the same record type and predicate as the subscription. If you limit the subscription to a specific record zone, set the operation's ``CKQueryOperation/zoneID`` property to that record zone's ID. Because ``CKQueryOperation`` doesn't employ server change tokens, dispose of any records you cache on-device and use the query's results instead.
///
/// The example below shows how to create a query subscription in the user's private database, configure the notifications it generates — in this case, silent push notifications — and then save that subscription to the server:
///
/// ```objc
/// // Only proceed if the subscription doesn't already exist.
/// if([[NSUserDefaults standardUserDefaults]
///     boolForKey:@"didCreateQuerySubscription"] == NO) {
///
/// // Define a predicate that matches records with a tags field
/// // that contains the word 'Swift'.
/// NSPredicate *predicate = [NSPredicate predicateWithFormat:
///                           @"tags CONTAINS 'Swift'"];
///
/// // Create a subscription and scope it to the 'FeedItem' record type.
/// // Provide a unique identifier for the subscription and declare the
/// // circumstances for invoking it.
/// CKQuerySubscriptionOptions options =
///     CKQuerySubscriptionOptionsFiresOnRecordCreation;
/// CKQuerySubscription *subscription = [[CKQuerySubscription alloc]
///                                      initWithRecordType:@"FeedItem"
///                                      predicate:predicate
///                                      subscriptionID:@"tagged-feed-changes"
///                                      options:options];
///
/// // Further specialize the subscription to only evaluate
/// // records in a specific record zone
/// subscription.zoneID = recordZone.zoneID;
///
/// // Configure the notification so that the system delivers it silently
/// // and, therefore, doesn't require permission from the user.
/// CKNotificationInfo *notificationInfo = [CKNotificationInfo new];
/// notificationInfo.shouldSendContentAvailable = YES;
/// subscription.notificationInfo = notificationInfo;
///
/// // Create an operation that saves the subscription to the server.
/// CKModifySubscriptionsOperation *operation =
///     [[CKModifySubscriptionsOperation alloc]
///      initWithSubscriptionsToSave:@[subscription]
///      subscriptionIDsToDelete:NULL];
///
/// operation.modifySubscriptionsCompletionBlock =
///     ^(NSArray *subscriptions, NSArray *deleted, NSError *error) {
///     if (error) {
///         // Handle the error.
///     } else {
///         // Record that the system successfully creates the subscription
///         // to prevent unnecessary trips to the server in later launches.
///         [[NSUserDefaults standardUserDefaults]
///          setBool:YES forKey:@"didCreateQuerySubscription"];
///     }
/// };
///
/// // Set an appropriate QoS and add the operation to the private
/// // database's operation queue to execute it.
/// operation.qualityOfService = NSQualityOfServiceUtility;
/// [CKContainer.defaultContainer.privateCloudDatabase addOperation:operation];
/// ```
API_AVAILABLE(macos(10.12), ios(10.0), tvos(10.0), watchos(6.0))
CK_SUBCLASSING_DEPRECATED // should not be subclassed, or Sendable may no longer apply
// NS_SWIFT_SENDABLE on macos(14.0), ios(17.0), tvos(17.0), watchos(10.0)
@interface CKQuerySubscription : CKSubscription <NSSecureCoding, NSCopying>

/// Creates a query-based subscription that queries records of a specific type.
///
/// - Parameters:
///   - recordType: The record's type. You're responsible for defining your app's record types. This parameter must not be `nil` or an empty string.
///   - predicate: The predicate that identifies the records for inclusion in the subscription. This parameter must not be `nil`. For information about the operators that predicates support, see the discussion in ``CKQuery``.
///   - querySubscriptionOptions: A bitmask of configuration options. See ``CKQuerySubscription/Options`` for more information.
///
/// The subscription that this method returns is a query-based subscription with a scope that includes all of the user's record zones. When CloudKit modifies a record that matches the specified type and predicate, it uses `querySubscriptionOptions` to determine whether to send a push notification.
- (instancetype)initWithRecordType:(CKRecordType)recordType predicate:(NSPredicate *)predicate options:(CKQuerySubscriptionOptions)querySubscriptionOptions API_DEPRECATED_WITH_REPLACEMENT("initWithRecordType:predicate:subscriptionID:options:", macos(10.12, 10.12), ios(10.0, 10.0), tvos(10.0, 10.0), watchos(6.0, 6.0));

/// Creates a named query-based subscription that queries records of a specific type.
///
/// - Parameters:
///   - recordType: The record's type. You're responsible for defining your app's record types. This parameter must not be `nil` or an empty string.
///   - predicate: The predicate that identifies the records for inclusion in the subscription. This parameter must not be `nil`. For information about the operators that predicates support, see the discussion in ``CKQuery``.
///   - subscriptionID: The subscription's name. You should provide a value that is unique in the target database, and you may not provide `nil` or an empty string.
///   - querySubscriptionOptions: A bitmask of configuration options. See ``CKQuerySubscription/Options`` for more information.
///
/// The subscription that this method returns is a query-based subscription with a scope that includes all of the user's record zones. When CloudKit modifies a record that matches the specified type and predicate, it uses `querySubscriptionOptions` to determine whether to send a push notification.
- (instancetype)initWithRecordType:(CKRecordType)recordType predicate:(NSPredicate *)predicate subscriptionID:(CKSubscriptionID)subscriptionID options:(CKQuerySubscriptionOptions)querySubscriptionOptions NS_DESIGNATED_INITIALIZER;

/// Creates a query-based subscription from a serialized instance.
///
/// - Parameters:
///   - aDecoder: The coder for decoding the serialized query subscription.
- (instancetype)initWithCoder:(NSCoder *)aDecoder NS_DESIGNATED_INITIALIZER;

/// The type of record that the subscription queries.
@property (readonly, copy) CKRecordType recordType;

/// The matching criteria to apply to records.
///
/// A query-based subscription uses its search predicate to identify potential matches for records. It combines the predicate information with the value in the ``CKQuerySubscription/querySubscriptionOptions`` property to determine when to send a push notification to the app.
///
/// The search predicate defines the records that the subscription object monitors for changes. The system only uses the property's value when the ``CKSubscription/subscriptionType`` property is ``CKSubscription/SubscriptionType/query``. Otherwise, the system ignores it.
@property (readonly, copy) NSPredicate *predicate;

/// The ID of the record zone that the subscription queries.
///
/// This property applies to query-based subscriptions and zone-based subscriptions. Specifying a record zone ID limits the scope of the query to only the records in that zone. For zone-based subscriptions, the query includes all records in the specified record zone. For a query-based subscription, the query includes only records of a specific type in the specified record zone.
///
/// For zone-based subscriptions, CloudKit sets this property's value automatically. For all other subscription types, the default value is `nil`. If you want to scope your query-based subscription to a specific record zone, you must assign a value explicitly.
@property (nullable, copy) CKRecordZoneID *zoneID;

/// Options that define the behavior of the subscription.
///
/// Set the value of this property at initialization time. When you configure a query-based subscription, use one of the following values:
///
/// - ``CKQuerySubscription/Options/firesOnRecordCreation``
/// - ``CKQuerySubscription/Options/firesOnRecordUpdate``
/// - ``CKQuerySubscription/Options/firesOnRecordDeletion``
///
/// If you don't set an option, the system throws an <doc://com.apple.documentation/documentation/foundation/nsexceptionname/invalidargumentexception>.
@property (readonly, assign) CKQuerySubscriptionOptions querySubscriptionOptions;

@end


/// A subscription that generates push notifications when CloudKit modifies records in a specific record zone.
///
/// Subscriptions track the creation, modification, and deletion of records in a database, and are fundamental in keeping data on the user's device up to date. A subscription applies only to the user that creates it. When a subscription registers a change, such as CloudKit saving a new record, it sends push notifications to the user's devices to inform your app about the change. You can then fetch the changes and cache them on-device. When appropriate, the server excludes the device where the change originates.
///
/// - Note: You don't need to explicitly enable push notifications for your App ID to receive subscription notifications. Xcode automatically adds the entitlement when you enable the CloudKit capability. For more information, see <doc:enabling-cloudkit-in-your-app>. To use silent push notifications, add the Background Modes capability in your Xcode project and then select the "Background fetch" and "Remote notifications" options.
///
/// Record zone subscriptions execute whenever a change happens in the record zone you specify when you create the subscription. You can further specialize the subscription by setting its ``CKDatabaseSubscription/recordType-46v7a`` property to a specific record type. This limits the scope of the subscription to only track changes to records of that type and reduces the number of notifications it generates.
///
/// - Note: Only the private database supports record zone subscriptions. If you attempt to save a record zone subscription in a public or shared database, CloudKit returns an error.
///
/// Create any subscriptions on your app's first launch. After you initialize a subscription, save it to the server using ``CKModifySubscriptionsOperation``. When the operation completes, record that state on-device (in <doc://com.apple.documentation/documentation/foundation/userdefaults>, for example). You can then check that state on subsequent launches to prevent unnecessary trips to the server.
///
/// To configure the notification that the subscription generates, set the subscription's ``CKSubscription/notificationInfo`` property. Because the system coalesces notifications, don't rely on them for specific changes. CloudKit can omit data to keep the payload size under the APNs size limit. Consider notifications an indication of remote changes and use ``CKFetchRecordZoneChangesOperation`` to fetch the changed records. Server change tokens allow you to limit the fetch results to just the changes since your previous fetch.
///
/// The example below shows how to create a record zone subscription in the user's private database, configure the notifications it generates — in this case, silent push notifications — and then save that subscription to the server:
///
/// ```objc
/// // Only proceed if the subscription doesn't already exist.
/// if([[NSUserDefaults standardUserDefaults]
///     boolForKey:@"didCreateFeedSubscription"] == NO) {
///
///     // Create a subscription that's scoped to a specific record zone. Provide
///     // a subscription ID that's unique within the context of the user's
///     // private database.
///     CKRecordZoneSubscription *subscription =
///     [[CKRecordZoneSubscription alloc]
///      initWithZoneID:recordZone.zoneID
///      subscriptionID:@"feed-changes"];
///
///     // Scope the subscription to just the 'FeedItem' record type.
///     subscription.recordType = @"FeedItem";
///
///     // Configure the notification so that the system delivers it silently
///     // and therefore doesn't require permission from the user.
///     CKNotificationInfo *notificationInfo = [CKNotificationInfo new];
///     notificationInfo.shouldSendContentAvailable = YES;
///     subscription.notificationInfo = notificationInfo;
///
///     // Create an operation that saves the subscription to the server.
///     CKModifySubscriptionsOperation *operation =
///         [[CKModifySubscriptionsOperation alloc]
///          initWithSubscriptionsToSave:@[subscription]
///          subscriptionIDsToDelete:NULL];
///
///     operation.modifySubscriptionsCompletionBlock =
///         ^(NSArray *subscriptions, NSArray *deleted, NSError *error) {
///         if (error) {
///             // Handle the error.
///         } else {
///             // Record that the system successfully creates the subscription
///             // to prevent unnecessary trips to the server in later launches.
///             [[NSUserDefaults standardUserDefaults]
///              setBool:YES forKey:@"didCreateFeedSubscription"];
///         }
///     };
///
///     // Set an appropriate QoS and add the operation to the private
///     // database's operation queue to execute it.
///     operation.qualityOfService = NSQualityOfServiceUtility;
///     [CKContainer.defaultContainer.privateCloudDatabase addOperation:operation];
/// }
/// ```
API_AVAILABLE(macos(10.12), ios(10.0), tvos(10.0), watchos(6.0))
CK_SUBCLASSING_DEPRECATED // should not be subclassed, or Sendable may no longer apply
// NS_SWIFT_SENDABLE on macos(13.3), macCatalyst(16.4), ios(16.4), tvos(16.4), watchos(9.4)
@interface CKRecordZoneSubscription : CKSubscription <NSSecureCoding, NSCopying>

/// Creates a subscription for all records in the specified record zone.
///
/// - Parameters:
///   - zoneID: The ID of the record zone that contains the records you want to monitor. This parameter must not be `nil`.
///
/// The subscription that this method returns is a zone-based subscription that generates push notifications when CloudKit changes any of the specified record zone's records.
- (instancetype)initWithZoneID:(CKRecordZoneID *)zoneID API_DEPRECATED_WITH_REPLACEMENT("initWithZoneID:subscriptionID:", macos(10.12, 10.12), ios(10.0, 10.0), tvos(10.0, 10.0), watchos(6.0, 6.0));

/// Creates a named subscription for all records in the specified record zone.
///
/// - Parameters:
///   - zoneID: The ID of the record zone that contains the records you want to monitor. This parameter must not be `nil`.
///   - subscriptionID: The subscription's name. It must be unique in the container, and must not be `nil` or an empty string.
///
/// The subscription that this method returns is a zone-based subscription that generates push notifications when CloudKit changes any of the specified record zone's records.
- (instancetype)initWithZoneID:(CKRecordZoneID *)zoneID subscriptionID:(CKSubscriptionID)subscriptionID NS_DESIGNATED_INITIALIZER;

/// Creates a zone-based subscription from a serialized instance.
///
/// - Parameters:
///   - aDecoder: The coder for decoding the serialized record zone subscription.
- (instancetype)initWithCoder:(NSCoder *)aDecoder NS_DESIGNATED_INITIALIZER;

/// The ID of the record zone that the subscription queries.
///
/// This property applies to query-based subscriptions and zone-based subscriptions. Specifying a record zone ID limits the scope of the query to only the records in that zone. For zone-based subscriptions, the query includes all records in the specified record zone. For a query-based subscription, the query includes only records of a specific type in the specified record zone.
///
/// For zone-based subscriptions, CloudKit sets this property's value automatically. For all other subscription types, the default value is `nil`. If you want to scope your query-based subscription to a specific record zone, you must assign a value explicitly.
@property (readonly, copy, nonatomic) CKRecordZoneID *zoneID;

/// The type of record that the subscription queries.
@property (nullable, copy) CKRecordType recordType;

@end


/// A subscription that generates push notifications when CloudKit modifies records in a database.
///
/// Subscriptions track the creation, modification, and deletion of records in a database, and are fundamental in keeping data on the user's device up to date. A subscription applies only to the user that creates it. When a subscription registers a change, such as CloudKit saving a new record, it sends push notifications to the user's devices to inform your app about the change. You can then fetch the changes and cache them on-device. When appropriate, the server excludes the device where the change originates.
///
/// - Note: You don't need to explicitly enable push notifications for your App ID to receive subscription notifications. Xcode automatically adds the entitlement when you enable the CloudKit capability. For more information, see <doc:enabling-cloudkit-in-your-app>. To use silent push notifications, add the Background Modes capability in your Xcode project and then select the "Background fetch" and "Remote notifications" options.
///
/// A database subscription executes whenever a change occurs in a custom record zone that resides in the database where you save the subscription. This is important for the shared database because you don't know what record zones exist in advance. The only exception to this is the default record zone in the user's private database, which doesn't participate in database subscriptions.
///
/// You can further specialize a database subscription by setting its ``recordType-46v7a`` property to a specific record type. This limits the scope of the subscription to only track changes to records of that type and reduces the number of notifications it generates.
///
/// - Note: Only private and shared databases support database subscriptions. If you attempt to save a database subscription in the public database, CloudKit returns an error.
///
/// Create any subscriptions on your app's first launch. After you initialize a subscription, save it to the server using ``CKModifySubscriptionsOperation``. After the operation completes, record that state on-device (in <doc://com.apple.documentation/documentation/foundation/userdefaults>, for example). You can then check that state on subsequent launches to prevent unnecessary trips to the server.
///
/// To configure the notification that the subscription generates, set the subscription's ``CKSubscription/notificationInfo`` property. Because the system coalesces notifications, don't rely on them for specific changes. CloudKit can omit data to keep the payload size under the APNs size limit. Consider notifications an indication of remote changes, and use ``CKFetchDatabaseChangesOperation`` to fetch the record zones that contain those changes. After you have the record zones, use ``CKFetchRecordZoneChangesOperation`` to fetch the changed records in each zone. Server change tokens allow you to limit the fetch results to just the changes since your previous fetch.
///
/// The example below shows how to create a database subscription in the user's private database, configure the notifications it generates — in this case, silent push notifications — and then save that subscription to the server:
///
/// ```objc
/// // Only proceed if the subscription doesn't already exist.
/// if([[NSUserDefaults standardUserDefaults]
///     boolForKey:@"didCreateFeedSubscription"] == NO) {
///
///     // Create a subscription with an ID that's unique within the scope of
///     // the user's private database.
///     CKDatabaseSubscription *subscription =
///         [[CKDatabaseSubscription alloc]
///          initWithSubscriptionID:@"feed-changes"];
///
///     // Scope the subscription to just the 'FeedItem' record type.
///     subscription.recordType = @"FeedItem";
///
///     // Configure the notification so that the system delivers it silently
///     // and, therefore, doesn't require permission from the user.
///     CKNotificationInfo *notificationInfo = [CKNotificationInfo new];
///     notificationInfo.shouldSendContentAvailable = YES;
///     subscription.notificationInfo = notificationInfo;
///
///     // Create an operation that saves the subscription to the server.
///     CKModifySubscriptionsOperation *operation =
///         [[CKModifySubscriptionsOperation alloc]
///          initWithSubscriptionsToSave:@[subscription]
///          subscriptionIDsToDelete:NULL];
///
///     operation.modifySubscriptionsCompletionBlock =
///         ^(NSArray *subscriptions, NSArray *deleted, NSError *error) {
///         if (error) {
///             // Handle the error.
///         } else {
///             // Record that the system successfully creates the subscription
///             // to prevent unnecessary trips to the server in later launches.
///             [[NSUserDefaults standardUserDefaults]
///              setBool:YES forKey:@"didCreateFeedSubscription"];
///         }
///     };
///
///     // Set an appropriate QoS and add the operation to the private
///     // database's operation queue to execute it.
///     operation.qualityOfService = NSQualityOfServiceUtility;
///     [CKContainer.defaultContainer.privateCloudDatabase addOperation:operation];
/// }
/// ```
API_AVAILABLE(macos(10.12), ios(10.0), tvos(10.0), watchos(6.0))
CK_SUBCLASSING_DEPRECATED // should not be subclassed, or Sendable may no longer apply
// NS_SWIFT_SENDABLE on macos(13.3), macCatalyst(16.4), ios(16.4), tvos(16.4), watchos(9.4)
@interface CKDatabaseSubscription : CKSubscription <NSSecureCoding, NSCopying>

/// Creates an empty database subscription.
- (instancetype)init API_DEPRECATED_WITH_REPLACEMENT("initWithSubscriptionID:", macos(10.12, 10.12), ios(10.0, 10.0), tvos(10.0, 10.0), watchos(6.0, 6.0));

/// Creates an empty database subscription.
+ (instancetype)new OBJC_SWIFT_UNAVAILABLE("use object initializers instead");

/// Creates a named subscription for all records in a database.
///
/// - Parameters:
///   - subscriptionID: The subscription's name. It must be unique in the container, and must not be `nil` or an empty string.
- (instancetype)initWithSubscriptionID:(CKSubscriptionID)subscriptionID NS_DESIGNATED_INITIALIZER;

/// Creates a database subscription from a serialized instance.
///
/// - Parameters:
///   - aDecoder: The object that decodes the serialized database subscription.
- (instancetype)initWithCoder:(NSCoder *)aDecoder NS_DESIGNATED_INITIALIZER;

/// The type of record that the subscription queries.
@property (nullable, copy) CKRecordType recordType;

@end


/// An object that describes the configuration of a subscription's push notifications.
///
/// When configuring a subscription, use this class to specify the type of push notifications you want to generate when conditions meet the subscription's trigger. You can provide content that the system displays to the user, describe the sounds to play, and indicate whether the app's icon has a badge. You can request that the notification include information about the record that triggers it.
///
/// When your app receives a push notification that a subscription generates, instantiate an instance of ``CKNotification`` using the ``CKNotification/init(fromRemoteNotificationDictionary:)`` method and pass the notification's payload. The object that the method returns contains the data you specify when configuring the subscription.
///
/// For more information about push notification alerts and how they display to the user, see [Apple Push Notification Service](https://developer.apple.com/library/archive/documentation/NetworkingInternet/Conceptual/RemoteNotificationsPG/Chapters/ApplePushService.html#//apple_ref/doc/uid/TP40008194-CH100) in [Local and Remote Notification Programming Guide](https://developer.apple.com/library/archive/documentation/NetworkingInternet/Conceptual/RemoteNotificationsPG/index.html#//apple_ref/doc/uid/TP40008194).
///
/// - Note: If you don't set any of the ``alertBody``, ``soundName``, or ``shouldBadge`` properties, CloudKit sends the push notification using a lower priority and doesn't display any content to the user.
API_AVAILABLE(macos(10.10), ios(8.0), watchos(6.0))
CK_SUBCLASSING_DEPRECATED // should not be subclassed, or Sendable may no longer apply
// NS_SWIFT_SENDABLE on macos(13.3), macCatalyst(16.4), ios(16.4), tvos(16.4), watchos(9.4)
@interface CKNotificationInfo : NSObject <NSSecureCoding, NSCopying>

/// The text for the notification's alert.
///
/// Set this property's value to have the system display the specified string when it receives the corresponding push notification. If you localize your app's content, use the ``CKSubscription/NotificationInfo/alertLocalizationKey`` property instead.
@property (nullable, copy) NSString *alertBody __TVOS_PROHIBITED;

/// The key that identifies the localized string for the notification's alert.
///
/// Set this property's value to have the system display a localized string when it receives the corresponding push notification. The system uses the key to find the matching string in your app's `Localizable.string` file. If you specify a value for this property, CloudKit ignores the ``CKSubscription/NotificationInfo/alertBody`` property's value.
///
/// For information about localizing string resources, see [Internationalization and Localization Guide](https://developer.apple.com/library/archive/documentation/MacOSX/Conceptual/BPInternational/Introduction/Introduction.html#//apple_ref/doc/uid/10000171i).
@property (nullable, copy) NSString *alertLocalizationKey __TVOS_PROHIBITED;

/// The fields for building a notification's alert.
///
/// This property is an array of field names that CloudKit uses to extract the corresponding values from the record that triggers the push notification. The values must be strings, numbers, or dates. Don't specify keys that use other value types. CloudKit may truncate strings with a length greater than 100 characters when it adds them to a notification's payload.
///
/// If you use `%@` for your substitution variables, CloudKit replaces those variables by traversing the array in order. If you use variables of the form `%n$@`, where `n` is an integer, `n` represents the index (starting at 1) of the item in the array to use. So, the first item in the array replaces the variable `%1$@`, the second item replaces the variable `%2$@`, and so on. You can use indexed substitution variables to change the order of items in the resulting string, which might be necessary when you localize your app's content.
@property (nullable, copy) NSArray<CKRecordFieldKey> *alertLocalizationArgs __TVOS_PROHIBITED;

/// The notification's title.
///
/// CloudKit uses this value to set the `title` push notification property.
///
/// See <doc://com.apple.documentation/documentation/usernotifications/generating-a-remote-notification> for more detail about push notification properties.
@property (nullable, copy) NSString *title API_AVAILABLE(macos(10.13), ios(11.0)) __TVOS_PROHIBITED;

/// The key that identifies the localized string for the notification's title.
///
/// CloudKit uses this value to set the `title-loc-key` push notification property.
///
/// See <doc://com.apple.documentation/documentation/usernotifications/generating-a-remote-notification> for more details about push notification properties.
@property (nullable, copy) NSString *titleLocalizationKey API_AVAILABLE(macos(10.13), ios(11.0)) __TVOS_PROHIBITED;

/// The fields for building a notification's title.
///
/// This property is an array of field names that CloudKit uses to extract the corresponding values from the record that triggers the push notification. The values must be strings, numbers, or dates. Don't specify keys that use other value types. CloudKit may truncate strings with a length greater than 100 characters when it adds them to a notification's payload.
///
/// If you use `%@` for your substitution variables, CloudKit replaces those variables by traversing the array in order. If you use variables of the form `%n$@`, where `n` is an integer, `n` represents the index (starting at 1) of the item in the array to use. So, the first item in the array replaces the variable `%1$@`, the second item replaces the variable `%2$@`, and so on. You can use indexed substitution variables to change the order of items in the resulting string, which might be necessary when you localize your app's content.
@property (nullable, copy) NSArray<CKRecordFieldKey> *titleLocalizationArgs API_AVAILABLE(macos(10.13), ios(11.0)) __TVOS_PROHIBITED;

/// The notification's subtitle.
///
/// CloudKit uses this value to set the `subtitle` push notification property. If you set ``CKSubscription/NotificationInfo/subtitleLocalizationKey``, CloudKit ignores this value.
///
/// See <doc://com.apple.documentation/documentation/usernotifications/generating-a-remote-notification> for more details about push notification properties.
@property (nullable, copy) NSString *subtitle API_AVAILABLE(macos(10.13), ios(11.0)) __TVOS_PROHIBITED;

/// The key that identifies the localized string for the notification's subtitle.
///
/// CloudKit uses this value to set the `subtitle-loc-key` push notification property. Setting this property overrides any value in ``CKSubscription/NotificationInfo/subtitle``.
///
/// See <doc://com.apple.documentation/documentation/usernotifications/generating-a-remote-notification> for more details about push notification properties.
@property (nullable, copy) NSString *subtitleLocalizationKey API_AVAILABLE(macos(10.13), ios(11.0)) __TVOS_PROHIBITED;

/// The fields for building a notification's subtitle.
///
/// This property is an array of field names that CloudKit uses to extract the corresponding values from the record that triggers the push notification. The values must be strings, numbers, or dates. Don't specify keys that use other value types. CloudKit may truncate strings with a length greater than 100 characters when it adds them to a notification's payload.
///
/// If you use `%@` for your substitution variables, CloudKit replaces those variables by traversing the array in order. If you use variables of the form `%n$@`, where `n` is an integer, `n` represents the index (starting at 1) of the item in the array to use. So, the first item in the array replaces the variable `%1$@`, the second item replaces the variable `%2$@`, and so on. You can use indexed substitution variables to change the order of items in the resulting string, which might be necessary when you localize your app's content.
@property (nullable, copy) NSArray<CKRecordFieldKey> *subtitleLocalizationArgs API_AVAILABLE(macos(10.13), ios(11.0)) __TVOS_PROHIBITED;

/// The key that identifies the localized string for the notification's action.
///
/// Set this property's value to have the system use a localized string for the text of the notification's button that opens your app. The system uses the key to find the matching string in your app's `Localizable.string` file.
///
/// If this property's value is `nil`, the system displays a single button to dismiss the alert.
///
/// For information about localizing string resources, see [Internationalization and Localization Guide](https://developer.apple.com/library/archive/documentation/MacOSX/Conceptual/BPInternational/Introduction/Introduction.html#//apple_ref/doc/uid/10000171i).
@property (nullable, copy) NSString *alertActionLocalizationKey __TVOS_PROHIBITED;

/// The filename of an image to use as a launch image.
///
/// If you specify a value, the system uses it to locate an image in the app's bundle, and displays it as a launch image when the user launches the app after receiving a push notification.
@property (nullable, copy) NSString *alertLaunchImage __TVOS_PROHIBITED;

/// The filename of the sound file to play when a notification arrives.
///
/// If you specify a value, the system uses it to locate a sound file in the app's bundle. The sound plays when the system receives a push notification. If the system can't find the specified file, or if you use the string `default`, the system plays the default sound.
@property (nullable, copy) NSString *soundName __TVOS_PROHIBITED;

/// The names of fields to include in the push notification's payload.
///
/// This property contains an array of strings, each of which corresponds to the name of a field in the record that triggers the notification. When the system receives a notification, it includes the keys, and their corresponding values. You can request a maximum of three keys.
///
/// For the keys you specify, the allowable types are <doc://com.apple.documentation/documentation/foundation/nsstring>, <doc://com.apple.documentation/documentation/foundation/nsnumber>, <doc://com.apple.documentation/documentation/corelocation/cllocation>, <doc://com.apple.documentation/documentation/foundation/nsdate>, and ``CKRecord/Reference``. You can't specify keys with values that contain other data types. CloudKit may truncate strings that are more than 100 characters when it adds them to the notification's payload.
@property (nullable, copy) NSArray<CKRecordFieldKey> *desiredKeys;

/// A Boolean value that determines whether an app's icon badge increments its value.
///
/// The default value of this property is <doc://com.apple.documentation/documentation/swift/false>. Set it to <doc://com.apple.documentation/documentation/swift/true> to cause the system to increment the badge value whenever it receives the corresponding push notification.
@property (assign) BOOL shouldBadge API_AVAILABLE(tvos(10.0));

/// A Boolean value that indicates whether the push notification includes the content available flag.
///
/// When this property is <doc://com.apple.documentation/documentation/swift/true>, the server includes the `content-available` flag in the push notification's payload. That flag causes the system to wake or launch an app that isn't currently running. The app then receives background execution time to download any data for the push notification, such as the set of changed records. If the app is already running in the foreground, the inclusion of this flag has no additional effect and the system delivers the notification to the app delegate for processing as usual.
///
/// The default value of this property is <doc://com.apple.documentation/documentation/swift/false>.
@property (assign) BOOL shouldSendContentAvailable;

/// A Boolean value that indicates whether the push notification sets the mutable content flag.
///
/// When this property is <doc://com.apple.documentation/documentation/swift/true>, the server includes the `mutable-content` flag with a value of `1` in the push notification's payload. When the value is `1`, the system passes the notification to your app extension for modification before delivery.
///
/// See <doc://com.apple.documentation/documentation/usernotifications/generating-a-remote-notification> for more information about the `mutable-content` flag, and <doc://com.apple.documentation/documentation/usernotifications/modifying-content-in-newly-delivered-notifications> for information about how to modify push notification content in your app extension prior to delivery.
///
/// The default value of this property is <doc://com.apple.documentation/documentation/swift/false>.
@property (assign) BOOL shouldSendMutableContent API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0));


/// The name of the action group that corresponds to this notification.
///
/// Categories allow you to present custom actions to the user on your push notifications. For more information, see <doc://com.apple.documentation/documentation/uikit/uimutableusernotificationcategory>.
@property (nullable, copy) NSString *category API_AVAILABLE(macos(10.11), ios(9.0)) __TVOS_PROHIBITED;

/// A value that the system uses to coalesce unseen push notifications.
///
/// When CloudKit generates a push notification, it sets the notification's `apns-collapse-id` header to this property's value. The system uses this header to coalesce unseen notifications.
///
/// See <doc://com.apple.documentation/documentation/usernotifications/sending-notification-requests-to-apns> for more information about sending notifications using the Apple Push Notification service.
@property (nullable, copy) NSString *collapseIDKey API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0));

@end

NS_HEADER_AUDIT_END(nullability, sendability)
