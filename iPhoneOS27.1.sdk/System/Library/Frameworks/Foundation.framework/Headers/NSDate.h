/*	NSDate.h
	Copyright (c) 1994-2019, Apple Inc. All rights reserved.
*/

#import <Foundation/NSObject.h>
#import <Foundation/NSNotification.h>

@class NSString;

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

/// A notification posted whenever the system clock is changed.
///
/// This can be initiated by a call to `settimeofday()` or the user changing values in the Date and Time Preference panel. The notification object is `nil`. This notification does not contain a `userInfo` dictionary.
FOUNDATION_EXPORT NSNotificationName const NSSystemClockDidChangeNotification API_AVAILABLE(macos(10.6), ios(4.0), watchos(2.0), tvos(9.0));

/// A number of seconds.
///
/// An `NSTimeInterval` value is always specified in seconds; it yields sub-millisecond precision over a range of 10,000 years.
///
/// On its own, a time interval does not specify a unique point in time, or even a span between specific times. Combining a time interval with one or more known reference points yields an `NSDate` or `NSDateInterval` value.
typedef double NSTimeInterval;

#define NSTimeIntervalSince1970  978307200.0

/// A representation of a specific point in time, independent of any calendar or time zone.
///
/// In Swift, use this type when you need reference semantics or other Foundation-specific behavior.
///
/// ``NSDate`` objects encapsulate a single point in time, independent of any particular calendrical system or time zone. Date objects are immutable, representing an invariant time interval relative to an absolute reference date (00:00:00 UTC on 1 January 2001).
///
/// The ``NSDate`` class provides methods for comparing dates, calculating the time interval between two dates, and creating a new date from a time interval relative to another date. ``NSDate`` objects can be used in conjunction with ``DateFormatter`` objects to create localized representations of dates and times, as well as with ``NSCalendar`` objects to perform calendar arithmetic.
///
/// ``NSDate`` is _toll-free bridged_ with its Core Foundation counterpart, <doc://com.apple.documentation/documentation/corefoundation/cfdate>. See [Toll-Free Bridging](https://developer.apple.com/library/archive/documentation/General/Conceptual/CocoaEncyclopedia/Toll-FreeBridgin/Toll-FreeBridgin.html#//apple_ref/doc/uid/TP40010810-CH2) for more information on toll-free bridging.
///
/// > Important:
/// > The Swift overlay to the Foundation framework provides the ``Date`` structure, which bridges to the ``NSDate`` class. For more information about value types, see <doc://com.apple.documentation/documentation/swift/working-with-foundation-types>.
///
/// ### Subclassing Notes
///
/// You might subclass ``NSDate`` in order to make it easier to work with a particular calendrical system, or to work with date and time values with a finer temporal granularity.
///
/// #### Methods to Override and Other Requirements
///
/// If you want to subclass ``NSDate`` to obtain behavior different than that provided by the private or public subclasses, you must:
///
/// - Declare a suitable instance variable to hold the date and time value (relative to an absolute reference date)
/// - Override the ``timeIntervalSinceReferenceDate-property`` instance method to provide the correct date and time value based on your instance variable
/// - Override ``init(timeIntervalSinceReferenceDate:)``, one of the designated initializer methods
/// - If creating a subclass that represents a calendrical system, define methods that partition past and future periods into the units of this calendar
/// - Implement the methods required by the ``NSCopying`` and [NSCoding](https://developer.apple.com/library/archive/documentation/Swift/Conceptual/BuildingCocoaApps/WritingSwiftClassesWithObjective-CBehavior.html#//apple_ref/doc/uid/TP40014216-CH5-ID152) protocols, because ``NSDate`` adopts these protocols
///
///
///
/// #### Special Considerations
///
/// Your subclass may use a different reference date than the absolute reference date used by ``NSDate`` (00:00:00 UTC on 1 January 2001). If it does, it must still use the absolute reference date in its implementations of the methods ``timeIntervalSinceReferenceDate-property`` and ``init(timeIntervalSinceReferenceDate:)``. That is, the reference date referred to in the titles of these methods is the absolute reference date. If you do not use the absolute reference date in these methods, comparisons between ``NSDate`` objects of your subclass and `NSDate` objects of a private subclass will not work.
NS_SWIFT_SENDABLE
@interface NSDate : NSObject <NSCopying, NSSecureCoding>

/// The interval between the date object and 00:00:00 UTC on 1 January 2001.
///
/// This property's value is negative if the date object is earlier than the system's absolute reference date (00:00:00 UTC on 1 January 2001).
@property (readonly) NSTimeInterval timeIntervalSinceReferenceDate;

