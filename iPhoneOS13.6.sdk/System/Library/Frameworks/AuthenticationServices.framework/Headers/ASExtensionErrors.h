//
//  ASExtensionErrors.h
//  AuthenticationServices Framework
//
//  Copyright © 2019 Apple Inc. All rights reserved.
//

#import <AuthenticationServices/ASFoundation.h>
#import <Foundation/Foundation.h>

AS_EXTERN API_AVAILABLE(ios(12.0)) API_UNAVAILABLE(macCatalyst, macos, tvos, watchos)
NSErrorDomain const ASExtensionErrorDomain;

typedef NS_ERROR_ENUM(ASExtensionErrorDomain, ASExtensionErrorCode) {
    ASExtensionErrorCodeFailed = 0,
    ASExtensionErrorCodeUserCanceled = 1,
    ASExtensionErrorCodeUserInteractionRequired = 100,
    ASExtensionErrorCodeCredentialIdentityNotFound = 101,
} API_AVAILABLE(ios(12.0)) API_UNAVAILABLE(macCatalyst, macos, tvos, watchos);
