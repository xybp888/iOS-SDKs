/*	NSURLSession.h
	Copyright (c) 2013-2019, Apple Inc. All rights reserved.
*/

#import <Foundation/NSObject.h>
#import <Foundation/NSURLRequest.h>
#import <Foundation/NSHTTPCookieStorage.h>
#import <Foundation/NSProgress.h>

#include <Security/SecureTransport.h>

@class NSString;
@class NSURL;
@class NSError;
@class NSArray<ObjectType>;
@class NSDictionary<KeyType, ObjectType>;
@class NSInputStream;
@class NSOutputStream;
@class NSData;
@class NSOperationQueue;

@class NSURLCache;
@class NSURLResponse;
@class NSHTTPURLResponse;
@class NSHTTPCookie;
@class NSCachedURLResponse;
@class NSURLAuthenticationChallenge;
@class NSURLProtectionSpace;
@class NSURLCredential;
@class NSURLCredentialStorage;
@class NSURLSessionDataTask;
@class NSURLSessionUploadTask;
@class NSURLSessionDownloadTask;
@class NSNetService;

/*

 NSURLSession is a replacement API for NSURLConnection.  It provides
 options that affect the policy of, and various aspects of the
 mechanism by which NSURLRequest objects are retrieved from the
 network.

 An NSURLSession may be bound to a delegate object.  The delegate is
 invoked for certain events during the lifetime of a session, such as
 server authentication or determining whether a resource to be loaded
 should be converted into a download.
 
 NSURLSession instances are thread-safe.

 The default NSURLSession uses a system provided delegate and is
 appropriate to use in place of existing code that uses
 +[NSURLConnection sendAsynchronousRequest:queue:completionHandler:]

 An NSURLSession creates NSURLSessionTask objects which represent the
 action of a resource being loaded.  These are analogous to
 NSURLConnection objects but provide for more control and a unified
 delegate model.
 
 NSURLSessionTask objects are always created in a suspended state and
 must be sent the -resume message before they will execute.

 Subclasses of NSURLSessionTask are used to syntactically
 differentiate between data and file downloads.

 An NSURLSessionDataTask receives the resource as a series of calls to
 the URLSession:dataTask:didReceiveData: delegate method.  This is type of
 task most commonly associated with retrieving objects for immediate parsing
 by the consumer.

 An NSURLSessionUploadTask differs from an NSURLSessionDataTask
 in how its instance is constructed.  Upload tasks are explicitly created
 by referencing a file or data object to upload, or by utilizing the
 -URLSession:task:needNewBodyStream: delegate message to supply an upload
 body.

 An NSURLSessionDownloadTask will directly write the response data to
 a temporary file.  When completed, the delegate is sent
 URLSession:downloadTask:didFinishDownloadingToURL: and given an opportunity 
 to move this file to a permanent location in its sandboxed container, or to
 otherwise read the file. If canceled, an NSURLSessionDownloadTask can
 produce a data blob that can be used to resume a download at a later
 time.

 Beginning with iOS 9 and Mac OS X 10.11, NSURLSessionStream is
 available as a task type.  This allows for direct TCP/IP connection
 to a given host and port with optional secure handshaking and
 navigation of proxies.  Data tasks may also be upgraded to a
 NSURLSessionStream task via the HTTP Upgrade: header and appropriate
 use of the pipelining option of NSURLSessionConfiguration.  See RFC
 2817 and RFC 6455 for information about the Upgrade: header, and
 comments below on turning data tasks into stream tasks.

 An NSURLSessionWebSocketTask is a task that allows clients to connect to servers supporting
 WebSocket. The task will perform the HTTP handshake to upgrade the connection
 and once the WebSocket handshake is successful, the client can read and write
 messages that will be framed using the WebSocket protocol by the framework.
 */

@class NSURLSession;
@class NSURLSessionDataTask;                /* DataTask objects receive the payload through zero or more delegate messages */
@class NSURLSessionUploadTask;              /* UploadTask objects receive periodic progress updates but do not return a body */
@class NSURLSessionDownloadTask;            /* DownloadTask objects represent an active download to disk.  They can provide resume data when canceled. */
@class NSURLSessionStreamTask;              /* StreamTask objects may be used to create NSInput and NSOutputStreams, or used directly in reading and writing. */
@class NSURLSessionWebSocketTask;           /* WebSocket objects perform a WebSocket handshake with the server and can be used to send and receive WebSocket messages */

@class NSURLSessionConfiguration;
@protocol NSURLSessionDelegate;
@protocol NSURLSessionTaskDelegate;

@class NSURLSessionTaskMetrics;
@class NSDateInterval;

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

#define NSURLSESSION_AVAILABLE	10_9

/// The total size of the transfer cannot be determined.
FOUNDATION_EXPORT const int64_t NSURLSessionTransferSizeUnknown API_AVAILABLE(macos(10.9), ios(7.0), watchos(2.0), tvos(9.0));    /* -1LL */

/// An object that coordinates a group of related, network data transfer tasks.
///
/// The ``URLSession`` class and related classes provide an API for downloading data from and uploading data to endpoints indicated by URLs. Your app can also use this API to perform background downloads when your app isn't running or, in iOS, while your app is suspended. You can use the related ``URLSessionDelegate`` and ``URLSessionTaskDelegate`` to support authentication and receive events like redirection and task completion.
///
/// > Note:
/// > The ``URLSession`` API involves many different classes that work together in a fairly complex way which may not be obvious if you read the reference documentation by itself. Before using the API, read the overview in the <doc:url-loading-system> topic. The articles in the Essentials, Uploading, and Downloading sections offer examples of performing common tasks with ``URLSession``.
///
/// Your app creates one or more ``URLSession`` instances, each of which coordinates a group of related data-transfer tasks. For example, if you're creating a web browser, your app might create one session per tab or window, or one session for interactive use and another for background downloads. Within each session, your app adds a series of tasks, each of which represents a request for a specific URL (following HTTP redirects, if necessary).
///
/// ### Types of URL sessions
///
/// The tasks within a given URL session share a common session configuration object, which defines connection behavior, like the maximum number of simultaneous connections to make to a single host, whether connections can use the cellular network, and so on.
///
/// ``URLSession`` has a singleton ``shared`` session (which doesn't have a configuration object) for basic requests. It's not as customizable as sessions you create, but it serves as a good starting point if you have very limited requirements. You access this session by calling the shared class method. For other kinds of sessions, you create a ``URLSession`` with one of three kinds of configurations:
///
/// - A default session behaves much like the shared session, but lets you configure it. You can also assign a delegate to the default session to obtain data incrementally.
/// - Ephemeral sessions are similar to shared sessions, but don't write caches, cookies, or credentials to disk.
/// - Background sessions let you perform uploads and downloads of content in the background while your app isn't running.
///
/// See Creating a session configuration object in the ``URLSessionConfiguration`` class for details on creating each type of configuration.
///
/// ### Types of URL session tasks
///
/// Within a session, you create tasks that optionally upload data to a server and then retrieve data from the server either as a file on disk or as one or more ``NSData`` objects in memory. The ``URLSession`` API provides four types of tasks:
///
/// - Data tasks send and receive data using ``NSData`` objects. Data tasks are intended for short, often interactive requests to a server.
/// - Upload tasks are similar to data tasks, but they also send data (often in the form of a file), and support background uploads while the app isn't running.
/// - Download tasks retrieve data in the form of a file, and support background downloads and uploads while the app isn't running.
/// - WebSocket tasks exchange messages over TCP and TLS, using the WebSocket protocol defined in [RFC 6455](https://tools.ietf.org/html/rfc6455).
///
///
///
/// ### Using a session delegate
///
/// Tasks in a session also share a common delegate object. You implement this delegate to provide and obtain information when various events occur, including when:
///
/// - Authentication fails.
/// - Data arrives from the server.
/// - Data becomes available for caching.
///
/// If you don't need the features provided by a delegate, you can use this API without providing one by passing `nil` when you create a session.
///
/// > Important:
/// > The session object keeps a strong reference to the delegate until your app exits or explicitly invalidates the session. If you don't invalidate the session, your app leaks memory until the app terminates.
///
/// Each task you create with the session calls back to the session's delegate, using the methods defined in ``URLSessionTaskDelegate``. You can also intercept these callbacks before they reach the session delegate by populating a separate ``URLSessionTask/delegate`` that's specific to the task.
///
/// ### Asynchronicity and URL sessions
///
/// Like most networking APIs, the ``URLSession`` API is highly asynchronous. It returns data to your app in one of three ways, depending on the methods you call:
///
/// - If you're using Swift, you can use the methods marked with the `async` keyword to perform common tasks. For example, ``data(from:delegate:)`` fetches data, while ``download(from:delegate:)`` downloads files. Your call point uses the `await` keyword to suspend running until the transfer completes. You can also use the ``bytes(from:delegate:)`` method to receive data as an <doc://com.apple.documentation/documentation/swift/asyncsequence>. With this approach, you use the `for`-`await`-`in` syntax to iterate over the data as your app receives it. The ``URL`` type also offers covenience methods to fetch bytes or lines from the shared URL session.
/// - In Swift or Objective-C, you can provide a completion handler block, which runs when the transfer completes.
/// - In Swift or Objective-C, you can receive callbacks to a delegate method as the transfer progresses and immediately after it completes.
///
/// In addition to delivering this information to delegates, the ``URLSession`` provides status and progress properties. Query these properties if you need to make programmatic decisions based on the current state of the task (with the caveat that its state can change at any time).
///
/// ### Protocol support
///
/// The ``URLSession`` class natively supports the `data`, `file`, `ftp`, `http`, and `https` URL schemes, with transparent support for proxy servers and SOCKS gateways, as configured in the user's system preferences.
///
/// ``URLSession`` supports the HTTP/1.1, HTTP/2, and HTTP/3 protocols. HTTP/2 support, as described by [RFC 7540](https://tools.ietf.org/html/rfc7540), requires a server that supports Application-Layer Protocol Negotiation (ALPN).
///
/// You can also add support for your own custom networking protocols and URL schemes (for your app's private use) by subclassing ``URLProtocol``.
///
/// ### App Transport Security (ATS)
///
/// iOS 9.0 and macOS 10.11 and later use App Transport Security (ATS) for all HTTP connections made with ``URLSession``. ATS requires that HTTP connections use HTTPS ([RFC 2818](https://tools.ietf.org/html/rfc2818)).
///
/// For more information, see <doc://com.apple.documentation/documentation/bundleresources/information-property-list/nsapptransportsecurity>.
///
/// ### Foundation copying behavior
///
/// Session and task objects conform to the ``NSCopying`` protocol as follows:
///
/// - When your app copies a session or task object, you get the same object back.
/// - When your app copies a configuration object, you get a new copy you can independently modify.
///
/// ### Thread safety
///
/// The URL session API is thread-safe. You can freely create sessions and tasks in any thread context. When your delegate methods call the provided completion handlers, the work is automatically scheduled on the correct delegate queue.
NS_SWIFT_SENDABLE
API_AVAILABLE(macos(10.9), ios(7.0), watchos(2.0), tvos(9.0))
@interface NSURLSession : NSObject

/// The shared singleton session object.
///
/// For basic requests, the `NSURLSession` class provides a shared singleton session object
/// that gives you a reasonable default behavior for creating tasks. Use the shared session to
/// fetch the contents of a URL to memory with just a few lines of code.
///
/// Unlike the other session types, you don't create the shared session; you merely access it
/// by using this property directly. As a result, you don't provide a delegate or a configuration object.
///
/// Because the shared session has neither a delegate nor a customizable configuration object, the
/// shared session has important limitations:
///
/// - You can't obtain data incrementally as it arrives from the server.
/// - You can't significantly customize the default connection behavior.
/// - Your ability to perform authentication is limited.
/// - You can't perform background downloads or uploads when your app isn't running.
///
/// The shared session uses the shared `NSURLCache`, `NSHTTPCookieStorage`, and
/// `NSURLCredentialStorage` objects, uses a shared custom networking protocol list
/// (configured with `+[NSURLProtocol registerClass:]` and `+[NSURLProtocol unregisterClass:]`),
/// and is based on a default configuration.
@property (class, readonly, strong) NSURLSession *sharedSession;

/// Creates a session with the specified session configuration.
///
/// - Parameter configuration: A configuration object that specifies certain behaviors, such as
///   caching policies, timeouts, proxies, pipelining, TLS versions to support, cookie policies,
///   credential storage, and so on. See `NSURLSessionConfiguration` for more information.
///
/// Calling this method is equivalent to calling
/// `+sessionWithConfiguration:delegate:delegateQueue:` with a `nil` delegate and queue.
+ (NSURLSession *)sessionWithConfiguration:(NSURLSessionConfiguration *)configuration;

/// Creates a session with the specified session configuration, delegate, and operation queue.
///
/// - Parameter configuration: A configuration object that specifies certain behaviors, such as
///   caching policies, timeouts, proxies, pipelining, TLS versions to support, cookie policies,
///   and credential storage. See `NSURLSessionConfiguration` for more information.
/// - Parameter delegate: A session delegate object that handles requests for authentication
///   and other session-related events. This delegate object is responsible for handling
///   authentication challenges, for making caching decisions, and for handling other
///   session-related events. If `nil`, the class should be used only with methods that take
///   completion handlers. The session object keeps a strong reference to the delegate until
///   your app exits or explicitly invalidates the session. If you do not invalidate the session
///   by calling `-invalidateAndCancel` or `-finishTasksAndInvalidate`, your app leaks memory
///   until it exits.
/// - Parameter queue: An operation queue for scheduling the delegate calls and completion
///   handlers. The queue should be a serial queue, in order to ensure the correct ordering of
///   callbacks. If `nil`, the session creates a serial operation queue for performing all
///   delegate method calls and completion handler calls.
+ (NSURLSession *)sessionWithConfiguration:(NSURLSessionConfiguration *)configuration delegate:(nullable id <NSURLSessionDelegate>)delegate delegateQueue:(nullable NSOperationQueue *)queue;

/// The operation queue provided when this object was created.
///
/// All delegate method calls and completion handlers related to the session are performed on
/// this queue. The session object keeps a strong reference to this queue until your app exits
/// or the session object is deallocated. If you do not invalidate the session, your app leaks
/// memory until it exits.
///
/// > Note: This queue must be set at object creation time and may not be changed.
@property (readonly, retain) NSOperationQueue *delegateQueue;

/// The delegate assigned when this object was created.
///
/// This delegate object is responsible for handling authentication challenges, for making
/// caching decisions, and for handling other session-related events. The session object keeps
/// a strong reference to this delegate until your app exits or explicitly invalidates the
/// session. If you do not invalidate the session, your app leaks memory until it exits.
///
/// > Note: This delegate object must be set at object creation time and may not be changed.
@property (nullable, readonly, retain) id <NSURLSessionDelegate> delegate;

/// A copy of the configuration object for this session.
///
/// Beginning in iOS 9 and OS X 10.11, `NSURLSession` objects store a copy of the
/// `NSURLSessionConfiguration` object passed to their initializers, such that a session's
/// configuration is immutable after initialization. Any further changes to mutable properties
/// on the configuration object passed to a session's initializer or the value returned from
/// a session's configuration property do not affect the behavior of that session. However,
/// you can create a new session with the modified configuration object.
@property (readonly, copy) NSURLSessionConfiguration *configuration;

/// An app-defined descriptive label for the session.
///
/// This property contains a human-readable string that you can use for debugging purposes.
/// This value may be `nil` and defaults to `nil`. The value is ignored by the session.
@property (nullable, copy) NSString *sessionDescription;

