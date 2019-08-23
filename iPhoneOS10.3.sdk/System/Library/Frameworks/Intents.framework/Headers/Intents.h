//
//  Intents.h
//  Intents
//
//  Copyright © 2016 Apple. All rights reserved.
//

#import <Foundation/Foundation.h>

//! Project version number for Intents.
FOUNDATION_EXPORT double IntentsVersionNumber;

//! Project version string for Intents.
FOUNDATION_EXPORT const unsigned char IntentsVersionString[];

#ifndef __INTENTS_INDIRECT__
#define __INTENTS_INDIRECT__
#endif

// Base
#import <Intents/INIntent.h>
#import <Intents/INIntentErrors.h>
#import <Intents/INIntentHandlerProviding.h>
#import <Intents/INIntentIdentifiers.h>
#import <Intents/INIntentResponse.h>
#import <Intents/INIntentResolutionResult.h>
#import <Intents/INDomainHandling.h>
#import <Intents/INInteraction.h>
#import <Intents/INSpeakable.h>

// Intents & Intent Responses
#import <Intents/INIntents.h>
#import <Intents/INIntentResponses.h>

// Extension
#import <Intents/INExtension.h>

// Common Types
#import <Intents/INPersonHandle.h>
#import <Intents/INCurrencyAmount.h>
#import <Intents/INDateComponentsRange.h>
#import <Intents/INImage.h>
#import <Intents/INPaymentMethod.h>
#import <Intents/INPaymentMethodType.h>
#import <Intents/INPerson.h>
#import <Intents/INSpeakableString.h>
#import <Intents/INPersonHandleLabel.h>
#import <Intents/INPersonRelationship.h>

// Common Resolution Results
#import <Intents/INBooleanResolutionResult.h>
#import <Intents/INCurrencyAmountResolutionResult.h>
#import <Intents/INDateComponentsRangeResolutionResult.h>
#import <Intents/INDoubleResolutionResult.h>
#import <Intents/INIntegerResolutionResult.h>
#import <Intents/INPersonResolutionResult.h>
#import <Intents/INPlacemarkResolutionResult.h>
#import <Intents/INSpeakableStringResolutionResult.h>
#import <Intents/INStringResolutionResult.h>
#import <Intents/INTemperatureResolutionResult.h>
#import <Intents/INDateComponentsResolutionResult.h>
#import <Intents/INRestaurantResolutionResult.h>
#import <Intents/INRestaurantGuestResolutionResult.h>

// Calls Domain
#import <Intents/INSearchCallHistoryIntent.h>
#import <Intents/INSearchCallHistoryIntentResponse.h>
#import <Intents/INStartAudioCallIntent.h>
#import <Intents/INStartAudioCallIntentResponse.h>
#import <Intents/INStartVideoCallIntent.h>
#import <Intents/INStartVideoCallIntentResponse.h>

#import <Intents/INCallRecordType.h>
#import <Intents/INCallRecordTypeResolutionResult.h>
#import <Intents/INCallCapabilityOptions.h>

// CarPlay & Radio Domains
#import <Intents/INSetAudioSourceInCarIntent.h>
#import <Intents/INSetAudioSourceInCarIntentResponse.h>
#import <Intents/INSetClimateSettingsInCarIntent.h>
#import <Intents/INSetClimateSettingsInCarIntentResponse.h>
#import <Intents/INSetDefrosterSettingsInCarIntent.h>
#import <Intents/INSetDefrosterSettingsInCarIntentResponse.h>
#import <Intents/INSetSeatSettingsInCarIntent.h>
#import <Intents/INSetSeatSettingsInCarIntentResponse.h>
#import <Intents/INSetProfileInCarIntent.h>
#import <Intents/INSetProfileInCarIntentResponse.h>
#import <Intents/INSaveProfileInCarIntent.h>
#import <Intents/INSaveProfileInCarIntentResponse.h>
#import <Intents/INSetRadioStationIntent.h>
#import <Intents/INSetRadioStationIntentResponse.h>

#import <Intents/INCarAirCirculationMode.h>
#import <Intents/INCarAirCirculationModeResolutionResult.h>
#import <Intents/INCarAudioSource.h>
#import <Intents/INCarAudioSourceResolutionResult.h>
#import <Intents/INCarDefroster.h>
#import <Intents/INCarDefrosterResolutionResult.h>
#import <Intents/INCarSeat.h>
#import <Intents/INCarSeatResolutionResult.h>
#import <Intents/INCarSignalOptions.h>
#import <Intents/INCarSignalOptionsResolutionResult.h>
#import <Intents/INRadioType.h>
#import <Intents/INRadioTypeResolutionResult.h>
#import <Intents/INRelativeReference.h>
#import <Intents/INRelativeReferenceResolutionResult.h>
#import <Intents/INRelativeSetting.h>
#import <Intents/INRelativeSettingResolutionResult.h>

