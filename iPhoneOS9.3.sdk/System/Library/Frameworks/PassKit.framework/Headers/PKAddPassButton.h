//
//  PKAddPassButton.h
//  PassKit
//
//  Copyright © 2015 Apple, Inc. All rights reserved.
//
#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSInteger, PKAddPassButtonStyle) {
    PKAddPassButtonStyleBlack = 0,
    PKAddPassButtonStyleBlackOutline,
} NS_ENUM_AVAILABLE_IOS(9_0);

// Use PKAddPassButton to show an "Add to Apple Wallet" button. Two types are available for barcode or payment passes.
// Refer to the Apple Pay developer documentation for more information on how to use this class
NS_CLASS_AVAILABLE_IOS(9_0) @interface PKAddPassButton : UIButton

+ (instancetype)addPassButtonWithStyle:(PKAddPassButtonStyle)addPassButtonStyle;

- (instancetype)initWithAddPassButtonStyle:(PKAddPassButtonStyle)style NS_DESIGNATED_INITIALIZER;

@property (nonatomic, assign) PKAddPassButtonStyle addPassButtonStyle UI_APPEARANCE_SELECTOR;

@end

NS_ASSUME_NONNULL_END