//
//  CKFetchRecordsOperation.h
//  CloudKit
//
//  Copyright (c) 2014 Apple Inc. All rights reserved.
//

#import <CloudKit/CKDatabaseOperation.h>

#import <CloudKit/CKRecord.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

/// An operation for retrieving records from a database.
///
/// Use this operation to retrieve the entire contents of each record or only a subset of its contained values. As records become available, the operation object reports progress about the state of the operation to several different blocks, which you can use to process the results.
///
/// Fetching records is a common use of CloudKit, even if your app doesn't cache record IDs locally. For example, when you fetch a record related to the current record through a ``CKRecord/Reference`` object, you use the ID in the reference to perform the fetch.
///
/// The handlers you assign to process the fetched records execute serially on an internal queue that the fetch operation manages. You must provide handlers capable of executing on a background thread, so any tasks that require access to the main thread must redirect accordingly.
///
/// In addition to data records, a fetch records operation can fetch the current user record. The ``fetchCurrentUserRecordOperation()`` method returns a specially configured operation object that retrieves the current user record. That record is a standard ``CKRecord`` object that has no content initially. You can add data to the user record and save it as necessary. Don't store sensitive personal information, such as passwords, in the user record because other users of your app can access the discoverable user record in a public database. If you must store sensitive information about a user, do so in a separate record that is accessible only to that user.
///
/// If you assign a closure to the <doc://com.apple.documentation/documentation/foundation/operation/completionblock> property of the operation object, CloudKit calls it after the operation executes and returns its results. Use a closure to perform any housekeeping tasks for the operation, but don't use it to process the results of the operation. The closure you specify should handle the failure of the operation to complete its task, whether due to an error or an explicit cancellation.
API_AVAILABLE(macos(10.10), ios(8.0), watchos(3.0))
@interface CKFetchRecordsOperation : CKDatabaseOperation

/// Creates an empty fetch operation.
///
/// You must set the ``CKFetchRecordsOperation/recordIDs`` property before you execute the operation.
///
/// A fetch operation retrieves all of a record's fields, including any assets that those fields reference. If you want to minimize the amount of data that the operation returns, configure the ``CKFetchRecordsOperation/desiredKeys-34l1l`` property with only the keys that contain the values that you have an interest in.
///
/// After initializing the operation, you must associate at least one progress handler with the operation (excluding the completion handler) to process the results.
- (instancetype)init NS_DESIGNATED_INITIALIZER;

/// Creates a fetch operation for retrieving the records with the specified IDs.
///
/// - Parameters:
///   - recordIDs: An array of ``CKRecord/ID`` objects that represents the records you want to retrieve. If you provide an empty array, you must set the ``CKFetchRecordsOperation/recordIDs`` property before you execute the operation.
///
/// A fetch operation retrieves all of a record's fields, including any assets that those fields reference. If you want to minimize the amount of data that the operation returns, configure the ``CKFetchRecordsOperation/desiredKeys-34l1l`` property with only the keys that contain the values that you have an interest in.
///
/// After initializing the operation, you must associate at least one progress handler with the operation (excluding the completion handler) to process the results.
- (instancetype)initWithRecordIDs:(NSArray<CKRecordID *> *)recordIDs;

/// Returns a fetch operation for retrieving the current user record.
///
/// The returned operation object searches for the single record that corresponds to the current user record. You must associate at least one progress handler with the operation object (excluding the completion handler) to process the results.
+ (instancetype)fetchCurrentUserRecordOperation;

/// The record IDs of the records to fetch.
///
/// Use this property to view or change the IDs of the records you want to retrieve. If you use the operation that ``CKFetchRecordsOperation/fetchCurrentUserRecordOperation()`` returns, CloudKit ignores the contents of this property and sets its value to `nil`.
///
/// If you intend to specify a value other than `nil`, do so before you execute the operation or add the operation to a queue. The records you fetch don't need to be in the same record zone. The record ID for each record provides the zone information that CloudKit needs to fetch the corresponding record.
@property (nullable, copy, nonatomic) NSArray<CKRecordID *> *recordIDs;

