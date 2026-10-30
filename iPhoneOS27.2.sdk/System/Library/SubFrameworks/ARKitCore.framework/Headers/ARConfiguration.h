//
//  ARConfiguration.h
//  ARKit
//
//  Copyright © 2016-2021 Apple Inc. All rights reserved.
//

#import <AVFoundation/AVFoundation.h>
#import <CoreLocation/CoreLocation.h>
#import <Foundation/Foundation.h>

#import <ARKitCore/ARPlaneDetectionTypes.h>

NS_ASSUME_NONNULL_BEGIN

API_UNAVAILABLE_BEGIN(visionos)

@class ARReferenceImage;
@class ARReferenceObject;
@class ARVideoFormat;
@class ARWorldMap;

/**
 Types of optional frame features you can enable in your app.

 A frame semantic represents 2D information that ARKit extracts from a frame.
*/
API_AVAILABLE(ios(13.0))
typedef NS_OPTIONS(NSUInteger, ARFrameSemantics) {
    /** No semantic operation is run. */
    ARFrameSemanticNone = 0,

    /**
     An option that indicates that people occlude your app's virtual content.

     The `ARFrameSemanticPersonSegmentation` frame semantic specifies that any person ARKit detects in the camera feed occludes virtual
     content, regardless of the person's depth in the scene.

     When this option is enabled, ARKit sets the ``ARFrame/estimatedDepthData`` and ``ARFrame/segmentationBuffer`` properties to serve as a
     foundation for people occlusion. The standard renderers (<doc://com.apple.documentation/documentation/realitykit/arview>, and
     ``ARSCNView``) use those properties to implement people occlusion for you. See ``ARConfiguration/frameSemantics`` for more information.

     In the ``ARFrame/segmentationBuffer``, every pixel ARKit classifies as a person has an intensity value equal to ``ARSegmentationClassPerson``.

     - SeeAlso: ``ARFrame/segmentationBuffer``
     - SeeAlso: ``ARSegmentationClass``
    */
    ARFrameSemanticPersonSegmentation = (1 << 0),

    /**
     An option that indicates that people occlude your app's virtual content depending on depth.

     The `ARFrameSemanticPersonSegmentationWithDepth` frame semantic specifies that any person ARKit detects in the camera feed should occlude
     virtual content, depending on the person's depth in the scene.

     When this option is enabled, ARKit sets the ``ARFrame/estimatedDepthData`` and ``ARFrame/segmentationBuffer`` properties to serve as a
     foundation for people occlusion. The standard renderers (<doc://com.apple.documentation/documentation/realitykit/arview>, and
     ``ARSCNView``) use those properties to implement people occlusion for you. See ``ARConfiguration/frameSemantics`` for more information.

     In the ``ARFrame/segmentationBuffer``, every pixel ARKit classifies as a person has an intensity value equal to ``ARSegmentationClassPerson`` and
     an accompanying depth value in ``ARFrame/estimatedDepthData``.

     - SeeAlso: ``ARFrame/estimatedDepthData``
     - SeeAlso: ``ARFrame/segmentationBuffer``
     */
    ARFrameSemanticPersonSegmentationWithDepth = (1 << 1) | (1 << 0),

    /**
     An option that indicates that 2D body detection is enabled.

     When you set this option in your configuration's ``ARConfiguration/frameSemantics`` property, ARKit describes the joint positions of a
     body it detects in the camera image, using normalized coordinates. See ``ARFrame/detectedBody`` for more information.

     - SeeAlso: ``ARFrame/detectedBody``
     - SeeAlso: ``ARBody2D``
    */
    ARFrameSemanticBodyDetection = (1 << 2),

    /**
     An option that provides the distance from the device to real-world objects viewed through the camera.

     Enable this option on a world-tracking configuration (``ARWorldTrackingConfiguration``) to instruct ARKit to provide your app with the
     distance between the user's device and the real-world objects in the camera feed. ARKit samples this distance using the LiDAR scanner and
     provides the results through the ``ARFrame/sceneDepth`` property on the session's ``ARSession/currentFrame``.

     ARKit creates this object from LiDAR readings at the same time as the current frame. The data in ``ARFrame/sceneDepth`` reflects the distance
     from the device to real-world objects pictured in the frame's ``ARFrame/capturedImage``. Alternatively, ARKit provides a
     ``ARFrameSemanticSmoothedSceneDepth`` property that minimizes the difference in LiDAR readings across frames.

     ARKit supports scene depth only on LiDAR-capable devices, so call ``ARConfiguration/supportsFrameSemantics:`` to ensure device support
     before attempting to enable scene depth.

     - SeeAlso: ``ARFrame/sceneDepth``
    */
    ARFrameSemanticSceneDepth API_AVAILABLE(ios(14.0)) = (1 << 3),

    /**
     An option that provides the distance from the device to real-world objects, averaged across several frames.

     Enable this option on a world-tracking configuration (``ARWorldTrackingConfiguration``) to instruct ARKit to provide your app with the
     distance between the user's device and the real-world objects pictured in the frame's ``ARFrame/capturedImage``. ARKit samples this
     distance using the LiDAR scanner and provides the results through the ``ARFrame/smoothedSceneDepth`` property on the session's
     ``ARSession/currentFrame``.

     To minimize the difference in LiDAR readings across frames, ARKit processes the data as an average. The averaged readings reduce
     flickering to create a smoother motion effect when depicting objects with depth, as demonstrated in
     <doc:creating-a-fog-effect-using-scene-depth>. Alternatively, to access a discrete LiDAR reading at the instant the framework creates the
     current frame, use ``ARFrame/sceneDepth``.

     ARKit supports scene depth only on LiDAR-capable devices, so call ``ARConfiguration/supportsFrameSemantics:`` to ensure device support
     before attempting to enable scene depth.

     - SeeAlso: ``ARFrame/smoothedSceneDepth``
    */
    ARFrameSemanticSmoothedSceneDepth API_AVAILABLE(ios(14.0)) = (1 << 4),

} NS_SWIFT_NAME(ARConfiguration.FrameSemantics);

/**
 Options for how ARKit constructs a scene coordinate system based on real-world device motion.
 */
API_AVAILABLE(ios(11.0))
typedef NS_ENUM(NSInteger, ARWorldAlignment) {
    /**
     The coordinate system's y-axis is parallel to gravity, and its origin is the initial position of the device.

     The y-axis matches the direction of gravity as detected by the device's motion sensing hardware; that is, the vector `(0,-1,0)` points
     downward.

     The position and orientation of the device as of when the session configuration is first run determine the rest of the coordinate system:
     For the z-axis, ARKit chooses a basis vector `(0,0,-1)` pointing in the direction the device camera faces and perpendicular to the gravity
     axis. ARKit chooses a x-axis based on the z- and y-axes using the right hand rule—that is, the basis vector `(1,0,0)` is orthogonal to the
     other two axes, and (for a viewer looking in the negative-z direction) points toward the right.
    */
    ARWorldAlignmentGravity,

    /**
     The coordinate system's y-axis is parallel to gravity, its x- and z-axes are oriented to compass heading, and its origin is the initial
     position of the device.

     The y-axis matches the direction of gravity as detected by the device's motion sensing hardware; that is, the vector `(0,-1,0)` points
     downward.

     The x- and z-axes match the longitude and latitude directions as measured by Location Services. The vector `(0,0,-1)` points to true north
     and the vector `(-1,0,0)` points west. (That is, the positive x-, y-, and z-axes point east, up, and south, respectively.)

     Although this option fixes the _directions_ of the three coordinate axes to real-world directions, the _location_ of the coordinate
     system's origin is still relative to the device, matching the device's position as of when the session configuration is first run.

     - Note: Using gravity and heading alignment requires tracking the device's geographic location. Your app's Info.plist must include
     user-facing text for the
     [NSLocationUsageDescription](https://developer.apple.com/library/archive/documentation/General/Reference/InfoPlistKeyReference/Articles/CocoaKeys.html#//apple_ref/doc/plist/info/NSLocationUsageDescription)
     or
     [NSLocationWhenInUseUsageDescription](https://developer.apple.com/library/archive/documentation/General/Reference/InfoPlistKeyReference/Articles/CocoaKeys.html#//apple_ref/doc/plist/info/NSLocationWhenInUseUsageDescription)
     key so that the user can grant your app permission for location tracking.
    */
    ARWorldAlignmentGravityAndHeading,

    /**
     The scene coordinate system is locked to match the orientation of the camera.

     Camera alignment defines a coordinate system based on the native sensor orientation of the device camera. Relative to a
     <doc://com.apple.documentation/documentation/avfoundation/avcapturevideoorientation/landscaperight>-oriented camera image, the x-axis
     points to the right, the y-axis points up, and the z-axis points out the front of the device (toward the user).

     When this alignment is active, ARKit performs no device motion tracking. That is, world-space positions are effectively always relative to
     the current position and orientation of the device. (For example, a SceneKit object placed in an ``ARSCNView`` will thus maintain the same
     position on screen, even as the camera image changes while the device moves.)

     - Note: This coordinate system is always the same regardless of device or user interface orientation. That is, the x-axis always points
     along the long axis of the device, even if that direction is "down" relative to the user.
    */
    ARWorldAlignmentCamera
} NS_SWIFT_NAME(ARConfiguration.WorldAlignment);

/**
 The available environment texturing options for world tracking.

 Environment textures are cube-map textures that depict the view in all directions from a specific point in a scene. In 3D asset rendering,
 environment textures are the basis for image-based lighting algorithms where surfaces can realistically reflect light from their surroundings.
 ARKit generates environment textures during an AR session using camera imagery, allowing SceneKit or a custom-rendering engine to provide
 realistic image-based lighting for virtual objects in your AR experience.

 To enable texture map generation for your configuration, change this property (from its default value of `AREnvironmentTexturingNone`):

 - With `AREnvironmentTexturingManual` environment texturing, you identify points in the scene for which you want light probe texture maps by
 creating ``AREnvironmentProbeAnchor`` objects and adding them to the session.
 - With `AREnvironmentTexturingAutomatic` environment texturing, ARKit automatically creates, positions, and adds ``AREnvironmentProbeAnchor``
 objects to the session.

 In both cases, ARKit automatically generates environment textures as the session collects camera imagery. Use a delegate method such as
 ``ARSessionDelegate/session:didUpdateAnchors:`` to find out when a texture is available, and access it from the anchor's
 ``AREnvironmentProbeAnchor/environmentTexture`` property.

 If you display AR content using ``ARSCNView`` and the ``ARSCNView/automaticallyUpdatesLighting`` option, SceneKit automatically retrieves
 ``AREnvironmentProbeAnchor`` texture maps and uses them to light the scene.
 */
