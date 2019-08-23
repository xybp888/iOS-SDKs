//
//  HKStatisticsQuery.h
//  HealthKit
//
//  Copyright (c) 2014 Apple Inc. All rights reserved.
//

#import <HealthKit/HKQuery.h>
#import <HealthKit/HKStatistics.h>

NS_ASSUME_NONNULL_BEGIN

@class HKStatistics;

/*!
 @class     HKStatisticsQuery
 @abstract  Calculates statistics on quantity samples matching the given quantity type and predicate.
 */
HK_CLASS_AVAILABLE_IOS_WATCHOS(8_0, 2_0)
@interface HKStatisticsQuery : HKQuery

- (instancetype)initWithQuantityType:(HKQuantityType *)quantityType
             quantitySamplePredicate:(nullable NSPredicate *)quantitySamplePredicate
                             options:(HKStatisticsOptions)options
                   completionHandler:(void(^)(HKStatisticsQuery *query, HKStatistics * _Nullable result, NSError * _Nullable error))handler;

@end

NS_ASSUME_NONNULL_END
