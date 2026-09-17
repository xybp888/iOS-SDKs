/*	NSFileManager.h
	Copyright (c) 1994-2019, Apple Inc. All rights reserved.
*/

#import <Foundation/NSObject.h>
#import <Foundation/NSEnumerator.h>
#import <Foundation/NSDictionary.h>
#import <Foundation/NSPathUtilities.h>
#import <Foundation/NSNotification.h>
#import <Foundation/NSError.h>
#import <Foundation/NSURL.h>
#import <CoreFoundation/CFBase.h>
#import <dispatch/dispatch.h>

@class NSArray<ObjectType>, NSData, NSDate, NSDirectoryEnumerator<ObjectType>, NSError, NSNumber, NSFileProviderService, NSXPCConnection, NSLock, NSFileVersion;
@protocol NSFileManagerDelegate;

/// Keys in dictionaries used to get and set file attributes.
///
/// These keys are used with the methods listed in the Getting and Setting Attributes topic of ``FileManager``.
typedef NSString * NSFileAttributeKey NS_TYPED_EXTENSIBLE_ENUM;
/// Values representing a file's type attribute.
///
/// These strings are the possible values for the ``FileAttributeKey/type`` attribute key contained in the dictionary object returned by ``FileManager/attributesOfItem(atPath:)``.
typedef NSString * NSFileAttributeType NS_TYPED_ENUM;
/// Protection level values that can be associated with a file attribute key.
///
/// These values are associated with the ``FileAttributeKey/protectionKey`` key.
typedef NSString * NSFileProtectionType NS_TYPED_ENUM;

/// The name used to identify a File Provider service.
///
/// ## Discussion
///
/// The team providing the protocol also defines the name. To create a new service's name:
///
/// - Use reverse domain name notation for the interfaces name (for example, `com.example.MyInterface`).
/// - (Optional) Incorporate versioning by appending a version number to the end of the name (`com.example.MyInterface.v2`).
///
/// For more information on defining a service's protocol, see <doc:NSFileProviderService#Defining-the-Service’s-Protocol>.
typedef NSString * NSFileProviderServiceName NS_TYPED_EXTENSIBLE_ENUM;

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

/* Version number where NSFileManager can copy/move/enumerate resources forks correctly. 
*/
#define NSFoundationVersionWithFileManagerResourceForkSupport 412

/// Options for enumerating mounted volumes with the ``FileManager/mountedVolumeURLs(includingResourceValuesForKeys:options:)`` method.
typedef NS_OPTIONS(NSUInteger, NSVolumeEnumerationOptions) {
    /// The enumeration skips hidden volumes.
    NSVolumeEnumerationSkipHiddenVolumes = 1UL << 1,

    /// The enumeration produces file reference URLs rather than path-based URLs.
    NSVolumeEnumerationProduceFileReferenceURLs = 1UL << 2
} API_AVAILABLE(macos(10.6), ios(4.0), watchos(2.0), tvos(9.0));

/// Options for enumerating the contents of directories.
///
/// These options are used with the ``FileManager/contentsOfDirectory(at:includingPropertiesForKeys:options:)`` method.
typedef NS_OPTIONS(NSUInteger, NSDirectoryEnumerationOptions) {
    /// An option to perform a shallow enumeration that doesn't descend into directories.
    NSDirectoryEnumerationSkipsSubdirectoryDescendants = 1UL << 0,

    /// An option to treat packages like files and not descend into their contents.
    NSDirectoryEnumerationSkipsPackageDescendants      = 1UL << 1,

    /// An option to skip hidden files.
    NSDirectoryEnumerationSkipsHiddenFiles             = 1UL << 2,

    /* NSDirectoryEnumerationIncludesDirectoriesPostOrder causes the NSDirectoryEnumerator to enumerate each directory a second time after all of its contained files have been enumerated. Use NSDirectoryEnumerator.isEnumeratingDirectoryPostOrder to differentiate a post-order enumerated directory from a pre-order one.
     */
    NSDirectoryEnumerationIncludesDirectoriesPostOrder API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0)) = 1UL << 3,

    /* NSDirectoryEnumerationProducesRelativePathURLs causes the NSDirectoryEnumerator to always produce file path URLs relative to the directoryURL. This can reduce the size of each URL object returned during enumeration.
     */
    NSDirectoryEnumerationProducesRelativePathURLs API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0)) = 1UL << 4,
} API_AVAILABLE(macos(10.6), ios(4.0), watchos(2.0), tvos(9.0));

/// Options for specifying the behavior of file replacement operations.
///
/// These options are used by ``FileManager/replaceItem(at:withItemAt:backupItemName:options:resultingItemURL:)``.
typedef NS_OPTIONS(NSUInteger, NSFileManagerItemReplacementOptions) {
    /// Only metadata from the new item is used, and metadata from the original item isn't preserved (default).
    NSFileManagerItemReplacementUsingNewMetadataOnly = 1UL << 0,

    /// The backup item remains in place after a successful replacement.
     NSFileManagerItemReplacementWithoutDeletingBackupItem = 1UL << 1
} API_AVAILABLE(macos(10.6), ios(4.0), watchos(2.0), tvos(9.0));

/// Constants indicating the relationship between a directory and an item.
typedef NS_ENUM(NSInteger, NSURLRelationship) {
    /// The directory contains the specified item.
    NSURLRelationshipContains,
    /// The directory and the item are the same. This relationship occurs when the value of the `NSURLFileResourceIdentifierKey` is the same for the directory and item.
    NSURLRelationshipSame,
    /// The directory does not contain the item and is not the same as the item.
    NSURLRelationshipOther
} API_AVAILABLE(macos(10.10), ios(8.0), watchos(2.0), tvos(9.0));

/// Options that specify the behavior of an unmount operation.
/* NSFileManagerUnmountOptions to pass to unmountVolumeAtURL:options:completionHandler: */
typedef NS_OPTIONS(NSUInteger, NSFileManagerUnmountOptions) {
    /// Specifies that all partitions on an unmountable disk should be unmounted.
    ///
    /// If the volume is on a partitioned disk, this option unmounts all volumes on that disk. Then, then the disk is ejected (if it is ejectable).
    NSFileManagerUnmountAllPartitionsAndEjectDisk = 1UL << 0,

    /// Specifies that no UI should accompany the unmount operation.
    ///
    /// If this option is not specified when calling `unmountVolumeAtURL:options:completionHandler:`, any needed UI will delay completion of the completion handler.
    NSFileManagerUnmountWithoutUI = 1UL << 1,
} API_AVAILABLE(macos(10.11)) API_UNAVAILABLE(ios, watchos, tvos);

/// The process identifier of the process that prevented a volume from unmounting.
///
/// If ``unmountVolume(at:options:completionHandler:)`` fails, the process identifier of the dissenter can be found in the `NSError`'s `userInfo` dictionary with this key. The value is an `NSNumber` containing the process identifier.
FOUNDATION_EXPORT NSString *const NSFileManagerUnmountDissentingProcessIdentifierErrorKey API_AVAILABLE(macos(10.11)) API_UNAVAILABLE(ios, watchos, tvos);

/// Sent after the iCloud ("ubiquity") identity has changed.
///
/// The system generates this notification when the user logs into or out of an iCloud account or enables or disables the syncing of documents and data. When your app receives this notification, get the new token from the `ubiquityIdentityToken` property. The value of that token is `nil` if the user disabled iCloud or logged out. There is no `userInfo` dictionary.
extern NSNotificationName const NSUbiquityIdentityDidChangeNotification API_AVAILABLE(macos(10.8), ios(6.0), watchos(2.0), tvos(9.0));

/// A convenient interface to the contents of the file system, and the primary means of interacting with it.
///
/// A file manager object lets you examine the contents of the file system and make changes to it. The ``FileManager`` class provides convenient access to a shared file manager object that is suitable for most types of file-related manipulations. A file manager object is typically your primary mode of interaction with the file system. You use it to locate, create, copy, and move files and directories. You also use it to get information about a file or directory or change some of its attributes.
///
/// When specifying the location of files, you can use either ``NSURL`` or ``NSString`` objects. The use of the ``NSURL`` class is generally preferred for specifying file-system items because URLs can convert path information to a more efficient representation internally. You can also obtain a bookmark from an ``NSURL`` object, which is similar to an alias and offers a more sure way of locating the file or directory later.
///
/// If you are moving, copying, linking, or removing files or directories, you can use a delegate in conjunction with a file manager object to manage those operations. The delegate's role is to affirm the operation and to decide whether to proceed when errors occur. In macOS 10.7 and later, the delegate must conform to the ``FileManagerDelegate`` protocol.
///
/// In iOS 5.0 and later and in macOS 10.7 and later, ``FileManager`` includes methods for managing items stored in iCloud. Files and directories tagged for cloud storage are synced to iCloud so that they can be made available to the user's iOS devices and Macintosh computers. Changes to an item in one location are propagated to all other locations to ensure the items stay in sync.
///
/// ### Threading considerations
///
/// The methods of the shared ``FileManager`` object can be called from multiple threads safely. However, if you use a delegate to receive notifications about the status of move, copy, remove, and link operations, you should create a unique instance of the file manager object, assign your delegate to that object, and use that file manager to initiate your operations.
@interface NSFileManager : NSObject

/// The shared file manager object for the process.
///
/// This method always represents the same file manager object. If you plan to use a delegate with the file manager to receive notifications about the completion of file-based operations, you should create a new instance of ``FileManager`` rather than using the shared object.
@property (class, readonly, strong) NSFileManager *defaultManager;

/// Returns an array of URLs that identify the mounted volumes available on the device.
///
/// - Parameters:
///   - propertyKeys: An array of keys that identify the file properties that you want pre-fetched for each volume. For each returned URL, the values for these keys are cached in the corresponding ``NSURL`` objects. You may specify `nil` for this parameter. For a list of keys you can specify, see Common File System Resource Keys.
///   - options: Option flags for the enumeration. For a list of possible values, see ``FileManager/VolumeEnumerationOptions``.
/// - Returns: An array of `NSURL` objects identifying the mounted volumes.
///   > Important:
///   > This method returns `nil` on platforms other than macOS.
///
/// This call may block if I/O is required to determine values for the requested `propertyKeys`.
- (nullable NSArray<NSURL *> *)mountedVolumeURLsIncludingResourceValuesForKeys:(nullable NSArray<NSURLResourceKey> *)propertyKeys options:(NSVolumeEnumerationOptions)options API_AVAILABLE(macos(10.6), ios(4.0), watchos(2.0), tvos(9.0));

/// Starts the process of unmounting the specified volume.
///
/// - Parameters:
///   - url: A file URL specifying the volume to be unmounted.
///   - mask: A bitmask of ``FileManager/UnmountOptions`` that you can use to customize the unmount operation’s behavior.
///   - completionHandler: A block executed when the unmount operation completes. The block receives an error parameter which is `nil` if unmounting was successful. Otherwise, it indicates why unmounting failed.
///
/// If the volume is encrypted, it is relocked after being unmounted.
- (void)unmountVolumeAtURL:(NSURL *)url options:(NSFileManagerUnmountOptions)mask completionHandler:(void (NS_SWIFT_SENDABLE ^)(NSError * _Nullable errorOrNil))completionHandler API_AVAILABLE(macos(10.11)) API_UNAVAILABLE(ios, watchos, tvos);

/// Performs a shallow search of the specified directory and returns URLs for the contained items.
///
/// - Parameters:
///   - url: The URL for the directory whose contents you want to enumerate.
///   - keys: An array of keys that identify the file properties that you want pre-fetched for each item in the directory. For each returned URL, the specified properties are fetched and cached in the ``NSURL`` object. For a list of keys you can specify, see Common File System Resource Keys. If you want directory contents to have no pre-fetched file properties, pass an empty array to this parameter. If you want directory contents to have default set of pre-fetched file properties, pass `nil` to this parameter.
///   - mask: Options for the enumeration. Because this method performs only shallow enumerations, options that prevent descending into subdirectories or packages are not allowed; the only supported option is ``FileManager/DirectoryEnumerationOptions/skipsHiddenFiles``.
///   - error: On input, a pointer to an error object. If an error occurs, this pointer is set to an actual error object containing the error information. You may specify `nil` for this parameter if you do not want the error information.
/// - Returns: An array of ``NSURL`` objects, each of which identifies a file, directory, or symbolic link contained in `url`. If the directory contains no entries, this method returns an empty array. When using Objective-C, if an error occurs, this method returns `nil` and assigns an appropriate error object to the `error` parameter.
///
/// This method performs a shallow search of the directory and therefore does not traverse symbolic links or return the contents of any subdirectories. This method also does not return URLs for the current directory ("`.`"), parent directory ("`..`"), or resource forks (files that begin with "`._`") but it does return other hidden files. If you need to perform a deep enumeration, use the ``NSFileManager/enumeratorAtURL:includingPropertiesForKeys:options:errorHandler:`` method instead.
///
/// The order of the files in the returned array is undefined.
- (nullable NSArray<NSURL *> *)contentsOfDirectoryAtURL:(NSURL *)url includingPropertiesForKeys:(nullable NSArray<NSURLResourceKey> *)keys options:(NSDirectoryEnumerationOptions)mask error:(NSError **)error API_AVAILABLE(macos(10.6), ios(4.0), watchos(2.0), tvos(9.0));


/// Returns an array of URLs for the specified common directory in the requested domains.
///
/// - Parameters:
///   - directory: The search path directory. The supported values are described in ``FileManager/SearchPathDirectory``.
///   - domainMask: The file system domain to search. The value for this parameter is one or more of the constants described in ``FileManager/SearchPathDomainMask``.
/// - Returns: An array of ``NSURL`` objects identifying the requested directories. The directories are ordered according to the order of the domain mask constants, with items in the user domain first and items in the system domain last.
///
/// This method is intended to locate known and common directories in the system. For example, setting the directory to ``FileManager/SearchPathDirectory/applicationDirectory``, will return the Applications directories in the requested domain. There are a number of common directories available in the ``FileManager/SearchPathDirectory``, including: ``FileManager/SearchPathDirectory/desktopDirectory``, ``FileManager/SearchPathDirectory/applicationSupportDirectory``, and many more.
- (NSArray<NSURL *> *)URLsForDirectory:(NSSearchPathDirectory)directory inDomains:(NSSearchPathDomainMask)domainMask API_AVAILABLE(macos(10.6), ios(4.0), watchos(2.0), tvos(9.0));

