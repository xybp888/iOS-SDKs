#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIFoundation/NSTextSelectionNavigation.h>)
//
//  NSTextSelectionNavigation.h
//  Text Kit
//
//  Copyright (c) 2019-2025, Apple Inc. All rights reserved.
//

#import <Foundation/NSObject.h>
#import <CoreGraphics/CGGeometry.h>
#import <UIKit/NSTextSelection.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

@class NSTextSelection;
@class NSTextRange;
@class NSTextLineFragment;
@protocol NSTextLocation;
@protocol NSTextSelectionDataSource;

/// An interface you use to expose methods for obtaining results from actions performed on text selections.
///
/// It returns the essential information necessary for editing, selecting, and
/// navigating operations.

/// Values that describe the direction of a selection.
typedef NS_ENUM(NSInteger, NSTextSelectionNavigationDirection) {
    // Logical directions
    // Works with just character information
    /// The value that represents a logical forward selection based on the flow of text stored in the document.
    NSTextSelectionNavigationDirectionForward,
    /// The value that represents a logical backward selection based on the flow of text stored in the document.
    NSTextSelectionNavigationDirectionBackward,

    // Visual directions
    // Requires layout information if the direction is along the line (i.e. right and left for a horizontal line). Otherwise, it gets resolved to the corresponding logical direction except for NSTextSelectionNavigationDestinationCharacter
    /// The value that represents a selection in the right direction along the current line.
    NSTextSelectionNavigationDirectionRight,
    /// The value that represents a selection in the left direction along the current line.
    NSTextSelectionNavigationDirectionLeft,
    /// The value that represents a selection in the up direction, above the current line.
    NSTextSelectionNavigationDirectionUp,
    /// The value that represents a selection in the down direction, below the current line.
    NSTextSelectionNavigationDirectionDown
} API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0), visionos(1.0)) API_UNAVAILABLE(watchos);

/// Values that affect how the framework handles navigation across different textual boundaries during a selection.
typedef NS_ENUM(NSInteger, NSTextSelectionNavigationDestination) {
    /// The selection moves to the next extended grapheme cluster boundary.
    ///
    /// When the movement direction isn't along the line (for example up and
    /// down for a horizontal line), it moves to the adjacent line using the
    /// anchor point instead of resolving to the logical direction. This could
    /// result in a location inside a cluster depending on the specific
    /// characteristics of a given script. For example, certain Indic scripts
    /// combine characters in specific ways depending on usage and position to
    /// form composite characters. The framework returns a location consistent
    /// with the rules of the script and the direction of movement.
    NSTextSelectionNavigationDestinationCharacter,
    /// The selection moves to the next word boundary, ignoring punctuation, whitespace, and format characters preceding the next word.
    NSTextSelectionNavigationDestinationWord,
    /// The selection moves to the next line boundary.
    ///
    /// The boundary of a line can be logical, based on the line separator
    /// characters, as well as visual using soft line wrapping.
    NSTextSelectionNavigationDestinationLine,
    /// The selection moves to the next sentence boundary, ignoring punctuation, whitespace, and format characters preceding the next sentence.
    NSTextSelectionNavigationDestinationSentence,
    /// The selection moves to the next paragraph boundary, ignoring the end-of-line elastic characters and paragraph separators.
    NSTextSelectionNavigationDestinationParagraph,
    /// The selection moves to the next container or page boundary, ignoring the end-of-line elastic characters and container/page separators.
    NSTextSelectionNavigationDestinationContainer,
    /// The selection moves to the document boundary.
    NSTextSelectionNavigationDestinationDocument,
} API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0), visionos(1.0)) API_UNAVAILABLE(watchos);

/// Values that describe how the framework handles different kinds of selection modifiers.
typedef NS_OPTIONS(NSUInteger, NSTextSelectionNavigationModifier) {
    /// The value that indicates the framework extends the selection by not moving the initial location while in a drag selection.
    NSTextSelectionNavigationModifierExtend = (1 << 0),
    /// The value that indicates the framework extends the selection visually inside the rectangular area defined by the anchor and drag positions.
    NSTextSelectionNavigationModifierVisual = (1 << 1),
    /// The value that indicates the framework extends the selection visually inside the rectangular area defined by the anchor and dragged positions.
    ///
    /// This produces an ``NSTextSelection`` per line.
    NSTextSelectionNavigationModifierMultiple = (1 << 2),
} API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0), visionos(1.0)) API_UNAVAILABLE(watchos);

