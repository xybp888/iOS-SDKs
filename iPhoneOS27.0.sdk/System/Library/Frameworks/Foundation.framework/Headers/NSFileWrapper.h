/*
	NSFileWrapper.h
	Copyright (c) 1995-2019, Apple Inc. All rights reserved.
*/

#import <Foundation/NSObject.h>

@class NSData, NSDictionary<KeyType, ObjectType>, NSError, NSString, NSURL;

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

/// Reading options that can be set by the -initWithURL:options:error: and -readFromURL:options:error: methods.
///
/// You can use the NSFileWrapperReadingImmediate and NSFileWrapperReadingWithoutMapping reading options together to take an exact snapshot of a file-system hierarchy that is safe from all errors (including the ones mentioned above) once reading has succeeded. If reading with both options succeeds, then subsequent invocations of the methods listed in the comment for the NSFileWrapperReadingImmediate reading option to the receiver and all its descendant file wrappers will never fail. However, note that reading with both options together is expensive in terms of both I/O and memory for large files, or directories containing large files, or even directories containing many small files.
typedef NS_OPTIONS(NSUInteger, NSFileWrapperReadingOptions) {

    /// Whether the contents are read immediately, applied recursively in the case of directory file wrappers. If reading with this option succeeds then subsequent invocations of -fileWrappers, -regularFileContents, -symbolicLinkDestinationURL:, -serializedRepresentation, and, on Mac OS X, -[NSFileWrapper(NSExtensions) icon] sent to the receiver and all its descendant file wrappers won't fail. For performance NSFileWrapper may or may not immediately read the contents of some file packages immediately even when this option is chosen. For example, the contents of bundles (not all file packages are bundles) are immutable to the user so on Mac OS X NSFileWrapper may read the children of such a directory lazily. You can use this option to take a reasonable snapshot of a file or folder for writing later. For example, a Mac OS X application like TextEdit can use this option when creating new file wrappers to represent attachments that the user creates by copying and pasting or dragging and dropping from the Finder to a TextEdit document. You wouldn't use this option when reading a document file package because that would cause unnecessarily bad perfomance. For example, an application wouldn't use this option when creating file wrappers to represent attachments as it's opening a document stored in a file package.
    NSFileWrapperReadingImmediate = 1 << 0,

    /// Whether file mapping for regular file wrappers is disallowed. In Mac OS 10.6 and newer NSFileWrapper only ever memory maps files on internal drives, regardless of whether this option is used. It never memory maps files on external drives or network volumes. You can use this option to keep NSFileWrapper from memory mapping files at all, even ones on internal drives. This is useful if you want to make sure your application doesn't hold files open (mapped files are open files) and therefore prevent the user from ejecting DVDs, unmounting disk partitions, or unmounting disk images.
    NSFileWrapperReadingWithoutMapping = 1 << 1

} API_AVAILABLE(macos(10.6), ios(4.0), watchos(2.0), tvos(9.0));

/// Writing options that can be set by the -writeToURL:options:originalContentsURL:error: method.
typedef NS_OPTIONS(NSUInteger, NSFileWrapperWritingOptions) {

    /// Whether writing is done atomically.
    ///
    /// You can use this option to ensure that, when overwriting a file package, the overwriting either completely succeeds or completely fails, with no possibility of leaving the file package in an inconsistent state. Because this option causes additional I/O, you shouldn't use it unnecessarily. For example, don't use this option in an override of `-[NSDocument writeToURL:ofType:error:]`, because `NSDocument` safe-saving is already done atomically.
    NSFileWrapperWritingAtomic = 1 << 0,

    /// Whether descendant file wrappers are sent -setFilename: if the writing succeeds. This is necessary when your application passes original contents URLs to -writeToURL:options:originalContentsURL:error:. Without using this and reusing child file wrappers properly subsequent invocations of -writeToURL:options:originalContentsURL:error: wouldn't be able to reliably create hard links in a new file package for performance because the record of names in the old file package would be out of date.
    NSFileWrapperWritingWithNameUpdating = 1 << 1

} API_AVAILABLE(macos(10.6), ios(4.0), watchos(2.0), tvos(9.0));

