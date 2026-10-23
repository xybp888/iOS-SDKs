/*	NSLocale.h
	Copyright (c) 2003-2019, Apple Inc. All rights reserved.
*/

#import <Foundation/NSObject.h>
#import <CoreFoundation/CFLocale.h>
#import <Foundation/NSNotification.h>

@class NSCalendar;

/// The keys used to access components of a locale.
///
/// Use these keys with the methods ``NSLocale/object(forKey:)`` and ``NSLocale/displayName(forKey:value:)``.
typedef NSString * NSLocaleKey NS_TYPED_ENUM;

@class NSArray<ObjectType>, NSDictionary<KeyType, ObjectType>, NSString;

// Toll-free bridged with CFLocaleRef

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

/// Information about linguistic, cultural, and technological conventions for use in formatting data for presentation.
///
/// In Swift, this object bridges to ``Locale``; use ``NSLocale`` when you need reference semantics or other Foundation-specific behavior.
///
/// You typically use a locale to format and interpret information about and according to the user's customs and preferences.
///
/// You can initialize any number of locale instances with ``init(localeIdentifier:)`` using one of the locale identifiers found in the ``availableLocaleIdentifiers`` array. However, you usually use a locale configured to match the preferences of the current user.
///
/// Use the ``current`` property to get the locale matching the current user's preferences. If you need to be alerted when the user does make changes to region settings, register for the ``currentLocaleDidChangeNotification`` notification. Alternatively, you can use the ``autoupdatingCurrent`` property to get a locale that automatically updates with the user's configuration settings:
///
/// @TabNavigator {
/// @Tab("Swift") {
/// ```swift
/// let locale = NSLocale.autoupdatingCurrent
/// ```
/// }
/// @Tab("Objective-C") {
/// ```objc
/// NSLocale* locale = [NSLocale autoupdatingCurrentLocale];
/// ```
/// }
/// }
///
///
/// You can inspect a locale by reading its properties, as listed in Getting Information About a Locale. For properties containing a code or identifier, you can then obtain a string suitable for presentation to the user with the methods listed in Getting Display Information About a Locale. For example, you can report the user's language as a string localized in that language using the autoupdating locale obtained in the previous example:
///
/// @TabNavigator {
/// @Tab("Swift") {
/// ```swift
/// let code = locale.languageCode!
/// let language = locale.localizedString(forLanguageCode: code)!
///
/// print("\(language)")
/// // Prints "English" for locale en_US, "français" for fr_FR
/// ```
/// }
/// @Tab("Objective-C") {
/// ```objc
/// NSString* code = locale.languageCode;
/// NSString* language = [locale localizedStringForLanguageCode:code];
///
/// NSLog(@"%@",language);
/// // Prints "English" for locale en_US, "français" for fr_FR
/// ```
/// }
/// }
///
///
/// You frequently use a locale in conjunction with a formatter. For example, the ``DateFormatter`` class has a ``DateFormatter/locale`` property that ensures dates are converted to strings that match the user's expectations about date formatting. By default, this property indicates the user's current locale, which is usually the behavior you want, but you can instead set it to another locale instance to obtain a different output. See [Data Formatting Guide](https://developer.apple.com/library/archive/documentation/Cocoa/Conceptual/DataFormatting/DataFormatting.html#//apple_ref/doc/uid/10000029i) for more information about working with formatters.
///
/// ``NSLocale`` is _toll-free bridged_ with its Core Foundation counterpart, <doc://com.apple.documentation/documentation/corefoundation/cflocale>. See [Toll-Free Bridging](https://developer.apple.com/library/archive/documentation/General/Conceptual/CocoaEncyclopedia/Toll-FreeBridgin/Toll-FreeBridgin.html#//apple_ref/doc/uid/TP40010810-CH2) for more information on toll-free bridging.
///
/// > Important:
/// > The Swift overlay to the Foundation framework provides the ``Locale`` structure, which bridges to the ``NSLocale`` class. For more information about value types, see <doc://com.apple.documentation/documentation/swift/working-with-foundation-types>.
NS_SWIFT_SENDABLE
@interface NSLocale : NSObject <NSCopying, NSSecureCoding>
/// Returns the object corresponding to the specified key.
- (nullable id)objectForKey:(NSLocaleKey)key;

