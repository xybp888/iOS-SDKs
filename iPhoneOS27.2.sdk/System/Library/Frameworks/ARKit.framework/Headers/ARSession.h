#if (defined(USE_ARKIT_PUBLIC_HEADERS) && USE_ARKIT_PUBLIC_HEADERS) || !__has_include(<ARKitCore/ARSession.h>)
//
//  ARSession.h
//  ARKit
//
//  Copyright © 2016-2021 Apple Inc. All rights reserved.
//

#import <ARKit/ARConfiguration.h>
#import <ARKit/ARGeoTrackingTypes.h>
#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

API_UNAVAILABLE_BEGIN(visionos)

@class ARAnchor;
@class ARCamera;
@class ARFrame;
@class ARCollaborationData;
@class ARWorldMap;
@class ARRay;
@class ARRaycastQuery;
@class ARRaycastResult;
@class ARTrackedRaycast;
@class CALayer;

@protocol ARSessionDelegate;

/**
 Options for transitioning an AR session's current state when you change its configuration.

 If you provide no options, the session uses its default behavior: it resumes tracking from the last known position and keeps all existing anchors.
*/
API_AVAILABLE(ios(11.0))
typedef NS_OPTIONS(NSUInteger, ARSessionRunOptions) {
    /**
     An option to reset the device's position from the session's previous run.

     By default, when you call the ``ARSession/run(_:options:)`` method on a session that has run before or is already
     running, the session resumes device position tracking from its last known state. (For example, an ``ARAnchor``
     object keeps its apparent position relative to the camera.) When you call the ``ARSession/run(_:options:)`` method
     with a configuration of the same type as the session's current configuration, you can add this option to force
     device position tracking to return to its initial state.

     When you call the ``ARSession/run(_:options:)`` method with a configuration of a different type than the session's
     current configuration, the session always resets tracking (that is, this option is implicitly enabled).

     In either case, when you reset tracking, ARKit also removes any existing anchors from the session.
    */
    ARSessionRunOptionResetTracking = (1 << 0),

    /**
     An option to remove any anchor objects associated with the session's previous run.

     By default, when you call the ``ARSession/run(_:options:)`` method on a session that has run before or is already
     running, the session keeps any ``ARAnchor`` objects that you previously added. That is, objects in the AR scene
     keep their apparent real-world positions relative to the device (unless you enable the
     ``ARSessionRunOptionResetTracking`` option).

     Enable the ``ARSessionRunOptionRemoveExistingAnchors`` option if changing session configurations should invalidate
     the apparent real-world positions of objects in the AR scene. For example, if you've added virtual content to the
     AR scene whose positions are correlated to real-world objects, remove those anchors so you can reevaluate
     appropriate real-world positions. On the other hand, if the virtual content in your scene needs to track real-world
     positions only when that content first appears and can move freely thereafter, you can disable this option to keep
     the anchors.
    */
    ARSessionRunOptionRemoveExistingAnchors = (1 << 1),

    /**
     An option to stop all active tracked raycasts.

     By default, when you call the ``ARSession/run(_:options:)`` method on a session that is running or has run before,
     the session keeps tracking any ``ARTrackedRaycast`` objects that you previously added by calling
     ``ARSession/trackedRaycast(_:updateHandler:)``.

     Use ``ARSessionRunOptionStopTrackedRaycasts`` if you want to stop all active tracked raycasts. Alternatively, you
     can stop individual raycasts by calling ``ARTrackedRaycast/stopTracking()`` on individual raycasts.
    */
    ARSessionRunOptionStopTrackedRaycasts = (1 << 2),

    /**
     An option to reset the scene mesh.

     When you reset scene reconstruction, ARKit removes any existing mesh anchors (``ARMeshAnchor``) from the session.
    */
    ARSessionRunOptionResetSceneReconstruction = (1 << 3)
} NS_SWIFT_NAME(ARSession.RunOptions);

