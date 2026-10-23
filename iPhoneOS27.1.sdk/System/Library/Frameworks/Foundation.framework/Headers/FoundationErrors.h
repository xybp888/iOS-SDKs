/*	FoundationErrors.h
	Copyright (c) 2004-2019, Apple Inc. All rights reserved.
*/

#import <Foundation/NSObject.h>
#import <Foundation/NSError.h>


/* NSError codes in NSCocoaErrorDomain. Note that other frameworks (such as AppKit and CoreData) also provide additional NSCocoaErrorDomain error codes.
*/
NS_ERROR_ENUM(NSCocoaErrorDomain) {
    // File system and file I/O related errors, with NSFilePathErrorKey or NSURLErrorKey containing path or URL
    /// A filesystem operation was attempted on a non-existent file.
    NSFileNoSuchFileError = 4,
    /// The file could not be locked.
    NSFileLockingError = 255,
    /// Read error, for unknown reasons.
    NSFileReadUnknownError = 256,
    /// Could not read because of a permission problem.
    NSFileReadNoPermissionError = 257,
    /// Could not read because of an invalid file name.
    NSFileReadInvalidFileNameError = 258,
    /// Could not read because of a corrupted file, bad format, or similar reason.
    NSFileReadCorruptFileError = 259,
    /// Could not read because no such file was found.
    NSFileReadNoSuchFileError = 260,
    /// Could not read because the string encoding was not applicable.
    ///
    /// Access the bad encoding from the `userInfo` dictionary using the ``NSStringEncodingErrorKey`` key.
    NSFileReadInapplicableStringEncodingError = 261,
    /// Could not read because the specified URL scheme is unsupported.
    NSFileReadUnsupportedSchemeError = 262,
    /// Could not read because the specified file was too large.
    NSFileReadTooLargeError API_AVAILABLE(macos(10.5), ios(2.0), watchos(2.0), tvos(9.0)) = 263,
    /// Could not read because the string encoding of the file contents could not be determined.
    NSFileReadUnknownStringEncodingError API_AVAILABLE(macos(10.5), ios(2.0), watchos(2.0), tvos(9.0)) = 264,
    /// Write error, for unknown reasons.
    NSFileWriteUnknownError = 512,
    /// Could not write because of a permission problem.
    NSFileWriteNoPermissionError = 513,
    /// Could not write because of an invalid file name.
    NSFileWriteInvalidFileNameError = 514,
    /// Could not perform an operation because the destination file already exists.
    ///
    /// This error can be produced by the ``NSFileManager`` class's copy, move, and link methods.
    NSFileWriteFileExistsError API_AVAILABLE(macos(10.7), ios(5.0), watchos(2.0), tvos(9.0)) = 516,
    /// Could not write because the string encoding was not applicable.
    ///
    /// Access the bad encoding from the `userInfo` dictionary using the ``NSStringEncodingErrorKey`` key.
    NSFileWriteInapplicableStringEncodingError = 517,
    /// Could not write because the specified URL scheme is unsupported.
    NSFileWriteUnsupportedSchemeError = 518,
    /// Could not write because of a lack of disk space.
    NSFileWriteOutOfSpaceError = 640,
    /// Could not write because the volume is read-only.
    NSFileWriteVolumeReadOnlyError API_AVAILABLE(macos(10.6), ios(4.0), watchos(2.0), tvos(9.0)) = 642,

    // NSFileManager unmount errors
    /// The volume could not be unmounted (reason unknown).
    NSFileManagerUnmountUnknownError API_AVAILABLE(macos(10.11)) API_UNAVAILABLE(ios, watchos, tvos) = 768,
    /// The volume could not be unmounted because it is in use.
    NSFileManagerUnmountBusyError API_AVAILABLE(macos(10.11)) API_UNAVAILABLE(ios, watchos, tvos) = 769,

    // Other errors
    /// A key-value coding validation error.
    NSKeyValueValidationError = 1024,
    /// A formatter could not generate a string for an object, or parse a string into an object.
    NSFormattingError = 2048,
    /// The user canceled the operation (for example, by pressing Command-period).
    ///
    /// This code is for errors that do not require a dialog displayed and might be candidates for special-casing.
    NSUserCancelledError = 3072,
    /// The feature is not supported, because the file system lacks the feature, or required libraries are missing, or other similar reasons.
    ///
    /// For example, some volumes may not support a Trash folder, so these methods will report failure by returning `false` or `nil` and an ``NSError`` with ``NSFeatureUnsupportedError``.
    NSFeatureUnsupportedError API_AVAILABLE(macos(10.8), ios(6.0), watchos(2.0), tvos(9.0)) = 3328,

    // Executable loading errors
    /// The executable type is not loadable in the current process.
    NSExecutableNotLoadableError API_AVAILABLE(macos(10.5), ios(2.0), watchos(2.0), tvos(9.0)) = 3584,
    /// The executable does not provide an architecture compatible with the current process.
    NSExecutableArchitectureMismatchError API_AVAILABLE(macos(10.5), ios(2.0), watchos(2.0), tvos(9.0)) = 3585,
    /// The executable has Objective-C runtime information incompatible with the current process.
    NSExecutableRuntimeMismatchError API_AVAILABLE(macos(10.5), ios(2.0), watchos(2.0), tvos(9.0)) = 3586,
    /// The executable cannot be loaded for an otherwise-unspecified reason.
    ///
    /// This error covers situations such as an error caused by a library the executable depends on.
    NSExecutableLoadError API_AVAILABLE(macos(10.5), ios(2.0), watchos(2.0), tvos(9.0)) = 3587,
    /// The executable failed due to linking issues.
    NSExecutableLinkError API_AVAILABLE(macos(10.5), ios(2.0), watchos(2.0), tvos(9.0)) = 3588,

    // Inclusive error range definitions, for checking future error codes
    /// The start of the range of error codes reserved for file errors.
    NSFileErrorMinimum = 0,
    /// The end of the range of error codes reserved for file errors.
    NSFileErrorMaximum = 1023,

    /// The start of the range of error codes reserved for validation errors.
    NSValidationErrorMinimum = 1024,
    /// The end of the range of error codes reserved for validation errors.
    NSValidationErrorMaximum = 2047,

    /// The beginning of the range of error codes reserved for errors related to executable files.
    NSExecutableErrorMinimum API_AVAILABLE(macos(10.5), ios(2.0), watchos(2.0), tvos(9.0)) = 3584,
    /// The end of the range of error codes reserved for errors related to executable files.
    NSExecutableErrorMaximum API_AVAILABLE(macos(10.5), ios(2.0), watchos(2.0), tvos(9.0)) = 3839,

    /// The start of the range of error codes reserved for formatting errors.
    NSFormattingErrorMinimum = 2048,
    /// The end of the range of error codes reserved for formatting errors.
    NSFormattingErrorMaximum = 2559,

    /// Parsing of the property list failed.
    NSPropertyListReadCorruptError API_AVAILABLE(macos(10.6), ios(4.0), watchos(2.0), tvos(9.0)) = 3840,
    /// The version number of the property list could not be determined.
    NSPropertyListReadUnknownVersionError API_AVAILABLE(macos(10.6), ios(4.0), watchos(2.0), tvos(9.0)) = 3841,
    /// Reading of the property list failed.
    NSPropertyListReadStreamError API_AVAILABLE(macos(10.6), ios(4.0), watchos(2.0), tvos(9.0)) = 3842,
    /// Writing to the property list failed.
    NSPropertyListWriteStreamError API_AVAILABLE(macos(10.6), ios(4.0), watchos(2.0), tvos(9.0)) = 3851,
    /// Writing failed because of an invalid property list object, or an invalid property list type was specified.
    NSPropertyListWriteInvalidError API_AVAILABLE(macos(10.10), ios(8.0), watchos(2.0), tvos(9.0)) = 3852,

    /// The start of the range of error codes reserved for property list errors.
    NSPropertyListErrorMinimum API_AVAILABLE(macos(10.6), ios(4.0), watchos(2.0), tvos(9.0)) = 3840,
    /// The end of the range of error codes reserved for property list errors.
    NSPropertyListErrorMaximum API_AVAILABLE(macos(10.6), ios(4.0), watchos(2.0), tvos(9.0)) = 4095,

    /// The XPC connection was interrupted.
    NSXPCConnectionInterrupted API_AVAILABLE(macos(10.8), ios(6.0), watchos(2.0), tvos(9.0)) = 4097,
    /// The XPC connection was invalid.
    NSXPCConnectionInvalid API_AVAILABLE(macos(10.8), ios(6.0), watchos(2.0), tvos(9.0)) = 4099,
    /// The XPC connection reply was invalid.
    NSXPCConnectionReplyInvalid API_AVAILABLE(macos(10.8), ios(6.0), watchos(2.0), tvos(9.0)) = 4101,
    /// A code-signing requirement check failed.
    ///
    /// This error represents a failure to meet the requirement set by a call to ``NSXPCConnection``'s ``NSXPCConnection/setCodeSigningRequirement:`` method, or ``NSXPCListener``'s ``NSXPCListener/setConnectionCodeSigningRequirement:`` method.
    NSXPCConnectionCodeSigningRequirementFailure API_AVAILABLE(macos(13.0), ios(16.0), tvos(16.0), watchos(9.0)) = 4102,

    /// The lower bounds of XPC connection error code values.
    ///
    /// All XPC error codes have values between ``NSXPCConnectionErrorMinimum`` and ``NSXPCConnectionErrorMaximum``, exclusive. This constant does not correspond to any particular error.
    NSXPCConnectionErrorMinimum API_AVAILABLE(macos(10.8), ios(6.0), watchos(2.0), tvos(9.0)) = 4096,
    /// The upper bounds of XPC connection error code values.
    ///
    /// All XPC error codes have values between ``NSXPCConnectionErrorMinimum`` and ``NSXPCConnectionErrorMaximum``, exclusive. This constant does not correspond to any particular error.
    NSXPCConnectionErrorMaximum API_AVAILABLE(macos(10.8), ios(6.0), watchos(2.0), tvos(9.0)) = 4224,

    /// The item has not been uploaded to iCloud by another device yet.
    ///
    /// When this error occurs, you do not need to ask the system to start downloading the item. The system will download the item as soon as it can. If you want to know when the item becomes available, use an ``NSMetadataQuery`` object to monitor changes to the file's URL.
    NSUbiquitousFileUnavailableError API_AVAILABLE(macos(10.9), ios(7.0), watchos(2.0), tvos(9.0)) = 4353,
    /// The item could not be uploaded to iCloud because it would make the account go over its quota.
    NSUbiquitousFileNotUploadedDueToQuotaError API_AVAILABLE(macos(10.9), ios(7.0), watchos(2.0), tvos(9.0)) = 4354,
    /// Connecting to the iCloud servers failed.
    NSUbiquitousFileUbiquityServerNotAvailable API_AVAILABLE(macos(10.9), ios(7.0), watchos(2.0), tvos(9.0)) = 4355,

    /// The minimum error code value that represents an iCloud error.
    NSUbiquitousFileErrorMinimum API_AVAILABLE(macos(10.9), ios(7.0), watchos(2.0), tvos(9.0)) = 4352,
    /// The maximum error code value that represents an iCloud error.
    NSUbiquitousFileErrorMaximum API_AVAILABLE(macos(10.9), ios(7.0), watchos(2.0), tvos(9.0)) = 4607,

    /// The data for the user activity wasn't available.
    ///
    /// This error can occur if the remote device became unavailable.
    NSUserActivityHandoffFailedError API_AVAILABLE(macos(10.10), ios(8.0), watchos(2.0), tvos(9.0)) = 4608,
    /// The user activity could not be continued because a required connection was not available.
    NSUserActivityConnectionUnavailableError API_AVAILABLE(macos(10.10), ios(8.0), watchos(2.0), tvos(9.0)) = 4609,
    /// The remote application failed to send data within the specified time.
    NSUserActivityRemoteApplicationTimedOutError API_AVAILABLE(macos(10.10), ios(8.0), watchos(2.0), tvos(9.0)) = 4610,
    /// The user activity's `userInfo` dictionary was too large to receive.
    NSUserActivityHandoffUserInfoTooLargeError API_AVAILABLE(macos(10.10), ios(8.0), watchos(2.0), tvos(9.0)) = 4611,

    /// The start of the range of error codes reserved for user activity errors.
    NSUserActivityErrorMinimum API_AVAILABLE(macos(10.10), ios(8.0), watchos(2.0), tvos(9.0)) = 4608,
    /// The end of the range of error codes reserved for user activity errors.
    NSUserActivityErrorMaximum API_AVAILABLE(macos(10.10), ios(8.0), watchos(2.0), tvos(9.0)) = 4863,

    /// Decoding failed due to corrupt data.
    NSCoderReadCorruptError API_AVAILABLE(macos(10.11), ios(9.0), watchos(2.0), tvos(9.0)) = 4864,
    /// The requested data was not found.
    NSCoderValueNotFoundError API_AVAILABLE(macos(10.11), ios(9.0), watchos(2.0), tvos(9.0)) = 4865,
    /// Data was not valid to encode.
    NSCoderInvalidValueError API_AVAILABLE(macos(10.13), ios(11.0), watchos(4.0), tvos(11.0)) = 4866,
    /// The start of the range of error codes reserved for coder errors.
    NSCoderErrorMinimum API_AVAILABLE(macos(10.11), ios(9.0), watchos(2.0), tvos(9.0)) = 4864,
    /// The end of the range of error codes reserved for coder errors.
    NSCoderErrorMaximum API_AVAILABLE(macos(10.11), ios(9.0), watchos(2.0), tvos(9.0)) = 4991,

    /// The start of the range of error codes reserved for bundle errors.
    NSBundleErrorMinimum API_AVAILABLE(macos(10.11), ios(9.0), watchos(2.0), tvos(9.0)) = 4992,
    /// The end of the range of error codes reserved for bundle errors.
    NSBundleErrorMaximum API_AVAILABLE(macos(10.11), ios(9.0), watchos(2.0), tvos(9.0)) = 5119,

    /// Insufficient space available to download the requested On Demand Resources.
    NSBundleOnDemandResourceOutOfSpaceError API_AVAILABLE(macos(10.11), ios(9.0), watchos(2.0), tvos(9.0)) = 4992,
    /// The application exceeded the amount of On Demand Resources content in use at one time.
    NSBundleOnDemandResourceExceededMaximumSizeError API_AVAILABLE(macos(10.11), ios(9.0), watchos(2.0), tvos(9.0)) = 4993,
    /// The application specified a tag that the system could not find in the application tag manifest.
    NSBundleOnDemandResourceInvalidTagError API_AVAILABLE(macos(10.11), ios(9.0), watchos(2.0), tvos(9.0)) = 4994,

    /// Sharing failed due to a network failure.
    NSCloudSharingNetworkFailureError API_AVAILABLE(macosx(10.12), ios(10.0)) API_UNAVAILABLE(watchos, tvos) = 5120,
    /// The user doesn't have enough storage space available to share the requested items.
    NSCloudSharingQuotaExceededError API_AVAILABLE(macosx(10.12), ios(10.0)) API_UNAVAILABLE(watchos, tvos) = 5121,
    /// Additional participants could not be added to the share because the limit was reached.
    NSCloudSharingTooManyParticipantsError API_AVAILABLE(macosx(10.12), ios(10.0)) API_UNAVAILABLE(watchos, tvos) = 5122,
    /// A conflict occurred during an attempt to save changes.
    ///
    /// This error occurs when a conflict is detected while trying to save changes to the `CKShare` or root `CKRecord`. Respond to this error by first fetching the server's changes to the records, then either handle the conflict manually or present it, which will instruct the user to try the operation again.
    NSCloudSharingConflictError API_AVAILABLE(macosx(10.12), ios(10.0)) API_UNAVAILABLE(watchos, tvos) = 5123,
    /// The current user doesn't have permission to perform the requested actions.
    NSCloudSharingNoPermissionError API_AVAILABLE(macosx(10.12), ios(10.0)) API_UNAVAILABLE(watchos, tvos) = 5124,
    /// An otherwise unspecified cloud-sharing error occurred.
    ///
    /// For CloudKit sharing, use the ``NSUnderlyingErrorKey``, whose value is a `CKErrorDomain` error, to discover the specific error. Refer to the CloudKit documentation for the proper response to these errors.
    NSCloudSharingOtherError API_AVAILABLE(macosx(10.12), ios(10.0)) API_UNAVAILABLE(watchos, tvos) = 5375,

    /// The start of the range of error codes reserved for cloud sharing errors.
    NSCloudSharingErrorMinimum API_AVAILABLE(macosx(10.12), ios(10.0)) API_UNAVAILABLE(watchos, tvos) = 5120,
    /// The end of the range of error codes reserved for cloud sharing errors.
    NSCloudSharingErrorMaximum API_AVAILABLE(macosx(10.12), ios(10.0)) API_UNAVAILABLE(watchos, tvos) = 5375,

    /// An error code value that indicates a failure to compress data using the provided algorithm.
    NSCompressionFailedError API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0)) = 5376,
    /// An error code value that indicates a failure to decompress data using the provided algorithm.
    NSDecompressionFailedError API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0)) = 5377,

    /// The start of the range of error codes reserved for compression errors.
    NSCompressionErrorMinimum API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0)) = 5376,
    /// The end of the range of error codes reserved for compression errors.
    NSCompressionErrorMaximum API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0)) = 5503,
};

