//
//  GKBasePlayer.h
//  Game Center
//
//  Copyright 2016-2022 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <GameKit/GKDefines.h>

NS_CLASS_AVAILABLE(10_12, 10_0) __WATCHOS_AVAILABLE(3_0)
@interface GKBasePlayer : NSObject

@property(readonly, nullable, retain, NS_NONATOMIC_IOSONLY) NSString *playerID API_DEPRECATED( "use the teamPlayerID property to identify a player",ios(4.1,13.0),tvos(9.0,13.0),macosx(10.8,10.15));

/// This player's name representation as displayed in the Game Center in-game UI. Use this when you need to display the player's name. The display name may be very long, so be sure to use appropriate string truncation API when drawing.
@property(readonly, nullable, NS_NONATOMIC_IOSONLY) NSString *displayName;

@end
