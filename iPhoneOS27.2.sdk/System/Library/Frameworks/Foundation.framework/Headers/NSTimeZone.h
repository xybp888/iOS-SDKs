/*	NSTimeZone.h
	Copyright (c) 1994-2019, Apple Inc. All rights reserved.
*/

#import <Foundation/NSObject.h>
#import <Foundation/NSDate.h>
#import <Foundation/NSNotification.h>

@class NSString, NSArray<ObjectType>, NSDictionary<KeyType, ObjectType>, NSDate, NSData, NSLocale;

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

/// Information about standard time conventions associated with a specific geopolitical region.
///
/// In Swift, this type bridges to ``TimeZone``; use ``NSTimeZone`` when you need reference semantics or other Foundation-specific behavior.
///
/// Time zones represent the standard time policies for a geopolitical region. Time zones have identifiers like "America/Los\_Angeles" and can also be identified by abbreviations, such as PST for Pacific Standard Time. You can create time zone objects by ID with ``init(name:)`` and by abbreviation with ``init(abbreviation:)``.
///
/// > Note:
/// > Time zone database entries such as "America/Los\_Angeles" are IDs, not names. An example of a time zone name is "Pacific Daylight Time". Although many ``NSTimeZone`` symbols include the word "name", they actually refer to IDs.
///
/// Time zones can also represent a temporal offset—either plus or minus—from Greenwich Mean Time (GMT). For example, the temporal offset of Pacific Standard Time is 8 hours behind Greenwich Mean Time (GMT-8). You can create time zone objects with a temporal offset by using ``init(forSecondsFromGMT:)``.
///
/// You typically work with system time zones rather than creating time zones by identifier or by offset. The ``system`` class property returns the time zone currently used by the system, if known. This value is cached once the property is accessed and doesn't reflect any system time zone changes until you call the ``resetSystemTimeZone()`` method. The ``local`` class property returns an autoupdating proxy object that always returns the current time zone used by the system. You can also set the ``default`` class property to make your app run as if it were in a different time zone than the system.
///
/// > Tip:
/// > You can't use ``NSTimeZone`` APIs to change the time zone of the device or of other apps.
///
///
///
/// ``NSTimeZone`` is _toll-free bridged_ with its Core Foundation counterpart, <doc://com.apple.documentation/documentation/corefoundation/cftimezone>. See [Toll-Free Bridging](https://developer.apple.com/library/archive/documentation/General/Conceptual/CocoaEncyclopedia/Toll-FreeBridgin/Toll-FreeBridgin.html#//apple_ref/doc/uid/TP40010810-CH2) for more information on toll-free bridging.
///
/// > Important:
/// > The Swift overlay to the Foundation framework provides the ``TimeZone`` structure, which bridges to the ``NSTimeZone`` class. For more information about value types, see <doc://com.apple.documentation/documentation/swift/working-with-foundation-types>.
NS_SWIFT_SENDABLE
@interface NSTimeZone : NSObject <NSCopying, NSSecureCoding>

/// The geopolitical region ID that identifies the receiver.
@property (readonly, copy) NSString *name;
/// The data that stores the information used by the receiver.
///
/// Treat this data as an opaque object.
@property (readonly, copy) NSData *data;

/// Returns the difference in seconds between the receiver and Greenwich Mean Time at a given date.
///
/// - Parameter aDate: The date against which to test the receiver.
/// - Returns: The difference in seconds between the receiver and Greenwich Mean Time at `aDate`.
///
/// The difference may be different from the current difference if the time zone changes its offset from GMT at different points in the year--for example, the U.S. time zones change with daylight saving time.
- (NSInteger)secondsFromGMTForDate:(NSDate *)aDate;
/// Returns the abbreviation for the receiver at a given date.
///
/// - Parameter aDate: The date for which to get the abbreviation for the receiver.
/// - Returns: The abbreviation for the receiver at `aDate`.
///
/// Note that the abbreviation may be different at different dates. For example, during daylight saving time the US/Eastern time zone has an abbreviation of "EDT." At other times, its abbreviation is "EST."
- (nullable NSString *)abbreviationForDate:(NSDate *)aDate;
/// Indicates whether the receiver uses daylight saving time on a given date.
///
/// - Parameter aDate: The date against which to test the receiver.
/// - Returns: `YES` if the receiver uses daylight saving time at `aDate`, otherwise `NO`.
- (BOOL)isDaylightSavingTimeForDate:(NSDate *)aDate;
/// Returns the daylight saving time offset for a given date.
///
/// - Parameter aDate: A date.
/// - Returns: The daylight saving time offset for `aDate`.
- (NSTimeInterval)daylightSavingTimeOffsetForDate:(NSDate *)aDate API_AVAILABLE(macos(10.5), ios(2.0), watchos(2.0), tvos(9.0));
/// Returns the next daylight saving time transition after a given date.
///
/// - Parameter aDate: A date.
/// - Returns: The next daylight saving time transition after `aDate`. Depending on the time zone of the receiver, this method may return a change of the time zone's offset from GMT. Returns `nil` if the time zone of the receiver does not observe daylight savings time as of `aDate`.
- (nullable NSDate *)nextDaylightSavingTimeTransitionAfterDate:(NSDate *)aDate API_AVAILABLE(macos(10.5), ios(2.0), watchos(2.0), tvos(9.0));

