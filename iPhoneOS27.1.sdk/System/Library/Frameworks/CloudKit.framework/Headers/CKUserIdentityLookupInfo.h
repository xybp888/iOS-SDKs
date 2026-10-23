//
//  CKUserIdentityLookupInfo.h
//  CloudKit
//
//  Copyright © 2016 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

#import <CloudKit/CKDefines.h>

@class CKRecordID;

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

/// The criteria to use when searching for discoverable iCloud users.
///
/// Use this object when you want to discover the identities of your app's users with ``CKDiscoverUserIdentitiesOperation``, or to create a share's participants with ``CKFetchShareParticipantsOperation``.
///
/// You create individual instances by providing an email address, phone number, or user record ID. Alternatively, create an array of objects all at once by using one of the convenience methods, such as ``lookupInfos(withEmails:)``.
API_AVAILABLE(macos(10.12), ios(10.0), tvos(10.0), watchos(3.0))
CK_SUBCLASSING_DEPRECATED // should not be subclassed, or Sendable may no longer apply
// NS_SWIFT_SENDABLE on macos(13.3), macCatalyst(16.4), ios(16.4), tvos(16.4), watchos(9.4)
@interface CKUserIdentityLookupInfo : NSObject <NSSecureCoding, NSCopying>
- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

/// Creates a lookup info for the specified email address.
///
/// - Parameters:
///   - emailAddress: The email address for looking up the user identity.
///
/// After you create a lookup info, use the ``CKDiscoverUserIdentitiesOperation`` operation or the  ``CKFetchShareParticipantsOperation`` operation to retrieve the corresponding user identity.
- (instancetype)initWithEmailAddress:(NSString *)emailAddress;

/// Creates a lookup info for the specified phone number.
///
/// - Parameters:
///   - phoneNumber: The phone number for looking up the user identity.
///
/// After you create a lookup info, use the ``CKDiscoverUserIdentitiesOperation`` operation or the  ``CKFetchShareParticipantsOperation`` operation to retrieve the corresponding user identity.
- (instancetype)initWithPhoneNumber:(NSString *)phoneNumber;

/// Creates a lookup info for the specified user record ID.
///
/// - Parameters:
///   - userRecordID: The user record ID for looking up the user identity.
///
/// After you create a lookup info, use the ``CKDiscoverUserIdentitiesOperation`` operation or the  ``CKFetchShareParticipantsOperation`` operation to retrieve the corresponding user identity.
- (instancetype)initWithUserRecordID:(CKRecordID *)userRecordID;

/// Returns an array of lookup infos for the specified email addresses.
///
/// - Parameters:
///   - emails: The email addresses for looking up the user identities.
///
/// Use the values that this method returns in an ``CKDiscoverUserIdentitiesOperation`` operation or an  ``CKFetchShareParticipantsOperation`` operation to retrieve the corresponding user identities.
+ (NSArray<CKUserIdentityLookupInfo *> *)lookupInfosWithEmails:(NSArray<NSString *> *)emails;

/// Returns an array of lookup infos for the specified phone numbers.
///
/// - Parameters:
///   - phoneNumbers: The phone numbers for looking up the user identities.
///
/// Use the values that this method returns in an ``CKDiscoverUserIdentitiesOperation`` operation or an  ``CKFetchShareParticipantsOperation`` operation to retrieve the corresponding user identities.
+ (NSArray<CKUserIdentityLookupInfo *> *)lookupInfosWithPhoneNumbers:(NSArray<NSString *> *)phoneNumbers;

/// Returns an array of lookup infos for the specified user record IDs.
///
/// - Parameters:
///   - recordIDs: The user record IDs for looking up the user identities.
///
/// Use the values that this method returns in an ``CKDiscoverUserIdentitiesOperation`` operation or an  ``CKFetchShareParticipantsOperation`` operation to retrieve the corresponding user identities.
+ (NSArray<CKUserIdentityLookupInfo *> *)lookupInfosWithRecordIDs:(NSArray<CKRecordID *> *)recordIDs;

/// The user's email address.
@property (nullable, readonly, copy) NSString *emailAddress;

/// The user's phone number.
@property (nullable, readonly, copy) NSString *phoneNumber;

/// The ID of the user record.
///
/// Use this value to retrieve the user record for the user identity. The user record doesn't contain any personal information about the user, by default. You can add data to the user record, but you shouldn't add anything sensitive.
@property (nullable, readonly, copy) CKRecordID *userRecordID;

@end

NS_HEADER_AUDIT_END(nullability, sendability)
