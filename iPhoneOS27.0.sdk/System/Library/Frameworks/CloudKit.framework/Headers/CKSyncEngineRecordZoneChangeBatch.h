//
//  CKSyncEngineRecordZoneChangeBatch.h
//  CloudKit
//
//  Copyright © 2022 Apple Inc. All rights reserved.
//

@class CKRecord, CKRecordID, CKRecordZoneID;

#import <CloudKit/CKDefines.h>
#import <CloudKit/CKSyncEngineState.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

/// An object that contains the record changes for a single send operation.
API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0), watchos(10.0))
NS_REFINED_FOR_SWIFT
CK_SUBCLASSING_RESTRICTED
NS_SWIFT_SENDABLE
@interface CKSyncEngineRecordZoneChangeBatch : NSObject

/// Creates a batch of records to modify using the provided record zone changes.
///
/// - Parameters:
///   - pendingChanges: The record zone changes to process.
///   - recordProvider: A block that returns the record for the specified record identifier.
///
/// - Returns: The batch of records to modify, or `nil` if there are no pending changes.
///
/// This method iterates over `pendingChanges` and adds the necessary information to the new batch, until there are no more changes or the size of the batch reaches the maximum limit.
/// If the type of change is a record save, the method asks the specified `recordProvider` block for that record.
/// If the closure returns `nil`, the method skips that change.
- (nullable instancetype)initWithPendingChanges:(NSArray<CKSyncEnginePendingRecordZoneChange *> *)pendingChanges
                                 recordProvider:(CKRecord * _Nullable (NS_SWIFT_SENDABLE NS_NOESCAPE ^)(CKRecordID *recordID))recordProvider;

/// Creates a batch of records to modify.
///
/// - Parameters:
///   - recordsToSave: The records to save.
///   - recordIDsToDelete: The identifiers of the records to delete.
///   - atomicByZone: A Boolean value that determines whether CloudKit modifies the specified records atomically by record zone.
///
/// - Returns: An initialized change batch.
///
/// - Important: When using this initializer to create batches, consider the number of records you specify and their combined size.
/// If you specify too many records, or their combined size is too large, the send operation may fail with an error of type ``CKError/Code/limitExceeded``.
- (instancetype)initWithRecordsToSave:(nullable NSArray<CKRecord *> *)recordsToSave
                    recordIDsToDelete:(nullable NSArray<CKRecordID *> *)recordIDsToDelete
                         atomicByZone:(BOOL)atomicByZone;

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

/// The records to save.
@property (readonly, copy) NSArray<CKRecord *> *recordsToSave;

/// The unique identifiers of the records to delete.
@property (readonly, copy) NSArray<CKRecordID *> *recordIDsToDelete;

/// A Boolean value that determines whether CloudKit modifies records atomically by record zone.
///
/// When <doc://com.apple.documentation/documentation/swift/true>, CloudKit processes record changes atomically by record zone, and if any individual change fails, all other changes in that record's record zone fail and return an error of type ``CKError/Code/batchRequestFailed``.
///
/// The default value is <doc://com.apple.documentation/documentation/swift/false>.
@property (assign) BOOL atomicByZone;

@end

NS_HEADER_AUDIT_END(nullability, sendability)