@end

@interface NSTimeZone (NSExtendedTimeZone)

/// The time zone currently used by the system.
///
/// If the current system time zone cannot be determined, the GMT time zone is used instead.
///
/// If you access this class property, its value is cached by the app and doesn't update if the user subsequently changes the system time zone. In order for the property to reflect the new time zone, you must first call ``resetSystemTimeZone`` to clear the cached value.
@property (class, readonly, copy) NSTimeZone *systemTimeZone;
/// Clears any time zone value cached for the `systemTimeZone` property.
///
/// If the app has cached the system time zone by accessing the `systemTimeZone` class property, this method clears that cached value. If you subsequently access `systemTimeZone`, a new time zone object is created and cached.
+ (void)resetSystemTimeZone;

/// The default time zone for the current app.
///
/// If no default time zone has been set, the current system time zone is used. If the current system time zone cannot be determined, the GMT time zone is used instead.
///
/// The default time zone is used by the app for date and time operations. You can set it to cause the app to run as if it were in a different time zone. Setting this property clears any value that was previously set.
@property (class, copy) NSTimeZone *defaultTimeZone;

/// An object that tracks the current system time zone.
///
/// Use this property when you want an object that always reflects the current system time zone. Contrast this behavior with that of the `systemTimeZone` class property, which has its value cached until you manually clear it by calling ``resetSystemTimeZone``.
@property (class, readonly, copy) NSTimeZone *localTimeZone;

/// Returns an array of strings listing the IDs of all the time zones known to the system.
@property (class, readonly, copy) NSArray<NSString *> *knownTimeZoneNames;

/// Returns a dictionary holding the mappings of time zone abbreviations to time zone names.
///
/// Note that more than one time zone may have the same abbreviation--for example, US/Pacific and Canada/Pacific both use the abbreviation "PST." In these cases, this dictionary chooses a single name to map the abbreviation to.
@property (class, copy) NSDictionary<NSString *, NSString *> *abbreviationDictionary API_AVAILABLE(macos(10.6), ios(4.0), watchos(2.0), tvos(9.0));

+ (NSDictionary<NSString *, NSString *> *)abbreviationDictionary;

/// Returns the time zone data version.
@property (class, readonly, copy) NSString *timeZoneDataVersion API_AVAILABLE(macos(10.6), ios(4.0), watchos(2.0), tvos(9.0));

/// The current difference in seconds between the receiver and Greenwich Mean Time.
@property (readonly) NSInteger secondsFromGMT;
/// The abbreviation for the receiver, such as "EDT" (Eastern Daylight Time).
///
/// Invokes `abbreviationForDate:` with the current date as the argument.
@property (nullable, readonly, copy) NSString *abbreviation;
/// A Boolean value that indicates whether the receiver is currently using daylight saving time.
///
/// Invokes `isDaylightSavingTimeForDate:` with the current date as the argument.
@property (readonly, getter=isDaylightSavingTime) BOOL daylightSavingTime;
/// The current daylight saving time offset of the receiver.
@property (readonly) NSTimeInterval daylightSavingTimeOffset API_AVAILABLE(macos(10.5), ios(2.0), watchos(2.0), tvos(9.0)); // for current instant
/// The date of the next daylight saving time transition for the receiver.
///
/// This property contains the date of the next (after the current instant) daylight saving time transition for the receiver. Depending on the time zone of the receiver, the value of this property may represent a change of the time zone's offset from GMT. Returns `nil` if the time zone of the receiver does not currently observe daylight saving time.
@property (nullable, readonly, copy) NSDate *nextDaylightSavingTimeTransition API_AVAILABLE(macos(10.5), ios(2.0), watchos(2.0), tvos(9.0)); // after current instant

/// A textual description of the time zone including the name, abbreviation, offset from GMT, and whether or not daylight saving time is currently in effect.
@property (readonly, copy) NSString *description;

/// Indicates whether the receiver has the same name and data as the specified time zone.
///
/// - Parameter aTimeZone: The time zone to compare with the receiver.
/// - Returns: `YES` if `aTimeZone` and the receiver have the same name and data, otherwise `NO`.
- (BOOL)isEqualToTimeZone:(NSTimeZone *)aTimeZone;

