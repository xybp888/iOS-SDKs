#if !__has_include(<AVFCapture/AVCaptureAncillaryDataEncoder.h>)
/*
	File:  AVCaptureAncillaryDataEncoder.h
 
	Framework:  AVFoundation
 
	Copyright 2025 Apple Inc. All rights reserved.
*/

#import <AVFoundation/AVBase.h>
#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/// # AVCaptureAncillaryDataUserKey string constants
///
/// Clients may use an AVCaptureAncillaryDataUserKey to inspect the ``AVCaptureAncillaryDataEncoder/currentUserDefinedAncillaryData``.
typedef NSString * AVCaptureAncillaryDataUserKey NS_TYPED_ENUM API_AVAILABLE(macos(27.0), ios(27.0), macCatalyst(27.0), tvos(27.0)) API_UNAVAILABLE(visionos) API_UNAVAILABLE(watchos);

/// An AVCaptureAncillaryDataEncoder key corresponding with the optional RDD18 user defined metadata Instance UID
///
/// Clients may set the Instance UID with ``AVCaptureAncillaryDataEncoder/setUserInstanceUID:userUdamVersion:``
AVF_EXPORT AVCaptureAncillaryDataUserKey const AVCaptureAncillaryDataUserKeyRDD18InstanceUID API_AVAILABLE(macos(27.0), ios(27.0), macCatalyst(27.0), tvos(27.0)) API_UNAVAILABLE(visionos) API_UNAVAILABLE(watchos);

/// An AVCaptureAncillaryDataEncoder key corresponding with the optional RDD18 user defined metadata UDAM Set Version
///
/// Clients may set the UDAM Set Version with ``AVCaptureAncillaryDataEncoder/setUserInstanceUID:userUdamVersion:``
AVF_EXPORT AVCaptureAncillaryDataUserKey const AVCaptureAncillaryDataUserKeyRDD18UDAMSetVersion API_AVAILABLE(macos(27.0), ios(27.0), macCatalyst(27.0), tvos(27.0)) API_UNAVAILABLE(visionos) API_UNAVAILABLE(watchos);

/// An AVCaptureAncillaryDataEncoder key corresponding with RDD18 user defined metadata
///
/// Clients may inspect the user metadata with ``AVCaptureAncillaryDataEncoder\currentUserDefinedAncillaryData`` and set it with ``AVCaptureAncillaryDataEncoder\setRDD18AncillaryData:forTag:error:`` ``AVCaptureAncillaryDataEncoder\setRDD18AncillaryDataString:forTag:error:`` or remove it with ``AVCaptureAncillaryDataEncoder\removeRDD18AncillaryDataForTag:``
AVF_EXPORT AVCaptureAncillaryDataUserKey const AVCaptureAncillaryDataUserKeyRDD18UserItems API_AVAILABLE(macos(27.0), ios(27.0), macCatalyst(27.0), tvos(27.0)) API_UNAVAILABLE(visionos) API_UNAVAILABLE(watchos);

/// ``AVCaptureAncillaryDataEncoder`` is a class off of ``AVCaptureBroadcastVideoOutput`` that provides an interface for encoding capture time ancillary to accompany the  broadcating video.
///
/// ## Topics
/// ### Creating an Ancillary Data Encoder
/// - Done automatically with ``AVCaptureBroadcastVideoOutput``
///
/// ### Managing the user definded data
/// - ``setUserInstanceUID:userUdamVersion:``
/// - ``setRDD18AncillaryData:forTag:error:``
/// - ``setRDD18AncillaryDataString:forTag:error:``
/// - ``removeRDD18AncillaryDataForTag:``

///
/// ### inspecting the user defined data
/// - ``currentUserDefinedAncillaryData``
///
/// ## See Also
/// - ``AVCaptureBroadcastVideoOutput``

API_AVAILABLE(macos(27.0), ios(27.0), macCatalyst(27.0), tvos(27.0)) API_UNAVAILABLE(visionos) API_UNAVAILABLE(watchos)
@interface AVCaptureAncillaryDataEncoder: NSObject

