//
//  ARPlaneAnchor.h
//  ARKit
//
//  Copyright © 2016-2021 Apple Inc. All rights reserved.
//

#import <ARKitCore/ARAnchor.h>

NS_ASSUME_NONNULL_BEGIN

API_UNAVAILABLE_BEGIN(visionos)

@class ARPlaneGeometry;

/**
 The kinds of alignment — horizontal or vertical — that a plane anchor can have.
 */
API_AVAILABLE(ios(11.0))
typedef NS_ENUM(NSInteger, ARPlaneAnchorAlignment) {
    /**
     The plane is perpendicular to gravity.

     The ``ARAnchor/transform`` property for a horizontal plane anchor includes no rotation about the x- or z-axis. Thus, using this anchor's
     transform to place a 3D model asset in your scene results in the model appearing "right side up".
     */
    ARPlaneAnchorAlignmentHorizontal,

    /**
     The plane is parallel to gravity.

     The ``ARAnchor/transform`` property for a vertical plane anchor includes a rotation component. That is, the transform matrix represents the
     result of rotating a horizontal plane to match the orientation of the detected surface.
     */
    ARPlaneAnchorAlignmentVertical API_AVAILABLE(ios(11.3)),
} NS_SWIFT_NAME(ARPlaneAnchor.Alignment);

/**
 Possible states of ARKit's process for classifying plane anchors.

 You get values of this type from a plane anchor's ``ARPlaneAnchor/classificationStatus`` property, describing the state of ARKit's plane
 classification process.
 */
API_AVAILABLE(ios(12.0))
typedef NS_ENUM(NSInteger, ARPlaneClassificationStatus) {
    /**
     ARKit cannot currently provide plane classification information.

     Plane classification is available on iOS devices with an A12 Bionic chip or later. On other devices, all plane anchors always indicate a
     classification status of ``ARPlaneClassificationStatus/ARPlaneClassificationStatusNotAvailable``.

     A classification status of ``ARPlaneClassificationStatus/ARPlaneClassificationStatusNotAvailable`` can also occur if the plane classification
     process is temporarily unavailable.
     */
    ARPlaneClassificationStatusNotAvailable = 0,
    /**
     ARKit has not yet produced a classification for the plane anchor.

     This status occurs when ARKit is still in the process of plane classification. To be notified when ARKit produces a classification, observe the
     same plane anchor in a later frame (for example, in the ``ARSessionDelegate/session(_:didUpdate:)-3qtt8`` or
     ``ARSCNViewDelegate/renderer(_:didUpdate:for:)`` delegate method).
     */
    ARPlaneClassificationStatusUndetermined,
    /**
     ARKit has completed its classification process for the plane anchor, but the result is inconclusive.

     ARKit attempts to classify detected planes using a finite set of common categories. However, a detected plane may not be a real object fitting
     any of those categories, or the plane classification process may not be able to recognize it. In such cases, the plane anchor's
     ``ARPlaneAnchor/classification-2hi2p`` is ``ARPlaneClassification/ARPlaneClassificationNone`` and its ``ARPlaneAnchor/classificationStatus`` is
     ``ARPlaneClassificationStatus/ARPlaneClassificationStatusUnknown``.
     */
    ARPlaneClassificationStatusUnknown,
    /**
     ARKit has completed its classification process for the plane anchor.

     See the ``ARPlaneAnchor/classification-2hi2p`` property to identify the detected surface.
     */
    ARPlaneClassificationStatusKnown
} NS_REFINED_FOR_SWIFT;

/**
 Possible characterizations of real-world surfaces represented by plane anchors.

 You get values of this type from a plane anchor's ``ARPlaneAnchor/classification-2hi2p`` property, identifying the likely type of real-world surface
 for a detected plane anchor.
 */
