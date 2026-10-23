/*	NSPathUtilities.h
	Copyright (c) 1994-2019, Apple Inc. All rights reserved.
*/

#import <Foundation/NSString.h>
#import <Foundation/NSArray.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

@interface NSString (NSStringPathExtensions)

/// Returns a string built from the strings in a given array by concatenating them with a path separator between each pair.
///
/// This method doesn't clean up the path created; use ``NSString/standardizingPath`` to resolve empty components, references to the parent directory, and so on.
///
/// - Parameter components: An array of `NSString` objects representing a file path. To create an absolute path, use a slash mark ("`/`") as the first component. To include a trailing path divider, use an empty string as the last component.
/// - Returns: A string built from the strings in `components` by concatenating them (in the order they appear in the array) with a path separator between each pair.
+ (NSString *)pathWithComponents:(NSArray<NSString *> *)components;
/// The file-system path components of the receiver.
///
/// The strings in the array appear in the order they did in the receiver. If the string begins or ends with the path separator, then the first or last component, respectively, will contain the separator. Empty components (caused by consecutive path separators) are deleted.
///
/// This property only works with file paths (not, for example, string representations of URLs).
@property (readonly, copy) NSArray<NSString *> *pathComponents;

/// A Boolean value that indicates whether the receiver represents an absolute path.
///
/// This property only works with file paths (not, for example, string representations of URLs). It does not check the filesystem for the existence of the path.
@property (getter=isAbsolutePath, readonly) BOOL absolutePath;

/// The last path component of the receiver.
///
/// This property only works with file paths (not, for example, string representations of URLs).
@property (readonly, copy) NSString *lastPathComponent;
/// A new string made by deleting the last path component from the receiver, along with any final path separator.
///
/// If the receiver represents the root path it is returned unaltered. This property only works with file paths (not, for example, string representations of URLs).
@property (readonly, copy) NSString *stringByDeletingLastPathComponent;
/// Returns a new string made by appending to the receiver a given string.
///
/// The following table illustrates the effect of this method on a variety of different paths, assuming that `str` is supplied as `"scratch.tiff"`:
///
/// | Receiver's String Value | Resulting String |
/// |---|---|
/// | `"/tmp"` | `"/tmp/scratch.tiff"` |
/// | `"/tmp/"` | `"/tmp/scratch.tiff"` |
/// | `"/"` | `"/scratch.tiff"` |
/// | `""` (an empty string) | `"scratch.tiff"` |
///
/// Note that this method only works with file paths (not, for example, string representations of URLs).
///
/// - Parameter str: The path component to append to the receiver.
/// - Returns: A new string made by appending `str` to the receiver, preceded if necessary by a path separator.
- (NSString *)stringByAppendingPathComponent:(NSString *)str;

/// The path extension, if any, of the string as interpreted as a path.
///
/// The path extension is the portion of the last path component which follows the final period, if there is one. The extension divider is not included. This property only works with file paths (not, for example, string representations of URLs).
@property (readonly, copy) NSString *pathExtension;
/// A new string made by deleting the extension (if any, and only the last) from the receiver.
///
/// Strips any trailing path separator before checking for an extension. If the receiver represents the root path, it is returned unaltered. This property only works with file paths (not, for example, string representations of URLs).
@property (readonly, copy) NSString *stringByDeletingPathExtension;
/// Returns a new string made by appending to the receiver an extension separator followed by a given extension.
///
/// The following table illustrates the effect of this method on a variety of different paths, assuming that `str` is supplied as `"tiff"`:
///
/// | Receiver's String Value | Resulting String |
/// |---|---|
/// | `"/tmp/scratch.old"` | `"/tmp/scratch.old.tiff"` |
/// | `"/tmp/scratch."` | `"/tmp/scratch..tiff"` |
/// | `"/tmp/"` | `"/tmp.tiff"` |
/// | `"scratch"` | `"scratch.tiff"` |
///
/// Note that adding an extension to `"/tmp/"` causes the result to be `"/tmp.tiff"` instead of `"/tmp/.tiff"`. This difference is because a file named `".tiff"` is not considered to have an extension, so the string is appended to the last nonempty path component.
///
/// Note that this method only works with file paths (not, for example, string representations of URLs).
///
/// - Parameter str: The extension to append to the receiver.
/// - Returns: A new string made by appending to the receiver an extension separator followed by `str`.
- (nullable NSString *)stringByAppendingPathExtension:(NSString *)str;

