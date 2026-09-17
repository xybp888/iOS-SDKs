//
//  CKRecordZoneID.h
//  CloudKit
//
//  Copyright (c) 2014 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

#import <CloudKit/CKDefines.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

/// An object that uniquely identifies a record zone in a database.
///
/// Zones are a mechanism for grouping related records together. You create zone ID objects when you want to fetch an existing zone object or create a new zone with a specific name.
///
/// A record zone ID distinguishes one zone from another by a name string and the ID of the user who creates the zone. You should specify ASCII strings that don't exceed 255 characters. When creating your own record zone ID objects, you can use names that have more meaning to your app or to the user, providing each zone name is unique within the specified database. You should set the owner name to the current user name or the name of another user. Get the current user name from ``CKCurrentUserDefaultName`` or by calling ``CKContainer/fetchUserRecordID(completionHandler:)``.
///
/// When creating new record zones, make the name string in the record zone ID unique in the target database. Public databases don't support custom zones, and only the user who owns the database can create zones in private databases.
///
/// Don't create subclasses of this class.
///
/// ### Interacting with Record Zone IDs
///
/// After you create a record zone ID, interactions with it typically include:
///
/// - Creating a ``CKRecord/ID`` object so that you can fetch or create records in that zone.
/// - Retrieving an existing ``CKRecordZone`` object from the database.
///
/// You don't need to create a record zone ID to create a record zone. The ``CKRecordZone`` class has initialization methods that create a record zone ID using the name string you provide.
///
/// #### Creating Record Zone IDs for Records
///
/// To create a new record in a custom zone, create a record zone ID that specifies the zone name. Use the record zone ID to create a ``CKRecord/ID``, and then use the record ID to create the record.
///
/// #### Fetching a Record Zone Object from the Database
///
/// To fetch a record zone from the database, use a ``CKFetchRecordZonesOperation`` object or the ``CKDatabase/fetch(withRecordZoneID:completionHandler:)`` method of ``CKDatabase``. Both techniques accept a record zone ID that you provide and retrieve the corresponding record zone object asynchronously. If you use the operation object, you can retrieve multiple record zones at the same time.
API_AVAILABLE(macos(10.10), ios(8.0), watchos(3.0))
CK_SUBCLASSING_DEPRECATED // should not be subclassed, or Sendable may no longer apply
// NS_SWIFT_SENDABLE on macos(13.3), macCatalyst(16.4), ios(16.4), tvos(16.4), watchos(9.4)
@interface CKRecordZoneID : NSObject <NSSecureCoding, NSCopying>

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

/// Creates a record zone ID with the specified name and owner.
///
/// - Parameters:
///   - zoneName: The name that identifies the record zone. Zone names consist of up to 255 ASCII characters, and don't start with an underscore. To specify the default zone of the current database, use ``CKRecordZoneDefaultName-8mfij``. This parameter must not be `nil` or an empty string.
///   - ownerName: The user who creates the record zone. To specify the current user, use ``CKCurrentUserDefaultName``. If you provide `nil` or an empty string for this parameter, the method throws an exception.
///
/// - Returns: A new record zone ID.
- (instancetype)initWithZoneName:(NSString *)zoneName ownerName:(NSString *)ownerName NS_DESIGNATED_INITIALIZER;

/// The unique name of the record zone.
@property (readonly, copy, nonatomic) NSString *zoneName;

/// The ID of the user who owns the record zone.
@property (readonly, copy, nonatomic) NSString *ownerName;

@end

NS_HEADER_AUDIT_END(nullability, sendability)