AV_INIT_UNAVAILABLE

/// Indicates whether ancillary data should be encoded and transmitted.
///
/// This property controls whether ancillary data is encoded and sent along with video buffers in AVCaptureBroadcastVideoOutput.
/// Default value is `true`.
@property (nonatomic, getter=isEnabled) BOOL enabled;

/// This is a representation of the user defined anacillary data.
///
/// Using SMPTE 291 and SMPTE RDD 18 standards for user-defined data, this property specifies the user-defined ancillary data to be sent with every frame in ``AVCaptureBroadcastVideoOutput``.  The dictionary will contain a NSUUID the ``AVCaptureAncillaryDataUserKeyRDD18InstanceUID`` key, a uint16_t for the ``AVCaptureAncillaryDataUserKeyRDD18UDAMSetVersion`` key and a dictionary for the ``AVCaptureAncillaryDataUserKeyRDD18UserItems``. The ``AVCaptureAncillaryDataUserKeyRDD18UserItems`` will contain keys of the user tag and with the corresponding values.
///
/// To update the data please see the following methods:
/// - ``setUserInstanceUID:userUdamVersion:`` will update the ``AVCaptureAncillaryDataUserKeyRDD18InstanceUID`` and ``AVCaptureAncillaryDataUserKeyRDD18UDAMSetVersion`` keys
/// - ``setRDD18AncillaryData:forTag:error:``  will update the ``AVCaptureAncillaryDataUserKeyRDD18UserItems`` key
/// - ``setRDD18AncillaryDataString:forTag:error:`` will update the ``AVCaptureAncillaryDataUserKeyRDD18UserItems`` key
@property (nonatomic, readonly) NSDictionary<AVCaptureAncillaryDataUserKey, id>  *currentUserDefinedAncillaryData;

/// Allows users to track how much data in bytes can be added to the userDefinedAncillaryData.
///
/// Using SMPTE 291 and SMPTE RDD 18 standards for ancillary data, this property specifies max size in bytes for the user defined portion of that data
@property (nonatomic, readonly) int16_t userDefinedAncillaryDataSizeRemaining;

/// Set the UID and Version number for the user data.
///
/// Allows the user to set the instance and version of the ancillary data.
///
/// - Parameter uuid: The UUID for the SMPTE RDD 18 ancillary data instance
/// - Parameter version: The SMPTE RDD 18 User Defined Acquisition Metadata (UDAM) Set Version
- (void)setUserInstanceUID:(NSUUID *)uuid forUserUDAMVersion:(NSNumber *)version;

/// Allows the user to add their own data to be encoded and transmitted using SMPTE RDD 18 standards.
///
/// - Parameters:
///   - data: The data to be encoded and transmitted
///   - tag: The SMPTE RDD 18 tag with value between 0xE011 and 0xFFFF or valid tags definded in SMPTE RDD 18:2021
///   - error: Error if the data cannot be added
- (BOOL)setRDD18AncillaryData:(NSData *)data forTag:(uint16_t)tag error:(NSError **)error;

/// Allows the user to add their own string to be encoded as data and transmitted using SMPTE RDD 18 standards.
///
/// - Parameters:
///   - string: The string to be encoded as data and transmitted
///   - tag: The SMPTE RDD 18 tag with value between 0xE011 and 0xFFFF or valid tags definded in SMPTE RDD 18:2021
///   - error: Error if the data cannot be added
- (BOOL)setRDD18AncillaryDataString:(NSString *)string forTag:(uint16_t)tag error:(NSError **)error;

/// Allows the user to remove the ancillary data associated with the tag.
///
/// - Parameters:
///   - tag: The SMPTE RDD 18 tag with, value between 0xE011 and 0xFFFF or valid tags definded in SMPTE RDD 18:2021, for the data to be removed
- (void)removeRDD18AncillaryDataForTag:(uint16_t)tag;

@end

NS_ASSUME_NONNULL_END

#else
#import <AVFCapture/AVCaptureAncillaryDataEncoder.h>
#endif