API_AVAILABLE(ios(12.0))
typedef NS_ENUM(NSInteger, AREnvironmentTexturing) {
    /** The framework doesn't generate environment textures. */
    AREnvironmentTexturingNone,

    /**
     The framework generates environment textures only for probe anchors you explicitly add to the session.

     When you use this environment texturing option, you must manually choose when and where to generate environment map textures:

     1. Create an ``AREnvironmentProbeAnchor`` object with a `transform` indicating its position in the scene.
     2. Add the probe anchor to the session with the ``ARSession/addAnchor:`` method.

     If you display AR content using ``ARSCNView``, SceneKit automatically retrieves texture maps from probe anchors and uses them to light the
     scene. Otherwise, use a delegate method such as ``ARSessionDelegate/session:didUpdateAnchors:`` to find out when the probe anchor's texture
     has been updated and access the ``AREnvironmentProbeAnchor/environmentTexture`` property.
    */
    AREnvironmentTexturingManual,

    /**
     The framework automatically determines when and where to generate environment textures.

     When you use this environment texturing option, ARKit automatically chooses positions in the scene to generate environment textures based
     on the camera imagery it has collected and the other anchors you've placed.

     If you display AR content using ``ARSCNView``, SceneKit automatically retrieves texture maps from probe anchors and uses them to light the
     scene. Otherwise, use a delegate method such as ``ARSessionDelegate/session:didUpdateAnchors:`` to find out when the probe anchor's texture
     has been updated and access the ``AREnvironmentProbeAnchor/environmentTexture`` property.
    */
    AREnvironmentTexturingAutomatic
} NS_SWIFT_NAME(ARWorldTrackingConfiguration.EnvironmentTexturing);

/**
 Options that enable ARKit to detect the shape of the physical environment.

 When you set one of the these values onto a world-tracking configuration's ``ARWorldTrackingConfiguration/sceneReconstruction`` property,
 ARKit provides you with a mesh that models the real-world surrounding the user.
 */
API_AVAILABLE(ios(13.4))
typedef NS_OPTIONS(NSUInteger, ARSceneReconstruction) {
    /** No scene reconstruction is run. */
    ARSceneReconstructionNone = 0,

    /** A polygonal mesh approximation of the physical environment. */
    ARSceneReconstructionMesh = (1 << 0),

    /** An approximate shape of the physical environment, including classification of the real-world objects within it. */
    ARSceneReconstructionMeshWithClassification = (1 << 1) | (1 << 0)
} NS_SWIFT_NAME(ARConfiguration.SceneReconstruction);

/**
 The base object that contains information about how to configure an augmented reality session.

 ``ARConfiguration`` defines a base class for the different options you can configure in your AR experience.

 All AR configurations establish a correspondence between the real world that the device inhabits and the virtual 3D-coordinate space, where
 you model content. When your app mixes virtual content with a live-camera image, the user experiences the illusion that your virtual content
 is part of the real world.

 To acquire the live-camera imagery, ARKit manages a camera-capture pipeline for you. Depending on the configuration you choose, it determines
 the cameras that capture imagery, and which camera feed the app displays.

 AR apps recognize real-world regions of interest. At runtime, ARKit generates an ``ARAnchor`` for a real-world object it recognizes, which
 allows an app to refer to its details, such as size and physical location. The configuration you choose determines the kinds of real-world
 objects ARKit recognizes and makes available to your app.

 Don't allocate ``ARConfiguration`` yourself; instead, instantiate one of its subclasses.

 For more information about the camera-capture pipeline, see <doc:choosing-which-camera-feed-to-augment>.
 */
API_AVAILABLE(ios(11.0))
@interface ARConfiguration : NSObject <NSCopying>

/**
 A Boolean value indicating whether the current device supports this session configuration class.

 Different types of AR experiences (which you configure using concrete ``ARConfiguration`` subclasses) can have different hardware
 requirements.

 Before attempting to create an AR configuration, verify that the user's device supports the configuration you plan to use by checking the
 ``ARConfiguration/isSupported`` property of the corresponding configuration class. If this property's value is
 <doc://com.apple.documentation/documentation/swift/false>, the current device does not support the requested configuration.

 - Important: All ARKit configurations require an iOS device with an A9 or later processor. If your app otherwise supports other devices and
 offers augmented reality as a secondary feature, use this property to determine whether to offer AR-based features to the user.

   If your app requires ARKit for its core functionality, use the `arkit` key in the
 <doc://com.apple.documentation/documentation/bundleresources/information-property-list/uirequireddevicecapabilities> section of your app's
 Info.plist to make your app available only on devices that support ARKit.
 */
@property (class, nonatomic, readonly) BOOL isSupported;

/**
 The set of video capture formats available on the current device.

 By default, the ``ARConfiguration/videoFormat`` property for a new session configuration matches the first video capture format in this
 array. To change the video format for a session, change that property's value to one of the other ``ARVideoFormat`` objects in this array.

 - Important: ``ARConfiguration`` is an abstract base class, so its implementation of this property always returns an empty array. Read this
 property from the configuration subclass you plan to use for your AR session, such as ``ARWorldTrackingConfiguration`` or
 ``ARFaceTrackingConfiguration``.

 Different devices and iOS versions offer different sets of supported video formats, but the order of this array always puts higher-quality
 formats before lower-quality formats. For best results across all devices and versions, choose formats based on their order in the array
 rather than on hard-coded minimum resolution or frame rate values.
*/
@property (class, nonatomic, readonly) NSArray<ARVideoFormat *> *supportedVideoFormats API_AVAILABLE(ios(11.3));

/**
 Video format of the session output.
 */
@property (nonatomic, strong) ARVideoFormat *videoFormat API_AVAILABLE(ios(11.3));

/**
 A value specifying how the session maps real-world device motion into a 3D scene coordinate system.

 Creating an AR experience depends on being able to construct a coordinate system for placing objects in a virtual 3D world that maps to the
 real-world position and motion of the device. When you run a session configuration, ARKit creates a scene coordinate system based on the
 position and orientation of the device; any ``ARAnchor`` objects you create or that the AR session detects are positioned relative to that
 coordinate system.

 See ``ARWorldAlignment`` for possible values. The default is `ARWorldAlignmentGravity`.
*/
@property (nonatomic, assign) ARWorldAlignment worldAlignment;

/**
 A Boolean value specifying whether ARKit analyzes scene lighting in captured camera images.

 When this value is <doc://com.apple.documentation/documentation/swift/true> (the default), a running AR session provides scene lighting
 information in the ``ARFrame/lightEstimate`` property of each ``ARFrame`` object it captures.

 If you render your own overlay graphics for the AR scene, you can use this information in shading algorithms to help make those graphics match
 the real-world lighting conditions of the scene captured by the camera. (A
 <doc://com.apple.documentation/documentation/realitykit/realityview> or <doc://com.apple.documentation/documentation/realitykit/arview>
 automatically uses this information to configure RealityKit lighting.)
*/
@property (nonatomic, assign, getter=isLightEstimationEnabled) BOOL lightEstimationEnabled;

/**
 A Boolean value that specifies whether to capture audio during the AR session.

 To receive and handle captured audio data, your session delegate must implement the
 ``ARSessionObserver/session:didOutputAudioSampleBuffer:`` method. Disabled by default.
*/
@property (nonatomic, assign) BOOL providesAudioData;

/**
 The set of frame semantics you want ARKit to provide with each frame.

 You can choose whether ARKit reports information about a particular per-frame metric, or _semantic_. Before enabling a frame semantic, call
 ``ARConfiguration/supportsFrameSemantics:`` to ensure device support. An exception is thrown if the option is not supported. Defaults to
 `ARFrameSemanticNone`.

 ### Enable 2D Body Detection

 To get information about the 2D location of a person that ARKit recognizes in a frame, you enable the ``ARFrameSemanticBodyDetection`` frame
 semantic.

 ```swift
 if let config = mySession.configuration as? ARBodyTrackingConfiguration {
     config.frameSemantics.insert(.bodyDetection)
     // Run the configuration to effect a frame semantics change.
     mySession.run(config)
 }
 ```

 ### Enable People Occlusion

 People occlusion is a feature that enables people in the camera feed to cover your app's virtual content.

 To indicate that a person should overlap your app's virtual content when the person is closer to the camera than the virtual content, add the
 ``ARFrameSemanticPersonSegmentationWithDepth`` option to your configuration's frame semantics.

 ```swift
 if let config = mySession.configuration as? ARWorldTrackingConfiguration {
     config.frameSemantics.insert(.personSegmentationWithDepth)
     // Run the configuration to effect a frame semantics change.
     mySession.run(config)
 }
 ```

 To indicate that a person should overlap your app's virtual content regardless of the person's depth in the scene, use the
 ``ARFrameSemanticPersonSegmentation`` frame semantic instead. This option is particularly appropriate for green-screen scenarios.

 Standard renderers (<doc://com.apple.documentation/documentation/realitykit/arview>, and ``ARSCNView``) implement people occlusion for you.
 See <doc:occluding-virtual-content-with-people> for a sample app that demonstrates people occlusion in RealityKit.

 If you implement your own renderer, use ``ARFrame/segmentationBuffer`` and ``ARFrame/estimatedDepthData`` to implement people occlusion
 yourself. ``ARMatteGenerator`` helps you by providing masks. For a sample app that demonstrates matte generator and people occlusion, see
 <doc:effecting-people-occlusion-in-custom-renderers>.

 If you enable Scene Reconstruction, ARKit adjusts the mesh according to any people ARKit may detect in the camera feed. ARKit removes any part
 of the scene mesh that overlaps with people, as defined by the with- or without-depth frame semantics. For more information about scene
 reconstruction, see <doc:visualizing-and-interacting-with-a-reconstructed-scene>.

 - SeeAlso: ``ARFrameSemantics``
 - SeeAlso: ``ARConfiguration/supportsFrameSemantics:``
*/
@property (nonatomic, assign) ARFrameSemantics frameSemantics API_AVAILABLE(ios(13.0));

