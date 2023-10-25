// Copyright © Apple Inc. All rights reserved.

#import <TargetConditionals.h>
#import <Foundation/Foundation.h>

#if !TARGET_OS_WATCH

@protocol GKTurnBasedMatchmakerViewControllerDelegate;

@class GKMatchmakerViewController, GKTurnBasedMatch, GKMatchRequest;

@protocol GKTurnBasedMatchmakerViewControllerDelegate;

#import <GameKit/GKMatchmakerViewController.h>

/// View controller to manage turn-based matches, invite friends and perform automatching. Present modally from the top view controller.
#if TARGET_OS_IPHONE

#import <UIKit/UINavigationController.h> // UINavigationController

NS_ASSUME_NONNULL_BEGIN
NS_CLASS_AVAILABLE(10_8, 5_0)
@interface GKTurnBasedMatchmakerViewController : UINavigationController
@end
#else
#import <GameKit/GKDialogController.h>
NS_ASSUME_NONNULL_BEGIN
NS_CLASS_AVAILABLE(10_8, 5_0)
@interface GKTurnBasedMatchmakerViewController : NSViewController <GKViewController>
@end
#endif

@interface GKTurnBasedMatchmakerViewController ()

@property (nonatomic, nullable, readwrite, weak) id<GKTurnBasedMatchmakerViewControllerDelegate> turnBasedMatchmakerDelegate;
@property (nonatomic, readwrite, assign) BOOL showExistingMatches; /// defaults to YES

/// This controls the mode of matchmaking to support in the UI (all, nearby only, automatch only, invite only). Throws an exception if you can not set to the desired mode (due to restrictions)
@property (nonatomic, assign) GKMatchmakingMode matchmakingMode API_AVAILABLE(ios(15), macos(12), tvos(15));

- (id)initWithMatchRequest:(GKMatchRequest *)request;

@end

@protocol GKTurnBasedMatchmakerViewControllerDelegate <NSObject>
@required

/// The user has cancelled
- (void)turnBasedMatchmakerViewControllerWasCancelled:(GKTurnBasedMatchmakerViewController *)viewController NS_AVAILABLE(10_8, 5_0);

/// Matchmaking has failed with an error
- (void)turnBasedMatchmakerViewController:(GKTurnBasedMatchmakerViewController *)viewController didFailWithError:(NSError *)error NS_AVAILABLE(10_8, 5_0);


@optional

// Deprecated
- (void)turnBasedMatchmakerViewController:(GKTurnBasedMatchmakerViewController *)viewController didFindMatch:(GKTurnBasedMatch *)match API_DEPRECATED_WITH_REPLACEMENT("-player:receivedTurnEventForMatch:didBecomeActive:", ios(5.0,9.0), macos(10.8,10.11)) API_UNAVAILABLE(tvos);

// Deprectated
- (void)turnBasedMatchmakerViewController:(GKTurnBasedMatchmakerViewController *)viewController playerQuitForMatch:(GKTurnBasedMatch *)match API_DEPRECATED_WITH_REPLACEMENT("-player:wantsToQuitMatch:", ios(5.0,9.0), macos(10.8,10.11)) API_UNAVAILABLE(tvos);

@end

NS_ASSUME_NONNULL_END

#endif
