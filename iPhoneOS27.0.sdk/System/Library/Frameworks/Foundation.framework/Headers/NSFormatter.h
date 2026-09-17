/*	NSFormatter.h
	Copyright (c) 1995-2019, Apple Inc. All rights reserved.
*/

#import <Foundation/NSObject.h>
#import <Foundation/NSRange.h>
#import <Foundation/NSAttributedString.h>

@class NSString;
@class NSAttributedString;
@class NSDictionary<KeyType, ObjectType>;

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

/// The formatting context for a formatter.
///
/// Use formatting contexts to specify where the result of formatting will appear, so that the formatter can provide the most appropriate result.
///
/// For example, when formatting a date or date symbol for a French locale, you want the month name to be capitalized if it appears at the beginning of the sentence,
/// but not if it appears elsewhere.
///
/// If the formatting context isn't known ahead of time, specify `NSFormattingContextDynamic` to have the system determine the context automatically.
typedef NS_ENUM(NSInteger, NSFormattingContext) {

    /// The capitalization context to be used is unknown (this is the default value).
    NSFormattingContextUnknown = 0,

    /// The capitalization context is determined dynamically from the set {NSFormattingContextStandalone, NSFormattingContextBeginningOfSentence, NSFormattingContextMiddleOfSentence}. For example, if a date is placed at the beginning of a sentence, NSFormattingContextBeginningOfSentence is used to format the string automatically. When this context is used, the formatter will return a string proxy that works like a normal string in most cases. After returning from the formatter, the string in the string proxy is formatted by using NSFormattingContextUnknown. When the string proxy is used in stringWithFormat:, we can determine where the %@ is and then set the context accordingly. With the new context, the string in the string proxy will be formatted again and be put into the final string returned from stringWithFormat:.
    NSFormattingContextDynamic = 1,

    /// The capitalization context if a date or date symbol is to be formatted with capitalization appropriate for stand-alone usage such as an isolated name on a calendar page.
    NSFormattingContextStandalone = 2,

    /// The capitalization context if a date or date symbol is to be formatted with capitalization appropriate for a list or menu item.
    NSFormattingContextListItem = 3,

    /// The capitalization context if a date or date symbol is to be formatted with capitalization appropriate for the beginning of a sentence.
    NSFormattingContextBeginningOfSentence = 4,

    /// The capitalization context if a date or date symbol is to be formatted with capitalization appropriate for the middle of a sentence.
    NSFormattingContextMiddleOfSentence = 5,

} API_AVAILABLE(macos(10.10), ios(8.0), watchos(2.0), tvos(9.0));

/// Specifies the width of the unit, determining the textual representation.
///
/// There are 3 widths: long, medium, and short.
/// For example, for English, when formatting "3 pounds":
/// Long is "3 pounds"; medium is "3 lb"; short is "3#".
typedef NS_ENUM(NSInteger, NSFormattingUnitStyle) {
    /// The shortest spelling for a unit.
    NSFormattingUnitStyleShort = 1,
    /// The medium-length spelling for a unit.
    NSFormattingUnitStyleMedium,
    /// The long spelling for a unit.
    NSFormattingUnitStyleLong,
} API_AVAILABLE(macos(10.10), ios(8.0), watchos(2.0), tvos(9.0));

// NSFormatter does not specify if it is Sendable. Subclasses should annotate themselves.
// This allows subclasses to declare sendable conformances without requiring that all subclasses must be sendable
NS_HEADER_AUDIT_END(sendability)
/// An abstract class that declares an interface for objects that create, interpret, and validate the textual representation of values.
///
/// The Foundation framework provides several concrete subclasses of ``Formatter``, including ``ByteCountFormatter``, ``DateFormatter``, ``DateComponentsFormatter``, ``DateIntervalFormatter``, ``MeasurementFormatter``, ``NumberFormatter``, and ``PersonNameComponentsFormatter``.
///
/// > Tip:
/// > In Swift, you can use implementations of ``FormatStyle`` rather than ``Formatter``. The ``FormatStyle`` API offers a declarative idiom for customizing the formatting of various types. Also, Foundation caches identical ``FormatStyle`` instances, so you don't need to pass them around your app, or risk wasting memory with duplicate formatters.
///
///
///
/// ### Subclassing Notes
///
/// ``Formatter`` is intended for subclassing. A custom formatter can restrict the input and enhance the display of data in novel ways. For example, you could have a custom formatter that ensures that serial numbers entered by a user conform to predefined formats. Before you decide to create a custom formatter, make sure that you cannot configure the public subclasses to satisfy your requirements.
///
/// For instructions on how to create your own custom formatter, see [Creating a Custom Formatter](https://developer.apple.com/library/archive/documentation/Cocoa/Conceptual/DataFormatting/Articles/CreatingACustomFormatter.html#//apple_ref/doc/uid/20000196).
@interface NSFormatter : NSObject <NSCopying, NSCoding>

/// Returns a string representation of a given object.
- (nullable NSString *)stringForObjectValue:(nullable id)obj;

/// Returns an attributed string representation of a given object.
- (nullable NSAttributedString *)attributedStringForObjectValue:(id)obj withDefaultAttributes:(nullable NSDictionary<NSAttributedStringKey, id> *)attrs;

/// Returns a string to use for editing a given object.
- (nullable NSString *)editingStringForObjectValue:(id)obj;

/// Returns by reference an object after creating it from a string.
- (BOOL)getObjectValue:(out id _Nullable * _Nullable)obj forString:(NSString *)string errorDescription:(out NSString * _Nullable * _Nullable)error;

/// Returns a Boolean value that indicates whether a partial string is valid.
///
/// Compatibility method.  If a subclass overrides this and does not override the new method below, this will be called as before (the new method just calls this one by default).  The selection range will always be set to the end of the text with this method if replacement occurs.
- (BOOL)isPartialStringValid:(NSString *)partialString newEditingString:(NSString * _Nullable * _Nullable)newString errorDescription:(NSString * _Nullable * _Nullable)error;

/// This method should be implemented in subclasses that want to validate user changes to a string in a field, where the user changes are not necessarily at the end of the string, and preserve the selection (or set a different one, such as selecting the erroneous part of the string the user has typed).
- (BOOL)isPartialStringValid:(NSString * _Nonnull * _Nonnull)partialStringPtr proposedSelectedRange:(nullable NSRangePointer)proposedSelRangePtr originalString:(NSString *)origString originalSelectedRange:(NSRange)origSelRange errorDescription:(NSString * _Nullable * _Nullable)error;

@end
NS_HEADER_AUDIT_BEGIN(sendability)

NS_HEADER_AUDIT_END(nullability, sendability)
