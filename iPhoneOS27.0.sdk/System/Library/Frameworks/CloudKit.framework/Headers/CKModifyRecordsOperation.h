//
//  CKModifyRecordsOperation.h
//  CloudKit
//
//  Copyright (c) 2014 Apple Inc. All rights reserved.
//

#import <CloudKit/CKDatabaseOperation.h>

@class CKRecord, CKRecordID;

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

/// Constants that indicate which policy to apply when saving records.
typedef NS_ENUM(NSInteger, CKRecordSavePolicy) {
    /// A policy that instructs CloudKit to only proceed if the record's change tag matches that of the server's copy.
    ///
    /// The server maintains a change tag for each record automatically. When you fetch a record, that change tag accompanies the rest of the record's data. If the change tag in your local record matches the change tag of the record on the server, the save operation proceeds normally. If the server record contains a newer change tag, CloudKit doesn't save the record and reports a ``CKError/Code/serverRecordChanged`` error.
    ///
    /// - Note: A ``CKShare`` record is always saved with policy `ifServerRecordUnchanged`, regardless of an operation's ``CKModifyRecordsOperation/savePolicy``.
    CKRecordSaveIfServerRecordUnchanged = 0,

    /// A policy that instructs CloudKit to save only the fields of a record that contain changes.
    ///
    /// - Important: This policy doesn't compare record change tags. To only save changes to the most recent version of a record, use ``CKModifyRecordsOperation/RecordSavePolicy/ifServerRecordUnchanged`` instead.
    CKRecordSaveChangedKeys             = 1,

    /// A policy that instructs CloudKit to save all keys of a record, even those without changes.
    ///
    /// - Important: This policy doesn't compare record change tags. To only save changes to the most recent version of a record, use ``CKModifyRecordsOperation/RecordSavePolicy/ifServerRecordUnchanged`` instead.
    ///
    /// This policy causes CloudKit to overwrite any existing values on the server. It's possible for a server record to contain keys that aren't present locally. Another client might add keys to the record after you fetch it. Also, if you use the ``CKFetchRecordsOperation/desiredKeys-34l1l`` property to request a subset of keys during a fetch operation, saving that same record modifies only those keys that you include in the fetch and any keys you add to the record after that.
    CKRecordSaveAllKeys                 = 2
} API_AVAILABLE(macos(10.10), ios(8.0), watchos(3.0));

/// An operation that modifies one or more records.
///
/// After modifying the fields of a record, use this operation to save those changes to a database. You also use this operation to delete records permanently from a database.
///
/// If you're saving a record that contains a reference to another record, set the reference's ``CKRecord/Reference/action`` to indicate if the target record's deletion should cascade to the saved record. This helps avoid orphaned records in explicit record hierarchies. When creating two new records that have a reference between them, use the same operation to save both records at the same time. During a save operation, CloudKit requires that the target record of the ``CKRecord/parent`` reference, if set, exists in the database or is part of the same operation; all other reference fields are exempt from this requirement.
///
/// When you save records, the value in the ``savePolicy`` property determines how to proceed when CloudKit detects conflicts. Because records can change between the time you fetch them and the time you save them, the save policy determines whether new changes overwrite existing changes. By default, the operation reports an error when there's a newer version on the server. You can change the default setting to permit your changes to overwrite the server values wholly or partially.
///
/// The handlers you assign to monitor progress of the operation execute serially on an internal queue that the operation manages. You must provide handlers capable of executing on a background thread, so any tasks that require access to the main thread must redirect accordingly.
///
/// If you assign a completion handler to the <doc://com.apple.documentation/documentation/foundation/operation/completionblock> property of the operation, CloudKit calls it after the operation executes and returns the results. Use the completion handler to perform any housekeeping tasks for the operation, but don't use it to process the results of the operation. The completion handler you provide should manage any failures of the operation, whether due to an error or an explicit cancellation.
///
/// - Important: To ensure the speed of fetching and saving records, the server may reject large operations. When this occurs, a block reports the ``CKError/Code/limitExceeded`` error. Your app should handle this error, and refactor the operation into multiple smaller batches.
API_AVAILABLE(macos(10.10), ios(8.0), watchos(3.0))
@interface CKModifyRecordsOperation : CKDatabaseOperation

/// Creates an empty modify records operation.
///
/// You must set at least one of the ``CKModifyRecordsOperation/recordsToSave`` or ``CKModifyRecordsOperation/recordIDsToDelete`` properties before you execute the operation.
- (instancetype)init NS_DESIGNATED_INITIALIZER;

