#if (defined(USE_ARKIT_PUBLIC_HEADERS) && USE_ARKIT_PUBLIC_HEADERS) || !__has_include(<ARKitUI/ARSKView.h>)
//
//  ARSKView.h
//  ARKit
//
//  Copyright © 2017 Apple Inc. All rights reserved.
//

#import <ARKit/ARHitTestResult.h>
#import <ARKit/ARSession.h>
#import <SpriteKit/SpriteKit.h>

API_UNAVAILABLE_BEGIN(visionos)

NS_ASSUME_NONNULL_BEGIN

@class ARSKView;

#pragma mark ARSKViewDelegate

/**
 Methods you can implement to mediate the automatic synchronization of SpriteKit content with an AR session.

 Implement this protocol to provide SpriteKit content corresponding to ``ARAnchor`` objects tracked by the view's
 AR session, or to manage the view's automatic updating of such content.

 This protocol extends the ``ARSessionObserver`` protocol, so your session delegate can also implement those methods
 to respond to changes in session status.
 */
API_AVAILABLE(ios(11.0))
API_DEPRECATED("This API is deprecated on visionOS.", visionos(1.0, 1.0))
@protocol ARSKViewDelegate <SKViewDelegate, ARSessionObserver>
@optional

/**
 Asks the delegate to provide a SpriteKit node corresponding to a newly added anchor.

 Depending on the session configuration, ARKit may automatically add anchors to a session, such as the origin of the
 world coordinate system and detected planes. ARKit also calls this method to provide visual content for any
 ``ARAnchor`` objects you manually add using the session's ``ARSession/add(anchor:)`` method.

 You can implement this method to provide a new <doc://com.apple.documentation/documentation/spritekit/sknode> object
 (or instance of any system or custom <doc://com.apple.documentation/documentation/spritekit/sknode> subclass) you plan
 to use as a visual representation of the anchor.

 Note that ARKit controls the node's position, rotation, and scale to simulate a billboarded 3D effect even for 2D
 sprites. If you provide a `SKTransformNode` node, ARKit applies a 3D transformation.

 Alternatively, if you do not implement this method, ARKit creates an empty node, and you can implement the
 ``ARSKViewDelegate/view(_:didAdd:for:)`` method instead to provide visual content by adding children to that node.

 - Parameters:
   - view: The ``ARSKView`` object rendering the scene.
   - anchor: The anchor for which a node is requested.

 - Returns: A new SpriteKit node, which ARKit will add to the scene and update to follow its corresponding AR anchor, or `nil` to have ARKit ignore
 the anchor (no node is created for it).
*/
- (nullable SKNode *)view:(ARSKView *)view nodeForAnchor:(ARAnchor *)anchor;

/**
 Tells the delegate that a SpriteKit node corresponding to a new AR anchor has been added to the scene.

 Depending on the session configuration, ARKit may automatically add anchors to a session. The view calls this method
 once for each new anchor. ARKit also calls this method to provide visual content for any ``ARAnchor`` objects you
 manually add using the session's ``ARSession/add(anchor:)`` method.

 You can provide visual content for the anchor by adding child nodes.

 Alternatively, you can implement the ``ARSKViewDelegate/view(_:nodeFor:)`` method to create your own node (or instance
 of an <doc://com.apple.documentation/documentation/spritekit/sknode> subclass) for an anchor.

 - Parameters:
   - view: The ``ARSKView`` object rendering the scene.
   - node: The newly added SpriteKit node.
   - anchor: The AR anchor corresponding to the node.
*/
- (void)view:(ARSKView *)view didAddNode:(SKNode *)node forAnchor:(ARAnchor *)anchor;

/**
 Tells the delegate that a SpriteKit node's properties will be updated to match the current state of its corresponding anchor.

 Depending on the session configuration, ARKit may automatically update anchors in a session. The view calls this
 method once for each updated anchor.

 - Parameters:
   - view: The ``ARSKView`` object rendering the scene.
   - node: The updated SpriteKit node.
   - anchor: The AR anchor corresponding to the node.
*/
- (void)view:(ARSKView *)view willUpdateNode:(SKNode *)node forAnchor:(ARAnchor *)anchor;