// Messages Domain
#import <Intents/INSearchForMessagesIntent.h>
#import <Intents/INSearchForMessagesIntentResponse.h>
#import <Intents/INSendMessageIntent.h>
#import <Intents/INSendMessageIntentResponse.h>
#import <Intents/INSetMessageAttributeIntent.h>
#import <Intents/INSetMessageAttributeIntentResponse.h>

#import <Intents/INMessage.h>
#import <Intents/INMessageAttribute.h>
#import <Intents/INMessageAttributeResolutionResult.h>
#import <Intents/INMessageAttributeOptions.h>
#import <Intents/INMessageAttributeOptionsResolutionResult.h>

// Payments Domain
#import <Intents/INBillDetails.h>
#import <Intents/INBillPayee.h>
#import <Intents/INBillPayeeResolutionResult.h>
#import <Intents/INBillType.h>
#import <Intents/INPaymentRecord.h>
#import <Intents/INPaymentStatus.h>
#import <Intents/INPaymentAccount.h>
#import <Intents/INPaymentAccountResolutionResult.h>
#import <Intents/INPaymentAmount.h>
#import <Intents/INPaymentAmountResolutionResult.h>
#import <Intents/INBillTypeResolutionResult.h>
#import <Intents/INPaymentStatusResolutionResult.h>

// Photos Domain
#import <Intents/INSearchForPhotosIntent.h>
#import <Intents/INSearchForPhotosIntentResponse.h>
#import <Intents/INStartPhotoPlaybackIntent.h>
#import <Intents/INStartPhotoPlaybackIntentResponse.h>

#import <Intents/INPhotoAttributeOptions.h>

// Ridesharing Domain
#import <Intents/INListRideOptionsIntent.h>
#import <Intents/INListRideOptionsIntentResponse.h>
#import <Intents/INRequestRideIntent.h>
#import <Intents/INRequestRideIntentResponse.h>
#import <Intents/INGetRideStatusIntent.h>
#import <Intents/INGetRideStatusIntentResponse.h>

#import <Intents/INPriceRange.h>
#import <Intents/INRideOption.h>
#import <Intents/INRideStatus.h>
#import <Intents/INRidePhase.h>
#import <Intents/INRideDriver.h>
#import <Intents/INRideVehicle.h>
#import <Intents/INRideFareLineItem.h>
#import <Intents/INRidePartySizeOption.h>
#import <Intents/INRideCompletionStatus.h>

// Workouts Domain
#import <Intents/INStartWorkoutIntent.h>
#import <Intents/INStartWorkoutIntentResponse.h>
#import <Intents/INPauseWorkoutIntent.h>
#import <Intents/INPauseWorkoutIntentResponse.h>
#import <Intents/INEndWorkoutIntent.h>
#import <Intents/INEndWorkoutIntentResponse.h>
#import <Intents/INCancelWorkoutIntent.h>
#import <Intents/INCancelWorkoutIntentResponse.h>
#import <Intents/INResumeWorkoutIntent.h>
#import <Intents/INResumeWorkoutIntentResponse.h>

#import <Intents/INWorkoutGoalUnitType.h>
#import <Intents/INWorkoutGoalUnitTypeResolutionResult.h>
#import <Intents/INWorkoutLocationType.h>
#import <Intents/INWorkoutLocationTypeResolutionResult.h>
#import <Intents/INWorkoutNameIdentifier.h>

// Restaurant Booking
#import <Intents/INIntentRestaurantReservation.h>

// User Vocabulary
#import <Intents/INVocabulary.h>

// Utilities
#import <Intents/INSiriAuthorizationStatus.h>
#import <Intents/INPreferences.h>
#import <Intents/CLPlacemark+IntentsAdditions.h>
#import <Intents/NSUserActivity+IntentsAdditions.h>
#import <Intents/INPerson+SiriAdditions.h>

// Deprecated
#import <Intents/INPerson_Deprecated.h>
#import <Intents/INRequestRideIntent_Deprecated.h>
#import <Intents/INRideDriver_Deprecated.h>
#import <Intents/INSaveProfileInCarIntent_Deprecated.h>
#import <Intents/INSetProfileInCarIntent_Deprecated.h>
