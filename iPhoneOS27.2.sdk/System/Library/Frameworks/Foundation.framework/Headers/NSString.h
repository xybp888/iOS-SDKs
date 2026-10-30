/*	NSString.h
	Copyright (c) 1994-2019, Apple Inc. All rights reserved.
*/

/*
 An NSString object encodes a Unicode-compliant text string, represented as a sequence of UTF–16 code units. All lengths, character indexes, and ranges are expressed in terms of UTF–16 code units, with index values starting at 0.  The length property of an NSString returns the number of UTF-16 code units in an NSString, and the characterAtIndex: method retrieves a specific UTF-16 code unit. These two "primitive" methods provide basic access to the contents of a string object.
 
 Most use of strings, however, is at a higher level, with the strings being treated as single entities: Using the APIs in NSString, you can compare strings against one another, search them for substrings, combine them into new strings, and so on. In cases where locale settings may make a difference, use the localized... API variants to perform the operations using the current user's locale, or use the locale: variants that take an explicit NSLocale argument.
 
 If you do need to access individual characters in a string, you need to consider whether you want to access the individual UTF-16 code points (referred to as "characters" in APIs, and represented with the "unichar" type), or human-readable characters (referred to as "composed character sequences" or "grapheme clusters").  Composed character sequences can span multiple UTF-16 characters, when representing a base letter plus an accent, for example, or Emoji.
 
 To access composed character sequences, use APIs such as rangeOfComposedCharacterSequenceAtIndex:, or enumerate the whole or part of the string with enumerateSubstringsInRange:options:usingBlock:, supplying NSStringEnumerationByComposedCharacterSequences as the enumeration option.
 
 For instance, to extract the composed character sequence at a given index (where index is a valid location in the string, 0..length-1):
 
     NSString *substr = [string substringWithRange:[string rangeOfComposedCharacterSequenceAtIndex:index]];
 
 And to enumerate composed character sequences in a string:
 
     [string enumerateSubstringsInRange:NSMakeRange(0, string.length)                      // enumerate the whole range of the string
                                options:NSStringEnumerationByComposedCharacterSequences    // by composed character sequences
                             usingBlock:^(NSString * substr, NSRange substrRange, NSRange enclosingRange, BOOL *stop) {
          ... use substr, whose range in string is substrRange ...
     }];
 
 NSStrings can be immutable or mutable. The contents of an immutable string is defined when it is created and subsequently cannot be changed.  To construct and manage a string that can be changed after it has been created, use NSMutableString, which is a subclass of NSString.
 
 An NSString object can be initialized using a number of ways: From a traditional (char *) C-string, a sequence of bytes, an NSData object, the contents of an NSURL, etc, with the character contents specified in a variety of string encodings, such as ASCII, ISOLatin1, UTF–8, UTF–16, etc.
*/

/* The unichar type represents a single UTF-16 code unit in an NSString. Although many human-readable characters are representable with a single unichar, some  such as Emoji may span multiple unichars. See discussion above.
*/
typedef unsigned short unichar;

#import <limits.h>
#import <Foundation/NSObject.h>
#import <Foundation/NSRange.h>
#if !0
#import <Foundation/NSItemProvider.h>
#endif
#import <stdarg.h>

@class NSData, NSArray<ObjectType>, NSDictionary<KeyType, ObjectType>, NSCharacterSet, NSURL, NSError, NSLocale;

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

/// These options apply to the various search/find and comparison methods (except where noted).
typedef NS_OPTIONS(NSUInteger, NSStringCompareOptions) {
    /// A case-insensitive search.
    NSCaseInsensitiveSearch = 1,
    /// Exact character-by-character equivalence.
    NSLiteralSearch = 2,
    /// Search from end of source string.
    NSBackwardsSearch = 4,
    /// Search is limited to start (or end, if `NSBackwardsSearch`) of source string.
    NSAnchoredSearch = 8,
    /// Numbers within strings are compared using numeric value, that is, `Name2.txt` < `Name7.txt` < `Name25.txt`.
    ///
    /// Numeric comparison only applies to the numerals in the string, not other characters that would have meaning in a numeric representation such as a negative sign, a comma, or a decimal point. This option only applies to compare methods, not find.
    NSNumericSearch = 64,
    /// Search ignores diacritic marks.
    ///
    /// For example, 'o' is equal to 'o'.
    NSDiacriticInsensitiveSearch API_AVAILABLE(macos(10.5), ios(2.0), watchos(2.0), tvos(9.0)) = 128,
    /// Search ignores width differences in characters that have full-width and half-width forms, as occurs in East Asian character sets.
    ///
    /// For example, with this option, the full-width Latin small letter 'a' (`U+FF41`) is equal to the basic Latin small letter 'a' (`U+0061`).
    NSWidthInsensitiveSearch API_AVAILABLE(macos(10.5), ios(2.0), watchos(2.0), tvos(9.0)) = 256,
    /// Comparisons are forced to return either `NSOrderedAscending` or `NSOrderedDescending` if the strings are equivalent but not strictly equal.
    ///
    /// This option ensures reliable, reproducible results when sorting. For example, "aaa" is greater than "AAA" if `NSCaseInsensitiveSearch` is specified.
    NSForcedOrderingSearch API_AVAILABLE(macos(10.5), ios(2.0), watchos(2.0), tvos(9.0)) = 512,
#if !0
    /// The search string is treated as an ICU-compatible regular expression.
    ///
    /// If set, no other options can apply except `NSCaseInsensitiveSearch` and `NSAnchoredSearch`. You can use this option only with the `rangeOfString:` methods and `stringByReplacingOccurrencesOfString:withString:options:range:`.
    NSRegularExpressionSearch API_AVAILABLE(macos(10.7), ios(3.2), watchos(2.0), tvos(9.0)) = 1024
#endif
};

/// The type for string encoding values.
///
/// In addition to the values explicitly listed below, `NSStringEncoding` supports encodings provided by CFString. See `CFStringEncodingExt.h` for a list of these encodings and `CFString.h` for functions which convert between `NSStringEncoding` and `CFStringEncoding`.
typedef NSUInteger NSStringEncoding;
NS_ENUM(NSStringEncoding) {
    /// Strict 7-bit ASCII encoding within 8-bit chars; ASCII values 0…127 only.
    NSASCIIStringEncoding = 1,
    /// 8-bit ASCII encoding with NEXTSTEP extensions.
    NSNEXTSTEPStringEncoding = 2,
    /// 8-bit EUC encoding for Japanese text.
    NSJapaneseEUCStringEncoding = 3,
    /// An 8-bit representation of Unicode characters, suitable for transmission or storage by ASCII-based systems.
    NSUTF8StringEncoding = 4,
    /// 8-bit ISO Latin 1 encoding.
    NSISOLatin1StringEncoding = 5,
    /// 8-bit Adobe Symbol encoding vector.
    NSSymbolStringEncoding = 6,
    /// 7-bit verbose ASCII to represent all Unicode characters.
    NSNonLossyASCIIStringEncoding = 7,
    /// 8-bit Shift-JIS encoding for Japanese text.
    NSShiftJISStringEncoding = 8,
    /// 8-bit ISO Latin 2 encoding.
    NSISOLatin2StringEncoding = 9,
    /// The canonical Unicode encoding for string objects.
    NSUnicodeStringEncoding = 10,
    /// Microsoft Windows codepage 1251, encoding Cyrillic characters.
    NSWindowsCP1251StringEncoding = 11,
    /// Microsoft Windows codepage 1252; equivalent to WinLatin1.
    NSWindowsCP1252StringEncoding = 12,
    /// Microsoft Windows codepage 1253, encoding Greek characters.
    NSWindowsCP1253StringEncoding = 13,
    /// Microsoft Windows codepage 1254, encoding Turkish characters.
    NSWindowsCP1254StringEncoding = 14,
    /// Microsoft Windows codepage 1250; equivalent to WinLatin2.
    NSWindowsCP1250StringEncoding = 15,
    /// ISO 2022 Japanese encoding for electronic mail.
    NSISO2022JPStringEncoding = 21,
    /// Classic Macintosh Roman encoding.
    NSMacOSRomanStringEncoding = 30,

    /// An alias for ``NSUnicodeStringEncoding``.
    NSUTF16StringEncoding = NSUnicodeStringEncoding,

    /// ``NSUTF16StringEncoding`` encoding with explicit big-endian byte order.
    NSUTF16BigEndianStringEncoding = 0x90000100,
    /// ``NSUTF16StringEncoding`` encoding with explicit little-endian byte order.
    NSUTF16LittleEndianStringEncoding = 0x94000100,

    /// 32-bit UTF encoding.
    NSUTF32StringEncoding = 0x8c000100,
    /// ``NSUTF32StringEncoding`` encoding with explicit big-endian byte order.
    NSUTF32BigEndianStringEncoding = 0x98000100,
    /// ``NSUTF32StringEncoding`` encoding with explicit little-endian byte order.
    NSUTF32LittleEndianStringEncoding = 0x9c000100
};

/// Options for converting string encodings.
typedef NS_OPTIONS(NSUInteger, NSStringEncodingConversionOptions) {
    /// Allows lossy conversion.
    NSStringEncodingConversionAllowLossy = 1,
    /// Specifies an external representation (with a byte-order mark, if necessary, to indicate endianness).
    NSStringEncodingConversionExternalRepresentation = 2
};


