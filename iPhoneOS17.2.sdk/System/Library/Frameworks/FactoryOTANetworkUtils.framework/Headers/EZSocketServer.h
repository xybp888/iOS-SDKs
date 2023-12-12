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


@class    EZSocket;
@class    EZSocketServer;
@protocol EZSocketSerialization;


typedef NS_OPTIONS(NSUInteger, EZSocketServerOptions) {
    EZSocketServerAcceptUndetached = 1 << 0,  /* Will not detach the accept loop into a separate thread */
};


@protocol EZSocketServerDelegate <NSObject>

/*
 * server:didReceiveConnection: will be invoked from the thread from which start: is called
 * on the server instance, unless the EZSocketServerAcceptUndetached is set, in which case
 * a separate thread is detached and this method will be called from that thread.
 */
- (void)server:(EZSocketServer *_Nonnull)server didReceiveConnection:(EZSocket *_Nonnull)socket;

@end


@interface EZSocketServer : NSObject

/*
 * Currently supported schemes:
 * - tcp://host:port    (Note: For passive TCP sockets, the host in the URL is ignored)  
 * - unix://filepath
 *
 */

+ (instancetype _Nullable)serverWithURL:(NSURL *_Nonnull)url
                               delegate:(id<EZSocketServerDelegate> _Nonnull)delegate
                                  error:(NSError *_Nullable *_Nullable)err;


+ (instancetype _Nullable)serverWithURL:(NSURL *_Nonnull)url
                               delegate:(id<EZSocketServerDelegate> _Nonnull)delegate
                                options:(EZSocketServerOptions)options
                                  error:(NSError *_Nullable *_Nullable)err;

/*
 * listenForConnections:
 * 
 * Opens a passive socket and detaches a thread to accept connections (unless EZSocketServerAcceptUndetached 
 * is set).
 *
 * This is a blocking call if EZSocketServerAcceptUndetached is set.
 */
- (bool)listenForConnections:(NSError *_Nullable *_Nullable)err;


/*
 * accept:
 *
 * This is a blocking call on accept() to accept one connection.
 * Cannot be used if listenForConnections: has been called already.
 */
- (EZSocket *_Nullable)accept:(NSError *_Nullable *_Nullable)error;


/*
 * Shuts down the accept loop
 */
- (void)shutdown;

@property (nonnull,readonly) NSURL *url;
@property (nullable, weak) id<EZSocketServerDelegate> delegate;

@end
