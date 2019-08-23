//
//  UIInterface.h
//  UIKit
//
//  Copyright (c) 2005-2015 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKitDefines.h>
#import <UIKit/UIColor.h>
#import <UIKit/UIFont.h>

// for UINavigationBar and UIToolBar

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSInteger, UIBarStyle) {
    UIBarStyleDefault          = 0,
    UIBarStyleBlack            = 1,
    
    UIBarStyleBlackOpaque      = 1, // Deprecated. Use UIBarStyleBlack
    UIBarStyleBlackTranslucent = 2, // Deprecated. Use UIBarStyleBlack and set the translucent property to YES
} __TVOS_PROHIBITED;

typedef NS_ENUM(NSInteger, UIUserInterfaceSizeClass) {
    UIUserInterfaceSizeClassUnspecified = 0,
    UIUserInterfaceSizeClassCompact     = 1,
    UIUserInterfaceSizeClassRegular     = 2,
} NS_ENUM_AVAILABLE_IOS(8_0);

// System colors

@interface UIColor (UIColorSystemColors)
+ (UIColor *)lightTextColor __TVOS_PROHIBITED;                // for a dark background
+ (UIColor *)darkTextColor __TVOS_PROHIBITED;                 // for a light background

+ (UIColor *)groupTableViewBackgroundColor __TVOS_PROHIBITED;

+ (UIColor *)viewFlipsideBackgroundColor NS_DEPRECATED_IOS(2_0, 7_0) __TVOS_PROHIBITED;
+ (UIColor *)scrollViewTexturedBackgroundColor NS_DEPRECATED_IOS(3_2, 7_0) __TVOS_PROHIBITED;
+ (UIColor *)underPageBackgroundColor NS_DEPRECATED_IOS(5_0, 7_0) __TVOS_PROHIBITED;
@end

// System fonts

@interface UIFont (UIFontSystemFonts)
+ (CGFloat)labelFontSize __TVOS_PROHIBITED;
+ (CGFloat)buttonFontSize __TVOS_PROHIBITED;
+ (CGFloat)smallSystemFontSize __TVOS_PROHIBITED;
+ (CGFloat)systemFontSize __TVOS_PROHIBITED;
@end

NS_ASSUME_NONNULL_END
