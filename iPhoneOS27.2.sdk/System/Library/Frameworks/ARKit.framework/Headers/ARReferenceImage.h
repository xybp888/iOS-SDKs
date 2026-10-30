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
 A 2D image that you want ARKit to detect in the physical environment.

 To accurately detect the position and orientation of a 2D image in the real world, ARKit requires
 preprocessed image data and knowledge of the image's real-world dimensions. The `ARReferenceImage`
 class encapsulates this information. To enable image detection in an AR session, pass a collection
 of reference images to your session configuration's ``ARWorldTrackingConfiguration/detectionImages`` property.

 Typically, you create reference images in your Xcode project's asset catalog:

 1. In your asset catalog, use the Add (+) button to create an AR Resource Group.
 2. Drag image files into the resource group to create AR Reference Image entries in the asset catalog.
 3. For each reference image, use the Xcode inspector panel to provide the real-world size at which you
 want ARKit to recognize the image. (You can also provide a descriptive name, which appears as the
 ``name`` property at runtime and can be useful for debugging.)
 */
API_AVAILABLE(ios(11.3))
NS_SWIFT_SENDABLE
@interface ARReferenceImage : NSObject

/**
 A descriptive name for the image.

 For reference images loaded from an Xcode asset catalog, this property is the name assigned in the
 asset catalog. For programmatically created reference images, this value is `nil`.

 - Note: This string is not localized text intended for user display. However, in debugging you can
 use this property to indicate which image was detected.
 */
@property (nonatomic, copy, nullable) NSString *name;

/**
 The real-world dimensions, in meters, of the image.

 To accurately recognize the position and orientation of an image in the AR environment, ARKit must
 know the image's physical size. You provide this information when creating an AR reference image in
 your Xcode project's asset catalog, or when programmatically creating an `ARReferenceImage`.

 When you want to recognize different-sized versions of a reference image, you set
 ``ARWorldTrackingConfiguration/automaticImageScaleEstimationEnabled`` to <doc://com.apple.documentation/documentation/swift/true>,
 and in this case, ARKit disregards `physicalSize`.
 */
@property (nonatomic, readonly) CGSize physicalSize;

/**
 The AR resource group name for this image.

 If ARKit loaded this image from an AR resource group in an asset catalog, ARKit sets the value of
 this property to the resource group's name. Otherwise, the value of this property is `nil`.
*/
@property (nonatomic, strong, nullable, readonly) NSString *resourceGroupName API_AVAILABLE(ios(13.0));

/**
 Determines whether the reference image is valid.

 ARKit considers certain images invalid for image tracking (for example, an image that's all white).
 Call this function on a reference image you create programmatically to make sure ARKit can track it,
 before passing it in to your session's ``ARWorldTrackingConfiguration/detectionImages`` array.

 You only need this function when you create a reference image programmatically, because Xcode performs
 this validation for you when you create a reference image in an asset catalog.

 - Parameter completionHandler: Completion handler invoked when validation is done. The completion handler takes the following parameters:
   error - An error that indicates why the image is not suitable for tracking, or `nil` if no error occurred.
*/
- (void)validateWithCompletionHandler:(void (^)(NSError *_Nullable error))completionHandler API_AVAILABLE(ios(13.0));

/**
 Creates a new reference image from a Core Graphics image object.

 To accurately recognize the position and orientation of an image in the AR environment, ARKit must
 know the image's physical size. When you call this initializer, ARKit uses the `physicalWidth`
 measurement and `orientation` you provide together with the aspect ratio of the image itself to
 calculate the physical height. Use the ``ARReferenceImage/physicalSize`` property of the created
 ``ARReferenceImage`` object to retrieve these values.

 > Important: ARKit preprocesses reference images before using them for image detection. To provide reference images bundled with your app, create AR
 reference image assets in your Xcode asset catalog, and use the ``ARReferenceImage/referenceImages(inGroupNamed:bundle:)`` method to load them.

 - Parameters:
   - image: A Core Graphics image object.
   - orientation: The intended display orientation for the image.
   - physicalWidth: The real-world width, in meters, of the image.
*/
- (instancetype)initWithCGImage:(CGImageRef)image
                    orientation:(CGImagePropertyOrientation)orientation
                  physicalWidth:(CGFloat)physicalWidth NS_SWIFT_NAME(init(_:orientation:physicalWidth:));

/**
 Creates a new reference image from a Core Video pixel buffer.

 To accurately recognize the position and orientation of an image in the AR environment, ARKit must
 know the image's physical size. When you call this initializer, ARKit uses the `physicalWidth`
 measurement and `orientation` you provide together with the aspect ratio of the image itself to
 calculate the physical height. Use the ``ARReferenceImage/physicalSize`` property of the created
 ``ARReferenceImage`` object to retrieve these values.

 > Important: ARKit preprocesses reference images before using them for image detection. To provide reference images bundled with your app, create AR
 reference image assets in your Xcode asset catalog, and use the ``ARReferenceImage/referenceImages(inGroupNamed:bundle:)`` method to load them.

 - Parameters:
   - pixelBuffer: A Core Video pixel buffer containing the image data for the new image.
   - orientation: The intended display orientation for the image.
   - physicalWidth: The real-world width, in meters, of the image.
*/
- (instancetype)initWithPixelBuffer:(CVPixelBufferRef)pixelBuffer
                        orientation:(CGImagePropertyOrientation)orientation
                      physicalWidth:(CGFloat)physicalWidth NS_SWIFT_NAME(init(_:orientation:physicalWidth:));

/**
 Loads all reference images in the specified AR Resource Group in your Xcode project's asset catalog.

 To use the images for image detection in a world-tracking AR session, provide this set for your
 session configuration's ``ARWorldTrackingConfiguration/detectionImages`` property.

 - Parameters:
   - name: The name of an AR Resource Group from your Xcode project's main asset catalog.
   - bundle: The bundle from which to load asset catalog resources, or `nil` to use your app's main bundle.

 - Returns: A set of all unique reference images in the specified group.
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