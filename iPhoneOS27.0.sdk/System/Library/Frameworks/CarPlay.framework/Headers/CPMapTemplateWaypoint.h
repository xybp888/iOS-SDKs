//
//  CPMapTemplateWaypoint.h
//  CarPlay
//
//  Copyright © 2025 Apple Inc. All rights reserved.

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@class CPNavigationWaypoint;
@class CPTravelEstimates;

/**
 * CPMapTemplateWaypoint represents a waypoint with associated travel estimates
 */
API_AVAILABLE(ios(26.4)) API_UNAVAILABLE(tvos) API_UNAVAILABLE(tvos)
@interface CPMapTemplateWaypoint : NSObject <NSSecureCoding>

/**
 * The navigation waypoint containing location-based information and guidance for a point of interest along a route.
 */
@property (nonatomic, strong) CPNavigationWaypoint *waypoint;

/**
 * Travel estimates for reaching this waypoint, including time and distance calculations.
 */
@property (nonatomic, strong) CPTravelEstimates *travelEstimates;

/**
 * Initializes a new CPMapTemplateWaypoint with the specified waypoint and travel estimates.
 *
 * @param waypoint The navigation waypoint
 * @param travelEstimates The calculated travel estimates for reaching this waypoint
 * @return A new CPMapTemplateWaypoint instance ready for use with CarPlay templates
 */
- (instancetype)initWithWaypoint:(CPNavigationWaypoint *)waypoint
                 travelEstimates:(CPTravelEstimates *)travelEstimates;

- (instancetype)init NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
