//
//  CKFetchRecordChangesOperation.h
//  CloudKit
//
//  Copyright (c) 2014 Apple Inc. All rights reserved.
//

#import <CloudKit/CKDatabaseOperation.h>

#import <CloudKit/CKRecord.h>
#import <CloudKit/CKServerChangeToken.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

/// An operation that reports on the changed and deleted records in the specified record zone.
///
/// @DeprecationSummary {
///     Use ``CKFetchRecordZoneChangesOperation`` instead.
/// }
/// 
/// Use this type of operation object to optimize fetch operations for sets of records you manage locally. Specifically, use it when you maintain a local cache of your record data and need to synchronize that cache periodically with the server.
///
/// To get the most benefit out of a `CKFetchRecordChangesOperation` object, you must maintain a local cache of the records from the specified zone. Each time you fetch changes from that zone, the server provides a token that identifies your request. With each subsequent fetch request, you initialize the operation object with the token from the previous request, and the server returns only the records with changes since that request.
///
/// The blocks you assign to process the fetched records execute serially on an internal queue that the operation manages. You must provide blocks capable of executing on a background thread, so any tasks that require access to the main thread must redirect accordingly.
///
/// If you assign a completion block to the <doc://com.apple.documentation/documentation/foundation/operation/completionblock> property of the operation object, the system calls the completion block after the operation executes and returns its results to you. You can use a completion block to perform housekeeping tasks for the operation, but don't use it to process the results of the operation. Any completion block you specify should handle the failure of the operation to complete its task, whether due to an error or an explicit cancellation.
API_DEPRECATED_WITH_REPLACEMENT("CKFetchRecordZoneChangesOperation", macos(10.10, 10.12), ios(8.0, 10.0), tvos(9.0, 10.0), watchos(3.0, 3.0))
@interface CKFetchRecordChangesOperation : CKDatabaseOperation

/// Creates an empty fetch record changes operation.
- (instancetype)init NS_DESIGNATED_INITIALIZER;

/// Creates an operation for fetching changes in the specified record zone.
///
/// - Parameters:
///   - recordZoneID: The zone that contains the records you want to fetch. You can fetch changes in a custom zone. CloudKit doesn't support syncing the default zone.
///   - previousServerChangeToken: The change token from a previous fetch operation. This is the token that the system passes to your ``CKFetchRecordChangesOperation/fetchRecordChangesCompletionBlock`` handler during a previous fetch operation. Use this token to limit the returned data to only those changes that occur after that fetch request. If you specify `nil` for this parameter, the operation object fetches all records and their contents.
///
/// - Returns: An initialized operation object.
///
/// When initializing the operation object, use the token from a previous fetch request if you have one. You can archive tokens and write them to disk for later use.
///
/// The returned operation object retrieves all changed fields of the record, including any assets in those fields. If you want to minimize the amount of data that returns even further, configure the ``CKFetchRecordChangesOperation/desiredKeys`` property with the subset of keys that have values you want to fetch.
///
/// After initializing the operation, associate at least one progress block with the operation object (excluding the completion block) to process the results.
- (instancetype)initWithRecordZoneID:(CKRecordZoneID *)recordZoneID previousServerChangeToken:(nullable CKServerChangeToken *)previousServerChangeToken;

/// The ID of the record zone with the records you want to fetch.
///
/// Typically, you set the value of this property when you initialize the operation object. If you intend to change the record zone, update the value before executing the operation or submitting it to a queue.
@property (nullable, copy, nonatomic) CKRecordZoneID *recordZoneID;

/// The token that identifies the starting point for retrieving changes.
///
/// Each fetch request returns a unique token in addition to any changes. The token passes as a parameter to your ``CKFetchRecordChangesOperation/fetchRecordChangesCompletionBlock`` handler. During a subsequent fetch request, providing the previous token causes the server to return only the changes that occur after the previous fetch request. Tokens are opaque data objects that you can write to disk safely and reuse later.
///
/// Typically, you set the value of this property when you initialize the operation object. If you intend to change the record zone, update the value of the property before executing the operation or submitting it to a queue.
@property (nullable, copy, nonatomic) CKServerChangeToken *previousServerChangeToken;

