//
//  CKSyncEngineEvent.h
//  CloudKit
//
//  Copyright © 2022 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CloudKit/CKRecord.h>

@class CKRecordZone, CKRecordZoneID;
@class CKSyncEngineAccountChangeEvent, CKSyncEngineDidFetchChangesEvent, CKSyncEngineDidFetchRecordZoneChangesEvent, CKSyncEngineDidSendChangesEvent, CKSyncEngineFetchedDatabaseChangesEvent, CKSyncEngineFetchedRecordDeletion, CKSyncEngineFetchedRecordZoneChangesEvent, CKSyncEngineSentDatabaseChangesEvent, CKSyncEngineSentRecordZoneChangesEvent, CKSyncEngineStateUpdateEvent, CKSyncEngineWillFetchChangesEvent, CKSyncEngineWillFetchRecordZoneChangesEvent, CKSyncEngineWillSendChangesEvent;
@class CKSyncEngineFailedRecordSave, CKSyncEngineFailedZoneSave, CKSyncEngineFetchChangesContext, CKSyncEngineFetchedZoneDeletion, CKSyncEngineSendChangesContext, CKSyncEngineStateSerialization;

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

/// Describes an event that occurs during a sync operation.
API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0), watchos(10.0))
NS_REFINED_FOR_SWIFT
typedef NS_ENUM(NSInteger, CKSyncEngineEventType) {
    
    //
    // Local State Changes
    //
    
    /// The sync engine updated its state.
    ///
    /// You should persist it locally.
    CKSyncEngineEventTypeStateUpdate,
    
    /// The user signed in or out of their account.
    CKSyncEngineEventTypeAccountChange,
    
    //
    // Fetched Changes
    //
    
    /// The sync engine has fetched new database changes from the server.
    CKSyncEngineEventTypeFetchedDatabaseChanges,
    
    /// The sync engine fetched new record zone changes from the server.
    CKSyncEngineEventTypeFetchedRecordZoneChanges,
    
    //
    // Sent Changes
    //
    
    /// The sync engine sent a batch of database changes to the server.
    CKSyncEngineEventTypeSentDatabaseChanges,
    
    /// The sync engine sent a batch of record zone changes to the server.
    CKSyncEngineEventTypeSentRecordZoneChanges,
    
    //
    // Fetch Changes Lifecycle
    //
    
    /// The sync engine is about to fetch changes from the server.
    CKSyncEngineEventTypeWillFetchChanges,
    
    /// The sync engine is about to fetch record zone changes from the server for a specific zone.
    CKSyncEngineEventTypeWillFetchRecordZoneChanges,
    
    /// The sync engine has completed fetching record zone changes from the server for a specific zone.
    CKSyncEngineEventTypeDidFetchRecordZoneChanges,
    
    /// The sync engine finished fetching changes from the server.
    CKSyncEngineEventTypeDidFetchChanges,
    
    //
    // Send Changes Lifecycle
    //
    
    /// The sync engine is about to send changes to the server.
    CKSyncEngineEventTypeWillSendChanges,
    
    /// The sync engine finished sending changes to the server.
    CKSyncEngineEventTypeDidSendChanges,
};

/// An event that occurs during a sync operation.
///
/// All sync operation events descend from this base class, and as such you don't create instances of it directly. Instead, the sync engine dispatches them to your app's delegate, periodically, throughout a sync operation.
///
/// See the documentation for each event class for more details about when and why an event is posted.
///
/// Use the ``type`` property to determine the event's proper type, and then use the corresponding convenience property to retrieve a reference to the event that's downcast to the appropriate subclass. For example, when CloudKit vends an event with ``type`` set to ``CKSyncEngineEventType/stateUpdate``, use the ``stateUpdateEvent`` property to get the downcast reference.
///
/// - Important: It is a fatal error to access a non-corresponding convenience property.
API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0), watchos(10.0))
NS_REFINED_FOR_SWIFT
// This class should not be subclassed. If it is, Sendable may no longer apply.
NS_SWIFT_SENDABLE
@interface CKSyncEngineEvent : NSObject

/// The type of event.
@property (readonly, assign) CKSyncEngineEventType type;

// Helpers to cast an event to the proper subclass.
// These crash the current process if used for the wrong event type.

