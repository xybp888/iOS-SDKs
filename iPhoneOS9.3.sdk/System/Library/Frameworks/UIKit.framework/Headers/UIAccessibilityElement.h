//
//  UIAccessibilityElement.h
//  UIAccessibility
//
//  Copyright (c) 2008-2015 Apple Inc. All rights reserved.
//

#import <CoreGraphics/CoreGraphics.h>
#import <UIKit/UIAccessibilityConstants.h>
#import <UIKit/UIAccessibilityIdentification.h>

NS_ASSUME_NONNULL_BEGIN

/*
 UIAccessibilityElement
 
 Instances of this class can be used as "fake" accessibility elements.
 An accessibility container (see UIAccessibility.h) can create and vend instances
 of UIAccessibilityElement to cover for user interface items that are not
 backed by a UIView (for example: painted text or icon).
 */

NS_CLASS_AVAILABLE_IOS(3_0) @interface UIAccessibilityElement : NSObject<UIAccessibilityIdentification>

// initialize with the accessibility container that contains this element
- (instancetype)initWithAccessibilityContainer:(id)container;

@property (nullable, nonatomic, assign) id accessibilityContainer;
@property (nonatomic, assign) BOOL isAccessibilityElement;
@property (nullable, nonatomic, strong) NSString *accessibilityLabel;
@property (nullable, nonatomic, strong) NSString *accessibilityHint;
@property (nullable, nonatomic, strong) NSString *accessibilityValue;
@property (nonatomic, assign) CGRect accessibilityFrame;
@property (nonatomic, assign) UIAccessibilityTraits accessibilityTraits;

@end

NS_ASSUME_NONNULL_END
