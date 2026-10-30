#if (defined(USE_ARKIT_PUBLIC_HEADERS) && USE_ARKIT_PUBLIC_HEADERS) || !__has_include(<ARKitCore/ARAnchor.h>)
//
//  ARAnchor.h
//  ARKit
//
//  Copyright © 2016-2021 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <simd/simd.h>

NS_ASSUME_NONNULL_BEGIN

API_UNAVAILABLE_BEGIN(visionos)

@class ARAnchor;
/**
 Support for custom anchor subclasses.

 An ``ARAnchor`` (or an instance of any anchor subclass) represents a position and orientation in world space, and optionally associates extra
 information with that point (like a name, or plane or image detection data). Each time ARKit generates an ``ARFrame`` object (describing the current
 environment as of a specific frame of live camera video), ARKit updates the ``ARFrame/anchors`` associated with the session as of that moment.
 Because anchor objects are immutable, ARKit must copy them to make changes from one ``ARFrame`` to the next.

 If you create your own ARAnchor subclass, you must implement the ``init(anchor:)`` initializer required by this protocol. To ensure that any custom
 information in your subclass is maintained between successive frames, your implementation should copy any custom properties it declares.
 */
API_AVAILABLE(ios(12.0))
@protocol ARAnchorCopying <NSCopying>

/**
 Initializes a new anchor by copying custom information from another anchor.

 Each time ARKit generates a new ``ARFrame`` object (corresponding to an incoming frame of live camera video at 60 fps), ARKit calls this initializer
 to copy each of the ``ARFrame/anchors`` associated with the previous frame.

 > Note:
 > ARKit always calls this initializer with an `anchor` parameter of the same class as `self`.

 If you subclass ``ARAnchor`` to add extra properties, your implementation of this initializer should copy the values of those properties, then chain
 to the superclass initializer. For example, an AR game might define a `BoardAnchor` class to encode the position and size of a game board, so its
 version of this initializer would copy that `size` property:

 ```swift
 required init(anchor: ARAnchor) {
     let other = anchor as! BoardAnchor
     self.size = other.size
     super.init(anchor: other)
 }
 ```

 > Important:
 > Carefully consider performance and your app's data model when storing references to other objects in anchors. Copying custom values might be
 expensive, but multiple references to the same data might or might not be correct for your app.

 - Parameter anchor: The other anchor from which to copy information.
*/
- (instancetype)initWithAnchor:(ARAnchor *)anchor;

@end

/**
 An interface for objects that track the location of real-world objects or locations.

 This protocol is adopted by ARKit classes, such as the ``ARFaceAnchor`` class, that represent moving objects in a scene.

 ARKit automatically manages representations of such objects in an active AR session, ensuring that changes in the real-world object's position and
 orientation (the ``ARAnchor/transform`` property for anchors) are reflected in corresponding ARKit objects. The ``isTracked`` property indicates
 whether the current transform is valid with respect to movement of the real-world object.

 Trackable anchor classes affect other ARKit behaviors:

 - The ``ARSession/getCurrentWorldMap(completionHandler:)`` method automatically includes only non-trackable anchors in the ``ARWorldMap`` it creates.
 (After you create a world map, you can add other anchors to it if you choose.)
 - ``ARSCNView`` and ``ARSKView`` automatically hide the nodes for anchors whose ``isTracked`` property is
 <doc://com.apple.documentation/documentation/swift/false>.
 - World-tracking sessions use non-trackable anchors to optimize tracking quality in the area around each anchor. Trackable anchors do not affect
 world tracking.
 */
API_AVAILABLE(ios(11.0))
@protocol ARTrackable <NSObject>

/**
 A Boolean value that indicates whether the object's transform is valid.

 If this value is <doc://com.apple.documentation/documentation/swift/true>, the object's transform currently matches the position and orientation of
 the real-world object it represents.

 If this value is <doc://com.apple.documentation/documentation/swift/false>, the object is not guaranteed to match the movement of its corresponding
 real-world feature, even if it remains in the visible scene. When the tracked object is no longer detected in the camera image, its anchor reports
 `NO` for `isTracked`.
*/
@property (nonatomic, readonly) BOOL isTracked;

@end

