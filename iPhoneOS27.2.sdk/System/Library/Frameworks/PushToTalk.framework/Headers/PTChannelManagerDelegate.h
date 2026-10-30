//
//  PTChannelManagerDelegate.h
//  PushToTalk
//
//  Copyright © 2022 Apple. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <PushToTalk/PTParticipant.h>
#import <PushToTalk/PTPushResult.h>

@class PTChannelManager;
@class AVAudioSession;

typedef NS_ENUM(NSInteger, PTChannelJoinReason) {
    /// The app joined via a programmatic call to requestJoinChannelWithUUID:descriptor: while in the foreground
    PTChannelJoinReasonDeveloperRequest = 0,
    
    /// Rejoined via channel restoration
    PTChannelJoinReasonChannelRestoration = 1,
} API_AVAILABLE(ios(16.0)) API_UNAVAILABLE(macos, macCatalyst, tvos, watchos);

typedef NS_ENUM(NSInteger, PTChannelLeaveReason) {
    PTChannelLeaveReasonUnknown = 0,
    
    /// User pressed the leave button in the system UI
    PTChannelLeaveReasonUserRequest = 1,
    
    /// The app made a call to leaveChannelWithUUID:
    PTChannelLeaveReasonDeveloperRequest = 2,
    
    /// For example, a new managed device restriction has come into effect
    PTChannelLeaveReasonSystemPolicy = 3,
} API_AVAILABLE(ios(16.0)) API_UNAVAILABLE(macos, macCatalyst, tvos, watchos);

typedef NS_ENUM(NSInteger, PTChannelTransmitRequestSource) {
    PTChannelTransmitRequestSourceUnknown = 0,
    
    /// User pressed the transmit button in the on-screen system user interface
    PTChannelTransmitRequestSourceUserRequest = 1,
    
    /// The app made a call to requestBeginTransmittingWithChannelUUID:
    PTChannelTransmitRequestSourceDeveloperRequest = 2,
    
    /// User pressed a button on a hands-free device such as a wired headset
    PTChannelTransmitRequestSourceHandsfreeButton = 3,
} API_AVAILABLE(ios(16.0)) API_UNAVAILABLE(macos, macCatalyst, tvos, watchos);

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(16.0)) API_UNAVAILABLE(macos, macCatalyst, tvos, watchos)
@protocol PTChannelManagerDelegate <NSObject>

/// This method is called when your channel becomes active in the system user interface
- (void)channelManager:(PTChannelManager *)channelManager didJoinChannelWithUUID:(NSUUID *)channelUUID reason:(PTChannelJoinReason)reason NS_SWIFT_NAME(channelManager(_:didJoinChannel:reason:));

/// This method is called once your channel is ended
- (void)channelManager:(PTChannelManager *)channelManager didLeaveChannelWithUUID:(NSUUID *)channelUUID reason:(PTChannelLeaveReason)reason NS_SWIFT_NAME(channelManager(_:didLeaveChannel:reason:));

/// This method is called when the user begins pressing the Talk button in the system user interface,  when a programmatic transmit start request succeeds, or transmitting began due to a hands-free accessory button press.
- (void)channelManager:(PTChannelManager *)channelManager channelUUID:(NSUUID *)channelUUID didBeginTransmittingFromSource:(PTChannelTransmitRequestSource)source;

/// This method is called when the user stops pressing the Talk button in the system user interface,  when a programmatic transmit stop request succeeds, or transmitting ends due to a hands-free accessory button press.
- (void)channelManager:(PTChannelManager *)channelManager channelUUID:(NSUUID *)channelUUID didEndTransmittingFromSource:(PTChannelTransmitRequestSource)source;

/// This method is called when your channel manager receives a push token after joining a channel. This token is ephemeral and is only valid while joined to the channel; it is invalidated when the user or a push request leave the channel. When sending pushes, the apns-topic header field must use your app’s bundle ID with .voip-ptt appended to the end
- (void)channelManager:(PTChannelManager *)channelManager receivedEphemeralPushToken:(NSData *)pushToken;

/// This method is called for each incoming push. You must instantiate and return nonnil PTPushResult for each incoming push. The system will fulfill the action specified by the PTPushResult on your behalf automatically.
- (PTPushResult *)incomingPushResultForChannelManager:(PTChannelManager *)channelManager channelUUID:(NSUUID *)channelUUID pushPayload:(NSDictionary<NSString *, id> *)pushPayload NS_SWIFT_NAME(incomingPushResult(channelManager:channelUUID:pushPayload:));

- (void)channelManager:(PTChannelManager *)channelManager didActivateAudioSession:(AVAudioSession *)audioSession;

- (void)channelManager:(PTChannelManager *)channelManager didDeactivateAudioSession:(AVAudioSession *)audioSession;

@optional

- (void)channelManager:(PTChannelManager *)channelManager failedToJoinChannelWithUUID:(NSUUID *)channelUUID error:(NSError *)error NS_SWIFT_NAME(channelManager(_:failedToJoinChannel:error:));

- (void)channelManager:(PTChannelManager *)channelManager failedToLeaveChannelWithUUID:(NSUUID *)channelUUID error:(NSError *)error NS_SWIFT_NAME(channelManager(_:failedToLeaveChannel:error:));

- (void)channelManager:(PTChannelManager *)channelManager failedToBeginTransmittingInChannelWithUUID:(NSUUID *)channelUUID error:(NSError *)error NS_SWIFT_NAME(channelManager(_:failedToBeginTransmittingInChannel:error:));

- (void)channelManager:(PTChannelManager *)channelManager failedToStopTransmittingInChannelWithUUID:(NSUUID *)channelUUID error:(NSError *)error NS_SWIFT_NAME(channelManager(_:failedToStopTransmittingInChannel:error:));

/// This method is called for each incoming service update push. Use this method to extract service update data from the notification's payload and to
/// perform the relevant task for that data. When you finish the task, execute the provided `completion` handler block to let PushToTalk know you are finished.
///
/// Service Update push notifications that are sent with high priority (priority=10) are subject to a budget of six per hour. Use the `remainingHighPriorityBudget`
/// value to monitor the number of remaining high priority push notifications available to your app. Low-priority push notifications (priority<=5) are not subject
/// to a budget limit and should be used whenever possible.
- (void)incomingServiceUpdatePushForChannelManager:(PTChannelManager *)channelManager channelUUID:(NSUUID *)channelUUID pushPayload:(NSDictionary<NSString *, id> *)pushPayload isHighPriority:(BOOL)isHighPriority remainingHighPriorityBudget:(NSInteger)remainingHighPriorityBudget withCompletionHandler:(void (^)(void))completion API_AVAILABLE(ios(17.2)) API_UNAVAILABLE(macos, macCatalyst, tvos, watchos) NS_SWIFT_NAME(incomingServiceUpdatePush(channelManager:channelUUID:pushPayload:isHighPriority:remainingHighPriorityBudget:completion:));

@end

NS_ASSUME_NONNULL_END

