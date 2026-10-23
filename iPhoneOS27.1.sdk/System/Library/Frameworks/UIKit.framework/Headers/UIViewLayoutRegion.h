#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UIViewLayoutRegion.h>)
//
//  UIViewLayoutRegion.h
//  UIKit
//
//  Copyright © 2025 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIGeometry.h>
#import <UIKit/UIKitDefines.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

typedef NS_ENUM(NSUInteger, UIViewLayoutRegionAdaptivityAxis) {
    UIViewLayoutRegionAdaptivityAxisNone,
    UIViewLayoutRegionAdaptivityAxisHorizontal,
    UIViewLayoutRegionAdaptivityAxisVertical,
} API_AVAILABLE(ios(26.0), tvos(26.0), visionos(26.0)) API_UNAVAILABLE(watchos) NS_REFINED_FOR_SWIFT;

UIKIT_EXTERN API_AVAILABLE(ios(26.0), tvos(26.0), visionos(26.0)) API_UNAVAILABLE(watchos) NS_REFINED_FOR_SWIFT
@interface UIViewLayoutRegion: NSObject

+ (UIViewLayoutRegion *)safeAreaLayoutRegionWithCornerAdaptation:(UIViewLayoutRegionAdaptivityAxis)adaptivityAxis;
+ (UIViewLayoutRegion *)marginsLayoutRegionWithCornerAdaptation:(UIViewLayoutRegionAdaptivityAxis)adaptivityAxis;
+ (UIViewLayoutRegion *)readableContentLayoutRegionWithCornerAdaptation:(UIViewLayoutRegionAdaptivityAxis)adaptivityAxis;

/// Returns a bar layout region of a given extent on a given edge.
/// @note Only a single edge is allowed per region.
+ (UIViewLayoutRegion *)layoutRegionForBarOnEdge:(UIRectEdge)edge extent:(CGFloat)extent API_AVAILABLE(ios(27.1), tvos(27.1), visionos(27.1)) API_UNAVAILABLE(watchos);

/// Returns a bar layout region of a given extent on a given directional edge.
/// @note Only a single edge is allowed per region.
+ (UIViewLayoutRegion *)layoutRegionForBarOnDirectionalEdge:(NSDirectionalRectEdge)edge extent:(CGFloat)extent API_AVAILABLE(ios(27.1), tvos(27.1), visionos(27.1)) API_UNAVAILABLE(watchos);

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

@end

NS_HEADER_AUDIT_END(nullability, sendability)

#else
#import <UIKitCore/UIViewLayoutRegion.h>
#endif
