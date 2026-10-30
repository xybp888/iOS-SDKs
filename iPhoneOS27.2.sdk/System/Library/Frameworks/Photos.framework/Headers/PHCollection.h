//
//  PHCollection.h
//  Photos
//
//  Copyright (c) 2013 Apple Inc. All rights reserved.
//

#import <Photos/PHObject.h>
#import <Photos/PHFetchResult.h>
#import <Photos/PhotosTypes.h>

@class PHCollectionList, PHFetchResult, PHFetchOptions;
@class CLLocation;

NS_ASSUME_NONNULL_BEGIN
API_AVAILABLE_BEGIN(macos(10.15), ios(8), tvos(10))

OS_EXPORT API_AVAILABLE(macos(10.13))
NS_SWIFT_SENDABLE
@interface PHCollection : PHObject

@property (nonatomic, assign, readonly) BOOL canContainAssets;
@property (nonatomic, assign, readonly) BOOL canContainCollections;
@property (nonatomic, strong, readonly, nullable) NSString *localizedTitle API_AVAILABLE(macos(10.13));

/// The last date at which this collection was modified.
@property (nonatomic, strong, readonly, nullable) NSDate *modificationDate API_AVAILABLE(macos(26), ios(26), tvos(26), visionos(26));

#pragma mark - Capabilities

- (BOOL)canPerformEditOperation:(PHCollectionEditOperation)anOperation;


#pragma mark - Fetching collections

/*!
 Retrieves collections from the specified collection list
 
 By default, the returned `PHFetchResult` object contains all collections in the specified collection list. To retrieve a more specific set of assets, provide a `PHFetchOptions` object that contains a filter predicate.

 - Parameters:
 - collectionList: The collection list from which to fetch collections
 - options: Options that specify a filter predicate and sort order for the fetched collections, or nil to use default options

 - Returns: A fetch result that contains the requested `PHCollection` objects, or an empty fetch result if no objects match the request.
 */
+ (PHFetchResult<PHCollection *> *)fetchCollectionsInCollectionList:(PHCollectionList *)collectionList options:(nullable PHFetchOptions *)options;

/*!
 Retrieves collections from the root of the photo library’s hierarchy of user-created albums and folders
 
 This is the equivalent to calling `fetchCollectionsInCollectionList:options:` with the collection list matching the type `PHCollectionListTypeFolder` and subtype `PHCollectionListSubtypeRootFolder`
 
 - Parameters:
 - options: Options that specify a filter predicate and sort order for the fetched collections, or nil to use default options
 
 - Returns: A fetch result containing the matching collection lists, in the library's natural order.
 */
+ (PHFetchResult<PHCollection *> *)fetchTopLevelUserCollectionsWithOptions:(nullable PHFetchOptions *)options;

@end

API_AVAILABLE_END
NS_ASSUME_NONNULL_END

// PHCollection subclasses declarations have been moved to their own header files, imported here for compatibility
#import <Photos/PHAssetCollection.h>
#import <Photos/PHCollectionList.h>
