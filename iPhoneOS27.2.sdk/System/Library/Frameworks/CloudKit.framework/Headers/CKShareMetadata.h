//
//  CKShareMetadata.h
//  CloudKit
//
//  Copyright © 2016 Apple Inc. All rights reserved.
//

#import <CloudKit/CKDefines.h>
#import <CloudKit/CKShareParticipant.h>

@class CKShare, CKRecord, CKRecordID;

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

/// An object that describes a shared record's metadata.
///
/// A share's metadata is an intermediary object that provides access to the share, its owner, and, for a shared record hierarchy, its root record. Metadata also includes details about the current user's participation in the share.
///
/// You don't create metadata. CloudKit provides it to your app when the user taps or clicks a share's ``CKShare/url``, such as in an email or a message. The method CloudKit calls varies by platform and app configuration, and includes the following:
///
/// - For a scene-based iOS app in a running or suspended state, CloudKit calls the <doc://com.apple.documentation/documentation/uikit/uiwindowscenedelegate/windowscene(_:userdidacceptcloudkitsharewith:)> method on your window scene delegate.
/// - For a scene-based iOS app that's not running, the system launches your app in response to the tap or click, and calls the <doc://com.apple.documentation/documentation/uikit/uiscenedelegate/scene(_:willconnectto:options:)> method on your scene delegate. The `connectionOptions` parameter contains the metadata. Use its <doc://com.apple.documentation/documentation/uikit/uiscene/connectionoptions/cloudkitsharemetadata> property to access it.
/// - For an iOS app that doesn't use scenes, CloudKit calls your app delegate's <doc://com.apple.documentation/documentation/uikit/uiapplicationdelegate/application(_:userdidacceptcloudkitsharewith:)> method.
/// - For a macOS app, CloudKit calls your app delegate's <doc://com.apple.documentation/documentation/appkit/nsapplicationdelegate/application(_:userdidacceptcloudkitsharewith:)> method.
/// - For a watchOS app, CloudKit calls the <doc://com.apple.documentation/documentation/watchkit/wkextensiondelegate/userdidacceptcloudkitshare(with:)> method on your watch extension delegate.
///
/// Respond by checking the ``participantStatus`` of the provided metadata. If the status is `pending`, use ``CKAcceptSharesOperation`` to accept participation in the share. You can also fetch metadata independent of this flow using ``CKFetchShareMetadataOperation``.
///
/// For a shared record hierarchy, the ``hierarchicalRootRecordID`` property contains the ID of the share's root record. When using ``CKFetchShareMetadataOperation`` to fetch metadata, you can include the entire root record by setting the operation's ``CKFetchShareMetadataOperation/shouldFetchRootRecord`` property to <doc://com.apple.documentation/documentation/swift/true>. CloudKit then populates the ``rootRecord`` property before it returns the metadata. You can further customize this behavior using the operation's ``CKFetchShareMetadataOperation/rootRecordDesiredKeys-3xrex`` property to specify which fields to return. This functionality isn't applicable for a shared record zone because, unlike a shared record hierarchy, it doesn't have a nominated root record.
///
/// The participant properties provide the current user's acceptance status, permissions, and role. Use these values to determine what functionality to provide to the user. For example, only display editing controls for accepted participants with `readWrite` permissions.
API_AVAILABLE(macos(10.12), ios(10.0), tvos(10.0), watchos(3.0))
CK_SUBCLASSING_DEPRECATED // should not be subclassed, or Sendable may no longer apply
// NS_SWIFT_SENDABLE on macos(14.0), ios(17.0), tvos(17.0), watchos(10.0)
@interface CKShareMetadata : NSObject <NSCopying, NSSecureCoding>

- (instancetype)init CK_UNAVAILABLE("Obtain `CKShareMetadata` from `CKFetchShareMetadataOperation` or platform-specific scene / app delegate callbacks.");
+ (instancetype)new CK_UNAVAILABLE("Obtain `CKShareMetadata` from `CKFetchShareMetadataOperation` or platform-specific scene / app delegate callbacks.");

/// The ID of the share's container.
@property (readonly, copy) NSString *containerIdentifier;

/// The share that owns the metadata.
@property (readonly, copy) CKShare *share;

/// The record ID of the shared hierarchy's root record.
///
/// CloudKit populates this property only for metadata that belongs to a shared record hierarchy. If the metadata is part of a shared record zone, the property is `nil`. This is because, unlike a shared record hierarchy, a shared record zone doesn't have a nominated root record.
@property (nullable, readonly, copy) CKRecordID *hierarchicalRootRecordID API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0), watchos(8.0));

/// The share's participant role for the user who retrieves the metadata.
@property (readonly, assign) CKShareParticipantRole participantRole API_AVAILABLE(macos(10.14), ios(12.0), tvos(12.0), watchos(5.0));

/// The share's participation status for the user who retrieves the metadata.
@property (readonly, assign) CKShareParticipantAcceptanceStatus participantStatus;

/// The share's permissions for the user who retrieves the metadata.
@property (readonly, assign) CKShareParticipantPermission participantPermission;

/// The identity of the share's owner.
@property (readonly, copy) CKUserIdentity *ownerIdentity;

/// The share's root record.
///
/// This property contains the root record of the shared record hierarchy if you set the ``CKFetchShareMetadataOperation/shouldFetchRootRecord`` property of the operation that fetches the metadata to <doc://com.apple.documentation/documentation/swift/true>. You can specify which fields CloudKit returns by setting the same operation's ``CKFetchShareMetadataOperation/rootRecordDesiredKeys-3xrex`` property.
///
/// The operation ignores the ``CKFetchShareMetadataOperation/shouldFetchRootRecord`` and ``CKFetchShareMetadataOperation/rootRecordDesiredKeys-3xrex`` properties when fetching a shared record zone's metadata because, unlike a shared record hierarchy, a record zone doesn't have a nominated root record.
@property (nullable, readonly, copy) CKRecord *rootRecord;

/// The share's participation type for the user who retrieves the metadata.
@property (readonly, assign) CKShareParticipantType participantType API_OBSOLETED_WITH_REPLACEMENT("role", macos(10.12, 10.14, 16.0), ios(10.0, 12.0, 19.0), tvos(10.0, 12.0, 19.0), watchos(3.0, 5.0, 12.0));

/// The record ID of the share's root record.
///
/// @DeprecationSummary {
///     Use ``CKShare/Metadata/hierarchicalRootRecordID`` instead.
/// }
/// 
/// CloudKit populates this property only for metadata that belongs to a shared record hierarchy. If the metadata is part of a shared record zone, the property returns `nil`. This is because, unlike a shared record hierarchy, a shared record zone doesn't have a nominated root record.
@property (readonly, copy) CKRecordID *rootRecordID API_DEPRECATED_WITH_REPLACEMENT("hierarchicalRootRecordID", macos(10.12, 13.0), ios(10.0, 16.0), tvos(10.0, 16.0), watchos(3.0, 9.0));

@end

NS_HEADER_AUDIT_END(nullability, sendability)
