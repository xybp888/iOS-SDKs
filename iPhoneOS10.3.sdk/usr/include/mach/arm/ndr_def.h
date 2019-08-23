/*
 * Copyright (c) 2000-2007 Apple Inc. All rights reserved.
 */
/*
 * @OSF_COPYRIGHT@
 */

/* NDR record for Intel x86s */

#include <mach/ndr.h>

NDR_record_t NDR_record = {
	0,			/* mig_reserved */
	0,			/* mig_reserved */
	0,			/* mig_reserved */
	NDR_PROTOCOL_2_0,		
	NDR_INT_LITTLE_ENDIAN,
	NDR_CHAR_ASCII,
	NDR_FLOAT_IEEE,
	0,
};
