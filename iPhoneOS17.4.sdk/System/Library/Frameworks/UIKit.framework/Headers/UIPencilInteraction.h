#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UIPencilInteraction.h>)
//
//  UIPencilInteraction.h
//  UIKit
//
//  Copyright © 2018 Apple Inc. All rights reserved.
//

#import <UIKit/UIInteraction.h>
#import <UIKit/UIKitDefines.h>

#pragma mark - Preferred Actions

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

/// Preferred actions available to the user in Settings.
typedef NS_ENUM(NSInteger, UIPencilPreferredAction) {

    /// No action, or the user has disabled pencil interactions in Accessibility settings
    UIPencilPreferredActionIgnore = 0,
    
    /// Switch between the current tool and eraser
    UIPencilPreferredActionSwitchEraser,
    
    /// Switch between the current tool and the previously used tool
    UIPencilPreferredActionSwitchPrevious,
    
    /// Show and hide the color palette
    UIPencilPreferredActionShowColorPalette,
    
    /// Show the ink attributes palette
    UIPencilPreferredActionShowInkAttributes API_AVAILABLE(ios(16.0)) API_UNAVAILABLE(tvos, watchos),

} API_AVAILABLE(ios(12.1)) API_UNAVAILABLE(watchos, tvos);

#pragma mark - Interaction

@protocol UIPencilInteractionDelegate;

UIKIT_EXTERN API_AVAILABLE(ios(12.1)) API_UNAVAILABLE(visionos) API_UNAVAILABLE(watchos, tvos) NS_SWIFT_UI_ACTOR
@interface UIPencilInteraction : NSObject <UIInteraction>

/// The user’s preferred double-tap action as set in Settings app
@property (class, nonatomic, readonly) UIPencilPreferredAction preferredTapAction;

/// The user's preference for drawing with pencil only as set in Settings app or the system tool picker
@property (class, nonatomic, readonly) BOOL prefersPencilOnlyDrawing;

/// The interaction's delegate
@property (nonatomic, weak, nullable) id <UIPencilInteractionDelegate> delegate;

/// Whether the interaction is enabled or not
@property (nonatomic, getter=isEnabled) BOOL enabled;

@end

#pragma mark - Interaction Delegate

UIKIT_EXTERN API_AVAILABLE(ios(12.1)) API_UNAVAILABLE(watchos, tvos) API_UNAVAILABLE(visionos) NS_SWIFT_UI_ACTOR
@protocol UIPencilInteractionDelegate <NSObject>

@optional

/// Called when the user taps on the side of the pencil, if the interaction's view is in a visible view hierarchy.
///
/// The delegate may do anything in this method.  To perform the user's preferred action (as set in Settings),
/// consult the `preferredTapAction` class property of `UIPencilInteraction`.
- (void)pencilInteractionDidTap:(UIPencilInteraction *)interaction;

@end

NS_HEADER_AUDIT_END(nullability, sendability)

#else
#import <UIKitCore/UIPencilInteraction.h>
#endif
