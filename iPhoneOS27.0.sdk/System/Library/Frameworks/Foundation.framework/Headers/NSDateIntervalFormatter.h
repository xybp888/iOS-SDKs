/*	NSDateIntervalFormatter.h
        Copyright (c) 2013-2019, Apple Inc. All rights reserved.
 */

#import <Foundation/NSFormatter.h>
#import <Foundation/NSDateInterval.h>
#include <dispatch/dispatch.h>
@class NSLocale, NSCalendar, NSTimeZone, NSDate;

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

/// Formatting styles for individual date and time values.
typedef NS_ENUM(NSUInteger, NSDateIntervalFormatterStyle) {
    /// No style.
    NSDateIntervalFormatterNoStyle = 0,
    /// A short style.
    NSDateIntervalFormatterShortStyle = 1,
    /// A medium style.
    NSDateIntervalFormatterMediumStyle = 2,
    /// A long style.
    NSDateIntervalFormatterLongStyle = 3,
    /// A full style.
    NSDateIntervalFormatterFullStyle = 4
} API_AVAILABLE(macos(10.10), ios(8.0), watchos(2.0), tvos(9.0));

/// A formatter that creates string representations of time intervals.
///
/// A ``DateIntervalFormatter`` object creates user-readable strings from pairs of dates. Use a date interval formatter to create user-readable strings of the form _\<start\>_ `-` _\<end\>_ for your app's interface, where _\<start\>_ and _\<end\>_ are date values that you supply. The formatter uses locale and language information, along with custom formatting options, to define the content of the resulting string. You can specify different styles for the date and time information in each date value.
///
/// To use this class, create an instance, configure its properties, and call the ``string(from:to:)`` method to generate a string. The properties of this class let you configure the calendar and specify the style to apply to date and time values. Given a current date of January 16, 2015, Configuring the Formatter Options shows how to configure a formatter object and generate the string "1/16/15 - 1/17/15".
///
///
///
/// Configuring a formatter object
///
/// @TabNavigator {
/// @Tab("Swift") {
/// ```swift
/// let formatter = DateIntervalFormatter()
/// formatter.dateStyle = .short
/// formatter.timeStyle = .none
///
/// // Create two dates that are exactly 1 day apart.
/// let startDate = Date()
/// let endDate = Date(timeInterval: 86400, since: startDate)
///
/// // Use the configured formatter to generate the string.
/// let outputString = formatter.string(from: startDate, to: endDate)
/// ```
/// }
/// @Tab("Objective-C") {
/// ```objc
/// NSDateIntervalFormatter* formatter = [[NSDateIntervalFormatter alloc] init];
/// formatter.dateStyle = NSDateIntervalFormatterShortStyle;
/// formatter.timeStyle = NSDateIntervalFormatterNoStyle;
///
/// // Create two dates that are exactly 1 day apart.
/// NSDate* startDate = [NSDate date];
/// NSDate* endDate = [NSDate dateWithTimeInterval:86400 sinceDate:startDate];
///
/// // Use the configured formatter to generate the string.
/// NSString* outputString = [formatter stringFromDate:startDate toDate:endDate];
/// ```
/// }
/// }
///
///
/// > Note:
/// > Always set to the ``dateStyle`` and ``timeStyle`` properties to appropriate values before generating any strings.
///
/// The ``string(from:to:)`` method may be called safely from any thread of your app. It is also safe to share a single instance of this class from multiple threads, with the caveat that you should not change the configuration of the object while another thread is using it to generate a string.
///
/// > Tip:
/// > In Swift, you can use ``Date/IntervalFormatStyle`` rather than ``DateIntervalFormatter``. The ``FormatStyle`` API offers a declarative idiom for customizing the formatting of various types. Also, Foundation caches identical ``FormatStyle`` instances, so you don't need to pass them around your app, or risk wasting memory with duplicate formatters.
NS_SWIFT_SENDABLE
API_AVAILABLE(macos(10.10), ios(8.0), watchos(2.0), tvos(9.0))
@interface NSDateIntervalFormatter : NSFormatter

/// The locale for the formatter. Default is `[NSLocale currentLocale]`.
@property (null_resettable, copy) NSLocale   *locale;
/// The calendar for the formatter. Default is the calendar of the locale.
@property (null_resettable, copy) NSCalendar *calendar;
/// The time zone for the formatter. Default is `[NSTimeZone defaultTimeZone]`.
@property (null_resettable, copy) NSTimeZone *timeZone;
/// The date template for the formatter. Default is an empty string.
@property (null_resettable, copy) NSString   *dateTemplate;
/// The date style for the formatter. Default is `NSDateIntervalFormatterNoStyle`.
@property NSDateIntervalFormatterStyle dateStyle;
/// The time style for the formatter. Default is `NSDateIntervalFormatterNoStyle`.
@property NSDateIntervalFormatterStyle timeStyle;

/// Returns a formatted date interval from the specified start date to end date.
///
/// If the range is smaller than the resolution specified by the `dateTemplate`, a single date format will be produced.
/// If the range is larger than the format specified by the `dateTemplate`, a locale-specific fallback will be used to format the items missing from the pattern.
///
/// For example, if the range is 2010-03-04 07:56 - 2010-03-04 19:56 (12 hours)
///      - The pattern `jm` will produce
///         for `en_US`, "7:56 AM - 7:56 PM"
///         for `en_GB`, "7:56 - 19:56"
///      - The pattern `MMMd` will produce
///         for `en_US`, "Mar 4"
///         for `en_GB`, "4 Mar"
///      If the range is 2010-03-04 07:56 - 2010-03-08 16:11 (4 days, 8 hours, 15 minutes)
///      - The pattern `jm` will produce
///         for `en_US`, "3/4/2010 7:56 AM - 3/8/2010 4:11 PM"
///         for `en_GB`, "4/3/2010 7:56 - 8/3/2010 16:11"
///      - The pattern `MMMd` will produce
///         for `en_US`, "Mar 4-8"
///         for `en_GB`, "4-8 Mar"
- (NSString *)stringFromDate:(NSDate *)fromDate toDate:(NSDate *)toDate;

/// Returns a formatted string for the given date interval.
- (nullable NSString *)stringFromDateInterval:(NSDateInterval *)dateInterval API_AVAILABLE(macosx(10.12), ios(10.0), watchos(3.0), tvos(10.0));

@end

NS_HEADER_AUDIT_END(nullability, sendability)