/// A static, plain-text Unicode string object.
///
/// You can use this type in Swift when you need reference semantics or other Foundation-specific behavior.
///
/// The ``NSString`` class and its mutable subclass, ``NSMutableString``, provide an extensive set of APIs for working with strings, including methods for comparing, searching, and modifying strings. ``NSString`` objects are used throughout Foundation and other Cocoa frameworks, serving as the basis for all textual and linguistic functionality on the platform.
///
/// ``NSString`` is _toll-free bridged_ with its Core Foundation counterpart, <doc://com.apple.documentation/documentation/corefoundation/cfstring>. See [Toll-Free Bridging](https://developer.apple.com/library/archive/documentation/General/Conceptual/CocoaEncyclopedia/Toll-FreeBridgin/Toll-FreeBridgin.html#//apple_ref/doc/uid/TP40010810-CH2) for more information.
///
/// ### String Objects
///
/// An ``NSString`` object encodes a Unicode-compliant text string, represented as a sequence of UTF–16 code units. All lengths, character indexes, and ranges are expressed in terms of 16-bit platform-endian values, with index values starting at `0`.
///
/// An ``NSString`` object can be initialized from or written to a C buffer, an ``NSData`` object, or the contents of an ``NSURL``. It can also be encoded and decoded to and from ASCII, UTF–8, UTF–16, UTF–32, or any other string encoding represented by ``NSStringEncoding``.
///
/// > Note:
/// > An immutable string is a text string that is defined when it is created and subsequently cannot be changed. An immutable string is implemented as an array of UTF–16 code units (in other words, a text string). To create and manage an immutable string, use the ``NSString`` class. To construct and manage a string that can be changed after it has been created, use ``NSMutableString``.
///
/// The objects you create using ``NSString`` and ``NSMutableString`` are referred to as string objects (or, when no confusion will result, merely as strings). The term C string refers to the standard `char *` type.
///
/// Because of the nature of class clusters, string objects aren't actual instances of the ``NSString`` or ``NSMutableString`` classes but of one of their private subclasses. Although a string object's class is private, its interface is public, as declared by these abstract superclasses, ``NSString`` and ``NSMutableString``. The string classes adopt the ``NSCopying`` and ``NSMutableCopying`` protocols, making it convenient to convert a string of one type to the other.
///
/// #### Understanding Characters
///
/// A string object presents itself as a sequence of UTF–16 code units. You can determine how many UTF-16 code units a string object contains with the ``length`` method and can retrieve a specific UTF-16 code unit with the ``character(at:)`` method. These two "primitive" methods provide basic access to a string object.
///
/// Most use of strings, however, is at a higher level, with the strings being treated as single entities: You compare strings against one another, search them for substrings, combine them into new strings, and so on. If you need to access string objects character by character, you must understand the Unicode character encoding, specifically issues related to composed character sequences. For details see _The Unicode Standard, Version 4.0_ (The Unicode Consortium, Boston: Addison-Wesley, 2003, ISBN 0-321-18578-1) and the Unicode Consortium web site: [http://www.unicode.org/](http://www.unicode.org/). See also [Characters and Grapheme Clusters](https://developer.apple.com/library/archive/documentation/Cocoa/Conceptual/Strings/Articles/stringsClusters.html#//apple_ref/doc/uid/TP40008025) in [String Programming Guide](https://developer.apple.com/library/archive/documentation/Cocoa/Conceptual/Strings/introStrings.html#//apple_ref/doc/uid/10000035i).
///
/// Localized string comparisons are based on the Unicode Collation Algorithm, as tailored for different languages by CLDR (Common Locale Data Repository). Both are projects of the Unicode Consortium. Unicode is a registered trademark of Unicode, Inc.
///
/// #### Interpreting UTF-16-Encoded Data
///
/// When creating an `NSString` object from a UTF-16-encoded string (or a byte stream interpreted as UTF-16), if the byte order is not otherwise specified, `NSString` assumes that the UTF-16 characters are big-endian, unless there is a BOM (byte-order mark), in which case the BOM dictates the byte order. When creating an `NSString` object from an array of `unichar` values, the returned string is always native-endian, since the array always contains UTF–16 code units in native byte order.
///
/// ### Subclassing Notes
///
/// It is possible to subclass ``NSString`` (and ``NSMutableString``), but doing so requires providing storage facilities for the string (which is not inherited by subclasses) and implementing two primitive methods. The abstract ``NSString`` and ``NSMutableString`` classes are the public interface of a class cluster consisting mostly of private, concrete classes that create and return a string object appropriate for a given situation. Making your own concrete subclass of this cluster imposes certain requirements (discussed in <doc:#Methods-to-Override>).
///
/// Make sure your reasons for subclassing ``NSString`` are valid. Instances of your subclass should represent a string and not something else. Thus the only attributes the subclass should have are the length of the character buffer it's managing and access to individual characters in the buffer. Valid reasons for making a subclass of ``NSString`` include providing a different backing store (perhaps for better performance) or implementing some aspect of object behavior differently, such as memory management. If your purpose is to add non-essential attributes or metadata to your subclass of ``NSString``, a better alternative would be object composition (see <doc:#Alternatives-to-Subclassing>). Cocoa already provides an example of this with the ``NSAttributedString`` class.
///
/// #### Methods to Override
///
/// Any subclass of `NSString`   _must_ override the primitive instance methods ``length`` and ``character(at:)``. These methods must operate on the backing store that you provide for the characters of the string. For this backing store you can use a static array, a dynamically allocated buffer, a standard `NSString` object, or some other data type or mechanism. You may also choose to override, partially or fully, any other `NSString` method for which you want to provide an alternative implementation. For example, for better performance it is recommended that you override ``getCharacters(_:range:)`` and give it a faster implementation.
///
/// You might want to implement an initializer for your subclass that is suited to the backing store that the subclass is managing. The `NSString` class does not have a designated initializer, so your initializer need only invoke the <doc://com.apple.documentation/documentation/objectivec/nsobject-swift.class/init()> method of `super`. The `NSString` class adopts the ``NSCopying``, ``NSMutableCopying``, and ``NSCoding`` protocols; if you want instances of your own custom subclass created from copying or coding, override the methods in these protocols.
///
/// #### Alternatives to Subclassing
///
/// Often a better and easier alternative to making a subclass of `NSString`—or of any other abstract, public class of a class cluster, for that matter—is object composition. This is especially the case when your intent is to add to the subclass metadata or some other attribute that is not essential to a string object. In object composition, you would have an `NSString` object as one instance variable of your custom class (typically a subclass of `NSObject`) and one or more instance variables that store the metadata that you want for the custom object. Then just design your subclass interface to include accessor methods for the embedded string object and the metadata.
///
/// If the behavior you want to add supplements that of the existing class, you could write a category on `NSString`. Keep in mind, however, that this category will be in effect for all instances of `NSString` that you use, and this might have unintended consequences.
@interface NSString : NSObject <NSCopying, NSMutableCopying, NSSecureCoding>

#pragma mark *** String funnel methods ***

/* NSString primitives. A minimal subclass of NSString just needs to implement these two, along with an init method appropriate for that subclass. We also recommend overriding getCharacters:range: for performance.
 */

/// The number of UTF-16 code units in the receiver.
///
/// This number includes the individual characters of composed character sequences, so you cannot use this property to determine if a string will be visible when printed or how long it will appear.
@property (readonly) NSUInteger length;

/// Returns the character at a given UTF-16 code unit index.
///
/// @param index The index of the character to retrieve. Raises an `NSRangeException` if @c index lies beyond the end of the receiver.
/// @return The character at the array position given by @c index.
///
/// You should always use the @c rangeOfComposedCharacterSequenceAtIndex: or
/// @c rangeOfComposedCharacterSequencesForRange: method to determine character boundaries,
/// so that any surrogate pairs or character clusters are handled correctly.
- (unichar)characterAtIndex:(NSUInteger)index;

/* The initializers available to subclasses. See further below for additional init methods.
*/

/// Returns an initialized @c NSString object that contains no characters.
///
/// @return An initialized @c NSString object that contains no characters. The returned object may be different from the original receiver.
- (instancetype)init NS_DESIGNATED_INITIALIZER;
- (nullable instancetype)initWithCoder:(NSCoder *)coder NS_DESIGNATED_INITIALIZER;
@end

@interface NSString (NSStringExtensionMethods)

#pragma mark *** Substrings ***

/* To avoid breaking up character sequences such as Emoji, you can do:
    [str substringFromIndex:[str rangeOfComposedCharacterSequenceAtIndex:index].location]
    [str substringToIndex:NSMaxRange([str rangeOfComposedCharacterSequenceAtIndex:index])]
    [str substringWithRange:[str rangeOfComposedCharacterSequencesForRange:range]
*/

/// Returns a new string containing the characters of the receiver from the one at a given index to the end.
///
/// @param from An index. The value must lie within the bounds of the receiver, or be equal to the length of the receiver.
///   Raises an @c NSRangeException if (@c anIndex - 1) lies beyond the end of the receiver.
/// @return A new string containing the characters of the receiver from the one at @c anIndex to the end.
///   If @c anIndex is equal to the length of the string, returns an empty string.
- (NSString *)substringFromIndex:(NSUInteger)from;

/// Returns a new string containing the characters of the receiver up to, but not including, the one at a given index.
///
/// @param to An index. The value must lie within the bounds of the receiver, or be equal to the length of the receiver.
///   Raises an @c NSRangeException if (@c anIndex - 1) lies beyond the end of the receiver.
/// @return A new string containing the characters of the receiver up to, but not including, the one at @c anIndex.
///   If @c anIndex is equal to the length of the string, returns a copy of the receiver.
- (NSString *)substringToIndex:(NSUInteger)to;

/// Returns a string object containing the characters of the receiver that lie within a given range.
///
/// @param range A range. The range must not exceed the bounds of the receiver.
///   Raises an @c NSRangeException if any part of @c range lies beyond the bounds of the receiver.
/// @return A string object containing the characters of the receiver that lie within @c aRange.
- (NSString *)substringWithRange:(NSRange)range;                // Use with rangeOfComposedCharacterSequencesForRange: to avoid breaking up character sequences

/// Copies characters from a given range in the receiver into a given buffer.
///
/// @param buffer Upon return, contains the characters from the receiver. @c buffer must be large enough
///   to contain the characters in the range @c aRange (@c aRange.length*sizeof(unichar)). This method does not add a @c NULL character.
/// @param range The range of characters to retrieve. The range must not exceed the bounds of the receiver.
///   Raises an @c NSRangeException if any part of @c aRange lies beyond the bounds of the receiver.
- (void)getCharacters:(unichar *)buffer range:(NSRange)range;   // Use with rangeOfComposedCharacterSequencesForRange: to avoid breaking up character sequences


#pragma mark *** String comparison and equality ***

/* In the compare: methods, the range argument specifies the subrange, rather than the whole, of the receiver to use in the comparison. The range is not applied to the search string.  For example, [@"AB" compare:@"ABC" options:0 range:NSMakeRange(0,1)] compares "A" to "ABC", not "A" to "A", and will return NSOrderedAscending. It is an error to specify a range that is outside of the receiver's bounds, and an exception may be raised.
*/

/// Returns the result of invoking @c compare:options:range: with no options and the receiver's full extent as the range.
///
/// @param string The string with which to compare the receiver. This value must not be @c nil.
/// @return The lexical ordering. @c NSOrderedAscending if the receiver precedes @c aString in lexical ordering,
///   @c NSOrderedSame if the receiver and @c aString are equivalent in lexical value,
///   and @c NSOrderedDescending if the receiver follows @c aString.
- (NSComparisonResult)compare:(NSString *)string;

/// Compares the string with the specified string using the given options.
///
/// @param string The string with which to compare the receiver. This value must not be @c nil.
/// @param mask Options for the search---you can combine any of the following using a C bitwise OR operator:
///   @c NSCaseInsensitiveSearch, @c NSLiteralSearch, @c NSNumericSearch.
/// @return The lexical ordering.
- (NSComparisonResult)compare:(NSString *)string options:(NSStringCompareOptions)mask;

/// Returns the result of invoking @c compare:options:range:locale: with a @c nil locale.
///
/// @param string The string with which to compare the range of the receiver specified by @c range. This value must not be @c nil.
/// @param mask Options for the search.
/// @param rangeOfReceiverToCompare The range of the receiver over which to perform the comparison. The range must not exceed the bounds of the receiver.
/// @return The lexical ordering.
- (NSComparisonResult)compare:(NSString *)string options:(NSStringCompareOptions)mask range:(NSRange)rangeOfReceiverToCompare;

/// Compares the string using the specified options and returns the lexical ordering for the range.
///
/// @param string The string with which to compare the range of the receiver. This value must not be @c nil.
/// @param mask Options for the search.
/// @param rangeOfReceiverToCompare The range of the receiver over which to perform the comparison. The range must not exceed the bounds of the receiver.
/// @param locale An instance of @c NSLocale. To use the current locale, pass @c [NSLocale currentLocale].
///   To use the system locale, pass @c nil.
/// @return The lexical ordering.
- (NSComparisonResult)compare:(NSString *)string options:(NSStringCompareOptions)mask range:(NSRange)rangeOfReceiverToCompare locale:(nullable id)locale; // locale arg used to be a dictionary pre-Leopard. We now accept NSLocale. Assumes the current locale if non-nil and non-NSLocale. nil continues to mean canonical compare, which doesn't depend on user's locale choice.

/// Returns the result of invoking @c compare:options: with @c NSCaseInsensitiveSearch as the only option.
///
/// @param string The string with which to compare the receiver.
/// @return The lexical ordering.
- (NSComparisonResult)caseInsensitiveCompare:(NSString *)string;

/// Compares the string and a given string using a localized comparison.
///
/// @param string The string with which to compare the receiver. This value must not be @c nil.
/// @return The lexical ordering. This method uses the current locale.
- (NSComparisonResult)localizedCompare:(NSString *)string;

/// Compares the string with a given string using a case-insensitive, localized, comparison.
///
/// @param string The string with which to compare the receiver. This value must not be @c nil.
/// @return The lexical ordering. This method uses the current locale.
- (NSComparisonResult)localizedCaseInsensitiveCompare:(NSString *)string;

/* localizedStandardCompare:, added in 10.6, should be used whenever file names or other strings are presented in lists and tables where Finder-like sorting is appropriate.  The exact behavior of this method may be tweaked in future releases, and will be different under different localizations, so clients should not depend on the exact sorting order of the strings.
*/

/// Compares strings as sorted by the Finder.
///
/// This method should be used whenever file names or other strings are presented in lists and tables
/// where Finder-like sorting is appropriate. The exact sorting behavior of this method is different
/// under different locales and may be changed in future releases. This method uses the current locale.
- (NSComparisonResult)localizedStandardCompare:(NSString *)string API_AVAILABLE(macos(10.6), ios(4.0), watchos(2.0), tvos(9.0));

/// Returns a Boolean value that indicates whether a given string is equal to the receiver using a literal Unicode-based comparison.
///
/// @param aString The string with which to compare the receiver.
/// @return @c YES if @c aString is equivalent to the receiver (if they have the same id or if they are
///   @c NSOrderedSame in a literal comparison), otherwise @c NO.
///
/// When you know both objects are strings, this method is a faster way to check equality than @c isEqual:.
- (BOOL)isEqualToString:(NSString *)aString;


#pragma mark *** String searching ***

/* These perform locale unaware prefix or suffix match. If you need locale awareness, use rangeOfString:options:range:locale:, passing NSAnchoredSearch (or'ed with NSBackwardsSearch for suffix, and NSCaseInsensitiveSearch|NSDiacriticInsensitiveSearch if needed) for options, NSMakeRange(0, [receiver length]) for range, and [NSLocale currentLocale] for locale.
*/

