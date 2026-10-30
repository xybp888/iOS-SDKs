/*
 NSUnit.h
 Copyright (c) 2015-2019, Apple Inc.
 All rights reserved.
 */

#import <Foundation/NSObject.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

#pragma mark Unit Converters

/// An abstract class that provides a description of how to convert a unit to and from the base unit of its dimension.
///
/// For units that can be converted by a scale factor or linear equation, use the concrete subclass ``UnitConverterLinear``.
///
/// ### Subclassing Notes
///
/// ``NSUnitConverter`` is an abstract class that is intended for subclassing. You can implement your own subclass of ``NSUnitConverter`` to convert between units according to any desired mapping function. For example, units may be converted using a logarithmic, exponential, or quantile scale.
///
/// #### Methods to Override
///
/// All subclasses must fully implement the following methods:
///
/// - ``baseUnitValue(fromValue:)``
/// - ``value(fromBaseUnitValue:)``
///
/// #### Alternatives to Subclassing
///
/// As stated above, most physical units can be converted using a linear equation with ``UnitConverterLinear``. You should only create a custom subclass of ``NSUnitConverter`` for units that cannot be converted in this way.
API_AVAILABLE(macosx(10.12), ios(10.0), watchos(3.0), tvos(10.0))
@interface NSUnitConverter : NSObject

/*
 The following methods perform conversions to and from the base unit of a unit class's dimension.  Each unit is defined against the base unit for the dimension to which the unit belongs.

 These methods are implemented differently depending on the type of conversion.  The default implementation in NSUnitConverter simply returns the value.

 These methods exist for the sole purpose of creating custom conversions for units in order to support converting a value from one kind of unit to another in the same dimension.  NSUnitConverter is an abstract class that is meant to be subclassed.  There is no need to call these methods directly to do a conversion -- the correct way to convert a measurement is to use [NSMeasurement measurementByConvertingToUnit:].  measurementByConvertingToUnit: uses the following 2 methods internally to perform the conversion.

 When creating a custom unit converter, you must override these two methods to implement the conversion to and from a value in terms of a unit and the corresponding value in terms of the base unit of that unit's dimension in order for conversion to work correctly.
 */

/// For a given unit, returns the specified value of that unit in terms of the base unit of its dimension.
///
/// This method takes a value in a particular unit and returns the result of converting it into the base unit of that unit's dimension.
/// For example, a converter for the miles unit calling this method, passing `1.0` to the `value` parameter, results in `1609.34` (_1 mi = 1609.34 m_).
///
/// @param value Value in terms of the unit class.
/// @return Value in terms of the base unit.
- (double)baseUnitValueFromValue:(double)value;

/// For a given unit, returns the specified base unit value in terms of that unit.
///
/// This method takes in a value in terms of the base unit of a unit's dimension and returns the equivalent value in terms of the unit.
///
/// @param baseUnitValue Value in terms of the base unit.
/// @return Value in terms of the unit class.
- (double)valueFromBaseUnitValue:(double)baseUnitValue;

@end


/// A description of how to convert between units using a linear equation.
///
/// A linear equation for unit conversion takes the form `y = mx + b`, such that the following is true:
///
/// - `y` is the value in terms of the base unit of the dimension.
/// - `m` is the known coefficient to use for this unit's conversion.
/// - `x` is the value in terms of the unit on which you call this method.
/// - `b` is the known constant to use for this unit's conversion.
///
/// The `baseUnitValueFromValue:` method performs the conversion in the form of `y = mx + b`, where `x` represents the value passed in and `y` represents the value returned. The `valueFromBaseUnitValue:` method performs the inverse conversion in the form of `x = (y - b) / m`, where `y` represents the value passed in and `x` represents the value returned.
///
/// For example, consider the ``UnitTemperature/fahrenheit`` unit that ``UnitTemperature`` defines. The ``UnitConverter/baseUnitValue(fromValue:)`` method calculates the value in the base unit, ``UnitTemperature/kelvin``, using the formula `K = (0.55555555555556) × °F + 255.37222222222427`. The ``UnitConverter/value(fromBaseUnitValue:)`` method calculates the value in ``UnitTemperature/fahrenheit`` using the formula `°F = (K — 255.37222222222427) / (0.55555555555556)`, where the ``coefficient`` is `(0.55555555555556)` and the ``constant`` is `255.37222222222427`.
///
/// @TabNavigator {
/// @Tab("Swift") {
/// ```swift
/// let kelvinToFahrenheit = UnitConverterLinear(coefficient: 0.55555555555556, constant: 255.37222222222427)
/// ```
/// }
/// @Tab("Objective-C") {
/// ```objc
/// NSUnitConverter *kelvinToFahrenheit = [[NSUnitConverterLinear alloc] initWithCoefficient:0.55555555555556 constant:255.37222222222427];
/// ```
/// }
/// }
///
///
/// Units that perform conversion using only a scale factor have a ``coefficient`` equal to the scale factor and a ``constant`` equal to `0`. For example, consider the ``UnitLength/kilometers`` unit ``UnitLength`` defines. The ``UnitConverter/baseUnitValue(fromValue:)`` method calculates the value in meters using the formula `valueInMeters = 1000 * valueInKilometers + 0`. The ``UnitConverter/value(fromBaseUnitValue:)`` calculates the value in kilometers using the formula `valueInKilometers = (valueInMeters - 0) / 1000`, where the coefficient is `1000` and the constant is `0`.
///
/// @TabNavigator {
/// @Tab("Swift") {
/// ```swift
/// let kilometersToMeters = UnitConverterLinear(coefficient: 1000.0, constant: 0.0)
/// ```
/// }
/// @Tab("Objective-C") {
/// ```objc
/// NSUnitConverterLinear *kilometersToMeters = [[NSUnitConverterLinear alloc] initWithCoefficient:1000.0 constant:0.0];
/// ```
/// }
/// }
API_AVAILABLE(macosx(10.12), ios(10.0), watchos(3.0), tvos(10.0))
@interface NSUnitConverterLinear : NSUnitConverter <NSSecureCoding> {
@private
    double _coefficient;
    double _constant;
}

/*
 For units that require linear conversion, the methods perform calculations in the form of y = ax + b, where
    - x is the value in terms of the unit on which this method is called
    - y is the value in terms of the base unit of the dimension
    - a is the known coefficient used for this unit's conversion
    - b is the known constant used for this unit's conversion

 baseUnitValueFromValue: performs the conversion in the form of y = ax + b, where x represents the value passed in and y represents the value returned.
 valueFromBaseUnitValue: performs the inverse conversion in the form of x = (y + (-1 * b))/a, where y represents the value passed in and x represents the value returned.

 An example of this is NSUnitTemperature.  For Celsius, baseUnitValueFromValue: calculates the value in Kelvin using the formula
            K = 1 * °C + 273.15
 and valueFromBaseUnitValue: calculates the value in Celsius using the formula
            C° = (K + (-1 * 273.15))/1
 where the coefficient is 1 and the constant is 273.15.

 For units that only require conversion by scale factor, the coefficient is the scale factor and the constant is always 0.  baseUnitValueFromValue: calculates the value in meters using the formula
            valueInMeters = 1000 * valueInKilometers + 0
 and valueFromBaseUnitValue: calculates the value in kilometers using the formula
            valueInKilometers = valueInMeters / 1000
 where the coefficient is 1000 and the constant is 0.  This API provides a convenience initializer initWithCoefficient: that assumes the constant is 0.
 */
/// The coefficient to use in the linear unit conversion calculation.
@property (readonly) double coefficient;
/// The constant to use in the linear unit conversion calculation.
@property (readonly) double constant;

/// Initializes a linear unit converter with the specified coefficient, using a constant of `0`.
- (instancetype)initWithCoefficient:(double)coefficient;

/// Initializes a linear unit converter with the specified coefficient and constant.
- (instancetype)initWithCoefficient:(double)coefficient constant:(double)constant NS_DESIGNATED_INITIALIZER;

@end


#pragma mark Unit

/// An abstract class representing a unit of measure.
///
/// Each instance of an ``Unit`` subclass consists of a ``symbol``, which can be used to create string representations of ``NSMeasurement`` objects with the ``MeasurementFormatter`` class.
///
/// The ``Dimension`` subclass is an abstract class that represents a dimensional unit, which can be converted into different units of the same type. The Foundation framework provides several concrete ``Dimension`` subclasses to represent the most common physical quantities, including mass, length, duration, and speed.
///
/// ### Subclassing Notes
///
/// ``NSUnit`` is intended for subclassing. For dimensional units, you should use one of the Apple provided ``Dimension`` subclasses listed in Table 1 of ``Dimension``, or create a custom subclass of ``Dimension``. You can create a direct subclass of ``NSUnit`` to represent a custom dimensionless unit, such as a count, score, or ratio.
NS_SWIFT_SENDABLE
API_AVAILABLE(macosx(10.12), ios(10.0), watchos(3.0), tvos(10.0))
@interface NSUnit : NSObject <NSCopying, NSSecureCoding> {
@private
    NSString *_symbol;
}

/// The symbolic representation of the unit.
///
/// The symbol of a unit is a string that can be used to designate a number as a quantity of a particular unit in user-readable representations.
/// Units typically have symbols that are abbreviated and standardized, so as to be easily and unambiguously conveyed.
/// For example, the `milePerHour` unit has the symbol `mph`.
/// If a unit does not have a standardized or well-understood symbol, the lowercase name of the unit can be used.
/// For example, the `metricCup` unit has the symbol `metric cup`.
///
/// Unit symbols may incorporate a metric prefix to indicate a multiple or fraction of existing unit symbols.
/// For example, the `kilogram` unit has the symbol `kg`, which uses the SI prefix k for kilo- to indicate a magnitude of 10^3 for the `gram` unit,
/// and the `microgram` unit has the symbol `µg`, which uses the SI prefix µ for micro- to indicate a magnitude of 10^-6 for the `gram` unit.
@property (readonly, copy) NSString *symbol;

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new API_UNAVAILABLE(macos, ios, watchos, tvos);

