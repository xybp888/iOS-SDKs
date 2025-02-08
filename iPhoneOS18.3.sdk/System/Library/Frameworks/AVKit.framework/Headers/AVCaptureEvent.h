/*
	File:  AVCaptureEvent.h
	
	Framework:  AVKit
	
	Copyright © 2022-2023 Apple Inc. All rights reserved.
	
	To report bugs, go to:  http://developer.apple.com/bugreporter/

 */


#import <Foundation/Foundation.h>

#if TARGET_OS_MACCATALYST
#import <AVKitCore/AVKitDefines.h>
#else
#import <AVKit/AVKitDefines.h>
#endif // TARGET_OS_MACCATALYST


NS_ASSUME_NONNULL_BEGIN

@class AVCaptureEvent;


// MARK: -

/*!
	@enum		AVCaptureEventPhase
	@abstract	An enum describing the phase of a capture event.
	@constant	AVCaptureEventPhaseBegan
				A phase sent at the beginning of a capture event.
	@constant	AVCaptureEventPhaseEnded
				A phase sent at the end of a capture event.
	@constant	AVCaptureEventPhaseCancelled
				A phase sent when a capture event is cancelled.
 */
typedef NS_ENUM(NSUInteger, AVCaptureEventPhase) {
	AVCaptureEventPhaseBegan,
	AVCaptureEventPhaseEnded,
	AVCaptureEventPhaseCancelled,
} API_AVAILABLE(ios(17.2)) API_UNAVAILABLE(visionos) API_UNAVAILABLE(macos, tvos, watchos);


// MARK: -

/*!
	@interface	AVCaptureEvent
	@abstract	An object describing a system capture event.
 */
API_AVAILABLE(ios(17.2)) API_UNAVAILABLE(visionos) API_UNAVAILABLE(macos, tvos, watchos)
@interface AVCaptureEvent : NSObject

AVKIT_INIT_UNAVAILABLE


/*!
	@property	phase
	@abstract	The current phase of this capture event.
 */
@property (nonatomic, readonly) AVCaptureEventPhase phase;

@end

NS_ASSUME_NONNULL_END
