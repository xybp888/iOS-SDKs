/*	
    NSURLAuthenticationChallenge.h
    Copyright (c) 2003-2019, Apple Inc. All rights reserved.    
    
    Public header file.
*/

#import <Foundation/NSObject.h>

@class NSURLAuthenticationChallenge;
@class NSURLCredential;
@class NSURLProtectionSpace;
@class NSURLResponse;
@class NSError;

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

/// The `URLAuthenticationChallengeSender` protocol represents the interface that the sender of an authentication challenge must implement.
///
/// The methods in the protocol are generally sent by a delegate in response to receiving a ``NSURLConnectionDelegate/connection(_:didReceive:)``: or ``NSURLDownloadDelegate/download(_:didReceive:)-1pc0v``:. The different methods provide different ways of responding to authentication challenges.
///
/// > Important:
/// > This protocol is _only_ for use with the legacy ``NSURLConnection`` and ``NSURLDownload`` classes. It should not be used with ``URLSession``-based code, for which you respond to authentication challenges by passing ``URLSession/AuthChallengeDisposition`` constants to the provided completion handler blocks.
NS_SWIFT_SENDABLE
API_AVAILABLE(macos(10.2), ios(2.0), watchos(2.0), tvos(9.0))
@protocol NSURLAuthenticationChallengeSender <NSObject>

/// Attempts to use a given credential for a given authentication challenge.
///
/// This method has no effect if it is called with an authentication challenge that has already been handled.
- (void)useCredential:(NSURLCredential *)credential forAuthenticationChallenge:(NSURLAuthenticationChallenge *)challenge;

/// Attempts to continue downloading a request without providing a credential for a given challenge.
///
/// This method has no effect if it is called with an authentication challenge that has already been handled.
- (void)continueWithoutCredentialForAuthenticationChallenge:(NSURLAuthenticationChallenge *)challenge;

/// Cancels a given authentication challenge.
- (void)cancelAuthenticationChallenge:(NSURLAuthenticationChallenge *)challenge;

@optional
/// Causes the system-provided default behavior to be used.
- (void)performDefaultHandlingForAuthenticationChallenge:(NSURLAuthenticationChallenge *)challenge;

/// Rejects the currently supplied protection space.
- (void)rejectProtectionSpaceAndContinueWithChallenge:(NSURLAuthenticationChallenge *)challenge;

@end

@class NSURLAuthenticationChallengeInternal;

/// A challenge from a server requiring authentication from the client.
///
/// Your app receives authentication challenges in various ``URLSession``, ``NSURLConnection``, and ``NSURLDownload`` delegate methods, such as ``URLSessionTaskDelegate/urlSession(_:task:didReceive:completionHandler:)``. These objects provide the information you'll need when deciding how to handle a server's request for authentication.
///
/// At the core of that authentication challenge is a _protection space_ that defines the type of authentication being requested, the host and port number, the networking protocol, and (where applicable) the authentication realm (a group of related URLs on the same server that share a single set of credentials).
NS_SWIFT_SENDABLE
API_AVAILABLE(macos(10.2), ios(2.0), watchos(2.0), tvos(9.0))
@interface NSURLAuthenticationChallenge : NSObject <NSSecureCoding>
{
@private
    NSURLAuthenticationChallengeInternal *_internal;
}

/// Initializes an authentication challenge.
///
/// - Parameter space: The `NSURLProtectionSpace` to use.
/// - Parameter credential: The proposed `NSURLCredential` for this challenge, or `nil`.
/// - Parameter previousFailureCount: A count of previous failures attempting access.
/// - Parameter response: The `NSURLResponse` for the authentication failure, if applicable, else `nil`.
/// - Parameter error: The `NSError` for the authentication failure, if applicable, else `nil`.
/// - Parameter sender: The sender of this challenge.
/// - Returns: An authentication challenge initialized with the specified parameters.
- (instancetype)initWithProtectionSpace:(NSURLProtectionSpace *)space proposedCredential:(nullable NSURLCredential *)credential previousFailureCount:(NSInteger)previousFailureCount failureResponse:(nullable NSURLResponse *)response error:(nullable NSError *)error sender:(id<NSURLAuthenticationChallengeSender>)sender;

/// Initializes an authentication challenge copying all parameters from another one.
///
/// - Parameter challenge: The existing challenge to copy.
/// - Parameter sender: The sender of the challenge.
/// - Returns: A new challenge initialized with the parameters from the passed in challenge.
///
/// This initializer may be useful to subclassers that want to proxy one type of authentication challenge to look like another type.
- (instancetype)initWithAuthenticationChallenge:(NSURLAuthenticationChallenge *)challenge sender:(id<NSURLAuthenticationChallengeSender>)sender;

/// A description of the protection space that requires authentication.
@property (readonly, copy) NSURLProtectionSpace *protectionSpace;

/// The proposed credential for this challenge.
///
/// The proposed credential may be `nil`, if there is no default credential to use for this challenge (either stored
/// or in the URL). If the credential is not `nil` and returns `YES` for `hasPassword`, it is ready to use as-is.
/// If it returns `NO` for `hasPassword`, it provides a default username the client could use when prompting.
@property (nullable, readonly, copy) NSURLCredential *proposedCredential;

/// The count of previous failed authentication attempts.
@property (readonly) NSInteger previousFailureCount;

/// The response representing authentication failure.
///
/// If there was a previous authentication failure, and this protocol uses responses to indicate authentication
/// failure, then this method will return the response. Otherwise it will return `nil`.
@property (nullable, readonly, copy) NSURLResponse *failureResponse;

/// The error representing authentication failure.
///
/// If there was a previous authentication failure, and this protocol uses errors to indicate authentication
/// failure, then this method will return the error. Otherwise it will return `nil`.
@property (nullable, readonly, copy) NSError *error;

/// The sender of this challenge.
///
/// The sender is the object you should reply to when done processing the challenge.
@property (nullable, readonly, retain) id<NSURLAuthenticationChallengeSender> sender;

@end

NS_HEADER_AUDIT_END(nullability, sendability)
