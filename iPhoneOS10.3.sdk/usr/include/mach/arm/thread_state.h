/*
 * Copyright (c) 2000-2007 Apple Inc. All rights reserved.
 */
/*
 * @OSF_COPYRIGHT@
 */

#ifndef _MACH_ARM_THREAD_STATE_H_
#define _MACH_ARM_THREAD_STATE_H_

/* Size of maximum exported thread state in words */
#define ARM_THREAD_STATE_MAX	(144)    /* Size of biggest state possible */

#if defined (__arm__) || defined(__arm64__)
#define THREAD_STATE_MAX	ARM_THREAD_STATE_MAX
#else
#error Unsupported arch
#endif

#endif	/* _MACH_ARM_THREAD_STATE_H_ */