API_AVAILABLE(ios(12.0))
typedef NS_ENUM(NSInteger, ARPlaneClassification) {
    /**
     No classification is available for the plane anchor.

     When a plane anchor has no classification, the ``ARPlaneAnchor/classificationStatus`` property indicates the reason: the classification process
     might be unavailable or incomplete, or ARKit may not have been able to conclusively identify the plane.
     */
    ARPlaneClassificationNone = 0,
    /** The plane anchor represents a real-world wall or similar large vertical surface. */
    ARPlaneClassificationWall,
    /** The plane anchor represents a real-world floor, ground plane, or similar large horizontal surface. */
    ARPlaneClassificationFloor,
    /** The plane anchor represents a real-world ceiling or similar overhead horizontal surface. */
    ARPlaneClassificationCeiling,
    /** The plane anchor represents a real-world table, desk, bar, or similar flat surface. */
    ARPlaneClassificationTable,
    /** The plane anchor represents a real-world chair, stool, bench or similar flat surface. */
    ARPlaneClassificationSeat,
    /** The plane anchor fits the description of a real-world window. */
    ARPlaneClassificationWindow,
    /** The plane anchor represents a real-world door, or similar archway. */
    ARPlaneClassificationDoor
} NS_REFINED_FOR_SWIFT;

/**
 The size and y-axis rotation of a detected plane.

 A plane anchor (``ARPlaneAnchor``) describes its size and orientation on the y-axis using the ``ARPlaneAnchor/planeExtent`` property of this type.

 At runtime, ARKit continually updates the anchor's width and height as the framework refines its knowledge of the plane's shape in the environment.

 Similarly, as the session runs, the framework may update the plane's y-rotation to better fit its rectangular area in the environment. In iOS 15 and
 earlier, the framework rotates the plane anchor according to that angle. In iOS 16, the framework doesn't rotate the anchor automatically and its
 transform matrix remains unchanged. Instead, the framework exposes the angle ``rotationOnYAxis`` that you apply to any plane extent geometry in your
 app.

 > Important:
 > Apps that run on iOS 16 with a deployment target less than iOS 16 preserve the prior y-axis rotation behavior.

 ### Size and Rotate an Entity to a Plane's Extent

 The following code defines a RealityKit entity sized to the plane extent's width and height. The helper function also applies the extent's suggested
 y-axis rotation by setting its transform `yaw` value to ``rotationOnYAxis``.

 ```swift
 func createPlane(for planeAnchor: ARPlaneAnchor, material: Material) -> ModelEntity {

     // Get the plane's extent.
     let extent = planeAnchor.planeExtent

     // Create a model entity sized to the plane's extent.
     let planeEntity = ModelEntity(mesh: .generatePlane (width: extent.width, depth: extent.height),
         materials: [material])

     // Orient the entity according to the extent's y-axis rotation.
     planeEntity.transform = Transform(pitch: 0, yaw: extent.rotationOnYAxis, roll: 0)

     // Center the entity on the plane.
     planeEntity.transform.translation = planeAnchor.center

     return planeEntity
 }
 ```
 */
API_AVAILABLE(ios(16.0))
NS_SWIFT_SENDABLE
@interface ARPlaneExtent : NSObject <NSSecureCoding>

/**
 A radian value that indicates a plane's y-axis orientation.

 As the session runs, the framework may update the plane's y-rotation to better fit its rectangular area in the environment. In iOS 15 and earlier,
 the framework rotates the plane anchor according to that angle. In iOS 16, the framework doesn't rotate the anchor automatically and its transform
 matrix remains unchanged. Instead, the framework exposes the angle in ``ARPlaneExtent/rotationOnYAxis`` that you apply to any plane extent geometry
 in your app.

 > Important:
 > Apps that run on iOS 16 with a deployment target less than iOS 16 preserve the prior y-axis rotation behavior.
 */
@property (nonatomic, readonly) float rotationOnYAxis;

/**
 The estimated width of the plane.

 This corresponds to the length of the plane along the x-axis, prior to applying `rotationOnYAxis`.
 */
@property (nonatomic, readonly) float width;

/**
 The estimated height of the plane.

 This corresponds to the length of the plane along the z-axis, prior to applying `rotationOnYAxis`.
 */
