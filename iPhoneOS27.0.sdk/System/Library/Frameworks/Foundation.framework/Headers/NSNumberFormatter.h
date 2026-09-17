/*	NSNumberFormatter.h
	Copyright (c) 1996-2019, Apple Inc. All rights reserved.
*/

#import <Foundation/NSFormatter.h>
#include <CoreFoundation/CFNumberFormatter.h>

@class NSLocale, NSError, NSMutableDictionary, NSRecursiveLock, NSString, NSCache;

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

/// These constants specify the behavior of a number formatter. These constants are returned by the
/// \c defaultFormatterBehavior class method and the \c formatterBehavior property.
typedef NS_ENUM(NSUInteger, NSNumberFormatterBehavior) {
    /// The number-formatter behavior set as the default for new instances. You can set the default
    /// formatter behavior with the class method \c setDefaultFormatterBehavior: .
    NSNumberFormatterBehaviorDefault = 0,
#if TARGET_OS_OSX
    /// The number-formatter behavior as it existed prior to macOS 10.4.
    NSNumberFormatterBehavior10_0 = 1000,
#endif
    /// The number-formatter behavior since macOS 10.4.
    NSNumberFormatterBehavior10_4 = 1040,
};

/// A formatter that converts between numeric values and their textual representations.
///
/// Instances of ``NumberFormatter`` format the textual representation of cells that contain ``NSNumber`` objects and convert textual representations of numeric values into ``NSNumber`` objects. The representation encompasses integers, floats, and doubles; floats and doubles can be formatted to a specified decimal position. ``NumberFormatter`` objects can also impose ranges on the numeric values cells can accept.
///
/// > Tip:
/// > In Swift, you can use ``IntegerFormatStyle``, ``FloatingPointFormatStyle``, or ``Decimal/FormatStyle`` rather than ``NumberFormatter``. The ``FormatStyle`` API offers a declarative idiom for customizing the formatting of various types. Also, Foundation caches identical ``FormatStyle`` instances, so you don't need to pass them around your app, or risk wasting memory with duplicate formatters.
///
/// ### Significant Digits and Fraction Digits
///
/// The ``NumberFormatter`` class provides flexible options for displaying non-zero fractional parts of numbers.
///
/// If you set the ``usesSignificantDigits`` property to <doc://com.apple.documentation/documentation/swift/true>, you can configure ``NumberFormatter`` to display significant digits using the ``minimumSignificantDigits`` and ``maximumSignificantDigits`` properties. If ``usesSignificantDigits`` is <doc://com.apple.documentation/documentation/swift/false>, these properties are ignored. See Configuring Significant Digits.
///
/// Otherwise, you can configure the minimum and maximum number of integer and fraction digits, or the numbers before and after the decimal separator, respectively, using the ``minimumIntegerDigits``, ``maximumIntegerDigits``, ``minimumFractionDigits``, and ``maximumFractionDigits`` properties. See Configuring Integer and Fraction Digits.
///
/// ### Thread Safety
///
/// On iOS 7 and later ``NumberFormatter`` is thread-safe.
///
/// In macOS 10.9 and later ``NumberFormatter`` is thread-safe so long as you are using the modern behavior in a 64-bit app.
///
/// On earlier versions of the operating system, or when using the legacy formatter behavior or running in 32-bit in macOS, ``NumberFormatter`` is not thread-safe, and you therefore must not mutate a number formatter simultaneously from multiple threads.
NS_SWIFT_SENDABLE
@interface NSNumberFormatter : NSFormatter

/// The capitalization formatting context used when formatting a number.
///
/// Defaults to \c NSFormattingContextUnknown.
@property NSFormattingContext formattingContext API_AVAILABLE(macos(10.10), ios(8.0), watchos(2.0), tvos(9.0)); // default is NSFormattingContextUnknown

// - (id)init; // designated initializer

