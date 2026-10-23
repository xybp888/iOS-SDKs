#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIFoundation/NSTextLayoutFragment.h>)
//
//  NSTextLayoutFragment.h
//  Text Kit
//
//  Copyright (c) 2017-2025, Apple Inc. All rights reserved.
//

#import <Foundation/NSArray.h>
#import <CoreGraphics/CoreGraphics.h>
#import <UIKit/NSTextViewportRenderingSurface.h>

@class NSTextLayoutManager;
@class NSTextElement;
@class NSTextRange;
@class NSTextParagraph;
@class NSTextLineFragment;
@class NSOperationQueue;
@class NSTextAttachmentViewProvider;
@protocol NSTextLocation;

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

/// A class that represents the layout fragment typically corresponding to a rendering surface, such as a layer or view subclass.

/// Values that describe options for enumerating text layout fragments.
typedef NS_OPTIONS(NSUInteger, NSTextLayoutFragmentEnumerationOptions) {
  /// The value that represents no selected enumeration options.
  NSTextLayoutFragmentEnumerationOptionsNone = 0,
  /// Enumerates in reverse from the layout fragment before the one containing this location.
  NSTextLayoutFragmentEnumerationOptionsReverse = (1 << 0),
  /// When enumerating, tells the layout fragments to estimate their size.
  NSTextLayoutFragmentEnumerationOptionsEstimatesSize = (1 << 1),
  /// When enumerating, tells the layout fragments to lay out their contents.
  NSTextLayoutFragmentEnumerationOptionsEnsuresLayout = (1 << 2),
  /// Synthesizes the extra line fragment when necessary.
  NSTextLayoutFragmentEnumerationOptionsEnsuresExtraLineFragment = (1 << 3),
} API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0), visionos(1.0)) API_UNAVAILABLE(watchos);

/// Values that describe the possible layout states of a text layout fragment.
typedef NS_ENUM(NSUInteger, NSTextLayoutFragmentState) {
  /// No layout information is available.
  NSTextLayoutFragmentStateNone = 0,
  /// The text layout manager hasn't performed a full layout yet for the region covered by this layout fragment and is returning estimated bounds.
  NSTextLayoutFragmentStateEstimatedUsageBounds = 1,
  /// The layout fragment measurements are available without text line fragments.
  NSTextLayoutFragmentStateCalculatedUsageBounds = 2,
  /// Measurements for the text line fragments and layout fragment are available.
  NSTextLayoutFragmentStateLayoutAvailable = 3
} API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0), visionos(1.0)) API_UNAVAILABLE(watchos);

API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0), visionos(1.0)) API_UNAVAILABLE(watchos)
@interface NSTextLayoutFragment : NSObject <NSSecureCoding, NSTextViewportRenderingSurfaceKey>
#pragma mark Initialization
/// Creates a new layout fragment using the provided text element and range.
///
/// - Parameters:
///   - textElement: The text element for this layout fragment.
///   - rangeInElement: The range inside the text element, or `nil` for the entire element.
- (instancetype)initWithTextElement:(NSTextElement *)textElement range:(nullable NSTextRange *)rangeInElement NS_DESIGNATED_INITIALIZER;
/// Creates a new layout fragment with the coder you provide.
///
/// - Parameters:
///   - coder: A coder that conforms to <doc://com.apple.documentation/documentation/foundation/nscoder>.
- (nullable instancetype)initWithCoder:(NSCoder *)coder NS_DESIGNATED_INITIALIZER;

- (instancetype)init NS_UNAVAILABLE;

#pragma mark Properties
/// The text layout manager for this text layout fragment.
@property (nullable, weak, readonly) NSTextLayoutManager *textLayoutManager;

#pragma mark Contents
/// The parent text element.
@property (weak, readonly) NSTextElement *textElement;

/// The range inside the text element relative to the document origin.
@property (strong, readonly) NSTextRange *rangeInElement;

#pragma mark Layout
/// An array of text line fragments.
///
/// Valid when ``state`` is `NSTextLayoutFragmentStateLayoutAvailable`.
/// KVO-compliant.
@property (copy, readonly) NSArray<NSTextLineFragment *> *textLineFragments;

/// Returns the text line fragment for the vertical offset you provide, or the closest text line fragment beyond the vertical offset.
///
/// Set `requiresExactMatch` to `true` to find the text line fragment that
/// contains the vertical offset, or set `requiresExactMatch` to `false` to find
/// the closest text line fragment matching or beyond the vertical offset.
/// Returns `nil` if there isn't a match.
///
/// - Parameters:
///   - verticalOffset: The vertical offset to search for.
///   - requiresExactMatch: When `false`, returns the closest line fragment beyond `verticalOffset` if no line fragment contains it.
///
/// - Returns: The matching line fragment, or `nil`.
- (nullable NSTextLineFragment *)textLineFragmentForVerticalOffset:(CGFloat)verticalOffset requiresExactMatch:(BOOL)requiresExactMatch API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0), visionos(1.0)) API_UNAVAILABLE(watchos);

