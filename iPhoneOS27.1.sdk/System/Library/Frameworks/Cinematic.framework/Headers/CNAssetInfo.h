//
//  CNAssetInfo.h
//  Cinematic
//
//  Copyright © 2022-2023 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <AVFoundation/AVFoundation.h>
#import <Cinematic/CNRenderingSession.h>

NS_ASSUME_NONNULL_BEGIN


NS_REFINED_FOR_SWIFT
API_AVAILABLE(macos(27.0), ios(27.0)) API_UNAVAILABLE(watchos, tvos)
@interface CNAssetPreprocessConfiguration : NSObject

-(instancetype)initWithDestinationAssetURL:(NSURL *)destinationAssetURL;

/// Controls whether the color track in the output asset reference the source asset
/// or embed a copy of its sample data.
///
/// When YES, the output asset references the color from the
/// source asset. This keeps the intermediate file small, but the output asset will not be
/// portable — it depends on the source asset remaining at its original location.
///
/// When NO (the default), the color is copied into the output asset, making it
/// self-contained and portable at the cost of roughly doubling the storage required.
///
/// The disparity and metadata tracks are always embedded regardless of this setting.
@property BOOL referenceSourceAssetTracks;

@property (readonly) NSURL *destinationAssetURL;

@end

typedef NS_ENUM(NSInteger, CNCinematicResourceVersion) {
    CNCinematicResourceVersion1 =   1,
} API_AVAILABLE(macos(27.0), ios(27.0), tvos(27.0)) API_UNAVAILABLE(watchos);

typedef NS_ENUM(NSInteger, CNCinematicCapability) {
    /// No cinematic capabilities
    CNCinematicCapabilityNone = 0,
    /// The cinematic asset can be used without preprocessing
    CNCinematicCapabilityRenderable = 1,
    /// The cinematic asset needs preprocessing before it can be used
    CNCinematicCapabilityNeedsPreprocessing = 2,
} API_AVAILABLE(macos(27.0), ios(27.0), tvos(27.0)) API_UNAVAILABLE(watchos);

typedef NS_ENUM(NSInteger, CNResourceStatus) {
    /// Configuration is supported
    CNResourceStatusReady,
    /// Configuration is supported but requires download of resources
    CNResourceStatusNeedsDownloading,
    /// The device lacks hardware capabilities for the given configuration
    CNResourceStatusUnsupportedDevice,
    /// The given asset is unsupported on the current build
    CNResourceStatusUnsupportedAsset
} API_AVAILABLE(macos(27.0), ios(27.0), tvos(27.0)) API_UNAVAILABLE(watchos);

NS_REFINED_FOR_SWIFT
API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0)) API_UNAVAILABLE(watchos)
/// Information associated with an AVAsset for a cinematic video.
@interface CNAssetInfo : NSObject

/// Asynchronously checks the cinematic capability of an asset.
/// The completionHandler returns:
///     CNCinematicCapabilityNone if a cinematic metadata track is not present.
///     CNCinematicCapabilityRenderable if the cinematic asset can be used without preprocessing
///     CNCinematicCapabilityNeedsPreprocessing If cinematic asset needs preprocessing before it can be used
/// For assets that need preprocessing use [CNAssetInfo preprocessAssetWithConfiguration:completionHandler:] before using the asset
+ (void)checkCinematicCapabilityForAsset:(AVAsset *)asset completionHandler:(void (^)(CNCinematicCapability capability))completionHandler
API_AVAILABLE(macos(27.0), ios(27.0), tvos(27.0)) API_UNAVAILABLE(watchos);

/// Asynchronously check if asset is cinematic.
/// Only Cinematic assets containing a disparity track and a metadata track will return YES.
+ (void)checkIfCinematic:(AVAsset *)asset completionHandler:(void (^)(BOOL result))completionHandler
API_DEPRECATED_WITH_REPLACEMENT("checkCinematicCapabilityForAsset:completionHandler:",
                                macos(14.0, 27.0), ios(17.0, 27.0), tvos(17.0, 27.0));

