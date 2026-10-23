//
//  PTErrors.h
//  PushToTalk
//
//  Copyright © 2022 Apple. All rights reserved.
//


#import <PushToTalk/PTBase.h>

PT_EXTERN NSErrorDomain const PTInstantiationErrorDomain API_AVAILABLE(ios(16.0)) API_UNAVAILABLE(macos, macCatalyst, tvos, watchos);
PT_EXTERN NSErrorDomain const PTChannelErrorDomain API_AVAILABLE(ios(16.0)) API_UNAVAILABLE(macos, macCatalyst, tvos, watchos);

typedef NS_ERROR_ENUM(PTInstantiationErrorDomain, PTInstantiationError) {
    PTInstantiationErrorUnknown = 0,
    
    /// The PushToTalk API is not available on the simulator or macOS devices
    PTInstantiationErrorInvalidPlatform = 1,
    
    /// App is lacking the push-to-talk UIBackgroundMode
    PTInstantiationErrorMissingBackgroundMode = 2,
    
    /// App is lacking apns-environment entitlement (Push Notifications Capability)
    PTInstantiationErrorMissingPushServerEnvironment = 3,
    
    /// App is lacking the com.apple.developer.push-to-talk entitlement
    PTInstantiationErrorMissingEntitlement = 4,
    
    /// There is already an in-flight instantiation request
    PTInstantiationErrorInstantiationAlreadyInProgress = 5,
} API_AVAILABLE(ios(16.0)) API_UNAVAILABLE(macos, macCatalyst, tvos, watchos);

typedef NS_ERROR_ENUM(PTChannelErrorDomain, PTChannelError) {
    PTChannelErrorUnknown = 0,
    
    /// The action cannot be performed because there is no active channel with the supplied UUID
    PTChannelErrorChannelNotFound = 1,
    
    /// There is a maximum of one active channel at a time, for the whole device
    PTChannelErrorChannelLimitReached = 2,
    
    /// A traditional call is ongoing, preventing the channel action
    PTChannelErrorCallActive = 3,
    
    /// Setting a nonnil active participant is not posible while transmitting is ongoing.
    PTChannelErrorTransmissionInProgress = 4,
    
    /// Error for trying to end a transmission when no transmission is even started
    PTChannelErrorTransmissionNotFound = 5,
    
    /// Error for trying to join a channel or begin transmitting while app is not foreground
    PTChannelErrorAppNotForeground = 6,
    
    /// A device management policy or profile forbids joining the channel
    PTChannelErrorDeviceManagementRestriction = 7,
    
    /// A Screen Time restriction prevented the action
    PTChannelErrorScreenTimeRestriction = 8,

    /// A transmission is not allowed due to the current transmission mode of the channel
    PTChannelErrorTransmissionNotAllowed = 9,
} API_AVAILABLE(ios(16.0)) API_UNAVAILABLE(macos, macCatalyst, tvos, watchos);

