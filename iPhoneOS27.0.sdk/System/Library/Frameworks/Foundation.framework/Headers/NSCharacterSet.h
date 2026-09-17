/*	NSCharacterSet.h
	Copyright (c) 1994-2019, Apple Inc. All rights reserved.
*/

#import <CoreFoundation/CFCharacterSet.h>
#import <Foundation/NSObject.h>
#import <Foundation/NSRange.h>
#import <Foundation/NSString.h>

@class NSData;

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

/// Specifies the lower bound for a Unicode character range reserved for Apple's corporate use (the range is `0xF400`–`0xF8FF`).
enum {
    NSOpenStepUnicodeReservedBase = 0xF400
};

/// An object representing a fixed set of Unicode character values for use in search operations.
///
/// In Swift, this bridges to a ``CharacterSet``; use ``NSCharacterSet`` when you need reference semantics or other Foundation-specific behavior.
///
/// An `NSCharacterSet` object represents a set of Unicode-compliant characters. `NSString` and `NSScanner` objects use `NSCharacterSet` objects to group characters together for searching operations, so that they can find any of a particular set of characters during a search. The cluster's two public classes, `NSCharacterSet` and ``NSMutableCharacterSet``, declare the programmatic interface for static and dynamic character sets, respectively.
///
/// The objects you create using these classes are referred to as character set objects (and when no confusion will result, merely as character sets). Because of the nature of class clusters, character set objects aren't actual instances of the `NSCharacterSet` or `NSMutableCharacterSet` classes but of one of their private subclasses. Although a character set object's class is private, its interface is public, as declared by these abstract superclasses, `NSCharacterSet` and `NSMutableCharacterSet`. The character set classes adopt the `NSCopying` and `NSMutableCopying` protocols, making it convenient to convert a character set of one type to the other.
///
/// The `NSCharacterSet` class declares the programmatic interface for an object that manages a set of Unicode characters (see the ``NSString`` class cluster specification for information on Unicode). `NSCharacterSet`'s principal primitive method, ``characterIsMember(_:)``, provides the basis for all other instance methods in its interface. A subclass of `NSCharacterSet` needs only to implement this method, plus ``NSMutableCopying/mutableCopy(with:)``, for proper behavior. For optimal performance, a subclass should also override ``bitmapRepresentation``, which otherwise works by invoking ``characterIsMember(_:)`` for every possible Unicode value.
///
/// `NSCharacterSet` is "toll-free bridged" with its Core Foundation counterpart, <doc://com.apple.documentation/documentation/corefoundation/cfcharacterset>. See [Toll-Free Bridging](https://developer.apple.com/library/archive/documentation/General/Conceptual/CocoaEncyclopedia/Toll-FreeBridgin/Toll-FreeBridgin.html#//apple_ref/doc/uid/TP40010810-CH2) for more information on toll-free bridging.
///
/// > Important:
/// > The Swift overlay to the Foundation framework provides the ``CharacterSet`` structure, which bridges to the ``NSCharacterSet`` class and its mutable subclass, ``NSMutableCharacterSet``. For more information about value types, see <doc://com.apple.documentation/documentation/swift/working-with-foundation-types>.
@interface NSCharacterSet : NSObject <NSCopying, NSMutableCopying, NSSecureCoding>

/// A character set containing the characters in Unicode General Category Cc and Cf.
///
/// These characters include, for example, the soft hyphen (`U+00AD`), control characters to support bi-directional text, and IETF language tag characters.
@property (readonly, class, copy) NSCharacterSet *controlCharacterSet;

/// A character set containing the characters in Unicode General Category Zs and `CHARACTER TABULATION` (`U+0009`).
///
/// This set doesn't contain the newline or carriage return characters.
@property (readonly, class, copy) NSCharacterSet *whitespaceCharacterSet;

/// A character set containing characters in Unicode General Category Z\*, `U+000A` ~ `U+000D`, and `U+0085`.
@property (readonly, class, copy) NSCharacterSet *whitespaceAndNewlineCharacterSet;

/// A character set containing the characters in the category of Decimal Numbers.
///
/// Informally, this set is the set of all characters used to represent the decimal values `0` through `9`. These characters include, for example, the decimal digits of the Indic scripts and Arabic.
@property (readonly, class, copy) NSCharacterSet *decimalDigitCharacterSet;

