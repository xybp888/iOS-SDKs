/*	NSMetadata.h
	Copyright (c) 2004-2019, Apple Inc. All rights reserved.
*/

#import <Foundation/NSMetadataAttributes.h>

#import <Foundation/NSObject.h>
#import <Foundation/NSDate.h>
#import <Foundation/NSNotification.h>

@class NSString, NSURL, NSArray<ObjectType>, NSDictionary<KeyType, ObjectType>, NSPredicate, NSOperationQueue, NSSortDescriptor;
@class NSMetadataItem, NSMetadataQueryAttributeValueTuple, NSMetadataQueryResultGroup;
@protocol NSMetadataQueryDelegate;

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

/// A query that you perform against Spotlight metadata.
///
/// The ``NSMetadataQuery`` class encapsulates the functionality provided by the <doc://com.apple.documentation/documentation/coreservices/file_metadata/mdquery> opaque type for querying the Spotlight metadata.
///
/// ``NSMetadataQuery`` objects provide metadata query results in several ways:
///
/// - As individual attribute values for requested attributes.
/// - As value lists that contain the distinct values for given attributes in the query results.
/// - As a result array proxy, containing all the query results. This is suitable for use with Cocoa bindings.
/// - As a hierarchical collection of results, grouping together items with the same values for specified grouping attributes. This is also suitable for use with Cocoa bindings.
///
/// Queries have two phases: the initial gathering phase that collects all currently matching results and a second live-update phase.
///
/// By default, the receiver has no limitation on its search scope. Use the ``searchScopes`` property to customize.
///
/// By default, notification of updated results occurs at 1.0 seconds. Use the ``notificationBatchingInterval`` property to customize.
///
/// You must set a predicate with the ``predicate`` property before starting a query.
API_AVAILABLE(macos(10.4), ios(5.0), watchos(2.0), tvos(9.0))
@interface NSMetadataQuery : NSObject {
@private
    NSUInteger _flags;
    NSTimeInterval _interval;
    id _private[11];
    void *_reserved;
}

/// The query's delegate.
///
/// This property contains an object that acts as the query's delegate, or nil. The delegate must implement the NSMetadataQueryDelegate protocol. Pass nil to remove the current delegate.
@property (nullable, assign) id<NSMetadataQueryDelegate> delegate;

/// The predicate used to filter query results.
///
/// Setting this property while a query is running stops the query and discards the current results. The receiver immediately starts a new query.
@property (nullable, copy) NSPredicate *predicate;

/// An array of sort descriptors to use when sorting the query results.
@property (copy) NSArray<NSSortDescriptor *> *sortDescriptors;

/// An array of attributes whose values are gathered by the query.
@property (copy) NSArray<NSString *> *valueListAttributes;

/// An array of attributes used to group query results.
@property (nullable, copy) NSArray<NSString *> *groupingAttributes;

/// The interval at which notification of updated results occurs.
@property NSTimeInterval notificationBatchingInterval;

/// An array of search scopes that limits where the query searches for results.
///
/// Scopes is an NSArray of NSURL objects (file URLs only) and/or string
/// paths and/or the special string constants below, which specifies the
/// locations to which the search is limited; an empty array means no
/// limits, which is the default state.
@property (copy) NSArray *searchScopes;

/// An array of objects that the query will search.
///
/// Items can be a mixture of NSMetadataItem, NSURL objects (file URLs only)
/// and/or string paths; the getter returns the same mixture as was set.
@property (nullable, copy) NSArray *searchItems API_AVAILABLE(macos(10.9), ios(7.0), watchos(2.0), tvos(9.0));

/// An optional operation queue for notifications and delegate method calls.
@property (nullable, retain) NSOperationQueue *operationQueue API_AVAILABLE(macos(10.9), ios(7.0), watchos(2.0), tvos(9.0));

/// Attempts to start the query.
///
/// Returns YES when successful; otherwise, NO. A query may fail to start if it does not specify a predicate, or if the query has already been started. This method must be called from the receiver's operationQueue or on the main thread.
- (BOOL)startQuery;

/// Stops the query from generating any further results.
- (void)stopQuery;

/// A Boolean value that indicates whether the query has started.
@property (readonly, getter=isStarted) BOOL started;

/// A Boolean value that indicates whether the query is in its initial gathering phase.
@property (readonly, getter=isGathering) BOOL gathering;

/// A Boolean value that indicates whether the query has been stopped.
@property (readonly, getter=isStopped) BOOL stopped;

/// Disables updates to the query results. These nest.
- (void)disableUpdates;

/// Enables updates to the query results.
- (void)enableUpdates;

/// The number of results returned by the query.
@property (readonly) NSUInteger resultCount;

/// Returns the query result at a specific index.
///
/// For performance reasons, use this method when retrieving a specific result, rather than the array returned by the results property.
- (id)resultAtIndex:(NSUInteger)idx;

