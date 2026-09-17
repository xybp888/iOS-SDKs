//
//  CPRouteSegment.h
//  CarPlay
//
//  Copyright © 2025 Apple Inc. All rights reserved.

#import <Foundation/Foundation.h>
#import <CarPlay/CPLocation.h>

@class CPLaneGuidance, CPManeuver, CPNavigationWaypoint, CPTravelEstimates;

NS_ASSUME_NONNULL_BEGIN
/**
 CPRouteSegment describes information pertaining to a segment of a route.
 */
API_AVAILABLE(ios(26.4)) API_UNAVAILABLE(tvos) API_UNAVAILABLE(macos, watchos) NS_SWIFT_SENDABLE
@interface CPRouteSegment : NSObject <NSCopying>

/**
 Initialize a CPRouteSegment object with maneuvers, lane guidances, the current maneuvers, the current lane guidance, trip travel estimates, the current maneuver travel estimates, the origin and the destination. If the current trip supports route sharing, also provide coordinates along the current segment.
 */
- (instancetype)initWithOrigin:(CPNavigationWaypoint *)origin
                   destination:(CPNavigationWaypoint *)destination
                     maneuvers:(NSArray<CPManeuver *> *)maneuvers
                 laneGuidances:(NSArray<CPLaneGuidance *> *)laneGuidances
               currentManeuvers:(NSArray<CPManeuver *> *)currentManeuvers
           currentLaneGuidance:(CPLaneGuidance *)currentLaneGuidance
            tripTravelEstimates:(CPTravelEstimates *)tripTravelEstimates
        maneuverTravelEstimates:(CPTravelEstimates *)maneuverTravelEstimates
                   coordinates:(CPLocationCoordinate3D *)coordinates
            coordinatesCount:(NSInteger)coordinatesCount NS_SWIFT_NAME(init(__origin:destination:maneuvers:laneGuidances:currentManeuvers:currentLaneGuidance:tripTravelEstimates:maneuverTravelEstimates:coordinates:coordinatesCount:)) NS_DESIGNATED_INITIALIZER NS_REFINED_FOR_SWIFT;

- (instancetype)init NS_UNAVAILABLE;

/**
 identifier is a NSUUID that uniquely identifies this route segment.
*/
@property (nonatomic, readonly, strong) NSUUID *identifier;

/**
 origin is a CPNavigationWaypoint, describing the origin of the segment.
*/
@property(nonatomic, readonly) CPNavigationWaypoint *origin;

/**
 destination is a CPNavigationWaypoint, describing the destination of the segment.
*/
@property(nonatomic, readonly) CPNavigationWaypoint *destination;

/**
 coordinates is an array of CPLocationCoordinate3D, describing coordinates along the segment.
*/
@property (nullable, nonatomic, readonly) CPLocationCoordinate3D *coordinates NS_REFINED_FOR_SWIFT;

/**
 coordinatesCount is an integer, describing the number of coordinates along the segment.
*/
@property (nonatomic, readonly) NSInteger coordinatesCount NS_REFINED_FOR_SWIFT;

/**
 maneuvers is an array of CPManeuver objects, each describes a single maneuver.
*/
@property (nonatomic, readonly, copy) NSArray<CPManeuver *> *maneuvers;

/**
 laneGuidances is an array of CPLaneGuidance objects, each describes a single lane guidance.
*/
@property (nonatomic, readonly, copy) NSArray<CPLaneGuidance *> *laneGuidances;

/**
 currentManeuvers is an array of CPManeuver objects, describing the current maneuvers.
*/
@property (nonatomic, readonly, copy) NSArray<CPManeuver *> *currentManeuvers;

/**
 currentLaneGuidance is a CPLaneGuidance object, describing the current lane guidance.
*/
@property (nonatomic, readonly, copy) CPLaneGuidance *currentLaneGuidance;

/**
 tripTravelEstimates is a CPTravelEstimates object, describing the travel estimates for the current trip.
*/
@property (nonatomic, readonly, copy) CPTravelEstimates *tripTravelEstimates;

/**
 maneuverTravelEstimates is a CPTravelEstimates object, describing the travel estimates for the first maneuver in the list of current maneuvers.
*/
@property (nonatomic, readonly, copy) CPTravelEstimates *maneuverTravelEstimates;

@end

NS_ASSUME_NONNULL_END