/// A character set containing the characters in Unicode General Category L\* & M\*.
///
/// Informally, this set is the set of all characters used as letters of alphabets and ideographs.
@property (readonly, class, copy) NSCharacterSet *letterCharacterSet;

/// A character set containing the characters in Unicode General Category Ll.
///
/// Informally, this set is the set of all characters used as lowercase letters in alphabets that make case distinctions.
@property (readonly, class, copy) NSCharacterSet *lowercaseLetterCharacterSet;

/// A character set containing the characters in Unicode General Category Lu and Lt.
///
/// Informally, this set is the set of all characters used as uppercase letters in alphabets that make case distinctions.
@property (readonly, class, copy) NSCharacterSet *uppercaseLetterCharacterSet;

/// A character set containing the characters in Unicode General Category M\*.
///
/// This set is also defined as all legal Unicode characters with a non-spacing priority greater than `0`. Informally, this set is the set of all characters used as modifiers of base characters.
@property (readonly, class, copy) NSCharacterSet *nonBaseCharacterSet;

/// A character set containing the characters in Unicode General Categories L\*, M\*, and N\*.
///
/// Informally, this set is the set of all characters used as basic units of alphabets, syllabaries, ideographs, and digits.
@property (readonly, class, copy) NSCharacterSet *alphanumericCharacterSet;

/// A character set containing individual Unicode characters that can also be represented as composed character sequences (such as for letters with accents), by the definition of "standard decomposition" in version 3.2 of the Unicode character encoding standard.
///
/// These characters include compatibility characters as well as pre-composed characters.
///
/// > Note: This character set doesn't currently include the Hangul characters defined in version 2.0 of the Unicode standard.
@property (readonly, class, copy) NSCharacterSet *decomposableCharacterSet;

/// A character set containing values in the category of Non-Characters or that have not yet been defined in version 3.2 of the Unicode standard.
@property (readonly, class, copy) NSCharacterSet *illegalCharacterSet;

/// A character set containing the characters in Unicode General Category P\*.
///
/// Informally, this set is the set of all non-whitespace characters used to separate linguistic units in scripts, such as periods, dashes, parentheses, and so on.
@property (readonly, class, copy) NSCharacterSet *punctuationCharacterSet;

/// A character set containing the characters in Unicode General Category Lt.
@property (readonly, class, copy) NSCharacterSet *capitalizedLetterCharacterSet;

/// A character set containing the characters in Unicode General Category S\*.
///
/// These characters include, for example, the dollar sign (`$`) and the plus (`+`) sign.
@property (readonly, class, copy) NSCharacterSet *symbolCharacterSet;

/// A character set containing the newline characters (`U+000A` ~ `U+000D`, `U+0085`, `U+2028`, and `U+2029`).
@property (readonly, class, copy) NSCharacterSet *newlineCharacterSet API_AVAILABLE(macos(10.5), ios(2.0), watchos(2.0), tvos(9.0));

/// Returns a character set containing characters with Unicode values in a given range.
///
/// This code excerpt creates a character set object containing the lowercase English alphabetic characters:
///
/// ```objc
/// NSRange lcEnglishRange;
/// NSCharacterSet *lcEnglishLetters;
///
/// lcEnglishRange.location = (unsigned int)'a';
/// lcEnglishRange.length = 26;
/// lcEnglishLetters = [NSCharacterSet characterSetWithRange:lcEnglishRange];
/// ```
///
/// - Parameter aRange: A range of Unicode values. `aRange.location` is the value of the first character to return; `aRange.location + aRange.length - 1` is the value of the last.
/// - Returns: A character set containing characters whose Unicode values are given by `aRange`. If `aRange.length` is `0`, returns an empty character set.
+ (NSCharacterSet *)characterSetWithRange:(NSRange)aRange;

/// Returns a character set containing the characters in a given string.
///
/// - Parameter aString: A string containing characters for the new character set.
/// - Returns: A character set containing the characters in `aString`. Returns an empty character set if `aString` is empty.
+ (NSCharacterSet *)characterSetWithCharactersInString:(NSString *)aString;

