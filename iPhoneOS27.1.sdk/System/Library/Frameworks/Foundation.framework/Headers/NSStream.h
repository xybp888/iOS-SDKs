/*	NSStream.h
        Copyright (c) 2003-2019, Apple Inc. All rights reserved
*/

#import <Foundation/NSObject.h>
#import <Foundation/NSError.h>

@class NSData, NSDictionary, NSError, NSHost, NSInputStream, NSOutputStream, NSRunLoop, NSString, NSURL;
@protocol NSStreamDelegate;

/// `NSStream` defines these string constants as keys for accessing stream properties using ``Stream/property(forKey:)`` and setting properties with ``Stream/setProperty(_:forKey:)``.
typedef NSString * NSStreamPropertyKey NS_TYPED_EXTENSIBLE_ENUM;

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

/// The type declared for the constants that indicate the current status of a stream.
typedef NS_ENUM(NSUInteger, NSStreamStatus) {
    /// The stream is not open for reading or writing. This status is returned before the underlying call to open a stream but after it's been created.
    NSStreamStatusNotOpen = 0,
    /// The stream is in the process of being opened for reading or for writing. For network streams, this status might include the time after the stream was opened, but while network DNS resolution is happening.
    NSStreamStatusOpening = 1,
    /// The stream is open, but no reading or writing is occurring.
    NSStreamStatusOpen = 2,
    /// Data is being read from the stream.
    NSStreamStatusReading = 3,
    /// Data is being written to the stream.
    NSStreamStatusWriting = 4,
    /// There is no more data to read, or no more data can be written to the stream.
    NSStreamStatusAtEnd = 5,
    /// The stream is closed.
    NSStreamStatusClosed = 6,
    /// The remote end of the connection can't be contacted, or the connection has been severed for some other reason.
    NSStreamStatusError = 7
};

/// Describes the constants that may be sent to the delegate as a bit field to specify the kind of stream event.
typedef NS_OPTIONS(NSUInteger, NSStreamEvent) {
    /// No event has occurred.
    NSStreamEventNone = 0,
    /// The open has completed successfully.
    NSStreamEventOpenCompleted = 1UL << 0,
    /// The stream has bytes to be read.
    NSStreamEventHasBytesAvailable = 1UL << 1,
    /// The stream can accept bytes for writing.
    NSStreamEventHasSpaceAvailable = 1UL << 2,
    /// An error has occurred on the stream.
    NSStreamEventErrorOccurred = 1UL << 3,
    /// The end of the stream has been reached.
    NSStreamEventEndEncountered = 1UL << 4
};

