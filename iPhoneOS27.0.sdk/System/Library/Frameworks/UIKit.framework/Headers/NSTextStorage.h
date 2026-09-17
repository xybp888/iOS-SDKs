#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIFoundation/NSTextStorage.h>)
//
//  NSTextStorage.h
//  Text Kit
//
//  Copyright (c) 1994-2025, Apple Inc. All rights reserved.
//

#import <Foundation/NSObject.h>
#import <Foundation/NSNotification.h>
#import <UIKit/UIKitDefines.h>
#import <UIKit/NSAttributedString.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

@class NSArray, NSLayoutManager, NSNotification;

@protocol NSTextStorageDelegate;
@protocol NSTextStorageObserving;

typedef NS_OPTIONS(NSUInteger, NSTextStorageEditActions) {
    NSTextStorageEditedAttributes API_AVAILABLE(macos(10.0), ios(7.0), tvos(9.0), visionos(1.0)) API_UNAVAILABLE(watchos) = (1 << 0),
    NSTextStorageEditedCharacters API_AVAILABLE(macos(10.0), ios(7.0), tvos(9.0), visionos(1.0)) API_UNAVAILABLE(watchos) = (1 << 1)
} API_AVAILABLE(macos(10.11), ios(7.0), tvos(9.0), visionos(1.0)) API_UNAVAILABLE(watchos)
NS_SWIFT_NAME(NSTextStorage.EditActions)
;

/// The fundamental storage mechanism of TextKit that contains the text managed by the system.
///
/// `NSTextStorage` is a semi-abstract subclass of `NSMutableAttributedString`.
/// It implements change management (`beginEditing`/`endEditing`), verification
/// of attributes, delegate handling, and layout management notification. The one
/// aspect it does not implement is the actual attributed string storage — this
/// is left up to subclassers, which need to override the two
/// `NSMutableAttributedString` primitives in addition to two
/// `NSAttributedString` primitives:
///
/// - `-string`
/// - `-attributesAtIndex:effectiveRange:`
/// - `-replaceCharactersInRange:withString:`
/// - `-setAttributes:range:`
///
/// These primitives should perform the change then call
/// `edited:range:changeInLength:` to get everything else to happen.
UIKIT_EXTERN API_AVAILABLE(macos(10.0), ios(7.0), tvos(9.0), visionos(1.0)) API_UNAVAILABLE(watchos)
@interface NSTextStorage : NSMutableAttributedString <NSSecureCoding>
/**************************** Pending edit info ****************************/

/// A mask that describes the kinds of edits pending for the text storage object.
@property (readonly, NS_NONATOMIC_IOSONLY) NSTextStorageEditActions editedMask;

/// The range of text that contains changes.
///
/// `{NSNotFound, 0}` when there is no pending changes.
@property (readonly, NS_NONATOMIC_IOSONLY) NSRange editedRange;

/// The difference between the current length of the edited range and its length before editing.
@property (readonly, NS_NONATOMIC_IOSONLY) NSInteger changeInLength;


/**************************** Delegate ****************************/

/// The delegate for the text storage object.
@property (nullable, weak, NS_NONATOMIC_IOSONLY) id <NSTextStorageDelegate> delegate;


/**************************** Edit management ****************************/

/// Tracks changes made to the text storage object, allowing the text storage to record the full extent of changes.
///
/// If there are no outstanding `beginEditing` calls, this method calls
/// ``processEditing`` to trigger post-editing processes. This method has to be
/// called by the primitives after changes are made if subclassed and overridden.
/// `editedRange` is the range in the original string (before the edit).
///
/// - Parameters:
///   - editedMask: The type of edit (attributes, characters, or both).
///   - editedRange: The range in the original string before the edit.
///   - delta: The change in length resulting from the edit.
- (void)edited:(NSTextStorageEditActions)editedMask range:(NSRange)editedRange changeInLength:(NSInteger)delta;

/// Sends out delegate notifications, fixes the attributes, and notifies text storage observer of the change.
///
/// Sends `-textStorage:willProcessEditing`, fixes the attributes, sends
/// `-textStorage:didProcessEditing`, and notifies the text storage observer of change
/// with `-processEditingForTextStorage:edited:range:changeInLength:invalidatedRange:`.
/// Invoked from ``edited:range:changeInLength:`` or `endEditing`.
- (void)processEditing;


/**************************** Attribute fixing ****************************/

/// A Boolean value that indicates whether the receiver fixes invalidated attributes lazily.
///
/// The concrete UIKit subclass fixes attributes lazily by default. The abstract
/// class (hence, all custom subclasses) is not lazy.
@property (readonly, NS_NONATOMIC_IOSONLY) BOOL fixesAttributesLazily;

/// Notes the range of attributes that requires validation.
///
/// If the `NSTextStorage` is not lazy this just calls
/// `fixAttributesInRange:`. If it is lazy this instead just records the range
/// needing fixing in order to do it later.
///
/// - Parameters:
///   - range: The range of attributes to invalidate.
- (void)invalidateAttributesInRange:(NSRange)range;

