//
//  PhotosTypes.h
//  Photos
//
//  Copyright (c) 2013 Apple Inc. All rights reserved.
//

#ifndef Photos_PhotosTypes_h
#define Photos_PhotosTypes_h

#import <Foundation/Foundation.h>


API_AVAILABLE_BEGIN(macos(10.11), ios(8), tvos(10))

#pragma mark - PHCollectionListTypes

typedef NS_ENUM(NSInteger, PHImageContentMode) {
    PHImageContentModeAspectFit = 0,
    PHImageContentModeAspectFill = 1,
    PHImageContentModeDefault = PHImageContentModeAspectFit
};

typedef NS_ENUM(NSInteger, PHCollectionListType) {

    PHCollectionListTypeMomentList    API_DEPRECATED("Will be removed in a future release", ios(8, 13), tvos(10, 13)) API_UNAVAILABLE(macos) = 1,

    PHCollectionListTypeFolder        = 2,
    PHCollectionListTypeSmartFolder   = 3,
};

typedef NS_ENUM(NSInteger, PHCollectionListSubtype) {
    
    // PHCollectionListTypeMomentList subtypes

    PHCollectionListSubtypeMomentListCluster    API_DEPRECATED("Will be removed in a future release", ios(8, 13), tvos(10, 13)) API_UNAVAILABLE(macos) = 1,
    PHCollectionListSubtypeMomentListYear       API_DEPRECATED("Will be removed in a future release", ios(8, 13), tvos(10, 13)) API_UNAVAILABLE(macos) = 2,

    // PHCollectionListTypeFolder subtypes

    /// A user-configurable folder containing albums or other folders.
    ///
    /// Can be created, or modified via ``/Photos/PHCollectionListChangeRequest``
    PHCollectionListSubtypeRegularFolder        = 100,

    /// The collection list that contains the top-level user collections.
    ///
    /// There is always one root folder in the library and does not allow ``/Photos/PHCollectionEditOperation/PHCollectionEditOperationRename`` or ``/Photos/PHCollectionEditOperation/PHCollectionEditOperationDelete``
    PHCollectionListSubtypeRootFolder           API_AVAILABLE(macos(27), ios(27), tvos(27), visionos(27)) = 101,

    // PHCollectionListTypeSmartFolder subtypes
    PHCollectionListSubtypeSmartFolderEvents    = 200,
    PHCollectionListSubtypeSmartFolderFaces     = 201,
    
    // Used for fetching if you don't care about the exact subtype
    PHCollectionListSubtypeAny = NSIntegerMax
};

#pragma mark - PHCollection types

typedef NS_ENUM(NSInteger, PHCollectionEditOperation) {
    PHCollectionEditOperationDeleteContent    = 1, // Delete things it contains
    PHCollectionEditOperationRemoveContent    = 2, // Remove things it contains, they're not deleted from the library
    PHCollectionEditOperationAddContent       = 3, // Add things from other collection
    PHCollectionEditOperationCreateContent    = 4, // Create new things, or duplicate them from others in the same container
    PHCollectionEditOperationRearrangeContent = 5, // Change the order of things
    PHCollectionEditOperationDelete           = 6, // Deleting of the container, not the content
    PHCollectionEditOperationRename           = 7, // Renaming of the container, not the content
};

#pragma mark - PHAssetCollection types

typedef NS_ENUM(NSInteger, PHAssetCollectionType) {
    PHAssetCollectionTypeAlbum           = 1,
    PHAssetCollectionTypeSmartAlbum      = 2,

    PHAssetCollectionTypeMoment     API_DEPRECATED("Will be removed in a future release", ios(8, 13), tvos(10, 13)) API_UNAVAILABLE(macos) = 3,

};

