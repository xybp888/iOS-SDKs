//
//  CSSearchableIndex.h
//  CoreSpotlight
//
//  Copyright © 2015–2026 Apple Inc. All rights reserved.
//

#import <CoreSpotlight/CSSearchableItem.h>

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

extern NSString * const CSIndexErrorDomain API_AVAILABLE(macos(10.11), ios(9.0), visionos(1.0)) API_UNAVAILABLE(tvos, watchos);

typedef NS_ENUM(NSInteger, CSIndexErrorCode) {
    CSIndexErrorCodeUnknownError             = -1,
    CSIndexErrorCodeIndexUnavailableError    = -1000, //The indexer was unavailable
    CSIndexErrorCodeInvalidItemError         = -1001, //The CSSearchableItem is invalid for some reason
    CSIndexErrorCodeInvalidClientStateError  = -1002, //The provided clientState was not valid for some reason
    CSIndexErrorCodeRemoteConnectionError    = -1003, //There was an error trying to communicate with the remote process
    CSIndexErrorCodeQuotaExceeded            = -1004, //Quota for bundle was exceeded
    CSIndexErrorCodeIndexingUnsupported      = -1005, //Indexing isn't supported on this device
    CSIndexErrorCodeMismatchedClientState API_AVAILABLE(macos(15.0), ios(18.0), visionos(2.0)) API_UNAVAILABLE(tvos, watchos) = -1006, //The expected client state did not match the indexed one.
} API_AVAILABLE(macos(10.11), ios(9.0), visionos(1.0)) API_UNAVAILABLE(tvos, watchos);

@protocol CSSearchableIndexDelegate;

API_AVAILABLE(macos(10.11), ios(9.0), visionos(1.0))
API_UNAVAILABLE(tvos, watchos)
@interface CSSearchableIndex : NSObject

@property (weak,nullable) id<CSSearchableIndexDelegate> indexDelegate;

@property (nonatomic, readonly) NSFileProtectionType protectionClass API_AVAILABLE(macos(27.0), ios(27.0), visionos(27.0)) API_UNAVAILABLE(tvos, watchos);

// Not all devices support indexing.  Call this method to check if indexing is supported on the current device.
+ (BOOL)isIndexingAvailable;

+ (instancetype)defaultSearchableIndex;

// Apps can set a name for the index instance. This name is used as a handle for the client state used with the batch API, allowing a single client to have multiple client states; you have to retrieve the client state for an index instance with the same name as you used when setting the client state.
- (instancetype)initWithName:(NSString *)name;

// Apps can set a default protection class for items in their entitlements.  You can alternately create an instance with a custom protection class to use on iOS.  It should be one of NSFileProtectionComplete, NSFileProtectionCompleteUnlessOpen, or NSFileProtectionCompleteUntilFirstUserAuthentication.
- (instancetype)initWithName:(NSString *)name protectionClass:(nullable NSFileProtectionType)protectionClass;

// Call this method to add or update items in the index.
// Completion handlers will be called once the data has been journaled by the index.  If the completion handler returns an error, the client should retry, as it was not journaled correctly.
// reindexSearchableItemsWithIdentifiers will be called if the journaling completed successfully but the data was not able to be indexed for some reason.
- (void)indexSearchableItems:(NSArray<CSSearchableItem *> *)items completionHandler:(void (^ __nullable)(NSError * __nullable error))completionHandler;

// Call this method to remove items with the given identifiers from the index.
// Completion handlers will be called once the data has been journaled by the index.  If the completion handler returns an error, the client should retry, as it was not journaled correctly.
// reindexSearchableItemsWithIdentifiers will be called if the journaling completed successfully but the data was not able to be indexed for some reason.
- (void)deleteSearchableItemsWithIdentifiers:(NSArray<NSString *> *)identifiers completionHandler:(void (^ __nullable)(NSError * __nullable error))completionHandler;

