/*	NSCalendar.h
	Copyright (c) 2004-2019, Apple Inc. All rights reserved.
*/

#import <Foundation/NSObject.h>
#import <Foundation/NSRange.h>
#import <Foundation/NSDate.h>
#import <Foundation/NSNotification.h>
#include <CoreFoundation/CFCalendar.h>

@class NSDateComponents, NSLocale, NSTimeZone, NSString, NSArray<ObjectType>;

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

#if !defined(NS_CALENDAR_ENUM_DEPRECATED)
#define NS_CALENDAR_ENUM_DEPRECATED(A, B, C, D, ...) NS_ENUM_DEPRECATED(A, B, C, D, __VA_ARGS__)
#define NS_CALENDAR_DEPRECATED(A, B, C, D, ...) NS_DEPRECATED(A, B, C, D, __VA_ARGS__)
#define NS_CALENDAR_DEPRECATED_MAC(A, B, ...) NS_DEPRECATED_MAC(A, B, __VA_ARGS__)
#endif

/// The supported calendar types.
///
/// Use these identifiers to specify the kind of calendar. The Gregorian calendar is the calendar typically used in Europe, the Western Hemisphere, and elsewhere.
typedef NSString * NSCalendarIdentifier NS_TYPED_EXTENSIBLE_ENUM;

/// Identifier for the Gregorian calendar.
FOUNDATION_EXPORT NSCalendarIdentifier const NSCalendarIdentifierGregorian  API_AVAILABLE(macos(10.6), ios(4.0), watchos(2.0), tvos(9.0)); // the common calendar in Europe, the Western Hemisphere, and elsewhere
/// Identifier for the Buddhist calendar.
FOUNDATION_EXPORT NSCalendarIdentifier const NSCalendarIdentifierBuddhist            API_AVAILABLE(macos(10.6), ios(4.0), watchos(2.0), tvos(9.0));
/// Identifier for the Chinese calendar.
FOUNDATION_EXPORT NSCalendarIdentifier const NSCalendarIdentifierChinese             API_AVAILABLE(macos(10.6), ios(4.0), watchos(2.0), tvos(9.0));
/// Identifier for the Coptic calendar.
FOUNDATION_EXPORT NSCalendarIdentifier const NSCalendarIdentifierCoptic              API_AVAILABLE(macos(10.6), ios(4.0), watchos(2.0), tvos(9.0));
/// Identifier for the Ethiopic Amete Mihret calendar.
FOUNDATION_EXPORT NSCalendarIdentifier const NSCalendarIdentifierEthiopicAmeteMihret API_AVAILABLE(macos(10.6), ios(4.0), watchos(2.0), tvos(9.0));
/// Identifier for the Ethiopic Amete Alem calendar.
FOUNDATION_EXPORT NSCalendarIdentifier const NSCalendarIdentifierEthiopicAmeteAlem   API_AVAILABLE(macos(10.6), ios(4.0), watchos(2.0), tvos(9.0));
/// Identifier for the Hebrew calendar.
FOUNDATION_EXPORT NSCalendarIdentifier const NSCalendarIdentifierHebrew              API_AVAILABLE(macos(10.6), ios(4.0), watchos(2.0), tvos(9.0));
/// Identifier for the ISO 8601 calendar.
FOUNDATION_EXPORT NSCalendarIdentifier const NSCalendarIdentifierISO8601             API_AVAILABLE(macos(10.6), ios(4.0), watchos(2.0), tvos(9.0));
/// Identifier for the Indian calendar.
FOUNDATION_EXPORT NSCalendarIdentifier const NSCalendarIdentifierIndian              API_AVAILABLE(macos(10.6), ios(4.0), watchos(2.0), tvos(9.0));
/// Identifier for the Islamic calendar.
FOUNDATION_EXPORT NSCalendarIdentifier const NSCalendarIdentifierIslamic             API_AVAILABLE(macos(10.6), ios(4.0), watchos(2.0), tvos(9.0));
/// Identifier for the Islamic civil calendar.
FOUNDATION_EXPORT NSCalendarIdentifier const NSCalendarIdentifierIslamicCivil        API_AVAILABLE(macos(10.6), ios(4.0), watchos(2.0), tvos(9.0));
/// Identifier for the Japanese calendar.
FOUNDATION_EXPORT NSCalendarIdentifier const NSCalendarIdentifierJapanese            API_AVAILABLE(macos(10.6), ios(4.0), watchos(2.0), tvos(9.0));
/// Identifier for the Persian calendar.
FOUNDATION_EXPORT NSCalendarIdentifier const NSCalendarIdentifierPersian             API_AVAILABLE(macos(10.6), ios(4.0), watchos(2.0), tvos(9.0));
/// Identifier for the Republic of China (Minguo) calendar.
FOUNDATION_EXPORT NSCalendarIdentifier const NSCalendarIdentifierRepublicOfChina     API_AVAILABLE(macos(10.6), ios(4.0), watchos(2.0), tvos(9.0));
/// Identifier for the Islamic tabular calendar.
///
/// A simple tabular Islamic calendar using the astronomical/Thursday epoch of CE 622 July 15.
FOUNDATION_EXPORT NSCalendarIdentifier const NSCalendarIdentifierIslamicTabular      API_AVAILABLE(macos(10.10), ios(8.0), watchos(2.0), tvos(9.0));
/// Identifier for the Islamic Umm al-Qura calendar.
///
/// The Islamic Umm al-Qura calendar used in Saudi Arabia. This is based on astronomical calculation, instead of tabular behavior.
FOUNDATION_EXPORT NSCalendarIdentifier const NSCalendarIdentifierIslamicUmmAlQura    API_AVAILABLE(macos(10.10), ios(8.0), watchos(2.0), tvos(9.0));
FOUNDATION_EXPORT NSCalendarIdentifier const NSCalendarIdentifierBangla              API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));
FOUNDATION_EXPORT NSCalendarIdentifier const NSCalendarIdentifierGujarati            API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));
FOUNDATION_EXPORT NSCalendarIdentifier const NSCalendarIdentifierKannada             API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));
FOUNDATION_EXPORT NSCalendarIdentifier const NSCalendarIdentifierMalayalam           API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));
FOUNDATION_EXPORT NSCalendarIdentifier const NSCalendarIdentifierMarathi             API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));
FOUNDATION_EXPORT NSCalendarIdentifier const NSCalendarIdentifierOdia                API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));
FOUNDATION_EXPORT NSCalendarIdentifier const NSCalendarIdentifierTamil               API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));
FOUNDATION_EXPORT NSCalendarIdentifier const NSCalendarIdentifierTelugu              API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));
FOUNDATION_EXPORT NSCalendarIdentifier const NSCalendarIdentifierVikram              API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));
FOUNDATION_EXPORT NSCalendarIdentifier const NSCalendarIdentifierDangi               API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));
FOUNDATION_EXPORT NSCalendarIdentifier const NSCalendarIdentifierVietnamese          API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

