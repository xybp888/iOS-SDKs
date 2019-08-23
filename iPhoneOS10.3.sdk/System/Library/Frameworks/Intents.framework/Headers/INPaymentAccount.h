//
//  INPaymentAccount.h
//  Intents
//
//  Copyright © 2016 Apple. All rights reserved.
//

#import <Foundation/Foundation.h>

#import <Intents/INAccountType.h>


NS_ASSUME_NONNULL_BEGIN

@class INSpeakableString;

API_AVAILABLE(ios(10.3), watchos(3.2)) API_UNAVAILABLE(macosx)
@interface INPaymentAccount : NSObject <NSCopying, NSSecureCoding>

- (id)init NS_UNAVAILABLE;

- (nullable instancetype)initWithNickname:(INSpeakableString *)nickname
                                   number:(nullable NSString *)accountNumber
                              accountType:(INAccountType)accountType
                         organizationName:(nullable INSpeakableString *)organizationName NS_DESIGNATED_INITIALIZER;

// e.g. "Salary deposit account"
@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) INSpeakableString *nickname;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSString *accountNumber;

@property (readonly, assign, NS_NONATOMIC_IOSONLY) INAccountType accountType;

// e.g. "Bank of Narnia"
@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) INSpeakableString *organizationName;

@end

NS_ASSUME_NONNULL_END
