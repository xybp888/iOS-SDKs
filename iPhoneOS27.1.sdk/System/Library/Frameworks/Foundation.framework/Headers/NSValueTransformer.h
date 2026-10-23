/*	NSValueTransformer.h
        Copyright (c) 2002-2019, Apple Inc. All rights reserved.
*/

#import <Foundation/NSObject.h>

@class NSArray<ObjectType>, NSString;

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

/// Named value transformers defined by `NSValueTransformer`.
typedef NSString *NSValueTransformerName NS_TYPED_EXTENSIBLE_ENUM;

/// The name of the transformer that negates a Boolean value.
FOUNDATION_EXPORT NSValueTransformerName const NSNegateBooleanTransformerName	API_AVAILABLE(macos(10.3), ios(3.0), watchos(2.0), tvos(9.0));

/// The name of the transformer that returns `true` if the value is `nil`.
FOUNDATION_EXPORT NSValueTransformerName const NSIsNilTransformerName		API_AVAILABLE(macos(10.3), ios(3.0), watchos(2.0), tvos(9.0));

/// The name of the transformer that returns `true` if the value is non-`nil`.
FOUNDATION_EXPORT NSValueTransformerName const NSIsNotNilTransformerName	API_AVAILABLE(macos(10.3), ios(3.0), watchos(2.0), tvos(9.0));

/// The name of the transformer that uses ``NSUnarchiver`` to unarchive data.
FOUNDATION_EXPORT NSValueTransformerName const NSUnarchiveFromDataTransformerName       API_DEPRECATED_WITH_REPLACEMENT("NSSecureUnarchiveFromDataTransformerName", macos(10.3, 10.14), ios(3.0, 12.0), watchos(2.0, 5.0), tvos(9.0, 12.0));

/// The name of the transformer that uses ``NSKeyedUnarchiver`` to unarchive data.
FOUNDATION_EXPORT NSValueTransformerName const NSKeyedUnarchiveFromDataTransformerName  API_DEPRECATED_WITH_REPLACEMENT("NSSecureUnarchiveFromDataTransformerName", macos(10.3, 10.14), ios(3.0, 12.0), watchos(2.0, 5.0), tvos(9.0, 12.0));

/// The name of the transformer that uses ``NSKeyedUnarchiver`` with secure coding to unarchive data.
FOUNDATION_EXPORT NSValueTransformerName const NSSecureUnarchiveFromDataTransformerName API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0));

/// An abstract class used to transform values from one representation to another.
API_AVAILABLE(macos(10.3), ios(3.0), watchos(2.0), tvos(9.0))
@interface NSValueTransformer : NSObject {
}

/// Registers the provided value transformer with a given identifier.
+ (void)setValueTransformer:(nullable NSValueTransformer *)transformer forName:(NSValueTransformerName)name;

/// Returns the value transformer identified by a given identifier.
+ (nullable NSValueTransformer *)valueTransformerForName:(NSValueTransformerName)name;

/// Returns an array of all the registered value transformer names.
+ (NSArray<NSValueTransformerName> *)valueTransformerNames;

/// Returns the class of objects returned when applying the value transformer.
+ (Class)transformedValueClass;

/// Returns a Boolean value that indicates whether the receiver can reverse a transformation.
+ (BOOL)allowsReverseTransformation;

/// Returns the result of transforming a given value.
- (nullable id)transformedValue:(nullable id)value;

/// Returns the result of the reverse transformation of a given value.
- (nullable id)reverseTransformedValue:(nullable id)value;

@end

/// A value transformer that converts data to and from classes that support secure coding.
///
/// This class provides a default ``ValueTransformer`` implementation for secure decoding. This class attempts to decode data into the classes listed within ``allowedTopLevelClasses``, which includes ``NSArray``, ``NSDictionary``, ``NSSet``, ``NSString``, ``NSNumber``, ``NSDate``, ``NSData``, ``NSURL``, ``NSUUID``, and ``NSNull``.
///
/// To archive or unarchive other classes that support ``NSSecureCoding``, create a subclass and override ``allowedTopLevelClasses`` to list the classes to transform.
///
/// To use ``NSSecureUnarchiveFromDataTransformer`` with <doc://com.apple.documentation/documentation/coredata>, use the name of this class, or the name of a subclass you implement, as the name of the transformer for an entity's attribute within a Core Data Model. If you use your own transformer subclass, register it with your app before intializing your persistent container with Core Data.
///
/// For an example of subclassing ``NSSecureUnarchiveFromDataTransformer``, see <doc://com.apple.documentation/documentation/coredata/handling-different-data-types-in-core-data>, which has a `ColorToDataTransformer` class that transforms <doc://com.apple.documentation/documentation/uikit/uicolor> to ``NSData`` and the reverse, to support archiving instances of <doc://com.apple.documentation/documentation/uikit/uicolor>.
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
@interface NSSecureUnarchiveFromDataTransformer : NSValueTransformer

/// The list of allowable classes which the top-level object in the archive must conform to on encoding and decoding.
///
/// Returns the result of \c +transformedValueClass if not \c Nil; otherwise, currently returns \c NSArray, \c NSDictionary, \c NSSet, \c NSString, \c NSNumber, \c NSDate, \c NSData, \c NSURL, \c NSUUID, and \c NSNull.
///
/// Can be overridden by subclasses to provide an expanded or different set of allowed transformation classes.
@property (class, readonly, copy) NSArray<Class> *allowedTopLevelClasses;

@end

NS_HEADER_AUDIT_END(nullability, sendability)
