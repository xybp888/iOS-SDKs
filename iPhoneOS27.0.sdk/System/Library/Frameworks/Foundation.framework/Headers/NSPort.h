/*	NSPort.h
	Copyright (c) 1994-2019, Apple Inc. All rights reserved.
*/

#import <Foundation/NSObject.h>
#import <Foundation/NSNotification.h>
#import <Foundation/NSRunLoop.h>

/// Type for the platform-specific native socket handle.
typedef int NSSocketNativeHandle;

@class NSRunLoop, NSMutableArray, NSDate;
@class NSConnection, NSPortMessage;
@class NSData;
@protocol NSPortDelegate, NSMachPortDelegate;

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

/// Posted from the ``invalidate`` method, which is invoked when the ``NSPort`` is deallocated or when it notices that its communication channel has been damaged.
FOUNDATION_EXPORT NSNotificationName const NSPortDidBecomeInvalidNotification;

/// An abstract class that represents a communication channel.
///
/// Communication occurs between ``NSPort`` objects, which typically reside in different threads or tasks. The distributed objects system uses ``NSPort`` objects to send ``NSPortMessage`` objects back and forth. Implement interapplication communication using distributed objects whenever possible and use ``NSPort`` objects only when necessary.
///
/// To receive incoming messages, add ``NSPort`` objects to an instance of ``NSRunLoop`` as input sources. ``NSConnection`` objects automatically add their receive port when initialized.
@interface NSPort : NSObject <NSCopying, NSCoding>

// For backwards compatibility on Mach, +allocWithZone: returns
// an instance of the NSMachPort class when sent to the NSPort
// class.  Otherwise, it returns an instance of a concrete
// subclass which can be used for messaging between threads
// or processes on the local machine.

/// Creates and returns a new ``NSPort`` object capable of both sending and receiving messages.
+ (NSPort *)port;

/// Marks the receiver as invalid and posts an ``NSPortDidBecomeInvalidNotification`` to the default notification center.
- (void)invalidate;

/// A Boolean value that indicates whether the receiver is valid.
@property (readonly, getter=isValid) BOOL valid;

/// Sets the receiver's delegate to a given object.
- (void)setDelegate:(nullable id <NSPortDelegate>)anObject;

/// Returns the receiver's delegate.
- (nullable id <NSPortDelegate>)delegate;

/// Schedules the receiver into a given run loop.
///
/// You should not directly invoke this method. Instead, you should add the port to a run loop.
- (void)scheduleInRunLoop:(NSRunLoop *)runLoop forMode:(NSRunLoopMode)mode;

/// Removes the receiver from the run loop mode of the given run loop.
///
/// You should not directly invoke this method. Instead, you should remove the port from the run loop.
- (void)removeFromRunLoop:(NSRunLoop *)runLoop forMode:(NSRunLoopMode)mode;

/// The number of bytes of space reserved by the receiver for sending data.
@property (readonly) NSUInteger reservedSpaceLength;

/*
The components array consists of a series of instances of some subclass of NSData, and instances of some subclass of NSPort; since one subclass of NSPort does not necessarily know how to transport an instance of another subclass of NSPort (or could do it even if it knew about the other subclass), all of the instances of NSPort in the components array and the 'receivePort' argument MUST be of the same subclass of NSPort that receives this message.  If multiple DO transports are being used in the same program, this requires some care.
 */

/// Attempts to send the message before a given date, treating the receiver as the send port and the given port as the receive port.
- (BOOL)sendBeforeDate:(NSDate *)limitDate components:(nullable NSMutableArray *)components from:(nullable NSPort *) receivePort reserved:(NSUInteger)headerSpaceReserved;

