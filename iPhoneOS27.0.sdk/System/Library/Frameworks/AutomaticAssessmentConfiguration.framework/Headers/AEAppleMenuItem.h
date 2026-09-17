//
//  AEAppleMenuItem.h
//  AutomaticAssessmentConfiguration
//
//  Copyright © 2026 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <AutomaticAssessmentConfiguration/AEVisibility.h>

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE_BEGIN(macos(27.0), macCatalyst(27.0))
API_UNAVAILABLE_BEGIN(ios)

/// Identifies an item in the Apple menu.
///
/// Use these constants with ``AEAssessmentConfiguration/allowedAppleMenuItems``
/// to control which Apple menu items are visible during an assessment session.
///
/// - Note: ``AEAppleMenuItemAboutThisMac`` is always visible during assessment
///   sessions regardless of configuration.
typedef NSString *AEAppleMenuItem NS_TYPED_ENUM NS_SWIFT_NAME(AEAppleMenuItem);

AE_VISIBLE AEAppleMenuItem const AEAppleMenuItemAboutThisMac;
AE_VISIBLE AEAppleMenuItem const AEAppleMenuItemAppStore;
AE_VISIBLE AEAppleMenuItem const AEAppleMenuItemForceQuit;
AE_VISIBLE AEAppleMenuItem const AEAppleMenuItemLocation;
AE_VISIBLE AEAppleMenuItem const AEAppleMenuItemLockScreen;
AE_VISIBLE AEAppleMenuItem const AEAppleMenuItemLogout;
AE_VISIBLE AEAppleMenuItem const AEAppleMenuItemRecent;
AE_VISIBLE AEAppleMenuItem const AEAppleMenuItemRestart;
AE_VISIBLE AEAppleMenuItem const AEAppleMenuItemShutDown;
AE_VISIBLE AEAppleMenuItem const AEAppleMenuItemSleep;
AE_VISIBLE AEAppleMenuItem const AEAppleMenuItemSystemInformation;
AE_VISIBLE AEAppleMenuItem const AEAppleMenuItemSystemSettings;

API_UNAVAILABLE_END
API_AVAILABLE_END

NS_ASSUME_NONNULL_END