/// Invalidates the session, allowing any outstanding tasks to finish.
///
/// This method returns immediately without waiting for tasks to finish. Once a session is
/// invalidated, new tasks cannot be created in the session, but existing tasks continue until
/// completion. After the last task finishes and the session makes the last delegate call related
/// to those tasks, the session calls the `URLSession:didBecomeInvalidWithError:` method on its
/// delegate, then breaks references to the delegate and callback objects. After invalidation,
/// session objects cannot be reused.
///
/// To cancel all outstanding tasks, call `-invalidateAndCancel` instead.
///
/// > Important: Calling this method on the shared session has no effect.
///
/// When invalidating a background session, it is not safe to create another background
/// session with the same identifier until `URLSession:didBecomeInvalidWithError:` has
/// been issued.
- (void)finishTasksAndInvalidate;

/// Cancels all outstanding tasks and then invalidates the session.
///
/// Once invalidated, references to the delegate and callback objects are broken. After
/// invalidation, session objects cannot be reused.
///
/// To allow outstanding tasks to run until completion, call `-finishTasksAndInvalidate` instead.
///
/// > Important: Calling this method on the shared session has no effect.
- (void)invalidateAndCancel;

/// Empties all cookies, caches and credential stores, removes disk files, flushes in-progress
/// downloads to disk, and ensures that future requests occur on a new socket.
///
/// - Parameter completionHandler: The completion handler to call when the reset operation is
///   complete. This handler is executed on the delegate queue.
- (void)resetWithCompletionHandler:(void (NS_SWIFT_SENDABLE ^)(void))completionHandler;

/// Flushes cookies and credentials to disk, clears transient caches, and ensures that future
/// requests occur on a new TCP connection.
///
/// - Parameter completionHandler: The completion handler to call when the flush operation is
///   complete. This handler is executed on the delegate queue.
- (void)flushWithCompletionHandler:(void (NS_SWIFT_SENDABLE ^)(void))completionHandler;

/// Asynchronously calls a completion callback with all data, upload, and download tasks in a session.
///
/// - Parameter completionHandler: The completion handler to call with the list of tasks.
///   This handler is executed on the delegate queue. The arrays passed to the completion handler
///   contain any tasks that you have created within the session, not including any tasks that
///   have been invalidated after completing, failing, or being cancelled.
- (void)getTasksWithCompletionHandler:(void (NS_SWIFT_SENDABLE ^)(NSArray<NSURLSessionDataTask *> *dataTasks, NSArray<NSURLSessionUploadTask *> *uploadTasks, NSArray<NSURLSessionDownloadTask *> *downloadTasks))completionHandler NS_SWIFT_ASYNC_NAME(getter:tasks());

/// Asynchronously calls a completion callback with all tasks in a session.
///
/// - Parameter completionHandler: The completion handler to call with the list of tasks.
- (void)getAllTasksWithCompletionHandler:(void (NS_SWIFT_SENDABLE ^)(NSArray<__kindof NSURLSessionTask *> *tasks))completionHandler NS_SWIFT_ASYNC_NAME(getter:allTasks()) API_AVAILABLE(macos(10.11), ios(9.0), watchos(2.0), tvos(9.0));

/* 
 * NSURLSessionTask objects are always created in a suspended state and
 * must be sent the -resume message before they will execute.
 */

/// Creates a task that retrieves the contents of a URL based on the specified URL request object.
///
/// By creating a task based on a request object, you can tune various aspects of the task's
/// behavior, including the cache policy and timeout interval.
///
/// After you create the task, you must start it by calling its `-resume` method.
///
/// - Parameter request: A URL request object that provides request-specific information such as
///   the URL, cache policy, request type, and body data or body stream.
/// - Returns: The new session data task.
- (NSURLSessionDataTask *)dataTaskWithRequest:(NSURLRequest *)request;

/// Creates a task that retrieves the contents of the specified URL.
///
/// After you create the task, you must start it by calling its `-resume` method. The task
/// calls methods on the session's delegate to provide you with the response metadata, response
/// data, and so on.
///
/// - Parameter url: The URL to be retrieved.
/// - Returns: The new session data task.
- (NSURLSessionDataTask *)dataTaskWithURL:(NSURL *)url;

/// Creates a task that performs an HTTP request for uploading the specified file.
///
/// An HTTP upload request is any request that contains a request body, such as a `POST` or
/// `PUT` request. Upload tasks require you to create a request object so that you can provide
/// metadata for the upload, like HTTP request headers.
///
/// After you create the task, you must start it by calling its `-resume` method. The task
/// calls methods on the session's delegate to provide you with the upload's progress, response
/// metadata, response data, and so on.
///
/// - Parameter request: A URL request object that provides the URL, cache policy, request type,
///   and so on. The body stream and body data in this request object are ignored.
/// - Parameter fileURL: The URL of the file to upload.
/// - Returns: The new session upload task.
- (NSURLSessionUploadTask *)uploadTaskWithRequest:(NSURLRequest *)request fromFile:(NSURL *)fileURL;

/// Creates a task that performs an HTTP request for the specified URL request object and
/// uploads the provided data.
///
/// An HTTP upload request is any request that contains a request body, such as a `POST` or
/// `PUT` request. Upload tasks require you to create a request object so that you can provide
/// metadata for the upload, like HTTP request headers.
///
/// After you create the task, you must start it by calling its `-resume` method. The task
/// calls methods on the session's delegate to provide you with the upload's progress, response
/// metadata, response data, and so on.
///
/// - Parameter request: A URL request object that provides the URL, cache policy, request type,
///   and so on. The body stream and body data in this request object are ignored.
/// - Parameter bodyData: The body data for the request.
/// - Returns: The new session upload task.
- (NSURLSessionUploadTask *)uploadTaskWithRequest:(NSURLRequest *)request fromData:(NSData *)bodyData;

/// Creates an upload task from a resume data blob. Requires the server to support the latest resumable uploads
/// Internet-Draft from the HTTP Working Group, found at
/// https://datatracker.ietf.org/doc/draft-ietf-httpbis-resumable-upload/
/// If resuming from an upload file, the file must still exist and be unmodified. If the upload cannot be successfully
/// resumed, URLSession:task:didCompleteWithError: will be called.
///
/// - Parameter resumeData: Resume data blob from an incomplete upload, such as data returned by the cancelByProducingResumeData: method.
/// - Returns: A new session upload task, or nil if the resumeData is invalid.
- (NSURLSessionUploadTask *)uploadTaskWithResumeData:(NSData *)resumeData API_AVAILABLE(macos(14.0), ios(17.0), watchos(10.0), tvos(17.0));

/// Creates a task that performs an HTTP request for uploading data based on the specified URL
/// request.
///
/// An HTTP upload request is any request that contains a request body, such as a `POST` or
/// `PUT` request. Upload tasks require you to provide a request object so that you can provide
/// metadata for the upload, such as HTTP request headers.
///
/// After you create the task, you must start it by calling its `-resume` method. The task
/// calls methods on the session's delegate to provide you with the upload's progress, response
/// metadata, response data, and so on. The session's delegate must have a
/// `URLSession:task:needNewBodyStream:` method that provides the body data to upload.
///
/// - Parameter request: A URL request object that provides the URL, cache policy, request type,
///   and so on. The body stream and body data in this request object are ignored, and the
///   session calls its delegate's `URLSession:task:needNewBodyStream:` method to supply an
///   upload body.
/// - Returns: The new session upload task.
- (NSURLSessionUploadTask *)uploadTaskWithStreamedRequest:(NSURLRequest *)request;

/// Creates a download task that retrieves the contents of a URL based on the specified URL
/// request object and saves the results to a file.
///
/// By creating a task based on a request object, you can tune various aspects of the task's
/// behavior, including the cache policy and timeout interval.
///
/// After you create the task, you must start it by calling its `-resume` method. The task
/// calls methods on the session's delegate to provide you with progress notifications, the
/// location of the resulting temporary file, and so on.
///
/// - Parameter request: A URL request object that provides the URL, cache policy, request type,
///   body data or body stream, and so on.
/// - Returns: The new session download task.
- (NSURLSessionDownloadTask *)downloadTaskWithRequest:(NSURLRequest *)request;

/// Creates a download task that retrieves the contents of the specified URL and saves the
/// results to a file.
///
/// After you create the task, you must start it by calling its `-resume` method.
///
/// - Parameter url: The URL to download.
/// - Returns: The new session download task.
- (NSURLSessionDownloadTask *)downloadTaskWithURL:(NSURL *)url;

/// Creates a download task to resume a previously canceled or failed download.
///
/// After you create the task, you must start it by calling its `-resume` method.
///
/// This method is equivalent to `-downloadTaskWithResumeData:completionHandler:` with a
/// `nil` completion handler. For detailed usage information, including ways to obtain a
/// resume data object, see that method.
///
/// - Parameter resumeData: A data object that provides the data necessary to resume a download.
/// - Returns: The new session download task.
- (NSURLSessionDownloadTask *)downloadTaskWithResumeData:(NSData *)resumeData;

/// Creates a task that establishes a bidirectional TCP/IP connection to a specified hostname
/// and port.
///
/// After you create the task, you must start it by calling its `-resume` method.
///
/// - Parameter hostname: The hostname of the connection endpoint.
/// - Parameter port: The port of the connection endpoint.
/// - Returns: The new session stream task.
- (NSURLSessionStreamTask *)streamTaskWithHostName:(NSString *)hostname port:(NSInteger)port API_AVAILABLE(macos(10.11), ios(9.0), watchos(2.0), tvos(9.0));

/// Creates a task that establishes a bidirectional TCP/IP connection using a specified
/// network service.
///
/// After you create the task, you must start it by calling its `-resume` method.
///
/// - Parameter service: An `NSNetService` object used to determine the endpoint of the TCP/IP
///   connection. This network service is resolved before any data is read or written to the
///   resulting stream task.
/// - Returns: The new session stream task.
- (NSURLSessionStreamTask *)streamTaskWithNetService:(NSNetService *)service API_DEPRECATED("Use nw_connection_t in Network framework instead", macos(10.11, API_TO_BE_DEPRECATED), ios(9.0, API_TO_BE_DEPRECATED), tvos(9.0, API_TO_BE_DEPRECATED)) API_UNAVAILABLE(watchos);

/// Creates a WebSocket task for the provided URL.
///
/// The provided URL must have a `ws` or `wss` scheme.
///
/// - Parameter url: The WebSocket URL with which to connect.
- (NSURLSessionWebSocketTask *)webSocketTaskWithURL:(NSURL *)url API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0));

/// Creates a WebSocket task given a URL and an array of protocols.
///
/// During the WebSocket handshake, the task uses the provided protocols to negotiate a
/// preferred protocol with the server.
///
/// > Note: The protocol doesn't affect the WebSocket framing. More details on the protocol
/// > are available in RFC 6455, The WebSocket Protocol.
///
/// - Parameter url: The WebSocket URL with which to connect.
/// - Parameter protocols: An array of protocols to negotiate with the server.
- (NSURLSessionWebSocketTask *)webSocketTaskWithURL:(NSURL *)url protocols:(NSArray<NSString *>*)protocols API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0));

/// Creates a WebSocket task for the provided URL request.
///
/// You can modify the request's properties prior to calling `-resume` on the task. The task
/// uses these properties during the HTTP handshake phase.
///
/// To add custom protocols, add a header with the key `Sec-WebSocket-Protocol`, and a
/// comma-separated list of protocols you want to negotiate with the server. The custom HTTP
/// headers provided by the client remain unchanged for the handshake with the server.
///
/// - Parameter request: A URL request that indicates a WebSocket endpoint with which to connect.
- (NSURLSessionWebSocketTask *)webSocketTaskWithRequest:(NSURLRequest *)request API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0));


- (instancetype)init API_DEPRECATED("Please use +[NSURLSession sessionWithConfiguration:] or other class methods to create instances", macos(10.9,10.15), ios(7.0,13.0), watchos(2.0,6.0), tvos(9.0,13.0));
+ (instancetype)new API_DEPRECATED("Please use +[NSURLSession sessionWithConfiguration:] or other class methods to create instances", macos(10.9,10.15), ios(7.0,13.0), watchos(2.0,6.0), tvos(9.0,13.0));

@end

/*
 * NSURLSession convenience routines deliver results to 
 * a completion handler block.  These convenience routines
 * are not available to NSURLSessions that are configured
 * as background sessions.
 *
 * Task objects are always created in a suspended state and 
 * must be sent the -resume message before they will execute.
 */
@interface NSURLSession (NSURLSessionAsynchronousConvenience)
/// Creates a task that retrieves the contents of a URL based on the specified URL request
/// object, and calls a handler upon completion.
///
/// By creating a task based on a request object, you can tune various aspects of the task's
/// behavior, including the cache policy and timeout interval.
///
/// By using the completion handler, the task bypasses calls to delegate methods for response
/// and data delivery, and instead provides any resulting `NSData`, `NSURLResponse`, and
/// `NSError` objects inside the completion handler. Delegate methods for handling
/// authentication challenges, however, are still called.
///
/// After you create the task, you must start it by calling its `-resume` method.
///
/// - Parameter request: A URL request object that provides the URL, cache policy, request type,
///   body data or body stream, and so on.
/// - Parameter completionHandler: The completion handler to call when the load request is
///   complete. This handler is executed on the delegate queue.
- (NSURLSessionDataTask *)dataTaskWithRequest:(NSURLRequest *)request completionHandler:(void (NS_SWIFT_SENDABLE ^)(NSData * _Nullable data, NSURLResponse * _Nullable response, NSError * _Nullable error))completionHandler;

/// Creates a task that retrieves the contents of the specified URL, then calls a handler upon
/// completion.
///
/// After you create the task, you must start it by calling its `-resume` method.
///
/// By using the completion handler, the task bypasses calls to delegate methods for response
/// and data delivery, and instead provides any resulting `NSData`, `NSURLResponse`, and
/// `NSError` objects inside the completion handler. Delegate methods for handling
/// authentication challenges, however, are still called.
///
/// - Parameter url: The URL to be retrieved.
/// - Parameter completionHandler: The completion handler to call when the load request is
///   complete. This handler is executed on the delegate queue.
- (NSURLSessionDataTask *)dataTaskWithURL:(NSURL *)url completionHandler:(void (NS_SWIFT_SENDABLE ^)(NSData * _Nullable data, NSURLResponse * _Nullable response, NSError * _Nullable error))completionHandler;

/// Creates a task that performs an HTTP request for uploading the specified file, then calls
/// a handler upon completion.
///
/// - Parameter request: A URL request object that provides the URL, cache policy, request type,
///   and so on. The body stream and body data in this request object are ignored.
/// - Parameter fileURL: The URL of the file to upload.
/// - Parameter completionHandler: The completion handler to call when the load request is
///   complete. This handler is executed on the delegate queue.
- (NSURLSessionUploadTask *)uploadTaskWithRequest:(NSURLRequest *)request fromFile:(NSURL *)fileURL completionHandler:(void (NS_SWIFT_SENDABLE ^)(NSData * _Nullable data, NSURLResponse * _Nullable response, NSError * _Nullable error))completionHandler;

/// Creates a task that performs an HTTP request for the specified URL request object, uploads
/// the provided data, and calls a handler upon completion.
///
/// - Parameter request: A URL request object that provides the URL, cache policy, request type,
///   and so on. The body stream and body data in this request object are ignored.
/// - Parameter bodyData: The body data for the request.
/// - Parameter completionHandler: The completion handler to call when the load request is
///   complete. This handler is executed on the delegate queue.
- (NSURLSessionUploadTask *)uploadTaskWithRequest:(NSURLRequest *)request fromData:(nullable NSData *)bodyData completionHandler:(void (NS_SWIFT_SENDABLE ^)(NSData * _Nullable data, NSURLResponse * _Nullable response, NSError * _Nullable error))completionHandler;

