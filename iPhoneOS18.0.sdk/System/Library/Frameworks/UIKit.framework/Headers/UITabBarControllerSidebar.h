#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UITabBarControllerSidebar.h>)
//
//  UITabBarControllerSidebar.h
//  UIKit
//
//  Copyright © 2024 Apple Inc. All rights reserved.
//

#import <UIKit/UIKitDefines.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

@protocol UITabBarControllerSidebarDelegate, UIContentConfiguration;
@class UITabSidebarScrollTarget, UITab, UITabBarController, UIView;
@class UISwipeActionsConfiguration, UIContextMenuConfiguration;

#pragma mark - UITabBarControllerSidebarLayout

typedef NS_ENUM(NSInteger, UITabBarControllerSidebarLayout) {
    /// On iOS, this resolves to `overlap`.
    /// On macOS and visionOS, this resolves to `tile`.
    UITabBarControllerSidebarLayoutAutomatic = 0,

    /// When the sidebar is displayed, it will overlap the selected view controller,
    /// allowing the selected view controller to render underneath the sidebar. Anchor
    /// the view's content to the `layoutMarginsGuide` or `safeAreaLayoutGuide` to avoid
    /// being occluded by the sidebar.
    UITabBarControllerSidebarLayoutOverlap API_UNAVAILABLE(visionos) = 1,

    /// When the sidebar is displayed, the selected view controller is resized and shifted
    /// to display alongside the sidebar. The selected view controller is not occluded by
    /// the sidebar, cannot render underneath the sidebar.
    UITabBarControllerSidebarLayoutTile = 2,
} NS_SWIFT_NAME(UITabBarControllerSidebar.Layout) API_AVAILABLE(ios(18.0), visionos(2.0)) API_UNAVAILABLE(tvos) API_UNAVAILABLE(watchos);

#pragma mark - UITabSidebarScrollTarget

UIKIT_EXTERN NS_SWIFT_UI_ACTOR NS_REFINED_FOR_SWIFT
API_AVAILABLE(ios(18.0), visionos(2.0)) API_UNAVAILABLE(tvos) API_UNAVAILABLE(watchos)
@interface UITabSidebarScrollTarget : NSObject

/// Scrolls to the `headerContentConfiguration` if it is set.
+ (instancetype)targetForHeader;

/// Scrolls to the `footerContentConfiguration` if it is set.
+ (instancetype)targetForFooter;

/// Scrolls to the item representing the tab if it exists.
+ (instancetype)targetForTab:(UITab *)tab;

@end

#pragma mark - UITabBarControllerSidebar

UIKIT_EXTERN NS_SWIFT_UI_ACTOR
API_AVAILABLE(ios(18.0), visionos(2.0)) API_UNAVAILABLE(tvos) API_UNAVAILABLE(watchos)
NS_SWIFT_NAME(UITabBarController.Sidebar)
@interface UITabBarControllerSidebar : NSObject

/// The object managing the delegate of the sidebar.
@property (nonatomic, weak, nullable) id<UITabBarControllerSidebarDelegate> delegate;

/// Determines if the sidebar is currently hidden.
@property (nonatomic, assign, getter=isHidden) BOOL hidden;

#pragma mark Layout

/// The preferred layout for how the sidebar lays out with the tab bar controller's
/// content. Default is `.automatic`
@property (nonatomic, assign) UITabBarControllerSidebarLayout preferredLayout;

#pragma mark Content

/// Content configuration for an optional header to display in the sidebar.
/// The header is displayed above all tab content in the sidebar.
@property (nonatomic, copy, nullable) id<UIContentConfiguration> headerContentConfiguration NS_REFINED_FOR_SWIFT;

/// Content configuration for an optional header to display in the sidebar.
/// The footer is displayed below all tab content in the sidebar.
@property (nonatomic, copy, nullable) id<UIContentConfiguration> footerContentConfiguration NS_REFINED_FOR_SWIFT;

/// A view to display at the bottom of the sidebar, like a UIToolbar. The width of this view
/// will be managed by the sidebar itself, and its height will be set to the value it returns
/// from `systemLayoutSizeFittingSize:withHorizontalFittingPriority:verticalFittingPriority:`
/// Default is nil.
@property (nonatomic, strong, nullable) UIView *bottomBarView;

/// Scrolls to the specified target in the sidebar with an option to animate the change.
- (void)scrollToTarget:(UITabSidebarScrollTarget *)target animated:(BOOL)animated NS_REFINED_FOR_SWIFT;