// NSStream is an abstract class encapsulating the common API to NSInputStream and NSOutputStream.
// Subclassers of NSInputStream and NSOutputStream must also implement these methods.
/// An abstract class representing a stream.
///
/// This class's interface is common to all Cocoa stream classes, including its concrete subclasses ``InputStream`` and ``OutputStream``.
///
/// ``Stream`` objects provide an easy way to read and write data to and from a variety of media in a device-independent way. You can create stream objects for data located in memory, in a file, or on a network (using sockets), and you can use stream objects without loading all of the data into memory at once.
///
/// By default, ``Stream`` instances that aren't file-based are non-seekable, one-way streams (although custom seekable subclasses are possible). After you provide or consume data, you can't retrieve the data from the stream.
///
/// ### Subclassing Notes
///
/// ``Stream`` is an abstract class, incapable of instantiation and intended for you to subclass it. It publishes a programmatic interface that all subclasses must adopt and provide implementations for. The two Apple-provided concrete subclasses of ``Stream``, ``InputStream`` and ``OutputStream``, are suitable for most purposes. However, there might be situations when you want a peer subclass to ``InputStream`` and ``OutputStream``. For example, you might want a class that implements a full-duplex (two-way) stream, or a class whose instances are capable of seeking through a stream.
///
/// #### Methods to Override
///
/// All subclasses must fully implement the following methods:
///
/// - ``open()`` and ``close()``
///
/// Implement ``open()`` to open the stream for reading or writing and make the stream available to the client directly or, if the stream object is scheduled on a run loop, to the delegate. Implement ``close()`` to close the stream and remove the stream object from the run loop, if necessary. A closed stream should still be able to accept new properties and report its current properties. Once you close a stream, you can't reopen it.
/// - ``delegate``
///
/// Return and set the delegate. By a default, a stream object must be its own delegate; so a ``delegate`` message with an argument of `nil` should restore this delegate. Don't retain the delegate to prevent retain cycles.
///
/// To learn about delegates and delegation, read "Delegation" in Cocoa Fundamentals Guide.
/// - ``schedule(in:forMode:)`` and ``remove(from:forMode:)``
///
/// Implement ``schedule(in:forMode:)`` to schedule the stream object on the specified run loop for the specified mode. Implement ``remove(from:forMode:)`` to remove the object from the run loop. See the documentation of the ``RunLoop`` class for details. Once the stream object for an open stream is scheduled on a run loop, it is the responsibility of the subclass as it processes stream data to send ``StreamDelegate/stream(_:handle:)`` messages to its delegate.
/// - ``property(forKey:)`` and ``setProperty(_:forKey:)``
///
/// Implement these methods to return and set, respectively, the property value for the specified key. You may add custom properties, but be sure to handle all properties defined by ``Stream`` as well.
/// - ``streamStatus`` and ``streamError``
///
/// Implement ``streamStatus`` to return the current status of the stream as a ``Status`` constant; you may define new ``Status`` constants, but be sure to handle the system defined constants properly. Implement ``streamError`` to return an ``NSError`` object representing the current error. You might decide to return a custom ``NSError`` object that can provide complete and localized information about the error.
@interface NSStream : NSObject
/// Opens the receiving stream.
///
/// A stream must be created before it can be opened. Once opened, a stream cannot be closed and reopened.
- (void)open;
/// Closes the receiver.
///
/// Closing the stream terminates the flow of bytes and releases system resources that were reserved for the stream when it was opened. If the stream has been scheduled on a run loop, closing the stream implicitly removes the stream from the run loop. A stream that is closed can still be queried for its properties.
- (void)close;

/// The receiver's delegate.
///
/// By default, a stream is its own delegate, and subclasses of `NSInputStream` and `NSOutputStream` must maintain this contract. If you override this method in a subclass, passing `nil` must restore the receiver as its own delegate. Delegates are not retained.
@property (nullable, assign /* actually weak */) id <NSStreamDelegate> delegate;

/// Returns the receiver's property for a given key.
/// - Parameter key: The key for one of the receiver's properties.
/// - Returns: The receiver's property for the key `key`.
- (nullable id)propertyForKey:(NSStreamPropertyKey)key;
/// Attempts to set the value of a given property of the receiver and returns a Boolean value that indicates whether the value is accepted by the receiver.
/// - Parameters:
///   - property: The value for `key`.
///   - key: The key for one of the receiver's properties.
/// - Returns: `YES` if the value is accepted by the receiver, otherwise `NO`.
- (BOOL)setProperty:(nullable id)property forKey:(NSStreamPropertyKey)key;

/// Schedules the receiver on a given run loop in a given mode.
///
/// Unless the client is polling the stream, it is responsible for ensuring that the stream is scheduled on at least one run loop and that at least one of the run loops on which the stream is scheduled is being run.
/// - Parameters:
///   - aRunLoop: The run loop on which to schedule the receiver.
///   - mode: The mode for the run loop.
- (void)scheduleInRunLoop:(NSRunLoop *)aRunLoop forMode:(NSRunLoopMode)mode;
/// Removes the receiver from a given run loop running in a given mode.
/// - Parameters:
///   - aRunLoop: The run loop on which the receiver was scheduled.
///   - mode: The mode for the run loop.
- (void)removeFromRunLoop:(NSRunLoop *)aRunLoop forMode:(NSRunLoopMode)mode;

