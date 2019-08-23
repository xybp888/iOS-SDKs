//
//  PKAddPaymentPassViewController.h
//  PassKit
//
//  Copyright © 2015 Apple, Inc. All rights reserved.
//
#import <UIKit/UIKit.h>
NS_ASSUME_NONNULL_BEGIN

@class PKAddPaymentPassViewController, PKPaymentPass;

typedef NS_ENUM(NSInteger, PKAddPaymentPassError) {
    PKAddPaymentPassErrorUnsupported,
    PKAddPaymentPassErrorUserCancelled,
    PKAddPaymentPassErrorSystemCancelled
} NS_ENUM_AVAILABLE_IOS(9_0);

NS_CLASS_AVAILABLE_IOS(9_0) @interface PKAddPaymentPassRequestConfiguration : NSObject

/* Schemes defined in PKConstants.h.
 * Supported Schemes:
 *  PKEncryptionSchemeECC_V2:
 *      ephemeralPublicKey
 */
- (nullable instancetype)initWithEncryptionScheme:(NSString *)encryptionScheme NS_DESIGNATED_INITIALIZER;

@property (nonatomic, copy, readonly) NSString *encryptionScheme;

/* Display Properties:
 *  At least one of cardholder name or primary account suffix must be supplied.
 */
@property (nonatomic, copy, nullable) NSString *cardholderName;
@property (nonatomic, copy, nullable) NSString *primaryAccountSuffix;
@property (nonatomic, copy, nullable) NSString *localizedDescription;

/* Pass Library Filters:
 *  If the filtered set is empty, then all filter will be ignored.
 */
@property (nonatomic, copy, nullable) NSString *primaryAccountIdentifier;

/* Filters introduction page to a specific network - does not function as a restriction.
 */
@property (nonatomic, copy, nullable) NSString *paymentNetwork;

@end

NS_CLASS_AVAILABLE_IOS(9_0) @interface PKAddPaymentPassRequest : NSObject

- (instancetype)init NS_DESIGNATED_INITIALIZER;

@property (nonatomic, copy, nullable) NSData *encryptedPassData;
@property (nonatomic, copy, nullable) NSData *activationData;

/* Scheme dependent properties:
 */
@property (nonatomic, copy, nullable) NSData *ephemeralPublicKey;
@property (nonatomic, copy, nullable) NSData *wrappedKey;

@end

@protocol PKAddPaymentPassViewControllerDelegate<NSObject>

/* Certificates is an array of NSData, each a DER encoded X.509 certificate, with the leaf first and root last.
 * The continuation handler must be called within 20 seconds, or the flow will terminate with
 * PKAddPaymentPassErrorInvalidRequest.
 */
- (void)addPaymentPassViewController:(PKAddPaymentPassViewController *)controller
 generateRequestWithCertificateChain:(NSArray<NSData *> *)certificates
                               nonce:(NSData *)nonce
                      nonceSignature:(NSData *)nonceSignature
                   completionHandler:(void(^)(PKAddPaymentPassRequest *request))handler;

/* Error parameter will use codes from the PKAddPaymentPassError enumeration, using the PKPassKitErrorDomain domain.
 */
- (void)addPaymentPassViewController:(PKAddPaymentPassViewController *)controller didFinishAddingPaymentPass:(nullable PKPaymentPass *)pass error:(nullable NSError *)error;

@end

NS_CLASS_AVAILABLE_IOS(9_0) @interface PKAddPaymentPassViewController : UIViewController

+ (BOOL)canAddPaymentPass;

/* This controller should be presented with -[UIViewController presentViewController:animated:completion:].
 */
- (nullable instancetype)initWithRequestConfiguration:(PKAddPaymentPassRequestConfiguration *)configuration
                                             delegate:(nullable id<PKAddPaymentPassViewControllerDelegate>)delegate NS_DESIGNATED_INITIALIZER;

@property (nonatomic, weak, nullable) id<PKAddPaymentPassViewControllerDelegate> delegate;

@end

NS_ASSUME_NONNULL_END