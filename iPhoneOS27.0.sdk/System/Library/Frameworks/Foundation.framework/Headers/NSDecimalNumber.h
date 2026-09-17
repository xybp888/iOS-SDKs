/*	NSDecimalNumber.h
	Copyright (c) 1995-2019, Apple Inc. All rights reserved.
*/

#import <Foundation/NSValue.h>
#import <Foundation/NSScanner.h>
#import <Foundation/NSDecimal.h>
#import <Foundation/NSDictionary.h>
#import <Foundation/NSException.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

/* **************	Exceptions		***********/

/// The name of an exception raised if there is an exactness error.
FOUNDATION_EXPORT NSExceptionName const NSDecimalNumberExactnessException;
/// The name of an exception raised on overflow.
FOUNDATION_EXPORT NSExceptionName const NSDecimalNumberOverflowException;
/// The name of an exception raised on underflow.
FOUNDATION_EXPORT NSExceptionName const NSDecimalNumberUnderflowException;
/// The name of an exception raised on divide by zero.
FOUNDATION_EXPORT NSExceptionName const NSDecimalNumberDivideByZeroException;

/* **************	Rounding and Exception behavior		***********/

@class NSDecimalNumber;

/// A protocol that declares three methods that control the discretionary aspects of working with decimal numbers.
///
/// The ``scale()`` and ``roundingMode()`` methods determine the precision of `NSDecimalNumber`'s return values and the way in which those values should be rounded to fit that precision. The ``exceptionDuringOperation(_:error:leftOperand:rightOperand:)`` method determines the way in which an `NSDecimalNumber` object should handle different calculation errors.
///
/// For an example of a class that adopts the `NSDecimalBehaviors` protocol, see the specification for ``NSDecimalNumberHandler``.
@protocol NSDecimalNumberBehaviors

/// Returns the way that `NSDecimalNumber`'s `decimalNumberBy...` methods round their return values.
- (NSRoundingMode)roundingMode;

/// Returns the number of digits allowed after the decimal separator.
- (short)scale;
    // The scale could return NO_SCALE for no defined scale.

/// Specifies what an `NSDecimalNumber` object will do when it encounters an error.
///
/// - Parameters:
///   - operation: The method that was being executed when the error occurred.
///   - error: The type of error that was generated.
///   - leftOperand: The left operand.
///   - rightOperand: The right operand, or `nil` for unary operations.
/// - Returns: An `NSDecimalNumber` object to use as the result, or `nil` to ignore the error.
///
/// The receiver can raise an exception, return a new value, or return `nil` to ignore the exception.
- (nullable NSDecimalNumber *)exceptionDuringOperation:(SEL)operation error:(NSCalculationError)error leftOperand:(NSDecimalNumber *)leftOperand rightOperand:(nullable NSDecimalNumber *)rightOperand;

@end

/// An object for representing and performing arithmetic on base-10 numbers.
///
/// In Swift, this object bridges to ``Decimal``; use ``NSDecimalNumber`` when you need reference semantics or other Foundation-specific behavior.
///
/// `NSDecimalNumber`, an immutable subclass of `NSNumber`, provides an object-oriented wrapper for doing base-10 arithmetic. An instance can represent any number that can be expressed as `mantissa x 10^exponent` where mantissa is a decimal integer up to 38 digits long, and exponent is an integer from –128 through 127.
///
/// > Important:
/// > The Swift overlay to the Foundation framework provides the ``Decimal`` structure, which bridges to the ``NSDecimalNumber`` class. For more information about value types, see <doc://com.apple.documentation/documentation/swift/working-with-foundation-types>.
NS_SWIFT_SENDABLE
@interface NSDecimalNumber : NSNumber {
@private
    signed   int _exponent:8;
    unsigned int _length:4;
    unsigned int _isNegative:1;
    unsigned int _isCompact:1;
    unsigned int _reserved:1;
    unsigned int _hasExternalRefCount:1;
    unsigned int _refs:16;
    unsigned short _mantissa[];
}

