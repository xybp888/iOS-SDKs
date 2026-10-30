#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIFoundation/NSTextContainer.h>)
//
//  NSTextContainer.h
//  Text Kit
//
//  Copyright (c) 1994-2025, Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKitDefines.h>
#import <UIKit/NSParagraphStyle.h>
#import <UIKit/NSText.h>
#import <UIKit/NSLayoutManager.h>

@class NSTextLayoutManager;
@class NSTextView;
@class UIBezierPath;

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

/// A region where text layout occurs.
///
/// An ``NSLayoutManager`` or ``NSTextLayoutManager`` uses ``NSTextContainer``
/// to determine where to break lines, lay out portions of text, and so on. An
/// ``NSTextContainer`` object typically defines rectangular regions, but you
/// can define exclusion paths inside the text container to create regions where
/// text doesn't flow. You can also subclass to create text containers with
/// nonrectangular regions, such as circular regions, regions with holes in
/// them, or regions that flow alongside graphics.
///
/// You can access instances of the ``NSTextContainer``, ``NSLayoutManager``,
/// and ``NSTextStorage`` classes from threads other than the main thread as
/// long as the app guarantees access from only one thread at a time. The same
/// restrictions apply to ``NSTextLayoutManager`` and ``NSTextContentStorage``.
UIKIT_EXTERN API_AVAILABLE(macos(10.0), ios(7.0), tvos(9.0), visionos(1.0)) API_UNAVAILABLE(watchos)
@interface NSTextContainer : NSObject <NSSecureCoding, NSTextLayoutOrientationProvider>

/**************************** Initialization ****************************/

/// Initializes a text container with a specified bounding rectangle.
///
/// The new text container must be added to an ``NSLayoutManager`` or
/// ``NSTextLayoutManager`` object before it can be used. The text container
/// must also have an associated
/// <doc://com.apple.documentation/documentation/appkit/nstextview> object for
/// text to be displayed. This method is the designated initializer for the
/// `NSTextContainer` class.
///
/// - Parameters:
///   - size: The size of the text container's bounding rectangle.
///
/// ## See Also
///
/// - [Text Layout Programming Guide](https://developer.apple.com/library/archive/documentation/Cocoa/Conceptual/TextLayout/TextLayout.html#//apple_ref/doc/uid/10000158i)
/// - [Cocoa Text Architecture Guide](https://developer.apple.com/library/archive/documentation/TextFonts/Conceptual/CocoaTextArchitecture/Introduction/Introduction.html#//apple_ref/doc/uid/TP40009459)
/// - ``NSLayoutManager/addTextContainer(_:)``
/// - [Text System Storage Layer Overview](https://developer.apple.com/library/archive/documentation/Cocoa/Conceptual/TextStorageLayer/TextStorageLayer.html#//apple_ref/doc/uid/10000087i)
- (instancetype)initWithSize:(CGSize)size NS_DESIGNATED_INITIALIZER API_AVAILABLE(macos(10.11), ios(7.0), tvos(9.0), visionos(1.0)) API_UNAVAILABLE(watchos);
/// Creates a text container from data in an unarchiver.
///
/// - Parameters:
///   - coder: A coder that conforms to <doc://com.apple.documentation/documentation/foundation/nscoder>.
- (instancetype)initWithCoder:(NSCoder *)coder NS_DESIGNATED_INITIALIZER;

/// The ``NSTextLayoutManager`` owning the text container.
///
/// When non-nil, the legacy `layoutManager` should be `nil`.
@property (weak, nullable, readonly, NS_NONATOMIC_IOSONLY) NSTextLayoutManager *textLayoutManager API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0), visionos(1.0)) API_UNAVAILABLE(watchos);

/************************* Container shape properties *************************/

/// The size of the text container's bounding rectangle.
///
/// This property defines the maximum size for the layout area returned from
/// ``NSTextContainer/lineFragmentRect(forProposedRect:at:writingDirection:remaining:)``.
/// A value of `0.0` or less means no limitation.
///
/// If you don't specify an explicit size when you initialize a text container,
/// the system uses a default large size of (`10000000.0`, `10000000.0`).
@property (NS_NONATOMIC_IOSONLY) CGSize size API_AVAILABLE(macos(10.11), ios(7.0), tvos(9.0), visionos(1.0)) API_UNAVAILABLE(watchos);

