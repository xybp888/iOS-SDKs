/*	NSDateFormatter.h
	Copyright (c) 1995-2019, Apple Inc. All rights reserved.
*/

#import <Foundation/NSFormatter.h>
#include <CoreFoundation/CFDateFormatter.h>

@class NSLocale, NSDate, NSCalendar, NSTimeZone, NSError, NSArray<ObjectType>, NSMutableDictionary, NSString;

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

#if !defined(NS_CALENDAR_ENUM_DEPRECATED)
#define NS_CALENDAR_ENUM_DEPRECATED(A, B, C, D, ...) NS_ENUM_DEPRECATED(A, B, C, D, __VA_ARGS__)
#define NS_CALENDAR_DEPRECATED(A, B, C, D, ...) NS_DEPRECATED(A, B, C, D, __VA_ARGS__)
#define NS_CALENDAR_DEPRECATED_MAC(A, B, ...) NS_DEPRECATED_MAC(A, B, __VA_ARGS__)
#endif

/// A formatter that converts between dates and their textual representations.
///
/// Instances of ``DateFormatter`` create string representations of ``NSDate`` objects, and convert textual representations of dates and times into ``NSDate`` objects. For user-visible representations of dates and times, ``DateFormatter`` provides a variety of localized presets and configuration options. For fixed format representations of dates and times, you can specify a custom format string.
///
/// When working with date representations in ISO 8601 format, use ``ISO8601DateFormatter`` instead.
///
/// To represent an interval between two ``NSDate`` objects, use ``DateIntervalFormatter`` instead.
///
/// To represent a quantity of time specified by an ``NSDateComponents`` object, use ``DateComponentsFormatter`` instead.
///
/// > Tip:
/// > In Swift, you can use ``Date/FormatStyle`` or ``Date/VerbatimFormatStyle`` rather than ``DateFormatter``. The ``FormatStyle`` API offers a declarative idiom for customizing the formatting of various types. Also, Foundation caches identical ``FormatStyle`` instances, so you don't need to pass them around your app, or risk wasting memory with duplicate formatters.
///
/// ### Working With User-Visible Representations of Dates and Times
///
/// When displaying a date to a user, you set the ``dateStyle`` and ``timeStyle`` properties of the date formatter according to your particular needs. For example, if you want to show the month, day, and year without showing the time, you would set the ``dateStyle`` property to ``Style/long`` and the ``timeStyle`` property to ``Style/none``. Conversely, if you want to show only the time, you would set the `dateStyle` property to ``Style/none`` and the ``timeStyle`` property to ``Style/short``. Based on the values of the ``dateStyle`` and ``timeStyle`` properties, ``DateFormatter`` provides a representation of a specified date that is appropriate for a given locale.
///
/// @TabNavigator {
/// @Tab("Swift") {
/// ```swift
/// let dateFormatter = DateFormatter()
/// dateFormatter.dateStyle = .medium
/// dateFormatter.timeStyle = .none
///
/// let date = Date(timeIntervalSinceReferenceDate: 118800)
///
/// // US English Locale (en_US)
/// dateFormatter.locale = Locale(identifier: "en_US")
/// print(dateFormatter.string(from: date)) // Jan 2, 2001
///
/// // French Locale (fr_FR)
/// dateFormatter.locale = Locale(identifier: "fr_FR")
/// print(dateFormatter.string(from: date)) // 2 janv. 2001
///
/// // Japanese Locale (ja_JP)
/// dateFormatter.locale = Locale(identifier: "ja_JP")
/// print(dateFormatter.string(from: date)) // 2001/01/02
/// ```
/// }
/// @Tab("Objective-C") {
/// ```objc
/// NSDateFormatter *dateFormatter = [[NSDateFormatter alloc] init];
/// dateFormatter.dateStyle = NSDateFormatterMediumStyle;
/// dateFormatter.timeStyle = NSDateFormatterNoStyle;
///
/// NSDate *date = [NSDate dateWithTimeIntervalSinceReferenceDate:118800];
///
/// // US English Locale (en_US)
/// dateFormatter.locale = [[NSLocale alloc] initWithLocaleIdentifier:@"en_US"];
/// NSLog(@"%@", [dateFormatter stringFromDate:date]); // Jan 2, 2001
///
/// // French Locale (fr_FR)
/// dateFormatter.locale = [[NSLocale alloc] initWithLocaleIdentifier:@"fr_FR"];
/// NSLog(@"%@", [dateFormatter stringFromDate:date]); // 2 janv. 2001
///
/// // Japanese Locale (ja_JP)
/// dateFormatter.locale = [[NSLocale alloc] initWithLocaleIdentifier:@"ja_JP"];
/// NSLog(@"%@", [dateFormatter stringFromDate:date]); // 2001/01/02
/// ```
/// }
/// }
///
///
/// If you need to define a format that cannot be achieved using the predefined styles, you can use the ``setLocalizedDateFormatFromTemplate(_:)`` to specify a localized date format from a template.
///
/// @TabNavigator {
/// @Tab("Swift") {
/// ```swift
/// let dateFormatter = DateFormatter()
/// let date = Date(timeIntervalSinceReferenceDate: 410220000)
///
/// // US English Locale (en_US)
/// dateFormatter.locale = Locale(identifier: "en_US")
/// dateFormatter.setLocalizedDateFormatFromTemplate("MMMMd") // set template after setting locale
/// print(dateFormatter.string(from: date)) // December 31
///
/// // British English Locale (en_GB)
/// dateFormatter.locale = Locale(identifier: "en_GB")
/// dateFormatter.setLocalizedDateFormatFromTemplate("MMMMd") // // set template after setting locale
/// print(dateFormatter.string(from: date)) // 31 December
/// ```
/// }
/// @Tab("Objective-C") {
/// ```objc
/// NSDateFormatter *dateFormatter = [[NSDateFormatter alloc] init];
/// NSDate *date = [NSDate dateWithTimeIntervalSinceReferenceDate:410220000];
///
/// // US English Locale (en_US)
/// dateFormatter.locale = [[NSLocale alloc] initWithLocaleIdentifier:@"en_US"];
/// [dateFormatter setLocalizedDateFormatFromTemplate:@"MMMMd"]; // set template after setting locale
/// NSLog(@"%@", [dateFormatter stringFromDate:date]); // December 31
///
/// // British English Locale (en_GB)
/// dateFormatter.locale = [[NSLocale alloc] initWithLocaleIdentifier:@"en_GB"];
/// [dateFormatter setLocalizedDateFormatFromTemplate:@"MMMMd"]; // set template after setting locale
/// NSLog(@"%@", [dateFormatter stringFromDate:date]); // 31 December
/// ```
/// }
/// }
///
///
/// ### Working With Fixed Format Date Representations
///
/// > Important:
/// > In macOS 10.12 and later or iOS 10 and later, use the ``ISO8601DateFormatter`` class when working with ISO 8601 date representations.
///
/// When working with fixed format dates, such as RFC 3339, you set the ``dateFormat`` property to specify a format string. For most fixed formats, you should also set the ``locale`` property to a POSIX locale (`"en_US_POSIX"`), and set the ``timeZone`` property to UTC.
///
/// @TabNavigator {
/// @Tab("Swift") {
/// ```swift
/// let RFC3339DateFormatter = DateFormatter()
/// RFC3339DateFormatter.locale = Locale(identifier: "en_US_POSIX")
/// RFC3339DateFormatter.dateFormat = "yyyy-MM-dd'T'HH:mm:ssZZZZZ"
/// RFC3339DateFormatter.timeZone = TimeZone(secondsFromGMT: 0)
///
/// /* 39 minutes and 57 seconds after the 16th hour of December 19th, 1996 with an offset of -08:00 from UTC (Pacific Standard Time) */
/// let string = "1996-12-19T16:39:57-08:00"
/// let date = RFC3339DateFormatter.date(from: string)
/// ```
/// }
/// @Tab("Objective-C") {
/// ```objc
/// RFC3339DateFormatter = [[NSDateFormatter alloc] init];
/// RFC3339DateFormatter.locale = [NSLocale localeWithLocaleIdentifier:@"en_US_POSIX"];
/// RFC3339DateFormatter.dateFormat = @"yyyy-MM-dd'T'HH:mm:ssZZZZZ";
/// RFC3339DateFormatter.timeZone = [NSTimeZone timeZoneForSecondsFromGMT:0];
///
/// /* 39 minutes and 57 seconds after the 16th hour of December 19th, 1996 with an offset of -08:00 from UTC (Pacific Standard Time) */
/// NSString *string = @"1996-12-19T16:39:57-08:00";
/// NSDate *date = [RFC3339DateFormatter dateFromString:string];
/// ```
/// }
/// }
///
///
/// For more information, see [Technical Q&A QA1480 “NSDateFormatter and Internet Dates”](https://developer.apple.com/library/mac/qa/qa1480/).
///
/// ### Thread Safety
///
/// On iOS 7 and later `NSDateFormatter` is thread safe.
///
/// In macOS 10.9 and later `NSDateFormatter` is thread safe so long as you are using the modern behavior in a 64-bit app.
///
/// On earlier versions of the operating system, or when using the legacy formatter behavior or running in 32-bit in macOS, `NSDateFormatter` is not thread safe, and you therefore must not mutate a date formatter simultaneously from multiple threads.
NS_SWIFT_SENDABLE
@interface NSDateFormatter : NSFormatter {
@private
    NSMutableDictionary *_attributes;
    CFDateFormatterRef _formatter;
    NSUInteger _counter;
}

