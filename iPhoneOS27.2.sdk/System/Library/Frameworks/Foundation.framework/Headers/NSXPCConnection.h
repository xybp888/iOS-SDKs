/*	NSXPCConnection.h
        Copyright (c) 2011-2019, Apple Inc. All rights reserved.
 */

#import <dispatch/dispatch.h>
#import <bsm/audit.h>

#import <Foundation/NSObject.h> 
#import <Foundation/NSCoder.h>

#import <CoreFoundation/CFDictionary.h>

#if __has_include(<xpc/xpc.h>)
#include <xpc/xpc.h>
#endif

@class NSMutableDictionary, NSString, NSOperationQueue, NSSet<ObjectType>, NSLock, NSError;
@class NSXPCConnection, NSXPCListener, NSXPCInterface, NSXPCListenerEndpoint;
@protocol NSXPCListenerDelegate;

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

/// Methods for creating new proxy objects.
///
/// ``NSXPCConnection`` implements this protocol. All objects returned from the methods in this protocol also implement the protocol. This allows creation of new proxies from other proxies.
@protocol NSXPCProxyCreating

/// Returns a proxy object with no error handling block.
///
/// Messages sent to the proxy object will be sent over the wire to the other side of the connection. All messages must be 'oneway void' return type. Control may be returned to the caller before the message is sent. This proxy object will conform with the `NSXPCProxyCreating` protocol.
- (id)remoteObjectProxy;

/// Returns a proxy object which will invoke the error handling block if an error occurs on the connection.
///
/// If the message sent to the proxy has a reply handler, then either the error handler or the reply handler will be called exactly once. This proxy object will also conform with the `NSXPCProxyCreating` protocol.
- (id)remoteObjectProxyWithErrorHandler:(void (NS_SWIFT_SENDABLE ^)(NSError *error))handler;

@optional

/// Returns a proxy that makes a synchronous IPC call instead of the default async behavior.
///
/// The error handler block and reply block will be invoked on the calling thread before the message to the proxy returns, instead of on the queue for the connection.
- (id)synchronousRemoteObjectProxyWithErrorHandler:(void (^)(NSError *error))handler API_AVAILABLE(macos(10.11), ios(9.0), watchos(2.0), tvos(9.0));

@end

// ----------------------------------

/// Options that may be passed to a connection.
typedef NS_OPTIONS(NSUInteger, NSXPCConnectionOptions) {
    /// Use this option if connecting to a service in the privileged Mach bootstrap (for example, a `launchd.plist` in `/Library/LaunchDaemons`).
    NSXPCConnectionPrivileged = (1 << 12UL)
} API_AVAILABLE(macos(10.8), ios(6.0), watchos(2.0), tvos(9.0));

/// A bidirectional communication channel between two processes.
///
/// This class is the primary means of creating and configuring the communication mechanism between two processes. Each process has one instance of this class to represent the endpoint in the communication channel.
API_AVAILABLE(macos(10.8), ios(6.0), watchos(2.0), tvos(9.0))
@interface NSXPCConnection : NSObject <NSXPCProxyCreating>

/// Initializes an `NSXPCConnection` that will connect to the specified service name.
///
/// Receiving a non-nil result from this init method does not mean the service name is valid or the service has been launched. The init method simply constructs the local object.
- (instancetype)initWithServiceName:(NSString *)serviceName API_UNAVAILABLE(ios, watchos, tvos);
/// The name of the XPC service that this connection was configured to connect to.
@property (nullable, readonly, copy) NSString *serviceName;

/// Initializes an `NSXPCConnection` for a named Mach service advertised in a `launchd.plist`.
///
/// For example, an agent with a `launchd.plist` in `~/Library/LaunchAgents`. If the connection is being made to something in a privileged Mach bootstrap (for example, a daemon with a `launchd.plist` in `/Library/LaunchDaemons`), then use the `NSXPCConnectionPrivileged` option. Receiving a non-nil result from this init method does not mean the service name is valid or the service has been launched.
- (instancetype)initWithMachServiceName:(NSString *)name options:(NSXPCConnectionOptions)options API_UNAVAILABLE(ios, watchos, tvos);

