//
//  SKTestSession.h
//  StoreKitTest
//
//  Copyright © 2020 Apple Inc. All rights reserved.
//

#import <StoreKit/StoreKit.h>

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSInteger, SKTestTimeRate) {
    SKTestTimeRateRealTime,
    
    SKTestTimeRateOneHourIsOneDay API_DEPRECATED("Use real time or a time rate in terms of monthly renewals", ios(14.0, 15.2), macos(11.0, 12.1), tvos(14.0, 15.2), watchos(7.0, 8.3)) API_UNAVAILABLE(visionos),
    SKTestTimeRateThirtyMinutesIsOneDay API_DEPRECATED("Use real time or a time rate in terms of monthly renewals", ios(14.0, 15.2), macos(11.0, 12.1), tvos(14.0, 15.2), watchos(7.0, 8.3)) API_UNAVAILABLE(visionos),
    SKTestTimeRateFiveMinutesIsOneDay API_DEPRECATED("Use real time or a time rate in terms of monthly renewals", ios(14.0, 15.2), macos(11.0, 12.1), tvos(14.0, 15.2), watchos(7.0, 8.3)) API_UNAVAILABLE(visionos),
    SKTestTimeRateOneMinuteIsOneDay API_DEPRECATED_WITH_REPLACEMENT("SKTestTimeRateMonthlyRenewalEveryThirtyMinutes", ios(14.0, 15.2), macos(11.0, 12.1), tvos(14.0, 15.2), watchos(7.0, 8.3)) API_UNAVAILABLE(visionos),
    SKTestTimeRateThirtySecondsIsOneDay API_DEPRECATED_WITH_REPLACEMENT("SKTestTimeRateMonthlyRenewalEveryFifteenMinutes", ios(14.0, 15.2), macos(11.0, 12.1), tvos(14.0, 15.2), watchos(7.0, 8.3)) API_UNAVAILABLE(visionos),
    SKTestTimeRateOneSecondIsOneDay API_DEPRECATED_WITH_REPLACEMENT("SKTestTimeRateMonthlyRenewalEveryThirtySeconds", ios(14.0, 15.2), macos(11.0, 12.1), tvos(14.0, 15.2), watchos(7.0, 8.3)) API_UNAVAILABLE(visionos),
    
    SKTestTimeRateMonthlyRenewalEveryHour API_AVAILABLE(ios(15.2), macos(12.1), tvos(15.2), watchos(8.3), visionos(1.0)) = 10,
    SKTestTimeRateMonthlyRenewalEveryThirtyMinutes API_AVAILABLE(ios(15.2), macos(12.1), tvos(15.2), watchos(8.3), visionos(1.0)),
    SKTestTimeRateMonthlyRenewalEveryFifteenMinutes API_AVAILABLE(ios(15.2), macos(12.1), tvos(15.2), watchos(8.3), visionos(1.0)),
    SKTestTimeRateMonthlyRenewalEveryFiveMinutes API_AVAILABLE(ios(15.2), macos(12.1), tvos(15.2), watchos(8.3), visionos(1.0)),
    SKTestTimeRateMonthlyRenewalEveryThirtySeconds API_AVAILABLE(ios(15.2), macos(12.1), tvos(15.2), watchos(8.3), visionos(1.0)) = 15,
    
    SKTestTimeRateOneRenewalEveryFifteenMinutes API_AVAILABLE(ios(16.4), macos(13.3), tvos(16.4), watchos(9.4), visionos(1.0)) = 1000,
    SKTestTimeRateOneRenewalEveryFiveMinutes API_AVAILABLE(ios(16.4), macos(13.3), tvos(16.4), watchos(9.4), visionos(1.0)),
    SKTestTimeRateOneRenewalEveryMinute API_AVAILABLE(ios(16.4), macos(13.3), tvos(16.4), watchos(9.4), visionos(1.0)),
    SKTestTimeRateOneRenewalEveryThirtySeconds API_AVAILABLE(ios(16.4), macos(13.3), tvos(16.4), watchos(9.4), visionos(1.0)),
    SKTestTimeRateOneRenewalEveryTenSeconds API_AVAILABLE(ios(16.4), macos(13.3), tvos(16.4), watchos(9.4), visionos(1.0)),
    SKTestTimeRateOneRenewalEveryTwoSeconds API_AVAILABLE(ios(16.4), macos(13.3), tvos(16.4), watchos(9.4), visionos(1.0)) = 1005
} NS_SWIFT_NAME(SKTestSession.TimeRate) API_AVAILABLE(ios(14.0), macos(11.0), tvos(14.0), watchos(7.0), visionos(1.0));

@class SKTestTransaction;

SK_EXTERN_CLASS API_AVAILABLE(ios(14.0), macos(11.0), tvos(14.0), watchos(7.0), visionos(1.0)) NS_SWIFT_SENDABLE
@interface SKTestSession : NSObject


#pragma mark - Properties

// Default to NO
@property (nonatomic, assign) BOOL askToBuyEnabled;

// Default to NO
@property (nonatomic, assign) BOOL disableDialogs;

// Default to NO
@property (nonatomic, assign) BOOL failTransactionsEnabled API_DEPRECATED("No longer supported. Use simulatedError(forAPI:).", ios(14.0, 17.0), macos(11.0, 14.0), tvos(14.0, 17.0), watchos(7.0, 10.0)) API_UNAVAILABLE(visionos);

// Default to NO
@property (nonatomic, assign) BOOL interruptedPurchasesEnabled;

