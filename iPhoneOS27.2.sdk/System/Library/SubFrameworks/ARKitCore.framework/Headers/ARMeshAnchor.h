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

/**
 An anchor for a physical object that ARKit detects and recreates virtually using a polygonal mesh.

 ARKit subdivides the reconstructed, real-world scene surrounding the user into mesh anchors.

 Mesh anchors constantly update their data as ARKit refines its understanding of the real world. Although ARKit updates a mesh to reflect a change in
 the physical environment (such as when a person pulls out a chair), the mesh's subsequent change is not intended to reflect in real time.
 */
API_AVAILABLE(ios(13.4))
NS_SWIFT_SENDABLE
@interface ARMeshAnchor : ARAnchor

/**
 3D information about the mesh such as its shape and classifications.

 Contains the anchor's portion of mesh data that, with any other mesh anchors in the AR session, collectively reconstruct the scene around the user.
 The mesh anchor records this data in its own coordinate system.
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