/// Returns the display name for the given locale component value.
- (nullable NSString *)displayNameForKey:(NSLocaleKey)key value:(id)value;

/// Initializes a locale using a given locale identifier.
- (instancetype)initWithLocaleIdentifier:(NSString *)string NS_DESIGNATED_INITIALIZER;

/// Returns a locale initialized from data in the given unarchiver.
///
/// - Parameters:
///   - coder: The decoder to use during initialization.
/// - Returns: The initialized locale.
- (nullable instancetype)initWithCoder:(NSCoder *)coder NS_DESIGNATED_INITIALIZER;
@end

@interface NSLocale (NSExtendedLocale)

/// The identifier for the locale.
@property (readonly, copy) NSString *localeIdentifier;  // same as NSLocaleIdentifier
/// Returns a localized string for the specified locale identifier.
- (NSString *)localizedStringForLocaleIdentifier:(NSString *)localeIdentifier API_AVAILABLE(macosx(10.12), ios(10.0), watchos(3.0), tvos(10.0));

/// The language code for the locale.
@property (readonly, copy) NSString *languageCode API_AVAILABLE(macosx(10.12), ios(10.0), watchos(3.0), tvos(10.0));
/// Returns a localized string for the specified language code.
- (nullable NSString *)localizedStringForLanguageCode:(NSString *)languageCode API_AVAILABLE(macosx(10.12), ios(10.0), watchos(3.0), tvos(10.0));

/// Returns the identifier for the language part of the locale. For example, returns "en-US" for "en_US@rg=gbzzzz"  locale.
@property (readonly, copy) NSString *languageIdentifier API_AVAILABLE(macosx(14.0), ios(17.0), watchos(10.0), tvos(17.0));

/// The country or region code for the locale.
@property (nullable, readonly, copy) NSString *countryCode API_DEPRECATED_WITH_REPLACEMENT("regionCode", macos(10.12, API_TO_BE_DEPRECATED), ios(10.0, API_TO_BE_DEPRECATED), watchos(3.0, API_TO_BE_DEPRECATED), tvos(10.0, API_TO_BE_DEPRECATED));

/// Returns a localized string for the specified country or region code.
- (nullable NSString *)localizedStringForCountryCode:(NSString *)countryCode API_AVAILABLE(macosx(10.12), ios(10.0), watchos(3.0), tvos(10.0));

/// Returns the region code of the locale.
/// If the `rg` subtag is present, the value of the subtag will be used. For example,  returns "GB" for "en_US@rg=gbzzzz" locale.
/// If the `localeIdentifier` doesn’t contain a region, returns `nil`.
@property (nullable, readonly, copy) NSString *regionCode API_AVAILABLE(macosx(14.0), ios(17.0), watchos(10.0), tvos(17.0));

/// The script code for the locale.
@property (nullable, readonly, copy) NSString *scriptCode API_AVAILABLE(macosx(10.12), ios(10.0), watchos(3.0), tvos(10.0));
/// Returns a localized string for the specified script code.
- (nullable NSString *)localizedStringForScriptCode:(NSString *)scriptCode API_AVAILABLE(macosx(10.12), ios(10.0), watchos(3.0), tvos(10.0));

/// The variant code for the locale.
@property (nullable, readonly, copy) NSString *variantCode API_AVAILABLE(macosx(10.12), ios(10.0), watchos(3.0), tvos(10.0));
/// Returns a localized string for the specified variant code.
- (nullable NSString *)localizedStringForVariantCode:(NSString *)variantCode API_AVAILABLE(macosx(10.12), ios(10.0), watchos(3.0), tvos(10.0));

/// The exemplar character set for the locale.
@property (readonly, copy) NSCharacterSet *exemplarCharacterSet API_AVAILABLE(macosx(10.12), ios(10.0), watchos(3.0), tvos(10.0));