/// Returns a Boolean value that indicates whether a given string matches the beginning characters of the receiver.
///
/// @param str A string.
/// @return @c YES if @c aString matches the beginning characters of the receiver, otherwise @c NO.
///   Returns @c NO if @c aString is empty.
- (BOOL)hasPrefix:(NSString *)str;

/// Returns a Boolean value that indicates whether a given string matches the ending characters of the receiver.
///
/// @param str A string.
/// @return @c YES if @c aString matches the ending characters of the receiver, otherwise @c NO.
///   Returns @c NO if @c aString is empty.
- (BOOL)hasSuffix:(NSString *)str;

/// Returns a string containing characters the receiver and a given string have in common, starting from the beginning of each up to the first characters that aren't equivalent.
///
/// @param str The string with which to compare the receiver.
/// @param mask Options for the comparison. The following search options may be specified by combining them
///   with the C bitwise OR operator: @c NSCaseInsensitiveSearch, @c NSLiteralSearch.
/// @return A string containing characters the receiver and @c aString have in common.
- (NSString *)commonPrefixWithString:(NSString *)str options:(NSStringCompareOptions)mask;

/* Simple convenience methods for string searching. containsString: returns YES if the target string is contained within the receiver. Same as calling rangeOfString:options: with no options, thus doing a case-sensitive, locale-unaware search. localizedCaseInsensitiveContainsString: is the case-insensitive variant which also takes the current locale into effect. Starting in 10.11 and iOS9, the new localizedStandardRangeOfString: or localizedStandardContainsString: APIs are even better convenience methods for user level searching.   More sophisticated needs can be achieved by calling rangeOfString:options:range:locale: directly.
*/

/// Returns a Boolean value indicating whether the string contains a given string by performing a case-sensitive, locale-unaware search.
///
/// @param str The string to search for. This value must not be @c nil.
/// @return @c YES if the receiver contains @c str, otherwise @c NO.
///
/// Calling this method is equivalent to calling @c rangeOfString:options: with no options.
- (BOOL)containsString:(NSString *)str API_AVAILABLE(macos(10.10), ios(8.0), watchos(2.0), tvos(9.0));

/// Returns a Boolean value indicating whether the string contains a given string by performing a case-insensitive, locale-aware search.
///
/// @param str The string to search for. This value must not be @c nil.
/// @return @c YES if the receiver contains @c str, otherwise @c NO.
- (BOOL)localizedCaseInsensitiveContainsString:(NSString *)str API_AVAILABLE(macos(10.10), ios(8.0), watchos(2.0), tvos(9.0));

/* The following two are the most appropriate methods for doing user-level string searches, similar to how searches are done generally in the system.  The search is locale-aware, case and diacritic insensitive. As with other APIs, "standard" in the name implies "system default behavior," so the exact list of search options applied may change over time.  If you need more control over the search options, please use the rangeOfString:options:range:locale: method. You can pass [NSLocale currentLocale] for searches in user's locale.
*/

/// Returns a Boolean value indicating whether the string contains a given string by performing a case and diacritic insensitive, locale-aware search.
///
/// @param str The string to search for. This value must not be @c nil.
/// @return @c YES if the receiver contains @c str, otherwise @c NO.
- (BOOL)localizedStandardContainsString:(NSString *)str API_AVAILABLE(macos(10.11), ios(9.0), watchos(2.0), tvos(9.0));

/// Finds and returns the range of the first occurrence of a given string within the string by performing a case and diacritic insensitive, locale-aware search.
///
/// @param str The string to search for. This value must not be @c nil.
/// @return The range of the first occurrence of @c str in the receiver. Returns @c {NSNotFound, 0} if @c str is not found.
- (NSRange)localizedStandardRangeOfString:(NSString *)str API_AVAILABLE(macos(10.11), ios(9.0), watchos(2.0), tvos(9.0));

/* These methods perform string search, looking for the searchString within the receiver string.  These return length==0 if the target string is not found. So, to check for containment: ([str rangeOfString:@"target"].length > 0).  Note that the length of the range returned by these methods might be different than the length of the target string, due composed characters and such.
 
Note that the first three methods do not take locale arguments, and perform the search in a non-locale aware fashion, which is not appropriate for user-level searching. To do user-level string searching, use the last method, specifying locale:[NSLocale currentLocale], or better yet, use localizedStandardRangeOfString: or localizedStandardContainsString:.
 
The range argument specifies the subrange, rather than the whole, of the receiver to use in the search.  It is an error to specify a range that is outside of the receiver's bounds, and an exception may be raised.
*/

/// Finds and returns the range of the first occurrence of a given string within the string.
///
/// @param searchString The string to search for.
/// @return An @c NSRange structure giving the location and length in the receiver of the first occurrence of @c searchString.
///   Returns @c {NSNotFound, 0} if @c searchString is not found or is empty.
- (NSRange)rangeOfString:(NSString *)searchString;

/// Finds and returns the range of the first occurrence of a given string within the string, subject to given options.
///
/// @param searchString The string to search for.
/// @param mask A mask specifying search options. For possible values, see @c NSStringCompareOptions.
/// @return An @c NSRange structure giving the location and length in the receiver of the first occurrence of @c searchString,
///   modulo the options in @c mask. Returns @c {NSNotFound, 0} if @c searchString is not found or is empty.
- (NSRange)rangeOfString:(NSString *)searchString options:(NSStringCompareOptions)mask;

/// Finds and returns the range of the first occurrence of a given string, within the given range of the string, subject to given options.
///
/// @param searchString The string for which to search.
/// @param mask A mask specifying search options.
/// @param rangeOfReceiverToSearch The range within the receiver for which to search. Raises an @c NSRangeException if the range is invalid.
/// @return An @c NSRange structure giving the location and length in the receiver of @c searchString within @c rangeOfReceiverToSearch,
///   modulo the options in @c mask. The range returned is relative to the start of the string.
///   Returns @c {NSNotFound, 0} if @c searchString is not found or is empty.
- (NSRange)rangeOfString:(NSString *)searchString options:(NSStringCompareOptions)mask range:(NSRange)rangeOfReceiverToSearch;

/// Finds and returns the range of the first occurrence of a given string within a given range of the string, subject to given options, using the specified locale, if any.
///
/// @param searchString The string for which to search.
/// @param mask A mask specifying search options.
/// @param rangeOfReceiverToSearch The range within the receiver for which to search. Raises an @c NSRangeException if the range is invalid.
/// @param locale The locale to use when comparing the receiver with @c aString. To use the current locale, pass @c [NSLocale currentLocale]. To use the system locale, pass @c nil.
/// @return An @c NSRange structure giving the location and length in the receiver of @c aString within @c aRange, modulo the options in @c mask. The range returned is relative to the start of the string.
///   Returns @c {NSNotFound, 0} if @c aString is not found or is empty.
- (NSRange)rangeOfString:(NSString *)searchString options:(NSStringCompareOptions)mask range:(NSRange)rangeOfReceiverToSearch locale:(nullable NSLocale *)locale API_AVAILABLE(macos(10.5), ios(2.0), watchos(2.0), tvos(9.0));

/* These return the range of the first character from the set in the string, not the range of a sequence of characters. 
 
The range argument specifies the subrange, rather than the whole, of the receiver to use in the search.  It is an error to specify a range that is outside of the receiver's bounds, and an exception may be raised.
*/

/// Finds and returns the range in the string of the first character from a given character set.
///
/// @param searchSet A character set. This value must not be @c nil.
/// @return The range in the receiver of the first character found from @c aSet. Returns a range of @c {NSNotFound, 0} if none of the characters in @c aSet are found.
- (NSRange)rangeOfCharacterFromSet:(NSCharacterSet *)searchSet;

/// Finds and returns the range in the string of the first character, using given options, from a given character set.
///
/// @param searchSet A character set. This value must not be @c nil.
/// @param mask A mask specifying search options. The following options may be combined: @c NSAnchoredSearch, @c NSBackwardsSearch.
/// @return The range in the receiver of the first character found from @c aSet. Returns a range of @c {NSNotFound, 0} if none of the characters in @c aSet are found.
- (NSRange)rangeOfCharacterFromSet:(NSCharacterSet *)searchSet options:(NSStringCompareOptions)mask;

/// Finds and returns the range in the string of the first character from a given character set found in a given range with given options.
///
/// @param searchSet A character set. This value must not be @c nil.
/// @param mask A mask specifying search options. The following options may be combined: @c NSAnchoredSearch, @c NSBackwardsSearch.
/// @param rangeOfReceiverToSearch The range in which to search. @c aRange must not exceed the bounds of the receiver.
/// @return The range in the receiver of the first character found from @c aSet within @c aRange. Returns a range of @c {NSNotFound, 0} if none of the characters in @c aSet are found.
- (NSRange)rangeOfCharacterFromSet:(NSCharacterSet *)searchSet options:(NSStringCompareOptions)mask range:(NSRange)rangeOfReceiverToSearch;

/// Returns the range in the receiver of the composed character sequence located at a given index.
///
/// @param index The index of a character in the receiver. The value must not exceed the bounds of the receiver.
/// @return The range in the receiver of the composed character sequence located at @c anIndex.
- (NSRange)rangeOfComposedCharacterSequenceAtIndex:(NSUInteger)index;

/// Returns the range in the string of the composed character sequences for a given range.
///
/// @param range A range in the receiver. The range must not exceed the bounds of the receiver.
/// @return The range in the receiver that includes the composed character sequences in @c range.
///
/// This method provides a convenient way to grow a range to include all composed character sequences it overlaps.
- (NSRange)rangeOfComposedCharacterSequencesForRange:(NSRange)range API_AVAILABLE(macos(10.5), ios(2.0), watchos(2.0), tvos(9.0));

/// Returns a new string made by appending a given string to the receiver.
///
/// @param aString The string to append to the receiver. @c aString must not be @c nil.
/// @return A new string made by appending @c aString to the receiver.
- (NSString *)stringByAppendingString:(NSString *)aString;

/// Returns a string made by appending to the receiver a string constructed from a given format string and the following arguments.
- (NSString *)stringByAppendingFormat:(NSString *)format, ... NS_FORMAT_FUNCTION(1,2);


#pragma mark *** Extracting numeric values ***

/* The following convenience methods all skip initial space characters (whitespaceSet) and ignore trailing characters. They are not locale-aware. NSScanner or NSNumberFormatter can be used for more powerful and locale-aware parsing of numbers.
*/

/// The floating-point value of the string as a @c double.
///
/// This property doesn't include any whitespace at the beginning of the string. This property is @c HUGE_VAL or @c -HUGE_VAL on overflow, @c 0.0 on underflow. This property is @c 0.0 if the string doesn't begin with a valid text representation of a floating-point number. Uses non-localized formatting information.
@property (readonly) double doubleValue;

/// The floating-point value of the string as a @c float.
///
/// This property doesn't include whitespace at the beginning of the string. This property is @c HUGE_VAL or @c -HUGE_VAL on overflow, @c 0.0 on underflow. This property is @c 0.0 if the string doesn't begin with a valid text representation of a floating-point number. Uses non-localized formatting information.
@property (readonly) float floatValue;

/// The integer value of the string.
///
/// The integer value of the string, assuming a decimal representation and skipping whitespace at the beginning of the string. This property is @c INT_MAX or @c INT_MIN on overflow. This property is @c 0 if the string doesn't begin with a valid decimal text representation of a number. Uses non-localized formatting information.
@property (readonly) int intValue;

/// The @c NSInteger value of the string.
///
/// The @c NSInteger value of the string, assuming a decimal representation and skipping whitespace at the beginning of the string. This property is @c 0 if the string doesn't begin with a valid decimal text representation of a number. Uses non-localized formatting information.
@property (readonly) NSInteger integerValue API_AVAILABLE(macos(10.5), ios(2.0), watchos(2.0), tvos(9.0));

/// The @c long @c long value of the string.
///
/// The @c long @c long value of the string, assuming a decimal representation and skipping whitespace at the beginning of the string. This property is @c LLONG_MAX or @c LLONG_MIN on overflow. This property is @c 0 if the receiver doesn't begin with a valid decimal text representation of a number. Uses non-localized formatting information.
@property (readonly) long long longLongValue API_AVAILABLE(macos(10.5), ios(2.0), watchos(2.0), tvos(9.0));

