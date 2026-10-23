//
//  AEAssessmentConfiguration.h
//  AutomaticAssessmentConfiguration
//
//  Copyright © 2020 Apple Inc. All rights reserved.
//

#import <AutomaticAssessmentConfiguration/AEVisibility.h>
#import <AutomaticAssessmentConfiguration/AEAppleMenuItem.h>
#import <AutomaticAssessmentConfiguration/AEMenuBarItem.h>
#import <AutomaticAssessmentConfiguration/AEUserAccountType.h>
#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@class AEAssessmentApplication;
@class AEAssessmentBinaryExecutable;
@class AEAssessmentBinaryExecutableConfiguration;
@class AEAssessmentParticipantConfiguration;

/// Configuration information for an assessment session.
///
/// Create a configuration instance and pass it to the ``AEAssessmentSession/init(configuration:)`` initializer of an ``AEAssessmentSession`` instance to create a new assessment session. Before using the configuration, indicate which exceptions you want to allow for the assessment session's restrictions by setting values on the configuration instance. For example, you can set values to allow dictation and certain aspects of autocorrect:
///
/// ```swift
/// let config = AEAssessmentConfiguration()
///
/// #if os(iOS) // These exceptions available only on iOS and iPadOS.
/// config.allowsDictation = true
/// config.autocorrectMode = [.punctuation, .spelling]
/// #endif
///
/// let session = AEAssessmentSession(configuration: config)
/// ```
///
/// While you provide a configuration instance when creating a session on iOS, iPadOS, and macOS, specific exceptions apply only to certain platforms. In particular, on macOS, you can selectively make specific apps besides your own available during an assessment — for example, to allow users to access a calculator or a dictionary. All other exceptions apply only to iOS and iPadOS.
///
/// ## Topics
///
/// ### Allowing access to other apps
///
/// - ``setConfiguration(_:for:)``
/// - ``configurationsByApplication``
/// - ``remove(_:)``
/// - ``setConfiguration(_:for:)-(AEAssessmentBinaryExecutableConfiguration,_)``
/// - ``configurationsByBinaryExecutable``
/// - ``removeBinaryExecutable(_:)``
/// - ``mainParticipantConfiguration``
/// - ``AEAssessmentApplication``
/// - ``AEAssessmentBinaryExecutable``
/// - ``AEAssessmentParticipantConfiguration``
///
/// ### Allowing accessibility
///
/// - ``allowsAccessibilityAlternativeInputMethods``
/// - ``allowsAccessibilityBackgroundSounds``
/// - ``allowsAccessibilityFullKeyboardAccess``
/// - ``allowsAccessibilityHoverText``
/// - ``allowsAccessibilityKeyboard``
/// - ``allowsAccessibilityLiveCaptions``
/// - ``allowsAccessibilityLiveSpeech``
/// - ``allowsAccessibilityReader``
/// - ``allowsAccessibilitySpeech``
/// - ``allowsAccessibilitySwitchControl``
/// - ``allowsAccessibilityTypingFeedback``
/// - ``allowsAccessibilityVoiceControl``
/// - ``allowsAccessibilityVoiceOver``
/// - ``allowsAccessibilityZoom``
/// - ``allowsAccessibilitySpokenContent``
/// - ``allowsDictation``
///
/// ### Allowing typing assistance
///
/// - ``allowsContinuousPathKeyboard``
/// - ``allowsKeyboardShortcuts``
/// - ``allowsPredictiveKeyboard``
/// - ``allowsPasswordAutoFill``
///
/// ### Allowing corrections
///
/// - ``allowsSpellCheck``
/// - ``autocorrectMode-swift.property``
/// - ``AutocorrectMode-swift.struct``
///
/// ### Allowing handoff
///
/// - ``allowsActivityContinuation``
///
/// ### Allowing content capture
///
/// - ``allowsScreenshots``
///
/// ### Controlling force quit
///
/// - ``allowsForceQuit``
///
API_AVAILABLE(ios(13.4), macos(10.15.4), macCatalyst(14.0))
API_UNAVAILABLE(visionos)
@interface AEAssessmentConfiguration: NSObject <NSCopying>

