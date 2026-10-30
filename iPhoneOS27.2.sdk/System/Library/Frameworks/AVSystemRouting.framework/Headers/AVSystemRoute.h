/*
    File:  AVSystemRoute.h
    
    Framework:  AVSystemRouting
    
    Copyright © 2026 Apple Inc. All rights reserved.
    
 */

#import <Foundation/Foundation.h>
#import <AVKit/AVKit.h>
#import <UniformTypeIdentifiers/UTType.h>

NS_ASSUME_NONNULL_BEGIN

/// The mode that determines how media playback launches on a remote device.
///
/// Use this enumeration with ``AVSystemRouteSession/initWithURL:mode:`` to control how
/// media playback is initiated on the remote device. The launch mode determines whether
/// your app launches its counterpart on the remote device, or uses a system-provided
/// media player.
API_AVAILABLE(ios(27.0)) API_UNAVAILABLE(tvos, watchos, macos, macCatalyst, visionos)
typedef NS_ENUM(NSInteger, AVSystemRouteLaunchMode) {
	/// Launches the corresponding application on the remote device.
	///
	/// Use this mode when you want to start your app's counterpart on the remote device,
	/// enabling app-to-application communication and custom playback experiences. The remote application
	/// can handle the provided URL and maintain bidirectional communication through the
	/// `AVSystemRouteDataChannel` returned in the completion handler.
	///
	/// Application identifiers must be configured in the `MDESupportedProtocols`
	/// key in your app's `Info.plist` file. For example:
	/// ```xml
	/// <key>MDESupportedProtocols</key>
	///	<dict>
	///		<key>com.example.sharingprotocol</key>
	///		<string>com.example.myapplicationidentifier</string>
	/// </dict>
	/// ```
	///
	/// - Important: If `MDESupportedProtocols` is not set, calls to
	///              ``AVSystemRouteSession/startWithCompletionHandler:`` fail.
	AVSystemRouteLaunchModeApplication,
	
	/// Launches the system's built-in media player on the remote device.
	///
	/// Use this mode when you want to use the remote device's built-in media player
	/// instead of launching a custom application. This provides a standardized playback
	/// experience without requiring a corresponding application to be installed on the remote device.
	///
	/// To support the `AVSystemRouteLaunchModePlayer` launch mode,
	/// the `MDESupportsUniversalURLPlayback` key must be set in the app's `Info.plist` file. For example:
	/// ```xml
	/// <key>MDESupportsUniversalURLPlayback</key>
	/// <true/>
	/// ```
	///
	/// - Important: If `MDESupportsUniversalURLPlayback` is not set to `true`, calls to
	///              ``AVSystemRouteSession/startWithCompletionHandler:`` fail.
	AVSystemRouteLaunchModePlayer,
} NS_REFINED_FOR_SWIFT;

@class AVSystemRouteSession;

/// An active media route to a remote device that manages connection and communication for media playback and data exchange.
///
/// Use this object to control playback sessions, communicate with remote applications through data channels, and manage the lifecycle of remote connections.
///
/// The system route provides a high-level abstraction for routing media content to external devices
/// such as TVs, speakers, or other compatible endpoints. You can create multiple
/// sessions on a single route to manage different playback contexts or communication channels.
///
/// ## Manage sessions
///
/// Create an ``AVSystemRouteSession-5i6j6`` to initiate playback or communication with the remote device.
///
/// ## Access the protocol identifier
///
/// The ``AVSystemRoute/protocolType`` property identifies the communication protocol used by the active route.
///
/// ## Send and receive data
///
/// Use the ``AVSystemRoute/routeDataChannel`` property to send and receive custom data with the extension
/// outside of any media session. This enables control messages, state synchronization, and
/// other bidirectional communication needs.
API_AVAILABLE(ios(27.0)) API_UNAVAILABLE(tvos, watchos, macos, macCatalyst, visionos)
NS_REFINED_FOR_SWIFT
NS_SWIFT_SENDABLE
@interface AVSystemRoute : NSObject

