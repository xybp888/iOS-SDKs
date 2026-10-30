//
//  ARFaceAnchor.h
//  ARKit
//
//  Copyright © 2016-2021 Apple Inc. All rights reserved.
//

#import <ARKitCore/ARAnchor.h>
#import <CoreGraphics/CoreGraphics.h>

NS_ASSUME_NONNULL_BEGIN

API_UNAVAILABLE_BEGIN(visionos)

/**
 Identifiers for specific facial features, for use with coefficients describing the relative movements of those features.

 The ``ARFaceAnchor/blendShapes`` dictionary provided by an ``ARFaceAnchor`` object describes the facial expression of a detected face in terms of the
 movements of specific facial features. For each key in the dictionary, the corresponding value is a floating point number indicating the current
 position of that feature relative to its neutral configuration, ranging from `0.0` (neutral) to `1.0` (maximum movement).

 ARKit provides many blend shape coefficients, resulting in a detailed model of a facial expression; however, you can use as many or as few of the
 coefficients as you desire to create a visual effect. For example, you might animate a simple cartoon character using only the ``jawOpen``,
 ``eyeBlinkLeft``, and ``eyeBlinkRight`` coefficients. A professional 3D artist could create a detailed character model rigged for realistic animation
 using a larger set, or the entire set, of coefficients.

 > Note:
 > In the naming of blend shape coefficients, the left and right directions are relative to the face. That is, the ``eyeBlinkRight`` coefficient
 refers to the face's right eye. ARKit views running a face-tracking session mirror the camera image, so the face's right eye appears on the right
 side in the view.

 - Note: Blend shapes are computed based on the captured image. For example, if the detected person has a closed right eye, the eye on the left side
 of the captured image will appear closed and reported as blend shape activation by ARKit.

 - SeeAlso: ``ARFrame/capturedImage``
*/
typedef NSString *ARBlendShapeLocation NS_STRING_ENUM NS_SWIFT_NAME(ARFaceAnchor.BlendShapeLocation) API_AVAILABLE(ios(11.0));
/** The coefficient describing downward movement of the outer portion of the left eyebrow. */
FOUNDATION_EXTERN ARBlendShapeLocation const ARBlendShapeLocationBrowDownLeft API_AVAILABLE(ios(11.0));
/** The coefficient describing downward movement of the outer portion of the right eyebrow. */
FOUNDATION_EXTERN ARBlendShapeLocation const ARBlendShapeLocationBrowDownRight API_AVAILABLE(ios(11.0));
/** The coefficient describing upward movement of the inner portion of both eyebrows. */
FOUNDATION_EXTERN ARBlendShapeLocation const ARBlendShapeLocationBrowInnerUp API_AVAILABLE(ios(11.0));
/** The coefficient describing upward movement of the outer portion of the left eyebrow. */
FOUNDATION_EXTERN ARBlendShapeLocation const ARBlendShapeLocationBrowOuterUpLeft API_AVAILABLE(ios(11.0));
/** The coefficient describing upward movement of the outer portion of the right eyebrow. */
FOUNDATION_EXTERN ARBlendShapeLocation const ARBlendShapeLocationBrowOuterUpRight API_AVAILABLE(ios(11.0));
/** The coefficient describing outward movement of both cheeks. */
FOUNDATION_EXTERN ARBlendShapeLocation const ARBlendShapeLocationCheekPuff API_AVAILABLE(ios(11.0));
/** The coefficient describing upward movement of the cheek around and below the left eye. */
FOUNDATION_EXTERN ARBlendShapeLocation const ARBlendShapeLocationCheekSquintLeft API_AVAILABLE(ios(11.0));
/** The coefficient describing upward movement of the cheek around and below the right eye. */
FOUNDATION_EXTERN ARBlendShapeLocation const ARBlendShapeLocationCheekSquintRight API_AVAILABLE(ios(11.0));
/** The coefficient describing closure of the eyelids over the left eye. */
FOUNDATION_EXTERN ARBlendShapeLocation const ARBlendShapeLocationEyeBlinkLeft API_AVAILABLE(ios(11.0));
/** The coefficient describing closure of the eyelids over the right eye. */
FOUNDATION_EXTERN ARBlendShapeLocation const ARBlendShapeLocationEyeBlinkRight API_AVAILABLE(ios(11.0));
/** The coefficient describing movement of the left eyelids consistent with a downward gaze. */
FOUNDATION_EXTERN ARBlendShapeLocation const ARBlendShapeLocationEyeLookDownLeft API_AVAILABLE(ios(11.0));
/** The coefficient describing movement of the right eyelids consistent with a downward gaze. */
FOUNDATION_EXTERN ARBlendShapeLocation const ARBlendShapeLocationEyeLookDownRight API_AVAILABLE(ios(11.0));
/** The coefficient describing movement of the left eyelids consistent with a rightward gaze. */
FOUNDATION_EXTERN ARBlendShapeLocation const ARBlendShapeLocationEyeLookInLeft API_AVAILABLE(ios(11.0));
/** The coefficient describing movement of the right eyelids consistent with a leftward gaze. */
FOUNDATION_EXTERN ARBlendShapeLocation const ARBlendShapeLocationEyeLookInRight API_AVAILABLE(ios(11.0));
/** The coefficient describing movement of the left eyelids consistent with a leftward gaze. */
FOUNDATION_EXTERN ARBlendShapeLocation const ARBlendShapeLocationEyeLookOutLeft API_AVAILABLE(ios(11.0));
/** The coefficient describing movement of the right eyelids consistent with a rightward gaze. */
FOUNDATION_EXTERN ARBlendShapeLocation const ARBlendShapeLocationEyeLookOutRight API_AVAILABLE(ios(11.0));
/** The coefficient describing movement of the left eyelids consistent with an upward gaze. */
FOUNDATION_EXTERN ARBlendShapeLocation const ARBlendShapeLocationEyeLookUpLeft API_AVAILABLE(ios(11.0));
/** The coefficient describing movement of the right eyelids consistent with an upward gaze. */
FOUNDATION_EXTERN ARBlendShapeLocation const ARBlendShapeLocationEyeLookUpRight API_AVAILABLE(ios(11.0));
/** The coefficient describing contraction of the face around the left eye. */
FOUNDATION_EXTERN ARBlendShapeLocation const ARBlendShapeLocationEyeSquintLeft API_AVAILABLE(ios(11.0));
/** The coefficient describing contraction of the face around the right eye. */
FOUNDATION_EXTERN ARBlendShapeLocation const ARBlendShapeLocationEyeSquintRight API_AVAILABLE(ios(11.0));
/** The coefficient describing a widening of the eyelids around the left eye. */
FOUNDATION_EXTERN ARBlendShapeLocation const ARBlendShapeLocationEyeWideLeft API_AVAILABLE(ios(11.0));
/** The coefficient describing a widening of the eyelids around the right eye. */
FOUNDATION_EXTERN ARBlendShapeLocation const ARBlendShapeLocationEyeWideRight API_AVAILABLE(ios(11.0));
/** The coefficient describing forward movement of the lower jaw. */
FOUNDATION_EXTERN ARBlendShapeLocation const ARBlendShapeLocationJawForward API_AVAILABLE(ios(11.0));
/** The coefficient describing leftward movement of the lower jaw. */
FOUNDATION_EXTERN ARBlendShapeLocation const ARBlendShapeLocationJawLeft API_AVAILABLE(ios(11.0));
/** The coefficient describing an opening of the lower jaw. */
FOUNDATION_EXTERN ARBlendShapeLocation const ARBlendShapeLocationJawOpen API_AVAILABLE(ios(11.0));
/** The coefficient describing rightward movement of the lower jaw. */
FOUNDATION_EXTERN ARBlendShapeLocation const ARBlendShapeLocationJawRight API_AVAILABLE(ios(11.0));
/**
 The coefficient describing closure of the lips _independent of jaw position_.

 This coefficient describes a closing of the lips without relation to the position of the jaw (the ``ARFaceAnchor/BlendShapeLocation/jawOpen``
 coefficient), so some values of the ``ARFaceAnchor/BlendShapeLocation/mouthClose`` coefficient can produce unrealistic facial expressions unless
 other coefficients are also set to realistic values.
*/
FOUNDATION_EXTERN ARBlendShapeLocation const ARBlendShapeLocationMouthClose API_AVAILABLE(ios(11.0));
/** The coefficient describing backward movement of the left corner of the mouth. */
FOUNDATION_EXTERN ARBlendShapeLocation const ARBlendShapeLocationMouthDimpleLeft API_AVAILABLE(ios(11.0));
/** The coefficient describing backward movement of the right corner of the mouth. */
FOUNDATION_EXTERN ARBlendShapeLocation const ARBlendShapeLocationMouthDimpleRight API_AVAILABLE(ios(11.0));
/** The coefficient describing downward movement of the left corner of the mouth. */
FOUNDATION_EXTERN ARBlendShapeLocation const ARBlendShapeLocationMouthFrownLeft API_AVAILABLE(ios(11.0));
/** The coefficient describing downward movement of the right corner of the mouth. */
FOUNDATION_EXTERN ARBlendShapeLocation const ARBlendShapeLocationMouthFrownRight API_AVAILABLE(ios(11.0));
/** The coefficient describing contraction of both lips into an open shape. */
FOUNDATION_EXTERN ARBlendShapeLocation const ARBlendShapeLocationMouthFunnel API_AVAILABLE(ios(11.0));
/** The coefficient describing leftward movement of both lips together. */
FOUNDATION_EXTERN ARBlendShapeLocation const ARBlendShapeLocationMouthLeft API_AVAILABLE(ios(11.0));
/** The coefficient describing downward movement of the lower lip on the left side. */
FOUNDATION_EXTERN ARBlendShapeLocation const ARBlendShapeLocationMouthLowerDownLeft API_AVAILABLE(ios(11.0));
/** The coefficient describing downward movement of the lower lip on the right side. */
FOUNDATION_EXTERN ARBlendShapeLocation const ARBlendShapeLocationMouthLowerDownRight API_AVAILABLE(ios(11.0));
/** The coefficient describing upward compression of the lower lip on the left side. */
FOUNDATION_EXTERN ARBlendShapeLocation const ARBlendShapeLocationMouthPressLeft API_AVAILABLE(ios(11.0));
/** The coefficient describing upward compression of the lower lip on the right side. */
FOUNDATION_EXTERN ARBlendShapeLocation const ARBlendShapeLocationMouthPressRight API_AVAILABLE(ios(11.0));
/** The coefficient describing contraction and compression of both closed lips. */
FOUNDATION_EXTERN ARBlendShapeLocation const ARBlendShapeLocationMouthPucker API_AVAILABLE(ios(11.0));
/** The coefficient describing rightward movement of both lips together. */
FOUNDATION_EXTERN ARBlendShapeLocation const ARBlendShapeLocationMouthRight API_AVAILABLE(ios(11.0));
/** The coefficient describing movement of the lower lip toward the inside of the mouth. */
FOUNDATION_EXTERN ARBlendShapeLocation const ARBlendShapeLocationMouthRollLower API_AVAILABLE(ios(11.0));
/** The coefficient describing movement of the upper lip toward the inside of the mouth. */
FOUNDATION_EXTERN ARBlendShapeLocation const ARBlendShapeLocationMouthRollUpper API_AVAILABLE(ios(11.0));
/** The coefficient describing outward movement of the lower lip. */
FOUNDATION_EXTERN ARBlendShapeLocation const ARBlendShapeLocationMouthShrugLower API_AVAILABLE(ios(11.0));
/** The coefficient describing outward movement of the upper lip. */
FOUNDATION_EXTERN ARBlendShapeLocation const ARBlendShapeLocationMouthShrugUpper API_AVAILABLE(ios(11.0));
/** The coefficient describing upward movement of the left corner of the mouth. */
FOUNDATION_EXTERN ARBlendShapeLocation const ARBlendShapeLocationMouthSmileLeft API_AVAILABLE(ios(11.0));
/** The coefficient describing upward movement of the right corner of the mouth. */
FOUNDATION_EXTERN ARBlendShapeLocation const ARBlendShapeLocationMouthSmileRight API_AVAILABLE(ios(11.0));
/** The coefficient describing leftward movement of the left corner of the mouth. */
FOUNDATION_EXTERN ARBlendShapeLocation const ARBlendShapeLocationMouthStretchLeft API_AVAILABLE(ios(11.0));
/** The coefficient describing rightward movement of the right corner of the mouth. */
FOUNDATION_EXTERN ARBlendShapeLocation const ARBlendShapeLocationMouthStretchRight API_AVAILABLE(ios(11.0));
/** The coefficient describing upward movement of the upper lip on the left side. */
FOUNDATION_EXTERN ARBlendShapeLocation const ARBlendShapeLocationMouthUpperUpLeft API_AVAILABLE(ios(11.0));
/** The coefficient describing upward movement of the upper lip on the right side. */
FOUNDATION_EXTERN ARBlendShapeLocation const ARBlendShapeLocationMouthUpperUpRight API_AVAILABLE(ios(11.0));
/** The coefficient describing a raising of the left side of the nose around the nostril. */
FOUNDATION_EXTERN ARBlendShapeLocation const ARBlendShapeLocationNoseSneerLeft API_AVAILABLE(ios(11.0));
/** The coefficient describing a raising of the right side of the nose around the nostril. */
FOUNDATION_EXTERN ARBlendShapeLocation const ARBlendShapeLocationNoseSneerRight API_AVAILABLE(ios(11.0));
/** The coefficient describing extension of the tongue. */
FOUNDATION_EXTERN ARBlendShapeLocation const ARBlendShapeLocationTongueOut API_AVAILABLE(ios(12.0));

