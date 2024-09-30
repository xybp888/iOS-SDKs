//
//  BGTaskRequest.h
//  BackgroundTasks
//
//  Copyright © 2019 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <BackgroundTasks/BGDefines.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 @abstract An abstract class that represents a request for the app to be launched in the background to perform work.
 @discussion Do not instantiate instances of this class directly. Instead, use one of its concrete subclasses.
 */
BG_EXTERN API_AVAILABLE(ios(13.0), tvos(13.0)) API_UNAVAILABLE(macos, watchos)
/// An abstract class for representing task requests.
@interface BGTaskRequest : NSObject <NSCopying>
/*!
 @abstract The identifier associated with this request.
 */

/// The identifier of the task associated with the request.
@property (readonly, copy) NSString *identifier;

/*!
 @abstract The earliest date at which the task may run.
 @discussion Setting this property does not guarantee that the task will begin at the specified date, but only that it will not begin sooner. If not specified, no start delay is used.
 */

/// The earliest date and time at which to run the task.
///
/// Specify `nil` for no start delay.
///
/// Setting the property indicates that the background task shouldn’t start any
/// earlier than this date. However, the system doesn’t guarantee launching the
/// task at the specified date, but only that it won’t begin sooner.
@property (copy, nullable) NSDate *earliestBeginDate;

- (instancetype)init NS_UNAVAILABLE; // This is an abstract type and should not be directly instantiated
+ (instancetype)new NS_UNAVAILABLE; // This is an abstract type and should not be directly instantiated
@end

/*!
 @abstract A request to briefly launch your app to keep its contents up to date.
 @discussion Schedule a refresh task request to ask that the system launch your app briefly so that you can download data and keep your app's contents up-to-date. The system will fulfill this request intelligently based on system conditions and app usage.
 */

/// A request to launch your app in the background to execute a short refresh task.
BG_EXTERN API_AVAILABLE(ios(13.0), tvos(13.0)) API_UNAVAILABLE(macos, watchos)
@interface BGAppRefreshTaskRequest : BGTaskRequest

/// Return a new refresh task request for the specified identifier.
///
/// - Parameters:
///     - identifier: The string identifier of the refresh task associated with the request.
- (instancetype)initWithIdentifier:(NSString *)identifier;

@end

/*!
 @abstract A request to launch your app to perform deferrable processing tasks.
 @discussion Schedule a processing task request to ask that the system launch your app when conditions are favorable for battery life to handle deferrable, longer-running processing, such as syncing, database maintenance, or similar tasks. The system will attempt to fulfill this request to the best of its ability within the next two days as long as the user has used your app within the past week.
 */

/// A request to launch your app in the background to execute a processing task
/// that can take minutes to complete.
BG_EXTERN API_AVAILABLE(ios(13.0), tvos(13.0)) API_UNAVAILABLE(macos, watchos)
@interface BGProcessingTaskRequest : BGTaskRequest

/// Return a new processing task request for the specified identifier.
///
/// - Parameters:
///     - identifier: The string identifier of the processing task associated with the request.
- (instancetype)initWithIdentifier:(NSString *)identifier;

/*!
 @abstract Whether the background task represented by this request requires network connectivity.
 @discussion If this property is set to YES, the system will only launch your app to fulfill this request when the device has a network connection. If this is set to NO, your app may not have network access.
 The default value is NO.
 */

/// A Boolean specifying if the processing task requires network connectivity.
@property (assign) BOOL requiresNetworkConnectivity;

/*!
 @abstract Whether the background task represented by this request should only be done while the device is connected to external power.
 @discussion If this property is set to YES, the system will launch your app to fulfill this request only while the device is connected to external power. Setting this to YES will also disable the CPU Monitor feature.
 Specify YES if this task is resource intensive to minimize impact to battery life. Please note that, even if this value is NO, the system will not necessarily schedule this task while the device is on battery power, depending on the type of device and system conditions.
 The default value is NO.
 */

/// A Boolean specifying if the processing task requires a device connected to power.
@property (assign) BOOL requiresExternalPower;

@end

/// A request to launch your app in the background to execute a health research task for studies a user has opted into and
/// that can take minutes to complete.
BG_EXTERN API_AVAILABLE(ios(17.0), tvos(17.0)) API_UNAVAILABLE(macos, watchos)
@interface BGHealthResearchTaskRequest : BGProcessingTaskRequest
/*!
 @abstract What file protection state is required to access data relevant to this task.
 @discussion Update this property to indicate what type of data needs to be accessible when the task is run.
 The default value is `NSFileProtectionCompleeUntilFirstUserAuthentication`.
 */

/// A String indicating file protection availability required for processing.
@property (assign) NSFileProtectionType protectionTypeOfRequiredData;

@end

NS_ASSUME_NONNULL_END


