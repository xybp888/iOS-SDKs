//
//  CKDatabase.h
//  CloudKit
//
//  Copyright (c) 2014 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

#import <CloudKit/CKSubscription.h>

@class CKDatabaseOperation, CKRecord, CKRecordID, CKRecordZone, CKRecordZoneID, CKQuery;

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

/// Constants that represent the scope of a database.
typedef NS_ENUM(NSInteger, CKDatabaseScope) {
    /// The public database.
    ///
    /// Records in a public database:
    ///
    /// - By default are world readable, owner writable.
    /// - Can be locked down by Roles, a process done in the Developer Portal, a web interface.  Roles are not present in the client API.
    /// - Are visible to the application developer via the Developer Portal.
    /// - Do not contribute to the owner's iCloud account storage quota.
    CKDatabaseScopePublic = 1,

    /// The private database.
    ///
    /// Records in a private database:
    ///
    /// - By default are owner readable and owner writable.
    /// - Are not visible to the application developer via the Developer Portal.
    /// - Are counted towards the owner's iCloud account storage quota.
    CKDatabaseScopePrivate,

    /// The shared database.
    ///
    /// Records in a shared database:
    ///
    /// - Are available to share participants based on the permissions of the enclosing ``CKShare``
    /// - Are not visible to the application developer via the Developer Portal.
    /// - Are counted towards the originating owner's iCloud account storage quota.
    CKDatabaseScopeShared,
} API_AVAILABLE(macos(10.12), ios(10.0), tvos(10.0), watchos(3.0));

/// An object that represents a collection of record zones and subscriptions.
///
/// A database takes requests and operations and applies them to the objects it contains, whether that's record zones, records, or subscriptions. Each of your app's users has access to the three separate databases:
///
/// - A public database that's accessible to all users of your app.
/// - A private database that's accessible only to the user of the current device.
/// - A shared database that's accessible only to the user of the current device, which contains records that other iCloud users share with them.
///
/// The public database is always available, even when the device doesn't have an active iCloud account. In this scenario, your app can fetch specific records and perform searches, but it can't create or modify records. CloudKit requires an iCloud account for writing to the public database so it can identify the authors of any changes. All access to the private and shared databases requires an iCloud account.
///
/// You don't create instances of ``CKDatabase``, nor do you subclass it. Instead, you access the required database using one of your app's containers. For more information, see ``CKContainer``.
///
/// By default, CloudKit executes the methods in this class with a low-priority quality of service (QoS). To use a higher-priority QoS, perform the following:
///
/// 1. Create an instance of ``CKOperation/Configuration`` and set its ``CKOperation/Configuration/qualityOfService`` property to the preferred value.
/// 2. Call the databaseʼs ``configuredWith(configuration:group:body:)-637p1`` method and provide the configuration and a trailing closure.
/// 3. In the closure, use the provided database to execute the relevant methods at the preferred QoS.
///
/// ```swift
/// func fetchRecords(
///     with ids: [CKRecord.ID]
/// ) async throws -> [CKRecord.ID: Result<CKRecord, any Error>] {
///
///     // Get a reference to the user's private database.
///     let database = CKContainer.default().privateCloudDatabase
///
///     // Create a configuration with a higher-priority quality of service.
///     let config = CKOperation.Configuration()
///     config.qualityOfService = .userInitiated
///
///     // Configure the database and execute the fetch.
///     return try await database.configuredWith(configuration: config) { db in
///         try await db.records(for: ids)
///     }
/// }
/// ```
API_AVAILABLE(macos(10.10), ios(8.0), watchos(3.0))
// This class should not be subclassed. If it is, Sendable may no longer apply.
NS_SWIFT_SENDABLE
@interface CKDatabase : NSObject
- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

