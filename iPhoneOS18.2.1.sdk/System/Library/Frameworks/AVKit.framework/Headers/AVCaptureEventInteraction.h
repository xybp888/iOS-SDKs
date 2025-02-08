/*
	File:  AVCaptureEventInteraction.h
	
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
#import <AVKit/AVCaptureEvent.h>
#import <UIKit/UIInteraction.h>


NS_ASSUME_NONNULL_BEGIN

// MARK: -

/*!
	@interface	AVCaptureEventInteraction
	@abstract	A UIInteraction used to register actions triggered by system capture events.
	@discussion	Events may or may not be sent to applications based on the current system state. Backgrounded applications will not receive events, additionally events will only be sent to applications that are actively using the camera. AVCaptureEventInteraction should be attached to views in the responder chain.
 
				This API is for media capture use cases only.
 */
API_AVAILABLE(ios(17.2)) API_UNAVAILABLE(visionos) API_UNAVAILABLE(macos, tvos, watchos)
@interface AVCaptureEventInteraction : NSObject <UIInteraction>

AVKIT_INIT_UNAVAILABLE


/*!
	@method		initWithEventHandler:
	@param		handler
				An event handler called when either the primary or secondary events are triggered.
	@returns	An AVCaptureEventInteraction.
	@abstract	Initializer for an AVCaptureEventInteraction.
 */
- (instancetype)initWithEventHandler:(void (^)(AVCaptureEvent *event))handler NS_SWIFT_NAME(init(handler:));

/*!
	@method		initWithPrimaryEventHandler:secondaryEventHandler:
	@param		primaryHandler
				An event handler called when a primary capture event is triggered.
	@param		secondaryHandler
 				An event handler called when a secondary capture event is triggered.
	@returns	An AVCaptureEventInteraction.
	@abstract	Initializer for an AVCaptureEventInteraction.
 */
- (instancetype)initWithPrimaryEventHandler:(void (^)(AVCaptureEvent *event))primaryHandler secondaryEventHandler:(void (^)(AVCaptureEvent *event))secondaryHandler NS_SWIFT_NAME(init(primary:secondary:));


/*!
	@property	enabled
	@abstract	A boolean value indicating whether this capture event interaction is active or not.
 
				Set this value to NO when your application cannot or will not respond to the action callbacks to avoid non-interactive buttons or UI elements.
 */
@property (nonatomic, readwrite, getter=isEnabled) BOOL enabled;

@end

NS_ASSUME_NONNULL_END
