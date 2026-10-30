/*	
    NSURLRequest.h
    Copyright (c) 2003-2019, Apple Inc. All rights reserved.    
    
    Public header file.
*/

#import <Foundation/NSObject.h>
#import <Foundation/NSDate.h>

@class NSData;
@class NSDictionary<KeyType, ObjectType>;
@class NSInputStream;
@class NSString;
@class NSURL;
@class NSURLRequestInternal;

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

/*!
    @header NSURLRequest.h

    This header file describes the constructs used to represent URL
    load requests in a manner independent of protocol and URL scheme.
    Immutable and mutable variants of this URL load request concept
    are described, named NSURLRequest and NSMutableURLRequest,
    respectively. A collection of constants is also declared to
    exercise control over URL content caching policy.

    <p>NSURLRequest and NSMutableURLRequest are designed to be
    customized to support protocol-specific requests. Protocol
    implementors who need to extend the capabilities of NSURLRequest
    and NSMutableURLRequest are encouraged to provide categories on
    these classes as appropriate to support protocol-specific data. To
    store and retrieve data, category methods can use the
    <tt>+propertyForKey:inRequest:</tt> and
    <tt>+setProperty:forKey:inRequest:</tt> class methods on
    NSURLProtocol. See the NSHTTPURLRequest on NSURLRequest and
    NSMutableHTTPURLRequest on NSMutableURLRequest for examples of
    such extensions.

    <p>The main advantage of this design is that a client of the URL
    loading library can implement request policies in a standard way
    without type checking of requests or protocol checks on URLs. Any
    protocol-specific details that have been set on a URL request will
    be used if they apply to the particular URL being loaded, and will
    be ignored if they do not apply.
*/

/// Constants that specify the caching strategy for a URL load request.
///
/// Specifically, these constants cover interactions that have to do with whether already-existing cache data
/// is returned to satisfy a URL load request.
///
/// - `NSURLRequestUseProtocolCachePolicy`: The caching logic defined in the protocol implementation, if any, is used for a particular URL load request. This is the default policy.
/// - `NSURLRequestReloadIgnoringLocalCacheData`: The data for the URL load should be loaded from the origin source. No existing local cache data should be used.
/// - `NSURLRequestReloadIgnoringLocalAndRemoteCacheData`: Not only should local cache data be ignored, but proxies and other intermediates should be instructed to disregard their caches as far as the protocol allows.
/// - `NSURLRequestReloadIgnoringCacheData`: Older name for `NSURLRequestReloadIgnoringLocalCacheData`.
/// - `NSURLRequestReturnCacheDataElseLoad`: Existing cache data should be used, regardless of its age or expiration date. If no data exists in the cache, the URL is loaded from the origin source.
/// - `NSURLRequestReturnCacheDataDontLoad`: Existing cache data should be used, regardless of its age or expiration date. If no data exists in the cache, no attempt is made to load the URL. This constant specifies a behavior similar to an "offline" mode.
/// - `NSURLRequestReloadRevalidatingCacheData`: Existing cache data may be used provided the origin source confirms its validity, otherwise the URL is loaded from the origin source.
typedef NS_ENUM(NSUInteger, NSURLRequestCachePolicy)
{
    /// Use the caching logic defined in the protocol implementation, if any, for a particular URL load request.
    ///
    /// This is the default policy for URL load requests.
    NSURLRequestUseProtocolCachePolicy = 0,

    /// The URL load should be loaded only from the originating source.
    ///
    /// No existing cache data should be used to satisfy a URL load request.
    NSURLRequestReloadIgnoringLocalCacheData = 1,
    /// Ignore local cache data, and instruct proxies and other intermediates to disregard their caches so far as the protocol allows.
    NSURLRequestReloadIgnoringLocalAndRemoteCacheData = 4,
    /// Replaced by `NSURLRequestReloadIgnoringLocalCacheData`.
    NSURLRequestReloadIgnoringCacheData = NSURLRequestReloadIgnoringLocalCacheData,

    /// Use existing cache data, regardless of age or expiration date, loading from originating source only if there is no cached data.
    NSURLRequestReturnCacheDataElseLoad = 2,
    /// Use existing cache data, regardless of age or expiration date, and fail if no cached data is available.
    ///
    /// If there is no existing data in the cache corresponding to a URL load request, no attempt is made to load the data from the originating source, and the load is considered to have failed. This constant specifies a behavior that is similar to an "offline" mode.
    NSURLRequestReturnCacheDataDontLoad = 3,

    /// Use cache data if the origin source can validate it; otherwise, load from the origin.
    NSURLRequestReloadRevalidatingCacheData = 5,
};