/// The receiver's status.
@property (readonly) NSStreamStatus streamStatus;
/// An `NSError` object representing the stream error, or `nil` if no error has been encountered.
@property (nullable, readonly, copy) NSError *streamError;
@end

// NSInputStream is an abstract class representing the base functionality of a read stream.
// Subclassers are required to implement these methods.
/// A stream that provides read-only stream functionality.
///
/// ``InputStream`` is "toll-free bridged" with its Core Foundation counterpart, <doc://com.apple.documentation/documentation/corefoundation/cfreadstream>. For more information on toll-free bridging, see [Toll-Free Bridging](https://developer.apple.com/library/archive/documentation/General/Conceptual/CocoaEncyclopedia/Toll-FreeBridgin/Toll-FreeBridgin.html#//apple_ref/doc/uid/TP40010810-CH2).
///
/// ### Subclassing Notes
///
/// `NSInputStream` is an abstract superclass of a _class cluster_ consisting of concrete subclasses of `NSStream` that provide standard read-only access to stream data. Although `NSInputStream` is probably sufficient for most situations requiring access to stream data, you can create a subclass of `NSInputStream` if you want more specialized behavior (for example, you want to record statistics on the data in a stream).
///
/// #### Methods to Override
///
/// To create a subclass of `NSInputStream` you may have to implement initializers for the type of stream data supported and suitably re-implement existing initializers. You must also provide complete implementations of the following methods:
///
/// - ``read(_:maxLength:)``
///
/// From the current read index, take up to the number of bytes specified in the second parameter from the stream and place them in the client-supplied buffer (first parameter). The buffer must be of the size specified by the second parameter. Return the actual number of bytes placed in the buffer; if there is nothing left in the stream, return `0`. Reset the index into the stream for the next read operation.
/// - ``getBuffer(_:length:)``
///
/// Return in 0(1) a pointer to the subclass-allocated buffer (first parameter). Return by reference in the second parameter the number of bytes actually put into the buffer. The buffer's contents are valid only until the next stream operation. Return <doc://com.apple.documentation/documentation/swift/false> if you cannot access data in the buffer; otherwise, return <doc://com.apple.documentation/documentation/swift/true>. If this method is not appropriate for your type of stream, you may return <doc://com.apple.documentation/documentation/swift/false>.
/// - ``hasBytesAvailable``
///
/// Return <doc://com.apple.documentation/documentation/swift/true> if there is more data to read in the stream, <doc://com.apple.documentation/documentation/swift/false> if there is not. If you want to be semantically compatible with `NSInputStream`, return <doc://com.apple.documentation/documentation/swift/true> if a read must be attempted to determine if bytes are available.
@interface NSInputStream : NSStream
/// Reads up to a given number of bytes into a given buffer.
/// - Parameters:
///   - buffer: A data buffer. The buffer must be large enough to contain the number of bytes specified by `len`.
///   - len: The maximum number of bytes to read.
/// - Returns: A positive number indicates the number of bytes read; `0` indicates that the end of the buffer was reached; `-1` means that the operation failed (more information about the error can be obtained with `streamError`).
- (NSInteger)read:(uint8_t *)buffer maxLength:(NSUInteger)len;

/// Returns by reference a pointer to a read buffer and, by reference, the number of bytes available, and returns a Boolean value that indicates whether the buffer is available.
///
/// This buffer is only valid until the next stream operation. Subclassers may return `NO` for this if it is not appropriate for the stream type. This may return `NO` if the buffer is not available.
/// - Parameters:
///   - buffer: Upon return, contains a pointer to a read buffer.
///   - len: Upon return, contains the number of bytes available.
/// - Returns: `YES` if the buffer is available, otherwise `NO`.
- (BOOL)getBuffer:(uint8_t * _Nullable * _Nonnull)buffer length:(NSUInteger *)len;

