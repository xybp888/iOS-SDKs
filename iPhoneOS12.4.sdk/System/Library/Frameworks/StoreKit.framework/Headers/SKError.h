//
//  SKError.h
//  StoreKit
//
//  Copyright 2009 Apple, Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <StoreKit/StoreKitDefines.h>

NS_ASSUME_NONNULL_BEGIN

SK_EXTERN NSString * const SKErrorDomain NS_AVAILABLE(10_7, 3_0);

// error codes for the SKErrorDomain
typedef NS_ENUM(NSInteger,SKErrorCode) {
    SKErrorUnknown,
    SKErrorClientInvalid,                                                     // client is not allowed to issue the request, etc.
    SKErrorPaymentCancelled,                                                  // user cancelled the request, etc.
    SKErrorPaymentInvalid,                                                    // purchase identifier was invalid, etc.
    SKErrorPaymentNotAllowed,                                                 // this device is not allowed to make the payment
    SKErrorStoreProductNotAvailable NS_ENUM_AVAILABLE(NA, 3_0),               // Product is not available in the current storefront
    SKErrorCloudServicePermissionDenied NS_ENUM_AVAILABLE(NA, 9_3),           // user has not allowed access to cloud service information
    SKErrorCloudServiceNetworkConnectionFailed NS_ENUM_AVAILABLE(NA, 9_3),    // the device could not connect to the nework
    SKErrorCloudServiceRevoked NS_ENUM_AVAILABLE(NA, 10_3),                   // user has revoked permission to use this cloud service
    SKErrorPrivacyAcknowledgementRequired NS_ENUM_AVAILABLE(10_14_4, 12_2),   // The user needs to acknowledge Apple's privacy policy
    SKErrorUnauthorizedRequestData NS_ENUM_AVAILABLE(10_14_4, 12_2),          // The app is attempting to use SKPayment's requestData property, but does not have the appropriate entitlement
    SKErrorInvalidOfferIdentifier NS_ENUM_AVAILABLE(10_14_4, 12_2),           // The specified subscription offer identifier is not valid
    SKErrorInvalidSignature NS_ENUM_AVAILABLE(10_14_4, 12_2),                 // The cryptographic signature provided is not valid
    SKErrorMissingOfferParams NS_ENUM_AVAILABLE(10_14_4, 12_2),               // One or more parameters from SKPaymentDiscount is missing
    SKErrorInvalidOfferPrice NS_ENUM_AVAILABLE(10_14_4, 12_2),                // The price of the selected offer is not valid (e.g. lower than the current base subscription price)
};

NS_ASSUME_NONNULL_END
