#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIFoundation/NSTextLayoutManager.h>)
//
//  NSTextLayoutManager.h
//  Text Kit
//
//  Copyright (c) 2017-2025, Apple Inc. All rights reserved.
//


#import <Foundation/NSAttributedString.h>
#import <CoreGraphics/CGGeometry.h>
#import <UIKit/UIKitDefines.h>
#import <UIKit/NSTextLayoutFragment.h>

@class NSTextRange;
@class NSTextContentManager;
@class NSTextElement;
@class NSTextContainer;
@class NSTextSelection;
@class NSTextSelectionNavigation;
@class NSTextViewportLayoutController;
@class NSTextAttachment;
@class NSTextAttachmentViewProvider;
@protocol NSTextLocation;
@protocol NSTextLayoutManagerDelegate;
@protocol NSTextSelectionDataSource;

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

/// Values that describe the rendering of selection boundaries.
typedef NS_ENUM(NSInteger, NSTextLayoutManagerSegmentType) {
    /// The standard segment, matching the typographic bounds of the range.
    NSTextLayoutManagerSegmentTypeStandard = 0,
    /// The segment behavior suitable for selection rendering.
    ///
    /// This segment type extends the last segment in a line fragment to the trailing edge if continuing to the next line.
    NSTextLayoutManagerSegmentTypeSelection = 1,
    /// The segment behavior suitable for highlighting.
    NSTextLayoutManagerSegmentTypeHighlight = 2,
} API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0), visionos(1.0)) API_UNAVAILABLE(watchos);

/// Values that describe where and how the framework extends segments of a selection.
typedef NS_OPTIONS(NSUInteger, NSTextLayoutManagerSegmentOptions) {
    /// The value that represents the empty options set.
    NSTextLayoutManagerSegmentOptionsNone = 0,
    /// Causes the framework to enumerate text segment rectangles, but avoids preparing a range object.
    NSTextLayoutManagerSegmentOptionsRangeNotRequired = (1 << 0),
    /// Causes the framework to enumerate segments only in the first and last line fragments.
    NSTextLayoutManagerSegmentOptionsMiddleFragmentsExcluded = (1 << 1),
    /// Causes the framework to extend the segment to the head edge.
    NSTextLayoutManagerSegmentOptionsHeadSegmentExtended = (1 << 2),
    /// Causes the framework to extend the segment to the tail edge.
    NSTextLayoutManagerSegmentOptionsTailSegmentExtended = (1 << 3),
    /// Causes the framework to place the segment based on the upstream affinity for an empty range.
    NSTextLayoutManagerSegmentOptionsUpstreamAffinity = (1 << 4),
} API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0), visionos(1.0)) API_UNAVAILABLE(watchos);

/// The primary class that you use to manage text layout and presentation for custom text displays.
///
/// `NSTextLayoutManager` is the centerpiece of the TextKit object network
/// maintaining the layout geometry through an array of ``NSTextContainer``
/// objects. It lays out results using ``NSTextLayoutFragment`` and
/// ``NSTextElement`` objects vended from a ``NSTextContentManager`` that
/// participates in the content layout process.
API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0), visionos(1.0)) API_UNAVAILABLE(watchos)
@interface NSTextLayoutManager : NSObject <NSSecureCoding, NSTextSelectionDataSource>
#pragma mark Initialization
/// Creates a new text layout manager.
- (instancetype)init NS_DESIGNATED_INITIALIZER;
/// Creates a new text layout manager with the coder you provide.
///
/// - Parameters:
///   - coder: A coder that conforms to <doc://com.apple.documentation/documentation/foundation/nscoder>.
- (nullable instancetype)initWithCoder:(NSCoder *)coder NS_DESIGNATED_INITIALIZER;

#pragma mark Basic properties
/// The delegate for the text layout manager object.
@property (nullable, weak) id <NSTextLayoutManagerDelegate> delegate;

/// A Boolean value that controls whether the framework uses the leading information specified by the font when laying out text.
///
/// If set to `true`, uses the leading as specified by the font. However, this
/// isn't appropriate for most UI text. The default value is `true`.
@property BOOL usesFontLeading;

