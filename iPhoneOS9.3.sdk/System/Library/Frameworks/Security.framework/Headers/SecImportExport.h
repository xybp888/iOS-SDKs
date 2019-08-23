/*
 * Copyright (c) 2007-2009,2012-2013 Apple Inc. All Rights Reserved.
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
	@header SecImportExport
	contains import/export functionality for keys and certificates.
*/

#ifndef _SECURITY_SECIMPORTEXPORT_H_
#define _SECURITY_SECIMPORTEXPORT_H_

#include <Security/SecBase.h>
#include <CoreFoundation/CFBase.h>
#include <CoreFoundation/CFArray.h>
#include <CoreFoundation/CFData.h>
#include <CoreFoundation/CFDictionary.h>

__BEGIN_DECLS

CF_ASSUME_NONNULL_BEGIN
CF_IMPLICIT_BRIDGING_ENABLED

/*!
    @enum Import/Export options
    @discussion Predefined key constants used to pass in arguments to the
        import/export functions
    @constant kSecImportExportPassphrase Specifies a passphrase represented by
        a CFStringRef to be used to encrypt/decrypt.
*/
extern const CFStringRef kSecImportExportPassphrase
    __OSX_AVAILABLE_STARTING(__MAC_10_6, __IPHONE_2_0);

/*!
    @enum Import/Export item description
    @discussion Predefined key constants used to pass back a CFArray with a
        CFDictionary per item.

    @constant kSecImportItemLabel a CFStringRef representing the item label.  
        This implementation specific identifier cannot be expected to have
        any format.
    @constant kSecImportItemKeyID a CFDataRef representing the key id.  Often
        the SHA-1 digest of the public key.
    @constant kSecImportItemIdentity a SecIdentityRef representing the identity.
    @constant kSecImportItemTrust a SecTrustRef set up with all relevant 
        certificates.  Not guaranteed to succesfully evaluate.
    @constant kSecImportItemCertChain a CFArrayRef holding all relevant 
        certificates for this item's identity
*/
extern const CFStringRef kSecImportItemLabel
    __OSX_AVAILABLE_STARTING(__MAC_10_6, __IPHONE_2_0);
extern const CFStringRef kSecImportItemKeyID
    __OSX_AVAILABLE_STARTING(__MAC_10_6, __IPHONE_2_0);
extern const CFStringRef kSecImportItemTrust
    __OSX_AVAILABLE_STARTING(__MAC_10_6, __IPHONE_2_0);
extern const CFStringRef kSecImportItemCertChain
    __OSX_AVAILABLE_STARTING(__MAC_10_6, __IPHONE_2_0);
extern const CFStringRef kSecImportItemIdentity
    __OSX_AVAILABLE_STARTING(__MAC_10_6, __IPHONE_2_0);

/*!
	@function SecPKCS12Import
	@abstract return contents of a PKCS#12 formatted blob.
    @param pkcs12_data PKCS#12 formatted data
    @param options Dictionary containing options for decode.  A 
        kSecImportExportPassphrase is required at a minimum.  Only password-
        based PKCS#12 blobs are currently supported.
    @param items Array containing a dictionary for every item extracted.  See
        kSecImportItem constants.
	@result errSecSuccess in case of success. errSecDecode means either the
        blob can't be read or it is malformed. errSecAuthFailed means an
        incorrect password was passed, or data in the container got damaged.
*/
OSStatus SecPKCS12Import(CFDataRef pkcs12_data, CFDictionaryRef options,
    CFArrayRef * __nonnull CF_RETURNS_RETAINED items) __OSX_AVAILABLE_STARTING(__MAC_10_6, __IPHONE_2_0);

CF_IMPLICIT_BRIDGING_DISABLED
CF_ASSUME_NONNULL_END

__END_DECLS

#endif /* !_SECURITY_SECIMPORTEXPORT_H_ */