/// Returns a date object initialized to the current date and time.
///
/// This method is a designated initializer for `NSDate`.
- (instancetype)init NS_DESIGNATED_INITIALIZER;
/// Returns a date object initialized relative to 00:00:00 UTC on 1 January 2001 by a given number of seconds.
///
/// - Parameter ti: The number of seconds to add to the reference date (00:00:00 UTC on 1 January 2001). A negative value means the receiver will be earlier than the reference date.
///
/// This method is a designated initializer for the `NSDate` class and is declared primarily for the use of subclasses of `NSDate`. When you subclass `NSDate` to create a concrete date class, you must override this method.
- (instancetype)initWithTimeIntervalSinceReferenceDate:(NSTimeInterval)ti NS_DESIGNATED_INITIALIZER;
/// Returns a date object initialized from data in the given unarchiver.
- (nullable instancetype)initWithCoder:(NSCoder *)coder NS_DESIGNATED_INITIALIZER;

@end

@interface NSDate (NSExtendedDate)

/// Returns the interval between the receiver and another given date.
///
/// - Parameter anotherDate: The date with which to compare the receiver. You must pass a non-`nil` date object.
/// - Returns: The interval between the receiver and the `anotherDate` parameter. If the receiver is earlier than `anotherDate`, the return value is negative. If `anotherDate` is `nil`, the results are undefined.
- (NSTimeInterval)timeIntervalSinceDate:(NSDate *)anotherDate;
/// The interval between the date object and the current date and time.
///
/// If the date object is earlier than the current date and time, this property's value is negative.
@property (readonly) NSTimeInterval timeIntervalSinceNow;
/// The interval between the date object and 00:00:00 UTC on 1 January 1970.
///
/// This property's value is negative if the date object is earlier than 00:00:00 UTC on 1 January 1970.
@property (readonly) NSTimeInterval timeIntervalSince1970;

/// Returns a new date object that is set to a given number of seconds relative to the receiver.
///
/// @DeprecationSummary Use `dateByAddingTimeInterval:` instead.
///
/// - Parameter seconds: The number of seconds to add to the receiver. Use a negative value for seconds to have the returned object specify a date before the receiver.
/// - Returns: A new `NSDate` object that is set to `seconds` seconds relative to the receiver. The date returned might have a representation different from the receiver's.
- (id)addTimeInterval:(NSTimeInterval)seconds API_DEPRECATED("Use dateByAddingTimeInterval instead", macos(10.0,10.6), ios(2.0,4.0), watchos(2.0,2.0), tvos(9.0,9.0));
/// Returns a new date object that is set to a given number of seconds relative to the receiver.
///
/// - Parameter ti: The number of seconds to add to the receiver. Use a negative value for seconds to have the returned object specify a date before the receiver.
/// - Returns: A new `NSDate` object that is set to `seconds` seconds relative to the receiver. The date returned might have a representation different from the receiver's.
- (instancetype)dateByAddingTimeInterval:(NSTimeInterval)ti API_AVAILABLE(macos(10.6), ios(2.0), watchos(2.0), tvos(9.0));

/// Returns the earlier of the receiver and another given date.
///
/// - Parameter anotherDate: The date with which to compare the receiver.
/// - Returns: The earlier of the receiver and `anotherDate`, determined using `timeIntervalSinceDate:`. If the receiver and `anotherDate` represent the same date, returns the receiver.
- (NSDate *)earlierDate:(NSDate *)anotherDate;
/// Returns the later of the receiver and another given date.
///
/// - Parameter anotherDate: The date with which to compare the receiver.
/// - Returns: The later of the receiver and `anotherDate`, determined using `timeIntervalSinceDate:`. If the receiver and `anotherDate` represent the same date, returns the receiver.
- (NSDate *)laterDate:(NSDate *)anotherDate;
/// Indicates the temporal ordering of the receiver and another given date.
///
/// - Parameter other: The date with which to compare the receiver. This value must not be `nil`. If the value is `nil`, the behavior is undefined and may change in future versions of macOS.
/// - Returns: `NSOrderedSame` if the two dates are exactly equal, `NSOrderedDescending` if the receiver is later in time than `other`, and `NSOrderedAscending` if the receiver is earlier in time than `other`.
///
/// This method detects sub-second differences between dates. If you want to compare dates with a less fine granularity, use `timeIntervalSinceDate:` to compare the two dates.
- (NSComparisonResult)compare:(NSDate *)other;
/// Returns a Boolean value that indicates whether a given object is a date that is exactly equal the receiver.
///
/// - Parameter otherDate: The date to compare with the receiver.
/// - Returns: `YES` if the `otherDate` is an `NSDate` object and is exactly equal to the receiver, otherwise `NO`.
///
/// This method detects sub-second differences between dates. If you want to compare dates with a less fine granularity, use `timeIntervalSinceDate:` to compare the two dates.
- (BOOL)isEqualToDate:(NSDate *)otherDate;

/// A string representation of the date object.
///
/// The representation is useful for debugging only. There are a number of options to acquire a formatted string for a date including: date formatters (see `NSDateFormatter`), and the `NSDate` methods `descriptionWithLocale:`.
@property (readonly, copy) NSString *description;
/// Returns a string representation of the date using the given locale.
///
/// - Parameter locale: An `NSLocale` object. If you pass `nil`, `NSDate` formats the date in the same way as the `description` property.
/// - Returns: A string representation of the receiver, using the given locale, or if the locale argument is `nil`, in the international format `YYYY-MM-DD HH:MM:SS +/-HHMM`, where `+/-HHMM` represents the time zone offset in hours and minutes from UTC (for example, "2001-03-24 10:45:32 +0600").
- (NSString *)descriptionWithLocale:(nullable id)locale;