/// Attempts to send the message with a given identifier before a given date, treating the receiver as the send port and the given port as the receive port.
- (BOOL)sendBeforeDate:(NSDate *)limitDate msgid:(NSUInteger)msgID components:(nullable NSMutableArray *)components from:(nullable NSPort *)receivePort reserved:(NSUInteger)headerSpaceReserved;
#if TARGET_OS_OSX || TARGET_OS_MACCATALYST
/// Adds a given connection to the receiver in a given run loop mode.
- (void)addConnection:(NSConnection *)conn toRunLoop:(NSRunLoop *)runLoop forMode:(NSRunLoopMode)mode NS_SWIFT_UNAVAILABLE("Use NSXPCConnection instead") API_DEPRECATED("Use NSXPCConnection instead", macosx(10.0, 10.13), ios(2.0,11.0), watchos(2.0,4.0), tvos(9.0,11.0));
/// Removes a given connection from the receiver in a given run loop mode.
- (void)removeConnection:(NSConnection *)conn fromRunLoop:(NSRunLoop *)runLoop forMode:(NSRunLoopMode)mode NS_SWIFT_UNAVAILABLE("Use NSXPCConnection instead") API_DEPRECATED("Use NSXPCConnection instead", macosx(10.0, 10.13), ios(2.0,11.0), watchos(2.0,4.0), tvos(9.0,11.0));
#endif

@end

/// An interface for handling incoming messages.
@protocol NSPortDelegate <NSObject>
@optional

/// Handles a given port message.
- (void)handlePortMessage:(NSPortMessage *)message;

@end

#if TARGET_OS_OSX || TARGET_OS_IPHONE

/// A port that can be used as an endpoint for distributed object connections (or raw messaging).
///
/// ``NSMachPort`` is a subclass of ``NSPort`` that wraps a Mach port, the fundamental communication port in macOS. ``NSMachPort`` allows for local (on the same machine) communication only.
NS_AUTOMATED_REFCOUNT_WEAK_UNAVAILABLE
@interface NSMachPort : NSPort

/// Creates and returns a port object with a given Mach port.
+ (NSPort *)portWithMachPort:(uint32_t)machPort;

/// Initializes a newly allocated ``NSMachPort`` object with a given Mach port.
- (instancetype)initWithMachPort:(uint32_t)machPort NS_DESIGNATED_INITIALIZER;

/// Sets the receiver's delegate to a given object.
- (void)setDelegate:(nullable id <NSMachPortDelegate>)anObject;

/// Returns the receiver's delegate.
- (nullable id <NSMachPortDelegate>)delegate;

/// Used to remove access rights to a mach port when the `NSMachPort` object is invalidated or destroyed.
typedef NS_OPTIONS(NSUInteger, NSMachPortOptions) {
    /// Do not remove any send or receive rights.
    NSMachPortDeallocateNone = 0,
    /// Deallocate the port's send right when the port is invalidated or destroyed.
    NSMachPortDeallocateSendRight = (1UL << 0),
    /// Deallocate the port's receive right when the port is invalidated or destroyed.
    NSMachPortDeallocateReceiveRight = (1UL << 1)
} API_AVAILABLE(macos(10.5), ios(2.0), watchos(2.0), tvos(9.0));

/// Creates and returns a port object with a given Mach port and the specified options.
+ (NSPort *)portWithMachPort:(uint32_t)machPort options:(NSMachPortOptions)f API_AVAILABLE(macos(10.5), ios(2.0), watchos(2.0), tvos(9.0));

/// Initializes a newly allocated ``NSMachPort`` object with a given Mach port and the specified options.
- (instancetype)initWithMachPort:(uint32_t)machPort options:(NSMachPortOptions)f API_AVAILABLE(macos(10.5), ios(2.0), watchos(2.0), tvos(9.0)) NS_DESIGNATED_INITIALIZER;

/// The Mach port used by the receiver.
@property (readonly) uint32_t machPort;

/// Schedules the port on a given run loop.
- (void)scheduleInRunLoop:(NSRunLoop *)runLoop forMode:(NSRunLoopMode)mode;

/// Removes the port from a given run loop.
- (void)removeFromRunLoop:(NSRunLoop *)runLoop forMode:(NSRunLoopMode)mode;

@end

