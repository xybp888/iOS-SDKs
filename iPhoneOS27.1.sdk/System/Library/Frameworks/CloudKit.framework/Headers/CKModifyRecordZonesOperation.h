//
//  CKModifyRecordZonesOperation.h
//  CloudKit
//
//  Copyright (c) 2014 Apple Inc. All rights reserved.
//

#import <CloudKit/CKDatabaseOperation.h>

@class CKRecordZone, CKRecordZoneID;

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

/// An operation that modifies one or more record zones.
///
/// After you create one or more record zones, use this operation to save those zones to the database. You can also use the operation to delete record zones and their records.
///
/// If you assign a handler to the <doc://com.apple.documentation/documentation/foundation/operation/completionblock> property of the operation, CloudKit calls the handler after the operation executes and returns its results. Use the handler to perform housekeeping tasks for the operation, but don't use it to process the results of the operation. The handler you provide should manage any failures of the operation, whether due to an error or an explicit cancellation.
API_AVAILABLE(macos(10.10), ios(8.0), watchos(3.0))
@interface CKModifyRecordZonesOperation : CKDatabaseOperation

/// Creates an empty modify record zones operation.
///
/// You must set at least one of the ``CKModifyRecordZonesOperation/recordZonesToSave`` or ``CKModifyRecordZonesOperation/recordZoneIDsToDelete`` properties before you execute the operation.
- (instancetype)init NS_DESIGNATED_INITIALIZER;

/// Creates an operation for modifying the specified record zones.
///
/// - Parameters:
///   - recordZonesToSave: The record zones to save. You can specify `nil` for this parameter.
///   - recordZoneIDsToDelete: The IDs of the record zones to delete. You can specify `nil` for this parameter.
///
/// The record zones you intend to save or delete must all reside in the same database, which you specify when you configure the operation. If you delete a record zone, CloudKit deletes any records it contains.
- (instancetype)initWithRecordZonesToSave:(nullable NSArray<CKRecordZone *> *)recordZonesToSave recordZoneIDsToDelete:(nullable NSArray<CKRecordZoneID *> *)recordZoneIDsToDelete;

/// The record zones to save to the database.
///
/// The initial value of the property is the array that you provide to the ``CKModifyRecordZonesOperation/init(recordZonesToSave:recordZoneIDsToDelete:)`` method. You can modify this array as necessary before you execute the operation. The record zones must all target the same database. You can specify `nil`, or an empty array, for this property.
///
/// If you intend to change the value of this property, do so before you execute the operation or submit the operation to a queue.
@property (nullable, copy, nonatomic) NSArray<CKRecordZone *> *recordZonesToSave;

/// The IDs of the record zones to delete permanently from the database.
///
/// The initial value of the property is the array of zone IDs that you provide to the ``CKModifyRecordZonesOperation/init(recordZonesToSave:recordZoneIDsToDelete:)`` method. You can modify this array as necessary before you execute the operation. The record zones must all target the same database. You can specify `nil`, or an empty array, for this property.
///
/// If you intend to change the value of this property, do so before you execute the operation or submit the operation to a queue.
@property (nullable, copy, nonatomic) NSArray<CKRecordZoneID *> *recordZoneIDsToDelete;

/// The closure to execute when CloudKit saves a record zone.
///
/// This property is a closure that returns no value and has the following parameters:
///
/// - The ID of the record zone that CloudKit saves.
/// - The record zone that CloudKit saves, or `nil` if CloudKit can't save the record zone.
/// - If CloudKit can't save the record zone, an error that provides information about the failure; otherwise, `nil`.
///
/// The closure executes once for each record zone in the ``CKModifyRecordZonesOperation/recordZonesToSave`` property. Each time the closure executes, it executes serially with respect to the other record zone completion blocks of the operation.
///
/// If you intend to use this closure to process results, set it before you execute the operation or submit the operation to a queue.
@property (nullable, copy, nonatomic) void (^perRecordZoneSaveBlock)(CKRecordZoneID *recordZoneID, CKRecordZone * _Nullable recordZone, NSError * _Nullable error) API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0), watchos(8.0)) NS_REFINED_FOR_SWIFT;

/// The closure to execute when CloudKit deletes a record zone.
///
/// This property is a closure that returns no value and has the following parameters:
///
/// - The ID of the record zone that CloudKit deletes.
/// - If CloudKit can't delete the record zone, an error that provides information about the failure; otherwise, `nil`.
///
/// The closure executes once for each record zone in the ``CKModifyRecordZonesOperation/recordZoneIDsToDelete`` property. Each time the closure executes, it executes serially with respect to the other record zone completion blocks of the operation.
///
/// If you intend to use this closure to process results, set it before you execute the operation or submit the operation to a queue.
@property (nullable, copy, nonatomic) void (^perRecordZoneDeleteBlock)(CKRecordZoneID *recordZoneID, NSError * _Nullable error) API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0), watchos(8.0)) NS_REFINED_FOR_SWIFT;

/// The closure to execute after CloudKit modifies all of the record zones.
///
/// This property is a closure that returns no value and has the following parameters:
///
/// - The record zones that CloudKit saves.
/// - The IDs of the record zones that CloudKit deletes.
/// - If CloudKit can't modify any of the record zones, this parameter provides information about the failure; otherwise, it's `nil`.
///
/// The closure executes once, and represents your only opportunity to process the results.
///
/// The closure reports an error of type ``CKError/Code/partialFailure`` when it modifies only some of the record zones successfully. The <doc://com.apple.documentation/documentation/foundation/nserror/userinfo> dictionary of the error contains a ``CKPartialErrorsByItemIDKey`` key that has a dictionary as its value. The keys of the dictionary are the IDs of the record zones that the operation can't modify, and the corresponding values are errors that contain information about the failures.
///
/// If you intend to use this closure to process the results, set it before you execute the operation or submit the operation to a queue.
@property (nullable, copy, nonatomic) void (^modifyRecordZonesCompletionBlock)(NSArray<CKRecordZone *> * _Nullable savedRecordZones, NSArray<CKRecordZoneID *> * _Nullable deletedRecordZoneIDs, NSError * _Nullable operationError)
CK_SWIFT_DEPRECATED("Use modifyRecordZonesResultBlock instead", macos(10.10, 12.0), ios(8.0, 15.0), tvos(9.0, 15.0), watchos(3.0, 8.0));

@end

NS_HEADER_AUDIT_END(nullability, sendability)
