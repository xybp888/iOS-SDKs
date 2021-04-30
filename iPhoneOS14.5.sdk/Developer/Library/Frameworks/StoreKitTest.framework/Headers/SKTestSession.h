//
//  SKTestSession.h
//  StoreKitTest
//
//  Copyright © 2020 Apple Inc. All rights reserved.
//

#import <StoreKit/StoreKit.h>

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSUInteger, SKTestTimeRate) {
    SKTestTimeRateRealTime,
    SKTestTimeRateOneHourIsOneDay,
    SKTestTimeRateThirtyMinutesIsOneDay,
    SKTestTimeRateFiveMinutesIsOneDay,
    SKTestTimeRateOneMinuteIsOneDay,
    SKTestTimeRateThirtySecondsIsOneDay,
    SKTestTimeRateOneSecondIsOneDay,
} NS_SWIFT_NAME(SKTestSession.TimeRate) API_AVAILABLE(ios(14.0), macos(11.0), tvos(14.0), watchos(7.0));

@class SKTestTransaction;

SK_EXTERN_CLASS API_AVAILABLE(ios(14.0), macos(11.0), tvos(14.0), watchos(7.0))
@interface SKTestSession : NSObject


#pragma mark - Properties

// Default to NO
@property (nonatomic, assign) BOOL askToBuyEnabled;

// Default to NO
@property (nonatomic, assign) BOOL disableDialogs;

// Default to NO
@property (nonatomic, assign) BOOL failTransactionsEnabled;

// Default to NO
@property (nonatomic, assign) BOOL interruptedPurchasesEnabled;

/*
 Requires shouldFailTransactions to be set to YES
 Valid values are:
     SKErrorUnknown
     SKErrorInvalidOfferIdentifier
     SKErrorInvalidSignature
     SKErrorMissingOfferParams
     SKErrorInvalidOfferPrice
 */
@property (nonatomic, assign) SKErrorCode failureError;

// ISO 3166-1 Alpha-3 country code representation, default to USA
@property (nonatomic, copy) NSString *storefront;

// Default to en_US
@property (nonatomic, copy) NSLocale *locale;

// Default to SKTestTimeRateRealTime
@property (nonatomic, assign) SKTestTimeRate timeRate;


#pragma mark - Methods

// The filename needs to reference a .storekit file that is included in your application's bundle
- (nullable instancetype)initWithConfigurationFileNamed:(NSString *)filename error:(NSError **)error;

// The URL needs to be a file URL to a .storekit file
- (nullable instancetype)initWithContentsOfURL:(NSURL *)fileURL error:(NSError **)error NS_DESIGNATED_INITIALIZER;

- (instancetype)init NS_UNAVAILABLE;

- (NSArray<SKTestTransaction *> *)allTransactions;

- (void)clearTransactions;

- (BOOL)deleteTransactionWithIdentifier:(NSUInteger)identifier error:(NSError **)error NS_SWIFT_NAME(deleteTransaction(identifier:));

- (BOOL)expireSubscriptionWithProductIdentifier:(NSString *)productIdentifier error:(NSError **)error NS_SWIFT_NAME(expireSubscription(productIdentifier:));

- (BOOL)forceRenewalOfSubscriptionWithProductIdentifier:(NSString *)productIdentifier error:(NSError **)error NS_SWIFT_NAME(forceRenewalOfSubscription(productIdentifier:));

- (BOOL)refundTransactionWithIdentifier:(NSUInteger)identifier error:(NSError **)error NS_SWIFT_NAME(refundTransaction(identifier:));

- (BOOL)resolveIssueForTransactionWithIdentifier:(NSUInteger)identifier error:(NSError **)error NS_SWIFT_NAME(resolveIssueForTransaction(identifier:));

// Removes all property overrides and resets everything back to the default state
- (void)resetToDefaultState;


#pragma mark - Ask to Buy

- (BOOL)approveAskToBuyTransactionWithIdentifier:(NSUInteger)identifier error:(NSError **)error NS_SWIFT_NAME(approveAskToBuyTransaction(identifier:));

- (BOOL)declineAskToBuyTransactionWithIdentifier:(NSUInteger)identifier error:(NSError **)error NS_SWIFT_NAME(declineAskToBuyTransaction(identifier:));


#pragma mark - Auto-Renew

- (BOOL)disableAutoRenewForTransactionWithIdentifier:(NSUInteger)identifier error:(NSError **)error NS_SWIFT_NAME(disableAutoRenewForTransaction(identifier:));

- (BOOL)enableAutoRenewForTransactionWithIdentifier:(NSUInteger)identifier error:(NSError **)error NS_SWIFT_NAME(enableAutoRenewForTransaction(identifier:));


#pragma mark - External Transactions

- (BOOL)buyProductWithIdentifier:(NSString *)productIdentifier error:(NSError **)error NS_SWIFT_NAME(buyProduct(productIdentifier:));

@end

NS_ASSUME_NONNULL_END
