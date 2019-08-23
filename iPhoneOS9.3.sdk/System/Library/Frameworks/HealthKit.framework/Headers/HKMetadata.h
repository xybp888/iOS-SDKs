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
HK_EXTERN NSString * const HKMetadataKeyDeviceSerialNumber NS_AVAILABLE_IOS(8_0);

/*!
 @constant      HKMetadataKeyBodyTemperatureSensorLocation
 @abstract      Represents the location where a particular body temperature reading was taken.
 @discussion    The expected value type is an NSNumber containing a HKBodyTemperatureSensorLocation value.
 */
HK_EXTERN NSString * const HKMetadataKeyBodyTemperatureSensorLocation NS_AVAILABLE_IOS(8_0);

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
} NS_ENUM_AVAILABLE_IOS(8_0);

/*!
 @constant      HKMetadataKeyHeartRateSensorLocation
 @abstract      Represents the location where a particular heart rate reading was taken.
 @discussion    The expected value type is an NSNumber containing a HKHeartRateSensorLocation value.
 */
HK_EXTERN NSString * const HKMetadataKeyHeartRateSensorLocation NS_AVAILABLE_IOS(8_0);

typedef NS_ENUM(NSInteger, HKHeartRateSensorLocation) {
    HKHeartRateSensorLocationOther = 0,
    HKHeartRateSensorLocationChest,
    HKHeartRateSensorLocationWrist,
    HKHeartRateSensorLocationFinger,
    HKHeartRateSensorLocationHand,
    HKHeartRateSensorLocationEarLobe,
    HKHeartRateSensorLocationFoot,
} NS_ENUM_AVAILABLE_IOS(8_0);

/*!
 @constant      HKMetadataKeyFoodType
 @abstract      Represents the type of food that was consumed when creating an HKObject.
 @discussion    This should be a short string representing the type of food, such as 'Banana'. The expected value type
                is NSString.
 */
HK_EXTERN NSString * const HKMetadataKeyFoodType NS_AVAILABLE_IOS(8_0);

/*!
 @constant      HKMetadataKeyUDIDeviceIdentifier
 @abstract      Represents the device identifier portion of a device's UDI (Unique Device Identifier).
 @discussion    The device identifier can be used to reference the GUDID (Globally Unique Device Identifier Database).
                The expected value type is NSString.
 
                ** Note that the use of this key is now discouraged in favor of the HKDevice class.
 */
HK_EXTERN NSString * const HKMetadataKeyUDIDeviceIdentifier NS_AVAILABLE_IOS(8_0);

/*!
 @constant      HKMetadataKeyUDIProductionIdentifier
 @abstract      Represents the production identifier portion of a device's UDI (Unique Device Identifier).
 @discussion    While part of a device's UDI, the production identifier is not saved in the FDA's GUDID 
                (Globally Unique Device Identifier Database) and its use in HealthKit is now discouraged for
                user privacy reasons. Apps should consider handling this independently of HealthKit APIs if
                needed.
                The expected value type is NSString.
 */
HK_EXTERN NSString * const HKMetadataKeyUDIProductionIdentifier NS_AVAILABLE_IOS(8_0);

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
HK_EXTERN NSString * const HKMetadataKeyDigitalSignature NS_AVAILABLE_IOS(8_0);

/*!
 @constant      HKMetadataKeyExternalUUID
 @abstract      Represents a unique identifier for an HKObject that is set by its source. 
 @discussion    The expected value type is NSString.
 */
HK_EXTERN NSString * const HKMetadataKeyExternalUUID NS_AVAILABLE_IOS(8_0);

/*!
 @constant      HKMetadataKeyTimeZone
 @abstract      Represents the time zone that the user was in when the HKObject was created.
 @discussion    The expected value type is an NSString compatible with NSTimeZone's +timeZoneWithName:.
 */
HK_EXTERN NSString * const HKMetadataKeyTimeZone NS_AVAILABLE_IOS(8_0);


/*!
 @constant      HKMetadataKeyDeviceName
 @abstract      Represents the name of the device that took the reading.
 @discussion    The expected value type is NSString.
 
                ** Note that the use of this key is now discouraged in favor of the HKDevice class.
 */
