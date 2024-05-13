//
//  CPLane.h
//  CarPlay
//
//  Copyright © 2023 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

typedef NS_ENUM(NSInteger, CPLaneStatus)
{
    CPLaneStatusNotGood = 0,
    CPLaneStatusGood,
    CPLaneStatusPreferred
} API_AVAILABLE(ios(17.4));

NS_ASSUME_NONNULL_BEGIN

/**
 @c CPLane represents information about a single lane.
 */
API_AVAILABLE(ios(17.4))
@interface CPLane : NSObject <NSCopying, NSSecureCoding>

/**
 status is a @c CPLaneStatus representing the status of this lane.
 */
@property (nonatomic, assign) CPLaneStatus status API_AVAILABLE(ios(17.4));

/**
 primaryAngle is the angle to be highlighted if this lane is preferred or good. If primaryAngle is present it can not be included in secondaryAngles.
 */
@property (nonatomic, strong) NSMeasurement<NSUnitAngle *> *primaryAngle API_AVAILABLE(ios(17.4));

/**
 secondaryAngles is a list of the remaining angles of this lane guidance.
 */
@property (nonatomic, strong) NSArray<NSMeasurement<NSUnitAngle *> *> *secondaryAngles API_AVAILABLE(ios(17.4));
@end

NS_ASSUME_NONNULL_END
