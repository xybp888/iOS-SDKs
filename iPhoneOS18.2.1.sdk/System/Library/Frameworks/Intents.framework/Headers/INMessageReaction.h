//
//  INMessageReaction.h
//  Intents
//
//  Copyright (c) 2016-2024 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

#import <Intents/INMessageReactionType.h>

NS_ASSUME_NONNULL_BEGIN

/// An object that describes a reaction to a message.
API_AVAILABLE(ios(18.0), macos(15.0), watchos(11.0))
API_UNAVAILABLE(tvos)
@interface INMessageReaction : NSObject <NSCopying, NSSecureCoding>

/// Creates an INMessageReaction
///
/// - Parameters:
///   - reactionType: The type of message reaction.
///   - reactionDescription: Text that describes the reaction.
///   - emoji: The single emoji character used for an emoji reaction.
- (instancetype)initWithReactionType:(INMessageReactionType)reactionType
                 reactionDescription:(nullable NSString *)reactionDescription
                               emoji:(nullable NSString *)emoji NS_DESIGNATED_INITIALIZER;

/// The type of reaction.
@property (readonly, assign, NS_NONATOMIC_IOSONLY) INMessageReactionType reactionType;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSString *reactionDescription;

/// The emoji used to react.
@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSString *emoji;

@end

NS_ASSUME_NONNULL_END
