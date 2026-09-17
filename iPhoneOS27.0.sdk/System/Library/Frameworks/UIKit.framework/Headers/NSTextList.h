#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIFoundation/NSTextList.h>)
//
//  NSTextList.h
//  Text Kit
//
//  Copyright (c) 2004-2025, Apple Inc. All rights reserved.

#import <Foundation/NSObject.h>
#import <UIKit/UIKitDefines.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)
/// A section of text that forms a single list.
///
/// `NSTextList` represents a stylistic format of a group of text list items
/// belonging to the same nested level. It supports both ordered and unordered
/// lists. The type of marker is defined by ``markerFormat``.

/// Values for available options for text list items.
typedef NS_OPTIONS(NSUInteger, NSTextListOptions) {
    /// Specifies that a nested list should include the marker for its enclosing superlist before its own marker.
    NSTextListPrependEnclosingMarker API_AVAILABLE(macos(10.0), ios(7.0), tvos(9.0), watchos(2.0), visionos(1.0)) = (1 << 0),
} API_AVAILABLE(macos(10.0), ios(7.0), tvos(9.0), watchos(2.0), visionos(1.0));

typedef NSString * NSTextListMarkerFormat NS_TYPED_EXTENSIBLE_ENUM API_AVAILABLE(macos(10.0), ios(7.0), tvos(9.0), watchos(2.0), visionos(1.0));
/// The value that represents a square-shaped marker that you can apply to a text list item.
UIKIT_EXTERN NSTextListMarkerFormat const NSTextListMarkerBox API_AVAILABLE(macos(10.0), ios(7.0), tvos(9.0), watchos(2.0), visionos(1.0));
/// The value that represents a checkmark-shaped marker that you can apply to a text list item.
UIKIT_EXTERN NSTextListMarkerFormat const NSTextListMarkerCheck API_AVAILABLE(macos(10.0), ios(7.0), tvos(9.0), watchos(2.0), visionos(1.0));
/// The value that represents a circle-shaped marker that you can apply to a text list item.
UIKIT_EXTERN NSTextListMarkerFormat const NSTextListMarkerCircle API_AVAILABLE(macos(10.0), ios(7.0), tvos(9.0), watchos(2.0), visionos(1.0));
/// The value that represents a diamond-shaped marker that you can apply to a text list item.
UIKIT_EXTERN NSTextListMarkerFormat const NSTextListMarkerDiamond API_AVAILABLE(macos(10.0), ios(7.0), tvos(9.0), watchos(2.0), visionos(1.0));
/// The value that represents a disc-shaped marker that you can apply to a text list item.
UIKIT_EXTERN NSTextListMarkerFormat const NSTextListMarkerDisc API_AVAILABLE(macos(10.0), ios(7.0), tvos(9.0), watchos(2.0), visionos(1.0));
/// The value that represents a hyphen-shaped marker that you can apply to a text list item.
UIKIT_EXTERN NSTextListMarkerFormat const NSTextListMarkerHyphen API_AVAILABLE(macos(10.0), ios(7.0), tvos(9.0), watchos(2.0), visionos(1.0));
/// The value that represents a square-shaped marker that you can apply to a text list item.
UIKIT_EXTERN NSTextListMarkerFormat const NSTextListMarkerSquare API_AVAILABLE(macos(10.0), ios(7.0), tvos(9.0), watchos(2.0), visionos(1.0));
/// The value that represents a lowercase hexadecimal (base 16) numerical marker that you can apply to a text list item.
UIKIT_EXTERN NSTextListMarkerFormat const NSTextListMarkerLowercaseHexadecimal API_AVAILABLE(macos(10.0), ios(7.0), tvos(9.0), watchos(2.0), visionos(1.0));
/// The value that represents an uppercase hexadecimal (base 16) numerical marker that you can apply to a text list item.
UIKIT_EXTERN NSTextListMarkerFormat const NSTextListMarkerUppercaseHexadecimal API_AVAILABLE(macos(10.0), ios(7.0), tvos(9.0), watchos(2.0), visionos(1.0));
/// The value that represents an octal (base 8) numerical marker that you can apply to a text list item.
UIKIT_EXTERN NSTextListMarkerFormat const NSTextListMarkerOctal API_AVAILABLE(macos(10.0), ios(7.0), tvos(9.0), watchos(2.0), visionos(1.0));
/// The value that represents a lowercase localized alphabetical marker that you can apply to a text list item.
UIKIT_EXTERN NSTextListMarkerFormat const NSTextListMarkerLowercaseAlpha API_AVAILABLE(macos(10.0), ios(7.0), tvos(9.0), watchos(2.0), visionos(1.0));
/// The value that represents an uppercase localized alphabetical marker that you can apply to a text list item.
UIKIT_EXTERN NSTextListMarkerFormat const NSTextListMarkerUppercaseAlpha API_AVAILABLE(macos(10.0), ios(7.0), tvos(9.0), watchos(2.0), visionos(1.0));
/// The value that represents a lowercase Latin alphabetical marker that you can apply to a text list item.
///
/// Lowercase Latin alphabetical markers follow the pattern a, b, c, and so on.
UIKIT_EXTERN NSTextListMarkerFormat const NSTextListMarkerLowercaseLatin API_AVAILABLE(macos(10.0), ios(7.0), tvos(9.0), watchos(2.0), visionos(1.0));
/// The value that represents an uppercase Latin alphabetical marker that you can apply to a text list item.
///
/// Uppercase Latin alphabetical markers follow the pattern A, B, C, and so on.
UIKIT_EXTERN NSTextListMarkerFormat const NSTextListMarkerUppercaseLatin API_AVAILABLE(macos(10.0), ios(7.0), tvos(9.0), watchos(2.0), visionos(1.0));
/// The value that represents a lowercase Roman numeral marker that you can apply to a text list item.
///
/// Lowercase Roman numeral markers follow the pattern i, ii, iii, iv, and so on.
UIKIT_EXTERN NSTextListMarkerFormat const NSTextListMarkerLowercaseRoman API_AVAILABLE(macos(10.0), ios(7.0), tvos(9.0), watchos(2.0), visionos(1.0));
/// The value that represents an uppercase Roman numeral marker that you can apply to a text list item.
///
/// Uppercase Roman numeral markers follow the pattern I, II, III, IV, and so on.
UIKIT_EXTERN NSTextListMarkerFormat const NSTextListMarkerUppercaseRoman API_AVAILABLE(macos(10.0), ios(7.0), tvos(9.0), watchos(2.0), visionos(1.0));
/// The value that represents a decimal annotation marker that you can apply to a text list item.
///
/// Decimal annotation markers follow the pattern 1.0, 1.1, 2.0, and so on.
UIKIT_EXTERN NSTextListMarkerFormat const NSTextListMarkerDecimal API_AVAILABLE(macos(10.0), ios(7.0), tvos(9.0), watchos(2.0), visionos(1.0));

