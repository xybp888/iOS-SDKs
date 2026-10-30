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
 A raycast query that ARKit repeats in succession to give you refined results over time.

 Tracked raycasting improves hit-testing techniques by repeating the query for a 3D position in succession. ARKit provides you with an updated
 position as it refines its understanding of world over time.

 To start a tracked raycast, you call <doc://com.apple.documentation/documentation/arkit/arsession/trackedraycast(_:updatehandler:)> on your app's
 current <doc://com.apple.documentation/documentation/arkit/arsession>.
 */
API_AVAILABLE(ios(13.0))
@interface ARTrackedRaycast : NSObject

/**
 Stops repeating the raycast query.

 A tracked raycast updates continuously until you stop it explicitly by calling `stopTracking`. A raycast will automatically stop when:

 - You reset the session's tracking, or pass the `ARSessionRunOptionStopTrackedRaycasts` run option to `run(_:options:)`.
 - You change the session's configuration.
 - You deallocate the `ARTrackedRaycast`.
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
