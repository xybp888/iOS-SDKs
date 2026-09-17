//
//  CKShare.h
//  CloudKit
//
//  Copyright (c) 2016 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

#import <CloudKit/CKRecord.h>
#import <CloudKit/CKShareParticipant.h>


#define CKSHARE_REQUEST_ACCESS_INTERFACES_AVAILABILITY API_AVAILABLE(macos(26.0), ios(26.0), tvos(26.0), watchos(26.0), visionos(26.0))


@class CKShareAccessRequester, CKShareBlockedIdentity, CKUserIdentityLookupInfo;

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

/// The system type that identifies a share record.
CK_EXTERN CKRecordType const CKRecordTypeShare API_AVAILABLE(macos(10.12), ios(10.0), tvos(10.0), watchos(3.0));

/// The name of a share record that manages a shared record zone.
///
/// When you create an instance of ``CKShare`` for sharing a record zone, CloudKit automatically assigns this constant as the ``CKRecord/ID/recordName`` element of the share record's ``CKRecord/recordID``. After you save the share record to iCloud, you can fetch it by reconstructing the record ID using this constant, as the following example shows:
///
/// ```swift
/// func fetchShare(
///     forZone zone: CKRecordZone,
///     completion: @escaping (Result<CKShare, any Error>) -> Void
/// ) {
///     let database = CKContainer.default().privateCloudDatabase
///
///     // Use the 'CKRecordNameZoneWideShare' constant to create the record ID.
///     let recordID = CKRecord.ID(recordName: CKRecordNameZoneWideShare,
///                                zoneID: zone.zoneID)
///
///     // Fetch the share record from the specified record zone.
///     database.fetch(withRecordID: recordID) { share, error in
///         if let error = error {
///             // If the fetch fails, inform the caller.
///             completion(.failure(error))
///         } else if let share = share as? CKShare {
///             // Otherwise, pass the fetched share record to the
///             // completion handler.
///             completion(.success(share))
///         } else {
///             fatalError("Unable to fetch record with ID: \(recordID)")
///         }
///     }
/// }
/// ```
CK_EXTERN NSString * const CKRecordNameZoneWideShare API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0), watchos(8.0));

/// The system field key for the share's title.
///
/// This predefined key is part of the `CKRecordTypeShare` schema. The out of process UI flow uses this key to send a share, and as part of the share acceptance flow. It is an optional value on a `CKShare` record.
CK_EXTERN CKRecordFieldKey const CKShareTitleKey API_AVAILABLE(macos(10.12), ios(10.0), tvos(10.0), watchos(3.0));

/// The system field key for the share's thumbnail image data.
///
/// This predefined key is part of the `CKRecordTypeShare` schema.  It is used by the out of process UI flow to send a share, and as part of the share acceptance flow.  It is an optional value on a `CKShare` record.
CK_EXTERN CKRecordFieldKey const CKShareThumbnailImageDataKey API_AVAILABLE(macos(10.12), ios(10.0), tvos(10.0), watchos(3.0));

/// The system field key for the share's type.
///
/// This predefined key is part of the `CKRecordTypeShare` schema.  It is used by the out of process UI flow to send a share, and as part of the share acceptance flow.  It is an optional value on a `CKShare` record.
CK_EXTERN CKRecordFieldKey const CKShareTypeKey API_AVAILABLE(macos(10.12), ios(10.0), tvos(10.0), watchos(3.0));

