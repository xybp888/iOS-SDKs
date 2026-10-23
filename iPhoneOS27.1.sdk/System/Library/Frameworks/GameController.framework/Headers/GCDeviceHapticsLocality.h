//  
//  GCDeviceHapticsLocality.h
//  GameController
//
//  Copyright © 2025 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/**
 *  A GCHapticsLocality represents the locations of haptic actuators on a
 *  device.  You can create a haptic engine with a given GCHapticsLocality,
 *  and any patterns you send to that engine will play on all specified
 *  actuators.
 *
 *  ```
 *  CHHapticEngine *engine = [controller.haptics createEngineWithLocality:GCHapticsLocalityDefault];
 *  ```
 *
 *  @see GCDeviceHaptics
 */
typedef NSString* GCHapticsLocality NS_TYPED_ENUM API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));

GAMECONTROLLER_EXPORT GCHapticsLocality const GCHapticsLocalityDefault API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0)); // guaranteed to be supported
GAMECONTROLLER_EXPORT GCHapticsLocality const GCHapticsLocalityAll API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0)); // guaranteed to be supported

GAMECONTROLLER_EXPORT GCHapticsLocality const GCHapticsLocalityHandles API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));
GAMECONTROLLER_EXPORT GCHapticsLocality const GCHapticsLocalityLeftHandle API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));
GAMECONTROLLER_EXPORT GCHapticsLocality const GCHapticsLocalityRightHandle API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));

GAMECONTROLLER_EXPORT GCHapticsLocality const GCHapticsLocalityTriggers API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));
GAMECONTROLLER_EXPORT GCHapticsLocality const GCHapticsLocalityLeftTrigger API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));
GAMECONTROLLER_EXPORT GCHapticsLocality const GCHapticsLocalityRightTrigger API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));

NS_ASSUME_NONNULL_END
