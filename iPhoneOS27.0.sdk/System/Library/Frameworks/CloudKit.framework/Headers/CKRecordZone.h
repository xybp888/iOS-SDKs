//
//  CKRecordZone.h
//  CloudKit
//
//  Copyright (c) 2014 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

#import <CloudKit/CKDefines.h>

@class CKRecordZoneID, CKReference;

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

/// The capabilities that a record zone supports.
typedef NS_OPTIONS(NSUInteger, CKRecordZoneCapabilities) {
    /// A capability for fetching only the changed records from a zone.
    ///
    /// This capability makes the creation of offline caches more efficient. Instead of fetching the entire record every time, use ``CKFetchRecordZoneChangesOperation`` to fetch only the changed values, and use the data it returns to update your cache. This minimizes the amount of data you receive from the server.
    CKRecordZoneCapabilityFetchChanges   = 1 << 0,

    /// A capability that allows atomic changes of multiple records.
    ///
    /// When you use a ``CKModifyRecordsOperation`` object to save records, if the server is unable to save the changes for one record, it doesn't save the changes for any of the records. Combining this capability with the ``CKModifyRecordsOperation/RecordSavePolicy/ifServerRecordUnchanged`` policy of the operation object prevents your app from overwriting changes to a group of records if one or more of the records on the server has recent changes.
    CKRecordZoneCapabilityAtomic         = 1 << 1,

    /// A capability for sharing a specific hierarchy of records.
    ///
    /// CloudKit allows you to share record hierarchies from custom record zones that you create in the user's private database. For more information, see <doc:shared-records>.
    CKRecordZoneCapabilitySharing        API_AVAILABLE(macos(10.12), ios(10.0), tvos(10.0)) = 1 << 2,

    /// A capability for sharing the entire contents of a record zone.
    ///
    /// CloudKit allows you to share custom record zones that you create in the user's private database. For more information, see <doc:shared-records>.
    CKRecordZoneCapabilityZoneWideSharing API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0), watchos(8.0)) = 1 << 3,
} API_AVAILABLE(macos(10.10), ios(8.0), watchos(3.0));

API_AVAILABLE(macos(26.0), ios(26.0), tvos(26.0), watchos(26.0), visionos(26.0))
typedef NS_ENUM(NSInteger, CKRecordZoneEncryptionScope) {
    /// Zone uses per-record encryption keys for any encrypted values on a record or share.
    ///
    /// This is the default encryption scope for a record zone.
    CKRecordZoneEncryptionScopePerRecord,

    /// Zone uses per-zone encryption keys for encrypted values across all records and the zone-wide share, if present.
    ///
    /// This is an optional optimization that can reduce the overall storage used by encryption keys in a zone.
    /// Note that:
    /// - Record zones using per-zone encryption only support zone-wide sharing.
    /// - Encryption scope can only be assigned at zone creation and cannot be changed for the lifetime of the zone.
    /// - The server does not return zones using per-zone encryption to device OS versions older than the corresponding API availability version.
    /// - An older OS trying to overwrite an existing zone using per-zone encryption due to a naming collision results in a `.serverRejectedRequest` error.
    /// - On device OS upgrade, your application is responsible for fetching database changes via `CKFetchDatabaseChangesOperation` with a nil sync token to verify it has
    /// received all the zones available to it from the server.
    CKRecordZoneEncryptionScopePerZone,
};

/// The default record zone's name.
///
/// Use this value when you need to refer to the default zone by name, such as when creating a zone ID. The default zone has no special capabilities.
CK_EXTERN NSString * const CKRecordZoneDefaultName API_AVAILABLE(macos(10.10), ios(8.0), watchos(3.0));

/// A database partition that contains related records.
///
/// Zones are an important part of how you organize your data. The public and private databases each have a single default zone. In the private database, you can use ``CKRecordZone`` objects to create additional custom zones as necessary. Use custom zones to arrange and encapsulate groups of related records in the private database. Custom zones support other capabilities too, such as the ability to write multiple records as a single atomic transaction.
///
/// Treat each custom zone as a single unit of data that is separate from every other zone in the database. You can add records inside the zone. You can also create links between the records inside a zone by using the ``CKRecord/Reference`` class. However, the ``CKRecord/Reference`` class doesn't support cross-zone linking, so each reference object must point to a record in the same zone as the current record.
///
/// Use the ``CKRecordZone`` class as-is and don't subclass it.
///
/// ### Creating a Custom Record Zone
///
/// Generally, you use instances of this class to create and manage custom zones. Although you can use this class to retrieve a database's default zone, most operations act on records in the default zone by default, so you rarely need to specify it explicitly.
///
/// To create a custom zone, use ``CKRecordZone`` to create the zone object, and then save that zone to the user's private database using a ``CKModifyRecordZonesOperation`` object. You can't save any records in the zone until you save it to the database. When creating records, explicitly specify the zone ID if you want the records to reside in a specific zone; otherwise, they save to the default zone. You can't create custom zones in a public database.
///
/// After creating a `CKRecordZone` object and saving it to the database, you don't interact with the object much. Instead, most interactions occur with its corresponding ``ID`` object, which you use to refer to the zone when creating records.
API_AVAILABLE(macos(10.10), ios(8.0), watchos(3.0))
CK_SUBCLASSING_DEPRECATED
// NS_SWIFT_SENDABLE on macos(14.0), ios(17.0), tvos(17.0), watchos(10.0)
@interface CKRecordZone : NSObject <NSSecureCoding, NSCopying>

