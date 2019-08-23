//
//  UIAccessibilityAdditions.h
//  UIKit
//
//  Copyright (c) 2009-2015 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKitDefines.h>
#import <UIKit/UIPickerView.h>
#import <UIKit/UIScrollView.h>

NS_ASSUME_NONNULL_BEGIN

/* 
  Optionally implement the following methods in a UIPickerView delegate
  in order to provide accessibility information per component. 
  See UIAccessibility.h for more information about hints and labels.
*/

__TVOS_PROHIBITED
@protocol UIPickerViewAccessibilityDelegate <UIPickerViewDelegate>

@optional
- (nullable NSString *)pickerView:(UIPickerView *)pickerView accessibilityLabelForComponent:(NSInteger)component;
- (nullable NSString *)pickerView:(UIPickerView *)pickerView accessibilityHintForComponent:(NSInteger)component;

@end

/*
 Provide a custom status string when VoiceOver scrolls with accessibilityScroll:
 For example, in a bookcase user interface that displays a list of books, you can implement 
 this protocol to announce "Showing books 10 through 20".
 By default, VoiceOver will announce "Page X of Y" when scrolling. 
 */
@protocol UIScrollViewAccessibilityDelegate <UIScrollViewDelegate>

@optional
- (nullable NSString *)accessibilityScrollStatusForScrollView:(UIScrollView *)scrollView;

@end

NS_ASSUME_NONNULL_END
