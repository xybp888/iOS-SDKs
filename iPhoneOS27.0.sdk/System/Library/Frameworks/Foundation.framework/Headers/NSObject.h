/*	NSObject.h
	Copyright (c) 1994-2019, Apple Inc. All rights reserved.
*/

#import <objc/NSObject.h>
#import <Foundation/NSObjCRuntime.h>
#import <Foundation/NSZone.h>

@class NSInvocation, NSMethodSignature, NSCoder, NSString, NSEnumerator;
@class Protocol;

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

/* **************	Basic protocols		***************/

/// A protocol that objects adopt to provide functional copies of themselves.
///
/// The exact meaning of "copy" can vary from class to class, but a copy must be a functionally independent object with values identical to the original at the time the copy was made. A copy produced with ``NSCopying`` is implicitly retained by the sender, who is responsible for releasing it.
///
/// ``NSCopying`` declares one method, ``copy(with:)``, but copying is commonly invoked with the convenience method <doc://com.apple.documentation/documentation/objectivec/nsobject-swift.class/copy()>. The <doc://com.apple.documentation/documentation/objectivec/nsobject-swift.class/copy()> method is defined for all objects inheriting from <doc://com.apple.documentation/documentation/objectivec/nsobject-swift.class> and simply invokes ``copy(with:)`` with the default zone.
///
/// Your options for implementing this protocol are as follows:
///
/// - Implement ``NSCopying`` using <doc://com.apple.documentation/documentation/objectivec/nsobject-swift.class/alloc> and `init...` in classes that don't inherit ``copy(with:)``.
/// - Implement ``NSCopying`` by invoking the superclass's ``copy(with:)`` when `NSCopying` behavior is inherited. If the superclass implementation might use the ``NSCopyObject`` function, make explicit assignments to pointer instance variables for retained objects.
/// - Implement ``NSCopying`` by retaining the original instead of creating a new copy when the class and its contents are immutable.
///
/// If a subclass inherits ``NSCopying`` from its superclass and declares additional instance variables, the subclass has to override ``copy(with:)`` to properly handle its own instance variables, invoking the superclass's implementation first.
@protocol NSCopying

/// Returns a new instance that's a copy of the receiver.
- (id)copyWithZone:(nullable NSZone *)zone;

@end

/// A protocol that mutable objects adopt to provide functional copies of themselves.
///
/// The ``NSMutableCopying`` protocol declares a method for providing mutable copies of an object. Only classes that define an "immutable vs. mutable" distinction should adopt this protocol. Classes that don't define such a distinction should adopt ``NSCopying`` instead.
///
/// ``NSMutableCopying`` declares one method, ``mutableCopy(with:)``, but mutable copying is commonly invoked with the convenience method <doc://com.apple.documentation/documentation/objectivec/nsobject-swift.class/mutablecopy()>. The <doc://com.apple.documentation/documentation/objectivec/nsobject-swift.class/mutablecopy()> method is defined for all NSObjects and simply invokes ``mutableCopy(with:)`` with the default zone.
///
/// If a subclass inherits ``NSMutableCopying`` from its superclass and declares additional instance variables, the subclass has to override ``mutableCopy(with:)`` to properly handle its own instance variables, invoking the superclass's implementation first.
@protocol NSMutableCopying

/// Returns a new instance that's a mutable copy of the receiver.
- (id)mutableCopyWithZone:(nullable NSZone *)zone;

@end

/// A protocol that enables an object to be encoded and decoded for archiving and distribution.
///
/// The `NSCoding` protocol declares the two methods that a class must implement so that instances of that class can be encoded and decoded. This capability provides the basis for archiving (where objects and other structures are stored on disk) and distribution (where objects are copied to different address spaces).
///
/// In keeping with object-oriented design principles, an object being encoded or decoded is responsible for encoding and decoding its instance variables. A coder instructs the object to do so by invoking ``encode(with:)`` or ``init(coder:)``. ``encode(with:)`` instructs the object to encode its instance variables to the coder provided; an object can receive this method any number of times. ``init(coder:)`` instructs the object to initialize itself from data in the coder provided; as such, it replaces any other initialization method and is sent only once per object. Any object class that should be codeable must adopt the `NSCoding` protocol and implement its methods.
///
/// It is important to consider the possible types of archiving that a coder supports. In macOS 10.2 and later, keyed archiving is preferred. You may, however, need to support classic archiving. For details, see [Archives and Serializations Programming Guide](https://developer.apple.com/library/archive/documentation/Cocoa/Conceptual/Archiving/Archiving.html#//apple_ref/doc/uid/10000047i).
@protocol NSCoding
/// Encodes the receiver using a given archiver.
- (void)encodeWithCoder:(NSCoder *)coder;
/// Initializes the receiver from data in a given unarchiver.
- (nullable instancetype)initWithCoder:(NSCoder *)coder; // NS_DESIGNATED_INITIALIZER
@end

