/*
 * Copyright (c) 2000-2009,2011-2014 Apple Inc. All Rights Reserved.
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
	@header SecBase
	SecBase contains common declarations for the Security functions.
*/

#ifndef _SECURITY_SECBASE_H_
#define _SECURITY_SECBASE_H_

#include <Availability.h>
#include <sys/cdefs.h>
#include <CoreFoundation/CFBase.h>

#if defined(__clang__)
#define SEC_DEPRECATED_ATTRIBUTE DEPRECATED_ATTRIBUTE
#else
#define SEC_DEPRECATED_ATTRIBUTE
#endif

__BEGIN_DECLS

CF_ASSUME_NONNULL_BEGIN
CF_IMPLICIT_BRIDGING_ENABLED

/*!
    @typedef SecCertificateRef
    @abstract CFType representing a X.509 certificate.
    See SecCertificate.h for details.
*/
typedef struct CF_BRIDGED_TYPE(id) __SecCertificate *SecCertificateRef;

/*!
    @typedef SecIdentityRef
    @abstract CFType representing an identity, which contains
    a SecKeyRef and an associated SecCertificateRef. See
    SecIdentity.h for details.
*/
typedef struct CF_BRIDGED_TYPE(id) __SecIdentity *SecIdentityRef;

/*!
    @typedef SecKeyRef
    @abstract CFType representing a cryptographic key. See
    SecKey.h for details.
*/
typedef struct CF_BRIDGED_TYPE(id) __SecKey *SecKeyRef;

/*!
    @typedef SecPolicyRef
    @abstract CFType representing a X.509 certificate trust policy.
    See SecPolicy.h for details.
*/
typedef struct CF_BRIDGED_TYPE(id) __SecPolicy *SecPolicyRef;

/*!
    @typedef SecAccessControl
    @abstract CFType representing access control for an item.
    SecAccessControl.h for details.
*/
typedef struct CF_BRIDGED_TYPE(id) __SecAccessControl *SecAccessControlRef;

/***********************************************
 *** OSStatus values unique to Security APIs ***
 ***********************************************/

/*
    Note: the comments that appear after these errors are used to create
    SecErrorMessages.strings. The comments must not be multi-line, and
    should be in a form meaningful to an end user. If a different or
    additional comment is needed, it can be put in the header doc format,
    or on a line that does not start with errZZZ.
*/

CF_ENUM(OSStatus)
{
    errSecSuccess                               = 0,       /* No error. */
    errSecUnimplemented                         = -4,      /* Function or operation not implemented. */
    errSecIO                                    = -36,     /*I/O error (bummers)*/
    errSecOpWr                                  = -49,     /*file already open with with write permission*/
    errSecParam                                 = -50,     /* One or more parameters passed to a function where not valid. */
    errSecAllocate                              = -108,    /* Failed to allocate memory. */
    errSecUserCanceled                          = -128,    /* User canceled the operation. */
    errSecBadReq                                = -909,    /* Bad parameter or invalid state for operation. */
    errSecInternalComponent                     = -2070,
    errSecNotAvailable                          = -25291,  /* No keychain is available. You may need to restart your computer. */
    errSecDuplicateItem                         = -25299,  /* The specified item already exists in the keychain. */
    errSecItemNotFound                          = -25300,  /* The specified item could not be found in the keychain. */
    errSecInteractionNotAllowed                 = -25308,  /* User interaction is not allowed. */
    errSecDecode                                = -26275,  /* Unable to decode the provided data. */
    errSecAuthFailed                            = -25293,  /* The user name or passphrase you entered is not correct. */
};

CF_IMPLICIT_BRIDGING_DISABLED
CF_ASSUME_NONNULL_END

__END_DECLS

#endif /* !_SECURITY_SECBASE_H_ */