/**
 The object that manages the major tasks associated with every AR experience, such as motion tracking, camera
 passthrough, and image analysis.

 An `ARSession` object coordinates the major processes that ARKit performs on your behalf to create an augmented reality
 experience. These processes include reading data from the device's motion sensing hardware, controlling the device's
 built-in camera, and performing image analysis on captured camera images. The session synthesizes all of these results
 to establish a correspondence between the real-world space the device inhabits and a virtual space where you model AR
 content.

 ### Create a Session

 Every AR experience requires an `ARSession`. If you implement a custom renderer, you instantiate the session yourself.

 ```swift
 let session = ARSession()
 session.delegate = self
 ```

 If you use one of the standard renderers (like <doc://com.apple.documentation/documentation/realitykit/arview>,
 ``ARSCNView``, or ``ARSKView``), the renderer creates a session object for you. When you want to interact with your
 app's session, you access it on your app's renderer.

 ```swift
 let session = myView.session
 ```

 ### Run a Session

 Running a session requires a configuration. Subclasses of ``ARConfiguration`` determine how ARKit tracks a device's
 position and motion relative to the real world, and thus it determines the kinds of AR experiences you create. For
 example, ``ARWorldTrackingConfiguration`` enables you to augment the user's view of the world around them though the
 device's back camera.
 */
API_AVAILABLE(ios(11.0))
API_DEPRECATED_WITH_REPLACEMENT("Please use ar_session_t in C and ARKitSession in Swift instead.", visionos(1.0, 1.0))
@interface ARSession : NSObject

/**
 A unique identifier of the running session.

 This property might change after you call the run function, but not immediately. Therefore, to get the new value,
 listen for its change using key-value observation.

 ```swift
 // Use key-value observation to monitor my ARSession's identifier.
 var sessionIDObservation: NSKeyValueObservation?
 ...
 sessionIDObservation = observe(
     \.arView.session.identifier,
     options: [.old, .new]) {
         object, change in
         print("SessionID changed to: \(change.newValue!)")
     }
 ```
*/
@property (atomic, strong, readonly) NSUUID *identifier API_AVAILABLE(ios(13.0));

/**
 An object you provide to receive captured video images and tracking information, or to respond to changes in session
 status.

 If you use the ``ARSCNView`` or ``ARSKView`` class to display your AR experience, a session delegate isn't necessary.
 Those views automatically display captured video images and coordinate SceneKit or SpriteKit content to track device
 and camera motion.

 If you create your own visualization for an AR experience using Metal or other rendering technologies, set a session
 delegate. Your delegate object periodically receives ``ARFrame`` objects captured by the session. These objects contain
 video frame images for you to display and AR scene information you can use to coordinate display of the scene elements
 you render.
 */
@property (nonatomic, weak, nullable) id<ARSessionDelegate> delegate;

/**
 The dispatch queue through which the session calls your delegate methods.

 If this value is `nil` (the default), the session calls your delegate methods on the main queue.
*/
@property (nonatomic, strong, nullable) dispatch_queue_t delegateQueue;

/**
 The most recent still frame captured by the active camera feed, including ARKit's interpretation of it.
 */
@property (nonatomic, copy, nullable, readonly) ARFrame *currentFrame;

/**
 An object that defines motion and scene tracking behaviors for the session.
 */
@property (nonatomic, copy, nullable, readonly) ARConfiguration *configuration;

/**
 Starts AR processing for the session with the specified configuration.

 The session tracks device motion, captures and processes scene imagery from the device camera, and coordinates with
 your ``ARSession/delegate`` object or ``ARSCNView`` or ``ARSKView`` view only when running.

 Calling this method on a session that has already started transitions immediately to the new session configuration.
 After you call this method, the session runs asynchronously.

 To determine how existing session state transitions to the new configuration, use the ``ARSession/run(_:options:)``
 method instead. Calling ``ARSession/runWithConfiguration:`` is equivalent to calling ``ARSession/run(_:options:)`` with
 no options enabled.

 - Parameter configuration: An object that defines motion and scene tracking behaviors for the session.
*/
- (void)runWithConfiguration:(ARConfiguration *)configuration NS_SWIFT_UNAVAILABLE("Use run(_:options:) instead");

/**
 Starts AR processing for the session with the specified configuration and options.

 The session tracks device motion, captures and processes scene imagery from the device camera, and coordinates with
 your ``ARSession/delegate`` object or ``ARSCNView`` or ``ARSKView`` view only when running.

 Calling this method on a session that has already started transitions immediately to the new session configuration.
 The `options` parameter determines how existing session state transitions to the new configuration. By default, the
 session resumes device position tracking from the last known state and keeps any anchors already included in the
 session (those you've added manually with ``ARSession/add(anchor:)``, as well as those added automatically by ARKit
 features such as plane detection or face tracking).

 This method returns immediately when called, but the session continues to run.

 - Parameters:
   - configuration: An object that defines motion and scene tracking behaviors for the session.
   - options: Options affecting how existing session state (if any) transitions to the new configuration.

     If the session is running for the first time, this parameter has no effect.
*/
- (void)runWithConfiguration:(ARConfiguration *)configuration options:(ARSessionRunOptions)options NS_SWIFT_NAME(run(_:options:));

