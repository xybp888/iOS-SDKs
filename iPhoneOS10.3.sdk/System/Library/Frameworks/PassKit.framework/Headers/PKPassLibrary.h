//
//  PKPassLibrary.h
//  PassKit
//
//  Copyright (c) 2011 Apple, Inc. All rights reserved.
//
//  Threading contract: no concurrent usage.

#import <Foundation/Foundation.h>
#import <PassKit/PKPass.h>

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSInteger, PKPassLibraryAddPassesStatus) {
    PKPassLibraryDidAddPasses,
    PKPassLibraryShouldReviewPasses,
    PKPassLibraryDidCancelAddPasses,
} NS_ENUM_AVAILABLE_IOS(7_0);


typedef NS_ENUM(NSUInteger, PKAutomaticPassPresentationSuppressionResult) {
    PKAutomaticPassPresentationSuppressionResultNotSupported = 0,   // Suppression is not supported for this device
    PKAutomaticPassPresentationSuppressionResultAlreadyPresenting,  // Passes are already being presented and cannot be suppressed
    PKAutomaticPassPresentationSuppressionResultDenied,             // Suppression was denied due to lack of entitlement
    PKAutomaticPassPresentationSuppressionResultCancelled,          // Suppression was cancelled before the response handler was fired
    PKAutomaticPassPresentationSuppressionResultSuccess             // Suppression of automatic pass presentation was successful
} __WATCHOS_PROHIBITED NS_ENUM_AVAILABLE_IOS(9_0);

typedef NSUInteger PKSuppressionRequestToken;

NS_CLASS_AVAILABLE_IOS(6_0)
@interface PKPassLibrary : NSObject

// The library is not available on iPad in 6.0.
+ (BOOL)isPassLibraryAvailable NS_AVAILABLE_IOS(6_0);

// These methods may be used to temporarily disable the automatic presentation of passes when a device encounters a contactless field.
// Use of these methods require an entitlement. Otherwise, requesting will always return a PKAutomaticPassPresentationSuppressionResultDenied as the result.
+ (PKSuppressionRequestToken)requestAutomaticPassPresentationSuppressionWithResponseHandler:(void(^)(PKAutomaticPassPresentationSuppressionResult result))responseHandler __WATCHOS_PROHIBITED NS_AVAILABLE_IOS(9_0) NS_EXTENSION_UNAVAILABLE("Not available to extensions");
+ (void)endAutomaticPassPresentationSuppressionWithRequestToken:(PKSuppressionRequestToken)requestToken __WATCHOS_PROHIBITED NS_AVAILABLE_IOS(9_0) NS_EXTENSION_UNAVAILABLE("Not available to extensions");
+ (BOOL)isSuppressingAutomaticPassPresentation __WATCHOS_PROHIBITED NS_AVAILABLE_IOS(9_0) NS_EXTENSION_UNAVAILABLE("Not available to extensions");

// If device supports adding payment passes, this method will return YES. Otherwise, NO will be returned.
+ (BOOL)isPaymentPassActivationAvailable NS_DEPRECATED_IOS(8_0, 9_0, "Use -[PKPassLibrary isPaymentPassActivationAvailable] instead");

// If this pass library supports activating payment passes, this method will return YES. Otherwise, NO will be returned.
- (BOOL)isPaymentPassActivationAvailable NS_AVAILABLE_IOS(9_0);

// These return only local passes the process is entitled to access.
- (NSArray<PKPass *> *)passes;
- (nullable PKPass *)passWithPassTypeIdentifier:(NSString *)identifier serialNumber:(NSString *)serialNumber;
- (NSArray<PKPass *> *)passesOfType:(PKPassType)passType NS_AVAILABLE_IOS(8_0);

// This returns the remote payment passes from attached devices
- (NSArray<PKPaymentPass *> *)remotePaymentPasses NS_AVAILABLE_IOS(9_0);

- (void)removePass:(PKPass *)pass;

// This returns YES even if the process is not entitled to access the pass in the library.  An app like Mail is not entitled to get
// pass from the library, but it should avoid presenting UI for adding an email attachment pass that is already in the library.
- (BOOL)containsPass:(PKPass *)pass;

// This will fail if a pass with matching identifier and serial number is not already present in the library, or if the process
// is not entitled to access the pass. To add a completely new pass, use PKAddPassesViewController.
- (BOOL)replacePassWithPass:(PKPass *)pass;

