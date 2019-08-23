//
//  INRideCompletionStatus.h
//  Intents
//
//  Copyright © 2016 Apple. All rights reserved.
//

#import <Foundation/Foundation.h>

@class INCurrencyAmount;

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(macosx(10.12), ios(10.0), watchos(3.2))
@interface INRideCompletionStatus: NSObject <NSCopying, NSSecureCoding>

- (instancetype)init NS_UNAVAILABLE;

// The ride completed.
+ (instancetype)completed;

// The ride completed. The fare in the provided amount was successfully paid; this amount may be displayed to the user.
+ (instancetype)completedWithSettledPaymentAmount:(INCurrencyAmount *)settledPaymentAmount NS_SWIFT_NAME(completed(settled:));

// The ride completed but there is a payment outstanding that the user needs to settle in the application.
// The .completionUserActivity should be set, and will be continued in your application to perform payment tasks.
+ (instancetype)completedWithOutstandingPaymentAmount:(INCurrencyAmount *)outstandingPaymentAmount NS_SWIFT_NAME(completed(outstanding:));

// The ride was canceled by the service (e.g. because the driver asked to cancel)
+ (instancetype)canceledByService;

// The ride was canceled by the user (e.g. by doing so through your application)
+ (instancetype)canceledByUser;

// The ride was canceled by the service because the passenger was not present for pickup and the vehicle maximum wait time elapsed.
+ (instancetype)canceledMissedPickup;

// If this property is set, UI may be shown to the user to complete post-ride tasks (e.g. for feedback or settling outstanding payment). Acting on that UI will continue this activity in your application.
@property (readwrite, strong, nullable, NS_NONATOMIC_IOSONLY) NSUserActivity *completionUserActivity;

// YES if the ride was completed.
@property (readonly, NS_NONATOMIC_IOSONLY, getter=isCompleted) BOOL completed;

// YES if the ride was canceled.
@property (readonly, NS_NONATOMIC_IOSONLY, getter=isCanceled) BOOL canceled;

// YES if the user missed the pickup. This is only YES if .canceled is YES.
@property (readonly, NS_NONATOMIC_IOSONLY, getter=isMissedPickup) BOOL missedPickup;

// The payment amount, if any.
@property (readonly, strong, nullable, NS_NONATOMIC_IOSONLY) INCurrencyAmount *paymentAmount;

// Whether the payment is outstanding (YES) or settled (NO).
@property (readonly, NS_NONATOMIC_IOSONLY, getter=isOutstanding) BOOL outstanding;

@end

NS_ASSUME_NONNULL_END
