/*	NSData.h
	Copyright (c) 1994-2019, Apple Inc. All rights reserved.
*/

#import <Foundation/NSObject.h>
#import <Foundation/NSRange.h>

@class NSString, NSURL, NSError;

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

/* ***************	Read/Write Options	****************/

/// Options for methods used to read data objects.
typedef NS_OPTIONS(NSUInteger, NSDataReadingOptions) {
    /// A hint indicating the file should be mapped into virtual memory, if possible and safe.
    NSDataReadingMappedIfSafe =   1UL << 0,
    /// A hint indicating the file should not be stored in the file-system caches.
    ///
    /// For data being read once and discarded, this option can improve performance.
    NSDataReadingUncached = 1UL << 1,
    /// Hint to map the file in if possible.
    ///
    /// This takes precedence over `NSDataReadingMappedIfSafe` if both are given.
    NSDataReadingMappedAlways API_AVAILABLE(macos(10.7), ios(5.0), watchos(2.0), tvos(9.0)) = 1UL << 3,

    /// Deprecated name for `NSDataReadingMappedIfSafe`.
    NSDataReadingMapped API_DEPRECATED_WITH_REPLACEMENT("NSDataReadingMappedIfSafe", macos(10.0, API_TO_BE_DEPRECATED), ios(2.0, API_TO_BE_DEPRECATED), watchos(2.0, API_TO_BE_DEPRECATED), tvos(9.0, API_TO_BE_DEPRECATED)) = NSDataReadingMappedIfSafe,
    /// Deprecated name for `NSDataReadingMapped`.
    NSMappedRead API_DEPRECATED_WITH_REPLACEMENT("NSDataReadingMapped", macos(10.0, API_TO_BE_DEPRECATED), ios(2.0, API_TO_BE_DEPRECATED), watchos(2.0, API_TO_BE_DEPRECATED), tvos(9.0, API_TO_BE_DEPRECATED)) = NSDataReadingMapped,
    /// Deprecated name for `NSDataReadingUncached`.
    NSUncachedRead API_DEPRECATED_WITH_REPLACEMENT("NSDataReadingUncached", macos(10.0, API_TO_BE_DEPRECATED), ios(2.0, API_TO_BE_DEPRECATED), watchos(2.0, API_TO_BE_DEPRECATED), tvos(9.0, API_TO_BE_DEPRECATED)) = NSDataReadingUncached
};

/// Options for methods used to write data objects.
typedef NS_OPTIONS(NSUInteger, NSDataWritingOptions) {
    /// An option to write data to an auxiliary file first and then replace the original file with the auxiliary file when the write completes.
    ///
    /// This option is equivalent to using a write method that takes the parameter `atomically` as `YES`.
    NSDataWritingAtomic = 1UL << 0,
    /// An option that attempts to write data to a file and fails with an error if the destination file already exists.
    ///
    /// You can't combine this constant with `NSDataWritingAtomic` because atomic allows the system to overwrite the original file.
    NSDataWritingWithoutOverwriting API_AVAILABLE(macos(10.8), ios(6.0), watchos(2.0), tvos(9.0)) = 1UL << 1,

    /// An option to not encrypt the file when writing it out.
    ///
    /// The system doesn't store the file in an encrypted format and your app can access this file at boot time and while the device is unlocked.
    NSDataWritingFileProtectionNone API_AVAILABLE(macos(11.0), ios(4.0), watchos(2.0), tvos(9.0))                                  = 0x10000000,
    /// An option to make the file accessible only while the device is unlocked.
    ///
    /// The system stores the file in an encrypted format and your app may only read or write to the file while the device is unlocked. At all other times, any attempts your app makes to read and write the file will fail.
    NSDataWritingFileProtectionComplete API_AVAILABLE(macos(11.0), ios(4.0), watchos(2.0), tvos(9.0))                              = 0x20000000,
    /// An option to allow the file to be accessible while the device is unlocked or the file is already open.
    ///
    /// Your app cannot open the file to read it or write to it when the device is locked, but your app can create new files with this class. If one of these files is open when the device is locked, your app can read and write to the opened file.
    NSDataWritingFileProtectionCompleteUnlessOpen API_AVAILABLE(macos(11.0), ios(5.0), watchos(2.0), tvos(9.0))                    = 0x30000000,
    /// An option to allow the file to be accessible after a user first unlocks the device.
    ///
    /// The app can read or write to the file while the device is unlocked, but while it's booting up, the file has the protection equivalent to `NSDataWritingFileProtectionComplete`.
    NSDataWritingFileProtectionCompleteUntilFirstUserAuthentication API_AVAILABLE(macos(11.0), ios(5.0), watchos(2.0), tvos(9.0))  = 0x40000000,
    NSDataWritingFileProtectionCompleteWhenUserInactive API_AVAILABLE(ios(17.0), watchos(10.0), tvos(17.0)) API_UNAVAILABLE(macos)  = 0x50000000,
    /// An option the system uses when determining the file protection options that the system assigns to the data.
    NSDataWritingFileProtectionMask API_AVAILABLE(macos(11.0), ios(4.0), watchos(2.0), tvos(9.0))                                  = 0xf0000000,

    /// An option that attempts to write data to an auxiliary file first and then exchange the files.
    ///
    /// @DeprecationSummary {
    ///     Use `NSDataWritingAtomic` instead.
    /// }
    NSAtomicWrite API_DEPRECATED_WITH_REPLACEMENT("NSDataWritingAtomic", macos(10.0, API_TO_BE_DEPRECATED), ios(2.0, API_TO_BE_DEPRECATED), watchos(2.0, API_TO_BE_DEPRECATED), tvos(9.0, API_TO_BE_DEPRECATED)) = NSDataWritingAtomic
};


/* ***************	Data Search Options	****************/

/// Options for method used to search data objects.
///
/// These options are used with the ``NSData/range(of:options:in:)`` method.
typedef NS_OPTIONS(NSUInteger, NSDataSearchOptions) {
    /// Search from the end of the data object.
    NSDataSearchBackwards = 1UL << 0,
    /// Search is limited to start (or end, if searching backwards) of the data object.
    ///
    /// This option performs searching only on bytes at the beginning of the range (or the end when using `NSDataSearchBackwards`). No match at the beginning or end means nothing is found, even if a matching sequence of bytes occurs elsewhere in the data object.
    NSDataSearchAnchored = 1UL << 1
} API_AVAILABLE(macos(10.6), ios(4.0), watchos(2.0), tvos(9.0));


/* ***************        Base 64 Options	****************/

/// Options for methods used to Base64 encode data.
typedef NS_OPTIONS(NSUInteger, NSDataBase64EncodingOptions) {
    /// Set the maximum line length to 64 characters, after which a line ending is inserted.
    NSDataBase64Encoding64CharacterLineLength = 1UL << 0,
    /// Set the maximum line length to 76 characters, after which a line ending is inserted.
    NSDataBase64Encoding76CharacterLineLength = 1UL << 1,

    /// When a maximum line length is set, specify that the line ending to insert should include a carriage return.
    NSDataBase64EncodingEndLineWithCarriageReturn = 1UL << 4,
    /// When a maximum line length is set, specify that the line ending to insert should include a line feed.
    NSDataBase64EncodingEndLineWithLineFeed = 1UL << 5,

} API_AVAILABLE(macos(10.9), ios(7.0), watchos(2.0), tvos(9.0));


