//
//  HKAnchoredObjectQuery.h
//  HealthKit
//
//  Copyright (c) 2014 Apple Inc. All rights reserved.
//

#import <HealthKit/HKQuery.h>

@class HKDeletedObject;

NS_ASSUME_NONNULL_BEGIN

#define HKAnchoredObjectQueryNoAnchor (0)

/*!
 @class         HKQueryAnchor
 @discussion    This object encapsulates the state of an HKAnchoredObjectQuery
 */
HK_CLASS_AVAILABLE_IOS(9_0)
@interface HKQueryAnchor : NSObject <NSSecureCoding, NSCopying>

/*!
 @method        anchorFromValue:
 @discussion    Creates an HKQueryAnchor with an integer anchor which was previously obtained from an HKAnchoredObjectQuery prior to iOS 9.0.
 */
+ (instancetype)anchorFromValue:(NSUInteger)value;

- (instancetype)init NS_UNAVAILABLE;

@end

/*!
 @class         HKAnchoredObjectQuery
 @discussion    This query can be used by an application to find out about new or deleted samples in the HealthKit
                database.
 */
HK_CLASS_AVAILABLE_IOS(8_0)
@interface HKAnchoredObjectQuery : HKQuery

/*!
 @property      updateHandler
 @abstract      An optional handler to be called when samples matching the given predicate are added or deleted.
 @discussion    This property may not be modified once the query has been executed.  It may only be set if the query has
                no limit.
 */
@property (nonatomic, copy, nullable) void(^updateHandler)(HKAnchoredObjectQuery *query, NSArray<__kindof HKSample *> * __nullable addedObjects, NSArray<HKDeletedObject *> * __nullable deletedObjects, HKQueryAnchor * __nullable newAnchor, NSError * __nullable error) NS_AVAILABLE_IOS(9_0);

- (instancetype)initWithType:(HKSampleType *)type
                   predicate:(nullable NSPredicate *)predicate
                      anchor:(NSUInteger)anchor
                       limit:(NSUInteger)limit
           completionHandler:(void(^)(HKAnchoredObjectQuery *query, NSArray<__kindof HKSample *> * __nullable results, NSUInteger newAnchor, NSError * __nullable error))handler NS_DEPRECATED_IOS(8_0, 9_0);

/*!
 @method        initWithType:predicate:anchor:limit:resultsHandler:
 @abstract      Returns a query that will retrieve HKSamples and HKDeletedObjects matching the given predicate that are
                newer than the given anchor.
 @discussion    If no updateHandler is set on the query, the query will automatically stop after calling resultsHandler.
                Otherwise, the query continues to run and call updateHandler as samples matching the predicate are
                created or deleted.
 
 @param         type            The type of sample to retrieve.
 @param         predicate       The predicate which samples should match.
 @param         anchor          The anchor which was returned by a previous HKAnchoredObjectQuery result or update
                                handler.  Pass nil when querying for the first time.
 @param         limit           The maximum number of samples and deleted objects to return.  Pass HKObjectQueryNoLimit
                                for no limit.
 @param         resultsHandler  The block to invoke with results when the query has finished finding.
 */
- (instancetype)initWithType:(HKSampleType *)type
                   predicate:(nullable NSPredicate *)predicate
                      anchor:(nullable HKQueryAnchor *)anchor
                       limit:(NSUInteger)limit
              resultsHandler:(void(^)(HKAnchoredObjectQuery *query, NSArray<__kindof HKSample *> * __nullable sampleObjects, NSArray<HKDeletedObject *> * __nullable deletedObjects, HKQueryAnchor * __nullable newAnchor, NSError * __nullable error))handler NS_AVAILABLE_IOS(9_0);

@end

NS_ASSUME_NONNULL_END
