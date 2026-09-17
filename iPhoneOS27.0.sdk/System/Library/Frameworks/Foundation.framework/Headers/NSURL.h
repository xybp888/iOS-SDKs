/*	NSURL.h
	Copyright (c) 1997-2023, Apple Inc. All rights reserved.
*/

#import <Foundation/NSObject.h>
#import <Foundation/NSString.h>
#import <Foundation/NSCharacterSet.h>
#if !0
#import <Foundation/NSItemProvider.h>
#endif
#if TARGET_OS_OSX || TARGET_OS_MACCATALYST
#import <Foundation/NSURLHandle.h>
#endif

@class NSArray<ObjectType>, NSNumber, NSData, NSDictionary<KeyType, ObjectType>;

/// Keys that apply to file system URLs.
///
/// To request information using one of these keys, pass it to the `forKey:` parameter of the ``NSURL/getResourceValue(_:forKey:)`` instance method.
typedef NSString * NSURLResourceKey NS_TYPED_EXTENSIBLE_ENUM;

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

/// An object that represents the location of a resource, such as an item on a remote server or the path to a local file.
///
/// In Swift, this object bridges to ``URL``; use ``NSURL`` when you need reference semantics or other Foundation-specific behavior.
///
/// You can use URL objects to construct URLs and access their parts. For URLs that represent local files, you can also manipulate properties of those files directly, such as changing the file's last modification date. Finally, you can pass URL objects to other APIs to retrieve the contents of those URLs. For example, you can use the ``URLSession``, ``NSURLConnection``, and ``NSURLDownload`` classes to access the contents of remote resources, as described in <doc:url-loading-system>.
///
/// URL objects are the preferred way to refer to local files. Most objects that read data from or write data to a file have methods that accept an ``NSURL`` object instead of a pathname as the file reference. For example, you can get the contents of a local file URL as an `NSString` object using the ``NSString/init(contentsOfURL:encoding:)-715fw`` initializer, or as an `NSData` object using the ``NSData/init(contentsOfURL:options:)-5abi3`` initializer.
///
/// You can also use URLs for interapplication communication. In macOS, the <doc://com.apple.documentation/documentation/appkit/nsworkspace> class provides the <doc://com.apple.documentation/documentation/appkit/nsworkspace/open(_:)> method to open a location specified by a URL. Similarly, in iOS, the <doc://com.apple.documentation/documentation/uikit/uiapplication> class provides the <doc://com.apple.documentation/documentation/uikit/uiapplication/open(_:options:completionhandler:)> method.
///
/// The ``NSURL`` class is "toll-free bridged" with its Core Foundation counterpart, <doc://com.apple.documentation/documentation/corefoundation/cfurl>. See [Toll-Free Bridging](https://developer.apple.com/library/archive/documentation/General/Conceptual/CocoaEncyclopedia/Toll-FreeBridgin/Toll-FreeBridgin.html#//apple_ref/doc/uid/TP40010810-CH2) for more information on toll-free bridging.
///
/// > Important:
/// > The Swift overlay to the Foundation framework provides the ``URL`` structure, which bridges to the ``NSURL`` class. For more information about value types, see [Classes and Structures](https://developer.apple.com/library/archive/documentation/Swift/Conceptual/Swift_Programming_Language/ClassesAndStructures.html#//apple_ref/doc/uid/TP40014097-CH13) in [The Swift Programming Language (Swift 4.1)](https://developer.apple.com/library/archive/documentation/Swift/Conceptual/Swift_Programming_Language/index.html#//apple_ref/doc/uid/TP40014097) and [Working with Cocoa Frameworks](https://developer.apple.com/library/archive/documentation/Swift/Conceptual/BuildingCocoaApps/WorkingWithCocoaDataTypes.html#//apple_ref/doc/uid/TP40014216-CH6) in [Using Swift with Cocoa and Objective-C (Swift 4.1)](https://developer.apple.com/library/archive/documentation/Swift/Conceptual/BuildingCocoaApps/index.html#//apple_ref/doc/uid/TP40014216).
///
/// ### Structure of a URL
///
/// An ``NSURL`` object is composed of two parts—a potentially `nil` base URL and a string that is resolved relative to the base URL. An ``NSURL`` object is considered absolute if its string part is fully resolved without a base; all other URLs are considered relative.
///
/// For example, when constructing an `NSURL` object, you might specify `file:///path/to/user/` as the base URL and `folder/file.html` as the string part, as follows:
///
/// ```objc
/// NSURL *baseURL = [NSURL fileURLWithPath:@"file:///path/to/user/"];
/// NSURL *URL = [NSURL URLWithString:@"folder/file.html" relativeToURL:baseURL];
/// NSLog(@"absoluteURL = %@", [URL absoluteURL]);
/// ```
///
/// When fully resolved, the absolute URL is `file:///path/to/user/folder/file.html`.
///
/// A URL can be also be divided into pieces based on its structure. For example, the URL `https://johnny:p4ssw0rd@www.example.com:443/script.ext;param=value?query=value#ref` contains the following URL components:
///
/// | Component | Value |
/// |---|---|
/// | ``scheme`` | `https` |
/// | ``user`` | `johnny` |
/// | ``password`` | `p4ssw0rd` |
/// | ``host`` | `www.example.com` |
/// | ``port`` | `443` |
/// | ``path`` | `/script.ext` |
/// | ``pathExtension`` | `ext` |
/// | ``pathComponents`` | `["/", "script.ext"]` |
/// | ``parameterString`` | `param=value` |
/// | ``query`` | `query=value` |
/// | ``fragment`` | `ref` |
///
/// The ``NSURL`` class provides properties that let you examine each of these components.
///
/// > Important:
/// > For apps linked on or after iOS 17 and aligned OS versions, ``NSURL`` parsing has updated from the obsolete RFC 1738/1808 parsing to the same [RFC 3986](https://www.ietf.org/rfc/rfc3986.txt) parsing as ``NSURLComponents``. This unifies the parsing behaviors of the `NSURL` and `NSURLComponents` APIs. Now, `NSURL` automatically percent- and IDNA-encodes invalid characters to help create a valid URL.
/// >
/// > To check if a `URLString` is strictly valid according to the RFC, use the new `[NSURL URLWithString:URLString encodingInvalidCharacters:NO]` method. This method leaves all characters as they are and returns `nil` if `URLString` is explicitly invalid.
///
/// For apps linked before iOS 17, the ``NSURL`` class parses URLs according to [RFC 1808](https://tools.ietf.org/html/rfc1808), [RFC 1738](https://tools.ietf.org/html/rfc1738), and [RFC 2732](https://tools.ietf.org/html/rfc2732).
///
/// ### Bookmarks and Security Scope
///
/// Starting with OS X v10.6 and iOS 4.0, the ``NSURL`` class provides a facility for creating and using bookmark objects. A **bookmark** provides a persistent reference to a file-system resource. When you resolve a bookmark, you obtain a URL to the resource's current location. A bookmark's association with a file-system resource (typically a file or folder) usually continues to work if the user moves or renames the resource, or if the user relaunches your app or restarts the system.
///
/// For a general introduction to using bookmarks, read [Locating Files Using Bookmarks](https://developer.apple.com/library/archive/documentation/FileManagement/Conceptual/FileSystemProgrammingGuide/AccessingFilesandDirectories/AccessingFilesandDirectories.html#//apple_ref/doc/uid/TP40010672-CH3-SW10) in [File System Programming Guide](https://developer.apple.com/library/archive/documentation/FileManagement/Conceptual/FileSystemProgrammingGuide/Introduction/Introduction.html#//apple_ref/doc/uid/TP40010672).
///
/// In a macOS app that adopts App Sandbox, you can use **security-scoped bookmarks** to gain access to file-system resources outside your app's sandbox. These bookmarks preserve the user's intent to give your app access to a resource across app launches. For details on how this works, including information on the entitlements you need in your Xcode project, read [Security-Scoped Bookmarks and Persistent Resource Access](https://developer.apple.com/library/archive/documentation/Security/Conceptual/AppSandboxDesignGuide/AppSandboxInDepth/AppSandboxInDepth.html#//apple_ref/doc/uid/TP40011183-CH3-SW16) in [App Sandbox Design Guide](https://developer.apple.com/library/archive/documentation/Security/Conceptual/AppSandboxDesignGuide/AboutAppSandbox/AboutAppSandbox.html#//apple_ref/doc/uid/TP40011183). The methods for using security-scoped bookmarks are described in this document in Working with Bookmark Data.
///
/// When you resolve a security-scoped bookmark, you get a security-scoped URL.
///
/// ### Security-Scoped URLs
///
/// Security-scoped URLs provide access to resources outside an app's sandbox. In macOS, you get access to security-scoped URLs when you resolve a security-scoped bookmark. In iOS, apps that _open_ or _move_ documents using a <doc://com.apple.documentation/documentation/uikit/uidocumentpickerviewcontroller> also receive security-scoped URLs.
///
/// To gain access to a security-scoped URL, you must call the ``startAccessingSecurityScopedResource()`` method (or its Core Foundation equivalent, the <doc://com.apple.documentation/documentation/corefoundation/cfurlstartaccessingsecurityscopedresource(_:)> function). For iOS apps, if you use a <doc://com.apple.documentation/documentation/uikit/uidocument> to access the URL, it automatically manages the security-scoped URL for you.
///
/// If `startAccessingSecurityScopedResource` (or `CFUrLStartAccessingSecurityScopedResource`) returns <doc://com.apple.documentation/documentation/swift/true>, you must relinquish your access by calling the ``stopAccessingSecurityScopedResource()`` method (or its Core Foundation equivalent, the <doc://com.apple.documentation/documentation/corefoundation/cfurlstopaccessingsecurityscopedresource(_:)> function). You should relinquish your access as soon as you have finished using the file. After you call these methods, you immediately lose access to the resource in question.
///
/// > Warning:
/// > If you fail to relinquish your access when you no longer need a file-system resource, your app leaks kernel resources. If sufficient kernel resources are leaked, your app loses its ability to add file-system locations to its sandbox, using Powerbox, security-scoped bookmarks, or similar APIs, until relaunched.
///
/// #### Security-Scoped URLs and String Paths
///
/// In a macOS app, when you copy a security-scoped URL, the copy has the security scope of the original. You gain access to the file-system resource (that the URL points to) just as you would with the original URL: by calling the ``startAccessingSecurityScopedResource()`` method (or its Core Foundation equivalent).
///
/// If you need a security-scoped URL's path as a string value (as provided by the ``path`` method), such as to provide to an API that requires a string value, obtain the path from the URL as needed. Note, however, that a string-based path obtained from a security-scoped URL _does not_ have security scope and you cannot use that string to obtain access to a security-scoped resource.
NS_SWIFT_SENDABLE
@interface NSURL: NSObject <NSSecureCoding, NSCopying>
{
    NSString *_urlString;
    NSURL *_baseURL;
    void *_clients;
    void *_reserved;
}

/// Initializes an NSURL with the given scheme, host, and path.
///
/// This method percent-encodes both the host and path, so this cannot be used to set a username/password or port
/// in the hostname part or with a IPv6 `[...]` type address. Use `NSURLComponents` for IPv6 addresses.
- (nullable instancetype)initWithScheme:(NSString *)scheme host:(nullable NSString *)host path:(NSString *)path API_DEPRECATED("Use NSURLComponents instead, which lets you create a valid URL with any valid combination of URL components and subcomponents (not just scheme, host and path), and lets you set components and subcomponents with either percent-encoded or un-percent-encoded strings.", macos(10.0,10.11), ios(2.0,9.0), watchos(2.0,2.0), tvos(9.0,9.0));

/// Initializes a newly created file NSURL referencing the local file or directory at path, relative to a base URL.
- (instancetype)initFileURLWithPath:(NSString *)path isDirectory:(BOOL)isDir relativeToURL:(nullable NSURL *)baseURL API_AVAILABLE(macos(10.11), ios(9.0), watchos(2.0), tvos(9.0)) NS_DESIGNATED_INITIALIZER;
/// Initializes a newly created file NSURL referencing the local file or directory at path, relative to a base URL.
///
/// Better to use `initFileURLWithPath:isDirectory:relativeToURL:` if you know if the path is a directory vs non-directory, as it saves an I/O.
- (instancetype)initFileURLWithPath:(NSString *)path relativeToURL:(nullable NSURL *)baseURL API_AVAILABLE(macos(10.11), ios(9.0), watchos(2.0), tvos(9.0)) NS_DESIGNATED_INITIALIZER;

/// Initializes a newly created file NSURL referencing the local file or directory at path.
- (instancetype)initFileURLWithPath:(NSString *)path isDirectory:(BOOL)isDir API_AVAILABLE(macos(10.5), ios(2.0), watchos(2.0), tvos(9.0)) NS_DESIGNATED_INITIALIZER;
/// Initializes a newly created file NSURL referencing the local file or directory at path.
///
/// Better to use `initFileURLWithPath:isDirectory:` if you know if the path is a directory vs non-directory, as it saves an I/O.
- (instancetype)initFileURLWithPath:(NSString *)path NS_DESIGNATED_INITIALIZER;

/// Initializes and returns a newly created file NSURL referencing the local file or directory at path, relative to a base URL.
+ (NSURL *)fileURLWithPath:(NSString *)path isDirectory:(BOOL) isDir relativeToURL:(nullable NSURL *)baseURL API_AVAILABLE(macos(10.11), ios(9.0), watchos(2.0), tvos(9.0));
/// Initializes and returns a newly created file NSURL referencing the local file or directory at path, relative to a base URL.
///
/// Better to use `fileURLWithPath:isDirectory:relativeToURL:` if you know if the path is a directory vs non-directory, as it saves an I/O.
+ (NSURL *)fileURLWithPath:(NSString *)path relativeToURL:(nullable NSURL *)baseURL API_AVAILABLE(macos(10.11), ios(9.0), watchos(2.0), tvos(9.0));

/// Initializes and returns a newly created file NSURL referencing the local file or directory at path.
+ (NSURL *)fileURLWithPath:(NSString *)path isDirectory:(BOOL)isDir API_AVAILABLE(macos(10.5), ios(2.0), watchos(2.0), tvos(9.0));
/// Initializes and returns a newly created file NSURL referencing the local file or directory at path.
///
/// Better to use `fileURLWithPath:isDirectory:` if you know if the path is a directory vs non-directory, as it saves an I/O.
+ (NSURL *)fileURLWithPath:(NSString *)path;

/// Initializes a newly created URL referencing the local file or directory at the file system representation of the path.
///
/// File system representation is a null-terminated C string with canonical UTF-8 encoding.
- (instancetype)initFileURLWithFileSystemRepresentation:(const char *)path isDirectory:(BOOL)isDir relativeToURL:(nullable NSURL *)baseURL API_AVAILABLE(macos(10.9), ios(7.0), watchos(2.0), tvos(9.0)) NS_DESIGNATED_INITIALIZER;

/// Initializes and returns a newly created URL referencing the local file or directory at the file system representation of the path.
///
/// File system representation is a null-terminated C string with canonical UTF-8 encoding.
+ (NSURL *)fileURLWithFileSystemRepresentation:(const char *)path isDirectory:(BOOL) isDir relativeToURL:(nullable NSURL *)baseURL API_AVAILABLE(macos(10.9), ios(7.0), watchos(2.0), tvos(9.0));

/// These methods expect their string arguments to contain any percent escape codes that are necessary. It is an error for URLString to be nil.
- (nullable instancetype)initWithString:(NSString *)URLString;
/// Initializes an NSURL with a URL string, relative to a base URL.
- (nullable instancetype)initWithString:(NSString *)URLString relativeToURL:(nullable NSURL *)baseURL NS_DESIGNATED_INITIALIZER;
/// Returns a newly created NSURL initialized with the given URL string.
+ (nullable instancetype)URLWithString:(NSString *)URLString;
/// Returns a newly created NSURL initialized with the given URL string, relative to a base URL.
+ (nullable instancetype)URLWithString:(NSString *)URLString relativeToURL:(nullable NSURL *)baseURL;

/// Initializes an `NSURL` with a URL string and the option to add (or skip) IDNA- and percent-encoding of invalid characters.
/// If `encodingInvalidCharacters` is false, and the URL string is invalid according to RFC 3986, `nil` is returned.
/// If `encodingInvalidCharacters` is true, `NSURL` will try to encode the string to create a valid URL.
/// If the URL string is still invalid after encoding, `nil` is returned.
///
/// - Parameter URLString: The URL string.
/// - Parameter encodingInvalidCharacters: True if `NSURL` should try to encode an invalid URL string, false otherwise.
/// - Returns: An `NSURL` instance for a valid URL, or `nil` if the URL is invalid.
- (nullable instancetype)initWithString:(NSString *)URLString encodingInvalidCharacters:(BOOL)encodingInvalidCharacters API_AVAILABLE(macos(14.0), ios(17.0), watchos(10.0), tvos(17.0));