/// Options to modify the decoding algorithm used to decode Base64 encoded data.
typedef NS_OPTIONS(NSUInteger, NSDataBase64DecodingOptions) {
    /// Modify the decoding algorithm so that it ignores unknown non-Base-64 bytes, including line ending characters.
    NSDataBase64DecodingIgnoreUnknownCharacters = 1UL << 0
} API_AVAILABLE(macos(10.9), ios(7.0), watchos(2.0), tvos(9.0));


/* ***************	Immutable Data		****************/

/// A static byte buffer in memory.
///
/// In Swift, the buffer bridges to ``Data``; use ``NSData`` when you need reference semantics or other Foundation-specific behavior.
///
/// [NSData](https://developer.apple.com/library/archive/documentation/Cocoa/Conceptual/PropertyLists/OldStylePlists/OldStylePLists.html#//apple_ref/doc/uid/20001012-47169) and its mutable subclass ``NSMutableData`` provide data objects, or object-oriented wrappers for byte buffers. Data objects let simple allocated buffers (that is, data with no embedded pointers) take on the behavior of Foundation objects.
///
/// The size of the data is subject to a theoretical limit of about 8 exabytes (1 EB = 10^18 bytes; in practice, the limit should not be a factor).
///
/// [NSData](https://developer.apple.com/library/archive/documentation/Cocoa/Conceptual/PropertyLists/OldStylePlists/OldStylePLists.html#//apple_ref/doc/uid/20001012-47169) is _toll-free bridged_ with its Core Foundation counterpart, `CFData`. See [Toll-Free Bridging](https://developer.apple.com/library/archive/documentation/General/Conceptual/CocoaEncyclopedia/Toll-FreeBridgin/Toll-FreeBridgin.html#//apple_ref/doc/uid/TP40010810-CH2) for more information on toll-free bridging.
///
/// > Important:
/// > The Swift overlay to the Foundation framework provides the ``Data`` structure, which bridges to the ``NSData`` class and its mutable subclass ``NSMutableData``. For more information about value types, see [Working with Foundation Types](https://developer.apple.com/documentation/swift/working-with-foundation-types).
///
/// ### Writing Data Atomically
///
/// [NSData](https://developer.apple.com/library/archive/documentation/Cocoa/Conceptual/PropertyLists/OldStylePlists/OldStylePLists.html#//apple_ref/doc/uid/20001012-47169) provides methods for atomically saving their contents to a file, which guarantee that the data is either saved in its entirety, or it fails completely. An atomic write first writes the data to a temporary file and then, only if this write succeeds, moves the temporary file to its final location.
///
/// Although atomic write operations minimize the risk of data loss due to corrupt or partially written files, they may not be appropriate when writing to a temporary directory, the user's home directory or other publicly accessible directories. When you work with a publicly accessible file, treat that file as an untrusted and potentially dangerous resource. An attacker may compromise or corrupt these files. The attacker can also replace the files with hard or symbolic links, causing your write operations to overwrite or corrupt other system resources.
///
/// Avoid using the ``write(to:atomically:)`` method (and the related methods) when working inside a publicly accessible directory. Instead, use ``FileHandle`` with an existing file descriptor to securely write the file.
///
/// For more information, see [Securing File Operations](https://developer.apple.com/library/archive/documentation/Security/Conceptual/SecureCodingGuide/Articles/RaceConditions.html#//apple_ref/doc/uid/TP40002585-SW9) in [Secure Coding Guide](https://developer.apple.com/library/archive/documentation/Security/Conceptual/SecureCodingGuide/Introduction.html#//apple_ref/doc/uid/TP40002415).
@interface NSData : NSObject <NSCopying, NSMutableCopying, NSSecureCoding>

/// The number of bytes contained by the data object.
@property (readonly) NSUInteger length;
/// A pointer to the data object's contents.
///
/// If the ``NSData/length`` of the [NSData](https://developer.apple.com/library/archive/documentation/Cocoa/Conceptual/PropertyLists/OldStylePlists/OldStylePLists.html#//apple_ref/doc/uid/20001012-47169) object is 0, this property returns `nil`.
///
/// For an immutable data object, the returned pointer is valid until the data object is deallocated. For a mutable data object, the returned pointer is valid until the data object is deallocated or the data is mutated.
@property (readonly) const void *bytes NS_RETURNS_INNER_POINTER;

@end

@interface NSData (NSExtendedData)

