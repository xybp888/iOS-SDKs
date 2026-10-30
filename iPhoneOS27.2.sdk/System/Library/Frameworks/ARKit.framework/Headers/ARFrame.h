#if (defined(USE_ARKIT_PUBLIC_HEADERS) && USE_ARKIT_PUBLIC_HEADERS) || !__has_include(<ARKitCore/ARFrame.h>)
//
//  ARFrame.h
//  ARKit
//
//  Copyright © 2016-2021 Apple Inc. All rights reserved.
//

#import <CoreVideo/CoreVideo.h>
#import <Foundation/Foundation.h>
#import <simd/simd.h>

#import <ARKit/ARGeoTrackingTypes.h>
#import <ARKit/ARHitTestResult.h>
#import <ARKit/ARRaycastQuery.h>

@class ARAnchor;
@class ARCamera;
@class ARLightEstimate;
@class ARPointCloud;
@class AVDepthData;
@class ARBody2D;
@class ARDepthData;
@class AVMetadataObject;

@protocol MTLTexture;

NS_ASSUME_NONNULL_BEGIN

API_UNAVAILABLE_BEGIN(visionos)

/**
 A categorization of a pixel that defines a type of content you use to occlude your app's virtual content.

 ARKit applies the categories defined in this class based on its interpretation of the camera feed's pixel data. Only people are identified in a
 camera feed, and therefore the available pixel classifications are either ``person`` or ``none``.

 - SeeAlso: ``ARConfiguration/frameSemantics``
 - SeeAlso: ``ARFrame/segmentationBuffer``
*/
API_AVAILABLE(ios(13.0))
typedef NS_ENUM(uint8_t, ARSegmentationClass) {
    /** A classification of a pixel in the segmentation buffer as unidentified. */
    ARSegmentationClassNone = 0,

    /** A classification of a pixel in the segmentation buffer as part of a person. */
    ARSegmentationClassPerson = 255

} NS_SWIFT_NAME(ARFrame.SegmentationClass);

/**
 A value describing the world mapping status for the area visible in a given frame.
 */
API_AVAILABLE(ios(12.0))
typedef NS_ENUM(NSInteger, ARWorldMappingStatus) {
    /** No world map is available.

     When the ``ARFrame/worldMappingStatus`` of the session's ``ARSession/currentFrame`` is ``ARFrame/WorldMappingStatus/notAvailable``, the session
     has no internal map of the real-world space around the device, nor the scene visible to the camera. Calling
     ``ARSession/getCurrentWorldMap(completionHandler:)`` at this time results in an error.

     This status occurs shortly after starting a new session. To save or share a world map, wait for the user to explore their surroundings and the
     session's status to change to ``ARFrame/WorldMappingStatus/mapped`` or ``ARFrame/WorldMappingStatus/extending``. */
    ARWorldMappingStatusNotAvailable,

    /** World tracking has not yet sufficiently mapped the area around the current device position.

     When the ``ARFrame/worldMappingStatus`` of the session's ``ARSession/currentFrame`` is ``ARFrame/WorldMappingStatus/limited``, the session has
     not yet fully mapped the real-world space around the device, nor the scene visible to the camera.

     Although it is possible at this time to save a world map by calling ``ARSession/getCurrentWorldMap(completionHandler:)``, the resulting
     ``ARWorldMap`` is unlikely to be useful for relocalization in the real-world space near the device's current position.

     To produce a higher quality world map, wait for the user to explore more of their surroundings and the session's status to change to
     ``ARFrame/WorldMappingStatus/mapped`` or ``ARFrame/WorldMappingStatus/extending``. */
    ARWorldMappingStatusLimited,

    /** World tracking has mapped recently visited areas, but is still mapping around the current device position.

     When the ``ARFrame/worldMappingStatus`` of the session's ``ARSession/currentFrame`` is ``ARFrame/WorldMappingStatus/extending``, the session has
     produced a high-fidelity internal map of the real-world spaces the device has recently passed through, but is still collecting data to map the
     area around the device's current position and the scene visible to the camera.

     This status provides moderate to high reliability for relocalizing to a saved world map, provided that:

     1. You call ``ARSession/getCurrentWorldMap(completionHandler:)`` to save the world map while the status of the ``ARSession/currentFrame`` is
     ``ARFrame/WorldMappingStatus/extending``.
     2. When you run a new session (later or on another device) from that ``ARWorldMap``, the device running the new session passes through positions
     and orientations that were visited by the device that saved the session.

     Saving or sharing a world map at this time is likely to produce adequate results, but a higher quality world map may be possible if you wait
     until the user explores more of their surroundings and the status changes to ``ARFrame/WorldMappingStatus/mapped``. */
    ARWorldMappingStatusExtending,

    /** World tracking has adequately mapped the visible area.

     When the ``ARFrame/worldMappingStatus`` of the session's ``ARSession/currentFrame`` is ``ARFrame/WorldMappingStatus/mapped``, the session has
     produced a high-fidelity internal map of the real-world space around the device's current position and the scene visible to the camera.

     This status provides the highest reliability for relocalizing to a saved world map, provided that:

     1. You call ``ARSession/getCurrentWorldMap(completionHandler:)`` to save the world map while the status of the ``ARSession/currentFrame`` is
     ``ARFrame/WorldMappingStatus/mapped``.
     2. When you run a new session (later or on another device) from that ``ARWorldMap``, the device running the new session is at a real-world
     position and orientation similar to that when the world map was saved. */
    ARWorldMappingStatusMapped
} NS_SWIFT_NAME(ARFrame.WorldMappingStatus);

