/*	NSFileHandle.h
	Copyright (c) 1995-2019, Apple Inc. All rights reserved.
*/

#import <Foundation/NSObject.h>
#import <Foundation/NSArray.h>
#import <Foundation/NSRange.h>
#import <Foundation/NSException.h>
#import <Foundation/NSNotification.h>
#import <Foundation/NSRunLoop.h>

@class NSString, NSData, NSError;

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

/// An object-oriented wrapper for a file descriptor.
///
/// You use file handle objects to access data associated with files, sockets, pipes, and devices. For files, you can read, write, and seek within the file. For sockets, pipes, and devices, you can use a file handle object to monitor the device and process data asynchronously.
///
/// Most creation methods for ``FileHandle`` cause the file handle object to take ownership of the associated file descriptor. This means that the file handle object both creates the file descriptor and is responsible for closing it later, usually when the system deallocates the file handle object. If you want to use a file handle object with a file descriptor that you created, use the ``init(fileDescriptor:)`` method or use the ``init(fileDescriptor:closeOnDealloc:)`` method and pass <doc://com.apple.documentation/documentation/swift/false> for the `flag` parameter.
///
/// ### Run Loop Considerations
///
/// When using a file handle object to communicate asynchronously with a socket, you must initiate the corresponding operations from a thread with an active run loop. Although the read, accept, and wait operations themselves are performed asynchronously on background threads, the file handle uses a run loop source to monitor the operations and notify your code appropriately. Therefore, you must call those methods from your application's main thread or from any thread where you've configured a run loop and are using it to process events.
NS_SWIFT_SENDABLE
@interface NSFileHandle : NSObject <NSSecureCoding>

/// The data currently available in the receiver.
///
/// If the receiver is a file, returns the data obtained by reading the file from the current file pointer to the end of the file. If the receiver is a communications channel, reads up to a buffer of data and returns it; if no data is available, the method blocks. Returns an empty data object if the end of file has been reached. Raises ``NSExceptionName/fileHandleOperationException`` upon failure.
@property (readonly, copy) NSData *availableData;

/// Creates and returns a file handle object associated with the specified file descriptor and deallocation policy.
///
/// - Parameters:
///   - fd: The POSIX file descriptor with which to initialize the file handle. This descriptor represents an open file or socket that you created previously. For example, when creating a file handle for a socket, you would pass the value returned by the `socket` function.
///   - closeopt: `YES` if the returned file handle object should take ownership of the file descriptor and close it for you or `NO` if you want to maintain ownership of the file descriptor.
/// - Returns: An initialized file handle object.
///
/// If `flag` is `NO`, you are responsible for closing the file descriptor at some point after disposing of the file handle object. If you want the file handle object to close the descriptor for you automatically, pass `YES` for the `flag` parameter. The file handle does not close the descriptor if you release the file handle after sending ``FileHandle/closeFile()`` or ``FileHandle/close()``.
- (instancetype)initWithFileDescriptor:(int)fd closeOnDealloc:(BOOL)closeopt NS_DESIGNATED_INITIALIZER;
/// Returns a file handle initialized from data in an unarchiver.
- (nullable instancetype)initWithCoder:(NSCoder *)coder NS_DESIGNATED_INITIALIZER;

/// Reads the available data synchronously up to the end of file or maximum number of bytes.
///
/// - Returns: The data available through the receiver up to the maximum size that can be represented by an `NSData` object.
///
/// This method invokes ``FileHandle/readData(ofLength:)`` as part of its implementation.
- (nullable NSData *)readDataToEndOfFileAndReturnError:(out NSError **)error
    API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0)) NS_REFINED_FOR_SWIFT;

/// Reads data synchronously up to the specified number of bytes.
///
/// - Parameters:
///   - length: The number of bytes to read from the receiver.
///   - error: If an error occurs, upon return contains an `NSError` object that describes the problem.
/// - Returns: The data available through the receiver up to a maximum of `length` bytes, or `nil` if an error occurred.
///
/// If the receiver is a file, this method returns data obtained by reading `length` bytes starting at the current file pointer. If `length` bytes are not available, returns as many bytes as are available. Returns an empty `NSData` when the end of file is reached.
- (nullable NSData *)readDataUpToLength:(NSUInteger)length error:(out NSError **)error
    API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0)) NS_REFINED_FOR_SWIFT;

