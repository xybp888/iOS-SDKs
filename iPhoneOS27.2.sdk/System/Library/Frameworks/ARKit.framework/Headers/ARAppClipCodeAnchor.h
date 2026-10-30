#if (defined(USE_ARKIT_PUBLIC_HEADERS) && USE_ARKIT_PUBLIC_HEADERS) || !__has_include(<ARKitCore/ARAppClipCodeAnchor.h>)
#import <TargetConditionals.h>
//
//  ARAppClipCodeAnchor.h
//  ARKit
//
//  Copyright © 2016-2021 Apple Inc. All rights reserved.
//

#import <ARKit/ARAnchor.h>

NS_ASSUME_NONNULL_BEGIN

API_UNAVAILABLE_BEGIN(visionos)

/**
 The states in the process of decoding an App Clip Code URL.
*/
API_AVAILABLE(ios(14.3))
typedef NS_ENUM(NSInteger, ARAppClipCodeURLDecodingState) {
    /**
     A state that indicates the continuing process of decoding an App Clip Code's URL.

     The App Clip Code anchor's ``ARAppClipCodeAnchor/url`` is `nil` in this state.
     */
    ARAppClipCodeURLDecodingStateDecoding,

    /**
     A state that indicates the failure to decode an App Clip Code's URL.

     The decoding of an App Clip Code URL fails under these circumstances:

     - The full app or App Clip is missing the associated-domains entitlement from its code signature.
     - The host of the resource identified by the App Clip Code URL doesn't vend an Apple App Site Association (AASA) file.
     - The AASA file hosted at the App Clip Code URL's domain lacks the App Clip's fully-qualified application identifier.
     - The App Clip Code is not associated to the App Clip in an App Clip experience in App Store Connect.

     For more information, see <doc://com.apple.documentation/documentation/appclip/configuring-the-launch-experience-of-your-app-clip>.
     */
    ARAppClipCodeURLDecodingStateFailed,

    /**
     A state that indicates the completed decoding of an App Clip Code URL.

     The App Clip Code anchor's ``ARAppClipCodeAnchor/url`` is defined in this state.
     */
    ARAppClipCodeURLDecodingStateDecoded
} NS_SWIFT_NAME(ARAppClipCodeAnchor.URLDecodingState);

/**
 An anchor that tracks the position and orientation of an App Clip Code in the physical environment.

 Your App Clip gives users immediate access to critical or context-specific parts of your app's AR experience, and makes it easy for them to download
 and launch your full app if they choose.

 You can use physical App Clip Codes in the real world to enable users to discover your App Clip. An App Clip Code includes a unique URL and can
 incorporate an NFC tag. When users hold their iPhone near the code or scan it with the camera or Code Scanner in Control Center, the system offers to
 launch the code's associated App Clip.

 For more on App Clip Codes, see <doc://com.apple.documentation/documentation/appclip>. For an app that reacts to App Clip Codes in AR, see
 <doc://com.apple.documentation/documentation/appclip/interacting-with-app-clip-codes-in-ar>.

 ### Distinguish Between App Clip Codes

 There may be multiple App Clip Codes visible in the camera feed that share the same ``url``, so ARKit also relies on the App Clip Code's location
 (see ``ARAnchor/transform``) to distinguish different App Clip Codes in the physical environment.

 When the framework recognizes an App Clip Code, it initializes an ``ARAppClipCodeAnchor`` and passes it to the session delegate via
 ``ARSessionDelegate/session(_:didAdd:)``. If a recognized App Clip Code becomes obscured or is no longer visible in the camera feed, the framework
 sets the anchor's ``ARTrackable/isTracked`` property to <doc://com.apple.documentation/documentation/swift/false> and passes it into the
 ``ARSessionDelegate/session(_:didUpdate:)-3qtt8`` callback. If the same App Clip Code becomes visible once again:

 - ARKit sets ``ARTrackable/isTracked`` to <doc://com.apple.documentation/documentation/swift/true> if the App Clip Code maintained its relative
 position in the physical environment.
 - ARKit initializes a new ``ARAppClipCodeAnchor`` if the App Clip Code position in the physical environment changed significantly.

 ### Remove App Clip Codes

 To prevent App Clip Codes from accumulating in the session, ARKit removes anchors by passing them in to the
 ``ARSessionDelegate/session(_:didRemove:)`` callback. ARKit removes an ``ARAppClipCodeAnchor`` if all of the following conditions are true:

 - The framework instantiates a new ``ARAppClipCodeAnchor``.
 - The new anchor's ``url`` matches one or more existing anchors with substantially different positions in the physical environment.
 - The existing anchors are untracked (``ARTrackable/isTracked`` is <doc://com.apple.documentation/documentation/swift/false>).
 */
