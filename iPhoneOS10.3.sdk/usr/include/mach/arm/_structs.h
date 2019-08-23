/*
 * Copyright (c) 2004-2007 Apple Inc. All rights reserved.
 */
/*
 * @OSF_COPYRIGHT@
 */
#ifndef	_MACH_ARM__STRUCTS_H_
#define	_MACH_ARM__STRUCTS_H_

#if __DARWIN_UNIX03
#define _STRUCT_ARM_EXCEPTION_STATE	struct __darwin_arm_exception_state
_STRUCT_ARM_EXCEPTION_STATE
{
	__uint32_t	__exception; /* number of arm exception taken */
	__uint32_t	__fsr; /* Fault status */
	__uint32_t	__far; /* Virtual Fault Address */
};
#else /* !__DARWIN_UNIX03 */
#define _STRUCT_ARM_EXCEPTION_STATE	struct arm_exception_state
_STRUCT_ARM_EXCEPTION_STATE
{
	__uint32_t	exception; /* number of arm exception taken */
	__uint32_t	fsr; /* Fault status */
	__uint32_t	far; /* Virtual Fault Address */
};
#endif /* __DARWIN_UNIX03 */

#if __DARWIN_UNIX03
#define _STRUCT_ARM_EXCEPTION_STATE64	struct __darwin_arm_exception_state64
_STRUCT_ARM_EXCEPTION_STATE64
{
	__uint64_t	__far; /* Virtual Fault Address */
	__uint32_t	__esr; /* Exception syndrome */
	__uint32_t	__exception; /* number of arm exception taken */
};
#else /* !__DARWIN_UNIX03 */
#define _STRUCT_ARM_EXCEPTION_STATE64	struct arm_exception_state64
_STRUCT_ARM_EXCEPTION_STATE64
{
	__uint64_t	far; /* Virtual Fault Address */
	__uint32_t	esr; /* Exception syndrome */
	__uint32_t	exception; /* number of arm exception taken */
};
#endif /* __DARWIN_UNIX03 */

#if __DARWIN_UNIX03
#define _STRUCT_ARM_THREAD_STATE	struct __darwin_arm_thread_state
_STRUCT_ARM_THREAD_STATE
{
	__uint32_t	__r[13];	/* General purpose register r0-r12 */
	__uint32_t	__sp;		/* Stack pointer r13 */
	__uint32_t	__lr;		/* Link register r14 */
	__uint32_t	__pc;		/* Program counter r15 */
	__uint32_t	__cpsr;		/* Current program status register */
};
#else /* !__DARWIN_UNIX03 */
#define _STRUCT_ARM_THREAD_STATE	struct arm_thread_state
_STRUCT_ARM_THREAD_STATE
{
	__uint32_t	r[13];	/* General purpose register r0-r12 */
	__uint32_t	sp;		/* Stack pointer r13 */
	__uint32_t	lr;		/* Link register r14 */
	__uint32_t	pc;		/* Program counter r15 */
	__uint32_t	cpsr;		/* Current program status register */
};
#endif /* __DARWIN_UNIX03 */

#if __DARWIN_UNIX03
#define _STRUCT_ARM_THREAD_STATE64	struct __darwin_arm_thread_state64
_STRUCT_ARM_THREAD_STATE64
{
	__uint64_t    __x[29];	/* General purpose registers x0-x28 */
	__uint64_t    __fp;		/* Frame pointer x29 */
	__uint64_t    __lr;		/* Link register x30 */
	__uint64_t    __sp;		/* Stack pointer x31 */
	__uint64_t    __pc;		/* Program counter */
	__uint32_t    __cpsr;	/* Current program status register */
	__uint32_t    __pad;    /* Same size for 32-bit or 64-bit clients */
};
#else /* !__DARWIN_UNIX03 */
#define _STRUCT_ARM_THREAD_STATE64	struct arm_thread_state64
_STRUCT_ARM_THREAD_STATE64
{
	__uint64_t    x[29];	/* General purpose registers x0-x28 */
	__uint64_t    fp;		/* Frame pointer x29 */
	__uint64_t    lr;		/* Link register x30 */
	__uint64_t    sp;		/* Stack pointer x31 */
	__uint64_t    pc; 		/* Program counter */
	__uint32_t    cpsr;		/* Current program status register */
	__uint32_t    __pad;    /* Same size for 32-bit or 64-bit clients */
};
#endif /* __DARWIN_UNIX03 */

#if __DARWIN_UNIX03
#define _STRUCT_ARM_VFP_STATE		struct __darwin_arm_vfp_state
_STRUCT_ARM_VFP_STATE
{
	__uint32_t        __r[64];
	__uint32_t        __fpscr;

};
#else /* !__DARWIN_UNIX03 */
#define _STRUCT_ARM_VFP_STATE	struct arm_vfp_state
_STRUCT_ARM_VFP_STATE
{
	__uint32_t        r[64];
	__uint32_t        fpscr;
};
#endif /* __DARWIN_UNIX03 */

#if __DARWIN_UNIX03
#define _STRUCT_ARM_NEON_STATE64	struct __darwin_arm_neon_state64
#define _STRUCT_ARM_NEON_STATE		struct __darwin_arm_neon_state

#if defined(__arm64__)
_STRUCT_ARM_NEON_STATE64
{
	__uint128_t       __v[32];
	__uint32_t        __fpsr;
	__uint32_t        __fpcr;
};

