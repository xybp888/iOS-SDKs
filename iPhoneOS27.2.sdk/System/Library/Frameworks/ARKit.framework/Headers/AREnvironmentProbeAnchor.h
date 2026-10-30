#if (defined(USE_ARKIT_PUBLIC_HEADERS) && USE_ARKIT_PUBLIC_HEADERS) || !__has_include(<ARKitCore/AREnvironmentProbeAnchor.h>)
//
//  AREnvironmentProbeAnchor.h
//  ARKit
//
//  Copyright © 2018 Apple Inc. All rights reserved.
//

#import <ARKit/ARAnchor.h>

@protocol MTLTexture;

NS_ASSUME_NONNULL_BEGIN

API_UNAVAILABLE_BEGIN(visionos)

/**
 An object that provides environmental lighting information for a specific area of space in a world-tracking AR session.

 Environment textures depict the view in all directions from a specific point in a scene. In 3D asset rendering, environment textures are the basis
 for image-based lighting algorithms where surfaces can realistically reflect light from their surroundings. ARKit can generate environment textures
 during an AR session using camera imagery, allowing SceneKit or a custom-rendering engine to provide realistic image-based lighting for virtual
 objects in your AR experience.

 To enable texture map generation for an AR session, set the ``ARWorldTrackingConfiguration/environmentTexturing`` property:

 - With ``ARWorldTrackingConfiguration/EnvironmentTexturing/manual`` environment texturing, you identify points in the scene for which you want light
 probe texture maps by creating ``AREnvironmentProbeAnchor`` objects and adding them to the session.
 - With ``ARWorldTrackingConfiguration/EnvironmentTexturing/automatic`` environment texturing, ARKit automatically creates, positions, and adds
 ``AREnvironmentProbeAnchor`` objects to the session.

 In both cases, ARKit automatically generates environment textures as the session collects camera imagery. Use a delegate method such as
 ``ARSessionDelegate/session(_:didUpdate:)-3qtt8`` to find out when a texture is available, and access it from the anchor's ``environmentTexture``
 property.

 If you display AR content using ``ARSCNView`` and the ``ARSCNView/automaticallyUpdatesLighting`` option, SceneKit automatically retrieves
 ``AREnvironmentProbeAnchor`` texture maps and uses them to light the scene.
*/
API_AVAILABLE(ios(12.0))
NS_SWIFT_SENDABLE
@interface AREnvironmentProbeAnchor : ARAnchor

/**
 A cube-map texture that represents the view in all directions from the probe anchor's position.

 This texture is in the format <doc://com.apple.documentation/documentation/metal/mtlpixelformat/bgra8unorm_srgb>.
*/
@property (nonatomic, strong, nullable, readonly) id<MTLTexture> environmentTexture;

/**
 The area around the anchor's position that contains the texture.

 Rendering reflective objects may involve projecting the ``AREnvironmentProbeAnchor/environmentTexture`` onto a proxy geometry centered on the
 anchor's position, then sampling from the projected texture.

 An environment probe anchor may have an infinite extent, which indicates that its texture is a global lighting environment, or a finite extent, which
 indicates that its texture represents the local lighting conditions in a specific area of the scene.
*/
@property (nonatomic, readonly) simd_float3 extent;

/**
 Creates a new environment probe anchor.

 - Parameters:
   - transform: A matrix that encodes the position, orientation, and scale of the anchor, relative to the world coordinate space of the AR session in
 which you place the anchor.

     World coordinate space in ARKit always follows a right-handed convention, but is oriented based on the session configuration. For details, see
 <doc:understanding-world-tracking>.
   - extent: The area around the anchor's position that contains the texture.

 Use the ``ARSession/add(anchor:)`` method to begin tracking your custom anchor in an AR session. After you add an environment probe anchor to the
 scene, ARKit begins generating environment textures for it. To be notified when the anchor has a new ``AREnvironmentProbeAnchor/environmentTexture``,
 implement the ``ARSessionDelegate/session(_:didUpdate:)-3qtt8``, ``ARSCNViewDelegate/renderer(_:didUpdate:for:)``, or
 ``ARSKViewDelegate/view(_:didUpdate:for:)`` delegate method.
*/
- (instancetype)initWithTransform:(simd_float4x4)transform extent:(simd_float3)extent;

/**
 Creates a new anchor object with a descriptive name.

 - Parameters:
   - name: A descriptive name for the anchor. ARKit doesn't display the name to users, but your app can use it to identify anchors for debugging.
   - transform: A matrix that encodes the position, orientation, and scale of the anchor, relative to the world coordinate space of the AR session in
 which you place the anchor.

     World coordinate space in ARKit always follows a right-handed convention, but is oriented based on the session configuration. For details, see
 <doc:understanding-world-tracking>.
   - extent: The area around the anchor's position that contains the texture.

     An environment probe anchor may have an infinite extent, which indicates that its texture is a global lighting environment, or a finite extent,
 which indicates that its texture represents the local lighting conditions in a specific area of the scene.

 Use the ``ARSession/add(anchor:)`` method to begin tracking your custom anchor in an AR session. After you add an environment probe anchor to the
 scene, ARKit begins generating environment textures for it. To be notified when the anchor has a new ``AREnvironmentProbeAnchor/environmentTexture``,
 implement the ``ARSessionDelegate/session(_:didUpdate:)-3qtt8``, ``ARSCNViewDelegate/renderer(_:didUpdate:for:)``, or
 ``ARSKViewDelegate/view(_:didUpdate:for:)`` delegate method.
*/
- (instancetype)initWithName:(NSString *)name transform:(simd_float4x4)transform extent:(simd_float3)extent API_UNAVAILABLE(visionos);

@end

API_UNAVAILABLE_END

NS_ASSUME_NONNULL_END
#else
#import <ARKitCore/AREnvironmentProbeAnchor.h> 
#endif // #if (defined(USE_ARKIT_PUBLIC_HEADERS) \&\& USE_ARKIT_PUBLIC_HEADERS) || !__has_include(<ARKitCore/AREnvironmentProbeAnchor.h>)