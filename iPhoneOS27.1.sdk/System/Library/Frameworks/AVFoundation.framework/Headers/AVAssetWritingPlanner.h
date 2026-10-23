#if !__has_include(<AVFCore/AVAssetWritingPlanner.h>)
/*
	File:  AVAssetWritingPlanner.h

	Framework:  AVFoundation

	Copyright (c) 2025-2026 Apple Inc. All rights reserved.

	AVAssetWritingPlanner orchestrates an incremental and resumable asset file
	writing session, breaking exports into discrete segments that can be written
	independently and resumed after interruption. Not intended for real-time
	applications. See class documentation below for the full workflow.

*/


#import <AVFoundation/AVBase.h>
#import <Foundation/Foundation.h>
#import <CoreFoundation/CFBase.h>
#import <AVFoundation/AVVideoSettings.h>
#import <AVFoundation/AVComposition.h>
#import <AVFoundation/AVAssetWriterInput.h>

#import <CoreMedia/CMTime.h>
#import <CoreMedia/CMTimeRange.h>

#define AVF_VTCOMPRESSIONSESSION_AVAILABLE (__has_include(<VideoToolbox/VTCompressionSession.h>))

#if AVF_VTCOMPRESSIONSESSION_AVAILABLE
#import <VideoToolbox/VTCompressionSession.h>
#endif // AVF_VTCOMPRESSIONSESSION_AVAILABLE

NS_ASSUME_NONNULL_BEGIN

/// AVPlannedVideoSegmentBoundaryGuidelines provides guidance on determining planned segment boundaries for a video track in an incremental writing session executed by the AVAssetWritingPlanner.
///
/// The properties provide guidance on determining segment boundaries for a video track in an incremental writing session. All conditions should be supported for best results. The client should choose frame count and minimum duration that meet the minimum requirement. However, the client should also consider the balance between overhead caused by completing and saving states for small segments, and the cost of having to redo a large segment if the incremental session stopped in the middle of a segment due to errors or crashes. For example, use 1 minute segments for 4K60fps video.
typedef struct {
	/// The minimum number of frames in each incremental segment. 0 means that incremental segmentation is not supported for this codecType. 1 means there is no frame count restriction for incremental encoding for this codecType. Using 1 for segment frame count is not recommended because of the performance overhead, so the client should choose a value that represents a reasonable amount of work.
	NSInteger	minimumFrameCount;
	/// The minimum duration of each incremental segment. kCMTimeZero means there is no minimum segment duration requirement. kCMTimePositiveInfinity means that incremental segmentation is not supported for this codecType.
	CMTime		minimumDuration;
} AVPlannedVideoSegmentBoundaryGuidelines API_AVAILABLE(macos(27.0), ios(27.0), tvos(27.0), visionos(27.0)) API_UNAVAILABLE(watchos)
NS_SWIFT_NAME(AVAssetWritingPlanner.SegmentBoundaryGuidelines);

@class AVAssetTrackPlan, AVPlannedVideoSegmentConfiguration, AVPlannedSegmentWritingRequest, AVAssetWritingPlannerProgress;

