#if !__has_include(<AVFCore/AVSampleBufferAudioRenderer.h>)
/*
	File:  AVSampleBufferAudioRenderer.h

	Framework:  AVFoundation
 
	Copyright 2016-2021 Apple Inc. All rights reserved.

*/

#import <AVFoundation/AVQueuedSampleBufferRendering.h>
#import <AVFoundation/AVAudioProcessingSettings.h>

NS_ASSUME_NONNULL_BEGIN

@class AVSampleBufferAudioRendererInternal;

/// AVSampleBufferAudioRenderer can decompress and play compressed or uncompressed audio.
/// 
/// An instance of AVSampleBufferAudioRenderer must be added to an AVSampleBufferRenderSynchronizer before the first sample buffer is enqueued.
NS_SWIFT_NONSENDABLE
API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0), watchos(4.0), visionos(1.0))
@interface AVSampleBufferAudioRenderer : NSObject <AVQueuedSampleBufferRendering>
{
@private
	AVSampleBufferAudioRendererInternal *_audioRendererInternal;
}

/// Indicates the status of the audio renderer.
/// 
/// A renderer begins with status AVQueuedSampleBufferRenderingStatusUnknown.
/// 
/// As sample buffers are enqueued for rendering using -enqueueSampleBuffer:, the renderer will transition to either AVQueuedSampleBufferRenderingStatusRendering or AVQueuedSampleBufferRenderingStatusFailed.
/// 
/// If the status is AVQueuedSampleBufferRenderingStatusFailed, check the value of the renderer's error property for information on the error encountered. This is terminal status from which recovery is not always possible.
/// 
/// This property is key value observable.
@property (nonatomic, readonly) AVQueuedSampleBufferRenderingStatus status
#if defined(__swift__)
API_DEPRECATED("Use EnqueueResult from enqueue(_:) and enqueueImmediately(_:), and RenderingEvent from renderingEventsAfterFinishedEnqueuing instead", macos(10.13, 27.0), ios(11.0, 27.0), tvos(11.0, 27.0), watchos(4.0, 27.0), visionos(1.0, 27.0))
#else
API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0), watchos(4.0), visionos(1.0))
#endif
;

/// If the renderer's status is AVQueuedSampleBufferRenderingStatusFailed, this describes the error that caused the failure.
/// 
/// The value of this property is an NSError that describes what caused the renderer to no longer be able to render sample buffers. The value of this property is nil unless the value of status is AVQueuedSampleBufferRenderingStatusFailed.
@property (nonatomic, readonly, nullable) NSError *error
#if defined(__swift__)
API_DEPRECATED("Use EnqueueResult from enqueue(_:) and enqueueImmediately(_:), and RenderingEvent from renderingEventsAfterFinishedEnqueuing instead", macos(10.13, 27.0), ios(11.0, 27.0), tvos(11.0, 27.0), watchos(4.0, 27.0), visionos(1.0, 27.0))
#else
API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0), watchos(4.0), visionos(1.0))
#endif
;


/// Specifies the unique ID of the Core Audio output device used to play audio.
/// 
/// By default, the value of this property is nil, indicating that the default audio output device is used. Otherwise the value of this property is an NSString containing the unique ID of the Core Audio output device to be used for audio output.
/// 
/// Core Audio's kAudioDevicePropertyDeviceUID is a suitable source of audio output device unique IDs.
/// 
/// Modifying this property while the timebase's rate is not 0.0 may cause the rate to briefly change to 0.0.
/// 
/// On macOS, the audio device clock may be used as the AVSampleBufferRenderSynchronizer's and all attached AVQueuedSampleBufferRendering's timebase's clocks. If the audioOutputDeviceUniqueID is modified, the clocks of all these timebases may also change.
/// 
/// If multiple AVSampleBufferAudioRenderers with different values for audioOutputDeviceUniqueID are attached to the same AVSampleBufferRenderSynchronizer, audio may not stay in sync during playback. To avoid this, ensure that all synchronized AVSampleBufferAudioRenderers are using the same audio output device.
@property (nonatomic, copy, nullable) NSString *audioOutputDeviceUniqueID API_AVAILABLE(macos(10.13)) API_UNAVAILABLE(ios, tvos, watchos, visionos);

