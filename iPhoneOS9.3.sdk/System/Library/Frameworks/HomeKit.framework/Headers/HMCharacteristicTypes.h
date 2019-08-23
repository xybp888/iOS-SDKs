//  HMCharacteristicTypes.h
//  HomeKit
//
//  Copyright © 2015 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <HomeKit/HMDefines.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 * @brief This constant specifies that the characteristic supports notifications
 *        using the event connection established by the controller. The
 *        event connection provides unidirectional communication from the
 *        accessory to the controller.
 */
HM_EXTERN NSString * const HMCharacteristicPropertySupportsEventNotification NS_AVAILABLE_IOS(8_0) __WATCHOS_AVAILABLE(__WATCHOS_2_0);

/*!
 * @brief This constant specifies that the characteristic is readable.
 */
HM_EXTERN NSString * const HMCharacteristicPropertyReadable NS_AVAILABLE_IOS(8_0) __WATCHOS_AVAILABLE(__WATCHOS_2_0);

/*!
 * @brief This constant specifies that the characteristic is writable.
 */
HM_EXTERN NSString * const HMCharacteristicPropertyWritable NS_AVAILABLE_IOS(8_0) __WATCHOS_AVAILABLE(__WATCHOS_2_0);

/*!
 * @brief This constant specifies that the characteristic should be hidden from the user.
 */
HM_EXTERN NSString * const HMCharacteristicPropertyHidden NS_AVAILABLE_IOS(9_3) __WATCHOS_AVAILABLE(2.2);

/*!
 * @group Accessory Service Characteristic Types
 *
 * @brief These constants define the characteristic types supported by the HomeKit Accessory Profile for HomeKit based accessories.
 */

/*!
 * @brief Characteristic type for power state. The value of the characteristic is a boolean.
 */
HM_EXTERN NSString * const HMCharacteristicTypePowerState NS_AVAILABLE_IOS(8_0) __WATCHOS_AVAILABLE(__WATCHOS_2_0);

/*!
 * @brief Characteristic type for hue. The value of the characteristic is a float value in arc degrees.
 */
HM_EXTERN NSString * const HMCharacteristicTypeHue NS_AVAILABLE_IOS(8_0) __WATCHOS_AVAILABLE(__WATCHOS_2_0);

/*!
 * @brief Characteristic type for saturation. The value of the characteristic is a float value in percent.
 */
HM_EXTERN NSString * const HMCharacteristicTypeSaturation NS_AVAILABLE_IOS(8_0) __WATCHOS_AVAILABLE(__WATCHOS_2_0);

/*!
 * @brief Characteristic type for brightness. The value of the characteristic is an int value in percent.
 */
HM_EXTERN NSString * const HMCharacteristicTypeBrightness NS_AVAILABLE_IOS(8_0) __WATCHOS_AVAILABLE(__WATCHOS_2_0);

/*!
 * @brief Characteristic type for temperature units. The value of the characteristic is one of the values
 *        defined for HMCharacteristicValueTemperatureUnit.
 */
HM_EXTERN NSString * const HMCharacteristicTypeTemperatureUnits NS_AVAILABLE_IOS(8_0) __WATCHOS_AVAILABLE(__WATCHOS_2_0);

/*!
 * @brief Characteristic type for current temperature. The value of the characteristic is a float value in Celsius.
 */
HM_EXTERN NSString * const HMCharacteristicTypeCurrentTemperature NS_AVAILABLE_IOS(8_0) __WATCHOS_AVAILABLE(__WATCHOS_2_0);

/*!
 * @brief Characteristic type for target temperature. The value of the characteristic is a float value in Celsius.
 */
HM_EXTERN NSString * const HMCharacteristicTypeTargetTemperature NS_AVAILABLE_IOS(8_0) __WATCHOS_AVAILABLE(__WATCHOS_2_0);

/*!
 * @brief Characteristic type for heating/cooling mode. The value of the characteristic is one of the values
 *        defined for HMCharacteristicValueHeatingCooling and indicates the current heating/cooling mode.
 */
HM_EXTERN NSString * const HMCharacteristicTypeCurrentHeatingCooling NS_AVAILABLE_IOS(8_0) __WATCHOS_AVAILABLE(__WATCHOS_2_0);

/*!
 * @brief Characteristic type for target heating/cooling mode. The value of the characteristic is one of the values
 *        defined for HMCharacteristicValueHeatingCooling and indicates the target heating/cooling mode.
 */
