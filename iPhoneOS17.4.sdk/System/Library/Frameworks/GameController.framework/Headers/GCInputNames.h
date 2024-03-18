//
//  GCInputNames.h
//  GameController
//
//  Copyright © 2020 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <GameController/GCExtern.h>

__attribute__((objc_non_runtime_protocol)) NS_REFINED_FOR_SWIFT
@protocol GCPhysicalInputElementName
@end

__attribute__((objc_non_runtime_protocol)) NS_REFINED_FOR_SWIFT
@protocol GCButtonElementName <GCPhysicalInputElementName>
@end

__attribute__((objc_non_runtime_protocol)) NS_REFINED_FOR_SWIFT
@protocol GCAxisElementName <GCPhysicalInputElementName>
@end

__attribute__((objc_non_runtime_protocol)) NS_REFINED_FOR_SWIFT
@protocol GCSwitchElementName <GCPhysicalInputElementName>
@end

__attribute__((objc_non_runtime_protocol)) NS_REFINED_FOR_SWIFT
@protocol GCDirectionPadElementName <GCPhysicalInputElementName>
@end


typedef NSString<GCPhysicalInputElementName> *const GCInputElementName NS_REFINED_FOR_SWIFT NS_TYPED_EXTENSIBLE_ENUM;
typedef NSString<GCButtonElementName> *const GCInputButtonName NS_REFINED_FOR_SWIFT NS_TYPED_EXTENSIBLE_ENUM;
typedef NSString<GCAxisElementName> *const GCInputAxisName NS_REFINED_FOR_SWIFT NS_TYPED_EXTENSIBLE_ENUM;
typedef NSString<GCSwitchElementName> *const GCInputSwitchName NS_REFINED_FOR_SWIFT NS_TYPED_EXTENSIBLE_ENUM;
typedef NSString<GCDirectionPadElementName> *const GCInputDirectionPadName NS_REFINED_FOR_SWIFT NS_TYPED_EXTENSIBLE_ENUM;


/**
A set of commonly used strings that can be used to access controller buttons
 
@example controller.physicalInputProfile.buttons[GCInputButtonA]
 
@see GCController.h
@see GCPhysicalInputProfile.h
*/

GAMECONTROLLER_EXTERN GCInputButtonName GCInputButtonA API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0)) NS_SWIFT_NAME(a);
GAMECONTROLLER_EXTERN GCInputButtonName GCInputButtonB API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0)) NS_SWIFT_NAME(b);
GAMECONTROLLER_EXTERN GCInputButtonName GCInputButtonX API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0)) NS_SWIFT_NAME(x);
GAMECONTROLLER_EXTERN GCInputButtonName GCInputButtonY API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0)) NS_SWIFT_NAME(y);

GAMECONTROLLER_EXTERN GCInputDirectionPadName GCInputDirectionPad API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0)) NS_SWIFT_NAME(directionPad);
GAMECONTROLLER_EXTERN GCInputDirectionPadName GCInputLeftThumbstick API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));
GAMECONTROLLER_EXTERN GCInputDirectionPadName GCInputRightThumbstick API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));

GAMECONTROLLER_EXTERN GCInputButtonName GCInputLeftThumbstickButton API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));
GAMECONTROLLER_EXTERN GCInputButtonName GCInputRightThumbstickButton API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));

/*
 * Shoulder Buttons
 */

GAMECONTROLLER_EXTERN GCInputButtonName GCInputLeftShoulder API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));
GAMECONTROLLER_EXTERN GCInputButtonName GCInputRightShoulder API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));

/**
 *  Identifies the button element located at the top-left/right of a gamepad,
 *  between the left/right shoulder button and the gamepad's horizontal center.
 */
GAMECONTROLLER_EXTERN GCInputButtonName GCInputLeftBumper API_AVAILABLE(macos(14.4), ios(17.4), tvos(17.4), visionos(1.1));
GAMECONTROLLER_EXTERN GCInputButtonName GCInputRightBumper API_AVAILABLE(macos(14.4), ios(17.4), tvos(17.4), visionos(1.1));

GAMECONTROLLER_EXTERN GCInputButtonName GCInputLeftTrigger API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));
GAMECONTROLLER_EXTERN GCInputButtonName GCInputRightTrigger API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));

