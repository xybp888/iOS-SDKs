//
//  CKRecord.h
//  CloudKit
//
//  Copyright (c) 2014 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

#import <CloudKit/CKAsset.h>
#import <CloudKit/CKDefines.h>
#import <CloudKit/CKReference.h>

#import <CoreLocation/CLLocation.h>

@class CKRecordID, CKRecordZoneID;

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

/// A data type that CloudKit requires for record types.
typedef NSString *CKRecordType;

/// A data type that CloudKit requires for record field names.
typedef NSString *CKRecordFieldKey;

/// The system type that identifies a user record.
///
/// CloudKit automatically creates a user record for each unique user of the app. User records are empty initially. You can add data to the user record using the same rules that apply for all records. Specifically, you must specify a consistent type of data for a particular field name in all user records. However, you can't create new user records using this record type and you can't query for records of this type. To locate user records, you must know the ID of the user record or use the methods that CKContainer provides to discover user records.
CK_EXTERN CKRecordType const CKRecordTypeUserRecord API_AVAILABLE(macos(10.10), ios(8.0), watchos(3.0));

/// A key constant that a record uses for its CKRecord.recordID.
CK_EXTERN CKRecordFieldKey const CKRecordRecordIDKey API_AVAILABLE(macos(10.10), ios(8.0), watchos(3.0)) NS_REFINED_FOR_SWIFT;

/// A key constant that a record uses for its CKRecord.creatorUserRecordID.
CK_EXTERN CKRecordFieldKey const CKRecordCreatorUserRecordIDKey API_AVAILABLE(macos(10.10), ios(8.0), watchos(3.0)) NS_REFINED_FOR_SWIFT;

/// A key constant that a record uses for its CKRecord.creationDate.
CK_EXTERN CKRecordFieldKey const CKRecordCreationDateKey API_AVAILABLE(macos(10.10), ios(8.0), watchos(3.0)) NS_REFINED_FOR_SWIFT;

/// A key constant that a record uses for its CKRecord.lastModifiedUserRecordID.
CK_EXTERN CKRecordFieldKey const CKRecordLastModifiedUserRecordIDKey API_AVAILABLE(macos(10.10), ios(8.0), watchos(3.0)) NS_REFINED_FOR_SWIFT;

/// A key constant that a record uses for its CKRecord.modificationDate.
CK_EXTERN CKRecordFieldKey const CKRecordModificationDateKey API_AVAILABLE(macos(10.10), ios(8.0), watchos(3.0)) NS_REFINED_FOR_SWIFT;

/// The key constant that a record uses for its CKRecord.parent.
CK_EXTERN CKRecordFieldKey const CKRecordParentKey API_AVAILABLE(macos(10.12), ios(10.0), tvos(10.0), watchos(3.0));

/// The key constant that a record uses for its CKRecord.share.
CK_EXTERN CKRecordFieldKey const CKRecordShareKey API_AVAILABLE(macos(10.12), ios(10.0), tvos(10.0), watchos(3.0));

/// The protocol that provides strong type-checking for objects that the CloudKit framework stores on the server.
///
/// CloudKit supports the following classes that adopt this protocol:
///
/// - <doc://com.apple.documentation/documentation/foundation/nsstring>
/// - <doc://com.apple.documentation/documentation/foundation/nsnumber>
/// - <doc://com.apple.documentation/documentation/foundation/nsarray>
/// - <doc://com.apple.documentation/documentation/foundation/nsdate>
/// - <doc://com.apple.documentation/documentation/foundation/nsdata>
/// - ``CKRecord/Reference``
/// - ``CKAsset``
/// - <doc://com.apple.documentation/documentation/corelocation/cllocation>
///
/// Don't adopt this protocol in your custom classes. CloudKit doesn't support writing custom data types to the server. Attempting to do so results in an error.
@protocol CKRecordValue <NSObject>
@end