/// The capitalization formatting context used when formatting a date.
///
/// The formatting context allows the formatter to apply appropriate capitalization
/// depending on how the string will be used, and whether the locale makes capitalization
/// distinctions.
@property NSFormattingContext formattingContext API_AVAILABLE(macos(10.10), ios(8.0), watchos(2.0), tvos(9.0)); // default is NSFormattingContextUnknown

// - (id)init; // designated initializer

/// Returns by reference a date representation of a specified string and its date range,
/// as well as a Boolean value that indicates whether the system can parse the string.
///
/// - Parameters:
///   - obj: If the receiver is able to parse `string`, upon return contains a date
///     representation of `string`.
///   - string: The string to parse.
///   - rangep: If the receiver is able to parse `string`, upon return contains the range
///     of `string` used to create the date.
///   - error: If the receiver is unable to create a date by parsing `string`, upon return
///     contains an `NSError` object that describes the problem.
/// - Returns: `YES` if the receiver can create a date by parsing `string`,
///   otherwise `NO`.
- (BOOL)getObjectValue:(out id _Nullable * _Nullable)obj forString:(NSString *)string range:(inout nullable NSRange *)rangep error:(out NSError **)error;

/// Returns a string representation of a specified date that the system formats
/// using the receiver's current settings.
///
/// - Parameter date: The date to format.
/// - Returns: A string representation of `date`.
- (NSString *)stringFromDate:(NSDate *)date;