/// A representation of a node (a file, directory, or symbolic link) in the file system.
///
/// The ``FileWrapper`` class provides access to the attributes and contents of file system nodes. A file system node is a file, directory, or symbolic link. Instances of this class are known as file wrappers.
///
/// > Note:
/// > Starting in macOS 10.7, ``FileWrapper`` moved from Application Kit to Foundation. As a result of this the `icon`, and `setIcon:` methods have moved to a new category of ``FileWrapper`` that remains in Application Kit.
///
/// File wrappers represent a file system node as an object that can be displayed as an image (and possibly edited in place), saved to the file system, or transmitted to another application.
///
/// There are three types of file wrappers:
///
/// - Regular-file file wrapper: Represents a regular file.
/// - Directory file wrapper: Represents a directory.
/// - Symbolic-link file wrapper: Represents a symbolic link.
///
/// A file wrapper has these attributes:
///
/// - Filename. Name of the file system node the file wrapper represents.
/// - file-system attributes. See ``FileManager`` for information on the contents of the `attributes` dictionary.
/// - Regular-file contents. Applicable only to regular-file file wrappers.
/// - File wrappers. Applicable only to directory file wrappers.
/// - Destination node. Applicable only to symbolic-link file wrappers.
API_AVAILABLE(macos(10.0), ios(4.0), watchos(2.0), tvos(9.0))
@interface NSFileWrapper : NSObject<NSSecureCoding>

#pragma mark *** Initialization ***

/// Initializes a file wrapper instance whose kind is determined by the type of file-system node located by the URL.
///
/// If `url` is a directory, this method recursively creates file wrappers for each node within that directory. Use the `fileWrappers` property to get the file wrappers of the nodes contained by the directory.
///
/// - Parameters:
///   - url: URL of the file-system node the file wrapper is to represent.
///   - options: Option flags for reading the node located at `url`. See `NSFileWrapperReadingOptions` for possible values.
///   - outError: If an error occurs, upon return contains an `NSError` object that describes the problem. Pass `NULL` if you do not want error information.
/// - Returns: File wrapper for the file-system node at `url`. May be a directory, file, or symbolic link, depending on what is located at the URL. Returns `nil` if reading is not successful.
- (nullable instancetype)initWithURL:(NSURL *)url options:(NSFileWrapperReadingOptions)options error:(NSError **)outError NS_DESIGNATED_INITIALIZER API_AVAILABLE(macos(10.6), ios(4.0), watchos(2.0), tvos(9.0));

/// Initializes the receiver as a directory file wrapper, with a given file-wrapper list.
///
/// After initialization, the file wrapper is not associated with a file-system node until you save it using -writeToURL:options:originalContentsURL:error:. The receiver is initialized with open permissions: anyone can read, write, or modify the directory on disk.
///
/// If any file wrapper in the directory doesn't have a preferred filename, its preferred name is automatically set to its corresponding key in the `childrenByPreferredName` dictionary.
///
/// - Parameter childrenByPreferredName: Key-value dictionary of file wrappers with which to initialize the receiver. The dictionary must contain entries whose values are the file wrappers that are to become children and whose keys are filenames.
/// - Returns: Initialized file wrapper for `fileWrappers`.
- (instancetype)initDirectoryWithFileWrappers:(NSDictionary<NSString *, NSFileWrapper *> *)childrenByPreferredName NS_DESIGNATED_INITIALIZER;

/// Initializes the receiver as a regular-file file wrapper.
///
/// After initialization, the file wrapper is not associated with a file-system node until you save it using -writeToURL:options:originalContentsURL:error:. The file wrapper is initialized with open permissions: anyone can write to or read the file wrapper.
///
/// - Parameter contents: Contents of the file.
/// - Returns: Initialized regular-file file wrapper containing `contents`.
- (instancetype)initRegularFileWithContents:(NSData *)contents NS_DESIGNATED_INITIALIZER;

