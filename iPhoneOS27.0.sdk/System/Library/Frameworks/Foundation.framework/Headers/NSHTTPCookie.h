/*	
    NSHTTPCookie.h
    Copyright (c) 2003-2019, Apple Inc. All rights reserved.    
    
    Public header file.
*/

#import <Foundation/NSObject.h>

@class NSArray<ObjectType>;
@class NSDate;
@class NSDictionary<KeyType, ObjectType>;
@class NSNumber;
@class NSString;
@class NSURL;

/// Constants that define the supported keys in a cookie attributes dictionary.
typedef NSString * NSHTTPCookiePropertyKey NS_TYPED_EXTENSIBLE_ENUM;
/// Values that indicate whether to restrict the cookie to requests sent back to the same site that created it.
///
/// ## Discussion
///
/// [RFC 6265](https://tools.ietf.org/html/draft-ietf-httpbis-cookie-same-site-00) defines "same site" as the registerable domain of a URI.
typedef NSString * NSHTTPCookieStringPolicy NS_TYPED_ENUM;

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

/// An `NSString` object containing the name of the cookie (required).
FOUNDATION_EXPORT NSHTTPCookiePropertyKey const NSHTTPCookieName API_AVAILABLE(macos(10.2), ios(2.0), watchos(2.0), tvos(9.0));

/// An `NSString` object containing the value of the cookie.
///
/// This cookie attribute is required.
FOUNDATION_EXPORT NSHTTPCookiePropertyKey const NSHTTPCookieValue API_AVAILABLE(macos(10.2), ios(2.0), watchos(2.0), tvos(9.0));

/// An NSURL or `NSString` object containing the URL that set this cookie.
///
/// If you do not provide a value for `NSHTTPCookieOriginURL`, you must provide a value for `NSHTTPCookieDomain`.
FOUNDATION_EXPORT NSHTTPCookiePropertyKey const NSHTTPCookieOriginURL API_AVAILABLE(macos(10.2), ios(2.0), watchos(2.0), tvos(9.0));

/// An `NSString` object that specifies the version of the cookie.
///
/// Must be either `"0"` or `"1"`. The default is `"0"`. This cookie attribute is optional.
FOUNDATION_EXPORT NSHTTPCookiePropertyKey const NSHTTPCookieVersion API_AVAILABLE(macos(10.2), ios(2.0), watchos(2.0), tvos(9.0));

/// An `NSString` object containing the domain for the cookie.
///
/// If this cookie attribute is missing, the domain is inferred from the value for `NSHTTPCookieOriginURL`. If you do not
/// specify a value for `NSHTTPCookieOriginURL`, you _must_ specify a value for `NSHTTPCookieDomain`.
FOUNDATION_EXPORT NSHTTPCookiePropertyKey const NSHTTPCookieDomain API_AVAILABLE(macos(10.2), ios(2.0), watchos(2.0), tvos(9.0));

/// An `NSString` object containing the path for the cookie.
///
/// This cookie attribute is required.
FOUNDATION_EXPORT NSHTTPCookiePropertyKey const NSHTTPCookiePath API_AVAILABLE(macos(10.2), ios(2.0), watchos(2.0), tvos(9.0));

/// An `NSString` object indicating that the cookie should be transmitted only over secure channels.
///
/// Providing any value for this key indicates that the cookie should remain secure.
FOUNDATION_EXPORT NSHTTPCookiePropertyKey const NSHTTPCookieSecure API_AVAILABLE(macos(10.2), ios(2.0), watchos(2.0), tvos(9.0));

/// An `NSDate` object or `NSString` object specifying the expiration date for the cookie.
///
/// This cookie attribute is only used for Version 0 cookies. This cookie attribute is optional.
FOUNDATION_EXPORT NSHTTPCookiePropertyKey const NSHTTPCookieExpires API_AVAILABLE(macos(10.2), ios(2.0), watchos(2.0), tvos(9.0));

/// An `NSString` object containing the comment for the cookie.
///
/// Only valid for Version 1 cookies and later. This cookie attribute is optional.
FOUNDATION_EXPORT NSHTTPCookiePropertyKey const NSHTTPCookieComment API_AVAILABLE(macos(10.2), ios(2.0), watchos(2.0), tvos(9.0));

/// An `NSURL` object or `NSString` object containing the comment URL for the cookie.
///
/// Only valid for Version 1 cookies or later. This cookie attribute is optional.
FOUNDATION_EXPORT NSHTTPCookiePropertyKey const NSHTTPCookieCommentURL API_AVAILABLE(macos(10.2), ios(2.0), watchos(2.0), tvos(9.0));

