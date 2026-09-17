//
//  CPRouteDetail.h
//  CarPlay
//
//  Copyright © 2026 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CarPlay/CPTemplate.h>

NS_ASSUME_NONNULL_BEGIN

/**
 @c CPRouteDetail provides additional contextual information about a route that can be displayed
 alongside standard routing details. This includes environmental data, vehicle consumption metrics,
 costs, and custom information specific to your app's routing capabilities.

 Route information appears in the route selection interface and during active navigation, helping users
 make informed decisions about their journey. The system automatically formats and displays this
 information using appropriate styling and placement.

 @discussion Use route information to differentiate between routing options and provide transparency
 about journey characteristics. For example, display toll costs to help users choose between paid
 expressways and free alternatives, or show battery consumption for electric vehicles to ensure
 destination reachability.

 @note Route information is supplementary to core routing details (distance, time, maneuvers). The
 system may choose to display some or all information based on available space and user context.
 */
API_AVAILABLE(ios(27.0)) API_UNAVAILABLE(tvos) API_UNAVAILABLE(macos, watchos)
CARPLAY_TEMPLATE_UI_ACTOR
@interface CPRouteDetail : NSObject <NSCopying, NSSecureCoding>

/**
 Creates additional route information for a toll amount.

 Use this method to display toll costs associated with a route. The toll amount will be formatted
 according to the provided locale's currency settings.

 @discussion Toll information helps users make informed routing decisions, particularly when comparing
 routes with varying toll costs. The system automatically formats the value using the locale's currency
 symbol, decimal separator, and digit grouping conventions.

 @param value The toll amount as a decimal value (e.g., 5.50 for $5.50)
 @param locale The locale to use for currency formatting. The locale's currency code determines the
        currency symbol and formatting rules. Pass @c [NSLocale currentLocale] to use the user's
        preferred locale, or create a specific locale for fixed currency display.
 @return A new @c CPRouteDetail instance representing the toll amount

 @note The system displays toll amounts with high visibility during route selection to help users
       understand cost implications before committing to a route.
 */
+ (instancetype)routeDetailWithTollAmount:(double)value locale:(NSLocale *)locale;

/**
 Creates additional route information for a fuel level.

 Use this method to display the estimated fuel level upon arrival at the destination. This helps
 drivers of liquid-fuel vehicles plan refueling stops along their route.

 @discussion The system automatically converts the measurement to the user's preferred units based on
 their region and settings (e.g., liters in metric regions, gallons in the US). Display the estimated
 remaining fuel rather than fuel consumed to help users assess whether refueling is necessary.

 @param fuelLevel A measurement representing the remaining fuel level using @c NSUnitVolume. Common units:
        - @c NSUnitVolume.liters for gasoline/diesel (metric regions)
        - @c NSUnitVolume.gallons for gasoline/diesel (US)
        - @c NSUnitVolume.imperialGallons for gasoline/diesel (UK)
 @return A new @c CPRouteDetail instance representing the fuel level

 @note For vehicles with alternative fuel types like compressed natural gas or hydrogen, consider using
       @c routeDetailWithFuelMass: or @c routeDetailWithFuelEnergy: as appropriate for the
       fuel measurement standard.
 */
+ (instancetype)routeDetailWithFuelLevel:(NSMeasurement<NSUnitVolume *> *)fuelLevel;

/**
 Creates additional route information for fuel energy content.

 Use this method to display fuel levels for hydrogen fuel cell vehicles or other vehicles where
 fuel is measured in energy units rather than volume or mass.

 @discussion Hydrogen fuel cell vehicles often express fuel capacity in kilowatt-hours of energy
 content. The system formats this appropriately for user display.

 @param fuelEnergy A measurement representing the fuel energy using @c NSUnitEnergy. Common units:
        - @c NSUnitEnergy.kilowattHours for hydrogen fuel cells
        - @c NSUnitEnergy.megajoules for alternative energy measurements
 @return A new @c CPRouteDetail instance representing the fuel energy

 @note This method is distinct from battery energy (@c routeDetailWithKilowattHours:) and should
       be used specifically for fuel-based energy storage systems.
 */
