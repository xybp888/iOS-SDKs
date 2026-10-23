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
 An optional name used to identify the object.
 */
@property (nonatomic, copy, nullable) NSString *name;

/**
 The center of the object in the object’s local coordinate space.
 */
@property (nonatomic, readonly) simd_float3 center;

/**
 The extent of the object in the object’s local coordinate space.
 */
@property (nonatomic, readonly) simd_float3 extent;

/**
 The scale of the object’s local coordinate space.

 Multiplying the extent by this scale will result in the physical extent of the object, measured in meters.
*/
@property (nonatomic, readonly) simd_float3 scale;

/**
 The AR resource group name for this object.

 If this object was loaded via an AR resource group in the Xcode asset catalogue this property will have the name of the resource group,
 else be set to `nil`.
*/
@property (nonatomic, strong, nullable, readonly)
    NSString *resourceGroupName API_DEPRECATED("Only supported for legacy reference objects.", ios(13.0, 27.0));

/**
 The feature points of the object.

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

 - Parameters:
   - name: The name of the resource group.
   - bundle: The bundle containing the image file or asset catalog. Specify `nil` to search the app’s main bundle.

 - Returns: The set of reference objects or `nil` on error.
*/
+ (nullable NSSet<ARReferenceObject *> *)referenceObjectsInGroupNamed:(NSString *)name
                                                               bundle:(nullable NSBundle *)bundle
    API_DEPRECATED("Only supported for legacy reference objects.", ios(12.0, 27.0));

/**
 Initializes a new reference object with the contents of an archive at the specified URL.

 - Parameters:
   - url: The local file `URL` from which to read data (`.arobject` or `.referenceobject` archive).
   - error: The error to populate if the object could not be initialized.

 - Returns: An initialized reference object.
*/
- (nullable instancetype)initWithArchiveURL:(NSURL *)url error:(NSError **)error;

/**
 Exports the object as an archive at the given URL.

 The `URL` path should use `ARReferenceObjectArchiveExtension` (.arobject) for the file extension.
 If serialization across devices is desired, NSKeyedArchiver should be used instead.

 You can't export reference objects loaded from a `.referenceobject` file.

 - Parameters:
   - url: The `URL` at which to write the exported object.
   - previewImage: An optional preview image to include in the archive.
   - error: The error to populate if the write is not successful.

 - Returns: `YES` if the location is written successfully, otherwise `NO`.
*/
- (BOOL)exportObjectToURL:(NSURL *)url
             previewImage:(nullable UIImage *)previewImage
                    error:(NSError **)error API_DEPRECATED("Only supported for legacy reference objects.", ios(12.0, 27.0));

/**
 Returns a new reference object by applying the specified transform to the object's origin.

 This can be used to change the reference object's origin with respect to the physical object. Providing
 a transform local to the current object's coordinate space will return an object with the transform's position and orientation as the origin.

 For reference objects loaded from a `.referenceobject` file, this method returns the same reference object unchanged.

 - Parameter transform: The rotation and translation to apply to the object's origin.

 - Returns: A reference object with updated origin.
*/
- (ARReferenceObject *)referenceObjectByApplyingTransform:(simd_float4x4)transform
    API_DEPRECATED("Only supported for legacy reference objects.", ios(12.0, 27.0));

/**
 Returns a new reference object by aligning and merging the provided object with this reference.

 This can be used to combine multiple scans of the same object for detection in different conditions. The object being merged
 must share similar feature points for the merge to succeed.

 You can't merge reference objects loaded from a `.referenceobject` file.

 - Parameters:
   - object: The reference object to align and merge.
   - error: The error to populate if the merge is not successful.

 - Returns: A new reference object combining features of both scans or `nil` if the merge was not successful.
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
