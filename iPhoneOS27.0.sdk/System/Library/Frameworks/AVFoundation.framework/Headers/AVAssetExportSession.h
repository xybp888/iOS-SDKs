#if !__has_include(<AVFCore/AVAssetExportSession.h>)
/*
	File:  AVAssetExportSession.h

	Framework:  AVFoundation
 
	Copyright 2010-2026 Apple Inc. All rights reserved.

*/


#import <AVFoundation/AVBase.h>
#import <AVFoundation/AVMediaFormat.h>
#import <AVFoundation/AVAudioProcessingSettings.h>
#import <Foundation/Foundation.h>
#import <CoreMedia/CMTime.h>
#import <CoreMedia/CMTimeRange.h>

// for CGSize
#import <CoreGraphics/CoreGraphics.h>

NS_ASSUME_NONNULL_BEGIN

// -- Export Preset Names --


/* These export options can be used to produce movie files with video size appropriate to the device.
   The export will not scale the video up from a smaller size. The video will be compressed using
   H.264 and the audio will be compressed using AAC.  */
AVF_EXPORT NSString *const AVAssetExportPresetLowQuality         API_AVAILABLE(macos(10.11), ios(4.0), tvos(9.0), visionos(1.0)) API_UNAVAILABLE(watchos);
AVF_EXPORT NSString *const AVAssetExportPresetMediumQuality      API_AVAILABLE(macos(10.11), ios(4.0), tvos(9.0), visionos(1.0)) API_UNAVAILABLE(watchos);
AVF_EXPORT NSString *const AVAssetExportPresetHighestQuality     API_AVAILABLE(macos(10.11), ios(4.0), tvos(9.0), visionos(1.0)) API_UNAVAILABLE(watchos);

/* These export options can be used to produce movie files with video size appropriate to the device.
   The export will not scale the video up from a smaller size. The video will be compressed using
   HEVC and the audio will be compressed using AAC.  */
AVF_EXPORT NSString *const AVAssetExportPresetHEVCHighestQuality 			API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0), visionos(1.0)) API_UNAVAILABLE(watchos);
AVF_EXPORT NSString *const AVAssetExportPresetHEVCHighestQualityWithAlpha	API_AVAILABLE(macos(10.15), ios(13.0), tvos(13.0), visionos(1.0)) API_UNAVAILABLE(watchos);

/* These export options can be used to produce movie files with the specified video size.
   The export will not scale the video up from a smaller size. The video will be compressed using
   H.264 and the audio will be compressed using AAC.  Some devices cannot support some sizes. */
AVF_EXPORT NSString *const AVAssetExportPreset640x480           API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), visionos(1.0)) API_UNAVAILABLE(watchos);
AVF_EXPORT NSString *const AVAssetExportPreset960x540           API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), visionos(1.0)) API_UNAVAILABLE(watchos);
AVF_EXPORT NSString *const AVAssetExportPreset1280x720          API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), visionos(1.0)) API_UNAVAILABLE(watchos);
AVF_EXPORT NSString *const AVAssetExportPreset1920x1080         API_AVAILABLE(macos(10.7), ios(5.0), tvos(9.0), visionos(1.0)) API_UNAVAILABLE(watchos);
AVF_EXPORT NSString *const AVAssetExportPreset3840x2160         API_AVAILABLE(macos(10.10), ios(9.0), tvos(9.0), visionos(1.0)) API_UNAVAILABLE(watchos);

/* These export options can be used to produce movie files with the specified video size.
   The export will not scale the video up from a smaller size. The video will be compressed using
   HEVC and the audio will be compressed using AAC.  Some devices cannot support some sizes. */
AVF_EXPORT NSString *const AVAssetExportPresetHEVC1920x1080				API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0), visionos(1.0)) API_UNAVAILABLE(watchos);
AVF_EXPORT NSString *const AVAssetExportPresetHEVC1920x1080WithAlpha	API_AVAILABLE(macos(10.15), ios(13.0), tvos(13.0), visionos(1.0)) API_UNAVAILABLE(watchos);
AVF_EXPORT NSString *const AVAssetExportPresetHEVC3840x2160				API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0), visionos(1.0)) API_UNAVAILABLE(watchos);
AVF_EXPORT NSString *const AVAssetExportPresetHEVC3840x2160WithAlpha	API_AVAILABLE(macos(10.15), ios(13.0), tvos(13.0), visionos(1.0)) API_UNAVAILABLE(watchos);
AVF_EXPORT NSString *const AVAssetExportPresetHEVC4320x2160				API_AVAILABLE(macos(26.0), ios(26.0), visionos(26.0)) API_UNAVAILABLE(tvos, watchos);
AVF_EXPORT NSString *const AVAssetExportPresetHEVC7680x4320				API_AVAILABLE(macos(12.1), ios(26.0), visionos(26.0)) API_UNAVAILABLE(tvos, watchos);

