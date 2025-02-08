//
//  BGTaskScheduler.h
//  BackgroundTasks
//
//  Copyright © 2019 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

#import <BackgroundTasks/BGDefines.h>

@class BGTaskScheduler;
@class BGTaskRequest;
@class BGTask;

NS_ASSUME_NONNULL_BEGIN

/// The background tasks error domain as a string.
BG_EXTERN API_AVAILABLE(ios(13.0), tvos(13.0)) API_UNAVAILABLE(macos, watchos)
NSErrorDomain const BGTaskSchedulerErrorDomain;

/*!
 @enum BGTaskSchedulerErrorCode
 @constant BGTaskSchedulerErrorCodeUnavailable Background task scheduling functionality is not available for this app/extension. Background App Refresh may have been disabled in Settings.
 @constant BGTaskSchedulerErrorCodeTooManyPendingTaskRequests The task request could not be submitted because there are too many pending task requests of this type. Cancel some existing task requests before trying again.
 @constant BGTaskSchedulerErrorCodeNotPermitted The task request could not be submitted because the appropriate background mode is not included in the UIBackgroundModes array, or its identifier was not present in the BGTaskSchedulerPermittedIdentifiers array in the app's Info.plist.
 */

/// An enumeration of the task scheduling errors.
typedef NS_ERROR_ENUM(BGTaskSchedulerErrorDomain, BGTaskSchedulerErrorCode) {
    /// A task scheduling error indicating that the app or extension can’t
    /// schedule background work.
    ///
    /// This error usually occurs for one of following reasons:
    ///
    /// - The user has disabled background refresh in settings.
    /// - The app is running on Simulator which doesn’t support background processing.
    ///  - The keyboard extension either hasn’t set
    /// <doc://com.apple.documentation/documentation/bundleresources/information_property_list/nsextension/nsextensionattributes/requestsopenaccess>
    /// to `YES` in [The Info.plist
    /// File](https://developer.apple.com/library/archive/documentation/Carbon/Conceptual/ProvidingUserAssitAppleHelp/authoring_help/authoring_help_book.html#//apple_ref/doc/uid/TP30000903-CH206-SW22),
    /// or the user hasn’t granted open access.
    /// - The extension type isn’t able to schedule background tasks.
    BGTaskSchedulerErrorCodeUnavailable = 1,
    /// A task scheduling error indicating that there are too many pending tasks
    /// of the type requested.
    ///
    /// Try canceling some existing task requests and then resubmit the request
    /// that failed.
    BGTaskSchedulerErrorCodeTooManyPendingTaskRequests = 2,
    /// A task scheduling error indicating the app isn’t permitted to schedule the
    /// task.
    ///
    /// There are two causes for this error:
    ///
    /// - The app doesn’t set the appropriate mode in the
    /// <doc://com.apple.documentation/documentation/bundleresources/information_property_list/uibackgroundmodes>
    /// array.
    ///
    /// - The task identifier of the submitted task wasn’t in the
    /// <doc://com.apple.documentation/documentation/bundleresources/information_property_list/bgtaskschedulerpermittedidentifiers>
    /// array in [the Info.plist
    /// File](https://developer.apple.com/library/archive/documentation/Carbon/Conceptual/ProvidingUserAssitAppleHelp/authoring_help/authoring_help_book.html#//apple_ref/doc/uid/TP30000903-CH206-SW22).
    BGTaskSchedulerErrorCodeNotPermitted = 3,
} API_AVAILABLE(ios(13.0), tvos(13.0)) API_UNAVAILABLE(macos, watchos);

/*!
 @class BGTaskScheduler
 @abstract The object you use to schedule deferrable work to be done in the background.
 */
BG_EXTERN API_AVAILABLE(ios(13.0), tvos(13.0)) API_UNAVAILABLE(macos, watchos)
/// A class for scheduling task requests that launch your app in the background.
///
/// Background tasks give your app a way to run code while the app is suspended.
/// To learn how to register, schedule, and run a background task, see
/// <doc://com.apple.documentation/documentation/uikit/app_and_environment/scenes/preparing_your_ui_to_run_in_the_background/using_background_tasks_to_update_your_app>.
@interface BGTaskScheduler : NSObject
- (instancetype)init NS_UNAVAILABLE; //Use the shared scheduler object instead
+ (instancetype)new NS_UNAVAILABLE; //Use the shared scheduler object instead

/// The shared background task scheduler instance.
@property (class, readonly, strong) __kindof BGTaskScheduler *sharedScheduler;

