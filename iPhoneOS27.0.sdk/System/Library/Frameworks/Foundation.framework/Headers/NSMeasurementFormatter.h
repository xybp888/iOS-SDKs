/*
 NSMeasurementFormatter.h
 Copyright (c) 2015-2019, Apple Inc.
 All rights reserved.
 */

#import <Foundation/NSObject.h>
#import <Foundation/NSFormatter.h>
#import <Foundation/NSNumberFormatter.h>
#import <Foundation/NSMeasurement.h>
#import <Foundation/NSLocale.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

/// Options for configuring how the measurement formatter formats measurements.
typedef NS_OPTIONS(NSUInteger, NSMeasurementFormatterUnitOptions) {
    /// Ensures the formatter uses the provided unit even if it is not the preferred unit of the set locale.
    NSMeasurementFormatterUnitOptionsProvidedUnit = (1UL << 0),
    /// Makes the formatter show a natural scale (e.g. "12 kilometers" instead of "12000 meters"). Note that setting this option results in scaling within the unit system of the preferred unit of the locale. To scale within the unit system of the provided unit, combine with `NSMeasurementFormatterUnitOptionsProvidedUnit`.
    NSMeasurementFormatterUnitOptionsNaturalScale = (1UL << 1),
    /// Displays the temperature value without a unit (e.g. "90\u00B0" rather than "90\u00B0F" or "90\u00B0C").
    NSMeasurementFormatterUnitOptionsTemperatureWithoutUnit = (1UL << 2),
} API_AVAILABLE(macosx(10.12), ios(10.0), watchos(3.0), tvos(10.0));

/// A formatter that provides localized representations of units and measurements.
///
/// You use the ``string(from:)-wt9y`` method to create a localized representation of an ``NSMeasurement`` object, and you use the ``string(from:)-4hwjz`` method to create a localized representation of an ``Unit`` object. The formatter takes into account the specified ``locale``, ``unitStyle``, and ``unitOptions`` when producing string representations of units and measurements.
///
/// > Tip:
/// > In Swift, you can use ``Measurement/FormatStyle`` rather than ``MeasurementFormatter``. The ``FormatStyle`` API offers a declarative idiom for customizing the formatting of various types. Also, Foundation caches identical ``FormatStyle`` instances, so you don't need to pass them around your app, or risk wasting memory with duplicate formatters.
API_AVAILABLE(macosx(10.12), ios(10.0), watchos(3.0), tvos(10.0))
@interface NSMeasurementFormatter : NSFormatter <NSSecureCoding> {
@private
    void *_formatter;
}

/*
 Ex:
 
 By default, if unitOptions is set to the empty set, the formatter will do the following:
    - kilocalories may be formatted as "C" instead of "kcal" depending on the locale.
    - kilometersPerHour may be formatted as "miles per hour" for US and UK locales but "kilometers per hour" for other locales.
 
 However, if NSMeasurementFormatterUnitOptionsProvidedUnit is set, the formatter will do the following:
    - kilocalories would be formatted as "kcal" in the language of the locale, even if the locale prefers "C".
    - kilometersPerHour would be formatted as "kilometers per hour" for US and UK locales even though the preference is for "miles per hour."
 */
/// The options for how the unit is formatted.
///
/// This property can be set to ensure that the formatter behaves in a way the developer expects,
/// even if it is not standard according to the preferences of the user's locale.
/// If not specified, `unitOptions` defaults to localizing according to the preferences of the locale.
///
/// Note that `NSMeasurementFormatter` will handle converting measurement objects to the preferred units
/// in a particular locale. For instance, if provided a measurement object in kilometers and the set locale
/// is en_US, the formatter will implicitly convert the measurement object to miles and return the formatted
/// string as the equivalent measurement in miles.
@property NSMeasurementFormatterUnitOptions unitOptions;

/// The unit style used when creating string representations of measurements.
///
/// If not specified, `unitStyle` is set to `NSFormattingUnitStyleMedium`.
@property NSFormattingUnitStyle unitStyle;

/// The locale used when formatting measurements.
///
/// If not specified, the locale is set to the user's current locale.
@property (null_resettable, copy) NSLocale *locale;

/// The number formatter used to format the numeric value of a measurement.
///
/// If not specified, the number formatter is set up with `NSNumberFormatterDecimalStyle`.
@property (null_resettable, copy) NSNumberFormatter *numberFormatter;

/// Creates and returns a localized string representation of the provided measurement.
///
/// - Parameters:
///   - measurement: The measurement to be represented.
/// - Returns: A user-readable string that represents the measurement.
- (NSString *)stringFromMeasurement:(NSMeasurement *)measurement;

/// Creates and returns a localized string representation of the provided unit of measure.
///
/// If the unit cannot be localized, the unit's `symbol` value is used.
///
/// - Parameters:
///   - unit: The unit of measure to be represented.
/// - Returns: A user-readable string that represents the unit of measure.
- (NSString *)stringFromUnit:(NSUnit *)unit;

@end

NS_HEADER_AUDIT_END(nullability, sendability)