/// The Boolean value of the string.
///
/// Returns @c YES on encountering one of "Y", "y", "T", "t", or a digit 1-9---the method ignores any trailing characters. Returns @c NO if the receiver doesn't begin with a valid decimal text representation of a number. Skips initial space characters (whitespaceSet), or optional -/+ sign followed by zeroes.
@property (readonly) BOOL boolValue API_AVAILABLE(macos(10.5), ios(2.0), watchos(2.0), tvos(9.0));  // Skips initial space characters (whitespaceSet), or optional -/+ sign followed by zeroes. Returns YES on encountering one of "Y", "y", "T", "t", or a digit 1-9. It ignores any trailing characters.


#pragma mark *** Case changing ***

/* The following three return the canonical (non-localized) mappings. They are suitable for programming operations that require stable results not depending on the user's locale preference.  For locale-aware case mapping for strings presented to users, use the "localized" methods below.
*/

/// An uppercase representation of the string.
///
/// This property performs the canonical (non-localized) mapping. It is suitable for programming operations that require stable results not depending on the current locale. Case transformations aren't guaranteed to be symmetrical or to produce strings of the same lengths as the originals.
@property (readonly, copy) NSString *uppercaseString;

/// A lowercase representation of the string.
///
/// This property performs the canonical (non-localized) mapping. It is suitable for programming operations that require stable results not depending on the current locale. Case transformations aren't guaranteed to be symmetrical or to produce strings of the same lengths as the originals.
@property (readonly, copy) NSString *lowercaseString;

/// A capitalized representation of the string.
///
/// A capitalized string is a string with the first character in each word changed to its corresponding uppercase value, and all remaining characters set to their corresponding lowercase values. This property performs the canonical (non-localized) mapping. Case transformations aren't guaranteed to be symmetrical or to produce strings of the same lengths as the originals.
@property (readonly, copy) NSString *capitalizedString;

/* The following three return the locale-aware case mappings. They are suitable for strings presented to the user.
*/

/// Returns a version of the string with all letters converted to uppercase, taking into account the current locale.
@property (readonly, copy) NSString *localizedUppercaseString API_AVAILABLE(macos(10.11), ios(9.0), watchos(2.0), tvos(9.0));

/// Returns a version of the string with all letters converted to lowercase, taking into account the current locale.
@property (readonly, copy) NSString *localizedLowercaseString API_AVAILABLE(macos(10.11), ios(9.0), watchos(2.0), tvos(9.0));

/// Returns a capitalized representation of the receiver using the current locale.
@property (readonly, copy) NSString *localizedCapitalizedString API_AVAILABLE(macos(10.11), ios(9.0), watchos(2.0), tvos(9.0));

/* The following methods perform localized case mappings based on the locale specified. Passing nil indicates the canonical mapping.  For the user preference locale setting, specify +[NSLocale currentLocale].
*/

/// Returns a version of the string with all letters converted to uppercase, taking into account the specified locale.
///
/// @param locale The locale. For strings presented to users, pass the current locale. To use the system locale, pass @c nil.
- (NSString *)uppercaseStringWithLocale:(nullable NSLocale *)locale API_AVAILABLE(macos(10.8), ios(6.0), watchos(2.0), tvos(9.0));

/// Returns a version of the string with all letters converted to lowercase, taking into account the specified locale.
///
/// @param locale The locale. For strings presented to users, pass the current locale. To use the system locale, pass @c nil.
- (NSString *)lowercaseStringWithLocale:(nullable NSLocale *)locale API_AVAILABLE(macos(10.8), ios(6.0), watchos(2.0), tvos(9.0));

/// Returns a capitalized representation of the receiver using the specified locale.
///
/// @param locale The locale. For strings presented to users, pass the current locale. To use the system locale, pass @c nil.
- (NSString *)capitalizedStringWithLocale:(nullable NSLocale *)locale API_AVAILABLE(macos(10.8), ios(6.0), watchos(2.0), tvos(9.0));


#pragma mark *** Finding lines, sentences, words, etc ***

/// Returns by reference the beginning of the first line and the end of the last line touched by the given range.
///
/// @param startPtr Upon return, contains the index of the first character of the line containing the beginning of @c aRange. Pass @c NULL if you do not need this value.
/// @param lineEndPtr Upon return, contains the index of the first character past the terminator of the line containing the end of @c aRange. Pass @c NULL if you do not need this value.
/// @param contentsEndPtr Upon return, contains the index of the first character of the terminator of the line containing the end of @c aRange. Pass @c NULL if you do not need this value.
/// @param range A range within the receiver. The value must not exceed the bounds of the receiver.
- (void)getLineStart:(nullable NSUInteger *)startPtr end:(nullable NSUInteger *)lineEndPtr contentsEnd:(nullable NSUInteger *)contentsEndPtr forRange:(NSRange)range;

/// Returns the range of characters representing the line or lines containing a given range.
///
/// @param range A range within the receiver. The value must not exceed the bounds of the receiver.
/// @return The range of characters representing the line or lines containing @c aRange, including the line termination characters.
- (NSRange)lineRangeForRange:(NSRange)range;

/// Returns by reference the beginning of the first paragraph and the end of the last paragraph touched by the given range.
///
/// @param startPtr Upon return, contains the index of the first character of the paragraph containing the beginning of @c aRange. Pass @c NULL if you do not need this value.
/// @param parEndPtr Upon return, contains the index of the first character past the terminator of the paragraph containing the end of @c aRange. Pass @c NULL if you do not need this value.
/// @param contentsEndPtr Upon return, contains the index of the first character of the terminator of the paragraph containing the end of @c aRange. Pass @c NULL if you do not need this value.
/// @param range A range within the receiver. The value must not exceed the bounds of the receiver.
- (void)getParagraphStart:(nullable NSUInteger *)startPtr end:(nullable NSUInteger *)parEndPtr contentsEnd:(nullable NSUInteger *)contentsEndPtr forRange:(NSRange)range;

/// Returns the range of characters representing the paragraph or paragraphs containing a given range.
///
/// @param range A range within the receiver. The range must not exceed the bounds of the receiver.
/// @return The range of characters representing the paragraph or paragraphs containing @c aRange, including the paragraph termination characters.
- (NSRange)paragraphRangeForRange:(NSRange)range;

/// Constants to specify kinds of substrings and styles of enumeration.
///
/// These options are used with the ``NSString/enumerateSubstrings(in:options:using:)`` method. Pass in one `NSStringEnumerationBy...` option and combine with any of the remaining enumeration style constants using the C bitwise `OR` operator.
typedef NS_OPTIONS(NSUInteger, NSStringEnumerationOptions) {
    // Pass in one of the "By" options:
    NSStringEnumerationByLines = 0,                       // Equivalent to lineRangeForRange:
    NSStringEnumerationByParagraphs = 1,                  // Equivalent to paragraphRangeForRange:
    NSStringEnumerationByComposedCharacterSequences = 2,  // Equivalent to rangeOfComposedCharacterSequencesForRange:
    NSStringEnumerationByWords = 3,
    NSStringEnumerationBySentences = 4,
    NSStringEnumerationByCaretPositions API_AVAILABLE(macos(11.0), ios(14.0), watchos(7.0), tvos(14.0)) = 5, // Enumerate text editing cursor positions. It could separate characters within a grapheme cluster.
    NSStringEnumerationByDeletionClusters API_AVAILABLE(macos(11.0), ios(14.0), watchos(7.0), tvos(14.0)) = 6, //  Enumerate text editing positions for backwards deletion. It could separate characters within a grapheme cluster.

    // ...and combine any of the desired additional options:
    NSStringEnumerationReverse = 1UL << 8,
    NSStringEnumerationSubstringNotRequired = 1UL << 9,
    NSStringEnumerationLocalized = 1UL << 10              // User's default locale
};

/* In the enumerate methods, the blocks will be invoked inside an autorelease pool, so any values assigned inside the block should be retained.
*/

/// Enumerates the substrings of the specified type in the specified range of the string.
///
/// @param range The range within the string to enumerate substrings.
/// @param opts Options specifying types of substrings and enumeration styles.
/// @param block The block executed for the enumeration.
- (void)enumerateSubstringsInRange:(NSRange)range options:(NSStringEnumerationOptions)opts usingBlock:(void (^)(NSString * _Nullable substring, NSRange substringRange, NSRange enclosingRange, BOOL *stop))block API_AVAILABLE(macos(10.6), ios(4.0), watchos(2.0), tvos(9.0));

/// Enumerates all the lines in the string.
///
/// @param block The block executed for the enumeration. The block takes two arguments: the current line (without line terminators), and a stop flag.
- (void)enumerateLinesUsingBlock:(void (^)(NSString *line, BOOL *stop))block API_AVAILABLE(macos(10.6), ios(4.0), watchos(2.0), tvos(9.0));


#pragma mark *** Character encoding and converting to/from c-string representations ***

/// A null-terminated UTF8 representation of the string.
///
/// This C string is a pointer to a structure inside the string object, which may have a lifetime shorter than the string object and will certainly not have a longer lifetime. Therefore, you should copy the C string if it needs to be stored outside of the memory context in which you use this property.
@property (nullable, readonly) const char *UTF8String NS_RETURNS_INNER_POINTER;	// Convenience to return null-terminated UTF8 representation

/// The fastest encoding to which the receiver may be converted without loss of information.
///
/// "Fastest" applies to retrieval of characters from the string. This encoding may not be space efficient.
@property (readonly) NSStringEncoding fastestEncoding;    	// Result in O(1) time; a rough estimate

/// The smallest encoding to which the receiver can be converted without loss of information.
///
/// This encoding may not be the fastest for accessing characters, but is space-efficient. This property may take some time to access.
@property (readonly) NSStringEncoding smallestEncoding;   	// Result in O(n) time; the encoding in which the string is most compact

/// Returns an @c NSData object containing a representation of the receiver encoded using a given encoding.
///
/// @param encoding A string encoding.
/// @param lossy If @c YES, then allows characters to be removed or altered in conversion.
/// @return An @c NSData object containing a representation of the receiver encoded using @c encoding.
///   Returns @c nil if @c flag is @c NO and the receiver can't be converted without losing some information.
- (nullable NSData *)dataUsingEncoding:(NSStringEncoding)encoding allowLossyConversion:(BOOL)lossy;   // External representation

/// Returns an @c NSData object containing a representation of the receiver encoded using a given encoding.
///
/// @param encoding A string encoding.
/// @return The result of invoking @c dataUsingEncoding:allowLossyConversion: with @c NO as the second argument (that is, requiring lossless conversion).
- (nullable NSData *)dataUsingEncoding:(NSStringEncoding)encoding;                                    // External representation

/// Returns a Boolean value that indicates whether the receiver can be converted to a given encoding without loss of information.
///
/// @param encoding A string encoding.
/// @return @c YES if the receiver can be converted to @c encoding without loss of information. Returns @c NO if characters would have to be changed or deleted in the process of changing encodings.
- (BOOL)canBeConvertedToEncoding:(NSStringEncoding)encoding;

/* Methods to convert NSString to a NULL-terminated cString using the specified encoding. Note, these are the "new" cString methods, and are not deprecated like the older cString methods which do not take encoding arguments.  Also, cString methods should be used just with 8-bit encodings, and not encodings such as UTF-16 or UTF-32.  For those, use methods such as getCharacters:range: (for UTF-16 characters in system endianness) or getBytes:... (which can take any encoding).
*/

/// Returns a representation of the string as a C string using a given encoding.
///
/// @param encoding The encoding for the returned C string.
/// @return A C string representation of the receiver using the encoding specified by @c encoding. Returns @c NULL if the receiver cannot be losslessly converted to @c encoding.
///
/// The returned C string is guaranteed to be valid only until either the receiver is freed, or until the current memory is emptied, whichever occurs first. You should copy the C string or use @c getCString:maxLength:encoding: if it needs to store the C string beyond this time.
- (nullable const char *)cStringUsingEncoding:(NSStringEncoding)encoding NS_RETURNS_INNER_POINTER;	// "Autoreleased"; NULL return if encoding conversion not possible; for performance reasons, lifetime of this should not be considered longer than the lifetime of the receiving string (if the receiver string is freed, this might go invalid then, before the end of the autorelease scope). Use only with 8-bit encodings, and not encodings such as UTF-16 or UTF-32.

/// Converts the string to a given encoding and stores it in a buffer.
///
/// @param buffer Upon return, contains the converted C-string plus the @c NULL termination byte. The buffer must include room for @c maxBufferCount bytes.
/// @param maxBufferCount The maximum number of bytes to write to @c buffer (including the @c NULL termination byte).
/// @param encoding The encoding for the returned C string.
/// @return @c YES if the operation was successful, otherwise @c NO. Returns @c NO if conversion is not possible due to encoding errors or if @c buffer is too small.
- (BOOL)getCString:(char *)buffer maxLength:(NSUInteger)maxBufferCount encoding:(NSStringEncoding)encoding;	// NO return if conversion not possible due to encoding errors or too small of a buffer. The buffer should include room for maxBufferCount bytes; this number should accomodate the expected size of the return value plus the NULL termination character, which this method adds. (So note that the maxLength passed to this method is one more than the one you would have passed to the deprecated getCString:maxLength:.) Use only with 8-bit encodings, and not encodings such as UTF-16 or UTF-32.

