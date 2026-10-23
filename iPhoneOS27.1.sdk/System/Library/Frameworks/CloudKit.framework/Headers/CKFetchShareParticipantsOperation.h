//
//  CKFetchShareParticipantsOperation.h
//  CloudKit
//
//  Copyright (c) 2014 Apple Inc. All rights reserved.
//

#import <CloudKit/CKOperation.h>

@class CKUserIdentityLookupInfo, CKShareParticipant, CKRecordID;

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

/// An operation that converts user identities into share participants.
///
/// Participants are a fundamental part of sharing in CloudKit. A participant provides information about a user and their participation in a share, which includes their identity, acceptance status, role, and permissions. The acceptance status manages the user's visibility of the shared records. The role and permissions control what actions the user can perform on those records.
///
/// You don't create participants. Instead, create an instance of ``CKUserIdentity/LookupInfo`` for each user. Provide the user's email address or phone number, and then use this operation to convert them into participants that you can add to a share. CloudKit limits the number of participants in a share to 100, and each participant must have an active iCloud account.
///
/// - Note: <doc://com.apple.documentation/documentation/uikit/uicloudsharingcontroller> provides a consistent and familiar experience for managing a share's participants and their permissions. Only use this operation when you want to provide an app-specific approach.
///
/// CloudKit queries iCloud for corresponding accounts as part of the operation. If it doesn't find an account, the server updates the participant's ``CKShare/Participant/userIdentity`` to reflect that by setting the ``CKUserIdentity/hasiCloudAccount`` property to <doc://com.apple.documentation/documentation/swift/false>. CloudKit associates a participant with their iCloud account when they accept the share.
///
/// Anyone with the URL of a public share can become a participant in that share. For a private share, the owner manages its participants. A participant can't accept a private share unless the owner adds them first.
///
/// To run the operation, add it to the container's operation queue. The operation executes its callbacks on a private serial queue.
///
/// The following example demonstrates how to create the operation, configure it, and then execute it using the default container's operation queue:
///
/// ```swift
/// func fetchParticipants(for lookupInfos: [CKUserIdentity.LookupInfo],
///     completion: @escaping (Result<[CKShare.Participant], any Error>) -> Void) {
///
///     var participants = [CKShare.Participant]()
///
///     // Create the operation using the lookup objects
///     // that the caller provides to the method.
///     let operation = CKFetchShareParticipantsOperation(
///         userIdentityLookupInfos: lookupInfos)
///
///     // Collect the participants as CloudKit generates them.
///     operation.shareParticipantFetchedBlock = { participant in
///         participants.append(participant)
///     }
///
///     // If the operation fails, return the error to the caller.
///     // Otherwise, return the array of participants.
///     operation.fetchShareParticipantsCompletionBlock = { error in
///         if let error = error {
///             completion(.failure(error))
///         } else {
///             completion(.success(participants))
///         }
///     }
///
///     // Set an appropriate QoS and add the operation to the
///     // container's queue to execute it.
///     operation.qualityOfService = .userInitiated
///     CKContainer.default().add(operation)
/// }
/// ```
///
/// The operation calls ``shareParticipantFetchedBlock`` once for each item you provide, and CloudKit returns the participant, or an error if it can't generate a participant. CloudKit also batches per-participant errors. If the operation completes with errors, it returns a ``CKError/partialFailure`` error. The error stores the individual errors in its <doc://com.apple.documentation/documentation/foundation/nserror/userinfo> dictionary. Use the ``CKPartialErrorsByItemIDKey`` key to extract them.
API_AVAILABLE(macos(10.12), ios(10.0), tvos(10.0), watchos(3.0))
@interface CKFetchShareParticipantsOperation : CKOperation

/// Creates an empty operation.
///
/// You can use this operation only once.
///
/// - Note: If you don't set ``CKFetchShareParticipantsOperation/userIdentityLookupInfos`` prior to executing the operation, it returns immediately with no results.
- (instancetype)init NS_DESIGNATED_INITIALIZER;