/**
 A video image captured as part of a session with position-tracking information.

 A running session continuously captures video frames from the device's camera while ARKit analyzes the captures to determine the user's position in
 the world. ARKit can provide this information to you in the form of an ``ARFrame`` in two ways:

 - Occasionally, by accessing an ``ARSession`` object's ``ARSession/currentFrame``
 - Constantly, as a stream of frames through the ``ARSessionDelegate/session(_:didUpdate:)-9v2kw`` callback

 To automatically receive all frames as ARKit captures them, make one of your objects the ``ARSession/delegate`` of your app's ``ARSession``.

 Each frame can contain additional data, for example, EXIF (``exifData``), or data based on any particular ``ARConfiguration/frameSemantics`` that you
 enable.
*/
API_AVAILABLE(ios(11.0))
NS_SWIFT_SENDABLE
@interface ARFrame : NSObject <NSCopying>

/**
 The time at which the frame was captured.
 */
@property (nonatomic, readonly) NSTimeInterval timestamp;

/**
 A pixel buffer containing the image captured by the camera.

 ARKit captures pixel buffers in a full-range planar YCbCr format (also known as YUV) format according to the ITU R. 601-4 standard. (You can verify
 this by checking the <doc://com.apple.documentation/documentation/corevideo/kcvimagebufferycbcrmatrixkey> pixel buffer attachment.)

 Unlike some uses of that standard, ARKit captures full-range color space values, not video-range values. To correctly render these images on a device
 display, you'll need to access the luma and chroma planes of the pixel buffer and convert full-range YCbCr values to an sRGB (or ITU R. 709) format
 according to the ITU-T T.871 specification.

 The following matrix (shown in Metal shader syntax) performs this conversion when multiplied by a 4-element vector (containing Y', Cb, Cr values and
 an "alpha" value of 1.0):

 ```cpp
 const float4x4 ycbcrToRGBTransform = float4x4(
     float4(+1.0000f, +1.0000f, +1.0000f, +0.0000f),
     float4(+0.0000f, -0.3441f, +1.7720f, +0.0000f),
     float4(+1.4020f, -0.7141f, +0.0000f, +0.0000f),
     float4(-0.7010f, +0.5291f, -0.8860f, +1.0000f)
 );
 ```

 For more details, see <doc:displaying-an-ar-experience-with-metal>, or use the Metal variant of the AR app template when creating a new project in
 Xcode.
 */
@property (nonatomic, readonly) CVPixelBufferRef capturedImage;

/**
 Auxiliary data for the captured image.

 The system's image capture pipeline produces pixel data and auxiliary information for each exposure. The AR frame exposes this pixel data through
 ``ARFrame/capturedImage`` and the auxiliary info through this property (``ARFrame/exifData``). Example EXIF data includes camera manufacturer,
 orientation, compression, resolution, exposure, and the date and time that the exposure occurred.
 */
