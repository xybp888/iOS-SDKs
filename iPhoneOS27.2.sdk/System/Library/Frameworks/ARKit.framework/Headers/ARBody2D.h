#if (defined(USE_ARKIT_PUBLIC_HEADERS) && USE_ARKIT_PUBLIC_HEADERS) || !__has_include(<ARKitCore/ARBody2D.h>)
//
//  ARBody2D.h
//  ARKit
//
//  Copyright © 2019 Apple Inc. All rights reserved.
//

#import <ARKit/ARSkeleton.h>
#import <simd/simd.h>

NS_ASSUME_NONNULL_BEGIN

API_UNAVAILABLE_BEGIN(visionos)

/**
 The screen-space representation of a person ARKit recognizes in the camera feed.

 When ARKit recognizes a person in the camera feed, it estimates the screen-space
 location of the body's joints and provides the location to you through the current
 frame's <doc://com.apple.documentation/documentation/arkit/arframe/detectedbody>.
 */
API_AVAILABLE(ios(13.0))
NS_SWIFT_SENDABLE
@interface ARBody2D : NSObject

/**
 An object that contains the screen position of a body's joints.
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
#else
#import <ARKitCore/ARBody2D.h> 
#endif // #if (defined(USE_ARKIT_PUBLIC_HEADERS) \&\& USE_ARKIT_PUBLIC_HEADERS) || !__has_include(<ARKitCore/ARBody2D.h>)