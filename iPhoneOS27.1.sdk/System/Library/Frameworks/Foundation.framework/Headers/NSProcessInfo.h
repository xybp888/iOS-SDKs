/*	NSProcessInfo.h
	Copyright (c) 1994-2019, Apple Inc. All rights reserved.
 */

#import <Foundation/NSObject.h>
#import <Foundation/NSDate.h>
#import <Foundation/NSNotification.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

/// Constants returned by ``ProcessInfo/operatingSystem`` to indicate the operating system.
enum {
    /// Indicates the Windows NT operating system.
    NSWindowsNTOperatingSystem = 1,
    /// Indicates the Windows 95 operating system.
    NSWindows95OperatingSystem,
    /// Indicates the Solaris operating system.
    NSSolarisOperatingSystem,
    /// Indicates the HP-UX operating system.
    NSHPUXOperatingSystem,
    /// Indicates the macOS operating system.
    NSMACHOperatingSystem,
    /// Indicates the SunOS operating system.
    NSSunOSOperatingSystem,
    /// Indicates the OSF/1 operating system.
    NSOSF1OperatingSystem
} API_DEPRECATED("Not supported", macos(10.0,10.10), ios(2.0,8.0), watchos(2.0,2.0), tvos(9.0,9.0));

/// A structure that contains version information about the currently executing operating system, including major, minor, and patch version numbers.
///
/// Use the ``ProcessInfo`` property ``ProcessInfo/operatingSystemVersion`` to fetch an instance of this type. You can also pass this type to ``ProcessInfo/isOperatingSystemAtLeast(_:)`` to determine whether the current operating system version is the same or later than the given value.
typedef struct NS_SWIFT_SENDABLE {
    /// The major release number, such as 10 in version 10.9.3.
    NSInteger majorVersion;
    /// The minor release number, such as 9 in version 10.9.3.
    NSInteger minorVersion;
    /// The update release number, such as 3 in version 10.9.3.
    NSInteger patchVersion;
} NSOperatingSystemVersion;

@class NSArray<ObjectType>, NSString, NSDictionary<KeyType, ObjectType>;

