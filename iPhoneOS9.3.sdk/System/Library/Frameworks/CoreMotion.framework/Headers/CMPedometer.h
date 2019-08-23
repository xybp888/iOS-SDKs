/*
 *  CMPedometer.h
 *  CoreMotion
 *
 *  Copyright (c) 2013 Apple Inc. All rights reserved.
 *
 */

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/*
 *  CMPedometerData
 *
 *  Discussion:
 *      A description of the user's pedestrian activity. At a minimum this
 *      object contains a step count. On supported platforms it also contains
 *      distance, flights of stairs, pace, and cadence.
 */
NS_CLASS_AVAILABLE(NA, 8_0) __TVOS_PROHIBITED
@interface CMPedometerData : NSObject <NSSecureCoding, NSCopying>

/*
 *  startDate
 *
 *  Discussion:
 *      The start time of the period for which the pedometer data is valid.
 *
 *      This is the start time requested for the session or historical query.
 */
@property(readonly, nonatomic) NSDate *startDate;

/*
 *  endDate
 *
 *  Discussion:
 *      The end time of the period for which the pedometer data is valid.
 *
 *      For updates this is the time for the most recent update. For historical
 *      queries this is the end time requested.
 */
@property(readonly, nonatomic) NSDate *endDate;

/*
 *  numberOfSteps
 *
 *  Discussion:
 *      Number of steps taken by the user.
 */
@property(readonly, nonatomic) NSNumber *numberOfSteps;

/*
 *  distance
 *
 *  Discussion:
 *      Estimated distance in meters traveled by the user while walking and
 *      running. Value is nil unsupported platforms.
 */
@property(readonly, nonatomic, nullable) NSNumber *distance;

/*
 *  floorsAscended
 *
 *  Discussion:
 *      Approximate number of floors ascended by way of stairs. Value is nil
 *      on unsupported platforms.
 *
 */
@property(readonly, nonatomic, nullable) NSNumber *floorsAscended;

/*
 *  floorsDescended
 *
 *  Discussion:
 *      Approximate number of floors descended by way of stairs. Value is nil
 *      on unsupported platforms.
 */
@property(readonly, nonatomic, nullable) NSNumber *floorsDescended;

/*
 * currentPace
 *
 *
 * Discussion:
 *      For updates this returns the current pace, in s/m (seconds per meter).
 *      Value is nil if any of the following are true:
 *
 *         (1) Information not yet available;
 *         (2) Historical query;
 *         (3) Unsupported platform.
 *
 */
@property(readonly, nonatomic, nullable) NSNumber *currentPace NS_AVAILABLE(NA,9_0);

/*
 * currentCadence
 *
 *
 * Discussion:
 *      For updates this returns the rate at which steps are taken, in steps per second.
 *      Value is nil if any of the following are true:
 *
 *         (1) Information not yet available;
 *         (2) Historical query;
 *         (3) Unsupported platform.
 *
 */
@property(readonly, nonatomic, nullable) NSNumber *currentCadence NS_AVAILABLE(NA,9_0);

@end

/*
 *  CMPedometerHandler
 *
 *  Discussion:
 *      Typedef of block to be invoked when pedometer data is available. Error
 *      types are defined in "CMError.h".
 */
typedef void (^CMPedometerHandler)(CMPedometerData * __nullable pedometerData, NSError * __nullable error) __TVOS_PROHIBITED;

/*
 *  CMPedometer
 *
 *  Discussion:
 *      CMPedometer allows access to the user's pedestrian activity. The
 *      activity can be retrieved in one of two ways:
 *
 *      1. Via a query specifying a time range from which the pedometer data is
 *      tabulated and returned.
 *      (See queryPedometerDataFromDate:toDate:withHandler:)
 *
 *      2. By providing a block to startPedometerUpdatesFromDate:withHandler:,
 *      pedometer updates will be provided on a best effort basis. Pedometer
 *      updates can be stopped by calling stopPedometerUpdates.
 *
 */
NS_CLASS_AVAILABLE(NA,8_0) __TVOS_PROHIBITED
@interface CMPedometer : NSObject

/*
 *  isStepCountingAvailable
 *
 *  Discussion:
 *      Determines whether the device supports step counting functionality.
 */
+ (BOOL)isStepCountingAvailable;

/*
 *  isDistanceAvailable
 *
 *  Discussion:
 *      Determines whether the device supports distance estimation
 *      in addition to step counting.
 */
+ (BOOL)isDistanceAvailable;

/*
 *  isFloorCountingAvailable
 *
 *  Discussion:
 *      Determines whether the device supports counting flights of stairs
 *      in addition to step counting.
 */
+ (BOOL)isFloorCountingAvailable;

/*
 *  isPaceAvailable
 *
 *  Discussion:
 *      Determines whether the device supports pace estimation
 *      in addition to step counting.
 */
+ (BOOL)isPaceAvailable NS_AVAILABLE(NA,9_0);

/*
 *  isCadenceAvailable
 *
 *  Discussion:
 *      Determines whether the device supports cadence estimation
 *      in addition to step counting.
 */
+ (BOOL)isCadenceAvailable NS_AVAILABLE(NA,9_0);

/*
 *  queryPedometerDataFromDate:toDate:withHandler:
 *
 *  Discussion:
 *      Queries for the user's pedestrian activity in the given time range. Data
 *      is available for up to 7 days. The data returned is computed from a
 *      system-wide history that is continuously being collected in the
 *      background. The result is returned on a serial queue.
 */
- (void)queryPedometerDataFromDate:(NSDate *)start
							toDate:(NSDate *)end
					   withHandler:(CMPedometerHandler)handler;

/*
 *  startPedometerUpdatesFromDate:withHandler:
 *
 *  Discussion:
 *      Starts a series of continuous pedometer updates to the
 *      handler on a serial queue. For each update, the app
 *      will receive the cumulative pedestrian activity since the
 *      start date specified and the timestamp associated with the
 *      latest determination. If the app is backgrounded and resumed
 *      at a later time, the app will receive all of the pedestrian
 *      activity accumulated during the background period in the
 *      very next update.
 */
- (void)startPedometerUpdatesFromDate:(NSDate *)start
						  withHandler:(CMPedometerHandler)handler;

/*
 *  stopPedometerUpdates
 *
 *  Discussion:
 *      Stops pedometer updates.
 */
- (void)stopPedometerUpdates;

@end

NS_ASSUME_NONNULL_END