/// A Boolean value that indicates whether the receiver has bytes available to read.
///
/// `YES` if the stream has bytes available or if it is impossible to tell without actually doing the read.
@property (readonly) BOOL hasBytesAvailable;

/// Initializes and returns an `NSInputStream` object for reading from a given `NSData` object.
///
/// The stream must be opened before it can be used.
/// - Parameter data: The data object from which to read. The contents of `data` are copied.
- (instancetype)initWithData:(NSData *)data NS_DESIGNATED_INITIALIZER;
/// Initializes and returns an `NSInputStream` object that reads data from the file at a given URL.
///
/// The stream must be opened before it can be used.
/// - Parameter url: The URL to the file.
- (nullable instancetype)initWithURL:(NSURL *)url API_AVAILABLE(macos(10.6), ios(4.0), watchos(2.0), tvos(9.0)) NS_DESIGNATED_INITIALIZER;

@end

// NSOutputStream is an abstract class representing the base functionality of a write stream.
// Subclassers are required to implement these methods.
/// A stream that provides write-only stream functionality.
///
/// ``OutputStream`` is "toll-free bridged" with its Core Foundation counterpart, <doc://com.apple.documentation/documentation/corefoundation/cfwritestream>. For more information on toll-free bridging, see [Toll-Free Bridging](https://developer.apple.com/library/archive/documentation/General/Conceptual/CocoaEncyclopedia/Toll-FreeBridgin/Toll-FreeBridgin.html#//apple_ref/doc/uid/TP40010810-CH2).
///
/// ### Subclassing Notes
///
/// `NSOutputStream` is a concrete subclass of `NSStream` that lets you write data to a stream. Although `NSOutputStream` is probably sufficient for most situations requiring this capability, you can create a subclass of `NSOutputStream` if you want more specialized behavior (for example, you want to record statistics on the data in a stream).
///
/// #### Methods to Override
///
/// To create a subclass of `NSOutputStream` you may have to implement initializers for the type of stream data supported and suitably reimplement existing initializers. You must also provide complete implementations of the following methods:
///
/// - ``write(_:maxLength:)``
///
/// From the current write pointer, take up to the number of bytes specified in the `maxLength:` parameter from the client-supplied buffer (first parameter) and put them onto the stream. The buffer must be of the size specified by the second parameter. To prepare for the next operation, offset the write pointer by the number of bytes written. Return a signed integer based on the outcome of the current operation:
///
/// - If the write operation is successful, return the actual number of bytes put onto the stream.
/// - If the stream is of a fixed length and has reached its capacity, return `0`.
/// - If there was an error writing to the stream, return `-1`.
/// - ``hasSpaceAvailable``
///
/// Return <doc://com.apple.documentation/documentation/swift/true> if the stream can currently accept more data, <doc://com.apple.documentation/documentation/swift/false> if it cannot. If you want to be semantically compatible with `NSOutputStream`, return <doc://com.apple.documentation/documentation/swift/true> if a write must be attempted to determine if space is available.
@interface NSOutputStream : NSStream
/// Writes the contents of a provided data buffer to the receiver.
/// - Parameters:
///   - buffer: The data to write.
///   - len: The length of the data buffer, in bytes. The behavior of this method is undefined if you pass a negative or zero number.
/// - Returns: A positive number indicates the number of bytes written; `0` indicates that a fixed-length stream has reached its capacity; `-1` means that the operation failed (more information about the error can be obtained with `streamError`).
- (NSInteger)write:(const uint8_t *)buffer maxLength:(NSUInteger)len;

/// A Boolean value that indicates whether the receiver can be written to.
///
/// `YES` if the stream can be written to or if a write must be attempted in order to determine if space is available, `NO` otherwise.
@property (readonly) BOOL hasSpaceAvailable;