/// Creates an operation for generating share participants from the specified user data.
///
/// - Parameters:
///   - userIdentityLookupInfos: The user data for the participants. If you specify `nil`, you must assign a value to the ``CKFetchShareParticipantsOperation/userIdentityLookupInfos`` property before you execute this operation.
///
/// After you create the operation, assign a handler to the ``CKFetchShareParticipantsOperation/fetchShareParticipantsCompletionBlock`` property to process the results.
- (instancetype)initWithUserIdentityLookupInfos:(NSArray<CKUserIdentityLookupInfo *> *)userIdentityLookupInfos;

/// The user data for the participants.
///
/// Use this property to view or change the participants user data. If you intend to specify or change the value of this property, do so before you execute the operation or submit it to a queue.
///
/// - Note: If you don't set ``CKFetchShareParticipantsOperation/userIdentityLookupInfos`` prior to executing the operation, it returns immediately with no results.
@property (nullable, copy, nonatomic) NSArray<CKUserIdentityLookupInfo *> *userIdentityLookupInfos;

/// The closure to execute as the operation generates individual participants.
///
/// The closure returns no value and takes the following parameters:
///
/// - The participant that the operation generates.
///
/// The operation executes this closure once for each item of user data in the ``CKFetchShareParticipantsOperation/userIdentityLookupInfos`` property. Each time the closure executes, it executes serially with respect to the other closures of the operation.
///
/// If you intend to use this closure to process results, set it before you execute the operation or submit the operation to a queue.
@property (nullable, copy, nonatomic) void (^shareParticipantFetchedBlock)(CKShareParticipant *participant) API_DEPRECATED("Use perShareParticipantCompletionBlock instead, which surfaces per-share-participant errors", macos(10.12, 12.0), ios(10.0, 15.0), tvos(10.0, 15.0), watchos(3.0, 8.0));

/// The closure to execute as the operation generates individual participants.
///
/// The closure returns no value and takes the following parameters:
///
/// - The lookup info of the share participant.
/// - The generated share participant, or `nil` if CloudKit can't generate the share participant.
/// - If CloudKit can't generate the share participant, this parameter provides information about the failure; otherwise, it's `nil`.
///
/// The operation executes this closure once for each item of user data in the ``CKFetchShareParticipantsOperation/userIdentityLookupInfos`` property. Each time the closure executes, it executes serially with respect to the other closures of the operation.
///
/// If you intend to use this closure to process results, set it before you execute the operation or submit the operation to a queue.
@property (nullable, copy, nonatomic) void (^perShareParticipantCompletionBlock)(CKUserIdentityLookupInfo *lookupInfo, CKShareParticipant * _Nullable participant, NSError * _Nullable error) NS_REFINED_FOR_SWIFT;

/// The closure to execute when the operation finishes.
///
/// The closure returns no value and takes the following parameter:
///
/// - An error that contains information about a problem, or `nil` if CloudKit successfully generates the participants.
///
/// The operation executes this closure only once. The closure executes on a background queue, so any tasks that require access to the main queue must dispatch accordingly.
///
/// The closure reports an error of type ``CKError/Code/partialFailure`` when it can't generate some of the participants. The `userInfo` dictionary of the error contains a ``CKPartialErrorsByItemIDKey`` key that has a dictionary as its value. The keys of the dictionary identify the participants that CloudKit can't generate, and the corresponding values are errors that contain information about the failures.
///
/// Set this property's value before you execute the operation or submit it to a queue.
@property (nullable, copy, nonatomic) void (^fetchShareParticipantsCompletionBlock)(NSError * _Nullable operationError)
CK_SWIFT_DEPRECATED("Use fetchShareParticipantsResultBlock instead", macos(10.12, 12.0), ios(10.0, 15.0), tvos(10.0, 15.0), watchos(3.0, 8.0));

@end

NS_HEADER_AUDIT_END(nullability, sendability)
