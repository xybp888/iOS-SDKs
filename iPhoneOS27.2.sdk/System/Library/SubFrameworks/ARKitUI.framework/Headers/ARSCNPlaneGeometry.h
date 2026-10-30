//
//  ARSCNPlaneGeometry.h
//  ARKit
//
//  Copyright © 2016-2021 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <SceneKit/SCNGeometry.h>

@protocol MTLDevice;

API_UNAVAILABLE_BEGIN(visionos)

@class ARPlaneGeometry;

NS_ASSUME_NONNULL_BEGIN

/**
 A SceneKit representation of the 2D shape of a plane, for use with plane detection results in an AR session.

 `ARSCNPlaneGeometry` is a subclass of <doc://com.apple.documentation/documentation/scenekit/scngeometry> that wraps the mesh data provided by the
 ``ARPlaneGeometry`` class. You can use `ARSCNPlaneGeometry` to visualize the plane shape estimates provided by ARKit in a SceneKit view.

 > Important:
 > `ARSCNPlaneGeometry` is available only in SceneKit views or renderers that use Metal. This class is not supported for OpenGL-based SceneKit
 rendering.

 As your AR session continues to run, ARKit provides refined estimates of a detected plane's 2D shape. Use the ``updateFromPlaneGeometry:`` method to
 incorporate those refinements into the plane's SceneKit representation.
 */
API_AVAILABLE(ios(11.3))
@interface ARSCNPlaneGeometry : SCNGeometry

/**
 Creates a SceneKit plane geometry for rendering with the specified Metal device object.

 - Parameter device: The Metal device to use for rendering the geometry.

 A newly created `ARSCNPlaneGeometry` instance does not represent any specific plane; use the ``updateFromPlaneGeometry:`` method to make the geometry
 match the estimated shape of a specific plane anchor.

 The geometry contains a single geometry element; as such, assigning more than one material has no visible effect (see the inherited
 <doc://com.apple.documentation/documentation/scenekit/scngeometry/materials> property).
*/
+ (nullable instancetype)planeGeometryWithDevice:(id<MTLDevice>)device;

/**
 Reshapes the SceneKit geometry to match the specified plane mesh.

 - Parameter planeGeometry: A coarse mesh representation of a detected plane's estimated shape.

 To update a SceneKit model of a plane actively tracked in an AR session, call this method in your ``ARSCNViewDelegate`` object's
 ``ARSCNViewDelegate/renderer(_:didUpdate:for:)`` callback, passing the ``ARPlaneAnchor/geometry`` property from the ``ARPlaneAnchor`` object that
 callback provides.
*/
- (void)updateFromPlaneGeometry:(ARPlaneGeometry *)planeGeometry;

@end

NS_ASSUME_NONNULL_END

API_UNAVAILABLE_END