/// A specialized record type that manages a collection of shared records.
///
/// A share is a specialized record type that facilitates the sharing of one or more records with many participants. You store shareable records in a custom record zone in the user's private database. As you create records in that zone, they become eligible for record zone sharing. If you want to share a specific hierarchy of related records, rather than the entire record zone, set each record's ``CKRecord/parent`` property to define the relationship with its parent. CloudKit infers the shared hierarchy using only the ``CKRecord/parent`` property, and ignores any custom reference fields.
///
/// You create a share with either the ID of the record zone to share, or the root record, which defines the point in a record hierarchy where you want to start sharing. CloudKit shares all the records in the record zone, or every record in the hierarchy below the root. If you set the root record's ``CKRecord/parent`` property, CloudKit ignores it. A record can take part in only a single share. This applies to every record in the shared record zone or hierarchy. If a record is participating in another share, any attempt to save the share fails, and CloudKit returns an ``CKError/alreadyShared`` error.
///
/// Use ``CKModifyRecordsOperation`` to save the share to the server. The initial set of records the share includes must exist on the server or be part of the same save operation to succeed. CloudKit then updates the share's ``url`` property. Use <doc://com.apple.documentation/documentation/uikit/uicloudsharingcontroller> to present options to the user for sharing the URL. Otherwise, distribute the URL to any participants you add to the share. You can allow anyone with the URL to take part in the share by setting ``publicPermission`` to a value more permissive than ``ParticipantPermission/none``.
///
/// - Important: You must add the <doc://com.apple.documentation/documentation/bundleresources/information-property-list/cksharingsupported> key to your app's `Info.plist` file with a value of `true`. This allows the system to launch your app when a user taps or clicks the URL.
///
/// After CloudKit saves the share, a participant can fetch its corresponding metadata, which includes a reference to the share, information about the user's participation, and, for shared hierarchies, the root record's record ID. Create an instance of ``CKFetchShareMetadataOperation`` using the share's URL and add it to the container's queue to execute it. The operation returns an instance of ``Metadata`` for each URL you provide. This is only applicable if you manually process share acceptance. If a user receives the share URL and taps or clicks it, CloudKit automatically processes their participation.
///
/// To determine the configuration of a fetched share, inspect the ``CKRecord/ID/recordName`` property of its ``CKRecord/recordID``. If the value is ``CKRecordNameZoneWideShare``, the share is managing a shared record zone; otherwise, it's managing a shared record hierarchy.
///
/// ```swift
/// let isZoneWide = (metadata.share.recordID.recordName == CKRecordNameZoneWideShare)
/// ```
///
/// CloudKit limits the number of participants in a share to 100, and each participant must have an active iCloud account. You don't create participants. Instead, use <doc://com.apple.documentation/documentation/uikit/uicloudsharingcontroller> to manage a share's participants and their permissions. Alternatively, create an instance of ``CKUserIdentity/LookupInfo`` for each user. Provide the user's email address or phone number, and use ``CKFetchShareParticipantsOperation`` to fetch the corresponding participants. CloudKit queries iCloud for corresponding accounts as part of the operation. If it doesn't find an account, the server updates the participant's ``Participant/userIdentity`` to reflect that by setting the ``CKUserIdentity/hasiCloudAccount`` property to <doc://com.apple.documentation/documentation/swift/false>. CloudKit associates the participant with their iCloud account when they accept the share if they launch the process by tapping or clicking the share URL.
///
/// Participants with write permissions can modify or delete any record that you include in the share. However, only the owner can delete a shared hierarchy's root record. If a participant attempts to delete the share, CloudKit removes the participant. The share remains active for all other participants. If the owner deletes a share that manages a record hierarchy, CloudKit sets the root record's ``CKRecord/share`` property to `nil`. CloudKit deletes the share if the owner of the shared hierarchy deletes its root record.
///
/// You can customize the title and image the system displays when initiating a share or accepting an invitation to participate. You can also provide a custom UTI to indicate the content of the shared records. Use the keys that ``SystemFieldKey`` defines, as the following example shows:
///
/// ```swift
/// let share = CKShare(rootRecord: album)
///
/// // Configure the share so the system displays the album's
/// // name and cover when the user initiates sharing or accepts
/// // an invitation to participate.
/// share[CKShare.SystemFieldKey.title] = album["name"]
/// if let cover = album["cover"] as? UIImage, let data = cover.pngData() {
///     share[CKShare.SystemFieldKey.thumbnailImageData] = data
/// }
/// // Include a custom UTI that describes the share's content.
/// share[CKShare.SystemFieldKey.shareType] = "com.example.app.album"
/// ```
API_AVAILABLE(macos(10.12), ios(10.0), tvos(10.0), watchos(3.0))
// This class should not be subclassed. If it is, Sendable may no longer apply.
// NS_SWIFT_SENDABLE on macos(14.0), ios(17.0), tvos(17.0), watchos(10.0)
@interface CKShare : CKRecord <NSSecureCoding, NSCopying>

/// Creates a new share for the specified record.
///
/// - Parameters:
///   - rootRecord: The record to share.
///
/// When saving a newly created ``CKShare``, you save both the share and its ``CKShare/Metadata/rootRecord`` in the same ``CKModifyRecordsOperation`` batch.
- (instancetype)initWithRootRecord:(CKRecord *)rootRecord;

/// Creates a new share for the specified record and record ID.
///
/// - Parameters:
///   - rootRecord: The record to share.
///   - shareID: The ``CKRecord/ID`` for the share.
///
/// When saving a newly created ``CKShare``, you save both the share and its ``CKShare/Metadata/rootRecord`` in the same ``CKModifyRecordsOperation`` batch.
- (instancetype)initWithRootRecord:(CKRecord *)rootRecord shareID:(CKRecordID *)shareID NS_DESIGNATED_INITIALIZER;