/// The calendar identifier for the locale.
@property (readonly, copy) NSString *calendarIdentifier API_AVAILABLE(macosx(10.12), ios(10.0), watchos(3.0), tvos(10.0));
/// Returns a localized string for the specified calendar identifier.
- (nullable NSString *)localizedStringForCalendarIdentifier:(NSString *)calendarIdentifier API_AVAILABLE(macosx(10.12), ios(10.0), watchos(3.0), tvos(10.0));

/// The collation identifier for the locale.
@property (nullable, readonly, copy) NSString *collationIdentifier API_AVAILABLE(macosx(10.12), ios(10.0), watchos(3.0), tvos(10.0));
/// Returns a localized string for the specified collation identifier.
- (nullable NSString *)localizedStringForCollationIdentifier:(NSString *)collationIdentifier API_AVAILABLE(macosx(10.12), ios(10.0), watchos(3.0), tvos(10.0));

/// A Boolean value that indicates whether the locale uses the metric system.
@property (readonly) BOOL usesMetricSystem API_AVAILABLE(macosx(10.12), ios(10.0), watchos(3.0), tvos(10.0));

/// The decimal separator for the locale.
@property (readonly, copy) NSString *decimalSeparator API_AVAILABLE(macosx(10.12), ios(10.0), watchos(3.0), tvos(10.0));

/// The grouping separator for the locale.
@property (readonly, copy) NSString *groupingSeparator API_AVAILABLE(macosx(10.12), ios(10.0), watchos(3.0), tvos(10.0));

/// The currency symbol for the locale.
@property (readonly, copy) NSString *currencySymbol API_AVAILABLE(macosx(10.12), ios(10.0), watchos(3.0), tvos(10.0));

/// The currency code for the locale.
@property (nullable, readonly, copy) NSString *currencyCode API_AVAILABLE(macosx(10.12), ios(10.0), watchos(3.0), tvos(10.0));
/// Returns a localized string for the specified currency code.
- (nullable NSString *)localizedStringForCurrencyCode:(NSString *)currencyCode API_AVAILABLE(macosx(10.12), ios(10.0), watchos(3.0), tvos(10.0));

/// The collator identifier for the locale.
@property (readonly, copy) NSString *collatorIdentifier API_AVAILABLE(macosx(10.12), ios(10.0), watchos(3.0), tvos(10.0));
/// Returns a localized string for the specified collator identifier.
- (nullable NSString *)localizedStringForCollatorIdentifier:(NSString *)collatorIdentifier API_AVAILABLE(macosx(10.12), ios(10.0), watchos(3.0), tvos(10.0));

/// The begin quotation delimiter for the locale.
@property (readonly, copy) NSString *quotationBeginDelimiter API_AVAILABLE(macosx(10.12), ios(10.0), watchos(3.0), tvos(10.0));

/// The end quotation delimiter for the locale.
@property (readonly, copy) NSString *quotationEndDelimiter API_AVAILABLE(macosx(10.12), ios(10.0), watchos(3.0), tvos(10.0));

/// The begin quotation delimiter for the locale when using alternate quotation marks.
@property (readonly, copy) NSString *alternateQuotationBeginDelimiter API_AVAILABLE(macosx(10.12), ios(10.0), watchos(3.0), tvos(10.0));

/// The end quotation delimiter for the locale when using alternate quotation marks.
@property (readonly, copy) NSString *alternateQuotationEndDelimiter API_AVAILABLE(macosx(10.12), ios(10.0), watchos(3.0), tvos(10.0));

@end

@interface NSLocale (NSLocaleCreation)

/// A locale representing the user's region settings at the time the property is read.
@property (class, readonly, strong) NSLocale *autoupdatingCurrentLocale API_AVAILABLE(macos(10.5), ios(2.0), watchos(2.0), tvos(9.0)); // generally you should use this property

/// An object representing the user's current locale.
@property (class, readonly, copy) NSLocale *currentLocale;	// an object representing the user's current locale
/// The default generic root locale with little localization.
@property (class, readonly, copy) NSLocale *systemLocale;	// the default generic root locale with little localization

/// Creates and returns a locale initialized with the given locale identifier.
+ (instancetype)localeWithLocaleIdentifier:(NSString *)ident API_AVAILABLE(macos(10.6), ios(4.0), watchos(2.0), tvos(9.0));

