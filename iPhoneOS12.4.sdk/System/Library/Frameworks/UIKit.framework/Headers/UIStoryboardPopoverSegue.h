#if USE_UIKIT_PUBLIC_HEADERS || !__has_include(<UIKitCore/UIStoryboardPopoverSegue.h>)
//
//  UIStoryboardPopoverSegue.h
//  UIKit
//
//  Copyright 2011-2018 Apple Inc. All rights reserved.
//

#import <UIKit/UIStoryboardSegue.h>

NS_ASSUME_NONNULL_BEGIN

@class UIPopoverController;

NS_CLASS_DEPRECATED_IOS(5_0, 9_0, "Access destinationViewController.popoverPresentationController from your segue's performHandler or override of -perform") @interface UIStoryboardPopoverSegue : UIStoryboardSegue {
}

@property (nonatomic, strong, readonly) UIPopoverController *popoverController;

@end

NS_ASSUME_NONNULL_END

#else
#import <UIKitCore/UIStoryboardPopoverSegue.h>
#endif
