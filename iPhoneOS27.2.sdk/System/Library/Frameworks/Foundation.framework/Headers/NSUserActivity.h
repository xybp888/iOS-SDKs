/*	NSUserActivity.h
	Copyright (c) 2014-2019, Apple Inc. All rights reserved.
*/

#import <Foundation/NSObject.h>
#import <Foundation/NSObjCRuntime.h>

#if __OBJC2__

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

@class NSArray, NSArray<ObjectType>, NSDictionary<KeyType, ObjectType>, NSSet<ObjectType>, NSString, NSURL, NSInputStream, NSOutputStream, NSError;
@protocol NSUserActivityDelegate;

typedef NSString* NSUserActivityPersistentIdentifier NS_SWIFT_BRIDGED_TYPEDEF;

/// A representation of the state of your app at a moment in time.
///
/// An ``NSUserActivity`` object provides a lightweight way to capture the state of your app and put it to use later. Create this object to capture information about what a person was doing, such as viewing app content, editing a document, viewing a web page, or watching a video. When the system launches your app and an activity object is available, your app can use the information in that object to restore itself to an appropriate state. Spotlight also uses these objects to improve search results for people. To allow people to continue an activity on another device, see <doc:implementing-handoff-in-your-app>.
///
/// ### Siri
///
/// If SiriKit needs to launch your app for any reason, it creates a user activity object and assigns an appropriate <doc://com.apple.documentation/documentation/intents/ininteraction> object to its ``interaction`` property. Your app can use the interaction information to configure itself and display information related to the interaction started by SiriKit. You can also provide SiriKit with a custom user activity object containing additional data that you want passed to your app.
///
/// In iOS 15 and later, a person can share content they're viewing by asking Siri to "share this". Apps built with Mac Catalyst provide the same capability with an <doc://com.apple.documentation/documentation/appkit/nssharingservicepickertoolbaritem> in the toolbar. You can use <doc://com.apple.documentation/documentation/uikit/uiactivityitemsconfigurationproviding/activityitemsconfiguration> or <doc://com.apple.documentation/documentation/uikit/uiwindowscene/activityitemsconfigurationsource> to provide shareable content. In iOS, if both of those properties are <doc://com.apple.documentation/documentation/objectivec/nil-227m0>, Siri uses the ``webpageURL`` property of your app's current user activity as a fallback value.
///
/// ### Quick Note
///
/// Quick Note on macOS and iOS can link to any app content represented as an ``NSUserActivity``. To appear as a link, the content must be the app's current activity, and provide at least one of the following identifiers:
///
/// - term ``webpageURL``: An `https:` URL, ideally in a canonical form that's consistent every time a person visits the same content.
/// - term ``persistentIdentifier``: A string that uniquely identifies the content in this domain. The identifier should identify the same content across devices.
/// - term ``targetContentIdentifier``: A string that uniquely identifies the content in this domain, but also allows disambiguating between multiple scenes of an app. The identifier should identify the same content across devices.
///
///
///
/// To work well with Quick Note, content must adhere to the following guidelines:
///
/// - The activity ``title`` should be clear and concise. This text describes the content of the link, like "Photo taken on July 27, 2020" or "Conversation with Maria". Use nouns for activity titles.
/// - Keep the app's current activity up to date, using ``becomeCurrent()`` and ``resignCurrent()``.
/// - Linkable identifiers (listed above) must be stable and consistent for the same content. When you link from a note to a document in an app, and later revisit that document, the system shows an indicator linking back to the note. The system compares identifiers to check that the document is the same as the original source of the link.
/// - Maintain support for activities provided by your app, and support navigating to linked content indefinitely. Links added to notes are important to people, who may feel that a broken link indicates data loss.
/// - Gracefully handle attempts to navigate to an activity that points to content that doesn't exist. For example, you can redirect to the new location of moved content, or show an error message. This situation may happen with shared notes, when a person links to content that exists only on another person's device.
///
/// ### Search results
///
/// If your ``NSUserActivity`` objects contain information that a person might want to search for later, set the ``isEligibleForSearch`` property to <doc://com.apple.documentation/documentation/swift/true>. When you enable search, Spotlight indexes your user activity objects and considers them during subsequent on-device searches. For example, if a person viewed information about a particular restaurant in your app, you'd enable search for the corresponding user activity object. Subsequent searches for restaurants using Spotlight could then include the results obtained from your user activity object.
///
/// In addition to on-device searches, you can contribute URLs accessed by your app with the global Spotlight search engine. Sharing a URL helps Spotlight improve its own search results for other people. To contribute a URL, put the URL in the ``webpageURL`` property of your activity object and set the ``isEligibleForPublicIndexing`` property to <doc://com.apple.documentation/documentation/swift/true>.
///
/// > Important:
/// > Your app must maintain a strong reference to any activity objects that you use for search results.
///
/// Employ user activity objects to record user-initiated activities, not as a general-purpose indexing mechanism of your app's data. To index all of your app's content, and not just the content touched by people, use the APIs of the <doc://com.apple.documentation/documentation/corespotlight> framework.
API_AVAILABLE(macos(10.10), ios(8.0), watchos(2.0), tvos(9.0))
@interface NSUserActivity : NSObject

