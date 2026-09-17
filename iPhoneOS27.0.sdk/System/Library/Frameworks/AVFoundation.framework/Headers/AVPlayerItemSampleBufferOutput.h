#if !__has_include(<AVFCore/AVPlayerItemSampleBufferOutput.h>)
/*
    File:  AVPlayerItemSampleBufferOutput.h

	Framework:  AVFoundation
 
    Copyright 2021-2022, 2024, 2026 Apple Inc. All rights reserved.
*/

#import <AVFoundation/AVBase.h>
#import <AVFoundation/AVPlayerItemOutput.h>
#import <CoreMedia/CMSampleBuffer.h>

@class AVPlayerItemSampleBufferOutput;

NS_ASSUME_NONNULL_BEGIN

/// Defines common delegate methods for objects participating in sample buffer output.
API_AVAILABLE(macos(27), ios(27), tvos(27), watchos(27), visionos(27))
NS_REFINED_FOR_SWIFT
@protocol AVPlayerItemSampleBufferOutputDelegate <NSObject>
 
@optional
 
/// Invoked when the output becomes ready to deliver a sample buffer.
- (void)outputMediaDataAvailable:(AVPlayerItemSampleBufferOutput *)output;
 
/// Invoked when the output is commencing a new sequence.
///
/// This method is invoked after seeks and changes in playback direction. If you are maintaining
/// any queued future samples previously copied, it may be appropriate to discard these upon receiving this message.
///
/// Note that delivery of this message may race with calls to ``-copyNextSampleBuffer``.
- (void)outputSequenceWasRestarted:(AVPlayerItemSampleBufferOutput *)output;

@end

/// Configuration options specified when creating an ``AVPlayerItemSampleBufferOutput``.
///
/// Mutating ``AVPlayerItemSampleBufferOutputConfiguration`` after using it to create an ``AVPlayerItemSampleBufferOutput`` object will not affect the ``AVPlayerItemSampleBufferOutput`` object.
API_AVAILABLE(macos(27), ios(27), tvos(27), watchos(27), visionos(27))
NS_SWIFT_SENDABLE
@interface AVPlayerItemSampleBufferOutputConfiguration : NSObject

@end

/// Audio-specific configuration options specified when creating an ``AVPlayerItemSampleBufferOutput``.
API_AVAILABLE(macos(27), ios(27), tvos(27), watchos(27), visionos(27))
NS_SWIFT_SENDABLE
@interface AVPlayerItemSampleBufferOutputAudioConfiguration : AVPlayerItemSampleBufferOutputConfiguration

/// Indicates the audio format in which the client prefers to receive the output sample buffers.
///
/// Must be a PCM format.
///
/// The output `CMSampleBuffers'` `CMFormatDescription` may not exactly match this format description, but it will match the parts described in the ``AudioStreamBasicDescription``. The output format may differ from the requestedAudioFormat in its LPCM numeric type, channel interleaving and sample size.
/// If any of these differs from the format in which you wish to operate, you can set up conversions between the format of audio sample buffers provided by the AVPlayerItemSampleBufferOutput and your required processing format by using AudioConverter or AVAudioEngine.
///
/// Specifying a PCM format is currently required.  In the future it may be optional.
@property (nonatomic, nullable) __attribute__((NSObject)) CMFormatDescriptionRef requestedAudioFormat;

@end

/// ``AVPlayerItemSampleBufferOutput`` delivers `CMSampleBuffers` for ``AVPlayerItem`` playback.
///
/// Playback only happens when the ``AVPlayerItem`` is the current item of its ``AVPlayer``.
///
/// Create an ``AVPlayerItemSampleBufferOutput`` with a
/// ``AVPlayerItemSampleBufferOutputAudioConfiguration`` to configure it to deliver
/// `CMSampleBuffers` containing the decoded audio, and attach it to the ``AVPlayerItem``
/// using ``-[AVPlayerItem addOutput:]``; the audio will be in the format specified by the
/// configuration object's ``requestedAudioFormat``.
///
/// Note that ``AVPlayerItemSampleBufferOutput`` may be used to pull `CMSampleBuffers` far ahead
/// of the current play time.  Practical use requires clients to monitor the item timebase time, and pause pulling
/// when they have received CMSampleBuffers sufficient to prepare for near-term-future playback or processing.
///
/// Marker-only `CMSampleBuffers` may be among those returned; you can detect and skip these
/// by testing whether `CMSampleBufferGetNumSamples(sampleBuffer) == 0`.
///
/// The output `CMSampleBuffers` will have appropriate OutputPresentationTimeStamps for playback,
/// but beyond that, synchronizing presentation to the AVPlayerItem's timebase is entirely up to the client.
///
/// Currently supported for HLS `AVPlayerItems` only, and only for delivering decoded PCM audio.
NS_SWIFT_SENDABLE
API_AVAILABLE(macos(27), ios(27), tvos(27), watchos(27), visionos(27))
@interface AVPlayerItemSampleBufferOutput : AVPlayerItemOutput

/// Initializes an instance of ``AVPlayerItemSampleBufferOutput``.
///
/// - Parameter configuration:
///		Specifies the kind and format of media data to be delivered.
- (instancetype)initWithConfiguration:(nullable AVPlayerItemSampleBufferOutputConfiguration *)configuration;

/// Copies the next sample buffer for the output synchronously.
///
/// - Returns: A CMSampleBuffer object referencing the output sample buffer.
///
/// The client is responsible for calling ``CFRelease`` on the returned ``CMSampleBuffer`` object when finished with it.
/// This method will return `NULL` if there are no more sample buffers currently available for the receiver.
/// Clients may use the delegate method ``outputMediaDataAvailable:`` to be informed when the
/// next ``CMSampleBuffer`` becomes available.
- (nullable NS_SWIFT_SENDING CMSampleBufferRef)copyNextSampleBuffer CF_RETURNS_RETAINED NS_REFINED_FOR_SWIFT;

/// Sets the receiver's delegate and a dispatch queue on which the delegate will be called.
/// - Parameter delegate:
/// 	An object conforming to AVPlayerItemSampleBufferOutputDelegate protocol.
/// - Parameter delegateQueue:
///		A dispatch queue on which all delegate methods will be called.
- (void)setDelegate:(nullable id<AVPlayerItemSampleBufferOutputDelegate>)delegate queue:(nullable dispatch_queue_t)delegateQueue NS_REFINED_FOR_SWIFT;

/// The receiver's delegate.
@property (readonly, weak) id<AVPlayerItemSampleBufferOutputDelegate> delegate NS_REFINED_FOR_SWIFT;

/// The dispatch queue where the delegate is messaged.
@property (nonatomic, readonly, nullable) dispatch_queue_t delegateQueue NS_REFINED_FOR_SWIFT;

@end

NS_ASSUME_NONNULL_END

#else
#import <AVFCore/AVPlayerItemSampleBufferOutput.h>
#endif