/// A collection of key-value pairs that store your app's data.
///
/// Records are the fundamental objects that manage data in CloudKit. You can define any number of record types for your app, with each record type corresponding to a different type of information. Within a record type, you then define one or more fields, each with a name and a value. Records can contain simple data types, such as strings and numbers, or more complex types, such as geographic locations or pointers to other records.
///
/// An important step in using CloudKit is defining the record types your app supports. A new record object doesn't contain any keys or values. During development, you can add new keys and values at any time. The first time you set a value for a key and save the record, the server associates that type with the key for all records of the same type. The `CKRecord` class doesn't impose these type constraints or do any local validation of a record's contents. CloudKit enforces these constraints when you save the records.
///
/// - Note: The ability to add new keys is only possible during development. When you deploy to a production environment, the server returns an error if you try to specify an unknown record type or try to save a record that contains unknown keys.
///
/// Although records behave like dictionaries, there are limitations to the types of values you can assign to keys. The following are the object types that the `CKRecord` class supports. Attempting to specify objects of any other type results in failure. Fields of all types are searchable unless otherwise noted.
///
/// ### Supported Data Types
///
/// `CKRecord` fields support the following data types:
///
/// - term <doc://com.apple.documentation/documentation/foundation/nsstring>: Stores relatively small amounts of text. Although strings themselves can be any length, use a ``CKAsset`` to store large amounts of text.
/// - term <doc://com.apple.documentation/documentation/foundation/nsnumber>: Stores any numerical information, including integers and floating-point numbers.
/// - term <doc://com.apple.documentation/documentation/foundation/nsdata>: Stores arbitrary bytes of data. A typical use for data objects is to map the bytes that they contain to a `struct`. Don't use data objects for storing large binary data files; use a ``CKAsset`` instead. Data fields aren't searchable.
/// - term <doc://com.apple.documentation/documentation/foundation/nsdate>: Stores day and time information in an accessible form.
/// - term <doc://com.apple.documentation/documentation/foundation/nsarray>: Stores one or more objects of any other type in this table. You can store arrays of strings, arrays of numbers, arrays of references, and so on.
/// - term <doc://com.apple.documentation/documentation/corelocation/cllocation>: Stores geographic coordinate data. You use locations in conjunction with the Core Location framework and any other services that handle location information.
/// - term ``CKAsset``: Associates a disk-based file with the record. Although assets have a close association with records, you manage them separately. For more information about using assets, see ``CKAsset``.
/// - term ``Reference``: Creates a link to a related record. A reference stores the ID of the target record. The advantage of using a reference instead of storing the ID as a string is that references can initiate cascade deletions of dependent records. The disadvantage is that references can only link between records in the same record zone. For more information, see ``Reference``.
///
/// - Important: To ensure the speed of fetching and saving records, the data that a record stores must not exceed 1 MB. Assets don't count toward this limit, but all other data types do.
///
/// ### Defining Records
///
/// The process for defining your record types depends entirely on your app and the data you're trying to represent. It's best to design records that encapsulate data for one unit of information. For example, you might use one record type to store an employee's name, job title, and date of hire, and use a separate record type to store the employee's address information. Using different record types lets you manage, manipulate, and validate the two types of information separately.
///
/// Use fields that contain ``Reference`` objects to establish relationships between different types of records. After you define your record types, use the iCloud Dashboard to set them up. During development, you can also create new record types programmatically.
///
/// ### Indexing the Fields of a Record
///
/// Indexes make it possible to search the contents of your records efficiently. During development, the server indexes all fields with data types it can use in the predicate of a query. This automatic indexing makes it easier to experiment with queries during development, but the indexes require space in a database, and require time to generate and maintain.
///
/// To manage the indexing behavior of your records in the production environment, use CloudKit Dashboard. When migrating your schema from the development environment to the production environment, enable indexing only for the fields that your app uses in queries, and disable it for all other fields.
///
/// ### Customizing Records
///
/// Use this class as-is to manage data coming from or going to the server, and don't subclass it.
///
/// ### Storing Records Locally
///
/// If you store records in a local database, use the ``encodeSystemFields(with:)`` method to encode and store the record's metadata. The metadata contains the record ID and the change tag, which you need later to sync records in a local database with those in CloudKit.
API_AVAILABLE(macos(10.10), ios(8.0), watchos(3.0))
// This class should not be subclassed. If it is, Sendable may no longer apply.
// NS_SWIFT_SENDABLE on macos(14.0), ios(17.0), tvos(17.0), watchos(10.0)
@interface CKRecord : NSObject <NSSecureCoding, NSCopying>

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

