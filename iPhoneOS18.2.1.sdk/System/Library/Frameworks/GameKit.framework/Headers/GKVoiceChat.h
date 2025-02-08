// Copyright © Apple Inc. All rights reserved.

#import <Foundation/Foundation.h>

typedef NS_ENUM(NSInteger, GKVoiceChatPlayerState) {
    GKVoiceChatPlayerConnected,
    GKVoiceChatPlayerDisconnected,
    GKVoiceChatPlayerSpeaking,
    GKVoiceChatPlayerSilent,
    GKVoiceChatPlayerConnecting
} API_DEPRECATED("No longer supported", ios(4.1, 18.0), macos(10.8, 15.0), tvos(9.0, 18.0), visionos(1.0, 2.0)) __WATCHOS_PROHIBITED;
@class GKPlayer;

NS_ASSUME_NONNULL_BEGIN
/// GKVoiceChat represents an instance of a named voice communications channel
API_DEPRECATED("No longer supported", ios(4.1, 18.0), macos(10.8, 15.0), tvos(9.0, 18.0), visionos(1.0, 2.0)) __WATCHOS_PROHIBITED
@interface GKVoiceChat : NSObject

- (void)start;  /// start receiving audio from the chat
- (void)stop;   /// stop receiving audio from the chat

- (void)setPlayer:(GKPlayer *)player muted:(BOOL)isMuted NS_AVAILABLE(10_10, 8_0);

@property(copy, NS_NONATOMIC_IOSONLY) void(^playerVoiceChatStateDidChangeHandler)(GKPlayer *player, GKVoiceChatPlayerState state) NS_AVAILABLE(10_10, 8_0);

@property(readonly, copy, NS_NONATOMIC_IOSONLY) NSString *name;  // name the chat was created with
@property(assign, getter=isActive, NS_NONATOMIC_IOSONLY)    BOOL active; // make this session active and route the microphone
@property(assign, NS_NONATOMIC_IOSONLY) float volume; // default 1.0 (max is 1.0, min is 0.0)

@property(readonly, NS_NONATOMIC_IOSONLY) NSArray<GKPlayer *> *players NS_AVAILABLE(10_10, 8_0); // array of GKPlayer *

+ (BOOL)isVoIPAllowed;

@end

__WATCHOS_PROHIBITED
@interface GKVoiceChat (Deprecated)
@property(copy, NS_NONATOMIC_IOSONLY) void(^playerStateUpdateHandler)(NSString *playerID, GKVoiceChatPlayerState state) API_DEPRECATED_WITH_REPLACEMENT("-setPlayerVoiceChatStateDidChangeHandler:", ios(4.1,8.0), macos(10.8,10.10)) __TVOS_UNAVAILABLE;
@end

__WATCHOS_PROHIBITED
@interface GKVoiceChat (Obsoleted)
/*** This property is obsolete. ***/
@property(readonly, nullable, NS_NONATOMIC_IOSONLY) NSArray<NSString *> *playerIDs API_DEPRECATED_WITH_REPLACEMENT("-players:", ios(5.0,8.0), macos(10.8,10.10)) __TVOS_UNAVAILABLE;

/*** This method is obsolete. It will never be invoked and its implementation does nothing***/
- (void)setMute:(BOOL)isMuted forPlayer:(NSString *)playerID API_DEPRECATED_WITH_REPLACEMENT("-setPlayer:muted:", ios(5.0,8.0), macos(10.8,10.10)) __TVOS_UNAVAILABLE;
@end
NS_ASSUME_NONNULL_END
