/*	NSExtensionRequestHandling.h
 Copyright (c) 2013-2019, Apple Inc. All rights reserved.
 */

#import <Foundation/Foundation.h>

#if __OBJC2__
NS_HEADER_AUDIT_BEGIN(nullability, sendability)

@class NSExtensionContext;

/// The interface an app extension uses to respond to a request from a host app.
///
/// The ``NSExtensionRequestHandling`` protocol provides a life cycle hook into an app extension. An extension's principal object can implement this protocol and use ``beginRequest(with:)`` to keep track of the request from a host app.
@protocol NSExtensionRequestHandling <NSObject>

@required

/// Tells the extension to prepare its interface for the requesting context.
- (void)beginRequestWithExtensionContext:(NSExtensionContext *)context;

@end

NS_HEADER_AUDIT_END(nullability, sendability)
#endif
