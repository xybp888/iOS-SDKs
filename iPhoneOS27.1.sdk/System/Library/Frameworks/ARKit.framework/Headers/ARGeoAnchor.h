#if (defined(USE_ARKIT_PUBLIC_HEADERS) && USE_ARKIT_PUBLIC_HEADERS) || !__has_include(<ARKitCore/ARGeoAnchor.h>)
//
//  ARGeoAnchor.h
//  ARKit
//
//  Copyright © 2016-2021 Apple Inc. All rights reserved.
//

#import <ARKit/ARAnchor.h>
#import <ARKit/ARGeoTrackingTypes.h>
#import <CoreLocation/CoreLocation.h>

NS_ASSUME_NONNULL_BEGIN

API_UNAVAILABLE_BEGIN(visionos)

/**
 An anchor representing a geographical location in the world.

 The anchor's transform will be automatically updated by the session based on location and heading.
 The session needs to be configured with ARGeoTrackingConfiguration.
*/
API_AVAILABLE(ios(14.0))
NS_SWIFT_SENDABLE
@interface ARGeoAnchor : ARAnchor <ARTrackable>

/**
 The coordinate where this anchor will be placed.

 The anchor's transform will be automatically updated by the session when `ARGeoTrackingConfiguration` is set.
*/
@property (nonatomic, readonly) CLLocationCoordinate2D coordinate;

/**
 The distance to mean sea level, in meters (negative values indicate it's below sea level).

 Only valid when `altitudeSource` is not `ARAltitudeSourceUnknown`.
*/
@property (nonatomic, readonly) CLLocationDistance altitude NS_REFINED_FOR_SWIFT;

/**
 The source of altitude information. If the user did not provide the altitude, ARKit populates this property to indicate the expected accuracy
 depending on the available altitude data.
 */
@property (nonatomic, readonly) ARAltitudeSource altitudeSource;

/**
 Initializes a new ARGeoAnchor with the given coordinates.

 ARKit will query the ground level altitude during runtime, and populate the altitude as soon as that information becomes available.

 - Parameter coordinate: The coordinates.

 - Returns: An initialized geo anchor.
*/
- (instancetype)initWithCoordinate:(CLLocationCoordinate2D)coordinate NS_REFINED_FOR_SWIFT;

/**
 Initializes a new ARGeoAnchor with the given coordinates and altitude.

 - Parameters:
   - coordinate: The coordinates.
   - altitude: Altitude in meters.

 - Returns: An initialized geo anchor.
*/
- (instancetype)initWithCoordinate:(CLLocationCoordinate2D)coordinate altitude:(CLLocationDistance)altitude NS_REFINED_FOR_SWIFT;

/**
 Initializes a new named ARGeoAnchor with the given coordinates.

 ARKit will query the ground level altitude during runtime, and populate the altitude as soon as that information becomes available.

 - Parameters:
   - name: Name of the anchor.
   - coordinate: The coordinates.

 - Returns: An initialized geo anchor.
*/
- (instancetype)initWithName:(NSString *)name coordinate:(CLLocationCoordinate2D)coordinate NS_REFINED_FOR_SWIFT API_UNAVAILABLE(visionos);

/**
 Initializes a new named ARGeoAnchor with the given coordinates and altitude.

 - Parameters:
   - name: Name of the anchor.
   - coordinate: The coordinates.
   - altitude: Altitude in meters.

 - Returns: An initialized geo anchor.
*/
- (instancetype)initWithName:(NSString *)name
                  coordinate:(CLLocationCoordinate2D)coordinate
                    altitude:(CLLocationDistance)altitude API_UNAVAILABLE(visionos);

/**
 Unavailable.

 - Parameter transform: The transformation matrix.

 - Returns: This method is unavailable.
*/
- (instancetype)initWithTransform:(simd_float4x4)transform NS_UNAVAILABLE;

/**
 Unavailable.

 - Parameters:
   - name: The anchor name.
   - transform: The transformation matrix.

 - Returns: This method is unavailable.
*/
- (instancetype)initWithName:(NSString *)name transform:(simd_float4x4)transform NS_UNAVAILABLE;

@end

API_UNAVAILABLE_END

NS_ASSUME_NONNULL_END

#else
#import <ARKitCore/ARGeoAnchor.h> 
#endif // #if (defined(USE_ARKIT_PUBLIC_HEADERS) \&\& USE_ARKIT_PUBLIC_HEADERS) || !__has_include(<ARKitCore/ARGeoAnchor.h>)