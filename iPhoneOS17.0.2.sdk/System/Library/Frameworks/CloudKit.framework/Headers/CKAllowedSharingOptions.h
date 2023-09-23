//
//  CKAllowedSharingOptions.h
//  CKFramework
//
//  Copyright © 2022 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

#import <CloudKit/CKDefines.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

typedef NS_OPTIONS(NSUInteger, CKSharingParticipantAccessOption) {
    /*! If specified, the system sharing UI will allow the user to share publicly i.e. anyone with the link has access. */
    CKSharingParticipantAccessOptionAnyoneWithLink = 1 << 0,

    /*! If specified, the system sharing UI will allow the user to share privately to specified recipients. */
    CKSharingParticipantAccessOptionSpecifiedRecipientsOnly = 1 << 1,

    /*! Allow the user to configure the share with either access option. */
    CKSharingParticipantAccessOptionAny = CKSharingParticipantAccessOptionAnyoneWithLink | CKSharingParticipantAccessOptionSpecifiedRecipientsOnly,
} API_AVAILABLE(macos(13.0), ios(16.0)) API_UNAVAILABLE(tvos, watchos);

typedef NS_OPTIONS(NSUInteger, CKSharingParticipantPermissionOption) {
    /*! If specified, the system sharing UI will allow the user to grant participants read-only permissions. */
    CKSharingParticipantPermissionOptionReadOnly = 1 << 0,

    /*! If specified, the system sharing UI will allow the user to grant participants read/write permissions. */
    CKSharingParticipantPermissionOptionReadWrite = 1 << 1,

    /*! Allow the user to configure added share participants with either permission option. */
    CKSharingParticipantPermissionOptionAny = CKSharingParticipantPermissionOptionReadOnly | CKSharingParticipantPermissionOptionReadWrite,
} API_AVAILABLE(macos(13.0), ios(16.0)) API_UNAVAILABLE(tvos, watchos);

API_AVAILABLE(macos(13.0), ios(16.0))
API_UNAVAILABLE(tvos, watchos)
CK_SUBCLASSING_DEPRECATED // should not be subclassed, or Sendable may no longer apply
// NS_SWIFT_SENDABLE on macos(13.3), macCatalyst(16.4), ios(16.4))
@interface CKAllowedSharingOptions : NSObject <NSSecureCoding, NSCopying>
- (instancetype)initWithAllowedParticipantPermissionOptions:(CKSharingParticipantPermissionOption)allowedParticipantPermissionOptions allowedParticipantAccessOptions:(CKSharingParticipantAccessOption)allowedParticipantAccessOptions;

@property (assign) CKSharingParticipantPermissionOption allowedParticipantPermissionOptions;
@property (assign) CKSharingParticipantAccessOption allowedParticipantAccessOptions;

/*!
 Standard allowed options are most permissive i.e. @c allowedParticipantPermissionOptions = @c CKSharingParticipantPermissionOptionAny
 and @c allowedParticipantAccessOptions = @c CKSharingParticipantAccessOptionAny
 */
@property (class, readonly, strong, nonatomic) CKAllowedSharingOptions *standardOptions;
@end

NS_HEADER_AUDIT_END(nullability, sendability)