/// Initializes the receiver as a symbolic-link file wrapper that links to a specified file.
///
/// The file wrapper is not associated with a file-system node until you save it using -writeToURL:options:originalContentsURL:error:. The file wrapper is initialized with open permissions: anyone can modify or read the file reference.
///
/// - Parameter url: URL of the file the file wrapper is to reference.
/// - Returns: Initialized symbolic-link file wrapper referencing `url`.
- (instancetype)initSymbolicLinkWithDestinationURL:(NSURL *)url NS_DESIGNATED_INITIALIZER API_AVAILABLE(macos(10.6), ios(4.0), watchos(2.0), tvos(9.0));

/// Initializes the receiver as a regular-file file wrapper from given serialized data.
///
/// The file wrapper is not associated with a file-system node until you save it using -writeToURL:options:originalContentsURL:error:.
///
/// - Parameter serializeRepresentation: Serialized representation of a file wrapper in the format used for the `NSFileContentsPboardType` pasteboard type.
/// - Returns: Regular-file file wrapper initialized from `serializedRepresentation`.
- (nullable instancetype)initWithSerializedRepresentation:(NSData *)serializeRepresentation NS_DESIGNATED_INITIALIZER;

- (nullable instancetype)initWithCoder:(NSCoder *)inCoder NS_DESIGNATED_INITIALIZER;

#pragma mark *** Properties Applicable to Every Kind of File Wrapper ***

/// This property contains a boolean value indicating whether the file wrapper is a directory file wrapper.
///
/// Invocations of -readFromURL:options:error: may change the value of this property, if the type of the file on disk has changed.
@property (readonly, getter=isDirectory) BOOL directory;

/// This property contains a boolean value that indicates whether the file wrapper object is a regular-file.
///
/// Invocations of -readFromURL:options:error: may change the value of this property if the type of the file on disk has changed.
@property (readonly, getter=isRegularFile) BOOL regularFile;

/// A boolean that indicates whether the file wrapper object is a symbolic-link file wrapper.
///
/// Invocations of -readFromURL:options:error: may change the value contained by this property, if the type of the file on disk has changed.
@property (readonly, getter=isSymbolicLink) BOOL symbolicLink;

/// The preferred filename for the file wrapper object.
///
/// This name is normally used as the dictionary key when a child file wrapper is added to a directory file wrapper. However, if another file wrapper with the same preferred name already exists in the directory file wrapper when this object is added, the filename assigned as the dictionary key may differ from the preferred filename.
///
/// When you change the preferred filename, the default implementation of this property causes the existing parent directory file wrappers to remove and re-add the child to accommodate the change. Preferred filenames of children are not preserved when you write a file wrapper to disk and then later instantiate another file wrapper by reading the file from disk. If you need to preserve the user-visible names of attachments, you have to store the names yourself.
///
/// Some instances of NSFileWrapper may be created without a preferredFilename (e.g. -initDirectoryWithFileWrappers: or -initRegularFileWithContents:), meaning preferredFilename may be nil. However, setting nil is never allowed and will result in an exception.
@property (nullable, copy) NSString *preferredFilename;

/// The filename of the file wrapper object.
///
/// This property contains the file wrapper's filename, or `nil` when the file wrapper has no corresponding file-system node.
///
/// The filename is used for record-keeping purposes only and is set automatically when the file wrapper is created from the file system using -initWithURL:options:error: and when it's saved to the file system using -writeToURL:options:originalContentsURL:error: (although this method allows you to request that the filename not be updated).
///
/// The filename is usually the same as the preferred filename, but might instead be a name derived from the preferred filename. You can use this method to get the name of a child that's just been read. Don't use this method to get the name of a child that's about to be written, because the name might be about to change; send -keyForFileWrapper: to the parent instead.
@property (nullable, copy) NSString *filename;