/// Initializes and returns a newly created `NSURL` with a URL string and the option to add (or skip) IDNA- and percent-encoding of invalid characters.
/// If `encodingInvalidCharacters` is false, and the URL string is invalid according to RFC 3986, `nil` is returned.
/// If `encodingInvalidCharacters` is true, `NSURL` will try to encode the string to create a valid URL.
/// If the URL string is still invalid after encoding, `nil` is returned.
///
/// - Parameter URLString: The URL string.
/// - Parameter encodingInvalidCharacters: True if `NSURL` should try to encode an invalid URL string, false otherwise.
/// - Returns: An `NSURL` instance for a valid URL, or `nil` if the URL is invalid.
+ (nullable instancetype)URLWithString:(NSString *)URLString encodingInvalidCharacters:(BOOL)encodingInvalidCharacters API_AVAILABLE(macos(14.0), ios(17.0), watchos(10.0), tvos(17.0));


/// Initializes a newly created NSURL using the contents of the given data, relative to a base URL.
///
/// If the data representation is not a legal URL string as ASCII bytes, the URL object may not behave as expected.
- (instancetype)initWithDataRepresentation:(NSData *)data relativeToURL:(nullable NSURL *)baseURL API_AVAILABLE(macos(10.11), ios(9.0), watchos(2.0), tvos(9.0)) NS_DESIGNATED_INITIALIZER;
/// Initializes and returns a newly created NSURL using the contents of the given data, relative to a base URL.
///
/// If the data representation is not a legal URL string as ASCII bytes, the URL object may not behave as expected.
+ (NSURL *)URLWithDataRepresentation:(NSData *)data relativeToURL:(nullable NSURL *)baseURL API_AVAILABLE(macos(10.11), ios(9.0), watchos(2.0), tvos(9.0));

/// Initializes a newly created absolute NSURL using the contents of the given data, relative to a base URL.
///
/// If the data representation is not a legal URL string as ASCII bytes, the URL object may not behave as expected.
- (instancetype)initAbsoluteURLWithDataRepresentation:(NSData *)data relativeToURL:(nullable NSURL *)baseURL API_AVAILABLE(macos(10.11), ios(9.0), watchos(2.0), tvos(9.0)) NS_DESIGNATED_INITIALIZER;
/// Initializes and returns a newly created absolute NSURL using the contents of the given data, relative to a base URL.
///
/// If the data representation is not a legal URL string as ASCII bytes, the URL object may not behave as expected.
+ (NSURL *)absoluteURLWithDataRepresentation:(NSData *)data relativeToURL:(nullable NSURL *)baseURL API_AVAILABLE(macos(10.11), ios(9.0), watchos(2.0), tvos(9.0));

/// The data representation of the URL's relativeString.
///
/// If the URL was initialized with `initWithData:relativeToURL:`, the data representation returned are the same bytes
/// as those used at initialization; otherwise, the data representation returned are the bytes of the relativeString
/// encoded with `NSUTF8StringEncoding`.
@property (readonly, copy) NSData *dataRepresentation API_AVAILABLE(macos(10.11), ios(9.0), watchos(2.0), tvos(9.0));

/// The URL string for the receiver as an absolute URL.
@property (nullable, readonly, copy) NSString *absoluteString;
/// The relative portion of the URL. If `baseURL` is `nil`, or if the receiver is itself absolute, this is the same as `absoluteString`.
@property (readonly, copy) NSString *relativeString;
/// The base URL. May be `nil`.
@property (nullable, readonly, copy) NSURL *baseURL;
/// The absolute URL. If the receiver is itself absolute, this returns self.
@property (nullable, readonly, copy) NSURL *absoluteURL;

/// The scheme component of the URL.
///
/// The full URL is the concatenation of `[myURL scheme]`, `':'`, `[myURL resourceSpecifier]`.
@property (nullable, readonly, copy) NSString *scheme;
/// The resource specifier component of the URL.
@property (nullable, readonly, copy) NSString *resourceSpecifier;

/// The host component of the URL, or `nil` if the URL does not conform to RFC 1808.
@property (nullable, readonly, copy) NSString *host;
/// The port component of the URL, or `nil` if the URL does not conform to RFC 1808.
@property (nullable, readonly, copy) NSNumber *port;
/// The user component of the URL, or `nil` if the URL does not conform to RFC 1808.
@property (nullable, readonly, copy) NSString *user;
/// The password component of the URL, or `nil` if the URL does not conform to RFC 1808.
@property (nullable, readonly, copy) NSString *password;
/// The path component of the URL, or `nil` if the URL does not conform to RFC 1808.
@property (nullable, readonly, copy) NSString *path;
/// The fragment component of the URL, or `nil` if the URL does not conform to RFC 1808.
@property (nullable, readonly, copy) NSString *fragment;
/// The parameter string of the URL.
@property (nullable, readonly, copy) NSString *parameterString API_DEPRECATED("The parameterString method is deprecated. Post deprecation for applications linked with or after the macOS 10.15, and for all iOS, watchOS, and tvOS applications, parameterString will always return nil, and the path method will return the complete path including the semicolon separator and params component if the URL string contains them.", macosx(10.2,10.15), ios(2.0,13.0), watchos(2.0,6.0), tvos(9.0,13.0));
/// The query component of the URL, or `nil` if the URL does not conform to RFC 1808.
@property (nullable, readonly, copy) NSString *query;
/// The relative path of the URL. Same as `path` if `baseURL` is `nil`.
@property (nullable, readonly, copy) NSString *relativePath;

/// A Boolean value that indicates whether the URL's path represents a directory.
///
/// Determined from the URL string (whether the path component ends with a `/` character). Does not check the resource.
@property (readonly) BOOL hasDirectoryPath API_AVAILABLE(macos(10.11), ios(9.0), watchos(2.0), tvos(9.0));

/// Fills a buffer with the URL's path in file system representation.
///
/// File system representation is a null-terminated C string with canonical UTF-8 encoding.
- (BOOL)getFileSystemRepresentation:(char *)buffer maxLength:(NSUInteger)maxBufferLength API_AVAILABLE(macos(10.9), ios(7.0), watchos(2.0), tvos(9.0));

/// The URL's path in file system representation.
///
/// File system representation is a null-terminated C string with canonical UTF-8 encoding. The returned C string
/// will be automatically freed just as a returned object would be released; use `getFileSystemRepresentation:maxLength:`
/// if you need to store the representation outside of the autorelease context.
@property (readonly) const char *fileSystemRepresentation NS_RETURNS_INNER_POINTER API_AVAILABLE(macos(10.9), ios(7.0), watchos(2.0), tvos(9.0));

/// A Boolean value that indicates whether the URL scheme is `file:`.
///
/// If `isFileURL` is `YES`, then `path` is suitable for input into `NSFileManager` or `NSPathUtilities`.
@property (readonly, getter=isFileURL) BOOL fileURL;

/// A string constant for the "file" URL scheme.
///
/// If you are comparing to a URL's scheme to check for file URLs, use the `fileURL` property instead - it is much faster.
FOUNDATION_EXPORT NSString * const NSURLFileScheme;


/// The standardized form of the URL.
@property (nullable, readonly, copy) NSURL *standardizedURL;

#if !0

/* Working with file reference URLs
 */

/// Returns whether the URL is a file reference URL.
- (BOOL)isFileReferenceURL API_AVAILABLE(macos(10.6), ios(4.0), watchos(2.0), tvos(9.0));

/// Returns a file reference URL that refers to the same resource as a specified file URL.
///
/// File reference URLs use a URL path syntax that identifies a file system object by reference, not by path.
/// This form of file URL remains valid when the file system path of the URL’s underlying resource changes.
/// A file reference URL’s path should never be persistently stored because it is not valid across system restarts
/// and across remounts of volumes. Use a bookmark instead for persistent references.
- (nullable NSURL *)fileReferenceURL API_AVAILABLE(macos(10.6), ios(4.0), watchos(2.0), tvos(9.0));

/// A file path URL that refers to the same resource as this URL.
///
/// File path URLs use a file system style path. The resource must exist and be reachable to be converted.
@property (nullable, readonly, copy) NSURL *filePathURL API_AVAILABLE(macos(10.6), ios(4.0), watchos(2.0), tvos(9.0));


/* Resource access

 The behavior of resource value caching is slightly different between the NSURL and CFURL API.
 
 When the NSURL methods which get, set, or use cached resource values are used from the main thread, resource values cached by the URL (except those added as temporary properties) are removed the next time the main thread's run loop runs. -removeCachedResourceValueForKey: and -removeAllCachedResourceValues also may be used to remove cached resource values.
 
 The CFURL functions do not automatically remove any resource values cached by the URL. The client has complete control over the cache lifetime. If you are using CFURL API, you must use CFURLClearResourcePropertyCacheForKey or CFURLClearResourcePropertyCache to remove cached resource values.
 */

/// Returns the value of the resource property for the specified key.
///
/// This method first checks if the URL object already caches the resource value. If so, it returns the cached value.
/// If not, it synchronously obtains the resource value from the backing store and adds it to the cache.
/// If this method returns `YES` and value is populated with `nil`, the resource property is not available for the resource.
/// This method is currently applicable only to URLs for file system resources.
- (BOOL)getResourceValue:(out id _Nullable * _Nonnull)value forKey:(NSURLResourceKey)key error:(out NSError ** _Nullable)error API_AVAILABLE(macos(10.6), ios(4.0), watchos(2.0), tvos(9.0));

/// Returns the resource values identified by specified array of resource keys.
///
/// This method first checks if the URL object already caches the resource values. If so, it returns the cached values.
/// If not, it synchronously obtains the values from the backing store and adds them to the cache.
/// If a resource value for one or more requested keys is not present in the result, that property is not available for the resource.
/// This method is currently applicable only to URLs for file system resources.
- (nullable NSDictionary<NSURLResourceKey, id> *)resourceValuesForKeys:(NSArray<NSURLResourceKey> *)keys error:(NSError **)error API_AVAILABLE(macos(10.6), ios(4.0), watchos(2.0), tvos(9.0));

/// Sets the resource value identified by a given resource key.
///
/// This method writes the new resource value out to the backing store. Attempts to set a read-only resource property
/// or to set a resource property not supported by the resource are ignored and are not considered errors.
/// This method is currently applicable only to URLs for file system resources.
- (BOOL)setResourceValue:(nullable id)value forKey:(NSURLResourceKey)key error:(NSError **)error API_AVAILABLE(macos(10.6), ios(4.0), watchos(2.0), tvos(9.0));

/// Sets any number of resource values of a URL's resource.
///
/// This method writes the new resource values out to the backing store. Attempts to set read-only resource properties
/// or to set resource properties not supported by the resource are ignored and are not considered errors.
/// If an error occurs after some resource properties have been successfully changed, the userInfo dictionary in
/// the returned error contains an array of resource keys that were not set with the key `kCFURLKeysOfUnsetValuesKey`.
/// This method is currently applicable only to URLs for file system resources.
- (BOOL)setResourceValues:(NSDictionary<NSURLResourceKey, id> *)keyedValues error:(NSError **)error API_AVAILABLE(macos(10.6), ios(4.0), watchos(2.0), tvos(9.0));

/// Key for the resource properties that have not been set after `setResourceValues:error:` returns an error, returned as an array of strings.
FOUNDATION_EXPORT NSURLResourceKey const NSURLKeysOfUnsetValuesKey API_AVAILABLE(macos(10.7), ios(5.0), watchos(2.0), tvos(9.0));

/// Removes the cached resource value identified by a given key from the URL object.
///
/// Removing a cached resource value may remove other cached resource values because some resource values are
/// cached as a set, and because some resource values depend on other resource values.
/// This method is currently applicable only to URLs for file system resources.
- (void)removeCachedResourceValueForKey:(NSURLResourceKey)key API_AVAILABLE(macos(10.9), ios(7.0), watchos(2.0), tvos(9.0));

/// Removes all cached resource values and all temporary resource values from the URL object.
///
/// This method is currently applicable only to URLs for file system resources.
- (void)removeAllCachedResourceValues API_AVAILABLE(macos(10.9), ios(7.0), watchos(2.0), tvos(9.0));

/// Sets a temporary resource value on the URL object.
///
/// Temporary resource values are for client use. They exist only in memory and are never written to the
/// resource's backing store. Once set, a temporary resource value can be read with `getResourceValue:forKey:error:`
/// or `resourceValuesForKeys:error:`. To remove a temporary resource value, use `removeCachedResourceValueForKey:`.
/// This method is currently applicable only to URLs for file system resources.
- (void)setTemporaryResourceValue:(nullable NS_SWIFT_SENDABLE id)value forKey:(NSURLResourceKey)key API_AVAILABLE(macos(10.9), ios(7.0), watchos(2.0), tvos(9.0));

/// The File System Resource Keys
///
/// URLs to file system resources support the properties defined below. Note that not all property values will exist
/// for all file system URLs. For example, if a file is located on a volume that does not support creation dates,
/// it is valid to request the creation date property, but the returned value will be `nil`, and no error will be generated.

// Resource keys applicable to all file system objects

