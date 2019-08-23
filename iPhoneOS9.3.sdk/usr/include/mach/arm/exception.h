/*
 * Copyright (c) 2007 Apple Inc. All rights reserved.
 */

#ifndef	_MACH_ARM_EXCEPTION_H_
#define _MACH_ARM_EXCEPTION_H_

#define EXC_TYPES_COUNT         14      /* incl. illegal exception 0 */

#define EXC_MASK_MACHINE         0

#define EXCEPTION_CODE_MAX       2      /*  code and subcode */

/*
 *	Trap numbers as defined by the hardware exception vectors.
 */

/*
 *      EXC_BAD_INSTRUCTION
 */

#define EXC_ARM_UNDEFINED	1	/* Undefined */


/*
 *      EXC_BAD_ACCESS
 *      Note: do not conflict with kern_return_t values returned by vm_fault
 */

#define EXC_ARM_DA_ALIGN	0x101	/* Alignment Fault */
#define EXC_ARM_DA_DEBUG	0x102	/* Debug (watch/break) Fault */
#define EXC_ARM_SP_ALIGN	0x103	/* SP Alignment Fault */
#define EXC_ARM_SWP			0x104	/* SWP instruction */

/*
 *	EXC_BREAKPOINT
 */

#define EXC_ARM_BREAKPOINT	1	/* breakpoint trap */


#endif	/* _MACH_ARM_EXCEPTION_H_ */
