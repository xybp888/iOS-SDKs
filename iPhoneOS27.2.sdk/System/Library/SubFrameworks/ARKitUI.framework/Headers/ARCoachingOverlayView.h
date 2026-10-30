//
//  ARCoachingOverlayView.h
//  ARKit
//
//  Copyright © 2019 Apple Inc. All rights reserved.
//

#import <UIKit/UIKit.h>

API_UNAVAILABLE_BEGIN(visionos)

NS_ASSUME_NONNULL_BEGIN

@class ARSession;

@protocol ARCoachingOverlayViewDelegate;
@protocol ARSessionProviding;

/**
 The options that specify your app's tracking requirements.

 This enumeration lists the available goals you can set on a coaching overlay's ``ARCoachingOverlayView/goal-swift.property``. The coaching overlay
 adjusts its messaging to the user based on the value.
 */
API_AVAILABLE(ios(13.0))
typedef NS_ENUM(NSInteger, ARCoachingGoal) {
    /**
     A goal that specifies your app requires basic world tracking.

     When you use this goal, coaching overlay won't hide until the user has moved their device in a way that facilitates ARKit starting up a basic
     world tracking session.
     */
    ARCoachingGoalTracking,
    /**
     A goal that specifies your app requires a horizontal plane.

     When you use this goal, coaching overlay won't hide until the user has moved their device in a way that facilitates ARKit finding at least one
     horizontal surface.
     */
    ARCoachingGoalHorizontalPlane,
    /**
     A goal that specifies your app requires a vertical plane.

     When you use this goal, coaching overlay won't hide until the user has moved their device in a way that facilitates ARKit finding at least one
     vertical surface.
     */
    ARCoachingGoalVerticalPlane,
    /**
     A goal that specifies your app requires a plane of any type.

     When you use this goal, coaching overlay won't hide until the user has moved their device in a way that facilitates ARKit finding at least one
     surface. For the available surface types, see ``ARPlaneClassification``.
     */
    ARCoachingGoalAnyPlane,
    /**
     A goal that specifies your app requires a precise geographic location.

     When you set this goal, the coaching overlay provides the user instructions when they start a geotracking session, or when they go off course
     during a session.
     */
    ARCoachingGoalGeoTracking,
} NS_SWIFT_NAME(ARCoachingOverlayView.Goal);

/**
 A view that displays standardized onboarding instructions to direct users toward a specific goal.

 This view offers your users a standardized onboarding routine. You can configure this view to automatically display during session initialization and
 in limited tracking situations, while giving the user specific instructions that best facilitate ARKit's world tracking.

 When you start your app, the coaching overlay asks the user to move the device in ways that help ARKit establish tracking. When you choose a specific
 goal like finding a plane, the view tailors its instructions accordingly. After the coaching overlay determines the goal has been met and no further
 coaching is required, it hides from the user's view.

 For an example app that uses the coaching overlay, see <doc:placing-objects-and-handling-3d-interaction>.

 ### Supporting Automatic Coaching

 By default, ``activatesAutomatically`` is enabled and therefore you should override
 ``ARCoachingOverlayViewDelegate/coachingOverlayViewWillActivate(_:)`` to determine whether coaching is in progress. Coordinate your actions to help
 the user focus on these instructions, for example, by hiding any UI that's not necessary while the session reinitializes.

 ### Relocalizing After an Interruption

 If relocalization is enabled (see ``ARSessionObserver/sessionShouldAttemptRelocalization(_:)``), ARKit attempts to restore your session if any
 interruptions degrade your app's tracking state. In this event, the coaching overlay presents itself and gives the user instructions to assist ARKit
 with relocalizing.

 During this time, the coaching overlay includes a button that lets the user indicate they'd like to start over rather than restore the session.

 ARKit notifies you when the user presses Start Over by calling your delegate's
 ``ARCoachingOverlayViewDelegate/coachingOverlayViewDidRequestSessionReset(_:)`` function. Implement this callback if your app requires any custom
 actions to restart the AR experience.

 ```swift
 func coachingOverlayViewDidRequestSessionReset(_ coachingOverlayView: ARCoachingOverlayView) {

     // Reset the session.
     let configuration = ARWorldTrackingConfiguration()
     configuration.planeDetection = [.horizontal, .vertical]
     session.run(configuration, options: [.resetTracking])

     // Custom actions to restart the AR experience.
     // ...
 }
 ```

 If you do not implement ``ARCoachingOverlayViewDelegate/coachingOverlayViewDidRequestSessionReset(_:)``, the coaching overlay responds to the Start
 Over button by resetting tracking, which also removes any existing anchors.

 For more information about relocalization, see <doc:managing-session-life-cycle-and-tracking-quality>.
*/
API_AVAILABLE(ios(13.0))
API_DEPRECATED("This API is deprecated on visionOS.", visionos(1.0, 1.0))
@interface ARCoachingOverlayView : UIView