/// Creates a new record of the specified type.
///
/// - Parameters:
///   - recordType: A string that represents the type of record that you want to create. You can't change the record type after initialization. You define the record types that your app supports and use them to distinguish between records with different types of data. This parameter must not be `nil` or contain an empty string.
///
///     A record type must consist of one or more alphanumeric characters and must start with a letter. CloudKit permits the use of underscores, but not spaces.
///
/// - Returns: An initialized record object.
///
/// Use this method to initialize a new record object in the default zone of the database. The newly created record contains no data in any of its fields and receives a unique ID.
///
/// ```objc
/// // Create a new record of type "employee".
/// CKRecord* myRecord = [[CKRecord alloc] initWithRecordType:@"employee"];
/// ```
///
/// New records exist only in memory until you explicitly save them to iCloud. In addition, new records are sparse by default and have no values for the fields you define. Until you set the value of a key explicitly, getting the value of a key in a new record returns `nil`. Even though a record has an associated type, CloudKit ignores the type information until you save the record.
///
/// Save the record using a ``CKModifyRecordsOperation`` object or by using the ``CKDatabase/save(_:completionHandler:)-3tatz`` method of ``CKDatabase`` to transfer the record's contents to the server.
- (instancetype)initWithRecordType:(CKRecordType)recordType;

/// Creates a record using an ID that you provide.
///
/// - Parameters:
///   - recordType: A string that represents the type of record that you want to create. You can't change the record type after initialization. You define the record types that your app supports and use them to distinguish between records with different types of data. This parameter must not be `nil` or contain an empty string.
///
///     A record type must consist of one or more alphanumeric characters and must start with a letter. CloudKit permits the use of underscores, but not spaces.
///   - recordID: The ID to assign to the record. When creating the ID, you can specify the zone where you want to store the record. You should provide a value that is unique across all records and you may not provide `nil`.
///
/// - Returns: An initialized record object.
///
/// Use this method to initialize a new record object with the specified ID. The newly created record contains no data.
///
/// Upon creation, record objects exist only in memory on the local device. Save the record using a ``CKModifyRecordsOperation`` object or by using the ``CKDatabase/save(_:completionHandler:)-3tatz`` method of ``CKDatabase`` to transfer the record's contents to the server.
- (instancetype)initWithRecordType:(CKRecordType)recordType recordID:(CKRecordID *)recordID;

/// Creates a record in the specified zone.
///
/// - Parameters:
///   - recordType: A string that represents the type of record that you want to create. You can't change the record type after initialization. You define the record types that your app supports and use them to distinguish between records with different types of data. This parameter must not be `nil` or contain an empty string.
///
///     A record type must consist of one or more alphanumeric characters and must start with a letter. CloudKit permits the use of underscores, but not spaces.
///   - zoneID: The ID of the record zone where you want to store the record.
///
/// - Returns: An initialized record object.
///
/// Use this method to initialize a new record object in the specified record zone.
///
/// Upon creation, the new record contains no data and exists only in memory on the local device. Save the record using a ``CKModifyRecordsOperation`` object or by using the ``CKDatabase/save(_:completionHandler:)-3tatz`` method of ``CKDatabase`` to transfer the record's contents to the server.
- (instancetype)initWithRecordType:(CKRecordType)recordType zoneID:(CKRecordZoneID *)zoneID;

/// The value that your app defines to identify the type of record.
///
/// Use this value to differentiate between different record types in your app. The value is primarily for your benefit, so choose record types that represent the data in the corresponding records.
///
/// CloudKit provides two system-defined record types:
///
/// | Record Type | Description |
/// |---|---|
/// | ``CKRecordTypeUserRecord-49k30`` | Identifies records that represent users. |
/// | ``CKRecordTypeShare-8b6yt`` | Identifies records that the user shares. |
@property (readonly, copy) CKRecordType recordType;