/*
 * Back Buttons
 *
 * Some gamepads include additional buttons or triggers on their underside.
 * Because the number and layout of bottom buttons can vary by controller, the
 * Game Controller framework identifies them by their ease of operation.  The
 * back left and right buttons at the first position are located nearest the
 * natural rest position of the user's fingers and are suitable for actions
 * requiring repeated inputs.  The buttons at the 'second' position may require
 * the user to move their fingers to press and should be used for less frequent
 * actions.
 *
 * Example view looking at the underside of a gamepad with four back buttons
 * arranged horizontally:
 *
 *     +---------------------------------------------------------------+
 *     |                       Controller top                          |
 *     +---------------------------------------------------------------+
 *     |                                                               |
 *   R | [(R) 0]  [(R) 1]                             [(L) 1]  [(L) 0] | L
 *     |                                                               |
 *     +---------------------------------------------------------------|
 *     |             Controller bottom (nearest the user)              |
 *     +---------------------------------------------------------------+
 */

/* Note: The `position` argument begins at index 0. */
GAMECONTROLLER_EXTERN GCInputButtonName GCInputBackLeftButton(NSInteger position) NS_REFINED_FOR_SWIFT API_AVAILABLE(macos(14.4), ios(17.4), tvos(17.4), visionos(1.1));
GAMECONTROLLER_EXTERN GCInputButtonName GCInputBackRightButton(NSInteger position) NS_REFINED_FOR_SWIFT API_AVAILABLE(macos(14.4), ios(17.4), tvos(17.4), visionos(1.1));

GAMECONTROLLER_EXTERN GCInputButtonName GCInputButtonHome API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));
GAMECONTROLLER_EXTERN GCInputButtonName GCInputButtonMenu API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));
GAMECONTROLLER_EXTERN GCInputButtonName GCInputButtonOptions API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));
GAMECONTROLLER_EXTERN GCInputButtonName GCInputButtonShare API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0));

/**
A set of strings commonly used to access Xbox buttons
 
@example controller.physicalInputProfile.buttons[GCInputButtonPaddleOne]
 
@see GCController.h
@see GCPhysicalInputProfile.h
*/
GAMECONTROLLER_EXTERN GCInputButtonName GCInputXboxPaddleOne API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));
GAMECONTROLLER_EXTERN GCInputButtonName GCInputXboxPaddleTwo API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));
GAMECONTROLLER_EXTERN GCInputButtonName GCInputXboxPaddleThree API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));
GAMECONTROLLER_EXTERN GCInputButtonName GCInputXboxPaddleFour API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));

/**
A set of strings commonly used to access DualShock buttons
 
@example controller.physicalInputProfile.dpads[GCInputDualShockTouchpadOne]
 
@see GCController.h
@see GCPhysicalInputProfile.h
*/
GAMECONTROLLER_EXTERN GCInputDirectionPadName GCInputDualShockTouchpadOne API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));
GAMECONTROLLER_EXTERN GCInputDirectionPadName GCInputDualShockTouchpadTwo API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));
GAMECONTROLLER_EXTERN GCInputButtonName GCInputDualShockTouchpadButton API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));

/**
A set of strings commonly used by racing wheels.
*/
GAMECONTROLLER_EXTERN GCInputAxisName GCInputSteeringWheel API_AVAILABLE(macos(13.0), macCatalyst(16.0)) API_UNAVAILABLE(ios, tvos);
GAMECONTROLLER_EXTERN GCInputElementName GCInputShifter API_AVAILABLE(macos(13.0), macCatalyst(16.0)) API_UNAVAILABLE(ios, tvos);
GAMECONTROLLER_EXTERN GCInputButtonName GCInputPedalAccelerator API_AVAILABLE(macos(13.0), macCatalyst(16.0)) API_UNAVAILABLE(ios, tvos);
GAMECONTROLLER_EXTERN GCInputButtonName GCInputPedalBrake API_AVAILABLE(macos(13.0), macCatalyst(16.0)) API_UNAVAILABLE(ios, tvos);
GAMECONTROLLER_EXTERN GCInputButtonName GCInputPedalClutch API_AVAILABLE(macos(13.0), macCatalyst(16.0)) API_UNAVAILABLE(ios, tvos);
GAMECONTROLLER_EXTERN GCInputButtonName GCInputLeftPaddle API_AVAILABLE(macos(13.0), macCatalyst(16.0)) API_UNAVAILABLE(ios, tvos);
GAMECONTROLLER_EXTERN GCInputButtonName GCInputRightPaddle API_AVAILABLE(macos(13.0), macCatalyst(16.0)) API_UNAVAILABLE(ios, tvos);

/// Gets the name of an arcade button at a certain position.
GAMECONTROLLER_EXTERN GCInputButtonName GCInputArcadeButtonName(NSInteger row, NSInteger column) NS_REFINED_FOR_SWIFT API_AVAILABLE(macos(13.0), ios(16.0), tvos(16.0));