@class ARFaceGeometry;

/**
 An anchor for a unique face that is visible in the front-facing camera.

 The session automatically adds an ``ARFaceAnchor`` object to its list of anchors when it detects a unique face in the front camera feed.

 When you track faces using ``ARFaceTrackingConfiguration``, ARKit can track multiple faces simultaneously. Alternatively, you can enable face
 tracking with a world tracking configuration.

 ### Tracking Face Position and Orientation

 The inherited ``ARAnchor/transform`` property describes the face's current position and orientation in world coordinates; that is, in a coordinate
 space relative to that specified by the ``ARConfiguration/worldAlignment`` property of the session configuration. Use this transform matrix to
 position virtual content you want to "attach" to the face in your AR scene.

 This transform matrix creates a face coordinate system for positioning other elements relative to the face. Units of face coordinate space are in
 meters, with the origin centered behind the face.

 The coordinate system is right-handed—the positive x direction points to the viewer's right (that is, the face's own left), the positive y direction
 points up (relative to the face itself, not to the world), and the positive z direction points outward from the face (toward the viewer).

 ### Using Face Topology

 The ``geometry`` property provides an ``ARFaceGeometry`` object representing detailed topology for the face, which conforms a generic face model to
 match the dimensions, shape, and current expression of the detected face.

 You can use this model as the basis for overlaying content that follows the shape of the user's face—for example, to apply virtual makeup or tattoos.
 You can also use this model to create _occlusion geometry_—a 3D model that doesn't render any visible content (allowing the camera image to show
 through), but that obstructs the camera's view of other virtual content in the scene.

 ### Tracking Facial Expressions

 The ``blendShapes`` property provides a high-level model of the current facial expression, described via a series of many named coefficients that
 represent the movement of specific facial features relative to their neutral configurations. You can use blend shape coefficients to animate 2D or 3D
 content, such as a character or avatar, in ways that follow the user's facial expressions.
 */