/// The fields of the records to fetch.
///
/// Use this property to limit the amount of data that CloudKit returns for each record during the fetch operation. When CloudKit returns a record, it only includes fields with names that match one of the keys in this property. The property's default value is `nil`, which instructs CloudKit to return all of a record's keys.
///
/// If you're retrieving records of different types, make sure the array includes the fields you want from all of the various record types that the operation can return.
///
/// If you intend to specify a value other than `nil`, do so before you execute the operation or add the operation to a queue.
@property (nullable, copy, nonatomic) NSArray<CKRecordFieldKey> *desiredKeys;

/// The closure to execute with progress information for individual records.
///
/// This property is a closure that returns no value and has the following parameters:
///
/// - The ID of the record to retrieve.
/// - The amount of data, as a percentage, that CloudKit downloads for the record. The range is `0.0` to `1.0`, where `0.0` indicates that CloudKit hasn't downloaded anything, and `1.0` means the download is complete.
///
/// The fetch operation executes this closure one or more times for each record ID in the ``CKFetchRecordsOperation/recordIDs`` property. Each time the closure executes, it executes serially with respect to the other progress closures of the operation. You can use this closure to track the ongoing progress of the download operation.
///
/// If you intend to use this closure to process results, set it before you execute the operation or add the operation to a queue.
@property (nullable, copy, nonatomic) void (^perRecordProgressBlock)(CKRecordID *recordID, double progress);

/// The closure to execute when a record becomes available.
///
/// This property is a closure that returns no value and has the following parameters:
///
/// - The record, or `nil` if CloudKit can't retrieve the record.
/// - The ID of the record.
/// - If CloudKit can't retrieve the record, an error that provides information about the failure; otherwise, `nil`.
///
/// The fetch operation executes this closure once for each record ID in the ``CKFetchRecordsOperation/recordIDs`` property. Each time the closure executes, it executes serially with respect to the other progress closures of the operation.
///
/// If you intend to use this closure to process results, set it before you execute the operation or submit the operation to a queue.
@property (nullable, copy, nonatomic) void (^perRecordCompletionBlock)(CKRecord * _Nullable record, CKRecordID * _Nullable recordID, NSError * _Nullable error)
CK_SWIFT_DEPRECATED("Use perRecordResultBlock instead", macos(10.10, 12.0), ios(8.0, 15.0), tvos(9.0, 15.0), watchos(3.0, 8.0));


/// The closure to execute after CloudKit retrieves all of the records.
///
/// This property is a closure that returns no value and has the following parameters:
///
/// - A dictionary that contains the records that CloudKit retrieves. Each key in the dictionary is a ``CKRecord/ID`` object that corresponds to a record you request. The value of each key is the actual ``CKRecord`` object that CloudKit returns.
/// - If CloudKit can't retrieve any of the records, an error that provides information about the failure; otherwise, `nil`.
///
/// The fetch operation executes this closure only once, and it's your final opportunity to process the results. The closure executes after all of the individual progress closures, but before the operation's completion closure. The closure executes serially with respect to the other progress closures of the operation.
///
/// The closure reports an error of type ``CKError/Code/partialFailure`` when it retrieves only some of the records successfully. The <doc://com.apple.documentation/documentation/foundation/nserror/userinfo> dictionary of the error contains a ``CKPartialErrorsByItemIDKey`` key that has a dictionary as its value. The keys of the dictionary are the IDs of the records that the operation can't retrieve, and the corresponding values are errors that contain information about the failures.
///
/// If you intend to use this closure to process results, set it before you execute the operation or submit the operation to a queue.
@property (nullable, copy, nonatomic) void (^fetchRecordsCompletionBlock)(NSDictionary<CKRecordID * , CKRecord *> * _Nullable recordsByRecordID, NSError * _Nullable operationError)
CK_SWIFT_DEPRECATED("Use fetchRecordsResultBlock instead", macos(10.10, 12.0), ios(8.0, 15.0), tvos(9.0, 15.0), watchos(3.0, 8.0));

@end

NS_HEADER_AUDIT_END(nullability, sendability)