/// Ensures all attributes in the range are validated and ready to be used.
///
/// A lazy `NSTextStorage` is required to call this method before accessing any
/// attributes. This gives the attribute fixing a chance to occur if necessary.
/// Subclasses that wish to support laziness must call it from all attribute
/// accessors that they implement.
///
/// - Parameters:
///   - range: The range to ensure attributes are fixed in.
- (void)ensureAttributesAreFixedInRange:(NSRange)range;

/**************************** NSTextStorageObserving ****************************/
/// An object conforming to `NSTextStorageObserving` that observes and retains the text storage.
@property (nullable, weak, NS_NONATOMIC_IOSONLY) id <NSTextStorageObserving> textStorageObserver API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0)) API_UNAVAILABLE(watchos);
@end


/// The optional methods that delegates of text storage objects implement.
API_AVAILABLE(macos(10.11), ios(7.0), tvos(9.0), visionos(1.0)) API_UNAVAILABLE(watchos)
@protocol NSTextStorageDelegate <NSObject>
@optional

/// Sent inside `processEditing` right before fixing attributes.
///
/// Delegates can change the characters or attributes.
- (void)textStorage:(NSTextStorage *)textStorage willProcessEditing:(NSTextStorageEditActions)editedMask range:(NSRange)editedRange changeInLength:(NSInteger)delta API_AVAILABLE(macos(10.11), ios(7.0), tvos(9.0), visionos(1.0)) API_UNAVAILABLE(watchos);

/// Sent inside `processEditing` right before notifying text storage observer.
///
/// Delegates can change the attributes.
- (void)textStorage:(NSTextStorage *)textStorage didProcessEditing:(NSTextStorageEditActions)editedMask range:(NSRange)editedRange changeInLength:(NSInteger)delta API_AVAILABLE(macos(10.11), ios(7.0), tvos(9.0), visionos(1.0)) API_UNAVAILABLE(watchos);

@end

/**** Notifications ****/

UIKIT_EXTERN NSNotificationName  const NSTextStorageWillProcessEditingNotification API_AVAILABLE(macos(10.0), ios(7.0), tvos(9.0), visionos(1.0)) API_UNAVAILABLE(watchos);
UIKIT_EXTERN NSNotificationName  const NSTextStorageDidProcessEditingNotification API_AVAILABLE(macos(10.0), ios(7.0), tvos(9.0), visionos(1.0)) API_UNAVAILABLE(watchos);

#pragma mark NSTextStorageObserving
/// A protocol that defines the interface for objects observing changes in the text backing-store.
API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0)) API_UNAVAILABLE(watchos)
@protocol NSTextStorageObserving <NSObject>
/// The document text storage object.
@property (nullable, strong, NS_NONATOMIC_IOSONLY) NSTextStorage *textStorage;

/// Notifies the observer that the text storage has been edited.
///
/// The `newCharRange` is the range in the final string which was explicitly
/// edited. The `invalidatedRange` includes portions that changed as a result of
/// attribute fixing — it is either equal to `newCharRange` or larger.
/// Controllers should not change the contents of the text storage during the
/// execution of this message.
///
/// - Parameters:
///   - textStorage: The text storage that was edited.
///   - editMask: The type of edit.
///   - newCharRange: The range of characters that changed.
///   - delta: The change in length.
///   - invalidatedCharRange: The full invalidated range including attribute fixing.
- (void)processEditingForTextStorage:(NSTextStorage *)textStorage edited:(NSTextStorageEditActions)editMask range:(NSRange)newCharRange changeInLength:(NSInteger)delta invalidatedRange:(NSRange)invalidatedCharRange;

/// Performs an editing transaction on the text storage.
///
/// - Parameters:
///   - textStorage: The text storage.
///   - transaction: The block to execute within the transaction.
- (void)performEditingTransactionForTextStorage:(NSTextStorage *)textStorage usingBlock:(void (NS_NOESCAPE ^) (void))transaction;
@end

/**************************** Layout Manager  ****************************/
API_AVAILABLE(macos(10.0), ios(7.0), tvos(9.0), visionos(1.0)) API_UNAVAILABLE(watchos)
@interface NSTextStorage (NSTextStorage_NSLayoutManagerInterface)

// NSLayoutManager objects owned by the receiver.
@property (readonly, copy, NS_NONATOMIC_IOSONLY) NSArray<NSLayoutManager *> *layoutManagers;

// Adds aLayoutManager to the receiver.  Sends -[NSLayoutManager setTextStorage:] to aLayoutManager with the receiver.
- (void)addLayoutManager:(NSLayoutManager *)aLayoutManager;

// Removes aLayoutManager from the receiver if already owned by it.  Sends -[NSLayoutManager setTextStorage:] to aLayoutManager with nil.
- (void)removeLayoutManager:(NSLayoutManager *)aLayoutManager;
@end

NS_HEADER_AUDIT_END(nullability, sendability)
#else
#import <UIFoundation/NSTextStorage.h>
#endif
