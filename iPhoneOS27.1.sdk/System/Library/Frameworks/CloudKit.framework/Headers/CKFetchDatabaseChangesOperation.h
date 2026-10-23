//
//  CKFetchDatabaseChangesOperation.h
//  CloudKit
//
//  Copyright © 2016 Apple Inc. All rights reserved.
//

#import <CloudKit/CKDatabaseOperation.h>

@class CKRecordZoneID, CKServerChangeToken;

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

/// An operation that fetches database changes.
///
/// Use this operation to fetch all record zone changes in a database. This includes new record zones, changed zones — including deleted or purged zones — and zones that contain record changes. When you create the operation, you provide a server change token, which is an opaque token that represents a specific point in the database's history. CloudKit returns only the changes that occur after that point. For your app's first fetch, or to refetch every change in the database's history, use `nil` instead.
///
/// - Note: Only private and shared databases support this operation. If you attempt to execute this operation in the public database, CloudKit returns an error.
///
/// The operation yields new change tokens during its execution, and issues a final change token when it completes without error. The change tokens conform to <doc://com.apple.documentation/documentation/foundation/nssecurecoding> and are safe to cache on-disk. This operation's tokens aren't compatible with ``CKFetchRecordZoneChangesOperation`` so you should segregate them in your cache. Don't infer any behavior or order from the tokens' contents.
///
/// When your app launches for the first time, use this operation to fetch all the database's changes. Cache the results on-device and use ``CKDatabaseSubscription`` to subscribe to future changes. Fetch those changes on receipt of the push notifications the subscription generates. It's not necessary to perform a fetch each time your app launches, or to schedule fetches at regular intervals.
///
/// The operation calls ``recordZoneWithIDChangedBlock`` for each zone that contains record changes. It also calls it for new and modified record zones. Store the IDs that CloudKit provides to this callback. Use those IDs with ``CKFetchRecordZoneChangesOperation`` to fetch the corresponding changes. There are similar callbacks for deleted and purged record zones.
///
/// To run the operation, add it to the corresponding database's operation queue. The operation executes its callbacks on a private serial queue.
///
/// The following example shows how to create the operation, configure its callbacks, and execute it. For brevity, it omits the delete, and purge callbacks.
///
/// ```swift
/// // Create a fetch operation using the server change
/// // token from the previous fetch.
/// CKFetchDatabaseChangesOperation *operation =
///     [[CKFetchDatabaseChangesOperation alloc]
///      initWithPreviousServerChangeToken:token];
///
/// // Collect the IDs of the modified record zones.
/// operation.recordZoneWithIDChangedBlock = ^(CKRecordZoneID *recordZoneID) {
///     [recordZoneIDs addObject:recordZoneID];
/// };
///
/// // Process any change tokens that CloudKit provides
/// // as the operation runs.
/// operation.changeTokenUpdatedBlock = ^(CKServerChangeToken *newToken) {
///     tokenHandler(newToken);
/// };
///
/// // Store the final change token and pass the IDs of the
/// // modified record zones for further processing.
/// operation.fetchDatabaseChangesCompletionBlock =
///     ^(CKServerChangeToken *newToken, BOOL more, NSError *error) {
///     if (error) {
///         // Handle the error.
///     } else {
///         tokenHandler(newToken);
///         recordZonesHandler(recordZoneIDs);
///     }
/// };
///
/// // Set an appropriate QoS and add the operation to the shared
/// // database's operation queue to execute it.
/// operation.qualityOfService = NSQualityOfServiceUtility;
/// [CKContainer.defaultContainer.sharedCloudDatabase addOperation:operation];
/// ```
API_AVAILABLE(macos(10.12), ios(10.0), tvos(10.0), watchos(3.0))
@interface CKFetchDatabaseChangesOperation : CKDatabaseOperation

/// Creates an empty fetch database changes operation.
- (instancetype)init NS_DESIGNATED_INITIALIZER;

/// Creates an operation for fetching database changes.
///
/// - Parameters:
///   - previousServerChangeToken: The change token that CloudKit uses to determine which database changes to return.
///
/// After creating the operation, assign a handler to the ``CKFetchDatabaseChangesOperation/fetchDatabaseChangesCompletionBlock`` property so that you can process the operation's results.
///
/// If this is your first fetch, or if you want to refetch all zones, pass `nil` for the change token. If you provide a change token from a previous ``CKFetchDatabaseChangesOperation``, CloudKit returns only the zones with changes since that token. The per-database ``CKServerChangeToken`` isn't the same as the per-record zone ``CKServerChangeToken`` from ``CKFetchRecordZoneChangesOperation``.
- (instancetype)initWithPreviousServerChangeToken:(nullable CKServerChangeToken *)previousServerChangeToken;

