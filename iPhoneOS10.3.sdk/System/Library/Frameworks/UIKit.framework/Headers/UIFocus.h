//
//  UIFocus.h
//  UIKit
//
//  Copyright © 2015-2016 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIFocusGuide.h>
#import <UIKit/UIFocusAnimationCoordinator.h>

@class UIView, UIFocusUpdateContext;

typedef NS_OPTIONS(NSUInteger, UIFocusHeading) {
    UIFocusHeadingNone          = 0,
    UIFocusHeadingUp            = 1 << 0,
    UIFocusHeadingDown          = 1 << 1,
    UIFocusHeadingLeft          = 1 << 2,
    UIFocusHeadingRight         = 1 << 3,
    UIFocusHeadingNext          = 1 << 4,
    UIFocusHeadingPrevious      = 1 << 5,
} NS_ENUM_AVAILABLE_IOS(9_0);


NS_ASSUME_NONNULL_BEGIN

/// Objects conforming to UIFocusEnvironment influence and respond to focus behavior within a specific area of the screen that they control.
NS_CLASS_AVAILABLE_IOS(9_0) @protocol UIFocusEnvironment <NSObject>

/// The preferred focus environments define where to search for the default focused item in an environment, such as when focus updates programmatically.
/// Starting from the target environment, each preferred focus environment is recursively searched in the order of the array until an eligible, focusable item is found.
/// Preferred focus environments can include focusable and non-focusable items, in addition to non-item environments. Returning an empty array is equivalent to returning an array containing only 'self'.
@property (nonatomic, copy, readonly) NSArray<id<UIFocusEnvironment>> *preferredFocusEnvironments;

/// Marks this environment as needing a focus update, which if accepted will attempt to reset focus to this environment, or one of its preferred focus environments, on the next update cycle. If this environment does not currently contain the focused item, then calling this method has no effect. If a parent of this environment is also requesting focus, then this environment's request is rejected in favor of the parent's.
- (void)setNeedsFocusUpdate;

/// Forces focus to be updated immediately. If there is an environment that has requested a focus update via -setNeedsFocusUpdate, and the request was accepted, then focus will be updated to that environment or one of its preferred focus environments.
- (void)updateFocusIfNeeded;

/// Asks whether the system should allow a focus update to occur.
- (BOOL)shouldUpdateFocusInContext:(UIFocusUpdateContext *)context;

/// Called when the screen’s focused item has been updated to a new item. Use the animation coordinator to schedule focus-related animations in response to the update.
- (void)didUpdateFocusInContext:(UIFocusUpdateContext *)context withAnimationCoordinator:(UIFocusAnimationCoordinator *)coordinator;

@optional

@property (nonatomic, weak, readonly, nullable) UIView *preferredFocusedView NS_DEPRECATED_IOS(9_0, 10_0, "Use -preferredFocusEnvironments instead.");

@end


/// Objects conforming to UIFocusItem are considered capable of participating in focus. Only UIFocusItems can ever be focused.
/// NOTE: This protocol is not currently meant to be conformed to by third-party classes.
NS_CLASS_AVAILABLE_IOS(10_0) @protocol UIFocusItem <UIFocusEnvironment>

/// Indicates whether or not this item is currently allowed to become focused.
/// Returning NO restricts the item from being focusable, even if it is visible in the user interface. For example, UIControls return NO if they are disabled.
#if UIKIT_DEFINE_AS_PROPERTIES
@property(nonatomic, readonly) BOOL canBecomeFocused;
#else
- (BOOL)canBecomeFocused;
#endif

@end


/// UIFocusUpdateContexts provide information relevant to a specific focus update from one view to another. They are ephemeral objects that are usually discarded after the update is finished.
NS_CLASS_AVAILABLE_IOS(9_0) @interface UIFocusUpdateContext : NSObject

/// The item that was focused before the update, i.e. where focus is updating from. May be nil if no item was focused, such as when focus is initially set.
@property (nonatomic, weak, readonly, nullable) id<UIFocusItem> previouslyFocusedItem NS_AVAILABLE_IOS(10_0);

/// The item that is focused after the update, i.e. where focus is updating to. May be nil if no item is being focused, meaning focus is being lost.
@property (nonatomic, weak, readonly, nullable) id<UIFocusItem> nextFocusedItem NS_AVAILABLE_IOS(10_0);

/// The view that was focused before the update. May be nil if no view was focused, such as when setting initial focus.
/// If previouslyFocusedItem is not a view, this returns that item's containing view, otherwise they are equal.
@property (nonatomic, weak, readonly, nullable) UIView *previouslyFocusedView;

/// The view that will be focused after the update. May be nil if no view will be focused.
/// If nextFocusedItem is not a view, this returns that item's containing view, otherwise they are equal.
@property (nonatomic, weak, readonly, nullable) UIView *nextFocusedView;

/// The focus heading in which the update is occuring.
@property (nonatomic, assign, readonly) UIFocusHeading focusHeading;

@end

NS_ASSUME_NONNULL_END