/// Creates a URLSessionUploadTask from a resume data blob. If resuming from an upload
/// file, the file must still exist and be unmodified.
///
/// - Parameter resumeData: Resume data blob from an incomplete upload, such as data returned by the cancelByProducingResumeData: method.
/// - Parameter completionHandler: The completion handler to call when the load request is complete.
/// - Returns: A new session upload task, or nil if the resumeData is invalid.
- (NSURLSessionUploadTask *)uploadTaskWithResumeData:(NSData *)resumeData completionHandler:(void (NS_SWIFT_SENDABLE ^)(NSData * _Nullable data, NSURLResponse * _Nullable response, NSError * _Nullable error))completionHandler API_AVAILABLE(macos(14.0), ios(17.0), watchos(10.0), tvos(17.0));

/// Creates a download task that retrieves the contents of a URL based on the specified URL
/// request object, saves the results to a file, and calls a handler upon completion.
///
/// By creating a task based on a request object, you can tune various aspects of the task's
/// behavior, including the cache policy and timeout interval.
///
/// After you create the task, you must start it by calling its `-resume` method.
///
/// - Parameter request: A URL request object that provides the URL, cache policy, request type,
///   body data or body stream, and so on.
/// - Parameter completionHandler: The completion handler to call when the load request is
///   complete. This handler is executed on the delegate queue.
- (NSURLSessionDownloadTask *)downloadTaskWithRequest:(NSURLRequest *)request completionHandler:(void (NS_SWIFT_SENDABLE ^)(NSURL * _Nullable location, NSURLResponse * _Nullable response, NSError * _Nullable error))completionHandler;

/// Creates a download task that retrieves the contents of the specified URL, saves the results
/// to a file, and calls a handler upon completion.
///
/// After you create the task, you must start it by calling its `-resume` method.
///
/// - Parameter url: The URL to download.
/// - Parameter completionHandler: The completion handler to call when the load request is
///   complete. This handler is executed on the delegate queue.
- (NSURLSessionDownloadTask *)downloadTaskWithURL:(NSURL *)url completionHandler:(void (NS_SWIFT_SENDABLE ^)(NSURL * _Nullable location, NSURLResponse * _Nullable response, NSError * _Nullable error))completionHandler;

/// Creates a download task to resume a previously canceled or failed download and calls a
/// handler upon completion.
///
/// Your app can obtain a `resumeData` object in two ways:
///
/// - If your app cancels an existing transfer by calling
///   `-cancelByProducingResumeData:`, the session object passes a `resumeData`
///   object to the completion handler that you provided in that call.
/// - If a transfer fails, the session object provides an `NSError` object either to its
///   delegate or to the task's completion handler. In that object, the
///   `NSURLSessionDownloadTaskResumeData` key in the `userInfo` dictionary contains a
///   `resumeData` object.
///
/// After you create the task, you must start it by calling its `-resume` method.
///
/// > Note: A download can be resumed only if it is an HTTP or HTTPS `GET` request, and only
/// > if the remote server supports byte-range requests (with the `Range` header) and provides
/// > the `ETag` or `Last-Modified` header in its responses.
///
/// - Parameter resumeData: A data object that provides the data necessary to resume the download.
/// - Parameter completionHandler: The completion handler to call when the load request is
///   complete. This handler is executed on the delegate queue.
- (NSURLSessionDownloadTask *)downloadTaskWithResumeData:(NSData *)resumeData completionHandler:(void (NS_SWIFT_SENDABLE ^)(NSURL * _Nullable location, NSURLResponse * _Nullable response, NSError * _Nullable error))completionHandler;

@end

/// Constants for determining the current state of a task.
typedef NS_ENUM(NSInteger, NSURLSessionTaskState) {
    /// The task is currently being serviced by the session.
    ///
    /// A task in this state is subject to the request and resource timeouts specified in the session configuration object.
    NSURLSessionTaskStateRunning = 0,
    /// The task was suspended by the app.
    ///
    /// No further processing takes place until the task is resumed. A task in this state is not subject to timeouts.
    NSURLSessionTaskStateSuspended = 1,
    /// The task has received a cancel message.
    ///
    /// The delegate may or may not have received a `URLSession:task:didCompleteWithError:` message yet. A task in this state is not subject to timeouts.
    NSURLSessionTaskStateCanceling = 2,
    /// The task has completed (without being canceled), and the task's delegate receives no further callbacks.
    ///
    /// If the task completed successfully, the task's `error` property is `nil`. Otherwise, it provides an error object that tells what went wrong. A task in this state is not subject to timeouts.
    NSURLSessionTaskStateCompleted = 3,
} API_AVAILABLE(macos(10.9), ios(7.0), watchos(2.0), tvos(9.0));

/// A task, like downloading a specific resource, performed in a URL session.
///
/// The ``URLSessionTask`` class is the base class for tasks in a URL session. Tasks are always part of a session; you create a task by calling one of the task creation methods on a ``URLSession`` instance. The method you call determines the type of task.
///
/// - Use ``URLSession``'s ``URLSession/dataTask(with:)-10dy7`` and related methods to create ``URLSessionDataTask`` instances. Data tasks request a resource, returning the server's response as one or more `NSData` objects in memory. They are supported in default, ephemeral, and shared sessions, but are not supported in background sessions.
/// - Use ``URLSession``'s ``URLSession/uploadTask(with:from:)`` and related methods to create ``URLSessionUploadTask`` instances. Upload tasks are like data tasks, except that they make it easier to provide a request body so you can upload data before retrieving the server's response. Additionally, upload tasks are supported in background sessions.
/// - Use ``URLSession``'s ``URLSession/downloadTask(with:)-1onj`` and related methods to create ``URLSessionDownloadTask`` instances. Download tasks download a resource directly to a file on disk. Download tasks are supported in any type of session.
/// - Use ``URLSession``'s ``URLSession/streamTask(withHostName:port:)`` or ``URLSession/streamTask(with:)`` to create ``URLSessionStreamTask`` instances. Stream tasks establish a TCP/IP connection from a host name and port or a net service object.
///
/// After you create a task, you start it by calling its ``resume()`` method. The session then maintains a strong reference to the task until the request finishes or fails; you don't need to maintain a reference to the task unless it's useful for your app's internal bookkeeping.
///
/// > Note:
/// > All task properties support key-value observing.
NS_SWIFT_SENDABLE
API_AVAILABLE(macos(10.9), ios(7.0), watchos(2.0), tvos(9.0))
@interface NSURLSessionTask : NSObject <NSCopying, NSProgressReporting>

/// An identifier uniquely identifying the task within a given session.
///
/// This value is unique only within the context of a single session; tasks in other sessions
/// may have the same `taskIdentifier` value.
@property (readonly)                 NSUInteger    taskIdentifier;

/// The original request object passed when the task was created.
///
/// This value is typically the same as the currently active request (`currentRequest`)
/// except when the server has responded to the initial request with a redirect to a
/// different URL.
@property (nullable, readonly, copy) NSURLRequest  *originalRequest;

/// The URL request object currently being handled by the task.
///
/// This value is typically the same as the initial request (`originalRequest`) except when
/// the server has responded to the initial request with a redirect to a different URL.
@property (nullable, readonly, copy) NSURLRequest  *currentRequest;

/// The server's response to the currently active request.
///
/// This object provides information about the request as provided by the server. This
/// information always includes the original URL. It may also include an expected length,
/// MIME type information, encoding information, a suggested filename, or a combination
/// of these.
@property (nullable, readonly, copy) NSURLResponse *response;

/// A delegate specific to the task.
///
/// This task-specific delegate receives messages from the task before the session's delegate
/// receives them. Methods not implemented on this delegate will still be forwarded to the
/// session delegate.
///
/// Cannot be modified after task resumes. Not supported on background session.
///
/// Delegate is strongly referenced until the task completes, after which it is reset to `nil`.
@property (nullable, retain) id <NSURLSessionTaskDelegate> delegate API_AVAILABLE(macos(12.0), ios(15.0), watchos(8.0), tvos(15.0));

/// A representation of the overall task progress.
///
/// It can be used for task progress tracking.
@property (readonly, strong) NSProgress *progress API_AVAILABLE(macos(10.13), ios(11.0), watchos(4.0), tvos(11.0));

/// The earliest date at which the network load should begin.
///
/// For tasks created from background `NSURLSession` instances, this property indicates that
/// the network load should not begin any earlier than this date. Setting this property does
/// not guarantee that the load will begin at the specified date, but only that it will not
/// begin sooner. If not specified, no start delay is used.
///
/// This property has no effect for tasks created from nonbackground sessions.
@property (nullable, copy) NSDate *earliestBeginDate API_AVAILABLE(macos(10.13), ios(11.0), watchos(4.0), tvos(11.0));

/// A best-guess upper bound on the number of bytes the client expects to send.
///
/// The value set for this property should account for the size of HTTP headers and body data or body stream. If no value is specified, the system uses `NSURLSessionTransferSizeUnknown` instead. This property is used by the system to optimize the scheduling of URL session tasks. Developers are strongly encouraged to provide an approximate upper bound, or an exact byte count, if possible, rather than accept the default.
@property int64_t countOfBytesClientExpectsToSend API_AVAILABLE(macos(10.13), ios(11.0), watchos(4.0), tvos(11.0));

/// A best-guess upper bound on the number of bytes the client expects to receive.
///
/// The value set for this property should account for the size of both HTTP response headers and the response body. If no value is specified, the system uses `NSURLSessionTransferSizeUnknown` instead. This property is used by the system to optimize the scheduling of URL session tasks. Developers are strongly encouraged to provide an approximate upper bound, or an exact byte count, if possible, rather than accept the default.
@property int64_t countOfBytesClientExpectsToReceive API_AVAILABLE(macos(10.13), ios(11.0), watchos(4.0), tvos(11.0));


/// The number of bytes that the task has sent to the server in the request body.
///
/// This byte count includes _only_ the length of the request body itself, not the request headers.
///
/// To be notified when this value changes, implement the `URLSession:task:didSendBodyData:totalBytesSent:totalBytesExpectedToSend:` delegate method.
@property (readonly) int64_t countOfBytesSent;

/// The number of bytes that the task has received from the server in the response body.
///
/// To be notified when this value changes, implement the `URLSession:dataTask:didReceiveData:` delegate method (for data and upload tasks) or the `URLSession:downloadTask:didWriteData:totalBytesWritten:totalBytesExpectedToWrite:` method (for download tasks).
@property (readonly) int64_t countOfBytesReceived;

/// The number of bytes that the task expects to send in the request body.
///
/// The URL loading system can determine the length of the upload data in three ways:
///
/// - From the length of the data object provided as the upload body.
/// - From the length of the file on disk provided as the upload body of an upload task (_not_ a download task).
/// - From the `Content-Length` in the request object, if you explicitly set it.
///
/// Otherwise, the value is `NSURLSessionTransferSizeUnknown` (`-1`) if you provided a stream or body data object, or zero (`0`) if you did not.
@property (readonly) int64_t countOfBytesExpectedToSend;

/// The number of bytes that the task expects to receive in the response body.
///
/// This value is determined based on the `Content-Length` header received from the server. If that header is absent, the value is `NSURLSessionTransferSizeUnknown`.
@property (readonly) int64_t countOfBytesExpectedToReceive;

/// An app-provided string value for the current task.
///
/// The system doesn't interpret this value; use it for whatever purpose you see fit. For example, you could store a description of the task for debugging purposes, or a key to track the task in your own data structures.
@property (nullable, copy) NSString *taskDescription;

/// Cancels the task.
///
/// This method returns immediately, marking the task as being canceled. Once a task is
/// marked as being canceled, `URLSession:task:didCompleteWithError:` will be sent to the
/// task delegate, passing an error in the domain `NSURLErrorDomain` with the code
/// `NSURLErrorCancelled`. A task may, under some circumstances, send messages to its
/// delegate before the cancelation is acknowledged.
///
/// This method may be called on a task that is suspended.
- (void)cancel;

/// The current state of the task---active, suspended, in the process of being canceled, or completed.
@property (readonly) NSURLSessionTaskState state;

/// An error object that indicates why the task failed.
///
/// This value is `nil` if the task is still active or if the transfer completed successfully.
@property (nullable, readonly, copy) NSError *error;

/// Temporarily suspends the task.
///
/// Suspending a task will prevent the `NSURLSession` from continuing to load data. There
/// may still be delegate calls made on behalf of this task (for instance, to report data
/// received while suspending) but no further transmissions will be made on behalf of the
/// task until `-resume` is sent. The timeout timer associated with the task will be
/// disabled while a task is suspended. `-suspend` and `-resume` are nestable.
- (void)suspend;

/// Resumes the task, if it is suspended.
///
/// Newly-initialized tasks begin in a suspended state, so you need to call this method
/// to start the task.
- (void)resume;

/// The relative priority at which you'd like a host to handle the task, specified as a floating point value between `0.0` (lowest priority) and `1.0` (highest priority).
///
/// To provide hints to a host on how to prioritize URL session tasks from your app, specify a priority for each task. Specifying a priority provides only a hint and does not guarantee performance. If you don't specify a priority, a URL session task has a priority of `NSURLSessionTaskPriorityDefault`, with a value of `0.5`.
///
/// There are three named priorities you can employ: `NSURLSessionTaskPriorityDefault`, `NSURLSessionTaskPriorityLow`, and `NSURLSessionTaskPriorityHigh`.
///
/// You can specify or change a task's priority at any time, but not all networking protocols respond to changes after a task has started. There is no API to let you determine the effective priority for a task from a host's perspective.
@property float priority API_AVAILABLE(macos(10.10), ios(8.0), watchos(2.0), tvos(9.0));

/// A Boolean value that determines whether to deliver a partial response body in increments.
///
/// Set this property to `true` to tell the task that the app would benefit from receiving a partial response body in increments. If the app can't process the response until it has all the data, set this property to `false`. Task performance may improve when this value is `false`, in which case the task only delivers data when complete.
///
/// This property defaults to `true`, except in the following cases which default to `false`:
///
/// - The task delivers results to a completion handler rather than to a delegate.
/// - The task is a download task.
@property BOOL prefersIncrementalDelivery API_AVAILABLE(macos(11.3), ios(14.5), watchos(7.4), tvos(14.5));


/// Initializes an empty URL session task.
///
/// Don't use this initializer directly. Instead, create tasks from a ``NSURLSession``.
- (instancetype)init API_DEPRECATED("Not supported", macos(10.9,10.15), ios(7.0,13.0), watchos(2.0,6.0), tvos(9.0,13.0));
/// Creates a new URL session task.
///
/// Don't call this method directly. Instead, create tasks from a ``NSURLSession``.
+ (instancetype)new API_DEPRECATED("Not supported", macos(10.9,10.15), ios(7.0,13.0), watchos(2.0,6.0), tvos(9.0,13.0));

@end

/// The default URL session task priority, used implicitly for any task you have not prioritized.
///
/// The floating point value of this constant is `0.5`.
FOUNDATION_EXPORT const float NSURLSessionTaskPriorityDefault API_AVAILABLE(macos(10.10), ios(8.0), watchos(2.0), tvos(9.0));
/// A low URL session task priority, with a floating point value above the minimum of `0` and below the default value.
FOUNDATION_EXPORT const float NSURLSessionTaskPriorityLow API_AVAILABLE(macos(10.10), ios(8.0), watchos(2.0), tvos(9.0));
/// A high URL session task priority, with a floating point value above the default value and below the maximum of `1.0`.
FOUNDATION_EXPORT const float NSURLSessionTaskPriorityHigh API_AVAILABLE(macos(10.10), ios(8.0), watchos(2.0), tvos(9.0));

