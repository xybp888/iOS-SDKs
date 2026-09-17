#if (defined(USE_ARKIT_PUBLIC_HEADERS) && USE_ARKIT_PUBLIC_HEADERS) || !__has_include(<ARKitCore/ARWorldMap.h>)
//
//  ARWorldMap.h
//  ARKit
//
//  Copyright © 2018 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <simd/simd.h>

@class ARAnchor;
@class ARPointCloud;

NS_ASSUME_NONNULL_BEGIN

API_UNAVAILABLE_BEGIN(visionos)

/**
 Object representing the mapping of a physical 3D space.

 `ARWorldMap` supports archiving and unarchiving across devices
 and versions with NSDecodingFailurePolicySetErrorAndReturn, providing an error
 if the map format is not supported.
*/
API_AVAILABLE(ios(12.0))
@interface ARWorldMap : NSObject <NSCopying, NSSecureCoding>

/**
 The position of the center of the mapped world in meters.
 */
@property (nonatomic, readonly) simd_float3 center;

/**
 The extent of the mapped world in meters.
 */
@property (nonatomic, readonly) simd_float3 extent;

/**
 A list of anchors in the map.
 */
@property (nonatomic, copy) NSArray<__kindof ARAnchor *> *anchors;

/**
 The feature points in the map.
 */
@property (nonatomic, strong, readonly) ARPointCloud *rawFeaturePoints;

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

API_UNAVAILABLE_END

NS_ASSUME_NONNULL_END
#else
#import <ARKitCore/ARWorldMap.h> 
#endif // #if (defined(USE_ARKIT_PUBLIC_HEADERS) \&\& USE_ARKIT_PUBLIC_HEADERS) || !__has_include(<ARKitCore/ARWorldMap.h>)