/// Returns an initialized output stream that will write to memory.
///
/// The stream must be opened before it can be used. The contents of the memory stream are retrieved by passing `NSStreamDataWrittenToMemoryStreamKey` to `propertyForKey:`.
- (instancetype)initToMemory NS_DESIGNATED_INITIALIZER;
/// Returns an initialized output stream that can write to a provided buffer.
///
/// The stream must be opened before it can be used. When the number of bytes written to `buffer` has reached `capacity`, the stream's `streamStatus` will return `NSStreamStatusAtEnd`.
/// - Parameters:
///   - buffer: The buffer the output stream will write to.
///   - capacity: The size of the buffer in bytes.
- (instancetype)initToBuffer:(uint8_t *)buffer capacity:(NSUInteger)capacity NS_DESIGNATED_INITIALIZER;
/// Returns an initialized output stream for writing to a specified URL.
///
/// The stream must be opened before it can be used.
/// - Parameters:
///   - url: The URL to the file the output stream will write to.
///   - shouldAppend: `YES` if newly written data should be appended to any existing file contents, otherwise `NO`.
- (nullable instancetype)initWithURL:(NSURL *)url append:(BOOL)shouldAppend API_AVAILABLE(macos(10.6), ios(4.0), watchos(2.0), tvos(9.0)) NS_DESIGNATED_INITIALIZER;

@end


@interface NSStream (NSSocketStreamCreationExtensions)

/// Creates and returns by reference an `NSInputStream` object and `NSOutputStream` object for a socket connection with a given host on a given port.
/// - Parameters:
///   - hostname: The host to which to connect.
///   - port: The port to connect to on `host`.
///   - inputStream: Upon return, contains the input stream. If `nil` is passed, the stream object is not created.
///   - outputStream: Upon return, contains the output stream. If `nil` is passed, the stream object is not created.
+ (void)getStreamsToHostWithName:(NSString *)hostname port:(NSInteger)port inputStream:(NSInputStream * _Nullable * _Nullable)inputStream outputStream:(NSOutputStream * _Nullable * _Nullable)outputStream API_DEPRECATED("Use nw_connection_t in Network framework instead", macos(10.10, API_TO_BE_DEPRECATED), ios(8.0, API_TO_BE_DEPRECATED), tvos(9.0, API_TO_BE_DEPRECATED)) API_UNAVAILABLE(watchos);

#if TARGET_OS_OSX
/// Creates and returns by reference an `NSInputStream` object and `NSOutputStream` object for a socket connection with a given host on a given port.
///
/// If neither `port` nor `host` is properly specified, no socket connection is made.
///
/// - Parameters:
///   - host: The host to which to connect.
///   - port: The port to connect to on `host`.
///   - inputStream: Upon return, contains the input stream. If `nil` is passed, the stream object is not created.
///   - outputStream: Upon return, contains the output stream. If `nil` is passed, the stream object is not created.
+ (void)getStreamsToHost:(NSHost *)host port:(NSInteger)port inputStream:(NSInputStream * _Nullable * _Nullable)inputStream outputStream:(NSOutputStream * _Nullable * _Nullable)outputStream API_DEPRECATED("Use nw_connection_t in Network framework instead", macos(10.3,10.10)) API_UNAVAILABLE(ios, watchos, tvos);
#endif

@end

@interface NSStream (NSStreamBoundPairCreationExtensions)
/// Creates and returns by reference a bound pair of input and output streams.
///
/// The created streams are bound to one another, such that any data written to `outputStream` is received by `inputStream`.
/// - Parameters:
///   - bufferSize: The size of the buffer, in bytes, used to transfer data from `inputStream` to `outputStream`.
///   - inputStream: On return, contains an input stream.
///   - outputStream: On return, contains an output stream.
+ (void)getBoundStreamsWithBufferSize:(NSUInteger)bufferSize inputStream:(NSInputStream * _Nullable * _Nullable)inputStream outputStream:(NSOutputStream * _Nullable * _Nullable)outputStream API_AVAILABLE(macos(10.10), ios(8.0), watchos(2.0), tvos(9.0));
@end

