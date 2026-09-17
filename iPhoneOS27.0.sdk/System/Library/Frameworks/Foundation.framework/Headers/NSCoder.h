/*	NSCoder.h
	Copyright (c) 1993-2019, Apple Inc. All rights reserved.
*/

#import <Foundation/NSObject.h>

@class NSString, NSData, NSSet<ObjectType>;

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

/// Policies describing the action the coder should take when encountering decode failures.
typedef NS_ENUM(NSInteger, NSDecodingFailurePolicy) {
    /// A failure policy that directs the coder to raise an exception.
    ///
    /// With this policy, the `NSCoder` raises an exception internally to propagate failure messages (and unwind the stack). This exception can be transformed into an `NSError` via any of the TopLevel decode APIs.
    NSDecodingFailurePolicyRaiseException,

    /// A failure policy that directs the coder to capture the failure as an error object.
    ///
    /// On decode failure, the `NSCoder` will capture the failure as an `NSError`, and prevent further decodes (by returning `0` / `nil` equivalent as appropriate). Use this policy if you know that all encoded objects use `failWithError:` to communicate decode failures and don't raise exceptions for error propagation.
    NSDecodingFailurePolicySetErrorAndReturn,
} API_AVAILABLE(macos(10.11), ios(9.0), watchos(2.0), tvos(9.0));

/// An abstract class that serves as the basis for objects that enable archiving and distribution of other objects.
///
/// ``NSCoder`` declares the interface used by concrete subclasses to transfer objects and other values between memory and some other format. This capability provides the basis for archiving (storing objects and data on disk) and distribution (copying objects and data items between different processes or threads). The concrete subclasses provided by Foundation for these purposes are ``NSArchiver``, ``NSUnarchiver``, ``NSKeyedArchiver``, ``NSKeyedUnarchiver``, and ``NSPortCoder``. Concrete subclasses of ``NSCoder`` are "coder classes", and instances of these classes are "coder objects" (or simply "coders"). A coder that can only encode values is an "encoder", and one that can only decode values is a "decoder".
///
/// ``NSCoder`` operates on objects, scalars, C arrays, structures, strings, and on pointers to these types. It doesn't handle types whose implementation varies across platforms, such as `union`, `void *`, function pointers, and long chains of pointers. A coder stores object type information along with the data, so an object decoded from a stream of bytes is normally of the same class as the object that was originally encoded into the stream. An object can change its class when encoded, however; this is described in [Archives and Serializations Programming Guide](https://developer.apple.com/library/archive/documentation/Cocoa/Conceptual/Archiving/Archiving.html#//apple_ref/doc/uid/10000047i).
///
/// The AVFoundation framework adds methods to the ``NSCoder`` class to make it easier to create archives including Core Media time structures, and extract Core Media time structure from archives.
///
/// ### Subclassing Notes
///
/// For details of how to create a subclass of `NSCoder`, see [Subclassing NSCoder](https://developer.apple.com/library/archive/documentation/Cocoa/Conceptual/Archiving/Articles/subclassing.html#//apple_ref/doc/uid/20000951) in [Archives and Serializations Programming Guide](https://developer.apple.com/library/archive/documentation/Cocoa/Conceptual/Archiving/Archiving.html#//apple_ref/doc/uid/10000047i).
@interface NSCoder : NSObject

/// Encodes a value of the given type at the given address.
///
/// Subclasses must override this method, and match it with a subsequent ``decodeValueOfObjCType:at:size:`` message.
/// When calling this method, `type` must contain exactly one type code.
/// You should not use this method to encode Objective-C objects.
- (void)encodeValueOfObjCType:(const char *)type at:(const void *)addr;

/// Encodes a given data object.
///
/// Subclasses must override this method. This method must be matched by a subsequent ``decodeDataObject`` message.
- (void)encodeDataObject:(NSData *)data;

/// Decodes and returns an `NSData` object that was previously encoded with ``encodeDataObject:``.
///
/// Subclasses must override this method.
- (nullable NSData *)decodeDataObject;

/// Decodes a single value of a known type from the specified data buffer.
///
/// The `type` parameter must contain exactly one type code, and the buffer specified by `data` must be large enough to hold the value corresponding to that type code.
/// Subclasses must override this method and provide an implementation to decode the value.
/// This method matches an ``encodeValueOfObjCType:at:`` message used during encoding.
- (void)decodeValueOfObjCType:(const char *)type at:(void *)data size:(NSUInteger)size API_AVAILABLE(macos(10.13), ios(11.0), watchos(4.0), tvos(11.0));