/// Locates and optionally creates the specified common directory in a domain.
///
/// - Parameters:
///   - directory: The search path directory. The supported values are described in ``FileManager/SearchPathDirectory``.
///   - domain: The file system domain to search. The value for this parameter is one of the constants described in ``FileManager/SearchPathDomainMask``. You should specify only one domain for your search and you may not specify the ``FileManager/SearchPathDomainMask/allDomainsMask`` constant for this parameter.
///   - url: The file URL used to determine the location of the returned URL. Only the volume of this parameter is used. This parameter is ignored unless the `directory` parameter contains the value ``FileManager/SearchPathDirectory/itemReplacementDirectory`` and the `domain` parameter contains the value ``FileManager/SearchPathDomainMask/userDomainMask``.
///   - shouldCreate: Whether to create the directory if it does not already exist. When creating a temporary directory, this parameter is ignored and the directory is always created.
///   - error: On input, a pointer to an error object. If an error occurs, this pointer is set to an actual error object containing the error information. You may specify `nil` for this parameter if you do not want the error information.
/// - Returns: The ``NSURL`` for the requested directory. When using Objective-C, if an error occurs, this method returns `nil` and assigns an appropriate error object to the `error` parameter.
///
/// You typically use this method to locate one of the standard system directories, such as the `Documents`, `Application Support` or `Caches` directories. After locating (or creating) the desired directory, this method returns the URL for that directory. If more than one appropriate directory exists in the specified domain, this method returns only the first one it finds.
///
/// > Important:
/// > Passing a directory and domain pair that makes no sense (for example ``FileManager/SearchPathDirectory/desktopDirectory`` and ``FileManager/SearchPathDomainMask/networkDomainMask``) raises an exception.
///
/// You can use this method to create a new temporary directory. To do so, specify ``FileManager/SearchPathDirectory/itemReplacementDirectory`` for the `directory` parameter, ``FileManager/SearchPathDomainMask/userDomainMask`` for the `domain` parameter, and a URL for the `url` parameter which determines the volume of the returned URL.
///
/// > Important:
/// > If you use this method to create a temporary directory, you should not rely on the existence of that temporary directory after the app is exited. It is recommended that you remove any temporary directories that are created after they're no longer needed.
- (nullable NSURL *)URLForDirectory:(NSSearchPathDirectory)directory inDomain:(NSSearchPathDomainMask)domain appropriateForURL:(nullable NSURL *)url create:(BOOL)shouldCreate error:(NSError **)error API_AVAILABLE(macos(10.6), ios(4.0), watchos(2.0), tvos(9.0));

/// Determines the type of relationship that exists between a directory and an item.
///
/// - Parameters:
///   - outRelationship: A pointer to a variable in which to put the relationship between `directoryURL` and `otherURL`. For a list of possible values, see ``FileManager/URLRelationship``.
///   - directoryURL: The URL of the directory that potentially contains the item in `otherURL`. The URL in this parameter must specify a directory. This parameter must not be `nil`.
///   - otherURL: The URL of the file or directory whose relationship to `directoryURL` is being tested. This parameter must not be `nil`.
///   - error: On input, a pointer to an error object. If an error occurs, this pointer is set to an actual error object containing the error information. You may specify `nil` for this parameter if you do not want the error information.
/// - Returns: `YES` if the relationship between the items was successfully determined, or `NO` if an error occurred.
///
/// Use this method to determine the relationship between an item and a directory whose location you already know. If the relationship between the items is determined successfully, this method sets the value of the `outRelationship` parameter to an appropriate value. The directory may contain the item, it may be the same as the item, or it may not have a direct relationship to the item.
- (BOOL)getRelationship:(NSURLRelationship *)outRelationship ofDirectoryAtURL:(NSURL *)directoryURL toItemAtURL:(NSURL *)otherURL error:(NSError **)error API_AVAILABLE(macos(10.10), ios(8.0), watchos(2.0), tvos(9.0));

/// Determines the type of relationship that exists between a system directory and the specified item.
///
/// - Parameters:
///   - outRelationship: A pointer to a variable in which to put the relationship between `directoryURL` and `otherURL`. For a list of possible values, see ``FileManager/URLRelationship``.
///   - directory: The search path directory. For a list of possible values, see ``FileManager/SearchPathDirectory``.
///   - domainMask: The file system domain to search. Specify `0` for this parameter if you want the file manager to choose the domain appropriate for `url`.
///   - url: The URL of the file or directory whose relationship to `directoryURL` is being tested. This parameter must not be `nil`.
///   - error: On input, a pointer to an error object. If an error occurs, this pointer is set to an actual error object containing the error information. You may specify `nil` for this parameter if you do not want the error information.
/// - Returns: `YES` if the relationship between the items was successfully determined, or `NO` if an error occurred.
///
/// Use this method to determine the relationship between an item and one of the system-specific directories. For example, you might use this method to determine if the specified item is in the user's `Documents` directory or is in the trash. If the relationship between the items is determined successfully, this method sets the value of the `outRelationship` parameter to an appropriate value. The directory may contain the item, it may be the same as the item, or it may not have a direct relationship to the item.
- (BOOL)getRelationship:(NSURLRelationship *)outRelationship ofDirectory:(NSSearchPathDirectory)directory inDomain:(NSSearchPathDomainMask)domainMask toItemAtURL:(NSURL *)url error:(NSError **)error API_AVAILABLE(macos(10.10), ios(8.0), watchos(2.0), tvos(9.0));

/// Creates a directory with the given attributes at the specified URL.
///
/// - Parameters:
///   - url: A file URL that specifies the directory to create. If you want to specify a relative path, you must set the current working directory before creating the corresponding ``NSURL`` object. This parameter must not be `nil`.
///   - createIntermediates: If `YES`, this method creates any nonexistent parent directories as part of creating the directory in `url`. If `NO`, this method fails if any of the intermediate parent directories does not exist.
///   - attributes: The file attributes for the new directory. You can set the owner and group numbers, file permissions, and modification date. If you specify `nil` for this parameter, the directory is created according to the umask(2) of the process. Some of the keys, such as `NSFileHFSCreatorCode` and `NSFileHFSTypeCode`, do not apply to directories.
///   - error: On input, a pointer to an error object. If an error occurs, this pointer is set to an actual error object containing the error information. You may specify `nil` for this parameter if you do not want the error information.
/// - Returns: `YES` if the directory was created, `YES` if `createIntermediates` is set and the directory already exists, or `NO` if an error occurred.
///
/// If you specify `nil` for the `attributes` parameter, this method uses a default set of values for the owner, group, and permissions of any newly created directories in the path. Similarly, if you omit a specific attribute, the default value is used. The default values for newly created directories are as follows:
///
/// - Permissions are set according to the umask of the current process. For more information, see umask.
/// - The owner ID is set to the effective user ID of the process.
/// - The group ID is set to that of the parent directory.
///
/// If you want to specify a relative path for url, you must set the current working directory before creating the corresponding ``NSURL`` object.
- (BOOL)createDirectoryAtURL:(NSURL *)url withIntermediateDirectories:(BOOL)createIntermediates attributes:(nullable NSDictionary<NSFileAttributeKey, id> *)attributes error:(NSError **)error API_AVAILABLE(macos(10.7), ios(5.0), watchos(2.0), tvos(9.0));

/// Creates a symbolic link at the specified URL that points to an item at the given URL.
///
/// - Parameters:
///   - url: The file URL at which to create the new symbolic link. The last path component of the URL issued as the name of the link.
///   - destURL: The file URL that contains the item to be pointed to by the link. In other words, this is the destination of the link.
///   - error: On input, a pointer to an error object. If an error occurs, this pointer is set to an actual error object containing the error information. You may specify `nil` for this parameter if you do not want the error information.
/// - Returns: `YES` if the symbolic link was created or `NO` if an error occurred. This method also returns `NO` if a file, directory, or link already exists at `url`.
///
/// This method does not traverse symbolic links contained in `destURL`, making it possible to create symbolic links to locations that do not yet exist. Also, if the final path component in `url` is a symbolic link, that link is not followed.
- (BOOL)createSymbolicLinkAtURL:(NSURL *)url withDestinationURL:(NSURL *)destURL error:(NSError **)error API_AVAILABLE(macos(10.7), ios(5.0), watchos(2.0), tvos(9.0));

/// The delegate of the file manager object.
///
/// It is recommended that you assign a delegate to the file manager object only if you allocated and initialized the object yourself. Avoid assigning a delegate to the shared file manager obtained from the ``FileManager/default`` method.
///
/// The default value of this property is `nil`. When assigning a delegate to this property, your object must conform to the ``FileManagerDelegate`` protocol.
@property (nullable, assign) id <NSFileManagerDelegate> delegate API_AVAILABLE(macos(10.5), ios(2.0), watchos(2.0), tvos(9.0));

/// Sets the attributes of the specified file or directory.
///
/// - Parameters:
///   - attributes: A dictionary containing as keys the attributes to set for `path` and as values the corresponding value for the attribute. You can set the following attributes: `NSFileBusy`, `NSFileCreationDate`, `NSFileExtensionHidden`, `NSFileGroupOwnerAccountID`, `NSFileGroupOwnerAccountName`, `NSFileHFSCreatorCode`, `NSFileHFSTypeCode`, `NSFileImmutable`, `NSFileModificationDate`, `NSFileOwnerAccountID`, `NSFileOwnerAccountName`, `NSFilePosixPermissions`. You can change single attributes or any combination of attributes; you need not specify keys for all attributes.
///   - path: The path of a file or directory.
///   - error: On input, a pointer to an error object. If an error occurs, this pointer is set to an actual error object containing the error information. You may specify `nil` for this parameter if you do not want the error information.
/// - Returns: `YES` if _all_ changes succeed. If any change fails, returns `NO`, but it is undefined whether any changes actually occurred.
///
/// As in the POSIX standard, the app either must own the file or directory or must be running as superuser for attribute changes to take effect. The method attempts to make all changes specified in attributes and ignores any rejection of an attempted modification. If the last component of the path is a symbolic link, the system traverses it.
///
/// You must initialize the `NSFilePosixPermissions` value with the code representing the POSIX file-permissions bit pattern. The system sets `NSFileHFSCreatorCode` and `NSFileHFSTypeCode` only when `path` specifies a file.
- (BOOL)setAttributes:(NSDictionary<NSFileAttributeKey, id> *)attributes ofItemAtPath:(NSString *)path error:(NSError **)error API_AVAILABLE(macos(10.5), ios(2.0), watchos(2.0), tvos(9.0));

/// Creates a directory with given attributes at the specified path.
///
/// - Parameters:
///   - path: A path string identifying the directory to create. You may specify a full path or a path that is relative to the current working directory. This parameter must not be `nil`.
///   - createIntermediates: If `YES`, this method creates any nonexistent parent directories as part of creating the directory in `path`. If `NO`, this method fails if any of the intermediate parent directories does not exist. This method also fails if any of the intermediate path elements corresponds to a file and not a directory.
///   - attributes: The file attributes for the new directory and any newly created intermediate directories. You can set the owner and group numbers, file permissions, and modification date. If you specify `nil` for this parameter or omit a particular value, one or more default values are used as described in the discussion. Some of the keys, such as `NSFileHFSCreatorCode` and `NSFileHFSTypeCode`, do not apply to directories.
///   - error: On input, a pointer to an error object. If an error occurs, this pointer is set to an actual error object containing the error information. You may specify `nil` for this parameter if you do not want the error information.
/// - Returns: `YES` if the directory was created, `YES` if `createIntermediates` is set and the directory already exists, or `NO` if an error occurred.
///
/// If you specify `nil` for the `attributes` parameter, this method uses a default set of values for the owner, group, and permissions of any newly created directories in the path. Similarly, if you omit a specific attribute, the default value is used. The default values for newly created directories are as follows:
///
/// - Permissions are set according to the umask of the current process. For more information, see umask.
/// - The owner ID is set to the effective user ID of the process.
/// - The group ID is set to that of the parent directory.
- (BOOL)createDirectoryAtPath:(NSString *)path withIntermediateDirectories:(BOOL)createIntermediates attributes:(nullable NSDictionary<NSFileAttributeKey, id> *)attributes error:(NSError **)error API_AVAILABLE(macos(10.5), ios(2.0), watchos(2.0), tvos(9.0));

/// Performs a shallow search of the specified directory and returns the paths of any contained items.
///
/// - Parameters:
///   - path: The path to the directory whose contents you want to enumerate.
///   - error: On input, a pointer to an error object. If an error occurs, this pointer is set to an actual error object containing the error information. You may specify `nil` for this parameter if you do not want the error information.
/// - Returns: An array of ``NSString`` objects, each of which identifies a file, directory, or symbolic link contained in `path`. Returns an empty array if the directory exists but has no contents. In Objective-C, if an error occurs, this method returns `nil` and assigns an appropriate error object to the `error` parameter.
///
/// This method performs a shallow search of the directory and therefore does not traverse symbolic links or return the contents of any subdirectories. This method also does not return URLs for the current directory ("`.`"), parent directory ("`..`"), or resource forks (files that begin with "`._`") but it does return other hidden files (files that begin with a period character). If you need to perform a deep enumeration, use the ``NSFileManager/enumeratorAtURL:includingPropertiesForKeys:options:errorHandler:`` method instead.
///
/// The order of the files in the returned array is undefined.
- (nullable NSArray<NSString *> *)contentsOfDirectoryAtPath:(NSString *)path error:(NSError **)error API_AVAILABLE(macos(10.5), ios(2.0), watchos(2.0), tvos(9.0));

/// Performs a deep enumeration of the specified directory and returns the paths of all of the contained subdirectories.
///
/// - Parameters:
///   - path: The path of the directory to list.
///   - error: If an error occurs, upon return contains an ``NSError`` object that describes the problem. Pass `NULL` if you don't want error information.
/// - Returns: An array of strings, each containing the path of an item in the directory specified by `path`. When using Objective-C, returns `nil` if an error occurred.
///
/// This method recurses the specified directory and its subdirectories. The method skips the "`.`" and "`..`" directories at each level of the recursion.
///
/// Because this method recurses the directory's contents, you might not want to use it in performance-critical code. Instead, consider using the ``NSFileManager/enumeratorAtURL:includingPropertiesForKeys:options:errorHandler:`` or ``FileManager/enumerator(atPath:)`` method to enumerate the directory contents yourself. Doing so gives you more control over the retrieval of items and more opportunities to complete the enumeration or perform other tasks at the same time.
- (nullable NSArray<NSString *> *)subpathsOfDirectoryAtPath:(NSString *)path error:(NSError **)error API_AVAILABLE(macos(10.5), ios(2.0), watchos(2.0), tvos(9.0));

/// Returns the attributes of the item at a given path.
///
/// - Parameters:
///   - path: The path of a file or directory.
///   - error: On input, a pointer to an error object. If an error occurs, this pointer is set to an actual error object containing the error information. You may specify `nil` for this parameter if you do not want the error information.
/// - Returns: A dictionary object that describes the attributes (file, directory, symlink, and so on) of the file specified by `path` (or `nil` if an error occurred in Objective-C). The keys in the dictionary are described in `File Attribute Keys`.
///
/// If the item at the path is a symbolic link---that is, the value of the `NSFileType` key in the attributes dictionary is `NSFileTypeSymbolicLink`---you can use the ``FileManager/destinationOfSymbolicLink(atPath:)`` method to retrieve the path of the item pointed to by the link. You can also use the `stringByResolvingSymlinksInPath` method of ``NSString`` to resolve links in the path before retrieving the item's attributes.
///
/// As a convenience, ``NSDictionary`` provides a set of methods (declared as a category on ``NSDictionary``) for quickly and efficiently obtaining attribute information from the returned dictionary: `fileGroupOwnerAccountName`, `fileModificationDate`, `fileOwnerAccountName`, `filePosixPermissions`, `fileSize`, `fileSystemFileNumber`, `fileSystemNumber`, and `fileType`.
- (nullable NSDictionary<NSFileAttributeKey, id> *)attributesOfItemAtPath:(NSString *)path error:(NSError **)error API_AVAILABLE(macos(10.5), ios(2.0), watchos(2.0), tvos(9.0));

