#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UISceneAccessoryRegistration.h>)
//
//  UISceneAccessoryRegistration.h
//  UIKit
//
//  Copyright © 2026 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKitDefines.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

/// A type which represents the registration for a given scene accessory.
///
/// Instances of this type allow for observing availability of a given scene accessory,
/// as well as controlling whether the contents should be displayed when the system determines the scene is available.
UIKIT_EXTERN NS_SWIFT_UI_ACTOR
API_AVAILABLE(ios(27.0))
API_UNAVAILABLE(macCatalyst, tvos, visionos, watchos)
@interface UISceneAccessoryRegistration : NSObject
/// Whether the associated scene accessory is available for display by the system or not.
///
/// This value is observable during the `updateProperties` and `layoutSubviews` lifecycle events.
@property (nonatomic, readonly, getter=isAvailable) BOOL available;

/// Whether the content defined by this scene accessory should be displayed or not.
///
/// This value does not reflect the availability of the scene accessory, which is determined by the system.
@property (nonatomic, readwrite, getter=isEnabled) BOOL enabled;

- (instancetype)init NS_UNAVAILABLE;

@end


NS_HEADER_AUDIT_END(nullability, sendability)

#else
#import <UIKitCore/UISceneAccessoryRegistration.h>
#endif
