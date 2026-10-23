#if (defined(USE_ARKIT_PUBLIC_HEADERS) && USE_ARKIT_PUBLIC_HEADERS) || !__has_include(<ARKitCore/ARAppClipCodeAnchor.h>)
#import <TargetConditionals.h>
//
//  ARAppClipCodeAnchor.h
//  ARKit
//
//  Copyright © 2016-2021 Apple Inc. All rights reserved.
//

#import <ARKit/ARAnchor.h>

NS_ASSUME_NONNULL_BEGIN

API_UNAVAILABLE_BEGIN(visionos)

/**
A value describing app clip code URL decoding state.
*/
API_AVAILABLE(ios(14.3))
typedef NS_ENUM(NSInteger, ARAppClipCodeURLDecodingState) {
    /** App clip code tracking is attempting to decode the URL. */
    ARAppClipCodeURLDecodingStateDecoding,

    /** App clip code tracking failed to decode the URL. */
    ARAppClipCodeURLDecodingStateFailed,

    /** App clip code tracking decoded the URL. */
    ARAppClipCodeURLDecodingStateDecoded
} NS_SWIFT_NAME(ARAppClipCodeAnchor.URLDecodingState);

/**
 An anchor representing an app clip code in the world.
 */
API_AVAILABLE(ios(14.3))
NS_SWIFT_SENDABLE
@interface ARAppClipCodeAnchor : ARAnchor <ARTrackable>

/**
The URL encoded in this app clip code. Not nil only if urlDecodingState is .decoded.
 */
@property (nonatomic, copy, nullable, readonly) NSURL *url;

/**
 The URL decoding state of the app clip code.
 */
@property (nonatomic, assign, readonly) ARAppClipCodeURLDecodingState urlDecodingState;

/**
The estimated radius of the app clip code in meters.
 */
@property (nonatomic, assign, readonly) float radius;

/**
 Unavailable. App Clip Code anchors are created by the system.

 - Parameter transform: The transformation matrix.

 - Returns: This method is unavailable.
*/
- (instancetype)initWithTransform:(simd_float4x4)transform NS_UNAVAILABLE;

/**
 Unavailable. App Clip Code anchors are created by the system.

 - Parameters:
   - name: The anchor name.
   - transform: The transformation matrix.

 - Returns: This method is unavailable.
*/
- (instancetype)initWithName:(NSString *)name transform:(simd_float4x4)transform NS_UNAVAILABLE;

@end

API_UNAVAILABLE_END

NS_ASSUME_NONNULL_END

#else
#import <ARKitCore/ARAppClipCodeAnchor.h> 
#endif // #if (defined(USE_ARKIT_PUBLIC_HEADERS) \&\& USE_ARKIT_PUBLIC_HEADERS) || !__has_include(<ARKitCore/ARAppClipCodeAnchor.h>)