/// Initializes a unit with the specified symbol.
- (instancetype)initWithSymbol:(NSString *)symbol NS_DESIGNATED_INITIALIZER;

@end


#pragma mark Dimensions

/// An abstract class representing a dimensional unit of measure.
///
/// The Foundation framework provides concrete subclasses for many of the most common types of physical units.
///
/// Table 1: ``Dimension`` subclasses.
///
/// | NSDimension subclass | Description | Base unit |
/// |---|---|---|
/// | ``UnitAcceleration`` | Unit of measure for acceleration | meters per second squared (m/s²) |
/// | ``UnitAngle`` | Unit of measure for planar angle and rotation | degrees (°) |
/// | ``UnitArea`` | Unit of measure for area | square meters (m²) |
/// | ``UnitConcentrationMass`` | Unit of measure for concentration of mass | grams per liter (g/L) |
/// | ``UnitDispersion`` | Unit of measure for dispersion | parts per million (ppm) |
/// | ``UnitDuration`` | Unit of measure for duration of time | seconds (sec) |
/// | ``UnitElectricCharge`` | Unit of measure for electric charge | coulombs (C) |
/// | ``UnitElectricCurrent`` | Unit of measure for electric current | amperes (A) |
/// | ``UnitElectricPotentialDifference`` | Unit of measure for electric potential difference | volts (V) |
/// | ``UnitElectricResistance`` | Unit of measure for electric resistance | ohms (Ω) |
/// | ``UnitEnergy`` | Unit of measure for energy | joules (J) |
/// | ``UnitFrequency`` | Unit of measure for frequency | hertz (Hz) |
/// | ``UnitFuelEfficiency`` | Unit of measure for fuel efficiency | liters per 100 kilometers (L/100km) |
/// | ``UnitIlluminance`` | Unit of measure for illuminance | lux (lx) |
/// | ``UnitInformationStorage`` | Unit of measure for quantities of information | bytes (b) |
/// | ``UnitLength`` | Unit of measure for length | meters (m) |
/// | ``UnitMass`` | Unit of measure for mass | kilograms (kg) |
/// | ``UnitPower`` | Unit of measure for power | watts (W) |
/// | ``UnitPressure`` | Unit of measure for pressure | newtons per square meter (N/m²) |
/// | ``UnitSpeed`` | Unit of measure for speed | meters per second (m/s) |
/// | ``UnitTemperature`` | Unit of measure for temperature | kelvin (K) |
/// | ``UnitVolume`` | Unit of measure for volume | liters (L) |
///
///
/// Each instance of a ``Dimension`` subclass has a ``converter``, which represents the unit in terms of the dimension's ``baseUnit()``. For example, the `NSLengthUnit` class uses ``UnitLength/meters`` as its base unit. The system defines the predefined ``UnitLength/miles`` unit by a ``UnitConverterLinear`` with a ``UnitConverterLinear/coefficient`` of `1609.34`, which corresponds to the conversion ratio of miles to meters (1 mi = 1609.34 m); the system defines the predefined ``UnitLength/meters`` unit by a ``UnitConverterLinear`` with a ``UnitConverterLinear/coefficient`` of `1.0` because it's the base unit.
///
/// You typically use an `NSDimension` subclass in conjunction with the ``NSMeasurement`` class to represent specific quantities of a particular unit.
///
/// ### Working with Custom Units
///
/// In addition to the Apple-provided units, you can define custom units. You can initialize custom units from a symbol and converter of an existing type or implemented as a class method of an existing type for additional convenience. You can also define your own `NSDimension` subclass to represent an entirely new unit dimension.
///
/// #### Initializing a Custom Unit with a Specified Symbol and Definition
///
/// The simplest way to define a custom unit is to create a new instance of an existing `NSDimension` subclass using the ``init(symbol:converter:)`` method.
///
/// For example, the _smoot_ is a nonstandard unit of length (1 smoot = 1.70180 m). You can create a new instance of ``UnitLength`` as follows:
///
/// @TabNavigator {
/// @Tab("Swift") {
/// ```swift
/// let smoots = UnitLength(symbol: "smoot", converter: UnitConverterLinear(coefficient: 1.70180))
/// ```
/// }
/// @Tab("Objective-C") {
/// ```objc
/// NSUnitConverter *smootsToMeters = [[NSUnitConverterLinear alloc] initWithCoefficient:1.70180];
/// NSUnitLength *smoots = [[NSUnitLength alloc] initWithSymbol:@"smoot" converter:smootsToMeters];
/// ```
/// }
/// }
///
///
/// #### Extending Existing Dimension Subclasses
///
/// Alternatively, if you use a custom unit extensively throughout an app, consider extending the corresponding ``Dimension`` subclass and adding a static variable.
///
/// For example, a measurement of speed can be furlongs per fortnight (1 fur/ftn = 201.168 m / 1,209,600 s). If an app makes frequent use of this unit, you can extend ``UnitSpeed`` to add a `furlongsPerFortnight` static variable for convenient access as follows:
///
/// @TabNavigator {
/// @Tab("Swift") {
/// ```swift
/// extension UnitSpeed {
/// static let furlongPerFortnight = UnitSpeed(symbol: "fur/ftn", converter: UnitConverterLinear(coefficient: 201.168 / 1209600.0))
/// }
/// ```
/// }
/// @Tab("Objective-C") {
/// ```objc
/// @interface NSUnitSpeed ()
/// + (NSUnitSpeed *)furlongsPerFortnight;
/// @end
///
/// @implementation NSUnitSpeed ()
/// + (NSUnitSpeed *)furlongsPerFortnight {
/// NSUnitConverter *furlongsPerFortnightToMetersPerSecond = [[NSUnitConverterLinear alloc] initWithCoefficient:201.168 / 1209600.0];
/// return [[NSUnitSpeed alloc] initWithSymbol:@"fur/ftn" converter:furlongsPerFortnightToMetersPerSecond];
/// }
/// @end
/// ```
/// }
/// }
///
///
/// #### Creating a Custom Dimension Subclass
///
/// You can create a new subclass of ``Dimension`` to describe a new unit dimension.
///
/// For example, the Foundation framework doesn't define any units for radioactivity. Radioactivity is the process by which the nucleus of an atom emits radiation. The SI unit of measure for radioactivity is the becquerel (Bq), which is the quantity of radioactive material in which one nucleus decays per second (1 Bq = 1 s-1). Radioactivity is also commonly described in terms of curies (Ci), a unit defined relative to the decay of one gram of the radium-226 isotope (1 Ci = 3.7 × 1010 Bq). You can implement a `CustomUnitRadioactivity` class that defines both units of radioactivity as follows:
///
/// @TabNavigator {
/// @Tab("Swift") {
/// ```swift
/// class CustomRadioactivityUnit: Dimension {
/// static let becquerel = CustomRadioactivityUnit(symbol: "Bq", UnitConverterLinear(coefficient: 1.0))
/// static let curie = CustomRadioactivityUnit(symbol: "Ci", UnitConverterLinear(coefficient: 3.7e10))
///
/// static let baseUnit = self.becquerel
/// }
/// ```
/// }
/// @Tab("Objective-C") {
/// ```objc
/// @interface CustomUnitRadioactivity: NSDimension
/// + (CustomUnitRadioactivity *)becquerels;
/// + (CustomUnitRadioactivity *)curies;
/// @end
///
/// @implementation CustomRadioactivityUnit
/// + (CustomUnitRadioactivity *)becquerels {
/// NSUnitConverter *baseUnitConverter = [[NSUnitConverterLinear alloc] initWithCoefficient:1];
/// return [[CustomUnitRadioactivity alloc] initWithSymbol:@"Bq" converter:baseUnitConverter];
/// }
///
/// + (CustomUnitRadioactivity *)curies {
/// NSUnitConverter *curiesToBecquerels = [[NSUnitConverterLinear alloc] initWithCoefficient:3.7e10];
/// return [[CustomUnitRadioactivity alloc] initWithSymbol:@"Ci" converter:curiesToBecquerels];
/// }
///
/// + (instancetype)baseUnit {
/// return [self bacquerels];
/// }
/// @end
/// ```
/// }
/// }
///
///
/// ### Subclassing Notes
///
/// The system provides ``Dimension`` for subclassing. Although the subclasses listed in Table 1 above are suitable for most purposes, you may want to define a custom unit type. For instance, you may need a custom unit type to represent a derived unit, such as magnetic flux (measured as the product of electric potential difference and time).
///
/// To represent dimensionless units, subclass ``Unit`` directly.
///
/// #### Methods to Override
///
/// All subclasses must fully implement the ``baseUnit()`` method designating the base unit, relative to which you define any additional units.
///
/// You must also implement a class method named for the base unit itself, to use interchangeably. For example, the ``UnitIlluminance`` class defines its ``baseUnit()`` in terms of the lux (lx) and provides a corresponding ``UnitIlluminance/lux`` class method.
///
/// #### Alternatives to Subclassing
///
/// As described in <doc:#Working-with-Custom-Units>, you need to create a custom subclass of ``Dimension`` only if you or the system haven't defined a unit of the desired dimension. You can define a custom unit for an existing ``Dimension`` subclass by either calling the ``init(symbol:converter:)`` method or extending the subclass and adding a corresponding class method.
NS_SWIFT_SENDABLE
API_AVAILABLE(macosx(10.12), ios(10.0), watchos(3.0), tvos(10.0))
@interface NSDimension : NSUnit <NSSecureCoding> {
@private
    NSUInteger _reserved;
@protected
    NSUnitConverter *_converter;
}

/// The unit converter that describes how this unit converts to and from the base unit of its dimension.
@property (readonly, copy) NSUnitConverter *converter;

/// Initializes a dimensional unit with the specified symbol and unit converter.
- (instancetype)initWithSymbol:(NSString *)symbol converter:(NSUnitConverter *)converter NS_DESIGNATED_INITIALIZER;