@property (nonatomic, strong, readonly) NSDictionary<NSString *, id> *exifData API_AVAILABLE(ios(16.0));

/**
 A tileable Metal texture created by ARKit to match the visual characteristics of the current video stream.

 Camera grain enhances the visual cohesion of the real and augmented aspects of your user experience by enabling your app's virtual content to take on
 similar image noise characteristics that naturally occur in the camera feed.

 ![Screenshot showing the before and after cases of applying image noise to an app's virtual content.](media-3261294)

 If ``ARSCNView`` is your renderer, SceneKit applies camera grain to your app's virtual content by default. For more information, see
 ``ARSCNView/rendersCameraGrain``.

 ### Enable Image Noise on a Custom Renderer

 For apps that display an AR experience using a custom Metal renderer, ARKit provides you with an ``ARFrame/cameraGrainTexture`` that matches the
 noise it detects in the current video stream. Set the noise texture onto your renderer to apply its characteristics to your virtual content.

 The depth dimension of the image noise texture contains variations that you select at runtime based on the ``ARFrame/cameraGrainIntensity`` of the
 current frame.
*/
@property (nonatomic, nullable, readonly) id<MTLTexture> cameraGrainTexture API_AVAILABLE(ios(13.0));

/**
 A value that specifies the amount of grain present in the camera grain texture.

 This property is normalized within the range [0..1], where zero specifies no grain, and one specifies the maximum amount of grain.

 When you apply this value to the depth component of the ``ARFrame/cameraGrainTexture``, you select among variations of visual image noise data stored
 in the Metal texture that conceptually match this level of intensity.
*/
@property (nonatomic, readonly) float cameraGrainIntensity API_AVAILABLE(ios(13.0));

/**
 Depth data captured in front-camera experiences.

 Frames vended by the session contain a depth map captured by the depth sensor in addition to the color pixel buffer (see ``ARFrame/capturedImage``)
 captured by the color camera. The depth-sensing camera provides data at a different frame rate than the color camera, so this property's value can be
 `nil` if no depth data was captured at the same time as the current color image.

 This depth data is available only in face-based experiences (see ``ARFaceTrackingConfiguration``) using the device's front TrueDepth camera. This
 property's value is `nil` when running other AR configurations.
*/
@property (nonatomic, strong, nullable, readonly) AVDepthData *capturedDepthData;

/**
 The time at which depth data for the frame (if any) was captured.

 Face-based AR (see ``ARFaceTrackingConfiguration``) uses the front-facing, depth-sensing camera on compatible devices. When running such a
 configuration, frames vended by the session contain a depth map captured by the depth camera in addition to the color pixel buffer (see
 ``ARFrame/capturedImage``) captured by the color camera. This property's value is always zero when running other AR configurations.

 The depth-sensing camera provides data at a different frame rate than the color camera, so this property's value may not exactly match the
 ``ARFrame/timestamp`` property for the image captured by the color camera, and can also be zero if no depth data was captured at the same time as the
 current color image.
 */
@property (nonatomic, readonly) NSTimeInterval capturedDepthDataTimestamp;

/**
 Information about the camera position, orientation, and imaging parameters used to capture the frame.
*/
@property (nonatomic, copy, readonly) ARCamera *camera;

/**
 The list of anchors representing positions tracked or objects detected in the scene.

 You can manually add or remove anchors to track locations in the scene using the ``ARSession`` class. Depending on session configuration, ARKit may
 also add anchors, such as the origin of the world coordinate system or automatically detected planes.
 */
@property (nonatomic, copy, readonly) NSArray<__kindof ARAnchor *> *anchors;

/**
 An estimate of lighting conditions based on the camera image.

 If you render your own overlay graphics for the AR scene, you can use this information in shading algorithms to help make those graphics match the
 real-world lighting conditions of the scene captured by the camera. (The ``ARSCNView`` class automatically uses this information to configure
 SceneKit lighting.)

 This property's value is `nil` if the ``ARConfiguration/isLightEstimationEnabled`` property of the session configuration that captured this frame is
 <doc://com.apple.documentation/documentation/swift/false>.
*/
@property (nonatomic, strong, nullable, readonly) ARLightEstimate *lightEstimate;