/// The resource name provided by the file system (Read-write, value type `NSString`).
FOUNDATION_EXPORT NSURLResourceKey const NSURLNameKey                        API_AVAILABLE(macos(10.6), ios(4.0), watchos(2.0), tvos(9.0));
/// Localized or extension-hidden name as displayed to users (Read-only, value type `NSString`).
FOUNDATION_EXPORT NSURLResourceKey const NSURLLocalizedNameKey               API_AVAILABLE(macos(10.6), ios(4.0), watchos(2.0), tvos(9.0));
/// `true` for regular files (Read-only, value type boolean `NSNumber`).
FOUNDATION_EXPORT NSURLResourceKey const NSURLIsRegularFileKey               API_AVAILABLE(macos(10.6), ios(4.0), watchos(2.0), tvos(9.0));
/// `true` for directories (Read-only, value type boolean `NSNumber`).
FOUNDATION_EXPORT NSURLResourceKey const NSURLIsDirectoryKey                 API_AVAILABLE(macos(10.6), ios(4.0), watchos(2.0), tvos(9.0));
/// `true` for symlinks (Read-only, value type boolean `NSNumber`).
FOUNDATION_EXPORT NSURLResourceKey const NSURLIsSymbolicLinkKey              API_AVAILABLE(macos(10.6), ios(4.0), watchos(2.0), tvos(9.0));
/// `true` for the root directory of a volume (Read-only, value type boolean `NSNumber`).
FOUNDATION_EXPORT NSURLResourceKey const NSURLIsVolumeKey                    API_AVAILABLE(macos(10.6), ios(4.0), watchos(2.0), tvos(9.0));
/// `true` for packaged directories (Read-only 10_6 and 10_7, read-write 10_8, value type boolean `NSNumber`).
FOUNDATION_EXPORT NSURLResourceKey const NSURLIsPackageKey                   API_AVAILABLE(macos(10.6), ios(4.0), watchos(2.0), tvos(9.0));
/// `true` if resource is an application (Read-only, value type boolean `NSNumber`).
FOUNDATION_EXPORT NSURLResourceKey const NSURLIsApplicationKey               API_AVAILABLE(macos(10.11), ios(9.0), watchos(2.0), tvos(9.0));
/// `true` if the resource is scriptable. Only applies to applications (Read-only, value type boolean `NSNumber`).
FOUNDATION_EXPORT NSURLResourceKey const NSURLApplicationIsScriptableKey     API_AVAILABLE(macos(10.11)) API_UNAVAILABLE(ios, watchos, tvos);
/// `true` for system-immutable resources (Read-write, value type boolean `NSNumber`).
FOUNDATION_EXPORT NSURLResourceKey const NSURLIsSystemImmutableKey           API_AVAILABLE(macos(10.6), ios(4.0), watchos(2.0), tvos(9.0));
/// `true` for user-immutable resources (Read-write, value type boolean `NSNumber`).
FOUNDATION_EXPORT NSURLResourceKey const NSURLIsUserImmutableKey             API_AVAILABLE(macos(10.6), ios(4.0), watchos(2.0), tvos(9.0));
/// `true` for resources normally not displayed to users (Read-write, value type boolean `NSNumber`).
FOUNDATION_EXPORT NSURLResourceKey const NSURLIsHiddenKey                    API_AVAILABLE(macos(10.6), ios(4.0), watchos(2.0), tvos(9.0));
/// `true` for resources whose filename extension is removed from the localized name property (Read-write, value type boolean `NSNumber`).
FOUNDATION_EXPORT NSURLResourceKey const NSURLHasHiddenExtensionKey          API_AVAILABLE(macos(10.6), ios(4.0), watchos(2.0), tvos(9.0));
/// The date the resource was created (Read-write, value type `NSDate`).
FOUNDATION_EXPORT NSURLResourceKey const NSURLCreationDateKey                API_AVAILABLE(macos(10.6), ios(4.0), watchos(2.0), tvos(9.0));
/// The date the resource was last accessed (Read-write, value type `NSDate`).
FOUNDATION_EXPORT NSURLResourceKey const NSURLContentAccessDateKey           API_AVAILABLE(macos(10.6), ios(4.0), watchos(2.0), tvos(9.0));
/// The time the resource content was last modified (Read-write, value type `NSDate`).
FOUNDATION_EXPORT NSURLResourceKey const NSURLContentModificationDateKey     API_AVAILABLE(macos(10.6), ios(4.0), watchos(2.0), tvos(9.0));
/// The time the resource's attributes were last modified (Read-only, value type `NSDate`).
FOUNDATION_EXPORT NSURLResourceKey const NSURLAttributeModificationDateKey   API_AVAILABLE(macos(10.6), ios(4.0), watchos(2.0), tvos(9.0));
/// Number of hard links to the resource (Read-only, value type `NSNumber`).
FOUNDATION_EXPORT NSURLResourceKey const NSURLLinkCountKey                   API_AVAILABLE(macos(10.6), ios(4.0), watchos(2.0), tvos(9.0));
/// The resource's parent directory, if any (Read-only, value type `NSURL`).
FOUNDATION_EXPORT NSURLResourceKey const NSURLParentDirectoryURLKey          API_AVAILABLE(macos(10.6), ios(4.0), watchos(2.0), tvos(9.0));
/// URL of the volume on which the resource is stored (Read-only, value type `NSURL`).
FOUNDATION_EXPORT NSURLResourceKey const NSURLVolumeURLKey                   API_AVAILABLE(macos(10.6), ios(4.0), watchos(2.0), tvos(9.0));
/// Uniform type identifier (UTI) for the resource (Read-only, value type `NSString`).
FOUNDATION_EXPORT NSURLResourceKey const NSURLTypeIdentifierKey API_DEPRECATED("Use NSURLContentTypeKey instead", macos(10.6, API_TO_BE_DEPRECATED), ios(4.0, API_TO_BE_DEPRECATED), watchos(2.0, API_TO_BE_DEPRECATED), tvos(9.0, API_TO_BE_DEPRECATED));
/// File type (`UTType`) for the resource (Read-only, value type `UTType`).
FOUNDATION_EXPORT NSURLResourceKey const NSURLContentTypeKey                 API_AVAILABLE(macos(11.0), ios(14.0), watchos(7.0), tvos(14.0));
/// User-visible type or “kind” description (Read-only, value type `NSString`).
FOUNDATION_EXPORT NSURLResourceKey const NSURLLocalizedTypeDescriptionKey    API_AVAILABLE(macos(10.6), ios(4.0), watchos(2.0), tvos(9.0));
/// The label number assigned to the resource (Read-write, value type `NSNumber`).
FOUNDATION_EXPORT NSURLResourceKey const NSURLLabelNumberKey                 API_AVAILABLE(macos(10.6), ios(4.0), watchos(2.0), tvos(9.0));
/// The color of the assigned label (Read-only, value type `NSColor`).
FOUNDATION_EXPORT NSURLResourceKey const NSURLLabelColorKey                  API_AVAILABLE(macos(10.6), ios(4.0), watchos(2.0), tvos(9.0));
/// The user-visible label text (Read-only, value type `NSString`).
FOUNDATION_EXPORT NSURLResourceKey const NSURLLocalizedLabelKey              API_AVAILABLE(macos(10.6), ios(4.0), watchos(2.0), tvos(9.0));
/// The icon normally displayed for the resource (Read-only, value type `NSImage`).
FOUNDATION_EXPORT NSURLResourceKey const NSURLEffectiveIconKey               API_AVAILABLE(macos(10.6), ios(4.0), watchos(2.0), tvos(9.0));
/// The custom icon assigned to the resource, if any (Currently not implemented, value type `NSImage`).
FOUNDATION_EXPORT NSURLResourceKey const NSURLCustomIconKey                  API_AVAILABLE(macos(10.6), ios(4.0), watchos(2.0), tvos(9.0));
/// An identifier which can be used to compare two file system objects for equality using `isEqual`. Not persistent across system restarts. (Read-only, value type `id <NSCopying, NSCoding, NSSecureCoding, NSObject>`).
FOUNDATION_EXPORT NSURLResourceKey const NSURLFileResourceIdentifierKey      API_AVAILABLE(macos(10.7), ios(5.0), watchos(2.0), tvos(9.0));
/// An identifier that can be used to identify the volume the file system object is on. Not persistent across system restarts. (Read-only, value type `id <NSCopying, NSCoding, NSSecureCoding, NSObject>`).
FOUNDATION_EXPORT NSURLResourceKey const NSURLVolumeIdentifierKey            API_AVAILABLE(macos(10.7), ios(5.0), watchos(2.0), tvos(9.0));
/// The optimal block size when reading or writing this file's data, or `nil` if not available. (Read-only, value type `NSNumber`).
FOUNDATION_EXPORT NSURLResourceKey const NSURLPreferredIOBlockSizeKey        API_AVAILABLE(macos(10.7), ios(5.0), watchos(2.0), tvos(9.0));
/// `true` if this process (as determined by EUID) can read the resource. (Read-only, value type boolean `NSNumber`).
FOUNDATION_EXPORT NSURLResourceKey const NSURLIsReadableKey                  API_AVAILABLE(macos(10.7), ios(5.0), watchos(2.0), tvos(9.0));
/// `true` if this process (as determined by EUID) can write to the resource. (Read-only, value type boolean `NSNumber`).
FOUNDATION_EXPORT NSURLResourceKey const NSURLIsWritableKey                  API_AVAILABLE(macos(10.7), ios(5.0), watchos(2.0), tvos(9.0));
/// `true` if this process (as determined by EUID) can execute a file resource or search a directory resource. (Read-only, value type boolean `NSNumber`).
FOUNDATION_EXPORT NSURLResourceKey const NSURLIsExecutableKey                API_AVAILABLE(macos(10.7), ios(5.0), watchos(2.0), tvos(9.0));
/// The file system object's security information encapsulated in an `NSFileSecurity` object. (Read-write, value type `NSFileSecurity`).
FOUNDATION_EXPORT NSURLResourceKey const NSURLFileSecurityKey                API_AVAILABLE(macos(10.7), ios(5.0), watchos(2.0), tvos(9.0));
/// `true` if resource should be excluded from backups, `false` otherwise (Read-write, value type boolean `NSNumber`).
FOUNDATION_EXPORT NSURLResourceKey const NSURLIsExcludedFromBackupKey        API_AVAILABLE(macos(10.8), ios(5.1), watchos(2.0), tvos(9.0));
/// The array of Tag names (Read-write, value type `NSArray` of `NSString`).
FOUNDATION_EXPORT NSURLResourceKey const NSURLTagNamesKey                    API_AVAILABLE(macos(10.9)) API_UNAVAILABLE(ios, watchos, tvos);
/// The URL's path as a file system path (Read-only, value type `NSString`).
FOUNDATION_EXPORT NSURLResourceKey const NSURLPathKey                        API_AVAILABLE(macos(10.8), ios(6.0), watchos(2.0), tvos(9.0));
/// The URL's path as a canonical absolute file system path (Read-only, value type `NSString`).
FOUNDATION_EXPORT NSURLResourceKey const NSURLCanonicalPathKey               API_AVAILABLE(macosx(10.12), ios(10.0), watchos(3.0), tvos(10.0));
/// `true` if this URL is a file system trigger directory. (Read-only, value type boolean `NSNumber`).
FOUNDATION_EXPORT NSURLResourceKey const NSURLIsMountTriggerKey              API_AVAILABLE(macos(10.7), ios(5.0), watchos(2.0), tvos(9.0));
/// An opaque generation identifier for change detection. Persistent across system restarts. (Read-only, value type `id <NSCopying, NSCoding, NSSecureCoding, NSObject>`).
FOUNDATION_EXPORT NSURLResourceKey const NSURLGenerationIdentifierKey API_AVAILABLE(macos(10.10), ios(8.0), watchos(2.0), tvos(9.0));
/// The document identifier assigned by the kernel, used to identify the document regardless of where it moves on a volume. (Read-only, value type `NSNumber`).
FOUNDATION_EXPORT NSURLResourceKey const NSURLDocumentIdentifierKey API_AVAILABLE(macos(10.10), ios(8.0), watchos(2.0), tvos(9.0));
/// The date the resource was created, or renamed into or within its parent directory. (Read-only before macOS 10.15/iOS 13.0; Read-write after, value type `NSDate`).
FOUNDATION_EXPORT NSURLResourceKey const NSURLAddedToDirectoryDateKey API_AVAILABLE(macos(10.10), ios(8.0), watchos(2.0), tvos(9.0));
/// The quarantine properties as defined in `LSQuarantine.h`. Pass `NSNull` to remove quarantine information. (Read-write, value type `NSDictionary`).
FOUNDATION_EXPORT NSURLResourceKey const NSURLQuarantinePropertiesKey API_AVAILABLE(macos(10.10)) API_UNAVAILABLE(ios, watchos, tvos);
/// The file system object type. (Read-only, value type `NSString`).
FOUNDATION_EXPORT NSURLResourceKey const NSURLFileResourceTypeKey            API_AVAILABLE(macos(10.7), ios(5.0), watchos(2.0), tvos(9.0));
/// The file system's internal inode identifier for the item. Not stable across all file systems or mounts. (Read-only, value type `NSNumber` containing an unsigned long long).
FOUNDATION_EXPORT NSURLResourceKey const NSURLFileIdentifierKey              API_AVAILABLE(macos(13.3), ios(16.4), watchos(9.4), tvos(16.4));
/// A 64-bit value assigned by APFS that identifies a file's content data stream. (Read-only, value type `NSNumber`).
FOUNDATION_EXPORT NSURLResourceKey const NSURLFileContentIdentifierKey       API_AVAILABLE(macos(11.0), ios(14.0), watchos(7.0), tvos(14.0));
/// `true` for cloned files and their originals that may share data blocks. (Read-only, value type `NSNumber`).
FOUNDATION_EXPORT NSURLResourceKey const NSURLMayShareFileContentKey         API_AVAILABLE(macos(11.0), ios(14.0), watchos(7.0), tvos(14.0));
/// `true` if the file has extended attributes. `false` guarantees there are none. (Read-only, value type `NSNumber`).
FOUNDATION_EXPORT NSURLResourceKey const NSURLMayHaveExtendedAttributesKey   API_AVAILABLE(macos(11.0), ios(14.0), watchos(7.0), tvos(14.0));
/// `true` if the file can be deleted by the file system when asked to free space. (Read-only, value type `NSNumber`).
FOUNDATION_EXPORT NSURLResourceKey const NSURLIsPurgeableKey                 API_AVAILABLE(macos(11.0), ios(14.0), watchos(7.0), tvos(14.0));
/// `true` if the file has sparse regions. (Read-only, value type `NSNumber`).
FOUNDATION_EXPORT NSURLResourceKey const NSURLIsSparseKey                    API_AVAILABLE(macos(11.0), ios(14.0), watchos(7.0), tvos(14.0));

/// Possible values for the type of file resource.
typedef NSString * NSURLFileResourceType NS_TYPED_ENUM;

/// The resource is a named pipe.
FOUNDATION_EXPORT NSURLFileResourceType const NSURLFileResourceTypeNamedPipe      API_AVAILABLE(macos(10.7), ios(5.0), watchos(2.0), tvos(9.0));
/// The resource is a character special file.
FOUNDATION_EXPORT NSURLFileResourceType const NSURLFileResourceTypeCharacterSpecial API_AVAILABLE(macos(10.7), ios(5.0), watchos(2.0), tvos(9.0));
/// The resource is a directory.
FOUNDATION_EXPORT NSURLFileResourceType const NSURLFileResourceTypeDirectory      API_AVAILABLE(macos(10.7), ios(5.0), watchos(2.0), tvos(9.0));
/// The resource is a block special file.
FOUNDATION_EXPORT NSURLFileResourceType const NSURLFileResourceTypeBlockSpecial   API_AVAILABLE(macos(10.7), ios(5.0), watchos(2.0), tvos(9.0));
/// The resource is a regular file.
FOUNDATION_EXPORT NSURLFileResourceType const NSURLFileResourceTypeRegular        API_AVAILABLE(macos(10.7), ios(5.0), watchos(2.0), tvos(9.0));
/// The resource is a symbolic link.
FOUNDATION_EXPORT NSURLFileResourceType const NSURLFileResourceTypeSymbolicLink   API_AVAILABLE(macos(10.7), ios(5.0), watchos(2.0), tvos(9.0));
/// The resource is a socket.
FOUNDATION_EXPORT NSURLFileResourceType const NSURLFileResourceTypeSocket         API_AVAILABLE(macos(10.7), ios(5.0), watchos(2.0), tvos(9.0));
/// The resource's type is unknown.
FOUNDATION_EXPORT NSURLFileResourceType const NSURLFileResourceTypeUnknown        API_AVAILABLE(macos(10.7), ios(5.0), watchos(2.0), tvos(9.0));

/// A dictionary of `NSImage`/`UIImage` objects keyed by size (Read-write, value type `NSDictionary`). See `NSURLThumbnailDictionaryItem` for possible keys.
FOUNDATION_EXPORT NSURLResourceKey const NSURLThumbnailDictionaryKey         API_DEPRECATED("Use the QuickLookThumbnailing framework and extension point instead", macos(10.10, 12.0), ios(8.0, 15.0), watchos(2.0, 8.0), tvos(9.0, 15.0));
/// All thumbnails as a single `NSImage` (Read-write, value type `NSImage`).
FOUNDATION_EXPORT NSURLResourceKey const NSURLThumbnailKey                   API_DEPRECATED("Use the QuickLookThumbnailing framework and extension point instead", macos(10.10, 12.0)) API_UNAVAILABLE(ios, watchos, tvos);

/// Possible keys for the ``URLResourceKey/thumbnailDictionaryKey`` dictionary.
typedef NSString *NSURLThumbnailDictionaryItem NS_TYPED_EXTENSIBLE_ENUM;
/// A 1024 x 1024 pixel thumbnail as a `UIImage` on iOS or an `NSImage` on macOS.
FOUNDATION_EXPORT NSURLThumbnailDictionaryItem const NSThumbnail1024x1024SizeKey         API_DEPRECATED("Use the QuickLookThumbnailing framework and extension point instead", macos(10.10, 12.0), ios(8.0, 15.0), watchos(2.0, 8.0), tvos(9.0, 15.0));

// Resource keys applicable only to regular files
/// The file's size, in bytes (Read-only, value type `NSNumber`).
FOUNDATION_EXPORT NSURLResourceKey const NSURLFileSizeKey                    API_AVAILABLE(macos(10.6), ios(4.0), watchos(2.0), tvos(9.0));
/// The total allocated size on-disk for the file, in bytes (number of blocks times block size) (Read-only, value type `NSNumber`).
FOUNDATION_EXPORT NSURLResourceKey const NSURLFileAllocatedSizeKey           API_AVAILABLE(macos(10.6), ios(4.0), watchos(2.0), tvos(9.0));
/// Total displayable size of the file in bytes (this may include space used by metadata), or `nil` if not available. (Read-only, value type `NSNumber`).
FOUNDATION_EXPORT NSURLResourceKey const NSURLTotalFileSizeKey               API_AVAILABLE(macos(10.7), ios(5.0), watchos(2.0), tvos(9.0));
/// Total allocated size of the file in bytes (this may include space used by metadata), or `nil` if not available. This can be less than the value returned by `NSURLTotalFileSizeKey` if the resource is compressed. (Read-only, value type `NSNumber`).
FOUNDATION_EXPORT NSURLResourceKey const NSURLTotalFileAllocatedSizeKey      API_AVAILABLE(macos(10.7), ios(5.0), watchos(2.0), tvos(9.0));
/// `true` if the resource is a Finder alias file or a symlink, `false` otherwise (Read-only, value type boolean `NSNumber`).
FOUNDATION_EXPORT NSURLResourceKey const NSURLIsAliasFileKey                 API_AVAILABLE(macos(10.6), ios(4.0), watchos(2.0), tvos(9.0));
/// The protection level for this file (Read-write, value type `NSURLFileProtectionType`).
FOUNDATION_EXPORT NSURLResourceKey const NSURLFileProtectionKey              API_AVAILABLE(macos(10.11), ios(9.0), watchos(2.0), tvos(9.0));

/// Protection-level values for a URL resource key.
///
/// These are values for the ``URLResourceKey`` key ``URLResourceKey/fileProtectionKey``.
typedef NSString * NSURLFileProtectionType NS_TYPED_ENUM;
/// The file has no special protections associated with it. It can be read from or written to at any time.
FOUNDATION_EXPORT NSURLFileProtectionType const NSURLFileProtectionNone API_AVAILABLE(macos(11.0), ios(9.0), watchos(2.0), tvos(9.0));
/// The file is stored in an encrypted format on disk and cannot be read from or written to while the device is locked or booting.
FOUNDATION_EXPORT NSURLFileProtectionType const NSURLFileProtectionComplete API_AVAILABLE(macos(11.0), ios(9.0), watchos(2.0), tvos(9.0));
/// The file is stored in an encrypted format on disk after it closes. Files can be created while the device is locked, but once closed, cannot be opened again until the device is unlocked.
FOUNDATION_EXPORT NSURLFileProtectionType const NSURLFileProtectionCompleteUnlessOpen API_AVAILABLE(macos(11.0), ios(9.0), watchos(2.0), tvos(9.0));
/// The file is stored in an encrypted format on disk and cannot be accessed until after the device has booted. After the user unlocks the device for the first time, your app can access the file and continue to access it even if the user subsequently locks the device.
FOUNDATION_EXPORT NSURLFileProtectionType const NSURLFileProtectionCompleteUntilFirstUserAuthentication API_AVAILABLE(macos(11.0), ios(9.0), watchos(2.0), tvos(9.0));
/// The file is stored in an encrypted format on disk and cannot be accessed until after first unlock after the device has booted. After this first unlock, your app can access the file even while the device is locked until access expiry. Access is renewed once the user unlocks the device again.
FOUNDATION_EXPORT NSURLFileProtectionType const NSURLFileProtectionCompleteWhenUserInactive API_AVAILABLE(ios(17.0), watchos(10.0), tvos(17.0)) API_UNAVAILABLE(macos);