/// A dictionary of file attributes.
///
/// The file attributes' dictionary is the same format as that returned by -[NSFileManager attributesOfItemAtPath:error:].
@property (copy) NSDictionary<NSString *, id> *fileAttributes;

/* On Mac OS X methods for setting and getting the icon are in AppKit's NSFileWrapper(NSExtensions), declared in <AppKit/NSFileWrapperExtensions.h>.
*/

#pragma mark *** Reading ***

/// Indicates whether the contents of a file wrapper matches a directory, regular file, or symbolic link on disk.
///
/// The contents of files are not compared; matching of regular files is based on file modification dates. For a directory, children are compared against the files in the directory, recursively.
///
/// Because children of directory file wrappers are not read immediately by the -initWithURL:options:error: method unless the NSFileWrapperReadingImmediate reading option is used, even a newly-created directory file wrapper might not have the same contents as the directory on disk. You can use this method to determine whether the file wrapper's contents in memory need to be updated.
///
/// If the file wrapper needs updating, use the -readFromURL:options:error: method with the NSFileWrapperReadingImmediate reading option.
///
/// - Parameter url: URL of the file-system node with which to compare the file wrapper.
/// - Returns: `YES` when the contents of the file wrapper match the contents of `url`, `NO` otherwise.
- (BOOL)matchesContentsOfURL:(NSURL *)url API_AVAILABLE(macos(10.6), ios(4.0), watchos(2.0), tvos(9.0));

/// Recursively rereads the entire contents of a file wrapper from the specified location on disk.
///
/// When reading a directory, children are added and removed as necessary to match the file system.
///
/// - Parameters:
///   - url: URL of the file-system node corresponding to the file wrapper.
///   - options: Option flags for reading the node located at `url`. See `NSFileWrapperReadingOptions` for possible values.
///   - outError: If an error occurs, upon return contains an `NSError` object that describes the problem. Pass `NULL` if you do not want error information.
/// - Returns: `YES` if successful. If not successful, returns `NO` after setting `outError` to an `NSError` object that describes the reason why the file wrapper could not be reread.
- (BOOL)readFromURL:(NSURL *)url options:(NSFileWrapperReadingOptions)options error:(NSError **)outError API_AVAILABLE(macos(10.6), ios(4.0), watchos(2.0), tvos(9.0));

#pragma mark *** Writing ***

/// Recursively writes the entire contents of a file wrapper to a given file-system URL.
///
/// - Parameters:
///   - url: URL of the file-system node to which the file wrapper's contents are written.
///   - options: Option flags for writing to the node located at `url`. See `NSFileWrapperWritingOptions` for possible values.
///   - originalContentsURL: The location of a previous revision of the contents being written. The default implementation of this method attempts to avoid unnecessary I/O by writing hard links to regular files instead of actually writing out their contents when the contents have not changed. The child file wrappers must return accurate values when sent -filename for this to work. Use the NSFileWrapperWritingWithNameUpdating writing option to increase the likelihood of that. Specify `nil` for this parameter if there is no earlier version of the contents or if you want to ensure that all the contents are written to files.
///   - outError: If an error occurs, upon return contains an `NSError` object that describes the problem. Pass `NULL` if you do not want error information.
/// - Returns: `YES` when the write operation is successful. If not successful, returns `NO` after setting `outError` to an `NSError` object that describes the reason why the file wrapper's contents could not be written.
- (BOOL)writeToURL:(NSURL *)url options:(NSFileWrapperWritingOptions)options originalContentsURL:(nullable NSURL *)originalContentsURL error:(NSError **)outError API_AVAILABLE(macos(10.6), ios(4.0), watchos(2.0), tvos(9.0));

#pragma mark *** Serialization ***

/// The contents of the file wrapper as an opaque data object.
///
/// This property contains a data object in the format used by the NSFileContentsPboardType pasteboard type. This data object is also suitable for passing to -initWithSerializedRepresentation:.
///
/// This property may be `nil` if the user modifies the contents of the file system node after you call -readFromURL:options:error: or -initWithURL:options:error:, but before NSFileWrapper has read the contents of the file. You can use the NSFileWrapperReadingImmediate reading option to reduce the likelihood of this problem.
@property (nullable, readonly, copy) NSData *serializedRepresentation;