/// The maximum number of changed records to report with this operation object.
///
/// Use this property to limit the number of results in situations where you expect the number of changed records to be large. The default value is 0, which causes the server to return an appropriate number of results using dynamic conditions.
///
/// When the number of returned results exceeds the results limit, the operation object sets the ``CKFetchRecordChangesOperation/moreComing`` property to <doc://com.apple.documentation/documentation/swift/true> before executing the block in the ``CKFetchRecordChangesOperation/fetchRecordChangesCompletionBlock`` property. In your block, check the value of that property, and if it's <doc://com.apple.documentation/documentation/swift/true>, create a new ``CKFetchRecordChangesOperation`` object to fetch more results.
@property (assign, nonatomic) NSUInteger resultsLimit;

/// The fields to fetch for the requested records.
///
/// Use this property to limit the amount of data that the system retrieves for each record during the fetch operation. This property contains an array of strings, each of which contains the name of a field from the target records. When you retrieve a record, the returned records only include fields with names that match one of the keys in this property. The default value is `nil`, which causes the system to fetch all keys of the record.
///
/// Because you can fetch records of different types, configure the array to include the merged set of all field names for the requested records and at least one field name from each record type.
///
/// If you intend to specify the desired set of keys, set the value of this property before executing the operation or submitting it to a queue.
@property (nullable, copy, nonatomic) NSArray<CKRecordFieldKey> *desiredKeys;

/// The block to execute with the contents of a changed record.
///
/// The block returns no value and takes the following parameters:
///
///   - term `record`: The changed record. If you specify a value for the ``CKFetchRecordChangesOperation/desiredKeys`` property, the record only contains the fields in the ``CKFetchRecordChangesOperation/desiredKeys`` property.
///
/// The operation object executes this block once for each record in the zone with changes since the previous fetch request. Each time the block executes, it executes serially with respect to the other progress blocks of the operation. If no records change, the block doesn't execute.
///
/// If you intend to use this block to process results, set it before executing the operation or submitting it to a queue.
@property (nullable, copy, nonatomic) void (^recordChangedBlock)(CKRecord *record);

/// The block to execute with the ID of a deleted record.
///
/// The block returns no value and takes the following parameters:
///
///   - term `recordID`: The ID of the deleted record.
///
/// The operation object executes this block once for each record the server deletes in the record zone after the previous fetch request. Each time the block executes, it executes serially with respect to the other progress blocks of the operation. If there aren't any deleted records, this block doesn't execute.
///
/// If you intend to use this block to process results, set it before executing the operation or submitting it to a queue.
@property (nullable, copy, nonatomic) void (^recordWithIDWasDeletedBlock)(CKRecordID *recordID);

/// A Boolean value that indicates whether more results are available.
///
/// If the server is unable to deliver all of the changed results with this operation object, it sets this property to <doc://com.apple.documentation/documentation/swift/true> before executing the block in the ``CKFetchRecordChangesOperation/fetchRecordChangesCompletionBlock`` property. To fetch the remaining changes, create a new ``CKFetchRecordChangesOperation`` object using the change token that the server returns.
@property (readonly, assign, nonatomic) BOOL moreComing;

/// The block to execute when the system finishes processing all changes.
///
/// The block returns no value and takes the following parameters:
///
///   - term `serverChangeToken`: The new change token from the server. You can store this token locally and use it during subsequent fetch operations to limit the results to records that the system changes after executing the operation.
///   - term `clientChangeToken`: The most recent client change token from the device. If the change token isn't the most recent change token you provided, the server might not have received the associated changes.
///   - term `operationError`: An error object that contains information about a problem, or `nil` if the system successfully retrieves the changes.
///
/// When implementing this block, check the ``CKFetchRecordChangesOperation/moreComing`` property of the operation object to verify that the server was able to deliver all results. If that property is <doc://com.apple.documentation/documentation/swift/true>, you must create another operation object using the value in the `serverChangeToken` parameter to fetch any remaining changes.
///
/// The operation object executes this block only once at the conclusion of the operation. It executes after all individual change blocks, but before the operation's completion block. The block executes serially with respect to the other progress blocks of the operation.
///
/// If you intend to use this block to process results, set it before executing the operation or submitting the operation object to a queue.
@property (nullable, copy, nonatomic) void (^fetchRecordChangesCompletionBlock)(CKServerChangeToken * _Nullable serverChangeToken, NSData * _Nullable clientChangeTokenData, NSError * _Nullable operationError);

@end

NS_HEADER_AUDIT_END(nullability, sendability)
