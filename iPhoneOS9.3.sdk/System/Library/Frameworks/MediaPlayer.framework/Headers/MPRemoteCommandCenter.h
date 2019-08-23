//
//  MPRemoteCommandCenter.h
//  MediaPlayer
//
//  Copyright (c) 2013 Apple, Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <MediaPlayer/MediaPlayerDefines.h>

NS_ASSUME_NONNULL_BEGIN

@class MPRemoteCommand, MPSkipIntervalCommand, MPRatingCommand, MPChangePlaybackRateCommand, MPFeedbackCommand, MPChangePlaybackPositionCommand;

MP_EXTERN_CLASS_AVAILABLE(7_1)
@interface MPRemoteCommandCenter : NSObject

// Playback Commands
@property (nonatomic, readonly) MPRemoteCommand *pauseCommand;
@property (nonatomic, readonly) MPRemoteCommand *playCommand;
@property (nonatomic, readonly) MPRemoteCommand *stopCommand;
@property (nonatomic, readonly) MPRemoteCommand *togglePlayPauseCommand;
@property (nonatomic, readonly) MPRemoteCommand *enableLanguageOptionCommand;
@property (nonatomic, readonly) MPRemoteCommand *disableLanguageOptionCommand;

// Previous/Next Track Commands
@property (nonatomic, readonly) MPRemoteCommand *nextTrackCommand;
@property (nonatomic, readonly) MPRemoteCommand *previousTrackCommand;

// Skip Interval Commands
@property (nonatomic, readonly) MPSkipIntervalCommand *skipForwardCommand;
@property (nonatomic, readonly) MPSkipIntervalCommand *skipBackwardCommand;

// Seek Commands
@property (nonatomic, readonly) MPRemoteCommand *seekForwardCommand;
@property (nonatomic, readonly) MPRemoteCommand *seekBackwardCommand;

// Rating Command
@property (nonatomic, readonly) MPRatingCommand *ratingCommand;

// Playback Commands
@property (nonatomic, readonly) MPChangePlaybackRateCommand *changePlaybackRateCommand;

// Feedback Commands
// These are generalized to three distinct actions. Your application can provide
// additional context about these actions with the localizedTitle property in
// MPFeedbackCommand.
@property (nonatomic, readonly) MPFeedbackCommand *likeCommand;
@property (nonatomic, readonly) MPFeedbackCommand *dislikeCommand;
@property (nonatomic, readonly) MPFeedbackCommand *bookmarkCommand;

@property (nonatomic, readonly) MPChangePlaybackPositionCommand *changePlaybackPositionCommand;

+ (MPRemoteCommandCenter *)sharedCommandCenter;

@end

NS_ASSUME_NONNULL_END