/// A Boolean value that controls internal security analysis for malicious inputs and activates defensive behaviors.
///
/// By enabling this functionality, it's possible certain text such as a very
/// long paragraph might result in unexpected layout. The default value is `false`.
@property BOOL limitsLayoutForSuspiciousContents;

/// A Boolean value that controls whether the text layout manager attempts to hyphenate when wrapping lines.
///
/// May be overridden on a per-paragraph basis by the `NSParagraphStyle`'s
/// `usesDefaultHyphenation`. The receiver makes the best effort to decide the
/// exact logic including the hyphenation factor based on the context. The
/// default value is `false`. Can be overridden by the preference key
/// `"NSUsesDefaultHyphenation"`.
@property BOOL usesHyphenation;

/// Specifies the behavior for resolving ``NSTextAlignment/natural`` to the visual alignment.
///
/// When set to `true`, the resolved visual alignment is determined by the resolved base writing direction; otherwise, it is using the user’s preferred language.
/// The default value is `true`.
@property BOOL resolvesNaturalAlignmentWithBaseWritingDirection API_AVAILABLE(macos(26.0), ios(26.0), tvos(26.0), visionos(26.0)) API_UNAVAILABLE(watchos);

#pragma mark NSTextContentManager interface
/// Returns the text content manager associated with this text layout manager.
@property (nullable, weak, readonly) NSTextContentManager *textContentManager;

/// Replaces the current text content manager with a new one you provide.
///
/// This method should be used in order to replace an ``NSTextContentManager``
/// with a new one, leaving all related objects intact. This method makes sure
/// the ``NSTextLayoutManager`` doesn't get deallocated while migrating to the
/// new manager.
///
/// - Parameters:
///   - textContentManager: The new content manager.
- (void)replaceTextContentManager:(NSTextContentManager *)textContentManager;

#pragma mark NSTextContainer interface
/// The text container object that provides geometric information for the layout destination.
///
/// If `isSimpleRectangularTextContainer` is `false`, ``NSTextLayoutManager`` always
/// fills from the top instead of allowing non-contiguous layout support.
@property (nullable, strong, readwrite) NSTextContainer *textContainer;

/// Returns the usage bounds for the text container.
///
/// KVO-compliant. Views can observe this property in order to trigger a resize
/// operation. For example, `UIView`/`NSView` should call
/// `setNeedsUpdateConstraints()` when the usage bounds changes.
@property (readonly) CGRect usageBoundsForTextContainer;

#pragma mark Layout
/// Returns the text viewport layout controller associated with the text layout manager's text container.
@property (readonly, strong) NSTextViewportLayoutController *textViewportLayoutController;

/// The queue that the framework dispatches layout operations on.
///
/// If non-nil, it performs layout in the specified queue until
/// `estimatedUsageBounds` is `false`.
@property (nullable, strong) NSOperationQueue *layoutQueue;

/// Performs the layout for the specified text range.
///
/// - Parameters:
///   - range: The text range to lay out.
- (void)ensureLayoutForRange:(NSTextRange *)range;

/// Performs the layout for filling bounds inside the last text container.
///
/// - Parameters:
///   - bounds: A <doc://com.apple.documentation/documentation/corefoundation/cgrect> that describes the layout bounds.
- (void)ensureLayoutForBounds:(CGRect)bounds;

/// Invalidates layout information for the specified text range.
///
/// - Parameters:
///   - range: The text range to invalidate.
- (void)invalidateLayoutForRange:(NSTextRange *)range;

/// Returns the text layout fragment at the position you specify in the text container.
///
/// - Parameters:
///   - position: A <doc://com.apple.documentation/documentation/corefoundation/cgpoint> in the text container coordinate system.
///
/// - Returns: The layout fragment containing the position, or `nil`.
- (nullable NSTextLayoutFragment *)textLayoutFragmentForPosition:(CGPoint)position;

