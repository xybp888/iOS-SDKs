#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UISplitArrangement.h>)
//
//  UISplitArrangement.h
//  UIKit
//
//  Copyright © 2026 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIArrangementViewController.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

/// A dimension for a view within a split arrangement.
UIKIT_EXTERN
API_AVAILABLE(ios(27.1), tvos(27.1), visionos(27.1))
API_UNAVAILABLE(watchos)
NS_REFINED_FOR_SWIFT
@interface UISplitArrangementDimension : NSObject <NSCopying>

/// The automatic dimension for a split arrangement.
+ (instancetype)automaticDimension NS_SWIFT_NAME(automatic());

/// The intrinsic dimension for a split arrangement based on intrinsic content size.
+ (instancetype)intrinsicDimension NS_SWIFT_NAME(intrinsic());

/// A fractional dimension for a split arrangement.
///
/// - parameter fraction: The fraction of the container to use.
+ (instancetype)fractionalDimension:(CGFloat)fraction NS_SWIFT_NAME(fractional(_:));

/// An absolute dimension for a split arrangement.
///
/// - parameter absoluteValue: The absolute point value of the dimension.
+ (instancetype)absoluteDimension:(CGFloat)absoluteValue NS_SWIFT_NAME(absolute(_:));

- (instancetype)init NS_UNAVAILABLE;

@end

/// A range of dimensions defining the minimum, preferred, and maximum
/// size for a view within a split arrangement.
UIKIT_EXTERN
API_AVAILABLE(ios(27.1), tvos(27.1), visionos(27.1))
API_UNAVAILABLE(watchos)
NS_REFINED_FOR_SWIFT
@interface UISplitArrangementDimensionRange : NSObject <NSCopying>

/// The minimum dimension for the view.
@property (nonatomic, copy) UISplitArrangementDimension *minimum;

/// The preferred dimension for the view.
@property (nonatomic, copy) UISplitArrangementDimension *preferred;

/// The maximum dimension for the view.
@property (nonatomic, copy) UISplitArrangementDimension *maximum;

- (instancetype)init NS_DESIGNATED_INITIALIZER;

@end

/// The view properties for a split arrangement view.
UIKIT_EXTERN
API_AVAILABLE(ios(27.1), tvos(27.1), visionos(27.1))
API_UNAVAILABLE(watchos)
NS_REFINED_FOR_SWIFT
NS_SWIFT_UI_ACTOR
@interface UISplitArrangementViewProperties : NSObject <NSCopying>

/// The width dimension range for the view.
@property (nonatomic, copy) UISplitArrangementDimensionRange *width;

/// The height dimension range for the view.
@property (nonatomic, copy) UISplitArrangementDimensionRange *height;

/// The layout priority of the view within the split arrangement.
@property (nonatomic) CGFloat layoutPriority;

- (instancetype)init NS_DESIGNATED_INITIALIZER;

@end

/// An arrangement that splits views.
UIKIT_EXTERN
API_AVAILABLE(ios(27.1), tvos(27.1), visionos(27.1))
API_UNAVAILABLE(watchos)
NS_REFINED_FOR_SWIFT
NS_SWIFT_UI_ACTOR
@interface UISplitArrangement : UIArrangement

/// Returns a split arrangement.
+ (instancetype)splitArrangement NS_SWIFT_NAME(splitArrangement());

/// The axes of the arrangement.
@property (nonatomic) UIAxis axes;

/// Returns the default properties for a view in the split arrangement.
@property (nonatomic, copy, readonly) UISplitArrangementViewProperties *defaultViewProperties;

/// Sets the view properties in the split arrangement for a specific placement.
///
/// - parameter viewProperties: The view properties in the arrangement.
/// - parameter placement: The placement of the properties in the arrangement.
- (void)setViewProperties:(UISplitArrangementViewProperties *)viewProperties forPlacement:(UIArrangementViewControllerViewPlacement)placement;

- (instancetype)init NS_UNAVAILABLE;

@end

NS_HEADER_AUDIT_END(nullability, sendability)

#else
#import <UIKitCore/UISplitArrangement.h>
#endif