- (instancetype)init NS_UNAVAILABLE;

+ (instancetype)new NS_UNAVAILABLE;

/// The communication protocol the active route uses.
///
/// The protocol's `identifier` property enables your app to adapt its behavior based on the selected protocol.
/// The protocol's display name and icon can also be obtained from the `UTType`.
@property (readonly, copy) UTType *protocolType;

/// The SF Symbol name representing the remote device or route.
///
/// This property returns a system symbol name as an `NSString` that identifies the type of device
/// (such as a TV, speaker, or other compatible endpoint). Use this value with
/// `UIImage(systemName:)` to create an icon for display in your app's user interface.
///
/// ```objc
/// UIImage *routeIcon = [UIImage systemImageNamed:route.routeSymbolName];
/// ```
///
/// The symbol helps people visually identify where their media will be played.
@property (readonly, copy) NSString *routeSymbolName;

/// The user-facing display name of the remote device or route.
///
/// Use this property to show the name of the destination device in your app's user interface. The display name
/// typically reflects a custom name for the device or a default name the system provides.
@property (readonly, copy) NSString *routeDisplayName;

/// Adds a session to the active route.
///
/// Call this method to register a new ``AVSystemRouteSession-5i6j6`` with the route before starting
/// playback or communication. The session must be added to the route before calling its
/// ``AVSystemRouteSession/startWithCompletionHandler:`` method.
///
/// Adding a session establishes the association between the session and this route, enabling
/// the system to manage the session's lifecycle and route media appropriately. You can add
/// multiple sessions to a single route to handle different media streams or communication channels.
///
/// Sessions are single-use. Once a session has been stopped, it cannot be added to a route
/// again. Create a new ``AVSystemRouteSession-5i6j6`` for each new playback.
///
/// - Parameter session: The session to add to this route. The session must be newly created and
///                      not already associated with another route or previously stopped.
///
/// - Returns: `true` if the route successfully adds the session; `false` if the route cannot add it
///            (for example, if the session is already associated with another route or if the
///            route is in an invalid state).
///
/// - Note: You must remove sessions when they are no longer needed using ``AVSystemRoute/removeSession:``
///         to release system resources.
- (BOOL)addSession:(AVSystemRouteSession *)session;

/// Removes a session from the active route.
///
/// Call this method to unregister a session from the route when playback ends or when you no
/// longer need the session. Removing a session stops any ongoing communication associated with
/// that session and releases system resources.
///
/// If the session is currently active, this method stops the session before removing it.
///
/// - Parameter session: The session to remove from this route. If the session is not currently
///                      associated with this route, this method has no effect.
///
/// - Important: Always remove sessions when they are no longer needed to ensure proper cleanup
///              of system resources and network connections. To start new playback after removing
///              a session, create a new ``AVSystemRouteSession-5i6j6`` instance.
- (void)removeSession:(AVSystemRouteSession *)session;

@end

@class AVSystemRouteMediaSession;

/// An object that manages a single media playback session on a remote device.
///
/// ``AVSystemRouteSession`` manages a single media playback session on a remote device. Create a
/// session to initiate playback on a connected device, communicate with a remote application, and
/// control the lifecycle of the remote playback experience.
///
/// To use a session:
/// 1. Create an ``AVSystemRouteSession`` with a URL and launch mode
/// 2. Add the session to an ``AVSystemRoute-9kkj3`` using ``AVSystemRoute/addSession:``
/// 3. Start the session with ``AVSystemRouteSession/startWithCompletionHandler:``
/// 4. Use the returned ``AVSystemRouteMediaSession-4mo0j`` to communicate with the remote device
/// 5. Call ``AVSystemRouteSession/stop`` when playback ends to clean up resources
///
/// Sessions are single-use. After calling ``AVSystemRouteSession/stop``, the session cannot be
/// restarted or added to another route. Create a new ``AVSystemRouteSession`` for each new
/// playback.
///
/// ## Reporting Playback Metadata
///
/// Report playback metadata to `MPNowPlayingInfoCenter` to ensure the system displays accurate
/// information about the current media across a person's devices and in system UI.
API_AVAILABLE(ios(27.0)) API_UNAVAILABLE(tvos, watchos, macos, macCatalyst, visionos)
NS_REFINED_FOR_SWIFT
NS_SWIFT_SENDABLE
@interface AVSystemRouteSession : NSObject