+ (instancetype)routeDetailWithFuelEnergy:(NSMeasurement<NSUnitEnergy *> *)fuelEnergy;

/**
 Creates additional route information for fuel mass.

 Use this method to display fuel levels for vehicles that measure fuel by mass, such as compressed
 natural gas (CNG) vehicles.

 @discussion CNG and similar compressed gas systems often measure fuel in mass units rather than
 volume due to the variable density under pressure. The system formats the mass measurement
 according to the user's preferred units.

 @param fuelMass A measurement representing the fuel mass using @c NSUnitMass. Common units:
        - @c NSUnitMass.kilograms for compressed natural gas
        - @c NSUnitMass.pounds for CNG in regions using imperial units
 @return A new @c CPRouteDetail instance representing the fuel mass
 */
+ (instancetype)routeDetailWithFuelMass:(NSMeasurement<NSUnitMass *> *)fuelMass;

/**
 Creates additional route information for battery percentage.

 Use this method to display the estimated battery level upon arrival at the destination for
 electric vehicles. Display as a percentage (0.0 to 100.0) to show state of charge.

 @discussion Percentage-based battery display is familiar to most users and provides an intuitive
 understanding of remaining range. The system formats this as a percentage with appropriate visual
 indicators. Values are clamped to the 0.0-100.0 range if necessary.

 @param batteryLevel The battery level as a percentage from 0.0 (empty) to 100.0 (full). Values
        outside this range will be clamped.
 @return A new @c CPRouteDetail instance representing the battery level

 @note For more technical users or when absolute capacity is more relevant, consider using
       @c routeDetailWithKilowattHours: to show energy in kilowatt-hours instead.
 */
+ (instancetype)routeDetailWithBatteryLevel:(double)batteryLevel;

/**
 Creates additional route information for battery energy in kilowatt-hours.

 Use this method to display battery levels for electric vehicles using absolute energy measurements
 rather than percentages. This provides more meaningful information for users familiar with their
 vehicle's battery capacity.

 @discussion Displaying battery in kilowatt-hours helps users better understand range and charging
 needs, particularly for long trips or when comparing vehicles with different battery capacities.
 A 10% battery in a 100 kWh vehicle (10 kWh) provides very different range than 10% in a 40 kWh
 vehicle (4 kWh).

 @param kilowattHours A measurement of battery energy using @c NSUnitEnergy.kilowattHours
 @return A new @c CPRouteDetail instance representing the battery energy

 @note Most electric vehicles use kilowatt-hours as the standard unit for battery capacity. The
       system automatically formats this with the "kWh" abbreviation.
 */
+ (instancetype)routeDetailWithKilowattHours:(NSMeasurement<NSUnitEnergy *> *)kilowattHours;

/**
 Creates additional route information for carbon footprint.

 Use this method to display the estimated carbon emissions for the route. This helps
 environmentally-conscious users evaluate and compare the environmental impact of different
 route options.

 @discussion The system formats the measurement with appropriate units and precision. Measurements
 in grams display with the 'g' suffix, while measurements in kilograms use 'kg'. The measurement
 is automatically formatted as CO₂ in the UI (e.g., "2.5 kg CO₂"). The system may round values
 for display clarity.

 @param carbonFootprint A measurement of carbon emissions using @c NSUnitMass. Typical units include:
        - @c NSUnitMass.grams for small emissions (e.g., short trips, efficient vehicles)
        - @c NSUnitMass.kilograms for larger emissions (e.g., long journeys, less efficient vehicles)
 @return A new @c CPRouteDetail instance representing the carbon footprint

 @note Apps should calculate carbon footprint based on vehicle type, fuel efficiency, route distance,
       terrain, and traffic conditions. Electric vehicles may show reduced or zero emissions compared
       to combustion vehicles, depending on the regional electricity generation mix. Consider
       providing methodology information in your app's settings or help documentation.
 */
+ (instancetype)routeDetailWithCarbonFootprint:(NSMeasurement<NSUnitMass *> *)carbonFootprint;