/// Returns a character set containing characters determined by a given bitmap representation.
///
/// This method is useful for creating a character set object with data from a file or other external data source.
///
/// A raw bitmap representation of a character set is a byte array with the first 2^16 bits (that is, 8192 bytes) representing the code point range of the Basic Multilingual Plane (BMP), such that the value of the bit at position n represents the presence in the character set of the character with decimal Unicode value n. A bitmap representation may contain zero to sixteen additional 8192 byte segments for each additional Unicode plane containing a character in a character set, with each 8192 byte segment prepended with a single plane index byte.
///
/// To add a character in the Basic Multilingual Plane (BMP) with decimal Unicode value n to a raw bitmap representation, you might do the following:
///
/// ```objc
/// unsigned char bitmapRep[8192];
/// bitmapRep[n >> 3] |= (((unsigned int)1) << (n & 7));
/// ```
///
/// To remove that character:
///
/// ```objc
/// bitmapRep[n >> 3] &= ~(((unsigned int)1) << (n & 7));
/// ```
///
/// - Parameter data: A bitmap representation of a character set.
/// - Returns: A character set containing characters determined by `data`.
+ (NSCharacterSet *)characterSetWithBitmapRepresentation:(NSData *)data;

/// Returns a character set read from the bitmap representation stored in the file at a given path.
///
/// This method doesn't use filenames to check for the uniqueness of the character sets it creates. To prevent duplication of character sets in memory, cache them and make them available through an API that checks whether the requested set has already been loaded.
///
/// To read a bitmap representation from any file, use the `NSData` method `dataWithContentsOfFile:options:error:` and pass the result to ``characterSetWithBitmapRepresentation:``.
///
/// - Parameter fName: A path to a file containing a bitmap representation of a character set. The path name must end with the extension `.bitmap`.
/// - Returns: A character set read from the bitmap representation stored in the file at `fName`.
+ (nullable NSCharacterSet *)characterSetWithContentsOfFile:(NSString *)fName;

- (instancetype) initWithCoder:(NSCoder *)coder NS_DESIGNATED_INITIALIZER;

/// Returns a Boolean value that indicates whether a given character is in the receiver.
///
/// - Parameter aCharacter: The character to test for membership of the receiver.
/// - Returns: `YES` if `aCharacter` is in the receiving character set, otherwise `NO`.
- (BOOL)characterIsMember:(unichar)aCharacter;

/// An `NSData` object encoding the receiver in binary format.
///
/// This format is suitable for saving to a file or otherwise transmitting or archiving.
///
/// A raw bitmap representation of a character set is a byte array with the first 2^16 bits (that is, 8192 bytes) representing the code point range of the Basic Multilingual Plane (BMP), such that the value of the bit at position n represents the presence in the character set of the character with decimal Unicode value n. A bitmap representation may contain zero to sixteen additional 8192 byte segments for each additional Unicode plane containing a character in a character set, with each 8192 byte segment prepended with a single plane index byte.
///
/// For example, a character set containing only Basic Latin (ASCII) characters, which are contained by the Basic Multilingual Plane (BMP, plane 0), has a bitmap representation with a size of 8192 bytes, whereas a character set containing both Basic Latin (ASCII) characters and emoji characters, which are contained by the Supplementary Multilingual Plane (SMP, plane 1), has a bitmap representation with a size of 16385 bytes (8192 bytes for BMP, followed by the byte `0x01` for the plane index of SMP, followed by 8192 bytes for SMP).
///
/// To test for the presence of a character in the Basic Multilingual Plane (BMP) with decimal Unicode value n in a raw bitmap representation, you might do the following:
///
/// ```objc
/// unsigned char bitmapRep[8192];
/// if (bitmapRep[n >> 3] & (((unsigned int)1) << (n  & 7))) {
///     /* Character is present. */
/// }
/// ```
@property (readonly, copy) NSData *bitmapRepresentation;

/// A character set containing only characters that don't exist in the receiver.
///
/// Using the inverse of an immutable character set is much more efficient than inverting a mutable character set.
@property (readonly, copy) NSCharacterSet *invertedSet;


