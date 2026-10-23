//
//  ARObjectAnchor.h
//  ARKit
//
//  Copyright © 2016-2021 Apple Inc. All rights reserved.
//

#import <ARKitCore/ARAnchor.h>

NS_ASSUME_NONNULL_BEGIN

API_UNAVAILABLE_BEGIN(visionos)

@class ARReferenceObject;

/**
 An anchor for a real-world 3D object that ARKit detects in the physical environment.

 When you run a world-tracking AR session and specify ``ARReferenceObject`` objects
 for the session configuration's ``ARWorldTrackingConfiguration/detectionObjects`` or ``ARWorldTrackingConfiguration/trackingObjects`` property,
 ARKit searches for those objects in the real-world environment. When the session
 recognizes an object, it automatically adds to its list of anchors an
 ``ARObjectAnchor`` for each match.

 For objects loaded from a `.referenceobject` file, use ``ARTrackable/isTracked``
 to determine whether ARKit is currently tracking the object. ARKit keeps the
 anchor in the session even when tracking is temporarily lost, so check
 ``ARTrackable/isTracked`` before relying on the anchor's transform. For objects
 loaded from the older `.arobject` format, ``ARTrackable/isTracked`` always
 returns `true` and doesn't reflect tracking state.

 To place virtual 3D content that matches the position or size of the detected
 object, use the anchor's inherited ``ARAnchor/transform`` property together with the
 ``ARReferenceObject/center`` and ``ARReferenceObject/extent`` of the anchor's
 ``ARObjectAnchor/referenceObject``. Starting in iOS 27, you can also
 render the trained model directly: if the reference object's ``ARReferenceObject/usdzFile``
 URL is non-nil, load that USDZ file and overlay it on the real object.
 */
API_AVAILABLE(ios(12.0))
NS_SWIFT_SENDABLE
@interface ARObjectAnchor : ARAnchor <ARTrackable>

/**
 Reference to the detected object.
 */
@property (nonatomic, strong, readonly) ARReferenceObject *referenceObject;

/**
 A Boolean value indicating whether the anchor is currently being tracked.
 */
@property (nonatomic, readonly) BOOL isTracked API_AVAILABLE(ios(27.0));

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
