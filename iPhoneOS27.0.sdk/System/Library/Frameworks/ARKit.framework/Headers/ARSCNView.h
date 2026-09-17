#if (defined(USE_ARKIT_PUBLIC_HEADERS) && USE_ARKIT_PUBLIC_HEADERS) || !__has_include(<ARKitUI/ARSCNView.h>)
//
//  ARSCNView.h
//  ARKit
//
//  Copyright © 2016-2021 Apple Inc. All rights reserved.
//

#import <ARKit/ARHitTestResult.h>
#import <ARKit/ARSession.h>
#import <ARKit/ARTrackedRaycast.h>
#import <SceneKit/SceneKit.h>

API_UNAVAILABLE_BEGIN(visionos)

@protocol ARSCNViewDelegate;

NS_ASSUME_NONNULL_BEGIN

/**
 A view that integrates ARSession rendering into SceneKit.

 The view draws the camera background, provides and updates a camera,
 manages nodes for anchors, and updates lighting.
*/
API_AVAILABLE(ios(11.0))
API_DEPRECATED_WITH_REPLACEMENT("Please use RealityView instead.", visionos(1.0, 1.0))
@interface ARSCNView : SCNView <ARSessionProviding>

/**
 Specifies the renderer delegate.
 */
@property (nonatomic, weak, nullable) id<ARSCNViewDelegate> delegate;

/**
 The session that the view uses to update the scene.
 */
@property (nonatomic, strong) ARSession *session;

/**
 Specifies the scene of the view.
 */
@property (nonatomic, strong) SCNScene *scene;

/**
 Determines whether the view will update the scene’s lighting.

 When set, the view will automatically create and update lighting for
 light estimates the session provides. Defaults to `YES`.
*/
@property (nonatomic, assign) BOOL automaticallyUpdatesLighting;

/**
 Determines whether view renders camera grain.

 When set, the view will automatically add camera grain to rendered
 content that matches the grainy noise of the camera stream. Enabled by default.
*/
@property (nonatomic, assign) BOOL rendersCameraGrain API_AVAILABLE(ios(13.0));

/**
 Determines whether view renders motion blur.

 When set, the view will automatically add motion blur to rendered
 content that matches the motion blur of the camera stream.
 Overwrites SCNCamera's motionBlurIntensity property. Disabled by default.
*/
@property (nonatomic, assign) BOOL rendersMotionBlur API_AVAILABLE(ios(13.0));

/**
 Searches the scene hierarchy for an anchor associated with the provided node.

 - Parameter node: A node in the view's scene.

 - Returns: The anchor associated with the node, or `nil` if none exists.
*/
- (nullable ARAnchor *)anchorForNode:(SCNNode *)node;

/**
 Returns the node that has been mapped to a specific anchor.

 - Parameter anchor: An anchor with an existing node mapping.

 - Returns: The node mapped to the anchor, or `nil` if none exists.
*/
- (nullable SCNNode *)nodeForAnchor:(ARAnchor *)anchor;

/**
 Searches the current frame for objects corresponding to a point in the view.

 A 2D point in the view’s coordinate space can refer to any point along a line segment
 in the 3D coordinate space. Hit-testing is the process of finding objects in the world located along this line segment.

 - Parameters:
   - point: A point in the view’s coordinate system.
   - types: The types of results to search for.

 - Returns: An array of all hit-test results sorted from nearest to farthest.
*/
- (NSArray<ARHitTestResult *> *)hitTest:(CGPoint)point
                                  types:(ARHitTestResultType)types
    API_DEPRECATED("Use [ARSCNView raycastQueryFromPoint:allowingTarget:alignment]", ios(11.0, 14.0));

