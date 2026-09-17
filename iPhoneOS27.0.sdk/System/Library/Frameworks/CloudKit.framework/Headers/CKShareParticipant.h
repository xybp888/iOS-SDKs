//
//  CKShareParticipant.h
//  CloudKit
//
//  Copyright (c) 2016 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

@class CKUserIdentity;

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

/// Constants that represent the status of a participant.
typedef NS_ENUM(NSInteger, CKShareParticipantAcceptanceStatus) {
    /// The participant's status is unknown.
    CKShareParticipantAcceptanceStatusUnknown,

    /// The participant's acceptance of the share request is pending.
    CKShareParticipantAcceptanceStatusPending,

    /// The participant accepted the share request.
    CKShareParticipantAcceptanceStatusAccepted,

    /// The system removed the participant from the share.
    CKShareParticipantAcceptanceStatusRemoved,
} API_AVAILABLE(macos(10.12), ios(10.0), tvos(10.0), watchos(3.0));

/// Constants that represent the permissions to grant to a share participant.
typedef NS_ENUM(NSInteger, CKShareParticipantPermission) {
    /// The participant's permissions are unknown.
    CKShareParticipantPermissionUnknown,

    /// The participant doesn't have any permissions for the share.
    CKShareParticipantPermissionNone,

    /// The participant has read-only permissions for the share.
    CKShareParticipantPermissionReadOnly,

    /// The participant has read-and-write permissions for the share.
    CKShareParticipantPermissionReadWrite,
} API_AVAILABLE(macos(10.12), ios(10.0), tvos(10.0), watchos(3.0));

/// Constants that represent the role of a share's participant.
typedef NS_ENUM(NSInteger, CKShareParticipantRole) {
    /// The participant's role is unknown.
    CKShareParticipantRoleUnknown = 0,

    /// The participant is the share's owner.
    ///
    /// The owner of a share can invite private users.
    CKShareParticipantRoleOwner = 1,

    /// The participant has the private role.
    ///
    /// A private user of a share can access the share.
    CKShareParticipantRolePrivateUser = 3,

    /// The participant has the public role.
    ///
    /// A public user of a share is self-added when accessing the share URL.
    CKShareParticipantRolePublicUser = 4,
    
    /// The participant has the administrator role.
    ///
    /// An administrator of a share can add and remove participants and change their permissions.
    ///
    /// CloudKit returns shares with `administrator` participants as read-only to devices running OS versions prior to this role being introduced.
    /// CloudKit returns administrator participants on such read-only shares as ``CloudKit/CKShareParticipantRole/CKShareParticipantRolePrivateUser``.
    CKShareParticipantRoleAdministrator API_AVAILABLE(macos(26.0), ios(26.0), tvos(26.0), watchos(26.0), visionos(26.0)) = 2,
} API_AVAILABLE(macos(10.14), ios(12.0), tvos(12.0), watchos(5.0));

/// The role of a participant.
typedef NS_ENUM(NSInteger, CKShareParticipantType) {
    /// An unknown role.
    CKShareParticipantTypeUnknown = 0,

    /// The type of an owner.
    CKShareParticipantTypeOwner = 1,

    /// The type of a private user.
    CKShareParticipantTypePrivateUser = 3,

    /// The type of a public owner.
    CKShareParticipantTypePublicUser = 4,
} API_OBSOLETED_WITH_REPLACEMENT("CKShareParticipantRole", macos(10.12, 10.14, 16.0), ios(10.0, 12.0, 19.0), tvos(10.0, 12.0, 19.0), watchos(3.0, 5.0, 12.0));

/// An object that describes a user's participation in a share.
///
/// Participants are a key element of sharing in CloudKit. A participant provides information about an iCloud user and their participation in a share, including their identity, acceptance status, permissions, and role.
///
/// The acceptance status determines the participant's visibility of the shared records. Statuses are: `pending`, `accepted`, `removed`, and `unknown`. If the status is `pending`, use ``CKAcceptSharesOperation`` to accept the share. Upon acceptance, CloudKit makes the shared records available in the participant's shared database. The records remain accessible for as long as the participant's status is `accepted`.
///
/// You don't create participants. Use the share's ``CKShare/participants`` property to access its existing participants. Use <doc://com.apple.documentation/documentation/uikit/uicloudsharingcontroller> to manage the share's participants and their permissions. Alternatively, you can generate participants using ``CKFetchShareParticipantsOperation``. Participants must have an active iCloud account.
///
/// Anyone with the URL of a public share can become a participant in that share. Participants of a public share assume the `publicUser` role. For private shares, the owner manages the participants. An owner is any participant with the `owner` role. A participant of a private share can't accept the share unless the owner adds them first. Private share participants assume the `privateUser` role. CloudKit removes any pending participants if the owner changes the share's ``CKShare/publicPermission``. CloudKit removes all participants if the new permission is `none`.
///
/// Participants with write permissions can modify or delete any record that you include in the share. However, only the owner can delete a shared hierarchy's root record. If a participant attempts to delete the share, CloudKit removes the participant. The share remains active for all other participants.
API_AVAILABLE(macos(10.12), ios(10.0), tvos(10.0), watchos(3.0))
// This class should not be subclassed. If it is, Sendable may no longer apply.
// NS_SWIFT_SENDABLE on macos(14.0), ios(17.0), tvos(17.0), watchos(10.0)
@interface CKShareParticipant : NSObject <NSSecureCoding, NSCopying>

