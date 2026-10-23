#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UIArrangementViewController.h>)
//
//  UIArrangementViewController.h
//  UIKit
//
//  Copyright © 2026 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIGeometry.h>
#import <UIKit/UIKitDefines.h>
#import <UIKit/UIViewController.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

/// A placement of a view within an arrangement view controller.
/// Use this type to define placement for container views within the arrangement view controller.
typedef NS_ENUM(NSInteger, UIArrangementViewControllerViewPlacement) {
    UIArrangementViewControllerViewPlacementNone,
    UIArrangementViewControllerViewPlacementPrimary,
    UIArrangementViewControllerViewPlacementSecondary
} NS_REFINED_FOR_SWIFT API_AVAILABLE(ios(27.1), tvos(27.1), visionos(27.1))
API_UNAVAILABLE(watchos);

/// The state of a view within an arrangement.
UIKIT_EXTERN
API_AVAILABLE(ios(27.1), tvos(27.1), visionos(27.1))
API_UNAVAILABLE(watchos)
NS_REFINED_FOR_SWIFT
NS_SWIFT_UI_ACTOR
@interface UIArrangementViewState : NSObject <NSCopying>

/// The z-index of the view within the arrangement.
@property (nonatomic, readonly) NSInteger zIndex;

/// The axis of the split for the view within a split arrangement.
@property (nonatomic, readonly) UIAxis splitAxis;

/// Whether the view is hidden in the arrangement.
@property (nonatomic, readonly, getter=isHidden) BOOL hidden;

- (instancetype)init NS_UNAVAILABLE;

@end

/// An arrangement of views within an arrangement view controller.
UIKIT_EXTERN
API_AVAILABLE(ios(27.1), tvos(27.1), visionos(27.1))
API_UNAVAILABLE(watchos)
NS_REFINED_FOR_SWIFT
NS_SWIFT_UI_ACTOR
@interface UIArrangement : NSObject <NSCopying>

- (instancetype)init NS_UNAVAILABLE;

@end

/// A view controller that presents its container view controllers through an arrangement.
UIKIT_EXTERN
API_AVAILABLE(ios(27.1), tvos(27.1), visionos(27.1))
API_UNAVAILABLE(watchos)
NS_SWIFT_UI_ACTOR
@interface UIArrangementViewController : UIViewController

- (instancetype)init NS_DESIGNATED_INITIALIZER;

/// Updates the arrangement of the view controller.
///
/// - parameter arrangement: The arrangement to apply.
/// - parameter animated: Whether to animate the arrangement transition.
- (void)updateArrangement:(UIArrangement *)arrangement animated:(BOOL)animated NS_REFINED_FOR_SWIFT;

/// Updates the arrangement of the view controller.
///
/// - parameter arrangement: The arrangement to apply.
- (void)updateArrangement:(UIArrangement *)arrangement NS_REFINED_FOR_SWIFT;

/// Returns the arrangement view state for a placement.
///
/// - parameter placement: The placement of the view controller.
- (nullable UIArrangementViewState *)stateForPlacement:(UIArrangementViewControllerViewPlacement)placement NS_REFINED_FOR_SWIFT;

/// The view controller in the arrangement for the provided placement.
///
/// - parameter placement: The placement of the view controller.
- (nullable UIViewController *)viewControllerForPlacement:(UIArrangementViewControllerViewPlacement)placement NS_REFINED_FOR_SWIFT;

/// The placement for the provided view controller in the arrangement.
/// Will return `UIArrangementViewControllerViewPlacementNone` if the provided view
/// controller is not a view controller provided to the arrangement view controller with an explicit
/// placement.
///
/// - parameter viewController: The view controller in the arrangement.
- (UIArrangementViewControllerViewPlacement)placementForViewController:(UIViewController *)viewController NS_REFINED_FOR_SWIFT;

/// Sets the view controller in the arrangement for a specific placement.
///
/// - parameter viewController: The view controller in the arrangement.
/// - parameter placement: The placement of the view controller in the arrangement.
/// - parameter animated: Whether to animate the view controller transition.
- (void)setViewController:(nullable UIViewController *)viewController forPlacement:(UIArrangementViewControllerViewPlacement)placement animated:(BOOL)animated NS_REFINED_FOR_SWIFT;

/// Sets the view controller in the arrangement for a specific placement.
///
/// - parameter viewController: The view controller in the arrangement.
/// - parameter placement: The placement of the view controller in the arrangement.
- (void)setViewController:(nullable UIViewController *)viewController forPlacement:(UIArrangementViewControllerViewPlacement)placement NS_REFINED_FOR_SWIFT;

@end

@interface UIViewController (UIArrangementViewController)

/// The nearest ancestor arrangement view controller.
@property (nonatomic, readonly, nullable) UIArrangementViewController *arrangementViewController
    API_AVAILABLE(ios(27.1), tvos(27.1), visionos(27.1))
    API_UNAVAILABLE(watchos);

@end

NS_HEADER_AUDIT_END(nullability, sendability)

#else
#import <UIKitCore/UIArrangementViewController.h>
#endif
