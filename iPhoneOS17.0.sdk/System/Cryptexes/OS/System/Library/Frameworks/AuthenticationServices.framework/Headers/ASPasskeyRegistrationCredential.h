//
//  ASPasskeyRegistrationCredential.h
//  AuthenticationServices Framework
//
//  Copyright © 2022 Apple Inc. All rights reserved.
//

#import <AuthenticationServices/ASAuthorizationCredential.h>
#import <AuthenticationServices/ASFoundation.h>
#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/*! @class This class encapsulates a passkey registration response created by a credential provider extension.
 */
AS_EXTERN API_AVAILABLE(ios(17.0), macos(14.0)) API_UNAVAILABLE(tvos, watchos)
@interface ASPasskeyRegistrationCredential : NSObject <ASAuthorizationCredential>

/*! @abstract Initializes an ASPasskeyRegistrationCredential object.
 @param relyingParty the relying party identifier associated with this passkey.
 @param clientDataHash the JSON encoded client data for this registration result.
 @param rawID the raw credential identifier of this passkey.
 @param attestationObject the attestation object for this passkey registration result.
 */
- (instancetype)initWithRelyingParty:(NSString *)relyingParty clientDataHash:(NSData *)clientDataHash credentialID:(NSData *)credentialID attestationObject:(NSData *)attestationObject;

/*! @abstract Creates and initializes an ASPasskeyRegistrationCredential object.
 @param relyingParty the relying party identifier associated with this passkey.
 @param clientDataHash the JSON encoded client data for this registration result.
 @param rawID the raw credential identifier of this passkey.
 @param attestationObject the attestation object for this passkey registration result.
 */
+ (instancetype)credentialWithRelyingParty:(NSString *)relyingParty clientDataHash:(NSData *)clientDataHash credentialID:(NSData *)credentialID attestationObject:(NSData *)attestationObject;

/*! @abstract The relying party identifier associated with this passkey.
 */
@property (nonatomic, readonly) NSString *relyingParty;

/*! @abstract The hash of the client data for this registration result.
 */
@property (nonatomic, readonly) NSData *clientDataHash;

/*! @abstract The raw credential identifier of this passkey.
 */
@property (nonatomic, readonly) NSData *credentialID;

/*! @abstract The attestation object for this passkey registration result.
 */
@property (nonatomic, readonly) NSData *attestationObject;

@end

NS_ASSUME_NONNULL_END