/**
 Pauses processing in the session.

 While paused, the session doesn't track device motion or capture scene imagery, nor does it coordinate with its
 ``ARSession/delegate`` object or update any associated
 <doc://com.apple.documentation/documentation/realitykit/realityview> or
 <doc://com.apple.documentation/documentation/realitykit/arview> object.
*/
- (void)pause;

/**
 Adds the specified anchor to be tracked by the session.

 Changes to anchor tracking take effect when the next frame is captured.

 - Parameter anchor: The anchor to add.
*/
- (void)addAnchor:(__kindof ARAnchor *)anchor NS_SWIFT_NAME(add(anchor:));

/**
 Removes the specified anchor from tracking by the session.

 Changes to anchor tracking take effect when the next frame is captured.

 - Parameter anchor: The anchor to remove.
*/
- (void)removeAnchor:(__kindof ARAnchor *)anchor NS_SWIFT_NAME(remove(anchor:));

/**
 Changes the basis for the AR world coordinate space using the specified transform.

 ARKit defines a world coordinate space for you to use to place virtual content and locate detected objects in an AR
 experience. By default, this space is based on the initial position and orientation of the device when the session
 begins. However, after a session begins and has detected useful reference points (such as a plane or image), you may
 find it helpful to redefine the world coordinate system based on those reference points.

 - Parameter relativeTransform: A transform matrix encoding a translation and orientation relative to the session's
   current world coordinate space. Any scale component of the transform is ignored.
*/
- (void)setWorldOrigin:(simd_float4x4)relativeTransform NS_SWIFT_NAME(setWorldOrigin(relativeTransform:)) API_AVAILABLE(ios(11.3));

/**
 Returns an object encapsulating the world-tracking session's space-mapping state and set of anchors.

 An ``ARWorldMap`` encapsulates the state of a running ``ARSession``. This state includes ARKit's awareness of the
 physical space the user moves the device in (which ARKit uses to determine the device's position and orientation), as
 well as any ``ARAnchor`` objects added to the session (which can represent detected real-world features or virtual
 content placed by your app). After you use this method to save a session's world map, you can assign it to a
 configuration's ``ARWorldTrackingConfiguration/initialWorldMap`` property and use ``ARSession/run(_:options:)`` to start
 another session with the same spatial awareness and anchors.

 By saving world maps and using them to start new sessions, your app can add new AR capabilities:

 - **Multiuser AR experiences.** Create a shared frame of reference by sending archived ``ARWorldMap`` objects to a
   nearby user's device. With two devices tracking the same world map, you can build a networked experience where both
   users can see and interact with the same virtual content.
 - **Persistent AR experiences.** Save a world map when your app becomes inactive, then restore it the next time your
   app launches in the same physical environment. You can use anchors from the resumed world map to place the same
   virtual content at the same positions from the saved session.

 Before saving a world map, monitor the ``ARFrame/worldMappingStatus`` property to verify that ARKit has an adequate
 understanding of the user's environment, ensuring that you can reliably make use of the saved map on a different device
 or at a later time.

 World map generation requires a world-tracking AR session. If you call this method on an ``ARSession`` not run with
 ``ARWorldTrackingConfiguration``, it invokes your completion handler immediately, providing no world map and an error.

 > Important:
 > ARKit calls your `completionHandler` on the session's ``ARSession/delegateQueue`` (if set; on the main queue
 > otherwise). If you need to perform expensive work from this handler (such as archiving and saving or sending the
 > world map), do so on an appropriate dispatch queue to avoid disrupting performance.

 - Parameter completionHandler: A closure to be invoked asynchronously after ARKit finishes generating the world map.
   The closure takes two parameters: worldMap - The generated ``ARWorldMap``, or `nil` if a map could not be generated.
   error - If the `worldMap` is `nil`, an error object describing the failure.
*/
- (void)getCurrentWorldMapWithCompletionHandler:(void (^)(ARWorldMap *_Nullable worldMap, NSError *_Nullable error))completionHandler
    API_AVAILABLE(ios(12.0));