/// Returns the text layout fragment from the document at the specified location.
///
/// - Parameters:
///   - location: A document location.
///
/// - Returns: The layout fragment containing the location, or `nil`.
- (nullable NSTextLayoutFragment *)textLayoutFragmentForLocation:(id <NSTextLocation>)location;

/// Enumerates the text layout fragments starting at the specified location.
///
/// If `location` is `nil`, it assumes `self.textContentManager.documentRange.location`;
/// uses `documentRange.endLocation` for reverse enumeration. When enumerating
/// backward, it starts with the fragment preceding the one containing
/// `location`. If enumerated at least one fragment, it returns the edge of the
/// enumerated range. Note that the enumerated range might not match the range of
/// the last element returned. Returning `false` from block breaks out of the
/// enumeration.
///
/// - Parameters:
///   - location: The starting location, or `nil` for the document edge.
///   - options: Enumeration options controlling direction and behavior.
///   - block: A block called for each layout fragment. Return `false` to stop.
///
/// - Returns: The edge of the enumerated range, or `nil`.
- (nullable id <NSTextLocation>)enumerateTextLayoutFragmentsFromLocation:(nullable id <NSTextLocation>)location options:(NSTextLayoutFragmentEnumerationOptions)options usingBlock:(BOOL (NS_NOESCAPE ^)(NSTextLayoutFragment *layoutFragment))block;

#pragma mark Text Selection
/// An array of text selections associated by the text layout manager.
///
/// Each ``NSTextSelection`` represents an insertion point. The selection state is
/// shared among all view ports connected to the text layout manager via text
/// containers.
@property (strong) NSArray<NSTextSelection *> *textSelections;

/// Returns a text selection navigation configured to have the text layout manager as its data source.
@property (strong) NSTextSelectionNavigation *textSelectionNavigation;

#pragma mark Rendering Attributes
/// Enumerates the rendering attributes from the specified location.
///
/// It enumerates only ranges with rendering attributes specified. Returning `false`
/// from block breaks out of the enumeration.
///
/// Rendering attributes override the document text attributes stored in
/// ``NSTextParagraph`` objects supplied by ``NSTextContentManager``.
/// ``NSTextLayoutFragment`` associated with a text paragraph applies the
/// overriding attributes before executing layout. Specifying
/// <doc://com.apple.documentation/documentation/foundation/nsnull> to an
/// attribute indicates removing it from the document attributes. Rendering
/// attributes are invalidated upon re-layout of the text layout fragment that
/// they belong to.
///
/// - Parameters:
///   - location: The starting location.
///   - reverse: Whether to enumerate in reverse.
///   - block: A block called for each range with rendering attributes. Return `false` to stop.
- (void)enumerateRenderingAttributesFromLocation:(id <NSTextLocation> )location reverse:(BOOL)reverse usingBlock:(BOOL (NS_NOESCAPE ^)(NSTextLayoutManager *textLayoutManager, NSDictionary<NSAttributedStringKey, id> *attributes, NSTextRange *textRange))block;

/// Sets the rendering attributes for the range you specify.
///
/// - Parameters:
///   - renderingAttributes: The attributes to set.
///   - textRange: The range to apply attributes to.
- (void)setRenderingAttributes:(NSDictionary<NSAttributedStringKey, id> *)renderingAttributes forTextRange:(NSTextRange *)textRange;

/// Adds a rendering attribute for the range you specify.
///
/// Passing `nil` for value indicates overriding the specified attribute by
/// removing it from the final attributes passed to the layout and rendering
/// engine. This is a convenience over ``setRenderingAttributes:forTextRange:``.
///
/// - Parameters:
///   - renderingAttribute: The <doc://com.apple.documentation/documentation/foundation/nsattributedstring/key> attribute to add.
///   - value: The attribute value, or `nil` to remove.
///   - textRange: The range to apply the attribute to.
- (void)addRenderingAttribute:(NSAttributedStringKey)renderingAttribute value:(nullable id)value forTextRange:(NSTextRange *)textRange;