// Resource keys applicable only to directories
/// The count of file system objects contained in the directory (Read-only, value type `NSNumber`).
///
/// This is a count of objects actually stored in the file system, so excludes virtual items like `.` and `..`.
/// The property is useful for quickly identifying an empty directory for backup and syncing.
/// If the URL is not a directory or the file system cannot cheaply compute the value, `nil` is returned.
/// Not all file systems can provide this information.
FOUNDATION_EXPORT NSURLResourceKey const NSURLDirectoryEntryCountKey              API_AVAILABLE(macos(14.0), ios(17.0), watchos(10.0), tvos(17.0));

/* Volumes resource keys
 
 As a convenience, volume resource values can be requested from any file system URL. The value returned will reflect the property value for the volume on which the resource is located.
 */
/// The user-visible volume format (Read-only, value type `NSString`).
FOUNDATION_EXPORT NSURLResourceKey const NSURLVolumeLocalizedFormatDescriptionKey API_AVAILABLE(macos(10.6), ios(4.0), watchos(2.0), tvos(9.0));
/// The volume's total capacity in bytes (Read-only, value type `NSNumber`).
FOUNDATION_EXPORT NSURLResourceKey const NSURLVolumeTotalCapacityKey              API_AVAILABLE(macos(10.6), ios(4.0), watchos(2.0), tvos(9.0));
/// The volume's available capacity in bytes (Read-only, value type `NSNumber`).
FOUNDATION_EXPORT NSURLResourceKey const NSURLVolumeAvailableCapacityKey          API_AVAILABLE(macos(10.6), ios(4.0), watchos(2.0), tvos(9.0));
/// The total number of resources on the volume (Read-only, value type `NSNumber`).
FOUNDATION_EXPORT NSURLResourceKey const NSURLVolumeResourceCountKey              API_AVAILABLE(macos(10.6), ios(4.0), watchos(2.0), tvos(9.0));
/// `true` if the volume format supports persistent object identifiers and can look up file system objects by their IDs (Read-only, value type boolean `NSNumber`).
FOUNDATION_EXPORT NSURLResourceKey const NSURLVolumeSupportsPersistentIDsKey      API_AVAILABLE(macos(10.6), ios(4.0), watchos(2.0), tvos(9.0));
/// `true` if the volume format supports symbolic links (Read-only, value type boolean `NSNumber`).
FOUNDATION_EXPORT NSURLResourceKey const NSURLVolumeSupportsSymbolicLinksKey      API_AVAILABLE(macos(10.6), ios(4.0), watchos(2.0), tvos(9.0));
/// `true` if the volume format supports hard links (Read-only, value type boolean `NSNumber`).
FOUNDATION_EXPORT NSURLResourceKey const NSURLVolumeSupportsHardLinksKey          API_AVAILABLE(macos(10.6), ios(4.0), watchos(2.0), tvos(9.0));
/// `true` if the volume format supports a journal used to speed recovery in case of unplanned restart (such as a power outage or crash). This does not necessarily mean the volume is actively using a journal. (Read-only, value type boolean `NSNumber`).
FOUNDATION_EXPORT NSURLResourceKey const NSURLVolumeSupportsJournalingKey         API_AVAILABLE(macos(10.6), ios(4.0), watchos(2.0), tvos(9.0));
/// `true` if the volume is currently using a journal for speedy recovery after an unplanned restart. (Read-only, value type boolean `NSNumber`).
FOUNDATION_EXPORT NSURLResourceKey const NSURLVolumeIsJournalingKey               API_AVAILABLE(macos(10.6), ios(4.0), watchos(2.0), tvos(9.0));
/// `true` if the volume format supports sparse files, that is, files which can have 'holes' that have never been written to, and thus do not consume space on disk. A sparse file may have an allocated size on disk that is less than its logical length. (Read-only, value type boolean `NSNumber`).
FOUNDATION_EXPORT NSURLResourceKey const NSURLVolumeSupportsSparseFilesKey        API_AVAILABLE(macos(10.6), ios(4.0), watchos(2.0), tvos(9.0));
/// `true` if the volume keeps track of allocated but unwritten runs of a file so that it can substitute zeroes without actually writing zeroes to the media. For security reasons, parts of a file (runs) that have never been written to must appear to contain zeroes. (Read-only, value type boolean `NSNumber`).
FOUNDATION_EXPORT NSURLResourceKey const NSURLVolumeSupportsZeroRunsKey           API_AVAILABLE(macos(10.6), ios(4.0), watchos(2.0), tvos(9.0));
/// `true` if the volume format treats upper and lower case characters in file and directory names as different. Otherwise an upper case character is equivalent to a lower case character, and you can't have two names that differ solely in the case of the characters. (Read-only, value type boolean `NSNumber`).
FOUNDATION_EXPORT NSURLResourceKey const NSURLVolumeSupportsCaseSensitiveNamesKey API_AVAILABLE(macos(10.6), ios(4.0), watchos(2.0), tvos(9.0));
/// `true` if the volume format preserves the case of file and directory names. Otherwise the volume may change the case of some characters (typically making them all upper or all lower case). (Read-only, value type boolean `NSNumber`).
FOUNDATION_EXPORT NSURLResourceKey const NSURLVolumeSupportsCasePreservedNamesKey API_AVAILABLE(macos(10.6), ios(4.0), watchos(2.0), tvos(9.0));
/// `true` if the volume supports reliable storage of times for the root directory. (Read-only, value type boolean `NSNumber`).
FOUNDATION_EXPORT NSURLResourceKey const NSURLVolumeSupportsRootDirectoryDatesKey API_AVAILABLE(macos(10.7), ios(5.0), watchos(2.0), tvos(9.0));
/// `true` if the volume supports returning volume size values (`NSURLVolumeTotalCapacityKey` and `NSURLVolumeAvailableCapacityKey`). (Read-only, value type boolean `NSNumber`).
FOUNDATION_EXPORT NSURLResourceKey const NSURLVolumeSupportsVolumeSizesKey        API_AVAILABLE(macos(10.7), ios(5.0), watchos(2.0), tvos(9.0));
/// `true` if the volume can be renamed. (Read-only, value type boolean `NSNumber`).
FOUNDATION_EXPORT NSURLResourceKey const NSURLVolumeSupportsRenamingKey           API_AVAILABLE(macos(10.7), ios(5.0), watchos(2.0), tvos(9.0));
/// `true` if the volume implements whole-file flock(2) style advisory locks, and the `O_EXLOCK` and `O_SHLOCK` flags of the open(2) call. (Read-only, value type boolean `NSNumber`).
FOUNDATION_EXPORT NSURLResourceKey const NSURLVolumeSupportsAdvisoryFileLockingKey API_AVAILABLE(macos(10.7), ios(5.0), watchos(2.0), tvos(9.0));
/// `true` if the volume implements extended security (ACLs). (Read-only, value type boolean `NSNumber`).
FOUNDATION_EXPORT NSURLResourceKey const NSURLVolumeSupportsExtendedSecurityKey   API_AVAILABLE(macos(10.7), ios(5.0), watchos(2.0), tvos(9.0));
/// `true` if the volume should be visible via the GUI (i.e., appear on the Desktop as a separate volume). (Read-only, value type boolean `NSNumber`).
FOUNDATION_EXPORT NSURLResourceKey const NSURLVolumeIsBrowsableKey                API_AVAILABLE(macos(10.7), ios(5.0), watchos(2.0), tvos(9.0));
/// The largest file size (in bytes) supported by this file system, or `nil` if this cannot be determined. (Read-only, value type `NSNumber`).
FOUNDATION_EXPORT NSURLResourceKey const NSURLVolumeMaximumFileSizeKey            API_AVAILABLE(macos(10.7), ios(5.0), watchos(2.0), tvos(9.0));
/// `true` if the volume's media is ejectable from the drive mechanism under software control. (Read-only, value type boolean `NSNumber`).
FOUNDATION_EXPORT NSURLResourceKey const NSURLVolumeIsEjectableKey                API_AVAILABLE(macos(10.7), ios(5.0), watchos(2.0), tvos(9.0));
/// `true` if the volume's media is removable from the drive mechanism. (Read-only, value type boolean `NSNumber`).
FOUNDATION_EXPORT NSURLResourceKey const NSURLVolumeIsRemovableKey                API_AVAILABLE(macos(10.7), ios(5.0), watchos(2.0), tvos(9.0));
/// `true` if the volume's device is connected to an internal bus, `false` if connected to an external bus, or `nil` if not available. (Read-only, value type boolean `NSNumber`).
FOUNDATION_EXPORT NSURLResourceKey const NSURLVolumeIsInternalKey                 API_AVAILABLE(macos(10.7), ios(5.0), watchos(2.0), tvos(9.0));
/// `true` if the volume is automounted. Note: do not mistake this with the functionality provided by `kCFURLVolumeSupportsBrowsingKey`. (Read-only, value type boolean `NSNumber`).
FOUNDATION_EXPORT NSURLResourceKey const NSURLVolumeIsAutomountedKey              API_AVAILABLE(macos(10.7), ios(5.0), watchos(2.0), tvos(9.0));
/// `true` if the volume is stored on a local device. (Read-only, value type boolean `NSNumber`).
FOUNDATION_EXPORT NSURLResourceKey const NSURLVolumeIsLocalKey                    API_AVAILABLE(macos(10.7), ios(5.0), watchos(2.0), tvos(9.0));
/// `true` if the volume is read-only. (Read-only, value type boolean `NSNumber`).
FOUNDATION_EXPORT NSURLResourceKey const NSURLVolumeIsReadOnlyKey                 API_AVAILABLE(macos(10.7), ios(5.0), watchos(2.0), tvos(9.0));
/// The volume's creation date, or `nil` if this cannot be determined. (Read-only, value type `NSDate`).
FOUNDATION_EXPORT NSURLResourceKey const NSURLVolumeCreationDateKey               API_AVAILABLE(macos(10.7), ios(5.0), watchos(2.0), tvos(9.0));
/// The `NSURL` needed to remount a network volume, or `nil` if not available. (Read-only, value type `NSURL`).
FOUNDATION_EXPORT NSURLResourceKey const NSURLVolumeURLForRemountingKey           API_AVAILABLE(macos(10.7), ios(5.0), watchos(2.0), tvos(9.0));
/// The volume's persistent UUID as a string, or `nil` if a persistent UUID is not available for the volume. (Read-only, value type `NSString`).
FOUNDATION_EXPORT NSURLResourceKey const NSURLVolumeUUIDStringKey                 API_AVAILABLE(macos(10.7), ios(5.0), watchos(2.0), tvos(9.0));
/// The name of the volume (Read-write if `NSURLVolumeSupportsRenamingKey` is `YES`, otherwise read-only, value type `NSString`).
FOUNDATION_EXPORT NSURLResourceKey const NSURLVolumeNameKey                       API_AVAILABLE(macos(10.7), ios(5.0), watchos(2.0), tvos(9.0));
/// The user-presentable name of the volume (Read-only, value type `NSString`).
FOUNDATION_EXPORT NSURLResourceKey const NSURLVolumeLocalizedNameKey              API_AVAILABLE(macos(10.7), ios(5.0), watchos(2.0), tvos(9.0));
/// `true` if the volume is encrypted. (Read-only, value type boolean `NSNumber`).
FOUNDATION_EXPORT NSURLResourceKey const NSURLVolumeIsEncryptedKey                API_AVAILABLE(macosx(10.12), ios(10.0), watchos(3.0), tvos(10.0));
/// `true` if the volume is the root filesystem. (Read-only, value type boolean `NSNumber`).
FOUNDATION_EXPORT NSURLResourceKey const NSURLVolumeIsRootFileSystemKey           API_AVAILABLE(macosx(10.12), ios(10.0), watchos(3.0), tvos(10.0));
/// `true` if the volume supports transparent decompression of compressed files using `decmpfs`. (Read-only, value type boolean `NSNumber`).
FOUNDATION_EXPORT NSURLResourceKey const NSURLVolumeSupportsCompressionKey        API_AVAILABLE(macosx(10.12), ios(10.0), watchos(3.0), tvos(10.0));
/// `true` if the volume supports `clonefile(2)`. (Read-only, value type boolean `NSNumber`).
FOUNDATION_EXPORT NSURLResourceKey const NSURLVolumeSupportsFileCloningKey API_AVAILABLE(macosx(10.12), ios(10.0), watchos(3.0), tvos(10.0));
/// `true` if the volume supports `renamex_np(2)`'s `RENAME_SWAP` option. (Read-only, value type boolean `NSNumber`).
FOUNDATION_EXPORT NSURLResourceKey const NSURLVolumeSupportsSwapRenamingKey API_AVAILABLE(macosx(10.12), ios(10.0), watchos(3.0), tvos(10.0));
/// `true` if the volume supports `renamex_np(2)`'s `RENAME_EXCL` option. (Read-only, value type boolean `NSNumber`).
FOUNDATION_EXPORT NSURLResourceKey const NSURLVolumeSupportsExclusiveRenamingKey API_AVAILABLE(macosx(10.12), ios(10.0), watchos(3.0), tvos(10.0));
/// `true` if the volume supports making files immutable with the `NSURLIsUserImmutableKey` or `NSURLIsSystemImmutableKey` properties. (Read-only, value type boolean `NSNumber`).
FOUNDATION_EXPORT NSURLResourceKey const NSURLVolumeSupportsImmutableFilesKey API_AVAILABLE(macosx(10.13), ios(11.0), watchos(4.0), tvos(11.0));
/// `true` if the volume supports setting POSIX access permissions with the `NSURLFileSecurityKey` property. (Read-only, value type boolean `NSNumber`).
FOUNDATION_EXPORT NSURLResourceKey const NSURLVolumeSupportsAccessPermissionsKey API_AVAILABLE(macosx(10.13), ios(11.0), watchos(4.0), tvos(11.0));
/// `true` if the volume supports the File Protection attribute (see `NSURLFileProtectionKey`). (Read-only, value type `NSNumber`).
FOUNDATION_EXPORT NSURLResourceKey const NSURLVolumeSupportsFileProtectionKey     API_AVAILABLE(macos(11.0), ios(14.0), watchos(7.0), tvos(14.0));

/// The volume's available capacity in bytes for storing important resources, including space expected to be cleared by purging non-essential and cached resources. (Read-only, value type `NSNumber`).
///
/// "Important" means something that the user or application clearly expects to be present on the local system,
/// but is ultimately replaceable. This would include items that the user has explicitly requested via the UI,
/// and resources that an application requires in order to provide functionality.
///
/// Examples: A video that the user has explicitly requested to watch but has not yet finished watching
/// or an audio file that the user has requested to download.
///
/// This value should not be used in determining if there is room for an irreplaceable resource.
/// In the case of irreplaceable resources, always attempt to save the resource regardless of available capacity
/// and handle failure as gracefully as possible.
FOUNDATION_EXPORT NSURLResourceKey const NSURLVolumeAvailableCapacityForImportantUsageKey API_AVAILABLE(macos(10.13), ios(11.0)) API_UNAVAILABLE(watchos, tvos);

/// The volume's available capacity in bytes for storing nonessential resources, including space expected to be cleared by purging non-essential and cached resources. (Read-only, value type `NSNumber`).
///
/// "Opportunistic" means something that the user is likely to want but does not expect to be present on the local system,
/// but is ultimately non-essential and replaceable. This would include items that will be created or downloaded
/// without an explicit request from the user on the current device.
///
/// Examples: A background download of a newly available episode of a TV series that a user has been recently watching,
/// a piece of content explicitly requested on another device, or a new document saved to a network server
/// by the current user from another device.
FOUNDATION_EXPORT NSURLResourceKey const NSURLVolumeAvailableCapacityForOpportunisticUsageKey API_AVAILABLE(macos(10.13), ios(11.0)) API_UNAVAILABLE(watchos, tvos);

/// The name of the file system type. (Read-only, value type `NSString`).
FOUNDATION_EXPORT NSURLResourceKey const NSURLVolumeTypeNameKey                       API_AVAILABLE(macos(13.3), ios(16.4), watchos(9.4), tvos(16.4));
/// The file system subtype value. (Read-only, value type `NSNumber`).
FOUNDATION_EXPORT NSURLResourceKey const NSURLVolumeSubtypeKey                        API_AVAILABLE(macos(13.3), ios(16.4), watchos(9.4), tvos(16.4));
/// The volume mounted from location. (Read-only, value type `NSString`).
FOUNDATION_EXPORT NSURLResourceKey const NSURLVolumeMountFromLocationKey              API_AVAILABLE(macos(13.3), ios(16.4), watchos(9.4), tvos(16.4));