/// Calendrical units such as year, month, day and hour.
typedef NS_OPTIONS(NSUInteger, NSCalendarUnit) {
        /// Identifier for the era unit.
        ///
        /// The corresponding value is an `NSInteger`.
        NSCalendarUnitEra                = kCFCalendarUnitEra,
        /// Identifier for the year unit.
        ///
        /// The corresponding value is an `NSInteger`.
        NSCalendarUnitYear               = kCFCalendarUnitYear,
        /// Identifier for the month unit.
        ///
        /// The corresponding value is an `NSInteger`.
        NSCalendarUnitMonth              = kCFCalendarUnitMonth,
        /// Identifier for the day unit.
        ///
        /// The corresponding value is an `NSInteger`.
        NSCalendarUnitDay                = kCFCalendarUnitDay,
        /// Identifier for the hour unit.
        ///
        /// The corresponding value is an `NSInteger`.
        NSCalendarUnitHour               = kCFCalendarUnitHour,
        /// Identifier for the minute unit.
        ///
        /// The corresponding value is an `NSInteger`.
        NSCalendarUnitMinute             = kCFCalendarUnitMinute,
        /// Identifier for the second unit.
        ///
        /// The corresponding value is a `double`.
        NSCalendarUnitSecond             = kCFCalendarUnitSecond,
        /// Identifier for the weekday unit.
        ///
        /// The corresponding value is an `NSInteger`. The weekday units are the numbers `1` through `N` (where for the Gregorian calendar `N`=`7` and `1` is Sunday).
        NSCalendarUnitWeekday            = kCFCalendarUnitWeekday,
        /// Identifier for the ordinal weekday unit.
        ///
        /// The corresponding value is an `NSInteger`. The weekday ordinal unit describes ordinal position within the month unit of the corresponding weekday unit. For example, in the Gregorian calendar a weekday ordinal unit of `2` for a weekday unit `3` indicates "the second Tuesday in the month".
        NSCalendarUnitWeekdayOrdinal     = kCFCalendarUnitWeekdayOrdinal,
        /// Identifier for the quarter of the calendar.
        ///
        /// The corresponding value is an `NSInteger`.
        ///
        /// > Important: The `NSCalendarUnitQuarter` unit is largely unimplemented, and is not recommended for use.
        NSCalendarUnitQuarter            API_AVAILABLE(macos(10.6), ios(4.0), watchos(2.0), tvos(9.0)) = kCFCalendarUnitQuarter,
        /// Identifier for the week of the month calendar unit.
        NSCalendarUnitWeekOfMonth        API_AVAILABLE(macos(10.7), ios(5.0), watchos(2.0), tvos(9.0)) = kCFCalendarUnitWeekOfMonth,
        /// Identifier for the week of the year calendar unit.
        NSCalendarUnitWeekOfYear         API_AVAILABLE(macos(10.7), ios(5.0), watchos(2.0), tvos(9.0)) = kCFCalendarUnitWeekOfYear,
        /// Identifier for the week-counting year unit.
        NSCalendarUnitYearForWeekOfYear  API_AVAILABLE(macos(10.7), ios(5.0), watchos(2.0), tvos(9.0)) = kCFCalendarUnitYearForWeekOfYear,
        /// Identifier for the nanosecond unit.
        NSCalendarUnitNanosecond         API_AVAILABLE(macos(10.7), ios(5.0), watchos(2.0), tvos(9.0)) = (1 << 15),
        NSCalendarUnitDayOfYear          API_AVAILABLE(macos(15.0), ios(18.0), watchos(11.0), tvos(18.0)) = kCFCalendarUnitDayOfYear,
        /// Identifier for the calendar of a date components object.
        ///
        /// The corresponding value is an `NSCalendar`.
        NSCalendarUnitCalendar           API_AVAILABLE(macos(10.7), ios(4.0), watchos(2.0), tvos(9.0)) = (1 << 20),
        /// Identifier for the time zone of a date components object.
        ///
        /// The corresponding value is an `NSTimeZone`.
        NSCalendarUnitTimeZone           API_AVAILABLE(macos(10.7), ios(4.0), watchos(2.0), tvos(9.0)) = (1 << 21),
        NSCalendarUnitIsLeapMonth API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0)) = (1 << 30),
        NSCalendarUnitIsRepeatedDay API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0)) = (1UL << 31),
    #if !0
        /// Specifies the era unit.
        /// @deprecated Use `NSCalendarUnitEra` instead.
        NSEraCalendarUnit API_DEPRECATED_WITH_REPLACEMENT("NSCalendarUnitEra", macos(10.4, 10.10), ios(2.0, 8.0), watchos(2.0, 2.0), tvos(9.0, 9.0)) = NSCalendarUnitEra,
        /// Specifies the year unit.
        /// @deprecated Use `NSCalendarUnitYear` instead.
        NSYearCalendarUnit API_DEPRECATED_WITH_REPLACEMENT("NSCalendarUnitYear", macos(10.4, 10.10), ios(2.0, 8.0), watchos(2.0, 2.0), tvos(9.0, 9.0)) = NSCalendarUnitYear,
        /// Specifies the month unit.
        /// @deprecated Use `NSCalendarUnitMonth` instead.
        NSMonthCalendarUnit API_DEPRECATED_WITH_REPLACEMENT("NSCalendarUnitMonth", macos(10.4, 10.10), ios(2.0, 8.0), watchos(2.0, 2.0), tvos(9.0, 9.0)) = NSCalendarUnitMonth,
        /// Specifies the day unit.
        /// @deprecated Use `NSCalendarUnitDay` instead.
        NSDayCalendarUnit API_DEPRECATED_WITH_REPLACEMENT("NSCalendarUnitDay", macos(10.4, 10.10), ios(2.0, 8.0), watchos(2.0, 2.0), tvos(9.0, 9.0)) = NSCalendarUnitDay,
        /// Specifies the hour unit.
        /// @deprecated Use `NSCalendarUnitHour` instead.
        NSHourCalendarUnit API_DEPRECATED_WITH_REPLACEMENT("NSCalendarUnitHour", macos(10.4, 10.10), ios(2.0, 8.0), watchos(2.0, 2.0), tvos(9.0, 9.0)) = NSCalendarUnitHour,
        /// Specifies the minute unit.
        /// @deprecated Use `NSCalendarUnitMinute` instead.
        NSMinuteCalendarUnit API_DEPRECATED_WITH_REPLACEMENT("NSCalendarUnitMinute", macos(10.4, 10.10), ios(2.0, 8.0), watchos(2.0, 2.0), tvos(9.0, 9.0)) = NSCalendarUnitMinute,
        /// Specifies the second unit.
        /// @deprecated Use `NSCalendarUnitSecond` instead.
        NSSecondCalendarUnit API_DEPRECATED_WITH_REPLACEMENT("NSCalendarUnitSecond", macos(10.4, 10.10), ios(2.0, 8.0), watchos(2.0, 2.0), tvos(9.0, 9.0)) = NSCalendarUnitSecond,
        /// Specifies the week unit.
        ///
        /// Equal to `kCFCalendarUnitWeek`.
        /// @deprecated Use `NSCalendarUnitWeekOfMonth` or `NSCalendarUnitWeekOfYear` instead.
        NSWeekCalendarUnit API_DEPRECATED("NSCalendarUnitWeekOfMonth or NSCalendarUnitWeekOfYear, depending on which you mean", macos(10.4, 10.10), ios(2.0, 8.0), watchos(2.0, 2.0), tvos(9.0, 9.0)) = kCFCalendarUnitWeek,
        /// Specifies the weekday unit.
        /// @deprecated Use `NSCalendarUnitWeekday` instead.
        NSWeekdayCalendarUnit API_DEPRECATED_WITH_REPLACEMENT("NSCalendarUnitWeekday", macos(10.4, 10.10), ios(2.0, 8.0), watchos(2.0, 2.0), tvos(9.0, 9.0)) = NSCalendarUnitWeekday,
        /// Specifies the ordinal weekday unit.
        ///
        /// The weekday ordinal unit describes the ordinal position within the month of the corresponding weekday unit. For example, in the Gregorian calendar a weekday ordinal of 2 for a weekday of 3 indicates "the second Tuesday in the month". Equal to `kCFCalendarUnitWeekdayOrdinal`.
        /// @deprecated Use `NSCalendarUnitWeekdayOrdinal` instead.
        NSWeekdayOrdinalCalendarUnit API_DEPRECATED_WITH_REPLACEMENT("NSCalendarUnitWeekdayOrdinal", macos(10.4, 10.10), ios(2.0, 8.0), watchos(2.0, 2.0), tvos(9.0, 9.0)) = NSCalendarUnitWeekdayOrdinal,
        /// Specifies the quarter unit.
        /// @deprecated Use `NSCalendarUnitQuarter` instead.
        NSQuarterCalendarUnit API_DEPRECATED_WITH_REPLACEMENT("NSCalendarUnitQuarter", macos(10.6, 10.10), ios(4.0, 8.0), watchos(2.0, 2.0), tvos(9.0, 9.0)) = NSCalendarUnitQuarter,
        /// Specifies the week of the month calendar unit.
        /// @deprecated Use `NSCalendarUnitWeekOfMonth` instead.
        NSWeekOfMonthCalendarUnit API_DEPRECATED_WITH_REPLACEMENT("NSCalendarUnitWeekOfMonth", macos(10.7, 10.10), ios(5.0, 8.0), watchos(2.0, 2.0), tvos(9.0, 9.0)) = NSCalendarUnitWeekOfMonth,
        /// Specifies the week of the year calendar unit.
        /// @deprecated Use `NSCalendarUnitWeekOfYear` instead.
        NSWeekOfYearCalendarUnit API_DEPRECATED_WITH_REPLACEMENT("NSCalendarUnitWeekOfYear", macos(10.7, 10.10), ios(5.0, 8.0), watchos(2.0, 2.0), tvos(9.0, 9.0)) = NSCalendarUnitWeekOfYear,
        /// Specifies the year when the calendar is being interpreted as a week-based calendar.
        /// @deprecated Use `NSCalendarUnitYearForWeekOfYear` instead.
        NSYearForWeekOfYearCalendarUnit API_DEPRECATED_WITH_REPLACEMENT("NSCalendarUnitYearForWeekOfYear", macos(10.7, 10.10), ios(5.0, 8.0), watchos(2.0, 2.0), tvos(9.0, 9.0)) = NSCalendarUnitYearForWeekOfYear,
        /// Specifies the calendar of the calendar.
        /// @deprecated Use `NSCalendarUnitCalendar` instead.
        NSCalendarCalendarUnit API_DEPRECATED_WITH_REPLACEMENT("NSCalendarUnitCalendar", macos(10.7, 10.10), ios(4.0, 8.0), watchos(2.0, 2.0), tvos(9.0, 9.0)) = NSCalendarUnitCalendar,
        /// Specifies the time zone of the calendar as an `NSTimeZone`.
        /// @deprecated Use `NSCalendarUnitTimeZone` instead.
        NSTimeZoneCalendarUnit API_DEPRECATED_WITH_REPLACEMENT("NSCalendarUnitTimeZone", macos(10.7, 10.10), ios(4.0, 8.0), watchos(2.0, 2.0), tvos(9.0, 9.0)) = NSCalendarUnitTimeZone,
    #endif
};
    