#pragma mark *** Directories ***

/* Each of these methods throw an exception when [receiver isDirectory]==NO. */

/// Adds a child file wrapper to the receiver, which must be a directory file wrapper.
///
/// Use this method to add an existing file wrapper as a child of a directory file wrapper. If the file wrapper does not have a preferred filename, set the `preferredFilename` property to give it one before calling -addFileWrapper:. To create a new file wrapper and add it to a directory, use the -addRegularFileWithContents:preferredFilename: method.
///
/// This method raises `NSInternalInconsistencyException` if the receiver is not a directory file wrapper.
/// This method raises `NSInvalidArgumentException` if the child file wrapper doesn't have a preferred name.
///
/// - Parameter child: File wrapper to add to the directory.
/// - Returns: Dictionary key used to store `fileWrapper` in the directory's list of file wrappers. The dictionary key is a unique filename, which is the same as the passed-in file wrapper's preferred filename unless that name is already in use as a key in the directory's dictionary of children.
- (NSString *)addFileWrapper:(NSFileWrapper *)child;

/// Creates a regular-file file wrapper with the given contents and adds it to the receiver, which must be a directory file wrapper.
///
/// This is a convenience method. The default implementation allocates a new file wrapper, initializes it with -initRegularFileWithContents:, sets its preferred filename, adds it to the directory with -addFileWrapper:, and returns what -addFileWrapper: returned.
///
/// This method raises `NSInternalInconsistencyException` if the receiver is not a directory file wrapper.
/// This method raises `NSInvalidArgumentException` if you pass `nil` or an empty value for `filename`.
///
/// - Parameters:
///   - data: Contents for the new regular-file file wrapper.
///   - fileName: Preferred filename for the new regular-file file wrapper.
/// - Returns: Dictionary key used to store the new file wrapper in the directory's list of file wrappers. The dictionary key is a unique filename, which is the same as the passed-in file wrapper's preferred filename unless that name is already in use as a key in the directory's dictionary of children.
- (NSString *)addRegularFileWithContents:(NSData *)data preferredFilename:(NSString *)fileName;

/// Removes a child file wrapper from the receiver, which must be a directory file wrapper.
///
/// This method raises `NSInternalInconsistencyException` if the receiver is not a directory file wrapper.
///
/// - Parameter child: File wrapper to remove from the directory.
- (void)removeFileWrapper:(NSFileWrapper *)child;

/// The file wrappers contained by a directory file wrapper.
///
/// The dictionary contains entries whose values are the file wrappers and whose keys are the unique filenames that have been assigned to each one.
///
/// This property may contain `nil` if the user modifies the directory after you call -readFromURL:options:error: or -initWithURL:options:error: but before NSFileWrapper has read the contents of the directory. Use the NSFileWrapperReadingImmediate reading option to reduce the likelihood of that problem.
///
/// This property raises `NSInternalInconsistencyException` if the file wrapper object is not a directory file wrapper.
@property (nullable, readonly, copy) NSDictionary<NSString *, NSFileWrapper *> *fileWrappers;

/// Returns the dictionary key used by a directory to identify a given file wrapper.
///
/// The dictionary key is a unique filename, which may not be the same as the passed-in file wrapper's preferred filename if more than one file wrapper in the directory's dictionary of children has the same preferred filename. Returns `nil` if the file wrapper specified in `child` is not a child of the directory.
///
/// This method raises `NSInternalInconsistencyException` if the receiver is not a directory file wrapper.
///
/// - Parameter child: The child file wrapper for which you want the key.
/// - Returns: Dictionary key used to store the file wrapper in the directory's list of file wrappers.
- (nullable NSString *)keyForFileWrapper:(NSFileWrapper *)child;

#pragma mark *** Regular Files ***