/// Load cinematic asset information asynchronously.
+ (void)loadFromAsset:(AVAsset *)asset
        completionHandler:(void (^)(CNAssetInfo * _Nullable cinematicAssetInfo,
                                    NSError * _Nullable error))completionHandler;

@property (strong, readonly) AVAsset *asset;

@property (strong, readonly) NSArray<AVAssetTrack *> *allCinematicTracks;

@property (strong, readonly) AVAssetTrack *cinematicVideoTrack;
// In case the not renderable this will return an empty AVAssetTrack object where enabled is set to false
@property (strong, readonly) AVAssetTrack *cinematicDisparityTrack;
@property (strong, readonly) AVAssetTrack *cinematicMetadataTrack;

/// Time range over which all cinematic tracks are valid.
@property (readonly) CMTimeRange timeRange;

/// Natural size at which cinematic video would be rendered
@property (readonly) CGSize naturalSize;

/// Natural size at which cinematic video would be displayed.
/// Same as naturalSize with preferredTransform applied.
@property (readonly) CGSize preferredSize;

/// The preferred transform of the rendered image for display purposes.
/// Always the identity transform or a multiple of a 90º rotation with no scaling.
@property (readonly) CGAffineTransform preferredTransform;

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

/// Use of these properties where appropriate is preferred to help maintain future compatibility
API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0)) API_UNAVAILABLE(watchos)
@interface CNAssetInfo (AbstractTracks)

/// Track to be used for frame timing
@property (strong, readonly) AVAssetTrack *frameTimingTrack;

/// Tracks required to construct AVAssetReaderVideoCompositionOutput.
@property (strong, readonly) NSArray<AVAssetTrack *> *videoCompositionTracks;

/// Source video track IDs required to implement AVVideoCompositionInstruction protocol
@property (strong, readonly) NSArray<NSNumber *> *videoCompositionTrackIDs;

/// Source metadata track IDs required to implement AVVideoCompositionInstruction protocol
@property (strong, readonly) NSArray<NSNumber *> *sampleDataTrackIDs;

@end

API_AVAILABLE(macos(27.0), ios(27.0), tvos(27.0)) API_UNAVAILABLE(watchos)
@interface CNAssetInfo (CNAssetWithoutDisparity)

/// Check status for a set of resources.
/// @param resourceVersions Resource version(s) to check. Empty set to check all available resource versions.
/// @return The first encountered non-ready status, or CNResourceStatusReady if all are ready.
+(CNResourceStatus)resourceStatusForVersions:(NSSet<NSNumber *> *)resourceVersions
API_AVAILABLE(macos(27.0), ios(27.0), tvos(27.0)) API_UNAVAILABLE(watchos);

/// Downloads the resources required to render cinematic effects on assets
/// Resources are device-wide and are cached once downloaded
/// @param resourceVersions Resource version(s) to download. Pass an empty set to
///                        download all available resources
/// @param downloadTimeout Maximum seconds to wait before timeout. Pass \c defaultResourceDownloadTimeout
///   for the system default.
/// @param completionHandler Called on completion; \c error is \c nil on success.
/// @return A \c NSProgress tracking the download.
+(NSProgress *)downloadResourcesForVersions:(NSSet<NSNumber *> *)resourceVersions
                                    timeout:(NSTimeInterval)downloadTimeout
                          completionHandler:(void (^)(NSError * _Nullable error))completionHandler
API_AVAILABLE(macos(27.0), ios(27.0)) API_UNAVAILABLE(watchos, tvos);

/// Downloads the resources required to render cinematic effects for the given asset
/// Resources are device-wide and are cached once downloaded
/// @param downloadTimeout Maximum seconds to wait before timeout. Pass \c defaultResourceDownloadTimeout
///   for the system default.
/// @param completionHandler Called on completion; On success, \c newAssetInfo is a refreshed instance with the downloaded resources available; \c error is non-nil on failure
/// @return A \c NSProgress tracking the download.
-(NSProgress *)downloadResourcesWithTimeout:(NSTimeInterval)downloadTimeout
                          completionHandler:(void (^)(CNAssetInfo * _Nullable newAssetInfo, NSError * _Nullable error))completionHandler