- (instancetype)init NS_UNAVAILABLE;

+ (instancetype)new NS_UNAVAILABLE;

/// Creates a session for initiating playback on a remote device.
///
/// Initialize a session with the media URL and launch mode before adding it to an ``AVSystemRoute-9kkj3``.
/// The URL and mode determine how the remote device handles playback — either by launching your
/// app's counterpart or using the system's built-in media player.
///
/// - Parameters:
///   - url: The URL identifying the media content to play. This URL is passed to the remote
///          application or player. For application mode, your remote application receives this URL to
///          handle appropriately (for example, to navigate to specific content). For player
///          mode, the system uses this URL to load media directly.
///   - mode: The launch mode determining whether to start your app's counterpart
///           (``AVSystemRouteLaunchMode/application``) or the system media player
///           (``AVSystemRouteLaunchMode/player``) on the remote device.
///
/// - Note: After creating a session, you must add it to an ``AVSystemRoute-9kkj3`` using ``AVSystemRoute/addSession:``
///         before calling ``AVSystemRouteSession/startWithCompletionHandler:``.
- (instancetype)initWithURL:(NSURL *)url mode:(AVSystemRouteLaunchMode)mode;

/// Starts the session and initiates media playback on the remote device.
///
/// Call this method to begin the playback session after adding it to an ``AVSystemRoute-9kkj3``. The
/// session uses the URL and launch mode specified during initialization to start playback on
/// the remote device.
///
/// When using ``AVSystemRouteLaunchMode/application``, your app must declare supported protocol
/// identifiers in the `MDESupportedProtocols` key in your `Info.plist` file. These
/// identifiers enable the system to establish communication between your app and its counterpart
/// on the remote device.
///
/// After a successful launch with ``AVSystemRouteLaunchMode/application``, the returned
/// ``AVSystemRouteMediaSession-4mo0j`` provides access to a ``AVSystemRouteMediaSession-4mo0j/dataChannel`` and a ``AVSystemRouteMediaSession-4mo0j/playbackControl``.
/// Use these objects to send playback commands, state updates, or custom messages between your
/// app and the remote application.
///
/// Report playback metadata to `MPNowPlayingInfoCenter` to ensure the system displays accurate
/// information about the current media across a person's devices.
///
/// - Parameter completionHandler: A completion handler called when the launch operation completes.
///                                The handler receives two parameters:
///                                - `launchError`: An error object if the launch failed, or `nil`
///                                  on success.
///                                - `mediaSession`: A media session object for communicating with
///                                  the remote device.
///                                  Access its ``AVSystemRouteMediaSession-4mo0j/dataChannel`` property to send and receive
///                                  data between your app and the remote application. Access its ``AVSystemRouteMediaSession-4mo0j/playbackControl`` property to send and receive playback commands between your app and the remote application. For ``AVSystemRouteLaunchMode/player``, ``AVSystemRouteMediaSession-4mo0j/dataChannel`` is `nil`.
///
/// - Important: Call ``AVSystemRouteSession/stop`` when playback ends to properly clean up the remote session.
///
/// - Note: This method operates asynchronously. The completion handler may be called on a
///         background queue, so dispatch to the main queue if you need to update UI.
- (void)startWithCompletionHandler:(void (^)(NSError * _Nullable launchError, AVSystemRouteMediaSession * _Nullable mediaSession))completionHandler;

