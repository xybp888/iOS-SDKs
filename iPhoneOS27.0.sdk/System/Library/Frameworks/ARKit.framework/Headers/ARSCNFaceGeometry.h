#if (defined(USE_ARKIT_PUBLIC_HEADERS) && USE_ARKIT_PUBLIC_HEADERS) || !__has_include(<ARKitUI/ARSCNFaceGeometry.h>)
//
//  ARSCNFaceGeometry.h
//  ARKit
//
//  Copyright © 2016-2021 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <SceneKit/SCNGeometry.h>

@protocol MTLDevice;

API_UNAVAILABLE_BEGIN(visionos)

@class ARFaceGeometry;

NS_ASSUME_NONNULL_BEGIN

/**
 A SceneKit geometry representing a face.
 */
API_AVAILABLE(ios(11.0))
@interface ARSCNFaceGeometry : SCNGeometry

/**
 Creates a new face geometry using a Metal device.

 - Parameter device: A Metal device.

 - Returns: A new face geometry.
*/
+ (nullable instancetype)faceGeometryWithDevice:(id<MTLDevice>)device;

/**
 Creates a new face geometry using a Metal device.

 By default the regions between the eye lids as well as the region
 between the lips are not covered by geometry. For using the face geometry as an
 occlusion geometry set \p fillMesh to YES. This will fill
 in additional geometry into the gaps between the eye lids as well as into the
 gap between the lips.

 - Parameters:
   - device: A Metal device.
   - fillMesh: Whether to fill in additional geometry into the
     gaps between the eye lids as well as into the gap between the lips.

 - Returns: A new face geometry.
*/
+ (nullable instancetype)faceGeometryWithDevice:(id<MTLDevice>)device fillMesh:(BOOL)fillMesh;

/**
 Updates the geometry with the vertices of a face geometry.

 - Parameter faceGeometry: A face geometry.
*/
- (void)updateFromFaceGeometry:(ARFaceGeometry *)faceGeometry;

/**
 Unavailable. ARSCNFaceGeometry objects are created by the system.

 - Returns: This method is unavailable.
*/
- (instancetype)init NS_UNAVAILABLE;

/**
 Unavailable. ARSCNFaceGeometry objects are created by the system.

 - Returns: This method is unavailable.
*/
+ (instancetype)new NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END

API_UNAVAILABLE_END
#else
#import <ARKitUI/ARSCNFaceGeometry.h> 
#endif // #if (defined(USE_ARKIT_PUBLIC_HEADERS) \&\& USE_ARKIT_PUBLIC_HEADERS) || !__has_include(<ARKitUI/ARSCNFaceGeometry.h>)