/// Constants you use to specify a style when presenting time zone names.
typedef NS_ENUM(NSInteger, NSTimeZoneNameStyle) {
	/// Specifies a standard name style. For example, "Central Standard Time" for Central Time.
	NSTimeZoneNameStyleStandard,
	/// Specifies a short name style. For example, "CST" for Central Time.
	NSTimeZoneNameStyleShortStandard,
	/// Specifies a daylight saving name style. For example, "Central Daylight Time" for Central Time.
	NSTimeZoneNameStyleDaylightSaving,
	/// Specifies a short daylight saving name style. For example, "CDT" for Central Time.
	NSTimeZoneNameStyleShortDaylightSaving,
	/// Specifies a generic name style. For example, "Central Time" for Central Time.
	NSTimeZoneNameStyleGeneric,
	/// Specifies a generic time zone name. For example, "CT" for Central Time.
	NSTimeZoneNameStyleShortGeneric
};

/// Returns the localized name of the time zone.
///
/// - Parameter style: The format style for the returned string.
/// - Parameter locale: The locale for which to format the name.
/// - Returns: The name of the receiver localized for the given locale using the given style.
- (nullable NSString *)localizedName:(NSTimeZoneNameStyle)style locale:(nullable NSLocale *)locale API_AVAILABLE(macos(10.5), ios(2.0), watchos(2.0), tvos(9.0));

@end

@interface NSTimeZone (NSTimeZoneCreation)

// Primary creation method is +timeZoneWithName:; the
// data-taking variants should rarely be used directly

/// Returns the time zone object identified by a given identifier.
///
/// - Parameter tzName: The ID for the time zone.
/// - Returns: The time zone in the information directory with a name matching `tzName`. Returns `nil` if there is no match for the name.
+ (nullable instancetype)timeZoneWithName:(NSString *)tzName;
/// Returns the time zone with a given identifier whose data has been initialized using given data.
///
/// - Parameter tzName: The ID for the time zone.
/// - Parameter aData: This parameter is ignored.
/// - Returns: The time zone with the ID `tzName`.
///
/// As of macOS 10.6, the underlying implementation of this method has been changed to ignore the specified `data` parameter. You should not use this method. Instead, use `timeZoneWithName:` to get the time zone object for a given name.
+ (nullable instancetype)timeZoneWithName:(NSString *)tzName data:(nullable NSData *)aData;

/// Returns a time zone initialized with a given identifier.
///
/// - Parameter tzName: The identifier for the time zone. Providing `nil` for this parameter raises an invalid argument exception.
/// - Returns: A time zone object initialized with the identifier `tzName`.
///
/// If `tzName` is a known identifier, this method calls `initWithName:data:` with the appropriate data object.
- (nullable instancetype)initWithName:(NSString *)tzName;
/// Initializes a time zone with a given identifier and time zone data.
///
/// - Parameter tzName: The identifier for the time zone. Providing `nil` for this parameter raises an invalid argument exception.
/// - Parameter aData: This parameter is ignored.
///
/// As of macOS 10.6, the underlying implementation of this method has been changed to ignore the specified `data` parameter. You should not use this method. Instead, use `initWithName:` to initialize a time zone object with a given name.
- (nullable instancetype)initWithName:(NSString *)tzName data:(nullable NSData *)aData;

/// Returns a time zone object offset from Greenwich Mean Time by a given number of seconds.
///
/// - Parameter seconds: The number of seconds by which the new time zone is offset from GMT.
/// - Returns: A time zone object offset from Greenwich Mean Time by `seconds`.
///
/// The name of the new time zone is GMT +/- the offset, in hours and minutes. Time zones created with this method never have daylight savings, and the offset is constant no matter the date.
+ (instancetype)timeZoneForSecondsFromGMT:(NSInteger)seconds;

/// Returns the time zone object identified by a given abbreviation.
///
/// - Parameter abbreviation: An abbreviation for a time zone.
/// - Returns: The time zone object identified by `abbreviation` determined by resolving the abbreviation to a name using the abbreviation dictionary and then returning the time zone for that name. Returns `nil` if there is no match for `abbreviation`.
///
/// In general, you are discouraged from using abbreviations except for unique instances such as "GMT". Time Zone abbreviations are not standardized and so a given abbreviation may have multiple meanings--for example, "EST" refers to Eastern Time in both the United States and Australia.
+ (nullable instancetype)timeZoneWithAbbreviation:(NSString *)abbreviation;

@end

/// A notification posted when the time zone changes.
FOUNDATION_EXPORT NSNotificationName const NSSystemTimeZoneDidChangeNotification API_AVAILABLE(macos(10.5), ios(2.0), watchos(2.0), tvos(9.0));

NS_HEADER_AUDIT_END(nullability, sendability)