HM_EXTERN NSString * const HMCharacteristicTypeTargetHeatingCooling NS_AVAILABLE_IOS(8_0) __WATCHOS_AVAILABLE(__WATCHOS_2_0);

/*!
 * @brief Characteristic type for cooling threshold temperature. The value of the characteristic is a float value in Celsius.
 */
HM_EXTERN NSString * const HMCharacteristicTypeCoolingThreshold NS_AVAILABLE_IOS(8_0) __WATCHOS_AVAILABLE(__WATCHOS_2_0);

/*!
 * @brief Characteristic type for heating threshold temperature. The value of the characteristic is a float value in Celsius.
 */
HM_EXTERN NSString * const HMCharacteristicTypeHeatingThreshold NS_AVAILABLE_IOS(8_0) __WATCHOS_AVAILABLE(__WATCHOS_2_0);

/*!
 * @brief Characteristic type for current relative humidity. The value of the characteristic is a float value in percent.
 */
HM_EXTERN NSString * const HMCharacteristicTypeCurrentRelativeHumidity NS_AVAILABLE_IOS(8_0) __WATCHOS_AVAILABLE(__WATCHOS_2_0);

/*!
 * @brief Characteristic type for target relative humidity. The value of the characteristic is a float value in percent.
 */
HM_EXTERN NSString * const HMCharacteristicTypeTargetRelativeHumidity NS_AVAILABLE_IOS(8_0) __WATCHOS_AVAILABLE(__WATCHOS_2_0);

/*!
 * @brief Characteristic type for current door state. The value of the characteristic is one of the values
 *        defined for HMCharacteristicValueDoorState and indicates the current door state.
 */
HM_EXTERN NSString * const HMCharacteristicTypeCurrentDoorState NS_AVAILABLE_IOS(8_0) __WATCHOS_AVAILABLE(__WATCHOS_2_0);

/*!
 * @brief Characteristic type for target door state. The value of the characteristic is one of the values
 *        defined for HMCharacteristicValueDoorState and indicates the target door state.
 */
HM_EXTERN NSString * const HMCharacteristicTypeTargetDoorState NS_AVAILABLE_IOS(8_0) __WATCHOS_AVAILABLE(__WATCHOS_2_0);

/*!
 * @brief Characteristic type for obstruction detected. The value of the characteristic is a boolean value.
 */
HM_EXTERN NSString * const HMCharacteristicTypeObstructionDetected NS_AVAILABLE_IOS(8_0) __WATCHOS_AVAILABLE(__WATCHOS_2_0);

/*!
 * @brief Characteristic type for name. The value of the characteristic is a string.
 */
HM_EXTERN NSString * const HMCharacteristicTypeName NS_AVAILABLE_IOS(8_0) __WATCHOS_AVAILABLE(__WATCHOS_2_0);

/*!
 * @brief Characteristic type for manufacturer. The value of the characteristic is a string.
 */
HM_EXTERN NSString * const HMCharacteristicTypeManufacturer NS_AVAILABLE_IOS(8_0) __WATCHOS_AVAILABLE(__WATCHOS_2_0);

/*!
 * @brief Characteristic type for model. The value of the characteristic is a string.
 */
HM_EXTERN NSString * const HMCharacteristicTypeModel NS_AVAILABLE_IOS(8_0) __WATCHOS_AVAILABLE(__WATCHOS_2_0);

/*!
 * @brief Characteristic type for serial number. The value of the characteristic is a string.
 */
HM_EXTERN NSString * const HMCharacteristicTypeSerialNumber NS_AVAILABLE_IOS(8_0) __WATCHOS_AVAILABLE(__WATCHOS_2_0);

/*!
 * @brief Characteristic type for identify. The characteristic is write-only that takes a boolean.
 */
HM_EXTERN NSString * const HMCharacteristicTypeIdentify NS_AVAILABLE_IOS(8_0) __WATCHOS_AVAILABLE(__WATCHOS_2_0);

/*!
 * @brief Characteristic type for rotation direction. The value of the characteristic is one of the values
 *        defined for HMCharacteristicValueRotationDirection and indicates the fan rotation direction.
 */
HM_EXTERN NSString * const HMCharacteristicTypeRotationDirection NS_AVAILABLE_IOS(8_0) __WATCHOS_AVAILABLE(__WATCHOS_2_0);

/*!
 * @brief Characteristic type for rotation speed. The value of the characteristic is a float representing
 *        the percentage of maximum speed.
 */
