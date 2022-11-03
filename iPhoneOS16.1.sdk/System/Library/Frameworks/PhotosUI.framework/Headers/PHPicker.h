//
//  PHPicker.h
//  PhotosUI
//
//  Copyright © 2020 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@class PHPhotoLibrary;

NS_REFINED_FOR_SWIFT
typedef NS_ENUM(NSInteger, PHAssetPlaybackStyle);

/// A mode that determines which representation \c PHPickerViewController should provide for an asset given a type identifier, if multiple representations are available.
NS_REFINED_FOR_SWIFT
typedef NS_ENUM(NSInteger, PHPickerConfigurationAssetRepresentationMode) {
    /// Uses the best representation determined by the system. This may change in future releases.
    PHPickerConfigurationAssetRepresentationModeAutomatic = 0,
    /// Uses the current representation to avoid transcoding if possible.
    PHPickerConfigurationAssetRepresentationModeCurrent = 1,
    /// Uses the most compatible representation if possible, even if transcoding is required.
    PHPickerConfigurationAssetRepresentationModeCompatible = 2,
} API_AVAILABLE(ios(14), macos(13)) API_UNAVAILABLE(watchos) API_UNAVAILABLE(tvos);

/// An enum that determines how \c PHPickerViewController handles user selection.
NS_REFINED_FOR_SWIFT
typedef NS_ENUM(NSInteger, PHPickerConfigurationSelection) {
    /// Uses the default selection behavior.
    PHPickerConfigurationSelectionDefault = 0,
    /// Uses the selection order made by the user. Selected assets are numbered.
    PHPickerConfigurationSelectionOrdered = 1,
} API_AVAILABLE(ios(15), macos(13)) API_UNAVAILABLE(watchos) API_UNAVAILABLE(tvos);

NS_ASSUME_NONNULL_END

API_AVAILABLE_BEGIN(ios(14), macos(13))
API_UNAVAILABLE_BEGIN(tvos, watchos)
NS_ASSUME_NONNULL_BEGIN

/// A filter that restricts which types of assets \c PHPickerViewController can show.
__attribute__((objc_subclassing_restricted))
OS_EXPORT
NS_REFINED_FOR_SWIFT
API_UNAVAILABLE(watchos)
@interface PHPickerFilter : NSObject <NSCopying>

/// The filter for images.
@property (nonatomic, class, readonly) PHPickerFilter *imagesFilter API_UNAVAILABLE(watchos);

/// The filter for videos.
@property (nonatomic, class, readonly) PHPickerFilter *videosFilter;

/// The filter for live photos.
@property (nonatomic, class, readonly) PHPickerFilter *livePhotosFilter;

/// The filter for Depth Effect photos.
@property (nonatomic, class, readonly) PHPickerFilter *depthEffectPhotosFilter API_AVAILABLE(ios(16));

/// The filter for bursts.
@property (nonatomic, class, readonly) PHPickerFilter *burstsFilter API_AVAILABLE(ios(16));

/// The filter for panorama photos.
@property (nonatomic, class, readonly) PHPickerFilter *panoramasFilter API_AVAILABLE(ios(15));

/// The filter for screenshots.
@property (nonatomic, class, readonly) PHPickerFilter *screenshotsFilter API_AVAILABLE(ios(15));

/// The filter for screen recordings.
@property (nonatomic, class, readonly) PHPickerFilter *screenRecordingsFilter API_AVAILABLE(ios(15));

/// The filter for Cinematic videos.
@property (nonatomic, class, readonly) PHPickerFilter *cinematicVideosFilter API_AVAILABLE(ios(16));

/// The filter for Slow-Mo videos.
@property (nonatomic, class, readonly) PHPickerFilter *slomoVideosFilter API_AVAILABLE(ios(15));

/// The filter for time-lapse videos.
@property (nonatomic, class, readonly) PHPickerFilter *timelapseVideosFilter API_AVAILABLE(ios(15));

/// Returns a new filter based on the asset playback style.
+ (PHPickerFilter *)playbackStyleFilter:(PHAssetPlaybackStyle)playbackStyle API_AVAILABLE(ios(15));

/// Returns a new filter formed by OR-ing the filters in a given array.
+ (PHPickerFilter *)anyFilterMatchingSubfilters:(NSArray<PHPickerFilter *> *)subfilters;

/// Returns a new filter formed by AND-ing the filters in a given array.
+ (PHPickerFilter *)allFilterMatchingSubfilters:(NSArray<PHPickerFilter *> *)subfilters API_AVAILABLE(ios(15));

/// Returns a new filter formed by negating the given filter.
+ (PHPickerFilter *)notFilterOfSubfilter:(PHPickerFilter *)subfilter API_AVAILABLE(ios(15));

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

@end

/// A configuration for \c PHPickerViewController.
__attribute__((objc_subclassing_restricted))
OS_EXPORT
NS_REFINED_FOR_SWIFT
API_UNAVAILABLE(watchos)
@interface PHPickerConfiguration : NSObject <NSCopying>

/// The preferred representation mode of selected assets. Default is \c PHPickerConfigurationAssetRepresentationModeAutomatic.
/// @discussion Setting \c preferredAssetRepresentationMode to \c PHPickerConfigurationAssetRepresentationModeAutomatic means the best representation determined by the system will be used.
@property (nonatomic) PHPickerConfigurationAssetRepresentationMode preferredAssetRepresentationMode API_UNAVAILABLE(watchos);

/// The selection behavior of the picker. Default is \c PHPickerConfigurationSelectionDefault.
@property (nonatomic) PHPickerConfigurationSelection selection API_AVAILABLE(ios(15)) API_UNAVAILABLE(watchos);