/// Initializes a decimal number using the given mantissa, exponent, and sign.
///
/// - Parameters:
///   - mantissa: The mantissa for the new decimal number object.
///   - exponent: The exponent for the new decimal number object.
///   - flag: A Boolean value that specifies whether the sign of the number is negative.
/// - Returns: An `NSDecimalNumber` object initialized using the given mantissa, exponent, and sign.
///
/// The arguments express a number in scientific notation requiring mantissa to be an integer. For example, to create an `NSDecimalNumber` object equivalent to 1.23, use `initWithMantissa:exponent:isNegative:` as follows: `[NSDecimalNumber alloc] initWithMantissa:123 exponent:-2 isNegative:NO]`
- (instancetype)initWithMantissa:(unsigned long long)mantissa exponent:(short)exponent isNegative:(BOOL)flag;
/// Initializes a decimal number to represent a given decimal.
///
/// - Parameter dcm: The value of the new object.
/// - Returns: An `NSDecimalNumber` object initialized to represent `dcm`.
///
/// This method is the designated initializer for `NSDecimalNumber`.
- (instancetype)initWithDecimal:(NSDecimal)dcm NS_DESIGNATED_INITIALIZER;
/// Initializes a decimal number so that its value is equivalent to that in a given numeric string.
///
/// - Parameter numberValue: A numeric string.
/// - Returns: An `NSDecimalNumber` object initialized with the value of `numberValue`.
///
/// Don't use this initializer if `numberValue` has a fractional part, since the lack of a locale makes handling the decimal separator ambiguous. Use ``NSDecimalNumber/initWithString:locale:`` instead for fractional values.
- (instancetype)initWithString:(nullable NSString *)numberValue;
/// Initializes a decimal number so that its value is equivalent to that in a given numeric string, interpreted using a given locale.
///
/// - Parameters:
///   - numberValue: A numeric string.
///   - locale: A dictionary that defines the locale (specifically the `decimalSeparator`) to use to interpret the number in `numberValue`.
/// - Returns: An `NSDecimalNumber` object initialized with the value of `numberValue`, interpreted using `locale`.
- (instancetype)initWithString:(nullable NSString *)numberValue locale:(nullable id)locale;
/// Returns a string that represents the contents of the decimal number for a given locale.
///
/// - Parameter locale: An object containing locale information with which to format the description.
/// - Returns: A string that represents the contents of the decimal number formatted using the locale information in `locale`.
- (NSString *)descriptionWithLocale:(nullable id)locale;

/// The decimal value of the number.
@property (readonly) NSDecimal decimalValue;

/// Creates and returns a decimal number using the given mantissa, exponent, and sign.
+ (NSDecimalNumber *)decimalNumberWithMantissa:(unsigned long long)mantissa exponent:(short)exponent isNegative:(BOOL)flag;
/// Creates and returns a decimal number equivalent to the given decimal structure.
+ (NSDecimalNumber *)decimalNumberWithDecimal:(NSDecimal)dcm;
/// Creates and returns a decimal number equivalent to the given numeric string.
+ (NSDecimalNumber *)decimalNumberWithString:(nullable NSString *)numberValue;
/// Creates and returns a decimal number equivalent to the given numeric string, interpreted using the given locale.
+ (NSDecimalNumber *)decimalNumberWithString:(nullable NSString *)numberValue locale:(nullable id)locale;

/// A decimal number equivalent to the number 0.
@property (class, readonly, copy) NSDecimalNumber *zero;
/// A decimal number equivalent to the number 1.
@property (class, readonly, copy) NSDecimalNumber *one;
/// The smallest possible value of a decimal number.
@property (class, readonly, copy) NSDecimalNumber *minimumDecimalNumber;
/// The largest possible value of a decimal number.
@property (class, readonly, copy) NSDecimalNumber *maximumDecimalNumber;
/// A decimal number that specifies no number.
///
/// Any arithmetic method receiving `notANumber` as an argument returns `notANumber`.
@property (class, readonly, copy) NSDecimalNumber *notANumber;

/// Adds this number to another given number.
///
/// - Parameter decimalNumber: The number to add to the receiver.
/// - Returns: A new `NSDecimalNumber` object whose value is the sum of the receiver and `decimalNumber`.
///
/// This method uses the default behavior when handling calculation errors and rounding.
- (NSDecimalNumber *)decimalNumberByAdding:(NSDecimalNumber *)decimalNumber;
/// Adds this number to another given number using the specified behavior.
///
/// - Parameters:
///   - decimalNumber: The number to add to the receiver.
///   - behavior: The behavior for handling calculation errors and rounding.
- (NSDecimalNumber *)decimalNumberByAdding:(NSDecimalNumber *)decimalNumber withBehavior:(nullable id <NSDecimalNumberBehaviors>)behavior;

/// Subtracts another given number from this one.
///
/// - Parameter decimalNumber: The number to subtract from the receiver.
/// - Returns: A new `NSDecimalNumber` object whose value is the receiver minus `decimalNumber`.
///
/// This method uses the default behavior when handling calculation errors and rounding.
- (NSDecimalNumber *)decimalNumberBySubtracting:(NSDecimalNumber *)decimalNumber;
/// Subtracts another given number from this one using the specified behavior.
///
/// - Parameters:
///   - decimalNumber: The number to subtract from the receiver.
///   - behavior: The behavior for handling calculation errors and rounding.
- (NSDecimalNumber *)decimalNumberBySubtracting:(NSDecimalNumber *)decimalNumber withBehavior:(nullable id <NSDecimalNumberBehaviors>)behavior;

