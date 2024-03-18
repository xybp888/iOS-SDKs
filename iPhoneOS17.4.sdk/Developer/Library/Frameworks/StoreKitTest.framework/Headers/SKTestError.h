//
//  SKTestError.h
//  StoreKitTest
//
//  Copyright © 2020 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <StoreKit/StoreKitDefines.h>

NS_ASSUME_NONNULL_BEGIN

SK_EXTERN NSErrorDomain const SKTestErrorDomain API_AVAILABLE(ios(14.0), macos(11.0), tvos(14.0), watchos(7.0), visionos(1.0));

SK_EXTERN NSErrorDomain const SKAdTestErrorDomain API_AVAILABLE(ios(15.4)) API_UNAVAILABLE(macos,watchos) __TVOS_PROHIBITED;

typedef NS_ERROR_ENUM(SKTestErrorDomain, SKTestErrorCode) {
    SKTestErrorCodeServiceUnavailable       = 0,
    SKTestErrorCodeInvalidProductIdentifier = 1,
    SKTestErrorCodeInvalidProductType       = 2,
    SKTestErrorCodeInvalidURL               = 3,
    SKTestErrorCodeFileNotFound             = 4,
    SKTestErrorCodeNoSubscriptionFound      = 5,
    SKTestErrorCodeNoTransactionFound       = 6,
    SKTestErrorCodeInvalidAction            = 7
} API_AVAILABLE(ios(14.0), macos(11.0), tvos(14.0), watchos(7.0), visionos(1.0));

typedef NS_ERROR_ENUM(SKAdTestErrorDomain, SKAdTestErrorCode) {
    SKAdTestErrorCodeSignatureMissingAdNetworkId                                    = 0,
    SKAdTestErrorCodeSignatureMissingCampaignId                                     = 1,
    SKAdTestErrorCodeSignatureMissingAppAdamId                                      = 2,
    SKAdTestErrorCodeSignatureMissingNonce                                          = 3,
    SKAdTestErrorCodeSignatureMissingSourceAppAdamId                                = 4,
    SKAdTestErrorCodeSignatureMissingFidelityType                                   = 5,
    SKAdTestErrorCodeSignatureMissingTimestamp                                      = 6,
    SKAdTestErrorCodeSignatureVerificationFailed                                    = 7,
    SKAdTestErrorCodeSignatureInvalidKey                                            = 8,
    SKAdTestErrorCodeSignatureInvalidOrder                                          = 9,
    SKAdTestErrorCodeSignatureUnknownError                                          = 10,
    SKAdTestErrorCodeMisplacedWinnerPostback                                        = 11,
    SKAdTestErrorCodeInvalidRunnerUpPostback                                        = 12,
    SKAdTestErrorCodeInvalidConversionValue                                         = 13,
    SKAdTestErrorCodeMissingWinningPostback                                         = 14,
    SKAdTestErrorCodeMissingPostbacks                                               = 15,
    SKAdTestErrorCodeMalformedPostbacks                                             = 16,
    SKAdTestErrorCodeExcessivePostbacks                                             = 17,
    SKAdTestErrorCodeNoPendingPostbacks                                             = 18,
    SKAdTestErrorCodeInvalidPostbackURL                                             = 19,
    SKAdTestErrorCodeMissingSignature                                               = 20,
    SKAdTestErrorCodeUnknownError                                                   = 21,
    SKAdTestErrorCodeSignatureMissingSourceIdentifier NS_ENUM_AVAILABLE_IOS(16_4)   = 22,
    SKAdTestErrorCodeInvalidVersion NS_ENUM_AVAILABLE_IOS(16_4)                     = 23,
    SKAdTestErrorCodeInvalidCampaignId NS_ENUM_AVAILABLE_IOS(16_4)                  = 24,
    SKAdTestErrorCodeInvalidSourceIdentifier NS_ENUM_AVAILABLE_IOS(16_4)            = 25,
    SKAdTestErrorCodeInvalidWinningPostbackCount NS_ENUM_AVAILABLE_IOS(16_4)        = 26,
    SKAdTestErrorCodeUnlinkedWinningPostbacks NS_ENUM_AVAILABLE_IOS(16_4)           = 27,
    SKAdTestErrorCodeConflictingSource NS_ENUM_AVAILABLE_IOS(16_4)                  = 28,
    SKAdTestErrorCodeInvalidSourceAppAdamId NS_ENUM_AVAILABLE_IOS(16_4)             = 29,
    SKAdTestErrorCodeInvalidSourceDomain NS_ENUM_AVAILABLE_IOS(16_4)                = 30,
    SKAdTestErrorCodeInvalidImpressionId NS_ENUM_AVAILABLE_IOS(16_4)                = 31,
    SKAdTestErrorCodeSignatureMissingSourceDomain NS_ENUM_AVAILABLE_IOS(16_4)       = 32,
} API_AVAILABLE(ios(15.4)) API_UNAVAILABLE(macos,watchos,visionos) __TVOS_PROHIBITED;

NS_ASSUME_NONNULL_END
