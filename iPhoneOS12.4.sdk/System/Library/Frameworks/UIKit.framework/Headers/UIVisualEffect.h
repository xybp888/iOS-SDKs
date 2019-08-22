#if USE_UIKIT_PUBLIC_HEADERS || !__has_include(<UIKitCore/UIVisualEffect.h>)
//
//  UIVisualEffect.h
//  UIKit
//
//  Copyright © 2016-2018 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

NS_CLASS_AVAILABLE_IOS(8_0) @interface UIVisualEffect : NSObject <NSCopying, NSSecureCoding>

@end

NS_ASSUME_NONNULL_END

#else
#import <UIKitCore/UIVisualEffect.h>
#endif