/// A collection of information about the current process.
///
/// Each process has a single, shared ``ProcessInfo`` object known as a _process information agent_ that can return information such as arguments, environment variables, host name, and process name. The ``processInfo`` class method returns the shared agent for the current process. For example, the following line returns the ``ProcessInfo`` object, which then provides the name of the current process:
///
/// @TabNavigator {
/// @Tab("Swift") {
/// ```swift
/// let processName = ProcessInfo.processInfo.processName
/// ```
/// }
/// @Tab("Objective-C") {
/// ```objc
/// NSString *processName = [[NSProcessInfo processInfo] processName];
/// ```
/// }
/// }
///
///
/// > Note:
/// > ``ProcessInfo`` is thread-safe in macOS 10.7 and later.
///
/// The ``ProcessInfo`` class also includes the ``operatingSystemVersion`` property, which returns an ``OperatingSystemVersion`` structure identifying the operating system version on which the process is executing.
///
/// ``ProcessInfo`` objects attempt to interpret environment variables and command-line arguments in the user's default C string encoding if they can't convert to Unicode as UTF-8 strings. If neither the Unicode nor C string conversion works, the ``ProcessInfo`` object ignores these values.
///
/// ### Manage Activities
///
/// The system has heuristics to improve battery life, performance, and responsiveness of applications for the benefit of the user. You can use the following methods to manage _activities_ that give hints to the system that your application has special requirements:
///
/// - ``beginActivity(options:reason:)``
/// - ``endActivity(_:)``
/// - ``performActivity(options:reason:using:)``
///
/// In response to creating an activity, the system disables some or all of the heuristics so your application can finish quickly while still providing responsive behavior if the user needs it.
///
/// You use activities when your application performs a long-running operation. If the activity can take different amounts of time (for example, calculating the next move in a chess game), it should use this API to ensure correct behavior when the amount of data or the capabilities of the user's computer varies. Activities fall into two major categories:
///
/// - _User-initiated_ activities are explicitly started by the user. Examples include exporting or downloading a user-specified file.
/// - _Background_ activities perform the normal operations of your application and aren't explicitly started by the user. Examples include autosaving, indexing, and automatic downloading of files.
///
/// In addition, if your application requires high priority input/output (I/O), you can include the ``ActivityOptions/latencyCritical`` flag (using a bitwise `OR`). You should only use this flag for activities like audio or video recording that require high priority I/O.
///
/// If your activity takes place synchronously inside an event callback on the main thread, you don't need to use this API.
///
/// Be aware that failing to end these activities for an extended period of time can have significant negative impacts on the performance of your user's computer, so be sure to use only the minimum amount of time required. User preferences may override your application's request.
///
/// You can also use this API to control automatic termination or sudden termination (see <doc:#Support-Sudden-Termination>). For example, the following code brackets the work to protect it from sudden termination:
///
/// @TabNavigator {
/// @Tab("Swift") {
/// ```swift
/// let activity = ProcessInfo.processInfo.beginActivity(
/// options: .automaticTerminationDisabled,
/// reason: "Good Reason")
/// // Perform some work.
/// ProcessInfo.processInfo.endActivity(activity)
/// ```
/// }
/// @Tab("Objective-C") {
/// ```objc
/// id activity = [[NSProcessInfo processInfo] beginActivityWithOptions:NSActivityAutomaticTerminationDisabled reason:@"Good Reason"];
/// // Perform some work.
/// [[NSProcessInfo processInfo] endActivity:activity];
/// ```
/// }
/// }
///
///
///
///
/// The above example is equivalent to the following code, which uses the ``disableAutomaticTermination(_:)`` method:
///
/// @TabNavigator {
/// @Tab("Swift") {
/// ```swift
/// ProcessInfo.processInfo.disableAutomaticTermination("Good Reason")
/// // Perform some work.
/// ProcessInfo.processInfo.enableAutomaticTermination("Good Reason")
/// ```
/// }
/// @Tab("Objective-C") {
/// ```objc
/// [[NSProcessInfo processInfo] disableAutomaticTermination:@"Good Reason"];
/// // Perform some work.
/// [[NSProcessInfo processInfo] enableAutomaticTermination:@"Good Reason"];
/// ```
/// }
/// }
///
///
/// Because this API returns an object, it may be easier to pair begins and ends than when using the automatic termination API. If your app deallocates the object before the ``endActivity(_:)`` call, the activity ends automatically.
///
/// This API also provides a mechanism to disable system-wide idle sleep and display idle sleep. These can have a large impact on the user experience, so be careful to end activities that disable sleep (including ``ActivityOptions/userInitiated``).
///
/// ### Support Sudden Termination
///
/// macOS 10.6 and later includes a mechanism that allows the system to log out or shut down more quickly by, whenever possible, killing applications instead of requesting that they quit themselves.
///
/// Your application can enable this capability on a global basis and then manually override its availability during actions that could cause data corruption or a poor user experience by allowing sudden termination.
///
/// Alternatively, your application can manually enable and disable this functionality. Creating a process assigns a counter that indicates if the process is safe to terminate. You decrement and increment the counter using the methods ``enableSuddenTermination()`` and ``disableSuddenTermination()``. A value of `0` enables the system to terminate the process without first sending a notification or event.
///
/// Your application can support sudden termination upon launch by adding a key to the application's `Info.plist` file. If the <doc://com.apple.documentation/documentation/bundleresources/information-property-list/nssupportssuddentermination> key exists in the `Info.plist` file and has a value of <doc://com.apple.documentation/documentation/swift/true>, it's the equivalent of calling ``enableSuddenTermination()`` during your application launch. This allows the system to terminate the process immediately. You can still override this behavior by invoking ``disableSuddenTermination()``.
///
/// Typically, you disable sudden termination whenever your app defers work that the app must complete before it terminates. If, for example, your app defers writing data to disk and enables sudden termination, you should bracket the sensitive operations with a call to ``disableSuddenTermination()``, perform the necessary operations, and then send a balancing ``enableSuddenTermination()`` message.
///
/// In agents or daemon executables that don't depend on AppKit, you can manually invoke ``enableSuddenTermination()`` right away. You can then use the enable and disable methods whenever the process has work it must do before it terminates.
///
/// Some AppKit functionality automatically disables sudden termination on a temporary basis to ensure data integrity.
///
/// - ``UserDefaults`` temporarily disables sudden termination to prevent the process from terminating between the time at which it sets the default and the time at which it writes the preferences file — including that default — to disk.
/// - <doc://com.apple.documentation/documentation/appkit/nsdocument> temporarily disables sudden termination to prevent the process from terminating between the time at which the user has made a change to a document and the time at which <doc://com.apple.documentation/documentation/appkit/nsdocument> writes the user's change to disk.
///
/// > Tip:
/// > You can determine the value of the sudden termination using the following LLDB command.
/// >
/// > ```objc
/// > print (long)[[NSClassFromString(@"NSProcessInfo") processInfo] _suddenTerminationDisablingCount]
/// > ```
/// >
/// > Don't attempt to invoke or override `suddenTerminationDisablingCount` (a private method) in your application. It's there for this debugging purpose and may disappear at any time.
///
/// ### Monitor Thermal State to Adjust App Performance
///
/// _Thermal state_ indicates the level of heat generated by logic components as they run apps. As the thermal state increases, the system decreases heat by reducing the speed of the processors. Optimize your app's performance by monitoring the thermal state and reducing system usage as the thermal state increases. Query the current state with ``thermalState`` to determine if your app needs to reduce system usage. You can register the ``thermalStateDidChangeNotification`` for notifications of a change in thermal state. For recommended actions, see ``ThermalState``.
NS_SWIFT_SENDABLE
@interface NSProcessInfo : NSObject {
@private
    NSDictionary	*environment;
    NSArray		*arguments;
    NSString		*hostName;
    NSString		*name;
    NSInteger		automaticTerminationOptOutCounter;
}