/// A string that contains a hexadecimal representation of the data object's contents in a property list format.
@property (readonly, copy) NSString *description;
/// Copies a number of bytes from the start of the data object into a given buffer.
///
/// The number of bytes copied is the smaller of the `length` parameter and the ``NSData/length`` of the data encapsulated in the object.
/// - Parameters:
///   - buffer: A buffer into which to copy data.
///   - length: The number of bytes from the start of the receiver's data to copy to `buffer`.
- (void)getBytes:(void *)buffer length:(NSUInteger)length;
/// Copies a range of bytes from the data object into a given buffer.
///
/// If `range` isn't within the receiver's range of bytes, an ``NSExceptionName/rangeException`` is raised.
/// - Parameters:
///   - buffer: A buffer into which to copy data.
///   - range: The range of bytes in the receiver's data to copy to `buffer`. The range must lie within the range of bytes of the receiver's data.
- (void)getBytes:(void *)buffer range:(NSRange)range;
/// Returns a Boolean value indicating whether this data object is the same as another.
///
/// Two data objects are equal if they hold the same number of bytes, and if the bytes at the same position in the objects are the same.
/// - Parameter other: The data object with which to compare the receiver.
/// - Returns: `YES` if the contents of `otherData` are equal to the contents of the receiver, otherwise `NO`.
- (BOOL)isEqualToData:(NSData *)other;
/// Returns a new data object containing the data object's bytes that fall within the limits specified by a given range.
///
/// A sample using this method can be found in [Working With Binary Data](https://developer.apple.com/library/archive/documentation/Cocoa/Conceptual/BinaryData/Tasks/WorkingBinaryData.html#//apple_ref/doc/uid/20000717).
/// - Parameter range: The range in the receiver from which to get the data. If this range is not within the data object's range of bytes, ``NSExceptionName/rangeException`` is raised.
/// - Returns: A data object containing the receiver's bytes that fall within the limits specified by `range`.
- (NSData *)subdataWithRange:(NSRange)range;
/// Writes the data object's bytes to the file specified by a given path.
///
/// This method may not be appropriate when writing to publicly accessible files. To securely write data to a public location, use ``FileHandle`` instead. For more information, see [Securing File Operations](https://developer.apple.com/library/archive/documentation/Security/Conceptual/SecureCodingGuide/Articles/RaceConditions.html#//apple_ref/doc/uid/TP40002585-SW9) in [Secure Coding Guide](https://developer.apple.com/library/archive/documentation/Security/Conceptual/SecureCodingGuide/Introduction.html#//apple_ref/doc/uid/TP40002415).
/// - Parameters:
///   - path: The location to which to write the receiver's bytes. If `path` contains a tilde (~) character, you must expand it with ``NSString/expandingTildeInPath`` before invoking this method.
///   - useAuxiliaryFile: If `YES`, the data is written to a backup file, and then--assuming no errors occur--the backup file is renamed to the name specified by `path`; otherwise, the data is written directly to `path`.
/// - Returns: `YES` if the operation succeeds, otherwise `NO`.
- (BOOL)writeToFile:(NSString *)path atomically:(BOOL)useAuxiliaryFile;
/// Writes the data object's bytes to the location specified by a given URL.
///
/// Since at present only `file://` URLs are supported, there is no difference between this method and ``NSData/write(toFile:atomically:)``, except for the type of the first argument.
///
/// This method may not be appropriate when writing to publicly accessible files. To securely write data to a public location, use ``FileHandle`` instead. For more information, see [Securing File Operations](https://developer.apple.com/library/archive/documentation/Security/Conceptual/SecureCodingGuide/Articles/RaceConditions.html#//apple_ref/doc/uid/TP40002585-SW9) in [Secure Coding Guide](https://developer.apple.com/library/archive/documentation/Security/Conceptual/SecureCodingGuide/Introduction.html#//apple_ref/doc/uid/TP40002415).
/// - Parameters:
///   - url: The location to which to write the receiver's bytes. Only `file://` URLs are supported.
///   - atomically: If `YES`, the data is written to a backup location, and then--assuming no errors occur--the backup location is renamed to the name specified by `aURL`; otherwise, the data is written directly to `aURL`. `atomically` is ignored if `aURL` is not of a type the supports atomic writes.
/// - Returns: `YES` if the operation succeeds, otherwise `NO`.
- (BOOL)writeToURL:(NSURL *)url atomically:(BOOL)atomically; // the atomically flag is ignored if the url is not of a type the supports atomic writes
/// Writes the data object's bytes to the file specified by a given path.
///
/// This method may not be appropriate when writing to publicly accessible files. To securely write data to a public location, use ``FileHandle`` instead. For more information, see [Securing File Operations](https://developer.apple.com/library/archive/documentation/Security/Conceptual/SecureCodingGuide/Articles/RaceConditions.html#//apple_ref/doc/uid/TP40002585-SW9) in [Secure Coding Guide](https://developer.apple.com/library/archive/documentation/Security/Conceptual/SecureCodingGuide/Introduction.html#//apple_ref/doc/uid/TP40002415).
/// - Parameters:
///   - path: The location to which to write the receiver's bytes.
///   - writeOptionsMask: A mask that specifies options for writing the data. Constant components are described in ``NSData/WritingOptions``.
///   - errorPtr: If there is an error writing out the data, upon return contains an error object that describes the problem.
/// - Returns: `YES` if the operation succeeds, otherwise `NO`.
- (BOOL)writeToFile:(NSString *)path options:(NSDataWritingOptions)writeOptionsMask error:(NSError **)errorPtr;
/// Writes the data object's bytes to the location specified by a given URL.
///
/// Since at present only `file://` URLs are supported, there is no difference between this method and ``NSData/write(toFile:options:)``, except for the type of the first argument.
///
/// This method may not be appropriate when writing to publicly accessible files. To securely write data to a public location, use ``FileHandle`` instead. For more information, see [Securing File Operations](https://developer.apple.com/library/archive/documentation/Security/Conceptual/SecureCodingGuide/Articles/RaceConditions.html#//apple_ref/doc/uid/TP40002585-SW9) in [Secure Coding Guide](https://developer.apple.com/library/archive/documentation/Security/Conceptual/SecureCodingGuide/Introduction.html#//apple_ref/doc/uid/TP40002415).
/// - Parameters:
///   - url: The location to which to write the receiver's bytes.
///   - writeOptionsMask: A mask that specifies options for writing the data. Constant components are described in ``NSData/WritingOptions``.
///   - errorPtr: If there is an error writing out the data, upon return contains an error object that describes the problem.
/// - Returns: `YES` if the operation succeeds, otherwise `NO`.
- (BOOL)writeToURL:(NSURL *)url options:(NSDataWritingOptions)writeOptionsMask error:(NSError **)errorPtr;
/// Finds and returns the range of the first occurrence of the given data, within the given range, subject to given options.
///
/// - Parameters:
///   - dataToFind: The data for which to search.
///   - mask: A mask specifying search options. The ``NSData/SearchOptions`` options may be specified singly or by combining them with the C bitwise `OR` operator.
///   - searchRange: The range within the receiver in which to search for `dataToFind`. If this range is not within the data object's range of bytes, ``NSExceptionName/rangeException`` is raised.
/// - Returns: An `NSRange` structure giving the location and length of `dataToFind` within `searchRange`, modulo the options in `mask`. The range returned is relative to the start of the searched data, not the passed-in search range. Returns `{NSNotFound, 0}` if `dataToFind` is not found or is empty.
- (NSRange)rangeOfData:(NSData *)dataToFind options:(NSDataSearchOptions)mask range:(NSRange)searchRange API_AVAILABLE(macos(10.6), ios(4.0), watchos(2.0), tvos(9.0));

/// Enumerates each range of bytes in the data object using a block.
///
/// The enumeration block is called once for each contiguous region of memory in the receiver (once total for a contiguous [NSData](https://developer.apple.com/library/archive/documentation/Cocoa/Conceptual/PropertyLists/OldStylePlists/OldStylePLists.html#//apple_ref/doc/uid/20001012-47169) object), until either all bytes have been enumerated, or the `stop` parameter is set to `YES`.
/// - Parameter block: The block to apply to byte ranges in the array. The block takes three arguments:
///   - `bytes`: The bytes for the current range. This pointer is valid until the data object is deallocated.
///   - `byteRange`: The range of the current data bytes.
///   - `stop`: A reference to a Boolean value. The block can set the value to `YES` to stop further processing of the data. The stop argument is an out-only argument. You should only ever set this Boolean to `YES` within the Block.
- (void) enumerateByteRangesUsingBlock:(void (NS_NOESCAPE ^)(const void *bytes, NSRange byteRange, BOOL *stop))block API_AVAILABLE(macos(10.9), ios(7.0), watchos(2.0), tvos(9.0));

@end

@interface NSData (NSDataCreation)

