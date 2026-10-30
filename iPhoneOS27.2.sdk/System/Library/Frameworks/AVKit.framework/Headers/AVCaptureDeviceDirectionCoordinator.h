/*
	File:  AVCaptureDeviceDirectionCoordinator.h

	Framework:  AVKit

	Copyright © 2026 Apple Inc. All rights reserved.

	To report bugs, go to:  http://developer.apple.com/bugreporter/

 */


#import <Foundation/Foundation.h>

#if TARGET_OS_MACCATALYST
#import <AVKitCore/AVKitDefines.h>
#else
#import <AVKit/AVKitDefines.h>
#endif // TARGET_OS_MACCATALYST

#import <AVFoundation/AVCaptureDevice.h>
#import <UIKit/UIView.h>

NS_ASSUME_NONNULL_BEGIN

// MARK: -

/// A descriptor of a capture device.
///
/// Represents an ``AVCaptureDevice`` and exposes the subset of its properties needed to identify the device.
API_AVAILABLE(ios(27.1), macCatalyst(27.1)) API_UNAVAILABLE(macos, tvos, visionos, watchos)
NS_SWIFT_SENDABLE
@interface AVCaptureDeviceDescriptor : NSObject

AVKIT_INIT_UNAVAILABLE

/// The type of the capture device.
///
/// The corresponding ``AVCaptureDeviceType`` of the capture device.
@property (nonatomic, readonly) AVCaptureDeviceType deviceType;

/// The media types of the capture device.
///
/// The set of ``AVMediaType`` values supported by the capture device.
@property (nonatomic, copy, readonly) NSSet<AVMediaType> *mediaTypes;

/// The position of the capture device.
///
/// The corresponding ``AVCaptureDevicePosition`` of the capture device.
@property (nonatomic, readonly) AVCaptureDevicePosition position;

/// The unique identifier of the capture device.
///
/// Matches the ``AVCaptureDevice/uniqueID`` of the capture device.
@property (nonatomic, readonly) NSString *uniqueID;

/// The localized name of the capture device.
///
/// Matches the ``AVCaptureDevice/localizedName`` of the capture device.
@property (nonatomic, readonly) NSString *localizedName;

@end

// MARK: -

/// An object containing arrays that describe the direction the camera is facing.
API_AVAILABLE(ios(27.1), macCatalyst(27.1)) API_UNAVAILABLE(macos, tvos, visionos, watchos)
NS_SWIFT_SENDABLE
@interface AVCaptureDeviceDirectionMap : NSObject

AVKIT_INIT_UNAVAILABLE

/// An array describing the cameras that are facing forward.
///
/// These cameras capture the scene in front of the display. The ``AVCaptureDeviceDescriptor``s in the array can be used to identify and obtain the corresponding ``AVCaptureDevice``. The array may be empty if no cameras are available or applicable for the current configuration.
@property (nonatomic, copy, readonly) NSArray<AVCaptureDeviceDescriptor *> *forwardFacingDeviceDescriptors;

/// An array describing the cameras that are facing backward.
///
/// These cameras capture the scene behind the display. The ``AVCaptureDeviceDescriptor``s in the array can be used to identify and obtain the corresponding ``AVCaptureDevice``. The array may be empty if no cameras are available or applicable for the current configuration.
@property (nonatomic, copy, readonly) NSArray<AVCaptureDeviceDescriptor *> *backwardFacingDeviceDescriptors;

@end

// MARK: -

/// A monitor that describes the direction a capture device faces in relation to a view.
API_AVAILABLE(ios(27.1), macCatalyst(27.1)) API_UNAVAILABLE(macos, tvos, visionos, watchos)
@interface AVCaptureDeviceDirectionCoordinator : NSObject

AVKIT_INIT_UNAVAILABLE

/// Initializes a coordinator for the given view, registering a handler to be invoked when the set of forward-facing or backward-facing video devices changes.
///
/// - Note: Initialize the coordinator only on the main thread.
///
/// - Parameter view: The ``UIView`` in relation to which the camera directions are described.
/// - Parameter deviceTypes: An array of device types you'd like the coordinator to consider.
/// - Parameter changeHandler: A block to be called when the direction of a camera on the device changes. The block receives an updated ``AVCaptureDeviceDirectionMap`` object. The handler is called on the main queue.
/// - Returns: An ``AVCaptureDeviceDirectionCoordinator`` instance.
- (instancetype)initWithView:(UIView *)view
				 deviceTypes:(NSArray<AVCaptureDeviceType> *)deviceTypes
			   changeHandler:(nullable void (^)(AVCaptureDeviceDirectionMap *deviceDirections))changeHandler;

/// The current directional state of all cameras in relation to the initialized view.
///
/// - Note: Returns an empty map until the coordinator fires its first callback.
@property (nonatomic, readonly) AVCaptureDeviceDirectionMap *deviceDirections;

@end

NS_ASSUME_NONNULL_END

