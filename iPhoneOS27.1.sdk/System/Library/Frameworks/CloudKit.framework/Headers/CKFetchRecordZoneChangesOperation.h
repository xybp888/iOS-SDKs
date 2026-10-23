//
//  CKFetchRecordZoneChangesOperation.h
//  CloudKit
//
//  Copyright (c) 2016 Apple Inc. All rights reserved.
//

#import <CloudKit/CKDatabaseOperation.h>

#import <CloudKit/CKRecord.h>
#import <CloudKit/CKServerChangeToken.h>

@class CKFetchRecordZoneChangesConfiguration, CKFetchRecordZoneChangesOptions;

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

/// An operation that fetches record zone changes.
///
/// Use this operation to fetch record changes in one or more record zones, such as those that occur during record creation, modification, and deletion. You provide a configuration object for each record zone to query for changes. The configuration contains a server change token, which is an opaque pointer to a specific change in the zone's history. CloudKit returns only the changes that occur after that point. For the first time you fetch a record zone's changes, or to refetch all changes in a zone's history, use `nil` instead.
///
/// - Note: Only private and shared databases support this operation. If you attempt to execute this operation in the public database, CloudKit returns an error.
///
/// CloudKit processes the record zones in succession, and returns the changes for each zone in batches. Each batch yields a new change token. If all batches return without error, the operation issues a final change token for that zone. The change tokens conform to <doc://com.apple.documentation/documentation/foundation/nssecurecoding> and are safe to cache on-disk. This operation's tokens aren't compatible with ``CKFetchDatabaseChangesOperation`` so you should segregate them in your app's cache. Don't infer behavior or order from the tokens' contents.
///
/// If you create record zones in the private database, fetch all changes the first time the app launches. Cache the results on-device and use ``CKRecordZoneSubscription`` to subscribe to future changes. Fetch those changes on receipt of the push notifications the subscription generates. If you use the shared database, subscribe to changes with ``CKDatabaseSubscription`` instead. When a user participates in sharing, CloudKit adds and removes record zones. This means you don't know in advance which zones exist in the shared database. Use ``CKFetchDatabaseChangesOperation`` to fetch shared record zones on receipt of the subscription's push notifications. Then fetch the changes in those zones using this operation. Regardless of which database you use, it's not necessary to perform fetches each time your app launches, or to schedule fetches at regular intervals.
///
/// To run the operation, add it to the corresponding database's operation queue. The operation executes its callbacks on a private serial queue.
///
/// The following example demonstrates how to create the operation, configure its callbacks, and execute it. For brevity, it omits the delete and operation completion callbacks.
///
/// ```swift
/// // Create a dictionary that maps a record zone ID to its
/// // corresponding zone configuration. The configuration
/// // contains the server change token from the most recent
/// // fetch of that record zone.
/// NSMutableDictionary *configurations = [NSMutableDictionary new];
/// for (CKRecordZoneID *recordZoneID in recordZoneIDs) {
///     CKFetchRecordZoneChangesConfiguration *config =
///         [CKFetchRecordZoneChangesConfiguration new];
///     config.previousServerChangeToken = [tokenCache objectForKey:recordZoneID];
///     [configurations setObject:config forKey:recordZoneID];
/// }
///
/// // Create a fetch operation with an array of record zone IDs
/// // and the zone configuration mapping dictionary.
/// CKFetchRecordZoneChangesOperation *operation =
///     [[CKFetchRecordZoneChangesOperation alloc]
///      initWithRecordZoneIDs:recordZoneIDs
///      configurationsByRecordZoneID:configurations];
///
/// // Process each changed record as CloudKit returns it.
/// operation.recordChangedBlock = ^(CKRecord *record) {
///     recordHandler(record);
/// };
///
/// // Cache the change tokens that CloudKit provides as
/// // the operation runs.
/// operation.recordZoneChangeTokensUpdatedBlock = ^(CKRecordZoneID *recordZoneID,
///                                                  CKServerChangeToken *token,
///                                                  NSData *data) {
///     [tokenCache setObject:token forKey:recordZoneID];
/// };
///
/// // If the fetch for the current record zone completes
/// // successfully, cache the final change token.
/// operation.recordZoneFetchCompletionBlock = ^(CKRecordZoneID *recordZoneID,
///                                              CKServerChangeToken *token,
///                                              NSData *data, BOOL more,
///                                              NSError *error) {
///     if (error) {
///         // Handle the error.
///     } else {
///         [tokenCache setObject:token forKey:recordZoneID];
///     }
/// };
///
/// // Set an appropriate QoS and add the operation to the shared
/// // database's operation queue to execute it.
/// operation.qualityOfService = NSQualityOfServiceUtility;
/// [CKContainer.defaultContainer.sharedCloudDatabase addOperation:operation];
/// ```
API_AVAILABLE(macos(10.12), ios(10.0), tvos(10.0), watchos(3.0))
@interface CKFetchRecordZoneChangesOperation : CKDatabaseOperation

