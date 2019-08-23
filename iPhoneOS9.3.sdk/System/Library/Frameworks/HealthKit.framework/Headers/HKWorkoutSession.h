//
//  HKWorkoutSession.h
//  HealthKit
//
//  Copyright (c) 2015 Apple. All rights reserved.
//

#import <HealthKit/HKWorkout.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 @enum          HKWorkoutSessionState
 @abstract      This enumerated type is used to represent the state of a workout session.
 */
typedef NS_ENUM(NSInteger, HKWorkoutSessionState) {
    HKWorkoutSessionStateNotStarted = 1,
    HKWorkoutSessionStateRunning,
    HKWorkoutSessionStateEnded,
} HK_AVAILABLE_WATCHOS_ONLY(2_0);


/*!
 @enum          HKWorkoutSessionLocationType
 @abstract      This enumerated type is used to represent the location type of a workout session.
 @discussion    This value represents whether a workout is performed indoors or outdoors.
 */
typedef NS_ENUM(NSInteger, HKWorkoutSessionLocationType) {
    HKWorkoutSessionLocationTypeUnknown = 1,
    HKWorkoutSessionLocationTypeIndoor,
    HKWorkoutSessionLocationTypeOutdoor,
} HK_AVAILABLE_WATCHOS_ONLY(2_0);


@protocol HKWorkoutSessionDelegate;

/*!
 @class         HKWorkoutSession
 @abstract      An HKWorkoutSession is an object describing the properties of a workout activity session.
 */
HK_CLASS_AVAILABLE_WATCHOS_ONLY(2_0)
@interface HKWorkoutSession : NSObject <NSSecureCoding>

/*!
 @property      activityType
 @abstract      Indicates the type of workout that will be performed during the session.
 */
@property (readonly) HKWorkoutActivityType activityType;

/*!
 @property      locationType
 @abstract      Indicates the type of location (indoors vs. outdoors) where the workout will take place.
 @discussion    Knowing the location type allows for more accurate measurements and better performance.
 */
@property (readonly) HKWorkoutSessionLocationType locationType;

/*!
 @property      delegate
 @abstract      The session delegate, which receives
 @discussion    The session delegate object is the one implementing the methods that get called when the session
                state changes or a failure occurs in the session.
 */
@property (weak, nullable) id<HKWorkoutSessionDelegate> delegate;

/*!
 @property      state
 @abstract      Indicates the current state of the workout session.
 @discussion    Each time this value is updated, the delegate method workoutSession:didChangeToState:fromState:date:
                will be called.
 */
@property (readonly) HKWorkoutSessionState state;

/*!
 @property      startDate
 @abstract      Indicates the date when the workout session started running.
 @discussion    This value is nil when a workout session is initialized. It is set when the workout session state
                changes to HKWorkoutSessionStateRunning.
 */
@property (readonly, nullable) NSDate *startDate;

/*!
 @property      endDate
 @abstract      Indicates the date when the workout session ended.
 @discussion    This value is nil when a workout session is initialized. It is set when the workout session state
                changes to HKWorkoutSessionStateEnded.
 */
@property (readonly, nullable) NSDate *endDate;

/*!
 @method        initWithActivityType:locationType:

 @param         activityType    The activity type of the workout session.
 @param         locationType    The type of location where the workout will be performed.
 */
- (instancetype)initWithActivityType:(HKWorkoutActivityType)activityType
                        locationType:(HKWorkoutSessionLocationType)locationType;

- (instancetype)init NS_UNAVAILABLE;

@end


/*!
 @enum          HKWorkoutSessionStateDelegate
 @abstract      This protocol should be implemented to be notified when a workout session's state changes.
 @discussion    The methods on this protocol are called on an anonymous serial background queue.
 */
HK_AVAILABLE_WATCHOS_ONLY(2_0)
@protocol HKWorkoutSessionDelegate <NSObject>

/*!
 @method        workoutSession:didChangeToState:fromState:date:
 @abstract      This method is called when a workout session transitions to a new state.
 @discussion    The date is provided to indicate when the state change actually happened.  If your application is
                suspended then the delegate will receive this call once the application resumes, which may be much later
                than when the original state change ocurred.
 */
- (void)workoutSession:(HKWorkoutSession *)workoutSession
      didChangeToState:(HKWorkoutSessionState)toState
             fromState:(HKWorkoutSessionState)fromState
                  date:(NSDate *)date;

/*!
 @method        workoutSession:didFailWithError:
 @abstract      This method is called when an error occurs that stops a workout session.
 @discussion    When the state of the workout session changes due to an error occurring, this method is always called
                before workoutSession:didChangeToState:fromState:date:.
 */
- (void)workoutSession:(HKWorkoutSession *)workoutSession didFailWithError:(NSError *)error;

@end

NS_ASSUME_NONNULL_END
