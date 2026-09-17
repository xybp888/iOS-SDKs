/*	NSAttributedString.h
	Copyright (c) 1994-2019, Apple Inc. All rights reserved.
*/

/*
 An NSAttributedString object manages a string of characters and associated sets of attributes (for example, font, color, kerning) that apply to individual characters or ranges of characters in the string.
 
 While NSAttributedString and its mutable counterpart NSMutableAttributedString are declared in Foundation, higher level UI frameworks (UIKit, AppKit) extend their APIs with functionality and types available in those frameworks.
 
 NSAttributedString and NSMutableAttributedString themselves are abstract, with concrete implementations returned by the various initialization APIs. The APIs and these concrete implementations are optimized for dealing with the contents in terms of ranges of runs of same attributes. If traversing thru an NSAttributedString, it's best to pay attention to the effectiveRange or longestEffectiveRange return values to process the contents in chunks and advance by runs, rather than character at a time.

 NSAttributedString and NSMutableAttributedString are designed to be easily subclassed. To subclass, provide implementations of the "primitive" methods, which are listed in the core class definitions below. For NSAttributedString, these are string and attributesAtIndex:effectiveRange:. For NSMutableAttributedString, additionally override replaceCharactersInRange:withString: and setAttributes:range:. You can also override any other methods, if needed, for performance. For instance if you have a mutableString backing store for the characters, overriding NSMutableAttributedString's mutableString can be useful.
 
 Unless you are providing your own custom storage, using an instance of NSMutableAttributeString as your storage can be a practical way to subclass NSMutableAttributeString. You can have the above methods call directly into that instance, in addition to doing whatever customizations you need for your subclass.
 */

#import <Foundation/NSString.h>
#import <Foundation/NSDictionary.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

/// The attributes you apply to ranges of characters in an attributed string.
///
/// Some attributes provide information about how to render, lay out, or interpret the text, while other attributes provide transient or collaborative information.
typedef NSString * NSAttributedStringKey NS_TYPED_EXTENSIBLE_ENUM;

/// A type that represents a key in the formatting context dictionary.
typedef NSString * NSAttributedStringFormattingContextKey NS_TYPED_EXTENSIBLE_ENUM;

/// A key for the inflection concepts in the formatting context dictionary.
FOUNDATION_EXPORT NSAttributedStringFormattingContextKey const NSInflectionConceptsKey
API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0), watchos(10.0));

/// A string of text that manages data, layout, and stylistic information for ranges of characters to support rendering.
///
/// ``NSAttributedString`` is a type you use to manage strings of stylized Unicode text. In addition to text, an attributed string contains key-value pairs known as _attributes_ that specify additional information to apply to ranges of characters within the string. Attributed strings support many different kinds of attributes, including:
///
/// - Rendering attributes that specify font, color, kern, ligature, and other details
/// - Attributes for attachments and adaptive image glyphs
/// - Semantic attributes such as link URLs or tool-tip information
/// - Language attributes to support automatic gender agreement and text layout
/// - Accessibility attributes that provide information for assistive technologies
/// - Attributes that summarize details of the Markdown import process
/// - Custom attributes you define for your app
///
/// Use attributed strings anywhere you need styled text, or when you need to associate additional information with your text. Because ``NSAttributedString`` is an immutable type, you specify all of the text and attributes for it at creation time and can't change them later. You can create attributed strings directly from a string of characters and a dictionary of attributes. You can also create attributed strings from the contents of a file, including files that contain RTF, RTFD, HTML, Markdown, or other file formats. If you need to modify the contents of an attributed string later, use the ``NSMutableAttributedString`` type instead.
///
/// If you create an ``NSAttributedString`` without any font information, the string's default font is Helvetica 12-point, which might differ from the default system font for the platform. To change the font, specify a font attribute at creation time.
///
/// ### Persistence
///
/// Be aware of how you persist attributed strings to and from the disk. RTF and RTFD are the preferred format for attributed strings because they offer the best fidelity for reading and writing attribute data. The RTF formats support a large number of standard attributes, and Apple extends the formats to support many Apple-specific attributes. If you define custom attributes for ranges of characters, store them separately alongside the RTF file for your text.
///
/// If you work extensively with HTML content, validate the results and performance of import and export operations during testing. WebKit handles the conversion between HTML markup and attributed strings. If an HTML file contains tags or constructs that attributed strings don't support, the import process ignores them and imports what it can.
///
/// When you create an attributed string from Markdown, the system adds presentation intent attributes with information about the original Markdown content. The system doesn't add style attributes to match the Markdown elements, but the system applies default style information when it renders a string with intent attributes. To change the rendering behavior of your Markdown content, remove the intent attributes and add the style attributes you prefer.
///
/// > Important:
/// > When reading or writing attributed strings, choose methods that return or throw an error, and check any errors you receive. Handling errors is the best way to detect issues with the import or export process and take corrective action.
///
/// The methods for reading and writing common file formats also support document attributes. Document attributes aren't part of the attributed string itself, but accompany the text when you save it to a file. When you read a file, the system returns any document attributes that it finds. Similarly, when you write an attributed string to a file, you can specify the attributes to include. For more information about document attributes, see ``DocumentAttributeKey`` and ``DocumentReadingOptionKey``.
///
/// ### System framework interoperability
///
/// <doc://com.apple.documentation/documentation/uikit/textkit> and <doc://com.apple.documentation/documentation/coretext> use attributed strings extensively during the layout and rendering processes. These technologies use the string's text and rendering-related attributes to calculate the text metrics needed during layout. Similarly, these technologies apply those same attributes during rendering to give the text its styled appearance. The technologies use only attributes that directly affect the appearance of the text, and ignore most other attributes. For some attributes, the text system adds attributes during rendering as needed. For example, the text system provides default style attributes for text with the ``Key/link`` attribute.
///
/// <doc://com.apple.documentation/documentation/appkit> and <doc://com.apple.documentation/documentation/uikit> also support attributed strings in several ways. Some views and controls in these frameworks have APIs that accept attributed strings, and render the string with its style information. The frameworks also add methods to the ``NSAttributedString`` class that let you draw a styled string directly in one of your custom views. Because these methods use TextKit to draw the string, they recognize the same rendering-related attributes as that technology.
///
/// The ``NSAttributedString`` class and its Core Foundation counterpart, <doc://com.apple.documentation/documentation/corefoundation/cfattributedstring>, are toll-free bridged, which means you can use the two types interchangeably in your code without losing any text or attribute information.
API_AVAILABLE(macos(10.0), ios(3.2), watchos(2.0), tvos(9.0))
@interface NSAttributedString : NSObject <NSCopying, NSMutableCopying, NSSecureCoding>

