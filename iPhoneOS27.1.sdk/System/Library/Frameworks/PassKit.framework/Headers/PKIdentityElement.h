#if !__has_include(<PassKitCore/PKIdentityElement.h>) || PK_USE_PUBLIC_PASSKIT
//
//  PKIdentityElement.h
//    PassKit
//
//  Copyright © 2022 Apple, Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/// Elements that can be requested from identity documents. Not
/// all elements are supported by all document types. If an element
/// is requested from a type that does not support it, the element
/// is ignored.
API_AVAILABLE(ios(16.0)) API_UNAVAILABLE(macos, watchos, tvos)
@interface PKIdentityElement: NSObject <NSCopying>

/// The user's given name
///
/// When requested, this element returns the given name if the identity document provides it
/// as a separate field. For documents that do not provide separated name fields (common with
/// international identity documents), this will fall back to returning the full name.
@property (class, nonatomic, readonly) PKIdentityElement *givenNameElement;

/// The user's family name
///
/// When requested, this element returns the family name if the identity document provides it
/// as a separate field. For documents that do not provide separated name fields (common with
/// international identity documents), this will fall back to returning the full name.
@property (class, nonatomic, readonly) PKIdentityElement *familyNameElement;

/// The user's full name.
///
/// For National ID and other identity documents, requesting this element returns the user's
/// full name as a single properly formatted string. The response may also include given name
/// and family name when available.
///
/// For Driver's License documents, requesting this element returns the given name and family
/// name as separate fields, but does not return a full name field. This limitation exists
/// because the mDL (mobile Driver's License) standard does not currently include a full name
/// field in its specification.
@property (class, nonatomic, readonly) PKIdentityElement *nameElement API_AVAILABLE(ios(27.0));

/// The portrait of the user on record with the issuer.
@property (class, nonatomic, readonly) PKIdentityElement *portraitElement;

/// The address on record with the issuer.
@property (class, nonatomic, readonly) PKIdentityElement *addressElement;

/// The user's height on record with the issuer.
@property (nonatomic, class, readonly) PKIdentityElement *heightElement API_AVAILABLE(ios(26.0));

/// The user's weight on record with the issuer.
@property (nonatomic, class, readonly) PKIdentityElement *weightElement API_AVAILABLE(ios(26.0));

/// The user's eye color on record with the issuer.
@property (nonatomic, class, readonly) PKIdentityElement *eyeColorElement API_AVAILABLE(ios(26.0));

/// The user's hair color on record with the issuer.
@property (nonatomic, class, readonly) PKIdentityElement *hairColorElement API_AVAILABLE(ios(26.0));

/// The user's organ donor status on record with the issuer.
@property (nonatomic, class, readonly) PKIdentityElement *organDonorStatusElement API_AVAILABLE(ios(26.0));

/// The user's veteran status on record with the issuer.
@property (nonatomic, class, readonly) PKIdentityElement *veteranStatusElement API_AVAILABLE(ios(26.0));

/// The state or government that issued the identity document.
@property (class, nonatomic, readonly) PKIdentityElement *issuingAuthorityElement;

/// The document's issue date. This is usually the issue date of the corresponding physical
/// document, if applicable.
@property (class, nonatomic, readonly) PKIdentityElement *documentIssueDateElement;

/// The document's expiration date. This is usually the expiration date of the corresponding physical
/// document, if applicable.
@property (class, nonatomic, readonly) PKIdentityElement *documentExpirationDateElement;

/// The document's DHS (U.S. Department of Homeland Security) compliance status.
///
/// This is also known as the document's "REAL ID status".
@property (class, nonatomic, readonly) PKIdentityElement *documentDHSComplianceStatusElement API_AVAILABLE(ios(17.2));

/// The document's number, as defined by the document's issuing authority.
@property (class, nonatomic, readonly) PKIdentityElement *documentNumberElement;

/// The user's driving privileges.
@property (class, nonatomic, readonly) PKIdentityElement *drivingPrivilegesElement;

/// The user's age in years.
@property (class, nonatomic, readonly) PKIdentityElement *ageElement;

/// The user's date of birth.
@property (class, nonatomic, readonly) PKIdentityElement *dateOfBirthElement;

/// The user's sex.
@property (class, nonatomic, readonly) PKIdentityElement *sexElement API_AVAILABLE(ios(17.2));

/// The signature or usual mark of the mobile document holder.
@property (class, nonatomic, readonly) PKIdentityElement *signatureUsualMarkElement API_AVAILABLE(ios(26.4), visionos(26.4));

/// The place where the mobile document holder was born.
@property (class, nonatomic, readonly) PKIdentityElement *placeOfBirthElement API_AVAILABLE(ios(26.4), visionos(26.4));

/// The mobile document holder's nationality.
@property (class, nonatomic, readonly) PKIdentityElement *nationalityElement API_AVAILABLE(ios(26.4), visionos(26.4));

/// Indicates whether the mobile document holder has temporary lawful status based on information from the U.S. Department of Homeland Security (DHS).
@property (class, nonatomic, readonly) PKIdentityElement *dhsTemporaryLawfulStatusElement API_AVAILABLE(ios(26.4), visionos(26.4));

/// Boolean indicating whether the user's age is at least the given age.
/// For example, ageThresholdElementWithAge:21 will return true if the user is at least 21 years old.
/// This value is only available for a given age if it was provided by the issuer. If this value
/// is not available, it will automatically fall back to a request for age.
+ (instancetype)ageThresholdElementWithAge:(NSInteger)age NS_SWIFT_NAME(age(atLeast:));

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END


#else
#import <TargetConditionals.h>
#import <PassKitCore/PKIdentityElement.h>
#endif