/// Returns a date representation of a specified string that the system interprets
/// using the receiver's current settings.
///
/// - Parameter string: The string to parse.
/// - Returns: A date representation of `string`. If `dateFromString:` can't parse
///   the string, returns `nil`.
- (nullable NSDate *)dateFromString:(NSString *)string;

/// The following constants specify predefined format styles for dates and times.
///
/// The format for these date and time styles is not exact because they depend on the
/// locale, user preference settings, and the operating system version. Do not use these
/// constants if you want an exact format.
typedef NS_ENUM(NSUInteger, NSDateFormatterStyle) {    // date and time format styles
    /// Specifies no style.
    ///
    /// Equal to `kCFDateFormatterNoStyle`.
    NSDateFormatterNoStyle = kCFDateFormatterNoStyle,
    /// Specifies a short style, typically numeric only, such as "11/23/37" or "3:30 PM".
    ///
    /// Equal to `kCFDateFormatterShortStyle`.
    NSDateFormatterShortStyle = kCFDateFormatterShortStyle,
    /// Specifies a medium style, typically with abbreviated text, such as
    /// "Nov 23, 1937" or "3:30:32 PM".
    ///
    /// Equal to `kCFDateFormatterMediumStyle`.
    NSDateFormatterMediumStyle = kCFDateFormatterMediumStyle,
    /// Specifies a long style, typically with full text, such as
    /// "November 23, 1937" or "3:30:32 PM PST".
    ///
    /// Equal to `kCFDateFormatterLongStyle`.
    NSDateFormatterLongStyle = kCFDateFormatterLongStyle,
    /// Specifies a full style with complete details, such as
    /// "Tuesday, April 12, 1952 AD" or "3:30:42 PM Pacific Standard Time".
    ///
    /// Equal to `kCFDateFormatterFullStyle`.
    NSDateFormatterFullStyle = kCFDateFormatterFullStyle
};

