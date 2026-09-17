/*    
    NSURLConnection.h
    Copyright (c) 2003-2019, Apple Inc. All rights reserved.    
    
    Public header file.
*/

#import <Foundation/NSObject.h>
#import <Foundation/NSRunLoop.h>

@class NSArray;
@class NSURL;
@class NSCachedURLResponse;
@class NSData;
@class NSError;
@class NSURLAuthenticationChallenge;
@class NSURLConnectionInternal;
@class NSURLRequest;
@class NSURLResponse;
@class NSRunLoop;
@class NSInputStream;
@class NSURLProtectionSpace;
@class NSOperationQueue;

@protocol NSURLConnectionDelegate;

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

/*** DEPRECATED: The NSURLConnection class should no longer be used.  NSURLSession is the replacement for NSURLConnection ***/

/// An object that enables you to start and stop URL requests.
///
/// > Important:
/// > This API is considered legacy. Use ``URLSession`` instead.
///
/// An `NSURLConnection` object lets you load the contents of a URL by providing a URL request object. The interface for `NSURLConnection` is sparse, providing only the controls to start and cancel asynchronous loads of a URL request. You perform most of your configuration on the URL request object itself.
///
/// > Note:
/// > Although instances of this class are commonly called "connections", there is not a 1:1 correlation between these objects and the underlying network connections.
///
/// The `NSURLConnection` class provides convenience class methods to load URL requests both asynchronously using a callback block and synchronously.
///
/// For greater control, you can create a URL connection object with a delegate object that conforms to the ``NSURLConnectionDelegate`` and ``NSURLConnectionDataDelegate`` protocols. The connection calls methods on that delegate to provide you with progress and status as the URL request is loaded asynchronously. The connection also calls delegate methods to let you override the connection's default behavior (for example, specifying how a particular redirect should be handled). These delegate methods are called on the thread that initiated the asynchronous load operation.
///
/// > Note:
/// > During a request, the connection maintains a strong reference to its delegate. It releases that strong reference when the connection finishes loading, fails, or is canceled.
///
/// For more information about errors, see the `NSURLError.h` header, <doc:foundation-constants>, and URL Loading System Error Codes in [Error Handling Programming Guide](https://developer.apple.com/library/archive/documentation/Cocoa/Conceptual/ErrorHandlingCocoa/ErrorHandling/ErrorHandling.html#//apple_ref/doc/uid/TP40001806).
///
/// ### NSURLConnection Protocols
///
/// The `NSURLConnection` class works in tandem with three formal protocols: ``NSURLConnectionDelegate``, ``NSURLConnectionDataDelegate``, and ``NSURLConnectionDownloadDelegate``. To use these protocols, you write a class that conforms to them and implement any methods that are appropriate, then provide an instance of that class as the delegate when you create a connection object.
///
/// The ``NSURLConnectionDelegate`` protocol is primarily used for credential handling, but also handles connection completion. Because it handles connection failure during data transfers, all connection delegates must typically implement this protocol.
///
/// In addition, unless you're using Newsstand Kit, your delegate must also conform to the ``NSURLConnectionDataDelegate`` protocol, because this protocol provides methods that the `NSURLConnection` class calls with progress information during an upload, with fragments of the response data during a download, and to provide a new upload body stream if the server's response necessitates a second connection attempt—for example, if `NSURLConnection` must retry the request with different credentials.
///
/// Finally, if you're using Newsstand Kit, your delegate can conform to the ``NSURLConnectionDownloadDelegate`` protocol. This protocol provides support for continuing interrupted file downloads and receiving a notification whenever a download finishes. This protocol is solely for use with `NSURLConnection` objects created using Newsstand Kit's `download(with:)` method.
///
/// > Note:
/// > Some methods in these protocols were previously part of other formal protocols or were previously part of an informal protocol on `NSObject`.
API_AVAILABLE(macos(10.2), ios(2.0), watchos(2.0), tvos(9.0))
@interface NSURLConnection : NSObject
{
    @private
    NSURLConnectionInternal *_internal;
}

