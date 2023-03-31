//
//  CKUserIdentityLookupInfo.h
//  CloudKit
//
//  Copyright © 2016 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

@class CKRecordID;

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

API_AVAILABLE(macos(10.12), ios(10.0), tvos(10.0), watchos(3.0))
// NS_SWIFT_SENDABLE on macos(13.3), macCatalyst(16.4), ios(16.4), tvos(16.4), watchos(9.4)
@interface CKUserIdentityLookupInfo : NSObject <NSSecureCoding, NSCopying>
- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

- (instancetype)initWithEmailAddress:(NSString *)emailAddress;
- (instancetype)initWithPhoneNumber:(NSString *)phoneNumber;
- (instancetype)initWithUserRecordID:(CKRecordID *)userRecordID;

+ (NSArray<CKUserIdentityLookupInfo *> *)lookupInfosWithEmails:(NSArray<NSString *> *)emails;
+ (NSArray<CKUserIdentityLookupInfo *> *)lookupInfosWithPhoneNumbers:(NSArray<NSString *> *)phoneNumbers;
+ (NSArray<CKUserIdentityLookupInfo *> *)lookupInfosWithRecordIDs:(NSArray<CKRecordID *> *)recordIDs;

@property (atomic, readonly, copy, nullable) NSString *emailAddress;
@property (atomic, readonly, copy, nullable) NSString *phoneNumber;
@property (atomic, readonly, copy, nullable) CKRecordID *userRecordID;
@end

NS_HEADER_AUDIT_END(nullability, sendability)