/// The options for arithmetic operations involving calendars.
typedef NS_OPTIONS(NSUInteger, NSCalendarOptions) {
	/// Specifies that the components specified for an `NSDateComponents` object should be incremented and wrap around to zero/one on overflow, but should not cause higher units to be incremented.
	NSCalendarWrapComponents = (1UL << 0),

	/// Specifies that the operation should travel as far forward or backward as necessary looking for a match.
	NSCalendarMatchStrictly    API_AVAILABLE(macos(10.9), ios(7.0), watchos(2.0), tvos(9.0)) = (1ULL << 1),
	/// Specifies that the operation should travel backwards to find the previous match before the given date.
	NSCalendarSearchBackwards  API_AVAILABLE(macos(10.9), ios(7.0), watchos(2.0), tvos(9.0)) = (1ULL << 2),

	/// Specifies that, when there is no matching time before the end of the next instance of the next highest unit specified in the given `NSDateComponents` object, this method uses the previous existing value of the missing unit and preserves the lower units' values.
	NSCalendarMatchPreviousTimePreservingSmallerUnits API_AVAILABLE(macos(10.9), ios(7.0), watchos(2.0), tvos(9.0)) = (1ULL << 8),
	/// Specifies that, when there is no matching time before the end of the next instance of the next highest unit specified in the given `NSDateComponents` object, this method uses the next existing value of the missing unit and preserves the lower units' values.
	NSCalendarMatchNextTimePreservingSmallerUnits     API_AVAILABLE(macos(10.9), ios(7.0), watchos(2.0), tvos(9.0)) = (1ULL << 9),
	/// Specifies that, when there is no matching time before the end of the next instance of the next highest unit specified in the given `NSDateComponents` object, this method uses the next existing value of the missing unit and does not preserve the lower units' values.
	NSCalendarMatchNextTime                           API_AVAILABLE(macos(10.9), ios(7.0), watchos(2.0), tvos(9.0)) = (1ULL << 10),

	/// Specifies that, if there are two or more matching times, the operation should return the first occurrence.
	NSCalendarMatchFirst  API_AVAILABLE(macos(10.9), ios(7.0), watchos(2.0), tvos(9.0)) = (1ULL << 12),
	/// Specifies that, if there are two or more matching times, the operation should return the last occurrence.
	NSCalendarMatchLast   API_AVAILABLE(macos(10.9), ios(7.0), watchos(2.0), tvos(9.0)) = (1ULL << 13)
};

enum {
	/// Specifies that the components specified for an `NSDateComponents` object should be incremented and wrap around to zero/one on overflow, but should not cause higher units to be incremented.
	///
	/// @deprecated Use `NSCalendarWrapComponents` instead.
	NSWrapCalendarComponents API_DEPRECATED_WITH_REPLACEMENT("NSCalendarWrapComponents", macos(10.4, 10.10), ios(2.0, 8.0), watchos(2.0, 2.0), tvos(9.0, 9.0)) = NSCalendarWrapComponents,
};

/// A definition of the relationships between calendar units and absolute points in time, providing features for calculation and comparison of dates.
///
/// In Swift, this object bridges to ``Calendar``; use ``NSCalendar`` when you need reference semantics or other Foundation-specific behavior.
///
/// ``NSCalendar`` objects encapsulate information about systems of reckoning time in which the beginning, length, and divisions of a year are defined. They provide information about the calendar and support for calendrical computations such as determining the range of a given calendrical unit and adding units to a given absolute time.
///
/// ``NSCalendar`` is _toll-free bridged_ with its Core Foundation counterpart, <doc://com.apple.documentation/documentation/corefoundation/cfcalendar>. See [Toll-Free Bridging](https://developer.apple.com/library/archive/documentation/General/Conceptual/CocoaEncyclopedia/Toll-FreeBridgin/Toll-FreeBridgin.html#//apple_ref/doc/uid/TP40010810-CH2) for more information on toll-free bridging.
///
/// > Important:
/// > The Swift overlay to the Foundation framework provides the ``Calendar`` structure, which bridges to the ``NSCalendar`` class. For more information about value types, see <doc://com.apple.documentation/documentation/swift/working-with-foundation-types>.
///
/// ### Locales and Calendars
///
/// Most locales use the most widely used civil calendar, called the _Gregorian calendar_ (``Identifier/gregorian``), but there remain exceptions to this trend. For example:
///
/// - In Saudi Arabia, some locales use primarily the Islamic Umm al-Qura calendar (``Identifier/islamicUmmAlQura``).
/// - In Ethiopia, some locales use primarily the Ethiopian calendar (``Identifier/ethiopicAmeteMihret`` or ``Identifier/ethiopicAmeteAlem``).
/// - In Iran and Afghanistan, some locales use primarily the Persian calendar (``Identifier/persian``).
/// - In Thailand, some locales use primarily the Buddhist calendar (``Identifier/buddhist``).
///
/// Other locales use another calendar alongside the Gregorian calendar. For example:
///
/// - India also uses the Indian national calendar (``Identifier/indian``).
/// - Israel also uses the Hebrew calendar (``Identifier/hebrew``).
/// - China mainland and other regions also use the Chinese calendar (``Identifier/chinese``), primarily to calculate astronomical date and Chinese traditional holidays.
/// - Japan also uses the Japanese calendar (``Identifier/japanese``), primarily to add year names.
///
/// Independent of any particular locale, certain calendars are used primarily to calculate dates for religious observances. Among these are the Buddhist (``Identifier/buddhist``), Coptic (``Identifier/coptic``), Hebrew (``Identifier/hebrew``), and Islamic (``Identifier/islamic``) calendars.
///
/// ### How NSCalendar Models the Gregorian Calendar
///
/// The Gregorian calendar was first introduced in 1582, as a replacement for the Julian Calendar. According to the Julian calendar, a leap day is added to February for any year with a number divisible by 4, which results in an annual disparity of 11 minutes, or 1 day every 128 years. The Gregorian calendar revised the rules for leap day calculation, by skipping the leap day for any year with a number divisible by 100, unless that year number is also divisible by 400, resulting in an annual disparity of only 26 seconds, or 1 day every 3323 years.
///
/// To transition from the Julian calendar to the Gregorian calendar, 10 days were dropped from the Gregorian calendar (October 5–14).
///
/// After the Gregorian calendar was introduced, many regions continued to use the Julian calendar, with Turkey being the last country or region to adopt the Gregorian calendar, in 1926. As a result of the staggered adoption, the transition period for regions at the time of adoption have different start dates and a different number of skipped days to account for the additional disparity from leap day calculations.
///
/// ``NSCalendar`` models the behavior of a _proleptic_ Gregorian calendar (_as defined by ISO 8601:2004_), which extends the Gregorian calendar backward in time from the date of its introduction. This behavior should be taken into account when working with dates created before the transition period of the affected locales.
///
/// ### Calendar Arithmetic
///
/// To do calendar arithmetic, you use ``NSDate`` objects in conjunction with a calendar. For example, to convert between a decomposed date in one calendar and another calendar, you must first convert the decomposed elements into a date using the first calendar, then decompose it using the second. ``NSDate`` provides the absolute scale and epoch (reference point) for dates and times, which can then be rendered into a particular calendar, for calendrical computations or user display.
///
/// Two ``NSCalendar`` methods that return a date object, ``date(from:)``, ``date(byAdding:to:options:)``, take as a parameter an ``NSDateComponents`` object that describes the calendrical components required for the computation. You can provide as many components as you need (or choose to). When there is incomplete information to compute an absolute time, default values similar to `0` and `1` are usually chosen by a calendar, but this is a calendar-specific choice. If you provide inconsistent information, calendar-specific disambiguation is performed (which may involve ignoring one or more of the parameters). Related methods (``components(_:from:)`` and ``components(_:from:to:options:)-84y5w``) take a bit mask parameter that specifies which components to calculate when returning an ``NSDateComponents`` object. The bit mask is composed of ``Unit`` constants (see `Constants`).
///
/// In a calendar, day, week, weekday, month, and year numbers are generally 1-based, but there may be calendar-specific exceptions. Ordinal numbers, where they occur, are 1-based. Some calendars represented by this API may have to map their basic unit concepts into year/month/week/day/… nomenclature. For example, a calendar composed of 4 quarters in a year instead of 12 months uses the month unit to represent quarters. The particular values of the unit are defined by each calendar, and are not necessarily consistent with values for that unit in another calendar.
@interface NSCalendar : NSObject <NSCopying, NSSecureCoding>