/// A URL session task that returns downloaded data directly to the app in memory.
///
/// A ``URLSessionDataTask`` is a concrete subclass of ``URLSessionTask``. The methods in the ``URLSessionDataTask`` class are documented in ``URLSessionTask``.
///
/// A data task returns data directly to the app (in memory) as one or more `NSData` objects. When you use a data task:
///
/// - During upload of the body data (if your app provides any), the session periodically calls its delegate's ``URLSessionTaskDelegate/urlSession(_:task:didSendBodyData:totalBytesSent:totalBytesExpectedToSend:)`` method with status information.
/// - After receiving an initial response, the session calls its delegate's ``URLSessionDataDelegate/urlSession(_:dataTask:didReceive:completionHandler:)`` method to let you examine the status code and headers, and optionally convert the data task into a download task.
/// - During the transfer, the session calls its delegate's ``URLSessionDataDelegate/urlSession(_:dataTask:didReceive:)`` method to provide your app with the content as it arrives.
/// - Upon completion, the session calls its delegate's ``URLSessionDataDelegate/urlSession(_:dataTask:willCacheResponse:completionHandler:)`` method to let you determine whether the response should be cached.
///
/// For examples of using data tasks for fetching and uploading data, see <doc:fetching-website-data-into-memory> and <doc:uploading-data-to-a-website>.
NS_SWIFT_SENDABLE
API_AVAILABLE(macos(10.9), ios(7.0), watchos(2.0), tvos(9.0))
@interface NSURLSessionDataTask : NSURLSessionTask

- (instancetype)init API_DEPRECATED("Please use -[NSURLSession dataTaskWithRequest:] or other NSURLSession methods to create instances", macos(10.9,10.15), ios(7.0,13.0), watchos(2.0,6.0), tvos(9.0,13.0));
+ (instancetype)new API_DEPRECATED("Please use -[NSURLSession dataTaskWithRequest:] or other NSURLSession methods to create instances", macos(10.9,10.15), ios(7.0,13.0), watchos(2.0,6.0), tvos(9.0,13.0));

@end

/// A URL session task that uploads data to the network in a request body.
///
/// The ``URLSessionUploadTask`` class is a subclass of ``URLSessionDataTask``, which in turn is a concrete subclass of ``URLSessionTask``. The methods associated with the ``URLSessionUploadTask`` class are documented in ``URLSessionTask``.
///
/// Upload tasks are used for making HTTP requests that require a request body (such as `POST` or `PUT`). They behave similarly to data tasks, but you create them by calling different methods on the session that are designed to make it easier to provide the content to upload. As with data tasks, if the server provides a response, upload tasks return that response as one or more `NSData` objects in memory.
///
/// > Note:
/// > Unlike data tasks, you can use upload tasks to upload content in the background.
///
/// When you create an upload task, you provide a ``URLRequest`` instance that contains any additional headers that you might need to send alongside the upload, such as the content type, content disposition, and so on. In iOS, when you create an upload task for a file in a background session, the system copies that file to a temporary location and streams data from there.
///
/// While the upload is in progress, the task calls the session delegate's ``URLSessionTaskDelegate/urlSession(_:task:didSendBodyData:totalBytesSent:totalBytesExpectedToSend:)`` method periodically to provide you with status information.
///
/// When the upload phase of the request finishes, the task behaves like a data task, calling methods on the session delegate to provide you with the server's response—headers, status code, content data, and so on.
NS_SWIFT_SENDABLE
API_AVAILABLE(macos(10.9), ios(7.0), watchos(2.0), tvos(9.0))
@interface NSURLSessionUploadTask : NSURLSessionDataTask

- (instancetype)init API_DEPRECATED("Please use -[NSURLSession uploadTaskWithStreamedRequest:] or other NSURLSession methods to create instances", macos(10.9,10.15), ios(7.0,13.0), watchos(2.0,6.0), tvos(9.0,13.0));
+ (instancetype)new API_DEPRECATED("Please use -[NSURLSession uploadTaskWithStreamedRequest:] or other NSURLSession methods to create instances", macos(10.9,10.15), ios(7.0,13.0), watchos(2.0,6.0), tvos(9.0,13.0));

/// Cancels an upload and calls the completion handler with resume data for later use.
/// resumeData will be nil if the server does not support the latest resumable uploads
/// Internet-Draft from the HTTP Working Group, found at
/// https://datatracker.ietf.org/doc/draft-ietf-httpbis-resumable-upload/
///
/// - Parameter completionHandler: The completion handler to call when the upload has been successfully canceled.
- (void)cancelByProducingResumeData:(void (NS_SWIFT_SENDABLE ^)(NSData * _Nullable resumeData))completionHandler API_AVAILABLE(macos(14.0), ios(17.0), watchos(10.0), tvos(17.0));

@end

/// A URL session task that stores downloaded data to a file.
///
/// An ``URLSessionDownloadTask`` is a concrete subclass of ``URLSessionTask``, which provides most of the methods for this class.
///
/// Download tasks directly write the server's response data to a temporary file, providing your app with progress updates as data arrives from the server. When you use download tasks in background sessions, these downloads continue even when your app is in the suspended state or otherwise not running.
///
/// You can pause (cancel) download tasks and resume them later (assuming the server supports doing so). You can also resume downloads that failed because of network connectivity problems.
///
/// ### Download delegate behavior
///
/// When you use a download task, your delegate receives several callbacks unique to download scenarios.
///
/// - During download, the session periodically calls the delegate's ``URLSessionDownloadDelegate/urlSession(_:downloadTask:didWriteData:totalBytesWritten:totalBytesExpectedToWrite:)`` method with status information.
/// - Upon successful completion, the session calls the delegate's ``URLSessionDownloadDelegate/urlSession(_:downloadTask:didFinishDownloadingTo:)`` method or completion handler. In that method, you must either open the file for reading or move it to a permanent location in your app's sandbox container directory.
/// - Upon unsuccessful completion, the session calls the delegate's ``URLSessionTaskDelegate/urlSession(_:task:didCompleteWithError:)`` method or completion handler. The only errors your delegate receives through the `error` parameter are client-side errors, such as being unable to resolve the hostname or connect to the host. To check for server-side errors, inspect the ``URLSessionTask/response`` property of the `task` parameter received by this callback.
NS_SWIFT_SENDABLE
API_AVAILABLE(macos(10.9), ios(7.0), watchos(2.0), tvos(9.0))
@interface NSURLSessionDownloadTask : NSURLSessionTask

/// Cancels a download and calls the completion handler with resume data for later use.
///
/// If conditions will allow for resuming the download in the future, the callback will be
/// called with an opaque data blob, which may be used with `-downloadTaskWithResumeData:`
/// to attempt to resume the download. If resume data cannot be created, the completion
/// handler will be called with `nil` resumeData.
///
/// - Parameter completionHandler: The completion handler to call when the cancel operation
///   is complete. The `resumeData` parameter contains data that can be used to resume the
///   download at a later time, or `nil` if resuming is not possible.
- (void)cancelByProducingResumeData:(void (NS_SWIFT_SENDABLE ^)(NSData * _Nullable resumeData))completionHandler;


/// Initializes a download task.
///
/// Don't use this initializer to manually create download tasks. Instead, use the factory methods on ``NSURLSession`` to add tasks to an existing URL session.
- (instancetype)init API_DEPRECATED("Please use -[NSURLSession downloadTaskWithRequest:] or other NSURLSession methods to create instances", macos(10.9,10.15), ios(7.0,13.0), watchos(2.0,6.0), tvos(9.0,13.0));
/// Creates and initializes a download task.
///
/// Don't use this method to manually create download tasks. Instead, use the factory methods on ``NSURLSession`` to add tasks to an existing URL session.
+ (instancetype)new API_DEPRECATED("Please use -[NSURLSession downloadTaskWithRequest:] or other NSURLSession methods to create instances", macos(10.9,10.15), ios(7.0,13.0), watchos(2.0,6.0), tvos(9.0,13.0));

@end

/// A URL session task that is stream-based.
///
/// ``URLSessionStreamTask`` is a concrete subclass of ``URLSessionTask``. Many of the methods in the ``URLSessionStreamTask`` class are documented in ``URLSessionTask``.
///
/// The ``URLSessionStreamTask`` class provides an interface a TCP/IP connection created via ``URLSession``. Tasks may be created from an ``URLSession`` using the ``URLSession/streamTask(withHostName:port:)`` and ``URLSession/streamTask(with:)`` methods. They may also be created as a result of an ``URLSessionDataTask`` being upgraded via the HTTP `Upgrade:` response header and appropriate use of the ``URLSessionConfiguration/httpShouldUsePipelining`` option of ``URLSessionConfiguration``.
///
/// > Note:
/// > See [RFC 2817](https://tools.ietf.org/html/rfc2817) and [RFC 6455](https://tools.ietf.org/html/rfc6455) for information about the `Upgrade:` header.
///
/// A ``URLSessionStreamTask`` object performs asynchronous reads and writes, which are enqueued and executed serially, calling a handler upon completion being on the session delegate queue. If the task is canceled, all enqueued reads and writes will call their completion handlers with an appropriate error.
///
/// When working with APIs that accept ``Stream`` objects, you can create ``InputStream`` and ``OutputStream`` objects from an ``URLSessionStreamTask`` object by calling the ``captureStreams()`` method.
///
/// > Note:
/// > watchOS supports ``URLSessionStreamTask`` for specific use cases. For more details, see <doc://com.apple.documentation/documentation/technotes/tn3135-low-level-networking-on-watchos>.
NS_SWIFT_SENDABLE
API_AVAILABLE(macos(10.11), ios(9.0), watchos(2.0), tvos(9.0))
@interface NSURLSessionStreamTask : NSURLSessionTask

/// Reads minimum `minBytes`, or at most `maxBytes` bytes and invokes the completion handler
/// on the session's delegate queue with the data or an error.
///
/// If an error occurs, any outstanding reads will also fail, and new read requests will
/// error out immediately.
///
/// - Parameter minBytes: The minimum number of bytes to read.
/// - Parameter maxBytes: The maximum number of bytes to read.
/// - Parameter timeout: The timeout interval for the read operation.
/// - Parameter completionHandler: The completion handler to call when the read operation
///   completes.
- (void)readDataOfMinLength:(NSUInteger)minBytes maxLength:(NSUInteger)maxBytes timeout:(NSTimeInterval)timeout completionHandler:(void (NS_SWIFT_SENDABLE ^) (NSData * _Nullable_result data, BOOL atEOF, NSError * _Nullable error))completionHandler;

/// Writes the data completely to the underlying socket.
///
/// If all the bytes have not been written by the timeout, a timeout error will occur.
/// Note that invocation of the completion handler does not guarantee that the remote side
/// has received all the bytes, only that they have been written to the kernel.
///
/// - Parameter data: The data to write to the stream.
/// - Parameter timeout: The timeout interval for the write operation.
/// - Parameter completionHandler: The completion handler to call when the write operation
///   completes.
- (void)writeData:(NSData *)data timeout:(NSTimeInterval)timeout completionHandler:(void (NS_SWIFT_SENDABLE ^) (NSError * _Nullable error))completionHandler;

/// Completes any already enqueued reads and writes, then invokes the
/// `URLSession:streamTask:didBecomeInputStream:outputStream:` delegate message.
///
/// When that message is received, the task object is considered completed and will not
/// receive any more delegate messages.
- (void)captureStreams;

/// Enqueues a request to close the write end of the underlying socket.
///
/// All outstanding IO will complete before the write side of the socket is closed. The
/// server, however, may continue to write bytes back to the client, so best practice is
/// to continue reading from the server until you receive EOF.
- (void)closeWrite;

/// Enqueues a request to close the read side of the underlying socket.
///
/// All outstanding IO will complete before the read side is closed. You may continue
/// writing to the server.
- (void)closeRead;

/// Begins encrypted handshake.
///
/// The handshake begins after all pending IO has completed. TLS authentication callbacks
/// are sent to the session's `URLSession:task:didReceiveChallenge:completionHandler:`
/// delegate method.
- (void)startSecureConnection;

/// Completes any enqueued reads and writes, and closes the secure connection.
- (void)stopSecureConnection API_DEPRECATED("TLS cannot be disabled once it is enabled", macos(10.9,10.15), ios(7.0,13.0), watchos(2.0,6.0), tvos(9.0,13.0));


- (instancetype)init API_DEPRECATED("Please use -[NSURLSession streamTaskWithHostName:port:] or other NSURLSession methods to create instances", macos(10.9,10.15), ios(7.0,13.0), watchos(2.0,6.0), tvos(9.0,13.0));
+ (instancetype)new API_DEPRECATED("Please use -[NSURLSession streamTaskWithHostName:port:] or other NSURLSession methods to create instances", macos(10.9,10.15), ios(7.0,13.0), watchos(2.0,6.0), tvos(9.0,13.0));

@end

/// An enumeration of the types of messages sent and received.
typedef NS_ENUM(NSInteger, NSURLSessionWebSocketMessageType) {
    NSURLSessionWebSocketMessageTypeData = 0,
    NSURLSessionWebSocketMessageTypeString = 1,
} API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0));

/* The client can create a WebSocket message object that will be passed to the send calls
 * and will be delivered from the receive calls. The message can be initialized with data or string.
 * If initialized with data, the string property will be nil and vice versa.
 */
NS_SWIFT_SENDABLE
API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0))
@interface NSURLSessionWebSocketMessage : NSObject

/* Create a message with data type
 */
- (instancetype)initWithData:(NSData *)data NS_DESIGNATED_INITIALIZER;

/* Create a message with string type
 */
- (instancetype)initWithString:(NSString *)string NS_DESIGNATED_INITIALIZER;

@property (readonly) NSURLSessionWebSocketMessageType type;
@property (nullable, readonly, copy) NSData *data;
@property (nullable, readonly, copy) NSString *string;


- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

/// A code that indicates why a WebSocket connection closed.
///
/// The WebSocket close codes follow the close codes defined in [RFC 6455](https://tools.ietf.org/html/rfc6455#section-7.4.1).
typedef NS_ENUM(NSInteger, NSURLSessionWebSocketCloseCode)
{
    /// A code that indicates the connection is still open.
    NSURLSessionWebSocketCloseCodeInvalid =                             0,
    /// A code that indicates normal connection closure.
    NSURLSessionWebSocketCloseCodeNormalClosure =                    1000,
    /// A code that indicates an endpoint is going away.
    ///
    /// This code indicates situations like a server going down or a browser having navigated away from a page.
    NSURLSessionWebSocketCloseCodeGoingAway =                        1001,
    /// A code that indicates an endpoint terminated the connection due to a protocol error.
    NSURLSessionWebSocketCloseCodeProtocolError =                    1002,
    /// A code that indicates an endpoint terminated the connection after receiving a type of data it can't accept.
    ///
    /// An endpoint that only accepts text may send this close code if it receives a binary message.
    NSURLSessionWebSocketCloseCodeUnsupportedData =                  1003,
    /// A reserved code that indicates an endpoint expected a status code and didn't receive one.
    NSURLSessionWebSocketCloseCodeNoStatusReceived =                 1005,
    /// A reserved code that indicates the connection closed without a close control frame.
    NSURLSessionWebSocketCloseCodeAbnormalClosure =                  1006,
    /// A code that indicates the server terminated the connection because it received data inconsistent with the message's type.
    NSURLSessionWebSocketCloseCodeInvalidFramePayloadData =          1007,
    /// A code that indicates an endpoint terminated the connection because it received a message that violates its policy.
    ///
    /// This is a generic code for use when a more specific code is unavailable.
    NSURLSessionWebSocketCloseCodePolicyViolation =                  1008,
    /// A code that indicates an endpoint is terminating the connection because it received a message too big for it to process.
    NSURLSessionWebSocketCloseCodeMessageTooBig =                    1009,
    /// A code that indicates the client terminated the connection because the server didn't negotiate a required extension.
    ///
    /// RFC 6455 indicates the client should provide a close reason with a list of the needed extensions.
    NSURLSessionWebSocketCloseCodeMandatoryExtensionMissing =        1010,
    /// A code that indicates the server terminated the connection because it encountered an unexpected condition.
    NSURLSessionWebSocketCloseCodeInternalServerError =              1011,
    /// A reserved code that indicates the connection closed due to the failure to perform a TLS handshake.
    NSURLSessionWebSocketCloseCodeTLSHandshakeFailure =              1015,
} API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0));

