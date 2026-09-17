//
//  CKLocationSortDescriptor.h
//  CloudKit
//
//  Copyright (c) 2014 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

#import <CloudKit/CKDefines.h>

@class CLLocation;

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

/// An object for sorting records that contain location data.
///
/// You can add a location sort descriptor to your queries when searching for records. At creation time, you must provide the sort descriptor with a key that has a <doc://com.apple.documentation/documentation/corelocation/cllocation> object as its value. The sort descriptor uses the value of that key to perform the sort.
///
/// CloudKit computes distance by drawing a direct line between the two locations that follows the curvature of the Earth. Distances don't account for altitude changes between the two locations.
API_AVAILABLE(macos(10.10), ios(8.0), watchos(3.0))
@interface CKLocationSortDescriptor : NSSortDescriptor <NSSecureCoding>

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

/// Creates a location sort descriptor using the specified key and relative location.
///
/// - Parameters:
///   - key: The name of the key with a <doc://com.apple.documentation/documentation/corelocation/cllocation> object as its value. The key must belong to the records you're sorting. The sort descriptor uses this key to retrieve the corresponding value from the record.
///   - relativeLocation: The reference location when sorting. CloudKit sorts records according to their distance from this location.
///
/// During sorting, the sort descriptor computes the distance between the value in the `relativeLocation` parameter and the location value in the specified key of each record. It then sorts the records in ascending order using the distance between the two points. You can't change the sort order.
- (instancetype)initWithKey:(NSString *)key relativeLocation:(CLLocation *)relativeLocation NS_DESIGNATED_INITIALIZER;

/// Creates a location sort descriptor from a serialized instance.
///
/// - Parameters:
///   - aDecoder: The coder to use when deserializing the location sort descriptor.
- (instancetype)initWithCoder:(NSCoder *)aDecoder NS_DESIGNATED_INITIALIZER;

/// The reference location for sorting records.
@property (readonly, copy, nonatomic) CLLocation *relativeLocation;

@end

NS_HEADER_AUDIT_END(nullability, sendability)