// Call this method on the index to remove any items from the index with the given domain identifiers.
// The delete is recursive so if domain identifiers are of the form <account-id>.<mailbox-id>, for example,
// calling delete with <account-id> will delete all the searchable items with that account and any mailbox.
- (void)deleteSearchableItemsWithDomainIdentifiers:(NSArray<NSString *> *)domainIdentifiers completionHandler:(void (^ __nullable)(NSError * __nullable error))completionHandler;

// Call this method to delete all searchable items from the index.
- (void)deleteAllSearchableItemsWithCompletionHandler:(void (^ __nullable)(NSError * __nullable error))completionHandler;

@end

API_AVAILABLE(macos(10.11), ios(9.0), visionos(1.0))
API_UNAVAILABLE(tvos, watchos)
@interface CSSearchableIndex (CSOptionalBatching)

// Batching:

// For some clients, it may be beneficial to batch updates to the index.  Those clients can use batching and persist client state information (< 250 bytes) in the index.  That state information can be used to determine where indexing needs to resume from in case of a client crash or jetsam. Batching is supported for indexSearchableItems deleteSearchableItemsWithIdentifiers.  Persisted client state will be reset whenever deleteAllSearchableItemsWithCompletionHandler is called.

// Note: Batching is unsupported for the CSSearchableIndex returned by the defaultSearchableIndex method

// Thread safety: In batch mode, the client takes responsibility for protecting the private CSSearchableIndex instance from concurrent access from multiple threads. Concurrent calls to the index instance will have undefined results. beginIndexBatch must not be called again before endIndexBatchWithClientState:completionHandler: has returned (it is however safe to call before the completionHandler passed to endIndexBatchWithClientState:completionHandler has been called).


// Begin a batch of index adds, updates, or deletes.
- (void)beginIndexBatch;

// End a batch passing in expected client state information to be persisted in the index, along with new client state for the current batch. The completion handler will be called once the client state has been persisted. If the client state does not match expected, an error of CSIndexErrorCodeMismatchedClientState will be returned.
- (void)endIndexBatchWithExpectedClientState:(nullable NSData *)expectedClientState newClientState:(NSData *)newClientState completionHandler:(void (^ __nullable)(NSError * __nullable error))completionHandler NS_SWIFT_NAME(endIndexBatch(expectedClientState:newClientState:completionHandler:)) API_AVAILABLE(macos(15.0), ios(18.0), visionos(2.0)) API_UNAVAILABLE(tvos, watchos);

// End a batch passing in client state information to be persisted in the index. The completion handler will be called once the client state has been persisted.
- (void)endIndexBatchWithClientState:(NSData *)clientState completionHandler:(void (^ __nullable)(NSError * __nullable error))completionHandler;

// Async fetches the app's last stored client state information.
- (void)fetchLastClientStateWithCompletionHandler:(void (^)(NSData * __nullable clientState,NSError * __nullable error))completionHandler;

@end

API_AVAILABLE(macos(13.0))
API_UNAVAILABLE(ios, tvos, watchos, visionos)
@interface CSSearchableIndex (CSExternalProvider)

- (void)fetchDataForBundleIdentifier:(NSString *)bundleIdentifier
                      itemIdentifier:(NSString *)itemIdentifier
                         contentType:(UTType *)contentType
                   completionHandler:(void (^)(NSData * _Nullable, NSError * _Nullable))completionHandler;

@end


// An application that is long running should provide a CSSearchableIndexDelegate conforming object to handle communication from the index.
// Alternatively, an app can provide an extension whose request handler conforms to this protocol and the extension will be called if the app isn't running.
API_AVAILABLE(macos(10.11), ios(9.0), visionos(1.0))
API_UNAVAILABLE(tvos, watchos)
@protocol CSSearchableIndexDelegate <NSObject>

@required

