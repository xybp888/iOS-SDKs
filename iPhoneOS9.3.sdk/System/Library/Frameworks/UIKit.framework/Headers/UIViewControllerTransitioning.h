//
//  UIViewControllerTransitioning.h
//  UIKit
//
//  Copyright (c) 2013-2015 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIViewController.h>
#import <UIKit/UIViewControllerTransitionCoordinator.h>

NS_ASSUME_NONNULL_BEGIN

@class UIView;

// The following keys are understood by UIViewControllerContextTransitioning context objects
// that are created by the system.

UIKIT_EXTERN NSString *const UITransitionContextFromViewControllerKey NS_AVAILABLE_IOS(7_0);
UIKIT_EXTERN NSString *const UITransitionContextToViewControllerKey NS_AVAILABLE_IOS(7_0);

UIKIT_EXTERN NSString *const UITransitionContextFromViewKey NS_AVAILABLE_IOS(8_0);
UIKIT_EXTERN NSString *const UITransitionContextToViewKey NS_AVAILABLE_IOS(8_0);

// A transition context object is constructed by the system and passed to the
// animator in its animateTransition: and transitionDuration: methods as well as
// to the interaction controller in its startInteractiveTransition: method. If
// there is an interaction controller its startInteractiveTransition: is called
// first and its up to the the interaction controller object to call the
// animateTransition: method if needed. If there is no interaction controller,
// then the system automatically invokes the animator's animateTransition:
// method.
//
// The system queries the view controller's transitionDelegate or the the
// navigation controller's delegate to determine if an animator or interaction
// controller should be used in a transition. The transitionDelegate is a new
// propery on UIViewController and conforms to the
// UIViewControllerTransitioningDelegate protocol defined below. The navigation
// controller likewise has been agumented with a couple of new delegate methods.
//
// The UIViewControllerContextTransitioning protocol can be adopted by custom
// container controllers.  It is purposely general to cover more complex
// transitions than the system currently supports. For now, navigation push/pops
// and UIViewController present/dismiss transitions can be
// customized. Information about the transition is obtained by using the
// viewControllerForKey:, initialFrameForViewController:, and
// finalFrameForViewController: methods. The system provides two keys for
// identifying the from view controller and the to view controller for
// navigation push/pop and view controller present/dismiss transitions.
//
// All custom animations must invoke the context's completeTransition: method
// when the transition completes.  Furthermore the animation should take place
// within the containerView specified by the context. For interactive
// transitions the context's updateInteractiveTransition:,
// finishInteractiveTransition or cancelInteractiveTransition should be called
// as the interactive animation proceeds. A concrete interaction controller
// class, UIPercentDrivenInteractiveTransition, is provided below to
// interactive; drive CA transitions defined by an animator.

@protocol UIViewControllerContextTransitioning <NSObject>

// The view in which the animated transition should take place.
- (nullable UIView *)containerView;

// Most of the time this is YES. For custom transitions that use the new UIModalPresentationCustom
// presentation type we will invoke the animateTransition: even though the transition should not be
// animated. This allows the custom transition to add or remove subviews to the container view. 
- (BOOL)isAnimated;

- (BOOL)isInteractive; // This indicates whether the transition is currently interactive.

- (BOOL)transitionWasCancelled;

- (UIModalPresentationStyle)presentationStyle;

// It only makes sense to call these from an interaction controller that
// conforms to the UIViewControllerInteractiveTransitioning protocol and was
// vended to the system by a container view controller's delegate or, in the case
// of a present or dismiss, the transitioningDelegate.
- (void)updateInteractiveTransition:(CGFloat)percentComplete;
- (void)finishInteractiveTransition;
- (void)cancelInteractiveTransition;

// This must be called whenever a transition completes (or is cancelled.)
// Typically this is called by the object conforming to the
// UIViewControllerAnimatedTransitioning protocol that was vended by the transitioning
// delegate.  For purely interactive transitions it should be called by the
// interaction controller. This method effectively updates internal view
// controller state at the end of the transition.
- (void)completeTransition:(BOOL)didComplete;


// Currently only two keys are defined by the
// system - UITransitionContextToViewControllerKey, and
// UITransitionContextFromViewControllerKey. 
// Animators should not directly manipulate a view controller's views and should
// use viewForKey: to get views instead.
- (nullable __kindof UIViewController *)viewControllerForKey:(NSString *)key;

