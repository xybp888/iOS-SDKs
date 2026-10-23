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

/// A class that supports safely sharing Thread credentials between multiple
/// clients.
///
/// Request credentials for either a specific Thread network or for the
/// _preferred network_ using `THClient`. The preferred network is the default
/// Thread network chosen by the framework for a home.
///
/// The ThreadNetwork framework maintains a database of network credentials. The
/// class allows clients to store, list, and delete credentials for a given
/// network from the database.
///
/// Some methods in `THClient` use the _team ID_, a string that you store in
/// your application’s `Info.plist`. The ThreadNetwork framework uses the team
/// ID to preserve the privacy of the Thread network credentials across
/// different clients. For example, credentials stored by one client can’t be
/// deleted or modified by another client.
///
/// - Important: Thread credentials give you the ability to add any device into
///   the Thread network. Use this information responsibly.
@interface THClient : NSObject

/// Creates the client object.
///
/// - Returns: An instance of the client object.
- (instancetype)init API_AVAILABLE(ios(15.0));

/// Requests all Thread credentials from the framework.
///
/// The framework identifies the developer by the team ID. When calling this
/// method, you receive credentials for your team ID only.
///
/// - Parameters:
///   - completion: The completion handler the framework calls when the
///     credentials become available.
///
/// > Concurrency Note: You can call this method from synchronous code using a completion handler,
/// > as shown on this page, or you can call it as an asynchronous method that has the
/// > following declaration:
/// >
/// > ```swift
/// > func allCredentials() async throws -> Set<THCredentials>
/// > ```
/// >
/// > For information about concurrency and asynchronous code in Swift, see <doc://com.apple.documentation/documentation/swift/calling-objective-c-apis-asynchronously>.
- (void)retrieveAllCredentials:(void (^)(NSSet<THCredentials*>* _Nullable credentials, NSError* _Nullable error))completion API_AVAILABLE(ios(15.0)) NS_SWIFT_ASYNC_NAME(allCredentials());

/// Requests all Thread credentials with active border routers around from the framework.
///
/// The framework identifies the developer by the team ID. When calling this
/// method, you will receive credentials for active border routers around.
/// You receive credentials for your team ID only.
///
/// - Parameters:
///   - completion: The completion handler the framework calls when the
///     credentials become available.
///
/// > Concurrency Note: You can call this method from synchronous code using a completion handler,
/// > as shown on this page, or you can call it as an asynchronous method that has the
/// > following declaration:
/// >
/// > ```swift
/// > func allActiveCredentials() async throws -> Set<THCredentials>
/// > ```
/// >
/// > For information about concurrency and asynchronous code in Swift, see <doc://com.apple.documentation/documentation/swift/calling-objective-c-apis-asynchronously>.
- (void)retrieveAllActiveCredentials:(void (^)(NSSet<THCredentials*>* _Nullable credentials, NSError* _Nullable error))completion API_AVAILABLE(ios(16.4)) NS_SWIFT_ASYNC_NAME(allActiveCredentials());

/// Requests all active Thread credentials with active border routers around from the framework.
///
/// When calling this method, you will receive credentials for active border routers around.
/// You receive all credentials agnostic to team ID.
/// Unlike ``retrieveAllActiveCredentials:``, this method returns active credentials
/// on the device regardless of who actually stored it.
///
/// - Parameters:
///   - completion: The completion handler the framework calls when the
///     credentials become available.
///
/// - Note: This method asks for user permission to share available credentials.
///         If user denies the permission then the completion will contain error with code 15.
///
/// > Concurrency Note: You can call this method from synchronous code using a completion handler,
/// > as shown on this page, or you can call it as an asynchronous method that has the
/// > following declaration:
/// >
/// > ```swift
/// > var activeCredentialsForNearbyNetworks: Set<THCredentials> { get async throws }
/// > ```
/// >
/// > For information about concurrency and asynchronous code in Swift, see <doc://com.apple.documentation/documentation/swift/calling-objective-c-apis-asynchronously>.
- (void)retrieveActiveCredentialsForNearbyNetworksWithCompletion:(void (^)(NSSet<THCredentials*>* _Nullable credentials, NSError* _Nullable error))completion API_AVAILABLE(ios(27.0)) NS_SWIFT_ASYNC_NAME(getter:activeCredentialsForNearbyNetworks());

