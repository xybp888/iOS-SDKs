//
//  WKExtension.h
//  WatchKit
//
//  Copyright (c) 2015 Apple Inc. All rights reserved.
//

#if TARGET_OS_WATCH

#import <WatchKit/WKDefines.h>

NS_ASSUME_NONNULL_BEGIN

@protocol WKExtensionDelegate;
@class HKWorkoutConfiguration;
@class UNNotification;
@class UILocalNotification;
@class WKRefreshBackgroundTask;

WK_AVAILABLE_WATCHOS_ONLY(2.0)
@interface WKExtension : NSObject

+ (WKExtension *)sharedExtension;

- (void)openSystemURL:(NSURL *)url;

@property (nonatomic, weak, nullable) id<WKExtensionDelegate> delegate;
@property (nonatomic, readonly, nullable) WKInterfaceController *rootInterfaceController;

typedef NS_ENUM(NSInteger, WKApplicationState) {
    WKApplicationStateActive,
    WKApplicationStateInactive,
    WKApplicationStateBackground,
} WK_AVAILABLE_WATCHOS_ONLY(3.0);
@property (nonatomic, readonly) WKApplicationState applicationState WK_AVAILABLE_WATCHOS_ONLY(3.0);

@end

WK_AVAILABLE_WATCHOS_ONLY(2.0)
@protocol WKExtensionDelegate <NSObject>

@optional

- (void)applicationDidFinishLaunching;
- (void)applicationDidBecomeActive;
- (void)applicationWillResignActive;
- (void)applicationWillEnterForeground;
- (void)applicationDidEnterBackground;

// iOS app started a workout. -[HKHealthStore startWorkoutSession:] should be called from here
- (void)handleWorkoutConfiguration:(HKWorkoutConfiguration *)workoutConfiguration WK_AVAILABLE_WATCHOS_ONLY(3.0);

- (void)handleUserActivity:(nullable NSDictionary *)userInfo;
- (void)handleActivity:(NSUserActivity *)userActivity WK_AVAILABLE_WATCHOS_ONLY(3.2);

- (void)handleBackgroundTasks:(NSSet <WKRefreshBackgroundTask *> *)backgroundTasks WK_AVAILABLE_WATCHOS_ONLY(3.0);

// deprecated
- (void)handleActionWithIdentifier:(nullable NSString *)identifier forRemoteNotification:(NSDictionary *)remoteNotification WK_DEPRECATED_WATCHOS(2.0, 3.0, "use UNUserNotificationCenterDelegate");
- (void)handleActionWithIdentifier:(nullable NSString *)identifier forLocalNotification:(UILocalNotification *)localNotification WK_DEPRECATED_WATCHOS(2.0, 3.0, "use UNUserNotificationCenterDelegate");
- (void)handleActionWithIdentifier:(nullable NSString *)identifier forRemoteNotification:(NSDictionary *)remoteNotification withResponseInfo:(NSDictionary *)responseInfo WK_DEPRECATED_WATCHOS(2.0, 3.0, "use UNUserNotificationCenterDelegate");
- (void)handleActionWithIdentifier:(nullable NSString *)identifier forLocalNotification:(UILocalNotification *)localNotification withResponseInfo:(NSDictionary *)responseInfo WK_DEPRECATED_WATCHOS(2.0, 3.0, "use UNUserNotificationCenterDelegate");
- (void)didReceiveRemoteNotification:(NSDictionary *)userInfo WK_DEPRECATED_WATCHOS(2.0, 3.0, "use UNUserNotificationCenterDelegate");
- (void)didReceiveLocalNotification:(UILocalNotification *)notification WK_DEPRECATED_WATCHOS(2.0, 3.0, "use UNUserNotificationCenterDelegate");

@end

NS_ASSUME_NONNULL_END

#endif // TARGET_OS_WATCH
