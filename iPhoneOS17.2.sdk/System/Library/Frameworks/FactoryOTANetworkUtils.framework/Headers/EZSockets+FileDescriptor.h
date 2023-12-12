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
#import <FactoryOTANetworkUtils/EZSocket.h>
#import <FactoryOTANetworkUtils/EZSocketServer.h>

@interface EZSocket(FileDescriptor)


+ (instancetype _Nonnull)socketWithFileDescriptor:(int)fd; /* will not close fd on dealloc */
+ (instancetype _Nonnull)socketWithFileDescriptor:(int)fd closeOnDealloc:(bool)cod;

@end

@interface EZSocketServer(FileDescriptor)

+ (instancetype _Nullable)serverWithFileDescriptor:(int)fd delegate:(id<EZSocketServerDelegate> _Nullable)delegate;

@end