/// Returns a dictionary that describes the attributes of the mounted file system on which a given path resides.
///
/// - Parameters:
///   - path: Any pathname within the mounted file system.
///   - error: On input, a pointer to an error object. If an error occurs, this pointer is set to an actual error object containing the error information. You may specify `nil` for this parameter if you do not want the error information.
/// - Returns: A dictionary object that describes the attributes of the mounted file system on which `path` resides. See `File-System Attribute Keys` for a description of the keys available in the dictionary.
///
/// This method does not traverse a terminal symbolic link.
- (nullable NSDictionary<NSFileAttributeKey, id> *)attributesOfFileSystemForPath:(NSString *)path error:(NSError **)error API_AVAILABLE(macos(10.5), ios(2.0), watchos(2.0), tvos(9.0));

/// Creates a symbolic link that points to the specified destination.
///
/// - Parameters:
///   - path: The path at which to create the new symbolic link. The last path component is used as the name of the link.
///   - destPath: The path that contains the item to be pointed to by the link. In other words, this is the destination of the link.
///   - error: If an error occurs, upon return contains an ``NSError`` object that describes the problem. Pass `NULL` if you do not want error information.
/// - Returns: `YES` if the symbolic link was created or `NO` if an error occurred. This method also returns `NO` if a file, directory, or link already exists at `path`.
///
/// This method does not traverse symbolic links contained in `destPath`, making it possible to create symbolic links to locations that do not yet exist. Also, if the final path component in `path` is a symbolic link, that link is not followed.
- (BOOL)createSymbolicLinkAtPath:(NSString *)path withDestinationPath:(NSString *)destPath error:(NSError **)error API_AVAILABLE(macos(10.5), ios(2.0), watchos(2.0), tvos(9.0));

/// Returns the path of the item pointed to by a symbolic link.
///
/// - Parameters:
///   - path: The path of a file or directory.
///   - error: If an error occurs, upon return contains an ``NSError`` object that describes the problem. Pass `NULL` if you do not want error information.
/// - Returns: An ``NSString`` object containing the path of the directory or file to which the symbolic link `path` refers. When using Objective-C, returns `nil` upon failure. If the symbolic link is specified as a relative path, that relative path is returned.
- (nullable NSString *)destinationOfSymbolicLinkAtPath:(NSString *)path error:(NSError **)error API_AVAILABLE(macos(10.5), ios(2.0), watchos(2.0), tvos(9.0));

/// Copies the item at the specified path to a new location synchronously.
///
/// - Parameters:
///   - srcPath: The path to the file or directory you want to copy. This parameter must not be `nil`.
///   - dstPath: The path at which to place the copy of `srcPath`. This path must include the name of the file or directory in its new location. This parameter must not be `nil`.
///   - error: On input, a pointer to an error object. If an error occurs, this pointer is set to an actual error object containing the error information. You may specify `nil` for this parameter if you do not want the error information.
/// - Returns: `YES` if the item was copied successfully or the file manager's delegate stopped the operation deliberately. Returns `NO` if an error occurred.
///
/// When copying items, the current process must have permission to read the file or directory at `srcPath` and write the parent directory of `dstPath`. If the item at `srcPath` is a directory, this method copies the directory and all of its contents, including any hidden files. If a file with the same name already exists at `dstPath`, this method stops the copy attempt and returns an appropriate error. If the last component of `srcPath` is a symbolic link, only the link is copied to the new path.
///
/// Prior to copying an item, the file manager asks its delegate if it should actually do so for each item. It does this by calling the `fileManager:shouldCopyItemAtURL:toURL:` method; if that method is not implemented it calls the `fileManager:shouldCopyItemAtPath:toPath:` method instead. If the delegate method returns `YES`, or if the delegate does not implement the appropriate methods, the file manager copies the given file or directory. If there is an error copying an item, the file manager may also call the delegate's `fileManager:shouldProceedAfterError:copyingItemAtURL:toURL:` or `fileManager:shouldProceedAfterError:copyingItemAtPath:toPath:` method to determine how to proceed.
- (BOOL)copyItemAtPath:(NSString *)srcPath toPath:(NSString *)dstPath error:(NSError **)error API_AVAILABLE(macos(10.5), ios(2.0), watchos(2.0), tvos(9.0));
/// Moves the file or directory at the specified path to a new location synchronously.
///
/// - Parameters:
///   - srcPath: The path to the file or directory you want to move. This parameter must not be `nil`.
///   - dstPath: The new path for the item in `srcPath`. This path must include the name of the file or directory in its new location. This parameter must not be `nil`.
///   - error: On input, a pointer to an error object. If an error occurs, this pointer is set to an actual error object containing the error information. You may specify `nil` for this parameter if you do not want the error information.
/// - Returns: `YES` if the item was moved successfully or the file manager's delegate stopped the operation deliberately. Returns `NO` if an error occurred.
///
/// When moving items, the current process must have permission to read the item at `srcPath` and write the parent directory of `dstPath`. If the item at `srcPath` is a directory, this method moves the directory and all of its contents, including any hidden files. If an item with the same name already exists at `dstPath`, this method stops the move attempt and returns an appropriate error. If the last component of `srcPath` is a symbolic link, only the link is moved to the new path; the item pointed to by the link remains at its current location.
///
/// Prior to moving the item, the file manager asks its delegate if it should actually move it. It does this by calling the `fileManager:shouldMoveItemAtURL:toURL:` method; if that method is not implemented it calls the `fileManager:shouldMoveItemAtPath:toPath:` method instead. If the item being moved is a directory, the file manager notifies the delegate only for the directory itself and not for any of its contents. If the delegate method returns `YES`, or if the delegate does not implement the appropriate methods, the file manager moves the file. If there is an error moving one out of several items, the file manager may also call the delegate's `fileManager:shouldProceedAfterError:movingItemAtURL:toURL:` or `fileManager:shouldProceedAfterError:movingItemAtPath:toPath:` method to determine how to proceed.
///
/// If the source and destination of the move operation are not on the same volume, this method copies the item first and then removes it from its current location. This behavior may trigger additional delegate notifications related to copying and removing individual items.
- (BOOL)moveItemAtPath:(NSString *)srcPath toPath:(NSString *)dstPath error:(NSError **)error API_AVAILABLE(macos(10.5), ios(2.0), watchos(2.0), tvos(9.0));
/// Creates a hard link between the items at the specified paths.
///
/// - Parameters:
///   - srcPath: The path that specifies the item you wish to link to. The value in this parameter must not be `nil`.
///   - dstPath: The path that identifies the location where the link will be created. The value in this parameter must not be `nil`.
///   - error: On input, a pointer to an error object. If an error occurs, this pointer is set to an actual error object containing the error information. You may specify `nil` for this parameter if you do not want the error information.
/// - Returns: `YES` if the hard link was created or `NO` if an error occurred. This method also returns `NO` if a file, directory, or link already exists at `dstPath`.
///
/// Use this method to create hard links between files in the current file system. If `srcPath` is a directory, this method creates a new directory at `dstPath` and then creates hard links for the items in that directory. If `srcPath` is (or contains) a symbolic link, the symbolic link is copied to the new location and not converted to a hard link.
///
/// Prior to linking each item, the file manager asks its delegate if it should actually create the link. It does this by calling the `fileManager:shouldLinkItemAtURL:toURL:` method; if that method is not implemented it calls the `fileManager:shouldLinkItemAtPath:toPath:` method instead. If the delegate method returns `YES`, or if the delegate does not implement the appropriate methods, the file manager creates the hard link. If there is an error linking one out of several items, the file manager may also call the delegate's `fileManager:shouldProceedAfterError:linkingItemAtURL:toURL:` or `fileManager:shouldProceedAfterError:linkingItemAtPath:toPath:` method to determine how to proceed.
- (BOOL)linkItemAtPath:(NSString *)srcPath toPath:(NSString *)dstPath error:(NSError **)error API_AVAILABLE(macos(10.5), ios(2.0), watchos(2.0), tvos(9.0));
/// Removes the file or directory at the specified path.
///
/// - Parameters:
///   - path: A path string indicating the file or directory to remove. If the path specifies a directory, the contents of that directory are recursively removed. You may specify `nil` for this parameter in Objective-C.
///   - error: On input, a pointer to an error object. If an error occurs, this pointer is set to an actual error object containing the error information. You may specify `nil` for this parameter if you do not want the error information.
/// - Returns: `YES` if the item was removed successfully or if `path` was `nil`. Returns `NO` if an error occurred. If the delegate stops the operation for a file, this method returns `YES`. However, if the delegate stops the operation for a directory, this method returns `NO`.
///
/// Prior to removing each item, the file manager asks its delegate if it should actually do so. It does this by calling the `fileManager:shouldRemoveItemAtURL:` method; if that method is not implemented it calls the `fileManager:shouldRemoveItemAtPath:` method instead. If the delegate method returns `YES`, or if the delegate does not implement the appropriate methods, the file manager proceeds to remove the file or directory. If there is an error removing an item, the file manager may also call the delegate's `fileManager:shouldProceedAfterError:removingItemAtURL:` or `fileManager:shouldProceedAfterError:removingItemAtPath:` method to determine how to proceed.
///
/// Removing an item also removes all old versions of that item, invalidating any URLs returned by the `URLForPublishingUbiquitousItemAtURL:expirationDate:error:` method to old versions.
- (BOOL)removeItemAtPath:(NSString *)path error:(NSError **)error API_AVAILABLE(macos(10.5), ios(2.0), watchos(2.0), tvos(9.0));

/// Copies the file at the specified URL to a new location synchronously.
///
/// - Parameters:
///   - srcURL: The file URL that identifies the file you want to copy. The URL in this parameter must not be a file reference URL. This parameter must not be `nil`.
///   - dstURL: The URL at which to place the copy of `srcURL`. The URL in this parameter must not be a file reference URL and must include the name of the file in its new location. This parameter must not be `nil`.
///   - error: On input, a pointer to an error object. If an error occurs, this pointer is set to an actual error object containing the error information. You may specify `nil` for this parameter if you do not want the error information.
/// - Returns: `YES` if the item was copied successfully or the file manager's delegate stopped the operation deliberately. Returns `NO` if an error occurred.
///
/// When copying items, the current process must have permission to read the file or directory at `srcURL` and write the parent directory of `dstURL`. If the item at `srcURL` is a directory, this method copies the directory and all of its contents, including any hidden files. If a file with the same name already exists at `dstURL`, this method stops the copy attempt and returns an appropriate error. If the last component of `srcURL` is a symbolic link, only the link is copied to the new path.
- (BOOL)copyItemAtURL:(NSURL *)srcURL toURL:(NSURL *)dstURL error:(NSError **)error API_AVAILABLE(macos(10.6), ios(4.0), watchos(2.0), tvos(9.0));
/// Moves the file or directory at the specified URL to a new location synchronously.
///
/// - Parameters:
///   - srcURL: The file URL that identifies the file or directory you want to move. The URL in this parameter must not be a file reference URL. This parameter must not be `nil`.
///   - dstURL: The new location for the item in `srcURL`. The URL in this parameter must not be a file reference URL and must include the name of the file or directory in its new location. This parameter must not be `nil`.
///   - error: On input, a pointer to an error object. If an error occurs, this pointer is set to an actual error object containing the error information. You may specify `nil` for this parameter if you do not want the error information.
/// - Returns: `YES` if the item was moved successfully or the file manager's delegate stopped the operation deliberately. Returns `NO` if an error occurred.
///
/// When moving items, the current process must have permission to read the item at `srcURL` and write the parent directory of `dstURL`. If the item at `srcURL` is a directory, this method moves the directory and all of its contents, including any hidden files. If an item with the same name already exists at `dstURL`, this method stops the move attempt and returns an appropriate error. If the last component of `srcURL` is a symbolic link, only the link is moved to the new path; the item pointed to by the link remains at its current location.
///
/// If the source and destination of the move operation are not on the same volume, this method copies the item first and then removes it from its current location. This behavior may trigger additional delegate notifications related to copying and removing individual items.
- (BOOL)moveItemAtURL:(NSURL *)srcURL toURL:(NSURL *)dstURL error:(NSError **)error API_AVAILABLE(macos(10.6), ios(4.0), watchos(2.0), tvos(9.0));
/// Creates a hard link between the items at the specified URLs.
///
/// - Parameters:
///   - srcURL: The file URL that identifies the source of the link. The URL in this parameter must not be a file reference URL; it must specify the actual path to the item. The value in this parameter must not be `nil`.
///   - dstURL: The file URL that specifies where you want to create the hard link. The URL in this parameter must not be a file reference URL; it must specify the actual path to the item. The value in this parameter must not be `nil`.
///   - error: On input, a pointer to an error object. If an error occurs, this pointer is set to an actual error object containing the error information. You may specify `nil` for this parameter if you do not want the error information.
/// - Returns: `YES` if the hard link was created or `NO` if an error occurred. This method also returns `NO` if a file, directory, or link already exists at `dstURL`.
///
/// Use this method to create hard links between files in the current file system. If `srcURL` is a directory, this method creates a new directory at `dstURL` and then creates hard links for the items in that directory. If `srcURL` is (or contains) a symbolic link, the symbolic link is copied and not converted to a hard link at `dstURL`.
- (BOOL)linkItemAtURL:(NSURL *)srcURL toURL:(NSURL *)dstURL error:(NSError **)error API_AVAILABLE(macos(10.6), ios(4.0), watchos(2.0), tvos(9.0));
/// Removes the file or directory at the specified URL.
///
/// - Parameters:
///   - URL: A file URL specifying the file or directory to remove. If the URL specifies a directory, the contents of that directory are recursively removed. You may specify `nil` for this parameter in Objective-C.
///   - error: On input, a pointer to an error object. If an error occurs, this pointer is set to an actual error object containing the error information. You may specify `nil` for this parameter if you do not want the error information.
/// - Returns: `YES` if the item was removed successfully or if `URL` was `nil`. Returns `NO` if an error occurred. If the delegate stops the operation for a file, this method returns `YES`. However, if the delegate stops the operation for a directory, this method returns `NO`.
///
/// Prior to removing each item, the file manager asks its delegate if it should actually do so. It does this by calling the `fileManager:shouldRemoveItemAtURL:` method; if that method is not implemented it calls the `fileManager:shouldRemoveItemAtPath:` method instead.
///
/// Removing an item also removes all old versions of that item, invalidating any URLs returned by the `URLForPublishingUbiquitousItemAtURL:expirationDate:error:` method to old versions.
- (BOOL)removeItemAtURL:(NSURL *)URL error:(NSError **)error API_AVAILABLE(macos(10.6), ios(4.0), watchos(2.0), tvos(9.0));

/// Moves an item to the trash.
///
/// - Parameters:
///   - url: The item to move to the trash.
///   - outResultingURL: On input, a pointer to a URL object. On output, this pointer is set to the item's location in the trash. The actual name of the item may be changed when moving it to the trash, so use this URL to access it. You may specify `nil` for this parameter if you do not want the information.
///   - error: On input, a pointer to an error object. If an error occurs, this pointer is set to an actual error object containing the error information. You may specify `nil` for this parameter if you do not want the error information.
/// - Returns: `YES` if the item at `url` was successfully moved to the trash, or `NO` if the item was not moved to the trash.
- (BOOL)trashItemAtURL:(NSURL *)url resultingItemURL:(NSURL * _Nullable * _Nullable)outResultingURL error:(NSError **)error API_AVAILABLE(macos(10.8), ios(11.0)) API_UNAVAILABLE(watchos, tvos);

