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


typedef NSString<GCPhysicalInputElementName> *const GCInputElementName NS_TYPED_EXTENSIBLE_ENUM NS_REFINED_FOR_SWIFT;
typedef NSString<GCButtonElementName> *const GCInputButtonName NS_TYPED_EXTENSIBLE_ENUM NS_REFINED_FOR_SWIFT;
typedef NSString<GCAxisElementName> *const GCInputAxisName NS_TYPED_EXTENSIBLE_ENUM NS_REFINED_FOR_SWIFT;
typedef NSString<GCSwitchElementName> *const GCInputSwitchName NS_TYPED_EXTENSIBLE_ENUM NS_REFINED_FOR_SWIFT;
typedef NSString<GCDirectionPadElementName> *const GCInputDirectionPadName NS_TYPED_EXTENSIBLE_ENUM NS_REFINED_FOR_SWIFT;


/**
A set of commonly used strings that can be used to access controller buttons
 
@example controller.physicalInputProfile.buttons[GCInputButtonA]
 
@see GCController.h
@see GCPhysicalInputProfile.h
*/

GAMECONTROLLER_EXTERN GCInputButtonName GCInputButtonA NS_REFINED_FOR_SWIFT API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));
GAMECONTROLLER_EXTERN GCInputButtonName GCInputButtonB NS_REFINED_FOR_SWIFT API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));
GAMECONTROLLER_EXTERN GCInputButtonName GCInputButtonX NS_REFINED_FOR_SWIFT API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));
GAMECONTROLLER_EXTERN GCInputButtonName GCInputButtonY NS_REFINED_FOR_SWIFT API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));

GAMECONTROLLER_EXTERN GCInputDirectionPadName GCInputDirectionPad NS_REFINED_FOR_SWIFT API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));
GAMECONTROLLER_EXTERN GCInputDirectionPadName GCInputLeftThumbstick NS_REFINED_FOR_SWIFT API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));
GAMECONTROLLER_EXTERN GCInputDirectionPadName GCInputRightThumbstick NS_REFINED_FOR_SWIFT API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));

GAMECONTROLLER_EXTERN GCInputButtonName GCInputLeftShoulder NS_REFINED_FOR_SWIFT API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));
GAMECONTROLLER_EXTERN GCInputButtonName GCInputRightShoulder NS_REFINED_FOR_SWIFT API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));
GAMECONTROLLER_EXTERN GCInputButtonName GCInputLeftTrigger NS_REFINED_FOR_SWIFT API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));
GAMECONTROLLER_EXTERN GCInputButtonName GCInputRightTrigger NS_REFINED_FOR_SWIFT API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));
GAMECONTROLLER_EXTERN GCInputButtonName GCInputLeftThumbstickButton NS_REFINED_FOR_SWIFT API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));
GAMECONTROLLER_EXTERN GCInputButtonName GCInputRightThumbstickButton NS_REFINED_FOR_SWIFT API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));

GAMECONTROLLER_EXTERN GCInputButtonName GCInputButtonHome NS_REFINED_FOR_SWIFT API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));
GAMECONTROLLER_EXTERN GCInputButtonName GCInputButtonMenu NS_REFINED_FOR_SWIFT API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));
GAMECONTROLLER_EXTERN GCInputButtonName GCInputButtonOptions NS_REFINED_FOR_SWIFT API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));
GAMECONTROLLER_EXTERN GCInputButtonName GCInputButtonShare NS_REFINED_FOR_SWIFT API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0));

/**
A set of strings commonly used to access Xbox buttons
 
@example controller.physicalInputProfile.buttons[GCInputButtonPaddleOne]
 
@see GCController.h
@see GCPhysicalInputProfile.h
*/
GAMECONTROLLER_EXTERN GCInputButtonName GCInputXboxPaddleOne NS_REFINED_FOR_SWIFT API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));
GAMECONTROLLER_EXTERN GCInputButtonName GCInputXboxPaddleTwo NS_REFINED_FOR_SWIFT API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));
GAMECONTROLLER_EXTERN GCInputButtonName GCInputXboxPaddleThree NS_REFINED_FOR_SWIFT API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));
GAMECONTROLLER_EXTERN GCInputButtonName GCInputXboxPaddleFour NS_REFINED_FOR_SWIFT API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));

/**
A set of strings commonly used to access DualShock buttons
 
@example controller.physicalInputProfile.dpads[GCInputDualShockTouchpadOne]
 
@see GCController.h
@see GCPhysicalInputProfile.h
*/
GAMECONTROLLER_EXTERN GCInputDirectionPadName GCInputDualShockTouchpadOne NS_REFINED_FOR_SWIFT API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));
GAMECONTROLLER_EXTERN GCInputDirectionPadName GCInputDualShockTouchpadTwo NS_REFINED_FOR_SWIFT API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));
GAMECONTROLLER_EXTERN GCInputButtonName GCInputDualShockTouchpadButton NS_REFINED_FOR_SWIFT API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));

/**
A set of strings commonly used by racing wheels.
*/
GAMECONTROLLER_EXTERN GCInputAxisName GCInputSteeringWheel NS_REFINED_FOR_SWIFT API_AVAILABLE(macos(13.0), macCatalyst(16.0)) API_UNAVAILABLE(ios, tvos);
GAMECONTROLLER_EXTERN GCInputElementName GCInputShifter NS_REFINED_FOR_SWIFT API_AVAILABLE(macos(13.0), macCatalyst(16.0)) API_UNAVAILABLE(ios, tvos);
GAMECONTROLLER_EXTERN GCInputButtonName GCInputPedalAccelerator NS_REFINED_FOR_SWIFT API_AVAILABLE(macos(13.0), macCatalyst(16.0)) API_UNAVAILABLE(ios, tvos);
GAMECONTROLLER_EXTERN GCInputButtonName GCInputPedalBrake NS_REFINED_FOR_SWIFT API_AVAILABLE(macos(13.0), macCatalyst(16.0)) API_UNAVAILABLE(ios, tvos);
GAMECONTROLLER_EXTERN GCInputButtonName GCInputPedalClutch NS_REFINED_FOR_SWIFT API_AVAILABLE(macos(13.0), macCatalyst(16.0)) API_UNAVAILABLE(ios, tvos);
GAMECONTROLLER_EXTERN GCInputButtonName GCInputLeftPaddle NS_REFINED_FOR_SWIFT API_AVAILABLE(macos(13.0), macCatalyst(16.0)) API_UNAVAILABLE(ios, tvos);
GAMECONTROLLER_EXTERN GCInputButtonName GCInputRightPaddle NS_REFINED_FOR_SWIFT API_AVAILABLE(macos(13.0), macCatalyst(16.0)) API_UNAVAILABLE(ios, tvos);