/// Creates an empty data object.
///
/// This method is declared primarily for the use of mutable subclasses of [NSData](https://developer.apple.com/library/archive/documentation/Cocoa/Conceptual/PropertyLists/OldStylePlists/OldStylePLists.html#//apple_ref/doc/uid/20001012-47169).
+ (instancetype)data;
/// Creates a data object containing a given number of bytes copied from a given buffer.
///
/// - Parameters:
///   - bytes: A buffer containing data for the new object.
///   - length: The number of bytes to copy from `bytes`. This value must not exceed the length of `bytes`.
+ (instancetype)dataWithBytes:(nullable const void *)bytes length:(NSUInteger)length;
/// Creates a data object that holds a given number of bytes from a given buffer.
///
/// The returned object takes ownership of the `bytes` pointer and frees it on deallocation. Therefore, `bytes` must point to a memory block allocated with `malloc`.
/// - Parameters:
///   - bytes: A buffer containing data for the new object. `bytes` must point to a memory block allocated with `malloc`.
///   - length: The number of bytes to hold from `bytes`. This value must not exceed the length of `bytes`.
+ (instancetype)dataWithBytesNoCopy:(void *)bytes length:(NSUInteger)length;
/// Creates a data object that holds a given number of bytes from a given buffer.
///
/// - Parameters:
///   - bytes: A buffer containing data for the new object. If `freeWhenDone` is `YES`, `bytes` must point to a memory block allocated with `malloc`.
///   - length: The number of bytes to hold from `bytes`. This value must not exceed the length of `bytes`.
///   - b: If `YES`, the returned object takes ownership of the `bytes` pointer and frees it on deallocation.
+ (instancetype)dataWithBytesNoCopy:(void *)bytes length:(NSUInteger)length freeWhenDone:(BOOL)b;
/// Creates a data object by reading every byte from the file at a given path.
///
/// This method returns `nil` if the data object could not be created. In this case, `errorPtr` will contain an ``NSError`` indicating the problem.
/// - Parameters:
///   - path: The absolute path of the file from which to read data.
///   - readOptionsMask: A mask that specifies options for reading the data. Constant components are described in ``NSData/ReadingOptions``.
///   - errorPtr: If an error occurs, upon return contains an error object that describes the problem.
+ (nullable instancetype)dataWithContentsOfFile:(NSString *)path options:(NSDataReadingOptions)readOptionsMask error:(NSError **)errorPtr;
/// Creates a data object from the data at the provided file URL using specific reading options.
///
/// > Important:
/// > As this method runs synchronously and blocks the calling thread until it finishes, don't invoke it from the main thread. Use file coordination or one of the nonblocking file-related APIs instead.
/// - Parameters:
///   - url: The location on disk of the data to read.
///   - readOptionsMask: The mask specifying the options to use when reading the data. For more information, see ``NSData/ReadingOptions``.
///   - errorPtr: `nil` if the data is read; otherwise, an error object describing the failure.
/// - Returns: A data object that contains the file's data, or `nil` if the system can't create one.
+ (nullable instancetype)dataWithContentsOfURL:(NSURL *)url options:(NSDataReadingOptions)readOptionsMask error:(NSError **)errorPtr;
/// Creates a data object by reading every byte from the file at a given path.
///
/// This method returns `nil` if the data object could not be created. If you need to know the reason for failure, use ``NSData/dataWithContentsOfFile:options:error:``.
///
/// This method is equivalent to calling ``NSData/dataWithContentsOfFile:options:error:`` and passing no options.
///
/// A sample using this method can be found in [Working With Binary Data](https://developer.apple.com/library/archive/documentation/Cocoa/Conceptual/BinaryData/Tasks/WorkingBinaryData.html#//apple_ref/doc/uid/20000717).
/// - Parameter path: The absolute path of the file from which to read data.
+ (nullable instancetype)dataWithContentsOfFile:(NSString *)path;
/// Creates a data object from the data at the specified file URL.
///
/// > Important:
/// > As this method runs synchronously and blocks the calling thread until it finishes, don't invoke it from the main thread. Use file coordination or one of the nonblocking file-related APIs instead.
///
/// If you specify a malformed URL or the referenced location doesn't exist on disk, the initializer fails and returns `nil`. To handle such errors, use ``NSData/init(contentsOfURL:options:)-95rht`` instead.
/// - Parameter url: The location on disk of the data to read.
/// - Returns: A data object that contains the file's data, or `nil` if the system can't create one.
+ (nullable instancetype)dataWithContentsOfURL:(NSURL *)url;
/// Initializes a data object filled with a given number of bytes copied from a given buffer.
///
/// A data object initialized by adding to it `length` bytes of data copied from the buffer `bytes`. The returned object might be different than the original receiver.
- (instancetype)initWithBytes:(nullable const void *)bytes length:(NSUInteger)length;
/// Initializes a data object filled with a given number of bytes of data from a given buffer.
///
/// The returned object takes ownership of the `bytes` pointer and frees it on deallocation. Therefore, `bytes` must point to a memory block allocated with `malloc`.
/// - Parameters:
///   - bytes: A buffer containing data for the new object. `bytes` must point to a memory block allocated with `malloc`.
///   - length: The number of bytes to hold from `bytes`. This value must not exceed the length of `bytes`.
/// - Returns: A data object initialized by adding to it `length` bytes of data from the buffer `bytes`. The returned object might be different than the original receiver.
- (instancetype)initWithBytesNoCopy:(void *)bytes length:(NSUInteger)length;
/// Initializes a newly allocated data object by adding the given number of bytes from the given buffer.
///
/// - Parameters:
///   - bytes: A buffer containing data for the new object. If `flag` is `YES`, `bytes` must point to a memory block allocated with `malloc`.
///   - length: The number of bytes to hold from `bytes`. This value must not exceed the length of `bytes`.
///   - b: If `YES`, the returned object takes ownership of the `bytes` pointer and frees it on deallocation.
- (instancetype)initWithBytesNoCopy:(void *)bytes length:(NSUInteger)length freeWhenDone:(BOOL)b;
/// Initializes a data object filled with a given number of bytes of data from a given buffer, with a custom deallocator block.
///
/// Use this method to define your own deallocation behavior for the data buffer you provide.
///
/// In order to avoid any inadvertent strong reference cycles, you should avoid capturing pointers to any objects that may in turn maintain strong references to the `NSData` object. This includes explicit references to `self`, and implicit references to `self` due to direct instance variable access. To make it easier to avoid these references, the `deallocator` block takes two parameters, a pointer to the `buffer`, and its length; you should always use these values instead of trying to use references from outside the block.
/// - Parameters:
///   - bytes: A buffer containing data for the new object.
///   - length: The number of bytes to hold from `bytes`. This value must not exceed the length of `bytes`.
///   - deallocator: A block to invoke when the resulting `NSData` object is deallocated.
/// - Returns: A data object initialized by adding to it `length` bytes of data from the buffer `bytes`. The returned object might be different than the original receiver.
- (instancetype)initWithBytesNoCopy:(void *)bytes length:(NSUInteger)length deallocator:(nullable void (^)(void *bytes, NSUInteger length))deallocator API_AVAILABLE(macos(10.9), ios(7.0), watchos(2.0), tvos(9.0));
/// Initializes a data object with the content of the file at a given path.
///
/// This method is equivalent to ``NSData/init(contentsOfFile:options:)`` with no options.
/// - Parameter path: The absolute path of the file from which to read data.
/// - Returns: A data object initialized by reading into it the data from the file specified by `path`.
- (nullable instancetype)initWithContentsOfFile:(NSString *)path options:(NSDataReadingOptions)readOptionsMask error:(NSError **)errorPtr;
/// Creates a data object from the data at the provided file URL using specific reading options.
///
/// > Important:
/// > As this method runs synchronously and blocks the calling thread until it finishes, don't invoke it from the main thread. Use file coordination or one of the nonblocking file-related APIs instead.
///
/// If the system can't create an instance, the initializer may throw in Swift, or return `nil` in Objective-C.
/// - Parameters:
///   - url: The location on disk of the data to read.
///   - readOptionsMask: The mask specifying the options to use when reading the data. For more information, see ``NSData/ReadingOptions``.
///   - errorPtr: `nil` if the data is read; otherwise, an error object describing the failure.
- (nullable instancetype)initWithContentsOfURL:(NSURL *)url options:(NSDataReadingOptions)readOptionsMask error:(NSError **)errorPtr;
/// Initializes a data object with the content of the file at a given path.
///
/// This method is equivalent to ``NSData/init(contentsOfFile:options:)`` with no options.
/// - Parameter path: The absolute path of the file from which to read data.
/// - Returns: A data object initialized by reading into it the data from the file specified by `path`.
- (nullable instancetype)initWithContentsOfFile:(NSString *)path;
/// Creates a data object from the data at the specified file URL, or returns `nil` if the system can't create one.
///
/// > Important:
/// > As this method runs synchronously and blocks the calling thread until it finishes, don't invoke it from the main thread. Use file coordination or one of the nonblocking file-related APIs instead.
///
/// If you specify a malformed URL or the referenced location doesn't exist on disk, the initializer fails and returns `nil`. To handle such errors, use ``NSData/init(contentsOfURL:options:)-5abi3`` instead.
/// - Parameter url: The location on disk of the data to read.
- (nullable instancetype)initWithContentsOfURL:(NSURL *)url;
/// Initializes a data object with the contents of another data object.
///
/// - Parameter data: A data object.
/// - Returns: A data object initialized with the contents `data`.
- (instancetype)initWithData:(NSData *)data;
/// Creates a data object containing the contents of another data object.
///
/// - Parameter data: A data object.
+ (instancetype)dataWithData:(NSData *)data;