/// Returns the base unit of the dimension.
///
/// The default implementation returns `nil` to indicate that the `NSDimension` class should not be used directly.
///
/// When implementing a subclass, you should return a unit converter that returns the inputted value for both the
/// `baseUnitValueFromValue:` and `valueFromBaseUnitValue:` methods. You can create a unit converter for a base unit
/// using the `NSUnitConverterLinear` `initWithCoefficient:` initializer, passing `1` as the coefficient.
+ (instancetype)baseUnit;

@end


#pragma mark - Predefined Dimensions

/// A unit of measure for acceleration.
///
/// You typically use instances of ``NSUnitAcceleration`` to represent specific quantities of acceleration using the ``NSMeasurement`` class.
///
/// ### Acceleration
///
/// Acceleration is the rate of change of velocity. Acceleration can be expressed by SI derived units in terms of meters per second squared (m/s2).
///
/// The ``NSUnitAcceleration`` class defines its ``Dimension/baseUnit()`` as ``metersPerSecondSquared``, and provides the following units, which are initialized using ``UnitConverterLinear`` converters with the specified coefficients:
///
///
/// | Name | Method | Symbol | Coefficient |
/// |---|---|---|---|
/// | Meters Per Second Squared | ``metersPerSecondSquared`` | m/s² | `1.0` |
/// | Gravity | ``gravity`` | g | `9.81` |
NS_SWIFT_SENDABLE
API_AVAILABLE(macosx(10.12), ios(10.0), watchos(3.0), tvos(10.0))
@interface NSUnitAcceleration : NSDimension <NSSecureCoding>
/*
 Base unit - metersPerSecondSquared
 */

/// The meters per second squared unit of acceleration.
@property (class, readonly, copy) NSUnitAcceleration *metersPerSecondSquared;
/// The gravity unit of acceleration.
@property (class, readonly, copy) NSUnitAcceleration *gravity;

@end

/// A unit of measure for planar angle and rotation.
///
/// You typically use instances of ``NSUnitAngle`` to represent specific quantities of planar angle using the ``NSMeasurement`` class.
///
/// ### Angle
///
/// Angle is a quantity of rotation. The SI unit for angle is the radian (rad), which is dimensionless and defined to be the angle subtended by an arc that is equal in length to the radius of a circle. Angle is also commonly expressed in terms of degrees (°) and revolutions (rev).
///
/// The ``NSUnitAngle`` class defines its ``Dimension/baseUnit()`` as ``degrees``, and provides the following units, which are initialized using ``UnitConverterLinear`` converters with the specified coefficients:
///
///
/// | Name | Method | Symbol | Definition |
/// |---|---|---|---|
/// | Degrees | ``degrees`` | ° | `1.0` |
/// | Arc Minutes | ``arcMinutes`` | ʹ | `0.016667` |
/// | Arc Seconds | ``arcSeconds`` | ʺ | `0.00027778` |
/// | Radians | ``radians`` | rad | `57.2958` |
/// | Gradians | ``gradians`` | grad | `0.9` |
/// | Revolutions | ``revolutions`` | rev | `360` |
NS_SWIFT_SENDABLE
API_AVAILABLE(macosx(10.12), ios(10.0), watchos(3.0), tvos(10.0))
@interface NSUnitAngle : NSDimension <NSSecureCoding>
/*
 Base unit - degrees
 */

/// The degrees unit of angle.
@property (class, readonly, copy) NSUnitAngle *degrees;
/// The arc minutes unit of angle.
@property (class, readonly, copy) NSUnitAngle *arcMinutes;
/// The arc seconds unit of angle.
@property (class, readonly, copy) NSUnitAngle *arcSeconds;
/// The radians unit of angle.
@property (class, readonly, copy) NSUnitAngle *radians;
/// The gradians unit of angle.
@property (class, readonly, copy) NSUnitAngle *gradians;
/// The revolutions unit of angle.
@property (class, readonly, copy) NSUnitAngle *revolutions;

@end

/// A unit of measure for area.
///
/// You typically use instances of ``NSUnitArea`` to represent specific quantities of area using the ``NSMeasurement`` class.
///
/// ### Area
///
/// Area is a quantity of extent in two dimensions. Area can be expressed by SI derived units in terms of square meters (m2). Area is also commonly measured in square feet (ft2) and acres (ac).
///
/// The ``NSUnitArea`` class defines its ``Dimension/baseUnit()`` as ``squareMeters``, and provides the following units, which are initialized using ``UnitConverterLinear`` converters with the specified coefficients:
///
///
/// | Name | Method | Symbol | Coefficient |
/// |---|---|---|---|
/// | Square Megameters | ``squareMegameters`` | Mm² | `1e12` |
/// | Square Kilometers | ``squareKilometers`` | km² | `1000000.0` |
/// | Square Meters | ``squareMeters`` | m² | `1.0` |
/// | Square Centimeter | ``squareCentimeters`` | cm² | `0.0001` |
/// | Square Millimeters | ``squareMillimeters`` | mm² | `0.000001` |
/// | Square Micrometers | ``squareMicrometers`` | µm² | `1e-12` |
/// | Square Nanometers | ``squareNanometers`` | nm² | `1e-18` |
/// | Square Inches | ``squareInches`` | in² | `0.00064516` |
/// | Square Feet | ``squareFeet`` | ft² | `0.092903` |
/// | Square Yards | ``squareYards`` | yd² | `0.836127` |
/// | Square Miles | ``squareMiles`` | mi² | `2.59e+6` |
/// | Acres | ``acres`` | ac | `4046.86` |
/// | Ares | ``ares`` | a | `100` |
/// | Hectares | ``hectares`` | ha | `10000` |
NS_SWIFT_SENDABLE
API_AVAILABLE(macosx(10.12), ios(10.0), watchos(3.0), tvos(10.0))
@interface NSUnitArea : NSDimension <NSSecureCoding>
/*
 Base unit - squareMeters
 */

/// The square megameters unit of area.
@property (class, readonly, copy) NSUnitArea *squareMegameters;
/// The square kilometers unit of area.
@property (class, readonly, copy) NSUnitArea *squareKilometers;
/// The square meters unit of area.
@property (class, readonly, copy) NSUnitArea *squareMeters;
/// The square centimeters unit of area.
@property (class, readonly, copy) NSUnitArea *squareCentimeters;
/// The square millimeters unit of area.
@property (class, readonly, copy) NSUnitArea *squareMillimeters;
/// The square micrometers unit of area.
@property (class, readonly, copy) NSUnitArea *squareMicrometers;
/// The square nanometers unit of area.
@property (class, readonly, copy) NSUnitArea *squareNanometers;
/// The square inches unit of area.
@property (class, readonly, copy) NSUnitArea *squareInches;
/// The square feet unit of area.
@property (class, readonly, copy) NSUnitArea *squareFeet;
/// The square yards unit of area.
@property (class, readonly, copy) NSUnitArea *squareYards;
/// The square miles unit of area.
@property (class, readonly, copy) NSUnitArea *squareMiles;
/// The acres unit of area.
@property (class, readonly, copy) NSUnitArea *acres;
/// The ares unit of area.
@property (class, readonly, copy) NSUnitArea *ares;
/// The hectares unit of area.
@property (class, readonly, copy) NSUnitArea *hectares;

@end

/// A unit of measure for concentration of mass.
///
/// You typically use instances of ``NSUnitConcentrationMass`` to represent specific quantities of concentration using the ``NSMeasurement`` class.
///
/// ### Concentration of Mass
///
/// Concentration is the abundance of a constituent within a volume. Concentration can be expressed by SI derived units in terms of kilograms per cubic meter (kg/m3).
///
/// The ``NSUnitConcentrationMass`` class defines its ``Dimension/baseUnit()`` as ``gramsPerLiter``, and provides the following units, which are initialized using ``UnitConverterLinear`` converters with the specified coefficients:
///
///
/// | Name | Method | Symbol | Coefficient |
/// |---|---|---|---|
/// | Grams Per Liter | ``gramsPerLiter`` | g/L | `1` |
/// | Milligrams Per Deciliter | ``milligramsPerDeciliter`` | mg/dL | `0.01` |
/// | Millimoles Per Liter | ``millimolesPerLiter(withGramsPerMole:)`` | mmol/L | `18 * gramsPerMole` |
NS_SWIFT_SENDABLE
API_AVAILABLE(macosx(10.12), ios(10.0), watchos(3.0), tvos(10.0))
@interface NSUnitConcentrationMass : NSDimension <NSSecureCoding>
/*
 Base unit - gramsPerLiter
 */

/// The grams per liter unit of concentration.
@property (class, readonly, copy) NSUnitConcentrationMass *gramsPerLiter;
/// The milligrams per deciliter unit of concentration.
@property (class, readonly, copy) NSUnitConcentrationMass *milligramsPerDeciliter;

/// Returns the millimoles per liter unit with the specified grams per mole.
+ (NSUnitConcentrationMass *)millimolesPerLiterWithGramsPerMole:(double)gramsPerMole;

@end

/// A unit of measure for specific quantities of dispersion.
///
/// You typically use instances of ``NSUnitDispersion`` to represent specific quantities of dispersion using the ``NSMeasurement`` class.
///
/// ### Dispersion
///
/// Dispersion describes the amount of a constituent divided by the amount of all other constituents in a mixture. Dispersion is a dimensionless quantity that is commonly expressed in "parts-per" notation, such as "parts per million" (ppm), to describe small relative quantities.
///
/// The ``NSUnitDispersion`` class defines its ``Dimension/baseUnit()`` as ``partsPerMillion``.
///
///
/// | Name | Method | Abbreviation |
/// |---|---|---|
/// | Parts Per Million | ``partsPerMillion`` | ppm |
NS_SWIFT_SENDABLE
API_AVAILABLE(macosx(10.12), ios(10.0), watchos(3.0), tvos(10.0))
@interface NSUnitDispersion : NSDimension <NSSecureCoding>
/*
 Base unit - partsPerMillion
 */
