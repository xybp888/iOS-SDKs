//
//  INRequestRideIntent_Deprecated.h
//  Intents
//
//  Copyright © 2016 Apple. All rights reserved.
//

#import <Intents/INRequestRideIntent.h>

#if (defined(TARGET_OS_IOS) && TARGET_OS_IOS)

NS_ASSUME_NONNULL_BEGIN

@interface INRequestRideIntent (Deprecated)

@property (readonly, nullable, NS_NONATOMIC_IOSONLY) INDateComponentsRange *pickupTime;

- (instancetype)initWithPickupLocation:(nullable CLPlacemark *)pickupLocation
                       dropOffLocation:(nullable CLPlacemark *)dropOffLocation
                        rideOptionName:(nullable INSpeakableString *)rideOptionName
                             partySize:(nullable NSNumber *)partySize
                         paymentMethod:(nullable INPaymentMethod *)paymentMethod NS_REFINED_FOR_SWIFT;

@end

NS_ASSUME_NONNULL_END

#endif