/// Writes the specified data synchronously to the file handle.
///
/// - Parameters:
///   - data: The data to write.
///   - error: If an error occurs, upon return contains an `NSError` object that describes the problem.
/// - Returns: `YES` if the data was written successfully; otherwise, `NO`.
///
/// This method writes data at the current file pointer, advancing the file pointer.
- (BOOL)writeData:(NSData *)data error:(out NSError **)error
    API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0)) NS_REFINED_FOR_SWIFT;

/// Gets the position of the file pointer within the file.
///
/// - Parameters:
///   - offsetInFile: On return, contains the file offset.
///   - error: If an error occurs, upon return contains an `NSError` object that describes the problem.
/// - Returns: `YES` if the offset was retrieved successfully; otherwise, `NO`.
- (BOOL)getOffset:(out unsigned long long *)offsetInFile error:(out NSError **)error
    API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0)) NS_REFINED_FOR_SWIFT;

/// Places the file pointer at the end of the file and returns the new file offset.
///
/// - Parameters:
///   - offsetInFile: On return, contains the new file offset, which is the file size.
///   - error: If an error occurs, upon return contains an `NSError` object that describes the problem.
/// - Returns: `YES` if the operation succeeded; otherwise, `NO`.
- (BOOL)seekToEndReturningOffset:(out unsigned long long *_Nullable)offsetInFile error:(out NSError **)error
    API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0)) NS_REFINED_FOR_SWIFT;

/// Moves the file pointer to the specified offset within the file.
///
/// - Parameters:
///   - offset: The offset to seek to.
///   - error: If an error occurs, upon return contains an `NSError` object that describes the problem.
/// - Returns: `YES` if the operation succeeded; otherwise, `NO`.
- (BOOL)seekToOffset:(unsigned long long)offset error:(out NSError **)error
    API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0));

/// Truncates or extends the file represented by the file handle to a specified offset within the file and puts the file pointer at that position.
///
/// - Parameters:
///   - offset: The offset within the file that will mark the new end of the file.
///   - error: If an error occurs, upon return contains an `NSError` object that describes the problem.
/// - Returns: `YES` if the operation succeeded; otherwise, `NO`.
///
/// If the file is extended (if `offset` is beyond the current end of file), the added characters are null bytes.
- (BOOL)truncateAtOffset:(unsigned long long)offset error:(out NSError **)error
    API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0));

/// Causes all in-memory data and attributes of the file represented by the file handle to write to permanent storage.
///
/// This method should be invoked by programs that require the file to be in a known state. Invocation of this method does not return until memory is flushed.
- (BOOL)synchronizeAndReturnError:(out NSError **)error
    API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0));

/// Disallows further access to the represented file or communications channel and signals end of file on communications channels that permit writing.
///
/// If the file handle object owns its file descriptor, it automatically closes that descriptor when it is deallocated. If you initialized the file handle object using the ``FileHandle/init(fileDescriptor:closeOnDealloc:)`` method, the file handle object takes ownership of the file descriptor if you passed `YES` for the `flag` parameter. After invoking this method, you may still need to release the file handle object, but the object should not be used to read from or write to the file.
- (BOOL)closeAndReturnError:(out NSError **)error
    API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0));

@end

@interface NSFileHandle (NSFileHandleCreation)

/// The file handle associated with the standard input file.
///
/// Conventionally this is a terminal device on which the user enters a stream of data. There is one standard input file handle per process; it is a shared instance.
@property (class, readonly, strong) NSFileHandle *fileHandleWithStandardInput;
/// The file handle associated with the standard output file.
///
/// Conventionally this is a terminal device that receives a stream of data from a program. There is one standard output file handle per process; it is a shared instance.
@property (class, readonly, strong) NSFileHandle *fileHandleWithStandardOutput;
/// The file handle associated with the standard error file.
///
/// Conventionally this is a terminal device to which error messages are sent. There is one standard error file handle per process; it is a shared instance.
@property (class, readonly, strong) NSFileHandle *fileHandleWithStandardError;
/// The file handle associated with a null device.
///
/// You can use the returned file handle as a "stand in" for standard file handles. Reads from the null-device file handle return an empty ``NSData`` object. Writes to it are discarded. The ``FileHandle/fileDescriptor`` property returns an illegal value. The ``FileHandle/close()`` method has no effect.
@property (class, readonly, strong) NSFileHandle *fileHandleWithNullDevice;

