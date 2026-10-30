//
//  CPMapPanelItem.h
//  CarPlay
//
//  Copyright © 2026 Apple Inc. All rights reserved.
//

#import <CarPlay/CPPanelItem.h>
#import <UIKit/UIKit.h>

@class CPTrip;
@class CPTravelEstimates;
@class CPRouteChoice;
@class CPRouteDetail;
@class CPChargingStationConnection;
@class CPMapTemplateWaypoint;
@class CPTextButton;

NS_ASSUME_NONNULL_BEGIN

/**
 A type that manages the waypoint, route, trip, and other information you display in a map panel.

 A `CPMapPanelItem` object stores navigation-related information and manages interactions with that information. When creating
 a ``CPMapPanel`` to display over your custom map, configure it with one or more items with the information you want to display.
 Use items to display information about:

 * Trip details for a particular journey
 * Travel estimates for a trip
 * Route choices between a start and end point
 * Route-related details such as costs and consumption metrics
 * Charging station connection details
 * Navigation waypoints

 Create one or more `CPMapPanelItem` objects and add them to a ``CPMapPanelSection``. You can add multiple items to a section
 and each item can contain different information. For example, you might include one item with the trip details and additional items
 to present route-specific options. Provide a handler with your item if you want to respond when someone taps or selects the item.

 Each type of item displays different information from the map panel interface. For example, an item you initialize with a ``CPTrip``
 object displays the trip’s destination and origin plus the number of route choices. When configuring a section, you might include
 multiple items of different types to present a complete view of the trip.
 */
API_AVAILABLE(ios(27.0)) API_UNAVAILABLE(tvos) API_UNAVAILABLE(macos, watchos)
@interface CPMapPanelItem : CPPanelItem

/**
 Creates a map panel item with trip-related details.

 - Parameters:
     - trip: The trip object that contains the origin, destination, and route information.
     - handler: A closure you use to respond when someone taps or selects the item. The closure takes the map panel item as a
        parameter and returns no value. Specify `nil` if you don’t want to respond to interactions with the item.
 - Returns: A map panel item initialized with trip information.

 For this type of item, the map panel shows journey’s destination point, its origin point, and the number of available route choices.
 This item type doesn’t show details about the individual route choice.
 */
- (instancetype)initWithTrip:(CPTrip *)trip handler:(nullable void (^)(CPMapPanelItem *item, dispatch_block_t completionBlock))handler;

/**
 Creates a map panel item with travel estimate information.

 - Parameters:
     - travelEstimates: The object that provides the remaining distance and time values for a trip.
     - handler: A closure you use to respond when someone taps or selects the item. The closure takes the map panel item as a
        parameter and returns no value. Specify `nil` if you don’t want to respond to interactions with the item.
 - Returns: A map panel item initialized with travel estimates.

 For this type of item, the map panel displays the expected arrival time, along with the remaining distance and time information.
 */
- (instancetype)initWithTravelEstimates:(CPTravelEstimates *)travelEstimates handler:(nullable void (^)(CPMapPanelItem *item, dispatch_block_t completionBlock))handler;

/**
 Creates a map panel item with one of the route choices available for a trip.

 - Parameters:
     - routeChoice: A route choice for an upcoming trip.
     - handler: A closure you use to respond when someone taps or selects the item. The closure takes the map panel item as a
        parameter and returns no value. Specify `nil` if you don’t want to respond to interactions with the item.
 - Returns: A map panel item initialized with a route choice.

 For this type of item, the map panel displays the relevant route choice summaries.
 */
- (instancetype)initWithRouteChoice:(CPRouteChoice *)routeChoice handler:(nullable void (^)(CPMapPanelItem *item, dispatch_block_t completionBlock))handler;

/**
 Creates a map panel item with route details.

 - Parameters:
     - routeDetails: The route detail that helps someone make an informed decision about their journey.
     - handler: A closure you use to respond when someone taps or selects the item. The closure takes the map panel item as a
        parameter and returns no value. Specify `nil` if you don’t want to respond to interactions with the item.
 - Returns: A map panel item initialized with route details.

 For this type of item, the map panel displays up to four route details per item.
 */
- (instancetype)initWithRouteDetails:(NSArray<CPRouteDetail *> *)routeDetails handler:(nullable void (^)(CPMapPanelItem *item, dispatch_block_t completionBlock))handler;

/**
 Creates a map panel item with charging connection details.

 - Parameters:
     - chargingStationConnection: The details of a charging station.
     - handler: A closure you use to respond when someone taps or selects the item. The closure takes the map panel item as a
        parameter and returns no value. Specify `nil` if you don’t want to respond to interactions with the item.
 - Returns: A map panel item initialized with charging information.

 For this type of item, the map panel displays the charging connector type and the supported power and voltage outputs.
 */
- (instancetype)initWithChargingStationConnection:(CPChargingStationConnection *)chargingStationConnection handler:(nullable void (^)(CPMapPanelItem *item, dispatch_block_t completionBlock))handler;

/**
 Creates a map panel item with waypoint information.

 - Parameters:
     - mapTemplateWaypoint: The waypoint information.
     - image: An image to display for the waypoint.
     - handler: A closure you use to respond when someone taps or selects the item. The closure takes the map panel item as a
        parameter and returns no value. Specify `nil` if you don’t want to respond to interactions with the item.
 - Returns: A map panel item initialized with waypoint details.

 For this type of item, the map panel displays the waypoint name, address, and any available route details.
 */
- (instancetype)initWithMapTemplateWaypoint:(CPMapTemplateWaypoint *)mapTemplateWaypoint image:(nullable UIImage *)image handler:(nullable void (^)(CPMapPanelItem *item, dispatch_block_t completionBlock))handler;

@end

NS_ASSUME_NONNULL_END