/// The unique ID of the record.
///
/// The system sets the ID of a new record at initialization time. If you use the ``CKRecord/init(recordType:recordID:)`` method to initialize the record, the ID derives from the ``CKRecord/ID`` object you provide. In all other cases, the record generates a UUID and bases its ID on that value. The ID of a record never changes during its lifetime.
///
/// When you save a new record object to the server, the server validates the uniqueness of the record, but returns an error only if the save policy calls for it. Specifically, it returns an error when the save policy is ``CKModifyRecordsOperation/RecordSavePolicy/ifServerRecordUnchanged``, which is the default. For all other save policies, the server overwrites the contents of the existing record.
@property (readonly, copy) CKRecordID *recordID;

/// The server change token for the record.
///
/// When you fetch a record from the server, you get the current version of that record as it exists on the server. However, at any time after you fetch a record, other users might save a newer version of it to the server. Every time CloudKit saves a record, the server updates the record's change token to a new value. When you save your copy of the record, the server compares your record's token with the token on the server. If the two tokens match, the server interprets that you modified the latest version of the record and that it can apply your changes immediately. If the two tokens don't match, the server checks your app's save policy to determine how to proceed.
///
/// In your own code, you can use change tokens to distinguish between two different versions of the same record.
///
/// - Note: In some situations, setting a record as the parent of another record can cause the `recordChangeTag` to update on the parent record. This usually occurs when you save the child record.
@property (nullable, readonly, copy) NSString *recordChangeTag;

/// The ID of the user who creates the record.
///
/// Use this property's value to retrieve the user record for the user who creates this record. Every user of the app has a unique user record that is empty by default. Apps can add data to the user record on behalf of the user, but don't store sensitive data in it.
@property (nullable, readonly, copy) CKRecordID *creatorUserRecordID;

/// The time when CloudKit first saves the record to the server.
///
/// The creation date reflects the time when CloudKit creates a record on the server with the current record's ID. For new instances of this class, the value of this property is initially `nil`. When you save the record to the server, the value updates with the creation date for the record.
@property (nullable, readonly, copy) NSDate *creationDate;

/// The ID of the user who most recently modified the record.
///
/// Use this property's value to retrieve the user record of the user who most recently modified this record. Every user of the app has a unique user record that is empty by default. Apps can add data to the user record on behalf of the user, but don't store sensitive data in it.
@property (nullable, readonly, copy) CKRecordID *lastModifiedUserRecordID;

/// The most recent time that CloudKit saved the record to the server.
///
/// The modification date reflects the most recent time that CloudKit saved a record with the current record's ID to the server. For new instances of this class, the value of this property is initially `nil`. When you save the record to the server, the value updates with the modification date for the record.
@property (nullable, readonly, copy) NSDate *modificationDate;

/// Returns the object that the record stores for the specified key.
///
/// - Parameters:
///   - key: The string that identifies a field in the record. A key must consist of one or more alphanumeric characters and must start with a letter. CloudKit permits the use of underscores, but not spaces.
///
/// - Returns: The object for the specified key, or `nil` if no such key exists in the record.
///
/// New records don't contain any keys or values. Values are always one of the data types in <doc:CKRecord#Supported-Data-Types>.
///
/// You access the fields of a `CKRecord` object the same way you access key-value pairs in a dictionary. The `CKRecord` class defines the ``CKRecord/objectForKey:`` and ``CKRecord/setObject:forKey:`` methods for getting and setting values. It also supports dictionary index notation. The following example shows how to use both techniques to set a `firstName` field and retrieve a `lastName` field from a record:
///
/// ```objc
/// // Equivalent ways to get a value.
/// id value = [myRecord objectForKey:@"hiredAt"];
/// value = myRecord[@"hiredAt"];
/// ```
- (nullable __kindof id<CKRecordValue>)objectForKey:(CKRecordFieldKey)key;

