//
//  CKShareParticipant.h
//  CloudKit
//
//  Copyright (c) 2016 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

@class CKUserIdentity;

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

typedef NS_ENUM(NSInteger, CKShareParticipantAcceptanceStatus) {
    CKShareParticipantAcceptanceStatusUnknown,
    CKShareParticipantAcceptanceStatusPending,
    CKShareParticipantAcceptanceStatusAccepted,
    CKShareParticipantAcceptanceStatusRemoved,
} API_AVAILABLE(macos(10.12), ios(10.0), tvos(10.0), watchos(3.0));

/*! These permissions determine what share participants can do with records inside that share */
typedef NS_ENUM(NSInteger, CKShareParticipantPermission) {
    CKShareParticipantPermissionUnknown,
    CKShareParticipantPermissionNone,
    CKShareParticipantPermissionReadOnly,
    CKShareParticipantPermissionReadWrite,
} API_AVAILABLE(macos(10.12), ios(10.0), tvos(10.0), watchos(3.0));

/*! @abstract The participant type determines whether a participant can modify the list of participants on a share.
 *
 *  @discussion
 *  - Owners can add private users
 *  - Private users can access the share
 *  - Public users are "self-added" when the participant accesses the shareURL.  Owners cannot add public users.
 */
typedef NS_ENUM(NSInteger, CKShareParticipantRole) {
    CKShareParticipantRoleUnknown = 0,
    CKShareParticipantRoleOwner = 1,
    CKShareParticipantRolePrivateUser = 3,
    CKShareParticipantRolePublicUser = 4,
} API_AVAILABLE(macos(10.14), ios(12.0), tvos(12.0), watchos(5.0));

typedef NS_ENUM(NSInteger, CKShareParticipantType) {
    CKShareParticipantTypeUnknown = 0,
    CKShareParticipantTypeOwner = 1,
    CKShareParticipantTypePrivateUser = 3,
    CKShareParticipantTypePublicUser = 4,
} API_DEPRECATED_WITH_REPLACEMENT("CKShareParticipantRole", macos(10.12, 10.14), ios(10.0, 12.0), tvos(10.0, 12.0), watchos(3.0, 5.0));

API_AVAILABLE(macos(10.12), ios(10.0), tvos(10.0), watchos(3.0))
// This class should not be subclassed. If it is, Sendable may no longer apply.
// NS_SWIFT_SENDABLE on macos(14.0), ios(17.0), tvos(17.0), watchos(10.0)
@interface CKShareParticipant : NSObject <NSSecureCoding, NSCopying>

/*! Use @c CKFetchShareParticipantsOperation to create a @c CKShareParticipant object */
- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@property (readonly, copy) CKUserIdentity *userIdentity;

/*! The default participant role is @c CKShareParticipantRolePrivateUser. */
@property (assign) CKShareParticipantRole role API_AVAILABLE(macos(10.14), ios(12.0), tvos(12.0), watchos(5.0));

/*! The default participant type is @c CKShareParticipantTypePrivateUser. */
@property (assign) CKShareParticipantType type API_DEPRECATED_WITH_REPLACEMENT("role", macos(10.12, 10.14), ios(10.0, 12.0), tvos(10.0, 12.0), watchos(3.0, 5.0));

@property (readonly, assign) CKShareParticipantAcceptanceStatus acceptanceStatus;

/*! The default permission for a new participant is @c CKShareParticipantPermissionReadOnly. */
@property (assign) CKShareParticipantPermission permission;

/*! A unique identifier for this participant. */
@property (readonly, copy) NSString *participantID API_AVAILABLE(macos(10.12), ios(10.0), tvos(10.0), watchos(3.0)) NS_REFINED_FOR_SWIFT;

@end

NS_HEADER_AUDIT_END(nullability, sendability)