@end

@interface NSData (NSDataBase64Encoding)

/// Initializes a data object with the given Base64 encoded string.
///
/// The default implementation of this method will reject non-alphabet characters, including line break characters. To support different encodings and ignore non-alphabet characters, specify an `options` value of ``NSData/Base64DecodingOptions/ignoreUnknownCharacters``.
/// - Parameters:
///   - base64String: A Base-64 encoded string.
///   - options: A mask that specifies options for Base-64 decoding the data. Possible values are given in ``NSData/Base64DecodingOptions``.
/// - Returns: A data object built by Base64 decoding the provided string. Returns `nil` if the data object could not be decoded.
- (nullable instancetype)initWithBase64EncodedString:(NSString *)base64String options:(NSDataBase64DecodingOptions)options API_AVAILABLE(macos(10.9), ios(7.0), watchos(2.0), tvos(9.0));

/// Creates a Base64 encoded string from the receiver's contents using the given options.
///
/// By default, no line endings are inserted.
///
/// If you specify one of the line length options (``NSData/Base64EncodingOptions/lineLength64Characters`` or ``NSData/Base64EncodingOptions/lineLength76Characters``) but don't specify the kind of line ending to insert, the default line ending is Carriage Return + Line Feed.
/// - Parameter options: A mask that specifies options for Base-64 encoding the data. Possible values are given in ``NSData/Base64EncodingOptions``.
/// - Returns: A Base64 encoded string.
- (NSString *)base64EncodedStringWithOptions:(NSDataBase64EncodingOptions)options API_AVAILABLE(macos(10.9), ios(7.0), watchos(2.0), tvos(9.0));

/// Initializes a data object with the given Base64 encoded data.
///
/// The default implementation of this method will reject non-alphabet characters, including line break characters. To support different encodings and ignore non-alphabet characters, specify an `options` value of ``NSData/Base64DecodingOptions/ignoreUnknownCharacters``.
/// - Parameters:
///   - base64Data: A Base64, UTF-8 encoded data object.
///   - options: A mask that specifies options for Base64 decoding the data. Possible values are given in ``NSData/Base64DecodingOptions``.
/// - Returns: A data object containing the Base64 decoded data. Returns `nil` if the data object could not be decoded.
- (nullable instancetype)initWithBase64EncodedData:(NSData *)base64Data options:(NSDataBase64DecodingOptions)options API_AVAILABLE(macos(10.9), ios(7.0), watchos(2.0), tvos(9.0));

/// Creates a Base64, UTF-8 encoded data object from the receiver's contents using the given options.
///
/// By default, no line endings are inserted.
///
/// If you specify one of the line length options (``NSData/Base64EncodingOptions/lineLength64Characters`` or ``NSData/Base64EncodingOptions/lineLength76Characters``) but don't specify the kind of line ending to insert, the default line ending is Carriage Return + Line Feed.
/// - Parameter options: A mask that specifies options for Base64 encoding the data. Possible values are given in ``NSData/Base64EncodingOptions``.
/// - Returns: A Base64, UTF-8 encoded data object.
- (NSData *)base64EncodedDataWithOptions:(NSDataBase64EncodingOptions)options API_AVAILABLE(macos(10.9), ios(7.0), watchos(2.0), tvos(9.0));

@end