/// Constants that specify the network service type of a request.
///
/// The service type is used to provide the networking layers a hint of the purpose of the request.
typedef NS_ENUM(NSUInteger, NSURLRequestNetworkServiceType)
{
    /// A service type for standard network traffic.
    NSURLNetworkServiceTypeDefault = 0,
    /// A service type for VoIP traffic.
    NSURLNetworkServiceTypeVoIP API_DEPRECATED("Use PushKit for VoIP control purposes", macos(10.7,10.15), ios(4.0,13.0), watchos(2.0,6.0), tvos(9.0,13.0)) = 1,
    /// A service type for low-delay tolerant, very low-loss tolerant, inelastic flow, and constant packet rate connections.
    NSURLNetworkServiceTypeVideo = 2,
    /// A service type for high-delay tolerant, high-loss tolerant, elastic flow, and variable size connections.
    NSURLNetworkServiceTypeBackground = 3,
    /// A service type for low-delay tolerant, very low-loss tolerant, inelastic flow, and constant packet rate connections.
    NSURLNetworkServiceTypeVoice = 4,
    /// A service type for medium-delay tolerant, elastic and inelastic flow, bursty, and long-lived connections.
    NSURLNetworkServiceTypeResponsiveData = 6,
    /// A service type for medium-delay tolerant, low-medium-loss tolerant, elastic flow, constant packet interval, and variable rate and size connections.
    NSURLNetworkServiceTypeAVStreaming API_AVAILABLE(macosx(10.9), ios(7.0), watchos(2.0), tvos(9.0)) = 8 ,
    /// A service type for low-delay tolerant, low-to-medium-loss tolerant, elastic flow, variable packet interval, rate, size responsive and time-sensitive connections.
    NSURLNetworkServiceTypeResponsiveAV API_AVAILABLE(macosx(10.9), ios(7.0), watchos(2.0), tvos(9.0)) = 9,
    /// A service for low-loss tolerant, inelastic flow, jitter tolerant, short but bursty rate, and variable size connections.
    NSURLNetworkServiceTypeCallSignaling API_AVAILABLE(macosx(10.12), ios(10.0), watchos(3.0), tvos(10.0)) = 11,
};

/// Constants that indicate whether the user or developer specified the URL.
///
/// - `NSURLRequestAttributionDeveloper`: The URL was specified by the developer. This is the default value.
/// - `NSURLRequestAttributionUser`: The URL was specified by the user.
typedef NS_ENUM(NSUInteger, NSURLRequestAttribution)
{
    /// A developer-initiated network request.
    ///
    /// This is the default value. Use this for any purpose other than when the user explicitly accesses a link.
    NSURLRequestAttributionDeveloper = 0,
    /// The user explicitly directs the app to make a network request.
    ///
    /// Use this for URL requests that satisfy a user request to access an explicit, unmodified URL.
    NSURLRequestAttributionUser = 1,
} API_AVAILABLE(macos(12.0), ios(15.0), watchos(8.0), tvos(15.0));

