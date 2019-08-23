//
//  PKPaymentButton.h
//
//  Copyright © 2014 Apple, Inc. All rights reserved.
//
#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSInteger, PKPaymentButtonStyle) {
    PKPaymentButtonStyleWhite = 0,
    PKPaymentButtonStyleWhiteOutline,
    PKPaymentButtonStyleBlack
} NS_ENUM_AVAILABLE_IOS(8_3);

typedef NS_ENUM(NSInteger, PKPaymentButtonType) {
    PKPaymentButtonTypePlain = 0,
    PKPaymentButtonTypeBuy,
    PKPaymentButtonTypeSetUp NS_ENUM_AVAILABLE_IOS(9_0)
} NS_ENUM_AVAILABLE_IOS(8_3);

// PKPaymentButton vends a number of Apple Pay related buttons for use inside of your app
// These buttons can be used to prompt the user to pay with Apple Pay, or set up cards for payment
// Refer to the Apple Pay developer documentation for more information on how to use this class
NS_CLASS_AVAILABLE(NA, 8_3) @interface PKPaymentButton : UIButton

+ (instancetype)buttonWithType:(PKPaymentButtonType)buttonType style:(PKPaymentButtonStyle)buttonStyle;

- (instancetype)initWithPaymentButtonType:(PKPaymentButtonType)type paymentButtonStyle:(PKPaymentButtonStyle)style NS_AVAILABLE_IOS(9_0) NS_DESIGNATED_INITIALIZER;

@end

NS_ASSUME_NONNULL_END