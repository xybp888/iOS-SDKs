//
//  CKSyncEngineState.h
//  CloudKit
//
//  Copyright © 2018 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

#import <CloudKit/CKDefines.h>

@class CKAsset, CKRecordID, CKRecordZone, CKRecordZoneID;
@class CKSyncEnginePendingRecordZoneChange, CKSyncEnginePendingDatabaseChange;

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

/// An object that manages the sync engine's state.
///
/// To reliably and consistently sync your app's data, a sync engine keeps a record of several important pieces of data, such as server changes tokens (for databases and record zones), subscription identifiers, the most recent ``CKUserIdentity/userRecordID``, and so on.
/// This class automatically manages that state on behalf of your app, but there are certain elements you can modify.
/// For example, you control the list of pending changes to send to the iCloud servers and manipulate that list using the ``addPendingDatabaseChanges:`` and ``addPendingRecordZoneChanges:`` methods.
/// If there aren't any scheduled sync operations when you invoke these methods, the engine automatically schedules one.
///
/// An engine's state changes periodically and, when it does, the sync engine dispatches an event of type  ``CKSyncEngineStateUpdateEvent`` to your delegate.
/// The event contains an instance of ``CKSyncEngineStateSerialization`` and, on receipt of such an event, it's your responsibility to persist the serialized state to disk so that it's available across app launches.
/// On the next initialization of the sync engine, you provide the most recently persisted state as part of the engine's configuration.
/// For more information, see ``CKSyncEngineConfiguration/initWithDatabase:stateSerialization:delegate:``.
API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0), watchos(10.0))
NS_REFINED_FOR_SWIFT
CK_SUBCLASSING_RESTRICTED
NS_SWIFT_SENDABLE
@interface CKSyncEngineState : NSObject

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

#pragma mark - Pending Changes

/// A list of record zone changes that the sync engine has yet to send to the iCloud servers.
///
/// This array contains any pending record zone changes to send to the iCloud servers.
/// After the sync engine sends those changes, your app's sync delegate receives an event of type ``CKSyncEngineSentRecordZoneChangesEvent``.
///
/// The sync engine keeps this list up-to-date while sending changes to the server.
/// For example, when it successfully saves a record, it removes that change from this list.
/// If it fails to send a change due to some retryable error (e.g. a network failure), it keeps that change in this list.
///
/// Use the ``CKSyncEngineState/addPendingRecordZoneChanges:`` and ``CKSyncEngineState/removePendingRecordZoneChanges:`` methods to modify the array's contents.
@property (readonly, copy) NSArray<CKSyncEnginePendingRecordZoneChange *> *pendingRecordZoneChanges;

/// A list of database changes that the sync engine has yet to send to the iCloud servers.
///
/// This array contains any pending database changes to send to the iCloud servers.
/// After the sync engine sends those changes, your app's sync delegate receives an event of type ``CKSyncEngineSentDatabaseChangesEvent``.
///
/// The sync engine keeps this list up-to-date while sending changes to the server.
/// For example, when it successfully saves a zone, it will remove that change from this list.
/// If it fails to send a change due to some retryable error (e.g. a network failure), it will keep that change in this list.
///
/// Use the ``CKSyncEngineState/addPendingDatabaseChanges:`` and ``CKSyncEngineState/removePendingDatabaseChanges:`` methods to modify the array's contents.
@property (readonly, copy) NSArray<CKSyncEnginePendingDatabaseChange *> *pendingDatabaseChanges;

/// A Boolean value that indicates whether there are pending changes that the sync engine is unaware of.
///
/// Use this property to inform the sync engine that there are pending changes other than those available in ``CKSyncEngineState/pendingRecordZoneChanges``.
/// After you set this property, the sync engine automatically schedules a send operation and, when that operation executes, asks your delegate to provide those changes by invoking the ``CKSyncEngineDelegate/syncEngine:nextRecordZoneChangeBatchForContext:`` method.
///
/// Using this property is optional and is necessary only if you track pending changes manually, outside of the sync engine's state.
@property (assign) BOOL hasPendingUntrackedChanges;

/// The identifiers of zones with changes on the server that have not yet been fetched.
///
/// The sync engine populates this list automatically, for example when receiving a push notification indicating new changes.
@property (readonly, copy) NSArray<CKRecordZoneID *> *zoneIDsWithUnfetchedServerChanges;

