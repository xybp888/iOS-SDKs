/*
 *  CLLocationPushServiceError.h
 *  CoreLocation
 *
 *  Copyright (c) 2021 Apple Inc. All rights reserved.
 *
 */

#import <Foundation/Foundation.h>
#import <CoreLocation/CLAvailability.h>

/*
 *  CLLocationPushServiceErrorDomain
 *
 *  Discussion:
 *    Error returned as the domain to NSError from -[CLLocationManager startMonitoringLocationPushesWithCompletion:].
 *
*/
#if defined(TARGET_OS_VISION) && TARGET_OS_VISION
CL_EXTERN NSErrorDomain const CLLocationPushServiceErrorDomain API_AVAILABLE(ios(15.0)) API_UNAVAILABLE(watchos, tvos, macos, macCatalyst, visionos);
#else
CL_EXTERN NSErrorDomain const CLLocationPushServiceErrorDomain API_AVAILABLE(ios(15.0)) API_UNAVAILABLE(watchos, tvos, macos, macCatalyst);
#endif

/*
 *  CLLocationPushServiceError
 *
 *  Discussion:
 *    Error returned as code to NSError from -[CLLocationManager startMonitoringLocationPushesWithCompletion:].
 */
typedef NS_ERROR_ENUM(CLLocationPushServiceErrorDomain, CLLocationPushServiceError) {
	CLLocationPushServiceErrorUnknown = 0,
	CLLocationPushServiceErrorMissingPushExtension = 1,	             // App is lacking a Location Push Service Extension
	CLLocationPushServiceErrorMissingPushServerEnvironment = 2,      // App is lacking APNS environment
	CLLocationPushServiceErrorMissingEntitlement = 3,                // App is lacking the com.apple.developer.location.push entitlement
	CLLocationPushServiceErrorUnsupportedPlatform = 4,				 // App is running on an unsupported platform
#if defined(TARGET_OS_VISION) && TARGET_OS_VISION
} API_AVAILABLE(ios(15.0)) API_UNAVAILABLE(watchos, tvos, macos, macCatalyst, visionos);
#else
} API_AVAILABLE(ios(15.0)) API_UNAVAILABLE(watchos, tvos, macos, macCatalyst);
#endif