/**
 Checks whether the device and configuration support a frame semantic.

 Call this function before attempting to enable a frame semantic on your app's configuration. For example, if you call
 `supportsFrameSemantics(.sceneDepth)` on ``ARWorldTrackingConfiguration``, the function returns
 <doc://com.apple.documentation/documentation/swift/true> on devices that support the LiDAR scanner's depth buffer.

 - Parameter frameSemantics: The frame semantics for which to check device support.

 - Returns: A boolean value that indicates whether the device supports the argument frame semantics.

 - Warning: Do not call this function on the superclass, ``ARConfiguration``. Only configuration subclasses support frame semantics.

 - SeeAlso: ``ARFrameSemantics``
*/
+ (BOOL)supportsFrameSemantics:(ARFrameSemantics)frameSemantics API_AVAILABLE(ios(13.0));

/**
 An object that enables you to alter the appearance of a frame's captured image.

 This property provides the underlying capture device for the framework's camera feed. By altering the device's configuration, your app
 indirectly adjusts the visual properties of the each AR frame's ``ARFrame/capturedImage``.

 Alter the device's settings with caution, as extreme changes can affect ARKit's features that rely on the ``ARFrame/capturedImage`` and depend
 on its integrity, such as people occlusion that uses ``ARFrameSemanticPersonSegmentation``.

 - Important: This property is `nil` on devices that aren't equipped with an ultra-wide camera.
*/
@property (class, nonatomic, nullable, readonly) AVCaptureDevice *configurableCaptureDeviceForPrimaryCamera API_AVAILABLE(ios(16.0));

/**
 Provides a 4K video format if the device and configuration support it.

 If the device and configuration support 4K, the returned video format is also present in the configuration's
 ``ARConfiguration/supportedVideoFormats`` array.

 This function returns `nil` if the device or configuration doesn't support 4K, so you can call this function to determine whether to enable 4K
 for your session.
*/
@property (class, nonatomic, nullable, readonly) ARVideoFormat *recommendedVideoFormatFor4KResolution API_AVAILABLE(ios(16.0));

/**
 Returns a video format that the framework recommends for high-resolution-still-image capture.

 The framework determines the resolution of the camera feed and still-image capture for this format. Call this function when your app requires
 a high-resolution still capture regardless of format specifics. If instead, your app requires a particular resolution, iterate over the
 ``ARConfiguration/supportedVideoFormats`` array and choose a format with the desired configuration where
 ``ARVideoFormat/isRecommendedForHighResolutionFrameCapturing`` is `true`.

 Other video formats may support still-image capture but at a lower quality or resolution.

 - SeeAlso: ``ARSession/captureHighResolutionFrameWithCompletion:``
*/
@property (class, nonatomic, nullable, readonly) ARVideoFormat *recommendedVideoFormatForHighResolutionFrameCapturing API_AVAILABLE(ios(16.0));

/**
 Enables high dynamic range (HDR) for the session's camera feed.

 Before calling this function, check whether the session configuration's video format supports HDR first by calling
 ``ARVideoFormat/isVideoHDRSupported``. Defaults to `NO`.
 */
@property (nonatomic, assign, readwrite) BOOL videoHDRAllowed API_AVAILABLE(ios(16.0));

/**
 Unavailable. Use configuration subclasses instead.

 - Returns: This method is unavailable.
*/
- (instancetype)init NS_UNAVAILABLE;

/**
 Unavailable. Use configuration subclasses instead.

 - Returns: This method is unavailable.
*/
+ (instancetype)new NS_UNAVAILABLE;

@end

/**
 A configuration that tracks the position of a device in relation to objects in the environment.

 The ``ARWorldTrackingConfiguration`` class tracks the device's movement with six degrees of freedom (6DOF): the three rotation axes (roll,
 pitch, and yaw), and three translation axes (movement in x, y, and z).

 This kind of tracking can create immersive AR experiences: A virtual object can appear to stay in the same place relative to the real world,
 even as the user tilts the device to look above or below the object, or moves the device around to see the object's sides and back.

 Tracking can no longer be resumed once you pause the session.

 World-tracking sessions also provide several ways for your app to recognize or interact with elements of the real-world scene visible to the
 camera:

 - Find real-world horizontal or vertical surfaces with ``planeDetection``. Add the surfaces to the session as ``ARPlaneAnchor`` objects.
 - Recognize and track the movement of 2D images with ``detectionImages``. Add 2D images to the scene as ``ARImageAnchor`` objects.
 - Recognize 3D objects with ``detectionObjects``. Add 3D objects to the scene as ``ARObjectAnchor`` objects.
 - Find the 3D positions of real-world features that correspond to a touch point on the device's screen with ray casting.
*/
API_AVAILABLE(ios(11.0))
@interface ARWorldTrackingConfiguration : ARConfiguration

/**
 A Boolean value that determines whether the device camera uses fixed focus or autofocus behavior.

 For apps deployed to iOS 11.3 or later, ARKit enables autofocus by default.
*/
@property (nonatomic, assign, getter=isAutoFocusEnabled) BOOL autoFocusEnabled API_AVAILABLE(ios(11.3));

/**
 An option that determines how the framework generates environment textures.

 Environment textures are cube-map textures that depict the view in all directions from a specific point in a scene. In 3D asset rendering,
 environment textures are the basis for image-based lighting algorithms where surfaces can realistically reflect light from their surroundings.
 ARKit generates environment textures during an AR session using camera imagery, allowing SceneKit or a custom-rendering engine to provide
 realistic image-based lighting for virtual objects in your AR experience.

 To enable texture map generation for your configuration, change this property (from its default value of ``AREnvironmentTexturingNone``):

 - With ``AREnvironmentTexturingManual`` environment texturing, you identify points in the scene for which you want light probe texture maps by
 creating ``AREnvironmentProbeAnchor`` objects and adding them to the session.
 - With ``AREnvironmentTexturingAutomatic`` environment texturing, ARKit automatically creates, positions, and adds ``AREnvironmentProbeAnchor``
 objects to the session.

 In both cases, ARKit automatically generates environment textures as the session collects camera imagery. Use a delegate method such as
 ``ARSessionDelegate/session:didUpdateAnchors:`` to find out when a texture is available, and access it from the anchor's
 ``AREnvironmentProbeAnchor/environmentTexture`` property.

 If you display AR content using ``ARSCNView`` and the ``ARSCNView/automaticallyUpdatesLighting`` option, SceneKit automatically retrieves
 ``AREnvironmentProbeAnchor`` texture maps and uses them to light the scene.
*/
@property (nonatomic, assign) AREnvironmentTexturing environmentTexturing API_AVAILABLE(ios(12.0));

/**
 A flag that instructs the framework to create environment textures in HDR format.

 If you set ``environmentTexturing`` to `.automatic` in iOS 12 or later, ARKit gives you environment textures you cast on your app's virtual
 content to create realistic reflections. By default, the framework sets ``wantsHDREnvironmentTextures`` to
 <doc://com.apple.documentation/documentation/swift/true>. When your renderer supports HDR environment textures in iOS 13, it enables your
 lighting engine to output more colors, with a more realistic result.

 Both <doc://com.apple.documentation/documentation/realitykit/arview> and ``ARSCNView`` support HDR environment textures. For more information,
 see <doc:adding-realistic-reflections-to-an-ar-experience>.

 For a Metal app that doesn't yet support HDR environment textures, you can use the following code to receive LDR environment textures until
 you're ready to update your renderer for HDR.

 ```swift
 if #available(iOS 13, *) {
     configuration.wantsHDREnvironmentTextures = false
 }
 ```
 */
@property (nonatomic, assign) BOOL wantsHDREnvironmentTextures API_AVAILABLE(ios(13.0));

/**
 The configuration's plane detection options.

 If set, new planes will continue to be detected and updated over time. Detected planes will be added to the session as ``ARPlaneAnchor``
 objects. In the event that two planes are merged, the newer plane will be removed. Defaults to `ARPlaneDetectionNone`.
*/
@property (nonatomic, assign) ARPlaneDetection planeDetection;

/**
 The state from a previous AR session to attempt to resume with this session configuration.

 An ``ARWorldMap`` encapsulates the state of a running ``ARSession``. This state includes ARKit's awareness of the physical space the user
 moves the device in (which ARKit uses to determine the device's position and orientation), as well as any ``ARAnchor`` objects added to the
 session (which can represent detected real-world features or virtual content placed by your app). After you use
 ``ARSession/getCurrentWorldMap:`` to save a session's world map, you can assign it to a configuration's ``initialWorldMap`` property and use
 ``ARSession/runWithConfiguration:options:`` to start another session with the same spatial awareness and anchors.

 By saving world maps and using them to start new sessions, your app can add new AR capabilities:

 - **Multiuser AR experiences.** Create a shared frame of reference by sending archived ``ARWorldMap`` objects to a nearby user's device. With
 two devices tracking the same world map, you can build a networked experience where both users can see and interact with the same virtual
 content.
 - **Persistent AR experiences.** Save a world map when your app becomes inactive, then restore it the next time your app launches in the same
 physical environment. You can use anchors from the resumed world map to place the same virtual content at the same positions from the saved
 session.

 When you run a session with an initial world map, the session starts in the limited (relocalizing) tracking state while ARKit attempts to
 reconcile the recorded world map with the current environment. If successful, the tracking state becomes normal after a short time, indicating
 that the current world coordinate system and anchors match those from the recorded world map.

 If ARKit cannot reconcile the recorded world map with the current environment (for example, if the device is in an entirely different place
 from where the world map was recorded), the session remains in the relocalizing state indefinitely.
*/
@property (nonatomic, strong, nullable) ARWorldMap *initialWorldMap API_AVAILABLE(ios(12.0));

