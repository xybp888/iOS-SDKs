//
//  CPLocation.h
//  CarPlay
//
//  Copyright © 2024 Apple Inc. All rights reserved.

#import <Foundation/Foundation.h>
#import <CoreLocation/CLLocation.h>

NS_ASSUME_NONNULL_BEGIN

/**
 CPLocationCoordinate3D represents a three-dimensional coordinate with latitude, longitude, and altitude components.
 */
typedef struct {
    /**
     latitude is the coordinate's latitude value in degrees.
     */
    CLLocationDegrees latitude;

    /**
     longitude is the coordinate's longitude value in degrees.
     */
    CLLocationDegrees longitude;
    
    /**
     altitude is the coordinate's elevation above sea level in meters. If no altitude is available, use CLLocationDistanceMax.
     */
    CLLocationDistance altitude;
} CPLocationCoordinate3D API_AVAILABLE(ios(26.4)) API_UNAVAILABLE(tvos) API_UNAVAILABLE(macos, watchos);

NS_ASSUME_NONNULL_END
