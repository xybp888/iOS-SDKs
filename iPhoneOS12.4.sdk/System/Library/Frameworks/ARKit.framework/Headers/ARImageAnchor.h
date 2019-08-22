//
//  ARImageAnchor.h
//  ARKit
//
//  Copyright © 2016-2017 Apple Inc. All rights reserved.
//

#import <ARKit/ARAnchor.h>

@class ARReferenceImage;

NS_ASSUME_NONNULL_BEGIN

/**
 An anchor representing an image in the world.
 */
API_AVAILABLE(ios(11.3))
@interface ARImageAnchor : ARAnchor <ARTrackable>

/**
 Reference to the detected image.
 */
@property (nonatomic, strong, readonly) ARReferenceImage *referenceImage;

/** Unavailable */
- (instancetype)initWithTransform:(simd_float4x4)transform NS_UNAVAILABLE;
- (instancetype)initWithName:(NSString *)name transform:(simd_float4x4)transform NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
