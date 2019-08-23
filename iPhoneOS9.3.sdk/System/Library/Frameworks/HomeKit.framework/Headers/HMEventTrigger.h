// HMEventTrigger.h
// HomeKit
//
// Copyright (c) 2015 Apple Inc. All rights reserved.

#import <Foundation/Foundation.h>
#import <HomeKit/HMTrigger.h>

NS_ASSUME_NONNULL_BEGIN

@class HMEvent;
@class HMCharacteristic;

/*!
 * @group Specifies a group of events that are deemed significant events in a day.
 *        These are also the key paths for the event in a NSPredicate.
 */

/*!
 * @brief Event corresponding to sunrise
 */
HM_EXTERN NSString * const HMSignificantEventSunrise NS_AVAILABLE_IOS(9_0) __WATCHOS_AVAILABLE(__WATCHOS_2_0);

/*!
 * @brief Event corresponding to sunset
 */
HM_EXTERN NSString * const HMSignificantEventSunset NS_AVAILABLE_IOS(9_0) __WATCHOS_AVAILABLE(__WATCHOS_2_0);

/*!
 * @brief Specifies the key path for a characteristic in a NSPredicate
 */
HM_EXTERN NSString * const HMCharacteristicKeyPath NS_AVAILABLE_IOS(9_0) __WATCHOS_AVAILABLE(__WATCHOS_2_0);

/*!
 * @brief Specifies the key path for a characteristic value in a NSPredicate
 */
HM_EXTERN NSString * const HMCharacteristicValueKeyPath NS_AVAILABLE_IOS(9_0) __WATCHOS_AVAILABLE(__WATCHOS_2_0);


/*!
 * @brief Triggers based on events.
 *
 * @discussion This class represents a trigger that is based on events.
 */
NS_CLASS_AVAILABLE_IOS(9_0) __WATCHOS_AVAILABLE(__WATCHOS_2_0)
@interface HMEventTrigger : HMTrigger

- (instancetype)init NS_UNAVAILABLE;

/*!
 * @brief Initializes a new event trigger object.
 *
 * @param name Name of the event trigger.
 *
 * @param events Array of events that can trigger the evaluation of the trigger. Note: The trigger will
 *               be evaluated if any one of the events is true.
 *
 * @param predicate The predicate to evaluate before executing any of the actions sets associated to this
 *                  event.
 *
 * @return Instance object representing the event trigger.
 */
- (instancetype)initWithName:(NSString *)name
                      events:(NSArray<HMEvent *> *)events
                   predicate:(nullable NSPredicate *)predicate NS_DESIGNATED_INITIALIZER __WATCHOS_PROHIBITED;

/*!
 * @brief The events associated with the trigger.
 */
@property(readonly, copy, nonatomic) NSArray<HMEvent *> *events;

/*!
 * @brief The predicate to evaluate before executing the action sets associated with the trigger.
 */
@property(readonly, copy, nonatomic, nullable) NSPredicate *predicate;

/*!
 * @brief Creates a predicate that will evaluate whether the event occurred before a significant event.
 *
 * @param significantEvent The significant event to compare against.
 *                         The valid values are: HMSignificantEventSunrise and HMSignificantEventSunset.
 *
 * @param offset An offset from the time of the signficant event. To specify an offset before the significant event, the
 *               properties of the NSDateComponents must be negative value. e.g. To specify 30 mins before sunset, the
 *               'minute' property must be set to -30.
 *
 * @return Predicate object representing a condition to evaluate before executing the action set.
 */
+ (NSPredicate *)predicateForEvaluatingTriggerOccurringBeforeSignificantEvent:(NSString *)significantEvent applyingOffset:(nullable NSDateComponents *)offset;

