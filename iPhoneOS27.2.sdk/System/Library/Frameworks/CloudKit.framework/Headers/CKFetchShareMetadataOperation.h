//
//  CKFetchShareMetadataOperation.h
//  CloudKit
//
//  Copyright © 2016 Apple Inc. All rights reserved.
//

#import <CloudKit/CKOperation.h>
#import <CloudKit/CKRecord.h>

@class CKShareMetadata, CKFetchShareMetadataOptions;

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

/// An operation that fetches metadata for one or more shares.
///
/// Use this operation to fetch the metadata for one or more shares. A share's metadata contains the share and details about the user's participation. Fetch metadata when you want to manually accept participation in a share using ``CKAcceptSharesOperation``.
///
/// For a shared record hierarchy, the fetched metadata includes the record ID of the share's root record. Set ``shouldFetchRootRecord`` to <doc://com.apple.documentation/documentation/swift/true> to fetch the entire root record. You can further customize this behavior using ``rootRecordDesiredKeys-3xrex`` to specify which fields you want to include in your fetch. This functionality isn't applicable for a shared record zone because, unlike a shared record hierarchy, it doesn't have a nominated root record.
///
/// To run the operation, add it to any container's operation queue. Returned metadata includes the ID of the container that stores the share. The operation executes its callbacks on a private serial queue.
///
/// The operation calls ``perShareMetadataBlock`` once for each URL you provide, and CloudKit returns the metadata, or an error if the fetch fails. CloudKit also batches per-URL errors. If the operation completes with errors, it returns a ``CKError/partialFailure`` error. The error stores individual errors in its <doc://com.apple.documentation/documentation/foundation/nserror/userinfo> dictionary. Use the ``CKPartialErrorsByItemIDKey`` key to extract them.
///
/// When all of the following conditions are true, CloudKit returns a ``CKError/participantMayNeedVerification`` error:
///
/// - There are pending participants that don't have matched iCloud accounts.
/// - The current user has an active iCloud account and isn't an existing participant (pending or otherwise).
///
/// On receipt of this error, call <doc://com.apple.documentation/documentation/uikit/uiapplication/open(_:options:completionhandler:)> with the share's URL to allow CloudKit to verify the user.
///
/// The following example demonstrates how to create the operation, configure it, and then execute it using the default container's operation queue:
///
/// ```swift
/// func fetchShareMetadata(for shareURLs: [URL],
///     completion: @escaping (Result<[URL: CKShare.Metadata], any Error>) -> Void) {
///
///     var cache = [URL: CKShare.Metadata]()
///
///     // Create the fetch operation using the share URLs that
///     // the caller provides to the method.
///     let operation = CKFetchShareMetadataOperation(shareURLs: shareURLs)
///
///     // To reduce network requests, request that CloudKit
///     // includes the root record in the metadata it returns.
///     operation.shouldFetchRootRecord = true
///
///     // Cache the metadata that CloudKit returns using the
///     // share URL. This implementation ignores per-metadata
///     // fetch errors and handles any errors in the completion
///     // closure instead.
///     operation.perShareMetadataBlock = { url, metadata, _ in
///         guard let metadata = metadata else { return }
///         cache[url] = metadata
///     }
///
///     // If the operation fails, return the error to the caller.
///     // Otherwise, return the array of participants.
///     operation.fetchShareMetadataCompletionBlock = { error in
///         if let error = error {
///             completion(.failure(error))
///         } else {
///             completion(.success(cache))
///         }
///     }
///
///     // Set an appropriate QoS and add the operation to the
///     // container's queue to execute it.
///     operation.qualityOfService = .userInitiated
///     CKContainer.default().add(operation)
/// }
/// ```
API_AVAILABLE(macos(10.12), ios(10.0), tvos(10.0), watchos(3.0))
@interface CKFetchShareMetadataOperation : CKOperation

/// Creates an empty fetch share metadata operation.
- (instancetype)init NS_DESIGNATED_INITIALIZER;