/// The event downcast to the subclass that represents an update to the sync engine's state.
@property (readonly, strong, nonatomic) CKSyncEngineStateUpdateEvent *stateUpdateEvent;

/// The event downcast to the subclass that represents a change to the device's iCloud account.
@property (readonly, strong, nonatomic) CKSyncEngineAccountChangeEvent *accountChangeEvent;

/// The event downcast to the subclass that represents an imminent database fetch.
@property (readonly, strong, nonatomic) CKSyncEngineWillFetchChangesEvent *willFetchChangesEvent;

/// The event downcast to the subclass that represents a set of fetched database changes to process.
@property (readonly, strong, nonatomic) CKSyncEngineFetchedDatabaseChangesEvent *fetchedDatabaseChangesEvent;

/// The event downcast to the subclass that represents a completed database fetch.
@property (readonly, strong, nonatomic) CKSyncEngineDidFetchChangesEvent *didFetchChangesEvent;

/// The event downcast to the subclass that represents an imminent fetch of record zone changes.
@property (readonly, strong, nonatomic) CKSyncEngineWillFetchRecordZoneChangesEvent *willFetchRecordZoneChangesEvent;

/// The event downcast to the subclass that represents a set of fetched record zone changes to process.
@property (readonly, strong, nonatomic) CKSyncEngineFetchedRecordZoneChangesEvent *fetchedRecordZoneChangesEvent;

/// The event downcast to the subclass that represents a completed record zone fetch.
@property (readonly, strong, nonatomic) CKSyncEngineDidFetchRecordZoneChangesEvent *didFetchRecordZoneChangesEvent;

/// The event downcast to the subclass that represents an imminent send operation.
@property (readonly, strong, nonatomic) CKSyncEngineWillSendChangesEvent *willSendChangesEvent;

/// The event downcast to the subclass that represents a sent batch of database changes.
@property (readonly, strong, nonatomic) CKSyncEngineSentDatabaseChangesEvent *sentDatabaseChangesEvent;

/// The event downcast to the subclass that represents a sent batch of record zone changes.
@property (readonly, strong, nonatomic) CKSyncEngineSentRecordZoneChangesEvent *sentRecordZoneChangesEvent;

/// The event downcast to the subclass that represents a completed send operation.
@property (readonly, strong, nonatomic) CKSyncEngineDidSendChangesEvent *didSendChangesEvent;

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

/// The sync engine state was updated, and you should persist it locally.
///
/// In order to function properly and efficiently, `CKSyncEngine` tracks some state internally.
/// When the sync engine state changes, it gives you the latest serialized version in a ``CKSyncEngine/Event/StateUpdate``.
/// This event happens occasionally when the sync engine modifies the state internally during normal sync operation.
/// This event also happens when you change the state yourself.
///
/// The sync engine does not persist this state to disk, so you need to persist it alongside your own local data.
/// The next time your process launches, use this latest state serialization in ``CKSyncEngineConfiguration/stateSerialization`` to initialize your sync engine.
///
/// This state is directly tied to the changes you fetch and send with the sync engine.
/// You should persist this state alongside any changes fetched prior to receiving this state.
API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0), watchos(10.0))
NS_REFINED_FOR_SWIFT
CK_SUBCLASSING_RESTRICTED
NS_SWIFT_SENDABLE
@interface CKSyncEngineStateUpdateEvent : CKSyncEngineEvent

/// The current state of the sync engine.
///
/// - Important: Always persist the most recent state to disk alongside your app data. The sync engine requires you to provide it with the most recent serialized state at initialization, and it's your responsibility to make sure the state is available across app launches.
@property (readonly, copy, nonatomic) CKSyncEngineStateSerialization *stateSerialization;

@end

