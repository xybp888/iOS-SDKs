//
//  CKSyncEngine.h
//  CloudKit
//
//  Copyright © 2018 Apple Inc. All rights reserved.
//

#import <CloudKit/CKDefines.h>
#import <CloudKit/CKSyncEngineRecordZoneChangeBatch.h>

@class CKDatabase, CKOperationGroup, CKRecord, CKRecordID, CKRecordZone, CKRecordZoneID;
@class CKSyncEngineConfiguration, CKSyncEngineEvent, CKSyncEngineState, CKSyncEngineStateSerialization;
@class CKSyncEngineFetchChangesContext, CKSyncEngineFetchChangesOptions, CKSyncEngineFetchChangesScope;
@class CKSyncEngineSendChangesContext, CKSyncEngineSendChangesOptions, CKSyncEngineSendChangesScope, CKSyncEnginePendingRecordZoneChange;

@protocol CKSyncEngineDelegate;

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

/// An object that manages the synchronization of local and remote record data.
///
/// Use ``CKSyncEngine`` to handle your app's CloudKit sync operations and benefit from the performance and reliability it provides.
/// To use the class, create an instance early in your app's launch process and specify a database to sync.
/// Thereafter, and depending on good system conditions, the sync engine periodically pushes and pulls database and record zone changes on the app's behalf.
/// To participate in those sync operations and to provide the engine with the changes to send, create an object that conforms to ``CKSyncEngineDelegate-3c38p`` and assign an instance of it to the engine's configuration.
/// You can have multiple instances of ``CKSyncEngine`` in a single process, each targeting a different database. For example, you may have one syncing a person's private database and another syncing their shared database.
///
/// Because periodic sync relies on good system conditions — adequate battery charge, an active network connection, a signed-in iCloud account, and so on — the engine's sync schedule is indeterminate.
/// If you need to sync immediately, like when your app requires it has the most recent changes before continuing, use the ``fetchChangesWithOptions:completionHandler:`` and ``sendChangesWithOptions:completionHandler:`` methods.
///
/// The sync engine uses an opaque type to track its internal state, and it's your responsibility to persist that state to disk and make it available across app launches so the engine can function properly.
/// For more information, see ``CKSyncEngineDelegate/syncEngine:handleEvent:`` and ``CKSyncEngineStateUpdateEvent``.
///
/// ``CKSyncEngine`` requires the CloudKit and Remote notifications entitlements.
/// For more information, see <doc://com.apple.documentation/documentation/xcode/configuring-icloud-services> and <doc://com.apple.documentation/documentation/xcode/configuring-background-execution-modes>.
///
/// - Important: Don't use ``CKSyncEngine`` to sync your app's public database.
///
/// ### Send changes to iCloud
///
/// A sync engine requires you to tell it about any changes to send, which you do by invoking the ``CKSyncEngineState/addPendingDatabaseChanges:`` and ``CKSyncEngineState/addPendingRecordZoneChanges:`` methods on the engine's ``state`` property.
/// If there are no scheduled sync operations when you invoke these methods, the engine automatically schedules one.
/// Database changes don't require any additional input, but the sync engine does expect you to provide the individual record zone changes — in batches — and return them from your delegate's implementation of ``CKSyncEngineDelegate/syncEngine:nextRecordZoneChangeBatchForContext:``.
/// After the engine sends the changes, it notifies your delegate about their success (or failure) by dispatching events of type ``CKSyncEngineSentDatabaseChangesEvent`` and ``CKSyncEngineSentRecordZoneChangesEvent``.
///
/// ### Batches
///
/// The sync engine sends record zone changes to the server in batches, where each batch corresponds to a single network request.
/// After your app registers pending changes through ``CKSyncEngineState/addPendingRecordZoneChanges:``, the engine drives a send operation by repeatedly invoking ``CKSyncEngineDelegate/syncEngine:nextRecordZoneChangeBatchForContext:`` to gather those changes into batches and sending each batch as one request.
/// It keeps asking for batches until your delegate returns `nil` or the operation is cancelled, meaning a single send operation may span many batches.
///
/// Each batch is bounded by the server's per-request limit of 250 records (saves plus deletes combined); a batch that exceeds the limit fails with ``CKError/Code/limitExceeded`` and the sync engine treats it like any other send failure.
/// To stay within the limit automatically, build your batches with ``CKSyncEngineRecordZoneChangeBatch/initWithPendingChanges:recordProvider:``, which walks your pending changes in order and stops once the batch is full.
/// Any changes that don't fit stay in ``CKSyncEngineState/pendingRecordZoneChanges``, so the engine picks them up on the next call.
///
/// After each batch finishes, the engine dispatches a ``CKSyncEngineSentRecordZoneChangesEvent`` (or ``CKSyncEngineSentDatabaseChangesEvent``, for database changes) that describes only the records in that batch, so a single send operation produces one sent-changes event per batch rather than a single event for the whole operation.
///
/// When your delegate builds a batch, include only changes that fall within the scope specified by ``CKSyncEngineSendChangesContext/options`` on the provided context.
/// Returning changes outside that scope causes the send to fail with ``CKError/Code/invalidArguments``.
///
/// ### Fetch changes from iCloud
///
/// By default, a sync engine attempts to discover an existing ``CKDatabaseSubscription`` for the associated database and uses that to receive silent notifications about remote record changes.
/// If the engine doesn't find a subscription, it automatically creates one to use. On receipt of a notification, the engine schedules a sync operation to fetch the related changes.
/// When that operation runs, the engine dispatches an instance of ``CKSyncEngineWillFetchChangesEvent`` to your delegate.
/// As it receives fetched changes, the engine dispatches ``CKSyncEngineFetchedDatabaseChangesEvent`` and ``CKSyncEngineFetchedRecordZoneChangesEvent``, accordingly.
/// After the operation finishes, the sync engine notifies your delegate by dispatching an instance of ``CKSyncEngineDidFetchChangesEvent``.
/// You handle all dispatched events in your delegate's implementation of ``CKSyncEngineDelegate/syncEngine:handleEvent:``.
///
/// ### Sync Scheduling
///
/// #### Automatic sync
///
/// By default, the sync engine automatically schedules sync tasks on your behalf.
/// If the user is signed in, the device has a network connection, and the system is generally in a good state, these scheduled syncs happen relatively quickly.
/// However, if the device has no network, is low on power, or is otherwise under a heavy load, these automatic syncs might be delayed.
/// Similarly, if the user isn't signed in to an account, the sync engine won't perform any sync tasks at all.
///
/// #### Manual sync
///
/// There may be some cases where you want to manually trigger a sync.
/// For example, if you have a pull-to-refresh UI, you can call ``fetchChangesWithOptions:completionHandler:`` to tell the sync engine to fetch immediately.
/// Or, if you have a "backup now" UI, you can call ``sendChangesWithOptions:completionHandler:`` to send to the server immediately.
///
/// ### Error Handling
///
/// There are some transient errors that the sync engine handles automatically behind the scenes.
/// The sync engine retries the operations for these transient errors automatically when it makes sense to do so.
/// Specifically, the sync engine will handle the following errors on your behalf:
///
/// * ``CKError/Code/notAuthenticated``
/// * ``CKError/Code/accountTemporarilyUnavailable``
/// * ``CKError/Code/networkFailure``
/// * ``CKError/Code/networkUnavailable``
/// * ``CKError/Code/requestRateLimited``
/// * ``CKError/Code/serviceUnavailable``
/// * ``CKError/Code/zoneBusy``
///
/// When the sync engine encounters one of these errors, it waits for the system to be in a good state, and tries again.
/// For example, if the server sends back a ``CKError/Code/requestRateLimited`` error, the sync engine respects this throttle and tries again after the error's retry-after time.
///
/// `CKSyncEngine` does _not_ handle errors that require application-specific logic.
/// For example, if you try to save a record and get a ``CKError/Code/serverRecordChanged``, you need to handle that error yourself.
/// There are plenty of errors that the sync engine cannot handle on your behalf, see ``CKError`` for a list of all the possible errors.
///
/// ### Accounts
///
/// `CKSyncEngine` monitors for account status, and it only syncs if there's an account signed in.
/// Because of this, you can initialize your `CKSyncEngine` at any time, regardless of account status.
/// If there is no account, or if the user disabled sync in settings, the sync engine stays dormant in the background.
/// Once an account is available, the sync engine starts syncing automatically.
///
/// The sync engine listens for when the user signs in or out of their account.
/// When it notices an account change, it sends an ``CKSyncEngineAccountChangeEvent`` to your delegate.
/// It's your responsibility to react appropriately to this change and update your local persistence.
///
/// - Tip: A sample code project for ``CKSyncEngine`` is available on GitHub here: [CloudKit Samples: CKSyncEngine](https://github.com/apple/sample-cloudkit-sync-engine).
API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0), watchos(10.0))
NS_REFINED_FOR_SWIFT
CK_SUBCLASSING_RESTRICTED
NS_SWIFT_SENDABLE
@interface CKSyncEngine : NSObject

