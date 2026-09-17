#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIFoundation/NSTextContentManager.h>)
//
//  NSTextContentManager.h
//  Text Kit
//
//  Copyright (c) 2018-2025, Apple Inc. All rights reserved.
//

#import <Foundation/NSArray.h>
#import <Foundation/NSNotification.h>
#import <UIKit/UIKitDefines.h>

@class NSTextRange;
@class NSTextElement;
@class NSTextParagraph;
@class NSTextLayoutManager;
@class NSTextStorage;
@class NSTextContentStorage;
@protocol NSTextLocation;
@protocol NSTextContentManagerDelegate;
@protocol NSTextStorageObserving;

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

#pragma mark NSTextElementProvider
/// Values that control the order in which the framework enumerates text elements.
typedef NS_OPTIONS(NSUInteger, NSTextContentManagerEnumerationOptions) {
    /// The value that represents no custom enumeration handling.
    NSTextContentManagerEnumerationOptionsNone = 0,
    /// Causes enumerations to start from the end of the text element.
    NSTextContentManagerEnumerationOptionsReverse = (1 << 0)
} API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0), visionos(1.0)) API_UNAVAILABLE(watchos);

/// A protocol the text content manager and its concrete subclasses conform to, which defines the interface for interacting with custom content types of a text document.
API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0), visionos(1.0)) API_UNAVAILABLE(watchos)
@protocol NSTextElementProvider <NSObject>
/// The starting and ending locations for the document.
///
/// The subclass could use its own implementation of a location object conforming
/// to ``NSTextLocation``.
@property (strong, readonly) NSTextRange *documentRange;

/// Enumerates text elements starting at the text location you provide.
///
/// If `textLocation` is `nil`, the method uses `documentRange.location` for
/// forward enumeration and `documentRange.endLocation` for reverse enumeration.
/// When enumerating backward, the method starts with the element preceding the
/// one containing `textLocation`. If enumerated at least one element, it
/// returns the edge of the enumerated range.
///
/// The enumerated range might not match the range of the last element returned.
/// It enumerates the elements in the sequence, but it can skip a range (it can
/// limit the maximum number of text elements enumerated for a single invocation
/// or hide some elements from the layout).
///
/// Subclasses are responsible for caching the ``NSTextElement`` objects they return.
/// The text layout system uses weak references to track elements internally, and elements that are deallocated without explicit layout invalidation may cause layout fragments to lose their content association.
///
/// Returning `false` from block breaks out of the enumeration.
///
/// - Parameters:
///   - textLocation: The ``NSTextLocation`` at which to start the enumeration.
///   - options: One of the possible `NSTextContentManagerEnumerationOptions` directions.
///   - block: A block called for each enumerated text element. Return `false` to end the enumeration process.
///
/// - Returns: An ``NSTextLocation`` representing the edge of the enumerated range.
- (nullable id <NSTextLocation>)enumerateTextElementsFromLocation:(nullable id <NSTextLocation>)textLocation options:(NSTextContentManagerEnumerationOptions)options usingBlock:(BOOL (NS_NOESCAPE ^)(NSTextElement *element))block;

/// Replaces the characters specified by range with the text elements you provide.
///
/// If the edges of `range` aren't at existing element range boundaries, the
/// method either splits the element if it allows the operation (for example,
/// ``NSTextParagraph``), or adjusts the replacement range.
///
/// > Note:
/// > This method is for use by ``NSTextLayoutManager``.
///
/// - Parameters:
///   - range: An ``NSTextRange``.
///   - textElements: The elements to replace the characters at `range`.
- (void)replaceContentsInRange:(NSTextRange *)range withTextElements:(nullable NSArray<NSTextElement *> *)textElements;

/// Synchronizes changes to the backing store.
///
/// If `completionHandler` is `nil`, performs the operation synchronously. The
/// `completionHandler` gets passed `error` if the synchronization fails. It
/// should block (or fail if synchronous) when there's an active transaction.
///
/// - Parameters:
///   - completionHandler: A completion handler to run upon successful completion, or to process an error upon failure.
- (void)synchronizeToBackingStore:(nullable void (^)(NSError * _Nullable error))completionHandler;

