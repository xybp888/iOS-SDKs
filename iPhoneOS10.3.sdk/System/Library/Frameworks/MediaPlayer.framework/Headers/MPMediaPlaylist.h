//
//  MPMediaPlaylist.h
//  MediaPlayer
//
//  Copyright 2008 Apple, Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <MediaPlayer/MediaPlayerDefines.h>
#import <MediaPlayer/MPMediaItemCollection.h>

NS_ASSUME_NONNULL_BEGIN

@class MPMediaItem;

// A playlist may have any number of MPMediaPlaylistAttributes associated.
typedef NS_OPTIONS(NSUInteger, MPMediaPlaylistAttribute) {
    MPMediaPlaylistAttributeNone    = 0,
    MPMediaPlaylistAttributeOnTheGo = (1 << 0), // if set, the playlist was created on a device rather than synced from iTunes
    MPMediaPlaylistAttributeSmart   = (1 << 1),
    MPMediaPlaylistAttributeGenius  = (1 << 2)
} MP_API_IOS_AVAILABLE_MACOS_TVOS_PROHIBITED(3.0, 10.12.2, 3.0);

// An MPMediaPlaylist is a collection of related MPMediaItems in an MPMediaLibrary.
// Playlists have a unique identifier which persists across application launches.

MP_API_IOS_AVAILABLE_MACOS_TVOS_PROHIBITED(3.0, 10.12.2, 3.0)
@interface MPMediaPlaylist : MPMediaItemCollection

#pragma mark - Properties

// Properties marked filterable can also be used to build MPMediaPropertyPredicates (see MPMediaQuery.h).

MP_EXTERN NSString * const MPMediaPlaylistPropertyPersistentID;                             // filterable
@property (nonatomic, readonly) MPMediaEntityPersistentID persistentID NS_AVAILABLE_IOS(7_0);

MP_EXTERN NSString * const MPMediaPlaylistPropertyName;                                     // filterable
@property (nonatomic, readonly, nullable) NSString *name NS_AVAILABLE_IOS(7_0);

MP_EXTERN NSString * const MPMediaPlaylistPropertyPlaylistAttributes;                       // filterable
@property (nonatomic, readonly) MPMediaPlaylistAttribute playlistAttributes NS_AVAILABLE_IOS(7_0);

// For playlists with attribute MPMediaPlaylistAttributeGenius, the seedItems are the MPMediaItems which were used to the generate the playlist.
// Returns nil for playlists without MPMediaPlaylistAttributeGenius set.
MP_EXTERN NSString * const MPMediaPlaylistPropertySeedItems;
@property (nonatomic, readonly, nullable) NSArray<MPMediaItem *> *seedItems NS_AVAILABLE_IOS(8_0);

MP_EXTERN NSString * const MPMediaPlaylistPropertyDescriptionText NS_AVAILABLE_IOS(9_3);
@property (nonatomic, readonly, nullable) NSString *descriptionText NS_AVAILABLE_IOS(9_3);

MP_EXTERN NSString * const MPMediaPlaylistPropertyAuthorDisplayName NS_AVAILABLE_IOS(9_3);
@property (nonatomic, readonly, nullable) NSString *authorDisplayName NS_AVAILABLE_IOS(9_3);

- (void)addItemWithProductID:(NSString *)productID completionHandler:(nullable void (^)(NSError * __nullable error))completionHandler NS_AVAILABLE_IOS(9_3);
- (void)addMediaItems:(NSArray<MPMediaItem *> *)mediaItems completionHandler:(nullable void (^)(NSError * __nullable error))completionHandler NS_AVAILABLE_IOS(9_3);

@end

MP_API_IOS_AVAILABLE_MACOS_TVOS_PROHIBITED(9.3, 10.12.2, 9.3)
@interface MPMediaPlaylistCreationMetadata : NSObject

- (id)init NS_UNAVAILABLE;
- (instancetype)initWithName:(NSString *)name NS_DESIGNATED_INITIALIZER;

/// The display name of the playlist.
@property (nonatomic, readonly, copy) NSString *name;
/// Defaults to the requesting app's display name.
@property (null_resettable, nonatomic, copy) NSString *authorDisplayName;
@property (nonatomic, copy) NSString *descriptionText;

@end

NS_ASSUME_NONNULL_END