/// The set of autocorrect features that you can enable during an assessment.
///
/// Use one or more of the autocorrect modes to set the ``AEAssessmentConfiguration/autocorrectMode-swift.property`` property of an ``AEAssessmentConfiguration`` instance. For example, you can enable both spelling and punctuation corrections by combining ``AEAssessmentConfiguration/AutocorrectMode-swift.struct/spelling`` and ``AEAssessmentConfiguration/AutocorrectMode-swift.struct/punctuation``:
///
/// ```swift
/// let config = AEAssessmentConfiguration()
///
/// #if os(iOS) // Available only on iOS and iPadOS.
/// config.autocorrectMode = [.punctuation, .spelling]
/// #endif
///
/// let session = AEAssessmentSession(configuration: config)
/// ```
///
/// ## Topics
///
/// ### Creating a mode
///
/// - ``AEAssessmentConfiguration/AutocorrectMode-swift.struct/init(rawValue:)``
///
/// ### Modes
///
/// - ``AEAssessmentConfiguration/AutocorrectMode-swift.struct/punctuation``
/// - ``AEAssessmentConfiguration/AutocorrectMode-swift.struct/spelling``
/// - ``AEAutocorrectMode/AEAutocorrectModeNone``
///
API_AVAILABLE(ios(14.0), macCatalyst(18.0), macos(15.0))
API_UNAVAILABLE(visionos)
typedef NS_OPTIONS(NSUInteger, AEAutocorrectMode) {
    AEAutocorrectModeNone = 0,
    /// A mode in which autocorrect checks for spelling as the user types.
    ///
    AEAutocorrectModeSpelling = 1 << 0,
    /// A mode in which autocorrect checks punctuation as the user types.
    ///
    AEAutocorrectModePunctuation = 1 << 1,
} NS_SWIFT_NAME(AEAssessmentConfiguration.AutocorrectMode);

/// The autocorrect mode that specifies which autocorrect features to allow during an assessment.
///
/// Users can turn on autocorrect in the Settings app (General > Keyboard > Auto-Correction). An assessment session disables this feature by default, but you can allow it by setting ``AEAssessmentConfiguration/autocorrectMode-swift.property`` in the ``AEAssessmentConfiguration`` instance that you use to initialize a session. Set the mode's value to some combination of the the values from the ``AEAssessmentConfiguration/AutocorrectMode-swift.struct`` structure.
///
@property (nonatomic, assign) AEAutocorrectMode autocorrectMode API_AVAILABLE(ios(14.0), macCatalyst(18.0), macos(15.0));

/// A Boolean value that indicates whether to allow spell check during an assessment.
///
/// Users can activate the spell checker by turning on the Check Spelling feature in the Settings app (General > Keyboard). An assessment session disables spell checking by default, but you can allow it by setting ``AEAssessmentConfiguration/allowsSpellCheck`` to `true` in the ``AEAssessmentConfiguration`` instance that you use to initialize a session.
///
@property (nonatomic, assign) BOOL allowsSpellCheck API_AVAILABLE(ios(14.0), macCatalyst(18.0), macos(15.0));

/// A Boolean value that indicates whether to enable the predictive keyboard during an assessment.
///
/// Users can turn on the Predictive Keyboard feature in the Settings app (General > Keyboard). An assessment session disables this feature by default, but you can allow it by setting ``AEAssessmentConfiguration/allowsPredictiveKeyboard`` to `true` in the ``AEAssessmentConfiguration`` instance that you use to initialize a session.
///
@property (nonatomic, assign) BOOL allowsPredictiveKeyboard API_AVAILABLE(ios(14.0), macCatalyst(18.0), macos(15.0));

/// A Boolean value that indicates whether to allow keyboard shortcuts during an assessment.
///
/// Users can add Keyboard Shortcuts in the Settings app (General > Keyboard > Text Replacement). An assessment session disables the use of keyboard shortcuts by default, but you can allow them by setting ``AEAssessmentConfiguration/allowsKeyboardShortcuts`` to `true` in the ``AEAssessmentConfiguration`` instance that you use to initialize a session.
///
@property (nonatomic, assign) BOOL allowsKeyboardShortcuts API_AVAILABLE(ios(14.0), macCatalyst(18.0), macos(15.0));

/// A Boolean value that indicates whether to allow Handoff during an assessment.
///
/// Handoff lets users start an activity on one device and seamlessly resume the activity on another. Users control whether a device participates in Handoff by turning the feature on or off in the Settings app (General > AirPlay & Handoff > Handoff). An assessment disables this feature by default, but you can allow users undergoing an assessment to continue to use Handoff by setting ``AEAssessmentConfiguration/allowsActivityContinuation`` to `true`.
///
@property (nonatomic, assign) BOOL allowsActivityContinuation API_AVAILABLE(ios(14.0)) API_UNAVAILABLE(macos, macCatalyst);