/// Creates a sync engine with the specified configuration.
///
/// - Parameters:
///   - configuration: The attributes of the new sync engine, such as the associated database and the object to use as the engine's delegate. For more information, see ``CKSyncEngineConfiguration``.
///
/// - Returns: A configured sync engine.
- (instancetype)initWithConfiguration:(CKSyncEngineConfiguration *)configuration NS_SWIFT_NAME(init(_:));

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

/// The associated database.
///
/// Multiple sync engines can run in the same process, each targeting a different database.
/// For example, you may use one sync engine for a person's private database and another for their shared database.
@property (readonly, strong) CKDatabase *database;

/// A collection of state properties used to efficiently manage sync engine operation.
///
/// - SeeAlso: ``CKSyncEngineState``
@property (readonly, strong) CKSyncEngineState *state;

#pragma mark - Fetching and Sending

/// Fetches pending remote changes from the server.
///
/// - Parameters:
///   - completionHandler: The block to execute when the fetch completes.
///
/// If the fetch fails, the completion handler's `error` parameter is an object that describes that failure; otherwise, it's `nil`.
///
/// Use this method to request the sync engine immediately fetches all pending remote changes before your app continues.
/// This isn't necessary in normal use, as the engine automatically syncs your app's records.
/// It is useful, however, in scenarios where you require more control over sync, such as pull-to-refresh or unit tests.
///
/// - Note: The sync engine invokes the completion handler only after your sync delegate finishes processing all related fetch events.
- (void)fetchChangesWithCompletionHandler:(nullable void (NS_SWIFT_SENDABLE ^)(NSError * _Nullable error))completionHandler;