/// A URL session task that communicates over the WebSockets protocol standard.
///
/// ``URLSessionWebSocketTask`` is a concrete subclass of ``URLSessionTask`` that provides a message-oriented transport protocol over TCP and TLS in the form of WebSocket framing. It follows the WebSocket Protocol defined in [RFC 6455](https://tools.ietf.org/html/rfc6455).
///
/// You create a ``URLSessionWebSocketTask`` with either a `ws:` or `wss:` URL. When creating the task, you can also provide a list of protocols to advertise during the handshake phase. Once the handshake completes, your app receives notifications through the session's ``URLSession/delegate``.
///
/// You send data with ``send(_:completionHandler:)`` and receive data with ``receive(completionHandler:)``. The task performs reads and writes asynchronously, and allows you to send and receive messages that contain both binary frames and UTF-8 encoded text frames. The task enqueues any reads or writes you perform prior to the handshake's completion, and executes them after the handshake completes.
///
/// ``URLSessionWebSocketTask`` supports redirection and authentication like other types of tasks do, using the methods in ``URLSessionTaskDelegate``. The WebSocket task calls the redirection and authentication delegate methods prior to completing the handshake. The WebSocket task also supports cookies, by storing cookies to the session configuration's ``URLSessionConfiguration/httpCookieStorage``, and attaches cookies to outgoing HTTP handshake requests.
///
/// > Note:
/// > watchOS supports ``URLSessionWebSocketTask`` for specific use cases. For more details, see <doc://com.apple.documentation/documentation/technotes/tn3135-low-level-networking-on-watchos>.
NS_SWIFT_SENDABLE
API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0))
@interface NSURLSessionWebSocketTask : NSURLSessionTask

/// Sends a WebSocket message, receiving the result in a completion handler.
///
/// If an error occurs while sending the message, any outstanding work also fails.
///
/// Note that invocation of the completion handler does not guarantee that the remote side
/// has received all the bytes, only that they have been written to the kernel.
///
/// - Parameters:
///   - message: The WebSocket message to send to the other endpoint.
///   - completionHandler: A closure that receives an `NSError` that indicates an error encountered while sending, or `nil` if no error occurred.
- (void)sendMessage:(NSURLSessionWebSocketMessage *)message completionHandler:(void (NS_SWIFT_SENDABLE ^)(NSError * _Nullable error))completionHandler;

/// Reads a WebSocket message once all the frames of the message are available.
///
/// If the task reaches the ``maximumMessageSize`` while buffering the frames, the receive call will
/// error out and all outstanding work will also fail, resulting in the end of the task.
///
/// - Parameters:
///   - completionHandler: A closure that receives the WebSocket message and an `NSError` that indicates an error encountered while receiving, or `nil` if no error occurred.
- (void)receiveMessageWithCompletionHandler:(void (NS_SWIFT_SENDABLE ^)(NSURLSessionWebSocketMessage * _Nullable message, NSError * _Nullable error))completionHandler;

/// Sends a ping frame from the client side.
///
/// The `pongReceiveHandler` is invoked when the client receives a pong from the server
/// endpoint. If a connection is lost or an error occurs before receiving the pong from
/// the endpoint, the handler will be invoked with an error. The handler will always be
/// called in the order in which the pings were sent.
///
/// - Parameter pongReceiveHandler: The handler to call when a pong is received or an error occurs.
- (void)sendPingWithPongReceiveHandler:(void (NS_SWIFT_SENDABLE ^)(NSError * _Nullable error))pongReceiveHandler;

/// Sends a close frame with the given close code.
///
/// An optional reason can be provided while sending the close frame. Simply calling
/// `-cancel` on the task will result in a cancellation frame being sent without any reason.
///
/// - Parameter closeCode: The close code to send.
/// - Parameter reason: An optional data object containing the close reason.
- (void)cancelWithCloseCode:(NSURLSessionWebSocketCloseCode)closeCode reason:(nullable NSData *)reason;

/// The maximum number of bytes to be buffered before erroring out.
///
/// This includes the sum of all bytes from continuation frames. Receive calls will error
/// out if this value is reached.
@property NSInteger maximumMessageSize;

/// A code that indicates the reason a connection closed.
///
/// You can retrieve the close code at any time. When the task is not yet closed,
/// this value is `NSURLSessionWebSocketCloseCodeInvalid`.
@property (readonly) NSURLSessionWebSocketCloseCode closeCode;

/// The close reason received from the server.
///
/// A task can be queried for its close reason at any point. A `nil` value indicates no
/// close reason or that the task is still running.
@property (nullable, readonly, copy) NSData *closeReason;


- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

/// Constants that specify the multipath service type to associate with a URL session.
///
/// The multipath service type determines whether Multipath TCP should be attempted and the conditions
/// for creating and switching between subflows. Using these service types requires the appropriate entitlement.
/// Any connection attempt will fail if the process does not have the required entitlement.
/// A primary interface is a generally less expensive interface in terms of both cost and power (such as Wi-Fi or Ethernet).
/// A secondary interface is more expensive (such as 3G or LTE).
typedef NS_ENUM(NSInteger, NSURLSessionMultipathServiceType)
{
    /// Specifies that Multipath TCP should not be used.
    ///
    /// Connections will use a single flow. This is the default value. No entitlement is required to set this value.
    NSURLSessionMultipathServiceTypeNone = 0,
    /// A Multipath TCP service that provides seamless handover between Wi-Fi and cellular in order to preserve the connection.
    ///
    /// Specify this option for long-lived or persistent connections. You must also set the Multipath entitlement in the Xcode Capabilities pane for your app.
    NSURLSessionMultipathServiceTypeHandover = 1,
    /// A service whereby Multipath TCP attempts to use the lowest-latency interface.
    ///
    /// Specify this option for latency-sensitive, low-volume connections that might use cellular data. You must also set the Multipath entitlement in the Xcode Capabilities pane for your app.
    NSURLSessionMultipathServiceTypeInteractive = 2,
    /// A service that aggregates the capacities of other Multipath options in an attempt to increase throughput and minimize latency.
    ///
    /// This option is available only for experimentation. Specify it for connections that use cellular data. You must also set the Multipath entitlement in the Xcode Capabilities pane for your app. To enable aggregation mode, open the Settings app on your development iPhone, navigate to Developer, and turn on Multipath Networking.
    NSURLSessionMultipathServiceTypeAggregate = 3
} API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, watchos, tvos) NS_SWIFT_NAME(URLSessionConfiguration.MultipathServiceType);

/// A configuration object that defines behavior and policies for a URL session.
///
/// An ``URLSessionConfiguration`` object defines the behavior and policies to use when uploading and downloading data using an ``URLSession`` object. When uploading or downloading data, creating a configuration object is always the first step you must take. You use this object to configure the timeout values, caching policies, connection requirements, and other types of information that you intend to use with your ``URLSession`` object.
///
/// It is important to configure your ``URLSessionConfiguration`` object appropriately before using it to initialize a session object. Session objects make a copy of the configuration settings you provide and use those settings to configure the session. Once configured, the session object ignores any changes you make to the ``URLSessionConfiguration`` object. If you need to modify your transfer policies, you must update the session configuration object and use it to create a new ``URLSession`` object.
///
/// > Note:
/// > In some cases, the policies defined in this configuration may be overridden by policies specified by an ``NSURLRequest`` object provided for a task. Any policy specified on the request object is respected unless the session's policy is more restrictive. For example, if the session configuration specifies that cellular networking should not be allowed, the ``NSURLRequest`` object cannot request cellular networking.
///
/// For more information about using configuration objects to create sessions, see ``URLSession``.
///
/// ### Types of session configurations
///
/// The behavior and capabilities of a URL session are largely determined by the kind of configuration used to create the session.
///
///
///
///
///
/// The singleton shared session (which has no configuration object) is for basic requests. It's not as customizable as sessions that you create, but it serves as a good starting point if you have very limited requirements. You access this session by calling the shared class method. See that method's discussion for more information about its limitations.
///
/// Default sessions behave much like the shared session (unless you customize them further), but let you obtain data incrementally using a delegate. You can create a default session configuration by calling the default method on the URLSessionConfiguration class.
///
/// Ephemeral sessions are similar to default sessions, but they don't write caches, cookies, or credentials to disk. You can create an ephemeral session configuration by calling the ephemeral method on the URLSessionConfiguration class.
///
/// Background sessions let you perform uploads and downloads of content in the background while your app isn't running. You can create a background session configuration by calling the backgroundSessionConfiguration(\_:) method on the URLSessionConfiguration class.
NS_SWIFT_SENDABLE
API_AVAILABLE(macos(10.9), ios(7.0), watchos(2.0), tvos(9.0))
@interface NSURLSessionConfiguration : NSObject <NSCopying>

/// A default session configuration object.
///
/// The default session configuration uses a persistent disk-based cache (except when the
/// result is downloaded to a file) and stores credentials in the user's keychain. It also
/// stores cookies (by default) in the same shared cookie store as `NSURLConnection` and
/// `NSURLDownload`.
///
/// Modifying the returned session configuration object does not affect any configuration
/// objects returned by future calls to this method, and does not change the default behavior
/// for existing sessions. It is therefore always safe to use the returned object as a
/// starting point for additional customization.
@property (class, readonly, strong) NSURLSessionConfiguration *defaultSessionConfiguration;

/// A session configuration that uses no persistent storage for caches, cookies, or credentials.
///
/// An ephemeral session configuration object is similar to a default session configuration
/// (see `defaultSessionConfiguration`), except that the corresponding session object doesn't
/// store caches, credential stores, or any session-related data to disk. Instead,
/// session-related data is stored in RAM. The only time an ephemeral session writes data to
/// disk is when you tell it to write the contents of a URL to a file.
///
/// The main advantage to using ephemeral sessions is privacy. By not writing potentially
/// sensitive data to disk, you make it less likely that the data will be intercepted and used
/// later. For this reason, ephemeral sessions are ideal for private browsing modes in web
/// browsers and other similar situations.
///
/// When your app invalidates the session, all ephemeral session data is purged automatically.
/// Additionally, in iOS, the in-memory cache isn't purged automatically when your app is
/// suspended but may be purged when your app is terminated or when the system experiences
/// memory pressure.
@property (class, readonly, strong) NSURLSessionConfiguration *ephemeralSessionConfiguration;

/// Creates a session configuration object that allows HTTP and HTTPS uploads or downloads to
/// be performed in the background.
///
/// Use this method to initialize a configuration object suitable for transferring data files
/// while the app runs in the background. A session configured with this object hands control
/// of the transfers over to the system, which handles the transfers in a separate process.
/// In iOS, this configuration makes it possible for transfers to continue even when the app
/// itself is suspended or terminated.
///
/// If an iOS app is terminated by the system and relaunched, the app can use the same
/// `identifier` to create a new configuration object and session and to retrieve the status
/// of transfers that were in progress at the time of termination. This behavior applies only
/// for normal termination of the app by the system. If the user terminates the app from the
/// multitasking screen, the system cancels all of the session's background transfers.
///
/// - Parameter identifier: The unique identifier for the configuration object. This parameter
///   must not be `nil` or an empty string.
/// - Returns: A configuration object that causes the system to perform upload and download
///   tasks in a separate process.
+ (NSURLSessionConfiguration *)backgroundSessionConfigurationWithIdentifier:(NSString *)identifier API_AVAILABLE(macos(10.10), ios(8.0), watchos(2.0), tvos(9.0));

/// The background session identifier of the configuration object.
///
/// The value of this property is set only when you use
/// `+backgroundSessionConfigurationWithIdentifier:` to create the configuration object.
/// The string uniquely identifies a background session object. In iOS, you use this string
/// in cases where the app was terminated while transfers were occurring in the background.
/// When the app relaunches, it uses the string to recreate the configuration and session
/// objects associated with the transfers.
@property (nullable, readonly, copy) NSString *identifier;

/// A predefined constant that determines when to return a response from the cache.
///
/// This property determines the request caching policy used by tasks within sessions based
/// on this configuration. The default value is `NSURLRequestUseProtocolCachePolicy`.
@property NSURLRequestCachePolicy requestCachePolicy;

/// The timeout interval to use when waiting for additional data.
///
/// This property determines the request timeout interval for all tasks within sessions based
/// on this configuration. The request timeout interval controls how long (in seconds) a task
/// should wait for additional data to arrive before giving up. The timer associated with this
/// value is reset whenever new data arrives. When the request timer reaches the specified
/// interval without receiving any new data, it triggers a timeout.
///
/// The default value is `60`.
///
/// > Important: Any upload or download tasks created by a background session are automatically
/// > retried if the original request fails due to a timeout. To configure how long an upload
/// > or download task should be allowed to be retried or transferred, use the
/// > `timeoutIntervalForResource` property.
@property NSTimeInterval timeoutIntervalForRequest;

/// The maximum amount of time that a resource request should be allowed to take.
///
/// This property determines the resource timeout interval for all tasks within sessions based
/// on this configuration. The resource timeout interval controls how long (in seconds) to
/// wait for an entire resource to transfer before giving up. The resource timer starts when
/// the request is initiated and counts until either the request completes or this timeout
/// interval is reached, whichever comes first.
///
/// The default value is 7 days.
@property NSTimeInterval timeoutIntervalForResource;

/// The type of network service for all tasks within network sessions to enable Cellular
/// Network Slicing.
@property NSURLRequestNetworkServiceType networkServiceType;

/// A Boolean value that determines whether connections should be made over a cellular network.
///
/// This property controls whether tasks in sessions based on this session configuration are
/// allowed to make connections over a cellular network.
///
/// The default value is `YES`.
@property BOOL allowsCellularAccess;

/// A Boolean value that indicates whether connections may use a network interface that the
/// system considers expensive.
///
/// The default value is `YES`.
@property BOOL allowsExpensiveNetworkAccess API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0));

/// A Boolean value that indicates whether connections may use the network when the user has
/// specified Low Data Mode.
///
/// The default value is `YES`.
@property BOOL allowsConstrainedNetworkAccess API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0));

/* allow request to route over ultra constrained networks. */
@property BOOL allowsUltraConstrainedNetworkAccess API_AVAILABLE(macos(26.1), ios(26.1), watchos(26.1), tvos(26.1), visionos(26.1));

/* requires requests from the session to be made with DNSSEC validation enabled. Defaults to NO. */
@property BOOL requiresDNSSECValidation API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0));

/// A Boolean value that indicates whether the session should wait for connectivity to become
/// available, or fail immediately.
///
/// Connectivity might be temporarily unavailable for several reasons. For example, a device
/// might only have a cellular connection when `allowsCellularAccess` is set to `NO`, or the
/// device might require a VPN connection but none is available. If the value of this property
/// is `YES` and sufficient connectivity is unavailable, the session calls the
/// `URLSession:taskIsWaitingForConnectivity:` delegate method and waits for connectivity.
///
/// If the value is `NO` and connectivity is unavailable, the connection fails immediately
/// with an error.
///
/// Default value is `NO`. Ignored by background sessions, as background sessions always
/// wait for connectivity.
@property BOOL waitsForConnectivity API_AVAILABLE(macos(10.13), ios(11.0), watchos(4.0), tvos(11.0));

