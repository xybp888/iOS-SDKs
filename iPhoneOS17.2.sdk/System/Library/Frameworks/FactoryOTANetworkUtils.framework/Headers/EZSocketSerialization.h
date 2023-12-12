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

@protocol EZSocketSerialization <NSObject>

- (NSData *_Nullable)dataWithDictionary:(NSDictionary *_Nonnull)dictionary error:(NSError *_Nullable *_Nullable)error;
- (NSDictionary *_Nullable)dictionaryWithData:(NSData *_Nonnull)data error:(NSError *_Nullable *_Nullable)error;

@property (nonnull, readonly) NSString *formatName;

@end
