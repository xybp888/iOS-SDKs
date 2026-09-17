/*	
    NSURLError.h
    Copyright (c) 2003-2019, Apple Inc. All rights reserved.
    
    Public header file.
*/

#import <TargetConditionals.h>

#if TARGET_OS_IPHONE
#if __has_include(<CFNetwork/CFNetwork.h>)
#import <CFNetwork/CFNetwork.h>
#endif
#else
#import <CoreServices/CoreServices.h>
#endif

#import <Foundation/NSObjCRuntime.h>
#import <Foundation/NSError.h>

@class NSString;

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

/// URL loading system errors.
FOUNDATION_EXPORT NSErrorDomain const NSURLErrorDomain;

/// The `NSError` userInfo dictionary key used to store and retrieve the URL which caused a load to fail.
///
/// The corresponding value is an ``NSURL`` instance.
FOUNDATION_EXPORT NSString * const NSURLErrorFailingURLErrorKey API_AVAILABLE(macos(10.6), ios(4.0), watchos(2.0), tvos(9.0));

/// The `NSError` userInfo dictionary key used to store and retrieve the `NSString` for the URL which caused a load to fail.
///
/// This constant supersedes ``NSErrorFailingURLStringKey``, which was deprecated starting in macOS 10.6. Both constants refer to the same value for backward-compatibility, but this symbol name has a better prefix.
FOUNDATION_EXPORT NSString * const NSURLErrorFailingURLStringErrorKey API_DEPRECATED("Use NSURLErrorFailingURLErrorKey instead", macos(10.6,15.4), ios(4.0,18.4), watchos(2.0,11.4), tvos(9.0,18.4), visionos(1.0,2.4));

/// The `NSError` userInfo dictionary key used to store and retrieve the `NSString` for the URL which caused a load to fail.
///
/// This constant is deprecated and superseded by ``NSURLErrorFailingURLStringErrorKey``.
FOUNDATION_EXPORT NSString * const NSErrorFailingURLStringKey API_DEPRECATED("Use NSURLErrorFailingURLErrorKey instead", macos(10.0,10.6), ios(2.0,4.0), watchos(2.0,2.0), tvos(9.0,9.0));

/// The `NSError` userInfo dictionary key used to store and retrieve the `SecTrustRef` object representing the state of a failed SSL handshake.
FOUNDATION_EXPORT NSString * const NSURLErrorFailingURLPeerTrustErrorKey API_AVAILABLE(macos(10.6), ios(4.0), watchos(2.0), tvos(9.0));

/// The `NSError` userInfo dictionary key used to store and retrieve the `NSNumber` corresponding to the reason why a background `NSURLSessionTask` was cancelled.
FOUNDATION_EXPORT NSString * const NSURLErrorBackgroundTaskCancelledReasonKey API_AVAILABLE(macos(10.10), ios(8.0), watchos(2.0), tvos(9.0));

/// Constants used by `NSError` to indicate why a background `NSURLSessionTask` was cancelled.
NS_ENUM(NSInteger)
{
    /// The user force-quit the application.
    NSURLErrorCancelledReasonUserForceQuitApplication =    0,
    /// The system disabled background updates.
    NSURLErrorCancelledReasonBackgroundUpdatesDisabled =   1,
    /// The system did not have sufficient resources to complete the operation.
    NSURLErrorCancelledReasonInsufficientSystemResources API_AVAILABLE(macos(10.10), ios(8.0), watchos(2.0), tvos(9.0)) = 2,

} API_AVAILABLE(macos(10.10), ios(7.0), watchos(2.0), tvos(9.0));

/// The `NSError` userInfo key for the `NSNumber` corresponding to the reason why the network is unavailable when the task failed due to unsatisfiable network constraints.
///
/// See ``NSURLErrorNetworkUnavailableReason`` for possible values.
FOUNDATION_EXPORT NSErrorUserInfoKey const NSURLErrorNetworkUnavailableReasonKey API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0));

/// An enumeration of reasons why a task couldn't satisfy networking constraints.
///
/// For example, if the ``URLSessionConfiguration`` property `allowsExpensiveNetworkAccess` was set to `NO` and the only interfaces available were marked as expensive, then the task would fail with a ``NSURLErrorNotConnectedToInternet`` error and the `userInfo` dictionary would contain the value ``NSURLErrorNetworkUnavailableReasonExpensive`` for the key ``NSURLErrorNetworkUnavailableReasonKey``.
///
/// The network may be unavailable due to restrictions placed on the ``URLSessionConfiguration``, such as ``URLSessionConfiguration/allowsConstrainedNetworkAccess``, ``URLSessionConfiguration/allowsExpensiveNetworkAccess`` and ``URLSessionConfiguration/allowsCellularAccess``.
typedef NS_ENUM(NSInteger, NSURLErrorNetworkUnavailableReason)
{
    /// The network is unavailable because the cellular interface is not available.
    NSURLErrorNetworkUnavailableReasonCellular =    0,
    /// The network is unavailable because the expensive interface is not available.
    NSURLErrorNetworkUnavailableReasonExpensive =   1,
    /// The network is unavailable because the constrained interface is not available.
    NSURLErrorNetworkUnavailableReasonConstrained = 2,
    /// The network is unavailable because the ultra-constrained interface is not available.
    NSURLErrorNetworkUnavailableReasonUltraConstrained API_AVAILABLE(macos(26.1), ios(26.1), watchos(26.1), tvos(26.1), visionos(26.1)) = 3,
} API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0));