AVF_EXPORT NSString *const AVAssetExportPresetMVHEVC960x960				API_AVAILABLE(macos(14.0), ios(17.0), visionos(1.0)) API_UNAVAILABLE(tvos) API_UNAVAILABLE(watchos);
AVF_EXPORT NSString *const AVAssetExportPresetMVHEVC1440x1440			API_AVAILABLE(macos(14.0), ios(17.0), visionos(1.0)) API_UNAVAILABLE(tvos) API_UNAVAILABLE(watchos);
AVF_EXPORT NSString *const AVAssetExportPresetMVHEVC4320x4320			API_AVAILABLE(macos(26.0), ios(26.0), visionos(26.0)) API_UNAVAILABLE(tvos, watchos);
AVF_EXPORT NSString *const AVAssetExportPresetMVHEVC7680x7680			API_AVAILABLE(macos(26.0), ios(26.0), visionos(26.0)) API_UNAVAILABLE(tvos, watchos);

/*  This export option will produce an audio-only .m4a file with appropriate iTunes gapless playback data */
AVF_EXPORT NSString *const AVAssetExportPresetAppleM4A			API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), visionos(1.0)) API_UNAVAILABLE(watchos);

/* This export option will cause the media of all tracks to be passed through to the output exactly as stored in the source asset, except for
   tracks for which passthrough is not possible, usually because of constraints of the container format as indicated by the specified outputFileType.
   This option is not included in the arrays returned by -allExportPresets and -exportPresetsCompatibleWithAsset. */
AVF_EXPORT NSString *const AVAssetExportPresetPassthrough		API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), visionos(1.0)) API_UNAVAILABLE(watchos);

/* This export option will produce a QuickTime movie with Apple ProRes 422 video and LPCM audio. */
AVF_EXPORT NSString *const AVAssetExportPresetAppleProRes422LPCM	API_AVAILABLE(macos(10.7), ios(15.0)) API_UNAVAILABLE(tvos, watchos, visionos);

/* This export option will produce a QuickTime movie with Apple ProRes 4444 video and LPCM audio. */
AVF_EXPORT NSString *const AVAssetExportPresetAppleProRes4444LPCM  API_AVAILABLE(macos(10.15), ios(15.0)) API_UNAVAILABLE(tvos, watchos, visionos);

#if TARGET_OS_OSX

/* These export options are used to produce files that can be played on the specified Apple devices. 
	These presets are available for Desktop export only.
	The files should have .m4v extensions (or .m4a for exports with audio only sources). */
AVF_EXPORT NSString *const AVAssetExportPresetAppleM4VCellular	API_AVAILABLE(macos(10.7)) API_UNAVAILABLE(ios, tvos, watchos, visionos);
AVF_EXPORT NSString *const AVAssetExportPresetAppleM4ViPod		API_AVAILABLE(macos(10.7)) API_UNAVAILABLE(ios, tvos, watchos, visionos);
AVF_EXPORT NSString *const AVAssetExportPresetAppleM4V480pSD	API_AVAILABLE(macos(10.7)) API_UNAVAILABLE(ios, tvos, watchos, visionos);
AVF_EXPORT NSString *const AVAssetExportPresetAppleM4VAppleTV	API_AVAILABLE(macos(10.7)) API_UNAVAILABLE(ios, tvos, watchos, visionos);
AVF_EXPORT NSString *const AVAssetExportPresetAppleM4VWiFi		API_AVAILABLE(macos(10.7)) API_UNAVAILABLE(ios, tvos, watchos, visionos);
AVF_EXPORT NSString *const AVAssetExportPresetAppleM4V720pHD	API_AVAILABLE(macos(10.7)) API_UNAVAILABLE(ios, tvos, watchos, visionos);
AVF_EXPORT NSString *const AVAssetExportPresetAppleM4V1080pHD	API_AVAILABLE(macos(10.8)) API_UNAVAILABLE(ios, tvos, watchos, visionos);

#endif // TARGET_OS_OSX


@class AVAsset;
@class AVAssetExportSessionInternal;
@class AVAudioMix;
@class AVVideoComposition;
@class AVMetadataItemFilter;
@protocol AVVideoCompositing;
@class AVMetadataItem;

typedef NS_ENUM(NSInteger, AVAssetExportSessionStatus) {
	AVAssetExportSessionStatusUnknown = 0,
    AVAssetExportSessionStatusWaiting = 1,
    AVAssetExportSessionStatusExporting = 2,
    AVAssetExportSessionStatusCompleted = 3,
    AVAssetExportSessionStatusFailed = 4,
    AVAssetExportSessionStatusCancelled = 5
};