// The NSInputStreamExtensions category contains additional initializers and convenience routines for dealing with NSInputStreams.
@interface NSInputStream (NSInputStreamExtensions)
/// Initializes and returns an `NSInputStream` object that reads data from the file at a given path.
///
/// The stream must be opened before it can be used.
/// - Parameter path: The path to the file.
- (nullable instancetype)initWithFileAtPath:(NSString *)path;

/// Creates and returns an initialized `NSInputStream` object for reading from a given `NSData` object.
///
/// The stream must be opened before it can be used.
///
/// - Parameter data: The data object from which to read. The contents of `data` are copied.
/// - Returns: An initialized `NSInputStream` object for reading from `data`. If `data` is not an `NSData` object, this method returns `nil`.
+ (nullable instancetype)inputStreamWithData:(NSData *)data;
/// Creates and returns an initialized `NSInputStream` object that reads data from the file at a given path.
///
/// The stream must be opened before it can be used.
///
/// - Parameter path: The path to the file.
/// - Returns: An initialized `NSInputStream` object that reads data from the file at `path`.
+ (nullable instancetype)inputStreamWithFileAtPath:(NSString *)path;
/// Creates and returns an initialized `NSInputStream` object that reads data from the file at a given URL.
///
/// The stream must be opened before it can be used.
/// - Parameter url: The URL to the file.
+ (nullable instancetype)inputStreamWithURL:(NSURL *)url API_AVAILABLE(macos(10.6), ios(4.0), watchos(2.0), tvos(9.0));
@end

// The NSOutputStreamExtensions category contains additional initializers and convenience routines for dealing with NSOutputStreams.
@interface NSOutputStream (NSOutputStreamExtensions)
/// Returns an initialized output stream for writing to a specified file.
///
/// The stream must be opened before it can be used.
/// - Parameters:
///   - path: The path to the file the output stream will write to.
///   - shouldAppend: `YES` if newly written data should be appended to any existing file contents, otherwise `NO`.
- (nullable instancetype)initToFileAtPath:(NSString *)path append:(BOOL)shouldAppend;

/// Creates and returns an initialized output stream that will write stream data to memory.
///
/// The stream must be opened before it can be used. You retrieve the contents of the memory stream by sending the message `propertyForKey:` to the receiver with an argument of `NSStreamDataWrittenToMemoryStreamKey`.
+ (instancetype)outputStreamToMemory;
/// Creates and returns an initialized output stream that can write to a provided buffer.
///
/// The stream must be opened before it can be used. When the number of bytes written to `buffer` has reached `capacity`, the stream's `streamStatus` will return `NSStreamStatusAtEnd`.
///
/// - Parameters:
///   - buffer: The buffer the output stream will write to.
///   - capacity: The size of the buffer in bytes.
/// - Returns: An initialized output stream that can write to `buffer`.
+ (instancetype)outputStreamToBuffer:(uint8_t *)buffer capacity:(NSUInteger)capacity;
/// Creates and returns an initialized output stream for writing to a specified file.
///
/// The stream must be opened before it can be used.
///
/// - Parameters:
///   - path: The path to the file the output stream will write to.
///   - shouldAppend: `YES` if newly written data should be appended to any existing file contents, otherwise `NO`.
/// - Returns: An initialized output stream that can write to `path`.
+ (instancetype)outputStreamToFileAtPath:(NSString *)path append:(BOOL)shouldAppend;
/// Creates and returns an initialized output stream for writing to a specified URL.
///
/// The stream must be opened before it can be used.
/// - Parameters:
///   - url: The URL to the file the output stream will write to.
///   - shouldAppend: `YES` if newly written data should be appended to any existing file contents, otherwise `NO`.
+ (nullable instancetype)outputStreamWithURL:(NSURL *)url append:(BOOL)shouldAppend API_AVAILABLE(macos(10.6), ios(4.0), watchos(2.0), tvos(9.0));
@end

