//
//  UNNotificationCategory.h
//  UserNotifications
//
//  Copyright © 2015 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

@class UNNotificationAction;

NS_ASSUME_NONNULL_BEGIN

typedef NS_OPTIONS(NSUInteger, UNNotificationCategoryOptions) {
    UNNotificationCategoryOptionNone = (0),
    
    // Whether dismiss action should be sent to the UNUserNotificationCenter delegate
    UNNotificationCategoryOptionCustomDismissAction = (1 << 0),
    
    // Whether notifications of this category should be allowed in CarPlay
    UNNotificationCategoryOptionAllowInCarPlay = (2 << 0),

} __IOS_AVAILABLE(10.0) __WATCHOS_AVAILABLE(3.0) __TVOS_PROHIBITED;

__IOS_AVAILABLE(10.0) __WATCHOS_AVAILABLE(3.0) __TVOS_PROHIBITED
@interface UNNotificationCategory : NSObject <NSCopying, NSSecureCoding>

// The unique identifier for this category. The UNNotificationCategory's actions will be displayed on notifications when the UNNotificationCategory's identifier matches the UNNotificationRequest's categoryIdentifier.
@property (NS_NONATOMIC_IOSONLY, readonly, copy) NSString *identifier;

// The UNNotificationActions in the order they will be displayed.
@property (NS_NONATOMIC_IOSONLY, readonly, copy) NSArray<UNNotificationAction *> *actions;

// The intents supported support for notifications of this category. See <Intents/INIntentIdentifiers.h> for possible values.
@property (NS_NONATOMIC_IOSONLY, readonly, copy) NSArray<NSString *> *intentIdentifiers;

@property (NS_NONATOMIC_IOSONLY, readonly) UNNotificationCategoryOptions options;

+ (instancetype)categoryWithIdentifier:(NSString *)identifier actions:(NSArray<UNNotificationAction *> *)actions intentIdentifiers:(NSArray<NSString *> *)intentIdentifiers options:(UNNotificationCategoryOptions)options;

- (instancetype)init NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