/// While this property is enabled, subscription renewals will fail due to billing issues, and enter a simulated
/// billing retry state.
///
/// Default to NO.
@property (nonatomic, assign) BOOL billingRetryOnRenewalEnabled API_AVAILABLE(ios(15.4), macos(12.3), tvos(15.4), watchos(8.5), visionos(1.0)) NS_SWIFT_NAME(shouldEnterBillingRetryOnRenewal);

/// Enable this property to test allowing a grace period when subscriptions enter a billing retry state.
///
/// Default to NO. The value of this property has no effect while billingRetryOnRenewalEnabled is NO.
@property (nonatomic, assign) BOOL billingGracePeriodEnabled API_AVAILABLE(ios(15.4), macos(12.3), tvos(15.4), watchos(8.5), visionos(1.0)) NS_SWIFT_NAME(billingGracePeriodIsEnabled);

/*
 Requires shouldFailTransactions to be set to YES
 Valid values are:
     SKErrorUnknown
     SKErrorInvalidOfferIdentifier
     SKErrorInvalidSignature
     SKErrorMissingOfferParams
     SKErrorInvalidOfferPrice
 */
@property (nonatomic, assign) SKErrorCode failureError API_DEPRECATED("No longer supported. Use simulatedError(forAPI:).", ios(14.0, 17.0), macos(11.0, 14.0), tvos(14.0, 17.0), watchos(7.0, 10.0)) API_UNAVAILABLE(visionos);

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

+ (instancetype)new NS_UNAVAILABLE;

- (NSArray<SKTestTransaction *> *)allTransactions;

- (void)clearTransactions;

- (BOOL)deleteTransactionWithIdentifier:(NSUInteger)identifier error:(NSError **)error NS_SWIFT_NAME(deleteTransaction(identifier:));

- (BOOL)expireSubscriptionWithProductIdentifier:(NSString *)productIdentifier error:(NSError **)error NS_SWIFT_NAME(expireSubscription(productIdentifier:));

- (BOOL)forceRenewalOfSubscriptionWithProductIdentifier:(NSString *)productIdentifier error:(NSError **)error NS_SWIFT_NAME(forceRenewalOfSubscription(productIdentifier:));

- (BOOL)refundTransactionWithIdentifier:(NSUInteger)identifier error:(NSError **)error NS_SWIFT_NAME(refundTransaction(identifier:));

/// Use this method to resolve a transaction that has a purchase issue.
///
/// Transactions will have issues if a purchase is made when interruptedPurchasesEnabled is YES, or if a
/// subscription renews when billingRetryOnRenewalEnabled is YES. The billing retry state is temporary, if a
/// transaction has exited the billing retry state then this method will have no effect.
- (BOOL)resolveIssueForTransactionWithIdentifier:(NSUInteger)identifier error:(NSError **)error NS_SWIFT_NAME(resolveIssueForTransaction(identifier:));

// Removes all property overrides and resets everything back to the default state
- (void)resetToDefaultState;


#pragma mark - Ask to Buy

- (BOOL)approveAskToBuyTransactionWithIdentifier:(NSUInteger)identifier error:(NSError **)error NS_SWIFT_NAME(approveAskToBuyTransaction(identifier:));

- (BOOL)declineAskToBuyTransactionWithIdentifier:(NSUInteger)identifier error:(NSError **)error NS_SWIFT_NAME(declineAskToBuyTransaction(identifier:));

#pragma mark - Auto-Renew

- (BOOL)disableAutoRenewForTransactionWithIdentifier:(NSUInteger)identifier error:(NSError **)error NS_SWIFT_NAME(disableAutoRenewForTransaction(identifier:));

- (BOOL)enableAutoRenewForTransactionWithIdentifier:(NSUInteger)identifier error:(NSError **)error NS_SWIFT_NAME(enableAutoRenewForTransaction(identifier:));

#pragma mark - Price Increase

/// Use this method to test a price increase for a transaction, requiring subscriber consent to continue renewing.
- (BOOL)requestPriceIncreaseConsentForTransactionWithIdentifier:(NSUInteger)identifier error:(NSError **)error  API_AVAILABLE(ios(15.4), macos(12.3), tvos(15.4), watchos(8.5), visionos(1.0)) NS_SWIFT_NAME(requestPriceIncreaseConsentForTransaction(identifier:));

/// Use this method on transactions that require price increase consent to consent to the price increase and
/// continue renewing.
- (BOOL)consentToPriceIncreaseForTransactionWithIdentifier:(NSUInteger)identifier error:(NSError **)error API_AVAILABLE(ios(15.4), macos(12.3), tvos(15.4), watchos(8.5), visionos(1.0)) NS_SWIFT_NAME(consentToPriceIncreaseForTransaction(identifier:));

/// Use this method on transactions that require price increase consent to disable autorenewing due to a
/// declined price increase.
- (BOOL)declinePriceIncreaseForTransactionWithIdentifier:(NSUInteger)identifier error:(NSError **)error API_AVAILABLE(ios(15.4), macos(12.3), tvos(15.4), watchos(8.5), visionos(1.0)) NS_SWIFT_NAME(declinePriceIncreaseForTransaction(identifier:));

#pragma mark - External Transactions

- (BOOL)buyProductWithIdentifier:(NSString *)productIdentifier error:(NSError **)error NS_SWIFT_NAME(buyProduct(productIdentifier:)) API_DEPRECATED("Use the Swift API: SKTestSession.buyProduct(identifier:, options:)", ios(14.0, 17.0), macos(11.0, 14.0), tvos(14.0, 17.0), watchos(7.0, 10.0)) API_UNAVAILABLE(visionos);

@end

NS_ASSUME_NONNULL_END