/*!
 * @brief Creates a predicate that will evaluate whether the event occurred before a significant event.
 *
 * @param significantEvent The significant event to compare against.
 *                         The valid values are: HMSignificantEventSunrise and HMSignificantEventSunset.
 *
 * @param offset An offset from the time of the signficant event. To specify an offset after the significant event, the
 *               properties of the NSDateComponents must be positive value. e.g. To specify 30 mins after sunset, the
 *               'minute' property must be set to 30.
 *
 * @return Predicate object representing a condition to evaluate before executing the action set.
 */
+ (NSPredicate *)predicateForEvaluatingTriggerOccurringAfterSignificantEvent:(NSString *)significantEvent applyingOffset:(nullable NSDateComponents *)offset;

/*!
 * @brief Creates a predicate that will evaluate whether the event occurred before the time specified.
 *
 * @param dateComponents Date components representing the time to compare against when the event occurs.
 *
 * @return Predicate object representing a condition to evaluate before executing the action set.
 */
+ (NSPredicate *)predicateForEvaluatingTriggerOccurringBeforeDateWithComponents:(NSDateComponents *)dateComponents;

/*!
 * @brief Creates a predicate that will evaluate whether the event occurred at the time specified.
 *
 * @param dateComponents Date components representing the time to compare against when the event occurs.
 *
 * @return Predicate object representing a condition to evaluate before executing the action set.
 */
+ (NSPredicate *)predicateForEvaluatingTriggerOccurringOnDateWithComponents:(NSDateComponents *)dateComponents;

/*!
 * @brief Creates a predicate that will evaluate whether the event occurred at or after the time specified.
 *
 * @param dateComponents Date components representing the time to compare against when the event occurs.
 *
 * @return Predicate object representing a condition to evaluate before executing the action set.
 */
+ (NSPredicate *)predicateForEvaluatingTriggerOccurringAfterDateWithComponents:(NSDateComponents *)dateComponents;

/*!
 * @brief Creates a predicate that will evaluate whether a characteristic value is related to the specified value.
 *
 * @param characteristic The characteristic that is evaluated as part of the predicate.
 *
 * @param operatorType The relation between the characteristic and the target value. 
 *                     This can be either Less Than, Greater Than, Less Than or Equal, Greater Than or Equal, Equal, or Not Equal.
 *                     Anything else will cause an exception to be thrown.
 *
 * @param value The value of the characteristic to compare when evaluating the predicate.
 *
 * @return Predicate object representing a condition to evaluate before executing the action set.
 */
+ (NSPredicate *)predicateForEvaluatingTriggerWithCharacteristic:(HMCharacteristic *)characteristic
                                                       relatedBy:(NSPredicateOperatorType)operatorType
                                                         toValue:(id)value;

/*!
 * @brief Adds a new event to the event trigger.
 *
 * @param event Event to add to the event trigger.
 *
 * @param completion Block that is invoked once the request is processed. 
 *                   The NSError provides more information on the status of the request, error
 *                   will be nil on success.
 */
- (void)addEvent:(HMEvent *)event completionHandler:(void (^)(NSError * __nullable error))completion __WATCHOS_PROHIBITED;

/*!
 * @brief Removes the specified event from the event trigger.
 *
 * @param event Event to remove from the event trigger.
 *
 * @param completion Block that is invoked once the request is processed. 
 *                   The NSError provides more information on the status of the request, error
 *                   will be nil on success.
 */
- (void)removeEvent:(HMEvent *)event completionHandler:(void (^)(NSError * __nullable error))completion __WATCHOS_PROHIBITED;

/*!
 * @brief This method replaces the predicate used to evaluate execution of the action sets associated with the trigger.
 *
 * @param predicate The new predicate for the event trigger.
 *
 * @param completion Block that is invoked once the request is processed.
 *                   The NSError provides more information on the status of the request,
 *                   error will be nil on success. 
 */
- (void)updatePredicate:(nullable NSPredicate *)predicate completionHandler:(void (^)(NSError * __nullable error))completion __WATCHOS_PROHIBITED;

@end

NS_ASSUME_NONNULL_END
