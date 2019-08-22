//
//  HKQuantitySeriesSampleQuery.h
//  HealthKit
//
//  Copyright © 2018 Apple. All rights reserved.
//

#import <HealthKit/HKQuery.h>

NS_ASSUME_NONNULL_BEGIN

@class HKQuantity;
@class HKQuantitySample;

/*!
 @class         HKQuantitySeriesSampleQuery
 @abstract      An HKQuantitySeriesSampleQuery is used to access series data associated with an
                HKQuantitySample.
 @discussion    Once instantiated, call -[HKHealthStore executeQuery:] to begin enumerating the series data.
                Call -[HKHealthStore stopQuery:] to discontinue further quantity data reporting.
 */
HK_EXTERN API_AVAILABLE(ios(12.0), watchos(5.0))
@interface HKQuantitySeriesSampleQuery : HKQuery

/*!
 @method        initWithSample:dataHandler:
 @abstract      Returns a query that will retrieve HKQuantity objects for the specified sample.
 
 @param         quantitySample      The HKQuantitySample for which the quantity data will
                                    be returned.
 @param         quantityHandler     The block to invoke with results from the query. It will be
                                    called repeatedly with HKQuantity and NSDate objects,
                                    in ascending date order, until all quantities are returned and
                                    the done parameter is YES or -[HKHealthStore stopQuery:] is called.
                                    The stopQuery call can be made within the quantityHandler block.
                                    Once done is YES, or stopQuery has been called, the query is
                                    complete and no more calls to quantityHandler will be made.
 */
- (instancetype)initWithSample:(HKQuantitySample *)quantitySample
               quantityHandler:(void(^)(HKQuantitySeriesSampleQuery *query, HKQuantity * _Nullable quantity, NSDate * _Nullable date, BOOL done, NSError * _Nullable error))quantityHandler NS_DESIGNATED_INITIALIZER;

@end

NS_ASSUME_NONNULL_END