/// Returns a text line fragment from a specific text location in the document.
///
/// Set `isUpstreamAffinity` to `true` to find a text fragment by its element
/// range end location, such as when you enumerate over line fragments in
/// reverse order. Set `isUpstreamAffinity` to `false` to find a text fragment that
/// contains `textLocation`.
///
/// - Parameters:
///   - textLocation: The text location to search for.
///   - isUpstreamAffinity: When the location is at the end of a text line fragment (and the beginning of another), `true` chooses the one ending with the location; `false` chooses the following.
///
/// - Returns: The matching line fragment, or `nil`.
- (nullable NSTextLineFragment *)textLineFragmentForTextLocation:(id <NSTextLocation>)textLocation isUpstreamAffinity:(BOOL)isUpstreamAffinity API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0), visionos(1.0)) API_UNAVAILABLE(watchos);

/// The queue on which the framework dispatches layout operations.
///
/// When non-nil, the layout operation is dispatched to the queue asynchronously.
@property (nullable, strong) NSOperationQueue *layoutQueue;

/// The layout information state.
///
/// KVO-compliant.
@property (readonly) NSTextLayoutFragmentState state;

/// Invalidates any layout information associated with the text layout fragment.
- (void)invalidateLayout;

#pragma mark Layout information
/// The rectangle the framework uses for tiling the layout fragment inside the target layout coordinate system.
///
/// Typically in an ``NSTextContainer`` coordinate system.
@property (readonly) CGRect layoutFragmentFrame;

/// The bounds defining the area required for rendering the contents.
///
/// The coordinate system is relative to ``layoutFragmentFrame``. The coordinate
/// system is vertically flipped, meaning origin (`{0,0}`) is at the upper-left
/// corner. The size should be larger than `layoutFragmentFrame.size`. The origin
/// could be in the negative coordinate since the rendering could be stretched
/// out of `layoutFragmentFrame`. Only valid when ``state`` is greater than
/// `NSTextLayoutFragmentStateEstimatedUsageBounds`.
@property (readonly) CGRect renderingSurfaceBounds;

#pragma mark Custom spacing

/// The amount of margin space reserved during paragraph layout between the leading edge of the text layout fragment and the start of the lines in the paragraph.
///
/// The leading edge is according to the primary writing direction of the paragraph.
@property (readonly) CGFloat leadingPadding;

/// The amount of margin space reserved during paragraph layout between the end of the lines in the paragraph and the trailing edge of the text layout fragment.
///
/// The trailing edge is according to the primary writing direction of the paragraph.
@property (readonly) CGFloat trailingPadding;

/// The amount of space reserved during paragraph layout between the top of the text layout fragment and the top of the first line in the paragraph.
@property (readonly) CGFloat topMargin;

/// The amount of space reserved during paragraph layout between the bottom of the last line in the paragraph and the bottom of the text layout fragment.
@property (readonly) CGFloat bottomMargin;

#pragma mark Rendering
/// Renders the visual representation of this element in the specified graphics context.
///
/// - Parameters:
///   - point: The origin as a <doc://com.apple.documentation/documentation/corefoundation/cgpoint>.
///   - context: The graphics context to draw into.
- (void)drawAtPoint:(CGPoint)point inContext:(CGContextRef)context;

#pragma mark Text attachments
/// The attachment view providers associated with the text layout fragment.
///
/// The property contents are only valid with
/// `NSTextLayoutFragmentStateLayoutAvailable`.
@property (copy, readonly) NSArray<NSTextAttachmentViewProvider *> *textAttachmentViewProviders;

/// Returns the frame in the text layout fragment coordinate system for the attachment at the location you specify.
///
/// Returns
/// <doc://com.apple.documentation/documentation/coregraphics/cgrectzero> if
/// `location` is not within any attachment or the state is not
/// `NSTextLayoutFragmentStateLayoutAvailable`.
///
/// - Parameters:
///   - location: The document location of the attachment.
///
/// - Returns: The frame of the attachment, or `CGRectZero`.
- (CGRect)frameForTextAttachmentAtLocation:(id <NSTextLocation>)location;
@end
NS_HEADER_AUDIT_END(nullability, sendability)
#else
#import <UIFoundation/NSTextLayoutFragment.h>
#endif