/**
 The current intermediate results of the scene analysis ARKit uses to perform world tracking.

 These points represent notable features detected in the camera image. Their positions in 3D world coordinate space are extrapolated as part of the
 image analysis that ARKit performs in order to accurately track the device's position, orientation, and movement. Taken together, these points
 loosely correlate to the contours of real-world objects in view of the camera.

 ARKit does not guarantee that the number and arrangement of raw feature points will remain stable between software releases, or even between
 subsequent frames in the same session. Regardless, the point cloud can sometimes prove useful when debugging your app's placement of virtual objects
 into the real-world scene.

 If you display AR content with SceneKit using the ``ARSCNView`` class, you can display this point cloud with the
 ``ARSCNDebugOptionShowFeaturePoints`` debug option.

 Feature point detection requires a ``ARWorldTrackingConfiguration`` session.
*/
@property (nonatomic, strong, nullable, readonly) ARPointCloud *rawFeaturePoints;

/**
 The feasibility of generating or relocalizing a world map for this frame.

 Every world-tracking session builds an internal world map, which ARKit uses to determine the device's position in the user's environment. You can
 save a snapshot of that internal state as an ``ARWorldMap`` object, which you can use later to resume the saved session or share between devices to
 create a multiuser AR experience.

 While you can call ``ARSession/getCurrentWorldMap(completionHandler:)`` at any time during a session, some times are better than others. Use this
 property to determine whether the session currently has enough data to generate a useful ``ARWorldMap`` or if it's better to wait for the session to
 map more of the user's local environment first.
*/
@property (nonatomic, readonly) ARWorldMappingStatus worldMappingStatus API_AVAILABLE(ios(12.0));

/**
 A buffer that contains pixel information identifying the shape of objects from the camera feed that you use to occlude virtual content.

 ARKit generates the contents of this buffer by processing the camera feed.

 If you implement a custom renderer, you apply this property by using alpha and depth mattes provided with ``ARMatteGenerator``.

 Apps using one of the standard renderers don't need this property to occlude virtual content with people. The standard renderers
 (<doc://com.apple.documentation/documentation/realitykit/arview>, ``ARSCNView``, and ``ARSKView``) enable people occlusion when you add
 ``ARConfiguration/FrameSemantics/personSegmentation`` or ``ARConfiguration/FrameSemantics/personSegmentationWithDepth`` to your configuration's
 ``ARConfiguration/frameSemantics``.

 - SeeAlso: ``ARSegmentationClass``
 - SeeAlso: ``ARConfiguration/frameSemantics``
*/
@property (nonatomic, nullable, readonly) CVPixelBufferRef segmentationBuffer API_AVAILABLE(ios(13.0));

/**
 A buffer that represents the estimated depth values from the camera feed that you use to occlude virtual content.

 Each non-background pixel in the segmentation buffer maps to a depth value in this buffer. Use this to occlude people from the rendering of your
 app's virtual content.

 If you implement a custom renderer, you apply this property by using alpha and depth mattes provided with ``ARMatteGenerator``.

 Apps using one of the standard renderers don't need this property to occlude virtual content with people. The standard renderers
 (<doc://com.apple.documentation/documentation/realitykit/arview>, ``ARSCNView``, and ``ARSKView``) enable people occlusion when you add
 ``ARConfiguration/FrameSemantics/personSegmentation`` or ``ARConfiguration/FrameSemantics/personSegmentationWithDepth`` to your configuration's
 ``ARConfiguration/frameSemantics``.

 - SeeAlso: ``ARConfiguration/frameSemantics``
 - SeeAlso: ``ARFrame/segmentationBuffer``
*/
@property (nonatomic, nullable, readonly) CVPixelBufferRef estimatedDepthData API_AVAILABLE(ios(13.0));