/// An interface that delegates of a stream instance use to handle events on the stream.
@protocol NSStreamDelegate <NSObject>
@optional
/// The delegate receives this message when a given event has occurred on a given stream.
- (void)stream:(NSStream *)aStream handleEvent:(NSStreamEvent)eventCode;
@end

// NSString constants for the propertyForKey/setProperty:forKey: API
// String constants for the setting of the socket security level.
/// The security level of the target stream.
FOUNDATION_EXPORT NSStreamPropertyKey const NSStreamSocketSecurityLevelKey		API_AVAILABLE(macos(10.3), ios(2.0), watchos(2.0), tvos(9.0));

/// `NSStream` defines these string constants for specifying the secure-socket layer (SSL) security level.
///
/// ## Discussion
///
/// You access and set these values using the `NSStreamSocketSecurityLevelKey` property key.
typedef NSString * NSStreamSocketSecurityLevel NS_TYPED_ENUM;

/// No security on the socket stream.
FOUNDATION_EXPORT NSStreamSocketSecurityLevel const NSStreamSocketSecurityLevelNone		API_AVAILABLE(macos(10.3), ios(2.0), watchos(2.0), tvos(9.0));
/// Specifies that the SSL version 2 security protocol should be set as the security protocol for a socket stream.
FOUNDATION_EXPORT NSStreamSocketSecurityLevel const NSStreamSocketSecurityLevelSSLv2		API_AVAILABLE(macos(10.3), ios(2.0), watchos(2.0), tvos(9.0));
/// Specifies that the SSL version 3 security protocol should be set as the security protocol for a socket stream.
FOUNDATION_EXPORT NSStreamSocketSecurityLevel const NSStreamSocketSecurityLevelSSLv3		API_AVAILABLE(macos(10.3), ios(2.0), watchos(2.0), tvos(9.0));
/// Specifies that the TLS version 1 security protocol should be set as the security protocol for a socket stream.
FOUNDATION_EXPORT NSStreamSocketSecurityLevel const NSStreamSocketSecurityLevelTLSv1		API_AVAILABLE(macos(10.3), ios(2.0), watchos(2.0), tvos(9.0));
/// Specifies that the highest level security protocol that can be negotiated be set as the security protocol for a socket stream.
FOUNDATION_EXPORT NSStreamSocketSecurityLevel const NSStreamSocketSecurityLevelNegotiatedSSL	API_AVAILABLE(macos(10.3), ios(2.0), watchos(2.0), tvos(9.0));

/// Value is an `NSDictionary` object containing SOCKS proxy configuration information. The dictionary returned from the System Configuration framework for SOCKS proxies usually suffices.
FOUNDATION_EXPORT NSStreamPropertyKey const NSStreamSOCKSProxyConfigurationKey		API_AVAILABLE(macos(10.3), ios(2.0), watchos(2.0), tvos(9.0));

typedef NSString * NSStreamSOCKSProxyConfiguration NS_TYPED_ENUM;

/// The SOCKS proxy host key.
FOUNDATION_EXPORT NSStreamSOCKSProxyConfiguration const NSStreamSOCKSProxyHostKey			API_AVAILABLE(macos(10.3), ios(2.0), watchos(2.0), tvos(9.0));
/// The SOCKS proxy port key. Value is an `NSNumber`.
FOUNDATION_EXPORT NSStreamSOCKSProxyConfiguration const NSStreamSOCKSProxyPortKey			API_AVAILABLE(macos(10.3), ios(2.0), watchos(2.0), tvos(9.0));
/// The SOCKS proxy version key.
FOUNDATION_EXPORT NSStreamSOCKSProxyConfiguration const NSStreamSOCKSProxyVersionKey		API_AVAILABLE(macos(10.3), ios(2.0), watchos(2.0), tvos(9.0));
/// The SOCKS proxy user key.
FOUNDATION_EXPORT NSStreamSOCKSProxyConfiguration const NSStreamSOCKSProxyUserKey			API_AVAILABLE(macos(10.3), ios(2.0), watchos(2.0), tvos(9.0));
/// The SOCKS proxy password key.
FOUNDATION_EXPORT NSStreamSOCKSProxyConfiguration const NSStreamSOCKSProxyPasswordKey		API_AVAILABLE(macos(10.3), ios(2.0), watchos(2.0), tvos(9.0));

