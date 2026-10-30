//
//  ARSCNView.h
//  ARKit
//
//  Copyright © 2016-2021 Apple Inc. All rights reserved.
//

#import <ARKitCore/ARHitTestResult.h>
#import <ARKitCore/ARSession.h>
#import <ARKitCore/ARTrackedRaycast.h>
#import <SceneKit/SceneKit.h>

API_UNAVAILABLE_BEGIN(visionos)

@protocol ARSCNViewDelegate;

NS_ASSUME_NONNULL_BEGIN

/**
 A view that blends virtual 3D content from SceneKit into your augmented reality experience.

 > Important: SceneKit is deprecated, use <doc://com.apple.documentation/documentation/realitykit> instead.
 > For more information, see WWDC25 session 288: [Bring your SceneKit projects to RealityKit](https://developer.apple.com/videos/play/wwdc2025/288/).

 The `ARSCNView` class provides an easy way to create augmented reality experiences that blend virtual 3D content with a device camera view of the
 real world. When you run the view's provided ``ARSession`` object:

 - The view automatically renders the live video feed from the device camera as the scene background.
 - The world coordinate system of the view's SceneKit scene directly responds to the AR world coordinate system established by the session
 configuration.
 - The view automatically moves its SceneKit camera to match the real-world movement of the device.

 ARKit automatically matches SceneKit's coordinate space to the real world, so after you place your app's virtual content, it maintains the illusion
 of resting in the real-world as the user moves the device. See <doc:providing-3d-virtual-content-with-scenekit>.

 You don't necessarily need to use the ``ARAnchor`` class to track positions of objects you add to the scene, but by implementing
 ``ARSCNViewDelegate`` methods, you can add SceneKit content to any anchors that are automatically detected by ARKit.

 Because ARKit requires Metal, use only Metal features of SceneKit. For example:

 - This class supports only <doc://com.apple.documentation/documentation/scenekit/scnprogram> instances with Metal Shading Language code.
 - If you set the <doc://com.apple.documentation/documentation/scenekit/scnview/option/preferredrenderingapi> property to
 <doc://com.apple.documentation/documentation/scenekit/scnrenderingapi/opengles2>, the framework reverts the value to
 <doc://com.apple.documentation/documentation/scenekit/scnrenderingapi/metal>.
*/
API_AVAILABLE(ios(11.0))
API_DEPRECATED_WITH_REPLACEMENT("Please use RealityView instead.", visionos(1.0, 1.0))
@interface ARSCNView : SCNView <ARSessionProviding>

/**
 An object you provide to mediate synchronization of the view's AR scene information with SceneKit content.
 */
@property (nonatomic, weak, nullable) id<ARSCNViewDelegate> delegate;

/**
 The AR session that manages motion tracking and camera image processing for the view's contents.

 A view creates its own session object; use this property to access and configure the view's session.
 */
@property (nonatomic, strong) ARSession *session;

/**
 The SceneKit scene to be displayed in the view.

 > Note:
 > Unlike the parent <doc://com.apple.documentation/documentation/scenekit/scnview> class, an ``ARSCNView`` object requires a non-`nil` scene to
 display.
 */
@property (nonatomic, strong) SCNScene *scene;

/**
 A Boolean value that specifies whether ARKit creates and updates SceneKit lights in the view's scene.

 If this value is <doc://com.apple.documentation/documentation/swift/true> (the default), the view automatically creates one or more
 <doc://com.apple.documentation/documentation/scenekit/scnlight> objects, adds them to the scene, and updates their properties to reflect estimated
 lighting information from the camera scene. Set this value to <doc://com.apple.documentation/documentation/swift/false> if you want to directly
 control all lighting in the SceneKit scene.
*/
@property (nonatomic, assign) BOOL automaticallyUpdatesLighting;

/**
 A flag that determines whether SceneKit applies image noise characteristics to your app's virtual content.

 Enabled by default. When set, SceneKit adds a camera grain effect to your app's virtual content that matches the image noise characteristics ARKit
 observes in the camera feed.

 ![Screenshot showing the before and after cases of applying image noise to an app's virtual content.](media-3281981)
*/
@property (nonatomic, assign) BOOL rendersCameraGrain API_AVAILABLE(ios(13.0));

/**
 Determines whether the view renders motion blur.

 This property is disabled by default. When set, the view automatically adds motion blur to rendered content which matches the visual characteristics
 of the motion blur ARKit observes in the camera feed.

 ![Screenshot showing the before and after case of virtual content rendering with motion blur.](media-3231009)

 The value of this property overwrites the <doc://com.apple.documentation/documentation/scenekit/scncamera/motionblurintensity> of
 <doc://com.apple.documentation/documentation/scenekit/scncamera>.
*/
@property (nonatomic, assign) BOOL rendersMotionBlur API_AVAILABLE(ios(13.0));

/**
 Returns the AR anchor associated with the specified SceneKit node, if any.

 - Parameter node: A SceneKit node in the view's scene.

 - Returns: The ``ARAnchor`` object tracking the node, or `nil` if the node is not associated with an anchor or not in the view's scene.
*/
- (nullable ARAnchor *)anchorForNode:(SCNNode *)node;

