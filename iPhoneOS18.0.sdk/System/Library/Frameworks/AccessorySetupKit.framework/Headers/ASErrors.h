/*
    Copyright (C) 2024 Apple Inc. All Rights Reserved.
*/

#pragma once

#ifndef ACCESSORY_SETUP_KIT_INDIRECT_INCLUDES
#error "Please #import <AccessorySetupKit/AccessorySetupKit.h> instead of this file directly."
#endif

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/// NSError domain for AccessorySetupKit errors.
AS_EXTERN NSErrorDomain const ASErrorDomain;

/// Error codes used with ASErrorDomain.
typedef NS_ERROR_ENUM( ASErrorDomain, ASErrorCode )
{
    ASErrorCodeSuccess                      = 0,        // Success.
    ASErrorCodeUnknown                      = 1,        // Underlying failure with an unknown cause.
    ASErrorCodeActivationFailed             = 100,      // Unable to activate discovery session.
    ASErrorCodeConnectionFailed             = 150,      // Unable to establish connection with accessory.
    ASErrorCodeDiscoveryTimeout             = 200,      // Discovery timed out.
    ASErrorCodeExtensionNotFound            = 300,      // Unable to find App Extension.
    ASErrorCodeInvalidated                  = 400,      // Invalidate was called before the operation completed normally.
    ASErrorCodeInvalidRequest               = 450,      // Invalid request.
    ASErrorCodePickerAlreadyActive          = 500,      // Picker already active.
    ASErrorCodePickerRestricted             = 550,      // Picker restricted due to application in background.
    ASErrorCodeUserCancelled                = 700,      // User cancelled.
    ASErrorCodeUserRestricted               = 750,      // Access restricted by user.
}   API_AVAILABLE( ios( 18.0 ) ) API_UNAVAILABLE(macos, macCatalyst, watchos, tvos, visionos);

NS_ASSUME_NONNULL_END