/// Multiplies the number by another given number.
///
/// - Parameter decimalNumber: The number by which to multiply the receiver.
/// - Returns: A new `NSDecimalNumber` object whose value is the receiver multiplied by `decimalNumber`.
///
/// This method uses the default behavior when handling calculation errors and rounding.
- (NSDecimalNumber *)decimalNumberByMultiplyingBy:(NSDecimalNumber *)decimalNumber;
/// Multiplies the number by another given number using the specified behavior.
///
/// - Parameters:
///   - decimalNumber: The number by which to multiply the receiver.
///   - behavior: The behavior for handling calculation errors and rounding.
- (NSDecimalNumber *)decimalNumberByMultiplyingBy:(NSDecimalNumber *)decimalNumber withBehavior:(nullable id <NSDecimalNumberBehaviors>)behavior;

/// Divides the number by another given number.
///
/// - Parameter decimalNumber: The number by which to divide the receiver.
/// - Returns: A new `NSDecimalNumber` object whose value is the value of the receiver divided by `decimalNumber`.
///
/// This method uses the default behavior when handling calculation errors and rounding.
- (NSDecimalNumber *)decimalNumberByDividingBy:(NSDecimalNumber *)decimalNumber;
/// Divides the number by another given number using the specified behavior.
///
/// - Parameters:
///   - decimalNumber: The number by which to divide the receiver.
///   - behavior: The behavior for handling calculation errors and rounding.
- (NSDecimalNumber *)decimalNumberByDividingBy:(NSDecimalNumber *)decimalNumber withBehavior:(nullable id <NSDecimalNumberBehaviors>)behavior;

/// Raises the number to a given power.
///
/// - Parameter power: The power to which to raise the receiver.
/// - Returns: A new `NSDecimalNumber` object whose value is the value of the receiver raised to the power `power`.
///
/// This method uses the default behavior when handling calculation errors and rounding.
- (NSDecimalNumber *)decimalNumberByRaisingToPower:(NSUInteger)power;
/// Raises the number to a given power using the specified behavior.
///
/// - Parameters:
///   - power: The power to which to raise the receiver.
///   - behavior: The behavior for handling calculation errors and rounding.
- (NSDecimalNumber *)decimalNumberByRaisingToPower:(NSUInteger)power withBehavior:(nullable id <NSDecimalNumberBehaviors>)behavior;

/// Multiplies the number by 10 raised to the given power.
///
/// This method uses the default behavior when handling calculation errors and rounding.
- (NSDecimalNumber *)decimalNumberByMultiplyingByPowerOf10:(short)power;
/// Multiplies the number by 10 raised to the given power using the specified behavior.
- (NSDecimalNumber *)decimalNumberByMultiplyingByPowerOf10:(short)power withBehavior:(nullable id <NSDecimalNumberBehaviors>)behavior;


/// Returns a rounded version of the decimal number using the specified rounding behavior.
///
/// - Parameter behavior: The rounding behavior to apply. The scale of the behavior determines the number of digits a rounded value is allowed to have after the decimal separator.
- (NSDecimalNumber *)decimalNumberByRoundingAccordingToBehavior:(nullable id <NSDecimalNumberBehaviors>)behavior;

/// Compares this decimal number to another number.
///
/// - Parameter decimalNumber: The number to compare. This value must not be `nil`.
/// - Returns: `NSOrderedAscending` if the value of `decimalNumber` is greater than the receiver, `NSOrderedSame` if they're equal, and `NSOrderedDescending` if `decimalNumber` is less.
- (NSComparisonResult)compare:(NSNumber *)decimalNumber;

/// The way arithmetic methods round off and handle error conditions.
///
/// By default, the arithmetic methods use the ``NSDecimalNumberHandler/defaultDecimalNumberHandler`` behavior: `NSRoundPlain` rounding, assuming precision does not exceed 38 significant digits, and raising exceptions on overflow, underflow, and divide by zero.
///
/// If this default behavior doesn't suit your application, you should use methods that let you specify the behavior, like ``adding(_:withBehavior:)``. If you find yourself using a particular behavior consistently, you can specify a different default behavior with `setDefaultBehavior(_:)`.
///
/// The default behavior is maintained separately for each thread in your app.

@property (class, strong) id <NSDecimalNumberBehaviors> defaultBehavior;


/// A C string containing the Objective-C type of the data contained in the decimal number object.
///
/// Returns `"d"` (for `double`).
@property (readonly) const char *objCType NS_RETURNS_INNER_POINTER;

/// An approximate `double` value for the decimal number.
@property (readonly) double doubleValue;
    