/// The parts per million unit of dispersion.
@property (class, readonly, copy) NSUnitDispersion *partsPerMillion;

@end

/// A unit of measure for a duration of time.
///
/// You typically use instances of ``NSUnitDuration`` to represent specific quantities of planar angle using the ``NSMeasurement`` class.
///
/// ### Duration
///
/// Duration is a quantity of time. The SI unit for time is the second (sec), which is defined in terms of the radioactivity of a cesium-133 atom. Duration is also commonly expressed in terms of minutes (min) and hours (hr).
///
/// > Note:
/// > Use the ``NSDateComponents`` class to represent quantities of calendrical units, such as days, weeks, months, and years.
///
/// The ``NSUnitDuration`` class defines its ``Dimension/baseUnit()`` as ``seconds``, and provides the following units, which ``UnitConverterLinear`` converters initialize with the given coefficients:
///
///
/// | Name | Method | Symbol | Coefficient |
/// |---|---|---|---|
/// | Seconds | ``seconds`` | sec | `1` |
/// | Minutes | ``minutes`` | min | `60` |
/// | Hours | ``hours`` | hr | `3600` |
NS_SWIFT_SENDABLE
API_AVAILABLE(macosx(10.12), ios(10.0), watchos(3.0), tvos(10.0))
@interface NSUnitDuration : NSDimension <NSSecureCoding>  // Note: This class is not meant to be used for date calculation.  Use NSDate/NSCalendar/NSDateComponents for calendrical date and time operations.
/*
 Base unit - seconds
 */

/// The hours unit of duration.
@property (class, readonly, copy) NSUnitDuration *hours;
/// The minutes unit of duration.
@property (class, readonly, copy) NSUnitDuration *minutes;
/// The seconds unit of duration.
@property (class, readonly, copy) NSUnitDuration *seconds;
/// The milliseconds unit of duration.
@property (class, readonly, copy) NSUnitDuration *milliseconds API_AVAILABLE(macos(10.15), ios(13.0), tvos(13.0), watchos(6.0));
/// The microseconds unit of duration.
@property (class, readonly, copy) NSUnitDuration *microseconds API_AVAILABLE(macos(10.15), ios(13.0), tvos(13.0), watchos(6.0));
/// The nanoseconds unit of duration.
@property (class, readonly, copy) NSUnitDuration *nanoseconds API_AVAILABLE(macos(10.15), ios(13.0), tvos(13.0), watchos(6.0));
/// The picoseconds unit of duration.
@property (class, readonly, copy) NSUnitDuration *picoseconds API_AVAILABLE(macos(10.15), ios(13.0), tvos(13.0), watchos(6.0));

@end

/// A unit of measure for electric charge.
///
/// You typically use instances of ``NSUnitElectricCharge`` to represent specific quantities of electric charge using the ``NSMeasurement`` class.
///
/// ### Electric Charge
///
/// Electric charge is a fundamental physical property of matter that causes it to experience a force within an electromagnetic field. The SI unit for electric charge is the coulomb (C), which is defined as the amount of charge carried by a current of one ampere in one second (1C = 1A · 1s). Charge is also commonly expressed in terms of ampere hours (Ah).
///
/// The ``NSUnitElectricCharge`` class defines its ``Dimension/baseUnit()`` as ``coulombs``, and provides the following units, which are initialized using ``UnitConverterLinear`` converters with the specified coefficients:
///
///
/// | Name | Method | Symbol | Coefficient |
/// |---|---|---|---|
/// | Coulombs | ``coulombs`` | C | `1.0` |
/// | Megaampere Hours | ``megaampereHours`` | MAh | `3.6e9` |
/// | Kiloampere Hours | ``kiloampereHours`` | kAh | `3600000.0` |
/// | Ampere Hours | ``ampereHours`` | Ah | `3600.0` |
/// | Milliampere Hours | ``milliampereHours`` | mAh | `3.6` |
/// | Microampere Hours | ``microampereHours`` | µAh | `0.0036` |
NS_SWIFT_SENDABLE
API_AVAILABLE(macosx(10.12), ios(10.0), watchos(3.0), tvos(10.0))
@interface NSUnitElectricCharge : NSDimension <NSSecureCoding>
/*
 Base unit - coulombs
 */

/// The coulombs unit of electric charge.
@property (class, readonly, copy) NSUnitElectricCharge *coulombs;
/// The megaampere hours unit of electric charge.
@property (class, readonly, copy) NSUnitElectricCharge *megaampereHours;
/// The kiloampere hours unit of electric charge.
@property (class, readonly, copy) NSUnitElectricCharge *kiloampereHours;
/// The ampere hours unit of electric charge.
@property (class, readonly, copy) NSUnitElectricCharge *ampereHours;
/// The milliampere hours unit of electric charge.
@property (class, readonly, copy) NSUnitElectricCharge *milliampereHours;
/// The microampere hours unit of electric charge.
@property (class, readonly, copy) NSUnitElectricCharge *microampereHours;

@end

/// A unit of measure for electric current.
///
/// You typically use instances of ``NSUnitElectricCurrent`` to represent specific quantities of electric current using the ``NSMeasurement`` class.
///
/// ### Electric Current
///
/// Electric current is the flow of electric charge. The SI unit for electric current is the ampere (A), which is defined in terms the production of electromagnetic force between two parallel linear conductors. It can also be expressed as the flow of one coulomb per second (1A = 1C / s).
///
/// The ``NSUnitElectricCurrent`` class defines its ``Dimension/baseUnit()`` as ``amperes``, and provides the following units, which are initialized using ``UnitConverterLinear`` converters with the specified coefficients:
///
///
/// | Name | Method | Symbol | Coefficient |
/// |---|---|---|---|
/// | Megaamperes | ``megaamperes`` | MA | `1000000.0` |
/// | Kiloamperes | ``kiloamperes`` | kA | `1000.0` |
/// | Amperes | ``amperes`` | A | `1.0` |
/// | Milliamperes | ``milliamperes`` | mA | `0.001` |
/// | Microamperes | ``microamperes`` | µA | `0.000001` |
NS_SWIFT_SENDABLE
API_AVAILABLE(macosx(10.12), ios(10.0), watchos(3.0), tvos(10.0))
@interface NSUnitElectricCurrent : NSDimension <NSSecureCoding>
/*
 Base unit - amperes
 */

/// The megaamperes unit of electric current.
@property (class, readonly, copy) NSUnitElectricCurrent *megaamperes;
/// The kiloamperes unit of electric current.
@property (class, readonly, copy) NSUnitElectricCurrent *kiloamperes;
/// The amperes unit of electric current.
@property (class, readonly, copy) NSUnitElectricCurrent *amperes;
/// The milliamperes unit of electric current.
@property (class, readonly, copy) NSUnitElectricCurrent *milliamperes;
/// The microamperes unit of electric current.
@property (class, readonly, copy) NSUnitElectricCurrent *microamperes;

@end

/// A unit of measure for electric potential difference.
///
/// You typically use instances of ``NSUnitElectricPotentialDifference`` to represent specific quantities of electric potential difference using the ``NSMeasurement`` class.
///
/// ### Electric Potential Difference
///
/// Electric potential difference is the amount of electric potential energy of a point charge at a point in space. The SI unit for electric potential difference is the volt (V), which is derived as the difference in electric potential energy between two points of a linear conductor when an electric current of one ampere dissipates one watt of power between those points (1V = 1W/1A).
///
/// The ``NSUnitElectricPotentialDifference`` class defines its ``Dimension/baseUnit()`` as ``volts``, and provides the following units, which are initialized using ``UnitConverterLinear`` converters with the specified coefficients:
///
///
/// | Name | Method | Symbol | Coefficient |
/// |---|---|---|---|
/// | Megavolts | ``megavolts`` | MV | `1000000.0` |
/// | Kilovolts | ``kilovolts`` | kV | `1000.0` |
/// | Volts | ``volts`` | V | `1.0` |
/// | Millivolts | ``millivolts`` | mV | `0.001` |
/// | Microvolts | ``microvolts`` | µV | `0.000001` |
NS_SWIFT_SENDABLE
API_AVAILABLE(macosx(10.12), ios(10.0), watchos(3.0), tvos(10.0))
@interface NSUnitElectricPotentialDifference : NSDimension <NSSecureCoding>
/*
 Base unit - volts
 */

/// The megavolts unit of electric potential difference.
@property (class, readonly, copy) NSUnitElectricPotentialDifference *megavolts;
/// The kilovolts unit of electric potential difference.
@property (class, readonly, copy) NSUnitElectricPotentialDifference *kilovolts;
/// The volts unit of electric potential difference.
@property (class, readonly, copy) NSUnitElectricPotentialDifference *volts;
/// The millivolts unit of electric potential difference.
@property (class, readonly, copy) NSUnitElectricPotentialDifference *millivolts;
/// The microvolts unit of electric potential difference.
@property (class, readonly, copy) NSUnitElectricPotentialDifference *microvolts;

@end

/// A unit of measure for electric resistance.
///
/// You typically use instances of ``NSUnitElectricResistance`` to represent specific quantities of electric resistance using the ``NSMeasurement`` class.
///
/// ### Electric Resistance
///
/// Electric resistance is the difficulty of passing an electric current through a conductor. The SI unit for electric resistance is the ohm (Ω), which is derived as the electric resistance that produces one ampere of current between two points in conductor with one volt of electric potential difference (1Ω = 1V/1A).
///
/// The ``NSUnitElectricResistance`` class defines its ``Dimension/baseUnit()`` as ``ohms``, and provides the following units, which are initialized using ``UnitConverterLinear`` converters with the specified coefficients:
///
///
/// | Name | Method | Symbol | Coefficient |
/// |---|---|---|---|
/// | Megaohms | ``megaohms`` | MΩ | `1000000.0` |
/// | Kiloohms | ``kiloohms`` | kΩ | `1000.0` |
/// | Ohms | ``ohms`` | Ω | `1.0` |
/// | Milliohms | ``milliohms`` | mΩ | `0.001` |
/// | Microohms | ``microohms`` | µΩ | `0.000001` |
NS_SWIFT_SENDABLE
API_AVAILABLE(macosx(10.12), ios(10.0), watchos(3.0), tvos(10.0))
@interface NSUnitElectricResistance : NSDimension <NSSecureCoding>
/*
 Base unit - ohms
 */

