// Copyright © 2022 Apple Inc. All rights reserved.

#import <Foundation/Foundation.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

@class ASAuthorizationWebBrowserPlatformPublicKeyCredential;

API_AVAILABLE(macos(13.3), macCatalyst(16.4)) API_UNAVAILABLE(ios, tvos, watchos)
typedef NS_ENUM(NSInteger, ASAuthorizationWebBrowserPublicKeyCredentialManagerAuthorizationState) {
    ASAuthorizationWebBrowserPublicKeyCredentialManagerAuthorizationStateAuthorized,
    ASAuthorizationWebBrowserPublicKeyCredentialManagerAuthorizationStateDenied,
    ASAuthorizationWebBrowserPublicKeyCredentialManagerAuthorizationStateNotDetermined,
} NS_SWIFT_NAME(ASAuthorizationWebBrowserPublicKeyCredentialManager.AuthorizationState);

NS_SWIFT_SENDABLE
AS_EXTERN API_AVAILABLE(macos(13.3), macCatalyst(16.4)) API_UNAVAILABLE(ios, tvos, watchos)
@interface ASAuthorizationWebBrowserPublicKeyCredentialManager : NSObject

- (instancetype)init NS_DESIGNATED_INITIALIZER;

- (void)requestAuthorizationForPublicKeyCredentials:(void (^)(ASAuthorizationWebBrowserPublicKeyCredentialManagerAuthorizationState authorizationState))completionHandler NS_SWIFT_NAME(requestAuthorizationForPublicKeyCredentials(_:));

- (void)platformCredentialsForRelyingParty:(NSString *)relyingParty completionHandler:(void (^)(NSArray<ASAuthorizationWebBrowserPlatformPublicKeyCredential *> *))completionHandler NS_REFINED_FOR_SWIFT;

@property (nonatomic, readonly) ASAuthorizationWebBrowserPublicKeyCredentialManagerAuthorizationState authorizationStateForPlatformCredentials;

@end

NS_HEADER_AUDIT_END(nullability, sendability)
