/*	NSProxy.h
	Copyright (c) 1994-2019, Apple Inc. All rights reserved.
*/

#import <Foundation/NSObject.h>

@class NSMethodSignature, NSInvocation;

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

/// An abstract superclass defining an API for objects that act as stand-ins for other objects or for objects that don't exist yet.
///
/// Typically, a message to a proxy is forwarded to the real object or causes the proxy to load (or transform itself into) the real object. Subclasses of ``NSProxy`` can be used to implement transparent distributed messaging (for example, ``NSDistantObject``) or for lazy instantiation of objects that are expensive to create.
NS_ROOT_CLASS
@interface NSProxy <NSObject> {
    __ptrauth_objc_isa_pointer Class	isa;
}

/// Returns a new, uninitialized instance of the receiving class.
+ (id)alloc;

/// Returns a new, uninitialized instance of the receiving class in the specified memory zone.
+ (id)allocWithZone:(nullable NSZone *)zone NS_AUTOMATED_REFCOUNT_UNAVAILABLE;

/// Returns `self`.
+ (Class)class;

/// Passes a given invocation to the real object the proxy represents.
- (void)forwardInvocation:(NSInvocation *)invocation;

/// Returns an ``NSMethodSignature`` object for a given selector.
- (nullable NSMethodSignature *)methodSignatureForSelector:(SEL)sel NS_SWIFT_UNAVAILABLE("NSInvocation and related APIs not available");

/// Deallocates the memory occupied by the receiver.
- (void)dealloc;

/// The garbage collector invokes this method on the receiver before disposing of the memory it uses.
- (void)finalize;

/// A string containing a human-readable description of the receiver.
@property (readonly, copy) NSString *description;

/// A string containing a human-readable description of the receiver suitable for debugging.
@property (readonly, copy) NSString *debugDescription;

/// Returns a Boolean value that indicates whether the receiving class responds to a given selector.
+ (BOOL)respondsToSelector:(SEL)aSelector;

- (BOOL)allowsWeakReference API_UNAVAILABLE(macos, ios, watchos, tvos);
- (BOOL)retainWeakReference API_UNAVAILABLE(macos, ios, watchos, tvos);

// - (id)forwardingTargetForSelector:(SEL)aSelector;

@end

NS_HEADER_AUDIT_END(nullability, sendability)