/// Returns a dictionary that describes the POSIX attributes of the file specified at a given path.
///
/// - Parameters:
///   - path: A file path.
///   - yorn: If `path` is not a symbolic link, this parameter has no effect. If `path` is a symbolic link, then: if `YES` the attributes of the linked-to file are returned, or if the link points to a nonexistent file the method returns `nil`; if `NO`, the attributes of the symbolic link are returned.
/// - Returns: An `NSDictionary` object that describes the POSIX attributes of the file specified at `path`. The keys in the dictionary are described in `File Attribute Keys`. If there is no item at `path`, returns `nil`.
- (nullable NSDictionary *)fileAttributesAtPath:(NSString *)path traverseLink:(BOOL)yorn API_DEPRECATED("Use -attributesOfItemAtPath:error: instead", macos(10.0,10.5), ios(2.0,2.0), watchos(2.0,2.0), tvos(9.0,9.0));
/// Changes the attributes of a given file or directory.
///
/// - Parameters:
///   - attributes: A dictionary containing as keys the attributes to set for `path` and as values the corresponding value for the attribute. You can set following: `NSFileBusy`, `NSFileCreationDate`, `NSFileExtensionHidden`, `NSFileGroupOwnerAccountID`, `NSFileGroupOwnerAccountName`, `NSFileHFSCreatorCode`, `NSFileHFSTypeCode`, `NSFileImmutable`, `NSFileModificationDate`, `NSFileOwnerAccountID`, `NSFileOwnerAccountName`, `NSFilePosixPermissions`. You can change single attributes or any combination of attributes; you need not specify keys for all attributes.
///   - path: A path to a file or directory.
/// - Returns: `YES` if _all_ changes succeed. If any change fails, returns `NO`, but it is undefined whether any changes actually occurred.
///
/// As in the POSIX standard, the app either must own the file or directory or must be running as superuser for attribute changes to take effect. The method attempts to make all changes specified in attributes and ignores any rejection of an attempted modification.
- (BOOL)changeFileAttributes:(NSDictionary *)attributes atPath:(NSString *)path API_DEPRECATED("Use -setAttributes:ofItemAtPath:error: instead", macos(10.0,10.5), ios(2.0,2.0), watchos(2.0,2.0), tvos(9.0,9.0));
/// Returns the directories and files (including symbolic links) contained in a given directory.
///
/// - Parameters:
///   - path: A path to a directory.
/// - Returns: An array of ``NSString`` objects identifying the directories and files (including symbolic links) contained in `path`. Returns an empty array if the directory exists but has no contents. Returns `nil` if the directory specified at `path` does not exist or there is some other error accessing it.
///
/// The search is shallow, and therefore does not return the contents of any subdirectories and does not traverse symbolic links in the specified directory. This returned array does not contain strings for the current directory ("`.`"), parent directory ("`..`"), or resource forks (begin with "`._`").
- (nullable NSArray *)directoryContentsAtPath:(NSString *)path API_DEPRECATED("Use -contentsOfDirectoryAtPath:error: instead", macos(10.0,10.5), ios(2.0,2.0), watchos(2.0,2.0), tvos(9.0,9.0));
/// Returns a dictionary that describes the attributes of the mounted file system on which a given path resides.
///
/// - Parameters:
///   - path: Any pathname within the mounted file system.
/// - Returns: An `NSDictionary` object that describes the attributes of the mounted file system on which `path` resides. See `File-System Attribute Keys` for a description of the keys available in the dictionary.
- (nullable NSDictionary *)fileSystemAttributesAtPath:(NSString *)path API_DEPRECATED("Use -attributesOfFileSystemForPath:error: instead", macos(10.0,10.5), ios(2.0,2.0), watchos(2.0,2.0), tvos(9.0,9.0));
/// Returns the path of the directory or file that a symbolic link at a given path refers to.
///
/// - Parameters:
///   - path: The path of a symbolic link.
/// - Returns: The path of the directory or file to which the symbolic link `path` refers, or `nil` upon failure. If the symbolic link is specified as a relative path, that relative path is returned.
- (nullable NSString *)pathContentOfSymbolicLinkAtPath:(NSString *)path API_DEPRECATED("Use -destinationOfSymbolicLinkAtPath:error:", macos(10.0,10.5), ios(2.0,2.0), watchos(2.0,2.0), tvos(9.0,9.0));
/// Creates a symbolic link identified by a given path that refers to a given location.
///
/// - Parameters:
///   - path: The path for a symbolic link.
///   - otherpath: The path to which `path` should refer.
/// - Returns: `YES` if the operation is successful, otherwise `NO`. Returns `NO` if a file, directory, or symbolic link identical to `path` already exists.
///
/// Creates a symbolic link identified by `path` that refers to the location `otherPath` in the file system.
- (BOOL)createSymbolicLinkAtPath:(NSString *)path pathContent:(NSString *)otherpath API_DEPRECATED("Use -createSymbolicLinkAtPath:error: instead", macos(10.0,10.5), ios(2.0,2.0), watchos(2.0,2.0), tvos(9.0,9.0));
/// Creates a directory (without contents) at a given path with given attributes.
///
/// - Parameters:
///   - path: The path at which to create the new directory. The directory to be created must not yet exist, but its parent directory must exist.
///   - attributes: The file attributes for the new directory. The attributes you can set are owner and group numbers, file permissions, and modification date. If you specify `nil` for `attributes`, default values for these attributes are set (particularly write access for the creator and read access for others). Some of the keys, such as `NSFileHFSCreatorCode` and `NSFileHFSTypeCode`, do not apply to directories.
/// - Returns: `YES` if the operation was successful, otherwise `NO`.
- (BOOL)createDirectoryAtPath:(NSString *)path attributes:(NSDictionary *)attributes API_DEPRECATED("Use -createDirectoryAtPath:withIntermediateDirectories:attributes:error: instead", macos(10.0,10.5), ios(2.0,2.0), watchos(2.0,2.0), tvos(9.0,9.0));

#if TARGET_OS_OSX || TARGET_OS_MACCATALYST
/// Creates a link from a source to a destination.
///
/// - Parameters:
///   - src: A path that identifies a source file or directory. The file, link, or directory specified by `source` must exist.
///   - dest: A path that identifies a destination file or directory. The destination should not yet exist. The destination path must end in a filename; there is no implicit adoption of the source filename.
///   - handler: An object that responds to the callback messages `fileManager:willProcessPath:` and `fileManager:shouldProceedAfterError:`. You can specify `nil` for `handler`; if you do so and an error occurs, the method automatically returns `NO`.
/// - Returns: `YES` if the link operation is successful. If the operation is not successful, but the handler method `fileManager:shouldProceedAfterError:` returns `YES`, also returns `YES`. Otherwise returns `NO`.
- (BOOL)linkPath:(NSString *)src toPath:(NSString *)dest handler:(nullable id)handler API_DEPRECATED("Not supported", macos(10.0,10.5), ios(2.0,2.0), watchos(2.0,2.0), tvos(9.0,9.0));
/// Copies the directory or file specified in a given path to a different location in the file system identified by another path.
///
/// - Parameters:
///   - src: The location of the source file.
///   - dest: The location to which to copy the file specified by `source`.
///   - handler: An object that responds to the callback messages `fileManager:willProcessPath:` and `fileManager:shouldProceedAfterError:`. You can specify `nil` for `handler`; if you do so and an error occurs, the method automatically returns `NO`.
/// - Returns: `YES` if the copy operation is successful. If the operation is not successful, but the callback handler of `fileManager:shouldProceedAfterError:` returns `YES`, also returns `YES`. Otherwise this method returns `NO`.
///
/// If `source` is a file, the method creates a file at `destination` that holds the exact contents of the original file (this includes BSD special files). If `source` is a directory, the method creates a new directory at `destination` and recursively populates it with duplicates of the files and directories contained in `source`, preserving all links. The file specified in `source` must exist, while `destination` must not exist prior to the operation.
- (BOOL)copyPath:(NSString *)src toPath:(NSString *)dest handler:(nullable id)handler API_DEPRECATED("Not supported", macos(10.0,10.5), ios(2.0,2.0), watchos(2.0,2.0), tvos(9.0,9.0));
/// Moves the directory or file specified by a given path to a different location in the file system identified by another path.
///
/// - Parameters:
///   - src: The path of a file or directory to move. `source` must exist.
///   - dest: The path to which `source` is moved. `destination` must not yet exist. The destination path must end in a filename; there is no implicit adoption of the source filename.
///   - handler: An object that responds to the callback messages `fileManager:willProcessPath:` and `fileManager:shouldProceedAfterError:`. You can specify `nil` for `handler`; if you do so and an error occurs, the method automatically returns `NO`.
/// - Returns: `YES` if the move operation is successful. If the operation is not successful, but the handler method `fileManager:shouldProceedAfterError:` returns `YES`, also returns `YES`; otherwise returns `NO`.
///
/// If `source` is a file, the method creates a file at `destination` that holds the exact contents of the original file and then deletes the original file. If `source` is a directory, the method creates a new directory at `destination` and recursively populates it with duplicates of the files and directories contained in `source`. It then deletes the old directory and its contents. Symbolic links are not traversed, however links are preserved.
- (BOOL)movePath:(NSString *)src toPath:(NSString *)dest handler:(nullable id)handler API_DEPRECATED("Not supported", macos(10.0,10.5), ios(2.0,2.0), watchos(2.0,2.0), tvos(9.0,9.0));
/// Deletes the file, link, or directory (including, recursively, all subdirectories, files, and links in the directory) identified by a given path.
///
/// - Parameters:
///   - path: The path of a file, link, or directory to delete. The value must not be "`.`" or "`..`".
///   - handler: An object that responds to the callback messages `fileManager:willProcessPath:` and `fileManager:shouldProceedAfterError:`. You can specify `nil` for `handler`; if you do so and an error occurs, the deletion stops and the method automatically returns `NO`.
/// - Returns: `YES` if the removal operation is successful. If the operation is not successful, but the handler method `fileManager:shouldProceedAfterError:` returns `YES`, also returns `YES`; otherwise returns `NO`.
///
/// Since the removal of directory contents is so thorough and final, be careful when using this method. If you specify "`.`" or "`..`" for `path` an `NSInvalidArgumentException` exception is raised. This method does not traverse symbolic links.
- (BOOL)removeFileAtPath:(NSString *)path handler:(nullable id)handler API_DEPRECATED("Not supported", macos(10.0,10.5), ios(2.0,2.0), watchos(2.0,2.0), tvos(9.0,9.0));
#endif

/* Process working directory management. Despite the fact that these are instance methods on NSFileManager, these methods report and change (respectively) the working directory for the entire process. Developers are cautioned that doing so is fraught with peril.
 */
/// The path to the program's current directory.
///
/// The current directory path is the starting point for any relative paths you specify. For example, if the current directory is `/tmp` and you specify a relative pathname of `reports/info.txt`, the resulting full path for the item is `/tmp/reports/info.txt`.
///
/// When an app is launched, this property is initially set to the app's current working directory. If the current working directory is not accessible for any reason, the value of this property is `nil`. You can change the value of this property by calling the `changeCurrentDirectoryPath:` method.
///
/// > Warning:
/// > This property reports the current working directory for the current process, not just the receiver.
@property (readonly, copy) NSString *currentDirectoryPath;
/// Changes the path of the current working directory to the specified path.
///
/// - Parameters:
///   - path: The path of the directory to which to change.
/// - Returns: `YES` if successful, otherwise `NO`.
///
/// All relative pathnames refer implicitly to the current working directory.
///
/// > Warning:
/// > This method changes the current working directory for the current process, not just the receiver.
- (BOOL)changeCurrentDirectoryPath:(NSString *)path;

/* The following methods are of limited utility. Attempting to predicate behavior based on the current state of the filesystem or a particular file on the filesystem is encouraging odd behavior in the face of filesystem race conditions. It's far better to attempt an operation (like loading a file or creating a directory) and handle the error gracefully than it is to try to figure out ahead of time whether the operation will succeed.
 */
/// Returns a Boolean value that indicates whether a file or directory exists at a specified path.
///
/// - Parameters:
///   - path: The path of the file or directory. If `path` begins with a tilde (`~`), it must first be expanded with `stringByExpandingTildeInPath`; otherwise, this method returns `NO`.
/// - Returns: `YES` if a file at the specified path exists, or `NO` if the file does not exist or its existence could not be determined.
///
/// If the file at `path` is inaccessible to your app, perhaps because one or more parent directories are inaccessible, this method returns `NO`. If the final element in `path` specifies a symbolic link, this method traverses the link and returns `YES` or `NO` based on the existence of the file at the link destination.
///
/// > Note:
/// > Attempting to predicate behavior based on the current state of the file system or a particular file on the file system is not recommended. Doing so can cause odd behavior or race conditions. It's far better to attempt an operation (such as loading a file or creating a directory), check for errors, and handle those errors gracefully than it is to try to figure out ahead of time whether the operation will succeed.
- (BOOL)fileExistsAtPath:(NSString *)path;
/// Returns a Boolean value that indicates whether a file or directory exists at a specified path.
///
/// - Parameters:
///   - path: The path of a file or directory. If `path` begins with a tilde (`~`), it must first be expanded with `stringByExpandingTildeInPath`, or this method will return `NO`.
///   - isDirectory: Upon return, contains `YES` if `path` is a directory or if the final path element is a symbolic link that points to a directory; otherwise, contains `NO`. If `path` doesn't exist, this value is undefined upon return. Pass `NULL` if you do not need this information.
/// - Returns: `YES` if a file at the specified path exists, or `NO` if the file's does not exist or its existence could not be determined.
///
/// If the file at `path` is inaccessible to your app, perhaps because one or more parent directories are inaccessible, this method returns `NO`. If the final element in `path` specifies a symbolic link, this method traverses the link and returns `YES` or `NO` based on the existence of the file at the link destination.
///
/// > Note:
/// > Attempting to predicate behavior based on the current state of the file system or a particular file on the file system is not recommended. Doing so can cause odd behavior or race conditions. It's far better to attempt an operation (such as loading a file or creating a directory), check for errors, and handle those errors gracefully than it is to try to figure out ahead of time whether the operation will succeed.
- (BOOL)fileExistsAtPath:(NSString *)path isDirectory:(nullable BOOL *)isDirectory;
/// Returns a Boolean value that indicates whether the invoking object appears able to read a specified file.
///
/// - Parameters:
///   - path: A file path.
/// - Returns: `YES` if the current process has read privileges for the file at `path`; otherwise `NO` if the process does not have read privileges or the existence of the file could not be determined.
///
/// If the file at `path` is inaccessible to your app, perhaps because it does not have search privileges for one or more parent directories, this method returns `NO`. This method traverses symbolic links in the path. This method also uses the real user ID and group ID, as opposed to the effective user and group IDs, to determine if the file is readable.
- (BOOL)isReadableFileAtPath:(NSString *)path;
/// Returns a Boolean value that indicates whether the invoking object appears able to write to a specified file.
///
/// - Parameters:
///   - path: A file path.
/// - Returns: `YES` if the current process has write privileges for the file at `path`; otherwise `NO` if the process does not have write privileges or the existence of the file could not be determined.
///
/// If the file at `path` is inaccessible to your app, perhaps because it does not have search privileges for one or more parent directories, this method returns `NO`. This method traverses symbolic links in the path. This method also uses the real user ID and group ID, as opposed to the effective user and group IDs, to determine if the file is writable.
- (BOOL)isWritableFileAtPath:(NSString *)path;
/// Returns a Boolean value that indicates whether the operating system appears able to execute a specified file.
///
/// - Parameters:
///   - path: A file path.
/// - Returns: `YES` if the current process has execute privileges for the file at `path`; otherwise `NO` if the process does not have execute privileges or the existence of the file could not be determined.
///
/// If the file at `path` is inaccessible to your app, perhaps because it does not have search privileges for one or more parent directories, this method returns `NO`. This method traverses symbolic links in the path. This method also uses the real user ID and group ID, as opposed to the effective user and group IDs, to determine if the file is executable.
- (BOOL)isExecutableFileAtPath:(NSString *)path;
/// Returns a Boolean value that indicates whether the invoking object appears able to delete a specified file.
///
/// - Parameters:
///   - path: A file path.
/// - Returns: `YES` if the current process has delete privileges for the file at `path`; otherwise `NO` if the process does not have delete privileges or the existence of the file could not be determined.
///
/// For a directory or file to be deletable, the current process must either be able to write to the parent directory of `path` or it must have the same owner as the item at `path`. If `path` is a directory, every item contained in `path` must be deletable by the current process.
///
/// If the file at `path` is inaccessible to your app, perhaps because it does not have search privileges for one or more parent directories, this method returns `NO`. If the item at `path` is a symbolic link, it is not traversed.
- (BOOL)isDeletableFileAtPath:(NSString *)path;

