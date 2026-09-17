#if (defined(USE_ARKIT_PUBLIC_HEADERS) && USE_ARKIT_PUBLIC_HEADERS) || !__has_include(<ARKitCore/AREnvironmentProbeAnchor.h>)
//
//  AREnvironmentProbeAnchor.h
//  ARKit
//
//  Copyright © 2018 Apple Inc. All rights reserved.
//

#import <ARKit/ARAnchor.h>

@protocol MTLTexture;

NS_ASSUME_NONNULL_BEGIN

API_UNAVAILABLE_BEGIN(visionos)

/**
 An object representing an environment probe in the world.

 Environment probes are used to light virtual geometry by producing environment
 textures from the probe's location in the world.
*/
API_AVAILABLE(ios(12.0))
NS_SWIFT_SENDABLE
@interface AREnvironmentProbeAnchor : ARAnchor

/**
 The environment texture of the probe.

 The texture is provided as a cube using MTLTextureTypeCube.
*/
@property (nonatomic, strong, nullable, readonly) id<MTLTexture> environmentTexture;

/**
 The extent of the probe in the anchor's coordinate space.

 This is the size of the box that is assumed when projecting the environment texture for parallax correction.
 The extent defaults to infinity for probes that do not need parallax correction.
*/
@property (nonatomic, readonly) simd_float3 extent;

/**
 Initializes a new environment probe anchor with the provided transform and extent.

 - Parameters:
   - transform: The transformation matrix that defines the anchor's rotation, translation and scale in world coordinates.
   - extent: The extent of the probe in the anchor's coordinate space.

 - Returns: An initialized environment probe anchor.
*/
- (instancetype)initWithTransform:(simd_float4x4)transform extent:(simd_float3)extent;

/**
 Initializes a new environment probe anchor with the provided name, transform, and extent.

 - Parameters:
   - name: A name to associate with the anchor.
   - transform: The transformation matrix that defines the anchor's rotation, translation and scale in world coordinates.
   - extent: The extent of the probe in the anchor's coordinate space.

 - Returns: An initialized environment probe anchor.
*/
- (instancetype)initWithName:(NSString *)name transform:(simd_float4x4)transform extent:(simd_float3)extent API_UNAVAILABLE(visionos);

@end

API_UNAVAILABLE_END

NS_ASSUME_NONNULL_END
#else
#import <ARKitCore/AREnvironmentProbeAnchor.h> 
#endif // #if (defined(USE_ARKIT_PUBLIC_HEADERS) \&\& USE_ARKIT_PUBLIC_HEADERS) || !__has_include(<ARKitCore/AREnvironmentProbeAnchor.h>)