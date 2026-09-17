//
//  CKSyncEngineConfiguration.h
//  CloudKit
//
//  Copyright © 2020 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

#import <CloudKit/CKSubscription.h>

@class CKDatabase, CKSyncEngineStateSerialization;
@protocol CKSyncEngineDelegate;

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

/// A type that configures the attributes and behavior of a sync engine.
API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0), watchos(10.0))
NS_REFINED_FOR_SWIFT
CK_SUBCLASSING_RESTRICTED
NS_SWIFT_SENDABLE
@interface CKSyncEngineConfiguration : NSObject

/// Creates a configuration for the specified database and serialized state.
///
/// - Parameters:
///   - database: The database to sync — either a person's private database or their shared database.
///   - stateSerialization: If this is the first initialization of the associated sync engine, specify `nil`; otherwise, specify the state from the most recent ``CKSyncEngineStateUpdateEvent`` that your delegate handled.
///   - delegate: The object that provides the records to sync and handles any related events.
///
/// - Returns: An initialized configuration instance.
- (instancetype)initWithDatabase:(CKDatabase *)database
              stateSerialization:(nullable CKSyncEngineStateSerialization *)stateSerialization
                        delegate:(id<CKSyncEngineDelegate>)delegate;

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

/// The associated database.
///
/// Multiple sync engines can run in the same process, each targeting a different database.
/// For example, you may use one sync engine for a person's private database and another for their shared database.
///
/// - Important: When using CloudKit's production environment, don't create multiple sync engines that target the same database.
/// You can, however, do this in the development environment to help testing — for example, to simulate multiple devices syncing back and forth.
@property (strong) CKDatabase *database;

/// The sync engine's serialized state.
///
/// This property returns the value you specify for the initializer's `stateSerialization` parameter.
/// If you choose to set this property after initialization, assign the state from the most recent ``CKSyncEngineStateUpdateEvent`` handled by your delegate.
/// However, if this is the first initialization of the associated sync engine, specify `nil` instead.
///
/// The default value is `nil`.
@property (nullable, copy) CKSyncEngineStateSerialization *stateSerialization;

/// The object that provides the records to sync and handles any related events.
@property (weak) id<CKSyncEngineDelegate> delegate;

/// A Boolean value that determines whether the engine syncs automatically.
///
/// By default, the sync engine uses the system scheduler to automatically schedule both send and fetch operations.
/// If an operation fails due to a recoverable error, such as a network failure, or when the server is enforcing request limits, the engine reschedules those operations as necessary.
/// Unless you have a specific need, prefer to use the default behavior in your app.
///
/// If you set this property's value to <doc://com.apple.documentation/documentation/swift/false>, use ``CKSyncEngine/fetchChangesWithCompletionHandler:`` and ``CKSyncEngine/sendChangesWithCompletionHandler:`` to invoke immediate sync operations, allowing for more control over when your app syncs its records.
/// For example, you may want to sync at a specific time of day, or deterministically simulate certain conditions in your unit tests.
///
/// The default value is <doc://com.apple.documentation/documentation/swift/true>.
@property (assign) BOOL automaticallySync;

/// The subscription identifier for the associated database.
///
/// By default, a sync engine attempts to discover an existing subscription for the synced database.
/// If one isn't found, the engine creates an internal ``CKDatabaseSubscription`` and uses that to receive notifications about remote record changes.
///
/// If you require the sync engine to use a specific database subscription, assign that subscription's identifier to this property.
/// Doing so enables your app to be backwards compatible if you're migrating to ``CKSyncEngine-4b4w9`` from a custom CloudKit sync implementation.
///
/// The default value is `nil`.
@property (nullable, copy) CKSubscriptionID subscriptionID;

@end

NS_HEADER_AUDIT_END(nullability, sendability)