/**
 A set of images that ARKit searches for in the user's environment.

 Add members to this set for each image that ARKit searches for in the user's environment. When ARKit _detects_ a matching image, the
 framework creates an ``ARImageAnchor`` object and adds it to the session.

 To define the reference images that this property contains, create an asset catalog in Xcode or create ``ARReferenceImage`` objects
 programmatically. For more information, see <doc:detecting-images-in-an-ar-experience>.

 If you set a nonzero value for ``maximumNumberOfTrackedImages``, ARKit enables image _tracking_, which continuously updates the transform for
 up to four of the reference image anchors as the session progresses. For an example, see <doc:tracking-and-altering-images>.

 ### Limit Reference Images for Performance

 Image detection accuracy and performance may decline as the number of images in this set increases. For best results, limit your detection
 image count to no more than around 100.

 To detect more than 100 images, your app can allocate a certain amount of time for the first 100 images before moving on to the next 100, and
 so on. When you update the contents of this property, call ``ARSession/runWithConfiguration:options:`` again with your app's configuration to
 effect the change.
*/
@property (nonatomic, copy, null_resettable) NSSet<ARReferenceImage *> *detectionImages API_AVAILABLE(ios(11.3));

/**
 A flag that instructs the framework to estimate and set the scale of a detected or tracked image on your behalf.

 If set to <doc://com.apple.documentation/documentation/swift/true>, ARKit uses its knowledge of the world to set an image anchor's
 ``ARImageAnchor/estimatedScaleFactor`` property, which corrects the image anchor's position in the physical environment.

 Enable this property when you want to detect different-sized versions of a reference image. ARKit must know the physical size of an image in
 the real world to accurately estimate its real-world position. Enable this property to tell ARKit to estimate a recognized image's physical
 size before it calculates the real-world position.

 - Note: When set to true the transform of a returned `ARImageAnchor` will use the estimated scale factor to correct the translation. Default
 value is `NO`.
*/
@property (nonatomic, assign) BOOL automaticImageScaleEstimationEnabled API_AVAILABLE(ios(13.0));

/**
 The number of image anchors to monitor closely for position and orientation updates.

 When you set a nonzero value for this property, the framework keeps that many image anchors up to date as the session progresses. The
 framework can track a maximum of four images simultaneously.

 The word _track_ in the property name refers to how the framework closely monitors the image's physical position and orientation for any
 changes. If the image moves, the framework updates the associated ``ARImageAnchor`` transform with the new pose. ARKit checks for changes
 every frame.

 ARKit tracks the first images it observes in the physical environment from the ``detectionImages`` set. When a session reaches the maximum
 number of tracked images, the framework attempts to track another member of the set only after one of the existing tracked images leaves the
 device's view.

 The default value is `0`, which disables image tracking. If you add reference images to ``detectionImages`` with this property set to `0`,
 ARKit creates image anchors for observed reference images but their positions only update infrequently, such as once every couple of seconds.
*/
@property (nonatomic, assign) NSInteger maximumNumberOfTrackedImages API_AVAILABLE(ios(12.0));

/**
 A set of 3D objects that the framework attempts to detect in the user's environment.

 The system keeps the object's pose stable in world space, consuming less power. Virtual content stays aligned with the
 object as long as it doesn't move; if the object moves, the system may delay the pose update. When an object is
 detected, an `ARObjectAnchor` is added to the session.

 Use this property for objects that are mostly stationary. For moving or handheld objects that need precise, per-frame
 updates, use `trackingObjects` instead.

 - Note: Supports both the `.arobject` format (introduced in iOS 12) and the `.referenceobject` format (introduced in
 iOS 27). A single session can't use both formats.
*/
@property (nonatomic, copy) NSSet<ARReferenceObject *> *detectionObjects API_AVAILABLE(ios(12.0));

/**
 Objects to track in the scene.

 The system tracks the object at the full frame rate of the selected `videoFormat`. When an object is tracked, an
 `ARObjectAnchor` is added to the session.

 Use this property for moving or handheld objects that require precise, per-frame pose updates. High frame-rate tracking
 significantly increases power consumption and processing load. For mostly stationary objects, use `detectionObjects`
 instead.

 - Note: Only the `.referenceobject` format (introduced in iOS 27) is supported; the older `.arobject` format works only
 with `detectionObjects`. A single session can't use both formats.
*/
@property (nonatomic, copy) NSSet<ARReferenceObject *> *trackingObjects API_AVAILABLE(ios(27.0));

/**
 A flag that opts you in to a peer-to-peer multiuser AR experience.

 The default value of this property is <doc://com.apple.documentation/documentation/swift/false>. When you enable collaboration, ARKit invokes
 ``ARSessionObserver/session:didOutputCollaborationData:`` periodically, providing you with collaboration data to share with peers.
 Collaboration data contains information about the real-world surfaces ARKit detects, your position in relation to them, and any anchors you
 may have created.

 Multiple users sharing collaboration data with each other results in an AR experience in which the users interact by sharing and manipulating
 anchors. By including information that describes a user's unique view of the world, collaboration data enhances ARKit's understanding of the
 layout of the physical environment much more quickly than is possible with only one user.

 For more information, see <doc:creating-a-collaborative-session>.

 - Important: Collaborative sessions work best with up to four participants.

 ### Sharing Collaboration Data Over the Network

 You are responsible for sending collaboration data over the network, including choosing the network framework and implementing the code. See
 <doc:creating-a-multiuser-ar-experience> for an example app that shares a world map among users via
 <doc://com.apple.documentation/documentation/multipeerconnectivity>. Although <doc:creating-a-multiuser-ar-experience> demonstrates sharing
 world data among peer users, it does so using a host-guest model. The primary advantage of collaboration data is that it enables you to share
 world data peer-to-peer.

 The data you send is a serialized version of the ``ARSession/CollaborationData`` object provided by your session. You serialize it using
 <doc://com.apple.documentation/documentation/foundation/nskeyedarchiver>.

 ```swift
 func session(_ session: ARSession, didOutputCollaborationData data: ARSession.CollaborationData) {
     if let collaborationDataEncoded = try? NSKeyedArchiver.archivedData(withRootObject: data, requiringSecureCoding: true) {
         multipeerSession.sendToAllPeers(collaborationDataEncoded)
     } else {
         fatalError("An error occurred while encoding collaboration data.")
     }
 }
 ```

 ### Updating Your Session with Collaboration Data

 When you receive collaboration data from other people, you instantiate an ``ARSession/CollaborationData`` object with it and pass the object
 to your session with ``ARSession/updateWithCollaborationData:``. For optimum performance, it's helpful if the participants in a collaborative
 session are on the same OS version. Unarchiving `ARSession.CollaborationData` received from a device running a different OS version may fail.

 ```swift
 func receivedData(_ data: Data) {
     if let collaborationData = try? NSKeyedUnarchiver.unarchivedObject(ofClass: ARSession.CollaborationData.self, from: data) {
         session.update(with: collaborationData)
     } else {
         print("A device running an incompatible OS version is in the collaborative session.")
     }
 }
 ```
*/
@property (nonatomic, assign, getter=isCollaborationEnabled) BOOL collaborationEnabled API_AVAILABLE(ios(13.0));

/**
 A Boolean value that tells you whether the iOS device supports tracking the user's face during a world-tracking session.

 Check the value of this property first, before you enable face tracking using ``userFaceTrackingEnabled``.
 */
@property (class, nonatomic, readonly) BOOL supportsUserFaceTracking API_AVAILABLE(ios(13.0));

/**
 A flag that determines whether ARKit tracks the user's face in a world-tracking session.

 When enabled, ARKit provides you with an ``ARFaceAnchor`` that represents the user's face during your world tracking session. For example, you
 can share avatar expressions with multiple users in a multiplayer game, or enable the player to control a virtual object in the physical
 environment using facial expressions.

 Check whether the device supports tracking of the user's face by using ``supportsUserFaceTracking`` before enabling this property. Disabled by
 default. The transform of the ``ARFaceAnchor`` objects will be in the world coordinate space.

 - SeeAlso: ``ARFaceAnchor``
*/
@property (nonatomic, assign, getter=userFaceTrackingEnabled) BOOL userFaceTrackingEnabled API_AVAILABLE(ios(13.0));

/**
 A Boolean value that indicates if the framework searches the physical environment for App Clip Codes.

 When this property's value is <doc://com.apple.documentation/documentation/swift/true>, the session delegate receives an
 ``ARAppClipCodeAnchor`` via ``ARSessionDelegate/session:didAddAnchors:`` for every App Clip Code that ARKit detects in the physical
 environment. The default value is <doc://com.apple.documentation/documentation/swift/false>.

 Before calling this function, check that the configuration supports App Clip Code tracking by calling ``supportsAppClipCodeTracking``.

 To avoid scanning a physical code that's not connected to an App Clip, the system ensures that an app provides an App Clip before allowing the
 app to interact with App Clip Codes. Without providing an App Clip, the app can recognize codes in the environment by determining their
 physical location (``ARAnchor/transform``), but code URLs (``ARAppClipCodeAnchor/url``) remain `nil`.
 */
@property (nonatomic, assign) BOOL appClipCodeTrackingEnabled API_AVAILABLE(ios(14.3));

/**
 A flag that indicates if the device tracks App Clip Codes.

 Devices require the Apple Neural Engine (ANE) to track App Clip Codes. The system sets this property to
 <doc://com.apple.documentation/documentation/swift/true> if the device contains the ANE chip. The default value of this property is
 <doc://com.apple.documentation/documentation/swift/false>.

 Call this function before setting ``appClipCodeTrackingEnabled``.
 */
@property (class, nonatomic, readonly) BOOL supportsAppClipCodeTracking API_AVAILABLE(ios(14.3));

/**
 Checks if the device supports scene reconstruction.

 Scene reconstruction requires a device with a LiDAR Scanner, such as the fourth-generation iPad Pro.

 - Parameter sceneReconstruction: The scene reconstruction type to check for support.

 - Returns: `YES` if the scene reconstruction type is supported on this device, `NO` otherwise.
*/
+ (BOOL)supportsSceneReconstruction:(ARSceneReconstruction)sceneReconstruction API_AVAILABLE(ios(13.4));

