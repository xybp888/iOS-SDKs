//
//  ARConfiguration.h
//  ARKit
//
//  Copyright © 2016-2017 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <AVFoundation/AVFoundation.h>

NS_ASSUME_NONNULL_BEGIN

@class ARReferenceImage;
@class ARReferenceObject;
@class ARVideoFormat;
@class ARWorldMap;

/**
 Enum constants for indicating the world alignment.
 */
API_AVAILABLE(ios(11.0))
typedef NS_ENUM(NSInteger, ARWorldAlignment) {
    /** Aligns the world with gravity that is defined by vector (0, -1, 0). */
    ARWorldAlignmentGravity,
    
    /** Aligns the world with gravity that is defined by the vector (0, -1, 0)
     and heading (w.r.t. True North) that is given by the vector (0, 0, -1). */
    ARWorldAlignmentGravityAndHeading,
    
    /** Aligns the world with the camera’s orientation. */
    ARWorldAlignmentCamera
} NS_SWIFT_NAME(ARConfiguration.WorldAlignment);


/**
 Enum constants for indicating the mode of environment texturing to run.
 */
API_AVAILABLE(ios(12.0))
typedef NS_ENUM(NSInteger, AREnvironmentTexturing) {
    /** No texture information is gathered. */
    AREnvironmentTexturingNone,
    
    /** Texture information is gathered for the environment.
     Environment textures will be generated for AREnvironmentProbes added to the session. */
    AREnvironmentTexturingManual,
    
    /** Texture information is gathered for the environment and probes automatically placed in the scene. */
    AREnvironmentTexturingAutomatic
} NS_SWIFT_NAME(ARWorldTrackingConfiguration.EnvironmentTexturing);


/**
 Option set indicating the type of planes to detect.
 */
API_AVAILABLE(ios(11.0))
typedef NS_OPTIONS(NSUInteger, ARPlaneDetection) {
    /** No plane detection is run. */
    ARPlaneDetectionNone                              = 0,
    
    /** Plane detection determines horizontal planes in the scene. */
    ARPlaneDetectionHorizontal                        = (1 << 0),
    
    /** Plane detection determines vertical planes in the scene. */
    ARPlaneDetectionVertical API_AVAILABLE(ios(11.3)) = (1 << 1)
} NS_SWIFT_NAME(ARWorldTrackingConfiguration.PlaneDetection);


/**
 An object to describe and configure the Augmented Reality techniques to be used in an ARSession.
 */
API_AVAILABLE(ios(11.0))
@interface ARConfiguration : NSObject <NSCopying>

/**
 Determines whether this device supports the ARConfiguration.
 */
@property (class, nonatomic, readonly) BOOL isSupported;

/**
 A list of supported video formats for this configuration and device.
 @discussion The first element in the list is the default format for session output.
 */
@property (class, nonatomic, readonly) NSArray<ARVideoFormat *> *supportedVideoFormats API_AVAILABLE(ios(11.3));

/**
 Video format of the session output.
 */
@property (nonatomic, strong) ARVideoFormat *videoFormat API_AVAILABLE(ios(11.3));

/**
 Determines how the coordinate system should be aligned with the world.
 @discussion The default is ARWorldAlignmentGravity.
 */
@property (nonatomic, assign) ARWorldAlignment worldAlignment;

/**
 Enable or disable light estimation.
 @discussion Enabled by default.
 */
@property (nonatomic, assign, getter=isLightEstimationEnabled) BOOL lightEstimationEnabled;

/**
 Determines whether to capture and provide audio data.
 @discussion Disabled by default.
 */
@property (nonatomic, assign) BOOL providesAudioData;

/** Unavailable */
- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end


/**
 A configuration for running world tracking.
 
 @discussion World tracking provides 6 degrees of freedom tracking of the device.
 By finding feature points in the scene, world tracking enables performing hit-tests against the frame.
 Tracking can no longer be resumed once the session is paused.
 */
API_AVAILABLE(ios(11.0))
@interface ARWorldTrackingConfiguration : ARConfiguration

/**
 Enable or disable continuous auto focus.
 @discussion Enabled by default.
 */
@property (nonatomic, assign, getter=isAutoFocusEnabled) BOOL autoFocusEnabled API_AVAILABLE(ios(11.3));

/**
 The mode of environment texturing to run.
 @discussion If set, texture information will be accumulated and updated. Adding an AREnvironmentProbeAnchor to the session
 will get the current environment texture available from that probe's perspective which can be used for lighting
 virtual objects in the scene. Defaults to AREnvironmentTexturingNone.
 */
@property (nonatomic, assign) AREnvironmentTexturing environmentTexturing API_AVAILABLE(ios(12.0));

/**
 Type of planes to detect in the scene.
 @discussion If set, new planes will continue to be detected and updated over time. Detected planes will be added to the session as
 ARPlaneAnchor objects. In the event that two planes are merged, the newer plane will be removed. Defaults to ARPlaneDetectionNone.
 */
@property (nonatomic, assign) ARPlaneDetection planeDetection;

