#if (defined(USE_ARKIT_PUBLIC_HEADERS) && USE_ARKIT_PUBLIC_HEADERS) || !__has_include(<ARKitCore/ARError.h>)
//
//  ARError.h
//  ARKit
//
//  Copyright © 2016-2021 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <TargetConditionals.h>

NS_ASSUME_NONNULL_BEGIN

API_UNAVAILABLE_BEGIN(visionos)

/**
 The domain for error objects produced by an AR session.
 */
API_AVAILABLE(ios(11.0))
FOUNDATION_EXTERN NSString *const ARErrorDomain;

/**
 Codes that identify errors in ARKit.
 */
API_AVAILABLE(ios(11.0))
typedef NS_ERROR_ENUM(ARErrorDomain, ARErrorCode){
    /**
     An error that indicates the device lacks support for the session's configuration.

     Call ``ARConfiguration/isSupported`` on an ``ARConfiguration`` to ensure it's supported
     before attempting to create and run it on the session with ``ARSession/runWithConfiguration:``.
     */
    ARErrorCodeUnsupportedConfiguration = 100,

    /**
     An error that indicates the framework fails to access a required sensor.
     */
    ARErrorCodeSensorUnavailable = 101,

    /**
     An error that indicates a sensor fails to provide required input.
     */
    ARErrorCodeSensorFailed = 102,

    /**
     An error that indicates the app lacks user permission for the camera.

     To use the device's camera:

     - Your app's Info.plist file must provide a message for the
     [NSCameraUsageDescription](https://developer.apple.com/library/archive/documentation/General/Reference/InfoPlistKeyReference/Articles/CocoaKeys.html#//apple_ref/doc/plist/info/NSCameraUsageDescription)
     key. If this key is missing, any attempt to run an AR session fails with this error.
     - When your app first attempts to run an AR session or otherwise use the camera, iOS automatically shows an alert with your camera usage
     description message, asking the user to grant camera permission to your app. If the user accepts this request, the session begins; otherwise the
     session fails with this error.
     - If the user has previously denied camera permission for your app, all attempts to run an AR session or otherwise use the camera fail with this
     error. To grant camera permission, the user must explicitly enable your app in the iOS Settings app, under Privacy > Camera.
     */
    ARErrorCodeCameraUnauthorized = 103,

    /**
     An error that indicates the app lacks user permission for the microphone.

     When this error occurs, the app needs to prompt the user to give permission to use the
     microphone in Settings.
     */
    ARErrorCodeMicrophoneUnauthorized = 104,

    /**
     An error that indicates the app lacks user permission for the device's current location.

     To resolve this issue, the app needs to ask the user to enable location access for this
     app in Settings.
     */
    ARErrorCodeLocationUnauthorized API_AVAILABLE(ios(14.0)) = 105,

    /**
     An error that indicates the system needs to finish a high-resolution frame request before accepting another request.

     The system provides this error to the completion handler of
     ``ARSession/captureHighResolutionFrame(completion:)`` for failed operations.
     */
    ARErrorCodeHighResolutionFrameCaptureInProgress API_AVAILABLE(ios(16.0)) = 106,

    /**
     An error that indicates a problem in the system's capture pipeline.

     The system provides this error to the completion handler of
     ``ARSession/captureHighResolutionFrame(completion:)`` for failed operations.
     */
    ARErrorCodeHighResolutionFrameCaptureFailed API_AVAILABLE(ios(16.0)) = 107,

    /**
     An error that indicates world tracking experienced an unrecoverable problem.
     */
    ARErrorCodeWorldTrackingFailed = 200,

    /**
     An error that indicates a location lacks geotracking support.

     This error code indicates that ARKit does not have the necessary localization imagery to
     support geo tracking at the user's current location. See
     ``ARGeoTrackingConfiguration/checkAvailability(completionHandler:)`` for more information.

     If ``ARGeoTrackingConfiguration/checkAvailability(completionHandler:)`` returns
     <doc://com.apple.documentation/documentation/swift/true> and an app begins a geo-tracking
     session, ARKit provides this error when the user has moved to an unsupported area.
     */
    ARErrorCodeGeoTrackingNotAvailableAtLocation API_AVAILABLE(ios(14.0)) = 201,

    /**
     An error that indicates localization imagery fails to match the device's camera captures.

     ARKit returns this error code when visual localization is taking too long.
     This situation indicates that the app has met all requirements for geo tracking except for
     visual localization. To try again, the app needs to ask the user pan the device around the
     physical environment to acquire different camera-feed imagery. For more information, see
     <doc:ARGeoTrackingStatus/State/localizing#Assisting-the-User-with-Visual-Localization>.
     */
    ARErrorCodeGeoTrackingFailed API_AVAILABLE(ios(14.0)) = 202,

    /**
     An error that indicates the framework fails to process a reference image.

     This error occurs when you supply a reference image to the configuration's
     ``ARWorldTrackingConfiguration/detectionImages`` but ARKit determined it's unusable. This can
     happen when the image data doesn't contain enough features to identify a unique picture, for
     example, it's all white.
     */
    ARErrorCodeInvalidReferenceImage API_AVAILABLE(ios(11.3)) = 300,

    /**
     An error that indicates the framework fails to process a reference object.

     Occurs when the framework can't load a reference object, when the reference object's format
     doesn't support a requested operation, or when a configuration mixes legacy `.arobject` and
     `.referenceobject` reference objects in the same session. Inspect `userInfo` for the specific
     reason.
     */
    ARErrorCodeInvalidReferenceObject API_AVAILABLE(ios(12.0)) = 301,

    /**
     An error that indicates the framework fails to process a world map.
     */
    ARErrorCodeInvalidWorldMap API_AVAILABLE(ios(12.0)) = 302,

    /**
     An error that indicates the configuration contains ambiguous or erroneous data.
     */
    ARErrorCodeInvalidConfiguration API_AVAILABLE(ios(12.0)) = 303,

    /**
     An error that indicates the framework fails to parse collaboration data the app receives over the network.

     ARKit produces this error when an app passes invalid data into the ``ARSession/update(with:)``
     function.
     */
    ARErrorCodeInvalidCollaborationData API_AVAILABLE(ios(13.2)) = 304,

    /**
     An error that indicates the framework requires more features to complete a task.

     For more information about a session's feature requirements, see
     <doc:managing-session-life-cycle-and-tracking-quality>.
     */
    ARErrorCodeInsufficientFeatures API_AVAILABLE(ios(12.0)) = 400,

    /**
     An error that indicates the framework fails to merge a detected object.
     */
    ARErrorCodeObjectMergeFailed API_AVAILABLE(ios(12.0)) = 401,

    /**
     An error that indicates a file access fails to read or write.
     */
    ARErrorCodeFileIOFailed API_AVAILABLE(ios(12.0)) = 500,

    /**
     An error that indicates a request fails.
     */
    ARErrorCodeRequestFailed API_AVAILABLE(ios(14.0)) = 501,
};

API_UNAVAILABLE_END

NS_ASSUME_NONNULL_END
#else
#import <ARKitCore/ARError.h> 
#endif // #if (defined(USE_ARKIT_PUBLIC_HEADERS) \&\& USE_ARKIT_PUBLIC_HEADERS) || !__has_include(<ARKitCore/ARError.h>)