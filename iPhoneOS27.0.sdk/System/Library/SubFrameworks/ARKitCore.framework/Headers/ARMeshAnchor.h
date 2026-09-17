//
//  ARMeshAnchor.h
//  ARKit
//
//  Copyright © 2019 Apple Inc. All rights reserved.
//

#import <ARKitCore/ARAnchor.h>

NS_ASSUME_NONNULL_BEGIN

API_UNAVAILABLE_BEGIN(visionos)

@class ARMeshGeometry;

/*
 An anchor representing a mesh in the world.
 */
API_AVAILABLE(ios(13.4))
NS_SWIFT_SENDABLE
@interface ARMeshAnchor : ARAnchor

/**
 Geometry of the mesh in anchor's coordinate system.
 */
@property (nonatomic, readonly) ARMeshGeometry *geometry;

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
