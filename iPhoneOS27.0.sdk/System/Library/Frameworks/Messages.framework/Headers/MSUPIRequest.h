/*!
 @header     MSUPIRequest
 @copyright  Copyright (c) 2026 Apple Inc. All rights reserved.
 */

#import <Foundation/Foundation.h>
#import <Messages/MessagesDefines.h>

NS_ASSUME_NONNULL_BEGIN

#if TARGET_OS_IOS

/*!
 @class         MSUPIRequest
 @abstract      Request for UPI (Unified Payments Interface) device validation.
 @discussion    In order to use this API, you must use the managed entitlement `com.apple.developer.upi-device-validation`. This API is only functional on devices with SMS capability, and only compatible with non-iMessagable recipients.
 */
API_AVAILABLE(ios(27.0), macCatalyst(27.0), visionos(27.0)) API_UNAVAILABLE(macos, watchos, tvos)
MESSAGES_EXTERN
@interface MSUPIRequest : NSObject

/*!
 @property   validationToken
 @abstract   The validation token to be sent.
*/
@property (nonatomic, copy, readonly) NSString *validationToken;

/*!
 @property   recipients
 @abstract   The SMS recipients who will receive the UPI validation message.
 */
@property (nonatomic, copy, readonly) NSArray <NSString *>*recipients;

/*!
 @method     initWithValidationToken:recipients:
 @abstract   Creates a new UPI request with the specified validation token and recipients.
 @param      validationToken  The validation token to be sent.
 @param      recipients  The SMS recipients who will receive the UPI validation message.
*/
- (instancetype)initWithValidationToken:(NSString *)validationToken recipients:(NSArray<NSString *> *)recipients;

/*!
 @method     sendWithCompletionHandler:
 @abstract   Sends this UPI request.
 @param      completionHandler  A completion handler called when the message has been sent or has failed to send.
 */
- (void)sendWithCompletionHandler:(void (^)(BOOL sent))completionHandler;

@end

#endif

NS_ASSUME_NONNULL_END