/// AVAssetWritingPlanner orchestrates incremental writing of media files.
/// 
/// AVAssetWritingPlanner orchestrates an incremental and resumable asset file
/// writing session. It keeps track of the progress of the incremental segments,
/// and can resume the writing from the last checkpoint. This is NOT intended for
/// any real time applications. Also, not all tracks can be written incrementally.
/// The workflow is as follows:
/// 1. The client creates the planner with a unique directoryForTemporaryFiles.
/// 2. The client tells the planner which tracks are to be written incrementally
/// by calling the "planTrack:withSegmentsGeneratedBy:" method, providing a
/// callback block that writes one segment per block invocation.
/// 3. The client kicks off the incremental writing session by calling the
/// "executePlanWithCompletionHandler" method.
/// 4. The planner will call the writingSegmentCallbackBlock to ask the client to
/// write one incremental segment of one track at a time. The client code
/// should write one incremental segment according to the
/// "AVPlannedSegmentWritingRequest" object passed in to the callback block.
/// Clients must call "finish" or "finishWithError" or "finishWithClientState"
/// or "cancel" methods on the request object when it finishes the segment
/// successfully, or encountered an error, or wants to cancel the writing of
/// the segment.
/// 5. At the end of the writing, after all incremental segments are finished,
/// the planner calls the completionHandler. The client can use the
/// "assemblyComposition" object passed in to the completionHandler to
/// assemble the incremental segments into full tracks and export it to a
/// final output file. The completionHandler will also be called when there
/// is any irrecoverable error.
/// 6. The client is responsible for cleaning all files in the
/// directoryForTemporaryFiles after the incremental session is done and the
/// final output file is written.
/// 
/// AVAssetWritingPlanner is able to recognize when a plan-in-progress matching
/// the plan was already saved at directoryForTemporaryFiles, presumably by a
/// previous invocation of the client, and possibly aborted due to that client
/// being terminated abruptly, and will assist by resuming the plan at the first
/// step that wasn't previously completed.
API_AVAILABLE(macos(27.0), ios(27.0), tvos(27.0), visionos(27.0)) API_UNAVAILABLE(watchos)
NS_SWIFT_NONSENDABLE
@interface AVAssetWritingPlanner : NSObject

/// Creates an instance of AVAssetWritingPlanner given a unique file directory to host all incremental segment files and other intermediate files.
/// 
/// The directoryForTemporaryFiles must differ between export operations, but remain identical when resuming the same export operation. The client is responsible for ensuring that this NSURL can be re-synthesized exactly across multiple launches of the app and device reboots (if desired). For example, if there are multiple source assets that need to be exported concurrently, these should result in unique NSURLs so that the planner can correctly identify each one.
/// Another example is if the same source asset is being output with different compression configurations, they also should be uniquely identifiable so that they do not alias to the same output file.
/// Source assets, compression configs, and video composition settings should all be taken into account when generating the unique URL.
/// A resuming planner instance can only find the files from a previous planner instance if presented with the identical URL. All intermediate segment files and metadata files are stored in the specified directoryForTemporaryFiles.
/// This initializer throws NSInvalidArgumentException if directoryForTemporaryFiles does not exist, or it is not writable, or it contains a corrupted AVAssetWritingPlanner incremental state file.
/// 
/// - Parameter directoryForTemporaryFiles: The file directory to host all incremental segment files and other intermediate files for the current AVAssetWritingPlanner operation.
/// 
/// - Returns: An instance of AVAssetWritingPlanner.
- (instancetype)initWithDirectoryForTemporaryFiles:(NSURL *)directoryForTemporaryFiles NS_DESIGNATED_INITIALIZER NS_REFINED_FOR_SWIFT;

/// The current progress of the AVAssetWritingPlanner.
/// 
/// Returns an AVAssetWritingPlannerProgress object that can be queried for per-track and overall progress information.
@property (readonly) AVAssetWritingPlannerProgress *progress;

/// Returns segment boundary guidelines that help clients determine how to segment compression video tracks with best results.
/// 
/// The videoEncoderSpecification parameter here is the same encoder specification the client uses to compress the video track.
/// 
/// - Parameter videoCodecType: The output videoCodecType for the video track.
/// - Parameter videoEncoderSpecification: The video encoder specification includes options for choosing a specific video encoder. This is a dictionary containing kVTVideoEncoderSpecification_* keys specified in the VideoToolbox framework.
/// 
/// - Returns: An AVPlannedVideoSegmentBoundaryGuidelines.
+ (AVPlannedVideoSegmentBoundaryGuidelines)segmentBoundaryGuidelinesForVideoCodecType:(AVVideoCodecType)videoCodecType videoEncoderSpecification:(NSDictionary *)videoEncoderSpecification
	NS_REFINED_FOR_SWIFT;

