#if (defined(USE_ARKIT_PUBLIC_HEADERS) && USE_ARKIT_PUBLIC_HEADERS) || !__has_include(<ARKitCore/ARImageAnchor.h>)
//
//  ARImageAnchor.h
//  ARKit
//
//  Copyright © 2016-2021 Apple Inc. All rights reserved.
//

#import <ARKit/ARAnchor.h>
#import <CoreGraphics/CoreGraphics.h>

#define AR_IMAGE_ANCHOR_PROTOCOLS <ARTrackable>

@class ARReferenceImage;

NS_ASSUME_NONNULL_BEGIN

/**
 An anchor representing an image in the world.
 */
API_AVAILABLE(ios(11.3))
NS_SWIFT_SENDABLE
@interface ARImageAnchor : ARAnchor AR_IMAGE_ANCHOR_PROTOCOLS

/**
 Reference to the detected image.
 */
@property (nonatomic, strong, readonly) ARReferenceImage *referenceImage;

/**
 The factor between estimated physical size and provided size.
 
 @discussion This value will be estimated if automaticImageScaleEstimationEnabled is set to true on the ARWorldTrackingConfiguration. It is used to
 correct the transform's translation. Default value is 1.0.
 */
@property (nonatomic, readonly) CGFloat estimatedScaleFactor API_AVAILABLE(ios(13.0));

/** Unavailable */
- (instancetype)initWithTransform:(simd_float4x4)transform NS_UNAVAILABLE;
- (instancetype)initWithName:(NSString *)name transform:(simd_float4x4)transform NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
#else
#import <ARKitCore/ARImageAnchor.h> 
#endif // #if (defined(USE_ARKIT_PUBLIC_HEADERS) \&\& USE_ARKIT_PUBLIC_HEADERS) || !__has_include(<ARKitCore/ARImageAnchor.h>)