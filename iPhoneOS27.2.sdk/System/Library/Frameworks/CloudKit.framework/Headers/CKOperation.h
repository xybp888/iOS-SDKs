//
//  CKOperation.h
//  CloudKit
//
//  Copyright (c) 2014 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

#import <CloudKit/CKDefines.h>

@class CKContainer, CKOperationConfiguration, CKOperationGroup;

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

/// A type that represents the ID of an operation.
typedef NSString *CKOperationID;

/// The abstract base class for all operations that execute in a database.
///
/// All CloudKit operations descend from `CKOperation`, which provides the infrastructure for executing tasks in one of your app's containers. Don't subclass or create instances of this class directly. Instead, create instances of one of its concrete subclasses.
///
/// Use the properties of this class to configure the behavior of the operation before submitting it to a queue or executing it directly. CloudKit operations involve communicating with the iCloud servers to send and receive data. You can use the properties of this class to configure the behavior of those network requests to ensure the best performance for your app.
///
/// - Important: `CKOperation` objects have a default quality of service level of <doc://com.apple.documentation/documentation/foundation/qualityofservice/default> (see <doc://com.apple.documentation/documentation/foundation/operation/qualityofservice>). Operations with this service level are discretionary, and the system schedules them for an optimal time according to battery level and other factors. On iPhone, discretionary activities pause when the device is in Low Power Mode. For information about quality of service levels, see [Prioritize Work with Quality of Service Classes](https://developer.apple.com/library/archive/documentation/Performance/Conceptual/EnergyGuide-iOS/PrioritizeWorkWithQoS.html#//apple_ref/doc/uid/TP40015243-CH39) in [Energy Efficiency Guide for iOS Apps](https://developer.apple.com/library/archive/documentation/Performance/Conceptual/EnergyGuide-iOS/index.html#//apple_ref/doc/uid/TP40015243) and [Prioritize Work at the Task Level](https://developer.apple.com/library/archive/documentation/Performance/Conceptual/power_efficiency_guidelines_osx/PrioritizeWorkAtTheTaskLevel.html#//apple_ref/doc/uid/TP40013929-CH35) in [Energy Efficiency Guide for Mac Apps](https://developer.apple.com/library/archive/documentation/Performance/Conceptual/power_efficiency_guidelines_osx/index.html#//apple_ref/doc/uid/TP40013929).
///
/// ### Long-Lived Operations
///
/// A _long-lived operation_ is an operation that continues to run after the user closes the app. To specify a long-lived operation, set ``isLongLived`` to <doc://com.apple.documentation/documentation/swift/true>, provide a completion handler, and execute the operation. To get the identifiers of all running long-lived operations, use the ``CKContainer/allLongLivedOperationIDs()`` method that ``CKContainer`` provides. To get a specific long-lived operation, use the ``CKContainer/longLivedOperation(for:)`` method. Make sure you set the completion handler of a long-lived operation before you execute it so that the system can notify you when it completes and you can process the results. Do not execute an operation, change it to long-lived, and execute it again as a long-lived operation.
///
/// @TabNavigator {
///     @Tab("Swift") {
///         ```swift
///         container.fetchAllLongLivedOperationIDs(completionHandler: { (operationIDs, error) in
///             if let error = error {
///                 print("Error fetching long lived operations: \(error)")
///                 // Handle error
///                 return
///             }
///             guard let identifiers = operationIDs else { return }
///             for operationID in identifiers {
///                 container.fetchLongLivedOperation(withID: operationID, completionHandler: { (operation, error) in
///                     if let error = error {
///                         print("Error fetching operation: \(operationID)\n\(error)")
///                         // Handle error
///                         return
///                     }
///                     guard let operation = operation else { return }
///                     // Add callback handlers to operation
///                     container.add(operation)
///                 })
///             }
///         })
///         ```
///     }
///     @Tab("Objective-C") {
///         ```objc
///         [container fetchAllLongLivedOperationIDsWithCompletionHandler:^(NSArray<NSString *> *_Nullable operationIDs, NSError *_Nullable error) {
///             if (error) {
///                 // Handle error
///                 return
///             }
///             for (NSString *operationID in operationIDs) {
///                 [container fetchLongLivedOperationWithID:operationID completionHandler:^(CKOperation *_Nullable operation, NSError *_Nullable error) {
///                     if (error) {
///                         // Handle error
///                         return
///                     }
///                     // Add callback handlers to operation
///                     [container addOperation:operation];
///                 }];
///             }
///         }];
///         ```
///     }
/// }
///
/// The following is the typical life cycle of a long-lived operation:
///
/// 1. The app creates a long-lived operation and executes it.
///    The daemon starts saving and sending the callbacks to the running app.
/// 2. The app exits.
///    The daemon continues running the long-lived operation and saves the callbacks.
/// 3. The app launches and fetches the long-lived operation.
///    If the operation is running or if it completed within the previous 24 hours, the daemon returns a proxy for the long-lived operation. If the operation completed more than 24 hours previously, the daemon may stop returning it in fetch requests.
/// 4. The app runs the long-lived operation again.
///    The daemon sends the app all the saved callbacks (it doesn't actually rerun the operation), and continues saving the callbacks and sending them to the running app.
/// 5. The app receives the completion callback or the app cancels the operation.
///    The daemon stops including the operation in future fetch results.
API_AVAILABLE(macos(10.10), ios(8.0), watchos(3.0))
@interface CKOperation : NSOperation