/// An `NSString` object stating whether the cookie should be discarded at the end of the session.
///
/// String value must be either `"TRUE"` or `"FALSE"`. This cookie attribute is optional. The default is `"FALSE"`, unless this
/// cookie is version 1 or greater and a value for `NSHTTPCookieMaximumAge` is not specified, in which case it is assumed to be `"TRUE"`.
FOUNDATION_EXPORT NSHTTPCookiePropertyKey const NSHTTPCookieDiscard API_AVAILABLE(macos(10.2), ios(2.0), watchos(2.0), tvos(9.0));

/// An `NSString` object containing an integer value stating how long in seconds the cookie should be kept, at most.
///
/// Only valid for Version 1 cookies and later. Default is `"0"`. This cookie attribute is optional.
FOUNDATION_EXPORT NSHTTPCookiePropertyKey const NSHTTPCookieMaximumAge API_AVAILABLE(macos(10.2), ios(2.0), watchos(2.0), tvos(9.0));

/// An `NSString` object containing comma-separated integer values specifying the ports for the cookie.
///
/// Only valid for Version 1 cookies or later. The default value is an empty string (`""`). This cookie attribute is optional.
FOUNDATION_EXPORT NSHTTPCookiePropertyKey const NSHTTPCookiePort API_AVAILABLE(macos(10.2), ios(2.0), watchos(2.0), tvos(9.0));

/// An NSString object indicating that the cookie is set via JavaScript.
 FOUNDATION_EXPORT NSHTTPCookiePropertyKey const NSHTTPCookieSetByJavaScript API_AVAILABLE(macos(15.2), ios(18.2), watchos(11.2), tvos(18.2), visionos(2.2));

/// A string indicating the same-site policy for the cookie.
FOUNDATION_EXPORT NSHTTPCookiePropertyKey const NSHTTPCookieSameSitePolicy API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0));

/// A policy that allows certain cross-site requests to include the cookie.
///
/// When a cookie has this policy, a request includes the cookie if the request is "top-level," meaning one that changes the URL in the address bar.
FOUNDATION_EXPORT NSHTTPCookieStringPolicy const NSHTTPCookieSameSiteLax API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0));

/// A policy that prohibits a cross-site request from including the cookie.
FOUNDATION_EXPORT NSHTTPCookieStringPolicy const NSHTTPCookieSameSiteStrict API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0));

@class NSHTTPCookieInternal;

/// A representation of an HTTP cookie.
///
/// An ``HTTPCookie`` object is immutable, initialized from a dictionary that contains the attributes of the cookie. This class supports two different cookie versions:
///
/// - Version 0: The original cookie format defined by Netscape. Most cookies are in this format.
/// - Version 1: The cookie format defined in [RFC 6265](https://tools.ietf.org/html/rfc6265), HTTP State Management Mechanism.
NS_SWIFT_SENDABLE
API_AVAILABLE(macos(10.2), ios(2.0), watchos(2.0), tvos(9.0))
@interface NSHTTPCookie : NSObject
{
@private
    NSHTTPCookieInternal * _cookiePrivate;
}

/// Initializes an HTTP cookie object with the given cookie properties.
///
/// - Parameter properties: The properties for the new cookie object, expressed as key-value pairs.
/// - Returns: An initialized `NSHTTPCookie`, or `nil` if the provided properties are invalid. To successfully create a cookie, you
///   must provide values for (at least) the path, name, and value keys, and either the origin URL key or the domain key.
///
/// See the `NSHTTPCookie` `-initWithProperties:` method for more information on the constraints
/// imposed on the dictionary, and for descriptions of the supported keys and values.
- (nullable instancetype)initWithProperties:(NSDictionary<NSHTTPCookiePropertyKey, id> *)properties;

/// Allocates and initializes an `NSHTTPCookie` with the given dictionary.
///
/// - Parameter properties: The dictionary to use to initialize this cookie.
/// - Returns: A newly-created and autoreleased `NSHTTPCookie` instance, or `nil` if the set of
///   dictionary keys is invalid, for example because a required key is missing, or a recognized key maps to an illegal value.
///
/// See the `NSHTTPCookie` `-initWithProperties:` method for more information on the constraints
/// imposed on the dictionary, and for descriptions of the supported keys and values.
+ (nullable NSHTTPCookie *)cookieWithProperties:(NSDictionary<NSHTTPCookiePropertyKey, id> *)properties;

/// Converts an array of cookies to a dictionary of header fields.
///
/// - Parameter cookies: The cookies from which the header fields are created.
/// - Returns: An `NSDictionary` where the keys are header field names, and the values are the corresponding header field values.
+ (NSDictionary<NSString *, NSString *> *)requestHeaderFieldsWithCookies:(NSArray<NSHTTPCookie *> *)cookies;

