/*	NSNetServices.h
        Copyright (c) 2002-2019, Apple Inc. All rights reserved.
*/

#import <Foundation/NSObject.h>
#import <Foundation/NSDate.h>
#import <Foundation/NSError.h>
#import <Foundation/NSRunLoop.h>

@class NSArray<ObjectType>, NSData, NSDictionary<KeyType, ObjectType>, NSInputStream, NSNumber, NSOutputStream, NSRunLoop, NSString;
@protocol NSNetServiceDelegate, NSNetServiceBrowserDelegate;

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

#pragma mark Error constants

/// This key identifies the error that occurred during the most recent operation.
FOUNDATION_EXPORT NSString * const NSNetServicesErrorCode API_AVAILABLE(macos(10.2), ios(2.0), tvos(9.0)) API_UNAVAILABLE(watchos);
/// This key identifies the originator of the error, which is either the `NSNetService` object or the mach network layer. For most errors, you should not need the value provided by this key.
FOUNDATION_EXPORT NSErrorDomain const NSNetServicesErrorDomain API_AVAILABLE(macos(10.2), ios(2.0), tvos(9.0)) API_UNAVAILABLE(watchos);

/// These constants identify errors that can occur when accessing net services.
typedef NS_ENUM(NSInteger, NSNetServicesError) {
    /// An unknown error occurred.
    NSNetServicesUnknownError = -72000L,
    /// The service could not be published because the name is already in use. The name could be in use locally or on another system.
    NSNetServicesCollisionError = -72001L,
    /// The service could not be found on the network.
    NSNetServicesNotFoundError	= -72002L,
    /// The net service cannot process the request at this time. No additional information about the network state is known.
    NSNetServicesActivityInProgress = -72003L,
    /// An invalid argument was used when creating the `NSNetService` object.
    NSNetServicesBadArgumentError = -72004L,
    /// The client canceled the action.
    NSNetServicesCancelledError = -72005L,
    /// The net service was improperly configured.
    NSNetServicesInvalidError = -72006L,
    /// The net service has timed out.
    NSNetServicesTimeoutError = -72007L,
    /// Missing required configuration for local network access.
    ///
    /// `NSBonjourServices` and `NSLocalNetworkUsageDescription` are required in Info.plist.
    NSNetServicesMissingRequiredConfigurationError API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0)) API_UNAVAILABLE(watchos) = -72008L,
} API_AVAILABLE(macos(10.2), ios(2.0), tvos(9.0)) API_UNAVAILABLE(watchos);


/// These constants specify options for a network service.
typedef NS_OPTIONS(NSUInteger, NSNetServiceOptions) {
    /// Specifies that the network service should not rename itself in the event of a name collision.
    NSNetServiceNoAutoRename = 1UL << 0,

    /// Specifies that a TCP listener should be started for both IPv4 and IPv6 on the port specified by this service.
    ///
    /// If the listening port can't be opened, the service calls its delegate's
    /// `-netService:didNotPublish:` method to report the error.
    ///
    /// The listener supports only TCP connections. If the service's type does not end with `_tcp`,
    /// publication fails with `NSNetServicesBadArgumentError`.
    ///
    /// Whenever a client connects to the listening socket, the service calls its delegate's
    /// `-netService:didAcceptConnectionWithInputStream:outputStream:` method with a pair of `NSStream` objects.
    NSNetServiceListenForConnections API_AVAILABLE(macos(10.9), ios(7.0), watchos(2.0), tvos(9.0)) = 1UL << 1
} API_AVAILABLE(macos(10.2), ios(2.0), tvos(9.0)) API_UNAVAILABLE(watchos);



#pragma mark -

