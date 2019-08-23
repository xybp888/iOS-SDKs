//
//  HKWorkout.h
//  HealthKit
//
//  Copyright (c) 2014 Apple Inc. All rights reserved.
//

#import <HealthKit/HKSample.h>

NS_ASSUME_NONNULL_BEGIN

@class HKQuantity;

/*!
 @enum          HKWorkoutActivityType
 @abstract      Represents a particular type of workout or exercise
 */
typedef NS_ENUM(NSUInteger, HKWorkoutActivityType) {
    HKWorkoutActivityTypeAmericanFootball = 1,
    HKWorkoutActivityTypeArchery,
    HKWorkoutActivityTypeAustralianFootball,
    HKWorkoutActivityTypeBadminton,
    HKWorkoutActivityTypeBaseball,
    HKWorkoutActivityTypeBasketball,
    HKWorkoutActivityTypeBowling,
    HKWorkoutActivityTypeBoxing, // See also HKWorkoutActivityTypeKickboxing.
    HKWorkoutActivityTypeClimbing,
    HKWorkoutActivityTypeCricket,
    HKWorkoutActivityTypeCrossTraining, // Any mix of cardio and/or strength training. See also HKWorkoutActivityTypeCoreTraining and HKWorkoutActivityTypeFlexibility.
    HKWorkoutActivityTypeCurling,
    HKWorkoutActivityTypeCycling,
    HKWorkoutActivityTypeDance,
    HKWorkoutActivityTypeDanceInspiredTraining NS_ENUM_DEPRECATED_IOS(8_0, 10_0, "Use HKWorkoutActivityTypeDance, HKWorkoutActivityTypeBarre, or HKWorkoutActivityTypePilates"), // This enum remains available to access older data.
    HKWorkoutActivityTypeElliptical,
    HKWorkoutActivityTypeEquestrianSports, // Polo, Horse Racing, Horse Riding, etc.
    HKWorkoutActivityTypeFencing,
    HKWorkoutActivityTypeFishing,
    HKWorkoutActivityTypeFunctionalStrengthTraining, // Primarily free weights and/or body weight and/or accessories
    HKWorkoutActivityTypeGolf,
    HKWorkoutActivityTypeGymnastics,
    HKWorkoutActivityTypeHandball,
    HKWorkoutActivityTypeHiking,
    HKWorkoutActivityTypeHockey, // Ice Hockey, Field Hockey, etc.
    HKWorkoutActivityTypeHunting,
    HKWorkoutActivityTypeLacrosse,
    HKWorkoutActivityTypeMartialArts,
    HKWorkoutActivityTypeMindAndBody, // Tai chi, meditation, etc.
    HKWorkoutActivityTypeMixedMetabolicCardioTraining, // Any mix of cardio-focused exercises
    HKWorkoutActivityTypePaddleSports, // Canoeing, Kayaking, Outrigger, Stand Up Paddle Board, etc.
    HKWorkoutActivityTypePlay, // Dodge Ball, Hopscotch, Tetherball, Jungle Gym, etc.
    HKWorkoutActivityTypePreparationAndRecovery, // Foam rolling, stretching, etc.
    HKWorkoutActivityTypeRacquetball,
    HKWorkoutActivityTypeRowing,
    HKWorkoutActivityTypeRugby,
    HKWorkoutActivityTypeRunning,
    HKWorkoutActivityTypeSailing,
    HKWorkoutActivityTypeSkatingSports, // Ice Skating, Speed Skating, Inline Skating, Skateboarding, etc.
    HKWorkoutActivityTypeSnowSports, // Sledding, Snowmobiling, Building a Snowman, etc. See also HKWorkoutActivityTypeCrossCountrySkiing, HKWorkoutActivityTypeSnowboarding, and HKWorkoutActivityTypeDownhillSkiing.
    HKWorkoutActivityTypeSoccer,
    HKWorkoutActivityTypeSoftball,
    HKWorkoutActivityTypeSquash,
    HKWorkoutActivityTypeStairClimbing, // See also HKWorkoutActivityTypeStairs and HKWorkoutActivityTypeStepTraining.
    HKWorkoutActivityTypeSurfingSports, // Traditional Surfing, Kite Surfing, Wind Surfing, etc.
    HKWorkoutActivityTypeSwimming,
    HKWorkoutActivityTypeTableTennis,
    HKWorkoutActivityTypeTennis,
    HKWorkoutActivityTypeTrackAndField, // Shot Put, Javelin, Pole Vaulting, etc.
    HKWorkoutActivityTypeTraditionalStrengthTraining, // Primarily machines and/or free weights
    HKWorkoutActivityTypeVolleyball,
    HKWorkoutActivityTypeWalking,
    HKWorkoutActivityTypeWaterFitness,
    HKWorkoutActivityTypeWaterPolo,
    HKWorkoutActivityTypeWaterSports, // Water Skiing, Wake Boarding, etc.
    HKWorkoutActivityTypeWrestling,
    HKWorkoutActivityTypeYoga,
    
    HKWorkoutActivityTypeBarre              HK_ENUM_AVAILABLE_IOS_WATCHOS(10_0, 3_0),    // HKWorkoutActivityTypeDanceInspiredTraining
    HKWorkoutActivityTypeCoreTraining       HK_ENUM_AVAILABLE_IOS_WATCHOS(10_0, 3_0),
    HKWorkoutActivityTypeCrossCountrySkiing HK_ENUM_AVAILABLE_IOS_WATCHOS(10_0, 3_0),
    HKWorkoutActivityTypeDownhillSkiing     HK_ENUM_AVAILABLE_IOS_WATCHOS(10_0, 3_0),
    HKWorkoutActivityTypeFlexibility        HK_ENUM_AVAILABLE_IOS_WATCHOS(10_0, 3_0),
    HKWorkoutActivityTypeHighIntensityIntervalTraining    HK_ENUM_AVAILABLE_IOS_WATCHOS(10_0, 3_0),
    HKWorkoutActivityTypeJumpRope           HK_ENUM_AVAILABLE_IOS_WATCHOS(10_0, 3_0),
    HKWorkoutActivityTypeKickboxing         HK_ENUM_AVAILABLE_IOS_WATCHOS(10_0, 3_0),
    HKWorkoutActivityTypePilates            HK_ENUM_AVAILABLE_IOS_WATCHOS(10_0, 3_0),    // HKWorkoutActivityTypeDanceInspiredTraining
    HKWorkoutActivityTypeSnowboarding       HK_ENUM_AVAILABLE_IOS_WATCHOS(10_0, 3_0),
    HKWorkoutActivityTypeStairs             HK_ENUM_AVAILABLE_IOS_WATCHOS(10_0, 3_0),
    HKWorkoutActivityTypeStepTraining       HK_ENUM_AVAILABLE_IOS_WATCHOS(10_0, 3_0),
    HKWorkoutActivityTypeWheelchairWalkPace HK_ENUM_AVAILABLE_IOS_WATCHOS(10_0, 3_0),
    HKWorkoutActivityTypeWheelchairRunPace  HK_ENUM_AVAILABLE_IOS_WATCHOS(10_0, 3_0),
    
    HKWorkoutActivityTypeOther = 3000,
} HK_ENUM_AVAILABLE_IOS_WATCHOS(8_0, 2_0);