/// The designated initializer.
- (nullable instancetype)initWithRequest:(NSURLRequest *)request delegate:(nullable id)delegate startImmediately:(BOOL)startImmediately API_DEPRECATED("Use NSURLSession (see NSURLSession.h)", macos(10.5,10.11), ios(2.0,9.0), tvos(9.0,9.0)) API_UNAVAILABLE(watchos);

/// Creates and returns a URL connection and begins loading the data for the URL request.
- (nullable instancetype)initWithRequest:(NSURLRequest *)request delegate:(nullable id)delegate API_DEPRECATED("Use NSURLSession (see NSURLSession.h)", macos(10.3,10.11), ios(2.0,9.0), tvos(9.0,9.0)) API_UNAVAILABLE(watchos);
/// Returns a URL connection that loads the data for a URL request and begins loading the data, if specified.
+ (nullable NSURLConnection*)connectionWithRequest:(NSURLRequest *)request delegate:(nullable id)delegate API_DEPRECATED("Use NSURLSession (see NSURLSession.h)", macos(10.3,10.11), ios(2.0,9.0), tvos(9.0,9.0)) API_UNAVAILABLE(watchos);

/// A deep copy of the original connection request.
///
/// As the connection performs the load, the request may change as a result of protocol canonicalization or due to following redirects.
@property (readonly, copy) NSURLRequest *originalRequest API_AVAILABLE(macos(10.8), ios(5.0), watchos(2.0), tvos(9.0));
/// The current connection request.
///
/// As the connection performs the load, the request may change as a result of protocol canonicalization or due to following redirects. This property provides the current value of the request.
@property (readonly, copy) NSURLRequest *currentRequest API_AVAILABLE(macos(10.8), ios(5.0), watchos(2.0), tvos(9.0));

/// Causes the connection to begin loading data, if it has not already.
///
/// Calling this method is necessary only if you create a connection with the `-initWithRequest:delegate:startImmediately:` method and provide `NO` for the `startImmediately` parameter. If you don't schedule the connection in a run loop or an operation queue before calling this method, the connection is scheduled in the current run loop in the default mode.
- (void)start API_AVAILABLE(macos(10.5), ios(2.0), watchos(2.0), tvos(9.0));
/// Cancels an asynchronous load of a request.
///
/// After this method is called, the connection makes no further delegate method calls. If you want to reattempt the connection, you should create a new connection object.
- (void)cancel;

/// Determines the run loop and mode that the connection uses to call methods on its delegate.
///
/// By default, a connection is scheduled on the current thread in the default mode when it is created. You cannot reschedule a connection after it has started.
- (void)scheduleInRunLoop:(NSRunLoop *)aRunLoop forMode:(NSRunLoopMode)mode API_AVAILABLE(macos(10.5), ios(2.0), watchos(2.0), tvos(9.0));
/// Removes the connection from the specified run loop and mode.
- (void)unscheduleFromRunLoop:(NSRunLoop *)aRunLoop forMode:(NSRunLoopMode)mode API_AVAILABLE(macos(10.5), ios(2.0), watchos(2.0), tvos(9.0));
/// Determines the operation queue that is used to call methods on the connection's delegate.
///
/// By default, a connection is scheduled on the current thread in the default mode when it is created. You cannot reschedule a connection after it has started.
- (void)setDelegateQueue:(nullable NSOperationQueue*) queue API_AVAILABLE(macos(10.7), ios(5.0), watchos(2.0), tvos(9.0));


/// Returns whether a request can be handled based on a preflight evaluation.
///
/// The result of this method is valid as long as no ``NSURLProtocol`` classes are registered or unregistered, and `request` remains unchanged. Applications should be prepared to handle failures even if they have performed request preflighting by calling this method.
///
/// - Parameter request: The request to evaluate. The connection deep-copies the request on creation.
/// - Returns: `YES` if a preflight operation determines that a connection with `request` can be created and the associated I/O can be started, `NO` otherwise.
+ (BOOL)canHandleRequest:(NSURLRequest *)request;

