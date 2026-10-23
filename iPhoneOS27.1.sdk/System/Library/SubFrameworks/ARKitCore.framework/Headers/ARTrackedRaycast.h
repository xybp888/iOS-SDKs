//
//  ARTrackedRaycast.h
//  ARKit
//
//  Copyright © 2018 Apple Inc. All rights reserved.
//

#import <ARKitCore/ARRaycastQuery.h>
#import <Foundation/Foundation.h>
#import <simd/simd.h>

NS_ASSUME_NONNULL_BEGIN

API_UNAVAILABLE_BEGIN(visionos)

/**
 A tracked raycast representation.
 */
API_AVAILABLE(ios(13.0))
@interface ARTrackedRaycast : NSObject

/**
 Stop raycasting.

 The raycast will be continuously tracked until stopped.
 Resetting session's tracking, changing its configuration or deallocation of ARTrackedRaycast object cause the raycast to stop.
*/
- (void)stopTracking;

/**
 Unavailable. Tracked raycasts are created by the system.

 - Returns: This method is unavailable.
*/
- (instancetype)init NS_UNAVAILABLE;

/**
 Unavailable. Tracked raycasts are created by the system.

 - Returns: This method is unavailable.
*/
+ (instancetype)new NS_UNAVAILABLE;

@end

API_UNAVAILABLE_END

NS_ASSUME_NONNULL_END