/// Executes the specified operation in the current database.
///
/// - Parameters:
///   - operation: The operation to execute.
///
/// Configure the operation fully before you call this method. Prior to the operation executing, CloudKit sets its ``CKDatabaseOperation/database`` property to the current database. The operation executes at the priority and quality of service (QoS) that you specify using the <doc://com.apple.documentation/documentation/foundation/operation/queuepriority-swift.property> and <doc://com.apple.documentation/documentation/foundation/operation/qualityofservice> properties.
- (void)addOperation:(CKDatabaseOperation *)operation;

/// The type of database.
///
/// For possible values, see ``CKDatabase/Scope``.
@property (readonly, assign, nonatomic) CKDatabaseScope databaseScope API_AVAILABLE(macos(10.12), ios(10.0), tvos(10.0), watchos(3.0));
@end

/*  Convenience APIs
 *
 *  These calls operate on a single item in the default zone and allow for simple operations.
 *  If you'd like to batch your requests, add dependencies between requests, set priorities, or schedule operations on your own queue, take a look at the corresponding CKOperation.
 *  CloudKit treats this work as having NSQualityOfServiceUserInitiated quality of service.
 */
@interface CKDatabase (ConvenienceMethods)

#pragma mark - Record Convenience Methods

/// Fetches a specific record.
///
/// - Parameters:
///   - recordID: The identifier of the record to fetch.
///   - completionHandler: The closure to execute with the fetch results.
///
/// The completion handler takes the following parameters:
///
/// - The requested record, or `nil` if CloudKit can't provide that record.
/// - An error if a problem occurs, or `nil` if the fetch completes successfully.
///
/// For information on a more convenient way to fetch specific records, see ``CKDatabase/records(for:desiredKeys:)``.
- (void)fetchRecordWithID:(CKRecordID *)recordID completionHandler:(void (NS_SWIFT_SENDABLE ^)(CKRecord * _Nullable record, NSError * _Nullable error))completionHandler NS_REFINED_FOR_SWIFT_ASYNC(2);

/// Saves a specific record.
///
/// - Parameters:
///   - record: The record to save.
///   - completionHandler: The closure to execute after CloudKit saves the record.
///
/// The completion handler takes the following parameters:
///
/// - The saved record (as it appears on the server), or `nil` if there's an error.
/// - An error if a problem occurs, or `nil` if CloudKit successfully saves the record.
///
/// The save succeeds only when the specified record is new, or is a more recent version than the one on the server.
///
/// For information on a more convenient way to save records, see ``CKDatabase/modifyRecords(saving:deleting:savePolicy:atomically:)``.
- (void)saveRecord:(CKRecord *)record completionHandler:(void (NS_SWIFT_SENDABLE ^)(CKRecord * _Nullable record, NSError * _Nullable error))completionHandler NS_REFINED_FOR_SWIFT_ASYNC(2);

/// Deletes a specific record.
///
/// - Parameters:
///   - recordID: The identifier of the record to delete.
///   - completionHandler: The closure to execute after CloudKit deletes the record.
///
/// The completion handler takes the following parameters:
///
/// - The identifier of the deleted record, or `nil` if there's an error.
/// - An error if a problem occurs, or `nil` if CloudKit successfully deletes the record.
///
/// Deleting a record may cause additional deletions if other records in the database reference the deleted record. CloudKit doesn't provide the identifiers of any additional records it deletes.
///
/// For information on a more convenient way to delete records, see ``CKDatabase/modifyRecords(saving:deleting:savePolicy:atomically:)``.
- (void)deleteRecordWithID:(CKRecordID *)recordID completionHandler:(void (NS_SWIFT_SENDABLE ^)(CKRecordID * _Nullable recordID, NSError * _Nullable error))completionHandler NS_REFINED_FOR_SWIFT_ASYNC(2);

#pragma mark - Query Convenience Method

