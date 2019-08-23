//
//  HKObject.h
//  HealthKit
//
//  Copyright (c) 2014 Apple Inc. All rights reserved.
//

#import <HealthKit/HKDefines.h>
#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@class HKSource;
@class HKSourceRevision;
@class HKDevice;

HK_CLASS_AVAILABLE_IOS_WATCHOS(8_0, 2_0)
@interface HKObject : NSObject <NSSecureCoding>

/*!
 @property      UUID
 @abstract      A unique identifier of the receiver in the HealthKit database.
 */
@property (readonly, strong) NSUUID *UUID;

@property (readonly, strong) HKSource *source NS_DEPRECATED_IOS(8_0, 9_0, "Use sourceRevision");

/*!
 @property      sourceRevision
 @abstract      Represents the revision of the source responsible for saving the receiver.
 */
@property (readonly, strong) HKSourceRevision *sourceRevision HK_AVAILABLE_IOS_WATCHOS(9_0, 2_0);

/*!
 @property      device
 @abstract      Represents the device that generated the data of the receiver.
 */
@property (readonly, strong, nullable) HKDevice *device HK_AVAILABLE_IOS_WATCHOS(9_0, 2_0);

/*!
 @property      metadata
 @abstract      Extra information describing properties of the receiver.
 @discussion    Keys must be NSString and values must be either NSString, NSNumber, NSDate, or
                HKQuantity. See HKMetadata.h for potential metadata keys and values.
 */
@property (readonly, copy, nullable) NSDictionary<NSString *, id> *metadata;

- (instancetype)init NS_UNAVAILABLE;

@end

// Predicate Key Paths
HK_EXTERN NSString * const HKPredicateKeyPathUUID HK_AVAILABLE_IOS_WATCHOS(8_0, 2_0);
HK_EXTERN NSString * const HKPredicateKeyPathSource HK_AVAILABLE_IOS_WATCHOS(8_0, 2_0);
HK_EXTERN NSString * const HKPredicateKeyPathMetadata HK_AVAILABLE_IOS_WATCHOS(8_0, 2_0);
HK_EXTERN NSString * const HKPredicateKeyPathCorrelation HK_AVAILABLE_IOS_WATCHOS(8_0, 2_0);
HK_EXTERN NSString * const HKPredicateKeyPathWorkout HK_AVAILABLE_IOS_WATCHOS(8_0, 2_0);
HK_EXTERN NSString * const HKPredicateKeyPathDevice HK_AVAILABLE_IOS_WATCHOS(9_0, 2_0);
HK_EXTERN NSString * const HKPredicateKeyPathSourceRevision HK_AVAILABLE_IOS_WATCHOS(9_0, 2_0);

NS_ASSUME_NONNULL_END