/// The behavior of the last line inside the text container.
///
/// The ``NSLineBreakMode`` constants specify what happens when a line is too
/// long for its container. For example, wrapping can occur on word boundaries
/// (the default) or character boundaries, or the line can be clipped or
/// truncated. The default value of this property is
/// ``NSLineBreakMode/byWordWrapping``.
@property (NS_NONATOMIC_IOSONLY) NSLineBreakMode lineBreakMode API_AVAILABLE(macos(10.11), ios(7.0), tvos(9.0), visionos(1.0)) API_UNAVAILABLE(watchos);

/// An array of path objects that represents the regions where text doesn't display in the text container.
///
/// The default value is an empty array.
@property (copy, NS_NONATOMIC_IOSONLY) NSArray<UIBezierPath *> *exclusionPaths API_AVAILABLE(macos(10.11), ios(7.0), tvos(9.0), visionos(1.0)) API_UNAVAILABLE(watchos);

/************************* Layout constraint properties *************************/

/// The value for the text inset within line fragment rectangles.
///
/// The padding appears at the beginning and end of the line fragment
/// rectangles. The layout manager and text layout manager use this value to
/// determine the layout width. The default value of this property is `5.0`.
///
/// Line fragment padding is not designed to express text margins. Instead, you
/// should use insets on your text view, adjust the paragraph margin attributes,
/// or change the position of the text view within its superview.
///
/// ## See Also
///
/// - ``lineFragmentRect(forProposedRect:at:writingDirection:remaining:)``
@property (NS_NONATOMIC_IOSONLY) CGFloat lineFragmentPadding;

/// The maximum number of lines that the text container can store.
///
/// The layout manager and text layout manager use the value of this property to
/// determine the maximum number of lines associated with the text container.
/// The default value of this property is `0`, which indicates that there is no
/// limit.
@property (NS_NONATOMIC_IOSONLY) NSUInteger maximumNumberOfLines API_AVAILABLE(macos(10.11), ios(7.0), tvos(9.0), visionos(1.0)) API_UNAVAILABLE(watchos);

/**************************** Line fragments ****************************/

/// Returns the bounds of a line fragment rectangle inside the text container for the proposed rectangle.
///
/// The bounds of the line fragment rectangle are determined by the intersection
/// of `proposedRect` and the text container's bounding rectangle defined by its
/// ``NSTextContainer/size`` property. The regions defined by the
/// ``NSTextContainer/exclusionPaths`` property are excluded from the return
/// value. It is possible that `proposedRect` can be divided into multiple line
/// fragments due to exclusion paths. In that case, `remainingRect` returns the
/// remainder that can be passed in as the proposed rectangle for the next
/// iteration.
///
/// This method can be overridden by subclasses for further text container
/// region customization.
///
/// - Parameters:
///   - proposedRect: A rectangle in which to lay out text proposed by the layout manager or text layout manager.
///   - characterIndex: The character location inside the text storage for the line fragment being processed.
///   - baseWritingDirection: The direction of advancement for line fragments inside a visual horizontal line. The values passed into the method are either ``NSWritingDirection/leftToRight`` or ``NSWritingDirection/rightToLeft``.
///   - remainingRect: The remainder of the proposed rectangle that was excluded from the returned rectangle. It can be passed in as the proposed rectangle for the next iteration.
///
/// - Returns: The bounds of the line fragment rect.
- (CGRect)lineFragmentRectForProposedRect:(CGRect)proposedRect atIndex:(NSUInteger)characterIndex writingDirection:(NSWritingDirection)baseWritingDirection remainingRect:(nullable CGRect *)remainingRect API_AVAILABLE(macos(10.11), ios(7.0), tvos(9.0), visionos(1.0)) API_UNAVAILABLE(watchos);

