#if !__has_include(<AVFCore/AVSampleBufferVideoRenderer.h>)
/*
	File:  AVSampleBufferVideoRenderer.h

	Framework:  AVFoundation
 
	Copyright 2023 Apple Inc. All rights reserved.

*/


#import <AVFoundation/AVBase.h>
#import <AVFoundation/AVQueuedSampleBufferRendering.h>

@class AVVideoPerformanceMetrics;

NS_ASSUME_NONNULL_BEGIN

AVF_EXPORT NSNotificationName const AVSampleBufferVideoRendererDidFailToDecodeNotification // decode failed, see NSError in notification payload
#if defined(__swift__)
API_DEPRECATED("Use the result of AVSampleBufferVideoRenderer.Receiver enqueue(_:) and enqueueImmediately(_:) for .successWithDecodeFailure instead", macos(14.0, 27.0), ios(17.0, 27.0), tvos(17.0, 27.0), visionos(1.0, 27.0))
API_UNAVAILABLE(watchos)
#else
API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0), visionos(1.0)) API_UNAVAILABLE(watchos)
#endif
;

AVF_EXPORT NSString *const AVSampleBufferVideoRendererDidFailToDecodeNotificationErrorKey // NSError
#if defined(__swift__)
API_DEPRECATED("Use the result of AVSampleBufferVideoRenderer.Receiver enqueue(_:) and enqueueImmediately(_:) for .successWithDecodeFailure instead", macos(14.0, 27.0), ios(17.0, 27.0), tvos(17.0, 27.0), visionos(1.0, 27.0))
API_UNAVAILABLE(watchos)
#else
API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0), visionos(1.0)) API_UNAVAILABLE(watchos)
#endif
;

AVF_EXPORT NSNotificationName const AVSampleBufferVideoRendererRequiresFlushToResumeDecodingDidChangeNotification // see requiresFlushToResumeDecoding property
#if defined(__swift__)
API_DEPRECATED("Use the result of AVSampleBufferVideoRenderer.Receiver enqueue(_:) and enqueueImmediately(_:) for .requiresFlushToResumeDecoding instead", macos(14.0, 27.0), ios(17.0, 27.0), tvos(17.0, 27.0), visionos(1.0, 27.0))
API_UNAVAILABLE(watchos)
#else
API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0), visionos(1.0)) API_UNAVAILABLE(watchos)
#endif
;
AVF_EXPORT NSString *const AVSampleBufferVideoRendererRequiresFlushToResumeDecodingDidChangeNotificationRequiresFlushKey // NSNumber(BOOL)
#if defined(__swift__)
API_DEPRECATED("Use the result of AVSampleBufferVideoRenderer.Receiver enqueue(_:) and enqueueImmediately(_:) for .requiresFlushToResumeDecoding instead", macos(27.0, 27.0), ios(27.0, 27.0), tvos(27.0, 27.0), visionos(27.0, 27.0))
API_UNAVAILABLE(watchos)
#else
API_AVAILABLE(macos(27.0), ios(27.0), tvos(27.0), visionos(27.0)) API_UNAVAILABLE(watchos)
#endif
;

/// AVSampleBufferVideoRenderer provides a mechanism to enqueue sample buffers for rendering.
NS_SWIFT_NONSENDABLE
API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0), visionos(1.0)) API_UNAVAILABLE(watchos)
@interface AVSampleBufferVideoRenderer : NSObject <AVQueuedSampleBufferRendering>

/// The ability of the video renderer to be used for enqueueing sample buffers.
/// 
/// The value of this property is an AVQueuedSampleBufferRenderingStatus that indicates whether the receiver can be used for enqueueing and rendering sample buffers. When the value of this property is AVQueuedSampleBufferRenderingStatusFailed, clients can check the value of the error property to determine the failure. To resume rendering sample buffers using the video renderer after a failure, clients must first reset the status to AVQueuedSampleBufferRenderingStatusUnknown. This can be achieved by invoking -flush on the video renderer.
/// This property is key value observable.
@property (readonly) AVQueuedSampleBufferRenderingStatus status
#if defined(__swift__)
API_DEPRECATED("Use EnqueueResult from enqueue(_:) and enqueueImmediately(_:), and RenderingEvent from renderingEventsAfterFinishedEnqueuing instead", macos(14.0, 27.0), ios(17.0, 27.0), tvos(17.0, 27.0), visionos(1.0, 27.0))
API_UNAVAILABLE(watchos)
#else
API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0), visionos(1.0)) API_UNAVAILABLE(watchos)
#endif
;