// Override these two APIs when subclassing NSAttributedString

/// The character contents of the receiver as a string.
@property (readonly, copy) NSString *string;

/// Returns the attributes for the character at the specified index.
///
/// Raises an `NSRangeException` if `location` lies beyond the end of the receiver's characters.
///
/// - Parameters:
///   - location: The index for which to return attributes. This value must lie within the bounds of the receiver.
///   - range: Upon return, the range over which the attributes and values are the same as those at `location`. This range isn't necessarily the maximum range covered, and its extent is implementation-dependent. If you need the maximum range, use `attributesAtIndex:longestEffectiveRange:inRange:`. If you don't need this value, pass `NULL`.
/// - Returns: The attributes for the character at `location`.
- (NSDictionary<NSAttributedStringKey, id> *)attributesAtIndex:(NSUInteger)location effectiveRange:(nullable NSRangePointer)range;

@end

@interface NSAttributedString (NSExtendedAttributedString)

/// The length of the attributed string.
@property (readonly) NSUInteger length;

/// Returns the value for an attribute with the specified name of the character at the specified index and, by reference, the range where the attribute applies.
///
/// Raises an `NSRangeException` if `location` lies beyond the end of the receiver's characters.
///
/// - Parameters:
///   - attrName: The name of an attribute.
///   - location: The index for which to return attributes. This value must not exceed the bounds of the receiver.
///   - range: If non-`NULL`, upon return contains a range over which the named attribute's value applies, or a range over which the attribute does not exist. The range isn't necessarily the maximum range covered by `attrName`, and its extent is implementation-dependent. If you need the maximum range, use `attribute:atIndex:longestEffectiveRange:inRange:`. If you don't need this value, pass `NULL`.
/// - Returns: The value for the attribute named `attrName` of the character at `location`, or `nil` if there is no such attribute.
- (nullable id)attribute:(NSAttributedStringKey)attrName atIndex:(NSUInteger)location effectiveRange:(nullable NSRangePointer)range;

/// Returns an attributed string consisting of the characters and attributes within the specified range in the attributed string.
///
/// Raises an `NSRangeException` if any part of `range` lies beyond the end of the receiver's characters. This method treats the length of the string as a valid range value that returns an empty string.
///
/// - Parameter range: The range from which to create a new attributed string. `range` must lie within the bounds of the receiver.
/// - Returns: An `NSAttributedString` object consisting of the characters and attributes within `range` in the receiver.
- (NSAttributedString *)attributedSubstringFromRange:(NSRange)range;

/// Returns the attributes for the character at the specified index and, by reference, the range where the attributes apply.
///
/// Raises an `NSRangeException` if `location` or any part of `rangeLimit` lies beyond the end of the receiver's characters.
///
/// If you don't need the range information, it's far more efficient to use `attributesAtIndex:effectiveRange:` to retrieve the attribute value.
///
/// - Parameters:
///   - location: The index for which to return attributes. This value must not exceed the bounds of the receiver.
///   - range: If non-`NULL`, upon return contains the maximum range over which the attributes and values are the same as those at `location`, clipped to `rangeLimit`.
///   - rangeLimit: The range over which to search for continuous presence of the attributes at `location`. This value must not exceed the bounds of the receiver.
- (NSDictionary<NSAttributedStringKey, id> *)attributesAtIndex:(NSUInteger)location longestEffectiveRange:(nullable NSRangePointer)range inRange:(NSRange)rangeLimit;

/// Returns the value for the attribute with the specified name of the character at the specified index and, by reference, the range where the attribute applies.
///
/// Raises an `NSRangeException` if `location` or any part of `rangeLimit` lies beyond the end of the receiver's characters.
///
/// If you don't need the longest effective range, it's far more efficient to use `attribute:atIndex:effectiveRange:` to retrieve the attribute value.
///
/// - Parameters:
///   - attrName: The name of an attribute.
///   - location: The index at which to test for `attrName`.
///   - range: If non-`NULL`, upon return contains the full range over which the value of the named attribute is the same as that at `location`, clipped to `rangeLimit`, or the full range over which the attribute does not exist. If you don't need this value, pass `NULL`.
///   - rangeLimit: The range over which to search for continuous presence of `attrName`. This value must not exceed the bounds of the receiver.
/// - Returns: The value for the attribute named `attrName` of the character at `location`, or `nil` if there is no such attribute.
- (nullable id)attribute:(NSAttributedStringKey)attrName atIndex:(NSUInteger)location longestEffectiveRange:(nullable NSRangePointer)range inRange:(NSRange)rangeLimit;

/// Returns a Boolean value that indicates whether the attributed string is equal to the specified string.
///
/// This method performs a character-by-character comparison of the string and its attributes. The character and its attributes must be the same in both strings for the method to return `YES`.
///
/// - Parameter other: The attributed string with which to compare the receiver.
/// - Returns: `YES` if the text and attributes in the current string and `other` are the same, otherwise `NO`.
- (BOOL)isEqualToAttributedString:(NSAttributedString *)other;

/// Creates an attributed string with the specified text and no attribute information.
///
/// - Parameter str: The text for the new attributed string.
/// - Returns: An `NSAttributedString` object initialized with the characters of `str` and no attribute information.
- (instancetype)initWithString:(NSString *)str;

/// Creates an attributed string with the specified text and attributes.
///
/// Returns an `NSAttributedString` object initialized with the characters of `str` and the attributes of `attrs`.
///
/// - Parameters:
///   - str: The text for the new attributed string.
///   - attrs: The attributes for the new attributed string. This method applies the attributes to the entire string.
- (instancetype)initWithString:(NSString *)str attributes:(nullable NSDictionary<NSAttributedStringKey, id> *)attrs;

/// Creates a new attributed string from the contents of another attributed string.
///
/// - Parameter attrStr: An attributed string.
/// - Returns: An `NSAttributedString` object initialized with the characters and attributes of `attrStr`.
- (instancetype)initWithAttributedString:(NSAttributedString *)attrStr;

/// Options for enumerating attributes of an attributed string.
typedef NS_OPTIONS(NSUInteger, NSAttributedStringEnumerationOptions) {
  /// Causes the enumeration to occur in reverse.
  NSAttributedStringEnumerationReverse = (1UL << 1),
  /// If this option is supplied, the longest effective range computation is not performed; the blocks may be invoked with consecutive attribute runs that have the same value.
  NSAttributedStringEnumerationLongestEffectiveRangeNotRequired = (1UL << 20)
};

