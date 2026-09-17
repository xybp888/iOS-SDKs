#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIFoundation/NSTextListElement.h>)
//
//  NSTextListElement.h
//  Text Kit
//
//  Copyright (c) 2021-2025, Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/NSTextElement.h>

@class NSTextList;

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

/// A class that represents a text list node.
///
/// It can contain an array of child elements. A text list can be represented by
/// a tree of `NSTextListElement` objects.
#pragma mark NSTextListElement

API_AVAILABLE(macos(13.0), ios(16.0), tvos(16.0), visionos(1.0)) API_UNAVAILABLE(watchos)
@interface NSTextListElement : NSTextParagraph
#pragma mark Initializer
/// Creates a text list element with the parent, list elements, nesting level, and marker attributes you provide.
///
/// - Parameters:
///   - parent: The parent `NSTextListElement` of this element, if any.
///   - textList: The ``NSTextList`` to add elements to.
///   - contents: An <doc://com.apple.documentation/documentation/foundation/nsattributedstring> that contains the contents of the text list element.
///   - markerAttributes: A dictionary of <doc://com.apple.documentation/documentation/foundation/nsattributedstring/key> keys and values that describe the marker attributes.
///   - children: An array of ``NSTextListElement`` elements.
///
/// One of `contents`, `markerAttributes`, or `childElements` must be non-`nil`.
/// If `markerAttributes` is not `nil` this method uses it to format the marker;
/// otherwise it is derived from `contents`.
///
/// To instantiate a text list element with a specific type, use either
/// ``textListElementWithChildElements:textList:nestingLevel:`` or
/// ``textListElementWithContents:markerAttributes:textList:childElements:`` instead.
- (instancetype)initWithParentElement:(nullable NSTextListElement *)parent textList:(NSTextList *)textList contents:(nullable NSAttributedString *)contents markerAttributes:(nullable NSDictionary<NSAttributedStringKey, id> *)markerAttributes childElements:(nullable NSArray<NSTextListElement *> *)children NS_DESIGNATED_INITIALIZER;

- (instancetype)initWithAttributedString:(nullable NSAttributedString *)attributedString NS_UNAVAILABLE;

/// Creates a text list element with the list elements, nesting level, and marker attributes you provide.
///
/// - Parameters:
///   - contents: An <doc://com.apple.documentation/documentation/foundation/nsattributedstring> that contains the contents of the text list element.
///   - markerAttributes: A dictionary of <doc://com.apple.documentation/documentation/foundation/nsattributedstring/key> keys and values that describe the marker attributes.
///   - textList: The ``NSTextList`` to add elements to.
///   - children: An array of ``NSTextListElement`` elements.
+ (instancetype)textListElementWithContents:(NSAttributedString *)contents markerAttributes:(nullable NSDictionary<NSAttributedStringKey, id> *)markerAttributes textList:(NSTextList *)textList childElements:(nullable NSArray<NSTextListElement *> *)children;

/// Creates a text list element with the list elements and nesting level you provide.
///
/// Raises an exception when `nestingLevel < 0`.
///
/// - Parameters:
///   - children: An array of ``NSTextListElement`` elements.
///   - textList: The ``NSTextList`` to add elements to.
///   - nestingLevel: An integer value that describes the level of nesting of these elements.
///
/// - Returns: `nil` if `children.count` is zero.
+ (nullable instancetype)textListElementWithChildElements:(NSArray<NSTextListElement *> *)children textList:(NSTextList *)textList nestingLevel:(NSInteger)nestingLevel;

#pragma mark Properties
/// The value that represents the text list.
@property (readonly, strong) NSTextList *textList;

/// The text list element contents without markers and formatting.
@property (nullable, readonly, strong) NSAttributedString *contents;

/// A dictionary of attributed string keys and values that represent the list's marker attributes.
@property (nullable, readonly, strong) NSDictionary<NSAttributedStringKey, id> *markerAttributes;

/// An attributed string that represents the string the framework displays for this element taking into account markers and the indentation level of the list element.
///
/// Derived from ``contents`` and ``textList`` configured with the text list
/// element's position inside the tree. Overrides `NSTextParagraph.attributedString`.
@property (strong, readonly) NSAttributedString *attributedString;

#pragma mark Child Elements
/// An array that contains child text elements.
@property (readonly, copy) NSArray<NSTextListElement *> *childElements;

/// A text list element that refers to the enclosing text list element.
@property (nullable, readonly, weak) NSTextListElement *parentElement;
@end
 
NS_HEADER_AUDIT_END(nullability, sendability)

#else
#import <UIFoundation/NSTextListElement.h>
#endif