/**
 Unproject a 2D point from the view onto a plane in 3D world coordinates.

 A 2D point in the view’s coordinate space can refer to any point along a line segment
 in the 3D coordinate space. Unprojecting gets the 3D position of the point along this line segment that intersects the provided plane.

 - Parameters:
   - point: A point in the view’s coordinate system.
   - planeTransform: The transform used to define the coordinate system of the plane. The coordinate system’s positive Y axis is assumed to be the
 normal of the plane.

 - Returns: 3D position in world coordinates or `NAN` values if unprojection is not possible.
*/
- (simd_float3)unprojectPoint:(CGPoint)point ontoPlaneWithTransform:(simd_float4x4)planeTransform API_AVAILABLE(ios(12.0))NS_REFINED_FOR_SWIFT;

/**
 Creates a raycast query originating from the point on view, aligned along the center of the field of view of the camera.

 A 2D point in the view's coordinate space and the frame camera's field of view is used to create a ray in the 3D coordinate space
 originating at the point.

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
 A delegate protocol for SceneKit-based AR view events and node mapping.
 */
API_AVAILABLE(ios(11.0))
API_DEPRECATED_WITH_REPLACEMENT("Please use RealityView instead.", visionos(1.0, 1.0))
@protocol ARSCNViewDelegate <SCNSceneRendererDelegate, ARSessionObserver>
@optional

/**
 Implement this to provide a custom node for the given anchor.

 This node will automatically be added to the scene graph.
 If this method is not implemented, a node will be automatically created.
 If nil is returned the anchor will be ignored.

 - Parameters:
   - renderer: The renderer that will render the scene.
   - anchor: The added anchor.

 - Returns: Node that will be mapped to the anchor or `nil`.
*/
- (nullable SCNNode *)renderer:(id<SCNSceneRenderer>)renderer nodeForAnchor:(ARAnchor *)anchor;

/**
 Called when a new node has been mapped to the given anchor.

 - Parameters:
   - renderer: The renderer that will render the scene.
   - node: The node that maps to the anchor.
   - anchor: The added anchor.
*/
- (void)renderer:(id<SCNSceneRenderer>)renderer didAddNode:(SCNNode *)node forAnchor:(ARAnchor *)anchor;

/**
 Called when a node will be updated with data from the given anchor.

 - Parameters:
   - renderer: The renderer that will render the scene.
   - node: The node that will be updated.
   - anchor: The anchor that was updated.
*/
- (void)renderer:(id<SCNSceneRenderer>)renderer willUpdateNode:(SCNNode *)node forAnchor:(ARAnchor *)anchor;

/**
 Called when a node has been updated with data from the given anchor.

 - Parameters:
   - renderer: The renderer that will render the scene.
   - node: The node that was updated.
   - anchor: The anchor that was updated.
*/
- (void)renderer:(id<SCNSceneRenderer>)renderer didUpdateNode:(SCNNode *)node forAnchor:(ARAnchor *)anchor;

/**
 Called when a mapped node has been removed from the scene graph for the given anchor.

 - Parameters:
   - renderer: The renderer that will render the scene.
   - node: The node that was removed.
   - anchor: The anchor that was removed.
*/
- (void)renderer:(id<SCNSceneRenderer>)renderer didRemoveNode:(SCNNode *)node forAnchor:(ARAnchor *)anchor;

@end

/**
 Extended debug options for an ARSCNView
 */
typedef SCNDebugOptions ARSCNDebugOptions API_AVAILABLE(ios(11.0));

/** Show the world origin in the scene. */
API_AVAILABLE(ios(11.0))
FOUNDATION_EXTERN const SCNDebugOptions ARSCNDebugOptionShowWorldOrigin NS_SWIFT_NAME(ARSCNDebugOptions.showWorldOrigin);

/** Show detected 3D feature points in the world. */
API_AVAILABLE(ios(11.0))
FOUNDATION_EXTERN const SCNDebugOptions ARSCNDebugOptionShowFeaturePoints NS_SWIFT_NAME(ARSCNDebugOptions.showFeaturePoints);

NS_ASSUME_NONNULL_END

API_UNAVAILABLE_END
#else
#import <ARKitUI/ARSCNView.h> 
#endif // #if (defined(USE_ARKIT_PUBLIC_HEADERS) \&\& USE_ARKIT_PUBLIC_HEADERS) || !__has_include(<ARKitUI/ARSCNView.h>)