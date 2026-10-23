#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIFoundation/NSParagraphStyle.h>)
//
//  NSParagraphStyle.h
//  Text Kit
//
//  Copyright (c) 1994-2025, Apple Inc. All rights reserved.
//
// NSParagraphStyle and NSMutableParagraphStyle hold paragraph style information
// NSTextTab holds information about a single tab stop

#import <Foundation/Foundation.h>
#import <UIKit/UIKitDefines.h>
#import <UIKit/NSText.h>

@class NSTextList;
@class NSTextBlock;

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

#if !__NSPARAGRAPH_STYLE_SHARED_SECTION__
#define __NSPARAGRAPH_STYLE_SHARED_SECTION__ 1

/// Constants that specify what happens when a line is too long for a container.
typedef NS_ENUM(NSInteger, NSLineBreakMode) {
    /// Wrapping occurs at word boundaries, unless the word doesn't fit.
    NSLineBreakByWordWrapping = 0,
    /// Wrapping occurs before the first character that doesn't fit.
    NSLineBreakByCharWrapping,
    /// Lines don't extend past the edge of the text container.
    NSLineBreakByClipping,
    /// A line displays so that the end fits in the container and an ellipsis glyph indicates the missing text at the beginning of the line.
    ///
    /// Although this mode works for multiline text, it's more often used for
    /// single line text.
    NSLineBreakByTruncatingHead,
    /// A line displays so that the beginning fits in the container and an ellipsis glyph indicates the missing text at the end of the line.
    ///
    /// Although this mode works for multiline text, it's more often used for
    /// single line text.
    NSLineBreakByTruncatingTail,
    /// A line displays so that the beginning and end fit in the container and an ellipsis glyph indicates the missing text in the middle.
    ///
    /// Use this mode for single-line layout; using it with multiline text
    /// truncates the text into a single line.
    NSLineBreakByTruncatingMiddle
} API_AVAILABLE(macos(10.0), ios(6.0), watchos(2.0), tvos(9.0), visionos(1.0));

/// Constants that specify how the text system breaks lines while laying out paragraphs.
///
/// Line break strategy describes a collection of options that can affect where
/// line breaks are placed in a paragraph. This is independent from line break
/// mode, which describes what happens when text is too long to fit within its
/// container. These options won't have any effect when used with line break
/// modes that don't support multiple lines, like clipping or truncating middle.
typedef NS_OPTIONS(NSUInteger, NSLineBreakStrategy) {
    /// The text system doesn't use any non-default line-break strategies.
    NSLineBreakStrategyNone = 0,
    /// The text system pushes out individual lines to avoid an orphan word on the last line of the paragraph.
    ///
    /// To avoid an orphan word on the last line of a paragraph before a page
    /// break, the text system may extend individual lines by one or more words.
    /// Typically, the text system only pushes out the last line by one word.
    NSLineBreakStrategyPushOut API_AVAILABLE(macos(10.11), ios(9.0), tvos(9.0), watchos(2.0), visionos(1.0)) = 1 << 0,
    /// The text system prohibits breaking between Hangul syllables.
    ///
    /// To avoid breaking between Hangul syllables, this strategy is preferred
    /// for typesetting modern Korean documents that display UI strings.
    NSLineBreakStrategyHangulWordPriority API_AVAILABLE(macos(11.0), ios(14.0), watchos(7.0), tvos(14.0), visionos(1.0)) = 1 << 1,
    /// The text system uses the same configuration of line-break strategies that it uses for standard UI labels.
    ///
    /// This strategy optimizes for displaying shorter strings that are common
    /// in UI labels. This strategy may be unsuitable for large amounts of text.
    NSLineBreakStrategyStandard API_AVAILABLE(macos(11.0), ios(14.0), watchos(7.0), tvos(14.0), visionos(1.0)) = 0xFFFF
} API_AVAILABLE(macos(10.11), ios(9.0), tvos(9.0), watchos(2.0), visionos(1.0));

#endif // !__NSPARAGRAPH_STYLE_SHARED_SECTION__