/// A network service that broadcasts its availability using multicast DNS.
///
/// The ``NetService`` class represents a network service, either one your application publishes or is a client of. This class and the ``NetServiceBrowser`` class use multicast DNS to convey information about network services to and from your application. The API of ``NetService`` provides a convenient way to publish the services offered by your application and to resolve the socket address for a service.
///
/// The types of services you access using ``NetService`` are the same types that you access directly using BSD sockets. HTTP and FTP are two services commonly provided by systems. (For a list of common services and the ports used by those services, see the file `/etc/services`.) Applications can also define their own custom services to provide specific data to clients.
///
/// You can use the ``NetService`` class as either a publisher of a service or a client of a service. If your application publishes a service, your code must acquire a port and prepare a socket to communicate with clients. Once your socket is ready, you use the ``NetService`` class to notify clients that your service is ready. If your application is the client of a network service, you can either create an ``NetService`` object directly (if you know the exact host and port information) or use an ``NetServiceBrowser`` object to browse for services.
///
/// To publish a service, initialize your ``NetService`` object with the service name, domain, type, and port information. All of this information must be valid for the socket created by your application. Once initialized, call the ``publish()`` method to broadcast your service information to the network.
///
/// When connecting to a service, use the ``NetServiceBrowser`` class to locate the service on the network and obtain the corresponding ``NetService`` object. Once you have the object, call the ``resolve(withTimeout:)`` method to verify that the service is available and ready for your application. If it is, the ``addresses`` property provides the socket information you can use to connect to the service.
///
/// The methods of ``NetService`` operate asynchronously so your application is not impacted by the speed of the network. All information about a service is returned to your application through the ``NetService`` object's delegate. You must provide a delegate object to respond to messages and to handle errors appropriately.
API_DEPRECATED("Use nw_connection_t or nw_listener_t in Network framework instead", macos(10.2, API_TO_BE_DEPRECATED), ios(2.0, API_TO_BE_DEPRECATED), tvos(9.0, API_TO_BE_DEPRECATED)) API_UNAVAILABLE(watchos)
@interface NSNetService : NSObject {
@private
    id _netService;
    id _delegate;
    id _reserved;
}

/// Initializes the receiver for publishing a network service of type `type` at the socket location specified by `domain`, `name`, and `port`.
///
/// - Parameters:
///   - domain: The domain for the service. To use the default registration domains, pass in an empty string (`@""`). To limit registration to the local domain, use `@"local."`.
///   - type: The network service type. Must contain both the service type and transport layer information (e.g. `_http._tcp.`).
///   - name: The name by which the service is identified to the network. If you pass the empty string (`@""`), the system automatically advertises your service using the computer name as the service name.
///   - port: The port on which the service is published.
///
/// You use this method to create a service that you wish to publish on the network. This method is the designated initializer.
- (instancetype)initWithDomain:(NSString *)domain type:(NSString *)type name:(NSString *)name port:(int)port NS_DESIGNATED_INITIALIZER;

/// Returns the receiver, initialized as a network service of a given type and sets the initial host information.
///
/// - Parameters:
///   - domain: The domain for the service. To resolve in the default domains, pass in an empty string (`@""`). To limit resolution to the local domain, use `@"local."`.
///   - type: The network service type. Must contain both the service type and transport layer information (e.g. `_http._tcp.`).
///   - name: The name of the service to resolve.
///
/// This method is the appropriate initializer to use to resolve a service. To publish a service, use `-initWithDomain:type:name:port:` instead.
/// You cannot use this initializer to publish a service. Calling `-publish` on an `NSNetService` object initialized with this method generates a call to your delegate's `-netService:didNotPublish:` method with an `NSNetServicesBadArgumentError` error.
- (instancetype)initWithDomain:(NSString *)domain type:(NSString *)type name:(NSString *)name;

/// Adds the service to the specified run loop.
///
/// - Parameters:
///   - aRunLoop: The run loop to which to add the receiver.
///   - mode: The run loop mode to which to add the receiver.
///
/// You can use this method in conjunction with `-removeFromRunLoop:forMode:` to transfer a service to a different run loop. You should not attempt to run a service on multiple run loops.
- (void)scheduleInRunLoop:(NSRunLoop *)aRunLoop forMode:(NSRunLoopMode)mode;

