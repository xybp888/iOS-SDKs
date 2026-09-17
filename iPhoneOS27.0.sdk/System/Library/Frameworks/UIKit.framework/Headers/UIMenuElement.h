#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UIMenuElement.h>)
//
//  UIMenuElement.h
//  UIKit
//
//  Copyright © 2019 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKitDefines.h>

@class UIImage;

typedef NS_ENUM(NSInteger, UIMenuElementState) {
    UIMenuElementStateOff,
    UIMenuElementStateOn,
    UIMenuElementStateMixed
} API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos);

typedef NS_OPTIONS(NSUInteger, UIMenuElementAttributes) {
    UIMenuElementAttributesDisabled     = 1 << 0,
    UIMenuElementAttributesDestructive  = 1 << 1,
    UIMenuElementAttributesHidden       = 1 << 2,
    
    /// Indicates that the menu should remain presented after firing
    /// the element's action rather than dismissing as it normally does.
    /// This attribute has no effect on Mac Catalyst.
    UIMenuElementAttributesKeepsMenuPresented API_AVAILABLE(ios(16.0)) API_UNAVAILABLE(watchos) = 1 << 3
} API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos);

/// Possible repeat behaviors for a menu element.
typedef NS_ENUM(NSInteger, UIMenuElementRepeatBehavior) {
    /// Automatically uses the appropriate repeat behavior for this element.
    UIMenuElementRepeatBehaviorAutomatic = 0,
    /// The element should be allowed to repeat.
    UIMenuElementRepeatBehaviorRepeatable,
    /// The element should not be repeatable.
    UIMenuElementRepeatBehaviorNonRepeatable,
} API_AVAILABLE(ios(26.0)) API_UNAVAILABLE(watchos) NS_SWIFT_NAME(UIMenuElement.RepeatBehavior);

/// Visibility options for a menu element's image.
typedef NS_ENUM(NSInteger, UIMenuElementImageVisibility) {
    /// The element's image visibility is determined by the platform and context.
    UIMenuElementImageVisibilityAutomatic = 0,
    /// The element prefers its image to be visible, even in contexts where
    /// images are not shown by default.
    UIMenuElementImageVisibilityVisible = 1,
    /// The element prefers its image to be hidden, even in contexts where
    /// images are shown by default.
    UIMenuElementImageVisibilityHidden = 2,
} API_AVAILABLE(ios(27.0)) API_UNAVAILABLE(watchos) NS_SWIFT_NAME(UIMenuElement.ImageVisibility);

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

UIKIT_EXTERN API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos) NS_SWIFT_UI_ACTOR
@interface UIMenuElement : NSObject <NSCopying, NSSecureCoding>

/// The element's title.
@property (nonatomic, readonly) NSString *title;

/// The element's subtitle.
@property (nonatomic, nullable, copy) NSString *subtitle API_AVAILABLE(ios(15.0)) API_UNAVAILABLE(watchos);

/// Image to be displayed alongside the element's title.
@property (nonatomic, nullable, readonly) UIImage *image;

/// The preferred visibility of the element's image.
@property (nonatomic) UIMenuElementImageVisibility preferredImageVisibility API_AVAILABLE(ios(27.0)) API_UNAVAILABLE(watchos);

/// This block gets called when the element is being highlighted or unhighlighted in a menu.
/// @param element The element being highlighted or unhighlighted.
/// @param isHighlighted YES when the element is highlighted, NO when unhighlighted.
@property (nonatomic, copy, nullable) void (^highlightStateUpdateHandler)(UIMenuElement *element, BOOL isHighlighted) API_AVAILABLE(ios(27.0)) API_UNAVAILABLE(watchos);

- (nullable instancetype)initWithCoder:(NSCoder *)coder NS_DESIGNATED_INITIALIZER;

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

NS_HEADER_AUDIT_END(nullability, sendability)

#else
#import <UIKitCore/UIMenuElement.h>
#endif