// Ubiquitous item resource keys
/// `true` if this item is synced to the cloud, `false` if it is only a local file. (Read-only, value type boolean `NSNumber`).
FOUNDATION_EXPORT NSURLResourceKey const NSURLIsUbiquitousItemKey                     API_AVAILABLE(macos(10.7), ios(5.0), watchos(2.0), tvos(9.0));
/// `true` if this item has conflicts outstanding. (Read-only, value type boolean `NSNumber`).
FOUNDATION_EXPORT NSURLResourceKey const NSURLUbiquitousItemHasUnresolvedConflictsKey API_AVAILABLE(macos(10.7), ios(5.0), watchos(2.0), tvos(9.0));
/// Equivalent to `NSURLUbiquitousItemDownloadingStatusKey == NSURLUbiquitousItemDownloadingStatusCurrent`. Has never behaved as documented in earlier releases, hence deprecated. (Read-only, value type boolean `NSNumber`).
FOUNDATION_EXPORT NSURLResourceKey const NSURLUbiquitousItemIsDownloadedKey           API_DEPRECATED("Use NSURLUbiquitousItemDownloadingStatusKey instead", macos(10.7,10.9), ios(5.0,7.0), watchos(2.0,2.0), tvos(9.0,9.0));
/// `true` if data is being downloaded for this item. (Read-only, value type boolean `NSNumber`).
FOUNDATION_EXPORT NSURLResourceKey const NSURLUbiquitousItemIsDownloadingKey          API_AVAILABLE(macos(10.7), ios(5.0), watchos(2.0), tvos(9.0));
/// `true` if there is data present in the cloud for this item. (Read-only, value type boolean `NSNumber`).
FOUNDATION_EXPORT NSURLResourceKey const NSURLUbiquitousItemIsUploadedKey             API_AVAILABLE(macos(10.7), ios(5.0), watchos(2.0), tvos(9.0));
/// `true` if data is being uploaded for this item. (Read-only, value type boolean `NSNumber`).
FOUNDATION_EXPORT NSURLResourceKey const NSURLUbiquitousItemIsUploadingKey            API_AVAILABLE(macos(10.7), ios(5.0), watchos(2.0), tvos(9.0));
/// Use `NSMetadataQuery` and `NSMetadataUbiquitousItemPercentDownloadedKey` on `NSMetadataItem` instead.
FOUNDATION_EXPORT NSURLResourceKey const NSURLUbiquitousItemPercentDownloadedKey      API_DEPRECATED("Use NSMetadataUbiquitousItemPercentDownloadedKey instead", macos(10.7,10.8), ios(5.0,6.0), watchos(2.0,2.0), tvos(9.0,9.0));
/// Use `NSMetadataQuery` and `NSMetadataUbiquitousItemPercentUploadedKey` on `NSMetadataItem` instead.
FOUNDATION_EXPORT NSURLResourceKey const NSURLUbiquitousItemPercentUploadedKey        API_DEPRECATED("Use NSMetadataUbiquitousItemPercentUploadedKey instead", macos(10.7,10.8), ios(5.0,6.0), watchos(2.0,2.0), tvos(9.0,9.0));
/// The current download state for the item. (Read-only, value type `NSString`).
///
/// The value indicates whether a local copy exists and whether that copy is the most current version of the item.
/// See `NSURLUbiquitousItemDownloadingStatus` for possible values.
FOUNDATION_EXPORT NSURLResourceKey const NSURLUbiquitousItemDownloadingStatusKey      API_AVAILABLE(macos(10.9), ios(7.0), watchos(2.0), tvos(9.0));
/// An error object that indicates why downloading the item from iCloud failed, see the `NSUbiquitousFile` section in FoundationErrors.h. (Read-only, value type `NSError`).
FOUNDATION_EXPORT NSURLResourceKey const NSURLUbiquitousItemDownloadingErrorKey       API_AVAILABLE(macos(10.9), ios(7.0), watchos(2.0), tvos(9.0));
/// An error object that indicates why uploading the item to iCloud failed, see the `NSUbiquitousFile` section in FoundationErrors.h. (Read-only, value type `NSError`).
FOUNDATION_EXPORT NSURLResourceKey const NSURLUbiquitousItemUploadingErrorKey         API_AVAILABLE(macos(10.9), ios(7.0), watchos(2.0), tvos(9.0));
/// `true` if a download of this item has already been requested with an API like `startDownloadingUbiquitousItemAtURL:error:`. (Read-only, value type boolean `NSNumber`).
FOUNDATION_EXPORT NSURLResourceKey const NSURLUbiquitousItemDownloadRequestedKey      API_AVAILABLE(macos(10.10), ios(8.0), watchos(2.0), tvos(9.0));
/// The name of this item's container as displayed to users. (Read-only, value type `NSString`).
FOUNDATION_EXPORT NSURLResourceKey const NSURLUbiquitousItemContainerDisplayNameKey   API_AVAILABLE(macos(10.10), ios(8.0), watchos(2.0), tvos(9.0));
/// `true` if the item is excluded from sync, which means it is locally on disk but won't be available on the server. An excluded item is no longer ubiquitous. (Read-write, value type boolean `NSNumber`).
FOUNDATION_EXPORT NSURLResourceKey const NSURLUbiquitousItemIsExcludedFromSyncKey     API_AVAILABLE(macos(11.3), ios(14.5), watchos(7.4), tvos(14.5));

/// `true` if the ubiquitous item is shared. (Read-only, value type boolean `NSNumber`).
FOUNDATION_EXPORT NSURLResourceKey const NSURLUbiquitousItemIsSharedKey                               API_AVAILABLE(macosx(10.12), ios(10.0)) API_UNAVAILABLE(watchos, tvos);
/// The current user's role for this shared item, or `nil` if not shared. (Read-only, value type `NSString`). See `NSURLUbiquitousSharedItemRole` for possible values.
FOUNDATION_EXPORT NSURLResourceKey const NSURLUbiquitousSharedItemCurrentUserRoleKey                  API_AVAILABLE(macosx(10.12), ios(10.0)) API_UNAVAILABLE(watchos, tvos);
/// The permissions for the current user, or `nil` if not shared. (Read-only, value type `NSString`). See `NSURLUbiquitousSharedItemPermissions` for possible values.
FOUNDATION_EXPORT NSURLResourceKey const NSURLUbiquitousSharedItemCurrentUserPermissionsKey           API_AVAILABLE(macosx(10.12), ios(10.0)) API_UNAVAILABLE(watchos, tvos);
/// The name components of the item's owner, or `nil` if the current user is the owner. (Read-only, value type `NSPersonNameComponents`).
FOUNDATION_EXPORT NSURLResourceKey const NSURLUbiquitousSharedItemOwnerNameComponentsKey              API_AVAILABLE(macosx(10.12), ios(10.0)) API_UNAVAILABLE(watchos, tvos);
/// The name components of the most recent editor of the document, or `nil` if it is the current user. (Read-only, value type `NSPersonNameComponents`).
FOUNDATION_EXPORT NSURLResourceKey const NSURLUbiquitousSharedItemMostRecentEditorNameComponentsKey   API_AVAILABLE(macosx(10.12), ios(10.0)) API_UNAVAILABLE(watchos, tvos);

/// Values that describe the iCloud storage state of a file.
///
/// ## Discussion
///
/// These constants are possible values for the ``URLResourceKey/ubiquitousItemDownloadingStatusKey`` key.
typedef NSString * NSURLUbiquitousItemDownloadingStatus NS_TYPED_ENUM;
/// The values returned for the `NSURLUbiquitousItemDownloadingStatusKey`.
/// This item has not been downloaded yet. Use `startDownloadingUbiquitousItemAtURL:error:` to download it.
FOUNDATION_EXPORT NSURLUbiquitousItemDownloadingStatus const NSURLUbiquitousItemDownloadingStatusNotDownloaded  API_AVAILABLE(macos(10.9), ios(7.0), watchos(2.0), tvos(9.0));
/// A local copy of this item exists, but it is stale. The most recent version will be downloaded as soon as possible.
FOUNDATION_EXPORT NSURLUbiquitousItemDownloadingStatus const NSURLUbiquitousItemDownloadingStatusDownloaded     API_AVAILABLE(macos(10.9), ios(7.0), watchos(2.0), tvos(9.0));
/// A local copy of this item exists and is the most up-to-date version known to the device.
FOUNDATION_EXPORT NSURLUbiquitousItemDownloadingStatus const NSURLUbiquitousItemDownloadingStatusCurrent        API_AVAILABLE(macos(10.9), ios(7.0), watchos(2.0), tvos(9.0));

/// The key for the role of a shared item.
typedef NSString * NSURLUbiquitousSharedItemRole NS_TYPED_ENUM;

/// The values returned for the `NSURLUbiquitousSharedItemCurrentUserRoleKey`.
/// The current user is the owner of this shared item.
FOUNDATION_EXPORT NSURLUbiquitousSharedItemRole const NSURLUbiquitousSharedItemRoleOwner       API_AVAILABLE(macosx(10.12), ios(10.0)) API_UNAVAILABLE(watchos, tvos);
/// The current user is a participant of this shared item.
FOUNDATION_EXPORT NSURLUbiquitousSharedItemRole const NSURLUbiquitousSharedItemRoleParticipant API_AVAILABLE(macosx(10.12), ios(10.0)) API_UNAVAILABLE(watchos, tvos);

/// The key for the permissions of a shared item.
typedef NSString * NSURLUbiquitousSharedItemPermissions NS_TYPED_ENUM;

/// The values returned for the `NSURLUbiquitousSharedItemCurrentUserPermissionsKey`.
/// The current user is only allowed to read this item.
FOUNDATION_EXPORT NSURLUbiquitousSharedItemPermissions const NSURLUbiquitousSharedItemPermissionsReadOnly     API_AVAILABLE(macosx(10.12), ios(10.0)) API_UNAVAILABLE(watchos, tvos);
/// The current user is allowed to both read and write this item.
FOUNDATION_EXPORT NSURLUbiquitousSharedItemPermissions const NSURLUbiquitousSharedItemPermissionsReadWrite    API_AVAILABLE(macosx(10.12), ios(10.0)) API_UNAVAILABLE(watchos, tvos);