/**
 Returns the SceneKit node associated with the specified AR anchor, if any.

 - Parameter anchor: An anchor in the view's AR session.

 - Returns: The node whose position in the AR scene the anchor tracks, or `nil` if the anchor has no associated node or is not in the view's AR
 session.
*/
- (nullable SCNNode *)nodeForAnchor:(ARAnchor *)anchor;

/**
 Searches for real-world objects or AR anchors in the captured camera image corresponding to a point in the SceneKit view.

 Hit testing searches for real-world objects or surfaces detected through the AR session's processing of the camera image. A 2D point in the view's
 coordinate system can refer to any point along a 3D line that starts at the device camera and extends in a direction determined by the device
 orientation and camera projection. This method searches along that line, returning all objects that intersect it in order of distance from the
 camera.

 > Note:
 > This method searches for AR anchors and real-world objects detected by the AR session, not SceneKit content displayed in the view. To search for
 SceneKit objects, use the view's <doc://com.apple.documentation/documentation/scenekit/scnscenerenderer/hittest(_:options:)> method instead.

 The behavior of a hit test depends on which `types` you specify and the order you specify them in. For details, see ``ARHitTestResult`` and the
 various ``ARHitTestResult/ResultType`` options.

 - Parameters:
   - point: A point in the 2D coordinate system of the view.
   - types: The types of hit-test result to search for.

 - Returns: A list of results, sorted from nearest to farthest (in distance from the camera).
*/
- (NSArray<ARHitTestResult *> *)hitTest:(CGPoint)point
                                  types:(ARHitTestResultType)types
    API_DEPRECATED("Use [ARSCNView raycastQueryFromPoint:allowingTarget:alignment]", ios(11.0, 14.0));

/**
 Returns the projection of a point from 2D view onto a plane in the 3D world space detected by ARKit.

 - Parameters:
   - point: The point in 2D view space to project onto a plane.

     The coordinate space for this point has its origin in the upper left corner and a size matching the view's bounds.
   - planeTransform: A transform matrix specifying the position and orientation of a plane (with infinite extent) in 3D world space. The plane is the
 xz-plane of the local coordinate space this transform defines.

 - Returns: The 3D point in world space where a ray projected from the specified 2D point intersects the specified plane. If the ray does not
 intersect the plane, this method returns a `float3` vector where all elements are `NaN`.
*/
- (simd_float3)unprojectPoint:(CGPoint)point ontoPlaneWithTransform:(simd_float4x4)planeTransform API_AVAILABLE(ios(12.0))NS_REFINED_FOR_SWIFT;

/**
 Creates a raycast query that originates from a point on the view, aligned with the center of the camera's field of view.

 When you call this function, ARKit creates a ray that extends in the positive z-direction from the argument screen space point, to determine if any
 of the argument targets exist in the physical environment anywhere along the ray. If so, ARKit returns a 3D position where the ray intersects the
 target.

 - Parameters:
   - point: A point in the view's coordinate system.
   - target: Type of target where the ray should terminate.
   - alignment: Alignment of the target.

 - Returns: A raycast query, or `nil` if the query cannot be created.
*/
- (nullable ARRaycastQuery *)raycastQueryFromPoint:(CGPoint)point
                                    allowingTarget:(ARRaycastTarget)target
                                         alignment:(ARRaycastTargetAlignment)alignment API_AVAILABLE(ios(13.0));

@end

#pragma mark - ARSCNViewDelegate

/**
 Methods you can implement to mediate the automatic synchronization of SceneKit content with an AR session.

 Implement this protocol to provide SceneKit content corresponding to ``ARAnchor`` objects tracked by the view's AR session, or to manage the view's
 automatic updating of such content.

 This protocol extends the ``ARSessionObserver`` protocol, so your session delegate can also implement those methods to respond to changes in session
 status.
 */
API_AVAILABLE(ios(11.0))
API_DEPRECATED_WITH_REPLACEMENT("Please use RealityView instead.", visionos(1.0, 1.0))
@protocol ARSCNViewDelegate <SCNSceneRendererDelegate, ARSessionObserver>
@optional

/**
 Asks the delegate to provide a SceneKit node corresponding to a newly added anchor.

 Depending on the session configuration, ARKit may automatically add anchors to a session. ARKit also calls this method to provide visual content for
 any ``ARAnchor`` objects you manually add using the session's ``ARSession/add(anchor:)`` method.

 You can implement this method to provide a new <doc://com.apple.documentation/documentation/scenekit/scnnode> object (or instance of an
 <doc://com.apple.documentation/documentation/scenekit/scnnode> subclass) containing any attachments you plan to use as a visual representation of the
 anchor. Note that ARKit controls the node's visibility and its <doc://com.apple.documentation/documentation/scenekit/scnnode/transform> property, so
 you may find it useful to add child nodes or adjust the node's <doc://com.apple.documentation/documentation/scenekit/scnnode/pivot> property to
 maintain any changes to position or orientation that you make.

 If you return `nil` from this method, no node is added to the scene.

 Alternatively, if you do not implement this method, ARKit creates an empty node, and you can implement the
 ``ARSCNViewDelegate/renderer(_:didAdd:for:)`` method instead to provide visual content by attaching it to that node.

 - Parameters:
   - renderer: The ``ARSCNView`` object rendering the scene.
   - anchor: The anchor for which a node is requested.

 - Returns: A new SceneKit node, which ARKit will add to the scene and update to follow its corresponding AR anchor.
*/
- (nullable SCNNode *)renderer:(id<SCNSceneRenderer>)renderer nodeForAnchor:(ARAnchor *)anchor;

