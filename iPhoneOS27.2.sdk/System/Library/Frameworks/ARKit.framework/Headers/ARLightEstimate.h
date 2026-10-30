#if (defined(USE_ARKIT_PUBLIC_HEADERS) && USE_ARKIT_PUBLIC_HEADERS) || !__has_include(<ARKitCore/ARLightEstimate.h>)
//
//  ARLightEstimate.h
//  ARKit
//
//  Copyright © 2016-2021 Apple Inc. All rights reserved.
//

#import <CoreGraphics/CoreGraphics.h>
#import <Foundation/Foundation.h>
#import <simd/simd.h>

NS_ASSUME_NONNULL_BEGIN

API_UNAVAILABLE_BEGIN(visionos)

/**
 Estimated scene lighting information associated with a captured video frame in an AR session.

 If you enable the ``ARConfiguration/isLightEstimationEnabled`` setting, ARKit provides light estimates in the ``ARFrame/lightEstimate`` property of
 each ``ARFrame`` it delivers.

 If you render your own overlay graphics for the AR scene, you can use this information in shading algorithms to help make those graphics match the
 real-world lighting conditions of the scene captured by the camera. The ``ARSCNView`` class automatically uses this information to configure SceneKit
 lighting.
 */
API_AVAILABLE(ios(11.0))
NS_SWIFT_SENDABLE
@interface ARLightEstimate : NSObject

/**
 The estimated intensity, in lumens, of ambient light throughout the scene.

 This value is based on the internal exposure compensation of the camera device, and scaled to be appropriate for use in rendering architectures that
 use realistic lighting metrics. A value of 1000 represents "neutral" lighting, and the value typically ranges from 0 (very dark) to around 2000 (very
 bright).

 For example, you can pass this value directly to the <doc://com.apple.documentation/documentation/scenekit/scnlight/intensity> property of a SceneKit
 ambient light for lighting results that roughly match those of the real-world scene captured by the device camera. (However, passing this value to
 SceneKit is generally not necessary; the ``ARSCNView`` class automatically sets SceneKit lighting based on this value.)
*/
@property (nonatomic, readonly) CGFloat ambientIntensity;

/**
 The estimated color temperature, in degrees Kelvin, of ambient light throughout the scene.

 This value is based on the internal white balance compensation of the camera device, and scaled to be appropriate for use in rendering architectures
 that use realistic lighting metrics. A value of 6500 represents neutral (pure white) lighting; lower values indicate a "warmer" yellow or orange
 tint, and higher values indicate a "cooler" blue tint.

 For example, you can pass this value directly to the <doc://com.apple.documentation/documentation/scenekit/scnlight/temperature> property of a
 SceneKit ambient light for lighting results that roughly match those of the real-world scene captured by the device camera. (However, passing this
 value to SceneKit is generally not necessary; the ``ARSCNView`` class automatically sets SceneKit lighting based on this value.)
*/
@property (nonatomic, readonly) CGFloat ambientColorTemperature;

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
 Estimated environmental lighting information associated with a captured video frame in a face-tracking AR session.

 When you run a face tracking AR session (see ``ARFaceTrackingConfiguration``) with the ``ARConfiguration/isLightEstimationEnabled`` property set to
 <doc://com.apple.documentation/documentation/swift/true>, ARKit uses the detected face as a light probe to estimate the directional lighting
 environment in the scene. The ``ARFrame/lightEstimate`` property of each frame vended by the session contains an ``ARDirectionalLightEstimate``
 instance containing this information.

 If you render your own overlay graphics for the AR scene, you can use this information in shading algorithms to help make those graphics match the
 real-world lighting conditions of the scene captured by the camera. (The ``ARSCNView`` class automatically uses this information to configure
 SceneKit lighting.)
 */
API_AVAILABLE(ios(11.0))
NS_SWIFT_SENDABLE
@interface ARDirectionalLightEstimate : ARLightEstimate

/**
 Data describing the estimated lighting environment in all directions.

 Spherical harmonics provide a compact mathematical model for the global lighting environment around a point in space, describing the distribution and
 colors of multiple directional light sources. When used in a renderer that supports environment-based lighting, spherical harmonics provide much less
 high-frequency detail than a cube map texture, but make much more efficient use of GPU resources.

 ARKit provides second-level spherical harmonics in separate red, green, and blue data planes. Thus, this data buffer contains 3 sets of 9
 coefficients, or a total of 27 values of 32-bit floating point type.
*/
@property (nonatomic, copy, readonly) NSData *sphericalHarmonicsCoefficients;

/**
 A vector indicating the orientation of the strongest directional light source in the scene.

 When ARKit analyzes the directional lighting environment for a detected face, the resulting lighting estimate can represent the influence of multiple
 light sources with different directions and intensities. To access this level of detail for use in your custom rendering code, use the
 ``ARDirectionalLightEstimate/sphericalHarmonicsCoefficients`` property.

 If your app displays AR content using a technology that doesn't support environment-based lighting, this
 ``ARDirectionalLightEstimate/primaryLightDirection`` property represents the average of directional light sources in the scene. This vector is
 normalized and in world coordinate space.
 */
@property (nonatomic, readonly) simd_float3 primaryLightDirection;

/**
 The estimated intensity, in lumens, of the strongest directional light source in the scene.

 When ARKit analyzes the directional lighting environment for a detected face, the resulting lighting estimate can represent the influence of multiple
 light sources with different directions and intensities. To access this level of detail for use in your custom rendering code, use the
 ``ARDirectionalLightEstimate/sphericalHarmonicsCoefficients`` property.

 If your app displays AR content using a technology that doesn't support environment-based lighting, this
 ``ARDirectionalLightEstimate/primaryLightIntensity`` property represents the average of directional light sources in the scene. This value is scaled
 to be appropriate for use in rendering architectures that use realistic lighting metrics, with a value of 1000 representing neutral lighting.

 For example, you can pass this value directly to the <doc://com.apple.documentation/documentation/scenekit/scnlight/intensity> property of a SceneKit
 directional light for lighting results that roughly match those of the real-world scene captured by the device camera. (However, passing this value
 to SceneKit is generally not necessary; the ``ARSCNView`` class automatically sets SceneKit lighting based on the
 ``ARDirectionalLightEstimate/sphericalHarmonicsCoefficients`` property.)
 */
@property (nonatomic, readonly) CGFloat primaryLightIntensity;

@end

API_UNAVAILABLE_END

NS_ASSUME_NONNULL_END
#else
#import <ARKitCore/ARLightEstimate.h> 
#endif // #if (defined(USE_ARKIT_PUBLIC_HEADERS) \&\& USE_ARKIT_PUBLIC_HEADERS) || !__has_include(<ARKitCore/ARLightEstimate.h>)