API_AVAILABLE(macos(27.0), ios(27.0)) API_UNAVAILABLE(watchos, tvos);

/// Preprocesses the asset by generating a disparity track, writing the result to the
/// URL specified in `configuration`. Required for assets whose `cinematicCapability`
/// is \c CNCinematicCapabilityNeedsPreprocessing; on success \c assetInfo will be \c CNCinematicCapabilityRenderable.
///
/// Ensure \c resourceStatus is ready before calling — download resources first if needed.
///
/// @param configuration Destination URL and whether to embed or reference source tracks.
/// @param completionHandler Called on completion; on success \c assetInfo is the new preprocessed
///   asset and \c error is \c nil. On failure \c assetInfo is \c nil and \c error is non-nil.
/// @return A \c NSProgress tracking preprocessing progress.
-(NSProgress *)preprocessAssetWithConfiguration:(CNAssetPreprocessConfiguration *)configuration
                              completionHandler:(void (^)(CNAssetInfo * _Nullable assetInfo, NSError * _Nullable error))completionHandler
API_AVAILABLE(macos(27.0), ios(27.0)) API_UNAVAILABLE(watchos, tvos);

/// Default timeout value for resource download for
///  `+[CNAssetInfo downloadResourcesForVersions:timeout:completionHandler:]`
///  `-[CNAssetInfo downloadResourcesWithTimeout:completionHandler:]`
@property (class, readonly) NSTimeInterval defaultResourceDownloadTimeout
API_AVAILABLE(macos(27.0), ios(27.0)) API_UNAVAILABLE(watchos, tvos);

/// True only when an asset has been preprocessed
@property (readonly, getter=isPreprocessed) BOOL preprocessed
API_AVAILABLE(macos(27.0), ios(27.0), tvos(27.0)) API_UNAVAILABLE(watchos);

@property (readonly) CNCinematicCapability cinematicCapability
API_AVAILABLE(macos(27.0), ios(27.0), tvos(27.0)) API_UNAVAILABLE(watchos);

@property (readonly) CNResourceStatus resourceStatus
API_AVAILABLE(macos(27.0), ios(27.0), tvos(27.0)) API_UNAVAILABLE(watchos);

@end

NS_REFINED_FOR_SWIFT
API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0)) API_UNAVAILABLE(watchos)
/// Information about composition tracks added to an AVComposition for a cinematic asset.
@interface CNCompositionInfo : CNAssetInfo

/// Inserts a timeRange of a cinematic source asset into the corresponding tracks of a composition
/// - Parameters:
///  - timeRange: time range of the cinematic asset to be inserted
///  - assetInfo: identifies the tracks of the cinematic asset to be inserted
///  - atTime: the time at which the inserted tracks are to be presented by the composition; `kCMTimeInvalid` may be used to append at the end.
///  - error: AVError if it fails, as with `-[AVMutableCompositionTrack insertTimeRange:ofTrack:atTime:error:]`
/// - Returns: whether the insertion was successful
- (BOOL)insertTimeRange:(CMTimeRange)timeRange ofCinematicAssetInfo:(CNAssetInfo *)assetInfo atTime:(CMTime)startTime error:(NSError * _Nullable * _Nullable)outError;

@end


API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0)) API_UNAVAILABLE(watchos)
@interface AVMutableComposition (CNComposition)

/// Adds a group of empty tracks associated with a cinematic asset to a mutable composition.
/// - Returns: Information about the composition tracks added to the mutable composition.
/// Be sure to call insertTimeRange on the result to specify at least one time range of cinematic asset you'd like in the composition.
- (CNCompositionInfo *)addTracksForCinematicAssetInfo:(CNAssetInfo *)assetInfo preferredStartingTrackID:(CMPersistentTrackID)preferredStartingTrackID NS_REFINED_FOR_SWIFT;

@end

NS_ASSUME_NONNULL_END
