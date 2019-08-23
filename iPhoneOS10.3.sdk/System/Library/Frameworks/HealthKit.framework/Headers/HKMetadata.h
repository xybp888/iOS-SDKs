//
//  HKMetadata.h
//  HealthKit
//
//  Copyright (c) 2013-2014 Apple Inc. All rights reserved.
//

#import <HealthKit/HKDefines.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 @constant      HKMetadataKeyUDIProductionIdentifier
 @abstract      Represents the serial number of the device that created the HKObject.
 @discussion    The expected value type is NSString.
 */
HK_EXTERN NSString * const HKMetadataKeyDeviceSerialNumber HK_AVAILABLE_IOS_WATCHOS(8_0, 2_0);

/*!
 @constant      HKMetadataKeyBodyTemperatureSensorLocation
 @abstract      Represents the location where a particular body temperature reading was taken.
 @discussion    The expected value type is an NSNumber containing a HKBodyTemperatureSensorLocation value.
 */
HK_EXTERN NSString * const HKMetadataKeyBodyTemperatureSensorLocation HK_AVAILABLE_IOS_WATCHOS(8_0, 2_0);

typedef NS_ENUM(NSInteger, HKBodyTemperatureSensorLocation) {
    HKBodyTemperatureSensorLocationOther = 0,
    HKBodyTemperatureSensorLocationArmpit,
    HKBodyTemperatureSensorLocationBody,
    HKBodyTemperatureSensorLocationEar,
    HKBodyTemperatureSensorLocationFinger,
    HKBodyTemperatureSensorLocationGastroIntestinal,
    HKBodyTemperatureSensorLocationMouth,
    HKBodyTemperatureSensorLocationRectum,
    HKBodyTemperatureSensorLocationToe,
    HKBodyTemperatureSensorLocationEarDrum,
    HKBodyTemperatureSensorLocationTemporalArtery,
    HKBodyTemperatureSensorLocationForehead,
} HK_ENUM_AVAILABLE_IOS_WATCHOS(8_0, 2_0);

/*!
 @constant      HKMetadataKeyHeartRateSensorLocation
 @abstract      Represents the location where a particular heart rate reading was taken.
 @discussion    The expected value type is an NSNumber containing a HKHeartRateSensorLocation value.
 */
HK_EXTERN NSString * const HKMetadataKeyHeartRateSensorLocation HK_AVAILABLE_IOS_WATCHOS(8_0, 2_0);

typedef NS_ENUM(NSInteger, HKHeartRateSensorLocation) {
    HKHeartRateSensorLocationOther = 0,
    HKHeartRateSensorLocationChest,
    HKHeartRateSensorLocationWrist,
    HKHeartRateSensorLocationFinger,
    HKHeartRateSensorLocationHand,
    HKHeartRateSensorLocationEarLobe,
    HKHeartRateSensorLocationFoot,
} HK_ENUM_AVAILABLE_IOS_WATCHOS(8_0, 2_0);

/*!
 @constant      HKMetadataKeyFoodType
 @abstract      Represents the type of food that was consumed when creating an HKObject.
 @discussion    This should be a short string representing the type of food, such as 'Banana'. The expected value type
                is NSString.
 */
HK_EXTERN NSString * const HKMetadataKeyFoodType HK_AVAILABLE_IOS_WATCHOS(8_0, 2_0);

/*!
 @constant      HKMetadataKeyUDIDeviceIdentifier
 @abstract      Represents the device identifier portion of a device's UDI (Unique Device Identifier).
 @discussion    The device identifier can be used to reference the GUDID (Globally Unique Device Identifier Database).
                The expected value type is NSString.
 
                ** Note that the use of this key is now discouraged in favor of the HKDevice class.
 */
HK_EXTERN NSString * const HKMetadataKeyUDIDeviceIdentifier HK_AVAILABLE_IOS_WATCHOS(8_0, 2_0);

