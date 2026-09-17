//
//  CPNavigationWaypoint.h
//  CarPlay
//
//  Copyright © 2025 Apple Inc. All rights reserved.

#import <CarPlay/CPLocation.h>
#import <Foundation/Foundation.h>

@class MKMapItem;

NS_ASSUME_NONNULL_BEGIN

/**
 CPNavigationWaypoint represents a point of interest along a route that provides location-based information and guidance.
 */
API_AVAILABLE(ios(26.4)) API_UNAVAILABLE(tvos) API_UNAVAILABLE(macos, watchos) NS_SWIFT_SENDABLE
@interface CPNavigationWaypoint : NSObject  <NSSecureCoding>

/**
 centerPoint is a CPLocationCoordinate3D representing the primary coordinate location of the waypoint.
 */
@property (nonatomic, readonly) CPLocationCoordinate3D centerPoint;

/**
 locationThreshold is the maximum distance in meters from the centerPoint used to determine if a destination is valid.
 */
@property (nonatomic, readonly, nullable) NSMeasurement<NSUnitLength *> *locationThreshold;

/**
 name is an optional display name for the waypoint.
 */
@property (nonatomic, readonly, nullable) NSString *name
API_DEPRECATED_WITH_REPLACEMENT("nameVariants", ios(26.4, 27.0));

/**
 nameVariants is an array of @c NSString representing variants of the waypoint's display name, arranged from most to least preferred.
 The variant strings should be provided as localized, displayable content.
 */
@property (nonatomic, readonly) NSArray<NSString *> *nameVariants API_AVAILABLE(ios(27.0));

/**
 address is an optional address string for the waypoint, formatted with newline characters separating each address component.
 Example: "Apple Inc.\n1 Apple Park Way\nCupertino, CA 95014\nUnited States"
 */
@property (nonatomic, readonly, nullable) NSString *address
API_DEPRECATED_WITH_REPLACEMENT("addressVariants", ios(26.4, 27.0));

/**
 addressVariants is an array of @c NSString representing variants of the waypoint's address, arranged from most to least preferred.
 The variant strings should be provided as localized, displayable content.
 */
@property (nonatomic, readonly) NSArray<NSString *> *addressVariants API_AVAILABLE(ios(27.0));

/**
 entryPoints is an optional array of CPLocationCoordinate3D entry points. These represent alternative access points to reach the waypoint.
 */
@property (nonatomic, readonly) CPLocationCoordinate3D *entryPoints NS_REFINED_FOR_SWIFT;

/**
 entryPointsCount is the number of entry points available in the entryPoints array.
 */
@property (nonatomic, readonly) NSUInteger entryPointsCount NS_REFINED_FOR_SWIFT;

/**
The timezone for the waypoint.
*/
@property (nonatomic, readonly, nullable) NSTimeZone *timeZone;

/**
 Initialize a CPNavigationWaypoint object with a center point, location threshold, optional name and name variants, optional long address and short address, optional entry points, and a timezone.
 */
- (instancetype)initWithCenterPoint:(CPLocationCoordinate3D)centerPoint
                  locationThreshold:(nullable NSMeasurement<NSUnitLength *> *)locationThreshold
                       nameVariants:(NSArray<NSString *> *)nameVariants
                    addressVariants:(NSArray<NSString *> *)addressVariants
                        entryPoints:(CPLocationCoordinate3D *)entryPoints
                   entryPointsCount:(NSUInteger)entryPointsCount
                           timeZone:(nullable NSTimeZone *)timeZone NS_DESIGNATED_INITIALIZER NS_REFINED_FOR_SWIFT;

/**
 Initialize a CPNavigationWaypoint object with a center point, location threshold, optional name and address, optional entry points, and a timezone.
 */
- (instancetype)initWithCenterPoint:(CPLocationCoordinate3D)centerPoint
                  locationThreshold:(nullable NSMeasurement<NSUnitLength *> *)locationThreshold
                               name:(nullable NSString *)name
                            address:(nullable NSString *)address
                        entryPoints:(CPLocationCoordinate3D *)entryPoints
                   entryPointsCount:(NSUInteger)entryPointsCount
                           timeZone:(nullable NSTimeZone *)timeZone NS_REFINED_FOR_SWIFT
API_DEPRECATED_WITH_REPLACEMENT("initWithCenterPoint:locationThreshold:nameVariants:addressVariants:entryPoints:entryPointsCount:timeZone:", ios(26.4, 27.0));;

/**
 Initialize a CPNavigationWaypoint object from an MKMapItem with a location threshold and optional entry points.
 */
- (instancetype)initWithMapItem:(MKMapItem *)mapItem
              locationThreshold:(nullable NSMeasurement<NSUnitLength *> *)locationThreshold
                    entryPoints:(CPLocationCoordinate3D *)entryPoints
               entryPointsCount:(NSUInteger)entryPointsCount NS_REFINED_FOR_SWIFT;

- (instancetype)init NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
