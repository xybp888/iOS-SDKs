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
    /// An option to change an accessory's SSID along with its display name.
    ASAccessoryRenameSSID NS_SWIFT_NAME(ssid)       = ( 1U << 0 ),
} NS_SWIFT_NAME(ASAccessory.RenameOptions);

//---------------------------------------------------------------------------------------------------------------------------
/*!    @brief        Accessory Support Options
*/
typedef NS_OPTIONS( NSUInteger, ASAccessorySupportOptions )
{
    /// The accessory supports Bluetooth Low Energy pairing.
    ASAccessorySupportBluetoothPairingLE             = ( 1U << 1 ),  // Accessory supports Bluetooth Low Energy pairing.
    /// The accessory supports bridging to Bluetooth classic transport.
    ///
    /// This option indicates that when connecting with low energy transport, the accessory supports activating Bluetooth classic transport profiles.
    ASAccessorySupportBluetoothTransportBridging     = ( 1U << 2 ),  // Accessory supports bring up of classic transport profiles when low energy transport for peripheral is connected.
} NS_SWIFT_NAME(ASAccessory.SupportOptions);

AS_EXTERN
API_AVAILABLE( ios( 18.0 ) ) API_UNAVAILABLE(macos, macCatalyst, watchos, tvos, visionos)
NS_SWIFT_SENDABLE
@interface ASAccessory : NSObject

/// The current authorization state of the accessory.
@property (readonly, assign, nonatomic) ASAccessoryState state;

/// The accessory's unique Bluetooth identifier, if any.
///
/// Use this identifier to establish a connection to the accessory.
@property (readonly, copy, nullable, nonatomic) NSUUID *bluetoothIdentifier;

/// The accessory's Bluetooth identifier, if any, for use when bridging classic transport profiles.
@property (readonly, copy, nullable, nonatomic) NSData *bluetoothTransportBridgingIdentifier;

/// The accessory's name, suitable for displaying to someone using your app.
@property (readonly, copy, nonatomic) NSString *displayName;

/// The accessory's Wi-Fi SSID, if any.
///
/// Use this identifier to establish a connection to the accessory.
@property (readonly, copy, nullable, nonatomic) NSString *SSID;

/// The descriptor used to discover the accessory.
@property (readonly, copy, nonatomic) ASDiscoveryDescriptor *descriptor;

@end

NS_ASSUME_NONNULL_END