// NSTextTab
typedef NSString * NSTextTabOptionKey NS_TYPED_ENUM API_AVAILABLE(macos(10.0), ios(7.0), tvos(9.0), watchos(2.0), visionos(1.0));

/// The characters that terminate a tab column.
///
/// The value is an `NSCharacterSet` object. The tab and newline characters are
/// implied even if they don't exist in the character set. This attribute is
/// optional.
UIKIT_EXTERN NSTextTabOptionKey const NSTabColumnTerminatorsAttributeName API_AVAILABLE(macos(10.0), ios(7.0), tvos(9.0), watchos(2.0), visionos(1.0));

/// A tab in a paragraph.
///
/// A text tab represents a tab in an ``NSParagraphStyle`` object, storing an
/// alignment type and location. ``NSTextTab`` objects are most frequently used
/// with the TextKit system and with
/// <doc://com.apple.documentation/documentation/UIKitCore/nsrulerview> and
/// <doc://com.apple.documentation/documentation/UIKitCore/nsrulermarker> objects.
///
/// The text system supports four alignment types: left, center, right, and
/// decimal (based on the decimal separator character of the locale in effect).
/// These alignment types are absolute, not based on the line sweep direction of
/// text. For example, tabbed text is always positioned to the left of a
/// right-aligned tab, whether the line sweep direction is left to right or
/// right to left. A tab's location, on the other hand, is relative to the back
/// margin. A tab set at 1.5", for example, is at 1.5" from the right in right
/// to left text.
UIKIT_EXTERN API_AVAILABLE(macos(10.0), ios(7.0), tvos(9.0), watchos(2.0), visionos(1.0))
@interface NSTextTab : NSObject <NSCopying, NSCoding, NSSecureCoding>

/// Returns the column terminators for the specified locale.
///
/// The returned value can be used as the value for
/// ``NSTextTab/OptionKey/columnTerminators`` to make a decimal tab stop.
///
/// - Parameters:
///   - aLocale: The locale to use when determining the terminators. Specify `nil` to use the system's current locale. You can get the user's locale using the <doc://com.apple.documentation/documentation/foundation/nslocale/1409990-current> method of <doc://com.apple.documentation/documentation/foundation/nslocale>.
///
/// - Returns: The characters for the column terminators.
+ (NSCharacterSet *)columnTerminatorsForLocale:(nullable NSLocale *)aLocale API_AVAILABLE(macos(10.11), ios(7.0), tvos(9.0), watchos(2.0), visionos(1.0));

/// Initializes a text tab with the text alignment, location, and options.
///
/// The text alignment is used to determine the position of text inside the tab column.
///
/// - Parameters:
///   - alignment: The text alignment for the tab column.
///   - loc: The location of the tab stop.
///   - options: Optional configuration attributes.
- (instancetype)initWithTextAlignment:(NSTextAlignment)alignment location:(CGFloat)loc options:(NSDictionary<NSTextTabOptionKey, id> *)options NS_DESIGNATED_INITIALIZER;

/// The text alignment of the text tab.
///
/// `NSTextAlignmentNatural` and `NSTextAlignmentJustified` are resolved to
/// either `NSTextAlignmentLeft` or `NSTextAlignmentRight` based on the user's
/// preferred language.
@property (readonly, NS_NONATOMIC_IOSONLY) NSTextAlignment alignment;

/// The text tab's ruler location relative to the back margin.
@property (readonly, NS_NONATOMIC_IOSONLY) CGFloat location;

/// The dictionary of attributes for the text tab.
@property (readonly, NS_NONATOMIC_IOSONLY) NSDictionary<NSTextTabOptionKey, id> *options;
@end