/// A Boolean that indicates whether the text container's region is a rectangle with no holes or gaps, and whose edges are parallel to the text view's coordinate system axes.
///
/// The value of this property is
/// <doc://com.apple.documentation/documentation/swift/true> when the text
/// container's region is a rectangle with no holes or gaps and the edges are
/// parallel to the text view's coordinate system axes. The default value of
/// this property is <doc://com.apple.documentation/documentation/swift/false>
/// when the ``NSTextContainer/exclusionPaths`` property contains one or more
/// items, when the ``NSTextContainer/maximumNumberOfLines`` property is not
/// zero, or when you override the
/// ``NSTextContainer/lineFragmentRect(forProposedRect:at:writingDirection:remaining:)``
/// method. Otherwise, the default value is
/// <doc://com.apple.documentation/documentation/swift/true>.
@property (getter=isSimpleRectangularTextContainer, readonly, NS_NONATOMIC_IOSONLY) BOOL simpleRectangularTextContainer API_AVAILABLE(macos(10.0), ios(9.0), tvos(9.0), visionos(1.0)) API_UNAVAILABLE(watchos);


/**************************** View synchronization ****************************/

/// A Boolean that controls whether the text container adjusts the width of its bounding rectangle when its text view resizes.
///
/// When the value of this property is
/// <doc://com.apple.documentation/documentation/swift/true>, the text container
/// adjusts its width when the width of its text view changes. The default value
/// of this property is
/// <doc://com.apple.documentation/documentation/swift/false>.
///
/// For more information about size tracking, see [Text System Storage Layer Overview](https://developer.apple.com/library/archive/documentation/Cocoa/Conceptual/TextStorageLayer/TextStorageLayer.html#//apple_ref/doc/uid/10000087i).
///
/// ## See Also
///
/// - ``NSTextContainer/size``
@property (NS_NONATOMIC_IOSONLY) BOOL widthTracksTextView;
/// A Boolean that controls whether the text container adjusts the height of its bounding rectangle when its text view resizes.
///
/// When the value of this property is
/// <doc://com.apple.documentation/documentation/swift/true>, the text container
/// adjusts its height when the height of its text view changes. The default
/// value of this property is
/// <doc://com.apple.documentation/documentation/swift/false>.
///
/// For more information about size tracking, see [Text System Storage Layer Overview](https://developer.apple.com/library/archive/documentation/Cocoa/Conceptual/TextStorageLayer/TextStorageLayer.html#//apple_ref/doc/uid/10000087i).
///
/// ## See Also
///
/// - ``NSTextContainer/size``
@property (NS_NONATOMIC_IOSONLY) BOOL heightTracksTextView;

@end

#pragma mark NSLayoutManager Interface
@class NSLayoutManager;

@interface NSTextContainer (NSTextContainer_NSLayoutManagerInterface)

// Accessor for the NSLayoutManager object owning the receiver.
// Avoid assigning a layout manager directly through this property.  Adding a text container to a layout manager through -[NSLayoutManager addTextContainer:] will use the property for assigning the new layout manager.
@property (nullable, assign, NS_NONATOMIC_IOSONLY) NSLayoutManager *layoutManager API_AVAILABLE(macos(10.0), ios(9.0), tvos(9.0), visionos(1.0)) API_UNAVAILABLE(watchos);

// This method should be used instead of the primitive -setLayoutManager: if you need to replace a container's layoutManager with a new one leaving the rest of the web intact.  All the NSTextContainers on the old NSLayoutManager get transferred to the new one.  This method deals with all the work of making sure the containers don't get deallocated and removing the old layoutManager from the text storage and replacing it with the new one.
- (void)replaceLayoutManager:(NSLayoutManager *)newLayoutManager NS_SWIFT_NAME(replaceLayoutManager(_:)) API_AVAILABLE(macos(10.0), ios(9.0), tvos(9.0), visionos(1.0)) API_UNAVAILABLE(watchos);
@end

NS_HEADER_AUDIT_END(nullability, sendability)
#else
#import <UIFoundation/NSTextContainer.h>
#endif
