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

@class EZSocketManager;

typedef NS_OPTIONS(NSUInteger, EZSocketManagerOptions) {
    EZSocketManagerReceiveUndetached = 1 << 0,  /* If set, the listen: method will not detach a thread to receive messages, i.e. becomes blocking */
};

NS_ASSUME_NONNULL_BEGIN

@protocol EZSocketManagerDelegate <NSObject>

- (void)socketManager:(EZSocketManager *)smgr socket:(EZSocket *)socket didReceiveMessage:(NSDictionary *)recvd_message;
- (void)socketManager:(EZSocketManager *)smgr socket:(EZSocket *)socket didDisconnect:(NSError *_Nullable)error;

/*
 * socketManager:socket:shouldDeserializeData
 * 
 * If this optional delegate method is implemented, it will be invoked when data is newly received.
 * The data may be inspected and consumed as desired. The return value indicates to the EZSocketManager instance
 * whether it should deserialize received data to dictionary and invoke the ::didReceiveMessage: method
 */
@optional
- (bool)socketManager:(EZSocketManager *)smgr socket:(EZSocket *)socket shouldDeserializeData:(NSData *)recvd_data;

@end


@interface EZSocketManager : NSObject

+ (instancetype _Nullable)managerWithSocket:(EZSocket *)socket
                                   delegate:(id<EZSocketManagerDelegate>)delegate;

+ (instancetype _Nullable)managerWithSocket:(EZSocket *)socket
                                   delegate:(id<EZSocketManagerDelegate> _Nullable)delegate
                                    options:(EZSocketManagerOptions)options;

+ (instancetype _Nullable)managerWithSocket:(EZSocket *)socket
                                   delegate:(id<EZSocketManagerDelegate> _Nullable)delegate
                                    options:(EZSocketManagerOptions)options
                                      error:(NSError **)error;
/*
 * listen:
 *
 * Starts receiving messages in a loop on the connection. A thread will be detached for the receiving loop
 * (unless EZSocketManagerReceiveUndetached option is set, in which case this is a blocking call)
 */
- (bool)listen:(NSError **)err;

- (void)disconnect;

@property (readonly) EZSocket *socket;
@property (nullable, weak) id<EZSocketManagerDelegate> delegate;

@end

NS_ASSUME_NONNULL_END
