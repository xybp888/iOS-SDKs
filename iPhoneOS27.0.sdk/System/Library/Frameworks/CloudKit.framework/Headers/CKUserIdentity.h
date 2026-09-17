//
//  CKUserIdentity.h
//  CloudKit
//
//  Copyright (c) 2014 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

#import <CloudKit/CKDefines.h>

@class CKRecordID, CKUserIdentityLookupInfo;

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

/// The identity of a user.
///
/// A user identity provides identifiable data about an iCloud user, including their name, user record ID, and an email address or phone number. CloudKit retrieves this information from the user's iCloud account. A user must give their consent to be discoverable before CloudKit can provide this data to your app. For more information, see ``CKContainer/requestApplicationPermission:completionHandler:``.
///
/// You don't create instances of this class. Instead, CloudKit provides them in certain contexts. A share's owner has a user identity, as does each of its participants. When creating participants, CloudKit tries to find iCloud accounts it can use to populate their identities. If CloudKit doesn't find an account, it sets the identity's ``hasiCloudAccount`` property to <doc://com.apple.documentation/documentation/swift/false>.
///
/// You can also discover the identities of your app's users by executing one of the user discovery operations: ``CKDiscoverAllUserIdentitiesOperation`` and ``CKDiscoverUserIdentitiesOperation``. Identities that CloudKit discovers using ``CKDiscoverAllUserIdentitiesOperation`` correspond to entries in the device's Contacts database. These identities contain the identifiers of their Contact records, which you can use to fetch those records from the Contacts database. For more information, see ``contactIdentifiers``.
API_AVAILABLE(macos(10.12), ios(10.0), tvos(10.0), watchos(3.0))
CK_SUBCLASSING_DEPRECATED // should not be subclassed, or Sendable may no longer apply
// NS_SWIFT_SENDABLE on macos(13.3), macCatalyst(16.4), ios(16.4), tvos(16.4), watchos(9.4)
@interface CKUserIdentity : NSObject <NSSecureCoding, NSCopying>
// Use CKDiscoverUserIdentitiesOperation or CKFetchShareParticipantsOperation to create a CKUserIdentity
- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

/// The user record ID for the corresponding user record.
@property (nullable, readonly, copy) CKRecordID *userRecordID;

/// The lookup info for retrieving the user identity.
///
/// Use this property's value to retrieve the user identity when using the ``CKDiscoverUserIdentitiesOperation`` and ``CKFetchShareParticipantsOperation`` operations.
@property (nullable, readonly, copy) CKUserIdentityLookupInfo *lookupInfo;

/// The user's name.
///
/// You can use this property to construct the user's name for display. Use the components with an instance of <doc://com.apple.documentation/documentation/foundation/personnamecomponentsformatter> to create a string representation for the current locale.
@property (nullable, readonly, copy) NSPersonNameComponents *nameComponents;

/// A Boolean value that indicates whether the user has an iCloud account.
///
/// `true` if the user identity has an iCloud account; otherwise, `false`.
@property (readonly, assign) BOOL hasiCloudAccount;

/// Identifiers that match contacts in the local Contacts database.
///
/// Identities that CloudKit discovers using ``CKDiscoverAllUserIdentitiesOperation`` correspond to entries in the local Contacts database, matching the identifier on <doc://com.apple.documentation/documentation/contacts/cncontact>.  Use these identifiers with the Contacts database to get additional information about the contacts. Multiple identifiers can exist for a single discovered user because multiple contacts can contain the same email addresses or phone numbers.
///
/// To transform these identifiers into an array of unified contact identifiers, create a predicate by calling the <doc://com.apple.documentation/documentation/contacts/cncontact/predicateforcontacts(withidentifiers:)> method, and then pass that predicate to the <doc://com.apple.documentation/documentation/contacts/cncontactstore/unifiedcontacts(matching:keystofetch:)> method.
@property (readonly, copy) NSArray<NSString *> *contactIdentifiers API_DEPRECATED("No longer supported. Please see Sharing CloudKit Data with Other iCloud Users.", macos(10.13, 15.0), ios(11.0, 18.0), watchos(4.0, 11.0));

@end

NS_HEADER_AUDIT_END(nullability, sendability)
