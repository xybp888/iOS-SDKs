/*
 * Copyright (c) 2022 Apple Inc.
 * All rights reserved.
 */

#ifndef __NE_INDIRECT__
#error "Please import the NetworkExtension module instead of this file directly."
#endif

NS_ASSUME_NONNULL_BEGIN

/*!
 * @file NERelayManager.h
 * @discussion This file declares the NERelayManager API. The NERelayManager API is used to directly configure relay settings on the system.
 *
 * This API is part of NetworkExtension.framework.
 *
 * This API is used to configure relay settings on the system.
 */

#if defined(__cplusplus)
#define NERELAY_EXPORT extern "C"
#else
#define NERELAY_EXPORT extern
#endif

@class NERelay;
@class NEOnDemandRule;

/*!
 * @typedef NERelayManagerError
 * @abstract NERelay Manager error codes
 */
typedef NS_ENUM(NSInteger, NERelayManagerError) {
	/*! @const NERelayManagerErrorConfigurationInvalid The relay manager is invalid */
	NERelayManagerErrorConfigurationInvalid = 1,
	/*! @const NERelayManagerErrorConfigurationDisabled The relay manager is not enabled. */
	NERelayManagerErrorConfigurationDisabled = 2,
	/*! @const NERelayManagerErrorConfigurationStale The relay manager needs to be loaded. */
	NERelayManagerErrorConfigurationStale = 3,
	/*! @const NERelayManagerErrorConfigurationCannotBeRemoved The relay manager cannot be removed. */
	NERelayManagerErrorConfigurationCannotBeRemoved = 4,
} API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0)) API_UNAVAILABLE(watchos);

/*! @const NERelayErrorDomain The NERelay error domain */
NERELAY_EXPORT NSString * const NERelayErrorDomain API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0)) API_UNAVAILABLE(watchos);

/*! @const NERelayConfigurationDidChangeNotification Name of the NSNotification that is posted when the relay configuration changes. */
NERELAY_EXPORT NSString * const NERelayConfigurationDidChangeNotification API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0)) API_UNAVAILABLE(watchos);

/*!
 * @interface NERelayManager
 * @discussion The NERelayManager class declares the programmatic interface for an object that manages relay configurations.
 *
 * NERelayManager declares methods and properties for configuring and controlling relay settings on the system.
 *
 * Instances of this class are thread safe.
 */
API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0)) API_UNAVAILABLE(watchos)
@interface NERelayManager : NSObject

/*!
 * @method sharedManager
 * @return The singleton NERelayManager object for the calling process.
 */
+ (NERelayManager *)sharedManager;

/*!
 * @method loadFromPreferencesWithCompletionHandler:
 * @discussion This function loads the current relay configuration from the caller's relay preferences.
 * @param completionHandler A block that will be called when the load operation is completed. The NSError passed to this block will be nil if the load operation succeeded, non-nil otherwise.
 */
- (void)loadFromPreferencesWithCompletionHandler:(void (^)(NSError * __nullable error))completionHandler;

/*!
 * @method removeFromPreferencesWithCompletionHandler:
 * @discussion This function removes the relay configuration from the caller's relay preferences. If the relay is enabled, the relay becomes disabled.
 * @param completionHandler A block that will be called when the remove operation is completed. The NSError passed to this block will be nil if the remove operation succeeded, non-nil otherwise.
 */
- (void)removeFromPreferencesWithCompletionHandler:(void (^)(NSError * __nullable error))completionHandler;

/*!
 * @method saveToPreferencesWithCompletionHandler:
 * @discussion This function saves the relay configuration in the caller's relay preferences. If the relay are enabled, they will become active.
 * @param completionHandler A block that will be called when the save operation is completed. The NSError passed to this block will be nil if the save operation succeeded, non-nil otherwise.
 */
- (void)saveToPreferencesWithCompletionHandler:(void (^)(NSError * __nullable error))completionHandler;

/*!
 * @property localizedDescription
 * @discussion A string containing a description of the relay.
 */
@property (copy, nullable) NSString *localizedDescription;

/*!
 * @property enabled
 * @discussion Toggles the enabled status of the relay. */
@property (getter=isEnabled) BOOL enabled;

/*!
 * @property relays
 * @discussion An array of relay configurations describing one or more relay hops.
 */
@property (strong, nullable) NSArray<NERelay *> *relays;

/*!
 * @property matchDomains
 * @discussion An array of strings containing domain names. If this property is non-nil, the relay will only be used to access hosts within the specified domains. If the property is nil, the relay will be used for all domains.
 */
@property (copy, nullable) NSArray<NSString *> *matchDomains;

/*!
 * @property excludedDomains
 * @discussion An array of strings containing domain names. If the destination host name of a connection shares a suffix with one of these strings then the relay will not be used.
 */
@property (copy, nullable) NSArray<NSString *> *excludedDomains;

/*!
 * @property onDemandRules
 * @discussion An array of NEOnDemandRule objects. If nil, the associated relay will always apply. If non-nil, the array describes the networks on which the relay should be used or not.
 */
@property (copy, nullable) NSArray<NEOnDemandRule *> *onDemandRules;

/*!
 * @method loadAllManagersFromPreferencesWithCompletionHandler:
 * @discussion This function asynchronously reads all of the NERelay configurations created by the calling app that have previously been saved to disk and returns them as NERelayManager objects.
 * @param completionHandler A block that takes an array NERelayManager objects. The array passed to the block may be empty if no NERelay configurations were successfully read from the disk.  The NSError passed to this block will be nil if the load operation succeeded, non-nil otherwise.
 */
+ (void)loadAllManagersFromPreferencesWithCompletionHandler:(void (^)(NSArray<NERelayManager *> *managers, NSError * __nullable error))completionHandler;

@end

NS_ASSUME_NONNULL_END
