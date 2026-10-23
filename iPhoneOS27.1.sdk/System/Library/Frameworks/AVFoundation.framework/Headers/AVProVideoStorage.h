#if !__has_include(<AVFCapture/AVProVideoStorage.h>)
/*
    File:  AVProVideoStorage.h

    Framework:  AVFoundation
 
    Copyright 2026 Apple Inc. All rights reserved.
*/

#import <AVFoundation/AVFCapture.h>

NS_ASSUME_NONNULL_BEGIN

/// A reason that Pro Video Storage may be busy.
typedef NSString * AVProVideoStorageBusyReason NS_TYPED_ENUM NS_SWIFT_NAME(AVProVideoStorage.BusyReason) API_AVAILABLE(macos(27.0), ios(27.0), macCatalyst(27.0), tvos(27.0)) API_UNAVAILABLE(visionos) API_UNAVAILABLE(watchos);

/// Pro Video Storage is being created or resized.
AVF_EXPORT AVProVideoStorageBusyReason const AVProVideoStorageBusyReasonAdjustingCapacity API_AVAILABLE(macos(27.0), ios(27.0), macCatalyst(27.0), tvos(27.0)) API_UNAVAILABLE(visionos) API_UNAVAILABLE(watchos);

/// Pro Video Storage capacity is being replenished.
AVF_EXPORT AVProVideoStorageBusyReason const AVProVideoStorageBusyReasonReplenishing API_AVAILABLE(macos(27.0), ios(27.0), macCatalyst(27.0), tvos(27.0)) API_UNAVAILABLE(visionos) API_UNAVAILABLE(watchos);

/// A capture to Pro Video Storage is in progress.
AVF_EXPORT AVProVideoStorageBusyReason const AVProVideoStorageBusyReasonCapturing API_AVAILABLE(macos(27.0), ios(27.0), macCatalyst(27.0), tvos(27.0)) API_UNAVAILABLE(visionos) API_UNAVAILABLE(watchos);

#pragma mark - AVProVideoStorage

/// A class to track and manage pre-allocated storage for high data rate video capture.
///
/// `AVProVideoStorage` is a singleton that manages system-wide pre-allocated storage used during high data rate video capture
/// to ensure I/O determinism and sustain high bandwidth captures (e.g. ProRes).
API_AVAILABLE(macos(27.0), ios(27.0), macCatalyst(27.0), tvos(27.0)) API_UNAVAILABLE(visionos) API_UNAVAILABLE(watchos)
@interface AVProVideoStorage : NSObject

/// Returns the singleton instance for Pro Video Storage.
///
/// - Returns: An instance of the Pro Video Storage class if supported; otherwise, `nil`.
@property(class, readonly, nullable) AVProVideoStorage *sharedStorage;

/// Whether Pro Video Storage is supported in its current configuration.
///
/// - Returns: `YES` if the device and OS support Pro Video Storage functionality; otherwise, `NO`.
@property(class, readonly, getter=isSupported) BOOL supported;

/// Opens the Pro Video Storage UI in Settings app.
///
/// Presents system UI that allows the user to adjust pre-allocated storage capacity.
- (void)openSettings;

/// Initial size of Pro Video Storage in bytes.
///
/// The initial capacity is defined by the user via the Settings app.
///
/// - Returns: 0 if Pro Video Storage is not configured or -1 if there was a failure while extracting information from it.
@property(nonatomic, readonly) NSInteger initialCapacity;

/// Current size of Pro Video Storage in bytes.
///
/// The remaining capacity decreases as recordings are captured.
///
/// - Returns: 0 if Pro Video Storage is not configured or -1 if there was a failure while extracting information from it.
@property(nonatomic, readonly) NSInteger remainingCapacity;

/// Performs a best-effort attempt to restore Pro Video Storage to the initial capacity specified by the user in Settings app.
///
/// If there is enough readily available free space on the file system, Pro Video Storage will be resized to ``initialCapacity``.
/// Otherwise, this method will attempt to resize it near that value.
///
/// Pro Video Storage is busy when the replenish operation starts and is no longer busy when the completion handler is called.
///
/// - Parameter completionHandler:
/// The completion handler is called on an arbitrary dispatch queue when the replenish operation finishes.
/// The `remainingCapacity` parameter reflects the new size in bytes, which may be less than ``initialCapacity``.
/// If the operation fails, the `error` parameter is set and `remainingCapacity` is unchanged or -1 if there was a failure retrieving the value.
- (void)replenishCapacityWithCompletionHandler:(nullable void (^)(NSInteger remainingCapacity, NSError * _Nullable error))completionHandler;

/// Whether Pro Video Storage is busy and the associated reasons.
///
/// A non-empty set indicates that Pro Video Storage is currently being modified.
/// While this is non-empty, starting a video capture will fail with an error.
/// This property is key-value observable.
@property(nonatomic, readonly) NSSet<AVProVideoStorageBusyReason> *busyReasons;

@end

NS_ASSUME_NONNULL_END

#else
#import <AVFCapture/AVProVideoStorage.h>
#endif
