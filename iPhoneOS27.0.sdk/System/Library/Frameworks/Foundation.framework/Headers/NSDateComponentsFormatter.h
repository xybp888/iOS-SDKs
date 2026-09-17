/*	NSDateComponentsFormatter.h
	Copyright (c) 2014-2019, Apple Inc. All rights reserved.
*/

#import <Foundation/NSFormatter.h>
#import <Foundation/NSCalendar.h>
#import <Foundation/NSNumberFormatter.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

/// Constants for specifying how to represent quantities of time.
///
/// All date and time values are localized and formatted according to the current user's language preferences.
///
/// The following table shows how the quantity of 9 hours, 41 minutes, and 30 seconds is displayed in the U.S. English locale for each style:
///
/// | Style | Displayed result |
/// |---|---|
/// | `spellOut` | "nine hours, forty-one minutes, thirty seconds" |
/// | `full` | "9 hours, 41 minutes, 30 seconds" |
/// | `short` | "9 hr, 41 min, 30 sec" |
/// | `brief` | "9hr 41min 30sec" |
/// | `abbreviated` | "9h 41m 30s" |
/// | `positional` | "9:31:30" |
API_AVAILABLE(macos(10.10), ios(8.0), watchos(2.0), tvos(9.0))
typedef NS_ENUM(NSInteger, NSDateComponentsFormatterUnitsStyle) {
    /// A style that uses the position of a unit of time to identify its value.
    ///
    /// This style is most commonly used for time values where the hour, minute, and second values are separated by colons.
    ///
    /// For example, one hour and ten minutes is displayed in the U.S. English locale as "1:10:00".
    ///
    /// > Note: This style may fall back to the behavior of `NSDateComponentsFormatterUnitsStyleAbbreviated` when attempting to display large time quantities.
    NSDateComponentsFormatterUnitsStylePositional = 0,
    /// A style that uses the most abbreviated spelling for units of time.
    ///
    /// This style represents the shortest representation of units and quantities of time.
    ///
    /// For example, the quantity of 3 years, 9 months, 26 days, 19 hours, and 17 seconds is displayed in the U.S. English locale as "3y 9mo 26d 19h 17s".
    NSDateComponentsFormatterUnitsStyleAbbreviated,
    /// A style that uses a shortened spelling for units.
    ///
    /// For example, the quantity of 3 years, 9 months, 26 days, 19 hours, and 17 seconds is displayed in the U.S. English locale as "3 yrs, 9 mths, 26 days, 19 hr, 17 sec".
    NSDateComponentsFormatterUnitsStyleShort,
    /// A style that spells out the units of time, but not the quantities.
    ///
    /// For example, the quantity of 3 years, 9 months, 26 days, 19 hours, and 17 seconds is displayed in the U.S. English locale as "3 years, 9 months, 26 days, 19 hours, 17 seconds".
    NSDateComponentsFormatterUnitsStyleFull,
    /// A style that spells out the units and quantities of time.
    ///
    /// For example, the quantity of 3 years, 9 months, 26 days, 19 hours, and 17 seconds is displayed in the U.S. English locale as "three years, nine months, twenty-six days, nineteen hours, seventeen seconds".
    NSDateComponentsFormatterUnitsStyleSpellOut,
    /// A style that uses a shortened spelling for units of time that is shorter than `NSDateComponentsFormatterUnitsStyleShort`.
    ///
    /// For example, the quantity of 3 years, 9 months, 26 days, 19 hours, and 17 seconds is displayed in the U.S. English locale as "3yrs 9mths 26days 19hr 17sec".
    NSDateComponentsFormatterUnitsStyleBrief API_AVAILABLE(macosx(10.12), ios(10.0), watchos(3.0), tvos(10.0))
};

