//
//  GCDeviceHaptics.h
//  GameController
//
//  Copyright © 2020 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

#import <GameController/GCExtern.h>
#import <GameController/GCDeviceHapticsLocality.h>

@class CHHapticEngine;

NS_ASSUME_NONNULL_BEGIN

GAMECONTROLLER_EXPORT const float GCHapticDurationInfinite API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));


API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0))
@interface GCDeviceHaptics : NSObject

#ifdef __APPLE_BLEACH_SDK__
- (instancetype)init NS_UNAVAILABLE;
#endif

/**
 *  The set of supported haptic localities for this device - representing the
 *  locations of its haptic actuators.
 *
 *  @note
 *  `GCHapticsLocalityDefault` and `GCHapticsLocalityAll` are guaranteed to be
 *  supported - and they may be equivalent.
 *
 *  @see GCHapticsLocality
 */
@property (copy, readonly) NSSet<GCHapticsLocality> *supportedLocalities;

/**
 *  Creates and returns a new instance of `CHHapticEngine` with a given
 *  `GCHapticsLocality`.  Any patterns you send to this engine will play on
 *  all specified actuators.
 *
 *  Often times, it is best to use `GCHapticsLocalityDefault`.  Engines created
 *  with the default locality will give users an expected haptic experience.
 *  On most game controllers, this will cause your haptic patterns to play on
 *  the handles. If you want to play different experiences on different
 *  actuators (for example, using the left handle actuator as a woofer and the
 *  right actuator as a tweeter), you can create multiple engines (for example,
 *  one with a `GCHapticsLocalityLeftHandle` locality and another with a
 *  `GCHapticsLocalityRightHandle` locality).
 *
 *  @see CHHapticEngine
 *  @see GCHapticsLocality
 */
- (nullable CHHapticEngine *)createEngineWithLocality:(GCHapticsLocality)locality;

@end

NS_ASSUME_NONNULL_END
