//
//  ARSkeletonDefinition.h
//  ARKit
//
//  Copyright © 2019 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

API_UNAVAILABLE_BEGIN(visionos)

/**
 A name identifier for a joint.

 Use this type to access information about a named joint, such as its index in a skeleton's array of joints, or its position on the screen or in the
 physical environment.

 When you're tracking a body in 2D space, you get the screen-space position of a named joint by using the ``ARSkeleton2D/landmark(for:)`` function.

 When you're tracking a body in 3D space, you get a named joint's position in either local or model space by using the
 ``ARSkeleton3D/localTransform(for:)`` or ``ARSkeleton3D/modelTransform(for:)`` functions, respectively.
*/
typedef NSString *ARSkeletonJointName NS_TYPED_ENUM NS_SWIFT_NAME(ARSkeleton.JointName) API_AVAILABLE(ios(13.0));

/**
 A skeletal joint that's the root of all other joints.

 The root skeletal joint is at the hip, and is located at the origin of its associated body anchor.
*/
FOUNDATION_EXTERN ARSkeletonJointName const ARSkeletonJointNameRoot API_AVAILABLE(ios(13.0));

/**
 A skeletal joint that ARKit tracks representing the head.
*/
FOUNDATION_EXTERN ARSkeletonJointName const ARSkeletonJointNameHead API_AVAILABLE(ios(13.0));

/**
 A skeletal joint that ARKit tracks representing the left hand.
*/
FOUNDATION_EXTERN ARSkeletonJointName const ARSkeletonJointNameLeftHand API_AVAILABLE(ios(13.0));

/**
 A skeletal joint that ARKit tracks representing the right hand.
*/
FOUNDATION_EXTERN ARSkeletonJointName const ARSkeletonJointNameRightHand API_AVAILABLE(ios(13.0));

/**
 A skeletal joint that ARKit tracks representing the left foot.
*/
FOUNDATION_EXTERN ARSkeletonJointName const ARSkeletonJointNameLeftFoot API_AVAILABLE(ios(13.0));

/**
 A skeletal joint that ARKit tracks representing the right foot.
*/
FOUNDATION_EXTERN ARSkeletonJointName const ARSkeletonJointNameRightFoot API_AVAILABLE(ios(13.0));

/**
 A skeletal joint that ARKit tracks representing the left shoulder.
*/
FOUNDATION_EXTERN ARSkeletonJointName const ARSkeletonJointNameLeftShoulder API_AVAILABLE(ios(13.0));

/**
 A skeletal joint that ARKit tracks representing the right shoulder.
*/
FOUNDATION_EXTERN ARSkeletonJointName const ARSkeletonJointNameRightShoulder API_AVAILABLE(ios(13.0));

@class ARSkeleton2D;
@class ARSkeleton3D;

/**
 The hierarchy of joints and their names.

 A skeleton definition establishes the relationship of joints that make up a 3D or 2D body's ``ARBodyAnchor/skeleton`` or ``ARBody2D/skeleton``, in
 which joints connect to other joints to compose a single skeleton in a parent-child hierarchy. Use ``parentIndices`` to identify the hierarchy for a
 given skeleton definition.

 ARKit names particular joints that are crucial to body tracking. You can access named joints by calling ``indexForJointName:`` and passing in one of
 the available ``jointNames`` identifiers.
*/
API_AVAILABLE(ios(13.0))
NS_SWIFT_SENDABLE
@interface ARSkeletonDefinition : NSObject

/**
 The default skeleton definition for bodies defined in 3D.

 - Note: The default height of this skeleton, measured from lowest to highest joint in standing position, is defined to be `1.71` meters.

 - SeeAlso: ``ARSkeleton3D``
*/
@property (class, nonatomic, readonly) ARSkeletonDefinition *defaultBody3DSkeletonDefinition;

/**
 The default skeleton definition for bodies defined in 2D.

 - SeeAlso: ``ARBody2D``
 */
@property (class, nonatomic, readonly) ARSkeletonDefinition *defaultBody2DSkeletonDefinition;

/**
 The skeleton's total number of joints.
 */
@property (nonatomic, readonly) NSUInteger jointCount;

/**
 A collection of unique joint names.

 Refer to this array to convert a joint index to a joint identifier.
 */
@property (nonatomic, readonly) NSArray<NSString *> *jointNames;

/**
 The parent index for each joint.

 This property may be used to identify the hierarchical dependency between joints. If a line is drawn for every joint and its parent joint, the result
 is a visualization of the underlying skeleton. The joint with no parent is denoted as the root joint. The root joint's parent index is `-1`.
*/
@property (nonatomic, readonly) NSArray<NSNumber *> *parentIndices NS_REFINED_FOR_SWIFT;

/**
 The 3D skeleton in neutral pose.

 The neutral skeleton pose assumes a standardized size of the skeleton in meters. The neutral pose is defined as the skeleton's T-pose. This skeleton
 is provided to you for reference to all other possible skeleton poses.
*/
@property (nonatomic, nullable, readonly) ARSkeleton3D *neutralBodySkeleton3D;

/**
 Returns the index for a given joint identifier.

 This function returns `NSNotFound` if an invalid joint name is passed in.

 - Parameter jointName: Name of a given joint.

 - Returns: The joint index.
*/
- (NSUInteger)indexForJointName:(ARSkeletonJointName)jointName NS_REFINED_FOR_SWIFT;

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

API_UNAVAILABLE_END

NS_ASSUME_NONNULL_END