/*!
 @constant      HKMetadataKeyUDIProductionIdentifier
 @abstract      Represents the production identifier portion of a device's UDI (Unique Device Identifier).
 @discussion    While part of a device's UDI, the production identifier is not saved in the FDA's GUDID 
                (Globally Unique Device Identifier Database) and its use in HealthKit is now discouraged for
                user privacy reasons. Apps should consider handling this independently of HealthKit APIs if
                needed.
                The expected value type is NSString.
 */
HK_EXTERN NSString * const HKMetadataKeyUDIProductionIdentifier HK_AVAILABLE_IOS_WATCHOS(8_0, 2_0);

/*!
 @constant      HKMetadataKeyDigitalSignature
 @abstract      Represents a digital signature validating the origin of an HKObject's value.
 @discussion    Intended to provide data integrity for sample data produced by trusted (tamper resistant) measuring devices.
                The digital signature format should be CMS (Cryptographic Message Syntax specified in IETF RFC 5652).
                It should be a “Signed-data” type signature containing the data items to be signed (e.g., timestamp, value, etc.)
                using ASN.1 encoding with DER (Distinguished Encoding Rules). The entire enveloping signature should be further
                encoded using base64. Recommended digest is SHA256, and recommended cipher is FIPS PUB 186-4 Digital Signature 
                Standard Elliptic Curve P-256. See documentation for details.

 */
HK_EXTERN NSString * const HKMetadataKeyDigitalSignature HK_AVAILABLE_IOS_WATCHOS(8_0, 2_0);

/*!
 @constant      HKMetadataKeyExternalUUID
 @abstract      Represents a unique identifier for an HKObject that is set by its source. 
 @discussion    The expected value type is NSString.
 */
HK_EXTERN NSString * const HKMetadataKeyExternalUUID HK_AVAILABLE_IOS_WATCHOS(8_0, 2_0);

/*!
 @constant      HKMetadataKeyTimeZone
 @abstract      Represents the time zone that the user was in when the HKObject was created.
 @discussion    The expected value type is an NSString compatible with NSTimeZone's +timeZoneWithName:.
 */
HK_EXTERN NSString * const HKMetadataKeyTimeZone HK_AVAILABLE_IOS_WATCHOS(8_0, 2_0);


/*!
 @constant      HKMetadataKeyDeviceName
 @abstract      Represents the name of the device that took the reading.
 @discussion    The expected value type is NSString.
 
                ** Note that the use of this key is now discouraged in favor of the HKDevice class.
 */
HK_EXTERN NSString * const HKMetadataKeyDeviceName HK_AVAILABLE_IOS_WATCHOS(8_0, 2_0);

/*!
 @constant      HKMetadataKeyDeviceManufacturerName
 @abstract      Represents the name of the manufacturer of the device that took the reading.
 @discussion    The expected value type is NSString.
 
                ** Note that the use of this key is now discouraged in favor of the HKDevice class.
 */
HK_EXTERN NSString * const HKMetadataKeyDeviceManufacturerName HK_AVAILABLE_IOS_WATCHOS(8_0, 2_0);

/*!
 @constant      HKMetadataKeyWasTakenInLab
 @abstract      Represents whether or not the reading was taken in a lab.
 @discussion    The expected value type is an NSNumber containing a BOOL value.
 */
HK_EXTERN NSString * const HKMetadataKeyWasTakenInLab HK_AVAILABLE_IOS_WATCHOS(8_0, 2_0);

/*!
 @constant      HKMetadataKeyReferenceRangeLowerLimit
 @abstract      Represents the lower limit of the reference range for a lab result.
 @discussion    The expected value type is an NSNumber.
 */
HK_EXTERN NSString * const HKMetadataKeyReferenceRangeLowerLimit HK_AVAILABLE_IOS_WATCHOS(8_0, 2_0);

/*!
 @constant      HKMetadataKeyReferenceRangeUpperLimit
 @abstract      Represents the upper limit of the reference range for a lab result.
 @discussion    The expected value type is an NSNumber.
 */
HK_EXTERN NSString * const HKMetadataKeyReferenceRangeUpperLimit HK_AVAILABLE_IOS_WATCHOS(8_0, 2_0);