/// A bitfield type that specifies output handling policies for alternate tracks in a track group.
typedef NS_OPTIONS(NSUInteger, AVAssetTrackGroupOutputHandling) {
	/// No specific processing directives are applied to alternate tracks. The output is produced without regard to alternate track group assignments in the original asset.
	AVAssetTrackGroupOutputHandlingNone						= 0UL,
	/// Preserve alternate tracks via pass-through.
	AVAssetTrackGroupOutputHandlingPreserveAlternateTracks	= (1UL << 0),

	AVAssetTrackGroupOutputHandlingDefaultPolicy			= AVAssetTrackGroupOutputHandlingNone
} API_AVAILABLE(macos(13.0), ios(16.0), tvos(16.0), visionos(1.0)) API_UNAVAILABLE(watchos);

/// The reason that configuring the export session for resumption failed.
typedef NSString * AVAssetExportSessionResumptionFailureReason NS_SWIFT_NAME(AVAssetExportSession.ResumptionFailureReason) NS_EXTENSIBLE_STRING_ENUM API_AVAILABLE(macos(27.0), ios(27.0), tvos(27.0), visionos(27.0)) API_UNAVAILABLE(watchos);

/// Indicates that resumption isn't supported for this preset and platform combination.
///
/// You can continue the export, but it runs as a non-resumable (default) export.
AVF_EXPORT AVAssetExportSessionResumptionFailureReason const AVAssetExportSessionResumptionFailureReasonUnsupportedForPresetOnPlatform API_AVAILABLE(macos(27.0), ios(27.0), tvos(27.0), visionos(27.0)) API_UNAVAILABLE(watchos);

/// Indicates that the specified temporary files directory doesn't exist.
///
/// Create the temporary files directory and call ``configureForResumableExportWithCompletionHandler:`` again.
AVF_EXPORT AVAssetExportSessionResumptionFailureReason const AVAssetExportSessionResumptionFailureReasonTemporaryDirectoryDoesNotExist API_AVAILABLE(macos(27.0), ios(27.0), tvos(27.0), visionos(27.0)) API_UNAVAILABLE(watchos);

/// Indicates the export session settings are incompatible with resumable export.
AVF_EXPORT AVAssetExportSessionResumptionFailureReason const AVAssetExportSessionResumptionFailureReasonIncompatibleSessionSettings  API_AVAILABLE(macos(27.0), ios(27.0), tvos(27.0), visionos(27.0)) API_UNAVAILABLE(watchos);

/// Indicates that the contents of the specified temporary files directory are inconsistent with the current resuming export.
///
/// You're likely aliasing two distinct exports together. Use a unique temporary files directory for each export, or clear the directory before resuming.
AVF_EXPORT AVAssetExportSessionResumptionFailureReason const AVAssetExportSessionResumptionFailureReasonIncompatibleTemporaryDirectoryContents API_AVAILABLE(macos(27.0), ios(27.0), tvos(27.0), visionos(27.0)) API_UNAVAILABLE(watchos);

/// The current resumption state of the export session.
///
/// Configure a resumable export session with ``AVAssetExportSession/configureForResumableExportWithCompletionHandler:``.
API_AVAILABLE(macos(27.0), ios(27.0), tvos(27.0), visionos(27.0)) API_UNAVAILABLE(watchos)
NS_REFINED_FOR_SWIFT
@interface AVAssetExportSessionResumptionState : NSObject

/// A Boolean value that indicates whether the export session is configured as resumable.
///
/// If `true`, the export session is configured as resumable. If `false`, the export session will remain as non-resumable (default). You can still call ``AVAssetExportSession/exportAsynchronouslyWithCompletionHandler:`` when this property is `false`.
@property (readonly, getter=isResumptionConfigured) BOOL resumptionConfigured;

/// A Boolean value that indicates whether or not a resuming export is continuing from a previous state.
///
/// A value of `true` means the export resumes from previous results; a value of `false` means it starts from the beginning. This value is valid only when ``resumptionConfigured`` is `true`.
@property (readonly, getter=isResumingFromPreviousState) BOOL resumingFromPreviousState;

/// The reason that the export session couldn't be configured as resumable.
///
/// This value is valid only when ``resumptionConfigured`` is `false`.
@property (readonly, nullable) AVAssetExportSessionResumptionFailureReason configurationFailureReason;

@end // AVAssetExportSessionResumptionState