/// A URL load request that is independent of protocol or URL scheme.
///
/// Use this type in Swift when you need reference semantics or other Foundation-specific behavior.
///
/// ``NSURLRequest`` encapsulates two essential properties of a load request: the URL to load and the policies used to load it. In addition, for HTTP and HTTPS requests, ``URLRequest`` includes the HTTP method (`GET`, `POST`, and so on) and the HTTP headers. Finally, custom protocols can support custom properties as explained in <doc:#Custom-protocol-properties>.
///
/// ``NSURLRequest`` only represents information about the request. Use other classes, such as ``URLSession``, to send the request to a server. See <doc:fetching-website-data-into-memory> and <doc:uploading-data-to-a-website> for an introduction to these techniques.
///
/// The mutable subclass of ``NSURLRequest`` is ``NSMutableURLRequest``.
///
/// > Important:
/// > The Swift overlay to the Foundation framework provides the ``URLRequest`` structure, which bridges to the ``NSURLRequest`` class and its mutable subclass, ``NSMutableURLRequest``. For more information about value types, see <doc://com.apple.documentation/documentation/swift/working-with-foundation-types>.
///
/// ### Reserved HTTP headers
///
/// The URL Loading System handles various aspects of the HTTP protocol for you (HTTP 1.1 persistent connections, proxies, authentication, and so on). As part of this support, the URL Loading System takes responsibility for certain HTTP headers:
///
/// - `Content-Length`
/// - `Authorization`
/// - `Connection`
/// - `Host`
/// - `Proxy-Authenticate`
/// - `Proxy-Authorization`
/// - `WWW-Authenticate`
///
/// If you set a value for one of these reserved headers, the system may ignore the value you set, or overwrite it with its own value, or simply not send it. Moreover, the exact behavior may change over time. To avoid confusing problems like this, do not set these headers directly.
///
/// The URL Loading System sets the `Content-Length` header based on whether the request body has a known length:
///
/// - If so, it uses the identity transfer encoding and sets the `Content-Length` header to that known length. You see this when you set the request body to a data object.
/// - If not, it uses the chunked transfer encoding and omits the `Content-Length` header. You see this when you set the request body to a stream.
///
/// ### Custom protocol properties
///
/// If you implement a custom URL protocol by subclassing ``URLProtocol``, and it needs protocol-specific properties, extend ``NSURLRequest`` with accessor methods for those custom properties. In your accessor methods, call ``URLProtocol/property(forKey:in:)`` and ``URLProtocol/setProperty(_:forKey:in:)`` to associate property values with the request.
API_AVAILABLE(macos(10.2), ios(2.0), watchos(2.0), tvos(9.0))
@interface NSURLRequest : NSObject <NSSecureCoding, NSCopying, NSMutableCopying>
{
@private
    NSURLRequestInternal *_internal;
}

/// Allocates and initializes an `NSURLRequest` with the given URL.
///
/// Default values are used for cache policy (`NSURLRequestUseProtocolCachePolicy`) and timeout interval (60 seconds).
///
/// - Parameter URL: The URL for the request.
/// - Returns: A newly-created and autoreleased `NSURLRequest` instance.
+ (instancetype)requestWithURL:(NSURL *)URL;

/// Indicates that `NSURLRequest` implements the `NSSecureCoding` protocol.
@property (class, readonly) BOOL supportsSecureCoding;

/// Allocates and initializes an `NSURLRequest` with the given URL and cache policy.
///
/// - Parameters:
///   - URL: The URL for the request.
///   - cachePolicy: The cache policy for the request.
///   - timeoutInterval: The timeout interval for the request, in seconds.
/// - Returns: A newly-created and autoreleased `NSURLRequest` instance.
+ (instancetype)requestWithURL:(NSURL *)URL cachePolicy:(NSURLRequestCachePolicy)cachePolicy timeoutInterval:(NSTimeInterval)timeoutInterval;

/// Initializes an `NSURLRequest` with the given URL.
///
/// Default values are used for cache policy (`NSURLRequestUseProtocolCachePolicy`) and timeout interval (60 seconds).
///
/// - Parameter URL: The URL for the request.
/// - Returns: An initialized `NSURLRequest`.
- (instancetype)initWithURL:(NSURL *)URL;

/// Initializes an `NSURLRequest` with the given URL, cache policy, and timeout interval.
///
/// This is the designated initializer for the `NSURLRequest` class.
///
/// - Parameters:
///   - URL: The URL for the request.
///   - cachePolicy: The cache policy for the request.
///   - timeoutInterval: The timeout interval for the request, in seconds.
/// - Returns: An initialized `NSURLRequest`.
- (instancetype)initWithURL:(NSURL *)URL cachePolicy:(NSURLRequestCachePolicy)cachePolicy timeoutInterval:(NSTimeInterval)timeoutInterval NS_DESIGNATED_INITIALIZER;

/// The URL of the receiver.
@property (nullable, readonly, copy) NSURL *URL;

/// The cache policy of the receiver.
@property (readonly) NSURLRequestCachePolicy cachePolicy;

/// The timeout interval of the receiver, measured in seconds.
///
/// The timeout interval specifies the limit on the idle interval allotted to a request in the process of loading.
/// The "idle interval" is defined as the period of time that has passed since the last instance of load activity
/// occurred for a request that is in the process of loading. Hence, when an instance of load activity occurs
/// (e.g. bytes are received from the network for a request), the idle interval for a request is reset to 0. If
/// the idle interval ever becomes greater than or equal to the timeout interval, the request is considered to
/// have timed out.
@property (readonly) NSTimeInterval timeoutInterval;

/// The main document URL associated with this load.
///
/// This URL is used for the cookie "same domain as main document" policy, and attributing the request as a
/// sub-resource of a user-specified URL. There may also be other future uses.
@property (nullable, readonly, copy) NSURL *mainDocumentURL;

