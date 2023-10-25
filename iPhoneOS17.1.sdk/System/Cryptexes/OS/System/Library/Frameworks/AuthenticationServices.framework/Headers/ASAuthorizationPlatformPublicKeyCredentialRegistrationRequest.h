// Copyright © 2020 Apple Inc. All rights reserved.

#import <AuthenticationServices/ASAuthorizationPublicKeyCredentialRegistrationRequest.h>
#import <AuthenticationServices/ASAuthorizationPublicKeyCredentialLargeBlobRegistrationInput.h>
#import <AuthenticationServices/ASAuthorizationRequest.h>
#import <AuthenticationServices/ASFoundation.h>

#import <AuthenticationServices/ASAuthorizationWebBrowserPlatformPublicKeyCredentialRegistrationRequest.h>

AS_HEADER_AUDIT_BEGIN(nullability, sendability)

API_AVAILABLE(macos(12.0), ios(15.0), tvos(16.0)) API_UNAVAILABLE(watchos)
@interface ASAuthorizationPlatformPublicKeyCredentialRegistrationRequest : ASAuthorizationRequest <ASAuthorizationPublicKeyCredentialRegistrationRequest>

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

@property (nonatomic, nullable) ASAuthorizationPublicKeyCredentialLargeBlobRegistrationInput *largeBlob NS_REFINED_FOR_SWIFT API_AVAILABLE(macos(14.0), ios(17.0)) API_UNAVAILABLE(tvos, watchos);

@end

API_AVAILABLE(macos(13.5), macCatalyst(16.6)) API_UNAVAILABLE(ios, tvos, watchos)
@interface ASAuthorizationPlatformPublicKeyCredentialRegistrationRequest () <ASAuthorizationWebBrowserPlatformPublicKeyCredentialRegistrationRequest>
@end

AS_HEADER_AUDIT_END(nullability, sendability)
