//
//  CKFetchWebAuthTokenOperation.h
//  CloudKit
//
//  Copyright © 2014 Apple Inc. All rights reserved.
//

#import <CloudKit/CKDatabaseOperation.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

/// An operation that creates an authentication token for use with CloudKit web services.
///
/// CloudKit web services provides an HTTP interface to fetch, create, update, and delete records, zones, and subscriptions. Each request you send requires an API token, which you configure in [CloudKit Dashboard](https://icloud.developer.apple.com). You must create an API token for each container in each environment.
///
/// If you want to send a request to an endpoint that requires an authenticated user, use this operation to fetch an authentication token. Append the authentication token, along with the API token, to the endpoint's URL. That request then acts on behalf of the current user. Authentication tokens are short-lived and expire after a single use.
///
/// For an example of using a web authentication token with a CloudKit web service, see <doc:changing-access-controls-on-user-data>.
///
/// This operation executes the handlers you provide on a background queue. Tasks that need access to the main queue must redirect as appropriate.
///
/// The operation calls ``fetchWebAuthTokenCompletionBlock`` after it executes to provide the fetched token. Use the completion handler to perform housekeeping tasks for the operation. It should also manage any failures, whether due to an error or an explicit cancellation.
///
/// - Note: Because this class inherits from <doc://com.apple.documentation/documentation/foundation/operation>, you can also set the <doc://com.apple.documentation/documentation/foundation/operation/completionblock> property. The operation calls both completion handlers if they're both set.
///
/// CloudKit operations have a default QoS of <doc://com.apple.documentation/documentation/foundation/qualityofservice/default>. Operations with this service level are discretionary. The system schedules their execution at an optimal time according to battery level and network conditions, among other factors. Use the <doc://com.apple.documentation/documentation/foundation/operation/qualityofservice> property to set a more appropriate QoS for the operation.
///
/// The following example shows how to create the operation, configure its callbacks, and execute it in the user's private database:
///
/// ```swift
/// func fetchWebAuthToken(for apiToken: String,
///     completion: @escaping (Result<String, any Error>) -> Void) {
///
///     // Create the operation using the API token
///     // that the caller provides to the method.
///     let operation = CKFetchWebAuthTokenOperation(apiToken: apiToken)
///
///     // If the operation fails, return the error to the caller.
///     // Otherwise, return the fetched authentication token.
///     operation.fetchWebAuthTokenCompletionBlock = { webToken, error in
///         if let error = error {
///             completion(.failure(error))
///         } else {
///             completion(.success(webToken!))
///         }
///     }
///
///     // Set an appropriate QoS and add the operation to the
///     // private database's queue to execute it.
///     operation.qualityOfService = .utility
///     CKContainer.default().privateCloudDatabase.add(operation)
/// }
/// ```
API_AVAILABLE(macos(10.11), ios(9.2), tvos(9.1), watchos(3.0))
@interface CKFetchWebAuthTokenOperation : CKDatabaseOperation

/// Creates an empty fetch operation.
///
/// You must set ``CKFetchWebAuthTokenOperation/apiToken`` before you execute the operation or add it to a queue.
- (instancetype)init NS_DESIGNATED_INITIALIZER;

/// Creates a fetch operation for the specified API token.
///
/// - Parameters:
///   - APIToken: The API token that allows access to an app's container.
- (instancetype)initWithAPIToken:(NSString *)APIToken;

/// The API token that allows access to an app's container.
@property (nullable, copy, nonatomic) NSString *APIToken;

/// The block to execute when the operation finishes.
///
/// The closure returns no value and takes the following parameters:
///
/// - If the operation is successful, the web authentication token; otherwise, `nil`.
/// - An error that contains information about a problem, or `nil` if the system successfully fetches the token.
///
/// The operation executes this closure only once. You must provide a closure capable of executing on a background thread, so any tasks that require access to the main thread must dispatch accordingly.
@property (nullable, copy, nonatomic) void (^fetchWebAuthTokenCompletionBlock)(NSString * _Nullable webAuthToken, NSError * _Nullable operationError) CK_SWIFT_DEPRECATED("Use fetchWebAuthTokenResultBlock instead", macos(10.11, 12.0), ios(9.2, 15.0), tvos(9.1, 15.0), watchos(3.0, 8.0));

@end

NS_HEADER_AUDIT_END(nullability, sendability)
