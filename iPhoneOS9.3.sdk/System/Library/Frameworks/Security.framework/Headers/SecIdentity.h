/*
 * Copyright (c) 2002-2004,2007-2009,2012-2013 Apple Inc. All Rights Reserved.
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
	@header SecIdentity
	The functions provided in SecIdentity.h implement a convenient way to
	match private keys with certificates.
*/

#ifndef _SECURITY_SECIDENTITY_H_
#define _SECURITY_SECIDENTITY_H_

#include <Security/SecBase.h>
#include <CoreFoundation/CFBase.h>

__BEGIN_DECLS

CF_ASSUME_NONNULL_BEGIN
CF_IMPLICIT_BRIDGING_ENABLED

/*!
	@function SecIdentityGetTypeID
	@abstract Returns the type identifier of SecIdentity instances.
	@result The CFTypeID of SecIdentity instances.
*/
CFTypeID SecIdentityGetTypeID(void)
    __OSX_AVAILABLE_STARTING(__MAC_10_3, __IPHONE_2_0);

/*!
	@function SecIdentityCopyCertificate
    @abstract Returns a reference to a certificate for the given identity
    reference.
    @param identityRef An identity reference.
	@param certificateRef On return, a pointer to the found certificate
    reference.
    @result A result code.  See "Security Error Codes" (SecBase.h).
*/
OSStatus SecIdentityCopyCertificate(
            SecIdentityRef identityRef, 
            SecCertificateRef * __nonnull CF_RETURNS_RETAINED certificateRef)
    __OSX_AVAILABLE_STARTING(__MAC_10_3, __IPHONE_2_0);

/*!
	@function SecIdentityCopyPrivateKey
    @abstract Returns the private key associated with an identity.
    @param identityRef An identity reference.
	@param privateKeyRef On return, a pointer to the private key for the given
    identity. The private key must be of class type kSecAppleKeyItemClass.
    @result A result code.  See "Security Error Codes" (SecBase.h).
*/
OSStatus SecIdentityCopyPrivateKey(
            SecIdentityRef identityRef, 
            SecKeyRef * __nonnull CF_RETURNS_RETAINED privateKeyRef)
    __OSX_AVAILABLE_STARTING(__MAC_10_3, __IPHONE_2_0);

CF_IMPLICIT_BRIDGING_DISABLED
CF_ASSUME_NONNULL_END

__END_DECLS

#endif /* !_SECURITY_SECIDENTITY_H_ */