/**
 Creates additional route information for an eco-score rating.

 Use this method to display a normalized environmental efficiency score for the route. The score
 should be a value between 0.0 and 100.0, where higher values indicate more environmentally
 friendly routing options.

 @discussion The eco-score can incorporate multiple factors including carbon emissions, fuel
 efficiency, traffic congestion impact, terrain characteristics, and route optimization. The system
 displays this as a percentage-like value with appropriate visual indicators. Use consistent
 calculation methodology across all routes to enable meaningful comparison.

 @param value The eco-score rating from 0.0 to 100.0. Values outside this range will be clamped.
        Higher scores indicate more environmentally friendly routes.
 @return A new @c CPRouteDetail instance representing the eco-score

 @note The interpretation and calculation methodology of eco-scores may vary by app. Consider
       documenting your scoring algorithm in your app's help or settings, and ensure the score
       remains consistent across app updates to maintain user trust and understanding.
 */
+ (instancetype)routeDetailWithEcoScore:(double)value;

/**
 Creates additional route information for emissions data.

 Use this method to display estimated emissions for the route. This differs from carbon footprint
 by potentially including other pollutants beyond CO₂, or representing total emissions using
 different measurement approaches.

 @discussion This method provides flexibility for apps that want to display emissions data differently
 than the standard carbon footprint calculation. Use cases include displaying other greenhouse gases
 (methane, nitrous oxide), air pollutants (NOx, particulate matter), or alternative carbon accounting
 methodologies. Unlike @c carbonFootprint, this method does not automatically append "CO₂" to the
 display value, giving you control over how emissions are labeled.

 @param emissions A measurement of emissions using @c NSUnitMass. The system formats with appropriate
        units and precision. Common units include:
        - @c NSUnitMass.grams for small emissions quantities
        - @c NSUnitMass.kilograms for standard emissions display
        - @c NSUnitMass.milligrams for particulate matter or trace pollutants
 @return A new @c CPRouteDetail instance representing emissions

 @note Consider using @c routeDetailWithCarbonFootprint: for standard CO₂ measurements, as it
       provides optimized formatting with the CO₂ label. Reserve this method for comprehensive
       emissions reporting or alternative pollutant measurements where the generic "emissions" label
       is more appropriate.
 */
+ (instancetype)routeDetailWithEmissions:(NSMeasurement<NSUnitMass *> *)emissions;


/**
 Creates additional route information for a route rating.

 Use this method to display a user-generated or quality rating for the route. The rating can
 represent various quality metrics such as road conditions, scenic value, or overall route quality.

 @discussion Route ratings help users select routes based on quality assessments beyond just time
 and distance. The system displays this as a rating value with appropriate visual indicators.
 Values are clamped to the 0.0-5.0 range to match common rating systems.

 @param rating The route rating from 0.0 to 5.0. Values outside this range will be clamped.
        Higher ratings indicate better quality routes.
 @return A new @c CPRouteDetail instance representing the route rating

 @note Rating methodologies may vary by app. Consider providing information about what the rating
       represents (e.g., road quality, scenic views, user reviews) in your app's documentation.
 */
+ (instancetype)routeDetailWithRating:(double)rating;

/**
 Creates additional route information for High-Occupancy Vehicle (HOV) lane access.

 Use this method to display information about HOV lane eligibility and requirements for the route.
 This helps users understand whether they can use faster HOV lanes based on vehicle occupancy.

 @discussion HOV information is valuable for users planning carpools or understanding time savings
 from using HOV lanes. Display requirements such as minimum passenger count or time restrictions.

 @return A new @c CPRouteDetail instance representing HOV lane information

 @note Ensure HOV information is accurate for the specific route and time of day, as restrictions
       often vary by time and location.
 */
+ (instancetype)routeDetailWithHOV:(NSString *)hovInfo;

