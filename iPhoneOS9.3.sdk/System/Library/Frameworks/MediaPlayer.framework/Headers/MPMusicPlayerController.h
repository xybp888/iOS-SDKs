//
//  MPMusicPlayerController.h
//  MediaPlayer
//
//  Copyright 2008 Apple, Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <MediaPlayer/MediaPlayerDefines.h>
#import <MediaPlayer/MPMediaItemCollection.h>
#import <MediaPlayer/MPMediaItem.h>
#import <MediaPlayer/MPMediaQuery.h>
#import <MediaPlayer/MPMediaPlayback.h>

NS_ASSUME_NONNULL_BEGIN

@class MPMediaItem, MPMediaQuery, MPMusicPlayerControllerInternal;

typedef NS_ENUM(NSInteger, MPMusicPlaybackState) {
    MPMusicPlaybackStateStopped,
    MPMusicPlaybackStatePlaying,
    MPMusicPlaybackStatePaused,
    MPMusicPlaybackStateInterrupted,
    MPMusicPlaybackStateSeekingForward,
    MPMusicPlaybackStateSeekingBackward
} __TVOS_PROHIBITED;

typedef NS_ENUM(NSInteger, MPMusicRepeatMode) {
    MPMusicRepeatModeDefault, // the user's preference for repeat mode
    MPMusicRepeatModeNone,
    MPMusicRepeatModeOne,
    MPMusicRepeatModeAll
} __TVOS_PROHIBITED;

typedef NS_ENUM(NSInteger, MPMusicShuffleMode) {
    MPMusicShuffleModeDefault, // the user's preference for shuffle mode
    MPMusicShuffleModeOff,
    MPMusicShuffleModeSongs,
    MPMusicShuffleModeAlbums
} __TVOS_PROHIBITED;

// MPMusicPlayerController allows playback of MPMediaItems through the Music application.
MP_EXTERN_CLASS_AVAILABLE(3_0)
__TVOS_PROHIBITED
@interface MPMusicPlayerController : NSObject <MPMediaPlayback>

/// Playing media items with the applicationMusicPlayer will restore the user's Music state after the application quits.
+ (MPMusicPlayerController *)applicationMusicPlayer;

/// Playing media items with the systemMusicPlayer will replace the user's current Music state.
+ (MPMusicPlayerController *)systemMusicPlayer;

+ (MPMusicPlayerController *)iPodMusicPlayer NS_DEPRECATED_IOS(3_0, 8_0, "Use +systemMusicPlayer instead.");

@end

@interface MPMusicPlayerController (MPPlaybackControl)

// See MPMediaPlayback.h for basic playback control.

// Returns the current playback state of the music player
@property (nonatomic, readonly) MPMusicPlaybackState playbackState;

// Determines how music repeats after playback completes. Defaults to MPMusicRepeatModeDefault.
@property (nonatomic) MPMusicRepeatMode repeatMode;

// Determines how music is shuffled when playing. Defaults to MPMusicShuffleModeDefault.
@property (nonatomic) MPMusicShuffleMode shuffleMode;

// The current volume of playing music, in the range of 0.0 to 1.0.
// This property is deprecated -- use MPVolumeView for volume control instead.
@property (nonatomic) float volume NS_DEPRECATED_IOS(3_0, 7_0);

// Returns the currently playing media item, or nil if none is playing.
// Setting the nowPlayingItem to an item in the current queue will begin playback at that item.
@property (nonatomic, copy, nullable) MPMediaItem *nowPlayingItem;

// Returns the index of the now playing item in the current playback queue.
// May return NSNotFound if the index is not valid (e.g. an empty queue or an infinite playlist).
@property (nonatomic, readonly) NSUInteger indexOfNowPlayingItem NS_AVAILABLE_IOS(5_0);

// Call -play to begin playback after setting an item queue source. Setting a query will implicitly use MPMediaGroupingTitle.
- (void)setQueueWithQuery:(MPMediaQuery *)query;
- (void)setQueueWithItemCollection:(MPMediaItemCollection *)itemCollection;
- (void)setQueueWithStoreIDs:(NSArray<NSString *> *)storeIDs NS_AVAILABLE_IOS(9_3);

// Skips to the next item in the queue. If already at the last item, this will end playback.
- (void)skipToNextItem;

// Restarts playback at the beginning of the currently playing media item.
- (void)skipToBeginning;

// Skips to the previous item in the queue. If already at the first item, this will end playback.
- (void)skipToPreviousItem;

// These methods determine whether playback notifications will be generated.
// Calls to begin/endGeneratingPlaybackNotifications are nestable.
- (void)beginGeneratingPlaybackNotifications;
- (void)endGeneratingPlaybackNotifications;

@end

// Posted when the playback state changes, either programatically or by the user.
MP_EXTERN __TVOS_PROHIBITED NSString * const MPMusicPlayerControllerPlaybackStateDidChangeNotification;

// Posted when the currently playing media item changes.
MP_EXTERN __TVOS_PROHIBITED NSString * const MPMusicPlayerControllerNowPlayingItemDidChangeNotification;

// Posted when the current volume changes.
MP_EXTERN __TVOS_PROHIBITED NSString * const MPMusicPlayerControllerVolumeDidChangeNotification;

NS_ASSUME_NONNULL_END
