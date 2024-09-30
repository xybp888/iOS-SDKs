/*
    Copyright (C) 2024 Apple Inc. All Rights Reserved.
*/

#pragma once

#ifndef ACCESSORY_SETUP_KIT_INDIRECT_INCLUDES
#error "Please #import <AccessorySetupKit/AccessorySetupKit.h> instead of this file directly."
#endif

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@class ASDiscoveryDescriptor;
@class ASPickerDisplayItem;

//---------------------------------------------------------------------------------------------------------------------------
/*!    @brief        Authorized Accessory State
*/
typedef NS_ENUM( NSInteger, ASAccessoryState )
{
    ASAccessoryStateUnauthorized            = 0,    // Invalid or Unauthorized Accessory.
    ASAccessoryStateAwaitingAuthorization   = 10,   // Selected by user but pending for full authorization.
    ASAccessoryStateAuthorized              = 20,   // Authorized and available Accessory.
} NS_SWIFT_NAME(ASAccessory.AccessoryState);

//---------------------------------------------------------------------------------------------------------------------------
/*!    @brief        Accessory Rename Options
*/
typedef NS_OPTIONS( NSUInteger, ASAccessoryRenameOptions )
{
    ASAccessoryRenameSSID NS_SWIFT_NAME(ssid)       = ( 1U << 0 ),    /// Change Accessory's SSID along with display name.
} NS_SWIFT_NAME(ASAccessory.RenameOptions);

//---------------------------------------------------------------------------------------------------------------------------
/*!    @brief        Accessory Support Options
*/
typedef NS_OPTIONS( NSUInteger, ASAccessorySupportOptions )
{
    ASAccessorySupportBluetoothPairingLE             = ( 1U << 1 ),  // Accessory supports Bluetooth Low Energy pairing.
    ASAccessorySupportBluetoothTransportBridging     = ( 1U << 2 ),  // Accessory supports bring up of classic transport profiles when low energy transport for peripheral is connected.
} NS_SWIFT_NAME(ASAccessory.SupportOptions);

AS_EXTERN
API_AVAILABLE( ios( 18.0 ) ) API_UNAVAILABLE(macos, macCatalyst, watchos, tvos, visionos)
NS_SWIFT_SENDABLE
@interface ASAccessory : NSObject

/*!
    @property    state
    @abstract    State of the accessory.
*/
@property (readonly, assign, nonatomic) ASAccessoryState state;

/*!
    @property    bluetoothIdentifier
    @abstract    A bluetooth identifier which clients can use to establish a connection to a bluetooth device.
*/
@property (readonly, copy, nullable, nonatomic) NSUUID *bluetoothIdentifier;

/*!
    @property    bluetoothTransportBridgingIdentifier
    @abstract    Identifier for bridging classic transport profiles.
*/
@property (readonly, copy, nullable, nonatomic) NSData *bluetoothTransportBridgingIdentifier;

/*!
    @property    name
    @abstract    String which clients can use to display name of the accessory.
*/
@property (readonly, copy, nonatomic) NSString *displayName;

/*!
    @property    SSID
    @abstract    Identifier which clients can use to connect to accessory's WiFi network.
*/
@property (readonly, copy, nullable, nonatomic) NSString *SSID;

/*!
    @property    descriptor
    @abstract    Descriptor when accessory was discovered.
*/
@property (readonly, copy, nonatomic) ASDiscoveryDescriptor *descriptor;

@end

NS_ASSUME_NONNULL_END