/// Indicates the processing algorithm used to manage audio pitch at varying rates.
/// 
/// Constants for various time pitch algorithms, e.g. AVAudioTimePitchSpectral, are defined in AVAudioProcessingSettings.h.
/// 
/// The default value for applications linked on or after iOS 15.0 or macOS 12.0 is AVAudioTimePitchAlgorithmTimeDomain. For iOS versions prior to 15.0 the default value is AVAudioTimePitchAlgorithmLowQualityZeroLatency.
/// For macOS versions prior to 12.0 the default value is AVAudioTimePitchAlgorithmSpectral.
/// 
/// If the timebase's rate is not supported by the audioTimePitchAlgorithm, audio will be muted.
/// 
/// Modifying this property while the timebase's rate is not 0.0 may cause the rate to briefly change to 0.0.
@property (nonatomic, copy) AVAudioTimePitchAlgorithm audioTimePitchAlgorithm;

/// Indicates the source audio channel layouts allowed by the receiver for spatialization.
/// 
/// Spatialization uses psychoacoustic methods to create a more immersive audio rendering when the content is played on specialized headphones and speaker arrangements. When an AVSampleBufferAudioRenderer's allowedAudioSpatializationFormats property is set to AVAudioSpatializationFormatMonoAndStereo the AVSampleBufferAudioRenderer will attempt to spatialize content tagged with a stereo channel layout, two-channel content with no layout specified as well as mono. It is considered incorrect to render a binaural recording with spatialization. A binaural recording is captured using two carefully placed microphones at each ear where the intent, when played on headphones, is to reproduce a naturally occurring spatial effect. Content tagged with a binaural channel layout will ignore this property value. When an AVSampleBufferAudioRenderer's allowedAudioSpatializationFormats property is set to AVAudioSpatializationFormatMultichannel the AVSampleBufferAudioRenderer will attempt to spatialize any decodable multichannel layout. Setting this property to AVAudioSpatializationFormatMonoStereoAndMultichannel indicates that the sender allows the AVSampleBufferAudioRenderer to spatialize any decodable mono, stereo or multichannel layout. This property is not observable. The default value for this property is AVAudioSpatializationFormatMultichannel.
@property (nonatomic, assign) AVAudioSpatializationFormats allowedAudioSpatializationFormats API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0), visionos(1.0)) API_UNAVAILABLE(watchos);

/// Sends a sample buffer in order to render its contents.
///
/// The audio in the sample buffer is rendered at the sample buffer's output presentation timestamp, as interpreted by the timebase.
- (void)enqueueSampleBuffer:(CMSampleBufferRef)sampleBuffer
#if defined(__swift__)
API_DEPRECATED("Attach renderer to a render synchronizer with sampleBufferReceiver(adding:) and use the receiver's enqueue(_:) async or enqueueImmediately(_:) methods instead", macos(10.13, 27.0), ios(11.0, 27.0), tvos(11.0, 27.0), watchos(4.0, 27.0), visionos(1.0, 27.0))
#else
API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0), watchos(4.0), visionos(1.0))
#endif
;

/// Instructs the receiver to discard pending enqueued sample buffers.
///
/// Additional sample buffers can be appended after -flush.
- (void)flush
#if defined(__swift__)
API_DEPRECATED("Attach renderer to a render synchronizer with sampleBufferReceiver(adding:) and use the receiver's flush() method instead", macos(10.13, 27.0), ios(11.0, 27.0), tvos(11.0, 27.0), watchos(4.0, 27.0), visionos(1.0, 27.0))
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
API_DEPRECATED("Attach renderer to a render synchronizer with sampleBufferReceiver(adding:) and use the receiver to enqueue samples on a detached Task instead", macos(10.13, 27.0), ios(11.0, 27.0), tvos(11.0, 27.0), watchos(4.0, 27.0), visionos(1.0, 27.0))
#else
API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0), watchos(4.0), visionos(1.0))
#endif
;

