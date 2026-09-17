#if (defined(USE_ARKIT_PUBLIC_HEADERS) && USE_ARKIT_PUBLIC_HEADERS) || !__has_include(<ARKitCore/ARReferenceImage.h>)
//
//  ARReferenceImage.h
//  ARKit
//
//  Copyright © 2016-2021 Apple Inc. All rights reserved.
//

#import <CoreGraphics/CoreGraphics.h>
#import <CoreVideo/CVPixelBuffer.h>
#import <Foundation/Foundation.h>
#import <ImageIO/CGImageProperties.h>

@class CIImage;

NS_ASSUME_NONNULL_BEGIN

API_UNAVAILABLE_BEGIN(visionos)

/**
 A reference image to be detected in the scene.
 */
API_AVAILABLE(ios(11.3))
NS_SWIFT_SENDABLE
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
 The AR resource group name for this image.

 If this image was loaded via an AR resource group in the Xcode asset catalogue this property will have the name of the resource group,
 else be set to nil.
*/
@property (nonatomic, strong, nullable, readonly) NSString *resourceGroupName API_AVAILABLE(ios(13.0));

/**
 Validate if this image can be used for image detection or tracking.

 When loading reference images from the asset catalog this verification is not needed as the same verification happens
 at compile time.

 - Parameter completionHandler: Completion handler invoked when validation is done. The completion handler takes the following parameters:
   error - An error that indicates why the image is not suitable for tracking, or `nil` if no error occurred.
*/
- (void)validateWithCompletionHandler:(void (^)(NSError *_Nullable error))completionHandler API_AVAILABLE(ios(13.0));

/**
 Creates a new reference image.

 - Parameters:
   - image: The reference image as `CGImage`.
   - orientation: The image orientation.
   - physicalWidth: The width in meters of the physical object.

 - Returns: An initialized reference image.
*/
- (instancetype)initWithCGImage:(CGImageRef)image
                    orientation:(CGImagePropertyOrientation)orientation
                  physicalWidth:(CGFloat)physicalWidth NS_SWIFT_NAME(init(_:orientation:physicalWidth:));

/**
 Creates a new reference image.

 - Parameters:
   - pixelBuffer: The reference image as `CVPixelBuffer`.
   - physicalWidth: The width in meters of the physical object.
   - orientation: The image orientation.

 - Returns: An initialized reference image.
*/
- (instancetype)initWithPixelBuffer:(CVPixelBufferRef)pixelBuffer
                        orientation:(CGImagePropertyOrientation)orientation
                      physicalWidth:(CGFloat)physicalWidth NS_SWIFT_NAME(init(_:orientation:physicalWidth:));

/**
 Returns the set of ARReferenceImages in the specified resource group and bundle.

 - Parameters:
   - name: The name of the resource group.
   - bundle: The bundle containing the image file or asset catalog. Specify `nil` to search the app’s main bundle.

 - Returns: The set of reference images or `nil` on error.
*/
+ (nullable NSSet<ARReferenceImage *> *)referenceImagesInGroupNamed:(NSString *)name bundle:(nullable NSBundle *)bundle;

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
#import <ARKitCore/ARReferenceImage.h> 
#endif // #if (defined(USE_ARKIT_PUBLIC_HEADERS) \&\& USE_ARKIT_PUBLIC_HEADERS) || !__has_include(<ARKitCore/ARReferenceImage.h>)