/// Removes the rendering attribute from the specified text range.
///
/// This is a convenience over ``setRenderingAttributes:forTextRange:``.
///
/// - Parameters:
///   - renderingAttribute: The <doc://com.apple.documentation/documentation/foundation/nsattributedstring/key> attribute to remove.
///   - textRange: The range to remove the attribute from.
- (void)removeRenderingAttribute:(NSAttributedStringKey)renderingAttribute forTextRange:(NSTextRange *)textRange;

/// Invalidates the rendering attributes in the specified text range.
///
/// Enumerating rendering attributes will skip the invalidated range.
///
/// - Parameters:
///   - textRange: The range to invalidate.
- (void)invalidateRenderingAttributesForTextRange:(NSTextRange *)textRange;

/// A callback block that the framework invokes whenever the text layout manager needs to validate the rendering attributes for the range.
///
/// The validator should use ``setRenderingAttributes:forTextRange:`` to fill the
/// rendering attributes appropriate for the range inside `textLayoutFragment`.
@property (nullable, copy) void (^renderingAttributesValidator)(NSTextLayoutManager *textLayoutManager, NSTextLayoutFragment *textLayoutFragment);

#pragma mark Link Attributes
/// Returns the default set of attributes for rendering `NSLinkAttributeName`.
///
/// The base ``NSTextLayoutManager`` class returns with
/// ``NSUnderlineStyle/single`` for
/// <doc://com.apple.documentation/documentation/foundation/nsattributedstring/key/1524865-underlinestyle>
/// in Swift or ``NSUnderlineStyleAttributeName`` in Objective-C, and the
/// platform link color for
/// <doc://com.apple.documentation/documentation/foundation/nsattributedstring/key/1533563-foregroundcolor>
/// in Swift or ``NSForegroundColorAttributeName`` in Objective-C. The platform
/// color for macOS is `linkColor`. Other platforms use `blueColor`.
@property (class, readonly) NSDictionary<NSAttributedStringKey, id> *linkRenderingAttributes;


/// Returns a dictionary of rendering attributes for rendering a link.
///
/// Just as other rendering attributes, specifying
/// <doc://com.apple.documentation/documentation/foundation/nsnull> removes the
/// attribute from the final attributes used for rendering. It has priority over
/// the general rendering attributes.
///
/// - Parameters:
///   - link: The link object.
///   - location: The document location of the link.
///
/// - Returns: A dictionary of rendering attributes.
- (NSDictionary<NSAttributedStringKey, id> *)renderingAttributesForLink:(id)link atLocation:(id <NSTextLocation>)location;

#pragma mark Text Segments
/// Enumerates text segments of a specific type and in the text range you provide.
///
/// A text segment is both logically and visually contiguous portion of the text
/// content inside a line fragment. It can be defined with a single text range.
/// The segments are enumerated visually from left to right. Returning `false` from
/// block breaks out of the enumeration.
///
/// - Parameters:
///   - textRange: The range to enumerate segments in.
///   - type: The segment type.
///   - options: Options controlling segment behavior.
///   - block: A block called for each segment. Return `false` to stop.
- (void)enumerateTextSegmentsInRange:(NSTextRange *)textRange type:(NSTextLayoutManagerSegmentType)type options:(NSTextLayoutManagerSegmentOptions)options usingBlock:(BOOL (NS_NOESCAPE ^)(NSTextRange * _Nullable textSegmentRange, CGRect textSegmentFrame, CGFloat baselinePosition, NSTextContainer *textContainer))block;

#pragma mark Editing
/// Replaces content at the location you specify with the text elements you provide.
///
/// - Parameters:
///   - range: The range of the content to replace.
///   - textElements: An array of text elements.
- (void)replaceContentsInRange:(NSTextRange *)range withTextElements:(NSArray<NSTextElement *> *)textElements;
/// Replaces content at the location you specify with an attributed string you provide.
///
/// - Parameters:
///   - range: The range of the content to replace.
///   - attributedString: An attributed string to replace the content at `range`.
- (void)replaceContentsInRange:(NSTextRange *)range withAttributedString:(NSAttributedString *)attributedString;
@end