/// Deletes Thread network credentials from the framework database for a Border
/// Agent.
///
/// The Border Agent is the software component running in the Border Router
/// responsible for advertising itself in the Wi-Fi or Ethernet network.
///
/// - Parameters:
///   - borderAgentID: The identifer of a Thread network Border Agent.
///   - completion: The completion handler the framework calls after deleting
///     the credentials.
///
/// > Concurrency Note: You can call this method from synchronous code using a completion handler,
/// > as shown on this page, or you can call it as an asynchronous method that has the
/// > following declaration:
/// >
/// > ```swift
/// > func deleteCredentials(forBorderAgent borderAgentID: Data) async throws
/// > ```
/// >
/// > For information about concurrency and asynchronous code in Swift, see <doc://com.apple.documentation/documentation/swift/calling-objective-c-apis-asynchronously>.
- (void)deleteCredentialsForBorderAgent:(NSData *)borderAgentID completion:(void (^)(NSError* _Nullable error))completion API_AVAILABLE(ios(15.0));

/// Requests Thread credentials for a Border Agent.
///
/// The framework identifies the developer by the team ID. When calling this
/// method, you receive credentials for your team ID only.
///
/// - Parameters:
///   - borderAgentID: The identifer of a Thread network Border Agent.
///   - completion: The completion handler the framework calls when the
///     credentials become available.
///
/// > Concurrency Note: You can call this method from synchronous code using a completion handler,
/// > as shown on this page, or you can call it as an asynchronous method that has the
/// > following declaration:
/// >
/// > ```swift
/// > func credentials(forBorderAgentID borderAgentID: Data) async throws -> THCredentials
/// > ```
/// >
/// > For information about concurrency and asynchronous code in Swift, see <doc://com.apple.documentation/documentation/swift/calling-objective-c-apis-asynchronously>.
- (void)retrieveCredentialsForBorderAgent:(NSData *)borderAgentID completion:( void (^)(THCredentials* _Nullable credentials, NSError* _Nullable error))completion API_AVAILABLE(ios(15.0)) NS_SWIFT_ASYNC_NAME(credentials(forBorderAgentID:));

/// Stores Thread network credentials into the framework database
/// that a Border Agent provides.
///
/// The Border Agent is the software component running in the
/// Border Router responsible for advertising itself in the Wi-Fi
/// or Ethernet network.
///
/// The framework only stores credentials if it can find an mDNS
/// record for the Border Agent that contains the specified Border
/// Agent identifier.
///
/// - Parameters:
///   - borderAgentID: The identifer of an active Thread network Border Agent.
///   - activeOperationalDataSet: The essential operational parameters for the
///     Thread network.
///   - completion: The completion handler the framework calls after
/// storing the credentials.
///
/// > Concurrency Note: You can call this method from synchronous code using a completion handler,
/// > as shown on this page, or you can call it as an asynchronous method that has the
/// > following declaration:
/// >
/// > ```swift
/// > func storeCredentials(forBorderAgent borderAgentID: Data, activeOperationalDataSet: Data) async throws
/// > ```
/// >
/// > For information about concurrency and asynchronous code in Swift, see <doc://com.apple.documentation/documentation/swift/calling-objective-c-apis-asynchronously>.
- (void)storeCredentialsForBorderAgent:(NSData *)borderAgentID
              activeOperationalDataSet:(NSData *)activeOperationalDataSet
                            completion:(void (^)(NSError* _Nullable error))completion API_AVAILABLE(ios(15.0));

/// Requests Thread credentials for the preferred network.
///
/// When you call this method, an alert appears asking for user permission to
/// access credentials.
///
/// - Parameters:
///   - completion: The completion handler the framework calls when the
///     credentials become available.
///
/// > Concurrency Note: You can call this method from synchronous code using a completion handler,
/// > as shown on this page, or you can call it as an asynchronous method that has the
/// > following declaration:
/// >
/// > ```swift
/// > func preferredCredentials() async throws -> THCredentials
/// > ```
/// >
/// > For information about concurrency and asynchronous code in Swift, see <doc://com.apple.documentation/documentation/swift/calling-objective-c-apis-asynchronously>.
- (void)retrievePreferredCredentials:(void (^)(THCredentials* _Nullable credentials, NSError* _Nullable error))completion API_AVAILABLE(ios(15.0)) NS_SWIFT_ASYNC_NAME(preferredCredentials());