/// Initializes and returns a newly created NSUserActivity with the given activity type.
///
/// A user activity may be continued only in an application that (1) has the same developer Team ID as the activity’s
/// source application and (2) supports the activity’s type. Supported activity types are specified in the application’s
/// @c Info.plist under the @c NSUserActivityTypes key.
/// @param activityType A string that identifies the type of the activity.
- (instancetype)initWithActivityType:(NSString *)activityType NS_DESIGNATED_INITIALIZER;

/// Initializes and returns a newly created NSUserActivity with the first activity type from the @c NSUserActivityTypes key in the application’s @c Info.plist.
- (instancetype)init API_DEPRECATED("Use initWithActivityType: with a specific activity type string", macosx(10.10, 10.12), ios(8.0,10.0), watchos(2.0,3.0), tvos(9.0,10.0));

/// The activity type the user activity was created with.
@property (readonly, copy) NSString *activityType;

/// An optional, user-visible title for this activity, such as a document name or web page title.
@property (nullable, copy) NSString *title;

/// The user info dictionary contains application-specific state needed to continue an activity on another device.
///
/// Each key and value must be of the following types: @c NSArray, @c NSData, @c NSDate, @c NSDictionary, @c NSNull,
/// @c NSNumber, @c NSSet, @c NSString, @c NSURL, or @c NSUUID.
@property (nullable, copy) NSDictionary *userInfo;

/// Adds to the user info dictionary the entries from @c otherDictionary.
///
/// The keys and values must be of the types allowed in the user info dictionary.
- (void)addUserInfoEntriesFromDictionary:(NSDictionary *)otherDictionary;

/// The keys from the user info property which represent the minimal information about this user activity that should be stored for later restoration.
///
/// A @c nil value means all keys in the user info are required.
@property (nullable, copy) NSSet<NSString *> *requiredUserInfoKeys API_AVAILABLE(macos(10.11), ios(9.0), watchos(3.0), tvos(10.0));

/// If set to @c YES, then the delegate for this user activity will receive a @c userActivityWillSave: callback before being sent for continuation on another device.
@property (assign) BOOL needsSave;

/// When no suitable application is installed on a resuming device and this is set, the user activity will instead be continued in a web browser by loading this resource.
@property (nullable, copy) NSURL *webpageURL;

/// The URL of the webpage that referred (linked to) @c webpageURL.
@property (nullable, copy) NSURL *referrerURL API_AVAILABLE(macos(10.13), ios(11.0), watchos(4.0), tvos(11.0));

/// If non-nil, an absolute date after which this activity is no longer eligible to be indexed or handed off.
@property (nullable, copy) NSDate *expirationDate API_AVAILABLE(macos(10.11), ios(9.0), watchos(3.0), tvos(10.0));

/// A set of keywords, representing words or phrases in the current user’s language that might help the user to find this activity in the application history.
@property (copy) NSSet<NSString *> *keywords API_AVAILABLE(macos(10.11), ios(9.0), watchos(3.0), tvos(10.0));

/// When used for continuation, the user activity can allow the continuing side to connect back for more information using streams.
///
/// This value is set to @c NO by default. It can be dynamically set to @c YES to selectively support continuation streams.
@property BOOL supportsContinuationStreams;

/// The user activity delegate is informed when the activity is being saved or continued.
@property (nullable, weak) id<NSUserActivityDelegate> delegate;

/// A string that identifies the content of this NSUserActivity, for matching against existing documents when re-opening to see if they are the same.
///
/// Setting this property is optional and does not automatically set @c needsSave to @c YES.
@property (nullable, copy) NSString* targetContentIdentifier API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0));

/// Marks the receiver as the activity currently in use by the user.
///
/// For example, the activity associated with the active window. A newly created activity is eligible for continuation on another device after the first time it becomes current.
- (void)becomeCurrent;

/// If this activity is the current activity, it should stop being so and set the current activity to nothing.
- (void)resignCurrent API_AVAILABLE(macos(10.11), ios(9.0), watchos(3.0), tvos(10.0));

/// Invalidate an activity when it’s no longer eligible for continuation.
///
/// For example, when the window associated with an activity is closed. An invalid activity cannot become current.
- (void)invalidate;

