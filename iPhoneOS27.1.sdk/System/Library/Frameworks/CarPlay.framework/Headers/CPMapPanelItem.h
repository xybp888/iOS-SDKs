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

API_AVAILABLE(ios(27.0)) API_UNAVAILABLE(tvos) API_UNAVAILABLE(macos, watchos)
@interface CPMapPanelItem : CPPanelItem

/**
 Initializes a map template item wrapping a @c CPTrip.
 */
- (instancetype)initWithTrip:(CPTrip *)trip handler:(nullable void (^)(CPMapPanelItem *item, dispatch_block_t completionBlock))handler;

/**
 Initializes a map template item wrapping a @c CPTravelEstimates.
 */
- (instancetype)initWithTravelEstimates:(CPTravelEstimates *)travelEstimates handler:(nullable void (^)(CPMapPanelItem *item, dispatch_block_t completionBlock))handler;

/**
 Initializes a map template item wrapping a @c CPRouteChoice.
 */
- (instancetype)initWithRouteChoice:(CPRouteChoice *)routeChoice handler:(nullable void (^)(CPMapPanelItem *item, dispatch_block_t completionBlock))handler;

/**
 Initializes a map template item wrapping an array of @c CPRouteDetail objects.
 */
- (instancetype)initWithRouteDetails:(NSArray<CPRouteDetail *> *)routeDetails handler:(nullable void (^)(CPMapPanelItem *item, dispatch_block_t completionBlock))handler;

/**
 Initializes a map template item wrapping a @c CPChargingStationConnection.
 */
- (instancetype)initWithChargingStationConnection:(CPChargingStationConnection *)chargingStationConnection handler:(nullable void (^)(CPMapPanelItem *item, dispatch_block_t completionBlock))handler;

/**
 Initializes a map template item wrapping a @c CPMapTemplateWaypoint.
 */
- (instancetype)initWithMapTemplateWaypoint:(CPMapTemplateWaypoint *)mapTemplateWaypoint image:(nullable UIImage *)image handler:(nullable void (^)(CPMapPanelItem *item, dispatch_block_t completionBlock))handler;

@end

NS_ASSUME_NONNULL_END