- (instancetype)init NS_UNAVAILABLE;     /* do not invoke; not a valid initializer for this class */

@end

@interface NSLocale (NSLocaleGeneralInfo)

/// An array of NSString objects, each of which identifies a locale available on the system.
@property (class, readonly, copy) NSArray<NSString *> *availableLocaleIdentifiers;
/// An array of NSString objects that represents all known legal ISO language codes.
@property (class, readonly, copy) NSArray<NSString *> *ISOLanguageCodes;
/// An array of NSString objects that represents all known legal ISO country codes.
@property (class, readonly, copy) NSArray<NSString *> *ISOCountryCodes;
/// An array of NSString objects that represents all known legal ISO currency codes.
@property (class, readonly, copy) NSArray<NSString *> *ISOCurrencyCodes;
/// An array of common ISO currency codes.
@property (class, readonly, copy) NSArray<NSString *> *commonISOCurrencyCodes API_AVAILABLE(macos(10.5), ios(2.0), watchos(2.0), tvos(9.0));

/// An ordered list of the user's preferred languages.
@property (class, readonly, copy) NSArray<NSString *> *preferredLanguages API_AVAILABLE(macos(10.5), ios(2.0), watchos(2.0), tvos(9.0)); // note that this list does not indicate what language the app is actually running in; the NSBundle.mainBundle object determines that at launch and knows that information

/// Returns a dictionary that is the result of parsing a locale ID.
+ (NSDictionary<NSString *, NSString *> *)componentsFromLocaleIdentifier:(NSString *)string;
/// Returns a locale identifier from the components specified in a given dictionary.
+ (NSString *)localeIdentifierFromComponents:(NSDictionary<NSString *, NSString *> *)dict;

/// Returns the canonical identifier for a given locale identification string.
+ (NSString *)canonicalLocaleIdentifierFromString:(NSString *)string;
/// Returns a canonical language identifier by mapping an arbitrary locale identification string to the canonical identifier.
+ (NSString *)canonicalLanguageIdentifierFromString:(NSString *)string;

/// Returns a locale identifier from a Windows locale code.
+ (nullable NSString *)localeIdentifierFromWindowsLocaleCode:(uint32_t)lcid API_AVAILABLE(macos(10.6), ios(4.0), watchos(2.0), tvos(9.0));
/// Returns a Windows locale code from the locale identifier.
+ (uint32_t)windowsLocaleCodeFromLocaleIdentifier:(NSString *)localeIdentifier API_AVAILABLE(macos(10.6), ios(4.0), watchos(2.0), tvos(9.0));

/// The directions that a language may take across a page of text.
///
/// Use these constants with the methods ``NSLocale/lineDirection(forLanguage:)`` and ``NSLocale/characterDirection(forLanguage:)``.
typedef NS_ENUM(NSUInteger, NSLocaleLanguageDirection) {
    /// The language direction is unknown.
    NSLocaleLanguageDirectionUnknown = kCFLocaleLanguageDirectionUnknown,
    /// The language direction is from left to right.
    NSLocaleLanguageDirectionLeftToRight = kCFLocaleLanguageDirectionLeftToRight,
    /// The language direction is from right to left.
    NSLocaleLanguageDirectionRightToLeft = kCFLocaleLanguageDirectionRightToLeft,
    /// The language direction is from top to bottom.
    NSLocaleLanguageDirectionTopToBottom = kCFLocaleLanguageDirectionTopToBottom,
    /// The language direction is from bottom to top.
    NSLocaleLanguageDirectionBottomToTop = kCFLocaleLanguageDirectionBottomToTop
};

/// Returns the direction of the sequence of characters in a line for the specified ISO language code.
+ (NSLocaleLanguageDirection)characterDirectionForLanguage:(NSString *)isoLangCode API_AVAILABLE(macos(10.6), ios(4.0), watchos(2.0), tvos(9.0));
/// Returns the direction of the sequence of lines for the specified ISO language code.
+ (NSLocaleLanguageDirection)lineDirectionForLanguage:(NSString *)isoLangCode API_AVAILABLE(macos(10.6), ios(4.0), watchos(2.0), tvos(9.0));