// Use CKFetchShareParticipantsOperation to create a CKShareParticipant object
- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

/// The identity of the participant.
///
/// This property contains a reference to the user identity for the share participant.
@property (readonly, copy) CKUserIdentity *userIdentity;

/// The participant's role for the share.
@property (assign) CKShareParticipantRole role API_AVAILABLE(macos(10.14), ios(12.0), tvos(12.0), watchos(5.0));

/// The participant type.
///
/// The property controls the participant type for the share. For a list of possible values, see ``CKShareParticipantType``.
@property (assign) CKShareParticipantType type API_OBSOLETED_WITH_REPLACEMENT("role", macos(10.12, 10.14, 16.0), ios(10.0, 12.0, 19.0), tvos(10.0, 12.0, 19.0), watchos(3.0, 5.0, 12.0));

/// The current state of the user's acceptance of the share.
///
/// This property contains the current state of the participant's acceptance of the share. For a list of possible values, see ``CKShare/ParticipantAcceptanceStatus``.
@property (readonly, assign) CKShareParticipantAcceptanceStatus acceptanceStatus;

/// The participant's permission level for the share.
///
/// This property controls the permissions that the participant has for the share. For a list of possible values, see ``CKShare/ParticipantPermission``.
@property (assign) CKShareParticipantPermission permission;

/// A unique identifier for this participant.
@property (readonly, copy) NSString *participantID API_AVAILABLE(macos(10.12), ios(10.0), tvos(10.0), watchos(3.0)) NS_REFINED_FOR_SWIFT;

/// Indicates whether the participant was originally a requester that an originator or administrator approved to join the share.
@property (readonly, assign, nonatomic) BOOL isApprovedRequester API_AVAILABLE(macos(26.0), ios(26.0), tvos(26.0), watchos(26.0), visionos(26.0));

/// The date and time when an originator or administrator added this participant to the share.
///
/// CloudKit sets this timestamp when the share is successfully saved to the server.
@property (nullable, readonly, copy, nonatomic) NSDate *dateAddedToShare API_AVAILABLE(macos(26.0), ios(26.0), tvos(26.0), watchos(26.0), visionos(26.0));

/// Generate a unique URL for inviting a participant without knowing their handle
///
/// When a participant's email address / phone number / userRecordID isn't known up-front, you can add a ``CKShareParticipant/oneTimeURLParticipant``
/// to the share. Once you save the share, you can get a custom invitation link or one-time URL for the added participant via ``CKShare/oneTimeURL(for:)``.
/// Any recipient user can use this custom link to fetch share metadata and accept the share.
///
/// Note that a one-time URL participant in the ``ParticipantAcceptanceStatus/pending`` state has empty ``CKUserIdentity/nameComponents``
/// and a nil ``CKUserIdentity/lookupInfo``.
+ (instancetype)oneTimeURLParticipant NS_SWIFT_NAME(oneTimeURLParticipant()) API_AVAILABLE(macos(15.0), ios(18.0), tvos(18.0), watchos(11.0), visionos(2.0));

/// Compares two `CKShareParticipant` objects for person identity equality.
///
/// This implementation differs from typical `NSObject` `isEqual:` behavior.
/// Standard `isEqual:` implementations compare all meaningful properties for structural
/// equality. This method specifically compares identity to answer "Are these the same person?"
/// rather than "Are these participant objects identical?"
///
/// This method returns `YES` if both participants represent the same person, regardless
/// of differences in `role`, `acceptanceStatus`, `permission`, or other properties,
/// or if CloudKit determines these represent the same identity via other heuristics.
///
/// The method returns `YES` if any of these identity conditions are met:
/// - `participantID` matches (direct participant identification)
/// - `userIdentity.userRecordID` matches (same CloudKit user)
/// - `userIdentity.lookupInfo` matches (same email, phone, or user record)
///
/// Properties NOT compared (may differ between "equal" participants):
/// - `role` (owner, privateUser, publicUser)
/// - `acceptanceStatus` (invited, accepted, removed, etc.)
/// - `permission` (readOnly, readWrite, none)
/// - `dateAddedToShare`
/// - `isApprovedRequester`
///
/// - Parameter object: The object to compare against
/// - Returns: `YES` if both participants represent the same person, `NO` otherwise
///
/// - Warning: Do not assume that participants returning `YES` from `isEqual:` have
/// identical properties. Use explicit property comparisons when needed.
///
/// **Common use cases:**
///
/// Correct: Checking if person is already in share
/// ```objc
/// if ([existingParticipants containsObject:newParticipant]) {
///     // Person already exists in share (regardless of role/status)
/// }
/// ```
///
/// Incorrect: Assuming structural equality
/// ```objc
/// if ([participant1 isEqual:participant2]) {
///     // DON'T assume participant1.role == participant2.role
///     // DON'T assume same acceptanceStatus or permissions
/// }
/// ```
///
/// Correct: Explicit structural comparison when needed
/// ```objc
/// if ([participant1 isEqual:participant2] &&
///     participant1.role == participant2.role &&
///     participant1.acceptanceStatus == participant2.acceptanceStatus) {
///     // Now you have both identity AND structural equality
/// }
/// ```
- (BOOL)isEqual:(id)object;

@end

NS_HEADER_AUDIT_END(nullability, sendability)
