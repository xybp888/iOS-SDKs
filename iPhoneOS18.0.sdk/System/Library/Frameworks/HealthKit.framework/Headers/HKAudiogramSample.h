//
//  HKAudiogramSample.h
//  HealthKit
//
//  Copyright © 2017-2024 Apple. All rights reserved.
//



#import <HealthKit/HKQuantity.h>
#import <HealthKit/HKSample.h>

NS_ASSUME_NONNULL_BEGIN

@class HKAudiogramSensitivityPoint;

/*!
 @class     HKAudiogramSample
 @abstract  A sample object representing the results of a standard hearing test.
 */
HK_EXTERN API_AVAILABLE(ios(13.0), watchos(6.0), macCatalyst(13.0), macos(13.0))
@interface HKAudiogramSample : HKSample

/*!
 @property  sensitivityPoints
 @abstract  The hearing sensitivity readings associated with a hearing test.
 */
@property (readonly, copy) NSArray<HKAudiogramSensitivityPoint *> *sensitivityPoints;
/*!
 @method                   audiogramSampleWithSensitivityPoints:startDate:endDate:metadata:
 @abstract                 Creates a new audiogram sample with the specified attributes.
 @param sensitivityPoints  Sensitivity data associated with the sample, with a maximum limit of 30 points. Frequencies must be unique, and ordered ascending.
 @param startDate          The start date for the hearing test.
 @param endDate            The end date for the hearing test.
 @param metadata           Optional meta data associated with the sample.
 @return                   A new instance of an audiogram sample.
 */
+ (instancetype)audiogramSampleWithSensitivityPoints:(NSArray<HKAudiogramSensitivityPoint *> *)sensitivityPoints
                                           startDate:(NSDate *)startDate
                                             endDate:(NSDate *)endDate
                                            metadata:(nullable NSDictionary<NSString *, id> *)metadata;


@end

NS_ASSUME_NONNULL_END