/// Searches for records matching a predicate in the specified record zone.
///
/// - Parameters:
///   - query: The query that contains the search parameters. For more information, see ``CKQuery``.
///   - zoneID: The identifier of the record zone to search. If you're searching a shared database, provide a record zone identifier; otherwise, you can specify `nil` to search all record zones in the database.
///   - completionHandler: The closure to execute with the search results.
///
/// The completion handler takes the following parameters:
/// 
/// - The records that match the specified query, or `nil` if there's an error.
/// - An error if a problem occurs, or `nil` if CloudKit completes the search successfully.
///
/// For information on a more convenient way to search a database, see ``CKDatabase/records(matching:inZoneWith:desiredKeys:resultsLimit:)``.
- (void)performQuery:(CKQuery *)query inZoneWithID:(nullable CKRecordZoneID *)zoneID completionHandler:(void (NS_SWIFT_SENDABLE ^)(NSArray<CKRecord *> * _Nullable results, NSError * _Nullable error))completionHandler
CK_SWIFT_DEPRECATED("renamed to fetch(withQuery:inZoneWith:desiredKeys:resultsLimit:completionHandler:)", macos(10.10, 12.0), ios(8.0, 15.0), tvos(9.0, 15.0), watchos(3.0, 8.0)) NS_REFINED_FOR_SWIFT_ASYNC(3);

#pragma mark - Record Zone Convenience Methods

/// Fetches all record zones from the current database.
///
/// - Parameters:
///   - completionHandler: The closure to execute with the fetch results.
///
/// The completion handler takes the following parameters:
///
/// - An array of fetched record zones, or `nil` if there's an error. When present, the array contains at least one record zone, the default zone.
/// - An error if a problem occurs, or `nil` if CloudKit successfully fetches all record zones.
- (void)fetchAllRecordZonesWithCompletionHandler:(void (NS_SWIFT_SENDABLE ^)(NSArray<CKRecordZone *> * _Nullable zones, NSError * _Nullable error))completionHandler NS_REFINED_FOR_SWIFT_ASYNC(1);

/// Fetches a specific record zone.
///
/// - Parameters:
///   - zoneID: The identifier of the record zone to fetch.
///   - completionHandler: The closure to execute with the fetch results.
///
/// The completion handler takes the following parameters:
///
/// - The fetched record zone, or `nil` if there's an error.
/// - An error if a problem occurs, or `nil` if CloudKit successfully fetches the specified record zone.
///
/// For information on a more convenient way to fetch specific record zones, see ``CKDatabase/recordZones(for:)`` in Swift or ``CKFetchRecordZonesOperation`` in Objective-C.
- (void)fetchRecordZoneWithID:(CKRecordZoneID *)zoneID completionHandler:(void (NS_SWIFT_SENDABLE ^)(CKRecordZone * _Nullable zone, NSError * _Nullable error))completionHandler NS_REFINED_FOR_SWIFT_ASYNC(2);

/// Saves a specific record zone.
///
/// - Parameters:
///   - zone: The record zone to save.
///   - completionHandler: The closure to execute after CloudKit saves the record.
///
/// The completion handler takes the following parameters:
///
/// - The saved record zone (as it appears on the server), or `nil` if there's an error.
/// - An error if a problem occurs, or `nil` if CloudKit successfully saves the record zone.
///
/// For information on a more convenient way to save record zones, see ``CKDatabase/modifyRecordZones(saving:deleting:)``.
- (void)saveRecordZone:(CKRecordZone *)zone completionHandler:(void (NS_SWIFT_SENDABLE ^)(CKRecordZone * _Nullable zone, NSError * _Nullable error))completionHandler NS_REFINED_FOR_SWIFT_ASYNC(2);

/// Deletes a specific record zone.
///
/// - Parameters:
///   - zoneID: The identifier of the record zone to delete.
///   - completionHandler: The closure to execute after CloudKit deletes the record zone.
///
/// - Warning: Deleting a record zone is a permanent action that deletes every record in that zone. You can't restore a deleted record zone.
///
/// The completion handler takes the following parameters:
///
/// - The identifier of the deleted record zone, or `nil` if there's an error.
/// - An error if a problem occurs, or `nil` if CloudKit successfully deletes the record zone.
///
/// For information on a more convenient way to delete record zones, see ``CKDatabase/modifyRecordZones(saving:deleting:)``.
- (void)deleteRecordZoneWithID:(CKRecordZoneID *)zoneID completionHandler:(void (NS_SWIFT_SENDABLE ^)(CKRecordZoneID * _Nullable zoneID, NSError * _Nullable error))completionHandler NS_REFINED_FOR_SWIFT_ASYNC(2);