/* Use this to convert string section at a time into a fixed-size buffer, without any allocations.  Does not NULL-terminate. 
    buffer is the buffer to write to; if NULL, this method can be used to computed size of needed buffer.
    maxBufferCount is the length of the buffer in bytes. It's a good idea to make sure this is at least enough to hold one character's worth of conversion. 
    usedBufferCount is the length of the buffer used up by the current conversion. Can be NULL.
    encoding is the encoding to convert to.
    options specifies the options to apply.
    range is the range to convert.
    leftOver is the remaining range. Can be NULL.
    YES return indicates some characters were converted. Conversion might usually stop when the buffer fills, 
      but it might also stop when the conversion isn't possible due to the chosen encoding. 
*/

/// Gets a given range of characters as bytes in a specified encoding.
///
/// @param buffer A buffer into which to store the bytes from the receiver. The returned bytes are not @c NULL-terminated.
/// @param maxBufferCount The maximum number of bytes to write to @c buffer.
/// @param usedBufferCount The number of bytes used from @c buffer. Pass @c NULL if you do not need this value.
/// @param encoding The encoding to use for the returned bytes.
/// @param options A mask to specify options to use for converting the receiver's contents to @c encoding.
/// @param range The range of characters in the receiver to get.
/// @param leftover The remaining range. Pass @c NULL if you do not need this value.
/// @return @c YES if some characters were converted, otherwise @c NO.
- (BOOL)getBytes:(nullable void *)buffer maxLength:(NSUInteger)maxBufferCount usedLength:(nullable NSUInteger *)usedBufferCount encoding:(NSStringEncoding)encoding options:(NSStringEncodingConversionOptions)options range:(NSRange)range remainingRange:(nullable NSRangePointer)leftover;

/* These return the maximum and exact number of bytes needed to store the receiver in the specified encoding in non-external representation. The first one is O(1), while the second one is O(n). These do not include space for a terminating null.
*/

/// Returns the maximum number of bytes needed to store the receiver in a given encoding.
///
/// @param enc The encoding for which to determine the receiver's length.
/// @return The maximum number of bytes needed to store the receiver in @c encoding in a non-external representation.
///   The length does not include space for a terminating @c NULL character. Returns @c 0 on error (overflow).
///   The result is an estimate and is returned in @c O(1) time; the estimate may be considerably greater than the actual length needed.
- (NSUInteger)maximumLengthOfBytesUsingEncoding:(NSStringEncoding)enc;	// Result in O(1) time; the estimate may be way over what's needed. Returns 0 on error (overflow)

/// Returns the number of bytes required to store the receiver in a given encoding.
///
/// @param enc The encoding for which to determine the receiver's length.
/// @return The number of bytes required to store the receiver in the encoding @c enc in a non-external representation.
///   The length does not include space for a terminating @c NULL character. Returns @c 0 on error.
///   The result is exact and is returned in @c O(n) time.
- (NSUInteger)lengthOfBytesUsingEncoding:(NSStringEncoding)enc;		// Result in O(n) time; the result is exact. Returns 0 on error (cannot convert to specified encoding, or overflow)

/// Returns a zero-terminated list of the encodings string objects support in the application's environment.
@property (class, readonly) const NSStringEncoding *availableStringEncodings;

/// Returns a human-readable string giving the name of a given encoding.
///
/// @param encoding A string encoding.
/// @return A human-readable string giving the name of @c encoding in the current locale.
+ (NSString *)localizedNameOfStringEncoding:(NSStringEncoding)encoding;

/* User-dependent encoding whose value is derived from user's default language and potentially other factors. The use of this encoding might sometimes be needed when interpreting user documents with unknown encodings, in the absence of other hints.  This encoding should be used rarely, if at all. Note that some potential values here might result in unexpected encoding conversions of even fairly straightforward NSString content --- for instance, punctuation characters with a bidirectional encoding.
 */

/// Returns the C-string encoding assumed for any method accepting a C string as an argument.
///
/// This property returns a user-dependent encoding whose value is derived from user's default language and potentially other factors. You might sometimes need to use this encoding when interpreting user documents with unknown encodings, in the absence of other hints, but in general this encoding should be used rarely, if at all.
@property (class, readonly) NSStringEncoding defaultCStringEncoding;	// Should be rarely used

#pragma mark *** Other ***

/// A string made by normalizing the string's contents using the Unicode Normalization Form D.
@property (readonly, copy) NSString *decomposedStringWithCanonicalMapping;
/// A string made by normalizing the string's contents using the Unicode Normalization Form C.
@property (readonly, copy) NSString *precomposedStringWithCanonicalMapping;
/// A string made by normalizing the receiver's contents using the Unicode Normalization Form KD.
@property (readonly, copy) NSString *decomposedStringWithCompatibilityMapping;
/// A string made by normalizing the receiver's contents using the Unicode Normalization Form KC.
@property (readonly, copy) NSString *precomposedStringWithCompatibilityMapping;

/// Returns an array containing substrings from the receiver that have been divided by a given separator.
///
/// @param separator The separator string.
/// @return An @c NSArray object containing substrings from the receiver that have been divided by @c separator.
- (NSArray<NSString *> *)componentsSeparatedByString:(NSString *)separator;

/// Returns an array containing substrings from the receiver that have been divided by characters in a given set.
///
/// @param separator A character set containing the characters to use to split the receiver. Must not be @c nil.
/// @return An @c NSArray object containing substrings from the receiver that have been divided by characters in @c separator.
- (NSArray<NSString *> *)componentsSeparatedByCharactersInSet:(NSCharacterSet *)separator API_AVAILABLE(macos(10.5), ios(2.0), watchos(2.0), tvos(9.0));

/// Returns a new string made by removing from both ends of the receiver characters contained in a given character set.
///
/// @param set A character set containing the characters to remove from the receiver. @c set must not be @c nil.
/// @return A new string made by removing from both ends of the receiver characters contained in @c set.
///   If the receiver is composed entirely of characters from @c set, the empty string is returned.
- (NSString *)stringByTrimmingCharactersInSet:(NSCharacterSet *)set;

/// Returns a new string formed from the receiver by either removing characters from the end, or by appending as many occurrences as necessary of a given pad string.
///
/// @param newLength The new length for the receiver.
/// @param padString The string with which to extend the receiver.
/// @param padIndex The index in @c padString from which to start padding.
- (NSString *)stringByPaddingToLength:(NSUInteger)newLength withString:(NSString *)padString startingAtIndex:(NSUInteger)padIndex;

/* Returns a string with the character folding options applied. theOptions is a mask of compare flags with *InsensitiveSearch suffix.
*/

/// Creates a string suitable for comparison by removing the specified character distinctions from a string.
///
/// @param options Any combination of @c NSCaseInsensitiveSearch, @c NSWidthInsensitiveSearch, and @c NSDiacriticInsensitiveSearch comparison options.
/// @param locale The locale to use for the folding operation. Pass @c nil to use the system locale.
/// @return A string created by performing a character folding operation with the specified options and locale.
- (NSString *)stringByFoldingWithOptions:(NSStringCompareOptions)options locale:(nullable NSLocale *)locale API_AVAILABLE(macos(10.5), ios(2.0), watchos(2.0), tvos(9.0));

/* Replace all occurrences of the target string in the specified range with replacement. Specified compare options are used for matching target. If NSRegularExpressionSearch is specified, the replacement is treated as a template, as in the corresponding NSRegularExpression methods, and no other options can apply except NSCaseInsensitiveSearch and NSAnchoredSearch.
*/

/// Returns a new string in which all occurrences of a target string in a specified range of the receiver are replaced by another given string.
///
/// @param target The string to replace.
/// @param replacement The string with which to replace @c target.
/// @param options A mask of options to use when comparing @c target with the receiver. Pass @c 0 to specify no options.
/// @param searchRange The range in the receiver in which to search for @c target.
/// @return A new string in which all occurrences of @c target, matched using @c options, in @c searchRange of the receiver are replaced by @c replacement.
- (NSString *)stringByReplacingOccurrencesOfString:(NSString *)target withString:(NSString *)replacement options:(NSStringCompareOptions)options range:(NSRange)searchRange API_AVAILABLE(macos(10.5), ios(2.0), watchos(2.0), tvos(9.0));

/* Replace all occurrences of the target string with replacement. Invokes the above method with 0 options and range of the whole string.
*/

/// Returns a new string in which all occurrences of a target string in the receiver are replaced by another given string.
///
/// @param target The string to replace.
/// @param replacement The string with which to replace @c target.
/// @return A new string in which all occurrences of @c target in the receiver are replaced by @c replacement.
- (NSString *)stringByReplacingOccurrencesOfString:(NSString *)target withString:(NSString *)replacement API_AVAILABLE(macos(10.5), ios(2.0), watchos(2.0), tvos(9.0));

/* Replace characters in range with the specified string, returning new string.
*/

/// Returns a new string in which the characters in a specified range of the receiver are replaced by a given string.
///
/// @param range A range of characters in the receiver.
/// @param replacement The string with which to replace the characters in @c range.
/// @return A new string in which the characters in @c range of the receiver are replaced by @c replacement.
- (NSString *)stringByReplacingCharactersInRange:(NSRange)range withString:(NSString *)replacement API_AVAILABLE(macos(10.5), ios(2.0), watchos(2.0), tvos(9.0));

#if !0
/// Constants representing an ICU string transform.
///
/// These constants are used by the `NSString` method `stringByApplyingTransform:reverse:`.
typedef NSString *NSStringTransform NS_TYPED_EXTENSIBLE_ENUM;

/* Perform string transliteration.  The transformation represented by transform is applied to the receiver. reverse indicates that the inverse transform should be used instead, if it exists. Attempting to use an invalid transform identifier or reverse an irreversible transform will return nil; otherwise the transformed string value is returned (even if no characters are actually transformed). You can pass one of the predefined transforms below (NSStringTransformLatinToKatakana, etc), or any valid ICU transform ID as defined in the ICU User Guide. Arbitrary ICU transform rules are not supported.
*/

/// Returns a new string by applying a specified transform to the string.
///
/// You can use this method to, for example, transliterate text from one script to another, strip diacritics or combining marks, and get the unicode names of characters.
- (nullable NSString *)stringByApplyingTransform:(NSStringTransform)transform reverse:(BOOL)reverse API_AVAILABLE(macos(10.11), ios(9.0), watchos(2.0), tvos(9.0));	// Returns nil if reverse not applicable or transform is invalid