/**
 A flag that enables scene reconstruction.

 When you enable scene reconstruction, ARKit provides a polygonal mesh that estimates the shape of the physical environment. Before setting
 this property, call ``supportsSceneReconstruction:`` to ensure device support. For a sample app that demonstrates scene reconstruction, see
 <doc:visualizing-and-interacting-with-a-reconstructed-scene>.

 If you enable plane detection, ARKit applies that information to the mesh. Where the LiDAR scanner may produce a slightly uneven mesh on a
 real-world surface, ARKit smooths out the mesh where it detects a plane on that surface.

 If you enable people occlusion, ARKit adjusts the mesh according to any people it detects in the camera feed. ARKit removes any part of the
 scene mesh that overlaps with people, as defined by the ``ARFrameSemanticPersonSegmentation`` or ``ARFrameSemanticPersonSegmentationWithDepth``
 frame semantics.

 If set to a value other than `ARSceneReconstructionNone`, output of scene reconstruction will be added to the session as ``ARMeshAnchor``
 objects. Defaults to `ARSceneReconstructionNone`.

 - SeeAlso: ``ARMeshAnchor``
*/
@property (nonatomic, assign) ARSceneReconstruction sceneReconstruction API_AVAILABLE(ios(13.4));

/**
 Initializes a new world-tracking configuration.

 To use the configuration in an AR experience, pass it as an argument to your app's ``ARSession/runWithConfiguration:options:`` function.
*/
- (instancetype)init;

/**
 Creates a new world-tracking configuration.

 To use the configuration in an AR experience, pass it as an argument to your app's ``ARSession/runWithConfiguration:options:`` function.
*/
+ (instancetype)new NS_SWIFT_UNAVAILABLE("Use init() instead");

@end

/**
 A configuration that tracks only the device's orientation using the rear-facing camera.

 All AR configurations establish a correspondence between the real world the device inhabits and a virtual 3D coordinate space where you can
 model content. When your app displays that content together with a live camera image, the user experiences the illusion that your virtual
 content is part of the real world.

 Creating and maintaining this correspondence between spaces requires tracking the device's motion. The ``AROrientationTrackingConfiguration``
 class tracks the device's movement with three degrees of freedom (3DOF): specifically, the three rotation axes (roll, pitch, and yaw).

 This basic level of motion tracking can create limited AR experiences: A virtual object can appear to be part of the real world, even as the
 user rotates the device to look above, below, or beside that object. However, this configuration cannot track movement of the device:
 non-trivially changing the device's position breaks the AR illusion, causing virtual content to appear to drift relative to the real world.
 For example, the user cannot walk around to see the sides and back of a virtual object. Additionally, 3DOF tracking does not support plane
 detection or hit testing.

 - Important: Because 3DOF tracking creates limited AR experiences, you should generally not use the ``AROrientationTrackingConfiguration``
 class directly. Instead, use ``ARWorldTrackingConfiguration`` for six degrees of freedom (6DOF) plane detection and hit testing. Use 3DOF
 tracking only as a fallback in situations where 6DOF tracking is temporarily unavailable.
*/
API_AVAILABLE(ios(11.0))
@interface AROrientationTrackingConfiguration : ARConfiguration

/**
 A Boolean value that determines whether the device camera uses fixed focus or autofocus behavior.

 In apps linked against the iOS 11.3 SDK or later, ARKit enables autofocus by default.
*/
@property (nonatomic, assign, getter=isAutoFocusEnabled) BOOL autoFocusEnabled API_AVAILABLE(ios(11.3));

/**
 Initializes a new orientation tracking configuration.

 To use the configuration in an AR session, pass it to the ``ARSession`` ``ARSession/runWithConfiguration:options:`` method.
*/
- (instancetype)init;

/**
 Creates a new orientation tracking configuration.

 To use the configuration in an AR session, pass it to the ``ARSession`` ``ARSession/runWithConfiguration:options:`` method.
*/
+ (instancetype)new NS_SWIFT_UNAVAILABLE("Use init() instead");

@end

/**
 A configuration that tracks facial movement and expressions using the front camera.

 A face-tracking configuration detects faces within 3 meters of the device's front camera. When ARKit detects a face, it creates an
 ``ARFaceAnchor`` object that provides information about a person's facial position, orientation, topology, and expressions.

 Face tracking supports devices with Apple Neural Engine in iOS 14 and iPadOS 14 and requires a device with a TrueDepth camera on iOS 13 and
 iPadOS 13 and earlier. To determine whether the device supports face tracking, call ``ARConfiguration/isSupported`` on
 ``ARFaceTrackingConfiguration`` before attempting to use this configuration.

 When you enable the ``ARConfiguration/isLightEstimationEnabled`` setting, a face-tracking configuration estimates directional and
 environmental lighting (an ``ARDirectionalLightEstimate`` object) by referring to the detected face as a light probe.

 - Note: Because face tracking provides your app with personal facial information, your app must include a privacy policy describing to users
 how you intend to use face tracking and face data. For details, see the
 [Apple Developer Program License Agreement](https://developer.apple.com/terms/).
*/
API_AVAILABLE(ios(11.0))
@interface ARFaceTrackingConfiguration : ARConfiguration

/**
 The maximum number of faces that the framework can track.

 Do not exceed this value when you set ``maximumNumberOfTrackedFaces``.
 */
@property (class, nonatomic, readonly) NSInteger supportedNumberOfTrackedFaces API_AVAILABLE(ios(13.0));

/**
 The number of faces to track during the session.

 The default value is one. Set the maximum number of tracked faces to limit the number of faces that can be tracked in a given frame. Check
 the value of ``supportedNumberOfTrackedFaces`` before setting this property.

 No new anchors will be provided to your delegate's ``ARSessionDelegate/session:didAddAnchors:`` if more than the maximum number of faces are
 visible in the camera feed. In that case, ARKit continues to track the faces that already have associated face anchors.
*/
@property (nonatomic, assign) NSInteger maximumNumberOfTrackedFaces API_AVAILABLE(ios(13.0));

/**
 A Boolean value that indicates whether the iOS device supports tracking the world in a face-tracking session.

 Check this property before attempting to enable world tracking in a face tracking configuration using ``isWorldTrackingEnabled``.
 */
@property (class, nonatomic, readonly) BOOL supportsWorldTracking API_AVAILABLE(ios(13.0));

/**
 A Boolean value that instructs a session to provide the app with the device's six degrees of freedom pose during a face-tracking session.

 Before attempting to enable this property, check whether the iOS device supports user-face tracking in a world-tracking session, by calling
 ``supportsWorldTracking``. Disabled by default. When enabled, `ARSession` uses the back facing camera to track the device's orientation and
 position in the world. The camera transform and the ``ARFaceAnchor`` transform will be in the world coordinate space.
*/
@property (nonatomic, assign, getter=isWorldTrackingEnabled) BOOL worldTrackingEnabled API_AVAILABLE(ios(13.0));

/**
 Enable or disable environment texturing.

 When enabled, the system automatically generates and updates the environment texture at the device position. Disabled by default.
*/
@property (nonatomic, assign, getter=isEnvironmentTexturingEnabled) BOOL environmentTexturingEnabled API_AVAILABLE(ios(27.0));

/**
 Creates a new face-tracking configuration.

 To use the configuration in an AR session, pass it to the ``ARSession`` ``ARSession/runWithConfiguration:options:`` method.
*/
- (instancetype)init;

/**
 Allocates and initializes a new face-tracking configuration.

 To use the configuration in an AR session, pass it to the ``ARSession`` ``ARSession/runWithConfiguration:options:`` method.
*/
+ (instancetype)new NS_SWIFT_UNAVAILABLE("Use init() instead");

@end

/**
 A configuration that tracks known images using the rear-facing camera.

 All AR configurations establish a correspondence between the real world the device inhabits and a virtual 3D coordinate space where you can
 model content. When your app displays that content together with a live camera image, the user experiences the illusion that your virtual
 content is part of the real world.

 With ``ARImageTrackingConfiguration``, ARKit establishes a 3D space not by tracking the motion of the device relative to the world, but solely
 by detecting and tracking the motion of known 2D images in view of the camera. ``ARWorldTrackingConfiguration`` can also detect images, but
 each configuration has its own strengths:

 - World tracking has a higher performance cost than image-only tracking, so your session can reliably track more images at once with
 ``ARImageTrackingConfiguration``.
 - Image-only tracking lets you anchor virtual content to known images only when those images are in view of the camera. World tracking with
 image detection lets you use known images to add virtual content to the 3D world, and continues to track the position of that content in
 world space even after the image is no longer in view.
 - World tracking works best in a stable, nonmoving environment. You can use image-only tracking to add virtual content to known images in more
 situations—for example, an advertisement inside a moving subway car.

 When an image-tracking configuration detects known images, it tracks their movement with six degrees of freedom (6DOF): specifically, the
 three rotation axes (roll, pitch, and yaw), and three translation axes (movement in x, y, and z).

 To use ``ARImageTrackingConfiguration``, define ``ARReferenceImage`` objects (either at runtime or by bundling them in your Xcode asset
 catalog) and assign them to the configuration's ``trackingImages`` property. Then, as with any AR configuration, pass the configuration to
 your session's ``ARSession/runWithConfiguration:options:`` method.
*/
API_AVAILABLE(ios(12.0))
@interface ARImageTrackingConfiguration : ARConfiguration

/**
 A Boolean value that determines whether the device camera uses fixed focus or autofocus behavior.

 Autofocus is enabled by default.
*/
@property (nonatomic, assign, getter=isAutoFocusEnabled) BOOL autoFocusEnabled;

/**
 A set of images that ARKit searches for and tracks in the user's environment.

 Add members to this set for each image that ARKit searches for in the user's environment. When ARKit observes a matching image, the framework
 creates an ``ARImageAnchor`` object and adds it to the session. If you set ``maximumNumberOfTrackedImages`` to a value greater than `1`, ARKit
 tracks multiple images as the session progresses, up to a maximum of four.

 To define the reference images that this property contains, create an asset catalog in Xcode or create ``ARReferenceImage`` objects
 programmatically. For an example, see <doc:tracking-and-altering-images>.
*/
@property (nonatomic, copy) NSSet<ARReferenceImage *> *trackingImages;