/// This method is present for historical reasons and is not used with keyed archivers.
///
/// - Returns: The version in effect for the class named `className` or `NSNotFound` if no class named `className` exists.
- (NSInteger)versionForClassName:(NSString *)className;
@end

@interface NSCoder (NSExtendedCoder)

/// Encodes an object.
///
/// `NSCoder`'s implementation simply invokes ``encodeValueOfObjCType:at:`` to encode `object`. Subclasses can override this method to encode a reference to `object` instead of `object` itself.
/// This method must be matched by a subsequent ``decodeObject`` message.
- (void)encodeObject:(nullable id)object;

/// An encoding method for subclasses to override to encode an interconnected group of objects, starting with the provided root object.
///
/// `NSCoder`'s implementation simply invokes ``encodeObject:``. This method must be matched by a subsequent ``decodeObject`` message.
- (void)encodeRootObject:(id)rootObject;

/// An encoding method for subclasses to override such that it creates a copy, rather than a proxy, when decoded.
///
/// `NSCoder`'s implementation simply invokes ``encodeObject:``. This method must be matched by a corresponding ``decodeObject`` message.
- (void)encodeBycopyObject:(nullable id)anObject;

/// An encoding method for subclasses to override such that it creates a proxy, rather than a copy, when decoded.
///
/// `NSCoder`'s implementation simply invokes ``encodeObject:``. This method must be matched by a corresponding ``decodeObject`` message.
- (void)encodeByrefObject:(nullable id)anObject;

/// An encoding method for subclasses to override to conditionally encode an object, preserving common references to it.
///
/// In the overriding method, `object` should be encoded only if it's unconditionally encoded elsewhere (with any other `encode...Object:` method).
/// `NSCoder`'s implementation simply invokes ``encodeObject:``.
/// This method must be matched by a subsequent ``decodeObject`` message.
- (void)encodeConditionalObject:(nullable id)object;

/// Encodes a series of values of potentially differing Objective-C types.
///
/// `types` is a C string containing any number of type codes. The variable arguments consist of one or more pointer arguments, each of which specifies a buffer containing the value to be encoded.
/// This method must be matched by a subsequent ``decodeValuesOfObjCTypes:`` message.
/// You should not use this method to encode Objective-C objects.
- (void)encodeValuesOfObjCTypes:(const char *)types, ...;

/// Encodes an array of the given Objective-C type, provided the number of items and a pointer.
///
/// The values are encoded from the buffer beginning at `array`. `type` must contain exactly one type code.
/// This method must be matched by a subsequent ``decodeArrayOfObjCType:count:at:`` message.
/// You should not use this method to encode C arrays of Objective-C objects.
- (void)encodeArrayOfObjCType:(const char *)type count:(NSUInteger)count at:(const void *)array;

/// Encodes a buffer of data of an unspecified type.
///
/// The buffer to be encoded begins at `byteaddr`, and its length in bytes is given by `length`.
/// This method must be matched by a corresponding ``decodeBytesWithReturnedLength:`` message.
- (void)encodeBytes:(nullable const void *)byteaddr length:(NSUInteger)length;

/// Decodes and returns a previously-encoded object.
///
/// `NSCoder`'s implementation invokes ``decodeValueOfObjCType:at:size:`` to decode the object data.
/// Subclasses may need to override this method if they override any of the corresponding `encode...Object` methods.
- (nullable id)decodeObject;

/// Decodes a previously-encoded object, returning an error if decoding fails.
- (nullable id)decodeTopLevelObjectAndReturnError:(NSError **)error API_AVAILABLE(macos(10.11), ios(9.0), watchos(2.0), tvos(9.0)) NS_SWIFT_UNAVAILABLE("Use 'decodeTopLevelObject() throws' instead");

/// Decodes a series of potentially different Objective-C types.
///
/// `types` is a single C string containing any number of type codes. The variable arguments consist of one or more pointer arguments, each of which specifies the buffer in which to place a single decoded value.
/// This method matches an ``encodeValuesOfObjCTypes:`` message used during encoding.
/// You should not use this method to decode Objective-C objects.
- (void)decodeValuesOfObjCTypes:(const char *)types, ...;