typedef NS_ENUM(NSInteger, PHAssetCollectionSubtype) {
    
    // PHAssetCollectionTypeAlbum regular subtypes
    PHAssetCollectionSubtypeAlbumRegular         = 2,
    PHAssetCollectionSubtypeAlbumSyncedEvent     = 3,
    PHAssetCollectionSubtypeAlbumSyncedFaces     = 4,
    PHAssetCollectionSubtypeAlbumSyncedAlbum     = 5,
    PHAssetCollectionSubtypeAlbumImported        = 6,
    
    // PHAssetCollectionTypeAlbum shared subtypes
    PHAssetCollectionSubtypeAlbumMyPhotoStream   = 100,
    PHAssetCollectionSubtypeAlbumCloudShared     = 101,

    
    // PHAssetCollectionTypeSmartAlbum subtypes
    PHAssetCollectionSubtypeSmartAlbumGeneric    = 200,
    PHAssetCollectionSubtypeSmartAlbumPanoramas  = 201,
    PHAssetCollectionSubtypeSmartAlbumVideos     = 202,
    PHAssetCollectionSubtypeSmartAlbumFavorites  = 203,
    PHAssetCollectionSubtypeSmartAlbumTimelapses = 204,
    PHAssetCollectionSubtypeSmartAlbumAllHidden  = 205,
    PHAssetCollectionSubtypeSmartAlbumRecentlyAdded = 206,
    PHAssetCollectionSubtypeSmartAlbumBursts     = 207,
    PHAssetCollectionSubtypeSmartAlbumSlomoVideos = 208,
    PHAssetCollectionSubtypeSmartAlbumUserLibrary = 209,
    PHAssetCollectionSubtypeSmartAlbumSelfPortraits API_AVAILABLE(ios(9)) = 210,
    PHAssetCollectionSubtypeSmartAlbumScreenshots API_AVAILABLE(ios(9)) = 211,
    PHAssetCollectionSubtypeSmartAlbumDepthEffect API_AVAILABLE(macos(10.13), ios(10.2), tvos(10.1)) = 212,
    PHAssetCollectionSubtypeSmartAlbumLivePhotos API_AVAILABLE(macos(10.13), ios(10.3), tvos(10.2)) = 213,
    PHAssetCollectionSubtypeSmartAlbumAnimated API_AVAILABLE(macos(10.15), ios(11), tvos(11)) = 214,
    PHAssetCollectionSubtypeSmartAlbumLongExposures API_AVAILABLE(macos(10.15), ios(11), tvos(11)) = 215,
    PHAssetCollectionSubtypeSmartAlbumUnableToUpload API_AVAILABLE(macos(10.15), ios(13), tvos(13)) = 216,
    PHAssetCollectionSubtypeSmartAlbumRAW API_AVAILABLE(macos(12), ios(15), tvos(15)) = 217,
    PHAssetCollectionSubtypeSmartAlbumCinematic API_AVAILABLE(macos(12), ios(15), tvos(15)) = 218,

    /// A Smart Album that groups all photos and videos captured as spatial media.
    PHAssetCollectionSubtypeSmartAlbumSpatial API_AVAILABLE(macos(15), ios(18), tvos(18)) = 219,
    
    /// A Smart Album that groups all videos captured using the device’s screenrecordings function.
    PHAssetCollectionSubtypeSmartAlbumScreenRecordings API_AVAILABLE(macos(11), ios(14), tvos(14)) = 220,

    
    // Used for fetching, if you don't care about the exact subtype
    PHAssetCollectionSubtypeAny = NSIntegerMax
};

#pragma mark - PHAsset types


typedef NS_ENUM(NSInteger, PHAssetEditOperation) {
    PHAssetEditOperationDelete      = 1,
    PHAssetEditOperationContent     = 2,
    PHAssetEditOperationProperties  = 3,

};

typedef NS_ENUM(NSInteger, PHAssetPlaybackStyle) {
    PHAssetPlaybackStyleUnsupported     = 0,
    PHAssetPlaybackStyleImage           = 1,
    PHAssetPlaybackStyleImageAnimated   = 2,
    PHAssetPlaybackStyleLivePhoto       = 3,
    PHAssetPlaybackStyleVideo           = 4,
    PHAssetPlaybackStyleVideoLooping    = 5,
} API_AVAILABLE(macos(10.13), ios(11), tvos(11)) NS_SWIFT_NAME(PHAsset.PlaybackStyle);

// Playback variation describes the Live Photo presentation effect applied to an asset (for example, Long Exposure).
// This MUST stay in sync with PFMetadataPlaybackVariation (PhotosFormats/PFMetadataDefine.h)
typedef NS_ENUM(NSInteger, PHAssetPlaybackVariation) {
    PHAssetPlaybackVariationNone            = 0,   // Default Live Photo presentation.
    PHAssetPlaybackVariationAutoloop        = 1,   // Loop variation.
    PHAssetPlaybackVariationMirror          = 2,   // Bounce variation.
    PHAssetPlaybackVariationLongExposure    = 3,   // Long Exposure variation.
} API_AVAILABLE(macos(10.15), ios(11), tvos(11)) NS_SWIFT_NAME(PHAsset.PlaybackVariation);

typedef NS_ENUM(NSInteger, PHAssetMediaType) {
    PHAssetMediaTypeUnknown = 0,
    PHAssetMediaTypeImage   = 1,
    PHAssetMediaTypeVideo   = 2,
    PHAssetMediaTypeAudio   = 3,
};