/// Creates an empty fetch record zone changes operation.
- (instancetype)init NS_DESIGNATED_INITIALIZER;

/// Creates an operation for fetching record zone changes.
///
/// - Parameters:
///   - recordZoneIDs: The IDs of the record zones that you want to query for changes. You can specify `nil` for this parameter.
///   - configurationsByRecordZoneID: A dictionary that maps record zone IDs to their corresponding configurations. You can specify `nil` for this parameter.
///
/// CloudKit configures the operation for retrieving all of the record zones that you specify. If you want to reduce the amount of data that CloudKit returns, provide zone configurations for each record zone.
- (instancetype)initWithRecordZoneIDs:(NSArray<CKRecordZoneID *> *)recordZoneIDs configurationsByRecordZoneID:(nullable NSDictionary<CKRecordZoneID *, CKFetchRecordZoneChangesConfiguration *> *)configurationsByRecordZoneID API_AVAILABLE(macos(10.14), ios(12.0), tvos(12.0), watchos(5.0));

/// The IDs of the record zones that contain the records to fetch.
///
/// Typically, you set the value of this property when you create the operation. If you intend to change the record zone IDs, update the value before you execute the operation or submit it to a queue.
@property (nullable, copy, nonatomic) NSArray<CKRecordZoneID *> *recordZoneIDs;

/// A dictionary of configurations for fetching change operations by zone identifier.
@property (nullable, copy, nonatomic) NSDictionary<CKRecordZoneID *, CKFetchRecordZoneChangesConfiguration *> *configurationsByRecordZoneID API_AVAILABLE(macos(10.14), ios(12.0), tvos(12.0), watchos(5.0));

/// A Boolean value that indicates whether to send repeated requests to the server.
///
/// If <doc://com.apple.documentation/documentation/swift/true>, the operation sends repeat requests to the server until it fetches all changes. CloudKit executes the handler you set on the ``CKFetchRecordZoneChangesOperation/recordZoneFetchResultBlock`` property with a change token after each request.
///
/// The default value is <doc://com.apple.documentation/documentation/swift/true>.
@property (assign, nonatomic) BOOL fetchAllChanges;

/// The closure to execute with the contents of a changed record.
///
/// The closure returns no value and takes the following parameter:
///
/// - The changed record. If you specify a value for the ``CKFetchRecordZoneChangesConfiguration/desiredKeys`` property, the record contains only the corresponding fields.
///
/// The operation executes this closure once for each record in the record zone with changes since the previous fetch request. Each time the closure executes, it executes serially with respect to the other closures of the operation. If there aren't any record changes, this closure doesn't execute.
///
/// Set this property before you execute the operation or submit it to a queue.
@property (nullable, copy, nonatomic) void (^recordChangedBlock)(CKRecord *record) API_DEPRECATED("Use recordWasChangedBlock instead, which surfaces per-record errors", macos(10.12, 12.0), ios(10.0, 15.0), tvos(10.0, 15.0), watchos(3.0, 8.0));

/// The closure to execute with the results of retrieving a record change.
///
/// The closure returns no value and takes the following parameters:
///
/// - The ID of the changed record to retrieve.
/// - The changed record, or `nil` if CloudKit can't retrieve the record.
///   If you specify a value for the ``CKFetchRecordZoneChangesConfiguration/desiredKeys`` property, the record contains only the corresponding fields.
/// - An error that contains information about a problem, or `nil` if CloudKit retrieves the record successfully.
///
/// The operation executes this closure once for each record in the record zone with changes since the previous fetch request. Each time the closure executes, it executes serially with respect to the other closures of the operation. If there aren't any record changes, this closure doesn't execute.
///
/// Set this property before you execute the operation or submit it to a queue.
@property (nullable, copy, nonatomic) void (^recordWasChangedBlock)(CKRecordID *recordID, CKRecord * _Nullable record, NSError * _Nullable error) API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0), watchos(8.0)) NS_REFINED_FOR_SWIFT;

/// The block to execute when a record no longer exists.
///
/// The block returns no value and takes the following parameters:
///
///   - term `recordID`: The deleted record's ID.
///   - term `recordType`: The deleted record's type.
///
/// The operation executes this block once for each record the server deletes after the previous change token. Each time the block executes, it executes serially with respect to the other blocks of the operation. If there aren't any record deletions, this block doesn't execute.
///
///  Set this property before you execute the operation or submit it to a queue.
@property (nullable, copy, nonatomic) void (^recordWithIDWasDeletedBlock)(CKRecordID *recordID, CKRecordType recordType);