/// Initializes an `NSXPCConnection` that will connect to an `NSXPCListener` identified by its endpoint.
- (instancetype)initWithListenerEndpoint:(NSXPCListenerEndpoint *)endpoint;
/// The endpoint that was provided when the connection was initialized.
@property (readonly, retain) NSXPCListenerEndpoint *endpoint;

/// The interface that describes messages that are allowed to be received by the exported object on this connection.
///
/// This value is required if an exported object is set.
@property (nullable, retain) NSXPCInterface *exportedInterface;

/// An object that is vended to the other side of this connection.
///
/// Messages sent to the `remoteObjectProxy` from the other side of the connection will be dispatched to this object. Messages delivered to exported objects are serialized and sent on a non-main queue. The receiver is responsible for handling the messages on a different queue or thread if it is required.
@property (nullable, retain) id exportedObject;

/// The interface that describes messages that are allowed to be received by the remote object on the other side of this connection.
///
/// This value is required if messages are sent over this connection.
@property (nullable, retain) NSXPCInterface *remoteObjectInterface;

/// Returns a proxy for the remote object (that is, the object exported from the other side of this connection).
@property (readonly, retain) id remoteObjectProxy;

/// Returns a proxy for the remote object, with an error handler.
- (id)remoteObjectProxyWithErrorHandler:(void (^)(NSError *error))handler;

/// Returns a proxy that makes a synchronous IPC call instead of the default async behavior.
///
/// The error handler block and reply block will be invoked on the calling thread before the message to the proxy returns, instead of on the queue for the connection.
- (id)synchronousRemoteObjectProxyWithErrorHandler:(void (^)(NSError *error))handler API_AVAILABLE(macos(10.11), ios(9.0), watchos(2.0), tvos(9.0));

/// A block that is called if the remote process exits or crashes.
///
/// It may be possible to re-establish the connection by simply sending another message. The handler will be invoked on the same queue as replies and other handlers, but there is no guarantee of ordering between those callbacks and this one. The `interruptionHandler` property is cleared after the connection becomes invalid to mitigate the impact of a retain cycle created by referencing the `NSXPCConnection` instance inside this block.
@property (nullable, copy) void (^interruptionHandler)(void);

/// A block that is called if the connection can not be formed or has terminated and may not be re-established.
///
/// The invalidation handler will also be called if a connection created with an `NSXPCListenerEndpoint` is invalidated from the remote side, or if the `NSXPCListener` used to create that endpoint is invalidated. You may not send messages over the connection from within an invalidation handler block. The `invalidationHandler` property is cleared after the connection becomes invalid to mitigate the impact of a retain cycle created by referencing the `NSXPCConnection` instance inside this block.
@property (nullable, copy) void (^invalidationHandler)(void);

/// Resumes the connection.
///
/// All connections start suspended. You must resume them before they will start processing received messages or sending messages through the `remoteObjectProxy`. Calling resume does not immediately launch the XPC service. The service will be started on demand when the first message is sent. However, if the name specified when creating the connection is determined to be invalid, your invalidation handler will be called immediately (and asynchronously) after calling resume. For new code, calling `activate` is preferred for the initial activation of the connection.
- (void)resume;

/// Suspends the connection.
///
/// Suspends must be balanced with resumes before the connection may be invalidated.
- (void)suspend;

/// Activates the connection.
///
/// Connections start in an inactive state. You must call `activate` on a connection before it will send or receive any messages. Calling `activate` on an active connection has no effect. For new code, using `activate` is preferred over `resume`.
- (void)activate API_AVAILABLE(macos(11.0), ios(14.0), watchos(7.0), tvos(14.0));

