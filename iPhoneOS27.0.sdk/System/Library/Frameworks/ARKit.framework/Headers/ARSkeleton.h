#if (defined(USE_ARKIT_PUBLIC_HEADERS) && USE_ARKIT_PUBLIC_HEADERS) || !__has_include(<ARKitCore/ARSkeleton.h>)
//
//  ARSkeleton.h
//  ARKit
//
//  Copyright © 2019 Apple Inc. All rights reserved.
//

#import <ARKit/ARSkeletonDefinition.h>
#import <Foundation/Foundation.h>
#import <Vision/Vision.h>
#import <simd/simd.h>

NS_ASSUME_NONNULL_BEGIN

API_UNAVAILABLE_BEGIN(visionos)

/**
 An object representing a skeleton.

 A skeleton's structure is defined by a skeleton definition.

 - SeeAlso: ``ARSkeletonDefinition``
*/
API_AVAILABLE(ios(13.0))
NS_SWIFT_SENDABLE
@interface ARSkeleton : NSObject

/**
 Skeleton definition.
 */
@property (nonatomic, readonly) ARSkeletonDefinition *definition;

/**
 The number of joints.
 */
@property (nonatomic, readonly) NSUInteger jointCount NS_REFINED_FOR_SWIFT;

/**
 Tracking state for a given joint.

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
 An object representing a skeleton in 3D.
 */
API_AVAILABLE(ios(13.0))
NS_SWIFT_SENDABLE
@interface ARSkeleton3D : ARSkeleton

/**
 The model space transforms for each joint.
 */
@property (nonatomic, readonly) const simd_float4x4 *jointModelTransforms NS_REFINED_FOR_SWIFT;

/**
 The local space joint data for each joint.
 */
@property (nonatomic, readonly) const simd_float4x4 *jointLocalTransforms NS_REFINED_FOR_SWIFT;

/**
 Returns the model transform for a joint with a given name.

 If an invalid joint name is passed the returned matrix will be filled with `NaN` values.

 - Parameter jointName: The name of the joint.

 - Returns: The model transform.
*/
- (simd_float4x4)modelTransformForJointName:(ARSkeletonJointName)jointName NS_REFINED_FOR_SWIFT;

/**
 Returns the local transform for a joint with a given name.

 If an invalid joint name is passed the returned matrix will be filled with `NaN` values.

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
 An object representing a skeleton in 2D.
 */
API_AVAILABLE(ios(13.0))
NS_SWIFT_SENDABLE
@interface ARSkeleton2D : ARSkeleton

/**
 The joint landmarks in normalized coordinates.

 The joint landmarks are detected in the captured image on the `ARFrame`.

 - SeeAlso: ``ARFrame/capturedImage``
*/
@property (nonatomic, readonly) const simd_float2 *jointLandmarks NS_REFINED_FOR_SWIFT;

/**
 Returns the landmark point for a joint with a given name.

 If an invalid joint name is passed the returned point will be filled with `NaN` values.

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
 Returns the landmark joint name that corresponds to a key point defined in Vision framework.

 If an invalid key point is passed the returned point will be `nil`.

 - Parameter recognizedPointKey: Recognized key point.

 - Returns: Joint name that could be mapped to a `ARSkeleton2D`. `nil` if no mapping exists.

 - SeeAlso: `VNRecognizedPointKey`
 - SeeAlso: `VNDetectHumanBodyPoseRequest`
*/
FOUNDATION_EXTERN __nullable ARSkeletonJointName ARSkeletonJointNameForRecognizedPointKey(VNRecognizedPointKey recognizedPointKey)
    NS_SWIFT_NAME(ARSkeletonJointName.init(_:)) API_AVAILABLE(ios(14.0));

API_UNAVAILABLE_END

NS_ASSUME_NONNULL_END
#else
#import <ARKitCore/ARSkeleton.h> 
#endif // #if (defined(USE_ARKIT_PUBLIC_HEADERS) \&\& USE_ARKIT_PUBLIC_HEADERS) || !__has_include(<ARKitCore/ARSkeleton.h>)