/// Removes the service from the given run loop for a given mode.
///
/// - Parameters:
///   - aRunLoop: The run loop from which to remove the receiver.
///   - mode: The run loop mode from which to remove the receiver.
///
/// You can use this method in conjunction with `-scheduleInRunLoop:forMode:` to transfer the service to a different run loop. Although it is possible to remove an `NSNetService` object completely from any run loop and then attempt actions on it, it is an error to do so.
- (void)removeFromRunLoop:(NSRunLoop *)aRunLoop forMode:(NSRunLoopMode)mode;

/// The delegate for the receiver.
///
/// The delegate must conform to the `NSNetServiceDelegate` protocol, and is not retained.
@property (nullable, assign) id <NSNetServiceDelegate> delegate;

/// Specifies whether to also publish, resolve, or monitor this service over peer-to-peer Bluetooth and Wi-Fi, if available.
///
/// This property must be set before calling `-publish`, `-publishWithOptions:`, `-resolveWithTimeout:`, or `-startMonitoring` in order to take effect. Initially set to `NO`.
@property BOOL includesPeerToPeer API_AVAILABLE(macos(10.10), ios(7.0), watchos(2.0), tvos(9.0));

/// A string containing the name of this service.
///
/// This value is set when the object is first initialized, whether by your code or by a browser object.
@property (readonly, copy) NSString *name;

/// The type of the published service.
///
/// This value is set when the object is first initialized, whether by your code or by a browser object.
@property (readonly, copy) NSString *type;

/// A string containing the domain for this service.
///
/// This can be an explicit domain name or it can contain the generic local domain name, `@"local."` (note the trailing period, which indicates an absolute name).
@property (readonly, copy) NSString *domain;

/// A string containing the DNS hostname for this service.
///
/// This value is `nil` until the service has been resolved (when `addresses` is non-`nil`).
@property (nullable, readonly, copy) NSString *hostName;

/// A read-only array containing `NSData` objects, each of which contains a socket address for the service.
///
/// Each `NSData` object in the returned array contains an appropriate `sockaddr` structure that you can use to connect to the socket. The exact type of this structure depends on the service to which you are connecting. If no addresses were resolved for the service, the returned array contains zero elements.
///
/// It is possible for a single service to resolve to more than one address or not resolve to any addresses. A service might resolve to multiple addresses if the computer publishing the service is currently multihoming.
@property (nullable, readonly, copy) NSArray<NSData *> *addresses;

/// The port on which the service is listening for connections.
///
/// If the object was initialized by calling `-initWithDomain:type:name:port:`, then the value was set when the object was first initialized.
/// If the object was initialized by calling `-initWithDomain:type:name:`, the value of this property is not valid (`-1`) until after the service has successfully been resolved (when `addresses` is non-`nil`).
@property (readonly) NSInteger port API_AVAILABLE(macos(10.5), ios(2.0), watchos(2.0), tvos(9.0));

/// Attempts to advertise the receiver's on the network.
///
/// This method returns immediately, with success or failure indicated by the callbacks to the delegate. This is equivalent to calling `-publishWithOptions:` with the default options (`0`).
- (void)publish;

/// Attempts to advertise the receiver on the network, with the given options.
///
/// - Parameters:
///   - options: Options for the receiver. The supported options are described in `NSNetServiceOptions`.
///
/// This method returns immediately, with success or failure indicated by the callbacks to the delegate.
- (void)publishWithOptions:(NSNetServiceOptions)options API_AVAILABLE(macos(10.5), ios(2.0), watchos(2.0), tvos(9.0));


/// Starts a resolve process for the service.
///
/// Attempts to determine at least one address for the service. This method returns immediately, with success or failure indicated by the callbacks to the delegate.
///
/// In OS X v10.4, this method calls `-resolveWithTimeout:` with a timeout value of `5`.
- (void)resolve API_DEPRECATED("Not supported", macos(10.2,10.4), ios(2.0,2.0), watchos(2.0,2.0), tvos(9.0,9.0));

/// Halts a currently running attempt to publish or resolve a service.
///
/// The delegate will receive `-netServiceDidStop:` after the service stops.
/// It is safe to remove all strong references to the service immediately after calling this method.
- (void)stop;

