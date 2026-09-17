/*	
    NSJSONSerialization.h
    Copyright (c) 2009-2019, Apple Inc. All rights reserved.
*/

#import <Foundation/NSObject.h>

@class NSError, NSOutputStream, NSInputStream, NSData;

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

/// Options used when reading JSON data.
typedef NS_OPTIONS(NSUInteger, NSJSONReadingOptions) {
    /// Specifies that arrays and dictionaries in the returned object are mutable.
    NSJSONReadingMutableContainers = (1UL << 0),
    /// Specifies that leaf strings in the JSON object graph are mutable.
    NSJSONReadingMutableLeaves = (1UL << 1),
    /// Specifies that the parser should allow top-level objects that are not an `NSArray` or `NSDictionary`.
    NSJSONReadingFragmentsAllowed = (1UL << 2),

#if !0
    /// Specifies that reading serialized JSON data supports the JSON5 syntax.
    NSJSONReadingJSON5Allowed API_AVAILABLE(macos(12.0), ios(15.0), watchos(8.0), tvos(15.0)) = (1UL << 3),
#endif
    /// Specifies that the parser assumes the top-level object is a dictionary, even without surrounding curly braces.
    NSJSONReadingTopLevelDictionaryAssumed API_AVAILABLE(macos(12.0), ios(15.0), watchos(8.0), tvos(15.0)) = (1UL << 4),

    /// Specifies that the parser should allow top-level objects that are not an `NSArray` or `NSDictionary`.
    ///
    /// @DeprecationSummary {
    ///     Use ``NSJSONReadingFragmentsAllowed`` instead.
    /// }
    NSJSONReadingAllowFragments API_DEPRECATED_WITH_REPLACEMENT("NSJSONReadingFragmentsAllowed", macos(10.7, API_TO_BE_DEPRECATED), ios(5.0, API_TO_BE_DEPRECATED), watchos(2.0, API_TO_BE_DEPRECATED), tvos(9.0, API_TO_BE_DEPRECATED)) = NSJSONReadingFragmentsAllowed,
} API_AVAILABLE(macos(10.7), ios(5.0), watchos(2.0), tvos(9.0));

/// Options used when writing JSON data.
typedef NS_OPTIONS(NSUInteger, NSJSONWritingOptions) {
    /// Specifies that the JSON output uses whitespace and indentation to make the output more readable.
    NSJSONWritingPrettyPrinted = (1UL << 0),

    /// Specifies that the output sorts dictionary keys using `[NSLocale systemLocale]` and `NSNumericSearch`.
    NSJSONWritingSortedKeys API_AVAILABLE(macos(10.13), ios(11.0), watchos(4.0), tvos(11.0)) = (1UL << 1),
    /// Specifies that the serializer should allow top-level objects that are not an `NSArray` or `NSDictionary`.
    NSJSONWritingFragmentsAllowed = (1UL << 2),
    /// Specifies that the serializer should not escape forward slashes (`/`).
    NSJSONWritingWithoutEscapingSlashes API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0)) = (1UL << 3),
} API_AVAILABLE(macos(10.7), ios(5.0), watchos(2.0), tvos(9.0));

/// An object that converts between JSON and the equivalent Foundation objects.
///
/// You use the ``JSONSerialization`` class to convert JSON to Foundation objects and convert Foundation objects to JSON.
///
/// To convert a Foundation object to JSON, the object must have the following properties:
///
/// - The top level object is an ``NSArray`` or ``NSDictionary``, unless you set the ``WritingOptions/fragmentsAllowed`` option.
/// - All objects are instances of ``NSString``, ``NSNumber``, ``NSArray``, ``NSDictionary``, or ``NSNull``.
/// - All dictionary keys are instances of ``NSString``.
/// - Numbers are neither `NaN` nor infinity.
///
/// Other rules may apply. Calling ``isValidJSONObject(_:)`` or attempting a conversion are the definitive ways to tell if the ``JSONSerialization`` class can convert given object to JSON data.
///
/// > Note:
/// > On iOS 7 and later and macOS 10.9 and later, ``JSONSerialization`` is thread safe.
API_AVAILABLE(macos(10.7), ios(5.0), watchos(2.0), tvos(9.0))
@interface NSJSONSerialization : NSObject

/// Returns a Boolean value that indicates whether a given object can be converted to JSON data.
///
/// The object must have the following properties: the top level object is an `NSArray` or `NSDictionary`; all objects are `NSString`, `NSNumber`, `NSArray`, `NSDictionary`, or `NSNull`; all dictionary keys are `NSString` instances; and `NSNumber` values are not NaN or infinity.
+ (BOOL)isValidJSONObject:(id)obj;

/// Returns JSON data from a Foundation object.
///
/// If the object will not produce valid JSON then an exception will be thrown. Setting the `NSJSONWritingPrettyPrinted` option will generate JSON with whitespace designed to make the output more readable. If that option is not set, the most compact possible JSON will be generated. The resulting data is encoded in UTF-8.
+ (nullable NSData *)dataWithJSONObject:(id)obj options:(NSJSONWritingOptions)opt error:(NSError **)error;

/// Returns a Foundation object from JSON data.
///
/// Set the `NSJSONReadingFragmentsAllowed` option if the parser should allow top-level objects that are not an `NSArray` or `NSDictionary`. Setting the `NSJSONReadingMutableContainers` option will make the parser generate mutable `NSArrays` and `NSDictionaries`. Setting the `NSJSONReadingMutableLeaves` option will make the parser generate mutable `NSString` objects. The data must be in one of the 5 supported encodings listed in the JSON specification: UTF-8, UTF-16LE, UTF-16BE, UTF-32LE, UTF-32BE. The most efficient encoding to use for parsing is UTF-8.
+ (nullable id)JSONObjectWithData:(NSData *)data options:(NSJSONReadingOptions)opt error:(NSError **)error;

#if !0
/// Writes a Foundation object as JSON into an output stream.
///
/// The stream should be opened and configured. The return value is the number of bytes written to the stream, or `0` on error. All other behavior of this method is the same as the `dataWithJSONObject:options:error:` method.
+ (NSInteger)writeJSONObject:(id)obj toStream:(NSOutputStream *)stream options:(NSJSONWritingOptions)opt error:(NSError **)error;

/// Returns a Foundation object from a JSON data stream.
///
/// The stream should be opened and configured. All other behavior of this method is the same as the `JSONObjectWithData:options:error:` method.
+ (nullable id)JSONObjectWithStream:(NSInputStream *)stream options:(NSJSONReadingOptions)opt error:(NSError **)error;
#endif
@end

NS_HEADER_AUDIT_END(nullability, sendability)
