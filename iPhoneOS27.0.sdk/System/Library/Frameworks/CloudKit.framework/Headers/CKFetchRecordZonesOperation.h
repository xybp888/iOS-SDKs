//
//  CKFetchRecordZonesOperation.h
//  CloudKit
//
//  Copyright (c) 2014 Apple Inc. All rights reserved.
//

#import <CloudKit/CKDatabaseOperation.h>

@class CKRecordZone, CKRecordZoneID;

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

/// An operation for retrieving record zones from a database.
///
/// Use this operation object to fetch record zones so that you can ascertain their capabilities.
///
/// If you assign a handler to the <doc://com.apple.documentation/documentation/foundation/operation/completionblock> property of the operation, CloudKit calls it after the operation executes and returns its results. You can use the handler to perform any housekeeping tasks that relate to the operation, but don't use it to process the results of the operation. The handler you specify should manage any failures, whether due to an error or an explicit cancellation.
API_AVAILABLE(macos(10.10), ios(8.0), watchos(3.0))
@interface CKFetchRecordZonesOperation : CKDatabaseOperation

/// Returns an operation for fetching all record zones in the current database.
///
/// Assign a value to the ``CKFetchRecordZonesOperation/fetchRecordZonesCompletionBlock`` property of the operation that this method returns so that you can process the results.
+ (instancetype)fetchAllRecordZonesOperation;

/// Creates an empty fetch zones operation.
///
/// You must set the ``CKFetchRecordZonesOperation/recordZoneIDs`` property before you execute the operation.
///
/// After creating the operation, assign a value to the ``CKFetchRecordZonesOperation/fetchRecordZonesCompletionBlock`` property so you can process the results.
- (instancetype)init NS_DESIGNATED_INITIALIZER;

/// Creates an operation for fetching the specified record zones.
///
/// - Parameters:
///   - zoneIDs: An array of ``CKRecordZone/ID`` objects that represents the zones you want to retrieve. If you provide an empty array, you must set the ``CKFetchRecordZonesOperation/recordZoneIDs`` property before you execute the operation.
///
/// After creating the operation, assign a value to the ``CKFetchRecordZonesOperation/fetchRecordZonesCompletionBlock`` property so you can process the results.
- (instancetype)initWithRecordZoneIDs:(NSArray<CKRecordZoneID *> *)zoneIDs;

/// The IDs of the record zones to retrieve.
///
/// Use this property to view or change the IDs of the record zones you want to retrieve. If you intend to change the value of this property, do so before you execute the operation or submit the operation to a queue.
///
/// If you use the operation that ``CKFetchRecordZonesOperation/fetchAllRecordZonesOperation()`` returns, CloudKit ignores the contents of this property and sets its value to `nil`.
@property (nullable, copy, nonatomic) NSArray<CKRecordZoneID *> *recordZoneIDs;

/// The closure to execute as the operation fetches individual record zones.
///
/// The closure returns no value and takes the following parameters:
///
/// - The ID of the record zone.
/// - The record zone, or `nil` if CloudKit can't fetch the record zone.
/// - If CloudKit can't fetch the record zone, this parameter provides information about the failure; otherwise, it's `nil`.
///
/// The operation executes this closure once for each record zone ID in the ``CKFetchRecordZonesOperation/recordZoneIDs`` property. Each time the closure executes, it executes serially with respect to the other closures of the operation.
///
/// If you intend to use this closure to process results, set it before you execute the operation or submit the operation to a queue.
@property (nullable, copy, nonatomic) void (^perRecordZoneCompletionBlock)(CKRecordZoneID *zoneID, CKRecordZone * _Nullable recordZone, NSError * _Nullable error) API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0), watchos(8.0)) NS_REFINED_FOR_SWIFT;


/// The closure to execute after CloudKit retrieves all of the record zones.
///
/// This property is a closure that returns no value and has the following parameters:
///
/// - A dictionary that maps the zone IDs you request to the results. The keys in the dictionary are ``CKRecordZone/ID`` objects, and the values are the corresponding ``CKRecordZone`` objects that CloudKit returns.
/// - If CloudKit can't retrieve any of the record zones, an error that provides information about the failure; otherwise, `nil`.
///
/// The operation executes the closure only once, and it's your only chance to process the results. You must provide a closure capable of executing on a background thread, so any tasks that require access to the main thread must redirect accordingly.
///
/// The closure reports an error of type ``CKError/Code/partialFailure`` when it retrieves only some of the record zones successfully. The <doc://com.apple.documentation/documentation/foundation/nserror/userinfo> dictionary of the error contains a ``CKPartialErrorsByItemIDKey`` key that has a dictionary as its value. The keys of the dictionary are the IDs of the record zones that the operation can't retrieve, and the corresponding values are errors that contain information about the failures.
///
/// If you intend to use this closure to process results, set it before you execute the operation or submit the operation to a queue.
@property (nullable, copy, nonatomic) void (^fetchRecordZonesCompletionBlock)(NSDictionary<CKRecordZoneID *, CKRecordZone *> * _Nullable recordZonesByZoneID, NSError * _Nullable operationError)
CK_SWIFT_DEPRECATED("Use fetchRecordZonesResultBlock instead", macos(10.10, 12.0), ios(8.0, 15.0), tvos(9.0, 15.0), watchos(3.0, 8.0));

@end

NS_HEADER_AUDIT_END(nullability, sendability)