/*!
 @constant      HKMetadataKeyWasUserEntered
 @abstract      Represents whether or not the reading was entered by the user.
 @discussion    The expected value type is an NSNumber containing a BOOL value.
 */
HK_EXTERN NSString * const HKMetadataKeyWasUserEntered HK_AVAILABLE_IOS_WATCHOS(8_0, 2_0);

/*!
 @constant      HKMetadataKeyWorkoutBrandName
 @abstract      Represents the brand name of a particular workout.
 @discussion    The expected value type is NSString.
 */
HK_EXTERN NSString * const HKMetadataKeyWorkoutBrandName HK_AVAILABLE_IOS_WATCHOS(8_0, 2_0);

/*!
 @constant      HKMetadataKeyGroupFitness
 @abstract      Represents whether or not a workout was performed as part of a group fitness class.
 @discussion    The expected value type is an NSNumber containing a BOOL value.
 */
HK_EXTERN NSString * const HKMetadataKeyGroupFitness HK_AVAILABLE_IOS_WATCHOS(8_0, 2_0);

/*!
 @constant      HKMetadataKeyIndoorWorkout
 @abstract      Represents whether or not a workout was performed indoors as opposed to outdoors.
 @discussion    The expected value type is an NSNumber containing a BOOL value.
 */
HK_EXTERN NSString * const HKMetadataKeyIndoorWorkout HK_AVAILABLE_IOS_WATCHOS(8_0, 2_0);

/*!
 @constant      HKMetadataKeyCoachedWorkout
 @abstract      Represents whether or not a workout was performed with a coach or personal trainer.
 @discussion    The expected value type is an NSNumber containing a BOOL value.
 */
HK_EXTERN NSString * const HKMetadataKeyCoachedWorkout HK_AVAILABLE_IOS_WATCHOS(8_0, 2_0);

typedef NS_ENUM(NSInteger, HKWeatherCondition) {
    HKWeatherConditionNone = 0,
    HKWeatherConditionClear,
    HKWeatherConditionFair,
    HKWeatherConditionPartlyCloudy,
    HKWeatherConditionMostlyCloudy,
    HKWeatherConditionCloudy,
    HKWeatherConditionFoggy,
    HKWeatherConditionHaze,
    HKWeatherConditionWindy,
    HKWeatherConditionBlustery,
    HKWeatherConditionSmoky,
    HKWeatherConditionDust,
    HKWeatherConditionSnow,
    HKWeatherConditionHail,
    HKWeatherConditionSleet,
    HKWeatherConditionFreezingDrizzle,
    HKWeatherConditionFreezingRain,
    HKWeatherConditionMixedRainAndHail,
    HKWeatherConditionMixedRainAndSnow,
    HKWeatherConditionMixedRainAndSleet,
    HKWeatherConditionMixedSnowAndSleet,
    HKWeatherConditionDrizzle,
    HKWeatherConditionScatteredShowers,
    HKWeatherConditionShowers,
    HKWeatherConditionThunderstorms,
    HKWeatherConditionTropicalStorm,
    HKWeatherConditionHurricane,
    HKWeatherConditionTornado,
} HK_ENUM_AVAILABLE_IOS_WATCHOS(10_0, 3_0);

/*!
 @constant      HKMetadataKeyWeatherCondition
 @abstract      Represents the weather condition during the sample.
 @discussion    The expected value type is an NSNumber containing an HKWeatherCondition value. This key may be set on an
                HKWorkout object to represent the overall weather condition during the workout.
 */
HK_EXTERN NSString * const HKMetadataKeyWeatherCondition HK_AVAILABLE_IOS_WATCHOS(10_0, 3_0);

/*!
 @constant      HKMetadataKeyWeatherTemperature
 @abstract      Represents the weather temperature during the sample.
 @discussion    The expected value type is an HKQuantity expressed in a temperature unit. This key may be set on an
                HKWorkout object to represent the overall temperature during the workout.
 */
HK_EXTERN NSString * const HKMetadataKeyWeatherTemperature HK_AVAILABLE_IOS_WATCHOS(10_0, 3_0);