/// Returns a Boolean value that indicates whether a given long character is a member of the receiver.
///
/// This method supports the specification of 32-bit characters.
///
/// - Parameter theLongChar: A UTF32 character.
/// - Returns: `YES` if `theLongChar` is in the receiver, otherwise `NO`.
- (BOOL)longCharacterIsMember:(UTF32Char)theLongChar;

/// Returns a Boolean value that indicates whether the receiver is a superset of another given character set.
///
/// - Parameter theOtherSet: A character set.
/// - Returns: `YES` if the receiver is a superset of `theOtherSet`, otherwise `NO`.
- (BOOL)isSupersetOfSet:(NSCharacterSet *)theOtherSet;

/// Returns a Boolean value that indicates whether the receiver has at least one member in a given character plane.
///
/// This method makes it easier to find the plane containing the members of the current character set. The Basic Multilingual Plane (BMP) is plane `0`.
///
/// - Parameter thePlane: A character plane.
/// - Returns: `YES` if the receiver has at least one member in `thePlane`, otherwise `NO`.
- (BOOL)hasMemberInPlane:(uint8_t)thePlane;
@end

/// An object representing a mutable set of Unicode character values for use in search operations.
///
/// In Swift, this object bridges to ``CharacterSet``; use ``NSMutableCharacterSet`` when you need reference semantics or other Foundation-specific behavior.
///
/// The `NSMutableCharacterSet` class declares the programmatic interface to objects that manage a modifiable set of Unicode characters. You can add or remove characters from a mutable character set as numeric values in `NSRange` structures or as character values in strings, combine character sets by union or intersection, and invert a character set.
///
/// Mutable character sets are less efficient to use than immutable character sets. If you don't need to change a character set after creating it, create an immutable copy with `copy` and use that.
///
/// `NSMutableCharacterSet` defines no primitive methods. Subclasses must implement all methods declared by this class in addition to the primitives of ``NSCharacterSet``. They must also implement ``NSMutableCopying/mutableCopy(with:)``.
///
/// `NSMutableCharacterSet` is "toll-free bridged" with its Core Foundation counterpart, <doc://com.apple.documentation/documentation/corefoundation/cfmutablecharacterset>. See [Toll-Free Bridging](https://developer.apple.com/library/archive/documentation/General/Conceptual/CocoaEncyclopedia/Toll-FreeBridgin/Toll-FreeBridgin.html#//apple_ref/doc/uid/TP40010810-CH2) for more information.
///
/// > Important:
/// > The Swift overlay to the Foundation framework provides the ``CharacterSet`` structure, which bridges to the ``NSMutableCharacterSet`` class and its immutable superclass, ``NSCharacterSet``.  For more information about value types, see <doc://com.apple.documentation/documentation/swift/working-with-foundation-types>.
@interface NSMutableCharacterSet : NSCharacterSet <NSCopying, NSMutableCopying, NSSecureCoding>

/// Adds to the receiver the characters whose Unicode values are in a given range.
///
/// This code excerpt adds to a character set the lowercase English alphabetic characters:
///
/// ```objc
/// NSMutableCharacterSet *aCharacterSet = [[NSMutableCharacterSet alloc] init];
/// NSRange lcEnglishRange;
///
/// lcEnglishRange.location = (unsigned int)'a';
/// lcEnglishRange.length = 26;
/// [aCharacterSet addCharactersInRange:lcEnglishRange];
/// ```
///
/// - Parameter aRange: The range of characters to add. `aRange.location` is the value of the first character to add; `aRange.location + aRange.length - 1` is the value of the last. If `aRange.length` is `0`, this method has no effect.
- (void)addCharactersInRange:(NSRange)aRange;

/// Removes from the receiver the characters whose Unicode values are in a given range.
///
/// - Parameter aRange: The range of characters to remove. `aRange.location` is the value of the first character to remove; `aRange.location + aRange.length - 1` is the value of the last. If `aRange.length` is `0`, this method has no effect.
- (void)removeCharactersInRange:(NSRange)aRange;

/// Adds to the receiver the characters in a given string.
///
/// This method has no effect if `aString` is empty.
///
/// - Parameter aString: The characters to add to the receiver.
- (void)addCharactersInString:(NSString *)aString;