/// Decodes an array of `count` items, whose Objective-C type is given by `itemType`.
///
/// The items are decoded into the buffer beginning at `array`, which must be large enough to contain them all. `itemType` must contain exactly one type code.
/// This method matches an ``encodeArrayOfObjCType:count:at:`` message used during encoding.
/// You should not use this method to decode C arrays of Objective-C objects.
- (void)decodeArrayOfObjCType:(const char *)itemType count:(NSUInteger)count at:(void *)array;

/// Decodes a buffer of data whose types are unspecified.
///
/// The buffer's length is returned by reference in `lengthp`. If you need the bytes beyond the scope of the current `@autoreleasepool` block, you must copy them.
/// This method matches an ``encodeBytes:length:`` message used during encoding.
- (nullable void *)decodeBytesWithReturnedLength:(NSUInteger *)lengthp NS_RETURNS_INNER_POINTER;

#if TARGET_OS_OSX
/// Encodes a property list.
///
/// `NSCoder`'s implementation invokes ``encodeValueOfObjCType:at:`` to encode the property list.
/// This method must be matched by a subsequent ``decodePropertyList`` message.
- (void)encodePropertyList:(id)aPropertyList;

/// Decodes a property list that was previously encoded with ``encodePropertyList:``.
- (nullable id)decodePropertyList;
#endif

/// This method is present for historical reasons and has no effect.
- (void)setObjectZone:(nullable NSZone *)zone NS_AUTOMATED_REFCOUNT_UNAVAILABLE;

/// This method is present for historical reasons and has no effect.
///
/// `NSCoder`'s implementation returns the default memory zone, as given by `NSDefaultMallocZone()`.
- (nullable NSZone *)objectZone NS_AUTOMATED_REFCOUNT_UNAVAILABLE;

/// The system version in effect for the archive.
///
/// During encoding, the current version. During decoding, the version that was in effect when the data was encoded.
/// Subclasses that implement decoding must override this property to return the system version of the data being decoded.
@property (readonly) unsigned int systemVersion;

/// A Boolean value that indicates whether the receiver supports keyed coding of objects.
///
/// `NO` by default. Concrete subclasses that support keyed coding, such as `NSKeyedArchiver`, need to override this property to return `YES`.
@property (readonly) BOOL allowsKeyedCoding;

/// Encodes an object and associates it with the string key.
///
/// Subclasses must override this method to identify multiple encodings of `object` and encode a reference to `object` instead.
- (void)encodeObject:(nullable id)object forKey:(NSString *)key;

/// An encoding method for subclasses to override to conditionally encode an object, preserving common references to it, only if it has been unconditionally encoded.
///
/// Subclasses must override this method if they support keyed coding.
- (void)encodeConditionalObject:(nullable id)object forKey:(NSString *)key;

/// Encodes a Boolean value and associates it with the string `key`.
///
/// Subclasses must override this method if they perform keyed coding.
- (void)encodeBool:(BOOL)value forKey:(NSString *)key;

/// Encodes a C integer value and associates it with the string key.
///
/// Subclasses must override this method if they perform keyed coding.
- (void)encodeInt:(int)value forKey:(NSString *)key;

/// Encodes a 32-bit integer value and associates it with the string key.
///
/// Subclasses must override this method if they perform keyed coding.
- (void)encodeInt32:(int32_t)value forKey:(NSString *)key;

/// Encodes a 64-bit integer value and associates it with the string key.
///
/// Subclasses must override this method if they perform keyed coding.
- (void)encodeInt64:(int64_t)value forKey:(NSString *)key;

/// Encodes a floating point value and associates it with the string key.
///
/// Subclasses must override this method if they perform keyed coding.
- (void)encodeFloat:(float)value forKey:(NSString *)key;

/// Encodes a double-precision floating point value and associates it with the string key.
///
/// Subclasses must override this method if they perform keyed coding.
- (void)encodeDouble:(double)value forKey:(NSString *)key;

/// Encodes a buffer of data, given its length and a pointer, and associates it with a string key.
///
/// Subclasses must override this method if they perform keyed coding.
- (void)encodeBytes:(nullable const uint8_t *)bytes length:(NSUInteger)length forKey:(NSString *)key;

/// Returns a Boolean value that indicates whether an encoded value is available for a string.
///
/// Subclasses must override this method if they perform keyed coding.
- (BOOL)containsValueForKey:(NSString *)key;

