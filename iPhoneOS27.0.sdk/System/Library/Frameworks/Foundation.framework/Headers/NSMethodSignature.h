/*	NSMethodSignature.h
	Copyright (c) 1994-2019, Apple Inc. All rights reserved.
*/

#import <Foundation/NSObject.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

/// A record of the type information for the return value and parameters of a method.
NS_SWIFT_UNAVAILABLE("NSInvocation and related APIs not available")
@interface NSMethodSignature : NSObject

/// Returns an ``NSMethodSignature`` object for the given Objective-C method type string.
+ (nullable NSMethodSignature *)signatureWithObjCTypes:(const char *)types;

/// The number of arguments recorded in the receiver.
@property (readonly) NSUInteger numberOfArguments;

/// Returns the type encoding for the argument at a given index.
- (const char *)getArgumentTypeAtIndex:(NSUInteger)idx NS_RETURNS_INNER_POINTER;

/// The number of bytes required by the receiver to store its arguments on the stack frame.
@property (readonly) NSUInteger frameLength;

/// Returns a Boolean value that indicates whether the receiver is asynchronous (the `oneway` qualifier).
- (BOOL)isOneway;

/// A C string encoding the return type of the method.
@property (readonly) const char *methodReturnType NS_RETURNS_INNER_POINTER;

/// The number of bytes required for the return value.
@property (readonly) NSUInteger methodReturnLength;

@end

NS_HEADER_AUDIT_END(nullability, sendability)
