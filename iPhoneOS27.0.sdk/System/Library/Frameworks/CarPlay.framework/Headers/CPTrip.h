//
//  CPTrip.h
//  CarPlay
//
//  Copyright © 2018 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <MapKit/MapKit.h>
#import <CarPlay/CPLocation.h>

NS_ASSUME_NONNULL_BEGIN

@class CPNavigationWaypoint;
@class CPRouteDetail;
@class CPTravelEstimates;

/**
 @c CPRouteChoice describes a possible route for a @c CPTrip.
 */
API_AVAILABLE(ios(12.0)) API_UNAVAILABLE(tvos) API_UNAVAILABLE(macos, watchos)
@interface CPRouteChoice : NSObject <NSCopying, NSSecureCoding>

/**
 Initialize a @c CPRouteChoice with summary variants, additional information variants, and selection summary variants.
 The variant strings should be provided as localized, displayable content.
 */
- (instancetype)initWithSummaryVariants:(NSArray<NSString *> *)summaryVariants additionalInformationVariants:(NSArray<NSString *> *)additionalInformationVariants selectionSummaryVariants:(NSArray<NSString *> *)selectionSummaryVariants NS_DESIGNATED_INITIALIZER;

/**
 Initialize a @c CPRouteChoice with summary variants, additional information variants,
 selection summary variants, and travel estimates.

 @discussion This initializer enables you to provide comprehensive route information including
 supplementary details through the travel estimates parameter. During route selection, users
 can compare routes based on time, distance, and additional factors like toll costs or
 energy consumption.

 @param summaryVariants An array of summary strings, from most to least preferred. The system
 selects the first variant that fits available space. Example: "Via I-280 S"
 @param additionalInformationVariants An array of additional information strings describing
 route characteristics. Example: "Fastest Route", "Avoids Tolls"
 @param selectionSummaryVariants An array of summary strings used when this route is selected
 @param travelEstimates Optional travel estimates including distance, time, and additional
 route information like tolls, fuel consumption, or battery usage. This information
 helps users compare routes beyond just time and distance.
 @return A new @c CPRouteChoice instance with travel estimates

 @note When travel estimates include additional route information, the system displays this
 information prominently during route selection to facilitate informed decision-making.
 */
- (instancetype)initWithSummaryVariants:(NSArray<NSString *> *)summaryVariants
          additionalInformationVariants:(NSArray<NSString *> *)additionalInformationVariants
               selectionSummaryVariants:(NSArray<NSString *> *)selectionSummaryVariants
                        travelEstimates:(nullable CPTravelEstimates *)travelEstimates NS_DESIGNATED_INITIALIZER
API_AVAILABLE(ios(27.0)) API_UNAVAILABLE(tvos) API_UNAVAILABLE(macos, watchos);

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

/**
 summaryVariants is an array of summary variants for this route choice, arranged from most to least preferred. You must provide at least one variant.
 The system will select the first variant that fits the available space. The variant strings should be provided as localized, displayable content.
 Example: "Via I-280 S"
 */
@property (nonatomic, readonly, copy) NSArray<NSString *> *summaryVariants;

/**
 selectionSummaryVariants is an array of summary variants for this route choice, arranged from most to least preferred. You must provide at least one variant.
 The system will select the first variant that fits the available space.
 */
@property (nullable, nonatomic, readonly, copy) NSArray<NSString *> *selectionSummaryVariants;

/**
 additionalInformationVariants is an array of additional information variants for this route choice, arranged from most to least preferred. You must provide at least one variant.
 The system will select the first variant that fits the available space. The variant strings should be provided as localized, displayable content.
 Examples: "Fastest Route", "Avoids Tolls"
 */
@property (nullable, nonatomic, readonly, copy) NSArray<NSString *> *additionalInformationVariants;

/**
 Any custom user info related to this route choice.
 */
@property (nullable, nonatomic, strong) id userInfo;