/// Returns a dictionary representing a TXT record given as an `NSData` object.
///
/// - Parameters:
///   - txtData: A data object encoding a TXT record.
/// - Returns: A dictionary representing `txtData`. The dictionary's keys are UTF8-encoded `NSString` objects. The values associated with all the dictionary's keys are `NSData` objects that encapsulate strings or data. Fails an assertion if `txtData` cannot be represented as an `NSDictionary` object.
+ (NSDictionary<NSString *, NSData *> *)dictionaryFromTXTRecordData:(NSData *)txtData;

/// Returns an `NSData` object representing a TXT record formed from a given dictionary.
///
/// - Parameters:
///   - txtDictionary: A dictionary containing a TXT record.
/// - Returns: An `NSData` object representing TXT data formed from `txtDictionary`. Fails an assertion if `txtDictionary` cannot be represented as an `NSData` object.
+ (NSData *)dataFromTXTRecordDictionary:(NSDictionary<NSString *, NSData *> *)txtDictionary;

/// Starts a resolve process of a finite duration for the service.
///
/// - Parameters:
///   - timeout: The maximum number of seconds to attempt a resolve. A value of `0.0` indicates no timeout and a resolve process of indefinite duration.
///
/// During the resolve period, the service sends `-netServiceDidResolveAddress:` to the delegate for each address it discovers that matches the service parameters. Once the timeout is hit, the service sends `-netServiceDidStop:` to the delegate. If no addresses resolve during the timeout period, the service sends `-netService:didNotResolve:` to the delegate.
- (void)resolveWithTimeout:(NSTimeInterval)timeout;

/// Creates a pair of input and output streams for the receiver and returns a Boolean value that indicates whether they were retrieved successfully.
///
/// - Parameters:
///   - inputStream: Upon return, the input stream for the receiver. Pass `NULL` if you do not need this stream.
///   - outputStream: Upon return, the output stream for the receiver. Pass `NULL` if you do not need this stream.
/// - Returns: `YES` if the streams are created successfully, otherwise `NO`.
///
/// After this method is called, no delegate callbacks are called by the receiver. The streams that are created are not open, and are not scheduled in any run loop for any mode.
- (BOOL)getInputStream:(out __strong NSInputStream * _Nullable * _Nullable)inputStream outputStream:(out __strong NSOutputStream * _Nullable * _Nullable)outputStream;

/// Sets the TXT record for the receiver, and returns a Boolean value that indicates whether the operation was successful.
///
/// - Parameters:
///   - recordData: The TXT record for the receiver. Pass `nil` to remove the TXT record from the instance.
/// - Returns: `YES` if `recordData` is successfully set as the TXT record, otherwise `NO`.
- (BOOL)setTXTRecordData:(nullable NSData *)recordData;

/// Returns the TXT record for the receiver.
///
/// If the instance has not been resolved, or the delegate's `-netService:didUpdateTXTRecordData:` has not been called, this will return `nil`. It is permitted to have a zero-length TXT record.
- (nullable NSData *)TXTRecordData;

/// Starts the monitoring of TXT-record updates for the receiver.
///
/// The delegate must implement `-netService:didUpdateTXTRecordData:`, which is called when the TXT record for the receiver is updated.
- (void)startMonitoring;

/// Stops the monitoring of TXT-record updates for the receiver.
- (void)stopMonitoring;


@end

#pragma mark -