/// Creates a new share for the specified record zone.
///
/// - Parameters:
///   - recordZoneID: The ID of the record zone to share.
///
/// A shared record zone must have the ``CKRecordZone/Capabilities/zoneWideSharing`` capability. Custom record zones that you create in the user's private database have this capability by default. A record zone, and the records it contains, can take part in only a single share.
///
/// After accepting a share invite, CloudKit adds the records of the shared record zone to a new zone in the participant's shared database. Use ``CKFetchDatabaseChangesOperation`` to fetch the ID of the new record zone. Then configure ``CKFetchRecordZoneChangesOperation`` with that record zone ID and execute the operation to fetch the records.
///
/// If you use ``CKFetchShareMetadataOperation`` to fetch the metadata for a shared record zone, the operation ignores the ``CKFetchShareMetadataOperation/shouldFetchRootRecord`` and ``CKFetchShareMetadataOperation/rootRecordDesiredKeys-3xrex`` properties because, unlike a shared record hierarchy, a record zone doesn't have a nominated root record.
- (instancetype)initWithRecordZoneID:(CKRecordZoneID *)recordZoneID NS_DESIGNATED_INITIALIZER API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0), watchos(8.0));

/// Creates a share from a serialized instance.
///
/// - Parameters:
///   - aDecoder: The coder to use when deserializing the share.
///
/// When saving a newly created ``CKShare``, you must save the share and its ``CKShare/Metadata/rootRecord`` in the same ``CKModifyRecordsOperation`` batch.
- (instancetype)initWithCoder:(NSCoder *)aDecoder NS_DESIGNATED_INITIALIZER;

/// The permission for anyone with access to the share's URL.
///
/// Setting this property's value to be more permissive than ``CKShare/ParticipantPermission/none`` allows any user with the share's URL to join. CloudKit removes all public participants when you save the share if you set the property's value to ``CKShare/ParticipantPermission/none``.
///
/// The default value is ``CKShare/ParticipantPermission/none``
@property (assign) CKShareParticipantPermission publicPermission;

/// The Uniform Resource Locator (URL) for inviting participants to the share.
///
/// This property is only available after saving a share record to the server. This URL is stable and persists across shares and reshares of the same root record.
@property (nullable, readonly, copy) NSURL *URL;

/// An array that contains the share's participants.
///
/// The property's value contains all of the share's participants that the current user has permissions to see. At a minimum, it includes the share's owner and the current user.
@property (readonly, copy) NSArray<CKShareParticipant *> *participants;

/// The participant that represents the share's owner.
@property (readonly, copy) CKShareParticipant *owner;

/// The participant that represents the current user.
@property (nullable, readonly, copy) CKShareParticipant *currentUserParticipant;

/// Adds a participant to the share.
///
/// - Parameters:
///   - participant: The participant to add to the share.
///
/// If a participant with a matching ``CKShare/Participant/userIdentity`` already exists in the share, the system updates the existing participant's properties and doesn't add a new participant.
///
/// To modify the list of participants, a share's ``CKShare/publicPermission`` must be ``CKShare/ParticipantPermission/none``. You can't mix and match public and private users in the same share. You can only add certain participant types with this API. See ``CKShare/Participant`` for more information.
- (void)addParticipant:(CKShareParticipant *)participant;

/// Removes a participant from the share.
///
/// - Parameters:
///   - participant: The participant to remove from the share.
///
/// To modify the list of participants, a share's ``CKShare/publicPermission`` must be ``CKShare/ParticipantPermission/none``. You can't mix and match public and private users in the same share. You can only add certain participant types with this API. See ``CKShare/Participant`` for more information.
- (void)removeParticipant:(CKShareParticipant *)participant;

/// Invitation URLs that any receiver can use to claim the associated participantID and join the share.
///
/// Only available after a share record has been saved to the server for participants created via ``CKShareParticipant/oneTimeURLParticipant``.
/// One-time URLs are stable, and tied to the associated participantIDs as long as the participant is part of the share.
/// Typically, a share owner provides a ``URL`` directly to a user invited via their handle.
/// However, any user can also use a one-time URL in the same manner to fetch share metadata and accept the share.
/// After share acceptance, the one-time URL becomes functionally equivalent to the regular ``URL``.
///
/// - Parameters:
///   - participantID: The ``CKShareParticipant/participantID`` corresponding to the ``CKShareParticipant/oneTimeURLParticipant`` added to the share.
- (nullable NSURL *)oneTimeURLForParticipantID:(NSString *)participantID API_AVAILABLE(macos(15.0), ios(18.0), tvos(18.0), watchos(11.0), visionos(2.0)) NS_REFINED_FOR_SWIFT;

