#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIFoundation/NSTextLineFragment.h>)
//
//  NSTextLineFragment.h
//  Text Kit
//
//  Copyright (c) 2017-2025, Apple Inc. All rights reserved.
//

#import <Foundation/NSArray.h>
#import <Foundation/NSAttributedString.h>
#import <CoreGraphics/CoreGraphics.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

#pragma mark NSTextLineFragment
/// A class that represents a line fragment as a single textual layout and rendering unit inside a text layout fragment.
API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0), visionos(1.0)) API_UNAVAILABLE(watchos)
@interface NSTextLineFragment : NSObject <NSSecureCoding>
#pragma mark Initialization
/// Creates a new line fragment with the attributed string and range you provide.
///
/// - Parameters:
///   - attributedString: The source attributed string.
///   - range: An <doc://com.apple.documentation/documentation/foundation/nsrange> that specifies which characters to include.
- (instancetype)initWithAttributedString:(NSAttributedString *)attributedString range:(NSRange)range NS_DESIGNATED_INITIALIZER;
/// Creates a new line fragment from the coder you provide.
///
/// - Parameters:
///   - aDecoder: A coder that conforms to <doc://com.apple.documentation/documentation/foundation/nscoder>.
- (nullable instancetype)initWithCoder:(NSCoder *)aDecoder NS_DESIGNATED_INITIALIZER;

/// Creates a new line fragment with the string, attributes, and range you provide.
- (instancetype)initWithString:(NSString *)string attributes:(NSDictionary<NSAttributedStringKey, id> *)attributes range:(NSRange)range;

- (instancetype)init NS_UNAVAILABLE;

#pragma mark Basic properties
/// The source attributed string.
@property (strong, readonly) NSAttributedString *attributedString;

/// The string range for the source attributed string corresponding to this line fragment.
@property (readonly) NSRange characterRange;

#pragma mark Typographic bounds
/// The typographic bounds specifying the dimensions of the line fragment for laying out line fragments to each other.
///
/// The origin value is offset from the beginning of the line fragment group
/// belonging to the parent layout fragment.
@property (readonly) CGRect typographicBounds;

#pragma mark Rendering
/// The rendering origin for the leftmost glyph in the line fragment coordinate system.
@property (readonly) CGPoint glyphOrigin;

/// Renders the line fragment contents at the specified point.
///
/// The origin can be specified as
/// `(CGRectGetMinX(typographicBounds), CGRectGetMinY(typographicBounds))`
/// relative to the parent layout fragment coordinate system.
///
/// - Parameters:
///   - point: The origin as a <doc://com.apple.documentation/documentation/corefoundation/cgpoint>.
///   - context: The graphics context to draw into.
- (void)drawAtPoint:(CGPoint)point inContext:(CGContextRef)context;

#pragma mark Character and point mappings
/// Returns the location of the character at the specified index.
///
/// The location is on the upstream edge of the glyph, in the coordinate system
/// relative to the line fragment origin.
///
/// - Parameters:
///   - index: The character index within this line fragment.
///
/// - Returns: A <doc://com.apple.documentation/documentation/corefoundation/cgpoint> on the upstream edge of the glyph, in the coordinate system relative to the line fragment origin.
- (CGPoint)locationForCharacterAtIndex:(NSInteger)index;

/// Returns the character index for the point inside the line fragment coordinate system.
///
/// - Parameters:
///   - point: A <doc://com.apple.documentation/documentation/corefoundation/cgpoint> in the line fragment coordinate system.
///
/// - Returns: The character index nearest to the point.
- (NSInteger)characterIndexForPoint:(CGPoint)point;

/// Returns the fraction of the distance through the glyph for the point.
///
/// The fraction of distance is from the upstream edge.
///
/// - Parameters:
///   - point: A <doc://com.apple.documentation/documentation/corefoundation/cgpoint> in the line fragment coordinate system.
///
/// - Returns: A value between 0.0 and 1.0 indicating the fraction through the glyph.
- (CGFloat)fractionOfDistanceThroughGlyphForPoint:(CGPoint)point;

@end
NS_HEADER_AUDIT_END(nullability, sendability)
#else
#import <UIFoundation/NSTextLineFragment.h>
#endif