/// The closure to execute when the change token updates.
///
/// The closure returns no value and takes the following parameters:
///
/// - The record zone's ID.
/// - The new change token from the server. You can store this token locally and use it during subsequent fetch operations to limit the results to records that change after this operation executes.
/// - The most recent client change token from the device. If the change token isn't the most recent change token you provided, the server might not have received the associated changes.
///
/// The operation executes this closure once for each retrieved change token. Each time the closure executes, it executes serially with respect to the other blocks of the operation.
///
/// Set this property before you execute the operation or submit it to a queue.
@property (nullable, copy, nonatomic) void (^recordZoneChangeTokensUpdatedBlock)(CKRecordZoneID *recordZoneID, CKServerChangeToken * _Nullable serverChangeToken, NSData * _Nullable clientChangeTokenData);

/// The closure to execute when a record zone's fetch finishes.
///
/// The closure returns no value and takes the following parameters:
///
/// - The record zone's ID.
/// - The change token to store and use in subsequent instances of ``CKFetchRecordZoneChangesOperation``.
/// - The more recent client change token from the device. If the change token isn't the more recent change token you provided, the server might not have received the associated changes.
/// - A Boolean that indicates whether this is the final record zone change. If ``CKFetchRecordZoneChangesOperation/fetchAllChanges`` is <doc://com.apple.documentation/documentation/swift/false>, it's the app's responsibility to create additional instances of ``CKFetchRecordZoneChangesOperation`` to fetch further changes.
/// - An error object that contains information about a problem, or `nil` if the operation successfully retrieves the results.
///
/// The app is responsible for saving the change token at the end of the operation and providing it to future uses of ``CKFetchRecordZoneChangesOperation``. Each time the closure executes, it executes serially with respect to the other closures of the operation.
///
/// Set this property before you execute the operation or submit it to a queue.
@property (nullable, copy, nonatomic) void (^recordZoneFetchCompletionBlock)(CKRecordZoneID *recordZoneID, CKServerChangeToken * _Nullable serverChangeToken, NSData * _Nullable clientChangeTokenData, BOOL moreComing, NSError * _Nullable recordZoneError) CK_SWIFT_DEPRECATED("Use recordZoneFetchResultBlock instead", macos(10.12, 12.0), ios(10.0, 15.0), tvos(10.0, 15.0), watchos(3.0, 8.0));

/// The closure to execute when the operation finishes.
///
/// The closure has no return value and takes the following parameter:
///
/// - An error object that contains information about a problem, or `nil` if CloudKit successfully retrieves the record zone changes.
///
/// This closure executes only once, and represents your final opportunity to process the results. The closure executes serially with respect to the other closures of the operation.
/// 
/// Set this property before you execute the operation or submit it to a queue.
@property (nullable, copy, nonatomic) void (^fetchRecordZoneChangesCompletionBlock)(NSError * _Nullable operationError) CK_SWIFT_DEPRECATED("Use fetchRecordZoneChangesResultBlock instead", macos(10.12, 12.0), ios(10.0, 15.0), tvos(10.0, 15.0), watchos(3.0, 8.0));

@end

@interface CKFetchRecordZoneChangesOperation(Deprecated)

/// Creates an operation for fetching record zone changes.
///
/// @DeprecationSummary {
///     Use ``CKFetchRecordZoneChangesOperation/init(recordZoneIDs:configurationsByRecordZoneID:)`` instead.
/// }
/// 
/// - Parameters:
///   - recordZoneIDs: The IDs of the record zones that you want to query for changes.
///   - optionsByRecordZoneID: A dictionary that maps record zone IDs to their corresponding options. You can specify `nil` for this parameter.
///
/// CloudKit configures the operation for retrieving all of the record zones that you specify. If you want to reduce the amount of data that CloudKit returns, provide zone options for each record zone.
- (instancetype)initWithRecordZoneIDs:(NSArray<CKRecordZoneID *> *)recordZoneIDs optionsByRecordZoneID:(nullable NSDictionary<CKRecordZoneID *, CKFetchRecordZoneChangesOptions *> *)optionsByRecordZoneID
API_DEPRECATED_WITH_REPLACEMENT("initWithRecordZoneIDs:configurationsByRecordZoneID:", macos(10.12, 10.14), ios(10.0, 12.0), tvos(10.0, 12.0), watchos(3.0, 5.0));

/// Configuration options for each record zone that the operation retrieves.
///
/// @DeprecationSummary {
///     Use ``CKFetchRecordZoneChangesOperation/configurationsByRecordZoneID`` instead.
/// }
/// 
/// You can associate each record zone ID with options that define what CloudKit fetches for that record zone.  See ``CKFetchRecordZoneChangesOperation/ZoneOptions`` for more information.
@property (nullable, copy, nonatomic) NSDictionary<CKRecordZoneID *, CKFetchRecordZoneChangesOptions *> *optionsByRecordZoneID
API_DEPRECATED_WITH_REPLACEMENT("configurationsByRecordZoneID", macos(10.12, 10.14), ios(10.0, 12.0), tvos(10.0, 12.0), watchos(3.0, 5.0));
@end