/// Fetches pending remote changes from the server using the specified options.
///
/// - Parameters:
///   - options: The options to use when fetching changes. For more information, see ``CKSyncEngineFetchChangesOptions``.
///   - completionHandler: The block to execute when the fetch completes.
///
/// If the fetch fails, the completion handler's `error` parameter is an object that describes that failure; otherwise, it's `nil`.
///
/// Use this method to request the sync engine immediately fetches all pending remote changes before your app continues.
/// This isn't necessary in normal use, as the engine automatically syncs your app's records.
/// It is useful, however, in scenarios where you require more control over sync, such as pull-to-refresh or unit tests.
///
/// - Note: The sync engine invokes the completion handler only after your sync delegate finishes processing all related fetch events.
- (void)fetchChangesWithOptions:(CKSyncEngineFetchChangesOptions *)options completionHandler:(nullable void (NS_SWIFT_SENDABLE ^)(NSError * _Nullable error))completionHandler NS_SWIFT_ASYNC_NAME(fetchChanges(_:)) NS_SWIFT_NAME(fetchChanges(_:completionHandler:));

/// Sends pending local changes to the server.
///
/// - Parameters:
///   - completionHandler: The block to execute when the send completes.
///
/// If the send fails, the completion handler's `error` parameter is an object that describes that failure; otherwise, it's `nil`.
///
/// Use this method to request the sync engine sends all pending local changes to the server before your app continues.
/// This isn't necessary in normal use, as the engine automatically syncs your app's records.
/// It is useful, however, in scenarios where you require greater control over sync, such as a "Backup now" button or unit tests.
///
/// - Note: The sync engine invokes the completion handler only after your sync delegate finishes processing all related send events.
- (void)sendChangesWithCompletionHandler:(nullable void (NS_SWIFT_SENDABLE ^)(NSError * _Nullable error))completionHandler;