/// Requests Thread credentials for an extended Personal Area Network (PAN) ID.
///
/// When calling this method, an alert appears asking for user permission to
/// access credentials.
///
/// - Parameters:
///   - extendedPANID: The extended PAN identifier.
///   - completion: The completion handler the framework calls when the
///     credentials become available.
///
/// > Concurrency Note: You can call this method from synchronous code using a completion handler,
/// > as shown on this page, or you can call it as an asynchronous method that has the
/// > following declaration:
/// >
/// > ```swift
/// > func credentials(forExtendedPANID extendedPANID: Data) async throws -> THCredentials
/// > ```
/// >
/// > For information about concurrency and asynchronous code in Swift, see <doc://com.apple.documentation/documentation/swift/calling-objective-c-apis-asynchronously>.
- (void)retrieveCredentialsForExtendedPANID:(NSData *)extendedPANID completion:( void (^)(THCredentials* _Nullable credentials, NSError* _Nullable error))completion API_AVAILABLE(ios(15.0)) NS_SWIFT_ASYNC_NAME(credentials(forExtendedPANID:));

/// Determines if the essential operating parameters match the preferred
/// network’s parameters.
///
/// - Parameters:
///   - activeOperationalDataSet: The essential operating parameters to compare
///     against the preferred network’s parameters.
///   - completion: The completion handler that returns the result of the
///     comparison.
///
/// > Concurrency Note: You can call this method from synchronous code using a completion handler,
/// > as shown on this page, or you can call it as an asynchronous method that has the
/// > following declaration:
/// >
/// > ```swift
/// > func isPreferred(forActiveOperationalDataset activeOperationalDataSet: Data) async -> Bool
/// > ```
/// >
/// > For information about concurrency and asynchronous code in Swift, see <doc://com.apple.documentation/documentation/swift/calling-objective-c-apis-asynchronously>.
- (void)checkPreferredNetworkForActiveOperationalDataset:(NSData *)activeOperationalDataSet
                                           completion:(void (^)(BOOL isPreferred))completion API_AVAILABLE(ios(15.5))   NS_SWIFT_ASYNC_NAME(isPreferred(forActiveOperationalDataset:));

/// Determines if the preferred network is available or not
///
/// - Parameters:
///   - completion: The completion handler that returns the result of the
///     preferred network availability.
///
/// > Concurrency Note: You can call this method from synchronous code using a completion handler,
/// > as shown on this page, or you can call it as an asynchronous method that has the
/// > following declaration:
/// >
/// > ```swift
/// > func isPreferredAvailable() async -> Bool
/// > ```
/// >
/// > For information about concurrency and asynchronous code in Swift, see <doc://com.apple.documentation/documentation/swift/calling-objective-c-apis-asynchronously>.
- (void)isPreferredNetworkAvailableWithCompletion:(void (^)(BOOL isPreferredAvailable))completion API_AVAILABLE(ios(16.4))   NS_SWIFT_ASYNC_NAME(isPreferredAvailable());

/// Triggers Credential Share mode on a nearby eligible Apple Border Router (tvOS(27.0)).
///
/// This method scans for Thread credential sharing capable Apple Border Routers, selects an eligible device, and requests to generate an ephemeral 9-digit code and start credential sharing mode.
///
/// When you call this method, the ephemeral 9-digit code appears on screen along with a warning message; it is not returned to the caller.
///
/// - Parameters:
///   - extendedPANID: The extended PAN identifier of the Thread network.
///   - completion: The completion handler the framework calls once credential
///     sharing mode has started. The `error` parameter is nil on success, or
///     non-nil if credential sharing mode could not be enabled.
///
/// > Concurrency Note: You can call this method from synchronous code using a completion handler,
/// > as shown on this page, or you can call it as an asynchronous method that has the
/// > following declarations:
/// >
/// > ```swift
/// > // Completion handler form:
/// > func enableCredentialSharingMode(forExtendedPANID extendedPANID: Data, completion: @escaping (Error?) -> Void)
/// >
/// > // Async form (throws on failure):
/// > func enableCredentialSharingMode(forExtendedPANID extendedPANID: Data) async throws
/// > ```
/// > For information about concurrency and asynchronous code in Swift, see <doc://com.apple.documentation/documentation/swift/calling-objective-c-apis-asynchronously>.
- (void)enableCredentialSharingModeForExtendedPANID:(nonnull NSData*)extendedPANID completion:(void (^)(NSError * _Nullable error))completion API_AVAILABLE(ios(27.0)) NS_SWIFT_ASYNC_NAME(enableCredentialSharingMode(forExtendedPANID:));
@end

NS_ASSUME_NONNULL_END
