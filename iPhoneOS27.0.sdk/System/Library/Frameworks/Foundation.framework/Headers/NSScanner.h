/*	NSScanner.h
	Copyright (c) 1994-2019, Apple Inc. All rights reserved.
*/

#import <Foundation/NSObject.h>

@class NSString, NSCharacterSet, NSDictionary;

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

// Some of these API are deprecated in Swift only. They remain available in Objective-C.
#if defined(__swift__)
#define _NS_SCANNER_DEPRECATED_FOR_SWIFT_ONLY_WITH_REPLACEMENT(...) API_DEPRECATED_WITH_REPLACEMENT(__VA_ARGS__)
#else
#define _NS_SCANNER_DEPRECATED_FOR_SWIFT_ONLY_WITH_REPLACEMENT(...)
#endif

/// A string parser that scans for substrings or characters in a character set, and for numeric values from decimal, hexadecimal, and floating-point representations.
///
/// A ``Scanner`` object interprets and converts the characters of a <doc://com.apple.documentation/documentation/swift/string> into number and string values. You assign the scanner's string when you create the scanner, and the scanner progresses through the characters of that string from beginning to end as you request items.
///
/// Because of the nature of class clusters, a scanner object isn't an actual instance of the ``Scanner`` class, but is one of its private subclasses. Although a scanner object's class is private, its interface is public, as declared by this abstract superclass, ``Scanner``. The objects you create using this class are referred to as scanner objects (and when no confusion will result, merely as scanners).
///
/// To set a ``Scanner`` object to ignore a set of characters as it scans the string, use the ``charactersToBeSkipped`` property. Characters in the skip set are skipped over before the target is scanned. The default set of characters to skip is the whitespace and newline character set.
///
/// To retrieve the unscanned remainder of the string, use `scanner.string.substring(from: scanner.scanLocation)`.
@interface NSScanner : NSObject <NSCopying>

/// The string the scanner will scan.
@property (readonly, copy) NSString *string;

/// The character position at which the receiver will begin its next scanning operation.
///
/// Raises an `NSRangeException` if `index` is beyond the end of the string being scanned.
///
/// This property is useful for backing up to rescan after an error. Rather than setting the scan location directly to skip known sequences of characters, use -scanString:intoString: or -scanCharactersFromSet:intoString:, which allow you to verify that the expected substring (or set of characters) is in fact present.
@property NSUInteger scanLocation _NS_SCANNER_DEPRECATED_FOR_SWIFT_ONLY_WITH_REPLACEMENT("currentIndex", macos(10.0,10.15), ios(2.0,13.0), watchos(2.0,6.0), tvos(9.0,13.0));

/// Character set containing the characters the scanner ignores when looking for a scannable element.
///
/// Characters to be skipped are skipped prior to the scanner examining the target. For example, if a scanner ignores spaces and you send it a -scanInt: message, it skips spaces until it finds a decimal digit or other character. While an element is being scanned, no characters are skipped. If you scan for something made of characters in the set to be skipped (for example, using -scanInt: when the set of characters to be skipped is the decimal digits), the result is undefined.
///
/// The characters to be skipped are treated as single values. A scanner doesn't apply its case sensitivity setting to these characters and doesn't attempt to match composed character sequences with anything in the set of characters to be skipped (though it does match pre-composed characters individually). If you want to skip all vowels while scanning a string, for example, you can set the characters to be skipped to those in the string "AEIOUaeiou" (plus any accented variants with pre-composed characters).
///
/// The default set to skip is the whitespace and newline character set.
@property (nullable, copy) NSCharacterSet *charactersToBeSkipped;

/// Flag that indicates whether the receiver distinguishes case in the characters it scans.
///
/// `YES` if the receiver distinguishes case in the characters it scans, otherwise `NO`. The default value is `NO`. Note that case sensitivity doesn't apply to the characters to be skipped.
@property BOOL caseSensitive;

