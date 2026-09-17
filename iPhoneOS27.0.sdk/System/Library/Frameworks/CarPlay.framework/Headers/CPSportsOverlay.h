//
//  CPSportsOverlay.h
//  CarPlay
//
//  Copyright © 2025 Apple Inc. All rights reserved.
//

#import <UIKit/UIKit.h>

@class CPNowPlayingSportsTeam;
@class CPNowPlayingSportsEventStatus;

NS_ASSUME_NONNULL_BEGIN

/**
 A sports overlay that displays left and right team information.
 */
API_AVAILABLE(ios(26.4)) API_UNAVAILABLE(tvos) API_UNAVAILABLE(macos, watchos)
CARPLAY_TEMPLATE_UI_ACTOR
@interface CPSportsOverlay : NSObject <NSSecureCoding>

/**
 Initialize a sports overlay with left and right team objects.

 @param leftTeam The left team information.
 @param rightTeam The right team information.
 */
- (instancetype)initWithLeftTeam:(CPNowPlayingSportsTeam *)leftTeam
                       rightTeam:(CPNowPlayingSportsTeam *)rightTeam
                     eventStatus:(nullable CPNowPlayingSportsEventStatus *)eventStatus API_AVAILABLE(ios(26.4));

/**
 The left team information.
 */
@property (nonatomic, strong, readonly) CPNowPlayingSportsTeam *leftTeam API_AVAILABLE(ios(26.4));

/**
 The right team information.
 */
@property (nonatomic, strong, readonly) CPNowPlayingSportsTeam *rightTeam API_AVAILABLE(ios(26.4));

/**
 The event status label.
 */
@property (nonatomic, strong, readonly, nullable) CPNowPlayingSportsEventStatus *eventStatus API_AVAILABLE(ios(26.4));

- (instancetype)init NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
