/*
 * Copyright (c) 2007 Apple Inc. All rights reserved.
 */
/*
 * FILE_ID: processor_info.h
 */

#ifndef _MACH_ARM_PROCESSOR_INFO_H_
#define _MACH_ARM_PROCESSOR_INFO_H_

#define PROCESSOR_CPU_STAT	0x10000003	/* Low level cpu statistics */

struct processor_cpu_stat {
	uint32_t	irq_ex_cnt;
	uint32_t	ipi_cnt;
	uint32_t	timer_cnt;
	uint32_t	undef_ex_cnt;
	uint32_t	unaligned_cnt;
	uint32_t	vfp_cnt;
	uint32_t	vfp_shortv_cnt;
	uint32_t	data_ex_cnt;
	uint32_t	instr_ex_cnt;
};

typedef	struct processor_cpu_stat	processor_cpu_stat_data_t;
typedef struct processor_cpu_stat	*processor_cpu_stat_t;
#define PROCESSOR_CPU_STAT_COUNT	((mach_msg_type_number_t) \
		(sizeof(processor_cpu_stat_data_t)/sizeof(natural_t)))


#endif /* _MACH_ARM_PROCESSOR_INFO_H_ */
