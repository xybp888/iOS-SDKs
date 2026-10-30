/*
    NSMeasurement.h
    Copyright (c) 2015-2019, Apple Inc.
    All rights reserved.
 */

#import <Foundation/NSObject.h>
#import <Foundation/NSUnit.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

/// A numeric quantity labeled with a unit of measure, with support for unit conversion and unit-aware calculations.
///
/// An ``NSMeasurement`` object represents a quantity and unit of measure. The ``NSMeasurement`` class provides a programmatic interface to converting measurements into different units, as well as calculating the sum or difference between two measurements.
///
/// ``NSMeasurement`` objects are initialized with an ``Unit`` object and `double` value. ``NSMeasurement`` objects are immutable, and cannot be changed after being created.
///
/// You can use the ``MeasurementFormatter`` class to create localized string representations of ``NSMeasurement`` objects.
///
/// > Important:
/// > The Swift overlay to the Foundation framework provides the ``Measurement`` structure, which bridges to the ``NSMeasurement`` class. For more information about value types, see <doc://com.apple.documentation/documentation/swift/working-with-foundation-types>.
API_AVAILABLE(macos(10.12), ios(10.0), watchos(3.0), tvos(10.0))
@interface NSMeasurement<UnitType: NSUnit *> : NSObject<NSCopying, NSSecureCoding> {
@private
    UnitType _unit;
    double _doubleValue;
}

/// The unit component of the measurement.
@property (readonly, copy) UnitType unit;
/// The value component of the measurement.
@property (readonly) double doubleValue;

- (instancetype)init NS_UNAVAILABLE;
/// Initializes an `NSMeasurement` with the given `double` value and unit.
- (instancetype)initWithDoubleValue:(double)doubleValue unit:(UnitType)unit NS_DESIGNATED_INITIALIZER;

/// Returns a Boolean value that indicates whether this measurement can be converted to the given unit.
- (BOOL)canBeConvertedToUnit:(NSUnit *)unit;

/// Returns a measurement created by converting the receiver to the specified unit.
///
/// - Parameter unit: The unit to convert to. Must be of the same dimensionality as the receiver's unit.
/// - Returns: A new `NSMeasurement` object with the given unit and converted value.
- (NSMeasurement *)measurementByConvertingToUnit:(NSUnit *)unit;

/// Returns a new measurement by adding the receiver to the given measurement.
///
/// - Parameter measurement: The measurement to add. Must be of the same dimensionality as the receiver.
/// - Returns: A new `NSMeasurement` with the adjusted value and the same unit as the receiver.
- (NSMeasurement<UnitType> *)measurementByAddingMeasurement:(NSMeasurement<UnitType> *)measurement;
/// Returns a new measurement by subtracting the given measurement from the receiver.
///
/// - Parameter measurement: The measurement to subtract. Must be of the same dimensionality as the receiver.
/// - Returns: A new `NSMeasurement` with the adjusted value and the same unit as the receiver.
- (NSMeasurement<UnitType> *)measurementBySubtractingMeasurement:(NSMeasurement<UnitType> *)measurement;

@end

NS_HEADER_AUDIT_END(nullability, sendability)
