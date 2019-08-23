//
//  HKCharacteristicObjects.h
//  HealthKit
//
//  Copyright © 2016 Apple. All rights reserved.
//

#import <HealthKit/HKDefines.h>

#import <Foundation/Foundation.h>

/*!
 @class     HKBiologicalSexObject
 @abstract  A wrapper object for HKBiologicalSex enumeration.
 */
HK_CLASS_AVAILABLE_IOS_WATCHOS(8_0, 2_0)
@interface HKBiologicalSexObject : NSObject <NSCopying, NSSecureCoding>

@property (readonly) HKBiologicalSex biologicalSex;

@end

/*!
 @class     HKBloodTypeObject
 @abstract  A wrapper object for HKBloodType enumeration.
 */
HK_CLASS_AVAILABLE_IOS_WATCHOS(8_0, 2_0)
@interface HKBloodTypeObject : NSObject <NSCopying, NSSecureCoding>

@property (readonly) HKBloodType bloodType;

@end

/*!
 @class     HKFitzpatrickSkinTypeObject
 @abstract  A wrapper object for HKFitzpatrickSkinType enumeration.
 */
HK_CLASS_AVAILABLE_IOS_WATCHOS(9_0, 2_0)
@interface HKFitzpatrickSkinTypeObject : NSObject <NSCopying, NSSecureCoding>

@property (readonly) HKFitzpatrickSkinType skinType;

@end

/*!
 @class     HKWheelchairUseObject
 @abstract  A wrapper object for HKWheelchairUse enumeration.
 */
HK_CLASS_AVAILABLE_IOS_WATCHOS(10_0, 3_0)
@interface HKWheelchairUseObject : NSObject <NSCopying, NSSecureCoding>

@property (readonly) HKWheelchairUse wheelchairUse;

@end
