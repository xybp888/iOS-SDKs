/*
 * Copyright (c) 2026 Apple Inc. All rights reserved.
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
 * @header
 * Public API for querying the Lockdown Mode state.
 *
 * Lockdown Mode is an optional security feature that provides enhanced
 * protections by reducing attack surface. This API allows applications
 * to query whether Lockdown Mode is currently enabled on the system.
 */
#ifndef __OS_LOCKDOWN_MODE_H
#define __OS_LOCKDOWN_MODE_H

#include <stdbool.h>

#include <os/base.h>
#include <os/availability.h>

__BEGIN_DECLS

/*!
 * @function os_lockdown_mode_enabled
 *
 * @abstract Returns a cached value indicating whether Lockdown Mode is
 * currently enabled on the system.
 *
 * @result
 * true if Lockdown Mode is enabled; false if Lockdown Mode is disabled or not
 * supported on the platform.
 *
 * @discussion
 * This function will abort the process if an unexpected error occurs while
 * querying the Lockdown Mode state.
 *
 */
API_AVAILABLE(macos(27.0), ios(27.0), watchos(27.0), tvos(27.0), visionos(27.0))
OS_EXPORT OS_WARN_RESULT
bool
os_lockdown_mode_enabled(void);

__END_DECLS

#endif // __OS_LOCKDOWN_MODE_H
