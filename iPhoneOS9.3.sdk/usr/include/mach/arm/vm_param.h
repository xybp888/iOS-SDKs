/*
 * Copyright (c) 2007 Apple Inc. All rights reserved.
 */
/*
 * FILE_ID: vm_param.h
 */

/*
 *	ARM machine dependent virtual memory parameters.
 */

#ifndef	_MACH_ARM_VM_PARAM_H_
#define _MACH_ARM_VM_PARAM_H_

#if !defined (KERNEL) && !defined (__ASSEMBLER__)
#include <mach/vm_page_size.h>
#endif

#define BYTE_SIZE	8	/* byte size in bits */


#define PAGE_SHIFT			vm_page_shift
#define PAGE_SIZE			vm_page_size
#define PAGE_MASK			vm_page_mask

#define VM_PAGE_SIZE		vm_page_size

#define	machine_ptob(x)		((x) << PAGE_SHIFT)


#define PAGE_MAX_SHIFT		14
#define PAGE_MAX_SIZE		(1 << PAGE_MAX_SHIFT)
#define PAGE_MAX_MASK		(PAGE_MAX_SIZE-1)

#define PAGE_MIN_SHIFT		12
#define PAGE_MIN_SIZE		(1 << PAGE_MIN_SHIFT)
#define PAGE_MIN_MASK		(PAGE_MIN_SIZE-1)

#ifndef __ASSEMBLER__


#if defined (__arm__)

#define VM_MIN_ADDRESS		((vm_address_t) 0x00000000)
#define VM_MAX_ADDRESS		((vm_address_t) 0x80000000)

/* system-wide values */
#define MACH_VM_MIN_ADDRESS	((mach_vm_offset_t) 0)
#define MACH_VM_MAX_ADDRESS	((mach_vm_offset_t) VM_MAX_ADDRESS)

#elif defined (__arm64__)

#define VM_MIN_ADDRESS		((vm_address_t) 0x0000000000000000ULL)
#define VM_MAX_ADDRESS		((vm_address_t) 0x0000000080000000ULL)

/* system-wide values */
#define MACH_VM_MIN_ADDRESS	((mach_vm_offset_t) 0x0ULL)
#define MACH_VM_MAX_ADDRESS	((mach_vm_offset_t) 0x0000001000000000ULL)

#else
#error architecture not supported
#endif

#define VM_MAP_MIN_ADDRESS      VM_MIN_ADDRESS
#define VM_MAP_MAX_ADDRESS      VM_MAX_ADDRESS


#endif	/* !__ASSEMBLER__ */

#define SWI_SYSCALL	0x80

#endif	/* _MACH_ARM_VM_PARAM_H_ */
