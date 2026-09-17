//
//  PHCollectionList.h
//  Photos
//
//  Copyright (c) 2013-2025 Apple Inc. All rights reserved.
//

#import <Photos/PHCollection.h>
#import <Photos/PhotosTypes.h>

@class PHAssetCollection, PHFetchResult, PHFetchOptions;

NS_ASSUME_NONNULL_BEGIN
API_AVAILABLE_BEGIN(macos(10.15), ios(8), tvos(10))

OS_EXPORT API_AVAILABLE(macos(10.13))
NS_SWIFT_SENDABLE
@interface PHCollectionList : PHCollection

@property (nonatomic, assign, readonly) PHCollectionListType collectionListType;
@property (nonatomic, assign, readonly) PHCollectionListSubtype collectionListSubtype;

@property (nonatomic, strong, readonly, nullable) NSDate *startDate;
@property (nonatomic, strong, readonly, nullable) NSDate *endDate;

@property (nonatomic, strong, readonly) NSArray<NSString *> *localizedLocationNames;


#pragma mark - Fetching collection lists

// A PHAssetCollectionTypeMoment will be contained by a PHCollectionListSubtypeMomentListCluster and a PHCollectionListSubtypeMomentListYear
// Non-moment PHAssetCollections will only be contained by a single collection list
+ (PHFetchResult<PHCollectionList *> *)fetchCollectionListsContainingCollection:(PHCollection *)collection options:(nullable PHFetchOptions *)options;

// Fetch collection lists of a single type matching the provided local identifiers (type is inferred from the local identifiers)
+ (PHFetchResult<PHCollectionList *> *)fetchCollectionListsWithLocalIdentifiers:(NSArray<NSString *> *)identifiers options:(nullable PHFetchOptions *)options;

// Fetch asset collections of a single type and subtype provided (use PHCollectionListSubtypeAny to match all subtypes)
+ (PHFetchResult<PHCollectionList *> *)fetchCollectionListsWithType:(PHCollectionListType)collectionListType subtype:(PHCollectionListSubtype)subtype options:(nullable PHFetchOptions *)options;


#pragma mark - Fetching moment collection lists (Deprecated)


+ (PHFetchResult<PHCollectionList *> *)fetchMomentListsWithSubtype:(PHCollectionListSubtype)momentListSubtype containingMoment:(PHAssetCollection *)moment options:(nullable PHFetchOptions *)options API_DEPRECATED("Will be removed in a future release", ios(8, 13), tvos(10, 13)) API_UNAVAILABLE(macos);
+ (PHFetchResult<PHCollectionList *> *)fetchMomentListsWithSubtype:(PHCollectionListSubtype)momentListSubtype options:(nullable PHFetchOptions *)options API_DEPRECATED("Will be removed in a future release", ios(8, 13), tvos(10, 13)) API_UNAVAILABLE(macos);



#pragma mark - Transient collection lists

// These collection lists are only in-memory and are not persisted to disk
+ (PHCollectionList *)transientCollectionListWithCollections:(NSArray<PHCollection *> *)collections title:(nullable NSString *)title;
+ (PHCollectionList *)transientCollectionListWithCollectionsFetchResult:(PHFetchResult<PHCollection *> *)fetchResult title:(nullable NSString *)title;

@end

API_AVAILABLE_END
NS_ASSUME_NONNULL_END