/// The paragraph or ruler attributes for an attributed string.
///
/// An ``NSParagraphStyle`` object stores formatting information for a paragraph
/// of text. The formatting information includes the amount of space between
/// lines, indentations for lines of text, line heights, tab-stop positions, and
/// more. Apply paragraph styles to the text of an attributed string by adding
/// the
/// <doc://com.apple.documentation/documentation/foundation/nsattributedstring/key/1527910-paragraphstyle>
/// attribute in Swift or the ``NSParagraphStyleAttributeName`` attribute in
/// Objective-C and setting its value to an instance of this class. The
/// text-rendering system uses the paragraph style information in an attributed
/// string to lay out and render the text.
///
/// The ``NSParagraphStyle`` class manages an immutable set of style
/// information, but you can create an ``NSMutableParagraphStyle`` when you want
/// to modify the style information before applying it to your text.
UIKIT_EXTERN API_AVAILABLE(macos(10.0), ios(6.0), tvos(9.0), watchos(2.0), visionos(1.0))
@interface NSParagraphStyle : NSObject <NSCopying, NSMutableCopying, NSSecureCoding>

/// The text alignment of the paragraph.
@property (readonly, NS_NONATOMIC_IOSONLY) NSTextAlignment alignment;

/// The default paragraph style.
///
/// The default paragraph style has the following default values:
///
/// | Subattribute | Default |
/// |---|---|
/// | Alignment | `NSNaturalTextAlignment` |
/// | Tab stops | 12 left-aligned tabs, spaced by `28.0` points |
/// | Line break mode | `NSLineBreakByWordWrapping` |
/// | All others | `0.0` |
///
/// See individual method descriptions for explanations of each subattribute.
@property (class, readonly, copy, NS_NONATOMIC_IOSONLY) NSParagraphStyle *defaultParagraphStyle;

/// Returns the default writing direction for the specified language.
///
/// - Parameters:
///   - languageName: The language specified in ISO language region format. Can be `nil` to return a default writing direction derived from the user's defaults database.
///
/// - Returns: The default writing direction.
+ (NSWritingDirection)defaultWritingDirectionForLanguage:(nullable NSString *)languageName;

/// The distance in points between the bottom of one line fragment and the top of the next.
///
/// This value is always nonnegative. The text layout manager uses this value in the
/// line fragment height.
@property (readonly, NS_NONATOMIC_IOSONLY) CGFloat lineSpacing;

/// Distance between the bottom of this paragraph and top of next.
///
/// This property contains the space (measured in points) between paragraphs.
/// This value is always nonnegative. The framework determines the space between
/// paragraphs by adding the previous paragraph's `paragraphSpacing` and the
/// current paragraph's ``NSParagraphStyle/paragraphSpacingBefore``.
@property (readonly, NS_NONATOMIC_IOSONLY) CGFloat paragraphSpacing;

// The following values are relative to the appropriate margin (depending on the paragraph direction)

/// The indentation of the paragraph's lines other than the first.
///
/// This property contains the distance (in points) from the leading margin of a
/// text container to the beginning of lines other than the first. This value is
/// always nonnegative.
@property (readonly, NS_NONATOMIC_IOSONLY) CGFloat headIndent;

/// The trailing indentation of the paragraph.
///
/// If positive, this value is the distance from the leading margin (for
/// example, the left margin in left-to-right text). If `0` or negative, it's
/// the distance from the trailing margin.
///
/// For example, a paragraph style designed to fit exactly in a two-inch wide
/// container has a head indent of `0.0` and a tail indent of `0.0`. One
/// designed to fit with a quarter-inch margin has a head indent of `0.25` and a
/// tail indent of `–0.25`.
@property (readonly, NS_NONATOMIC_IOSONLY) CGFloat tailIndent;

/// The indentation of the first line of the paragraph.
///
/// This property contains the distance (in points) from the leading margin of a
/// text container to the beginning of the paragraph's first line. This value is
/// always nonnegative.
@property (readonly, NS_NONATOMIC_IOSONLY) CGFloat firstLineHeadIndent;

/// The paragraph's minimum line height.
///
/// This property contains the minimum height in points that any line in the
/// receiver occupies, regardless of the font size or size of any attached
/// graphic. This value is always nonnegative.
@property (readonly, NS_NONATOMIC_IOSONLY) CGFloat minimumLineHeight;

