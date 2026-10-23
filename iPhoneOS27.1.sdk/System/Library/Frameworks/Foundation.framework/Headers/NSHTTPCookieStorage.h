/*	
    NSHTTPCookieStorage.h
    Copyright (c) 2003-2019, Apple Inc. All rights reserved.    
    
    Public header file.
*/

#import <Foundation/NSObject.h>
#import <Foundation/NSNotification.h>

@class NSArray<ObjectType>;
@class NSHTTPCookie;
@class NSURL;
@class NSDate;
@class NSURLSessionTask;
@class NSSortDescriptor;

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

/// Cookie acceptance policies implemented by the `NSHTTPCookieStorage` class.
///
/// - `NSHTTPCookieAcceptPolicyAlways`: Accept all cookies.
/// - `NSHTTPCookieAcceptPolicyNever`: Reject all cookies.
/// - `NSHTTPCookieAcceptPolicyOnlyFromMainDocumentDomain`: Accept cookies only from the main document domain.
typedef NS_ENUM(NSUInteger, NSHTTPCookieAcceptPolicy) {
    /// Accept all cookies. This is the default cookie accept policy.
    NSHTTPCookieAcceptPolicyAlways,
    /// Reject all cookies.
    NSHTTPCookieAcceptPolicyNever,
    /// Accept cookies only from the main document domain.
    NSHTTPCookieAcceptPolicyOnlyFromMainDocumentDomain
};


@class NSHTTPCookieStorageInternal;

/// A container that manages the storage of cookies.
///
/// Each stored cookie is represented by an instance of the ``HTTPCookie`` class.
///
/// ### Sharing cookie storage
///
/// The persistent cookie storage returned by ``shared`` may be available to app extensions or other apps, subject to the following guidelines:
///
/// - iOS — Each app and app extension has a unique data container, meaning  they have separate cookie stores. You can obtain a common cookie storage by using the ``sharedCookieStorage(forGroupContainerIdentifier:)`` method.
/// - macOS (non-sandboxed) — As of macOS 10.11, each app has its own cookie storage. Prior to macOS 10.11, a common cookie store is shared among the user's apps.
/// - macOS (sandboxed) — Same as iOS.
/// - <doc://com.apple.documentation/documentation/uikit/uiwebview> — `UIWebView` instances within an app inherit the parent app's shared cookie storage.
/// - <doc://com.apple.documentation/documentation/webkit/wkwebview> — Each `WKWebView` instance has its own cookie storage. See the <doc://com.apple.documentation/documentation/webkit/wkhttpcookiestore> class for more information.
///
/// Session cookies (where the cookie object's ``HTTPCookie/isSessionOnly`` property is <doc://com.apple.documentation/documentation/swift/true>) are local to a single process and are not shared.
///
/// > Note:
/// > In cases where a cookie storage is shared between processes, changes made to the cookie accept policy affect all currently running apps using the cookie storage.
///
///
///
/// ### Subclassing notes
///
/// The ``HTTPCookieStorage`` class is usable as-is, but you can subclass it. For example, you can override the storage methods like ``storeCookies(_:for:)``, ``getCookiesFor(_:completionHandler:)`` to screen which cookies are stored, or reimplement the storage mechanism for security or other reasons.
///
/// When overriding methods of this class, be aware that methods that take a `task` parameter are preferred by the system to equivalent methods that do not. Therefore, you should override the task-based methods when subclassing, as follows:
///
/// - Retrieving cookies — Override ``getCookiesFor(_:completionHandler:)``, instead of or in addition to ``cookies(for:)``.
/// - Adding cookies — Override ``storeCookies(_:for:)``, instead of or in addition to ``setCookies(_:for:mainDocumentURL:)``.
NS_SWIFT_SENDABLE
API_AVAILABLE(macos(10.2), ios(2.0), watchos(2.0), tvos(9.0))
@interface NSHTTPCookieStorage : NSObject
{
    @private
    NSHTTPCookieStorageInternal *_internal;
}

/// The shared cookie storage instance.
///
/// Starting in OS X 10.11, each app has its own `sharedHTTPCookieStorage` singleton,
/// which will not be shared with other applications.
@property(class, readonly, strong) NSHTTPCookieStorage *sharedHTTPCookieStorage;

/// Returns the cookie storage instance for the container associated with the specified app group identifier.
///
/// - Parameter identifier: The application group identifier.
/// - Returns: A cookie storage with a persistent store in the application group container.
///
/// By default, apps and associated app extensions will have different data containers. As a result, the
/// `sharedHTTPCookieStorage` singleton will refer to different persistent cookie stores when called by the app and by
/// its extensions. You can use this method to create a persistent cookie storage available to all apps and extensions
/// with access to the same app group. Subsequent calls to this method with the same identifier will return the same
/// cookie storage instance.
+ (NSHTTPCookieStorage *)sharedCookieStorageForGroupContainerIdentifier:(NSString *)identifier API_AVAILABLE(macos(10.11), ios(9.0), watchos(2.0), tvos(9.0));