/// Executes the specified block for each range of attributes in the attributed string.
///
/// If this method is called by an instance of `NSMutableAttributedString`, mutation (deletion, addition, or change) is allowed only if the mutation is within the range provided to the block. After a mutation, the enumeration continues with the range immediately following the processed range, adjusting for any change in length caused by the mutation.
///
/// - Parameters:
///   - enumerationRange: The range over which the attributes are enumerated.
///   - opts: The options used by the enumeration.
///   - block: The block to apply to ranges of attributes in the attributed string.
- (void)enumerateAttributesInRange:(NSRange)enumerationRange options:(NSAttributedStringEnumerationOptions)opts usingBlock:(void (NS_NOESCAPE ^)(NSDictionary<NSAttributedStringKey, id> *attrs, NSRange range, BOOL *stop))block API_AVAILABLE(macos(10.6), ios(4.0), watchos(2.0), tvos(9.0));

/// Executes the specified block for each range of a particular attribute in the attributed string.
///
/// If this method is called by an instance of `NSMutableAttributedString`, mutation (deletion, addition, or change) is allowed only if the mutation is within the range provided to the block. After a mutation, the enumeration continues with the range immediately following the processed range, adjusting for any change in length caused by the mutation.
///
/// - Parameters:
///   - attrName: The name of the attribute to enumerate.
///   - enumerationRange: The range over which the attribute values are enumerated.
///   - opts: The options used by the enumeration.
///   - block: A block to apply to ranges of the specified attribute in the attributed string.
- (void)enumerateAttribute:(NSAttributedStringKey)attrName inRange:(NSRange)enumerationRange options:(NSAttributedStringEnumerationOptions)opts usingBlock:(void (NS_NOESCAPE ^)(id _Nullable value, NSRange range, BOOL *stop))block API_AVAILABLE(macos(10.6), ios(4.0), watchos(2.0), tvos(9.0));

@end

/// A mutable string with associated attributes (such as visual style, hyperlinks, or accessibility data) for portions of its text.
///
/// The `NSMutableAttributedString` class declares additional methods for mutating the content of an attributed string. You can add and remove characters (raw strings) and attributes separately or together as attributed strings. See the class description for ``NSAttributedString`` for more information about attributed strings.
///
/// `NSMutableAttributedString` adds two primitive methods to those of `NSAttributedString`. These primitive methods provide the basis for all the other methods in its class. The primitive ``replaceCharacters(in:with:)-6oq9r`` method replaces a range of characters with those from a string, leaving all attribute information outside that range intact. The primitive ``setAttributes(_:range:)`` method sets attributes and values for a given range of characters, replacing any previous attributes and values for that range.
///
/// In macOS, AppKit also uses <doc://com.apple.documentation/documentation/appkit/nsparagraphstyle> and its subclass <doc://com.apple.documentation/documentation/appkit/nsmutableparagraphstyle> to encapsulate the paragraph or ruler attributes used by the `NSAttributedString` classes.
///
/// Note that the default font for `NSAttributedString` objects is Helvetica 12-point, which may differ from the macOS system font, so you may wish to create the string with non-default attributes suitable for your application using, for example, ``NSAttributedString/init(string:attributes:)``.
///
/// > iOS Note:
/// > In iOS, this class is used primarily in conjunction with the Core Text framework.
///
/// `NSMutableAttributedString` is "toll-free bridged" with its Core Foundation counterpart, <doc://com.apple.documentation/documentation/corefoundation/cfmutableattributedstring>. See [Toll-Free Bridging](https://developer.apple.com/library/archive/documentation/General/Conceptual/CocoaEncyclopedia/Toll-FreeBridgin/Toll-FreeBridgin.html#//apple_ref/doc/uid/TP40010810-CH2) for more information.
API_AVAILABLE(macos(10.0), ios(3.2), watchos(2.0), tvos(9.0))
@interface NSMutableAttributedString : NSAttributedString

// Override these two APIs (in addition to the two for NSAttributedString) when subclassing NSMutableAttributedString

/// Replaces the characters in the given range with the characters of the given string.
///
/// The new characters inherit the attributes of the first replaced character from `range`. Where the length of `range` is 0, the new characters inherit the attributes of the character preceding `range` if it has any, otherwise of the character following `range`.
///
/// Raises an `NSRangeException` if any part of `range` lies beyond the end of the receiver's characters.
///
/// - Parameters:
///   - range: A range specifying the characters to replace.
///   - str: A string specifying the characters to replace those in `range`.
- (void)replaceCharactersInRange:(NSRange)range withString:(NSString *)str;

/// Sets the attributes for the characters in the specified range to the specified attributes.
///
/// These new attributes replace any attributes previously associated with the characters in `range`. Raises an `NSRangeException` if any part of `range` lies beyond the end of the receiver's characters.
///
/// - Parameters:
///   - attrs: A dictionary containing the attributes to set.
///   - range: The range of characters whose attributes are set.
- (void)setAttributes:(nullable NSDictionary<NSAttributedStringKey, id> *)attrs range:(NSRange)range;

@end

@interface NSMutableAttributedString (NSExtendedMutableAttributedString)

/// The character contents of the receiver as a mutable string object.
///
/// The receiver tracks changes to this string and keeps its attribute mappings up to date.
@property (readonly, retain) NSMutableString *mutableString;

/// Adds an attribute with the given name and value to the characters in the specified range.
///
/// You may assign any `name`/`value` pair you wish to a range of characters. Raises an `NSInvalidArgumentException` if `name` or `value` is `nil` and an `NSRangeException` if any part of `range` lies beyond the end of the receiver's characters.
///
/// - Parameters:
///   - name: A string specifying the attribute name.
///   - value: The attribute value associated with `name`.
///   - range: The range of characters to which the specified attribute/value pair applies.
- (void)addAttribute:(NSAttributedStringKey)name value:(id)value range:(NSRange)range;

/// Adds the given collection of attributes to the characters in the specified range.
///
/// You may assign any name/value pair you wish to a range of characters. Raises an `NSInvalidArgumentException` if `attrs` is `nil` and an `NSRangeException` if any part of `range` lies beyond the end of the receiver's characters.
///
/// - Parameters:
///   - attrs: A dictionary containing the attributes to add.
///   - range: The range of characters to which the specified attributes apply.
- (void)addAttributes:(NSDictionary<NSAttributedStringKey, id> *)attrs range:(NSRange)range;

/// Removes the named attribute from the characters in the specified range.
///
/// Raises an `NSRangeException` if any part of `range` lies beyond the end of the receiver's characters.
///
/// - Parameters:
///   - name: A string specifying the attribute name to remove.
///   - range: The range of characters from which the specified attribute is removed.
- (void)removeAttribute:(NSAttributedStringKey)name range:(NSRange)range;