/// The megaohms unit of electric resistance.
@property (class, readonly, copy) NSUnitElectricResistance *megaohms;
/// The kiloohms unit of electric resistance.
@property (class, readonly, copy) NSUnitElectricResistance *kiloohms;
/// The ohms unit of electric resistance.
@property (class, readonly, copy) NSUnitElectricResistance *ohms;
/// The milliohms unit of electric resistance.
@property (class, readonly, copy) NSUnitElectricResistance *milliohms;
/// The microohms unit of electric resistance.
@property (class, readonly, copy) NSUnitElectricResistance *microohms;

@end

/// A unit of measure for energy.
///
/// You typically use instances of ``NSUnitEnergy`` to represent specific quantities of energy using the ``NSMeasurement`` class.
///
/// ### Energy
///
/// Energy is a fundamental property of matter than can be transferred and converted into different forms, such as kinetic, electric, and thermal. The SI unit for energy is the joule (J), which is derived as the work of one meter of displacement in the direction of a force of one newton (1J = 1N ∙ 1m). It can also be derived as the work required to displace an electric charge of one coulomb through an electrical potential difference of one volt (1J = 1C ∙ 1V), or the work required to produce one watt of power for one second (1J = 1W ∙ 1s). Energy is also commonly expressed in terms of the calorie (cal), or the energy needed to raise the temperature of one gram of water by one degree Celsius at a pressure of one atmosphere (1cal ≡ 4.184J).
///
/// The ``NSUnitEnergy`` class defines its ``Dimension/baseUnit()`` as ``joules``, and provides the following units, which are initialized using ``UnitConverterLinear`` converters with the specified coefficients:
///
///
/// | Name | Method | Symbol | Coefficient |
/// |---|---|---|---|
/// | Kilojoules | ``kilojoules`` | kJ | `1000.0` |
/// | Joules | ``joules`` | J | `1.0` |
/// | Kilocalories | ``kilocalories`` | kCal | `4184.0` |
/// | Calories | ``calories`` | cal | `4.184` |
/// | Kilowatt Hours | ``kilowattHours`` | kWh | `3600000.0` |
NS_SWIFT_SENDABLE
API_AVAILABLE(macosx(10.12), ios(10.0), watchos(3.0), tvos(10.0))
@interface NSUnitEnergy : NSDimension <NSSecureCoding>
/*
 Base unit - joules
 */

/// The kilojoules unit of energy.
@property (class, readonly, copy) NSUnitEnergy *kilojoules;
/// The joules unit of energy.
@property (class, readonly, copy) NSUnitEnergy *joules;
/// The kilocalories unit of energy.
@property (class, readonly, copy) NSUnitEnergy *kilocalories;
/// The calories unit of energy.
@property (class, readonly, copy) NSUnitEnergy *calories;
/// The kilowatt hours unit of energy.
@property (class, readonly, copy) NSUnitEnergy *kilowattHours;

@end

/// A unit of measure for frequency.
///
/// You typically use instances of ``NSUnitFrequency`` to represent specific quantities of frequency using the ``NSMeasurement`` class.
///
/// ### Frequency
///
/// Frequency is a quantity of occurrences for a repeating event over time. The SI unit for frequency is the hertz (Hz), which is a derived as one occurrence per second (`1 Hz = 1 / 1s`).
///
/// The ``UnitFrequency`` class defines its ``Dimension/baseUnit()`` as ``hertz``, and provides the following units, which are initialized using ``UnitConverterLinear`` converters with the specified coefficients:
///
///
/// | Name | Method | Symbol | Coefficient |
/// |---|---|---|---|
/// | Terahertz | ``terahertz`` | THz | `1e12` |
/// | Gigahertz | ``gigahertz`` | GHz | `1e9` |
/// | Megahertz | ``megahertz`` | MHz | `1000000.0` |
/// | Kilohertz | ``kilohertz`` | kHz | `1000.0` |
/// | Hertz | ``hertz`` | Hz | `1` |
/// | Millihertz | ``millihertz`` | mHz | `0.001` |
/// | Microhertz | ``microhertz`` | µHz | `0.000001` |
/// | Nanohertz | ``nanohertz`` | nHz | `1e-9` |
NS_SWIFT_SENDABLE
API_AVAILABLE(macosx(10.12), ios(10.0), watchos(3.0), tvos(10.0))
@interface NSUnitFrequency : NSDimension <NSSecureCoding>
/*
 Base unit - hertz
 */

/// The terahertz unit of frequency.
@property (class, readonly, copy) NSUnitFrequency *terahertz;
/// The gigahertz unit of frequency.
@property (class, readonly, copy) NSUnitFrequency *gigahertz;
/// The megahertz unit of frequency.
@property (class, readonly, copy) NSUnitFrequency *megahertz;
/// The kilohertz unit of frequency.
@property (class, readonly, copy) NSUnitFrequency *kilohertz;
/// The hertz unit of frequency.
@property (class, readonly, copy) NSUnitFrequency *hertz;
/// The millihertz unit of frequency.
@property (class, readonly, copy) NSUnitFrequency *millihertz;
/// The microhertz unit of frequency.
@property (class, readonly, copy) NSUnitFrequency *microhertz;
/// The nanohertz unit of frequency.
@property (class, readonly, copy) NSUnitFrequency *nanohertz;

/// The frames per second unit of frequency.
// 1 FPS ≡ 1 Hertz
@property (class, readonly, copy) NSUnitFrequency *framesPerSecond API_AVAILABLE(macos(10.15), ios(13.0), tvos(13.0), watchos(6.0));

@end

/// A unit of measure for fuel efficiency.
///
/// You typically use instances of ``NSUnitFuelEfficiency`` to represent specific quantities of fuel efficiency using the ``NSMeasurement`` class.
///
/// ### Fuel Efficiency
///
/// Fuel efficiency corresponds to the thermal efficiency of a process that converts the chemical potential energy of a fuel into kinetic energy. Fuel efficiency can be expressed by SI derived units in terms of cubic meters per meter (m3/m), but is more commonly expressed in terms of liters per kilometer (L/km) and miles per gallon (mpg).
///
/// The ``NSUnitFuelEfficiency`` class defines its ``Dimension/baseUnit()`` as ``litersPer100Kilometers``, and provides the following units:
///
///
/// | Name | Method | Symbol |
/// |---|---|---|
/// | Liters Per 100 Kilometers | ``litersPer100Kilometers`` | L/100km |
/// | Miles Per Gallon | ``milesPerGallon`` | mpg |
/// | Miles Per Imperial Gallon | ``milesPerImperialGallon`` | mpg |
NS_SWIFT_SENDABLE
API_AVAILABLE(macosx(10.12), ios(10.0), watchos(3.0), tvos(10.0))
@interface NSUnitFuelEfficiency : NSDimension <NSSecureCoding>
/*
 Base unit - litersPer100Kilometers
 */

/// The liters per 100 kilometers unit of fuel efficiency.
@property (class, readonly, copy) NSUnitFuelEfficiency *litersPer100Kilometers;
/// The miles per imperial gallon unit of fuel efficiency.
@property (class, readonly, copy) NSUnitFuelEfficiency *milesPerImperialGallon;
/// The miles per gallon unit of fuel efficiency.
@property (class, readonly, copy) NSUnitFuelEfficiency *milesPerGallon;

@end

/// A unit of measure for quantities of information.
///
/// Use instances of ``UnitInformationStorage`` to represent quantities of information using the ``NSMeasurement`` class. The base unit of measure for information is the bit, with a nibble representing four bits and a byte representing eight bits.
///
/// Larger units of information expand on bits and bytes by orders of magnitude in both decimal and binary forms.
///
/// ### Information Transfer
///
/// Units of bits commonly represent the amount of transferred information.
///
///
/// | Decimal Bits | Coefficient | Binary Bits | Coefficient |
/// |---|---|---|---|
/// | ``kilobits`` | `1000` | ``kibibits`` | `1024` |
/// | ``megabits`` | `1000e2` | ``mebibits`` | `1024e2` |
/// | ``gigabits`` | `1000e3` | ``gibibits`` | `1024e3` |
/// | ``terabits`` | `1000e4` | ``tebibits`` | `1024e4` |
/// | ``petabits`` | `1000e5` | ``pebibits`` | `1024e5` |
/// | ``exabits`` | `1000e6` | ``exbibits`` | `1024e6` |
/// | ``zettabits`` | `1000e7` | ``zebibits`` | `1024e7` |
/// | ``yottabits`` | `1000e8` | ``yobibits`` | `1024e8` |
///
///
///
///
/// ### Information Storage
///
/// Units of bytes commonly represent the amount of stored information.
///
///
/// | Decimal Bytes | Coefficient | Binary Bytes | Coefficient |
/// |---|---|---|---|
/// | ``kilobytes`` | `1000` | ``kibibytes`` | `1024` |
/// | ``megabytes`` | `1000e2` | ``mebibytes`` | `1024e2` |
/// | ``gigabytes`` | `1000e3` | ``gibibytes`` | `1024e3` |
/// | ``terabytes`` | `1000e4` | ``tebibytes`` | `1024e4` |
/// | ``petabytes`` | `1000e5` | ``pebibytes`` | `1024e5` |
/// | ``exabytes`` | `1000e6` | ``exbibytes`` | `1024e6` |
/// | ``zettabytes`` | `1000e7` | ``zebibytes`` | `1024e7` |
/// | ``yottabytes`` | `1000e8` | ``yobibytes`` | `1024e8` |
NS_SWIFT_SENDABLE
API_AVAILABLE(macos(10.15), ios(13.0), tvos(13.0), watchos(6.0))
NS_SWIFT_NAME(UnitInformationStorage)
@interface NSUnitInformationStorage : NSDimension <NSSecureCoding>

