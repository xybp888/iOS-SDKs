//
//  SALResellerAccount.h
//  ServicesAccountLinking
//
//  Created by Pete Hare on 8/7/25.
//

#ifndef SALResellerAccount_h
#define SALResellerAccount_h

#import <Foundation/Foundation.h>

// This C header provides backward compatibility via the SDK for both Swift and Objective-C clients.
// All integrations should use the ``ResellerAccount`` Swift extensions regardless of OS version.

/// Reseller account type for linking with Apple Media & Purchases accounts.
typedef struct {
    void *_reserved;
} SALResellerAccount NS_SWIFT_NAME(ResellerAccount);

/// Error domain for account registration failures.
static NSErrorDomain const SALRegistrationErrorDomain NS_SWIFT_NAME(RegistrationErrorDomain) = @"SALRegistrationErrorDomain";

/// `userInfo` key whose value is an `NSNumber` containing the server-provided retry interval
/// in seconds. Present on ``RegistrationError/rateLimited`` errors.
static NSString * const SALRegistrationErrorRetryAfterKey NS_SWIFT_NAME(RegistrationErrorRetryAfterKey) = @"retryAfter";

/// Registration error codes.
typedef NS_ERROR_ENUM(SALRegistrationErrorDomain, SALRegistrationError) {
    /// The application is not registered as an authorized partner.
    ///
    /// Contact the Apple channel partnership program to resolve.
    SALRegistrationErrorNotEligible = 0,

    /// Registration failed.
    ///
    /// This may indicate the user is not signed into an Apple Media & Purchases account
    /// or another system error occurred. Implement retry logic with appropriate user messaging.
    SALRegistrationErrorFailed = 1,

    /// The server rate-limited the request.
    ///
    /// Check the error's `userInfo` for ``RegistrationErrorRetryAfterKey`` to get the
    /// server-provided retry interval. If absent, use exponential backoff.
    SALRegistrationErrorRateLimited = 2
} NS_SWIFT_NAME(RegistrationError);

#endif /* SALResellerAccount_h */