/// Decodes and returns a previously-encoded object that was associated with the string `key`.
///
/// Subclasses must override this method if they perform keyed coding.
- (nullable id)decodeObjectForKey:(NSString *)key;

/// Decodes and returns a previously-encoded object for the given key, returning an error if decoding fails.
- (nullable id)decodeTopLevelObjectForKey:(NSString *)key error:(NSError **)error API_AVAILABLE(macos(10.11), ios(9.0), watchos(2.0), tvos(9.0)) NS_SWIFT_UNAVAILABLE("Use 'decodeObject(of:, forKey:)' instead");

/// Decodes and returns a boolean value that was previously encoded and associated with the string `key`.
///
/// Subclasses must override this method if they perform keyed coding.
- (BOOL)decodeBoolForKey:(NSString *)key;

/// Decodes and returns an int value that was previously encoded and associated with the string `key`.
///
/// If the encoded integer does not fit into the default integer size, the method raises an `NSRangeException`. Subclasses must override this method if they perform keyed coding.
- (int)decodeIntForKey:(NSString *)key;

/// Decodes and returns a 32-bit integer value that was previously encoded and associated with the string `key`.
///
/// If the encoded integer does not fit into a 32-bit integer, the method raises an `NSRangeException`. Subclasses must override this method if they perform keyed coding.
- (int32_t)decodeInt32ForKey:(NSString *)key;

/// Decodes and returns a 64-bit integer value that was previously encoded and associated with the string `key`.
///
/// Subclasses must override this method if they perform keyed coding.
- (int64_t)decodeInt64ForKey:(NSString *)key;

/// Decodes and returns a float value that was previously encoded and associated with the string `key`.
///
/// If the value was encoded as a double, the extra precision is lost. Subclasses must override this method if they perform keyed coding.
- (float)decodeFloatForKey:(NSString *)key;

/// Decodes and returns a double value that was previously encoded and associated with the string `key`.
///
/// Subclasses must override this method if they perform keyed coding.
- (double)decodeDoubleForKey:(NSString *)key;

/// Decodes a buffer of data that was previously encoded with ``encodeBytes:length:forKey:`` and associated with the string `key`.
///
/// The buffer's length is returned by reference in `lengthp`. The returned bytes are immutable. Subclasses must override this method if they perform keyed coding.
- (nullable const uint8_t *)decodeBytesForKey:(NSString *)key returnedLength:(nullable NSUInteger *)lengthp NS_RETURNS_INNER_POINTER;   // returned bytes immutable!

/// Decode bytes from the decoder. The length of the bytes must be greater than or equal to the `length` parameter.
/// If the result exists, but is of insufficient length, then the decoder uses `failWithError` to fail the entire decode operation. The result of that is configurable on a per-NSCoder basis using `NSDecodingFailurePolicy`.
- (nullable void *)decodeBytesWithMinimumLength:(NSUInteger)length API_AVAILABLE(macos(15.4), ios(18.4), watchos(11.4), tvos(18.4), visionos(2.4)) NS_RETURNS_INNER_POINTER;

/// Decode bytes from the decoder for a given key. The length of the bytes must be greater than or equal to the `length` parameter.
/// If the result exists, but is of insufficient length, then the decoder uses `failWithError` to fail the entire decode operation. The result of that is configurable on a per-NSCoder basis using `NSDecodingFailurePolicy`.
- (nullable const uint8_t *)decodeBytesForKey:(NSString *)key minimumLength:(NSUInteger)length API_AVAILABLE(macos(15.4), ios(18.4), watchos(11.4), tvos(18.4), visionos(2.4)) NS_RETURNS_INNER_POINTER;

/// Encodes an integer value and associates it with the string key.
///
/// Subclasses must override this method if they perform keyed coding.
- (void)encodeInteger:(NSInteger)value forKey:(NSString *)key API_AVAILABLE(macos(10.5), ios(2.0), watchos(2.0), tvos(9.0));

/// Decodes and returns an NSInteger value that was previously encoded and associated with the string `key`.
///
/// If the encoded integer does not fit into the NSInteger size, the method raises an `NSRangeException`. Subclasses must override this method if they perform keyed coding.
- (NSInteger)decodeIntegerForKey:(NSString *)key API_AVAILABLE(macos(10.5), ios(2.0), watchos(2.0), tvos(9.0));