/// An algorithm that indicates how to compress or decompress data.
///
/// Choose an algorithm that best suits the needs of your app:
///
/// - ``lzfse`` -- The algorithm offers faster speed and generally achieves better compression than ``zlib``. However, it is slower than ``lz4`` and doesn't compress as well as ``lzma``.
/// - ``zlib`` -- Use this algorithm if your app requires interoperability with non-Apple devices. For example, if you are transferring data to another device where it needs to be compressed or decompressed.
/// - ``lz4`` -- Use this algorithm if speed is critical, and you're willing to sacrifice compression ratio to achieve it.
/// - ``lzma`` -- Use this algorithm if compression ratio is critical, and you're willing to sacrifice speed to achieve it. It is an order of magnitude slower for both compression and decompression than other choices.
typedef NS_ENUM(NSInteger, NSDataCompressionAlgorithm) {

    /// The LZFSE compression algorithm, recommended for use on Apple platforms.
    ///
    /// LZFSE is the recommended compression algorithm if you don't have a specific reason to use another algorithm. Note that LZFSE is intended for use with Apple devices only. This algorithm generally compresses better than Zlib, but not as well as LZMA. It is generally slower than LZ4.
    NSDataCompressionAlgorithmLZFSE = 0,

    /// The LZ4 compression algorithm, recommended for fast compression.
    ///
    /// LZ4 is appropriate if compression speed is critical. LZ4 generally sacrifices compression ratio in order to achieve its greater speed.
    NSDataCompressionAlgorithmLZ4,     // This implementation of LZ4 makes a small modification to the standard format, which is described in greater detail in <compression.h>.

    /// The LZMA compression algorithm, recommended for high-compression ratio.
    ///
    /// LZMA is appropriate if compression ratio is critical and memory usage and compression speed are not a factor. LZMA is an order of magnitude slower for both compression and decompression than other algorithms. It can also use a very large amount of memory, so if you need to compress large amounts of data on embedded devices with limited memory you should probably avoid LZMA.
    /// Encoding uses LZMA level 6 only, but decompression works with any compression level.
    NSDataCompressionAlgorithmLZMA,

    /// The zlib compression algorithm, recommended for cross-platform compression.
    ///
    /// Zlib is appropriate if you want a good balance between compression speed and compression ratio, but only if you need interoperability with non-Apple platforms. Otherwise, LZFSE is generally a better choice than Zlib.
    /// Encoding uses Zlib level 5 only, but decompression works with any compression level. It uses the raw DEFLATE format as described in IETF RFC 1951.
    NSDataCompressionAlgorithmZlib,
    
} API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0));

@interface NSData (NSDataCompression)

/// Returns a new data object by decompressing data object's bytes.
///
/// Use this method to inflate in-memory data when you need uncompressed bytes. Specify the same algorithm used to compress the data to successfully decompress it.
///
/// The following example shows how to create a new ``NSData`` instance from data compressed with the ``NSData/CompressionAlgorithm/zlib`` algorithm:
///
/// ```swift
/// do {
///     let uncompressedData = try compressedData.decompressed(using: .zlib)
/// } catch {
///     print ("Decompression error: \(error)")
/// }
/// ```
/// - Parameters:
///   - algorithm: An algorithm used to decompress the data. For a list of available algorithms, see ``NSData/CompressionAlgorithm``.
///   - error: On return, a pointer to an ``NSError`` instance that indicates why decompressing the data failed, or `nil` if no error occurred.
/// - Returns: An ``NSData`` instance that contains the decompressed buffer data.
- (nullable instancetype)decompressedDataUsingAlgorithm:(NSDataCompressionAlgorithm)algorithm error:(NSError **)error API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0));
/// Returns a new data object by compressing the data object's bytes.
///
/// Use this method to compress in-memory data when you want to reduce memory usage and can afford the time to compress and decompress it. If your data object is already in a compressed format, such as media formats like JPEG images or AAC audio, additional compression may provide minimal or no reduction in memory usage.
///
/// To restore this data, use ``NSData/decompressed(using:)``, and specify the algorithm originally used to compress the data.
///
/// The following example shows how to compress the data from a string and prints the sizes of the data instances to illustrate the amount of compression:
///
/// ```swift
/// var string = "NSData and its mutable subclass NSMutableData provide data objects, or object-oriented wrappers for byte buffers. Data objects let simple allocated buffers (that is, data with no embedded pointers) take on the behavior of Foundation objects."
/// let data = Data(string.utf8) as NSData
/// print ("original data size: \(data.count) bytes")
/// do {
///     let compressedData = try data.compressed(using: .zlib)
///     print("zlib compressed size: \(compressedData.count) bytes")
/// } catch {
///     print ("Compression error: \(error)")
/// }
/// // Prints:
/// //  original data size: 241 bytes
/// //  zlib compressed size: 158 bytes
/// ```
/// - Parameters:
///   - algorithm: An algorithm used to compress the data. For a list of available algorithms, see ``NSData/CompressionAlgorithm``.
///   - error: On return, a pointer to an ``NSError`` instance that indicates why compressing the data failed, or `nil` if no error occurred.
/// - Returns: An ``NSData`` instance that contains the compressed buffer data.
- (nullable instancetype)compressedDataUsingAlgorithm:(NSDataCompressionAlgorithm)algorithm error:(NSError **)error API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0));

@end


@interface NSData (NSDeprecated)

/// Copies a data object's contents into a given buffer.
///
/// You can see a sample using this method in [Working With Binary Data](https://developer.apple.com/library/archive/documentation/Cocoa/Conceptual/BinaryData/Tasks/WorkingBinaryData.html#//apple_ref/doc/uid/20000717).
/// - Parameter buffer: A buffer into which to copy the receiver's data. The buffer must be at least ``NSData/length`` bytes.
- (void)getBytes:(void *)buffer API_DEPRECATED("This method is unsafe because it could potentially cause buffer overruns. Use -getBytes:length: instead.", macos(10.0,10.10), ios(2.0,8.0), watchos(2.0,2.0), tvos(9.0,9.0));
/// Creates a data object from the mapped file at a given path.
///
/// This method returns `nil` if the data object could not be created
///
/// Because of file mapping restrictions, this method should only be used if the file is guaranteed to exist for the duration of the data object's existence. It is generally safer to use the ``NSData/dataWithContentsOfFile:`` method.
///
/// This methods assumes mapped files are available from the underlying operating system. A mapped file uses virtual memory techniques to avoid copying pages of the file into memory until they are actually needed.
/// - Parameter path: The absolute path of the file from which to read data.
+ (nullable id)dataWithContentsOfMappedFile:(NSString *)path API_DEPRECATED("Use +dataWithContentsOfURL:options:error: and NSDataReadingMappedIfSafe or NSDataReadingMappedAlways instead.", macos(10.0,10.10), ios(2.0,8.0), watchos(2.0,2.0), tvos(9.0,9.0));
/// Initializes a data object with the contents of the mapped file specified by a given path.
///
/// - Parameter path: The absolute path of the file from which to read data.
/// - Returns: A data object initialized by reading into it the mapped file specified by `path`.
- (nullable id)initWithContentsOfMappedFile:(NSString *)path  API_DEPRECATED("Use -initWithContentsOfURL:options:error: and NSDataReadingMappedIfSafe or NSDataReadingMappedAlways instead.", macos(10.0,10.10), ios(2.0,8.0), watchos(2.0,2.0), tvos(9.0,9.0));

/// Initializes a data object initialized with the given Base64 encoded string.
///
/// Although this method was only introduced publicly for iOS 7, it has existed since iOS 4; you can use it if your application needs to target an operating system prior to iOS 7. This method behaves like ``NSData/init(base64EncodedString:options:)``, but ignores all unknown characters.
/// - Parameter base64String: A Base-64 encoded string.
/// - Returns: A data object built by Base-64 decoding the provided string. Returns `nil` if the data object could not be decoded.
- (nullable id)initWithBase64Encoding:(NSString *)base64String API_DEPRECATED("Use initWithBase64EncodedString:options: instead", macos(10.6,10.9), ios(4.0,7.0), watchos(2.0,2.0), tvos(9.0,9.0));
/// Initializes a Base64 encoded string from the string.
///
/// This method is equivalent to calling ``NSData/base64EncodedString(options:)`` with no options specified.
///
/// ### Special Considerations
///
/// Although this method was only introduced publicly for iOS 7, it has existed since iOS 4; you can use it if your application needs to target an operating system prior to iOS 7.
/// - Returns: A Base-64 encoded string.
- (NSString *)base64Encoding API_DEPRECATED("Use base64EncodedStringWithOptions: instead", macos(10.6,10.9), ios(4.0,7.0), watchos(2.0,2.0), tvos(9.0,9.0));