typedef NS_ENUM(NSInteger, HKWorkoutEventType) {
    HKWorkoutEventTypePause = 1,
    HKWorkoutEventTypeResume,
    HKWorkoutEventTypeLap           HK_ENUM_AVAILABLE_IOS_WATCHOS(10_0, 3_0),
    HKWorkoutEventTypeMarker        HK_ENUM_AVAILABLE_IOS_WATCHOS(10_0, 3_0),
    HKWorkoutEventTypeMotionPaused  HK_ENUM_AVAILABLE_IOS_WATCHOS(10_0, 3_0),
    HKWorkoutEventTypeMotionResumed HK_ENUM_AVAILABLE_IOS_WATCHOS(10_0, 3_0),
} HK_ENUM_AVAILABLE_IOS_WATCHOS(8_0, 2_0);

/*!
 @class         HKWorkoutEvent
 @abstract      Represents a particular event that occurred during a workout
 */
HK_CLASS_AVAILABLE_IOS_WATCHOS(8_0, 2_0)
@interface HKWorkoutEvent : NSObject <NSSecureCoding, NSCopying>

@property (readonly, assign) HKWorkoutEventType type;
@property (readonly, copy) NSDate *date;
@property (readonly, copy, nullable) NSDictionary<NSString *, id> *metadata HK_AVAILABLE_IOS_WATCHOS(10_0, 3_0);