HM_EXTERN NSString * const HMCharacteristicTypeRotationSpeed NS_AVAILABLE_IOS(8_0) __WATCHOS_AVAILABLE(__WATCHOS_2_0);

/*!
 * @brief Characteristic type for outlet in use. The value of the characteristic is a boolean, which is true
 *        if the outlet is in use.
 */
HM_EXTERN NSString * const HMCharacteristicTypeOutletInUse NS_AVAILABLE_IOS(8_0) __WATCHOS_AVAILABLE(__WATCHOS_2_0);

/*!
 * @brief Characteristic type for version. The value of the characteristic is a string.
 */
HM_EXTERN NSString * const HMCharacteristicTypeVersion NS_AVAILABLE_IOS(8_0) __WATCHOS_AVAILABLE(__WATCHOS_2_0);

/*!
 * @brief Characteristic type for logs. The value of the characteristic is TLV8 data wrapped in an NSData.
 */
HM_EXTERN NSString * const HMCharacteristicTypeLogs NS_AVAILABLE_IOS(8_0) __WATCHOS_AVAILABLE(__WATCHOS_2_0);

/*!
 * @brief Characteristic type for audio feedback. The value of the characteristic is a boolean.
 */
HM_EXTERN NSString * const HMCharacteristicTypeAudioFeedback NS_AVAILABLE_IOS(8_0) __WATCHOS_AVAILABLE(__WATCHOS_2_0);

/*!
 * @brief Characteristic type for admin only access. The value of the characteristic is a boolean.
 */
HM_EXTERN NSString * const HMCharacteristicTypeAdminOnlyAccess NS_AVAILABLE_IOS(8_0) __WATCHOS_AVAILABLE(__WATCHOS_2_0);

/*!
 * @brief Characteristic type for Security System Alarm Type. The value of the characteristic is a uint8.
 *        indicating the type of alarm triggered by a security system service. This characteristic has a value
 *        of 1 when the alarm type is not known and a value of 0 indicates that the alarm conditions are cleared.
 */
HM_EXTERN NSString * const HMCharacteristicTypeSecuritySystemAlarmType NS_AVAILABLE_IOS(9_0) __WATCHOS_AVAILABLE(__WATCHOS_2_0);

/*!
 * @brief Characteristic type for motion detected. The value of the characteristic is a boolean.
 */
HM_EXTERN NSString * const HMCharacteristicTypeMotionDetected NS_AVAILABLE_IOS(8_0) __WATCHOS_AVAILABLE(__WATCHOS_2_0);

/*!
 * @brief Characteristic type for current lock mechanism state. The value of the characteristic is one of the values
 *        defined for HMCharacteristicValueLockMechanismState.
 */
HM_EXTERN NSString * const HMCharacteristicTypeCurrentLockMechanismState NS_AVAILABLE_IOS(8_0) __WATCHOS_AVAILABLE(__WATCHOS_2_0);

/*!
 * @brief Characteristic type for target lock mechanism state. The value of the characteristic is either
 *        HMCharacteristicValueLockMechanismStateUnsecured, or HMCharacteristicValueLockMechanismStateSecured,
 *        as defined by HMCharacteristicValueLockMechanismState.
 */
HM_EXTERN NSString * const HMCharacteristicTypeTargetLockMechanismState NS_AVAILABLE_IOS(8_0) __WATCHOS_AVAILABLE(__WATCHOS_2_0);

/*!
 * @brief Characteristic type for the last known action for a lock mechanism. The value of the characteristic is one of the values
 *        defined for HMCharacteristicValueLockMechanismLastKnownAction.
 */
HM_EXTERN NSString * const HMCharacteristicTypeLockMechanismLastKnownAction NS_AVAILABLE_IOS(8_0) __WATCHOS_AVAILABLE(__WATCHOS_2_0);

/*!
 * @brief Characteristic type for the control point for lock management. The characteristic is write-only that takes TLV8 data wrapped in an NSData.
 */
HM_EXTERN NSString * const HMCharacteristicTypeLockManagementControlPoint NS_AVAILABLE_IOS(8_0) __WATCHOS_AVAILABLE(__WATCHOS_2_0);

/*!
 * @brief Characteristic type for the auto secure timeout for lock management. The value of the characteristic is an unsigned 
          32-bit integer representing the number of seconds.
 */