/// Returns segment boundary recommendations for a given source video asset track.
/// 
/// This is a convenience method that can help clients to pick optimal segmentation boundaries for a given
/// source video AVAssetTrack based on the structure of the track and the minimumSegmentDuration and
/// minimumSegmentFrameCount values provided.
/// 
/// The client needs to ensure that the minimumSegmentDuration is greater than or equal to the segment
/// boundary guidelines for the codec type. The client should also ensure that minimumSegmentFrameCount
/// also exceeds the segment boundary guidelines.
/// 
/// The segments returned will satisfy both the minimumSegmentDuration and minimumSegmentFrameCount
/// requirements. The only exception is the very last segment, which may be shorter.
/// 
/// The returned array will ensure that segment boundaries occur on sample boundaries.
/// 
/// Clients can use these results to fill in the AVPlannedVideoSegmentConfiguration for this asset track,
/// if the output maintains the source timing. If the output timing differs from the source, then the
/// returned AVPlannedVideoSegmentConfiguration array's results need to be modified accordingly by the client.
/// 
/// This method throws NSInvalidArgumentException if minimumSegmentDuration is not numeric or is less than
/// or equal to zero, or if minimumSegmentFrameCount is less than or equal to 0.
/// 
/// - Parameter videoAssetTrack: The source video AVAssetTrack to be analyzed.
/// - Parameter minimumSegmentDuration: The client selected minimum duration for the segments.
/// - Parameter minimumSegmentFrameCount: The minimum number of source frames in a segment.
/// 
/// - Returns: Array of AVPlannedVideoSegmentConfiguration objects, each element specifying the configuration of a planned video segment, ordered in output PTS order
+ (NSArray <AVPlannedVideoSegmentConfiguration *> *)segmentBoundaryRecommendationsForVideoAVAssetTrack:(AVAssetTrack *)videoAssetTrack minimumSegmentDuration:(CMTime)minimumSegmentDuration minimumSegmentFrameCount:(NSInteger)minimumSegmentFrameCount
	NS_SWIFT_NAME(segmentBoundaryRecommendations(forVideoTrack:minimumSegmentDuration:minimumSegmentFrameCount:));

/// Adds an AVAssetTrackPlan to this AVAssetWritingPlanner, with a block to be called by the planner to generate each segment of the track.
/// 
/// This method throws NSInternalInconsistencyException if a trackPlan with the same assemblyTrackID already exists in the planner, or if called after executePlanWithCompletionHandler: has been invoked.
/// 
/// - Parameter trackPlan: The track plan contains information about the track and boundaries of all the segments.
/// - Parameter writingSegmentCallbackBlock: A block to be called by the AVAssetWritingPlanner on each incremental segment for this track to write the segment to an intermediate file, according to the specifications in the "segmentWriteRequest" object passed to the block.
- (void)planTrack:(AVAssetTrackPlan *)trackPlan withSegmentsGeneratedBy:(void (^ NS_SWIFT_SENDABLE)(AVPlannedSegmentWritingRequest * NS_SWIFT_SENDING segmentWriteRequest))writingSegmentCallbackBlock
NS_REFINED_FOR_SWIFT;

/// Starts the incremental segment writing.
/// 
/// The planner calls the writingSegmentCallbackBlock sequentially, starting with the first segment work, or at the next unfinished segment if resuming a previously suspended session.
/// The completionHandler is called upon failure or success. When called with success (error is nil), this means that all segments for all tracks have been completed. The assemblyComposition will be non-nil and can be used to put the incremental tracks back together. One way to accomplish this is by feeding the assemblyComposition through AVAssetExportSession with the pass-through preset.
/// The client is responsible for combining any other tracks (those that were not eligible for incremental writing), as well as establishing any track references between the incrementally written tracks and the other tracks in the final asset.
/// 
/// - Parameter completionHandler: Called when all the incremental segments on all tracks added to the planner have completed, or some error occurs.
-(void)executePlanWithCompletionHandler:
		(void (^ NS_SWIFT_SENDABLE)(AVComposition * _Nullable NS_SWIFT_SENDING assemblyComposition, NSError * _Nullable error))completionHandler
NS_REFINED_FOR_SWIFT;