@property (nonatomic, readonly) float height;

@end

/**
 An anchor for a 2D planar surface that ARKit detects in the physical environment.

 When you enable ``ARWorldTrackingConfiguration/planeDetection`` in a world tracking session, ARKit notifies your app of all the surfaces it observes
 using the device's back camera. ARKit calls your delegate's ``ARSessionDelegate/session(_:didAdd:)`` with an ``ARPlaneAnchor`` for each unique
 surface. Each plane anchor provides details about the surface, like its real-world position and shape.

 The width and length of a plane (the ``planeExtent``) span the xz-plane of an ``ARPlaneAnchor`` instance's local coordinate system. The y-axis of the
 plane anchor is the plane's normal vector.
*/
API_AVAILABLE(ios(11.0))
NS_SWIFT_SENDABLE
@interface ARPlaneAnchor : ARAnchor

/**
 A Boolean value that indicates whether plane classification is available on the current device.

 Plane classification is available on iOS devices with an A12 Bionic chip or later.

 On devices without plane classification support, all plane anchors report a ``ARPlaneAnchor/classification-2hi2p`` value of
 ``ARPlaneClassification/ARPlaneClassificationNone`` and a ``ARPlaneAnchor/classificationStatus`` value of
 ``ARPlaneClassificationStatus/ARPlaneClassificationStatusNotAvailable``.
 */
@property (class, nonatomic, readonly, getter=isClassificationSupported) BOOL classificationSupported API_AVAILABLE(ios(12.0));

/**
 The general orientation of the detected plane with respect to gravity.
 */
@property (nonatomic, readonly) ARPlaneAnchorAlignment alignment;

/**
 The center point of the plane relative to its anchor position.

 When ARKit first detects a plane, the resulting ``ARPlaneAnchor`` object has a ``ARPlaneAnchor/center`` value of `(0,0,0)`, indicating that the
 translation portion of the anchor's ``ARAnchor/transform`` value locates the plane's center point.

 As scene analysis and plane detection continues, ARKit may determine that a previously detected plane anchor is part of a larger real-world surface,
 increasing the ``ARPlaneAnchor/extent`` width and length values. The plane's new boundaries may not be symmetric around its initial position, so the
 ``ARPlaneAnchor/center`` point changes relative to the anchor's (unchanged) ``ARAnchor/transform`` matrix.

 Although the type of this property is <doc://com.apple.documentation/documentation/simd/vector_float3>, a plane anchor is always two-dimensional, and
 is always positioned in only the x and z directions relative to its ``ARAnchor/transform`` position. (That is, the y-component of this vector is
 always zero.)
 */
@property (nonatomic, readonly) simd_float3 center;

/**
 The estimated width and length of the detected plane.

 > Warning:
 > In iOS 16, use ``ARPlaneAnchor/planeExtent`` instead.

 The framework sets the x and z components to the width and length of the plane, respectively. The y-component is unused, with a constant value of
 `0`.
 */
@property (nonatomic, readonly) simd_float3 extent API_DEPRECATED_WITH_REPLACEMENT("planeExtent", ios(11.0, 16.0));

/**
 The estimated width, length, and y-axis rotation of the detected plane.

 When ARKit first detects a plane, the resulting ``ARPlaneAnchor`` object has a ``ARPlaneAnchor/center`` value of `(0,0,0)`, indicating that the
 translation portion of the anchor's ``ARAnchor/transform`` value locates the plane's center point.

 As the session runs, ARKit may determine that a previously detected plane anchor is part of a larger real-world surface, increasing the
 ``ARPlaneAnchor/planeExtent`` width and height values. The plane's new boundaries may not be symmetric around its initial position, so the
 ``ARPlaneAnchor/center`` point changes relative to the anchor's unchanged ``ARAnchor/transform`` matrix.

 Similarly, as the session runs, the framework may update the plane's y-rotation to better fit its rectangular area in the environment. In iOS 15 and
 earlier, the framework rotates the plane anchor according to that angle. In iOS 16, the framework doesn't rotate the anchor automatically and its
 transform matrix remains unchanged. Instead, the framework exposes the angle in ``ARPlaneExtent/rotationOnYAxis`` that you apply to any plane extent
 geometry in your app.

 > Important:
 > Apps that run on iOS 16 with a deployment target less than iOS 16 preserve the prior y-axis rotation behavior.
 */
