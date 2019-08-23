//
//  PKPushRegistry.h
//  PushKit
//
//  Copyright (c) 2014 Apple. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <PushKit/PKDefines.h>

/* PKPushType constants can be used to register for a PKPushType-specific push token or to identify received push
   notifications.
 */
PK_EXPORT NSString * const PKPushTypeVoIP NS_AVAILABLE_IOS(8_0);
PK_EXPORT NSString * const PKPushTypeComplication NS_AVAILABLE_IOS(9_0);

@protocol PKPushRegistryDelegate;
@class PKPushCredentials, PKPushPayload;

/*!
 @class         PKPushRegistry
 @abstract      An instance of this class can be used to register for 3rd party notifications. The supported push
                notification types are listed above as NSString constants.
 */
NS_CLASS_AVAILABLE_IOS(8_0)
@interface PKPushRegistry : NSObject

/*!
 @property      delegate
 @abstract      Setting a delegate is required to receive device push tokens and incoming pushes.
 */
@property (readwrite,weak) id<PKPushRegistryDelegate> delegate;

/*!
 @property      desiredPushTypes
 @abstract      An app requests registration for various types of pushes by setting this NSSet to the desired
                PKPushType NSString constants. Push tokens and notifications will be delivered via delegate callback.
 */
@property (readwrite,copy) NSSet *desiredPushTypes;

/*!
 @method        pushTokenForType:
 @abstract      Access the locally cached push token for a specified PKPushType.
 @discussion    A push token returned here has previously been given to the delegate via handlePushTokenUpdate:forType:
                callback.
 @param         type
                This is a PKPushType NSString constant that is already in desiredPushTypes.
 @result        Returns the push token that can be used to send pushes to the device for the specified PKPushType.
                Returns nil if no push token is available for this PKPushType at the time of invocation.
 */
- (NSData *)pushTokenForType:(NSString *)type;

/*!
 @method        initWithQueue:
 @abstract      Instantiates a PKPushRegistry with a delegate callback dispatch queue.
 @param         queue
                All delegate callbacks are performed asynchronously by PKPushRegistry on this queue.
 @result        A PKPushRegistry instance that can be used to register for push tokens and notifications for supported
                push types.
 */
- (instancetype)initWithQueue:(dispatch_queue_t)queue;

@end


@protocol PKPushRegistryDelegate <NSObject>

@required

/*!
 @method        pushRegistry:didUpdatePushCredentials:forType:
 @abstract      This method is invoked when new credentials (including push token) have been received for the specified
                PKPushType.
 @param         registry
                The PKPushRegistry instance responsible for the delegate callback.
 @param         credentials
                The push credentials that can be used to send pushes to the device for the specified PKPushType.
 @param         type
                This is a PKPushType NSString constant which is present in [registry desiredPushTypes].
 */
- (void)pushRegistry:(PKPushRegistry *)registry didUpdatePushCredentials:(PKPushCredentials *)credentials forType:(NSString *)type;

/*!
 @method        pushRegistry:didReceiveIncomingPushWithPayload:forType:
 @abstract      This method is invoked when a push notification has been received for the specified PKPushType.
 @param         registry
                The PKPushRegistry instance responsible for the delegate callback.
 @param         payload
                The push payload sent by a developer via APNS server API.
 @param         type
                This is a PKPushType NSString constant which is present in [registry desiredPushTypes].
 */
- (void)pushRegistry:(PKPushRegistry *)registry didReceiveIncomingPushWithPayload:(PKPushPayload *)payload forType:(NSString *)type;


@optional

/*!
 @method        pushRegistry:didInvalidatePushTokenForType:
 @abstract      This method is invoked if a previously provided push token is no longer valid for use. No action is
                necessary to rerequest registration. This feedback can be used to update an app's server to no longer
                send push notifications of the specified type to this device.
 @param         registry
                The PKPushRegistry instance responsible for the delegate callback.
 @param         type
                This is a PKPushType NSString constant which is present in [registry desiredPushTypes].
 */
- (void)pushRegistry:(PKPushRegistry *)registry didInvalidatePushTokenForType:(NSString *)type;

@end
