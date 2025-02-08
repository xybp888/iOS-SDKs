//
//  ASAuthorizationError.h
//  AuthenticationServices Framework
//
//  Copyright © 2018 Apple Inc. All rights reserved.
//

#import <AuthenticationServices/ASFoundation.h>
#import <Foundation/Foundation.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

AS_EXTERN NSErrorDomain const ASAuthorizationErrorDomain API_AVAILABLE(ios(13.0), macos(10.15), tvos(13.0), watchos(6.0));

typedef NS_ERROR_ENUM(ASAuthorizationErrorDomain, ASAuthorizationError) {
    ASAuthorizationErrorUnknown = 1000,
    ASAuthorizationErrorCanceled = 1001,
    ASAuthorizationErrorInvalidResponse = 1002,
    ASAuthorizationErrorNotHandled = 1003,
    ASAuthorizationErrorFailed = 1004,
    ASAuthorizationErrorNotInteractive API_AVAILABLE(ios(15.0), macos(12.0)) API_UNAVAILABLE(tvos, watchos) = 1005,

    /// This error should only be returned when specifying @c excludedCredentials on a public key credential registration request.
    ASAuthorizationErrorMatchedExcludedCredential AS_API_AVAILABLE(ios(18.0), macos(15.0), visionos(2.0)) = 1006,

    /// This error signals that the import request failed. Details will be available in the `userInfo` of the NSError.
    ASAuthorizationErrorCredentialImport AS_API_AVAILABLE(ios(18.2), macos(15.2), visionos(2.2)) = 1007,
    /// This error signals that the export request failed. Details will be available in the `userInfo` of the NSError.
    ASAuthorizationErrorCredentialExport AS_API_AVAILABLE(ios(18.2), macos(15.2), visionos(2.2)) = 1008,
} API_AVAILABLE(ios(13.0), macos(10.15), tvos(13.0), watchos(6.0));

NS_HEADER_AUDIT_END(nullability, sendability)