/// A Boolean value that indicates whether to allow the use of dictation during an assessment.
///
/// By turning on Enable Dictation (General > Keyboard in the Settings app on iOS and iPadOS), users can speak into their device and have the words they speak converted to text. An assessment session disables this feature by default, but you can allow it by setting ``AEAssessmentConfiguration/allowsDictation`` to `true` in the ``AEAssessmentConfiguration`` instance that you use to initialize a session.
///
@property (nonatomic, assign) BOOL allowsDictation API_AVAILABLE(ios(14.0), macos(27.0), macCatalyst(27.0));

/// A Boolean value that indicates whether to allow alternative input methods for accessibility features during an assessment.
///
/// When the Accessibility Keyboard or Switch Control is enabled, alternative input methods such as Dwell Control may be available. An assessment session disables these alternative input methods by default, but you can allow them by setting ``AEAssessmentConfiguration/allowsAccessibilityAlternativeInputMethods`` to `YES` in the ``AEAssessmentConfiguration`` instance that you use to initialize a session.
///
/// - Note: This property only takes effect when ``AEAssessmentConfiguration/allowsAccessibilityKeyboard`` or ``AEAssessmentConfiguration/allowsAccessibilitySwitchControl`` is `YES`.
///
@property (nonatomic, assign) BOOL allowsAccessibilityAlternativeInputMethods API_AVAILABLE(macos(27.0), macCatalyst(27.0)) API_UNAVAILABLE(ios);

/// A Boolean value that indicates whether to allow Background Sounds during an assessment.
///
/// Users can enable Background Sounds in the Settings app (Accessibility > Audio & Visual > Background Sounds) to play ambient sounds that can mask unwanted environmental noise. An assessment session disables Background Sounds by default, but you can allow it by setting ``AEAssessmentConfiguration/allowsAccessibilityBackgroundSounds`` to `true` in the ``AEAssessmentConfiguration`` instance that you use to initialize a session.
///
@property (nonatomic, assign) BOOL allowsAccessibilityBackgroundSounds API_AVAILABLE(macos(27.0), macCatalyst(27.0)) API_UNAVAILABLE(ios);

/// A Boolean value that indicates whether to allow Full Keyboard Access during an assessment.
///
/// Users can enable Full Keyboard Access in the Settings app (Accessibility > Keyboard > Full Keyboard Access) to navigate and operate the system using only the keyboard. An assessment session **does not** disable Full Keyboard Access by default, but you can disable it by setting ``AEAssessmentConfiguration/allowsAccessibilityFullKeyboardAccess`` to `NO` in the ``AEAssessmentConfiguration`` instance that you use to initialize a session.
///
@property (nonatomic, assign) BOOL allowsAccessibilityFullKeyboardAccess API_AVAILABLE(macos(27.0), macCatalyst(27.0)) API_UNAVAILABLE(ios);

/// A Boolean value that indicates whether to allow Hover Text during an assessment.
///
/// Users can enable Hover Text in the Settings app (Accessibility > Zoom > Hover Text) to magnify text under the pointer. An assessment session **does not** disable Hover Text by default, but you can disable it by setting ``AEAssessmentConfiguration/allowsAccessibilityHoverText`` to `NO` in the ``AEAssessmentConfiguration`` instance that you use to initialize a session.
///
@property (nonatomic, assign) BOOL allowsAccessibilityHoverText API_AVAILABLE(macos(27.0), macCatalyst(27.0)) API_UNAVAILABLE(ios);

/// A Boolean value that indicates whether to allow the Accessibility Keyboard during an assessment.
///
/// Users can enable the Accessibility Keyboard in the Settings app (Accessibility > Keyboard > Accessibility Keyboard) to access an on-screen keyboard. An assessment session **does not** disable the Accessibility Keyboard by default, but you can disable it by setting ``AEAssessmentConfiguration/allowsAccessibilityKeyboard`` to `NO` in the ``AEAssessmentConfiguration`` instance that you use to initialize a session.
///
/// - Note: To allow the full Accessibility Keyboard with alternative input methods (such as Dwell Control), you must also set ``AEAssessmentConfiguration/allowsAccessibilityAlternativeInputMethods`` to `YES`.
///
@property (nonatomic, assign) BOOL allowsAccessibilityKeyboard API_AVAILABLE(macos(26.1), macCatalyst(26.1)) API_UNAVAILABLE(ios);