_STRUCT_ARM_NEON_STATE
{
	__uint128_t       __v[16];
	__uint32_t        __fpsr;
	__uint32_t        __fpcr;
};

#elif defined(__arm__)
/*
 * No 128-bit intrinsic for ARM; leave it opaque for now.
 */
_STRUCT_ARM_NEON_STATE64
{
	char opaque[(32 * 16) + (2 * sizeof(__uint32_t))];
} __attribute__((aligned(16)));

_STRUCT_ARM_NEON_STATE
{
	char opaque[(16 * 16) + (2 * sizeof(__uint32_t))];
} __attribute__((aligned(16)));

#else
#error Unknown architecture.
#endif

#else /* !__DARWIN_UNIX03 */
#define _STRUCT_ARM_NEON_STATE64 struct arm_neon_state64
#define _STRUCT_ARM_NEON_STATE struct arm_neon_state

#if defined(__arm64__)
_STRUCT_ARM_NEON_STATE64
{
	__uint128_t		q[32];
	uint32_t		fpsr;
	uint32_t		fpcr;

};
_STRUCT_ARM_NEON_STATE
{
	__uint128_t		q[16];
	uint32_t		fpsr;
	uint32_t		fpcr;

};
#elif defined(__arm__)
/*
 * No 128-bit intrinsic for ARM; leave it opaque for now.
 */
_STRUCT_ARM_NEON_STATE64
{
	char opaque[(32 * 16) + (2 * sizeof(__uint32_t))];
} __attribute__((aligned(16)));

_STRUCT_ARM_NEON_STATE
{
	char opaque[(16 * 16) + (2 * sizeof(__uint32_t))];
} __attribute__((aligned(16)));

#else
#error Unknown architecture.
#endif

#endif /* __DARWIN_UNIX03 */

/*
 * Debug State
 */
#if defined(__arm__)
/* Old-fashioned debug state is only for ARM */

#if __DARWIN_UNIX03
#define _STRUCT_ARM_DEBUG_STATE	struct __darwin_arm_debug_state
_STRUCT_ARM_DEBUG_STATE
{
	__uint32_t        __bvr[16];
	__uint32_t        __bcr[16];
	__uint32_t        __wvr[16];
	__uint32_t        __wcr[16];
};
#else /* !__DARWIN_UNIX03 */
#define _STRUCT_ARM_DEBUG_STATE	struct arm_debug_state
_STRUCT_ARM_DEBUG_STATE
{
	__uint32_t        bvr[16];
	__uint32_t        bcr[16];
	__uint32_t        wvr[16];
	__uint32_t        wcr[16];
};
#endif /* __DARWIN_UNIX03 */

#elif defined(__arm64__)

/* ARM's arm_debug_state is ARM64's arm_legacy_debug_state */

#if __DARWIN_UNIX03
#define _STRUCT_ARM_LEGACY_DEBUG_STATE	struct arm_legacy_debug_state
_STRUCT_ARM_LEGACY_DEBUG_STATE
{
	__uint32_t        __bvr[16];
	__uint32_t        __bcr[16];
	__uint32_t        __wvr[16];
	__uint32_t        __wcr[16];
};
#else /* __DARWIN_UNIX03 */
#define _STRUCT_ARM_LEGACY_DEBUG_STATE	struct arm_legacy_debug_state
_STRUCT_ARM_LEGACY_DEBUG_STATE
{
	__uint32_t        bvr[16];
	__uint32_t        bcr[16];
	__uint32_t        wvr[16];
	__uint32_t        wcr[16];
};
#endif /* __DARWIN_UNIX03 */
#else
#error unknown architecture
#endif

#if __DARWIN_UNIX03
#define _STRUCT_ARM_DEBUG_STATE32	struct __darwin_arm_debug_state32
_STRUCT_ARM_DEBUG_STATE32
{
	__uint32_t        __bvr[16];
	__uint32_t        __bcr[16];
	__uint32_t        __wvr[16];
	__uint32_t        __wcr[16];
	__uint64_t	  __mdscr_el1; /* Bit 0 is SS (Hardware Single Step) */
};

#define _STRUCT_ARM_DEBUG_STATE64	struct __darwin_arm_debug_state64
_STRUCT_ARM_DEBUG_STATE64
{
	__uint64_t        __bvr[16];
	__uint64_t        __bcr[16];
	__uint64_t        __wvr[16];
	__uint64_t        __wcr[16];
	__uint64_t	  __mdscr_el1; /* Bit 0 is SS (Hardware Single Step) */
};
#else /* !__DARWIN_UNIX03 */
#define _STRUCT_ARM_DEBUG_STATE32	struct arm_debug_state32
_STRUCT_ARM_DEBUG_STATE32
{
	__uint32_t        bvr[16];
	__uint32_t        bcr[16];
	__uint32_t        wvr[16];
	__uint32_t        wcr[16];
	__uint64_t	  mdscr_el1; /* Bit 0 is SS (Hardware Single Step) */
};

#define _STRUCT_ARM_DEBUG_STATE64	struct arm_debug_state64
_STRUCT_ARM_DEBUG_STATE64
{
	__uint64_t        bvr[16];
	__uint64_t        bcr[16];
	__uint64_t        wvr[16];
	__uint64_t        wcr[16];
	__uint64_t	  mdscr_el1; /* Bit 0 is SS (Hardware Single Step) */
};
#endif /* __DARWIN_UNIX03 */

#endif /* _MACH_ARM__STRUCTS_H_ */
