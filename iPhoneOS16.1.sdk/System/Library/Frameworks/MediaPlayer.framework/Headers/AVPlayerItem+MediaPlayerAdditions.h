//
//  AVPlayerItem+MPAdditions.h
//  MediaPlayer
//
//  Copyright © 2022 Apple Inc. All rights reserved.
//

#import <MediaPlayer/MediaPlayerDefines.h>
#import <AVFoundation/AVPlayerItem.h>

NS_ASSUME_NONNULL_BEGIN

@interface AVPlayerItem (MPAdditions)

/// The current now playing info for the player item.
/// Setting the info to nil will clear it.
@property (nonatomic, copy, nullable) NSDictionary<NSString *, id> *nowPlayingInfo MP_API(ios(16.0), tvos(16.0), macos(13.0), watchos(9.0));

@end

NS_ASSUME_NONNULL_END