/// The paragraph's maximum line height.
///
/// This property contains the maximum height in points that any line in the
/// receiver occupies, regardless of the font size or size of any attached
/// graphic. This value is always nonnegative. The default value is `0`.
///
/// Glyphs and graphics exceeding this height overlap neighboring lines;
/// however, a maximum height of `0` implies no line height limit. Although this
/// limit applies to the line itself, line spacing adds extra space between
/// adjacent lines.
@property (readonly, NS_NONATOMIC_IOSONLY) CGFloat maximumLineHeight;

/// The mode for breaking lines in the paragraph that don't fit within a container.
///
/// This property controls how the text system lays out lines that don't fit in
/// its container, such as by truncating with an ellipsis (…) or clipping the
/// text. This is different from ``NSParagraphStyle/LineBreakStrategy``, which
/// controls where the system places line breaks in a paragraph.
@property (readonly, NS_NONATOMIC_IOSONLY) NSLineBreakMode lineBreakMode;

/// The base writing direction for the paragraph.
///
/// If the value of this property is ``NSWritingDirection/natural``, the
/// consumer of the value must resolve the writing direction based on the
/// paragraph contents using the Unicode Bidi Algorithm.
@property (readonly, NS_NONATOMIC_IOSONLY) NSWritingDirection baseWritingDirection;

/// The line height multiple.
///
/// The framework multiplies the natural line height of the receiver by this
/// factor (if positive), and constrains the resulting value by the minimum and
/// maximum line height. The default value of this property is `0.0`.
@property (readonly, NS_NONATOMIC_IOSONLY) CGFloat lineHeightMultiple;

/// The distance between the paragraph's top and the beginning of its text content.
///
/// This property contains the space (measured in points) between the current
/// and previous paragraphs. The default value of this property is `0.0`.
@property (readonly, NS_NONATOMIC_IOSONLY) CGFloat paragraphSpacingBefore;

/// The paragraph's threshold for hyphenation.
///
/// The system attempts hyphenation when the ratio of the text width (as broken
/// without hyphenation) to the width of the line fragment is less than the
/// hyphenation factor. When the paragraph's hyphenation factor is `0.0`, the
/// system uses the text layout manager's hyphenation factor instead. The system
/// disables hyphenation when both are `0.0`. This property detects the
/// user-selected language by examining the first item in
/// <doc://com.apple.documentation/documentation/foundation/nslocale/1415614-preferredlanguages>.
///
/// ## See Also
///
/// - <doc://com.apple.documentation/documentation/coretext/kCTLanguageAttributeName>
@property (readonly, NS_NONATOMIC_IOSONLY) float hyphenationFactor;

/// A Boolean value that indicates whether the paragraph style uses the system hyphenation settings.
///
/// The system determines the exact hyphenation logic dynamically by examining
/// the layout context such as language, platform, etc. When `true`, it affects
/// the return value from ``hyphenationFactor`` when the property is set to
/// `0.0`.
@property (readonly, NS_NONATOMIC_IOSONLY) BOOL usesDefaultHyphenation API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0), watchos(8.0), visionos(1.0));

/// The text tab objects that represent the paragraph's tab stops.
///
/// The ``NSTextTab`` objects, sorted by location, define the tab stops for the
/// paragraph style. The default value is an array of 12 left-aligned tabs at
/// 28-point intervals.
@property (readonly,copy, NS_NONATOMIC_IOSONLY) NSArray<NSTextTab *> *tabStops API_AVAILABLE(macos(10.0), ios(7.0), tvos(9.0), watchos(2.0), visionos(1.0));

/// The documentwide default tab interval.
///
/// This property represents the default tab interval in points. Tabs after the
/// last specified in ``NSParagraphStyle/tabStops`` are placed at integer
/// multiples of this distance (if positive). Default value is `0.0`.
@property (readonly, NS_NONATOMIC_IOSONLY) CGFloat defaultTabInterval API_AVAILABLE(macos(10.0), ios(7.0), tvos(9.0), watchos(2.0), visionos(1.0));

