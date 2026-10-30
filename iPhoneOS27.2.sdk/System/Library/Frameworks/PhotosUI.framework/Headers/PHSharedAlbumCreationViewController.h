//
//  PHSharedAlbumCreationViewController.h
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

@class PHSharedAlbumCreationViewController;

NS_ASSUME_NONNULL_BEGIN
API_AVAILABLE_BEGIN(ios(27), macos(27), visionos(27))
API_UNAVAILABLE_BEGIN(tvos, watchos)

/// The sharing policy for creating shared albums.
typedef NS_ENUM(NSInteger, PHSharedAlbumCreationSharingPolicy) {
    /// The policy for requiring that only people the user approves or invites are allowed to access the shared album.
    PHSharedAlbumCreationSharingPolicyPrivate,
    /// The policy for allowing anyone, without approval, to access the shared album.
    PHSharedAlbumCreationSharingPolicyPublic,
} NS_SWIFT_SENDABLE;

/// An object used to configure a `PHSharedAlbumCreationViewController`.
NS_REFINED_FOR_SWIFT
@interface PHSharedAlbumCreationConfiguration : NSObject

/// - Parameters:
///     - photoLibrary: The photo library in which the shared album will be created.
- (instancetype)initWithPhotoLibrary:(PHPhotoLibrary *)photoLibrary NS_DESIGNATED_INITIALIZER;

/// The photo library in which the shared album will be created.
@property (nonatomic, readonly) PHPhotoLibrary *photoLibrary;

/// The default title for the shared album. Useful for suggesting a relevant title to the user. Defaults to `nil`.
@property (nonatomic, copy, nullable) NSString *defaultTitle;

/// The default sharing policy of the shared album. If not specified, this defaults to `PHSharedAlbumCreationSharingPolicyPrivate`.
@property (nonatomic) PHSharedAlbumCreationSharingPolicy defaultPolicy;

- (instancetype)init NS_UNAVAILABLE;

@end

/// An object that contains useful information about a created shared album.
NS_SWIFT_SENDABLE NS_REFINED_FOR_SWIFT
@interface PHSharedAlbumCreationResult : NSObject

/// The created shared album's identifier.
@property (nonatomic, readonly) NSString *albumIdentifier;

/// The created shared album's URL.
@property (nonatomic, readonly) NSURL *albumURL;

- (instancetype)init NS_UNAVAILABLE;

@end

/**
 * @abstract A set of methods that the delegate must implement to respond to `PHSharedAlbumCreationViewController` events.
 */
NS_SWIFT_NAME(PHSharedAlbumCreationViewController.Delegate)
@protocol PHSharedAlbumCreationViewControllerDelegate <NSObject>

/**
 * @abstract Called when shared album creation completes.
 *
 * @discussion If creation was successful, `-[PHSharedAlbumCreationViewController albumIdentifier]` will be non-`nil` and `error` will be `nil`. If creation was unsuccessful, `-[PHSharedAlbumCreationViewController albumIdentifier]` will be `nil` and `error` will be non-`nil`. The creation was cancelled by the user, both `-[PHSharedAlbumCreationViewController albumIdentifier]` and `error` will be `nil`. The view controller won't be dismissed automatically when this method is called.
 */
- (void)sharedAlbumCreationViewController:(PHSharedAlbumCreationViewController *)creationViewController didCompleteWithError:(nullable NSError *)error;

@end

#if TARGET_OS_OSX
/**
 * @abstract This class is used to present the shared album creation view from AppKit-based view controllers.
 */
@interface PHSharedAlbumCreationViewController: NSViewController
#else
/**
 * @abstract This class is used to present the shared album creation view from UIKit-based view controllers.
 */
@interface PHSharedAlbumCreationViewController: UIViewController
#endif

/**
 * @abstract Returns a view controller that allows the user to create a new shared album.
 *
 * @param configuration The configuration for creating a new shared album.
 */
- (instancetype)initWithConfiguration:(PHSharedAlbumCreationConfiguration *)configuration NS_DESIGNATED_INITIALIZER NS_REFINED_FOR_SWIFT;

/// The delegate to respond to `PHSharedAlbumCreationViewController` events.
@property (nonatomic, weak, nullable) id<PHSharedAlbumCreationViewControllerDelegate> delegate;

/// Upon successful album creation, `creationResult` will be non-nil and provide information about the just-created shared album.
@property (nonatomic, copy, nullable, readonly) PHSharedAlbumCreationResult *creationResult;

- (instancetype)init NS_UNAVAILABLE;
- (instancetype)initWithNibName:(nullable NSString *)nibNameOrNil bundle:(nullable NSBundle *)nibBundleOrNil NS_UNAVAILABLE;
- (nullable instancetype)initWithCoder:(NSCoder *)coder NS_UNAVAILABLE;

@end

API_UNAVAILABLE_END // tvos, watchos
API_AVAILABLE_END // ios(27), macos(27), visionos(27)
NS_ASSUME_NONNULL_END