// Report the used range of the string and an NSError, in addition to the usual stuff from NSFormatter

/// Returns by reference a cell-content object after creating it from a range of characters in a given string.
///
/// If a string contains any characters other than numerical digits or locale-appropriate group or decimal
/// separators, parsing will fail.
///
/// Any leading or trailing space separator characters in a string are ignored. For example, the strings
/// " 5", "5 ", and "5" all produce the number \c 5.
///
/// If there is an error, this method calls \c control:didFailToFormatString:errorDescription: on the delegate.
/// @param obj On return, contains an instance of \c NSDecimalNumber or \c NSNumber based on the current value
/// of the \c generatesDecimalNumbers property. Returns \c nil by reference if conversion failed.
/// @param string A string object with the range of characters specified in \c rangep that is used to create \c anObject.
/// @param rangep A range of characters in \c aString. On return, contains the actual range of characters used to
/// create the object.
/// @param error If an error occurs, upon return contains an \c NSError object that explains why the conversion failed.
/// @return \c YES if the conversion from string to cell-content object was successful, otherwise \c NO.
- (BOOL)getObjectValue:(out id _Nullable * _Nullable)obj forString:(NSString *)string range:(inout nullable NSRange *)rangep error:(out NSError **)error;

// Even though NSNumberFormatter responds to the usual NSFormatter methods,
//   here are some convenience methods which are a little more obvious.

/// Returns a string containing the formatted value of the provided number object.
/// @param number An \c NSNumber object that is parsed to create the returned string object.
/// @return A string containing the formatted value of \c number using the receiver's current settings.
- (nullable NSString *)stringFromNumber:(NSNumber *)number;
/// Returns an \c NSNumber object created by parsing a given string.
///
/// If a string contains any characters other than numerical digits or locale-appropriate group or decimal
/// separators, parsing will fail.
///
/// Any leading or trailing space separator characters in a string are ignored. For example, the strings
/// " 5", "5 ", and "5" all produce the number \c 5.
/// @param string An \c NSString object that is parsed to generate the returned number object.
/// @return An \c NSNumber object created by parsing \c string using the receiver's format, or \c nil if no single
/// number could be parsed.
- (nullable NSNumber *)numberFromString:(NSString *)string;