/// Returns a Boolean value that indicates whether the files or directories in specified paths have the same contents.
///
/// - Parameters:
///   - path1: The path of a file or directory to compare with the contents of `path2`.
///   - path2: The path of a file or directory to compare with the contents of `path1`.
/// - Returns: `YES` if file or directory specified in `path1` has the same contents as that specified in `path2`, otherwise `NO`.
///
/// If `path1` and `path2` are directories, the contents are the list of files and subdirectories each contains---contents of subdirectories are also compared. For files, this method checks to see if they're the same file, then compares their size, and finally compares their contents. This method does not traverse symbolic links, but compares the links themselves.
- (BOOL)contentsEqualAtPath:(NSString *)path1 andPath:(NSString *)path2;

/// Returns the display name of the file or directory at a specified path.
///
/// - Parameters:
///   - path: The path of a file or directory.
/// - Returns: The name of the file or directory at `path` in a localized form appropriate for presentation to the user. If there is no file or directory at `path`, or if an error occurs, returns `path` as is.
///
/// Display names are user-friendly names for files. They are typically used to localize standard file and directory names according to the user's language settings. They may also reflect other modifications, such as the removal of filename extensions. Such modifications are used only when displaying the file or directory to the user and do not reflect the actual path to the item in the file system.
- (NSString *)displayNameAtPath:(NSString *)path;

/// Returns an array of strings representing the user-visible components of a given path.
///
/// - Parameters:
///   - path: A pathname.
/// - Returns: An array of ``NSString`` objects representing the user-visible (for the Finder, Open and Save panels, and so on) components of `path`. Returns `nil` if path does not exist.
///
/// These components cannot be used for path operations and are only suitable for display to the user.
- (nullable NSArray<NSString *> *)componentsToDisplayForPath:(NSString *)path;

/// Returns a directory enumerator object that can be used to perform a deep enumeration of the directory at the specified path.
///
/// - Parameters:
///   - path: The path of the directory to enumerate.
/// - Returns: A ``FileManager/DirectoryEnumerator`` object that enumerates the contents of the directory at `path`. If `path` is a filename, the method returns an enumerator object that enumerates no files---the first call to `nextObject` will return `nil`.
///
/// Because the enumeration is deep---that is, it lists the contents of all subdirectories---this enumerator object is useful for performing actions that involve large file-system subtrees. This method does not resolve symbolic links encountered in the traversal process, nor does it recurse through them if they point to a directory.
///
/// The ``FileManager/DirectoryEnumerator`` class has methods for obtaining the attributes of the existing path and of the parent directory and for skipping descendants of the existing path.
- (nullable NSDirectoryEnumerator<NSString *> *)enumeratorAtPath:(NSString *)path;

/// Returns a directory enumerator object that can be used to perform a deep enumeration of the directory at the specified URL.
///
/// - Parameters:
///   - url: The location of the directory for which you want an enumeration. This URL must not be a symbolic link that points to the desired directory. You can use the `resolvingSymlinksInPath` method to resolve any symlinks in the URL.
///   - keys: An array of keys that identify the properties that you want pre-fetched for each item in the enumeration. The values for these keys are cached in the corresponding ``NSURL`` objects. You may specify `nil` for this parameter. For a list of keys you can specify, see ``URLResourceKey``.
///   - mask: Options for the enumeration. For a list of valid options, see `NSDirectoryEnumerationOptions`.
///   - handler: An optional error handler block for the file manager to call when an error occurs. The handler block should return `YES` if you want the enumeration to continue or `NO` if you want the enumeration to stop. If you specify `nil` for this parameter, the enumerator object continues to enumerate items as if you had specified a block that returned `YES`.
/// - Returns: A directory enumerator object that enumerates the contents of the directory at `url`. If `url` is a filename, the method returns an enumerator object that enumerates no files---the first call to `nextObject` returns `nil`.
///
/// Because the enumeration is deep---that is, it lists the contents of all subdirectories---this enumerator object is useful for performing actions that involve large file-system subtrees. If the method is passed a directory on which another file system is mounted (a mount point), it traverses the mount point. This method does not resolve symbolic links or mount points encountered in the enumeration process, nor does it recurse through them if they point to a directory.
///
/// The ``FileManager/DirectoryEnumerator`` class has methods for skipping descendants of the existing path and for returning the number of levels deep the current object is in the directory hierarchy being enumerated (where the directory passed to this method is considered to be level 0).
- (nullable NSDirectoryEnumerator<NSURL *> *)enumeratorAtURL:(NSURL *)url includingPropertiesForKeys:(nullable NSArray<NSURLResourceKey> *)keys options:(NSDirectoryEnumerationOptions)mask errorHandler:(nullable BOOL (^)(NSURL *url, NSError *error))handler API_AVAILABLE(macos(10.6), ios(4.0), watchos(2.0), tvos(9.0));

/// Returns an array of strings identifying the paths for all items in the specified directory.
///
/// - Parameters:
///   - path: The path of the directory to list.
/// - Returns: An array of ``NSString`` objects, each of which contains the path of an item in the directory specified by `path`. If `path` is a symbolic link, this method traverses the link. This method returns `nil` if it cannot retrieve the device of the linked-to file.
///
/// This method recurses the specified directory and its subdirectories. The method skips the "`.`" and "`..`" directories at each level of the recursion.
///
/// This method reveals every element of the subtree at `path`, including the contents of file packages (such as apps, nib files, and RTFD files).
///
/// In macOS 10.5 and later, use `subpathsOfDirectoryAtPath:error:` instead.
- (nullable NSArray<NSString *> *)subpathsAtPath:(NSString *)path;

/// Returns the contents of the file at the specified path.
///
/// - Parameters:
///   - path: The path of the file whose contents you want.
/// - Returns: An ``NSData`` object with the contents of the file. If `path` specifies a directory, or if some other error occurs, this method returns `nil`.
- (nullable NSData *)contentsAtPath:(NSString *)path;
/// Creates a file with the specified content and attributes at the given location.
///
/// - Parameters:
///   - path: The path for the new file.
///   - data: A data object containing the contents of the new file.
///   - attr: A dictionary containing the attributes to associate with the new file. You can use these attributes to set the owner and group numbers, file permissions, and modification date. For a list of keys, see `NSFileAttributeKey`. If you specify `nil` for `attributes`, the file is created with a set of default attributes.
/// - Returns: `YES` if the operation was successful or if the item already exists, otherwise `NO`.
///
/// If you specify `nil` for the `attributes` parameter, this method uses a default set of values for the owner, group, and permissions of any newly created directories in the path. Similarly, if you omit a specific attribute, the default value is used. The default values for newly created files are as follows:
///
/// - Permissions are set according to the umask of the current process. For more information, see umask.
/// - The owner ID is set to the effective user ID of the process.
/// - The group ID is set to that of the parent directory.
///
/// If a file already exists at `path`, this method overwrites the contents of that file if the current process has the appropriate privileges to do so.
- (BOOL)createFileAtPath:(NSString *)path contents:(nullable NSData *)data attributes:(nullable NSDictionary<NSFileAttributeKey, id> *)attr;

/// Returns a C-string representation of a given path that properly encodes Unicode strings for use by the file system.
///
/// - Parameters:
///   - path: A string object containing a path to a file. This parameter must not be `nil` or contain the empty string.
/// - Returns: A C-string representation of `path` that properly encodes Unicode strings for use by the file system.
///
/// Use this method if your code calls system routines that expect C-string path arguments. If you use the C string beyond the scope of the current autorelease pool, you must copy it.
///
/// This method raises an exception if `path` is `nil` or contains the empty string. This method also throws an exception if the conversion of the string fails.
- (const char *)fileSystemRepresentationWithPath:(NSString *)path NS_RETURNS_INNER_POINTER;

/// Returns an ``NSString`` object whose contents are derived from the specified C-string path.
///
/// - Parameters:
///   - str: A C string representation of a pathname.
///   - len: The number of characters in `string`.
/// - Returns: An ``NSString`` object converted from the C-string representation `string` with length `len` of a pathname in the current file system.
///
/// Use this method if your code receives paths as C strings from system routines.
- (NSString *)stringWithFileSystemRepresentation:(const char *)str length:(NSUInteger)len;

/// Replaces the contents of the item at the specified URL in a manner that ensures no data loss occurs.
///
/// - Parameters:
///   - originalItemURL: The item containing the content you want to replace.
///   - newItemURL: The item containing the new content for `originalItemURL`. It is recommended that you put this item in a temporary directory as provided by the OS. If a temporary directory is not available, put this item in a uniquely named directory that is in the same directory as the original item.
///   - backupItemName: If provided, the name used to create a backup of the original item. The backup is placed in the same directory as the original item. If an error occurs during the creation of the backup item, the operation fails. If there is already an item with the same name as the backup item, that item will be removed. The backup item will be removed in the event of success unless the `NSFileManagerItemReplacementWithoutDeletingBackupItem` option is provided in `options`.
///   - options: The options to use during the replacement. Typically, you pass `NSFileManagerItemReplacementUsingNewMetadataOnly` for this parameter, which uses only the metadata from the new item. Pass `0` to get the default behavior, which uses only the metadata from the new item while adjusting some properties using values from the original item.
///   - resultingURL: On input, a pointer for a URL object. When the item is replaced, this pointer is set to the URL of the new item. If no new file system object is required, the URL object in this parameter may be the same passed to the `originalItemURL` parameter. However, if a new file system object is required, the URL object may be different.
///   - error: On input, a pointer to an error object. If an error occurs, this pointer is set to an error object containing the error information. You may specify `nil` for this parameter if you do not want the error information.
/// - Returns: `YES` if the replacement was successful or `NO` if an error occurred.
///
/// By default, the creation date, permissions, Finder label and color, and Spotlight comments of the original item are preserved on the new item. You can configure which metadata is preserved using the `options` parameter.
///
/// This method works only when the `originalItemURL` and `newItemURL` parameters are located on the same volume. Attempting to call this method by passing `originalItemURL` and `newItemURL` parameters that have locations on different volumes results in an error. Instead, you can call the `URLForDirectory:inDomain:appropriateForURL:create:error:` method, passing `NSItemReplacementDirectory` as the search path directory, to get a temporary URL on the destination's volume that is suitable for use with this method.
///
/// If an error occurs and the original item is not in the original location or a temporary location, the resulting error object contains a user info dictionary with the key `"NSFileOriginalItemLocationKey"`. The value assigned to that key is an ``NSURL`` object with the location of the item.
- (BOOL)replaceItemAtURL:(NSURL *)originalItemURL withItemAtURL:(NSURL *)newItemURL backupItemName:(nullable NSString *)backupItemName options:(NSFileManagerItemReplacementOptions)options resultingItemURL:(NSURL * _Nullable * _Nullable)resultingURL error:(NSError **)error API_AVAILABLE(macos(10.6), ios(4.0), watchos(2.0), tvos(9.0));


/// Indicates whether the item at the specified URL should be stored in iCloud.
///
/// - Parameters:
///   - flag: `YES` to move the item to iCloud or `NO` to remove it from iCloud (if it is there currently).
///   - url: The URL of the item (file or directory) that you want to store in iCloud.
///   - destinationURL: When moving a file into iCloud, this is the location in iCloud at which to store the file or directory. This URL must be constructed from a URL returned by the `URLForUbiquityContainerIdentifier:` method. When moving a file out of iCloud, this is the location on the local device.
///   - error: On input, a pointer to variable for an ``NSError`` object. If an error occurs, this pointer is set to an ``NSError`` object containing information about the error. You may specify `nil` to ignore the error information.
/// - Returns: `YES` if the item's status was updated successfully or `NO` if an error occurred.
///
/// Use this method to move a file from its current location to iCloud. For files located in an app's sandbox, this involves physically removing the file from the sandbox container. You can also use this method to move files out of iCloud and back into a local directory.
///
/// > Important:
/// > Avoid calling this method from your app's main thread. This method performs a coordinated write operation on the specified file, which can block for a long time. Instead, use a dispatch queue to call this method from background thread.
- (BOOL)setUbiquitous:(BOOL)flag itemAtURL:(NSURL *)url destinationURL:(NSURL *)destinationURL error:(NSError **)error API_AVAILABLE(macos(10.7), ios(5.0), watchos(2.0), tvos(9.0));

/// Returns a Boolean indicating whether the item is targeted for storage in iCloud.
///
/// - Parameters:
///   - url: Specify the URL for the file or directory whose status you want to check.
/// - Returns: `YES` if the item is targeted for iCloud storage or `NO` if it is not. This method also returns `NO` if no item exists at `url`.
///
/// This method reflects only whether the item should be stored in iCloud because a call was made to the `setUbiquitous:itemAtURL:destinationURL:error:` method with a value of `YES` for its `flag` parameter. This method does not reflect whether the file has actually been uploaded to any iCloud servers. To determine a file's upload status, check the `NSURLUbiquitousItemIsUploadedKey` attribute of the corresponding ``NSURL`` object.
- (BOOL)isUbiquitousItemAtURL:(NSURL *)url API_AVAILABLE(macos(10.7), ios(5.0), watchos(2.0), tvos(9.0));

/// Starts downloading (if necessary) the specified item to the local system.
///
/// - Parameters:
///   - url: The URL for the file or directory in the cloud that you want to download.
///   - error: On input, a pointer to variable for an ``NSError`` object. If an error occurs, this pointer is set to an ``NSError`` object containing information about the error. You may specify `nil` to ignore the error information.
/// - Returns: `YES` if the download started successfully or was not necessary, `NO` otherwise.
///
/// If a cloud-based file or directory has not been downloaded yet, calling this method starts the download process. If the item exists locally, calling this method synchronizes the local copy with the version in the cloud.
- (BOOL)startDownloadingUbiquitousItemAtURL:(NSURL *)url error:(NSError **)error API_AVAILABLE(macos(10.7), ios(5.0), watchos(2.0), tvos(9.0));

