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

NS_ASSUME_NONNULL_BEGIN

@protocol EZSocketSerialization;

@interface EZSocket : NSObject

/*
 * socketWithURL:error:
 * 
 * Opens an active socket connection according to the URL.
 * Currently supported schemes:
 * - tcp://host:port
 * - unix://filepath
 */
+ (instancetype _Nullable)socketWithURL:(NSURL *)url error:(NSError **)error;

/*
 * sendMessage:error:
 *
 * Serializes a message and sends synchronously (internally calls sendData:error:)
 * Serializes using the serializer property if set, otherwise uses a default serialization (with NSKeyedArchiver and NSKeyedUnarchiver).
 * This method can be called from multiple threads.
 */
- (bool)sendMessage:(NSDictionary *)msg error:(NSError **)err;

/*
 * receiveMessage:
 *
 * Blocking call that receives one deserialized message (internally calls receiveData:)
 */
- (NSDictionary *_Nullable)receiveMessage:(NSError **)err;
/*
 * receiveMessageWithTimeout:error:
 *
 * Same as receiveMessage: but uses select to check if message is received within the specified timeout.
 * A timeout value of < 0 is the same as receiveMessage: which is an indefinite blocking call */
- (NSDictionary *_Nullable)receiveMessageWithTimeout:(NSTimeInterval)timeout error:(NSError **)error;

/*
 * sendData:error:
 *
 * Sends a message in the form of raw bytes synchronously, without serialization. (internally calls write() in unistd.h)
 * This method can be called from multiple threads.
 */
- (bool)sendData:(NSData *)data error:(NSError **)err;

/*
 * receiveData:
 *
 * Blocking call that receives one message in the form of raw bytes. (internally calls read() in unistd.h)
 */
- (NSData *_Nullable)receiveData:(NSError **)err;
/*
 * receiveDataWithTimeout:error:
 *
 * Same as receiveData: but uses select to check if data is received within the specified timeout.
 * A timeout value of < 0 is the same as receiveData: which is an indefinite blocking call */
- (NSData *_Nullable)receiveDataWithTimeout:(NSTimeInterval)timeout error:(NSError **)error;

- (void)close;

@property (strong) id<EZSocketSerialization> serializer;
@property (readonly) int fileDescriptor;
@property (readonly) NSURL *url;
@property (strong) NSString *name;

@end

NS_ASSUME_NONNULL_END
