//
//  ARReferenceImage.h
//  ARKit
//
//  Copyright © 2016-2017 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreGraphics/CoreGraphics.h>
#import <ImageIO/CGImageProperties.h>
#import <CoreVideo/CVPixelBuffer.h>

@class CIImage;

NS_ASSUME_NONNULL_BEGIN

/**
 A reference image to be detected in the scene.
 */
API_AVAILABLE(ios(11.3))
@interface ARReferenceImage : NSObject

/**
 An optional name used to identify the image.
 */
@property (nonatomic, copy, nullable) NSString *name;

/**
 The physical size of the image in meters.
 */
@property (nonatomic, readonly) CGSize physicalSize;

/**
 Creates a new reference image.
 
 @param image The reference image as CGImage.
 @param orientation The image orientation.
 @param physicalWidth The width in meters of the physical object.
 */
- (instancetype)initWithCGImage:(CGImageRef)image orientation:(CGImagePropertyOrientation)orientation physicalWidth:(CGFloat)physicalWidth NS_SWIFT_NAME(init(_:orientation:physicalWidth:));

/**
 Creates a new reference image.
 
 @param pixelBuffer The reference image as CVPixelBuffer.
 @param physicalWidth The width in meters of the physical object.
 @param orientation The image orientation.
 */
- (instancetype)initWithPixelBuffer:(CVPixelBufferRef)pixelBuffer orientation:(CGImagePropertyOrientation)orientation physicalWidth:(CGFloat)physicalWidth NS_SWIFT_NAME(init(_:orientation:physicalWidth:));

/**
 Returns the set of ARReferenceImages in the specified resource group and bundle.

 @param name The name of the resource group.
 @param bundle The bundle containing the image file or asset catalog. Specify nil to search the app’s main bundle.
 @return The set of reference images or nil on error.
 */
+ (nullable NSSet<ARReferenceImage *> *)referenceImagesInGroupNamed:(NSString *)name bundle:(nullable NSBundle *)bundle;

/** Unavailable */
- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