/// The predefined number format styles used by the \c numberStyle property.
typedef NS_ENUM(NSUInteger, NSNumberFormatterStyle) {
    /// An integer representation.
    ///
    /// For example, the number 1234.5678 is represented as 1235.
    NSNumberFormatterNoStyle = kCFNumberFormatterNoStyle,
    /// A decimal style format.
    ///
    /// For example, in the en_US locale, the number 1234.5678 is represented as 1,234.568.
    NSNumberFormatterDecimalStyle = kCFNumberFormatterDecimalStyle,
    /// A currency style format that uses the currency symbol defined by the number formatter locale.
    ///
    /// For example, in the en_US locale, the number 1234.5678 is represented as $1,234.57; in the fr_FR
    /// locale, the number 1234.5678 is represented as 1 234,57 EUR.
    NSNumberFormatterCurrencyStyle = kCFNumberFormatterCurrencyStyle,
    /// A percent style format.
    ///
    /// For example, in the en_US locale, the number 0.123 is represented as 12%.
    NSNumberFormatterPercentStyle = kCFNumberFormatterPercentStyle,
    /// A scientific style format.
    ///
    /// For example, in the en_US locale, the number 1234.5678 is represented as 1.2345678E3.
    NSNumberFormatterScientificStyle = kCFNumberFormatterScientificStyle,
    /// A style format in which numbers are spelled out in the language defined by the number formatter locale.
    ///
    /// For example, in the en_US locale, the number 1234.5678 is represented as one thousand two hundred
    /// thirty-four point five six seven eight; in the fr_FR locale, the number 1234.5678 is represented as
    /// mille deux cent trente-quatre virgule cinq six sept huit.
    ///
    /// This style is supported for most user locales. If this style doesn't support the number formatter
    /// locale, the en_US locale is used as a fallback.
    NSNumberFormatterSpellOutStyle = kCFNumberFormatterSpellOutStyle,
    /// An ordinal style format.
    ///
    /// For example, in the en_US locale, the number 3 is represented as 3rd; in the fr_FR locale, the number
    /// 3 is represented as 3e.
    NSNumberFormatterOrdinalStyle API_AVAILABLE(macos(10.11), ios(9.0), watchos(2.0), tvos(9.0)) = kCFNumberFormatterOrdinalStyle,
    /// A currency style format that uses the ISO 4217 currency code defined by the number formatter locale.
    ///
    /// This style behaves like the currency style, except that the currency symbol is replaced by the
    /// corresponding ISO 4217 currency code. For example, in the en_US locale, the number 1234.5678 is
    /// represented as USD1,234.57; in the fr_FR locale, the number 1234.5678 is represented as 1 234,57 EUR.
    NSNumberFormatterCurrencyISOCodeStyle API_AVAILABLE(macos(10.11), ios(9.0), watchos(2.0), tvos(9.0)) = kCFNumberFormatterCurrencyISOCodeStyle,
    /// A currency style format that uses the pluralized denomination defined by the number formatter locale.
    ///
    /// This style behaves like the currency style, except that the currency symbol is replaced by the
    /// corresponding pluralized denomination. For example, in the en_US locale, the number 1234.5678 is
    /// represented as 1,234.57 US dollars; in the fr_FR locale, the number 1234.5678 is represented as
    /// 1 234,57 euros.
    NSNumberFormatterCurrencyPluralStyle API_AVAILABLE(macos(10.11), ios(9.0), watchos(2.0), tvos(9.0)) = kCFNumberFormatterCurrencyPluralStyle,
    /// An accounting currency style format that uses the currency symbol defined by the number formatter locale.
    ///
    /// This style behaves like the currency style, except that negative numbers representations are surrounded
    /// by parentheses rather than preceded by a negative symbol. For example, in the en_US locale, the number
    /// -1234.5678 is represented as ($1,234.57); in the fr_FR locale, the number -1234.5678 is represented as
    /// (1 234,57 EUR).
    NSNumberFormatterCurrencyAccountingStyle API_AVAILABLE(macos(10.11), ios(9.0), watchos(2.0), tvos(9.0)) = kCFNumberFormatterCurrencyAccountingStyle,
};

/// Returns a localized number string with the specified style.
/// @param num The number to localize.
/// @param nstyle The localization style to use.
/// @return An appropriately formatted \c NSString.
+ (NSString *)localizedStringFromNumber:(NSNumber *)num numberStyle:(NSNumberFormatterStyle)nstyle API_AVAILABLE(macos(10.6), ios(4.0), watchos(2.0), tvos(9.0));

// Attributes of an NSNumberFormatter

/// Returns an \c NSNumberFormatterBehavior constant that indicates default formatter behavior for new
/// instances of \c NSNumberFormatter.
+ (NSNumberFormatterBehavior)defaultFormatterBehavior;
/// Sets the default formatter behavior for new instances of \c NSNumberFormatter.
/// @param behavior An \c NSNumberFormatterBehavior constant that indicates the revision of the class
/// providing the default behavior.
+ (void)setDefaultFormatterBehavior:(NSNumberFormatterBehavior)behavior;

