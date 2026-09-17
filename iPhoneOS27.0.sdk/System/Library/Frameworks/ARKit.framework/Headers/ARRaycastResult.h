#if (defined(USE_ARKIT_PUBLIC_HEADERS) && USE_ARKIT_PUBLIC_HEADERS) || !__has_include(<ARKitCore/ARRaycastResult.h>)
//
//  ARRaycastResult.h
//  ARKit
//
//  Copyright © 2018 Apple Inc. All rights reserved.
//

#import <ARKit/ARRaycastQuery.h>
#import <Foundation/Foundation.h>
#import <simd/simd.h>

@class ARAnchor;

NS_ASSUME_NONNULL_BEGIN

API_UNAVAILABLE_BEGIN(visionos)

/**
 Result of a raycast on a single target.
 */
API_AVAILABLE(ios(13.0))
@interface ARRaycastResult : NSObject

/**
 The transformation matrix that defines the raycast result's rotation, translation and scale relative to the world.
 */
@property (nonatomic, readonly) simd_float4x4 worldTransform;

/**
 Type of the target where the ray terminated.
 */
@property (nonatomic, readonly, assign) ARRaycastTarget target;

/**
 Alignment of the target.
 */
@property (nonatomic, readonly, assign) ARRaycastTargetAlignment targetAlignment;

/**
 The anchor that the ray intersected.

 In case of an existing plane target, an anchor will always be provided. In case of an estimated plane target,
 an anchor may be provided if the ray hit an existing plane.
*/
@property (nonatomic, readonly, strong, nullable) ARAnchor *anchor;

/**
 Unavailable. Raycast results are created by the system.

 - Returns: This method is unavailable.
*/
- (instancetype)init NS_UNAVAILABLE;

/**
 Unavailable. Raycast results are created by the system.

 - Returns: This method is unavailable.
*/
+ (instancetype)new NS_UNAVAILABLE;

@end

API_UNAVAILABLE_END

NS_ASSUME_NONNULL_END
#else
#import <ARKitCore/ARRaycastResult.h> 
#endif // #if (defined(USE_ARKIT_PUBLIC_HEADERS) \&\& USE_ARKIT_PUBLIC_HEADERS) || !__has_include(<ARKitCore/ARRaycastResult.h>)