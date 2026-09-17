//
//  CKAllowedSharingOptions.h
//  CKFramework
//
//  Copyright © 2022 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

#import <CloudKit/CKDefines.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

/// An object that controls participant access options.
typedef NS_OPTIONS(NSUInteger, CKSharingParticipantAccessOption) {
    /// The permission option the system uses to control whether a user can share publicly.
    CKSharingParticipantAccessOptionAnyoneWithLink = 1 << 0,

    /// The permission option the system uses to control whether a user can share privately.
    CKSharingParticipantAccessOptionSpecifiedRecipientsOnly = 1 << 1,

    /// The permission option the system uses to control whether a user can share publicly or privately.
    CKSharingParticipantAccessOptionAny = CKSharingParticipantAccessOptionAnyoneWithLink | CKSharingParticipantAccessOptionSpecifiedRecipientsOnly,
} API_AVAILABLE(macos(13.0), ios(16.0)) API_UNAVAILABLE(tvos, watchos);

/// An object that controls participant permission options.
typedef NS_OPTIONS(NSUInteger, CKSharingParticipantPermissionOption) {
    /// The permission option the system uses to control whether a user can grant read-only access.
    CKSharingParticipantPermissionOptionReadOnly = 1 << 0,

    /// The permission option the system uses to control whether a user can grant write access.
    CKSharingParticipantPermissionOptionReadWrite = 1 << 1,

    /// The permission option the system uses to control whether a user can grant read-only or write access.
    CKSharingParticipantPermissionOptionAny = CKSharingParticipantPermissionOptionReadOnly | CKSharingParticipantPermissionOptionReadWrite,
} API_AVAILABLE(macos(13.0), ios(16.0)) API_UNAVAILABLE(tvos, watchos);

/// An object that controls participant access and permission options.
///
/// Register an instance of this class with an <doc://com.apple.documentation/documentation/foundation/nsitemprovider> or when preparing a ``CKShareTransferRepresentation/ExportedShare`` before your app invokes the share sheet. The share sheet uses the registered `CKAllowedSharingOptions` object to let the user choose between the allowed options when sharing.
API_AVAILABLE(macos(13.0), ios(16.0))
API_UNAVAILABLE(tvos, watchos)
CK_SUBCLASSING_DEPRECATED // should not be subclassed, or Sendable may no longer apply
// NS_SWIFT_SENDABLE on macos(13.3), macCatalyst(16.4), ios(16.4))
@interface CKAllowedSharingOptions : NSObject <NSSecureCoding, NSCopying>

/// Creates and initializes an allowed sharing options object.
///
/// - Parameters:
///   - allowedParticipantPermissionOptions: The ``CKSharingParticipantPermissionOption`` setting.
///   - allowedParticipantAccessOptions: The ``CKSharingParticipantAccessOption`` setting.
- (instancetype)initWithAllowedParticipantPermissionOptions:(CKSharingParticipantPermissionOption)allowedParticipantPermissionOptions allowedParticipantAccessOptions:(CKSharingParticipantAccessOption)allowedParticipantAccessOptions;

/// The permission option the system uses to control whether a user can grant read-only or write access.
@property (assign) CKSharingParticipantPermissionOption allowedParticipantPermissionOptions;

/// The permission option the system uses to control whether a user can share publicly or privately.
@property (assign) CKSharingParticipantAccessOption allowedParticipantAccessOptions;

/// Default value is NO. If set, the system sharing UI allows the user to choose whether added participants can invite others to the share.
/// CloudKit returns shares with ``CKShare/ParticipantRole/administrator-enum.case`` participants as read-only to devices running OS versions prior to this role being introduced.
/// CloudKit returns administrator participants on such read-only shares as ``CKShare/ParticipantRole/privateUser-enum.case``.
@property (assign) BOOL allowsParticipantsToInviteOthers API_AVAILABLE(macos(26.0), ios(26.0), visionos(26.0)) API_UNAVAILABLE(tvos, watchos);

/// An object set to the most permissive sharing options.
///
/// The `standardOptions` has ``CKAllowedSharingOptions/allowedParticipantPermissionOptions`` set to ``CKSharingParticipantPermissionOption/any`` and ``CKAllowedSharingOptions/allowedParticipantAccessOptions`` set to ``CKSharingParticipantAccessOption/any``.
@property (class, readonly, strong, nonatomic) CKAllowedSharingOptions *standardOptions;

/// Default value is NO. If set, the system sharing UI allows the user to configure whether participants can request access to the share.
@property (assign) BOOL allowsAccessRequests API_AVAILABLE(macos(26.0), ios(26.0), visionos(26.0)) API_UNAVAILABLE(tvos, watchos);

@end

NS_HEADER_AUDIT_END(nullability, sendability)