/// Enumerates the current set of results using the given block.
///
/// This method disables the query at the start of the iteration and reenables it upon completion.
- (void)enumerateResultsUsingBlock:(void (NS_NOESCAPE ^)(id result, NSUInteger idx, BOOL *stop))block API_AVAILABLE(macos(10.9), ios(7.0), watchos(2.0), tvos(9.0));

/// Enumerates the current set of results using the given block and enumeration options.
- (void)enumerateResultsWithOptions:(NSEnumerationOptions)opts usingBlock:(void (NS_NOESCAPE ^)(id result, NSUInteger idx, BOOL *stop))block API_AVAILABLE(macos(10.9), ios(7.0), watchos(2.0), tvos(9.0));

/// An array containing the query's results.
///
/// This is for key-value bindings, and causes side-effects on the query.
@property (readonly, copy) NSArray *results;

/// Returns the index of the specified result.
- (NSUInteger)indexOfResult:(id)result;

/// A dictionary containing arrays of attribute value tuples, keyed by attribute name.
///
/// Values are arrays of `NSMetadataQueryAttributeValueTuple`.
@property (readonly, copy) NSDictionary<NSString *, NSArray<NSMetadataQueryAttributeValueTuple *> *> *valueLists;

/// An array of NSMetadataQueryResultGroups, for the first grouping attribute.
@property (readonly, copy) NSArray<NSMetadataQueryResultGroup *> *groupedResults;

/// Returns the value for the attribute name attrName at the index in the results specified by idx.
///
/// The attribute must be specified in valueListAttributes, as a sorting key in a specified sort descriptor, or as one of the grouping attributes specified for the query.
- (nullable id)valueOfAttribute:(NSString *)attrName forResultAtIndex:(NSUInteger)idx;

@end

/// An interface that enables the delegate of a metadata query to provide substitute results or attributes.
@protocol NSMetadataQueryDelegate <NSObject>
@optional

/// Implemented by the delegate to return a different object for a given query result.
- (id)metadataQuery:(NSMetadataQuery *)query replacementObjectForResultObject:(NSMetadataItem *)result;

/// Implemented by the delegate to return a replacement value for an attribute in a query result.
- (id)metadataQuery:(NSMetadataQuery *)query replacementValueForAttribute:(NSString *)attrName value:(id)attrValue;

@end

// notifications
/// Posted when the receiver begins with the initial result-gathering phase of the query.
FOUNDATION_EXPORT NSNotificationName const NSMetadataQueryDidStartGatheringNotification API_AVAILABLE(macos(10.4), ios(5.0), watchos(2.0), tvos(9.0));
/// Posted as the receiver is collecting results during the initial result-gathering phase of the query.
FOUNDATION_EXPORT NSNotificationName const NSMetadataQueryGatheringProgressNotification API_AVAILABLE(macos(10.4), ios(5.0), watchos(2.0), tvos(9.0));
/// Posted when the receiver has finished with the initial result-gathering phase of the query.
FOUNDATION_EXPORT NSNotificationName const NSMetadataQueryDidFinishGatheringNotification API_AVAILABLE(macos(10.4), ios(5.0), watchos(2.0), tvos(9.0));
/// Posted when the receiver's results have changed during the live-update phase of the query.
FOUNDATION_EXPORT NSNotificationName const NSMetadataQueryDidUpdateNotification API_AVAILABLE(macos(10.4), ios(5.0), watchos(2.0), tvos(9.0));

// keys for use with notification info dictionary
/// The key for retrieving an array of items added to the query result.
///
/// By default, this array contains ``NSMetadataItem`` objects, representing the query's results; however, the query's delegate can substitute these objects with instances of a different class.
FOUNDATION_EXPORT NSString * const NSMetadataQueryUpdateAddedItemsKey API_AVAILABLE(macos(10.9), ios(8.0), watchos(2.0), tvos(9.0));
/// The key for retrieving an array of items that have changed in the query result.
///
/// By default, this array contains ``NSMetadataItem`` objects, representing the query's results; however, the query's delegate can substitute these objects with instances of a different class.
FOUNDATION_EXPORT NSString * const NSMetadataQueryUpdateChangedItemsKey API_AVAILABLE(macos(10.9), ios(8.0), watchos(2.0), tvos(9.0));
/// The key for retrieving an array of items removed from the query result.
///
/// By default, this array contains ``NSMetadataItem`` objects, representing the query's results; however, the query's delegate can substitute these objects with instances of a different class.
FOUNDATION_EXPORT NSString * const NSMetadataQueryUpdateRemovedItemsKey API_AVAILABLE(macos(10.9), ios(8.0), watchos(2.0), tvos(9.0));

FOUNDATION_EXPORT NSString * const NSMetadataQueryResultContentRelevanceAttribute API_AVAILABLE(macos(10.4), ios(5.0), watchos(2.0), tvos(9.0));