/// A transform that converts Latin script to Katakana.
FOUNDATION_EXPORT NSStringTransform const NSStringTransformLatinToKatakana         API_AVAILABLE(macos(10.11), ios(9.0), watchos(2.0), tvos(9.0));
/// A transform that converts Latin script to Hiragana.
FOUNDATION_EXPORT NSStringTransform const NSStringTransformLatinToHiragana         API_AVAILABLE(macos(10.11), ios(9.0), watchos(2.0), tvos(9.0));
/// A transform that converts Latin script to Hangul.
FOUNDATION_EXPORT NSStringTransform const NSStringTransformLatinToHangul           API_AVAILABLE(macos(10.11), ios(9.0), watchos(2.0), tvos(9.0));
/// A transform that converts Latin script to Arabic.
FOUNDATION_EXPORT NSStringTransform const NSStringTransformLatinToArabic           API_AVAILABLE(macos(10.11), ios(9.0), watchos(2.0), tvos(9.0));
/// A transform that converts Latin script to Hebrew.
FOUNDATION_EXPORT NSStringTransform const NSStringTransformLatinToHebrew           API_AVAILABLE(macos(10.11), ios(9.0), watchos(2.0), tvos(9.0));
/// A transform that converts Latin script to Thai.
FOUNDATION_EXPORT NSStringTransform const NSStringTransformLatinToThai             API_AVAILABLE(macos(10.11), ios(9.0), watchos(2.0), tvos(9.0));
/// A transform that converts Latin script to Cyrillic.
FOUNDATION_EXPORT NSStringTransform const NSStringTransformLatinToCyrillic         API_AVAILABLE(macos(10.11), ios(9.0), watchos(2.0), tvos(9.0));
/// A transform that converts Latin script to Greek.
FOUNDATION_EXPORT NSStringTransform const NSStringTransformLatinToGreek            API_AVAILABLE(macos(10.11), ios(9.0), watchos(2.0), tvos(9.0));
/// A transform that converts text to Latin script.
FOUNDATION_EXPORT NSStringTransform const NSStringTransformToLatin                 API_AVAILABLE(macos(10.11), ios(9.0), watchos(2.0), tvos(9.0));
/// A transform that converts Mandarin to Latin script.
FOUNDATION_EXPORT NSStringTransform const NSStringTransformMandarinToLatin         API_AVAILABLE(macos(10.11), ios(9.0), watchos(2.0), tvos(9.0));
/// A transform that converts Hiragana to Katakana.
FOUNDATION_EXPORT NSStringTransform const NSStringTransformHiraganaToKatakana      API_AVAILABLE(macos(10.11), ios(9.0), watchos(2.0), tvos(9.0));
/// A transform that converts fullwidth characters to halfwidth.
FOUNDATION_EXPORT NSStringTransform const NSStringTransformFullwidthToHalfwidth    API_AVAILABLE(macos(10.11), ios(9.0), watchos(2.0), tvos(9.0));
/// A transform that converts characters to XML hex escape codes.
FOUNDATION_EXPORT NSStringTransform const NSStringTransformToXMLHex                API_AVAILABLE(macos(10.11), ios(9.0), watchos(2.0), tvos(9.0));
/// A transform that converts characters to their Unicode names.
FOUNDATION_EXPORT NSStringTransform const NSStringTransformToUnicodeName           API_AVAILABLE(macos(10.11), ios(9.0), watchos(2.0), tvos(9.0));
/// A transform that strips combining marks (accents or diacritics).
FOUNDATION_EXPORT NSStringTransform const NSStringTransformStripCombiningMarks     API_AVAILABLE(macos(10.11), ios(9.0), watchos(2.0), tvos(9.0));
/// A transform that strips diacritics from the string.
FOUNDATION_EXPORT NSStringTransform const NSStringTransformStripDiacritics         API_AVAILABLE(macos(10.11), ios(9.0), watchos(2.0), tvos(9.0));


/* Write to specified url or path using the specified encoding.  The optional error return is to indicate file system or encoding errors.
 */

/// Writes the contents of the receiver to the URL specified by @c url using the specified encoding.
///
/// @param url The URL to which to write the receiver. Only file URLs are supported.
/// @param useAuxiliaryFile If @c YES, the receiver is written to an auxiliary file, and then the auxiliary file is renamed to @c url.
///   The @c YES option guarantees that @c url, if it exists at all, won't be corrupted even if the system should crash during writing.
/// @param enc The encoding to use for the output.
/// @param error If there is an error, upon return contains an @c NSError object that describes the problem.
/// @return @c YES if the URL is written successfully, otherwise @c NO.
- (BOOL)writeToURL:(NSURL *)url atomically:(BOOL)useAuxiliaryFile encoding:(NSStringEncoding)enc error:(NSError **)error;

/// Writes the contents of the receiver to a file at a given path using a given encoding.
///
/// @param path The file to which to write the receiver.
/// @param useAuxiliaryFile If @c YES, the receiver is written to an auxiliary file, and then the auxiliary file is renamed to @c path.
///   The @c YES option guarantees that @c path, if it exists at all, won't be corrupted even if the system should crash during writing.
/// @param enc The encoding to use for the output.
/// @param error If there is an error, upon return contains an @c NSError object that describes the problem.
/// @return @c YES if the file is written successfully, otherwise @c NO.
- (BOOL)writeToFile:(NSString *)path atomically:(BOOL)useAuxiliaryFile encoding:(NSStringEncoding)enc error:(NSError **)error;
#endif

@property (readonly, copy) NSString *description;

/// An unsigned integer that can be used as a hash table address.
///
/// If two string objects are equal (as determined by the @c isEqualToString: method), they must have the same hash value.
/// You should not rely on this property having the same hash value across releases of macOS.
@property (readonly) NSUInteger hash;


#pragma mark *** Initializers ***

/* In general creation methods in NSString do not apply to subclassers, as subclassers are assumed to provide their own init methods which create the string in the way the subclass wishes.  Designated initializers of NSString are thus init and initWithCoder:.
*/

/// Returns an initialized @c NSString object that contains a given number of characters from a given C array of UTF-16 code units.
///
/// @param characters A C array of UTF-16 code units.
/// @param length The number of characters to use from @c characters.
/// @param freeBuffer If @c YES, the receiver releases the memory with @c free() when it no longer needs the data; if @c NO it won't.
/// @return An initialized @c NSString object. The returned object may be different from the original receiver.
- (instancetype)initWithCharactersNoCopy:(unichar *)characters length:(NSUInteger)length freeWhenDone:(BOOL)freeBuffer;	/* "NoCopy" is a hint */
- (instancetype)initWithCharactersNoCopy:(unichar *)chars length:(NSUInteger)len deallocator:(void(^_Nullable)(unichar *, NSUInteger))deallocator;

/// Returns an initialized @c NSString object that contains a given number of characters from a given C array of UTF-16 code units.
///
/// @param characters A C array of UTF-16 code units; the value must not be @c NULL.
/// @param length The number of characters to use from @c characters.
/// @return An initialized @c NSString object containing @c length characters taken from @c characters. The returned object may be different from the original receiver.
- (instancetype)initWithCharacters:(const unichar *)characters length:(NSUInteger)length;

/// Returns an @c NSString object initialized by copying the characters from a given C array of UTF8-encoded bytes.
///
/// @param nullTerminatedCString A @c NULL-terminated C array of bytes in UTF-8 encoding. This value must not be @c NULL.
/// @return An @c NSString object initialized by copying the bytes from @c nullTerminatedCString. The returned object may be different from the original receiver.
- (nullable instancetype)initWithUTF8String:(const char *)nullTerminatedCString NS_FORMAT_ARGUMENT(1);

/// Returns an @c NSString object initialized by copying the characters from another given string.
///
/// @param aString The string from which to copy characters. This value must not be @c nil.
/// @return An @c NSString object initialized by copying the characters from @c aString. The returned object may be different from the original receiver.
- (instancetype)initWithString:(NSString *)aString NS_FORMAT_ARGUMENT(1);

/// Returns an @c NSString object initialized by using a given format string as a template into which the remaining argument values are substituted.
- (instancetype)initWithFormat:(NSString *)format, ... NS_FORMAT_FUNCTION(1,2);

/// Returns an @c NSString object initialized by using a given format string as a template into which the remaining argument values are substituted without any localization.
///
/// @param format A format string. This value must not be @c nil.
/// @param argList A list of arguments to substitute into @c format.
/// @return An @c NSString object initialized by using @c format as a template into which the values in @c argList are substituted. The returned object may be different from the original receiver.
- (instancetype)initWithFormat:(NSString *)format arguments:(va_list)argList NS_FORMAT_FUNCTION(1,0);

/// Returns an @c NSString object initialized by using a given format string as a template into which the remaining argument values are substituted according to given locale.
- (instancetype)initWithFormat:(NSString *)format locale:(nullable id)locale, ... NS_FORMAT_FUNCTION(1,3);

/// Returns an @c NSString object initialized by using a given format string as a template into which the remaining argument values are substituted according to given locale information.
///
/// @param format A format string. This value must not be @c nil.
/// @param locale An @c NSLocale object specifying the locale to use. To use the current locale, pass @c [NSLocale currentLocale]. To use the system locale, pass @c nil.
/// @param argList A list of arguments to substitute into @c format.
/// @return An @c NSString object initialized by using @c format as a template into which values in @c argList are substituted according the locale information in @c locale. The returned object may be different from the original receiver.
- (instancetype)initWithFormat:(NSString *)format locale:(nullable id)locale arguments:(va_list)argList NS_FORMAT_FUNCTION(1,0);
- (nullable instancetype)initWithValidatedFormat:(NSString *)format validFormatSpecifiers:(NSString *)validFormatSpecifiers error:(NSError **)error, ... NS_FORMAT_FUNCTION(2, 4) API_AVAILABLE(macos(13.0), ios(16.0), watchos(8.0), tvos(8.0)) NS_SWIFT_UNAVAILABLE("Use string interpolations instead");
- (nullable instancetype)initWithValidatedFormat:(NSString *)format validFormatSpecifiers:(NSString *)validFormatSpecifiers locale:(nullable id)locale error:(NSError **)error, ... NS_FORMAT_FUNCTION(2, 5) API_AVAILABLE(macos(13.0), ios(16.0), watchos(8.0), tvos(8.0)) NS_SWIFT_UNAVAILABLE("Use string interpolations instead");
- (nullable instancetype)initWithValidatedFormat:(NSString *)format validFormatSpecifiers:(NSString *)validFormatSpecifiers arguments:(va_list)argList error:(NSError **)error NS_FORMAT_FUNCTION(2, 0) API_AVAILABLE(macos(13.0), ios(16.0), watchos(8.0), tvos(8.0)) NS_SWIFT_UNAVAILABLE("Use string interpolations instead");
- (nullable instancetype)initWithValidatedFormat:(NSString *)format validFormatSpecifiers:(NSString *)validFormatSpecifiers locale:(nullable id)locale arguments:(va_list)argList error:(NSError **)error NS_FORMAT_FUNCTION(2, 0) API_AVAILABLE(macos(10.13), ios(11.0), watchos(4.0), tvos(11.0)) NS_SWIFT_UNAVAILABLE("Use string interpolations instead");

/// Returns an @c NSString object initialized by converting given data into UTF-16 code units using a given encoding.
///
/// @param data An @c NSData object containing bytes in @c encoding and the default plain text format for that encoding.
/// @param encoding The encoding used by @c data.
/// @return An @c NSString object initialized by converting the bytes in @c data into UTF-16 code units using @c encoding.
///   The returned object may be different from the original receiver. Returns @c nil if the initialization fails.
- (nullable instancetype)initWithData:(NSData *)data encoding:(NSStringEncoding)encoding;

/// Returns an initialized @c NSString object containing a given number of bytes from a given buffer of bytes interpreted in a given encoding.
///
/// @param bytes A buffer of bytes interpreted in the encoding specified by @c encoding.
/// @param len The number of bytes to use from @c bytes.
/// @param encoding The character encoding applied to @c bytes.
/// @return An initialized @c NSString object containing @c length bytes from @c bytes interpreted using the encoding @c encoding.
///   The returned object may be different from the original receiver. Returns @c nil if the conversion fails.
- (nullable instancetype)initWithBytes:(const void *)bytes length:(NSUInteger)len encoding:(NSStringEncoding)encoding;

/// Returns an initialized @c NSString object that contains a given number of bytes from a given buffer of bytes interpreted in a given encoding, and optionally frees the buffer.
///
/// @param bytes A buffer of bytes interpreted in the encoding specified by @c encoding.
/// @param len The number of bytes to use from @c bytes.
/// @param encoding The character encoding of @c bytes.
/// @param freeBuffer If @c YES, the receiver releases the memory with @c free() when it no longer needs the data; if @c NO it won't.
/// @return An initialized @c NSString object. The returned object may be different from the original receiver.
- (nullable instancetype)initWithBytesNoCopy:(void *)bytes length:(NSUInteger)len encoding:(NSStringEncoding)encoding freeWhenDone:(BOOL)freeBuffer;	/* "NoCopy" is a hint */
- (nullable instancetype)initWithBytesNoCopy:(void *)bytes length:(NSUInteger)len encoding:(NSStringEncoding)encoding deallocator:(void(^_Nullable)(void *, NSUInteger))deallocator;

/// Returns an empty string.
+ (instancetype)string;
/// Returns a string created by copying the characters from another given string.
+ (instancetype)stringWithString:(NSString *)string NS_FORMAT_ARGUMENT(1);
/// Returns a string containing a given number of characters taken from a given C array of UTF-16 code units.
+ (instancetype)stringWithCharacters:(const unichar *)characters length:(NSUInteger)length;
/// Returns a string created by copying the data from a given C array of UTF8-encoded bytes.
+ (nullable instancetype)stringWithUTF8String:(const char *)nullTerminatedCString NS_FORMAT_ARGUMENT(1);
/// Returns a string created by using a given format string as a template into which the remaining argument values are substituted.
+ (instancetype)stringWithFormat:(NSString *)format, ... NS_FORMAT_FUNCTION(1,2);
/// Returns a string created by using a given format string as a template into which the remaining argument values are substituted according to the user's default locale.
+ (instancetype)localizedStringWithFormat:(NSString *)format, ... NS_FORMAT_FUNCTION(1,2);
+ (nullable instancetype)stringWithValidatedFormat:(NSString *)format validFormatSpecifiers:(NSString *)validFormatSpecifiers error:(NSError **)error, ... NS_FORMAT_FUNCTION(2,4) API_AVAILABLE(macos(10.13), ios(11.0), watchos(4.0), tvos(11.0)) NS_SWIFT_UNAVAILABLE("Use string interpolations instead");
+ (nullable instancetype)localizedStringWithValidatedFormat:(NSString *)format validFormatSpecifiers:(NSString *)validFormatSpecifiers error:(NSError **)error, ... NS_FORMAT_FUNCTION(2, 4) API_AVAILABLE(macos(10.13), ios(11.0), watchos(4.0), tvos(11.0)) NS_SWIFT_UNAVAILABLE("Use string interpolations instead");

