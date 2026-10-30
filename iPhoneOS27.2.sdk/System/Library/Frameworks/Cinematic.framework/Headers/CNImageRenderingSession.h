//
//  CNImageRenderingSession.h
//  Cinematic
//
//  Copyright © 2022-2025 Apple Inc. All rights reserved.
//


#pragma once
#import <AVFoundation/AVFoundation.h>
#import <Metal/Metal.h>
#import <Cinematic/CNRenderingSession.h>

NS_ASSUME_NONNULL_BEGIN

/// Configuration for a CNImageRenderingSession, specifying the rendering quality and algorithm version.
API_AVAILABLE(macos(27.0), ios(27.0), tvos(27.0), visionos(27.0)) API_UNAVAILABLE(watchos)
@interface CNImageRenderingSessionConfiguration : NSObject

-(instancetype)init NS_UNAVAILABLE;

/// Initialize with the latest rendering version
/// - Parameters:
///      - quality: The quality level for the rendering session.
-(instancetype)initWithQuality:(CNRenderingQuality)quality;

/// Initialize with a specific rendering version.
/// - Parameters:
///      - quality: The quality level for the rendering session.
///      - renderingVersion: Should be obtained from `latestRenderingVersion`. Pinning a version
///   from a prior build ensures rendering output is stable across OS updates. Use `isRenderingVersionSupported:` to verify the version is still supported before using it.
-(instancetype _Nullable)initWithQuality:(CNRenderingQuality)quality
                        renderingVersion:(NSInteger)renderingVersion;

@property (readonly) CNRenderingQuality quality;

/// Rendering version used to render
@property (readonly) NSInteger renderingVersion;

/// The version of the newest rendering algorithm
@property (class, readonly) NSInteger latestRenderingVersion;

/// Checks if a given rendering version is supported on the current build
+(BOOL)isRenderingVersionSupported:(NSInteger)renderingVersion;

@end

/// A session for rendering a shallow depth-of-field (SDoF) effect onto still images using Metal.
///
/// Use CNImageRenderingSession to apply a cinematic, lens-simulated bokeh effect to an image given
/// a disparity map. For large images, prefer the tiled API to avoid excessive GPU memory usage.
///
/// A single session may be reused across multiple render calls. It is not thread-safe.
API_AVAILABLE(macos(27.0), ios(27.0), tvos(27.0), visionos(27.0)) API_UNAVAILABLE(watchos)
@interface CNImageRenderingSession : NSObject

@property (readonly, strong) CNImageRenderingSessionConfiguration *configuration;

-(instancetype)init NS_UNAVAILABLE;

-(instancetype)initWithConfiguration:(CNImageRenderingSessionConfiguration *)configuration;

/// Encode a command to render a shallow depth of field (SDoF) image to a metal texture
/// - Parameters:
///   - commandBuffer: The Metal command buffer on which to encode the command
///   - sourceRGBA: A color texture to which the effect should be applied. Texture must be in linear color space. The width and height must match those of destinationRGBA.
///   - sourceDisparity: The texture with the disparity
///   - destinationRGBA: The texture to which the SDoF image is rendered. Texture must be in linear color space. Must have the same dimensions as sourceRGBA.
///   - fNumber: The f-stop value which inversely affects the aperture used to render the image. A smaller f/ number results in larger bokeh and a shallower depth of field in the rendered image.
///   - focusDisparity: The disparity value which represents the focus plane at which the rendered image should be in focus. A larger disparity results in the focus plane being closer to the camera. The scale and offset of disparity is not defined. It is best practice to obtain disparity values from detections or by interpolation between known disparity values.
/// - Returns: YES if encoding succeeded; NO if required resources are unavailable or if
///   the provided textures are incompatible.
- (BOOL)encodeRenderToCommandBuffer:(id<MTLCommandBuffer>)commandBuffer
                         sourceRGBA:(id<MTLTexture>)sourceRGBA
                    sourceDisparity:(id<MTLTexture>)sourceDisparity
                    destinationRGBA:(id<MTLTexture>)destinationRGBA
                            fNumber:(float)fNumber
                     focusDisparity:(float)focusDisparity;

/// Encode a command to render a shallow depth of field (SDoF) image to a metal texture
///
/// Tiled rendering avoids allocating a full-resolution texture for large images. The source tile must
/// be larger than the destination tile (the "extend" region) so the renderer has enough surrounding
/// pixel context to correctly compute bokeh near tile edges. Use `minimumTileExtendRectForTileRect:sourceRGBASize:`
/// to compute the required extended source rect.
///
/// - Parameters:
///   - commandBuffer: The Metal command buffer on which to encode the command
///   - sourceTileRGBA: A color texture to which the effect should be applied. Texture must be in linear color space. Its origin in the full image is given by tileExtendOffset.
///   - sourceDisparity: The texture with the disparity. This texture is not tiled.
///   - destinationTileRGBA: The texture to which the SDoF image is rendered. Texture must be in linear color space. Its dimensions define the tile size. Its origin in the full image is given by `tileOffset`.
///   - fNumber: The f-stop value which inversely affects the aperture used to render the image. A smaller f/ number results in larger bokeh and a shallower depth of field in the rendered image.
///   - focusDisparity: The disparity value which represents the focus plane at which the rendered image should be in focus. A larger disparity results in the focus plane being closer to the camera. The scale and offset of disparity is not defined. It is best practice to obtain disparity values from detections or by interpolation between known disparity values.
///   - sourceRGBASize: The width and height of the full (un-tiled) source image.
///   - tileOffset: The pixel-coordinate origin of the destination tile within the full image.
///   - tileExtendOffset: The pixel-coordinate origin of the extended source tile within the full image.
/// - Returns: YES if encoding succeeded; NO if required resources are unavailable or if the provided parameters are incompatible.
- (BOOL)encodeTileRenderToCommandBuffer:(id<MTLCommandBuffer>)commandBuffer
                         sourceTileRGBA:(id<MTLTexture>)sourceTileRGBA
                        sourceDisparity:(id<MTLTexture>)sourceDisparity
                    destinationTileRGBA:(id<MTLTexture>)destinationTileRGBA
                                fNumber:(float)fNumber
                         focusDisparity:(float)focusDisparity
                         sourceRGBASize:(CGSize)sourceRGBASize
                             tileOffset:(CGPoint)tileOffset
                       tileExtendOffset:(CGPoint)tileExtendOffset
NS_SWIFT_NAME(encodeTileRender(to:sourceTileRGBA:sourceDisparity:destinationTileRGBA:fNumber:focusDisparity:sourceRGBASize:tileOffset:tileExtendOffset:));

/// Returns the minimum source rect that must be sampled to render tileRect without edge artifacts.
///
/// When applying a bokeh blur near a tile boundary, the renderer needs pixels from outside the
/// destination tile. This method computes how far that border region extends. Pass the returned rect's origin as tileExtendOffset
/// and allocate sourceTileRGBA with the returned rect's size.
///
/// - Parameters:
///   - tileRect: The destination tile rect in full-image pixel coordinates.
///   - sourceRGBASize: The dimensions of the full (un-tiled) source image.
/// - Returns: A rect (in full-image pixel coordinates) covering the minimum required source region,
///   clamped to the image bounds.
+(CGRect)minimumTileExtendRectForTileRect:(CGRect)tileRect sourceRGBASize:(CGSize)sourceRGBASize;

@end

NS_ASSUME_NONNULL_END
