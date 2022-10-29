//
//  THClient.h
//  ThreadNetwork
//
//  Copyright © 2020 Apple. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <ThreadNetwork/THCredentials.h>

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(15.0))

@interface THClient : NSObject

/*
 * @function init
 *
 * @discussion
 * Initialize instance of THClient
 *
 * @parameter
 * no parameters
 */

- (instancetype)init API_AVAILABLE(ios(15.0));

/*
 * @function retrieveAllCredentials
 *
 * @discussion
 * Retrieve All Credentials, stored by the client
 *
 * @parameter
 * completion : Callback function to receive all credentials
 *
 */
- (void)retrieveAllCredentials:(void (^)(NSSet<THCredentials*>* _Nullable credentials, NSError* _Nullable error))completion API_AVAILABLE(ios(15.0)) API_UNAVAILABLE(macos, macCatalyst) NS_SWIFT_ASYNC_NAME(allCredentials());

/*
 * @function deleteActiveDataSetRecordForBorderAgent
 *
 * @discussion
 * Delete Credentials For The given Border Agent identifier, stored by the client
 *
 * @parameter
 * borderAgentID : Thread Network Border Agent Identifier
 * @parameter
 * completion : Callback function to return the status of the delete operation
 *
 */
- (void)deleteCredentialsForBorderAgent:(NSData *)borderAgentID completion:(void (^)(NSError* _Nullable error))completion API_AVAILABLE(ios(15.0)) API_UNAVAILABLE(macos, macCatalyst);

/*
 * @function retrieveCredentialsForBorderAgent
 *
 * @discussion
 * Retrieve Credentials For The given Thread Border Agent identifier, stored by the client
 *
 * @parameter
 * completion : Callback function to receive the matching active dataset record
 *
 */
- (void)retrieveCredentialsForBorderAgent:(NSData *)borderAgentID completion:( void (^)(THCredentials* _Nullable credentials, NSError* _Nullable error))completion API_AVAILABLE(ios(15.0)) API_UNAVAILABLE(macos, macCatalyst) NS_SWIFT_ASYNC_NAME(credentials(forBorderAgentID:));

/*
 * @function storeCredentialsForBorderAgent
 *
 * @discussion
 * Store the Credentials Record
 *
 * @parameters
 * borderAgent              : Border Agent Identifier
 * activeOperationalDataSet : byte array of active operational dataset
 * completion               : Callback function to return the status of the store operation
 *
 */

- (void)storeCredentialsForBorderAgent:(NSData *)borderAgentID
              activeOperationalDataSet:(NSData *)activeOperationalDataSet
                            completion:(void (^)(NSError* _Nullable error))completion API_AVAILABLE(ios(15.0)) API_UNAVAILABLE(macos, macCatalyst);

/*
 * @function retrievePreferredCredentials
 *
 * @discussion
 * Retrieve Preferred Thread Network Credentials.
 * Invoking this API will result into UI Alert prompt seeking user's permission to access the credentials
 *
 * @parameter
 * completion : Callback function to receive preferred network active dataset record
 *
 */
- (void)retrievePreferredCredentials:(void (^)(THCredentials* _Nullable credentials, NSError* _Nullable error))completion API_AVAILABLE(ios(15.0)) API_UNAVAILABLE(macos, macCatalyst) NS_SWIFT_ASYNC_NAME(preferredCredentials());

/*
 * @function retrieveActiveDataSetRecordForExtendedPANID
 *
 * @discussion
 * Retrieve Credentials For The given Extended-PAN Id
 * Invoking this API will result into UI Alert prompt seeking user's permission to access the credentials
 *
 * @parameter
 * extendedPANID    : Extended PAN Id identifying the thread network
 * completion       : Callback function to receive the matching active dataset record
 *
 */
- (void)retrieveCredentialsForExtendedPANID:(NSData *)extendedPANID completion:( void (^)(THCredentials* _Nullable credentials, NSError* _Nullable error))completion API_AVAILABLE(ios(15.0)) API_UNAVAILABLE(macos, macCatalyst) NS_SWIFT_ASYNC_NAME(credentials(forExtendedPANID:));
/*
 * @function checkPreferredNetworkForActiveOperationalDataset
 *
 * @discussion
 * Returns true if the dataset matches to the preferred network
 *
 * @parameters
 * activeOperationalDataSet : byte array of active operational dataset
 * completion               : Callback function gives true if dataset matches to preferred network, else false
 *
 */

- (void)checkPreferredNetworkForActiveOperationalDataset:(NSData *)activeOperationalDataSet
                                           completion:(void (^)(BOOL isPreferred))completion API_AVAILABLE(ios(15.0)) API_UNAVAILABLE(macos, macCatalyst) NS_SWIFT_ASYNC_NAME(isPreferred(forActiveOperationalDataset:));
@end

NS_ASSUME_NONNULL_END