/// Returns the process information agent for the process.
///
/// An `NSProcessInfo` object is created the first time this property is accessed, and that same object is returned on each subsequent access.
@property (class, readonly, strong) NSProcessInfo *processInfo;

/// The variable names (keys) and their values in the environment from which the process was launched.
@property (readonly, copy) NSDictionary<NSString *, NSString *> *environment;

/// Array of strings with the command-line arguments for the process.
///
/// This array contains all the information passed in the `argv` array, including the executable name in the first element.
@property (readonly, copy) NSArray<NSString *> *arguments;

/// The name of the host computer on which the process is executing.
@property (readonly, copy) NSString *hostName;

/// The name of the process.
///
/// The process name is used to register application defaults and is used in error messages. It does not uniquely identify the process.
///
/// > Warning:
/// > User defaults and other aspects of the environment might depend on the process name, so be very careful if you change it. Setting the process name in this manner is not thread safe.
@property (copy) NSString *processName;

/// The identifier of the process (often called process ID).
@property (readonly) int processIdentifier;

/// Global unique identifier for the process.
///
/// The global ID for the process includes the host name, process ID, and a time stamp, which ensures that the ID is unique for the network. This property generates a new string each time its getter is invoked, and it uses a counter to guarantee that strings created from the same process are unique.
@property (readonly, copy) NSString *globallyUniqueString;

/// Returns a constant to indicate the operating system on which the process is executing.
///
/// @DeprecationSummary {
///     Use ``ProcessInfo/operatingSystemVersion`` or ``ProcessInfo/isOperatingSystemAtLeast(_:)`` instead
/// }
///
/// - Returns: Operating system identifier. In macOS, it's `NSMACHOperatingSystem`.
- (NSUInteger)operatingSystem API_DEPRECATED("-operatingSystem always returns NSMACHOperatingSystem, use -operatingSystemVersion or -isOperatingSystemAtLeastVersion: instead", macos(10.0,10.10), ios(2.0,8.0), watchos(2.0,2.0), tvos(9.0,9.0));
/// Returns a string containing the name of the operating system on which the process is executing.
///
/// @DeprecationSummary {
///     Use ``ProcessInfo/operatingSystemVersionString`` instead.
/// }
///
/// - Returns: Operating system name. In macOS, it's `@"NSMACHOperatingSystem"`.
- (NSString *)operatingSystemName API_DEPRECATED("-operatingSystemName always returns NSMACHOperatingSystem, use -operatingSystemVersionString instead", macos(10.0,10.10), ios(2.0,8.0), watchos(2.0,2.0), tvos(9.0,9.0));