/// Formatting constants for when values contain zeroes.
API_AVAILABLE(macos(10.10), ios(8.0), watchos(2.0), tvos(9.0))
typedef NS_OPTIONS(NSUInteger, NSDateComponentsFormatterZeroFormattingBehavior) {
    /// No formatting behavior. This behavior prevents the dropping of zero values or adding of zeroes for padding. For example, with hours, minutes, and seconds displayed, the abbreviated value for one hour and 10 seconds is "1h 0m 10s".
    NSDateComponentsFormatterZeroFormattingBehaviorNone = (0),
    /// The default formatting behavior. When using positional units, this behavior drops leading zeroes but pads middle and trailing values with zeros as needed. For example, with hours, minutes, and seconds displayed, the value for one hour and 10 seconds is "1:00:10". For all other unit styles, this behavior drops all units whose values are 0. For example, when days, hours, minutes, and seconds are allowed, the abbreviated version of one hour and 10 seconds is displayed as "1h 10s".
    NSDateComponentsFormatterZeroFormattingBehaviorDefault = (1 << 0),

    /// The drop leading zeroes formatting behavior. Units whose values are 0 are dropped starting at the beginning of the sequence. Units continue to be dropped until a non-zero value is encountered. For example, when days, hours, minutes, and seconds are allowed, the abbreviated version of ten minutes is displayed as "10m 0s".
    NSDateComponentsFormatterZeroFormattingBehaviorDropLeading = (1 << 1),
    /// The drop middle zero units behavior. Units whose values are 0 are dropped from anywhere in the middle of a sequence. For example, when days, hours, minutes, and seconds are allowed, the abbreviated version of one hour, zero minutes, and five seconds is displayed as "0d 1h 5s".
    NSDateComponentsFormatterZeroFormattingBehaviorDropMiddle = (1 << 2),
    /// The drop trailing zero units behavior. Units whose value is 0 are dropped starting at the end of the sequence. For example, when days, hours, minutes, and seconds are allowed, the abbreviated version of one hour is displayed as "0d 1h".
    NSDateComponentsFormatterZeroFormattingBehaviorDropTrailing = (1 << 3),
    /// The drop all zero units behavior. This behavior drops all units whose values are 0. For example, when days, hours, minutes, and seconds are allowed, the abbreviated version of one hour is displayed as "1h".
    NSDateComponentsFormatterZeroFormattingBehaviorDropAll = (NSDateComponentsFormatterZeroFormattingBehaviorDropLeading | NSDateComponentsFormatterZeroFormattingBehaviorDropMiddle | NSDateComponentsFormatterZeroFormattingBehaviorDropTrailing),

    /// The add padding zeroes behavior. This behavior pads values with zeroes as appropriate. For example, consider the value of one hour formatted using the positional and abbreviated unit styles. When days, hours, minutes, and seconds are allowed, the value is displayed as "0d 1:00:00" using the positional style, and as "0d 1h 0m 0s" using the abbreviated style.
    NSDateComponentsFormatterZeroFormattingBehaviorPad = (1 << 16),
};

/// A formatter that creates string representations of quantities of time.
///
/// An ``DateComponentsFormatter`` object takes quantities of time and formats them as a user-readable string. Use a date components formatter to create strings for your app's interface. The formatter object has many options for creating both abbreviated and expanded strings. The formatter takes the current user's locale and language into account when generating strings.
///
/// To use this class, create an instance, configure its properties, and call one of its methods to generate an appropriate string. The properties of this class let you configure the calendar and specify the date and time units you want displayed in the resulting string. The listing below shows how to configure a formatter to create the string "About 5 minutes remaining".
///
/// @TabNavigator {
/// @Tab("Swift") {
/// ```swift
/// let formatter = DateComponentsFormatter()
/// formatter.unitsStyle = .full
/// formatter.includesApproximationPhrase = true
/// formatter.includesTimeRemainingPhrase = true
/// formatter.allowedUnits = [.minute]
///
/// // Use the configured formatter to generate the string.
/// let outputString = formatter.string(from: 300.0)
/// ```
/// }
/// @Tab("Objective-C") {
/// ```objc
/// NSDateComponentsFormatter *formatter = [[NSDateComponentsFormatter alloc] init];
/// formatter.unitsStyle = NSDateComponentsFormatterUnitsStyleFull;
/// formatter.includesApproximationPhrase = YES;
/// formatter.includesTimeRemainingPhrase = YES;
/// formatter.allowedUnits = NSCalendarUnitMinute;
///
/// // Use the configured formatter to generate the string.
/// NSString* outputString = [formatter stringFromTimeInterval:300.0];
/// ```
/// }
/// }
///
///
/// The methods of this class may be called safely from any thread of your app. It is also safe to share a single instance of this class from multiple threads, with the caveat that you should not change the configuration of the object while another thread is using it to generate a string.
///
/// > Tip:
/// > In Swift, you can use ``Date/RelativeFormatStyle`` rather than ``DateComponentsFormatter``. The ``FormatStyle`` API offers a declarative idiom for customizing the formatting of various types. Also, Foundation caches identical ``FormatStyle`` instances, so you don't need to pass them around your app, or risk wasting memory with duplicate formatters.
NS_SWIFT_SENDABLE
API_AVAILABLE(macos(10.10), ios(8.0), watchos(2.0), tvos(9.0))
@interface NSDateComponentsFormatter : NSFormatter

