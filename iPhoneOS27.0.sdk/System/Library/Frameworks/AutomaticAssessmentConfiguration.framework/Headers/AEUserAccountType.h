//
//  AEUserAccountType.h
//  AutomaticAssessmentConfiguration
//
//  Copyright © 2026 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/// Specifies the type of account required for an assessment session.
typedef NS_CLOSED_ENUM(NSInteger, AEUserAccountType) {
    /// No specific account type is required.
    AEUserAccountTypeAny = 0,
    /// Requires a standard user account.
    AEUserAccountTypeStandard = 1,
    /// Requires a guest user account.
    AEUserAccountTypeGuest = 2,
} NS_SWIFT_NAME(AEUserAccountType)
API_AVAILABLE(macos(27.0), macCatalyst(27.0))
API_UNAVAILABLE(ios);

NS_ASSUME_NONNULL_END
