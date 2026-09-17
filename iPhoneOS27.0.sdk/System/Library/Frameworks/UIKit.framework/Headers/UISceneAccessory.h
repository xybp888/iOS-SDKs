#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UISceneAccessory.h>)
//
//  UISceneAccessory.h
//  UIKit
//
//  Copyright © 2026 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKitDefines.h>
#import <UIKit/UIViewController.h>
#import <UIKit/UISceneConfiguration.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

/// A type which can be used to register for a specific type of scene accessory presentation.
///
/// A scene accessory declares supplementary content that the system presents on the app's behalf when an
/// associated piece of system functionality becomes available, for example when an external display is
/// connected. The app declares what content to provide; the system decides when and
/// where to present it. Scene accessories enhance the app's experience when available, but the app must
/// remain fully functional without them.
///
/// Use an instance of this type along with `UIViewController.registerSceneAccessory(_:)`.
UIKIT_EXTERN NS_SWIFT_UI_ACTOR
API_AVAILABLE(ios(27.0))
API_UNAVAILABLE(macCatalyst, tvos, visionos, watchos)
@interface UISceneAccessory : NSObject

/// Creates a new scene accessory configuration for presenting non-interactive content
/// on an external display.
///
/// When the display connects, the scene accessory's content may be presented on it.
///
/// - Parameter sceneConfiguration: A scene configuration value with delegate type defined for it.
+ (instancetype)externalNonInteractiveSceneAccessoryWithConfiguration:(UISceneConfiguration *)sceneConfiguration NS_SWIFT_NAME(externalNonInteractive(sceneConfiguration:));

/// Creates a new scene accessory configuration for presenting non-interactive content
/// on an external display.
///
/// When the display connects, the scene accessory's content may be presented on it.
///
/// This variant accepts a `userInfo` object to pass additional context to the scene delegate
/// upon connection. The `userInfo` object is accessible in the corresponding scene via
/// ``UISceneConnectionOptions.sceneAccessoryUserInfo``.
///
/// - Parameters:
///   - sceneConfiguration: A scene configuration value with delegate type defined for it.
///   - userInfo: An object that can be used to pass additional context to the scene delegate upon connection.
+ (instancetype)externalNonInteractiveSceneAccessoryWithConfiguration:(UISceneConfiguration *)sceneConfiguration userInfo:(id)userInfo NS_SWIFT_NAME(externalNonInteractive(sceneConfiguration:userInfo:));

- (instancetype)init NS_UNAVAILABLE;

@end

NS_HEADER_AUDIT_END(nullability, sendability)

#else
#import <UIKitCore/UISceneAccessory.h>
#endif
