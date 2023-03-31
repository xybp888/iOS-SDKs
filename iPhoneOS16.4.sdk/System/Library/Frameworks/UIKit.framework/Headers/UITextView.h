#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UITextView.h>)
//
//  UITextView.h
//  UIKit
//
//  Copyright (c) 2007-2018 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreGraphics/CoreGraphics.h>
#import <UIKit/UIFindInteraction.h>
#import <UIKit/UIScrollView.h>
#import <UIKit/UIStringDrawing.h>
#import <UIKit/UITextDragging.h>
#import <UIKit/UITextDropping.h>
#import <UIKit/UITextInput.h>
#import <UIKit/UITextSearching.h>
#import <UIKit/UIKitDefines.h>
#import <UIKit/UIDataDetectors.h>
#import <UIKit/UITextItemInteraction.h>
#import <UIKit/UIContentSizeCategoryAdjusting.h>
#import <UIKit/UITextPasteConfigurationSupporting.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

@class UIFindInteraction, UIFont, UIColor, UIMenu, UIMenuElement, UITextView, NSTextContainer, NSTextLayoutManager, NSLayoutManager, NSTextStorage, NSTextAttachment;
@protocol UIEditMenuInteractionAnimating;

NS_SWIFT_UI_ACTOR
@protocol UITextViewDelegate <NSObject, UIScrollViewDelegate>

@optional

- (BOOL)textViewShouldBeginEditing:(UITextView *)textView;
- (BOOL)textViewShouldEndEditing:(UITextView *)textView;

- (void)textViewDidBeginEditing:(UITextView *)textView;
- (void)textViewDidEndEditing:(UITextView *)textView;

- (BOOL)textView:(UITextView *)textView shouldChangeTextInRange:(NSRange)range replacementText:(NSString *)text;
- (void)textViewDidChange:(UITextView *)textView;

- (void)textViewDidChangeSelection:(UITextView *)textView;

- (BOOL)textView:(UITextView *)textView shouldInteractWithURL:(NSURL *)URL inRange:(NSRange)characterRange interaction:(UITextItemInteraction)interaction API_AVAILABLE(ios(10.0));
- (BOOL)textView:(UITextView *)textView shouldInteractWithTextAttachment:(NSTextAttachment *)textAttachment inRange:(NSRange)characterRange interaction:(UITextItemInteraction)interaction API_AVAILABLE(ios(10.0));

- (BOOL)textView:(UITextView *)textView shouldInteractWithURL:(NSURL *)URL inRange:(NSRange)characterRange API_DEPRECATED_WITH_REPLACEMENT("textView:shouldInteractWithURL:inRange:interaction:", ios(7.0, 10.0));
- (BOOL)textView:(UITextView *)textView shouldInteractWithTextAttachment:(NSTextAttachment *)textAttachment inRange:(NSRange)characterRange API_DEPRECATED_WITH_REPLACEMENT("textView:shouldInteractWithTextAttachment:inRange:interaction:", ios(7.0, 10.0));

/**
 * @abstract Asks the delegate for the menu to be shown for the specified text range.
 *
 * @param textView                     The text view requesting the menu.
 * @param range                            The text range for which the menu is presented for.
 * @param suggestedActions   The actions and commands that the system suggests.
 *
 * @return Return a UIMenu describing the desired menu hierarchy. Return @c nil to present the default system menu.
 */
- (nullable UIMenu *)textView:(UITextView *)textView editMenuForTextInRange:(NSRange)range suggestedActions:(NSArray<UIMenuElement *> *)suggestedActions API_AVAILABLE(ios(16.0));

/**
 * @abstract Called when the text view is about to present the edit menu.
 *
 * @param textView      The text view displaying the menu.
 * @param animator      Appearance animator. Add animations to this object to run them alongside the appearance transition.
 */
- (void)textView:(UITextView *)textView willPresentEditMenuWithAnimator:(id<UIEditMenuInteractionAnimating>)animator API_AVAILABLE(ios(16.0)) API_UNAVAILABLE(tvos, watchos);

/**
 * @abstract Called when the text view is about to dismiss the edit menu.
 *
 * @param textView      The text view displaying the menu.
 * @param animator      Dismissal animator. Add animations to this object to run them alongside the dismissal transition.
 */
- (void)textView:(UITextView *)textView willDismissEditMenuWithAnimator:(id<UIEditMenuInteractionAnimating>)animator API_AVAILABLE(ios(16.0)) API_UNAVAILABLE(tvos, watchos);

@end

UIKIT_EXTERN API_AVAILABLE(ios(2.0)) NS_SWIFT_UI_ACTOR
@interface UITextView : UIScrollView <UITextInput, UIContentSizeCategoryAdjusting>

@property(nullable,nonatomic,weak) id<UITextViewDelegate> delegate;

@property(null_resettable,nonatomic,copy) NSString *text;
@property(nullable,nonatomic,strong) UIFont *font;
@property(nullable,nonatomic,strong) UIColor *textColor;
@property(nonatomic) NSTextAlignment textAlignment;    // default is NSLeftTextAlignment
@property(nonatomic) NSRange selectedRange;
@property(nonatomic,getter=isEditable) BOOL editable API_UNAVAILABLE(tvos);
@property(nonatomic,getter=isSelectable) BOOL selectable API_AVAILABLE(ios(7.0)); // toggle selectability, which controls the ability of the user to select content and interact with URLs & attachments. On tvOS this also makes the text view focusable.
@property(nonatomic) UIDataDetectorTypes dataDetectorTypes API_AVAILABLE(ios(3.0)) API_UNAVAILABLE(tvos);

