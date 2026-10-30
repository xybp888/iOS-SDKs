//
//  PTPushResult.h
//  PushToTalk
//
//  Copyright © 2022 Apple. All rights reserved.
//


#import <PushToTalk/PTParticipant.h>

NS_ASSUME_NONNULL_BEGIN

NS_SWIFT_SENDABLE // Immutable with no mutable subclasses
PT_EXTERN API_AVAILABLE(ios(16.0)) API_UNAVAILABLE(macos, macCatalyst, tvos, watchos)
__attribute__((objc_subclassing_restricted))
@interface PTPushResult : NSObject

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

/// Use this if the push is a result of the user leaving the channel
@property(class, nonatomic, readonly) PTPushResult *leaveChannelPushResult NS_SWIFT_NAME(leaveChannel);

/// Use this to report the active remote participant that started speaking
+ (PTPushResult *)pushResultForActiveRemoteParticipant:(PTParticipant *)participant NS_SWIFT_NAME(activeRemoteParticipant(_:));

@end

NS_ASSUME_NONNULL_END

