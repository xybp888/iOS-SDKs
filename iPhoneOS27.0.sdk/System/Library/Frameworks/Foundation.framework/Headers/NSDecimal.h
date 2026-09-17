/*	NSDecimal.h
	Copyright (c) 1995-2019, Apple Inc. All rights reserved.
*/

#include <limits.h>
#import <Foundation/NSObjCRuntime.h>

@class NSDictionary;

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

/* **************	Type definitions		***********/

/// These constants specify rounding behaviors.
typedef NS_ENUM(NSUInteger, NSRoundingMode) {
    /// Round to the closest possible return value; when caught halfway between two positive numbers, round up; when caught between two negative numbers, round down.
    NSRoundPlain,
    /// Round return values down.
    NSRoundDown,
    /// Round return values up.
    NSRoundUp,
    /// Round to the closest possible return value; when halfway between two possibilities, return the possibility whose last digit is even.
    NSRoundBankers
};

/// Calculation error constants used to describe an error in ``NSDecimalNumberBehaviors/exceptionDuringOperation(_:error:leftOperand:rightOperand:)``.
typedef NS_ENUM(NSUInteger, NSCalculationError) {
    /// No error occurred.
    NSCalculationNoError = 0,
    /// The number can't be represented in 38 significant digits.
    NSCalculationLossOfPrecision,
    /// The number is too small to represent.
    NSCalculationUnderflow,
    /// The number is too large to represent.
    NSCalculationOverflow,
    /// The caller tried to divide by `0`.
    NSCalculationDivideByZero
};

#define NSDecimalMaxSize (8)
    // Give a precision of at least 38 decimal digits, 128 binary positions.

#define NSDecimalNoScale SHRT_MAX

/// A structure representing a base-10 number.
typedef struct NS_SWIFT_SENDABLE {
    signed   int _exponent:8;
    unsigned int _length:4;     // length == 0 && isNegative -> NaN
    unsigned int _isNegative:1;
    unsigned int _isCompact:1;
    unsigned int _reserved:18;
    unsigned short _mantissa[NSDecimalMaxSize];
} NSDecimal;

/// Returns a Boolean value indicating whether a decimal value is not a number.
///
/// - Parameter dcm: The decimal value to evaluate.
/// - Returns: `NO` if the value in `dcm` represents a valid number, otherwise `YES`.
NS_INLINE BOOL NSDecimalIsNotANumber(const NSDecimal *dcm)
  { return ((dcm->_length == 0) && dcm->_isNegative); }

/* **************	Operations		***********/

/// Copies the value of a decimal number.
FOUNDATION_EXPORT void NSDecimalCopy(NSDecimal *destination, const NSDecimal *source);

/// Compacts the decimal structure for efficiency.
FOUNDATION_EXPORT void NSDecimalCompact(NSDecimal *number);

/// Compares two decimal values.
FOUNDATION_EXPORT NSComparisonResult NSDecimalCompare(const NSDecimal *leftOperand, const NSDecimal *rightOperand);

/// Rounds a decimal value to the given scale using the given mode.
///
/// The `result` parameter may be a pointer to the same space as `number`. The `scale` parameter indicates the number of significant digits after the decimal point.
FOUNDATION_EXPORT void NSDecimalRound(NSDecimal *result, const NSDecimal *number, NSInteger scale, NSRoundingMode roundingMode);

/// Normalizes the internal representation of two decimal numbers to simplify later operations.
FOUNDATION_EXPORT NSCalculationError NSDecimalNormalize(NSDecimal *number1, NSDecimal *number2, NSRoundingMode roundingMode);

/// Adds two decimal values.
///
/// The `result` parameter may be a pointer to the same space as `leftOperand` or `rightOperand`.
FOUNDATION_EXPORT NSCalculationError NSDecimalAdd(NSDecimal *result, const NSDecimal *leftOperand, const NSDecimal *rightOperand, NSRoundingMode roundingMode);

/// Subtracts one decimal value from another.
///
/// The `result` parameter may be a pointer to the same space as `leftOperand` or `rightOperand`.
FOUNDATION_EXPORT NSCalculationError NSDecimalSubtract(NSDecimal *result, const NSDecimal *leftOperand, const NSDecimal *rightOperand, NSRoundingMode roundingMode);

/// Multiplies two decimal numbers together.
///
/// The `result` parameter may be a pointer to the same space as `leftOperand` or `rightOperand`.
FOUNDATION_EXPORT NSCalculationError NSDecimalMultiply(NSDecimal *result, const NSDecimal *leftOperand, const NSDecimal *rightOperand, NSRoundingMode roundingMode);

/// Divides one decimal number by another.
///
/// Division could be silently inexact. The `result` parameter may be a pointer to the same space as `leftOperand` or `rightOperand`.
FOUNDATION_EXPORT NSCalculationError NSDecimalDivide(NSDecimal *result, const NSDecimal *leftOperand, const NSDecimal *rightOperand, NSRoundingMode roundingMode);

/// Raises a decimal number to the given power.
FOUNDATION_EXPORT NSCalculationError NSDecimalPower(NSDecimal *result, const NSDecimal *number, NSUInteger power, NSRoundingMode roundingMode);

/// Multiplies a decimal number by a power of 10.
FOUNDATION_EXPORT NSCalculationError NSDecimalMultiplyByPowerOf10(NSDecimal *result, const NSDecimal *number, short power, NSRoundingMode roundingMode);

/// Returns a string representation of a decimal value appropriate for the given locale.
FOUNDATION_EXPORT NSString *NSDecimalString(const NSDecimal *dcm, id _Nullable locale);

NS_HEADER_AUDIT_END(nullability, sendability)