/// Starts the incremental segment writing on a given dispatch queue
/// 
/// The planner calls the writingSegmentCallbackBlock sequentially, starting with the first segment work, or at the next unfinished segment if resuming a previously suspended export.
/// The completionHandler is called upon failure or success. When called with success (error is nil), this means that all segments for all tracks have been completed. The assemblyComposition will be non-nil and can be used to put the incremental tracks back together. One way to accomplish this is by feeding the assemblyComposition through AVAssetExportSession with the pass-through preset.
/// The client is responsible for combining any other tracks (those that were not eligible for incremental writing), as well as establishing any track references between the incrementally written tracks and the other tracks in the final asset.
/// 
/// - Parameter executionQueue: The dispatch queue on which the planner executes the plans. The segment writing callback blocks and the completion handler are called from this queue.
/// - Parameter completionHandler: Called when all the incremental segments on all tracks added to the planner have completed, or some error occurs.
-(void)executePlanOnQueue:(dispatch_queue_t)executionQueue
	withCompletionHandler:(void (^ NS_SWIFT_SENDABLE)(AVComposition * _Nullable NS_SWIFT_SENDING assemblyComposition, NSError * _Nullable error))completionHandler
NS_SWIFT_UNAVAILABLE("Use executePlan(completionHandler:) instead");

AV_INIT_UNAVAILABLE

@end // AVAssetWritingPlanner

/// AVAssetWritingPlannerProgress tracks the progress of incremental writing for each track in an AVAssetWritingPlanner session.
/// 
/// This class provides per-track progress information as a percentage of the total duration completed. Progress can be queried by assemblyTrackID.
API_AVAILABLE(macos(27.0), ios(27.0), tvos(27.0), visionos(27.0)) API_UNAVAILABLE(watchos)
NS_SWIFT_SENDABLE
@interface AVAssetWritingPlannerProgress : NSObject

/// Returns the progress for a specific track identified by its assemblyTrackID.
/// 
/// The progress is calculated as the ratio of completed duration to total duration for the track.
/// 
/// - Parameter assemblyTrackID: The track ID to query progress for.
/// 
/// - Returns: A float value between 0.0 and 1.0 representing the percentage of duration completed for the track. Returns 0.0 if the track ID is not found.
- (float)progressForTrack:(CMPersistentTrackID)assemblyTrackID
	NS_SWIFT_NAME(progress(forTrack:));

/// The overall progress across all tracks.
/// 
/// Returns a float value between 0.0 and 1.0 representing the overall progress. This is calculated as the average progress of all tracks weighted by their durations.
@property (readonly) float overallProgress;

@end // AVAssetWritingPlannerProgress

/// AVPlannedSegmentConfiguration describes the requirements for a planned segment in an incremental writing session executed by the AVAssetWritingPlanner. Subclasses of this type that are used from Swift must fulfill the requirements of a Sendable type.
API_AVAILABLE(macos(27.0), ios(27.0), tvos(27.0), visionos(27.0)) API_UNAVAILABLE(watchos)
@interface AVPlannedSegmentConfiguration : NSObject

/// Creates an instance of AVPlannedSegmentConfiguration specifying the duration of the planned segment.
/// 
/// The duration parameter must be numeric and greater than 0. Otherwise, the initializer throws NSInvalidArgumentException.
/// 
/// - Parameter duration: The total duration of this planned segment. If an empty edit is included, this duration may be larger than the sum of the durations of the samples in this planned segment.
/// 
/// - Returns: An instance of AVPlannedSegmentConfiguration, or nil if initialization fails.
- (instancetype)initWithDuration:(CMTime)duration NS_DESIGNATED_INITIALIZER;

/// The duration of this planned segment.
@property (readonly) CMTime duration;

AV_INIT_UNAVAILABLE

@end // AVPlannedSegmentConfiguration

