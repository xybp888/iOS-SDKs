#if (defined(USE_ARKIT_PUBLIC_HEADERS) && USE_ARKIT_PUBLIC_HEADERS) || !__has_include(<ARKitCore/ARReferenceObject.h>)
//
//  ARReferenceObject.h
//  ARKit
//
//  Copyright © 2018 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <simd/simd.h>

@class UIImage;

NS_ASSUME_NONNULL_BEGIN

API_UNAVAILABLE_BEGIN(visionos)

/**
 The standard filename extension for exported ``ARReferenceObject`` instances.

 Use this filename extension when constructing a URL to save a reference object file with the ``ARReferenceObject/export(to:previewImage:)`` method.
 */
API_AVAILABLE(ios(12.0))
FOUNDATION_EXTERN NSString *const ARReferenceObjectArchiveExtension NS_SWIFT_NAME(ARReferenceObject.archiveExtension)
                                                                                      API_DEPRECATED("Only supported for legacy reference objects.",
                                                                                                     ios(12.0, 27.0));

@class ARPointCloud;

/**
 A 3D object that ARKit can detect or track in the scene.

 Train a reference object in the Create ML app to produce a `.referenceobject`
 file. Load the file from a local file URL with
 ``ARReferenceObject/init(archiveURL:)``, then assign the resulting reference
 object to either ``ARWorldTrackingConfiguration/detectionObjects`` or
 ``ARWorldTrackingConfiguration/trackingObjects`` on your
 ``ARWorldTrackingConfiguration``, depending on whether the object moves in the
 scene:

 - Use ``ARWorldTrackingConfiguration/detectionObjects`` for objects that are
 mostly stationary. The system holds the pose stable in world space, consuming less power.
 - Use ``ARWorldTrackingConfiguration/trackingObjects`` for moving or handheld
 objects when you need precise pose updates. The system tracks the object at the full
 frame rate of the selected ``ARConfiguration/videoFormat``.

 ARKit on iOS supports the `.referenceobject` format starting in iOS 27. If you
 already have `.referenceobject` files from a visionOS app, you can use them in
 your iOS app without retraining.

 - Note: ARKit also continues to load the older `.arobject` format (introduced in iOS 12).
 Those files work only with ``ARWorldTrackingConfiguration/detectionObjects``. A single
 session can't mix the two formats.
 */
API_AVAILABLE(ios(12.0))
NS_SWIFT_SENDABLE
@interface ARReferenceObject : NSObject <NSSecureCoding>

/**
 A descriptive name for the reference object.

 For a reference object loaded from an Xcode asset catalog, this property is the name assigned in the asset catalog. You can also use this property to
 assign a name to an object you've recorded in an AR session using ``ARSession/createReferenceObject(transform:center:extent:completionHandler:)``.

 - Note: This string is not localized text intended for user display. However, in debugging you can use this property to indicate which reference
 object was detected.
 */
@property (nonatomic, copy, nullable) NSString *name;

/**
 The center point of the reference object's space-mapping data.

 The ``extent`` and ``center`` properties together define a bounding box for the data recorded in the reference object in its local coordinate system.
 You define that coordinate system with the transform parameter when calling
 ``ARSession/createReferenceObject(transform:center:extent:completionHandler:)``, and can modify it by creating another reference object with
 ``ARReferenceObject/applyingTransform(_:)``.
 */
@property (nonatomic, readonly) simd_float3 center;

/**
 The size of the reference object's space-mapping data.

 The ``extent`` and ``center`` properties together define a bounding box for the data recorded in the reference object in its local coordinate system.
 You define that coordinate system with the transform parameter when calling
 ``ARSession/createReferenceObject(transform:center:extent:completionHandler:)``, and can modify it by creating another reference object with
 ``ARReferenceObject/applyingTransform(_:)``.
 */
@property (nonatomic, readonly) simd_float3 extent;

/**
 A scale factor for the local coordinate space the reference object defines.

 Multiplying the ``extent`` by this scale results in the physical size of the object in meters.
*/
@property (nonatomic, readonly) simd_float3 scale;

/**
 The AR resource group name for this object.

 If ARKit loaded this object from an AR resource group in an asset catalog, ARKit sets the value of this property to the resource group's name.
 Otherwise, the value of this property is `nil`.
*/
@property (nonatomic, strong, nullable, readonly)
    NSString *resourceGroupName API_DEPRECATED("Only supported for legacy reference objects.", ios(13.0, 27.0));

/**
 A coarse representation of the space-mapping data contained in the reference object.

 These points represent notable features detected in camera imagery during the session that recorded the reference object. ARKit extrapolates the
 locations of these features in 3D world coordinate space as part of the image and motion analysis that tracks the device's movement in a session.
 Taken together, these points loosely correlate to the contours of real-world objects that were in view of the camera during the session.

 ARKit does not guarantee that the number and arrangement of raw feature points will remain stable between software releases. However, you can
 visualize the point cloud to debug your app's object recording or detection, or inspect its size to estimate the quality of a recorded object.

 For reference objects loaded from a `.referenceobject` file, this property returns an empty point cloud.
 */
@property (nonatomic, strong, readonly) ARPointCloud *rawFeaturePoints API_DEPRECATED("Only supported for legacy reference objects.", ios(12.0, 27.0))
    ;

/**
 The URL to the extracted USDZ model, if available.
 */
@property (nonatomic, strong, nullable, readonly) NSURL *usdzFile API_AVAILABLE(ios(27.0));

