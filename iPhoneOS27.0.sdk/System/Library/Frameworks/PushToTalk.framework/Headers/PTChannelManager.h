//
//  PTChannelProvider.h
//  PushToTalk
//
//  Copyright © 2022 Apple. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <PushToTalk/PTBase.h>
#import <PushToTalk/PTChannelDescriptor.h>
#import <PushToTalk/PTChannelManagerDelegate.h>
#import <PushToTalk/PTChannelRestorationDelegate.h>
#import <PushToTalk/PTParticipant.h>

typedef NS_ENUM(NSInteger, PTServiceStatus) {
    /// The service is available for use and ready for use by the client.
    PTServiceStatusReady,
    /// The client is attempting to establish a connection to the service.
    PTServiceStatusConnecting,
    /// The service has become unavailable and availability needs to be re-established once conditions have changed.
    PTServiceStatusUnavailable,
} API_AVAILABLE(ios(16.0)) API_UNAVAILABLE(macos, macCatalyst, tvos, watchos);

typedef NS_ENUM(NSInteger, PTTransmissionMode) {
    /// Users can transmit and receive simultaneously.
    PTTransmissionModeFullDuplex,
    /// Users can transmit and receive but not simultaneously. This is the default value.
    PTTransmissionModeHalfDuplex,
    /// User is able to receive only, transmit is not permitted.
    PTTransmissionModeListenOnly,
} API_AVAILABLE(ios(16.0)) API_UNAVAILABLE(macos, macCatalyst, tvos, watchos);

NS_ASSUME_NONNULL_BEGIN

NS_SWIFT_SENDABLE
PT_EXTERN API_AVAILABLE(ios(16.0)) API_UNAVAILABLE(macos, macCatalyst, tvos, watchos)
@interface PTChannelManager : NSObject

/// You must instantiate a channel manager upon launching your app, otherwise the system will tear down channels and their ability to receive pushes. By providing a restoration delegate, you can decide whether to rejoin or leave any previously active channels that the system knows about. Once the channel restoration process is completed, you will be given the PTChannelManager instance.
+ (void)channelManagerWithDelegate:(id <PTChannelManagerDelegate>)delegate restorationDelegate:(id <PTChannelRestorationDelegate>)restorationDelegate completionHandler:(void(^)(PTChannelManager * _Nullable manager, NSError *_Nullable error))completionHandler NS_SWIFT_NAME(channelManager(delegate:restorationDelegate:completionHandler:));

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

/// Only one channel can be active at a time -- this is the channel that will handle user events
/// This being nonnull reflects whether the user can see this channel is active in the user interface
/// The ephemeral push token is only usable when this is nonnull.
@property (nonatomic, strong, nullable, readonly) NSUUID *activeChannelUUID;

/// You may only join a channel in the foreground. If successful, you will receive the delegate callback channelManager:didJoinChannelWithUUID:reason: with reason PTChannelJoinReasonProgrammaticRequest. Otherwise, the delegate callback channelManager:failedToJoinChannelWithUUID:error: will be invoked if implemented.
- (void)requestJoinChannelWithUUID:(NSUUID *)channelUUID descriptor:(PTChannelDescriptor *)descriptor NS_SWIFT_NAME(requestJoinChannel(channelUUID:descriptor:));

/// If successful, you will receive the delegate callback channelManager:channelUUID:didBeginTransmittingFromSource: with PTChannelTransmitRequestSourceProgrammaticRequest. Otherwise, the delegate callback channelManager:failedToBeginTransmittingInChannelWithUUID:error: will be invoked if implemented.
- (void)requestBeginTransmittingWithChannelUUID:(NSUUID *)channelUUID NS_SWIFT_NAME(requestBeginTransmitting(channelUUID:));

/// If successful, you will receive the delegate callback channelManager:channelUUID:didEndTransmittingFromSource with request source PTChannelTransmitRequestSourceProgrammaticRequest. Otherwise, the delegate callback channelManager:failedToStopTransmittingInChannelWithUUID:error: will be invoked if implemented. Generally, this should always succeed, unless you are not currently transmitting or are not joined to a channel.
- (void)stopTransmittingWithChannelUUID:(NSUUID *)channelUUID NS_SWIFT_NAME(stopTransmitting(channelUUID:));

/// If successful, you will receive the delegate callback channelManager:channelUUID:didLeaveChannelWithUUID:reason: with reason PTChannelLeaveReasonProgrammaticRequest, Otherwise, the delegate callback channelManager:failedToLeaveChannelWithUUID:error: will be invoked if implemented. Generally, this should always succeed so long as you are already joined to a channel.
- (void)leaveChannelWithUUID:(NSUUID *)channelUUID NS_SWIFT_NAME(leaveChannel(channelUUID:));

/// Updates the channel descriptor
- (void)setChannelDescriptor:(PTChannelDescriptor *)channelDescriptor forChannelUUID:(NSUUID *)channelUUID completionHandler:(void (^_Nullable)(NSError * _Nullable error))completionHandler NS_SWIFT_NAME(setChannelDescriptor(_:channelUUID:completionHandler:));

/// When receiving incoming audio from a remote participant, set the participant to a nonnull value, which will update the system user interface and block transmitting. When the user has stopped speaking, set the participant to nil.
- (void)setActiveRemoteParticipant:(PTParticipant *_Nullable)participant forChannelUUID:(NSUUID *)channelUUID completionHandler:(void (^_Nullable)(NSError * _Nullable error))completionHandler NS_SWIFT_NAME(setActiveRemoteParticipant(_:channelUUID:completionHandler:));

/// The default value for service status is PTServiceStatusReady. If your underlying network connection is experiencing issues, set the appropriate service status. The service status will be reflected in the system user interface.
- (void)setServiceStatus:(PTServiceStatus)status forChannelUUID:(NSUUID *)channelUUID completionHandler:(void (^_Nullable)(NSError * _Nullable))completionHandler NS_SWIFT_NAME(setServiceStatus(_:channelUUID:completionHandler:));

/// The default value for transmission mode is PTTransmissionModeHalfDuplex. If your application support one of the other transmission modes set it using this function. The system user interface will be updated to reflect the transmission mode.
- (void)setTransmissionMode:(PTTransmissionMode)transmissionMode forChannelUUID:(NSUUID *)channelUUID completionHandler:(void (^_Nullable)(NSError * _Nullable))completionHandler NS_SWIFT_NAME(setTransmissionMode(_:channelUUID:completionHandler:));

/// The default channel behavior is to map supported accessory button events to begin/end transmission actions. If your application does not wish to map these button events to transmission actions you can disable them by setting the enabled value to false.
- (void)setAccessoryButtonEventsEnabled:(BOOL)enabled forChannelUUID:(NSUUID *)channelUUID completionHandler:(void (^_Nullable)(NSError * _Nullable))completionHandler API_AVAILABLE(ios(17.0)) API_UNAVAILABLE(macos, macCatalyst, tvos, watchos) NS_SWIFT_NAME(setAccessoryButtonEventsEnabled(_:channelUUID:completionHandler:));

@end

NS_ASSUME_NONNULL_END