/// A Boolean value that determines whether background tasks can be scheduled at the
/// discretion of the system for optimal performance.
///
/// For configuration objects created using `+backgroundSessionConfigurationWithIdentifier:`,
/// use this property to give the system control over when transfers should occur. This
/// property is ignored for configuration objects created using other methods.
///
/// When transferring large amounts of data, you are encouraged to set this to `YES`. Doing so
/// lets the system schedule those transfers at times that are more optimal for the device.
/// The default value is `NO`.
@property (getter=isDiscretionary) BOOL discretionary API_AVAILABLE(macos(10.10), ios(7.0), watchos(2.0), tvos(9.0));

/// The identifier for the shared container into which files in background URL sessions should
/// be downloaded.
///
/// To create a URL session for use by an app extension, set this property to a valid
/// identifier for a container shared between the app extension and its containing app.
///
/// > Important: If you try to create a URL session from your app extension but fail to set
/// > this property to a valid value, the URL session is invalidated upon creation.
@property (nullable, copy) NSString *sharedContainerIdentifier API_AVAILABLE(macos(10.10), ios(8.0), watchos(2.0), tvos(9.0));

/// A Boolean value that indicates whether the app should be resumed or launched in the
/// background when transfers finish.
///
/// For configuration objects created using `+backgroundSessionConfigurationWithIdentifier:`,
/// you can use this property to control the launching behavior for an iOS app. This property
/// is ignored for configuration objects created using other methods.
///
/// The default value is `YES`. When `YES`, the system automatically wakes up or launches the
/// iOS app in the background when the session's tasks finish or require authentication.
///
/// > Note: macOS apps based on AppKit do not support background launch.
@property BOOL sessionSendsLaunchEvents API_AVAILABLE(macos(11.0), ios(7.0), watchos(2.0), tvos(9.0));

/// A dictionary containing information about the proxy to use within this session.
///
/// Prefer using `proxyConfigurations`, which supports secure proxy and relay types.
///
/// The default value is `NULL`, which means that tasks use the default system settings.
@property (nullable, copy) NSDictionary *connectionProxyDictionary;

/// The minimum TLS protocol to accept during protocol negotiation.
@property SSLProtocol TLSMinimumSupportedProtocol API_DEPRECATED_WITH_REPLACEMENT("TLSMinimumSupportedProtocolVersion", macos(10.9, API_TO_BE_DEPRECATED), ios(7.0, API_TO_BE_DEPRECATED), watchos(2.0, API_TO_BE_DEPRECATED), tvos(9.0, API_TO_BE_DEPRECATED));

/// The maximum TLS protocol version that the client should request when making connections
/// in this session.
@property SSLProtocol TLSMaximumSupportedProtocol API_DEPRECATED_WITH_REPLACEMENT("TLSMaximumSupportedProtocolVersion", macos(10.9, API_TO_BE_DEPRECATED), ios(7.0, API_TO_BE_DEPRECATED), watchos(2.0, API_TO_BE_DEPRECATED), tvos(9.0, API_TO_BE_DEPRECATED));

/// The minimum TLS protocol version that the client should accept when making connections
/// in this session.
@property tls_protocol_version_t TLSMinimumSupportedProtocolVersion API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0));

/// The maximum TLS protocol version that the client should request when making connections
/// in this session.
@property tls_protocol_version_t TLSMaximumSupportedProtocolVersion API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0));

/// A Boolean value that determines whether the session should use HTTP pipelining.
///
/// The default value is `NO`.
@property BOOL HTTPShouldUsePipelining API_DEPRECATED("Only supported in the classic loader, please adopt HTTP/2 and HTTP/3 instead", macos(10.9,15.4), ios(7.0,18.4), watchos(2.0,11.4), tvos(9.0,18.4), visionos(1.0,2.4));

/// A Boolean value that determines whether requests should contain cookies from the cookie store.
///
/// The default value is `YES`.
@property BOOL HTTPShouldSetCookies;

/// A policy constant that determines when cookies should be accepted.
///
/// This property determines the cookie accept policy for all tasks within sessions based on
/// this configuration.
@property NSHTTPCookieAcceptPolicy HTTPCookieAcceptPolicy;

/// A dictionary of additional headers to send with requests.
///
/// This property specifies additional headers that are added to all tasks within sessions
/// based on this configuration. If the same header appears in both this dictionary and the
/// request object (where applicable), the request object's value takes precedence.
///
/// An `NSURLSession` object is designed to handle various aspects of the HTTP protocol for
/// you. As a result, you should not modify the following headers: `Authorization`,
/// `Connection`, `Host`, `Proxy-Authenticate`, `Proxy-Authorization`, `WWW-Authenticate`.
@property (nullable, copy) NSDictionary *HTTPAdditionalHeaders;

/// The maximum number of simultaneous connections to make to a given host.
///
/// This limit is per session, so if you use multiple sessions, your app as a whole may
/// exceed this limit. The default value is `6`.
@property NSInteger HTTPMaximumConnectionsPerHost;

/// The cookie store for storing cookies within this session.
///
/// To disable cookie storage, set this property to `nil`.
///
/// For default and background sessions, the default value is the shared cookie storage object.
/// For ephemeral sessions, the default value is a private cookie storage object that stores
/// data in memory only, and is destroyed when you invalidate the session.
@property (nullable, retain) NSHTTPCookieStorage *HTTPCookieStorage;

/// A credential store that provides credentials for authentication.
///
/// To not use a credential store, set this property to `nil`.
///
/// For default and background sessions, the default value is the shared credential storage
/// object. For ephemeral sessions, the default value is a private credential store object
/// that stores data in memory only, and is destroyed when you invalidate the session.
@property (nullable, retain) NSURLCredentialStorage *URLCredentialStorage;

/// The URL cache for providing cached responses to requests within the session.
///
/// To disable caching, set this property to `nil`.
///
/// For default sessions, the default value is the shared URL cache object.
/// For background sessions, the default value is `nil`.
/// For ephemeral sessions, the default value is a private cache object that stores data
/// in memory only, and is destroyed when you invalidate the session.
@property (nullable, retain) NSURLCache *URLCache;

/// A Boolean value that indicates whether TCP connections should be kept open when the app
/// moves to the background.
@property BOOL shouldUseExtendedBackgroundIdleMode API_DEPRECATED("Not supported", macos(10.11,15.4), ios(9.0,18.4), watchos(2.0,11.4), tvos(9.0,18.4), visionos(1.0,2.4));

/// An array of extra protocol subclasses that handle requests in a session.
///
/// Use this array to extend the default set of common networking protocols available for use
/// by a session with one or more custom protocols that you define. You should not use
/// `+[NSURLProtocol registerClass:]`, as that method will register your class with the
/// default session rather than with an instance of `NSURLSession`.
///
/// > Note: You cannot use custom `NSURLProtocol` subclasses in conjunction with background
/// > sessions.
@property (nullable, copy) NSArray<Class> *protocolClasses;

/// A service type that specifies the Multipath TCP connection policy for transmitting data over Wi-Fi and cellular interfaces.
///
/// Multipath TCP, defined by the IETF in [RFC 6824](https://tools.ietf.org/html/rfc6824), is an extension to TCP that permits multiple interfaces to transmit a single data stream. This capability allows a seamless handover from Wi-Fi to cellular, aimed at making both interfaces more efficient and improving the user experience.
///
/// The default value is `NSURLSessionMultipathServiceTypeNone`, meaning Multipath TCP is
/// disabled. You can also select handover mode, which provides seamless handover between
/// Wi-Fi and cellular.
///
/// Multipath TCP requires server support. Resources for Linux-based systems are available at [https://mptcp.dev](https://mptcp.dev).
@property NSURLSessionMultipathServiceType multipathServiceType API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, watchos, tvos);

/*
 * Uses the classic network loader.
 *
 * NOTE: FTP and HTTP/1 pipelining are only supported in the classic loading mode.
 *
 * Defaults to YES. The default may be NO in a future OS update.
 */
@property BOOL usesClassicLoadingMode API_AVAILABLE(macos(15.4), ios(18.4), watchos(11.4), tvos(18.4), visionos(2.4));

/*
 * Enables HTTP/3 0-RTT early data transmission of safe requests (GET or HEAD
 * requests).
 *
 * WARNING: Inclusion in TLS early data changes the security guarantees offered
 * by TLS.
 *
 * Requests sent in early data are not covered by anti-replay security
 * protections. Early data must be idempotent and the impact of adversarial
 * replays must be carefully evaluated, as the data may be replayed. Early data
 * also does not provide full forward secrecy; data transmitted is more
 * susceptible to data breach and security compromise of the server, even if
 * the breach happens after the data was transmitted.
 *
 * See Section 8 of RFC8446 for more details.
 *
 * https://datatracker.ietf.org/doc/html/rfc8446#section-8
 *
 * See RFC8470 for additional discussion and security considerations.
 *
 * https://datatracker.ietf.org/doc/html/rfc8470
 *
 * If these risks are acceptable for your use case, set this property to YES.
 * If unsure, NO is the safest option.
 *
 * NOTE: Not supported in the classic loading mode.
 *
 * Defaults to NO.
 */
@property BOOL enablesEarlyData API_AVAILABLE(macos(26.0), ios(26.0), watchos(26.0), tvos(26.0), visionos(26.0));


/// Creates an empty session configuration.
///
/// @DeprecationSummary {
///     Use ``NSURLSessionConfiguration/defaultSessionConfiguration`` or other class methods to create instances.
/// }
- (instancetype)init API_DEPRECATED("Please use NSURLSessionConfiguration.defaultSessionConfiguration or other class methods to create instances", macos(10.9,10.15), ios(7.0,13.0), watchos(2.0,6.0), tvos(9.0,13.0));
+ (instancetype)new API_DEPRECATED("Please use NSURLSessionConfiguration.defaultSessionConfiguration or other class methods to create instances", macos(10.9,10.15), ios(7.0,13.0), watchos(2.0,6.0), tvos(9.0,13.0));

@end

/// The action to take on a delayed URL session task.
///
/// The values of this enumeration indicate how to handle a task with a delayed start time (as set with the ``URLSessionTask/earliestBeginDate`` property). When the task is ready to start, it calls the ``URLSessionTaskDelegate/urlSession(_:task:willBeginDelayedRequest:completionHandler:)`` method of ``URLSessionTaskDelegate``. The implementation of this method must call the provided completion handler, passing in one case of this enumeration as the first argument. If the `useNewRequest` disposition is used for the first argument, the caller must also provide a new ``NSURLRequest`` as the second argument.
typedef NS_ENUM(NSInteger, NSURLSessionDelayedRequestDisposition) {
    /// A disposition indicating that the task should proceed with the original request.
    NSURLSessionDelayedRequestContinueLoading = 0,
    /// A disposition indicating that the task should use a new request to perform the network load.
    NSURLSessionDelayedRequestUseNewRequest = 1,
    /// A disposition indicating that the task should be canceled.
    NSURLSessionDelayedRequestCancel = 2,
} NS_SWIFT_NAME(URLSession.DelayedRequestDisposition) API_AVAILABLE(macos(10.13), ios(11.0), watchos(4.0), tvos(11.0));

/// Constants passed by session or task delegates to the provided continuation block in response to an authentication challenge.
typedef NS_ENUM(NSInteger, NSURLSessionAuthChallengeDisposition) {
    /// Use the specified credential, which may be `nil`.
    NSURLSessionAuthChallengeUseCredential = 0,
    /// Use the default handling for the challenge as though this delegate method were not implemented. The provided credential parameter is ignored.
    NSURLSessionAuthChallengePerformDefaultHandling = 1,
    /// Cancel the entire request. The provided credential parameter is ignored.
    NSURLSessionAuthChallengeCancelAuthenticationChallenge = 2,
    /// Reject this challenge, and call the authentication delegate method again with the next authentication protection space. The provided credential parameter is ignored.
    ///
    /// This disposition is only appropriate in fairly unusual situations. For example, a Windows server might use both `NSURLAuthenticationMethodNegotiate` and `NSURLAuthenticationMethodNTLM`. If your app can only handle NTLM, you would want to reject the Negotiate challenge, in order to then receive the queued NTLM challenge. However, most apps won't face this scenario, and if you cannot provide a credential for a certain authentication method, you should usually fall back to the `performDefaultHandling` disposition instead.
    NSURLSessionAuthChallengeRejectProtectionSpace = 3,
} API_AVAILABLE(macos(10.9), ios(7.0), watchos(2.0), tvos(9.0));


/// Constants indicating how a data or upload session should proceed after receiving the initial headers.
///
/// When a data or upload task first receives a response, it calls the ``URLSessionDataDelegate/urlSession(_:dataTask:didReceive:completionHandler:)`` method of ``URLSessionDataDelegate``. Implement this method to inspect the received ``URLResponse`` and then call the provided completion handler. The first parameter to the completion handler is of this type, a disposition that tells the task how to proceed.
typedef NS_ENUM(NSInteger, NSURLSessionResponseDisposition) {
    /// Cancel the load.
    ///
    /// Using this disposition is equivalent to calling `cancel` on the task.
    NSURLSessionResponseCancel = 0,
    /// Allow the load operation to continue.
    NSURLSessionResponseAllow = 1,
    /// Convert the response for this request to use a download task.
    ///
    /// When used with the completion handler from `URLSession:dataTask:didReceiveResponse:completionHandler:`, this disposition converts the data task to a download task, resulting in the delegate's `URLSession:dataTask:didBecomeDownloadTask:` being called with the new download task that supersedes the current task.
    NSURLSessionResponseBecomeDownload = 2,
    /// Convert the response for this request to use a stream task.
    ///
    /// When used with the completion handler from `URLSession:dataTask:didReceiveResponse:completionHandler:`, this disposition converts the task to a stream task, resulting in the delegate's `URLSession:dataTask:didBecomeStreamTask:` being called with the new stream task that supersedes the current task.
    NSURLSessionResponseBecomeStream API_AVAILABLE(macos(10.11), ios(9.0), watchos(2.0), tvos(9.0)) = 3,
} API_AVAILABLE(macos(10.9), ios(7.0), watchos(2.0), tvos(9.0));

/*
 * NSURLSessionDelegate specifies the methods that a session delegate
 * may respond to.  There are both session specific messages (for
 * example, connection based auth) as well as task based messages.
 */

/// A protocol that defines methods that URL session instances call on their delegates to handle session-level events, like session life cycle changes.
///
/// In addition to the methods defined in this protocol, most delegates should also implement some or all of the methods in the ``URLSessionTaskDelegate``, ``URLSessionDataDelegate``, and ``URLSessionDownloadDelegate`` protocols to handle task-level events. These include events like the beginning and end of individual tasks, and periodic progress updates from data or download tasks.
///
/// > Note:
/// > Your ``URLSession`` object doesn't need to have a delegate. If no delegate is assigned, a system-provided delegate is used, and you must provide a completion callback to obtain the data.
NS_SWIFT_SENDABLE
API_AVAILABLE(macos(10.9), ios(7.0), watchos(2.0), tvos(9.0))
@protocol NSURLSessionDelegate <NSObject>
@optional

/// The last message a session receives. A session will only become invalid because of a
/// systemic error or when it has been explicitly invalidated, in which case the error
/// parameter will be `nil`.
- (void)URLSession:(NSURLSession *)session didBecomeInvalidWithError:(nullable NSError *)error;