/// If the video renderer's status is AVQueuedSampleBufferRenderingStatusFailed, this describes the error that caused the failure.
/// 
/// The value of this property is an NSError that describes what caused the video renderer to no longer be able to enqueue sample buffers. If the status is not AVQueuedSampleBufferRenderingStatusFailed, the value of this property is nil.
@property (readonly, nullable) NSError *error
#if defined(__swift__)
API_DEPRECATED("Use EnqueueResult from enqueue(_:) and enqueueImmediately(_:), and RenderingEvent from renderingEventsAfterFinishedEnqueuing instead", macos(14.0, 27.0), ios(17.0, 27.0), tvos(17.0, 27.0), visionos(1.0, 27.0))
API_UNAVAILABLE(watchos)
#else
API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0), visionos(1.0)) API_UNAVAILABLE(watchos)
#endif
;

/// Indicates that the receiver is in a state where it requires a call to -flush to continue decoding frames.
/// 
/// When the application enters a state where use of video decoder resources is not permissible, the value of this property changes to YES along with the video renderer's status changing to AVQueuedSampleBufferRenderingStatusFailed.
/// To resume rendering sample buffers using the video renderer after this property's value is YES, clients must first reset the video renderer by calling flush or flushWithRemovalOfDisplayedImage:completionHandler:.
/// Clients can track changes to this property via AVSampleBufferVideoRendererRequiresFlushToResumeDecodingDidChangeNotification.
/// This property is not key value observable.
@property (readonly) BOOL requiresFlushToResumeDecoding
#if defined(__swift__)
API_DEPRECATED("Use the result of AVSampleBufferVideoRenderer.Receiver enqueue(_:) and enqueueImmediately(_:) for .requiresFlushToResumeDecoding instead", macos(14.0, 27.0), ios(17.0, 27.0), tvos(17.0, 27.0), visionos(1.0, 27.0))
API_UNAVAILABLE(watchos)
#else
API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0), visionos(1.0)) API_UNAVAILABLE(watchos)
#endif
;

/// Instructs the video renderer to discard pending enqueued sample buffers and call the provided block when complete.
/// 
/// A flush resets decoder state. The next frame passed to enqueueSampleBuffer: should be an IDR frame (also known as a key frame or sync sample).
/// 
/// - Parameter removeDisplayedImage: Set YES to remove any currently displayed image, NO to preserve any current image.
/// - Parameter handler: The handler to invoke when flush operation is complete. May be nil.
- (void)flushWithRemovalOfDisplayedImage:(BOOL)removeDisplayedImage completionHandler:(nullable void (^ NS_SWIFT_SENDABLE)(void))handler
#if defined(__swift__)
API_DEPRECATED("Attach renderer to a render synchronizer with sampleBufferReceiver(adding:) and use the receiver's flush(removingDisplayedImage:) method instead", macos(14.0, 27.0), ios(17.0, 27.0), tvos(17.0, 27.0), visionos(1.0, 27.0))
API_UNAVAILABLE(watchos)
#else
API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0), visionos(1.0)) API_UNAVAILABLE(watchos)
#endif
;