/**
 Creates a reference object (for 3D object detection) from the specified region of the session's world space.

 > Important: This method is valid only when running a session with ``ARObjectScanningConfiguration``, which enables the
 > high-fidelity spatial data collection needed for scanning reference objects. Calling this method on a session with a
 > different configuration immediately invokes your `completionHandler` with an error.

 To use the extracted reference object for 3D object detection, assign it to the
 ``ARWorldTrackingConfiguration/detectionObjects`` property of a world tracking configuration. You can bundle reference
 objects in an app by saving them to files and adding them to an Xcode asset catalog.

 When ARKit detects a reference object, the transform of the resulting ``ARObjectAnchor`` is based on the origin of the
 reference object's coordinate system—the transform you specify when extracting the reference object. For example, if a
 reference object represents a physical item that sits on a horizontal surface, virtual content should appear to sit on
 whatever surface the physical object does. To adjust a reference object's origin after extracting it, use the
 ``ARReferenceObject/applyingTransform(_:)`` method.

 - Parameters:
   - transform: A transform matrix defining the origin and orientation of the local coordinate system for the region to
     extract.
   - center: A point, relative to the origin specified by `transform`, that defines the center of the bounding box for
     the region to extract.
   - extent: The width, height, and depth of the region to extract, centered on the `center` point and oriented to the
     local coordinate system specified by `transform`.
   - completionHandler: A handler to be invoked asynchronously after ARKit finishes creating the reference object. The
     handler takes two parameters: referenceObject - A ``ARReferenceObject`` that represents the specified region of the
     world map, or `nil` if a reference object could not be created. error - If the `referenceObject` is `nil`, an
     ``ARError`` describing the failure.
*/
- (void)createReferenceObjectWithTransform:(simd_float4x4)transform
                                    center:(simd_float3)center
                                    extent:(simd_float3)extent
                         completionHandler:(void (^)(ARReferenceObject *_Nullable referenceObject, NSError *_Nullable error))completionHandler
    NS_SWIFT_NAME(createReferenceObject(transform:center:extent:completionHandler:))
        API_DEPRECATED("Please consider migrating to the new reference object format.", ios(12.0, 27.0));

#pragma mark - Raycasting

/**
 Checks once for intersections between a ray and real-world surfaces.

 Ray casting provides a 3D location in physical space that corresponds to a given 2D location on the screen. When you
 call this function, it succeeds in returning a result when a mathematical ray that ARKit casts outward from the user
 intersects with any real-world surfaces that ARKit detects in the physical environment.

 - Parameter query: The ray you create from a screen point you're interested in.

 - Returns: An array of ray-cast results, sorted from nearest to furthest from the camera. The array is empty if the ray
 cast fails to find an intersection between the query's ray and a real-world surface.
*/
- (NSArray<ARRaycastResult *> *)raycast:(ARRaycastQuery *)query API_AVAILABLE(ios(13.0));

/**
 Repeats a ray-cast query over time to notify you of updated surfaces in the physical environment.

 A tracked ray cast wraps a ray-cast query that the session calls repeatedly, each time invoking your update handler to
 provide you with new results.

 When you're ready to stop a tracked ray cast, call ``ARTrackedRaycast/stopTracking()``.

 - Parameters:
   - query: The ray-cast query that ARKit will repeat. If you use a standard renderer, you ask the standard renderer to
     provide the ray-cast query; see Finding Real-World Surfaces of ``ARSCNView``. If you use a custom renderer, you
     create a ray-cast query by specifying a point on a particular frame; see `Finding Real-World Surfaces` in
     ``ARFrame``.
   - updateHandler: A closure you provide that ARKit calls every time it has an updated ray-cast result for you. Use
     this opportunity to update the position of any virtual content your app may have placed using the prior results of
     the tracked ray cast. ARKit invokes this closure on your session's delegate queue.

 - Returns: The tracked ray cast, or `nil` if the ray cast fails or the session's configuration isn't ``ARWorldTrackingConfiguration`` or one of its
 subclasses.
*/
- (nullable ARTrackedRaycast *)trackedRaycast:(ARRaycastQuery *)query
                                updateHandler:(void (^)(NSArray<ARRaycastResult *> *))updateHandler API_AVAILABLE(ios(13.0));

#pragma mark - Collaboration