/// Returns a formatted string based on the date information in the specified object.
///
/// @param obj An object containing the date and time information to format. The object in this parameter must be an instance of `NSDateComponents`.
/// @return A formatted string representing the specified date information.
- (nullable NSString *)stringForObjectValue:(nullable id)obj;

/// Returns a formatted string based on the specified date component information.
///
/// Use this method to format date information that is already broken down into the component day and time values.
///
/// @param components A date components object containing the date and time information to format. The `allowedUnits` property determines which date components are actually used to generate the string. All other date components are ignored. This parameter must not be `nil`.
/// @return A formatted string representing the specified date information.
- (nullable NSString *)stringFromDateComponents:(NSDateComponents *)components;

/// Returns a formatted string based on the time difference between two dates.
///
/// This method calculates the elapsed time between the `startDate` and `endDate` values and uses that information to generate the string. For example, if there is exactly one hour and ten minutes difference between the start and end dates, generating an abbreviated string would result in a string of "1h 10m".
///
/// Note that this is still formatting the quantity of time between the dates, not the pair of dates itself. For strings like "Feb 22nd - Feb 28th", use `NSDateIntervalFormatter`.
///
/// @param startDate The start time. This parameter must not be `nil`.
/// @param endDate The end time. This parameter must not be `nil`.
/// @return A formatted string representing the specified time information.
- (nullable NSString *)stringFromDate:(NSDate *)startDate toDate:(NSDate *)endDate;

/// Returns a formatted string based on the specified number of seconds.
///
/// This method formats the specified number of seconds into the appropriate units. For example, if the formatter allows the display of minutes and seconds, creating an abbreviated string for the value 70 seconds results in the string "1m 10s".
///
/// @param ti The time interval, measured in seconds. The value must be a finite number. Negative numbers are treated as positive numbers when creating the string.
/// @return A formatted string representing the specified time interval.
- (nullable NSString *)stringFromTimeInterval:(NSTimeInterval)ti;


/// Returns a localized string based on the specified date components and style option.
///
/// Use this convenience method to format a string using the default formatter values, with the exception of the `unitsStyle` value.
///
/// @param components The value to format.
/// @param unitsStyle The style for the resulting units. Use this parameter to specify whether you want the resulting string to use an abbreviated or more spelled out format.
/// @return A string containing the localized date and time information.
+ (nullable NSString *)localizedStringFromDateComponents:(NSDateComponents *)components unitsStyle:(NSDateComponentsFormatterUnitsStyle) unitsStyle;

/// The formatting style for unit names.
///
/// Configures the strings to use (if any) for unit names such as days, hours, minutes, and seconds. Use this property to specify whether you want abbreviated or shortened versions of unit names---for example, "hrs" instead of "hours".
///
/// The default value of this property is `NSDateComponentsFormatterUnitsStylePositional`.
@property NSDateComponentsFormatterUnitsStyle unitsStyle;