/// The cookie storage's cookies.
///
/// If you want to sort the cookie storage's cookies, you should use the `sortedCookiesUsingDescriptors:` method instead
/// of sorting the result of this property.
@property (nullable , readonly, copy) NSArray<NSHTTPCookie *> *cookies;

/// Stores a specified cookie in the cookie storage if the cookie accept policy permits.
///
/// The cookie replaces an existing cookie with the same name, domain, and path, if one exists.
- (void)setCookie:(NSHTTPCookie *)cookie;

/// Deletes the specified cookie from the cookie storage.
- (void)deleteCookie:(NSHTTPCookie *)cookie;

/// Removes cookies that were stored after a given date.
- (void)removeCookiesSinceDate:(NSDate *)date API_AVAILABLE(macos(10.10), ios(8.0), watchos(2.0), tvos(9.0));

/// Returns all the cookie storage's cookies that are sent to a specified URL.
///
/// - Parameter URL: The URL to filter on.
/// - Returns: An array of cookies whose URL matches the provided URL.
///
/// You can use `+[NSHTTPCookie requestHeaderFieldsWithCookies:]` to turn this array into a set of header fields
/// to add to a request.
- (nullable NSArray<NSHTTPCookie *> *)cookiesForURL:(NSURL *)URL;

/// Adds an array of cookies to the cookie store, following the cookie accept policy.
///
/// - Parameter cookies: The cookies to set.
/// - Parameter URL: The URL from which the cookies were sent.
/// - Parameter mainDocumentURL: The main document URL to be used as a base for the "same domain as main document" policy.
///
/// For `mainDocumentURL`, the caller should pass the URL for an appropriate main document, if known. For example, when loading
/// a web page, the URL of the main html document for the top-level frame should be passed. To save cookies based on a set of
/// response headers, you can use `+[NSHTTPCookie cookiesWithResponseHeaderFields:forURL:]` on a header field dictionary and then
/// use this method to store the resulting cookies in accordance with policy settings.
- (void)setCookies:(NSArray<NSHTTPCookie *> *)cookies forURL:(nullable NSURL *)URL mainDocumentURL:(nullable NSURL *)mainDocumentURL;

/// The cookie accept policy preference of the receiver.
///
/// The default cookie accept policy is `NSHTTPCookieAcceptPolicyAlways`.
@property NSHTTPCookieAcceptPolicy cookieAcceptPolicy;

/// Returns all of the cookie storage's cookies, sorted according to a given set of sort descriptors.
///
/// - Parameter sortOrder: An array of `NSSortDescriptor` objects which represent the preferred sort order of the resulting array.
/// - Returns: The sorted array of cookies.
///
/// Proper sorting of cookies may require extensive string conversion, which can be avoided by allowing the system to
/// perform the sorting. This API is to be preferred over the more generic `cookies` property, if sorting is going to be performed.
- (NSArray<NSHTTPCookie *> *)sortedCookiesUsingDescriptors:(NSArray<NSSortDescriptor *> *) sortOrder API_AVAILABLE(macos(10.7), ios(5.0), watchos(2.0), tvos(9.0));

@end

@interface NSHTTPCookieStorage (NSURLSessionTaskAdditions)
/// Stores an array of cookies in the cookie storage, on behalf of the provided task, if the cookie accept policy permits.
- (void)storeCookies:(NSArray<NSHTTPCookie *> *)cookies forTask:(NSURLSessionTask *)task API_AVAILABLE(macos(10.10), ios(8.0), watchos(2.0), tvos(9.0));
/// Fetches cookies relevant to the specified task and passes them to the completion handler.
- (void)getCookiesForTask:(NSURLSessionTask *)task completionHandler:(void (NS_SWIFT_SENDABLE ^) (NSArray<NSHTTPCookie *> * _Nullable cookies))completionHandler API_AVAILABLE(macos(10.10), ios(8.0), watchos(2.0), tvos(9.0));
@end

/// Name of notification that should be posted to the distributed notification center whenever the accept cookies preference is changed.
FOUNDATION_EXPORT NSNotificationName const NSHTTPCookieManagerAcceptPolicyChangedNotification API_DEPRECATED("Notification is never posted", macos(10.2, 10.11), ios(2.0, 9.0), watchos(2.0, 2.0), tvos(9.0, 9.0), visionos(1.0, 1.0));

/// Notification sent when the set of cookies changes.
FOUNDATION_EXPORT NSNotificationName const NSHTTPCookieManagerCookiesChangedNotification API_AVAILABLE(macos(10.2), ios(2.0), watchos(2.0), tvos(9.0));

NS_HEADER_AUDIT_END(nullability, sendability)