/// A Boolean value that indicates whether to allow Live Captions during an assessment.
///
/// Users can enable Live Captions in the Settings app (Accessibility > Live Captions) to receive real-time transcription of spoken audio as text on screen. An assessment session disables Live Captions by default, but you can allow it by setting ``AEAssessmentConfiguration/allowsAccessibilityLiveCaptions`` to `true` in the ``AEAssessmentConfiguration`` instance that you use to initialize a session.
///
@property (nonatomic, assign) BOOL allowsAccessibilityLiveCaptions API_AVAILABLE(ios(26.1), macCatalyst(26.1), macos(26.1));

/// A Boolean value that indicates whether to allow Live Speech during an assessment.
///
/// Users can enable Live Speech in the Settings app (Accessibility > Speech > Live Speech) to type what they want to say and have it spoken aloud. An assessment session disables Live Speech by default, but you can allow it by setting ``AEAssessmentConfiguration/allowsAccessibilityLiveSpeech`` to `true` in the ``AEAssessmentConfiguration`` instance that you use to initialize a session.
///
@property (nonatomic, assign) BOOL allowsAccessibilityLiveSpeech API_AVAILABLE(macos(27.0), macCatalyst(27.0)) API_UNAVAILABLE(ios);

/// A Boolean value that indicates whether to allow the Accessibility Reader during an assessment.
///
/// Users can enable the Accessibility Reader in the Settings app (Accessibility > Read & Speak > Accessibility Reader) to have text content formatted or read aloud. An assessment session disables the Accessibility Reader by default, but you can allow it by setting ``AEAssessmentConfiguration/allowsAccessibilityReader`` to `true` in the ``AEAssessmentConfiguration`` instance that you use to initialize a session.
///
@property (nonatomic, assign) BOOL allowsAccessibilityReader API_AVAILABLE(ios(26.1), macCatalyst(26.1), macos(26.1));

/// A Boolean value that indicates whether to allow the speech-related accessibility features during an assessment.
///
/// - Important: This property is deprecated. Use ``AEAssessmentConfiguration/allowsAccessibilitySpokenContent`` instead.
///
@property (nonatomic, assign) BOOL allowsAccessibilitySpeech API_DEPRECATED_WITH_REPLACEMENT("allowsAccessibilitySpokenContent", ios(14.0, 27.0)) API_UNAVAILABLE(macos, macCatalyst);

/// A Boolean value that indicates whether to allow Spoken Content during an assessment.
///
/// Users can enable Spoken Content in the Settings app (Accessibility > Read & Speak) to have text read aloud. This includes Speak Selection, Speak Screen, and related features. An assessment session disables Spoken Content by default, but you can allow it by setting ``AEAssessmentConfiguration/allowsAccessibilitySpokenContent`` to `true` in the ``AEAssessmentConfiguration`` instance that you use to initialize a session.
///
@property (nonatomic, assign) BOOL allowsAccessibilitySpokenContent API_AVAILABLE(ios(27.0), macos(27.0), macCatalyst(27.0));

/// A Boolean value that indicates whether to allow Switch Control during an assessment.
///
/// Users can enable Switch Control in the Settings app (Accessibility > Switch Control) to control their device using adaptive switches. An assessment session **does not** disable Switch Control by default, but you can disable it by setting ``AEAssessmentConfiguration/allowsAccessibilitySwitchControl`` to `NO` in the ``AEAssessmentConfiguration`` instance that you use to initialize a session.
///
/// - Note: To allow Switch Control with alternative input methods (such as Dwell Control), you must also set ``AEAssessmentConfiguration/allowsAccessibilityAlternativeInputMethods`` to `YES`.
///
@property (nonatomic, assign) BOOL allowsAccessibilitySwitchControl API_AVAILABLE(macos(27.0), macCatalyst(27.0)) API_UNAVAILABLE(ios);

/// A Boolean value that indicates whether to allow accessibility typing feedback during an assessment.
///
/// Users can enable typing feedback features in the Settings app (Accessibility > Keyboards & Typing > Typing Feedback)  to receive audio feedback when typing. An assessment session disables these accessibility typing feedback features by default, but you can allow them by setting ``AEAssessmentConfiguration/allowsAccessibilityTypingFeedback`` to `true` in the ``AEAssessmentConfiguration`` instance that you use to initialize a session.
///
@property (nonatomic, assign) BOOL allowsAccessibilityTypingFeedback API_AVAILABLE(ios(26.0)) API_UNAVAILABLE(macos, macCatalyst);