/// Describes a change to the device's iCloud account.
API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0), watchos(10.0))
NS_REFINED_FOR_SWIFT
typedef NS_ENUM(NSInteger, CKSyncEngineAccountChangeType) {
    
    /// A change indicating a sign-in to an iCloud account.
    ///
    /// If your app has locally-stored data when ``CKSyncEngine-4b4w9`` notifies it about the device signing in to an iCloud account, perform one of the following actions:
    ///
    /// - Keep the local data separate from any remote data
    /// - Merge the local data with the account's remote data
    /// - Delete the local data
    /// - Prompt the account's owner to make the decision
    CKSyncEngineAccountChangeTypeSignIn,
    
    /// A change indicating a sign-out of an iCloud account.
    ///
    /// You should delete any locally-stored data for the previous account.
    CKSyncEngineAccountChangeTypeSignOut,
    
    /// A change indicating a switch between two iCloud accounts.
    ///
    /// You should delete any locally-stored data for the previous account.
    CKSyncEngineAccountChangeTypeSwitchAccounts,
};

/// The user signed in or out of their account.
///
/// The sync engine automatically listens for account changes, and it sends this event when the user signs in or out.
/// It's your responsibility to react appropriately to this change and update your local persistence.
///
/// When the logged-in account changes, the sync engine resets its internal state.
/// This means that it clears any pending database or record zone changes that you may have added.
///
/// Note that it's possible the account changes multiple times while your app is quit.
/// If this happens, you only receive one account change event representing the transition between the last known state and the current state.
API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0), watchos(10.0))
NS_REFINED_FOR_SWIFT
CK_SUBCLASSING_RESTRICTED
NS_SWIFT_SENDABLE
@interface CKSyncEngineAccountChangeEvent : CKSyncEngineEvent

/// The iCloud account's change type.
@property (readonly, assign, nonatomic) CKSyncEngineAccountChangeType changeType;

/// The previous iCloud account's record identifier.
///
/// If the user just signed in, this is `nil`.
/// If the user signed out or switched accounts, this is the old account's user record ID.
@property (nullable, readonly, copy, nonatomic) CKRecordID *previousUser;

/// The current iCloud account's record identifier.
///
/// If the user just signed in or switched accounts, this is the new user record ID.
/// If the user signed out, this is `nil`.
@property (nullable, readonly, copy, nonatomic) CKRecordID *currentUser;

@end

/// An object that provides information about fetched database changes.
///
/// - Note: Although CloudKit doesn't guarantee the order of fetched database changes, the typical order for both deletions and modifications is oldest to newest.
API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0), watchos(10.0))
NS_REFINED_FOR_SWIFT
CK_SUBCLASSING_RESTRICTED
NS_SWIFT_SENDABLE
@interface CKSyncEngineFetchedDatabaseChangesEvent : CKSyncEngineEvent

/// The fetched record zone modifications.
@property (readonly, copy, nonatomic) NSArray<CKRecordZone *> *modifications;

/// The fetched record zone deletions.
@property (readonly, copy, nonatomic) NSArray<CKSyncEngineFetchedZoneDeletion *> *deletions;

@end

/// An object that provides information about fetched record zone changes.
///
/// - Note: Although CloudKit doesn't guarantee the order of fetched database changes, the typical order for both deletions and modifications is oldest to newest.
API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0), watchos(10.0))
NS_REFINED_FOR_SWIFT
CK_SUBCLASSING_RESTRICTED
NS_SWIFT_SENDABLE
@interface CKSyncEngineFetchedRecordZoneChangesEvent : CKSyncEngineEvent

/// The fetched record modifications.
@property (readonly, copy, nonatomic) NSArray<CKRecord *> *modifications;

/// The fetched record deletions.
@property (readonly, copy, nonatomic) NSArray<CKSyncEngineFetchedRecordDeletion *> *deletions;

@end

/// An object that provides information about a sent batch of database changes.
API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0), watchos(10.0))
NS_REFINED_FOR_SWIFT
CK_SUBCLASSING_RESTRICTED
NS_SWIFT_SENDABLE
@interface CKSyncEngineSentDatabaseChangesEvent : CKSyncEngineEvent

/// The modified record zones.
@property (readonly, copy, nonatomic) NSArray<CKRecordZone *> *savedZones;

/// The record zones that CloudKit is unable to modify.
@property (readonly, copy, nonatomic) NSArray<CKSyncEngineFailedZoneSave *> *failedZoneSaves;

/// The unique identifiers of the deleted record zones.
@property (readonly, copy, nonatomic) NSArray<CKRecordZoneID *> *deletedZoneIDs;

/// The unique identifiers of the record zones CloudKit is unable to delete, and the reasons why.
@property (readonly, copy, nonatomic) NSDictionary<CKRecordZoneID *, NSError *> *failedZoneDeletes;