/// Cancels any current requestMediaDataWhenReadyOnQueue:usingBlock: call.
///
/// This method may be called from outside the block or from within the block.
- (void)stopRequestingMediaData
#if defined(__swift__)
API_DEPRECATED("Cancel the receiver's Task instead", macos(10.13, 27.0), ios(11.0, 27.0), tvos(11.0, 27.0), watchos(4.0, 27.0), visionos(1.0, 27.0))
#else
API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0), watchos(4.0), visionos(1.0))
#endif
;

/// Indicates whether the enqueued media data meets the renderer's preroll level.
///
/// Clients should fetch the value of this property to learn if the renderer has had enough media data enqueued to start playback reliably. Starting playback when this property is NO may prevent smooth playback following an immediate start.
@property (nonatomic, readonly) BOOL hasSufficientMediaDataForReliablePlaybackStart
#if defined(__swift__)
API_DEPRECATED("For smooth playback, attach the renderer to a render synchronizer and set the synchronizer's delaysRateChangeUntilHasSufficientMediaData property to true instead", macos(11.3, 27.0), ios(14.5, 27.0), tvos(14.5, 27.0), watchos(7.4, 27.0), visionos(1.0, 27.0))
#else
API_AVAILABLE(macos(11.3), ios(14.5), tvos(14.5), watchos(7.4), visionos(1.0))
#endif
;

@end

@interface AVSampleBufferAudioRenderer (AVSampleBufferAudioRendererVolumeControl)

/// Indicates the current audio volume of the AVSampleBufferAudioRenderer.
/// 
/// A value of 0.0 means "silence all audio", while 1.0 means "play at the full volume of the audio media".
/// 
/// This property should be used for frequent volume changes, for example via a volume knob or fader.
/// 
/// This property is most useful on iOS to control the volume of the AVSampleBufferAudioRenderer relative to other audio output, not for setting absolute volume.
@property (nonatomic) float volume;

/// Indicates whether or not audio output of the AVSampleBufferAudioRenderer is muted.
/// 
/// Setting this property only affects audio muting for the renderer instance and not for the device.
@property (nonatomic, getter=isMuted) BOOL muted;

@end

@interface AVSampleBufferAudioRenderer (AVSampleBufferAudioRendererQueueManagement)

/// Flushes enqueued sample buffers with presentation time stamps later than or equal to the specified time.
/// 
/// This method can be used to replace media data scheduled to be rendered in the future, without interrupting playback. One example of this is when the data that has already been enqueued is from a sequence of two songs and the second song is swapped for a new song. In this case, this method would be called with the time stamp of the first sample buffer from the second song. After the completion handler is executed with a YES parameter, media data may again be enqueued with timestamps at the specified time.
/// 
/// If NO is provided to the completion handler, the flush did not succeed and the set of enqueued sample buffers remains unchanged. A flush can fail becuse the source time was too close to (or earlier than) the current time or because the current configuration of the receiver does not support flushing at a particular time. In these cases, the caller can choose to flush all enqueued media data by invoking the -flush method.
/// 
/// - Parameter completionHandler: A block that is invoked, possibly asynchronously, after the flush operation completes or fails.
- (void)flushFromSourceTime:(CMTime)time completionHandler:(void (^ NS_SWIFT_SENDABLE)(BOOL flushSucceeded))completionHandler
#if defined(__swift__)
API_DEPRECATED("Attach renderer to a render synchronizer with sampleBufferReceiver(adding:) and use the receiver's flush(fromSourceTime:) method instead", macos(10.13, 27.0), ios(11.0, 27.0), tvos(11.0, 27.0), watchos(4.0, 27.0), visionos(1.0, 27.0))
#else
API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0), watchos(4.0), visionos(1.0))
#endif
;