/**
 Tells the delegate that a SceneKit node corresponding to a new AR anchor has been added to the scene.

 Depending on the session configuration, ARKit may automatically add anchors to a session. The view calls this method once for each new anchor. ARKit
 also calls this method to provide visual content for any ``ARAnchor`` objects you manually add using the session's ``ARSession/add(anchor:)`` method.

 You can provide visual content for the anchor by attaching geometry (or other SceneKit features) to this node or by adding child nodes.

 Alternatively, you can implement the ``ARSCNViewDelegate/renderer(_:nodeFor:)`` method to create your own node (or instance of an
 <doc://com.apple.documentation/documentation/scenekit/scnnode> subclass) for an anchor.

 - Parameters:
   - renderer: The ``ARSCNView`` object rendering the scene.
   - node: The newly added SceneKit node.
   - anchor: The AR anchor corresponding to the node.
*/
- (void)renderer:(id<SCNSceneRenderer>)renderer didAddNode:(SCNNode *)node forAnchor:(ARAnchor *)anchor;

/**
 Tells the delegate that a SceneKit node's properties will be updated to match the current state of its corresponding anchor.

 Depending on the session configuration, ARKit may automatically update anchors in a session. The view calls this method once for each updated anchor.

 - Parameters:
   - renderer: The ``ARSCNView`` object rendering the scene.
   - node: The updated SceneKit node.
   - anchor: The AR anchor corresponding to the node.
*/
- (void)renderer:(id<SCNSceneRenderer>)renderer willUpdateNode:(SCNNode *)node forAnchor:(ARAnchor *)anchor;

/**
 Tells the delegate that a SceneKit node's properties have been updated to match the current state of its corresponding anchor.

 Depending on the session configuration, ARKit may automatically update anchors in a session. The view calls this method once for each updated anchor.

 - Parameters:
   - renderer: The ``ARSCNView`` object rendering the scene.
   - node: The updated SceneKit node.
   - anchor: The AR anchor corresponding to the node.
*/
- (void)renderer:(id<SCNSceneRenderer>)renderer didUpdateNode:(SCNNode *)node forAnchor:(ARAnchor *)anchor;

/**
 Tells the delegate that the SceneKit node corresponding to a removed AR anchor has been removed from the scene.

 Depending on the session configuration, ARKit may automatically remove anchors from a session. The view calls this method once for each removed
 anchor.

 - Parameters:
   - renderer: The ``ARSCNView`` object rendering the scene.
   - node: The removed SceneKit node.
   - anchor: The AR anchor corresponding to the node.
*/
- (void)renderer:(id<SCNSceneRenderer>)renderer didRemoveNode:(SCNNode *)node forAnchor:(ARAnchor *)anchor;

@end

/**
 Options for drawing overlay content to aid debugging of AR tracking in a SceneKit view.

 To use these debugging overlays, add them to the option set in the view's
 <doc://com.apple.documentation/documentation/scenekit/scnscenerenderer/debugoptions> property (inherited from the
 <doc://com.apple.documentation/documentation/scenekit/scnview> class).
 */
typedef SCNDebugOptions ARSCNDebugOptions API_AVAILABLE(ios(11.0));

/**
 Display a coordinate axis visualization indicating the position and orientation of the AR world coordinate system.

 This visualization is available to all session configurations and session ``ARConfiguration/worldAlignment`` options, but is most useful with a
 ``ARWorldTrackingConfiguration`` session. For example, if you start running a session when this option is enabled, then take a step backward, the
 real-world position tracked by the AR world coordinate system should become visible on your device screen.
*/
API_AVAILABLE(ios(11.0))
FOUNDATION_EXTERN const SCNDebugOptions ARSCNDebugOptionShowWorldOrigin NS_SWIFT_NAME(ARSCNDebugOptions.showWorldOrigin);

/**
 Display a point cloud showing intermediate results of the scene analysis that ARKit uses to track device position.

 This option is available only when running a ``ARWorldTrackingConfiguration`` session.
*/
API_AVAILABLE(ios(11.0))
FOUNDATION_EXTERN const SCNDebugOptions ARSCNDebugOptionShowFeaturePoints NS_SWIFT_NAME(ARSCNDebugOptions.showFeaturePoints);

NS_ASSUME_NONNULL_END

API_UNAVAILABLE_END
