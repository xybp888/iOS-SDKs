/*	
    NSURLCache.h
    Copyright (c) 2003-2019, Apple Inc. All rights reserved.    
    
    Public header file.
*/

#import <Foundation/NSObject.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

/// Constants that specify the caching strategy used by an `NSCachedURLResponse` object stored in an `NSURLCache`.
///
/// These constants cover interactions that have to do with whether already-existing cache data is returned
/// to satisfy a URL load request.
///
/// - `NSURLCacheStorageAllowed`: Storage in an `NSURLCache` is allowed without restriction.
/// - `NSURLCacheStorageAllowedInMemoryOnly`: Storage in an `NSURLCache` is allowed; however storage should be done in memory only, no disk storage should be done.
/// - `NSURLCacheStorageNotAllowed`: Storage in an `NSURLCache` is not allowed in any fashion, either in memory or on disk.
typedef NS_ENUM(NSUInteger, NSURLCacheStoragePolicy)
{
    /// Storage in `NSURLCache` is allowed without restriction.
    NSURLCacheStorageAllowed,
    /// Storage in `NSURLCache` is allowed; however storage should be restricted to memory only.
    NSURLCacheStorageAllowedInMemoryOnly,
    /// Storage in `NSURLCache` is not allowed in any fashion, either in memory or on disk.
    NSURLCacheStorageNotAllowed,
};


@class NSCachedURLResponseInternal;
@class NSData;
@class NSDictionary;
@class NSURLRequest;
@class NSURLResponse;
@class NSDate;
@class NSURLSessionDataTask;

/// A cached response to a URL request.
///
/// A ``CachedURLResponse`` object provides the server's response metadata in the form of a ``URLResponse`` object, along with an [NSData](https://developer.apple.com/library/archive/documentation/Cocoa/Conceptual/PropertyLists/OldStylePlists/OldStylePLists.html#//apple_ref/doc/uid/20001012-47169) object containing the actual cached content data. Its storage policy determines whether the response should be cached on disk, in memory, or not at all.
///
/// Cached responses also contain a user info dictionary where you can store app-specific information about the cached item.
///
/// The ``URLCache`` class stores and retrieves instances of ``CachedURLResponse``.
NS_SWIFT_SENDABLE
API_AVAILABLE(macos(10.2), ios(2.0), watchos(2.0), tvos(9.0))
@interface NSCachedURLResponse : NSObject <NSSecureCoding, NSCopying>
{
    @private
    NSCachedURLResponseInternal *_internal;
}

/// Creates a cached URL response instance.
///
/// The cache storage policy is set to the default, `NSURLCacheStorageAllowed`.
///
/// - Parameters:
///   - response: The response to cache.
///   - data: The data to cache.
/// - Returns: A cached URL response object, containing the response and data.
- (instancetype)initWithResponse:(NSURLResponse *)response data:(NSData *)data;

/// Creates a cached URL response with a given server response, data, user-info dictionary, and storage policy.
///
/// - Parameters:
///   - response: The response to cache.
///   - data: The data to cache.
///   - userInfo: An optional dictionary of user information. May be `nil`.
///   - storagePolicy: An `NSURLCacheStoragePolicy` constant.
/// - Returns: A cached URL response object, containing the response and data.
- (instancetype)initWithResponse:(NSURLResponse *)response data:(NSData *)data userInfo:(nullable NSDictionary *)userInfo storagePolicy:(NSURLCacheStoragePolicy)storagePolicy;

/// The URL response object associated with the instance.
@property (readonly, copy) NSURLResponse *response;

/// The cached response's data.
@property (readonly, copy) NSData *data;

/// The cached response's user info dictionary.
@property (nullable, readonly, copy) NSDictionary *userInfo;

/// The cached response's storage policy.
@property (readonly) NSURLCacheStoragePolicy storagePolicy;

@end


@class NSURLRequest;
@class NSURLCacheInternal;

