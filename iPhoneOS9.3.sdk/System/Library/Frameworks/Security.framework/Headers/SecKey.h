/*
 * Copyright (c) 2006-2009,2011-2013 Apple Inc. All Rights Reserved.
 * 
 * @APPLE_LICENSE_HEADER_START@
 * 
 * This file contains Original Code and/or Modifications of Original Code
 * as defined in and that are subject to the Apple Public Source License
 * Version 2.0 (the 'License'). You may not use this file except in
 * compliance with the License. Please obtain a copy of the License at
 * http://www.opensource.apple.com/apsl/ and read it before using this
 * file.
 * 
 * The Original Code and all software distributed under the License are
 * distributed on an 'AS IS' basis, WITHOUT WARRANTY OF ANY KIND, EITHER
 * EXPRESS OR IMPLIED, AND APPLE HEREBY DISCLAIMS ALL SUCH WARRANTIES,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, QUIET ENJOYMENT OR NON-INFRINGEMENT.
 * Please see the License for the specific language governing rights and
 * limitations under the License.
 * 
 * @APPLE_LICENSE_HEADER_END@
 */

/*!
	@header SecKey
	The functions provided in SecKey.h implement and manage a particular
    type of keychain item that represents a key.  A key can be stored in a
    keychain, but a key can also be a transient object.

	You can use a key as a keychain item in most functions.
*/

#ifndef _SECURITY_SECKEY_H_
#define _SECURITY_SECKEY_H_

#include <Security/SecBase.h>
#include <CoreFoundation/CFDictionary.h>
#include <sys/types.h>

__BEGIN_DECLS

CF_ASSUME_NONNULL_BEGIN
CF_IMPLICIT_BRIDGING_ENABLED

/* Padding Types (iPhone OS 2.0 and later only). */
typedef CF_OPTIONS(uint32_t, SecPadding)
{
    kSecPaddingNone      = 0,
    kSecPaddingPKCS1     = 1, // For EC, defaults to a signature in x9.62 DER encoding.
    kSecPaddingOAEP      = 2,

    /* For SecKeyRawSign/SecKeyRawVerify only,
     ECDSA signature is raw byte format {r,s}, big endian.
     First half is r, second half is s */
    kSecPaddingSigRaw  = 0x4000,

    /* For SecKeyRawSign/SecKeyRawVerify only, data to be signed is an MD2
       hash; standard ASN.1 padding will be done, as well as PKCS1 padding
       of the underlying RSA operation. */
    kSecPaddingPKCS1MD2  = 0x8000,  /* Unsupported as of iOS 5.0 */

    /* For SecKeyRawSign/SecKeyRawVerify only, data to be signed is an MD5
       hash; standard ASN.1 padding will be done, as well as PKCS1 padding
       of the underlying RSA operation. */
    kSecPaddingPKCS1MD5  = 0x8001,  /* Unsupported as of iOS 5.0 */

    /* For SecKeyRawSign/SecKeyRawVerify only, data to be signed is a SHA1
       hash; standard ASN.1 padding will be done, as well as PKCS1 padding
       of the underlying RSA operation. */
    kSecPaddingPKCS1SHA1 = 0x8002,

    /* For SecKeyRawSign/SecKeyRawVerify only, data to be signed is a SHA224
     hash; standard ASN.1 padding will be done, as well as PKCS1 padding
     of the underlying RSA operation. */
    kSecPaddingPKCS1SHA224 = 0x8003,

    /* For SecKeyRawSign/SecKeyRawVerify only, data to be signed is a SHA256
     hash; standard ASN.1 padding will be done, as well as PKCS1 padding
     of the underlying RSA operation. */
    kSecPaddingPKCS1SHA256 = 0x8004,

    /* For SecKeyRawSign/SecKeyRawVerify only, data to be signed is a SHA384
     hash; standard ASN.1 padding will be done, as well as PKCS1 padding
     of the underlying RSA operation. */
    kSecPaddingPKCS1SHA384 = 0x8005,

    /* For SecKeyRawSign/SecKeyRawVerify only, data to be signed is a SHA512
     hash; standard ASN.1 padding will be done, as well as PKCS1 padding
     of the underlying RSA operation. */
    kSecPaddingPKCS1SHA512 = 0x8006,
};


/*!
	@function SecKeyGetTypeID
	@abstract Returns the type identifier of SecKey instances.
	@result The CFTypeID of SecKey instances.
*/
CFTypeID SecKeyGetTypeID(void)
    __OSX_AVAILABLE_STARTING(__MAC_10_3, __IPHONE_2_0);