API_AVAILABLE(ios(11.0))
NS_SWIFT_SENDABLE
@interface ARFaceAnchor : ARAnchor <ARTrackable>

/**
 A coarse triangle mesh representing the topology of the detected face.

 This mesh provides vertex, index, and texture coordinate buffers describing the 3D shape of the face, conforming a generic face model to match the
 dimensions, shape, and current expression of the detected face.

 You can visualize the face geometry by passing these buffers to your preferred rendering engine. To visualize a face geometry using SceneKit, create
 an ``ARSCNFaceGeometry`` instance and use its ``ARSCNFaceGeometry/update(from:)`` method to update it to match the face geometry.
 */
@property (nonatomic, strong, readonly) ARFaceGeometry *geometry;

/**
 A transform matrix indicating the position and orientation of the face's left eye.

 The translation aspect of this matrix indicates the position of the center of the eyeball, relative to the position represented by the anchor's
 ``ARAnchor/transform``. The positive z-axis points from the center of the eyeball in the direction of the pupil.

 Rotational aspects of the matrix indicate the orientation of the eyeball—for example, a rotation about the x-axis directs the pupil upward or
 downward. The eye does not rotate about the z-axis.
 */
@property (nonatomic, assign, readonly) simd_float4x4 leftEyeTransform API_AVAILABLE(ios(12.0));