/// Constants that specify the behavior `NSDateFormatter` should exhibit.
typedef NS_ENUM(NSUInteger, NSDateFormatterBehavior) {
    /// Specifies default formatting behavior.
    NSDateFormatterBehaviorDefault = 0,
#if TARGET_OS_OSX
    /// Specifies formatting behavior equivalent to that in OS X 10.0.
    NSDateFormatterBehavior10_0 = 1000,
#endif
    /// Specifies formatting behavior equivalent for OS X 10.4.
    NSDateFormatterBehavior10_4 = 1040,
};


/// Returns a string representation of a specified date, that the system formats
/// for the current locale using the specified date and time styles.
///
/// - Parameters:
///   - date: A date.
///   - dstyle: A format style for the date. For possible values, see `NSDateFormatterStyle`.
///   - tstyle: A format style for the time. For possible values, see `NSDateFormatterStyle`.
/// - Returns: A localized string representation of `date` using the specified date
///   and time styles.
///
/// This method uses a date formatter configured with the current default settings.
/// The returned string is the same as if you configured and used a date formatter
/// as shown in the following example:
///
///     NSDateFormatter *formatter = [[NSDateFormatter alloc] init];
///     formatter.formatterBehavior = NSDateFormatterBehavior10_4;
///     formatter.dateStyle = dateStyle;
///     formatter.timeStyle = timeStyle;
///     NSString *result = [formatter stringForObjectValue:date];
+ (NSString *)localizedStringFromDate:(NSDate *)date dateStyle:(NSDateFormatterStyle)dstyle timeStyle:(NSDateFormatterStyle)tstyle API_AVAILABLE(macos(10.6), ios(4.0), watchos(2.0), tvos(9.0));

/// Returns a localized date format string representing the given date format components
/// arranged appropriately for the specified locale.
///
/// - Parameters:
///   - tmplate: A string containing date format patterns (such as "MM" or "h").
///   - opts: No options are currently defined — pass `0`.
///   - locale: The locale for which the template is required.
/// - Returns: A localized date format string representing the date format components
///   given in `tmplate`, arranged appropriately for the locale specified by `locale`.
///   The returned string may not contain exactly those components given in `tmplate`,
///   but may — for example — have locale-specific adjustments applied.
///
/// Different locales have different conventions for the ordering of date components.
/// You use this method to get an appropriate format string for a given set of components
/// for a specified locale (typically you use the current locale).
+ (nullable NSString *)dateFormatFromTemplate:(NSString *)tmplate options:(NSUInteger)opts locale:(nullable NSLocale *)locale API_AVAILABLE(macos(10.6), ios(4.0), watchos(2.0), tvos(9.0));

/// Returns the default formatting behavior for instances of the class.
///
/// For iOS and for macOS applications linked against macOS 10.5 and later,
/// the default is `NSDateFormatterBehavior10_4`.
@property (class) NSDateFormatterBehavior defaultFormatterBehavior;

/// Sets the date format from a template using the specified locale for the receiver.
///
/// - Parameter dateFormatTemplate: A string containing date format patterns
///   (such as "MM" or "h").
///
/// Calling this method is equivalent to, but not necessarily implemented as, setting
/// the `dateFormat` property to the result of calling the
/// `dateFormatFromTemplate:options:locale:` method, passing no options and the
/// `locale` property value.
///
/// > Important: You should call this method only after setting the `locale` of the receiver.
- (void) setLocalizedDateFormatFromTemplate:(NSString *)dateFormatTemplate API_AVAILABLE(macos(10.10), ios(8.0), watchos(2.0), tvos(9.0));

/// The date format string used by the receiver.
///
/// You should only set this property when working with fixed format representations.
/// For user-visible representations, you should use the `dateStyle` and `timeStyle`
/// properties, or the `setLocalizedDateFormatFromTemplate:` method if your desired
/// format cannot be achieved using the predefined styles; both of these properties
/// and this method provide a localized date representation appropriate for display
/// to the user.
@property (null_resettable, copy) NSString *dateFormat;

/// The date style of the receiver.
@property NSDateFormatterStyle dateStyle;

/// The time style of the receiver.
@property NSDateFormatterStyle timeStyle;

/// The locale for the receiver.
@property (null_resettable, copy) NSLocale *locale;

/// Indicates whether the formatter generates the deprecated calendar date type.
///
/// This property is `YES` if the formatter generates the deprecated `NSCalendarDate`
/// type, and is `NO` otherwise. You should use `NSDate` and `NSCalendar` rather
/// than `NSCalendarDate`.
@property BOOL generatesCalendarDates;