/// Invalidates the connection.
///
/// All outstanding error handling blocks and invalidation blocks will be called on the message handling queue. The connection must be invalidated before it is deallocated. After a connection is invalidated, no more messages may be sent or received.
- (void)invalidate;

/// The audit session identifier of the connecting process.
@property (readonly) au_asid_t auditSessionIdentifier;
/// The process identifier (PID) of the connecting process.
@property (readonly) pid_t processIdentifier;
/// The effective user identifier (EUID) of the connecting process.
@property (readonly) uid_t effectiveUserIdentifier;
/// The effective group identifier (EGID) of the connecting process.
@property (readonly) gid_t effectiveGroupIdentifier;

/// Returns the current connection, in the context of a call to a method on your exported object.
///
/// Useful for determining 'who called this'.
+ (nullable NSXPCConnection *)currentConnection API_AVAILABLE(macos(10.8), ios(6.0), watchos(2.0), tvos(9.0)) NS_SWIFT_UNAVAILABLE_FROM_ASYNC("currentConnection cannot be used from async contexts.");

/// Adds a barrier block to be executed on the connection after any outstanding sends have completed.
///
/// This does not guarantee that messages will be received by the remote process by the time the block is invoked. If you need to ensure receipt of a message by the remote process, waiting for a reply to come back is the best option.
- (void)scheduleSendBarrierBlock:(void (^)(void))block API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0));

/// Sets the code signing requirement for this connection. If the requirement is malformed, an exception is thrown. If new messages do not match the requirement, the connection is invalidated. It is recommended to set this before calling `resume`, as it is an XPC error to call it more than once.
/// See https://developer.apple.com/library/archive/documentation/Security/Conceptual/CodeSigningGuide/RequirementLang/RequirementLang.html for more information on the format.
- (void)setCodeSigningRequirement:(NSString *)requirement API_AVAILABLE(macos(13.0)) API_UNAVAILABLE(ios, tvos, watchos);

@end


/// A listener that waits for new incoming connections, configures them, and accepts or rejects them.
///
/// Each XPC service, launchd agent, or launchd daemon typically has at least one ``NSXPCListener`` object that listens for connections to a specified service name. Each listener must have a delegate that conforms to the ``NSXPCListenerDelegate`` protocol. When the listener receives a new connection request, it creates a new ``NSXPCConnection`` object, then asks the delegate to inspect, configure, and resume the connection object by calling the delegate's ``NSXPCListenerDelegate/listener(_:shouldAcceptNewConnection:)`` method.
API_AVAILABLE(macos(10.8), ios(6.0), watchos(2.0), tvos(9.0))
@interface NSXPCListener : NSObject

/// Returns the singleton listener for an XPC service.
///
/// If your listener is an XPC service (that is, in the XPCServices folder of an application or framework), then use this method to get the shared, singleton `NSXPCListener` object that will await new connections. When the resume method is called on this listener, it will not return. Instead it hands over control to the object and allows it to service the listener as appropriate. This makes it ideal for use in your `main()` function.
+ (NSXPCListener *)serviceListener;

/// Creates an anonymous listener connection.
///
/// Other processes may connect to this listener by passing this listener object's endpoint to `NSXPCConnection`'s `initWithListenerEndpoint:` method.
+ (NSXPCListener *)anonymousListener;

/// Initializes a listener for a named Mach service advertised in a `launchd.plist`.
///
/// For example, an agent with a `launchd.plist` in `~/Library/LaunchAgents`, or a daemon with a `launchd.plist` in `/Library/LaunchDaemons`.
- (instancetype)initWithMachServiceName:(NSString *)name NS_DESIGNATED_INITIALIZER API_UNAVAILABLE(ios, watchos, tvos);

/// The delegate for the connection listener.
///
/// If no delegate is set, all new connections will be rejected. See the protocol for more information on how to implement it.
@property (nullable, weak) id <NSXPCListenerDelegate> delegate;