/* This method throws an exception when [receiver isRegularFile]==NO. */

/// The contents of the file-system node associated with a regular-file file wrapper.
///
/// This property may contain `nil` if the user modifies the file after you call -readFromURL:options:error: or -initWithURL:options:error: but before NSFileWrapper has read the contents of the file. Use the NSFileWrapperReadingImmediate reading option to reduce the likelihood of that problem.
///
/// This property raises `NSInternalInconsistencyException` if the file wrapper object is not a regular-file file wrapper.
@property (nullable, readonly, copy) NSData *regularFileContents;

#pragma mark *** Symbolic Links ***

/* This method throws an exception when [receiver isSymbolicLink]==NO. */

/// The URL referenced by the file wrapper object, which must be a symbolic-link file wrapper.
///
/// This property may contain `nil` if the user modifies the symbolic link after you call -readFromURL:options:error: or -initWithURL:options:error: but before NSFileWrapper has read the contents of the link. Use the NSFileWrapperReadingImmediate reading option to reduce the likelihood of that problem.
///
/// This property raises `NSInternalInconsistencyException` if the file wrapper object is not a symbolic-link file wrapper.
@property (nullable, readonly, copy) NSURL *symbolicLinkDestinationURL API_AVAILABLE(macos(10.6), ios(4.0), watchos(2.0), tvos(9.0));

@end

#if TARGET_OS_OSX

@interface NSFileWrapper(NSDeprecated)

#pragma mark *** Backward Compatibility ***

/* Methods that were deprecated in OS X 10.6 and never available on iOS. */

/// Initializes a file wrapper instance whose kind is determined by the type of file-system node located by the path.
///
/// If `node` is a directory, this method recursively creates file wrappers for each node within that directory.
///
/// @deprecated Use -initWithURL:options:error: instead.
///
/// - Parameter path: Pathname of the file-system node the file wrapper is to represent.
/// - Returns: File wrapper for `node`.
- (nullable id)initWithPath:(NSString *)path API_DEPRECATED("Use -initWithURL:options:error: instead.", macos(10.0,10.10)) API_UNAVAILABLE(ios, watchos, tvos);

/// Initializes the receiver as a symbolic-link file wrapper.
///
/// The receiver is not associated to a file-system node until you save it using -writeToFile:atomically:updateFilenames:. It's also initialized with open permissions; anyone can read or write the disk representations it saves.
///
/// @deprecated Use -initSymbolicLinkWithDestinationURL: and -setPreferredFileName:, if necessary, instead.
///
/// - Parameter path: Pathname the receiver is to represent.
/// - Returns: Initialized symbolic-link file wrapper referencing `node`.
- (id)initSymbolicLinkWithDestination:(NSString *)path API_DEPRECATED("Use -initSymbolicLinkWithDestinationURL: and -setPreferredFileName:, if necessary, instead.", macos(10.0,10.10)) API_UNAVAILABLE(ios, watchos, tvos);

/// Indicates whether the file wrapper needs to be updated to match a given file-system node.
///
/// @deprecated Use -matchesContentsOfURL: instead.
///
/// - Parameter path: File-system node with which to compare the file wrapper.
/// - Returns: `YES` when the file wrapper needs to be updated to match `node`, `NO` otherwise.
- (BOOL)needsToBeUpdatedFromPath:(NSString *)path API_DEPRECATED("Use -matchesContentsOfURL: instead.", macos(10.0,10.10)) API_UNAVAILABLE(ios, watchos, tvos);

/// Updates the file wrapper to match a given file-system node.
///
/// For a directory file wrapper, the contained file wrappers are also sent -updateFromPath: messages. If nodes in the corresponding directory on the file system have been added or removed, corresponding file wrappers are released or created as needed.
///
/// @deprecated Use -readFromURL:options:error: instead.
///
/// - Returns: `YES` if the update is carried out, `NO` if it isn't needed.
- (BOOL)updateFromPath:(NSString *)path API_DEPRECATED("Use -readFromURL:options:error: instead.", macos(10.0,10.10)) API_UNAVAILABLE(ios, watchos, tvos);

