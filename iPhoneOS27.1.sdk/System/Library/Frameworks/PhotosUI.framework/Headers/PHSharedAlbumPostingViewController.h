//
//  PHSharedAlbumPostingViewController.h
//  PhotosUI
//
//  Copyright © 2026 Apple Inc. All rights reserved.
//

#if TARGET_OS_OSX
#import <AppKit/AppKit.h>
#else
#import <UIKit/UIKit.h>
#endif
#import <Photos/Photos.h>
#import <PhotosUI/PhotosUI.h>

@class PHSharedAlbumPostingViewController;

NS_ASSUME_NONNULL_BEGIN
API_AVAILABLE_BEGIN(ios(27), macos(27), visionos(27))
API_UNAVAILABLE_BEGIN(tvos, watchos)

/**
 * @abstract A set of methods that the delegate must implement to respond to `PHSharedAlbumPostingViewController` events.
 */
NS_SWIFT_NAME(PHSharedAlbumPostingViewController.Delegate)
@protocol PHSharedAlbumPostingViewControllerDelegate <NSObject>

/**
 * @abstract Called when asset posting has completed.
 *
 * @discussion `error` will be `nil` if asset posting was successful and non-`nil` if it was unsuccessful. The view controller won't be dismissed automatically when this method is called.
 */
- (void)sharedAlbumPostingViewController:(PHSharedAlbumPostingViewController *)postingViewController didCompleteWithError:(nullable NSError *)error;

@end

#if TARGET_OS_OSX
/**
 * @abstract This class is used to present a view for posting assets to a shared album from AppKit-based view controllers.
 */
@interface PHSharedAlbumPostingViewController: NSViewController
#else
/**
 * @abstract This class is used to present a view for posting assets to a shared album from UIKit-based view controllers.
 */
@interface PHSharedAlbumPostingViewController: UIViewController
#endif

/**
 * @abstract Returns a view controller that allows the user to create a new shared album.
 *
 * @param items The items to be posted to the shared album.
 * @param defaultAlbumIdentifier Identifier for the shared album to be pre-selected. If none provided, the user can manually choose a shared album.
 * @param photoLibrary The photo library to choose from.
 */
- (instancetype)initWithItems:(NSArray<PHPickerResult *> *)items defaultAlbumIdentifier:(nullable NSString *)defaultAlbumIdentifier photoLibrary:(PHPhotoLibrary *)photoLibrary NS_DESIGNATED_INITIALIZER NS_REFINED_FOR_SWIFT;

/// The delegate to respond to `PHSharedAlbumPostingViewController` events.
@property (nonatomic, weak, nullable) id<PHSharedAlbumPostingViewControllerDelegate> delegate;

/// The identifier of the shared album that was posted to.
@property (nonatomic, copy, nullable, readonly) NSString *albumIdentifier;

- (instancetype)init NS_UNAVAILABLE;
- (instancetype)initWithNibName:(nullable NSString *)nibNameOrNil bundle:(nullable NSBundle *)nibBundleOrNil NS_UNAVAILABLE;
- (nullable instancetype)initWithCoder:(NSCoder *)coder NS_UNAVAILABLE;

@end

API_UNAVAILABLE_END // tvos, watchos
API_AVAILABLE_END // ios(27), macos(27), visionos(27)
NS_ASSUME_NONNULL_END
