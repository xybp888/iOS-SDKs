//
//  GCControllerElement.h
//  GameController
//
//  Copyright (c) 2012 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <GameController/GCExtern.h>

NS_ASSUME_NONNULL_BEGIN

/**
 *  Elements on a GCDevice can be used for system gestures, such as showing the
 *  Game Overlay or taking a screenshot of gameplay.
 *
 *  The system gesture state represents an app preference to utilize a button
 *  with an attached system gesture for an app-specific purpose.  For example,
 *  a game streaming app may want to forward the button state to the remote
 *  device.
 *
 *  @example
 *  The Options button on an extended gamepad can be bound to take a screenshot
 *  with a long press. This occurs outside of the control of the app. If a user
 *  presses the Options button, the system gesture recognizer will run by
 *  default.  If a long press is detected, input will not be forwarded to your
 *  app (your application won't see the Options button was pressed at all).
 *  If a long press is not detected, input will be forwarded to your app, with a
 *  delay.
 *
 *  This behavior may not be desirable in certain applications, such as those
 *  that forward controller input to a remote gaming device (which may have its
 *  own screenshot function).  The app can set the `preferredSystemGestureState`
 *  of the element to `.Disabled`.  This requests the system disable its gesture
 *  recognizer - giving the app full control of the input for the element.
 *
 *  @see GCControllerElement.preferredSystemGestureState
 */
typedef NS_ENUM(NSInteger, GCSystemGestureState) {
    /** System gesture recognizers will run before input is sent to app, this
     *  is the default state */
    GCSystemGestureStateEnabled = 0,
    /** System gesture recognizers will not run at all.  Input is passed
     *  directly to the app. */
    GCSystemGestureStateDisabled = 2,
    /** Input is sent to app and processed by system gesture recognizers
     *  simultaneously.  This is no longer recommended - prefer `.Disabled`
     *  instead. */
    GCSystemGestureStateAlwaysReceive API_DEPRECATED_WITH_REPLACEMENT("GCSystemGestureStateDisabled", macos(11.0, 27.0), ios(14.0, 27.0), tvos(14.0, 27.0), visionos(1.0, 27.0)) = 1,
} NS_SWIFT_NAME(GCControllerElement.SystemGestureState) API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));

/**
 Every controller element knows which collection it belongs to and whether its input value is analog or digital.
 */
API_AVAILABLE(macos(10.9), ios(7.0), tvos(9.0))
@interface GCControllerElement : NSObject

/**
 Each element can be part of a wider collection of inputs that map to a single logical element. A directional pad (dpad)
 is a logical collection of two axis inputs and thus each axis belongs to the same collection element - the dpad.
 */
@property (nonatomic, weak, readonly, nullable) GCControllerElement *collection;

/**
 Check if the element can support more than just digital values, such as decimal ranges between 0 and 1.
 Defaults to YES for most elements.
 */
@property (nonatomic, readonly, getter = isAnalog) BOOL analog;

/**
 The element's SF Symbols name, taking input remapping into account.
 
 @note In almost all instances, you should use this over unmappedSfSymbolsName in your UI.
 */
@property (nonatomic, strong, nullable) NSString *sfSymbolsName API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));

/**
 The element's localized name, taking input remapping into account.
 
 @note In almost all instances, you should use this over unmappedLocalizedName in your UI.
 */
@property (nonatomic, strong, nullable) NSString *localizedName API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));

/**
 The element's SF Symbols name, not taking any input remapping into account.
 
 @note Use this in your games own remapping UI, or when you need to prompt a user that a given button has no mapping (sfSymbolsName is nil).
 */
@property (nonatomic, strong, nullable) NSString *unmappedSfSymbolsName API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));

/**
 The element's localized name, not taking any input remapping into account.
 
 @note Use this in your games own remapping UI, or when you need to prompt a user that a given button has no mapping (localizedName is nil).
 */
@property (nonatomic, strong, nullable) NSString *unmappedLocalizedName API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));

/**
 A set of aliases that can be used to access this element with keyed subscript notation.
 
 */
@property (nonatomic, copy, readonly) NSSet<NSString *> *aliases API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));


#pragma mark System Gestures

/**
 *  Check if the element is bound to a system gesture.
 *
 *  Defaults to NO for most elements.
 *
 *  @see preferredSystemGestureState
 */
@property (nonatomic, readonly, getter = isBoundToSystemGesture) BOOL boundToSystemGesture API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));

/**
 *  The preferred system gesture state for this element.
 *
 *  This is merely the preferred system gesture state - it is not guaranteed to
 *  be respected by the system.  It is highly recommended to leave this set to
 *  the default value, however there may be situations (for example, game
 *  streaming apps) where it is preferrable to disable system gestures.
 *
 *  Defaults to `GCSystemGestureStateEnabled`.
 *
 *  @see GCSystemGestureState
 */
@property (nonatomic, readwrite) GCSystemGestureState preferredSystemGestureState API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));

@end

NS_ASSUME_NONNULL_END