@end

/*!
    @protocol       NSURLConnectionDelegate

    @abstract        
                    Delegate methods that are common to all forms of
                    NSURLConnection.  These are all optional.  This
                    protocol should be considered a base class for the
                    NSURLConnectionDataDelegate and
                    NSURLConnectionDownloadDelegate protocols.

    @discussion
                    connection:didFailWithError: will be called at
                    most once, if an error occurs during a resource
                    load.  No other callbacks will be made after.<p>

                    connectionShouldUseCredentialStorage: will be
                    called at most once, before a resource load begins
                    (which means it may be called during construction
                    of the connection.)  The delegate should return
                    TRUE if the connection should consult the shared
                    NSURLCredentialStorage in response to
                    authentication challenges.  Regardless of the
                    result, the authentication challenge methods may
                    still be called.

                    connection:willSendRequestForAuthenticationChallenge:
                    is the preferred (Mac OS X 10.7 and iOS 5.0 or
                    later) mechanism for responding to authentication
                    challenges.  See
                    <Foundation/NSURLAuthenticationChallenge.h> for
                    more information on dealing with the various types
                    of authentication challenges.

                    connection:canAuthenticateAgainstProtectionSpace:
                    connection:didReceiveAuthenticationChallenge:
                    connection:didCancelAuthenticationChallenge: are
                    deprecated and new code should adopt
                    connection:willSendRequestForAuthenticationChallenge.
                    The older delegates will still be called for
                    compatibility, but incur more latency in dealing
                    with the authentication challenge.
*/

/// A protocol that most delegates of a URL connection implement to receive data associated with the connection.
///
/// The `NSURLConnectionDataDelegate` protocol describes methods that should be implemented by the delegate for an instance of the ``NSURLConnection`` class. Many methods in this protocol existed as part of an informal protocol in previous versions of macOS and iOS.
///
/// In addition to the methods described in this protocol, an `NSURLConnection` delegate should also implement the methods described in the ``NSURLConnectionDelegate`` protocol.
///
/// > Note:
/// > If you are using `NSURLConnection` as part of Newsstand Kit on iOS, you should also implement the methods in the ``NSURLConnectionDownloadDelegate`` protocol.
API_AVAILABLE(macos(10.2), ios(2.0), watchos(2.0), tvos(9.0))
@protocol NSURLConnectionDelegate <NSObject>
@optional
/// Sent when a connection fails to load its request successfully.
- (void)connection:(NSURLConnection *)connection didFailWithError:(NSError *)error;
/// Sent to determine whether the URL loader should consult the credential storage to authenticate the connection.
- (BOOL)connectionShouldUseCredentialStorage:(NSURLConnection *)connection;
/// Sent when a connection must authenticate a challenge in order to download its request.
- (void)connection:(NSURLConnection *)connection willSendRequestForAuthenticationChallenge:(NSURLAuthenticationChallenge *)challenge;
/// Sent to determine whether the delegate is able to respond to a protection space's form of authentication.
- (BOOL)connection:(NSURLConnection *)connection canAuthenticateAgainstProtectionSpace:(NSURLProtectionSpace *)protectionSpace API_DEPRECATED("Use -connection:willSendRequestForAuthenticationChallenge: instead.", macos(10.6,10.10), ios(3.0,8.0), watchos(2.0,2.0), tvos(9.0,9.0));
/// Sent when a connection receives an authentication challenge.
- (void)connection:(NSURLConnection *)connection didReceiveAuthenticationChallenge:(NSURLAuthenticationChallenge *)challenge API_DEPRECATED("Use -connection:willSendRequestForAuthenticationChallenge: instead.", macos(10.2,10.10), ios(2.0,8.0), watchos(2.0,2.0), tvos(9.0,9.0));
/// Sent when a connection cancels an authentication challenge.
- (void)connection:(NSURLConnection *)connection didCancelAuthenticationChallenge:(NSURLAuthenticationChallenge *)challenge API_DEPRECATED("Use -connection:willSendRequestForAuthenticationChallenge: instead.", macos(10.2,10.10), ios(2.0,8.0), watchos(2.0,2.0), tvos(9.0,9.0));
@end