/// A string containing the version of the operating system on which the process is executing.
///
/// The operating system version string is human readable, localized, and is appropriate for displaying to the user. This string is _not_ appropriate for parsing.
@property (readonly, copy) NSString *operatingSystemVersionString;

/// The version of the operating system on which the process is executing.
@property (readonly) NSOperatingSystemVersion operatingSystemVersion API_AVAILABLE(macos(10.10), ios(8.0), watchos(2.0), tvos(9.0));

/// The number of processing cores available on the computer.
///
/// This property value is equal to the result of entering the command `sysctl -n hw.ncpu` on the current system.
@property (readonly) NSUInteger processorCount API_AVAILABLE(macos(10.5), ios(2.0), watchos(2.0), tvos(9.0));

/// The number of active processing cores available on the computer.
///
/// Whereas the ``processorCount`` property reports the number of advertised processing cores, the ``activeProcessorCount`` property reflects the actual number of active processing cores on the system. There are a number of different factors that may cause a core to not be active, including boot arguments, thermal throttling, or a manufacturing defect.
///
/// This property value is equal to the result of entering the command `sysctl -n hw.logicalcpu` on the current system.
@property (readonly) NSUInteger activeProcessorCount API_AVAILABLE(macos(10.5), ios(2.0), watchos(2.0), tvos(9.0));

/// The amount of physical memory on the computer in bytes.
@property (readonly) unsigned long long physicalMemory API_AVAILABLE(macos(10.5), ios(2.0), watchos(2.0), tvos(9.0));

/// Returns a Boolean value indicating whether the version of the operating system on which the process is executing is the same or later than the given version.
///
/// This method accounts for major, minor, and update versions of the operating system.
///
/// - Parameters:
///   - version: The operating system version to test against.
/// - Returns: `true` if the operating system on which the process is executing is the same or later than the given version; otherwise `false`.
- (BOOL) isOperatingSystemAtLeastVersion:(NSOperatingSystemVersion)version API_AVAILABLE(macos(10.10), ios(8.0), watchos(2.0), tvos(9.0));

/// The amount of time the system has been awake since the last time it was restarted.
///
/// > Important:
/// > This API has the potential of being misused to access device signals to try to identify the device or user, also known as fingerprinting. Regardless of whether a user gives your app permission to track, fingerprinting is not allowed. When you use this API in your app or third-party SDK (an SDK not provided by Apple), declare your usage and the reason for using the API in your app or third-party SDK's `PrivacyInfo.xcprivacy` file. For more information, including the list of valid reasons for using the API, see [Describing use of required reason API](https://developer.apple.com/documentation/bundleresources/describing-use-of-required-reason-api).
@property (readonly) NSTimeInterval systemUptime API_AVAILABLE(macos(10.6), ios(4.0), watchos(2.0), tvos(9.0));

/// Disables the application for quick killing using sudden termination.
///
/// This method increments the sudden termination counter. When the termination counter reaches `0` the application allows sudden termination.
///
/// By default the sudden termination counter is set to 1. This can be overridden in your application Info.plist. See <doc:ProcessInfo#Support-Sudden-Termination> for more information and debugging suggestions.
- (void)disableSuddenTermination API_AVAILABLE(macos(10.6)) API_UNAVAILABLE(ios, watchos, tvos);
/// Enables the application for quick killing using sudden termination.
///
/// This method decrements the sudden termination counter. When the termination counter reaches `0` the application allows sudden termination.
///
/// By default the sudden termination counter is set to 1. This can be overridden in your application Info.plist. See <doc:ProcessInfo#Support-Sudden-Termination> for more information and debugging suggestions.
- (void)enableSuddenTermination API_AVAILABLE(macos(10.6)) API_UNAVAILABLE(ios, watchos, tvos);