/// Replaces the characters and attributes in a given range with the characters and attributes of the given attributed string.
///
/// Raises an `NSRangeException` if any part of `range` lies beyond the end of the receiver's characters.
///
/// - Parameters:
///   - range: The range of characters and attributes replaced.
///   - attrString: The attributed string whose characters and attributes replace those in the specified range.
- (void)replaceCharactersInRange:(NSRange)range withAttributedString:(NSAttributedString *)attrString;

/// Inserts the characters and attributes of the given attributed string into the receiver at the given index.
///
/// The new characters and attributes begin at the given index and the existing characters and attributes from the index to the end of the receiver are shifted by the length of the attributed string. Raises an `NSRangeException` if `loc` lies beyond the end of the receiver's characters.
///
/// - Parameters:
///   - attrString: The string whose characters and attributes are inserted.
///   - loc: The index at which the characters and attributes are inserted.
- (void)insertAttributedString:(NSAttributedString *)attrString atIndex:(NSUInteger)loc;

/// Adds the characters and attributes of a given attributed string to the end of the receiver.
///
/// - Parameter attrString: The string whose characters and attributes are added.
- (void)appendAttributedString:(NSAttributedString *)attrString;

/// Deletes the characters in the given range along with their associated attributes.
///
/// Raises an `NSRangeException` if any part of `range` lies beyond the end of the receiver's characters.
///
/// - Parameter range: A range specifying the characters to delete.
- (void)deleteCharactersInRange:(NSRange)range;

/// Replaces the receiver's entire contents with the characters and attributes of the given attributed string.
///
/// - Parameter attrString: The attributed string whose characters and attributes replace those in the receiver.
- (void)setAttributedString:(NSAttributedString *)attrString;

/// Begins the buffering of changes to the string's characters and attributes.
///
/// Override this method in a subclass to buffer or optimize a series of changes to the string's characters or attributes. The string continues to buffer text until you call `endEditing`, at which time it consolidates the changes and notifies observers.
///
/// You can nest pairs of `beginEditing` and `endEditing` messages.
- (void)beginEditing;

/// Ends the buffering of changes to the string's characters and attributes.
///
/// Override this method in a subclass to consolidate changes made since a previous call to `beginEditing`. When you call this method, the string notifies observers of the changes.
///
/// The default implementation of this method does nothing.
- (void)endEditing;

@end

// Support for Markdown:

// Presentation intents correspond to the Markdown constructs applied to a certain range.
// The system may supply a default presentation for these intents in certain contexts.

/// A type that defines presentation intent for runs of characters for traits like emphasis, strikethrough, and code voice.
///
/// Inline presentation intents.
/// For use with `NSInlinePresentationAttributeName`.
typedef NS_OPTIONS(NSUInteger, NSInlinePresentationIntent) {
    /// An intent that represents an emphasized presentation.
    NSInlinePresentationIntentEmphasized                   = 1 << 0,
    /// An intent that represents a strongly emphasized presentation.
    NSInlinePresentationIntentStronglyEmphasized           = 1 << 1,
    /// An intent that represents a code voice presentation.
    NSInlinePresentationIntentCode                         = 1 << 2,
    /// An intent that represents a strikethrough presentation.
    NSInlinePresentationIntentStrikethrough                = 1 << 5,
    /// An intent that represents a soft line break.
    NSInlinePresentationIntentSoftBreak                    = 1 << 6,
    /// An intent that represents a line break.
    NSInlinePresentationIntentLineBreak                    = 1 << 7,
    /// An intent that represents an inline HTML presentation.
    NSInlinePresentationIntentInlineHTML                   = 1 << 8,
    /// An intent that represents a block HTML presentation.
    NSInlinePresentationIntentBlockHTML                    = 1 << 9
} API_AVAILABLE(macos(12.0), ios(15.0), watchos(8.0), tvos(15.0)) NS_SWIFT_NAME(InlinePresentationIntent);


/// An attribute key whose value is an `NSNumber` wrapping a value of type `NSInlinePresentationIntent`.
FOUNDATION_EXTERN const NSAttributedStringKey NSInlinePresentationIntentAttributeName
 API_AVAILABLE(macos(12.0), ios(15.0), watchos(8.0), tvos(15.0)) NS_SWIFT_NAME(inlinePresentationIntent);

/// An attribute key whose value is an `NSString` providing an alternate description.
FOUNDATION_EXTERN const NSAttributedStringKey NSAlternateDescriptionAttributeName
 API_AVAILABLE(macos(12.0), ios(15.0), watchos(8.0), tvos(15.0)) NS_SWIFT_NAME(alternateDescription);

/// An attribute key whose value is an `NSURL` for an image.
FOUNDATION_EXTERN const NSAttributedStringKey NSImageURLAttributeName
 API_AVAILABLE(macos(12.0), ios(15.0), watchos(8.0), tvos(15.0)) NS_SWIFT_NAME(imageURL);

/// An attribute key whose value is an `NSString` containing a BCP-47 language identifier.
FOUNDATION_EXTERN const NSAttributedStringKey NSLanguageIdentifierAttributeName
API_AVAILABLE(macos(12.0), ios(15.0), watchos(8.0), tvos(15.0)) NS_SWIFT_NAME(languageIdentifier);

/// An attribute key whose value is an `NSAttributedStringMarkdownSourcePosition` indicating the position in the original Markdown source.
FOUNDATION_EXPORT const NSAttributedStringKey NSMarkdownSourcePositionAttributeName
API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0)) NS_SWIFT_NAME(markdownSourcePosition);


/// A type that represents policies for handling parsing failures.
typedef NS_ENUM(NSInteger, NSAttributedStringMarkdownParsingFailurePolicy) {
    /// A policy to return an error from the initializer if parsing fails.
    NSAttributedStringMarkdownParsingFailureReturnError = 0,

    /// A policy to return a partially parsed string, if possible. The returned string may include unparsed markup. If returning a partially parsed string isn't possible, the parser may return an error anyway.
    NSAttributedStringMarkdownParsingFailureReturnPartiallyParsedIfPossible = 1,
} API_AVAILABLE(macos(12.0), ios(15.0), watchos(8.0), tvos(15.0)) NS_REFINED_FOR_SWIFT;

