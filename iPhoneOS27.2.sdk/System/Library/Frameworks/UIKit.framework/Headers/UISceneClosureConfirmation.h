#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UISceneClosureConfirmation.h>)
//
//  UISceneClosureConfirmation.h
//  UIKit
//
//  Copyright © 2026 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UISceneDefinitions.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

@class UIAlertAction;

/// A configuration specifying a confirmation dialog that will be shown before a
/// user action will result in destruction of the scene session and the disconnection of the scene.
///
/// By default, the confirmation dialog includes a "Close" button (which closes the scene)
/// and a "Cancel" button (which keeps the scene open). You can replace either of these
/// default buttons by providing custom actions. Use a `UIAlertAction` with style
///  `.destructive` to replace the "Close" button, or style `.cancel` to replace
///  the "Cancel" button.
///
/// Example:
///
/// A property of this type is found on `UIWindowScene`.
/// A scene setting its `closureConfirmation` may look something like
/// ```
/// let closeAction = UIAlertAction(title:"End meeting for all", style:.destructive, handler: nil)
/// let cancelAction = UIAlertAction(title:"Stay in meeting", style:.cancel, handler:nil)
/// let myAction = UIAlertAction(title:"Leave & Assign new host", style:.default) { action in
///    // work to do before the window closes
/// }
/// var closureConfirmation: UISceneClosureConfirmation =
///    UISceneClosureConfirmation(title:"Leave or End meeting?",
///                               message:"You are the host. Would you like to end the meeting for all participants?",
///                               actions:[closeAction, cancelAction, myAction])
///
/// windowScene.closureConfirmation = closureConfirmation
/// ```
/// With this property set, upon user initiated close, the system will present the closure confirmation dialog.
UIKIT_EXTERN UIKIT_FINAL NS_SWIFT_UI_ACTOR API_AVAILABLE(ios(27.0)) API_UNAVAILABLE(tvos, watchos, visionos)
@interface UISceneClosureConfirmation : NSObject<NSCopying, NSSecureCoding>

/// Creates a scene closure confirmation with the provided parameters.
///
/// - Parameters:
///   - title: The title of the confirmation. If not provided, defaults to a generic localized title.
///   - message: Optional descriptive text that provides more details.
///   - actions: Actions to be included in the confirmation dialog. Close and Cancel are shown by default.
+ (instancetype)confirmationWithTitle:(nullable NSString *)title
                              message:(nullable NSString *)message
                              actions:(NSArray<UIAlertAction *> *)actions;

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

@end

NS_HEADER_AUDIT_END(nullability, sendability)

#else
#import <UIKitCore/UISceneClosureConfirmation.h>
#endif
