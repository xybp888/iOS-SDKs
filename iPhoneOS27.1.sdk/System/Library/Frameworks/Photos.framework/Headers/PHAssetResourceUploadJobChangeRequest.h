//
//  PHAssetResourceUploadJobChangeRequest.h
//  PhotoKit
//
//  Copyright © 2025 Apple Inc. All rights reserved.
//
#import <Photos/PHChangeRequest.h>

@class PHAssetResource;
@class PHAssetResourceUploadJob;

NS_ASSUME_NONNULL_BEGIN

/// Use within an application's `com.apple.photos.background-upload` extension to create and change ``PHAssetResourceUploadJob`` records.
///
/// When the extension's principal class receives a call to `process` background uploads, it can create new ``PHAssetResourceUploadJob``s through calls to perform changes on a PHPhotoLibrary using ``PHAssetResourceUploadJobChangeRequest`` and any in-flight upload jobs can be handled by updating their state to mark them as acknowledged, or to be retried. The maximum number of jobs that can be in flight is limited to the ``PHAssetResourceUploadJob.jobLimit``.
///
/// ``PHAssetResourceUploadJobChangeRequest`` can only be created or used within a photo library change block. For details on change blocks, see ``PHPhotoLibrary``.
API_AVAILABLE(ios(26.1), macCatalyst(27.0), macos(27.0)) API_UNAVAILABLE(tvos, visionos, watchos)
@interface PHAssetResourceUploadJobChangeRequest : PHChangeRequest

/// Creates an asset resource upload job.
///
/// If the number of jobs exceeds ``PHAssetResourceUploadJob/jobLimit`` the photo library ``performChanges`` request will fail with a ``PHPhotosErrorLimitExceeded`` error.
/// To generate jobs after this limit is triggered, you must acknowledge succeeded/failed jobs, and wait for the registered/pending ones to finish uploading, which will make those jobs also succeeded/failed.
///
/// - Parameter:
///     - destination: the destination <doc://com.apple.documentation/foundation/nsurlrequest> to which this asset resource will be sent.
///     - resource: the asset resource to be uploaded.
+ (void)createJobWithDestination:(NSURLRequest *)destination resource:(PHAssetResource *)resource NS_SWIFT_NAME(createJob(destination:resource:)) API_DEPRECATED_WITH_REPLACEMENT("creationRequestForJobWithDestination:resource:", ios(26.1, 26.4));

/// Creates an asset resource upload job and returns the change request.
///
/// This method creates an upload job and returns a change request that can be used to access the placeholder
/// for the created job. Use the placeholder to obtain the local identifier before the change block completes.
///
/// If the number of jobs exceeds ``PHAssetResourceUploadJob/jobLimit`` the photo library ``performChanges`` request will fail with a ``PHPhotosErrorLimitExceeded`` error.
/// To generate jobs after this limit is triggered, you must acknowledge succeeded/failed jobs, and wait for the registered/pending ones to finish uploading, which will make those jobs also succeeded/failed.
///
/// - Parameter:
///     - destination: the destination <doc://com.apple.documentation/foundation/nsurlrequest> to which this asset resource will be sent.
///     - resource: the asset resource to be uploaded.
/// - Returns: A change request for the created job.
+ (instancetype)creationRequestForJobWithDestination:(NSURLRequest *)destination resource:(PHAssetResource *)resource NS_SWIFT_NAME(creationRequestForJob(destination:resource:)) API_AVAILABLE(ios(26.4));

/// Creates a download-only job request for the specified asset resource.
///
/// This method registers a job that requests an asset resource be downloaded from iCloud to the device
/// without uploading it to a remote server. The download operation is performed asynchronously by the
/// system over time. This is useful when you need to ensure a resource is available locally for processing.
///
/// The job will transition through the same states as upload jobs (`PHAssetResourceUploadJobStateRegistered`,
/// `PHAssetResourceUploadJobStatePending`, and eventually `PHAssetResourceUploadJobStateSucceeded` or
/// `PHAssetResourceUploadJobStateFailed`), but will only perform a download operation.
///
/// Use `fetchJobsWithAction:options:` to check the job's state. When the job reaches
/// `PHAssetResourceUploadJobStateSucceeded`, the download has completed successfully.
///
/// - Note: The system may subsequently purge the downloaded resource due to system conditions.
///
/// - Parameter resource: The asset resource to download.
/// - Returns: A change request for the created job.
+ (instancetype)creationRequestForDownloadJobWithResource:(PHAssetResource *)resource NS_SWIFT_NAME(creationRequestForDownloadJob(resource:)) API_AVAILABLE(ios(26.4));

/// A placeholder for the asset resource upload job created by this request.
///
/// The placeholder can be used to obtain the local identifier of the job that will be created when the change block completes.
@property (nonatomic, strong, readonly, nullable) PHObjectPlaceholder *placeholderForCreatedAssetResourceUploadJob;

/// Creates a request for modifying the specified upload job.
///
/// - Parameter job: a job to be modified.
+ (nullable instancetype)changeRequestForUploadJob:(nonnull PHAssetResourceUploadJob *)job;

/// Acknowledges a successful or failed job. Jobs must be acknowledged to free up space for ``PHAssetResourceUploadJob/jobLimit``.
- (void)acknowledge;

/// Retries a job that is failed, unacknowledged, and has not been retried before. Successful retries also free up space for ``PHAssetResourceUploadJob/jobLimit``.
- (void)retryWithDestination:(nullable NSURLRequest *)destination NS_SWIFT_NAME(retry(destination:));

/// Cancels an upload job that is registered or pending.
///
/// Use this method to cancel an upload job that has not yet completed. This is useful when
/// a resource is uploaded through another path (e.g., the main app) and the background
/// upload job is no longer needed, avoiding wasteful duplicate uploads.
///
/// Only jobs in the `PHAssetResourceUploadJobStateRegistered` or `PHAssetResourceUploadJobStatePending`
/// states can be cancelled. Cancelled jobs transition to the `PHAssetResourceUploadJobStateCancelled` state
/// and are automatically acknowledged.
- (void)cancel API_AVAILABLE(ios(26.4));

@end

NS_ASSUME_NONNULL_END