/// An endpoint object which may be sent over an existing connection.
///
/// This allows the receiver of the endpoint to create a new connection to this `NSXPCListener`. The `NSXPCListenerEndpoint` uniquely names this listener object across connections.
@property (readonly, retain) NSXPCListenerEndpoint *endpoint;

/// Resumes the listener.
///
/// All listeners start suspended and must be resumed before they will process incoming requests. If called on the `serviceListener`, this method will never return. Call it as the last step inside your `main` function in your XPC service. If called on any other `NSXPCListener`, the listener is resumed and the method returns immediately. For new code, calling `activate` is preferred for the initial activation of the listener.
- (void)resume;

/// Suspends the listener.
///
/// Suspends must be balanced with resumes before the listener may be invalidated.
- (void)suspend;

/// Activates the listener.
///
/// Listeners start in an inactive state. You must call `activate` on a listener before it will send or receive any messages. Calling `activate` on an active listener has no effect. For new code, using `activate` is preferred over `resume`.
- (void)activate API_AVAILABLE(macos(11.0), ios(14.0), watchos(7.0), tvos(14.0));

/// Invalidates the listener.
///
/// No more connections will be created. Once a listener is invalidated it may not be resumed or suspended.
- (void)invalidate;

/// Sets the code signing requirement for new connections. If the requirement is malformed, an exception is thrown. If new peer connections do not match the requirement, the incoming connection is automatically rejected before consulting the delegate.
/// This method will only work on `anonymousListener` or `initWithMachServiceName` listener instances. Use on other types of listeners will result in an assertion failure.
/// See https://developer.apple.com/library/archive/documentation/Security/Conceptual/CodeSigningGuide/RequirementLang/RequirementLang.html for more information on the format.
- (void)setConnectionCodeSigningRequirement:(NSString *)requirement API_AVAILABLE(macos(13.0)) API_UNAVAILABLE(ios, tvos, watchos);

@end

/// The protocol that delegates to the XPC listener use to accept or reject new connections.
@protocol NSXPCListenerDelegate <NSObject>
@optional
/// Asks the delegate whether to accept or reject a new connection to the listener.
///
/// This is a good time to set up properties on the new connection, like its exported object and interfaces. If a value of `NO` is returned, the connection object will be invalidated after this method returns. Be sure to resume the new connection and return `YES` when you are finished configuring it and are ready to receive messages. You may delay resuming the connection if you wish, but still return `YES` from this method if you want the connection to be accepted.
- (BOOL)listener:(NSXPCListener *)listener shouldAcceptNewConnection:(NSXPCConnection *)newConnection;

@end

// ----------------------------------

/// An object that holds all information about the interface of an exported or imported object.
///
/// This includes what messages are allowed, what kinds of objects are allowed as arguments, what the signature of any reply blocks are, and any information about additional proxy objects.
API_AVAILABLE(macos(10.8), ios(6.0), watchos(2.0), tvos(9.0))
/// An interface that may be sent to an exported object or remote object proxy.
///
/// This object holds all information about the interface of an exported object or remote object proxy. It describes what messages are allowed, what kinds of objects are allowed as arguments, what the signature of any reply blocks are, and information about additional proxy objects.
@interface NSXPCInterface : NSObject

/// Returns an `NSXPCInterface` instance for a given protocol.
///
/// Most interfaces do not need any further configuration. Interfaces with collection classes or additional proxy objects should be configured using the methods below.
+ (NSXPCInterface *)interfaceWithProtocol:(Protocol *)protocol;

/// The Objective-C protocol this `NSXPCInterface` is based upon.
@property (assign) Protocol *protocol;