// Scope constants for defined search locations
/// Searches the user's home directory.
FOUNDATION_EXPORT NSString * const NSMetadataQueryUserHomeScope API_AVAILABLE(macos(10.4)) API_UNAVAILABLE(ios, watchos, tvos);
/// Searches all local mounted volumes and the user home directory (even if remote).
FOUNDATION_EXPORT NSString * const NSMetadataQueryLocalComputerScope API_AVAILABLE(macos(10.4)) API_UNAVAILABLE(ios, watchos, tvos);
/// Searches all user-mounted remote volumes.
FOUNDATION_EXPORT NSString * const NSMetadataQueryNetworkScope API_AVAILABLE(macos(10.4)) API_UNAVAILABLE(ios, watchos, tvos);

/// Searches all indexed local mounted volumes and the user home directory (even if remote).
FOUNDATION_EXPORT NSString * const NSMetadataQueryIndexedLocalComputerScope API_AVAILABLE(macos(10.9)) API_UNAVAILABLE(ios, watchos, tvos);
/// Searches all indexed user-mounted remote volumes.
FOUNDATION_EXPORT NSString * const NSMetadataQueryIndexedNetworkScope API_AVAILABLE(macos(10.9)) API_UNAVAILABLE(ios, watchos, tvos);

// -setSearchScopes: will throw an exception if the given array contains a mix of the scope constants below with constants above.
/// The "Documents" subdirectory in the application's Ubiquity container.
FOUNDATION_EXPORT NSString * const NSMetadataQueryUbiquitousDocumentsScope API_AVAILABLE(macos(10.7), ios(5.0), watchos(2.0), tvos(9.0));
/// The application's Ubiquity container, excluding the "Documents" subdirectory.
FOUNDATION_EXPORT NSString * const NSMetadataQueryUbiquitousDataScope API_AVAILABLE(macos(10.7), ios(5.0), watchos(2.0), tvos(9.0));
/// Documents from outside the application's container that are accessible without user interaction. NSMetadataItemURLKey attributes of results are security-scoped NSURLs.
FOUNDATION_EXPORT NSString * const NSMetadataQueryAccessibleUbiquitousExternalDocumentsScope API_AVAILABLE(macos(10.10), ios(8.0), watchos(2.0), tvos(9.0));


/// The metadata associated with a file.
///
/// Metadata items provide a simple interface to retrieve the available attribute names and values.
API_AVAILABLE(macos(10.4), ios(5.0), watchos(2.0), tvos(9.0))
@interface NSMetadataItem : NSObject {
@private
    id _item;
    void *_reserved;
}

/// Initializes a metadata item with the given URL.
- (nullable instancetype)initWithURL:(NSURL *)url NS_DESIGNATED_INITIALIZER API_AVAILABLE(macos(10.9)) API_UNAVAILABLE(ios, watchos, tvos);

/// Returns the value for the specified attribute of the receiver.
- (nullable id)valueForAttribute:(NSString *)key;

/// Returns a dictionary containing the specified attributes and their values.
- (nullable NSDictionary<NSString *, id> *)valuesForAttributes:(NSArray<NSString *> *)keys;

/// An array containing the attributes of the receiver.
@property (readonly, copy) NSArray<NSString *> *attributes;

@end

/// The `NSMetadataQueryAttributeValueTuple` class represents attribute-value tuples, which are objects that contain the attribute name and value of a metadata attribute.
///
/// Attribute-value tuples are returned by `NSMetadataQuery` objects as the results in the value lists. Each attribute/value tuple contains the attribute name, the value, and the number of instances of that value that exist for the attribute name.
API_AVAILABLE(macos(10.4), ios(5.0), watchos(2.0), tvos(9.0))
@interface NSMetadataQueryAttributeValueTuple : NSObject {
@private
    id _attr;
    id _value;
    NSUInteger _count;
    void *_reserved;
}

/// The attribute name for the tuple.
@property (readonly, copy) NSString *attribute;

/// The attribute value for the tuple.
@property (nullable, readonly, retain) id value;

/// The number of results with the given attribute value.
@property (readonly) NSUInteger count;

@end

/// The `NSMetadataQueryResultGroup` class represents a collection of grouped attribute results returned by an ``NSMetadataQuery`` object.
API_AVAILABLE(macos(10.4), ios(5.0), watchos(2.0), tvos(9.0))
@interface NSMetadataQueryResultGroup : NSObject {
@private
    id _private[9];
    NSUInteger _private2[1];
    void *_reserved;
}

/// The attribute name for this result group.
@property (readonly, copy) NSString *attribute;

/// The attribute value for this result group.
@property (readonly, retain) id value;

/// An array of subgroups for this result group, or nil if this is a leaf group.
@property (nullable, readonly, copy) NSArray<NSMetadataQueryResultGroup *> *subgroups;

/// The number of results in this group.
@property (readonly) NSUInteger resultCount;

/// Returns the result at the specified index within this group.
- (id)resultAtIndex:(NSUInteger)idx;

/// An array containing the results in this group. This is for K-V Bindings, and causes side-effects on the query.
@property (readonly, copy) NSArray *results;

@end

NS_HEADER_AUDIT_END(nullability, sendability)
