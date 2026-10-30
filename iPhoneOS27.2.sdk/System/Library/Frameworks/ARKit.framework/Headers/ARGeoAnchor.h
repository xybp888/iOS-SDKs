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
 An anchor that identifies a geographic location using latitude, longitude, and altitude data.

 A _geographic anchor_ (also known as _location anchor_) identifies a specific area in the world that the app can refer to in an AR experience. As a
 user moves around the scene, the session updates a location anchor's ``ARAnchor/transform`` based on the anchor's ``coordinate`` and the device's
 compass heading.

 ARKit aligns location anchors to an East-North-Up orientation, with its x- and z-axes matching the longitude and latitude directions. For more
 information, see ``ARConfiguration/WorldAlignment/gravityAndHeading``.

 ARKit sets the anchor's vertical position to the altitude you pass in to ``initWithCoordinate:altitude:``. If you initialize a location anchor using
 ``initWithCoordinate:`` instead, ARKit sets the anchor's altitude to ground level.

 > Important:
 > Location anchors are available only in geotracking sessions, and geotracking is available in specific areas; for more information, see
 ``ARGeoTrackingConfiguration``.

 ### Communicate Data Usage

 Location anchors consume data from Apple Maps called _localization imagery_ (for more information, see ``ARGeoTrackingConfiguration``). As the user
 moves, the framework downloads localization imagery to refine the user's precise geographic position. The amount of data the session requires depends
 on the user's movement and distance they travel. To make the user aware of potential fees, you can notify the user of their data usage.

 ### Manage Location Anchor Availability

 When an app creates a location anchor, it's invisible to the user until the framework _populates_ the anchor in the scene. When an anchor populates
 successfully, the session passes the anchor into the delegate's ``ARSessionDelegate/session(_:didAdd:)`` callback.

 If ARKit fails to populate a location anchor, the session calls ``ARSessionDelegate/session(_:didRemove:)`` to notify your delegate. A location
 anchor may fail to populate when:

 - The network is unavailable. If you create a location anchor without providing an altitude, ARKit defaults the altitude to ground level, and may
 query the server to check the topography at the anchor's geographic coordinate. If the network is unavailable, ask the user to restore a connection
 by disabling Airplane Mode, enabling WiFi, or moving to a location that provides service. If the network is available but slow, an altitude query
 response may be delayed. Consider pausing a navigation or presenting visual feedback for the anchor's tentative placement, such as by displaying a
 status indicator.
 - The location anchor is too far from the user. If users can create location anchors in your app, let them know to position the coordinates of each
 anchor within 0.05 degrees (~5 kilometers) of themselves and their device.
 - The server prevents the location anchor's position, such as in a large body of water.
*/
API_AVAILABLE(ios(14.0))
NS_SWIFT_SENDABLE
@interface ARGeoAnchor : ARAnchor <ARTrackable>

/**
 The latitude and longitude of the anchor's geographic location.

 This property is set by the app at anchor initialization. The anchor's transform will be automatically updated by the session when
 `ARGeoTrackingConfiguration` is set.
*/
@property (nonatomic, readonly) CLLocationCoordinate2D coordinate;

/**
 Vertical distance, in meters, between this anchor and sea level.

 Negative values indicate below sea level. This property is valid only when ``ARGeoAnchor/altitudeSource`` is a value other than
 ``ARGeoAnchor/AltitudeSource/unknown``.
*/
@property (nonatomic, readonly) CLLocationDistance altitude NS_REFINED_FOR_SWIFT;

/**
 A record of the source from which an altitude came.

 The value of this property is ``ARGeoAnchor/AltitudeSource/userDefined`` if you set the altitude yourself (see
 ``ARSession/getGeoLocation(forPoint:completionHandler:)``).

 If your app doesn't set the altitude, ARKit populates this property to indicate the altitude's expected accuracy (either
 ``ARGeoAnchor/AltitudeSource/precise``, or ``ARGeoAnchor/AltitudeSource/coarse``), depending on the level of confidence ARKit has with the altitude
 data that's available at the time.
 */
@property (nonatomic, readonly) ARAltitudeSource altitudeSource;

/**
 Initializes a new location anchor with the given coordinates.

 Because this initializer does not take an altitude argument, ARKit sets the anchor's ``altitude`` to ground level.

 - Parameter coordinate: Latitude and longitude of the anchor's geographic location.
*/
- (instancetype)initWithCoordinate:(CLLocationCoordinate2D)coordinate NS_REFINED_FOR_SWIFT;

/**
 Initializes a location anchor with the given coordinate and altitude.

 - Parameters:
   - coordinate: Latitude and longitude of the anchor's geographic location.
   - altitude: Vertical distance, in meters, between this anchor and sea level.
*/
- (instancetype)initWithCoordinate:(CLLocationCoordinate2D)coordinate altitude:(CLLocationDistance)altitude NS_REFINED_FOR_SWIFT;

/**
 Initializes a named location anchor with the given coordinates.

 Because this initializer does not take an altitude argument, ARKit sets the anchor's ``altitude`` to ground level.

 - Parameters:
   - name: Name of the anchor.
   - coordinate: Latitude and longitude of the anchor's geographic location.
*/
- (instancetype)initWithName:(NSString *)name coordinate:(CLLocationCoordinate2D)coordinate NS_REFINED_FOR_SWIFT API_UNAVAILABLE(visionos);

/**
 Initializes a named location anchor with the given coordinate and altitude.

 - Parameters:
   - name: Name of the anchor.
   - coordinate: Latitude and longitude of the anchor's geographic location.
   - altitude: Vertical distance, in meters, between this anchor and sea level.
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