/// AVPlannedVideoSegmentConfiguration describes the requirements for a planned video segment in an incremental writing session executed by the AVAssetWritingPlanner.
/// 
/// Use this class instead of the base class AVPlannedSegmentConfiguration if you are setting up AVAssetWriterInput to do video compression. AVAssetWritingPlanner will provide required video compression properties in its AVPlannedSegmentWritingRequest that are needed to prevent visual artifacts on segment boundaries.
API_AVAILABLE(macos(27.0), ios(27.0), tvos(27.0), visionos(27.0)) API_UNAVAILABLE(watchos)
@interface AVPlannedVideoSegmentConfiguration : AVPlannedSegmentConfiguration

/// Creates an instance of AVPlannedVideoSegmentConfiguration specifying the number of frames in and total duration of the segment.
/// 
/// For best results, frameCount and duration should be greater or equal to the minimumFrameCount and minimumDuration of AVPlannedVideoSegmentBoundaryGuidelines respectively.
/// This initializer throws NSInvalidArgumentException if frameCount is less than or equal to 0, or duration is not numeric, or duration is less than or equal to 0.
/// 
/// - Parameter frameCount: The number of frames in this planned video segment.
/// - Parameter duration: The duration of this planned video segment.
/// 
/// - Returns: An instance of AVPlannedVideoSegmentConfiguration.
- (instancetype)initWithNumberOfFrames:(NSInteger)frameCount duration:(CMTime)duration NS_DESIGNATED_INITIALIZER;

/// The number of frames in this planned video segment.
@property (readonly) NSInteger frameCount;

AV_INIT_UNAVAILABLE

@end // AVPlannedVideoSegmentConfiguration

/// AVAssetTrackPlan holds information about a track and how it should be segmented and executed in an incremental writing session.
/// 
/// Call AVAssetWritingPlanner's "planTrack:withSegmentsGeneratedBy:" method to add an AVAssetTrackPlan to the planner to include it in the incremental writing session.
API_AVAILABLE(macos(27.0), ios(27.0), tvos(27.0), visionos(27.0)) API_UNAVAILABLE(watchos)
@interface AVAssetTrackPlan : NSObject

/// This is the track ID of this track when it is included in the assemblyComposition the planner passes to the completion handler to assemble all planned segments of all tracks into a single AVComposition.
/// 
/// The assemblyTrackID serves the purpose as a unique identifier of the track in the incremental writing session. This does not necessarily match the trackID of the source asset.
/// The client is responsible for remembering the relationship between assemblyTrackID and the trackID in the source asset.
@property (readonly) CMPersistentTrackID assemblyTrackID;

/// The media type of this track.
@property (readonly) AVMediaType mediaType;

/// Array of AVPlannedSegmentConfigurations, each element specifying the configuration of a planned segment, ordered in output PTS order.
@property (readonly, copy) NSArray<AVPlannedSegmentConfiguration *> *segmentConfigurations;

/// Returns an instance of AVAssetTrackPlan
/// 
/// This initializer throws NSInvalidArgumentException if trackID is kCMPersistentTrackID_Invalid.
/// 
/// - Parameter mediaType: Media type of the track
/// - Parameter segmentConfigurations: Segment configurations of the track
/// - Parameter trackID: The trackID that identifies this track in the assemblyComposition the planner passes to the completion handler of the incremental writing session.
- (instancetype)initWithMediaType:(AVMediaType)mediaType segmentConfigurations:(NSArray<AVPlannedSegmentConfiguration *> *)segmentConfigurations assemblyTrackID:(CMPersistentTrackID)trackID NS_DESIGNATED_INITIALIZER;

AV_INIT_UNAVAILABLE

@end // AVAssetTrackPlan

/// AVAssetVideoTrackPlan holds information about a track and how it should be segmented and executed in an incremental writing session.
/// 
/// Call AVAssetWritingPlanner's "planTrack:withSegmentsGeneratedBy:" method to add an AVAssetTrackPlan to the planner's plan to include it in the incremental writing session.
/// Use this class instead of the base class AVAssetTrackPlan if you are setting up AVAssetWriter with video compression. This configuration hints to the planner that it
/// must coordinate segment boundaries transitions between segments. This is abstracted from the client via using either the resumableAssetWriterInputWithMediaType
/// or createResumableCompressionSessionWithAllocator helper functions within the AVPlannedVideoSegmentWritingRequest.
API_AVAILABLE(macos(27.0), ios(27.0), tvos(27.0), visionos(27.0)) API_UNAVAILABLE(watchos)
@interface AVAssetVideoTrackPlan : AVAssetTrackPlan