/*!
 @abstract Register a handler to be called for tasks that launch the app.
 @param identifier The identifier for the task that will be handled by the provided launch handler.
 @param queue The queue on which the launch handler and the expiration handler for the task will be called. The queue should be serial to ensure consistent ordering. If you pass nil, handlers will be called on a background queue.
 @param launchHandler The block that will be called when the app is launched for the specified task. The block has no return value and takes a single parameter, task, a BGTask object. Assign an expiration handler to the task's expirationHandler property and call setTaskCompletedWithSuccess: when the background work is complete.
 @discussion You must register launch handlers before your application finishes launching. Attempting to register a handler after launch or multiple handlers for the same identifier is an error. Although you may submit task requests from some extensions, only the host app will be launched to handle background work.
 @return YES if the handler was registered, or NO if it was not because the provided identifier was not present in the BGTaskSchedulerPermittedIdentifiers array in the app's Info.plist.
 */

/// Register a launch handler for the task with the associated identifier that’s
/// executed on the specified queue.
///
/// Every identifier in the
/// <doc://com.apple.documentation/documentation/bundleresources/information_property_list/bgtaskschedulerpermittedidentifiers>
/// requires a handler. Registration of all launch handlers must be complete
/// before the end of
/// <doc://com.apple.documentation/documentation/uikit/uiapplicationdelegate/1623053-applicationdidfinishlaunching>.
///
/// - Important: Register each task identifier only once. The system kills the
/// app on the second registration of the same task identifier.
///
/// - Parameters:
///     - identifier: A string containing the identifier of the task.
///
///     - queue: A queue for executing the task. Pass `nil` to use a default
/// background queue.
///
///     - launchHandler: The system runs the block of code for the launch handler
/// when it launches the app in the background. The block takes a single
/// parameter, a ``BGTask`` object used for assigning an expiration handler and
/// for setting a completion status. The block has no return value.
///
/// - Returns: Returns
/// <doc://com.apple.documentation/documentation/objectivec/yes> if the launch
/// handler was registered. Returns
/// <doc://com.apple.documentation/documentation/objectivec/no> if the
/// identifier isn't included in the
/// <doc://com.apple.documentation/documentation/bundleresources/information_property_list/bgtaskschedulerpermittedidentifiers>
/// `Info.plist`.
- (BOOL)registerForTaskWithIdentifier:(NSString *)identifier usingQueue:(nullable dispatch_queue_t)queue launchHandler:(void (^)(__kindof BGTask *task))launchHandler NS_EXTENSION_UNAVAILABLE("Only the host application may register launch handlers");

/*!
 @abstract Submit a request to be launched in the background to perform work.
 @param taskRequest The task request object representing the parameters of the background task to be scheduled.
 @param error If an error occurs, upon return contains an error object that indicates why the request was rejected.
 @discussion Submitting a task request with the same identifier as an existing request will replace that request.
 @return YES if the request was successfully submitted, NO if there was an error
 */

/// Submit a previously registered background task for execution.
///
/// Submitting a task request for an unexecuted task that’s already in the queue
/// replaces the previous task request.
///
/// There can be a total of 1 refresh task and 10 processing tasks scheduled at
/// any time. Trying to schedule more tasks returns
/// ``BGTaskSchedulerErrorCode/BGTaskSchedulerErrorCodeTooManyPendingTaskRequests``.
///
/// - Parameters:
///     - taskRequest: A background task request object specifying the task
///     - error: On input, a pointer to an error object. If an error occurs, this pointer is set to an error object containing the error information. Specify `nil` for this parameter to ignore the error information.
/// identifier and optional configuration information.
- (BOOL)submitTaskRequest:(BGTaskRequest *)taskRequest error:(NSError * _Nullable *)error;

/*!
 @abstract Cancel a previously submitted task request.
 @param identifier The identifier of the previously submitted task request to cancel.
 */

/// Cancel a previously scheduled task request.
///
/// - Parameters:
///   - identifier: The string identifier of the task request to cancel.
- (void)cancelTaskRequestWithIdentifier:(NSString *)identifier;

/*!
 @abstract Cancel all previously submitted task requests.
 */

/// Cancel all scheduled task requests.
- (void)cancelAllTaskRequests;

/*!
 @abstract Returns a list of all task requests that have been submitted but not yet completed.
 @param completionHandler A block for processing task requests. This block may be executed on a background thread. The block has no return value and takes a single parameter, taskRequests, which is an array of BGTaskRequest objects. If there are no pending requests, this array is empty. The task request objects returned are copies and changing their property values will have no immediate effect. To modify the parameters of a pending task request, submit it again to the scheduler with submitTaskRequest:error:.
 */

/// Request a list of unexecuted scheduled task requests.
///
/// - Parameters:
///     - completionHandler: The completion handler called with the pending tasks.
/// The handler may execute on a background thread.
///
/// The handler takes a single parameter `tasksRequests`, an array of `BGTaskRequest`
/// objects. The array is empty if there are no scheduled tasks.
///
/// The objects passed in the array are copies of the existing requests. Changing the
/// attributes of a request has no effect. To change the attributes submit a new
/// task request using ``BGTaskScheduler/submitTaskRequest:error:``.
- (void)getPendingTaskRequestsWithCompletionHandler:(void (^)(NSArray<BGTaskRequest *> *taskRequests))completionHandler;

@end

NS_ASSUME_NONNULL_END