/**
 The screen position information of a body that ARKit recognizes in the camera image.

 To enable 2D body detection, you add the ``ARConfiguration/FrameSemantics/bodyDetection`` frame semantic to your configuration's
 ``ARConfiguration/frameSemantics`` property, or run your session with an ``ARBodyTrackingConfiguration``, in which body detection is enabled by
 default.

 - SeeAlso: ``ARConfiguration/frameSemantics``
 */
@property (nonatomic, nullable, readonly) ARBody2D *detectedBody API_AVAILABLE(ios(13.0));

/**
 The session's condition with respect to geographic tracking at the time the session captured the frame.

 For the current geo-tracking status, check the value of this property on the session's ``ARSession/currentFrame``. ARKit populates this property only
 for ``ARGeoTrackingConfiguration`` sessions.
 */
@property (nonatomic, strong, nullable, readonly) ARGeoTrackingStatus *geoTrackingStatus API_AVAILABLE(ios(14.0));

/**
 Data on the distance between a device's rear camera and real-world objects in an AR experience.

 This property describes the distance between a device's camera and objects or areas in the real world, including ARKit's confidence in the estimated
 distance.

 This property is `nil` by default. Add the ``ARConfiguration/FrameSemantics/sceneDepth`` frame semantic to your configuration's
 ``ARConfiguration/frameSemantics`` to instruct the framework to populate this value with ``ARDepthData`` captured by the LiDAR scanner.

 Call ``ARConfiguration/supportsFrameSemantics(_:)`` on your app's configuration to support scene depth on select devices and configurations.

 - SeeAlso: ``ARFrameSemanticSceneDepth``
 - SeeAlso: ``ARConfiguration/frameSemantics``
 */
@property (nonatomic, strong, nullable, readonly) ARDepthData *sceneDepth API_AVAILABLE(ios(14.0));

/**
 An average of distance measurements between a device's rear camera and real-world objects that creates smoother visuals in an AR experience.

 This property describes the distance between a device's camera and objects or areas in the real world, including ARKit's confidence in the estimated
 distance. This is similar to ``ARFrame/sceneDepth`` except that the framework smoothes the depth data over time to lessen its frame-to-frame delta.

 This property is `nil` by default. Add the ``ARConfiguration/FrameSemantics/smoothedSceneDepth`` frame semantic to your configuration's
 ``ARConfiguration/frameSemantics`` to instruct the framework to populate this value with ``ARDepthData`` captured by the LiDAR scanner.

 Call ``ARConfiguration/supportsFrameSemantics(_:)`` on your app's configuration to support smoothed scene depth on select devices and configurations.

 - SeeAlso: ``ARFrameSemanticSmoothedSceneDepth``
 - SeeAlso: ``ARConfiguration/frameSemantics``
 */
@property (nonatomic, strong, nullable, readonly) ARDepthData *smoothedSceneDepth API_AVAILABLE(ios(14.0));

/**
 Metadata objects associated with the current frame.

 This array contains `AVMetadataFaceObject`s for detected faces when running an `ARFaceTrackingConfiguration` and face tracking is not
 active (`maximumNumberOfTrackedFaces` set to 0).

 - SeeAlso: ``ARFaceTrackingConfiguration/maximumNumberOfTrackedFaces``
 */
@property (nonatomic, strong, readonly) NSArray<__kindof AVMetadataObject *> *metadataObjects API_AVAILABLE(ios(27.0)) API_UNAVAILABLE(visionos);

/**
 Searches for real-world objects or AR anchors in the captured camera image.

 Hit testing searches for real-world objects or surfaces detected through the AR session's processing of the camera image. A 2D point in the image
 coordinates can refer to any point along a 3D line that starts at the device camera and extends in a direction determined by the device orientation
 and camera projection. This method searches along that line, returning all objects that intersect it in order of distance from the camera.

 > Note:
 > If you use ARKit with a SceneKit or SpriteKit view, the ``ARSCNView`` ``ARSCNView/hitTest(_:types:)`` or ``ARSKView``
 ``ARSKView/hitTest(_:types:)`` method lets you specify a search point in view coordinates.

 The behavior of a hit test depends on which `types` you specify and the order you specify them in. For details, see ``ARHitTestResult`` and the
 various ``ARHitTestResult/ResultType`` options.

 - Parameters:
   - point: A point in normalized image coordinate space. (The point `(0,0)` represents the top left corner of the image, and the point `(1,1)`
 represents the bottom right corner.)
   - types: The types of hit-test result to search for.

 - Returns: A list of results, sorted from nearest to farthest (in distance from the camera).
*/
- (NSArray<ARHitTestResult *> *)hitTest:(CGPoint)point types:(ARHitTestResultType)types API_DEPRECATED("Use [ARSession raycast:]", ios(11.0, 14.0));

