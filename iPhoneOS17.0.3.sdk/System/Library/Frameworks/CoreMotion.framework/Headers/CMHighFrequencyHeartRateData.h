//
//  CMHighFrequencyHeartRateData.h
//  CoreMotion
//
//  Copyright (c) 2022 Apple Inc. All rights reserved.
//

#ifndef CMHighFrequencyHeartRateData_h
#define CMHighFrequencyHeartRateData_h

#import <CoreMotion/CMAvailability.h>
#import <CoreMotion/CMLogItem.h>

/*
 *  CMHighFrequencyHeartRateDataConfidence
 *  Confidence categories for heart rate values.
 */
typedef NS_ENUM(NSInteger, CMHighFrequencyHeartRateDataConfidence) {
	CMHighFrequencyHeartRateDataConfidenceLow = 0,
	CMHighFrequencyHeartRateDataConfidenceMedium,
	CMHighFrequencyHeartRateDataConfidenceHigh,
	CMHighFrequencyHeartRateDataConfidenceHighest
} API_AVAILABLE(ios(17.0), watchos(10.0)) API_UNAVAILABLE(macos, tvos);


/*
 *  CMHighFrequencyHeartRateData
 *  Heart rate data collected at 1Hz.
 */
#if defined(TARGET_OS_VISION) && TARGET_OS_VISION
COREMOTION_EXPORT API_AVAILABLE(ios(17.0), watchos(10.0)) API_UNAVAILABLE(macos, tvos) API_UNAVAILABLE(visionos)
#else
COREMOTION_EXPORT API_AVAILABLE(ios(17.0), watchos(10.0)) API_UNAVAILABLE(macos, tvos)
#endif // defined(TARGET_OS_VISION) && TARGET_OS_VISION
@interface CMHighFrequencyHeartRateData : CMLogItem

/*
 *  heartRate
 *  The heart rate value in units of beats per minute (BPM)
 */
@property (readonly, nonatomic) double heartRate;

/*
 *  confidence
 *  Indicates the confidence level of the heart rate value
 */
@property (readonly, nonatomic) CMHighFrequencyHeartRateDataConfidence confidence;

/*
 *  date
 *  Corresponding date for the heart rate value
 */
@property (readonly, nonatomic, nullable) NSDate *date;

@end

#endif /* CMHighFrequencyHeartRateData_h */