/// Values that describe writing direction for selection navigation.
typedef NS_ENUM(NSInteger, NSTextSelectionNavigationWritingDirection) {
    /// Left-to-right writing direction.
    NSTextSelectionNavigationWritingDirectionLeftToRight   = 0,
    /// Right-to-left writing direction.
    NSTextSelectionNavigationWritingDirectionRightToLeft   = 1
} API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0), visionos(1.0)) API_UNAVAILABLE(watchos);

/// Values that describe text layout orientation for selection navigation.
typedef NS_ENUM(NSInteger, NSTextSelectionNavigationLayoutOrientation) {
    /// Lines render horizontally and grow from top to bottom.
    NSTextSelectionNavigationLayoutOrientationHorizontal = 0,
    /// Lines render vertically and grow from right to left.
    NSTextSelectionNavigationLayoutOrientationVertical = 1,
} API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0), visionos(1.0)) API_UNAVAILABLE(watchos);

API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0), visionos(1.0)) API_UNAVAILABLE(watchos)
@interface NSTextSelectionNavigation : NSObject
#pragma mark Initialization
/// Creates a new text selection navigation with the data source you provide.
///
/// - Parameters:
///   - dataSource: The data source providing layout and document content information.
- (instancetype)initWithDataSource:(id <NSTextSelectionDataSource>)dataSource NS_DESIGNATED_INITIALIZER;

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

#pragma mark Properties
/// The data source object providing the layout and document content information.
@property (readonly, weak) id <NSTextSelectionDataSource> textSelectionDataSource;

/// A Boolean value that indicates whether the object could produce selections with multiple disjoint ranges.
@property BOOL allowsNonContiguousRanges;

/// A Boolean value that indicates whether the coordinate system rotates for navigation methods based on the text container layout orientation.
///
/// The default value is `false`.
@property BOOL rotatesCoordinateSystemForLayoutOrientation;

#pragma mark Layout Information Cache
/// Flushes cached layout information.
///
/// Should be called whenever the document contents change.
- (void)flushLayoutCache;

#pragma mark Selection & Cursor Navigation
/// Returns a new selection that results from applying the navigation operations you specify to the text selection you provide.
///
/// Returns `nil` when the requested operation does not produce any logically
/// valid result.
///
/// - Parameters:
///   - textSelection: The starting text selection.
///   - direction: The navigation direction.
///   - destination: The navigation destination granularity.
///   - extending: Whether to extend the selection.
///   - confined: If `true`, confines movement to the text element the selection already lies within.
///
/// - Returns: The resulting text selection, or `nil` if the operation is invalid.
- (nullable NSTextSelection *)destinationSelectionForTextSelection:(NSTextSelection *)textSelection direction:(NSTextSelectionNavigationDirection)direction destination:(NSTextSelectionNavigationDestination)destination extending:(BOOL)extending confined:(BOOL)confined;

/// Returns an array of text selections produced with a tap or mouse down at the specified point.
///
/// - Parameters:
///   - point: The interaction point in the container coordinate system.
///   - containerLocation: The location identifying which text container the point belongs to.
///   - anchors: The last text selection state if `selecting` is `true` or the extend modifier is active.
///   - modifiers: The active selection modifiers.
///   - selecting: `true` if currently in a text selection dragging session.
///   - bounds: The view area in the container coordinate system that can interact with events (typically the view's visible area).
///
/// - Returns: An array of text selections for the interaction.
- (NSArray<NSTextSelection *> *)textSelectionsInteractingAtPoint:(CGPoint)point inContainerAtLocation:(id <NSTextLocation>)containerLocation anchors:(NSArray <NSTextSelection *> *)anchors modifiers:(NSTextSelectionNavigationModifier)modifiers selecting:(BOOL)selecting bounds:(CGRect)bounds;

/// Returns a text selection expanded to the nearest boundaries for the specified granularity enclosing the given selection.
///
/// The returned selection will have `granularity` set to `selectionGranularity`.
///
/// - Parameters:
///   - selectionGranularity: The granularity to expand to.
///   - textSelection: The selection to expand.
///
/// - Returns: The expanded text selection.
- (NSTextSelection *)textSelectionForSelectionGranularity:(NSTextSelectionGranularity)selectionGranularity enclosingTextSelection:(NSTextSelection *)textSelection;

/// Returns a text selection expanded to the nearest boundaries for the specified granularity that contains the given point.
///
/// The returned selection will have `granularity` set to `selectionGranularity`.
///
/// - Parameters:
///   - selectionGranularity: The granularity to expand to.
///   - point: The point in the container coordinate system.
///   - location: The location identifying the text container.
///
/// - Returns: The expanded text selection, or `nil`.
- (nullable NSTextSelection *)textSelectionForSelectionGranularity:(NSTextSelectionGranularity)selectionGranularity enclosingPoint:(CGPoint)point inContainerAtLocation:(id <NSTextLocation>)location;

