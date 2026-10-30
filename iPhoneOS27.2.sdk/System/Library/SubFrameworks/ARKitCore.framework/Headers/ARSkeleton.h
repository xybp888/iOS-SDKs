//
//  ARSkeleton.h
//  ARKit
//
//  Copyright © 2019 Apple Inc. All rights reserved.
//

#import <ARKitCore/ARSkeletonDefinition.h>
#import <Foundation/Foundation.h>
#import <Vision/Vision.h>
#import <simd/simd.h>

NS_ASSUME_NONNULL_BEGIN

API_UNAVAILABLE_BEGIN(visionos)

/**
 The interface for the skeleton of a tracked body.

 As a collection of joints, this class describes the state of a human body whose movements ARKit can track.

 The ``ARSkeleton3D`` subclass provides you with the position of a tracked body's joints in 3D space, specifically with its
 ``ARSkeleton3D/jointLocalTransforms`` and ``ARSkeleton3D/jointModelTransforms`` properties.

 The ``ARSkeleton2D`` subclass provides you with the position of a tracked body's joints in 2D space, by way of its ``ARSkeleton2D/jointLandmarks``
 property.

 - SeeAlso: ``ARSkeletonDefinition``
*/
API_AVAILABLE(ios(13.0))
NS_SWIFT_SENDABLE
@interface ARSkeleton : NSObject

/**
 The particular configuration of joints that define a body's current state.
 */
@property (nonatomic, readonly) ARSkeletonDefinition *definition;

/**
 The skeleton's total number of joints.
 */
@property (nonatomic, readonly) NSUInteger jointCount NS_REFINED_FOR_SWIFT;

/**
 Tells you whether ARKit tracks a joint at a particular index.

 Use this function to determine which joints ARKit tracks using a particular index.

 - Parameter jointIndex: The index of the joint.

 - Returns: `YES` if the joint is tracked. `NO` otherwise.
*/
- (BOOL)isJointTracked:(NSInteger)jointIndex;

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

/**
 The skeleton of a human body that ARKit tracks in 3D space.

 An ``ARBodyAnchor`` contains one instance of this ``ARSkeleton`` subclass to provide its joint positions in 3D space. The ``jointLocalTransforms``
 property describes a joint's 3D offset from its parent joint. The ``jointModelTransforms`` property describes a joint's 3D offset from the body
 anchor's ``ARAnchor/transform``.
 */
API_AVAILABLE(ios(13.0))
NS_SWIFT_SENDABLE
@interface ARSkeleton3D : ARSkeleton

/**
 The model space transforms for each joint.

 Model space refers to a joint's position relative to the hip joint. Note, the hip joint is located at the body anchor's origin.
 */
@property (nonatomic, readonly) const simd_float4x4 *jointModelTransforms NS_REFINED_FOR_SWIFT;

/**
 The local space transforms for each joint.

 Local space refers to a joint's position relative to its parent joint.
 */
@property (nonatomic, readonly) const simd_float4x4 *jointLocalTransforms NS_REFINED_FOR_SWIFT;

/**
 Returns the model transform for a joint with a given name.

 Model space refers to the joint's position relative to its hip joint. If an invalid joint name is passed in, the returned matrix will be filled with
 `NaN` values.

 - Parameter jointName: The name of the joint.

 - Returns: The model transform.
*/
- (simd_float4x4)modelTransformForJointName:(ARSkeletonJointName)jointName NS_REFINED_FOR_SWIFT;

/**
 Returns the local transform for a joint with a given name.

 Local space refers to the joint's position relative to its parent joint. If an invalid joint name is passed the returned matrix will be filled with
 `NaN` values.

 - Parameter jointName: The name of the joint.

 - Returns: The local transform.
*/
- (simd_float4x4)localTransformForJointName:(ARSkeletonJointName)jointName NS_REFINED_FOR_SWIFT;

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

/**
 An object that describes the locations of a body's joints in the camera feed.

 ``ARSkeleton2D`` provides you with a 2D body's joints in a flat hierarchy so you can access them efficiently. The joint locations are normalized
 within the range [0..1] in the coordinate space of the current frame's camera image, where 0 is the upper left, and 1 is the bottom right.

 To access a skeleton's joints by name, you use ``landmarkForJointNamed:``. To access a named joint by index (for example, for performance reasons),
 you query the definition for the named joint index using ``ARSkeletonDefinition/indexForJointName:``, then access ``jointLandmarks`` using the
 resulting index.
 */
API_AVAILABLE(ios(13.0))
NS_SWIFT_SENDABLE
@interface ARSkeleton2D : ARSkeleton

/**
 The joint landmarks in normalized coordinates.

 The joint landmarks are detected in the captured image on the `ARFrame`. The joint landmarks are normalized within the range [0..1] in the coordinate
 space of the current frame's camera image, where 0 is the upper left, and 1 is the bottom right.

 - SeeAlso: ``ARFrame/capturedImage``
*/
@property (nonatomic, readonly) const simd_float2 *jointLandmarks NS_REFINED_FOR_SWIFT;

/**
 Returns the location of a joint with a given name.

 Joint landmarks are normalized within the range [0..1] and are in the coordinate space of the current frame's camera image, where 0 is the upper
 left, and 1 is the bottom right. If an invalid joint name is passed the returned point will be filled with `NaN` values.

 - Parameter jointName: The name of the joint.

 - Returns: Landmark in normalized image coordinates.
*/
- (simd_float2)landmarkForJointNamed:(ARSkeletonJointName)jointName NS_REFINED_FOR_SWIFT;

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

/**
 Returns a joint name that corresponds to a key point defined in a human body pose.

 This function matches human body key points defined by the Vision framework with joint names defined by ARKit. This function may return `nil` if the
 key point doesn't map to a joint name. For more information about key points, see
 <doc://com.apple.documentation/documentation/vision/detecting-human-body-poses-in-images>.

 - Parameter recognizedPointKey: The argument key point.

 - Returns: Joint name that could be mapped to a `ARSkeleton2D`. `nil` if no mapping exists.

 - SeeAlso: `VNRecognizedPointKey`
 - SeeAlso: `VNDetectHumanBodyPoseRequest`
*/
FOUNDATION_EXTERN __nullable ARSkeletonJointName ARSkeletonJointNameForRecognizedPointKey(VNRecognizedPointKey recognizedPointKey)
    NS_SWIFT_NAME(ARSkeletonJointName.init(_:)) API_AVAILABLE(ios(14.0));

API_UNAVAILABLE_END

NS_ASSUME_NONNULL_END
