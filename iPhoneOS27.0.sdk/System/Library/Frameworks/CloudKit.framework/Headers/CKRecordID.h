//
//  CKRecordID.h
//  CloudKit
//
//  Copyright (c) 2014 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

#import <CloudKit/CKDefines.h>

@class CKRecordZoneID;

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

/// An object that uniquely identifies a record in a database.
///
/// A record ID object consists of a name string and a zone ID. The name string is an ASCII string that doesn't exceed 255 characters in length. When you create a record without specifying a record ID, the ID name string derives from a UUID and is, therefore, unique. When creating your own record ID objects, you can use names that have more meaning to your app or to the user, as long as each name is unique within the specified zone. For example, you might use a document name for the name string.
///
/// CloudKit uniques records by recordID within a specified database, but you can reuse record IDs in different databases. Each container has a public and a private database, and the private database is different for each unique user. This configuration provides for the reusing of record IDs in each user's private database, but ensures that only one record uses a specific record ID in the public database.
///
/// CloudKit generally creates record IDs when it first saves a new record, but you might manually instantiate instances of `CKRecordID` in  specific situations. For example, you must create an instance when saving a record in a zone other than the default zone. You also instantiate instances of `CKRecordID` when retrieving specific records from a database.
///
/// Don't subclass `CKRecordID`.
///
/// ### Interacting with Record IDs
///
/// After you create a `CKRecordID` object, interactions with that object typically involve creating a new record or retrieving an existing record from a database.
///
/// You might also use record IDs when you can't use a ``CKRecord/Reference`` object to refer to a record. References are only valid within a single zone of a database. To refer to objects outside of the current zone or database, save the strings in the record's `CKRecordID` and ``CKRecordZone/ID`` objects. When you want to retrieve the record later, use those strings to recreate the record and zone ID objects so that you can fetch the record.
///
/// #### Creating Record IDs for New Records
///
/// To assign a custom record ID to a new record, you must create the `CKRecordID` object first. You need to know the intended name and zone information for that record, which might also require creating a ``CKRecordZone/ID`` object. After creating the record ID object, initialize your new record using its ``CKRecord/init(recordType:recordID:)`` method.
///
/// #### Using Record IDs to Fetch Records
///
/// Use a record ID to fetch the corresponding ``CKRecord`` object from a database quickly. You perform the fetch operation using a ``CKFetchRecordsOperation`` object or the ``CKDatabase/fetch(withRecordID:completionHandler:)`` method of the ``CKDatabase`` class. In both cases, CloudKit returns the record asynchronously using the handler you provide.
API_AVAILABLE(macos(10.10), ios(8.0), watchos(3.0))
CK_SUBCLASSING_DEPRECATED // should not be subclassed, or Sendable may no longer apply
NS_SWIFT_SENDABLE
@interface CKRecordID : NSObject <NSSecureCoding, NSCopying>

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

/// Creates a new record ID with the specified name in the default zone.
///
/// - Parameters:
///   - recordName: The name that identifies the record. The string must contain only ASCII characters, must not exceed 255 characters, and must not start with an underscore. If you specify an empty string for this parameter, the method throws an exception.
///
/// - Returns: An initialized record ID object.
///
/// Use this method when you're creating or searching for records in the default zone.
- (instancetype)initWithRecordName:(NSString *)recordName;

/// Creates a new record ID with the specified name and zone information.
///
/// - Parameters:
///   - recordName: The name that identifies the record. The string must contain only ASCII characters, must not exceed 255 characters, and must not start with an underscore. If you specify an empty string for this parameter, the method throws an exception.
///   - zoneID: The ID of the zone where you want to store the record. This parameter must not be `nil`.
///
/// - Returns: An initialized record ID object.
///
/// Use this method when you create or search for records in a zone other than the default zone. The value in the `zoneID` parameter must represent a zone that already exists in the database. If the record zone doesn't exist, save the corresponding ``CKRecordZone`` object to the database before attempting to save any ``CKRecord`` objects in that zone.
- (instancetype)initWithRecordName:(NSString *)recordName zoneID:(CKRecordZoneID *)zoneID NS_DESIGNATED_INITIALIZER;

/// The unique name of the record.
///
/// For share records that manage a shared record zone, this property's value is always ``CKRecordNameZoneWideShare``.
@property (readonly, copy, nonatomic) NSString *recordName;

/// The ID of the zone that contains the record.
@property (readonly, copy, nonatomic) CKRecordZoneID *zoneID;

@end

NS_HEADER_AUDIT_END(nullability, sendability)
