#if !__has_include(<AVFCapture/AVCaptureBroadcastVideoOutput.h>)
/*
    File:  AVCaptureBroadcastVideoOutput.h

    Framework:  AVFoundation

    Copyright 2025 Apple Inc. All rights reserved.
 */

#import <AVFoundation/AVCaptureOutputBase.h>
#import <AVFoundation/AVCaptureTimecodeGenerator.h>
#import <AVFoundation/AVBase.h>
#import <Foundation/Foundation.h>
#import <AVFoundation/AVCaptureAncillaryDataEncoder.h>

NS_ASSUME_NONNULL_BEGIN

@protocol AVCaptureBroadcastVideoOutputDelegate;

/// Constants indicating the replacement policy when a video frame is dropped.
///
/// These constants specify how the broadcast video output should handle dropped frames by providing replacement content.
typedef NS_ENUM(NSInteger, AVCaptureBroadcastVideoOutputDroppedFrameReplacementPolicy) {
    /// Repeat the previous frame as replacement.
    /// When a frame is dropped, the most recent successfully output frame is repeated at the expected presentation time. This is the default behavior and provides smoother visual continuity.
    AVCaptureBroadcastVideoOutputDroppedFrameReplacementPolicyRepeatPreviousFrame = 0,
    
    /// Insert a black frame as replacement.
    /// When a frame is dropped, a black frame is inserted at the expected presentation time. This maintains output timing continuity while providing a clear visual indication of the dropped frame.
    AVCaptureBroadcastVideoOutputDroppedFrameReplacementPolicyBlackFrame = 1,
} NS_SWIFT_NAME(AVCaptureBroadcastVideoOutput.DroppedFrameReplacementPolicy) API_AVAILABLE(macos(27.0), ios(27.0), macCatalyst(27.0), tvos(27.0)) API_UNAVAILABLE(visionos) API_UNAVAILABLE(watchos);

/// ``AVCaptureBroadcastVideoOutput`` is a subclass of ``AVCaptureOutput`` that delivers broadcast-quality video and ancillary data through the device's DisplayPort hardware interface (USB-C DP Alt Mode)
///
/// Not all ``AVCaptureDeviceFormat`` instances support ``AVCaptureBroadcastVideoOutput``. Before adding this output to a session, check the device format's ``AVCaptureDeviceFormat.unsupportedCaptureOutputClasses`` property to verify that ``AVCaptureBroadcastVideoOutput`` is not listed. If the current format does not support broadcast video output, the connection will be marked inactive and no samples will be delivered.
///
/// ## Topics
/// ### Creating a broadcast video output
/// - ``init()``
///
/// ### Managing the Output
/// - ``delegate``
/// - ``delegateCallbackQueue``
/// - ``setDelegate:queue:``
///
/// ### Managing Video Output
/// - ``videoSettings``
/// - ``maxBufferedFrameCount``
/// - ``maxSupportedBufferedFrameCount``
/// - ``resetFrameBuffer()``
/// - ``droppedFrameReplacementPolicy``
///
/// ### Dropped Frame Replacement
/// - ``AVCaptureBroadcastVideoOutputDroppedFrameReplacementPolicy``
///
/// ## See Also
/// - ``AVCaptureBroadcastVideoOutputDelegate``
API_AVAILABLE(macos(27.0), ios(27.0), macCatalyst(27.0), tvos(27.0)) API_UNAVAILABLE(visionos) API_UNAVAILABLE(watchos)
@interface AVCaptureBroadcastVideoOutput : AVCaptureOutput

- (instancetype)init;

+ (instancetype)new;

/// The receiver's delegate.
///
/// The value of this property is an object conforming to the ``AVCaptureBroadcastVideoOutputDelegate`` protocol that will be able to monitor the broadcast output operations.
///
/// ## See Also
/// - ``AVCaptureBroadcastVideoOutputDelegate``
/// - ``setDelegate:queue:``
@property(nonatomic, readonly, nullable) id<AVCaptureBroadcastVideoOutputDelegate> delegate;

/// The dispatch queue on which all ``AVCaptureBroadcastVideoOutputDelegate`` methods will be called.
///
/// The value of this property is a dispatch queue on which all delegate method calls will be serialized. If you have not called the ``setDelegate:queue:`` method, the value of this property will be `nil`.
///
/// ## See Also
/// - ``delegate``
/// - ``setDelegate:queue:``
@property(nonatomic, readonly, nullable) dispatch_queue_t delegateCallbackQueue;

/// Sets the receiver's delegate and the dispatch queue on which the delegate will be called.
///
/// - Parameter delegate: An object conforming to the ``AVCaptureBroadcastVideoOutputDelegate`` protocol that will receive broadcast video output notifications.
/// - Parameter delegateCallbackQueue: A dispatch queue on which all ``AVCaptureBroadcastVideoOutputDelegate`` methods will be called.
///
/// ## See Also
/// - ``delegate``
/// - ``AVCaptureBroadcastVideoOutputDelegate``
- (void)setDelegate:(nullable id<AVCaptureBroadcastVideoOutputDelegate>)delegate queue:(nullable dispatch_queue_t)delegateCallbackQueue;