/// A Boolean value that indicates whether to allow Voice Control during an assessment.
///
/// Users can enable Voice Control in the Settings app (Accessibility > Voice Control) to control their device using voice commands. An assessment session **does not** disable Voice Control by default, but you can disable it by setting ``AEAssessmentConfiguration/allowsAccessibilityVoiceControl`` to `NO` in the ``AEAssessmentConfiguration`` instance that you use to initialize a session.
///
@property (nonatomic, assign) BOOL allowsAccessibilityVoiceControl API_AVAILABLE(macos(27.0), macCatalyst(27.0)) API_UNAVAILABLE(ios);

/// A Boolean value that indicates whether to allow VoiceOver during an assessment.
///
/// Users can enable VoiceOver in the Settings app (Accessibility > VoiceOver) to receive spoken descriptions of on-screen elements and gestures for navigating the interface. An assessment session **does not** disable VoiceOver by default, but you can disable it by setting ``AEAssessmentConfiguration/allowsAccessibilityVoiceOver`` to `NO` in the ``AEAssessmentConfiguration`` instance that you use to initialize a session.
///
@property (nonatomic, assign) BOOL allowsAccessibilityVoiceOver API_AVAILABLE(ios(27.0), macCatalyst(27.0), macos(27.0));

/// A Boolean value that indicates whether to allow Zoom during an assessment.
///
/// Users can enable Zoom in the Settings app (Accessibility > Zoom) to magnify the screen. An assessment session **does not** disable Zoom by default, but you can disable it by setting ``AEAssessmentConfiguration/allowsAccessibilityZoom`` to `NO` in the ``AEAssessmentConfiguration`` instance that you use to initialize a session.
///
@property (nonatomic, assign) BOOL allowsAccessibilityZoom API_AVAILABLE(macos(27.0), macCatalyst(27.0)) API_UNAVAILABLE(ios);

/// A Boolean value that indicates whether to allow password autofill during an assessment.
///
/// Users can store passwords for use with Password Autofill by turning on the feature in the Settings app (General > Passwords > AutoFill Passwords). An assessment session disables Password Autofill by default, but you can allow it by setting ``AEAssessmentConfiguration/allowsPasswordAutoFill`` to `true` in the ``AEAssessmentConfiguration`` instance that you use to initialize a session.
///
@property (nonatomic, assign) BOOL allowsPasswordAutoFill API_AVAILABLE(ios(14.0)) API_UNAVAILABLE(macos, macCatalyst);

/// A Boolean value that indicates whether to allow Slide to Type to operate during an assessment.
///
/// Users can turn on Slide to Type in the Settings app (General > Keyboard). An assessment session disables this feature by default, but you can allow it by setting ``AEAssessmentConfiguration/allowsContinuousPathKeyboard`` to `true` in the ``AEAssessmentConfiguration`` instance that you use to initialize a session.
///
@property (nonatomic, assign) BOOL allowsContinuousPathKeyboard API_AVAILABLE(ios(14.0)) API_UNAVAILABLE(macos, macCatalyst);

/// A Boolean value that indicates whether to allow screenshots copied to the clipboard during an assessment.
///
/// An assessment session disables the ability to take screenshots by default to maintain assessment integrity. This property specifically applies to screenshots that are copied to the clipboard, typically those taken using the Command+Control+Shift+3 and Command+Control+Shift+4 keyboard shortcuts. You can allow clipboard screenshots by setting `allowsScreenshots` to `true`.
///
/// - Note: The clipboard is cleared before the assessment session ends to prevent exporting captured content.
///
@property (nonatomic, assign) BOOL allowsScreenshots API_AVAILABLE(macos(26.1), macCatalyst(26.1)) API_UNAVAILABLE(ios);

/// A Boolean value that indicates whether to allow the emoji keyboard during an assessment.
///
/// Users can access the emoji keyboard by tapping the emoji button on the keyboard (iOS) or through the Edit menu and keyboard shortcuts (macOS). An assessment session disables access to the emoji keyboard by default, but you can allow it by setting ``AEAssessmentConfiguration/allowsEmojiKeyboard`` to `true` in the ``AEAssessmentConfiguration`` instance that you use to initialize a session.
///
@property (nonatomic, assign) BOOL allowsEmojiKeyboard API_AVAILABLE(ios(26.4), macos(27.0), macCatalyst(27.0));

#pragma mark System Services

/// A Boolean value that indicates whether to allow user script execution during an assessment.
///
/// User scripts, such as AppleScripts or Automator workflows, can automate tasks on the system. An assessment session disables user script execution by default, but you can allow it by setting ``AEAssessmentConfiguration/allowsUserScriptExecution`` to `true` in the ``AEAssessmentConfiguration`` instance that you use to initialize a session.
///
@property (nonatomic, assign) BOOL allowsUserScriptExecution API_AVAILABLE(macos(27.0), macCatalyst(27.0)) API_UNAVAILABLE(ios);