/// See \c kCFNumberFormatterMinGroupingDigits in \c CFNumberFormatter for an explanation on how minimum grouping digits is used.
@property NSInteger minimumGroupingDigits API_AVAILABLE(macos(15.0), ios(18.0), watchos(11.0), tvos(18.0), visionos(2.0));
/// The number style used by the receiver.
///
/// Styles are essentially predetermined sets of values for certain properties. Examples of number-formatter
/// styles are those used for decimal values, percentage values, and currency.
@property NSNumberFormatterStyle numberStyle;
/// The locale of the receiver.
///
/// The locale determines the default values for many formatter attributes, such as ISO region and language
/// codes, currency code, calendar, system of measurement, and decimal separator.
@property (null_resettable, copy) NSLocale *locale;
/// Determines whether the receiver creates instances of \c NSDecimalNumber when it converts strings to
/// number objects.
@property BOOL generatesDecimalNumbers;
/// The formatter behavior of the receiver.
@property NSNumberFormatterBehavior formatterBehavior;

/// The format the receiver uses to display negative values.
@property (null_resettable, copy) NSString *negativeFormat;
/// The text attributes to be used in displaying negative values.
///
/// This property is a dictionary that contains the attributes used to display negative values.
@property (nullable, copy) NSDictionary<NSString *, id> *textAttributesForNegativeValues;
/// The format the receiver uses to display positive values.
@property (null_resettable, copy) NSString *positiveFormat;
/// The text attributes to be used in displaying positive values.
///
/// This property is a dictionary that contains the attributes used to display positive values.
@property (nullable, copy) NSDictionary<NSString *, id> *textAttributesForPositiveValues;
/// Determines whether the receiver allows as input floating-point values (that is, values that include the
/// period character (\c .)).
///
/// By default, floating point values are allowed.
@property BOOL allowsFloats;
/// The character the receiver uses as a decimal separator.
@property (null_resettable, copy) NSString *decimalSeparator;
/// Determines whether the receiver always shows the decimal separator, even for integer numbers.
@property BOOL alwaysShowsDecimalSeparator;
/// The string used by the receiver as a currency decimal separator.
@property (null_resettable, copy) NSString *currencyDecimalSeparator;
/// Determines whether the receiver displays the group separator.
@property BOOL usesGroupingSeparator;
/// The string used by the receiver for a grouping separator.
///
/// For example, the grouping separator used in the United States is the comma ("10,000") whereas in France
/// it is the space ("10 000").
@property (null_resettable, copy) NSString *groupingSeparator;

/// The string used to represent a zero value.
///
/// If not specified, zero values are formatted normally.
///
/// You might, for example, set this property to \c "-" in a spreadsheet used for accounting.
@property (nullable, copy) NSString *zeroSymbol;
/// The text attributes used to display a zero value.
///
/// This property is a dictionary that contains the text attributes used to display zero values.
@property (nullable, copy) NSDictionary<NSString *, id> *textAttributesForZero;
/// The string used to represent a \c nil value.
///
/// By default, this property is set to an empty string ("").
@property (copy) NSString *nilSymbol;
/// The text attributes used to display the \c nil symbol.
@property (nullable, copy) NSDictionary<NSString *, id> *textAttributesForNil;
/// The string used to represent a NaN ("not a number") value.
///
/// By default, this property is set to the string "NaN".
@property (null_resettable, copy) NSString *notANumberSymbol;
/// The text attributes used to display the NaN ("not a number") string.
@property (nullable, copy) NSDictionary<NSString *, id> *textAttributesForNotANumber;
/// The string used to represent a positive infinity symbol.
///
/// By default, this property is set to the string "+\u221e".
@property (copy) NSString *positiveInfinitySymbol;
/// The text attributes used to display the positive infinity symbol.
///
/// This property is a dictionary that contains the text attributes used to display the positive infinity string.
@property (nullable, copy) NSDictionary<NSString *, id> *textAttributesForPositiveInfinity;
/// The string used to represent a negative infinity symbol.
///
/// By default, this property is set to the string "-\u221e".
@property (copy) NSString *negativeInfinitySymbol;
/// The text attributes used to display the negative infinity symbol.
///
/// This property is a dictionary that contains the text attributes used to display the negative infinity string.
@property (nullable, copy) NSDictionary<NSString *, id> *textAttributesForNegativeInfinity;