/// Creates an array of HTTP cookies that corresponds to the provided response header fields for the provided URL.
///
/// - Parameter headerFields: The response header fields to check for cookies.
/// - Parameter URL: The URL that the cookies came from, relevant to how the cookies are interpreted.
/// - Returns: An `NSArray` of `NSHTTPCookie` objects.
///
/// This method ignores irrelevant header fields in `headerFields`, allowing dictionaries to contain additional data.
+ (NSArray<NSHTTPCookie *> *)cookiesWithResponseHeaderFields:(NSDictionary<NSString *, NSString *> *)headerFields forURL:(NSURL *)URL;

/// The cookie's properties.
///
/// This dictionary can be used with `-initWithProperties:` or `+cookieWithProperties:` to create an equivalent `NSHTTPCookie` object.
@property (nullable, readonly, copy) NSDictionary<NSHTTPCookiePropertyKey, id> *properties;

/// The cookie's version.
///
/// Version 0 maps to "old-style" Netscape cookies. Version 1 maps to RFC 2965 cookies. There may be future versions.
@property (readonly) NSUInteger version;

/// The cookie's name.
@property (readonly, copy) NSString *name;

/// The cookie's string value.
@property (readonly, copy) NSString *value;

/// The cookie's expiration date.
///
/// This value is `nil` if there is no specific expiration date, as with session-only cookies.
/// The expiration date is the date when the cookie should be deleted.
@property (nullable, readonly, copy) NSDate *expiresDate;

/// A Boolean value that indicates whether the cookie should be discarded at the end of the session (regardless of expiration date).
@property (readonly, getter=isSessionOnly) BOOL sessionOnly;

/// The domain of the cookie.
///
/// If the domain does not start with a dot, then the cookie is only sent to the exact host specified by the domain. If the domain
/// does start with a dot, then the cookie is sent to other hosts in that domain as well, subject to certain restrictions.
/// See RFC 6265 for more detail.
@property (readonly, copy) NSString *domain;

/// The cookie's path.
///
/// The cookie will be sent with requests for this path in the cookie's domain, and all paths that have this prefix.
/// A path of `"/"` means the cookie will be sent for all URLs in the domain.
@property (readonly, copy) NSString *path;

/// A Boolean value that indicates whether the cookie may only be sent over secure channels.
///
/// Cookies may be marked secure by a server (or by a javascript). Cookies marked as such must only be sent via an
/// encrypted connection to trusted servers (i.e. via SSL or TLS), and should not be delivered to any javascript
/// applications to prevent cross-site scripting vulnerabilities.
@property (readonly, getter=isSecure) BOOL secure;

/// A Boolean value that indicates whether the cookie should only be sent to HTTP servers.
///
/// Cookies can be marked as HTTP-only by a server (or by JavaScript code). Cookies marked as such must only be sent
/// via HTTP Headers in HTTP requests for URLs that match both the path and domain of the respective cookies.
///
/// > Important: To prevent cross-site scripting vulnerabilities, don't deliver cookies marked as HTTP-only to JavaScript code.
@property (readonly, getter=isHTTPOnly) BOOL HTTPOnly;

/// The cookie's comment string.
///
/// This value is `nil` if the cookie has no comment. You can present this string to the user,
/// explaining the contents and purpose of this cookie.
@property (nullable, readonly, copy) NSString *comment;

/// The cookie's comment URL.
///
/// This value is `nil` if the cookie has no comment URL. This value specifies a URL that can be presented to the
/// user as a link for further information about this cookie.
@property (nullable, readonly, copy) NSURL *commentURL;

/// The cookie's port list.
///
/// The list of ports for the cookie, returned as an array of `NSNumber` objects containing integers.
/// If the cookie has no port list, the value of this property is `nil` and the cookie will be sent to any port.
/// Otherwise, the cookie is only sent to ports specified in the port list.
@property (nullable, readonly, copy) NSArray<NSNumber *> *portList;

/// A Boolean value that indicates whether to restrict the cookie to requests sent back to the same site that created it.
///
/// Cookies can be marked with an attribute Strict or Lax.
/// Cookies marked with "strict" (`NSHTTPCookieSameSiteStrict`) are not sent along with cross-site requests.
/// Cookies marked with "lax" (`NSHTTPCookieSameSiteLax`) are sent along cross-site requests provided the
/// cross-site requests are top-level requests (one that changes the URL in the address bar).
/// The result could also be `nil`, in which case the cookie will be sent along with all cross-site requests.
@property (nullable, readonly, copy) NSHTTPCookieStringPolicy sameSitePolicy API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0));

@end

NS_HEADER_AUDIT_END(nullability, sendability)
