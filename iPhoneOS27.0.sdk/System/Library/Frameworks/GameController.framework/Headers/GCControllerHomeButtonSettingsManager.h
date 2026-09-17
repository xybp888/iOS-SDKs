//  
//  GCControllerHomeButtonSettingsManager.h
//  GameController
//
//  Copyright © 2026 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

#import <GameController/GCExtern.h>

@class GCControllerHomeButtonSettingsManager;

NS_ASSUME_NONNULL_BEGIN

/**
 *  How the system responds to a press of the game controller Home button
 *  outside of contexts where an action of the front-most app takes priority.
 */
typedef NS_ENUM(NSInteger, GCControllerHomeButtonSettingSystemAction) {
    /** The setting value could not be retrieved.
     *
     *  This result indicates that an error occurred, typically because the
     *  app is not currently permitted to read settings state.  */
    GCControllerHomeButtonSettingSystemActionUnavailable = -1,
    /** The controller home button system action performs some other action. */
    GCControllerHomeButtonSettingSystemActionOther = 0,
    /** The controller home button system action opens the current application. */
    GCControllerHomeButtonSettingSystemActionOpenCurrentApplication = 1,
    /** System response to the game controller Home button press is
     *  disabled. */
    GCControllerHomeButtonSettingSystemActionDisabled API_AVAILABLE(macos(27.0)) API_UNAVAILABLE(ios, tvos, visionos) = NSIntegerMax,
} API_AVAILABLE(macos(27.0), ios(27.0), visionos(27.0)) API_UNAVAILABLE(tvos);


/**
 *  How the system responds to a press of the game controller Home button while
 *  your application is front-most.
 */
typedef NS_ENUM(NSInteger, GCControllerHomeButtonSettingInAppAction) {
    /** The setting value could not be retrieved.
     *
     *  This result indicates that an error occurred, typically because the
     *  app is not currently permitted to read settings state. */
    GCControllerHomeButtonSettingInAppActionUnavailable = -1,
    /** The system maintains its default handling regardless of your app's
     *  preference. */
    GCControllerHomeButtonSettingInAppActionDefault NS_SWIFT_NAME(systemDefault) = 0,
    /** The system defers its handling to your app's preference.
     *
     *  The system reponse to the game controller Home button press is disabled
     *  when the app indicates that it wants to handle the Home button
     *  press.  The app indicates that it wants to handle the Home button
     *  press by setting:
     *
     *  ```
     *  controller.physicalInputProfile.buttons[GCInputButtonHome].preferredSystemGestureState = GCSystemGestureStateDisabled;
     *  ```
     */
    GCControllerHomeButtonSettingInAppActionDefer = 1,
    /** System response to the game controller Home button press is
     *  disabled. */
    GCControllerHomeButtonSettingInAppActionDisabled API_AVAILABLE(macos(27.0)) API_UNAVAILABLE(ios, tvos, visionos) = NSIntegerMax,
} API_AVAILABLE(macos(27.0), ios(27.0), visionos(27.0)) API_UNAVAILABLE(tvos);


/**
 *  An additional returned flag indicating whether a setting has been modified
 *  by the user.
 */
typedef NS_ENUM(NSInteger, GCControllerHomeButtonSettingCustomizationStatus) {
    /** The user has not customized this setting.
     *
     *  The setting's value is the system default. */
    GCControllerHomeButtonSettingCustomizationDefault NS_SWIFT_NAME(systemDefault) = 0,
    /** The user has customized this setting at least once. */
    GCControllerHomeButtonSettingCustomizationUser,
} API_AVAILABLE(macos(27.0), ios(27.0), visionos(27.0)) API_UNAVAILABLE(tvos);


/**
 *  A hint passed to `-openControllerHomeButtonSettingsForActivity:` to
 *  indicate the reason the app is requesting to open Settings.
 *
 *  The system uses this hint to navigate to the appropriate screen in the
 *  Settings application.
 */
typedef NS_ENUM(NSInteger, GCControllerHomeButtonSettingsCustomizationActivity) {
    /** Customize the system action. */
    GCControllerHomeButtonSettingsCustomizeSystemActionActivity NS_SWIFT_NAME(customizeSystemAction) = 1,
    /** Customize the in-app action. */
    GCControllerHomeButtonSettingsCustomizeInAppActionActivity NS_SWIFT_NAME(customizeInAppAction),
} API_AVAILABLE(macos(27.0), ios(27.0), visionos(27.0)) API_UNAVAILABLE(tvos);


/**
 *  The type of the block that is scheduled after Home button settings change.
 */
typedef void(^GCControllerHomeButtonSettingsDidChangeHandler)(GCControllerHomeButtonSettingsManager *) NS_REFINED_FOR_SWIFT;


/**
 *  Access the game controller system Home button settings.
 *
 *  macOS, iOS, and visionOS allow the user to assign an action that launches a
 *  chosen application to a long press of the Home button (the logo button on
 *  PlayStation and Xbox controllers).  The \c GCControllerHomeButtonSettingsManager
 *  class allows your application to partially inspect the user's currently
 *  configured action, and to open the system game controller settings screen
 *  where the user can modify the action.
 *
 *  @note
 *  Performing operations on `GCControllerHomeButtonSettingsManager` is only
 *  permitted while a game controller is connected.
 */
API_AVAILABLE(macos(27.0), ios(27.0), visionos(27.0)) API_UNAVAILABLE(tvos) NS_REFINED_FOR_SWIFT
@interface GCControllerHomeButtonSettingsManager : NSObject

- (instancetype)initWithQueue:(nullable dispatch_queue_t)queue NS_DESIGNATED_INITIALIZER;
- (instancetype)init;

/**
 *  A block that is scheduled after Home button settings change.
 *
 *  This block is scheduled on the `queue` the
 *  `GCControllerHomeButtonSettingsManager` was initialized with.
 */
@property (atomic, copy, nullable) GCControllerHomeButtonSettingsDidChangeHandler settingsDidChangeHandler;

/**
 *  Opens the Settings app to the screen in game controller settings where
 *  the user can change the controller shortcut action.
 *
 *  @return
 *  YES if the Settings app was opened, NO if it could not be opened and
 *  \p error contains additional information.  This function returns immediately
 *  after attempting to open the Settings app.
 */
- (BOOL)openControllerHomeButtonSettingsForActivity:(GCControllerHomeButtonSettingsCustomizationActivity)activity error:(NSError * __autoreleasing *)error;

/**
 *  Get the current controller Home button system action setting.
 */
- (GCControllerHomeButtonSettingSystemAction)readControllerHomeButtonSystemAction:(GCControllerHomeButtonSettingCustomizationStatus * _Nullable)customization withError:(NSError * _Nullable __autoreleasing * _Nullable)error;
- (GCControllerHomeButtonSettingSystemAction)readControllerHomeButtonSystemActionWithError:(NSError * _Nullable __autoreleasing * _Nullable)error;

/**
 *  Get the current controller Home button in-app action setting.
 */
- (GCControllerHomeButtonSettingInAppAction)readControllerHomeButtonInAppAction:(GCControllerHomeButtonSettingCustomizationStatus * _Nullable)customization withError:(NSError * _Nullable __autoreleasing * _Nullable)error;
- (GCControllerHomeButtonSettingInAppAction)readControllerHomeButtonInAppActionWithError:(NSError * _Nullable __autoreleasing * _Nullable)error;

@end

NS_ASSUME_NONNULL_END