/*!
    @enum Dictionary key constants for SecKeyGeneratePair API.
    @discussion Predefined key constants used to get or set values
		in a dictionary.
    @constant kSecPrivateKeyAttrs The value for this key is a CFDictionaryRef
	containing attributes specific for the private key to be generated.
    @constant kSecPublicKeyAttrs The value for this key is a CFDictionaryRef
	containing attributes specific for the public key to be generated.
*/
extern const CFStringRef kSecPrivateKeyAttrs
    __OSX_AVAILABLE_STARTING(__MAC_10_8, __IPHONE_2_0);
extern const CFStringRef kSecPublicKeyAttrs
    __OSX_AVAILABLE_STARTING(__MAC_10_8, __IPHONE_2_0);

/*!
    @function SecKeyGeneratePair
    @abstract Generate a private/public keypair.
    @param parameters A dictionary containing one or more key-value pairs.
	See the discussion sections below for a complete overview of options.
    @param publicKey On return, a SecKeyRef reference to the public key.
    @param privateKey On return, a SecKeyRef reference to the private key.
    @result A result code. See "Security Error Codes" (SecBase.h).
    @discussion In order to generate a keypair the parameters dictionary must
	at least contain the following keys:

	  * kSecAttrKeyType with a value being kSecAttrKeyTypeRSA or any other
		kSecAttrKeyType defined in SecItem.h
      * kSecAttrKeySizeInBits with a value being a CFNumberRef or CFStringRef
	    containing the requested key size in bits.  Example sizes for RSA
		keys are: 512, 768, 1024, 2048.

	  The values below may be set either in the top-level dictionary or in a
	  dictionary that is the value of the kSecPrivateKeyAttrs or
	  kSecPublicKeyAttrs key in the top-level dictionary.  Setting these
	  attributes explicitly will override the defaults below.  See SecItem.h
	  for detailed information on these attributes including the types of
      the values.

      * kSecAttrLabel default NULL
	  * kSecAttrIsPermanent if this key is present and has a Boolean
	    value of true, the key or key pair will be added to the default
	    keychain.
      * kSecAttrTokenID if this key should be generated on specified token.  This
        attribute can contain CFStringRef and can be present only in the top-level
        parameters dictionary.
      * kSecAttrApplicationTag default NULL
      * kSecAttrEffectiveKeySize default NULL same as kSecAttrKeySizeInBits
      * kSecAttrCanEncrypt default false for private keys, true for public keys
      * kSecAttrCanDecrypt default true for private keys, false for public keys
      * kSecAttrCanDerive default true
      * kSecAttrCanSign default true for private keys, false for public keys
      * kSecAttrCanVerify default false for private keys, true for public keys
      * kSecAttrCanWrap default false for private keys, true for public keys
      * kSecAttrCanUnwrap default true for private keys, false for public keys

*/
OSStatus SecKeyGeneratePair(CFDictionaryRef parameters, SecKeyRef * __nullable CF_RETURNS_RETAINED publicKey,
    SecKeyRef * __nullable CF_RETURNS_RETAINED privateKey) __OSX_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_2_0);


/*!
    @function SecKeyRawSign
    @abstract Given a private key and data to sign, generate a digital
    signature. 
    @param key Private key with which to sign.
    @param padding See Padding Types above, typically kSecPaddingPKCS1SHA1.
    @param dataToSign The data to be signed, typically the digest of the
    actual data.
    @param dataToSignLen Length of dataToSign in bytes.
    @param sig Pointer to buffer in which the signature will be returned.
    @param sigLen IN/OUT maximum length of sig buffer on input, actualy
    length of sig on output.
    @result A result code. See "Security Error Codes" (SecBase.h).
    @discussion If the padding argument is kSecPaddingPKCS1, PKCS1 padding
    will be performed prior to signing. If this argument is kSecPaddingNone,
    the incoming data will be signed "as is".

    When PKCS1 padding is performed, the maximum length of data that can
    be signed is the value returned by SecKeyGetBlockSize() - 11.

    NOTE: The behavior this function with kSecPaddingNone is undefined if the
    first byte of dataToSign is zero; there is no way to verify leading zeroes
    as they are discarded during the calculation. 

    If you want to generate a proper PKCS1 style signature with DER encoding
    of the digest type - and the dataToSign is a SHA1 digest - use
    kSecPaddingPKCS1SHA1. 
 */
OSStatus SecKeyRawSign(
    SecKeyRef           key,
	SecPadding          padding,
	const uint8_t       *dataToSign,
	size_t              dataToSignLen,
	uint8_t             *sig,
	size_t              *sigLen)
    __OSX_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_2_0);


