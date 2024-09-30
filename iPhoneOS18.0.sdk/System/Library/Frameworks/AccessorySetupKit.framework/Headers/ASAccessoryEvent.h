/*
    Copyright (C) 2024 Apple Inc. All Rights Reserved.
*/

#ifndef ACCESSORY_SETUP_KIT_INDIRECT_INCLUDES
#error "Please #import <AccessorySetupKit/AccessorySetupKit.h> instead of this file directly."
#endif

#pragma once

#import <AccessorySetupKit/ASCommon.h>
#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

#ifdef __cplusplus
extern "C" {
#endif

@class ASAccessory;

//===========================================================================================================================
/// Type of event.
typedef NS_ENUM( NSInteger, ASAccessoryEventType )
{
    ASAccessoryEventTypeUnknown                     = 0,    // Unknown event. Placeholder for initializing event types.
    ASAccessoryEventTypeActivated                   = 10,   // [ASAccessoryEvent] Instance activate completed.
    ASAccessoryEventTypeInvalidated                 = 11,   // [ASAccessoryEvent] Instance invalidated.
    ASAccessoryEventTypeMigrationComplete           = 20,   // [ASAccessoryEvent] Accessories migration complete.
    ASAccessoryEventTypeAccessoryAdded              = 30,   // [ASAccessoryEvent] Accessory added.
    ASAccessoryEventTypeAccessoryRemoved            = 31,   // [ASAccessoryEvent] Accessory removed from system.
    ASAccessoryEventTypeAccessoryChanged            = 32,   // [ASAccessoryEvent] Accessory properties changed.
    ASAccessoryEventTypePickerDidPresent            = 40,   // [ASAccessoryEvent] Picker did present.
    ASAccessoryEventTypePickerDidDismiss            = 50,   // [ASAccessoryEvent] Picker did dismiss.
    ASAccessoryEventTypePickerSetupBridging         = 60,   // [ASAccessoryEvent] Picker started bridging with accessory.
    ASAccessoryEventTypePickerSetupFailed           = 70,   // [ASAccessoryEvent] Picker failed setup for accessory.
    ASAccessoryEventTypePickerSetupPairing          = 80,   // [ASAccessoryEvent] Picker started pairing with accessory.
    ASAccessoryEventTypePickerSetupRename           = 90,   // [ASAccessoryEvent] Picker started rename of accessory.
};

//===========================================================================================================================
/// Event for status and other updates.
AS_EXTERN
API_AVAILABLE( ios( 18.0 ) ) API_UNAVAILABLE(macos, macCatalyst, watchos, tvos, visionos)
@interface ASAccessoryEvent : NSObject

/// Type of event. Type may indicate the subclass of ASAccessoryEvent to provide additional properties.
@property (readonly, assign, nonatomic) ASAccessoryEventType eventType;

/// Accessory found, lost or changed.
@property (readonly, copy, nullable, nonatomic) ASAccessory *accessory;

/// Any error for event type.
@property (readonly, copy, nullable, nonatomic) NSError *error;

- (instancetype) init NS_UNAVAILABLE;
- (instancetype) new NS_UNAVAILABLE;

@end

#ifdef __cplusplus
}
#endif

NS_ASSUME_NONNULL_END