/// Creates an operation for modifying the specified records.
///
/// - Parameters:
///   - records: The records to save. You can specify `nil` for this parameter.
///   - recordIDs: The IDs of the records to delete. You can specify `nil` for this parameter.
///
/// The records that you intend to save or delete must all reside in the same database, which you specify when you configure the operation. If your app saves a record in a database that doesn't exist, the server creates the database.
- (instancetype)initWithRecordsToSave:(nullable NSArray<CKRecord *> *)records recordIDsToDelete:(nullable NSArray<CKRecordID *> *)recordIDs;

/// The records to save to the database.
///
/// The initial value of the property is the array that you provide to the ``CKModifyRecordsOperation/init(recordsToSave:recordIDsToDelete:)`` method. You can modify this array as necessary before you execute the operation. The records must all target the same database, but can belong to different record zones.
///
/// If you intend to change the value of this property, do so before you execute the operation or submit the operation to a queue.
@property (nullable, copy, nonatomic) NSArray<CKRecord *> *recordsToSave;

/// The IDs of the records to delete permanently from the database.
///
/// An array of ``CKRecord/ID`` objects that identifies the records to delete. The initial value of the property is the array of record IDs that you provide to the ``CKModifyRecordsOperation/init(recordsToSave:recordIDsToDelete:)`` method.
///
/// When deleting records, the operation reports progress only on the records with the IDs that you specify in this property. Deleting records can trigger the deletion of related records if there is an owner-owned relationship between the records involving a ``CKRecord/Reference`` object. When additional deletions occur, CloudKit doesn't pass them to the progress handler of the operation. For that reason, it's important to understand the implications of the ownership model you use when you relate records to each other through a ``CKRecord/Reference`` object. For more information about owner-owned relationships, see ``CKRecord/Reference``.
///
/// If you intend to change the value of this property, do so before you execute the operation or submit the operation to a queue.
@property (nullable, copy, nonatomic) NSArray<CKRecordID *> *recordIDsToDelete;

/// The policy to use when saving changes to records.
///
/// The server uses this property to determine how to proceed when saving record changes. The exact behavior depends on the policy you choose:
///
/// - Use ``CKModifyRecordsOperation/RecordSavePolicy/ifServerRecordUnchanged`` to only save a record when the change tag of the local copy matches that of the server's copy. If the server record's change tag is more recent, CloudKit discards the save and returns a ``CKError/Code/serverRecordChanged`` error.
/// - Use ``CKModifyRecordsOperation/RecordSavePolicy/changedKeys`` to save only the fields of the record that contain changes. The server doesn't compare record change tags when using this policy.
/// - Use ``CKModifyRecordsOperation/RecordSavePolicy/allKeys`` to save every field of the record, even those without changes. The server doesn't compare record change tags when using this policy.
///
/// If you change the property's value, do so before you execute the operation or submit the operation to a queue. The default value is ``CKModifyRecordsOperation/RecordSavePolicy/ifServerRecordUnchanged``.
@property (assign, nonatomic) CKRecordSavePolicy savePolicy;

/// A token that tracks local changes to records.
///
/// The default value is `nil`.
///
/// When you modify records from a fetch operation, specify a token using this property to indicate which version of the record you most recently modified. Compare the token you supply to the token in the next record fetch to confirm the server  successfully receives the device's most recent modify request.
///
/// If you intend to change the value of this property, do so before you execute the operation or submit the operation to a queue.
@property (nullable, copy, nonatomic) NSData *clientChangeTokenData;

/// A Boolean value that indicates whether the entire operation fails when CloudKit can't update one or more records in a record zone.
///
/// Modifying records atomically prevents you from updating your data in a way that leaves it in an inconsistent state. You use atomic updates when you want to write multiple records to the same record zone. If there's a failure to modify any of the records in a zone, CloudKit doesn't change the other records in that same zone. The record zone must have the ``CKRecordZone/Capabilities/atomic`` capability for this behavior to apply. If a record zone doesn't support the atomic capability, setting this property has no effect.
///
/// The default value of this property is <doc://com.apple.documentation/documentation/swift/true>, which causes all modifications within a single record zone to occur atomically. If your operation contains records in multiple record zones, a failure in one zone doesn't prevent modifications to records in a different zone. Changing the value of this property to <doc://com.apple.documentation/documentation/swift/false> causes CloudKit to modify records individually, regardless of whether the record zone supports atomic modifications.
@property (assign, nonatomic) BOOL atomic NS_SWIFT_NAME(isAtomic);