/// The user's current calendar.
///
/// The returned calendar is formed from the settings for the current user's chosen system locale overlaid with any custom settings the user has specified in System Preferences. Settings you get from this calendar do not change as System Preferences are changed.
@property (class, readonly, copy) NSCalendar *currentCalendar;

/// A calendar that tracks changes to user's preferred calendar.
///
/// Settings you get from this calendar do change as the user's settings change. Note that if you cache values based on the calendar or related information those caches will of course not be automatically updated by the updating of the calendar object.
@property (class, readonly, strong) NSCalendar *autoupdatingCurrentCalendar API_AVAILABLE(macos(10.5), ios(2.0), watchos(2.0), tvos(9.0));

/// Creates a new calendar specified by a given identifier.
///
/// - Parameters:
///   - calendarIdentifierConstant: The identifier for the new calendar. For valid identifiers, see `Calendar Identifiers`.
/// - Returns: The initialized calendar, or `nil` if the identifier is unknown (if, for example, it is either an unrecognized string or the calendar is not supported by the current version of the operating system).
///
/// The returned calendar defaults to the current locale and default time zone.
+ (nullable NSCalendar *)calendarWithIdentifier:(NSCalendarIdentifier)calendarIdentifierConstant API_AVAILABLE(macos(10.9), ios(8.0), watchos(2.0), tvos(9.0));

- (instancetype)init NS_UNAVAILABLE;

/// Initializes a calendar according to a given identifier.
///
/// - Parameters:
///   - ident: The identifier for the new calendar. For valid identifiers, see `Calendar Identifiers`.
/// - Returns: The initialized calendar, or `nil` if the identifier is unknown (if, for example, it is either an unrecognized string or the calendar is not supported by the current version of the operating system).
- (nullable id)initWithCalendarIdentifier:(NSCalendarIdentifier)ident NS_DESIGNATED_INITIALIZER;

/// An identifier for the calendar.
@property (readonly, copy) NSCalendarIdentifier calendarIdentifier;

/// The locale for the calendar.
@property (nullable, copy) NSLocale *locale;

/// The time zone for the calendar.
@property (copy) NSTimeZone *timeZone;

/// The index of the first weekday for the calendar.
@property NSUInteger firstWeekday;

/// The minimum number of days in the first week of the calendar.
@property NSUInteger minimumDaysInFirstWeek;

// Methods to return component name strings localized to the calendar's locale

/// A list of era symbols for this calendar.
@property (readonly, copy) NSArray<NSString *> *eraSymbols      API_AVAILABLE(macos(10.7), ios(5.0), watchos(2.0), tvos(9.0));
/// The long era symbols for this calendar.
@property (readonly, copy) NSArray<NSString *> *longEraSymbols  API_AVAILABLE(macos(10.7), ios(5.0), watchos(2.0), tvos(9.0));

/// The list of month symbols for this calendar.
@property (readonly, copy) NSArray<NSString *> *monthSymbols                    API_AVAILABLE(macos(10.7), ios(5.0), watchos(2.0), tvos(9.0));
/// The list of short month symbols for this calendar.
@property (readonly, copy) NSArray<NSString *> *shortMonthSymbols               API_AVAILABLE(macos(10.7), ios(5.0), watchos(2.0), tvos(9.0));
/// The list of very short month symbols for this calendar.
@property (readonly, copy) NSArray<NSString *> *veryShortMonthSymbols           API_AVAILABLE(macos(10.7), ios(5.0), watchos(2.0), tvos(9.0));
/// The list of standalone month symbols for this calendar.
@property (readonly, copy) NSArray<NSString *> *standaloneMonthSymbols          API_AVAILABLE(macos(10.7), ios(5.0), watchos(2.0), tvos(9.0));
/// The list of short standalone month symbols for this calendar.
@property (readonly, copy) NSArray<NSString *> *shortStandaloneMonthSymbols     API_AVAILABLE(macos(10.7), ios(5.0), watchos(2.0), tvos(9.0));
/// The list of very short standalone month symbols for this calendar.
@property (readonly, copy) NSArray<NSString *> *veryShortStandaloneMonthSymbols API_AVAILABLE(macos(10.7), ios(5.0), watchos(2.0), tvos(9.0));

/// The list of weekday symbols for this calendar.
@property (readonly, copy) NSArray<NSString *> *weekdaySymbols                    API_AVAILABLE(macos(10.7), ios(5.0), watchos(2.0), tvos(9.0));
/// The list of short weekday symbols for this calendar.
@property (readonly, copy) NSArray<NSString *> *shortWeekdaySymbols               API_AVAILABLE(macos(10.7), ios(5.0), watchos(2.0), tvos(9.0));
/// The list of very short weekday symbols for this calendar.
@property (readonly, copy) NSArray<NSString *> *veryShortWeekdaySymbols           API_AVAILABLE(macos(10.7), ios(5.0), watchos(2.0), tvos(9.0));
/// The list of standalone weekday symbols for this calendar.
@property (readonly, copy) NSArray<NSString *> *standaloneWeekdaySymbols          API_AVAILABLE(macos(10.7), ios(5.0), watchos(2.0), tvos(9.0));
/// The list of short standalone weekday symbols for this calendar.
@property (readonly, copy) NSArray<NSString *> *shortStandaloneWeekdaySymbols     API_AVAILABLE(macos(10.7), ios(5.0), watchos(2.0), tvos(9.0));
/// The list of very short standalone weekday symbols for this calendar.
@property (readonly, copy) NSArray<NSString *> *veryShortStandaloneWeekdaySymbols API_AVAILABLE(macos(10.7), ios(5.0), watchos(2.0), tvos(9.0));

/// The list of quarter symbols for this calendar.
@property (readonly, copy) NSArray<NSString *> *quarterSymbols                 API_AVAILABLE(macos(10.7), ios(5.0), watchos(2.0), tvos(9.0));
/// The list of short quarter symbols for this calendar.
@property (readonly, copy) NSArray<NSString *> *shortQuarterSymbols            API_AVAILABLE(macos(10.7), ios(5.0), watchos(2.0), tvos(9.0));
/// The list of standalone quarter symbols for this calendar.
@property (readonly, copy) NSArray<NSString *> *standaloneQuarterSymbols       API_AVAILABLE(macos(10.7), ios(5.0), watchos(2.0), tvos(9.0));
/// The list of short standalone quarter symbols for this calendar.
@property (readonly, copy) NSArray<NSString *> *shortStandaloneQuarterSymbols  API_AVAILABLE(macos(10.7), ios(5.0), watchos(2.0), tvos(9.0));

/// The AM symbol for this calendar.
@property (readonly, copy) NSString *AMSymbol  API_AVAILABLE(macos(10.7), ios(5.0), watchos(2.0), tvos(9.0));
/// The PM symbol for this calendar.
@property (readonly, copy) NSString *PMSymbol  API_AVAILABLE(macos(10.7), ios(5.0), watchos(2.0), tvos(9.0));


// Calendrical calculations

/// The minimum range limits of the values that a given unit can take on.
- (NSRange)minimumRangeOfUnit:(NSCalendarUnit)unit;

/// The maximum range limits of the values that a given unit can take on.
- (NSRange)maximumRangeOfUnit:(NSCalendarUnit)unit;

/// The range of absolute time values that a smaller calendar unit can take on in a larger calendar unit for a specified absolute time.
- (NSRange)rangeOfUnit:(NSCalendarUnit)smaller inUnit:(NSCalendarUnit)larger forDate:(NSDate *)date;

/// The ordinal number of a smaller calendar unit within a specified larger calendar unit for a specified absolute time.
- (NSUInteger)ordinalityOfUnit:(NSCalendarUnit)smaller inUnit:(NSCalendarUnit)larger forDate:(NSDate *)date;

/// The starting time and duration of a given calendar unit that contains a given date.
- (BOOL)rangeOfUnit:(NSCalendarUnit)unit startDate:(NSDate * _Nullable * _Nullable)datep interval:(nullable NSTimeInterval *)tip forDate:(NSDate *)date API_AVAILABLE(macos(10.5), ios(2.0), watchos(2.0), tvos(9.0));

