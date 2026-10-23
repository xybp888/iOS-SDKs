//
//  CKAcceptSharesOperation.h
//  CloudKit
//
//  Copyright (c) 2014 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

#import <CloudKit/CKDatabaseOperation.h>

@class CKShare, CKShareMetadata;

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

/// An operation that confirms a user's participation in a share.
///
/// Use this operation to accept participation in one or more shares. You create the operation with an array of share metadatas, which CloudKit provides to your app when the user taps or clicks a share's ``CKShare/url``. The method CloudKit calls varies by platform and app configuration. For more information, see ``CKShare/Metadata``. You can also fetch a share's metadata using ``CKFetchShareMetadataOperation``.
///
/// If there are several metadatas, group them by their ``CKShare/Metadata/containerIdentifier`` and create an operation for each container. Then add the operation to each container's operation queue to run it. The operation executes its callbacks on a private serial queue.
///
/// The operation calls ``perShareCompletionBlock`` once for each metadata you provide. CloudKit returns the metadata and its related share, or an error if it can't accept the share. CloudKit also batches per-metadata errors. If the operation completes with errors, it returns a ``CKError/partialFailure`` error. The error stores individual errors in its <doc://com.apple.documentation/documentation/foundation/nserror/userinfo> dictionary. Use the ``CKPartialErrorsByItemIDKey`` key to extract them.
///
/// After CloudKit applies all record changes, the operation calls ``acceptSharesCompletionBlock``. When the closure executes, the server may continue processing residual tasks of the operation, such as creating the record zone in the user's private database.
///
/// The following example demonstrates how to accept a share that CloudKit provides to your window scene delegate. It shows how to create the operation, configure it, and execute it in the correct container:
///
/// ```swift
/// func windowScene(_ windowScene: UIWindowScene,
///     userDidAcceptCloudKitShareWith cloudKitShareMetadata: CKShare.Metadata) {
///
///     // Accept the share. If successful, schedule a fetch of the
///     // share's root record.
///     acceptShare(metadata: cloudKitShareMetadata) { [weak self] result in
///         switch result {
///         case .success(let recordID):
///             self?.fetchRootRecordAndNotifyObservers(recordID)
///         case .failure(let error):
///             // Handle the error...
///         }
///     }
/// }
///
/// func acceptShare(metadata: CKShare.Metadata,
///     completion: @escaping (Result<CKRecord.ID, any Error>) -> Void) {
///
///     // Create a reference to the share's container so the operation
///     // executes in the correct context.
///     let container = CKContainer(identifier: metadata.containerIdentifier)
///
///     // Create the operation using the metadata the caller provides.
///     let operation = CKAcceptSharesOperation(shareMetadatas: [metadata])
///
///     var rootRecordID: CKRecord.ID!
///     // If CloudKit accepts the share, cache the root record's ID.
///     // The completion closure handles any errors.
///     operation.perShareCompletionBlock = { metadata, share, error in
///         if let _ = share, error == nil {
///             rootRecordID = hierarchicalRootRecordID
///         }
///     }
///
///     // If the operation fails, return the error to the caller.
///     // Otherwise, return the record ID of the share's root record.
///     operation.acceptSharesCompletionBlock = { error in
///         if let error = error {
///             completion(.failure(error))
///         } else {
///             completion(.success(rootRecordID))
///         }
///     }
///
///     // Set an appropriate QoS and add the operation to the
///     // container's queue to execute it.
///     operation.qualityOfService = .utility
///     container.add(operation)
/// }
/// ```
API_AVAILABLE(macos(10.12), ios(10.0), tvos(10.0), watchos(3.0))
@interface CKAcceptSharesOperation : CKOperation

/// Creates an operation for accepting shares.
///
/// You can use this operation only once.
- (instancetype)init NS_DESIGNATED_INITIALIZER;

/// Creates an operation for accepting the specified shares.
///
/// - Parameters:
///   - shareMetadatas: The share metadatas to accept. If you specify `nil`, you must assign a value to the ``CKAcceptSharesOperation/shareMetadatas`` property before you execute the operation.
///
/// After initializing the operation, assign a handler to the ``CKAcceptSharesOperation/acceptSharesCompletionBlock`` property to process the results.
- (instancetype)initWithShareMetadatas:(NSArray<CKShareMetadata *> *)shareMetadatas;

/// The share metadatas to process.
///
/// Use this property to view or change the metadata of the shares you want to process. If you intend to specify or change the value of this property, do so before you execute the operation or submit it to a queue.
@property (nullable, copy, nonatomic) NSArray<CKShareMetadata *> *shareMetadatas;

/// The block to execute as CloudKit processes individual shares.
///
/// The closure returns no value and takes the following parameters:
///
/// - The share metadata to process.
/// - The share, or `nil` if CloudKit can't process the share metadata.
/// - If CloudKit can't process the share metadata, this parameter provides information about the failure; otherwise, it's `nil`.
///
/// The operation executes this closure once for each element in the ``CKAcceptSharesOperation/shareMetadatas`` property. Each time the closure executes, it executes serially with respect to the other closures of the operation.
///
/// If you intend to use this closure to process results, set it before you execute the operation or submit the operation to a queue.
@property (nullable, copy, nonatomic) void (^perShareCompletionBlock)(CKShareMetadata *shareMetadata, CKShare * _Nullable acceptedShare, NSError * _Nullable error)
CK_SWIFT_DEPRECATED("Use perShareResultBlock instead", macos(10.12, 12.0), ios(10.0, 15.0), tvos(10.0, 15.0), watchos(3.0, 8.0));

/// The closure to execute when the operation finishes.
///
/// The closure returns no value and takes the following parameter:
/// - An error that contains information about a problem, or `nil` if CloudKit successfully processes the shares.
///
/// The operation executes this closure only once. The closure executes on a background queue, so any tasks that require access to the main queue must dispatch accordingly.
///
/// The closure reports an error of type ``CKError/Code/partialFailure`` when it can't process some of the shares. The `userInfo` dictionary of the error contains a ``CKPartialErrorsByItemIDKey`` key that has a dictionary as its value. The keys of the dictionary are share URLs that CloudKit can't process, and the corresponding values are errors that contain information about the failures.
///
/// Set this property's value before you execute the operation or submit it to a queue.
@property (nullable, copy, nonatomic) void (^acceptSharesCompletionBlock)(NSError * _Nullable operationError)
CK_SWIFT_DEPRECATED("Use acceptSharesResultBlock instead", macos(10.12, 12.0), ios(10.0, 15.0), tvos(10.0, 15.0), watchos(3.0, 8.0));

@end

NS_HEADER_AUDIT_END(nullability, sendability)