/// The locale to use when scanning.
///
/// A scanner's locale affects the way it interprets numeric values from the string. In particular, a scanner uses the locale's decimal separator to distinguish the integer and fractional parts of floating-point representations. A scanner with no locale set uses non-localized values. New scanners have no locale by default.
@property (nullable, retain) id locale;

/// Returns an `NSScanner` object initialized to scan a given string.
///
/// - Parameter string: The string to scan.
/// - Returns: An `NSScanner` object initialized to scan `aString` from the beginning.
- (instancetype)initWithString:(NSString *)string NS_DESIGNATED_INITIALIZER;

@end

@interface NSScanner (NSExtendedScanner)

// On overflow, the below methods will return success and clamp

/// Scans for an int value from a decimal representation, returning a found value by reference.
///
/// Skips past excess digits in the case of overflow, so the receiver's position is past the entire decimal representation.
///
/// Invoke this method with `NULL` as `intValue` to simply scan past a decimal integer representation.
///
/// - Parameter result: Upon return, contains the scanned value. Contains `INT_MAX` or `INT_MIN` on overflow.
/// - Returns: `YES` if the receiver finds a valid decimal integer representation, otherwise `NO`. Overflow is considered a valid integer representation.
- (BOOL)scanInt:(nullable int *)result _NS_SCANNER_DEPRECATED_FOR_SWIFT_ONLY_WITH_REPLACEMENT("scanInt()", macos(10.0,10.15), ios(2.0,13.0), watchos(2.0,6.0), tvos(9.0,13.0));

/// Scans for an NSInteger value from a decimal representation, returning a found value by reference.
///
/// Skips past excess digits in the case of overflow, so the receiver's position is past the entire integer representation.
///
/// Invoke this method with `NULL` as `value` to simply scan past a decimal integer representation.
///
/// - Parameter result: Upon return, contains the scanned value. Contains `INT_MAX` or `INT_MIN` on overflow.
/// - Returns: `YES` if the receiver finds a valid integer representation, otherwise `NO`. Overflow is considered a valid integer representation.
- (BOOL)scanInteger:(nullable NSInteger *)result API_AVAILABLE(macos(10.5), ios(2.0), watchos(2.0), tvos(9.0)) _NS_SCANNER_DEPRECATED_FOR_SWIFT_ONLY_WITH_REPLACEMENT("scanInt()", macos(10.5,10.15), ios(2.0,13.0), watchos(2.0,6.0), tvos(9.0,13.0));

/// Scans for a long long value from a decimal representation, returning a found value by reference.
///
/// All overflow digits are skipped. Skips past excess digits in the case of overflow, so the receiver's position is past the entire decimal representation.
///
/// Invoke this method with `NULL` as `longLongValue` to simply scan past a long decimal integer representation.
///
/// - Parameter result: Upon return, contains the scanned value. Contains `LLONG_MAX` or `LLONG_MIN` on overflow.
/// - Returns: `YES` if the receiver finds a valid decimal integer representation, otherwise `NO`. Overflow is considered a valid decimal integer representation.
- (BOOL)scanLongLong:(nullable long long *)result;

/// Scans for an unsigned long long value from a decimal representation, returning a found value by reference.
///
/// All overflow digits are skipped. Skips past excess digits in the case of overflow, so the receiver's position is past the entire decimal representation.
///
/// Invoke this method with `NULL` as `unsignedLongLongValue` to simply scan past an unsigned long decimal integer representation.
///
/// - Parameter result: Upon return, contains the scanned value. Contains `ULLONG_MAX` on overflow.
/// - Returns: `YES` if the receiver finds a valid decimal integer representation, otherwise `NO`. Overflow is considered a valid decimal integer representation.
- (BOOL)scanUnsignedLongLong:(nullable unsigned long long *)result API_AVAILABLE(macos(10.9), ios(7.0), watchos(2.0), tvos(9.0)) _NS_SCANNER_DEPRECATED_FOR_SWIFT_ONLY_WITH_REPLACEMENT("scanUnsignedLongLong()", macos(10.9,10.15), ios(7.0,13.0), watchos(2.0,6.0), tvos(9.0,13.0));