#pragma mark Text Input

/// A Boolean value that indicates whether to allow autofill during an assessment.
///
/// Users can enable autofill in System Settings (Passwords > Password Options > AutoFill Passwords and Passkeys). An assessment session disables autofill by default, but you can allow it by setting ``AEAssessmentConfiguration/allowsAutoFill`` to `true` in the ``AEAssessmentConfiguration`` instance that you use to initialize a session.
///
@property (nonatomic, assign) BOOL allowsAutoFill API_AVAILABLE(macos(27.0), macCatalyst(27.0)) API_UNAVAILABLE(ios);

/// A Boolean value that indicates whether to allow Chinese and Japanese structural input during an assessment.
///
/// Chinese and Japanese structural input methods allow users to enter characters using component-based input. An assessment session disables structural input by default, but you can allow it by setting ``AEAssessmentConfiguration/allowsStructuralInput`` to `true` in the ``AEAssessmentConfiguration`` instance that you use to initialize a session.
///
@property (nonatomic, assign) BOOL allowsStructuralInput API_AVAILABLE(macos(27.0), macCatalyst(27.0)) API_UNAVAILABLE(ios);

#pragma mark User Interface

/// A Boolean value that indicates whether to allow force quitting apps during an assessment.
///
/// Users can force quit apps by pressing Shift-Option-Command-Escape to force quit the frontmost app. An assessment session disables force quit by default, but you can allow it by setting ``AEAssessmentConfiguration/allowsForceQuit`` to `true` in the ``AEAssessmentConfiguration`` instance that you use to initialize a session.
///
/// - Note: This property controls only the force quit keyboard shortcuts. Setting it to `false` does not remove the Force Quit item from the Apple menu. Use ``AEAssessmentConfiguration/allowedAppleMenuItems`` to configure the allowed Apple menu items.
///
@property (nonatomic, assign) BOOL allowsForceQuit API_AVAILABLE(macos(27.0), macCatalyst(27.0)) API_UNAVAILABLE(ios);

/// The set of allowed directories and files that participants can access during an assessment.
///
/// By default, participants have restricted file system access. Use this property to specify file URLs to directories and files that should be accessible during the assessment session.
///
/// The default value is `nil`, which preserves the default unrestricted access behavior.
///
@property (nonatomic, copy, nullable) NSSet<NSURL *> *allowedDirectoriesAndFiles API_AVAILABLE(macos(27.0), macCatalyst(27.0)) API_UNAVAILABLE(ios);

/// A Boolean value that indicates whether to allow the Dock during an assessment.
///
/// An assessment session hides the Dock by default, but you can allow it by setting ``AEAssessmentConfiguration/allowsDock`` to `true` in the ``AEAssessmentConfiguration`` instance that you use to initialize a session.
///
@property (nonatomic, assign) BOOL allowsDock API_AVAILABLE(macos(27.0), macCatalyst(27.0)) API_UNAVAILABLE(ios);

/// A Boolean value that indicates whether to allow the menu bar during an assessment.
///
/// An assessment session hides the menu bar by default, but you can allow it by setting ``AEAssessmentConfiguration/allowsMenuBar`` to `true` in the ``AEAssessmentConfiguration`` instance that you use to initialize a session.
///
@property (nonatomic, assign) BOOL allowsMenuBar API_AVAILABLE(macos(27.0), macCatalyst(27.0)) API_UNAVAILABLE(ios);

/// The set of allowed Apple menu items during an assessment.
///
/// By default, all Apple menu items are restricted during an assessment. Use this property
/// to specify which menu items should be accessible.
///
/// - Note: ``AEAppleMenuItemAboutThisMac`` is always visible during assessment sessions regardless of configuration.
@property (nonatomic, copy, nullable) NSSet<AEAppleMenuItem> *allowedAppleMenuItems API_AVAILABLE(macos(27.0), macCatalyst(27.0)) API_UNAVAILABLE(ios);

/// The set of menu bar items that should remain visible during an assessment.
///
/// When `allowsMenuBar` is `true`, the menu bar is restricted to only the items
/// specified in this set. If this property is `nil`, all menu bar items are allowed
/// (unrestricted menu bar).
///
/// - Note: This property only takes effect when `allowsMenuBar` is `true`.
@property (nonatomic, copy, nullable) NSSet<AEMenuBarItem> *allowedMenuBarItems API_AVAILABLE(macos(27.0), macCatalyst(27.0)) API_UNAVAILABLE(ios);