/// The bytes unit of information storage.
// Bytes are defined by IEC 80000-13: one byte is 8 bits.
@property (readonly, class, copy) NSUnitInformationStorage *bytes;

/// The bits unit of information storage.
// One byte is 8 bits; one nibble is 4 bits.
@property (readonly, class, copy) NSUnitInformationStorage *bits;
/// The nibbles unit of information storage.
@property (readonly, class, copy) NSUnitInformationStorage *nibbles;

// SI-prefixed units (i.e. base 10):
// 1 kilobyte = 1000¹ bytes; 1 megabyte = 1000² bytes; etc.
/// The yottabytes unit of information storage.
@property (readonly, class, copy) NSUnitInformationStorage *yottabytes;
/// The zettabytes unit of information storage.
@property (readonly, class, copy) NSUnitInformationStorage *zettabytes;
/// The exabytes unit of information storage.
@property (readonly, class, copy) NSUnitInformationStorage *exabytes;
/// The petabytes unit of information storage.
@property (readonly, class, copy) NSUnitInformationStorage *petabytes;
/// The terabytes unit of information storage.
@property (readonly, class, copy) NSUnitInformationStorage *terabytes;
/// The gigabytes unit of information storage.
@property (readonly, class, copy) NSUnitInformationStorage *gigabytes;
/// The megabytes unit of information storage.
@property (readonly, class, copy) NSUnitInformationStorage *megabytes;
/// The kilobytes unit of information storage.
@property (readonly, class, copy) NSUnitInformationStorage *kilobytes;

/// The yottabits unit of information storage.
@property (readonly, class, copy) NSUnitInformationStorage *yottabits;
/// The zettabits unit of information storage.
@property (readonly, class, copy) NSUnitInformationStorage *zettabits;
/// The exabits unit of information storage.
@property (readonly, class, copy) NSUnitInformationStorage *exabits;
/// The petabits unit of information storage.
@property (readonly, class, copy) NSUnitInformationStorage *petabits;
/// The terabits unit of information storage.
@property (readonly, class, copy) NSUnitInformationStorage *terabits;
/// The gigabits unit of information storage.
@property (readonly, class, copy) NSUnitInformationStorage *gigabits;
/// The megabits unit of information storage.
@property (readonly, class, copy) NSUnitInformationStorage *megabits;
/// The kilobits unit of information storage.
@property (readonly, class, copy) NSUnitInformationStorage *kilobits;

// IEC-prefixed units (i.e. base 2):
// 1 kibibyte = 1024¹ bytes; 1 mebibyte = 1024² bytes; etc.
/// The yobibytes unit of information storage.
@property (readonly, class, copy) NSUnitInformationStorage *yobibytes;
/// The zebibytes unit of information storage.
@property (readonly, class, copy) NSUnitInformationStorage *zebibytes;
/// The exbibytes unit of information storage.
@property (readonly, class, copy) NSUnitInformationStorage *exbibytes;
/// The pebibytes unit of information storage.
@property (readonly, class, copy) NSUnitInformationStorage *pebibytes;
/// The tebibytes unit of information storage.
@property (readonly, class, copy) NSUnitInformationStorage *tebibytes;
/// The gibibytes unit of information storage.
@property (readonly, class, copy) NSUnitInformationStorage *gibibytes;
/// The mebibytes unit of information storage.
@property (readonly, class, copy) NSUnitInformationStorage *mebibytes;
/// The kibibytes unit of information storage.
@property (readonly, class, copy) NSUnitInformationStorage *kibibytes;

/// The yobibits unit of information storage.
@property (readonly, class, copy) NSUnitInformationStorage *yobibits;
/// The zebibits unit of information storage.
@property (readonly, class, copy) NSUnitInformationStorage *zebibits;
/// The exbibits unit of information storage.
@property (readonly, class, copy) NSUnitInformationStorage *exbibits;
/// The pebibits unit of information storage.
@property (readonly, class, copy) NSUnitInformationStorage *pebibits;
/// The tebibits unit of information storage.
@property (readonly, class, copy) NSUnitInformationStorage *tebibits;
/// The gibibits unit of information storage.
@property (readonly, class, copy) NSUnitInformationStorage *gibibits;
/// The mebibits unit of information storage.
@property (readonly, class, copy) NSUnitInformationStorage *mebibits;
/// The kibibits unit of information storage.
@property (readonly, class, copy) NSUnitInformationStorage *kibibits;

@end

/// A unit of measure for length.
///
/// You typically use instances of ``UnitLength`` to represent specific quantities of length using the ``NSMeasurement`` class.
///
/// ### Length
///
/// Length is the dimensional extent of matter. The SI unit for length is the meter (m), which is defined in terms of the distance traveled by light in a vacuum.
///
/// The ``UnitLength`` class defines its ``Dimension/baseUnit()`` as ``meters``, and provides the following units, which are initialized using ``UnitConverterLinear`` converters with the specified coefficients:
///
///
/// | Name | Method | Symbol | Coefficient |
/// |---|---|---|---|
/// | Megameters | ``megameters`` | Mm | `1000000.0` |
/// | Kilometers | ``kilometers`` | kM | `1000.0` |
/// | Hectometers | ``hectometers`` | hm | `100.0` |
/// | Decameters | ``decameters`` | dam | `10.0` |
/// | Meters | ``meters`` | m | `1.0` |
/// | Decimeters | ``decimeters`` | dm | `0.1` |
/// | Centimeters | ``centimeters`` | cm | `0.01` |
/// | Millimeters | ``millimeters`` | mm | `0.001` |
/// | Micrometers | ``micrometers`` | µm | `0.000001` |
/// | Nanometers | ``nanometers`` | nm | `1e-9` |
/// | Picometers | ``picometers`` | pm | `1e-12` |
/// | Inches | ``inches`` | in | `0.0254` |
/// | Feet | ``feet`` | ft | `0.3048` |
/// | Yards | ``yards`` | yd | `0.9144` |
/// | Miles | ``miles`` | mi | `1609.34` |
/// | Scandinavian Miles | ``scandinavianMiles`` | smi | `10000` |
/// | Light Years | ``lightyears`` | ly | `9.461e+15` |
/// | Nautical Miles | ``nauticalMiles`` | NM | `1852` |
/// | Fathoms | ``fathoms`` | ftm | `1.8288` |
/// | Furlongs | ``furlongs`` | fur | `201.168` |
/// | Astronomical Units | ``astronomicalUnits`` | au | `1.496e+11` |
/// | Parsecs | ``parsecs`` | pc | `3.086e+16` |
NS_SWIFT_SENDABLE
API_AVAILABLE(macosx(10.12), ios(10.0), watchos(3.0), tvos(10.0))
@interface NSUnitLength : NSDimension <NSSecureCoding>
/*
 Base unit - meters
 */

/// The megameters unit of length.
@property (class, readonly, copy) NSUnitLength *megameters;
/// The kilometers unit of length.
@property (class, readonly, copy) NSUnitLength *kilometers;
/// The hectometers unit of length.
@property (class, readonly, copy) NSUnitLength *hectometers;
/// The decameters unit of length.
@property (class, readonly, copy) NSUnitLength *decameters;
/// The meters unit of length.
@property (class, readonly, copy) NSUnitLength *meters;
/// The decimeters unit of length.
@property (class, readonly, copy) NSUnitLength *decimeters;
/// The centimeters unit of length.
@property (class, readonly, copy) NSUnitLength *centimeters;
/// The millimeters unit of length.
@property (class, readonly, copy) NSUnitLength *millimeters;
/// The micrometers unit of length.
@property (class, readonly, copy) NSUnitLength *micrometers;
/// The nanometers unit of length.
@property (class, readonly, copy) NSUnitLength *nanometers;
/// The picometers unit of length.
@property (class, readonly, copy) NSUnitLength *picometers;
/// The inches unit of length.
@property (class, readonly, copy) NSUnitLength *inches;
/// The feet unit of length.
@property (class, readonly, copy) NSUnitLength *feet;
/// The yards unit of length.
@property (class, readonly, copy) NSUnitLength *yards;
/// The miles unit of length.
@property (class, readonly, copy) NSUnitLength *miles;
/// The Scandinavian miles unit of length.
@property (class, readonly, copy) NSUnitLength *scandinavianMiles;
/// The lightyears unit of length.
@property (class, readonly, copy) NSUnitLength *lightyears;
/// The nautical miles unit of length.
@property (class, readonly, copy) NSUnitLength *nauticalMiles;
/// The fathoms unit of length.
@property (class, readonly, copy) NSUnitLength *fathoms;
/// The furlongs unit of length.
@property (class, readonly, copy) NSUnitLength *furlongs;
/// The astronomical units unit of length.
@property (class, readonly, copy) NSUnitLength *astronomicalUnits;
/// The parsecs unit of length.
@property (class, readonly, copy) NSUnitLength *parsecs;

@end

/// A unit of measure for illuminance.
///
/// You typically use instances of ``NSUnitIlluminance`` to represent specific quantities of illuminance using the ``NSMeasurement`` class.
///
/// ### Illuminance
///
/// Illuminance is the luminous flux incident on a surface. The SI unit for illuminance is the lux (lx), which is derived as one lumen per square meter (1lm / 1m2).
///
/// The ``NSUnitIlluminance`` class defines its ``Dimension/baseUnit()`` as ``lux``.
///
///
/// | Name | Method | Symbol |
/// |---|---|---|
/// | Lux | ``lux`` | lx |
NS_SWIFT_SENDABLE
API_AVAILABLE(macosx(10.12), ios(10.0), watchos(3.0), tvos(10.0))
@interface NSUnitIlluminance : NSDimension <NSSecureCoding>
/*
 Base unit - lux
 */