typedef NS_OPTIONS(NSUInteger, PHAssetMediaSubtype) {
    PHAssetMediaSubtypeNone               = 0,
    
    // Photo subtypes
    PHAssetMediaSubtypePhotoPanorama      = (1UL << 0),
    PHAssetMediaSubtypePhotoHDR           = (1UL << 1),
    PHAssetMediaSubtypePhotoScreenshot API_AVAILABLE(ios(9)) = (1UL << 2),
    PHAssetMediaSubtypePhotoLive API_AVAILABLE(ios(9.1)) = (1UL << 3),
    PHAssetMediaSubtypePhotoDepthEffect API_AVAILABLE(macos(10.12.2), ios(10.2), tvos(10.1)) = (1UL << 4),
    PHAssetMediaSubtypePhotoAnimation API_AVAILABLE(macos(10.15), ios(11), tvos(11), visionos(1)) = (1UL << 6),   /// The media subtype is a photo animation such as a GIF, animated PNGs, etc.
    PHAssetMediaSubtypeSpatialMedia API_AVAILABLE(macos(13), ios(16), tvos(16)) = (1UL << 10),

    // Video subtypes
    PHAssetMediaSubtypeVideoStreamed      = (1UL << 16),
    PHAssetMediaSubtypeVideoHighFrameRate = (1UL << 17),
    PHAssetMediaSubtypeVideoTimelapse     = (1UL << 18),
    PHAssetMediaSubtypeVideoScreenRecording API_AVAILABLE(macos(10.15), ios(13), tvos(13)) = (1UL << 19),
    PHAssetMediaSubtypeVideoCinematic API_AVAILABLE(macos(12), ios(15), tvos(15)) = (1UL << 21),
};


typedef NS_OPTIONS(NSUInteger, PHAssetBurstSelectionType) {
    PHAssetBurstSelectionTypeNone     = 0,
    PHAssetBurstSelectionTypeAutoPick = (1UL << 0),
    PHAssetBurstSelectionTypeUserPick = (1UL << 1),
};

/// This value determines which original resource is used for unadjusted asset derivatives and as the unadjusted resource provided/used for content adjustments.
///
/// This choice is only meaningful for assets that have a RAW alternate, such as
/// RAW+JPEG assets. For all other assets, the asset has a single original resource
/// and the value is always ``PHOriginalResourceChoiceCompressed``.

typedef NS_ENUM(NSInteger, PHOriginalResourceChoice) {
    /// The compressed original resource, such as a JPEG or HEIC, is used.
    PHOriginalResourceChoiceCompressed = 0,
    /// The RAW original resource is used.
    PHOriginalResourceChoiceRaw = 1,

} NS_SWIFT_NAME(PHAsset.OriginalResourceChoice)
API_AVAILABLE(macos(27), ios(27), tvos(27), visionos(27));


typedef NS_OPTIONS(NSUInteger, PHAssetSourceType) {
    PHAssetSourceTypeNone            = 0,
    PHAssetSourceTypeUserLibrary     = (1UL << 0),
    PHAssetSourceTypeCloudShared     = (1UL << 1),
    PHAssetSourceTypeiTunesSynced    = (1UL << 2),

} API_AVAILABLE(ios(9));


typedef NS_ENUM(NSInteger, PHAssetAdjustmentsState) {
    PHAssetAdjustmentsStateNone = 0,  // Asset has no adjustments applied



    PHAssetAdjustmentsStateUserAdjusted = 2,  // Asset has a user adjustment applied
    PHAssetAdjustmentsStateCameraAutoAdjusted = 3,  // Asset has a automatic Camera adjustment applied, no user adjustments
} NS_SWIFT_NAME(PHAsset.AdjustmentsState) API_AVAILABLE(macos(15), ios(18), tvos(18), visionos(2));

#pragma mark - PHAssetResourceType

/// Identifies a specific type of resource associated with a photo or video asset.
///
/// The set of resource types may expand in future OS releases. Additionally, assets synced from a device running
/// a newer OS may contain resource types that are not defined in the SDK version your app was built with.
///
/// When switching over resource type values, always include an `@unknown default` case that handles
/// unrecognized types gracefully — for example, by skipping the resource or preserving it as opaque data.
/// Do not use `fatalError` or other trapping assertions for unknown values.
///
/// If your app performs backup and restore of photo library assets, preserve all resources including those with
/// unrecognized types to maintain full fidelity when restoring to a device that may understand those types.
typedef NS_ENUM(NSInteger, PHAssetResourceType) {
    PHAssetResourceTypePhoto                             = 1,
    PHAssetResourceTypeVideo                             = 2,
    PHAssetResourceTypeAudio                             = 3,
    PHAssetResourceTypeAlternatePhoto                    = 4,
    PHAssetResourceTypeFullSizePhoto                     = 5,
    PHAssetResourceTypeFullSizeVideo                     = 6,
    PHAssetResourceTypeAdjustmentData                    = 7,
    PHAssetResourceTypeAdjustmentBasePhoto               = 8,
    PHAssetResourceTypePairedVideo API_AVAILABLE(ios(9.1)) = 9,
    PHAssetResourceTypeFullSizePairedVideo API_AVAILABLE(macos(10.15), ios(10)) = 10,
    PHAssetResourceTypeAdjustmentBasePairedVideo API_AVAILABLE(macos(10.15), ios(10)) = 11,
    PHAssetResourceTypeAdjustmentBaseVideo API_AVAILABLE(macos(10.15), ios(13)) = 12,

    PHAssetResourceTypePhotoProxy API_AVAILABLE(macos(14), ios(17))= 19,





} API_AVAILABLE(ios(9));


