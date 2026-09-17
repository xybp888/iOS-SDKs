//
//  CKQueryOperation.h
//  CloudKit
//
//  Copyright (c) 2014 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

#import <CloudKit/CKDatabaseOperation.h>
#import <CloudKit/CKDefines.h>
#import <CloudKit/CKRecord.h>

@class CKQuery, CKRecord, CKRecordZoneID;

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

/// An object that marks the stopping point for a query and the starting point for retrieving the remaining results.
///
/// You don't create instances of this class yourself. When fetching records using a query operation, if the number of results exceeds the limit for the query, CloudKit provides a cursor. Use that cursor to create a new instance of ``CKQueryOperation`` and retrieve the next batch of results for the same query.
///
/// For information about how to use a ``CKQueryOperation/Cursor`` object, see ``CKQueryOperation``.
API_AVAILABLE(macos(10.10), ios(8.0), watchos(3.0))
CK_SUBCLASSING_DEPRECATED // should not be subclassed, or Sendable may no longer apply
// NS_SWIFT_SENDABLE on macos(13.3), macCatalyst(16.4), ios(16.4), tvos(16.4), watchos(9.4)
@interface CKQueryCursor : NSObject <NSCopying, NSSecureCoding>
- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;
@end

/// A constant value that represents the maximum number of results CloudKit retrieves.
///
/// The value of this constant doesn't correspond to the actual number of records. CloudKit dynamically determines the actual number according to various conditions at runtime.
///
/// This constant is the ``CKQueryOperation/resultsLimit`` property's default value.
CK_EXTERN const NSUInteger CKQueryOperationMaximumResults API_AVAILABLE(macos(10.10), ios(8.0), watchos(3.0));

/// An operation for executing queries in a database.
///
/// A `CKQueryOperation` object is a concrete operation that you can use to execute queries. A query operation applies query parameters to the specified database and record zone, delivering any matching records asynchronously to the handlers that you provide.
///
/// To perform a new search:
///
/// 1. Initialize a `CKQueryOperation` object with a ``CKQuery`` object that contains the search criteria and sorting information for the records you want.
/// 2. Assign a handler to the ``queryCompletionBlock`` property so that you can process the results and execute the operation.
///
///    If the search yields many records, the operation object may deliver a portion of the total results to your blocks immediately, along with a cursor for obtaining the remaining records. Use the cursor to initialize and execute a separate `CKQueryOperation` instance when you're ready to process the next batch of results.
/// 3. Optionally, configure the results by specifying values for the ``resultsLimit`` and ``desiredKeys-4a6vy`` properties.
/// 4. Pass the query operation object to the ``CKDatabase/add(_:)`` method of the target database to execute the operation.
///
/// CloudKit restricts queries to the records in a single record zone. For new queries, you specify the zone when you initialize the query operation object. For cursor-based queries, the cursor contains the zone information. To search for records in multiple zones, you must create a separate `CKQueryOperation` object for each zone you want to search, although you can initialize each of them with the same ``CKQuery`` object.
///
/// If you assign a handler to the operation's <doc://com.apple.documentation/documentation/foundation/operation/completionblock> property, the operation calls it after it executes and returns any results. Use a handler to perform housekeeping tasks for the operation, but don't use it to process the results of the operation. The handler you provide should manage any failures, whether due to an error or an explicit cancellation.
API_AVAILABLE(macos(10.10), ios(8.0), watchos(3.0))
@interface CKQueryOperation : CKDatabaseOperation

/// Creates an empty query operation.
- (instancetype)init NS_DESIGNATED_INITIALIZER;

/// Creates an operation that searches for records in the specified record zone.
///
/// - Parameters:
///   - query: The query for the search.
///
/// You can use the operation that this method returns only once to perform a search, but you can reuse the query that you provide. During execution, the operation performs a new search and returns the first batch of results. If there are more results available, you must create a separate query object using the provided cursor object.
- (instancetype)initWithQuery:(CKQuery *)query;

/// Creates an operation with additional results from a previous search.
///
/// - Parameters:
///   - cursor: The cursor that identifies the previous search. CloudKit passes this value to the completion handler of the previous search. For more information, see the ``CKQueryOperation/queryCompletionBlock`` property.
///
/// Use this method to create an operation that retrieves the next batch of results from a previous search. When executing searches for a cursor, don't cache cursors for a long time before using them. A cursor isn't a snapshot of the previous search results; it stores a relative offset into the results list. An operation that you create from a cursor performs a new search, sorts the new set of results, and uses the previous offset value to determine where the next batch of results starts.
- (instancetype)initWithCursor:(CKQueryCursor *)cursor;

/// The query for the search.
///
/// The initial value of this property is the query that you provide to the ``CKQueryOperation/init(query:)`` method. When the value in the ``CKQueryOperation/cursor`` property is `nil`, the operation uses this property's value to execute a new search and return its results to your completion handler. If ``CKQueryOperation/cursor`` isn't `nil`, the operation uses the cursor instead.
///
/// If you intend to specify or change the value of this property, do so before you execute the operation or submit it to a queue.
@property (nullable, copy, nonatomic) CKQuery *query;