/// Creates an operation.
///
/// - Important: Don't use this method directly. Instead, create database operations using the initializers of the concrete subclasses.
- (instancetype)init NS_DESIGNATED_INITIALIZER;

/// The operation's configuration.
@property (null_resettable, copy, nonatomic) CKOperationConfiguration *configuration API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0), watchos(4.0));

/// The operation's group.
@property (nullable, strong, nonatomic) CKOperationGroup *group API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0), watchos(4.0));

/// A unique identifier for a long-lived operation.
///
/// Pass this property's value to the ``CKContainer/longLivedOperation(for:)`` method to fetch the corresponding long-lived operation. For more information, see <doc:CKOperation#Long-Lived-Operations>.
@property (readonly, copy, nonatomic) CKOperationID operationID API_AVAILABLE(macos(10.12), ios(9.3), tvos(9.2), watchos(3.0));

/// The closure to execute when the server begins to store callbacks for the long-lived operation.
///
/// If your app exits before CloudKit calls this property's value, the system doesn't include the operation's ID in the results of calls to the ``CKContainer/allLongLivedOperationIDs()`` method.
///
/// For more information, see <doc:CKOperation#Long-Lived-Operations>.
@property (nullable, copy, nonatomic) void (^longLivedOperationWasPersistedBlock)(void) API_AVAILABLE(macos(10.12), ios(9.3), tvos(9.2), watchos(3.0));

@end

/// An object that describes how a CloudKit operation behaves.
///
/// All of the properties in `CKOperationConfiguration` have a default value. When determining which properties to apply to a CloudKit operation, consult the operation's configuration property, as well as the ``CKOperationGroup/defaultConfiguration`` property of the group that the operation belongs to. These properties combine through the following rules:
///
/// | Group default configuration value | Operation configuration value | Value applied to operation |
/// |---|---|---|
/// | default value | default value | default value |
/// | default value | explicit value | operation.configuration explicit value |
/// | explicit value | default value | group.defaultConfiguration explicit value |
/// | explicit value | explicit value | operation.configuration explicit value |
API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0), watchos(4.0))
CK_SUBCLASSING_DEPRECATED // should not be subclassed, or Sendable may no longer apply
// NS_SWIFT_SENDABLE on macos(13.3), macCatalyst(16.4), ios(16.4), tvos(16.4), watchos(9.4)
@interface CKOperationConfiguration : NSObject

/// The configuration's container.
///
/// If you don't provide a container, CloudKit uses the default container that ``CKContainer`` provides.
@property (nullable, strong) CKContainer *container;

/// The priority that the system uses when it allocates resources to the operations that use this configuration.
@property (assign) NSQualityOfService qualityOfService;

/// A Boolean value that indicates whether operations that use this configuration can send data over the cellular network.
@property (assign) BOOL allowsCellularAccess;

/// A Boolean value that indicates whether the operations that use this configuration are long-lived.
@property (assign, getter=isLongLived) BOOL longLived;

/// The maximum amount of time that a request can take.
///
/// - SeeAlso: `NSURLSessionConfiguration.timeoutIntervalForRequest`
@property (assign) NSTimeInterval timeoutIntervalForRequest;

