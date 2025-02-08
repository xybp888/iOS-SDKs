//
//  BGTask.h
//  BackgroundTasks
//
//  Copyright © 2019 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

#import <BackgroundTasks/BGDefines.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 @abstract An abstract class that represents the background work for which the app was launched to handle.
 @discussion Subclasses of this type are created by the system and should not be directly instantiated.
 */
BG_EXTERN API_AVAILABLE(ios(13.0), tvos(13.0)) API_UNAVAILABLE(macos, watchos)
/// An abstract class representing a task that’s run while the app is in the
/// background.
@interface BGTask : NSObject

/*!
 @abstract The identifier associated with the request used to schedule this background work.
 */

/// The string identifier of the task.
///
/// The identifier is the same as the one used to register the launch handler in
/// ``BGTaskScheduler/registerForTaskWithIdentifier:usingQueue:launchHandler:``.
@property (copy, readonly) NSString *identifier;

/*!
 @abstract Called by the system shortly before your app's background time expires.
 @discussion There is a limit to how long your app has to perform its background work, and your work may need to be interrupted if system conditions change. Assign a handler to this property to cancel any ongoing tasks, perform any needed cleanup, and then call setTaskCompletedWithSuccess: to signal completion to the system and allow your app to be suspended.
 This property is cleared after it is called by the system or when setTaskCompletedWithSuccess: is called. This is to mitigate the impact of a retain cycle created by referencing the BGTask instance inside this block.
 */

/// A handler called shortly before the task’s background time expires.
///
/// The time allocated by the system for expiration handlers doesn’t vary with
/// the number of background tasks. All expiration handlers must complete before
/// the allocated time.
///
/// Not setting an expiration handler results in the system marking your task as
/// complete and unsuccessful instead of sending a warning.
///
/// The manager sets the value `expirationHandler` to `nil` after the handler
/// completes.
///
/// - Parameters:
///     - expirationHandler: The expiration handler takes no arguments and has no
/// return value. Use the handler to cancel any ongoing work and to do any
/// required cleanup in as short a time as possible.
///
/// The handler may be called before the background process uses the full amount of its
/// allocated time.
@property (nullable, strong) void (^expirationHandler)(void);

- (instancetype)init NS_UNAVAILABLE; // Subclasses of this abstract type are created by the system and cannot be directly instantiated
+ (instancetype)new NS_UNAVAILABLE; // Subclasses of this abstract type are created by the system and cannot be directly instantiated

/*!
 @abstract Marks this task as complete.
 @discussion Call this method as soon as the background work associated with this task is complete. The system provides your app with a limited amount of time to finish the task. If you do not call setTaskCompletedWithSuccess: on the task, the system continues to run in the background until all the available time is consumed, wasting battery power.
 The system suspends the app as soon as all background tasks are complete.
 @param success Whether the task was completed successfully. If the task was unsuccessful, you may request the system to try again later by submitting a new task request to the scheduler before calling this method.
 */

/// Informs the background task scheduler that the task is complete.
///
/// Not calling ``BGTask/setTaskCompletedWithSuccess:`` before the time for the
/// task expires may result in the system killing your app.
///
/// You can reschedule an unsuccessful required task.
///
/// - Important: If you don’t set an expiration handler, the system will mark
/// your task as complete and unsuccessful instead of sending a warning.
///
/// - Parameters:
///     - success: A `Boolean` indicating if the task completed successfully or not.
- (void)setTaskCompletedWithSuccess:(BOOL)success;

@end

/*!
 @abstract A background task used to perform deferrable processing.
 */
BG_EXTERN API_AVAILABLE(ios(13.0), tvos(13.0)) API_UNAVAILABLE(macos, watchos)
/// A time-consuming processing task that runs while the app is in the
/// background.
///
/// Use processing tasks for long data updates, processing data, and app
/// maintenance. Although processing tasks can run for minutes, the system can
/// interrupt the process. Add an expiration handler by setting
/// ``BGTask/expirationHandler`` for any required cleanup.
///
/// Executing processing tasks requires setting the `processing`
/// <doc://com.apple.documentation/documentation/bundleresources/information_property_list/uibackgroundmodes>
/// capability. For information on setting this capability, see
/// ``BGTaskScheduler``.
///
/// Processing tasks run only when the device is idle. The system terminates any
/// background processing tasks running when the user starts using the device.
/// Background refresh tasks are not affected.
@interface BGProcessingTask : BGTask

@end

/*!
 @abstract A potentially time-consuming task that is required to process data essential to a health research study.
 */
BG_EXTERN API_AVAILABLE(ios(17.0), tvos(25.0)) API_UNAVAILABLE(macos, watchos, tvos)
/// A task meant to perform processing on behalf of health research studies.
///
/// Health research tasks may only be used by applications entitled to perform
/// studies and user's have opted in to the relevant study. These apps must have the
/// `com.apple.developer.backgroundtasks.healthresearch` entitlement.
@interface BGHealthResearchTask : BGProcessingTask

@end

/*!
 @abstract A background task used to update your app's contents in the background.
 */
BG_EXTERN API_AVAILABLE(ios(13.0), tvos(13.0)) API_UNAVAILABLE(macos, watchos)
/// An object representing a short task typically used to refresh content that’s
/// run while the app is in the background.
///
/// Use app refresh tasks for updating your app with small bits of information,
/// such as the latest stock values.
///
/// Executing app refresh tasks requires setting the `fetch`
/// <doc://com.apple.documentation/documentation/bundleresources/information_property_list/uibackgroundmodes>
/// capability. For information on setting this capability, see
/// ``BGTaskScheduler``.
@interface BGAppRefreshTask : BGTask

@end

NS_ASSUME_NONNULL_END