/// An AVAssetExportSession creates a new timed media resource from the contents of an existing AVAsset in the form described by a specified export preset.
/// 
/// Prior to initializing an instance of AVAssetExportSession, you can invoke
/// +allExportPresets to obtain the complete list of presets available. Use
/// +exportPresetsCompatibleWithAsset: to obtain a list of presets that are compatible
/// with a specific AVAsset.
/// 
/// To configure an export, initialize an AVAssetExportSession with an AVAsset that contains
/// the source media, an AVAssetExportPreset, the output file type, (a UTI string from
/// those defined in AVMediaFormat.h) and the output URL.
/// 
/// After configuration is complete, invoke exportAsynchronouslyWithCompletionHandler:
/// to start the export process. This method returns immediately; the export is performed
/// asynchronously. Invoke the -progress method to check on the progress. Note that in
/// some cases, depending on the capabilities of the device, when multiple exports are
/// attempted at the same time some may be queued until others have been completed. When
/// this happens, the status of a queued export will indicate that it's "waiting".
/// 
/// Whether the export fails, completes, or is cancelled, the completion handler you
/// supply to -exportAsynchronouslyWithCompletionHandler: will be called. Upon
/// completion, the status property indicates whether the export has completed
/// successfully. If it has failed, the value of the error property supplies additional
/// information about the reason for the failure.
NS_SWIFT_NONSENDABLE
API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), visionos(1.0)) API_UNAVAILABLE(watchos)
@interface AVAssetExportSession : NSObject
{
@private
	AVAssetExportSessionInternal  *_exportSession;
}
AV_INIT_UNAVAILABLE

/// Returns an instance of AVAssetExportSession for the specified source asset and preset.
/// 
/// If the specified asset belongs to a mutable subclass of AVAsset, AVMutableComposition or AVMutableMovie, the results of any export-related operation are undefined if you mutate the asset after the operation commences. These operations include but are not limited to: 1) testing the compatibility of export presets with the asset, 2) calculating the maximum duration or estimated length of the output file, and 3) the export operation itself.
/// 
/// - Parameter asset: An AVAsset object that is intended to be exported.
/// - Parameter presetName: An NSString specifying the name of the preset template for the export.
/// 
/// - Returns: An instance of AVAssetExportSession.
+ (nullable instancetype)exportSessionWithAsset:(AVAsset *)asset presetName:(NSString *)presetName API_AVAILABLE(macos(10.7), ios(4.1), tvos(9.0), visionos(1.0)) API_UNAVAILABLE(watchos);

/// Initialize an AVAssetExportSession with the specified preset and set the source to the contents of the asset.
///
/// If the specified asset belongs to a mutable subclass of AVAsset, AVMutableComposition or AVMutableMovie, the results of any export-related operation are undefined if you mutate the asset after the operation commences. These operations include but are not limited to: 1) testing the compatibility of export presets with the asset, 2) calculating the maximum duration or estimated length of the output file, and 3) the export operation itself.
/// 
/// - Parameter asset: An AVAsset object that is intended to be exported.
/// - Parameter presetName: An NSString specifying the name of the preset template for the export.
/// 
/// - Returns: Returns the initialized AVAssetExportSession.
- (nullable instancetype)initWithAsset:(AVAsset *)asset presetName:(NSString *)presetName NS_DESIGNATED_INITIALIZER;

/* AVAssetExportSession properties are key-value observable unless documented otherwise */

/* Swift apps should use AVAssetExportSession.states to monitor the session */

/// Indicates the name of the preset with which the export session was initialized.
@property (nonatomic, readonly) NSString *presetName;

/// Indicates the instance of AVAsset with which the export session was initialized.
@property (nonatomic, retain, readonly) AVAsset *asset API_AVAILABLE(macos(10.8), ios(5.0), tvos(9.0), visionos(1.0)) API_UNAVAILABLE(watchos);

/// Indicates the type of file to be written by the export session.
///
/// The value of this property must be set before you invoke -exportAsynchronouslyWithCompletionHandler:; otherwise -exportAsynchronouslyWithCompletionHandler: will raise an NSInternalInconsistencyException. Setting the value of this property to a file type that's not among the session's supported file types will result in an NSInvalidArgumentException. See supportedFileTypes.
@property (nonatomic, copy, nullable) AVFileType outputFileType
#if defined(__swift__)
API_DEPRECATED("Use export(to:as:) async throws instead", macos(10.7, 27.0), ios(4.0, 27.0), tvos(9.0, 27.0), visionos(1.0, 27.0)) API_UNAVAILABLE(watchos)
#endif
;
/// Indicates the URL of the export session's output. You may use [[UTType typeWithIdentifier:outputFileType] preferredFilenameExtension] to obtain an appropriate path extension for the outputFileType you have specified. For more information, see <UniformTypeIdentifiers/UTType.h>.
@property (nonatomic, copy, nullable) NSURL *outputURL
#if defined(__swift__)
API_DEPRECATED("Use export(to:as:) async throws instead", macos(10.7, 27.0), ios(4.0, 27.0), tvos(9.0, 27.0), visionos(1.0, 27.0)) API_UNAVAILABLE(watchos)
#endif
;
/// Indicates that the output file should be optimized for network use, e.g. that a QuickTime movie file should support "fast start".
@property (nonatomic) BOOL shouldOptimizeForNetworkUse;