/// Disables automatic termination for the application.
///
/// This method increments the automatic termination counter. When the counter is greater than `0`, the application is considered active and ineligible for automatic termination. For example, you could disable automatic termination when the user of an instant messaging application signs on, because the application requires a background connection to be maintained even if the application is otherwise inactive.
///
/// The reason parameter is used to track why an application is or is not automatically terminable and can be inspected by debugging tools. A given reason can be used more than once at the same time.
///
/// - Parameters:
///   - reason: The reason why automatic termination is being disabled.
- (void)disableAutomaticTermination:(NSString *)reason API_AVAILABLE(macos(10.7)) API_UNAVAILABLE(ios, watchos, tvos);
/// Enables automatic termination for the application.
///
/// This method decrements the automatic termination counter. When the counter is `0`, the application is eligible for automatic termination.
///
/// The reason parameter is used to track why an application is or is not automatically terminable and can be inspected by debugging tools. A given reason can be used more than once at the same time.
///
/// - Parameters:
///   - reason: The reason why automatic termination is being enabled.
- (void)enableAutomaticTermination:(NSString *)reason API_AVAILABLE(macos(10.7)) API_UNAVAILABLE(ios, watchos, tvos);

/// A Boolean value indicating whether the app supports automatic termination.
///
/// Without setting this property or setting the equivalent `Info.plist` key (`NSSupportsAutomaticTermination`), the methods ``disableAutomaticTermination:`` and ``enableAutomaticTermination:`` have no effect, although the counter tracking automatic termination opt-outs is still kept up to date to ensure correctness if this is called later. Currently, setting this property to `NO` has no effect. This property should be set during `-applicationDidFinishLaunching:` or earlier.
@property BOOL automaticTerminationSupportEnabled API_AVAILABLE(macos(10.7)) API_UNAVAILABLE(ios, watchos, tvos);

@end

/*
 The system has heuristics to improve battery life, performance, and responsiveness of applications for the benefit of the user. This API can be used to give hints to the system that your application has special requirements. In response to creating one of these activities, the system will disable some or all of the heuristics so your application can finish quickly while still providing responsive behavior if the user needs it.
 
 These activities can be used when your application is performing a long-running operation. If the activity can take different amounts of time (for example, calculating the next move in a chess game), it should use this API. This will ensure correct behavior when the amount of data or the capabilities of the user's computer varies. You should put your activity into one of two major categories:
 
 User initiated: These are finite length activities that the user has explicitly started. Examples include exporting or downloading a user specified file.
 
 Background: These are finite length activities that are part of the normal operation of your application but are not explicitly started by the user. Examples include autosaving, indexing, and automatic downloading of files.
 
 In addition, if your application requires high priority IO, you can include the 'NSActivityLatencyCritical' flag (using a bitwise or). This should be reserved for activities like audio or video recording.
 
 If your activity takes place synchronously inside an event callback on the main thread, you do not need to use this API.
 
 Be aware that failing to end these activities for an extended period of time can have significant negative impacts to the performance of your user's computer, so be sure to use only the minimum amount of time required. User preferences may override your application’s request.
 
 This API can also be used to control auto termination or sudden termination. 
 
    id activity = [NSProcessInfo.processInfo beginActivityWithOptions:NSActivityAutomaticTerminationDisabled reason:@"Good Reason"];
    // work
    [NSProcessInfo.processInfo endActivity:activity];
 
 is equivalent to:
 
    [NSProcessInfo.processInfo disableAutomaticTermination:@"Good Reason"];
    // work
    [NSProcessInfo.processInfo enableAutomaticTermination:@"Good Reason"]
 
 Since this API returns an object, it may be easier to pair begins and ends. If the object is deallocated before the -endActivity: call, the activity will be automatically ended.
 
 This API also provides a mechanism to disable system-wide idle sleep and display idle sleep. These can have a large impact on the user experience, so be sure not to forget to end activities that disable sleep (including NSActivityUserInitiated).
 
 */