@end

/// The sync engine finished sending a batch of record zone changes to the server.
///
/// If a record save succeeded, you should encode the system fields of this record to use the next time you save. See ``CKRecord/encodeSystemFieldsWithCoder:``.
///
/// If a record deletion succeeded, you should remove any local system fields for that record.
///
/// If the record change failed, try to resolve the issue causing the error and save the record again if necessary.
API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0), watchos(10.0))
NS_REFINED_FOR_SWIFT
CK_SUBCLASSING_RESTRICTED
NS_SWIFT_SENDABLE
@interface CKSyncEngineSentRecordZoneChangesEvent : CKSyncEngineEvent

/// The modified records.
@property (readonly, copy, nonatomic) NSArray<CKRecord *> *savedRecords;

/// The records that CloudKit is unable to modify.
@property (readonly, copy, nonatomic) NSArray<CKSyncEngineFailedRecordSave *> *failedRecordSaves;

/// The unique identifiers of the deleted records.
@property (readonly, copy, nonatomic) NSArray<CKRecordID *> *deletedRecordIDs;

/// The unique identifiers of the records CloudKit is unable to delete, and the reasons why.
@property (readonly, copy, nonatomic) NSDictionary<CKRecordID *, NSError *> *failedRecordDeletes;

@end

/// The sync engine is about to fetch changes from the server.
///
/// The sync engine delivers the changes themselves via ``CKSyncEngineFetchedDatabaseChangesEvent`` and ``CKSyncEngineFetchedRecordZoneChangesEvent``.
///
/// Note that this event might not always occur every time you call ``CKSyncEngine/fetchChangesWithCompletionHandler:``.
/// For example, if you call ``CKSyncEngine/fetchChangesWithCompletionHandler:`` concurrently while the engine is already fetching changes, this event might not be sent.
/// Similarly, if there's no logged-in account, the engine might short-circuit the call to `fetchChanges`, and this event won't be sent.
API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0), watchos(10.0))
NS_REFINED_FOR_SWIFT
CK_SUBCLASSING_RESTRICTED
NS_SWIFT_SENDABLE
@interface CKSyncEngineWillFetchChangesEvent : CKSyncEngineEvent

@property (readonly, strong, nonatomic) CKSyncEngineFetchChangesContext *context API_AVAILABLE(macos(14.2), macCatalyst(17.2), ios(17.2), tvos(17.2), watchos(10.2));

@end

/// The sync engine finished fetching record zone changes from the server for a specific zone.
///
/// This might be a good signal to perform any post-processing tasks on a per-zone basis if necessary.
///
/// You should receive one ``CKSyncEngineDidFetchRecordZoneChangesEvent`` for each `CKSyncEngineWillFetchRecordZoneChangesEvent`.
API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0), watchos(10.0))
NS_REFINED_FOR_SWIFT
CK_SUBCLASSING_RESTRICTED
NS_SWIFT_SENDABLE
@interface CKSyncEngineWillFetchRecordZoneChangesEvent : CKSyncEngineEvent

/// The associated record zone's unique identifier.
@property (readonly, copy, nonatomic) CKRecordZoneID *zoneID;

@end

/// An object that provides information about a finished record zone fetch.
API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0), watchos(10.0))
NS_REFINED_FOR_SWIFT
CK_SUBCLASSING_RESTRICTED
NS_SWIFT_SENDABLE
@interface CKSyncEngineDidFetchRecordZoneChangesEvent : CKSyncEngineEvent

/// The associated record zone's unique identifier.
@property (readonly, copy, nonatomic) CKRecordZoneID *zoneID;

/// An error that describes the cause of a failed fetch operation.
///
/// A `nil` value indicates a successful fetch.
@property (nullable, readonly, copy, nonatomic) NSError *error;

@end

/// The sync engine finished fetching changes from the server.
///
/// You should receive one `CKSyncEngineDidFetchChangesEvent` for each ``CKSyncEngineWillFetchChangesEvent``.
API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0), watchos(10.0))
NS_REFINED_FOR_SWIFT
CK_SUBCLASSING_RESTRICTED
NS_SWIFT_SENDABLE
@interface CKSyncEngineDidFetchChangesEvent : CKSyncEngineEvent