/// Returns a file handle initialized for reading the file, device, or named socket at the specified path.
///
/// - Parameter path: The path to the file, device, or named socket to access.
/// - Returns: The initialized file handle object or `nil` if no file exists at `path`.
///
/// The file pointer is set to the beginning of the file. You cannot write data to the returned file handle object. The returned object responds only to ``FileHandle/readData(ofLength:)``, ``FileHandle/readDataToEndOfFile()``, and ``FileHandle/availableData``. The file handle owns its file descriptor.
+ (nullable instancetype)fileHandleForReadingAtPath:(NSString *)path;
/// Returns a file handle initialized for writing to the file, device, or named socket at the specified path.
///
/// - Parameter path: The path to the file, device, or named socket to access.
/// - Returns: The initialized file handle object or `nil` if no file exists at `path`.
///
/// The file pointer is set to the beginning of the file. You cannot read data from the returned file handle object. Use ``FileHandle/write(_:)`` to write data to the returned file handle object. The file handle owns its file descriptor.
+ (nullable instancetype)fileHandleForWritingAtPath:(NSString *)path;
/// Returns a file handle initialized for reading and writing to the file, device, or named socket at the specified path.
///
/// - Parameter path: The path to the file, device, or named socket to access.
/// - Returns: The initialized file handle object or `nil` if no file exists at `path`.
///
/// The file pointer is set to the beginning of the file. The returned object responds to both read and write messages.
+ (nullable instancetype)fileHandleForUpdatingAtPath:(NSString *)path;

/// Returns a file handle initialized for reading the file, device, or named socket at the specified URL.
///
/// - Parameters:
///   - url: The URL of the file, device, or named socket to access.
///   - error: If an error occurs, upon return contains an `NSError` object that describes the problem. Pass `NULL` if you do not want error information.
/// - Returns: The initialized file handle object or `nil` if no file exists at `url`.
///
/// The file pointer is set to the beginning of the file. You cannot write data to the returned file handle object.
/// Use the ``FileHandle/readDataToEndOfFile()`` or ``FileHandle/readData(ofLength:)`` methods to read data from it.
///
/// When using this method to create a file handle object, the file handle owns its associated file descriptor
/// and is responsible for closing it.
+ (nullable instancetype)fileHandleForReadingFromURL:(NSURL *)url error:(NSError **)error API_AVAILABLE(macos(10.6), ios(4.0), watchos(2.0), tvos(9.0));
/// Returns a file handle initialized for writing to the file, device, or named socket at the specified URL.
///
/// - Parameters:
///   - url: The URL of the file, device, or named socket to access.
///   - error: If an error occurs, upon return contains an `NSError` object that describes the problem. Pass `NULL` if you do not want error information.
/// - Returns: The initialized file handle object or `nil` if no file exists at `url`.
///
/// The file pointer is set to the beginning of the file. The returned object responds only to ``FileHandle/write(_:)``.
///
/// When using this method to create a file handle object, the file handle owns its associated file descriptor
/// and is responsible for closing it.
+ (nullable instancetype)fileHandleForWritingToURL:(NSURL *)url error:(NSError **)error API_AVAILABLE(macos(10.6), ios(4.0), watchos(2.0), tvos(9.0));
/// Returns a file handle initialized for reading and writing to the file, device, or named socket at the specified URL.
///
/// - Parameters:
///   - url: The URL of the file, device, or named socket to access.
///   - error: If an error occurs, upon return contains an `NSError` object that describes the problem. Pass `NULL` if you do not want error information.
/// - Returns: The initialized file handle object or `nil` if no file exists at `url`.
///
/// The file pointer is set to the beginning of the file. The returned object responds to both read and ``FileHandle/write(_:)`` messages.
///
/// When using this method to create a file handle object, the file handle owns its associated file descriptor
/// and is responsible for closing it.
+ (nullable instancetype)fileHandleForUpdatingURL:(NSURL *)url error:(NSError **)error API_AVAILABLE(macos(10.6), ios(4.0), watchos(2.0), tvos(9.0));

