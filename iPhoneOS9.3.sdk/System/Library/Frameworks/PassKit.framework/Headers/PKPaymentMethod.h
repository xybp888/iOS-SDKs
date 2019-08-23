//
//  PKPaymentMethod.h
//
//  Copyright © 2015 Apple, Inc. All rights reserved.
//

#ifndef __PKPAYMENTMETHOD_H
#define __PKPAYMENTMETHOD_H

#import <Foundation/Foundation.h>

@class PKPaymentPass;

NS_ASSUME_NONNULL_BEGIN
NS_CLASS_AVAILABLE(NA, 9_0)
@interface PKPaymentMethod : NSObject

typedef NS_OPTIONS(NSUInteger, PKPaymentMethodType) {
    PKPaymentMethodTypeUnknown = 0,
    PKPaymentMethodTypeDebit,
    PKPaymentMethodTypeCredit,
    PKPaymentMethodTypePrepaid,
    PKPaymentMethodTypeStore,
} NS_ENUM_AVAILABLE(NA, 9_0);

// A string describing the instrument that's suitable for display
@property (nonatomic, readonly, nullable) NSString *displayName;

// The payment network that backs the instrument. Suitable for display.
@property (nonatomic, readonly, nullable) NSString *network;

// The underlying instrument type (Credit, Debit, etc)
@property (nonatomic, readonly) PKPaymentMethodType type;

// The payment pass - will only be provided if your app is entitled to view the pass in question
@property (nonatomic, readonly, nullable) PKPaymentPass *paymentPass;

@end

NS_ASSUME_NONNULL_END

#endif