@optional
/// Returns a new location from location with the offset you provide.
///
/// The offset value could be positive or negative indicating the logical
/// direction. Could return `nil` when the inputs don't produce any legal
/// location (i.e. out of bounds index).
///
/// - Parameters:
///   - location: An ``NSTextLocation`` in the text element.
///   - offset: An offset of the number of characters to or from `location`.
///
/// - Returns: A new ``NSTextLocation``, or `nil` if the offset exceeds the bounds of the text.
- (nullable id <NSTextLocation>)locationFromLocation:(id <NSTextLocation>)location withOffset:(NSInteger)offset;

/// Returns the offset between the two specified locations.
///
/// The return value could be positive or negative. This method can return
/// <doc://com.apple.documentation/documentation/foundation/nsnotfound> when the
/// method can't represent an offset as an integer value. This can occur, for
/// example, if the locations aren't in the same document.
///
/// - Parameters:
///   - from: A starting location.
///   - to: An ending location.
///
/// - Returns: An integer that represents the offset between the starting and ending locations.
- (NSInteger)offsetFromLocation:(id <NSTextLocation>)from toLocation:(id <NSTextLocation>)to;

/// A method you implement if the location backing store requires manual adjustment after editing.
///
/// When `textRange` is intersecting or following the current edited range, the
/// method returns the range adjusted for the modification in the editing
/// session. Returns `nil` when no adjustment is necessary.
///
/// - Parameters:
///   - textRange: An ``NSTextRange`` that the method adjusts.
///   - forEditingTextSelection: A Boolean value that indicates if `textRange` is for the text selection associated with the edit session.
///
/// - Returns: The adjusted range, or `nil` when no adjustment is necessary.
- (nullable NSTextRange *)adjustedRangeFromRange:(NSTextRange *)textRange forEditingTextSelection:(BOOL)forEditingTextSelection;
@end

#pragma mark NSTextContentManager
/// An abstract class that defines the interface and a default implementation for managing the text document contents.
///
/// The concrete subclass overrides ``NSTextElementProvider`` for managing the
/// content backing store. It is the root object that strongly references the
/// rest of objects in the TextKit network via an array of
/// ``NSTextLayoutManager``. It manages the editing transaction by tracking the
/// ``NSTextLayoutManager`` that is active and focused for editing.
API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0), visionos(1.0)) API_UNAVAILABLE(watchos)
@interface NSTextContentManager : NSObject <NSTextElementProvider, NSSecureCoding>
#pragma mark Initialization
/// Creates a new content manager.
- (instancetype)init NS_DESIGNATED_INITIALIZER;
/// Creates a new content manager object from data in an unarchiver.
///
/// - Parameters:
///   - coder: An unarchiver that conforms to the <doc://com.apple.documentation/documentation/foundation/nscoder> class.
- (nullable instancetype)initWithCoder:(NSCoder *)coder NS_DESIGNATED_INITIALIZER;

#pragma mark Basic properties
/// The delegate for the content manager object.
@property (weak, nullable) id <NSTextContentManagerDelegate> delegate;

#pragma mark NSTextLayoutManager management
/// The array of text layout managers associated with this text content manager.
///
/// This property is KVO-compliant.
@property (copy, readonly) NSArray<NSTextLayoutManager *> *textLayoutManagers;

/// Adds the text layout manager you provide to the list of layout managers.
///
/// - Parameters:
///   - textLayoutManager: The text layout manager to add.
- (void)addTextLayoutManager:(NSTextLayoutManager *)textLayoutManager;
/// Removes the text layout manager you specify from the list of layout managers.
///
/// - Parameters:
///   - textLayoutManager: The text layout manager to remove.
- (void)removeTextLayoutManager:(NSTextLayoutManager *)textLayoutManager;

/// The primary text layout manager for this content.
///
/// The primary ``NSTextLayoutManager`` interacts with the user, allowing edits.
/// Setting this property to an ``NSTextLayoutManager`` not in
/// ``textLayoutManagers`` resets it to `nil`. It automatically synchronizes
/// pending edits before switching to a new primary object. The operation is
/// synchronous.
///
/// This property is KVO-compliant.
@property (nullable, strong) NSTextLayoutManager *primaryTextLayoutManager;

/// Synchronizes changes to all nonprimary text layout managers.
///
/// If `completionHandler` is `nil`, this method performs the operation
/// synchronously. The framework passes any error to the `completionHandler`.
/// The method blocks (or fails, if synchronous) when there's an active
/// transaction.
///
/// - Parameters:
///   - completionHandler: A completion handler that runs on success, or to handle error conditions.
- (void)synchronizeTextLayoutManagers:(nullable void (^)(NSError * _Nullable error))completionHandler;