/// Handles a connection-level authentication challenge.
///
/// If implemented, when a connection level authentication challenge has occurred, this
/// delegate will be given the opportunity to provide authentication credentials to the
/// underlying connection. Some types of authentication will apply to more than one request
/// on a given connection to a server (SSL Server Trust challenges). If this delegate message
/// is not implemented, the behavior will be to use the default handling, which may involve
/// user interaction.
- (void)URLSession:(NSURLSession *)session didReceiveChallenge:(NSURLAuthenticationChallenge *)challenge
                                             completionHandler:(void (NS_SWIFT_SENDABLE ^)(NSURLSessionAuthChallengeDisposition disposition, NSURLCredential * _Nullable credential))completionHandler;

/// Tells the delegate that all messages previously enqueued for this session have been
/// delivered.
///
/// If an application has received an
/// `-application:handleEventsForBackgroundURLSession:completionHandler:` message, the session
/// delegate will receive this message to indicate that all messages previously enqueued for
/// this session have been delivered. At this time it is safe to invoke the previously stored
/// completion handler, or to begin any internal updates that will result in invoking the
/// completion handler.
- (void)URLSessionDidFinishEventsForBackgroundURLSession:(NSURLSession *)session API_AVAILABLE(macos(11.0), ios(7.0), watchos(2.0), tvos(9.0));

@end

/*
 * Messages related to the operation of a specific task.
 */
API_AVAILABLE(macos(10.9), ios(7.0), watchos(2.0), tvos(9.0))
/// A protocol that defines methods that URL session instances call on their delegates to handle task-level events.
///
/// You use this protocol in one of two ways, depending on how you use a ``URLSession``:
///
/// - If you create tasks with Swift's `async`-`await` syntax, using methods like ``URLSession/bytes(for:delegate:)`` and ``URLSession/data(for:delegate:)``, you pass a `delegate` argument of this type. The delegate receives callbacks for things like task progress, while the call point awaits the completion of the task.
/// - If you add tasks to the session with methods like ``URLSession/dataTask(with:)-10dy7`` and ``URLSession/downloadTask(with:)-1onj``, then you implement this protocol's methods in a ``URLSession/delegate`` you set on the session. This session delegate may also implement other protocols as appropriate, like ``URLSessionDownloadDelegate`` and ``URLSessionDataDelegate``. You can also assign a delegate of this type directly to the task to intercept callbacks before the task delivers them to the session's delegate.
///
/// > Note:
/// > Your ``URLSession`` object doesn't need to have a delegate. If you don't assign a delegate, the session uses a system-provided delegate. In this case, you must provide a completion callback or use the Swift `async`-`await` methods to obtain the data.
@protocol NSURLSessionTaskDelegate <NSURLSessionDelegate>
@optional

/* Notification that a task has been created.  This method is the first message
 * a task sends, providing a place to configure the task before it is resumed.
 *
 * This delegate callback is *NOT* dispatched to the delegate queue.  It is
 * invoked synchronously before the task creation method returns.
 */
- (void)URLSession:(NSURLSession *)session didCreateTask:(NSURLSessionTask *)task
    API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0));

/// Tells the delegate that the system is ready to begin work for a task with a delayed start
/// time set (using the `earliestBeginDate` property).
///
/// The completionHandler must be invoked in order for loading to proceed. The disposition
/// provided to the completion handler continues the load with the original request provided
/// to the task, replaces the request with the specified task, or cancels the task. If this
/// delegate is not implemented, loading will proceed with the original request.
- (void)URLSession:(NSURLSession *)session task:(NSURLSessionTask *)task
                        willBeginDelayedRequest:(NSURLRequest *)request
                              completionHandler:(void (NS_SWIFT_SENDABLE ^)(NSURLSessionDelayedRequestDisposition disposition, NSURLRequest * _Nullable newRequest))completionHandler
    API_AVAILABLE(macos(10.13), ios(11.0), watchos(4.0), tvos(11.0));

/// Tells the delegate that a task cannot start the network loading process because the
/// current network connectivity is not available or sufficient for the task's request.
///
/// This delegate will be called at most one time per task, and is only called if the
/// `waitsForConnectivity` property in the `NSURLSessionConfiguration` has been set to `YES`.
///
/// This delegate callback will never be called for background sessions, because the
/// `waitsForConnectivity` property is ignored by those sessions.
- (void)URLSession:(NSURLSession *)session taskIsWaitingForConnectivity:(NSURLSessionTask *)task
    API_AVAILABLE(macos(10.13), ios(11.0), watchos(4.0), tvos(11.0));

/// Tells the delegate that an HTTP request is attempting to perform a redirection to a
/// different URL.
///
/// You must invoke the completion routine to allow the redirection, allow the redirection
/// with a modified request, or pass `nil` to the completionHandler to cause the body of the
/// redirection response to be delivered as the payload of this request. The default is to
/// follow redirections.
///
/// For tasks in background sessions, redirections will always be followed and this method
/// will not be called.
- (void)URLSession:(NSURLSession *)session task:(NSURLSessionTask *)task
                     willPerformHTTPRedirection:(NSHTTPURLResponse *)response
                                     newRequest:(NSURLRequest *)request
                              completionHandler:(void (NS_SWIFT_SENDABLE ^)(NSURLRequest * _Nullable))completionHandler;

/// Tells the delegate that the task has received a request-specific authentication challenge.
///
/// If this delegate is not implemented, the session specific authentication challenge will
/// *NOT* be called and the behavior will be the same as using the default handling
/// disposition.
- (void)URLSession:(NSURLSession *)session task:(NSURLSessionTask *)task
                            didReceiveChallenge:(NSURLAuthenticationChallenge *)challenge
                              completionHandler:(void (NS_SWIFT_SENDABLE ^)(NSURLSessionAuthChallengeDisposition disposition, NSURLCredential * _Nullable credential))completionHandler;

/// Tells the delegate that a task requires a new, unopened body stream.
///
/// This may be necessary when authentication has failed for any request that involves a
/// body stream.
- (void)URLSession:(NSURLSession *)session task:(NSURLSessionTask *)task
                              needNewBodyStream:(void (NS_SWIFT_SENDABLE ^)(NSInputStream * _Nullable bodyStream))completionHandler NS_SWIFT_ASYNC_NAME(urlSession(_:needNewBodyStreamForTask:));

/// Tells the delegate if a task requires a new body stream starting from the given offset. This may be
/// necessary when resuming a failed upload task.
///
/// - Parameter session: The session containing the task that needs a new body stream from the given offset.
/// - Parameter task: The task that needs a new body stream.
/// - Parameter offset: The starting offset required for the body stream.
/// - Parameter completionHandler: A completion handler that your delegate method should call with the new body stream.
- (void)URLSession:(NSURLSession *)session task:(NSURLSessionTask *)task
                    needNewBodyStreamFromOffset:(int64_t)offset
                              completionHandler:(void (NS_SWIFT_SENDABLE ^)(NSInputStream * _Nullable bodyStream))completionHandler NS_SWIFT_NAME(urlSession(_:task:needNewBodyStreamFrom:completionHandler:)) NS_SWIFT_ASYNC_NAME(urlSession(_:needNewBodyStreamForTask:from:)) API_AVAILABLE(macos(14.0), ios(17.0), watchos(10.0), tvos(17.0));

/// Periodically informs the delegate of the upload progress.
///
/// This information is also available as properties of the task.
- (void)URLSession:(NSURLSession *)session task:(NSURLSessionTask *)task
                                didSendBodyData:(int64_t)bytesSent
                                 totalBytesSent:(int64_t)totalBytesSent
                       totalBytesExpectedToSend:(int64_t)totalBytesExpectedToSend;

/* Sent for each informational response received except 101 switching protocols.
 */
- (void)URLSession:(NSURLSession *)session task:(NSURLSessionTask *)task didReceiveInformationalResponse:(NSHTTPURLResponse *)response API_AVAILABLE(macos(14.0), ios(17.0), watchos(10.0), tvos(17.0));

/// Tells the delegate that complete statistics information has been collected for the task.
- (void)URLSession:(NSURLSession *)session task:(NSURLSessionTask *)task didFinishCollectingMetrics:(NSURLSessionTaskMetrics *)metrics API_AVAILABLE(macosx(10.12), ios(10.0), watchos(3.0), tvos(10.0));

/// Tells the delegate that the task finished transferring data.
///
/// `error` may be `nil`, which implies that no error occurred and this task is complete.
- (void)URLSession:(NSURLSession *)session task:(NSURLSessionTask *)task
                           didCompleteWithError:(nullable NSError *)error;

@end

/// A protocol that defines methods that URL session instances call on their delegates to handle task-level events specific to data and upload tasks.
///
/// Your session delegate should also implement the methods in the ``URLSessionTaskDelegate`` protocol to handle task-level events that are common to all task types, and methods in the ``URLSessionDelegate`` protocol to handle session-level events.
///
/// > Note:
/// > A ``URLSession`` object need not have a delegate. If no delegate is assigned, when you create tasks in that session, you must provide a completion handler block to obtain the data.
/// >
/// > Completion handler blocks are primarily intended as an alternative to using a custom delegate. If you create a task using a method that takes a completion handler block, the delegate methods for response and data delivery are not called.
API_AVAILABLE(macos(10.9), ios(7.0), watchos(2.0), tvos(9.0))
@protocol NSURLSessionDataDelegate <NSURLSessionTaskDelegate>
@optional
/// Tells the delegate that the task has received a response and no further messages will be
/// received until the completion block is called.
///
/// The disposition allows you to cancel a request or to turn a data task into a download
/// task. This delegate message is optional - if you do not implement it, you can get the
/// response as a property of the task.
///
/// This method will not be called for background upload tasks (which cannot be converted
/// to download tasks).
- (void)URLSession:(NSURLSession *)session dataTask:(NSURLSessionDataTask *)dataTask
                                 didReceiveResponse:(NSURLResponse *)response
                                  completionHandler:(void (NS_SWIFT_SENDABLE ^)(NSURLSessionResponseDisposition disposition))completionHandler;

/// Tells the delegate that a data task has become a download task.
///
/// No future messages will be sent to the data task.
- (void)URLSession:(NSURLSession *)session dataTask:(NSURLSessionDataTask *)dataTask
                              didBecomeDownloadTask:(NSURLSessionDownloadTask *)downloadTask;

/// Tells the delegate that a data task has become a bidirectional stream task.
///
/// No future messages will be sent to the data task. The newly created streamTask will
/// carry the original request and response as properties.
- (void)URLSession:(NSURLSession *)session dataTask:(NSURLSessionDataTask *)dataTask
                                didBecomeStreamTask:(NSURLSessionStreamTask *)streamTask
    API_AVAILABLE(macos(10.11), ios(9.0), watchos(2.0), tvos(9.0));

/// Tells the delegate that data is available for the delegate to consume.
///
/// As the data may be discontiguous, you should use `[NSData enumerateByteRangesUsingBlock:]`
/// to access it.
- (void)URLSession:(NSURLSession *)session dataTask:(NSURLSessionDataTask *)dataTask
                                     didReceiveData:(NSData *)data;

/// Asks the delegate whether the data (or upload) task should store the response in the cache.
///
/// Invoke the completion routine with a valid `NSCachedURLResponse` to allow the resulting
/// data to be cached, or pass `nil` to prevent caching. Note that there is no guarantee
/// that caching will be attempted for a given resource, and you should not rely on this
/// message to receive the resource data.
- (void)URLSession:(NSURLSession *)session dataTask:(NSURLSessionDataTask *)dataTask
                                  willCacheResponse:(NSCachedURLResponse *)proposedResponse
                                  completionHandler:(void (NS_SWIFT_SENDABLE ^)(NSCachedURLResponse * _Nullable cachedResponse))completionHandler;

@end

/// A protocol that defines methods that URL session instances call on their delegates to handle task-level events specific to download tasks.
///
/// In addition to the methods in this protocol, be sure to implement the methods in the ``URLSessionTaskDelegate`` and ``URLSessionDelegate`` protocols to handle events common to all task types and session-level events, respectively.
///
/// > Note:
/// > An ``URLSession`` object need not have a delegate. If no delegate is assigned, a system-provided delegate is used, and you must provide a completion callback to obtain the data.
API_AVAILABLE(macos(10.9), ios(7.0), watchos(2.0), tvos(9.0))
@protocol NSURLSessionDownloadDelegate <NSURLSessionTaskDelegate>

/// Tells the delegate that a download task has completed a download.
///
/// The delegate should copy or move the file at the given location to a new location as it
/// will be removed when the delegate message returns. `URLSession:task:didCompleteWithError:`
/// will still be called.
- (void)URLSession:(NSURLSession *)session downloadTask:(NSURLSessionDownloadTask *)downloadTask
                              didFinishDownloadingToURL:(NSURL *)location;

@optional
/// Periodically informs the delegate of download progress.
- (void)URLSession:(NSURLSession *)session downloadTask:(NSURLSessionDownloadTask *)downloadTask
                                           didWriteData:(int64_t)bytesWritten
                                      totalBytesWritten:(int64_t)totalBytesWritten
                              totalBytesExpectedToWrite:(int64_t)totalBytesExpectedToWrite;

/// Tells the delegate that a download task has been resumed.
///
/// If a download failed with an error, the `userInfo` dictionary of the error will contain
/// an `NSURLSessionDownloadTaskResumeData` key, whose value is the resume data.
- (void)URLSession:(NSURLSession *)session downloadTask:(NSURLSessionDownloadTask *)downloadTask
                                      didResumeAtOffset:(int64_t)fileOffset
                                     expectedTotalBytes:(int64_t)expectedTotalBytes;

@end

/// A protocol that defines methods that URL session instances call on their delegates to handle task-level events specific to stream tasks.
///
/// In addition to these methods, be sure to implement the methods in the ``URLSessionTaskDelegate`` and ``URLSessionDelegate`` protocols to handle events common to all task types and session-level events, respectively.
///
/// > Note: A ``URLSession`` object need not have a delegate. If no delegate is assigned, a system-provided delegate is used, and you must provide a completion callback to obtain the data.
API_AVAILABLE(macos(10.11), ios(9.0), watchos(2.0), tvos(9.0))
@protocol NSURLSessionStreamDelegate <NSURLSessionTaskDelegate>
@optional

/// Indicates that the read side of a connection has been closed.
///
/// Any outstanding reads complete, but future reads will immediately fail. This may be sent
/// even when no reads are in progress. However, when this delegate message is received,
/// there may still be bytes available. You only know that no more bytes are available when
/// you are able to read until EOF.
- (void)URLSession:(NSURLSession *)session readClosedForStreamTask:(NSURLSessionStreamTask *)streamTask;

/// Indicates that the write side of a connection has been closed.
///
/// Any outstanding writes complete, but future writes will immediately fail.
- (void)URLSession:(NSURLSession *)session writeClosedForStreamTask:(NSURLSessionStreamTask *)streamTask;

/// Notifies the delegate that a better route to the host has been detected.
///
/// For example, a Wi-Fi interface becoming available. This is a hint to the delegate that
/// it may be desirable to create a new task for subsequent work. Note that there is no
/// guarantee that the future task will be able to connect to the host, so callers should
/// be prepared for failure of reads and writes over any new interface.
- (void)URLSession:(NSURLSession *)session betterRouteDiscoveredForStreamTask:(NSURLSessionStreamTask *)streamTask;

/// Tells the delegate that the stream task has been completed, and provides the resulting
/// input and output streams.
///
/// This will only be invoked after all enqueued IO has completed (including any necessary
/// handshakes). The streamTask will not receive any further delegate messages.
- (void)URLSession:(NSURLSession *)session streamTask:(NSURLSessionStreamTask *)streamTask
                                 didBecomeInputStream:(NSInputStream *)inputStream
                                         outputStream:(NSOutputStream *)outputStream;

@end

/// A protocol that defines methods that URL session instances call on their delegates to handle task-level events specific to WebSocket tasks.
API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0))
@protocol NSURLSessionWebSocketDelegate <NSURLSessionTaskDelegate>
@optional