/// Sends a sample buffer in order to render its contents.
///
/// Video-specific notes:
///
/// If sampleBuffer has the kCMSampleAttachmentKey_DoNotDisplay attachment set to kCFBooleanTrue, the frame will be decoded but not displayed. Otherwise, if sampleBuffer has the kCMSampleAttachmentKey_DisplayImmediately attachment set to kCFBooleanTrue, the decoded image will be displayed as soon as possible, replacing all previously enqueued images regardless of their timestamps. Otherwise, the decoded image will be displayed at sampleBuffer's output presentation timestamp, as interpreted by the timebase.
///
/// To schedule the removal of previous images at a specific timestamp, enqueue a marker sample buffer containing no samples, with the kCMSampleBufferAttachmentKey_EmptyMedia attachment set to kCFBooleanTrue.
///
/// IMPORTANT NOTE: attachments with the kCMSampleAttachmentKey_ prefix must be set via CMSampleBufferGetSampleAttachmentsArray and CFDictionarySetValue. Attachments with the kCMSampleBufferAttachmentKey_ prefix must be set via CMSetAttachment.
///
/// The combination of either a non-NULL controlTimebase or an AVSampleBufferRenderSynchronizer with the use of kCMSampleAttachmentKey_DisplayImmediately as an attachment to the CMSampleBuffers that are enqueued for display is not recommended.
- (void)enqueueSampleBuffer:(CMSampleBufferRef)sampleBuffer
#if defined(__swift__)
API_DEPRECATED("Attach renderer to a render synchronizer with sampleBufferReceiver(adding:) and use the receiver's enqueue(_:) async or enqueueImmediately(_:) methods instead", macos(10.13, 27.0), ios(11.0, 27.0), tvos(11.0, 27.0), visionos(1.0, 27.0))
API_DEPRECATED("Attach renderer to a render synchronizer with sampleBufferReceiver(adding:) and use the receiver's enqueue(_:) async or enqueueImmediately(_:) methods instead", watchos(4.0, 27.0))
#else
API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0), watchos(4.0), visionos(1.0))
#endif
;

/// Instructs the receiver to discard pending enqueued sample buffers.
///
/// Additional sample buffers can be appended after -flush.
///
/// Video-specific notes:
///
/// It is not possible to determine which sample buffers have been decoded, so the next frame passed to enqueueSampleBuffer: should be an IDR frame (also known as a key frame or sync sample).
- (void)flush
#if defined(__swift__)
API_DEPRECATED("Attach renderer to a render synchronizer with sampleBufferReceiver(adding:) and use the receiver's flush() method instead", macos(10.13, 27.0), ios(11.0, 27.0), tvos(11.0, 27.0), visionos(1.0, 27.0))
API_DEPRECATED("Attach renderer to a render synchronizer with sampleBufferReceiver(adding:) and use the receiver's flush() method instead", watchos(4.0, 27.0))
#else
API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0), watchos(4.0), visionos(1.0))
#endif
;

/// Indicates the readiness of the receiver to accept more sample buffers.
///
/// An object conforming to AVQueuedSampleBufferRendering keeps track of the occupancy levels of its internal queues for the benefit of clients that enqueue sample buffers from non-real-time sources -- i.e., clients that can supply sample buffers faster than they are consumed, and so need to decide when to hold back.
///
/// Clients enqueueing sample buffers from non-real-time sources may hold off from generating or obtaining more sample buffers to enqueue when the value of readyForMoreMediaData is NO.
///
/// It is safe to call enqueueSampleBuffer: when readyForMoreMediaData is NO, but it is a bad idea to enqueue sample buffers without bound.
///
/// To help with control of the non-real-time supply of sample buffers, such clients can use -requestMediaDataWhenReadyOnQueue:usingBlock in order to specify a block that the receiver should invoke whenever it's ready for sample buffers to be appended.
///
/// The value of readyForMoreMediaData will often change from NO to YES asynchronously, as previously supplied sample buffers are decoded and rendered.
///
/// This property is not key value observable.
@property (readonly, getter=isReadyForMoreMediaData) BOOL readyForMoreMediaData
#if defined(__swift__)
API_DEPRECATED("Attach renderer to a render synchronizer with sampleBufferReceiver(adding:) and use the receiver's enqueue(_:) async method on its own detached Task to suspend until it is ready for more media data instead", macos(10.13, 27.0), ios(11.0, 27.0), tvos(11.0, 27.0), watchos(4.0, 27.0), visionos(1.0, 27.0))
#else
API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0), watchos(4.0), visionos(1.0))
#endif
;