// The user will be prompted to grant permission for the calling process to add passes to the Pass Library. The user may respond
// by allowing the passes to be added, or requesting to review the passes. The selection will be returned in the completionHandler
// as a PKPassLibraryAddPassesStatus. If PKPassLibraryPassesPresentReview is returned, you must present a PKAddPassesViewController
// initialized with the passes so that the user may review and add the passes manually. The completion handler for this method is
// called on an arbitrary queue - dispatch to the main queue if you're presenting UI.
- (void)addPasses:(NSArray<PKPass *> *)passes withCompletionHandler:(nullable void(^)(PKPassLibraryAddPassesStatus status))completion NS_AVAILABLE_IOS(7_0);

// Opens the card setup flow (in Wallet on iPhone, Settings on iPad). Use this to direct a user to card setup directly from your app.
- (void)openPaymentSetup __WATCHOS_PROHIBITED NS_AVAILABLE_IOS(8_3);

// Presents the pass for use above the current application. The pass must already be in the pass library for this to have effect.
- (void)presentPaymentPass:(PKPaymentPass *)pass __WATCHOS_PROHIBITED NS_AVAILABLE_IOS(10_0);

// Returns YES if either the current device or an attached device both supports adding payment passes and does not already contain
// a payment pass with the supplied primary account identifier.
- (BOOL)canAddPaymentPassWithPrimaryAccountIdentifier:(NSString *)primaryAccountIdentifier NS_AVAILABLE_IOS(9_0);

// If the library can add Felica passes, this method will return YES. Otherwise, NO will be returned.
- (BOOL)canAddFelicaPass NS_AVAILABLE_IOS(10_1) __WATCHOS_AVAILABLE(3.1);

// These methods may be utilized to activate a payment pass that is provisioned but currently in the inactive state, by providing
// either a cryptographic OTP, or an activation code.
- (void)activatePaymentPass:(PKPaymentPass *)paymentPass withActivationData:(NSData *)activationData completion:(nullable void(^)(BOOL success, NSError* error))completion __WATCHOS_PROHIBITED NS_AVAILABLE_IOS(8_0);
- (void)activatePaymentPass:(PKPaymentPass *)paymentPass withActivationCode:(NSString *)activationCode completion:(nullable void(^)(BOOL success, NSError* error))completion __WATCHOS_PROHIBITED NS_DEPRECATED_IOS(8_0, 9_0, "Use activatePaymentPass:withActivationData:completion: instead");
@end

// This notification is issued by a library instance, with that instance as the sender.  If there are no instantiated library objects,
// no notifications. There are no guarantees about what thread or queue these come in on.
typedef NSString * PKPassLibraryNotificationName NS_EXTENSIBLE_STRING_ENUM;
extern PKPassLibraryNotificationName const PKPassLibraryDidChangeNotification NS_AVAILABLE_IOS(6_0);
extern PKPassLibraryNotificationName const PKPassLibraryRemotePaymentPassesDidChangeNotification NS_AVAILABLE_IOS(9_0);

// Entries in user info dictionary for PKPassLibraryDidChangeNotification.
// - PKPassLibraryAddedPassesUserInfoKey is the key for an array of passes
// - PKPassLibraryReplacementPassesUserInfoKey is the key for an array of passes
// - PKPassLibraryRemovedPassInfosUserInfoKey is the key for an array of dictionaries, each of which has keys
//   PKPassLibraryPassTypeIdentifierUserInfoKey and PKPassLibrarySerialNumberUserInfoKey mapping to strings.
typedef NSString * PKPassLibraryNotificationKey NS_STRING_ENUM;
extern PKPassLibraryNotificationKey const PKPassLibraryAddedPassesUserInfoKey NS_AVAILABLE_IOS(6_0);
extern PKPassLibraryNotificationKey const PKPassLibraryReplacementPassesUserInfoKey NS_AVAILABLE_IOS(6_0);
extern PKPassLibraryNotificationKey const PKPassLibraryRemovedPassInfosUserInfoKey NS_AVAILABLE_IOS(6_0);

extern PKPassLibraryNotificationKey const PKPassLibraryPassTypeIdentifierUserInfoKey NS_AVAILABLE_IOS(6_0);
extern PKPassLibraryNotificationKey const PKPassLibrarySerialNumberUserInfoKey NS_AVAILABLE_IOS(6_0);

NS_ASSUME_NONNULL_END