/**
 Updates your session with information about the physical environment that is collected by another user.

 Call this function to update a session when the app receives collaboration data from other users that are participating
 in a multiuser AR experience. Your app receives this data when multiple users scan different parts of an environment
 and share that information with your app over the network. For more information, see
 ``ARWorldTrackingConfiguration/isCollaborationEnabled``.

 Collaboration is supported for world tracking configurations only.

 - Parameter collaborationData: Collaboration data for updating the session.
*/
- (void)updateWithCollaborationData:(ARCollaborationData *)collaborationData API_AVAILABLE(ios(13.0));

#pragma mark - Geo Tracking

/**
 Converts a position in the framework's local coordinate system to latitude, longitude and altitude.

 ARKit refers to its local coordinate space as "world" coordinate space, but this is different from geographic
 coordinates. For more information on ARKit's coordinate space, see ``ARSession/setWorldOrigin(relativeTransform:)``.

 To succeed, this function requires an ``ARGeoTrackingConfiguration`` session with state equal to
 ``ARGeoTrackingStatus/State/localized``.

 - Parameters:
   - position: Position in local coordinates to convert.
   - completionHandler: Code that control will execute when this function returns. The session runs this code on its
     delegate queue. The parameters are: coordinate - Location coordinates (latitude, longitude). altitude - The
     altitude. error - The reason, if conversion fails.
*/
- (void)getGeoLocationForPoint:(simd_float3)position
             completionHandler:(void (^)(CLLocationCoordinate2D coordinate, CLLocationDistance altitude, NSError *_Nullable error))completionHandler
    API_AVAILABLE(ios(14.0));

#pragma mark - High Resolution Frame Capturing

/**
 Requests a frame outside of the normal frequency that contains a high-resolution captured image.

 If the function succeeds, the completion handler's frame contains a high quality, high resolution
 ``ARFrame/capturedImage``.

 In the event of failure, the completion block receives a non-`nil` error object. A call may fail if a previous request
 for a high resolution capture hasn't completed yet, or an underlying problem occurs in the system's capture pipeline.
 You can identify the failure reason in either case by checking for ``ARError/highResolutionFrameCaptureInProgress`` or
 ``ARError/highResolutionFrameCaptureFailed``, respectively.

 ARKit populates the frame's properties other than pixel data, including pose information, anchors, and frame semantics.
 The system provides the frame to your completion handler asynchronously.

 You can call this function at any time during a session. The system delivers a high-resolution frame out-of-band, which
 means that it doesn't affect the other frames that the session receives at a regular interval, such as
 ``ARSession/currentFrame`` or the frame argument to ``ARSessionDelegate/session(_:didUpdate:)-9v2kw``.

 For the highest resolution captured image, choose a non-binned ``ARConfiguration/videoFormat`` in your session's
 configuration. You can call ``ARConfiguration/recommendedVideoFormatForHighResolutionFrameCapturing`` to select the
 best option for you.

 For the highest resolution still images, choose a ``ARConfiguration/videoFormat`` among your configuration's
 ``ARConfiguration/supportedVideoFormats`` that returns `true` for
 ``ARConfiguration/VideoFormat/isRecommendedForHighResolutionFrameCapturing``. If your app doesn't have specific
 resolution requirements, you can use the framework-recommended format that
 ``ARConfiguration/recommendedVideoFormatForHighResolutionFrameCapturing`` returns.

 - Parameter completion: Code you provide that the framework runs after attempting to generate the frame.
*/
- (void)captureHighResolutionFrameWithCompletion:(void (^)(ARFrame *_Nullable frame, NSError *_Nullable error))completion API_AVAILABLE(ios(16.0));

/**
 Requests a single, high resolution frame to be captured.

 Some video formats do not support a significantly higher still image resolution than the streaming camera resolution. Use the
 `isRecommendedForHighResolutionFrameCapturing` method on the video format to check if the format is recommended. For passing customized photo
 settings to this method, obtain a `defaultPhotoSettings` object from the video format and modify it.

 - Parameters:
   - photoSettings: Custom AVCapturePhotoSettings to be used.
   - completion: Block being called when the call completes.
*/
- (void)captureHighResolutionFrameUsingPhotoSettings:(nullable AVCapturePhotoSettings *)photoSettings
                                          completion:(void (^)(ARFrame *_Nullable frame, NSError *_Nullable error))completion API_AVAILABLE(ios(26.0))
                                                         API_UNAVAILABLE(visionos);

/**
 The layer that displays the `ARFrame`, required before `viewRotationAngle` becomes available.

 Assign the layer that presents the camera image. Renderers such as `ARSCNView`, `ARSKView`, `ARView`, and
 `RealityView` set this for you.
 */
