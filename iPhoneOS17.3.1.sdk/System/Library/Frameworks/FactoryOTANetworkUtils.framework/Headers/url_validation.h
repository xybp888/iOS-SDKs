/*
 *
 *	  Copyright (c) 2017 Apple Computer, Inc.
 *	  All rights reserved.
 *
 *	  This document is the property of Apple Computer, Inc. It is
 *	  considered confidential and proprietary information.
 *
 *	  This document may not be reproduced or transmitted in any form,
 *	  in whole or in part, without the express written permission of
 *	  Apple Computer, Inc.
 */

#import <Foundation/Foundation.h>

#if __cplusplus
extern "C" {
#endif


bool validate_listening_url(NSURL *url, NSError **error);
bool validate_connection_url(NSURL *url, NSError **error);


#if __cplusplus
}
#endif

