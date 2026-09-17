//
//  PHPhotoLibrary.h
//  Photos
//
//  Copyright (c) 2013 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <Photos/PhotosTypes.h>

NS_ASSUME_NONNULL_BEGIN
API_AVAILABLE_BEGIN(macos(10.13), ios(8), tvos(10))

@class PHChange;
@class PHPhotoLibrary;
@class PHPersistentChangeToken;
@class PHPersistentChangeFetchResult;
@class PHAssetResourceUploadJobOptions;


typedef NS_ENUM(NSInteger, PHAuthorizationStatus) {
    PHAuthorizationStatusNotDetermined = 0, // User has not yet made a choice with regards to this application
    PHAuthorizationStatusRestricted,        // This application is not authorized to access photo data.
                                            // The user cannot change this application’s status, possibly due to active restrictions
                                            //   such as parental controls being in place.
    PHAuthorizationStatusDenied,            // User has explicitly denied this application access to photos data.
    PHAuthorizationStatusAuthorized,        // User has authorized this application to access photos data.
    PHAuthorizationStatusLimited API_AVAILABLE(ios(14)), // User has authorized this application for limited photo library access. Add PHPhotoLibraryPreventAutomaticLimitedAccessAlert = YES to the application's Info.plist to prevent the automatic alert to update the users limited library selection. Use -[PHPhotoLibrary(PhotosUISupport) presentLimitedLibraryPickerFromViewController:] from PhotosUI/PHPhotoLibrary+PhotosUISupport.h to manually present the limited library picker.
};

typedef NS_ENUM(NSInteger, PHAccessLevel) {
    PHAccessLevelAddOnly = 1,
    PHAccessLevelReadWrite = 2,
} API_AVAILABLE(macos(11), ios(14), tvos(14));


#pragma mark -
@protocol PHPhotoLibraryChangeObserver <NSObject>
// This callback is invoked on an arbitrary serial queue. If you need this to be handled on a specific queue, you should redispatch appropriately
- (void)photoLibraryDidChange:(PHChange *)changeInstance;

@end

#pragma mark -
API_AVAILABLE(macos(10.15), ios(13), tvos(13))
@protocol PHPhotoLibraryAvailabilityObserver <NSObject>
// This notification is posted on a private queue.
- (void)photoLibraryDidBecomeUnavailable:(PHPhotoLibrary *)photoLibrary API_AVAILABLE(macos(10.15), ios(13), tvos(13));
@end


API_AVAILABLE(macos(27), ios(27), tvos(27), visionos(27))
@protocol PHPhotoLibraryPersistentChangesObserver <NSObject>
// This callback is invoked on an arbitrary serial queue. If you need this to be handled on a specific queue, you should redispatch appropriately
- (void)photoLibraryPersistentChangesDidUpdate:(PHPhotoLibrary *)photoLibrary;
@end

/*!
 @class        PHPhotoLibrary
 @abstract     A PHPhotoLibrary provides access to the metadata and image data for the photos, videos and related content in the user's photo library, including content from the Camera Roll, iCloud Shared, Photo Stream, imported, and synced from iTunes.
 @discussion   ...
 */
#pragma mark -
OS_EXPORT
NS_SWIFT_SENDABLE
@interface PHPhotoLibrary : NSObject

+ (PHPhotoLibrary *)sharedPhotoLibrary;

#pragma mark - Library access authorization status

/// Replaces \c +authorizationStatus to support add-only/read-write access level status
+ (PHAuthorizationStatus)authorizationStatusForAccessLevel:(PHAccessLevel)accessLevel API_AVAILABLE(macosx(11), ios(14), tvos(14));
+ (void)requestAuthorizationForAccessLevel:(PHAccessLevel)accessLevel handler:(void(^)(PHAuthorizationStatus status))handler API_AVAILABLE(macosx(11), ios(14), tvos(14)) NS_SWIFT_ASYNC(2);

/// Deprecated and replaced by authorizationStatusForAccessLevel:, will return \c PHAuthorizationStatusAuthorized if the user has chosen limited photo library access
+ (PHAuthorizationStatus)authorizationStatus API_DEPRECATED_WITH_REPLACEMENT("+authorizationStatusForAccessLevel:", ios(8, API_TO_BE_DEPRECATED), macos(10.13, API_TO_BE_DEPRECATED), tvos(10, API_TO_BE_DEPRECATED));
+ (void)requestAuthorization:(void(^)(PHAuthorizationStatus status))handler API_DEPRECATED_WITH_REPLACEMENT("+requestAuthorizationForAccessLevel:handler:", ios(8, API_TO_BE_DEPRECATED), macos(10.13, API_TO_BE_DEPRECATED), tvos(10, API_TO_BE_DEPRECATED));

#pragma mark - Background Upload of Asset Resources: Feature and Extension Enablement
 
/// A Boolean value that indicates whether background asset resource uploading is enabled.
///
/// The value is `true` if the extension is enabled and active, and is `false` otherwise.
///
/// The extension's host app uses this property to determine the background processing status. See ``PHAssetResourceUploadJob`` and ````PHAssetResourceUploadJobChangeRequest`` for more information.
@property (readonly, getter=isUploadJobExtensionEnabled) BOOL uploadJobExtensionEnabled API_AVAILABLE(ios(26.1), macCatalyst(27.0), macos(27.0)) API_UNAVAILABLE(tvos, visionos, watchos) NS_SWIFT_NAME(uploadJobExtensionEnabled);