/**
 The initial map of the physical space that world tracking will localize to and track.
 @discussion If set, the session will attempt to localize to the provided map with
 a limited tracking state until localization is successful or run is called again
 with a different (or no) initial map specified. Once localized, the map will be extended
 and can again be saved using the `getCurrentWorldMap` method on the session.
 */
@property (nonatomic, strong, nullable) ARWorldMap *initialWorldMap API_AVAILABLE(ios(12.0));

/**
 Images to detect in the scene.
 @discussion If set the session will attempt to detect the specified images. When an image is detected an ARImageAnchor will be added to the session.
 */
@property (nonatomic, copy, null_resettable) NSSet<ARReferenceImage *> *detectionImages API_AVAILABLE(ios(11.3));

/**
 Maximum number of images to track simultaneously.
 @discussion Setting the maximum number of tracked images will limit the number of images that can be tracked in a given frame.
 If more than the maximum is visible, only the images already being tracked will continue to track until tracking is lost or another image is removed.
 Images will continue to be detected regardless of images tracked. Default value is zero.
 */
@property (nonatomic, assign) NSInteger maximumNumberOfTrackedImages API_AVAILABLE(ios(12.0));

/**
 Objects to detect in the scene.
 @discussion If set the session will attempt to detect the specified objects. When an object is detected an ARObjectAnchor will be added to the session.
 */
@property (nonatomic, copy) NSSet<ARReferenceObject *> *detectionObjects API_AVAILABLE(ios(12.0));

- (instancetype)init;
+ (instancetype)new NS_SWIFT_UNAVAILABLE("Use init() instead");

@end

/**
 A configuration for running orientation tracking.
 
 @discussion Orientation tracking provides 3 degrees of freedom tracking of the device.
 */
API_AVAILABLE(ios(11.0))
@interface AROrientationTrackingConfiguration : ARConfiguration

/**
 Enable or disable continuous auto focus.
 @discussion Enabled by default.
 */
@property (nonatomic, assign, getter=isAutoFocusEnabled) BOOL autoFocusEnabled API_AVAILABLE(ios(11.3));

- (instancetype)init;
+ (instancetype)new NS_SWIFT_UNAVAILABLE("Use init() instead");

@end


/**
 A configuration for running face tracking.
 
 @discussion Face tracking uses the front facing camera to track the face in 3D providing details on the topology and expression of the face.
 A detected face will be added to the session as an ARFaceAnchor object which contains information about head pose, mesh, eye pose, and blend shape
 coefficients. If light estimation is enabled the detected face will be treated as a light probe and used to estimate the direction of incoming light.
 */
API_AVAILABLE(ios(11.0))
@interface ARFaceTrackingConfiguration : ARConfiguration

- (instancetype)init;
+ (instancetype)new NS_SWIFT_UNAVAILABLE("Use init() instead");

@end


/**
 A configuration for running image tracking.
 
 @discussion Image tracking provides 6 degrees of freedom tracking of known images. Four images may be tracked simultaneously.
 */
API_AVAILABLE(ios(12.0))
@interface ARImageTrackingConfiguration : ARConfiguration

/**
 Enable or disable continuous auto focus.
 @discussion Enabled by default.
 */
@property (nonatomic, assign, getter=isAutoFocusEnabled) BOOL autoFocusEnabled;

/**
 Images to track in the scene.
 */
@property (nonatomic, copy) NSSet<ARReferenceImage *> *trackingImages;

/**
 Maximum number of images to track simultaneously.
 @discussion Setting the maximum number of tracked images will limit the number of images that can be tracked in a given frame.
 If more than the maximum is visible, only the images already being tracked will continue to track until tracking is lost or another image is removed.
 Default value is one.
 */
@property (nonatomic, assign) NSInteger maximumNumberOfTrackedImages;

- (instancetype)init;
+ (instancetype)new NS_SWIFT_UNAVAILABLE("Use init() instead");

@end


/**
 A configuration for scanning objects.
 
 @discussion The object scanning configuration runs world tracking, capturing additional detail in order to create reference objects.
 Running object scanning will consume additional power in order to provide more detailed features.
 The createReferenceObject method can be called on the session to capture a scan of an object in the world.
 */
API_AVAILABLE(ios(12.0))
@interface ARObjectScanningConfiguration : ARConfiguration

/**
 Enable or disable continuous auto focus.
 @discussion Enabled by default.
 */
@property (nonatomic, assign, getter=isAutoFocusEnabled) BOOL autoFocusEnabled;

/**
 Type of planes to detect in the scene.
 @discussion If set, new planes will continue to be detected and updated over time. Detected planes will be added to the session as
 ARPlaneAnchor objects. In the event that two planes are merged, the newer plane will be removed. Defaults to ARPlaneDetectionNone.
 */
@property (nonatomic, assign) ARPlaneDetection planeDetection;

- (instancetype)init;
+ (instancetype)new NS_SWIFT_UNAVAILABLE("Use init() instead");

@end

NS_ASSUME_NONNULL_END