/// The string the receiver uses as the prefix for positive values.
@property (null_resettable, copy) NSString *positivePrefix;
/// The string the receiver uses as the suffix for positive values.
@property (null_resettable, copy) NSString *positiveSuffix;
/// The string the receiver uses as a prefix for negative values.
@property (null_resettable, copy) NSString *negativePrefix;
/// The string the receiver uses as a suffix for negative values.
@property (null_resettable, copy) NSString *negativeSuffix;
/// The receiver's currency code.
///
/// A currency code is a three-letter code that is, in most cases, composed of a region's two-character
/// Internet region code plus an extra character to denote the currency unit. For example, the currency code
/// for the Australian dollar is "AUD". Currency codes are based on the ISO 4217 standard.
@property (null_resettable, copy) NSString *currencyCode;
/// The string used by the receiver as a local currency symbol.
///
/// A region typically has a local currency symbol and an international currency symbol. The local symbol is
/// used within the region, while the international currency symbol is used in international contexts to specify
/// that region's currency unambiguously. The local currency symbol is often represented by a Unicode code point.
@property (null_resettable, copy) NSString *currencySymbol;
/// The international currency symbol used by the receiver.
///
/// A region typically has a local currency symbol and an international currency symbol. The local symbol is
/// used within the region, while the international currency symbol is used in international contexts to specify
/// that region's currency unambiguously. The international currency symbol is often represented by a Unicode
/// code point.
@property (null_resettable, copy) NSString *internationalCurrencySymbol;
/// The string used to represent a percent symbol.
///
/// By default, this property is set to the percent sign (%).
@property (null_resettable, copy) NSString *percentSymbol;
/// The string used to represent a per-mill (per-thousand) symbol.
///
/// By default, this property is set to the per mille sign (\u2030).
@property (null_resettable, copy) NSString *perMillSymbol;
/// The string used to represent a minus sign.
///
/// By default, this property is set to the minus sign (-).
@property (null_resettable, copy) NSString *minusSign;
/// The string used to represent a plus sign.
///
/// By default, this property is set to the plus sign (+).
@property (null_resettable, copy) NSString *plusSign;
/// The string used to represent an exponent symbol.
///
/// By default, this property is set to the latin capital letter E.
///
/// The exponent symbol is the "E" or "e" in the scientific notation of numbers, as in "1.0E+42".
@property (null_resettable, copy) NSString *exponentSymbol;

/// The grouping size of the receiver.
@property NSUInteger groupingSize;
/// The secondary grouping size of the receiver.
///
/// Some locales allow the specification of another grouping size for larger numbers. For example, some locales
/// may represent a number such as 61, 242, 378.46 (as in the United States) as 6,12,42,378.46. In this case,
/// the secondary grouping size (covering the groups of digits furthest from the decimal point) is 2.
@property NSUInteger secondaryGroupingSize;
/// The multiplier of the receiver.
///
/// A multiplier is a factor used in conversions between numbers and strings (that is, numbers as stored and
/// numbers as displayed). When the input value is a string, the multiplier is used to divide, and when the
/// input value is a number, the multiplier is used to multiply. These operations allow the formatted values
/// to be different from the values that a program manipulates internally.
@property (nullable, copy) NSNumber *multiplier;
/// The format width used by the receiver.
///
/// The format width is the number of characters of a formatted number within a string that is either left
/// justified or right justified based on the value contained in \c paddingPosition.
@property NSUInteger formatWidth;
/// The string that the receiver uses to pad numbers in the formatted string representation.
@property (null_resettable, copy) NSString *paddingCharacter;