/// A network service browser that finds published services on a network using multicast DNS.
///
/// Services can range from standard services, such as HTTP and FTP, to custom services defined by other applications. You can use a network service browser in your code to obtain the list of accessible domains and then to obtain an ``NetService`` object for each discovered service. Each network service browser performs one search at a time, so if you want to perform multiple simultaneous searches, use multiple network service browsers.
///
/// A network service browser performs all searches asynchronously using the current run loop to execute the search in the background. Results from a search are returned through the associated delegate object, which your client application must provide. Searching proceeds in the background until the object receives a ``stop()`` message.
///
/// To use an `NSNetServiceBrowser` object to search for services, allocate it, initialize it, and assign a delegate. (If you wish, you can also use the ``schedule(in:forMode:)`` and ``remove(from:forMode:)`` methods to execute searches on a run loop other than the current one.) Once your object is ready, you begin by gathering the list of accessible domains using either the ``searchForRegistrationDomains()`` or ``searchForBrowsableDomains()`` methods. From the list of returned domains, you can pick one and use the ``searchForServices(ofType:inDomain:)`` method to search for services in that domain.
///
/// The `NSNetServiceBrowser` class provides two ways to search for domains. In most cases, your client should use the ``searchForRegistrationDomains()`` method to search only for local domains to which the host machine has registration authority. This is the preferred method for accessing domains as it guarantees that the host machine can connect to services in the returned domains. Access to domains outside this list may be more limited.
API_DEPRECATED("Use nw_browser_t in Network framework instead", macos(10.2, API_TO_BE_DEPRECATED), ios(2.0, API_TO_BE_DEPRECATED), tvos(9.0, API_TO_BE_DEPRECATED)) API_UNAVAILABLE(watchos)
@interface NSNetServiceBrowser : NSObject {
@private
    id _netServiceBrowser;
    id _delegate;
    void * _reserved;
}

/// Initializes an allocated `NSNetServiceBrowser` object.
- (instancetype)init;

/// The delegate object for this instance.
@property (nullable, assign) id <NSNetServiceBrowserDelegate> delegate;

/// Whether to browse over peer-to-peer Bluetooth and Wi-Fi, if available.
///
/// This property must be set before initiating a search to have an effect. Initially set to `NO`.
@property BOOL includesPeerToPeer API_AVAILABLE(macos(10.10), ios(7.0), watchos(2.0), tvos(9.0));

/// Adds the receiver to the specified run loop.
///
/// - Parameters:
///   - aRunLoop: Run loop in which to schedule the receiver.
///   - mode: Run loop mode in which to perform this operation.
///
/// You can use this method in conjunction with `-removeFromRunLoop:forMode:` to transfer the receiver to a run loop other than the default one. You should not attempt to run the receiver on multiple run loops.
- (void)scheduleInRunLoop:(NSRunLoop *)aRunLoop forMode:(NSRunLoopMode)mode;

/// Removes the receiver from the specified run loop.
///
/// - Parameters:
///   - aRunLoop: Run loop from which to remove the receiver.
///   - mode: Run loop mode in which to perform this operation.
///
/// You can use this method in conjunction with `-scheduleInRunLoop:forMode:` to transfer the receiver to a run loop other than the default one. Although it is possible to remove an `NSNetService` object completely from any run loop and then attempt actions on it, you must not do it.
- (void)removeFromRunLoop:(NSRunLoop *)aRunLoop forMode:(NSRunLoopMode)mode;

/// Initiates a search for domains visible to the host. This method returns immediately.
///
/// The delegate receives a `-netServiceBrowser:didFindDomain:moreComing:` message for each domain discovered.
- (void)searchForBrowsableDomains;

/// Initiates a search for domains in which the host may register services.
///
/// This method returns immediately, sending a `-netServiceBrowserWillSearch:` message to the delegate if the network was ready to initiate the search. The delegate receives a subsequent `-netServiceBrowser:didFindDomain:moreComing:` message for each domain discovered.
///
/// Most network service browser clients do not have to use this method -- it is sufficient to publish a service with the empty string, which registers it in any available registration domains automatically.
- (void)searchForRegistrationDomains;

/// Starts a search for services of a particular type within a specific domain.
///
/// - Parameters:
///   - type: Type of the service to search for. Must contain both the service type and transport layer information (e.g. `_http._tcp.`).
///   - domainString: Domain name in which to perform the search. Pass the empty string (`@""`) to search default registration domains.
///
/// This method returns immediately, sending a `-netServiceBrowserWillSearch:` message to the delegate if the network was ready to initiate the search. The delegate receives subsequent `-netServiceBrowser:didFindService:moreComing:` messages for each service discovered.
- (void)searchForServicesOfType:(NSString *)type inDomain:(NSString *)domainString;

