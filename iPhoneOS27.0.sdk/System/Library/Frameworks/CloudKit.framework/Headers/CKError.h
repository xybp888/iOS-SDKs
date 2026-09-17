//
//  CKError.h
//  CloudKit
//
//  Copyright (c) 2014 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

#import <CloudKit/CKDefines.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

API_AVAILABLE_BEGIN(macos(10.10), ios(8.0), watchos(3.0))

/// The error domain for CloudKit errors.
CK_EXTERN NSString * const CKErrorDomain;

/// The key to retrieve partial errors.
///
/// The value of this key is a dictionary that maps an item ID to an error. The type of each ID depends on where the error occurs. For example, if you receive a partial error when modifying a record, the ID is an instance of ``CKRecord/ID`` that corresponds to the record that CloudKit can't modify.
CK_EXTERN NSString * const CKPartialErrorsByItemIDKey;

/// The key to retrieve the original version of the record.
CK_EXTERN NSString * const CKRecordChangedErrorAncestorRecordKey;

/// The key to retrieve the server's version of the record.
CK_EXTERN NSString * const CKRecordChangedErrorServerRecordKey;

/// The key to retrieve the local version of the record.
CK_EXTERN NSString * const CKRecordChangedErrorClientRecordKey;

/// The key that determines whether CloudKit deletes a record zone because of a user action.
///
/// An <doc://com.apple.documentation/documentation/foundation/nsnumber> that represents a Boolean value you use to determine whether a user action causes CloudKit to delete a record zone. CloudKit adds this key to the error's `userInfo` dictionary when the error code is ``CKError/Code/zoneNotFound``.
CK_EXTERN NSString * const CKErrorUserDidResetEncryptedDataKey API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0), watchos(8.0));

/// The key to retrieve the number of seconds to wait before you retry a request.
///
/// An <doc://com.apple.documentation/documentation/foundation/nsnumber> that contains the number of seconds until you can retry a request. CloudKit adds this key to the error's <doc://com.apple.documentation/documentation/foundation/nserror/userinfo> dictionary when the error code is ``CKError/Code/serviceUnavailable`` or ``CKError/Code/requestRateLimited``.
CK_EXTERN NSString * const CKErrorRetryAfterKey;