/// The read-only value of the `NSFileManagerSupportedSyncControls` options (value type `NSNumber`).
FOUNDATION_EXPORT NSURLResourceKey const NSURLUbiquitousItemSupportedSyncControlsKey API_AVAILABLE(ios(26.0), macos(26.0), watchos(26.0), tvos(26.0), visionos(26.0));
/// A Boolean value that indicates whether sync is paused for this item (value type boolean `NSNumber`).
FOUNDATION_EXPORT NSURLResourceKey const NSURLUbiquitousItemIsSyncPausedKey API_AVAILABLE(ios(26.0), macos(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

/* Working with Bookmarks and alias (bookmark) files
 */

/// Options used when creating bookmark data.
///
/// When creating a bookmark, use bitwise `OR` operators to combine the options you want to specify, and provide them to the `options` parameter of the ``NSURL/bookmarkData(options:includingResourceValuesForKeys:relativeTo:)`` method.
///
/// > Note:
/// > Security-scoped bookmarks aren't available in versions of macOS prior to 10.7.3.
typedef NS_OPTIONS(NSUInteger, NSURLBookmarkCreationOptions) {
    /// This option does nothing and has no effect on bookmark resolution.
    NSURLBookmarkCreationPreferFileIDResolution API_DEPRECATED("Not supported", macos(10.6,10.9), ios(4.0,7.0), watchos(2.0,2.0), tvos(9.0,9.0)) = ( 1UL << 8 ),
    /// Creates bookmark data with "less" information, which may be smaller but still be able to resolve in certain ways.
    NSURLBookmarkCreationMinimalBookmark = ( 1UL << 9 ),
    /// Specifies that the bookmark data includes the required properties for creating Finder alias files.
    NSURLBookmarkCreationSuitableForBookmarkFile = ( 1UL << 10 ),
    /// Specifies that when creating a security-scoped bookmark, upon resolution, it provides a security-scoped URL allowing read/write access to a file-system resource.
    NSURLBookmarkCreationWithSecurityScope API_AVAILABLE(macos(10.7), macCatalyst(13.0)) API_UNAVAILABLE(ios, watchos, tvos) = ( 1 << 11 ),
    /// Specifies that when creating a security-scoped bookmark, upon resolution, it provides a security-scoped URL allowing read-only access to a file-system resource.
    ///
    /// This option is only meaningful when used along with `NSURLBookmarkCreationWithSecurityScope`.
    NSURLBookmarkCreationSecurityScopeAllowOnlyReadAccess API_AVAILABLE(macos(10.7), macCatalyst(13.0)) API_UNAVAILABLE(ios, watchos, tvos) = ( 1 << 12 ),
    /// Prevents inclusion of a bookmark's implicit ephemeral security scope, when creating one without security scope.
    ///
    /// Bookmarks that you create without security scope automatically carry implicit ephemeral security scope.
    /// This security scope is valid until reboot at the latest, and confers access to the resource to any other
    /// process that resolves the bookmark. Using this option prevents inclusion of this ephemeral security scope.
    /// When using this option, other processes can't call `startAccessingSecurityScopedResource` on the resolved URL.
    NSURLBookmarkCreationWithoutImplicitSecurityScope  API_AVAILABLE(macos(10.7), ios(5.0), watchos(2.0), tvos(9.0)) = (1 << 29)
} API_AVAILABLE(macos(10.6), ios(4.0), watchos(2.0), tvos(9.0));

/// Options used when resolving bookmark data.
///
/// When resolving a bookmark, use bitwise `OR` operators to combine the options you want to specify, and provide them to the `options` parameter of the ``NSURL/init(resolvingBookmarkData:options:relativeTo:bookmarkDataIsStale:)`` method.
typedef NS_OPTIONS(NSUInteger, NSURLBookmarkResolutionOptions) {
    /// Specifies that no UI feedback should accompany resolution of the bookmark data.
    NSURLBookmarkResolutionWithoutUI = ( 1UL << 8 ),
    /// Specifies that no volume should be mounted during resolution of the bookmark data.
    NSURLBookmarkResolutionWithoutMounting = ( 1UL << 9 ),
    /// Specifies that the security scope, applied to the bookmark when it was created, should be used during resolution of the bookmark data.
    NSURLBookmarkResolutionWithSecurityScope API_AVAILABLE(macos(10.7), macCatalyst(13.0)) API_UNAVAILABLE(ios, watchos, tvos) = ( 1 << 10 ),
    /// Specifies that resolution doesn't implicitly start accessing the ephemeral security-scoped resource.
    ///
    /// Instead, call `startAccessingSecurityScopedResource` on the returned URL when ready to use the resource.
    /// Not applicable to security-scoped bookmarks.
    NSURLBookmarkResolutionWithoutImplicitStartAccessing API_AVAILABLE(macos(11.2), ios(14.2), watchos(7.2), tvos(14.2)) = ( 1 << 15 ),
} API_AVAILABLE(macos(10.6), ios(4.0), watchos(2.0), tvos(9.0));

/// Options used when creating file bookmark data.
///
/// See `NSURLBookmarkCreationOptions` for more information.
typedef NSUInteger NSURLBookmarkFileCreationOptions;

/// Returns bookmark data for the URL, created with specified options and resource values.
///
/// This method returns bookmark data that can later be resolved into a URL object for a file even if the user
/// moves or renames it (if the volume format on which the file resides supports doing so).
///
/// If the specified URL is not a file URL, this method returns a bookmark containing only the URL, and the
/// `options` and `keys` parameters are ignored.
///
/// You can also use this method to create a security-scoped bookmark to support App Sandbox. Before you do so,
/// you must first enable the appropriate entitlements for your app. In addition, be sure to understand the behavior
/// of the `options` and `relativeURL` parameters.
///
/// For an app-scoped bookmark, no sandboxed app other than the one that created the bookmark can obtain access to
/// the file-system resource that the URL (obtained from the bookmark) points to.
///
/// For a document-scoped bookmark, any sandboxed app that has access to the bookmark data itself, and has access
/// to the document that owns the bookmark, can obtain access to the resource.
///
/// - Parameters:
///   - options: Options taken into account when creating the bookmark for the URL.
///   - keys: An array of names of URL resource properties to store as part of the bookmark.
///   - relativeURL: The URL that the bookmark data will be relative to. For an app-scoped bookmark, use `nil`.
///     For a document-scoped bookmark, use the absolute path to the document file that is to own the bookmark.
///   - error: The error that occurred in the case that the bookmark data cannot be created.
/// - Returns: Bookmark data for the URL, or `nil` if an error occurred.
- (nullable NSData *)bookmarkDataWithOptions:(NSURLBookmarkCreationOptions)options includingResourceValuesForKeys:(nullable NSArray<NSURLResourceKey> *)keys relativeToURL:(nullable NSURL *)relativeURL error:(NSError **)error API_AVAILABLE(macos(10.6), ios(4.0), watchos(2.0), tvos(9.0));

/// Initializes a newly created NSURL that points to a location specified by resolving bookmark data.
///
/// - Parameters:
///   - bookmarkData: The bookmark data the URL is derived from.
///   - options: Options taken into account when resolving the bookmark data.
///   - relativeURL: The base URL that the bookmark data is relative to.
///   - isStale: On return, if `YES`, the bookmark data is stale.
///   - error: The error that occurred in the case that the URL cannot be created.
/// - Returns: An NSURL initialized by resolving `bookmarkData`.
- (nullable instancetype)initByResolvingBookmarkData:(NSData *)bookmarkData options:(NSURLBookmarkResolutionOptions)options relativeToURL:(nullable NSURL *)relativeURL bookmarkDataIsStale:(BOOL * _Nullable)isStale error:(NSError **)error API_AVAILABLE(macos(10.6), ios(4.0), watchos(2.0), tvos(9.0));
/// Returns a new URL made by resolving bookmark data.
///
/// This method fails if the original file or directory could not be located or is on a volume that could not be mounted. If this method fails, you can use the ``NSURL/resourceValuesForKeys:fromBookmarkData:`` method to obtain information about the bookmark, such as the last known path (``NSURLPathKey``) to help the user decide how to proceed.
///
/// To obtain a security-scoped URL from a security-scoped bookmark, call this method using the ``NSURLBookmarkResolutionWithSecurityScope`` option. In addition, to use security scope, you must first have enabled the appropriate entitlements for your app, as described in [Enabling Security-Scoped Bookmark and URL Access](https://developer.apple.com/library/archive/documentation/Miscellaneous/Reference/EntitlementKeyReference/Chapters/EnablingAppSandbox.html#//apple_ref/doc/uid/TP40011195-CH4-SW18).
///
/// To then obtain access to the file-system resource pointed to by a security-scoped URL (in other words, to bring the resource into your app's sandbox), call the ``NSURL/startAccessingSecurityScopedResource`` method on the URL.
///
/// For an app-scoped bookmark, no sandboxed app other than the one that created the bookmark can obtain access to the file-system resource that the URL (obtained from the bookmark) points to.
///
/// For a document-scoped bookmark, any sandboxed app that has access to the bookmark data itself, and has access to the document that owns the bookmark, can obtain access to the resource.
///
/// > Note: Security-scoped bookmarks are not available in versions of macOS prior to OS X v10.7.3.
///
/// - Parameters:
///   - bookmarkData: The bookmark data the URL is derived from.
///   - options: Options taken into account when resolving the bookmark data. To resolve a security-scoped bookmark to support App Sandbox, you must include the ``NSURLBookmarkResolutionWithSecurityScope`` option.
///   - relativeURL: The base URL that the bookmark data is relative to. To resolve an app-scoped bookmark, use a value of `nil`. To resolve a document-scoped bookmark, use the absolute path to the document from which you retrieved the bookmark.
///   - isStale: On return, if `YES`, the bookmark data is stale. Your app should create a new bookmark using the returned URL and use it in place of any stored copies of the existing bookmark.
///   - error: The error that occurred in the case that the URL cannot be created.
/// - Returns: A new URL made by resolving `bookmarkData`.
+ (nullable instancetype)URLByResolvingBookmarkData:(NSData *)bookmarkData options:(NSURLBookmarkResolutionOptions)options relativeToURL:(nullable NSURL *)relativeURL bookmarkDataIsStale:(BOOL * _Nullable)isStale error:(NSError **)error API_AVAILABLE(macos(10.6), ios(4.0), watchos(2.0), tvos(9.0));

/// Returns the resource values for properties identified by a specified array of keys contained in specified bookmark data.
///
/// If the result dictionary does not contain a resource value for one or more of the requested resource keys, it means those resource properties are not available in the bookmark data.
///
/// - Parameters:
///   - keys: An array of names of URL resource properties. In addition to the standard, system-defined resource properties, you can also request any custom properties that you provided when you created the bookmark.
///   - bookmarkData: The bookmark data from which you want to retrieve resource values.
/// - Returns: A dictionary of the requested resource values contained in `bookmarkData`.
+ (nullable NSDictionary<NSURLResourceKey, id> *)resourceValuesForKeys:(NSArray<NSURLResourceKey> *)keys fromBookmarkData:(NSData *)bookmarkData API_AVAILABLE(macos(10.6), ios(4.0), watchos(2.0), tvos(9.0));

/// Creates an alias file on disk at a specified location with specified bookmark data.
///
/// This method will produce an error if `bookmarkData` was not created with the `NSURLBookmarkCreationSuitableForBookmarkFile` option.
///
/// If `bookmarkFileURL` points to a directory, the alias file will be created in that directory with its name derived from the information in `bookmarkData`. If `bookmarkFileURL` points to a file, the alias file will be created with the location and name indicated by `bookmarkFileURL`, and its extension will be changed to `.alias` if it is not already.
///
/// - Parameters:
///   - bookmarkData: The bookmark data containing information for the alias file.
///   - bookmarkFileURL: The desired location of the alias file.
///   - options: Options taken into account when creating the alias file.
///   - error: The error that occurred in the case that the alias file cannot be created.
/// - Returns: `YES` if the alias file is successfully created; otherwise, `NO`.
+ (BOOL)writeBookmarkData:(NSData *)bookmarkData toURL:(NSURL *)bookmarkFileURL options:(NSURLBookmarkFileCreationOptions)options error:(NSError **)error API_AVAILABLE(macos(10.6), ios(4.0), watchos(2.0), tvos(9.0));

/// Initializes and returns bookmark data derived from an alias file pointed to by a specified URL.
///
/// This method doesn't check to see if `bookmarkFileURL` points to an alias file. This allows this method to work with any file containing bookmark data. If `bookmarkFileURL` refers to a file which does not contain bookmark data or to a non-file object, such as a directory or symbolic link, this method returns `nil` and produces an error.
///
/// If `bookmarkFileURL` refers to an alias file created prior to OS X v10.6 that contains Alias Manager information but no bookmark data, this method synthesizes bookmark data for the file.
///
/// This method returns `nil` if bookmark data cannot be created.
///
/// - Parameters:
///   - bookmarkFileURL: The URL that points to a file containing bookmark data.
///   - error: The error that occurred in the case that the bookmark data cannot be derived.
/// - Returns: The bookmark data for the alias file.
+ (nullable NSData *)bookmarkDataWithContentsOfURL:(NSURL *)bookmarkFileURL error:(NSError **)error API_AVAILABLE(macos(10.6), ios(4.0), watchos(2.0), tvos(9.0));

/// Returns a new URL made by resolving the alias file at the given URL.
///
/// Creates and initializes a new URL based on the alias file at `url`. Use this method to resolve bookmark data that was saved using ``NSURL/writeBookmarkData(_:to:options:)`` and resolve that data in one step.
///
/// If the `url` argument does not refer to an alias file as defined by the `NSURLIsAliasFileKey` property, this method returns the `url` argument.
///
/// If the `url` argument is unreachable, this method returns `nil` and the optional error argument is populated.
///
/// > Note: The ``NSURL/BookmarkResolutionOptions/withSecurityScope`` option is not supported by this method.
///
/// - Parameters:
///   - url: The URL pointing to the alias file.
///   - options: Options taken into account when resolving the bookmark data.
///   - error: The error that occurred while trying to resolve the provided URL.
/// - Returns: A new URL created by resolving the bookmark data derived from the provided alias file. If an error occurs, this method returns `nil`.
+ (nullable instancetype)URLByResolvingAliasFileAtURL:(NSURL *)url options:(NSURLBookmarkResolutionOptions)options error:(NSError **)error API_AVAILABLE(macos(10.10), ios(8.0), watchos(2.0), tvos(9.0));

/// In an app that has adopted App Sandbox, makes the resource pointed to by a security-scoped URL available to the app.
///
/// When you obtain a security-scoped URL, such as by resolving a security-scoped bookmark, you cannot immediately
/// use the resource it points to. To make the resource available to your app, by way of adding its location to your
/// app's sandbox, call this method on the security-scoped URL.
///
/// If this method returns `YES`, then you must relinquish access as soon as you finish using the resource by calling
/// ``stopAccessingSecurityScopedResource``. You must balance each call to this method with a corresponding call to
/// ``stopAccessingSecurityScopedResource``. When you make the last balanced call, you immediately lose access to the
/// resource in question.
///
/// > Warning: If you fail to relinquish your access to file-system resources when you no longer need them,
/// > your app leaks kernel resources. If sufficient kernel resources leak, your app loses its ability to add
/// > file-system locations to its sandbox until relaunched.
///
/// - Returns: `YES` if the request to access the resource succeeded; otherwise, `NO`.
- (BOOL)startAccessingSecurityScopedResource API_AVAILABLE(macos(10.7), ios(8.0), watchos(2.0), tvos(9.0));

/// In an app that adopts App Sandbox, revokes access to the resource pointed to by a security-scoped URL.
///
/// When you no longer need access to a file or directory pointed to by a security-scoped URL, such as one returned
/// by resolving a security-scoped bookmark, call this method on the URL to relinquish access.
///
/// You must balance each call to ``startAccessingSecurityScopedResource`` with a call to this method. When you make
/// the last balanced call, you immediately lose access to the resource in question.
///
/// If you call this method on a URL whose referenced resource you don't have access to, nothing happens.
///
/// > Warning: If you fail to relinquish your access to file-system resources when you no longer need them,
/// > your app leaks kernel resources. If sufficient kernel resources leak, your app loses its ability to add
/// > file-system locations to its sandbox until relaunched.
- (void)stopAccessingSecurityScopedResource API_AVAILABLE(macos(10.7), ios(8.0), watchos(2.0), tvos(9.0));

#endif 

@end

#if !0

@interface NSURL (NSPromisedItems)

/* Get resource values from URLs of 'promised' items. A promised item is not guaranteed to have its contents in the file system until you use NSFileCoordinator to perform a coordinated read on its URL, which causes the contents to be downloaded or otherwise generated. Promised item URLs are returned by various APIs, including currently:
 - NSMetadataQueryUbiquitousDataScope
 - NSMetadataQueryUbiquitousDocumentsScope
 - An NSFilePresenter presenting the contents of the directory located by -URLForUbiquitousContainerIdentifier: or a subdirectory thereof
 
 The following methods behave identically to their similarly named methods above (-getResourceValue:forKey:error:, etc.), except that they allow you to get resource values and check for presence regardless of whether the promised item's contents currently exist at the URL. You must use these APIs instead of the normal NSURL resource value APIs if and only if any of the following are true:
 - You are using a URL that you know came directly from one of the above APIs
 - You are inside the accessor block of a coordinated read or write that used NSFileCoordinatorReadingImmediatelyAvailableMetadataOnly, NSFileCoordinatorWritingForDeleting, NSFileCoordinatorWritingForMoving, or NSFileCoordinatorWritingContentIndependentMetadataOnly
 
 Most of the NSURL resource value keys will work with these APIs. However, there are some that are tied to the item's contents that will not work, such as NSURLContentAccessDateKey or NSURLGenerationIdentifierKey. If one of these keys is used, the method will return YES, but the value for the key will be nil.
*/
/// Returns the value of the resource property for the specified key from a promised item.
///
/// This method behaves identically to `getResourceValue:forKey:error:`, but works on promised items. A promised item
/// is not guaranteed to have its contents in the file system until you use a file coordinator to perform a coordinated
/// read on its URL, which causes the contents to be downloaded or otherwise generated.
///
/// This method works for any resource value that is not tied to the item's contents. Some keys, like
/// `NSURLContentAccessDateKey` or `NSURLGenerationIdentifierKey`, do not return valid values. If you use one of
/// these keys, the method returns `YES`, but the value returns `nil`.
///
/// - Parameters:
///   - value: The location where the value for the resource property identified by `key` should be stored.
///   - key: The name of one of the URL's resource properties.
///   - error: The error that occurred in the case that the resource value cannot be retrieved.
/// - Returns: `YES` if `value` is successfully populated; otherwise, `NO`.
- (BOOL)getPromisedItemResourceValue:(id _Nullable * _Nonnull)value forKey:(NSURLResourceKey)key error:(NSError **)error API_AVAILABLE(macos(10.10), ios(8.0), watchos(2.0), tvos(9.0));
/// Returns the resource values for the properties identified by specified array of keys from a promised item.
///
/// This method behaves identically to `resourceValuesForKeys:error:`, but works on promised items. A promised item
/// is not guaranteed to have its contents in the file system until you use a file coordinator to perform a coordinated
/// read on its URL, which causes the contents to be downloaded or otherwise generated.
///
/// This method works for any resource value that is not tied to the item's contents. Some keys, like
/// `NSURLContentAccessDateKey` or `NSURLGenerationIdentifierKey`, do not return valid values.
///
/// - Parameters:
///   - keys: An array of names of URL resource properties.
///   - error: The error that occurred in the case that one or more resource values cannot be retrieved.
/// - Returns: A dictionary of resource values indexed by key.
- (nullable NSDictionary<NSURLResourceKey, id> *)promisedItemResourceValuesForKeys:(NSArray<NSURLResourceKey> *)keys error:(NSError **)error API_AVAILABLE(macos(10.10), ios(8.0), watchos(2.0), tvos(9.0));
/// Returns whether the promised item can be reached.
///
/// This method behaves identically to `checkResourceIsReachableAndReturnError:`, but works on promised items.
/// A promised item is not guaranteed to have its contents in the file system until you use a file coordinator
/// to perform a coordinated read on its URL, which causes the contents to be downloaded or otherwise generated.
///
/// - Parameter error: The error that occurred when the promised item could not be reached.
/// - Returns: `YES` if the promised item is reachable; otherwise, `NO`.
- (BOOL)checkPromisedItemIsReachableAndReturnError:(NSError **)error NS_SWIFT_NOTHROW API_AVAILABLE(macos(10.10), ios(8.0), watchos(2.0), tvos(9.0));

@end

#endif 


@interface NSURL (NSItemProvider) <NSItemProviderReading, NSItemProviderWriting>
@end

/// An object representing a single name/value pair for an item in the query portion of a URL.
///
/// In Swift, this object bridges to ``URLQueryItem``; use ``NSURLQueryItem`` when you need reference semantics or other Foundation-specific behavior.
///
/// You use query items with the ``NSURLComponents/queryItems`` property of an ``NSURLComponents`` object.
///
/// > Important:
/// > The Swift overlay to the Foundation framework provides the ``URLQueryItem`` structure, which bridges to the ``NSURLQueryItem`` class. For more information about value types, see <doc://com.apple.documentation/documentation/swift/working-with-foundation-types>.
NS_SWIFT_SENDABLE
API_AVAILABLE(macos(10.10), ios(8.0), watchos(2.0), tvos(9.0))
@interface NSURLQueryItem : NSObject <NSSecureCoding, NSCopying>
/// Initializes a newly allocated query item with the specified name and value.
///
/// To use the newly initialized query item in composing a URL, add it to the ``NSURLComponents/queryItems`` array of an ``NSURLComponents`` instance. Because assigning an array of query items to an ``NSURLComponents`` instance automatically encodes the name and value properties, you should not percent-encode these strings.
///
/// - Parameters:
///   - name: The name of the query item. For example, in the URL `http://www.apple.com/search/?q=iPad`, the `name` parameter is `q`.
///   - value: The value for the query item. For example, in the URL `http://www.apple.com/search/?q=iPad`, the `value` parameter is `iPad`.
/// - Returns: An initialized query item object.
- (instancetype)initWithName:(NSString *)name value:(nullable NSString *)value NS_DESIGNATED_INITIALIZER;
/// Creates a new query item with the specified name and value.
///
/// To use the newly initialized query item in composing a URL, add it to the ``NSURLComponents/queryItems`` array of an ``NSURLComponents`` instance. Because assigning an array of query items to an ``NSURLComponents`` instance automatically encodes the name and value properties, you should not percent-encode these strings.
///
/// - Parameters:
///   - name: The name of the query item. For example, in the URL `http://www.apple.com/search/?q=iPad`, the `name` parameter is `q`.
///   - value: The value for the query item. For example, in the URL `http://www.apple.com/search/?q=iPad`, the `value` parameter is `iPad`.
/// - Returns: A new query item object.
+ (instancetype)queryItemWithName:(NSString *)name value:(nullable NSString *)value;
/// The name of the query item.
///
/// For example, in the URL `http://www.apple.com/search/?q=iPad`, the `name` parameter is `q`.
///
/// This string is not percent-encoded.
@property (readonly) NSString *name;
/// The value for the query item.
///
/// For example, in the URL `http://www.apple.com/search/?q=iPad`, the `value` parameter is `iPad`.
///
/// This string is not percent-encoded.
@property (nullable, readonly) NSString *value;
@end


/// An object that parses URLs into and constructs URLs from their constituent parts.
///
/// In Swift, this object bridges to ``URLComponents``; use ``NSURLComponents`` when you need reference semantics or other Foundation-specific behavior.
///
/// The ``NSURLComponents`` class is a class that is designed to parse URLs based on [RFC 3986](http://www.ietf.org/rfc/rfc3986.txt) and to construct URLs from their constituent parts. Its behavior differs subtly from the ``NSURL`` class, which conforms to older RFCs. However, you can easily obtain an ``NSURL`` object based on the contents of a URL components object or vice versa.
///
/// You create a URL components object in one of three ways: from an ``NSString`` object that contains a URL, from an ``NSURL`` object, or from scratch by using the default initializer. From there, you can modify the URL's individual components and subcomponents by modifying various properties, either in unencoded form or in URL-encoded form. If you set the unencoded property, you can then obtain the encoded equivalent by reading the encoded property value and vice versa.
///
/// > Important:
/// > The Swift overlay to the Foundation framework provides the ``URLComponents`` structure, which bridges to the ``NSURLComponents`` class. For more information about value types, see <doc://com.apple.documentation/documentation/swift/working-with-foundation-types>.
API_AVAILABLE(macos(10.9), ios(7.0), watchos(2.0), tvos(9.0))
@interface NSURLComponents : NSObject <NSCopying>

/// Creates a URL components object with all components left undefined.
- (instancetype)init;

/// Creates a URL components object by parsing the URL from an `NSURL` object.
///
/// - Parameters:
///   - url: The URL to parse.
///   - resolve: Controls whether the URL should be resolved against its base URL before parsing. If `YES`, and if
///     the `url` parameter contains a relative URL, the original URL is resolved against its base URL before parsing
///     by calling the `absoluteURL` method. Otherwise, the string portion is used by itself.
/// - Returns: Returns the initialized URL components object, or `nil` if the URL could not be parsed.
- (nullable instancetype)initWithURL:(NSURL *)url resolvingAgainstBaseURL:(BOOL)resolve;

/// Returns a URL components object by parsing the URL from an `NSURL` object.
///
/// - Parameters:
///   - url: The URL to parse.
///   - resolve: Controls whether the URL should be resolved against its base URL before parsing. If `YES`, and if
///     the `url` parameter contains a relative URL, the original URL is resolved against its base URL before parsing
///     by calling the `absoluteURL` method. Otherwise, the string portion is used by itself.
/// - Returns: Returns the new URL components object, or `nil` if the URL could not be parsed.
+ (nullable instancetype)componentsWithURL:(NSURL *)url resolvingAgainstBaseURL:(BOOL)resolve;

/// Creates a URL components object by parsing a URL in string form.
///
/// - Parameter URLString: The URL string to parse.
/// - Returns: Returns the initialized URL components object, or `nil` if the URL string could not be parsed.
- (nullable instancetype)initWithString:(NSString *)URLString;

/// Returns a URL components object by parsing a URL in string form.
///
/// - Parameter URLString: The URL string to parse.
/// - Returns: Returns the new URL components object, or `nil` if the URL string could not be parsed.
+ (nullable instancetype)componentsWithString:(NSString *)URLString;

/// Initializes an `NSURLComponents` with a URL string and the option to add (or skip) IDNA- and percent-encoding of invalid characters.
/// If `encodingInvalidCharacters` is false, and the URL string is invalid according to RFC 3986, `nil` is returned.
/// If `encodingInvalidCharacters` is true, `NSURLComponents` will try to encode the string to create a valid URL.
/// If the URL string is still invalid after encoding, `nil` is returned.
///
/// - Parameter URLString: The URL string.
/// - Parameter encodingInvalidCharacters: True if `NSURLComponents` should try to encode an invalid URL string, false otherwise.
/// - Returns: An `NSURLComponents` instance for a valid URL, or `nil` if the URL is invalid.
- (nullable instancetype)initWithString:(NSString *)URLString encodingInvalidCharacters:(BOOL)encodingInvalidCharacters API_AVAILABLE(macos(14.0), ios(17.0), watchos(10.0), tvos(17.0));

/// Initializes and returns a newly created `NSURLComponents` with a URL string and the option to add (or skip) IDNA- and percent-encoding of invalid characters.
/// If `encodingInvalidCharacters` is false, and the URL string is invalid according to RFC 3986, `nil` is returned.
/// If `encodingInvalidCharacters` is true, `NSURLComponents` will try to encode the string to create a valid URL.
/// If the URL string is still invalid after encoding, nil is returned.
///
/// - Parameter URLString: The URL string.
/// - Parameter encodingInvalidCharacters: True if `NSURLComponents` should try to encode an invalid URL string, false otherwise.
/// - Returns: An `NSURLComponents` instance for a valid URL, or `nil` if the URL is invalid.
+ (nullable instancetype)componentsWithString:(NSString *)URLString encodingInvalidCharacters:(BOOL)encodingInvalidCharacters API_AVAILABLE(macos(14.0), ios(17.0), watchos(10.0), tvos(17.0));

/// A URL object derived from the components object.
///
/// If the receiver has an authority component (user, password, host, or port) and a path component, then the path
/// must either begin with `"/"` or be an empty string. Otherwise, this property contains `nil`.
///
/// If the receiver does not have an authority component (user, password, host, or port) and has a path component,
/// the path component must not start with `"//"`. If it does, this property contains `nil`.
@property (nullable, readonly, copy) NSURL *URL;

/// Returns a URL object derived from the components object, relative to a base URL.
///
/// If the components object has an authority component (user, password, host, or port) and a path component, then
/// the path must either begin with `"/"` or be an empty string. Otherwise, this method returns `nil`.
///
/// If the components object does not have an authority component (user, password, host, or port) and has a path
/// component, the path component must not start with `"//"`. If it does, this method returns `nil`.
///
/// - Parameter baseURL: If non-`nil`, this URL is used as the base URL portion of the resulting URL object.
- (nullable NSURL *)URLRelativeToURL:(nullable NSURL *)baseURL;

/// A URL derived from the components object, in string form.
///
/// If the receiver has an authority component (user, password, host, or port) and a path component, then the path
/// must either begin with `"/"` or be an empty string. Otherwise, this property contains `nil`.
///
/// If the receiver does not have an authority component (user, password, host, or port) and has a path component,
/// the path component must not start with `"//"`. If it does, this property contains `nil`.
@property (nullable, readonly, copy) NSString *string API_AVAILABLE(macos(10.10), ios(8.0), watchos(2.0), tvos(9.0));

// Warning: IETF STD 66 (rfc3986) says the use of the format "user:password" in the userinfo subcomponent of a URI is deprecated because passing authentication information in clear text has proven to be a security risk. However, there are cases where this practice is still needed, and so the user and password components and methods are provided.

/// The scheme URL component, or `nil` if not present.
///
/// For example, in the URL `http://www.example.com/index.html`, the scheme is `http`.
///
/// Attempting to set the scheme with an invalid scheme string will cause an exception.
@property (nullable, copy) NSString *scheme;

/// The username URL subcomponent, or `nil` if not present.
///
/// For example, in the URL `http://username:password@www.example.com/index.html`, the user is `username`.
///
/// Getting this property removes any percent encoding this component may have. Setting this property assumes the
/// string is not percent encoded and will add percent encoding.
@property (nullable, copy) NSString *user;

/// The password URL subcomponent, or `nil` if not present.
///
/// For example, in the URL `http://username:password@www.example.com/index.html`, the password is `password`.
///
/// Getting this property removes any percent encoding this component may have. Setting this property assumes the
/// string is not percent encoded and will add percent encoding.
@property (nullable, copy) NSString *password;

/// The host URL subcomponent, or `nil` if not present.
///
/// For example, in the URL `http://www.example.com/index.html`, the host is `www.example.com`.
///
/// Getting this property removes any percent encoding this component may have. Setting this property assumes the
/// string is not percent encoded and will add percent encoding.
@property (nullable, copy) NSString *host;

/// The port number URL component, or `nil` if not present.
///
/// For example, in the URL `http://www.example.com:8080/index.php`, the port number is `8080`.
///
/// Attempting to set a negative port number will cause an exception.
@property (nullable, copy) NSNumber *port;

/// The path URL component, or `nil` if not present.
///
/// For example, in the URL `http://www.example.com/index.html`, the path is `/index.html`.
///
/// Getting this property removes any percent encoding this component may have. Setting this property assumes the
/// string is not percent encoded and will add percent encoding.
@property (nullable, copy) NSString *path;

/// The query URL component as a string, or `nil` if not present.
///
/// For example, in the URL `http://www.example.com/index.php?key1=value1&key2=value2`, the query string is
/// `key1=value1&key2=value2`.
///
/// Getting this property removes any percent encoding this component may have. Setting this property assumes the
/// string is not percent encoded and will add percent encoding.
@property (nullable, copy) NSString *query;

/// The fragment URL component (the part after a `#` symbol), or `nil` if not present.
///
/// For example, in the URL `http://www.example.com/index.html#jumpLocation`, the fragment is `jumpLocation`.
///
/// Getting this property removes any percent encoding this component may have. Setting this property assumes the
/// string is not percent encoded and will add percent encoding.
@property (nullable, copy) NSString *fragment;

/// The username URL subcomponent expressed as a URL-encoded string, or `nil` if not present.
///
/// If you set this value to something that is not a valid, percent-encoded string, this class throws an exception.
@property (nullable, copy) NSString *percentEncodedUser;

/// The password URL subcomponent expressed as a URL-encoded string, or `nil` if not present.
///
/// If you set this value to something that is not a valid, percent-encoded string, this class throws an exception.
@property (nullable, copy) NSString *percentEncodedPassword;

/// The host URL subcomponent expressed as a URL-encoded string, or `nil` if not present.
///
/// If you set this value to something that is not a valid, percent-encoded string, this class throws an exception.
@property (nullable, copy) NSString *percentEncodedHost API_DEPRECATED("Use encodedHost instead", macos(10.9, API_TO_BE_DEPRECATED), ios(7.0, API_TO_BE_DEPRECATED), tvos(9.0, API_TO_BE_DEPRECATED), watchos(2.0, API_TO_BE_DEPRECATED));

/// The path URL component expressed as a URL-encoded string, or `nil` if not present.
///
/// If you set this value to something that is not a valid, percent-encoded string, this class throws an exception.
///
/// Although an unencoded semicolon is a valid character in a percent-encoded path, for compatibility with `NSURL`,
/// you should always percent-encode it.
@property (nullable, copy) NSString *percentEncodedPath;

/// The query URL component expressed as a URL-encoded string, or `nil` if not present.
///
/// If you set this value to something that is not a valid, percent-encoded string, this class throws an exception.
@property (nullable, copy) NSString *percentEncodedQuery;

/// The fragment URL component (the part after a `#` symbol) expressed as a URL-encoded string, or `nil` if not
/// present.
///
/// If you set this value to something that is not a valid, percent-encoded string, this class throws an exception.
@property (nullable, copy) NSString *percentEncodedFragment;

/// The host subcomponent, percent-encoded.
///
/// The getter for this property retains any percent-encoding this component may have. Setting this property assumes
/// the component string already has the correct percent-encoding. Attempting to set an incorrectly percent-encoded
/// string raises an exception.
@property (nullable, copy) NSString *encodedHost API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0));

