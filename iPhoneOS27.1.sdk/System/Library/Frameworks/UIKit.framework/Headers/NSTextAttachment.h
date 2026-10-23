#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIFoundation/NSTextAttachment.h>)
//
//  NSTextAttachment.h
//  Text Kit
//
//  Copyright (c) 1994-2025, Apple Inc. All rights reserved.
//

#import <Foundation/NSAttributedString.h>
#import <CoreGraphics/CGGeometry.h>
#import <UIKit/UIKitDefines.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

enum {
    /// Specifies a character that denotes an attachment.
    NSAttachmentCharacter API_AVAILABLE(macos(10.0), ios(7.0), tvos(9.0), watchos(2.0), visionos(1.0)) = 0xFFFC
} API_AVAILABLE(macos(10.0), ios(7.0), tvos(9.0), watchos(2.0), visionos(1.0));

@class NSTextContainer;
@class NSLayoutManager;
@class UIImage;
@class UIView;
@class NSFileWrapper;
@class NSTextAttachmentViewProvider;
@class NSTextLayoutManager;
@protocol NSTextLocation;

/// A set of methods that defines the interface to attachment objects from a text layout manager.
///
/// The `NSTextAttachmentLayout` protocol is the interface for working with
/// attachment objects with an ``NSTextAttachmentViewProvider`` using a
/// ``NSTextLayoutManager`` in macOS 12 and iOS 15 and later.
API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0), watchos(8.0), visionos(1.0))
@protocol NSTextAttachmentLayout <NSObject>

/// Returns the image object rendered at the bounds and inside the text container you specify.
///
/// A custom implementation should return an image appropriate for the target
/// rendering context that you derive by arguments to this method. The default
/// ``NSTextAttachment`` implementation returns the contents of the `image`
/// property when non-`nil`. If the `image` property is `nil`, it returns an
/// image based on the `contents` and `fileType` properties.
///
/// - Parameters:
///   - bounds: The <doc://com.apple.documentation/documentation/corefoundation/cgrect> that presents the image boundaries inside `textContainer`.
///   - attributes: A dictionary of <doc://com.apple.documentation/documentation/foundation/nsattributedstring/key> attributes.
///   - location: An ``NSTextLocation`` that indicates the location of the attachment inside the document.
///   - textContainer: The ``NSTextContainer`` that defines the area to fill in with text.
///
/// - Returns: An optional image object.
- (nullable UIImage *)imageForBounds:(CGRect)bounds attributes:(NSDictionary<NSAttributedStringKey, id> *)attributes location:(id <NSTextLocation>)location textContainer:(nullable NSTextContainer *)textContainer API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0), watchos(8.0), visionos(1.0));

/// Returns the layout bounds of the attachment you specify.
///
/// The framework interprets the bounds origin to match `position` inside
/// `proposedLineFragment`. The default ``NSTextAttachment`` implementation
/// returns bounds if the value isn't equivalent to
/// <doc://com.apple.documentation/documentation/coregraphics/cgrectzero>;
/// otherwise, it derives the bounds value from `image.size`. Conforming objects
/// can implement more sophisticated logic for negotiating the frame size based
/// on the available container space and proposed line fragment rectangle.
///
/// - Parameters:
///   - attributes: A dictionary of <doc://com.apple.documentation/documentation/foundation/nsattributedstring/key> attributes.
///   - location: An ``NSTextLocation`` that indicates the location of the attachment inside the document.
///   - textContainer: The ``NSTextContainer`` that defines the area to fill in with text.
///   - proposedLineFragment: A <doc://com.apple.documentation/documentation/corefoundation/cgrect> that describes the boundaries of the line fragment.
///   - position: A <doc://com.apple.documentation/documentation/corefoundation/cgpoint> inside `proposedLineFragment`.
///
/// - Returns: A <doc://com.apple.documentation/documentation/corefoundation/cgrect> that describes the boundaries of the attachment, or `CGRectZero`.
- (CGRect)attachmentBoundsForAttributes:(NSDictionary<NSAttributedStringKey, id> *)attributes location:(id <NSTextLocation>)location textContainer:(nullable NSTextContainer *)textContainer proposedLineFragment:(CGRect)proposedLineFragment position:(CGPoint)position API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0), watchos(8.0), visionos(1.0));