/// Video codec type of this track
@property (readonly) AVVideoCodecType videoCodecType;

/// Returns an instance of AVAssetVideoTrackPlan
/// 
/// This initializer throws NSInvalidArgumentException in the following cases.
/// 1. mediaType is not supported. Supported media types are AVMediaTypeVideo and AVMediaTypeAuxiliaryPicture
/// 2. The encoder specified by videoCodecType and encoderSpecification does not support video encoding in segments
/// 
/// - Parameter videoCodecType: Video codec type of the track
/// - Parameter encoderSpecification: The encoder specification the client will use to write planned segments of this track
/// - Parameter mediaType: Media type of the track. Only AVMediaTypeVideo and AVMediaTypeAuxiliaryPicture are supported.
/// - Parameter segmentConfigurations: Segment configurations of the track
/// - Parameter trackID: The trackID that identifies this track in the assemblyComposition the planner passes to the completion handler of the incremental writing session.
- (instancetype)initWithVideoCodecType:(AVVideoCodecType)videoCodecType encoderSpecification:(nullable NSDictionary *)encoderSpecification mediaType:(AVMediaType)mediaType segmentConfigurations:(NSArray<AVPlannedSegmentConfiguration *> *)segmentConfigurations assemblyTrackID:(CMPersistentTrackID)trackID NS_REFINED_FOR_SWIFT NS_DESIGNATED_INITIALIZER;

AV_INIT_UNAVAILABLE

@end // AVAssetVideoTrackPlan

/// AVPlannedSegmentWritingRequest encompasses a request from the AVAssetWritingPlanner to the client code to write one incremental track segment.
/// 
/// The client should respond to this request by writing the specified time range of data to a movie file at the specified segmentFileOutputURL, with start PTS zero. The client's writing work may be completed asynchronously. If it completes successfully, clients must call the `-finish` or `-finishWithClientState` method on the request object. If writing the segment fails, clients must call the `-finishWithError:` method on the request object. If segment writing needs to be stopped before reaching the end of the segment, clients must call `-cancel`.
API_AVAILABLE(macos(27.0), ios(27.0), tvos(27.0), visionos(27.0)) API_UNAVAILABLE(watchos)
@interface AVPlannedSegmentWritingRequest : NSObject

/// The URL of the file where this incremental segment should be written to.
/// 
/// AVAssetWritingPlanner will request each incremental segment to be written to a different file. If the file already exists from a previous session, the client should delete it to allow the subsequent asset writer session to succeed.
@property (readonly) NSURL *segmentFileOutputURL;

/// The PTS range for this segment.
/// 
/// The client is responsible for delivering the appropriate sample corresponding to timeRange.start if we are resuming a previous session that has already made incremental progress for this track.
@property (readonly) CMTimeRange timeRange;

/// The trackID identifies which track should be written to this segment file. This is the same track ID in the AVAssetTrackPlan object. This is also the trackID the AVAssetWritingPlanner uses to build the assembled AVComposition before it calls the completion handler.
@property (readonly) CMPersistentTrackID assemblyTrackID;

/// The client state persisted from the previous segment, if any. Specifically, this is the NSData provided to the previous segment's finishWithClientState: method. The client is responsible to restore its client state before writing the current segment. For example, clients such as compositors with a temporal element may need some processing history of previous samples in order to generate an output sample at time N. This will be nil for algorithms that are stateless.
@property (readonly, nullable) NSData *clientStateToRestore;

/// The current progress for the track identified by assemblyTrackID.
/// 
/// Returns a float value between 0.0 and 1.0 representing the percentage of duration completed for this track. This value is updated as segments are completed.
@property (readonly) float progress;

