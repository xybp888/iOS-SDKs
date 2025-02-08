//
//  ASCredentialProviderExtensionContext.h
//  AuthenticationServices Framework
//
//  Copyright © 2018 Apple Inc. All rights reserved.
//

#import <AuthenticationServices/ASExtensionErrors.h>
#import <AuthenticationServices/ASFoundation.h>
#import <Foundation/Foundation.h>

@class ASOneTimeCodeCredential;

@class ASPasskeyAssertionCredential;
@class ASPasskeyRegistrationCredential;

@class ASPasswordCredential;

NS_ASSUME_NONNULL_BEGIN

AS_EXTERN API_AVAILABLE(ios(12.0), macCatalyst(14.0), macos(11.0)) API_UNAVAILABLE(tvos, watchos)
@interface ASCredentialProviderExtensionContext : NSExtensionContext

/*! @abstract Complete the request by providing the user selected credential.
 @param credential the credential that the user has selected.
 @param completionHandler optionally contains any work which the extension may need to perform after the request has been completed,
 as a background-priority task. The `expired` parameter will be YES if the system decides to prematurely terminate a previous
 non-expiration invocation of the completionHandler.
 @discussion Calling this method will eventually dismiss the associated view controller.
 */
- (void)completeRequestWithSelectedCredential:(ASPasswordCredential *)credential completionHandler:(void(^ _Nullable)(BOOL expired))completionHandler
    NS_SWIFT_DISABLE_ASYNC
    ;

/*! @abstract Complete the assertion request by providing the user selected passkey credential.
 @param credential the credential that the user has selected. Includes assertion response.
 @param completionHandler optionally contains any work which the extension may need to perform after the request has been completed,
 as a background-priority task. The `expired` parameter will be YES if the system decides to prematurely terminate a previous
 non-expiration invocation of the completionHandler.
 @discussion Calling this method will eventually dismiss the associated view controller.
 */
- (void)completeAssertionRequestWithSelectedPasskeyCredential:(ASPasskeyAssertionCredential *)credential completionHandler:(void(^ _Nullable)(BOOL expired))completionHandler NS_SWIFT_NAME(completeAssertionRequest(using:completionHandler:)) API_AVAILABLE(ios(17.0), macos(14.0)) API_UNAVAILABLE(watchos, tvos);

/*! @abstract Complete the registration request by providing the newly created passkey credential.
 @param credential the credential that was created in response to the registration request.
 @param completionHandler optionally contains any work which the extension may need to perform after the request has been completed,
 as a background-priority task. The `expired` parameter will be YES if the system decides to prematurely terminate a previous
 non-expiration invocation of the completionHandler.
 @discussion Calling this method will eventually dismiss the associated view controller.
 */
- (void)completeRegistrationRequestWithSelectedPasskeyCredential:(ASPasskeyRegistrationCredential *)credential completionHandler:(void(^ _Nullable)(BOOL expired))completionHandler API_AVAILABLE(ios(17.0), macos(14.0)) NS_SWIFT_NAME(completeRegistrationRequest(using:completionHandler:)) API_UNAVAILABLE(watchos, tvos);

/*! @abstract Complete the request by providing the user selected one time code credential.
 @param credential the credential that the user has selected.
 @param completionHandler optionally contains any work which the extension may need to perform after the request has been completed,
 as a background-priority task. The `expired` parameter will be YES if the system decides to prematurely terminate a previous
 non-expiration invocation of the completionHandler.
 @discussion Calling this method will eventually dismiss the associated view controller.
 */
- (void)completeOneTimeCodeRequestWithSelectedCredential:(ASOneTimeCodeCredential *)credential completionHandler:(void(^ _Nullable)(BOOL expired))completionHandler NS_SWIFT_NAME(completeOneTimeCodeRequest(using:completionHandler:)) API_AVAILABLE(ios(18.0), macos(15.0), visionos(2.0)) API_UNAVAILABLE(watchos, tvos);

/*! @abstract Complete the request by providing the user selected text.
 @param text The string that the user has selected.
 @param completionHandler Optionally contains any work which the extension may need to perform after the request has been completed,
 as a background-priority task. The `expired` parameter will be YES if the system decides to prematurely terminate a previous
 non-expiration invocation of the completionHandler.
 @discussion Calling this method will eventually dismiss the associated view controller.
 */
- (void)completeRequestWithTextToInsert:(NSString *)text completionHandler:(void(^ _Nullable)(BOOL expired))completionHandler NS_SWIFT_NAME(completeRequest(withTextToInsert:completionHandler:)) API_AVAILABLE(ios(18.0)) API_UNAVAILABLE(macos, macCatalyst, visionos, watchos, tvos);

/*! @abstract Complete the request to configure the extension.
 @discussion Calling this method will eventually dismiss the associated view controller.
 */
- (void)completeExtensionConfigurationRequest;

- (void)completeRequestReturningItems:(nullable NSArray *)items completionHandler:(void (^ _Nullable)(BOOL))completionHandler NS_UNAVAILABLE;

/*! @abstract Cancels the request.
 @param error error's domain should be ASExtensionErrorDomain and the code should be a value of type ASExtensionErrorCode.
 @discussion The extension should call this method when the user cancels the action or a failure occurs.
 */
- (void)cancelRequestWithError:(NSError *)error;

@end

NS_ASSUME_NONNULL_END
