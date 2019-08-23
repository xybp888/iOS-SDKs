//
//  UIAccessibilityCustomRotor.h
//  UIKit
//
//  Copyright (c) 2016 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UITextInput.h>

/*
 UIAccessibilityCustomRotor
 
 Assistive technologies, like VoiceOver, use a context sensitive function to provide more power
 and flexibility to perform actions and searches. This is called "The Rotor."
 
 An element (or an element in the ancestor hierarchy) can expose an array of custom rotors
 that a user can activate to search for other instances of like minded elements. This can also
 be applied to ranges within elements.
 
 As an example, in a magazine app, a custom rotor can be created to allow the user to find the next link or heading within an article.
 Alternatively, in a document editor, the next misspelled word can be found by returning the next range that contains a misspelled word.
 */

NS_ASSUME_NONNULL_BEGIN

@class UIAccessibilityCustomRotor, UIAccessibilityCustomRotorItemResult, UIAccessibilityCustomRotorSearchPredicate;

typedef NS_ENUM(NSInteger, UIAccessibilityCustomRotorDirection) {
    UIAccessibilityCustomRotorDirectionPrevious NS_ENUM_AVAILABLE_IOS(10_0),
    UIAccessibilityCustomRotorDirectionNext NS_ENUM_AVAILABLE_IOS(10_0),
};

typedef UIAccessibilityCustomRotorItemResult *_Nullable(^UIAccessibilityCustomRotorSearch)(UIAccessibilityCustomRotorSearchPredicate *predicate);

// Create the array of UIAccessibilityCustomRotors and set it on the target element or ancestor element to which it applies.
@interface NSObject (UIAccessibilityCustomRotor)
@property (nonatomic, retain, nullable) NSArray<UIAccessibilityCustomRotor *> *accessibilityCustomRotors NS_AVAILABLE_IOS(10_0);
@end

// UIAccessibilityCustomRotorSearchPredicate is a container for search parameters.
// It should be examined to determine the next matching UIAccessibilityCustomRotorItemResult.
NS_CLASS_AVAILABLE_IOS(10_0) @interface UIAccessibilityCustomRotorSearchPredicate : NSObject
@property (nonatomic, retain) UIAccessibilityCustomRotorItemResult *currentItem;
@property (nonatomic) UIAccessibilityCustomRotorDirection searchDirection;
@end

NS_CLASS_AVAILABLE_IOS(10_0) @interface UIAccessibilityCustomRotor : NSObject

- (instancetype)initWithName:(NSString *)name itemSearchBlock:(UIAccessibilityCustomRotorSearch)itemSearchBlock;

// The localized name the assistive technology will use to describe the custom rotor.
@property (nonatomic, copy) NSString *name;

// A block that takes a UIAccessibilityCustomRotorItemResult and the search direction and returns the next/previous instance of that rotor item.
// If the currentItem is nil, that implies the first/last item should be returned.
@property (nonatomic, copy) UIAccessibilityCustomRotorSearch itemSearchBlock;

@end

NS_CLASS_AVAILABLE_IOS(10_0) @interface UIAccessibilityCustomRotorItemResult : NSObject

- (instancetype)initWithTargetElement:(id<NSObject>)targetElement targetRange:(nullable UITextRange *)targetRange;

// A UIAccessibilityCustomRotorItemResult references a real element that will be messaged for other accessibility properties.
@property (nonatomic, weak) id<NSObject> targetElement;

// Optionally, a target range can be used to search within an element (like a UITextView).
// If targetRange is nil, the search should begin from the start/end of the element depending on the search direction.
@property (nullable, nonatomic, retain) UITextRange *targetRange;

@end

NS_ASSUME_NONNULL_END
