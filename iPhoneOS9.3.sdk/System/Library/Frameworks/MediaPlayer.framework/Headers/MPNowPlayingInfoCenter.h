//
//  MPNowPlayingInfoCenter.h
//  MediaPlayer
//
//  Copyright 2011 Apple, Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <MediaPlayer/MediaPlayerDefines.h>

NS_ASSUME_NONNULL_BEGIN

// -----------------------------------------------------------------------------
// MPNowPlayingInfoCenter provides an interface for setting the current now 
// playing information for the application. This information will be displayed 
// wherever now playing information typically appears, such as the lock screen
// and app switcher. The now playing info dictionary contains a group of 
// metadata properties for a now playing item. The list of property constants
// is available in <MediaPlayer/MPMediaItem.h>. The properties which are 
// currently supported include:
// 
// MPMediaItemPropertyAlbumTitle
// MPMediaItemPropertyAlbumTrackCount
// MPMediaItemPropertyAlbumTrackNumber
// MPMediaItemPropertyArtist
// MPMediaItemPropertyArtwork
// MPMediaItemPropertyComposer
// MPMediaItemPropertyDiscCount
// MPMediaItemPropertyDiscNumber
// MPMediaItemPropertyGenre
// MPMediaItemPropertyPersistentID
// MPMediaItemPropertyPlaybackDuration
// MPMediaItemPropertyTitle
//
// In addition, metadata properties specific to the current playback session
// may also be specified -- see "Additional metadata properties" below.

MP_EXTERN_CLASS_AVAILABLE(5_0)
@interface MPNowPlayingInfoCenter : NSObject

// Returns the default now playing info center.
// The default center holds now playing info about the current application.
+ (MPNowPlayingInfoCenter *)defaultCenter;

// The current now playing info for the center.
// Setting the info to nil will clear it.
@property (copy, nullable) NSDictionary<NSString *, id> *nowPlayingInfo;

@end

// -----------------------------------------------------------------------------
// Additional metadata properties

// The elapsed time of the now playing item, in seconds.
// Note the elapsed time will be automatically extrapolated from the previously 
// provided elapsed time and playback rate, so updating this property frequently
// is not required (or recommended.)
MP_EXTERN NSString *const MPNowPlayingInfoPropertyElapsedPlaybackTime NS_AVAILABLE_IOS(5_0); // NSNumber (double)

// The playback rate of the now playing item, with 1.0 representing normal 
// playback. For example, 2.0 would represent playback at twice the normal rate.
// If not specified, assumed to be 1.0.
MP_EXTERN NSString *const MPNowPlayingInfoPropertyPlaybackRate NS_AVAILABLE_IOS(5_0); // NSNumber (double)

// The "default" playback rate of the now playing item. You should set this
// property if your app is playing a media item at a rate other than 1.0 in a
// default playback state. e.g., if you are playing back content at a rate of
// 2.0 and your playback state is not fast-forwarding, then the default
// playback rate should also be 2.0. Conversely, if you are playing back content
// at a normal rate (1.0) but the user is fast-forwarding your content at a rate
// greater than 1.0, then the default playback rate should be set to 1.0.
MP_EXTERN NSString *const MPNowPlayingInfoPropertyDefaultPlaybackRate NS_AVAILABLE_IOS(8_0); // NSNumber (double)

// The index of the now playing item in the application's playback queue.
// Note that the queue uses zero-based indexing, so the index of the first item 
// would be 0 if the item should be displayed as "item 1 of 10".
MP_EXTERN NSString *const MPNowPlayingInfoPropertyPlaybackQueueIndex NS_AVAILABLE_IOS(5_0); // NSNumber (NSUInteger)

// The total number of items in the application's playback queue.
MP_EXTERN NSString *const MPNowPlayingInfoPropertyPlaybackQueueCount NS_AVAILABLE_IOS(5_0); // NSNumber (NSUInteger)

// The chapter currently being played. Note that this is zero-based.
MP_EXTERN NSString *const MPNowPlayingInfoPropertyChapterNumber NS_AVAILABLE_IOS(5_0); // NSNumber (NSUInteger)

// The total number of chapters in the now playing item.
MP_EXTERN NSString *const MPNowPlayingInfoPropertyChapterCount NS_AVAILABLE_IOS(5_0); // NSNumber (NSUInteger)

// A list of available language option groups in the now playing item
// Only one language option in a given group can be played at once.
MP_EXTERN NSString *const MPNowPlayingInfoPropertyAvailableLanguageOptions NS_AVAILABLE_IOS(9_0); // NSArrayRef of MPNowPlayingInfoLanguageOptionGroup

// A list of currently active language options in the now playing item.
MP_EXTERN NSString *const MPNowPlayingInfoPropertyCurrentLanguageOptions NS_AVAILABLE_IOS(9_0); // NSArray of MPNowPlayingInfoLanguageOption


NS_ASSUME_NONNULL_END
