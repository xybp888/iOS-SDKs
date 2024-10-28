/*
 * Copyright (c) 2024 Apple Inc. All rights reserved.
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

#ifndef _DARWIN_C_STDATOMIC_
#define _DARWIN_C_STDATOMIC_

#if !__building_module(Darwin)
#error "Do not include this header directly, include <stdatomic.h> instead"
#endif

/* <stdatomic.h> isn't supported in C++ until C++23. Don't automatically
   include it when building Darwin unless it's supported. */
#if !defined(__cplusplus) || (__cplusplus >= 202302L)
#include <stdatomic.h>
#endif

#endif /* _DARWIN_C_STDATOMIC_ */
