#if !__has_include(<AVFCore/AVSampleBufferVideoRenderer.h>)
/*
	File:  AVSampleBufferVideoRenderer.h

	Framework:  AVFoundation
 
	Copyright 2023 Apple Inc. All rights reserved.

*/

/*!
	@class			AVSampleBufferVideoRenderer

	@abstract		AVSampleBufferVideoRenderer provides a mechanism to enqueue sample buffers for rendering.
*/

#import <AVFoundation/AVBase.h>
#import <AVFoundation/AVQueuedSampleBufferRendering.h>

NS_ASSUME_NONNULL_BEGIN

AVF_EXPORT NSNotificationName const AVSampleBufferVideoRendererDidFailToDecodeNotification API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0)) API_UNAVAILABLE(watchos); // decode failed, see NSError in notification payload
AVF_EXPORT NSString *const AVSampleBufferVideoRendererDidFailToDecodeNotificationErrorKey API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0)) API_UNAVAILABLE(watchos); // NSError

AVF_EXPORT NSNotificationName const AVSampleBufferVideoRendererRequiresFlushToResumeDecodingDidChangeNotification API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0)) API_UNAVAILABLE(watchos); // see requiresFlushToResumeDecoding property

API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0)) API_UNAVAILABLE(watchos)
@interface AVSampleBufferVideoRenderer : NSObject <AVQueuedSampleBufferRendering>

/*!
	@property		status
	@abstract		The ability of the video renderer to be used for enqueueing sample buffers.
	@discussion		The value of this property is an AVQueuedSampleBufferRenderingStatus that indicates whether the receiver can be used for enqueueing and rendering sample buffers. When the value of this property is AVQueuedSampleBufferRenderingStatusFailed, clients can check the value of the error property to determine the failure. To resume rendering sample buffers using the video renderer after a failure, clients must first reset the status to AVQueuedSampleBufferRenderingStatusUnknown. This can be achieved by invoking -flush on the video renderer.
					This property is key value observable.
*/
@property (readonly) AVQueuedSampleBufferRenderingStatus status;

/*!
	@property		error
	@abstract		If the video renderer's status is AVQueuedSampleBufferRenderingStatusFailed, this describes the error that caused the failure.
	@discussion		The value of this property is an NSError that describes what caused the video renderer to no longer be able to enqueue sample buffers. If the status is not AVQueuedSampleBufferRenderingStatusFailed, the value of this property is nil.
*/
@property (readonly, nullable) NSError *error;

/*!
	@property		requiresFlushToResumeDecoding
	@abstract		Indicates that the receiver is in a state where it requires a call to -flush to continue decoding frames.
	@discussion		When the application enters a state where use of video decoder resources is not permissible, the value of this property changes to YES along with the video renderer's status changing to AVQueuedSampleBufferRenderingStatusFailed.
					To resume rendering sample buffers using the video renderer after this property's value is YES, clients must first reset the video renderer by calling flush or flushWithRemovalOfDisplayedImage:completionHandler:.
					Clients can track changes to this property via AVSampleBufferVideoRendererRequiresFlushToResumeDecodingDidChangeNotification.
					This property is not key value observable.
*/
@property (readonly) BOOL requiresFlushToResumeDecoding;

/*!
	@method			flushWithRemovalOfDisplayedImage:completionHandler:
	@abstract		Instructs the video renderer to discard pending enqueued sample buffers and call the provided block when complete.
	@param			removeDisplayedImage
					Set YES to remove any currently displayed image, NO to preserve any current image.
	@param			handler
					The handler to invoke when flush operation is complete. May be nil.
	@discussion		A flush resets decoder state. The next frame passed to enqueueSampleBuffer: should be an IDR frame (also known as a key frame or sync sample).
*/

- (void)flushWithRemovalOfDisplayedImage:(BOOL)removeDisplayedImage completionHandler:(nullable void (^)(void))handler;

@end

NS_ASSUME_NONNULL_END

#else
#import <AVFCore/AVSampleBufferVideoRenderer.h>
#endif