/// Indicates whether the archiver requires all archived classes to resist object substitution attacks.
///
/// Secure coders check a set of allowed classes before decoding objects, and all objects must implement `NSSecureCoding`.
// Returns YES if this coder requires secure coding. Secure coders check a list of allowed classes before decoding objects, and all objects must implement NSSecureCoding.
@property (readonly) BOOL requiresSecureCoding API_AVAILABLE(macos(10.8), ios(6.0), watchos(2.0), tvos(9.0));

/// Decodes an object for the key, restricted to the specified class.
///
/// If the coder requires secure coding, then an exception will be thrown if the class to be decoded does not implement `NSSecureCoding` or is not `isKindOfClass:` of the argument.
/// If the coder does not require secure coding, then the class argument is ignored.
// Specify what the expected class of the allocated object is. If the coder responds YES to -requiresSecureCoding, then an exception will be thrown if the class to be decoded does not implement NSSecureCoding or is not isKindOfClass: of the argument. If the coder responds NO to -requiresSecureCoding, then the class argument is ignored and no check of the class of the decoded object is performed, exactly as if decodeObjectForKey: had been called.
- (nullable id)decodeObjectOfClass:(Class)aClass forKey:(NSString *)key API_AVAILABLE(macos(10.8), ios(6.0), watchos(2.0), tvos(9.0));

/// Decodes an object for the key and restricted class, returning an error if decoding fails.
- (nullable id)decodeTopLevelObjectOfClass:(Class)aClass forKey:(NSString *)key error:(NSError **)error API_AVAILABLE(macos(10.11), ios(9.0), watchos(2.0), tvos(9.0)) NS_SWIFT_UNAVAILABLE("Use 'decodeObject(of:, forKey:)' instead");

/**
 Decodes the \c NSArray object for the given  \c key, which should be an \c NSArray<cls>, containing the given non-collection class (no nested arrays or arrays of dictionaries, etc) from the coder.

 Requires \c NSSecureCoding otherwise an exception is thrown and sets the \c decodingFailurePolicy to \c NSDecodingFailurePolicySetErrorAndReturn.

 Returns \c nil if the object for \c key is not of the expected types, or cannot be decoded, and sets the \c error on the decoder.
 */
- (nullable NSArray *)decodeArrayOfObjectsOfClass:(Class)cls forKey:(NSString *)key API_AVAILABLE(macos(11.0), ios(14.0), watchos(7.0), tvos(14.0)) NS_REFINED_FOR_SWIFT;

/**
  Decodes the \c NSDictionary object for the given \c key, which should be an \c NSDictionary<keyCls,objectCls> , with keys of type given in \c keyCls and objects of the given non-collection class \c objectCls (no nested dictionaries or other dictionaries contained in the dictionary, etc) from the coder.

 Requires \c NSSecureCoding otherwise an exception is thrown and sets the \c decodingFailurePolicy to \c NSDecodingFailurePolicySetErrorAndReturn.

 Returns \c nil if the object for \c key is not of the expected types, or cannot be decoded, and sets the \c error on the decoder.
 */
- (nullable NSDictionary *)decodeDictionaryWithKeysOfClass:(Class)keyCls objectsOfClass:(Class)objectCls forKey:(NSString *)key API_AVAILABLE(macos(11.0), ios(14.0), watchos(7.0), tvos(14.0)) NS_REFINED_FOR_SWIFT;

/// Decodes an object for the key, restricted to the specified classes.
///
/// The class of the object may be any class in the provided `NSSet`, or a subclass of any class in the set.
// The class of the object may be any class in the provided NSSet, or a subclass of any class in the set. Otherwise, the behavior is the same as -decodeObjectOfClass:forKey:.
- (nullable id)decodeObjectOfClasses:(nullable NSSet<Class> *)classes forKey:(NSString *)key API_AVAILABLE(macos(10.8), ios(6.0), watchos(2.0), tvos(9.0)) NS_REFINED_FOR_SWIFT;

/// Decodes an object for the key and restricted classes, returning an error if decoding fails.
- (nullable id)decodeTopLevelObjectOfClasses:(nullable NSSet<Class> *)classes forKey:(NSString *)key error:(NSError **)error API_AVAILABLE(macos(10.11), ios(9.0), watchos(2.0), tvos(9.0)) NS_SWIFT_UNAVAILABLE("Use 'decodeObject(of:, forKey:)' instead");