/// Returns the text attachment view provider corresponding to the file type.
///
/// The default implementation queries the text attachment view provider class
/// using the ``NSTextAttachment/textAttachmentViewProviderClass(forFileType:)``
/// method of ``NSTextAttachment``. When non-`nil`, it instantiates a view, then
/// fills properties declared in `NSTextAttachmentViewProvider` if implemented.
///
/// - Parameters:
///   - parentView: The parent view.
///   - location: An ``NSTextLocation`` that indicates the location of the attachment inside the document.
///   - textContainer: The ``NSTextContainer`` that defines the area to fill in with text.
///
/// - Returns: An ``NSTextAttachmentViewProvider``.
- (nullable NSTextAttachmentViewProvider *)viewProviderForParentView:(nullable UIView *)parentView location:(id <NSTextLocation>)location textContainer:(nullable NSTextContainer *)textContainer API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0), visionos(1.0)) API_UNAVAILABLE(watchos);
@end

/// The values for the attachment characteristics of attributed strings and related objects.
///
/// The
/// <doc://com.apple.documentation/documentation/foundation/nsattributedstring>
/// class uses text attachment objects as the values for attachment attributes
/// (stored in the attributed string under the
/// <doc://com.apple.documentation/documentation/foundation/nsattributedstring/key/1534036-attachment>
/// key in Swift or the ``NSAttachmentAttributeName`` key in Objective-C).
///
/// A text attachment object contains either an
/// <doc://com.apple.documentation/documentation/foundation/nsdata> object or an
/// <doc://com.apple.documentation/documentation/foundation/filewrapper> object,
/// which in turn holds the contents of the attached file. The properties of
/// this class configure the appearance of the text attachment in your
/// interface. In macOS, the text attachment also uses a cell object that
/// conforms to the
/// <doc://com.apple.documentation/documentation/appkit/nstextattachmentcellprotocol>
/// protocol to draw the image that represents the text and handles mouse
/// events. For more information about text attachments, see the
/// <doc://com.apple.documentation/documentation/foundation/nsattributedstring>
/// and <doc://com.apple.documentation/documentation/appkit/nstextview>.
///
/// In macOS 12 and iOS 15 and later, ``NSTextAttachmentViewProvider`` and
/// ``NSTextAttachmentLayout`` provide additional capabilities to represent
/// document locations in terms of an ``NSTextLocation`` or an ``NSTextRange``,
/// and provide support for view-based text attachments.
API_AVAILABLE(macos(10.0), ios(7.0), tvos(9.0), watchos(2.0), visionos(1.0)) @interface NSTextAttachment : NSObject <NSTextAttachmentLayout, NSSecureCoding>

/**************************** Initialization ****************************/

/// Creates a text attachment object with the specified data.
///
/// This method is the designated initializer for the `NSTextAttachment` class.
///
/// When either `contentData` or `uti` is `nil`, TextKit considers the receiver
/// to be an attachment without document contents. In this case, the
/// `NSAttributedString` external file writing methods try to save the value of
/// the ``NSTextAttachment/image`` property instead.
///
/// - Parameters:
///   - contentData: Data to use for the text attachment contents. Can be `nil`.
///   - uti: A uniform type identifier specifying the data type of the attachment contents. Can be `nil`.
///
/// - Returns: A new `NSTextAttachment` object.
- (instancetype)initWithData:(nullable NSData *)contentData ofType:(nullable NSString *)uti NS_DESIGNATED_INITIALIZER API_AVAILABLE(macos(10.11), ios(7.0), tvos(9.0), watchos(2.0), visionos(1.0));



