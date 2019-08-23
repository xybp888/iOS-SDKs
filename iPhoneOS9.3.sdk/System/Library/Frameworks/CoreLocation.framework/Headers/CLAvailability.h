/*
 *  CLAvailability.h
 *  CoreLocation
 *
 *  Copyright 2011 Apple Inc. All rights reserved.
 *
 */

/*
#ifndef __CL_INDIRECT__
#error "Please #include <CoreLocation/CoreLocation.h> instead of this file directly."
#endif // __CL_INDIRECT__
*/

#import <Availability.h>

#ifndef __MAC_TBD
#define __MAC_TBD __MAC_NA
#endif

#ifndef __AVAILABILITY_INTERNAL__MAC_TBD
#define __AVAILABILITY_INTERNAL__MAC_TBD __AVAILABILITY_INTERNAL_UNAVAILABLE
#endif

#ifndef __TVOS_PROHIBITED
#define __TVOS_PROHIBITED
#endif

#ifndef __WATCHOS_PROHIBITED
#define __WATCHOS_PROHIBITED
#endif

#ifdef __cplusplus
#define CL_EXTERN extern "C" __attribute__((visibility ("default")))
#else
#define CL_EXTERN extern __attribute__((visibility ("default")))
#endif