/*!
    @function SecKeyRawVerify
    @abstract Given a public key, data which has been signed, and a signature,
    verify the signature. 
    @param key Public key with which to verify the signature.
    @param padding See Padding Types above, typically kSecPaddingPKCS1SHA1.
    @param signedData The data over which sig is being verified, typically
    the digest of the actual data.
    @param signedDataLen Length of signedData in bytes.
    @param sig Pointer to the signature to verify.
    @param sigLen Length of sig in  bytes.
    @result A result code. See "Security Error Codes" (SecBase.h).
    @discussion If the padding argument is kSecPaddingPKCS1, PKCS1 padding
    will be checked during verification. If this argument is kSecPaddingNone,
    the incoming data will be compared directly to sig.

    If you are verifying a proper PKCS1-style signature, with DER encoding
    of the digest type - and the signedData is a SHA1 digest - use
    kSecPaddingPKCS1SHA1.
 */ 
OSStatus SecKeyRawVerify(
    SecKeyRef           key,
	SecPadding          padding,
	const uint8_t       *signedData,
	size_t              signedDataLen,
	const uint8_t       *sig,
	size_t              sigLen)
    __OSX_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_2_0);


/*!
    @function SecKeyEncrypt
    @abstract Encrypt a block of plaintext. 
    @param key Public key with which to encrypt the data.
    @param padding See Padding Types above, typically kSecPaddingPKCS1.
    @param plainText The data to encrypt.
    @param plainTextLen Length of plainText in bytes, this must be less
    or equal to the value returned by SecKeyGetBlockSize().
    @param cipherText Pointer to the output buffer.
    @param cipherTextLen On input, specifies how much space is available at
    cipherText; on return, it is the actual number of cipherText bytes written.
    @result A result code. See "Security Error Codes" (SecBase.h).
    @discussion If the padding argument is kSecPaddingPKCS1 or kSecPaddingOAEP,
    PKCS1 (respectively kSecPaddingOAEP) padding will be performed prior to encryption.
    If this argument is kSecPaddingNone, the incoming data will be encrypted "as is".
    kSecPaddingOAEP is the recommended value. Other value are not recommended 
    for security reason (Padding attack or malleability).

    When PKCS1 padding is performed, the maximum length of data that can
    be encrypted is the value returned by SecKeyGetBlockSize() - 11.

    When memory usage is a critical issue, note that the input buffer
    (plainText) can be the same as the output buffer (cipherText). 
 */
OSStatus SecKeyEncrypt(
    SecKeyRef           key,
	SecPadding          padding,
	const uint8_t		*plainText,
	size_t              plainTextLen,
	uint8_t             *cipherText,
	size_t              *cipherTextLen)
    __OSX_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_2_0);


/*!
    @function SecKeyDecrypt
    @abstract Decrypt a block of ciphertext. 
    @param key Private key with which to decrypt the data.
    @param padding See Padding Types above, typically kSecPaddingPKCS1.
    @param cipherText The data to decrypt.
    @param cipherTextLen Length of cipherText in bytes, this must be less
    or equal to the value returned by SecKeyGetBlockSize().
    @param plainText Pointer to the output buffer.
    @param plainTextLen On input, specifies how much space is available at
    plainText; on return, it is the actual number of plainText bytes written.
    @result A result code. See "Security Error Codes" (SecBase.h).
    @discussion If the padding argument is kSecPaddingPKCS1 or kSecPaddingOAEP,
    the corresponding padding will be removed after decryption. 
    If this argument is kSecPaddingNone, the decrypted data will be returned "as is".

    When memory usage is a critical issue, note that the input buffer
    (plainText) can be the same as the output buffer (cipherText). 
 */
OSStatus SecKeyDecrypt(
    SecKeyRef           key,                /* Private key */
	SecPadding          padding,			/* kSecPaddingNone,
                                               kSecPaddingPKCS1,
                                               kSecPaddingOAEP */
	const uint8_t       *cipherText,
	size_t              cipherTextLen,		/* length of cipherText */
	uint8_t             *plainText,	
	size_t              *plainTextLen)		/* IN/OUT */
    __OSX_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_2_0);

/*!
    @function SecKeyGetBlockSize
    @abstract Decrypt a block of ciphertext. 
    @param key The key for which the block length is requested.
    @result The block length of the key in bytes.
    @discussion If for example key is an RSA key the value returned by 
    this function is the size of the modulus.
 */
size_t SecKeyGetBlockSize(SecKeyRef key)
    __OSX_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_2_0);

CF_IMPLICIT_BRIDGING_DISABLED
CF_ASSUME_NONNULL_END

__END_DECLS

#endif /* !_SECURITY_SECKEY_H_ */