@property(nonatomic) BOOL allowsEditingTextAttributes API_AVAILABLE(ios(6.0)); // defaults to NO
@property(null_resettable,copy) NSAttributedString *attributedText API_AVAILABLE(ios(6.0));
@property(nonatomic,copy) NSDictionary<NSAttributedStringKey, id> *typingAttributes API_AVAILABLE(ios(6.0)); // automatically resets when the selection changes

- (void)scrollRangeToVisible:(NSRange)range;


// Presented when object becomes first responder.  If set to nil, reverts to following responder chain.  If
// set while first responder, will not take effect until reloadInputViews is called.
@property (nullable, readwrite, strong) UIView *inputView;             
@property (nullable, readwrite, strong) UIView *inputAccessoryView;

@property(nonatomic) BOOL clearsOnInsertion API_AVAILABLE(ios(6.0)); // defaults to NO. if YES, the selection UI is hidden, and inserting text will replace the contents of the field. changing the selection will automatically set this to NO.

// Create a new text view with the specified text container (can be nil).
// This initializer will follow the NSTextContainer's usage of TextKit 2 (NSTextLayoutManager) or TextKit 1 (NSLayoutManager).
// If a nil NSTextContainer is specified, TextKit 2 will be used.
- (instancetype)initWithFrame:(CGRect)frame textContainer:(nullable NSTextContainer *)textContainer API_AVAILABLE(ios(7.0)) NS_DESIGNATED_INITIALIZER;

// From iOS 16 onwards, UITextViews are, by default, created with a TextKit 2 NSTextLayoutManager managing text layout (see the .textLayoutManager property). They will dynamically 'fall back' to a TextKit 1 NSLayoutManager if TextKit 1 features are used (notably, if the .layoutManager property is accessed).
// This convenience initializer can be used to specify TextKit 1 by default if you know code in your app relies on that. This avoids inefficiencies associated with the needless creation of a NSTextLayoutManager and the subsequent fallback.
+ (instancetype)textViewUsingTextLayoutManager:(BOOL)usingTextLayoutManager API_AVAILABLE(ios(16.0), tvos(16.0));

- (nullable instancetype)initWithCoder:(NSCoder *)coder NS_DESIGNATED_INITIALIZER;

// Get the text container for the text view
@property(nonatomic, readonly) NSTextContainer *textContainer API_AVAILABLE(ios(7.0));
// Inset the text container's layout area within the text view's content area
@property(nonatomic, assign) UIEdgeInsets textContainerInset API_AVAILABLE(ios(7.0));

// This property accesses the TextKit 2 NSTextLayoutManager. You should generally prefer to use it over the TextKit 1 .layoutManager property if it exists. This property will return nil if TextKit 1 is in use.
@property(nonatomic, nullable, readonly) NSTextLayoutManager *textLayoutManager API_AVAILABLE(ios(16.0), tvos(16.0));

// To ensure compatibility with older code, accessing the .layoutManager of a UITextView - or its .textContainer's .layoutManager - will cause a UITextView that's using TextKit 2 to 'fall back' to TextKit 1, and return a newly created NSLayoutManager. After this happens, .textLayoutManager will return nil - and _any TextKit 2 objects you may have cached will cease functioning_. Be careful about this if you are intending to be using TextKit 2!
@property(nonatomic, readonly) NSLayoutManager *layoutManager API_AVAILABLE(ios(7.0));

// The textual contents of the text view.
@property(nonatomic, readonly, strong) NSTextStorage *textStorage API_AVAILABLE(ios(7.0));

// Style for links
@property(null_resettable, nonatomic, copy) NSDictionary<NSAttributedStringKey,id> *linkTextAttributes API_AVAILABLE(ios(7.0));

// When turned on, this changes the rendering scale of the text to match the standard text scaling and preserves the original font point sizes when the contents of the text view are copied to the pasteboard.  Apps that show a lot of text content, such as a text viewer or editor, should turn this on and use the standard text scaling.
@property (nonatomic) BOOL usesStandardTextScaling API_AVAILABLE(ios(13.0));

/// If `findInteractionEnabled` is set to true, returns this text view's built-in find interaction. Otherwise, nil.
@property (nonatomic, nullable, readonly) UIFindInteraction *findInteraction API_AVAILABLE(ios(16.0)) API_UNAVAILABLE(watchos, tvos);

/// Enables this text view's built-in find interaction.
@property (nonatomic, readwrite, getter=isFindInteractionEnabled) BOOL findInteractionEnabled API_AVAILABLE(ios(16.0)) API_UNAVAILABLE(watchos, tvos);

@end

#if TARGET_OS_IOS

@interface UITextView () <UITextDraggable, UITextDroppable, UITextPasteConfigurationSupporting, UIFindInteractionDelegate, UITextSearching>
@end

#endif

@interface UITextView (UIInteractionStateRestorable)

// Note that the interaction state of a UITextView does _not_ encode the
// textual content of the field. It should be saved separately, and restored
// _before_ the interaction state.
// Currently, this encodes selection (and/or cursor position), scroll position,
// and first responder status.
// The object returned here will be a plist type, so can e.g. be stored in
// an NSUserActivity's userInfo dictionary.
@property (nonatomic, copy) id interactionState API_AVAILABLE(ios(15.0));

@end

UIKIT_EXTERN NSNotificationName const UITextViewTextDidBeginEditingNotification;
UIKIT_EXTERN NSNotificationName const UITextViewTextDidChangeNotification;
UIKIT_EXTERN NSNotificationName const UITextViewTextDidEndEditingNotification;

NS_HEADER_AUDIT_END(nullability, sendability)

#else
#import <UIKitCore/UITextView.h>
#endif