/// When an app is launched for a continuation event it can request streams back to the originating side.
///
/// Streams can only be successfully retrieved from the NSUserActivity in the NS/UIApplication delegate that is called for a continuation event.
/// The streams returned in the completion handler will be in an unopened state. The streams should be opened immediately to start requesting information from the other side.
- (void)getContinuationStreamsWithCompletionHandler:(void (NS_SWIFT_SENDABLE ^)(NSInputStream * _Nullable inputStream, NSOutputStream * _Nullable outputStream, NSError * _Nullable error))completionHandler;

/// Set to @c YES if this user activity should be eligible to be handed off to another device.
@property (getter=isEligibleForHandoff) BOOL eligibleForHandoff API_AVAILABLE(macos(10.11), ios(9.0), watchos(3.0), tvos(10.0));

/// Set to @c YES if this user activity should be indexed by App History.
@property (getter=isEligibleForSearch) BOOL eligibleForSearch API_AVAILABLE(macos(10.11), ios(9.0), watchos(3.0), tvos(10.0));

/// Set to @c YES if this user activity should be eligible for indexing for any user of this application, on any device.
///
/// Set to @c NO if the activity contains private or sensitive information or which would not be useful to other users if indexed.
/// The activity must also have @c requiredUserActivityKeys or a @c webpageURL.
@property (getter=isEligibleForPublicIndexing) BOOL eligibleForPublicIndexing API_AVAILABLE(macos(10.11), ios(9.0), watchos(3.0), tvos(10.0));

/// Set to @c YES if this user activity should be eligible for prediction.
@property (getter=isEligibleForPrediction) BOOL eligibleForPrediction API_AVAILABLE( ios(12.0), watchos(5.0) ) API_UNAVAILABLE( macos, tvos );

/// A persistent identifier for this user activity.
@property (copy, nullable) NSUserActivityPersistentIdentifier persistentIdentifier  API_AVAILABLE( macos(10.15), ios(12.0), watchos(5.0) ) API_UNAVAILABLE( tvos );

/// Deletes user activities that have the specified persistent identifiers.
///
/// @param persistentIdentifiers An array of persistent identifiers for the user activities to delete.
/// @param handler A completion handler that is called when the deletion is complete.
+(void) deleteSavedUserActivitiesWithPersistentIdentifiers:(NSArray<NSUserActivityPersistentIdentifier>*) persistentIdentifiers completionHandler:(void(NS_SWIFT_SENDABLE ^)(void))handler API_AVAILABLE( macos(10.15), ios(12.0), watchos(5.0) ) API_UNAVAILABLE( tvos );

/// Deletes all saved user activities for this application.
///
/// @param handler A completion handler that is called when the deletion is complete.
+(void) deleteAllSavedUserActivitiesWithCompletionHandler:(void(NS_SWIFT_SENDABLE ^)(void))handler API_AVAILABLE( macos(10.15), ios(12.0), watchos(5.0) ) API_UNAVAILABLE( tvos );

@end

/// An activity that continues from Handoff or a universal link.
///
/// Only activities of this type can be continued from a web browser to a native app.
FOUNDATION_EXPORT NSString * const NSUserActivityTypeBrowsingWeb;

/// The interface through which a user activity instance notifies its delegate of updates.
///
/// An object conforming to the ``NSUserActivityDelegate`` protocol works with an ``NSUserActivity`` object, which encapsulates the state of a user activity in an application on a particular device and enables the same activity to be continued on another device. For example, a user browsing an article in Safari on a Mac can move to an iOS device where the same webpage automatically opens in Safari with the same scroll position.
///
/// The user activity delegate is responsible for updating the state of an activity and is also notified when an activity has been continued on another device. The user activity delegate is typically a top-level object in the app—such as a window, view controller, or the app delegate—that manages the activity's interaction with the app.
API_AVAILABLE(macos(10.10), ios(8.0), watchos(3.0), tvos(9.0))
@protocol NSUserActivityDelegate <NSObject>
@optional

/// The user activity will be saved (to be continued or persisted). The receiver should update the activity with current activity state.
- (void)userActivityWillSave:(NSUserActivity *)userActivity;

/// The user activity was continued on another device.
- (void)userActivityWasContinued:(NSUserActivity *)userActivity;

/// If @c supportsContinuationStreams is set to @c YES the continuing side can request streams back to this user activity.
///
/// This delegate callback will be received with the incoming streams from the other side. The streams will be in an unopened state.
/// The streams should be opened immediately to start receiving requests from the continuing side.
- (void)userActivity:(NSUserActivity *)userActivity didReceiveInputStream:(NSInputStream *) inputStream outputStream:(NSOutputStream *)outputStream;

@end

NS_HEADER_AUDIT_END(nullability, sendability)

#endif
