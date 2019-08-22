//
//  HKCumulativeQuantitySeriesSample.h
//  HealthKit
//
//  Copyright © 2018 Apple. All rights reserved.
//

#import <HealthKit/HKQuantitySample.h>

NS_ASSUME_NONNULL_BEGIN

@class HKQuantity;

/*!
 @class         HKCumulativeQuantitySeriesSample
 @abstract      An HKQuantitySample subclass representing a series of cumulative quantity measurements.
 */
HK_EXTERN API_AVAILABLE(ios(12.0), watchos(5.0))
@interface HKCumulativeQuantitySeriesSample : HKQuantitySample

/*!
 @property      sum
 @abstract      The sum of quantities in the series represented by the receiver.
 */
@property (readonly, copy) HKQuantity *sum;

@end

// Predicate Key Paths
HK_EXTERN NSString * const HKPredicateKeyPathSum API_AVAILABLE(ios(12.0), watchos(5.0));

NS_ASSUME_NONNULL_END