/// Returns the character range of the scheme in the URL string returned by the `string` property.
///
/// If the component does not exist in the `NSURLComponents` object, `{NSNotFound, 0}` is returned.
@property (readonly) NSRange rangeOfScheme API_AVAILABLE(macos(10.11), ios(9.0), watchos(2.0), tvos(9.0));

/// Returns the character range of the user in the URL string returned by the `string` property.
///
/// If the component does not exist in the `NSURLComponents` object, `{NSNotFound, 0}` is returned.
@property (readonly) NSRange rangeOfUser API_AVAILABLE(macos(10.11), ios(9.0), watchos(2.0), tvos(9.0));

/// Returns the character range of the password in the URL string returned by the `string` property.
///
/// If the component does not exist in the `NSURLComponents` object, `{NSNotFound, 0}` is returned.
@property (readonly) NSRange rangeOfPassword API_AVAILABLE(macos(10.11), ios(9.0), watchos(2.0), tvos(9.0));

/// Returns the character range of the host in the URL string returned by the `string` property.
///
/// If the component does not exist in the `NSURLComponents` object, `{NSNotFound, 0}` is returned.
@property (readonly) NSRange rangeOfHost API_AVAILABLE(macos(10.11), ios(9.0), watchos(2.0), tvos(9.0));

/// Returns the character range of the port in the URL string returned by the `string` property.
///
/// If the component does not exist in the `NSURLComponents` object, `{NSNotFound, 0}` is returned.
@property (readonly) NSRange rangeOfPort API_AVAILABLE(macos(10.11), ios(9.0), watchos(2.0), tvos(9.0));

/// Returns the character range of the path in the URL string returned by the `string` property.
///
/// If the component does not exist in the `NSURLComponents` object, `{NSNotFound, 0}` is returned.
@property (readonly) NSRange rangeOfPath API_AVAILABLE(macos(10.11), ios(9.0), watchos(2.0), tvos(9.0));

/// Returns the character range of the query in the URL string returned by the `string` property.
///
/// If the component does not exist in the `NSURLComponents` object, `{NSNotFound, 0}` is returned.
@property (readonly) NSRange rangeOfQuery API_AVAILABLE(macos(10.11), ios(9.0), watchos(2.0), tvos(9.0));

/// Returns the character range of the fragment in the URL string returned by the `string` property.
///
/// If the component does not exist in the `NSURLComponents` object, `{NSNotFound, 0}` is returned.
@property (readonly) NSRange rangeOfFragment API_AVAILABLE(macos(10.11), ios(9.0), watchos(2.0), tvos(9.0));

/// The query URL component as an array of name/value pairs.
///
/// When you get this property's value, the `NSURLComponents` class parses the `query` string and returns an array
/// of `NSURLQueryItem` objects, each of which represents a single key-value pair, in the order in which they appear
/// in the original query string. Because a name may appear more than once in a single query string, the name
/// properties of query items are not guaranteed to be unique. If the `query` property is an empty string, the
/// `queryItems` property is an empty array. If the `query` property is `nil`, the `queryItems` property is also `nil`.
///
/// When you set this property's value, the `NSURLComponents` class joins each name/value pair with a `=` delimiter
/// and joins the array with a `&` delimiter, then sets the `query` property to the resulting string. Setting this
/// property to an empty array sets the `query` property to an empty string. Setting this property to `nil` sets the
/// `query` property to `nil`.
@property (nullable, copy) NSArray<NSURLQueryItem *> *queryItems API_AVAILABLE(macos(10.10), ios(8.0), watchos(2.0), tvos(9.0));

// The percentEncodedQueryItems getter returns an array of NSURLQueryItems in the order in which they appear in the original query string. Any percent-encoding in a NSURLQueryItem name or value is retained.
//
// The percentEncodedQueryItems setter combines an array containing any number of NSURLQueryItems, each of which represents a single key-value pair, into a query string and sets the NSURLComponents query property. This property assumes the NSURLQueryItem names and values are already correctly percent-encoded, and that the NSURLQueryItem names do not contain the query item delimiter characters '&' and '='. Attempting to set an incorrectly percent-encoded NSURLQueryItem or a NSURLQueryItem name with the query item delimiter characters '&' and '=' will cause an exception.
@property (nullable, copy) NSArray<NSURLQueryItem *> *percentEncodedQueryItems API_AVAILABLE(macosx(10.13), ios(11.0), watchos(4.0), tvos(11.0));

@end


@interface NSCharacterSet (NSURLUtilities)
// Predefined character sets for the six URL components and subcomponents which allow percent encoding. These character sets are passed to -stringByAddingPercentEncodingWithAllowedCharacters:.

/// Returns the character set for characters allowed in a user URL subcomponent.
///
/// The user component of a URL is an optional component that precedes the host component, and ends at either a colon (if a password is specified) or an `@` sign (if no password is specified). For example, in the URL `http://username:password@www.example.com/index.html`, the user component is `username`.
@property (class, readonly, copy) NSCharacterSet *URLUserAllowedCharacterSet API_AVAILABLE(macos(10.9), ios(7.0), watchos(2.0), tvos(9.0));

/// Returns the character set for characters allowed in a password URL subcomponent.
///
/// The password component of a URL is the component immediately following the colon after the username component of the URL, and ends at the `@` sign. For example, in the URL `http://username:password@www.example.com/index.html`, the password component is `password`.
@property (class, readonly, copy) NSCharacterSet *URLPasswordAllowedCharacterSet API_AVAILABLE(macos(10.9), ios(7.0), watchos(2.0), tvos(9.0));

/// Returns the character set for characters allowed in a host URL subcomponent.
///
/// The host component of a URL is usually the component immediately after the first two leading slashes. If the URL contains a username and password, the host component is the component after the `@` sign. For example, in the URL `http://username:password@www.example.com/index.html`, the host component is `www.example.com`.
@property (class, readonly, copy) NSCharacterSet *URLHostAllowedCharacterSet API_AVAILABLE(macos(10.9), ios(7.0), watchos(2.0), tvos(9.0));