/// Returns an @c NSString object initialized using the characters in a given C array, interpreted according to a given encoding.
///
/// @param nullTerminatedCString A C array of characters. The array must end with a @c NULL character; intermediate @c NULL characters are not allowed.
/// @param encoding The encoding of @c nullTerminatedCString.
/// @return An @c NSString object initialized using the characters from @c nullTerminatedCString. The returned object may be different from the original receiver.
- (nullable instancetype)initWithCString:(const char *)nullTerminatedCString encoding:(NSStringEncoding)encoding NS_FORMAT_ARGUMENT(1);
/// Returns a string containing the bytes in a given C array, interpreted according to a given encoding.
+ (nullable instancetype)stringWithCString:(const char *)cString encoding:(NSStringEncoding)enc NS_FORMAT_ARGUMENT(1);

/* These use the specified encoding.  If nil is returned, the optional error return indicates problem that was encountered (for instance, file system or encoding errors).
*/

/// Returns an @c NSString object initialized by reading data from a given URL interpreted using a given encoding.
///
/// @param url The URL to read.
/// @param enc The encoding of the file at @c url.
/// @param error If an error occurs, upon return contains an @c NSError object that describes the problem.
/// @return An @c NSString object initialized by reading data from @c url. Returns @c nil if the URL can't be opened or there is an encoding error.
- (nullable instancetype)initWithContentsOfURL:(NSURL *)url encoding:(NSStringEncoding)enc error:(NSError **)error;

/// Returns an @c NSString object initialized by reading data from the file at a given path using a given encoding.
///
/// @param path A path to a file.
/// @param enc The encoding of the file at @c path.
/// @param error If an error occurs, upon return contains an @c NSError object that describes the problem.
/// @return An @c NSString object initialized by reading data from the file named by @c path. Returns @c nil if the file can't be opened or there is an encoding error.
- (nullable instancetype)initWithContentsOfFile:(NSString *)path encoding:(NSStringEncoding)enc error:(NSError **)error;
/// Returns a string created by reading data from the file at a given path interpreted using a given encoding.
+ (nullable instancetype)stringWithContentsOfURL:(NSURL *)url encoding:(NSStringEncoding)enc error:(NSError **)error;
/// Returns a string created by reading data from the file at a given path interpreted using a given encoding.
+ (nullable instancetype)stringWithContentsOfFile:(NSString *)path encoding:(NSStringEncoding)enc error:(NSError **)error;

/* These try to determine the encoding, and return the encoding which was used.  Note that these methods might get "smarter" in subsequent releases of the system, and use additional techniques for recognizing encodings. If nil is returned, the optional error return indicates problem that was encountered (for instance, file system or encoding errors).
*/

/// Returns an @c NSString object initialized by reading data from a given URL and returns by reference the encoding used to interpret the data.
///
/// @param url The URL to read.
/// @param enc Upon return, if the URL is read successfully, contains the encoding used to interpret the file at @c url.
/// @param error If an error occurs, upon return contains an @c NSError object that describes the problem.
/// @return An @c NSString object initialized by reading data from @c url. Returns @c nil if the URL can't be opened or there is an encoding error.
- (nullable instancetype)initWithContentsOfURL:(NSURL *)url usedEncoding:(nullable NSStringEncoding *)enc error:(NSError **)error;

/// Returns an @c NSString object initialized by reading data from the file at a given path and returns by reference the encoding used to interpret the characters.
///
/// @param path A path to a file.
/// @param enc Upon return, if the file is read successfully, contains the encoding used to interpret the file at @c path.
/// @param error If an error occurs, upon return contains an @c NSError object that describes the problem.
/// @return An @c NSString object initialized by reading data from the file named by @c path. Returns @c nil if the file can't be opened or there is an encoding error.
- (nullable instancetype)initWithContentsOfFile:(NSString *)path usedEncoding:(nullable NSStringEncoding *)enc error:(NSError **)error;
/// Returns a string created by reading data from the file at a given URL and returns by reference the encoding used to interpret the data.
+ (nullable instancetype)stringWithContentsOfURL:(NSURL *)url usedEncoding:(nullable NSStringEncoding *)enc error:(NSError **)error;
/// Returns a string created by reading data from the file at a given path and returns by reference the encoding used to interpret the data.
+ (nullable instancetype)stringWithContentsOfFile:(NSString *)path usedEncoding:(nullable NSStringEncoding *)enc error:(NSError **)error;

@end

#if !0
typedef NSString * NSStringEncodingDetectionOptionsKey NS_TYPED_ENUM;

@interface NSString (NSStringEncodingDetection)

#pragma mark *** Encoding detection ***

/* This API is used to detect the string encoding of a given raw data. It can also do lossy string conversion. It converts the data to a string in the detected string encoding. The data object contains the raw bytes, and the option dictionary contains the hints and parameters for the analysis. The opts dictionary can be nil. If the string parameter is not NULL, the string created by the detected string encoding is returned. The lossy substitution string is emitted in the output string for characters that could not be converted when lossy conversion is enabled. The usedLossyConversion indicates if there is any lossy conversion in the resulted string. If no encoding can be detected, 0 is returned.
 
The possible items for the dictionary are:
 1) an array of suggested string encodings (without specifying the 3rd option in this list, all string encodings are considered but the ones in the array will have a higher preference; moreover, the order of the encodings in the array is important: the first encoding has a higher preference than the second one in the array)
 2) an array of string encodings not to use (the string encodings in this list will not be considered at all)
 3) a boolean option indicating whether only the suggested string encodings are considered
 4) a boolean option indicating whether lossy is allowed
 5) an option that gives a specific string to substitude for mystery bytes
 6) the current user's language
 7) a boolean option indicating whether the data is generated by Windows
 
If the values in the dictionary have wrong types (for example, the value of NSStringEncodingDetectionSuggestedEncodingsKey is not an array), an exception is thrown.
If the values in the dictionary are unknown (for example, the value in the array of suggested string encodings is not a valid encoding), the values will be ignored.
*/

/// Returns the string encoding for the given data as detected by attempting to create a string according to the specified encoding options.
///
/// @param data An @c NSData object containing bytes in an encoding to be determined.
/// @param opts Options to use when attempting to determine the string encoding.
/// @param string If a string encoding could be determined, upon return contains an @c NSString object constructed from @c data using the determined string encoding.
/// @param usedLossyConversion If a string encoding could be determined, upon return contains a @c BOOL value corresponding to whether lossy conversion was used.
/// @return An @c NSStringEncoding value, or @c 0 if a string encoding could not be determined.
+ (NSStringEncoding)stringEncodingForData:(NSData *)data
                          encodingOptions:(nullable NSDictionary<NSStringEncodingDetectionOptionsKey, id> *)opts
                          convertedString:(NSString * _Nullable * _Nullable)string
                      usedLossyConversion:(nullable BOOL *)usedLossyConversion API_AVAILABLE(macos(10.10), ios(8.0), watchos(2.0), tvos(9.0));

/* The following keys are for the option dictionary for the string encoding detection API.
*/
/// An array of `NSNumber` values containing `NSStringEncoding` values representing suggested encodings. If not present, all encodings are weighted the same.
FOUNDATION_EXPORT NSStringEncodingDetectionOptionsKey const NSStringEncodingDetectionSuggestedEncodingsKey           API_AVAILABLE(macos(10.10), ios(8.0), watchos(2.0), tvos(9.0));
/// An array of `NSNumber` values containing `NSStringEncoding` values representing disallowed encodings. If not present, all encodings are considered.
FOUNDATION_EXPORT NSStringEncodingDetectionOptionsKey const NSStringEncodingDetectionDisallowedEncodingsKey          API_AVAILABLE(macos(10.10), ios(8.0), watchos(2.0), tvos(9.0));
/// An `NSNumber` boolean value. If `YES`, only the suggested encodings are used. Default is `NO`.
FOUNDATION_EXPORT NSStringEncodingDetectionOptionsKey const NSStringEncodingDetectionUseOnlySuggestedEncodingsKey    API_AVAILABLE(macos(10.10), ios(8.0), watchos(2.0), tvos(9.0));
/// An `NSNumber` boolean value. If `YES`, lossy encodings may be used. Default is `YES`.
FOUNDATION_EXPORT NSStringEncodingDetectionOptionsKey const NSStringEncodingDetectionAllowLossyKey                   API_AVAILABLE(macos(10.10), ios(8.0), watchos(2.0), tvos(9.0));
/// An `NSNumber` boolean value. If `YES`, Windows encodings are considered. Default is `NO`.
FOUNDATION_EXPORT NSStringEncodingDetectionOptionsKey const NSStringEncodingDetectionFromWindowsKey                  API_AVAILABLE(macos(10.10), ios(8.0), watchos(2.0), tvos(9.0));
/// An `NSString` value used as a substitute for characters that cannot be represented in the encoding. Default is U+FFFD.
FOUNDATION_EXPORT NSStringEncodingDetectionOptionsKey const NSStringEncodingDetectionLossySubstitutionKey            API_AVAILABLE(macos(10.10), ios(8.0), watchos(2.0), tvos(9.0));
/// An `NSString` value containing an ISO language code. If present, the language is used to aid in encoding detection.
FOUNDATION_EXPORT NSStringEncodingDetectionOptionsKey const NSStringEncodingDetectionLikelyLanguageKey               API_AVAILABLE(macos(10.10), ios(8.0), watchos(2.0), tvos(9.0));

@end
#endif



@interface NSString (NSItemProvider) <NSItemProviderReading, NSItemProviderWriting>
@end


/// A dynamic plain-text Unicode string object.
///
/// In Swift, you can use this type instead of a <doc://com.apple.documentation/documentation/swift/string> in cases that require reference semantics.
///
/// The `NSMutableString` class declares the programmatic interface to an object that manages a mutable string—that is, a string whose contents can be edited—that conceptually represents an array of Unicode characters. To construct and manage an immutable string—or a string that cannot be changed after it has been created—use an object of the ``NSString`` class.
///
/// The `NSMutableString` class adds one primitive method—``replaceCharacters(in:with:)``—to the basic string-handling behavior inherited from `NSString`. All other methods that modify a string work through this method. For example, ``insert(_:at:)`` simply replaces the characters in a range of `0` length, while ``deleteCharacters(in:)`` replaces the characters in a given range with no characters.
///
/// NSMutableString is "toll-free bridged" with its Core Foundation counterpart, <doc://com.apple.documentation/documentation/corefoundation/cfmutablestring>. See [Toll-Free Bridging](https://developer.apple.com/library/archive/documentation/General/Conceptual/CocoaEncyclopedia/Toll-FreeBridgin/Toll-FreeBridgin.html#//apple_ref/doc/uid/TP40010810-CH2) for more information.
@interface NSMutableString : NSString

#pragma mark *** Mutable string ***

/* NSMutableString primitive (funnel) method. See below for the other mutation methods.
*/

/// Replaces the characters from @c range with those in @c aString.
///
/// @param range The range of characters to replace. @c range must not exceed the bounds of the receiver.
/// @param aString The string with which to replace the characters in @c range. @c aString must not be @c nil.
- (void)replaceCharactersInRange:(NSRange)range withString:(NSString *)aString;

@end

@interface NSMutableString (NSMutableStringExtensionMethods)

/* Additional mutation methods.  For subclassers these are all available implemented in terms of the primitive replaceCharactersInRange:range: method.
*/

/// Inserts into the receiver the characters of a given string at a given location.
///
/// @param aString The string to insert into the receiver. @c aString must not be @c nil.
/// @param loc The location at which @c aString is inserted. The location must not exceed the bounds of the receiver.
- (void)insertString:(NSString *)aString atIndex:(NSUInteger)loc;

/// Removes from the receiver the characters in a given range.
///
/// @param range The range of characters to delete. @c range must not exceed the bounds of the receiver.
- (void)deleteCharactersInRange:(NSRange)range;