/**
 The number of image anchors to monitor closely for position and orientation updates.

 When you set a nonzero value for this property, the framework keeps that many image anchors up to date as the session progresses. The
 framework can track a maximum of four images simultaneously.

 The word _track_ in the property name refers to how the framework closely monitors the image's physical position and orientation for any
 changes. If the image moves, the framework updates the associated ``ARImageAnchor`` transform with the new pose. ARKit checks for changes
 every frame.

 ARKit tracks the first images it observes in the physical environment from the ``trackingImages`` set. When a session reaches the maximum
 number of tracked images, the framework attempts to track another member of the set only after one of the existing tracked images leaves the
 device's view.

 The default value is `1`.
*/
@property (nonatomic, assign) NSInteger maximumNumberOfTrackedImages;

/**
 Initializes a new image-tracking configuration.

 To use the configuration in an AR session, pass it to the ``ARSession`` ``ARSession/runWithConfiguration:options:`` method.
*/
- (instancetype)init;

/**
 Creates a new image-tracking configuration.

 To use the configuration in an AR session, pass it to the ``ARSession`` ``ARSession/runWithConfiguration:options:`` method.
*/
+ (instancetype)new NS_SWIFT_UNAVAILABLE("Use init() instead");

@end

/**
 A configuration that recognizes objects and collects high-fidelity data about specific objects using the rear-facing camera.

 To create an app that recognizes objects in the physical environment, first you scan them during development using
 `ARObjectScanningConfiguration`. After you've scanned an object, call
 ``ARSession/createReferenceObjectWithTransform:center:extent:completionHandler:`` to turn it into an ``ARReferenceObject`` that you can use to detect
 it again at run-time. When users run your app, you ask ARKit to look for your scanned objects by running a world tracking configuration and assigning
 reference objects to its
 ``ARWorldTrackingConfiguration/detectionObjects`` property.

 - Important: `ARObjectScanningConfiguration` is for use only in development scenarios. Because the high-fidelity spatial mapping required by
 object scanning has a high performance and energy cost, many ARKit features are disabled that aren't required for object scanning.
*/
API_DEPRECATED("Please consider migrating to the new reference object format.", ios(12.0, 27.0));
@interface ARObjectScanningConfiguration : ARConfiguration

/**
 A Boolean value that determines whether the device camera uses fixed focus or autofocus behavior.

 Autofocus is enabled by default.
*/
@property (nonatomic, assign, getter=isAutoFocusEnabled) BOOL autoFocusEnabled;

/**
 A value specifying whether and how the session attempts to automatically detect flat surfaces in the camera-captured image.

 By default, plane detection is off. If you enable ``ARPlaneDetectionHorizontal`` or ``ARPlaneDetectionVertical`` plane detection, the session
 adds ``ARPlaneAnchor`` objects and notifies your ``ARSessionDelegate``, ``ARSCNViewDelegate``, or ``ARSKViewDelegate`` object whenever its
 analysis of captured video images detects an area that appears to be a flat surface.

 In an object-scanning session, you can use detected planes to help determine where the origin (anchor point) for a scanned object should be
 relative to its extent.
*/
@property (nonatomic, assign) ARPlaneDetection planeDetection;

/**
 Initializes a new object scanning configuration.

 To use the configuration in an AR session, pass it to the ``ARSession`` ``ARSession/runWithConfiguration:options:`` method.
*/
- (instancetype)init;

/**
 Creates a new object scanning configuration.

 To use the configuration in an AR session, pass it to the ``ARSession`` ``ARSession/runWithConfiguration:options:`` method.
*/
+ (instancetype)new NS_SWIFT_UNAVAILABLE("Use init() instead");

@end

/**
 A configuration that tracks human body poses, planar surfaces, and images using the rear-facing camera.

 When ARKit identifies a person in the rear camera's feed, it calls ``ARSessionDelegate/session:didAddAnchors:``, passing an ``ARBodyAnchor``
 you can use to track the body's movement.

 When you enable plane detection and image detection, you can use a body anchor to display a virtual character and set the character on a
 surface or image that you choose.

 By default, ``ARConfiguration/frameSemantics`` includes ``ARFrameSemanticBodyDetection``, which gives you access to the joint positions of a
 person that ARKit detects in the camera feed via the frame's ``ARFrame/detectedBody``.

 - SeeAlso: ``ARBodyAnchor``
 - SeeAlso: ``ARFrame/detectedBody``
*/
API_AVAILABLE(ios(13.0))
@interface ARBodyTrackingConfiguration : ARConfiguration

/**
 A Boolean value that determines whether the device camera uses fixed focus or autofocus behavior.

 For apps deployed to iOS 11.3 or later, ARKit enables autofocus by default.
*/
@property (nonatomic, assign, getter=isAutoFocusEnabled) BOOL autoFocusEnabled;

/**
 The state from a previous AR session to attempt to resume with this session configuration.

 An ``ARWorldMap`` encapsulates the state of a running ``ARSession``. This state includes ARKit's awareness of the physical space the user
 moves the device in (which ARKit uses to determine the device's position and orientation), as well as any ``ARAnchor`` objects added to the
 session (which can represent detected real-world features or virtual content placed by your app). After you use
 ``ARSession/getCurrentWorldMap:`` to save a session's world map, you can assign it to a configuration's ``initialWorldMap`` property and use
 ``ARSession/runWithConfiguration:options:`` to start another session with the same spatial awareness and anchors.

 By saving world maps and using them to start new sessions, your app can add new AR capabilities:

 - **Multiuser AR experiences.** Create a shared frame of reference by sending archived ``ARWorldMap`` objects to a nearby user's device. With
 two devices tracking the same world map, you can build a networked experience where both users can see and interact with the same virtual
 content.
 - **Persistent AR experiences.** Save a world map when your app becomes inactive, then restore it the next time your app launches in the same
 physical environment. You can use anchors from the resumed world map to place the same virtual content at the same positions from the saved
 session.

 When you run a session with an initial world map, the session starts in the limited (relocalizing) tracking state while ARKit attempts to
 reconcile the recorded world map with the current environment. If successful, the tracking state becomes normal after a short time, indicating
 that the current world coordinate system and anchors match those from the recorded world map.

 If ARKit cannot reconcile the recorded world map with the current environment (for example, if the device is in an entirely different place
 from where the world map was recorded), the session remains in the relocalizing state indefinitely.
*/
@property (nonatomic, strong, nullable) ARWorldMap *initialWorldMap;

/**
 The behavior ARKit uses for generating environment textures.

 Environment textures are cube-map textures that depict the view in all directions from a specific point in a scene. In 3D asset rendering,
 environment textures are the basis for image-based lighting algorithms where surfaces can realistically reflect light from their surroundings.
 ARKit can generate environment textures during an AR session using camera imagery, allowing SceneKit or a custom rendering engine to provide
 realistic image-based lighting for virtual objects in your AR experience.

 To enable texture map generation for your configuration, change this property (from its default value of ``AREnvironmentTexturingNone``):

 - With ``AREnvironmentTexturingManual`` environment texturing, you identify points in the scene for which you want light probe texture maps by
 creating ``AREnvironmentProbeAnchor`` objects and adding them to the session.
 - With ``AREnvironmentTexturingAutomatic`` environment texturing, ARKit automatically creates, positions, and adds ``AREnvironmentProbeAnchor``
 objects to the session.

 In both cases, ARKit automatically generates environment textures as the session collects camera imagery. Use a delegate method such as
 ``ARSessionDelegate/session:didUpdateAnchors:`` to find out when a texture is available, and access it from the anchor's
 ``AREnvironmentProbeAnchor/environmentTexture`` property.

 If you display AR content using ``ARSCNView`` and the ``ARSCNView/automaticallyUpdatesLighting`` option, SceneKit automatically retrieves
 ``AREnvironmentProbeAnchor`` texture maps and uses them to light the scene.
*/
@property (nonatomic, assign) AREnvironmentTexturing environmentTexturing;

/**
 A flag that instructs ARKit to create environment textures in HDR format.

 The default value is <doc://com.apple.documentation/documentation/swift/true>. If your renderer supports HDR environment textures, this
 feature effects more realistic reflections.

 RealityKit and SceneKit both support HDR environment textures. For more information, see
 <doc:adding-realistic-reflections-to-an-ar-experience>.
 */
@property (nonatomic, assign) BOOL wantsHDREnvironmentTextures;

/**
 A value specifying whether and how the session attempts to automatically detect flat surfaces in the camera-captured image.

 By default, plane detection is off. If you enable ``ARPlaneDetectionHorizontal`` or ``ARPlaneDetectionVertical`` plane detection, the session
 adds ``ARPlaneAnchor`` objects and notifies your ``ARSessionDelegate``, ``ARSCNViewDelegate``, or ``ARSKViewDelegate`` object whenever its
 analysis of captured video images detects an area that appears to be a flat surface.
*/
@property (nonatomic, assign) ARPlaneDetection planeDetection;

/**
 A set of images that ARKit searches for in the user's environment.

 Add members to this set for each image that ARKit searches for in the user's environment. When ARKit _detects_ a matching image, the
 framework creates an ``ARImageAnchor`` object and adds it to the session.

 To define the reference images that this property contains, create an asset catalog in Xcode or create ``ARReferenceImage`` objects
 programmatically. For more information, see <doc:detecting-images-in-an-ar-experience>.

 If you set a nonzero value for ``maximumNumberOfTrackedImages``, ARKit enables image _tracking_, which continuously updates the transform for
 up to four of the reference image anchors as the session progresses. For an example, see <doc:tracking-and-altering-images>.

 ### Limit Reference Images for Performance

 Image detection accuracy and performance may decline as the number of images in this set increases. For best results, limit your detection
 image count to no more than around 100.

 To detect more than 100 images, your app can allocate a certain amount of time for the first 100 images before moving on to the next 100, and
 so on. When you update the contents of this property, call ``ARSession/runWithConfiguration:options:`` again with your app's configuration to
 effect the change.
*/
@property (nonatomic, copy) NSSet<ARReferenceImage *> *detectionImages;

/**
 A flag that instructs ARKit to estimate and set the scale of a tracked image on your behalf.

 If set to <doc://com.apple.documentation/documentation/swift/true>, ARKit uses its knowledge of the world to set an image anchor's
 ``ARImageAnchor/estimatedScaleFactor`` property, which corrects the image anchor's position in the physical environment.

 Enable this property when you want to detect different sized versions of a reference image. ARKit must know the physical size of an image in
 the real world to accurately estimate its real-world position. You enable this property to tell ARKit to estimate a recognized image's
 physical size before it calculates the real-world position.

 - Note: When set to true the transform of a returned `ARImageAnchor` will use the estimated scale factor to correct the translation. Default
 value is `NO`.
*/
@property (nonatomic, assign) BOOL automaticImageScaleEstimationEnabled;

