#if (defined(USE_ARKIT_PUBLIC_HEADERS) && USE_ARKIT_PUBLIC_HEADERS) || !__has_include(<ARKitUI/ARSCNPlaneGeometry.h>)
//
//  ARSCNPlaneGeometry.h
//  ARKit
//
//  Copyright © 2016-2021 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <SceneKit/SCNGeometry.h>

@protocol MTLDevice;

API_UNAVAILABLE_BEGIN(visionos)

@class ARPlaneGeometry;

NS_ASSUME_NONNULL_BEGIN

/**
 A SceneKit geometry representing a plane.
 */
API_AVAILABLE(ios(11.3))
@interface ARSCNPlaneGeometry : SCNGeometry

/**
 Creates a new plane geometry using a Metal device.

 - Parameter device: A Metal device.

 - Returns: A new plane geometry.
*/
+ (nullable instancetype)planeGeometryWithDevice:(id<MTLDevice>)device;

/**
 Updates the geometry with the vertices of a plane geometry.

 - Parameter planeGeometry: A plane geometry.
*/
- (void)updateFromPlaneGeometry:(ARPlaneGeometry *)planeGeometry;

@end

NS_ASSUME_NONNULL_END

API_UNAVAILABLE_END
#else
#import <ARKitUI/ARSCNPlaneGeometry.h> 
#endif // #if (defined(USE_ARKIT_PUBLIC_HEADERS) \&\& USE_ARKIT_PUBLIC_HEADERS) || !__has_include(<ARKitUI/ARSCNPlaneGeometry.h>)