/// The server change token.
///
/// Assign the token you receive from the ``CKFetchDatabaseChangesOperation/fetchDatabaseChangesCompletionBlock`` to this property. Doing so yields only the changes that occur after your most recent fetch operation. If you specify `nil` for this parameter, the operation fetches all changes.
@property (nullable, copy, nonatomic) CKServerChangeToken *previousServerChangeToken;

/// The maximum number of results that the operation fetches.
///
/// Use this property to limit the number of changes this operation returns. When the operation reaches the limit, it updates the change token and returns it to indicate that more results are available.
@property (assign, nonatomic) NSUInteger resultsLimit;

/// A Boolean value that indicates whether to send repeated requests to the server.
///
/// If <doc://com.apple.documentation/documentation/swift/true>, the operation sends repeat requests to the server until it fetches all changes. CloudKit executes the handler you set on the ``CKFetchDatabaseChangesOperation/changeTokenUpdatedBlock`` property with a change token after each request.
///
/// The default value is <doc://com.apple.documentation/documentation/swift/true>.
@property (assign, nonatomic) BOOL fetchAllChanges;

/// The closure to execute with a single record zone change.
///
/// The closure returns no value and takes the following parameter:
///
///   - term `zoneID`: The ID of the  record zone that contains changes.
@property (nullable, copy, nonatomic) void (^recordZoneWithIDChangedBlock)(CKRecordZoneID *zoneID);

/// The closure to execute when a record zone no longer exists.
///
/// The closure returns no value and takes the following parameter:
///
///   - term `zoneID`: The deleted record zone's ID.
@property (nullable, copy, nonatomic) void (^recordZoneWithIDWasDeletedBlock)(CKRecordZoneID *zoneID);

/// The closure to execute when CloudKit purges a record zone.
///
/// The closure returns no value and takes the following parameter:
///
///   - term `zoneID`: The purged record zone's ID.
@property (nullable, copy, nonatomic) void (^recordZoneWithIDWasPurgedBlock)(CKRecordZoneID *zoneID) API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0), watchos(4.0));

/// The closure to execute when a user-invoked account reset deletes a record zone.
///
/// The closure returns no value and takes a single parameter: the deleted record zone's ID.
///
/// The operation executes this closure, instead of ``CKFetchDatabaseChangesOperation/recordZoneWithIDWasDeletedBlock``, after a user action causes CloudKit to delete the record zone. Reupload any locally cached data to iCloud to minimize data loss.
@property (nullable, copy, nonatomic) void (^recordZoneWithIDWasDeletedDueToUserEncryptedDataResetBlock)(CKRecordZoneID *zoneID) API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0), watchos(8.0));

/// The closure to execute when the change token updates.
///
/// The closure executes periodically, and provides a new change token so that you don't need to refetch previously fetched record zone changes in a subsequent operation.
@property (nullable, copy, nonatomic) void (^changeTokenUpdatedBlock)(CKServerChangeToken * serverChangeToken);

/// The closure to execute when the operation finishes.
///
/// The closure returns no value and takes the following parameters:
///
/// - The change token to store and use in subsequent instances of ``CKFetchDatabaseChangesOperation``.
/// - A Boolean value that indicates whether this is the final database change. If ``CKFetchDatabaseChangesOperation/fetchAllChanges`` is <doc://com.apple.documentation/documentation/swift/false>, it's the app's responsibility to create additional instances of ``CKFetchDatabaseChangesOperation`` to fetch further changes.
/// - An error object that contains information about a problem, or `nil` if CloudKit successfully retrieves the database changes.
///
/// - Note: The change token and error parameters are mutually exclusive — that is, the closure provides one of them but not both.
///
/// Your app is responsible for saving the change token at the end of the operation and providing it to future uses of ``CKFetchDatabaseChangesOperation``. If the server returns a ``CKError/Code/changeTokenExpired`` error, the ``CKFetchDatabaseChangesOperation/previousServerChangeToken`` value is stale and your app needs to clear its local cache and refetch the database changes, starting with a `nil` change token.
@property (nullable, copy, nonatomic) void (^fetchDatabaseChangesCompletionBlock)(CKServerChangeToken * _Nullable serverChangeToken, BOOL moreComing, NSError * _Nullable operationError)
CK_SWIFT_DEPRECATED("Use fetchDatabaseChangesResultBlock instead", macos(10.12, 12.0), ios(10.0, 15.0), tvos(10.0, 15.0), watchos(3.0, 8.0));

@end

NS_HEADER_AUDIT_END(nullability, sendability)
