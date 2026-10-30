//
//  ARTrackingStatusTypes.h
//  ARKit
//
//  Copyright © 2020 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

API_UNAVAILABLE_BEGIN(visionos)

/**
 Possible values for position-tracking quality.
 */
API_AVAILABLE(ios(11.0))
typedef NS_ENUM(NSInteger, ARTrackingState) {
    /** Camera position tracking is not available. */
    ARTrackingStateNotAvailable,

    /**
     Tracking is available, but the quality of results is questionable.

     In this state, the positions and transforms of anchors in the scene (especially detected planes) may not be accurate or consistent from one
     captured frame to the next.

     See the associated ``ARTrackingStateReason`` value for information you can present to the user for improving tracking quality.
     */
    ARTrackingStateLimited,

    /** Camera position tracking is providing optimal results. */
    ARTrackingStateNormal,
} NS_REFINED_FOR_SWIFT;

/**
 Possible causes for limited position-tracking quality.
 */
API_AVAILABLE(ios(11.0))
typedef NS_ENUM(NSInteger, ARTrackingStateReason) {
    /**
     The current tracking state is not limited.

     This value occurs when the ``ARCamera/trackingState-9pgmq`` property is ``ARTrackingState/ARTrackingStateNotAvailable`` or
     ``ARTrackingState/ARTrackingStateNormal``.
     */
    ARTrackingStateReasonNone,

    /**
     The AR session has not yet gathered enough camera or motion data to provide tracking information.

     This value occurs temporarily after starting a new AR session or changing configurations.
     */
    ARTrackingStateReasonInitializing,

    /** The device is moving too fast for accurate image-based position tracking. */
    ARTrackingStateReasonExcessiveMotion,

    /** The scene visible to the camera does not contain enough distinguishable features for image-based position tracking. */
    ARTrackingStateReasonInsufficientFeatures,

    /**
     The AR session is attempting to resume after an interruption.

     ARKit cannot track device position or orientation when the session has been interrupted (for example, by dismissing the view hosting an AR
     session or switching to another app). When resuming the session after an interruption, you cannot be certain that the world coordinate system
     (used for placing anchors) matches the device's real-world environment.

     If your session or view delegate implements the ``ARSessionObserver/sessionShouldAttemptRelocalization(_:)`` method and returns
     <doc://com.apple.documentation/documentation/swift/true>, ARKit attempts to reconcile pre- and post-interruption world tracking state. During
     this process, called _relocalization_, world tracking quality is ``ARTrackingState/ARTrackingStateLimited``, with
     ``ARTrackingStateReason/ARTrackingStateReasonRelocalizing`` as the reason for limited quality.

     If successful, the relocalization process ends after a short time, tracking quality returns to the ``ARTrackingState/ARTrackingStateNormal``
     state, and the world coordinate system and anchor positions generally reflect their state before the interruption.

     However, the speed and success rate of relocalization can vary depending on real-world conditions. You may wish to hide AR content or disable UI
     during relocalization, and reset tracking if relocalization doesn't succeed within a time frame appropriate for your app.
     */
    ARTrackingStateReasonRelocalizing API_AVAILABLE(ios(11.3)),
} NS_REFINED_FOR_SWIFT;

API_UNAVAILABLE_END