+ (instancetype)workoutEventWithType:(HKWorkoutEventType)type date:(NSDate *)date;
+ (instancetype)workoutEventWithType:(HKWorkoutEventType)type date:(NSDate *)date metadata:(NSDictionary<NSString *, id> *)metadata HK_AVAILABLE_IOS_WATCHOS(10_0, 3_0);
- (instancetype)init NS_UNAVAILABLE;

@end

/*!
 @class         HKWorkout
 @abstract      An HKObject subclass representing a workout or activity
 */
HK_CLASS_AVAILABLE_IOS_WATCHOS(8_0, 2_0)
@interface HKWorkout : HKSample

/*!
 @property      workoutActivityType
 @abstract      Represents the activity that the user was performing during a workout
 */
@property (readonly, assign) HKWorkoutActivityType workoutActivityType;

/*!
 @property      workoutEvents
 @abstract      An array of HKWorkoutEvents that occurred during a workout.
 @discussion    These events will be ordered by date in ascending order. All events must take place
                between the start date and end date of the workout. The first workout event should always be a pause event
                because it is assumed that the workout begins in a running state. A pause event can only be followed by
                a resume event, and a resume event can only be followed by a pause event.
 */
@property (readonly, copy, nullable) NSArray<HKWorkoutEvent *> *workoutEvents;

/*!
 @property      duration
 @abstract      The length of time that a workout was recording
 @discussion    The duration is derived from the start an end date of the workout, and takes into account periods that the 
                workout was paused. Periods that the workout was paused are based off of the workoutEvents property.
 */
@property (readonly, assign) NSTimeInterval duration;

/*!
 @property      totalEnergyBurned
 @abstract      The amount of energy that was burned during a workout
 @discussion    This metric should represent the total active energy burned during the course of the workout. It should be a
                quantity with a unit representing energy.
 */
@property (readonly, strong, nullable) HKQuantity *totalEnergyBurned;
/*!
 @property      totalDistance
 @abstract      The total distance that was traveled during a workout
 @discussion    This metric should represent the total distance traveled during the course of the workout. It should be a
                quantity with a unit representing length.
 */
@property (readonly, strong, nullable) HKQuantity *totalDistance;

/*!
 @property      totalSwimmingStrokeCount
 @abstract      The total count of swimming strokes that was accumulated during a workout
 @discussion    This metric should represent the total count of swimming strokes accumulated during the course of the
                workout. It should be a quantity with a unit representing count.
 */
@property (readonly, strong, nullable) HKQuantity *totalSwimmingStrokeCount HK_AVAILABLE_IOS_WATCHOS(10_0, 3_0);

/*!
 @method        workoutWithActivityType:startDate:endDate:

 @param         workoutActivityType     The activity type of the workout
 @param         startDate               The point in time that the workout was started
 @param         endDate                 The point in time that the workout was ended
 */
+ (instancetype)workoutWithActivityType:(HKWorkoutActivityType)workoutActivityType
                              startDate:(NSDate *)startDate
                                endDate:(NSDate *)endDate;

/*!
 @method        workoutWithActivityType:startDate:endDate:workoutEvents:totalEnergyBurned:totalDistance:metadata
 @discussion    If the optional total parameters are specified, matching samples that add up to the calculated total quantities
                should be associated with this workout using addSamples:toWorkout:completion: in HKHealthStore.
 
 @param         workoutActivityType     The activity type of the workout
 @param         startDate               The point in time that the workout was started
 @param         endDate                 The point in time that the workout was ended
 @param         workoutEvents           An array of HKWorkoutEvents. The workout's duration is derived from these events. (Optional)
 @param         totalEnergyBurned       The amount of energy that was burned during the workout. (Optional)
 @param         totalDistance           The total distance that was traveled during the workout. (Optional)
 @param         metadata                Metadata for the workout. (Optional)
 */
