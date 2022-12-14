/*
    File:  AVCustomRoutingEvent.h
    
    Framework:  AVRouting
    
    Copyright © 2022 Apple Inc. All rights reserved.
    
 */

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@class AVCustomDeviceRoute;

/*!
	@constant	AVCustomRoutingEventReasonActivate
				Represents an activation event, e.g. a user selected a route in the picker.
	@constant	AVCustomRoutingEventReasonDeactivate
				Represents a deactivation event, e.g. a user deselected a route in the picker.
	@constant	AVCustomRoutingEventReasonReactivate
				Represents a reactivation event, e.g. a route that is already authorized is selected by the user.
 */
typedef NS_ENUM(NSInteger, AVCustomRoutingEventReason) {
	AVCustomRoutingEventReasonActivate = 0,
	AVCustomRoutingEventReasonDeactivate,
	AVCustomRoutingEventReasonReactivate,
};

/*!
	@class		AVCustomRoutingEvent
	@abstract	This class represents an event that occurs on a route.
	@discussion	Depending on the reason for the event, clients are expected to establish or tear down the connection to the given route.
 */
API_AVAILABLE(ios(16.0)) API_UNAVAILABLE(macos) API_UNAVAILABLE(tvos, watchos)
@interface AVCustomRoutingEvent : NSObject

/*!
	@property 	reason
	@abstract	The reason for the event.
 */
@property (nonatomic, readonly) AVCustomRoutingEventReason reason API_AVAILABLE(ios(16.0)) API_UNAVAILABLE(macos) API_UNAVAILABLE(tvos, watchos);

/*!
	@property 	route
	@abstract	The route associated with the event.
 */
@property (nonatomic, readonly) AVCustomDeviceRoute *route API_AVAILABLE(ios(16.0)) API_UNAVAILABLE(macos) API_UNAVAILABLE(tvos, watchos);

@end

NS_ASSUME_NONNULL_END
