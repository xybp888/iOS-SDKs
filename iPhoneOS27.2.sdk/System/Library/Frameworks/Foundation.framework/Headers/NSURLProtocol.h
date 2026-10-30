/*	
    NSURLProtocol.h
    Copyright (c) 2003-2019, Apple Inc. All rights reserved.    
    
    Public header file.
*/

#import <Foundation/NSObject.h>
#import <Foundation/NSURLCache.h>

@class NSCachedURLResponse;
@class NSError;
@class NSMutableURLRequest;
@class NSURLAuthenticationChallenge;
@class NSURLConnection;
@class NSURLProtocol;
@class NSURLProtocolInternal;
@class NSURLRequest;
@class NSURLResponse;
@class NSURLSessionTask;

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

/*!
    @header NSURLProtocol.h

    This header file describes the constructs used to represent URL
    protocols, and describes the extensible system by which specific
    classes can be made to handle the loading of particular URL types or
    schemes.
    
    <p>NSURLProtocol is an abstract class which provides the
    basic structure for performing protocol-specific loading of URL
    data.
    
    <p>The NSURLProtocolClient describes the integration points a
    protocol implementation can use to hook into the URL loading system.
    NSURLProtocolClient describes the methods a protocol implementation
    needs to drive the URL loading system from a NSURLProtocol subclass.
    
    <p>To support customization of protocol-specific requests,
    protocol implementors are encouraged to provide categories on
    NSURLRequest and NSMutableURLRequest. Protocol implementors who
    need to extend the capabilities of NSURLRequest and
    NSMutableURLRequest in this way can store and retrieve
    protocol-specific request data by using the
    <tt>+propertyForKey:inRequest:</tt> and
    <tt>+setProperty:forKey:inRequest:</tt> class methods on
    NSURLProtocol. See the NSHTTPURLRequest on NSURLRequest and
    NSMutableHTTPURLRequest on NSMutableURLRequest for examples of
    such extensions.
    
    <p>An essential responsibility for a protocol implementor is
    creating a NSURLResponse for each request it processes successfully.
    A protocol implementor may wish to create a custom, mutable 
    NSURLResponse class to aid in this work.
*/

/// The interface used by ``URLProtocol`` subclasses to communicate with the URL Loading System.
///
/// Don't implement this protocol in your application. Instead, your ``URLProtocol`` subclass calls methods of this protocol on its own ``URLProtocol/client`` property.
NS_SWIFT_SENDABLE
API_AVAILABLE(macos(10.2), ios(2.0), watchos(2.0), tvos(9.0))
@protocol NSURLProtocolClient <NSObject>

/// Indicates to the client that a redirect has occurred.
///
/// - Parameters:
///   - protocol: The `NSURLProtocol` object sending the message.
///   - request: The `NSURLRequest` to which the protocol implementation has redirected.
///   - redirectResponse: The redirect response.
- (void)URLProtocol:(NSURLProtocol *)protocol wasRedirectedToRequest:(NSURLRequest *)request redirectResponse:(NSURLResponse *)redirectResponse;

/// Indicates to the client that the protocol implementation has examined a cached response and determined that it is valid.
///
/// - Parameters:
///   - protocol: The `NSURLProtocol` object sending the message.
///   - cachedResponse: The `NSCachedURLResponse` object that has been examined and is valid.
- (void)URLProtocol:(NSURLProtocol *)protocol cachedResponseIsValid:(NSCachedURLResponse *)cachedResponse;

/// Indicates to the client that the protocol implementation has created an `NSURLResponse` for the current load.
///
/// - Parameters:
///   - protocol: The `NSURLProtocol` object sending the message.
///   - response: The `NSURLResponse` object the protocol implementation has created.
///   - policy: The `NSURLCacheStoragePolicy` the protocol has determined should be used for the given response if the response is to be stored in a cache.
- (void)URLProtocol:(NSURLProtocol *)protocol didReceiveResponse:(NSURLResponse *)response cacheStoragePolicy:(NSURLCacheStoragePolicy)policy;

/// Indicates to the client that the protocol implementation has loaded URL data.
///
/// The data object must contain only new data loaded since the previous call to this method (if any),
/// not cumulative data for the entire load.
///
/// - Parameters:
///   - protocol: The `NSURLProtocol` object sending the message.
///   - data: URL load data being made available.
- (void)URLProtocol:(NSURLProtocol *)protocol didLoadData:(NSData *)data;

/// Indicates to the client that the protocol implementation has finished loading successfully.
///
/// - Parameter protocol: The `NSURLProtocol` object sending the message.
- (void)URLProtocolDidFinishLoading:(NSURLProtocol *)protocol;

