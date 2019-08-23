//
//  INDomainHandling.h
//  Intents
//
//  Copyright © 2016 Apple. All rights reserved.
//

#import <Intents/INIntents.h>

#if !TARGET_OS_WATCH
API_AVAILABLE(macosx(10.12), ios(10.0))
@protocol INCallsDomainHandling <INStartAudioCallIntentHandling, INStartVideoCallIntentHandling, INSearchCallHistoryIntentHandling>
@end
#else
API_AVAILABLE(macosx(10.12), ios(10.0), watchos(3.2))
@protocol INCallsDomainHandling <INStartAudioCallIntentHandling, INSearchCallHistoryIntentHandling>
@end
#endif

API_AVAILABLE(ios(10.3), watchos(3.2))
API_UNAVAILABLE(macosx)
@protocol INCarCommandsDomainHandling <INActivateCarSignalIntentHandling, INSetCarLockStatusIntentHandling, INGetCarLockStatusIntentHandling, INGetCarPowerLevelStatusIntentHandling>
@end

API_AVAILABLE(ios(10.0))
API_UNAVAILABLE(macosx, watchos)
@protocol INCarPlayDomainHandling <INSetAudioSourceInCarIntentHandling, INSetClimateSettingsInCarIntentHandling, INSetDefrosterSettingsInCarIntentHandling, INSetSeatSettingsInCarIntentHandling, INSetProfileInCarIntentHandling, INSaveProfileInCarIntentHandling>
@end

API_AVAILABLE(ios(10.0), watchos(3.2))
API_UNAVAILABLE(macosx)
@protocol INWorkoutsDomainHandling <INStartWorkoutIntentHandling, INPauseWorkoutIntentHandling, INEndWorkoutIntentHandling, INCancelWorkoutIntentHandling, INResumeWorkoutIntentHandling>
@end

API_AVAILABLE(ios(10.0))
API_UNAVAILABLE(macosx, watchos)
@protocol INRadioDomainHandling <INSetRadioStationIntentHandling>
@end

#if !TARGET_OS_WATCH
API_AVAILABLE(macosx(10.12), ios(10.0))
@protocol INMessagesDomainHandling <INSendMessageIntentHandling, INSearchForMessagesIntentHandling, INSetMessageAttributeIntentHandling>
@end
#else
API_AVAILABLE(macosx(10.12), ios(10.0), watchos(3.2))
@protocol INMessagesDomainHandling <INSendMessageIntentHandling, INSearchForMessagesIntentHandling>
@end
#endif

#if __IPHONE_OS_VERSION_MAX_ALLOWED >= 100300

API_AVAILABLE(ios(10.3), watchos(3.2))
API_UNAVAILABLE(macosx)
@protocol INPaymentsDomainHandling <INSendPaymentIntentHandling, INRequestPaymentIntentHandling, INPayBillIntentHandling, INSearchForBillsIntentHandling>
@end

#else

API_AVAILABLE(ios(10.0))
API_UNAVAILABLE(macosx)
@protocol INPaymentsDomainHandling <INSendPaymentIntentHandling, INRequestPaymentIntentHandling>
@end

#endif

API_AVAILABLE(ios(10.0), watchos(3.2))
API_UNAVAILABLE(macosx)
@protocol INPhotosDomainHandling <INSearchForPhotosIntentHandling, INStartPhotoPlaybackIntentHandling>
@end

API_AVAILABLE(ios(10.0), watchos(3.2))
API_UNAVAILABLE(macosx)
@protocol INRidesharingDomainHandling <INListRideOptionsIntentHandling, INRequestRideIntentHandling, INGetRideStatusIntentHandling>
@end