/// A type that represents the syntax for intepreting a Markdown string.
typedef NS_ENUM(NSInteger, NSAttributedStringMarkdownInterpretedSyntax) {
    /// A syntax value that interprets the full Markdown syntax and produces all relevant attributes.
    NSAttributedStringMarkdownInterpretedSyntaxFull = 0,

    /// A syntax value that parses all Markdown text, but interprets only attributes that apply to inline spans. Attributes that differentiate blocks (e.g. `NSPresentationIntentAttributeName`) will not be applied. (Extended attributes apply to inline spans, if allowed, and will also be interpreted.)
    NSAttributedStringMarkdownInterpretedSyntaxInlineOnly = 1,

    /// A syntax value that behaves like `NSAttributedStringMarkdownInterpretedSyntaxInlineOnly`, but does not interpret multiple consecutive instances of whitespace as a single separator space. All whitespace characters will appear in the result as they are specified in the source.
    NSAttributedStringMarkdownInterpretedSyntaxInlineOnlyPreservingWhitespace = 2
} API_AVAILABLE(macos(12.0), ios(15.0), watchos(8.0), tvos(15.0)) NS_REFINED_FOR_SWIFT;

/// The position of attributed string text in its original Markdown source string.
NS_REFINED_FOR_SWIFT
API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0))
@interface NSAttributedStringMarkdownSourcePosition : NSObject <NSCopying, NSSecureCoding>

/// The line where the text begins in the Markdown source. Uses 1-based counting.
@property (readonly) NSInteger startLine;
/// The column where the text begins in the Markdown source. Uses 1-based counting. Columns represent UTF-8 indices; for multi-byte characters, the column indicates the first byte.
@property (readonly) NSInteger startColumn;
/// The line where the text ends in the Markdown source. Uses 1-based counting.
@property (readonly) NSInteger endLine;
/// The column where the text ends in the Markdown source. Uses 1-based counting. Columns represent UTF-8 indices; for multi-byte characters, the column indicates the first byte.
@property (readonly) NSInteger endColumn;

/// Creates a Markdown source position instance from its start and end line and column.
///
/// - Parameters:
///   - startLine: The line number where text begins in the Markdown source. Specify a 1-based number.
///   - startColumn: The column number where text begins in the Markdown source. Specify a 1-based number. Columns represent UTF-8 indices; for multi-byte characters, the column indicates the first byte.
///   - endLine: The line number where the Markdown source ends. Specify a 1-based number.
///   - endColumn: The column number where the Markdown source ends. Specify a 1-based number.
- (instancetype)initWithStartLine:(NSInteger)startLine startColumn:(NSInteger)startColumn endLine:(NSInteger)endLine endColumn:(NSInteger)endColumn;

/// Returns a range indicating the source portion within a Markdown string.
///
/// Use this method to access the marked-up region of `string` with an `NSRange`, rather than making manual calculations based on row and column values.
///
/// - Parameter string: The Markdown source string that this source position object refers to.
/// - Returns: A range that represents the source portion within a source Markdown string.
- (NSRange)rangeInString:(NSString *)string;

@end

/// Options that affect the parsing of Markdown content into an attributed string.
NS_REFINED_FOR_SWIFT
API_AVAILABLE(macos(12.0), ios(15.0), watchos(8.0), tvos(15.0))
@interface NSAttributedStringMarkdownParsingOptions : NSObject <NSCopying>

/// Creates a Markdown parsing options instance.
- (instancetype)init;

/// A Boolean value that indicates whether parsing allows extensions to Markdown that specify extended attributes. Defaults to `NO` (only parse CommonMark syntax).
@property BOOL allowsExtendedAttributes;

/// The syntax for interpreting a Markdown string.
///
/// If your Markdown data uses syntax that this setting excludes, the parser still parses it and includes its text in the final result. However, the relevant text won't have attributes.
@property NSAttributedStringMarkdownInterpretedSyntax interpretedSyntax;

/// The policy for handling a parsing failure. The default is `NSAttributedStringMarkdownParsingFailureReturnError`.
@property NSAttributedStringMarkdownParsingFailurePolicy failurePolicy;

/// The BCP-47 language code for this document. If not `nil`, the `NSLanguageIdentifierAttributeName` attribute will be applied to any range in the returned string that doesn't otherwise specify a language attribute. The default is `nil`, which applies no attributes.
@property (nullable, copy) NSString *languageCode;

/// A Boolean value that indicates whether parsing applies attributes that indicate the position of attributed text in the original Markdown string.
@property BOOL appliesSourcePositionAttributes API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0));

@end


@interface NSAttributedString (NSAttributedStringCreateFromMarkdown)

// These constructors have a 'baseURL' parameter. If specified, links in the document will be relative to this URL, and images in the document will be looked for relative to this URL (if the other options allow image loading).
// Defaults to nil. If set to nil, paths will not be resolved.

/// Creates an attributed string from the contents of a specified URL that contains Markdown-formatted data using the provided options.
///
/// - Parameters:
///   - markdownFile: The URL to load Markdown-formatted data from.
///   - options: Options that affect how the initializer interprets formatting in the Markdown string. This parameter defaults to no options.
///   - baseURL: The base URL to use when resolving Markdown URLs. The initializer treats URLs as being relative to this URL. If this value is `nil`, the initializer doesn't resolve URLs. The default is `nil`.
///   - error: On return, if an error occurs, this pointer contains an actual error object with the error information. You may specify `nil` for this parameter if you don't want the error information.
/// - Returns: An attributed string with the parsed Markdown text and styling, or `nil` if parsing the data fails.
- (nullable instancetype)initWithContentsOfMarkdownFileAtURL:(NSURL *)markdownFile
     options:(nullable NSAttributedStringMarkdownParsingOptions *)options
     baseURL:(nullable NSURL *)baseURL
     error:(NSError **)error
     API_AVAILABLE(macos(12.0), ios(15.0), watchos(8.0), tvos(15.0))
     NS_REFINED_FOR_SWIFT;

/// Creates an attributed string from Markdown-formatted data using the provided options.
///
/// - Parameters:
///   - markdown: The `NSData` instance that contains the Markdown formatting.
///   - options: Options that affect how the initializer interprets formatting in the Markdown string. This parameter defaults to no options.
///   - baseURL: The base URL to use when resolving Markdown URLs. The initializer treats URLs as being relative to this URL. If this value is `nil`, the initializer doesn't resolve URLs. The default is `nil`.
///   - error: On return, if an error occurs, this pointer contains an actual error object with the error information. You may specify `nil` for this parameter if you don't want the error information.
/// - Returns: An attributed string with the parsed Markdown text and styling, or `nil` if parsing the data fails.
- (nullable instancetype)initWithMarkdown:(NSData *)markdown
     options:(nullable NSAttributedStringMarkdownParsingOptions *)options
     baseURL:(nullable NSURL *)baseURL
     error:(NSError **)error
     API_AVAILABLE(macos(12.0), ios(15.0), watchos(8.0), tvos(15.0))
     NS_REFINED_FOR_SWIFT;

