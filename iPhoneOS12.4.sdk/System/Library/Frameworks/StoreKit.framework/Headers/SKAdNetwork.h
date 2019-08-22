//
//  SKAdNetwork.h
//  StoreKit
//
//  Copyright © 2017 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <StoreKit/StoreKitDefines.h>

NS_ASSUME_NONNULL_BEGIN

SK_EXTERN_CLASS_AVAILABLE_IOS(11_3) __TVOS_PROHIBITED @interface SKAdNetwork : NSObject

// Participating apps should call this on launch to complete the install+open action associated with a product view
+ (void)registerAppForAdNetworkAttribution NS_AVAILABLE_IOS(11_3);

@end

// Constants for use with SKStoreProductViewController to associate a product view with an install+open

// Advertising network's cryptographic signature for the atribution params (NSString)
SK_EXTERN NSString * const SKStoreProductParameterAdNetworkAttributionSignature NS_AVAILABLE_IOS(11_3);

// Advertising network campaign identifier (NSNumber)
SK_EXTERN NSString * const SKStoreProductParameterAdNetworkCampaignIdentifier NS_AVAILABLE_IOS(11_3);

// Advertising network identifier (NSString)
SK_EXTERN NSString * const SKStoreProductParameterAdNetworkIdentifier NS_AVAILABLE_IOS(11_3);

// Random entropy value for security (NSUUID)
SK_EXTERN NSString * const SKStoreProductParameterAdNetworkNonce NS_AVAILABLE_IOS(11_3);

// Timestamp for this ad impression (NSNumber)
SK_EXTERN NSString * const SKStoreProductParameterAdNetworkTimestamp NS_AVAILABLE_IOS(11_3);

NS_ASSUME_NONNULL_END