@end

/* ***************	Mutable Data		****************/

/// An object representing a dynamic byte buffer in memory.
///
/// In Swift, this object bridges to ``Data``; use ``NSMutableData`` when you need reference semantics or other Foundation-specific behavior.
///
/// `NSMutableData` and its superclass `NSData` provide data objects, or object-oriented wrappers for byte buffers. Data objects let simple allocated buffers (that is, data with no embedded pointers) take on the behavior of Foundation objects. `NSData` creates static data objects, and `NSMutableData` creates dynamic data objects. You can easily convert one type of data object to the other with the initializer that takes an `NSData` object or an  `NSMutableData` object as an argument.
///
/// The following ``NSData`` methods change when used on a mutable data object:
///
/// - ``NSData/init(bytesNoCopy:length:freeWhenDone:)``
/// - ``NSData/init(bytesNoCopy:length:deallocator:)``
/// - ``NSData/init(bytesNoCopy:length:)``
/// - ``NSData/dataWithBytesNoCopy:length:freeWhenDone:``
/// - ``NSData/dataWithBytesNoCopy:length:``
///
/// When called, the bytes are immediately copied and then the buffer is freed.
///
/// `NSMutableData` is "toll-free bridged" with its Core Foundation counterpart, `CFData`. See [Toll-Free Bridging](https://developer.apple.com/library/archive/documentation/General/Conceptual/CocoaEncyclopedia/Toll-FreeBridgin/Toll-FreeBridgin.html#//apple_ref/doc/uid/TP40010810-CH2) for more information on toll-free bridging.
///
/// > Important:
/// > The Swift overlay to the Foundation framework provides the ``Data`` structure, which bridges to the ``NSMutableData`` class and its immutable superclass ``NSData``. For more information about value types, see [Working with Foundation Types](https://developer.apple.com/documentation/swift/working-with-foundation-types).
@interface NSMutableData : NSData

/// A pointer to the data contained by the mutable data object.
///
/// If the length of the receiver's data is not zero, this property is guaranteed to contain a pointer to the object's internal bytes. If the length of receiver's data _is_ zero, this property may or may not contain `NULL` dependent upon many factors related to how the object was created (moreover, in this case the method result might change between different releases). The returned pointer is valid until the data object is deallocated.
///
/// > Note:
/// > This property is similar to, but different than the ``NSData/bytes`` property. The ``NSData/bytes`` property contains a pointer to a constant. You can use The ``NSData/bytes`` pointer to read the data managed by the data object, but you cannot modify that data. However, if the ``NSMutableData/mutableBytes`` property contains a non-`null` pointer, this pointer points to mutable data. You can use the ``NSMutableData/mutableBytes`` pointer to modify the data managed by the data object.
///
/// A sample using this method can be found in [Working With Mutable Binary Data](https://developer.apple.com/library/archive/documentation/Cocoa/Conceptual/BinaryData/Tasks/WorkingMutableData.html#//apple_ref/doc/uid/20002150).
@property (readonly) void *mutableBytes NS_RETURNS_INNER_POINTER;
/// The number of bytes contained in the mutable data object.
///
/// The mutable data object's length parameter is read-writeable. You can set this parameter to expand or truncate the number of bytes contained by the data object. If the mutable data object is expanded, the additional bytes are filled with zeros.
///
/// > Important:
/// > Changing the length of a mutable data object invalidate any existing data pointers returned by the ``NSData/bytes`` or ``NSMutableData/mutableBytes`` properties.
@property NSUInteger length;

@end

@interface NSMutableData (NSExtendedMutableData)

/// Appends to the receiver a given number of bytes from a given buffer.
///
/// A sample using this method can be found in [Working With Mutable Binary Data](https://developer.apple.com/library/archive/documentation/Cocoa/Conceptual/BinaryData/Tasks/WorkingMutableData.html#//apple_ref/doc/uid/20002150).
/// - Parameters:
///   - bytes: A buffer containing data to append to the receiver's content.
///   - length: The number of bytes from `bytes` to append.
- (void)appendBytes:(const void *)bytes length:(NSUInteger)length;
/// Appends the content of another data object to the receiver.
///
/// - Parameter other: The data object whose content is to be appended to the contents of the receiver.
- (void)appendData:(NSData *)other;
/// Increases the length of the receiver by a given number of bytes.
///
/// The additional bytes are all set to `0`.
///
/// > Important:
/// > Changing the length of a mutable data object invalidates any existing data pointers returned by the ``NSData/bytes`` or ``NSMutableData/mutableBytes`` properties.
/// - Parameter extraLength: The number of bytes by which to increase the receiver's length.
- (void)increaseLengthBy:(NSUInteger)extraLength;
/// Replaces with a given set of bytes a given range within the contents of the receiver.
///
/// If the location of `range` isn't within the receiver's range of bytes, an `NSRangeException` is raised. The receiver is resized to accommodate the new bytes, if necessary.
///
/// A sample using this method is given in [Working With Mutable Binary Data](https://developer.apple.com/library/archive/documentation/Cocoa/Conceptual/BinaryData/Tasks/WorkingMutableData.html#//apple_ref/doc/uid/20002150).
/// - Parameters:
///   - range: The range within the receiver's contents to replace with `bytes`. The range must not exceed the bounds of the receiver.
///   - bytes: The data to insert into the receiver's contents.
- (void)replaceBytesInRange:(NSRange)range withBytes:(const void *)bytes;
/// Replaces with zeroes the contents of the receiver in a given range.
///
/// If the location of `range` isn't within the receiver's range of bytes, an `NSRangeException` is raised. The receiver is resized to accommodate the new bytes, if necessary.
/// - Parameter range: The range within the contents of the receiver to be replaced by zeros. The range must not exceed the bounds of the receiver.
- (void)resetBytesInRange:(NSRange)range;
/// Replaces the entire contents of the receiver with the contents of another data object.
///
/// As part of its implementation, this method calls ``NSMutableData/replaceBytes(in:withBytes:)``.
/// - Parameter data: The data object whose content replaces that of the receiver.
- (void)setData:(NSData *)data;
/// Replaces with a given set of bytes a given range within the contents of the receiver.
///
/// If the length of `range` is not equal to `replacementLength`, the receiver is resized to accommodate the new bytes. Any bytes past `range` in the receiver are shifted to accommodate the new bytes. You can therefore pass `NULL` for `replacementBytes` and `0` for `replacementLength` to delete bytes in the receiver in the range `range`. You can also replace a range (which might be zero-length) with more bytes than the length of the range, which has the effect of insertion (or "replace some and insert more").
/// - Parameters:
///   - range: The range within the receiver's contents to replace with `bytes`. The range must not exceed the bounds of the receiver.
///   - replacementBytes: The data to insert into the receiver's contents.
///   - replacementLength: The number of bytes to take from `replacementBytes`.
- (void)replaceBytesInRange:(NSRange)range withBytes:(nullable const void *)replacementBytes length:(NSUInteger)replacementLength;

