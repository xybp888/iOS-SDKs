// Copyright © 2023 Apple Inc. All rights reserved.

#import <AuthenticationServices/ASFoundation.h>

@class ASAuthorizationPlatformPublicKeyCredentialAssertionRequest;
@class ASAuthorizationPlatformPublicKeyCredentialRegistrationRequest;
@class ASPublicKeyCredentialClientData;

AS_HEADER_AUDIT_BEGIN(nullability, sendability)

#if defined(TARGET_OS_VISION) && TARGET_OS_VISION
API_AVAILABLE(macos(13.5), macCatalyst(16.6), ios(17.4)) API_UNAVAILABLE(tvos, watchos, visionos)
#else
API_AVAILABLE(macos(13.5), macCatalyst(16.6), ios(17.4)) API_UNAVAILABLE(tvos, watchos)
#endif
NS_REFINED_FOR_SWIFT
@protocol ASAuthorizationWebBrowserPlatformPublicKeyCredentialProvider

- (ASAuthorizationPlatformPublicKeyCredentialRegistrationRequest *)createCredentialRegistrationRequestWithClientData:(ASPublicKeyCredentialClientData *)clientData name:(NSString *)name userID:(NSData *)userID;

- (ASAuthorizationPlatformPublicKeyCredentialAssertionRequest *)createCredentialAssertionRequestWithClientData:(ASPublicKeyCredentialClientData *)clientData;

@end

AS_HEADER_AUDIT_END(nullability, sendability)
