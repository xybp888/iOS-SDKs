//
//  ARGeoTrackingTypes.h
//  ARKit
//
//  Copyright © 2020 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

API_UNAVAILABLE_BEGIN(visionos)

/**
 Options for setting a location anchor's altitude.

 Each altitude source has unique performance and accuracy characteristics.
 */
API_AVAILABLE(ios(14.0))
typedef NS_ENUM(NSInteger, ARAltitudeSource) {
    /** Altitude isn't yet set. */
    ARAltitudeSourceUnknown,

    /** The framework sets the altitude using a coarse digital-elevation model.

     The accuracy of this altitude is noticeably imprecise at close range, but it's sufficient from far away. Use this option to save computational
     resources for anchors that are far off in the distance. */
    ARAltitudeSourceCoarse,

    /** The framework sets the altitude using a high-resolution digital-elevation model. */
    ARAltitudeSourcePrecise,

    /** The app defines the altitude.

     ARKit records this altitude source when your app defines a geo anchor's altitude.

     You may acquire altitude by providing a particular scene coordinate to the session using
     ``ARSession/getGeoLocation(forPoint:completionHandler:)``.

     For example, your app might set a geo anchor's altitude by raycasting a surface, then adding an arbitrary `y-`amount to make the anchor more
     visible from afar. */
    ARAltitudeSourceUserDefined
} NS_SWIFT_NAME(ARGeoAnchor.AltitudeSource);

/**
 Values that are possible for the current state of geo tracking.

 For any ``ARGeoTrackingStatus/state`` in a frame's ``ARFrame/geoTrackingStatus``, ARKit provides a ``ARGeoTrackingStatus/stateReason``. A given
 geo tracking status may intermix states and reasons, so the reasons are not tied to specific states.
 */
API_AVAILABLE(ios(14.0))
typedef NS_ENUM(NSInteger, ARGeoTrackingState) {
    /** Geo tracking is not available.

     This state occurs when ARKit doesn't have the landscape data necessary for visual localization at the user's location. For more information, see
     ``ARGeoTrackingStatus/State/localizing``. */
    ARGeoTrackingStateNotAvailable,

    /** The session is initializing geo tracking.

     In this state, the session is preparing tracking and an app has the opportunity to onboard users to the experience. The app watches for changes
     in ``ARGeoTrackingStatus/stateReason`` and coaches the user accordingly to expedite initialization. */
    ARGeoTrackingStateInitializing,

    /** Geo tracking is attempting to localize against a map.

     In this state, the session downloads localization imagery for the user's geographic location and compares it with captures from the device's
     camera. This process is referred to as _visual localization_. When ARKit succeeds in matching this imagery with captures from the camera, the
     state moves to ``ARGeoTrackingStatus/State/localized`` and the app is free to create location anchors. For more information about localization
     imagery, see <doc:ARGeoTrackingConfiguration#Refine-the-users-position-with-imagery>.

     ### Assisting the User with Visual Localization

     To establish visual localization, the user must move the camera so it acquires the captures that ARKit needs. To elicit the right user movements
     in this state, the app needs to advise the user to:

     - Point the camera at buildings and other visual landmarks to help ARKit match the live camera data with its preexisting landscape-data.
     - Avoid pointing the device at objects that are too general, like trees. It's better to focus on distinct visuals, like structures, or signs.
     - Avoid pointing the device at real-world objects that are transient, like parked cars, or a construction site.
     - Because lighting conditions can affect visual localization, avoid geo tracking at night. */
    ARGeoTrackingStateLocalizing,

    /** Geo tracking is localized.

     In this state, ARKit has completed visual localization and the app is free to place location anchors (``ARGeoAnchor``). */
    ARGeoTrackingStateLocalized,
} NS_SWIFT_NAME(ARGeoTrackingStatus.State);

