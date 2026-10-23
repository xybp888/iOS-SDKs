//
//  CPPlaybackConfiguration.h
//  CarPlay
//
//  Copyright © 2025 Apple Inc. All rights reserved.
//

#import <CarPlay/CPTemplate.h>
#import <CoreGraphics/CoreGraphics.h>
#import <CoreMedia/CoreMedia.h>
#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/**
 The style of media presentation shown after selecting the item.
 */
API_AVAILABLE(ios(26.4)) API_UNAVAILABLE(tvos) API_UNAVAILABLE(macos, watchos)
typedef NS_ENUM(NSInteger, CPPlaybackPresentation) {
    CPPlaybackPresentationNone = 0, // Playback will not present directly from selection of this item
    CPPlaybackPresentationAudio,    // Show now playing
    CPPlaybackPresentationVideo     // Present video if available, otherwise show now playing
} NS_SWIFT_NAME(CPPlaybackConfiguration.Presentation);

/**
 The playback action to perform on the item.
 */
API_AVAILABLE(ios(26.4)) API_UNAVAILABLE(tvos) API_UNAVAILABLE(macos, watchos)
typedef NS_ENUM(NSInteger, CPPlaybackAction) {
    CPPlaybackActionNone = 0,   // No representation of playback action for this item
    CPPlaybackActionPlay,       // Start or resume playback
    CPPlaybackActionPause,      // Pause playback
    CPPlaybackActionReplay      // Replay content from the beginning
} NS_SWIFT_NAME(CPPlaybackConfiguration.Action);

/**
 @c CPPlaybackConfiguration represents the playback status of the media content that is represented by template items.
 @note The preferred presentation of playback may be used to prepare the system for playback of that content.
 */
API_AVAILABLE(ios(26.4)) API_UNAVAILABLE(tvos) API_UNAVAILABLE(macos, watchos)
CARPLAY_TEMPLATE_UI_ACTOR
@interface CPPlaybackConfiguration : NSObject <NSCopying, NSSecureCoding>

/**
Initialize a description of the playable media content that is represented by template items.

@note Video presentation may be unsupported for this session  (see `-[CPSessionConfiguration videoPlaybackSupported]`) or may be unavailable due to playback policy.

@param preferredPresentation The preferred style of media presentation shown after selecting the item.
@param playbackAction The playback action to perform on this item, such as play, pause, or replay.
@param elapsedTime The elapsed playback time as a CMTime value.
@param duration The total duration of the media content as a CMTime value. Provide 0 if the duration of the content is unknown or unavailable, for example in live-streaming content.
*/
- (instancetype)initWithPreferredPresentation:(CPPlaybackPresentation)preferredPresentation
                               playbackAction:(CPPlaybackAction)playbackAction
                                  elapsedTime:(CMTime)elapsedTime
                                     duration:(CMTime)duration API_AVAILABLE(ios(26.4));

/**
 The style of media presentation shown after selecting the item.
 */
@property(nonatomic, assign, readonly) CPPlaybackPresentation preferredPresentation API_AVAILABLE(ios(26.4));

/**
 The playback action to perform on this item, such as play, pause, or replay.
 */
@property (nonatomic, assign, readonly) CPPlaybackAction playbackAction API_AVAILABLE(ios(26.4));

/**
 The elapsed playback time as a CMTime value.
 */
@property (nonatomic, assign, readonly) CMTime elapsedTime API_AVAILABLE(ios(26.4));

/**
 The total duration of the media content as a CMTime value. Provide 0 if the duration of the content is unknown or unavailable, for example in live-streaming content.
 */
@property (nonatomic, assign, readonly) CMTime duration API_AVAILABLE(ios(26.4));

@end


API_AVAILABLE(ios(26.4)) API_UNAVAILABLE(tvos) API_UNAVAILABLE(macos, watchos)
@protocol CPPlayableItem <NSObject>

@property (nonatomic, copy, nullable) CPPlaybackConfiguration *playbackConfiguration API_AVAILABLE(ios(26.4));

@end

NS_ASSUME_NONNULL_END