/// A new string that replaces the current home directory portion of the current path with a tilde (`~`) character.
///
/// If the string does not specify a file in the current home directory, the path is unchanged. This property only works with file paths (not, for example, string representations of URLs).
@property (readonly, copy) NSString *stringByAbbreviatingWithTildeInPath;
/// A new string made by expanding the initial component of the receiver to its full path value.
///
/// Expands an initial "`~`" or "`~user`" component to its full path value. Returns a new string matching the receiver if the initial component can't be expanded. This property only works with file paths (not, for example, string representations of URLs).
@property (readonly, copy) NSString *stringByExpandingTildeInPath;

/// A new string made by removing extraneous path components from the receiver.
///
/// Expands an initial tilde expression, reduces empty components and "`/./`" sequences to single path separators, and resolves "`..`" references in absolute paths. Returns `self` if an error occurs. This property only works with file paths (not, for example, string representations of URLs).
@property (readonly, copy) NSString *stringByStandardizingPath;

/// A new string made from the receiver by resolving all symbolic links and standardizing path.
///
/// For absolute paths, all symbolic links are guaranteed to be removed. For relative paths, symbolic links that can't be resolved are left unresolved. Returns `self` if an error occurs. This property only works with file paths (not, for example, string representations of URLs).
@property (readonly, copy) NSString *stringByResolvingSymlinksInPath;

/// Returns an array of strings made by separately appending to the receiver each string in a given array.
///
/// Note that this method only works with file paths (not, for example, string representations of URLs). See ``NSString/appendingPathComponent(_:)`` for an individual example.
///
/// - Parameter paths: An array of `NSString` objects specifying paths to add to the receiver.
/// - Returns: An array of string objects made by separately appending each string in `paths` to the receiver, preceded if necessary by a path separator.
- (NSArray<NSString *> *)stringsByAppendingPaths:(NSArray<NSString *> *)paths;

#if !0
/// Interprets the receiver as a path in the file system and attempts to perform filename completion, returning a numeric value that indicates whether a match was possible, and by reference the longest path that matches the receiver.
///
/// You can check for the existence of matches without retrieving by passing `NULL` as `outputArray`.
///
/// Note that this method only works with file paths (not, for example, string representations of URLs).
///
/// - Parameters:
///   - outputName: Upon return, contains the longest path that matches the receiver.
///   - flag: If `true`, the method considers case for possible completions.
///   - outputArray: Upon return, contains all matching filenames.
///   - filterTypes: An array of `NSString` objects specifying path extensions to consider for completion. Only paths whose extensions (not including the extension separator) match one of these strings are included in `outputArray`. Pass `nil` if you don't want to filter the output.
/// - Returns: `0` if no matches are found and `1` if exactly one match is found. In the case of multiple matches, returns the actual number of matching paths if `outputArray` is provided, or simply a positive value if `outputArray` is `NULL`.
- (NSUInteger)completePathIntoString:(NSString * _Nullable * _Nullable)outputName caseSensitive:(BOOL)flag matchesIntoArray:(NSArray<NSString *> * _Nullable * _Nullable)outputArray filterTypes:(nullable NSArray<NSString *> *)filterTypes;
#endif 

