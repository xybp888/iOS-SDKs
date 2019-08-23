//
//  RPBroadcast.h
//  ReplayKit
//
//  The following guidelines can be followed to add broadcasting capabilities to an application:
//
//  Use the RPScreenRecorder singleton to enable the microphone and front-facing camera recording.
//
//  Load an instance of RPBroadcastActivityViewController and present it when the user intends to start 	broadcasting. This will present a view controller thats allows the user to select from the broadcast servies available on the device. Selecting a broadcast service presents the service’s UI to the user and allows the user to sign-in and setup their broadcast.
//
//  Once setup with the service is complete, an RPBroadcastController instance will be provided via the RPBroadcastActivityViewControllerDelegate protocol. This controller can be used to start, pause and finish the broadcast.
//
//  RPBroadcastController will have an NSDictionary instance in its serviceInfo property which will contain a URL  to their broadcast (which can be provided to the user to share prior to starting a broadcast), as well as other optional meta data the service may wish to provide.
//
//  Copyright © 2016 Apple Inc. All rights reserved.
//

#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

@protocol RPBroadcastActivityViewControllerDelegate;
@protocol RPBroadcastControllerDelegate;
@class RPBroadcastController;

/*! @class RPBroadcastActivityViewController
 @abstract View controller that presents the user with a list of broadcast services installed on the device.
 */
NS_CLASS_AVAILABLE_IOS(10_0)
@interface RPBroadcastActivityViewController : UIViewController

/*  @abstract Loads a RPBroadcastActivityViewController instance and returns it in the handler block.

 The view controller will present the user with a list of broadcast services available on the device and allow the user to set up a broadcast with the service through the service's UI.

 The RPBroadcastActivityViewController can be presented using [UIViewController presentViewController:animated:completion:] and should be dismissed when the delegate's broadcastActivityViewController:didFinishWithBroadcastController:error: method is called. Note that on large screen devices such as iPad, the default presentation style for view controllers is a popover. For an instance of RPBroadcastActivityViewController to present properly on iPad, it needs to have its popoverPresentationController's sourceRect and sourceView configured.

 @param broadcastActivityViewController The RPBroadcastActivityViewController which can be presented.
 @param error Optional error in the RPRecordingErrorCode domain which is supplied in the event the view controller could not be loaded.
 */
+ (void)loadBroadcastActivityViewControllerWithHandler:(nonnull void(^)(RPBroadcastActivityViewController * __nullable broadcastActivityViewController, NSError * __nullable error))handler;

/*  @abstract Delegate that is notified when the activity view controller is complete. */
@property (nonatomic, weak, nullable) id<RPBroadcastActivityViewControllerDelegate> delegate;
@end

@protocol RPBroadcastActivityViewControllerDelegate <NSObject>

/*  @abstract Called when the view controller is finished.
 @param broadcastActivityViewController The view controller instance.
 @param broadcastController An RPBroadcastController instance that can be used to start and stop broadcasts to a user selected service.
 @param error Optional error in the RPRecordingErrorCode domain. A nil error signifies that the user has successfully set up the broadcast with a broadcast service and is ready to start broadcasting.
 */
- (void)broadcastActivityViewController:(RPBroadcastActivityViewController *)broadcastActivityViewController didFinishWithBroadcastController:(nullable RPBroadcastController *)broadcastController error:(nullable NSError *)error;
@end

/*! @class RPBroadcastController
 @abstract Available once a user has successfully initiated a broadcast using an RPBroadcastActivityViewController. Can be used to start, pause and stop a broadcast.
 */
NS_CLASS_AVAILABLE_IOS(10_0)
@interface RPBroadcastController : NSObject
/*  @abstract Indicates whether the controller is currently broadcasting. */
@property (nonatomic, readonly, getter=isBroadcasting) BOOL broadcasting;
/*  @abstract Indicates whether the controller is currently paused. */
@property (nonatomic, readonly, getter=isPaused) BOOL paused;
/*  @abstract URL that can be used to redirect the user to the on-going or completed broadcast. */
@property (nonatomic, readonly) NSURL *broadcastURL;
/*  @abstract Dictionary updated by the service during a broadcast. The keys and values of this dictionary are defined by the broadcast service. KVO observable. */
@property (nonatomic, readonly, nullable) NSDictionary <NSString *, NSObject <NSCoding> *> *serviceInfo;
/*  @abstract Delegate which will be notified when an error occurs during broadcast. */
@property (nonatomic, weak) id<RPBroadcastControllerDelegate> delegate;
/*  @abstract bundleID of the broadcast extension which was selected by the user. */
@property (nonatomic, readonly) NSString *broadcastExtensionBundleID;
/*  @abstract Start the broadcast.
 @param error Optional error in the RPRecordingErrorCode domain. A nil error signifies that broadcasting has started successfully.
 */
- (void)startBroadcastWithHandler:(void(^)(NSError * __nullable error))handler;

/*  @abstract Pause the broadcast. The broadcast will pause immediately. */
- (void)pauseBroadcast;

/*  @abstract Resumes the broadcast. The broadcast will resume immediately. */
- (void)resumeBroadcast;

/*  @abstract Finish the broadcast.
 @param error Optional error in the RPRecordingErrorCode domain. A nil error signifies that broadcasting has finished successfully.
 */
- (void)finishBroadcastWithHandler:(void(^)(NSError * __nullable error))handler;
@end

@protocol RPBroadcastControllerDelegate <NSObject>
@optional

/*  @abstract Called when broadcasting finishes due to an error.
 @param broadcastController The controller instance.
 @param error Required error in the RPRecordingErrorCode domain.
 */

- (void)broadcastController:(RPBroadcastController *)broadcastController didFinishWithError:(NSError * __nullable)error;
/*  @abstract Called when the broadcast service has data to pass back to broadcasting app.
 @param broadcastController The controller instance.
 @param serviceInfo NSDictionary instance with keys and values defined by the broadcasting service.
 */
- (void)broadcastController:(RPBroadcastController *)broadcastController didUpdateServiceInfo:(NSDictionary <NSString *, NSObject <NSCoding> *> *)serviceInfo;
@end

NS_ASSUME_NONNULL_END