/// The bitmask of calendrical units such as day and month to include in the output string.
///
/// The allowed calendar units are:
///
///  - `NSCalendarUnitYear`
///  - `NSCalendarUnitMonth`
///  - `NSCalendarUnitWeekOfMonth` (used to mean "quantity of weeks")
///  - `NSCalendarUnitDay`
///  - `NSCalendarUnitHour`
///  - `NSCalendarUnitMinute`
///  - `NSCalendarUnitSecond`
///
/// Assigning any other calendar units to this property results in an exception.
@property NSCalendarUnit allowedUnits;

/// The formatting style for units whose value is 0.
///
/// When the value for a particular unit is 0, the zero formatting behavior determines whether that value is retained or omitted from any resulting strings. For example, when the formatting behavior is `NSDateComponentsFormatterZeroFormattingBehaviorDropTrailing`, the value of one hour, ten minutes, and zero seconds would omit the mention of seconds.
///
/// The default value of this property is `NSDateComponentsFormatterZeroFormattingBehaviorDefault`.
@property NSDateComponentsFormatterZeroFormattingBehavior zeroFormattingBehavior;

/// The default calendar to use when formatting date components.
///
/// The formatter uses the calendar in this property to format values that do not have an inherent calendar of their own. For example, the formatter uses this calendar when formatting an `NSTimeInterval` value.
///
/// The default value of this property is the autoupdating current calendar. Setting this property to `nil` causes the formatter to use the Gregorian calendar with the `en_US_POSIX` locale.
@property (nullable, copy) NSCalendar *calendar;

/// Where units have variable length (number of days in a month, number of hours in a day, etc.), `NSDateComponentsFormatter` will calculate as though counting from the date specified by the `referenceDate` in the appropriate calendar. Defaults to `[NSDate dateWithTimeIntervalSinceReferenceDate:0]` at the time of the `-stringForObjectValue:` call if not set. Set to `nil` to get the default behavior.
@property (nullable, copy) NSDate *referenceDate API_AVAILABLE(macosx(10.13), ios(11.0), watchos(4.0), tvos(11.0));

/// A Boolean indicating whether non-integer units may be used for values.
///
/// Fractional units may be used when a value cannot be exactly represented using the available units. For example, if minutes are not allowed, the value "1h 30m" could be formatted as "1.5h".
///
/// The default value of this property is `NO`.
@property BOOL allowsFractionalUnits;

/// The maximum number of time units to include in the output string.
///
/// Use this property to limit the number of units displayed in the resulting string. For example, with this property set to 2, instead of "1h 10m, 30s", the resulting string would be "1h 10m". Use this property when you are constrained for space or want to round up values to the nearest large unit.
///
/// The default value of this property is `0`, which does not cause the elimination of any units.
@property NSInteger maximumUnitCount;

/// A Boolean value indicating whether to collapse the largest unit into smaller units when a certain threshold is met.
///
/// An example of when this property might apply is when expressing 63 seconds worth of time. When this property is set to `YES`, the formatted value would be "63s". When the value of this property is `NO`, the formatted value would be "1m 3s".
///
/// The default value of this property is `NO`.
@property BOOL collapsesLargestUnit;

/// A Boolean value indicating whether the resulting phrase reflects an inexact time value.
///
/// Setting the value of this property to `YES` adds phrasing to output strings to reflect that the given time value is approximate and not exact. Using this property yields more correct phrasing than simply prepending the string "About" to an output string.
///
/// The default value of this property is `NO`.
@property BOOL includesApproximationPhrase;

/// A Boolean value indicating whether output strings reflect the amount of time remaining.
///
/// Setting this property to `YES` results in output strings like "30 minutes remaining".
///
/// The default value of this property is `NO`.
@property BOOL includesTimeRemainingPhrase;

/// Not yet supported.
@property NSFormattingContext formattingContext;

/// `NSDateComponentsFormatter` currently only implements formatting, not parsing. Until it implements parsing, this will always return `NO`.
- (BOOL)getObjectValue:(out id _Nullable * _Nullable)obj forString:(NSString *)string errorDescription:(out NSString * _Nullable * _Nullable)error;

@end

NS_HEADER_AUDIT_END(nullability, sendability)