@end

/// A notification that indicates that the user's locale changed.
FOUNDATION_EXPORT NSNotificationName const NSCurrentLocaleDidChangeNotification API_AVAILABLE(macos(10.5), ios(2.0), watchos(2.0), tvos(9.0));


/// The locale identifier.
FOUNDATION_EXPORT NSLocaleKey const NSLocaleIdentifier;		// NSString
/// The locale language code.
FOUNDATION_EXPORT NSLocaleKey const NSLocaleLanguageCode;	// NSString
/// The locale country code.
FOUNDATION_EXPORT NSLocaleKey const NSLocaleCountryCode;		// NSString
/// The locale script code.
FOUNDATION_EXPORT NSLocaleKey const NSLocaleScriptCode;		// NSString
/// The locale variant code.
FOUNDATION_EXPORT NSLocaleKey const NSLocaleVariantCode;		// NSString
/// The locale exemplar character set.
FOUNDATION_EXPORT NSLocaleKey const NSLocaleExemplarCharacterSet;// NSCharacterSet
/// The locale calendar.
FOUNDATION_EXPORT NSLocaleKey const NSLocaleCalendar;		// NSCalendar
/// The locale collation identifier.
FOUNDATION_EXPORT NSLocaleKey const NSLocaleCollationIdentifier; // NSString
/// A Boolean value that indicates whether the locale uses the metric system.
FOUNDATION_EXPORT NSLocaleKey const NSLocaleUsesMetricSystem;	// NSNumber boolean
/// The measurement system for the locale.
FOUNDATION_EXPORT NSLocaleKey const NSLocaleMeasurementSystem;	// NSString
/// The decimal separator for the locale.
FOUNDATION_EXPORT NSLocaleKey const NSLocaleDecimalSeparator;	// NSString
/// The grouping separator for the locale.
FOUNDATION_EXPORT NSLocaleKey const NSLocaleGroupingSeparator;	// NSString
/// The currency symbol for the locale.
FOUNDATION_EXPORT NSLocaleKey const NSLocaleCurrencySymbol;      // NSString
/// The currency code for the locale.
FOUNDATION_EXPORT NSLocaleKey const NSLocaleCurrencyCode;	// NSString
/// The collator identifier for the locale.
FOUNDATION_EXPORT NSLocaleKey const NSLocaleCollatorIdentifier API_AVAILABLE(macos(10.6), ios(4.0), watchos(2.0), tvos(9.0));  // NSString
/// The begin quotation delimiter key for the locale.
FOUNDATION_EXPORT NSLocaleKey const NSLocaleQuotationBeginDelimiterKey API_AVAILABLE(macos(10.6), ios(4.0), watchos(2.0), tvos(9.0));	// NSString
/// The end quotation delimiter key for the locale.
FOUNDATION_EXPORT NSLocaleKey const NSLocaleQuotationEndDelimiterKey API_AVAILABLE(macos(10.6), ios(4.0), watchos(2.0), tvos(9.0));	// NSString
/// The alternate begin quotation delimiter key for the locale.
FOUNDATION_EXPORT NSLocaleKey const NSLocaleAlternateQuotationBeginDelimiterKey API_AVAILABLE(macos(10.6), ios(4.0), watchos(2.0), tvos(9.0));	// NSString
/// The alternate end quotation delimiter key for the locale.
FOUNDATION_EXPORT NSLocaleKey const NSLocaleAlternateQuotationEndDelimiterKey API_AVAILABLE(macos(10.6), ios(4.0), watchos(2.0), tvos(9.0));	// NSString


#if !defined(NS_CALENDAR_ENUM_DEPRECATED)
#define NS_CALENDAR_ENUM_DEPRECATED(A, B, C, D, ...) NS_ENUM_DEPRECATED(A, B, C, D, __VA_ARGS__)
#define NS_CALENDAR_DEPRECATED(A, B, C, D, ...) NS_DEPRECATED(A, B, C, D, __VA_ARGS__)
#define NS_CALENDAR_DEPRECATED_MAC(A, B, ...) NS_DEPRECATED_MAC(A, B, __VA_ARGS__)
#endif