/// Option flags used with ``ProcessInfo/beginActivity(options:reason:)`` and ``ProcessInfo/performActivity(options:reason:using:)``.
typedef NS_OPTIONS(uint64_t, NSActivityOptions) {
    // To include one of these individual flags in one of the sets, use bitwise or:
    //   NSActivityUserInitiated | NSActivityIdleDisplaySleepDisabled
    // (this may be used during a presentation, for example)
    
    // To exclude from one of the sets, use bitwise and with not:
    //   NSActivityUserInitiated & ~NSActivitySuddenTerminationDisabled
    // (this may be used during a user intiated action that may be safely terminated with no application interaction in case of logout)

    /// A flag to require the screen to stay powered on.
    NSActivityIdleDisplaySleepDisabled = (1ULL << 40),

    /// A flag to prevent idle sleep.
    ///
    /// This is negated by `NSActivityUserInitiatedAllowingIdleSystemSleep`.
    NSActivityIdleSystemSleepDisabled = (1ULL << 20),

    /// A flag to prevent sudden termination.
    ///
    /// This is included by `NSActivityUserInitiatedAllowingIdleSystemSleep`.
    NSActivitySuddenTerminationDisabled = (1ULL << 14),

    /// A flag to prevent automatic termination.
    ///
    /// This is included by `NSActivityUserInitiatedAllowingIdleSystemSleep`.
    NSActivityAutomaticTerminationDisabled = (1ULL << 15),

    /// A flag to track the activity with an animation signpost interval.
    ///
    /// Use this to track the timing of a user interaction by annotating the beginning and end of an activity using an animation signpost interval. This differs from `NSActivityTrackingEnabled` in the type of interval signposts the logging system emits. Use this when the interaction involves an animation.
    NSActivityAnimationTrackingEnabled API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0)) =
    (1ULL << 45),

    /// A flag to track the activity with a signpost interval.
    ///
    /// Use this to track the timing of a user interaction by annotating the beginning and end of an activity using a signpost interval. This differs from `NSActivityAnimationTrackingEnabled` in the type of interval signposts the logging system emits. Use `NSActivityAnimationTrackingEnabled` when the interaction involves an animation.
    NSActivityTrackingEnabled API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0)) = (1ULL << 46),
    
    // ----
    // Sets of options.

    /// A flag to indicate the app is performing a user-requested action.
    ///
    /// Examples of user initiated actions are exporting or downloading a user-specified file or dismissing a form sheet.
    NSActivityUserInitiated = (0x00FFFFFFULL | NSActivityIdleSystemSleepDisabled),
    /// A flag to indicate the app is performing a user-requested action, but that the system can sleep on idle.
    NSActivityUserInitiatedAllowingIdleSystemSleep = (NSActivityUserInitiated & ~NSActivityIdleSystemSleepDisabled),

    /// A flag to indicate the app has initiated some kind of work, but not as the direct result of user request.
    NSActivityBackground = 0x000000FFULL,

    /// A flag to indicate the activity requires the highest amount of timer and I/O precision available.
    ///
    /// Very few applications should need to use this constant.
    NSActivityLatencyCritical = 0xFF00000000ULL,
    /// A flag to indicate the app is responding to user interaction.
    ///
    /// Examples of user-interactive actions include scrolling and interactively dismissing from a navigation controller.
    NSActivityUserInteractive API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0)) =
    (NSActivityUserInitiated | NSActivityLatencyCritical),
} API_AVAILABLE(macos(10.9), ios(7.0), watchos(2.0), tvos(9.0));

@interface NSProcessInfo (NSProcessInfoActivity)
/// Begins an activity using the given options and reason.
///
/// Indicate completion of the activity by calling ``endActivity(_:)`` passing the returned object as the argument.
///
/// - Parameters:
///   - options: Options for the activity. See ``ProcessInfo/ActivityOptions`` for possible values.
///   - reason: A string used in debugging to indicate the reason the activity began.
/// - Returns: An object token representing the activity.
- (id <NSObject>)beginActivityWithOptions:(NSActivityOptions)options reason:(NSString *)reason API_AVAILABLE(macos(10.9), ios(7.0), watchos(2.0), tvos(9.0));

