#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIFoundation/NSTextElement.h>)
//
//  NSTextElement.h
//  Text Kit
//
//  Copyright (c) 2018-2025, Apple Inc. All rights reserved.
//


#import <Foundation/NSArray.h>

@class NSTextRange;
@class NSTextContentManager;

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

/// An abstract base class that represents the smallest units of text layout such as paragraphs or attachments.
///
/// A text element is associated with an ``NSTextContentManager``.
API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0), visionos(1.0)) API_UNAVAILABLE(watchos)
@interface NSTextElement : NSObject
#pragma mark Initialization
/// Creates a new text element with the content manager you provide.
///
/// - Parameters:
///   - textContentManager: The content manager to associate with this element.
- (instancetype)initWithTextContentManager:(nullable NSTextContentManager *)textContentManager NS_DESIGNATED_INITIALIZER;

#pragma mark Properties
/// The value that represents the current content manager.
///
/// A text element can migrate between text content managers.
@property (nullable, weak) NSTextContentManager *textContentManager;

/// A range value that represents the range of the element inside the document.
@property (nullable, strong) NSTextRange *elementRange;

#pragma mark Child Elements
/// An array of zero or more child text elements.
///
/// A concrete `NSTextElement` subclass can be structured in a tree. An element
/// can have zero or more child elements.
@property (readonly, copy) NSArray<__kindof NSTextElement *> *childElements API_AVAILABLE(macos(13.0), ios(16.0), tvos(16.0), visionos(1.0)) API_UNAVAILABLE(watchos);

/// A value that represents the parent element if this text element is a child of an enclosing element.
@property (nullable, readonly, weak) __kindof NSTextElement *parentElement API_AVAILABLE(macos(13.0), ios(16.0), tvos(16.0), visionos(1.0)) API_UNAVAILABLE(watchos);

/// A Boolean value that indicates whether this element is in the text layout.
///
/// When `true`, the element is enumerated by ``NSTextContentManager``.
@property (readonly) BOOL isRepresentedElement API_AVAILABLE(macos(13.0), ios(16.0), tvos(16.0), visionos(1.0)) API_UNAVAILABLE(watchos);

@end

#pragma mark NSTextParagraph
/// A class that represents a single paragraph backed by an attributed string as the contents.
API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0), visionos(1.0)) API_UNAVAILABLE(watchos)
@interface NSTextParagraph : NSTextElement
#pragma mark Initialization
/// Creates a new paragraph with the attributed string you provide.
///
/// - Parameters:
///   - attributedString: The attributed string for the paragraph contents.
- (instancetype)initWithAttributedString:(nullable NSAttributedString *)attributedString NS_DESIGNATED_INITIALIZER;

#pragma mark Contents
/// The source attributed string.
@property (strong, readonly) NSAttributedString *attributedString;

/// The range of the paragraph's content within the document.
///
/// The paragraph's content is the text up to but not including the paragraph
/// separator. Together with ``paragraphSeparatorRange``, this range covers the
/// entire ``NSTextElement/elementRange``.
@property (nullable, strong, readonly) NSTextRange *paragraphContentRange;

/// The range of the paragraph separator within the document.
///
/// Together with ``paragraphContentRange``, this range covers the entire
/// ``NSTextElement/elementRange``.
@property (nullable, strong, readonly) NSTextRange *paragraphSeparatorRange;
@end
NS_HEADER_AUDIT_END(nullability, sendability)
#else
#import <UIFoundation/NSTextElement.h>
#endif
