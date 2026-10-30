//  
//  GCSpatialAccessory.h
//  GameController
//
//  Copyright © 2025 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

#import <GameController/GCExtern.h>
#import <GameController/GCDevice.h>

@class GCDeviceType;
@class GCDeviceHaptics;
@protocol GCDevicePhysicalInput;

NS_ASSUME_NONNULL_BEGIN

/**
 Use these constants with NSNotificationCenter to listen to connection and disconnection events.
 
 Use GCSpatialAccessoryDidConnectNotification for observing connections of spatial accessories.
 Use GCSpatialAccessoryDidDisconnectNotification for observing disconnections of spatial accessories.
 
 Connections and disconnections of spatial accessories will also be reflected in the accessories array
 of the GCSpatialAccessory class.
 
 The 'object' property of the notification will contain the GCSpatialAccessory that was connected or disconnected.
 
 @see NSNotificationCenter
 @see GCSpatialAccessory.accessories
 */
GAMECONTROLLER_EXPORT NSString * const GCSpatialAccessoryDidConnectNotification API_AVAILABLE(visionos(27.0)) API_UNAVAILABLE(macos, ios, tvos);
GAMECONTROLLER_EXPORT NSString * const GCSpatialAccessoryDidDisconnectNotification API_AVAILABLE(visionos(27.0)) API_UNAVAILABLE(macos, ios, tvos);


API_AVAILABLE(visionos(27.0)) API_UNAVAILABLE(macos, ios, tvos)
@interface GCSpatialAccessory : NSObject <GCDevice>

/**
 *  Tests the conformance of the receiver to the provided device type.
 */
- (BOOL)conformsToDeviceType:(GCDeviceType *)type;

/**
 *  Gets the input profile for the device.
 */
@property (readonly, strong, nullable) id<GCDevicePhysicalInput> input;

/**
 *  Gets the haptics for the device, if supported.
 *
 *  Use this property to create CHHapticEngine instances according to your needs.
 *
 *  @note
 *  Haptics are a drain on the devices's battery, and can be distracting when
 *  used excessively.
 */
@property (readonly, strong, nullable) GCDeviceHaptics *haptics;

@end


@interface GCSpatialAccessory (Discovery)

/**
 Get the collection of spatial accessories currently connected to the system.
 
 @see GCSpatialAccessoryDidConnectNotification
 @see GCSpatialAccessoryDidDisconnectNotification
 */
@property (readonly, class) NSArray<GCSpatialAccessory*> *spatialAccessories;


@end

NS_ASSUME_NONNULL_END
