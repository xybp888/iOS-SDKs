//
//  UIPressesEvent.h
//  UIKit
//
//  Copyright (c) 2005-2015 Apple Inc. All rights reserved.
//

#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

NS_CLASS_AVAILABLE_IOS(9_0) @interface UIPressesEvent : UIEvent

- (NSSet <UIPress *> *)allPresses;
- (NSSet <UIPress *> *)pressesForGestureRecognizer:(UIGestureRecognizer *)gesture;

@end

NS_ASSUME_NONNULL_END
