// Copyright © 2022 Apple Inc. All rights reserved.

#import <Foundation/Foundation.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

NS_REFINED_FOR_SWIFT
AS_EXTERN API_AVAILABLE(macos(13.3), macCatalyst(16.4)) API_UNAVAILABLE(ios, tvos, watchos)
@interface ASAuthorizationWebBrowserPlatformPublicKeyCredential : NSObject

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

/// The user name of the saved credential.
@property (nonatomic, readonly) NSString *name;


/// The "relying party" (generally website) the credential was saved for.
@property (nonatomic, readonly) NSString *relyingParty;

/// A unique identifier for this credential.
@property (nonatomic, readonly) NSData *credentialID;

/// A unique identifier for the user account associated with this credential. One account may have multiple associated credentials.
@property (nonatomic, readonly) NSData *userHandle;

@end

NS_HEADER_AUDIT_END(nullability, sendability)
