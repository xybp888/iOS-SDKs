//
//  SKTestError.h
//  StoreKitTest
//
//  Copyright © 2020 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <StoreKit/StoreKitDefines.h>

NS_ASSUME_NONNULL_BEGIN

SK_EXTERN NSErrorDomain const SKTestErrorDomain API_AVAILABLE(ios(14.0), macos(11.0), tvos(14.0), watchos(7.0));

typedef NS_ERROR_ENUM(SKTestErrorDomain, SKTestErrorCode) {
    SKTestErrorCodeServiceUnavailable       = 0,
    SKTestErrorCodeInvalidProductIdentifier = 1,
    SKTestErrorCodeInvalidProductType       = 2,
    SKTestErrorCodeInvalidURL               = 3,
    SKTestErrorCodeFileNotFound             = 4,
    SKTestErrorCodeNoSubscriptionFound      = 5,
    SKTestErrorCodeNoTransactionFound       = 6,
    SKTestErrorCodeInvalidAction            = 7
} API_AVAILABLE(ios(14.0), macos(11.0), tvos(14.0), watchos(7.0));


NS_ASSUME_NONNULL_END
