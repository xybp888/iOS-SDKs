//
//  ADSActionViewControllerInterface.h
//  iAd
//
//  Created by David Wilson on 3/28/14.
//
//

#import <Foundation/Foundation.h>

@class ADAdSpace;

@protocol ADActionViewControllerInterface <NSObject>

@property (nonatomic, readonly) BOOL readyForPresentation;
@property (nonatomic, weak, readonly) ADAdSpace *adSpace;

- (void)dismiss;

- (void)clientApplicationDidEnterBackground;
- (void)clientApplicationCancelledAction;

@end

@protocol ADActionViewControllerChildInterface <NSObject>

- (void)actionViewControllerClosed;

@end
