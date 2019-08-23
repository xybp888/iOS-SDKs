//
//  RPVideoPreviewViewController.h
//  ReplayKit
//
//  Copyright © 2015 Apple Inc. All rights reserved.
//

#import <UIKit/UIKit.h>

NS_CLASS_AVAILABLE_IOS(9_0)
NS_ASSUME_NONNULL_BEGIN
/*! @class RPPreviewViewController
 @abstract View controller that allows the user to preview/edit a movie recorded with ReplayKit. Passed into the completion handler supplied to [RPScreenRecorder stopRecordingWithHandler:].
 */
@protocol RPPreviewViewControllerDelegate;

@interface RPPreviewViewController : UIViewController
@property (nonatomic, weak, nullable) id<RPPreviewViewControllerDelegate>previewControllerDelegate;
@end

@protocol RPPreviewViewControllerDelegate <NSObject>
@optional
/* @abstract Called when the view controller is finished. */
- (void)previewControllerDidFinish:(RPPreviewViewController *)previewController;

/* @abstract Called when the view controller is finished and returns a set of activity types that the user has completed on the recording. The built in activity types are listed in UIActivity.h. */
- (void)previewController:(RPPreviewViewController *)previewController didFinishWithActivityTypes:(NSSet <NSString *> *)activityTypes;
@end
NS_ASSUME_NONNULL_END