HM_EXTERN NSString * const HMCharacteristicTypeLockManagementAutoSecureTimeout NS_AVAILABLE_IOS(8_0) __WATCHOS_AVAILABLE(__WATCHOS_2_0);

/*!
 * @brief Characteristic type for density of air-particulate matter. The value of the characteristic is
 *        in units of micrograms/m^2.
 */
HM_EXTERN NSString * const HMCharacteristicTypeAirParticulateDensity NS_AVAILABLE_IOS(9_0) __WATCHOS_AVAILABLE(__WATCHOS_2_0);

/*!
 * @brief Characteristic type for size of air-particulate matter. The value of the characteristic is
 *        one of the values defined for HMCharacteristicValueAirParticulateSize.
 */
HM_EXTERN NSString * const HMCharacteristicTypeAirParticulateSize NS_AVAILABLE_IOS(9_0) __WATCHOS_AVAILABLE(__WATCHOS_2_0);

/*!
 * @brief Characteristic type for air quality. The value of the characteristic is
 *        one of the values defined for HMCharacteristicValueAirQuality.
 */
HM_EXTERN NSString * const HMCharacteristicTypeAirQuality NS_AVAILABLE_IOS(9_0) __WATCHOS_AVAILABLE(__WATCHOS_2_0);

/*!
 * @brief Characteristic type for battery level. The value of the characteristic is an uint8
 *        value in percent.
 */
HM_EXTERN NSString * const HMCharacteristicTypeBatteryLevel NS_AVAILABLE_IOS(9_0) __WATCHOS_AVAILABLE(__WATCHOS_2_0);

/*!
 * @brief Characteristic type for carbon dioxide detected. The value of the characteristic is a uint8 value.
 *        A value of 0 indicates carbon dioxide levels are normal.
 */
HM_EXTERN NSString * const HMCharacteristicTypeCarbonDioxideDetected NS_AVAILABLE_IOS(9_0) __WATCHOS_AVAILABLE(__WATCHOS_2_0);

/*!
 * @brief Characteristic type for carbon dioxide level.
 *        The value of the characteristic is a float value in units of ppm.
 */
HM_EXTERN NSString * const HMCharacteristicTypeCarbonDioxideLevel NS_AVAILABLE_IOS(9_0) __WATCHOS_AVAILABLE(__WATCHOS_2_0);

/*!
 * @brief Characteristic type for carbon dioxide peak level.
 *        The value of the characteristic is a float value in units of ppm.
 */
HM_EXTERN NSString * const HMCharacteristicTypeCarbonDioxidePeakLevel NS_AVAILABLE_IOS(9_0) __WATCHOS_AVAILABLE(__WATCHOS_2_0);

/*!
 * @brief Characteristic type for carbon monoxide detected. The value of the characteristic is a uint8 value.
 *        A value of 0 indicates carbon monoxide levels are normal.
 */
HM_EXTERN NSString * const HMCharacteristicTypeCarbonMonoxideDetected NS_AVAILABLE_IOS(9_0) __WATCHOS_AVAILABLE(__WATCHOS_2_0);

/*!
 * @brief Characteristic type for carbon monoxide level.
 *        The value of the characteristic is a float value in units of ppm.
 */
HM_EXTERN NSString * const HMCharacteristicTypeCarbonMonoxideLevel NS_AVAILABLE_IOS(9_0) __WATCHOS_AVAILABLE(__WATCHOS_2_0);

/*!
 * @brief Characteristic type for carbon monoxide peak level.
 *        The value of the characteristic is a float value in units of ppm.
 */
HM_EXTERN NSString * const HMCharacteristicTypeCarbonMonoxidePeakLevel NS_AVAILABLE_IOS(9_0) __WATCHOS_AVAILABLE(__WATCHOS_2_0);

/*!
 * @brief Characteristic type for Charging state. The value of the characteristic is a uint8.
 *        A value of 1 indicates charging is in progress.
 */
HM_EXTERN NSString * const HMCharacteristicTypeChargingState NS_AVAILABLE_IOS(9_0) __WATCHOS_AVAILABLE(__WATCHOS_2_0);

/*!
 * @brief Characteristic type for Contact sensor state. The value of the characteristic is a uint8 value.
 *        A value of 0 indicates that contact is detected; a value of 1 indicates no contact is detected.
 */
HM_EXTERN NSString * const HMCharacteristicTypeContactState NS_AVAILABLE_IOS(9_0) __WATCHOS_AVAILABLE(__WATCHOS_2_0);