typedef NSString * NSStreamSOCKSProxyVersion NS_TYPED_ENUM;

/// SOCKS proxy version 4.
FOUNDATION_EXPORT NSStreamSOCKSProxyVersion const NSStreamSOCKSProxyVersion4			API_AVAILABLE(macos(10.3), ios(2.0), watchos(2.0), tvos(9.0));
/// SOCKS proxy version 5.
FOUNDATION_EXPORT NSStreamSOCKSProxyVersion const NSStreamSOCKSProxyVersion5			API_AVAILABLE(macos(10.3), ios(2.0), watchos(2.0), tvos(9.0));

/// Value is an `NSData` instance containing the data written to a memory stream. Use this property when you have an output-stream object instantiated to collect written data in memory. The value of this property is read-only.
FOUNDATION_EXPORT NSStreamPropertyKey const NSStreamDataWrittenToMemoryStreamKey	API_AVAILABLE(macos(10.3), ios(2.0), watchos(2.0), tvos(9.0));

/// Value is an `NSNumber` object containing the current absolute offset of the stream.
FOUNDATION_EXPORT NSStreamPropertyKey const NSStreamFileCurrentOffsetKey		API_AVAILABLE(macos(10.3), ios(2.0), watchos(2.0), tvos(9.0));

// NSString constants for error domains.
/// The error domain used by `NSError` when reporting SSL errors.
FOUNDATION_EXPORT NSErrorDomain const NSStreamSocketSSLErrorDomain			API_AVAILABLE(macos(10.3), ios(2.0), watchos(2.0), tvos(9.0));
/// The error domain used by `NSError` when reporting SOCKS errors.
FOUNDATION_EXPORT NSErrorDomain const NSStreamSOCKSErrorDomain			API_AVAILABLE(macos(10.3), ios(2.0), watchos(2.0), tvos(9.0));

/// The type of service for the stream. Providing the service type allows the system to properly handle certain attributes of the stream, including routing and suspension behavior.
FOUNDATION_EXPORT NSStreamPropertyKey const NSStreamNetworkServiceType		    API_AVAILABLE(macos(10.7), ios(4.0), watchos(2.0), tvos(9.0));

/// `NSStream` defines these string constants for specifying the service type of a stream.
typedef NSString * NSStreamNetworkServiceTypeValue NS_TYPED_ENUM;

// Supported network service types:
/// The VoIP network service type.
FOUNDATION_EXPORT NSStreamNetworkServiceTypeValue const NSStreamNetworkServiceTypeVoIP	    API_AVAILABLE(macos(10.7), ios(4.0), watchos(2.0), tvos(9.0));
/// The video network service type.
FOUNDATION_EXPORT NSStreamNetworkServiceTypeValue const NSStreamNetworkServiceTypeVideo	    API_AVAILABLE(macos(10.7), ios(5.0), watchos(2.0), tvos(9.0));
/// The background network service type.
FOUNDATION_EXPORT NSStreamNetworkServiceTypeValue const NSStreamNetworkServiceTypeBackground	    API_AVAILABLE(macos(10.7), ios(5.0), watchos(2.0), tvos(9.0));
/// The voice network service type.
FOUNDATION_EXPORT NSStreamNetworkServiceTypeValue const NSStreamNetworkServiceTypeVoice	    API_AVAILABLE(macos(10.7), ios(5.0), watchos(2.0), tvos(9.0));
FOUNDATION_EXPORT NSStreamNetworkServiceTypeValue const NSStreamNetworkServiceTypeCallSignaling    API_AVAILABLE(macosx(10.12), ios(10.0), watchos(3.0), tvos(10.0));

NS_HEADER_AUDIT_END(nullability, sendability)