/// Tells the delegate that the WebSocket handshake was successful and the connection has been
/// upgraded to WebSocket.
///
/// It will also provide the protocol that is picked in the handshake. If the handshake fails,
/// this delegate will not be invoked.
- (void)URLSession:(NSURLSession *)session webSocketTask:(NSURLSessionWebSocketTask *)webSocketTask didOpenWithProtocol:(nullable NSString *) protocol;

/// Tells the delegate that the WebSocket has received a close frame from the server endpoint.
///
/// The close code and the close reason may be provided by the delegate if the server elects
/// to send this information in the close frame.
- (void)URLSession:(NSURLSession *)session webSocketTask:(NSURLSessionWebSocketTask *)webSocketTask didCloseWithCode:(NSURLSessionWebSocketCloseCode)closeCode reason:(nullable NSData *)reason;

@end

/// Key in the `userInfo` dictionary of an `NSError` received during a failed download.
FOUNDATION_EXPORT NSString * const NSURLSessionDownloadTaskResumeData API_AVAILABLE(macos(10.9), ios(7.0), watchos(2.0), tvos(9.0));

/// Key in the userInfo dictionary of an NSError received during a failed upload.
FOUNDATION_EXPORT NSString * const NSURLSessionUploadTaskResumeData API_AVAILABLE(macos(14.0), ios(17.0), watchos(10.0), tvos(17.0));

@interface NSURLSessionConfiguration (NSURLSessionDeprecated)
/// Returns a session configuration object that allows HTTP and HTTPS uploads or downloads to be performed in the background.
///
/// @DeprecationSummary {
///     Use ``NSURLSessionConfiguration/backgroundSessionConfigurationWithIdentifier:`` instead.
/// }
///
/// - Parameter identifier: The unique identifier for the configuration object. This parameter must not be `nil` or an empty string.
/// - Returns: A URL session configuration object that causes upload and download tasks to be performed by the system in a separate process.
+ (NSURLSessionConfiguration *)backgroundSessionConfiguration:(NSString *)identifier API_DEPRECATED_WITH_REPLACEMENT("-backgroundSessionConfigurationWithIdentifier:", macos(10.9, 10.10), ios(7.0, 8.0), watchos(2.0, 2.0), tvos(9.0, 9.0));
@end

/// The manner in which a resource is fetched.
typedef NS_ENUM(NSInteger, NSURLSessionTaskMetricsResourceFetchType) {
    /// The manner in which the resource was fetched could not be determined.
    NSURLSessionTaskMetricsResourceFetchTypeUnknown,
    /// The resource was loaded over the network.
    NSURLSessionTaskMetricsResourceFetchTypeNetworkLoad,
    /// The resource was pushed by the server to the client.
    NSURLSessionTaskMetricsResourceFetchTypeServerPush API_DEPRECATED("Server push is no longer supported as of iOS 17 and aligned releases", macos(10.12,15.4), ios(10.0,18.4), watchos(3.0,11.4), tvos(10.0,18.4), visionos(1.0,2.4)),
    /// The resource was retrieved from the local storage.
    NSURLSessionTaskMetricsResourceFetchTypeLocalCache,
} API_AVAILABLE(macosx(10.12), ios(10.0), watchos(3.0), tvos(10.0));

/*
 * DNS protocol used for domain resolution.
 */
typedef NS_ENUM(NSInteger, NSURLSessionTaskMetricsDomainResolutionProtocol) {
    NSURLSessionTaskMetricsDomainResolutionProtocolUnknown,
    NSURLSessionTaskMetricsDomainResolutionProtocolUDP,     /* Resolution used DNS over UDP. */
    NSURLSessionTaskMetricsDomainResolutionProtocolTCP,     /* Resolution used DNS over TCP. */
    NSURLSessionTaskMetricsDomainResolutionProtocolTLS,     /* Resolution used DNS over TLS. */
    NSURLSessionTaskMetricsDomainResolutionProtocolHTTPS,   /* Resolution used DNS over HTTPS. */
} API_AVAILABLE(macos(11.0), ios(14.0), watchos(7.0), tvos(14.0));

/// An object that encapsulates the performance metrics collected by the URL Loading System during the execution of a session task.
///
/// Each ``URLSessionTaskTransactionMetrics`` object consists of a ``request`` and ``response`` property, corresponding to the request and response of the corresponding task. It also contains temporal metrics, starting with ``fetchStartDate`` and ending with ``responseEndDate``, as well as other characteristics like ``networkProtocolName`` and ``resourceFetchType``.
///
/// ### Understanding temporal metrics
///
/// The figure below shows the sequence of events for a URL session task, which correspond to the temporal metrics captured by ``URLSessionTaskTransactionMetrics``.
///
/// ![Diagram showing the temporal metrics for a URL session task. When a task starts, it performs a DNS lookup and then starts a connection. If the connection is encrypted, the user agent starts a TLS security handshake to secure the connection. After the connection to the server is established, the user agent requests the specified resource, and receives a response.](media-3162616)
///
/// For all metrics with a start and end date, if an aspect of the task was not completed, then its corresponding end date metric is `nil`. This can happen if name lookup begins, but the operation either times out, fails, or the client cancels the task before the name can be resolved. In this case, the ``domainLookupEndDate`` property is `nil`, along with all metrics for aspects that occurred afterwards.
///
/// ### Measuring tasks using iCloud Private Relay
///
/// iCloud Private Relay can change the timing and sequence of events for your tasks by sending requests through a set of privacy proxies. All tasks that use iCloud Private Relay set the ``isProxyConnection`` property in their transaction metrics. In this case, the ``remoteAddress`` property contains the address of the proxy, and not the origin server.
///
/// Tasks to different hosts can reuse the same transport connection, just like how tasks can already share a connection when using HTTP/2. In these cases, a proxied task may not report any ``secureConnectionStartDate`` or ``secureConnectionEndDate``.
NS_SWIFT_SENDABLE
API_AVAILABLE(macosx(10.12), ios(10.0), watchos(3.0), tvos(10.0))
@interface NSURLSessionTaskTransactionMetrics : NSObject

/// Represents the transaction request.
@property (copy, readonly) NSURLRequest *request;

/// Represents the transaction response. Can be `nil` if error occurred and no response was generated.
@property (nullable, copy, readonly) NSURLResponse *response;

/// For all `NSDate` metrics below, if that aspect of the task could not be completed, then
/// the corresponding “EndDate” metric will be `nil`. For example, if a name lookup was
/// started but the name lookup timed out, failed, or the client canceled the task before
/// the name could be resolved -- then while `domainLookupStartDate` may be set,
/// `domainLookupEndDate` will be `nil` along with all later metrics.

/// The time when the user agent started fetching the resource, whether or not the resource
/// was retrieved from the server or local resources.
///
/// The following metrics will be set to `nil`, if a persistent connection was used or the
/// resource was retrieved from local resources: `domainLookupStartDate`,
/// `domainLookupEndDate`, `connectStartDate`, `connectEndDate`,
/// `secureConnectionStartDate`, `secureConnectionEndDate`.
@property (nullable, copy, readonly) NSDate *fetchStartDate;

/// The time immediately before the user agent started the name lookup for the resource.
@property (nullable, copy, readonly) NSDate *domainLookupStartDate;

/// The time after the name lookup was completed.
@property (nullable, copy, readonly) NSDate *domainLookupEndDate;

/// The time immediately before the user agent started establishing the connection to the server.
///
/// For example, this would correspond to the time immediately before the user agent started
/// trying to establish the TCP connection.
@property (nullable, copy, readonly) NSDate *connectStartDate;

/// If an encrypted connection was used, the time immediately before the user agent started
/// the security handshake to secure the current connection.
///
/// For example, this would correspond to the time immediately before the user agent started
/// the TLS handshake. If an encrypted connection was not used, this attribute is set to `nil`.
@property (nullable, copy, readonly) NSDate *secureConnectionStartDate;

/// If an encrypted connection was used, the time immediately after the security handshake
/// completed.
///
/// If an encrypted connection was not used, this attribute is set to `nil`.
@property (nullable, copy, readonly) NSDate *secureConnectionEndDate;

/// The time immediately after the user agent finished establishing the connection to the
/// server, including completion of security-related and other handshakes.
@property (nullable, copy, readonly) NSDate *connectEndDate;

/// The time immediately before the user agent started requesting the source, regardless of
/// whether the resource was retrieved from the server or local resources.
@property (nullable, copy, readonly) NSDate *requestStartDate;

/// The time immediately after the user agent finished requesting the source, regardless of
/// whether the resource was retrieved from the server or local resources.
@property (nullable, copy, readonly) NSDate *requestEndDate;

/// The time immediately after the user agent received the first byte of the response from
/// the server or from local resources.
@property (nullable, copy, readonly) NSDate *responseStartDate;

/// The time immediately after the user agent received the last byte of the resource.
@property (nullable, copy, readonly) NSDate *responseEndDate;

/// The network protocol used to fetch the resource, as identified by the ALPN Protocol ID
/// Identification Sequence [RFC7301]. E.g., h3, h2, http/1.1.
///
/// When a proxy is configured AND a tunnel connection is established, then this attribute
/// returns the value for the tunneled protocol.
@property (nullable, copy, readonly) NSString *networkProtocolName;

/// Whether a proxy connection was used to fetch the resource.
@property (assign, readonly, getter=isProxyConnection) BOOL proxyConnection;

/// Whether a persistent connection was used to fetch the resource.
@property (assign, readonly, getter=isReusedConnection) BOOL reusedConnection;

/// Indicates whether the resource was loaded, pushed or retrieved from the local cache.
@property (assign, readonly) NSURLSessionTaskMetricsResourceFetchType resourceFetchType;

/// The number of bytes transferred for request header.
@property (readonly) int64_t countOfRequestHeaderBytesSent API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0));

/// The number of bytes transferred for request body.
///
/// It includes protocol-specific framing, transfer encoding, and content encoding.
@property (readonly) int64_t countOfRequestBodyBytesSent API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0));

/// The size of upload body data, file, or stream.
@property (readonly) int64_t countOfRequestBodyBytesBeforeEncoding API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0));

/// The number of bytes transferred for response header.
@property (readonly) int64_t countOfResponseHeaderBytesReceived API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0));

/// The number of bytes transferred for response body.
///
/// It includes protocol-specific framing, transfer encoding, and content encoding.
@property (readonly) int64_t countOfResponseBodyBytesReceived API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0));

/// The size of data delivered to your delegate or completion handler.
@property (readonly) int64_t countOfResponseBodyBytesAfterDecoding API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0));

/// The IP address string of the local interface for the connection.
///
/// For multipath protocols, this is the local address of the initial flow.
/// If a connection was not used, this attribute is set to `nil`.
@property (nullable, copy, readonly) NSString *localAddress API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0));

/// The port number of the local interface for the connection.
///
/// For multipath protocols, this is the local port of the initial flow.
/// If the app didn't use the connection, this value is `nil`.
@property (nullable, copy, readonly) NSNumber *localPort API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0));

/// The IP address string of the remote interface for the connection.
///
/// For multipath protocols, this is the remote address of the initial flow.
/// If a connection was not used, this attribute is set to `nil`.
@property (nullable, copy, readonly) NSString *remoteAddress API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0));

/// The port number of the remote interface for the connection.
///
/// For multipath protocols, this is the remote port of the initial flow.
/// If the app didn't use the connection, this value is `nil`.
@property (nullable, copy, readonly) NSNumber *remotePort API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0));

/// The TLS protocol version the task negotiated with the endpoint for the connection.
///
/// This value is a 2-byte sequence in host byte order. See `tls_protocol_version_t`
/// in `Security/SecProtocolTypes.h` for possible values. If the task didn't negotiate
/// an encrypted connection, this value is `nil`.
@property (nullable, copy, readonly) NSNumber *negotiatedTLSProtocolVersion API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0));

/// The TLS cipher suite the task negotiated with the endpoint for the connection.
///
/// This value is a 2-byte sequence in host byte order. See `tls_ciphersuite_t`
/// in `Security/SecProtocolTypes.h` for possible values. If the task didn't negotiate
/// an encrypted connection, this value is `nil`.
@property (nullable, copy, readonly) NSNumber *negotiatedTLSCipherSuite API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0));

/// Whether the connection is established over a cellular interface.
@property (readonly, getter=isCellular) BOOL cellular API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0));

/// Whether the connection is established over an expensive interface.
@property (readonly, getter=isExpensive) BOOL expensive API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0));

/// Whether the connection is established over a constrained interface.
@property (readonly, getter=isConstrained) BOOL constrained API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0));

/// Whether a multipath protocol is successfully negotiated for the connection.
@property (readonly, getter=isMultipath) BOOL multipath API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0));

/// DNS protocol used for domain resolution.
@property (readonly) NSURLSessionTaskMetricsDomainResolutionProtocol domainResolutionProtocol API_AVAILABLE(macos(11.0), ios(14.0), watchos(7.0), tvos(14.0));


/// Creates a transaction metrics instance.
///
/// You should never need to create your own ``NSURLSessionTaskTransactionMetrics`` instances. The ``NSURLSession`` creates task transaction metrics as part of the ``NSURLSessionTaskMetrics`` instance that it delivers to the ``NSURLSessionTaskDelegate`` delegate.
- (instancetype)init API_DEPRECATED("Not supported", macos(10.12,10.15), ios(10.0,13.0), watchos(3.0,6.0), tvos(10.0,13.0));
/// Creates a new transaction metrics instance.
///
/// You should never need to create your own ``NSURLSessionTaskTransactionMetrics`` instances. The ``NSURLSession`` creates task transaction metrics as part of the ``NSURLSessionTaskMetrics`` instance that it delivers to the ``NSURLSessionTaskDelegate`` delegate.
+ (instancetype)new API_DEPRECATED("Not supported", macos(10.12,10.15), ios(10.0,13.0), watchos(3.0,6.0), tvos(10.0,13.0));

@end

/// An object encapsulating the metrics for a session task.
///
/// Each ``URLSessionTaskMetrics`` object contains the ``taskInterval`` and ``redirectCount``, as well as metrics for each request-and-response transaction made during the execution of the task.
NS_SWIFT_SENDABLE
API_AVAILABLE(macosx(10.12), ios(10.0), watchos(3.0), tvos(10.0))
@interface NSURLSessionTaskMetrics : NSObject

/// An array containing the metrics collected for every request/response transaction created
/// during the task execution.
@property (copy, readonly) NSArray<NSURLSessionTaskTransactionMetrics *> *transactionMetrics;

/// Interval from the task creation time to the task completion time.
///
/// Task creation time is the time when the task was instantiated. Task completion time is
/// the time when the task is about to change its internal state to completed.
@property (copy, readonly) NSDateInterval *taskInterval;

/// The number of redirects that were recorded.
@property (assign, readonly) NSUInteger redirectCount;


/// Creates a task metrics instance.
///
/// You should never need to create your own ``NSURLSessionTaskMetrics`` instances. If you are interested in task metrics, implement the ``NSURLSessionTaskDelegate`` method `URLSession:task:didFinishCollectingMetrics:`. The ``NSURLSession`` will collect task metrics for you and deliver them to this method.
- (instancetype)init API_DEPRECATED("Not supported", macos(10.12,10.15), ios(10.0,13.0), watchos(3.0,6.0), tvos(10.0,13.0));
/// Creates a task metrics instance.
///
/// You should never need to create your own ``NSURLSessionTaskMetrics`` instances.
+ (instancetype)new API_DEPRECATED("Not supported", macos(10.12,10.15), ios(10.0,13.0), watchos(3.0,6.0), tvos(10.0,13.0));

@end

NS_HEADER_AUDIT_END(nullability, sendability)
