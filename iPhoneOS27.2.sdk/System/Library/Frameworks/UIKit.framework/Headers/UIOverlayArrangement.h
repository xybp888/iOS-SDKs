#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UIOverlayArrangement.h>)
//
//  UIOverlayArrangement.h
//  UIKit
//
//  Copyright © 2026 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIArrangementViewController.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

/// The view properties for an overlay arrangement view.
UIKIT_EXTERN
API_AVAILABLE(ios(27.1), tvos(27.1), visionos(27.1))
API_UNAVAILABLE(watchos)
NS_REFINED_FOR_SWIFT
NS_SWIFT_UI_ACTOR
@interface UIOverlayArrangementViewProperties : NSObject <NSCopying>

/// The edge the view occupies when the overlay arrangement transitions to a side-by-side layout.
@property (nonatomic) NSDirectionalRectEdge edge;

- (instancetype)init NS_DESIGNATED_INITIALIZER;

@end

/// An arrangement that overlays views.
UIKIT_EXTERN
API_AVAILABLE(ios(27.1), tvos(27.1), visionos(27.1))
API_UNAVAILABLE(watchos)
NS_REFINED_FOR_SWIFT
NS_SWIFT_UI_ACTOR
@interface UIOverlayArrangement : UIArrangement

/// Returns an overlay arrangement.
+ (instancetype)overlayArrangement NS_SWIFT_NAME(overlayArrangement());

/// The supported axes of the arrangement.
@property (nonatomic) UIAxis axes;

/// Returns the default properties for a view in the overlay arrangement.
@property (nonatomic, copy, readonly) UIOverlayArrangementViewProperties *defaultViewProperties;

/// Sets the view properties in the overlay arrangement for a specific placement.
///
/// - parameter viewProperties: The view properties in the arrangement.
/// - parameter placement: The placement of the properties in the arrangement.
- (void)setViewProperties:(UIOverlayArrangementViewProperties *)viewProperties forPlacement:(UIArrangementViewControllerViewPlacement)placement;

- (instancetype)init NS_UNAVAILABLE;

@end

NS_HEADER_AUDIT_END(nullability, sendability)

#else
#import <UIKitCore/UIOverlayArrangement.h>
#endif