/**
 Creates additional route information for the number of traffic lights along the route.

 Use this method to display the count of traffic signals that will be encountered along the route.
 This helps users understand potential stop-and-go traffic patterns and estimate realistic travel time.

 @discussion Traffic light count provides valuable context for route selection, especially in urban
 areas where signal timing can significantly impact travel time. Routes with fewer traffic lights
 may offer smoother travel despite similar distances.

 @param trafficLights The number of traffic lights along the route. Common values range from 0 to 50+
        for typical urban routes.
 @return A new @c CPRouteDetail instance representing the traffic light count

 @note The count should include all signalized intersections where the route requires stopping or
       yielding. Consider excluding traffic lights on cross streets that don't affect the route.
       This information pairs well with travel time estimates to help users understand route flow.
 */
+ (instancetype)routeDetailWithTrafficLights:(NSUInteger)trafficLights;

/**
 Creates additional route information for route warnings.

 Use this method to display important warnings or alerts about conditions along the route. This
 helps users prepare for challenging or hazardous conditions they may encounter.

 @discussion Warnings draw attention to significant issues that may affect route safety or
 accessibility. Use this for critical information that users should be aware of before selecting
 a route.

 @return A new @c CPRouteDetail instance representing a route warning

 @note Reserve warnings for significant conditions. Use the tintColor property to set an
       appropriate color (such as red or orange) to ensure warnings are visually prominent.
       Consider localizing warning messages for international users.
 */
+ (instancetype)routeDetailWithWarning:(NSString *)warning;

/**
 Creates additional route information with a freeform informational string.

 Use this method to display a short piece of general information about the route that does not
 fit any of the predefined route detail categories.

 @discussion Info strings should be concise and localized. The system displays this alongside
 other route details during route selection and active navigation.

 @param info A localized string containing the information to display. Must not be nil.
 @return A new @c CPRouteDetail instance representing the informational text.
 */
+ (instancetype)routeDetailWithInfo:(NSString *)info;

/**
 Creates additional route information describing parking at the destination.

 Use this method to surface parking-related details (availability, estimated cost, distance
 to destination) so users can factor parking into their route selection.

 @discussion Parking information is displayed alongside other route details. Keep the string
 concise and localized so it reads clearly in the available space.

 @param parking A localized string describing parking at the destination. Must not be nil.
 @return A new @c CPRouteDetail instance representing the parking information.
 */
+ (instancetype)routeDetailWithParking:(NSString *)parking;

/**
 Creates custom additional route information with a symbol name and value.

 Use this method to display app-specific route information that doesn't fit the predefined
 categories. You provide a custom SF Symbol name and a formatted string value that will be
 displayed together.

 @discussion Custom route information provides flexibility for specialized use cases not covered
 by predefined types. However, the system may not display custom items in as many contexts as
 predefined information types (toll, fuel, battery, etc.), which receive optimized placement and
 visual treatment. Use custom information sparingly for truly unique routing characteristics.

 @param symbolName An SF Symbol name to display alongside the value. Choose simple, recognizable
        icons that clearly communicate the information type. Symbol images are rendered as templates
        and automatically adapt to the current appearance mode (light/dark). Must not be nil.
 @param value A pre-formatted string to display. The string should be concise and include any
        necessary units or symbols. The system does not perform additional formatting on custom
        values, so ensure proper localization and unit conversion in your app.
 @return A new @c CPRouteDetail instance with the custom symbol and value

 @note Custom route information should be used only when predefined types are insufficient. Consider
       whether your use case might be addressed by future additions to the framework. If you find
       yourself creating many custom information types, consider filing enhancement requests for
       new predefined types that would benefit other developers.
 */
+ (instancetype)routeDetailWithSymbolName:(NSString *)symbolName value:(NSString *)value;

/**
 The symbolTintColor to apply to the label.

 The system requires a dynamic color that adapts to appearance changes. Static colors without
 light and dark variants fall back to the system default label color. Alpha components are
 ignored and all colors render at full opacity.

 @seealso Use @c +[UIColor colorWithDynamicProvider:] or asset catalog colors to create
 dynamic colors that adapt to light and dark appearances.
 */
@property (nonatomic, strong, nullable) UIColor *symbolTintColor;

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
