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
 A delegate protocol for SpriteKit-based AR view events and node mapping.
 */
API_AVAILABLE(ios(11.0))
API_DEPRECATED("This API is deprecated on visionOS.", visionos(1.0, 1.0))
@protocol ARSKViewDelegate <SKViewDelegate, ARSessionObserver>
@optional

/**
 Implement this to provide a custom node for the given anchor.

 This node will automatically be added to the scene graph.
 If this method is not implemented, a node will be automatically created.
 If nil is returned the anchor will be ignored.

 - Parameters:
   - view: The view that will render the scene.
   - anchor: The added anchor.

 - Returns: Node that will be mapped to the anchor or `nil`.
*/
- (nullable SKNode *)view:(ARSKView *)view nodeForAnchor:(ARAnchor *)anchor;

/**
 Called when a new node has been mapped to the given anchor.

 - Parameters:
   - view: The view that will render the scene.
   - node: The node that maps to the anchor.
   - anchor: The added anchor.
*/
- (void)view:(ARSKView *)view didAddNode:(SKNode *)node forAnchor:(ARAnchor *)anchor;

/**
 Called when a node will be updated with data from the given anchor.

 - Parameters:
   - view: The view that will render the scene.
   - node: The node that will be updated.
   - anchor: The anchor that was updated.
*/
- (void)view:(ARSKView *)view willUpdateNode:(SKNode *)node forAnchor:(ARAnchor *)anchor;

/**
 Called when a node has been updated with data from the given anchor.

 - Parameters:
   - view: The view that will render the scene.
   - node: The node that was updated.
   - anchor: The anchor that was updated.
*/
- (void)view:(ARSKView *)view didUpdateNode:(SKNode *)node forAnchor:(ARAnchor *)anchor;

/**
 Called when a mapped node has been removed from the scene graph for the given anchor.

 - Parameters:
   - view: The view that will render the scene.
   - node: The node that was removed.
   - anchor: The anchor that was removed.
*/
- (void)view:(ARSKView *)view didRemoveNode:(SKNode *)node forAnchor:(ARAnchor *)anchor;

@end

#pragma mark ARSKView

/**
 A view that integrates ARSession rendering into SpriteKit.

 The view draws the camera background, and projects and maps anchors to nodes.
*/
API_AVAILABLE(ios(11.0))
API_DEPRECATED("This API is deprecated on visionOS.", visionos(1.0, 1.0))
@interface ARSKView : SKView <ARSessionProviding>

/**
 Specifies the view’s delegate.
 */
@property (nonatomic, weak, nullable) NSObject<ARSKViewDelegate> *delegate;

/**
 The session that the view uses to update the view.
 */
@property (nonatomic, strong) ARSession *session;

/**
 Searches the scene hierarchy for an anchor associated with the provided node.

 - Parameter node: A node in the view's scene.

 - Returns: The anchor associated with the node, or `nil` if none exists.
*/
- (nullable ARAnchor *)anchorForNode:(SKNode *)node;

/**
 Returns the node that has been mapped to a specific anchor.

 - Parameter anchor: An anchor with an existing node mapping.

 - Returns: The node mapped to the anchor, or `nil` if none exists.
*/
- (nullable SKNode *)nodeForAnchor:(ARAnchor *)anchor;

/**
 Searches the current frame for objects corresponding to a point in the view.

 A 2D point in the view’s coordinate space can refer to any point along a line segment
 in the 3D coordinate space. Hit-testing is the process of finding objects in the world located along this line segment.

 - Parameters:
   - point: A point in the view’s coordinate system.
   - types: The types of results to search for.

 - Returns: An array of all hit-test results sorted from nearest to farthest.
*/
- (NSArray<ARHitTestResult *> *)hitTest:(CGPoint)point types:(ARHitTestResultType)types API_DEPRECATED("Use raycasting", ios(11.0, 14.0));

@end

NS_ASSUME_NONNULL_END

API_UNAVAILABLE_END
#else
#import <ARKitUI/ARSKView.h> 
#endif // #if (defined(USE_ARKIT_PUBLIC_HEADERS) \&\& USE_ARKIT_PUBLIC_HEADERS) || !__has_include(<ARKitUI/ARSKView.h>)