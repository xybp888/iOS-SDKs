/*      NSEnergyFormatter.h
        Copyright (c) 2014-2019, Apple Inc. All rights reserved.
 */

#import <Foundation/Foundation.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

/// The units supported by the `NSEnergyFormatter` class.
typedef NS_ENUM(NSInteger, NSEnergyFormatterUnit) {
    /// The joule unit.
    NSEnergyFormatterUnitJoule = 11,
    /// The kilojoule unit.
    NSEnergyFormatterUnitKilojoule = 14,
    /// The calorie unit (chemistry "calories", abbreviated "cal").
    NSEnergyFormatterUnitCalorie = (7 << 8) + 1,
    /// The kilocalorie unit (kilocalories in general, abbreviated "kcal", or "C" in some locales when `isForFoodEnergyUse` is set to `YES`).
    NSEnergyFormatterUnitKilocalorie = (7 << 8) + 2,
} API_AVAILABLE(macos(10.10), ios(8.0), watchos(2.0), tvos(9.0));

/// A formatter that provides localized descriptions of energy values.
///
/// > Note:
/// > As of iOS 10, macOS 10.12, tvOS 10, and watchOS 3, Foundation provides the ``MeasurementFormatter`` class, which can be used to represent quantities of ``UnitEnergy`` to provide equivalent functionality to ``EnergyFormatter``. You are encouraged to transition to these new Foundation Units and Measurements APIs whenever possible.
API_AVAILABLE(macos(10.10), ios(8.0), watchos(2.0), tvos(9.0))
@interface NSEnergyFormatter : NSFormatter

/// The number formatter used to format the numbers in an energy string.
///
/// The default value is an `NSNumberFormatter` with `NSNumberFormatterDecimalStyle`.
@property (null_resettable, copy) NSNumberFormatter *numberFormatter;

/// The unit style used when creating string representations of energy values.
///
/// The default value is `NSFormattingUnitStyleMedium`.
@property NSFormattingUnitStyle unitStyle;

/// A Boolean value that indicates whether the resulting string is used to represent food energy.
///
/// The default value is `NO`. If set to `YES`, `NSEnergyFormatterUnitKilocalorie` may be displayed as "C" instead of "kcal".
@property (getter = isForFoodEnergyUse) BOOL forFoodEnergyUse;

/// Returns an energy string for the provided value and unit.
- (NSString *)stringFromValue:(double)value unit:(NSEnergyFormatterUnit)unit;

/// Returns an energy string for the provided value in joules.
///
/// Formats a number in joules to a localized string with the locale-appropriate unit and an appropriate scale (e.g. 10.3J = 2.46cal in the US locale).
- (NSString *)stringFromJoules:(double)numberInJoules;

/// Returns a unit string for the provided value and unit.
///
/// Returns a localized string of the given unit, and if the unit is singular or plural is based on the given number.
- (NSString *)unitStringFromValue:(double)value unit:(NSEnergyFormatterUnit)unit;

/// Returns a unit string based on the provided value in joules.
///
/// Returns the locale-appropriate unit, the same unit used by `stringFromJoules:`.
- (NSString *)unitStringFromJoules:(double)numberInJoules usedUnit:(nullable NSEnergyFormatterUnit *)unitp;

/// No parsing is supported. This method will return `NO`.
- (BOOL)getObjectValue:(out id _Nullable * _Nullable)obj forString:(NSString *)string errorDescription:(out NSString * _Nullable * _Nullable)error;
@end

NS_HEADER_AUDIT_END(nullability, sendability)
