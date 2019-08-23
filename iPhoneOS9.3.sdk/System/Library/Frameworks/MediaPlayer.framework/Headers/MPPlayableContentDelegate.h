//
//  MPPlayableContentDelegate.h
//  MobileMusicPlayer
//
//  Copyright (c) 2013 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@class MPPlayableContentManager, MPContentItem, MPPlayableContentManagerContext;

/// The MPPlayableContentDelegate is a protocol that allows for external media
/// players to send playback commands to an application. For instance,
/// the user could browse the application's media content (provided by the
/// MPPlayableContentDataSource) and selects a content item to play. If the media
/// player decides that it wants to play the item, it will ask the application's
/// content delegate to initiate playback.
__TVOS_PROHIBITED
@protocol MPPlayableContentDelegate <NSObject>
@optional

/// This method is called when a media player interface wants to play a requested
/// content item. The application should call the completion handler with an
/// appropriate error if there was an error beginning playback for the item.
- (void)playableContentManager:(MPPlayableContentManager *)contentManager initiatePlaybackOfContentItemAtIndexPath:(NSIndexPath *)indexPath completionHandler:(void(^)(NSError * __nullable))completionHandler NS_AVAILABLE_IOS(7_1);

/// This method is called when a media player interface wants the now playing
/// app to setup a playback queue for later playback. The application should
/// load content into its play queue and prepare it for playback, but not start
/// playback until a Play command is received or if the playable content manager
/// requests to play something else.
/// The app should call the provided completion handler once it is ready to play
/// something.
- (void)playableContentManager:(MPPlayableContentManager *)contentManager initializePlaybackQueueWithCompletionHandler:(void(^)(NSError * __nullable))completionHandler NS_AVAILABLE_IOS(9_0);

/// This method is called when the content server notifies the manager that the current context has changed.
- (void)playableContentManager:(MPPlayableContentManager *)contentManager didUpdateContext:(MPPlayableContentManagerContext *)context NS_AVAILABLE_IOS(8_4);

@end

NS_ASSUME_NONNULL_END
