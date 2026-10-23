/*	NSValue.h
	Copyright (c) 1994-2019, Apple Inc. All rights reserved.
*/

#import <Foundation/NSObject.h>

@class NSString, NSDictionary;

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

/// A simple container for a single C or Objective-C data item.
///
/// An ``NSValue`` object can hold any of the scalar types such as `int`, `float`, and `char`, as well as pointers, structures, and object `id` references. Use this class to work with such data types in collections (such as ``NSArray`` and ``NSSet``), [Key-value coding](https://developer.apple.com/library/archive/documentation/General/Conceptual/DevPedia-CocoaCore/KeyValueCoding.html#//apple_ref/doc/uid/TP40008195-CH25), and other APIs that require Objective-C objects. ``NSValue`` objects are always immutable.
///
/// ### Subclassing Notes
///
/// The abstract ``NSValue`` class is the public interface of a class cluster consisting mostly of private, concrete classes that create and return a value object appropriate for a given situation. It is possible to subclass ``NSValue``, but doing so requires providing storage facilities for the value (which is not inherited by subclasses) and implementing two primitive methods.
///
/// #### Methods to Override
///
/// Any subclass of ``NSValue`` _must_ override the primitive instance methods ``getValue(_:)`` and ``objCType``. These methods must operate on the storage that you provide for the value.
///
/// You might want to implement an initializer for your subclass that is suited to the storage you provide. The ``NSValue`` class does not have a designated initializer, so your initializer need only invoke the <doc://com.apple.documentation/documentation/objectivec/nsobject-swift.class/init()> method of `super`. The ``NSValue`` class adopts the ``NSCopying`` and ``NSSecureCoding`` protocols; if you want instances of your own custom subclass created from copying or coding, override the methods in these protocols.
///
/// You may also wish to implement the <doc://com.apple.documentation/documentation/objectivec/nsobjectprotocol/hash> method to make your subclass work well in collections.
///
/// #### Alternatives to Subclassing
///
/// If you need only to use ``NSValue`` objects for wrap a custom data types or structures defined by your app, you need not create an ``NSValue`` subclass. Instead, create a category that uses existing ``NSValue`` methods to store and retrieve data of your custom type. For example, the code below defines a custom Polyhedron structure and creates ``NSValue`` convenience methods to store and retrieve it:
///
/// ```objc
/// typedef struct {
/// int numFaces;
/// float radius;
/// } Polyhedron;
///
/// @interface NSValue (Polyhedron)
/// + (instancetype)valuewithPolyhedron:(Polyhedron)value;
/// @property (readonly) Polyhedron polyhedronValue;
/// @end
///
/// @implementation NSValue (Polyhedron)
/// + (instancetype)valuewithPolyhedron:(Polyhedron)value
/// {
/// return [self valueWithBytes:&value objCType:@encode(Polyhedron)];
/// }
/// - (Polyhedron) polyhedronValue
/// {
/// Polyhedron value;
/// [self getValue:&value];
/// return value;
/// }
/// @end
/// ```
@interface NSValue : NSObject <NSCopying, NSSecureCoding>

/// Copies the value into the specified buffer.
///
/// - Parameters:
///   - value: A buffer into which to copy the value. The buffer must be large enough to hold the value.
///   - size: The number of bytes to copy.
- (void)getValue:(void *)value size:(NSUInteger)size API_AVAILABLE(macos(10.13), ios(11.0), watchos(4.0), tvos(11.0));

/// A C string containing the Objective-C type of the data contained in the value object, as encoded by the `@encode()` compiler directive.
@property (readonly) const char *objCType NS_RETURNS_INNER_POINTER;

/// Initializes a value object to contain the specified value, interpreted with the specified Objective-C type.
///
/// - Parameters:
///   - value: A pointer to data to be stored in the new value object.
///   - type: The Objective-C type of `value`, as provided by the `@encode()` compiler directive. Do not hard-code this parameter as a C string.
/// - Returns: An initialized value object that contains `value`, interpreted as being of the Objective-C type `type`. The returned object might be different than the original receiver.
///
/// This is the designated initializer for the ``NSValue`` class.
- (instancetype)initWithBytes:(const void *)value objCType:(const char *)type NS_DESIGNATED_INITIALIZER;
- (nullable instancetype)initWithCoder:(NSCoder *)coder NS_DESIGNATED_INITIALIZER;