/// Indicates to the client that the protocol implementation has failed to load successfully.
///
/// - Parameters:
///   - protocol: The `NSURLProtocol` object sending the message.
///   - error: The error that caused the load to fail.
- (void)URLProtocol:(NSURLProtocol *)protocol didFailWithError:(NSError *)error;

/// Start authentication for the specified request.
///
/// The protocol client guarantees that it will answer the request on the same thread that called this method.
/// It may add a default credential to the challenge it issues to the connection delegate, if the protocol did not provide one.
///
/// - Parameters:
///   - protocol: The protocol object requesting authentication.
///   - challenge: The authentication challenge.
- (void)URLProtocol:(NSURLProtocol *)protocol didReceiveAuthenticationChallenge:(NSURLAuthenticationChallenge *)challenge;

/// Cancel authentication for the specified request.
///
/// - Parameters:
///   - protocol: The protocol object cancelling authentication.
///   - challenge: The authentication challenge.
- (void)URLProtocol:(NSURLProtocol *)protocol didCancelAuthenticationChallenge:(NSURLAuthenticationChallenge *)challenge;

@end

/// An abstract class that handles the loading of protocol-specific URL data.
///
/// Don't instantiate a ``URLProtocol`` subclass directly. Instead, create subclasses for any custom protocols or URL schemes that your app supports. When a download starts, the system creates the appropriate protocol object to handle the corresponding URL request. You define your protocol class and call the ``registerClass(_:)`` class method during your app's launch time so that the system is aware of your protocol.
///
/// > Note:
/// > You cannot use this class to define custom URL schemes and protocols in watchOS 2 and later.
///
/// To support the customization of protocol-specific requests, create extensions to the ``URLRequest`` class to provide any custom API that you need. You can store and retrieve protocol-specific request data by using ``URLProtocol``'s class methods ``property(forKey:in:)`` and ``setProperty(_:forKey:in:)``.
///
/// Create a ``URLResponse`` for each request your subclass processes successfully. You may want to create a custom ``URLResponse`` class to provide protocol specific information.
///
/// ### Subclassing notes
///
/// When overriding methods of this class, be aware that methods that take a `task` parameter are preferred by the system to those that do not. Therefore, you should override the task-based methods when subclassing, as follows:
///
/// Swift:
///
/// - Initialization — Override ``init(task:cachedResponse:client:)`` instead of or in addition to ``init(request:cachedResponse:client:)``. Also override the task-based ``canInit(with:)-18gbo`` instead of or in addition to the request-based ``canInit(with:)-76brg``.
///
/// Objective-C:
///
/// - Initialization — Override ``canInit(with:)-18gbo`` and ``init(task:cachedResponse:client:)`` instead of or in addition to ``canInit(with:)-76brg`` and ``init(request:cachedResponse:client:)``.
API_AVAILABLE(macos(10.2), ios(2.0), watchos(2.0), tvos(9.0))
@interface NSURLProtocol : NSObject
{
    @private
    NSURLProtocolInternal *_internal;
}

/// Creates a URL protocol instance to handle the request.
///
/// - Parameters:
///   - request: The request to load.
///   - cachedResponse: A response that has been retrieved from the cache for the given request.
///     The protocol implementation should apply protocol-specific validity checks if such tests are necessary.
///   - client: The `NSURLProtocolClient` object that serves as the interface the protocol implementation
///     can use to report results back to the URL loading system.
- (instancetype)initWithRequest:(NSURLRequest *)request cachedResponse:(nullable NSCachedURLResponse *)cachedResponse client:(nullable id <NSURLProtocolClient>)client NS_DESIGNATED_INITIALIZER;

/// The object the protocol uses to communicate with the URL loading system.
@property (nullable, readonly, retain) id <NSURLProtocolClient> client;

/// The protocol's request.
@property (readonly, copy) NSURLRequest *request;

/// The protocol's cached response.
@property (nullable, readonly, copy) NSCachedURLResponse *cachedResponse;

/*======================================================================
  Begin responsibilities for protocol implementors

  The methods between this set of begin-end markers must be
  implemented in order to create a working protocol.
  ======================================================================*/
  
/// Determines whether the protocol subclass can handle the specified request.
///
/// A concrete subclass should inspect the given request and determine whether or not the implementation
/// can perform a load with that request. This is an abstract method. Subclasses must provide an implementation.
///
/// - Parameter request: A request to inspect.
/// - Returns: `YES` if the protocol can handle the given request, `NO` if not.
+ (BOOL)canInitWithRequest:(NSURLRequest *)request;