API_AVAILABLE(ios(14.3))
NS_SWIFT_SENDABLE
@interface ARAppClipCodeAnchor : ARAnchor <ARTrackable>

/**
 The URL encoded in an App Clip Code.

 To enable users to decode your App Clip code's URL from an App Clip or within an AR app, associate your App Clip with its App Clip Code(s) in App
 Store Connect; for more information, see [set up an App Clip experience](https://help.apple.com/app-store-connect/#/dev5b665db74). Because each App
 Clip Code belongs to a specific App Clip experience, you can decode an App Clip Code URL in a full app's AR experience only after first providing an
 accompanying App Clip.

 This property is `nil` by default. The framework sets a value for this property when ``ARAppClipCodeAnchor/urlDecodingState`` is
 ``ARAppClipCodeAnchor/URLDecodingState/decoded``. This property remains `nil` for App Clip Codes that belong to another App Clip experience or
 development team.

 ### Distribute Your App and App Clip for Testing

 Although you can launch an App Clip from the camera after creating an App Clip local experience, ARKit checks the App Clip experience registry in App
 Store Connect to determine if your App Clip associates to a particular App Clip Code URL. When ARKit confirms that an App Clip Code in the physical
 environment belongs to your App Clip experience, the framework sets the value of this property.

 After setting up an App Clip experience, distribute your app to testers; for more information, see
 <doc://com.apple.documentation/documentation/appclip/testing-the-launch-experience-of-your-app-clip>.
 */
@property (nonatomic, copy, nullable, readonly) NSURL *url;

/**
 A state that indicates the process of decoding an App Clip Code URL.

 The initial value of this property is ``ARAppClipCodeAnchor/URLDecodingState/decoding``.
 */
@property (nonatomic, assign, readonly) ARAppClipCodeURLDecodingState urlDecodingState;

/**
 The App Clip Code's radius in meters.

 ARKit estimates the value of this property at runtime. As the user views an App Clip Code from different angles, ARKit refines its estimate of the
 true radius of the App Clip Code.
 */
@property (nonatomic, assign, readonly) float radius;

/**
 Unavailable. App Clip Code anchors are created by the system.

 - Parameter transform: The transformation matrix.

 - Returns: This method is unavailable.
*/
- (instancetype)initWithTransform:(simd_float4x4)transform NS_UNAVAILABLE;

/**
 Unavailable. App Clip Code anchors are created by the system.

 - Parameters:
   - name: The anchor name.
   - transform: The transformation matrix.

 - Returns: This method is unavailable.
*/
- (instancetype)initWithName:(NSString *)name transform:(simd_float4x4)transform NS_UNAVAILABLE;

@end

API_UNAVAILABLE_END

NS_ASSUME_NONNULL_END

#else
#import <ARKitCore/ARAppClipCodeAnchor.h> 
#endif // #if (defined(USE_ARKIT_PUBLIC_HEADERS) \&\& USE_ARKIT_PUBLIC_HEADERS) || !__has_include(<ARKitCore/ARAppClipCodeAnchor.h>)