/// The interval between 00:00:00 UTC on 1 January 2001 and the current date and time.
///
/// This method is the primitive method for `NSDate`. If you subclass `NSDate`, you must override this method with your own implementation for it.
@property (class, readonly) NSTimeInterval timeIntervalSinceReferenceDate;

@end

@interface NSDate (NSDateCreation)

/// Creates and returns a new date object set to the current date and time.
///
/// This method uses the default initializer method for the class, `init`.
+ (instancetype)date;
/// Creates and returns a date object set to a given number of seconds from the current date and time.
///
/// - Parameter secs: The number of seconds from the current date and time for the new date. Use a negative value to specify a date before the current date.
/// - Returns: An `NSDate` object set to `secs` seconds from the current date and time.
+ (instancetype)dateWithTimeIntervalSinceNow:(NSTimeInterval)secs;
/// Creates and returns a date object set to a given number of seconds from 00:00:00 UTC on 1 January 2001.
///
/// - Parameter ti: The number of seconds from the absolute reference date (00:00:00 UTC on 1 January 2001) for the new date. Use a negative argument to specify a date and time before the reference date.
/// - Returns: An `NSDate` object set to `ti` seconds from the absolute reference date.
+ (instancetype)dateWithTimeIntervalSinceReferenceDate:(NSTimeInterval)ti;
/// Creates and returns a date object set to the given number of seconds from 00:00:00 UTC on 1 January 1970.
///
/// - Parameter secs: The number of seconds from the reference date (00:00:00 UTC on 1 January 1970) for the new date. Use a negative argument to specify a date and time before the reference date.
/// - Returns: An `NSDate` object set to `secs` seconds from the reference date.
///
/// This method is useful for creating `NSDate` objects from `time_t` values returned by BSD system functions.
+ (instancetype)dateWithTimeIntervalSince1970:(NSTimeInterval)secs;
/// Creates and returns a date object set to a given number of seconds from the specified date.
///
/// - Parameter secsToBeAdded: The number of seconds to add to `date`. Use a negative argument to specify a date and time before `date`.
/// - Parameter date: The date.
/// - Returns: An `NSDate` object set to `secsToBeAdded` seconds from `date`.
+ (instancetype)dateWithTimeInterval:(NSTimeInterval)secsToBeAdded sinceDate:(NSDate *)date;

/// A date object representing a date in the distant future.
///
/// You can pass this value when an `NSDate` object is required to have the date argument essentially ignored. For example, the `NSWindow` method `nextEventMatchingMask:untilDate:inMode:dequeue:` returns `nil` if an event specified in the event mask does not happen before the specified date. You can use the object returned by `distantFuture` as the date argument to wait indefinitely for the event to occur.
@property (class, readonly, copy) NSDate *distantFuture;
/// A date object representing a date in the distant past.
///
/// You can use this object as a control date, a guaranteed temporal boundary.
@property (class, readonly, copy) NSDate *distantPast;

/// The current date and time, as of the time of access.
///
/// This is equivalent to initializing a new instance with `NSDate()` (or `[[NSDate alloc] init]` in Objective-C). The `NSDate` instance doesn't automatically update its time after you retrieve it.
@property (class, readonly, copy) NSDate *now API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0));

/// Returns a date object initialized relative to the current date and time by a given number of seconds.
///
/// - Parameter secs: The number of seconds from relative to the current date and time to which the receiver should be initialized. A negative value means the returned object will represent a date in the past.
/// - Returns: An `NSDate` object initialized relative to the current date and time by `secs` seconds.
- (instancetype)initWithTimeIntervalSinceNow:(NSTimeInterval)secs;
/// Returns a date object initialized relative to 00:00:00 UTC on 1 January 1970 by a given number of seconds.
///
/// - Parameter secs: The number of seconds from the reference date (00:00:00 UTC on 1 January 1970) for the new date. Use a negative argument to specify a date and time before the reference date.
/// - Returns: An `NSDate` object set to `seconds` seconds from the reference date.
///
/// This method is useful for creating `NSDate` objects from `time_t` values returned by BSD system functions.
- (instancetype)initWithTimeIntervalSince1970:(NSTimeInterval)secs;
/// Returns a date object initialized relative to another given date by a given number of seconds.
///
/// - Parameter secsToBeAdded: The number of seconds to add to `date`. A negative value means the receiver will be earlier than `date`.
/// - Parameter date: The reference date.
/// - Returns: An `NSDate` object initialized relative to `date` by `secsToBeAdded` seconds.
- (instancetype)initWithTimeInterval:(NSTimeInterval)secsToBeAdded sinceDate:(NSDate *)date;

@end

NS_HEADER_AUDIT_END(nullability, sendability)
