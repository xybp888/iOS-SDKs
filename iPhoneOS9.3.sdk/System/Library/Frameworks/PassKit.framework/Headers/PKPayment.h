//
//  PKPayment.h
//
//  Copyright (c) 2014 Apple, Inc. All rights reserved.
//

#import <AddressBook/ABRecord.h>
#import <PassKit/PKPaymentToken.h>

@class PKShippingMethod;
@class PKContact;

// PKPayment represents the result of a payment request.  Successful payments
// have a PKPaymentToken which contains a payment credential encrypted to the merchant
// identifier specified in the request, and when requested, the user's shipping address
// and chosen shipping method.
NS_CLASS_AVAILABLE(NA, 8_0)
@interface PKPayment : NSObject

// A PKPaymentToken which contains an encrypted payment credential.
@property (nonatomic, readonly, nonnull) PKPaymentToken *token;

// The full billing address that the user selected for this transaction.  Fields are
// constrained to those specified in the requiredBillingAddressFields property of the original
// PKPaymentRequest object.  This property is only set when the application has set
// the requiredBillingAddressFields property of the PKPaymentRequest.
@property (nonatomic, readonly, nullable) ABRecordRef billingAddress NS_DEPRECATED_IOS(8_0, 9_0, "Use billingContact instead");
@property (nonatomic, readonly, nullable) PKContact *billingContact NS_AVAILABLE_IOS(9_0);

// The full shipping address that the user selected for this transaction.  Fields are
// constrained to those specified in the requiredShippingAddressFields property of the original
// PKPaymentRequest object.  This property is only set when the application has set
// the requiredShippingAddressFields property of the PKPaymentRequest.
@property (nonatomic, readonly, nullable) ABRecordRef shippingAddress NS_DEPRECATED_IOS(8_0, 9_0, "Use shippingContact instead");;
@property (nonatomic, readonly, nullable) PKContact *shippingContact NS_AVAILABLE_IOS(9_0);

// The shipping method that the user chose.  This property is only set when the
// application has set the shippingMethods property of the PKPaymentRequest.
@property (nonatomic, readonly, nullable) PKShippingMethod *shippingMethod;

@end

