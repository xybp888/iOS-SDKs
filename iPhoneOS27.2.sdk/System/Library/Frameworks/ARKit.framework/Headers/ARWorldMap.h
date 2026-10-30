#if (defined(USE_ARKIT_PUBLIC_HEADERS) && USE_ARKIT_PUBLIC_HEADERS) || !__has_include(<ARKitCore/ARWorldMap.h>)
//
//  ARWorldMap.h
//  ARKit
//
//  Copyright © 2018 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <simd/simd.h>

@class ARAnchor;
@class ARPointCloud;

NS_ASSUME_NONNULL_BEGIN

API_UNAVAILABLE_BEGIN(visionos)

/**
 The space-mapping state and set of anchors from a world-tracking AR session.

 The session state in a world map includes ARKit's awareness of the physical space in which the user moves the device. ARKit uses the details of the
 user's physical space to determine the device's position and orientation, as well as any ``ARAnchor`` objects added to the session that can represent
 detected real-world features or virtual content placed by your app.

 `ARWorldMap` supports archiving and unarchiving across devices and versions with `NSDecodingFailurePolicySetErrorAndReturn`, providing an error if
 the map format is not supported.

 ### Serialize and Deserialize a World Map

 When your app quits, you can save the current world map (acquired using ``ARSession/getCurrentWorldMap(completionHandler:)``). Because ``ARWorldMap``
 conforms to <doc://com.apple.documentation/documentation/foundation/nssecurecoding>, you serialize it using
 <doc://com.apple.documentation/documentation/foundation/nskeyedarchiver>.

 ```swift
 func writeWorldMap(_ worldMap: ARWorldMap, to url: URL) throws {
     let data = try NSKeyedArchiver.archivedData(withRootObject: worldMap, requiringSecureCoding: true)
     try data.write(to: url)
 }
 ```

 To restore the world map the next time your app launches, use <doc://com.apple.documentation/documentation/foundation/nskeyedunarchiver>.

 ```swift
 func loadWorldMap(from url: URL) throws -> ARWorldMap {
     let mapData = try Data(contentsOf: url)
     guard let worldMap = try NSKeyedUnarchiver.unarchivedObject(ofClass: ARWorldMap.self, from: mapData)
         else { throw ARError(.invalidWorldMap) }
     return worldMap
 }
 ```

 You can use anchors from a resumed world map to place the same virtual content at the same positions from the saved session, if the app launches in
 the same physical environment.

 For more information, see <doc:saving-and-loading-world-data>.

 ### Share a Saved World Map

 With two devices tracking the same world map, you can build a networked experience in which both users can see and interact with the same virtual
 content. To send an ``ARWorldMap`` to another device:

 1. On one device, use <doc://com.apple.documentation/documentation/foundation/nskeyedarchiver> to convert the world map to a data object. You don't
 need to write the data to a file to send it over the network.
 2. Use the networking technology of your choice to send the resulting data to another device. For example, in a
 <doc://com.apple.documentation/documentation/multipeerconnectivity> session, call
 <doc://com.apple.documentation/documentation/multipeerconnectivity/mcsession/send(_:topeers:with:)> to send data, and implement
 <doc://com.apple.documentation/documentation/multipeerconnectivity/mcsessiondelegate> methods on the other device to receive data.
 3. On the receiving device, use <doc://com.apple.documentation/documentation/foundation/nskeyedunarchiver> to instantiate an ``ARWorldMap`` from the
 data.

 For more information, see <doc:creating-a-multiuser-ar-experience>.

 ### Run a Deserialized World Map

 To begin a new session from an existing ``ARWorldMap``, set a world-tracking configuration's ``ARWorldTrackingConfiguration/initialWorldMap``
 property and use ``ARSession/run(_:options:)``. This starts a new session using the same spatial awareness and anchors loaded from the saved world
 map.
*/
API_AVAILABLE(ios(12.0))
@interface ARWorldMap : NSObject <NSCopying, NSSecureCoding>

/**
 The center point of the world map's space-mapping data, in meters, relative to the world coordinate origin of the session the map was recorded in.

 The ``ARWorldMap/extent`` and ``ARWorldMap/center`` properties together define a bounding box for the data recorded in the world map.
 */
@property (nonatomic, readonly) simd_float3 center;

/**
 The size of the world map's space-mapping data, in meters, relative to the world coordinate origin of the session the map was recorded in.

 The ``ARWorldMap/extent`` and ``ARWorldMap/center`` properties together define a bounding box for the data recorded in the world map.
 */
@property (nonatomic, readonly) simd_float3 extent;

/**
 The set of anchors recorded in the world map.

 This array is a snapshot of ``ARAnchor`` objects (including subclasses of ``ARAnchor``) in the session as of when the world map was captured,
 including the ``ARAnchor/transform`` for each. When you create a world map, ARKit automatically includes all anchors whose positions are assumed to
 be static with respect to the environment—that is, anchor classes that don't conform to ``ARTrackable``. After you create a world map, you can choose
 to add more anchors to, or remove anchors from, this list before saving or sharing the map.

 When you run a session from a world map (and after ARKit successfully reconciles the map to the user's current environment), the session
 automatically includes all anchors from that world map. You can then use those anchors to recreate the placement of virtual content so that it
 matches the session the world map was captured in.
 */
@property (nonatomic, copy) NSArray<__kindof ARAnchor *> *anchors;

/**
 A coarse representation of the space-mapping data recorded in the world map.

 These points represent notable features detected in camera imagery during the session that recorded the world map. ARKit extrapolates the locations
 of these features in 3D world coordinate space as part of the image and motion analysis that tracks the device's movement in a session. Taken
 together, these points loosely correlate to the contours of real-world objects that were in view of the camera during the session.

 ARKit does not guarantee that the number and arrangement of raw feature points will remain stable between software releases. However, you can
 visualize the point cloud to debug your world map recording, or inspect its size to estimate the quality of a recorded world map.
 */
@property (nonatomic, strong, readonly) ARPointCloud *rawFeaturePoints;

/**
 Unavailable.

 - Returns: This method is unavailable.
*/
- (instancetype)init NS_UNAVAILABLE;

/**
 Unavailable.

 - Returns: This method is unavailable.
*/
+ (instancetype)new NS_UNAVAILABLE;

@end

API_UNAVAILABLE_END

NS_ASSUME_NONNULL_END
#else
#import <ARKitCore/ARWorldMap.h> 
#endif // #if (defined(USE_ARKIT_PUBLIC_HEADERS) \&\& USE_ARKIT_PUBLIC_HEADERS) || !__has_include(<ARKitCore/ARWorldMap.h>)