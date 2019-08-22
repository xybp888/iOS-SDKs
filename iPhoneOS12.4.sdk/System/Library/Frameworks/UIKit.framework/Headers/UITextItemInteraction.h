#if USE_UIKIT_PUBLIC_HEADERS || !__has_include(<UIKitCore/UITextItemInteraction.h>)
//
//  UITextItemInteraction.h
//  UIKit
//
//  Copyright (c) 2016-2018 Apple Inc. All rights reserved.
//

typedef NS_ENUM(NSInteger, UITextItemInteraction) {
    UITextItemInteractionInvokeDefaultAction,
    UITextItemInteractionPresentActions,
    UITextItemInteractionPreview,
} NS_ENUM_AVAILABLE_IOS(10_0);

#else
#import <UIKitCore/UITextItemInteraction.h>
#endif
