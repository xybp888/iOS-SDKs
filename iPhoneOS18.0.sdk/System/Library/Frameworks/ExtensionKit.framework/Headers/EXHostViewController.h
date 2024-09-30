//
//  EXHostViewController.h
//  ExtensionKit
//

#import <ExtensionFoundation/ExtensionFoundation.h>
#import <Foundation/Foundation.h>

#if !TARGET_OS_WATCH

#if TARGET_OS_OSX
#import <AppKit/AppKit.h>
#else
#import <UIKit/UIKit.h>
#endif

NS_ASSUME_NONNULL_BEGIN

@protocol EXHostViewControllerDelegate;

API_AVAILABLE(macos(13.0))
API_UNAVAILABLE(ios, watchos, tvos)
#if defined(TARGET_OS_VISION) && TARGET_OS_VISION
API_UNAVAILABLE(visionos)
#endif
EXTENSIONKIT_EXPORT
#if TARGET_OS_OSX
/// A view controller that hosts remote views provided by an extension.
@interface EXHostViewController : NSViewController
#else
/// A view controller that hosts remote views provided by an extension.
@interface EXHostViewController : UIViewController
#endif

/// The connection delegate.
@property (weak, nonatomic, nullable) id<EXHostViewControllerDelegate> delegate;

#if TARGET_OS_OSX
/// A view that’s used when the view controller has no content to display.
@property (strong, nonatomic) NSView* placeholderView;
#else
/// A view that’s used when the view controller has no content to display.
@property (strong, nonatomic) UIView* placeholderView;
#endif

/// Attempts to connect to the extension over XPC.
///
/// - Returns: An object representing the connection.
-(nullable NSXPCConnection*)makeXPCConnectionWithError:(NSError* __nullable*)error;

@end

API_AVAILABLE(macos(13.0))
API_UNAVAILABLE(ios, watchos, tvos)
#if defined(TARGET_OS_VISION) && TARGET_OS_VISION
API_UNAVAILABLE(visionos)
#endif
/// The delegate for a hosted view controller.
@protocol EXHostViewControllerDelegate <NSObject>
@optional

/// A delegate method the view controller calls when a connection succeeds.
///
/// This delegate method gets called when the extension process has launched and
/// the remote scene connects. After this delegate method gets called the host
/// view controller can establish an XPC connection with the scene in the
/// extension process.
///
/// - Parameters:
///   - viewController: The user interface object from the remote process.
-(void)hostViewControllerDidActivate:(EXHostViewController*)viewController NS_SWIFT_UI_ACTOR;

/// A delegate method the host view controller calls when an extension
/// disconnects.
///
/// Called when the host view controller stops hosting the remote user
/// interface. This can occur when the extension exits or when the view
/// controller’s configuration property changes.
///
/// - Parameters:
///   - viewController: The view controller for the extension that’s disconnecting
///
///   - error: An error object containing information about why the object
/// disconnected, or `nil` if it’s disconnecting without error.
-(void)hostViewControllerWillDeactivate:(EXHostViewController*)viewController error:(nullable NSError *)error NS_SWIFT_UI_ACTOR;

@end

NS_ASSUME_NONNULL_END

#endif // !TARGET_OS_WATCH