@end

@interface NSValue (NSValueCreation)

/// Creates a value object containing the specified value, interpreted with the specified Objective-C type.
///
/// - Parameters:
///   - value: A pointer to data to be stored in the new value object.
///   - type: The Objective-C type of `value`, as provided by the `@encode()` compiler directive. Do not hard-code this parameter as a C string.
/// - Returns: A new value object that contains `value`, which is interpreted as being of the Objective-C type `type`.
+ (NSValue *)valueWithBytes:(const void *)value objCType:(const char *)type;
/// Creates a value object containing the specified value, interpreted with the specified Objective-C type.
///
/// @DeprecationSummary {
///     Use ``NSValue/valueWithBytes:objCType:`` instead.
/// }
+ (NSValue *)value:(const void *)value withObjCType:(const char *)type;

@end

@interface NSValue (NSValueExtensionMethods)

/// Creates a value object containing the specified object without retaining it.
///
/// - Parameter anObject: The value for the new object.
/// - Returns: A new value object that contains `anObject`. Accessing `nonretainedObjectValue` on the result will return `anObject` itself (as opposed to a copy).
///
/// This method is useful for preventing an object from being retained when it's added to a collection object (such as an `NSArray` or `NSDictionary` instance).
+ (NSValue *)valueWithNonretainedObject:(nullable id)anObject;
/// The value as a non-retained pointer to an object.
///
/// This method is potentially dangerous, because the returned object might have been released by the time it is used. Ensure that the object has a retained reference before using it.
@property (nullable, readonly) id nonretainedObjectValue;

/// Creates a value object containing the specified pointer.
///
/// - Parameter pointer: The value for the new object.
/// - Returns: A new value object that contains `aPointer`.
///
/// This method does not copy the data that `pointer` points to.
+ (NSValue *)valueWithPointer:(nullable const void *)pointer;
/// Returns the value as an untyped pointer.
@property (nullable, readonly) void *pointerValue;

/// Returns a Boolean value that indicates whether the value object and another value object are equal.
///
/// - Parameter value: The other value object with which to compare the value object.
/// - Returns: `YES` if both value objects are equal; otherwise, `NO`.
///
/// The ``NSValue`` class compares the type and contents of each value object to determine equality.
- (BOOL)isEqualToValue:(NSValue *)value;

@end