#pragma mark - Subscription Convenience Methods

/// Fetches a specific subscription and delivers it to a completion handler.
///
/// - Parameters:
///   - subscriptionID: The identifier of the subscription to fetch.
///   - completionHandler: The block to execute with the fetch results.
///
/// The completion handler takes the following parameters:
///
///   - term `subscription`: The requested subscription, or `nil` if CloudKit can't provide that subscription.
///   - term `error`: An error if a problem occurs, or `nil` if the fetch completes successfully.
///
/// For information on a more configurable way to fetch specific subscriptions, see ``CKFetchSubscriptionsOperation``.
- (void)fetchSubscriptionWithID:(CKSubscriptionID)subscriptionID completionHandler:(void (NS_SWIFT_SENDABLE ^)(CKSubscription * _Nullable subscription, NSError * _Nullable error))completionHandler API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(6.0)) NS_REFINED_FOR_SWIFT_ASYNC(2);

/// Fetches all subscriptions from the current database.
///
/// - Parameters:
///   - completionHandler: The closure to execute with the fetch results.
///
/// The completion handler takes the following parameters:
///
/// - The database's subscriptions, or `nil` if CloudKit can't provide the subscriptions.
/// - An error if a problem occurs, or `nil` if the fetch completes successfully.
///
/// For information on a more configurable way to fetch all subscriptions from a specific database, see ``CKFetchSubscriptionsOperation/fetchAllSubscriptionsOperation()``.
- (void)fetchAllSubscriptionsWithCompletionHandler:(void (NS_SWIFT_SENDABLE ^)(NSArray<CKSubscription *> * _Nullable subscriptions, NSError * _Nullable error))completionHandler API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(6.0)) NS_REFINED_FOR_SWIFT_ASYNC(1);

/// Saves a specific subscription.
///
/// - Parameters:
///   - subscription: The subscription to save.
///   - completionHandler: The closure to execute after CloudKit saves the subscription.
///
/// The completion handler takes the following parameters:
///
/// - The saved subscription (as it appears on the server), or `nil` if there's an error.
/// - An error if a problem occurs, or `nil` if CloudKit successfully saves the subscription.
///
/// For information on a more convenient way to save subscriptions, see ``CKDatabase/modifySubscriptions(saving:deleting:)``.
- (void)saveSubscription:(CKSubscription *)subscription completionHandler:(void (NS_SWIFT_SENDABLE ^)(CKSubscription * _Nullable subscription, NSError * _Nullable error))completionHandler API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(6.0)) NS_REFINED_FOR_SWIFT_ASYNC(2);

/// Deletes a specific subscription and delivers the deleted subscription's identifier to a completion handler.
///
/// - Parameters:
///   - subscriptionID: The identifier of the subscription to delete.
///   - completionHandler: The block to execute after CloudKit deletes the subscription.
///
/// The completion handler takes the following parameters:
///
///   - term `subscriptionID`: The identifier of the deleted subscription, or `nil` if there's an error.
///   - term `error`: An error if a problem occurs, or `nil` if CloudKit successfully deletes the subscription.
///
/// For information on a more configurable way to delete subscriptions, see ``CKModifySubscriptionsOperation``.
- (void)deleteSubscriptionWithID:(CKSubscriptionID)subscriptionID completionHandler:(void (NS_SWIFT_SENDABLE ^)(CKSubscriptionID _Nullable subscriptionID, NSError * _Nullable error))completionHandler API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(6.0)) NS_REFINED_FOR_SWIFT_ASYNC(2);

@end

NS_HEADER_AUDIT_END(nullability, sendability)