#pragma mark NSTextLayoutManagerDelegate
/// Optional methods that delegates implement to respond to layout changes.
API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0), visionos(1.0)) API_UNAVAILABLE(watchos)
@protocol NSTextLayoutManagerDelegate <NSObject>
@optional
/// Returns a text layout fragment for the specified location in the text element.
///
/// The delegate can provide an ``NSTextLayoutFragment`` specialized for an
/// ``NSTextElement`` subclass targeted for the rendering surface.
///
/// - Parameters:
///   - textLayoutManager: The text layout manager sending the message.
///   - location: The document location.
///   - textElement: The text element containing the location.
///
/// - Returns: A layout fragment for the location, or `nil` to use the default.
- (NSTextLayoutFragment *)textLayoutManager:(NSTextLayoutManager *)textLayoutManager textLayoutFragmentForLocation:(id <NSTextLocation>)location inTextElement:(NSTextElement *)textElement;

/// Invoked while determining the soft line break point.
///
/// When `hyphenating` is `false`, ``NSTextLayoutManager`` tries to find the next
/// line break opportunity before location. When `hyphenating` is `true`, it is an
/// auto-hyphenation point.
///
/// - Parameters:
///   - textLayoutManager: The text layout manager sending the message.
///   - location: The candidate break location.
///   - hyphenating: `true` if this is an auto-hyphenation point.
///
/// - Returns: `true` to allow the break; `false` to prevent it.
- (BOOL)textLayoutManager:(NSTextLayoutManager *)textLayoutManager shouldBreakLineBeforeLocation:(id <NSTextLocation>)location hyphenating:(BOOL)hyphenating;

/// Returns a dictionary of rendering attributes for rendering a link.
///
/// Just as other rendering attributes, specifying
/// <doc://com.apple.documentation/documentation/foundation/nsnull> removes the
/// attribute from the final attributes used for rendering. It has priority over
/// the general rendering attributes.
///
/// - Parameters:
///   - textLayoutManager: The text layout manager sending the message.
///   - link: The link object.
///   - location: The document location of the link.
///   - renderingAttributes: The default rendering attributes.
///
/// - Returns: A dictionary of rendering attributes for the link, or `nil` to use defaults.
- (nullable NSDictionary<NSAttributedStringKey, id> *)textLayoutManager:(NSTextLayoutManager *)textLayoutManager renderingAttributesForLink:(id)link atLocation:(id <NSTextLocation>)location defaultAttributes:(NSDictionary<NSAttributedStringKey, id> *)renderingAttributes;



/// Notifies the delegate that a view provider associated with a text attachment is about to be invalidated.
///
/// The delegate can use this to cache the view provider.
///
/// - Parameters:
///   - textLayoutManager: The text layout manager sending the message.
///   - viewProvider: The view provider being invalidated.
///   - textAttachment: The attachment associated with the view provider.
- (void)textLayoutManager:(NSTextLayoutManager *)textLayoutManager cacheTextAttachmentViewProvider:(NSTextAttachmentViewProvider *)viewProvider forTextAttachment:(NSTextAttachment *)textAttachment API_AVAILABLE(macos(27.0), ios(27.0), tvos(27.0), visionos(27.0)) API_UNAVAILABLE(watchos);

/// Returns a cached `NSTextAttachmentViewProvider` to be associated with a particular attachment.
///
/// - Parameters:
///   - textLayoutManager: The text layout manager sending the message.
///   - attachment: The attachment to retrieve a cached view provider for.
///
/// - Returns: A previously cached view provider, or `nil`.
- (nullable NSTextAttachmentViewProvider *)textLayoutManager:(NSTextLayoutManager *)textLayoutManager retrieveCachedTextAttachmentViewProviderForTextAttachment:(NSTextAttachment *)attachment API_AVAILABLE(macos(27.0), ios(27.0), tvos(27.0), visionos(27.0)) API_UNAVAILABLE(watchos);

@end

NS_HEADER_AUDIT_END(nullability, sendability)
#else
#import <UIFoundation/NSTextLayoutManager.h>
#endif
