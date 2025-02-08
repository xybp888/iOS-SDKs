//
//  CPNavigationEnum.h
//  CarPlay
//
//  Copyright © 2023 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

#import <CarPlay/CPLane.h>
#import <CarPlay/CPManeuver.h>

#pragma mark - Maneuver
NSString *NSStringFromCPManeuverType(CPManeuverType maneuverType);
NSString *NSStringFromCPJunctionType(CPJunctionType junctionType);
NSString *NSStringFromCPTrafficSide(CPTrafficSide trafficSide);

#pragma mark - Lane
NSString *NSStringFromCPLaneStatus(CPLaneStatus laneStatus);

