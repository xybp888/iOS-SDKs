/*	
    NSURLResponse.h
    Copyright (c) 2003-2019, Apple Inc. All rights reserved.    
    
    Public header file.
*/


#import <Foundation/NSObject.h>

@class NSDictionary<KeyType, ObjectType>;
@class NSString;
@class NSURL;
@class NSURLRequest;
@class NSURLResponseInternal;

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

/// The response length cannot be determined in advance of receiving the data from the server.
///
/// For example, `NSURLResponseUnknownLength` is returned when the server HTTP response does not
/// include a `Content-Length` header.
#define NSURLResponseUnknownLength ((long long)-1)

/// The metadata associated with the response to a URL load request, independent of protocol and URL scheme.
///
/// The related ``HTTPURLResponse`` class is a commonly used subclass of ``URLResponse`` whose objects represent a response to an HTTP URL load request and store additional protocol-specific information such as the response headers. Whenever you make an HTTP request, the ``URLResponse`` object you get back is actually an instance of the ``HTTPURLResponse`` class.
///
/// > Note:
/// > ``URLResponse`` objects don't contain the actual bytes representing the content of a URL. Instead, the data is returned either a piece at a time through delegate calls or in its entirety when the request completes, depending on the method and class used to initiate the request.
/// >
/// > Read <doc:fetching-website-data-into-memory> to learn various ways to receive the content data from a URL load.
NS_SWIFT_SENDABLE
API_AVAILABLE(macos(10.2), ios(2.0), watchos(2.0), tvos(9.0))
@interface NSURLResponse : NSObject <NSSecureCoding, NSCopying>
{
    @package
    NSURLResponseInternal *_internal;
}

/// Creates an initialized `NSURLResponse` object with the URL, MIME type, length, and text encoding set to given values.
///
/// This is the designated initializer for `NSURLResponse`.
///
/// - Parameters:
///   - URL: The URL for the new object.
///   - MIMEType: The MIME content type of the response.
///   - length: The expected content length. This value should be `-1` if the expected length is undetermined.
///   - name: The name of the text encoding for the associated data, if applicable, else `nil`.
/// - Returns: The initialized URL response.
- (instancetype)initWithURL:(NSURL *)URL MIMEType:(nullable NSString *)MIMEType expectedContentLength:(NSInteger)length textEncodingName:(nullable NSString *)name NS_DESIGNATED_INITIALIZER;

/// The URL for the response.
@property (nullable, readonly, copy) NSURL *URL;

/// The MIME type of the response.
///
/// The MIME type is often provided by the response's originating source. However, that value may be changed or
/// corrected by a protocol implementation if it can be determined that the response's source reported the
/// information incorrectly. If the response's originating source does not provide a MIME type, an attempt to
/// guess the MIME type may be made.
@property (nullable, readonly, copy) NSString *MIMEType;

/// The expected length of the response's content.
///
/// This property's value is `NSURLResponseUnknownLength` if the length can't be determined.
/// Some protocol implementations report the content length as part of the response, but not all protocols
/// guarantee to deliver that amount of data. Your app should be prepared to deal with more or less data.
@property (readonly) long long expectedContentLength;

/// The name of the text encoding provided by the response's originating source.
///
/// If no text encoding was provided by the protocol, this property's value is `nil`.
/// You can convert this string to a `CFStringEncoding` value by calling `CFStringConvertIANACharSetNameToEncoding(_:)`.
/// You can subsequently convert that value to an `NSStringEncoding` value by calling
/// `CFStringConvertEncodingToNSStringEncoding(_:)`.
@property (nullable, readonly, copy) NSString *textEncodingName;

/// A suggested filename for the response data.
///
/// Accessing this property attempts to generate a filename using the following information, in order:
/// 1. A filename specified using the content disposition header.
/// 2. The last path component of the URL.
/// 3. The host of the URL.
///
/// If the host of URL can't be converted to a valid filename, the filename `"unknown"` is used.
/// In most cases, this property appends the proper file extension based on the MIME type.
/// Accessing this property always returns a valid filename regardless of whether the resource is saved to disk.
@property (nullable, readonly, copy) NSString *suggestedFilename;

@end



@class NSHTTPURLResponseInternal;

/// The metadata associated with the response to an HTTP protocol URL load request.
///
/// The ``HTTPURLResponse`` class is a subclass of ``URLResponse`` that provides methods for accessing information specific to HTTP protocol responses. Whenever you make HTTP URL load requests, any response objects you get back from the ``URLSession``, ``NSURLConnection``, or ``NSURLDownload`` class are instances of the ``HTTPURLResponse`` class.
NS_SWIFT_SENDABLE
API_AVAILABLE(macos(10.2), ios(2.0), watchos(2.0), tvos(9.0))
@interface NSHTTPURLResponse : NSURLResponse 
{
    @package
    NSHTTPURLResponseInternal *_httpInternal;
}

/// Initializes an HTTP URL response object with a status code, protocol version, and response headers.
///
/// - Parameters:
///   - url: The URL from which the response was generated.
///   - statusCode: An HTTP status code. See [RFC 2616](http://www.ietf.org/rfc/rfc2616.txt) for details.
///   - HTTPVersion: The version of the HTTP response as represented by the server. This is typically represented as `"HTTP/1.1"`.
///   - headerFields: A dictionary representing the header keys and values of the server response.
/// - Returns: An initialized `NSHTTPURLResponse` object, or `nil` if an error occurred during initialization.
- (nullable instancetype)initWithURL:(NSURL *)url statusCode:(NSInteger)statusCode HTTPVersion:(nullable NSString *)HTTPVersion headerFields:(nullable NSDictionary<NSString *, NSString *> *)headerFields API_AVAILABLE(macos(10.7), ios(5.0), watchos(2.0), tvos(9.0));

/// The response's HTTP status code.
///
/// See [RFC 2616](http://www.ietf.org/rfc/rfc2616.txt) for details.
@property (readonly) NSInteger statusCode;

/// All HTTP header fields of the response.
///
/// The value of this property is a dictionary that contains all the HTTP header fields received as part of
/// the server's response. By examining this dictionary, clients can see the "raw" header information returned
/// by the HTTP server.
///
/// HTTP headers are case insensitive. To simplify your code, URL Loading System canonicalizes certain header
/// field names into their standard form. For example, if the server sends a `content-length` header, it's
/// automatically adjusted to be `Content-Length`.
///
/// When using Swift, this property is a standard dictionary, so its keys are case-sensitive.
/// To perform a case-insensitive header lookup, use the `valueForHTTPHeaderField:` method instead.
@property (readonly, copy) NSDictionary *allHeaderFields;

/// Returns the value that corresponds to the given header field.
///
/// In keeping with the HTTP RFC, HTTP header field names are case-insensitive.
///
/// - Parameter field: The header field name to use for the lookup (case-insensitive).
/// - Returns: The value associated with the given header field, or `nil` if there is no value associated with the given header field.
- (nullable NSString *)valueForHTTPHeaderField:(NSString *)field API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0));

/// Returns a localized string corresponding to a specified HTTP status code.
///
/// - Parameter statusCode: The HTTP status code. See [RFC 2616](http://www.ietf.org/rfc/rfc2616.txt) for details.
/// - Returns: A localized string suitable for displaying to users that describes the specified status code.
+ (NSString *)localizedStringForStatusCode:(NSInteger)statusCode;

@end

NS_HEADER_AUDIT_END(nullability, sendability)
