#if !__has_include(<AVFCore/AVPlayerLayer.h>)
/*
	File:  AVPlayerLayer.h

	Framework:  AVFoundation
 
	Copyright 2010-2022 Apple Inc. All rights reserved.

*/



#import <AVFoundation/AVBase.h>
#import <AVFoundation/AVAnimation.h>
#import <CoreVideo/CVPixelBuffer.h>

#if __has_include(<QuartzCore/CoreAnimation.h>)
#import <QuartzCore/CoreAnimation.h>

@class AVPlayer;
@class AVPlayerLayerInternal;

NS_ASSUME_NONNULL_BEGIN

/// AVPlayerLayer is a subclass of CALayer to which an AVPlayer can direct its visual output.
/// 
/// To create an AVPlayerLayer instance:
/// 
/// AVPlayer *player = ...;
/// // ... set up an AVPlayer
/// 
/// CALayer *superlayer = ...;
/// AVPlayerLayer *playerLayer = [AVPlayerLayer playerLayerWithPlayer:player];
/// 
/// // ... set up the AVPlayerLayer's geometry. For example: set the AVPlayerLayer frame according to the presentationSize of the AVPlayer's currentItem.
/// 
/// [superlayer addSublayer:playerLayer];
/// 
/// AVPlayerLayer provides a property 'videoGravity' that defines how the video content is displayed within the AVPlayerLayer property 'bounds' rect. 
/// The value for the @"contents" key of an AVPlayerLayer is opaque and effectively read-only.
/// 
/// Note that during playback AVPlayer may compensate for temporal drift between its visual output
/// and its audible output to one or more independently-clocked audio output devices by adjusting the timing of its
/// associated AVPlayerLayers. The effects of these adjustments are usually very minute; however, clients that
/// wish to remain entirely unaffected by such adjustments may wish to place other layers for which timing is
/// important into indepedently timed subtrees of their layer trees.
API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), visionos(1.0)) API_UNAVAILABLE(watchos)
@interface AVPlayerLayer : CALayer
{
@private
	AVPlayerLayerInternal		*_playerLayer;
}

/// Returns an instance of AVPlayerLayer to display the visual output of the specified AVPlayer.
/// 
/// - Returns: An instance of AVPlayerLayer.
+ (AVPlayerLayer *)playerLayerWithPlayer:(nullable AVPlayer *)player;

/// Indicates the instance of AVPlayer for which the AVPlayerLayer displays visual output
@property (nonatomic, retain, nullable) AVPlayer *player;

/// A string defining how the video is displayed within an AVPlayerLayer bounds rect. @discusssion Options are AVLayerVideoGravityResizeAspect, AVLayerVideoGravityResizeAspectFill and AVLayerVideoGravityResize. AVLayerVideoGravityResizeAspect is default. See <AVFoundation/AVAnimation.h> for a description of these options.
@property (copy) AVLayerVideoGravity videoGravity;

/// Boolean indicating that the first video frame has been made ready for display for the current item of the associated AVPlayer. @discusssion Use this property as an indicator of when best to show or animate-in an AVPlayerLayer into view. An AVPlayerLayer may be displayed, or made visible, while this property is NO, however the layer will not have any user-visible content until the value becomes YES. Note that if an animation is added to an AVPlayerLayer before it becomes readyForDisplay the video image displayed inside might not animate with the receiver. This property remains NO for an AVPlayer currentItem whose AVAsset contains no enabled video tracks. This property is key-value observable.
@property (nonatomic, readonly, getter=isReadyForDisplay) BOOL readyForDisplay;

/// The current size and position of the video image as displayed within the receiver's bounds.
@property (nonatomic, readonly) CGRect videoRect API_AVAILABLE(macos(10.9), ios(7.0), tvos(9.0), visionos(1.0)) API_UNAVAILABLE(watchos);

/// The client requirements for the visual output displayed in AVPlayerLayer during playback.
/// 
/// Pixel buffer attribute keys are defined in <CoreVideo/CVPixelBuffer.h>
/// This property is key-value observable.
@property (nonatomic, copy, nullable) NSDictionary<NSString *, id> *pixelBufferAttributes API_AVAILABLE(macos(10.11), ios(9.0), tvos(9.0), visionos(1.0)) API_UNAVAILABLE(watchos);

/// Returns a retained reference to the pixel buffer currently displayed in this AVPlayerLayer. This will return NULL if the displayed pixel buffer is protected, no image is currently being displayed, if the current player's rate is non-zero or if the image is unavailable.
/// 
/// This will only return the current image while the media is paused, otherwise this will return nil. Clients must release the pixel buffer after use.
/// 
/// Do not write to the returned CVPixelBuffer's attachments or pixel data.
- (nullable CVPixelBufferRef)copyDisplayedPixelBuffer CF_RETURNS_RETAINED 
#if defined(__swift__)
API_DEPRECATED_WITH_REPLACEMENT("displayedReadOnlyPixelBuffer", macos(13.0, 27.0), ios(16.0, 27.0), tvos(16.0, 27.0), watchos(1.0, 27.0), visionos(1.0, 27.0))
#else
API_AVAILABLE(macos(13.0), ios(16.0), tvos(16.0), visionos(1.0)) API_UNAVAILABLE(watchos)
#endif
;

/// Starts displaying a caption preview with the specified accessibility profile.
///
/// This method enables a preview mode that displays sample caption text using the visual appearance settings from the specified accessibility profile. The preview replaces any currently active subtitles and/or closed captions while active. The sample caption text position can be specified to avoid UI controls.
///
/// - Parameters:
///   - profileID: The identifier of the accessibility profile to use for caption appearance.
///                Profile IDs can be obtained from `MACaptionAppearanceCopyProfileIDs()`.
///                This determines font, color, background, and other visual characteristics.
///   - position: A CGPoint that defines the position (in points) of the caption preview relative to the default positioning of content captions (centered near the bottom of the video). Position values can be negative. (0, 0) represents the default positioning.
///   - text: Optional custom text to display in the preview. If `nil`, a standard localized preview message will be shown.
///
/// - Note: You must call ``stopShowingCaptionPreview`` to exit the preview.
- (void)setCaptionPreviewProfileID:(NSString *)profileID position:(CGPoint)position text:(nullable NSString *)text API_AVAILABLE(macos(26.4), ios(26.4), tvos(26.4), visionos(26.4)) API_UNAVAILABLE(watchos);

/// Stops showing the caption preview.
///
/// This method stops the caption preview and restores any currently active subtitles and/or closed captions.
- (void)stopShowingCaptionPreview API_AVAILABLE(macos(26.4), ios(26.4), tvos(26.4), visionos(26.4)) API_UNAVAILABLE(watchos);

@end

NS_ASSUME_NONNULL_END

#endif  // __has_include(<QuartzCore/CoreAnimation.h>)

#else
#import <AVFCore/AVPlayerLayer.h>
#endif