/**
 Tells the delegate that a SpriteKit node's properties have been updated to match the current state of its corresponding anchor.

 Depending on the session configuration, ARKit may automatically update anchors in a session. The view calls this
 method once for each updated anchor.

 - Parameters:
   - view: The ``ARSKView`` object rendering the scene.
   - node: The updated SpriteKit node.
   - anchor: The AR anchor corresponding to the node.
*/
- (void)view:(ARSKView *)view didUpdateNode:(SKNode *)node forAnchor:(ARAnchor *)anchor;

/**
 Tells the delegate that the SpriteKit node corresponding to an AR anchor has been removed from the scene.

 Depending on the session configuration, ARKit may automatically remove anchors from a session. The view calls this
 method once for each removed anchor.

 - Parameters:
   - view: The ``ARSKView`` object rendering the scene.
   - node: The removed SpriteKit node.
   - anchor: The AR anchor corresponding to the node.
*/
- (void)view:(ARSKView *)view didRemoveNode:(SKNode *)node forAnchor:(ARAnchor *)anchor;

@end

#pragma mark ARSKView

/**
 A view that blends virtual 2D content from SpriteKit into the 3D space of an augmented reality experience.

 Use the ``ARSKView`` class to create augmented reality experiences that position 2D elements in 3D space within a
 device camera view of the real world. When you run the view's provided ``ARSession`` object:

 - The view automatically renders the live video feed from the device camera as the scene background.
 - When you implement ``ARSKViewDelegate`` methods to associate SpriteKit content with real-world positions, the view
   automatically scales and rotates those SpriteKit nodes so that they appear to track the real world seen by the camera.
*/
API_AVAILABLE(ios(11.0))
API_DEPRECATED("This API is deprecated on visionOS.", visionos(1.0, 1.0))
@interface ARSKView : SKView <ARSessionProviding>

/**
 An object you provide to mediate synchronization of the view's AR scene information with SpriteKit content.
 */
@property (nonatomic, weak, nullable) NSObject<ARSKViewDelegate> *delegate;

/**
 The AR session that manages motion tracking and camera image processing for the view's contents.

 A view creates its own session object; use this property to access and configure the view's session.
 */
@property (nonatomic, strong) ARSession *session;

/**
 Returns the AR anchor associated with the specified SpriteKit node, if any.

 - Parameters:
   - node: A SpriteKit node in the view's scene.

 - Returns: The ``ARAnchor`` object tracking the node, or `nil` if the node is not associated with an anchor or not in the view's scene.
*/
- (nullable ARAnchor *)anchorForNode:(SKNode *)node;

/**
 Returns the SpriteKit node associated with the specified AR anchor, if any.

 - Parameters:
   - anchor: An anchor in the view's AR session.

 - Returns: The node whose position in the AR scene the anchor tracks, or `nil` if the anchor has no associated node or is not in the view's AR
 session.
*/
- (nullable SKNode *)nodeForAnchor:(ARAnchor *)anchor;

/**
 Searches for real-world objects or AR anchors in the captured camera image corresponding to a point in the SpriteKit view.

 Hit testing searches for real-world objects or surfaces detected through the AR session's processing of the camera
 image. A 2D point in the view's coordinate system can refer to any point along a 3D line that starts at the device
 camera and extends in a direction determined by the device orientation and camera projection. This method searches
 along that line, returning all objects that intersect it in order of distance from the camera.

 > Note:
 > This method searches for AR anchors and real-world objects detected by the AR session, not SpriteKit content
 > displayed in the view. To search for SpriteKit objects, use the
 > <doc://com.apple.documentation/documentation/spritekit/sknode/nodes(at:)> method of the view's SpriteKit scene.

 The behavior of a hit test depends on which `types` you specify and the order you specify them in. For details, see
 ``ARHitTestResult`` and the various ``ARHitTestResult/ResultType`` options.

 - Parameters:
   - point: A point in the 2D coordinate system of the view.
   - types: The types of hit-test result to search for.

 - Returns: A list of results, sorted from nearest to farthest (in distance from the camera).
*/
- (NSArray<ARHitTestResult *> *)hitTest:(CGPoint)point types:(ARHitTestResultType)types API_DEPRECATED("Use raycasting", ios(11.0, 14.0));

@end

NS_ASSUME_NONNULL_END

API_UNAVAILABLE_END
#else
#import <ARKitUI/ARSKView.h> 
#endif // #if (defined(USE_ARKIT_PUBLIC_HEADERS) \&\& USE_ARKIT_PUBLIC_HEADERS) || !__has_include(<ARKitUI/ARSKView.h>)