/*!
 * @brief Characteristic type for current horizontal tilt angle. The value is a float representing the angle in arc degrees.
 */
HM_EXTERN NSString * const HMCharacteristicTypeCurrentHorizontalTilt NS_AVAILABLE_IOS(9_0) __WATCHOS_AVAILABLE(__WATCHOS_2_0);

/*!
 * @brief Characteristic type for current light level. The value of the characteristic in units of lux.
 */
HM_EXTERN NSString * const HMCharacteristicTypeCurrentLightLevel NS_AVAILABLE_IOS(9_0) __WATCHOS_AVAILABLE(__WATCHOS_2_0);

/*!
 * @brief Characteristic type for current position of a door/window. The value of the characteristic is an
 *        uint8 value in percent.
 */
HM_EXTERN NSString * const HMCharacteristicTypeCurrentPosition NS_AVAILABLE_IOS(9_0) __WATCHOS_AVAILABLE(__WATCHOS_2_0);

/*!
 * @brief Characteristic type for current security system state. The value of the characteristic is one of
 *        the values defined for HMCharacteristicValueCurrentSecuritySystemState.
 */
HM_EXTERN NSString * const HMCharacteristicTypeCurrentSecuritySystemState NS_AVAILABLE_IOS(9_0) __WATCHOS_AVAILABLE(__WATCHOS_2_0);

/*!
 * @brief Characteristic type for current vertical tilt angle. The value is a float representing the angle in arc degrees.
 */
HM_EXTERN NSString * const HMCharacteristicTypeCurrentVerticalTilt NS_AVAILABLE_IOS(9_0) __WATCHOS_AVAILABLE(__WATCHOS_2_0);

/*!
 * @brief Characteristic type for firmware version. The value of the characteristic is a string value
 *        describing the firmware version of the accessory.
 */
HM_EXTERN NSString * const HMCharacteristicTypeFirmwareVersion NS_AVAILABLE_IOS(9_0) __WATCHOS_AVAILABLE(__WATCHOS_2_0);

/*!
 * @brief Characteristic type for hardware version. The value of the characteristic is a string value
 *        describing the hardware version of the accessory.
 */
HM_EXTERN NSString * const HMCharacteristicTypeHardwareVersion NS_AVAILABLE_IOS(9_0) __WATCHOS_AVAILABLE(__WATCHOS_2_0);

/*!
 * @brief Characteristic type for Hold Position. The value of the characteristic is a boolean
 *        indicating that the current position should be held/maintained.
 */
HM_EXTERN NSString * const HMCharacteristicTypeHoldPosition NS_AVAILABLE_IOS(9_0) __WATCHOS_AVAILABLE(__WATCHOS_2_0);

/*!
 * @brief Characteristic type for programmable switch input event. The value of the characteristic is an int
 *        that can change based on the type of programmable switch. For a binary programmable switch, a value of 0
 *        indicates OFF (and 1 indicates ON). For a slider programmable switch, the value indicates the level.
 */
HM_EXTERN NSString * const HMCharacteristicTypeInputEvent NS_AVAILABLE_IOS(9_0) __WATCHOS_AVAILABLE(__WATCHOS_2_0);

/*!
 * @brief Characteristic type for leak detected. The value of the characteristic is a uint8 value.
 *        A value of 0 indicates no leak is detected; a value of 1 indicates that a leak is detected.
 */
HM_EXTERN NSString * const HMCharacteristicTypeLeakDetected NS_AVAILABLE_IOS(9_0) __WATCHOS_AVAILABLE(__WATCHOS_2_0);

/*!
 * @brief Characteristic type for Occupancy Detected. The value of the characteristic is a uint8 value.
 *        A value of 0 indicates no occupancy is detected; a value of 1 indicates that occupancy is detected.
 */
HM_EXTERN NSString * const HMCharacteristicTypeOccupancyDetected NS_AVAILABLE_IOS(9_0) __WATCHOS_AVAILABLE(__WATCHOS_2_0);

/*!
 * @brief Characteristic type for programmable switch output state. This value is to be used for presentation
 *        purposes. For a binary programmable switch, a value of 1 can be used to present a state of ON.
 */
HM_EXTERN NSString * const HMCharacteristicTypeOutputState NS_AVAILABLE_IOS(9_0) __WATCHOS_AVAILABLE(__WATCHOS_2_0);

/*!
 * @brief Characteristic type for Position state. The value of the characteristic is one of the
 *        one of the values defined for HMCharacteristicValuePositionState.
 */