/// Halts a currently running search or resolution.
///
/// This method sends a `-netServiceBrowserDidStopSearch:` message to the delegate and causes the browser to discard any pending search results.
- (void)stop;

@end

#pragma mark -

/// The interface a net service uses to inform its delegate about the state of the service it offers.
///
/// The ``NetServiceDelegate`` protocol defines the optional methods implemented by delegates of ``NetService`` objects.
API_AVAILABLE(macos(10.2), ios(2.0), tvos(9.0)) API_UNAVAILABLE(watchos)
@protocol NSNetServiceDelegate <NSObject>
@optional

/// Notifies the delegate that the network is ready to publish the service.
///
/// - Parameters:
///   - sender: The service that is ready to publish.
///
/// Publication of the service proceeds asynchronously and may still generate a call to the delegate's `-netService:didNotPublish:` method if an error occurs.
- (void)netServiceWillPublish:(NSNetService *)sender;

/// Notifies the delegate that a service was successfully published.
///
/// - Parameters:
///   - sender: The service that was published.
- (void)netServiceDidPublish:(NSNetService *)sender;

/// Notifies the delegate that a service could not be published.
///
/// - Parameters:
///   - sender: The service that could not be published.
///   - errorDict: A dictionary containing information about the problem. The dictionary contains the keys `NSNetServicesErrorCode` and `NSNetServicesErrorDomain`.
///
/// This method may be called long after a `-netServiceWillPublish:` message has been delivered to the delegate.
- (void)netService:(NSNetService *)sender didNotPublish:(NSDictionary<NSString *, NSNumber *> *)errorDict;

/// Notifies the delegate that the network is ready to resolve the service.
///
/// - Parameters:
///   - sender: The service that the network is ready to resolve.
///
/// Resolution of the service proceeds asynchronously and may still generate a call to the delegate's `-netService:didNotResolve:` method if an error occurs.
- (void)netServiceWillResolve:(NSNetService *)sender;

/// Informs the delegate that the address for a given service was resolved.
///
/// - Parameters:
///   - sender: The service that was resolved.
///
/// The delegate can use the `addresses` method to retrieve the service's address. If the delegate needs only one address, it can stop the resolution process using `-stop`. Otherwise, the resolution will continue until the timeout specified in `-resolveWithTimeout:` is reached.
- (void)netServiceDidResolveAddress:(NSNetService *)sender;

/// Informs the delegate that an error occurred during resolution of a given service.
///
/// - Parameters:
///   - sender: The service that did not resolve.
///   - errorDict: A dictionary containing information about the problem. The dictionary contains the keys `NSNetServicesErrorCode` and `NSNetServicesErrorDomain`.
///
/// Clients may try to resolve again upon receiving this error. For example, a DNS rotary may yield different IP addresses on different resolution requests. A common error condition is that no addresses were resolved during the timeout period specified in `-resolveWithTimeout:`.
- (void)netService:(NSNetService *)sender didNotResolve:(NSDictionary<NSString *, NSNumber *> *)errorDict;

/// Informs the delegate that a `-publish` or `-resolveWithTimeout:` request was stopped.
///
/// - Parameters:
///   - sender: The service that stopped.
- (void)netServiceDidStop:(NSNetService *)sender;

/// Notifies the delegate that the TXT record for a given service has been updated.
///
/// - Parameters:
///   - sender: The service whose TXT record was updated.
///   - data: The new TXT record.
- (void)netService:(NSNetService *)sender didUpdateTXTRecordData:(NSData *)data;


/// Called when a client connects to a service managed by Bonjour.
///
/// - Parameters:
///   - sender: The net service object that the client connected to.
///   - inputStream: A stream object for receiving data from the client.
///   - outputStream: A stream object for sending data to the client.
///
/// When you publish a service, if you set the `NSNetServiceListenForConnections` flag in the service options, the service object accepts connections on behalf of your app. Later, when a client connects to that service, the service object calls this method to provide the app with a pair of streams for communicating with that client.
- (void)netService:(NSNetService *)sender didAcceptConnectionWithInputStream:(NSInputStream *)inputStream outputStream:(NSOutputStream *)outputStream API_AVAILABLE(macos(10.9), ios(7.0), watchos(2.0), tvos(9.0));

