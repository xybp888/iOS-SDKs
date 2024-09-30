/*
    Copyright (C) 2024 Apple Inc. All Rights Reserved.
*/

#pragma once

#ifndef ACCESSORY_SETUP_KIT_INDIRECT_INCLUDES
#error "Please #import <AccessorySetupKit/AccessorySetupKit.h> instead of this file directly."
#endif

#import <AccessorySetupKit/ASCommon.h>
#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@class CBUUID;

//---------------------------------------------------------------------------------------------------------------------------
/*!    @brief        Discovery Range
*/
typedef NS_ENUM( NSInteger, ASDiscoveryDescriptorRange )
{
    ASDiscoveryDescriptorRangeDefault            = 0,
    ASDiscoveryDescriptorRangeImmediate          = 10,
} NS_SWIFT_NAME(ASDiscoveryDescriptor.Range);

AS_EXTERN
API_AVAILABLE( ios( 18.0 ) ) API_UNAVAILABLE(macos, macCatalyst, watchos, tvos, visionos)
NS_SWIFT_SENDABLE
@interface ASDiscoveryDescriptor : NSObject

/*!
 * @property supportedOptions
 * @discussion Accessory capabilities.
 */
@property (readwrite, assign, nonatomic) ASAccessorySupportOptions supportedOptions;

/*!
 * @property companyIdentifier
 * @discussion Accessory's Bluetooth 16-bit Company Identifier.
 */
@property (readwrite, assign, nonatomic) ASBluetoothCompanyIdentifier bluetoothCompanyIdentifier;

/*!
 * @property manufacturerDataBlob
 * @discussion Accessory's Bluetooth Manufacturer Data Blob.
 */
@property (readwrite, copy, nullable, nonatomic) NSData *bluetoothManufacturerDataBlob;

/*!
 * @property manufacturerDataBlobMask
 * @discussion Accessory's Bluetooth Manufacturer Data Mask.
 */
@property (readwrite, copy, nullable, nonatomic) NSData *bluetoothManufacturerDataMask;

/*!
 * @property bluetoothNameSubstring
 * @discussion Accessory's over-the-air Bluetooth name sub-string.
 */
@property (readwrite, copy, nullable, nonatomic) NSString *bluetoothNameSubstring;

/*!
 * @property bluetoothRange
 * @discussion Discover accessory within specific bluetooth range.
 */
@property (readwrite, assign, nonatomic) ASDiscoveryDescriptorRange bluetoothRange;

/*!
 * @property serviceDataBlob
 * @discussion Accessory's Bluetooth Service Data Blob.
 */
@property (readwrite, copy, nullable, nonatomic) NSData *bluetoothServiceDataBlob;

/*!
 * @property serviceDataBlobMask
 * @discussion Accessory's Bluetooth Service Data Mask.
 */
@property (readwrite, copy, nullable, nonatomic) NSData *bluetoothServiceDataMask;

/*!
 * @property serviceUUID
 * @discussion Accessory's Bluetooth Service UUID.
 */
@property (readwrite, copy, nullable, nonatomic) CBUUID *bluetoothServiceUUID;
/*!
 * @property SSID
 * @discussion SSID of the Wi-Fi Network.
 */
@property (readwrite, copy, nullable, nonatomic) NSString *SSID;

/*!
 * @property SSIDPrefix
 * @discussion Prefix string of SSID of the Wi-Fi Network.
 */
@property (readwrite, copy, nullable, nonatomic) NSString *SSIDPrefix;

@end

NS_ASSUME_NONNULL_END