/// Returns a canonical version of the specified request.
///
/// It is up to each concrete protocol implementation to define what "canonical" means. However, a protocol
/// should guarantee that the same input request always yields the same canonical form. Special consideration
/// should be given when implementing this method since the canonical form of a request is used to look up
/// objects in the URL cache, a process which performs equality checks between `NSURLRequest` objects.
///
/// This is an abstract method; subclasses must provide an implementation.
///
/// - Parameter request: A request to make canonical.
/// - Returns: The canonical form of the given request.
+ (NSURLRequest *)canonicalRequestForRequest:(NSURLRequest *)request;

/// A Boolean value indicating whether two requests are equivalent for cache purposes.
///
/// Requests are considered equivalent for cache purposes if and only if they would be handled by the same
/// protocol AND that protocol declares them equivalent after performing implementation-specific checks.
///
/// - Returns: `YES` if the two requests are cache-equivalent, `NO` otherwise.
+ (BOOL)requestIsCacheEquivalent:(NSURLRequest *)a toRequest:(NSURLRequest *)b;

/// Starts protocol-specific loading of the request.
///
/// When this method is called, the protocol implementation should start loading a request.
- (void)startLoading;

/// Stops protocol-specific loading of the request.
///
/// When this method is called, the protocol implementation should end the work of loading a request.
/// This could be in response to a cancel operation, so protocol implementations must be able to handle
/// this call while a load is in progress.
- (void)stopLoading;

/*======================================================================
  End responsibilities for protocol implementors
  ======================================================================*/

/// Fetches the property associated with the specified key in the specified request.
///
/// The purpose of this method is to provide an interface for protocol implementors to access
/// protocol-specific information associated with `NSURLRequest` objects.
///
/// - Parameters:
///   - key: The string to use for the property lookup.
///   - request: The request to use for the property lookup.
/// - Returns: The property stored with the given key, or `nil` if no property had previously been stored with the given key in the given request.
+ (nullable id)propertyForKey:(NSString *)key inRequest:(NSURLRequest *)request;

/// Sets the property associated with the specified key in the specified request.
///
/// The purpose of this method is to provide an interface for protocol implementors to customize
/// protocol-specific information associated with `NSMutableURLRequest` objects.
///
/// - Parameters:
///   - value: The property to store.
///   - key: The string to use for the property storage.
///   - request: The request in which to store the property.
+ (void)setProperty:(id)value forKey:(NSString *)key inRequest:(NSMutableURLRequest *)request;

/// Removes the property associated with the specified key in the specified request.
///
/// Like `setProperty:forKey:inRequest:`, the purpose of this method is to give protocol implementors
/// the ability to store protocol-specific information in an `NSURLRequest`.
///
/// - Parameters:
///   - key: The key whose value should be removed.
///   - request: The request to be modified.
+ (void)removePropertyForKey:(NSString *)key inRequest:(NSMutableURLRequest *)request;


/// Attempts to register a subclass of ``URLProtocol``, making it visible to the URL loading system.
///
/// When the URL loading system begins to load a request, each protocol class that has been registered is
/// consulted in turn to see if it can be initialized with a given request. The first protocol handler class
/// to provide a `YES` answer to `+canInitWithRequest:` "wins" and that protocol implementation is used to
/// perform the URL load. There is no guarantee that all registered protocol classes will be consulted.
/// Registering a class places it first on the list of classes that will be consulted.
///
/// - Parameter protocolClass: The class to register.
/// - Returns: `YES` if the protocol was registered successfully, `NO` if not. The only way that failure can
///   occur is if the given class is not a subclass of `NSURLProtocol`.
+ (BOOL)registerClass:(Class)protocolClass;

/// Unregisters the specified subclass of ``URLProtocol``.
///
/// After unregistration, a protocol class is no longer consulted in calls to `NSURLProtocol` class methods.
///
/// - Parameter protocolClass: The class to unregister.
+ (void)unregisterClass:(Class)protocolClass;

@end


@interface NSURLProtocol (NSURLSessionTaskAdditions)
/// Determines whether the protocol subclass can handle the specified task.
+ (BOOL)canInitWithTask:(NSURLSessionTask *)task API_AVAILABLE(macos(10.10), ios(8.0), watchos(2.0), tvos(9.0));
/// Creates a URL protocol instance to handle the task.
- (instancetype)initWithTask:(NSURLSessionTask *)task cachedResponse:(nullable NSCachedURLResponse *)cachedResponse client:(nullable id <NSURLProtocolClient>)client API_AVAILABLE(macos(10.10), ios(8.0), watchos(2.0), tvos(9.0));
/// The protocol's task.
@property (nullable, readonly, copy) NSURLSessionTask *task API_AVAILABLE(macos(10.10), ios(8.0), watchos(2.0), tvos(9.0));
@end

NS_HEADER_AUDIT_END(nullability, sendability)