#pragma mark Element access
/// Returns an array of text elements that intersect with the range you specify.
///
/// This method can return a set of elements that don't fill the entire range if
/// the entire range isn't synchronously available. Uses
/// ``NSTextElementProvider/enumerateTextElements(from:options:using:)`` to fill
/// the array.
///
/// - Parameters:
///   - range: An ``NSTextRange`` that describes the range of text to process.
///
/// - Returns: An array of ``NSTextElement``.
- (NSArray<NSTextElement *> *)textElementsForRange:(NSTextRange *)range;

#pragma mark Transaction
/// Indicates there's an active editing transaction from the primary text layout manager.
///
/// The synchronization operations to non-primary text layout managers and the
/// backing store block (or fail when synchronous) while this property is `true`.
/// Non-primary text layout managers should avoid accessing the elements while
/// this is `true`. KVO-compliant.
@property (readonly) BOOL hasEditingTransaction;

/// Performs an editing transaction and invokes a block upon completion.
///
/// Invoked by ``primaryTextLayoutManager`` controlling the active editing
/// transaction. Can be nested. The outermost transaction toggles
/// ``hasEditingTransaction`` and sends synchronization messages if enabled after
/// invoking `transaction`.
///
/// - Parameters:
///   - transaction: The block to execute within the editing transaction.
- (void)performEditingTransactionUsingBlock:(void (NS_NOESCAPE ^) (void))transaction NS_SWIFT_DISABLE_ASYNC;

/// Records information about an edit action to the transaction.
///
/// `originalTextRange` is the range edited before the action, and
/// `newTextRange` is the corresponding range after the action. The concrete
/// subclass should invoke this method for each edit action.
///
/// - Parameters:
///   - originalTextRange: The range before the edit.
///   - newTextRange: The corresponding range after the edit.
- (void)recordEditActionInRange:(NSTextRange *)originalTextRange newTextRange:(NSTextRange *)newTextRange;

/// Determines if the framework should automatically synchronize all text layout managers when exiting an editing transaction.
///
/// The default value is `true`.
@property BOOL automaticallySynchronizesTextLayoutManagers;

/// Determines whether to automatically synchronize with the backing store when an editing transaction finishes.
///
/// The default value is `false`.
@property BOOL automaticallySynchronizesToBackingStore;
@end

#pragma mark NSTextContentManagerDelegate
/// The optional methods that delegates of content manager objects implement for customizing or validating text elements.
API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0), visionos(1.0)) API_UNAVAILABLE(watchos)
@protocol NSTextContentManagerDelegate <NSObject>
@optional
/// Returns a custom element for the specified location.
///
/// When non-nil, `textContentManager` uses the element instead of creating one
/// based on its standard mapping logic.
- (nullable NSTextElement *)textContentManager:(NSTextContentManager *)textContentManager textElementAtLocation:(id <NSTextLocation>)location;

/// Gives the delegate a chance to validate a text element before enumeration.
///
/// Returning `false` indicates the text element should be skipped from the enumeration.
- (BOOL)textContentManager:(NSTextContentManager *)textContentManager shouldEnumerateTextElement:(NSTextElement *)textElement options:(NSTextContentManagerEnumerationOptions)options;
@end

#pragma mark NSTextContentStorageDelegate
/// The optional methods that delegates of content storage objects implement to handle content processing.
API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0), visionos(1.0)) API_UNAVAILABLE(watchos)
@protocol NSTextContentStorageDelegate <NSTextContentManagerDelegate>
@optional
/// Returns a custom `NSTextParagraph` for the specified range in the content storage's attributed string.
///
/// When non-nil, `textContentStorage` uses the text paragraph instead of
/// creating the standard ``NSTextParagraph`` with the attributed substring in
/// range. The attributed string for a custom text paragraph must have
/// `range.length`.
- (nullable NSTextParagraph *)textContentStorage:(NSTextContentStorage *)textContentStorage textParagraphWithRange:(NSRange)range;
@end

