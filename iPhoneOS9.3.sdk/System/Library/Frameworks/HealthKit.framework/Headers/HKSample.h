//
//  HKSample.h
//  HealthKit
//
//  Copyright (c) 2014 Apple Inc. All rights reserved.
//

#import <HealthKit/HKObject.h>

NS_ASSUME_NONNULL_BEGIN

@class HKSampleType;

/*!
 @class         HKSample
 @abstract      An abstract class representing measurements taken over a period of time.
 */
HK_CLASS_AVAILABLE_IOS(8_0)
@interface HKSample : HKObject

@property (readonly, strong) HKSampleType *sampleType;

@property (readonly, strong) NSDate *startDate;
@property (readonly, strong) NSDate *endDate;

@end

// Sort Identifiers
HK_EXTERN NSString * const HKSampleSortIdentifierStartDate NS_AVAILABLE_IOS(8_0);
HK_EXTERN NSString * const HKSampleSortIdentifierEndDate NS_AVAILABLE_IOS(8_0);

// Predicate Key Paths
HK_EXTERN NSString * const HKPredicateKeyPathStartDate NS_AVAILABLE_IOS(8_0);
HK_EXTERN NSString * const HKPredicateKeyPathEndDate NS_AVAILABLE_IOS(8_0);

NS_ASSUME_NONNULL_END