/// The formatter behavior for the receiver.
@property NSDateFormatterBehavior formatterBehavior;

/// The time zone for the receiver.
///
/// If unspecified, the system time zone is used.
@property (null_resettable, copy) NSTimeZone *timeZone;

/// The calendar for the receiver.
///
/// If unspecified, the logical calendar for the current user is used.
@property (null_resettable, copy) NSCalendar *calendar;

/// A Boolean value that indicates whether the receiver uses heuristics when parsing a string.
///
/// `YES` if the receiver has been set to use heuristics when parsing a string
/// to guess at the date which is intended, otherwise `NO`.
///
/// If a formatter is set to be lenient, when parsing a string it uses heuristics to
/// guess at the date which is intended. As with any guessing, it may get the result
/// date wrong (that is, a date other than that which was intended).
@property (getter=isLenient) BOOL lenient;

/// The earliest date that can be denoted by a two-digit year specifier.
///
/// If the two-digit start date is set to January 6, 1976, then "January 1, 76" is
/// interpreted as New Year's Day in 2076, whereas "February 14, 76" is interpreted
/// as Valentine's Day in 1976.
///
/// By default, this property is equal to December 31, 1949.
@property (nullable, copy) NSDate *twoDigitStartDate;

/// The default date for the receiver.
///
/// By default, this property is `nil`.
@property (nullable, copy) NSDate *defaultDate;

/// The era symbols for the receiver.
///
/// An array containing `NSString` objects representing the era symbols for the
/// receiver (for example, {"B.C.E.", "C.E."}).
@property (null_resettable, copy) NSArray<NSString *> *eraSymbols;

/// The month symbols for the receiver.
@property (null_resettable, copy) NSArray<NSString *> *monthSymbols;

/// The array of short month symbols for the receiver.
@property (null_resettable, copy) NSArray<NSString *> *shortMonthSymbols;

/// The array of weekday symbols for the receiver.
@property (null_resettable, copy) NSArray<NSString *> *weekdaySymbols;

/// The array of short weekday symbols for the receiver.
@property (null_resettable, copy) NSArray<NSString *> *shortWeekdaySymbols;

/// The AM symbol for the receiver.
@property (null_resettable, copy) NSString *AMSymbol;

/// The PM symbol for the receiver.
@property (null_resettable, copy) NSString *PMSymbol;

/// The long era symbols for the receiver.
///
/// An array containing `NSString` objects representing the era symbols for the
/// receiver (for example, {"Before Common Era", "Common Era"}).
@property (null_resettable, copy) NSArray<NSString *> *longEraSymbols API_AVAILABLE(macos(10.5), ios(2.0), watchos(2.0), tvos(9.0));

/// The very short month symbols for the receiver.
@property (null_resettable, copy) NSArray<NSString *> *veryShortMonthSymbols API_AVAILABLE(macos(10.5), ios(2.0), watchos(2.0), tvos(9.0));

/// The standalone month symbols for the receiver.
@property (null_resettable, copy) NSArray<NSString *> *standaloneMonthSymbols API_AVAILABLE(macos(10.5), ios(2.0), watchos(2.0), tvos(9.0));

/// The short standalone month symbols for the receiver.
@property (null_resettable, copy) NSArray<NSString *> *shortStandaloneMonthSymbols API_AVAILABLE(macos(10.5), ios(2.0), watchos(2.0), tvos(9.0));

/// The very short month symbols for the receiver.
@property (null_resettable, copy) NSArray<NSString *> *veryShortStandaloneMonthSymbols API_AVAILABLE(macos(10.5), ios(2.0), watchos(2.0), tvos(9.0));

/// The array of very short weekday symbols for the receiver.
@property (null_resettable, copy) NSArray<NSString *> *veryShortWeekdaySymbols API_AVAILABLE(macos(10.5), ios(2.0), watchos(2.0), tvos(9.0));

/// The array of standalone weekday symbols for the receiver.
@property (null_resettable, copy) NSArray<NSString *> *standaloneWeekdaySymbols API_AVAILABLE(macos(10.5), ios(2.0), watchos(2.0), tvos(9.0));

