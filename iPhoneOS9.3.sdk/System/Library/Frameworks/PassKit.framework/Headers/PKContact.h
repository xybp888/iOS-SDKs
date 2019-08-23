//
//  PKContact.h
//
//  Copyright © 2015 Apple, Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <Contacts/Contacts.h>

NS_CLASS_AVAILABLE(NA, 9_0)
@interface PKContact : NSObject

@property (nonatomic, retain, nullable) NSPersonNameComponents *name;

@property (nonatomic, retain, nullable) CNPostalAddress *postalAddress;
@property (nonatomic, retain, nullable) NSString        *emailAddress;
@property (nonatomic, retain, nullable) CNPhoneNumber   *phoneNumber;

// CNPostalAddress does not support a distinct sublocality field. Some regions require a distinct sublocality,
// and the Apple Pay sheet will prompt users to input it. Access the sublocality value here.
@property (nonatomic, retain, nullable) NSString        *supplementarySubLocality NS_AVAILABLE_IOS(9_2);

@end