// Values for NSCalendar identifiers (not the NSLocaleCalendar property key)
/// Identifier for the Gregorian calendar.
FOUNDATION_EXPORT NSString * const NSGregorianCalendar API_DEPRECATED_WITH_REPLACEMENT("NSCalendarIdentifierGregorian", macos(10.4, 10.10), ios(2.0, 8.0), watchos(2.0, 2.0), tvos(9.0, 9.0));
/// Identifier for the Buddhist calendar.
FOUNDATION_EXPORT NSString * const NSBuddhistCalendar API_DEPRECATED_WITH_REPLACEMENT("NSCalendarIdentifierBuddhist", macos(10.4, 10.10), ios(2.0, 8.0), watchos(2.0, 2.0), tvos(9.0, 9.0));
/// Identifier for the Chinese calendar.
FOUNDATION_EXPORT NSString * const NSChineseCalendar API_DEPRECATED_WITH_REPLACEMENT("NSCalendarIdentifierChinese", macos(10.4, 10.10), ios(2.0, 8.0), watchos(2.0, 2.0), tvos(9.0, 9.0));
/// Identifier for the Hebrew calendar.
FOUNDATION_EXPORT NSString * const NSHebrewCalendar API_DEPRECATED_WITH_REPLACEMENT("NSCalendarIdentifierHebrew", macos(10.4, 10.10), ios(2.0, 8.0), watchos(2.0, 2.0), tvos(9.0, 9.0));
/// Identifier for the Islamic calendar.
FOUNDATION_EXPORT NSString * const NSIslamicCalendar API_DEPRECATED_WITH_REPLACEMENT("NSCalendarIdentifierIslamic", macos(10.4, 10.10), ios(2.0, 8.0), watchos(2.0, 2.0), tvos(9.0, 9.0));
/// Identifier for the Islamic civil calendar.
FOUNDATION_EXPORT NSString * const NSIslamicCivilCalendar API_DEPRECATED_WITH_REPLACEMENT("NSCalendarIdentifierIslamicCivil", macos(10.4, 10.10), ios(2.0, 8.0), watchos(2.0, 2.0), tvos(9.0, 9.0));
/// Identifier for the Japanese calendar.
FOUNDATION_EXPORT NSString * const NSJapaneseCalendar API_DEPRECATED_WITH_REPLACEMENT("NSCalendarIdentifierJapanese", macos(10.4, 10.10), ios(2.0, 8.0), watchos(2.0, 2.0), tvos(9.0, 9.0));
/// Identifier for the Republic of China calendar.
FOUNDATION_EXPORT NSString * const NSRepublicOfChinaCalendar API_DEPRECATED_WITH_REPLACEMENT("NSCalendarIdentifierRepublicOfChina", macos(10.6, 10.10), ios(4.0, 8.0), watchos(2.0, 2.0), tvos(9.0, 9.0));
/// Identifier for the Persian calendar.
FOUNDATION_EXPORT NSString * const NSPersianCalendar API_DEPRECATED_WITH_REPLACEMENT("NSCalendarIdentifierPersian", macos(10.6, 10.10), ios(4.0, 8.0), watchos(2.0, 2.0), tvos(9.0, 9.0));
/// Identifier for the Indian calendar.
FOUNDATION_EXPORT NSString * const NSIndianCalendar API_DEPRECATED_WITH_REPLACEMENT("NSCalendarIdentifierIndian", macos(10.6, 10.10), ios(4.0, 8.0), watchos(2.0, 2.0), tvos(9.0, 9.0));
/// Identifier for the ISO8601 calendar.
FOUNDATION_EXPORT NSString * const NSISO8601Calendar API_DEPRECATED_WITH_REPLACEMENT("NSCalendarIdentifierISO8601", macos(10.6, 10.10), ios(4.0, 8.0), watchos(2.0, 2.0), tvos(9.0, 9.0));

NS_HEADER_AUDIT_END(nullability, sendability)