/**
 A transform matrix indicating the position and orientation of the face's right eye.

 The translation aspect of this matrix indicates the position of the center of the eyeball, relative to the position represented by the anchor's
 ``ARAnchor/transform``. The positive z-axis points from the center of the eyeball in the direction of the pupil.

 Rotational aspects of the matrix indicate the orientation of the eyeball—for example, a rotation about the x-axis directs the pupil upward or
 downward. The eye does not rotate about the z-axis.
 */
@property (nonatomic, assign, readonly) simd_float4x4 rightEyeTransform API_AVAILABLE(ios(12.0));

/**
 A position in face coordinate space estimating the direction of the face's gaze.

 This vector abstracts from the ``leftEyeTransform`` and ``rightEyeTransform`` matrices to estimate what point, relative to the face, the user's eyes
 are focused upon. For example:

 - If the user is looking to the left, the vector has a positive x-axis component.
 - If the user is focused on a nearby object, the vector's length is shorter.
 - If the user is focused on a faraway object, the vector's length is longer.
 */
@property (nonatomic, assign, readonly) simd_float3 lookAtPoint API_AVAILABLE(ios(12.0));

/**
 A dictionary of named coefficients representing the detected facial expression in terms of the movement of specific facial features.

 Each key in this dictionary (an ``ARFaceAnchor/BlendShapeLocation`` constant) represents one of many specific facial features recognized by ARKit.
 The corresponding value for each key is a floating point number indicating the current position of that feature relative to its neutral
 configuration, ranging from `0.0` (neutral) to `1.0` (maximum movement).

 You can use blend shape coefficients to animate a 2D or 3D character in ways that follow the user's facial expressions. ARKit provides many blend
 shape coefficients, resulting in a detailed model of a facial expression; however, you can use as many or as few of the coefficients as you desire to
 create a visual effect. For example, you might animate a simple cartoon character using only the ``ARFaceAnchor/BlendShapeLocation/jawOpen``,
 ``ARFaceAnchor/BlendShapeLocation/eyeBlinkLeft``, and ``ARFaceAnchor/BlendShapeLocation/eyeBlinkRight`` coefficients. A professional 3D artist could
 create a detailed character model rigged for realistic animation using a larger set, or the entire set, of coefficients.

 You can also use blend shape coefficients to record a specific facial expression and reuse it later. The ``ARFaceGeometry``
 ``ARFaceGeometry/init(blendShapes:)`` initializer creates a detailed 3D mesh from a dictionary equivalent to this property's value; the serialized
 form of a blend shapes dictionary is more portable than that of the face mesh those coefficients describe.
 */
@property (nonatomic, strong, readonly) NSDictionary<ARBlendShapeLocation, NSNumber *> *blendShapes;

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
