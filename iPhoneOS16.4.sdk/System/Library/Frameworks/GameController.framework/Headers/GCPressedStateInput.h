//  
//  GCPressedStateInput.h
//  GameController
//
//  Copyright © 2021 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

@protocol GCPhysicalInputElement;

NS_ASSUME_NONNULL_BEGIN

/**
 An object conforming to \c GCPressedStateInput represents the pressed state of
 an element, typically a button.
 */
API_AVAILABLE(macos(13.0), ios(16.0), tvos(16.0))
@protocol GCPressedStateInput <NSObject>

/**
 Set this block if you want to be notified when the pressed state changes.
 */
@property (copy, nullable) void (^pressedDidChangeHandler)(__kindof id<GCPhysicalInputElement> element, id<GCPressedStateInput> input, BOOL pressed);

/**
 Buttons are mostly used in a digital sense, thus we have a recommended method
 for checking for pressed state instead of interpreting the value.
 
 As a general guideline a button is pressed if the value exceeds 0. However
 there may be hysteresis applied to counter noisy input values, thus incidental
 values around the threshold value may not trigger a change in pressed state.
 
 Other buttons may support two-stage actuation, where the button reports a
 value between 0 and 1 but is only considered pressed when its value is greater
 than some threshold other than 0.
 
 @see pressedDidChangeHandler
 */
@property (readonly, getter = isPressed) BOOL pressed;

/**
 The timestamp of the last pressed state change.
 
 This time interval is not relative to any specific point in time.  You can
 subtract a previous timestamp from the current timestamp to determine the time
 (in seconds) between changes to the value.
 */
@property (readonly) NSTimeInterval lastPressedStateTimestamp;

/**
 The interval (in seconds) between the timestamp of the last pressed state
 change and the current time.
 
 This should be treated as a lower bound of the event latency.  It may not
 include (wired or wireless) transmission latency, or latency accrued on
 the device before the event was transmitted to the host.
 */
@property (readonly) NSTimeInterval lastPressedStateLatency;

@end


NS_ASSUME_NONNULL_END