#pragma mark Editing
/// Returns the resolved location for inserting the next input when the selection is at a bidirectional boundary.
///
/// Returns `nil` if `textSelection` has `isLogical == YES` or
/// `secondarySelectionLocation == nil`.
///
/// - Parameters:
///   - textSelection: The current text selection.
///   - writingDirection: The active input writing direction.
///
/// - Returns: The resolved insertion location, or `nil`.
- (nullable id <NSTextLocation>)resolvedInsertionLocationForTextSelection:(NSTextSelection *)textSelection writingDirection:(NSTextSelectionNavigationWritingDirection)writingDirection;

/// Returns the ranges that should be deleted based on the text selection and movement arguments.
///
/// The selection after deletion should contain a 0-length range starting at the
/// location of the first range returned. `destination` is ignored when
/// `textSelection` has a non-empty selection. `allowsDecomposition` only applies
/// to `NSTextSelectionNavigationDirectionBackward` and
/// `NSTextSelectionNavigationDestinationCharacter` with a 0-length selection.
///
/// - Parameters:
///   - textSelection: The current text selection.
///   - direction: The deletion direction.
///   - destination: The deletion destination granularity.
///   - allowsDecomposition: Whether to allow character decomposition during backward deletion.
///
/// - Returns: An array of ranges to delete.
- (NSArray<NSTextRange *> *)deletionRangesForTextSelection:(NSTextSelection *)textSelection direction:(NSTextSelectionNavigationDirection)direction destination:(NSTextSelectionNavigationDestination)destination allowsDecomposition:(BOOL)allowsDecomposition;
@end

/// The protocol that provides layout and document content information for text selection navigation.
API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0), visionos(1.0)) API_UNAVAILABLE(watchos)
@protocol NSTextSelectionDataSource <NSObject>
@required
/// The starting and ending locations for the document.
@property (strong, readonly) NSTextRange *documentRange;

/// Enumerates the textual segment boundaries starting at the specified location.
///
/// The segmentation logic should be based on the natural language semantics and
/// rules such as Unicode Text Segmentation UAX 29. It is allowed to have custom
/// text segmentation behavior for specialized document contents (i.e. text
/// editors with structured document contents such as a programming language).
/// `NSStringEnumerationByLines` should be aware of the visual line boundaries
/// based on soft line wrapping. For forward enumeration, location may be at the
/// trailing edge of a visual line; the implementation must enumerate into
/// subsequent content rather than only within the current line fragment.
///
/// - Parameters:
///   - location: The starting location.
///   - options: One or more <doc://com.apple.documentation/documentation/foundation/nsstring/enumerationoptions> values controlling segmentation type and direction.
///   - block: A block called for each substring segment.
- (void)enumerateSubstringsFromLocation:(id <NSTextLocation>)location options:(NSStringEnumerationOptions)options usingBlock:(void (NS_NOESCAPE ^)(NSString * _Nullable substring, NSTextRange *substringRange, NSTextRange * _Nullable enclosingRange, BOOL *stop))block;

/// Returns a text range corresponding to the specified granularity enclosing the given location.
///
/// Returns `nil` when `documentRange.isEmpty` is `true`. When location falls at a
/// visual line boundary, results for `NSTextSelectionGranularityLine` should be
/// consistent with ``lineFragmentRangeForPoint:inContainerAtLocation:`` for the
/// same position.
///
/// - Parameters:
///   - selectionGranularity: The granularity to expand to.
///   - location: The document location.
///
/// - Returns: The enclosing range, or `nil`.
- (nullable NSTextRange *)textRangeForSelectionGranularity:(NSTextSelectionGranularity)selectionGranularity enclosingLocation:(id <NSTextLocation>)location;

/// Returns a new location from the specified location with the given offset.
///
/// The offset value could be positive or negative indicating the logical
/// direction. Could return `nil` when the inputs don't produce any legal
/// location (i.e. out of bounds index).
///
/// - Parameters:
///   - location: The base location.
///   - offset: The offset from the base location.
///
/// - Returns: A new location, or `nil` if out of bounds.
- (nullable id <NSTextLocation>)locationFromLocation:(id <NSTextLocation>)location withOffset:(NSInteger)offset;

/// Returns the offset between the two specified locations.
///
/// The return value could be positive or negative. Could return `NSNotFound`
/// when the offset cannot be represented in an integer value (i.e. locations
/// are not in the same document). If either location is invalid or
/// out-of-document, return 0 to avoid arithmetic overflow.
///
/// - Parameters:
///   - from: The starting location.
///   - to: The ending location.
///
/// - Returns: The signed offset, or <doc://com.apple.documentation/documentation/foundation/nsnotfound> if the locations are not in the same document.
- (NSInteger)offsetFromLocation:(id <NSTextLocation>)from toLocation:(id <NSTextLocation>)to;