/**************************** Content properties ****************************/

/// The contents for the text attachment.
///
/// Modifying this property has a side effect of invalidating ``image`` and
/// ``fileWrapper`` properties.
@property (nullable, copy, NS_NONATOMIC_IOSONLY) NSData *contents API_AVAILABLE(macos(10.11), ios(7.0), tvos(9.0), watchos(2.0), visionos(1.0));

/// The file type of the contents for the text attachment.
///
/// A UTI describing the format for ``contents``. Modifying this property has a
/// side effect of invalidating ``image`` and ``fileWrapper`` properties.
@property (nullable, copy, NS_NONATOMIC_IOSONLY) NSString *fileType API_AVAILABLE(macos(10.11), ios(7.0), tvos(9.0), watchos(2.0), visionos(1.0));

/**************************** Rendering/layout properties ****************************/

/// An instance of the relevant image class that represents the contents of the text attachment object.
///
/// For details about using the
/// <doc://com.apple.documentation/documentation/uikit/uiimage> class to create
/// text attachments that automatically adjust to surrounding font and color
/// attributes, see the
/// <doc://com.apple.documentation/documentation/uikit/NSTextAttachment/init(image:)>
/// initializer.
///
/// Modifying this property has the side effect of invalidating the
/// ``NSTextAttachment/contents``, ``NSTextAttachment/fileType``, and
/// ``NSTextAttachment/fileWrapper`` properties.
@property (nullable, strong, NS_NONATOMIC_IOSONLY) UIImage *image API_AVAILABLE(macos(10.11), ios(7.0), tvos(9.0), watchos(2.0), visionos(1.0));

/// The layout bounds of the text attachment's graphical representation in the text coordinate system.
///
/// The bounds rectangle origin is at the current glyph location on the text
/// baseline. The default value is
/// <doc://com.apple.documentation/documentation/coregraphics/cgrectzero>.
@property (NS_NONATOMIC_IOSONLY) CGRect bounds API_AVAILABLE(macos(10.11), ios(7.0), tvos(9.0), watchos(2.0), visionos(1.0));

/**************************** Non-image contents properties ****************************/

/// The text attachment's file wrapper.
///
/// The file wrapper holds the contents of the attached file. Modifying this
/// property has a side effect of invalidating the ``NSTextAttachment/image``,
/// ``NSTextAttachment/contents``, and ``NSTextAttachment/fileType`` properties.
@property (nullable, strong, NS_NONATOMIC_IOSONLY) NSFileWrapper *fileWrapper;


#pragma mark Advanced Layout Properties
/// The layout padding before and after the text attachment bounds.
///
/// The layout and rendering bounds X origin is inset by the padding value. This
/// affects the relationship between the text attachment bounds and
/// `NSLayoutManager` glyph metrics methods
/// ``NSLayoutManager/location(forGlyphAt:)`` and
/// ``NSLayoutManager/attachmentSize(forGlyphAt:)``. The default value is `0.0`.
@property CGFloat lineLayoutPadding API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0), watchos(8.0), visionos(1.0));


#pragma mark View-based attachments
/// Returns the text attachment view provider class, if any, for the file type you specify.
///
/// - Parameters:
///   - fileType: A <doc://com.apple.documentation/documentation/swift/string> that represents the file type.
///
/// - Returns: The text attachment view provider class, or `nil` if there is no class for the specified file type.
+ (nullable Class)textAttachmentViewProviderClassForFileType:(NSString *)fileType API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0), visionos(1.0)) API_UNAVAILABLE(watchos);

/// Registers a specific file type with the attachment view provider.
///
/// - Parameters:
///   - textAttachmentViewProviderClass: The text attachment view provider class.
///   - fileType: A <doc://com.apple.documentation/documentation/swift/string> that represents the file type.
+ (void)registerTextAttachmentViewProviderClass:(Class)textAttachmentViewProviderClass forFileType:(NSString *)fileType API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0), visionos(1.0)) API_UNAVAILABLE(watchos);