/// Enables or disables the background asset resource upload job feature.
///
/// You must call this function before you create ``PHAssetResourceUploadJob`` in the extension's host application.
///
/// To enable background uploads, you must have both full library access and register the extension with the extension point: "com.apple.photos.background-upload".
///
/// - Parameters:
///     - enable: `true` allows calls to the extension's host application; you can fulfill that protocol to create ``PHAssetResourceUploadJob`` objects. `false` stops calls to the extension's host application.
///     - error: if either enabling or disabling was unsuccessful, `false` is returned and an error is set on the `error` parameter.
- (BOOL)setUploadJobExtensionEnabled:(BOOL)enable error:(NSError **)error API_DEPRECATED("Use -enableUploadJobExtensionWithOptions:error: and -disableUploadJobExtensionWithError: instead", ios(26.1, 27.0)) API_UNAVAILABLE(macCatalyst, macos, tvos, visionos, watchos);

/// Enables the background asset resource upload job feature with the given options, atomically.
///
/// The configuration is created with `options` already set, as a single change — unlike calling
/// ``setUploadJobExtensionOptions:error:`` afterward, as a separate change.
///
/// - Parameters:
///     - options: the options to set for the newly enabled configuration, or `nil` to use default values.
///     - error: if enabling was unsuccessful, `false` is returned and an error is set on the `error` parameter.
- (BOOL)enableUploadJobExtensionWithOptions:(nullable PHAssetResourceUploadJobOptions *)options error:(NSError **)error API_AVAILABLE(ios(27.0), macCatalyst(27.0), macos(27.0)) API_UNAVAILABLE(tvos, visionos, watchos);

/// Disables the background asset resource upload job feature.
///
/// - Parameters:
///     - error: if disabling was unsuccessful, `false` is returned and an error is set on the `error` parameter.
- (BOOL)disableUploadJobExtensionWithError:(NSError **)error API_AVAILABLE(ios(27.0), macCatalyst(27.0), macos(27.0)) API_UNAVAILABLE(tvos, visionos, watchos);

/// The options for the calling app's background asset resource upload job configuration.
///
/// The value is `nil` if the extension isn't enabled or the caller isn't authorized. Otherwise, the value is an
/// options object with default values if the configuration exists but no options have been set.
@property (readonly, nullable) PHAssetResourceUploadJobOptions *uploadJobExtensionOptions API_AVAILABLE(ios(27.0), macCatalyst(27.0), macos(27.0)) API_UNAVAILABLE(tvos, visionos, watchos);

/// Sets the options for the calling app's background asset resource upload job configuration.
///
/// To reset the configuration's options to their default values, pass a newly-initialized `PHAssetResourceUploadJobOptions` instance.
///
/// - Parameters:
///     - options: the options to set.
///     - error: if the configuration could not be found, the caller isn't authorized, or the update failed, `false` is returned and an error is set on the `error` parameter.
- (BOOL)setUploadJobExtensionOptions:(PHAssetResourceUploadJobOptions *)options error:(NSError **)error API_AVAILABLE(ios(27.0), macCatalyst(27.0), macos(27.0)) API_UNAVAILABLE(tvos, visionos, watchos);

#pragma mark - Library availability

@property (readonly, atomic, nullable, strong) NSError *unavailabilityReason API_AVAILABLE(macos(10.15), ios(13), tvos(13));

- (void)registerAvailabilityObserver:(id<PHPhotoLibraryAvailabilityObserver>)observer API_AVAILABLE(macos(10.15), ios(13), tvos(13));
- (void)unregisterAvailabilityObserver:(id<PHPhotoLibraryAvailabilityObserver>)observer API_AVAILABLE(macos(10.15), ios(13), tvos(13));

#pragma mark - Applying Changes

// handlers are invoked on an arbitrary serial queue
// Nesting change requests will throw an exception
- (void)performChanges:(dispatch_block_t)changeBlock completionHandler:(nullable void(^)(BOOL success, NSError *__nullable error))completionHandler NS_SWIFT_ASYNC_THROWS_ON_FALSE(1);
- (BOOL)performChangesAndWait:(dispatch_block_t)changeBlock error:(NSError *__autoreleasing *)error;

#pragma mark - Change Handling

- (void)registerChangeObserver:(id<PHPhotoLibraryChangeObserver>)observer;
- (void)unregisterChangeObserver:(id<PHPhotoLibraryChangeObserver>)observer;

#pragma mark - Change History

/// Registers an observer to be notified when persistent changes occur in the photo library.
///
/// The observer is held weakly by the photo library. The observer's ``PHPhotoLibraryPersistentChangesObserver/photoLibraryPersistentChangesDidUpdate:`` method
/// is called on an arbitrary serial queue when changes are committed to the photo library. Use
/// ``fetchPersistentChangesSinceToken:error:`` to retrieve the specific changes.
///
/// Requires read-write photo library authorization (``PHAccessLevel/PHAccessLevelReadWrite``).
- (void)registerPersistentChangesObserver:(id<PHPhotoLibraryPersistentChangesObserver>)observer API_AVAILABLE(macos(27), ios(27), tvos(27), visionos(27));

/// Unregisters a previously registered persistent changes observer.
///
/// After calling this method, the observer will no longer receive persistent changes callbacks.
- (void)unregisterPersistentChangesObserver:(id<PHPhotoLibraryPersistentChangesObserver>)observer API_AVAILABLE(macos(27), ios(27), tvos(27), visionos(27));

- (nullable PHPersistentChangeFetchResult *)fetchPersistentChangesSinceToken:(PHPersistentChangeToken *)token error:(NSError **)error API_AVAILABLE(macos(13), ios(16), tvos(16));

@property (nonatomic, readonly) PHPersistentChangeToken *currentChangeToken API_AVAILABLE(macos(13), ios(16), tvos(16));


@end

API_AVAILABLE_END
NS_ASSUME_NONNULL_END
