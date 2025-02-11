/*
 * Copyright (c) 2006-2023 Apple Computer, Inc. All rights reserved.
 *
 * @APPLE_OSREFERENCE_LICENSE_HEADER_START@
 *
 * This file contains Original Code and/or Modifications of Original Code
 * as defined in and that are subject to the Apple Public Source License
 * Version 2.0 (the 'License'). You may not use this file except in
 * compliance with the License. The rights granted to you under the License
 * may not be used to create, or enable the creation or redistribution of,
 * unlawful or unlicensed copies of an Apple operating system, or to
 * circumvent, violate, or enable the circumvention or violation of, any
 * terms of an Apple operating system software license agreement.
 *
 * Please obtain a copy of the License at
 * http://www.opensource.apple.com/apsl/ and read it before using this file.
 *
 * The Original Code and all software distributed under the License are
 * distributed on an 'AS IS' basis, WITHOUT WARRANTY OF ANY KIND, EITHER
 * EXPRESS OR IMPLIED, AND APPLE HEREBY DISCLAIMS ALL SUCH WARRANTIES,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, QUIET ENJOYMENT OR NON-INFRINGEMENT.
 * Please see the License for the specific language governing rights and
 * limitations under the License.
 *
 * @APPLE_OSREFERENCE_LICENSE_HEADER_END@
 */

#ifndef _OS__OSBYTEORDER_H
#define _OS__OSBYTEORDER_H

#include <sys/_types.h>

/* Macros for swapping constant values in the preprocessing stage. */
#define __DARWIN_OSSwapConstInt16(x) \
    ((__uint16_t)((((__uint16_t)(x) & 0xff00U) >> 8) | \
	        (((__uint16_t)(x) & 0x00ffU) << 8)))

#define __DARWIN_OSSwapConstInt32(x) \
    ((__uint32_t)((((__uint32_t)(x) & 0xff000000U) >> 24) | \
	        (((__uint32_t)(x) & 0x00ff0000U) >>  8) | \
	        (((__uint32_t)(x) & 0x0000ff00U) <<  8) | \
	        (((__uint32_t)(x) & 0x000000ffU) << 24)))

#define __DARWIN_OSSwapConstInt64(x) \
    ((__uint64_t)((((__uint64_t)(x) & 0xff00000000000000ULL) >> 56) | \
	        (((__uint64_t)(x) & 0x00ff000000000000ULL) >> 40) | \
	        (((__uint64_t)(x) & 0x0000ff0000000000ULL) >> 24) | \
	        (((__uint64_t)(x) & 0x000000ff00000000ULL) >>  8) | \
	        (((__uint64_t)(x) & 0x00000000ff000000ULL) <<  8) | \
	        (((__uint64_t)(x) & 0x0000000000ff0000ULL) << 24) | \
	        (((__uint64_t)(x) & 0x000000000000ff00ULL) << 40) | \
	        (((__uint64_t)(x) & 0x00000000000000ffULL) << 56)))

#if defined(__GNUC__)


#if defined (__arm__) || defined(__arm64__)
#include <libkern/arm/_OSByteOrder.h>
#endif


#define __DARWIN_OSSwapInt16(x) \
    ((__uint16_t)(__builtin_constant_p(x) ? __DARWIN_OSSwapConstInt16(x) : _OSSwapInt16(x)))

#define __DARWIN_OSSwapInt32(x) \
    (__builtin_constant_p(x) ? __DARWIN_OSSwapConstInt32(x) : _OSSwapInt32(x))

#define __DARWIN_OSSwapInt64(x) \
    (__builtin_constant_p(x) ? __DARWIN_OSSwapConstInt64(x) : _OSSwapInt64(x))

#else /* ! __GNUC__ */


#define __DARWIN_OSSwapInt16(x) _OSSwapInt16(x)

#define __DARWIN_OSSwapInt32(x) _OSSwapInt32(x)

#define __DARWIN_OSSwapInt64(x) _OSSwapInt64(x)

#endif /* __GNUC__ */

#endif /* ! _OS__OSBYTEORDER_H */
