//
//  CPNavigationSession.h
//  CarPlay
//
//  Copyright © 2018 Apple Inc. All rights reserved.
//

#import <CarPlay/CPManeuver.h>
#import <CarPlay/CPMapPanel.h>
#import <CarPlay/CPRerouteReason.h>
#import <CarPlay/CPRouteInformation.h>
#import <CarPlay/CPRouteSegment.h>
#import <CarPlay/CPTemplate.h>
#import <CarPlay/CPTravelEstimates.h>
#import <CarPlay/CPTrip.h>
#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSUInteger, CPTripPauseReason) {
    CPTripPauseReasonArrived          = 1,
    CPTripPauseReasonLoading          = 2,
    CPTripPauseReasonLocating         = 3,
    CPTripPauseReasonRerouting        = 4,
    CPTripPauseReasonProceedToRoute   = 5,
} API_AVAILABLE(ios(12.0)) API_UNAVAILABLE(tvos) API_UNAVAILABLE(macos, watchos);

/**
 @c CPNavigationSession represents the active navigation session. A @c CPNavigationSession will be created for you
 when calling startNavigationSessionForTrip: on @c CYMapTemplate
 */
API_AVAILABLE(ios(12.0)) API_UNAVAILABLE(tvos) API_UNAVAILABLE(macos, watchos)
CARPLAY_TEMPLATE_UI_ACTOR
@interface CPNavigationSession : NSObject

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

/**
 Pause the current trip.
 
 @param reason The reason navigation was paused.
 @param description An optional description of the pause reason. If @c nil, a system-provided string will be used.
 */
- (void)pauseTripForReason:(CPTripPauseReason)reason description:(nullable NSString *)description;

/**
 Pause the current trip.
 
 @param reason The reason navigation was paused.
 @param description An optional description of the pause reason. If @c nil, a system-provided string will be used.
 @param turnCardColor An optional color of the pause card. If @c nil, will fallback to the @c guidanceBackgroundColor on @c CPMapTemplate. If no color is specified there, will default to a system-provided color.
 */
- (void)pauseTripForReason:(CPTripPauseReason)reason description:(nullable NSString *)description turnCardColor:(nullable UIColor *)turnCardColor API_AVAILABLE(ios(15.4));

/**
 Resume the current trip with updated route information
 
 @param routeInformation The updated route information for the current trip
 */
- (void)resumeTripWithUpdatedRouteInformation:(CPRouteInformation *)routeInformation NS_SWIFT_NAME(resumeTrip(updatedRouteInformation:)) API_AVAILABLE(ios(17.4)) API_DEPRECATED_WITH_REPLACEMENT("resumeTripWithUpdatedRouteSegments:currentSegment:rerouteReason:", ios(17.4, 26.4));

/**
 Resume the current trip with updated route segments
 
 @param routeSegments The updated route segments for the current trip
 @param currentSegment The current route segment
 @param rerouteReason The reason for the reroute
 */
- (void)resumeTripWithUpdatedRouteSegments:(NSArray<CPRouteSegment *> *)routeSegments currentSegment:(CPRouteSegment *)currentSegment rerouteReason:(CPRerouteReason)rerouteReason NS_SWIFT_NAME(resumeTrip(updatedRouteSegments:currentSegment:rerouteReason:)) API_AVAILABLE(ios(26.4));

/**
 Resume navigation with an updated trip and route segments for cases such as the trip destination changing.
 
 @param trip The updated trip
 @param routeSegments The updated route segments for the current trip
 @param currentSegment The current route segment
 @param rerouteReason The reason for the reroute
 */
- (void)resumeNavigationWithUpdatedTrip:(CPTrip *)trip routeSegments:(NSArray<CPRouteSegment *> *)routeSegments currentSegment:(CPRouteSegment *)currentSegment rerouteReason:(CPRerouteReason)rerouteReason NS_SWIFT_NAME(resumeNavigation(updatedTrip:routeSegments:currentSegment:rerouteReason:)) API_AVAILABLE(ios(27.0));

/**
 Finish the trip.
 */
- (void)finishTrip;

/**
 Cancel the trip.
 */
- (void)cancelTrip;

/**
 The next maneuvers that should be performed to follow the current route.
 Multiple maneuvers are displayed simultaneously, however the system may limit the number of maneuvers shown at the same time.
 */
@property (nonatomic, readwrite, copy) NSArray<CPManeuver *> *upcomingManeuvers;

/**
 The current lane guidance to be used for navigation metdata.
 Must be set to nil if there is no current lane guidance. CPLaneGuidances set here must first be added to the session using addLaneGuidances:
 */
@property (nullable, nonatomic, readwrite, copy) CPLaneGuidance *currentLaneGuidance API_AVAILABLE(ios(17.4));

/**
 Use this method to add CPManeuvers in chronological order to the navigation session.
 The application must provide as many maneuvers as possible, as soon as they are available. All
 maneuvers set in upcomingManeuvers must be first added using this method.
 */
- (void)addManeuvers:(NSArray<CPManeuver *> *)maneuvers API_AVAILABLE(ios(17.4));

/**
 Use this method to add CPLaneGuidances in chronological order to the navigation session.
 CPLaneGuidance objects must be added as soon as they are available.
 */
- (void)addLaneGuidances:(NSArray<CPLaneGuidance *> *)laneGuidances API_AVAILABLE(ios(17.4));

/**
 Use this method to add CPRouteSegments in chronological order to the navigation session.
 CPRouteSegment objects must be added as soon as they are available.
 */
- (void)addRouteSegments:(NSArray<CPRouteSegment *> *)routeSegments API_AVAILABLE(ios(26.4));

/**
 Set this property with variants of the current road name. From most to least verbose.
 */
@property (nonatomic, copy) NSArray<NSString *> *currentRoadNameVariants API_AVAILABLE(ios(17.4));

/**
 Set this property with the current maneuver state based on how close the maneuver is.
 */
@property (nonatomic) CPManeuverState maneuverState API_AVAILABLE(ios(17.4));

/**
 The trip associated with this navigation session.
 */
@property (nonatomic, readonly, strong) CPTrip *trip;

/**
 Update the travel estimates for the active navigation session and maneuver.
 
 @param estimates The updated travel estimates.
 @param maneuver The maneuver pertaining to this update.
 */
- (void)updateTravelEstimates:(CPTravelEstimates *)estimates forManeuver:(CPManeuver *)maneuver;

/**
The options panel to display when the ellipsis button on the travel estimates is tapped.
 */
@property (nonatomic, strong, nullable) CPMapPanel *optionsPanel API_AVAILABLE(ios(27.0));

/**
The route segments associated with this navigation session.
 */
@property (nonatomic, readonly, strong) NSArray<CPRouteSegment *> *routeSegments API_AVAILABLE(ios(26.4));

/**
The current route segment.
 */
@property (nonatomic) CPRouteSegment *currentSegment API_AVAILABLE(ios(26.4));

/**
 Whether the vehicle is presently using route data for any features in its built-in navigation system.
 */
@property (nonatomic, readonly, getter=isRouteSharingEnabled) BOOL routeSharingEnabled API_AVAILABLE(ios(27.0));

/**
 Whether the connected vehicle supports the route sharing feature.
 */
@property (nonatomic, readonly, getter=isRouteSharingSupported) BOOL routeSharingSupported API_AVAILABLE(ios(27.0));

@end

NS_ASSUME_NONNULL_END