// Currently only two keys are defined by the system -
// UITransitionContextFromViewKey, and UITransitionContextToViewKey
// viewForKey: may return nil which would indicate that the animator should not
// manipulate the associated view controller's view.
- (nullable __kindof UIView *)viewForKey:(NSString *)key NS_AVAILABLE_IOS(8_0);

- (CGAffineTransform)targetTransform NS_AVAILABLE_IOS(8_0);

// The frame's are set to CGRectZero when they are not known or
// otherwise undefined.  For example the finalFrame of the
// fromViewController will be CGRectZero if and only if the fromView will be
// removed from the window at the end of the transition. On the other
// hand, if the finalFrame is not CGRectZero then it must be respected
// at the end of the transition.
- (CGRect)initialFrameForViewController:(UIViewController *)vc;
- (CGRect)finalFrameForViewController:(UIViewController *)vc;
@end

@protocol UIViewControllerAnimatedTransitioning <NSObject>

// This is used for percent driven interactive transitions, as well as for container controllers that have companion animations that might need to
// synchronize with the main animation. 
- (NSTimeInterval)transitionDuration:(nullable id <UIViewControllerContextTransitioning>)transitionContext;
// This method can only  be a nop if the transition is interactive and not a percentDriven interactive transition.
- (void)animateTransition:(id <UIViewControllerContextTransitioning>)transitionContext;


@optional

// This is a convenience and if implemented will be invoked by the system when the transition context's completeTransition: method is invoked.
- (void)animationEnded:(BOOL) transitionCompleted;

@end


@protocol UIViewControllerInteractiveTransitioning <NSObject>
- (void)startInteractiveTransition:(id <UIViewControllerContextTransitioning>)transitionContext;

@optional
- (CGFloat)completionSpeed;
- (UIViewAnimationCurve)completionCurve;

@end

@class UIPresentationController;

@protocol UIViewControllerTransitioningDelegate <NSObject>

@optional
- (nullable id <UIViewControllerAnimatedTransitioning>)animationControllerForPresentedController:(UIViewController *)presented presentingController:(UIViewController *)presenting sourceController:(UIViewController *)source;

- (nullable id <UIViewControllerAnimatedTransitioning>)animationControllerForDismissedController:(UIViewController *)dismissed;

- (nullable id <UIViewControllerInteractiveTransitioning>)interactionControllerForPresentation:(id <UIViewControllerAnimatedTransitioning>)animator;

- (nullable id <UIViewControllerInteractiveTransitioning>)interactionControllerForDismissal:(id <UIViewControllerAnimatedTransitioning>)animator;

- (nullable UIPresentationController *)presentationControllerForPresentedViewController:(UIViewController *)presented presentingViewController:(UIViewController *)presenting sourceViewController:(UIViewController *)source NS_AVAILABLE_IOS(8_0);

@end

NS_CLASS_AVAILABLE_IOS(7_0) @interface UIPercentDrivenInteractiveTransition : NSObject <UIViewControllerInteractiveTransitioning>

// This is the non-interactive duration that was returned when the
// animators transitionDuration: method was called when the transition started.
@property (readonly) CGFloat duration;

// The last percentComplete value specified by updateInteractiveTransition:
@property (readonly) CGFloat percentComplete;

// completionSpeed defaults to 1.0 which corresponds to a completion duration of
// (1 - percentComplete)*duration.  It must be greater than 0.0. The actual
// completion is inversely proportional to the completionSpeed.  This can be set
// before cancelInteractiveTransition or finishInteractiveTransition is called
// in order to speed up or slow down the non interactive part of the
// transition.
@property (nonatomic,assign) CGFloat completionSpeed;

// When the interactive part of the transition has completed, this property can
// be set to indicate a different animation curve. It defaults to UIViewAnimationCurveEaseInOut.
// Note that during the interactive portion of the animation the timing curve is linear. 
@property (nonatomic,assign) UIViewAnimationCurve completionCurve;

// These methods should be called by the gesture recognizer or some other logic
// to drive the interaction. This style of interaction controller should only be
// used with an animator that implements a CA style transition in the animator's
// animateTransition: method. If this type of interaction controller is
// specified, the animateTransition: method must ensure to call the
// UIViewControllerTransitionParameters completeTransition: method. The other
// interactive methods on UIViewControllerContextTransitioning should NOT be
// called.

- (void)updateInteractiveTransition:(CGFloat)percentComplete;
- (void)cancelInteractiveTransition;
- (void)finishInteractiveTransition;

@end

NS_ASSUME_NONNULL_END

