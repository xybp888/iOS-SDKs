//
//  PKAddSecureElementPassViewController.h
//  PassKit
//
//  Copyright © 2020 Apple, Inc. All rights reserved.
//
#if TARGET_OS_IPHONE

#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

@class PKSecureElementPass;
@class PKAddSecureElementPassConfiguration;
@class PKAddSecureElementPassViewController;

@protocol PKAddSecureElementPassViewControllerDelegate <NSObject>

- (void)addSecureElementPassViewController:(PKAddSecureElementPassViewController *)controller
          didFinishAddingSecureElementPass:(nullable PKSecureElementPass *)pass
                                     error:(nullable NSError *)error;
@end

API_AVAILABLE(ios(13.4))
@interface PKAddSecureElementPassViewController : UIViewController

+ (BOOL)canAddSecureElementPassWithConfiguration:(PKAddSecureElementPassConfiguration *)configuration NS_SWIFT_NAME(canAddSecureElementPass(configuration:));

- (nullable instancetype)initWithConfiguration:(PKAddSecureElementPassConfiguration *)configuration
                                      delegate:(nullable id<PKAddSecureElementPassViewControllerDelegate>)delegate;

@property (nonatomic, weak, nullable) id<PKAddSecureElementPassViewControllerDelegate> delegate;

@end

NS_ASSUME_NONNULL_END

#endif // TARGET_OS_IPHONE