/// The `NSURLRequestNetworkServiceType` associated with this request.
///
/// Returns `NSURLNetworkServiceTypeDefault` for requests that have not explicitly set a network service type.
@property (readonly) NSURLRequestNetworkServiceType networkServiceType API_AVAILABLE(macos(10.7), ios(4.0), watchos(2.0), tvos(9.0));

/// A Boolean value that indicates whether a connection created with this request is allowed to use the built-in cellular radios (if present).
@property (readonly) BOOL allowsCellularAccess  API_AVAILABLE(macos(10.8), ios(6.0), watchos(2.0), tvos(9.0));

/// A Boolean value that indicates whether a connection created with this request is allowed to use network interfaces which have been marked as expensive.
@property (readonly) BOOL allowsExpensiveNetworkAccess API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0));

/// A Boolean value that indicates whether a connection created with this request is allowed to use network interfaces which have been marked as constrained.
@property (readonly) BOOL allowsConstrainedNetworkAccess API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0));

/// A Boolean value that indicates whether a connection created with this request is allowed to use network interfaces which have been marked as ultra constrained.
@property (readonly) BOOL allowsUltraConstrainedNetworkAccess API_AVAILABLE(macos(26.1), ios(26.1), watchos(26.1), tvos(26.1), visionos(26.1));

/// A Boolean value that indicates whether the server is assumed to support HTTP/3.
///
/// When `YES`, enables QUIC racing without HTTP/3 service discovery. Defaults to `NO`. The default may be `YES` in a future OS update.
@property (readonly) BOOL assumesHTTP3Capable API_AVAILABLE(macos(11.3), ios(14.5), watchos(7.4), tvos(14.5));

/// The `NSURLRequestAttribution` associated with this request.
///
/// Returns `NSURLRequestAttributionDeveloper` for requests that have not explicitly set an attribution.
@property (readonly) NSURLRequestAttribution attribution API_AVAILABLE(macos(12.0), ios(15.0), watchos(8.0), tvos(15.0));

/// A Boolean value that indicates whether a request requires DNSSEC validation during DNS lookup.
///
/// `YES` if the DNS lookup for this request should require DNSSEC validation. Defaults to `NO`.
@property (readonly) BOOL requiresDNSSECValidation API_AVAILABLE(macos(13.0), ios(16.1), watchos(9.1), tvos(16.1));

/// A Boolean value that indicates whether storing and usage of DNS answers in a persistent per-process cache is allowed.
///
/// This should only be set for hostnames whose resolutions are not expected to change across networks. Defaults to `NO`.
@property (readonly) BOOL allowsPersistentDNS API_AVAILABLE(macos(15.0), ios(18.0), watchos(11.0), tvos(18.0), visionos(2.0));

/*
 * Cookie partition identifier used for cookie storage and retrieval.
 */
@property (nullable, readonly, copy) NSString *cookiePartitionIdentifier API_AVAILABLE(macos(15.2), ios(18.2), watchos(11.2), tvos(18.2), visionos(2.2));

@end



/// A mutable URL load request that is independent of protocol or URL scheme.
///
/// In Swift, this object bridges to ``NSURLRequest`` and you use when you need reference semantics or other Foundation-specific behavior.
///
/// ``NSMutableURLRequest`` is a subclass of ``NSURLRequest`` that allows you to change the request's properties.
///
/// ``NSMutableURLRequest`` only represents information about the request. Use other classes, such as ``URLSession``, to send the request to a server. See <doc:fetching-website-data-into-memory> and <doc:uploading-data-to-a-website> for an introduction to these techniques.
///
/// Classes that create a network operation based on a request make a deep copy of that request. Thus, changing the request after creating a network operation has no effect on the ongoing operation. For example, if you use ``URLSession/dataTask(with:completionHandler:)-e6xv`` to create a data task from a request, and then later change the request, the data task continues using the original request.
///
/// > Important:
/// > The Swift overlay to the Foundation framework provides the ``URLRequest`` structure, which bridges to the ``NSMutableURLRequest`` class and its immutable superclass, ``NSURLRequest``. For more information about value types, see <doc://com.apple.documentation/documentation/swift/working-with-foundation-types>.
API_AVAILABLE(macos(10.2), ios(2.0), watchos(2.0), tvos(9.0))
@interface NSMutableURLRequest : NSURLRequest

/// The URL of the receiver.
@property (nullable, copy) NSURL *URL;