/// A date created from the specified components.
- (nullable NSDate *)dateFromComponents:(NSDateComponents *)comps;

/// The date components representing a given date.
- (NSDateComponents *)components:(NSCalendarUnit)unitFlags fromDate:(NSDate *)date;

/// A date representing the absolute time calculated by adding given components to a given date.
- (nullable NSDate *)dateByAddingComponents:(NSDateComponents *)comps toDate:(NSDate *)date options:(NSCalendarOptions)opts;

/// Returns the difference between two supplied dates as date components.
///
/// The result is lossy if there is not a small enough unit requested to hold the full precision of the difference. Some operations can be ambiguous, and the behavior of the computation is calendar-specific, but generally larger components will be computed before smaller components; for example, in the Gregorian calendar a result might be 1 month and 5 days instead of, for example, 0 months and 35 days. The resulting component values may be negative if `resultDate` is before `startDate`.
///
/// Note that some computations can take a relatively long time.
///
/// - Parameters:
///   - unitFlags: Specifies the components for the returned `NSDateComponents` object.
///   - startingDate: The start date for the calculation.
///   - resultDate: The end date for the calculation.
///   - opts: Options for the calculation. If you specify ``NSCalendar/Options/wrapComponents``, the specified components are incremented and wrap around to zero/one on overflow, but do not cause higher units to be incremented.
/// - Returns: An `NSDateComponents` object whose components are specified by `unitFlags` and calculated from the difference between the `resultDate` and `startDate`. Returns `nil` if either date falls outside the defined range of the receiver or if the computation cannot be performed.
- (NSDateComponents *)components:(NSCalendarUnit)unitFlags fromDate:(NSDate *)startingDate toDate:(NSDate *)resultDate options:(NSCalendarOptions)opts;


/// Returns the era, year, month, and day of a given date.
///
/// Pass `NULL` for a `NSInteger` pointer parameter if you don't care about that value.
- (void)getEra:(out nullable NSInteger *)eraValuePointer year:(out nullable NSInteger *)yearValuePointer month:(out nullable NSInteger *)monthValuePointer day:(out nullable NSInteger *)dayValuePointer fromDate:(NSDate *)date API_AVAILABLE(macos(10.9), ios(8.0), watchos(2.0), tvos(9.0));


/// Returns the era, year for week-of-year calculations, week of year, and weekday of a given date.
///
/// Pass `NULL` for a `NSInteger` pointer parameter if you don't care about that value.
- (void)getEra:(out nullable NSInteger *)eraValuePointer yearForWeekOfYear:(out nullable NSInteger *)yearValuePointer weekOfYear:(out nullable NSInteger *)weekValuePointer weekday:(out nullable NSInteger *)weekdayValuePointer fromDate:(NSDate *)date API_AVAILABLE(macos(10.9), ios(8.0), watchos(2.0), tvos(9.0));


/// Returns the hour, minute, second, and nanoseconds of a given date.
///
/// Pass `NULL` for a `NSInteger` pointer parameter if you don't care about that value.
- (void)getHour:(out nullable NSInteger *)hourValuePointer minute:(out nullable NSInteger *)minuteValuePointer second:(out nullable NSInteger *)secondValuePointer nanosecond:(out nullable NSInteger *)nanosecondValuePointer fromDate:(NSDate *)date API_AVAILABLE(macos(10.9), ios(8.0), watchos(2.0), tvos(9.0));


/// Returns the value for one component of a date.
/*
	Get just one component's value.
*/
- (NSInteger)component:(NSCalendarUnit)unit fromDate:(NSDate *)date API_AVAILABLE(macos(10.9), ios(8.0), watchos(2.0), tvos(9.0));


/// Creates a date with given components. Current era is assumed.
/*
	Create a date with given components.
	Current era is assumed.
*/
- (nullable NSDate *)dateWithEra:(NSInteger)eraValue year:(NSInteger)yearValue month:(NSInteger)monthValue day:(NSInteger)dayValue hour:(NSInteger)hourValue minute:(NSInteger)minuteValue second:(NSInteger)secondValue nanosecond:(NSInteger)nanosecondValue API_AVAILABLE(macos(10.9), ios(8.0), watchos(2.0), tvos(9.0));


/// Creates a date with given week-of-year-based components. Current era is assumed.
/*
	Create a date with given components.
	Current era is assumed.
*/
- (nullable NSDate *)dateWithEra:(NSInteger)eraValue yearForWeekOfYear:(NSInteger)yearValue weekOfYear:(NSInteger)weekValue weekday:(NSInteger)weekdayValue hour:(NSInteger)hourValue minute:(NSInteger)minuteValue second:(NSInteger)secondValue nanosecond:(NSInteger)nanosecondValue API_AVAILABLE(macos(10.9), ios(8.0), watchos(2.0), tvos(9.0));


/// Returns the first moment date of a given date.
///
/// Pass in `[NSDate date]`, for example, if you want the start of "today".
/// If there were two midnights, it returns the first. If there was none, it returns the first moment that did exist.
/*
	This API returns the first moment date of a given date.
	Pass in [NSDate date], for example, if you want the start of "today".
	If there were two midnights, it returns the first.  If there was none, it returns the first moment that did exist.
*/
- (NSDate *)startOfDayForDate:(NSDate *)date API_AVAILABLE(macos(10.9), ios(8.0), watchos(2.0), tvos(9.0));


/// Returns all the date components of a date, as if in a given time zone (instead of the receiving calendar's time zone).
///
/// The time zone overrides the time zone of the `NSCalendar` for the purposes of this calculation.
/*
	This API returns all the date components of a date, as if in a given time zone (instead of the receiving calendar's time zone).
	The time zone overrides the time zone of the NSCalendar for the purposes of this calculation.
	Note: if you want "date information in a given time zone" in order to display it, you should use NSDateFormatter to format the date.
*/
- (NSDateComponents *)componentsInTimeZone:(NSTimeZone *)timezone fromDate:(NSDate *)date API_AVAILABLE(macos(10.9), ios(8.0), watchos(2.0), tvos(9.0));


/// Compares the given dates down to the given unit, reporting them equal if they are the same in the given unit and all larger units, otherwise either less than or greater than.
/*
	This API compares the given dates down to the given unit, reporting them equal if they are the same in the given unit and all larger units, otherwise either less than or greater than.
*/
- (NSComparisonResult)compareDate:(NSDate *)date1 toDate:(NSDate *)date2 toUnitGranularity:(NSCalendarUnit)unit API_AVAILABLE(macos(10.9), ios(8.0), watchos(2.0), tvos(9.0));


/// Returns whether the given dates are equal down to the given unit, reporting them equal if they are the same in the given unit and all larger units.
/*
	This API compares the given dates down to the given unit, reporting them equal if they are the same in the given unit and all larger units.
*/
- (BOOL)isDate:(NSDate *)date1 equalToDate:(NSDate *)date2 toUnitGranularity:(NSCalendarUnit)unit API_AVAILABLE(macos(10.9), ios(8.0), watchos(2.0), tvos(9.0));


/// Returns whether the given dates are in the same day.
/*
	This API compares the Days of the given dates, reporting them equal if they are in the same Day.
*/
- (BOOL)isDate:(NSDate *)date1 inSameDayAsDate:(NSDate *)date2 API_AVAILABLE(macos(10.9), ios(8.0), watchos(2.0), tvos(9.0));


/// Returns whether the given date is within "today".
/*
	This API reports if the date is within "today".
*/
- (BOOL)isDateInToday:(NSDate *)date API_AVAILABLE(macos(10.9), ios(8.0), watchos(2.0), tvos(9.0));


/// Returns whether the given date is within "yesterday".
/*
	This API reports if the date is within "yesterday".
*/
- (BOOL)isDateInYesterday:(NSDate *)date API_AVAILABLE(macos(10.9), ios(8.0), watchos(2.0), tvos(9.0));


/// Returns whether the given date is within "tomorrow".
/*
	This API reports if the date is within "tomorrow".
*/
- (BOOL)isDateInTomorrow:(NSDate *)date API_AVAILABLE(macos(10.9), ios(8.0), watchos(2.0), tvos(9.0));


/// Returns whether the given date is within a weekend period, as defined by the calendar and calendar's locale.
/*
	This API reports if the date is within a weekend period, as defined by the calendar and calendar's locale.
*/
- (BOOL)isDateInWeekend:(NSDate *)date API_AVAILABLE(macos(10.9), ios(8.0), watchos(2.0), tvos(9.0));