/// A Boolean value that indicates whether only participant applications are allowed to run during an assessment.
///
@property (nonatomic, assign) BOOL allowOnlyParticipantsToRun API_AVAILABLE(macos(27.0), macCatalyst(27.0)) API_UNAVAILABLE(ios);

#pragma mark Enablement Requirements

/// A Boolean value that indicates whether the assessment allows Lockdown Mode to be active.
///
/// When set to `false`, the assessment session will only start if Lockdown Mode is not enabled on the device. This requirement is not enforced by default.
///
@property (nonatomic, assign) BOOL allowLockdownMode API_AVAILABLE(macos(27.0), macCatalyst(27.0)) API_UNAVAILABLE(ios);

/// A Boolean value that indicates whether the assessment allows iCloud Private Relay to be active.
///
/// When set to `false`, the assessment session will only start if iCloud Private Relay is not enabled. This requirement is not enforced by default.
///
@property (nonatomic, assign) BOOL allowPrivateRelay API_AVAILABLE(macos(27.0), macCatalyst(27.0)) API_UNAVAILABLE(ios);

/// A Boolean value that indicates whether the assessment allows running inside a virtual machine.
///
/// When set to `false`, the assessment session will only start if the device is not a virtual machine. This requirement is not enforced by default; virtual machines are allowed unless you opt out.
///
/// > Important: This check is advisory, not a security guarantee. Setting `allowVirtualMachine` to `false` may not block an assessment session in every virtualized environment. Use this property to steer proctored exams toward physical hardware; it doesn't provide a cryptographic attestation that the session is running on a physical machine.
///
/// For stronger assurances about the runtime environment, pair this property with
/// [App Attest](https://developer.apple.com/documentation/DeviceCheck) on macOS.
///
@property (nonatomic, assign) BOOL allowVirtualMachine API_AVAILABLE(macos(27.0), macCatalyst(27.0)) API_UNAVAILABLE(ios);

/// A Boolean value that indicates whether the device must be managed to start an assessment.
///
/// When set to `true`, the assessment session will only start if the device is enrolled in a Mobile Device Management (MDM) solution. This requirement is disabled by default.
///
@property (nonatomic, assign) BOOL requiresManagedDevice API_AVAILABLE(macos(27.0), macCatalyst(27.0)) API_UNAVAILABLE(ios);

/// A Boolean value that indicates whether System Integrity Protection (SIP) must be enabled to start an assessment.
///
/// When set to `true`, the assessment session will only start if System Integrity Protection is enabled on the device. This requirement is disabled by default.
///
/// > Important: This check is advisory, not a security guarantee. The framework can't reliably detect whether SIP is enabled on systems where the user has administrator privileges, so setting `requiresSIP` to `true` may not block an assessment session when SIP is in fact disabled. Use this property to prompt users to re-enable SIP if they turned it off for unrelated reasons; it doesn't indicate whether the system was modified while SIP was previously disabled.
///
/// For stronger assurances that SIP is enabled, pair this property with [App Attest](https://developer.apple.com/documentation/DeviceCheck) on macOS.
///
@property (nonatomic, assign) BOOL requiresSIP API_AVAILABLE(macos(27.0), macCatalyst(27.0)) API_UNAVAILABLE(ios);

/// A Boolean value that indicates whether only a single user account must be logged in to start an assessment.
///
/// When set to `true`, the assessment session will only start if there is exactly one user account logged in on the device. This requirement is disabled by default.
///
@property (nonatomic, assign) BOOL requiresSingleUser API_AVAILABLE(macos(27.0), macCatalyst(27.0)) API_UNAVAILABLE(ios);

/// Specifies the type of user account required to start an assessment.
///
/// This property defines the account requirement for starting an assessment session. Set it to `.standard` to require a non-administrator account, `.guest` to require a guest account, or `.any` (the default) to allow any account type.
///
@property (nonatomic, assign) AEUserAccountType requiresUserAccountType API_AVAILABLE(macos(27.0), macCatalyst(27.0)) API_UNAVAILABLE(ios);

/// The app-specific configuration for the app that invokes the assessment.
///
/// Use this property to get and customize the app-specific configuration that's applied to your own app. For example, you can set the `allowsNetworkAccess` property for your own app:
///
/// ```swift
/// let config = AEAssessmentConfiguration()
/// config.mainParticipantConfiguration.allowsNetworkAccess = false
/// ```
///
@property (nonatomic, strong, readonly) AEAssessmentParticipantConfiguration *mainParticipantConfiguration API_AVAILABLE(ios(17.5), macCatalyst(15.0), macos(12.0));

