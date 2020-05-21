/*
	Copyright (C) 2020 Apple Inc. All Rights Reserved.
*/

#pragma once

#ifndef EXPOSURE_NOTIFICATION_INDIRECT_INCLUDES
#error "Please #import <ExposureNotification/ExposureNotification.h> instead of this file directly."
#endif

#import <dispatch/dispatch.h>
#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

#ifdef __cplusplus
extern "C" {
#endif

//===========================================================================================================================
// MARK: -
// MARK: == Configuration ==

/// General API support available. Allows compile-time conditionalization of code.
#ifndef EN_FEATURE_GENERAL
	#if TARGET_OS_IOS
		#define EN_FEATURE_GENERAL		1
	#else
		#define EN_FEATURE_GENERAL		0
	#endif
#endif

/// Indicates the platforms this API is available. Used for non-exportable items, such as typedefs.
#define EN_API_AVAILABLE			API_AVAILABLE( ios( 13.5 ) ) API_UNAVAILABLE( macos, tvos, watchos )

/// Indicates the platforms this API is available and exports the symbol via the framework.
#define EN_API_AVAILABLE_EXPORT		EN_API_AVAILABLE __attribute__( ( visibility( "default" ) ) )

//===========================================================================================================================
// MARK: -
// MARK: == Errors ==

/// NSError domain for Exposure Notification errors.
EN_API_AVAILABLE_EXPORT
extern NSErrorDomain const		ENErrorDomain;

/// Error codes used with ENErrorDomain.
typedef NS_ERROR_ENUM( ENErrorDomain, ENErrorCode )
{
	ENErrorCodeUnknown				= 1,  /// Underlying failure with an unknown cause.
	ENErrorCodeBadParameter			= 2,  /// Missing or incorrect parameter.
	ENErrorCodeNotEntitled			= 3,  /// Calling process doesn't have the correct entitlement.
	ENErrorCodeNotAuthorized		= 4,  /// User denied this process access to Exposure Notification functionality.
	ENErrorCodeUnsupported			= 5,  /// Operation is not supported.
	ENErrorCodeInvalidated			= 6,  /// Invalidate was called before the operation completed normally.
	ENErrorCodeBluetoothOff			= 7,  /// Bluetooth was turned off the by user.
	ENErrorCodeInsufficientStorage	= 8,  /// Insufficient storage space to enable Exposure Notification.
	ENErrorCodeNotEnabled			= 9,  /// Exposure Notification has not been enabled.
	ENErrorCodeAPIMisuse			= 10, /// The API was used incorrectly.
	ENErrorCodeInternal				= 11, /// Internal error. This indicates a bug in this framework.
	ENErrorCodeInsufficientMemory	= 12, /// Not enough memory to perform an operation.
	ENErrorCodeRateLimited			= 13, /// API called too frequently. See API for acceptable frequency.
	ENErrorCodeRestricted			= 14, /// Exposure Notification is disabled due to system policies.
	ENErrorCodeBadFormat			= 15, /// File or data format problem.
};

/// Type for returning NSError's from functions. Avoids long and repetitious method signatures.
typedef NSError * _Nullable __autoreleasing * _Nullable		ENErrorOutType;

//===========================================================================================================================
// MARK: -
// MARK: == Misc ==

//===========================================================================================================================
/*!	@brief	Attenuation of a radio signal. This is the Advertised Transmit Power - Measured RSSI.

	Note: The attenuation value may be misleading because more attenuation doesn’t necessarily mean the device is farther 
	away. For example, two people could be very close and facing each other with their phones in their back pockets. This 
	may report higher attenuation (i.e. weaker received signal) even though the individuals are very close together.
*/
typedef uint8_t		ENAttenuation;

//===========================================================================================================================
/*!	@brief	Indicates the status of authorization for the app.
*/
typedef NS_ENUM( NSInteger, ENAuthorizationStatus )
{
	/// Authorization status has not yet been determined.
	/// This status means the user has not been prompted yet. Using the API in this state may prompt the user.
	ENAuthorizationStatusUnknown		= 0,
	
	/// This app is not authorized to use Exposure Notification. The user cannot change this app's authorization status.
	/// This status may be due to active restrictions, such as parental controls being in place.
	ENAuthorizationStatusRestricted		= 1,
	
	/// The user denied authorization for this app.
	ENAuthorizationStatusNotAuthorized	= 2,
	
	/// The user has authorized this app to use Exposure Notification.
	ENAuthorizationStatusAuthorized		= 3,
};

//===========================================================================================================================
/*!	@brief	ENIntervalNumber (ENIN)
	
	A number for each 10 minute window that is shared between all devices participating in the protocol.
	These time windows are based Unix Time (epoch 1970-01-01 00:00:00). It's calculated as:
	
	ENIN = <Seconds since 1970-01-01 00:00:00> / ( 60 * 10 )
	
	It's encoded as an unsigned 32-bit (uint32_t), little endian value.
*/
typedef uint32_t	ENIntervalNumber;

//===========================================================================================================================
/*!	@brief	Represents a risk level, ranging from 0-7.
*/
typedef uint8_t		ENRiskLevel;

//===========================================================================================================================
/*!	@brief	The value, ranging from 1 to 8, that the app assigns to each Risk Level in each of the Risk Level Parameters.
*/
typedef uint8_t		ENRiskLevelValue;

//===========================================================================================================================
/*!	@brief	Represents estimated risk calculated by a scoring algorithm. Range is 1-8. 8 is the highest risk.
*/
typedef uint8_t		ENRiskScore;

//===========================================================================================================================
// MARK: -
// MARK: == Handlers ==

/// Invoked when an operation completes. Error is nil for success or non-nil if an error occurred.
typedef void ( ^ENErrorHandler )( NSError * _Nullable error );

// MARK: -
// MARK: == Classes ==

//===========================================================================================================================
/*!	@brief	Configuration parameters for exposure detection.

	Risk Parameters
	
	The four parameters used to calculate the Total Risk Score:
	
	-	Transmission - purely app defined, flexibility to tag a specific positive key. Could be tagged based on symptoms, 
		level of diagnosis verification or other determination from the app/health authority.
	-	Duration (measured by API) - Cumulative duration of the exposure Days (measured by API).
	-	Days since the exposure incident.
	-	Attenuation (measured by API) - Minimum bluetooth signal strength attenuation (Tx Power - RSSI).
	
	Risk Level Value:
	The value, ranging from 1 to 8, that the app assigns to each Risk Level in each of the Risk Level Parameter.  
	
	Risk Level:
	The eight “buckets” assigned to each Risk Level Parameter.
	
	Risk Score:
	The resulting score from the risk calculation (an integer).  The maximum score per person over a 24 hour period.
	
	These parameters are used to calculate a risk for each exposure incident using the following forumula:
	
	Sum = 
		( attenuationLevelValue * attenuationWeight ) + 
		( daysSinceLastExposureLevelValue * daysSinceLastExposureWeight ) + 
		( durationLevelValue * durationWeight ) + 
		( transmissionRiskLevelValue * transmissionRiskWeight )
	TotalRiskScore = Sum / ( attenuationWeight + daysSinceLastExposureWeight + durationWeight + transmissionRiskWeight )
	
	Level values are in the range 1-8.
	Weights must be in the range 0-100.
	TotalRiskScore will be in the range 1-8.
*/
EN_API_AVAILABLE_EXPORT
@interface ENExposureConfiguration : NSObject

/// Metadata associated with the configuration.
@property (readwrite, copy, nullable, nonatomic) NSDictionary *		metadata;

/// Minimum risk score. Excludes exposure incidents with scores lower than this. Defaults to no minimum.
@property (readwrite, assign, nonatomic) ENRiskScore				minimumRiskScore;

//---------------------------------------------------------------------------------------------------------------------------
/*!	@brief	Level values for attenuation buckets. Must contain a value for each bucket as defined below:
	
	attenuationScores[0] when Attenuation > 73.
	attenuationScores[1] when 73 >= Attenuation > 63.
	attenuationScores[2] when 63 >= Attenuation > 51.
	attenuationScores[3] when 51 >= Attenuation > 33.
	attenuationScores[4] when 33 >= Attenuation > 27.
	attenuationScores[5] when 27 >= Attenuation > 15.
	attenuationScores[6] when 15 >= Attenuation > 10.
	attenuationScores[7] when 10 >= Attenuation.
*/
@property (readwrite, copy, nonatomic) NSArray <NSNumber *> *		attenuationLevelValues;

/// Weight to apply to the attenuation level value. Must be in the range 0-100.
@property (readwrite, assign, nonatomic) double						attenuationWeight;

//---------------------------------------------------------------------------------------------------------------------------
/*!	@brief	Level values for days since last exposure buckets. Must contain a value for each bucket as defined below:

	daysSinceLastExposureScores[0] when Days >= 14.
	daysSinceLastExposureScores[1] else Days >= 12
	daysSinceLastExposureScores[2] else Days >= 10
	daysSinceLastExposureScores[3] else Days >= 8
	daysSinceLastExposureScores[4] else Days >= 6
	daysSinceLastExposureScores[5] else Days >= 4
	daysSinceLastExposureScores[6] else Days >= 2
	daysSinceLastExposureScores[7] else Days >= 0
*/
@property (readwrite, copy, nonatomic) NSArray <NSNumber *> *		daysSinceLastExposureLevelValues;

/// Weight to apply to the days since last exposure level value. Must be in the range 0-100.
@property (readwrite, assign, nonatomic) double						daysSinceLastExposureWeight;

//---------------------------------------------------------------------------------------------------------------------------
/*!	@brief	Level values for duration buckets. Must contain a value for each bucket as defined below:

	durationScores[0] when Duration == 0
	durationScores[1] else Duration <= 5
	durationScores[2] else Duration <= 10
	durationScores[3] else Duration <= 15
	durationScores[4] else Duration <= 20
	durationScores[5] else Duration <= 25
	durationScores[6] else Duration <= 30
	durationScores[7] else Duration  > 30
*/
@property (readwrite, copy, nonatomic) NSArray <NSNumber *> *		durationLevelValues;

/// Weight to apply to the duration level value. Must be in the range 0-100.
@property (readwrite, assign, nonatomic) double						durationWeight;

//---------------------------------------------------------------------------------------------------------------------------
/*!	@brief	Level values for transmission risk buckets. Must contain a value for each bucket as defined below:

	transmissionRiskScores[0] for risk level 0.
	transmissionRiskScores[1] for risk level 1.
	transmissionRiskScores[2] for risk level 2.
	transmissionRiskScores[3] for risk level 3.
	transmissionRiskScores[4] for risk level 4.
	transmissionRiskScores[5] for risk level 5.
	transmissionRiskScores[6] for risk level 6.
	transmissionRiskScores[7] for risk level 7.
*/
@property (readwrite, copy, nonatomic) NSArray <NSNumber *> *		transmissionRiskLevelValues;

/// Weight to apply to the transmission risk level value. Must be in the range 0-100.
@property (readwrite, assign, nonatomic) double						transmissionRiskWeight;

@end

//===========================================================================================================================
/*!	@brief	Info about an exposure.
*/
EN_API_AVAILABLE_EXPORT
@interface ENExposureInfo : NSObject

/// Array of durations in seconds at certain radio signal attenuations.
/// Array index 0: Sum of durations for this exposure when attenuation was <= 50.
/// Array index 1: Sum of durations for this exposure when attenuation was > 50.
@property (readwrite, copy, nonatomic) NSArray <NSNumber *> *		attenuationDurations;

/// Attenuation value of the peer device when exposure occurred.
@property (readonly, assign, nonatomic) ENAttenuation				attenuationValue;

/// Date when the exposure occurred. This may have reduced precision, such as within 1 day of the actual time.
@property (readonly, copy, nonatomic) NSDate *						date;

/// Length of exposure in 5 minute increments with a 30 minute maximum.
@property (readonly, assign, nonatomic) NSTimeInterval				duration;

/// Metadata associated with the exposure.
@property (readonly, copy, nullable, nonatomic) NSDictionary *		metadata;

/// Indicates the total risk calculated for this exposure incident.
@property (readonly, assign, nonatomic) ENRiskScore					totalRiskScore;

/// Indicates the transmission risk associated with the diagnosis key.
@property (readonly, assign, nonatomic) ENRiskLevel					transmissionRiskLevel;

@end

//===========================================================================================================================
/*!	@brief	Summary of exposure detection.
*/
EN_API_AVAILABLE_EXPORT
@interface ENExposureDetectionSummary : NSObject

/// Array of durations in seconds at certain radio signal attenuations.
/// Array index 0: Sum of durations for all exposures when attenuation was <= 50.
/// Array index 1: Sum of durations for all exposures when attenuation was > 50.
/// These durations are aggregated across all exposures and capped at 30 minutes.
@property (readwrite, copy, nonatomic) NSArray <NSNumber *> *		attenuationDurations;

/// Number of days since the most recent exposure. 0 = today, 1 = yesterday, etc. Only valid if matchedKeyCount > 0.
@property (readonly, assign, nonatomic) NSInteger					daysSinceLastExposure;

/// Number of diagnosis keys that matched.
@property (readonly, assign, nonatomic) uint64_t					matchedKeyCount;

/// Highest risk score of all exposure incidents.
@property (readonly, assign, nonatomic) ENRiskScore					maximumRiskScore;

/// Metadata associated with the summary.
@property (readonly, copy, nullable, nonatomic) NSDictionary *		metadata;

@end

//===========================================================================================================================
/*!	@brief	Key used to generate rolling proximity identifiers.
*/
EN_API_AVAILABLE_EXPORT
@interface ENTemporaryExposureKey : NSObject

/// Key material used to generate Rolling Proximity Identifiers.
@property (readwrite, copy, nonatomic) NSData *					keyData;

/// Duration this key is valid. It's the number of 10-minute windows between key rolling.
@property (readwrite, assign, nonatomic) ENIntervalNumber		rollingPeriod;

/// Interval number when the key's EKRollingPeriod started.
@property (readwrite, assign, nonatomic) ENIntervalNumber		rollingStartNumber;

/// Risk of transmission associated with the person this key came from.
@property (readwrite, assign, nonatomic) ENRiskLevel			transmissionRiskLevel;

@end

#ifdef __cplusplus
}
#endif

NS_ASSUME_NONNULL_END