/// The cache policy of the receiver.
@property NSURLRequestCachePolicy cachePolicy;

/// The timeout interval of the receiver, measured in seconds.
///
/// The timeout interval specifies the limit on the idle interval allotted to a request in the process of loading.
/// The "idle interval" is defined as the period of time that has passed since the last instance of load activity
/// occurred for a request that is in the process of loading. Hence, when an instance of load activity occurs
/// (e.g. bytes are received from the network for a request), the idle interval for a request is reset to 0. If
/// the idle interval ever becomes greater than or equal to the timeout interval, the request is considered to
/// have timed out.
@property NSTimeInterval timeoutInterval;

/// The main document URL.
///
/// The caller should pass the URL for an appropriate main document, if known. For example, when loading a web page,
/// the URL of the main html document for the top-level frame should be passed. This main document is used to
/// implement the cookie "only from same domain as main document" policy, attributing this request as a sub-resource
/// of a user-specified URL, and possibly other things in the future.
@property (nullable, copy) NSURL *mainDocumentURL;

/// The `NSURLRequestNetworkServiceType` to associate with this request.
///
/// This is used to provide the network layers with a hint as to the purpose of the request. Most clients should not need to set this.
@property NSURLRequestNetworkServiceType networkServiceType API_AVAILABLE(macos(10.7), ios(4.0), watchos(2.0), tvos(9.0));

/// A Boolean value that indicates whether a connection created with this request is allowed to use the built-in cellular radios (if present).
///
/// The default is `YES`.
@property BOOL allowsCellularAccess API_AVAILABLE(macos(10.8), ios(6.0), watchos(2.0), tvos(9.0));

/// A Boolean value that indicates whether a connection created with this request is allowed to use network interfaces which have been marked as expensive.
@property BOOL allowsExpensiveNetworkAccess API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0));

/// A Boolean value that indicates whether a connection created with this request is allowed to use network interfaces which have been marked as constrained.
@property BOOL allowsConstrainedNetworkAccess API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0));

/// A Boolean value that indicates whether a connection created with this request is allowed to use network interfaces which have been marked as ultra constrained.
@property BOOL allowsUltraConstrainedNetworkAccess API_AVAILABLE(macos(26.1), ios(26.1), watchos(26.1), tvos(26.1), visionos(26.1));

/// A Boolean value that indicates whether the server is assumed to support HTTP/3.
///
/// When `YES`, enables QUIC racing without HTTP/3 service discovery. Defaults to `NO`. The default may be `YES` in a future OS update.
@property BOOL assumesHTTP3Capable API_AVAILABLE(macos(11.3), ios(14.5), watchos(7.4), tvos(14.5));

/// The `NSURLRequestAttribution` to associate with this request.
///
/// Set to `NSURLRequestAttributionUser` if the URL was specified by the user. Defaults to `NSURLRequestAttributionDeveloper`.
@property NSURLRequestAttribution attribution API_AVAILABLE(macos(12.0), ios(15.0), watchos(8.0), tvos(15.0));

/// A Boolean value that indicates whether a request requires DNSSEC validation during DNS lookup.
///
/// `YES` if the DNS lookup for this request should require DNSSEC validation. Defaults to `NO`.
@property BOOL requiresDNSSECValidation API_AVAILABLE(macos(13.0), ios(16.1), watchos(9.1), tvos(16.1));

/// A Boolean value that indicates whether storing and usage of DNS answers in a persistent per-process cache is allowed.
///
/// This should only be set for hostnames whose resolutions are not expected to change across networks. Defaults to `NO`.
@property BOOL allowsPersistentDNS API_AVAILABLE(macos(15.0), ios(18.0), watchos(11.0), tvos(18.0), visionos(2.0));

/*
* Cookie partition identifier used for cookie storage and retrieval.
*/
@property (nullable, copy) NSString *cookiePartitionIdentifier API_AVAILABLE(macos(15.2), ios(18.2), watchos(11.2), tvos(18.2), visionos(2.2));

@end



/// The `NSHTTPURLRequest` category on `NSURLRequest` provides methods for accessing information specific to HTTP protocol requests.
@interface NSURLRequest (NSHTTPURLRequest)

/// The HTTP request method of the receiver.
@property (nullable, readonly, copy) NSString *HTTPMethod;

/// A dictionary containing all the HTTP header fields of the receiver.
@property (nullable, readonly, copy) NSDictionary<NSString *, NSString *> *allHTTPHeaderFields;