/// Sends pending local changes to the server using the specified options.
///
/// - Parameters:
///   - options: The options to use when sending changes. For more information, see ``CKSyncEngineSendChangesOptions``.
///   - completionHandler: The block to execute when the send completes.
///
/// If the send fails, the completion handler's `error` parameter is an object that describes that failure; otherwise, it's `nil`.
///
/// Use this method to request the sync engine sends all pending local changes to the server before your app continues.
/// This isn't necessary in normal use, as the engine automatically syncs your app's records.
/// It is useful, however, in scenarios where you require greater control over sync, such as a "Backup now" button or unit tests.
///
/// - Note: The sync engine invokes the completion handler only after your sync delegate finishes processing all related send events.
- (void)sendChangesWithOptions:(CKSyncEngineSendChangesOptions *)options completionHandler:(nullable void (NS_SWIFT_SENDABLE ^)(NSError * _Nullable error))completionHandler NS_SWIFT_ASYNC_NAME(sendChanges(_:)) NS_SWIFT_NAME(sendChanges(_:completionHandler:));

/// Cancels any in-progress or pending sync operations.
///
/// The sync engine processes cancellation requests asynchronously, meaning it's possible for in-progress operations to complete even after this method returns.
- (void)cancelOperationsWithCompletionHandler:(nullable void (NS_SWIFT_SENDABLE ^)(void))completionHandler;

@end

#pragma mark - Delegate

/// An interface for providing record data to a sync engine and customizing that engine's behavior.
///
/// - Important: ``CKSyncEngine-4b4w9`` delivers events serially, which means the delegate doesn't receive the next event until it finishes handling the current one.
/// To maintain this ordering, don't call sync engine methods from your delegate that may cause the engine to generate additional events.
/// For example, don't invoke ``CKSyncEngine/fetchChangesWithCompletionHandler:`` or ``CKSyncEngine/sendChangesWithCompletionHandler:`` from within ``syncEngine:handleEvent:``.
API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0), watchos(10.0))
NS_REFINED_FOR_SWIFT
@protocol CKSyncEngineDelegate <NSObject>

/// Tells the delegate to handle the specified sync event.
///
/// - Parameters:
///   - syncEngine: The sync engine that generates the event.
///   - event: Information about the event. An event may occur for a number of reasons, such as when new data is available or when the device's iCloud account changes. For more information, see ``CKSyncEngineEvent``.
///
/// - Important: If `event` is an instance of ``CKSyncEngineStateUpdateEvent``, you must persist the attached state to disk alongside your app data.
/// The sync engine requires you to provide it with the most recent serialized state at initialization, and it's your responsibility to make sure this is available across app launches.
///
/// The sync engine provides events serially; your delegate won't receive the subsequent event until it finishes processing the current one and returns from this method.
- (void)syncEngine:(CKSyncEngine *)syncEngine handleEvent:(CKSyncEngineEvent *)event NS_SWIFT_NAME(syncEngine(_:handleEvent:));