/// The text lists that contain the paragraph, nested from outermost to innermost.
@property (readonly, copy, NS_NONATOMIC_IOSONLY) NSArray<NSTextList *> *textLists API_AVAILABLE(macos(10.0), ios(7.0), tvos(9.0), watchos(2.0), visionos(1.0));

/// The text blocks that contain the paragraph, nested from outermost to innermost.
@property (readonly, copy, NS_NONATOMIC_IOSONLY) NSArray<__kindof NSTextBlock *> *textBlocks API_AVAILABLE(macos(10.0), ios(6.0), tvos(9.0), visionos(1.0), watchos(2.0));

/// A Boolean value that indicates whether the system tightens character spacing before truncating text.
///
/// When this property is
/// <doc://com.apple.documentation/documentation/swift/true>, the system tries
/// to reduce the space between characters before truncating characters. The
/// system performs this tightening in cases where the text wouldn't otherwise
/// fit in the available space. The maximum amount of tightening performed by
/// the system is dependent on the font, line width, and other factors.
///
/// The default value of this property is
/// <doc://com.apple.documentation/documentation/swift/false>.
@property (readonly, NS_NONATOMIC_IOSONLY) BOOL allowsDefaultTighteningForTruncation API_AVAILABLE(macos(10.11), ios(9.0), tvos(9.0), watchos(2.0), visionos(1.0));

/// The strategy for breaking lines while laying out paragraphs.
///
/// Line-break strategies are collections of options the system uses to
/// determine where to break lines in a paragraph. This is different from
/// ``NSParagraphStyle/lineBreakMode``, which controls how to lay out lines of
/// text that don't fit in a container. The system ignores this property if the
/// paragraph style's ``NSParagraphStyle/lineBreakMode`` property specifies a
/// mode that doesn't support multiple lines, such as
/// ``NSLineBreakMode/byClipping``.
///
/// The default value is ``NSLineBreakStrategy/NSLineBreakStrategyNone``.
@property (readonly, NS_NONATOMIC_IOSONLY) NSLineBreakStrategy lineBreakStrategy API_AVAILABLE(macos(10.11), ios(9.0), tvos(9.0), watchos(2.0), visionos(1.0));

@end


/// An object for changing the values of the subattributes in a paragraph style attribute.
///
/// The ``NSMutableParagraphStyle`` class adds methods to its superclass,
/// ``NSParagraphStyle``, for changing the values of the subattributes in a
/// paragraph style attribute. For more information, see ``NSParagraphStyle``
/// and
/// <doc://com.apple.documentation/documentation/foundation/nsattributedstring>.
///
/// > Important:
/// > Don't mutate a paragraph style object after adding it to an attributed
///   string. Doing so can cause your app to crash.
UIKIT_EXTERN API_AVAILABLE(macos(10.0), ios(6.0), tvos(9.0), watchos(2.0), visionos(1.0))
@interface NSMutableParagraphStyle : NSParagraphStyle

/// The text alignment of the paragraph.
@property (NS_NONATOMIC_IOSONLY) NSTextAlignment alignment;

/// The distance in points between the bottom of one line fragment and the top of the next.
///
/// This value is always nonnegative. This value is included in the line
/// fragment heights in the text layout manager.
@property (NS_NONATOMIC_IOSONLY) CGFloat lineSpacing;

/// The space after the end of the paragraph.
///
/// This property contains the space (measured in points) added at the end of
/// the paragraph to separate it from the following paragraph. This value must
/// be nonnegative. The space between paragraphs is determined by adding the
/// previous paragraph's `paragraphSpacing` and the current paragraph's
/// ``NSMutableParagraphStyle/paragraphSpacingBefore``.
@property (NS_NONATOMIC_IOSONLY) CGFloat paragraphSpacing;

/// The indentation of the first line of the paragraph.
///
/// This property contains the distance (in points) from the leading margin of a
/// text container to the beginning of the paragraph's first line. This value is
/// always nonnegative.
@property (NS_NONATOMIC_IOSONLY) CGFloat firstLineHeadIndent;