@property (nonatomic, weak, nullable) CALayer *viewLayer API_AVAILABLE(ios(27.0));

/**
 The angle, in degrees, to rotate a view by so the `ARFrame` it displays stays level with the horizon as the device
 rotates.

 Updates in step with the system UI rotation. The value is normalized to `[0, 360)` (`0` at LandscapeRight, `90` at
 Portrait, `180` at LandscapeLeft, `270` at PortraitUpsideDown), or `NaN` until the angle is available (`viewLayer` is
 set and on screen).
 */
@property (atomic, readonly) CGFloat viewRotationAngle API_AVAILABLE(ios(27.0)) NS_REFINED_FOR_SWIFT;

@end

#pragma mark - ARSessionObserver

/**
 Methods you can implement to respond to changes in the state of an AR session.

 This protocol defines optional methods common to the ``ARSessionDelegate``, ``ARSCNViewDelegate``, and
 ``ARSKViewDelegate`` protocols. You can implement this protocol's methods when adopting one of those protocols.
 */
API_AVAILABLE(ios(11.0))
API_DEPRECATED_WITH_REPLACEMENT("Please use ar_session_t in C and ARKitSession in Swift instead.", visionos(1.0, 1.0))
@protocol ARSessionObserver <NSObject>

@optional

/**
 Tells the delegate that the session has stopped running due to an error.

 On failure the session will be paused.

 - Parameters:
   - session: The session providing information.
   - error: An object describing the failure.
*/
- (void)session:(ARSession *)session didFailWithError:(NSError *)error;

/**
 Informs the delegate of changes to the quality of ARKit's device position tracking.

 ARKit tracks the position and orientation of the device relative to a virtual scene through a combination of motion
 sensing and image processing. As such, factors that affect signal quality from the device's motion sensing hardware or
 that interfere with scene detection in the camera image can result in poor estimates of the device position relative to
 the virtual scene.

 - Parameters:
   - session: The session providing information.
   - camera: The camera whose tracking parameters have changed. (Equivalent to
     ``ARSession/currentFrame``.``ARFrame/camera``.)
*/
- (void)session:(ARSession *)session cameraDidChangeTrackingState:(ARCamera *)camera;

/**
 Tells the delegate that the session has temporarily stopped processing frames and tracking device position.

 A session is interrupted when it fails to receive camera or motion sensing data. Session interruptions occur whenever
 camera capture is not available—for example, when your app is in the background or there are multiple foreground
 apps—or when the device is too busy to process motion sensor data.

 > Important:
 > An interruption is equivalent to manually pausing the session. Do not call ``ARSession/pause()`` in response to this
 > callback, as that prevents your app from being notified when the interruption ends.

 - Parameter session: The session providing information.
*/
- (void)sessionWasInterrupted:(ARSession *)session;

/**
 Tells the delegate that the session has resumed processing frames and tracking device position.

 After a session has been interrupted (see the ``ARSessionObserver/sessionWasInterrupted(_:)`` delegate method), it
 automatically resumes running whenever the conditions that caused the interruption improve.

 When a session resumes, it continues tracking from its last known state. However, if the device has moved since the
 interruption began, the ARKit world coordinate system and anchor positions no longer match their original real-world
 frame of reference. To attempt recovery of world tracking from before the interruption, implement the
 ``ARSessionObserver/sessionShouldAttemptRelocalization(_:)`` delegate method.

 - Parameter session: The session providing information.
*/
- (void)sessionInterruptionEnded:(ARSession *)session;

