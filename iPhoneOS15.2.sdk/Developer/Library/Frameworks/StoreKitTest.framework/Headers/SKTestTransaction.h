//
//  SKTestTransaction.h
//  StoreKitTest
//
//  Copyright © 2020 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <StoreKit/StoreKit.h>

NS_ASSUME_NONNULL_BEGIN

SK_EXTERN_CLASS API_AVAILABLE(ios(14.0), macos(11.0), tvos(14.0), watchos(7.0))
@interface SKTestTransaction : NSObject

@property(nonatomic, readonly) BOOL autoRenewingEnabled;

@property(nonatomic, readonly, nullable) NSDate *cancelDate;

@property(nonatomic, readonly, nullable) NSDate *expirationDate;

@property(nonatomic, readonly) BOOL hasPurchaseIssue;

@property(nonatomic, readonly) NSUInteger identifier;

@property(nonatomic, readonly) NSUInteger originalTransactionIdentifier;

@property(nonatomic, readonly) BOOL pendingAskToBuyConfirmation;

@property(nonatomic, readonly) NSString *productIdentifier;

@property(nonatomic, readonly) NSDate *purchaseDate;

@property(nonatomic, readonly) SKPaymentTransactionState state;

@end

NS_ASSUME_NONNULL_END
