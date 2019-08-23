//
//  PKContact.h
//
//  Copyright © 2015 Apple, Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <Contacts/Contacts.h>

NS_CLASS_AVAILABLE_IOS(9_0) __WATCHOS_AVAILABLE(3.0)
@interface PKContact : NSObject

@property (nonatomic, strong, nullable) NSPersonNameComponents *name;

@property (nonatomic, strong, nullable) CNPostalAddress *postalAddress;
@property (nonatomic, strong, nullable) NSString        *emailAddress;
@property (nonatomic, strong, nullable) CNPhoneNumber   *phoneNumber;

// This property is now deprecated. Use the -subLocality property on [PKContact -postalAddress] instead
@property (nonatomic, retain, nullable) NSString        *supplementarySubLocality API_DEPRECATED("Use subLocality and subAdministrativeArea on -postalAddress instead", ios(9.2, 10.3), watchos(3.0, 3.2));

@end
