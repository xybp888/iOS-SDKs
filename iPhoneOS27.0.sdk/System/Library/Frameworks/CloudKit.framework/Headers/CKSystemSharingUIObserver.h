//
//  CKSystemSharingUIObserver.h
//  CloudKit
//
//  Copyright © 2022 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

#import <CloudKit/CKDefines.h>

@class CKContainer, CKShare, CKRecordID;

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

/// An object the system uses to monitor changes in sharing.
///
/// Initialize a `CKSystemSharingUIObserver` instance with your ``CKContainer`` when preparing to share an item using the share sheet. Use your implementation to update the local state of a shared item when your app receives a ``CKShare``, or to delete a locally cached share when the system notifies your app about a share deletion.
///
/// The system only propagates changes on the local device using `CKSystemSharingUIObserver`. The system doesn't notify your app about any remote changes on the server. For more information about how to keep your local cache in sync with remote changes, see <doc:remote-records>.
API_AVAILABLE(macos(13.0), ios(16.0))
API_UNAVAILABLE(tvos, watchos)
CK_SUBCLASSING_DEPRECATED // should not be subclassed, or Sendable may no longer apply
// NS_SWIFT_SENDABLE on macos(13.3), macCatalyst(16.4), ios(16.4)
@interface CKSystemSharingUIObserver : NSObject

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

/// Creates and initializes an observer using the provided container.
///
/// - Parameters:
///   - container: The ``CKContainer`` for the sharing observer.
- (instancetype)initWithContainer:(CKContainer *)container NS_DESIGNATED_INITIALIZER;

/// A callback block the system invokes after the success or failure of a share save by the system sharing UI.
///
/// Following a successful share save by the system sharing UI in the provided ``CKContainer``, the system invokes this callback with a `nonnull` ``CKRecord/ID``, a `nonnull` share, and a `nil` error.
///
/// If a save failure occurs due to a per-item error like ``CKError/Code/serverRecordChanged``, the system invokes this callback with a `nonnull` ``CKRecord/ID``, a `nil` share, and a `nonnull` error.
///
/// Each ``CKSystemSharingUIObserver`` instance has a private serial queue. The system uses this queue for all callback block invocations.
@property (nullable, copy) NS_SWIFT_SENDABLE void (^systemSharingUIDidSaveShareBlock)(CKRecordID *recordID, CKShare * _Nullable share, NSError * _Nullable error) NS_REFINED_FOR_SWIFT;

/// A callback block the system invokes after the success or failure of a share delete by the system sharing UI.
///
/// The system invokes this block on the success or failure of a ``CKShare`` delete when the user decides to stop sharing through the system sharing UI.
///
/// Each ``CKSystemSharingUIObserver`` instance has a private serial queue. The system uses this queue for all callback block invocations.
@property (nullable, copy) NS_SWIFT_SENDABLE void (^systemSharingUIDidStopSharingBlock)(CKRecordID *recordID, NSError * _Nullable error) NS_REFINED_FOR_SWIFT;

@end

NS_HEADER_AUDIT_END(nullability, sendability)
