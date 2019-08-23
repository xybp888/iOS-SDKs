//
//  UIFocus.h
//  UIKit
//
//  Copyright © 2015 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UILayoutGuide.h>
#import <UIKit/UIFocusAnimationCoordinator.h>

@class UIView;

typedef NS_OPTIONS(NSUInteger, UIFocusHeading) {
    UIFocusHeadingUp            = 1 << 0,
    UIFocusHeadingDown          = 1 << 1,
    UIFocusHeadingLeft          = 1 << 2,
    UIFocusHeadingRight         = 1 << 3,
    UIFocusHeadingNext          = 1 << 4,
    UIFocusHeadingPrevious      = 1 << 5,
} NS_ENUM_AVAILABLE_IOS(9_0);


NS_ASSUME_NONNULL_BEGIN

/// UIFocusUpdateContexts provide information relevant to a specific focus update from one view to another. They are ephemeral objects that are usually discarded after the update is finished.
NS_CLASS_AVAILABLE_IOS(9_0) @interface UIFocusUpdateContext : NSObject

/// The view that was focused before the update. May be nil if no view was focused, such as when setting initial focus.
@property (nonatomic, weak, readonly, nullable) UIView *previouslyFocusedView;

/// The view that will be focused after the update. May be nil if no view will be focused.
@property (nonatomic, weak, readonly, nullable) UIView *nextFocusedView;

/// The focus heading in which the update is occuring.
@property (nonatomic, assign, readonly) UIFocusHeading focusHeading;

@end


/// UIFocusEnvironments represent branches of the view hierarchy participating in the focus system.
NS_CLASS_AVAILABLE_IOS(9_0) @protocol UIFocusEnvironment <NSObject>

/// The preferred focused view is the view that will be focused when focus is updated programmatically. This includes setting initial focus and forcing updates via -updateFocusIfNeeded. May be self in the case of UIView instances.
@property (nonatomic, weak, readonly, nullable) UIView *preferredFocusedView;

/// Marks this environment as needing a focus update, which if accepted will reset focus to the preferred focused view on the next update cycle. If this environment does not currently contain the focused view, then calling this method has no effect. If a parent of this environment is also requesting focus, then that parent's preferred focused view is used instead.
- (void)setNeedsFocusUpdate;

/// Forces focus to be updated immediately. If there is an environment that has requested a focus update via -setNeedsFocusUpdate, and the request was accepted, then focus will be updated to that environment's preferred focused view.
- (void)updateFocusIfNeeded;

/// Asks whether the system should allow a focus update to occur.
- (BOOL)shouldUpdateFocusInContext:(UIFocusUpdateContext *)context;

/// Called when the screen’s focusedView has been updated to a new view. Use the animation coordinator to schedule focus-related animations in response to the update.
- (void)didUpdateFocusInContext:(UIFocusUpdateContext *)context withAnimationCoordinator:(UIFocusAnimationCoordinator *)coordinator;

@end


/// UIFocusGuides are UILayoutGuide subclasses that participate in the focus system from within their owning view. A UIFocusGuide may be used to expose non-view areas as focusable.
NS_CLASS_AVAILABLE_IOS(9_0) @interface UIFocusGuide : UILayoutGuide

/// If disabled, UIFocusGuides are ignored by the focus engine, but still participate in layout. Modifying this flag allows you to conditionally enable or disable certain focus behaviors. YES by default.
@property (nonatomic, getter=isEnabled) BOOL enabled;

/// Setting a preferred focused view marks this guide's layoutFrame as focusable, and if focused, redirects focus to its preferred focused view. If nil, this guide is effectively disabled.
@property (nonatomic, weak, nullable) UIView *preferredFocusedView;

@end

NS_ASSUME_NONNULL_END
