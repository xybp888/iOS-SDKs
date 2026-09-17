/*    NSRelativeDateTimeFormatter.h
      Copyright (c) 2018-2019, Apple Inc. All rights reserved.
 */

#import <Foundation/NSDate.h>
#import <Foundation/NSFormatter.h>

@class NSCalendar, NSLocale, NSDateComponents;

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

/// Specifies how to describe a relative date.
typedef NS_ENUM(NSInteger, NSRelativeDateTimeFormatterStyle) {
    /// A numeric relative date style (e.g. "1 day ago", "2 days ago", "1 week ago", "in 1 week").
    NSRelativeDateTimeFormatterStyleNumeric = 0,
    /// A named relative date style (e.g. "yesterday", "2 days ago", "last week", "next week"). Falls back to the numeric style if no name is available.
    NSRelativeDateTimeFormatterStyleNamed,
} API_AVAILABLE(macosx(10.15), ios(13.0), watchos(6.0), tvos(13.0));

/// Specifies how to format the quantity or the name of the unit.
typedef NS_ENUM(NSInteger, NSRelativeDateTimeFormatterUnitsStyle) {
    /// The full units style (e.g. "2 months ago").
    NSRelativeDateTimeFormatterUnitsStyleFull = 0,
    /// The spelled-out units style (e.g. "two months ago").
    NSRelativeDateTimeFormatterUnitsStyleSpellOut,
    /// The short units style (e.g. "2 mo. ago").
    NSRelativeDateTimeFormatterUnitsStyleShort,
    /// The abbreviated units style (e.g. "2 mo. ago"). May give different results in languages other than English.
    NSRelativeDateTimeFormatterUnitsStyleAbbreviated,
} API_AVAILABLE(macosx(10.15), ios(13.0), watchos(6.0), tvos(13.0));

/// A formatter that creates locale-aware string representations of a relative date or time.
///
/// Use the strings that the formatter produces, such as "1 hour ago", "in 2 weeks", "yesterday", and "tomorrow" as standalone strings. Embedding them in other strings may not be grammatically correct.
API_AVAILABLE(macosx(10.15), ios(13.0), watchos(6.0), tvos(13.0))
@interface NSRelativeDateTimeFormatter : NSFormatter
#if !__OBJC2__
{
    @private
    void * _formatter;
    NSRelativeDateTimeFormatterStyle _dateTimeStyle;
    NSRelativeDateTimeFormatterUnitsStyle _unitsStyle;
    NSFormattingContext _formattingContext;
    NSCalendar *_calendar;
    NSLocale *_locale;
}
#endif // !__OBJC2__

/// Specifies how to describe a relative date.
///
/// For example, "yesterday" vs "1 day ago" in English. Default is `NSRelativeDateTimeFormatterStyleNumeric`.
@property NSRelativeDateTimeFormatterStyle dateTimeStyle;

/// Specifies how to format the quantity or the name of the unit.
///
/// For example, "1 day ago" vs "one day ago" in English. Default is `NSRelativeDateTimeFormatterUnitsStyleFull`.
@property NSRelativeDateTimeFormatterUnitsStyle unitsStyle;

/// Specifies the formatting context of the output.
///
/// Default is `NSFormattingContextUnknown`.
@property NSFormattingContext formattingContext;

/// Specifies the calendar to use for formatting values that do not have an inherent calendar of their own.
///
/// Defaults to `autoupdatingCurrentCalendar`. Also resets to `autoupdatingCurrentCalendar` on assignment of `nil`.
@property (null_resettable, copy) NSCalendar *calendar;

/// Specifies the locale of the output string.
///
/// Defaults to and resets on assignment of `nil` to the calendar's locale.
@property (null_resettable, copy) NSLocale *locale;

/// Returns a formatted string representing a relative time from the given date components.
///
/// Negative component values are evaluated as a date in the past.
/// This method formats the value of the least granular unit in the `NSDateComponents` object, and does not provide a compound format of the date component.
///
/// Note this method only supports the following components: year, month, week of month, day, hour, minute, and second. The rest will be ignored.
- (NSString *)localizedStringFromDateComponents:(NSDateComponents *)dateComponents;

/// Returns a formatted string representing a relative time from the given time interval.
///
/// Negative time interval is evaluated as a date in the past.
- (NSString *)localizedStringFromTimeInterval:(NSTimeInterval)timeInterval;

/// Formats the date interval from the reference date to the given date using the formatter's calendar.
- (NSString *)localizedStringForDate:(NSDate *)date relativeToDate:(NSDate *)referenceDate;

/// Creates a formatted string for a date relative to the current date and time.
///
/// To determine the relative interval, the formatter uses `[NSDate date]` as the reference date.
///
/// - Parameters:
///   - obj: A date object to format.
/// - Returns: A string that represents the date interval between a date and the current date and time, or `nil` if `obj` isn't an instance of `NSDate`.
- (nullable NSString *)stringForObjectValue:(nullable id)obj;

@end

NS_HEADER_AUDIT_END(nullability, sendability)