@property (nonatomic, readonly) ARPlaneExtent *planeExtent API_AVAILABLE(ios(16.0));

/**
 A coarse triangle mesh representing the general shape of the detected plane.

 This mesh provides vertex, index, and texture coordinate buffers describing the estimated 2D footprint of the plane.

 You can visualize the plane geometry by passing these buffers to your preferred rendering engine. To visualize a plane geometry using SceneKit,
 create an ``ARSCNPlaneGeometry`` instance and use its ``ARSCNPlaneGeometry/update(from:)`` method to update it to match the plane geometry.
 */
@property (nonatomic, strong, readonly) ARPlaneGeometry *geometry API_AVAILABLE(ios(11.3));

/**
 The current state of ARKit's process for classifying the plane anchor.

 On supported devices, ARKit automatically attempts to characterize each detected plane, describing it as a real-world surface such as a wall, floor,
 or table. You can then use this information to enhance the realism of your AR experience; for example, by placing certain virtual content only on
 floors.

 When this property's value is ``ARPlaneClassificationStatus/ARPlaneClassificationStatusKnown``, the ``ARPlaneAnchor/classification-2hi2p`` property
 represents ARKit's characterization of the real-world surface corresponding to the plane anchor.

 Plane classification can take longer than plane detection, and ARKit reports classifications only for planes where it has a high confidence in the
 result, so you can use other values of this property to keep track of ARKit's classification process:

 - If ARKit is still working to classify a plane, the classification is ``ARPlaneClassification/ARPlaneClassificationNone`` and the status is
 ``ARPlaneClassificationStatus/ARPlaneClassificationStatusUndetermined``.
 - If ARKit cannot characterize a plane with high confidence, the classification is ``ARPlaneClassification/ARPlaneClassificationNone`` and the status
 is ``ARPlaneClassificationStatus/ARPlaneClassificationStatusUnknown``.

 Plane classification is available on iOS devices with an A12 Bionic chip or later. Before using classification results, check the
 ``ARPlaneAnchor/isClassificationSupported`` class property to make sure you're on a supported device.
 */
@property (nonatomic, assign, readonly) ARPlaneClassificationStatus classificationStatus API_AVAILABLE(ios(12.0)) NS_REFINED_FOR_SWIFT;

/**
 A general characterization of what kind of real-world surface the plane anchor represents.

 On supported devices, ARKit automatically attempts to characterize each detected plane, describing it as a real-world surface such as a wall, floor,
 or table. You can then use this information to enhance the realism of your AR experience; for example, by placing certain virtual content only on
 floors.

 Plane classification can take longer than plane detection, and ARKit reports classifications only for planes where it has a high confidence in the
 result. Use this property together with the ``ARPlaneAnchor/classificationStatus`` property to keep track of ARKit's classification process:

 - If ARKit is still working to classify a plane, the classification is ``ARPlaneClassification/ARPlaneClassificationNone`` and the status is
 ``ARPlaneClassificationStatus/ARPlaneClassificationStatusUndetermined``.
 - If ARKit cannot characterize a plane with high confidence, the classification is ``ARPlaneClassification/ARPlaneClassificationNone`` and the status
 is ``ARPlaneClassificationStatus/ARPlaneClassificationStatusUnknown``.

 Plane classification is available on iOS devices with an A12 Bionic chip or later. Before using classification results, check the
 ``ARPlaneAnchor/isClassificationSupported`` class property to make sure you're on a supported device.
 */
@property (nonatomic, assign, readonly) ARPlaneClassification classification API_AVAILABLE(ios(12.0)) NS_REFINED_FOR_SWIFT;

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