@end

#pragma mark -

/// The interface a net service browser uses to inform a delegate about the state of service discovery.
///
/// Delegates of ``NetServiceBrowser`` instances optionally implement these methods.
API_AVAILABLE(macos(10.2), ios(2.0), tvos(9.0)) API_UNAVAILABLE(watchos)
@protocol NSNetServiceBrowserDelegate <NSObject>
@optional

/// Tells the delegate that a search is commencing.
///
/// - Parameters:
///   - browser: Sender of this delegate message.
///
/// This message is sent to the delegate only if the underlying network layer is ready to begin a search. The delegate can use this notification to prepare its data structures to receive data.
- (void)netServiceBrowserWillSearch:(NSNetServiceBrowser *)browser;

/// Tells the delegate that a search was stopped.
///
/// - Parameters:
///   - browser: Sender of this delegate message.
///
/// When the browser receives a `-stop` message from its client, it sends a `netServiceBrowserDidStopSearch:` message to its delegate. The delegate then performs any necessary cleanup.
- (void)netServiceBrowserDidStopSearch:(NSNetServiceBrowser *)browser;

/// Tells the delegate that a search was not successful.
///
/// - Parameters:
///   - browser: Sender of this delegate message.
///   - errorDict: Dictionary with the reasons the search was unsuccessful. Use the dictionary keys `NSNetServicesErrorCode` and `NSNetServicesErrorDomain` to retrieve the error information from the dictionary.
- (void)netServiceBrowser:(NSNetServiceBrowser *)browser didNotSearch:(NSDictionary<NSString *, NSNumber *> *)errorDict;

/// Tells the delegate the sender found a domain.
///
/// - Parameters:
///   - browser: Sender of this delegate message.
///   - domainString: Name of the domain found by the browser.
///   - moreComing: `YES` when the browser is waiting for additional domains. `NO` when there are no additional domains.
///
/// The delegate uses this message to compile a list of available domains. It should wait until `moreComing` is `NO` to do a bulk update of user interface elements.
- (void)netServiceBrowser:(NSNetServiceBrowser *)browser didFindDomain:(NSString *)domainString moreComing:(BOOL)moreComing;

/// Tells the delegate the sender found a service.
///
/// - Parameters:
///   - browser: Sender of this delegate message.
///   - service: Network service found by the browser. The delegate can use this object to connect to and use the service.
///   - moreComing: `YES` when the browser is waiting for additional services. `NO` when there are no additional services.
///
/// The delegate uses this message to compile a list of available services. It should wait until `moreComing` is `NO` to do a bulk update of user interface elements.
- (void)netServiceBrowser:(NSNetServiceBrowser *)browser didFindService:(NSNetService *)service moreComing:(BOOL)moreComing;

/// Tells the delegate the a domain has disappeared or has become unavailable.
///
/// - Parameters:
///   - browser: Sender of this delegate message.
///   - domainString: Name of the domain that became unavailable.
///   - moreComing: `YES` when the browser is waiting for additional domains. `NO` when there are no additional domains.
///
/// The delegate uses this message to compile a list of unavailable domains. It should wait until `moreComing` is `NO` to do a bulk update of user interface elements.
- (void)netServiceBrowser:(NSNetServiceBrowser *)browser didRemoveDomain:(NSString *)domainString moreComing:(BOOL)moreComing;

/// Tells the delegate a service has disappeared or has become unavailable.
///
/// - Parameters:
///   - browser: Sender of this delegate message.
///   - service: Network service that has become unavailable.
///   - moreComing: `YES` when the browser is waiting for additional services. `NO` when there are no additional services.
///
/// The delegate uses this message to compile a list of unavailable services. It should wait until `moreComing` is `NO` to do a bulk update of user interface elements.
- (void)netServiceBrowser:(NSNetServiceBrowser *)browser didRemoveService:(NSNetService *)service moreComing:(BOOL)moreComing;

@end

NS_HEADER_AUDIT_END(nullability, sendability)