/// Scans for a float value, returning a found value by reference.
///
/// Skips past excess digits in the case of overflow, so the scanner's position is past the entire floating-point representation.
///
/// Invoke this method with `NULL` as `floatValue` to simply scan past a float value representation. Floating-point representations are assumed to be IEEE compliant.
///
/// - Parameter result: Upon return, contains the scanned value. Contains `HUGE_VAL` or `-HUGE_VAL` on overflow, or `0.0` on underflow.
/// - Returns: `YES` if the receiver finds a valid floating-point representation, otherwise `NO`. Overflow or underflow are both considered valid floating-point representations.
- (BOOL)scanFloat:(nullable float *)result _NS_SCANNER_DEPRECATED_FOR_SWIFT_ONLY_WITH_REPLACEMENT("scanFloat()", macos(10.0,10.15), ios(2.0,13.0), watchos(2.0,6.0), tvos(9.0,13.0));

/// Scans for a double value, returning a found value by reference.
///
/// Skips past excess digits in the case of overflow, so the scanner's position is past the entire floating-point representation.
///
/// Invoke this method with `NULL` as `doubleValue` to simply scan past a double value representation. Floating-point representations are assumed to be IEEE compliant.
///
/// - Parameter result: Upon return, contains the scanned value. Contains `HUGE_VAL` or `-HUGE_VAL` on overflow, or `0.0` on underflow.
/// - Returns: `YES` if the receiver finds a valid floating-point representation, otherwise `NO`. Overflow or underflow are both considered valid floating-point representations.
- (BOOL)scanDouble:(nullable double *)result _NS_SCANNER_DEPRECATED_FOR_SWIFT_ONLY_WITH_REPLACEMENT("scanDouble()", macos(10.0,10.15), ios(2.0,13.0), watchos(2.0,6.0), tvos(9.0,13.0));

/// Scans for an unsigned value from a hexadecimal representation, returning a found value by reference.
///
/// The hexadecimal integer representation may optionally be preceded by `0x` or `0X`. Skips past excess digits in the case of overflow, so the receiver's position is past the entire hexadecimal representation.
///
/// Invoke this method with `NULL` as `intValue` to simply scan past a hexadecimal integer representation.
///
/// - Parameter result: Upon return, contains the scanned value. Contains `UINT_MAX` on overflow.
/// - Returns: `YES` if the receiver finds a valid hexadecimal integer representation, otherwise `NO`. Overflow is considered a valid hexadecimal integer representation.
- (BOOL)scanHexInt:(nullable unsigned *)result                                                                                 // Optionally prefixed with "0x" or "0X"
    _NS_SCANNER_DEPRECATED_FOR_SWIFT_ONLY_WITH_REPLACEMENT("scanHexInt()", macos(10.0,10.15), ios(2.0,13.0), watchos(2.0,6.0), tvos(9.0,13.0));

/// Scans for a long long value from a hexadecimal representation, returning a found value by reference.
///
/// The hexadecimal integer representation may optionally be preceded by `0x` or `0X`. Skips past excess digits in the case of overflow, so the receiver's position is past the entire hexadecimal representation.
///
/// Invoke this method with `NULL` as `result` to simply scan past a hexadecimal long long representation.
///
/// - Parameter result: Upon return, contains the scanned value. Contains `HUGE_VAL` or `-HUGE_VAL` on overflow.
/// - Returns: `YES` if the receiver finds a valid hexadecimal long long representation, otherwise `NO`. Overflow is considered a valid hexadecimal long long representation.
- (BOOL)scanHexLongLong:(nullable unsigned long long *)result API_AVAILABLE(macos(10.5), ios(2.0), watchos(2.0), tvos(9.0))    // Optionally prefixed with "0x" or "0X"
    _NS_SCANNER_DEPRECATED_FOR_SWIFT_ONLY_WITH_REPLACEMENT("scanHexLongLong()", macos(10.5,10.15), ios(2.0,13.0), watchos(2.0,6.0), tvos(9.0,13.0));