/// Determines whether or not parallelization can be employed in the export.
/// 
/// On select platforms, there may be opportunities to expedite the export by using additional resources in parallel.
/// If set to YES, export parallelization will be enabled, only if parallelization requirements are met. There will
/// be no error signaled if export parallelization is not achievable, and instead the export will proceed as normal
/// (without parallelization).
/// If set to NO, export parallelization will not be used.
@property (nonatomic) BOOL allowsParallelizedExport API_AVAILABLE(macos(14.0)) API_UNAVAILABLE(ios, tvos, watchos, visionos); // defaults to YES

/// Indicates the status of the export session.
@property (nonatomic, readonly) AVAssetExportSessionStatus status
#if defined(__swift__)
API_DEPRECATED("Use states(updateInterval:) instead", macos(10.7, 15.0), ios(4.0, 18.0), tvos(9.0, 18.0), visionos(1.0, 2.0)) API_UNAVAILABLE(watchos)
#endif
;

/// Describes the error that occured if the export status is AVAssetExportSessionStatusFailed.
@property (nonatomic, readonly, nullable) NSError *error
#if defined(__swift__)
API_DEPRECATED("Use export(to:as:) async throws instead", macos(10.7, 15.0), ios(4.0, 18.0), tvos(9.0, 18.0), visionos(1.0, 2.0)) API_UNAVAILABLE(watchos)
#endif
;

/// Starts the asynchronous execution of an export session.
/// 
/// Initiates an asynchronous export operation and returns immediately.
/// 
/// - Parameter handler: If internal preparation for export fails, the handler will be invoked synchronously. The handler may also be called asynchronously after -exportAsynchronouslyWithCompletionHandler: returns, in the following cases: 1) if a failure occurs during the export, including failures of loading, re-encoding, or writing media data to the output, 2) if -cancelExport is invoked, 3) if export session succeeds, having completely written its output to the outputURL. In each case, AVAssetExportSession.status will signal the terminal state of the asset reader, and if a failure occurs, the NSError that describes the failure can be obtained from the error property.
- (void)exportAsynchronouslyWithCompletionHandler:(void (^ NS_SWIFT_SENDABLE)(void))handler
#if defined(__swift__)
API_DEPRECATED_WITH_REPLACEMENT("export(to:as:) async throws", macos(10.7, 15.0), ios(4.0, 18.0), tvos(9.0, 18.0), visionos(1.0, 2.0)) API_UNAVAILABLE(watchos)
#endif
;

/// Specifies the progress of the export on a scale from 0 to 1.0. A value of 0 means the export has not yet begun, A value of 1.0 means the export is complete. This property is not key-value observable.
@property (nonatomic, readonly) float progress
#if defined(__swift__)
API_DEPRECATED("Use states(updateInterval:) instead", macos(10.7, 27.0), ios(4.0, 27.0), tvos(9.0, 27.0), visionos(1.0, 27.0)) API_UNAVAILABLE(watchos)
#endif
;

/// Cancels the execution of an export session.
/// 
/// Cancel can be invoked when the export is running.
- (void)cancelExport
#if defined(__swift__)
API_DEPRECATED("Use Task.cancel() instead", macos(10.7, 27.0), ios(4.0, 27.0), tvos(9.0, 27.0), visionos(1.0, 27.0)) API_UNAVAILABLE(watchos)
#endif
;

@end

API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), visionos(1.0)) API_UNAVAILABLE(watchos)
@interface AVAssetExportSession (AVAssetExportSessionPresets)

/// Returns all available export preset names.
/// 
/// Returns an array of NSStrings with the names of all available presets. Note that not all presets are 
/// compatible with all AVAssets.
/// 
/// - Returns: An NSArray containing an NSString for each of the available preset names.
+ (NSArray<NSString *> *)allExportPresets;

/// Returns only the identifiers compatible with the given AVAsset object.
/// 
/// Not all export presets are compatible with all AVAssets. For example an video only asset is not compatible with an audio only preset.
/// This method returns only the identifiers for presets that will be compatible with the given asset. 
/// You should pass in an ``AVAsset`` that is ready to be exported.
/// In order to ensure that the setup and running of the export operation will succeed using a given preset no significant changes
/// (such as adding or deleting tracks) should be made to the asset between retrieving compatible identifiers and performing the export operation.
/// This method will access the tracks property of the AVAsset to build the returned NSArray. To avoid blocking the calling thread, 
/// the tracks property should be loaded using the AVAsynchronousKeyValueLoading protocol before calling this method.
/// 
/// - Parameter asset: An AVAsset object that is intended to be exported.
/// 
/// - Returns: An NSArray containing NSString values for the identifiers of compatible export types.  
/// 								The array is a complete list of the valid identifiers that can be used as arguments to 
/// 								initWithAsset:presetName: with the specified asset.
+ (NSArray<NSString *> *)exportPresetsCompatibleWithAsset:(AVAsset *)asset API_DEPRECATED_WITH_REPLACEMENT("determineCompatibilityOfExportPreset:withAsset:outputFileType:completionHandler:", macos(10.7, 13.0), ios(4.0, 16.0), tvos(9.0, 16.0)) API_UNAVAILABLE(watchos, visionos);