/// Returns the value which corresponds to the given header field.
///
/// In keeping with the HTTP RFC, HTTP header field names are case-insensitive.
///
/// - Parameter field: The header field name to use for the lookup (case-insensitive).
/// - Returns: The value associated with the given header field, or `nil` if there is no value associated with the given header field.
- (nullable NSString *)valueForHTTPHeaderField:(NSString *)field;

/// The request body data of the receiver.
///
/// This data is sent as the message body of the request, as in done in an HTTP POST request.
@property (nullable, readonly, copy) NSData *HTTPBody;

/// The request body stream of the receiver, if any.
///
/// The stream is returned for examination only; it is not safe for the caller to manipulate the stream in any way.
/// Note that the `HTTPBodyStream` and `HTTPBody` are mutually exclusive - only one can be set on a given request.
/// Also note that the body stream is preserved across copies, but is lost when the request is coded via the `NSCoding` protocol.
@property (nullable, readonly, retain) NSInputStream *HTTPBodyStream;

/// A Boolean value that indicates whether the default cookie handling will happen for this request.
@property (readonly) BOOL HTTPShouldHandleCookies;

/// A Boolean value that indicates whether the request should not wait for the previous response before transmitting.
@property (readonly) BOOL HTTPShouldUsePipelining API_DEPRECATED("Only supported in the classic loader, please adopt HTTP/2 and HTTP/3 instead", macos(10.7,15.4), ios(4.0,18.4), watchos(2.0,11.4), tvos(9.0,18.4), visionos(1.0,2.4));

@end



/// The `NSMutableHTTPURLRequest` category on `NSMutableURLRequest` provides methods for configuring information specific to HTTP protocol requests.
@interface NSMutableURLRequest (NSMutableHTTPURLRequest)

/// The HTTP request method of the receiver.
@property (copy) NSString *HTTPMethod;

/// The HTTP header fields of the receiver.
///
/// Setting this property replaces all header fields that may have existed before this method call.
/// Since HTTP header fields must be string values, each object and key in the dictionary must be an `NSString`.
@property (nullable, copy) NSDictionary<NSString *, NSString *> *allHTTPHeaderFields;

/// Sets the value of the given HTTP header field.
///
/// If a value was previously set for the given header field, that value is replaced with the given value.
/// In keeping with the HTTP RFC, HTTP header field names are case-insensitive.
///
/// - Parameters:
///   - value: The header field value.
///   - field: The header field name (case-insensitive).
- (void)setValue:(nullable NSString *)value forHTTPHeaderField:(NSString *)field;

/// Adds an HTTP header field value to the current header dictionary.
///
/// If a value was previously set for the given header field, the given value is appended to the
/// previously-existing value. The appropriate field delimiter, a comma in the case of HTTP, is added
/// by the implementation. In keeping with the HTTP RFC, HTTP header field names are case-insensitive.
///
/// - Parameters:
///   - value: The header field value.
///   - field: The header field name (case-insensitive).
- (void)addValue:(NSString *)value forHTTPHeaderField:(NSString *)field;

/// The request body data of the receiver.
///
/// This data is sent as the message body of the request, as in done in an HTTP POST request.
@property (nullable, copy) NSData *HTTPBody;

/// The request body stream of the receiver.
///
/// The provided stream should be unopened; the request will take over the stream's delegate. The entire
/// stream's contents will be transmitted as the HTTP body of the request. Note that the body stream and the
/// body data (set by `setHTTPBody:`) are mutually exclusive - setting one will clear the other.
@property (nullable, retain) NSInputStream *HTTPBodyStream;

/// A Boolean value that indicates whether default cookie handling will happen for this request.
///
/// The default is `YES` - in other words, cookies are sent from and stored to the cookie manager by default.
@property BOOL HTTPShouldHandleCookies;

/// A Boolean value that indicates whether the request should not wait for the previous response before transmitting.
///
/// Calling this method with a `YES` value does not guarantee HTTP pipelining behavior. This method may have
/// no effect if an HTTP proxy is configured, or if the HTTP request uses an unsafe request method (e.g., POST
/// requests will not pipeline).
@property BOOL HTTPShouldUsePipelining API_DEPRECATED("Only supported in the classic loader, please adopt HTTP/2 and HTTP/3 instead", macos(10.7,15.4), ios(4.0,18.4), watchos(2.0,11.4), tvos(9.0,18.4), visionos(1.0,2.4));

@end

NS_HEADER_AUDIT_END(nullability, sendability)
