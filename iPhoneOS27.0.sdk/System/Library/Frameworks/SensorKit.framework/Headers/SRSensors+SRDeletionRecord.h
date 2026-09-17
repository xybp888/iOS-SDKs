//
//  SRSensors+SRDeletionRecord.h
//  SensorKit
//
//  Copyright © 2019 Apple Inc. All rights reserved.
//

#import <SensorKit/SRSensors.h>

NS_ASSUME_NONNULL_BEGIN

#ifdef __swift__
API_DEPRECATED("Use deletionRecords(matching request: SRFetchRequest) of SRReader<Sensor> class", ios(14.0, 27.0)) API_UNAVAILABLE(watchos, visionos) API_UNAVAILABLE(tvos, macos)
#else
SR_EXTERN API_AVAILABLE(ios(14.0)) API_UNAVAILABLE(watchos, visionos) API_UNAVAILABLE(tvos, macos)
#endif
@interface NSString (SRDeletionRecord)
/**
 * @brief Returns a sensor stream that contains deletion records of the sensor
 *
 * @discussion This sensor stream should only be used for fetching. All other
 * operations will be ignored. Deletion records share the recording and authorization
 * state with their parent sensor.
 *
 * @return May return nil if there is no deletion record available for this sensor
 */
- (nullable SRSensor)sr_sensorForDeletionRecordsFromSensor;
@end

NS_ASSUME_NONNULL_END