/// Returns whether a given date falls within a weekend period, and if so, returns by reference the start date and time interval of the weekend range.
///
/// Note that a particular calendar day may not necessarily fall entirely within a weekend period, as weekends can start in the middle of a day in some calendars and locales.
///
/// - Parameters:
///   - datep: Upon return, contains the starting date of the weekend period.
///   - tip: Upon return, contains the time interval of the weekend period.
///   - date: The date to use to perform the calculation.
/// - Returns: `YES` if the given date falls within a weekend period, otherwise `NO`.
- (BOOL)rangeOfWeekendStartDate:(out NSDate * _Nullable * _Nullable)datep interval:(out nullable NSTimeInterval *)tip containingDate:(NSDate *)date API_AVAILABLE(macos(10.9), ios(8.0), watchos(2.0), tvos(9.0));


/// Returns by reference the starting date and time interval range of the next weekend period after a given date.
///
/// Note that a particular calendar day may not necessarily fall entirely within a weekend period, as weekends can start in the middle of a day in some calendars and locales.
///
/// The `NSCalendarSearchBackwards` option can be used to find the previous weekend range strictly before the date. Returns `NO` if there are no such things as weekends in the calendar and its locale.
///
/// - Parameters:
///   - datep: Upon return, contains the starting date of the next weekend period.
///   - tip: Upon return, contains the time interval of the next weekend period.
///   - options: Options for the calculation. If you specify ``NSCalendar/Options/searchBackwards``, the starting date and time interval range of the preceding weekend period will be returned by reference instead.
///   - date: The date for which to perform the calculation.
/// - Returns: `NO` if the calendar and locale do not have the concept of a weekend, otherwise `YES`.
- (BOOL)nextWeekendStartDate:(out NSDate * _Nullable * _Nullable)datep interval:(out nullable NSTimeInterval *)tip options:(NSCalendarOptions)options afterDate:(NSDate *)date API_AVAILABLE(macos(10.9), ios(8.0), watchos(2.0), tvos(9.0));


/// Returns the difference between start and end dates given as date components.
///
/// If an `NSDateComponents` object does not specify a value for a calendar unit required to determine an absolute date, the base value of that unit is assumed. For example, given an `NSDateComponents` object with only a `year` and a `month` specified, the resulting `NSDate` object would be constructed using a `day` value of `1` and `hour`, `minute`, `second` and `nanosecond` values of `0`. Passing an `NSDateComponents` argument with an unspecified `era` or `year` value is not advised.
///
/// If an `NSDateComponents` object's `timeZone` property is set, the time zone property value will be used in the calculation. If an `NSDateComponents` object's `calendar` property is set, the calendar property value will be used instead of the receiving calendar. If both an `NSDateComponents` object's `timeZone` and `calendar` properties are set, the time zone property value overrides the time zone of the calendar property value.
///
/// - Parameters:
///   - unitFlags: Specifies the components for the returned `NSDateComponents` object.
///   - startingDateComp: The start date for the calculation as an `NSDateComponents` object.
///   - resultDateComp: The end date for the calculation as an `NSDateComponents` object.
///   - options: The options parameter is currently unused.
/// - Returns: An `NSDateComponents` object whose components are specified by `unitFlags` and calculated from the difference between the `startingDateComp` and `resultDateComp`. Returns `nil` if either date falls outside the defined range of the receiver or if the computation cannot be performed.
- (NSDateComponents *)components:(NSCalendarUnit)unitFlags fromDateComponents:(NSDateComponents *)startingDateComp toDateComponents:(NSDateComponents *)resultDateComp options:(NSCalendarOptions)options API_AVAILABLE(macos(10.9), ios(8.0), watchos(2.0), tvos(9.0));


/// Returns a new date representing the date calculated by adding an amount of a specific component to a given date.
/*
	This API returns a new NSDate object representing the date calculated by adding an amount of a specific component to a given date.
	The NSCalendarWrapComponents option specifies if the component should be incremented and wrap around to zero/one on overflow, and should not cause higher units to be incremented.
*/
- (nullable NSDate *)dateByAddingUnit:(NSCalendarUnit)unit value:(NSInteger)value toDate:(NSDate *)date options:(NSCalendarOptions)options API_AVAILABLE(macos(10.9), ios(8.0), watchos(2.0), tvos(9.0));

/*
	This method computes the dates which match (or most closely match) a given set of components, and calls the block once for each of them, until the enumeration is stopped.
	There will be at least one intervening date which does not match all the components (or the given date itself must not match) between the given date and any result.
	If the NSCalendarSearchBackwards option is used, this method finds the previous match before the given date.  The intent is that the same matches as for a forwards search will be found (that is, if you are enumerating forwards or backwards for each hour with minute "27", the seconds in the date you will get in forwards search would obviously be 00, and the same will be true in a backwards search in order to implement this rule.  Similarly for DST backwards jumps which repeats times, you'll get the first match by default, where "first" is defined from the point of view of searching forwards.  So, when searching backwards looking for a particular hour, with no minute and second specified, you don't get a minute and second of 59:59 for the matching hour (which would be the nominal first match within a given hour, given the other rules here, when searching backwards).
	If the NSCalendarMatchStrictly option is used, the algorithm travels as far forward or backward as necessary looking for a match, but there are ultimately implementation-defined limits in how far distant the search will go.  If the NSCalendarMatchStrictly option is not specified, the algorithm searches up to the end of the next instance of the next higher unit to the highest specified unit in the NSDateComponents argument.  If you want to find the next Feb 29 in the Gregorian calendar, for example, you have to specify the NSCalendarMatchStrictly option to guarantee finding it.
	If an exact match is not possible, and requested with the NSCalendarMatchStrictly option, nil is passed to the block and the enumeration ends.  (Logically, since an exact match searches indefinitely into the future, if no match is found there's no point in continuing the enumeration.)

	If the NSCalendarMatchStrictly option is NOT used, exactly one option from the set {NSCalendarMatchPreviousTimePreservingSmallerUnits, NSCalendarMatchNextTimePreservingSmallerUnits, NSCalendarMatchNextTime} must be specified, or an illegal argument exception will be thrown.
	
        If the NSCalendarMatchPreviousTimePreservingSmallerUnits option is specified, and there is no matching time before the end of the next instance of the next higher unit to the highest specified unit in the NSDateComponents argument, the method will return the previous existing value of the missing unit and preserves the lower units' values (e.g., no 2:37am results in 1:37am, if that exists).
	
        If the NSCalendarMatchNextTimePreservingSmallerUnits option is specified, and there is no matching time before the end of the next instance of the next higher unit to the highest specified unit in the NSDateComponents argument, the method will return the next existing value of the missing unit and preserves the lower units' values (e.g., no 2:37am results in 3:37am, if that exists).
 
	If the NSCalendarMatchNextTime option is specified, and there is no matching time before the end of the next instance of the next higher unit to the highest specified unit in the NSDateComponents argument, the method will return the next existing time which exists (e.g., no 2:37am results in 3:00am, if that exists).
	If the NSCalendarMatchFirst option is specified, and there are two or more matching times (all the components are the same, including isLeapMonth) before the end of the next instance of the next higher unit to the highest specified unit in the NSDateComponents argument, the method will return the first occurrence.
	If the NSCalendarMatchLast option is specified, and there are two or more matching times (all the components are the same, including isLeapMonth) before the end of the next instance of the next higher unit to the highest specified unit in the NSDateComponents argument, the method will return the last occurrence.
	If neither the NSCalendarMatchFirst or NSCalendarMatchLast option is specified, the default behavior is to act as if NSCalendarMatchFirst was specified.
	There is no option to return middle occurrences of more than two occurrences of a matching time, if such exist.

	Result dates have an integer number of seconds (as if 0 was specified for the nanoseconds property of the NSDateComponents matching parameter), unless a value was set in the nanoseconds property, in which case the result date will have that number of nanoseconds (or as close as possible with floating point numbers).
	The enumeration is stopped by setting *stop = YES in the block and return.  It is not necessary to set *stop to NO to keep the enumeration going.
*/
/// Computes the dates that match (or most closely match) a given set of components, and calls the block once for each of them, until the enumeration is stopped.
///
/// If you specify a strict matching option (``NSCalendar/Options/matchStrictly``), this method searches as far as necessary looking for a match, up to an implementation-defined limit. If an exact match is not possible, `nil` is passed to the `date` argument of the block, and the enumeration is stopped. Otherwise, this method searches as far as the next instance of the next highest calendar unit in the given `NSDateComponents` object.
///
/// If you do not specify a strict matching option, you must specify one of ``NSCalendar/Options/matchPreviousTimePreservingSmallerUnits``, ``NSCalendar/Options/matchNextTimePreservingSmallerUnits``, or ``NSCalendar/Options/matchNextTime``, or an illegal argument exception will be thrown.
///
/// - Parameters:
///   - start: The date for which to perform the calculation.
///   - comps: The date components to match. If no components are specified, the enumeration will not be executed.
///   - opts: Options for the enumeration. For possible values, see ``NSCalendar/Options``.
///   - block: The block to apply to each enumerated date. The block takes three arguments: the enumerated date, whether the date exactly matches the specified date components, and a reference to a Boolean value that the block can set to `YES` to stop the enumeration.
- (void)enumerateDatesStartingAfterDate:(NSDate *)start matchingComponents:(NSDateComponents *)comps options:(NSCalendarOptions)opts usingBlock:(void (NS_NOESCAPE ^)(NSDate * _Nullable date, BOOL exactMatch, BOOL *stop))block API_AVAILABLE(macos(10.9), ios(8.0), watchos(2.0), tvos(9.0));