/**
 A flag that determines whether ARKit estimates the height of a body that it's tracking.

 When you assign this property a value of <doc://com.apple.documentation/documentation/swift/true>, you instruct ARKit to compute a value for
 ``ARBodyAnchor/estimatedScaleFactor`` for a person's body anchor. ARKit must know the physical height of a person in the real world to
 accurately estimate the person's real-world position. You enable this property to tell ARKit to estimate a recognized person's physical height
 before it assigns the body anchor's position.

 - Note: When set to true the transform of a returned `ARBodyAnchor` will use the estimated scale factor to correct the translation. Default
 value is `NO`.
*/
@property (nonatomic, assign) BOOL automaticSkeletonScaleEstimationEnabled;
/**
 The number of image anchors to monitor closely for position and orientation updates.

 When you set a nonzero value for this property, the framework keeps that many image anchors up to date as the session progresses. The
 framework can track a maximum of four images simultaneously.

 The word _track_ in the property name refers to how the framework closely monitors the image's physical position and orientation for any
 changes. If the image moves, the framework updates the associated ``ARImageAnchor`` transform with the new pose. ARKit checks for changes
 every frame.

 ARKit tracks the first images it observes in the physical environment from the ``detectionImages`` set. When a session reaches the maximum
 number of tracked images, the framework attempts to track another member of the set only after one of the existing tracked images leaves the
 device's view.

 The default value is `0`, which disables image tracking. If you add reference images to ``detectionImages`` with this property set to `0`,
 ARKit creates image anchors for observed reference images but their positions only update infrequently, such as once every couple of seconds.
*/
@property (nonatomic, assign) NSInteger maximumNumberOfTrackedImages;

/**
 A Boolean value that indicates if the framework searches the physical environment for App Clip Codes.

 When this property's value is <doc://com.apple.documentation/documentation/swift/true>, the session delegate receives an
 ``ARAppClipCodeAnchor`` via ``ARSessionDelegate/session:didAddAnchors:`` for every App Clip Code that ARKit detects in the physical
 environment. The default value is `false`.

 Before calling this function, check that the configuration supports App Clip Code tracking by calling ``supportsAppClipCodeTracking``.

 To avoid scanning a physical code that's not connected to an App Clip, the system ensures that an app provides an App Clip before allowing the
 app to interact with App Clip Codes. Without providing an App Clip, the app can recognize codes in the environment by determining their
 physical location (``ARAnchor/transform``), but code URLs (``ARAppClipCodeAnchor/url``) remain `nil`.
 */
@property (nonatomic, assign) BOOL appClipCodeTrackingEnabled API_AVAILABLE(ios(14.3));

/**
 A flag that indicates if the device tracks App Clip Codes.

 Devices require the Apple Neural Engine (ANE) to track App Clip Codes. The system sets this property to
 <doc://com.apple.documentation/documentation/swift/true> if the device contains the ANE chip. The default value of this property is
 <doc://com.apple.documentation/documentation/swift/false>.

 Call this function before setting ``appClipCodeTrackingEnabled``.
 */
@property (class, nonatomic, readonly) BOOL supportsAppClipCodeTracking API_AVAILABLE(ios(14.3));

/**
 Creates a new body tracking configuration.
*/
- (instancetype)init;

/**
 Creates a new body tracking configuration.
*/
+ (instancetype)new NS_SWIFT_UNAVAILABLE("Use init() instead");

@end

/**
 A configuration that tracks only the device's position in 3D space.

 Enables 6 degrees of freedom tracking of the iOS device by running the camera at lowest possible resolution and frame rate. Use this
 configuration when you don't need to parse the camera feed, such as for example, virtual reality scenarios.
*/
API_AVAILABLE(ios(13.0))
@interface ARPositionalTrackingConfiguration : ARConfiguration

/**
 A value that specifies if and how the session automatically attempts to detect flat surfaces in the camera-captured image.

 By default, this configuration disables plane detection. If you enable ``ARPlaneDetectionHorizontal`` or ``ARPlaneDetectionVertical`` plane
 detection, the session adds ``ARPlaneAnchor`` objects and notifies your ``ARSessionDelegate``, ``ARSCNViewDelegate``, or ``ARSKViewDelegate``
 object when its analysis of captured video images detects an area that appears to be a flat surface.
*/
@property (nonatomic, assign) ARPlaneDetection planeDetection;

/**
 The state from a previous AR session to attempt to resume with this session configuration.

 An ``ARWorldMap`` encapsulates the state of a running ``ARSession``. This state includes ARKit's awareness of the physical space the user
 moves the device in (which ARKit uses to determine the device's position and orientation), as well as any ``ARAnchor`` objects added to the
 session (which can represent detected real-world features or virtual content placed by your app). After you use
 ``ARSession/getCurrentWorldMap:`` to save a session's world map, you can assign it to a configuration's ``initialWorldMap`` property and use
 ``ARSession/runWithConfiguration:options:`` to start another session with the same spatial awareness and anchors.

 By saving world maps and using them to start new sessions, your app can add new AR capabilities:

 - **Multiuser AR experiences.** Create a shared frame of reference by sending archived ``ARWorldMap`` objects to a nearby user's device. With
 two devices tracking the same world map, you can build a networked experience where both users can see and interact with the same virtual
 content.
 - **Persistent AR experiences.** Save a world map when your app becomes inactive, then restore it the next time your app launches in the same
 physical environment. You can use anchors from the resumed world map to place the same virtual content at the same positions from the saved
 session.

 When you run a session with an initial world map, the session starts in the limited (relocalizing) tracking state while ARKit attempts to
 reconcile the recorded world map with the current environment. If successful, the tracking state becomes normal after a short time, indicating
 that the current world coordinate system and anchors match those from the recorded world map.

 If ARKit cannot reconcile the recorded world map with the current environment (for example, if the device is in an entirely different place
 from where the world map was recorded), the session remains in the relocalizing state indefinitely.
*/
@property (nonatomic, strong, nullable) ARWorldMap *initialWorldMap;

/**
 Creates a new positional tracking configuration.
*/
- (instancetype)init;

/**
 Creates a new positional tracking configuration.
*/
+ (instancetype)new NS_SWIFT_UNAVAILABLE("Use init() instead");

@end

/**
 A configuration that tracks locations with GPS, map data, and a device's compass.

 This configuration creates location anchors (``ARGeoAnchor``) that specify a particular latitude, longitude, and optionally, altitude to
 enable an app to track geographic areas of interest in an AR experience.

 - Important: The ``ARConfiguration/isSupported`` property returns <doc://com.apple.documentation/documentation/swift/true> for this class on
 iOS 14 & iPadOS 14 devices that have an A12 chip or later and cellular (GPS) capability. Geotracking is available in specific geographic
 locations. To determine availability at the user's location at runtime, call ``checkAvailabilityWithCompletionHandler:``.

 Geotracking occurs exclusively outdoors. If a geotracking app navigates users between waypoints, your app needs to handle any events along a
 route. The user must have an internet connection, and you can provide them information about data usage, as described in ``ARGeoAnchor``.

 ### Encourage user safety

 To keep your users' focus on the road while traveling, discourage them from looking at the device when in motion, such as while riding a bike.
 Keep users informed when navigating through unfamiliar territory. For instance, you can recommend they steer clear of private property, or
 remind them to check their device's battery level before beginning a long route.

 ### Refine the user's position with imagery

 To place location anchors with precision, geotracking requires a better understanding of the user's geographic location than is possible with
 GPS alone. Based on the user's GPS coordinates, ARKit downloads imagery that depicts the physical environment in that area. Apple collects
 this _localization imagery_ in advance by capturing photos of the view from the street and recording the geographic position at each photo. By
 comparing the device's current camera image with this imagery, the session matches the user's precise geographic location with the scene's
 local coordinates. For information about the user's position in local space, see ``ARCamera/transform``.

 Localization imagery captures views from public streets and routes accessible by car, but doesn't include images of gated or pedestrian-only
 areas.

 Geotracking sessions use localization imagery in the ``ARGeoTrackingStatus/State/localizing`` state.

 ### Supported areas and cities

 Localization imagery is available for specific areas in over 20 countries, including many metropolitan areas in Australia, Europe, Japan, and
 North America. To check availability in a particular location, see the ``checkAvailabilityWithCompletionHandler:`` function.

 - Tip: You can share an experience of geotracking with developers who live outside an area that supports it. Record a session in your app in
 an area that supports localization imagery for developers to create and test their geotracking app. For more information, see
 <doc:recording-and-replaying-ar-session-data>.
*/
API_AVAILABLE(ios(14.0))
@interface ARGeoTrackingConfiguration : ARConfiguration

/** Unavailable */
@property (nonatomic, assign) ARWorldAlignment worldAlignment NS_UNAVAILABLE;

/**
 An option that determines how the framework generates environment textures.

 Environment textures are cube-map textures that depict the view in all directions from a specific point in a scene. In 3D asset rendering,
 environment textures are the basis for image-based lighting algorithms where surfaces can realistically reflect light from their surroundings.
 ARKit generates environment textures during an AR session using camera imagery, allowing SceneKit or a custom-rendering engine to provide
 realistic image-based lighting for virtual objects in your AR experience.

 To enable texture map generation for your configuration, change this property (from its default value of ``AREnvironmentTexturingNone``):

 - With ``AREnvironmentTexturingManual`` environment texturing, you identify points in the scene for which you want light probe texture maps by
 creating ``AREnvironmentProbeAnchor`` objects and adding them to the session.
 - With ``AREnvironmentTexturingAutomatic`` environment texturing, ARKit automatically creates, positions, and adds ``AREnvironmentProbeAnchor``
 objects to the session.

 In both cases, ARKit automatically generates environment textures as the session collects camera imagery. Use a delegate method such as
 ``ARSessionDelegate/session:didUpdateAnchors:`` to find out when a texture is available, and access it from the anchor's
 ``AREnvironmentProbeAnchor/environmentTexture`` property.

 If you display AR content using ``ARSCNView`` and the ``ARSCNView/automaticallyUpdatesLighting`` option, SceneKit automatically retrieves
 ``AREnvironmentProbeAnchor`` texture maps and uses them to light the scene.
*/
@property (nonatomic, assign) AREnvironmentTexturing environmentTexturing;

