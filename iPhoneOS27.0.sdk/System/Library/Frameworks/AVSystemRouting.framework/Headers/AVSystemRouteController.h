/*
    File:  AVSystemRouteController.h
    
    Framework:  AVSystemRouting
    
    Copyright © 2026 Apple Inc. All rights reserved.
    
 */

#import <Foundation/Foundation.h>
#import <AVSystemRouting/AVSystemRoute.h>

NS_ASSUME_NONNULL_BEGIN

@protocol AVSystemRouteControllerObserver;

/// An object that manages interaction with system routes.
///
/// Important: Your app must declare support for extensions with the `MDESupportsUniversalURLPlayback` key and/or for specific protocols in
/// the `MDESupportedProtocols` key of  the app's `Info.plist`.
/// ```xml
/// <key>MDESupportsUniversalURLPlayback</key>
///     <true/>
/// <key>MDESupportedProtocols</key>
///    <dict>
///        <key>com.example.sharingprotocol</key>
///        <string>com.example.myapplicationidentifier</string>
/// </dict>
/// ```
/// Where the key in `MDESupportedProtocols` is the Protocol ID of the extension you are declaring support for and the string value
/// is the application ID of your remote application which the protocol would launch on the receiver.
///
/// Use the shared ``AVSystemRouteController/sharedController`` instance to observe routing events.
/// Register an ``AVSystemRouteControllerObserver-7p7a5`` to receive callbacks when users select or deselect
/// routes in the system route picker.
API_AVAILABLE(ios(27.0)) API_UNAVAILABLE(tvos, watchos, macos, macCatalyst, visionos)
NS_REFINED_FOR_SWIFT
NS_SWIFT_SENDABLE
@interface AVSystemRouteController : NSObject

- (instancetype)init NS_UNAVAILABLE;

+ (instancetype)new NS_UNAVAILABLE;

/// The shared system routing controller instance.
@property (class, nonatomic, readonly) AVSystemRouteController *sharedController;

/// A Boolean value that indicates whether a supported system routing extension is available.
///
/// This property is `YES` when the app has declared support for at least one form of
/// system routing in its `Info.plist` and a matching extension is installed:
/// - one or more protocols listed under `MDESupportedProtocols` and at least one installed
///   extension matches, or
/// - `MDESupportsUniversalURLPlayback` set to `true`, with an installed extension that
///   supports URL playback.
///
/// If neither key is declared, or no installed extension matches the declared support,
/// this property is `NO`.
///
/// Check this property before attempting to use the routing controller to ensure that the
/// necessary system support is available for your app's routing requirements.
@property (class, nonatomic, readonly, getter = isSupportedExtensionAvailable) BOOL supportedExtensionAvailable;

/// Adds an observer to receive notifications about system routing events.
///
/// Use this method to register an observer that receives callbacks when people interact
/// with system routes in the route picker. The observer must conform to the
/// ``AVSystemRouteControllerObserver-7p7a5`` protocol and implement the required protocol method
/// to handle routing events such as route activation and deactivation.
///
/// Important: Your app must declare support for extensions with the `MDESupportsUniversalURLPlayback` key and/or for specific protocols in
/// the `MDESupportedProtocols` key of  the app's `Info.plist`.  This observer will only be called back when a user selects a route that has
/// been provided by an extension that matches one of your app's specified supported protocols.
///
/// - Parameter observer: An object that conforms to ``AVSystemRouteControllerObserver-7p7a5``
///   to receive routing event notifications.
/// - Returns: `YES` if the observer was successfully added; `NO` if the observer was already
///   registered, if registration failed, or if a previous registration for the same observer
///   was cleaned up due to the observer being deallocated.
- (BOOL)addObserver:(id<AVSystemRouteControllerObserver>)observer;

/// Removes a previously registered observer from the system routing controller.
///
/// Call this method to unregister an observer when it no longer needs to receive routing
/// event notifications. This is typically done in the observer's deallocation or
/// when the observer is no longer relevant to avoid memory leaks and unnecessary callbacks.
///
/// - Parameter observer: The observer object to remove. If the observer is not currently
///   registered, this method has no effect.
- (void)removeObserver:(id<AVSystemRouteControllerObserver>)observer;

@end

/// Values that indicate the reason for a routing event.
API_AVAILABLE(ios(27.0)) API_UNAVAILABLE(tvos, watchos, macos, macCatalyst, visionos)
typedef NS_ENUM(NSInteger, AVSystemRouteEventReason) {

/// A value that indicates a user selected a route in the picker.
	AVSystemRouteEventReasonActivate = 0,

/// A value that indicates a user deselected a route in the picker.
	AVSystemRouteEventReasonDeactivate,
} NS_REFINED_FOR_SWIFT;

/// An object that represents an event that occurs on a system route.
API_AVAILABLE(ios(27.0)) API_UNAVAILABLE(tvos, watchos, macos, macCatalyst, visionos)
NS_REFINED_FOR_SWIFT
NS_SWIFT_SENDABLE
@interface AVSystemRouteEvent : NSObject

- (instancetype)init NS_UNAVAILABLE;

+ (instancetype)new NS_UNAVAILABLE;

/// The reason for the routing event.
@property (nonatomic, readonly) AVSystemRouteEventReason reason;

/// The system route for the event.
@property (nonatomic, readonly) AVSystemRoute *route;

@end

/// A protocol for observers of a system routing controller.
API_AVAILABLE(ios(27.0)) API_UNAVAILABLE(tvos, watchos, macos, macCatalyst, visionos)
NS_REFINED_FOR_SWIFT
@protocol AVSystemRouteControllerObserver <NSObject>
/// Connects to, or disconnects from, a device when a user requests it in the
/// picker.
///
/// - Parameters:
///   - controller: The system routing controller.
///   - event: The routing event to handle.
///   - completionHandler: A completion handler to call after processing the event.
///     Pass `YES` if the event was handled successfully, `NO` otherwise.
- (void)systemRouteController:(AVSystemRouteController *) controller handleEvent:(AVSystemRouteEvent *) event completionHandler:(void (^)(BOOL success)) completionHandler;

@end

NS_ASSUME_NONNULL_END
