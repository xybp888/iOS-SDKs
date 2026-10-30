//
//  PHSharedAlbumCustomizationViewController.h
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

@class PHSharedAlbumCustomizationViewController;

NS_ASSUME_NONNULL_BEGIN
API_AVAILABLE_BEGIN(ios(27), macos(27), visionos(27))
API_UNAVAILABLE_BEGIN(tvos, watchos)

/**
 * @abstract A set of methods that the delegate must implement to respond to `PHSharedAlbumCustomizationViewController` events.
 */
NS_SWIFT_NAME(PHSharedAlbumCustomizationViewController.Delegate)
@protocol PHSharedAlbumCustomizationViewControllerDelegate <NSObject>

/**
 * @abstract Called when shared album customization completes.
 *
 * @discussion `error` will be `nil` if customization was successful and non-`nil` if it was unsuccessful. The view controller won't be dismissed automatically when this method is called.
 */
- (void)sharedAlbumCustomizationViewController:(PHSharedAlbumCustomizationViewController *)customizationViewController didCompleteWithError:(nullable NSError *)error;

@end

#if TARGET_OS_OSX
/**
 * @abstract This class is used to present the shared album customization view from AppKit-based view controllers.
 *
 * @discussion Only the system photo library is supported, so `albumIdentifier` must be for an album in the system photo library. If `albumIdentifier` is from a different library, showing a customization sheet will fail.
 */
@interface PHSharedAlbumCustomizationViewController: NSViewController
#else
/**
 * @abstract This class is used to present the shared album customization view from UIKit-based view controllers.
 *
 * @discussion Only the system photo library is supported, so `albumIdentifier` must be for an album in the system photo library. If `albumIdentifier` is from a different library, showing a customization sheet will fail.
 */
@interface PHSharedAlbumCustomizationViewController: UIViewController
#endif

/**
 * @abstract Returns a view controller that allows the user to customize a specified shared album.
 *
 * @discussion Only the system photo library is supported, so `albumIdentifier` must be for an album in the system photo library. If `albumIdentifier` is from a different library, showing a customization sheet will fail.
 *
 * @param albumIdentifier The identifier of the shared album to be customized.
 * @param photoLibrary The photo library in which the specified shared album exists.
 */
- (instancetype)initWithAlbumIdentifier:(NSString *)albumIdentifier photoLibrary:(PHPhotoLibrary *)photoLibrary NS_DESIGNATED_INITIALIZER;

/// The delegate to respond to `PHSharedAlbumCustomizationViewController` events.
@property (nonatomic, weak, nullable) id<PHSharedAlbumCustomizationViewControllerDelegate> delegate;

/// The identifier of the shared album to be customized.
@property (nonatomic, copy, readonly) NSString *albumIdentifier;

- (instancetype)init NS_UNAVAILABLE;
- (instancetype)initWithNibName:(nullable NSString *)nibNameOrNil bundle:(nullable NSBundle *)nibBundleOrNil NS_UNAVAILABLE;
- (nullable instancetype)initWithCoder:(NSCoder *)coder NS_UNAVAILABLE;

@end

API_UNAVAILABLE_END // tvos, watchos
API_AVAILABLE_END // ios(27), macos(27), visionos(27)
NS_ASSUME_NONNULL_END
