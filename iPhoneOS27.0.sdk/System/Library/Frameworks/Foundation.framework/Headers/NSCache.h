/*      NSCache.h
        Copyright (c) 2008-2019, Apple Inc. All rights reserved.
*/

#import <Foundation/NSObject.h>

@class NSString;
@protocol NSCacheDelegate;

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

/// A mutable collection you use to temporarily store transient key-value pairs that are subject to eviction when resources are low.
///
/// Cache objects differ from other mutable collections in a few ways:
///
/// - The ``NSCache`` class incorporates various auto-eviction policies, which ensure that a cache doesn't use too much of the system's memory. If memory is needed by other applications, these policies remove some items from the cache, minimizing its memory footprint.
/// - You can add, remove, and query items in the cache from different threads without having to lock the cache yourself.
/// - Unlike an ``NSMutableDictionary`` object, a cache does not copy the key objects that are put into it.
///
/// You typically use ``NSCache`` objects to temporarily store objects with transient data that are expensive to create. Reusing these objects can provide performance benefits, because their values do not have to be recalculated. However, the objects are not critical to the application and can be discarded if memory is tight. If discarded, their values will have to be recomputed again when needed.
///
/// Objects that have subcomponents that can be discarded when not being used can adopt the ``NSDiscardableContent`` protocol to improve cache eviction behavior. By default, ``NSDiscardableContent`` objects in a cache are automatically removed if their content is discarded, although this automatic removal policy can be changed. If an ``NSDiscardableContent`` object is put into the cache, the cache calls ``NSDiscardableContent/discardContentIfPossible()`` on it upon its removal.
API_AVAILABLE(macos(10.6), ios(4.0), watchos(2.0), tvos(9.0))
@interface NSCache <KeyType, ObjectType> : NSObject

/// The name of the cache.
///
/// The default value is an empty string ("").
@property (copy) NSString *name;

/// The cache's delegate.
///
/// The delegate must adopt the `NSCacheDelegate` protocol.
@property (nullable, assign) id<NSCacheDelegate> delegate;

/// Returns the value associated with a given key.
///
/// - Parameter key: An object identifying the value.
/// - Returns: The value associated with `key`, or `nil` if no value is associated with `key`.
- (nullable ObjectType)objectForKey:(KeyType)key;
/// Sets the value of the specified key in the cache.
///
/// Unlike an `NSMutableDictionary` object, a cache does not copy the key objects that are put into it.
///
/// - Parameter obj: The object to be stored in the cache.
/// - Parameter key: The key with which to associate the value.
- (void)setObject:(ObjectType)obj forKey:(KeyType)key; // 0 cost
/// Sets the value of the specified key in the cache, and associates the key-value pair with the specified cost.
///
/// The `cost` value is used to compute a sum encompassing the costs of all the objects in the cache. When memory is limited or when the total cost of the cache eclipses the maximum allowed total cost, the cache could begin an eviction process to remove some of its elements.
///
/// Unlike an `NSMutableDictionary` object, a cache does not copy the key objects that are put into it.
///
/// - Parameter obj: The object to store in the cache.
/// - Parameter key: The key with which to associate the value.
/// - Parameter g: The cost with which to associate the key-value pair.
- (void)setObject:(ObjectType)obj forKey:(KeyType)key cost:(NSUInteger)g;
/// Removes the value of the specified key in the cache.
///
/// - Parameter key: The key identifying the value to be removed.
- (void)removeObjectForKey:(KeyType)key;

/// Empties the cache.
- (void)removeAllObjects;

/// The maximum total cost that the cache can hold before it starts evicting objects.
///
/// If `0`, there is no total cost limit. The default value is `0`.
///
/// This is not a strict limit, and if the cache goes over the limit, an object in the cache could be evicted instantly, at a later point in time, or possibly never, all depending on the implementation details of the cache.
@property NSUInteger totalCostLimit;	// limits are imprecise/not strict
/// The maximum number of objects the cache should hold.
///
/// If `0`, there is no count limit. The default value is `0`.
///
/// This is not a strict limit -- if the cache goes over the limit, an object in the cache could be evicted instantly, later, or possibly never, depending on the implementation details of the cache.
@property NSUInteger countLimit;	// limits are imprecise/not strict
/// Whether the cache will automatically evict discardable-content objects whose content has been discarded.
///
/// If `YES`, the cache will evict a discardable-content object after its content is discarded. If `NO`, it will not. The default value is `YES`.
@property BOOL evictsObjectsWithDiscardedContent;

@end

/// The delegate of an ``NSCache`` object implements this protocol to perform specialized actions when an object is about to be evicted or removed from the cache.
@protocol NSCacheDelegate <NSObject>
@optional
/// Called when an object is about to be evicted or removed from the cache.
///
/// It is not possible to modify `cache` from within the implementation of this delegate method.
///
/// - Parameter cache: The cache with which the object of interest is associated.
/// - Parameter obj: The object of interest in the cache.
- (void)cache:(NSCache *)cache willEvictObject:(id)obj;
@end

NS_HEADER_AUDIT_END(nullability, sendability)