/**
 Asks the delegate whether to attempt recovery of world-tracking state after an interruption.

 When ARKit loses track of the device's position or orientation, ARKit calls
 ``ARSessionObserver/sessionShouldAttemptRelocalization(_:)`` to try to resume the experience where the user left off.
 This process is called _relocalization_. ARKit relocalizes when it loses access to the camera or other sensors on the
 device, such as when your app calls ``ARSession/pause()``, or when the user switches to another app and back.

 When relocalization succeeds, your app's virtual content appears in the same position it was in before the
 interruption. But if your app fails to relocalize, the world coordinate system and anchor positions are likely out of
 sync with the real world.

 Here are the possible scenarios:

 - If by default you don't implement this function, ARKit spends a few seconds trying to relocalize before restarting
   your session.
 - If you implement this function and return <doc://com.apple.documentation/documentation/swift/false>, ARKit does not
   attempt to relocalize after an interruption, and the session restarts immediately.
 - If you implement this function and return <doc://com.apple.documentation/documentation/swift/true>, you allow the
   user more time to find the location they were in and resume where they left off, but you're responsible for
   restarting the session when it's prudent to do so.

 When you return <doc://com.apple.documentation/documentation/swift/true>, guide the user to facilitate relocalization;
 for example, by presenting a UI that asks them to return to their previous location. Relocalization works when ARKit
 recognizes the physical environment it observed before the interruption. If the user does not return to their previous
 location, the app stays in ``ARCamera/TrackingState/Reason/relocalizing`` state indefinitely. It's important to give
 the user a way to restart if they choose to. Using ``ARCoachingOverlayView`` makes much of this functionality
 available.

 To respond to failed relocalization, call the session's ``ARSession/run(_:options:)`` method with the
 ``ARSession/RunOptions/resetTracking`` option. Resetting tracking during relocalization discards all world-tracking
 state from before the interruption, but keeps world-tracking results obtained during the relocalization attempt.

 - Parameter session: The session providing information.

 - Returns: Return YES to begin relocalizing.
*/
- (BOOL)sessionShouldAttemptRelocalization:(ARSession *)session API_AVAILABLE(ios(11.3));

/**
 Tells the delegate that a new sample buffer of recorded audio is available.

 ARKit calls this method on your delegate object only if you're running an AR session with a configuration whose
 ``ARConfiguration/providesAudioData`` setting is <doc://com.apple.documentation/documentation/swift/true>.

 - Parameters:
   - session: The session providing information.
   - audioSampleBuffer: The sample buffer that was output.
*/
- (void)session:(ARSession *)session didOutputAudioSampleBuffer:(CMSampleBufferRef)audioSampleBuffer;

/**
 Provides information for nearby users about your perspective in the environment.

 The data parameter contains information about your perspective in the physical environment. When ARKit invokes this
 function, send the `data` object to nearby users. The users update their session with your data to gain your app's
 model of the physical environment in addition to their own. For more information, see
 ``ARWorldTrackingConfiguration/isCollaborationEnabled``.

 For an example app that implements this callback, see <doc:creating-a-collaborative-session>.

 - Parameters:
   - session: The app's collaborative session.
   - data: The information to share with participants.
*/
- (void)session:(ARSession *)session didOutputCollaborationData:(ARCollaborationData *)data API_AVAILABLE(ios(13.0));

/**
 Listen and react to geo-tracking state changes.

 To create and maintain an effective geo-tracking session, an app must react promptly when ARKit changes the
 geo-tracking status. For more information, see ``ARGeoTrackingStatus``.

 ARKit invokes this callback only for ``ARGeoTrackingConfiguration`` sessions.

 - Parameters:
   - session: The geo-tracking session.
   - geoTrackingStatus: The new status.
*/
- (void)session:(ARSession *)session didChangeGeoTrackingStatus:(ARGeoTrackingStatus *)geoTrackingStatus API_AVAILABLE(ios(14.0));

/**
 This is called when the view rotation angle changes.

 ARKit calls this method when a new angle becomes available, in step with the system UI rotation. Implement it to
 rotate a view by the given angle so the `ARFrame` it displays stays level with the horizon as the device rotates.

 - Parameters:
   - session: The session that provides the angle.
   - viewRotationAngle: The angle, in degrees, normalized to `[0, 360)` (`0` at LandscapeRight, `90` at Portrait,
     `180` at LandscapeLeft, and `270` at PortraitUpsideDown).
 */
- (void)session:(ARSession *)session didChangeViewRotationAngle:(CGFloat)viewRotationAngle API_AVAILABLE(ios(27.0));

@end

#pragma mark - ARSessionDelegate

/**
 Methods you can implement to receive captured video frame images and tracking state from an AR session.

 Implement this protocol if you need to work directly with ``ARFrame`` objects captured by the session or directly
 follow changes to the session's set of tracked ``ARAnchor`` objects. Typically, you adopt this protocol when building a
 custom view for displaying AR content—if you display content with SceneKit or SpriteKit, the ``ARSCNViewDelegate`` and
 ``ARSKViewDelegate`` protocols provide similar information and integrate with those technologies.

 This protocol extends the ``ARSessionObserver`` protocol, so your session delegate can also implement those methods to
 respond to changes in session status.
 */
