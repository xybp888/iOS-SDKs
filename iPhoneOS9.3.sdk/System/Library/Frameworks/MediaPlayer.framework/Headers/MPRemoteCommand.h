//
//  MPRemoteCommand.h
//  MediaPlayer
//
//  Copyright (c) 2013 Apple, Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <MediaPlayer/MediaPlayerDefines.h>

NS_ASSUME_NONNULL_BEGIN

@class MPRemoteCommandEvent;

typedef NS_ENUM(NSInteger, MPRemoteCommandHandlerStatus) {
    /// There was no error executing the requested command.
    MPRemoteCommandHandlerStatusSuccess = 0,
    
    /// The command could not be executed because the requested content does not
    /// exist in the current application state.
    MPRemoteCommandHandlerStatusNoSuchContent = 100,
    
    /// The command could not be executed because there is no now playing item
    /// available that is required for this command. As an example, an
    /// application would return this error code if an "enable language option"
    /// command is received, but nothing is currently playing.
    MPRemoteCommandHandlerStatusNoActionableNowPlayingItem NS_ENUM_AVAILABLE_IOS(9_1) = 110,
    
    /// The command could not be executed for another reason.
    MPRemoteCommandHandlerStatusCommandFailed = 200
} NS_ENUM_AVAILABLE_IOS(7_1);

MP_EXTERN_CLASS_AVAILABLE(7_1)
@interface MPRemoteCommand : NSObject

/// Whether a button (for example) should be enabled and tappable for this
/// particular command.
@property (nonatomic, assign, getter = isEnabled) BOOL enabled;

// Target-action style for adding handlers to commands.
// Actions receive an MPRemoteCommandEvent as the first parameter.
// Targets are not retained by addTarget:action:, and should be removed from the
// command when the target is deallocated.
//
// Your selector should return a MPRemoteCommandHandlerStatus value when
// possible. This allows the system to respond appropriately to commands that
// may not have been able to be executed in accordance with the application's
// current state.
- (void)addTarget:(id)target action:(SEL)action;
- (void)removeTarget:(id)target action:(nullable SEL)action;
- (void)removeTarget:(nullable id)target;

/// Returns an opaque object to act as the target.
- (id)addTargetWithHandler:(MPRemoteCommandHandlerStatus(^)(MPRemoteCommandEvent *event))handler;

@end

MP_EXTERN_CLASS_AVAILABLE(7_1)
@interface MPSkipIntervalCommand : MPRemoteCommand

/// An array of NSNumbers (NSTimeIntervals) that contain preferred skip intervals.
@property (nonatomic, copy) NSArray *preferredIntervals;

@end

MP_EXTERN_CLASS_AVAILABLE(7_1)
@interface MPFeedbackCommand : MPRemoteCommand

/// Whether the feedback command is in an "active" state. An example of when a
/// feedback command would be active is if the user already "liked" a particular
/// content item.
@property (nonatomic, assign, getter = isActive) BOOL active;

/// A localized string briefly describing the context of the command.
@property (nonatomic, copy) NSString *localizedTitle;

/// An optional shorter version of the localized title for this feedback
/// command. MediaPlayer uses this property to display this command's title on
/// remote control interfaces with little screen space.
@property (nonatomic, copy) NSString *localizedShortTitle NS_AVAILABLE_IOS(8_0);

@end

MP_EXTERN_CLASS_AVAILABLE(7_1)
@interface MPRatingCommand : MPRemoteCommand

/// Minimum rating for the command.
@property (nonatomic, assign) float minimumRating;

/// Maximum rating for the command.
@property (nonatomic, assign) float maximumRating;

@end

MP_EXTERN_CLASS_AVAILABLE(7_1)
@interface MPChangePlaybackRateCommand : MPRemoteCommand

/// An array of NSNumbers (floats) that contain supported playback rates that
/// the command can send.
@property (nonatomic, copy) NSArray<NSNumber *> *supportedPlaybackRates;

@end

MP_EXTERN_CLASS_AVAILABLE(9_0)
@interface MPChangePlaybackPositionCommand : MPRemoteCommand

@end

NS_ASSUME_NONNULL_END