/**
 A flag that instructs the framework to create environment textures in HDR format.

 If you set ``environmentTexturing`` to `.automatic` in iOS 12 or later, ARKit gives you environment textures you cast on your app's virtual
 content to create realistic reflections. By default, the framework sets ``wantsHDREnvironmentTextures`` to
 <doc://com.apple.documentation/documentation/swift/true>. When your renderer supports HDR environment textures in iOS 13, it enables your
 lighting engine to output more colors, with a more realistic result.

 Both <doc://com.apple.documentation/documentation/realitykit/arview> and ``ARSCNView`` support HDR environment textures. For more information,
 see <doc:adding-realistic-reflections-to-an-ar-experience>.

 For a Metal app that doesn't yet support HDR environment textures, you can use the following code to receive LDR environment textures until
 you're ready to update your renderer for HDR.

 ```swift
 if #available(iOS 13, *) {
     configuration.wantsHDREnvironmentTextures = false
 }
 ```
 */
@property (nonatomic, assign) BOOL wantsHDREnvironmentTextures;

/**
 A value that specifies whether and how the session automatically attempts to detect flat surfaces in the camera-captured image.

 By default, this configuration disables plane detection. If you enable ``ARPlaneDetectionHorizontal`` or ``ARPlaneDetectionVertical`` plane
 detection, the session adds ``ARPlaneAnchor`` objects and notifies your ``ARSessionDelegate``, ``ARSCNViewDelegate``, or ``ARSKViewDelegate``
 object when its analysis of captured video images detects an area that appears to be a flat surface.
*/
@property (nonatomic, assign) ARPlaneDetection planeDetection;

/**
 A set of images that ARKit searches for in the user's environment.

 Add members to this set for each image that ARKit searches for in the user's environment. When ARKit _detects_ a matching image, the
 framework creates an ``ARImageAnchor`` object and adds it to the session.

 To define the reference images that this property contains, create an asset catalog in Xcode or create ``ARReferenceImage`` objects
 programmatically. For more information, see <doc:detecting-images-in-an-ar-experience>.

 If you set a nonzero value for ``maximumNumberOfTrackedImages``, ARKit enables image _tracking_, which continuously updates the transform for
 up to four of the reference image anchors as the session progresses. For an example, see <doc:tracking-and-altering-images>.

 ### Limit Reference Images for Performance

 Image detection accuracy and performance may decline as the number of images in this set increases. For best results, limit your detection
 image count to no more than around 100.

 To detect more than 100 images, your app can allocate a certain amount of time for the first 100 images before moving on to the next 100, and
 so on. When you update the contents of this property, call ``ARSession/runWithConfiguration:options:`` again with your app's configuration to
 effect the change.
*/
@property (nonatomic, copy, null_resettable) NSSet<ARReferenceImage *> *detectionImages;

/**
 A flag that instructs the framework to estimate and set the scale of a detected or tracked image on your behalf.

 If set to <doc://com.apple.documentation/documentation/swift/true>, ARKit uses its knowledge of the world to set an image anchor's
 ``ARImageAnchor/estimatedScaleFactor`` property, which corrects the image anchor's position in the physical environment.

 Enable this property when you want to detect different-sized versions of a reference image. ARKit must know the physical size of an image in
 the real world to accurately estimate its real-world position. Enable this property to tell ARKit to estimate a recognized image's physical
 size before it calculates the real-world position.

 - Note: When set to true the transform of a returned `ARImageAnchor` will use the estimated scale factor to correct the translation. Default
 value is `NO`.
*/
@property (nonatomic, assign) BOOL automaticImageScaleEstimationEnabled;

/**
 The number of image anchors to monitor closely for position and orientation updates.

 When you set a nonzero value for this property, the framework keeps that many image anchors up to date as the session progresses. The
 framework can track a maximum of four images simultaneously.

 The word _track_ in the property name refers to how the framework closely monitors the image's physical position and orientation for any
 changes. If the image moves, the framework updates the associated ``ARImageAnchor`` transform with the new pose. ARKit checks for changes
 every frame.

 ARKit tracks the first images it observes in the physical environment from the ``detectionImages`` set. When a session reaches the maximum
 number of tracked images, the framework attempts to track another member of the set only after one of the existing tracked images leaves the
 device's view.

 The default value is `0`, which disables image tracking. If you add reference images to ``detectionImages`` with this property set to `0`,
 ARKit creates image anchors for observed reference images but their positions only update infrequently, such as once every couple of seconds.
*/
@property (nonatomic, assign) NSInteger maximumNumberOfTrackedImages;

/**
 A set of 3D objects that the framework attempts to detect in the user's environment.

 The system keeps the object's pose stable in world space, consuming less power. Virtual content stays aligned with the
 object as long as it doesn't move; if the object moves, the system may delay the pose update. When an object is
 detected, an `ARObjectAnchor` is added to the session.

 Use this property for objects that are mostly stationary. For moving or handheld objects that need precise, per-frame
 updates, use `trackingObjects` instead.

 - Note: Supports both the `.arobject` format (introduced in iOS 12) and the `.referenceobject` format (introduced in
 iOS 27). A single session can't use both formats.
*/
@property (nonatomic, copy) NSSet<ARReferenceObject *> *detectionObjects;

/**
 Objects to track in the scene.

 The system tracks the object at the full frame rate of the selected `videoFormat`. When an object is tracked, an
 `ARObjectAnchor` is added to the session.

 Use this property for moving or handheld objects that require precise, per-frame pose updates. High frame-rate tracking
 significantly increases power consumption and processing load. For mostly stationary objects, use `detectionObjects`
 instead.

 - Note: Only the `.referenceobject` format (introduced in iOS 27) is supported; the older `.arobject` format works only
 with `detectionObjects`. A single session can't use both formats.
*/
@property (nonatomic, copy) NSSet<ARReferenceObject *> *trackingObjects API_AVAILABLE(ios(27.0));

/**
 A Boolean value that indicates if the framework searches the physical environment for App Clip Codes.

 When this property's value is <doc://com.apple.documentation/documentation/swift/true>, the session delegate receives an
 ``ARAppClipCodeAnchor`` via ``ARSessionDelegate/session:didAddAnchors:`` for every App Clip Code that ARKit detects in the physical
 environment. The default value is `false`.

 Before calling this function, check that the configuration supports App Clip Code tracking by calling ``supportsAppClipCodeTracking``.

 To avoid scanning a physical code that's not connected to an App Clip, the system ensures that an app provides an App Clip before allowing the
 app to interact with App Clip Codes. Without providing an App Clip, the app can recognize codes in the environment by determining their
 physical location (``ARAnchor/transform``), but code URLs (``ARAppClipCodeAnchor/url``) remain `nil`.
 */
@property (nonatomic, assign) BOOL appClipCodeTrackingEnabled API_AVAILABLE(ios(14.3));

/**
 A flag that indicates if the device tracks App Clip Codes.

 Devices require the Apple Neural Engine (ANE) to track App Clip Codes. The system sets this property to
 <doc://com.apple.documentation/documentation/swift/true> if the device contains the ANE chip. The default value of this property is
 <doc://com.apple.documentation/documentation/swift/false>.

 Call this function before setting ``appClipCodeTrackingEnabled``.
 */
@property (class, nonatomic, readonly) BOOL supportsAppClipCodeTracking API_AVAILABLE(ios(14.3));

/**
 Determines if geotracking supports the user's current location.

 This function returns <doc://com.apple.documentation/documentation/swift/false> under the following circumstances:

 - ARKit lacks localization imagery for the user's geographic position.
 - A network connection is unavailable to download localization imagery.
 - The device lacks cellular (GPS) capability.

 To determine availability at a different location than the device's current location, call
 ``checkAvailabilityAtCoordinate:completionHandler:`` instead.

 For a list of supported areas and cities, see ``ARGeoTrackingConfiguration``.

 - Parameter completionHandler: Code you supply that runs after the function returns. The closure takes a Boolean argument (`isAvailable`) that
 indicates whether geotracking is available, and an `NSError` argument that describes the failure if the check could not be completed. This handler is
 executed on an arbitrary serial queue.
*/
+ (void)checkAvailabilityWithCompletionHandler:(void (^)(BOOL isAvailable, NSError *_Nullable error))completionHandler NS_SWIFT_DISABLE_ASYNC;

/**
 Determines if geotracking supports a particular location.

 This function returns <doc://com.apple.documentation/documentation/swift/false> under the following circumstances:

 - ARKit lacks localization imagery for the argument GPS coordinate.
 - A network connection is unavailable to download localization imagery.
 - The device lacks cellular (GPS) capability.

 To determine availability at the user's GPS coordinate, use ``checkAvailabilityWithCompletionHandler:`` instead.

 For a list of supported areas and cities, see ``ARGeoTrackingConfiguration``.

 - Parameters:
   - coordinate: The GPS location that the framework checks for availability.
   - completionHandler: Code you supply that runs after the function returns. The closure takes a Boolean argument (`isAvailable`) that indicates
    whether geotracking is available, and an `NSError` argument that describes the failure if the check could not be completed. This handler is
    executed on an arbitrary serial queue.
*/
+ (void)checkAvailabilityAtCoordinate:(CLLocationCoordinate2D)coordinate
                    completionHandler:(void (^)(BOOL isAvailable, NSError *_Nullable error))completionHandler NS_SWIFT_DISABLE_ASYNC;

/**
 Initializes a new geotracking configuration.

 To use the configuration in an AR experience, pass it as an argument to your app's ``ARSession/runWithConfiguration:options:`` function.
*/
- (instancetype)init;

/**
 Instantiates a new geotracking configuration.
*/
+ (instancetype)new NS_SWIFT_UNAVAILABLE("Use init() instead");

@end

API_UNAVAILABLE_END

NS_ASSUME_NONNULL_END
