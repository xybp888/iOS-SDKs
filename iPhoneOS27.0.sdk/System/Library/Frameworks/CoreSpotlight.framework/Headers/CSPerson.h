//
//  CSPerson.h
//  CoreSpotlight
//
//  Copyright © 2015–2026 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(macos(10.11), ios(9.0), visionos(1.0))
API_UNAVAILABLE(tvos, watchos)
@interface CSPerson : NSObject <NSSecureCoding,NSCopying>

- (instancetype)initWithDisplayName:(nullable NSString *)displayName handles:(NSArray<NSString*> *)handles handleIdentifier:(NSString *)handleIdentifier;

@property (readonly,nullable) NSString *displayName; //An optional display name for displaying this recipient

@property (readonly) NSArray<NSString*> *handles; //An array of contact handles, e.g. phone numbers

@property (readonly) NSString *handleIdentifier; //A CNContactPropertyKey to identify the type of of handle, e.g. CNContactPhoneNumbersKey

@property (copy,nullable) NSString *contactIdentifier; //If the property has already been resolved, the identifier for the Contact

@end

NS_ASSUME_NONNULL_END
