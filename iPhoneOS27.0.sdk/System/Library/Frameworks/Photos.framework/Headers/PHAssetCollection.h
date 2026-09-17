//
//  PHAssetCollection.h
//  Photos
//
//  Copyright (c) 2013-2025 Apple Inc. All rights reserved.
//

#import <Photos/PHCollection.h>
#import <Photos/PhotosTypes.h>

@class PHAsset, PHCollectionList, PHFetchResult, PHFetchOptions;
@class CLLocation;

NS_ASSUME_NONNULL_BEGIN
API_AVAILABLE_BEGIN(macos(10.15), ios(8), tvos(10))

OS_EXPORT API_AVAILABLE(macos(10.13))
NS_SWIFT_SENDABLE
@interface PHAssetCollection : PHCollection

@property (nonatomic, assign, readonly) PHAssetCollectionType assetCollectionType;
@property (nonatomic, assign, readonly) PHAssetCollectionSubtype assetCollectionSubtype;

// These counts are just estimates; the actual count of objects returned from a fetch should be used if you care about accuracy. Returns NSNotFound if a count cannot be quickly returned.
@property (nonatomic, assign, readonly) NSUInteger estimatedAssetCount;

@property (nonatomic, strong, readonly, nullable) NSDate *startDate;
@property (nonatomic, strong, readonly, nullable) NSDate *endDate;

@property (nonatomic, strong, readonly, nullable) CLLocation *approximateLocation;
@property (nonatomic, strong, readonly) NSArray<NSString *> *localizedLocationNames;


#pragma mark - Fetching asset collections

// Fetch asset collections of a single type matching the provided local identifiers (type is inferred from the local identifiers)
+ (PHFetchResult<PHAssetCollection *> *)fetchAssetCollectionsWithLocalIdentifiers:(NSArray<NSString *> *)identifiers options:(nullable PHFetchOptions *)options;

// Fetch asset collections of a single type and subtype provided (use PHAssetCollectionSubtypeAny to match all subtypes)
+ (PHFetchResult<PHAssetCollection *> *)fetchAssetCollectionsWithType:(PHAssetCollectionType)type subtype:(PHAssetCollectionSubtype)subtype options:(nullable PHFetchOptions *)options;

// Smart Albums are not supported, only Albums and Moments
+ (PHFetchResult<PHAssetCollection *> *)fetchAssetCollectionsContainingAsset:(PHAsset *)asset withType:(PHAssetCollectionType)type options:(nullable PHFetchOptions *)options;

// assetGroupURLs are URLs retrieved from ALAssetGroup's ALAssetsGroupPropertyURL
+ (PHFetchResult<PHAssetCollection *> *)fetchAssetCollectionsWithALAssetGroupURLs:(NSArray<NSURL *> *)assetGroupURLs options:(nullable PHFetchOptions *)options API_DEPRECATED("Will be removed in a future release", ios(8,16), tvos(10,16), macos(10.15,13));


#pragma mark - Fetching moment asset collections (Deprecated)


+ (PHFetchResult<PHAssetCollection *> *)fetchMomentsInMomentList:(PHCollectionList *)momentList options:(nullable PHFetchOptions *)options API_DEPRECATED("Will be removed in a future release", ios(8, 13), tvos(10, 13)) API_UNAVAILABLE(macos);
+ (PHFetchResult<PHAssetCollection *> *)fetchMomentsWithOptions:(nullable PHFetchOptions *)options API_DEPRECATED("Will be removed in a future release", ios(8, 13), tvos(10, 13)) API_UNAVAILABLE(macos);



#pragma mark - Transient asset collections
// These asset collections are only in-memory and are not persisted to disk

+ (PHAssetCollection *)transientAssetCollectionWithAssets:(NSArray<PHAsset *> *)assets title:(nullable NSString *)title;
+ (PHAssetCollection *)transientAssetCollectionWithAssetFetchResult:(PHFetchResult<PHAsset *> *)fetchResult title:(nullable NSString *)title;


@end

API_AVAILABLE_END
NS_ASSUME_NONNULL_END