/// A section of text that forms a single list.
///
/// The visible elements of the list, including list markers, appear in the text
/// as they do for lists created by hand. The list object, however, allows the
/// list to be recognized as such by the text system. This enables automatic
/// creation of markers and spacing. Text lists are used in HTML import and
/// export.
///
/// Text lists appear as attributes on paragraphs, as part of the paragraph
/// style. An ``NSParagraphStyle`` may have an array of text lists, representing
/// the nested lists containing the paragraph, in order from outermost to
/// innermost. For example, if list1 contains four paragraphs, the middle two of
/// which are also in the inner list2, then the text lists array for the first
/// and fourth paragraphs is (list1), while the text lists array for the second
/// and third paragraphs is (list1, list2).
///
/// The methods implementing this are ``NSParagraphStyle/textLists`` on
/// ``NSParagraphStyle``, and ``NSMutableParagraphStyle/textLists`` on
/// ``NSMutableParagraphStyle``.
///
/// In addition,
/// <doc://com.apple.documentation/documentation/foundation/nsattributedstring>
/// has convenience methods for lists, such as
/// <doc://com.apple.documentation/documentation/foundation/nsattributedstring/1525314-range>,
/// which determines the range covered by a list, and
/// <doc://com.apple.documentation/documentation/foundation/nsattributedstring/1527303-itemnumber>,
/// which determines the ordinal position within a list of a particular item.
API_AVAILABLE(macos(10.0), ios(7.0), tvos(9.0), watchos(2.0), visionos(1.0))
@interface NSTextList : NSObject <NSSecureCoding, NSCopying>

