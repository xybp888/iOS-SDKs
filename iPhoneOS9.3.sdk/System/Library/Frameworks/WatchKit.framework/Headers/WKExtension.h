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

WK_AVAILABLE_WATCHOS_ONLY(2.0)
@interface WKExtension : NSObject

+ (WKExtension *)sharedExtension;

- (void)openSystemURL:(NSURL *)url;

@property (nonatomic, weak, nullable) id<WKExtensionDelegate> delegate;
@property (nonatomic,readonly, nullable) WKInterfaceController *rootInterfaceController;

@end

@class UILocalNotification;

WK_AVAILABLE_WATCHOS_ONLY(2.0)
@protocol WKExtensionDelegate <NSObject>

@optional

- (void)applicationDidFinishLaunching;
- (void)applicationDidBecomeActive;
- (void)applicationWillResignActive;

- (void)handleActionWithIdentifier:(nullable NSString *)identifier forRemoteNotification:(NSDictionary *)remoteNotification; // when the app is launched from a notification. If launched from app icon in notification UI, identifier will be empty
- (void)handleActionWithIdentifier:(nullable NSString *)identifier forLocalNotification:(UILocalNotification *)localNotification; // when the app is launched from a notification. If launched from app icon in notification UI, identifier will be empty
- (void)handleActionWithIdentifier:(nullable NSString *)identifier forRemoteNotification:(NSDictionary *)remoteNotification withResponseInfo:(NSDictionary *)responseInfo; // when the app is launched from a notification. If launched from app icon in notification UI, identifier will be empty
- (void)handleActionWithIdentifier:(nullable NSString *)identifier forLocalNotification:(UILocalNotification *)localNotification withResponseInfo:(NSDictionary *)responseInfo; // when the app is launched from a notification. If launched from app icon in notification UI, identifier will be empty
- (void)handleUserActivity:(nullable NSDictionary *)userInfo;

- (void)didReceiveRemoteNotification:(NSDictionary *)userInfo;
- (void)didReceiveLocalNotification:(UILocalNotification *)notification;

@end

NS_ASSUME_NONNULL_END

#endif // TARGET_OS_WATCH