API_AVAILABLE(ios(11.0))
API_DEPRECATED_WITH_REPLACEMENT("Please use ar_session_t in C and ARKitSession in Swift instead.", visionos(1.0, 1.0))
@protocol ARSessionDelegate <ARSessionObserver>

@optional

/**
 Provides a newly captured camera image and accompanying AR information to the delegate.

 Implement this method if you provide your own display for rendering an AR experience. The provided ``ARFrame`` object
 contains the latest image captured from the device camera, which you can render as a scene background, as well as
 information about camera parameters and anchor transforms you can use for rendering virtual content on top of the
 camera image.

 - Parameters:
   - session: The session providing information.
   - frame: An object containing the new camera image and AR information.
*/
- (void)session:(ARSession *)session didUpdateFrame:(ARFrame *)frame;

/**
 Tells the delegate that one or more anchors have been added to the session.

 Depending on the session configuration, ARKit may automatically add anchors to a session.

 If you display an AR experience using SceneKit or SpriteKit, you can instead implement one of the following methods
 instead to track not only the addition of anchors to the session but also how to add SceneKit or SpriteKit content to
 the corresponding scene:

 - ``ARSCNView``: ``ARSCNViewDelegate/renderer(_:nodeFor:)`` or ``ARSCNViewDelegate/renderer(_:didAdd:for:)``
 - ``ARSKView``: ``ARSKView/node(for:)`` or ``ARSKViewDelegate/view(_:didAdd:for:)``

 - Parameters:
   - session: The session providing information.
   - anchors: The anchors newly added to the session.
*/
- (void)session:(ARSession *)session didAddAnchors:(NSArray<__kindof ARAnchor *> *)anchors;

/**
 Tells the delegate that the session has adjusted the properties of one or more anchors.

 Depending on the session configuration, ARKit may automatically update the properties of anchors in a session.

 If you display an AR experience using SceneKit or SpriteKit, you can implement one of the following methods instead to
 track not only the anchors in the session but also any corresponding SceneKit or SpriteKit content:

 - ``ARSCNView``: ``ARSCNViewDelegate/renderer(_:willUpdate:for:)`` or ``ARSCNViewDelegate/renderer(_:didUpdate:for:)``
 - ``ARSKView``: ``ARSKViewDelegate/view(_:willUpdate:for:)`` or ``ARSKViewDelegate/view(_:didUpdate:for:)``

 - Parameters:
   - session: The session providing information.
   - anchors: The anchors whose properties have changed.
*/
- (void)session:(ARSession *)session didUpdateAnchors:(NSArray<__kindof ARAnchor *> *)anchors;

/**
 Tells the delegate that one or more anchors have been removed from the session.

 Depending on the session configuration, ARKit may automatically remove anchors from a session.

 If you display an AR experience using SceneKit or SpriteKit, you can instead implement one of the following methods
 instead to track not only the anchors in the session but also any corresponding SceneKit or SpriteKit content:

 - ``ARSCNView``: ``ARSCNViewDelegate/renderer(_:didRemove:for:)``
 - ``ARSKView``: ``ARSKViewDelegate/view(_:didRemove:for:)``

 - Parameters:
   - session: The session providing information.
   - anchors: The anchors newly removed from the session.
*/
- (void)session:(ARSession *)session didRemoveAnchors:(NSArray<__kindof ARAnchor *> *)anchors;

@end

/**
 An object that provides a session.

 As an example usage, ``ARCoachingOverlayView`` exposes ``ARCoachingOverlayView/sessionProvider`` to access your app's
 current session.
 */
API_DEPRECATED_WITH_REPLACEMENT("Please use ar_session_t in C and ARKitSession in Swift instead.", visionos(1.0, 1.0))
@protocol ARSessionProviding <NSObject>

/**
 A contract to declare an AR session.

 Some clients may use key-value observation (KVO) to be notified when this property changes values. To support KVO,
 Swift classes that adopt ``ARSessionProviding`` should mark its ``ARSessionProviding/session`` as `@objc` and
 `dynamic`.
*/
@property (readonly) ARSession *session;

@end

API_UNAVAILABLE_END

NS_ASSUME_NONNULL_END
#else
#import <ARKitCore/ARSession.h> 
#endif // #if (defined(USE_ARKIT_PUBLIC_HEADERS) \&\& USE_ARKIT_PUBLIC_HEADERS) || !__has_include(<ARKitCore/ARSession.h>)