HM_EXTERN NSString * const HMCharacteristicTypePositionState NS_AVAILABLE_IOS(9_0) __WATCHOS_AVAILABLE(__WATCHOS_2_0);

/*!
 * @brief Characteristic type for Smoke Detected. The value of the characteristic is a uint8 value.
 *        A value of 0 indicates no leak is detected; a value of 1 indicates that a leak is detected.
 */
HM_EXTERN NSString * const HMCharacteristicTypeSmokeDetected NS_AVAILABLE_IOS(9_0) __WATCHOS_AVAILABLE(__WATCHOS_2_0);

/*!
 * @brief Characteristic type for software version. The value of the characteristic is a string value
 *        describing the software version of the accessory.
 */
HM_EXTERN NSString * const HMCharacteristicTypeSoftwareVersion NS_AVAILABLE_IOS(9_0) __WATCHOS_AVAILABLE(__WATCHOS_2_0);

/*!
 * @brief Characteristic type to indicate status of a service is active. The value of the characteristic is a boolean.
 */
HM_EXTERN NSString * const HMCharacteristicTypeStatusActive NS_AVAILABLE_IOS(9_0) __WATCHOS_AVAILABLE(__WATCHOS_2_0);

/*!
 * @brief Characteristic type to indicate status of a service is fault. The value of the characteristic is a uint8 value.
 */
HM_EXTERN NSString * const HMCharacteristicTypeStatusFault NS_AVAILABLE_IOS(9_0) __WATCHOS_AVAILABLE(__WATCHOS_2_0);

/*!
 * @brief Characteristic type to indicate status of a service is jammed. The value of the characteristic is a uint8 value.
 *        A value of 0 indicates that the service is not jammed; a value of 1 indicates that the service is jammed.
 */
HM_EXTERN NSString * const HMCharacteristicTypeStatusJammed NS_AVAILABLE_IOS(9_0) __WATCHOS_AVAILABLE(__WATCHOS_2_0);

/*!
 * @brief Characteristic type to indicate status of a service is low battery. The value of the characteristic is a uint8 value.
 *        A value of 0 indicates battery level is normal; a value of 1 indicates that battery level is low.
 */
HM_EXTERN NSString * const HMCharacteristicTypeStatusLowBattery NS_AVAILABLE_IOS(9_0) __WATCHOS_AVAILABLE(__WATCHOS_2_0);

/*!
 * @brief Characteristic type to indicate status of a service is tampered. The value of the characteristic is a uint8 value.
 *        A value of 0 indicates no tampering has been detected; a value of 1 indicates that a tampering has been detected.
 */
HM_EXTERN NSString * const HMCharacteristicTypeStatusTampered NS_AVAILABLE_IOS(9_0) __WATCHOS_AVAILABLE(__WATCHOS_2_0);

/*!
 * @brief Characteristic type for target horizontal tilt angle. The value is a float representing the angle in arc degrees.
 */
HM_EXTERN NSString * const HMCharacteristicTypeTargetHorizontalTilt NS_AVAILABLE_IOS(9_0) __WATCHOS_AVAILABLE(__WATCHOS_2_0);

/*!
 * @brief Characteristic type for target security system state. The value of the characteristic is one of
 *        the values defined for HMCharacteristicValueTargetSecuritySystemState.
 */
HM_EXTERN NSString * const HMCharacteristicTypeTargetSecuritySystemState NS_AVAILABLE_IOS(9_0) __WATCHOS_AVAILABLE(__WATCHOS_2_0);

/*!
 * @brief Characteristic type for target position of a door/window. The value of the characteristic is an
 *        uint8 value in percent. For shades/awnings, a value of 0 indicates no shade and a value of 100
 *        indicates most shade. For blinds, a value of 0 indicates most light is allowed in and 100
 *        indicates least light is allowed.
 */
HM_EXTERN NSString * const HMCharacteristicTypeTargetPosition NS_AVAILABLE_IOS(9_0) __WATCHOS_AVAILABLE(__WATCHOS_2_0);

/*!
 * @brief Characteristic type for target vertical tilt angle. The value is a float representing the angle in arc degrees.
 */
HM_EXTERN NSString * const HMCharacteristicTypeTargetVerticalTilt NS_AVAILABLE_IOS(9_0) __WATCHOS_AVAILABLE(__WATCHOS_2_0);

NS_ASSUME_NONNULL_END
