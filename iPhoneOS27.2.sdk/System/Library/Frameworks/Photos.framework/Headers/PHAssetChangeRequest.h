//
//  PHAssetChangeRequest.h
//  Photos
//
//  Copyright (c) 2013 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

#import <Photos/PHAsset.h>
#import <Photos/PHChangeRequest.h>
#import <Photos/PHContentEditingOutput.h>

@class UIImage;
@class CLLocation;
@class PHAssetResource;
@class PHObjectPlaceholder;
@class PHContentEditingInputRequestOptions;

NS_ASSUME_NONNULL_BEGIN
API_AVAILABLE_BEGIN(macos(10.15), ios(8), tvos(10))

// PHAssetChangeRequest can only be created or used within a -[PHPhotoLibrary performChanges:] or -[PHPhotoLibrary performChangesAndWait:] block.
OS_EXPORT
@interface PHAssetChangeRequest : PHChangeRequest

#pragma mark - Creating Assets

// Basic asset creation. For finer-grained control, see PHAssetCreationRequest.
+ (instancetype)creationRequestForAssetFromImage:(UIImage *)image;
+ (nullable instancetype)creationRequestForAssetFromImageAtFileURL:(NSURL *)fileURL;
+ (nullable instancetype)creationRequestForAssetFromVideoAtFileURL:(NSURL *)fileURL;

// This can be used to fetch the newly created asset after the change block has completed by using -localIdentifier
// It can also be added directly to collections within the current change block
@property (nonatomic, strong, readonly, nullable) PHObjectPlaceholder *placeholderForCreatedAsset;

/// The rating for this asset
@property (nonatomic, assign, readwrite) PHAssetRating rating API_AVAILABLE(macos(27), ios(27), tvos(27), visionos(27));

/// An asset description to change to.
/// Set to nil or an empty string to clear the caption.
@property (nonatomic, copy, readwrite, nullable) NSString *caption API_AVAILABLE(ios(27), macos(27), tvos(27), visionos(27));

#pragma mark - Deleting Assets

+ (void)deleteAssets:(id<NSFastEnumeration>)assets;



#pragma mark - Modifying Assets

// if the asset does not allow the type of change requested, these methods will raise an exception, call canPerformEditOperation: on the asset to determine if the type of edit operation is allowed.
+ (instancetype)changeRequestForAsset:(PHAsset *)asset;

@property (nonatomic, strong, readwrite, nullable) NSDate *creationDate;
@property (nonatomic, strong, readwrite, nullable) CLLocation *location;
@property (nonatomic, assign, readwrite, getter=isFavorite) BOOL favorite;

// a hidden asset will be excluded from moment collections, but may still be included in other smart or regular album collections
@property (nonatomic, assign, readwrite, getter=isHidden) BOOL hidden;

/// Disable or enable the video part of a Live Photo so it just appears as a still image (disabled) or a Live Photo (enabled)
///
/// Applies to Live Photos only.
- (void)setLivePhotoVideoPlaybackEnabled:(BOOL)enabled API_AVAILABLE(macos(27), ios(27), tvos(27), visionos(27));

/// Add or remove a keyword associated with this asset
/// Adding a keyword that is already associated (or removing a keyword that is not) will be silently ignored
- (void)addKeyword:(NSString *)keyword API_AVAILABLE(macos(27), ios(27), tvos(27), visionos(27));
- (void)removeKeyword:(NSString *)keyword API_AVAILABLE(macos(27), ios(27), tvos(27), visionos(27));

#pragma mark - Editing Asset Contents

@property (nonatomic, strong, readwrite, nullable) PHContentEditingOutput *contentEditingOutput;

// Reverts the asset's content to its original camera-captured state, preserving any adjustments applied by the camera pipeline at capture time (e.g. Portrait bokeh, Night mode). User edits are removed.
// Reverting requires that all original resources are downloaded to the device first and this must be performed manually by the client if the original resources aren't already local.
// Use PHAssetResourceManager to ensure that original asset content is downloaded to the current device before making this request.
- (void)revertAssetContentToOriginal;

/// Reverts the asset's content to its original, choosing which original resource to use as the unadjusted base for all renders.
///
/// In addition to reverting all adjustments, this selects either the RAW
/// (``PHOriginalResourceChoice/PHOriginalResourceChoiceRaw``) or the compressed
/// (``PHOriginalResourceChoice/PHOriginalResourceChoiceCompressed``) resource as the source for all renders.
/// This applies to RAW+JPEG assets only. Using this with other types of assets is not supported.
///
/// - Parameter choice: The original resource to use as the unadjusted base after reverting.
- (void)revertAssetContentToOriginalResourceChoice:(PHOriginalResourceChoice)choice API_AVAILABLE(macos(27), ios(27), tvos(27), visionos(27));

@end


typedef NSUInteger PHContentEditingInputRequestID;

OS_EXPORT
@interface PHContentEditingInputRequestOptions : NSObject

// Block to be provided by the client, used to determine if the given adjustment data can be handled (i.e. can be decoded and rendered).
@property (nonatomic, copy) BOOL (^canHandleAdjustmentData)(PHAdjustmentData *adjustmentData);

// Used if data is not available locally and needs to be retrieved from iCloud.
@property (nonatomic, assign, getter = isNetworkAccessAllowed) BOOL networkAccessAllowed;
@property (nonatomic, copy, nullable) void (^progressHandler)(double progress, BOOL *stop);

/// Set this value to `true` if you don't want a `displaySizeImage` on the `PHContentEditingInput`. This can give performance wins when the image will not be used.
@property (nonatomic, assign) BOOL skipsDisplaySizeImage API_AVAILABLE(macos(27), ios(27), tvos(27), visionos(27));

/// The original resource to use as the unadjusted base when fulfilling the request.
///
/// When set, the content editing input request is fulfilled as though the asset's
/// original resource choice were the value specified here. This property applies to
/// RAW+JPEG assets only, and is intended for switching between the RAW and compressed
/// resource of such an asset. Setting it for an asset that has only a RAW resource is an error.
@property (nonatomic, assign) PHOriginalResourceChoice originalResourceChoice API_AVAILABLE(macos(27), ios(27), tvos(27), visionos(27));

@end


@interface PHAsset (PHContentEditingInput)

// Completion and progress handlers are called on an arbitrary serial queue.
- (PHContentEditingInputRequestID)requestContentEditingInputWithOptions:(nullable PHContentEditingInputRequestOptions *)options completionHandler:(void (^)(PHContentEditingInput *__nullable contentEditingInput, NSDictionary *info))completionHandler;
- (void)cancelContentEditingInputRequest:(PHContentEditingInputRequestID)requestID;

@end

// Completion handler info dictionary keys
extern NSString *const PHContentEditingInputResultIsInCloudKey;
extern NSString *const PHContentEditingInputCancelledKey;
extern NSString *const PHContentEditingInputErrorKey;


@interface PHContentEditingOutput (PHAssetChangeRequest)

// Create a PHContentEditingOutput from a newly created asset within the change request block
- (instancetype)initWithPlaceholderForCreatedAsset:(PHObjectPlaceholder *)placeholderForCreatedAsset;

@end

API_AVAILABLE_END
NS_ASSUME_NONNULL_END