/// Removes from the receiver the characters in a given string.
///
/// This method has no effect if `aString` is empty.
///
/// - Parameter aString: The characters to remove from the receiver.
- (void)removeCharactersInString:(NSString *)aString;

/// Modifies the receiver so it contains all characters that exist in either the receiver or another set.
- (void)formUnionWithCharacterSet:(NSCharacterSet *)otherSet;

/// Modifies the receiver so it contains only characters that exist in both the receiver and another set.
///
/// - Parameter otherSet: The character set with which to perform the intersection.
- (void)formIntersectionWithCharacterSet:(NSCharacterSet *)otherSet;

/// Replaces all the characters in the receiver with all the characters it didn't previously contain.
///
/// Inverting a mutable character set, whether by `invert` or by `invertedSet`, is much less efficient than inverting an immutable character set with `invertedSet`.
- (void)invert;

/// Returns a mutable character set containing the characters in Unicode General Category Cc and Cf.
+ (NSMutableCharacterSet *)controlCharacterSet;
/// Returns a mutable character set containing the characters in Unicode General Category Zs and `CHARACTER TABULATION` (`U+0009`).
+ (NSMutableCharacterSet *)whitespaceCharacterSet;
/// Returns a mutable character set containing characters in Unicode General Category Z\*, `U+000A` ~ `U+000D`, and `U+0085`.
+ (NSMutableCharacterSet *)whitespaceAndNewlineCharacterSet;
/// Returns a mutable character set containing the characters in the category of decimal numbers.
+ (NSMutableCharacterSet *)decimalDigitCharacterSet;
/// Returns a mutable character set containing the characters in Unicode General Category L\* & M\*.
+ (NSMutableCharacterSet *)letterCharacterSet;
/// Returns a mutable character set containing the characters in Unicode General Category Ll.
+ (NSMutableCharacterSet *)lowercaseLetterCharacterSet;
/// Returns a mutable character set containing the characters in Unicode General Category Lu and Lt.
+ (NSMutableCharacterSet *)uppercaseLetterCharacterSet;
/// Returns a mutable character set containing the characters in Unicode General Category M\*.
+ (NSMutableCharacterSet *)nonBaseCharacterSet;
/// Returns a mutable character set containing the characters in Unicode General Categories L\*, M\*, and N\*.
+ (NSMutableCharacterSet *)alphanumericCharacterSet;
/// Returns a mutable character set containing individual Unicode characters that can also be represented as composed character sequences (such as for letters with accents), by the definition of "standard decomposition" in version 3.2 of the Unicode character encoding standard.
+ (NSMutableCharacterSet *)decomposableCharacterSet;
/// Returns a mutable character set containing values in the category of Non-Characters or that have not yet been defined in version 3.2 of the Unicode standard.
+ (NSMutableCharacterSet *)illegalCharacterSet;
/// Returns a mutable character set containing the characters in Unicode General Category P\*.
+ (NSMutableCharacterSet *)punctuationCharacterSet;
/// Returns a mutable character set containing the characters in Unicode General Category Lt.
+ (NSMutableCharacterSet *)capitalizedLetterCharacterSet;
/// Returns a mutable character set containing the characters in Unicode General Category S\*.
+ (NSMutableCharacterSet *)symbolCharacterSet;
/// Returns a mutable character set containing the newline characters (`U+000A` ~ `U+000D`, `U+0085`, `U+2028`, and `U+2029`).
+ (NSMutableCharacterSet *)newlineCharacterSet API_AVAILABLE(macos(10.5), ios(2.0), watchos(2.0), tvos(9.0));

/// Returns a mutable character set containing characters with Unicode values in a given range.
+ (NSMutableCharacterSet *)characterSetWithRange:(NSRange)aRange;
/// Returns a mutable character set containing the characters in a given string.
+ (NSMutableCharacterSet *)characterSetWithCharactersInString:(NSString *)aString;
/// Returns a mutable character set containing characters determined by a given bitmap representation.
+ (NSMutableCharacterSet *)characterSetWithBitmapRepresentation:(NSData *)data;
/// Returns a mutable character set read from the bitmap representation stored in the file at a given path.
+ (nullable NSMutableCharacterSet *)characterSetWithContentsOfFile:(NSString *)fName;

@end

NS_HEADER_AUDIT_END(nullability, sendability)
