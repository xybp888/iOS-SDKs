/*	NSInvocation.h
	Copyright (c) 1994-2019, Apple Inc. All rights reserved.
*/

#import <Foundation/NSObject.h>

@class NSMethodSignature;

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

/// An Objective-C message rendered as an object.
///
/// ``NSInvocation`` objects are used to store and forward messages between objects and between applications, primarily by ``Timer`` objects and the distributed objects system. An ``NSInvocation`` object contains all the elements of an Objective-C message: a target, a selector, arguments, and the return value. Each of these elements can be set directly, and the return value is set automatically when the ``NSInvocation`` object is dispatched.
///
/// An ``NSInvocation`` object can be repeatedly dispatched to different targets; its arguments can be modified between dispatch for varying results; even its selector can be changed to another with the same method signature (argument and return types). This flexibility makes ``NSInvocation`` useful for repeating messages with many arguments and variations; rather than retyping a slightly different expression for each message, you modify the ``NSInvocation`` object as needed each time before dispatching it to a new target.
///
/// ``NSInvocation`` does not support invocations of methods with either variable numbers of arguments or `union` arguments. You should use the ``invocationWithMethodSignature:`` class method to create ``NSInvocation`` objects; you should not create these objects using <doc://com.apple.documentation/documentation/objectivec/nsobject-swift.class/alloc> and <doc://com.apple.documentation/documentation/objectivec/nsobject-swift.class/init()>.
///
/// This class does not retain the arguments for the contained invocation by default. If those objects might disappear between the time you create your instance of ``NSInvocation`` and the time you use it, you should explicitly retain the objects yourself or invoke the ``retainArguments`` method to have the invocation object retain them itself.
///
/// > Note:
/// > ``NSInvocation`` conforms to the ``NSCoding`` protocol, but only supports coding by an ``NSPortCoder``. ``NSInvocation`` does not support archiving.
NS_SWIFT_UNAVAILABLE("NSInvocation and related APIs not available")
@interface NSInvocation : NSObject

/// Returns an `NSInvocation` object able to construct messages using a given method signature.
///
/// The new object must have its selector set and its arguments set with `setArgument:atIndex:` before it can be invoked. Do not use the `alloc`/`init` approach to create `NSInvocation` objects.
///
/// - Parameter sig: An object encapsulating a method signature.
+ (NSInvocation *)invocationWithMethodSignature:(NSMethodSignature *)sig;

/// The receiver's method signature.
@property (readonly, retain) NSMethodSignature *methodSignature;

/// If the receiver hasn't already done so, retains the target and all object arguments of the receiver and copies all of its C-string arguments and blocks.
///
/// For efficiency, newly created `NSInvocation` objects don't retain or copy their arguments, nor do they retain their targets, copy C strings, or copy any associated blocks. You should instruct an `NSInvocation` object to retain its arguments if you intend to cache it, because the arguments may otherwise be released before the invocation is invoked.
- (void)retainArguments;
/// A Boolean value that indicates if the receiver has retained its arguments.
@property (readonly) BOOL argumentsRetained;

/// The receiver's target, or `nil` if the receiver has no target.
///
/// The target is the receiver of the message sent by `invoke`.
@property (nullable, assign) id target;
/// The receiver's selector, or 0 if it hasn't been set.
@property SEL selector;

/// Gets the invocation's return value.
///
/// - Parameter retLoc: An untyped buffer into which the invocation copies its return value. It should be large enough to accommodate the value.
- (void)getReturnValue:(void *)retLoc;
/// Sets the receiver's return value.
///
/// This value is normally set when you send an `invoke` or `invokeWithTarget:` message.
///
/// - Parameter retLoc: An untyped buffer whose contents are copied as the receiver's return value.
- (void)setReturnValue:(void *)retLoc;

/// Returns by indirection the receiver's argument at a specified index.
///
/// Indices 0 and 1 indicate the hidden arguments `self` and `_cmd`, respectively; these values can be retrieved directly with the `target` and `selector` properties. Use indices 2 and greater for the arguments normally passed in a message.
///
/// - Parameter argumentLocation: An untyped buffer to hold the returned argument.
/// - Parameter idx: An integer specifying the index of the argument to get.
- (void)getArgument:(void *)argumentLocation atIndex:(NSInteger)idx;
/// Sets an argument of the receiver.
///
/// Indices 0 and 1 indicate the hidden arguments `self` and `_cmd`, respectively; you should set these values directly with the `target` and `selector` properties. Use indices 2 and greater for the arguments normally passed in a message.
///
/// - Parameter argumentLocation: An untyped buffer containing an argument to be assigned to the receiver.
/// - Parameter idx: An integer specifying the index of the argument.
- (void)setArgument:(void *)argumentLocation atIndex:(NSInteger)idx;

/// Sends the receiver's message (with arguments) to its target and sets the return value.
///
/// You must set the receiver's target, selector, and argument values before calling this method.
- (void)invoke;
/// Sets the receiver's target, sends the receiver's message (with arguments) to that target, and sets the return value.
///
/// You must set the receiver's selector and argument values before calling this method.
///
/// - Parameter target: The object to set as the receiver's target.
- (void)invokeWithTarget:(id)target;
- (void)invokeUsingIMP:(IMP)imp;
@end


#if TARGET_OS_OSX
#if MAC_OS_X_VERSION_MAX_ALLOWED <= MAC_OS_X_VERSION_10_5

enum _NSObjCValueType {
    NSObjCNoType = 0,
    NSObjCVoidType = 'v',
    NSObjCCharType = 'c',
    NSObjCShortType = 's',
    NSObjCLongType = 'l',
    NSObjCLonglongType = 'q',
    NSObjCFloatType = 'f',
    NSObjCDoubleType = 'd',
    NSObjCBoolType = 'B',
    NSObjCSelectorType = ':',
    NSObjCObjectType = '@',
    NSObjCStructType = '{',
    NSObjCPointerType = '^',
    NSObjCStringType = '*',
    NSObjCArrayType = '[',
    NSObjCUnionType = '(',
    NSObjCBitfield = 'b'
} API_DEPRECATED("Not supported", macos(10.0,10.5), ios(2.0,2.0), watchos(2.0,2.0), tvos(9.0,9.0));

typedef struct {
    NSInteger type API_DEPRECATED("Not supported", macos(10.0,10.5), ios(2.0,2.0), watchos(2.0,2.0), tvos(9.0,9.0));
    union {
    	char charValue;
	short shortValue;
	long longValue;
	long long longlongValue;
	float floatValue;
	double doubleValue;
	bool boolValue;
	SEL selectorValue;
	id objectValue;
	void *pointerValue;
	void *structLocation;
	char *cStringLocation;
    } value API_DEPRECATED("Not supported", macos(10.0,10.5), ios(2.0,2.0), watchos(2.0,2.0), tvos(9.0,9.0));
} NSObjCValue API_DEPRECATED("Not supported", macos(10.0,10.5), ios(2.0,2.0), watchos(2.0,2.0), tvos(9.0,9.0));

#endif
#endif

NS_HEADER_AUDIT_END(nullability, sendability)