/// Computes the next date which matches (or most closely matches) a given set of components.
/*
	This method computes the next date which matches (or most closely matches) a given set of components.
	The general semantics follow those of the -enumerateDatesStartingAfterDate:... method above.
	To compute a sequence of results, use the -enumerateDatesStartingAfterDate:... method above, rather than looping and calling this method with the previous loop iteration's result.
*/
- (nullable NSDate *)nextDateAfterDate:(NSDate *)date matchingComponents:(NSDateComponents *)comps options:(NSCalendarOptions)options API_AVAILABLE(macos(10.9), ios(8.0), watchos(2.0), tvos(9.0));


/// Returns a new date representing the date found which matches a specific component value.
/*
	This API returns a new NSDate object representing the date found which matches a specific component value.
	The general semantics follow those of the -enumerateDatesStartingAfterDate:... method above.
	To compute a sequence of results, use the -enumerateDatesStartingAfterDate:... method above, rather than looping and calling this method with the previous loop iteration's result.
*/
- (nullable NSDate *)nextDateAfterDate:(NSDate *)date matchingUnit:(NSCalendarUnit)unit value:(NSInteger)value options:(NSCalendarOptions)options API_AVAILABLE(macos(10.9), ios(8.0), watchos(2.0), tvos(9.0));


/// Returns a new date representing the date found which matches the given hour, minute, and second values.
/*
	This API returns a new NSDate object representing the date found which matches the given hour, minute, and second values.
	The general semantics follow those of the -enumerateDatesStartingAfterDate:... method above.
	To compute a sequence of results, use the -enumerateDatesStartingAfterDate:... method above, rather than looping and calling this method with the previous loop iteration's result.
*/
- (nullable NSDate *)nextDateAfterDate:(NSDate *)date matchingHour:(NSInteger)hourValue minute:(NSInteger)minuteValue second:(NSInteger)secondValue options:(NSCalendarOptions)options API_AVAILABLE(macos(10.9), ios(8.0), watchos(2.0), tvos(9.0));

/*
	This API returns a new NSDate object representing the date calculated by setting a specific component to a given time, and trying to keep lower components the same.  If the unit already has that value, this may result in a date which is the same as the given date.
	Changing a component's value often will require higher or coupled components to change as well.  For example, setting the Weekday to Thursday usually will require the Day component to change its value, and possibly the Month and Year as well.
	If no such time exists, the next available time is returned (which could, for example, be in a different day, week, month, ... than the nominal target date).  Setting a component to something which would be inconsistent forces other units to change; for example, setting the Weekday to Thursday probably shifts the Day and possibly Month and Year.
	The specific behaviors here are as yet unspecified; for example, if I change the weekday to Thursday, does that move forward to the next, backward to the previous, or to the nearest Thursday?  A likely rule is that the algorithm will try to produce a result which is in the next-larger unit to the one given (there's a table of this mapping at the top of this document).  So for the "set to Thursday" example, find the Thursday in the Week in which the given date resides (which could be a forwards or backwards move, and not necessarily the nearest Thursday).  For forwards or backwards behavior, one can use the -nextDateAfterDate:matchingUnit:value:options: method above.
 */
/// Returns a new date representing the date calculated by setting a specific component of a given date to a given value, while trying to keep lower components the same.
///
/// Changing a component's value often requires higher or coupled components to change as well. For example, setting the `weekday` to "Thursday" will require the `day` component to change its value, and possibly the `month` and `year` as well. If no such time exists, the next available date is returned, which may be on a different calendar day.
///
/// - Parameters:
///   - unit: The unit to set with the given value. For possible values, see ``NSCalendar/Unit``.
///   - v: The value to set for the given calendar unit.
///   - date: The date to use to perform the calculation.
///   - opts: Options for the calculation. For possible values, see ``NSCalendar/Options``.
/// - Returns: A new `NSDate` instance representing the date calculated by setting a specific component of a given date to a given value. If the unit already has that value, this may result in a date which is the same as the given date.
- (nullable NSDate *)dateBySettingUnit:(NSCalendarUnit)unit value:(NSInteger)v ofDate:(NSDate *)date options:(NSCalendarOptions)opts API_AVAILABLE(macos(10.9), ios(8.0), watchos(2.0), tvos(9.0));


/// Returns a new date representing the date calculated by setting hour, minute, and second to a given time.
///
/// If no such time exists, the next available time is returned (which could be in a different day than the nominal target date). The intent is to return a date on the same day as the original date argument.
/*
	This API returns a new NSDate object representing the date calculated by setting hour, minute, and second to a given time.
	If no such time exists, the next available time is returned (which could, for example, be in a different day than the nominal target date).
	The intent is to return a date on the same day as the original date argument.  This may result in a date which is earlier than the given date, of course.
 */
- (nullable NSDate *)dateBySettingHour:(NSInteger)h minute:(NSInteger)m second:(NSInteger)s ofDate:(NSDate *)date options:(NSCalendarOptions)opts API_AVAILABLE(macos(10.9), ios(8.0), watchos(2.0), tvos(9.0));


/// Returns `YES` if the date has all the matched components. Otherwise, it returns `NO`.
/*
    This API returns YES if the date has all the matched components. Otherwise, it returns NO.
    It is useful to test the return value of the -nextDateAfterDate:matchingUnit:value:options:, to find out if the components were obeyed or if the method had to fudge the result value due to missing time.
 */
- (BOOL)date:(NSDate *)date matchesComponents:(NSDateComponents *)components API_AVAILABLE(macos(10.9), ios(8.0), watchos(2.0), tvos(9.0));

@end


// This notification is posted through [NSNotificationCenter defaultCenter]
// when the system day changes. Register with "nil" as the object of this
// notification. If the computer/device is asleep when the day changed,
// this will be posted on wakeup. You'll get just one of these if the
// machine has been asleep for several days. The definition of "Day" is
// relative to the current calendar (NSCalendar.currentCalendar) of the
// process and its locale and time zone. There are no guarantees that this
// notification is received by observers in a "timely" manner, same as
// with distributed notifications.

/// A notification posted whenever the calendar day of the system changes, as determined by the system calendar, locale, and time zone.
///
/// If the device is asleep when the day changes, this notification will be posted on wakeup. Only one notification will be posted on wakeup if the device has been asleep for multiple days. There are no guarantees about the timeliness of when this notification will be received by observers.
FOUNDATION_EXPORT NSNotificationName const NSCalendarDayChangedNotification API_AVAILABLE(macos(10.9), ios(8.0), watchos(2.0), tvos(9.0));



// This is a just used as an extensible struct, basically;
// note that there are two uses: one for specifying a date
// via components (some components may be missing, making the
// specific date ambiguous), and the other for specifying a
// set of component quantities (like, 3 months and 5 hours).
// Undefined fields have (or fields can be set to) the value
// NSDateComponentUndefined.

// NSDateComponents is not responsible for answering questions
// about a date beyond the information it has been initialized
// with; for example, if you initialize one with May 6, 2004,
// and then ask for the weekday, you'll get Undefined, not Thurs.
// A NSDateComponents is meaningless in itself, because you need
// to know what calendar it is interpreted against, and you need
// to know whether the values are absolute values of the units,
// or quantities of the units.
// When you create a new one of these, all values begin Undefined.

/// Constants that denote that the value of a date component is undefined.
NS_ENUM(NSInteger) {
	/// Specifies a date component without a value.
	NSDateComponentUndefined = NSIntegerMax,

	/// Specifies a date component without a value.
	///
	/// @deprecated Use `NSDateComponentUndefined` instead.
	NSUndefinedDateComponent API_DEPRECATED_WITH_REPLACEMENT("NSDateComponentUndefined", macos(10.4, 10.10), ios(2.0, 8.0), watchos(2.0, 2.0), tvos(9.0, 9.0)) = NSDateComponentUndefined
};