/// Creates an operation for fetching the metadata for the specified shares.
///
/// - Parameters:
///   - shareURLs: The URLs of the shares. If you specify `nil`, you must assign a value to the ``CKFetchShareMetadataOperation/shareURLs`` property before you execute the operation.
///
/// After creating the operation, assign a handler to the ``CKFetchShareMetadataOperation/fetchShareMetadataCompletionBlock`` property to process the results.
- (instancetype)initWithShareURLs:(NSArray<NSURL *> *)shareURLs;

/// The URLs of the shares to fetch.
///
/// Use this property to view or change the URLs of the shares to fetch. If you intend to specify or change this property's value, do so before you execute the operation or submit it to a queue.
@property (nullable, copy, nonatomic) NSArray<NSURL *> *shareURLs;

/// A Boolean value that indicates whether to retrieve the root record.
///
/// For a shared record hierarchy, set this property to <doc://com.apple.documentation/documentation/swift/true> to include the root record in the fetched share metadata. CloudKit ignores this property for a shared record zone because, unlike a shared record hierarchy, it doesn't have a nominated root record.
///
/// The default value is <doc://com.apple.documentation/documentation/swift/false>.
@property (assign, nonatomic) BOOL shouldFetchRootRecord;

/// The fields to return when fetching the root record.
///
/// For a shared record hierarchy, and when ``CKFetchShareMetadataOperation/shouldFetchRootRecord`` is <doc://com.apple.documentation/documentation/swift/true>, set this property to specify which of the root record's fields the operation fetches. Use `nil` to fetch the entire record. CloudKit ignores this property for a shared record zone because, unlike a hierarchy, it doesn't have a nominated root record.
///
/// The default value is `nil`.
@property (nullable, copy, nonatomic) NSArray<CKRecordFieldKey> *rootRecordDesiredKeys;

/// The closure to execute as the operation fetches individual shares.
///
/// The closure returns no value and takes the following parameters:
///
/// - The share's URL.
/// - The share metadata, or `nil` if CloudKit can't fetch the metadata.
/// - If CloudKit can't fetch the share metadata, this parameter provides information about the failure; otherwise, it's `nil`.
///
/// The operation executes this closure once for each URL in the ``CKFetchShareMetadataOperation/shareURLs`` property. Each time the closure executes, it executes serially with respect to the other closures of the operation.
///
/// If you intend to use this closure to process results, set it before you execute the operation or submit the operation to a queue.
@property (nullable, copy, nonatomic) void (^perShareMetadataBlock)(NSURL *shareURL, CKShareMetadata * _Nullable shareMetadata, NSError * _Nullable error)
CK_SWIFT_DEPRECATED("Use perShareMetadataResultBlock instead", macos(10.12, 12.0), ios(10.0, 15.0), tvos(10.0, 15.0), watchos(3.0, 8.0));

/// The closure to execute when the operation finishes.
///
/// The closure returns no value and takes the following parameter:
///
/// - An error that contains information about a problem, or `nil` if CloudKit successfully fetches the metadatas.
///
/// The operation executes this closure only once. The closure executes on a background queue, so any tasks that require access to the main queue must dispatch accordingly.
///
/// The closure reports an error of type ``CKError/Code/partialFailure`` when it can't fetch some of the metadatas. The `userInfo` dictionary of the error contains a ``CKPartialErrorsByItemIDKey`` key that has a dictionary as its value. The keys of the dictionary identify the metadatas that CloudKit can't fetch, and the corresponding values are errors that contain information about the failures.
///
/// Set this property's value before you execute the operation or submit it to a queue.
@property (nullable, copy, nonatomic) void (^fetchShareMetadataCompletionBlock)(NSError * _Nullable operationError)
CK_SWIFT_DEPRECATED("Use fetchShareMetadataResultBlock instead", macos(10.12, 12.0), ios(10.0, 15.0), tvos(10.0, 15.0), watchos(3.0, 8.0));

@end

NS_HEADER_AUDIT_END(nullability, sendability)
