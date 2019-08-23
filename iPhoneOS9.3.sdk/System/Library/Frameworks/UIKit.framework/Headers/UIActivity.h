//
//  UIActivity.h
//  UIKit
//
//  Copyright 2012-2015 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKitDefines.h>

NS_ASSUME_NONNULL_BEGIN

@class UIImage, UIViewController;

UIKIT_EXTERN NSString *const UIActivityTypePostToFacebook     NS_AVAILABLE_IOS(6_0) __TVOS_PROHIBITED;
UIKIT_EXTERN NSString *const UIActivityTypePostToTwitter      NS_AVAILABLE_IOS(6_0) __TVOS_PROHIBITED;
UIKIT_EXTERN NSString *const UIActivityTypePostToWeibo        NS_AVAILABLE_IOS(6_0) __TVOS_PROHIBITED;    // SinaWeibo
UIKIT_EXTERN NSString *const UIActivityTypeMessage            NS_AVAILABLE_IOS(6_0) __TVOS_PROHIBITED;
UIKIT_EXTERN NSString *const UIActivityTypeMail               NS_AVAILABLE_IOS(6_0) __TVOS_PROHIBITED;
UIKIT_EXTERN NSString *const UIActivityTypePrint              NS_AVAILABLE_IOS(6_0) __TVOS_PROHIBITED;
UIKIT_EXTERN NSString *const UIActivityTypeCopyToPasteboard   NS_AVAILABLE_IOS(6_0) __TVOS_PROHIBITED;
UIKIT_EXTERN NSString *const UIActivityTypeAssignToContact    NS_AVAILABLE_IOS(6_0) __TVOS_PROHIBITED;
UIKIT_EXTERN NSString *const UIActivityTypeSaveToCameraRoll   NS_AVAILABLE_IOS(6_0) __TVOS_PROHIBITED;
UIKIT_EXTERN NSString *const UIActivityTypeAddToReadingList   NS_AVAILABLE_IOS(7_0) __TVOS_PROHIBITED;
UIKIT_EXTERN NSString *const UIActivityTypePostToFlickr       NS_AVAILABLE_IOS(7_0) __TVOS_PROHIBITED;
UIKIT_EXTERN NSString *const UIActivityTypePostToVimeo        NS_AVAILABLE_IOS(7_0) __TVOS_PROHIBITED;
UIKIT_EXTERN NSString *const UIActivityTypePostToTencentWeibo NS_AVAILABLE_IOS(7_0) __TVOS_PROHIBITED;
UIKIT_EXTERN NSString *const UIActivityTypeAirDrop            NS_AVAILABLE_IOS(7_0) __TVOS_PROHIBITED;
UIKIT_EXTERN NSString *const UIActivityTypeOpenInIBooks       NS_AVAILABLE_IOS(9_0) __TVOS_PROHIBITED;

typedef NS_ENUM(NSInteger, UIActivityCategory) {
    UIActivityCategoryAction,
    UIActivityCategoryShare,
} NS_ENUM_AVAILABLE_IOS(7_0) __TVOS_PROHIBITED;

NS_CLASS_AVAILABLE_IOS(6_0) __TVOS_PROHIBITED @interface UIActivity : NSObject

// override methods

+ (UIActivityCategory)activityCategory NS_AVAILABLE_IOS(7_0); // default is UIActivityCategoryAction.

- (nullable NSString *)activityType;       // default returns nil. subclass may override to return custom activity type that is reported to completion handler
- (nullable NSString *)activityTitle;      // default returns nil. subclass must override and must return non-nil value
- (nullable UIImage *)activityImage;       // default returns nil. subclass must override and must return non-nil value

- (BOOL)canPerformWithActivityItems:(NSArray *)activityItems;   // override this to return availability of activity based on items. default returns NO
- (void)prepareWithActivityItems:(NSArray *)activityItems;      // override to extract items and set up your HI. default does nothing

- (nullable UIViewController *)activityViewController;   // return non-nil to have view controller presented modally. call activityDidFinish at end. default returns nil
- (void)performActivity;                        // if no view controller, this method is called. call activityDidFinish when done. default calls [self activityDidFinish:NO]

// state method

- (void)activityDidFinish:(BOOL)completed;   // activity must call this when activity is finished
@end

NS_ASSUME_NONNULL_END