/// The array of short standalone weekday symbols for the receiver.
@property (null_resettable, copy) NSArray<NSString *> *shortStandaloneWeekdaySymbols API_AVAILABLE(macos(10.5), ios(2.0), watchos(2.0), tvos(9.0));

/// The array of very short standalone weekday symbols for the receiver.
@property (null_resettable, copy) NSArray<NSString *> *veryShortStandaloneWeekdaySymbols API_AVAILABLE(macos(10.5), ios(2.0), watchos(2.0), tvos(9.0));

/// The quarter symbols for the receiver.
@property (null_resettable, copy) NSArray<NSString *> *quarterSymbols API_AVAILABLE(macos(10.5), ios(2.0), watchos(2.0), tvos(9.0));

/// The short quarter symbols for the receiver.
@property (null_resettable, copy) NSArray<NSString *> *shortQuarterSymbols API_AVAILABLE(macos(10.5), ios(2.0), watchos(2.0), tvos(9.0));

/// The standalone quarter symbols for the receiver.
@property (null_resettable, copy) NSArray<NSString *> *standaloneQuarterSymbols API_AVAILABLE(macos(10.5), ios(2.0), watchos(2.0), tvos(9.0));

/// The short standalone quarter symbols for the receiver.
@property (null_resettable, copy) NSArray<NSString *> *shortStandaloneQuarterSymbols API_AVAILABLE(macos(10.5), ios(2.0), watchos(2.0), tvos(9.0));

/// The start date of the Gregorian calendar for the receiver.
///
/// This is used to specify the start date for the Gregorian calendar switch from the
/// Julian calendar. Different locales switched at different times. Normally you should
/// just accept the locale's default date for the switch.
@property (nullable, copy) NSDate *gregorianStartDate API_AVAILABLE(macos(10.5), ios(2.0), watchos(2.0), tvos(9.0));

/// A Boolean value that indicates whether the receiver uses phrases such as
/// "today" and "tomorrow" for the date component.
///
/// `YES` if the receiver uses relative date formatting, otherwise `NO`.
///
/// If a date formatter uses relative date formatting, where possible it replaces the
/// date component of its output with a phrase — such as "today" or "tomorrow" — that
/// indicates a relative date. The available phrases depend on the locale for the date
/// formatter; whereas, for dates in the future, English may only allow "tomorrow,"
/// French may allow "the day after the day after tomorrow."
@property BOOL doesRelativeDateFormatting API_AVAILABLE(macos(10.6), ios(4.0), watchos(2.0), tvos(9.0));

@end

#if TARGET_OS_OSX
@interface NSDateFormatter (NSDateFormatterCompatibility)

/// Initializes and returns an `NSDateFormatter` instance that uses the OS X 10.0
/// formatting behavior and the given date format string in its conversions.
///
/// - Parameters:
///   - format: The format for the receiver.
///   - flag: A flag that specifies whether the receiver should process dates entered
///     as expressions in the vernacular (for example, "tomorrow") — `YES` means
///     that it should.
/// - Returns: An initialized `NSDateFormatter` instance that uses `format` in its
///   conversions and that uses the OS X 10.0 formatting behavior.
///
/// `NSDateFormatter` attempts natural-language processing only after it fails to
/// interpret an entered string according to `format`. Natural-language processing
/// supports only a limited set of colloquial phrases, primarily in English. It may
/// give unexpected results, and its use is strongly discouraged.
///
/// > Important: You cannot use this method to initialize a formatter with the OS X 10.4
/// > formatting behavior, you must use `init`.
- (id)initWithDateFormat:(NSString *)format allowNaturalLanguage:(BOOL)flag API_DEPRECATED("Create an NSDateFormatter with `init` and set the dateFormat property instead.", macos(10.4, 10.9));

/// Returns a Boolean value that indicates whether the receiver attempts to process dates
/// entered as a vernacular string.
///
/// - Returns: `YES` if the receiver attempts to process dates entered as a vernacular
///   string ("today," "next week," "dinner time," and so on), otherwise `NO`.
///
/// Natural-language processing supports only a limited set of colloquial phrases,
/// primarily in English. It may give unexpected results, and its use is strongly
/// discouraged.
///
/// > Note: This method is for use with formatters using `NSDateFormatterBehavior10_0`
/// > behavior.
- (BOOL)allowsNaturalLanguage API_DEPRECATED("There is no replacement", macos(10.4, 10.9));

@end
#endif

NS_HEADER_AUDIT_END(nullability, sendability)