/// The indentation of the paragraph's lines other than the first.
///
/// This property contains the distance (in points) from the leading margin of a
/// text container to the beginning of lines other than the first. This value is
/// always nonnegative.
@property (NS_NONATOMIC_IOSONLY) CGFloat headIndent;

/// The trailing indentation of the paragraph.
///
/// If positive, this value is the distance from the leading margin (for
/// example, the left margin in left-to-right text). If `0` or negative, it's
/// the distance from the trailing margin.
///
/// For example, a paragraph style designed to fit exactly in a 2-inch wide
/// container has a head indent of `0.0` and a tail indent of `0.0`. One
/// designed to fit with a quarter-inch margin has a head indent of `0.25` and
/// a tail indent of `–0.25`.
@property (NS_NONATOMIC_IOSONLY) CGFloat tailIndent;

/// The mode for breaking lines in the paragraph.
///
/// This property controls how the text system lays out lines that don't fit in
/// its container, such as by truncating with an ellipsis (…) or clipping the
/// text. This is different from ``NSParagraphStyle/LineBreakStrategy``, which
/// controls where the system places line breaks in a paragraph.
@property (NS_NONATOMIC_IOSONLY) NSLineBreakMode lineBreakMode;

/// The paragraph's minimum line height.
///
/// This property contains the minimum height in points that any line in the
/// receiver will occupy, regardless of the font size or size of any attached
/// graphic. This value must be nonnegative.
@property (NS_NONATOMIC_IOSONLY) CGFloat minimumLineHeight;

/// The paragraph's maximum line height.
///
/// This property contains the maximum height in points that any line in the
/// receiver will occupy, regardless of the font size or size of any attached
/// graphic. This value is always nonnegative. The default value is `0`.
///
/// Glyphs and graphics exceeding this height will overlap neighboring lines;
/// however, a maximum height of `0` implies no line height limit. Although this
/// limit applies to the line itself, line spacing adds extra space between
/// adjacent lines.
@property (NS_NONATOMIC_IOSONLY) CGFloat maximumLineHeight;

/// The base writing direction for the paragraph.
///
/// If you specify ``NSWritingDirection/natural``, the consumer of the value
/// must resolve the writing direction based on the paragraph contents using
/// the Unicode Bidi Algorithm.
@property (NS_NONATOMIC_IOSONLY) NSWritingDirection baseWritingDirection;

/// The line height multiple.
///
/// The natural line height of the receiver is multiplied by this factor (if
/// positive) before being constrained by minimum and maximum line height. The
/// default value of this property is `0.0`.
@property (NS_NONATOMIC_IOSONLY) CGFloat lineHeightMultiple;

/// The distance between the paragraph's top and the beginning of its text content.
///
/// This property contains the space (measured in points) between the
/// paragraph's top and the beginning of its text content. The default value of
/// this property is `0.0`.
@property (NS_NONATOMIC_IOSONLY) CGFloat paragraphSpacingBefore;

/// The paragraph's threshold for hyphenation.
///
/// Valid values lie between `0.0` and `1.0` inclusive. The default value is
/// `0.0`. Hyphenation is attempted when the ratio of the text width (as broken
/// without hyphenation) to the width of the line fragment is less than the
/// hyphenation factor. When the paragraph's hyphenation factor is `0.0`, the
/// text layout manager's hyphenation factor is used instead. When both are `0.0`,
/// hyphenation is disabled. This property detects the user-selected language by
/// examining the first item in `preferredLanguages`.
///
/// ## See Also
///
/// - <doc://com.apple.documentation/documentation/coretext/kCTLanguageAttributeName>
@property (NS_NONATOMIC_IOSONLY) float hyphenationFactor;

/// A Boolean value that indicates whether the paragraph style uses the system hyphenation settings.
///
/// The system determines the exact hyphenation logic dynamically by examining
/// the layout context such as language, platform, etc. When `true`, it affects
/// the return value from ``hyphenationFactor`` when the property is set to
/// `0.0`.
@property (readwrite, NS_NONATOMIC_IOSONLY) BOOL usesDefaultHyphenation API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0), watchos(8.0), visionos(1.0));