/// Performs an inspection on the compatibility of an export preset, AVAsset and output file type. Calls the completion handler with YES if the arguments are compatible; NO otherwise.
/// 
/// Not all export presets are compatible with all AVAssets and file types. This method can be used to query compatibility.
/// In order to ensure that the setup and running of an export operation will succeed using a given preset no significant changes 
/// (such as adding or deleting tracks) should be made to the asset between retrieving compatible identifiers and performing the export operation.
/// 
/// - Parameter presetName: An NSString specifying the name of the preset template for the export.
/// - Parameter asset: An AVAsset object that is intended to be exported.
/// - Parameter outputFileType: An AVFileType indicating a file type to check; or nil, to query whether there are any compatible types.
/// - Parameter handler: A callback that receives the compatibility result.
+ (void)determineCompatibilityOfExportPreset:(NSString *)presetName withAsset:(AVAsset *)asset outputFileType:(nullable AVFileType)outputFileType completionHandler:(void (^ NS_SWIFT_SENDABLE)(BOOL compatible))handler API_AVAILABLE(macos(10.9), ios(6.0), tvos(9.0), visionos(1.0)) API_UNAVAILABLE(watchos) NS_SWIFT_ASYNC_NAME(compatibility(ofExportPreset:with:outputFileType:));

@end // AVAssetExportSessionPresets

API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), visionos(1.0)) API_UNAVAILABLE(watchos)
@interface AVAssetExportSession (AVAssetExportSessionFileTypes)

/// Indicates the types of files the target can write, according to the preset the target was initialized with.
///
/// Does not perform an inspection of the AVAsset to determine whether its contents are compatible with the supported file types. If you need to make that determination before initiating the export, use - (void)determineCompatibleFileTypesWithCompletionHandler:(void (^)(NSArray *compatibleFileTypes))handler:.
@property (nonatomic, readonly) NSArray<AVFileType> *supportedFileTypes;

/// Performs an inspection on the AVAsset and Preset the object was initialized with to determine a list of file types the ExportSession can write.
/// 
/// This method is different than the supportedFileTypes property in that it performs an inspection of the AVAsset in order to determine its compatibility with each of the session's supported file types.
/// 
/// - Parameter handler: Called when the inspection completes with an array of file types the ExportSession can write. Note that this may have a count of zero.
- (void)determineCompatibleFileTypesWithCompletionHandler:(void (^ NS_SWIFT_SENDABLE)(NSArray<AVFileType> *compatibleFileTypes))handler API_AVAILABLE(macos(10.9), ios(6.0), tvos(9.0), visionos(1.0)) API_UNAVAILABLE(watchos) NS_SWIFT_ASYNC_NAME(getter:compatibleFileTypes());

@end // AVAssetExportSessionFileTypes

API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), visionos(1.0)) API_UNAVAILABLE(watchos)
@interface AVAssetExportSession (AVAssetExportSessionDurationAndLength)

/// Specifies a time range to be exported from the source. The default timeRange of an export session is kCMTimeZero..kCMTimePositiveInfinity, meaning that the full duration of the asset will be exported.
@property (nonatomic) CMTimeRange timeRange;

/// Provides an estimate of the maximum duration of exported media that is possible given the source asset, the export preset, and the current value of fileLengthLimit. The export will not stop when it reaches this maximum duration; set the timeRange property to export only a certain time range.
@property (nonatomic, readonly) CMTime maxDuration API_DEPRECATED("Use estimateMaximumDurationWithCompletionHandler: instead", macos(10.14, 15.0), ios(4.0, 18.0), tvos(9.0, 18.0)) API_UNAVAILABLE(watchos, visionos);

/// Indicates the estimated byte size of exported file. Returns zero when export preset is AVAssetExportPresetPassthrough, AVAssetExportPresetAppleProRes422LPCM or AVAssetExportPresetAppleProRes4444LPCM. This property will also return zero if a numeric value (ie. not invalid, indefinite, or infinite) for the timeRange property has not been set. Note that the returned value does not take into account the source asset information. For a more accurate estimation, use estimateOutputFileLengthWithCompletionHandler.
@property (nonatomic, readonly) long long estimatedOutputFileLength API_DEPRECATED("Use estimateOutputFileLengthWithCompletionHandler: instead", macos(10.9, 15.0), ios(5.0, 18.0), tvos(5.0, 18.0)) API_UNAVAILABLE(watchos, visionos);