/// These constants are used to specify how numbers should be padded. These constants are used by the
/// \c paddingPosition property.
typedef NS_ENUM(NSUInteger, NSNumberFormatterPadPosition) {
    /// Specifies that the padding should occur before the prefix.
    NSNumberFormatterPadBeforePrefix = kCFNumberFormatterPadBeforePrefix,
    /// Specifies that the padding should occur after the prefix.
    NSNumberFormatterPadAfterPrefix = kCFNumberFormatterPadAfterPrefix,
    /// Specifies that the padding should occur before the suffix.
    NSNumberFormatterPadBeforeSuffix = kCFNumberFormatterPadBeforeSuffix,
    /// Specifies that the padding should occur after the suffix.
    NSNumberFormatterPadAfterSuffix = kCFNumberFormatterPadAfterSuffix
};

/// These constants are used to specify how numbers should be rounded. These constants are used by the
/// \c roundingMode property.
typedef NS_ENUM(NSUInteger, NSNumberFormatterRoundingMode) {
    /// Round towards positive infinity.
    NSNumberFormatterRoundCeiling = kCFNumberFormatterRoundCeiling,
    /// Round towards negative infinity.
    NSNumberFormatterRoundFloor = kCFNumberFormatterRoundFloor,
    /// Round towards zero.
    NSNumberFormatterRoundDown = kCFNumberFormatterRoundDown,
    /// Round away from zero.
    NSNumberFormatterRoundUp = kCFNumberFormatterRoundUp,
    /// Round towards the nearest integer, or towards an even number if equidistant.
    NSNumberFormatterRoundHalfEven = kCFNumberFormatterRoundHalfEven,
    /// Round towards the nearest integer, or towards zero if equidistant.
    NSNumberFormatterRoundHalfDown = kCFNumberFormatterRoundHalfDown,
    /// Round towards the nearest integer, or away from zero if equidistant.
    NSNumberFormatterRoundHalfUp = kCFNumberFormatterRoundHalfUp
};

/// The padding position used by the receiver.
@property NSNumberFormatterPadPosition paddingPosition;
/// The rounding mode used by the receiver.
@property NSNumberFormatterRoundingMode roundingMode;
/// The rounding increment used by the receiver.
@property (null_resettable, copy) NSNumber *roundingIncrement;
/// The minimum number of digits before the decimal separator.
///
/// By default, this property is set to \c 0.
@property NSUInteger minimumIntegerDigits;
/// The maximum number of digits before the decimal separator.
///
/// By default, this property is set to \c 42.
@property NSUInteger maximumIntegerDigits;
/// The minimum number of digits after the decimal separator.
///
/// By default, this property is set to \c 0.
@property NSUInteger minimumFractionDigits;
/// The maximum number of digits after the decimal separator.
///
/// By default, this property is set to \c 0.
@property NSUInteger maximumFractionDigits;
/// The lowest number allowed as input by the receiver.
@property (nullable, copy) NSNumber *minimum;
/// The highest number allowed as input by the receiver.
@property (nullable, copy) NSNumber *maximum;
/// The currency grouping separator for the receiver.
@property (null_resettable, copy) NSString *currencyGroupingSeparator API_AVAILABLE(macos(10.5), ios(2.0), watchos(2.0), tvos(9.0));
/// Determines whether the receiver will use heuristics to guess at the number which is intended by a string.
///
/// If the formatter is set to be lenient, as with any guessing it may get the result number wrong (that is,
/// a number other than that which was intended).
@property (getter=isLenient) BOOL lenient API_AVAILABLE(macos(10.5), ios(2.0), watchos(2.0), tvos(9.0));
/// A Boolean value indicating whether the formatter uses minimum and maximum significant digits when
/// formatting numbers.
///
/// The \c NSNumberFormatter class has two ways of determining how many digits to represent: using integer and
/// fraction digits and using significant digits.
///
/// When this property is set to \c NO, numbers are formatted according to whether you want them formatted as
/// fractions or as integers. This property is \c NO by default.
///
/// Set this property to \c YES to format numbers according to the significant digits configuration specified
/// by the \c minimumSignificantDigits and \c maximumSignificantDigits properties. By default, the minimum
/// number of significant digits is 1, and the maximum number of significant digits is 6.
///
/// When a number formatter is configured to use significant digits, it ignores any minimum or maximum values
/// used to set integer or fraction digits.
@property BOOL usesSignificantDigits API_AVAILABLE(macos(10.5), ios(2.0), watchos(2.0), tvos(9.0));
/// The minimum number of significant digits for the number formatter.
///
/// You must set the \c usesSignificantDigits property to \c YES in order for this property to affect
/// formatting behavior. By default, the minimum number of significant digits is 1.
@property NSUInteger minimumSignificantDigits API_AVAILABLE(macos(10.5), ios(2.0), watchos(2.0), tvos(9.0));
/// The maximum number of significant digits for the number formatter.
///
/// You must set the \c usesSignificantDigits property to \c YES in order for this property to affect
/// formatting behavior. By default, the maximum number of significant digits is 6. Values less than 1
/// are ignored.
@property NSUInteger maximumSignificantDigits API_AVAILABLE(macos(10.5), ios(2.0), watchos(2.0), tvos(9.0));
/// Determines whether partial string validation is enabled for the receiver.
@property (getter=isPartialStringValidationEnabled) BOOL partialStringValidationEnabled API_AVAILABLE(macos(10.5), ios(2.0), watchos(2.0), tvos(9.0));

