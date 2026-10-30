/*	NSPropertyList.h
	Copyright (c) 2002-2019, Apple Inc. All rights reserved.
*/

#import <Foundation/NSObject.h>
#include <CoreFoundation/CFPropertyList.h>

@class NSData, NSString, NSError, NSInputStream, NSOutputStream;

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

/// These constants specify mutability options for property list objects created during property list deserialization.
typedef NS_OPTIONS(NSUInteger, NSPropertyListMutabilityOptions) {
    /// Causes the returned property list to contain immutable objects.
    NSPropertyListImmutable = kCFPropertyListImmutable,
    /// Causes the returned property list to have mutable containers but immutable leaves.
    NSPropertyListMutableContainers = kCFPropertyListMutableContainers,
    /// Causes the returned property list to have mutable containers and mutable leaves.
    NSPropertyListMutableContainersAndLeaves = kCFPropertyListMutableContainersAndLeaves
};

/// These constants are used to specify a property list serialization format.
typedef NS_ENUM(NSUInteger, NSPropertyListFormat) {
    /// Specifies the ASCII property list format inherited from the OpenStep APIs.
    NSPropertyListOpenStepFormat = kCFPropertyListOpenStepFormat,
    /// Specifies the XML property list format.
    NSPropertyListXMLFormat_v1_0 = kCFPropertyListXMLFormat_v1_0,
    /// Specifies the binary property list format.
    NSPropertyListBinaryFormat_v1_0 = kCFPropertyListBinaryFormat_v1_0
};

/// A type that specifies read options for property list deserialization.
///
/// The only read options supported are described in `NSPropertyListMutabilityOptions`.
typedef NSPropertyListMutabilityOptions NSPropertyListReadOptions;
typedef NSUInteger NSPropertyListWriteOptions;

/// An object that converts between a property list and one of several serialized representations.
///
/// The ``PropertyListSerialization`` class provides methods that convert a property list to and from several serialized formats. A property list is itself an array or dictionary that contains only ``NSData``, ``NSString``, ``NSArray``, ``NSDictionary``, ``NSDate``, and ``NSNumber`` objects.
///
/// Property list objects are toll-free bridged with their respective Core Foundation types (<doc://com.apple.documentation/documentation/corefoundation/cfdata>, <doc://com.apple.documentation/documentation/corefoundation/cfstring>, and so on). See [Toll-Free Bridging](https://developer.apple.com/library/archive/documentation/General/Conceptual/CocoaEncyclopedia/Toll-FreeBridgin/Toll-FreeBridgin.html#//apple_ref/doc/uid/TP40010810-CH2)  for more information on toll-free bridging.
@interface NSPropertyListSerialization : NSObject

/// Returns a Boolean value that indicates whether a given property list is valid for a given format.
+ (BOOL)propertyList:(id)plist isValidForFormat:(NSPropertyListFormat)format;

/// Returns an `NSData` object containing the serialized representation of a given property list in a given format.
///
/// The format can be either `NSPropertyListXMLFormat_v1_0` or `NSPropertyListBinaryFormat_v1_0`. The `opt` parameter is currently unused and should be set to `0`. If an error occurs the return value will be `nil` and the error parameter (if non-NULL) set to an autoreleased `NSError` describing the problem.
+ (nullable NSData *)dataWithPropertyList:(id)plist format:(NSPropertyListFormat)format options:(NSPropertyListWriteOptions)opt error:(out NSError **)error API_AVAILABLE(macos(10.6), ios(4.0), watchos(2.0), tvos(9.0));

#if !0
/// Writes a property list to an output stream in a given format.
///
/// The stream should be opened and configured. The format can be either `NSPropertyListXMLFormat_v1_0` or `NSPropertyListBinaryFormat_v1_0`. The `opt` parameter is currently unused and should be set to `0`. If an error occurs the return value will be `0` and the error parameter (if non-NULL) set to an autoreleased `NSError` describing the problem. In a successful case, the return value is the number of bytes written to the stream.
+ (NSInteger)writePropertyList:(id)plist toStream:(NSOutputStream *)stream format:(NSPropertyListFormat)format options:(NSPropertyListWriteOptions)opt error:(out NSError **)error API_AVAILABLE(macos(10.6), ios(4.0), watchos(2.0), tvos(9.0));
#endif

/// Creates and returns a property list from the specified data.
///
/// The options can be any of `NSPropertyListMutabilityOptions`. If the format parameter is non-NULL, it will be filled out with the format that the property list was stored in. If an error occurs the return value will be `nil` and the error parameter (if non-NULL) set to an autoreleased `NSError` describing the problem.
+ (nullable id)propertyListWithData:(NSData *)data options:(NSPropertyListReadOptions)opt format:(nullable NSPropertyListFormat *)format error:(out NSError **)error API_AVAILABLE(macos(10.6), ios(4.0), watchos(2.0), tvos(9.0));

#if !0
/// Creates and returns a property list by reading from the specified stream.
///
/// The options can be any of `NSPropertyListMutabilityOptions`. If the format parameter is non-NULL, it will be filled out with the format that the property list was stored in. If an error occurs the return value will be `nil` and the error parameter (if non-NULL) set to an autoreleased `NSError` describing the problem.
+ (nullable id)propertyListWithStream:(NSInputStream *)stream options:(NSPropertyListReadOptions)opt format:(nullable NSPropertyListFormat *)format error:(out NSError **)error API_AVAILABLE(macos(10.6), ios(4.0), watchos(2.0), tvos(9.0));

/// Returns a data object containing a given property list in a given format.
///
/// @DeprecationSummary {
///     Use ``NSPropertyListSerialization/dataWithPropertyList:format:options:error:`` instead.
/// }
+ (nullable NSData *)dataFromPropertyList:(id)plist format:(NSPropertyListFormat)format errorDescription:(out __strong NSString * _Nullable * _Nullable)errorString API_DEPRECATED("Use dataWithPropertyList:format:options:error: instead.", macos(10.0,10.10), ios(2.0,8.0), watchos(2.0,2.0), tvos(9.0,9.0));
#endif

/// Creates and returns a property list from the specified data and using the specified options.
///
/// @DeprecationSummary {
///     Use ``NSPropertyListSerialization/propertyListWithData:options:format:error:`` instead.
/// }
+ (nullable id)propertyListFromData:(NSData *)data mutabilityOption:(NSPropertyListMutabilityOptions)opt format:(nullable NSPropertyListFormat *)format errorDescription:(out __strong NSString * _Nullable * _Nullable)errorString API_DEPRECATED("Use propertyListWithData:options:format:error: instead.", macos(10.0,10.10), ios(2.0,8.0), watchos(2.0,2.0), tvos(9.0,9.0));

@end

NS_HEADER_AUDIT_END(nullability, sendability)
