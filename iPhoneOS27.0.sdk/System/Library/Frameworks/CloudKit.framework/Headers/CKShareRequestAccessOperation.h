//
//  CKShareRequestAccessOperation.h
//  CloudKit
//
//  Copyright © 2025 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CloudKit/CKDatabaseOperation.h>

@class CKShare;

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

API_AVAILABLE(macos(26.0), ios(26.0), tvos(26.0), watchos(26.0), visionos(26.0))
@interface CKShareRequestAccessOperation : CKOperation

/// Creates a new, empty share request access operation.
- (instancetype)init NS_DESIGNATED_INITIALIZER;

/// Creates a share request access operation configured with specified share URLs.
///
/// - Parameter shareURLs: An array of `NSURL` objects representing the shares to request access to.
/// - Returns: A configured ``CKShareRequestAccessOperation`` instance.
- (instancetype)initWithShareURLs:(NSArray<NSURL *> *)shareURLs NS_SWIFT_NAME(init(shareURLs:));

/// The URLs of the shares to request access to.
///
/// Include multiple URLs to request access to multiple shares simultaneously. The server processes each URL independently.
@property (nullable, copy, nonatomic) NSArray<NSURL *> *shareURLs;

/// The closure to execute when CloudKit processes a share access request.
///
/// The server does not disclose share existence to protect user privacy.
///
/// This property is a closure that returns no value and has the following parameters:
///
/// - The URL of the share that was processed.
/// - An error describing why the access request failed, or `nil` if successful.
///
/// The closure executes once for each URL in the ``CKShareRequestAccessOperation/shareURLs`` property. Each time the closure executes, it executes serially with respect to the other closure of the operation.
///
/// If you intend to use this closure to process results, set it before you execute the operation or submit the operation to a queue.
@property (nullable, copy, nonatomic) void (^perShareAccessRequestCompletionBlock)(NSURL *shareURL, NSError * _Nullable shareRequestAccessError) NS_REFINED_FOR_SWIFT;

/// The closure to execute after CloudKit processes all share access requests.
///
/// This property is a closure that returns no value and has the following parameter:
///
/// - An error that contains information about a problem, or `nil` if the system successfully processes the share access requests.
///
/// The closure executes only once, and represents your final opportunity to process the operation's results. It executes after all share access request completion closures finish. The closure executes serially with respect to the other closures of the operation.
///
/// The closure reports an error of type ``CKError/Code/partialFailure`` when it processes only some of the share access requests successfully. The <doc://com.apple.documentation/documentation/foundation/nserror/userinfo> dictionary of the error contains a ``CKPartialErrorsByItemIDKey`` key that has a dictionary as its value. The keys of the dictionary are the URLs of the shares whose access requests can't be processed by the operation. The corresponding values are errors that contain information about the failures.
///
/// If you intend to use this closure to process results, set it before you execute the operation or submit the operation to a queue.
@property (nullable, copy, nonatomic) void (^shareRequestAccessCompletionBlock)(NSError * _Nullable operationError) NS_REFINED_FOR_SWIFT;

@end

NS_HEADER_AUDIT_END(nullability, sendability)