/// Creates an attributed string from a Markdown-formatted string using the provided options.
///
/// - Parameters:
///   - markdownString: The string that contains the Markdown formatting.
///   - options: Options that affect how the initializer interprets formatting in the Markdown string. This parameter defaults to no options.
///   - baseURL: The base URL to use when resolving Markdown URLs. The initializer treats URLs as being relative to this URL. If this value is `nil`, the initializer doesn't resolve URLs. The default is `nil`.
///   - error: On return, if an error occurs, this pointer contains an actual error object with the error information. You may specify `nil` for this parameter if you don't want the error information.
/// - Returns: An attributed string with the parsed Markdown text and styling, or `nil` if parsing the data fails.
- (nullable instancetype)initWithMarkdownString:(NSString *)markdownString
     options:(nullable NSAttributedStringMarkdownParsingOptions *)options
     baseURL:(nullable NSURL *)baseURL
     error:(NSError **)error
     API_AVAILABLE(macos(12.0), ios(15.0), watchos(8.0), tvos(15.0))
     NS_REFINED_FOR_SWIFT;

@end


// Formatting API:

/// Options to use when creating an attributed string from a format string and variable list of arguments.
typedef NS_OPTIONS(NSUInteger, NSAttributedStringFormattingOptions) {
    /// An option to replace the attributes in a substituted string with those of the provided attributed string.
    NSAttributedStringFormattingInsertArgumentAttributesWithoutMerging
      API_AVAILABLE(macos(12.0), ios(15.0), watchos(8.0), tvos(15.0)) = 1 << 0,
    /// An option to apply the replacement index attribute to the replaced portions of text in a format string.
    NSAttributedStringFormattingApplyReplacementIndexAttribute
      API_AVAILABLE(macos(12.0), ios(15.0), watchos(8.0), tvos(15.0)) = 1 << 1,
} NS_REFINED_FOR_SWIFT;

@interface NSAttributedString (NSAttributedStringFormatting)

/// Formats the string using the specified locale (or the canonical one, if nil).
- (instancetype)initWithFormat:(NSAttributedString *)format
                       options:(NSAttributedStringFormattingOptions)options
                        locale:(nullable NSLocale *)locale, ...
    NS_REFINED_FOR_SWIFT
    API_AVAILABLE(macos(12.0), ios(15.0), watchos(8.0), tvos(15.0));

/// Formats the string using the arguments list and the specified locale (or the canonical one, if nil).
- (instancetype)initWithFormat:(NSAttributedString *)format
                       options:(NSAttributedStringFormattingOptions)options
                        locale:(nullable NSLocale *)locale
                     arguments:(va_list)arguments
    NS_REFINED_FOR_SWIFT
    API_AVAILABLE(macos(12.0), ios(15.0), watchos(8.0), tvos(15.0));

/// Formats the string using the current locale and default options.
+ (instancetype)localizedAttributedStringWithFormat:(NSAttributedString *)format, ...
    NS_REFINED_FOR_SWIFT
    API_AVAILABLE(macos(12.0), ios(15.0), watchos(8.0), tvos(15.0));

/// Formats the string using the current locale and the specified options.
+ (instancetype)localizedAttributedStringWithFormat:(NSAttributedString *)format
                                            options:(NSAttributedStringFormattingOptions)options, ...
    NS_REFINED_FOR_SWIFT
    API_AVAILABLE(macos(12.0), ios(15.0), watchos(8.0), tvos(15.0));

/// Formats the string using the specified locale (or the canonical one, if nil).
- (instancetype)initWithFormat:(NSAttributedString *)format
                       options:(NSAttributedStringFormattingOptions)options
                        locale:(nullable NSLocale *)locale
                       context:(NSDictionary<NSAttributedStringFormattingContextKey, id>*)context,...
    NS_REFINED_FOR_SWIFT
    API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0), watchos(10.0));

/// Formats the string using the arguments list and the specified locale (or the canonical one, if nil).
- (instancetype)initWithFormat:(NSAttributedString *)format
                       options:(NSAttributedStringFormattingOptions)options
                        locale:(nullable NSLocale *)locale
                       context:(NSDictionary<NSAttributedStringFormattingContextKey, id>*)context
                     arguments:(va_list)arguments
    NS_REFINED_FOR_SWIFT
    API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0), watchos(10.0));

/// Formats the string using the current locale and default options.
+ (instancetype)localizedAttributedStringWithFormat:(NSAttributedString *)format
                                            context:(NSDictionary<NSAttributedStringFormattingContextKey, id>*)context, ...
    NS_REFINED_FOR_SWIFT
    API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0), watchos(10.0));

/// Formats the string using the current locale and the specified options.
+ (instancetype)localizedAttributedStringWithFormat:(NSAttributedString *)format
                                            options:(NSAttributedStringFormattingOptions)options
                                            context:(NSDictionary<NSAttributedStringFormattingContextKey, id>*)context, ...
    NS_REFINED_FOR_SWIFT
    API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0), watchos(10.0));

@end

@interface NSMutableAttributedString (NSMutableAttributedStringFormatting)

/// Formats the specified string and arguments with the current locale,
/// then appends the result to the receiver.
- (void)appendLocalizedFormat:(NSAttributedString *)format, ...
    NS_REFINED_FOR_SWIFT
    API_AVAILABLE(macos(12.0), ios(15.0), watchos(8.0), tvos(15.0));

@end

/// An attribute key whose value is an `NSNumber` indicating the replacement's position in a format string.
FOUNDATION_EXPORT NSAttributedStringKey const NSReplacementIndexAttributeName
    NS_SWIFT_NAME(replacementIndex)
    API_AVAILABLE(macos(12.0), ios(15.0), watchos(8.0), tvos(15.0));


// -----

@interface NSAttributedString (NSMorphology)

/// If the string has portions tagged with NSInflectionRuleAttributeName
/// that have no format specifiers, create a new string with those portions inflected
/// by following the rule in the attribute.
- (NSAttributedString *)attributedStringByInflectingString
    API_AVAILABLE(macos(12.0), ios(15.0), watchos(8.0), tvos(15.0));

@end

/// An attribute key whose value is an `NSMorphology` object that specifies the morphology for the attributed string.
FOUNDATION_EXPORT NSAttributedStringKey const NSMorphologyAttributeName
    NS_SWIFT_NAME(morphology)
    API_AVAILABLE(macos(12.0), ios(15.0), watchos(8.0), tvos(15.0));