/// An object that maps URL requests to cached response objects.
///
/// The ``URLCache`` class implements the caching of responses to URL load requests, by mapping ``NSURLRequest`` objects to ``CachedURLResponse`` objects. It provides a composite in-memory and on-disk cache, and lets you manipulate the sizes of both the in-memory and on-disk portions. You can also control the path where cache data is persistently stored.
///
/// > Note:
/// > In iOS, the on-disk cache may be purged when the system runs low on disk space, but only when your app is not running.
///
/// ### Thread safety
///
/// In iOS 8 and later, and macOS 10.10 and later, ``URLCache`` is thread safe.
///
/// Although ``URLCache`` instance methods can safely be called from multiple execution contexts at the same time, be aware that methods like  ``cachedResponse(for:)`` and ``storeCachedResponse(_:for:)-7p7bl`` have an unavoidable race condition when attempting to read or write responses for the same request.
///
/// Subclasses of ``URLCache`` must implement overridden methods in such a thread-safe manner.
///
/// ### Subclassing notes
///
/// The ``URLCache`` class is meant to be used as-is, but you can subclass it when you have specific needs. For example, you might want to screen which responses are cached, or reimplement the storage mechanism for security or other reasons.
///
/// When overriding methods of this class, be aware that methods that take a `task` parameter are preferred by the system to those that do not. Therefore, you should override the task-based methods when subclassing, as follows:
///
/// - Storing responses in the cache — Override the task-based ``storeCachedResponse(_:for:)-8uq91``, instead of or in addition to the request-based ``storeCachedResponse(_:for:)-7p7bl``.
/// - Getting responses from the cache — Override ``getCachedResponse(for:completionHandler:)``, instead of or in addition to ``cachedResponse(for:)``.
/// - Removing cached responses — Override the task-based ``removeCachedResponse(for:)-1zwp6``, instead of or in addition to the request-based ``removeCachedResponse(for:)-1dh89``.
NS_SWIFT_SENDABLE
API_AVAILABLE(macos(10.2), ios(2.0), watchos(2.0), tvos(9.0))
@interface NSURLCache : NSObject
{
    @private
    NSURLCacheInternal *_internal;
}

/// The shared URL cache instance.
///
/// Unless set explicitly, this method returns an `NSURLCache` instance created with the following default values:
/// - Memory capacity: 4 megabytes (4 * 1024 * 1024 bytes)
/// - Disk capacity: 20 megabytes (20 * 1024 * 1024 bytes)
/// - Disk path: `(user home directory)/Library/Caches/(application bundle id)`
///
/// If your app doesn't have special caching requirements or constraints, the default shared cache instance should
/// be acceptable. Callers should take care to ensure that the setter is called at a time when no other caller has
/// a reference to the previously-set shared URL cache.
@property (class, strong) NSURLCache *sharedURLCache;

/// Initializes an `NSURLCache` with the given capacity and path.
///
/// The returned `NSURLCache` is backed by disk. A disk cache measured in the tens of megabytes should be acceptable in most cases.
///
/// - Parameters:
///   - memoryCapacity: The capacity, measured in bytes, for the cache in memory.
///   - diskCapacity: The capacity, measured in bytes, for the cache on disk.
///   - path: The path on disk where the cache data is stored.
/// - Returns: An initialized `NSURLCache`, with the given capacity, backed by disk.
- (instancetype)initWithMemoryCapacity:(NSUInteger)memoryCapacity diskCapacity:(NSUInteger)diskCapacity diskPath:(nullable NSString *)path API_DEPRECATED_WITH_REPLACEMENT("initWithMemoryCapacity:diskCapacity:directoryURL:", macos(10.2, API_TO_BE_DEPRECATED), ios(2.0, API_TO_BE_DEPRECATED), watchos(2.0, API_TO_BE_DEPRECATED), tvos(9.0, API_TO_BE_DEPRECATED));