@end

/// The name of a file-operation exception.
FOUNDATION_EXPORT NSExceptionName const NSFileHandleOperationException;

/// Posted when the file handle reads the data currently available in a file or at a communications channel.
///
/// The notification object is the ``FileHandle`` object that sent the notification. To cause the posting of this notification, you must send either ``FileHandle/readInBackgroundAndNotify()`` or ``FileHandle/readInBackgroundAndNotify(forModes:)`` to an appropriate file handle object. The notification's `userInfo` dictionary contains the `NSFileHandleNotificationDataItem` key.
FOUNDATION_EXPORT NSNotificationName const NSFileHandleReadCompletionNotification;
/// Posted when the file handle reads all data in the file or, if a communications channel, until the other process signals the end of data.
FOUNDATION_EXPORT NSNotificationName const NSFileHandleReadToEndOfFileCompletionNotification;
/// Posted when an ``FileHandle`` object establishes a socket connection between two processes, creates a ``FileHandle`` object for one end of the connection, and makes this object available to observers by putting it in the `userInfo` dictionary.
FOUNDATION_EXPORT NSNotificationName const NSFileHandleConnectionAcceptedNotification;
/// Posted when the file handle determines that data is currently available for reading in a file or at a communications channel.
FOUNDATION_EXPORT NSNotificationName const NSFileHandleDataAvailableNotification;

/// A key in a userInfo dictionary to access the data object received by a ``FileHandle/readCompletionNotification``.
FOUNDATION_EXPORT NSString * const NSFileHandleNotificationDataItem;
/// A key in a userInfo dictionary to access the ``FileHandle`` object of a connected-socket.
FOUNDATION_EXPORT NSString * const NSFileHandleNotificationFileHandleItem;
/// Currently unused.
FOUNDATION_EXPORT NSString * const NSFileHandleNotificationMonitorModes API_DEPRECATED("Not supported", macos(10.0,10.7), ios(2.0,5.0), watchos(2.0,2.0), tvos(9.0,9.0));

@interface NSFileHandle (NSFileHandleAsynchronousAccess)

/// Reads from the file or communications channel in the background and posts a notification when finished.
///
/// - Parameter modes: The runloop modes in which the read completion notification can be posted.
///
/// See ``FileHandle/readInBackgroundAndNotify()`` for details. This method differs in that the notification is queued for posting in the specified run-loop modes.
- (void)readInBackgroundAndNotifyForModes:(nullable NSArray<NSRunLoopMode> *)modes;
/// Reads from the file or communications channel in the background and posts a notification when finished.
///
/// This method performs an asynchronous ``FileHandle/availableData`` operation on a file or communications channel and posts an ``FileHandle/readCompletionNotification``. You must call this method from a thread that has an active run loop.
- (void)readInBackgroundAndNotify;

/// Reads to the end of file from the file or communications channel in the background and posts a notification when finished.
///
/// - Parameter modes: The runloop modes in which the read completion notification can be posted.
///
/// See ``FileHandle/readToEndOfFileInBackgroundAndNotify()`` for details. This method differs in that the notification is queued for posting in the specified run-loop modes.
- (void)readToEndOfFileInBackgroundAndNotifyForModes:(nullable NSArray<NSRunLoopMode> *)modes;
/// Reads to the end of file from the file or communications channel in the background and posts a notification when finished.
///
/// This method performs an asynchronous ``FileHandle/readDataToEndOfFile()`` operation on a file or communications channel and posts an `NSFileHandleReadToEndOfFileCompletionNotification`. You must call this method from a thread that has an active run loop.
- (void)readToEndOfFileInBackgroundAndNotify;

