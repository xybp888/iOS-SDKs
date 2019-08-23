//
//  MPMoviePlayerViewController.h
//  MediaPlayer
//
//  Copyright 2009-2015 Apple, Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <MediaPlayer/MediaPlayerDefines.h>
#import <UIKit/UIViewController.h>

@class MPMoviePlayerController;

MP_API_IOS_DEPRECATED_WITH_REPLACEMENT_MACOS_TVOS_PROHIBITED("Use AVPlayerViewController in AVKit.", 3.2, 9.0, 10.12.2, 10.12.2, 3.2, 9.0)
@interface MPMoviePlayerViewController : UIViewController

- (instancetype)initWithContentURL:(NSURL *)contentURL NS_DESIGNATED_INITIALIZER;

@property (nonatomic, readonly) MPMoviePlayerController *moviePlayer;

@end

// -----------------------------------------------------------------------------
// UIViewController Additions
// Additions to present a fullscreen movie player as a modal view controller using the standard movie player transition.

@interface UIViewController (MPMoviePlayerViewController)

- (void)presentMoviePlayerViewControllerAnimated:(MPMoviePlayerViewController *)moviePlayerViewController MP_API_IOS_DEPRECATED_WITH_REPLACEMENT_MACOS_TVOS_PROHIBITED("Use AVPlayerViewController in AVKit.", 3.2, 9.0, 10.12.2, 10.12.2, 3.2, 9.0);
- (void)dismissMoviePlayerViewControllerAnimated MP_API_IOS_DEPRECATED_WITH_REPLACEMENT_MACOS_TVOS_PROHIBITED("Use AVPlayerViewController in AVKit.", 3.2, 9.0, 10.12.2, 10.12.2, 3.2, 9.0);

@end