/// A Boolean value that indicates whether the text attachment tries to use a text attachment view provider.
///
/// When `true`, the text attachment tries to use a view provider returned by
/// ``NSTextAttachmentLayout/viewProvider(for:location:textContainer:)``.
/// Default is `true`.
@property BOOL allowsTextAttachmentView API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0), visionos(1.0)) API_UNAVAILABLE(watchos);

/// A Boolean value that indicates whether the text attachment is configured to use text attachment view providers.
///
/// The default implementation of this property checks
/// ``NSTextAttachment/allowsTextAttachmentView``,
/// ``textAttachmentViewProviderClassForFileType:``, and ``contents``.
@property (readonly) BOOL usesTextAttachmentView API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0), visionos(1.0)) API_UNAVAILABLE(watchos);
@end

@interface NSAttributedString (NSAttributedStringAttachmentConveniences)
/// Returns an attributed string containing the specified attachment using `NSAttachmentCharacter` as the base character.
+ (NSAttributedString *)attributedStringWithAttachment:(NSTextAttachment *)attachment API_AVAILABLE(macos(10.0), ios(7.0), tvos(9.0), watchos(2.0), visionos(1.0));

/// Returns an attributed string containing the specified attachment with attributes using `NSAttachmentCharacter` as the base character.
+ (instancetype)attributedStringWithAttachment:(NSTextAttachment *)attachment attributes:(NSDictionary<NSAttributedStringKey, id> *)attributes API_AVAILABLE(macos(15.0), ios(18.0), tvos(18.0), watchos(11.0), visionos(2.0));
@end

/// A container object that associates a text attachment at a particular document location with a view object.
///
/// Use `NSTextAttachmentViewProvider` when you need to represent document
/// locations in terms of an ``NSTextLocation`` or an ``NSTextRange`` or you
/// want to support view-based text attachments. The view provider controls the
/// view placement and layout without requiring view classes to be aware of the
/// text attachment coordination using a ``NSTextLayoutManager`` in macOS 12 or
/// iOS 15 and later.
API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0), visionos(1.0)) API_UNAVAILABLE(watchos)
@interface NSTextAttachmentViewProvider : NSObject
/// Creates a new text attachment view whose content starts at the location you provide.
///
/// - Parameters:
///   - textAttachment: The ``NSTextAttachment`` for this view.
///   - parentView: The parent view of this attachment.
///   - textLayoutManager: The ``NSTextLayoutManager`` for this view.
///   - location: The ``NSTextLocation`` that identifies the start of the text.
- (instancetype)initWithTextAttachment:(NSTextAttachment *)textAttachment parentView:(nullable UIView *)parentView textLayoutManager:(nullable NSTextLayoutManager *)textLayoutManager location:(id <NSTextLocation>)location NS_DESIGNATED_INITIALIZER;

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

/// The text attachment for this view.
///
/// Specify the value of this property at initialization time using the
/// ``NSTextAttachmentViewProvider/init(textAttachment:parentView:textLayoutManager:location:)``
/// initializer.
@property (readonly, weak) NSTextAttachment *textAttachment;

/// The text layout manager for this view.
///
/// Specify the value of this property at initialization time using the
/// ``NSTextAttachmentViewProvider/init(textAttachment:parentView:textLayoutManager:location:)``
/// initializer.
@property (readonly, weak, nullable) NSTextLayoutManager *textLayoutManager;

/// The location that indicates the start of the text attachment.
///
/// Specify the value of this property at initialization time using the
/// ``NSTextAttachmentViewProvider/init(textAttachment:parentView:textLayoutManager:location:)``
/// initializer.
@property (readonly, strong) id <NSTextLocation> location;