/// Clients must call this method after all writing activities for the intermediate segment file have successfully completed.
/// 
/// This method throws NSGenericException if finish, finishWithClientState:, finishWithError:, or cancel has already been called on this request.
- (void)finish NS_REFINED_FOR_SWIFT;

/// Clients must call this method after all writing activities for the intermediate segment file have successfully completed. If called with nil, this is equivalent to calling finish.
/// 
/// This method throws NSGenericException if finish, finishWithClientState:, finishWithError:, or cancel has already been called on this request.
- (void)finishWithClientState:(nullable NSData *)segmentEndingClientState NS_REFINED_FOR_SWIFT;

/// Clients must call this method if a non-recoverable error occurs while generating the segment file. The completionHandler of AVAssetWritingPlanner will be called with an error whose code is AVErrorAssetWritingPlannerClientWritingError, and the error provided here will be available in the NSUnderlyingErrorKey of the userInfo dictionary. If called with nil, this is equivalent to calling finish.
/// 
/// This method throws NSGenericException if finish, finishWithClientState:, finishWithError:, or cancel has already been called on this request.
- (void)finishWithError:(nullable NSError *)error NS_REFINED_FOR_SWIFT;

/// Clients should call this if the current segment is to be cancelled, but the export is still expected to be resumed at a later time. For example, this could happen if the export is running in the background and the expiration handler is called due to changes in system conditions.
/// 
/// This method throws NSGenericException if finish, finishWithClientState:, finishWithError:, or cancel has already been called on this request.
- (void)cancel NS_REFINED_FOR_SWIFT;

AV_INIT_UNAVAILABLE

@end // AVPlannedSegmentWritingRequest

/// AVPlannedVideoSegmentWritingRequest encompasses a request from the AVAssetWritingPlanner to the client code to write one incremental video track segment with compression.
/// 
/// The client should respond to this request by writing the specified time range of data to a movie file at the specified segmentFileOutputURL, with start PTS zero. The client's writing work may be completed asynchronously. If it completes successfully, it must call the `-finish` method on the request object. If writing the segment fails, it must call the `-finishWithError:` method on the request object.
API_AVAILABLE(macos(27.0), ios(27.0), tvos(27.0), visionos(27.0)) API_UNAVAILABLE(watchos)
@interface AVPlannedVideoSegmentWritingRequest : AVPlannedSegmentWritingRequest

/// The number of frames in this planned video segment. This is provided for convenience, and is the same value that was configured for the segment in AVPlannedVideoSegmentConfiguration.
@property (readonly) NSInteger frameCount;

/// Helper function that returns a minimally configured AVAssetWriterInput object for writing the current segment. The final video encoder state from the previous segment will be restored before writing starts.
/// 
/// Clients using AVAssetWriterInput with video compression must use this method to create the writer input for writing the segment. The planner initializes the writer input in such a way that when writing starts, the video encoder's state is restored to the final state of the last segment.
/// The client should perform additional configurations on the returned writer input as needed, but must apply the same configurations for each segment of the track.
/// 
/// Client cannot call this method more than once on a writing request object.
/// For the same segment writing request, this method and the "createResumableCompressionSessionWithAllocator" method are mutually exclusive. The client can call either one of the two, but not both.
/// This method fails (returns nil) with error if the outputSettings or sourceFormatHint differs from the previous segment.
/// 
/// The writing request retains the writer input but does not mutate it after this method is returned.
/// 
/// - Parameter mediaType: The type of media that an input accepts.
/// - Parameter outputSettings: The settings to use for configuring the AVAssetWriterInput object to be returned. Create an output settings dictionary manually, or use AVOutputSettingsAssistant to create preset-based settings.
/// - Parameter sourceFormatHint: A hint about the format of the media data to append. The input uses the source format hint to fill in missing output settings. If you specify a hint, you only need to specify AVFormatIDKey for the audio output settings, and AVVideoCodecKey is the only required key for video output settings. The system raises an error if the format description isn't valid for the indicated media type.
/// - Parameter errorOut: A pointer where a NSError object may be returned.
/// - Returns: A new writer input. Nil if a writer input cannot be created.
- (nullable AVAssetWriterInput *)resumableAssetWriterInputWithMediaType:(AVMediaType)mediaType outputSettings:(nullable NSDictionary<NSString *, id>*)outputSettings sourceFormatHint:(nullable CMFormatDescriptionRef)sourceFormatHint returningError:(NSError * _Nullable * _Nullable)errorOut
NS_REFINED_FOR_SWIFT;

