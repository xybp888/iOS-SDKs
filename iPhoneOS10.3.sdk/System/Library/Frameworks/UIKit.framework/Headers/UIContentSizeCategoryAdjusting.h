//
//  UIContentSizeCategoryAdjusting.h
//  UIKit
//
//  Copyright (c) 2016-2016 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKitDefines.h>

NS_ASSUME_NONNULL_BEGIN

NS_CLASS_AVAILABLE_IOS(10_0) @protocol UIContentSizeCategoryAdjusting <NSObject>

/*
 Indicates whether the corresponding element should automatically update its font when the device’s UIContentSizeCategory is changed.
 For this property to take effect, the element’s font must be a font vended using +preferredFontForTextStyle: or +preferredFontForTextStyle:compatibleWithTraitCollection: with a valid UIFontTextStyle.
 */
@property (nonatomic) BOOL adjustsFontForContentSizeCategory;

@end

NS_ASSUME_NONNULL_END
