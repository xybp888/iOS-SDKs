//
//  MPMusicPlayerApplicationController.h
//  MediaPlayer
//
//  Copyright 2016 Apple, Inc. All rights reserved.
//

#import <MediaPlayer/MediaPlayer.h>
#import <MediaPlayer/MPMusicPlayerController.h>

NS_ASSUME_NONNULL_BEGIN

MP_API_IOS_AVAILABLE_MACOS_TVOS_PROHIBITED(10.3, 10.12.1, 10.3)
@interface MPMusicPlayerControllerQueue : NSObject

- (instancetype)init NS_UNAVAILABLE;

@property (nonatomic, copy, readonly) NSArray<MPMediaItem *> *items;

@end

MP_API_IOS_AVAILABLE_MACOS_TVOS_PROHIBITED(10.3, 10.12.1, 10.3)
@interface MPMusicPlayerControllerMutableQueue : MPMusicPlayerControllerQueue

- (void)insertQueueDescriptor:(MPMusicPlayerQueueDescriptor *)queueDescriptor afterItem:(nullable MPMediaItem *)afterItem;
- (void)removeItem:(MPMediaItem *)item;

@end

MP_API_IOS_AVAILABLE_MACOS_TVOS_PROHIBITED(10.3, 10.12.1, 10.3)
@interface MPMusicPlayerApplicationController : MPMusicPlayerController

- (void)performQueueTransaction:(void (^)(MPMusicPlayerControllerMutableQueue *queue))queueTransaction completionHandler:(void (^)(MPMusicPlayerControllerQueue *queue, NSError *_Nullable error))completionHandler;

@end

// Posted when the queue changes
MP_EXTERN __TVOS_PROHIBITED NSString * const MPMusicPlayerControllerQueueDidChangeNotification;

NS_ASSUME_NONNULL_END
