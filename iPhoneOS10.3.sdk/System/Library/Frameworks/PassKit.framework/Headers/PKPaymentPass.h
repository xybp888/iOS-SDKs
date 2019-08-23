//
//  PKPaymentPass.h
//  PassKit
//
//  Copyright (c) 2014 Apple, Inc. All rights reserved.
//

#ifndef __PKPAYMENTPASS_H
#define __PKPAYMENTPASS_H

#import <PassKit/PKPass.h>

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSUInteger, PKPaymentPassActivationState) {
    PKPaymentPassActivationStateActivated,
    PKPaymentPassActivationStateRequiresActivation,
    PKPaymentPassActivationStateActivating,
    PKPaymentPassActivationStateSuspended,
    PKPaymentPassActivationStateDeactivated
} NS_ENUM_AVAILABLE_IOS(8_0);


NS_CLASS_AVAILABLE_IOS(8_0)
@interface PKPaymentPass : PKPass

@property (nonatomic, copy, readonly) NSString *primaryAccountIdentifier;
@property (nonatomic, copy, readonly) NSString *primaryAccountNumberSuffix;
@property (weak, readonly) NSString *deviceAccountIdentifier;
@property (weak, readonly) NSString *deviceAccountNumberSuffix;
@property (nonatomic, readonly) PKPaymentPassActivationState activationState;

@end
NS_ASSUME_NONNULL_END

#endif // End __PKPAYMENTPASS_H