/// A protocol that enables encoding and decoding in a manner that is robust against object substitution attacks.
///
/// Objects which are safe to be encoded and decoded across privilege boundaries should adopt `NSSecureCoding` instead of `NSCoding`. Secure coders (those that respond `YES` to `requiresSecureCoding`) will only encode objects that adopt the `NSSecureCoding` protocol.
///
/// `NSSecureCoding` guarantees only that an archive contains the classes it claims. It makes no guarantees about the suitability for consumption by the receiver of the decoded content of the archive.
@protocol NSSecureCoding <NSCoding>
@required
/// A Boolean value that indicates whether this class supports secure coding.
///
/// This property must return `YES` on all classes that allow secure coding. Subclasses of classes that adopt `NSSecureCoding` and override `initWithCoder:` must also override this property and return `YES`.
@property (class, readonly) BOOL supportsSecureCoding;
@end

/* **********	Base class		***********/

@interface NSObject (NSCoderMethods)
+ (NSInteger)version;
+ (void)setVersion:(NSInteger)aVersion;
@property (readonly) Class classForCoder;
- (nullable id)replacementObjectForCoder:(NSCoder *)coder;
- (nullable id)awakeAfterUsingCoder:(NSCoder *)coder NS_REPLACES_RECEIVER;
@end

#if TARGET_OS_OSX
@interface NSObject (NSDeprecatedMethods)

+ (void)poseAsClass:(Class)aClass API_DEPRECATED("Posing no longer supported", macos(10.0,10.5), ios(2.0,2.0), watchos(2.0,2.0), tvos(9.0,9.0))
#if __OBJC2__
UNAVAILABLE_ATTRIBUTE
#endif
;

@end
#endif


/* **********	Discardable Content		***********/

/// You implement this protocol when a class's objects have subcomponents that can be discarded when not being used, thereby giving an application a smaller memory footprint.
///
/// An `NSDiscardableContent` object's life cycle is dependent upon a "counter" variable. An `NSDiscardableContent` object is a purgeable block of memory that keeps track of whether or not it is currently being used by some other object. When this memory is being read, or is still needed, its counter variable will be greater than or equal to 1. When it is not being used, and can be discarded, the counter variable will be equal to 0.
///
/// When the counter is equal to 0, the block of memory may be discarded if memory is tight at that point in time. In order to discard the content, call ``discardContentIfPossible()`` on the object, which will free the associated memory if the counter variable equals 0.
///
/// By default, `NSDiscardableContent` objects are initialized with their counter equal to 1 to ensure that they are not immediately discarded by the memory-management system. From this point, you must keep track of the counter variable's state. Calling the ``beginContentAccess()`` method increments the counter variable by 1, thus ensuring that the object will not be discarded. When you no longer need the object, decrement its counter by calling ``endContentAccess()``.
///
/// The Foundation framework includes the ``NSPurgeableData`` class, which provides a default implementation of this protocol.
@protocol NSDiscardableContent
@required
/// Called to access the content, incrementing the access counter.
- (BOOL)beginContentAccess;
/// Called when the content is no longer being accessed, decrementing the access counter.
- (void)endContentAccess;
/// Called to discard the content if the access counter is zero.
- (void)discardContentIfPossible;
/// Returns a Boolean value indicating whether the content has been discarded.
- (BOOL)isContentDiscarded;
@end

@interface NSObject (NSDiscardableContentProxy)
@property (readonly, retain) id autoContentAccessingProxy API_AVAILABLE(macos(10.6), ios(4.0), watchos(2.0), tvos(9.0));
@end

/* **********	Object Allocation / Deallocation		*******/

/// Creates and returns a new instance of a given class.
// For ARC code that needs this functionality, consider using class_createInstance directly.
FOUNDATION_EXPORT id NSAllocateObject(Class aClass, NSUInteger extraBytes, NSZone * _Nullable zone) NS_AUTOMATED_REFCOUNT_UNAVAILABLE;

/// Destroys an existing object.
FOUNDATION_EXPORT void NSDeallocateObject(id object) NS_AUTOMATED_REFCOUNT_UNAVAILABLE;

