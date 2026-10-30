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

/// The About This Mac item, which remains visible during an assessment session whether or not
/// ``AEAssessmentConfiguration/allowedAppleMenuItems`` names it.
AE_VISIBLE AEAppleMenuItem const AEAppleMenuItemAboutThisMac;
/// The App Store item.
AE_VISIBLE AEAppleMenuItem const AEAppleMenuItemAppStore;
/// The Force Quit item, covering both the Force Quit Applications window and quitting an app outright.
AE_VISIBLE AEAppleMenuItem const AEAppleMenuItemForceQuit;
/// The Location item.
AE_VISIBLE AEAppleMenuItem const AEAppleMenuItemLocation;
/// The Lock Screen item.
AE_VISIBLE AEAppleMenuItem const AEAppleMenuItemLockScreen;
/// The Log Out item, covering both the command and its confirmation.
AE_VISIBLE AEAppleMenuItem const AEAppleMenuItemLogout;
/// The Recent Items item.
AE_VISIBLE AEAppleMenuItem const AEAppleMenuItemRecent;
/// The Restart item, covering both the command and its confirmation.
AE_VISIBLE AEAppleMenuItem const AEAppleMenuItemRestart;
/// The Shut Down item, covering both the command and its confirmation.
AE_VISIBLE AEAppleMenuItem const AEAppleMenuItemShutDown;
/// The Sleep item.
AE_VISIBLE AEAppleMenuItem const AEAppleMenuItemSleep;
/// The System Information item.
AE_VISIBLE AEAppleMenuItem const AEAppleMenuItemSystemInformation;
/// The System Settings item.
AE_VISIBLE AEAppleMenuItem const AEAppleMenuItemSystemSettings;

API_UNAVAILABLE_END
API_AVAILABLE_END

NS_ASSUME_NONNULL_END