/// Scans for a double value from a hexadecimal representation, returning a found value by reference.
///
/// This corresponds to `%a` or `%A` formatting. The hexadecimal float representation must be preceded by `0x` or `0X`.
///
/// Skips past excess digits in the case of overflow, so the scanner's position is past the entire floating-point representation.
///
/// Invoke this method with `NULL` as `result` to simply scan past a hexadecimal float representation.
///
/// - Parameter result: Upon return, contains the scanned value. Contains `HUGE_VAL` or `-HUGE_VAL` on overflow, or `0.0` on underflow.
/// - Returns: `YES` if the receiver finds a valid float-point representation, otherwise `NO`. Overflow or underflow are both considered valid floating-point representations.
- (BOOL)scanHexFloat:(nullable float *)result API_AVAILABLE(macos(10.5), ios(2.0), watchos(2.0), tvos(9.0))                    // Corresponding to %a or %A formatting. Requires "0x" or "0X" prefix.
    _NS_SCANNER_DEPRECATED_FOR_SWIFT_ONLY_WITH_REPLACEMENT("scanHexFloat()", macos(10.5,10.15), ios(2.0,13.0), watchos(2.0,6.0), tvos(9.0,13.0));

/// Scans for a double value from a hexadecimal representation, returning a found value by reference.
///
/// This corresponds to `%a` or `%A` formatting. The hexadecimal double representation must be preceded by `0x` or `0X`.
///
/// Skips past excess digits in the case of overflow, so the scanner's position is past the entire floating-point representation.
///
/// Invoke this method with `NULL` as `result` to simply scan past a hexadecimal double representation.
///
/// - Parameter result: Upon return, contains the scanned value. Contains `HUGE_VAL` or `-HUGE_VAL` on overflow, or `0.0` on underflow.
/// - Returns: `YES` if the receiver finds a valid double-point representation, otherwise `NO`. Overflow or underflow are both considered valid floating-point representations.
- (BOOL)scanHexDouble:(nullable double *)result API_AVAILABLE(macos(10.5), ios(2.0), watchos(2.0), tvos(9.0))                  // Corresponding to %a or %A formatting. Requires "0x" or "0X" prefix.
    _NS_SCANNER_DEPRECATED_FOR_SWIFT_ONLY_WITH_REPLACEMENT("scanHexDouble()", macos(10.5,10.15), ios(2.0,13.0), watchos(2.0,6.0), tvos(9.0,13.0));

/// Scans a given string, returning an equivalent string object by reference if a match is found.
///
/// If `string` is present at the current scan location, then the current scan location is advanced to after the string; otherwise the scan location does not change.
///
/// Invoke this method with `NULL` as `stringValue` to simply scan past a given string.
///
/// - Parameters:
///   - string: The string for which to scan at the current scan location.
///   - result: Upon return, if the receiver contains a string equivalent to `string` at the current scan location, contains a string equivalent to `string`.
/// - Returns: `YES` if `string` matches the characters at the scan location, otherwise `NO`.
- (BOOL)scanString:(NSString *)string intoString:(NSString * _Nullable * _Nullable)result _NS_SCANNER_DEPRECATED_FOR_SWIFT_ONLY_WITH_REPLACEMENT("scanString(_:)", macos(10.0,10.15), ios(2.0,13.0), watchos(2.0,6.0), tvos(9.0,13.0));