/// An object wrapper for primitive scalar numeric values.
///
/// `NSNumber` is a subclass of `NSValue` that offers a value as any C scalar (numeric) type. It defines a set of methods specifically for setting and accessing the value as a signed or unsigned `char`, `short int`, `int`, `long int`, `long long int`, `float`, or `double` or as a `BOOL`. (Note that number objects do not necessarily preserve the type they are created with.) It also defines a ``compare(_:)`` method to determine the ordering of two `NSNumber` objects.
///
/// `NSNumber` is "toll-free bridged" with its Core Foundation counterparts: <doc://com.apple.documentation/documentation/corefoundation/cfnumber> for integer and floating point values, and <doc://com.apple.documentation/documentation/corefoundation/cfboolean> for Boolean values. See [Toll-Free Bridging](https://developer.apple.com/library/archive/documentation/General/Conceptual/CocoaEncyclopedia/Toll-FreeBridgin/Toll-FreeBridgin.html#//apple_ref/doc/uid/TP40010810-CH2) for more information on toll-free bridging.
///
/// ### Value Conversions
///
/// `NSNumber` provides readonly properties that return the object's stored value converted to a particular Boolean, integer, unsigned integer, or floating point C scalar type. Because numeric types have different storage capabilities, attempting to initialize with a value of one type and access the value of another type may produce an erroneous result—for example, initializing with a `double` value exceeding `FLT_MAX` and accessing its ``floatValue``, or initializing with an negative integer value and accessing its ``uintValue``. In some cases, attempting to initialize with a value of a type and access the value of another type may result in loss of precision—for example, initializing with a `double` value with many significant digits and accessing its ``floatValue``, or initializing with a large integer value and accessing its ``int8Value``.
///
/// An `NSNumber` object initialized with a value of a particular type accessing the converted value of a different _kind_ of type, such as `unsigned int` and `float`, will convert its stored value to that converted type in the following ways:
///
///
/// | `Value` | ``boolValue`` | ``intValue-95zzp`` | ``uintValue`` | ``floatValue`` |
/// |---|---|---|---|---|
/// | <doc://com.apple.documentation/documentation/swift/false> | <doc://com.apple.documentation/documentation/swift/false> | `0` | `0` | `0.0` |
/// | <doc://com.apple.documentation/documentation/swift/true> | <doc://com.apple.documentation/documentation/swift/true> | `1` | `1` | `1.0` |
///
///
///
/// | `Value` | ``boolValue`` | ``intValue-95zzp`` | ``uintValue`` | ``floatValue`` |
/// |---|---|---|---|---|
/// | `0` | <doc://com.apple.documentation/documentation/swift/false> | `0` | `0` | `0.0` |
/// | `1` | <doc://com.apple.documentation/documentation/swift/true> | `1` | `1` | `1.0` |
/// | `-1` | <doc://com.apple.documentation/documentation/swift/true> | `-1` | _invalid, erroneous result_ | `-1.0` |
///
///
///
/// | `Value` | ``boolValue`` | ``intValue-95zzp`` | ``uintValue`` | ``floatValue`` |
/// |---|---|---|---|---|
/// | `0` | <doc://com.apple.documentation/documentation/swift/false> | `0` | `0` | `0.0` |
/// | `1` | <doc://com.apple.documentation/documentation/swift/true> | `1` | `1` | `1.0` |
///
///
///
/// | `Value` | ``boolValue`` | ``intValue-95zzp`` | ``uintValue`` | ``floatValue`` |
/// |---|---|---|---|---|
/// | `0.0` | <doc://com.apple.documentation/documentation/swift/false> | `0` | `0` | `0.0` |
/// | `1.0` | <doc://com.apple.documentation/documentation/swift/true> | `1` | `1` | `1.0` |
/// | `-1.0` | <doc://com.apple.documentation/documentation/swift/true> | `-1` | _invalid, erroneous result_ | `-1.0` |
///
///
/// ### Subclassing Notes
///
/// As with any class cluster, subclasses of `NSNumber` must override the primitive methods of its superclass, `NSValue`. In addition, there are two requirements around the data type your subclass represents:
///
/// 1. Your implementation of ``NSValue/objCType`` must return one of "`c`", "`C`", "`s`", "`S`", "`i`", "`I`", "`l`", "`L`", "`q`", "`Q`", "`f`", and "`d`". This is required for the other methods of ``NSNumber`` to behave correctly.
/// 2. Your subclass must override the accessor method that corresponds to the declared type—for example, if your implementation of ``NSValue/objCType`` returns  "`i`", you must override ``int32Value``.
NS_SWIFT_SENDABLE
@interface NSNumber : NSValue