HK_EXTERN NSString * const HKMetadataKeyDeviceName NS_AVAILABLE_IOS(8_0);

/*!
 @constant      HKMetadataKeyDeviceManufacturerName
 @abstract      Represents the name of the manufacturer of the device that took the reading.
 @discussion    The expected value type is NSString.
 
                ** Note that the use of this key is now discouraged in favor of the HKDevice class.
 */
HK_EXTERN NSString * const HKMetadataKeyDeviceManufacturerName NS_AVAILABLE_IOS(8_0);

/*!
 @constant      HKMetadataKeyWasTakenInLab
 @abstract      Represents whether or not the reading was taken in a lab.
 @discussion    The expected value type is an NSNumber containing a BOOL value.
 */
HK_EXTERN NSString * const HKMetadataKeyWasTakenInLab NS_AVAILABLE_IOS(8_0);

/*!
 @constant      HKMetadataKeyReferenceRangeLowerLimit
 @abstract      Represents the lower limit of the reference range for a lab result.
 @discussion    The expected value type is an NSNumber.
 */
HK_EXTERN NSString * const HKMetadataKeyReferenceRangeLowerLimit NS_AVAILABLE_IOS(8_0);

/*!
 @constant      HKMetadataKeyReferenceRangeUpperLimit
 @abstract      Represents the upper limit of the reference range for a lab result.
 @discussion    The expected value type is an NSNumber.
 */
HK_EXTERN NSString * const HKMetadataKeyReferenceRangeUpperLimit NS_AVAILABLE_IOS(8_0);

/*!
 @constant      HKMetadataKeyWasUserEntered
 @abstract      Represents whether or not the reading was entered by the user.
 @discussion    The expected value type is an NSNumber containing a BOOL value.
 */
HK_EXTERN NSString * const HKMetadataKeyWasUserEntered NS_AVAILABLE_IOS(8_0);

/*!
 @constant      HKMetadataKeyWorkoutBrandName
 @abstract      Represents the brand name of a particular workout.
 @discussion    The expected value type is NSString.
 */
HK_EXTERN NSString * const HKMetadataKeyWorkoutBrandName NS_AVAILABLE_IOS(8_0);

/*!
 @constant      HKMetadataKeyGroupFitness
 @abstract      Represents whether or not a workout was performed as part of a group fitness class.
 @discussion    The expected value type is an NSNumber containing a BOOL value.
 */
HK_EXTERN NSString * const HKMetadataKeyGroupFitness NS_AVAILABLE_IOS(8_0);

/*!
 @constant      HKMetadataKeyIndoorWorkout
 @abstract      Represents whether or not a workout was performed indoors as opposed to outdoors.
 @discussion    The expected value type is an NSNumber containing a BOOL value.
 */
HK_EXTERN NSString * const HKMetadataKeyIndoorWorkout NS_AVAILABLE_IOS(8_0);

/*!
 @constant      HKMetadataKeyCoachedWorkout
 @abstract      Represents whether or not a workout was performed with a coach or personal trainer.
 @discussion    The expected value type is an NSNumber containing a BOOL value.
 */
HK_EXTERN NSString * const HKMetadataKeyCoachedWorkout NS_AVAILABLE_IOS(8_0);

/*!
 @constant      HKMetadataKeySexualActivityProtectionUsed
 @abstract      Represents whether or not protection was used during sexual activity. This can be used to track either
                protection from STIs or protection from pregnancy.
 @discussion    The expected value type is an NSNumber containing a BOOL value.
 */
HK_EXTERN NSString * const HKMetadataKeySexualActivityProtectionUsed NS_AVAILABLE_IOS(9_0);

/*!
 @constant      HKMetadataKeyMenstrualCycleStart
 @abstract      Indicates whether or not the sample represents the start of a menstrual cycle. This is a required
                metadata key for category samples of type HKCategorySampleMenstrualFlow.
 @discussion    The expected value type is an NSNumber containing a BOOL value.
 */
HK_EXTERN NSString * const HKMetadataKeyMenstrualCycleStart NS_AVAILABLE_IOS(9_0);

NS_ASSUME_NONNULL_END
