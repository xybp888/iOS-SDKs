/*      NSMassFormatter.h
        Copyright (c) 2014-2019, Apple Inc. All rights reserved.
 */

#import <Foundation/NSFormatter.h>

@class NSNumberFormatter;

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

/// The units supported by the `NSMassFormatter` class.
typedef NS_ENUM(NSInteger, NSMassFormatterUnit) {
    /// The gram unit.
    NSMassFormatterUnitGram = 11,
    /// The kilogram unit.
    NSMassFormatterUnitKilogram = 14,
    /// The ounce unit.
    NSMassFormatterUnitOunce = (6 << 8) + 1,
    /// The pound unit.
    NSMassFormatterUnitPound = (6 << 8) + 2,
    /// The stone unit.
    NSMassFormatterUnitStone = (6 << 8) + 3,
} API_AVAILABLE(macos(10.10), ios(8.0), watchos(2.0), tvos(9.0));

/// A formatter that provides localized descriptions of mass and weight values.
///
/// > Note:
/// > As of iOS 10, macOS 10.12, tvOS 10, and watchOS 3, Foundation provides the ``MeasurementFormatter`` class, which can be used to represent quantities of ``UnitMass`` to provide equivalent functionality to ``MassFormatter``. You are encouraged to transition to these new Foundation Units and Measurements APIs whenever possible.
API_AVAILABLE(macos(10.10), ios(8.0), watchos(2.0), tvos(9.0))
@interface NSMassFormatter : NSFormatter

/// The number formatter used to format the numbers in a mass string.
///
/// The default value is an `NSNumberFormatter` with `NSNumberFormatterDecimalStyle`.
@property (null_resettable, copy) NSNumberFormatter *numberFormatter;

/// The unit style used when creating string representations of mass values.
///
/// The default value is `NSFormattingUnitStyleMedium`.
@property NSFormattingUnitStyle unitStyle;

/// A Boolean value that indicates whether the resulting string represents a person's mass.
///
/// The default value is `NO`. If set to `YES`, the number argument for `stringFromKilograms:` and `unitStringFromKilograms:usedUnit:` is considered as a person's mass.
@property (getter = isForPersonMassUse) BOOL forPersonMassUse;

/// Returns a mass string for the provided value and unit.
- (NSString *)stringFromValue:(double)value unit:(NSMassFormatterUnit)unit;

/// Returns a mass string for the provided value in kilograms.
///
/// Formats a number in kilograms to a localized string with the locale-appropriate unit and an appropriate scale (e.g. 1.2kg = 2.64lb in the US locale).
- (NSString *)stringFromKilograms:(double)numberInKilograms;

/// Returns a unit string for the provided value and unit.
///
/// Returns a localized string of the given unit, and if the unit is singular or plural is based on the given number.
- (NSString *)unitStringFromValue:(double)value unit:(NSMassFormatterUnit)unit;

/// Returns a unit string based on the provided value in kilograms.
///
/// Returns the locale-appropriate unit, the same unit used by `stringFromKilograms:`.
- (NSString *)unitStringFromKilograms:(double)numberInKilograms usedUnit:(nullable NSMassFormatterUnit *)unitp;

/// No parsing is supported. This method will return `NO`.
- (BOOL)getObjectValue:(out id _Nullable * _Nullable)obj forString:(NSString *)string errorDescription:(out NSString * _Nullable * _Nullable)error;
@end

NS_HEADER_AUDIT_END(nullability, sendability)