// The index requests that the delegate should reindex all of its searchable data and clear any local state that it might have persisted because the index has been lost.
// The app or extension should call indexSearchableItems on the passed in CSSearchableIndex.
// The app or extension must call the acknowledgement handler once any client state information has been persisted, that way, in case of a crash, the indexer can call this again.
// If the app passes clientState information in a batch, the acknowledgement can be called right away.
// The passed in index shouldn't be used in an extension if a custom protection class is needed.
- (void)searchableIndex:(CSSearchableIndex *)searchableIndex reindexAllSearchableItemsWithAcknowledgementHandler:(void (^)(void))acknowledgementHandler;

// The index requests that the delegate should reindex the searchable data with the provided identifiers.
// The app or extension should call indexSearchableItems:completionHandler on the passed in index CSSearchableIndex to update the items' states.
// The app or extension must call the acknowledgement handler once any client state information has been persisted, that way, in case of a crash, the indexer can call this again.
// If the app passes clientState information in a batch, the acknowledgement can be called right away.
// The passed in index shouldn't be used in an extension if a custom protection class is needed.
- (void)searchableIndex:(CSSearchableIndex *)searchableIndex reindexSearchableItemsWithIdentifiers:(NSArray <NSString *> *)identifiers
 acknowledgementHandler:(void (^)(void))acknowledgementHandler;

@optional

// When on battery power, it is possible for indexing to slowed down to prevent battery drain.
// The developer may want to optionally implement these methods to receive notice that indexing is being throttled and react accordingly (e.g. by priortizing indexing of more important content).
- (void)searchableIndexDidThrottle:(CSSearchableIndex *)searchableIndex;
- (void)searchableIndexDidFinishThrottle:(CSSearchableIndex *)searchableIndex;

// The developer may provide a NSData representation if type was specified in providerDataTypeIdentifiers property.
- (nullable NSData *)dataForSearchableIndex:(CSSearchableIndex *)searchableIndex itemIdentifier:(NSString *)itemIdentifier typeIdentifier:(NSString *)typeIdentifier error:(out NSError ** __nullable)outError API_AVAILABLE(macos(10.13), ios(11.0), visionos(1.0)) API_UNAVAILABLE(tvos, watchos);

// The developer may provide a NSURL to file representation representation if type was specified from providerDataTypeIdentifiers or providerInPlaceFileTypeIdentifiers property.
- (nullable NSURL *)fileURLForSearchableIndex:(CSSearchableIndex *)searchableIndex itemIdentifier:(NSString *)itemIdentifier typeIdentifier:(NSString *)typeIdentifier inPlace:(BOOL)inPlace error:(out NSError ** __nullable)outError API_AVAILABLE(macos(10.13), ios(11.0), visionos(1.0)) API_UNAVAILABLE(tvos, watchos);

// The index requests that the delegate provide searchable items for the provided identifiers with the default protection class
- (void)searchableItemsForIdentifiers:(NSArray <NSString *> *)identifiers searchableItemsHandler:(void (^)(NSArray<CSSearchableItem *> *items))searchableItemsHandler NS_SWIFT_ASYNC(2) API_AVAILABLE(macos(15.4), ios(18.4), visionos(2.4)) API_UNAVAILABLE(tvos, watchos);

// The index requests that the delegate provide searchable items for the provided identifiers in the specified protection class
- (void)searchableItemsForIdentifiers:(NSArray <NSString *> *)identifiers protectionClass:(NSFileProtectionType)protectionClass searchableItemsHandler:(void (^)(NSArray<CSSearchableItem *> *items))searchableItemsHandler NS_SWIFT_ASYNC(3) API_AVAILABLE(macos(27.0), ios(27.0), visionos(27.0)) API_UNAVAILABLE(tvos, watchos);

// The developer may want to be notified when an item has been updated with specific attributes (see: CSSearchableItemUpdateListenerOptions for Apple Intelligence attributes)
- (void)searchableItemsDidUpdate:(NSArray<CSSearchableItem *> *)items API_AVAILABLE(macos(15.4), ios(18.4), visionos(2.4)) API_UNAVAILABLE(tvos, watchos);

@end

NS_ASSUME_NONNULL_END