/*!
    @protocol       NSURLConnectionDataDelegate

    @abstract        
                    Delegate methods used for loading data to memory.
                    These delegate methods are all optional.

    @discussion
                    connection:willSendRequest:redirectResponse: is
                    called whenever an connection determines that it
                    must change URLs in order to continue loading a
                    request.  This gives the delegate an opportunity
                    inspect and if necessary modify a request.  A
                    delegate can cause the request to abort by either
                    calling the connections -cancel method, or by
                    returning nil from this callback.<p>

                    There is one subtle difference which results from
                    this choice. If -cancel is called in the delegate
                    method, all processing for the connection stops,
                    and no further delegate callbacks will be sent. If
                    the delegate returns nil, the connection will
                    continue to process, and this has special
                    relevance in the case where the redirectResponse
                    argument is non-nil. In this case, any data that
                    is loaded for the connection will be sent to the
                    delegate, and the delegate will receive a finished
                    or failure delegate callback as appropriate.<p>

                    connection:didReceiveResponse: is called when
                    enough data has been read to construct an
                    NSURLResponse object. In the event of a protocol
                    which may return multiple responses (such as HTTP
                    multipart/x-mixed-replace) the delegate should be
                    prepared to inspect the new response and make
                    itself ready for data callbacks as appropriate.<p>

                    connection:didReceiveData: is called with a single
                    immutable NSData object to the delegate,
                    representing the next portion of the data loaded
                    from the connection.  This is the only guaranteed
                    for the delegate to receive the data from the
                    resource load.<p>

                    connection:needNewBodyStream: is called when the
                    loader must retransmit a requests payload, due to
                    connection errors or authentication challenges.
                    Delegates should construct a new unopened and
                    autoreleased NSInputStream.  If not implemented,
                    the loader will be required to spool the bytes to
                    be uploaded to disk, a potentially expensive
                    operation.  Returning nil will cancel the
                    connection.

                    connection:didSendBodyData:totalBytesWritten:totalBytesExpectedToWrite:
                    is called during an upload operation to provide
                    progress feedback.  Note that the values may
                    change in unexpected ways if the request needs to
                    be retransmitted.<p>

                    connection:willCacheResponse: gives the delegate
                    an opportunity to inspect and modify the
                    NSCachedURLResponse which will be cached by the
                    loader if caching is enabled for the original
                    NSURLRequest.  Returning nil from this delegate
                    will prevent the resource from being cached.  Note
                    that the -data method of the cached response may
                    return an autoreleased in-memory copy of the true
                    data, and should not be used as an alternative to
                    receiving and accumulating the data through
                    connection:didReceiveData:<p>

                    connectionDidFinishLoading: is called when all
                    connection processing has completed successfully,
                    before the delegate is released by the
                    connection.<p>
*/

/// A protocol that most delegates of a URL connection implement to receive data associated with the connection.
///
/// The `NSURLConnectionDataDelegate` protocol describes methods that should be implemented by the delegate for an instance of the ``NSURLConnection`` class. Many methods in this protocol existed as part of an informal protocol in previous versions of macOS and iOS.
///
/// In addition to the methods described in this protocol, an `NSURLConnection` delegate should also implement the methods described in the ``NSURLConnectionDelegate`` protocol.
///
/// > Note:
/// > If you are using `NSURLConnection` as part of Newsstand Kit on iOS, you should also implement the methods in the ``NSURLConnectionDownloadDelegate`` protocol.
API_AVAILABLE(macos(10.2), ios(2.0), watchos(2.0), tvos(9.0))
@protocol NSURLConnectionDataDelegate <NSURLConnectionDelegate>
@optional
/// Sent when the connection determines that it must change URLs in order to continue loading a request.
- (nullable NSURLRequest *)connection:(NSURLConnection *)connection willSendRequest:(NSURLRequest *)request redirectResponse:(nullable NSURLResponse *)response;
/// Sent when the connection has received sufficient data to construct the URL response for its request.
- (void)connection:(NSURLConnection *)connection didReceiveResponse:(NSURLResponse *)response;