/// Ends the given activity.
///
/// - Parameters:
///   - activity: An activity object returned by ``beginActivity(options:reason:)``.
- (void)endActivity:(id <NSObject>)activity API_AVAILABLE(macos(10.9), ios(7.0), watchos(2.0), tvos(9.0));

/// Synchronously performs an activity defined by a given block using the given options.
///
/// The activity will be automatically ended after `block` returns.
///
/// - Parameters:
///   - options: Options for the activity. See ``ProcessInfo/ActivityOptions`` for possible values.
///   - reason: A string used in debugging to indicate the reason the activity began.
///   - block: A block containing the work to be performed by the activity.
- (void)performActivityWithOptions:(NSActivityOptions)options reason:(NSString *)reason usingBlock:(void (^)(void))block API_AVAILABLE(macos(10.9), ios(7.0), watchos(2.0), tvos(9.0));

/// Performs the specified block asynchronously and notifies you if the process is about to be suspended.
///
/// Use this method to perform tasks when your process is executing in the background. This method queues `block` for asynchronous execution on a concurrent queue. When your process is in the background, the method tries to take a task assertion to ensure that your block has time to execute. If it is unable to take a task assertion, or if the time allotted for the task assertion expires, the system executes your block with the parameter set to `YES`. If it is able to take the task assertion, it executes the block and passes `NO` for the expired parameter.
///
/// If your block is still executing and the system needs to suspend the process, the system executes your block a second time with the `expired` parameter set to `YES`. Your block must be prepared to handle this case. When the expired parameter is `YES`, stop any in-progress tasks as quickly as possible.
///
/// - Parameters:
///   - reason: A string used in debugging to indicate the reason the activity began. This parameter must not be `nil` or an empty string.
///   - block: A block containing the work to be performed by the activity. The block takes a Boolean parameter indicating whether the process is about to be suspended.
- (void)performExpiringActivityWithReason:(NSString *)reason usingBlock:(void(NS_SWIFT_SENDABLE ^)(BOOL expired))block API_AVAILABLE(ios(8.2), watchos(2.0), tvos(9.0)) API_UNAVAILABLE(macos);

@end

@interface NSProcessInfo (NSUserInformation)

/// Returns the account name of the current user.
@property (readonly, copy) NSString *userName API_AVAILABLE(macosx(10.12)) API_UNAVAILABLE(ios, watchos, tvos);

/// Returns the full name of the current user.
@property (readonly, copy) NSString *fullUserName API_AVAILABLE(macosx(10.12)) API_UNAVAILABLE(ios, watchos, tvos);

@end

/// Values used to indicate the system's thermal state.
///
/// These values are used by the ``ProcessInfo`` class as return values for ``ProcessInfo/thermalState``.
///
/// For information about testing your app under different thermal states, see [Test under adverse device conditions](https://help.apple.com/xcode/mac/current/#/dev308429d42).
typedef NS_ENUM(NSInteger, NSProcessInfoThermalState) {
    /// The thermal state is within normal limits.
    NSProcessInfoThermalStateNominal,

    /// The thermal state is slightly elevated.
    ///
    /// Reduce or defer background work, like prefetching content over the network or updating database indexes.
    NSProcessInfoThermalStateFair,

    /// The thermal state is high.
    ///
    /// Reduce usage of resources that generate heat and consume battery. Reduce CPU and GPU usage, reduce the target framerate, and reduce the level of detail in rendered content.
    NSProcessInfoThermalStateSerious,

    /// The thermal state is significantly impacting the performance of the system and the device needs to cool down.
    ///
    /// Reduce usage of the CPU, GPU, and I/O to the minimum level required for user interaction. If possible, stop using peripherals such as the camera, flash, microphone, and speaker.
    NSProcessInfoThermalStateCritical
} API_AVAILABLE(macosx(10.10.3), ios(11.0), watchos(4.0), tvos(11.0));

@interface NSProcessInfo (NSProcessInfoThermalState)