/// Removes the local copy of the specified item that's stored in iCloud.
///
/// - Parameters:
///   - url: The URL to a file or directory in iCloud storage.
///   - error: On input, a pointer to variable for an ``NSError`` object. If an error occurs, this pointer is set to an ``NSError`` object containing information about the error. You may specify `nil` to ignore the error information.
/// - Returns: `YES` if the local item was removed successfully or `NO` if it was not.
///
/// Don't use a coordinated write to perform this operation. This method doesn't remove the item from iCloud. It removes only the local version. You can then use `startDownloadingUbiquitousItemAtURL:error:` to force iCloud to download a new version of the file or directory from the server.
///
/// To delete a file permanently from the user's iCloud storage, use the regular ``NSFileManager`` routines for deleting files and directories. Remember that deleting items from iCloud can't be undone. Once deleted, the item is gone forever.
- (BOOL)evictUbiquitousItemAtURL:(NSURL *)url error:(NSError **)error API_AVAILABLE(macos(10.7), ios(5.0), watchos(2.0), tvos(9.0));

/// Returns the URL for the iCloud container associated with the specified identifier and establishes access to that container.
///
/// - Parameters:
///   - containerIdentifier: The fully-qualified container identifier for an iCloud container directory. The string you specify must not contain wildcards and must be of the form `<TEAMID>.<CONTAINER>`, where `<TEAMID>` is your development team ID and `<CONTAINER>` is the bundle identifier of the container you want to access. If you specify `nil` for this parameter, this method returns the first container listed in the `com.apple.developer.ubiquity-container-identifiers` entitlement array.
/// - Returns: A URL pointing to the specified ubiquity container, or `nil` if the container could not be located or if iCloud storage is unavailable for the current user or device.
///
/// You use this method to determine the location of your app's ubiquity container directories and to configure your app's initial iCloud access. The first time you call this method for a given ubiquity container, the system extends your app's sandbox to include that container.
///
/// > Important:
/// > Do not call this method from your app's main thread. Because this method might take a nontrivial amount of time to set up iCloud and return the requested URL, you should always call it from a secondary thread. To determine if iCloud is available, especially at launch time, check the value of the `ubiquityIdentityToken` property instead.
- (nullable NSURL *)URLForUbiquityContainerIdentifier:(nullable NSString *)containerIdentifier API_AVAILABLE(macos(10.7), ios(5.0), watchos(2.0), tvos(9.0));

/// Returns a URL that can be emailed to users to allow them to download a copy of a flat file item from iCloud.
///
/// - Parameters:
///   - url: The URL of the item in the cloud that you want to share. The URL must be prefixed with the base URL returned from the `URLForUbiquityContainerIdentifier:` method that corresponds to the item's location. The file must be a flat file, not a bundle. The file at the specified URL must already be uploaded to iCloud when you call this method.
///   - outDate: On input, a pointer to a variable for a date object. On output, this parameter contains the date after which the item is no longer available at the returned URL. You may specify `nil` for this parameter if you are not interested in the date.
///   - error: On input, a pointer to variable for an ``NSError`` object. If an error occurs, this pointer is set to an ``NSError`` object containing information about the error. You may specify `nil` for this parameter if you do not want the error information.
/// - Returns: A URL with which users can download a copy of the item at `url`. In Objective-C, returns `nil` if the URL could not be created for any reason.
///
/// This method creates a snapshot of the specified flat file and places that copy in a temporary iCloud location where it can be accessed by other users using the returned URL. The snapshot reflects the contents of the file at the time the URL was generated and is not updated when subsequent changes are made to the original file in the user's iCloud storage.
///
/// Your app must have access to the network for this call to succeed. If the specified file is in the process of being uploaded to iCloud, you must not call this method until the upload has finished.
///
/// > Important:
/// > As of iOS 8.0 and macOS 10.10 The `url` must specify a flat file, not a bundle. Bundles have a folder as the root item.
- (nullable NSURL *)URLForPublishingUbiquitousItemAtURL:(NSURL *)url expirationDate:(NSDate * _Nullable * _Nullable)outDate error:(NSError **)error API_AVAILABLE(macos(10.7), ios(5.0), watchos(2.0), tvos(9.0));

/// An opaque token that represents the current user's iCloud Drive Documents identity.
///
/// In iCloud Drive Documents, when iCloud is available, this property contains an opaque object representing the identity of the current user. If iCloud is unavailable or there is no logged-in user, the value of this property is `nil`. Accessing the value of this property is relatively fast, so you can check the value at launch time from your app's main thread.
///
/// You can use the token in this property, together with the `NSUbiquityIdentityDidChangeNotification` notification, to detect when the user logs in or out of iCloud and to detect changes to the active iCloud account. When the user logs in with a different iCloud account, the identity token changes, and the system posts the notification. If you stored or archived the previous token, compare that token to the newly obtained one using the `isEqual:` method to determine if the users are the same or different.
///
/// Accessing the token in this property doesn't connect your app to its ubiquity containers. To establish access to a ubiquity container, call the `URLForUbiquityContainerIdentifier:` method.
@property (nullable, readonly, copy) id<NSObject,NSCopying,NSCoding> ubiquityIdentityToken API_AVAILABLE(macos(10.8), ios(6.0), watchos(2.0), tvos(9.0));

/// An option set of the sync controls available for an item.
///
/// Get an instance of this type by calling ``URL/resourceValues(forKeys:)`` on a ``URL`` instance (Swift) or ``NSURL/getResourceValue:forKey:error:`` on an ``NSURL`` (Swift or Objective-C) and passing in the key ``NSURLUbiquitousItemSupportedSyncControlsKey``.
typedef NS_OPTIONS(NSUInteger, NSFileManagerSupportedSyncControls) {
    /// The file provider supports pausing the sync on the item.
    NSFileManagerSupportedSyncControlsPauseSync = 1 << 0,

    /// The file provider supports failing an upload if the local and server versions conflict.
    NSFileManagerSupportedSyncControlsFailUploadOnConflict = 1 << 1,
} API_AVAILABLE(ios(26.0), macos(26.0), watchos(26.0), tvos(26.0), visionos(26.0));

/// Asynchronously pauses sync of an item at the given URL.
///
/// Call this when opening an item to prevent sync from altering the contents of the URL.
/// Once paused, the file provider will not upload local changes nor download remote changes.
///
/// While paused, call ``uploadLocalVersionOfUbiquitousItem(at:withConflictResolutionPolicy:completionHandler:)`` when the document is in a stable state.
/// This action keeps the server version as up-to-date as possible.
///
/// If the item is already paused, a second call to this method reports success.
/// If the file provider is already applying changes to the item, the pause fails with an ``NSFileWriteUnknownError-enum.case``, with an underlying error that has domain ``NSPOSIXErrorDomain`` and code ``POSIXError/EBUSY``.
/// If the pause fails, wait for the state to stabilize before retrying.
/// Pausing also fails with ``CocoaError/featureUnsupported`` if `url` refers to a regular (non-package) directory.
///
/// Pausing sync is independent of the calling app's lifecycle; sync doesn't automatically resume if the app closes or crashes and relaunches later.
/// To resume syncing, explicitly call ``resumeSyncForUbiquitousItem(at:with:completionHandler:)``.
/// Always be sure to resume syncing before you close the item.
///
/// - Parameters:
///   - url: The URL of the item for which to pause sync.
///   - completionHandler: A closure or block that the framework calls when the pause action completes. It receives a single ``NSError`` parameter to indicate an error that prevented pausing; this value is `nil` if the pause succeeded. In Swift, you can omit the completion handler and catch the thrown error instead.
- (void)pauseSyncForUbiquitousItemAtURL:(NSURL *)url completionHandler:(void (NS_SWIFT_SENDABLE ^)(NSError * _Nullable error))completionHandler API_AVAILABLE(ios(26.0), macos(26.0), visionos(26.0)) API_UNAVAILABLE(watchos, tvos);

/// The behaviors the file manager can apply to resolve conflicts when resuming a sync.
///
/// You use this type when calling ``FileManager/resumeSyncForUbiquitousItem(at:with:completionHandler:)`` to resume synchronizing.
/// In most situations, the ``NSFileManagerResumeSyncBehavior/preserveLocalChanges`` behavior is the best choice to avoid risk of data loss.
typedef NS_ENUM(NSInteger, NSFileManagerResumeSyncBehavior) {
    /// Resumes synchronizing by uploading the local version of the file.
    ///
    /// If the server has a newer version, the server may create a conflict copy of the file, or may automatically pick the winner of the conflict.
    /// Apps can choose to implement conflict handling themselves by passing `NSFileManagerResumeSyncBehaviorAfterUploadWithFailOnConflict`.
    NSFileManagerResumeSyncBehaviorPreserveLocalChanges          = 0,
    /// Resumes sync by first uploading the local version of the file, failing if the provider detects a conflict.
    ///
    /// If the upload succeeds, the sync resumes with the ``preserveLocalChanges`` behavior.
    ///
    /// If the provider detects a conflict, the upload fails with an  ``NSFileWriteUnknownError-enum.case``, with the underlying error of <doc://com.apple.documentation/documentation/FileProvider/NSFileProviderError/localVersionConflictingWithServer>.
    /// In this case, the app needs to call ``FileManager/fetchLatestRemoteVersionOfItem(at:completionHandler:)``, rebase local changes on top of the newly fetched version to resolve the conflict, and try again to resume sync.
    /// This scenario is only available on paused items for which the file provider supports the fail-on-conflict behavior.
    /// To check that the file provider supports the behavior, get the ``NSURLUbiquitousItemSupportedSyncControlsKey`` URL resource and verify that ``NSFileManagerSupportedSyncControls/failUploadOnConflict`` is `true`.
    NSFileManagerResumeSyncBehaviorAfterUploadWithFailOnConflict = 1,
    /// Resumes synchronizing by overwriting any local changes with the remote version of the file.
    ///
    /// If a conflict occurs, the file manager stores the local changes as an alternate version.
    /// Only use this behavior if you provide a separate means of resolving and merging conflicts.
    NSFileManagerResumeSyncBehaviorDropLocalChanges              = 2,
} API_AVAILABLE(ios(26.0), macos(26.0), visionos(26.0)) API_UNAVAILABLE(watchos, tvos);

/// Asynchronously resumes the sync on a paused item using the given resume behavior.
///
/// Always call this method when your app closes an item to allow the file provider to sync local changes back to the server.
///
/// In most situations, the ``NSFileManagerResumeSyncBehavior/preserveLocalChanges`` behavior is the best choice to avoid any risk of data loss.
///
/// The resume call fails with ``CocoaError/featureUnsupported`` if `url` isn't currently paused.
/// If the device isn't connected to the network, the call may fail with ``NSFileWriteUnknownError-enum.case``, with the underlying error of <doc://com.apple.documentation/documentation/FileProvider/NSFileProviderError/serverUnreachable>.
///
/// - Parameters:
///   - url: The URL of the item for which to resume sync.
///   - behavior: A ``NSFileManagerResumeSyncBehavior`` value that tells the file manager how to handle conflicts between local and remote versions of files.
///   - completionHandler: A closure or block that the framework calls when the resume action completes. It receives a single ``NSError`` parameter to indicate an error that prevented the resume action; the value is `nil` if the resume succeeded. In Swift, you can omit the completion handler and catch the thrown error instead.
- (void)resumeSyncForUbiquitousItemAtURL:(NSURL *)url withBehavior:(NSFileManagerResumeSyncBehavior)behavior completionHandler:(void (NS_SWIFT_SENDABLE ^)(NSError * _Nullable error))completionHandler API_AVAILABLE(ios(26.0), macos(26.0), visionos(26.0)) API_UNAVAILABLE(watchos, tvos);

/// Asynchronously fetches the latest remote version of a given item from the server.
///
/// Use this method if uploading fails due to a version conflict and sync is paused.
/// In this case, fetching the latest remote version allows you to inspect the newer item from the server, resolve the conflict, and resume uploading.
///
/// The version provided by this call depends on several factors:
/// * If there is no newer version of the file on the server, the caller receives the current version of the file.
/// * If the server has a newer version and sync isn't paused, this call replaces the local item and provides the version of the new item.
/// * If the server has a newer version but sync is paused, the returned version points to a side location. In this case, call ``NSFileVersion/replaceItem(at:options:)`` on the provided version object to replace the local item with the newer item from the server.
///
/// If the device isn't connected to the network, the call may fail with ``NSFileReadUnknownError-enum.case``, with the underlying error of <doc://com.apple.documentation/documentation/FileProvider/NSFileProviderError/serverUnreachable>.
///
/// - Parameters:
///   - url: The URL of the item for which to check the version.
///   - completionHandler: A closure or block that the framework calls when the fetch action completes. It receives parameters of types ``NSFileVersion`` and ``NSError``. The error is `nil` if fetching the remote version succeeded; otherwise it indicates the error that caused the call to fail. In Swift, you can omit the completion handler, catching any error in a `do`-`catch` block and receiving the version as the return value.
- (void)fetchLatestRemoteVersionOfItemAtURL:(NSURL *)url completionHandler:(void (NS_SWIFT_SENDABLE ^)(NSFileVersion * _Nullable latestRemoteVersion, NSError * _Nullable error))completionHandler API_AVAILABLE(ios(26.0), macos(26.0), visionos(26.0)) API_UNAVAILABLE(watchos, tvos);

/// The policies the file manager can apply to resolve conflicts when uploading a local version of a file.
typedef NS_ENUM(NSInteger, NSFileManagerUploadLocalVersionConflictPolicy) {
    /// Resolves the conflict using the policy defined by the file provider.
    NSFileManagerUploadConflictPolicyDefault = 0,
    /// Resolves the conflict by causing the upload to fail.
    ///
    /// This policy causes an upload to fail if the local version of a file, with any local changes applied, doesn't match the server version.
    /// In this scenario, call ``FileManager/fetchLatestRemoteVersionOfItem(at:completionHandler:)``, rebase local changes on top of the newly fetched version, and retry the upload.
    ///
    /// This policy is only available on paused items for which the file provider supports the fail-on-conflict behavior.
    /// To check that the file provider supports the behavior, get the ``NSURLUbiquitousItemSupportedSyncControlsKey`` URL resource and verify that ``NSFileManagerSupportedSyncControls/failUploadOnConflict`` is `true`.
    NSFileManagerUploadConflictPolicyFailOnConflict = 1,
} API_AVAILABLE(ios(26.0), macos(26.0), visionos(26.0)) API_UNAVAILABLE(watchos, tvos);

/// Asynchronously uploads the local version of the item using the provided conflict resolution policy.
///
/// Once your app pauses a sync for an item, call this method every time your document is in a stable state.
/// This action keeps the server version as up-to-date as possible.
///
/// If the server has a newer version than the one to which the app made changes, uploading fails with ``NSFileWriteUnknownError-enum.case``, with an underlying error of <doc://com.apple.documentation/documentation/FileProvider/NSFileProviderError/localVersionConflictingWithServer>.
/// In this case, call ``FileManager/fetchLatestRemoteVersionOfItem(at:completionHandler:)``, rebase local changes on top of that version, and retry the upload.
///
/// If the device isn't connected to the network, the call may fail with ``NSFileWriteUnknownError-enum.case``, with the underlying error of <doc://com.apple.documentation/documentation/FileProvider/NSFileProviderError/serverUnreachable>.
///
/// - Parameters:
///   - url: The URL of the item for which to check the version.
///   - conflictResolutionPolicy: The policy the file manager applies if the local and server versions conflict.
///   - completionHandler: A closure or block that the framework calls when the upload completes. It receives parameters of types ``NSFileVersion`` and ``NSError``. The error is `nil` if fetching the remote version succeeded; otherwise it indicates the error that caused the call to fail. In Swift, you can omit the completion handler, catching any error in a `do`-`catch` block and receiving the version as the return value.
- (void)uploadLocalVersionOfUbiquitousItemAtURL:(NSURL *)url withConflictResolutionPolicy:(NSFileManagerUploadLocalVersionConflictPolicy)conflictResolutionPolicy completionHandler:(void (NS_SWIFT_SENDABLE ^)(NSFileVersion * _Nullable uploadedVersion, NSError * _Nullable error))completionHandler API_AVAILABLE(ios(26.0), macos(26.0), visionos(26.0)) API_UNAVAILABLE(watchos, tvos);