/// An attribute key whose value is an `NSInflectionRule` object that specifies the inflection rule to apply to the attributed string.
FOUNDATION_EXPORT NSAttributedStringKey const NSInflectionRuleAttributeName
    NS_SWIFT_NAME(inflectionRule)
    API_AVAILABLE(macos(12.0), ios(15.0), watchos(8.0), tvos(15.0));

/// An attribute key whose value indicates inflection agreement with a specific argument.
FOUNDATION_EXPORT NSAttributedStringKey const NSInflectionAgreementArgumentAttributeName
    NS_SWIFT_NAME(agreeWithArgument)
    API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0), watchos(10.0));

/// An attribute key whose value indicates inflection agreement with a specific concept.
FOUNDATION_EXPORT NSAttributedStringKey const NSInflectionAgreementConceptAttributeName
    NS_SWIFT_NAME(agreeWithConcept)
    API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0), watchos(10.0));

/// An attribute key whose value indicates the referent concept for inflection.
FOUNDATION_EXPORT NSAttributedStringKey const NSInflectionReferentConceptAttributeName
    NS_SWIFT_NAME(referentConcept)
    API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0), watchos(10.0));

/// An attribute key whose value provides an alternative inflection for the attributed string.
FOUNDATION_EXPORT NSAttributedStringKey const NSInflectionAlternativeAttributeName
    NS_SWIFT_NAME(inflectionAlternative)
    API_AVAILABLE(macos(12.0), ios(15.0), watchos(8.0), tvos(15.0));

/// An attribute key whose value specifies a localized number format.
FOUNDATION_EXPORT NSAttributedStringKey const NSLocalizedNumberFormatAttributeName
    NS_SWIFT_NAME(localizedNumberFormat)
    API_AVAILABLE(macos(15.0), ios(18.0), watchos(11.0), tvos(18.0));

/// An attribute key whose value is an `NSString` representing the delimiter used when declaring the current list item.
FOUNDATION_EXTERN const NSAttributedStringKey NSListItemDelimiterAttributeName
    NS_SWIFT_NAME(listItemDelimiter)
    API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

/// An attribute key whose value is an `NSPresentationIntent` object representing the presentation intent for a block-level element.
FOUNDATION_EXTERN
const NSAttributedStringKey NSPresentationIntentAttributeName API_AVAILABLE(macos(12.0), ios(15.0), watchos(8.0), tvos(15.0));

/// An enumeration of intended display styles for blocks of text like paragraphs, lists, and code blocks.
typedef NS_ENUM(NSInteger, NSPresentationIntentKind) {
    /// A presentation style for a paragraph of text.
    NSPresentationIntentKindParagraph,
    /// A presentation style for a section header.
    NSPresentationIntentKindHeader,
    /// A presentation style for an ordered list of items.
    NSPresentationIntentKindOrderedList,
    /// A presentation style for an unordered list of items.
    NSPresentationIntentKindUnorderedList,
    /// A presentation style for a list of items.
    NSPresentationIntentKindListItem,
    /// A presentation style for a block of code.
    NSPresentationIntentKindCodeBlock,
    /// A presentation style for a block quote.
    NSPresentationIntentKindBlockQuote,
    /// A presentation style for a horizontal rule.
    NSPresentationIntentKindThematicBreak,
    /// A presentation style for a table.
    NSPresentationIntentKindTable,
    /// A presentation style for the header row of a table.
    NSPresentationIntentKindTableHeaderRow,
    /// A presentation style for a row of a table.
    NSPresentationIntentKindTableRow,
    /// A presentation style for a single cell of a table.
    NSPresentationIntentKindTableCell,
} API_AVAILABLE(macos(12.0), ios(15.0), watchos(8.0), tvos(15.0)) NS_REFINED_FOR_SWIFT;

/// An enumeration of values for aligning the contents of table columns.
typedef NS_ENUM(NSInteger, NSPresentationIntentTableColumnAlignment) {
    /// A presentation style for columns with left-aligned text.
    NSPresentationIntentTableColumnAlignmentLeft,
    /// A presentation style for columns with center-aligned text.
    NSPresentationIntentTableColumnAlignmentCenter,
    /// A presentation style for columns with right-aligned text.
    NSPresentationIntentTableColumnAlignmentRight,
} API_AVAILABLE(macos(12.0), ios(15.0), watchos(8.0), tvos(15.0)) NS_REFINED_FOR_SWIFT;

/// A type that contains the Markdown formatting for blocks of text, like paragraphs, lists, code blocks, and parts of tables.
///
/// An ``NSPresentationIntent`` object stores the Markdown semantics for a range of characters in an attributed string. When parsing Markdown into an attributed string, the system sets the value of the ``NSAttributedString/Key/presentationIntentAttributeName`` attribute to an instance of this class. When displaying your string in system views, the system applies a default visual style to match the corresponding information in this type. To replace the system's default formatting, remove these attributes from your attributed string and apply the formatting you want.
NS_REFINED_FOR_SWIFT
API_AVAILABLE(macos(12.0), ios(15.0), watchos(8.0), tvos(15.0))
@interface NSPresentationIntent: NSObject <NSCopying, NSSecureCoding>

/// The type of the intent.
@property (readonly) NSPresentationIntentKind intentKind;

- (instancetype)init NS_UNAVAILABLE;

/// The parent of the current intent.
@property (readonly, nullable, strong) NSPresentationIntent *parentIntent;

/// Creates a paragraph intent with the provided information.
///
/// - Parameters:
///   - identity: The unique identifier for the intent.
///   - parent: The parent intent of the paragraph.
/// - Returns: A new intent with the kind set to `NSPresentationIntentKindParagraph`.
+ (NSPresentationIntent *)paragraphIntentWithIdentity:(NSInteger)identity nestedInsideIntent:(nullable NSPresentationIntent *)parent;

/// Creates a header intent with the provided information.
///
/// - Parameters:
///   - identity: The unique identifier for the intent.
///   - level: The level for the header section. Specify `1` or greater for this parameter. Don't specify `0`.
///   - parent: The parent intent of the header.
/// - Returns: A new intent with the kind set to `NSPresentationIntentKindHeader`.
+ (NSPresentationIntent *)headerIntentWithIdentity:(NSInteger)identity level:(NSInteger)level nestedInsideIntent:(nullable NSPresentationIntent *)parent;

/// Creates a code-block intent with the provided information.
///
/// - Parameters:
///   - identity: The unique identifier for the intent.
///   - languageHint: The programming language for the code listing.
///   - parent: The parent intent of the code block.
/// - Returns: A new intent with the kind set to `NSPresentationIntentKindCodeBlock`.
+ (NSPresentationIntent *)codeBlockIntentWithIdentity:(NSInteger)identity languageHint:(nullable NSString *)languageHint nestedInsideIntent:(nullable NSPresentationIntent *)parent;