/**
 Decodes the \c NSArray object for the given \c key, which should be an \c NSArray, containing the given non-collection classes (no nested arrays or arrays of dictionaries, etc) from the coder.

 Requires \c NSSecureCoding otherwise an exception is thrown and sets the \c decodingFailurePolicy to \c NSDecodingFailurePolicySetErrorAndReturn.

 Returns \c nil if the object for \c key is not of the expected types, or cannot be decoded, and sets the \c error on the decoder.
 */
- (nullable NSArray *)decodeArrayOfObjectsOfClasses:(NSSet<Class> *)classes forKey:(NSString *)key API_AVAILABLE(macos(11.0), ios(14.0), watchos(7.0), tvos(14.0)) NS_REFINED_FOR_SWIFT;

/**
 Decodes the \c NSDictionary object for the given \c key, which should be an \c NSDictionary, with keys of the types given in \c keyClasses and objects of the given non-collection classes in \c objectClasses (no nested dictionaries or other dictionaries contained in the dictionary, etc) from the given coder.

 Requires \c NSSecureCoding otherwise an exception is thrown and sets the \c decodingFailurePolicy to \c NSDecodingFailurePolicySetErrorAndReturn.

 Returns \c nil if the object for \c key is not of the expected types, or cannot be decoded, and sets the \c error on the decoder.
 */
- (nullable NSDictionary *)decodeDictionaryWithKeysOfClasses:(NSSet<Class> *)keyClasses objectsOfClasses:(NSSet<Class> *)objectClasses forKey:(NSString *)key API_AVAILABLE(macos(11.0), ios(14.0), watchos(7.0), tvos(14.0)) NS_REFINED_FOR_SWIFT;

/// Returns a decoded property list for the specified key.
///
/// This method calls ``decodeObjectOfClasses:forKey:`` with a set allowing only property list types.
// Calls -decodeObjectOfClasses:forKey: with a set allowing only property list types.
- (nullable id)decodePropertyListForKey:(NSString *)key API_AVAILABLE(macos(10.8), ios(6.0), watchos(2.0), tvos(9.0));

/// The set of coded classes allowed for secure coding.
///
/// Secure coders check this set of allowed classes before decoding objects, and all objects must implement `NSSecureCoding`.
// Get the current set of allowed classes.
@property (nullable, readonly, copy) NSSet<Class> *allowedClasses API_AVAILABLE(macos(10.8), ios(6.0), watchos(2.0), tvos(9.0));

/*
 Typically, you would want to call this method in your -initWithCoder: implementation when you detect situations like:
 - lack of secure coding
 - corruption of your data
 - domain validation failures

 After calling -failWithError: within your -initWithCoder: implementation, you should clean up and return nil as early as possible.

 Once an error has been signaled to a decoder, it remains set until it has handed off to the first TopLevel decode invocation above it.  For example, consider the following call graph:
 A    -decodeTopLevelObjectForKey:error:
 B        -initWithCoder:
 C            -decodeObjectForKey:
 D                -initWithCoder:
 E                    -decodeObjectForKey:
 F                        -failWithError:

 In this case the error provided in stack-frame F will be returned via the outError in stack-frame A. Furthermore the result object from decodeTopLevelObjectForKey:error: will be nil, regardless of the result of stack-frame B.

 NSCoder implementations support two mechanisms for the stack-unwinding from F to A:
 - forced (NSException based)
 - particpatory (error based)

 The kind of unwinding you get is determined by the decodingFailurePolicy property of this NSCoder (which defaults to NSDecodingFailurePolicyRaiseException to match historical behavior).
 */

/// Signals to this coder that the decode operation has failed.
///
/// Typically, you call this method in your ``NSCoding/init(coder:)`` implementation. You should set the error when you detect problems such as lack of secure coding, data corruption, or a domain validation failure.
///
/// This method is only meaningful to call for decodes.
///
/// The effect of calling this method depends on the value of ``decodingFailurePolicy``, as follows:
///
/// - If the policy is ``DecodingFailurePolicy/raiseException``, calling this method throws an exception immediately. Swift code cannot catch this kind of exception.
/// - If the policy is ``DecodingFailurePolicy/setErrorAndReturn``, calling this method sets the error property once per call to one of the `decode` methods. Calling it repeatedly has no effect until the call stack unwinds to one of these methods' entry points.
///
/// After calling `failWithError:` within your ``NSCoding/init(coder:)`` implementation, you should clean up and return `nil` as early as possible.
///
/// - Parameter error: An error that indicates why decoding failed.
- (void)failWithError:(NSError *)error API_AVAILABLE(macos(10.11), ios(9.0), watchos(2.0), tvos(9.0));