/// Writes a file wrapper's contents to a given file-system node.
///
/// @deprecated Use -writeToURL:options:originalContentsURL:error: instead.
///
/// - Parameters:
///   - path: Pathname of the file-system node to which the receiver's contents are written.
///   - atomicFlag: `YES` to write the file safely so that an existing file is not overwritten and the method fails if the file cannot be written in its entirety. `NO` to overwrite an existing file and ignore incomplete writes.
///   - updateFilenamesFlag: `YES` to update the receiver's filenames (its filename and -- for directory file wrappers -- the filenames of its sub-file wrappers) to the filenames of the corresponding nodes in the file system, after a successful write operation. `NO` to specify that the receiver's filenames not be updated.
/// - Returns: `YES` when the write operation is successful, `NO` otherwise.
- (BOOL)writeToFile:(NSString *)path atomically:(BOOL)atomicFlag updateFilenames:(BOOL)updateFilenamesFlag API_DEPRECATED("Use -writeToURL:options:originalContentsURL:error: instead.", macos(10.0,10.10)) API_UNAVAILABLE(ios, watchos, tvos);

/// Creates a file wrapper from a given file-system node and adds it to the receiver, which must be a directory file wrapper.
///
/// @deprecated Instantiate a new NSFileWrapper with -initWithURL:options:error:, send it -setPreferredFileName: if necessary, then use -addFileWrapper: instead.
///
/// This method raises `NSInternalInconsistencyException` if the receiver is not a directory file wrapper.
///
/// - Parameter path: File-system node from which to create the file wrapper to add to the directory.
/// - Returns: Dictionary key used to store the new file wrapper in the directory's list of file wrappers.
- (NSString *)addFileWithPath:(NSString *)path API_DEPRECATED("Instantiate a new NSFileWrapper with -initWithURL:options:error:, send it -setPreferredFileName: if necessary, then use -addFileWrapper: instead.", macos(10.0,10.10)) API_UNAVAILABLE(ios, watchos, tvos);

/// Creates a symbolic-link file wrapper pointing to a given file-system node and adds it to the receiver, which must be a directory file wrapper.
///
/// @deprecated Instantiate a new NSFileWrapper with -initWithSymbolicLinkDestinationURL:, send it -setPreferredFileName: if necessary, then use -addFileWrapper: instead.
///
/// This method raises `NSInternalInconsistencyException` if the receiver is not a directory file wrapper.
/// This method raises `NSInvalidArgumentException` if you pass `nil` or an empty value for `preferredFilename`.
///
/// - Parameters:
///   - path: Pathname the new symbolic-link file wrapper is to reference.
///   - filename: Preferred filename for the new symbolic-link file wrapper.
/// - Returns: Dictionary key used to store the new file wrapper in the directory's list of file wrappers.
- (NSString *)addSymbolicLinkWithDestination:(NSString *)path preferredFilename:(NSString *)filename API_DEPRECATED("Instantiate a new NSFileWrapper with -initWithSymbolicLinkDestinationURL:, send it -setPreferredFileName: if necessary, then use -addFileWrapper: instead.", macos(10.0,10.10)) API_UNAVAILABLE(ios, watchos, tvos);

/// Provides the pathname referenced by the file wrapper object, which must be a symbolic-link file wrapper.
///
/// This method raises `NSInternalInconsistencyException` if the receiver is not a symbolic-link file wrapper.
///
/// @deprecated Use -symbolicLinkDestinationURL instead.
///
/// - Returns: Pathname the file wrapper references (the destination of the symbolic link the file wrapper represents).
- (NSString *)symbolicLinkDestination API_DEPRECATED("Use -symbolicLinkDestinationURL instead.", macos(10.0,10.10)) API_UNAVAILABLE(ios, watchos, tvos);

@end

#endif

NS_HEADER_AUDIT_END(nullability, sendability)