/// A configuration object that describes the information to fetch from a record zone.
API_AVAILABLE(macos(10.14), ios(12.0), tvos(12.0), watchos(5.0))
CK_SUBCLASSING_DEPRECATED // should not be subclassed, or Sendable may no longer apply
// NS_SWIFT_SENDABLE on macos(13.3), macCatalyst(16.4), ios(16.4), tvos(16.4), watchos(9.4)
@interface CKFetchRecordZoneChangesConfiguration : NSObject <NSSecureCoding, NSCopying>

/// The token that identifies the starting point for retrieving changes.
///
/// Each fetch request returns a unique token in addition to any changes. CloudKit passes the token to your ``CKFetchRecordZoneChangesOperation/recordZoneFetchResultBlock`` handler. During a subsequent fetch request, providing the previous token causes the server to return only the changes since the previous fetch request. Tokens are opaque values that you can write to disk safely and reuse later.
@property (nullable, copy) CKServerChangeToken *previousServerChangeToken;

/// The maximum number of records to fetch from the record zone.
///
/// Use this property to limit the number of results in situations where you expect a large number of records. The default value is 0, which causes the server to return an appropriate number of records using dynamic conditions.
///
/// When the number of records that CloudKit returns exceeds this limit, the operation sets the `moreComing` property to <doc://com.apple.documentation/documentation/swift/true> when executing the ``CKFetchRecordZoneChangesOperation/recordZoneFetchResultBlock`` handler.
@property (assign) NSUInteger resultsLimit;

/// The fields to fetch for the requested records.
///
/// Use this property to limit the amount of data that CloudKit retrieves for each record during the fetch operation. This property contains an array of strings, each of which is the name of a field from the target records. When you retrieve a record, CloudKit only includes fields with names that match one of the keys in this property. The default value is `nil`, which causes CloudKit to fetch all of the record's keys.
///
/// Because you can fetch records of different types, configure the array to include the merged set of all field names for the requested records and at least one field name from each record type.
///
/// If you intend to specify the desired set of keys, set the value of this property before executing the operation or submitting it to a queue.
@property (nullable, copy) NSArray<CKRecordFieldKey> *desiredKeys;
@end



/// A configuration object that describes the information to fetch from a record zone.
///
/// @DeprecationSummary {
///     Use ``CKFetchRecordZoneChangesOperation/ZoneConfiguration`` instead.
/// }
API_DEPRECATED_WITH_REPLACEMENT("CKFetchRecordZoneChangesConfiguration", macos(10.12, 10.14), ios(10.0, 12.0), tvos(10.0, 12.0), watchos(3.0, 5.0))
@interface CKFetchRecordZoneChangesOptions : NSObject <NSSecureCoding, NSCopying>

/// The token that identifies the starting point for retrieving changes.
///
/// Each fetch request returns a unique token in addition to any changes. CloudKit passes the token to your ``CKFetchRecordZoneChangesOperation/recordZoneFetchCompletionBlock`` handler. During a subsequent fetch request, providing the previous token causes the server to return only the changes since the previous fetch request. Tokens are opaque values that you can write to disk safely and reuse later.
@property (nullable, copy, nonatomic) CKServerChangeToken *previousServerChangeToken;

/// The maximum number of records to fetch from the record zone.
///
/// Use this property to limit the number of results in situations where you expect a large number of records. The default value is 0, which causes the server to return an appropriate number of records using dynamic conditions.
///
/// When the number of records that CloudKit returns exceeds this limit, the operation sets the `moreComing` property to <doc://com.apple.documentation/documentation/swift/true> when executing the ``CKFetchRecordZoneChangesOperation/recordZoneFetchCompletionBlock`` handler.
@property (assign, nonatomic) NSUInteger resultsLimit;

/// The fields to fetch for the requested records.
///
/// Use this property to limit the amount of data that CloudKit retrieves for each record during the fetch operation. This property contains an array of strings, each of which is the name of a field from the target records. When you retrieve a record, CloudKit only includes fields with names that match one of the keys in this property. The default value is `nil`, which causes CloudKit to fetch all of the record's keys.
///
/// Because you can fetch records of different types, configure the array to include the merged set of all field names for the requested records and at least one field name from each record type.
///
/// If you intend to specify the desired set of keys, set the value of this property before executing the operation or submitting it to a queue.
@property (nullable, copy, nonatomic) NSArray<CKRecordFieldKey> *desiredKeys;
@end

NS_HEADER_AUDIT_END(nullability, sendability)
