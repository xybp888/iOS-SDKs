#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UIViewReservedRegion.h>)
//
//  UIViewReservedRegion.h
//  UIKit
//
//  Copyright © 2026 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIGeometry.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

@class UIViewReservedRegionIdentifier;
@class UIViewReservedRegionKind;

/// A region within a view's coordinate space that has been reserved by another entity.
UIKIT_EXTERN UIKIT_FINAL API_AVAILABLE(ios(27.1), tvos(27.1), visionos(27.1)) API_UNAVAILABLE(watchos)
NS_REFINED_FOR_SWIFT
@interface UIViewReservedRegion : NSObject <NSCopying>

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

/// The identifier of the region.
@property (nonatomic, readonly) UIViewReservedRegionIdentifier *identifier;

/// The kind of the region.
@property (nonatomic, readonly) UIViewReservedRegionKind *kind;

/// The rect of the region in the view's coordinate space, including the margins.
@property (nonatomic, readonly) CGRect frame;

/// The margins included in the frame around the reserved rect for interactive content.
@property (nonatomic, readonly) UIEdgeInsets margins;

/// Whether the region is currently active.
@property (nonatomic, readonly, getter=isActive) BOOL active;

@end

/// An identifier of a reserved region.
UIKIT_EXTERN UIKIT_FINAL API_AVAILABLE(ios(27.1), tvos(27.1), visionos(27.1)) API_UNAVAILABLE(watchos)
NS_REFINED_FOR_SWIFT
@interface UIViewReservedRegionIdentifier : NSObject <NSCopying>

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

@end

/// A kind of reserved region.
UIKIT_EXTERN UIKIT_FINAL API_AVAILABLE(ios(27.1), tvos(27.1), visionos(27.1)) API_UNAVAILABLE(watchos)
NS_REFINED_FOR_SWIFT
@interface UIViewReservedRegionKind : NSObject <NSCopying>

/// A region that is occluded by an element.
+ (instancetype)occlusionRegionKind;

/// A region where an element should divide into two separate regions.
+ (instancetype)divisionRegionKind;

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

@end

/// Options for querying reserved regions.
typedef NS_OPTIONS(NSUInteger, UIViewReservedRegionQueryOptions) {
    /// No reserved region query options.
    UIViewReservedRegionQueryOptionsNone = 0,
    /// Include inactive reserved regions.
    UIViewReservedRegionQueryOptionsIncludeInactive = 1 << 0

} API_AVAILABLE(ios(27.1), tvos(27.1), visionos(27.1)) API_UNAVAILABLE(watchos) NS_REFINED_FOR_SWIFT;

NS_HEADER_AUDIT_END(nullability, sendability)

#else
#import <UIKitCore/UIViewReservedRegion.h>
#endif
