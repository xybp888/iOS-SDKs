//
//  ARPointCloud.h
//  ARKit
//
//  Copyright © 2016-2021 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <simd/simd.h>

NS_ASSUME_NONNULL_BEGIN

API_UNAVAILABLE_BEGIN(visionos)

/**
 A collection of points in the world coordinate space of the AR session.

 Use the ``ARFrame`` ``ARFrame/rawFeaturePoints`` property to obtain a point cloud representing intermediate results of the scene analysis ARKit uses
 to perform world tracking.
 */
API_AVAILABLE(ios(11.0))
NS_SWIFT_SENDABLE
@interface ARPointCloud : NSObject <NSSecureCoding>

/**
 The number of points in the point cloud.
 */
@property (nonatomic, readonly) NSUInteger count NS_REFINED_FOR_SWIFT;

/**
 The list of detected points.
 */
@property (nonatomic, readonly) const simd_float3 *points NS_REFINED_FOR_SWIFT;

/**
 A list of unique identifiers corresponding to detected feature points.

 Each identifier in this list corresponds to the point vector at the same index in the ``ARPointCloud/points`` array.
 */
@property (nonatomic, readonly) const uint64_t *identifiers NS_REFINED_FOR_SWIFT;

/**
 Unavailable. ARPointCloud objects are created by the system.

 - Returns: This method is unavailable.
*/
- (instancetype)init NS_UNAVAILABLE;

/**
 Unavailable. ARPointCloud objects are created by the system.

 - Returns: This method is unavailable.
*/
+ (instancetype)new NS_UNAVAILABLE;

@end

API_UNAVAILABLE_END

NS_ASSUME_NONNULL_END