#pragma mark - PHAssetResourceUploadJob types

/// The states of an upload job.
typedef NS_ENUM(NSInteger, PHAssetResourceUploadJobState) {
    /// The job has been registered.
    PHAssetResourceUploadJobStateRegistered = 1,
    /// A request has been made to send the asset resource to the destination, but has not yet been fulfilled.
    PHAssetResourceUploadJobStatePending = 2,
    /// The job has failed to send over.
    PHAssetResourceUploadJobStateFailed = 3,
    /// The job has sent over successfully.
    PHAssetResourceUploadJobStateSucceeded = 4,
    /// The job has been cancelled.
    PHAssetResourceUploadJobStateCancelled API_AVAILABLE(ios(26.4)) = 5,

} NS_SWIFT_NAME(PHAssetResourceUploadJob.State) API_AVAILABLE(ios(26.1), macCatalyst(27.0), macos(27.0)) API_UNAVAILABLE(tvos, visionos, watchos);


/// The types of an upload job
typedef NS_ENUM(int16_t, PHAssetResourceUploadJobType) {
    /// An upload job type (will download the resource from iCloud if required. then upload)
    PHAssetResourceUploadJobTypeUpload = 0,
    /// A download job type (will download the resource from iCloud if required)
    PHAssetResourceUploadJobTypeDownloadOnly = 1,
} NS_SWIFT_NAME(PHAssetResourceUploadJob.Type) API_AVAILABLE(ios(26.4), macCatalyst(27.0), macos(27.0)) API_UNAVAILABLE(tvos, visionos, watchos);

/// An action to perform on an upload job.
///
/// Determine the available jobs for an action by calling the ``PHAssetResourceUploadJob/fetchJobsWithAction:options:`` method.
typedef NS_ENUM(NSInteger, PHAssetResourceUploadJobAction) {

    /// A job that requires acknowledgement.
    ///
    /// An acknowledgeable job has a ``PHAssetResourceUploadJob/state`` of `succeeded` or `failed`
    /// and hasn't been acknowledged.
    ///
    /// Call ``PHAssetResourceUploadJobChangeRequest/acknowledge`` to acknowledge a job
    /// and free queue capacity for new uploads.
    PHAssetResourceUploadJobActionAcknowledge = 1,

    /// A job to retry processing.
    ///
    /// A retryable job has a ``PHAssetResourceUploadJob/state`` of `failed` and hasn't previously been retried.
    ///
    /// Call ``PHAssetResourceUploadJobChangeRequest/retryWithDestination:`` to retry the job.
    PHAssetResourceUploadJobActionRetry = 2,

    /// A job to process.
    ///
    /// A processable job has a ``PHAssetResourceUploadJob/state`` of `registered` or `pending`.
    PHAssetResourceUploadJobActionProcess API_AVAILABLE(ios(26.5)) = 3,
} NS_SWIFT_NAME(PHAssetResourceUploadJob.Action) API_AVAILABLE(ios(26.1), macCatalyst(27.0), macos(27.0)) API_UNAVAILABLE(tvos, visionos, watchos);

/// Describes a rating for an asset.
typedef NS_ENUM(NSInteger, PHAssetRating) {
    PHAssetRatingUnset = 0,
    PHAssetRatingOne,
    PHAssetRatingTwo,
    PHAssetRatingThree,
    PHAssetRatingFour,
    PHAssetRatingFive
} NS_SWIFT_NAME(PHAsset.Rating) API_AVAILABLE(macos(27), ios(27), tvos(27), visionos(27));

#pragma mark - PHObjectTypes

typedef NS_ENUM(NSInteger, PHObjectType) {
    PHObjectTypeAsset                = 1,
    PHObjectTypeAssetCollection      = 2,
    PHObjectTypeCollectionList       = 3,
} API_AVAILABLE(macos(13), ios(16), tvos(16));

API_AVAILABLE_END

#endif