@end

@interface NSMutableData (NSMutableDataCreation)

/// Creates and returns a mutable data object capable of holding the specified number of bytes.
///
/// This method doesn't necessarily allocate the requested memory right away. Mutable data objects allocate additional memory as needed, so `aNumItems` simply establishes the object's initial capacity. When it does allocate the initial memory, though, it allocates the specified amount. This method sets the length of the data object to `0`.
///
/// If the capacity specified in `aNumItems` is greater than four memory pages in size, this method may round the amount of requested memory up to the nearest full page.
/// - Parameter aNumItems: The number of bytes the new data object can initially contain.
/// - Returns: A new `NSMutableData` object capable of holding `aNumItems` bytes. The returned object has the same memory alignment guarantees as `malloc(_:)`.
+ (nullable instancetype)dataWithCapacity:(NSUInteger)aNumItems;
/// Creates and returns an mutable data object containing a given number of zeroed bytes.
///
/// - Parameter length: The number of bytes the new data object initially contains.
/// - Returns: A new `NSMutableData` object of `length` bytes, filled with zeros. The returned object has the same memory alignment guarantees as `malloc(_:)`.
+ (nullable instancetype)dataWithLength:(NSUInteger)length;
/// Returns an initialized mutable data object capable of holding the specified number of bytes.
///
/// This method doesn't necessarily allocate the requested memory right away. Mutable data objects allocate additional memory as needed, so `capacity` simply establishes the object's initial capacity. When it does allocate the initial memory, though, it allocates the specified amount. This method sets the length of the data object to `0`.
///
/// If the capacity specified in `capacity` is greater than four memory pages in size, this method may round the amount of requested memory up to the nearest full page.
/// - Parameter capacity: The number of bytes the data object can initially contain.
/// - Returns: An initialized `NSMutableData` object capable of holding `capacity` bytes. The returned object has the same memory alignment guarantees as `malloc(_:)`.
- (nullable instancetype)initWithCapacity:(NSUInteger)capacity;
/// Initializes and returns a mutable data object containing a given number of zeroed bytes.
///
/// - Parameter length: The number of bytes the object initially contains.
/// - Returns: An initialized `NSMutableData` object containing `length` zeroed bytes. The returned object has the same memory alignment guarantees as `malloc(_:)`.
- (nullable instancetype)initWithLength:(NSUInteger)length;

@end

@interface NSMutableData (NSMutableDataCompression)

/// Decompresses the data object's bytes.
///
/// Use this method to inflate in-memory data when you need uncompressed bytes. Specify the same algorithm used to compress the data to successfully decompress it.
///
/// The following example shows how to inflate an instance of ``NSMutableData`` compressed with the ``NSData/CompressionAlgorithm/zlib`` algorithm:
///
/// ```swift
/// do {
///     data.decompress(using: .zlib)
/// } catch {
///     print ("Decompression error: \(error)")
/// }
/// ```
/// - Parameters:
///   - algorithm: The algorithm to use for decompressing the data. For a list of available algorithms, see ``NSData/CompressionAlgorithm``.
///   - error: On return, a pointer to an ``NSError`` instance that indicates why decompressing the data failed, or `nil` if no error occurred.
- (BOOL)decompressUsingAlgorithm:(NSDataCompressionAlgorithm)algorithm error:(NSError **)error API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0));
/// Compresses the data object's bytes using an algorithm that you specify.
///
/// Use this method to compress in-memory data when you want to reduce memory usage and can afford the time to compress and decompress the data. If your data object is already in a compressed format, such as media formats like JPEG images or AAC audio, ``NSMutableData/compress(using:)`` may provide minimal or no benefit.
///
/// The following example shows how to compress data from a string and prints the sizes of the data instances to illustrate the amount of compression:
///
/// ```swift
/// var string = "NSData and its mutable subclass NSMutableData provide data objects, or object-oriented wrappers for byte buffers. Data objects let simple allocated buffers (that is, data with no embedded pointers) take on the behavior of Foundation objects."
/// let data = NSMutableData(data: Data(string.utf8))
/// print ("original data size: \(data.length)")
/// do {
///     try data.compress(using: .zlib)
///     print("zlib compressed size: \(data.length)")
/// } catch {
///     print ("Compression error: \(error)")
/// }
/// // Prints:
/// //  original data size: 241
/// //  zlib compressed size: 158
/// ```
/// - Parameters:
///   - algorithm: The algorithm to use to compress the data. For a list of available algorithms, see ``NSData/CompressionAlgorithm``.
///   - error: On return, a pointer to an ``NSError`` instance that indicates why compressing the data failed, or `nil` if no error occurred.
- (BOOL)compressUsingAlgorithm:(NSDataCompressionAlgorithm)algorithm error:(NSError **)error API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0));

@end

#if !0
/* ***************	    Purgeable Data	****************/

/// A mutable data object containing bytes that can be discarded when they're no longer needed.
///
/// ``NSPurgeableData`` objects inherit their creation methods from their superclass, ``NSMutableData`` while providing a default implementation of the ``NSDiscardableContent`` protocol.
///
/// All ``NSPurgeableData`` objects begin "accessed" to ensure that they are not instantly discarded. The ``NSDiscardableContent/beginContentAccess()`` method marks the object's bytes as "accessed," thus protecting them from being discarded, and must be called before accessing the object, or else an exception will be raised. This method returns <doc://com.apple.documentation/documentation/swift/true> if the bytes have not been discarded and if they have been successfully marked as "accessed". Any method that directly or indirectly accesses these bytes or their length when they are not "accessed" will raise an exception. When you are done with the data, call ``NSDiscardableContent/endContentAccess()`` to allow them to be discarded in order to quickly free up memory.
///
/// You may use these objects by themselves, and do not necessarily have to use them in conjunction with ``NSCache`` to get the purging behavior. The ``NSCache`` class incorporates a caching mechanism with some auto-removal policies to ensure that its memory footprint does not get too large.
///
/// ``NSPurgeableData`` objects should not be used as keys in hashing-based collections, because the value of the bytes pointer can change after every mutation of the data.
API_AVAILABLE(macos(10.6), ios(4.0), watchos(2.0), tvos(9.0))
@interface NSPurgeableData : NSMutableData <NSDiscardableContent>
@end
#endif

NS_HEADER_AUDIT_END(nullability, sendability)