/**
 Creates a raycast query for a screen point.

 To cast the ray, you pass the resulting query to your current session via ``ARSession/raycast(_:)`` or
 ``ARSession/trackedRaycast(_:updateHandler:)``.

 - Parameters:
   - point: A normalized coordinate in the UI system, where 0 is top-left, and 1 is bottom-right.
   - target: The type of surface the raycast query can terminate on.
   - alignment: An alignment with respect to gravity a plane must have to intersect this ray.
- Returns: A raycast query configured with the specified parameters.
*/
- (ARRaycastQuery *)raycastQueryFromPoint:(CGPoint)point
                           allowingTarget:(ARRaycastTarget)target
                                alignment:(ARRaycastTargetAlignment)alignment API_AVAILABLE(ios(13.0));


/**
 Interface orientation enumeration type (from UIKit).
 */
typedef NS_ENUM(NSInteger, UIInterfaceOrientation);

/**
 Returns an affine transform for converting between normalized image coordinates and a coordinate space appropriate for rendering the camera image
 onscreen.

 Normalized image coordinates range from `(0,0)` in the upper left corner of the image to `(1,1)` in the lower right corner.

 This method creates an affine transform representing the rotation and aspect-fit crop operations necessary to adapt the camera image to the specified
 orientation and to the aspect ratio of the specified viewport. The affine transform does not scale to the viewport's pixel size.

 The ``ARFrame/capturedImage`` pixel buffer is the original image captured by the device camera, and thus not adjusted for device orientation or view
 aspect ratio.

 - Parameters:
   - orientation: The orientation intended for presenting the view.
   - viewportSize: The size, in points, of the view intended for rendering the camera image.

 - Returns: A transform matrix that converts from normalized image coordinates in the captured image to normalized image coordinates that account for
 the specified parameters.
*/
- (CGAffineTransform)displayTransformForOrientation:(UIInterfaceOrientation)orientation
                                       viewportSize:(CGSize)viewportSize
    API_DEPRECATED("Use displayTransformForViewRotationAngle:viewportSize:", ios(11.0, 27.0));

/**
 Returns a display transform for the provided viewport size and view angle.

 The display transform can be used to convert normalized points in the image-space coordinate system
 of the captured image to normalized points in the view's coordinate space. The transform provides the correct rotation
 and aspect-fill for presenting the captured image in the given view angle and size.

 The view angle, in degrees, is the clockwise rotation needed to keep the camera image level with the horizon
 (`0` LandscapeRight, `90` Portrait, `180` LandscapeLeft, `270` PortraitUpsideDown). Obtain it from
 `ARSession.viewRotationAngle`.

 - Parameters:
   - viewRotationAngle: The view rotation angle, in degrees, of the viewport.
   - viewportSize: The size of the viewport.

 - Returns: The display transform matrix.
*/
- (CGAffineTransform)displayTransformForViewRotationAngle:(CGFloat)viewRotationAngle
                                             viewportSize:(CGSize)viewportSize NS_SWIFT_NAME(displayTransform(viewRotationAngle:viewportSize:))
                                                              API_AVAILABLE(ios(27.0));


/**
 Unavailable.

 - Returns: This method is unavailable.
*/
- (instancetype)init NS_UNAVAILABLE;

/**
 Unavailable.

 - Returns: This method is unavailable.
*/
+ (instancetype)new NS_UNAVAILABLE;

@end

API_UNAVAILABLE_END

NS_ASSUME_NONNULL_END
#else
#import <ARKitCore/ARFrame.h> 
#endif // #if (defined(USE_ARKIT_PUBLIC_HEADERS) \&\& USE_ARKIT_PUBLIC_HEADERS) || !__has_include(<ARKitCore/ARFrame.h>)