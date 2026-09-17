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

/* Represents a menu bar item that can be allowed during an assessment session.
 *
 * Use these constants to specify which menu bar items should remain visible when
 * `allowsMenuBar` is enabled. You can allow system items (like Wi-Fi or Clock)
 * or third-party menu extras by using their bundle identifier as the raw value.
 */
typedef NSString *AEMenuBarItem NS_TYPED_EXTENSIBLE_ENUM NS_SWIFT_NAME(AEMenuBarItem);

/* The Battery system menu bar item */
AE_VISIBLE AEMenuBarItem const AEMenuBarItemBattery;
/* The Bluetooth system menu bar item */
AE_VISIBLE AEMenuBarItem const AEMenuBarItemBluetooth;
/* The Clock system menu bar item */
AE_VISIBLE AEMenuBarItem const AEMenuBarItemClock;
/* The Displays system menu bar item */
AE_VISIBLE AEMenuBarItem const AEMenuBarItemDisplays;
/* The Input Menu system menu bar item (keyboard layouts) */
AE_VISIBLE AEMenuBarItem const AEMenuBarItemKeyboard;
/* The Volume system menu bar item */
AE_VISIBLE AEMenuBarItem const AEMenuBarItemVolume;
/* The WiFi system menu bar item */
AE_VISIBLE AEMenuBarItem const AEMenuBarItemWifi;

API_UNAVAILABLE_END
API_AVAILABLE_END

NS_ASSUME_NONNULL_END
