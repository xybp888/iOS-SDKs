#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIFoundation/NSShadow.h>)
//
//  NSShadow.h
//  Text Kit
//
//  Copyright (c) 2002-2025, Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreGraphics/CoreGraphics.h>
#import <UIKit/UIKitDefines.h>

@class UIColor;

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

/*
 NSShadow stores the properties of a drop shadow for drawing text.
 To set a shadow on an NSAttributedString use it as a value for NSShadowAttributeName.
 */

UIKIT_EXTERN API_AVAILABLE(macos(10.0), ios(6.0), watchos(2.0), tvos(9.0), visionos(1.0))
@interface NSShadow : NSObject <NSCopying, NSSecureCoding>

- (instancetype)init NS_DESIGNATED_INITIALIZER; // designated initializer, returns a default shadow with zero offset, zero blur radius, and default color
- (nullable instancetype)initWithCoder:(NSCoder *)coder NS_DESIGNATED_INITIALIZER;

@property (NS_NONATOMIC_IOSONLY) CGSize shadowOffset;      // offset in user space of the shadow from the original drawing
@property (NS_NONATOMIC_IOSONLY) CGFloat shadowBlurRadius; // blur radius of the shadow in default user space units
@property (nullable, copy, NS_NONATOMIC_IOSONLY) id shadowColor;           // color used for the shadow (default is black with an alpha value of 1/3)

@end

NS_HEADER_AUDIT_END(nullability, sendability)
#else
#import <UIFoundation/NSShadow.h>
#endif
