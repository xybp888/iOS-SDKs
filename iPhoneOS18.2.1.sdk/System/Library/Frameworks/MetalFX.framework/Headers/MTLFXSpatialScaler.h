//
//  MTLFXSpatialScaler.h
//  MetalFX
//
//  Copyright (c) 2021-2022 Apple Inc. All rights reserved.
//

#import <Metal/Metal.h>

typedef NS_ENUM(NSInteger, MTLFXSpatialScalerColorProcessingMode) {
    MTLFXSpatialScalerColorProcessingModePerceptual NS_SWIFT_NAME(perceptual) = 0, /* This should be used when the input and output textures are already in an sRGB or otherwise perceptual 0-1 encoding. */
    MTLFXSpatialScalerColorProcessingModeLinear NS_SWIFT_NAME(linear) = 1,         /* This should be used when the input and output textures will contain light linear data in the 0-1 range. */
    MTLFXSpatialScalerColorProcessingModeHDR NS_SWIFT_NAME(hdr) = 2,               /* This should be used when the input and output texture will contain light linear data outside the 0-1 range.
                                                                                      In this case a reversible tonemapping operation will be done internally to convert to a 0-1 range. */
} API_AVAILABLE(macos(13.0), ios(16.0));

// Forward declaration.
@protocol MTLFXSpatialScaler;

API_AVAILABLE(macos(13.0), ios(16.0))
@interface MTLFXSpatialScalerDescriptor : NSObject <NSCopying>

// These properties must be set to the respective Metal pixel formats for each texture that will be used with the scaler.
@property (readwrite, nonatomic) MTLPixelFormat colorTextureFormat;
@property (readwrite, nonatomic) MTLPixelFormat outputTextureFormat;
@property (readwrite, nonatomic) NSUInteger inputWidth;
@property (readwrite, nonatomic) NSUInteger inputHeight;
@property (readwrite, nonatomic) NSUInteger outputWidth;
@property (readwrite, nonatomic) NSUInteger outputHeight;

/* The default for colorProcessingMode is MTLFXSpatialScalerColorProcessingMode_Perceptual */
@property (readwrite, nonatomic) MTLFXSpatialScalerColorProcessingMode colorProcessingMode;

// The following method is used to instantiate the effect encoder for a given
// Metal device.
- (nullable id <MTLFXSpatialScaler>)newSpatialScalerWithDevice:(nonnull id<MTLDevice>)device;

// Class method for determining support
+ (BOOL)supportsDevice:(nonnull id<MTLDevice>)device;

@end

// This is the object that gets created from the descriptor
API_AVAILABLE(macos(13.0), ios(16.0))
@protocol MTLFXSpatialScaler <NSObject>

// Properties return the minimum required MTLTextureUsage bits required
@property (nonatomic, readonly) MTLTextureUsage colorTextureUsage;
@property (nonatomic, readonly) MTLTextureUsage outputTextureUsage;

// Dynamic resolution property
@property (nonatomic) NSUInteger inputContentWidth;
@property (nonatomic) NSUInteger inputContentHeight;

// These would be all of the "state" needed that is allowed to change on a frame by
// frame basis.   We don't care about the textures assigned except that they must
// match the required MTLTextureUsage flags.
@property (nonatomic, retain, nullable) id<MTLTexture> colorTexture;
// outputTexture is required to have MTLStorageModePrivate for storageMode
@property (nonatomic, retain, nullable) id<MTLTexture> outputTexture;

// Read-only immutable properties of effect
@property (nonatomic, readonly) MTLPixelFormat colorTextureFormat;
@property (nonatomic, readonly) MTLPixelFormat outputTextureFormat;
@property (nonatomic, readonly) NSUInteger inputWidth;
@property (nonatomic, readonly) NSUInteger inputHeight;
@property (nonatomic, readonly) NSUInteger outputWidth;
@property (nonatomic, readonly) NSUInteger outputHeight;
@property (nonatomic, readonly) MTLFXSpatialScalerColorProcessingMode colorProcessingMode;

// Property for synchronization when using untracked resources
@property (nonatomic, retain, nullable) id<MTLFence> fence;

// Method to encode the effect to a command buffer
- (void)encodeToCommandBuffer:(nonnull id<MTLCommandBuffer>)commandBuffer;

@end

