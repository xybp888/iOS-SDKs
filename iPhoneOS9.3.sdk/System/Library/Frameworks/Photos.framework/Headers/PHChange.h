//
//  PHChange.h
//  Photos
//
//  Copyright (c) 2013 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

@class PHObject;
@class PHObjectChangeDetails;
@class PHFetchResultChangeDetails;
@class PHFetchResult;

NS_ASSUME_NONNULL_BEGIN

NS_CLASS_AVAILABLE_IOS(8_0) @interface PHChange : NSObject

- (nullable PHObjectChangeDetails *)changeDetailsForObject:(PHObject *)object;
- (nullable PHFetchResultChangeDetails *)changeDetailsForFetchResult:(PHFetchResult *)object;

@end



NS_CLASS_AVAILABLE_IOS(8_0) @interface PHObjectChangeDetails : NSObject

// the object in the state before this change (returns the object that was passed in to changeDetailsForObject:)
@property (atomic, strong, readonly) __kindof PHObject *objectBeforeChanges;

// the object in the state after this change
@property (atomic, strong, readonly, nullable) __kindof PHObject *objectAfterChanges;

// YES if the image or video content for this object has been changed
@property (atomic, readonly) BOOL assetContentChanged;

// YES if the object was deleted
@property (atomic, readonly) BOOL objectWasDeleted;

@end



NS_CLASS_AVAILABLE_IOS(8_0) @interface PHFetchResultChangeDetails : NSObject

// fetch result with the state of the fetched objects before this change (returns the fetch result passed in to changeDetailsForFetchResult:)
@property (atomic, strong, readonly) PHFetchResult *fetchResultBeforeChanges;

// fetch result with the state of the fetched objects after this change
@property (atomic, strong, readonly) PHFetchResult *fetchResultAfterChanges;

// YES if the changes to this fetch result are described by the removed/inserted/changed details.
// NO indicates that the scope of changes were too large and UI clients should do a full reload, incremental changes could not be provided
@property (atomic, assign, readonly) BOOL hasIncrementalChanges;

// The indexes of the removed items, relative to the 'before' state of the fetch result
// returns nil if hasIncrementalChanges is NO
@property (atomic, strong, readonly, nullable) NSIndexSet *removedIndexes;
@property (atomic, strong, readonly) NSArray<__kindof PHObject *> *removedObjects;

// The indexes of the inserted items, relative to the 'before' state of the fetch result after applying the removedIndexes
// returns nil if hasIncrementalChanges is NO
@property (atomic, strong, readonly, nullable) NSIndexSet *insertedIndexes;
@property (atomic, strong, readonly) NSArray<__kindof PHObject *> *insertedObjects;

// The indexes of the updated items, relative to the 'after' state of the fetch result
// returns nil if hasIncrementalChanges is NO
@property (atomic, strong, readonly, nullable) NSIndexSet *changedIndexes;
@property (atomic, strong, readonly) NSArray<__kindof PHObject *> *changedObjects;

// Enumerates the indexes of the moved items, relative to the 'before' state of the fetch result after applying the removedIndexes and insertedIndexes
- (void)enumerateMovesWithBlock:(void(^)(NSUInteger fromIndex, NSUInteger toIndex))handler;

// YES if there are moved items
// returns NO if hasIncrementalChanges is NO
@property (atomic, assign, readonly) BOOL hasMoves;


// Provides a "diff" between 2 PHFetchResult objects.
+ (instancetype)changeDetailsFromFetchResult:(PHFetchResult *)fromResult toFetchResult:(PHFetchResult *)toResult changedObjects:(NSArray<PHObject *> *)changedObjects;

@end

NS_ASSUME_NONNULL_END