/// Sent as a connection loads data incrementally.
- (void)connection:(NSURLConnection *)connection didReceiveData:(NSData *)data;

/// Sent when the connection needs to retransmit a request body stream to the server.
- (nullable NSInputStream *)connection:(NSURLConnection *)connection needNewBodyStream:(NSURLRequest *)request;
/// Sent as the body of a message is sent to the server, providing progress information for uploads.
- (void)connection:(NSURLConnection *)connection   didSendBodyData:(NSInteger)bytesWritten
                                                 totalBytesWritten:(NSInteger)totalBytesWritten
                                         totalBytesExpectedToWrite:(NSInteger)totalBytesExpectedToWrite;

/// Sent before the connection stores a cached response in the cache, to give the delegate an opportunity to alter it.
- (nullable NSCachedURLResponse *)connection:(NSURLConnection *)connection willCacheResponse:(NSCachedURLResponse *)cachedResponse;

/// Sent when a connection has finished loading successfully.
- (void)connectionDidFinishLoading:(NSURLConnection *)connection;
@end

/*!
    @protocol       NSURLConnectionDownloadDelegate

    @abstract
                    Delegate methods used to perform resource
                    downloads directly to a disk file.  All the
                    methods are optional with the exception of
                    connectionDidFinishDownloading:destinationURL:
                    which must be implemented in order to inform the
                    delegate of the location of the finished download.
                    This delegate and download implementation is
                    currently only available on iOS 5.0 or later.

    @discussion
                    connection:didWriteData:totalBytesWritten:expectedTotalBytes:
                    provides progress information about the state of
                    the download, the number of bytes written since
                    the last delegate callback, the total number of
                    bytes written to disk and the total number of
                    bytes that are expected (or 0 if this is unknown.)

                    connectionDidResumeDownloading:totalBytesWritten:expectedTotalBytes:
                    is called when the connection is able to resume an
                    in progress download.  This may happen due to a
                    connection or network failure.

                    connectionDidFinishDownloading:destinationURL: is
                    a terminal event which indicates the completion of
                    a download and provides the location of the file.
                    The file will be located in the applications cache
                    directory and is guaranteed to exist for the
                    duration of the delegate callback.  The
                    implication is that the delegate should copy or
                    move the download to a more persistent location if
                    desired.
*/

/// A protocol that delegates of a URL connection created with Newsstand Kit implement to receive data associated with a download.
///
/// The `NSURLConnectionDownloadDelegate` protocol describes methods that should be implemented by the delegate of instances of `NSURLConnection` created using Newsstand Kit's `download(with:)` method. The methods in this protocol provide progress information about the download of a URL asset and, when downloading concludes, provide a file URL where the downloaded file can be accessed.
///
/// In addition to the methods described in this protocol, an `NSURLConnection` delegate should also implement the methods described in the ``NSURLConnectionDelegate`` protocol.
///
/// > Note:
/// > If you are using `NSURLConnection` directly, your delegate class should instead implement the methods defined in the ``NSURLConnectionDataDelegate`` protocol.
API_AVAILABLE(macos(10.2), ios(2.0), watchos(2.0), tvos(9.0))
@protocol NSURLConnectionDownloadDelegate <NSURLConnectionDelegate>
@optional
/// Sent as the connection writes data to a disk file, providing progress information for downloads.
- (void)connection:(NSURLConnection *)connection didWriteData:(long long)bytesWritten totalBytesWritten:(long long)totalBytesWritten expectedTotalBytes:(long long) expectedTotalBytes;
/// Sent when a connection resumes an in-progress download.
- (void)connectionDidResumeDownloading:(NSURLConnection *)connection totalBytesWritten:(long long)totalBytesWritten expectedTotalBytes:(long long) expectedTotalBytes;

