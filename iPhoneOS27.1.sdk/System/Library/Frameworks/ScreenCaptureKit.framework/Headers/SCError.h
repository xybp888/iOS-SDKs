//
//  SCError.h
//  ScreenCaptureKit
//
//  Copyright © 2021 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
API_AVAILABLE(macos(12.3), macCatalyst(18.2), ios(27.0), visionos(27.0), tvos(27.0))
extern NSErrorDomain const __nonnull SCStreamErrorDomain;

NS_ASSUME_NONNULL_BEGIN
API_AVAILABLE(macos(12.3), macCatalyst(18.2), ios(27.0), visionos(27.0), tvos(27.0))
typedef NS_ERROR_ENUM (SCStreamErrorDomain, SCStreamErrorCode) {
    SCStreamErrorUserDeclined API_AVAILABLE(macos(12.3), macCatalyst(18.2), ios(27.0), visionos(27.0), tvos(27.0)) = -3801, // The user chose not to authorize capture
    SCStreamErrorFailedToStart API_AVAILABLE(macos(12.3), macCatalyst(18.2), ios(27.0), visionos(27.0), tvos(27.0)) = -3802, // The stream failed to start
    SCStreamErrorMissingEntitlements API_AVAILABLE(macos(12.3), macCatalyst(18.2), ios(27.0), visionos(27.0), tvos(27.0)) = -3803, // The stream failed due to missing entitlements
    SCStreamErrorFailedApplicationConnectionInvalid API_AVAILABLE(macos(12.3), macCatalyst(18.2), ios(27.0), visionos(27.0), tvos(27.0)) = -3804, // Failed during recording application connection invalid
    SCStreamErrorFailedApplicationConnectionInterrupted API_AVAILABLE(macos(12.3), macCatalyst(18.2), ios(27.0), visionos(27.0), tvos(27.0)) = -3805, // Failed during recording appliation connection interrupted
    SCStreamErrorFailedNoMatchingApplicationContext API_AVAILABLE(macos(12.3), macCatalyst(18.2), ios(27.0), visionos(27.0), tvos(27.0)) = -3806, // Failed during recording context id does not match application
    SCStreamErrorAttemptToStartStreamState API_AVAILABLE(macos(12.3), macCatalyst(18.2), ios(27.0), visionos(27.0), tvos(27.0)) = -3807, // Failed due to attempting to start a stream thats already in a recording state
    SCStreamErrorAttemptToStopStreamState API_AVAILABLE(macos(12.3), macCatalyst(18.2), ios(27.0), visionos(27.0), tvos(27.0)) = -3808, // Failed due to attempting to stop a stream thats already in a recording state
    SCStreamErrorAttemptToUpdateFilterState API_AVAILABLE(macos(12.3), macCatalyst(18.2), ios(27.0), visionos(27.0), tvos(27.0)) = -3809, // Failed due to attempting to update the filter on a stream
    SCStreamErrorAttemptToConfigState API_AVAILABLE(macos(12.3), macCatalyst(18.2), ios(27.0), visionos(27.0), tvos(27.0)) = -3810, // Failed due to attempting to update stream config on a stream
    SCStreamErrorInternalError API_AVAILABLE(macos(12.3), macCatalyst(18.2), ios(27.0), visionos(27.0), tvos(27.0)) = -3811, // Failed to start due to video/audio capture failure
    SCStreamErrorInvalidParameter API_AVAILABLE(macos(12.3), macCatalyst(18.2), ios(27.0), visionos(27.0), tvos(27.0)) = -3812, // Failed due to invalid parameter
    SCStreamErrorNoWindowList API_AVAILABLE(macos(12.3), macCatalyst(18.2), ios(27.0), visionos(27.0), tvos(27.0)) = -3813, // Failed due to no window list
    SCStreamErrorNoDisplayList API_AVAILABLE(macos(12.3), macCatalyst(18.2), ios(27.0), visionos(27.0), tvos(27.0)) = -3814, // Failed due to no display list
    SCStreamErrorNoCaptureSource API_AVAILABLE(macos(12.3), macCatalyst(18.2), ios(27.0), visionos(27.0), tvos(27.0)) = -3815, // Failed due to no display or window list to capture
    SCStreamErrorRemovingStream API_AVAILABLE(macos(12.3), macCatalyst(18.2), ios(27.0), visionos(27.0), tvos(27.0)) = -3816, // Failed to remove stream
    SCStreamErrorUserStopped API_AVAILABLE(macos(12.3), macCatalyst(18.2), ios(27.0), visionos(27.0), tvos(27.0)) = -3817, // The stream was stopped by the user
    SCStreamErrorFailedToStartAudioCapture API_AVAILABLE(macos(13.0), macCatalyst(18.2), ios(27.0), visionos(27.0), tvos(27.0)) = -3818, // The stream failed to start audio
    SCStreamErrorFailedToStopAudioCapture API_AVAILABLE(macos(13.0), macCatalyst(18.2), ios(27.0), visionos(27.0), tvos(27.0)) = -3819, // The stream failed to stop audio
    SCStreamErrorFailedToStartMicrophoneCapture API_AVAILABLE(macos(15.0), macCatalyst(18.2), ios(27.0), visionos(27.0), tvos(27.0)) = -3820, // The stream failed to start microphone
    SCStreamErrorSystemStoppedStream API_AVAILABLE(macos(15.0), macCatalyst(18.2), ios(27.0), visionos(27.0), tvos(27.0)) = -3821, // The stream was stopped by the system
    SCStreamErrorInsufficientStorage API_AVAILABLE(macos(27.0), macCatalyst(27.0), ios(27.0), visionos(27.0), tvos(27.0)) = -3822, // The stream was stopped due to insufficient storage for recording
    SCStreamErrorNotSupported API_AVAILABLE(macos(27.0), macCatalyst(27.0), ios(27.0), visionos(27.0), tvos(27.0)) = -3823,      // The operation is not supported on this platform
    SCStreamErrorMissingBackgroundMode API_AVAILABLE(ios(27.0), visionos(27.0), tvos(27.0)) = -3824, // The stream was stopped due to missing background mode
};

NS_ASSUME_NONNULL_END