+ (instancetype)workoutWithActivityType:(HKWorkoutActivityType)workoutActivityType
                              startDate:(NSDate *)startDate
                                endDate:(NSDate *)endDate
                          workoutEvents:(nullable NSArray<HKWorkoutEvent *> *)workoutEvents
                      totalEnergyBurned:(nullable HKQuantity *)totalEnergyBurned
                          totalDistance:(nullable HKQuantity *)totalDistance
                               metadata:(nullable NSDictionary<NSString *, id> *)metadata;

/*!
 @method        workoutWithActivityType:startDate:endDate:workoutEvents:totalEnergyBurned:totalDistance:metadata
 @discussion    If the optional total parameters are specified, matching samples that add up to the calculated total quantities
                should be associated with this workout using addSamples:toWorkout:completion: in HKHealthStore.
 
 @param         workoutActivityType     The activity type of the workout
 @param         startDate               The point in time that the workout was started
 @param         endDate                 The point in time that the workout was ended
 @param         workoutEvents           An array of HKWorkoutEvents. The workout's duration is derived from these events. (Optional)
 @param         totalEnergyBurned       The amount of energy that was burned during the workout. (Optional)
 @param         totalDistance           The total distance that was traveled during the workout. (Optional)
 @param         device                  The HKDevice associated with the workout. (Optional)
 @param         metadata                Metadata for the workout. (Optional)
 */
+ (instancetype)workoutWithActivityType:(HKWorkoutActivityType)workoutActivityType
                              startDate:(NSDate *)startDate
                                endDate:(NSDate *)endDate
                          workoutEvents:(nullable NSArray<HKWorkoutEvent *> *)workoutEvents
                      totalEnergyBurned:(nullable HKQuantity *)totalEnergyBurned
                          totalDistance:(nullable HKQuantity *)totalDistance
                                 device:(nullable HKDevice *)device
                               metadata:(nullable NSDictionary<NSString *, id> *)metadata HK_AVAILABLE_IOS_WATCHOS(9_0, 2_0);

/*!
 @method        workoutWithActivityType:startDate:endDate:duration:totalEnergyBurned:totalDistance:metadata:
 @discussion    If the optional total parameters are specified, matching samples that add up to the calculated total quantities
                should be associated with this workout using addSamples:toWorkout:completion: in HKHealthStore.
 
 @param         workoutActivityType     The activity type of the workout
 @param         startDate               The point in time that the workout was started
 @param         endDate                 The point in time that the workout was ended
 @param         duration                The duration of the workout. If 0, the difference between startDate and endDate is used.
 @param         totalEnergyBurned       The amount of energy that was burned during the workout. (Optional)
 @param         totalDistance           The total distance that was traveled during the workout. (Optional)
 @param         metadata                Metadata for the workout. (Optional)
 */
+ (instancetype)workoutWithActivityType:(HKWorkoutActivityType)workoutActivityType
                              startDate:(NSDate *)startDate
                                endDate:(NSDate *)endDate
                               duration:(NSTimeInterval)duration
                      totalEnergyBurned:(nullable HKQuantity *)totalEnergyBurned
                          totalDistance:(nullable HKQuantity *)totalDistance
                               metadata:(nullable NSDictionary<NSString *, id> *)metadata;

/*!
 @method        workoutWithActivityType:startDate:endDate:duration:totalEnergyBurned:totalDistance:device:metadata:
 @discussion    If the optional total parameters are specified, matching samples that add up to the calculated total quantities
                should be associated with this workout using addSamples:toWorkout:completion: in HKHealthStore.
 
 @param         workoutActivityType     The activity type of the workout
 @param         startDate               The point in time that the workout was started
 @param         endDate                 The point in time that the workout was ended
 @param         duration                The duration of the workout. If 0, the difference between startDate and endDate is used.
 @param         totalEnergyBurned       The amount of energy that was burned during the workout. (Optional)
 @param         totalDistance           The total distance that was traveled during the workout. (Optional)
 @param         device                  The HKDevice associated with the workout. (Optional)
 @param         metadata                Metadata for the workout. (Optional)
 */
