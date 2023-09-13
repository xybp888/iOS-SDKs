// Copyright © Apple Inc. All rights reserved.

#import <TargetConditionals.h>

#if !TARGET_OS_WATCH

#if TARGET_OS_IPHONE || TARGET_OS_MACCATALYST
#import <UIKit/UIKit.h>
#else
#import <AppKit/AppKit.h>
#endif

@protocol GKFriendRequestComposeViewControllerDelegate;
@class GKPlayer;


/// Standard view controller for sending friend requests to other players. Present modally from the top view controller.
#if TARGET_OS_IPHONE || TARGET_OS_MACCATALYST
NS_ASSUME_NONNULL_BEGIN

NS_CLASS_DEPRECATED(10_8, 10_12, 4_2, 10_0) API_UNAVAILABLE(tvos)
@interface GKFriendRequestComposeViewController : UINavigationController
@end
#else
#import <GameKit/GKDialogController.h>
NS_ASSUME_NONNULL_BEGIN
NS_CLASS_DEPRECATED(10_8, 10_12, 4_2, 10_0)
@interface GKFriendRequestComposeViewController : NSViewController <GKViewController> 
@end
#endif

NS_CLASS_DEPRECATED(10_8, 10_12, 4_2, 10_0) __TVOS_UNAVAILABLE
@interface GKFriendRequestComposeViewController ()
/// Get the maximum number of recipients permitted
+ (NSUInteger)maxNumberOfRecipients;

/// Specify the message sent to the invitee. A default message will be used if you don't specify one.
- (void)setMessage:(nullable NSString *)message;

/// Add recipients to the request.
/// If you don't specify at least one recipient before presenting the view, the recipients field will be made firstResponder, to encourage the user to add some.
/// If you add more than maxNumberOfRecipients recipients, these methods will throw an exception.
- (void)addRecipientPlayers:(NSArray<GKPlayer *> *)players NS_AVAILABLE(10_10, 8_0);
- (void)addRecipientsWithPlayerIDs:(NSArray<NSString *> *)playerIDs API_DEPRECATED_WITH_REPLACEMENT("-addRecipientPlayers:", ios(4.2,8.0), macos(10.8,10.10)) __TVOS_UNAVAILABLE;
- (void)addRecipientsWithEmailAddresses:(NSArray<NSString *> *)emailAddresses;

@property (nonatomic, weak, nullable) id<GKFriendRequestComposeViewControllerDelegate> composeViewDelegate NS_DEPRECATED(10_8, 10_12, 4_2, 10_0) API_UNAVAILABLE(tvos);
@end

/// Optional delegate
NS_DEPRECATED(10_8, 10_12, 4_2, 10_0) API_UNAVAILABLE(tvos)
@protocol GKFriendRequestComposeViewControllerDelegate
/// The compose view has finished
- (void)friendRequestComposeViewControllerDidFinish:(GKFriendRequestComposeViewController *)viewController NS_DEPRECATED(10_8, 10_12, 4_2, 10_0) API_UNAVAILABLE(tvos);
@end

NS_ASSUME_NONNULL_END

#endif
