//
//  MFComposeAssistantViewController.h
//  MessageUI
//
//  Copyright © 2025 Apple Inc. All rights reserved.
//

#import <MessageUI/MFMailDraft.h>

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

@class MFComposeAssistantViewController;

NS_ASSUME_NONNULL_BEGIN

@protocol MFComposeAssistantViewControllerDelegate <NSObject>

- (void)composeAssistantViewController:(MFComposeAssistantViewController *)controller didComposeDraft:(MFMailDraft *)draft;

@end

@interface MFComposeAssistantViewController: UIViewController

- (instancetype)initWithDelegate:(id<MFComposeAssistantViewControllerDelegate>)delegate;

@end

NS_ASSUME_NONNULL_END