/**
 An object that specifies the position and orientation of an item in the physical environment.

 To track the static positions and orientations of real or virtual objects relative to the camera, create anchor objects and use the ``ARSession/add(anchor:)`` method to add them to your AR session.

 > Tip:
 > Adding an anchor to the session helps ARKit to optimize world-tracking accuracy in the area around that anchor, so that virtual objects appear to stay in place relative to the real world. If a virtual object moves, remove the corresponding anchor from the old position and add one at the new position.

 Some ARKit features automatically add special anchors to a session. World-tracking sessions can add ``ARPlaneAnchor``, ``ARObjectAnchor``, and ``ARImageAnchor`` objects if you enable the corresponding features; face-tracking sessions add ``ARFaceAnchor`` objects.

 ### Subclassing Notes

 In addition to creating your own `ARAnchor` instances to track the real-world positions of your virtual content, you can also subclass `ARAnchor` to associate custom data with anchors you create. Ensure that your anchor classes behave correctly when ARKit updates frames or saves and loads anchors in an ``ARWorldMap``:

 - Anchor subclasses must fulfill the requirements of the ``ARAnchorCopying`` protocol. ARKit calls ``ARAnchorCopying/init(anchor:)`` (on a background thread) to copy instances of your anchor class from each ``ARFrame`` to the next. Your implementation of this initializer should copy the values of any custom properties your subclass adds.
 - Anchor subclasses must also adopt the <doc://com.apple.documentation/documentation/foundation/nssecurecoding> protocol. Override <doc://com.apple.documentation/documentation/foundation/nscoding/encode(with:)> and <doc://com.apple.documentation/documentation/foundation/nscoding/init(coder:)> to save and restore the values of your subclass's custom properties when ARKit saves and loads them in a world map.
 - Anchors are considered equal based on their ``identifier`` property.
 - Only anchors that do not adopt ``ARTrackable`` are included when you save a world map.
 */
API_AVAILABLE(ios(11.0))
NS_SWIFT_SENDABLE
@interface ARAnchor : NSObject <ARAnchorCopying,
                                NSSecureCoding
                                >

/**
 A unique identifier for the anchor.

 Whether an anchor is created manually (with the ``ARAnchor/init(transform:)`` initializer) or automatically by ARKit (and provided to you through
 ``ARSessionDelegate``, ``ARSCNViewDelegate``, or ``ARSKViewDelegate`` methods), each anchor automatically receives a unique identifier value.

 You can use this value to determine which anchors accompanying a specific ``ARFrame`` capture correspond to anchors in frames captured previously.
 */
@property (nonatomic, readonly) NSUUID *identifier;

/**
 A descriptive name for the anchor.

 To name an anchor, create one with the ``ARAnchor/init(name:transform:)`` initializer. This property is `nil` for anchors created otherwise.

 ARKit does not display the name to users, but your app can use it to identify anchors for debugging.
 */
@property (nonatomic, nullable, readonly) NSString *name API_AVAILABLE(ios(12.0)) API_UNAVAILABLE(visionos);

/**
 The unique identifier of the session that owns this anchor.

 ARKit sets this property when a user first adds an anchor to a session. In multiuser experiences, use this ID to identify the user that created the
 anchor.
*/
@property (nonatomic, nullable, readonly) NSUUID *sessionIdentifier API_AVAILABLE(ios(13.0));

/**
 A matrix encoding the position, orientation, and scale of the anchor relative to the world coordinate space of the AR session the anchor is placed
 in.

 World coordinate space in ARKit always follows a right-handed convention, but is oriented based on the session configuration. For details, see
 <doc:understanding-world-tracking>.
 */
@property (nonatomic, readonly) simd_float4x4 transform;

/**
 Creates a new anchor object with the specified transform.

 Use the ``ARSession/add(anchor:)`` method to begin tracking your custom anchor in an AR session.

 - Parameter transform: A matrix encoding the position, orientation, and scale of the anchor relative to the world coordinate space of the AR session
 the anchor is placed in. World coordinate space in ARKit always follows a right-handed convention, but is oriented based on the session
 configuration. For details, see <doc:understanding-world-tracking>.
*/
- (instancetype)initWithTransform:(simd_float4x4)transform;

/**
 Creates a new anchor object with the specified transform and a descriptive name.

 Use the ``ARSession/add(anchor:)`` method to begin tracking your custom anchor in an AR session.

 - Parameters:
   - name: A descriptive name for the anchor. ARKit does not display the name to users, but your app can use it to identify anchors for debugging.
   - transform: A matrix encoding the position, orientation, and scale of the anchor relative to the world coordinate space of the AR session the
 anchor is placed in. World coordinate space in ARKit always follows a right-handed convention, but is oriented based on the session configuration.
 For details, see <doc:understanding-world-tracking>.
*/
- (instancetype)initWithName:(NSString *)name transform:(simd_float4x4)transform API_AVAILABLE(ios(12.0))API_UNAVAILABLE(visionos);

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
#import <ARKitCore/ARAnchor.h> 
#endif // #if (defined(USE_ARKIT_PUBLIC_HEADERS) \&\& USE_ARKIT_PUBLIC_HEADERS) || !__has_include(<ARKitCore/ARAnchor.h>)