/**
 An object you supply that implements coaching event callbacks.

 Normally, you set the value of this property to your app's view controller.
 */
@property (nonatomic, weak, nullable) IBOutlet id<ARCoachingOverlayViewDelegate> delegate;

/**
 An object you designate that provides the current session.

 Use this property to set the coaching overlay's ``ARCoachingOverlayView/session`` when loading from a storyboard. If you set this property at
 runtime, the coaching overlay keeps its ``ARCoachingOverlayView/session`` property up to date for you. If your app recreates its ``ARSession`` at any
 point, you may find it convenient to set the ``ARCoachingOverlayView/sessionProvider`` once rather than update the coaching overlay's
 ``ARCoachingOverlayView/session`` manually.
*/
@property (nonatomic, weak, nullable) IBOutlet NSObject<ARSessionProviding> *sessionProvider;

/**
 The session this view uses to provide coaching.

 The coaching overlay monitors your app's ``ARSession`` and reacts according to its tracking status. You don't need to set this property if you set
 ``ARCoachingOverlayView/sessionProvider`` instead.
 */
@property (nonatomic, strong, nullable) ARSession *session;

/**
 A field that indicates your app's tracking requirements.

 The goal you choose determines the particular instructions the coaching overlay presents to the user.
 */
@property (nonatomic, assign) ARCoachingGoal goal;

/**
 A flag that indicates whether the coaching view activates automatically, depending on the current session state.

 The default value is <doc://com.apple.documentation/documentation/swift/true>. If enabled, the coaching overlay sets
 ``ARCoachingOverlayView/isActive`` automatically, depending on whether it needs user intervention to meet the current
 ``ARCoachingOverlayView/goal-swift.property``. The coaching overlay activates when the session is initializing or when tracking conditions have
 degraded past a certain threshold.
*/
@property (nonatomic, assign) BOOL activatesAutomatically;

/**
 A flag that indicates whether coaching is in progress.

 If ``ARCoachingOverlayView/activatesAutomatically`` is enabled, this flag tells you whether coaching is in progress. Assign a
 ``ARCoachingOverlayView/delegate`` to coordinate your actions with the coaching overlay and allow
 ``ARCoachingOverlayViewDelegate/coachingOverlayViewWillActivate(_:)`` to notify you when the coaching overlay is active.

 When the coaching overlay is deactivating, ``ARCoachingOverlayView/isActive`` is <doc://com.apple.documentation/documentation/swift/false>. If the
 `animated` property of ``ARCoachingOverlayView/setActive(_:animated:)`` is <doc://com.apple.documentation/documentation/swift/true>,
 ``ARCoachingOverlayView/isActive`` and <doc://com.apple.documentation/documentation/uikit/uiview/ishidden> are
 <doc://com.apple.documentation/documentation/swift/false> while the coaching overlay is fading out. When the coaching overlay is deactivated without
 animation, or when the animation finishes, ARKit notifies you by calling ``ARCoachingOverlayViewDelegate/coachingOverlayViewDidDeactivate(_:)``.
 */
