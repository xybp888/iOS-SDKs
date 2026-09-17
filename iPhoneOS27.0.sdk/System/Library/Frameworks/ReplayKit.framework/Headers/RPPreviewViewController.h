//
// RPPreviewViewController.h
// ReplayKit
//
// Copyright © 2015 Apple Inc. All rights reserved.
//

#import <TargetConditionals.h>

#if TARGET_OS_OSX
#import <AppKit/AppKit.h>
#else
#import <UIKit/UIKit.h>
#endif

#if TARGET_OS_TV
typedef NS_ENUM (NSInteger, RPPreviewViewControllerMode) {
    RPPreviewViewControllerModePreview,
    RPPreviewViewControllerModeShare
};
#endif

NS_ASSUME_NONNULL_BEGIN

@protocol RPPreviewViewControllerDelegate;

/*! @class RPPreviewViewController
 @abstract View controller that allows the user to preview/edit a movie recorded with ReplayKit. Passed into the completion handler supplied to [RPScreenRecorder stopRecordingWithHandler:].
 */
#if TARGET_OS_OSX
API_DEPRECATED("Use SCRecordingEditor instead", macos(11.0, 27.0))
@interface RPPreviewViewController : NSViewController
#else
API_DEPRECATED("Use SCRecordingEditor instead", ios(9.0, 27.0), tvos(10.0, 27.0))
@interface RPPreviewViewController : UIViewController
#endif
@property (nonatomic, weak, nullable) id<RPPreviewViewControllerDelegate>previewControllerDelegate;
#if TARGET_OS_TV
@property (nonatomic, assign) RPPreviewViewControllerMode mode __IOS_PROHIBITED __TVOS_AVAILABLE(10_0);  // Set
#endif
@end

API_DEPRECATED("Use SCRecordingEditor instead", ios(9.0, 27.0), tvos(10.0, 27.0), macos(11.0, 27.0))
@protocol RPPreviewViewControllerDelegate <NSObject>
@optional
/* @abstract Called when the view controller is finished. */
- (void)previewControllerDidFinish:(RPPreviewViewController *)previewController;

/* @abstract Called when the view controller is finished and returns a set of activity types that the user has completed on the recording. The built in activity types are listed in UIActivity.h. */
- (void)previewController:(RPPreviewViewController *)previewController didFinishWithActivityTypes:(NSSet <NSString *> *)activityTypes __TVOS_PROHIBITED;
@end
NS_ASSUME_NONNULL_END