/// The closure to execute with progress information for individual records.
///
/// This property is a closure that returns no value and has the following parameters:
///
/// - The record that CloudKit saves.
/// - The amount of data, as a percentage, that CloudKit saves for the record. The range is `0.0` to `1.0`, where `0.0` indicates that CloudKit hasn't saved any data, and `1.0` means that CloudKit has saved the entire record.
///
/// The modify records operation executes this closure one or more times for each record in the ``CKModifyRecordsOperation/recordsToSave`` property. Each time the closure executes, it executes serially with respect to the other progress closures of the operation. You can use this closure to track the ongoing progress of the operation.
///
/// If you intend to use this closure to process results, set it before you execute the operation or add the operation to a queue.
@property (nullable, copy, nonatomic) void (^perRecordProgressBlock)(CKRecord *record, double progress);

/// The closure to execute when CloudKit saves a record.
///
/// This property is a closure that returns no value and has the following parameters:
///
/// - The record that CloudKit saves.
/// - If CloudKit can't save the record, an error that provides information about the failure; otherwise, `nil`.
///
/// The closure executes once for each record in the ``CKModifyRecordsOperation/recordsToSave`` property. Each time the closure executes, it executes serially with respect to the other record completion blocks of the operation.
///
/// If you intend to use this closure to process results, set it before you execute the operation or submit the operation to a queue.
@property (nullable, copy, nonatomic) void (^perRecordCompletionBlock)(CKRecord *record, NSError * _Nullable error) API_DEPRECATED_WITH_REPLACEMENT("perRecordSaveBlock", macos(10.10, 12.0), ios(8.0, 15.0), tvos(9.0, 15.0), watchos(3.0, 8.0));

/// The closure to execute when CloudKit saves a record.
///
/// This property is a closure that returns no value and has the following parameters:
///
/// - The ID of the record that CloudKit saves.
/// - The saved record (as it appears on the server), or `nil` if there's an error.
/// - If CloudKit can't save the record, an error that provides information about the failure; otherwise, `nil`.
///
/// The closure executes once for each record in the ``CKModifyRecordsOperation/recordsToSave`` property. Each time the closure executes, it executes serially with respect to the other record completion blocks of the operation.
///
/// If you intend to use this closure to process results, set it before you execute the operation or submit the operation to a queue.
@property (nullable, copy, nonatomic) void (^perRecordSaveBlock)(CKRecordID *recordID, CKRecord * _Nullable record, NSError * _Nullable error) API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0), watchos(8.0)) NS_REFINED_FOR_SWIFT;

/// The closure to execute when CloudKit deletes a record.
///
/// This property is a closure that returns no value and has the following parameters:
///
/// - The ID of the record that CloudKit deletes.
/// - If CloudKit can't delete the record, an error that provides information about the failure; otherwise, `nil`.
///
/// The closure executes once for each record in the ``CKModifyRecordsOperation/recordIDsToDelete`` property. Each time the closure executes, it executes serially with respect to the other record completion blocks of the operation.
///
/// If you intend to use this closure to process results, set it before you execute the operation or submit the operation to a queue.
@property (nullable, copy, nonatomic) void (^perRecordDeleteBlock)(CKRecordID *recordID, NSError * _Nullable error) API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0), watchos(8.0)) NS_REFINED_FOR_SWIFT;

/// The closure to execute after CloudKit modifies all of the records.
///
/// This property is a closure that returns no value and has the following parameters:
///
/// - The records that CloudKit saves.
/// - The IDs of the records that CloudKit deletes.
/// - If CloudKit can't modify any of the records, this parameter provides information about the failure; otherwise, it's `nil`.
///
/// The closure executes only once, and represents your final opportunity to process the operation's results. It executes after all record progress closures and record completion closures finish. The closure executes serially with respect to the other closures of the operation.
///
/// Although this closure executes after the modification of records completes, it executes prior to the indexing of queries for those modified records. Therefore, if a query executes in this completion closure, the results of that query might not include the changes from this operation. Conversely, records that CloudKit fetches in the completion closure are up to date with the changes from the associated operation.
///
/// The closure reports an error of type ``CKError/Code/partialFailure`` when it modifies only some of the records successfully. The <doc://com.apple.documentation/documentation/foundation/nserror/userinfo> dictionary of the error contains a ``CKPartialErrorsByItemIDKey`` key that has a dictionary as its value. The keys of the dictionary are the IDs of the records that the operation can't modify, and the corresponding values are errors that contain information about the failures.
///
/// If you intend to use this closure to process results, set it before you execute the operation or submit the operation to a queue.
@property (nullable, copy, nonatomic) void (^modifyRecordsCompletionBlock)(NSArray<CKRecord *> * _Nullable savedRecords, NSArray<CKRecordID *> * _Nullable deletedRecordIDs, NSError * _Nullable operationError)
CK_SWIFT_DEPRECATED("Use modifyRecordsResultBlock instead", macos(10.10, 12.0), ios(8.0, 15.0), tvos(9.0, 15.0), watchos(3.0, 8.0));

@end

NS_HEADER_AUDIT_END(nullability, sendability)
