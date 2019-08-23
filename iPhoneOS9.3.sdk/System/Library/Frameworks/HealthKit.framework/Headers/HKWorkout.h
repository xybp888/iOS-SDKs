//
//  HKWorkout.h
//  HealthKit
//
//  Copyright (c) 2014 Apple Inc. All rights reserved.
//

#import <HealthKit/HKSample.h>

NS_ASSUME_NONNULL_BEGIN

@class HKQuantity;
@class HKWorkoutEvent;

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
    HKWorkoutActivityTypeBoxing, // Kickboxing, Boxing, etc.
    HKWorkoutActivityTypeClimbing,
    HKWorkoutActivityTypeCricket,
    HKWorkoutActivityTypeCrossTraining, // Any mix of cardio and/or strength and/or flexibility
    HKWorkoutActivityTypeCurling,
    HKWorkoutActivityTypeCycling,
    HKWorkoutActivityTypeDance,
    HKWorkoutActivityTypeDanceInspiredTraining, // Pilates, Barre, Feldenkrais, etc.
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
    HKWorkoutActivityTypeSnowSports, // Skiing, Snowboarding, Cross-Country Skiing, etc.
    HKWorkoutActivityTypeSoccer,
    HKWorkoutActivityTypeSoftball,
    HKWorkoutActivityTypeSquash,
    HKWorkoutActivityTypeStairClimbing,
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
    
    HKWorkoutActivityTypeOther = 3000,
} NS_ENUM_AVAILABLE_IOS(8_0);

typedef NS_ENUM(NSInteger, HKWorkoutEventType) {
    HKWorkoutEventTypePause = 1,
    HKWorkoutEventTypeResume
} NS_ENUM_AVAILABLE_IOS(8_0);

/*!
 @class         HKWorkoutEvent
 @abstract      Represents a particular event that occurred during a workout
 */
HK_CLASS_AVAILABLE_IOS(8_0)
@interface HKWorkoutEvent : NSObject <NSSecureCoding>

@property (readonly, assign) HKWorkoutEventType type;
@property (readonly, copy) NSDate *date;

+ (instancetype)workoutEventWithType:(HKWorkoutEventType)type date:(NSDate *)date;
- (instancetype)init NS_UNAVAILABLE;

@end

/*!
 @class         HKWorkout
 @abstract      An HKObject subclass representing a workout or activity
 */
HK_CLASS_AVAILABLE_IOS(8_0)
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
 @param         device                  The HKDevice associated with the workout (optional).
 @param         metadata                Metadata for the workout. (Optional)
 */
+ (instancetype)workoutWithActivityType:(HKWorkoutActivityType)workoutActivityType
                              startDate:(NSDate *)startDate
                                endDate:(NSDate *)endDate
                          workoutEvents:(nullable NSArray<HKWorkoutEvent *> *)workoutEvents
                      totalEnergyBurned:(nullable HKQuantity *)totalEnergyBurned
                          totalDistance:(nullable HKQuantity *)totalDistance
                                 device:(nullable HKDevice *)device
                               metadata:(nullable NSDictionary<NSString *, id> *)metadata NS_AVAILABLE_IOS(9_0);

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
 @param         device                  The HKDevice associated with the workout (optional).
 @param         metadata                Metadata for the workout. (Optional)
 */
+ (instancetype)workoutWithActivityType:(HKWorkoutActivityType)workoutActivityType
                              startDate:(NSDate *)startDate
                                endDate:(NSDate *)endDate
                               duration:(NSTimeInterval)duration
                      totalEnergyBurned:(nullable HKQuantity *)totalEnergyBurned
                          totalDistance:(nullable HKQuantity *)totalDistance
                                 device:(nullable HKDevice *)device
                               metadata:(nullable NSDictionary<NSString *, id> *)metadata NS_AVAILABLE_IOS(9_0);

@end

// Predicate Key Paths
HK_EXTERN NSString * const HKPredicateKeyPathWorkoutDuration NS_AVAILABLE_IOS(8_0);
HK_EXTERN NSString * const HKPredicateKeyPathWorkoutTotalDistance NS_AVAILABLE_IOS(8_0);
HK_EXTERN NSString * const HKPredicateKeyPathWorkoutTotalEnergyBurned NS_AVAILABLE_IOS(8_0);
HK_EXTERN NSString * const HKPredicateKeyPathWorkoutType NS_AVAILABLE_IOS(8_0);

// Sort Identifiers
HK_EXTERN NSString * const HKWorkoutSortIdentifierDuration NS_AVAILABLE_IOS(8_0);
HK_EXTERN NSString * const HKWorkoutSortIdentifierTotalDistance NS_AVAILABLE_IOS(8_0);
HK_EXTERN NSString * const HKWorkoutSortIdentifierTotalEnergyBurned NS_AVAILABLE_IOS(8_0);

NS_ASSUME_NONNULL_END
