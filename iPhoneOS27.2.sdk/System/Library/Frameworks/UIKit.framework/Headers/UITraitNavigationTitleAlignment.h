#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UITraitNavigationTitleAlignment.h>)
//
//  UITraitNavigationTitleAlignment.h
//  UIKit
//
//  Copyright © 2026 Apple Inc. All rights reserved.
//

#import <UIKit/UITrait.h>
#import <UIKit/UITraitCollection.h>
#import <UIKit/UINavigationItem.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

/// A trait that reports the alignment the navigation bar resolved for its title.
///
/// Read this trait from a custom navigation bar title view to discover the alignment the system
/// chose, so the view can lay out its content to match. When the system has resolved an alignment
/// the trait reports it, Leading or Center; otherwise it is Automatic.
///
/// Use the trait to align content within the size your view already reported, not to decide that
/// size. Overriding this trait's value will not change the actual alignment in the navigation bar.
/// That is controlled by `UINavigationItem.titleAlignment`.
UIKIT_EXTERN NS_REFINED_FOR_SWIFT API_AVAILABLE(ios(27.2), tvos(27.2), visionos(27.2)) API_UNAVAILABLE(watchos)
@interface UITraitNavigationTitleAlignment : NSObject <UINSIntegerTraitDefinition> // UINavigationItemTitleAlignment
@end

@interface UITraitCollection (NavigationTitleAlignment)

/// The alignment the navigation bar resolved for its title.
///
/// When the system has resolved an alignment for the title, this reports that concrete alignment,
/// Leading or Center, even when the client has not set a preference. Otherwise it reports Automatic.
@property (nonatomic, assign, readonly) UINavigationItemTitleAlignment navigationTitleAlignment API_AVAILABLE(ios(27.2), tvos(27.2), visionos(27.2)) API_UNAVAILABLE(watchos);

@end

NS_HEADER_AUDIT_END(nullability, sendability)

#else
#import <UIKitCore/UITraitNavigationTitleAlignment.h>
#endif
