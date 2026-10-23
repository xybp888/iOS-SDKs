//
//  ARBody2D.h
//  ARKit
//
//  Copyright © 2019 Apple Inc. All rights reserved.
//

#import <ARKitCore/ARSkeleton.h>
#import <simd/simd.h>

NS_ASSUME_NONNULL_BEGIN

API_UNAVAILABLE_BEGIN(visionos)

/**
 Representation of a body in 2D.
 */
API_AVAILABLE(ios(13.0))
NS_SWIFT_SENDABLE
@interface ARBody2D : NSObject

/**
 The body's skeleton.
 */
@property (nonatomic, readonly) ARSkeleton2D *skeleton;

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