/// Adds to the end of the receiver the characters of a given string.
///
/// @param aString The string to append to the receiver. @c aString must not be @c nil.
- (void)appendString:(NSString *)aString;

/// Adds a constructed string to the receiver.
///
/// @param format A format string. This value must not be @c nil.
- (void)appendFormat:(NSString *)format, ... NS_FORMAT_FUNCTION(1,2);

/// Replaces the characters of the receiver with those in a given string.
///
/// @param aString The string with which to replace the receiver's content. @c aString must not be @c nil.
- (void)setString:(NSString *)aString;

/* This method replaces all occurrences of the target string with the replacement string, in the specified range of the receiver string, and returns the number of replacements. NSBackwardsSearch means the search is done from the end of the range (the results could be different); NSAnchoredSearch means only anchored (but potentially multiple) instances will be replaced. NSLiteralSearch and NSCaseInsensitiveSearch also apply. NSNumericSearch is ignored. Use NSMakeRange(0, [receiver length]) to process whole string. If NSRegularExpressionSearch is specified, the replacement is treated as a template, as in the corresponding NSRegularExpression methods, and no other options can apply except NSCaseInsensitiveSearch and NSAnchoredSearch.
*/

/// Replaces all occurrences of a given string in a given range with another given string, returning the number of replacements.
///
/// @param target The string to replace.
/// @param replacement The string with which to replace @c target.
/// @param options A mask specifying search options.
/// @param searchRange The range of characters to replace. @c searchRange must not exceed the bounds of the receiver.
///   Specify @c NSMakeRange(0, [receiver length]) to process the entire string.
/// @return The number of replacements made.
- (NSUInteger)replaceOccurrencesOfString:(NSString *)target withString:(NSString *)replacement options:(NSStringCompareOptions)options range:(NSRange)searchRange;

#if !0
/* Perform string transliteration.  The transformation represented by transform is applied to the given range of string in place. Only the specified range will be modified, but the transform may look at portions of the string outside that range for context. If supplied, resultingRange is modified to reflect the new range corresponding to the original range. reverse indicates that the inverse transform should be used instead, if it exists. Attempting to use an invalid transform identifier or reverse an irreversible transform will return NO; otherwise YES is returned, even if no characters are actually transformed. You can pass one of the predefined transforms listed above (NSStringTransformLatinToKatakana, etc), or any valid ICU transform ID as defined in the ICU User Guide. Arbitrary ICU transform rules are not supported.
*/

/// Transliterates the receiver by applying a specified ICU string transform.
///
/// @param transform The transformation to apply. If the specified transform does not exist, the receiver is not modified, and this method returns @c NO.
/// @param reverse Whether an inverse transform should be used. If the specified transform does not have an inverse, the receiver is not modified, and this method returns @c NO.
/// @param range The range of the string to transform. @c range must not exceed the bounds of the receiver.
/// @param resultingRange If the transform was successfully applied, upon return contains the range of the transformed string.
/// @return @c YES if the transform was successfully applied. Otherwise, @c NO.
- (BOOL)applyTransform:(NSStringTransform)transform reverse:(BOOL)reverse range:(NSRange)range updatedRange:(nullable NSRangePointer)resultingRange API_AVAILABLE(macos(10.11), ios(9.0), watchos(2.0), tvos(9.0));
#endif

/* In addition to these two, NSMutableString responds properly to all NSString creation methods.
 */

/// Returns an @c NSMutableString object initialized with initial storage for a given number of characters.
///
/// @param capacity The number of characters the string is expected to initially contain. The value does not limit the length of the string.
/// @return An initialized @c NSMutableString object with initial storage for @c capacity characters.
- (NSMutableString *)initWithCapacity:(NSUInteger)capacity;

/// Returns an empty @c NSMutableString object with initial storage for a given number of characters.
///
/// @param capacity The number of characters the string is expected to initially contain. The value does not limit the length of the string.
/// @return An empty @c NSMutableString object with initial storage for @c capacity characters.
+ (NSMutableString *)stringWithCapacity:(NSUInteger)capacity;

@end


/// Name of an exception raised when a string encoding conversion fails.
FOUNDATION_EXPORT NSExceptionName const NSCharacterConversionException;
/// Name of an exception raised by `-propertyList` when parsing fails.
FOUNDATION_EXPORT NSExceptionName const NSParseErrorException; // raised by -propertyList
/// Maximum number of characters in an `NSString` object.
#define NSMaximumStringLength	(INT_MAX-1)

#pragma mark *** Deprecated/discouraged APIs ***

@interface NSString (NSExtendedStringPropertyListParsing)

/* These methods are no longer recommended since they do not work with property lists and strings files in binary plist format. Please use the APIs in NSPropertyList.h instead.
 */

/// Parses the receiver as a text representation of a property list, returning an @c NSString, @c NSData, @c NSArray, or @c NSDictionary object, according to the topmost element.
///
/// @return A property list representation of the receiver.
- (id)propertyList;

/// Returns a dictionary object initialized with the keys and values found in the receiver.
///
/// @return A dictionary object initialized with the keys and values found in the receiver.
///   The receiver must contain text in the format used for @c .strings files.
- (nullable NSDictionary *)propertyListFromStringsFileFormat;

@end

@interface NSString (NSStringDeprecated)

/* The following methods are deprecated and will be removed from this header file in the near future. These methods use NSString.defaultCStringEncoding as the encoding to convert to, which means the results depend on the user's language and potentially other settings. This might be appropriate in some cases, but often these methods are misused, resulting in issues when running in languages other then English. UTF8String in general is a much better choice when converting arbitrary NSStrings into 8-bit representations. Additional potential replacement methods are being introduced in NSString as appropriate.
*/

/// Returns a pointer to the receiver's contents as a C string in the default C-string encoding.
/// @deprecated Use @c cStringUsingEncoding: instead.
- (nullable const char *)cString NS_RETURNS_INNER_POINTER API_DEPRECATED("Use -cStringUsingEncoding: instead", macos(10.0,10.4), ios(2.0,2.0), watchos(2.0,2.0), tvos(9.0,9.0));

/// Returns a pointer to a lossy C-string representation of the receiver in the default C-string encoding.
/// @deprecated Use @c cStringUsingEncoding: instead.
- (nullable const char *)lossyCString NS_RETURNS_INNER_POINTER API_DEPRECATED("Use -cStringUsingEncoding: instead", macos(10.0,10.4), ios(2.0,2.0), watchos(2.0,2.0), tvos(9.0,9.0));

/// Returns the length of the receiver's C-string representation in the default C-string encoding.
/// @deprecated Use @c lengthOfBytesUsingEncoding: instead.
- (NSUInteger)cStringLength API_DEPRECATED("Use -lengthOfBytesUsingEncoding: instead", macos(10.0,10.4), ios(2.0,2.0), watchos(2.0,2.0), tvos(9.0,9.0));

/// Copies the receiver's C-string representation into a given buffer.
/// @deprecated Use @c getCString:maxLength:encoding: instead.
- (void)getCString:(char *)bytes API_DEPRECATED("Use -getCString:maxLength:encoding: instead", macos(10.0,10.4), ios(2.0,2.0), watchos(2.0,2.0), tvos(9.0,9.0));
- (void)getCString:(char *)bytes maxLength:(NSUInteger)maxLength API_DEPRECATED("Use -getCString:maxLength:encoding: instead", macos(10.0,10.4), ios(2.0,2.0), watchos(2.0,2.0), tvos(9.0,9.0));
- (void)getCString:(char *)bytes maxLength:(NSUInteger)maxLength range:(NSRange)aRange remainingRange:(nullable NSRangePointer)leftoverRange API_DEPRECATED("Use -getCString:maxLength:encoding: instead", macos(10.0,10.4), ios(2.0,2.0), watchos(2.0,2.0), tvos(9.0,9.0));

/// Writes the contents of the receiver to the file specified by @c path.
/// @deprecated Use @c writeToFile:atomically:encoding:error: instead.
- (BOOL)writeToFile:(NSString *)path atomically:(BOOL)useAuxiliaryFile API_DEPRECATED("Use -writeToFile:atomically:encoding:error: instead", macos(10.0,10.4), ios(2.0,2.0), watchos(2.0,2.0), tvos(9.0,9.0));

/// Writes the contents of the receiver to the URL specified by @c url.
/// @deprecated Use @c writeToURL:atomically:encoding:error: instead.
- (BOOL)writeToURL:(NSURL *)url atomically:(BOOL)atomically API_DEPRECATED("Use -writeToURL:atomically:encoding:error: instead", macos(10.0,10.4), ios(2.0,2.0), watchos(2.0,2.0), tvos(9.0,9.0));

/// Returns an @c NSString object initialized by reading data from the file named by @c path.
/// @deprecated Use @c initWithContentsOfFile:encoding:error: instead.
- (nullable id)initWithContentsOfFile:(NSString *)path API_DEPRECATED("Use -initWithContentsOfFile:encoding:error: instead", macos(10.0,10.4), ios(2.0,2.0), watchos(2.0,2.0), tvos(9.0,9.0));

/// Returns an @c NSString object initialized by reading data from the URL named by @c url.
/// @deprecated Use @c initWithContentsOfURL:encoding:error: instead.
- (nullable id)initWithContentsOfURL:(NSURL *)url API_DEPRECATED("Use -initWithContentsOfURL:encoding:error: instead", macos(10.0,10.4), ios(2.0,2.0), watchos(2.0,2.0), tvos(9.0,9.0));
+ (nullable id)stringWithContentsOfFile:(NSString *)path API_DEPRECATED("Use +stringWithContentsOfFile:encoding:error: instead", macos(10.0,10.4), ios(2.0,2.0), watchos(2.0,2.0), tvos(9.0,9.0));
+ (nullable id)stringWithContentsOfURL:(NSURL *)url API_DEPRECATED("Use +stringWithContentsOfURL:encoding:error: instead", macos(10.0,10.4), ios(2.0,2.0), watchos(2.0,2.0), tvos(9.0,9.0));

- (nullable id)initWithCStringNoCopy:(char *)bytes length:(NSUInteger)length freeWhenDone:(BOOL)freeBuffer API_DEPRECATED("Use -initWithCString:encoding: instead", macos(10.0,10.4), ios(2.0,2.0), watchos(2.0,2.0), tvos(9.0,9.0));
- (nullable id)initWithCString:(const char *)bytes length:(NSUInteger)length API_DEPRECATED("Use -initWithCString:encoding: instead", macos(10.0,10.4), ios(2.0,2.0), watchos(2.0,2.0), tvos(9.0,9.0));
- (nullable id)initWithCString:(const char *)bytes API_DEPRECATED("Use -initWithCString:encoding: instead", macos(10.0,10.4), ios(2.0,2.0), watchos(2.0,2.0), tvos(9.0,9.0));
+ (nullable id)stringWithCString:(const char *)bytes length:(NSUInteger)length API_DEPRECATED("Use +stringWithCString:encoding:", macos(10.0,10.4), ios(2.0,2.0), watchos(2.0,2.0), tvos(9.0,9.0));
+ (nullable id)stringWithCString:(const char *)bytes API_DEPRECATED("Use +stringWithCString:encoding: instead", macos(10.0,10.4), ios(2.0,2.0), watchos(2.0,2.0), tvos(9.0,9.0));

/// Copies all characters from the receiver into a given buffer.
///
/// @param buffer Upon return, contains the characters from the receiver. @c buffer must be large enough to contain all characters in the string.
/// @deprecated This method is unsafe because it could potentially cause buffer overruns. Use @c getCharacters:range: instead.
- (void)getCharacters:(unichar *)buffer;

@end

NS_ENUM(NSStringEncoding) {
    /// Installation-specific encoding.
    NSProprietaryStringEncoding = 65536
};

/* The rest of this file is bookkeeping stuff that has to be here. Don't use this stuff, don't refer to it.
*/
#if !defined(_OBJC_UNICHAR_H_)
#define _OBJC_UNICHAR_H_
#endif
#define NS_UNICHAR_IS_EIGHT_BIT 0

NS_SWIFT_UNAVAILABLE("Use String or NSString instead.")
@interface NSSimpleCString : NSString {
@package
    char *bytes;
    int numBytes;
#if __LP64__
    int _unused;
#endif
}
@end

NS_SWIFT_UNAVAILABLE("Use String or NSString instead.")
@interface NSConstantString : NSSimpleCString
@end

#if __OBJC2__
#else
extern void *_NSConstantStringClassReference;
#endif

NS_HEADER_AUDIT_END(nullability, sendability)
