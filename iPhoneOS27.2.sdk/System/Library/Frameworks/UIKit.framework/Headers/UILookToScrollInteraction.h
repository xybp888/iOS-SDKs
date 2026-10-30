#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UILookToScrollInteraction.h>)
//
//  UILookToScrollInteraction.h
//  UIKit
//
//  Copyright © 2025 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKitDefines.h>
#import <UIKit/UIInteraction.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

UIKIT_EXTERN API_AVAILABLE(visionos(27.0)) API_UNAVAILABLE(ios, watchos, tvos)
@interface UILookToScrollInteraction : NSObject <UIInteraction>

/// An interaction which specifies that the receiver should not trigger Look to Scroll.
+ (instancetype)exclusionRegionInteraction;
- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

NS_HEADER_AUDIT_END(nullability, sendability)

#else
#import <UIKitCore/UILookToScrollInteraction.h>
#endif