/*!
 @constant      HKMetadataKeyHumidity
 @abstract      Represents the weather humidity during the sample.
 @discussion    The expected value type is an HKQuantity expressed in percent. This key may be set on an HKWorkout
                object to represent the overall humidity during the workout.
 */
HK_EXTERN NSString * const HKMetadataKeyWeatherHumidity HK_AVAILABLE_IOS_WATCHOS(10_0, 3_0);

/*!
 @constant      HKMetadataKeySexualActivityProtectionUsed
 @abstract      Represents whether or not protection was used during sexual activity. This can be used to track either
                protection from STIs or protection from pregnancy.
 @discussion    The expected value type is an NSNumber containing a BOOL value.
 */
HK_EXTERN NSString * const HKMetadataKeySexualActivityProtectionUsed HK_AVAILABLE_IOS_WATCHOS(9_0, 2_0);

/*!
 @constant      HKMetadataKeyMenstrualCycleStart
 @abstract      Indicates whether or not the sample represents the start of a menstrual cycle. This is a required
                metadata key for category samples of type HKCategorySampleMenstrualFlow.
 @discussion    The expected value type is an NSNumber containing a BOOL value.
 */
HK_EXTERN NSString * const HKMetadataKeyMenstrualCycleStart HK_AVAILABLE_IOS_WATCHOS(9_0, 2_0);

/*!
 @constant      HKMetadataKeyLapLength
 @abstract      Represents the length of a lap recorded during a workout.
 @discussion    The expected value type is an HKQuantity object compatible with a length unit. This key may be set on an
                HKWorkout object to represent the length of a lap.
 */
HK_EXTERN NSString * const HKMetadataKeyLapLength HK_AVAILABLE_IOS_WATCHOS(10_0, 3_0);

/*!
 @enum          HKWorkoutSwimmingLocationType
 @abstract      This enumerated type is used to represent the location type of a swimming workout.
 @discussion    This value indicates whether a swimming workout was performed in a pool or open water.
 */
typedef NS_ENUM(NSInteger, HKWorkoutSwimmingLocationType) {
    HKWorkoutSwimmingLocationTypeUnknown = 0,
    HKWorkoutSwimmingLocationTypePool,
    HKWorkoutSwimmingLocationTypeOpenWater,
} HK_ENUM_AVAILABLE_IOS_WATCHOS(10_0, 3_0);

/*!
 @constant      HKMetadataKeySwimmingLocationType
 @abstract      Represents the location type of a swimming workout.
 @discussion    The expected value type is an NSNumber containing an HKWorkoutSwimmingLocationType value. This key may
                be set on an HKWorkout object to represent the swimming location type.
 */
HK_EXTERN NSString * const HKMetadataKeySwimmingLocationType HK_AVAILABLE_IOS_WATCHOS(10_0, 3_0);

/*!
 @enum          HKSwimmingStrokeStyle
 @abstract      Represents a style of stroke used during a swimming workout.
 */
typedef NS_ENUM(NSInteger, HKSwimmingStrokeStyle) {
    HKSwimmingStrokeStyleUnknown = 0,
    HKSwimmingStrokeStyleMixed,
    HKSwimmingStrokeStyleFreestyle,
    HKSwimmingStrokeStyleBackstroke,
    HKSwimmingStrokeStyleBreaststroke,
    HKSwimmingStrokeStyleButterfly,
} HK_ENUM_AVAILABLE_IOS_WATCHOS(10_0, 3_0);

/*!
 @constant      HKMetadataKeySwimmingStrokeStyle
 @abstract      Represents the predominant stroke style during a lap of a swimming workout.
 @discussion    The expected value type is an NSNumber containing an HKSwimmingStrokeStyle value. This key may be set on
                an HKWorkoutEvent object with the type HKWorkoutEventTypeLap to represent the predominant style used
                during the lap.
 */
HK_EXTERN NSString * const HKMetadataKeySwimmingStrokeStyle HK_AVAILABLE_IOS_WATCHOS(10_0, 3_0);

NS_ASSUME_NONNULL_END
