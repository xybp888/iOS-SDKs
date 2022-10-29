//
//  CKAllowedSharingOptions.h
//  CKFramework
//
//  Copyright © 2022 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

#import <CloudKit/CKDefines.h>

NS_ASSUME_NONNULL_BEGIN

typedef NS_OPTIONS(NSUInteger, CKSharingParticipantAccessOption) {
    /*! If specified, the system sharing UI will allow the user to share publicly i.e. anyone with the link has access. */
    CKSharingParticipantAccessOptionAnyoneWithLink = 1 << 0,

    /*! If specified, the system sharing UI will allow the user to share privately to specified recipients. */
    CKSharingParticipantAccessOptionSpecifiedRecipientsOnly = 1 << 1,

    /*! Allow the user to configure the share with either access option. */
    CKSharingParticipantAccessOptionAny = CKSharingParticipantAccessOptionAnyoneWithLink | CKSharingParticipantAccessOptionSpecifiedRecipientsOnly,
} API_AVAILABLE(macos(13.0), ios(16.0)) API_UNAVAILABLE(watchos, tvos);

typedef NS_OPTIONS(NSUInteger, CKSharingParticipantPermissionOption) {
    /*! If specified, the system sharing UI will allow the user to grant participants read-only permissions. */
    CKSharingParticipantPermissionOptionReadOnly = 1 << 0,

    /*! If specified, the system sharing UI will allow the user to grant participants read/write permissions. */
    CKSharingParticipantPermissionOptionReadWrite = 1 << 1,

    /*! Allow the user to configure added share participants with either permission option. */
    CKSharingParticipantPermissionOptionAny = CKSharingParticipantPermissionOptionReadOnly | CKSharingParticipantPermissionOptionReadWrite,
} API_AVAILABLE(macos(13.0), ios(16.0)) API_UNAVAILABLE(watchos, tvos);

CK_EXTERN
API_AVAILABLE(macos(13.0), ios(16.0))
API_UNAVAILABLE(watchos, tvos)
@interface CKAllowedSharingOptions : NSObject <NSSecureCoding, NSCopying>
- (instancetype)initWithAllowedParticipantPermissionOptions:(CKSharingParticipantPermissionOption)allowedParticipantPermissionOptions allowedParticipantAccessOptions:(CKSharingParticipantAccessOption)allowedParticipantAccessOptions;

@property (nonatomic, assign) CKSharingParticipantPermissionOption allowedParticipantPermissionOptions;
@property (nonatomic, assign) CKSharingParticipantAccessOption allowedParticipantAccessOptions;

/*!
 Standard allowed options are most permissive i.e. @c allowedParticipantPermissionOptions = @c CKSharingParticipantPermissionOptionAny
 and @c allowedParticipantAccessOptions = @c CKSharingParticipantAccessOptionAny
 */
@property (class, nonatomic, strong, readonly) CKAllowedSharingOptions *standardOptions;
@end

NS_ASSUME_NONNULL_END


