//
//  WKBackgroundTask.h
//  WatchKit
//
//  Copyright (c) 2016 Apple. All rights reserved.
//

#if TARGET_OS_WATCH

#import <ClockKit/ClockKit.h>
#import <WatchKit/WatchKit.h>
#import <WatchKit/WKExtension.h>

NS_ASSUME_NONNULL_BEGIN

// If the app fails to complete its background tasks within the allocated time,
// the system terminates the app and generates a crash report.
// These crash reports contain a unique exception code that describes the reason for the crash.
// To address these issues, decrease the amount of work that the app performs while running in the background.
//
// 0xc51bad01 - The app used too much CPU time
// 0xc51bad02 - The app used too much wall time
// 0xc51bad03 - The app did not receive sufficient runtime due to other system tasks.
//

WK_AVAILABLE_WATCHOS_ONLY(3.0)
@interface WKRefreshBackgroundTask : NSObject
@property (readonly, nullable) id<NSSecureCoding> userInfo;

- (void)setTaskCompleted;   // developer should call this when this task has been completed
@end

WK_AVAILABLE_WATCHOS_ONLY(3.0)
@interface WKApplicationRefreshBackgroundTask : WKRefreshBackgroundTask
@end

WK_AVAILABLE_WATCHOS_ONLY(3.0)
@interface WKSnapshotRefreshBackgroundTask : WKRefreshBackgroundTask
@property (readonly) BOOL returnToDefaultState;

// developer should call setTaskCompletedWithDefaultStateRestored when preparation for snapshot has been completed
// restoredDefaultState             -   YES if the app is its default state
// estimatedSnapshotExpiration      -      Date at which the snapshot should be scheduled for replacement.
//                                         If nil then the snapshot needs to be replaced asap.
//                                         Use [NSDate distantFuture] if the snapshot doesn't need to be replaced.
// userInfo                         -   Will be returned with the task that eventually runs
- (void)setTaskCompletedWithDefaultStateRestored:(BOOL)restoredDefaultState
                     estimatedSnapshotExpiration:(nullable NSDate *)estimatedSnapshotExpiration
                                        userInfo:(nullable id<NSSecureCoding>)userInfo
NS_SWIFT_NAME(setTaskCompleted(restoredDefaultState:estimatedSnapshotExpiration:userInfo:));

@end

WK_AVAILABLE_WATCHOS_ONLY(3.0)
@interface WKURLSessionRefreshBackgroundTask : WKRefreshBackgroundTask
@property (readonly, copy) NSString *sessionIdentifier;
@end

WK_AVAILABLE_WATCHOS_ONLY(3.0)
@interface WKWatchConnectivityRefreshBackgroundTask : WKRefreshBackgroundTask
@end

@interface WKExtension (WKBackgroundTasks)

// there can only be one background refresh request at any given time. Scheduling a second request will cancel the previously scheduled request
- (void)scheduleBackgroundRefreshWithPreferredDate:(NSDate *)preferredFireDate userInfo:(nullable id<NSSecureCoding>)userInfo scheduledCompletion:(void(^)(NSError * _Nullable error))scheduledCompletion WK_AVAILABLE_WATCHOS_ONLY(3.0);

// there can only be one snapshot refresh request at any given time. Scheduling a second request will cancel the previously scheduled request
- (void)scheduleSnapshotRefreshWithPreferredDate:(NSDate *)preferredFireDate userInfo:(nullable id<NSSecureCoding>)userInfo scheduledCompletion:(void(^)(NSError * _Nullable error))scheduledCompletion WK_AVAILABLE_WATCHOS_ONLY(3.0);

@end

NS_ASSUME_NONNULL_END

#endif //TARGET_OS_WATCH