/// Initializes an `NSURLCache` with the given capacity and directory.
///
/// - Parameters:
///   - memoryCapacity: The capacity, measured in bytes, for the cache in memory. Or `0` to disable memory cache.
///   - diskCapacity: The capacity, measured in bytes, for the cache on disk. Or `0` to disable disk cache.
///   - directoryURL: The path to a directory on disk where the cache data is stored. Or `nil` for default directory.
/// - Returns: An initialized `NSURLCache`, with the given capacity, optionally backed by disk.
- (instancetype)initWithMemoryCapacity:(NSUInteger)memoryCapacity diskCapacity:(NSUInteger)diskCapacity directoryURL:(nullable NSURL *)directoryURL API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0));

/// Returns the cached URL response in the cache for the specified URL request.
///
/// Returns `nil` if there is no `NSCachedURLResponse` stored using the given request.
///
/// - Parameter request: The `NSURLRequest` to use as a key for the lookup.
/// - Returns: The `NSCachedURLResponse` stored in the cache with the given request, or `nil` if there is no cached response.
- (nullable NSCachedURLResponse *)cachedResponseForRequest:(NSURLRequest *)request;

/// Stores a cached URL response for a specified request.
///
/// - Parameters:
///   - cachedResponse: The cached response to store.
///   - request: The `NSURLRequest` to use as a key for the storage.
- (void)storeCachedResponse:(NSCachedURLResponse *)cachedResponse forRequest:(NSURLRequest *)request;

/// Removes the cached URL response for a specified request.
///
/// No action is taken if there is no `NSCachedURLResponse` stored with the given request.
///
/// - Parameter request: The `NSURLRequest` to use as a key for the lookup.
- (void)removeCachedResponseForRequest:(NSURLRequest *)request;

/// Clears the cache, removing all `NSCachedURLResponse` objects that it stores.
- (void)removeAllCachedResponses;

/// Clears the cache of any cached responses since the provided date.
- (void)removeCachedResponsesSinceDate:(NSDate *)date API_AVAILABLE(macos(10.10), ios(8.0), watchos(2.0), tvos(9.0));

/// The in-memory capacity of the receiver, measured in bytes.
///
/// At the time this value is set, the in-memory cache will truncate its contents to the size given, if necessary.
@property NSUInteger memoryCapacity;

/// The on-disk capacity of the receiver, measured in bytes.
///
/// On mutation, the on-disk cache will truncate its contents to the size given, if necessary.
@property NSUInteger diskCapacity;

/// The current amount of space consumed by the in-memory cache of the receiver, measured in bytes.
@property (readonly) NSUInteger currentMemoryUsage;

/// The current amount of space consumed by the on-disk cache of the receiver, measured in bytes.
@property (readonly) NSUInteger currentDiskUsage;

@end

@interface NSURLCache (NSURLSessionTaskAdditions)
/// Stores a cached URL response for a specified data task.
- (void)storeCachedResponse:(NSCachedURLResponse *)cachedResponse forDataTask:(NSURLSessionDataTask *)dataTask API_AVAILABLE(macos(10.10), ios(8.0), watchos(2.0), tvos(9.0));
/// Gets the cached URL response for a specified data task, passing it to a completion handler.
- (void)getCachedResponseForDataTask:(NSURLSessionDataTask *)dataTask completionHandler:(void (NS_SWIFT_SENDABLE ^) (NSCachedURLResponse * _Nullable cachedResponse))completionHandler API_AVAILABLE(macos(10.10), ios(8.0), watchos(2.0), tvos(9.0));
/// Removes the cached URL response for a specified data task.
- (void)removeCachedResponseForDataTask:(NSURLSessionDataTask *)dataTask API_AVAILABLE(macos(10.10), ios(8.0), watchos(2.0), tvos(9.0));
@end

NS_HEADER_AUDIT_END(nullability, sendability)
