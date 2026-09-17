#if (defined(USE_ARKIT_PUBLIC_HEADERS) && USE_ARKIT_PUBLIC_HEADERS) || !__has_include(<ARKitCore/ARMatteGenerator.h>)
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
 The resolution at which the matte is to be generated.

 The matte generated per frame can be full resolution of the captured camera image or half resolution. The caller chooses one of the
 options from ARMatteResolution during initialization.
*/
API_AVAILABLE(ios(13.0))
typedef NS_ENUM(NSInteger, ARMatteResolution) {
    /* Matte generated at camera image resolution. */
    ARMatteResolutionFull = 0,

    /* Matte generated at half the camera image resolution. */
    ARMatteResolutionHalf = 1

} NS_SWIFT_NAME(ARMatteGenerator.Resolution);

/**
 An object designed to generate either full resolution or half resolution matte given the ARFrame.

 The caller initializes the object once and calls the alpha matte generation API for every `ARFrame` with the captured image and
 segmentation stencil.
*/
API_AVAILABLE(ios(13.0))
@interface ARMatteGenerator : NSObject

/**
 Initializes an instance of ARMatteGenerator.

 For efficient creation of alpha mattes in real time it is recommended to instantiate this object only once and to generate an alpha matte
 for every incoming frame.

 - Parameters:
   - device: The device the filter will run on.
   - matteResolution: The resolution at which the matte is to be generated. Set using one of the values from 'ARMatteResolution'.

 - Returns: Instance of `ARMatteGenerator`.

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

 - Returns: Alpha matte `MTLTexture` for the given `ARFrame` at full resolution or half resolution as chosen by the  caller during initialization.
*/
- (id<MTLTexture>)generateMatteFromFrame:(ARFrame *)frame commandBuffer:(id<MTLCommandBuffer>)commandBuffer;

/**
 Generates dilated depth at the resolution of the segmentation stencil.

 The caller can use depth information when compositing a virtual object with the captured scene. This API returns the dilated linear depth
 to the caller. The reprojection of this depth to the caller's scene space is carried out externally.

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
#else
#import <ARKitCore/ARMatteGenerator.h> 
#endif // #if (defined(USE_ARKIT_PUBLIC_HEADERS) \&\& USE_ARKIT_PUBLIC_HEADERS) || !__has_include(<ARKitCore/ARMatteGenerator.h>)