- (nullable instancetype)initWithCoder:(NSCoder *)coder NS_DESIGNATED_INITIALIZER;
/// Creates a number object containing a `char` value.
- (NSNumber *)initWithChar:(char)value NS_DESIGNATED_INITIALIZER;
/// Creates a number object containing an `unsigned char` value.
- (NSNumber *)initWithUnsignedChar:(unsigned char)value NS_DESIGNATED_INITIALIZER;
/// Creates a number object containing a `short` value.
- (NSNumber *)initWithShort:(short)value NS_DESIGNATED_INITIALIZER;
/// Creates a number object containing an `unsigned short` value.
- (NSNumber *)initWithUnsignedShort:(unsigned short)value NS_DESIGNATED_INITIALIZER;
/// Creates a number object containing an `int` value.
- (NSNumber *)initWithInt:(int)value NS_DESIGNATED_INITIALIZER;
/// Creates a number object containing an `unsigned int` value.
- (NSNumber *)initWithUnsignedInt:(unsigned int)value NS_DESIGNATED_INITIALIZER;
/// Creates a number object containing a `long` value.
- (NSNumber *)initWithLong:(long)value NS_DESIGNATED_INITIALIZER;
/// Creates a number object containing an `unsigned long` value.
- (NSNumber *)initWithUnsignedLong:(unsigned long)value NS_DESIGNATED_INITIALIZER;
/// Creates a number object containing a `long long` value.
- (NSNumber *)initWithLongLong:(long long)value NS_DESIGNATED_INITIALIZER;
/// Creates a number object containing an `unsigned long long` value.
- (NSNumber *)initWithUnsignedLongLong:(unsigned long long)value NS_DESIGNATED_INITIALIZER;
/// Creates a number object containing a `float` value.
- (NSNumber *)initWithFloat:(float)value NS_DESIGNATED_INITIALIZER;
/// Creates a number object containing a `double` value.
- (NSNumber *)initWithDouble:(double)value NS_DESIGNATED_INITIALIZER;
/// Creates a number object containing a `BOOL` value.
- (NSNumber *)initWithBool:(BOOL)value NS_DESIGNATED_INITIALIZER;
/// Creates a number object containing an `NSInteger` value.
- (NSNumber *)initWithInteger:(NSInteger)value API_AVAILABLE(macos(10.5), ios(2.0), watchos(2.0), tvos(9.0)) NS_DESIGNATED_INITIALIZER;
/// Creates a number object containing an `NSUInteger` value.
- (NSNumber *)initWithUnsignedInteger:(NSUInteger)value API_AVAILABLE(macos(10.5), ios(2.0), watchos(2.0), tvos(9.0)) NS_DESIGNATED_INITIALIZER;

/// The number object's value expressed as a `char`.
@property (readonly) char charValue;
/// The number object's value expressed as an `unsigned char`.
@property (readonly) unsigned char unsignedCharValue;
/// The number object's value expressed as a `short`.
@property (readonly) short shortValue;
/// The number object's value expressed as an `unsigned short`.
@property (readonly) unsigned short unsignedShortValue;
/// The number object's value expressed as an `int`.
@property (readonly) int intValue;
/// The number object's value expressed as an `unsigned int`.
@property (readonly) unsigned int unsignedIntValue;
/// The number object's value expressed as a `long`.
@property (readonly) long longValue;
/// The number object's value expressed as an `unsigned long`.
@property (readonly) unsigned long unsignedLongValue;
/// The number object's value expressed as a `long long`.
@property (readonly) long long longLongValue;
/// The number object's value expressed as an `unsigned long long`.
@property (readonly) unsigned long long unsignedLongLongValue;
/// The number object's value expressed as a `float`.
@property (readonly) float floatValue;
/// The number object's value expressed as a `double`.
@property (readonly) double doubleValue;
/// The number object's value expressed as a Boolean value.
///
/// A `0` value always means `NO`, and any nonzero value is interpreted as `YES`.
@property (readonly) BOOL boolValue;
/// The number object's value expressed as an `NSInteger`.
@property (readonly) NSInteger integerValue API_AVAILABLE(macos(10.5), ios(2.0), watchos(2.0), tvos(9.0));
/// The number object's value expressed as an `NSUInteger`.
@property (readonly) NSUInteger unsignedIntegerValue API_AVAILABLE(macos(10.5), ios(2.0), watchos(2.0), tvos(9.0));

/// The number object's value expressed as a human-readable string.
///
/// The string is created by invoking ``NSNumber/descriptionWithLocale:`` where locale is `nil`.
@property (readonly, copy) NSString *stringValue;

/// Returns an `NSComparisonResult` value that indicates whether the number object's value is greater than, equal to, or less than a given number.
///
/// - Parameter otherNumber: The number to compare to the number object's value. This value must not be `nil`.
/// - Returns: `NSOrderedAscending` if the value of `otherNumber` is greater than the number object's, `NSOrderedSame` if they're equal, and `NSOrderedDescending` if the value of `otherNumber` is less than the number object's.
///
/// The ``NSNumber/compare:`` method follows the standard C rules for type conversion. For example, if you compare an `NSNumber` object that has an integer value with an `NSNumber` object that has a floating point value, the integer value is converted to a floating-point value for comparison.
- (NSComparisonResult)compare:(NSNumber *)otherNumber;