/// Returns the character set for characters allowed in a path URL component.
///
/// The path component of a URL is the component immediately following the host component (if present). It ends wherever the query or fragment component begins. For example, in the URL `http://www.example.com/index.php?key1=value1`, the path component is `/index.php`.
@property (class, readonly, copy) NSCharacterSet *URLPathAllowedCharacterSet API_AVAILABLE(macos(10.9), ios(7.0), watchos(2.0), tvos(9.0));

/// Returns the character set for characters allowed in a query URL component.
///
/// The query component of a URL is the component immediately following a question mark (`?`). For example, in the URL `http://www.example.com/index.php?key1=value1#jumpLink`, the query component is `key1=value1`.
@property (class, readonly, copy) NSCharacterSet *URLQueryAllowedCharacterSet API_AVAILABLE(macos(10.9), ios(7.0), watchos(2.0), tvos(9.0));

/// Returns the character set for characters allowed in a fragment URL component.
///
/// The fragment component of a URL is the component after a `#` symbol. For example, in the URL `http://www.example.com/index.html#jumpLocation`, the fragment is `jumpLocation`.
@property (class, readonly, copy) NSCharacterSet *URLFragmentAllowedCharacterSet API_AVAILABLE(macos(10.9), ios(7.0), watchos(2.0), tvos(9.0));

@end


@interface NSString (NSURLUtilities)

/// Returns a new string made from the receiver by replacing all characters not in the specified set with percent-encoded characters.
///
/// Entire URL strings cannot be percent-encoded, because each URL component specifies a different set of allowed characters. For example, the query component of a URL allows the `@` character, but that character must be percent-encoded in the password component.
///
/// UTF-8 encoding is used to determine the correct percent-encoded characters. Any characters in `allowedCharacters` outside of the 7-bit ASCII range are ignored.
///
/// > Important: You must not call this method on strings that are already percent-encoded. Calling this method on strings that are already percent-encoded will cause percent characters in a percent-encoded sequence to be percent-encoded twice.
///
/// - Parameter allowedCharacters: The characters not replaced in the string. Typically, you specify one of the predefined character sets for a particular URL component, such as ``NSCharacterSet/urlPathAllowed`` or ``NSCharacterSet/urlQueryAllowed``.
/// - Returns: The encoded string, or `nil` if the transformation is not possible.
- (nullable NSString *)stringByAddingPercentEncodingWithAllowedCharacters:(NSCharacterSet *)allowedCharacters API_AVAILABLE(macos(10.9), ios(7.0), watchos(2.0), tvos(9.0));

/// A new string made from the receiver by replacing all percent-encoded sequences with the matching UTF-8 characters.
///
/// Returns `nil` if the receiver contains an invalid percent-encoding sequence.
///
/// > Important: Call this method only on strings that you know to be percent-encoded. Calling it on strings that are not percent-encoded can lead to misinterpreting a percent character as the beginning of a percent-encoded sequence.
@property (nullable, readonly, copy) NSString *stringByRemovingPercentEncoding API_AVAILABLE(macos(10.9), ios(7.0), watchos(2.0), tvos(9.0));


/// Returns a representation of the receiver using a given encoding to determine the percent escapes necessary to convert the receiver into a legal URL string.
///
/// @DeprecationSummary {
///     Use ``NSString/addingPercentEncoding(withAllowedCharacters:)`` instead.
/// }
///
/// - Parameter enc: The encoding to use for the returned string. If you are uncertain of the correct encoding you should use `NSUTF8StringEncoding`.
/// - Returns: A representation of the receiver using `enc` to determine the percent escapes necessary to convert the receiver into a legal URL string. Returns `nil` if `enc` cannot encode a particular character.
- (nullable NSString *)stringByAddingPercentEscapesUsingEncoding:(NSStringEncoding)enc API_DEPRECATED("Use -stringByAddingPercentEncodingWithAllowedCharacters: instead, which always uses the recommended UTF-8 encoding, and which encodes for a specific URL component or subcomponent since each URL component or subcomponent has different rules for what characters are valid.", macos(10.0,10.11), ios(2.0,9.0), watchos(2.0,2.0), tvos(9.0,9.0));
/// Returns a new string made by replacing in the receiver all percent escapes with the matching characters as determined by a given encoding.
///
/// @DeprecationSummary {
///     Use ``NSString/removingPercentEncoding`` instead.
/// }
///
/// - Parameter enc: The encoding to use for the returned string.
/// - Returns: A new string made by replacing in the receiver all percent escapes with the matching characters as determined by `enc`. Returns `nil` if the transformation is not possible, for example, the percent escapes give a byte sequence not legal in `enc`.
- (nullable NSString *)stringByReplacingPercentEscapesUsingEncoding:(NSStringEncoding)enc API_DEPRECATED("Use -stringByRemovingPercentEncoding instead, which always uses the recommended UTF-8 encoding.", macos(10.0,10.11), ios(2.0,9.0), watchos(2.0,2.0), tvos(9.0,9.0));

@end


@interface NSURL (NSURLPathUtilities)
    
/// Initializes and returns a newly created `NSURL` object as a file URL with specified path components.
///
/// The path components are separated by a forward slash in the returned URL.
///
/// - Parameter components: An array of path components.
/// - Returns: An `NSURL` object initialized with `components`.
+ (nullable NSURL *)fileURLWithPathComponents:(NSArray<NSString *> *)components API_AVAILABLE(macos(10.6), ios(4.0), watchos(2.0), tvos(9.0));
/// An array containing the path components.
///
/// Each component is unescaped. For example, in the URL `file:///directory/directory%202/file`, the path components array would be `@[@"/", @"directory", @"directory 2", @"file"]`.
@property (nullable, readonly, copy) NSArray<NSString *> *pathComponents API_AVAILABLE(macos(10.6), ios(4.0), watchos(2.0), tvos(9.0));
/// The last path component.
///
/// This property contains the last path component, unescaped. For example, in the URL `file:///path/to/file`, the last path component is `file`.
@property (nullable, readonly, copy) NSString *lastPathComponent API_AVAILABLE(macos(10.6), ios(4.0), watchos(2.0), tvos(9.0));
/// The path extension.
///
/// This property contains the path extension, unescaped. For example, in the URL `file:///path/to/file.txt`, the path extension is `txt`.
@property (nullable, readonly, copy) NSString *pathExtension API_AVAILABLE(macos(10.6), ios(4.0), watchos(2.0), tvos(9.0));

/// Returns a new URL by appending a path component to the original URL.
///
/// If the original URL does not end with a forward slash and `pathComponent` does not begin with a forward slash,
/// a forward slash is inserted between the two parts of the returned URL, unless the original URL is the empty string.
///
/// If the receiver is a file URL and `pathComponent` does not end with a trailing slash, this method may read file
/// metadata to determine whether the resulting path is a directory. This is done synchronously, and may have
/// significant performance costs if the receiver is a location on a network mounted filesystem. You can instead use
/// ``URLByAppendingPathComponent:isDirectory:`` if you know whether the resulting path is a directory to avoid
/// this file metadata operation.
///
/// - Parameter pathComponent: The path component to add to the URL, in its original form (not URL encoded).
/// - Returns: A new URL with `pathComponent` appended.
- (nullable NSURL *)URLByAppendingPathComponent:(NSString *)pathComponent API_AVAILABLE(macos(10.6), ios(4.0), watchos(2.0), tvos(9.0));
/// Returns a new URL by appending a path component to the original URL, along with a trailing slash if the component is a directory.
///
/// If the original URL does not end with a forward slash and `pathComponent` does not begin with a forward slash,
/// a forward slash is inserted between the two parts of the returned URL, unless the original URL is the empty string.
///
/// - Parameters:
///   - pathComponent: The path component to add to the URL.
///   - isDirectory: If `YES`, a trailing slash is appended after `pathComponent`.
/// - Returns: A new URL with `pathComponent` appended.
- (nullable NSURL *)URLByAppendingPathComponent:(NSString *)pathComponent isDirectory:(BOOL)isDirectory API_AVAILABLE(macos(10.7), ios(5.0), watchos(2.0), tvos(9.0));
/// A URL you create by removing the last path component from the receiver.
///
/// If the URL represents the root path, this property contains a copy of the original URL. Otherwise, if the original URL has only one path component, this property contains the empty string.
@property (nullable, readonly, copy) NSURL *URLByDeletingLastPathComponent API_AVAILABLE(macos(10.6), ios(4.0), watchos(2.0), tvos(9.0));
/// Returns a new URL by appending a path extension to the original URL.
///
/// If the original URL ends with one or more forward slashes, these are removed from the returned URL.
/// A period is inserted between the two parts of the new URL.
///
/// - Parameter pathExtension: The path extension to add to the URL.
/// - Returns: A new URL with `pathExtension` appended.
- (nullable NSURL *)URLByAppendingPathExtension:(NSString *)pathExtension API_AVAILABLE(macos(10.6), ios(4.0), watchos(2.0), tvos(9.0));
/// A URL you create by removing the path extension from the receiver, if any.
///
/// If the URL represents the root path, this property contains a copy of the original URL. If the URL has multiple path extensions, only the last one is removed.
@property (nullable, readonly, copy) NSURL *URLByDeletingPathExtension API_AVAILABLE(macos(10.6), ios(4.0), watchos(2.0), tvos(9.0));

/* The following methods work only on `file:` scheme URLs; for non-`file:` scheme URLs, these methods return the URL unchanged.
 */
#if !0
/// Returns whether the resource pointed to by a file URL can be reached.
///
/// This method synchronously checks if the file at the provided URL is reachable. Checking reachability is
/// appropriate when making decisions that do not require other immediate operations on the resource, such as
/// periodic maintenance of user interface state that depends on the existence of a specific document.
///
/// If your app must perform operations on the file, such as opening it or copying resource properties, it is
/// more efficient to attempt the operation and handle any failure that may occur.
///
/// This method is currently applicable only to URLs for file system resources. For other URL types, `NO` is returned.
///
/// - Parameter error: The error that occurred when the resource could not be reached.
/// - Returns: `YES` if the resource is reachable; otherwise, `NO`.
- (BOOL)checkResourceIsReachableAndReturnError:(NSError **)error NS_SWIFT_NOTHROW API_AVAILABLE(macos(10.6), ios(4.0), watchos(2.0), tvos(9.0));
/// A URL that points to the same resource as the original URL using an absolute path.
///
/// This property only works on URLs with the `file:` path scheme. For all other URLs, it returns a copy of the original URL. Like ``NSString/standardizingPath``, this property expands an initial tilde expression, reduces empty components and "`/./`" sequences, and resolves "`..`" references in absolute paths. The resulting path may still contain symbolic links.
@property (nullable, readonly, copy) NSURL *URLByStandardizingPath API_AVAILABLE(macos(10.6), ios(4.0), watchos(2.0), tvos(9.0));
/// A URL that points to the same resource as the receiver and includes no symbolic links.
///
/// If the receiver has no symbolic links, this property contains a copy of the original URL. If some symbolic links cannot be resolved, they are left in place. This property only works on URLs with the `file:` path scheme. For all other URLs, it returns a copy of the receiver.
@property (nullable, readonly, copy) NSURL *URLByResolvingSymlinksInPath API_AVAILABLE(macos(10.6), ios(4.0), watchos(2.0), tvos(9.0));
#endif 

@end


#if (TARGET_OS_MAC && !0) || TARGET_OS_IPHONE
/// A stub class that encapsulates security information about a file.
///
/// ``NSFileSecurity`` contains no methods of its own. Instead, it is transparently bridged to <doc://com.apple.documentation/documentation/corefoundation/cffilesecurity>.
API_AVAILABLE(macos(10.7), ios(5.0), watchos(2.0), tvos(9.0))
@interface NSFileSecurity : NSObject <NSCopying, NSSecureCoding>
- (nullable instancetype) initWithCoder:(NSCoder *)coder NS_DESIGNATED_INITIALIZER;
@end
#endif


/* deprecated interfaces
 */

#if TARGET_OS_OSX
/* NSURLClient and NSURLLoading are deprecated; use NSURLConnection instead.
 */

/* Client informal protocol for use with the deprecated loadResourceDataNotifyingClient: below.
 */
#if !defined(SWIFT_CLASS_EXTRA)
@interface NSObject (NSURLClient)
- (void)URL:(NSURL *)sender resourceDataDidBecomeAvailable:(NSData *)newBytes API_DEPRECATED("Use NSURLConnection instead", macos(10.0,10.4), ios(2.0,2.0), watchos(2.0,2.0), tvos(9.0,9.0));
- (void)URLResourceDidFinishLoading:(NSURL *)sender API_DEPRECATED("Use NSURLConnection instead", macos(10.0,10.4), ios(2.0,2.0), watchos(2.0,2.0), tvos(9.0,9.0));
- (void)URLResourceDidCancelLoading:(NSURL *)sender API_DEPRECATED("Use NSURLConnection instead", macos(10.0,10.4), ios(2.0,2.0), watchos(2.0,2.0), tvos(9.0,9.0));
- (void)URL:(NSURL *)sender resourceDidFailLoadingWithReason:(NSString *)reason API_DEPRECATED("Use NSURLConnection instead", macos(10.0,10.4), ios(2.0,2.0), watchos(2.0,2.0), tvos(9.0,9.0));
@end
#endif

@interface NSURL (NSURLLoading)
/// Returns the receiver's resource data, loading it if necessary.
///
/// If the receiver has not already loaded its resource data, it will attempt to load it as a blocking operation.
///
/// @deprecated Use `NSURLSession` or `NSURLConnection` for loading content from remote URLs.
///
/// - Parameter shouldUseCache: Whether the URL should use cached resource data. If `YES`, the cache is consulted.
///   If `NO`, the data is always loaded directly.
/// - Returns: The receiver's resource data.
- (nullable NSData *)resourceDataUsingCache:(BOOL)shouldUseCache API_DEPRECATED("Use NSURLConnection instead", macos(10.0,10.4), ios(2.0,2.0), watchos(2.0,2.0), tvos(9.0,9.0));
/// Loads the receiver's resource data in the background.
///
/// A given NSURL object can perform only one background load at a time.
///
/// @deprecated Use `NSURLSession` or `NSURLConnection` for loading content from remote URLs.
///
/// - Parameters:
///   - client: The client of the loading operation, notified of progress using the `NSURLClient` informal protocol.
///   - shouldUseCache: Whether the URL should use cached resource data. If `YES`, the cache is consulted.
///     If `NO`, the data is always loaded directly.
- (void)loadResourceDataNotifyingClient:(id)client usingCache:(BOOL)shouldUseCache API_DEPRECATED("Use NSURLConnection instead", macos(10.0,10.4), ios(2.0,2.0), watchos(2.0,2.0), tvos(9.0,9.0));
/// Returns the specified property of the receiver's resource.
///
/// @deprecated Use `NSURLSession` or `NSURLConnection` instead.
///
/// - Parameter propertyKey: The key of the desired property.
/// - Returns: The value of the property, or `nil` if there is no such key.
- (nullable id)propertyForKey:(NSString *)propertyKey API_DEPRECATED("Use NSURLConnection instead", macos(10.0,10.4), ios(2.0,2.0), watchos(2.0,2.0), tvos(9.0,9.0));

/// Attempts to set the resource data for the receiver.
///
/// In the case of a file URL, setting the data involves writing `data` to the specified file.
///
/// @deprecated Use `NSURLSession` or `NSURLConnection` instead.
///
/// - Parameter data: The data to set for the URL.
/// - Returns: `YES` if successful, `NO` otherwise.
- (BOOL)setResourceData:(NSData *)data API_DEPRECATED("Use NSURLConnection instead", macos(10.0,10.4), ios(2.0,2.0), watchos(2.0,2.0), tvos(9.0,9.0));
/// Changes the specified property of the receiver's resource.
///
/// @deprecated Use `NSURLSession` or `NSURLConnection` instead.
///
/// - Parameters:
///   - property: The new value of the property.
///   - propertyKey: The key of the desired property.
/// - Returns: `YES` if the modification was successful, `NO` otherwise.
- (BOOL)setProperty:(id)property forKey:(NSString *)propertyKey API_DEPRECATED("Use NSURLConnection instead", macos(10.0,10.4), ios(2.0,2.0), watchos(2.0,2.0), tvos(9.0,9.0));

/// Returns a URL handle to service the receiver.
///
/// Sophisticated clients use the URL handle directly for additional control.
///
/// @deprecated Use `NSURLSession` or `NSURLConnection` for loading content from remote URLs.
///
/// - Parameter shouldUseCache: Whether to use a cached URL handle. If `YES`, the cache is searched for a URL handle
///   that has serviced the receiver or another identical URL. If `NO`, a newly instantiated handle is returned.
/// - Returns: A URL handle to service the receiver.
- (nullable NSURLHandle *)URLHandleUsingCache:(BOOL)shouldUseCache API_DEPRECATED("Use NSURLConnection instead", macos(10.0,10.4), ios(2.0,2.0), watchos(2.0,2.0), tvos(9.0,9.0));
@end
#endif

NS_HEADER_AUDIT_END(nullability, sendability)
