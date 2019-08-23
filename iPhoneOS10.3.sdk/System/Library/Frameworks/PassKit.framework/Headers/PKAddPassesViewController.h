//
//  PKAddPassesViewController.h
//  PassKit
//
//  Copyright (c) 2011 Apple, Inc. All rights reserved.
//

#if TARGET_OS_IPHONE

#import <UIKit/UIKit.h>

@class PKPass;
@class PKAddPassesViewController;

NS_ASSUME_NONNULL_BEGIN

@protocol PKAddPassesViewControllerDelegate <NSObject>
@optional
-(void)addPassesViewControllerDidFinish:(PKAddPassesViewController *)controller; // delegate should dismiss presentation
@end

NS_CLASS_AVAILABLE_IOS(6_0)
@interface PKAddPassesViewController : UIViewController

/* controller should be presented with -presentViewController:animated:completion:
 pass should be a pass you want the user to add.
 */
- (instancetype)initWithPass:(PKPass *)pass;
- (instancetype)initWithPasses:(NSArray<PKPass *> *)passes NS_AVAILABLE_IOS(7_0);
+ (BOOL)canAddPasses NS_AVAILABLE_IOS(8_0);

@property(nonatomic,assign,nullable) id <PKAddPassesViewControllerDelegate> delegate;

@end

NS_ASSUME_NONNULL_END

#endif