/// Returns a Boolean value that indicates whether the number object's value and a given number are equal.
///
/// - Parameter number: The number to compare to the number object's value.
/// - Returns: `YES` if the number object's value and `number` are equal; otherwise, `NO`.
///
/// Two `NSNumber` objects are considered equal if they have the same id values or if they have equivalent values (as determined by the ``NSNumber/compare:`` method). This method is more efficient than ``NSNumber/compare:`` if you know the two objects are numbers.
- (BOOL)isEqualToNumber:(NSNumber *)number;

/// Returns a string that represents the contents of the number object for a given locale.
///
/// - Parameter locale: An object containing locale information with which to format the description. Use `nil` if you don't want the description formatted.
/// - Returns: A string that represents the contents of the number object formatted using the locale information in `locale`.
- (NSString *)descriptionWithLocale:(nullable id)locale;

@end

@interface NSNumber (NSNumberCreation)

/// Creates and returns an `NSNumber` object containing a given value, treating it as a `char`.
+ (NSNumber *)numberWithChar:(char)value;
/// Creates and returns an `NSNumber` object containing a given value, treating it as an `unsigned char`.
+ (NSNumber *)numberWithUnsignedChar:(unsigned char)value;
/// Creates and returns an `NSNumber` object containing a given value, treating it as a `short`.
+ (NSNumber *)numberWithShort:(short)value;
/// Creates and returns an `NSNumber` object containing a given value, treating it as an `unsigned short`.
+ (NSNumber *)numberWithUnsignedShort:(unsigned short)value;
/// Creates and returns an `NSNumber` object containing a given value, treating it as an `int`.
+ (NSNumber *)numberWithInt:(int)value;
/// Creates and returns an `NSNumber` object containing a given value, treating it as an `unsigned int`.
+ (NSNumber *)numberWithUnsignedInt:(unsigned int)value;
/// Creates and returns an `NSNumber` object containing a given value, treating it as a `long`.
+ (NSNumber *)numberWithLong:(long)value;
/// Creates and returns an `NSNumber` object containing a given value, treating it as an `unsigned long`.
+ (NSNumber *)numberWithUnsignedLong:(unsigned long)value;
/// Creates and returns an `NSNumber` object containing a given value, treating it as a `long long`.
+ (NSNumber *)numberWithLongLong:(long long)value;
/// Creates and returns an `NSNumber` object containing a given value, treating it as an `unsigned long long`.
+ (NSNumber *)numberWithUnsignedLongLong:(unsigned long long)value;
/// Creates and returns an `NSNumber` object containing a given value, treating it as a `float`.
+ (NSNumber *)numberWithFloat:(float)value;
/// Creates and returns an `NSNumber` object containing a given value, treating it as a `double`.
+ (NSNumber *)numberWithDouble:(double)value;
/// Creates and returns an `NSNumber` object containing a given value, treating it as a `BOOL`.
+ (NSNumber *)numberWithBool:(BOOL)value;
/// Creates and returns an `NSNumber` object containing a given value, treating it as an `NSInteger`.
+ (NSNumber *)numberWithInteger:(NSInteger)value API_AVAILABLE(macos(10.5), ios(2.0), watchos(2.0), tvos(9.0));
/// Creates and returns an `NSNumber` object containing a given value, treating it as an `NSUInteger`.
+ (NSNumber *)numberWithUnsignedInteger:(NSUInteger)value API_AVAILABLE(macos(10.5), ios(2.0), watchos(2.0), tvos(9.0));

@end

@interface NSValue (NSDeprecated)
/// Copies the value into the specified buffer.
///
/// @DeprecationSummary {
///     This method is unsafe because it could potentially cause buffer overruns. Use ``NSValue/getValue:size:`` instead.
/// }
- (void)getValue:(void *)value API_DEPRECATED_WITH_REPLACEMENT("getValue:size:", macos(10.0, API_TO_BE_DEPRECATED), ios(2.0, API_TO_BE_DEPRECATED), watchos(2.0, API_TO_BE_DEPRECATED), tvos(9.0, API_TO_BE_DEPRECATED));
@end

NS_HEADER_AUDIT_END(nullability, sendability)