/// Accepts a socket connection (for stream-type sockets only) in the background and creates a file handle for the "near" (client) end of the communications channel.
///
/// - Parameter modes: The runloop modes in which the connection accepted notification can be posted.
///
/// See ``FileHandle/acceptConnectionInBackgroundAndNotify()`` for details. This method differs in that the notification is queued for posting in the specified run-loop modes.
- (void)acceptConnectionInBackgroundAndNotifyForModes:(nullable NSArray<NSRunLoopMode> *)modes;
/// Accepts a socket connection (for stream-type sockets only) in the background and creates a file handle for the "near" (client) end of the communications channel.
///
/// This method asynchronously creates a file handle for the other end of the socket connection and returns that object by posting an `NSFileHandleConnectionAcceptedNotification`. The notification includes a `userInfo` dictionary with the created ``FileHandle`` object, accessible using the `NSFileHandleNotificationFileHandleItem` key.
///
/// You must call this method from a thread that has an active run loop.
- (void)acceptConnectionInBackgroundAndNotify;

/// Asynchronously checks to see if data is available.
///
/// - Parameter modes: The runloop modes in which the data available notification can be posted.
///
/// See ``FileHandle/waitForDataInBackgroundAndNotify()`` for details. This method differs in that the notification is queued for posting in the specified run-loop modes.
- (void)waitForDataInBackgroundAndNotifyForModes:(nullable NSArray<NSRunLoopMode> *)modes;
/// Asynchronously checks to see if data is available.
///
/// When the data becomes available, this method posts a ``FileHandle/dataAvailableNotification`` notification on the current thread. You must call this method from a thread that has an active run loop.
- (void)waitForDataInBackgroundAndNotify;

#ifdef __BLOCKS__
/// The block to use for reading the contents of the file handle asynchronously.
///
/// The default value is `nil`. To read data asynchronously, assign a non-nil block. Doing so creates a dispatch source for the associated file descriptor and submits the block to that source when data arrives. Set to `nil` to stop reading.
@property (nullable, copy) void (NS_SWIFT_SENDABLE ^readabilityHandler)(NSFileHandle *)  API_AVAILABLE(macos(10.7), ios(5.0), watchos(2.0), tvos(9.0));
/// The block to use for writing the contents of the file handle asynchronously.
///
/// The default value is `nil`. To write data asynchronously, assign a non-nil block. Doing so creates a dispatch source for the associated file descriptor and submits the block when the file handle has room for data. Set to `nil` to stop.
@property (nullable, copy) void (NS_SWIFT_SENDABLE ^writeabilityHandler)(NSFileHandle *) API_AVAILABLE(macos(10.7), ios(5.0), watchos(2.0), tvos(9.0));
#endif

@end

@interface NSFileHandle (NSFileHandlePlatformSpecific)

/// Creates and returns a file handle object associated with the specified file descriptor.
///
/// - Parameter fd: The POSIX file descriptor.
/// - Returns: A file handle initialized with `fileDescriptor`.
///
/// The file descriptor is not owned by the file handle object, so you are responsible for closing the file descriptor at some point after disposing of the file handle object. You can create a file handle for a socket by using the result of a `socket` call as `fileDescriptor`.
- (instancetype)initWithFileDescriptor:(int)fd;

/// The POSIX file descriptor associated with the receiver.
///
/// You can use this property to get the file descriptor while it is open. If the file handle object owns the file descriptor, you must not close it yourself. However, you can use the ``FileHandle/close()`` method to close the file handle, which also closes the file descriptor. If the receiver is not the owner of the file descriptor, closing the file descriptor while the file handle is still associated with it raises ``NSExceptionName/fileHandleOperationException``.
@property (readonly) int fileDescriptor;

@end

@interface NSFileHandle (/* Deprecations */)

/* The API below may throw exceptions and will be deprecated in a future version of the OS.
 Use their replacements instead. */

