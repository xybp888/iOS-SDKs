//
//  HKCorrelation.h
//  HealthKit
//
//  Copyright (c) 2014 Apple Inc. All rights reserved.
//

#import <HealthKit/HKSample.h>

NS_ASSUME_NONNULL_BEGIN

@class HKObjectType;
@class HKCorrelationType;

/*!
 @class         HKCorrelation
 @abstract      An HKCorrelation is a collection of correlated objects.
 @discussion    When multiple readings are taken together, it may be beneficial to correlate them so that they can be
                displayed together and share common metadata about how they were created.
 
                For example, systolic and diastolic blood pressure readings are typically presented together so these
                readings should be saved with a correlation of type blood pressure.
 */
HK_CLASS_AVAILABLE_IOS(8_0)
@interface HKCorrelation : HKSample

@property (readonly) HKCorrelationType *correlationType;

/*!
 @property  objects
 @abstract  A set of HKSamples containing all of the objects that were saved with the receiver.
 */
@property (readonly, copy) NSSet<__kindof HKSample *> *objects;

/*!
 @method        correlationWithType:startDate:endDate:objects:
 @abstract      Creates a new HKCorrelation with the given type, start date, end date, and objects.
 @discussion    objects must be a set of HKQuantitySamples and HKCategorySamples
 */
+ (instancetype)correlationWithType:(HKCorrelationType *)correlationType
                          startDate:(NSDate *)startDate
                            endDate:(NSDate *)endDate
                            objects:(NSSet<HKSample *> *)objects;

/*!
 @method        correlationWithType:startDate:endDate:objects:metadata:
 @abstract      Creates a new HKCorrelation with the given type, start date, end date, objects, and metadata.
 @discussion    objects must be a set of HKQuantitySamples and HKCategorySamples
 */
+ (instancetype)correlationWithType:(HKCorrelationType *)correlationType
                          startDate:(NSDate *)startDate
                            endDate:(NSDate *)endDate
                            objects:(NSSet<HKSample *> *)objects
                           metadata:(nullable NSDictionary<NSString *, id> *)metadata;

/*!
 @method        correlationWithType:startDate:endDate:objects:device:metadata:
 @abstract      Creates a new HKCorrelation with the given type, start date, end date, objects, and metadata.
 @param         type        The correlation type of the objects set.
 @param         startDate   The start date of the correlation.
 @param         endDate     The end date of the correlation.
 @param         device      The HKDevice that generated the samples (optional).
 @param         metadata    Metadata for the correlation (optional).
 @discussion    objects must be a set of HKQuantitySamples and HKCategorySamples
 */
+ (instancetype)correlationWithType:(HKCorrelationType *)correlationType
                          startDate:(NSDate *)startDate
                            endDate:(NSDate *)endDate
                            objects:(NSSet<HKSample *> *)objects
                             device:(nullable HKDevice *)device
                           metadata:(nullable NSDictionary<NSString *, id> *)metadata NS_AVAILABLE_IOS(9_0);

/*!
 @method    objectsForType:
 @abstract  Returns the set of correlated objects with the specified type.
 */
- (NSSet<__kindof HKSample *> *)objectsForType:(HKObjectType *)objectType;

@end

NS_ASSUME_NONNULL_END