/// Instructs the target to invoke a client-supplied block repeatedly, at its convenience, in order to gather sample buffers for playback.
///
/// The block should enqueue sample buffers to the receiver either until the receiver's readyForMoreMediaData property becomes NO or until there is no more data to supply. When the receiver has decoded enough of the media data it has received that it becomes ready for more media data again, it will invoke the block again in order to obtain more.
///
/// If this method is called multiple times, only the last call is effective. Call stopRequestingMediaData to cancel this request.
///
/// Each call to requestMediaDataWhenReadyOnQueue:usingBlock: should be paired with a corresponding call to stopRequestingMediaData:. Releasing the AVQueuedSampleBufferRendering object without a call to stopRequestingMediaData will result in undefined behavior.
- (void)requestMediaDataWhenReadyOnQueue:(dispatch_queue_t)queue usingBlock:(void (^ NS_SWIFT_SENDABLE)(void))block
#if defined(__swift__)
API_DEPRECATED("Attach renderer to a render synchronizer with sampleBufferReceiver(adding:) and use the receiver to enqueue samples on a detached Task instead", macos(10.13, 27.0), ios(11.0, 27.0), tvos(11.0, 27.0), visionos(1.0, 27.0))
API_DEPRECATED("Attach renderer to a render synchronizer with sampleBufferReceiver(adding:) and use the receiver to enqueue samples on a detached Task instead", watchos(4.0, 27.0))
#else
API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0), watchos(4.0), visionos(1.0))
#endif
;

/// Cancels any current requestMediaDataWhenReadyOnQueue:usingBlock: call.
///
/// This method may be called from outside the block or from within the block.
- (void)stopRequestingMediaData
#if defined(__swift__)
API_DEPRECATED("Cancel the receiver's Task instead", macos(10.13, 27.0), ios(11.0, 27.0), tvos(11.0, 27.0), visionos(1.0, 27.0))
API_DEPRECATED("Cancel the receiver's Task instead", watchos(4.0, 27.0))
#else
API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0), watchos(4.0), visionos(1.0))
#endif
;

/// Indicates whether the enqueued media data meets the renderer's preroll level.
///
/// Clients should fetch the value of this property to learn if the renderer has had enough media data enqueued to start playback reliably. Starting playback when this property is NO may prevent smooth playback following an immediate start.
@property (nonatomic, readonly) BOOL hasSufficientMediaDataForReliablePlaybackStart
#if defined(__swift__)
API_DEPRECATED("For smooth playback, attach the renderer to a render synchronizer and set the synchronizer's delaysRateChangeUntilHasSufficientMediaData property to true instead", macos(11.3, 27.0), ios(14.5, 27.0), tvos(14.5, 27.0), visionos(1.0, 27.0))
API_DEPRECATED("For smooth playback, attach the renderer to a render synchronizer and set the synchronizer's delaysRateChangeUntilHasSufficientMediaData property to true instead", watchos(7.4, 27.0))
#else
API_AVAILABLE(macos(11.3), ios(14.5), tvos(14.5), watchos(7.4), visionos(1.0))
#endif
;

@end

API_AVAILABLE(macos(14.4), ios(17.4), tvos(17.4), visionos(1.1)) API_UNAVAILABLE(watchos)
@interface AVSampleBufferVideoRenderer (AVSampleBufferVideoRendererPixelBufferOutput)

/// Returns a retained reference to the pixel buffer currently displayed in the AVSampleBufferVideoRenderer's target. This will return NULL if the displayed pixel buffer is protected, no image is currently being displayed, or if the image is unavailable.
/// 
/// This will return NULL if the rate is non-zero. Clients must release the pixel buffer after use.
/// 
/// Do not write to the returned CVPixelBuffer's attachments or pixel data.
- (nullable CVPixelBufferRef)copyDisplayedPixelBuffer CF_RETURNS_RETAINED API_AVAILABLE(macos(14.4), ios(17.4), tvos(17.4), visionos(1.1)) API_UNAVAILABLE(watchos);

@end

API_AVAILABLE(macos(14.4), ios(17.4), tvos(17.4), visionos(1.1)) API_UNAVAILABLE(watchos)
@interface AVSampleBufferVideoRenderer (AVSampleBufferVideoRendererPowerOptimization)