/// Asks the delegate to provide the next set of record changes to send to the server.
///
/// - Parameters:
///   - syncEngine: The sync engine requesting changes.
///   - context: The reason for the sync engine's request, and any additional options that request is using.
///
/// - Returns: If there are pending record changes, a batch of those changes for the sync engine to process; otherwise, `nil` to indicate there are no changes to send.
///
/// In your implementation, ask the sync engine's state for any pending record zone changes and then return a change batch containing an instance of ``CKRecord`` for each record identifier the state provides.
/// For both scheduled and manual send operations, the sync engine calls this method repeatedly until your app has no more changes and returns `nil`.
- (nullable CKSyncEngineRecordZoneChangeBatch *)syncEngine:(CKSyncEngine *)syncEngine nextRecordZoneChangeBatchForContext:(CKSyncEngineSendChangesContext *)context NS_SWIFT_NAME(syncEngine(_:nextRecordZoneChangeBatch:));

@optional

/// Returns a custom set of options for CKSyncEngine to use while fetching changes.
///
/// While `CKSyncEngine` fetches changes from the server, it calls this function to determine priority and other options for fetching changes.
///
/// For example, you can use this to prioritize fetching the object currently showing in the UI.
/// You can also use this to prioritize specific zones during initial sync.
///
/// By default, `CKSyncEngine` uses whatever options are in the context.
/// You can return `context.options` if you don't want to perform any customization.
///
/// This callback is called in between each server request while fetching changes.
/// This allows the fetching mechanism to react dynamically while your app state changes.
///
/// An example implementation might look something like this:
/// ```objc
/// - (CKSyncEngineFetchChangesOptions *)syncEngine:(CKSyncEngine *)syncEngine nextFetchChangesOptionsForContext:(CKSyncEngineFetchChangesContext *)context {
///
///     // Start with the options from the context.
///     CKSyncEngineFetchChangesOptions *options = context.options;
///
///     // By default, the sync engine will automatically fetch changes for all zones.
///     // If you know that you only want to sync a specific set of zones, you can override that here.
///     options.scope = [[CKSyncEngineFetchChangesScope alloc] initWithZoneIDs:@[...]];
///
///     // You can prioritize specific zones to be fetched first by putting them in order.
///     NSMutableArray<CKRecordZoneID *> *prioritizedZoneIDs = [[NSMutableArray alloc] init];
///
///     // If you're showing some data in the UI, you might want to prioritize that zone first.
///     CKRecordZoneID *onScreenZoneID = uiController.currentlyViewedItem.zoneID;
///     if (onScreenZoneID != nil) {
///         [prioritizedZoneIDs addObject:onScreenZoneID];
///     }
///
///     // You could also prioritize special, well-known zones if that makes sense for your app.
///     // For example, if you have a top-level metadata zone that you'd like to sync first, you can prioritize that here.
///     CKRecordZoneID *topLevelZoneID = [[CKRecordZoneID alloc] initWithZoneName:@"MyImportantMetadata"];
///     [prioritizedZoneIDs addObject:topLevelZoneID];
///
///     options.prioritizedZoneIDs = prioritizedZoneIDs;
///     return options;
/// }
/// ```
- (CKSyncEngineFetchChangesOptions *)syncEngine:(CKSyncEngine *)syncEngine nextFetchChangesOptionsForContext:(CKSyncEngineFetchChangesContext *)context NS_SWIFT_NAME(syncEngine(_:fetchChangesOptions:));

@end

#pragma mark - Misc

/// A set of options to use with a fetch operation.
API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0), watchos(10.0))
NS_REFINED_FOR_SWIFT
CK_SUBCLASSING_RESTRICTED
NS_SWIFT_SENDABLE
@interface CKSyncEngineFetchChangesOptions : NSObject <NSCopying>

/// The scope in which to fetch changes from the server.
@property (copy) CKSyncEngineFetchChangesScope *scope;

/// The operation group to use for the underlying CloudKit operations.
///
/// - Tip: Providing a specific operation group helps you to identify and analyze the telemetry of fetch operations in CloudKit Console.
///
/// The default value is `nil`.
@property (strong) CKOperationGroup *operationGroup;