/// Returns the services provided by the File Provider extension that manages the item at the given URL.
///
/// - Parameters:
///   - url: The file URL of a document or directory.
///   - completionHandler: A block that is called on an anonymous background queue. The system passes this block the following parameters: `services` (if the request is successful, a dictionary with zero or more `NSFileProviderServiceName` keys and their corresponding `NSFileProviderService` values; otherwise, `nil`) and `error` (if an error occurs, an object that describes the error; otherwise, `nil`).
///
/// Use the returned services to perform custom actions defined by the services' protocol. To access a service, get the `NSFileProviderService` object for the desired service name, get an `NSXPCConnection` from it, set up its `remoteObjectInterface` with the protocol that matches the service's name, call `resume` on the connection, and then call custom action methods on the proxy object.
- (void)getFileProviderServicesForItemAtURL:(NSURL *)url completionHandler:(void (NS_SWIFT_SENDABLE ^)(NSDictionary <NSFileProviderServiceName, NSFileProviderService *> * _Nullable services, NSError * _Nullable error))completionHandler API_AVAILABLE(macos(10.13), ios(11.0)) API_UNAVAILABLE(watchos, tvos);

/// Returns the container directory associated with the specified security application group identifier.
///
/// - Parameters:
///   - groupIdentifier: A string that names the group whose shared directory you want to obtain. This input should exactly match one of the strings in the app's App Groups entitlement.
/// - Returns: A URL indicating the location of the group's shared directory in the file system. In iOS, the value is `nil` when the group identifier is invalid. In macOS, a URL of the expected form is always returned, even if the app group is invalid, so be sure to test that you can access the underlying directory before attempting to use it.
///
/// Sandboxed apps in macOS and all apps in iOS that need to share files with other apps from the same developer on a given device use the App Groups entitlement to join one or more application groups.
- (nullable NSURL *)containerURLForSecurityApplicationGroupIdentifier:(NSString *)groupIdentifier API_AVAILABLE(macos(10.8), ios(7.0), watchos(2.0), tvos(9.0)); // Available for OS X in 10.8.3.


@end

@interface NSFileManager (NSUserInformation)

/// The home directory for the current user.
@property (readonly, copy) NSURL *homeDirectoryForCurrentUser API_AVAILABLE(macosx(10.12)) API_UNAVAILABLE(ios, watchos, tvos);
/// The temporary directory for the current user.
@property (readonly, copy) NSURL *temporaryDirectory API_AVAILABLE(macosx(10.12), ios(10.0), watchos(3.0), tvos(10.0));

/// Returns the home directory for the specified user.
///
/// - Parameters:
///   - userName: The username of the owner of the desired home directory.
/// - Returns: A URL object containing the location of the specified user's home directory, or `nil` if no such user exists or the user's home directory is not available.
- (nullable NSURL *)homeDirectoryForUser:(NSString *)userName API_AVAILABLE(macosx(10.12)) API_UNAVAILABLE(ios, watchos, tvos);

@end

/* These delegate methods are for the use of the deprecated handler-taking methods on NSFileManager for copying, moving, linking or deleting files.
 */
@interface NSObject (NSCopyLinkMoveHandler)
- (BOOL)fileManager:(NSFileManager *)fm shouldProceedAfterError:(NSDictionary *)errorInfo API_DEPRECATED(" Handler API no longer supported", macos(10.0,10.5), ios(2.0,2.0), watchos(2.0,2.0), tvos(9.0,9.0));
- (void)fileManager:(NSFileManager *)fm willProcessPath:(NSString *)path API_DEPRECATED("Handler API no longer supported", macos(10.0,10.5), ios(2.0,2.0), watchos(2.0,2.0), tvos(9.0,9.0));
@end


/// The interface a file manager's delegate uses to intervene during operations or if an error occurs.
///
/// The ``FileManagerDelegate`` protocol defines optional methods for managing operations involving the copying, moving, linking, or removal of files and directories. When you use an ``FileManager`` object to initiate a copy, move, link, or remove operation, the file manager asks its delegate whether the operation should begin at all and whether it should proceed when an error occurs.
///
/// The methods of this protocol accept either ``NSURL`` or ``NSString`` objects. The file manager always prefers methods that take an ``NSURL`` object over those that take an ``NSString`` object.
///
/// You should associate your delegate with a unique instance of the ``FileManager`` class, as opposed to the shared instance.
@protocol NSFileManagerDelegate <NSObject>
@optional

/// Asks the delegate if the file manager should copy the specified item to the new path.
///
/// Returning YES from this method will allow the copy to happen. Returning NO from this method causes the item in question to be skipped. If the item skipped was a directory, no children of that directory will be copied, nor will the delegate be notified of those children.
///
/// If the delegate does not implement this method, the NSFileManager instance acts as if this method returned YES.
- (BOOL)fileManager:(NSFileManager *)fileManager shouldCopyItemAtPath:(NSString *)srcPath toPath:(NSString *)dstPath;
/// Asks the delegate if the file manager should copy the specified item to the new URL.
///
/// This method is called once for each item that needs to be copied. Thus, for a directory, this method is called once for the directory and once for each item in the directory. This method is preferred over the path-based variant in macOS 10.6 and later.
///
/// If the delegate does not implement this method, the NSFileManager instance acts as if this method returned YES.
- (BOOL)fileManager:(NSFileManager *)fileManager shouldCopyItemAtURL:(NSURL *)srcURL toURL:(NSURL *)dstURL API_AVAILABLE(macos(10.6), ios(4.0), watchos(2.0), tvos(9.0));

/// Asks the delegate if the copy operation should continue after an error occurs while copying the item at the specified path.
///
/// If this method returns YES, the NSFileManager instance will continue as if the error had not occurred. If this method returns NO, the NSFileManager instance will stop copying.
///
/// If the delegate does not implement this method, the NSFileManager instance acts as if this method returned NO.
- (BOOL)fileManager:(NSFileManager *)fileManager shouldProceedAfterError:(NSError *)error copyingItemAtPath:(NSString *)srcPath toPath:(NSString *)dstPath;
/// Asks the delegate if the copy operation should continue after an error occurs while copying the item at the specified URL.
///
/// The file manager calls this method when there is a problem copying the item to the specified location. If you return YES, the file manager continues copying any other items and ignores the error. This method is preferred over the path-based variant in macOS 10.6 and later.
///
/// If the delegate does not implement this method, the NSFileManager instance acts as if this method returned NO.
- (BOOL)fileManager:(NSFileManager *)fileManager shouldProceedAfterError:(NSError *)error copyingItemAtURL:(NSURL *)srcURL toURL:(NSURL *)dstURL API_AVAILABLE(macos(10.6), ios(4.0), watchos(2.0), tvos(9.0));

/// Asks the delegate if the file manager should move the specified item to the new path.
///
/// If the source path and the destination path are not on the same device, a copy is performed to the destination path and the original is removed. If the copy does not succeed, an error is returned and the incomplete copy is removed, leaving the original in place.
///
/// If the delegate does not implement this method, the NSFileManager instance acts as if this method returned YES.
- (BOOL)fileManager:(NSFileManager *)fileManager shouldMoveItemAtPath:(NSString *)srcPath toPath:(NSString *)dstPath;
/// Asks the delegate if the file manager should move the specified item to the new URL.
///
/// If the delegate does not implement this method, the NSFileManager instance acts as if this method returned YES.
- (BOOL)fileManager:(NSFileManager *)fileManager shouldMoveItemAtURL:(NSURL *)srcURL toURL:(NSURL *)dstURL API_AVAILABLE(macos(10.6), ios(4.0), watchos(2.0), tvos(9.0));

/// Asks the delegate if the move operation should continue after an error occurs while moving the item at the specified path.
///
/// The delegate has the opportunity to remedy the error condition and allow the move to continue.
///
/// If the delegate does not implement this method, the NSFileManager instance acts as if this method returned NO.
- (BOOL)fileManager:(NSFileManager *)fileManager shouldProceedAfterError:(NSError *)error movingItemAtPath:(NSString *)srcPath toPath:(NSString *)dstPath;
/// Asks the delegate if the move operation should continue after an error occurs while moving the item at the specified URL.
///
/// If the delegate does not implement this method, the NSFileManager instance acts as if this method returned NO.
- (BOOL)fileManager:(NSFileManager *)fileManager shouldProceedAfterError:(NSError *)error movingItemAtURL:(NSURL *)srcURL toURL:(NSURL *)dstURL API_AVAILABLE(macos(10.6), ios(4.0), watchos(2.0), tvos(9.0));

/// Asks the delegate if the file manager should create a hard link to the item at the specified path.
///
/// If the delegate does not implement this method, the NSFileManager instance acts as if this method returned YES.
- (BOOL)fileManager:(NSFileManager *)fileManager shouldLinkItemAtPath:(NSString *)srcPath toPath:(NSString *)dstPath;
/// Asks the delegate if the file manager should create a hard link to the item at the specified URL.
///
/// If the delegate does not implement this method, the NSFileManager instance acts as if this method returned YES.
- (BOOL)fileManager:(NSFileManager *)fileManager shouldLinkItemAtURL:(NSURL *)srcURL toURL:(NSURL *)dstURL API_AVAILABLE(macos(10.6), ios(4.0), watchos(2.0), tvos(9.0));

/// Asks the delegate if the link operation should continue after an error occurs while linking the item at the specified path.
///
/// If the delegate returns YES from this method, the linking will continue. If the delegate returns NO from this method, the linking operation will stop and the error will be returned.
///
/// If the delegate does not implement this method, the NSFileManager instance acts as if this method returned NO.
- (BOOL)fileManager:(NSFileManager *)fileManager shouldProceedAfterError:(NSError *)error linkingItemAtPath:(NSString *)srcPath toPath:(NSString *)dstPath;
/// Asks the delegate if the link operation should continue after an error occurs while linking the item at the specified URL.
///
/// If the delegate does not implement this method, the NSFileManager instance acts as if this method returned NO.
- (BOOL)fileManager:(NSFileManager *)fileManager shouldProceedAfterError:(NSError *)error linkingItemAtURL:(NSURL *)srcURL toURL:(NSURL *)dstURL API_AVAILABLE(macos(10.6), ios(4.0), watchos(2.0), tvos(9.0));

/// Asks the delegate if the file manager should remove the item at the specified path.
///
/// If the delegate returns YES from this method, the NSFileManager instance will attempt to remove the item. If the delegate returns NO, the remove skips the item. If the item is a directory, no children of that item will be visited.
///
/// If the delegate does not implement this method, the NSFileManager instance acts as if this method returned YES.
- (BOOL)fileManager:(NSFileManager *)fileManager shouldRemoveItemAtPath:(NSString *)path;
/// Asks the delegate if the file manager should remove the item at the specified URL.
///
/// If the delegate does not implement this method, the NSFileManager instance acts as if this method returned YES.
- (BOOL)fileManager:(NSFileManager *)fileManager shouldRemoveItemAtURL:(NSURL *)URL API_AVAILABLE(macos(10.6), ios(4.0), watchos(2.0), tvos(9.0));

/// Asks the delegate if the remove operation should continue after an error occurs while removing the item at the specified path.
///
/// If the delegate returns YES from this method, the removal operation will continue. If the delegate returns NO, the removal operation will stop and the error will be returned.
///
/// If the delegate does not implement this method, the NSFileManager instance acts as if this method returned NO.
- (BOOL)fileManager:(NSFileManager *)fileManager shouldProceedAfterError:(NSError *)error removingItemAtPath:(NSString *)path;
/// Asks the delegate if the remove operation should continue after an error occurs while removing the item at the specified URL.
///
/// If the delegate does not implement this method, the NSFileManager instance acts as if this method returned NO.
- (BOOL)fileManager:(NSFileManager *)fileManager shouldProceedAfterError:(NSError *)error removingItemAtURL:(NSURL *)URL API_AVAILABLE(macos(10.6), ios(4.0), watchos(2.0), tvos(9.0));

@end


/// An object that enumerates the contents of a directory.
///
/// You obtain a directory enumerator using ``NSFileManager``'s `enumeratorAtPath:` method. The enumeration provides the pathnames of all files and directories contained within that directory. These pathnames are relative to the directory.
///
/// An enumeration is recursive, including the files of all subdirectories, and crosses device boundaries. An enumeration does not resolve symbolic links, or attempt to traverse symbolic links that point to directories.
@interface NSDirectoryEnumerator<ObjectType> : NSEnumerator<ObjectType>

/// A dictionary with the attributes of the most recently returned file or subdirectory (as referenced by the pathname).
///
/// See the description of the `fileAttributesAtPath:traverseLink:` method of ``NSFileManager`` for details on obtaining the attributes from the dictionary.
@property (nullable, readonly, copy) NSDictionary<NSFileAttributeKey, id> *fileAttributes;
/// A dictionary with the attributes of the directory at which enumeration started.
///
/// See the description of the `fileAttributesAtPath:traverseLink:` method of ``NSFileManager`` for details on obtaining the attributes from the dictionary.
@property (nullable, readonly, copy) NSDictionary<NSFileAttributeKey, id> *directoryAttributes;

/* For NSDirectoryEnumerators created with -enumeratorAtURL:includingPropertiesForKeys:options:errorHandler: and the NSDirectoryEnumerationIncludesDirectoriesPostOrder option, this property is YES when the current object is a directory that is being enumerated after all of its contents have been enumerated.
 */
@property (readonly) BOOL isEnumeratingDirectoryPostOrder API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0));

/// Causes the receiver to skip recursion into the most recently obtained subdirectory.
- (void)skipDescendents;

/// The number of levels deep the current object is in the directory hierarchy being enumerated.
///
/// The number of levels, with the directory passed to `enumeratorAtURL:includingPropertiesForKeys:options:errorHandler:` considered to be level `0`.
@property (readonly) NSUInteger level API_AVAILABLE(macos(10.6), ios(4.0), watchos(2.0), tvos(9.0));

/// Causes the receiver to skip recursion into the most recently obtained subdirectory.
///
/// This method is identical to `skipDescendents` except for the spelling.
- (void)skipDescendants API_AVAILABLE(macos(10.6), ios(4.0), watchos(2.0), tvos(9.0));

@end


/* In an application that has received a URL to a file owned by a file provider, instances of NSFileProviderService can by obtained by calling -[NSFileManager getFileProviderServicesForItemAtURL:completionHandler:]. Each NSFileProviderService instance can only be used to operate on the URL originally passed to that method.
 */