+ (instancetype)workoutWithActivityType:(HKWorkoutActivityType)workoutActivityType
                              startDate:(NSDate *)startDate
                                endDate:(NSDate *)endDate
                               duration:(NSTimeInterval)duration
                      totalEnergyBurned:(nullable HKQuantity *)totalEnergyBurned
                          totalDistance:(nullable HKQuantity *)totalDistance
                                 device:(nullable HKDevice *)device
                               metadata:(nullable NSDictionary<NSString *, id> *)metadata HK_AVAILABLE_IOS_WATCHOS(9_0, 2_0);

/*!
 @method        workoutWithActivityType:startDate:endDate:workoutEvents:totalEnergyBurned:totalDistance:totalSwimmingStrokeCount:device:metadata:
 @discussion    If the optional total parameters are specified, matching samples that add up to the calculated total quantities
                should be associated with this workout using addSamples:toWorkout:completion: in HKHealthStore.
 
 @param         workoutActivityType         The activity type of the workout
 @param         startDate                   The point in time that the workout was started
 @param         endDate                     The point in time that the workout was ended
 @param         workoutEvents               An array of HKWorkoutEvents. The workout's duration is derived from these events. (Optional)
 @param         totalEnergyBurned           The amount of energy that was burned during the workout. (Optional)
 @param         totalDistance               The total distance that was traveled during the workout. (Optional)
 @param         totalSwimmingStrokeCount    The total count of swimming strokes that was accumulated during the workout. (Optional)
 @param         device                      The HKDevice associated with the workout. (Optional)
 @param         metadata                    Metadata for the workout. (Optional)
 */
+ (instancetype)workoutWithActivityType:(HKWorkoutActivityType)workoutActivityType
                              startDate:(NSDate *)startDate
                                endDate:(NSDate *)endDate
                          workoutEvents:(nullable NSArray<HKWorkoutEvent *> *)workoutEvents
                      totalEnergyBurned:(nullable HKQuantity *)totalEnergyBurned
                          totalDistance:(nullable HKQuantity *)totalDistance
               totalSwimmingStrokeCount:(nullable HKQuantity *)totalSwimmingStrokeCount
                                 device:(nullable HKDevice *)device
                               metadata:(nullable NSDictionary<NSString *, id> *)metadata HK_AVAILABLE_IOS_WATCHOS(10_0, 3_0);

@end

// Predicate Key Paths
HK_EXTERN NSString * const HKPredicateKeyPathWorkoutDuration HK_AVAILABLE_IOS_WATCHOS(8_0, 2_0);
HK_EXTERN NSString * const HKPredicateKeyPathWorkoutTotalDistance HK_AVAILABLE_IOS_WATCHOS(8_0, 2_0);
HK_EXTERN NSString * const HKPredicateKeyPathWorkoutTotalEnergyBurned HK_AVAILABLE_IOS_WATCHOS(8_0, 2_0);
HK_EXTERN NSString * const HKPredicateKeyPathWorkoutType HK_AVAILABLE_IOS_WATCHOS(8_0, 2_0);
HK_EXTERN NSString * const HKPredicateKeyPathWorkoutTotalSwimmingStrokeCount HK_AVAILABLE_IOS_WATCHOS(10_0, 3_0);

// Sort Identifiers
HK_EXTERN NSString * const HKWorkoutSortIdentifierDuration HK_AVAILABLE_IOS_WATCHOS(8_0, 2_0);
HK_EXTERN NSString * const HKWorkoutSortIdentifierTotalDistance HK_AVAILABLE_IOS_WATCHOS(8_0, 2_0);
HK_EXTERN NSString * const HKWorkoutSortIdentifierTotalEnergyBurned HK_AVAILABLE_IOS_WATCHOS(8_0, 2_0);
HK_EXTERN NSString * const HKWorkoutSortIdentifierTotalSwimmingStrokeCount HK_AVAILABLE_IOS_WATCHOS(10_0, 3_0);

NS_ASSUME_NONNULL_END
