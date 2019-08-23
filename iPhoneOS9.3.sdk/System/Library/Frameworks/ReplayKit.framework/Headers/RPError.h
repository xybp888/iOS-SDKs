//
//  RPError.h
//  ReplayKit
//
//  Copyright © 2015 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
extern NSString * const __nonnull RPRecordingErrorDomain;

NS_ENUM_AVAILABLE_IOS(9_0)
typedef NS_ENUM(NSInteger, RPRecordingErrorCode) {
    RPRecordingErrorUnknown = -5800,
    RPRecordingErrorUserDeclined = -5801, // The user declined app recording.
    RPRecordingErrorDisabled = -5802, // App recording has been disabled via parental controls.
    RPRecordingErrorFailedToStart = -5803, // Recording failed to start
    RPRecordingErrorFailed = -5804, // Failed during recording
    RPRecordingErrorInsufficientStorage = -5805, // Insufficient storage for recording.
    RPRecordingErrorInterrupted = -5806, // Recording interrupted by other app
    RPRecordingErrorContentResize = -5807 // Recording interrupted by multitasking and Content Resizing
};