/**
 Returns the set of ARReferenceObjects in the specified resource group and bundle.

 To use the objects for detection in a world-tracking AR session, provide this set for your session configuration's
 ``ARWorldTrackingConfiguration/detectionObjects`` property.

 - Parameters:
   - name: The name of an AR Resource Group from your Xcode project's main asset catalog.
   - bundle: The bundle from which to load asset catalog resources, or `nil` to use your app's main bundle.

 - Returns: A set of all unique reference objects in the specified group, or `nil` on error.
*/
+ (nullable NSSet<ARReferenceObject *> *)referenceObjectsInGroupNamed:(NSString *)name
                                                               bundle:(nullable NSBundle *)bundle
    API_DEPRECATED("Only supported for legacy reference objects.", ios(12.0, 27.0));

/**
 Loads a reference object from the specified file URL.

 To use the object for detection in a world-tracking AR session, add it to the ``ARWorldTrackingConfiguration/detectionObjects`` set in your session
 configuration.

 - Parameters:
   - url: The local file `URL` from which to read data (`.arobject` or `.referenceobject` archive).
   - error: A pointer to an <doc://com.apple.documentation/documentation/foundation/nserror> object. If this method returns `nil`, check this pointer
 for an error describing the failure.
*/
- (nullable instancetype)initWithArchiveURL:(NSURL *)url error:(NSError **)error;

/**
 Writes a binary representation of the object to the specified file URL.

 After exporting a reference object from your object-scanning app to a file, you can bundle that reference object into other apps you create by
 inserting it into an Xcode asset catalog.

 The `URL` path should use `ARReferenceObjectArchiveExtension` (.arobject) for the file extension.
 If serialization across devices is desired, NSKeyedArchiver should be used instead.

 You can't export reference objects loaded from a `.referenceobject` file.

 - Parameters:
   - url: The file `URL` at which to write the reference object data.
   - previewImage: A thumbnail image to be embedded in the reference object's filesystem representation.

     ARKit ignores preview images when loading reference objects. Instead, this image helps make reference object files visually identifiable in
 external tools like Xcode, Finder, and Quick Look.
   - error: A pointer to an <doc://com.apple.documentation/documentation/foundation/nserror>. On completion, if the method returns
 <doc://com.apple.documentation/documentation/swift/false>, the pointer is populated with an object describing the failure.

 - Returns: <doc://com.apple.documentation/documentation/swift/true> if the operation succeeded. If
 <doc://com.apple.documentation/documentation/swift/false>, check the `error` parameter for failure details.
*/
- (BOOL)exportObjectToURL:(NSURL *)url
             previewImage:(nullable UIImage *)previewImage
                    error:(NSError **)error API_DEPRECATED("Only supported for legacy reference objects.", ios(12.0, 27.0));

/**
 Returns a new reference object by applying the specified transform to the object's origin.

 You define the local coordinate space of a reference object with the transform parameter when you create it with
 ``ARSession/createReferenceObject(transform:center:extent:completionHandler:)``. If an existing reference object has a local coordinate origin that
 doesn't fit well with the object's intended use, call this method to change the reference object's origin with respect to the physical object it
 represents.

 When ARKit detects a reference object, the ``ARAnchor/transform`` of the resulting ``ARObjectAnchor`` is based on the origin of the reference
 object's coordinate system. For example, if a reference object represents a physical item that sits on a horizontal surface, virtual content should
 appear to sit on whatever surface the physical object does. As such, it's typically useful to align a reference object's coordinate origin with the
 bottom of the physical object.

 For reference objects loaded from a `.referenceobject` file, this method returns the same reference object unchanged.

 - Parameter transform: A transform matrix in the local coordinate space of the reference object.

 - Returns: The transformed reference object.
*/
- (ARReferenceObject *)referenceObjectByApplyingTransform:(simd_float4x4)transform
    API_DEPRECATED("Only supported for legacy reference objects.", ios(12.0, 27.0));

/**
 Returns a new reference object that combines spatial information from both this reference object and another.

 The accuracy of 3D object detection depends on similarity of lighting and environmental conditions between when you scan a real object (producing an
 ``ARReferenceObject``) and when a user of your app attempts to detect that object. If, for example, you scan an object in a bright environment, then
 a user attempts to detect it in a dark environment, ARKit may fail to recognize that the real object matches the reference object, or may not detect
 the object quickly.

 To make a reference object that is more robust in a wide variety of detection conditions, scan the same real-world object multiple times: For each
 scan, vary the lighting conditions or the background environment to capture the variety of situations in which your app might attempt to detect the
 same real object. Then, use this method to combine those scan results into a single ``ARReferenceObject`` incorporating recognition information for
 all the conditions you scanned in.

 You can't merge reference objects loaded from a `.referenceobject` file.

 - Parameters:
   - object: The other reference object with which to combine this reference object.
   - error: A pointer to an <doc://com.apple.documentation/documentation/foundation/nserror>. On completion, if the method returns `nil`, this pointer
 references an object describing the failure.

 - Returns: A new ``ARReferenceObject`` that includes the spatial information from both objects. From Swift, this method throws an ``ARError`` if the
 two objects cannot be merged. From Objective-C, it returns `nil` and populates the `error` parameter with a description of the failure.
*/
- (nullable ARReferenceObject *)referenceObjectByMergingObject:(ARReferenceObject *)object
                                                         error:(NSError **)error
    API_DEPRECATED("Only supported for legacy reference objects.", ios(12.0, 27.0));

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
#import <ARKitCore/ARReferenceObject.h> 
#endif // #if (defined(USE_ARKIT_PUBLIC_HEADERS) \&\& USE_ARKIT_PUBLIC_HEADERS) || !__has_include(<ARKitCore/ARReferenceObject.h>)