/**
 Values that are possible for the current accuracy of geo tracking.

 To ensure the best possible user experience, an app must monitor and react to the geo tracking accuracy. When accuracy is
 ``ARGeoTrackingStatus/Accuracy/low``, the app needs to show content that's more forgiving if ARKit is off by a small distance. For example, if
 accuracy is ``ARGeoTrackingStatus/Accuracy/low``, rendering a location anchor as a large ball several meters in the air is more appropriate than
 rendering an arrow that rests its point on a real-world surface. Because a larger ball isn't meant to mark a precise location, any offset that
 results from low accuracy will be less noticeable to the user.

 Apps that need higher-precision location anchors need to wait for ``ARGeoTrackingStatus/Accuracy/medium`` or ``ARGeoTrackingStatus/Accuracy/high``
 accuracy before revealing rendered location-anchors, or dismissing user instructions.
 */
API_AVAILABLE(ios(14.0))
typedef NS_ENUM(NSInteger, ARGeoTrackingAccuracy) {
    /** Geo tracking accuracy is undetermined.

     This value indicates that because the session has not completed visual localization, geo tracking accuracy is indeterminate. */
    ARGeoTrackingAccuracyUndetermined,

    /** Geo tracking accuracy is low.

     This value indicates that visual localization is complete and geo tracking accuracy is low.

     One technique an app can use to deal with low accuracy is to render location anchors with an asset that's more forgiving, like a large ball. If
     an app renders the ball further in the air, any offset that results from low accuracy will be less noticeable, and less critical to the user. */
    ARGeoTrackingAccuracyLow,

    /** Geo tracking accuracy is average.

     This value indicates that visual localization is complete and geo tracking accuracy is average. */
    ARGeoTrackingAccuracyMedium,

    /** Geo tracking accuracy is high.

     This value indicates that visual localization is complete and geo tracking accuracy is very good. */
    ARGeoTrackingAccuracyHigh
} NS_SWIFT_NAME(ARGeoTrackingStatus.Accuracy);

/**
 The reasons that describe a geo tracking session's status.

 These possible values of ``ARGeoTrackingStatus/stateReason`` provide more information about a geo tracking session's current
 ``ARGeoTrackingStatus/state``.
 */
API_AVAILABLE(ios(14.0))
typedef NS_ENUM(NSInteger, ARGeoTrackingStateReason) {
    /** No issues reported.

     This reason indicates that there is no user action currently needed to improve the geo tracking state. */
    ARGeoTrackingStateReasonNone,

    /** The location doesn't provide geo tracking.

     This reason indicates that ARKit does not have the necessary landscape data to support geo tracking at the user's current location. See
     ``ARGeoTrackingConfiguration/checkAvailability(completionHandler:)`` for more information.

     If ``ARGeoTrackingConfiguration/checkAvailability(completionHandler:)`` returns <doc://com.apple.documentation/documentation/swift/true> and an
     app begins a geo tracking session, ARKit provides this state reason when the user has moved to an unsupported area. */
    ARGeoTrackingStateReasonNotAvailableAtLocation,

    /** The location requires user permission for geo tracking.

     This reason indicates that the user has not given this app permission to access the user's location. To enable geo tracking, an app needs to ask
     the user to enable location sharing for this app in Settings. */
    ARGeoTrackingStateReasonNeedLocationPermissions,

    /** The position or motion of the device makes geo tracking unstable.

     This reason indicates that ARKit's local-space tracking is functioning at a limited capacity. To retrieve more information about the cause, an
     app needs to refer to the camera's ``ARCamera/trackingState-9pgmq``. For the possible causes of this state, see ``ARTrackingState`` and
     ``ARTrackingStateReason``. */
    ARGeoTrackingStateReasonWorldTrackingUnstable,

    /** A state in which the framework performs a check for the user's GPS position.

     While in this state, the app needs to wait for the Core Location subsystem to provide the user's GPS location. Inform the user of the check in
     progress; for instance, present a message alerting them to the geo tracking initialization process. */
    ARGeoTrackingStateReasonWaitingForLocation,

    /** A state in which the framework performs a check for geo tracking availability at the user's location.

     While in this state, the app waits for the geo tracking subsystem to determine geo tracking availability at the user's GPS location. Inform the
     user of the check in progress; for instance, present a message alerting them to the geo tracking initialization process. */
    ARGeoTrackingStateReasonWaitingForAvailabilityCheck,

    /** A state in which the framework downloads localization imagery.

     ARKit provides this reason in state ``ARGeoTrackingStatus/State/localizing`` when the session is actively attempting to download localization
     imagery (see <doc:ARGeoTrackingConfiguration#Refine-the-users-position-with-imagery>).

     If this state persists for too long, it may indicate a network issue. If a reasonable amount of time elapses in this state reason, the app may
     consider requesting that the user check their internet connection. */
    ARGeoTrackingStateReasonGeoDataNotLoaded,

    /** The position of the device is too low for geo tracking.

     ARKit provides the app with this reason when the app is in state ``ARGeoTrackingStatus/State/localizing`` and the device is not capturing enough
     of the necessary live-camera imagery needed for visual localization because the user is pointing the camera too low. To resolve the issue, the
     app needs to instruct the user to raise the device and follow the guidance in
     <doc:ARGeoTrackingStatus/State/localizing#Assisting-the-User-with-Visual-Localization>. */
    ARGeoTrackingStateReasonDevicePointedTooLow,

    /** Localization imagery failed to match the view from the device's camera.

     ARKit provides this reason when visual localization is taking too long. This indicates that the app has met all requirements for geo tracking,
     except for visual localization. In this situation, the app needs to ask the user to pan the device around the physical environment to acquire
     more camera-feed imagery. For more information, see <doc:ARGeoTrackingStatus/State/localizing#Assisting-the-User-with-Visual-Localization>. */
    ARGeoTrackingStateReasonVisualLocalizationFailed
} NS_SWIFT_NAME(ARGeoTrackingStatus.StateReason);

