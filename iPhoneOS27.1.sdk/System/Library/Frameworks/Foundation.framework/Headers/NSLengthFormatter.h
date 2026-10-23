/*      NSLengthFormatter.h
        Copyright (c) 2014-2019, Apple Inc. All rights reserved.
 */

#import <Foundation/Foundation.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

/// The units supported by the `NSLengthFormatter` class.
typedef NS_ENUM(NSInteger, NSLengthFormatterUnit) {
    /// The millimeter unit.
    NSLengthFormatterUnitMillimeter = 8,
    /// The centimeter unit.
    NSLengthFormatterUnitCentimeter = 9,
    /// The meter unit.
    NSLengthFormatterUnitMeter = 11,
    /// The kilometer unit.
    NSLengthFormatterUnitKilometer = 14,
    /// The inch unit.
    NSLengthFormatterUnitInch = (5 << 8) + 1,
    /// The foot unit.
    NSLengthFormatterUnitFoot = (5 << 8) + 2,
    /// The yard unit.
    NSLengthFormatterUnitYard = (5 << 8) + 3,
    /// The mile unit.
    NSLengthFormatterUnitMile = (5 << 8) + 4,
} API_AVAILABLE(macos(10.10), ios(8.0), watchos(2.0), tvos(9.0));

/// A formatter that provides localized descriptions of linear distances, such as length and height measurements.
///
/// > Note:
/// > As of iOS 10, macOS 10.12, tvOS 10, and watchOS 3, Foundation provides the ``MeasurementFormatter`` class, which can be used to represent quantities of ``UnitLength`` to provide equivalent functionality to ``LengthFormatter``. You are encouraged to transition to these new Foundation Units and Measurements APIs whenever possible.
API_AVAILABLE(macos(10.10), ios(8.0), watchos(2.0), tvos(9.0))
@interface NSLengthFormatter : NSFormatter

/// The number formatter used to format the numbers in a length string.
///
/// The default value is an `NSNumberFormatter` with `NSNumberFormatterDecimalStyle`.
@property (null_resettable, copy) NSNumberFormatter *numberFormatter;

/// The unit style used when creating string representations of length values.
///
/// The default value is `NSFormattingUnitStyleMedium`.
@property NSFormattingUnitStyle unitStyle;

/// A Boolean value that indicates whether the resulting string represents a person's height.
///
/// The default value is `NO`. If set to `YES`, the number argument for `stringFromMeters:` and `unitStringFromMeters:usedUnit:` is considered as a person's height.
@property (getter = isForPersonHeightUse) BOOL forPersonHeightUse;

/// Returns a length string for the provided value and unit.
- (NSString *)stringFromValue:(double)value unit:(NSLengthFormatterUnit)unit;

/// Returns a length string for the provided value in meters.
///
/// Formats a number in meters to a localized string with the locale-appropriate unit and an appropriate scale (e.g. 4.3m = 14.1ft in the US locale).
- (NSString *)stringFromMeters:(double)numberInMeters;

/// Returns a unit string for the provided value and unit.
///
/// Returns a localized string of the given unit, and if the unit is singular or plural is based on the given number.
- (NSString *)unitStringFromValue:(double)value unit:(NSLengthFormatterUnit)unit;

/// Returns a unit string based on the provided value in meters.
///
/// Returns the locale-appropriate unit, the same unit used by `stringFromMeters:`.
- (NSString *)unitStringFromMeters:(double)numberInMeters usedUnit:(nullable NSLengthFormatterUnit *)unitp;

/// No parsing is supported. This method will return `NO`.
- (BOOL)getObjectValue:(out id _Nullable * _Nullable)obj forString:(NSString *)string errorDescription:(out NSString * _Nullable * _Nullable)error;
@end

NS_HEADER_AUDIT_END(nullability, sendability)
