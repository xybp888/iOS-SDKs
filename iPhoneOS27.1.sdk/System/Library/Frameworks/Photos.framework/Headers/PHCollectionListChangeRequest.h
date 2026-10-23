//
//  PHCollectionListChangeRequest.h
//  Photos
//
//  Copyright (c) 2013 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <Photos/PHChangeRequest.h>
#import <Photos/PHFetchResult.h>

@class PHCollection;
@class PHCollectionList;
@class PHObjectPlaceholder;

NS_ASSUME_NONNULL_BEGIN
API_AVAILABLE_BEGIN(macos(10.15), ios(8), tvos(10))

// PHCollectionListChangeRequest can only be created or used within a -[PHPhotoLibrary performChanges:] or -[PHPhotoLibrary performChangesAndWait:] block.
OS_EXPORT
@interface PHCollectionListChangeRequest : PHChangeRequest

#pragma mark - Creating Collection Lists

+ (instancetype)creationRequestForCollectionListWithTitle:(NSString *)title;

// This can be used to fetch the newly created collection list after the change block has completed by using -localIdentifier
// It can also be added directly to collection lists within the current change block
@property (nonatomic, strong, readonly) PHObjectPlaceholder *placeholderForCreatedCollectionList;

#pragma mark - Deleting Collection Lists

// requests that the specified collection lists and all their child collections (recursively) be deleted
+ (void)deleteCollectionLists:(id<NSFastEnumeration>)collectionLists;


#pragma mark - Modifying Collection Lists

/*!
 Creates a request for modifying the specified collection list.

 After you create a change request within a photo library change block, propose changes to the collection’s title or list of child collections with the properties and instance methods of the change request. After Photos runs your change block, the collection list reflects your changes. For details on change blocks, see PHPhotoLibrary.
 
 Use this method when you you don’t need to work with indexes in the list of child collections. If you need to insert, remove, or rearrange collections at specified indexes in the collection list, use the `changeRequestForCollectionList:childCollections:` method instead.

 Use `canPerformEditOperation:` on the collection list to determine if the type of change is allowed. If the collection list does not allow the type of change requested the changes request will fail and an error is returned.

 - Parameters:
 - collectionList: the collection list being modified
 */
+ (nullable instancetype)changeRequestForCollectionList:(PHCollectionList *)collectionList;

/*!
 Creates a request for modifying the specified collection list, with a fetch result for tracking changes.
  
 Use this method when you need to insert, remove, or rearrange collections at specified indexes in the collection list. By passing in a fetch result reflecting what your app sees as the current state of the collection’s membership, the Photos framework can ensure that the indexes you specify are valid even if the collection has changed since you last fetched it. If you don’t need to work with indexes in the list of child collections, you can use the `changeRequestForCollectionList:` method instead.

 Call `canPerformEditOperation:` on the collection list to determine if the type of change is allowed. If the collection list does not allow the type of change requested, the .

 - Parameters:
 - collectionList: the collection list being modified
 - childCollections: the child collections to modify (see `fetchCollectionsInCollectionList:options:`)
 */
+ (nullable instancetype)changeRequestForCollectionList:(PHCollectionList *)collectionList childCollections:(PHFetchResult<__kindof PHCollection *> *)childCollections;

/*!
 Creates a request to add, remove, or rearrange child collections in the top-level collection list.
 
 To add, remove or rearrange child collections in the top-level collection list, passing in the fetched collections in that collection list will ensure that the child collection positions are tracked correctly in the case that the collection list has been externally edited after the fetch, but before this change is applied
 
 This is the equivalent to calling `changeRequestForCollectionList:childCollections:` with the collection list matching the type `PHCollectionListTypeFolder` and subtype `PHCollectionListSubtypeRootFolder`
 
 - Parameters:
 - childCollections: the child collections to modify (see `fetchTopLevelUserCollections:options:`)
 */
+ (nullable instancetype)changeRequestForTopLevelCollectionListUserCollections:(PHFetchResult<__kindof PHCollection *> *)childCollections API_AVAILABLE(macos(11), ios(14.2), tvos(14));

@property (nonatomic, strong, readwrite) NSString *title;

#pragma mark - Mutating child collections

// A PHCollection can only belong to a single parent PHCollection
- (void)addChildCollections:(id<NSFastEnumeration>)collections;
- (void)insertChildCollections:(id<NSFastEnumeration>)collections atIndexes:(NSIndexSet *)indexes;
- (void)removeChildCollections:(id<NSFastEnumeration>)collections;
- (void)removeChildCollectionsAtIndexes:(NSIndexSet *)indexes;
- (void)replaceChildCollectionsAtIndexes:(NSIndexSet *)indexes withChildCollections:(id<NSFastEnumeration>)collections;

// The move removes the child collections at fromIndexes first then inserts those collections at the toIndex, so toIndex should point to a location based on the updated indexes after having removed the child collections at fromIndexes
- (void)moveChildCollectionsAtIndexes:(NSIndexSet *)indexes toIndex:(NSUInteger)toIndex;

@end

API_AVAILABLE_END
NS_ASSUME_NONNULL_END
