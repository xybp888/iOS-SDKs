/*
 *  CMBody.h
 *  CoreMotion
 *
 *  Copyright (c) 2026 Apple Inc. All rights reserved.
 *
 */

#import <Foundation/Foundation.h>
#import <CoreMotion/CMAvailability.h>

NS_ASSUME_NONNULL_BEGIN

/*
 *  CMBodyIdentifiable
 *
 *  Discussion:
 *      A protocol that objects adopt to identify a body for device motion calculations.
 *
 */
COREMOTION_EXPORT API_AVAILABLE(ios(27.0), macos(27.0), watchos(27.0), tvos(27.0), visionos(27.0))
@protocol CMBodyIdentifiable <NSObject>
@end

NS_ASSUME_NONNULL_END
