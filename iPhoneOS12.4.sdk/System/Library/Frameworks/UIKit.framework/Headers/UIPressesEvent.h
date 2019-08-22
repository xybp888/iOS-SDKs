#if USE_UIKIT_PUBLIC_HEADERS || !__has_include(<UIKitCore/UIPressesEvent.h>)
//
//  UIPressesEvent.h
//  UIKit
//
//  Copyright (c) 2005-2018 Apple Inc. All rights reserved.
//

#import <UIKit/UIEvent.h>
#import <UIKit/UIPress.h>
#import <UIKit/UIGestureRecognizer.h>

NS_ASSUME_NONNULL_BEGIN

NS_CLASS_AVAILABLE_IOS(9_0) @interface UIPressesEvent : UIEvent

#if UIKIT_DEFINE_AS_PROPERTIES
@property(nonatomic, readonly) NSSet <UIPress *> *allPresses;
#else
- (NSSet <UIPress *> *)allPresses;
#endif
- (NSSet <UIPress *> *)pressesForGestureRecognizer:(UIGestureRecognizer *)gesture;

@end

NS_ASSUME_NONNULL_END

#else
#import <UIKitCore/UIPressesEvent.h>
#endif