/// Stores an object in the record using the specified key.
///
/// - Parameters:
///   - object: The object to store using the specified key. The value you provide must be an instance of one the data types in <doc:CKRecord#Supported-Data-Types>. You receive an error if you use a data type that CloudKit doesn't support. If you specify `nil`, CloudKit removes any object that the record associates with the key.
///   - key: The key to associate with `object`. Use this key to retrieve the value later. A key must consist of one or more alphanumeric characters and must start with a letter. CloudKit permits the use of underscores, but not spaces. Avoid using a key that matches the name of any property of `CKRecord`.
///
/// If the specified key already exists in the record, CloudKit deletes its previous value and replaces it with the one in the `object` parameter. This change affects only the local copy of the record. You must save the record to the server again before the change becomes available to other clients.
///
/// If the type of the `object` parameter differs from the type of the object that's on the server, you encounter an error when you attempt to save this record to the server. For example, if the current value is an <doc://com.apple.documentation/documentation/foundation/nsstring> object, you receive an error if you change the value to an <doc://com.apple.documentation/documentation/foundation/nsnumber> object and save the record.
///
/// You access the fields of a `CKRecord` object the same way you access key-value pairs in a dictionary. The `CKRecord` class defines the ``CKRecord/objectForKey:`` and ``CKRecord/setObject:forKey:`` methods for getting and setting values. It also supports dictionary index notation. The following example shows how to use both techniques to set a `firstName` field and get a `lastName` field from a record:
///
/// ```objc
/// // Equivalent ways to set a value.
/// [myRecord setObject:[NSDate date] forKey:@"hiredAt"];
/// myRecord[@"hiredAt"] = [NSDate date];
/// ```
- (void)setObject:(nullable __kindof id<CKRecordValue>)object forKey:(CKRecordFieldKey)key;

/// Returns an array of the record's keys.
///
/// - Returns: An array of keys, or an empty array if the record doesn't contain any keys.
///
/// The array contains only those keys with values that aren't `nil`.
- (NSArray<CKRecordFieldKey> *)allKeys;

/// Returns an array of strings to use for full-text searches of the field's string-based values.
///
/// - Returns: An array of strings that contains data from the record's string-based fields.
///
/// When performing your own full-text searches, you can use this method to get a list of strings for your search. The method acts only on keys with string values. It breaks each value string apart at whitespace boundaries, creates new strings for each word, adds the new strings to an array, and returns the array. This tokenized version of the record's string values makes it easier to do string-based comparisons of individual words.
- (NSArray<NSString *> *)allTokens;

/// Returns the object that the record stores for the specified key.
///
/// - Parameters:
///   - key: The string that identifies a field in the record. A key must consist of one or more alphanumeric characters and must start with a letter. CloudKit permits the use of underscores, but not spaces.
///
/// - Returns: The object for the specified key, or `nil` if no such key exists in the record.
///
/// ## Discussion
///
/// - Important: Don't call this method directly. The presence of this method is necessary to support subscripting syntax for record objects.
- (nullable __kindof id<CKRecordValue>)objectForKeyedSubscript:(CKRecordFieldKey)key;

/// Stores an object in the record using the specified key.
///
/// - Parameters:
///   - object: The object to store using the specified key. It must be one of the data types in <doc:CKRecord#Supported-Data-Types>. You receive an error if you use a data type that CloudKit doesn't support. If you specify `nil`, CloudKit removes any object that the record associates with the key.
///   - key: The key to associate with `object`. Use this key to retrieve the value later. A key must consist of one or more alphanumeric characters and must start with a letter. CloudKit permits the use of underscores, but not spaces. Avoid using a key that matches the name of any property of `CKRecord`.
///
/// ## Discussion
///
/// - Important: Don't call this method directly. The presence of this method is necessary to support subscripting syntax for record objects.
- (void)setObject:(nullable __kindof id<CKRecordValue>)object forKeyedSubscript:(CKRecordFieldKey)key;

/// Returns an array of keys with recent changes to their values.
///
/// - Returns: An array of keys with changed values since downloading or saving the record. If there aren't any changed keys, this method returns an empty array.
- (NSArray<CKRecordFieldKey> *)changedKeys;