/// A file system-specific representation of the receiver.
///
/// The returned C string will be automatically freed just as a returned object would be released; your code should copy the representation or use ``NSString/getFileSystemRepresentation(_:maxLength:)`` if it needs to store it outside of the autorelease context. Raises ``NSExceptionName/characterConversionException`` if the receiver can't be represented in the file system's encoding.
@property (readonly) const char *fileSystemRepresentation NS_RETURNS_INNER_POINTER;
/// Interprets the receiver as a system-independent path and fills a buffer with a C-string in a format and encoding suitable for use with file-system calls.
///
/// This method operates by replacing the abstract path and extension separator characters ('`/`' and '`.`' respectively) with their equivalents for the operating system. If the system-specific path or extension separator appears in the abstract representation, the characters it is converted to depend on the system (unless they're identical to the abstract separators).
///
/// Note that this method only works with file paths (not, for example, string representations of URLs).
///
/// The following example illustrates the use of the `max` argument. The first method invocation returns failure as the file representation of the string (`@"/mach_kernel"`) is 12 bytes long and the value passed as the `max` argument (`12`) does not allow for the addition of a `NULL` termination byte.
///
/// ```objc
/// char filenameBuffer[13];
/// BOOL success;
/// success = [@"/mach_kernel" getFileSystemRepresentation:filenameBuffer maxLength:12];
/// // success == NO
/// // Changing the length to include the NULL character does work
/// success = [@"/mach_kernel" getFileSystemRepresentation:filenameBuffer maxLength:13];
/// // success == YES
/// ```
///
/// - Parameters:
///   - cname: Upon return, contains a C-string that represents the receiver as a system-independent path, plus the `NULL` termination byte. The size of the buffer must be large enough to contain `max` bytes.
///   - max: The maximum number of bytes in the string to return in `cname` (including a terminating `NULL` character, which this method adds).
/// - Returns: `true` if `cname` is successfully filled with a file-system representation, otherwise `false` (for example, if `max` would be exceeded or if the receiver can't be represented in the file system's encoding).
- (BOOL)getFileSystemRepresentation:(char *)cname maxLength:(NSUInteger)max;

@end

@interface NSArray<ObjectType> (NSArrayPathExtensions)

/// Returns an array containing all the pathname elements in the receiving array that have filename extensions from a given array.
///
/// - Parameter filterTypes: An array of `NSString` objects containing filename extensions. The extensions should not include the dot (`.`) character.
/// - Returns: An array containing all the pathname elements in the receiving array that have filename extensions from the `filterTypes` array.
- (NSArray<NSString *> *)pathsMatchingExtensions:(NSArray<NSString *> *)filterTypes;

@end

#if !0
/// Returns the logon name of the current user.
FOUNDATION_EXPORT NSString *NSUserName(void);
/// Returns a string containing the full name of the current user.
FOUNDATION_EXPORT NSString *NSFullUserName(void);

/// Returns the path to either the user's or application's home directory, depending on the platform.
FOUNDATION_EXPORT NSString *NSHomeDirectory(void);
/// Returns the path to a given user's home directory.
FOUNDATION_EXPORT NSString * _Nullable NSHomeDirectoryForUser(NSString * _Nullable userName);

/// Returns the path of the temporary directory for the current user.
FOUNDATION_EXPORT NSString *NSTemporaryDirectory(void);

/// Returns the root directory of the user's system.
FOUNDATION_EXPORT NSString *NSOpenStepRootDirectory(void);
#endif 