#pragma mark Initialization
/// Returns a new text list with the format, options, and starting item number you provide.
///
/// - Parameters:
///   - markerFormat: One of the possible ``NSTextList/MarkerFormat`` formats.
///   - options: One or more of the possible ``NSTextList/Options`` options.
///   - startingItemNumber: An integer that represents the starting item number.
- (instancetype)initWithMarkerFormat:(NSTextListMarkerFormat)markerFormat options:(NSTextListOptions)options startingItemNumber:(NSInteger)startingItemNumber NS_DESIGNATED_INITIALIZER API_AVAILABLE(macos(13.0), ios(16.0), tvos(16.0), watchos(9.0), visionos(1.0));

/// Returns an initialized text list.
///
/// The marker format is specified as a constant string, except for a numbering
/// specifier, which takes the form `{`keyword`}`. The currently supported
/// values for keyword include:
///
/// - `box`
/// - `check`
/// - `circle`
/// - `diamond`
/// - `disc`
/// - `hyphen`
/// - `square`
/// - `lower-hexadecimal`
/// - `upper-hexadecimal`
/// - `octal`
/// - `lower-alpha` or `lower-latin`
/// - `upper-alpha` or `upper-latin`
/// - `lower-roman`
/// - `upper-roman`
/// - `decimal`
///
/// Thus, for example, `@"({decimal})"` would specify the format for a list
/// numbered (1), (2), (3), and so on, and `@"{upper-roman}"` would specify the
/// format for a list numbered I, II, III, IV, and so on. (All of these keywords
/// are included in the Cascading Style Sheets level 3 specification.)
///
/// - Parameters:
///   - markerFormat: The marker format for the text list.
///   - options: The marker options for the text list.
///
/// - Returns: An initialized text list.
///
/// ## See Also
///
/// - ``markerFormat``
/// - ``listOptions``
- (instancetype)initWithMarkerFormat:(NSTextListMarkerFormat)markerFormat options:(NSUInteger)options;

/// Initializes and returns a newly allocated text list item.
///
/// - Parameters:
///   - coder: An instance of <doc://com.apple.documentation/documentation/foundation/nscoder>.
- (nullable instancetype) initWithCoder:(NSCoder *)coder NS_DESIGNATED_INITIALIZER;

#pragma mark Properties
/// The marker format string used by the receiver.
///
/// ## See Also
///
/// - ``NSTextList/init(markerFormat:options:)``
@property (readonly, strong) NSTextListMarkerFormat markerFormat;

/// The list options mask value of the receiver.
@property (readonly) NSTextListOptions listOptions;

#pragma mark Ordered List
/// The starting item number for the text list.
///
/// The default value is `1`. This value will be used only for ordered lists,
/// and ignored in other cases.
@property NSInteger startingItemNumber;

/// A Boolean value that indicates whether the list is ordered.
@property (readonly, getter=isOrdered) BOOL ordered API_AVAILABLE(macos(13.0), ios(16.0), tvos(16.0), watchos(9.0), visionos(1.0));

#pragma mark Resolved Marker String
/// Returns the computed value for a specific ordinal position in the list.
///
/// - Parameters:
///   - itemNumber: The ordinal position in the list whose computed marker value is desired. The receiver ignores this parameter if `itemNumber` is less than 1 or ``isOrdered`` is `false`.
///
/// - Returns: The computed marker value for `itemNumber`.
- (NSString *)markerForItemNumber:(NSInteger)itemNumber;

#pragma mark Marker handling
/// A Boolean value that indicates whether TextKit includes text list markers in the contents.
///
/// The default value is `false`.
@property (readonly, class) BOOL includesTextListMarkers API_AVAILABLE(macos(26.0), ios(26.0), tvos(26.0), watchos(26.0), visionos(26.0));
@end

NS_HEADER_AUDIT_END(nullability, sendability)
#else
#import <UIFoundation/NSTextList.h>
#endif