/// Requests the sidebar reconfigure the item representing the specified tab. This method has no effect if the `tab` is not
/// currently displayed in the sidebar.
- (void)reconfigureItemForTab:(UITab *)tab;

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

#pragma mark - UITabBarControllerSidebarAnimating

API_AVAILABLE(ios(18.0), visionos(2.0)) API_UNAVAILABLE(tvos) API_UNAVAILABLE(watchos)  NS_SWIFT_UI_ACTOR
NS_SWIFT_NAME(UITabBarControllerSidebar.Animating)
@protocol UITabBarControllerSidebarAnimating <NSObject>

- (void)addAnimations:(void (^)(void))animations;
- (void)addCompletion:(void (^)(void))completion NS_SWIFT_DISABLE_ASYNC;

@end

#pragma mark - UITabBarControllerSidebarDelegate

@class UITabSidebarItem, UITabSidebarItemRequest;

API_AVAILABLE(ios(18.0), visionos(2.0)) API_UNAVAILABLE(tvos) API_UNAVAILABLE(watchos)
NS_SWIFT_NAME(UITabBarControllerSidebar.Delegate)
@protocol UITabBarControllerSidebarDelegate <NSObject>

@optional

/// Notifies the delegate when the visibility of the sidebar is about to change when `sidebar.isHidden` changes.
/// Add animations to the animator to run alongside the visibility update. Alongside animations and completions will run immediately
/// if the sidebar visibility is changed without animation.
- (void)tabBarController:(UITabBarController *)tabBarController sidebarVisibilityWillChange:(UITabBarControllerSidebar *)sidebar animator:(id<UITabBarControllerSidebarAnimating>)animator;

#pragma mark Configuration

/// Return a `UITabSidebarItem` for the specified item request. When created, the item will be preconfigured
/// to the appropriate defaults for its given content. If this method is not implemented, a default sidebar
/// item will be provided for the request.
- (UITabSidebarItem *)tabBarController:(UITabBarController *)tabBarController
                               sidebar:(UITabBarControllerSidebar *)sidebar
                        itemForRequest:(UITabSidebarItemRequest *)request;

/// Called whenever the sidebar item's `configurationState` changes or the item is reconfigured.
/// The passed in item will accure all modifications until the delegate requests for a new sidebar
/// item from the delegate method `tabBarController:sidebar:itemForRequest:`
- (void)tabBarController:(UITabBarController *)tabBarController
                 sidebar:(UITabBarControllerSidebar *)sidebar
              updateItem:(UITabSidebarItem *)item;

#pragma mark Item Display Callbacks

/// Notifies the delegate when the sidebar is about to display the row representing the specified `tab`
- (void)tabBarController:(UITabBarController *)tabBarController sidebar:(UITabBarControllerSidebar *)sidebar willBeginDisplayingTab:(__kindof UITab *)tab;

/// Notifies the delegate when the sidebar has finished displaying the row representing the specified `tab`
- (void)tabBarController:(UITabBarController *)tabBarController sidebar:(UITabBarControllerSidebar *)sidebar didEndDisplayingTab:(__kindof UITab *)tab;

#pragma mark Interactions

/// Called when the sidebar is about to show leading swipe actions for the specified `tab`.
/// Return either a concrete `UISwipeActionsConfiguration` or nil if the tab does not show swipe actions.
- (nullable UISwipeActionsConfiguration *)tabBarController:(UITabBarController *)tabBarController
                                                   sidebar:(UITabBarControllerSidebar *)sidebar
                    leadingSwipeActionsConfigurationForTab:(__kindof UITab *)tab API_UNAVAILABLE(tvos);

/// Called when the sidebar is about to show trailing swipe actions for a particular tab.
/// Return either a UISwipeActionsConfiguration object or nil if this tab does not show swipe actions.
- (nullable UISwipeActionsConfiguration *)tabBarController:(UITabBarController *)tabBarController
                                                   sidebar:(UITabBarControllerSidebar *)sidebar
                   trailingSwipeActionsConfigurationForTab:(__kindof UITab *)tab API_UNAVAILABLE(tvos);

/// Called when the sidebar is about to display a context menu for the specified `tab`.
/// Return either a concrete `UIContextMenuConfiguration` or nil if the tab does not show context menus.
- (nullable UIContextMenuConfiguration *)tabBarController:(UITabBarController *)tabBarController
                                                  sidebar:(UITabBarControllerSidebar *)sidebar
                           contextMenuConfigurationForTab:(__kindof UITab *)tab;

@end

NS_HEADER_AUDIT_END(nullability, sendability)

#else
#import <UIKitCore/UITabBarControllerSidebar.h>
#endif
