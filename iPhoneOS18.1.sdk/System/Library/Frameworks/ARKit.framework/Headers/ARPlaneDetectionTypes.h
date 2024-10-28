#if (defined(USE_ARKIT_PUBLIC_HEADERS) && USE_ARKIT_PUBLIC_HEADERS) || !__has_include(<ARKitCore/ARPlaneDetectionTypes.h>)
//
//  ARPlaneDetectionTypes.h
//  ARKit
//
//  Copyright © 2016-2021 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

/**
 Option set indicating the type of planes to detect.
 */
API_AVAILABLE(ios(11.0))
typedef NS_OPTIONS(NSUInteger, ARPlaneDetection) {
    /** No plane detection is run. */
    ARPlaneDetectionNone                              = 0,

    /** Plane detection determines horizontal planes in the scene. */
    ARPlaneDetectionHorizontal                        = (1 << 0),

    /** Plane detection determines vertical planes in the scene. */
    ARPlaneDetectionVertical API_AVAILABLE(ios(11.3)) = (1 << 1),
    
} NS_SWIFT_NAME(ARWorldTrackingConfiguration.PlaneDetection);
#else
#import <ARKitCore/ARPlaneDetectionTypes.h> 
#endif // #if (defined(USE_ARKIT_PUBLIC_HEADERS) \&\& USE_ARKIT_PUBLIC_HEADERS) || !__has_include(<ARKitCore/ARPlaneDetectionTypes.h>)