@required
/// Sent when a download connection finishes loading and provides the location of the downloaded file.
- (void)connectionDidFinishDownloading:(NSURLConnection *)connection destinationURL:(NSURL *) destinationURL;
@end

/*!
    @category    NSURLConnection(NSURLConnectionSynchronousLoading)

    @abstract
                 The NSURLConnectionSynchronousLoading category on
                 NSURLConnection provides the interface to perform
                 synchronous loading of URL requests.
*/
@interface NSURLConnection (NSURLConnectionSynchronousLoading)

/// Performs a synchronous load of the specified URL request.
///
/// A synchronous load is built on top of the asynchronous loading code made available by the class. The calling thread is blocked while the asynchronous loading system performs the URL load on a thread spawned specifically for this load request. No special threading or run loop configuration is necessary in the calling thread in order to perform a synchronous load.
///
/// > Important: Because this call can potentially take several minutes to complete (particularly when using a cellular network in iOS), you should never call this function from the main thread of your application. The solution is to migrate to URL loading using ``NSURLSession``.
///
/// If authentication is required in order to download the request, the required credentials must be specified as part of the URL. If authentication fails, or credentials are missing, the connection will attempt to continue without credentials.
///
/// - Parameters:
///   - request: The URL request to load. The `request` object is deep-copied as part of the initialization process. Changes made to `request` after this method returns do not affect the request that is used for the loading process.
///   - response: Out parameter for the URL response returned by the server.
///   - error: Out parameter used if an error occurs while processing the request. May be `NULL`.
/// - Returns: The downloaded data for the URL request. Returns `nil` if a connection could not be created or if the download fails.
+ (nullable NSData *)sendSynchronousRequest:(NSURLRequest *)request returningResponse:(NSURLResponse * _Nullable * _Nullable)response error:(NSError **)error API_DEPRECATED("Use [NSURLSession dataTaskWithRequest:completionHandler:] (see NSURLSession.h", macos(10.3,10.11), ios(2.0,9.0), tvos(9.0,9.0)) API_UNAVAILABLE(watchos);

@end

/*!
    @category NSURLConnection(NSURLConnectionQueuedLoading)

    The NSURLConnectionQueuedLoading category on NSURLConnection
    provides the interface to perform asynchronous loading of URL
    requests where the results of the request are delivered to a
    block via an NSOperationQueue.

    Note that there is no guarantee of load ordering implied by this
    method.
 */
@interface NSURLConnection (NSURLConnectionQueuedLoading)

/*!
    @method       sendAsynchronousRequest:queue:completionHandler:

    @abstract 
                  Performs an asynchronous load of the given
                  request. When the request has completed or failed,
                  the block will be executed from the context of the
                  specified NSOperationQueue.

    @discussion
                  This is a convenience routine that allows for
                  asynchronous loading of a url-based resource.  If
                  the resource load is successful, the data parameter
                  to the callback will contain the resource data and
                  the error parameter will be nil.  If the resource
                  load fails, the data parameter will be nil and the
                  error will contain information about the failure.

    @param
         request   The request to load. Note that the request is
                   deep-copied as part of the initialization
                   process. Changes made to the request argument after
                   this method returns do not affect the request that
                   is used for the loading process.

    @param 
         queue     An NSOperationQueue upon which    the handler block will
                   be dispatched.

    @param
         handler   A block which receives the results of the resource load.
 */
+ (void)sendAsynchronousRequest:(NSURLRequest*) request
                          queue:(NSOperationQueue*) queue
              completionHandler:(void (^)(NSURLResponse* _Nullable response, NSData* _Nullable data, NSError* _Nullable connectionError)) handler API_DEPRECATED("Use [NSURLSession dataTaskWithRequest:completionHandler:] (see NSURLSession.h", macos(10.7,10.11), ios(5.0,9.0), tvos(9.0,9.0)) API_UNAVAILABLE(watchos);
           
@end

NS_HEADER_AUDIT_END(nullability, sendability)