/// Creates an exact copy of an object.
FOUNDATION_EXPORT id NSCopyObject(id object, NSUInteger extraBytes, NSZone * _Nullable zone) NS_AUTOMATED_REFCOUNT_UNAVAILABLE API_DEPRECATED("Not supported", macos(10.0,10.8), ios(2.0,6.0), watchos(2.0,2.0), tvos(9.0,9.0));

/// Indicates whether an object should be retained.
FOUNDATION_EXPORT BOOL NSShouldRetainWithZone(id anObject, NSZone * _Nullable requestedZone) NS_AUTOMATED_REFCOUNT_UNAVAILABLE;

/// Increments the specified object's reference count.
FOUNDATION_EXPORT void NSIncrementExtraRefCount(id object) NS_AUTOMATED_REFCOUNT_UNAVAILABLE;

/// Decrements the specified object's reference count.
FOUNDATION_EXPORT BOOL NSDecrementExtraRefCountWasZero(id object) NS_AUTOMATED_REFCOUNT_UNAVAILABLE;

/// Returns the specified object's reference count.
FOUNDATION_EXPORT NSUInteger NSExtraRefCount(id object) NS_AUTOMATED_REFCOUNT_UNAVAILABLE;

#if __has_feature(objc_arc)

/// Casts an Objective-C pointer to a Core Foundation pointer and also transfers ownership to the caller.
///
/// You use this function to cast an Objective-C object as Core Foundation-style object and take ownership of the object so that you can manage its lifetime. You are responsible for subsequently releasing the object, as illustrated in this example:
///
/// ```objc
/// NSString *string = <Get a string>;
/// CFStringRef cfString = (CFStringRef)CFBridgingRetain(string);
/// // Use the CF string.
/// CFRelease(cfString);
/// ```
///
/// - Parameter X: An Objective-C object.
/// - Returns: `X` cast as a `CFTypeRef` and retained.
// After using a CFBridgingRetain on an NSObject, the caller must take responsibility for calling CFRelease at an appropriate time.
NS_INLINE CF_RETURNS_RETAINED CFTypeRef _Nullable CFBridgingRetain(id _Nullable X) {
    return (__bridge_retained CFTypeRef)X;
}

/// Moves a non-Objective-C pointer to Objective-C and also transfers ownership to ARC.
///
/// You use this function to cast a Core Foundation-style object as an Objective-C object and transfer ownership of the object to ARC such that you don't have to release the object, as illustrated in this example:
///
/// ```objc
/// CFStringRef cfName = ABRecordCopyValue(person, kABPersonFirstNameProperty);
/// NSString *name = (NSString *)CFBridgingRelease(cfName);
/// ```
///
/// - Parameter X: A Core Foundation-style object.
/// - Returns: `X` cast as an Objective-C object and managed by ARC.
NS_INLINE id _Nullable CFBridgingRelease(CFTypeRef CF_CONSUMED _Nullable X) {
    return (__bridge_transfer id)X;
}

#else

/// Casts an Objective-C pointer to a Core Foundation pointer and also transfers ownership to the caller.
///
/// You use this function to cast an Objective-C object as Core Foundation-style object and take ownership of the object so that you can manage its lifetime. You are responsible for subsequently releasing the object.
///
/// - Parameter X: An Objective-C object.
/// - Returns: `X` cast as a `CFTypeRef` and retained.
// This function is intended for use while converting to ARC mode only.
NS_INLINE CF_RETURNS_RETAINED CFTypeRef _Nullable CFBridgingRetain(id _Nullable X) {
    return X ? CFRetain((CFTypeRef)X) : NULL;
}

/// Moves a non-Objective-C pointer to Objective-C and also transfers ownership to ARC.
///
/// You use this function to cast a Core Foundation-style object as an Objective-C object and transfer ownership of the object to ARC such that you don't have to release the object.
///
/// - Parameter X: A Core Foundation-style object.
/// - Returns: `X` cast as an Objective-C object and managed by ARC.
// Casts a CoreFoundation object to an Objective-C object, transferring ownership to ARC (ie. no need to CFRelease to balance a prior +1 CFRetain count). NS_RETURNS_RETAINED is used to indicate that the Objective-C object returned has +1 retain count.  So the object is 'released' as far as CoreFoundation reference counting semantics are concerned, but retained (and in need of releasing) in the view of ARC. This function is intended for use while converting to ARC mode only.
NS_INLINE id _Nullable CFBridgingRelease(CFTypeRef CF_CONSUMED _Nullable X) NS_RETURNS_RETAINED {
    return [(id)X autorelease];
}

#endif

NS_HEADER_AUDIT_END(nullability, sendability)