/**
 Trip preview information such as battery, fuel, or toll information to display for this route choice.

 @discussion The travel estimates associated with this route choice provide comprehensive information
 about the route, including traditional metrics (time and distance) and supplementary information
 (tolls, energy consumption, etc.).

 During route selection, the system displays this information to help users make informed decisions.
 For example, users can compare toll costs between different route options or evaluate whether
 their vehicle's battery level will be sufficient for a particular route.

 @note This property is read-only and set during initialization. To update route information,
 create a new CPRouteChoice instance with updated travel estimates.
 */
@property (nullable, nonatomic, readonly, strong) CPTravelEstimates *travelEstimates API_AVAILABLE(ios(27.0)) API_UNAVAILABLE(tvos) API_UNAVAILABLE(macos, watchos);

@end

/**
 @c CPTrip represents an origin and destination with route choices.
 */
API_AVAILABLE(ios(12.0)) API_UNAVAILABLE(tvos) API_UNAVAILABLE(macos, watchos)
@interface CPTrip : NSObject <NSSecureCoding>


/**
 Initialize a @c CPTrip with an origin waypoint, destination waypoint, and route choices.
 */
- (instancetype)initWithOriginWaypoint:(CPNavigationWaypoint *)origin destinationWaypoint:(CPNavigationWaypoint *)destination routeChoices:(NSArray<CPRouteChoice *> *)routeChoices NS_DESIGNATED_INITIALIZER API_AVAILABLE(ios(26.4));

/**
 Initialize a @c CPTrip with an origin item, destination item, and route choices.
 */
- (instancetype)initWithOrigin:(MKMapItem *)origin destination:(MKMapItem *)destination routeChoices:(NSArray<CPRouteChoice *> *)routeChoices API_DEPRECATED_WITH_REPLACEMENT("initWithOriginWaypoint:destinationWaypoint:routeChoices:", ios(12.0, 26.4));
- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

/**
 @c MKMapItem representing the origin for the trip.
 */
@property (nonatomic, readonly, strong) MKMapItem *origin API_DEPRECATED_WITH_REPLACEMENT("originWaypoint", ios(12.0, 26.4));

/**
 @c MKMapItem representing the destination for the trip.
 */
@property (nonatomic, readonly, strong) MKMapItem *destination API_DEPRECATED_WITH_REPLACEMENT("destinationWaypoint", ios(12.0, 26.4));

/**
 @c CPNavigationWaypoint representing the origin for the trip.
 */
@property(nonatomic, readonly) CPNavigationWaypoint *originWaypoint API_AVAILABLE(ios(26.4));

/**
 @c CPNavigationWaypoint representing the destination for the trip.
 */
@property(nonatomic, readonly) CPNavigationWaypoint *destinationWaypoint API_AVAILABLE(ios(26.4));

/**
 Array of @c CPRouteChoices for the trip.
 */
@property (nonatomic, readonly, copy) NSArray<CPRouteChoice *> *routeChoices;

/**
 Any custom user info related to this trip.
 */
@property (nullable, nonatomic, strong) id userInfo;

/**
 destinationNameVariants is an array of @c NSString representing the name of the destination for
 this trip, arranged from most to least preferred. You must provide at least one variant.
 The variant strings should be provided as localized, displayable content.
 */
@property (nonatomic, copy, nullable) NSArray<NSString *> *destinationNameVariants API_DEPRECATED_WITH_REPLACEMENT("destinationWaypoint.nameVariants", ios(17.4, 27.0));

/**
 Set to @YES to enable sharing of the destination of this trip.
 */
@property (nonatomic) BOOL hasShareableDestination API_AVAILABLE(ios(26.1));

/**
 Set to @NO to disable route sharing for this trip when route sharing is not supported in the current region.
 */
@property (nonatomic) BOOL routeSegmentsAvailableForRegion API_AVAILABLE(ios(26.4));

@end

NS_ASSUME_NONNULL_END
