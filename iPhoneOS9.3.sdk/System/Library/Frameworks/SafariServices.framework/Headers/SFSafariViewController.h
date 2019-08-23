//
//  SFSafariViewController.h
//  SafariServices
//
//  Copyright © 2015 Apple Inc. All rights reserved.
//

#import <SafariServices/SFFoundation.h>
#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

@protocol SFSafariViewControllerDelegate;

/*!
 @class SFSafariViewController
 A view controller for displaying web content in a Safari-like interface with some of Safari’s features. The
 web content in SFSafariViewController shares cookie and website data with web content opened in Safari.
 */
NS_CLASS_AVAILABLE_IOS(9_0)
@interface SFSafariViewController : UIViewController

/*! @abstract The view controller's delegate */
@property (nonatomic, weak, nullable) id<SFSafariViewControllerDelegate> delegate;

- (instancetype)init NS_UNAVAILABLE;
- (instancetype)initWithCoder:(NSCoder *)aDecoder NS_UNAVAILABLE;
- (instancetype)initWithNibName:(nullable NSString *)nibNameOrNil bundle:(nullable NSBundle *)nibBundleOrNil NS_UNAVAILABLE;

/*! @abstract Returns a view controller that loads a URL.
    @param URL, the URL to navigate to.
    @param entersReaderIfAvailable indicates if the Safari Reader version of content should be shown automatically
    when Safari Reader is available on a web page
 */
- (instancetype)initWithURL:(NSURL *)URL entersReaderIfAvailable:(BOOL)entersReaderIfAvailable NS_DESIGNATED_INITIALIZER;

/*! @abstract Returns a view controller that loads a URL.
    @param URL, the URL to navigate to.
 */
- (instancetype)initWithURL:(NSURL *)URL;

@end

NS_AVAILABLE_IOS(9_0)
@protocol SFSafariViewControllerDelegate <NSObject>
@optional

/*! @abstract Called when the view controller is about to show UIActivityViewController after the user taps the action button.
    @param URL, the URL of the web page.
    @param title, the title of the web page.
    @result Returns an array of UIActivity instances that will be appended to UIActivityViewController.
 */
- (NSArray<UIActivity *> *)safariViewController:(SFSafariViewController *)controller activityItemsForURL:(NSURL *)URL title:(nullable NSString *)title;

/*! @abstract Delegate callback called when the user taps the Done button. Upon this call, the view controller is dismissed modally. */
- (void)safariViewControllerDidFinish:(SFSafariViewController *)controller;

/*! @abstract Invoked when the initial URL load is complete.
    @param success YES if loading completed successfully, NO if loading failed.
    @discussion This method is invoked when SFSafariViewController completes the loading of the URL that you pass
    to its initializer. It is not invoked for any subsequent page loads in the same SFSafariViewController instance.
 */
- (void)safariViewController:(SFSafariViewController *)controller didCompleteInitialLoad:(BOOL)didLoadSuccessfully;

@end

NS_ASSUME_NONNULL_END