/// Creates a thematic break intent with the provided information.
///
/// - Parameters:
///   - identity: The unique identifier for the intent.
///   - parent: The parent intent of the thematic break.
/// - Returns: A new intent with the kind set to `NSPresentationIntentKindThematicBreak`.
+ (NSPresentationIntent *)thematicBreakIntentWithIdentity:(NSInteger)identity nestedInsideIntent:(nullable NSPresentationIntent *)parent;

/// Creates an ordered list intent with the provided information.
///
/// - Parameters:
///   - identity: The unique identifier for the intent.
///   - parent: The parent intent of the ordered list.
/// - Returns: A new intent with the kind set to `NSPresentationIntentKindOrderedList`.
+ (NSPresentationIntent *)orderedListIntentWithIdentity:(NSInteger)identity nestedInsideIntent:(nullable NSPresentationIntent *)parent;

/// Creates an unordered list intent with the provided information.
///
/// - Parameters:
///   - identity: The unique identifier for the intent.
///   - parent: The parent intent of the unordered list.
/// - Returns: A new intent with the kind set to `NSPresentationIntentKindUnorderedList`.
+ (NSPresentationIntent *)unorderedListIntentWithIdentity:(NSInteger)identity nestedInsideIntent:(nullable NSPresentationIntent *)parent;

/// Creates a list item intent with the provided information.
///
/// - Parameters:
///   - identity: The unique identifier for the intent.
///   - ordinal: The ordinal number of the list item.
///   - parent: The parent intent of the list item.
/// - Returns: A new intent with the kind set to `NSPresentationIntentKindListItem`.
+ (NSPresentationIntent *)listItemIntentWithIdentity:(NSInteger)identity ordinal:(NSInteger)ordinal nestedInsideIntent:(nullable NSPresentationIntent *)parent;

/// Creates a block quote intent with the provided information.
///
/// - Parameters:
///   - identity: The unique identifier for the intent.
///   - parent: The parent intent of the block quote.
/// - Returns: A new intent with the kind set to `NSPresentationIntentKindBlockQuote`.
+ (NSPresentationIntent *)blockQuoteIntentWithIdentity:(NSInteger)identity nestedInsideIntent:(nullable NSPresentationIntent *)parent;

/// Creates a table intent with the provided information.
///
/// - Parameters:
///   - identity: The unique identifier for the intent.
///   - columnCount: The number of columns in the table.
///   - alignments: An array of `NSNumber` values indicating the alignment of each column.
///   - parent: The parent intent of the table.
/// - Returns: A new intent with the kind set to `NSPresentationIntentKindTable`.
+ (NSPresentationIntent *)tableIntentWithIdentity:(NSInteger)identity columnCount:(NSInteger)columnCount alignments:(NSArray<NSNumber *> *)alignments nestedInsideIntent:(nullable NSPresentationIntent *)parent;

/// Creates a table header row intent with the provided information.
///
/// - Parameters:
///   - identity: The unique identifier for the intent.
///   - parent: The parent intent of the table header row.
/// - Returns: A new intent with the kind set to `NSPresentationIntentKindTableHeaderRow`.
+ (NSPresentationIntent *)tableHeaderRowIntentWithIdentity:(NSInteger)identity nestedInsideIntent:(nullable NSPresentationIntent *)parent;

/// Creates a table row intent with the provided information.
///
/// - Parameters:
///   - identity: The unique identifier for the intent.
///   - row: The row number (0-based).
///   - parent: The parent intent of the table row.
/// - Returns: A new intent with the kind set to `NSPresentationIntentKindTableRow`.
+ (NSPresentationIntent *)tableRowIntentWithIdentity:(NSInteger)identity row:(NSInteger)row nestedInsideIntent:(nullable NSPresentationIntent *)parent;

/// Creates a table cell intent with the provided information.
///
/// - Parameters:
///   - identity: The unique identifier for the intent.
///   - column: The column number (0-based).
///   - parent: The parent intent of the table cell.
/// - Returns: A new intent with the kind set to `NSPresentationIntentKindTableCell`.
+ (NSPresentationIntent *)tableCellIntentWithIdentity:(NSInteger)identity column:(NSInteger)column nestedInsideIntent:(nullable NSPresentationIntent *)parent;

/// A unique identifier for the intent in the document.
///
/// Use the value in this property to disambiguate attributes that apply to contiguous text. For example, you might use it to differentiate between two headers in a row with the same level.
@property (readonly) NSInteger identity;

/// The number for an item in an ordered list.
///
/// If the intent is not a list, the value of this property is `0`.
@property (readonly) NSInteger ordinal;

/// The alignments for the columns in a table.
///
/// If the intent is not a table, the value of this property is `nil`.
@property (nullable, readonly) NSArray<NSNumber *> *columnAlignments;

/// The number of columns in a table.
///
/// If the intent is not a table, the value of this property is `0`.
@property (readonly) NSInteger columnCount;

/// The level of a header section.
///
/// This value corresponds to the number of hash marks (`#`) associated with the header. If the intent is not a header, the value of this property is `0`.
@property (readonly) NSInteger headerLevel;

/// The language associated with the code listing.
///
/// If the intent is not a code block, the value of this property is `nil`.
@property (readonly, nullable, copy) NSString *languageHint;

/// The column number to which the cell belongs.
///
/// The value of this property is `0`-based, with the first column at `0`, the second column at `1`, and so on. If the intent is not a cell, this value is `0`.
@property (readonly) NSInteger column;

/// The row number to which this cell belongs.
///
/// The value of this property is `0`-based, with the first row at `0`, the second row at `1`, and so on. If the intent is not a cell, this value is `0`.
@property (readonly) NSInteger row;

/// The indentation level of the intent.
///
/// The initial list has an indentation level of `0`. Each time you nest a new list, the indentation level increases by `1`. All elements within the same list have the same indentation level. Text outside list intents has an indentation level of `0`.
@property (readonly) NSInteger indentationLevel;

/// Returns a Boolean value that indicates whether the current intent is equivalent to the specified intent.
///
/// Two intents are equivalent if their attributes match. This method doesn't consider the `identity` property of the intents when determining their equivalence.
///
/// - Parameter other: The other intent to use in the comparison.
/// - Returns: `YES` if the current intent is equivalent to the specified intent, or `NO` if it isn't.
- (BOOL)isEquivalentToPresentationIntent:(NSPresentationIntent *)other;

@end

NS_HEADER_AUDIT_END(nullability, sendability)