/// Encodes the record's system fields using the specified archiver.
///
/// - Parameters:
///   - coder: An archiver object.
///
/// Use this method to encode the record's metadata that CloudKit provides. Every record has keys that the system defines that correspond to record metadata, such as the record ID, record type, creation date, and so on. This method encodes those keys in the specified archiver. This method doesn't include any keys you add to the record. It also doesn't encode the keys that the ``CKRecord/changedKeys`` method returns.
///
/// You might use this method when you want to store only the system metadata because you store the actual record data elsewhere.
- (void)encodeSystemFieldsWithCoder:(NSCoder *)coder;

/// A reference to the share object that determines the share status of the record.
///
/// CloudKit clears this property's value when it deletes the corresponding ``CKShare`` object on the server. Send this record in the same batch operation as the share object you're deleting, and this property updates accordingly.
///
/// CloudKit only supports sharing in zones with the `CKRecordZoneCapabilitySharing` capability. The default zone doesn't support sharing.
///
/// If any records have a parent reference to this record, CloudKit implicitly shares them along with this record.
///
/// - Note: Records in a hierarchy must only exist within one share. If a child record in a hierarchy already has a share reference, you get a `CKErrorAlreadyShared` error if you try to share any of that record's parents.
@property (nullable, readonly, copy) CKReference *share API_AVAILABLE(macos(10.12), ios(10.0), tvos(10.0), watchos(3.0));

/// A reference to the record's parent record.
///
/// Use parent references to inform CloudKit about the hierarchy of your records. CloudKit shares the hierarchy when a ``CKShare`` includes a referenced record. Add relationships between records as you create them, even if you don't plan to share them. This allows you to manage the sharing of a hierarchy by only modifying the root record's ``CKRecord/share`` reference.
///
/// To indicate that a record belongs to its parent, set this property to a reference that points to the parent record. The reference must use the ``CKRecord/ReferenceAction/none`` action or CloudKit throws an exception. The parent record must exist on the server when you save the child, or you must include the record in the same save operation. Otherwise, the operation fails.
@property (nullable, copy) CKReference *parent API_AVAILABLE(macos(10.12), ios(10.0), tvos(10.0), watchos(3.0));

/// Creates and sets a reference object for a parent from its record.
///
/// - Parameters:
///   - parentRecord: A record that you want to set as the parent to this record.
///
/// This method creates and sets a ``CKRecord/Reference`` object that points to the record you provide. The resulting `CKReference` has an action of ``CKRecord/ReferenceAction/none``.
- (void)setParentReferenceFromRecord:(nullable CKRecord *)parentRecord API_AVAILABLE(macos(10.12), ios(10.0), tvos(10.0), watchos(3.0));

/// Creates and sets a reference object for a parent from the parent's record ID.
///
/// - Parameters:
///   - parentRecordID: The ``CKRecord/ID`` object for the record that you want to set as this record's parent.
///
/// This method creates and sets a ``CKRecord/Reference`` object that points to the record you provide. The resulting `CKReference` has an action of ``CKRecord/ReferenceAction/none``.
- (void)setParentReferenceFromRecordID:(nullable CKRecordID *)parentRecordID API_AVAILABLE(macos(10.12), ios(10.0), tvos(10.0), watchos(3.0));

@end

@interface NSString (CKRecordValue) <CKRecordValue>
@end

@interface NSNumber (CKRecordValue) <CKRecordValue>
@end

@interface NSArray (CKRecordValue) <CKRecordValue>
@end

@interface NSDate (CKRecordValue) <CKRecordValue>
@end

@interface NSData (CKRecordValue) <CKRecordValue>
@end

@interface CKReference (CKRecordValue) <CKRecordValue>
@end

@interface CKAsset (CKRecordValue) <CKRecordValue>
@end

@interface CLLocation (CKRecordValue) <CKRecordValue>
@end

/// A protocol for managing the key-value pairs of a CloudKit record.
API_AVAILABLE(macos(10.11), ios(9.0), watchos(3.0))
@protocol CKRecordKeyValueSetting <NSObject>

/// Returns the object that the record stores for the specified key.
///
/// - Parameters:
///   - key: The string that identifies a field in the record. A key must consist of one or more alphanumeric characters and must start with a letter. CloudKit permits the use of underscores, but not spaces.
///
/// - Returns: The object for the specified key, or `nil` if no such key exists in the record.
- (nullable __kindof id<CKRecordValue>)objectForKey:(CKRecordFieldKey)key;