/// A service that provides a custom communication channel between your app and a File Provider extension.
///
/// To communicate, both your app and the File Provider extension must implement their part of the service:
///
/// - Your app requests the proxy object, and calls its methods.
/// - The File Provider extension declares the supported services and vends a proxy object that implements the protocol for each service.
///
/// The app and File Provider extension communicate using an XPC service. This service performs actions only on items managed by the File Provider extension. For more information, see [Creating XPC Services](https://developer.apple.com/library/archive/documentation/MacOSX/Conceptual/BPSystemStartup/Chapters/CreatingXPCServices.html#//apple_ref/doc/uid/10000172i-SW6).
///
/// ### Defining the Service’s Protocol
///
/// Services let you define custom actions that are not provided by Apple's APIs. Both the app and the File Provider extension must agree upon the service's name and protocol.  Communicate the name and protocol through an outside source (for example, posting a header file that defines both the name and protocol, or publishing a library that includes them both).
///
/// The service can be defined by either the app or the File Provider extension:
///
/// - Apps can define a service for features they would like to use. File providers can then choose to support those features by implementing the service.
/// - File Provider extensions can provide a service for the features they support. Apps can then choose to use the specified service.
///
/// When defining a service's protocol, the parameters for each method must adhere to the following rules:
///
/// - The parameter's class must conform to ``NSSecureCoding``.
/// - The parameter's class must be defined in both the app and the File Provider extension (for example, standard system types or classes defined in a library imported by both sides).
/// - If a collection parameter contains types other than property list types (see [Property List Types and Objects](https://developer.apple.com/library/archive/documentation/General/Conceptual/DevPedia-CocoaCore/PropertyList.html#//apple_ref/doc/uid/TP40008195-CH44-SW2)), declare the valid types using the ``NSXPCInterface`` class's ``NSXPCInterface/classes(for:argumentIndex:ofReply:)`` method.
API_AVAILABLE(macos(10.13), ios(11.0)) API_UNAVAILABLE(watchos, tvos)
@interface NSFileProviderService : NSObject {
@private
    NSFileProviderServiceName _name;
    id _endpointCreatingProxy;
    dispatch_group_t _requestFinishedGroup;
}
/// Asynchronously returns the service's connection object.
///
/// - Parameters:
///   - completionHandler: A block that is called on an anonymous background queue. The block receives the `NSXPCConnection` object for the service, or `nil` if an error occurs, and an `NSError` describing the error if one occurred.
- (void)getFileProviderConnectionWithCompletionHandler:(void (NS_SWIFT_SENDABLE ^)(NSXPCConnection * _Nullable connection, NSError * _Nullable error))completionHandler;
/// The File Provider service's name.
@property (readonly, copy) NSFileProviderServiceName name;
@end

/// The key in a file attribute dictionary whose value indicates the file's type.
///
/// The corresponding value is an `NSString` object. See `NSFileAttributeType` for possible values.
FOUNDATION_EXPORT NSFileAttributeKey const NSFileType;
/// A directory.
FOUNDATION_EXPORT NSFileAttributeType const NSFileTypeDirectory;
/// A regular file.
FOUNDATION_EXPORT NSFileAttributeType const NSFileTypeRegular;
/// A symbolic link.
FOUNDATION_EXPORT NSFileAttributeType const NSFileTypeSymbolicLink;
/// A socket.
FOUNDATION_EXPORT NSFileAttributeType const NSFileTypeSocket;
/// A character special file.
FOUNDATION_EXPORT NSFileAttributeType const NSFileTypeCharacterSpecial;
/// A block special file.
FOUNDATION_EXPORT NSFileAttributeType const NSFileTypeBlockSpecial;
/// A file whose type is unknown.
FOUNDATION_EXPORT NSFileAttributeType const NSFileTypeUnknown;
/// The key in a file attribute dictionary whose value indicates the file's size in bytes.
///
/// The corresponding value is an `NSNumber` object containing an `unsigned long long`.
///
/// > Important: If the file has a resource fork, the returned value does _not_ include the size of the resource fork.
FOUNDATION_EXPORT NSFileAttributeKey const NSFileSize;
/// The key in a file attribute dictionary whose value indicates the file's last modified date.
///
/// The corresponding value is an `NSDate` object.
FOUNDATION_EXPORT NSFileAttributeKey const NSFileModificationDate;
/// The key in a file attribute dictionary whose value indicates the file's reference count.
///
/// The corresponding value is an `NSNumber` object containing an `unsigned long`. The number specifies the number of hard links to a file.
FOUNDATION_EXPORT NSFileAttributeKey const NSFileReferenceCount;
/// The key in a file attribute dictionary whose value indicates the identifier for the device on which the file resides.
///
/// The corresponding value is an `NSNumber` object containing an `unsigned long`.
FOUNDATION_EXPORT NSFileAttributeKey const NSFileDeviceIdentifier;
/// The key in a file attribute dictionary whose value indicates the name of the file's owner.
///
/// The corresponding value is an `NSString` object.
FOUNDATION_EXPORT NSFileAttributeKey const NSFileOwnerAccountName;
/// The key in a file attribute dictionary whose value indicates the group name of the file's owner.
///
/// The corresponding value is an `NSString` object.
FOUNDATION_EXPORT NSFileAttributeKey const NSFileGroupOwnerAccountName;
/// The key in a file attribute dictionary whose value indicates the file's Posix permissions.
///
/// The corresponding value is an `NSNumber` object. Use the `int16Value` method to retrieve the integer value for the permissions.
FOUNDATION_EXPORT NSFileAttributeKey const NSFilePosixPermissions;
/// The key in a file system attribute dictionary whose value indicates the filesystem number of the file system.
///
/// The corresponding value is an `NSNumber` object that specifies the filesystem number. The value corresponds to the value of `st_dev`, as returned by `stat`(2).
FOUNDATION_EXPORT NSFileAttributeKey const NSFileSystemNumber;
/// The key in a file attribute dictionary whose value indicates the file's filesystem file number.
///
/// The corresponding value is an `NSNumber` object containing an `unsigned long`. The value corresponds to the value of `st_ino`, as returned by `stat`(2).
FOUNDATION_EXPORT NSFileAttributeKey const NSFileSystemFileNumber;
/// The key in a file attribute dictionary whose value indicates whether the file's extension is hidden.
///
/// The corresponding value is an `NSNumber` object containing a Boolean value.
FOUNDATION_EXPORT NSFileAttributeKey const NSFileExtensionHidden;
/// The key in a file attribute dictionary whose value indicates the file's HFS creator code.
///
/// The corresponding value is an `NSNumber` object containing an `OSType` (unsigned 32-bit integer).
FOUNDATION_EXPORT NSFileAttributeKey const NSFileHFSCreatorCode;
/// The key in a file attribute dictionary whose value indicates the file's HFS type code.
///
/// The corresponding value is an `NSNumber` object containing an `OSType` (unsigned 32-bit integer). See HFS File Types for possible values.
FOUNDATION_EXPORT NSFileAttributeKey const NSFileHFSTypeCode;
/// The key in a file attribute dictionary whose value indicates whether the file is mutable.
///
/// The corresponding value is an `NSNumber` object containing a Boolean value.
FOUNDATION_EXPORT NSFileAttributeKey const NSFileImmutable;
/// The key in a file attribute dictionary whose value indicates whether the file is read-only.
///
/// The corresponding value is an `NSNumber` object containing a Boolean value.
FOUNDATION_EXPORT NSFileAttributeKey const NSFileAppendOnly;
/// The key in a file attribute dictionary whose value indicates the file's creation date.
///
/// The corresponding value is an `NSDate` object.
///
/// > Important: This API has the potential of being misused to access device signals to try to identify the device or user, also known as fingerprinting. Regardless of whether a user gives your app permission to track, fingerprinting is not allowed. When you use this API in your app or third-party SDK (an SDK not provided by Apple), declare your usage and the reason for using the API in your app or third-party SDK's `PrivacyInfo.xcprivacy` file. For more information, including the list of valid reasons for using the API, see [Describing use of required reason API](https://developer.apple.com/documentation/bundleresources/describing-use-of-required-reason-api).
FOUNDATION_EXPORT NSFileAttributeKey const NSFileCreationDate;
/// The key in a file attribute dictionary whose value indicates the file's owner's account ID.
///
/// The corresponding value is an `NSNumber` object containing an `unsigned long`.
FOUNDATION_EXPORT NSFileAttributeKey const NSFileOwnerAccountID;
/// The key in a file attribute dictionary whose value indicates the file's group ID.
///
/// The corresponding value is an `NSNumber` object containing an `unsigned long`.
FOUNDATION_EXPORT NSFileAttributeKey const NSFileGroupOwnerAccountID;
/// The key in a file attribute dictionary whose value indicates whether the file is busy.
///
/// The corresponding value is an `NSNumber` object containing a Boolean value.
FOUNDATION_EXPORT NSFileAttributeKey const NSFileBusy;
/// The key in a file attribute dictionary whose value identifies the protection level for this file.
///
/// The corresponding value is an `NSString` value. For a list of possible values, see `NSFileProtectionType`.
FOUNDATION_EXPORT NSFileAttributeKey const NSFileProtectionKey API_AVAILABLE(macos(10.6), ios(4.0), watchos(2.0), tvos(9.0));
/// The file has no special protections associated with it.
///
/// A file with this type of protection can be read from or written to at any time.
FOUNDATION_EXPORT NSFileProtectionType const NSFileProtectionNone API_AVAILABLE(macos(10.6), ios(4.0), watchos(2.0), tvos(9.0));
/// The file is stored in an encrypted format on disk and cannot be read from or written to while the device is locked or booting.
FOUNDATION_EXPORT NSFileProtectionType const NSFileProtectionComplete API_AVAILABLE(macos(10.6), ios(4.0), watchos(2.0), tvos(9.0));
/// The file is stored in an encrypted format on disk after it is closed.
///
/// Files with this type of protection can be created while the device is locked, but once closed, cannot be opened again until the device is unlocked. If the file is opened when unlocked, you may continue to access the file normally, even if the user locks the device.
FOUNDATION_EXPORT NSFileProtectionType const NSFileProtectionCompleteUnlessOpen API_AVAILABLE(macos(10.6), ios(5.0), watchos(2.0), tvos(9.0));
/// The file is stored in an encrypted format on disk and cannot be accessed until after the device has booted.
///
/// After the user unlocks the device for the first time, your app can access the file and continue to access it even if the user subsequently locks the device.
FOUNDATION_EXPORT NSFileProtectionType const NSFileProtectionCompleteUntilFirstUserAuthentication API_AVAILABLE(macos(10.6), ios(5.0), watchos(2.0), tvos(9.0));
FOUNDATION_EXPORT NSFileProtectionType const NSFileProtectionCompleteWhenUserInactive API_AVAILABLE(ios(17.0), watchos(10.0), tvos(17.0)) API_UNAVAILABLE(macos);

/// The key in a file system attribute dictionary whose value indicates the size of the file system.
///
/// The corresponding value is an `NSNumber` object that specifies the size of the file system in bytes. The value is determined by `statfs()`.
///
/// > Important: This API has the potential of being misused to access device signals to try to identify the device or user, also known as fingerprinting. Regardless of whether a user gives your app permission to track, fingerprinting is not allowed. When you use this API in your app or third-party SDK (an SDK not provided by Apple), declare your usage and the reason for using the API in your app or third-party SDK's `PrivacyInfo.xcprivacy` file. For more information, including the list of valid reasons for using the API, see [Describing use of required reason API](https://developer.apple.com/documentation/bundleresources/describing-use-of-required-reason-api).
FOUNDATION_EXPORT NSFileAttributeKey const NSFileSystemSize;
/// The key in a file system attribute dictionary whose value indicates the amount of free space on the file system.
///
/// The corresponding value is an `NSNumber` object that specifies the amount of free space on the file system in bytes. The value is determined by `statfs()`.
FOUNDATION_EXPORT NSFileAttributeKey const NSFileSystemFreeSize;
/// The key in a file system attribute dictionary whose value indicates the number of nodes in the file system.
///
/// The corresponding value is an `NSNumber` object that specifies the number of nodes in the file system.
FOUNDATION_EXPORT NSFileAttributeKey const NSFileSystemNodes;
/// The key in a file system attribute dictionary whose value indicates the number of free nodes in the file system.
///
/// The corresponding value is an `NSNumber` object that specifies the number of free nodes in the file system.
FOUNDATION_EXPORT NSFileAttributeKey const NSFileSystemFreeNodes;

@interface NSDictionary<KeyType, ObjectType> (NSFileAttributes)

/// Returns the file's size, in bytes.
///
/// - Returns: The value associated with the `NSFileSize` key, or `0` if the dictionary has no entry for the key.
- (unsigned long long)fileSize;
/// Returns the file's modification date.
///
/// - Returns: The value associated with the `NSFileModificationDate` key, or `nil` if the dictionary has no entry for the key.
- (nullable NSDate *)fileModificationDate;
/// Returns the file type.
///
/// - Returns: The value associated with the `NSFileType` key, or `nil` if the dictionary has no entry for the key.
///   For possible values, see `NSFileAttributeType`.
- (nullable NSString *)fileType;
/// Returns the file's POSIX permissions.
///
/// - Returns: The value associated with the `NSFilePosixPermissions` key, or `0` if the dictionary has no entry for the key.
- (NSUInteger)filePosixPermissions;
/// Returns the file's owner account name.
///
/// - Returns: The value associated with the `NSFileOwnerAccountName` key, or `nil` if the dictionary has no entry for the key.
- (nullable NSString *)fileOwnerAccountName;
/// Returns the file's group owner account name.
///
/// - Returns: The value associated with the `NSFileGroupOwnerAccountName` key, or `nil` if the dictionary has no entry for the key.
- (nullable NSString *)fileGroupOwnerAccountName;
/// Returns the filesystem number.
///
/// - Returns: The value associated with the `NSFileSystemNumber` key, or `0` if the dictionary has no entry for the key.
- (NSInteger)fileSystemNumber;
/// Returns the filesystem file number.
///
/// - Returns: The value associated with the `NSFileSystemFileNumber` key, or `0` if the dictionary has no entry for the key.
- (NSUInteger)fileSystemFileNumber;
/// Returns a Boolean value indicating whether the file hides its extension.
///
/// - Returns: The value associated with the `NSFileExtensionHidden` key, or `NO` if the dictionary has no entry for the key.
- (BOOL)fileExtensionHidden;
/// Returns the file's HFS creator code.
///
/// - Returns: The value associated with the `NSFileHFSCreatorCode` key, or `0` if the dictionary has no entry for the key.
- (OSType)fileHFSCreatorCode;
/// Returns the file's HFS type code.
///
/// - Returns: The value associated with the `NSFileHFSTypeCode` key, or `0` if the dictionary has no entry for the key.
- (OSType)fileHFSTypeCode;
/// Returns a Boolean value indicating whether the file is immutable.
///
/// - Returns: The value associated with the `NSFileImmutable` key, or `NO` if the dictionary has no entry for the key.
- (BOOL)fileIsImmutable;
/// Returns a Boolean value indicating whether the file is append only.
///
/// - Returns: The value associated with the `NSFileAppendOnly` key, or `NO` if the dictionary has no entry for the key.
- (BOOL)fileIsAppendOnly;
/// Returns the file's creation date.
///
/// - Returns: The value associated with the `NSFileCreationDate` key, or `nil` if the dictionary has no entry for the key.
- (nullable NSDate *)fileCreationDate;
/// Returns the file's owner account ID.
///
/// - Returns: The value associated with the `NSFileOwnerAccountID` key, or `nil` if the dictionary has no entry for the key.
- (nullable NSNumber *)fileOwnerAccountID;
/// Returns the file's group owner account ID.
///
/// - Returns: The value associated with the `NSFileGroupOwnerAccountID` key, or `nil` if the dictionary has no entry for the key.
- (nullable NSNumber *)fileGroupOwnerAccountID;
@end

NS_HEADER_AUDIT_END(nullability, sendability)
