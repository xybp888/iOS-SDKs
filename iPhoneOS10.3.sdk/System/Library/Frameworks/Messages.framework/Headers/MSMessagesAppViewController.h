/*!
 @header     MSMessagesAppViewController
 @copyright  Copyright (c) 2016 Apple Inc. All rights reserved.
 */

#import <UIKit/UIKit.h>

@class MSConversation, MSMessage;

NS_ASSUME_NONNULL_BEGIN

/*!
 @enum       MSMessagesAppPresentationStyle
 @abstract   Describes how the extension is presented in Messages.
 @constant   MSMessagesAppPresentationStyleCompact     The extension's UI is presented compact in the keyboard area.
 @constant   MSMessagesAppPresentationStyleExpanded   The extension's UI is presented expanded taking up most of the screen.
 */
typedef NS_ENUM(NSUInteger, MSMessagesAppPresentationStyle) {
    MSMessagesAppPresentationStyleCompact,
    MSMessagesAppPresentationStyleExpanded
} NS_ENUM_AVAILABLE_IOS(10_0);


@interface MSMessagesAppViewController : UIViewController

/*!
 @property   activeConversation
 @abstract   Current active conversation.
 */
@property (nonatomic, strong, readonly, nullable) MSConversation *activeConversation;

/*!
 @property   presentationStyle
 @abstract   Get the presentation extension's current presentation style.
 */
@property (nonatomic, assign, readonly) MSMessagesAppPresentationStyle presentationStyle;

/*!
 @method     requestPresentationStyle:
 @abstract   Requests that Messages transition the extension to the specified presentation style.
 @param      presentationStyle   The presentation style to transition to.
 */
-(void)requestPresentationStyle:(MSMessagesAppPresentationStyle)presentationStyle;

/*!
 @method    dismiss
 @abstract  Tells the Messages to dismiss the extension and present the keyboard.
 */
-(void)dismiss;

/*!
 @method     willBecomeActiveWithConversation:
 @abstract   Called when the extension is about to become active.
 @param      conversation   The current conversation.
 */
-(void)willBecomeActiveWithConversation:(MSConversation *)conversation;

/*!
 @method     didBecomeActiveWithConversation:
 @abstract   Called when the extension has become active active.
 @param      conversation   The current conversation.
 */
-(void)didBecomeActiveWithConversation:(MSConversation *)conversation;

/*!
 @method     willResignActiveWithConversation:
 @abstract   Called when the extension will resign active.
 @param      conversation   The current conversation.
 */
-(void)willResignActiveWithConversation:(MSConversation *)conversation;

/*!
 @method     didResignActiveWithConversation:
 @abstract   Called when the extension has resigned active.
 @param      conversation   The current conversation.
 */
-(void)didResignActiveWithConversation:(MSConversation *)conversation;

/*!
 @method     willSelectMessage:conversation:
 @abstract   Informs the extension that a new message will be selected in the conversation.
 @param      message    The message selected.
 @param      conversation    The conversation.
 */
-(void)willSelectMessage:(MSMessage *)message conversation:(MSConversation *)conversation;


/*!
 @method     didSelectMessage:conversation:
 @abstract   Informs the extension that a new message has been selected in the conversation.
 @param      message    The message selected.
 @param      conversation    The conversation.
 */
-(void)didSelectMessage:(MSMessage *)message conversation:(MSConversation *)conversation;

/*!
 @method     didReceiveMessage:conversation:
 @abstract   Informs the extension that a new message has arrived.
 @param      message    The message received.
 @param      conversation    The conversation.
 */
-(void)didReceiveMessage:(MSMessage *)message conversation:(MSConversation *)conversation;

/*!
 @method     didStartSendingMessage:conversation:
 @abstract   Informs the extension that the message send has been triggered.
 @discussion This is called when a user interaction with Messages start the message
 send process. It does not guarantee  that the message will be successfully sent or
 delivered.
 @param      message    The message being sent.
 @param      conversation    The conversation the message belongs to.
 */
-(void)didStartSendingMessage:(MSMessage *)message conversation:(MSConversation *)conversation;

/*!
 @method     didCancelSendingMessage:conversation:
 @abstract   Informs the extension that the user has removed the message from the input field.
 @param      message    The message sent.
 @param      conversation    The conversation.
 */
-(void)didCancelSendingMessage:(MSMessage *)message conversation:(MSConversation *)conversation;

/*!
 @method     willTransitionToPresentationStyle:
 @abstract   Called when the extension is about to transition to a new presentation style.
 @param      presentationStyle   The new presentation style.
 */
-(void)willTransitionToPresentationStyle:(MSMessagesAppPresentationStyle)presentationStyle;

/*!
 @method     didTransitionToPresentationStyle:
 @abstract   Called when the extension finished transitioning to a presentation style.
 @param      presentationStyle   The new presentation style.
 */
-(void)didTransitionToPresentationStyle:(MSMessagesAppPresentationStyle)presentationStyle;

@end

NS_ASSUME_NONNULL_END