/// The lux unit of illuminance.
@property (class, readonly, copy) NSUnitIlluminance *lux;

@end

/// A unit of measure for mass.
///
/// You typically use instances of ``NSUnitMass`` to represent specific quantities of mass using the ``NSMeasurement`` class.
///
/// ### Mass
///
/// Mass is a fundamental property of matter that causes it to resist a force accelerating it. The SI unit for mass is the kilogram (kg), which defined in terms of the mass of the international prototype kilogram.
///
/// The ``NSUnitMass`` class defines its ``Dimension/baseUnit()`` as ``kilograms``, and provides the following units, which ``UnitConverterLinear`` converters initialize with the given coefficients:
///
///
/// | Name | Method | Symbol | Coefficient |
/// |---|---|---|---|
/// | Kilograms | ``kilograms`` | kg | `1.0` |
/// | Grams | ``grams`` | g | `0.001` |
/// | Decigrams | ``decigrams`` | dg | `0.0001` |
/// | Centigrams | ``centigrams`` | cg | `0.00001` |
/// | Milligrams | ``milligrams`` | mg | `0.000001` |
/// | Micrograms | ``micrograms`` | µg | `1e-9` |
/// | Nanograms | ``nanograms`` | ng | `1e-12` |
/// | Picograms | ``picograms`` | pg | `1e-15` |
/// | Ounces | ``ounces`` | oz | `0.0283495` |
/// | Pounds | ``pounds`` | lb | `0.453592` |
/// | Stones | ``stones`` | st | `0.157473` |
/// | Metric Tons | ``metricTons`` | t | `1000` |
/// | Short Tons | ``shortTons`` | ton | `907.185` |
/// | Carats | ``carats`` | ct | `0.0002` |
/// | Ounces Troy | ``ouncesTroy`` | oz t | `0.03110348` |
/// | Slugs | ``slugs`` | slug | `14.5939` |
NS_SWIFT_SENDABLE
API_AVAILABLE(macosx(10.12), ios(10.0), watchos(3.0), tvos(10.0))
@interface NSUnitMass : NSDimension <NSSecureCoding>
/*
 Base unit - kilograms
 */

/// The kilograms unit of mass.
@property (class, readonly, copy) NSUnitMass *kilograms;
/// The grams unit of mass.
@property (class, readonly, copy) NSUnitMass *grams;
/// The decigrams unit of mass.
@property (class, readonly, copy) NSUnitMass *decigrams;
/// The centigrams unit of mass.
@property (class, readonly, copy) NSUnitMass *centigrams;
/// The milligrams unit of mass.
@property (class, readonly, copy) NSUnitMass *milligrams;
/// The micrograms unit of mass.
@property (class, readonly, copy) NSUnitMass *micrograms;
/// The nanograms unit of mass.
@property (class, readonly, copy) NSUnitMass *nanograms;
/// The picograms unit of mass.
@property (class, readonly, copy) NSUnitMass *picograms;
/// The ounces unit of mass.
@property (class, readonly, copy) NSUnitMass *ounces;
/// The pounds unit of mass.
@property (class, readonly, copy) NSUnitMass *poundsMass;
/// The stones unit of mass.
@property (class, readonly, copy) NSUnitMass *stones;
/// The metric tons unit of mass.
@property (class, readonly, copy) NSUnitMass *metricTons;
/// The short tons unit of mass.
@property (class, readonly, copy) NSUnitMass *shortTons;
/// The carats unit of mass.
@property (class, readonly, copy) NSUnitMass *carats;
/// The troy ounces unit of mass.
@property (class, readonly, copy) NSUnitMass *ouncesTroy;
/// The slugs unit of mass.
@property (class, readonly, copy) NSUnitMass *slugs;

@end

/// A unit of measure for power.
///
/// You typically use instances of ``NSUnitPower`` to represent specific quantities of power using the ``NSMeasurement`` class.
///
/// ### Power
///
/// Power is the amount of energy used over time. The SI unit for power is the watt (W), which is derived as one joule per second (1W = 1J / 1s).
///
/// The ``NSUnitPower`` class defines its ``Dimension/baseUnit()`` as ``watts``, and provides the following units, which are initialized using ``UnitConverterLinear`` converters with the specified coefficients:
///
///
/// | Name | Method | Symbol | Coefficient |
/// |---|---|---|---|
/// | Terawatts | ``terawatts`` | TW | `1e12` |
/// | Gigawatts | ``gigawatts`` | GW | `1e9` |
/// | Megawatts | ``megawatts`` | MW | `1000000.0` |
/// | Kilowatts | ``kilowatts`` | kW | `1000.0` |
/// | Watts | ``watts`` | W | `1` |
/// | Milliwatts | ``milliwatts`` | mW | `0.001` |
/// | Microwatts | ``microwatts`` | µW | `0.000001` |
/// | Nanowatts | ``nanowatts`` | nW | `1e-9` |
/// | Picowatts | ``picowatts`` | pW | `1e-12` |
/// | Femtowatts | ``femtowatts`` | fW | `1e-15` |
/// | Horsepower | ``horsepower`` | hp | `745.7` |
NS_SWIFT_SENDABLE
API_AVAILABLE(macosx(10.12), ios(10.0), watchos(3.0), tvos(10.0))
@interface NSUnitPower : NSDimension <NSSecureCoding>
/*
 Base unit - watts
 */

/// The terawatts unit of power.
@property (class, readonly, copy) NSUnitPower *terawatts;
/// The gigawatts unit of power.
@property (class, readonly, copy) NSUnitPower *gigawatts;
/// The megawatts unit of power.
@property (class, readonly, copy) NSUnitPower *megawatts;
/// The kilowatts unit of power.
@property (class, readonly, copy) NSUnitPower *kilowatts;
/// The watts unit of power.
@property (class, readonly, copy) NSUnitPower *watts;
/// The milliwatts unit of power.
@property (class, readonly, copy) NSUnitPower *milliwatts;
/// The microwatts unit of power.
@property (class, readonly, copy) NSUnitPower *microwatts;
/// The nanowatts unit of power.
@property (class, readonly, copy) NSUnitPower *nanowatts;
/// The picowatts unit of power.
@property (class, readonly, copy) NSUnitPower *picowatts;
/// The femtowatts unit of power.
@property (class, readonly, copy) NSUnitPower *femtowatts;
/// The horsepower unit of power.
@property (class, readonly, copy) NSUnitPower *horsepower;

@end

/// A unit of measure for pressure.
///
/// You typically use instances of ``NSUnitPressure`` to represent specific quantities of pressure using the ``NSMeasurement`` class.
///
/// ### Pressure
///
/// Pressure is the normal force over a surface. The SI unit for pressure is the pascal (Pa), which is derived as one newton of force over one square meter (`1 Pa = 1 N / 1 m`2).
///
/// The ``UnitPressure`` class defines its ``Dimension/baseUnit()`` as ``newtonsPerMetersSquared`` and provides the following units, which ``UnitConverterLinear`` converters initialize with the given coefficients:
///
///
/// | Name | Method | Symbol | Definition |
/// |---|---|---|---|
/// | Newtons Per Meter Squared (Equivalent to Pascals) | ``newtonsPerMetersSquared`` | N/m² | `1.0` |
/// | Gigapascals | ``gigapascals`` | GPa | `1e9` |
/// | Megapascals | ``megapascals`` | MPa | `1000000.0` |
/// | Kilopascals | ``kilopascals`` | kPa | `1000.0` |
/// | Hectopascals | ``hectopascals`` | hPa | `100.0` |
/// | Inches of Mercury | ``inchesOfMercury`` | inHg | `3386.39` |
/// | Bars | ``bars`` | bar | `100000` |
/// | Millibars | ``millibars`` | mbar | `100` |
/// | Millimeters of Mercury | ``millimetersOfMercury`` | mmHg | `133.322` |
/// | Pounds Per Square Inch | ``poundsForcePerSquareInch`` | psi | `6894.76` |
NS_SWIFT_SENDABLE
API_AVAILABLE(macosx(10.12), ios(10.0), watchos(3.0), tvos(10.0))
@interface NSUnitPressure : NSDimension <NSSecureCoding>
/*
 Base unit - newtonsPerMetersSquared (equivalent to 1 pascal)
 */

/// The newtons per meters squared unit of pressure.
@property (class, readonly, copy) NSUnitPressure *newtonsPerMetersSquared;
/// The gigapascals unit of pressure.
@property (class, readonly, copy) NSUnitPressure *gigapascals;
/// The megapascals unit of pressure.
@property (class, readonly, copy) NSUnitPressure *megapascals;
/// The kilopascals unit of pressure.
@property (class, readonly, copy) NSUnitPressure *kilopascals;
/// The hectopascals unit of pressure.
@property (class, readonly, copy) NSUnitPressure *hectopascals;
/// The inches of mercury unit of pressure.
@property (class, readonly, copy) NSUnitPressure *inchesOfMercury;
/// The bars unit of pressure.
@property (class, readonly, copy) NSUnitPressure *bars;
/// The millibars unit of pressure.
@property (class, readonly, copy) NSUnitPressure *millibars;
/// The millimeters of mercury unit of pressure.
@property (class, readonly, copy) NSUnitPressure *millimetersOfMercury;
/// The pounds per square inch unit of pressure.
@property (class, readonly, copy) NSUnitPressure *poundsForcePerSquareInch;

@end