/// Constants used by `NSError` to indicate errors in the URL domain.
NS_ERROR_ENUM(NSURLErrorDomain)
{
    /// The URL Loading System encountered an error that it can't interpret.
    ///
    /// This can occur when an error originates from a lower level framework or library. Whenever this error code is received, it is a bug, and should be reported to Apple.
    NSURLErrorUnknown = 			-1,
    /// An asynchronous load has been canceled.
    ///
    /// `NSURLSession` sends this error to its delegate when a task is cancelled.
    NSURLErrorCancelled = 			-999,
    /// A malformed URL prevented a URL request from being initiated.
    NSURLErrorBadURL = 				-1000,
    /// An asynchronous operation timed out.
    ///
    /// ``URLSession`` sends this error to its delegate when the ``NSURLRequest/timeoutInterval`` of an ``NSURLRequest`` expires before a load can complete.
    NSURLErrorTimedOut = 			-1001,
    /// A properly formed URL couldn't be handled by the framework.
    ///
    /// The most likely cause is that there is no available protocol handler for the URL.
    NSURLErrorUnsupportedURL = 			-1002,
    /// The host name for a URL couldn't be resolved.
    NSURLErrorCannotFindHost = 			-1003,
    /// An attempt to connect to a host failed.
    ///
    /// This can occur when a host name resolves, but the host is down or may not be accepting connections on a certain port.
    NSURLErrorCannotConnectToHost = 		-1004,
    /// A client or server connection was severed in the middle of an in-progress load.
    NSURLErrorNetworkConnectionLost = 		-1005,
    /// The host address couldn't be found via DNS lookup.
    ///
    /// This error code is no longer used. You should expect to handle ``NSURLErrorCannotFindHost`` instead.
    NSURLErrorDNSLookupFailed = 		-1006,
    /// A redirect loop was detected or the threshold for number of allowable redirects was exceeded (currently 16).
    NSURLErrorHTTPTooManyRedirects = 		-1007,
    /// A requested resource couldn't be retrieved.
    ///
    /// This error can indicate a file-not-found situation, or decoding problems that prevent data from being processed correctly.
    NSURLErrorResourceUnavailable = 		-1008,
    /// A network resource was requested, but an internet connection has not been established and can't be established automatically.
    ///
    /// This error occurs when the connection can't be established due to a lack of connectivity or because the user chooses not to make a network connection automatically.
    NSURLErrorNotConnectedToInternet = 		-1009,
    /// A redirect was specified by way of server response code, but the server didn't accompany this code with a redirect URL.
    NSURLErrorRedirectToNonExistentLocation = 	-1010,
    /// The URL Loading System received bad data from the server.
    ///
    /// This is equivalent to the "500 Server Error" message sent by HTTP servers.
    NSURLErrorBadServerResponse = 		-1011,
    /// An asynchronous request for authentication has been canceled by the user.
    ///
    /// This is typically incurred by clicking a "Cancel" button in a username/password dialog, rather than the user making an attempt to authenticate.
    NSURLErrorUserCancelledAuthentication = 	-1012,
    /// Authentication was required to access a resource.
    NSURLErrorUserAuthenticationRequired = 	-1013,
    /// A server reported that a URL has a non-zero content length, but terminated the network connection gracefully without sending any data.
    NSURLErrorZeroByteResource = 		-1014,
    /// Content data received during a connection request couldn't be decoded for a known content encoding.
    NSURLErrorCannotDecodeRawData =             -1015,
    /// Content data received during a connection request had an unknown content encoding.
    NSURLErrorCannotDecodeContentData =         -1016,
    /// A response to a connection request couldn't be parsed.
    NSURLErrorCannotParseResponse =             -1017,
    /// App Transport Security disallowed a connection because there is no secure network connection.
    ///
    /// Starting in iOS 9.0 and macOS 10.11, App Transport Security (ATS) is enabled by default for connections created by ``URLSession``. ATS requires the use of best practice secure protocols in HTTPS.
    NSURLErrorAppTransportSecurityRequiresSecureConnection API_AVAILABLE(macos(10.11), ios(9.0), watchos(2.0), tvos(9.0)) = -1022,
    /// The specified file doesn't exist.
    NSURLErrorFileDoesNotExist = 		-1100,
    /// A request for an FTP file resulted in the server responding that the file is not a plain file, but a directory.
    NSURLErrorFileIsDirectory = 		-1101,
    /// A resource couldn't be read because of insufficient permissions.
    NSURLErrorNoPermissionsToReadFile = 	-1102,
    /// The length of the resource data exceeded the maximum allowed.
    NSURLErrorDataLengthExceedsMaximum API_AVAILABLE(macos(10.5), ios(2.0), watchos(2.0), tvos(9.0)) =	-1103,
    /// An internal file operation failed.
    ///
    /// This error is never sent to third-party apps.
    NSURLErrorFileOutsideSafeArea API_AVAILABLE(macos(10.12.4), ios(10.3), watchos(3.2), tvos(10.2)) = -1104,

    // SSL errors
    /// An attempt to establish a secure connection failed for reasons that can't be expressed more specifically.
    NSURLErrorSecureConnectionFailed = 		-1200,
    /// A server certificate is expired, or is not yet valid.
    NSURLErrorServerCertificateHasBadDate = 	-1201,
    /// A server certificate was signed by a root server that isn't trusted.
    NSURLErrorServerCertificateUntrusted = 	-1202,
    /// A server certificate wasn't signed by any root server.
    NSURLErrorServerCertificateHasUnknownRoot = -1203,
    /// A server certificate isn't valid yet.
    NSURLErrorServerCertificateNotYetValid = 	-1204,
    /// A server certificate was rejected.
    NSURLErrorClientCertificateRejected = 	-1205,
    /// A client certificate was required to authenticate an SSL connection during a connection request.
    NSURLErrorClientCertificateRequired =	-1206,
    /// A specific request to load an item only from the cache couldn't be satisfied.
    ///
    /// This error is sent when the task needs to load from the network, but is blocked from doing so by the "load only from cache" directive.
    NSURLErrorCannotLoadFromNetwork = 		-2000,

    // Download and file I/O errors
    /// A download task couldn't create the downloaded file on disk because of an I/O failure.
    NSURLErrorCannotCreateFile = 		-3000,
    /// A downloaded file on disk couldn't be opened.
    NSURLErrorCannotOpenFile = 			-3001,
    /// A download task couldn't close the downloaded file on disk.
    NSURLErrorCannotCloseFile = 		-3002,
    /// A download task couldn't write the file to disk.
    NSURLErrorCannotWriteToFile = 		-3003,
    /// A downloaded file couldn't be removed from disk.
    NSURLErrorCannotRemoveFile = 		-3004,
    /// A downloaded file on disk couldn't be moved.
    NSURLErrorCannotMoveFile = 			-3005,
    /// A download task failed to decode an encoded file during the download.
    NSURLErrorDownloadDecodingFailedMidStream = -3006,
    /// A download task failed to decode an encoded file after downloading.
    NSURLErrorDownloadDecodingFailedToComplete =-3007,

    /// The attempted connection required activating a data context while roaming, but international roaming is disabled.
    NSURLErrorInternationalRoamingOff API_AVAILABLE(macos(10.7), ios(3.0), watchos(2.0), tvos(9.0)) =         -1018,
    /// A connection was attempted while a phone call was active on a network that doesn't support simultaneous phone and data communication, such as EDGE or GPRS.
    NSURLErrorCallIsActive API_AVAILABLE(macos(10.7), ios(3.0), watchos(2.0), tvos(9.0)) =                    -1019,
    /// The cellular network disallowed a connection.
    NSURLErrorDataNotAllowed API_AVAILABLE(macos(10.7), ios(3.0), watchos(2.0), tvos(9.0)) =                  -1020,
    /// A body stream was needed but the client did not provide one.
    ///
    /// This impacts clients on iOS that send a `POST` request using a body stream but do not implement the ``URLSessionTaskDelegate`` delegate method ``URLSessionTaskDelegate/urlSession(_:task:needNewBodyStream:)``.
    NSURLErrorRequestBodyStreamExhausted API_AVAILABLE(macos(10.7), ios(3.0), watchos(2.0), tvos(9.0)) =      -1021,

    /// The shared container identifier of the URL session configuration is needed but hasn't been set.
    ///
    /// To use a ``URLSession`` to perform background uploading or downloading in an app extension, you coordinate with the host app using a shared container. The app extension must set the ``URLSessionConfiguration/sharedContainerIdentifier`` of the URL session's configuration to the shared container's identifier.
    NSURLErrorBackgroundSessionRequiresSharedContainer API_AVAILABLE(macos(10.10), ios(8.0), watchos(2.0), tvos(9.0)) = -995,
    /// An app or app extension attempted to connect to a background session that is already connected to a process.
    ///
    /// This error can occur when both an app and an app extension attempt to use a background session at the same time.
    NSURLErrorBackgroundSessionInUseByAnotherProcess API_AVAILABLE(macos(10.10), ios(8.0), watchos(2.0), tvos(9.0)) = -996,
    /// The app is suspended or exits while a background data task is processing.
    ///
    /// If your app has created a background data task and the app is then suspended, the task will fail with this error code. To prevent this, when you receive the response, convert the data task to a download task.
    NSURLErrorBackgroundSessionWasDisconnected API_AVAILABLE(macos(10.10), ios(8.0), watchos(2.0), tvos(9.0))= -997,
};

NS_HEADER_AUDIT_END(nullability, sendability)