/// The current thermal state of the system.
///
/// At higher thermal states your app should reduce usage of system resources. For more information, see ``NSProcessInfoThermalState``.
@property (readonly) NSProcessInfoThermalState thermalState API_AVAILABLE(macosx(10.10.3), ios(11.0), watchos(4.0), tvos(11.0));

@end

@interface NSProcessInfo (NSProcessInfoPowerState)

/// A Boolean value that indicates the current state of Low Power Mode.
///
/// Users who wish to prolong their device's battery life can enable Low Power Mode under Settings > Battery. In Low Power Mode, the system conserves battery life by enacting certain energy-saving measures, such as:
///
/// - Reducing CPU and GPU performance.
/// - Reducing screen brightness.
/// - Pausing discretionary and background activities.
///
/// Your app can query the `isLowPowerModeEnabled` property at any time to determine whether Low Power Mode is active. Your app can also register to receive notifications when the Low Power Mode state of a device changes by observing ``NSProcessInfoPowerStateDidChangeNotification``.
@property (readonly, getter=isLowPowerModeEnabled) BOOL lowPowerModeEnabled API_AVAILABLE(macos(12.0), ios(9.0), watchos(2.0), tvos(9.0));

@end

/// Posts when the thermal state of the system changes.
///
/// The notification object is an `NSProcessInfo` instance.
///
/// To receive this notification, you must access the `thermalState` property prior to registering for the notification.
///
/// You can use this opportunity to take corrective action in your application to help cool the system down. Work that could be done in the background or at opportunistic times should be using the Quality of Service levels in `NSOperation` or the `NSBackgroundActivityScheduler` API.
///
/// This notification is posted on the global dispatch queue. Register for it using the default notification center.
FOUNDATION_EXTERN NSNotificationName const NSProcessInfoThermalStateDidChangeNotification API_AVAILABLE(macosx(10.10.3), ios(11.0), watchos(4.0), tvos(11.0));

/// Posts when the power state of a device changes.
///
/// After your observer receives this notification, query the `isLowPowerModeEnabled` property to determine the current power state of the device. If Low Power Mode is active, take appropriate steps to reduce activity in your app. Otherwise, your app can resume normal operations. This notification is posted on the global dispatch queue. Register for it using the default notification center. The object associated with the notification is `NSProcessInfo.processInfo`.
FOUNDATION_EXTERN NSNotificationName const NSProcessInfoPowerStateDidChangeNotification API_AVAILABLE(macos(12.0), ios(9.0), watchos(2.0), tvos(9.0));

@interface NSProcessInfo (NSProcessInfoPlatform)

/// A Boolean value that indicates whether the process originated as an iOS app and runs on macOS.
///
/// The value of this property is `YES` when the process is a Mac app built with Mac Catalyst, or an iOS app running on Apple silicon, and is running on a Mac. Frameworks that support iOS and macOS use this property to determine if the process is a Mac app built with Mac Catalyst.
///
/// > Note:
/// > To distinguish between an iOS app running on Apple silicon and a Mac app built with Mac Catalyst, use the ``isiOSAppOnMac`` property.
@property (readonly, getter=isMacCatalystApp) BOOL macCatalystApp API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0));

/// A Boolean value that indicates whether the process is an iPhone or iPad app running on a Mac.
///
/// The value of this property is `YES` only when the process is an iOS app running on a Mac. The value is `NO` for all other apps on the Mac, including Mac apps built using Mac Catalyst. The property is also `NO` for processes running on platforms other than macOS.
@property (readonly, getter=isiOSAppOnMac) BOOL iOSAppOnMac API_AVAILABLE(macos(11.0), ios(14.0), watchos(7.0), tvos(14.0));

/// A Boolean value that indicates whether the process is an iPhone or iPad app running on visionOS.
///
/// The value of this property is `YES` only when the process is an iOS app running on a visionOS device. The value is `NO` for all other apps on visionOS. The property is also `NO` for processes running on platforms other than visionOS.
@property (readonly, getter=isiOSAppOnVision) BOOL iOSAppOnVision API_AVAILABLE(macos(26.1), ios(26.1), watchos(26.1), tvos(26.1), visionos(26.1));

@end

NS_HEADER_AUDIT_END(nullability, sendability)