// View instantiation
/// The text attachment's view.
///
/// The getter first invokes ``loadView`` if the view hasn't been set yet.
///
/// > Important: Subclasses must call the superclass implementation if they
///   override the setter or getter.
@property(nullable, strong) UIView *view;

/// Creates the custom view hierarchy for this attachment.
///
/// Use this method to create a custom view hierarchy. Don't call this method
/// directly; the framework calls it at the appropriate time.
- (void)loadView;

/// A Boolean value that determines the text attachment's bounds policy.
///
/// If `true`, the framework calls the `textAttachment` property's
/// ``NSTextAttachmentViewProvider/attachmentBounds(for:location:textContainer:proposedLineFragment:position:)``
/// method and examines the text attachment view provider to determine the
/// bounds instead of using the `bounds` property of this instance. Defaults to
/// `false`.
@property BOOL tracksTextAttachmentViewBounds;

/// Returns the layout bounds for an attachment at a specific text location that contains the text attributes you specify.
///
/// - Parameters:
///   - attributes: A dictionary that contains a list of key and attribute pairs that describe the customization of the string.
///   - location: An ``NSTextLocation`` that indicates the location of the attachment inside the document.
///   - textContainer: The ``NSTextContainer`` that defines the area to fill in with text.
///   - proposedLineFragment: A <doc://com.apple.documentation/documentation/corefoundation/cgrect> that describes the boundaries of the line fragment.
///   - position: A <doc://com.apple.documentation/documentation/corefoundation/cgpoint> inside `proposedLineFragment`.
///
/// - Returns: A <doc://com.apple.documentation/documentation/corefoundation/cgrect> that describes the bounds of the attachment.
- (CGRect)attachmentBoundsForAttributes:(NSDictionary<NSAttributedStringKey, id> *)attributes location:(id <NSTextLocation>)location textContainer:(nullable NSTextContainer *)textContainer proposedLineFragment:(CGRect)proposedLineFragment position:(CGPoint)position;
@end


// This protocol defines the interface to attachment objects from NSLayoutManager
API_AVAILABLE(macos(10.11), ios(7.0), tvos(9.0), visionos(1.0)) API_UNAVAILABLE(watchos)
@protocol NSTextAttachmentContainer <NSObject>
// This protocol is available only for Objective-C 2 or later architecture

// Returns the image object rendered by NSLayoutManager at imageBounds inside textContainer.  It should return an image appropriate for the target rendering context derived by arguments to this method.  The NSTextAttachment implementation returns -image when non-nil.  If -image==nil, it returns an image based on -contents and -fileType properties.
- (nullable UIImage *)imageForBounds:(CGRect)imageBounds textContainer:(nullable NSTextContainer *)textContainer characterIndex:(NSUInteger)charIndex  API_AVAILABLE(macos(10.11), ios(7.0), tvos(9.0), visionos(1.0)) API_UNAVAILABLE(watchos);


// Returns the layout bounds to the layout manager.  The bounds origin is interpreted to match position inside lineFrag.  The NSTextAttachment implementation returns -bounds if not CGRectZero; otherwise, it derives the bounds value from -[image size].  Conforming objects can implement more sophisticated logic for negotiating the frame size based on the available container space and proposed line fragment rect.
- (CGRect)attachmentBoundsForTextContainer:(nullable NSTextContainer *)textContainer proposedLineFragment:(CGRect)lineFrag glyphPosition:(CGPoint)position characterIndex:(NSUInteger)charIndex API_AVAILABLE(macos(10.11), ios(7.0), tvos(9.0), visionos(1.0)) API_UNAVAILABLE(watchos);

@end

API_AVAILABLE(macos(10.0), ios(7.0), tvos(9.0), visionos(1.0)) API_UNAVAILABLE(watchos)
@interface NSTextAttachment(NSTextAttachment_Deprecation) <NSTextAttachmentContainer>
@end

NS_HEADER_AUDIT_END(nullability, sendability)
#else
#import <UIFoundation/NSTextAttachment.h>
#endif