/// Promises, for the purpose of enabling power optimizations, that future sample buffers will have PTS values no less than a specified lower-bound PTS.
/// 
/// Only applicable for forward playback.
/// Sending this message and later calling -enqueueSampleBuffer: with a buffer with a lower PTS has the potential to lead to dropping that later buffer.
/// For best results, call -expectMinimumUpcomingSampleBufferPresentationTime: regularly, in between calls to -enqueueSampleBuffer:, to advance the lower-bound PTS.
/// Messaging -flush resets such expectations.
/// (For example, it's OK to make this expectation, then in response to a seek back, flush and then enqueue buffers with lower PTS values.)
/// 
/// - Parameter minimumUpcomingPresentationTime: A lower bound on PTS values for buffers that will be passed to -enqueueSampleBuffer: in the future.
- (void)expectMinimumUpcomingSampleBufferPresentationTime:(CMTime)minimumUpcomingPresentationTime NS_REFINED_FOR_SWIFT API_AVAILABLE(macos(14.4), ios(17.4), tvos(17.4), visionos(1.1)) API_UNAVAILABLE(watchos);

/// Promises, for the purpose of enabling power optimizations, that future sample buffers will have monotonically increasing PTS values.
/// 
/// Only applicable for forward playback.
/// Sending this message and later calling -enqueueSampleBuffer: with a buffer with a lower PTS than any previously enqueued PTS has the potential to lead to dropped buffers.
/// Messaging -flush resets such expectations.
- (void)expectMonotonicallyIncreasingUpcomingSampleBufferPresentationTimes NS_REFINED_FOR_SWIFT API_AVAILABLE(macos(14.4), ios(17.4), tvos(17.4), visionos(1.1)) API_UNAVAILABLE(watchos);

/// Resets previously-promised expectations about upcoming sample buffer PTSs.
/// 
/// This undoes the state set by messaging -expectMinimumUpcomingSampleBufferPresentationTime: or -expectMonotonicallyIncreasingUpcomingSampleBufferPresentationTimes.
/// If you didn't use either of those, you don't have to use this.
- (void)resetUpcomingSampleBufferPresentationTimeExpectations NS_REFINED_FOR_SWIFT API_AVAILABLE(macos(14.4), ios(17.4), tvos(17.4), visionos(1.1)) API_UNAVAILABLE(watchos);

/// Recommended pixel buffer attributes for optimal performance when using CMSampleBuffers containing CVPixelBuffers.
/// 
/// The returned dictionary does not contain all of the attributes needed for creating pixel buffers.
/// Use ``CVPixelBufferCreateResolvedAttributesDictionary()`` to reconcile these attributes with the pixel buffer creation attributes.
@property (readonly, nonnull) NSDictionary<NSString*, NS_SWIFT_SENDABLE id> *recommendedPixelBufferAttributes NS_REFINED_FOR_SWIFT API_AVAILABLE(macos(26.0), ios(26.0), tvos(26.0), visionos(26.0)) API_UNAVAILABLE(watchos);

@end

API_AVAILABLE(macos(14.4), ios(17.4), tvos(17.4), visionos(1.1)) API_UNAVAILABLE(watchos)
@interface AVSampleBufferVideoRenderer (AVSampleBufferVideoRendererVideoPerformanceMetrics)

/// Gathers a snapshot of the video performance metrics and calls the completion handler with the results.
/// 
/// If there are no performance metrics available, the completion handler will be called with nil videoPerformanceMetrics.
/// 
/// - Parameter completionHandler: The handler to invoke with the video performance metrics.
- (void)loadVideoPerformanceMetricsWithCompletionHandler:(void (^ NS_SWIFT_SENDABLE)(AVVideoPerformanceMetrics * _Nullable_result videoPerformanceMetrics))completionHandler NS_SWIFT_ASYNC_NAME(getter:videoPerformanceMetrics()) API_AVAILABLE(macos(14.4), ios(17.4), tvos(17.4), visionos(1.1)) API_UNAVAILABLE(watchos);

@end

NS_ASSUME_NONNULL_END

#else
#import <AVFCore/AVSampleBufferVideoRenderer.h>
#endif