/// Configures the expected classes for a collection parameter in a method of the protocol.
///
/// If an argument to a method in your protocol is a collection class (for example, `NSArray` or `NSDictionary`), then the interface must be configured with the set of expected classes contained inside of the collection. The `classes` argument should be an `NSSet` containing `Class` objects. The `sel` argument specifies which method in the protocol is being configured. The `arg` parameter specifies which argument of the method the `NSSet` applies to. If the `NSSet` is for an argument of the reply block in the method, pass `YES` for `ofReply`. The first argument is index 0 for both the method and the reply block. If the expected classes are all property list types, calling this method is optional.
- (void)setClasses:(NSSet<Class> *)classes forSelector:(SEL)sel argumentIndex:(NSUInteger)arg ofReply:(BOOL)ofReply;
/// Returns the expected classes for a collection parameter in a method of the protocol.
- (NSSet<Class> *)classesForSelector:(SEL)sel argumentIndex:(NSUInteger)arg ofReply:(BOOL)ofReply;

/// Configures an argument in a method of the protocol to be sent as a proxy object instead of by copy.
- (void)setInterface:(NSXPCInterface *)ifc forSelector:(SEL)sel argumentIndex:(NSUInteger)arg ofReply:(BOOL)ofReply;
/// Returns the interface previously configured for a proxy argument.
- (nullable NSXPCInterface *)interfaceForSelector:(SEL)sel argumentIndex:(NSUInteger)arg ofReply:(BOOL)ofReply;

#if __has_include(<xpc/xpc.h>)
- (void)setXPCType:(xpc_type_t)type forSelector:(SEL)sel argumentIndex:(NSUInteger)arg ofReply:(BOOL)ofReply API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0));
- (nullable xpc_type_t)XPCTypeForSelector:(SEL)sel argumentIndex:(NSUInteger)arg ofReply:(BOOL)ofReply API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0));
#endif

@end

// ----------------------------------

/// An object that names a specific XPC listener.
///
/// An instance of ``NSXPCListenerEndpoint`` may be retrieved from an ``NSXPCListener`` instance and sent over existing ``NSXPCConnection``s. A process may then use the endpoint to create a new ``NSXPCConnection`` to the original ``NSXPCListener``.
///
/// This pattern is useful if you have a service which multiplexes work to other services. The service can act as an intermediate helper. The requesting application does not need to know specifically which service it is connecting to, just that it implements a known ``NSXPCInterface``.
NS_SWIFT_SENDABLE
API_AVAILABLE(macos(10.8), ios(6.0), watchos(2.0), tvos(9.0))
@interface NSXPCListenerEndpoint : NSObject <NSSecureCoding>
@end

// ----------------------------------

/// A coder that encodes and decodes objects that your app sends over an XPC connection.
///
/// If you want to perform custom encoding or decoding of <doc://com.apple.documentation/documentation/swift/codable> objects that your app sends over an ``NSXPCConnection``, use <doc://com.apple.documentation/documentation/objectivec/nsobjectprotocol/iskind(of:)> to determine if the coder provided to your object is a kind of ``NSXPCCoder``.
API_AVAILABLE(macos(10.8), ios(6.0), watchos(2.0), tvos(9.0))
@interface NSXPCCoder : NSCoder

#if __has_include(<xpc/xpc.h>)
/// Encodes an XPC object and associates it with the given key.
- (void)encodeXPCObject:(xpc_object_t)xpcObject forKey:(NSString *)key;

/// Decodes an XPC object of the given type for the given key.
///
/// This validates the type of the decoded object matches the type passed in. If they do not match, an exception is thrown (just like the rest of Secure Coding behaves). Note that this can return `NULL`, but calling an XPC function with `NULL` will crash.
- (nullable xpc_object_t)decodeXPCObjectOfType:(xpc_type_t)type forKey:(NSString *)key API_AVAILABLE(macos(10.9), ios(7.0), watchos(2.0), tvos(9.0));
#endif

/// User-defined information associated with this coder.
@property (nullable, retain) id <NSObject> userInfo;

/// The current `NSXPCConnection` that is encoding or decoding.
@property (nullable, readonly, strong) NSXPCConnection *connection API_AVAILABLE(macosx(10.12), ios(10.0), watchos(3.0), tvos(10.0));

@end

NS_HEADER_AUDIT_END(nullability, sendability)
