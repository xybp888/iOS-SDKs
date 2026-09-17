#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UIBarMinimization.h>)
//
//  UIBarMinimization.h
//  UIKit
//
//  Copyright © 2026 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

typedef NS_ENUM(NSInteger, UIBarMinimizationBehavior) {
    /// The system determines the minimization behavior.
    UIBarMinimizationBehaviorAutomatic = 0,
    /// Bar minimization is disabled.
    UIBarMinimizationBehaviorNever API_AVAILABLE(ios(27.0)) API_UNAVAILABLE(visionos) API_UNAVAILABLE(watchos, tvos),
    /// Minimize when the user scrolls down.
    UIBarMinimizationBehaviorOnScrollDown API_AVAILABLE(ios(27.0)) API_UNAVAILABLE(visionos) API_UNAVAILABLE(watchos, tvos),
    /// Minimize when the user scrolls up.
    UIBarMinimizationBehaviorOnScrollUp API_AVAILABLE(ios(27.0)) API_UNAVAILABLE(visionos) API_UNAVAILABLE(watchos, tvos),
} API_AVAILABLE(ios(27.0), tvos(27.0), visionos(27.0)) API_UNAVAILABLE(watchos);

typedef NS_ENUM(NSInteger, UIBarMinimizationSafeAreaAdjustment) {
    /// The system determines the safe area adjustment.
    UIBarMinimizationSafeAreaAdjustmentAutomatic = 0,
    /// The safe area adjusts as bars minimize, allowing content to reflow.
    UIBarMinimizationSafeAreaAdjustmentEnabled API_AVAILABLE(ios(27.0)) API_UNAVAILABLE(visionos) API_UNAVAILABLE(watchos, tvos),
    /// The safe area remains unchanged as bars minimize.
    UIBarMinimizationSafeAreaAdjustmentDisabled API_AVAILABLE(ios(27.0)) API_UNAVAILABLE(visionos) API_UNAVAILABLE(watchos, tvos),
} API_AVAILABLE(ios(27.0), tvos(27.0), visionos(27.0)) API_UNAVAILABLE(watchos);

typedef NS_ENUM(NSInteger, UIBarMinimizationRestorationBehavior) {
    /// The system determines the restoration behavior.
    ///
    /// By default, the bar restores when the user reverses scroll direction.
    /// The system selects ``UIBarMinimizationRestorationBehaviorAtScrollEdge``
    /// automatically for navigation items whose `preferredSearchBarPlacement`
    /// is `.integratedCentered`.
    UIBarMinimizationRestorationBehaviorAutomatic = 0,
    /// The bar restores only when the observed scroll view's content reaches the scroll edge.
    ///
    /// Currently this is only honored alongside
    /// ``UIBarMinimizationBehaviorOnScrollDown``. With other minimization
    /// behaviors, the system falls back to ``UIBarMinimizationRestorationBehaviorAutomatic``.
    UIBarMinimizationRestorationBehaviorAtScrollEdge API_AVAILABLE(ios(27.0)) API_UNAVAILABLE(visionos) API_UNAVAILABLE(watchos, tvos),
} API_AVAILABLE(ios(27.0), tvos(27.0), visionos(27.0)) API_UNAVAILABLE(watchos);

/// A configuration that controls how a navigation bar minimizes in response to scrolling.
///
/// Access this configuration through ``UINavigationItem/navigationBarMinimization``
/// and set its properties to customize minimization.
UIKIT_EXTERN NS_SWIFT_UI_ACTOR NS_REFINED_FOR_SWIFT
API_AVAILABLE(ios(27.0), tvos(27.0), visionos(27.0)) API_UNAVAILABLE(watchos)
@interface UIBarMinimization : NSObject <NSCopying, NSSecureCoding>

/// The minimization behavior.
///
/// When the navigation bar minimizes, an integrated top tab bar will also minimize.
///
/// The default value is ``UIBarMinimizationBehaviorAutomatic``.
@property (nonatomic, assign) UIBarMinimizationBehavior minimizationBehavior;

/// The safe area adjustment during minimization.
///
/// Currently, only the navigation bar supports customizing the safe area adjustment.
///
/// The default value is ``UIBarMinimizationSafeAreaAdjustmentAutomatic``.
@property (nonatomic, assign) UIBarMinimizationSafeAreaAdjustment safeAreaAdjustment;

/// The restoration behavior.
///
/// Use this property alongside ``minimizationBehavior`` to control when a
/// minimized navigation bar restores. By default the bar restores when the
/// user reverses scroll direction; with ``UIBarMinimizationRestorationBehaviorAtScrollEdge``,
/// the bar instead restores only when the scroll view's content reaches the
/// scroll edge. Currently only honored in combination with
/// ``UIBarMinimizationBehaviorOnScrollDown``.
///
/// The default value is ``UIBarMinimizationRestorationBehaviorAutomatic``.
@property (nonatomic, assign) UIBarMinimizationRestorationBehavior restorationBehavior;

@end


NS_HEADER_AUDIT_END(nullability, sendability)

#else
#import <UIKitCore/UIBarMinimization.h>
#endif
