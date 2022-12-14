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

/// A view controller that will host remote UI provided by an extension.
API_AVAILABLE(macos(13.0))
API_UNAVAILABLE(ios, watchos, tvos)
EXTENSIONKIT_EXPORT
#if TARGET_OS_OSX
@interface EXHostViewController : NSViewController
#else
@interface EXHostViewController : UIViewController
#endif

/// The view controller's delegate. The delegate will receive callbacks when the hosting state changes.
@property (weak, nonatomic, nullable) id<EXHostViewControllerDelegate> delegate;

/// A placeholder view that will be displayed while the remote UI is being loaded or if the remote process exits.
#if TARGET_OS_OSX
@property (strong, nonatomic) NSView* placeholderView;
#else
@property (strong, nonatomic) UIView* placeholderView;
#endif

/// Returns the connection, the caller is responsible for configuring the connection.
-(nullable NSXPCConnection*)makeXPCConnectionWithError:(NSError* __nullable*)error;

@end

/// The host view controller delegate will receive callbacks when the host view controller's state changes.
API_AVAILABLE(macos(13.0))
API_UNAVAILABLE(ios, watchos, tvos)
@protocol EXHostViewControllerDelegate <NSObject>
@optional

/// Called when extension process has launched and the remote scene is connected. After this delegate method has been called the host view controller can establish an XPC connection with the scene in the extension process.
-(void)hostViewControllerDidActivate:(EXHostViewController*)viewController;

/// Called when the view controller will stop hosting the remote user interface. This can occur when the extension exits or when the view controller's `configuration` property is changed.
-(void)hostViewControllerWillDeactivate:(EXHostViewController*)viewController error:(nullable NSError *)error;

@end

NS_ASSUME_NONNULL_END

#endif // !TARGET_OS_WATCH