/// The error codes that CloudKit returns.
typedef NS_ENUM(NSInteger, CKErrorCode) {
    /// A nonrecoverable error that CloudKit encounters.
    ///
    /// If you receive this error, file a [bug report](http://radar.apple.com) that includes the error log.
    CKErrorInternalError                  = 1,
    
    /// An error that occurs when an operation completes with partial failures.
    ///
    /// Examine the specific item failures, and act on the failed items. Each specific item error is from the CloudKit error domain. You can inspect the <doc://com.apple.documentation/documentation/foundation/nserror/userinfo> ``CKPartialErrorsByItemIDKey`` to see per-item errors.
    ///
    /// Note that in a custom zone, the system processes all items in an operation atomically. As a result, you may get a ``CKError/Code/batchRequestFailed`` error for all other items in an operation that don't cause an error.
    CKErrorPartialFailure                 = 2,
    
    /// An error that occurs when the network is unavailable.
    ///
    /// You can retry network failures immediately, but have your app implement a backoff period so that it doesn't attempt the same operation repeatedly.
    ///
    /// If the network is unavailable, have your app monitor for network reachability and wait to reissue the operation when the network is available again. See <doc://com.apple.documentation/documentation/cfnetwork/cfnetworkerrors> for more information.
    CKErrorNetworkUnavailable             = 3,
    
    /// An error that occurs when a network is available, but CloudKit is inaccessible.
    ///
    /// You can retry network failures immediately, but have your app implement a backoff period so that it doesn't attempt the same operation repeatedly.
    ///
    /// If the network is unavailable, have your app monitor for network reachability and wait to reissue the operation when the network is available again. See <doc://com.apple.documentation/documentation/cfnetwork/cfnetworkerrors> for more information.
    CKErrorNetworkFailure                 = 4,
    
    /// An error that occurs when you use an unknown or unauthorized container.
    CKErrorBadContainer                   = 5,
    
    /// An error that occurs when CloudKit is unavailable.
    CKErrorServiceUnavailable             = 6,
    
    /// An error that occurs when CloudKit rate-limits requests.
    ///
    /// Check for a ``CKErrorRetryAfterKey`` key in the <doc://com.apple.documentation/documentation/foundation/nserror/userinfo> dictionary of any CloudKit error that you receive. It's especially important to check for it if you receive any of these errors. Use the value of the ``CKErrorRetryAfterKey`` key as the number of seconds to wait before retrying this operation.
    CKErrorRequestRateLimited             = 7,
    
    /// An error that occurs when the app is missing a required entitlement.
    CKErrorMissingEntitlement             = 8,
    
    /// An error that occurs when CloudKit cannot authenticate the user.
    CKErrorNotAuthenticated               = 9,
    
    /// An error that occurs when the user doesn't have permission to save or fetch data.
    ///
    /// This error typically occurs in the public database in one of these circumstances:
    ///
    /// - You have roles for record types.
    /// - Your app is trying to accept a share that the user doesn't have an invitation for.
    ///
    /// Let users know they can't perform this operation. This error is nonrecoverable and you can't retry the operation.
    CKErrorPermissionFailure              = 10,
    
    /// An error that occurs when the specified record doesn't exist.
    CKErrorUnknownItem                    = 11,
    
    /// An error that occurs when the request contains invalid information.
    ///
    /// Consult the error's <doc://com.apple.documentation/documentation/foundation/nserror/userinfo> dictionary for more information about the issue.
    CKErrorInvalidArguments               = 12,
    
    /// An error that occurs when CloudKit truncates a query's results.
    CKErrorResultsTruncated API_DEPRECATED("Will not be returned", macos(10.10, 10.12), ios(8.0, 10.0), tvos(9.0, 10.0), watchos(3.0, 3.0)) = 13,
    
    /// An error that occurs when CloudKit rejects a record because the server's version is different.
    ///
    /// This error indicates that the server's version of the record is newer than the local version the client's trying to save. Your app needs to handle this error, resolve any conflicts in the record, and attempt another save of the record, if necessary.
    ///
    /// CloudKit provides your app with three copies of the record in this error's `userInfo` dictionary to assist with comparing and merging the changes:
    ///
    /// - ``CKRecordChangedErrorClientRecordKey``: The local record that the client's trying to save.
    /// - ``CKRecordChangedErrorServerRecordKey``: The record that exists on the server.
    /// - ``CKRecordChangedErrorAncestorRecordKey``: The original version of the record.
    ///
    /// When a conflict occurs, your app needs to merge all changes into the record for the ``CKRecordChangedErrorServerRecordKey`` key and attempt a new save using that record. Merging into either of the other two copies of the record results in another conflict error because those records have the old record change tag.
    CKErrorServerRecordChanged            = 14,
    
    /// An error that occurs when CloudKit rejects the request.
    ///
    /// This error is nonrecoverable.
    CKErrorServerRejectedRequest          = 15,
    
    /// An error that occurs when the system can't find the specified asset.
    CKErrorAssetFileNotFound              = 16,
    
    /// An error that occurs when the system modifies an asset while saving it.
    CKErrorAssetFileModified              = 17,
    
    /// An error that occurs when the current app version is older than the oldest allowed version.
    CKErrorIncompatibleVersion            = 18,
    
    /// An error that occurs when the server rejects the request because of a unique constraint violation.
    CKErrorConstraintViolation            = 19,
    
    /// An error that occurs when an operation cancels.
    CKErrorOperationCancelled             = 20,
    
    /// An error that occurs when the change token expires.
    CKErrorChangeTokenExpired             = 21,
    
    /// An error that occurs when the system rejects the entire batch of changes.
    ///
    /// This error occurs when an operation attempts to save multiple items in a custom zone, but one of those items encounters an error. Because custom zones are atomic, the entire batch fails. The items that cause the problem have their own errors, and all other items in the batch have a ``CKError/Code/batchRequestFailed`` error to indicate that the system can't save them.
    ///
    /// This error indicates that the system can't process the associated item due to an error in another item in the operation. Check the other per-item errors under ``CKPartialErrorsByItemIDKey`` for any that aren't ``CKError/Code/batchRequestFailed`` errors. Handle those errors, and then retry all items in the operation.
    CKErrorBatchRequestFailed             = 22,
    
    /// An error that occurs when the server is too busy to handle the record zone operation.
    ///
    /// Try the operation again in a few seconds. If you encounter this error again, increase the delay time exponentially for each subsequent retry to minimize server contention for the zone.
    ///
    /// Check for a ``CKErrorRetryAfterKey`` key in the <doc://com.apple.documentation/documentation/foundation/nserror/userinfo> dictionary of any CloudKit error that you receive. Use the value of this key as the number of seconds to wait before retrying the operation.
    CKErrorZoneBusy                       = 23,

    /// An error that occurs when the operation can't complete for the specified database.
    ///
    /// The system submitted the operation to the wrong database. Make sure you aren't submitting a share operation to the public database, or a record zone create operation to the shared database.
    CKErrorBadDatabase                    = 24,
    
    /// An error that occurs when saving a record exceeds the user's storage quota.
    ///
    /// **In the public database**: Your app's container doesn't have enough storage. Individual users can't do anything about this, but you can go to the CloudKit Dashboard to view and manage your container's storage.
    ///
    /// **In the private database**: The user doesn't have enough iCloud storage. Prompt the user to go to iCloud settings to manage their storage.
    ///
    /// **In the shared database**: The owner of the shared record zone doesn't have enough iCloud storage. The user can't do anything about this, but can contact the owner about upgrading their storage or cleaning up their iCloud account.
    CKErrorQuotaExceeded                  = 25,
    
    /// An error that occurs when the specified record zone doesn't exist.
    CKErrorZoneNotFound                   = 26,
    
    /// An error that occurs when a request's size exceeds the limit.
    ///
    /// The server can change its limits at any time, but the following are general guidelines:
    ///
    /// - 400 items (records or shares) per operation
    /// - 2 MB per request (not counting asset sizes)
    ///
    /// If your app receives ``CKError/Code/limitExceeded``, it must split the operation in half and try both requests again.
    CKErrorLimitExceeded                  = 27,
    
    /// An error that occurs when the user deletes a record zone using the Settings app.
    CKErrorUserDeletedZone                = 28,
    
    /// An error that occurs when a share has too many participants.
    ///
    /// Remove some participants before you retry the operation. Limits can change at any time, but CloudKit generally enforces a maximum of 100 participants for a share.
    CKErrorTooManyParticipants            API_AVAILABLE(macos(10.12), ios(10.0), tvos(10.0)) = 29,
    
    /// An error that occurs when CloudKit attempts to share a record with an existing share.
    ///
    /// A record can exist in only a single share at a time. This error means that one of the following conditions exists:
    ///
    /// - The record already has an existing share.
    /// - The record has a parent, and its parent has a share.
    /// - The record is a parent, and one of its children has a share.
    CKErrorAlreadyShared                  API_AVAILABLE(macos(10.12), ios(10.0), tvos(10.0)) = 30,
    
    /// An error that occurs when CloudKit can't find the target of a reference.
    CKErrorReferenceViolation             API_AVAILABLE(macos(10.12), ios(10.0), tvos(10.0)) = 31,
    
    /// An error that occurs when CloudKit rejects a request due to a managed-account restriction.
    ///
    /// The system restricts CloudKit access for this account. This is a nonrecoverable error.
    CKErrorManagedAccountRestricted       API_AVAILABLE(macos(10.12), ios(10.0), tvos(10.0)) = 32,
    
    /// An error that occurs when the user isn't a participant of the share.
    ///
    /// A fetch share metadata operation fails when the user isn't a participant of the share. However, there are invited participants on the share with email addresses or phone numbers that don't have associations with an iCloud account. The user may be able to join a share by associating one of those email addresses or phone numbers with the user's iCloud account.
    ///
    /// Call <doc://com.apple.documentation/documentation/uikit/uiapplication/openurl(_:)> on the share URL to have the user attempt to verify their information.
    CKErrorParticipantMayNeedVerification API_AVAILABLE(macos(10.12), ios(10.0), tvos(10.0)) = 33,
    
    /// An error that occurs when CloudKit is unable to maintain the network connection and provide a response.
    ///
    /// You can retry operations that are idempotent. For non-idempotent operations, you should consult server state to determine if the operation succeeded.
    CKErrorServerResponseLost             API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0), watchos(4.0)) = 34,

    /// An error that occurs when the system can't access the specified asset.
    CKErrorAssetNotAvailable              API_AVAILABLE(macos(10.13), ios(11.3), tvos(11.3), watchos(4.3)) = 35,

    /// An error that occurs when the user's iCloud account is temporarily unavailable.
    ///
    /// You receive this error when the user's iCloud account is available, but isn't ready to support CloudKit operations. Don't delete any cached data and don't enqueue any additional CloudKit operations.
    ///
    /// Checking the account status after the operation fails, assuming there are no other changes to the account's status, returns ``CKAccountStatus/temporarilyUnavailable``. Use the <doc://com.apple.documentation/documentation/foundation/nsnotification/name-swift.struct/ckaccountchanged> notification to listen for future account status changes, and retry the operation after the status becomes ``CKAccountStatus/available``.
    CKErrorAccountTemporarilyUnavailable  API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0), watchos(8.0)) = 36,
    
    /// The user is already an invited participant on this share. They must accept the existing share invitation before continuing.
    CKErrorParticipantAlreadyInvited      API_AVAILABLE(macos(26.0), ios(26.0), tvos(26.0), watchos(26.0), visionos(26.0)) = 37,
    

};

API_AVAILABLE_END // (macos(10.10), ios(8.0), watchos(3.0))

NS_HEADER_AUDIT_END(nullability, sendability)
