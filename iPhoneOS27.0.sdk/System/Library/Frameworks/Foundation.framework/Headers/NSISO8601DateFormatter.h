/*
    NSISO8601DateFormatter.h
    Copyright (c) 2015-2019, Apple Inc. All rights reserved.
 */

#include <CoreFoundation/CFDateFormatter.h>
#import <Foundation/NSFormatter.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

@class NSString, NSDate, NSTimeZone;

/// Options used to generate and parse ISO 8601 date representations.
typedef NS_OPTIONS(NSUInteger, NSISO8601DateFormatOptions) {
    /// The date representation includes the year. The format for year is inferred
    /// based on whether or not the week of year option is specified.
    ///
    /// - If week of year is present, `YYYY` is used to display week dates.
    /// - If week of year is not present, `yyyy` is used by default.
    NSISO8601DateFormatWithYear API_AVAILABLE(macosx(10.12), ios(10.0), watchos(3.0), tvos(10.0)) = kCFISO8601DateFormatWithYear,

    /// The date representation includes the month. The format for month is `MM`.
    NSISO8601DateFormatWithMonth API_AVAILABLE(macosx(10.12), ios(10.0), watchos(3.0), tvos(10.0)) = kCFISO8601DateFormatWithMonth,

    /// The date representation includes the week of the year.
    /// The format for week of year is `ww`, including the `W` prefix.
    NSISO8601DateFormatWithWeekOfYear API_AVAILABLE(macosx(10.12), ios(10.0), watchos(3.0), tvos(10.0)) = kCFISO8601DateFormatWithWeekOfYear,  // This includes the "W" prefix (e.g. "W49")

    /// The date representation includes the day. The format for day is inferred
    /// based on provided options:
    ///
    /// - If month is not present, day of year (`DDD`) is used.
    /// - If month is present, day of month (`dd`) is used.
    /// - If either weekOfMonth or weekOfYear is present, local day of week (`ee`) is used.
    NSISO8601DateFormatWithDay API_AVAILABLE(macosx(10.12), ios(10.0), watchos(3.0), tvos(10.0)) = kCFISO8601DateFormatWithDay,

    /// The date representation includes the time. The format for time is `HH:mm:ss`.
    NSISO8601DateFormatWithTime API_AVAILABLE(macosx(10.12), ios(10.0), watchos(3.0), tvos(10.0)) = kCFISO8601DateFormatWithTime,  // This uses the format "HHmmss"

    /// The date representation includes the timezone. The format for timezone is `ZZZZZ`.
    NSISO8601DateFormatWithTimeZone API_AVAILABLE(macosx(10.12), ios(10.0), watchos(3.0), tvos(10.0)) = kCFISO8601DateFormatWithTimeZone,

    /// The date representation uses a space (` `) instead of `T` between the date and time.
    NSISO8601DateFormatWithSpaceBetweenDateAndTime API_AVAILABLE(macosx(10.12), ios(10.0), watchos(3.0), tvos(10.0)) = kCFISO8601DateFormatWithSpaceBetweenDateAndTime,

    /// The date representation uses the dash separator (`-`) in the date.
    NSISO8601DateFormatWithDashSeparatorInDate API_AVAILABLE(macosx(10.12), ios(10.0), watchos(3.0), tvos(10.0)) = kCFISO8601DateFormatWithDashSeparatorInDate,

    /// The date representation uses the colon separator (`:`) in the time.
    NSISO8601DateFormatWithColonSeparatorInTime API_AVAILABLE(macosx(10.12), ios(10.0), watchos(3.0), tvos(10.0)) = kCFISO8601DateFormatWithColonSeparatorInTime,

    /// The date representation uses the colon separator (`:`) in the time zone.
    NSISO8601DateFormatWithColonSeparatorInTimeZone API_AVAILABLE(macosx(10.12), ios(10.0), watchos(3.0), tvos(10.0)) = kCFISO8601DateFormatWithColonSeparatorInTimeZone,

    NSISO8601DateFormatWithFractionalSeconds API_AVAILABLE(macosx(10.13), ios(11.0), watchos(4.0), tvos(11.0)) = kCFISO8601DateFormatWithFractionalSeconds,  // Add 3 significant digits of fractional seconds (".SSS")

    /// The date representation includes the year, month, and day. Equivalent to specifying
    /// `NSISO8601DateFormatWithYear`, `NSISO8601DateFormatWithMonth`, and
    /// `NSISO8601DateFormatWithDay`.
    NSISO8601DateFormatWithFullDate API_AVAILABLE(macosx(10.12), ios(10.0), watchos(3.0), tvos(10.0)) = kCFISO8601DateFormatWithFullDate,

    /// The date representation includes the hour, minute, and second.
    NSISO8601DateFormatWithFullTime API_AVAILABLE(macosx(10.12), ios(10.0), watchos(3.0), tvos(10.0)) = kCFISO8601DateFormatWithFullTime,

    /// The format used for internet date times, according to the RFC 3339 standard.
    /// Equivalent to specifying `NSISO8601DateFormatWithFullDate`,
    /// `NSISO8601DateFormatWithFullTime`, `NSISO8601DateFormatWithDashSeparatorInDate`,
    /// `NSISO8601DateFormatWithColonSeparatorInTime`, and
    /// `NSISO8601DateFormatWithColonSeparatorInTimeZone`.
    NSISO8601DateFormatWithInternetDateTime API_AVAILABLE(macosx(10.12), ios(10.0), watchos(3.0), tvos(10.0)) = kCFISO8601DateFormatWithInternetDateTime,  // RFC 3339
};

