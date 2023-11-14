// Copyright © 2023 Apple Inc. All rights reserved.

#import <AuthenticationServices/ASFoundation.h>

@class ASAuthorizationPlatformPublicKeyCredentialAssertionRequest;
@class ASAuthorizationPlatformPublicKeyCredentialRegistrationRequest;
@class ASPublicKeyCredentialClientData;

AS_HEADER_AUDIT_BEGIN(nullability, sendability)

API_AVAILABLE(macos(13.5), macCatalyst(16.6)) API_UNAVAILABLE(ios, tvos, watchos)
NS_REFINED_FOR_SWIFT
@protocol ASAuthorizationWebBrowserPlatformPublicKeyCredentialProvider

- (ASAuthorizationPlatformPublicKeyCredentialRegistrationRequest *)createCredentialRegistrationRequestWithClientData:(ASPublicKeyCredentialClientData *)clientData name:(NSString *)name userID:(NSData *)userID;

- (ASAuthorizationPlatformPublicKeyCredentialAssertionRequest *)createCredentialAssertionRequestWithClientData:(ASPublicKeyCredentialClientData *)clientData;

@end

AS_HEADER_AUDIT_END(nullability, sendability)