/// Returns the base writing direction at the specified location.
///
/// It is recommended to return the resolved base direction, either
/// `NSTextSelectionNavigationWritingDirectionLeftToRight` or
/// `NSTextSelectionNavigationWritingDirectionRightToLeft`.
///
/// - Parameters:
///   - location: The document location.
///
/// - Returns: An ``NSTextSelectionNavigationWritingDirection``, ideally the resolved base direction (either `NSTextSelectionNavigationWritingDirectionLeftToRight` or `NSTextSelectionNavigationWritingDirectionRightToLeft`).
- (NSTextSelectionNavigationWritingDirection)baseWritingDirectionAtLocation:(id <NSTextLocation>)location;

// Layout
/// Enumerates all the caret offsets from left to right in visual order.
///
/// `caretOffset` is the absolute horizontal position measured from the left edge
/// of the text container; implementors must account for the line fragment's
/// origin within the container and the typographic line's position within the
/// fragment (non-zero for center- or right-aligned text). When `leadingEdge` is
/// `true`, it indicates `caretOffset` is at the edge logically preceding the
/// character. For LTR characters, it is on the left, and on the right for RTL
/// characters. The block must be called twice per character — once for the
/// leading edge and once for the trailing edge — except for empty line
/// fragments (e.g. empty paragraphs) where a single leading-edge call is
/// sufficient. The location objects passed to the block must be positionally
/// equivalent (via `isEqual:`) to locations returned by other data source
/// methods for the same document positions.
///
/// - Parameters:
///   - location: A location identifying the line fragment to enumerate.
///   - block: A block called for each caret offset.
- (void)enumerateCaretOffsetsInLineFragmentAtLocation:(id<NSTextLocation>)location usingBlock:(void (NS_NOESCAPE ^)(CGFloat caretOffset, id <NSTextLocation> location, BOOL leadingEdge, BOOL * stop))block;

/// Returns the range of the line fragment whose visual bounds contain the specified point.
///
/// This is a containment test: for points at or past the trailing edge of a
/// line's last glyph, return the current line fragment's range, not the next.
/// For multi-container layouts, `location` identifies which text container the
/// point belongs to.
///
/// - Parameters:
///   - point: The point to test in the container coordinate system.
///   - location: The location identifying the text container.
///
/// - Returns: The line fragment range containing the point, or `nil`.
- (nullable NSTextRange *)lineFragmentRangeForPoint:(CGPoint)point inContainerAtLocation:(id <NSTextLocation>)location;

@optional
/// Enumerates the text container or page boundaries.
///
/// This optional method should be implemented when the text selection data
/// provider supports container/page boundary layout functionality.
///
/// - Parameters:
///   - location: The starting location.
///   - reverse: Whether to enumerate in reverse.
///   - block: A block called for each boundary location.
- (void)enumerateContainerBoundariesFromLocation:(id <NSTextLocation>)location reverse:(BOOL)reverse usingBlock:(void (NS_NOESCAPE ^)(id <NSTextLocation> boundaryLocation, BOOL *stop))block;

/// Returns the text layout orientation at the specified location.
///
/// If not implemented, ``NSTextSelectionNavigation`` assumes
/// `NSTextSelectionNavigationLayoutOrientationHorizontal`.
///
/// - Parameters:
///   - location: The document location.
///
/// - Returns: The layout orientation at the location.
- (NSTextSelectionNavigationLayoutOrientation)textLayoutOrientationAtLocation:(id <NSTextLocation>)location;

/// Converts an interaction point from display space into the text container's coordinate system.
///
/// `NSTextSelectionNavigation` calls this method before hit-testing to allow the data source to undo any display transform (rotation, flip, path layout, etc.) applied to the text.
///
/// - Parameters:
///   - point: The interaction point in display/view-space coordinates.
///   - containerLocation: The location identifying the text container the interaction occurred in.
/// - Returns: The point mapped into the text container's coordinate system. Return `point` unchanged when no transform is active.
- (CGPoint)convertInteractionPoint:(CGPoint)point toContainerAtLocation:(id<NSTextLocation>)containerLocation API_AVAILABLE(macos(27.0), ios(27.0), tvos(27.0), visionos(27.0)) API_UNAVAILABLE(watchos);
@end
NS_HEADER_AUDIT_END(nullability, sendability)
#else
#import <UIFoundation/NSTextSelectionNavigation.h>
#endif