/// Reads the available data synchronously up to the end of file or maximum number of bytes.
///
/// @DeprecationSummary {
///     Use ``FileHandle/readToEnd()`` in Swift, or `readDataToEndOfFileAndReturnError:` in Objective-C.
/// }
///
/// - Returns: The data available through the receiver up to the maximum size that can be represented by an `NSData` object.
///
/// This method invokes ``FileHandle/readData(ofLength:)`` as part of its implementation. Raises ``NSExceptionName/fileHandleOperationException`` upon failure.
- (NSData *)readDataToEndOfFile
    API_DEPRECATED_WITH_REPLACEMENT("readDataToEndOfFileAndReturnError:",
                                    macos(10.0, API_TO_BE_DEPRECATED), ios(2.0, API_TO_BE_DEPRECATED),
                                    watchos(2.0, API_TO_BE_DEPRECATED), tvos(9.0, API_TO_BE_DEPRECATED));

/// Reads data synchronously up to the specified number of bytes.
///
/// @DeprecationSummary {
///     Use ``FileHandle/read(upToCount:)`` in Swift, or `readDataUpToLength:error:` in Objective-C.
/// }
///
/// - Parameter length: The number of bytes to read from the receiver.
/// - Returns: The data available through the receiver up to a maximum of `length` bytes.
///
/// If the receiver is a file, this method returns data obtained by reading `length` bytes starting at the current file pointer. Returns an empty `NSData` when the end of file is reached. Raises ``NSExceptionName/fileHandleOperationException`` upon failure.
- (NSData *)readDataOfLength:(NSUInteger)length
    API_DEPRECATED_WITH_REPLACEMENT("readDataUpToLength:error:",
                                    macos(10.0, API_TO_BE_DEPRECATED), ios(2.0, API_TO_BE_DEPRECATED),
                                    watchos(2.0, API_TO_BE_DEPRECATED), tvos(9.0, API_TO_BE_DEPRECATED));


/// Writes the specified data synchronously to the file handle.
///
/// @DeprecationSummary {
///     Use ``FileHandle/write(contentsOf:)`` in Swift, or `writeData:error:` in Objective-C.
/// }
///
/// - Parameter data: The data to write.
///
/// This method writes data at the current file pointer, advancing the file pointer. Raises ``NSExceptionName/fileHandleOperationException`` upon failure.
- (void)writeData:(NSData *)data
    API_DEPRECATED_WITH_REPLACEMENT("writeData:error:",
                                    macos(10.0, API_TO_BE_DEPRECATED), ios(2.0, API_TO_BE_DEPRECATED),
                                    watchos(2.0, API_TO_BE_DEPRECATED), tvos(9.0, API_TO_BE_DEPRECATED));


/// The position of the file pointer within the file represented by the file handle.
///
/// @DeprecationSummary {
///     Use ``FileHandle/offset()`` in Swift, or `getOffset:error:` in Objective-C.
/// }
///
/// Raises ``NSExceptionName/fileHandleOperationException`` if the message is sent to a file handle representing a pipe or socket, or if the file descriptor is closed.
@property (readonly) unsigned long long offsetInFile
    API_DEPRECATED_WITH_REPLACEMENT("getOffset:error:",
                                    macos(10.0, API_TO_BE_DEPRECATED), ios(2.0, API_TO_BE_DEPRECATED),
                                    watchos(2.0, API_TO_BE_DEPRECATED), tvos(9.0, API_TO_BE_DEPRECATED));

/// Places the file pointer at the end of the file referenced by the file handle and returns the new file offset.
///
/// @DeprecationSummary {
///     Use ``FileHandle/seekToEnd()`` in Swift, or `seekToEndReturningOffset:error:` in Objective-C.
/// }
///
/// - Returns: The file offset with the file pointer at the end of the file. This is the size of the file.
///
/// Raises ``NSExceptionName/fileHandleOperationException`` if the message is sent to a file handle representing a pipe or socket, or if the file descriptor is closed.
- (unsigned long long)seekToEndOfFile
    API_DEPRECATED_WITH_REPLACEMENT("seekToEndReturningOffset:error:",
                                    macos(10.0, API_TO_BE_DEPRECATED), ios(2.0, API_TO_BE_DEPRECATED),
                                    watchos(2.0, API_TO_BE_DEPRECATED), tvos(9.0, API_TO_BE_DEPRECATED));