/// The maximum amount of time that a resource request can take.
///
/// - SeeAlso: `NSURLSessionConfiguration.timeoutIntervalForResource`
@property (assign) NSTimeInterval timeoutIntervalForResource;

@end

#pragma mark - Deprecated CKOperation

// These deprecated properties now read and write from the CKOperation's configuration
@interface CKOperation (CKOperationDeprecated)

/// The operation's container.
///
/// @DeprecationSummary {
///     Use ``CKOperation/Configuration/container`` instead.
/// }
///
/// The container defines where the operation executes. The ``CKContainer/add(_:)`` method of the ``CKContainer`` and ``CKDatabase`` classes implicitly set this property to their container.
///
/// If you execute the operation yourself, either directly or using a custom operation queue, set the value of this property explicitly. If the value is `nil` when you execute an operation, the operation implicitly executes in your app's default container.
@property (nullable, strong, nonatomic) CKContainer *container          API_DEPRECATED("Use CKOperationConfiguration", macos(10.10, 10.13), ios(8.0, 11.0), tvos(9.0, 11.0), watchos(3.0, 4.0));

/// A Boolean value that indicates whether the operation can send data over the cellular network.
///
/// @DeprecationSummary {
///     Use ``CKOperation/Configuration/allowsCellularAccess`` instead.
/// }
/// 
/// When you send or receive many records, or when you send records with large assets, you might set this property to <doc://com.apple.documentation/documentation/swift/false> to avoid consuming too much of the user's cellular data bandwidth. The default value is <doc://com.apple.documentation/documentation/swift/true>.
///
/// When this property is <doc://com.apple.documentation/documentation/swift/false>, the operation fails if Wi-Fi isn't available.
@property (assign, nonatomic) BOOL allowsCellularAccess                 API_DEPRECATED("Use CKOperationConfiguration", macos(10.10, 10.13), ios(8.0, 11.0), tvos(9.0, 11.0), watchos(3.0, 4.0));

/// A Boolean value that indicates whether the operation is long-lived.
///
/// @DeprecationSummary {
///     Use ``CKOperation/Configuration/isLongLived`` instead.
/// }
/// 
/// Set this property to <doc://com.apple.documentation/documentation/swift/true> to make the operation long-lived. The default value is <doc://com.apple.documentation/documentation/swift/false>. If you change this property's value after you execute the operation, the change has no effect.
///
/// For more information, see <doc:CKOperation#Long-Lived-Operations>.
@property (assign, nonatomic, getter=isLongLived) BOOL longLived        API_DEPRECATED("Use CKOperationConfiguration", macos(10.12, 10.13), ios(9.3, 11.0), tvos(9.2, 11.0), watchos(3.0, 4.0));

/// The timeout interval when waiting for additional data.
///
/// @DeprecationSummary {
///     Use ``CKOperation/Configuration/timeoutIntervalForRequest`` instead.
/// }
/// 
/// This property determines the request timeout interval for the operation, which controls how long, in seconds, the operation waits for additional data to arrive before stopping. The timer for this value resets whenever new data arrives. When the timer reaches the interval without receiving any new data, it triggers a timeout.
///
/// The default value is `60`.
@property (assign, nonatomic) NSTimeInterval timeoutIntervalForRequest  API_DEPRECATED("Use CKOperationConfiguration", macos(10.12, 10.13), ios(10.0, 11.0), tvos(10.0, 11.0), watchos(3.0, 4.0));

/// The maximum amount of time that a resource request can use.
///
/// @DeprecationSummary {
///     Use ``CKOperation/Configuration/timeoutIntervalForResource`` instead.
/// }
/// 
/// This property determines the resource timeout interval for this operation, which controls how long, in seconds, to wait for the entire operation to complete before stopping. The resource timer starts when the operation executes and counts until either the operation completes or this timeout interval occurs, whichever comes first.
///
/// The default value is `604800`, the number of seconds in 7 days.
@property (assign, nonatomic) NSTimeInterval timeoutIntervalForResource API_DEPRECATED("Use CKOperationConfiguration", macos(10.12, 10.13), ios(10.0, 11.0), tvos(10.0, 11.0), watchos(3.0, 4.0));
@end

NS_HEADER_AUDIT_END(nullability, sendability)