/// A unit of measure for speed.
///
/// You typically use instances of ``NSUnitSpeed`` to represent specific quantities of speed using the ``NSMeasurement`` class.
///
/// ### Speed
///
/// Speed is the magnitude of velocity, or the rate of change of position. Speed can be expressed by SI derived units in terms of meters per second (m/s), and is also commonly expressed in terms of kilometers per hour (km/h) and miles per hour (mph).
///
/// The ``NSUnitSpeed`` class defines its ``Dimension/baseUnit()`` as ``metersPerSecond``, and provides the following units, which are initialized using ``UnitConverterLinear`` converters with the specified coefficients:
///
///
/// | Name | Method | Symbol | Coefficient |
/// |---|---|---|---|
/// | Meters Per Second | ``metersPerSecond`` | m/s | `1.0` |
/// | Kilometers Per Hour | ``kilometersPerHour`` | km/h | `0.277778` |
/// | Miles Per Hour | ``milesPerHour`` | mph | `0.44704` |
/// | Knots | ``knots`` | kn | `0.514444` |
///
/// The base unit is ``metersPerSecond`` and is accessed via ``NSDimension/baseUnit`` on the ``NSDimension`` protocol.
NS_SWIFT_SENDABLE
API_AVAILABLE(macosx(10.12), ios(10.0), watchos(3.0), tvos(10.0))
@interface NSUnitSpeed : NSDimension <NSSecureCoding>
/*
 Base unit - metersPerSecond
 */

/// The meters per second unit of speed.
@property (class, readonly, copy) NSUnitSpeed *metersPerSecond;
/// The kilometers per hour unit of speed.
@property (class, readonly, copy) NSUnitSpeed *kilometersPerHour;
/// The miles per hour unit of speed.
@property (class, readonly, copy) NSUnitSpeed *milesPerHour;
/// The knots unit of speed.
@property (class, readonly, copy) NSUnitSpeed *knots;

@end

/// A unit of measure for temperature.
///
/// You typically use instances of ``NSUnitTemperature`` to represent specific quantities of temperature using the ``NSMeasurement`` class.
///
/// ### Temperature
///
/// Temperature is a comparative measure of thermal energy. The SI unit for temperature is the kelvin (K), which is defined in terms of the triple point of water. Temperature is also commonly measured by degrees of various scales, including Celsius (°C) and Fahrenheit (°F).
///
/// The ``NSUnitTemperature`` class defines its ``Dimension/baseUnit()`` to be ``kelvin``, and provides the following units, which are initialized using ``UnitConverterLinear`` converters with the specified coefficients and constants:
///
///
/// | Name | Method | Symbol | Coefficient | Constant |
/// |---|---|---|---|---|
/// | Kelvin | ``kelvin`` | K | `1` | `0` |
/// | Degree Celsius | ``celsius`` | °C | `1.0` | `273.15` |
/// | Degree Fahrenheit | ``fahrenheit`` | °F | `0.55555555555556` | `255.37222222222427` |
NS_SWIFT_SENDABLE
API_AVAILABLE(macosx(10.12), ios(10.0), watchos(3.0), tvos(10.0))
@interface NSUnitTemperature : NSDimension <NSSecureCoding>
/*
 Base unit - kelvin
 */
/// The kelvin unit of temperature.
@property (class, readonly, copy) NSUnitTemperature *kelvin;
/// The degrees Celsius unit of temperature.
@property (class, readonly, copy) NSUnitTemperature *celsius;
/// The degrees Fahrenheit unit of temperature.
@property (class, readonly, copy) NSUnitTemperature *fahrenheit;


@end

/// A unit of measure for volume.
///
/// You typically use instances of ``NSUnitVolume`` to represent specific quantities of volume using the ``NSMeasurement`` class.
///
/// ### Volume
///
/// Volume is a quantity of the extend of matter in three dimensions. The SI accepted unit of volume is the liter (L), which is derived as one cubic decimeter (1 dm3). Volume is also commonly expressed in terms of cubic meters (m3), gallons (gal), and cups (cup).
///
/// The ``NSUnitVolume`` class defines its ``Dimension/baseUnit()`` as ``liters``, and provides the following units, which are initialized using ``UnitConverterLinear`` converters with the specified coefficients:
///
///
/// | Name | Method | Symbol | Coefficient |
/// |---|---|---|---|
/// | Megaliters | ``megaliters`` | ML | `1000000.0` |
/// | Kiloliters | ``kiloliters`` | kL | `1000.0` |
/// | Liters | ``liters`` | L | `1.0` |
/// | Deciliters | ``deciliters`` | dL | `0.1` |
/// | Centiliters | ``centiliters`` | cL | `0.01` |
/// | Milliliters | ``milliliters`` | mL | `0.001` |
/// | Cubic Kilometers | ``cubicKilometers`` | km³ | `1e12` |
/// | Cubic Meters | ``cubicMeters`` | m³ | `1000.0` |
/// | Cubic Decimeters | ``cubicDecimeters`` | dm³ | `1.0` |
/// | Cubic Centimeters | ``cubicCentimeters`` | cm³ | `0.001` |
/// | Cubic Millimeters | ``cubicMillimeters`` | mm³ | `0.000001` |
/// | Cubic Inches | ``cubicInches`` | in³ | `0.0163871` |
/// | Cubic Feet | ``cubicFeet`` | ft³ | `28.3168` |
/// | Cubic Yards | ``cubicYards`` | yd³ | `764.555` |
/// | Cubic Miles | ``cubicMiles`` | mi³ | `4.168e+12` |
/// | Acre Feet | ``acreFeet`` | af | `1.233e+6` |
/// | Bushels | ``bushels`` | bsh | `35.2391` |
/// | Teaspoons | ``teaspoons`` | tsp | `0.00492892` |
/// | Tablespoons | ``tablespoons`` | tbsp | `0.0147868` |
/// | Fluid Ounces | ``fluidOunces`` | fl oz | `0.0295735` |
/// | Cups | ``cups`` | cup | `0.24` |
/// | Pints | ``pints`` | pt | `0.473176` |
/// | Quarts | ``quarts`` | qt | `0.946353` |
/// | Gallons | ``gallons`` | gal | `3.78541` |
/// | Imperial Teaspoons | ``imperialTeaspoons`` | tsp | `0.00591939` |
/// | Imperial Tablespoons | ``imperialTablespoons`` | tbsp | `0.0177582` |
/// | Imperial Fluid Ounces | ``imperialFluidOunces`` | fl oz | `0.0284131` |
/// | Imperial Pints | ``imperialPints`` | pt | `0.568261` |
/// | Imperial Quarts | ``imperialQuarts`` | qt | `1.13652` |
/// | Imperial Gallons | ``imperialGallons`` | gal | `4.54609` |
/// | Metric Cups | ``metricCups`` | metric cup | `0.25` |
NS_SWIFT_SENDABLE
API_AVAILABLE(macosx(10.12), ios(10.0), watchos(3.0), tvos(10.0))
@interface NSUnitVolume : NSDimension <NSSecureCoding>
/*
 Base unit - liters
 */

/// The megaliters unit of volume.
@property (class, readonly, copy) NSUnitVolume *megaliters;
/// The kiloliters unit of volume.
@property (class, readonly, copy) NSUnitVolume *kiloliters;
/// The liters unit of volume.
@property (class, readonly, copy) NSUnitVolume *liters;
/// The deciliters unit of volume.
@property (class, readonly, copy) NSUnitVolume *deciliters;
/// The centiliters unit of volume.
@property (class, readonly, copy) NSUnitVolume *centiliters;
/// The milliliters unit of volume.
@property (class, readonly, copy) NSUnitVolume *milliliters;
/// The cubic kilometers unit of volume.
@property (class, readonly, copy) NSUnitVolume *cubicKilometers;
/// The cubic meters unit of volume.
@property (class, readonly, copy) NSUnitVolume *cubicMeters;
/// The cubic decimeters unit of volume.
@property (class, readonly, copy) NSUnitVolume *cubicDecimeters;
/// The cubic centimeters unit of volume.
@property (class, readonly, copy) NSUnitVolume *cubicCentimeters;
/// The cubic millimeters unit of volume.
@property (class, readonly, copy) NSUnitVolume *cubicMillimeters;
/// The cubic inches unit of volume.
@property (class, readonly, copy) NSUnitVolume *cubicInches;
/// The cubic feet unit of volume.
@property (class, readonly, copy) NSUnitVolume *cubicFeet;
/// The cubic yards unit of volume.
@property (class, readonly, copy) NSUnitVolume *cubicYards;
/// The cubic miles unit of volume.
@property (class, readonly, copy) NSUnitVolume *cubicMiles;
/// The acre-feet unit of volume.
@property (class, readonly, copy) NSUnitVolume *acreFeet;
/// The bushels unit of volume.
@property (class, readonly, copy) NSUnitVolume *bushels;
/// The teaspoons unit of volume.
@property (class, readonly, copy) NSUnitVolume *teaspoons;
/// The tablespoons unit of volume.
@property (class, readonly, copy) NSUnitVolume *tablespoons;
/// The fluid ounces unit of volume.
@property (class, readonly, copy) NSUnitVolume *fluidOunces;
/// The cups unit of volume.
@property (class, readonly, copy) NSUnitVolume *cups;
/// The pints unit of volume.
@property (class, readonly, copy) NSUnitVolume *pints;
/// The quarts unit of volume.
@property (class, readonly, copy) NSUnitVolume *quarts;
/// The gallons unit of volume.
@property (class, readonly, copy) NSUnitVolume *gallons;
/// The imperial teaspoons unit of volume.
@property (class, readonly, copy) NSUnitVolume *imperialTeaspoons;
/// The imperial tablespoons unit of volume.
@property (class, readonly, copy) NSUnitVolume *imperialTablespoons;
/// The imperial fluid ounces unit of volume.
@property (class, readonly, copy) NSUnitVolume *imperialFluidOunces;
/// The imperial pints unit of volume.
@property (class, readonly, copy) NSUnitVolume *imperialPints;
/// The imperial quarts unit of volume.
@property (class, readonly, copy) NSUnitVolume *imperialQuarts;
/// The imperial gallons unit of volume.
@property (class, readonly, copy) NSUnitVolume *imperialGallons;
/// The metric cups unit of volume.
@property (class, readonly, copy) NSUnitVolume *metricCups;

@end

NS_HEADER_AUDIT_END(nullability, sendability)
