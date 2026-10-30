/*
 *  CMRecordedDeviceMotion.h
 *  CoreMotion
 *
 *  Copyright (c) 2025 Apple Inc. All rights reserved.
 *
 */

#import <CoreMotion/CMDeviceMotion.h>

NS_ASSUME_NONNULL_BEGIN

/*
 * CMRecordedDeviceMotion
 *
 * Discussion:
 *   CMRecordedDeviceMotion contains historical device motion data that has been
 *   recorded for later retrieval. This class extends CMDeviceMotion to support
 *   passively collected motion data, including data from accessories such as
 *   headphones.
 */
COREMOTION_EXPORT API_AVAILABLE(ios(27), watchos(27), macos(27), visionos(27)) API_UNAVAILABLE(tvos)
@interface CMRecordedDeviceMotion : CMDeviceMotion

/*
 * identifier
 *
 * Discussion:
 *   Unique identifier that identifies the batch for which the device motion sample
 *   was recorded in. This identifier will be monotonically increased for each new
 *   sensor batch recorded and can be used as an anchor for future queries.
 */
@property (readonly) uint64_t identifier;

/*
 * startDate
 *
 * Discussion:
 *   The date and time when this device motion sample was observed.
 */
@property (readonly) NSDate *startDate;

@end

NS_ASSUME_NONNULL_END
