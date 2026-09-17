/*	NSDateInterval.h
	Copyright (c) 2015-2019, Apple Inc. All rights reserved.
 */

#import <Foundation/NSObject.h>
#import <Foundation/NSDate.h>
#import <Foundation/NSCoder.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

/// An object representing the span of time between a specific start date and end date.
///
/// In Swift, this object bridges to ``DateInterval``; use ``NSDateInterval`` when you need reference semantics or other Foundation-specific behavior.
///
/// An `NSDateInterval` object represents a closed interval between two dates. The `NSDateInterval` class provides a programmatic interface for calculating the duration of a time interval and determining whether a date falls within it, as well as comparing date intervals and checking to see whether they intersect.
///
/// An `NSDateInterval` object consists of a ``startDate`` and an ``endDate``. The ``startDate`` and ``endDate`` of a date interval can be equal, in which case its ``duration`` is `0`. However, ``endDate`` cannot occur earlier than ``startDate``.
///
/// You can use the ``DateIntervalFormatter`` class to create string representations of `NSDateInterval` objects that are suitable for display in the current locale.
///
/// > Important:
/// > The Swift overlay to the Foundation framework provides the ``DateInterval`` structure, which bridges to the `NSDateInterval` class. For more information about value types, see <doc://com.apple.documentation/documentation/swift/working-with-foundation-types>.
NS_SWIFT_SENDABLE
API_AVAILABLE(macosx(10.12), ios(10.0), watchos(3.0), tvos(10.0))
@interface NSDateInterval : NSObject <NSCopying, NSSecureCoding>

/*
 NSDateInterval represents a closed date interval in the form of [startDate, endDate].  It is possible for the start and end dates to be the same with a duration of 0.  NSDateInterval does not support reverse intervals i.e. intervals where the duration is less than 0 and the end date occurs earlier in time than the start date.
 */

/// The start date of the date interval.
@property (readonly, copy) NSDate *startDate;
/// The end date of the date interval.
@property (readonly, copy) NSDate *endDate;
/// The duration of the date interval.
@property (readonly) NSTimeInterval duration;

/// Initializes a date interval by setting the start and end date to the current date.
- (instancetype)init;

/// Returns a date interval initialized from data in the given unarchiver.
- (instancetype)initWithCoder:(NSCoder *)coder NS_DESIGNATED_INITIALIZER;

/// Initializes a date interval with a given start date and duration.
///
/// - Parameters:
///   - startDate: The start date of the date interval.
///   - duration: The duration from the start date for the date interval.
///
/// This method raises an `NSArgumentException` if `duration` is less than `0`.
///
/// This is the designated initializer.
- (instancetype)initWithStartDate:(NSDate *)startDate duration:(NSTimeInterval)duration NS_DESIGNATED_INITIALIZER;

/// Initializes a date interval from a given start date and end date.
///
/// - Parameters:
///   - startDate: The start date of the date interval.
///   - endDate: The end date of the date interval.
///
/// This method raises an `NSArgumentException` if `endDate` occurs earlier than `startDate`.
- (instancetype)initWithStartDate:(NSDate *)startDate endDate:(NSDate *)endDate;

/// Compares the receiver with the specified date interval.
///
/// Prioritizes ordering by start date. If the start dates are equal, then it will order by duration.
/// e.g.
///    Given intervals a and b
/// ```
///        a.   |-----|
///        b.      |-----|
///  ```
/// `[a compare:b]` would return `NSOrderedAscending` because a's `startDate` is earlier in time than b's `startDate`.

/// In the event that the start dates are equal, the compare method will attempt to order by duration.
/// e.g.
///    Given intervals c and d
/// ```
///        c.  |-----|
///        d.  |---|
/// ```
/// `[c compare:d]` would result in `NSOrderedDescending` because c is longer than d.

/// If both the start dates and the durations are equal, then the intervals are considered equal and `NSOrderedSame` is returned as the result.
///
/// - Parameters:
///   - dateInterval: The date interval with which to compare the receiver.
/// - Returns: An `NSComparisonResult` value that indicates the temporal ordering of the receiver and the given date interval:
///   `NSOrderedAscending` if the receiver's start date occurs earlier, or both start dates are equal and the receiver's duration is less.
///   `NSOrderedDescending` if the receiver's start date occurs later, or both start dates are equal and the receiver's duration is greater.
///   `NSOrderedSame` if the start dates and durations are equal.
- (NSComparisonResult)compare:(NSDateInterval *)dateInterval;

/// Indicates whether the receiver is equal to the specified date interval.
///
/// - Parameters:
///   - dateInterval: The date interval with which to check the receiver for equality.
/// - Returns: `YES` if the start date and duration of `dateInterval` and the receiver are equal. Otherwise, `NO`.
- (BOOL)isEqualToDateInterval:(NSDateInterval *)dateInterval;
/// Indicates whether the receiver intersects with the specified date interval.
///
/// - Parameters:
///   - dateInterval: The date interval with which to check the receiver for intersection.
- (BOOL)intersectsDateInterval:(NSDateInterval *)dateInterval;

/// Returns the intersection between the receiver and the specified date interval.
///
/// - Parameters:
///   - dateInterval: The date interval with which to calculate the intersection of the receiver.
/// - Returns: A date interval for the intersection of the receiver and `dateInterval`, or `nil` if no intersection occurs.
///
/// Calculating the intersection of date intervals is a commutative and associative operation. The intersection of a date interval with itself is equal to itself.
- (nullable NSDateInterval *)intersectionWithDateInterval:(NSDateInterval *)dateInterval;

/// Indicates whether the receiver contains the specified date.
///
/// - Parameters:
///   - date: The date for which to test membership of the date interval.
/// - Returns: `YES` if the receiver contains `date`. Otherwise, `NO`.
- (BOOL)containsDate:(NSDate *)date;

@end

NS_HEADER_AUDIT_END(nullability, sendability)
