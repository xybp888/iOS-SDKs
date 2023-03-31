/*
    File:  AVCustomRoutingController.h
    
    Framework:  AVRouting
    
    Copyright © 2022 Apple Inc. All rights reserved.
    
 */

#import <Foundation/Foundation.h>

#import <AVRouting/AVRoutingDefines.h>

NS_ASSUME_NONNULL_BEGIN

@class AVCustomDeviceRoute;
@class AVCustomRoutingEvent;
@class AVCustomRoutingActionItem;
@class AVCustomRoutingPartialIP;
@protocol AVCustomRoutingControllerDelegate;

/*!
	@constant	AVCustomRoutingControllerAuthorizedRoutesDidChangeNotification
	@abstract	Posted when the value of authorizedRoutes changes.
 */
AVROUTING_EXTERN NSNotificationName const AVCustomRoutingControllerAuthorizedRoutesDidChangeNotification NS_SWIFT_NAME(AVCustomRoutingController.authorizedRoutesDidChange) API_AVAILABLE(ios(16.0)) API_UNAVAILABLE(macos) API_UNAVAILABLE(tvos, watchos);

/*!
	@class		AVCustomRoutingController
	@abstract	When a user selects / deselects a 3rd party device in the route picker, this class delegates the activation / deactivation of that device to the client of this class via AVCustomRoutingEvents.
	@discussion	This class also informs the client which routes have been previously authorized, allowing them to reconnect if appropriate.
 */
API_AVAILABLE(ios(16.0)) API_UNAVAILABLE(macos) API_UNAVAILABLE(tvos, watchos)
@interface AVCustomRoutingController : NSObject

/*!
	@property 	delegate
	@abstract	The receiver's delegate.
 */
@property (nonatomic, weak, nullable) id<AVCustomRoutingControllerDelegate> delegate API_AVAILABLE(ios(16.0)) API_UNAVAILABLE(macos) API_UNAVAILABLE(tvos, watchos);

/*!
	@property 	authorizedRoutes
	@abstract	The list of authorized routes. Once a route has been activated, it remains authorized for a certain amount of time even if the connection to the route temporarily goes down.
				The app may reactivate any one of these routes if they deem it appropriate, but must inform the system by calling -setActive:forRoute:.
 */
@property (nonatomic, readonly) NSArray<AVCustomDeviceRoute *> *authorizedRoutes API_AVAILABLE(ios(16.0)) API_UNAVAILABLE(macos) API_UNAVAILABLE(tvos, watchos);

/*!
    @property   knownRouteIPs
    @abstract   An array of route IPs known to be on the local network.
 */
@property (nonatomic, strong) NSArray<AVCustomRoutingPartialIP *> *knownRouteIPs API_AVAILABLE(ios(16.1)) API_UNAVAILABLE(macos) API_UNAVAILABLE(tvos, watchos);

/*!
    @property   customActionItems
    @abstract   An array of custom action items to be added in the picker.
 */
@property (nonatomic, strong) NSArray<AVCustomRoutingActionItem *> *customActionItems API_AVAILABLE(ios(16.0)) API_UNAVAILABLE(macos) API_UNAVAILABLE(tvos, watchos);

/*!
	@method     invalidateAuthorization
	@param		route
				The route for which to invalidate authorization.
	@abstract	Calling this method revokes the app's authorization to connect to a route. The route will only become authorized again if the user selects it via the route picker.
 */
- (void)invalidateAuthorizationForRoute:(AVCustomDeviceRoute *)route;

/*!
    @method     setActive:forRoute:
    @param      active
                Whether or not the route is active.
    @param      route
                The route to set as active or inactive.
    @abstract   Set this to NO if the connection to the route temporarily drops, and set it to YES once the connection is reestablished.
 */
- (void)setActive:(BOOL)active forRoute:(AVCustomDeviceRoute *)route;

/*!
    @method     isRouteActive:
    @param      route
                The route for which to check active status.
    @abstract   Returns whether or not the given route is active.
 */
- (BOOL)isRouteActive:(AVCustomDeviceRoute *)route;

@end