/// Stores an object in the record using the specified key.
///
/// - Parameters:
///   - object: The object to store using the specified key. It must be one of the data types in <doc:CKRecord#Supported-Data-Types>. You receive an error if you use a data type that CloudKit doesn't support. If you specify `nil`, CloudKit removes any object that the record associates with the key.
///   - key: The key to associate with `object`. Use this key to retrieve the value later. A key must consist of one or more alphanumeric characters and must start with a letter. CloudKit permits the use of underscores, but not spaces. Avoid using a key that matches the name of any property of `CKRecord`.
- (void)setObject:(nullable __kindof id<CKRecordValue>)object forKey:(CKRecordFieldKey)key;

/// Returns the object that the record stores for the specified key.
///
/// - Parameters:
///   - key: The string that identifies a field in the record. A key must consist of one or more alphanumeric characters and must start with a letter. CloudKit permits the use of underscores, but not spaces.
///
/// - Returns: The object for the specified key, or `nil` if no such key exists in the record.
- (nullable __kindof id<CKRecordValue>)objectForKeyedSubscript:(CKRecordFieldKey)key;

/// Stores an object in the record using the specified key.
///
/// - Parameters:
///   - object: The object to store using the specified key. It must be one of the data types in <doc:CKRecord#Supported-Data-Types>. You receive an error if you use a data type that CloudKit doesn't support. If you specify `nil`, CloudKit removes any object that the record associates with the key.
///   - key: The key to associate with `object`. Use this key to retrieve the value later. A key must consist of one or more alphanumeric characters and must start with a letter. CloudKit permits the use of underscores, but not spaces. Avoid using a key that matches the name of any property of `CKRecord`.
- (void)setObject:(nullable __kindof id<CKRecordValue>)object forKeyedSubscript:(CKRecordFieldKey)key;

/// Returns an array of the record's keys.
///
/// - Returns: An array of keys, or an empty array if the record doesn't contain any keys.
- (NSArray<CKRecordFieldKey> *)allKeys;

/// Returns an array of keys with recent changes to their values.
///
/// - Returns: An array of keys with changed values since downloading or saving the record. If there aren't any changed keys, this method returns an empty array.
- (NSArray<CKRecordFieldKey> *)changedKeys;
@end

API_AVAILABLE(macos(10.11), ios(9.0), watchos(3.0))
@interface CKRecord (CKRecordKeyValueSettingConformance) <CKRecordKeyValueSetting>

/// An object that manages the record's encrypted key-value pairs.
///
/// Use the object this property returns to read and write encrypted key-value pairs that you store on the record. You can encrypt values of any data type that CloudKit supports, except ``CKAsset``, which is encrypted by default, and ``CKRecord/Reference``, which isn't encrypted so it remains available for server-side use. Only encrypt new fields. CloudKit doesn't allow encryption on fields that already exist in your app's schema, or on records that you store in the public database.
///
/// - Note: CloudKit doesn't support indexes on encrypted fields. Don't include encrypted fields in your predicate or sort descriptors when fetching records with ``CKQuery`` and ``CKQueryOperation``.
///
/// CloudKit encrypts the fields' values on-device before saving them to iCloud, and decrypts the values only after fetching them from the server. When you enable Advanced Data Protection, the encryption keys are available exclusively to the record's owner and, if the user shares the record, that share's participants.
///
/// The following example shows how to use `encryptedValues` to encrypt and decrypt a string value:
///
/// ```swift
/// let record = CKRecord(recordType: "Property")
///
/// // Encrypt the name of the property's owner.
/// record.encryptedValues["ownerName"] = "Maria Ruiz"
///
/// // Decrypt the name of the property's owner, using the
/// // appropriate data type, and assign it to a local variable.
/// var clientName = record.encryptedValues["ownerName"] as? NSString
/// ```
@property (readonly, copy) NS_SWIFT_SENDABLE id<CKRecordKeyValueSetting> encryptedValues API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0), watchos(8.0));
                                                                                                     
@end

NS_HEADER_AUDIT_END(nullability, sendability)