/// A list of zones that are prioritized over others while fetching changes.
///
/// `CKSyncEngine` fetches changes for the zones in this list first.
/// You might use this to prioritize a specific set of zones for initial sync.
/// You could also prioritize the object currently showing in the UI by putting it first in this list.
///
/// Any zones not included in this list are prioritized in a default manner.
/// If a zone in this list has no changes to fetch, then that zone is ignored.
@property (copy) NSArray<CKRecordZoneID *> *prioritizedZoneIDs;

/// Initializes a set of options with the specific scope.
///
/// If you provide a `nil` scope, the default scope is used. The default scope includes everything.
- (instancetype)initWithScope:(nullable CKSyncEngineFetchChangesScope *)scope;

@end

/// A scope in which the sync engine will fetch changes from the server.
API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0), watchos(10.0))
NS_REFINED_FOR_SWIFT
CK_SUBCLASSING_RESTRICTED
NS_SWIFT_SENDABLE
@interface CKSyncEngineFetchChangesScope : NSObject <NSCopying>

/// A specific set of zone IDs to include in the scope.
///
/// For example, if you want to fetch changes for a specific set of zones, you can specify them here.
/// If `nil`, this scope includes all zones except those in `excludedZoneIDs`.
@property (nullable, readonly, copy) NSSet<CKRecordZoneID *> *zoneIDs;

/// A specific set of zone IDs to exclude from this scope.
///
/// If you know that you don't want to fetch changes for a particular set of zones, you can set those zones here.
@property (readonly, copy) NSSet<CKRecordZoneID *> *excludedZoneIDs;

/// Creates a scope that includes only the specified set of zones.
- (instancetype)initWithZoneIDs:(nullable NSSet<CKRecordZoneID *> *)zoneIDs;

/// Creates a scope that includes all zones except the specified excluded zones.
- (instancetype)initWithExcludedZoneIDs:(NSSet<CKRecordZoneID *> *)zoneIDs;

/// Returns true if the specified zone ID is included in this scope.
- (BOOL)containsZoneID:(CKRecordZoneID *)zoneID API_AVAILABLE(macos(14.2), macCatalyst(17.2), ios(17.2), tvos(17.2), watchos(10.2));

@end

/// A set of options to use with a send operation.
API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0), watchos(10.0))
NS_REFINED_FOR_SWIFT
CK_SUBCLASSING_RESTRICTED
NS_SWIFT_SENDABLE
@interface CKSyncEngineSendChangesOptions : NSObject <NSCopying>

/// The scope in which to send changes to the server.
@property (copy) CKSyncEngineSendChangesScope *scope;

/// The operation group to use for the underlying CloudKit operations.
///
/// - Tip: Providing a specific operation group helps you to identify and analyze the telemetry of send operations in CloudKit Console.
///
/// The default value is `nil`.
@property (strong) CKOperationGroup *operationGroup;

/// Initializes a set of options with the specific scope.
///
/// If no scope is provided, the default scope will include everything.
- (instancetype)initWithScope:(nullable CKSyncEngineSendChangesScope *)scope;

@end

/// A scope in which the sync engine will send changes to the server.
API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0), watchos(10.0))
NS_REFINED_FOR_SWIFT
CK_SUBCLASSING_RESTRICTED
NS_SWIFT_SENDABLE
@interface CKSyncEngineSendChangesScope : NSObject <NSCopying>

/// The scope of zone IDs in which to send changes.
///
/// If you only want to send changes for a particular set of zones, you can initialize your scope with those zone IDs.
/// When creating the next batch of changes to send to the server, consult this, and only send changes within these zones.
/// If this and ``recordIDs`` are `nil`, then you should send all changes.
@property (nullable, readonly, copy) NSSet<CKRecordZoneID *> *zoneIDs;

