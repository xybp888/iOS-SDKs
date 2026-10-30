//
//  ARMatteGenerator.h
//  ARKit
//
//  Copyright © 2019 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

@class ARFrame;

@protocol MTLTexture;
@protocol MTLCommandBuffer;
@protocol MTLDevice;

NS_ASSUME_NONNULL_BEGIN

API_UNAVAILABLE_BEGIN(visionos)

/**
 A resolution for a matte texture.

 You generate a matte texture every frame, specifying whether its resolution is the full size or half of the camera image.
*/
API_AVAILABLE(ios(13.0))
typedef NS_ENUM(NSInteger, ARMatteResolution) {
    /** An option that specifies the full camera image resolution. */
    ARMatteResolutionFull = 0,

    /** An option that specifies half of the camera image resolution. */
    ARMatteResolutionHalf = 1

} NS_SWIFT_NAME(ARMatteGenerator.Resolution);

/**
 An object that creates matte textures you use to occlude your app's virtual content with people that ARKit recognizes in the camera feed.

 Use this class when you want full control over occluding your app's virtual content, based on people ARKit recognizes in the camera feed.

 > Note:
 > Apps using one of the standard renderers (`ARView` or ``ARSCNView``) don't need this class to effect people occlusion. See
 ``ARConfiguration/frameSemantics`` for more information.

 To assist your custom renderer with people occlusion, matte generator processes alpha and depth information in a frame's
 ``ARFrame/segmentationBuffer`` and ``ARFrame/estimatedDepthData`` to provide you with matte and depth textures. You use these textures to layer
 people on top of your app's virtual content.
*/
API_AVAILABLE(ios(13.0))
@interface ARMatteGenerator : NSObject

/**
 Creates an AR matte generator.

 To create matte textures in real-time, create this object once and reuse it every frame.

 - Parameters:
   - device: The device the filter will run on.
   - matteResolution: The resolution at which the matte is to be generated. Set using one of the values from 'ARMatteResolution'.

 - SeeAlso: ``ARFrame``
 - SeeAlso: ``ARMatteGenerator/generateMatteFromFrame:commandBuffer:``
 - SeeAlso: ``ARMatteResolution``
*/
- (instancetype)initWithDevice:(id<MTLDevice>)device matteResolution:(ARMatteResolution)matteResolution NS_DESIGNATED_INITIALIZER;

/**
 Generates alpha matte at either full resolution or half the resolution of the captured image.

 - Parameters:
   - frame: Current `ARFrame` containing camera image and segmentation stencil. The caller is to ensure that a valid segmentation buffer is present.
   - commandBuffer: Metal command buffer for encoding matting related operations. The command buffer is committed by the caller externally.

 - Returns: An alpha matte `MTLTexture` for the given `ARFrame` at the resolution you chose at initialization.
*/
- (id<MTLTexture>)generateMatteFromFrame:(ARFrame *)frame commandBuffer:(id<MTLCommandBuffer>)commandBuffer;

/**
 Generates dilated depth at the resolution of the segmentation stencil.

 You use the linear depth information this function provides when compositing a virtual object with the camera image. The reprojection of this depth
 to the caller's scene space is carried out externally.

 - Parameters:
   - frame: Current `ARFrame` containing camera image and estimated depth buffer. The caller is to ensure that a valid depth buffer is present.
   - commandBuffer: Metal command buffer for encoding depth dilation operations. The command buffer is committed by the caller externally.

 - Returns: Dilated depth `MTLTexture` for the given `ARFrame` at the segmentation stencil resolution. The texture consists of a single channel and is
 of type `float16`.
*/
- (id<MTLTexture>)generateDilatedDepthFromFrame:(ARFrame *)frame commandBuffer:(id<MTLCommandBuffer>)commandBuffer;

/**
 Unavailable. ARMatteGenerator objects are created using designated initializers.

 - Returns: This method is unavailable.
*/
- (instancetype)init NS_UNAVAILABLE;

/**
 Unavailable. ARMatteGenerator objects are created using designated initializers.

 - Returns: This method is unavailable.
*/
+ (instancetype)new NS_UNAVAILABLE;

@end

API_UNAVAILABLE_END

NS_ASSUME_NONNULL_END