/// Scans the string as long as characters from a given character set are encountered, accumulating characters into a string that's returned by reference.
///
/// Invoke this method with `NULL` as `stringValue` to simply scan past a given set of characters.
///
/// - Parameters:
///   - set: The set of characters to scan.
///   - result: Upon return, contains the characters scanned.
/// - Returns: `YES` if the receiver scanned any characters, otherwise `NO`.
- (BOOL)scanCharactersFromSet:(NSCharacterSet *)set intoString:(NSString * _Nullable * _Nullable)result _NS_SCANNER_DEPRECATED_FOR_SWIFT_ONLY_WITH_REPLACEMENT("scanCharacters(from:)", macos(10.0,10.15), ios(2.0,13.0), watchos(2.0,6.0), tvos(9.0,13.0));

/// Scans the string until a given string is encountered, accumulating characters into a string that's returned by reference.
///
/// If `stopString` is present in the receiver, then on return the scan location is set to the beginning of that string. If `stopString` is the first string in the receiver, then the method returns `NO` and `stringValue` is not changed.
///
/// If the search string (`stopString`) isn't present in the scanner's source string, the remainder of the source string is put into `stringValue`, the receiver's `scanLocation` is advanced to the end of the source string, and the method returns `YES`.
///
/// Invoke this method with `NULL` as `stringValue` to simply scan up to a given string.
///
/// - Parameters:
///   - string: The string to scan up to.
///   - result: Upon return, contains any characters that were scanned.
/// - Returns: `YES` if the receiver scans any characters, otherwise `NO`. If the only scanned characters are in the `charactersToBeSkipped` character set (which by default is the whitespace and newline character set), then this method returns `NO`.
- (BOOL)scanUpToString:(NSString *)string intoString:(NSString * _Nullable * _Nullable)result _NS_SCANNER_DEPRECATED_FOR_SWIFT_ONLY_WITH_REPLACEMENT("scanUpTo(_:)", macos(10.0,10.15), ios(2.0,13.0), watchos(2.0,6.0), tvos(9.0,13.0));

/// Scans the string until a character from a given character set is encountered, accumulating characters into a string that's returned by reference.
///
/// Invoke this method with `NULL` as `stringValue` to simply scan up to a given set of characters.
///
/// If no characters in `stopSet` are present in the scanner's source string, the remainder of the source string is put into `stringValue`, the receiver's `scanLocation` is advanced to the end of the source string, and the method returns `YES`.
///
/// - Parameters:
///   - set: The set of characters up to which to scan.
///   - result: Upon return, contains the characters scanned.
/// - Returns: `YES` if the receiver scanned any characters, otherwise `NO`. If the only scanned characters are in the `charactersToBeSkipped` character set (which is the whitespace and newline character set by default), then returns `NO`.
- (BOOL)scanUpToCharactersFromSet:(NSCharacterSet *)set intoString:(NSString * _Nullable * _Nullable)result _NS_SCANNER_DEPRECATED_FOR_SWIFT_ONLY_WITH_REPLACEMENT("scanUpToCharacters(from:)", macos(10.0,10.15), ios(2.0,13.0), watchos(2.0,6.0), tvos(9.0,13.0));

/// Flag that indicates whether the receiver has exhausted all significant characters.
///
/// `YES` if the receiver has exhausted all significant characters in its string, otherwise `NO`. If only characters from the set to be skipped remain, returns `YES`.
@property (getter=isAtEnd, readonly) BOOL atEnd;

/// Returns an `NSScanner` object that scans a given string.
+ (instancetype)scannerWithString:(NSString *)string;

/// Returns an `NSScanner` object that scans a given string according to the user's default locale.
///
/// Sets the string to scan by invoking -initWithString: with `aString`. The locale is set with the user's default locale.
///
/// - Parameter string: The string to scan.
/// - Returns: An `NSScanner` object that scans `aString` according to the user's default locale.
+ (id)localizedScannerWithString:(NSString *)string;

@end

NS_HEADER_AUDIT_END(nullability, sendability)
