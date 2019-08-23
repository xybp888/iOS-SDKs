//
//  MPContentItem.h
//  MobileMusicPlayer
//
//  Copyright (c) 2013 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <MediaPlayer/MediaPlayerDefines.h>

NS_ASSUME_NONNULL_BEGIN

@class MPMediaItemArtwork;

/// MPContentItem represents high-level metadata for a particular media item for
/// representation outside the client application. Examples of media items that a
/// developer might want to represent include song files, streaming audio URLs,
/// or radio stations.
MP_EXTERN_CLASS_AVAILABLE(7_1)
@interface MPContentItem : NSObject

/// Designated initializer. A unique identifier is required to identify the item
/// for later use.
- (instancetype)initWithIdentifier:(NSString *)identifier NS_DESIGNATED_INITIALIZER;

/// A unique identifier for this content item. (Required)
@property (nonatomic, copy, readonly) NSString *identifier;

/// A title for this item. Usually this would be the track name, if representing
/// a song, the episode name of a podcast, etc.
@property (nonatomic, copy, nullable) NSString *title;

/// A subtitle for this item. If this were representing a song, this would
/// usually be the artist or composer.
@property (nonatomic, copy, nullable) NSString *subtitle;

/// Artwork for this item. Examples of artwork for a content item are the album
/// cover for a song, or a movie poster for a movie.
@property (nonatomic, strong, nullable) MPMediaItemArtwork *artwork;

/// Represents whether the content item is a container of other content items.
/// An example of a container content item might be an album, which contains
/// multiple songs.
@property (nonatomic, assign, getter = isContainer) BOOL container;

/// Represents whether this content item is playable or not. A content item can
/// be both a container, and playable. For example, a container item like a
/// playlist might be set as playable if the app would like to provide the
/// option of playing the playlist's tracks in order when selected.
@property (nonatomic, assign, getter = isPlayable) BOOL playable;

/// Represents the current playback progress of the item.
/// 0.0 = not watched/listened/viewed, 1.0 = fully watched/listened/viewed
/// Default is -1.0 (no progress indicator shown)
@property (nonatomic, assign) float playbackProgress;

@end

NS_ASSUME_NONNULL_END
