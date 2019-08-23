//
//  MPMusicPlayerQueueDescriptor.h
//  MediaPlayerFramework
//
//  Copyright © 2016 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <MediaPlayer/MediaPlayerDefines.h>

NS_ASSUME_NONNULL_BEGIN

@class MPMediaItem, MPMediaItemCollection, MPMediaQuery;

MP_API_IOS_AVAILABLE_MACOS_TVOS_PROHIBITED(10.1, 10.12.2, 10.1)
@interface MPMusicPlayerQueueDescriptor : NSObject<NSSecureCoding>

@end

MP_API_IOS_AVAILABLE_MACOS_TVOS_PROHIBITED(10.1, 10.12.2, 10.1)
@interface MPMusicPlayerMediaItemQueueDescriptor : MPMusicPlayerQueueDescriptor

- (instancetype)initWithQuery:(MPMediaQuery *)query;
- (instancetype)initWithItemCollection:(MPMediaItemCollection *)itemCollection;

@property (nonatomic, copy, readonly) MPMediaQuery *query;
@property (nonatomic, strong, readonly) MPMediaItemCollection *itemCollection;
@property (nonatomic, strong, nullable) MPMediaItem *startItem;

- (void)setStartTime:(NSTimeInterval)startTime forItem:(MPMediaItem *)mediaItem;
- (void)setEndTime:(NSTimeInterval)endTime forItem:(MPMediaItem *)mediaItem;

@end

MP_API_IOS_AVAILABLE_MACOS_TVOS_PROHIBITED(10.1, 10.12.2, 10.1)
@interface MPMusicPlayerStoreQueueDescriptor : MPMusicPlayerQueueDescriptor

- (instancetype)initWithStoreIDs:(NSArray<NSString *> *)storeIDs;

@property (nonatomic, copy, nullable) NSArray<NSString *> *storeIDs;
@property (nonatomic, copy, nullable) NSString *startItemID;

- (void)setStartTime:(NSTimeInterval)startTime forItemWithStoreID:(NSString *)storeID;
- (void)setEndTime:(NSTimeInterval)endTime forItemWithStoreID:(NSString *)storeID;

@end

NS_ASSUME_NONNULL_END