/// Moves the file pointer to the specified offset within the file represented by the receiver.
///
/// @DeprecationSummary {
///     Use ``FileHandle/seek(toOffset:)`` instead.
/// }
///
/// - Parameter offset: The offset to seek to.
///
/// Raises ``NSExceptionName/fileHandleOperationException`` if the message is sent to a file handle representing a pipe or socket, or if the file descriptor is closed.
- (void)seekToFileOffset:(unsigned long long)offset
    API_DEPRECATED_WITH_REPLACEMENT("seekToOffset:error:",
                                    macos(10.0, API_TO_BE_DEPRECATED), ios(2.0, API_TO_BE_DEPRECATED),
                                    watchos(2.0, API_TO_BE_DEPRECATED), tvos(9.0, API_TO_BE_DEPRECATED));


/// Truncates or extends the file represented by the file handle to a specified offset within the file and puts the file pointer at that position.
///
/// @DeprecationSummary {
///     Use ``FileHandle/truncate(atOffset:)`` instead.
/// }
///
/// - Parameter offset: The offset within the file that will mark the new end of the file.
///
/// If the file is extended (if `offset` is beyond the current end of file), the added characters are null bytes. Raises ``NSExceptionName/fileHandleOperationException`` upon failure.
- (void)truncateFileAtOffset:(unsigned long long)offset
    API_DEPRECATED_WITH_REPLACEMENT("truncateAtOffset:error:",
                                    macos(10.0, API_TO_BE_DEPRECATED), ios(2.0, API_TO_BE_DEPRECATED),
                                    watchos(2.0, API_TO_BE_DEPRECATED), tvos(9.0, API_TO_BE_DEPRECATED));

/// Causes all in-memory data and attributes of the file represented by the handle to write to permanent storage.
///
/// @DeprecationSummary {
///     Use ``FileHandle/synchronize()`` instead.
/// }
///
/// This method should be invoked by programs that require the file to be in a known state. Invocation of this method does not return until memory is flushed. Raises ``NSExceptionName/fileHandleOperationException`` upon failure.
- (void)synchronizeFile
    API_DEPRECATED_WITH_REPLACEMENT("synchronizeAndReturnError:",
                                    macos(10.0, API_TO_BE_DEPRECATED), ios(2.0, API_TO_BE_DEPRECATED),
                                    watchos(2.0, API_TO_BE_DEPRECATED), tvos(9.0, API_TO_BE_DEPRECATED));

/// Disallows further access to the represented file or communications channel and signals end of file on communications channels that permit writing.
///
/// @DeprecationSummary {
///     Use ``FileHandle/close()`` to handle errors when closing a file.
/// }
///
/// If the file handle object owns its file descriptor, it automatically closes that descriptor when it is deallocated. After invoking this method, you may still need to release the file handle object, but the object should not be used to read from or write to the file.
- (void)closeFile
    API_DEPRECATED_WITH_REPLACEMENT("closeAndReturnError:",
                                    macos(10.0, API_TO_BE_DEPRECATED), ios(2.0, API_TO_BE_DEPRECATED),
                                    watchos(2.0, API_TO_BE_DEPRECATED), tvos(9.0, API_TO_BE_DEPRECATED));


@end

/// A one-way communications channel between related processes.
///
/// ``Pipe`` objects provide an object-oriented interface for accessing pipes. An ``Pipe`` object represents both ends of a pipe and enables communication through the pipe. A pipe is a one-way communications channel between related processes; one process writes data, while the other process reads that data. The data that passes through the pipe is buffered; the size of the buffer is determined by the underlying operating system. ``Pipe`` is an abstract class, the public interface of a class cluster.
NS_SWIFT_SENDABLE
@interface NSPipe : NSObject

/// The receiver's read file handle.
@property (readonly, retain) NSFileHandle *fileHandleForReading;
/// The receiver's write file handle.
@property (readonly, retain) NSFileHandle *fileHandleForWriting;

/// Returns a new `NSPipe` object.
+ (NSPipe *)pipe;

@end

NS_HEADER_AUDIT_END(nullability, sendability)