/// The current video output settings for the broadcast video output.
///
/// This read-only property reports the actual video format and output settings currently being used for broadcast video output. The value is a dictionary containing metadata descriptors conforming to SMPTE ST 377 (Material Exchange Format) using Universal Labels (ULs) for professional broadcast interoperability.
///
/// The settings reflect the format negotiated between the camera capture pipeline and the connected broadcast video destination, taking into account:
/// - Camera native capture format capabilities
/// - Connected broadcast video destination capabilities
/// - System performance constraints
/// - Display transport bandwidth limitations
///
/// This property will return `nil` when no broadcast video destination is connected or when the output pipeline is not active.
///
/// > Important: The reported settings reflect the actual negotiated format and may differ from the camera's native capture format due to broadcast hardware constraints.
///
@property(nonatomic, readonly, nullable) NSDictionary<NSString *, id> *videoSettings;

/// This represents the maximum count of buffered frames. By default the value is 0, which means late frames are immediately dropped to maintain minimal latency.
///
/// When set to a value greater than 0, the buffer absorbs minor timing jitter in the capture pipeline, reducing the possibility of dropping frames during temporary processing variations. Frames accumulate in the buffer up to the specified limit. Once the buffer reaches ``maxBufferedFrameCount``, the oldest frame is removed to make room for each new incoming frame, maintaining a rolling window of buffered content.
///
/// Calling ``resetFrameBuffer()`` clears all buffered frames and resets the buffer count back to 0, allowing the buffer to fill again from empty.
///
/// The maximum supported value can be retrieved using ``maxSupportedBufferedFrameCount``. Setting a value higher than the maximum supported value will raise an `NSInvalidArgumentException`.
///
/// > Note: Enabling frame buffering (setting a value > 0) is useful for scenarios where temporary processing delays or timing variations are acceptable, such as when recording or archiving broadcast content. For live broadcast workflows where minimal latency is critical, keep the default value of 0.
///
/// ## See Also
/// - ``resetFrameBuffer()``
/// - ``maxSupportedBufferedFrameCount``
@property(nonatomic) NSInteger maxBufferedFrameCount;

/// The maximum value supported for maxBufferedFrameCount.
///
/// This class property returns the system-imposed limit for buffered frame count to ensure optimal performance and memory usage in broadcast workflows. The limit is determined based on system capabilities.
///
/// ## See Also
/// - ``maxBufferedFrameCount``
@property(class, nonatomic, readonly) NSInteger maxSupportedBufferedFrameCount;

/// Tells the broadcast video output to reset the frame buffer and drop all currently buffered frames.
///
/// This method can be called when buffered video frames should be dropped. This will force all those frames to be dropped and reset the buffered frame count to 0.
///
/// Use this method in scenarios where you need to clear pending frames, such as:
/// - **Pausing or stopping broadcast**: Drop pending frames that should not be transmitted
/// - **Reducing accumulated latency**: If buffering has built up significant delay, reset to return to real-time output
///
/// ## See Also
/// - ``maxBufferedFrameCount``
- (void)resetFrameBuffer;

/// The AVCaptureAncillaryDataEncoder that sends per-frame lens/camera/user-defined acquisition data along with the video buffer.
///
/// This property provides access to the ancillary data encoder to set user-defined data or disable ancillary data encoding entirely.
@property (nonatomic, readonly) AVCaptureAncillaryDataEncoder *ancillaryDataEncoder;

/// The strategy used to replace dropped video frames.
///
/// This property determines how the broadcast video output handles dropped frames. The default value is ``AVCaptureBroadcastVideoOutputDroppedFrameReplacementPolicyRepeatPreviousFrame``.
///
/// ## See Also
/// - ``AVCaptureBroadcastVideoOutputDroppedFrameReplacementPolicy``
@property (nonatomic) AVCaptureBroadcastVideoOutputDroppedFrameReplacementPolicy droppedFrameReplacementPolicy;

@end

/// Protocol for receiving broadcast video output events and data.
///
/// Objects conforming to this protocol can be set as delegates to receive notifications about broadcast video output operations, including dropped frames and ancillary data processing.
///
API_AVAILABLE(macos(27.0), ios(27.0), macCatalyst(27.0), tvos(27.0)) API_UNAVAILABLE(visionos) API_UNAVAILABLE(watchos)
@protocol AVCaptureBroadcastVideoOutputDelegate <NSObject>

@optional

/// Called when a video frame is dropped during broadcast video output processing.
///
/// This method is called whenever the broadcast video output system needs to drop a video frame due to performance constraints, destination issues, buffer overruns, or encoding failures.
///
/// - Parameter output: The ``AVCaptureBroadcastVideoOutput`` instance that dropped the video frame.
/// - Parameter presentationTimeStamp: The presentation timestamp (PTS) of the dropped video frame.
/// - Parameter connection: The ``AVCaptureConnection`` associated with the dropped video frame.
- (void)broadcastVideoOutput:(AVCaptureBroadcastVideoOutput *)output didDropVideoFrameWithPresentationTimeStamp:(CMTime)presentationTimeStamp fromConnection:(AVCaptureConnection *)connection;

@end

NS_ASSUME_NONNULL_END

#else
#import <AVFCapture/AVCaptureBroadcastVideoOutput.h>
#endif