/// The text tab objects that represent the paragraph's tab stops.
///
/// The ``NSTextTab`` objects, sorted by location, define the tab stops for the
/// paragraph style. The default value is an array of 12 left-aligned tabs at
/// 28-point intervals.
@property (null_resettable, copy, NS_NONATOMIC_IOSONLY) NSArray<NSTextTab *> *tabStops API_AVAILABLE(macos(10.0), ios(7.0), tvos(9.0), watchos(2.0), visionos(1.0));

/// A number used as the document's default tab spacing.
///
/// This property represents the default tab interval in points. The system
/// places tabs after the last specified in ``tabStops`` at integer multiples of
/// this distance (if positive). Default value is `0.0`.
@property (NS_NONATOMIC_IOSONLY) CGFloat defaultTabInterval API_AVAILABLE(macos(10.0), ios(7.0), tvos(9.0), watchos(2.0), visionos(1.0));

/// A Boolean value that indicates whether the system tightens intercharacter spacing before truncating text.
///
/// When this property is set to
/// <doc://com.apple.documentation/documentation/swift/true>, the system tries
/// to reduce the space between characters before truncating characters. The
/// system performs this tightening in cases where the text would not otherwise
/// fit in the available space. The maximum amount of tightening performed by
/// the system is dependent on the font, line width, and other factors.
///
/// The default value of this property is
/// <doc://com.apple.documentation/documentation/swift/false>.
@property (NS_NONATOMIC_IOSONLY) BOOL allowsDefaultTighteningForTruncation API_AVAILABLE(macos(10.11), ios(9.0), tvos(9.0), watchos(2.0), visionos(1.0));

/// The strategies that the text system may use to break lines while laying out the paragraph.
///
/// Line-break strategies are collections of options the system uses to
/// determine where to break lines in a paragraph. This is different from
/// ``NSParagraphStyle/lineBreakMode``, which controls how to lay out lines of
/// text that don't fit in a container. The system ignores this property if the
/// paragraph style's ``NSParagraphStyle/lineBreakMode`` property specifies a
/// mode that doesn't support multiple lines, such as
/// ``NSLineBreakMode/byClipping``.
///
/// The default value is ``NSLineBreakStrategy/NSLineBreakStrategyNone``.
@property (NS_NONATOMIC_IOSONLY) NSLineBreakStrategy lineBreakStrategy API_AVAILABLE(macos(10.11), ios(9.0), tvos(9.0), watchos(2.0), visionos(1.0));

/// The text lists that contain the paragraph.
@property (NS_NONATOMIC_IOSONLY, copy) NSArray<NSTextList *> *textLists API_AVAILABLE(macos(10.0), ios(7.0), tvos(9.0), watchos(2.0), visionos(1.0));

/// The text blocks that contain the paragraph.
@property (copy, NS_NONATOMIC_IOSONLY) NSArray<__kindof NSTextBlock *> *textBlocks API_AVAILABLE(macos(10.0), ios(6.0), tvos(9.0), visionos(1.0), watchos(2.0));

/// Adds the specified tab stop to the paragraph.
///
/// ## See Also
///
/// - ``tabStops``
- (void)addTabStop:(NSTextTab *)anObject API_AVAILABLE(macos(10.0), ios(9.0), tvos(9.0), watchos(2.0), visionos(1.0));

/// Removes the first text tab with a location and type equal to the specified tab stop.
///
/// ## See Also
///
/// - ``tabStops``
- (void)removeTabStop:(NSTextTab *)anObject API_AVAILABLE(macos(10.0), ios(9.0), tvos(9.0), watchos(2.0), visionos(1.0));

/// Replaces the subattributes of the paragraph with those in the specified paragraph style object.
- (void)setParagraphStyle:(NSParagraphStyle *)obj API_AVAILABLE(macos(10.0), ios(9.0), tvos(9.0), watchos(2.0), visionos(1.0));

@end

NS_HEADER_AUDIT_END(nullability, sendability)
#else
#import <UIFoundation/NSParagraphStyle.h>
#endif