@property (nonatomic, readonly) BOOL isActive;

/**
 Controls whether coaching is in progress.

 On activation the view will check the current session, and if relocalization is needed it will present a modified UI with
 relocalization coaching and a reset button.

 On deactivation the view will become hidden.

 If the `animated` property of ``ARCoachingOverlayView/setActive(_:animated:)`` is <doc://com.apple.documentation/documentation/swift/true>,
 ``ARCoachingOverlayView/isActive`` and <doc://com.apple.documentation/documentation/uikit/uiview/ishidden> are
 <doc://com.apple.documentation/documentation/swift/false> while the coaching overlay is fading out. When the coaching overlay is deactivated without
 animation, or when the animation finishes, ARKit notifies you by calling ``ARCoachingOverlayViewDelegate/coachingOverlayViewDidDeactivate(_:)``.

 - Parameters:
   - active: A flag you set to indicate whether the coaching overlay should activate or deactivate.
   - animated: A flag that when <doc://com.apple.documentation/documentation/swift/true>, fades the coaching overlay in or out. When you pass a value
 of <doc://com.apple.documentation/documentation/swift/false>, the coaching overlay shows or hides instantly.
*/
- (void)setActive:(BOOL)active animated:(BOOL)animated;

@end

/**
 A set of callbacks you implement to be notified of coaching events.

 Implement a delegate to coordinate your app's actions with coaching overlay. For example, when the coaching overlay determines the user needs
 guidance, you hide your app's UI to allow the user to focus on the coaching experience. When the coaching overlay determines the
 ``ARCoachingOverlayView/goal-swift.property`` is met, you show your app's UI and begin your app's AR experience.
 */
API_AVAILABLE(ios(13.0))
API_DEPRECATED("This API is deprecated on visionOS.", visionos(1.0, 1.0))
@protocol ARCoachingOverlayViewDelegate <NSObject>

@optional

/**
 Tells you when the user taps the coaching overlay view's Start Over button while the session is relocalizing.

 Implement this function to do the actions your app requires to restart the AR experience. For example, you might hide custom relocalization UI,
 deallocate resources, or restore virtual content to a starting location.

 If you don't implement this function, the coaching overlay resets the session for you––equivalent to calling ``ARSession/run(_:options:)`` with the
 ``ARSession/RunOptions/resetTracking`` option––when the user taps Start Over.

 - Parameter coachingOverlayView: The view currently active.
*/
- (void)coachingOverlayViewDidRequestSessionReset:(ARCoachingOverlayView *)coachingOverlayView;

/**
 Tells you when the coaching overlay view activates.

 Override this function to hide your app's UI while the coaching overlay is active.

 - Parameter coachingOverlayView: The view that will be activated.
*/
- (void)coachingOverlayViewWillActivate:(ARCoachingOverlayView *)coachingOverlayView;

/**
 Tells you when the coaching experience is completely deactivated.

 Implement this function to do any custom actions your app requires to begin the AR experience. For example, when coaching is deactivated, your app
 might restore custom UI.

 When the coaching overlay is deactivating, ``ARCoachingOverlayView/isActive`` is <doc://com.apple.documentation/documentation/swift/false>. If the
 `animated` property of ``ARCoachingOverlayView/setActive(_:animated:)`` is <doc://com.apple.documentation/documentation/swift/true>,
 ``ARCoachingOverlayView/isActive`` and <doc://com.apple.documentation/documentation/uikit/uiview/ishidden> are
 <doc://com.apple.documentation/documentation/swift/false> while the coaching overlay is fading out. When the coaching overlay is deactivated without
 animation, or when the animation finishes, ARKit sends a ``ARCoachingOverlayViewDelegate/coachingOverlayViewDidDeactivate(_:)`` notification.

 - Parameter coachingOverlayView: The view that was deactivated.
*/
- (void)coachingOverlayViewDidDeactivate:(ARCoachingOverlayView *)coachingOverlayView;

@end

NS_ASSUME_NONNULL_END

API_UNAVAILABLE_END
