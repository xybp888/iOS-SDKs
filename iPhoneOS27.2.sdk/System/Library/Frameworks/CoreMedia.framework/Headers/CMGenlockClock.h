/*
	File:  CMGenlockClock.h
 
	Framework:  CoreMedia
 
	Copyright 2026 Apple Inc. All rights reserved.
 
*/

#ifndef __CMGENLOCKCLOCK__
#define __CMGENLOCKCLOCK__

#include <CoreMedia/CMBase.h>
#include <CoreMedia/CMSync.h>

#ifdef __cplusplus
extern "C" {
#endif
    
#pragma pack(push)
#pragma pack()

#if COREMEDIA_SUPPORTS_GENLOCK_CLOCK
/// Returns a clock whose time is based on genlock when the system is synchronized to an external genlock signal, and on host time otherwise.
///
/// When the system is not synchronized to an external genlock signal, the returned clock will provide a time based on the host time clock.
/// When the system is synchronized to an external genlock signal, the returned clock will provide a time based on the genlock signal.
/// Use `CMIsAnyDisplaySynchronizedToLockedGenlockSignal` to determine whether the system is currently synchronized to an external genlock signal.
/// The caller is responsible for releasing the returned clock when it is no longer needed.
/// While the clock object persists, system energy use may be elevated (to monitor the genlock signal).
/// When a genlock clock is already in use, further calls to this function may return the same clock object.
CM_EXPORT CM_NULLABLE CM_RETURNS_RETAINED CMClockRef
CMClockCreateGenlockClock(void) CM_REFINED_FOR_SWIFT
	API_AVAILABLE(macos(27.0), macCatalyst(27.0)) API_UNAVAILABLE(ios, tvos, watchos, visionos);

/// Queries whether any display is synchronized to a locked external genlock signal.
CM_EXPORT Boolean
CMIsAnyDisplaySynchronizedToLockedGenlockSignal(void) CM_REFINED_FOR_SWIFT
	API_AVAILABLE(macos(27.0), macCatalyst(27.0)) API_UNAVAILABLE(ios, tvos, watchos, visionos);

CM_ASSUME_NONNULL_BEGIN

/// Posted when the display mode changes from genlock to non-genlock or vice versa.
///
/// Observe this notification using `CMNotificationCenterAddListener` on the
/// default local `CMNotificationCenter`.
/// The notification payload dictionary contains a `CFBoolean` value for the key
/// `kCMGenlockClockNotificationPayload_AnyDisplayIsSynchronizedToLockedGenlockSignal`.
CM_EXPORT const CFStringRef kCMGenlockClockNotification_DisplayGenlockModeChanged
	API_AVAILABLE(macos(27.0), macCatalyst(27.0)) API_UNAVAILABLE(ios, tvos, watchos, visionos);

CM_EXPORT const CFStringRef kCMGenlockClockNotificationPayload_AnyDisplayIsSynchronizedToLockedGenlockSignal
	API_AVAILABLE(macos(27.0), macCatalyst(27.0)) API_UNAVAILABLE(ios, tvos, watchos, visionos);

CM_ASSUME_NONNULL_END

#endif // COREMEDIA_SUPPORTS_GENLOCK_CLOCK

#pragma pack(pop)
    
#ifdef __cplusplus
}
#endif

#endif // __CMGENLOCKCLOCK__