/// A formatter that converts between dates and their ISO 8601 string representations.
///
/// The ``ISO8601DateFormatter`` class generates and parses string representations of dates following the [ISO 8601](http://www.iso.org/iso/home/standards/iso8601) standard. Use this class to create ISO 8601 representations of dates and create dates from text strings in ISO 8601 format.
///
/// > Tip:
/// > In Swift, you can use ``Date/ISO8601FormatStyle`` rather than ``ISO8601DateFormatter``. The ``FormatStyle`` API offers a declarative idiom for customizing the formatting of various types. Also, Foundation caches identical ``FormatStyle`` instances, so you don't need to pass them around your app, or risk wasting memory with duplicate formatters.
API_AVAILABLE(macosx(10.12), ios(10.0), watchos(3.0), tvos(10.0))
@interface NSISO8601DateFormatter : NSFormatter <NSSecureCoding> {
@private
    CFDateFormatterRef _formatter;
    NSTimeZone *_timeZone;
    NSISO8601DateFormatOptions _formatOptions;
}

/// The time zone used to create and parse date representations. When unspecified, GMT is used.
///
/// Resetting this property can incur a significant performance cost, as it may cause
/// internal state to be regenerated.
@property (null_resettable, copy) NSTimeZone *timeZone;

/// Options for generating and parsing ISO 8601 date representations.
///
/// The ISO 8601 specification allows for dates to be expressed in a variety of ways.
/// You can configure the format used to parse and generate representations by specifying
/// various combinations of format options.
///
/// > Important: Resetting this property can incur a significant performance cost,
/// > as it may cause internal state to be regenerated.
@property NSISO8601DateFormatOptions formatOptions;

/// Initializes an ISO 8601 date formatter with default format, time zone, and options.
///
/// By default, a formatter is initialized to use the GMT time zone and preconfigured
/// with the RFC 3339 standard format (`yyyy-MM-dd'T'HH:mm:ssXXXXX`) using the following
/// options: `NSISO8601DateFormatWithInternetDateTime`,
/// `NSISO8601DateFormatWithDashSeparatorInDate`,
/// `NSISO8601DateFormatWithColonSeparatorInTime`, and
/// `NSISO8601DateFormatWithColonSeparatorInTimeZone`.
- (instancetype)init NS_DESIGNATED_INITIALIZER;

/// Creates and returns an ISO 8601 formatted string representation of the specified date.
///
/// - Parameter date: The date to be represented.
/// - Returns: A user-readable string representing the date.
- (NSString *)stringFromDate:(NSDate *)date;

/// Creates and returns a date object from the specified ISO 8601 formatted string
/// representation.
///
/// - Parameter string: The ISO 8601 formatted string representation of a date.
/// - Returns: A date object, or `nil` if no valid date was found.
- (nullable NSDate *)dateFromString:(NSString *)string;

/// Creates a representation of the specified date with a given time zone and format options.
///
/// - Parameters:
///   - date: The date to be represented.
///   - timeZone: The time zone used.
///   - formatOptions: The options used. For possible values, see `NSISO8601DateFormatOptions`.
/// - Returns: A user-readable string representing the date.
+ (NSString *)stringFromDate:(NSDate *)date timeZone:(NSTimeZone *)timeZone formatOptions:(NSISO8601DateFormatOptions)formatOptions;

@end

NS_HEADER_AUDIT_END(nullability, sendability)
