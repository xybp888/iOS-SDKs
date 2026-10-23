#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UIVerticalBarEdge.h>)
//
//  UIVerticalBarEdge.h
//  UIKit
//
//  Copyright © 2026 Apple Inc. All rights reserved.
//

#import <UIKit/UITrait.h>
#import <UIKit/UITraitCollection.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

/// The edge where the system places the vertical bar.
typedef NS_ENUM(NSInteger, UIVerticalBarEdge) {
    /// The system has no preferred edge for the vertical bar.
    UIVerticalBarEdgeUnspecified = 0,
    /// The vertical bar is on the leading edge.
    UIVerticalBarEdgeLeading API_AVAILABLE(ios(27.1)) API_UNAVAILABLE(visionos) API_UNAVAILABLE(watchos, tvos),
    /// The vertical bar is on the trailing edge.
    UIVerticalBarEdgeTrailing API_AVAILABLE(ios(27.1)) API_UNAVAILABLE(visionos) API_UNAVAILABLE(watchos, tvos),
} API_AVAILABLE(ios(27.1), tvos(27.1), visionos(27.1)) API_UNAVAILABLE(watchos);

@interface UITraitCollection (VerticalBar)

/// The edge where the system places the vertical bar.
///
/// This property reflects the system's preferred edge regardless of whether a
/// vertical bar is currently visible. Returns `UIVerticalBarEdgeUnspecified` on
/// devices and in contexts where the system never places a vertical bar — for
/// example hardware without a vertical bar, or a size class or orientation in
/// which no vertical bar is used.
@property (nonatomic, readonly) UIVerticalBarEdge verticalBarEdge
    API_AVAILABLE(ios(27.1), tvos(27.1), visionos(27.1)) API_UNAVAILABLE(watchos);

/// The system traits that affect the value of `verticalBarEdge`.
///
/// Pass this array to
/// `-registerForTraitChanges:withHandler:` to be notified when the vertical
/// bar edge changes. Note that it is possible for the actual edge to be the same
/// even if the traits affecting the vertical bar edge themselves may have changed.
@property (nonatomic, readonly, class) NSArray<UITrait> *systemTraitsAffectingVerticalBarEdge
    NS_REFINED_FOR_SWIFT API_AVAILABLE(ios(27.1), tvos(27.1), visionos(27.1)) API_UNAVAILABLE(watchos);

@end

NS_HEADER_AUDIT_END(nullability, sendability)

#else
#import <UIKitCore/UIVerticalBarEdge.h>
#endif
