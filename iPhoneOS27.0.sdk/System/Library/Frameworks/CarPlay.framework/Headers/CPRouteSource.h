//  CPRouteSource.h
//  CarPlayFrameworks
//
//  Copyright © 2025 Apple Inc. All rights reserved.
//

/**
 * @enum CPRouteSource
 * @brief Specifies the destination and modification status of route information displayed to the user
 */
API_AVAILABLE(ios(26.4)) API_UNAVAILABLE(tvos) API_UNAVAILABLE(macos, watchos) NS_SWIFT_SENDABLE
typedef NS_ENUM(NSUInteger, CPRouteSource)
{
    /**
     * No current route source.
     */
    CPRouteSourceInactive = 0,
    
    /**
     * Route is from the device and being used by the vehicle unmodified.
     */
    CPRouteSourceiOSUnchanged = 1,
    
    /**
     * Route is from the device and being used by the vehicle but has been modified. The destination(s)/waypoints have not been changed.
     */
    CPRouteSourceiOSRouteModified = 2,
    
    /**
     * Route and destination(s) from the device are being used but both have been modified.
     */
    CPRouteSourceiOSRouteDestinationsModified = 3,
    
    /**
     * Only the destination(s) from the device are being used, routes are not.
     */
    CPRouteSourceiOSDestinationsOnly = 4,
    
    /**
     *  Route and destination(s) being used by the vehicle is from the vehicle’s system.
     */
    CPRouteSourceVehicle = 5
};
