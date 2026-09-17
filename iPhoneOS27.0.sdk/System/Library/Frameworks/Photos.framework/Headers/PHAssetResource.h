//
//  PHAssetResource.h
//  Photos
//
//  Copyright © 2015 Apple Inc. All rights reserved.
//

#import <Photos/PhotosTypes.h>

@class PHAsset;
@class PHAssetResourceUploadJob;
@class PHLivePhoto;
@class UTType;


NS_ASSUME_NONNULL_BEGIN
API_AVAILABLE_BEGIN(macos(10.15), ios(9), tvos(10))

OS_EXPORT
@interface PHAssetResource : NSObject

/// Describes the type of asset resource represented by this object, e.g. `photo`
@property (nonatomic, assign, readonly) PHAssetResourceType type;

/// The local identifier of the asset associated with this asset resource
@property (nonatomic, copy, readonly) NSString *assetLocalIdentifier;


@property (nonatomic, copy, readonly) NSString *originalFilename API_DEPRECATED("Use filename instead", ios(9, 27), macos(10.15, 27), tvos(10, 27), visionos(1, 27));


/// The filename associated with this asset resource (if any)
@property (nonatomic, copy, readonly, nullable) NSString *filename API_AVAILABLE(macos(27), ios(27), tvos(27), visionos(27));

/// The content type of the data associated with this asset resource (the data can be retrieved via `PHAssetResourceManager`)
@property (nonatomic, copy, readonly) UTType *contentType API_AVAILABLE(macos(26.0), ios(26.0), tvos(26.0), visionos(26.0));
@property (nonatomic, copy, readonly) NSString *uniformTypeIdentifier API_DEPRECATED("Use contentType instead", ios(9, API_TO_BE_DEPRECATED), macos(10.15, API_TO_BE_DEPRECATED), tvos(10, API_TO_BE_DEPRECATED), visionos(1, API_TO_BE_DEPRECATED));

@property (nonatomic, assign, readonly) NSInteger pixelWidth API_AVAILABLE(macos(13), ios(16), tvos(16));
@property (nonatomic, assign, readonly) NSInteger pixelHeight API_AVAILABLE(macos(13), ios(16), tvos(16));

/// The size of the resource in bytes if known, `nil` if unavailable (may not be available until resource download/processing is complete)
@property (nonatomic, copy, readonly, nullable) NSNumber *dataSize NS_REFINED_FOR_SWIFT API_AVAILABLE(macos(27), ios(27), tvos(27), visionos(27));

#pragma mark - Getting resources


+ (NSArray<PHAssetResource *> *)assetResourcesForAsset:(PHAsset *)asset;
+ (NSArray<PHAssetResource *> *)assetResourcesForLivePhoto:(PHLivePhoto *)livePhoto API_AVAILABLE(ios(9.1));


/*!
 Returns the asset resource associated with the given upload job.

 - Parameters:
 - job: the upload job whose associated asset resource is returned

 - Returns: The asset resource associated with the upload job, or nil if the resource cannot be found.
 */
+ (nullable PHAssetResource *)assetResourceForUploadJob:(PHAssetResourceUploadJob *)job NS_SWIFT_NAME(assetResource(forUploadJob:)) API_AVAILABLE(ios(27), macCatalyst(27), macos(27)) API_UNAVAILABLE(tvos, visionos, watchos);

@end

API_AVAILABLE_END
NS_ASSUME_NONNULL_END