@property (readonly, strong, nonatomic) CKSyncEngineFetchChangesContext *context API_AVAILABLE(macos(14.2), macCatalyst(17.2), ios(17.2), tvos(17.2), watchos(10.2));

@end

/// An object that provides information about an imminent send of local changes.
API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0), watchos(10.0))
NS_REFINED_FOR_SWIFT
CK_SUBCLASSING_RESTRICTED
NS_SWIFT_SENDABLE
@interface CKSyncEngineWillSendChangesEvent : CKSyncEngineEvent

/// The context of the imminent send request.
@property (readonly, strong, nonatomic) CKSyncEngineSendChangesContext *context;

@end

/// An object that provides information about a finished send operation.
API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0), watchos(10.0))
NS_REFINED_FOR_SWIFT
CK_SUBCLASSING_RESTRICTED
NS_SWIFT_SENDABLE
@interface CKSyncEngineDidSendChangesEvent : CKSyncEngineEvent

/// The context of the finished send request.
@property (readonly, strong, nonatomic) CKSyncEngineSendChangesContext *context;

@end

#pragma mark - Data

/// An object that describes the deletion of an individual record.
API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0), watchos(10.0))
NS_REFINED_FOR_SWIFT
CK_SUBCLASSING_RESTRICTED
NS_SWIFT_SENDABLE
@interface CKSyncEngineFetchedRecordDeletion : NSObject

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

/// The deleted record's unique identifier.
@property (readonly, copy, nonatomic) CKRecordID *recordID;

/// The record type of the deleted record.
@property (readonly, copy, nonatomic) CKRecordType recordType;

@end

/// Describes the reason for a record zone deletion.
API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0), watchos(10.0))
NS_REFINED_FOR_SWIFT
typedef NS_ENUM(NSInteger, CKSyncEngineZoneDeletionReason) {
    /// Your app deleted the record zone.
    CKSyncEngineZoneDeletionReasonDeleted,
    
    /// The owner of the iCloud account purged your app's data using the Settings app.
    ///
    /// - Important: Upon receipt of deletions with this reason, you must delete any locally cached data and not resend it to iCloud.
    CKSyncEngineZoneDeletionReasonPurged,
    
    /// The owner of the iCloud account reset their encrypted data.
    ///
    /// - Important: Upon receipt of deletions with this reason, you must delete any locally cached data and not resend it to iCloud.
    CKSyncEngineZoneDeletionReasonEncryptedDataReset,
};

/// An object that describes the deletion of a record zone.
API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0), watchos(10.0))
NS_REFINED_FOR_SWIFT
CK_SUBCLASSING_RESTRICTED
NS_SWIFT_SENDABLE
@interface CKSyncEngineFetchedZoneDeletion : NSObject

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

/// The identifier of the deleted record zone.
@property (readonly, copy, nonatomic) CKRecordZoneID *zoneID;

/// The reason for the deletion.
@property (readonly, assign, nonatomic) CKSyncEngineZoneDeletionReason reason;

@end

/// A type that describes an unsuccessful attempt to modify an individual record.
API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0), watchos(10.0))
NS_REFINED_FOR_SWIFT
CK_SUBCLASSING_RESTRICTED
NS_SWIFT_SENDABLE
@interface CKSyncEngineFailedRecordSave : NSObject

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

/// The record that CloudKit is unable to modify.
@property (readonly, strong, nonatomic) CKRecord *record;

/// An error that describes the reason for the unsuccessful attempt to modify the associated record.
@property (readonly, strong, nonatomic) NSError *error;

@end

/// An object that describes an unsuccessful attempt to modify a single record zone.
API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0), watchos(10.0))
NS_REFINED_FOR_SWIFT
NS_SWIFT_SENDABLE
CK_SUBCLASSING_RESTRICTED
@interface CKSyncEngineFailedZoneSave : NSObject

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

/// The record zone that CloudKit is unable to modify.
@property (readonly, strong, nonatomic) CKRecordZone *recordZone;

/// An error that describes the reason for the unsuccessful attempt to modify the associated record zone.
@property (readonly, strong, nonatomic) NSError *error;

@end

NS_HEADER_AUDIT_END(nullability, sendability)