/// Adds the specified record zone changes to the state.
///
/// - Parameters:
///   - changes: An array of record zone changes.
///
/// Use this method to enable the sync engine to manage your pending record zone changes.
/// For example, when someone makes a change that your app needs to send to the server, use this method to record the change.
/// Then, when creating the change batch for the next send operation, retrieve the pending changes from the ``CKSyncEngineState/pendingRecordZoneChanges`` property.
///
/// If there are no scheduled sync operations when you invoke this method, the sync engine automatically schedules one to send the changes.
/// After the engine sends those changes, it notifies your app's sync delegate with an event of type ``CKSyncEngineSentRecordZoneChangesEvent``.
///
/// The sync engine maintains a consistent collection of tracked pending changes, deduplicating them as necessary.
/// The engine removes changes from the list as it sends them, but retains any that fail due to a recoverable error, such as a network issue or exceeding the rate limit.
///
/// - Note: The order in which you apply record zone changes is important.
///
///   For example:
///   - If you add a `CKSyncEnginePendingRecordZoneChange` with type `CKSyncEnginePendingRecordZoneChangeTypeSaveRecord` for recordA then another with type `CKSyncEnginePendingRecordZoneChangeTypeDeleteRecord`, the sync engine discards the save and sends only the delete change.
///   - If you add a `CKSyncEnginePendingRecordZoneChange` with type `CKSyncEnginePendingRecordZoneChangeTypeDeleteRecord` for recordA then another with type `CKSyncEnginePendingRecordZoneChangeTypeSaveRecord`, the sync engine discards the delete and sends only the save change.
- (void)addPendingRecordZoneChanges:(NSArray<CKSyncEnginePendingRecordZoneChange *> *)changes NS_SWIFT_NAME(add(pendingRecordZoneChanges:));

/// Removes the specified record zone changes from the state.
///
/// - Parameters:
///   - changes: An array of record zone changes.
///
/// Use this method when you no longer want the sync engine to send certain pending changes.
- (void)removePendingRecordZoneChanges:(NSArray<CKSyncEnginePendingRecordZoneChange *> *)changes NS_SWIFT_NAME(remove(pendingRecordZoneChanges:));

/// Adds the specified database changes to the state.
///
/// - Parameters:
///   - changes: An array of database changes.
///
/// Use this method to enable the sync engine to manage your pending database changes.
/// For example, when someone makes a change that your app needs to send to the server, use this method to record the change.
/// If there are no scheduled sync operations when you invoke this method, the sync engine automatically schedules one to send the changes.
/// After the engine sends those changes, it notifies your app's sync delegate with an event of type ``CKSyncEngineSentDatabaseChangesEvent``.
///
/// The sync engine maintains a consistent collection of tracked pending changes, deduplicating them as necessary.
/// The engine removes changes from the list as it sends them, but retains any that fail due to a recoverable error, such as a network issue, or exceeding the rate limit.
///
/// - Note: The order in which you apply database changes is important.
///
///   For example:
///   - If you add a `CKSyncEnginePendingDatabaseChange` with type `CKSyncEnginePendingDatabaseChangeTypeSaveZone` for zoneA then another with type `CKSyncEnginePendingDatabaseChangeTypeDeleteZone`, the sync engine discards the save and sends only the delete change.
///   - If you add a `CKSyncEnginePendingDatabaseChange` with type `CKSyncEnginePendingDatabaseChangeTypeDeleteZone` for zoneA then another with type `CKSyncEnginePendingDatabaseChangeTypeSaveZone`, the sync engine discards the delete and sends only the save change.
- (void)addPendingDatabaseChanges:(NSArray<CKSyncEnginePendingDatabaseChange *> *)changes NS_SWIFT_NAME(add(pendingDatabaseChanges:));

/// Removes the specified database changes from the state.
///
/// - Parameters:
///   - changes: An array of database changes.
///
/// Use this method when you no longer want the sync engine to send certain pending changes.
- (void)removePendingDatabaseChanges:(NSArray<CKSyncEnginePendingDatabaseChange *> *)changes NS_SWIFT_NAME(remove(pendingDatabaseChanges:));