/// A specific set of zone IDs to exclude from this scope.
/// If you know that you don't want to send changes for a particular set of zones, you can set those zones here.
///
/// - Note: a scope with a non-nil ``zoneIDs`` always has an empty `excludedZoneIDs`.
@property (readonly, copy) NSSet<CKRecordZoneID *> *excludedZoneIDs;

/// The scope of record IDs in which to send changes.
///
/// If you only want to send changes for a particular set of records, you can initialize your scope with those records IDs.
/// When creating the next batch of changes to send to the server, consult this property, and only send changes for these record IDs.
/// If this and ``zoneIDs`` are `nil`, then you should send all changes.
@property (nullable, readonly, copy) NSSet<CKRecordID *> *recordIDs;

/// Creates a scope that contains only the given zone IDs.
/// If `zoneIDs` is `nil`, then this scope contains all zones.
- (instancetype)initWithZoneIDs:(nullable NSSet<CKRecordZoneID *> *)zoneIDs;

/// Creates a scope that contains all zones except for the given zone IDs.
- (instancetype)initWithExcludedZoneIDs:(NSSet<CKRecordZoneID *> *)excludedZoneIDs;

/// Creates a scope that includes only the given record IDs.
/// If `recordIDs` is nil, this scope contains all records.
- (instancetype)initWithRecordIDs:(nullable NSSet<CKRecordID *> *)recordIDs;

/// Returns true if this scope includes the given record ID.
- (BOOL)containsRecordID:(CKRecordID *)recordID;

/// Returns true if this scope includes the given pending change.
- (BOOL)containsPendingRecordZoneChange:(CKSyncEnginePendingRecordZoneChange *)pendingRecordZoneChange;

@end

/// Describes the reason for a sync operation.
API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0), watchos(10.0))
NS_REFINED_FOR_SWIFT
typedef NS_ENUM(NSInteger, CKSyncEngineSyncReason) {
    
    /// The sync engine automatically scheduled this sync.
    CKSyncEngineSyncReasonScheduled,
    
    /// A manual sync operation.
    ///
    /// The sync engine uses this reason only when your app invokes the ``CKSyncEngine/fetchChangesWithCompletionHandler:`` and ``CKSyncEngine/sendChangesWithCompletionHandler:`` methods and their variants.
    CKSyncEngineSyncReasonManual,
};

/// The context of an attempt to fetch changes from the server.
///
/// The sync engine might attempt to fetch changes from the server for many reasons.
/// For example, if you call ``CKSyncEngine/fetchChangesWithCompletionHandler:``, it tries to fetch changes immediately.
/// Or if it receives a push notification, it schedules a sync and fetch changes when the scheduler task runs.
API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0), watchos(10.0))
NS_REFINED_FOR_SWIFT
CK_SUBCLASSING_RESTRICTED
NS_SWIFT_SENDABLE
@interface CKSyncEngineFetchChangesContext : NSObject

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

/// The reason why the sync engine is attempting to fetch changes.
@property (readonly, assign) CKSyncEngineSyncReason reason;

/// The options being used for this attempt to fetch changes.
@property (readonly, copy) CKSyncEngineFetchChangesOptions *options;

@end

/// The context of an attempt to send changes to the server.
///
/// A sync engine has two ways to send changes to iCloud — periodically, in cooperation with the system scheduler, and manually, whenever your app invokes the ``CKSyncEngine/sendChangesWithCompletionHandler:`` method.
/// This object provides information about a single attempt to send changes that includes both the reason for the attempt and any additional options in use by the attempt.
API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0), watchos(10.0))
NS_REFINED_FOR_SWIFT
CK_SUBCLASSING_RESTRICTED
NS_SWIFT_SENDABLE
@interface CKSyncEngineSendChangesContext : NSObject

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

/// The reason for the send operation.
@property (readonly, assign) CKSyncEngineSyncReason reason;

/// The additional options for the send operation.
@property (readonly, copy) CKSyncEngineSendChangesOptions *options;

@end

NS_HEADER_AUDIT_END(nullability, sendability)
