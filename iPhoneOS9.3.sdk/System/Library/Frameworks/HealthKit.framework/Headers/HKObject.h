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

HK_CLASS_AVAILABLE_IOS(8_0)
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
@property (readonly, strong) HKSourceRevision *sourceRevision NS_AVAILABLE_IOS(9_0);

/*!
 @property      device
 @abstract      Represents the device that generated the data of the receiver.
 */
@property (readonly, strong, nullable) HKDevice *device NS_AVAILABLE_IOS(9_0);

/*!
 @property      metadata
 @abstract      Extra information describing properties of the receiver.
 @discussion    Keys must be NSString and values must be either NSString, NSNumber, or NSDate.
                See HKMetadata.h for potential metadata keys and values.
 */
@property (readonly, copy, nullable) NSDictionary<NSString *, id> *metadata;

- (instancetype)init NS_UNAVAILABLE;

@end

// Predicate Key Paths
HK_EXTERN NSString * const HKPredicateKeyPathUUID NS_AVAILABLE_IOS(8_0);
HK_EXTERN NSString * const HKPredicateKeyPathSource NS_AVAILABLE_IOS(8_0);
HK_EXTERN NSString * const HKPredicateKeyPathMetadata NS_AVAILABLE_IOS(8_0);
HK_EXTERN NSString * const HKPredicateKeyPathCorrelation NS_AVAILABLE_IOS(8_0);
HK_EXTERN NSString * const HKPredicateKeyPathWorkout NS_AVAILABLE_IOS(8_0);
HK_EXTERN NSString * const HKPredicateKeyPathDevice NS_AVAILABLE_IOS(9_0);
HK_EXTERN NSString * const HKPredicateKeyPathSourceRevision NS_AVAILABLE_IOS(9_0);

NS_ASSUME_NONNULL_END