/// An object that specifies a date or time in terms of units (such as year, month, day, hour, and minute) to be evaluated in a calendar system and time zone.
///
/// In Swift, this object bridges to ``DateComponents``; use ``NSDateComponents`` when you need reference semantics or other Foundation-specific behavior.
///
/// ``NSDateComponents`` encapsulates the components of a date in an extendable, object-oriented manner. It's used to specify a date by providing the temporal components that make up a date and time: hour, minutes, seconds, day, month, year, and so on. You can also use it to specify a duration of time, for example, 5 hours and 16 minutes. An ``NSDateComponents`` object is not required to define all the component fields. When a new instance of ``NSDateComponents`` is created, the date components are set to ``NSDateComponentUndefined``.
///
/// > Important:
/// > An ``NSDateComponents`` object is meaningless in itself; you need to know what calendar it is interpreted against, and you need to know whether the values are absolute values of the units, or quantities of the units.
///
/// An instance of ``NSDateComponents`` is not responsible for answering questions about a date beyond the information with which it was initialized. For example, if you initialize one with May 4, 2017, its weekday is ``NSDateComponentUndefined``, not Thursday. To get the correct day of the week, you must create a suitable instance of ``NSCalendar``, create an ``NSDate`` object using ``NSCalendar/date(from:)`` and then use ``NSCalendar/components(_:from:)`` to retrieve the weekday—as illustrated in the following example.
///
/// @TabNavigator {
/// @Tab("Swift") {
/// ```swift
/// let dateComponents = NSDateComponents()
/// dateComponents.day = 4
/// dateComponents.month = 5
/// dateComponents.year = 2017
///
/// if let gregorianCalendar = NSCalendar(calendarIdentifier: .gregorian),
/// let date = gregorianCalendar.date(from: dateComponents as DateComponents) {
/// let weekday = gregorianCalendar.component(.weekday, from: date)
/// print(weekday) // 5, which corresponds to Thursday in the Gregorian Calendar
/// }
///
/// ```
/// }
/// @Tab("Objective-C") {
/// ```objc
/// NSDateComponents *dateComponents = [[NSDateComponents alloc] init];
/// dateComponents.day = 4;
/// dateComponents.month = 5;
/// dateComponents.year = 2017;
///
/// NSCalendar *gregorianCalendar = [[NSCalendar alloc] initWithCalendarIdentifier:NSCalendarIdentifierGregorian];
/// NSDate *date = [gregorianCalendar dateFromComponents:dateComponents];
///
/// NSInteger weekday = [gregorianCalendar component:NSCalendarUnitWeekday fromDate:date];
/// NSLog(@"%d", weekday); // 5, which corresponds to Thursday in the Gregorian Calendar
/// ```
/// }
/// }
///
///
/// For more details, see [Calendars, Date Components, and Calendar Units](https://developer.apple.com/library/archive/documentation/Cocoa/Conceptual/DatesAndTimes/Articles/dtCalendars.html#//apple_ref/doc/uid/TP40003470) in [Date and Time Programming Guide](https://developer.apple.com/library/archive/documentation/Cocoa/Conceptual/DatesAndTimes/DatesAndTimes.html#//apple_ref/doc/uid/10000039i).
///
/// > Important:
/// > The Swift overlay to the Foundation framework provides the ``DateComponents`` structure, which bridges to the ``NSDateComponents`` class. For more information about value types, see <doc://com.apple.documentation/documentation/swift/working-with-foundation-types>.
@interface NSDateComponents : NSObject <NSCopying, NSSecureCoding>

/// The calendar used to interpret the date components.
@property (nullable, copy) NSCalendar *calendar API_AVAILABLE(macos(10.7), ios(4.0), watchos(2.0), tvos(9.0));
/// The time zone used to interpret the date components.
@property (nullable, copy) NSTimeZone *timeZone API_AVAILABLE(macos(10.7), ios(4.0), watchos(2.0), tvos(9.0));
/// The number of eras.
@property NSInteger era;
/// The number of years.
@property NSInteger year;
/// The number of months.
@property NSInteger month;
/// The number of days.
@property NSInteger day;
/// The number of hour units for the receiver.
@property NSInteger hour;
/// The number of minute units for the receiver.
@property NSInteger minute;
/// The number of second units for the receiver.
@property NSInteger second;
/// The number of nanosecond units for the receiver.
@property NSInteger nanosecond API_AVAILABLE(macos(10.7), ios(5.0), watchos(2.0), tvos(9.0));
/// The number of the weekdays.
@property NSInteger weekday;
/// The ordinal number of weekdays.
@property NSInteger weekdayOrdinal;
/// The number of quarters.
@property NSInteger quarter API_AVAILABLE(macos(10.6), ios(4.0), watchos(2.0), tvos(9.0));
/// The week number of the months.
@property NSInteger weekOfMonth API_AVAILABLE(macos(10.7), ios(5.0), watchos(2.0), tvos(9.0));
/// The ISO 8601 week date of the year.
@property NSInteger weekOfYear API_AVAILABLE(macos(10.7), ios(5.0), watchos(2.0), tvos(9.0));
/// The ISO 8601 week-numbering year.
@property NSInteger yearForWeekOfYear API_AVAILABLE(macos(10.7), ios(5.0), watchos(2.0), tvos(9.0));
/// The day of the year value of the date components.
@property NSInteger dayOfYear API_AVAILABLE(macos(15.0), ios(18.0), watchos(11.0), tvos(18.0));
/// A Boolean value that indicates whether the month is a leap month.
@property (getter=isLeapMonth) BOOL leapMonth API_AVAILABLE(macos(10.8), ios(6.0), watchos(2.0), tvos(9.0));
@property (getter=isRepeatedDay) BOOL repeatedDay API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));
/// The date calculated from the current components using the stored calendar.
@property (nullable, readonly, copy) NSDate *date API_AVAILABLE(macos(10.7), ios(4.0), watchos(2.0), tvos(9.0));

- (NSInteger)week API_DEPRECATED("Use -weekOfMonth or -weekOfYear, depending on which you mean", macos(10.4, 10.9), ios(2.0, 7.0), watchos(2.0, 2.0), tvos(9.0, 9.0));
- (void)setWeek:(NSInteger)v API_DEPRECATED("Use -setWeekOfMonth: or -setWeekOfYear:, depending on which you mean", macos(10.4, 10.9), ios(2.0, 7.0), watchos(2.0, 2.0), tvos(9.0, 9.0));

/// Sets a value for a given calendar unit.
///
/// The calendar and timeZone and isLeapMonth properties cannot be set by this method.
/*
	This API allows one to set a specific component of NSDateComponents, by enum constant value rather than property name.
	The calendar and timeZone and isLeapMonth properties cannot be set by this method.
*/
- (void)setValue:(NSInteger)value forComponent:(NSCalendarUnit)unit API_AVAILABLE(macos(10.9), ios(8.0), watchos(2.0), tvos(9.0));


/// Returns the value for a given calendar unit.
///
/// The calendar and timeZone and isLeapMonth property values cannot be retrieved by this method.
/*
	This API allows one to get the value of a specific component of NSDateComponents, by enum constant value rather than property name.
	The calendar and timeZone and isLeapMonth property values cannot be retrieved by this method.
*/
- (NSInteger)valueForComponent:(NSCalendarUnit)unit API_AVAILABLE(macos(10.9), ios(8.0), watchos(2.0), tvos(9.0));


/// A Boolean value that indicates whether the current combination of properties represents a date which exists in the current calendar.
///
/// This method is not appropriate for use on `NSDateComponents` objects which are specifying relative quantities of calendar components. The calendar property must be set, or `NO` is returned.
/*
	Reports whether or not the combination of properties which have been set in the receiver is a date which exists in the calendar.
	This method is not appropriate for use on NSDateComponents objects which are specifying relative quantities of calendar components.
	Except for some trivial cases (e.g., 'seconds' should be 0 - 59 in any calendar), this method is not necessarily cheap.
	If the time zone property is set in the NSDateComponents object, it is used.
	The calendar property must be set, or NO is returned.
*/
@property (getter=isValidDate, readonly) BOOL validDate API_AVAILABLE(macos(10.9), ios(8.0), watchos(2.0), tvos(9.0));


/// Returns a Boolean value that indicates whether the current combination of properties represents a date which exists in the specified calendar.
///
/// This method is not appropriate for use on `NSDateComponents` objects which are specifying relative quantities of calendar components.
/*
	Reports whether or not the combination of properties which have been set in the receiver is a date which exists in the calendar.
	This method is not appropriate for use on NSDateComponents objects which are specifying relative quantities of calendar components.
	Except for some trivial cases (e.g., 'seconds' should be 0 - 59 in any calendar), this method is not necessarily cheap.
	If the time zone property is set in the NSDateComponents object, it is used.
*/
- (BOOL)isValidDateInCalendar:(NSCalendar *)calendar API_AVAILABLE(macos(10.9), ios(8.0), watchos(2.0), tvos(9.0));


@end

NS_HEADER_AUDIT_END(nullability, sendability)
