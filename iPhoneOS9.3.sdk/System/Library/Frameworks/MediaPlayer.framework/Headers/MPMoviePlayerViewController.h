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

MP_EXTERN_CLASS_AVAILABLE(3_2)
NS_DEPRECATED_IOS(3_2, 9_0, "Use AVPlayerViewController in AVKit.")
__TVOS_PROHIBITED
@interface MPMoviePlayerViewController : UIViewController

- (instancetype)initWithContentURL:(NSURL *)contentURL NS_DESIGNATED_INITIALIZER;

@property (nonatomic, readonly) MPMoviePlayerController *moviePlayer;

@end

// -----------------------------------------------------------------------------
// UIViewController Additions
// Additions to present a fullscreen movie player as a modal view controller using the standard movie player transition.

@interface UIViewController (MPMoviePlayerViewController)

- (void)presentMoviePlayerViewControllerAnimated:(MPMoviePlayerViewController *)moviePlayerViewController NS_DEPRECATED_IOS(3_2, 9_0, "Use AVPlayerViewController in AVKit.") __TVOS_PROHIBITED;
- (void)dismissMoviePlayerViewControllerAnimated NS_DEPRECATED_IOS(3_2, 9_0, "Use AVPlayerViewController in AVKit.") __TVOS_PROHIBITED;

@end