#if AVF_VTCOMPRESSIONSESSION_AVAILABLE

/// Helper function to create a VTCompressionSession that restores the video encoder state persisted at the end of the previous segment.
/// 
/// Clients using VTCompressionSession directly to produce encoded video samples for writing the segment must use this method to create the session.
/// The client should perform additional configurations on the returned compression session, but must apply the same configurations for each segment of the track.
/// 
/// Client cannot call this method more than once on a writing request object.
/// For the same segment writing request, this method and the resumableAssetWriterInputWithMediaType:outputSettings:sourceFormatHint:returningError: method are mutually exclusive. The client can call either one of the two, but not both.
/// This method fails (returns nil) with error if the parameters differ from the previous segment.
/// 
/// The client should release the session after use.
/// The writing request retains the compression session but does not mutate the session after this method is returned.
/// 
/// - Parameter allocator: An allocator for the session. Pass NULL to use the default allocator.
/// - Parameter width: The pixel width of video frames.
/// - Parameter height: The pixel height of video frames.
/// - Parameter codecType: The codec type.
/// - Parameter encoderSpecification: A dictionary describing the characteristics of a video encoder to use. Pass NULL to let the system choose an encoder. If the client provides a specification, it should omit the following keys: kVTCompressionPropertyKey_SourceFrameCount, kVTCompressionPropertyKey_MoreFramesBeforeStart, and kVTCompressionPropertyKey_MoreFramesAfterEnd, since such keys will be overwritten by the underlying implementation.
/// - Parameter sourceImageBufferAttributes: Required attributes for source pixel buffers, used when creating a pixel buffer pool for source frames. If you don't want the system to create one for you, pass NULL. Using pixel buffers not allocated by the system increases the chance that you'll have to copy image data.
/// - Parameter compressedDataAllocator: An allocator for the compressed data. Pass NULL to use the default allocator. In macOS 10.12 and later, using a compressedDataAllocator may trigger an extra buffer copy.
/// - Parameter outputCallback: The callback to invoke with compressed frames. The system may call this function asynchronously, on a different thread from the one that calls VTCompressionSessionEncodeFrame. Pass NULL only if you'll be calling VTCompressionSessionEncodeFrameWithOutputHandler for encoding frames.
/// - Parameter outputCallbackRefCon: Client-defined reference value for the output callback.
/// - Parameter errorOut: A pointer where a NSError object may be returned.
- (nullable VTCompressionSessionRef)createResumableCompressionSessionWithAllocator:(nullable CFAllocatorRef)allocator
																			 width:(int32_t)width
																			height:(int32_t)height
																		 codecType:(CMVideoCodecType)codecType
																encoderSpecification:(nullable NSDictionary *)encoderSpecification
													   sourceImageBufferAttributes:(nullable NSDictionary *)sourceImageBufferAttributes
														   compressedDataAllocator:(nullable CFAllocatorRef)compressedDataAllocator
																	outputCallback:(nullable VTCompressionOutputCallback)outputCallback
																outputCallbackRefCon:(nullable void *)outputCallbackRefCon
																	returningError:(NSError * _Nullable * _Nullable)errorOut
CF_RETURNS_RETAINED
NS_REFINED_FOR_SWIFT;
#endif // AVF_VTCOMPRESSIONSESSION_AVAILABLE

@end // AVPlannedVideoSegmentWritingRequest

NS_ASSUME_NONNULL_END

#else
#import <AVFCore/AVAssetWritingPlanner.h>
#endif