/// The location of significant directories.
///
/// Use these constants with the ``URL/init(for:in:appropriateFor:create:)`` initializer and the ``FileManager/urls(for:in:)`` and ``FileManager/url(for:in:appropriateFor:create:)`` methods of FileManager.
typedef NS_ENUM(NSUInteger, NSSearchPathDirectory) {
    /// Supported applications (`/Applications`).
    NSApplicationDirectory = 1,
    /// Unsupported applications and demonstration versions.
    NSDemoApplicationDirectory,
    /// Developer applications (`/Developer/Applications`).
    ///
    /// Deprecated: As of Xcode 4.3, there is no longer a Developer Application directory directory; instead, Xcode.app is a self-contained application that gets installed in the user's Applications directory, by default, although it can be put anywhere.
    NSDeveloperApplicationDirectory,
    /// System and network administration applications.
    NSAdminApplicationDirectory,
    /// Various user-visible documentation, support, and configuration files (`/Library`).
    NSLibraryDirectory,
    /// Developer resources (`/Developer`).
    ///
    /// Deprecated: As of Xcode 4.3, there is no longer a Developer directory; instead, Xcode.app is a self-contained application that gets installed in the user's Applications directory, by default, although it can be put anywhere.
    NSDeveloperDirectory,
    /// User home directories (`/Users`).
    NSUserDirectory,
    /// Documentation.
    NSDocumentationDirectory,
    /// Document directory.
    NSDocumentDirectory,
    /// Core services (`System/Library/CoreServices`).
    NSCoreServiceDirectory,
    /// The user's autosaved documents (`Library/Autosave Information`).
    NSAutosavedInformationDirectory API_AVAILABLE(macos(10.6), ios(4.0), watchos(2.0), tvos(9.0)) = 11,
    /// The user's desktop directory.
    NSDesktopDirectory = 12,
    /// Discardable cache files (`Library/Caches`).
    NSCachesDirectory = 13,
    /// Application support files (`Library/Application Support`).
    NSApplicationSupportDirectory = 14,
    /// The user's downloads directory.
    ///
    /// The `NSDownloadsDirectory` flag only produces a path when you provide a `NSUserDomainMask`.
    NSDownloadsDirectory API_AVAILABLE(macos(10.5), ios(2.0), watchos(2.0), tvos(9.0)) = 15,
    /// Input Methods (`Library/Input Methods`).
    NSInputMethodsDirectory API_AVAILABLE(macos(10.6), ios(4.0), watchos(2.0), tvos(9.0)) = 16,
    /// The user's Movies directory (`~/Movies`).
    NSMoviesDirectory API_AVAILABLE(macos(10.6), ios(4.0), watchos(2.0), tvos(9.0)) = 17,
    /// The user's Music directory (`~/Music`).
    NSMusicDirectory API_AVAILABLE(macos(10.6), ios(4.0), watchos(2.0), tvos(9.0)) = 18,
    /// The user's Pictures directory (`~/Pictures`).
    NSPicturesDirectory API_AVAILABLE(macos(10.6), ios(4.0), watchos(2.0), tvos(9.0)) = 19,
    /// The system's PPDs directory (`Library/Printers/PPDs`).
    NSPrinterDescriptionDirectory API_AVAILABLE(macos(10.6), ios(4.0), watchos(2.0), tvos(9.0)) = 20,
    /// The user's Public sharing directory (`~/Public`).
    NSSharedPublicDirectory API_AVAILABLE(macos(10.6), ios(4.0), watchos(2.0), tvos(9.0)) = 21,
    /// The PreferencePanes directory for use with System Preferences (`Library/PreferencePanes`).
    NSPreferencePanesDirectory API_AVAILABLE(macos(10.6), ios(4.0), watchos(2.0), tvos(9.0)) = 22,
    /// The user scripts folder for the calling application (`~/Library/Application Scripts/<code-signing-id>`).
    NSApplicationScriptsDirectory API_AVAILABLE(macos(10.8)) API_UNAVAILABLE(ios, watchos, tvos) = 23,
    /// The constant used to create a temporary directory.
    ///
    /// Pass this constant to the `NSFileManager` method `URLForDirectory:inDomain:appropriateForURL:create:error:` in order to create a temporary directory.
    NSItemReplacementDirectory API_AVAILABLE(macos(10.6), ios(4.0), watchos(2.0), tvos(9.0)) = 99,
    /// All directories where applications can be stored.
    NSAllApplicationsDirectory = 100,
    /// All directories where resources can be stored.
    NSAllLibrariesDirectory = 101,
    /// The trash directory.
    NSTrashDirectory API_AVAILABLE(macos(10.8), ios(11.0)) API_UNAVAILABLE(watchos, tvos) = 102

};

/// Domain constants specifying base locations to use when you search for significant directories.
///
/// These constants are used by the ``FileManager/urls(for:in:)`` and ``FileManager/url(for:in:appropriateFor:create:)`` methods of ``FileManager``.
typedef NS_OPTIONS(NSUInteger, NSSearchPathDomainMask) {
    /// The user's home directory---the place to install user's personal items (`~`).
    NSUserDomainMask = 1,
    /// The place to install items available to everyone on this machine.
    NSLocalDomainMask = 2,
    /// The place to install items available on the network (`/Network`).
    NSNetworkDomainMask = 4,
    /// A directory for system files provided by Apple (`/System`).
    ///
    /// This directory can't be modified.
    NSSystemDomainMask = 8,
    /// All domains.
    ///
    /// Includes all of the above and future items.
    NSAllDomainsMask = 0x0ffff
};

#if !0
/// Creates a list of directory search paths.
FOUNDATION_EXPORT NSArray<NSString *> *NSSearchPathForDirectoriesInDomains(NSSearchPathDirectory directory, NSSearchPathDomainMask domainMask, BOOL expandTilde);
#endif 

NS_HEADER_AUDIT_END(nullability, sendability)