/*!
	@protocol	AVCustomRoutingControllerDelegate
	@abstract	A protocol for delegates of AVCustomRoutingController.
 */
API_AVAILABLE(ios(16.0)) API_UNAVAILABLE(macos) API_UNAVAILABLE(tvos, watchos)
@protocol AVCustomRoutingControllerDelegate <NSObject>

/*!
	@method		customRoutingController:handleEvent:completionHandler:
	@param		controller
				The custom routing controller.
	@param		event
				The route event for the delegate to process.
	@param		completionHandler
				The completion handler the delegate needs to call after the event has been processed. Pass YES to the completion handler if the activation, reactivation or deactivation of the route was successful, and NO otherwise.
	@abstract	The delegate needs to implement this method in order to both establish and tear down connection to a device when a user requests it through the picker.
 */
- (void)customRoutingController:(AVCustomRoutingController *)controller handleEvent:(AVCustomRoutingEvent *)event completionHandler:(void (^)(BOOL success))completionHandler;


@optional

/*!
	@method		customRoutingController:eventDidTimeOut:
	@param		controller
                The custom routing controller.
	@param		event
				The route event that timed out.
	@abstract	The delegate can implement this method in order know when a route event timed out. This gives them a chance to clean up any connection attempts that are currently in flight.
 */
- (void)customRoutingController:(AVCustomRoutingController *)controller eventDidTimeOut:(AVCustomRoutingEvent *)event;

/*!
    @method     customRoutingController:didSelectItem:
    @abstract   Informs the delegate that the user selected a custom item in the route picker.
 */
- (void)customRoutingController:(AVCustomRoutingController *)controller didSelectItem:(AVCustomRoutingActionItem *)customActionItem;

@end


/*!
    @class      AVCustomRoutingPartialIP
    @abstract   Represents a full or partial IP address. To be used in conjunction with AVCustomRoutingController.knownRouteIPs
 */
API_AVAILABLE(ios(16.1)) API_UNAVAILABLE(macos) API_UNAVAILABLE(tvos, watchos)
@interface AVCustomRoutingPartialIP : NSObject

/*!
    @property   address
    @abstract   Bytes of the IP address. A full or partial IP address for a device known to be on the network.
    @discussion To create full known IP, the app would do the following:
                    var anIPAddressInBytes:[Byte] = [192, 168, 10, 5]
                    var address = Data(bytes: anAddressInBytes, length: anAddressInBytes.count)
                    var aMaskInBytes:[Byte] = [255, 255, 255, 255]
                    var mask = Data(bytes: aMaskInBytes, length: aMaskInBytes.count)
                    var partialIP = AVCustomRoutingPartialIP(address: address, mask: mask)
 */
@property (readonly, copy, nonatomic) NSData *address API_AVAILABLE(ios(16.1)) API_UNAVAILABLE(macos) API_UNAVAILABLE(tvos, watchos);

/*!
    @property   mask
    @abstract   A mask representing how many octets of the ip address to respect.
    @discussion An app can use this mask to only pass e.g. the last two bytes of the IP address. So instead of passing the full IP address, the app can pass just the last two bytes by masking the first two.
                    var anIPAddressInBytes:[Byte] = [0, 0, 10, 5]
                    var address = Data(bytes: anAddressInBytes, length: anAddressInBytes.count)
                    var aMaskInBytes:[Byte] = [0, 0, 255, 255]
                    var mask = Data(bytes: aMaskInBytes, length: aMaskInBytes.count)
                    var partialIP =AVCustomRoutingPartialIP(address: address, mask: mask)
 */
@property (readonly, copy, nonatomic) NSData *mask API_AVAILABLE(ios(16.1)) API_UNAVAILABLE(macos) API_UNAVAILABLE(tvos, watchos);

/*!
    @method     initWithAddress:mask:
    @abstract   Initializes an IP fragment.
 */
- (instancetype)initWithAddress:(NSData *)address mask:(NSData *)mask API_AVAILABLE(ios(16.1)) API_UNAVAILABLE(macos) API_UNAVAILABLE(tvos, watchos);

- (instancetype)init NS_UNAVAILABLE;

+ (instancetype)new NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
