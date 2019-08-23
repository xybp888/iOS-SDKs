// HMAccessory.h
// HomeKit
//
// Copyright (c) 2013-2015 Apple Inc. All rights reserved.

#import <Foundation/Foundation.h>
#import <HomeKit/HMDefines.h>

NS_ASSUME_NONNULL_BEGIN

@class HMHome;
@class HMRoom;
@class HMService;
@class HMCharacteristic;
@class HMAccessoryCategory;
@protocol HMAccessoryDelegate;

/*!
 * @abstract Represent an accessory in the home.
 *
 * @discussion This class represents an accessory in the home. There is a one to
 *             one relationship between a physical accessory and an object of this
 *             class. An accessory is composed of one or more services.
 */
NS_CLASS_AVAILABLE_IOS(8_0) __WATCHOS_AVAILABLE(__WATCHOS_2_0)
@interface HMAccessory : NSObject

/*!
 * @brief The name of the accessory.
 *
 * @discussion Returns the accessory's name that is associated with HomeKit. The initial value is the name
 *             provided by the accessory information service of the accessory.
 */
@property(readonly, copy, nonatomic) NSString *name;

/*!
 * @brief A unique identifier for the accessory.
 *
 * @discussion Use uniqueIdentifier to obtain the identifier for this object.
 */
@property(readonly, copy, nonatomic) NSUUID *identifier NS_DEPRECATED_IOS(8_0, 9_0) __WATCHOS_PROHIBITED;

/*!
 * @brief A unique identifier for the accessory.
 */
@property(readonly, copy, nonatomic) NSUUID *uniqueIdentifier NS_AVAILABLE_IOS(9_0);

/*!
 * @brief Delegate object that receives updates on the state of the accessory.
 */
@property(weak, nonatomic, nullable) id<HMAccessoryDelegate> delegate;

/*!
 * @brief TRUE if the accessory is currently reachable, FALSE otherwise.
 */
@property(readonly, getter=isReachable, nonatomic) BOOL reachable;

/*!
 * @brief This property indicates whether this accessory is behind a bridge. If it is TRUE,
 *        the accessory cannot be removed from the home directly. Only the bridge that owns
 *        this accessory can be removed and removing the bridge will remove this accessory
 *        from the home.
 */
@property(readonly, getter=isBridged, nonatomic) BOOL bridged;

/*!
 * @brief If this accessory is a bridge, this property is an array of NSUUID objects that,
 *        each of which represents the 'uniqueIdentifier' of the accessory vended by the bridge.
 *
 * @discussion Use uniqueIdentifiersForBridgedAccessories to obtain the identifiers for the
 *             bridged accessories.
 */
@property(readonly, copy, nonatomic, nullable) NSArray<NSUUID *> *identifiersForBridgedAccessories NS_DEPRECATED_IOS(8_0, 9_0) __WATCHOS_PROHIBITED;

/*!
 * @brief If this accessory is a bridge, this property is an array of NSUUID objects that,
 *        each of which represents the 'uniqueIdentifier' of the accessory vended by the bridge.
 *
 * @discussion An accessory can be standalone, a bridge, or hosted behind a bridge.
 *                  - A standalone accessory would have its 'bridged' property set to FALSE and
 *                    its 'uniqueIdentifiersForBridgedAccessories' property set to nil.
 *                  - An accessory that is a bridge would have its 'bridged' property set to FALSE,
 *                    but have a non-empty 'uniqueIdentifiersForBridgedAccessories' property.
 *                  - An accessory behind a bridge would have its 'bridged' property set to TRUE and
 *                    its 'uniqueIdentifiersForBridgedAccessories' property set to nil.
 */
@property(readonly, copy, nonatomic, nullable) NSArray<NSUUID *> *uniqueIdentifiersForBridgedAccessories NS_AVAILABLE_IOS(9_0);

/*!
 * @brief Category information for the accessory. 
 */
@property(readonly, strong, nonatomic) HMAccessoryCategory *category NS_AVAILABLE_IOS(9_0);

/*!
 * @brief Room containing the accessory.
 */
@property(readonly, weak, nonatomic) HMRoom *room;

/*!
 * @brief Array of HMService objects that represent all the services provided by the accessory.
 */
@property(readonly, copy, nonatomic) NSArray<HMService *> *services;

/*!
 * @brief TRUE if the accessory is blocked, FALSE otherwise.
 */

@property(readonly, getter=isBlocked, nonatomic) BOOL blocked;

/*!
 * @brief This method is used to change the name of the accessory.
 *
 * @param name New name for the accessory.
 *
 * @discussion The new name is stored in HomeKit and not on the accessory.
 *
 * @param completion Block that is invoked once the request is processed.
 *                   The NSError provides more information on the status of the request, error
 *                   will be nil on success.
 */
- (void)updateName:(NSString *)name completionHandler:(void (^)(NSError * __nullable error))completion __WATCHOS_PROHIBITED;

/*!
 * @brief This method is used to have an accessory identify itself.
 *
 * @param completion Block that is invoked once the request is processed.
 *                   The NSError provides more information on the status of the request, error
 *                   will be nil on success.
 */
- (void)identifyWithCompletionHandler:(void (^)(NSError * __nullable error))completion;

@end


/*!
 * @brief This defines the protocol for a delegate to receive updates about
 *        different aspects of an accessory
 */
NS_AVAILABLE_IOS(8_0) __WATCHOS_AVAILABLE(__WATCHOS_2_0)
@protocol HMAccessoryDelegate <NSObject>

@optional

/*!
 * @brief Informs the delegate when the name of the accessory is modified.
 *
 * @param accessory Sender of the message.
 */
- (void)accessoryDidUpdateName:(HMAccessory *)accessory;

/*!
 * @brief Informs the delegate when the name of a service is modfied.
 *
 * @param accessory Sender of the message.
 *
 * @param service Service whose name was modified.
 */
- (void)accessory:(HMAccessory *)accessory didUpdateNameForService:(HMService *)service;

/*!
 * @brief Informs the delegate when the associated service type of a service is modified.
 *
 * @param accessory Sender of the message.
 *
 * @param service Service whose associated service type was modified.
 */
- (void)accessory:(HMAccessory *)accessory didUpdateAssociatedServiceTypeForService:(HMService *)service;

/*!
 * @brief Informs the delegate when the services on the accessory have been dynamically updated.
 *        The services discovered are accessible via the 'services' property of the accessory.
 *
 * @param accessory Sender of the message.
 */
- (void)accessoryDidUpdateServices:(HMAccessory *)accessory;

/*!
 * @brief Informs the delegate when the reachability of the accessory changes.
 *
 * @param accessory Sender of the message.
 */
- (void)accessoryDidUpdateReachability:(HMAccessory *)accessory;

/*!
 * @brief Informs the delegate of a change in value of a characteristic. 
 *
 * @param accessory Sender of this messqage
 *
 * @param service HMService that contains the characteristic whose value was modified.
 *
 * @param characteristic The characteristic whose value was changed.
 */
- (void)accessory:(HMAccessory *)accessory service:(HMService *)service didUpdateValueForCharacteristic:(HMCharacteristic *)characteristic;

@end

NS_ASSUME_NONNULL_END
