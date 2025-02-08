//
//  MTLFXTemporalScaler.h
//  MetalFX
//
//  Copyright (c) 2021-2022 Apple Inc. All rights reserved.
//

#import <Metal/Metal.h>

// Forward declaration.
@protocol MTLFXTemporalScaler;

API_AVAILABLE(macos(13.0), ios(16.0))
#if defined(TARGET_OS_VISION) && TARGET_OS_VISION
API_UNAVAILABLE(visionos)
#endif
@interface MTLFXTemporalScalerDescriptor : NSObject <NSCopying>

// These properties must be set to the respective Metal pixel formats for each texture that will be used with the scaler.
@property (readwrite, nonatomic) MTLPixelFormat colorTextureFormat;
@property (readwrite, nonatomic) MTLPixelFormat depthTextureFormat;
@property (readwrite, nonatomic) MTLPixelFormat motionTextureFormat;
@property (readwrite, nonatomic) MTLPixelFormat outputTextureFormat;

@property (readwrite, nonatomic) NSUInteger inputWidth;
@property (readwrite, nonatomic) NSUInteger inputHeight;
@property (readwrite, nonatomic) NSUInteger outputWidth;
@property (readwrite, nonatomic) NSUInteger outputHeight;

// Auto exposure property, setting this to YES to indicate for MetalFX
// to determine exposure per frame, which will ignore exposureTexture
// property on the scaler object.
@property (readwrite, nonatomic, getter=isAutoExposureEnabled) BOOL autoExposureEnabled;

// requiresSynchronousInitialization property, setting this to YES ensures
// that the effect is fully created before first use, setting it to NO
// allows the implementation to create an optimized version asynchronously, this
// can cause the performance to be submoptimal while the optimized version is created.
// Defaults to NO.
@property (readwrite, nonatomic) BOOL requiresSynchronousInitialization;

// Dynamic Resolution properties
// Set inputContentPropertiesEnabled to YES to indicate using dynamic resolution
// Scale value represents output resolution / input content resolution for either
// width or height dimension. It's assumed that aspect ratio of input/output is
// always the same. 
@property (readwrite, nonatomic, getter=isInputContentPropertiesEnabled) BOOL inputContentPropertiesEnabled;
@property (readwrite, nonatomic) float inputContentMinScale;
@property (readwrite, nonatomic) float inputContentMaxScale;

@property (readwrite, nonatomic, getter=isReactiveMaskTextureEnabled) BOOL reactiveMaskTextureEnabled API_AVAILABLE(macos(14.4), ios(17.4));
@property (readwrite, nonatomic) MTLPixelFormat reactiveMaskTextureFormat API_AVAILABLE(macos(14.4), ios(17.4));

// The following method is used to instantiate the effect encoder for a given
// Metal device.
- (nullable id <MTLFXTemporalScaler>)newTemporalScalerWithDevice:(nonnull id<MTLDevice>)device;

// Class methods for querying supported min/max input content scale.
+ (float)supportedInputContentMinScaleForDevice:(nonnull id<MTLDevice>)device API_AVAILABLE(macos(14.0), ios(17.0));
+ (float)supportedInputContentMaxScaleForDevice:(nonnull id<MTLDevice>)device API_AVAILABLE(macos(14.0), ios(17.0));

// Class method for determining support
+ (BOOL)supportsDevice:(nonnull id<MTLDevice>)device;

@end

// This is the object that gets created from the descriptor
API_AVAILABLE(macos(13.0), ios(16.0))
#if defined(TARGET_OS_VISION) && TARGET_OS_VISION
API_UNAVAILABLE(visionos)
#endif
@protocol MTLFXTemporalScaler <NSObject>

// Properties return the minimum required MTLTextureUsage bits required
@property (nonatomic, readonly) MTLTextureUsage colorTextureUsage;
@property (nonatomic, readonly) MTLTextureUsage depthTextureUsage;
@property (nonatomic, readonly) MTLTextureUsage motionTextureUsage;
@property (nonatomic, readonly) MTLTextureUsage reactiveTextureUsage API_AVAILABLE(macos(14.4), ios(17.4));
@property (nonatomic, readonly) MTLTextureUsage outputTextureUsage;

// Dynamic Resolution property
@property (nonatomic) NSUInteger inputContentWidth;
@property (nonatomic) NSUInteger inputContentHeight;

// These can change on a frame by frame basis.
// We don't care about the textures assigned except that they must
// match the originally specified dimensions and pixel formats.
@property (nonatomic, retain, nullable) id<MTLTexture> colorTexture;
@property (nonatomic, retain, nullable) id<MTLTexture> depthTexture;
@property (nonatomic, retain, nullable) id<MTLTexture> motionTexture;
// outputTexture is required to have MTLStorageModePrivate for storageMode
@property (nonatomic, retain, nullable) id<MTLTexture> outputTexture;

// Exposure properties
// Ideally this is a 1x1 R16F texture. Note that only R channel of
// the texel located at (0, 0) is used for exposure value. The value is used
// to multiply the input color, use GPU to generate the exposure value.
@property (nonatomic, retain, nullable) id<MTLTexture> exposureTexture;

// Reactive mask
// An optional single channel texture that contains values in the range
// 0.0f-1.0f. A value of 0.0f applies the default temporal effect treatment.
// A value greater than 0.0f applies a bias towards the current frame for
// the pixel.
@property (nonatomic, retain, nullable) id<MTLTexture> reactiveMaskTexture API_AVAILABLE(macos(14.4), ios(17.4));
// If the input color is pre-multiplied by fixed value, set this value
// which MetalFX will use to divide input color, this is not common.
@property (nonatomic) float preExposure;

// The jitter offset property indicates the pixel offset to sample in order to
// return to the frame's reference frame.
@property (nonatomic) float jitterOffsetX;
@property (nonatomic) float jitterOffsetY;

// Scale factor to be applied to motion vectors to convert to pixel/fragment
// coordinates in the input data.  The expectation for a 1.0 scale factor is
// that each pixel's motion vector will point to where that pixel was in the
// prior frame.  Assuming standard Metal device coordinates (0,0 is upper left
// in the framebuffer), the motion vectors for an object that moved down and
// to the right in the framebuffer texture by 10 pixels would be -10,-10.
@property (nonatomic) float motionVectorScaleX;
@property (nonatomic) float motionVectorScaleY;

// Reset.  Set to true when history is invalid (scene cut, etc.)
@property (nonatomic) BOOL reset;

// Set whether the depth buffer uses reversed depth or not. Defaults to YES.
@property (readwrite, nonatomic, getter=isDepthReversed) BOOL depthReversed;

// Read-only immutable properties of effect
@property (nonatomic, readonly) MTLPixelFormat colorTextureFormat;
@property (nonatomic, readonly) MTLPixelFormat depthTextureFormat;
@property (nonatomic, readonly) MTLPixelFormat motionTextureFormat;
@property (nonatomic, readonly) MTLPixelFormat outputTextureFormat;
@property (nonatomic, readonly) NSUInteger inputWidth;
@property (nonatomic, readonly) NSUInteger inputHeight;
@property (nonatomic, readonly) NSUInteger outputWidth;
@property (nonatomic, readonly) NSUInteger outputHeight;
@property (nonatomic, readonly) float inputContentMinScale;
@property (nonatomic, readonly) float inputContentMaxScale;

// Property for synchronization when using untracked resources
@property (nonatomic, retain, nullable) id<MTLFence> fence;

// Method to encode the effect to a command buffer
- (void)encodeToCommandBuffer:(nonnull id<MTLCommandBuffer>)commandBuffer;

@end
