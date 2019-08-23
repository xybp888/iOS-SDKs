//
//  HKObjectType.h
//  HealthKit
//
//  Copyright (c) 2013-2014 Apple Inc. All rights reserved.
//

#import <HealthKit/HKDefines.h>
#import <HealthKit/HKTypeIdentifiers.h>

NS_ASSUME_NONNULL_BEGIN

@class HKActivitySummaryType;
@class HKCategoryType;
@class HKCharacteristicType;
@class HKCorrelationType;
@class HKDocumentType;
@class HKQuantityType;
@class HKUnit;
@class HKWorkoutType;

/*!
 @class         HKObjectType
 @abstract      An abstract class representing a type of object that can be stored by HealthKit.
 */
HK_CLASS_AVAILABLE_IOS_WATCHOS(8_0, 2_0)
@interface HKObjectType : NSObject <NSSecureCoding, NSCopying>

/*!
 @property      identifier
 @abstract      A unique string identifying a type of health object.
 @discussion    See HKTypeIdentifiers.h for possible values.
 */
@property (readonly, strong) NSString *identifier;

- (instancetype)init NS_UNAVAILABLE;

+ (nullable HKQuantityType *)quantityTypeForIdentifier:(HKQuantityTypeIdentifier)identifier;
+ (nullable HKCategoryType *)categoryTypeForIdentifier:(HKCategoryTypeIdentifier)identifier;
+ (nullable HKCharacteristicType *)characteristicTypeForIdentifier:(HKCharacteristicTypeIdentifier)identifier;
+ (nullable HKCorrelationType *)correlationTypeForIdentifier:(HKCorrelationTypeIdentifier)identifier;
+ (nullable HKDocumentType *)documentTypeForIdentifier:(HKDocumentTypeIdentifier)identifier HK_AVAILABLE_IOS_WATCHOS(10_0, 3_0);
+ (HKWorkoutType *)workoutType;
+ (HKActivitySummaryType *)activitySummaryType HK_AVAILABLE_IOS_WATCHOS(9_3, 2_2);

@end

/*!
 @class         HKCharacteristicType
 @abstract      Represents a type of object that describes a characteristic of the user (such as date of birth).
 */
HK_CLASS_AVAILABLE_IOS_WATCHOS(8_0, 2_0)
@interface HKCharacteristicType : HKObjectType
@end

/*!
 @class         HKSampleType
 @abstract      Represents a type of HKSample.
 */
HK_CLASS_AVAILABLE_IOS_WATCHOS(8_0, 2_0)
@interface HKSampleType : HKObjectType
@end

/*!
 @class         HKCategoryType
 @abstract      Represent a type of HKCategorySample.
 */
HK_CLASS_AVAILABLE_IOS_WATCHOS(8_0, 2_0)
@interface HKCategoryType : HKSampleType
@end

/*!
 @class         HKCorrelationType
 @abstract      Represents a type of HKCorrelation
 */
HK_CLASS_AVAILABLE_IOS_WATCHOS(8_0, 2_0)
@interface HKCorrelationType : HKSampleType
@end

/*!
 @enum          HKQuantityAggregationStyle
 @discussion    Describes how quantities can be aggregated over time.
 
 @constant      HKQuantityAggregationStyleCumulative    Samples may be summed over a time interval.
 @constant      HKQuantityAggregationStyleDiscrete      Samples may be averaged over a time interval.
 */
typedef NS_ENUM(NSInteger, HKQuantityAggregationStyle) {
    HKQuantityAggregationStyleCumulative = 0,
    HKQuantityAggregationStyleDiscrete,
} HK_ENUM_AVAILABLE_IOS_WATCHOS(8_0, 2_0);

/*!
 @class         HKDocumentType
 @abstract      Represents a type of HKDocument.
 */
HK_CLASS_AVAILABLE_IOS_ONLY(10_0)
@interface HKDocumentType : HKSampleType
@end

/*!
 @class         HKQuantityType
 @abstract      Represents types of HKQuantitySamples.
 */
HK_CLASS_AVAILABLE_IOS_WATCHOS(8_0, 2_0)
@interface HKQuantityType : HKSampleType

@property (readonly) HKQuantityAggregationStyle aggregationStyle;

/*!
 @method        isCompatibleWithUnit:
 @abstract      Returns YES if the type of HKQuantitySample represented by the receiver can be created with quantities 
                of the given unit.
 */
- (BOOL)isCompatibleWithUnit:(HKUnit *)unit;

@end

/*!
 @class         HKCategoryType
 @abstract      Represents a workout or exercise
 */
HK_CLASS_AVAILABLE_IOS_WATCHOS(8_0, 2_0)
@interface HKWorkoutType : HKSampleType
@end

/*!
 @class         HKActivitySummaryType
 @abstract      Represents an HKActivitySummary
 */
HK_CLASS_AVAILABLE_IOS_WATCHOS(9_3, 2_2)
@interface HKActivitySummaryType : HKObjectType
@end


NS_ASSUME_NONNULL_END