@end

@class NSDecimalNumberHandler;

#if TARGET_OS_OSX
@interface NSNumberFormatter (NSNumberFormatterCompatibility)

/// Determines whether the receiver uses thousand separators.
@property BOOL hasThousandSeparators;
/// The character the receiver uses as a thousand separator.
///
/// If you don't have thousand separators enabled through any other means (such as \c format), using this
/// method enables them.
///
/// This method is for use with formatters using \c NSNumberFormatterBehavior10_0 behavior.
@property (null_resettable, copy) NSString *thousandSeparator;

/// Determines whether the dollar sign character (\c $), decimal separator character (\c .), and thousand
/// separator character (\c ,) are converted to appropriately localized characters as specified by the user's
/// localization preference.
///
/// While the currency-symbol part of this feature may be useful in certain types of applications, it's
/// probably more likely that you would tie a particular application to a particular currency (that is, that
/// you would "hard-code" the currency symbol and separators instead of having them dynamically change based
/// on the user's configuration). The reason for this, of course, is that \c NSNumberFormatter doesn't perform
/// currency conversions, it just formats numeric data. You wouldn't want one user interpreting the value
/// "56324" as US currency and another user who's accessing the same data interpreting it as Japanese currency,
/// simply based on each user's localization preferences.
@property BOOL localizesFormat;

/// The receiver's format.
///
/// The format string uses the format patterns from the Unicode Technical Standard #35. For more information,
/// see the Data Formatting Guide.
@property (copy) NSString *format;

/// The attributed string that the receiver uses to display zero values.
///
/// By default zero values are displayed according to the format specified for positive values.
///
/// This method is for use with formatters using \c NSNumberFormatterBehavior10_0 behavior.
@property (copy) NSAttributedString *attributedStringForZero;
/// The attributed string the receiver uses to display \c nil values.
///
/// By default \c nil values are displayed as an empty string.
///
/// This method is for use with formatters using \c NSNumberFormatterBehavior10_0 behavior.
@property (copy) NSAttributedString *attributedStringForNil;
/// The attributed string the receiver uses to display "not a number" values.
///
/// By default "not a number" values are displayed as the string "NaN".
///
/// This method is for use with formatters using \c NSNumberFormatterBehavior10_0 behavior.
@property (copy) NSAttributedString *attributedStringForNotANumber;

/// The rounding behavior used by the receiver.
@property (copy) NSDecimalNumberHandler *roundingBehavior;

@end
#endif

NS_HEADER_AUDIT_END(nullability, sendability)
