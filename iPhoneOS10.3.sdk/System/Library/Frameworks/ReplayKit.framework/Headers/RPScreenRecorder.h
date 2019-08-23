//
//  RPScreenRecorder.h
//  ReplayKit
//
//  ReplayKit is a high level framework that can be used to add video and audio recording and broadcast capabilities to an application. An application supplied user interface can use the RPScreenRecorder singleton to start and stop recording or broadcasting.
//
//  Optionally the framework allows the user to also record microphone content as well as content from the front facing camera.
//
//  When local recording stops, the framework will vend an instance of RPPreviewViewController that can be presented using [UIViewController presentViewController:animated:completion:]. The view controller allows the user to preview, trim and share the movie.
//
//  When broadcasting stops, the framework will return a url that can be used to view a broadcast.
//
//  Copyright © 2016 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import "RPPreviewViewController.h"
NS_ASSUME_NONNULL_BEGIN

NS_CLASS_AVAILABLE_IOS(9_0)
@protocol RPScreenRecorderDelegate;
@class RPBroadcastActivityViewController;

/*! @class RPScreenRecorder
 @abstract Singleton class used to control app recording.
 */
@interface RPScreenRecorder : NSObject

/* @abstract Shared instance of the screen recorder. */
+ (RPScreenRecorder *)sharedRecorder;

- (instancetype)init NS_UNAVAILABLE; // Use sharedRecorder instead

/*! 
 Deprecated. Use startRecordingWithHandler: instead.
 
 @abstract Starts app recording with a completion handler. Note that before recording actually starts, the user may be prompted with UI to confirm recording.
 @param microphoneEnabled Determines whether the microphone input should be included in the recorded movie audio.
 @result handler Called after user interactions are complete. Will be passed an optional NSError in the RPRecordingErrorDomain domain if there was an issue starting the recording.
 */
- (void)startRecordingWithMicrophoneEnabled:(BOOL)microphoneEnabled handler:(nullable void(^)(NSError * __nullable error))handler NS_DEPRECATED_IOS(9_0, 10_0);

/*! @abstract Starts app recording with a completion handler. Note that before recording actually starts, the user may be prompted with UI to confirm recording.
 @result handler Called after user interactions are complete. Will be passed an optional NSError in the RPRecordingErrorDomain domain if there was an issue starting the recording.
 */
- (void)startRecordingWithHandler:(nullable void(^)(NSError * __nullable error))handler NS_AVAILABLE_IOS(10_0);

/*! @abstract Stops app recording with a completion handler.
 @result handler Called when the movie is ready. Will return an instance of RPPreviewViewController on success which should be presented using [UIViewController presentViewController:animated:completion:]. Will be passed an optional NSError in the RPRecordingErrorDomain domain if there was an issue stopping the recording.
 */
- (void)stopRecordingWithHandler:(nullable void(^)(RPPreviewViewController * __nullable previewViewController, NSError * __nullable error))handler;

/*! @abstract Discards the current recording. This can only be called after the handler block in stopRecordingWithHandler: is executed.
 */
- (void)discardRecordingWithHandler:(void(^)(void))handler;

/* @abstract Delegate instance for RPScreenRecorder. */
@property (nonatomic, weak, nullable) id<RPScreenRecorderDelegate> delegate;

/* @abstract Check if ReplayKit is available on the device. Implement the screenRecorderDidChangeAvailability: on the delegate to listen for changes to this property. Can be used for key value observing. */
@property (nonatomic, readonly, getter=isAvailable) BOOL available;

/* @abstract Check if a recording session is in progress. Can be used for key value observing. */
@property (nonatomic, readonly, getter=isRecording) BOOL recording;

/* @abstract Specify or query whether the microphone should be enabled during recording. Can be used for key value observing. Default is NO. */
@property (nonatomic, getter=isMicrophoneEnabled) BOOL microphoneEnabled __TVOS_PROHIBITED;

/* @abstract Specify or query whether the camera should be enabled during recording. Can be used for key value observing. Default is NO. */
@property (nonatomic, getter=isCameraEnabled) BOOL cameraEnabled NS_AVAILABLE_IOS(10_0) __TVOS_PROHIBITED;

/* @abstract A UIView instance that renders the front facing camera contents. This will be nil if the camera has not been enabled */
@property (nonatomic, readonly, nullable) UIView *cameraPreviewView NS_AVAILABLE_IOS(10_0) __TVOS_PROHIBITED;

@end

@protocol RPScreenRecorderDelegate <NSObject>
@optional

/*! @abstract Called when recording has stopped due to an error.
 @param screenRecorder The instance of the screen recorder.
 @param error An NSError describing why recording has stopped in the RPRecordingErrorDomain.
 @param previewViewController If a partial movie is available before it was stopped, an instance of RPPreviewViewController will be returned.
 */
- (void)screenRecorder:(RPScreenRecorder *)screenRecorder didStopRecordingWithError:(NSError *)error previewViewController:(nullable RPPreviewViewController *)previewViewController;

/*! @abstract Called when the recorder becomes available or stops being available. Check the screen recorder's availability property to check the current availability state. Possible reasons for the recorder to be unavailable include an in-progress Airplay/TVOut session or unsupported hardware.
 @param screenRecorder The instance of the screen recorder.
 */
- (void)screenRecorderDidChangeAvailability:(RPScreenRecorder *)screenRecorder;
@end
NS_ASSUME_NONNULL_END