/// Returns the default record zone.
///
/// Always use this method to retrieve the default zone for a database. You can use the returned object to specify the default zone for either the public or private database of a container. You don't need to save the returned zone object before using it. The owner of the zone is ``CKOwnerDefaultName``, which corresponds to the current user.
///
/// The default zone of a database is a convenient place to store and access records. If you don't explicitly assign a zone to a record, CloudKit puts the record in the default zone.
///
/// The disadvantage of using the default zone for storing records is that it doesn't have any special capabilities. You can't save a group of records to iCloud atomically in the default zone. Similarly, you can't use a ``CKFetchRecordChangesOperation`` object on records in the default zone.
+ (CKRecordZone *)defaultRecordZone;

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

/// Creates a record zone object with the specified zone name.
///
/// - Parameters:
///   - zoneName: The name of the new zone. Zone names inside a user's private database are unique, consist of up to 255 ASCII characters, and don't start with an underscore. One way to satisfy the uniqueness of zone names is to create a string from a Universally Unique Identifier (UUID), but you can also use other techniques.
///
///     If this parameter is `nil` or is an empty string, the method throws an exception.
///
/// - Returns: The new custom zone.
///
/// Use this method to create a new record zone. The new zone has the name you provide and the zone's owner is the current user. After creating the zone, save it to the server using a ``CKModifyRecordZonesOperation`` object or the ``CKDatabase/save(_:completionHandler:)-32ffr`` method of ``CKDatabase``. You must save the zone to the server before you attempt to save any records to that zone.
///
/// Don't use this method to create a `CKRecordZone` object that corresponds to a zone that already exists in the database. If the zone exists, fetch it using a ``CKFetchRecordZonesOperation`` object or the ``CKDatabase/fetch(withRecordZoneID:completionHandler:)`` method of ``CKDatabase``.
- (instancetype)initWithZoneName:(NSString *)zoneName;

/// Creates a record zone object with the specified zone ID.
///
/// - Parameters:
///   - zoneID: The ID for the new zone. This parameter must not be `nil`.
///
/// - Returns: The custom record zone.
///
/// Use this method when you want to create a new record zone from the information in a zone ID. After creating the zone, save it to the server using a ``CKModifyRecordZonesOperation`` object or the ``CKDatabase/save(_:completionHandler:)-32ffr`` method of ``CKDatabase``.
///
/// Don't use this method to create a ``CKRecordZone`` object that corresponds to a zone that already exists in the database. If the zone exists, fetch it using a ``CKFetchRecordZonesOperation`` object or the ``CKDatabase/fetch(withRecordZoneID:completionHandler:)`` method of ``CKDatabase``.
- (instancetype)initWithZoneID:(CKRecordZoneID *)zoneID;

/// The unique ID of the zone.
///
/// The zone ID contains the name of the zone and the name of the user who owns the zone. Use this property to access both of those values.
@property (readonly, copy) CKRecordZoneID *zoneID;

/// The capabilities that the zone supports.
///
/// The server determines the capabilities of the zone and sets the value of this property when you save the record zone. Always check this property before performing tasks that require a specific capability.
///
/// Default zones don't support any special capabilities. Custom zones in a private database support the options that ``CKRecordZone/Capabilities`` provides.
@property (readonly, assign) CKRecordZoneCapabilities capabilities;

/// A reference to the record zone's share record.
///
/// CloudKit sets this property only for fetched record zones that contain a share record; otherwise, it's `nil`.
///
/// To share a record zone, create a share record using the ``CKShare/init(recordZoneID:)`` method and then save it to the server. Shared record zones must have the ``CKRecordZone/Capabilities/zoneWideSharing`` capability, which CloudKit enables by default for new custom record zones in the user's private database.
///
/// A record zone, and the records it contains, can take part in only a single share. CloudKit returns an error if you attempt to share an already-shared record zone, or if that record zone contains previously shared records.
///
/// Record zone sharing errors include the following:
///
/// - ``CKError/Code/serverRecordChanged``, which CloudKit returns if you try to share an already-shared record zone.
/// - ``CKError/Code/serverRejectedRequest``, which CloudKit returns if you try to share a record hierarchy from an already-shared record zone.
/// - ``CKError/Code/invalidArguments``, which CloudKit returns if you try to share a record zone that contains one or more shared hierarchies.
@property (nullable, readonly, copy) CKReference *share API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0), watchos(8.0));

/// The encryption scope determines the granularity at which CloudKit stores encryption keys within the zone.
///
/// Zone encryption scope defaults to `CKRecordZoneEncryptionScopePerRecord` and can only be modified before zone creation. Attempting to change the encryption
/// scope of an existing zone is invalid and results in an error.
///
/// Zones using `CKRecordZoneEncryptionScopePerZone` can only use zone-wide sharing and are not compatible with older device OS versions. Refer to `CKRecordZoneEncryptionScope` for more info.
@property (assign) CKRecordZoneEncryptionScope encryptionScope API_AVAILABLE(macos(26.0), ios(26.0), tvos(26.0), watchos(26.0), visionos(26.0));

@end

NS_HEADER_AUDIT_END(nullability, sendability)
