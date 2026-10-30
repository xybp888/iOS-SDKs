/*
 *  CLBody.h
 *  CoreLocation
 *
 *  Copyright 2026 Apple, Inc. All rights reserved.
 *
 */

#import <CoreLocation/CLAvailability.h>
#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/*
 *  CLBodyIdentifiable
 *
 *  Discussion:
 *      A protocol that objects adopt to identify a body for heading calculations.
 *
 */
CL_EXTERN
API_AVAILABLE(ios(27.0), macos(27.0), watchos(27.0), tvos(27.0), visionos(27.0))
@protocol CLBodyIdentifiable <NSObject>
@end

NS_ASSUME_NONNULL_END