@end

/// A class that adopts the decimal number behaviors protocol.
///
/// This class allows you to set the way an ``NSDecimalNumber`` object rounds off and handles errors, without having to create a custom class.
///
/// You can use an instance of this class as an argument to any of the ``NSDecimalNumber`` methods that end with `...Behavior:`. If you don't think you need special behavior, you probably don't need this class—it is likely that ``NSDecimalNumber``'s default behavior will suit your needs.
///
/// For more information, see the ``NSDecimalNumberBehaviors`` protocol specification.
NS_SWIFT_SENDABLE
@interface NSDecimalNumberHandler : NSObject <NSDecimalNumberBehaviors, NSCoding> {
  @private
    signed int _scale:16;
    unsigned _roundingMode:3;
    unsigned _raiseOnExactness:1;
    unsigned _raiseOnOverflow:1;
    unsigned _raiseOnUnderflow:1;
    unsigned _raiseOnDivideByZero:1;
    unsigned _unused:9;
    void *_reserved2;
    void *_reserved;
}

/// Returns the default instance of `NSDecimalNumberHandler`.
///
/// The default handler rounds to closest possible return value (``NSRoundPlain``), assumes precision up to 38 significant digits, and raises on overflow, underflow, and divide by zero.
@property (class, readonly, strong) NSDecimalNumberHandler *defaultDecimalNumberHandler;

/// Returns an `NSDecimalNumberHandler` object initialized so it behaves as specified by the method's arguments.
///
/// - Parameters:
///   - roundingMode: The rounding mode to use. Four values are allowed: `NSRoundUp`, `NSRoundDown`, `NSRoundPlain`, and `NSRoundBankers`.
///   - scale: The number of digits a rounded value is allowed to have after its decimal point.
///   - exact: If `YES`, raises an ``NSDecimalNumberExactnessException`` if rounding causes loss of precision.
///   - overflow: If `YES`, raises an ``NSDecimalNumberOverflowException`` if a calculation exceeds the maximum value.
///   - underflow: If `YES`, raises an ``NSDecimalNumberUnderflowException`` if a calculation goes below the minimum value.
///   - divideByZero: If `YES`, raises an ``NSDecimalNumberDivideByZeroException`` if the receiver attempts to divide by zero.
/// - Returns: An initialized `NSDecimalNumberHandler` object with customized behavior.
- (instancetype)initWithRoundingMode:(NSRoundingMode)roundingMode scale:(short)scale raiseOnExactness:(BOOL)exact raiseOnOverflow:(BOOL)overflow raiseOnUnderflow:(BOOL)underflow raiseOnDivideByZero:(BOOL)divideByZero NS_DESIGNATED_INITIALIZER;

/// Returns an `NSDecimalNumberHandler` object with customized behavior.
///
/// - Parameters:
///   - roundingMode: The rounding mode to use.
///   - scale: The number of digits a rounded value is allowed to have after its decimal point.
///   - exact: If `YES`, raises an exception on loss of precision.
///   - overflow: If `YES`, raises an exception on overflow.
///   - underflow: If `YES`, raises an exception on underflow.
///   - divideByZero: If `YES`, raises an exception on divide by zero.
/// - Returns: An `NSDecimalNumberHandler` object with customized behavior.
+ (instancetype)decimalNumberHandlerWithRoundingMode:(NSRoundingMode)roundingMode scale:(short)scale raiseOnExactness:(BOOL)exact raiseOnOverflow:(BOOL)overflow raiseOnUnderflow:(BOOL)underflow raiseOnDivideByZero:(BOOL)divideByZero;

@end

/* **********	Extensions to other classes		*******/

@interface NSNumber (NSDecimalNumberExtensions)

/// The decimal structure representation of the number.
///
/// The value returned isn't guaranteed to be exact for `float` and `double` values.
@property (readonly) NSDecimal decimalValue;

@end

@interface NSScanner (NSDecimalNumberScanning)

/// Scans for an `NSDecimal` value, returning a found value by reference.
///
/// Invoke this method with `NULL` as `dcm` to simply scan past an `NSDecimal` representation.
///
/// - Parameters:
///   - dcm: Upon return, contains the scanned value.
/// - Returns: `YES` if the receiver finds a valid `NSDecimal` representation, otherwise `NO`.
- (BOOL)scanDecimal:(nullable NSDecimal *)dcm
#if defined(__swift__) // Deprecated for Swift only:
    API_DEPRECATED_WITH_REPLACEMENT("scanDecimal()", macosx(10.0,10.15), ios(2.0,13.0), watchos(2.0,27.0), tvos(9.0,13.0))
#endif
    ;

@end

NS_HEADER_AUDIT_END(nullability, sendability)