/// The cursor for continuing the search.
///
/// The initial value of this property is the cursor that you provide to the ``CKQueryOperation/init(cursor:)`` method. When you use a cursor, the operation ignores the contents of the ``CKQueryOperation/query`` property. This property's value is an opaque value that CloudKit provides. For more information, see the ``CKQueryOperation/queryCompletionBlock`` property.
///
/// If you intend to specify or change the value in this property, do so before you execute the operation or submit it to a queue.
@property (nullable, copy, nonatomic) CKQueryCursor *cursor;

/// The ID of the record zone that contains the records to search.
///
/// The value of this property limits the scope of the search to only the records in the specified record zone. If you don't specify a record zone, the search includes all record zones.
///
/// When you create an operation using the ``CKQueryOperation/init(cursor:)`` method, this property's value is `nil` and CloudKit ignores any changes that you make to it. When the operation executes, the cursor provides the record zone information from the original search that provides the cursor.
@property (nullable, copy, nonatomic) CKRecordZoneID *zoneID;

/// The maximum number of records to return at one time.
///
/// For most queries, leave the value of this property as the default value, which is the ``CKQueryOperation/maximumResults`` constant. When using that value, CloudKit returns as many records as possible while minimizing delays in receiving those records. If you want to process a fixed number of results, change the value of this property accordingly.
@property (assign, nonatomic) NSUInteger resultsLimit;

/// The fields of the records to fetch.
///
/// Use this property to limit the amount of data that CloudKit returns for each record. When CloudKit returns a record, it only includes fields with names that match one of the keys in this property. The property's default value is `nil`, which instructs CloudKit to return all of a record's keys.
///
/// If you intend to specify a value other than `nil`, do so before you execute the operation or add the operation to a queue.
@property (nullable, copy, nonatomic) NSArray<CKRecordFieldKey> *desiredKeys;

/// The closure to execute when a record becomes available.
///
/// The closure returns no value and takes the following parameter:
///
/// - A single record that matches the search criteria.
///
/// After identifying and sorting the records, the query operation executes this closure once for each of the result's records. The closure executes serially with respect to all other closures of the operation, so you can expect only one closure at a time to execute for this operation.
///
/// Set the property's value before you execute the operation or submit it to a queue.
///
/// - Warning: Query indexes update asynchronously so they aren't always current. If you query for records that you recently changed and don't allow enough time for those changes to process, the query's results may be incorrect. The results may not contain the correct records, and the records may be out of order.
@property (nullable, copy, nonatomic) void (^recordFetchedBlock)(CKRecord *record) API_DEPRECATED("Use recordMatchedBlock instead, which surfaces per-record errors", macos(10.10, 12.0), ios(8.0, 15.0), tvos(9.0, 15.0), watchos(3.0, 8.0));

/// The closure to execute when a record match is available.
///
/// The closure returns no value and takes the following parameters:
///
/// - The ID of the record.
/// - The record, or `nil` if CloudKit can't retrieve the record.
/// - If CloudKit can't retrieve the record, an error that provides information about the failure; otherwise, `nil`.
///
/// After identifying and sorting the records, the query operation executes this closure once for each of the result's records. The closure executes serially with respect to all other closures of the operation, so you can expect only one closure at a time to execute for this operation.
///
/// Set the property's value before you execute the operation or submit it to a queue.
///
/// - Warning: Query indexes update asynchronously so they aren't always current. If you query for records that you recently changed and don't allow enough time for those changes to process, the query's results may be incorrect. The results may not contain the correct records, and the records may be out of order.
@property (nullable, copy, nonatomic) void (^recordMatchedBlock)(CKRecordID *recordID, CKRecord * _Nullable record, NSError * _Nullable error) API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0), watchos(8.0)) NS_REFINED_FOR_SWIFT;

/// The closure to execute after CloudKit retrieves all of the records.
///
/// The closure returns no value and takes the following parameters:
///
/// - A cursor that indicates there are more results to fetch, or `nil` if there are no additional results. Use the cursor to create a new query operation when you're ready to retrieve the next batch of results.
/// - An error that contains information about a problem, or `nil` if CloudKit retrieves the results successfully.
///
/// This closure executes only once, and represents your final opportunity to process the results. It executes after all of the individual record fetch closures. The closure executes serially with respect to the other closures of the operation.
///
/// If the number of records that the operation intends to return exceeds ``CKQueryOperation/resultsLimit``, the operation provides a cursor that you can use to retrieve the next batch of results. You must create a separate operation using the cursor to fetch the next batch of results.
///
/// Update the value of this property before you execute the operation or submit it to a queue.
@property (nullable, copy, nonatomic) void (^queryCompletionBlock)(CKQueryCursor * _Nullable cursor, NSError * _Nullable operationError)
CK_SWIFT_DEPRECATED("Use queryResultBlock instead", macos(10.10, 12.0), ios(8.0, 15.0), tvos(9.0, 15.0), watchos(3.0, 8.0));

@end

NS_HEADER_AUDIT_END(nullability, sendability)
