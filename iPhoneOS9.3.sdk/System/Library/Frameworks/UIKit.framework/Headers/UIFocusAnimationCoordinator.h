//
//  UIFocusAnimationCoordinator.h
//  UIKit
//
//  Copyright © 2015 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/// UIFocusAnimationCoordinator is used to coordinate disparate animations that are related to a focus update.
NS_CLASS_AVAILABLE_IOS(9_0) @interface UIFocusAnimationCoordinator : NSObject

/**
 Specifies focus-related animations that should be coordinated with the animations of the focusing or un-focusing view.
 
 Any animations specified will be run in the same animation context as the main animation. The completion block is invoked after the main animation completes.
 (Note that this may not be after all the coordinated animations specified by the call complete if the duration is not inherited.)
 
 It is perfectly legitimate to only specify a completion block.
 */
- (void)addCoordinatedAnimations:(nullable void (^)(void))animations completion:(nullable void (^)(void))completion;

@end

NS_ASSUME_NONNULL_END