// These superclass-provided initializers are not allowed for CKShare.
- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)initWithRecordType:(CKRecordType)recordType NS_UNAVAILABLE;
- (instancetype)initWithRecordType:(CKRecordType)recordType recordID:(CKRecordID *)recordID NS_UNAVAILABLE;
- (instancetype)initWithRecordType:(CKRecordType)recordType zoneID:(CKRecordZoneID *)zoneID NS_UNAVAILABLE;

/// A list of all uninvited users who have requested access to this share.
///
/// When an originator or administrator allows share access requests, uninvited users can request to join the share.
/// All pending access requests appear in this array. CloudKit returns each requester with name components
/// and either an email or phone number.
///
/// Either share owners or administrators can respond to these access requests.
///
/// ### Responding to Access Requests:
///
/// - **Approve Requesters:**
///     - Fetch the participant information by running ``CKFetchShareParticipantsOperation`` with
///       the requester's ``CKShareAccessRequester/participantLookupInfo``.
///     - Add the resulting participant to the share.
///
/// - **Deny Requesters:**
///     - Use ``CloudKit/CKShare/denyRequesters(_:)`` to remove the requester from the requesters list.
///
/// - **Block Requesters:**
///     - Use ``CloudKit/CKShare/blockRequesters(_:)`` to block requesters.
///     - Blocking a requester prevents them from sending future access requests to the share.
@property (readonly, copy) NSArray<CKShareAccessRequester *> *requesters CKSHARE_REQUEST_ACCESS_INTERFACES_AVAILABILITY;

/// A list of users blocked from requesting access to this share.
///
/// Identities remain in this list until an owner or administrator calls ``CloudKit/CKShare/unblockIdentities(_:)``.
@property (readonly, copy) NSArray<CKShareBlockedIdentity *> *blockedIdentities CKSHARE_REQUEST_ACCESS_INTERFACES_AVAILABILITY;

/// Indicates whether uninvited users can request access to this share.
///
/// By default, this property is `NO`. When this property is `YES`, uninvited users can request
/// access to the share if they discover the share URL. When this property is `NO`, the server prevents uninvited users
/// from requesting access and does not indicate whether the share exists.
///
/// Only the share owner or an administrator can modify this property. If another participant attempts to modify
/// this property, CloudKit throws an exception.
@property (readwrite, assign) BOOL allowsAccessRequests CKSHARE_REQUEST_ACCESS_INTERFACES_AVAILABILITY;

/// Denies access requests from specified users.
///
/// Use this method to deny pending access requests from uninvited users. CloudKit removes denied requesters
/// from the ``CloudKit/CKShare/requesters`` array. To persist the changes, save the share to the server
/// after calling this method.
///
/// After denial, requesters can still submit new access requests unless explicitly blocked using
/// ``CloudKit/CKShare/blockRequesters(_:)``.
///
/// Only the share owner or an administrator can invoke this method. Attempts by other participants
/// result in an exception.
///
/// - Parameter requesters: An array of ``CKShareAccessRequester`` objects to deny.
- (void)denyRequesters:(NSArray<CKShareAccessRequester *> *)requesters CKSHARE_REQUEST_ACCESS_INTERFACES_AVAILABILITY;

/// Blocks specified users from requesting access to this share.
///
/// Blocking prevents users from submitting future access requests and removes existing participants from the share.
/// Blocked requesters appear in the ``CloudKit/CKShare/blockedIdentities`` array.
///
/// To persist this change, save the share to the server after calling this method.
///
/// Only the share owner or an administrator can invoke this method. Attempts by other participants
/// result in an exception.
///
/// - Parameter requesters: An array of ``CKShareAccessRequester`` objects to block.
- (void)blockRequesters:(NSArray<CKShareAccessRequester *> *)requesters CKSHARE_REQUEST_ACCESS_INTERFACES_AVAILABILITY;

/// Unblocks previously blocked users, allowing them to request access again.
///
/// Use this method to remove specified identities from the ``CKShare/blockedIdentities`` array.
/// Unblocked identities can request access again if the ``CKShare/allowsAccessRequests`` is enabled.
///
/// To persist this change, save the share to the server after calling this method.
///
/// Only the share owner or an administrator can invoke this method. Attempts by other participants
/// result in an exception.
///
/// - Parameter blockedIdentities: An array of ``CKShareBlockedIdentity`` objects to unblock.
- (void)unblockIdentities:(NSArray<CKShareBlockedIdentity *> *)blockedIdentities CKSHARE_REQUEST_ACCESS_INTERFACES_AVAILABILITY;

@end

NS_HEADER_AUDIT_END(nullability, sendability)