/// The action the coder should take when decoding fails.
///
/// A decode call can fail for the following reasons:
///
/// - The keyed archive data is corrupt or missing.
/// - A type mismatch occurs, such as expecting a class but encountering a numeric type instead. This also occurs when `decodeInteger(forKey:)` encounters a value encoded as floating-point, or vice versa.
/// - A secure coding violation occurs. This happens when you attempt to decode an object that doesn't conform to `NSSecureCoding`, or when the encoded type doesn't match any of the expected types.
@property (readonly) NSDecodingFailurePolicy decodingFailurePolicy API_AVAILABLE(macos(10.11), ios(9.0), watchos(2.0), tvos(9.0));

/// An error in the top-level decode.
///
/// The meaning of this property depends on the setting of the `decodingFailurePolicy` property. For `NSDecodingFailurePolicyRaiseException`, this property is always `nil`. For `NSDecodingFailurePolicySetErrorAndReturn`, a non-`nil` value represents the first error encountered while decoding the archive.
///
/// While `error` is non-`nil`, all attempts to decode data from this coder will return a `nil`/zero-equivalent value. This error is consumed by a top-level decode API, which resets the coder back to being able to potentially decode data.
@property (nullable, readonly, copy) NSError *error API_AVAILABLE(macos(10.11), ios(9.0), watchos(2.0), tvos(9.0));

@end

#if TARGET_OS_OSX
/// Returns the next object from the coder.
///
/// Given an `NSCoder`, returns an object previously written with `NXWriteNSObject()`. The returned object is autoreleased.
///
/// - Parameter decoder: The coder from which to read the object.
/// - Returns: The next object from the coder.
FOUNDATION_EXPORT NSObject * _Nullable NXReadNSObjectFromCoder(NSCoder *decoder) API_DEPRECATED("Not supported", macos(10.0,10.5), ios(2.0,2.0), watchos(2.0,2.0), tvos(9.0,9.0));

@interface NSCoder (NSTypedstreamCompatibility)

/// Encodes an old-style object onto the coder.
///
/// @DeprecationSummary {
///     Apple discourages the use of this symbol.
/// }
///
/// No sharing is done across separate ``encodeNXObject:`` invocations. Callers must have implemented an ``NSCoding/encode(with:)``, which parallels the `write:` methods, on all of their classes that may be touched by this operation.
- (void)encodeNXObject:(id)object API_DEPRECATED("Not supported", macos(10.0,10.5), ios(2.0,2.0), watchos(2.0,2.0), tvos(9.0,9.0));

/// Decodes an object previously written with ``encodeNXObject:``.
///
/// @DeprecationSummary {
///     Apple discourages the use of this symbol.
/// }
///
/// No sharing is done across separate ``decodeNXObject`` invocations. Callers must have implemented an ``NSCoding/init(coder:)``, which parallels the `read:` methods, on all of their classes that may be touched by this operation. The returned object is autoreleased.
- (nullable id)decodeNXObject API_DEPRECATED("Not supported", macos(10.0,10.5), ios(2.0,2.0), watchos(2.0,2.0), tvos(9.0,9.0));

@end
#endif

@interface NSCoder(NSDeprecated)
/// Decodes a single value, whose Objective-C type is given by `type`.
///
/// @DeprecationSummary {
///     Use ``decodeValueOfObjCType:at:size:`` instead.
/// }
///
/// This method is unsafe because it could potentially cause buffer overruns.
- (void)decodeValueOfObjCType:(const char *)type at:(void *)data API_DEPRECATED_WITH_REPLACEMENT("decodeValueOfObjCType:at:size:", macos(10.0, API_TO_BE_DEPRECATED), ios(2.0, API_TO_BE_DEPRECATED), watchos(2.0, API_TO_BE_DEPRECATED), tvos(9.0, API_TO_BE_DEPRECATED));

@end

NS_HEADER_AUDIT_END(nullability, sendability)
