//
//  AEMenuBarItem.h
//  AutomaticAssessmentConfiguration
//
//  Copyright © 2026 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <AutomaticAssessmentConfiguration/AEVisibility.h>

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE_BEGIN(macos(27.0), macCatalyst(27.0))
API_UNAVAILABLE_BEGIN(ios)

/// Identifies a menu bar item that can remain visible during an assessment session.
///
/// Use these constants with ``AEAssessmentConfiguration/allowedMenuBarItems`` to control which menu
/// bar items stay visible while ``AEAssessmentConfiguration/allowsMenuBar`` is enabled. To allow a
/// third-party menu extra, use its bundle identifier as the raw value.
typedef NSString *AEMenuBarItem NS_TYPED_EXTENSIBLE_ENUM NS_SWIFT_NAME(AEMenuBarItem);

/// The Battery system menu bar item.
AE_VISIBLE AEMenuBarItem const AEMenuBarItemBattery;
/// The Bluetooth system menu bar item.
AE_VISIBLE AEMenuBarItem const AEMenuBarItemBluetooth;
/// The Clock system menu bar item.
AE_VISIBLE AEMenuBarItem const AEMenuBarItemClock;
/// The Displays system menu bar item.
AE_VISIBLE AEMenuBarItem const AEMenuBarItemDisplays;
/// The Input Menu system menu bar item, which selects keyboard layouts.
AE_VISIBLE AEMenuBarItem const AEMenuBarItemKeyboard;
/// The Volume system menu bar item.
AE_VISIBLE AEMenuBarItem const AEMenuBarItemVolume;
/// The Wi-Fi system menu bar item.
AE_VISIBLE AEMenuBarItem const AEMenuBarItemWifi;

API_UNAVAILABLE_END
API_AVAILABLE_END

NS_ASSUME_NONNULL_END