/// Stops the session and terminates media playback on the remote device.
///
/// Call this method to end the playback session and clean up resources on both the local and
/// remote devices. After calling this method, the session is terminated and further calls to
/// session methods will have no effect.
///
/// The system automatically handles disconnection and cleanup of the remote application or
/// player. If you need to start playback again, create a new ``AVSystemRouteSession`` instance.
///
/// - Note: Always call this method when playback ends to ensure proper resource cleanup and to
///         notify the remote device that the session has concluded.
- (void)stop;

@end

@class AVSystemRouteDataChannel;

/// An object that provides playback controls and a data channel for a session running on a remote device.
///
/// Use this object to access playback controls and a data channel for communicating
/// with the remote application. Call ``AVSystemRouteSession/startWithCompletionHandler:`` to get this object
/// after adding a session to an ``AVSystemRoute-9kkj3``.
API_AVAILABLE(ios(27.0)) API_UNAVAILABLE(tvos, watchos, macos, macCatalyst, visionos)
NS_REFINED_FOR_SWIFT
NS_SWIFT_SENDABLE
@interface AVSystemRouteMediaSession : NSObject

- (instancetype)init NS_UNAVAILABLE;

+ (instancetype)new NS_UNAVAILABLE;

/// The playback control interface for the remote session.
///
/// This property is always non-nil when obtained from a successful call to ``AVSystemRouteSession/start()``.
///
/// - Important: Always update media playback state information regularly in the playbackControl object to ensure
///              the system displays accurate information about the current media play state across a person's
///              devices and in system UI.
@property (readonly, nullable) NSObject<AVPlaybackUserInterfaceControllable> *playbackControl;

/// The data channel for sending and receiving data with the remote application.
///
/// This property is always non-nil when obtained from a successful call to ``AVSystemRouteSession/start()``.
@property (readonly, nullable) AVSystemRouteDataChannel *dataChannel;

@end

/// Properties for custom media app-to-extension communication.
API_AVAILABLE(ios(27.0)) API_UNAVAILABLE(tvos, watchos, macos, macCatalyst, visionos)
@interface AVSystemRoute (CustomExtensionCommunication)

/// A data channel for communicating with the extension outside of any media session.
///
/// Use this channel for control messages, state synchronization, and other bidirectional
/// communication needs that are not tied to a specific ``AVSystemRouteSession-5i6j6``.
@property (nonatomic, readonly) AVSystemRouteDataChannel *routeDataChannel;

@end

/// A protocol for handling data from a remote application.
API_AVAILABLE(ios(27.0)) API_UNAVAILABLE(tvos, watchos, macos, macCatalyst, visionos)
NS_REFINED_FOR_SWIFT
@protocol AVSystemRouteDataDelegate <NSObject>

/// Receives data sent from a connected remote application.
///
/// - Parameters:
///   - data: The data received from the remote application.
///   - completionHandler: A completion handler to call after processing the received data.
///     Pass an error if processing fails, or `nil` on success.
- (void)receiveData:(NSData *)data completionHandler:(void (^)(NSError * _Nullable error))completionHandler;
@end

/// An object that manages bidirectional data communication with a remote application.
API_AVAILABLE(ios(27.0)) API_UNAVAILABLE(tvos, watchos, macos, macCatalyst, visionos)
NS_REFINED_FOR_SWIFT
NS_SWIFT_SENDABLE
@interface AVSystemRouteDataChannel : NSObject

- (instancetype)init NS_UNAVAILABLE;

+ (instancetype)new NS_UNAVAILABLE;

/// Sends data to a remote application.
///
/// Calling this function again before the completion handler of a previous send is called is safe;
/// multiple send operations can be in-flight concurrently.
///
/// - Parameters:
///   - data: The data to send to the remote application.
///   - completionHandler: A completion handler called when the send operation completes.
///     The handler receives an error if the send failed, or `nil` on success.
- (void)sendData:(NSData *)data completionHandler:(void (^)(NSError * _Nullable error))completionHandler;

/// The delegate that handles incoming data from a remote application.
@property (nonatomic, weak, nullable) id<AVSystemRouteDataDelegate> dataDelegate;

@end

NS_ASSUME_NONNULL_END
