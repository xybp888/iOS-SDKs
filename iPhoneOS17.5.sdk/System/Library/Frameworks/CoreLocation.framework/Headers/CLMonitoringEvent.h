//
//  CLMonitoringEvent.h
//  CoreLocation
//
//  Copyright (c) 2021 Apple Inc. All rights reserved.

#ifndef CLMonitoringEvent_h
#define CLMonitoringEvent_h

#import <CoreLocation/CLAvailability.h>

@class CLCondition;

NS_ASSUME_NONNULL_BEGIN

/*
 * 	Enum representing the current state of the condition.
 */
typedef NS_ENUM(NSUInteger, CLMonitoringState) {
	CLMonitoringStateUnknown,
	CLMonitoringStateSatisfied,
	CLMonitoringStateUnsatisfied,
	CLMonitoringStateUnmonitored API_AVAILABLE(macos(14.2), ios(17.2)) API_UNAVAILABLE(tvos, watchos)
} NS_REFINED_FOR_SWIFT;

/*
 *	Event object that would be passed to the callback handler upon an event
 *
 *	Discussion:
 *		Instances of `CLMonitoringEvent` contain detailed information about
 *		an event in the monitoring of a `CLCondition` by a `CLMonitor`.
 *
 */
NS_REFINED_FOR_SWIFT
CL_EXTERN
API_AVAILABLE(macos(14.0), ios(17.0)) API_UNAVAILABLE(watchos, tvos)
#if defined(TARGET_OS_VISION) && TARGET_OS_VISION
API_UNAVAILABLE(visionos)
#endif
@interface CLMonitoringEvent : NSObject<NSSecureCoding>

/*
 *	identifier
 *
 *	Discussion:
 *		An `NSString` representing the identifier under which the condition
 *		was added for monitoring.
 *
 */
@property (readonly, strong) NSString *identifier;

/*
 *	refinement
 *
 *	Discussion:
 *		An optional instance of CLCondition that represents the most specific
 *		condition to which this event could apply. The type of the refinement
 *		condition depends onthe monitored condition itself.
 *
 */
@property (readonly, strong) __kindof CLCondition * _Nullable refinement;

/*
 * 	state
 *
 *	Discussion:
 *		State of the condition at the time of the event.
 */
@property (readonly, nonatomic) CLMonitoringState state;

/*
 *	date
 *
 *	Discussion:
 *		An instance of NSDate indicating the time of the event.
 */
@property (readonly, strong) NSDate *date;

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
#endif /* CLMonitoringEvent_h */