/// A notification that fires whenever the receiver's enqueued media data has been flushed for a reason other than a call to the -flush method.
/// 
/// The renderer may flush enqueued media data when the user routes playback to a new destination. The renderer may also flush enqueued media data when the playback rate of the attached AVSampleBufferRenderSynchronizer is changed (e.g. 1.0 -> 2.0 or 1.0 -> 0.0 -> 2.0), however no flush will occur for normal pauses (non-zero -> 0.0) and resumes (0.0 -> same non-zero rate as before).
/// 
/// When an automatic flush occurs, the attached render synchronizer's timebase will remain running at its current rate. It is typically best to respond to this notification by enqueueing media data with timestamps starting at the timebase's current time. To the listener, this will sound similar to muting the audio for a short period of time. If it is more desirable to ensure that all audio is played than to keep the timeline moving, you may also stop the synchronizer, set the synchronizer's current time to the value of AVSampleBufferAudioRendererFlushTimeKey, start reenqueueing sample buffers with timestamps starting at that time, and restart the synchronizer. To the listener, this will sound similar to pausing the audio for a short period of time.
/// 
/// This notification is delivered on an arbitrary thread. If sample buffers are being enqueued with the renderer concurrently with the receipt of this notification, it is possible that one or more sample buffers will remain enqueued in the renderer. This is generally undesirable, because the sample buffers that remain will likely have timestamps far ahead of the timebase's current time and so won't be rendered for some time. The best practice is to invoke the -flush method, in a manner that is serialized with enqueueing sample buffers, after receiving this notification and before resuming the enqueueing of sample buffers.
AVF_EXPORT NSNotificationName const AVSampleBufferAudioRendererWasFlushedAutomaticallyNotification
#if defined(__swift__)
API_DEPRECATED("Use the result of AVSampleBufferAudioRenderer.Receiver enqueue(_:) and enqueueImmediately(_:) for .successWithSuggestedFlushReason instead", macos(10.13, 27.0), ios(11.0, 27.0), tvos(11.0, 27.0), watchos(4.0, 27.0), visionos(1.0, 27.0))
#else
API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0), watchos(4.0), visionos(1.0))
#endif
;

/// A notification that indicates the hardware configuration does not match the enqueued data format.
/// 
/// The output configuration of the playback hardware might change during the playback session if other clients play content with different format. In such cases, if the media content format does not match the hardware configuration it would produce suboptimal rendering of the enqueued media data. When the framework detects such mismatch it will issue this notification, so the client can flush the renderer and re-enqueue the sample buffers from the current media playhead, which will configure the hardware based on the format of newly enqueued sample buffers.
AVF_EXPORT NSNotificationName const AVSampleBufferAudioRendererOutputConfigurationDidChangeNotification
#if defined(__swift__)
API_DEPRECATED("Use the result of AVSampleBufferAudioRenderer.Receiver enqueue(_:) and enqueueImmediately(_:) for .successWithSuggestedFlushReason instead", macos(12.0, 27.0), ios(15.0, 27.0), tvos(15.0, 27.0), watchos(8.0, 27.0), visionos(1.0, 27.0))
#else
API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0), watchos(8.0), visionos(1.0))
#endif
;

/// The presentation timestamp of the first enqueued sample that was flushed.
/// 
/// The value of this key is an NSValue wrapping a CMTime.
AVF_EXPORT NSString * const AVSampleBufferAudioRendererFlushTimeKey
#if defined(__swift__)
API_DEPRECATED("Use the result of AVSampleBufferAudioRenderer.Receiver enqueue(_:) and enqueueImmediately(_:) for .successWithSuggestedFlushReason instead", macos(10.13, 27.0), ios(11.0, 27.0), tvos(11.0, 27.0), watchos(4.0, 27.0), visionos(1.0, 27.0))
#else
API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0), watchos(4.0), visionos(1.0))
#endif
;

@end

NS_ASSUME_NONNULL_END

#else
#import <AVFCore/AVSampleBufferAudioRenderer.h>
#endif
