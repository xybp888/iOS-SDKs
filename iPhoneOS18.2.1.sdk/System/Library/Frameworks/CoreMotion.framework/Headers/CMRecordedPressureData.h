//
//  CMRecordedPressureData.h
//  CMRecordedPressureData
//
//  Copyright (c) 2021 Apple Inc. All rights reserved.
//


#import <Foundation/Foundation.h>
#import <CoreMotion/CMAmbientPressure.h>

NS_ASSUME_NONNULL_BEGIN

/*
 * CMRecordedPressureData
 *
 * Discussion:
 *   CMRecordedPressureData contains data for each pressure sample.
 */
#if defined(TARGET_OS_VISION) && TARGET_OS_VISION
COREMOTION_EXPORT API_AVAILABLE(ios(12.0), watchos(5.0)) API_UNAVAILABLE(macos) API_UNAVAILABLE(visionos)
#else
COREMOTION_EXPORT API_AVAILABLE(ios(12.0), watchos(5.0)) API_UNAVAILABLE(macos)
#endif // defined(TARGET_OS_VISION) && TARGET_OS_VISION
@interface CMRecordedPressureData : CMAmbientPressureData

/*
 * identifier
 *
 * Discussion:
 *   Unique identifier that identifies the batch for which the pressure sample
 *   was recorded in. This identifier will be monotonically increased
 *   for each new sensor batch recorded and can be used as an anchor for future queries.
 */
@property (readonly) uint64_t identifier;

/*
 * startDate
 *
 * Discussion:
 *   Wall time for when this sensor sample is recorded.
 *
 */
@property (readonly) NSDate *startDate;

@end

NS_ASSUME_NONNULL_END