@end

#pragma mark - CKSyncEngineStateSerialization

/// An opaque object that contains the serialized representation of a sync engine's current state.
API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0), watchos(10.0))
NS_REFINED_FOR_SWIFT
CK_SUBCLASSING_RESTRICTED
NS_SWIFT_SENDABLE
@interface CKSyncEngineStateSerialization : NSObject <NSSecureCoding>

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

#pragma mark - CKSyncEnginePendingRecordZoneChange

/// A type of change in a record zone that needs to be sent to the server.
API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0), watchos(10.0))
NS_REFINED_FOR_SWIFT
typedef NS_ENUM(NSInteger, CKSyncEnginePendingRecordZoneChangeType) {
    CKSyncEnginePendingRecordZoneChangeTypeSaveRecord,
    CKSyncEnginePendingRecordZoneChangeTypeDeleteRecord,
};

/// An object that describes an unsent record modification.
API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0), watchos(10.0))
NS_REFINED_FOR_SWIFT
CK_SUBCLASSING_RESTRICTED
NS_SWIFT_SENDABLE
@interface CKSyncEnginePendingRecordZoneChange : NSObject

/// Creates a record zone change of the specified type for the given record.
///
/// - Parameters:
///   - recordID: The identifier of the record to change.
///   - type: The type of change to make.
///
/// - Returns: An initialized record zone change.
- (instancetype)initWithRecordID:(CKRecordID *)recordID
                            type:(CKSyncEnginePendingRecordZoneChangeType)type NS_DESIGNATED_INITIALIZER NS_SWIFT_NAME(init(_:type:));

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

/// The identifier of the modified record.
@property (readonly, copy, nonatomic) CKRecordID *recordID;

/// The type of change to make.
@property (readonly, assign, nonatomic) CKSyncEnginePendingRecordZoneChangeType type;

@end

#pragma mark - CKSyncEnginePendingDatabaseChange

/// Describes the type of a pending database change.
API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0), watchos(10.0))
NS_REFINED_FOR_SWIFT
typedef NS_ENUM(NSInteger, CKSyncEnginePendingDatabaseChangeType) {
    CKSyncEnginePendingDatabaseChangeTypeSaveZone,
    CKSyncEnginePendingDatabaseChangeTypeDeleteZone,
};

/// An object that describes an unsent database modification.
API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0), watchos(10.0))
NS_REFINED_FOR_SWIFT
// This class should not be subclassed. If it is, Sendable may no longer apply.
NS_SWIFT_SENDABLE
@interface CKSyncEnginePendingDatabaseChange : NSObject

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

/// The identifier of the record zone to change.
@property (readonly, copy, nonatomic) CKRecordZoneID *zoneID;

/// The type of database change.
@property (readonly, assign, nonatomic) CKSyncEnginePendingDatabaseChangeType type;

@end

/// An object that describes an unsent record zone modification.
API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0), watchos(10.0))
NS_REFINED_FOR_SWIFT
CK_SUBCLASSING_RESTRICTED
NS_SWIFT_SENDABLE
@interface CKSyncEnginePendingZoneSave : CKSyncEnginePendingDatabaseChange

/// Creates a pending zone save for the specified record zone.
///
/// - Parameters:
///   - zone: The record zone to save.
///
/// - Returns: An initialized pending zone save.
- (instancetype)initWithZone:(CKRecordZone *)zone NS_SWIFT_NAME(init(_:));

/// The record zone to save.
@property (readonly, copy, nonatomic) CKRecordZone *zone;

@end

/// An object that describes an unsent record zone deletion.
API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0), watchos(10.0))
NS_REFINED_FOR_SWIFT
CK_SUBCLASSING_RESTRICTED
NS_SWIFT_SENDABLE
@interface CKSyncEnginePendingZoneDelete : CKSyncEnginePendingDatabaseChange

/// Creates a pending zone delete for the specified record zone identifier.
///
/// - Parameters:
///   - zoneID: The unique identifier of the record zone to delete.
///
/// - Returns: An initialized pending zone delete.
- (instancetype)initWithZoneID:(CKRecordZoneID *)zoneID NS_SWIFT_NAME(init(_:));

@end

NS_HEADER_AUDIT_END(nullability, sendability)
