// Copyright © Apple Inc. All rights reserved.

#import <TargetConditionals.h>
#import <Foundation/Foundation.h>
#import <GameKit/GKDefines.h>

NS_CLASS_AVAILABLE(10_12, 10_0) __WATCHOS_AVAILABLE(3_0)
@interface GKBasePlayer : NSObject

@property(readonly, nullable, retain, NS_NONATOMIC_IOSONLY) NSString *playerID API_DEPRECATED("Use either the gamePlayerID or teamPlayerID property to identify a player.",ios(4.1,13.0),tvos(9.0,13.0),macos(10.8,10.15));

/// This player's name representation as displayed in the Game Center in-game UI. Use this when you need to display the player's name. The display name may be very long, so be sure to use appropriate string truncation API when drawing.
@property(readonly, nullable, NS_NONATOMIC_IOSONLY) NSString *displayName;

@end
