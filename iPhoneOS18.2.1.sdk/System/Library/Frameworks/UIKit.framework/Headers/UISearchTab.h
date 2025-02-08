#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UISearchTab.h>)
//
//  UISearchTab.h
//  UIKit
//
//  Copyright © 2024 Apple Inc. All rights reserved.
//

#import <UIKit/UITab.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

UIKIT_EXTERN NS_SWIFT_UI_ACTOR
API_AVAILABLE(ios(18.0), tvos(18.0), visionos(2.0)) API_UNAVAILABLE(watchos)
@interface UISearchTab : UITab

/// Creates a search tab with a system localized title and image.
- (instancetype)initWithViewControllerProvider:(UIViewController *(^_Nullable)(__kindof UITab *))viewControllerProvider NS_DESIGNATED_INITIALIZER;

@end

NS_HEADER_AUDIT_END(nullability, sendability)

#else
#import <UIKitCore/UISearchTab.h>
#endif