/// Indicates the file length that the output of the session should not exceed. Depending on the content of the source asset, it is possible for the output to slightly exceed the file length limit. The length of the output file should be tested if you require that a strict limit be observed before making use of the output. See also maxDuration and timeRange.
@property (nonatomic) long long fileLengthLimit API_AVAILABLE(macos(10.14), ios(4.0), tvos(9.0), visionos(1.0)) API_UNAVAILABLE(watchos);

/// Starts the asynchronous execution of estimating the maximum duration of the export based on the asset, preset, and fileLengthLimit associated with the export session.
/// 
/// If fileLengthLimit is not set on the export session, fileLengthLimit will be assumed to be the maximum file size specified by the preset (if any); else infinite.
/// 
/// - Parameter handler: A callback that receives the estimated maximum duration, or <doc://com.apple.documentation/documentation/coremedia/cmtime/invalid> if an error occurs. The error parameter will be non-nil if an error occurs.
- (void)estimateMaximumDurationWithCompletionHandler:(void (^ NS_SWIFT_SENDABLE)(CMTime estimatedMaximumDuration, NSError * _Nullable error ))handler API_AVAILABLE(macos(10.15), ios(13.0), tvos(13.0), visionos(1.0)) API_UNAVAILABLE(watchos) NS_SWIFT_ASYNC_NAME(getter:estimatedMaximumDuration());

/// Starts the asynchronous execution of estimating the output file length of the export based on the asset, preset, and timeRange associated with the export session.
/// 
/// If timeRange is not set on the export session, timeRange will be assumed to be the full time range of the asset.
/// 
/// - Parameter handler: A callback that receives the estimated output file length in bytes, if it can be determined; 0 otherwise. The error parameter will be non-nil if an error occurs.
- (void)estimateOutputFileLengthWithCompletionHandler:(void (^ NS_SWIFT_SENDABLE)(int64_t estimatedOutputFileLength, NSError * _Nullable error ))handler API_AVAILABLE(macos(10.15), ios(13.0), tvos(13.0), visionos(1.0)) API_UNAVAILABLE(watchos) NS_SWIFT_ASYNC_NAME(getter:estimatedOutputFileLengthInBytes());

@end // AVAssetExportSessionDurationAndLength

API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), visionos(1.0)) API_UNAVAILABLE(watchos)
@interface AVAssetExportSession (AVAssetExportSessionMetadata)

/// Specifies an NSArray of AVMetadataItems that are to be written to the output file by the export session.
///
/// If the value of this key is nil, any existing metadata in the exported asset will be translated as accurately as possible into the appropriate metadata keyspace for the output file and written to the output.
@property (nonatomic, copy, nullable) NSArray<AVMetadataItem *> *metadata;

/// Specifies a filter object to be used during export to determine which metadata items should be transferred from the source asset.
///
/// If the value of this key is nil, no filter will be applied. This is the default. The filter will not be applied to metadata set with via the metadata property. To apply the filter to metadata before it is set on the metadata property, see the methods in AVMetadataItem's AVMetadataItemArrayFiltering category.
@property (nonatomic, retain, nullable) AVMetadataItemFilter *metadataItemFilter API_AVAILABLE(macos(10.9), ios(7.0), tvos(9.0), visionos(1.0)) API_UNAVAILABLE(watchos);

@end // AVAssetExportSessionMetadata

API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), visionos(1.0)) API_UNAVAILABLE(watchos)
@interface AVAssetExportSession (AVAssetExportSessionMediaProcessing)

/// Indicates the processing algorithm used to manage audio pitch for scaled audio edits.
///
/// Constants for various time pitch algorithms, e.g. AVAudioTimePitchAlgorithmSpectral, are defined in AVAudioProcessingSettings.h. An NSInvalidArgumentException will be raised if this property is set to a value other than the constants defined in that file. The default value is AVAudioTimePitchAlgorithmSpectral.
@property (nonatomic, copy) AVAudioTimePitchAlgorithm audioTimePitchAlgorithm API_AVAILABLE(macos(10.9), ios(7.0), tvos(9.0), visionos(1.0)) API_UNAVAILABLE(watchos);

/// Indicates whether non-default audio mixing is enabled for export and supplies the parameters for audio mixing. Ignored when export preset is AVAssetExportPresetPassthrough.
@property (nonatomic, copy, nullable) AVAudioMix *audioMix;

/// Indicates whether video composition is enabled for export and supplies the instructions for video composition. Ignored when export preset is AVAssetExportPresetPassthrough.
@property (nonatomic, copy, nullable) AVVideoComposition *videoComposition;

/// Indicates the custom video compositor instance used, if any.
@property (nonatomic, readonly, nullable) id <AVVideoCompositing> customVideoCompositor API_AVAILABLE(macos(10.9), ios(7.0), tvos(9.0), visionos(1.0)) API_UNAVAILABLE(watchos);

