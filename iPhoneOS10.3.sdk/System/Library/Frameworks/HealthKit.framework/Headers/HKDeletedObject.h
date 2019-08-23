//
//  HKDeletedObject.h
//  HealthKit
//
//  Copyright (c) 2015 Apple. All rights reserved.
//

#import <HealthKit/HKDefines.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 @class         HKDeletedObject
 @abstract      A class representing an HKObject that was deleted from the HealtKit database.
 */
HK_CLASS_AVAILABLE_IOS_WATCHOS(9_0, 2_0)
@interface HKDeletedObject : NSObject <NSSecureCoding>

/*!
 @property      UUID
 @abstract      The unique identifier of the HKObject that was deleted from the HealthKit database.
 */
@property (readonly, strong) NSUUID *UUID;

- (instancetype)init NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
