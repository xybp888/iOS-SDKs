#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIFoundation/NSTextSelection.h>)
//
//  NSTextSelection.h
//  Text Kit
//
//  Copyright (c) 2018-2025, Apple Inc. All rights reserved.
//

#import <Foundation/NSAttributedString.h>
#import <CoreGraphics/CGGeometry.h>

@class NSTextRange;
@protocol NSTextLocation;

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

/// A class that represents a single logical selection context that corresponds to an insertion point.
#pragma mark NSTextSelection

/// Values that describe the different granularities available to make a selection.
typedef NS_ENUM(NSInteger, NSTextSelectionGranularity) {
  /// A value that represents selection by character.
  NSTextSelectionGranularityCharacter,
  /// A value that represents selection by word.
  NSTextSelectionGranularityWord,
  /// A value that represents selection by paragraph.
  NSTextSelectionGranularityParagraph,
  /// A value that represents selection by line.
  NSTextSelectionGranularityLine,
  /// A value that represents selection by sentence.
  NSTextSelectionGranularitySentence
} API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0), visionos(1.0)) API_UNAVAILABLE(watchos);

/// Values that describe the visual location of the text cursor, or the direction of the non-anchored edge of the selection.
typedef NS_ENUM(NSInteger, NSTextSelectionAffinity) {
  /// The value that defines the visual location of the text cursor at the tail of the previous line.
  NSTextSelectionAffinityUpstream = 0,
  /// The value that defines the visual location of the text cursor at the head of the line containing the selection location.
  NSTextSelectionAffinityDownstream = 1
} API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0), visionos(1.0)) API_UNAVAILABLE(watchos);

API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0), visionos(1.0)) API_UNAVAILABLE(watchos)
@interface NSTextSelection : NSObject <NSSecureCoding>
#pragma mark Initialization
/// Creates a new text selection with the ranges, affinity, and granularity you specify.
///
/// `textRanges` should be ordered and not overlapping. Otherwise, they will be
/// normalized by reordering and merging overlapping ranges.
///
/// - Parameters:
///   - textRanges: An array of text ranges for this selection.
///   - affinity: The affinity of the selection.
///   - granularity: The granularity of the selection.
- (instancetype)initWithRanges:(NSArray<NSTextRange *> *)textRanges affinity:(NSTextSelectionAffinity)affinity granularity:(NSTextSelectionGranularity)granularity NS_DESIGNATED_INITIALIZER;
/// Creates a new text selection from the coder you provide.
///
/// - Parameters:
///   - coder: A coder that conforms to <doc://com.apple.documentation/documentation/foundation/nscoder>.
- (nullable instancetype)initWithCoder:(NSCoder *)coder NS_DESIGNATED_INITIALIZER;

/// Creates a new text selection with the range, affinity, and granularity you specify.
- (instancetype)initWithRange:(NSTextRange *)range affinity:(NSTextSelectionAffinity)affinity granularity:(NSTextSelectionGranularity)granularity;

/// Creates a new text selection at the specified location with the given affinity.
- (instancetype)initWithLocation:(id <NSTextLocation>)location affinity:(NSTextSelectionAffinity)affinity;

- (instancetype)init NS_UNAVAILABLE;

#pragma mark Basic properties
/// An array of disjoint logical ranges in the selection.
///
/// The array must be logically ordered. When editing, all ranges in a text
/// selection constitute a single insertion point.
@property (copy, readonly) NSArray<NSTextRange *> *textRanges;

/// The granularity of the selection.
///
/// `NSTextSelectionGranularityCharacter` by default. Extending operations
/// should modify the selection by the granularity.
@property (readonly) NSTextSelectionGranularity granularity;

/// Either upstream or downstream selection.
///
/// `NSTextSelectionAffinityDownstream` by default. For a 0-length selection, it
/// describes the visual location of the text cursor between the head of line
/// containing the selection location (downstream) or tail of the previous line
/// (upstream). For a selection with contents, it describes the logical direction
/// of the non-anchored edge of the selection.
@property (readonly) NSTextSelectionAffinity affinity;

/// A Boolean value indicating whether this is a transient text selection during drag handling.
@property (readonly, getter=isTransient) BOOL transient;

#pragma mark Navigation properties
/// The anchor position offset from the beginning of a line fragment in visual order.
///
/// That is, from the left for a horizontal line fragment and from the top for a
/// vertical. Navigating between lines uses this point when the current line
/// fragment associated with the selection is shorter than the next line visited.
/// The default value is `0.0`.
@property CGFloat anchorPositionOffset;

#pragma mark Visual selection
/// A Boolean value indicating whether the selection should be interpreted as logical or visual.
@property (getter=isLogical) BOOL logical;

/// The secondary character location when the user taps or clicks at a directional boundary.
///
/// Setting a non-nil location has a side effect of making ``logical`` `false`.
@property (strong, nullable) id <NSTextLocation> secondarySelectionLocation;

#pragma mark Typing attributes
/// The template attributes used for characters replacing the contents of this selection.
@property (copy) NSDictionary<NSAttributedStringKey, id> *typingAttributes;

#pragma mark Selection manipulation
/// Returns a copy of this selection, replacing the text ranges with the ones you provide.
///
/// All other attributes remain the same.
///
/// - Parameters:
///   - textRanges: The new text ranges for the returned selection.
///
/// - Returns: A new ``NSTextSelection`` with the updated ranges.
- (NSTextSelection *)textSelectionWithTextRanges:(NSArray<NSTextRange *> *)textRanges;

@end

NS_HEADER_AUDIT_END(nullability, sendability)

#else
#import <UIFoundation/NSTextSelection.h>
#endif