/**
 The state, accuracy, and reason that are possible for geo tracking's current condition.

 Geo tracking requires coordination with the user at various phases of the geo tracking lifecycle. To elicit the right user actions, an app needs to
 provide clear instructions to the user based on the current frame's ``ARFrame/geoTrackingStatus``:

 - Geo tracking ``state`` most notably regards the important process in which ARKit acquires a better understanding of the user's geographic location
 and orientation than is possible with GPS and the compass heading alone. See ``State/localizing`` for more information.
 - Given a particular ``state``, the app needs to tailor its user messaging according to the ``stateReason``.
 - An app may need to monitor ``accuracy`` closely if it requires high-precision localization.
 */
API_AVAILABLE(ios(14.0))
NS_SWIFT_SENDABLE
@interface ARGeoTrackingStatus : NSObject <NSCopying, NSSecureCoding>

/**
 A value that describes the session's current geo tracking state.

 For any ``ARGeoTrackingStatus/state`` in a frame's ``ARFrame/geoTrackingStatus``, ARKit provides a ``ARGeoTrackingStatus/stateReason``. A given
 geo tracking status may intermix states and reasons, so the reasons are not tied to specific states.
 */
@property (nonatomic, readonly) ARGeoTrackingState state;

/**
 The accuracy of geo tracking at the time the session captured the frame.

 ARKit populates this property after reaching ``ARGeoTrackingStatus/State/localized``. To ensure the best possible user experience, an app must
 monitor and react to the geo tracking accuracy. For more information, see ``ARGeoTrackingStatus/Accuracy``.
*/
@property (nonatomic, readonly) ARGeoTrackingAccuracy accuracy;

/**
 The reasons for the app's geo tracking status.

 These possible values provide more information about a geo tracking session's current ``state``.
 */
@property (nonatomic, readonly) ARGeoTrackingStateReason stateReason;

/**
 Unavailable. Geo tracking status objects are created by the system.

 - Returns: This method is unavailable.
*/
- (instancetype)init NS_UNAVAILABLE;

/**
 Unavailable. Geo tracking status objects are created by the system.

 - Returns: This method is unavailable.
*/
+ (instancetype)new NS_UNAVAILABLE;

@end

API_UNAVAILABLE_END

NS_ASSUME_NONNULL_END