/// Defines export policy for handling alternate audio tracks
/// 
/// Specifies the handling of audio tracks that are members of the same alternate track group corresponding to an exported audio track in the source asset.
/// If no audio track group is present, the value of this property has no effect.
/// If necessary, use the trackGroups property of AVAsset to determine whether any audio track groups are present.
/// The AVAudioMix property is not allowed to be used when also specifying alternate track output handling. An exception will be thrown if both are specified.
@property (nonatomic) AVAssetTrackGroupOutputHandling audioTrackGroupHandling API_AVAILABLE(macos(13.0), ios(16.0), tvos(16.0), visionos(1.0)) API_UNAVAILABLE(watchos);

@end // AVAssetExportSessionMediaProcessing

API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), visionos(1.0)) API_UNAVAILABLE(watchos)
@interface AVAssetExportSession (AVAssetExportSessionMultipass)

/// Determines whether the export session can perform multiple passes over the source media to achieve better results.
/// 
/// When the value for this property is YES, the export session can produce higher quality results at the expense of longer export times. Setting this property to YES may also require the export session to write temporary data to disk during the export. To control the location of temporary data, use the property directoryForTemporaryFiles.
/// 
/// The default value is NO. Not all export session configurations can benefit from performing multiple passes over the source media. In these cases, setting this property to YES has no effect.
/// 
/// This property cannot be set after the export has started.
@property (nonatomic) BOOL canPerformMultiplePassesOverSourceMediaData API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), visionos(1.0)) API_UNAVAILABLE(watchos);

/// Specifies a directory that is suitable for containing temporary files generated during the export process
/// 
/// AVAssetExportSession may need to write temporary files when configured in certain ways, such as when canPerformMultiplePassesOverSourceMediaData is set to YES. This property can be used to control where in the filesystem those temporary files are created. All temporary files will be deleted when the export is completed, is canceled, or fails.
/// 
/// When the value of this property is nil, the export session will choose a suitable location when writing temporary files. The default value is nil.
/// 
/// This property cannot be set after the export has started. The export will fail if the URL points to a location that is not a directory, does not exist, is not on the local file system, or if a file cannot be created in this directory (for example, due to insufficient permissions or sandboxing restrictions).
@property (nonatomic, copy, nullable) NSURL *directoryForTemporaryFiles API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), visionos(1.0)) API_UNAVAILABLE(watchos);

@end // AVAssetExportSessionMultipass

API_AVAILABLE(macos(27.0), ios(27.0), tvos(27.0), visionos(27.0)) API_UNAVAILABLE(watchos)
@interface AVAssetExportSession (AVAssetExportSessionResumable)

/// Attempts to configure the export session into resumption mode.
///
/// For select encoders, an export can be performed in temporal segments, and then stitched together at the end.
///
/// You are responsible for configuring the export session identically for subsequent sessions, if the export is to be resumed from partial results from a previous run.
///
/// - Important: ``directoryForTemporaryFiles`` must be specified for resumable exports. This directory holds the temporary files for resumable exports, which allows the export to resume on a subsequent instantiation. You are responsible for making the ``directoryForTemporaryFiles`` unique and deterministic across app launches or device reboots if the session is intended to be resumable after such events. You must ensure that it doesn't re-use a temporary directory corresponding to a different resumable export session, or the contents between different exports may be erroneously combined.
///
/// This method validates that the currently configured export properties allow resumption, and interrogates the contents of ``directoryForTemporaryFiles`` to determine whether this is a resuming session or a new one. As such, call this method after all settings are finalized for this export session, that is, just prior to ``exportAsynchronouslyWithCompletionHandler:``.
///
/// ``resumptionState`` details the currently configured resumption state of the export session. Even if resumptionState indicates that not all conditions for resumption are met, you may still call ``exportAsynchronouslyWithCompletionHandler:`` using the current session, and the export proceeds in the default, non-resuming manner.
///
/// This method cannot be called after the export has started.
/// 
/// Call ``cancelExport`` if an in-flight export needs to be interrupted. The export maintains the partial results.
///
/// You are responsible for deleting the temporary directory and its contents if the export will never be resumed.
///
/// Because intermediate files are written to support the resume functionality, resumable exports typically double the NAND accesses, because the samples need to be written to disk twice.
///
/// - Parameter handler: A callback that receives the resumption configuration state. If configuration fails, the system might call the handler synchronously.
- (void)configureForResumableExportWithCompletionHandler:(void (^)(AVAssetExportSessionResumptionState * resumptionState))handler NS_REFINED_FOR_SWIFT;

@end // AVAssetExportSessionResumable

NS_ASSUME_NONNULL_END

#else
#import <AVFCore/AVAssetExportSession.h>
#endif