#pragma mark NSTextContentStorage
/// A concrete object for managing the document's text content and generating the text elements necessary for layout.
///
/// An ``NSTextContentStorage`` object provides the backing store for document
/// content. It stores the text in an attributed string object, and defaults to
/// using an ``NSTextStorage`` object. It also maps portions of the text to
/// ``NSTextElement`` objects to organize the text into paragraphs, lists, and
/// other common element types found in text content. During layout, TextKit
/// uses these elements to lay out and render the content into one or more
/// rendering surfaces.
///
/// `NSTextContentStorage` is a concrete subclass of ``NSTextContentManager``
/// providing support for `NSAttributedString` backing store. It also implements
/// `NSTextStorageObserving` participating as a client of `NSTextStorage`. The
/// facility only supports a single `NSTextContentStorage` associated with a text
/// storage. When ``NSTextStorage`` is non-nil, ``attributedString`` is ignored.
/// By default, `NSTextContentStorage` is initialized with `NSTextStorage` as
/// the backing store.
API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0), visionos(1.0)) API_UNAVAILABLE(watchos)
@interface NSTextContentStorage : NSTextContentManager <NSTextStorageObserving>
#pragma mark Basic properties
/// The delegate for the content storage object.
@property (weak, nullable) id <NSTextContentStorageDelegate> delegate;

/// When `true`, `NSTextContentStorage` assumes the paragraph with `NSTextList` includes the text list marker string.
///
/// Utilizes `NSTextList.includesTextListMarkers` as the default value.
@property BOOL includesTextListMarkers API_AVAILABLE(macos(26.0), ios(26.0), tvos(26.0), visionos(26.0)) API_UNAVAILABLE(watchos);

#pragma mark Document contents
/// An attributed string that contains the contents of the document.
///
/// KVO-compliant.
@property (nullable, copy) NSAttributedString *attributedString;

#pragma mark NSAttributedString utils
/// Returns a new attributed string for the text element.
///
/// Returns `nil` if `textElement` cannot be mapped to `NSAttributedString`.
///
/// - Parameters:
///   - textElement: The text element to convert.
///
/// - Returns: An attributed string representation, or `nil` if unmappable.
- (nullable NSAttributedString *)attributedStringForTextElement:(NSTextElement *)textElement;

/// Returns the text element corresponding to the attributed string.
///
/// Returns `nil` when `attributedString` contains attributes not mappable to
/// ``NSTextElement``.
///
/// - Parameters:
///   - attributedString: The attributed string to convert.
///
/// - Returns: A text element, or `nil` if the attributes are unmappable.
- (nullable NSTextElement *)textElementForAttributedString:(NSAttributedString *)attributedString;

#pragma mark Optional NSTextElementProvider methods
/// Returns a new text location object based on an existing location and offset you provide.
///
/// The offset value could be positive or negative indicating the logical
/// direction. Could return `nil` when the inputs don't produce any legal
/// location (i.e. out of bounds index).
///
/// - Parameters:
///   - location: The base location.
///   - offset: The offset from the base location.
///
/// - Returns: A new location, or `nil` if the result would be out of bounds.
- (nullable id <NSTextLocation>)locationFromLocation:(id <NSTextLocation>)location withOffset:(NSInteger)offset;

/// Returns the number of characters between the specified locations.
///
/// The return value could be positive or negative. Could return `NSNotFound`
/// when the offset cannot be represented in an integer value (i.e. locations
/// are not in the same document).
///
/// - Parameters:
///   - from: The starting location.
///   - to: The ending location.
///
/// - Returns: The signed offset, or <doc://com.apple.documentation/documentation/foundation/nsnotfound> if the locations are not in the same document.
- (NSInteger)offsetFromLocation:(id <NSTextLocation>)from toLocation:(id <NSTextLocation>)to;

/// Returns the text range, if any, in the backing store that required manual adjustment after editing.
///
/// Should be implemented if the location backing store requires manual
/// adjustment after editing. When `textRange` is intersecting or following the
/// current edited range, the method returns the range adjusted for the
/// modification in the editing session. Returns `nil` when no adjustment is
/// necessary.
///
/// - Parameters:
///   - textRange: The range to adjust.
///   - forEditingTextSelection: Indicates if `textRange` is for the text selection associated with the edit session.
///
/// - Returns: The adjusted range, or `nil` if no adjustment is necessary.
- (nullable NSTextRange *)adjustedRangeFromRange:(NSTextRange *)textRange forEditingTextSelection:(BOOL)forEditingTextSelection;
@end

/// Posted by `NSTextContentStorage` when a text attribute unsupported by `NSTextContentStorage` is added to the underlying text storage.
UIKIT_EXTERN NSNotificationName NSTextContentStorageUnsupportedAttributeAddedNotification API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0), visionos(1.0)) API_UNAVAILABLE(watchos);

NS_HEADER_AUDIT_END(nullability, sendability)
#else
#import <UIFoundation/NSTextContentManager.h>
#endif
