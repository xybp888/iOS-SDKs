/*
 * Copyright (c) 2023 Apple Inc.
 * All rights reserved.
 */

#ifndef __NE_INDIRECT__
#error "Please import the NetworkExtension module instead of this file directly."
#endif

#import <NetworkExtension/NEProvider.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 * @file NEFailureHandlerProvider.h
 * @discussion This file declares the NEFailureHandlerProvider API. The NEFailureHandlerProvider API declares the base class for Network Extension providers that handle errors.
 *
 * This API is part of NetworkExtension.framework
 */
API_AVAILABLE(macos(14.0), ios(17.0)) API_UNAVAILABLE(tvos, watchos)
@interface NEFailureHandlerProvider : NEProvider

/*!
 * @method handleFailure:completionHandler:
 * @discussion This method is called by the framework when some other provider in the same containing app repeatedly fails to start or connect. For example, when a VPN provider repeatedly fails to connect this method will be called to handle the failure. Subclasses must override this method to perform necessary tasks, for example notify the user of the failure or modify the configuration to fix the failure.
 * @param error An NSError containing details about the failure.
 * @param completionHandler A block that must be called when the error has been handled.
 */
- (void)handleFailure:(NSError *)error completionHandler:(void (^)(void))completionHandler API_AVAILABLE(macos(14.0), ios(17.0)) API_UNAVAILABLE(tvos, watchos);

@end

NS_ASSUME_NONNULL_END