/// The maximum number of assets that can be selected. Default is 1.
/// @discussion Setting \c selectionLimit to 0 means maximum supported by the system.
@property (nonatomic) NSInteger selectionLimit API_UNAVAILABLE(watchos);

/// Types of assets that can be shown. Default is \c nil.
/// @discussion Setting \c filter to \c nil means all asset types can be shown.
@property (nonatomic, copy, nullable) PHPickerFilter *filter API_UNAVAILABLE(watchos);

/// Local identifiers of assets to be shown as selected when the picker is presented. Default is an empty array.
/// @discussion \c preselectedAssetIdentifiers should be an empty array if \c selectionLimit is 1 or \c photoLibrary is not specified. Returned item providers for preselected assets are always empty.
@property (nonatomic, copy) NSArray<NSString *> *preselectedAssetIdentifiers API_AVAILABLE(ios(15)) API_UNAVAILABLE(watchos);

/// Initializes a new configuration with the \c photoLibrary the picker should use.
- (instancetype)initWithPhotoLibrary:(PHPhotoLibrary *)photoLibrary API_UNAVAILABLE(watchos);

/// Initializes a new configuration with the system photo library. This configuration never returns asset identifiers.
- (instancetype)init API_UNAVAILABLE(watchos);

@end

/// A user selected asset from \c PHPickerViewController.
__attribute__((objc_subclassing_restricted))
OS_EXPORT
NS_REFINED_FOR_SWIFT
API_UNAVAILABLE(watchos)
@interface PHPickerResult : NSObject

/// Representations of the selected asset.
@property (nonatomic, readonly) NSItemProvider *itemProvider API_UNAVAILABLE(watchos);

/// The local identifier of the selected asset.
@property (nonatomic, readonly, nullable) NSString *assetIdentifier API_UNAVAILABLE(watchos);

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
API_UNAVAILABLE_END // (tvos, watchos)
API_AVAILABLE_END // (ios(14), macos(13))

#if __has_include(<AppKit/NSViewController.h>) || __has_include(<UIKit/UIViewController.h>)

#if TARGET_OS_IPHONE
#import <UIKit/UIKit.h>
#else
#import <AppKit/AppKit.h>
#endif // TARGET_OS_IPHONE

API_AVAILABLE_BEGIN(ios(14), macos(13))
API_UNAVAILABLE_BEGIN(tvos, watchos)
NS_ASSUME_NONNULL_BEGIN

@class PHPickerViewController;

/// A set of methods that the delegate must implement to respond to \c PHPickerViewController user events.
OS_EXPORT
NS_SWIFT_UI_ACTOR
NS_REFINED_FOR_SWIFT
API_UNAVAILABLE(watchos)
@protocol PHPickerViewControllerDelegate <NSObject>

/// Called when the user completes a selection or dismisses \c PHPickerViewController using the cancel button.
/// @discussion The picker won't be automatically dismissed when this method is called.
- (void)picker:(PHPickerViewController *)picker didFinishPicking:(NSArray<PHPickerResult *> *)results API_UNAVAILABLE(watchos);

@end

/// A picker that manages the system interfaces for choosing assets from the user's photo library and delivers the results of those interactions to a delegate.
/// @discussion The picker is intended to be used as-is and does not support subclassing. It is out-of-process, so photo library access authorization is not needed. The view hierarchy for the picker is private and must not be modified.
__attribute__((objc_subclassing_restricted))
OS_EXPORT
API_UNAVAILABLE(watchos)
#if TARGET_OS_IPHONE
@interface PHPickerViewController : UIViewController
#else
@interface PHPickerViewController : NSViewController
#endif // TARGET_OS_IPHONE

/// The configuration passed in during initialization.
@property (nonatomic, copy, readonly) PHPickerConfiguration *configuration NS_REFINED_FOR_SWIFT API_UNAVAILABLE(watchos);

/// The delegate to be notified.
@property (nonatomic, weak) id<PHPickerViewControllerDelegate> delegate NS_REFINED_FOR_SWIFT API_UNAVAILABLE(watchos);

/// Initializes a new picker with the \c configuration the picker should use.
- (instancetype)initWithConfiguration:(PHPickerConfiguration *)configuration NS_DESIGNATED_INITIALIZER NS_REFINED_FOR_SWIFT API_UNAVAILABLE(watchos);

/// Deselects selected assets in the picker.
/// @discussion Does nothing if asset identifiers are invalid or not selected, or \c photoLibrary is not specified in the configuration.
- (void)deselectAssetsWithIdentifiers:(NSArray<NSString *> *)identifiers API_AVAILABLE(ios(16));

/// Reorders selected assets in the picker. A \c nil \c afterIdentifier means moving to the front.
/// @discussion Does nothing if asset identifiers are invalid or not selected, or \c photoLibrary is not specified in the configuration.
- (void)moveAssetWithIdentifier:(NSString *)identifier afterAssetWithIdentifier:(nullable NSString *)afterIdentifier API_AVAILABLE(ios(16));

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;
#if TARGET_OS_IPHONE
- (instancetype)initWithNibName:(nullable NSString *)nibNameOrNil bundle:(nullable NSBundle *)nibBundleOrNil NS_UNAVAILABLE;
#else
- (instancetype)initWithNibName:(nullable NSNibName)nibNameOrNil bundle:(nullable NSBundle *)nibBundleOrNil NS_UNAVAILABLE;
#endif // TARGET_OS_IPHONE
- (nullable instancetype)initWithCoder:(NSCoder *)coder NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
API_UNAVAILABLE_END // (tvos, watchos)
API_AVAILABLE_END // (ios(14), macos(13))

#endif // __has_include(<AppKit/NSViewController.h>) || __has_include(<UIKit/UIViewController.h>)