/// An interface for handling incoming Mach messages.
@protocol NSMachPortDelegate <NSPortDelegate>
@optional

/// Handles an incoming Mach message.
///
/// The argument is a raw Mach message beginning with a `msg_header_t` structure.
- (void)handleMachMessage:(void *)msg;

@end

#endif

/// A port that can be used as an endpoint for distributed object connections (or raw messaging).
///
/// ``MessagePort`` is a subclass of ``Port`` that allows for local (on the same machine) communication only. A companion class, ``SocketPort``, allows for both local and remote communication, but may be more expensive than ``MessagePort`` for the local case.
///
/// ``MessagePort`` defines no additional methods over those already defined by ``Port``.
///
/// > Note:
/// > ``MessagePort`` conforms to the ``NSCoding`` protocol, but only supports coding by an ``NSPortCoder`` object. ``Port`` and its subclasses do not support archiving.
///
/// > Important:
/// > Avoid ``MessagePort``. There's little reason to use ``MessagePort`` rather than ``NSMachPort`` or ``SocketPort``. There's no particular performance or functionality advantage. It is recommended avoiding its use.
/// >
/// > ``MessagePort`` may be deprecated in the macOS 10.6 or later.
///
/// ## See Also
///
/// - [Distributed Objects Programming Topics](https://developer.apple.com/library/archive/documentation/Cocoa/Conceptual/DistrObjects/DistrObjects.html#//apple_ref/doc/uid/10000102i)
/// A port that can be used for local message sending on all platforms.
NS_AUTOMATED_REFCOUNT_WEAK_UNAVAILABLE
@interface NSMessagePort : NSPort {
    @private
    void *_port;
    id _delegate;
}

@end

#if TARGET_OS_OSX || TARGET_IPHONE_SIMULATOR

/// A port that represents a BSD socket.
///
/// A ``NSSocketPort`` object can be used as an endpoint for distributed object connections. Companion classes, ``NSMachPort`` and ``NSMessagePort``, allow for local (on the same machine) communication only. The ``NSSocketPort`` class allows for both local and remote communication, but may be more expensive than the others for the local case.
@interface NSSocketPort : NSPort

/// Initializes the receiver as a local TCP/IP socket of type `SOCK_STREAM`, on a system-selected port.
- (instancetype)init;

/// Initializes the receiver as a local TCP/IP socket of type `SOCK_STREAM`, listening on a given port number.
- (nullable instancetype)initWithTCPPort:(unsigned short)port;

/// Initializes the receiver as a local socket with the provided arguments.
- (nullable instancetype)initWithProtocolFamily:(int)family socketType:(int)type protocol:(int)protocol address:(NSData *)address NS_DESIGNATED_INITIALIZER;

/// Initializes the receiver with a previously created local socket.
- (nullable instancetype)initWithProtocolFamily:(int)family socketType:(int)type protocol:(int)protocol socket:(NSSocketNativeHandle)sock NS_DESIGNATED_INITIALIZER;

/// Initializes the receiver as a TCP/IP socket of type `SOCK_STREAM` that can connect to a remote host on a given port.
- (nullable instancetype)initRemoteWithTCPPort:(unsigned short)port host:(nullable NSString *)hostName;

/// Initializes the receiver as a remote socket with the provided arguments.
- (instancetype)initRemoteWithProtocolFamily:(int)family socketType:(int)type protocol:(int)protocol address:(NSData *)address NS_DESIGNATED_INITIALIZER;

/// The protocol family of the receiver's socket.
@property (readonly) int protocolFamily;

/// The type of the receiver's socket.
@property (readonly) int socketType;

/// The protocol that the receiver's socket uses.
@property (readonly) int protocol;

/// The receiver's socket address structure stored inside an ``NSData`` object.
@property (readonly, copy) NSData *address;

/// The receiver's native socket identifier on the platform.
@property (readonly) NSSocketNativeHandle socket;

@end

#endif

NS_HEADER_AUDIT_END(nullability, sendability)
