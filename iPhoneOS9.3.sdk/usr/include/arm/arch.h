/*
 * Copyright (c) 2007 Apple Inc. All rights reserved.
 */
#ifndef _ARM_ARCH_H
#define _ARM_ARCH_H

/* Collect the __ARM_ARCH_*__ compiler flags into something easier to use. */
#if defined (__ARM_ARCH_7A__) || defined (__ARM_ARCH_7S__) || defined (__ARM_ARCH_7F__) || defined (__ARM_ARCH_7K__)
#define _ARM_ARCH_7
#endif

#if defined (_ARM_ARCH_7) || defined (__ARM_ARCH_6K__) || defined (__ARM_ARCH_6ZK__)
#define _ARM_ARCH_6K
#endif

#if defined (_ARM_ARCH_7) || defined (__ARM_ARCH_6Z__) || defined (__ARM_ARCH_6ZK__)
#define _ARM_ARCH_6Z
#endif

#if defined (__ARM_ARCH_6__) || defined (__ARM_ARCH_6J__) || \
	defined (_ARM_ARCH_6Z) || defined (_ARM_ARCH_6K)
#define _ARM_ARCH_6
#endif

#if defined (_ARM_ARCH_6) || defined (__ARM_ARCH_5E__) || \
    defined (__ARM_ARCH_5TE__) || defined (__ARM_ARCH_5TEJ__)
#define _ARM_ARCH_5E
#endif

#if defined (_ARM_ARCH_5E) || defined (__ARM_ARCH_5__) || \
	defined (__ARM_ARCH_5T__)
#define _ARM_ARCH_5
#endif

#if defined (_ARM_ARCH_5) || defined (__ARM_ARCH_4T__)
#define _ARM_ARCH_4T
#endif

#if defined (_ARM_ARCH_4T) || defined (__ARM_ARCH_4__)
#define _ARM_ARCH_4
#endif

#endif