/// The collection of apps available during an assessment, along with their associated configurations.
///
/// Access this property to get a list of the currently allowed secondary apps and their individual configurations. Add apps to the list by calling the ``AEAssessmentConfiguration/setConfiguration(_:for:)`` method. Remove them from the list by calling the ``AEAssessmentConfiguration/remove(_:)`` method.
///
@property (nonatomic, copy, readonly) NSDictionary<AEAssessmentApplication *, AEAssessmentParticipantConfiguration *> *configurationsByApplication API_AVAILABLE(ios(17.5), macCatalyst(15.0), macos(12.0));

/// Adds an app to the list of apps available during an assessment.
///
/// Use this method to make an app besides your own available during an assessment. Create a representation of the app that you want to allow as an ``AEAssessmentApplication`` instance, and the configuration for that app using an ``AEAssessmentParticipantConfiguration`` instance:
///
/// ```swift
/// let calculator = AEAssessmentApplication(bundleIdentifier: "com.apple.calculator")
/// let calculatorConfig = AEAssessmentParticipantConfiguration()
/// calculatorConfig.allowsNetworkAccess = false // Calculator doesn't need the network.
/// ```
///
/// Use the app and its configuration to create an assessment configuration, and either create an assessment session with that, or update an existing session as shown below:
///
/// ```swift
/// let configuration = AEAssessmentConfiguration()
/// configuration.setConfiguration(calculatorConfig, for: calculator)
/// session.update(to: configuration)
/// ```
///
/// You can get a list of the currently allowed apps by accessing the ``AEAssessmentConfiguration/configurationsByApplication`` property. You can disallow a previously allowed app by using the ``AEAssessmentConfiguration/remove(_:)`` method.
///
/// - Parameters:
///   - configuration: The configuration of the secondary app.
///   - application: The app that you want to configure.
///
- (void)setConfiguration:(AEAssessmentParticipantConfiguration *)configuration forApplication:(AEAssessmentApplication *)application API_AVAILABLE(ios(17.5), macCatalyst(15.0), macos(12.0));

/// Removes the availability of a previously allowed app.
///
/// Use this method to remove apps that you previously added to the list of apps that are available during an assessment with the ``AEAssessmentConfiguration/setConfiguration(_:for:)`` method. You can get the list of currently allowed apps by accessing the configuration's ``AEAssessmentConfiguration/configurationsByApplication`` property.
///
/// - Parameters:
///   - application: The app that you want to remove from the list of allowed secondary apps.
///
- (void)removeApplication:(AEAssessmentApplication *)application API_AVAILABLE(ios(17.5), macCatalyst(15.0), macos(12.0));

/// The collection of executable participants available during an assessment, along with their associated configurations.
///
/// Add executables with ``AEAssessmentConfiguration/setConfiguration(_:for:)-(AEAssessmentBinaryExecutableConfiguration,_)`` and remove them with ``AEAssessmentConfiguration/removeBinaryExecutable(_:)``.
///
/// - SeeAlso: ``AEAssessmentBinaryExecutable``
@property (nonatomic, copy, readonly) NSDictionary<AEAssessmentBinaryExecutable *, AEAssessmentBinaryExecutableConfiguration *> *configurationsByBinaryExecutable API_AVAILABLE(macCatalyst(27.0), macos(27.0)) API_UNAVAILABLE(ios);

/// Adds an executable participant to the list of participants available during an assessment.
///
/// - Parameters:
///   - configuration: The configuration of the executable participant.
///   - binaryExecutable: The executable that you want to configure.
///
/// - SeeAlso: ``AEAssessmentBinaryExecutable``
- (void)setConfiguration:(AEAssessmentBinaryExecutableConfiguration *)configuration forBinaryExecutable:(AEAssessmentBinaryExecutable *)binaryExecutable API_AVAILABLE(macCatalyst(27.0), macos(27.0)) API_UNAVAILABLE(ios);

/// Removes the availability of a previously added executable participant.
///
/// - Parameters:
///   - binaryExecutable: The executable that you want to remove from the list of allowed participants.
///
- (void)removeBinaryExecutable:(AEAssessmentBinaryExecutable *)binaryExecutable API_AVAILABLE(macCatalyst(27.0), macos(27.0)) API_UNAVAILABLE(ios);

@end

NS_ASSUME_NONNULL_END
