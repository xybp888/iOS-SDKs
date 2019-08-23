//
//  PKPaymentToken.h
//
//  Copyright (c) 2014, Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

@class PKPaymentMethod;

// Contains the user's payment credentials, encrypted to the merchant.
NS_ASSUME_NONNULL_BEGIN
NS_CLASS_AVAILABLE(NA, 8_0)
@interface PKPaymentToken : NSObject

// Describes the properties of the underlying payment instrument selected to fund the payment
@property (nonatomic, readonly) PKPaymentMethod *paymentMethod NS_AVAILABLE_IOS(9_0);

// A string that describes the payment instrument the user has selected to fund the payment.
// Suitable for display, e.g. "Amex 1234".
@property (nonatomic, readonly) NSString *paymentInstrumentName NS_DEPRECATED_IOS(8_0, 9_0, "Use paymentMethod instead");

// Payment network for the card that funds the payment.
@property (nonatomic, readonly) NSString *paymentNetwork NS_DEPRECATED_IOS(8_0, 9_0, "Use paymentMethod instead");

// A string that describes a globally unique identifier for this transaction that can be used
// for receipt purposes.
@property (nonatomic, readonly) NSString *transactionIdentifier;

// UTF-8 encoded JSON dictionary of encrypted payment data.  Ready for transmission to
// merchant's e-commerce backend for decryption and submission to a payment processor's
// gateway.
@property (nonatomic, readonly) NSData *paymentData;

@end

NS_ASSUME_NONNULL_END