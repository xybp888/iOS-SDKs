//
//  SRHeadphoneSettings.h
//  SensorKit
//
//  Copyright © 2025 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <SensorKit/SRDefines.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

typedef NS_ENUM(NSInteger, SRHeadphoneSettingsSettingEnablement) {
    SRHeadphoneSettingsSettingEnablementUnsupported = 0,
    SRHeadphoneSettingsSettingEnablementEnabled,
    SRHeadphoneSettingsSettingEnablementDisabled
} API_AVAILABLE(ios(27.0)) API_UNAVAILABLE(watchos, visionos) API_UNAVAILABLE(tvos, macos);

typedef NS_ENUM(NSInteger, SRHeadphoneSettingsListeningMode) {
    SRHeadphoneSettingsListeningModeNormal = 1,
    SRHeadphoneSettingsListeningModeActiveNoiseCancelling,
    SRHeadphoneSettingsListeningModeTransparency,
    SRHeadphoneSettingsListeningModeAutoActiveNoiseCancelling
} API_AVAILABLE(ios(27.0)) API_UNAVAILABLE(watchos, visionos) API_UNAVAILABLE(tvos, macos);

typedef NS_ENUM(uint32_t, SRHeadphoneSettingsAdaptiveAudioStrength) {
    SRHeadphoneSettingsAdaptiveAudioStrengthLow = 1,
    SRHeadphoneSettingsAdaptiveAudioStrengthMedium,
    SRHeadphoneSettingsAdaptiveAudioStrengthHigh
} API_AVAILABLE(ios(27.0)) API_UNAVAILABLE(watchos, visionos) API_UNAVAILABLE(tvos, macos);

NS_SWIFT_SENDABLE
SR_EXTERN API_AVAILABLE(ios(27.0)) API_UNAVAILABLE(watchos, visionos) API_UNAVAILABLE(tvos, macos)
@interface SRHeadphoneSettingsHearingAssistance: NSObject <NSSecureCoding, NSCopying>

/*!
 *  @property hearingAidEnabled
 */
@property (nonatomic, assign, readonly) SRHeadphoneSettingsSettingEnablement hearingAidEnabled;

/*!
 *  @property mediaAssistEnabled
 *
 *  @brief Setting to enable adjustments to media that improve the clarity of music, video, and calls when hearing aid is active.
 */
@property (nonatomic, assign, readonly) SRHeadphoneSettingsSettingEnablement mediaAssistEnabled;

/*!
 *  @property adjustMediaEnabled
 *
 *  @brief Setting to enable audio adjustments to music and video playing on device.
 */
@property (nonatomic, assign, readonly) SRHeadphoneSettingsSettingEnablement adjustMediaEnabled;

/*!
 *  @property adjustVoiceEnabled
 *
 *  @brief Setting to enable audio adjustments to phone calls.
 */
@property (nonatomic, assign, readonly) SRHeadphoneSettingsSettingEnablement adjustVoiceEnabled;

/*!
 *  @property hearingProtectionEnabled
 *
 *  @brief Actively reduce your exposure to loud environmental sounds in Transparency and Adaptive modes.
 */
@property (nonatomic, assign, readonly) SRHeadphoneSettingsSettingEnablement hearingProtectionEnabled;

/*!
 *  @property conversationBoostEnabled
 *
 *  @brief In noisy environments, automatically focuses source on the person speaking to you.
 */
@property (nonatomic, assign, readonly) SRHeadphoneSettingsSettingEnablement conversationBoostEnabled;

/*!
 *  @property hearingAidAmplification
 */
@property (nonatomic, assign, readonly) double hearingAidAmplification;

/*!
 *  @property hearingAidBalance
 */
@property (nonatomic, assign, readonly) double hearingAidBalance;

/*!
 *  @property hearingAidTone
 */
@property (nonatomic, assign, readonly) double hearingAidTone;

/*!
 *  @property ambientNoiseReduction
 */
@property (nonatomic, assign, readonly) double ambientNoiseReduction;
@end

NS_SWIFT_SENDABLE
SR_EXTERN API_AVAILABLE(ios(27.0)) API_UNAVAILABLE(watchos, visionos) API_UNAVAILABLE(tvos, macos)
@interface SRHeadphoneSettings: NSObject <NSSecureCoding, NSCopying>

/*!
 *  @property adaptiveAudioStrength
 *
 *  @brief Adaptive Audio dynamically responds to your environment and cancels or allows
 *         external noise.
 */
@property (nonatomic, assign, readonly) SRHeadphoneSettingsAdaptiveAudioStrength adaptiveAudioStrength;

/*!
 *  @property listeningMode
 */
@property (nonatomic, assign, readonly) SRHeadphoneSettingsListeningMode listeningMode;

/*!
 *  @property personalizedVolumeEnabled
 *
 *  @brief Media volume adjusts in response to your environment.
 */
@property (nonatomic, assign, readonly) SRHeadphoneSettingsSettingEnablement personalizedVolumeEnabled;

/*!
 *  @property conversationAwarenessEnabled
 *
 *  @brief Media volume lowers and reduces background noise when you start speaking to other people.
 */
@property (nonatomic, assign, readonly) SRHeadphoneSettingsSettingEnablement conversationAwarenessEnabled;

/*!
 *  @property spatialAudioEnabled
 *
 *  @brief Hear audio rendered immersively in three dimensions.
 */
@property (nonatomic, assign, readonly) SRHeadphoneSettingsSettingEnablement spatialAudioEnabled;

/*!
 *  @property personalizedSpatialAudioEnabled
 *
 *  @brief Improved audio rendering when used with supported AirPods or Beats headphones.
 */
@property (nonatomic, assign, readonly) SRHeadphoneSettingsSettingEnablement personalizedSpatialAudioEnabled;

/*!
 *  @property hearingAssistance
 *
 *  @brief Hearing Assistance Settings
 */
@property (nonatomic, strong, readonly, nullable) SRHeadphoneSettingsHearingAssistance *hearingAssistance;

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new  NS_UNAVAILABLE;
@end

NS_HEADER_AUDIT_END(nullability, sendability)
