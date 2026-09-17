/*	NSUserDefaults.h
	Copyright (c) 1994-2019, Apple Inc. All rights reserved.
 */

#import <Foundation/NSObject.h>
#import <Foundation/NSNotification.h>

@class NSArray<ObjectType>, NSData, NSDictionary<KeyValue, ObjectValue>, NSMutableDictionary, NSString, NSURL;

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

/// The identifier for the domain that contains system-specified settings for all apps.
FOUNDATION_EXPORT NSString * const NSGlobalDomain;
/// The identifier for the domain that contains command-line settings.
FOUNDATION_EXPORT NSString * const NSArgumentDomain;
/// The identifier for the domain that contains your app's registered default values.
FOUNDATION_EXPORT NSString * const NSRegistrationDomain;

/*
 NSUserDefaults is a hierarchical persistent interprocess (optionally distributed) key-value store, optimized for storing user settings.
 
 Hierarchical: NSUserDefaults has a list of places to look for data called the "search list". A search list is referred to by an arbitrary string called the "suite identifier" or "domain identifier". When queried, NSUserDefaults checks each entry of its search list until it finds one that contains the key in question, or has searched the whole list. The list is (note: "current host + current user" preferences are unimplemented on iOS, watchOS, and tvOS, and "any user" preferences are not generally useful for applications on those operating systems):
 - Managed ("forced") preferences, set by a configuration profile or via mcx from a network administrator
 - Commandline arguments
 - Preferences for the current domain, in the cloud
 - Preferences for the current domain, the current user, in the current host
 - Preferences for the current domain, the current user, in any host
 - Preferences added via -addSuiteNamed:
 - Preferences global to all apps for the current user, in the current host
 - Preferences global to all apps for the current user, in any host
 - Preferences for the current domain, for all users, in the current host
 - Preferences global to all apps for all users, in the current host
 - Preferences registered with -registerDefaults:
 
 Persistent: Preferences stored in NSUserDefaults persist across reboots and relaunches of apps unless otherwise specified.
 
 Interprocess: Preferences may be accessible to and modified from multiple processes simultaneously (for example between an application and an extension).
 
 Optionally distributed (Currently only supported in Shared iPad for Students mode):  Data stored in user defaults can be made "ubiqitous", i.e. synchronized between devices via the cloud.  Ubiquitous user defaults are automatically propagated to all devices logged into the same iCloud account. When reading defaults (via -*ForKey: methods on NSUserDefaults), ubiquitous defaults are searched before local defaults. All operations on ubiquitous defaults are asynchronous, so registered defaults may be returned in place of ubiquitous defaults if downloading from iCloud hasn't finished. Ubiquitous defaults are specified in the Defaults Configuration File for an application.
 
 Key-Value Store: NSUserDefaults stores Property List objects (NSString, NSData, NSNumber, NSDate, NSArray, and NSDictionary) identified by NSString keys, similar to an NSMutableDictionary.
 
 Optimized for storing user settings: NSUserDefaults is intended for relatively small amounts of data, queried very frequently, and modified occasionally. Using it in other ways may be slow or use more memory than solutions more suited to those uses.
 
 The 'App' CFPreferences functions in CoreFoundation act on the same search lists that NSUserDefaults does.
 
 NSUserDefaults can be observed using Key-Value Observing for any key stored in it. Using NSKeyValueObservingOptionPrior to observe changes from other processes or devices will behave as though NSKeyValueObservingOptionPrior was not specified.
 */


/// An interface to the user's defaults database, which stores system-wide and app-specific settings.
///
/// A `UserDefaults` object provides access to the defaults system, which is a persistent
/// store for app-specific and system-wide settings. You use this system to store nonsensitive
/// information, such as app-specific configuration details. The system also stores configuration
/// details that apply to all apps, such as the current language settings for the device. In
/// your code, you check values from this system and use them to dynamically alter your app's
/// appearance or behavior. The term *defaults* refers to the fact that the stored data determines
/// the default startup state and behavior.
///
/// > Important: Don't store personal or sensitive information as settings. The defaults
/// system stores information on disk in an unencrypted format. Store personal or sensitive
/// information in the person's Keychain instead.
///
/// To access the defaults system, obtain a `UserDefaults` object and call its methods to
/// read and write values. The ``standard`` object is a shared object you
/// use to read and write your app's standard settings. You can also create unique
/// `UserDefaults` objects to manage specific sets of settings. For example, you can
/// create a `UserDefaults` object that reads and writes settings your app shares
/// with an app extension. Don't subclass `UserDefaults`.
///
/// Each item you store in a defaults object consists of a key-value pair, where each
/// key is a string that you use to locate the item and each value is a data object.
/// The defaults database supports the same value types found in property list files,
/// including types like `Int`, `Float`, `Double`, `Bool`, `String`,
/// ``URL``, `NSNumber`, ``Date``, `Array`, and `Dictionary`. To include other
/// types of objects in the defaults database, archive them to a ``Data``
/// object first and store that object instead. Prefer simple types over custom objects whenever possible.
///
/// With the exception of managed devices in educational institutions, the system stores
/// defaults locally on the current device. When you write values to a `UserDefaults` object,
/// the object updates its in-memory version of that information right away, and writes
/// the value to disk asynchronously. When someone backs up their device, the system includes
/// any persistent defaults databases in the backup data. Because the data is device-specific,
/// you don't use the defaults system to share data between devices. To share data between
/// someone's devices, use the ``NSUbiquitousKeyValueStore`` instead.
///
/// > Warning: Don't access the files of the defaults database directly from the file system.
/// Modifying one of the underlying files directly may cause data loss, a delay in changes
/// being available, or an app crash. In macOS, use the `defaults` command-line utility to
/// safely view or modify the defaults database outside of your app.
///
/// While your app is running, the defaults system generates notifications to let you know
/// when values change. To observe changes to individual settings, add a key-value observer
/// to your `UserDefaults` object, using key names to build the path to the setting
/// you want. To observe changes for all settings, register for a ``didChangeNotification``
/// with your `UserDefaults` object.
///
/// The `UserDefaults` type is thread-safe, and you can use the same object in multiple
/// threads or tasks simultaneously.
///
/// ### Domains and Settings Search Paths
///
/// To integrate settings from different sources, the defaults system organizes them
/// into domains. An app defines its own custom settings, but the system defines settings
/// that apply to all apps. Similarly, you might choose to override a specific setting
/// temporarily to test one of your app's features. The defaults system provides domains
/// for each of these cases along with several others.
///
/// When you request the value of a setting, the `UserDefaults` object searches its domains in
/// a specific order until it finds the value you want. The following table lists the key domains
/// that the defaults system supports and their search order. Some domains might not be
/// present for all apps. For example, the managed domain is present only on administrator-managed devices.
///
/// | Domain | Type | Description |
/// |----------|----------|----------|
/// | Managed | persistent | This domain contains settings that an administrator provided for a managed device. |
/// | Argument | volatile | This domain contains the settings you specified when launching your app from the command-line or Xcode. These keys represent temporary overrides of settings, and the system discards them after the app quits. |
/// | Educational managed | persistent | For managed devices in an educational institution, this domain contains any settings saved to the iCloud key-value store for that institution. |
/// | App | persistent | This domain contains the settings your app saves, either programmatically or using its settings UI. |
/// | Suite | persistent | This domain contains custom settings from an app group or other app you specify at runtime. This domain is absent by default, but you can add a suite using the ``addSuite(named:)`` method. |
/// | Global | persistent | This domain contains keys present for all apps on the system. The system provides the keys for this domain, and apps can't write to it. |
/// | Registration | volatile | This domain contains system-provided default values and the default values you register for your app at launch time. Registering a set of default values prevents your code from receiving `nil` values when requesting a setting. The system discards these values when your app quits, so you must register them each time your app launches. |
///
/// The system stores data for most persistent domains on the current device, and doesn't
/// share that data with other devices. To share settings among all of a person's devices,
/// save them using an ``NSUbiquitousKeyValueStore`` object instead.
///
/// ### Settings in Managed Environments
///
/// If your app supports managed environments, an administrator might configure any managed devices
/// with a default set of settings. Apps can't write to managed domains, so if your app encounters
/// a managed setting, disable or hide any controls that someone might use to change that setting's
/// value. To determine if a setting is managed, call the ``objectIsForced(forKey:)`` or
/// ``objectIsForced(forKey:inDomain:)`` method of your `UserDefaults` object.
///
/// ### Sandbox Considerations
///
/// A sandboxed app cannot access or modify the settings of another app or process, with the
/// following exceptions:
///
/// - An app can modify settings for one of its app extensions.
/// - An app can modify settings for an app group to which it belongs.
@interface NSUserDefaults : NSObject {
@private
    id _kvo_;
    CFStringRef _identifier_;
    CFStringRef _container_;
}

/// The shared defaults object for the current app.
///
/// The shared defaults object searches the current application's search list, which consists of the current domain, followed by any added suite domains, the global domain, and the registration domain.
@property (class, readonly, strong) NSUserDefaults *standardUserDefaults;

// +resetStandardUserDefaults releases the standardUserDefaults and sets it to nil. A new standardUserDefaults will be created the next time it's accessed. The only visible effect this has is that all KVO observers of the previous standardUserDefaults will no longer be observing it.
/// This method has no effect and shouldn't be used.
+ (void)resetStandardUserDefaults;

// -init is equivalent to -initWithSuiteName:nil
/// Creates a new defaults object and initializes it with the app's current settings.
- (instancetype)init;

// -initWithSuiteName: initializes an instance of NSUserDefaults that searches the shared preferences search list for the domain 'suitename'. For example, using the identifier of an application group will cause the receiver to search the preferences for that group. Passing the current application's bundle identifier, NSGlobalDomain, or the corresponding CFPreferences constants is an error. Passing nil will search the default search list.
/// Creates a new defaults object and initializes it with the settings from the specified database.
- (nullable instancetype)initWithSuiteName:(nullable NSString *)suitename API_AVAILABLE(macos(10.9), ios(7.0), watchos(2.0), tvos(9.0)) NS_DESIGNATED_INITIALIZER;

/// Creates a user defaults object initialized with the defaults for the specified user account.
- (nullable id)initWithUser:(NSString *)username API_DEPRECATED("Use -init instead", macos(10.0,10.9), ios(2.0,7.0), watchos(2.0,2.0), tvos(9.0,9.0));

/// Returns the object associated with the specified key.
///
/// - Parameter defaultName: A key in the current user's defaults database.
/// - Returns: The object associated with the specified key, or `nil` if the key was not found.
///
/// This method searches the receiver's search list for a default with the key `defaultName` and returns it. If another process has changed defaults in the search list, NSUserDefaults will automatically update to the latest values. If the key in question has been marked as ubiquitous via a Defaults Configuration File, the latest value may not be immediately available, and the registered value will be returned instead.
///
/// The returned object is immutable, even if the value you originally set was mutable.
- (nullable id)objectForKey:(NSString *)defaultName;

/// Sets the value of the specified key to a property list object.
///
/// - Parameters:
///   - value: The object to store in the defaults database. Pass `nil` to remove the value for `defaultName`.
///   - defaultName: The key with which to associate the value.
///
/// This method immediately stores a value (or removes the value if `nil` is passed) for the provided key in the search list entry for the receiver's suite name in the current user and any host, then asynchronously stores the value persistently, where it is made available to other processes.
///
/// Setting a default value to a non-property-list object that can't be archived will throw an exception.
- (void)setObject:(nullable id)value forKey:(NSString *)defaultName;

/// Removes the value for the specified key from the defaults database.
///
/// - Parameter defaultName: The key whose value you want to remove.
///
/// Removing a default has no effect on the value returned by the `object(forKey:)` method if the same key exists in a domain that precedes the application domain in the search list.
- (void)removeObjectForKey:(NSString *)defaultName;

/// Returns the string associated with the specified key.
///
/// - Parameter defaultName: A key in the current user's defaults database.
/// - Returns: The string associated with the specified key, or `nil` if the key doesn't exist or the value is not a string. If the value is a number, this method converts it to a string representation.
- (nullable NSString *)stringForKey:(NSString *)defaultName;

/// Returns the array associated with the specified key.
///
/// - Parameter defaultName: A key in the current user's defaults database.
/// - Returns: The array associated with the specified key, or `nil` if the key doesn't exist or its value is not an array. The returned array and its contents are immutable, even if the values you originally set were mutable.
- (nullable NSArray *)arrayForKey:(NSString *)defaultName;
/// Returns the dictionary object associated with the specified key.
///
/// - Parameter defaultName: A key in the current user's defaults database.
/// - Returns: The dictionary object associated with the specified key, or `nil` if the key doesn't exist or its value is not a dictionary. The returned dictionary and its contents are immutable, even if the values you originally set were mutable.
- (nullable NSDictionary<NSString *, id> *)dictionaryForKey:(NSString *)defaultName;
/// Returns the data object associated with the specified key.
///
/// - Parameter defaultName: A key in the current user's defaults database.
/// - Returns: The data object associated with the specified key, or `nil` if the key doesn't exist or its value is not a data object. The returned data object is immutable, even if the value you originally set was mutable.
- (nullable NSData *)dataForKey:(NSString *)defaultName;
/// Returns the array of strings associated with the specified key.
///
/// - Parameter defaultName: A key in the current user's defaults database.
/// - Returns: The array of strings associated with the specified key, or `nil` if the key doesn't exist, the value is not an array, or any element in the array is not a string. Unlike ``UserDefaults/string(forKey:)``, `NSNumber` values are not converted to strings.
- (nullable NSArray<NSString *> *)stringArrayForKey:(NSString *)defaultName;
/// Returns the integer value associated with the specified key.
///
/// - Parameter defaultName: A key in the current user's defaults database.
/// - Returns: The integer value associated with the specified key. If the key doesn't exist, this method returns `0`.
///
/// If the value is an `NSNumber`, the result of `-integerValue` will be returned. If the value is an `NSString`, it will be converted to `NSInteger` if possible. If the value is a Boolean, it will be converted to either `1` for `YES` or `0` for `NO`. If the value is absent or can't be converted to an integer, `0` will be returned.
- (NSInteger)integerForKey:(NSString *)defaultName;
/// Returns the floating-point value associated with the specified key.
///
/// - Parameter defaultName: A key in the current user's defaults database.
/// - Returns: The float value associated with the specified key. If the key doesn't exist, this method returns `0`.
///
/// If the value is an `NSNumber`, the result of `-floatValue` will be returned. If the value is an `NSString`, it will be converted if possible. Boolean values will not be converted.
- (float)floatForKey:(NSString *)defaultName;
/// Returns the double value associated with the specified key.
///
/// - Parameter defaultName: A key in the current user's defaults database.
/// - Returns: The double value associated with the specified key. If the key doesn't exist, this method returns `0`.
///
/// If the value is an `NSNumber`, the result of `-doubleValue` will be returned. If the value is an `NSString`, it will be converted if possible. Boolean values will not be converted.
- (double)doubleForKey:(NSString *)defaultName;
/// Returns the Boolean value associated with the specified key.
///
/// - Parameter defaultName: A key in the current user's defaults database.
/// - Returns: The Boolean value associated with the specified key. If the key doesn't exist, this method returns `NO`.
///
/// If the value is an `NSNumber`, `NO` will be returned if the value is `0`, `YES` otherwise. If the value is an `NSString`, values of `"YES"` or `"1"` will return `YES`, and values of `"NO"`, `"0"`, or any other string will return `NO`. If the value is absent or can't be converted to a `BOOL`, `NO` will be returned.
- (BOOL)boolForKey:(NSString *)defaultName;
/// Returns the URL associated with the specified key.
///
/// - Parameter defaultName: A key in the current user's defaults database.
/// - Returns: The URL associated with the specified key, or `nil` if the key doesn't exist or its value can't be converted to a URL.
///
/// If the value is an `NSString` path, then it will construct a file URL to that path. If the value is an archived URL from ``UserDefaults/set(_:forKey:)-2bqjt`` it will be unarchived.
- (nullable NSURL *)URLForKey:(NSString *)defaultName API_AVAILABLE(macos(10.6), ios(4.0), watchos(2.0), tvos(9.0));

/// Sets the value of the specified key to an integer.
///
/// - Parameters:
///   - value: The integer value to store.
///   - defaultName: The key with which to associate the value.
- (void)setInteger:(NSInteger)value forKey:(NSString *)defaultName;
/// Sets the value of the specified key to a floating-point number.
///
/// - Parameters:
///   - value: The floating-point value to store.
///   - defaultName: The key with which to associate the value.
- (void)setFloat:(float)value forKey:(NSString *)defaultName;
/// Sets the value of the specified key to a double.
///
/// - Parameters:
///   - value: The double value to store.
///   - defaultName: The key with which to associate the value.
- (void)setDouble:(double)value forKey:(NSString *)defaultName;
/// Sets the value of the specified key to a Boolean value.
///
/// - Parameters:
///   - value: The Boolean value to store.
///   - defaultName: The key with which to associate the value.
- (void)setBool:(BOOL)value forKey:(NSString *)defaultName;
/// Sets the value of the specified key to a URL.
///
/// - Parameters:
///   - url: The URL to store.
///   - defaultName: The key with which to associate the value.
///
/// If `url` is a file URL, the value that is archived is the `path` with the user's home directory abbreviated using a tilde (`~`) character. Use ``UserDefaults/url(forKey:)`` to retrieve values set this way.
- (void)setURL:(nullable NSURL *)url forKey:(NSString *)defaultName API_AVAILABLE(macos(10.6), ios(4.0), watchos(2.0), tvos(9.0));

/// Specifies the set of default settings and values to use as a fallback in cases where the app domain doesn't have them.
///
/// - Parameter registrationDictionary: The dictionary of keys and values you want to register.
///
/// The contents of the registration domain are not written to disk; you need to call this method each time your application starts. You can call this method more than once; each call adds or updates the entries in the registration domain.
///
/// Default values from Defaults Configuration Files will automatically be registered.
- (void)registerDefaults:(NSDictionary<NSString *, id> *)registrationDictionary;

/// Inserts settings for the specified domain into the search list of the current object.
///
/// - Parameter suiteName: The domain name to insert. This domain is inserted after the application domain. Passing ``NSGlobalDomain`` or the current application's bundle identifier is unsupported.
///
/// The additional search lists are searched after the current domain, but before global defaults.
- (void)addSuiteNamed:(NSString *)suiteName;
/// Removes the specified domain from the search list of the current object.
///
/// - Parameter suiteName: The domain name to remove.
- (void)removeSuiteNamed:(NSString *)suiteName;

/// Returns a dictionary with the union of all key-value pairs found from all domains.
///
/// - Returns: A dictionary that contains the keys and their corresponding values from each of the search list's domains. For duplicate keys, the object from the domain that is closest to the front of the search list is used.
- (NSDictionary<NSString *, id> *)dictionaryRepresentation;

// Volatile domains are not added to any search list, are not persisted, and are not visible to other applications. Using them is not recommended.

/// An array of identifiers for the volatile domains associated with the current object.
///
/// Use ``UserDefaults/volatileDomain(forName:)`` to retrieve the contents of a specific volatile domain.
@property (readonly, copy) NSArray<NSString *> *volatileDomainNames;
/// Retrieves the settings from the specified volatile domain.
///
/// - Parameter domainName: The name of the volatile domain.
/// - Returns: The dictionary for the volatile domain specified by `domainName`, or `nil` if the domain doesn't exist.
- (NSDictionary<NSString *, id> *)volatileDomainForName:(NSString *)domainName;
/// Replaces the keys and values in the specified domain with the new keys and values you supply.
///
/// - Parameters:
///   - domain: The dictionary of keys and values to assign to the domain.
///   - domainName: The name of the volatile domain.
- (void)setVolatileDomain:(NSDictionary<NSString *, id> *)domain forName:(NSString *)domainName;
/// Removes the keys and values from the specified volatile domain.
///
/// - Parameter domainName: The name of the volatile domain to remove.
- (void)removeVolatileDomainForName:(NSString *)domainName;

/// Returns an array of the current persistent domain names.
///
/// @DeprecationSummary {
///     Track domains yourself; use ``UserDefaults/persistentDomain(forName:)`` instead.
/// }
- (NSArray *)persistentDomainNames API_DEPRECATED("Not recommended", macos(10.0,10.9), ios(2.0,7.0), watchos(2.0,2.0), tvos(9.0,9.0));

/// Retrieves the settings from the specified persistent domain.
///
/// - Parameter domainName: The domain name.
/// - Returns: A dictionary containing the keys and values in the specified persistent domain, or `nil` if the domain doesn't exist.
- (nullable NSDictionary<NSString *, id> *)persistentDomainForName:(NSString *)domainName;
/// Replaces the keys and values in the specified domain with the new keys and values you supply.
///
/// - Parameters:
///   - domain: The dictionary of keys and values to assign to the domain.
///   - domainName: The name of the persistent domain.
///
/// Replaces all values in the search list entry specified by `domainName`, the current user, and any host, with the values in `domain`. The change will be persisted.
- (void)setPersistentDomain:(NSDictionary<NSString *, id> *)domain forName:(NSString *)domainName;
/// Removes the keys and values from the specified persistent domain.
///
/// - Parameter domainName: The name of the persistent domain.
///
/// Removes all values from the search list entry specified by `domainName`, the current user, and any host. The change is persistent.
- (void)removePersistentDomainForName:(NSString *)domainName;

/// Waits for any pending asynchronous updates to the defaults database and returns; this method is unnecessary and shouldn't be used.
///
/// This method is unnecessary and shouldn't be used.
- (BOOL)synchronize;

/// Returns a Boolean value that indicates whether an administrator provided the value for the specified key.
///
/// - Parameter key: The key whose status you want to check.
/// - Returns: `YES` if the value for `key` is managed by an administrator; otherwise, `NO`.
///
/// A key is managed when its value has been set by a configuration profile or managed by a mobile device management (MDM) server. For keys that are managed, you should disable any user interface that allows the user to modify the value of that key.
- (BOOL)objectIsForcedForKey:(NSString *)key;

/// Returns a Boolean value that indicates whether an administrator provided the value for the key in the specified domain.
///
/// - Parameters:
///   - key: The key whose status you want to check.
///   - domain: The domain of the key.
/// - Returns: `YES` if the value for `key` in `domain` is managed by an administrator; otherwise, `NO`.
///
/// For keys that are managed, you should disable any user interface that allows the user to modify the value of that key.
- (BOOL)objectIsForcedForKey:(NSString *)key inDomain:(NSString *)domain;

@end

/// Posted when the amount of data in the defaults database exceeds the allowed maximum.
///
/// Currently there is no limit for local user defaults except on tvOS, where a warning notification will be posted at 512kB, and the process terminated at 1MB. For ubiquitous defaults, the limit depends on the logged in iCloud user.
FOUNDATION_EXPORT NSNotificationName const NSUserDefaultsSizeLimitExceededNotification API_AVAILABLE(ios(9.3), watchos(2.0), tvos(9.0)) API_UNAVAILABLE(macos);

/// Posted when a cloud default is set, but no iCloud user is logged in.
///
/// This is not necessarily an error: ubiquitous defaults set when no iCloud user is logged in will be uploaded the next time one is available if configured to do so.
FOUNDATION_EXPORT NSNotificationName const NSUbiquitousUserDefaultsNoCloudAccountNotification API_DEPRECATED("Notification is never posted", ios(9.3, 9.3), watchos(2.0, 2.0), tvos(9.0, 9.0)) API_UNAVAILABLE(macos);

/// Posted when the user changes the primary iCloud account.
///
/// The keys and values in the local key-value store have been replaced with those from the new account, regardless of the relative timestamps.
FOUNDATION_EXPORT NSNotificationName const NSUbiquitousUserDefaultsDidChangeAccountsNotification API_DEPRECATED("Notification is never posted", ios(9.3, 9.3), watchos(2.0, 2.0), tvos(9.0, 9.0)) API_UNAVAILABLE(macos);

/// Posted when ubiquitous defaults finish downloading data, either the first time a device is connected to an iCloud account or when a user switches their primary iCloud account.
FOUNDATION_EXPORT NSNotificationName const NSUbiquitousUserDefaultsCompletedInitialSyncNotification API_DEPRECATED("Notification is never posted", ios(9.3, 9.3), watchos(2.0, 2.0), tvos(9.0, 9.0)) API_UNAVAILABLE(macos);

/// Posted when the current process changes the value of a setting.
///
/// This notification isn't posted when ubiquitous defaults change, or when an outside process changes defaults. Using key-value observing to register observers for the specific keys of interest will inform you of all updates, regardless of where they're from.
FOUNDATION_EXPORT NSNotificationName const NSUserDefaultsDidChangeNotification;

#if TARGET_OS_OSX
/* The following keys and their values are deprecated in Mac OS X 10.5 "Leopard". Developers should use NSLocale, NSDateFormatter and NSNumberFormatter to retrieve the values formerly returned by these keys.
 */
/// Key for an array of strings that specify the names for the days of the week, affecting strings that use the `%A` format specifier.
FOUNDATION_EXPORT NSString * const NSWeekDayNameArray API_DEPRECATED("", macos(10.0, 10.5)) API_UNAVAILABLE(ios, watchos, tvos);
/// Key for an array of strings that specify the abbreviations for the days of the week, affecting strings that use the `%a` format specifier.
FOUNDATION_EXPORT NSString * const NSShortWeekDayNameArray API_DEPRECATED("", macos(10.0, 10.5)) API_UNAVAILABLE(ios, watchos, tvos);
/// Key for the value that specifies the names for the months, affecting strings that use the `%B` format specifier.
FOUNDATION_EXPORT NSString * const NSMonthNameArray API_DEPRECATED("", macos(10.0, 10.5)) API_UNAVAILABLE(ios, watchos, tvos);
/// Key for an array of strings that specify the abbreviations for the months, affecting strings that use the `%b` format specifier.
FOUNDATION_EXPORT NSString * const NSShortMonthNameArray API_DEPRECATED("", macos(10.0, 10.5)) API_UNAVAILABLE(ios, watchos, tvos);
/// Key for a format string that specifies how dates with times are printed.
FOUNDATION_EXPORT NSString * const NSTimeFormatString API_DEPRECATED("", macos(10.0, 10.5)) API_UNAVAILABLE(ios, watchos, tvos);
/// Key for the format string that specifies how dates are printed using the date format specifiers.
FOUNDATION_EXPORT NSString * const NSDateFormatString API_DEPRECATED("", macos(10.0, 10.5)) API_UNAVAILABLE(ios, watchos, tvos);
/// Key for the value that specifies how dates with times are printed, affecting strings that use the format specifiers `%c`, `%X`, or `%x`.
FOUNDATION_EXPORT NSString * const NSTimeDateFormatString API_DEPRECATED("", macos(10.0, 10.5)) API_UNAVAILABLE(ios, watchos, tvos);
/// Key for a format string that specifies how times and dates are abbreviated.
FOUNDATION_EXPORT NSString * const NSShortTimeDateFormatString API_DEPRECATED("", macos(10.0, 10.5)) API_UNAVAILABLE(ios, watchos, tvos);
/// A string that specifies the symbol used to denote currency in this language.
FOUNDATION_EXPORT NSString * const NSCurrencySymbol API_DEPRECATED("", macos(10.0, 10.5)) API_UNAVAILABLE(ios, watchos, tvos);
/// A string that specifies the decimal separator.
FOUNDATION_EXPORT NSString * const NSDecimalSeparator API_DEPRECATED("", macos(10.0, 10.5)) API_UNAVAILABLE(ios, watchos, tvos);
/// A string that specifies the separator character for the thousands place of a decimal number.
FOUNDATION_EXPORT NSString * const NSThousandsSeparator API_DEPRECATED("", macos(10.0, 10.5)) API_UNAVAILABLE(ios, watchos, tvos);
/// Strings that identify the decimal digits in addition to or instead of the ASCII digits.
FOUNDATION_EXPORT NSString * const NSDecimalDigits API_DEPRECATED("", macos(10.0, 10.5)) API_UNAVAILABLE(ios, watchos, tvos);
/// Key for the value that specifies how the morning and afternoon designations are printed, affecting strings that use the `%p` format specifier.
FOUNDATION_EXPORT NSString * const NSAMPMDesignation API_DEPRECATED("", macos(10.0, 10.5)) API_UNAVAILABLE(ios, watchos, tvos);
/// Key for strings that identify the time of day.
FOUNDATION_EXPORT NSString * const NSHourNameDesignations API_DEPRECATED("", macos(10.0, 10.5)) API_UNAVAILABLE(ios, watchos, tvos);
/// Key for an array of strings that specify the words for year, month, and week in the current locale.
FOUNDATION_EXPORT NSString * const NSYearMonthWeekDesignations API_DEPRECATED("", macos(10.0, 10.5)) API_UNAVAILABLE(ios, watchos, tvos);
/// Key for an array of strings that denote a time in the past.
FOUNDATION_EXPORT NSString * const NSEarlierTimeDesignations API_DEPRECATED("", macos(10.0, 10.5)) API_UNAVAILABLE(ios, watchos, tvos);
/// Key for an array of strings that denote a time in the future.
FOUNDATION_EXPORT NSString * const NSLaterTimeDesignations API_DEPRECATED("", macos(10.0, 10.5)) API_UNAVAILABLE(ios, watchos, tvos);
/// Key for an array of strings that specify what this day is called.
FOUNDATION_EXPORT NSString * const NSThisDayDesignations API_DEPRECATED("", macos(10.0, 10.5)) API_UNAVAILABLE(ios, watchos, tvos);
/// Key for an array of strings that denote the day after today.
FOUNDATION_EXPORT NSString * const NSNextDayDesignations API_DEPRECATED("", macos(10.0, 10.5)) API_UNAVAILABLE(ios, watchos, tvos);
/// Key for an array of strings that denote the day after tomorrow.
FOUNDATION_EXPORT NSString * const NSNextNextDayDesignations API_DEPRECATED("", macos(10.0, 10.5)) API_UNAVAILABLE(ios, watchos, tvos);
/// Key for an array of strings that denote the day before today.
FOUNDATION_EXPORT NSString * const NSPriorDayDesignations API_DEPRECATED("", macos(10.0, 10.5)) API_UNAVAILABLE(ios, watchos, tvos);
/// Key for the string that specifies how to use ambiguous numbers in date strings.
FOUNDATION_EXPORT NSString * const NSDateTimeOrdering API_DEPRECATED("", macos(10.0, 10.5)) API_UNAVAILABLE(ios, watchos, tvos);
/// A string containing a three-letter abbreviation for currency, following the ISO 4217 standard.
FOUNDATION_EXPORT NSString * const NSInternationalCurrencyString API_DEPRECATED("", macos(10.0, 10.5)) API_UNAVAILABLE(ios, watchos, tvos);
/// Key for a format string that specifies how dates are abbreviated.
FOUNDATION_EXPORT NSString * const NSShortDateFormatString API_DEPRECATED("", macos(10.0, 10.5)) API_UNAVAILABLE(ios, watchos, tvos);
/// A format string that specifies how positive numbers are printed when representing a currency value.
FOUNDATION_EXPORT NSString * const NSPositiveCurrencyFormatString API_DEPRECATED("", macos(10.0, 10.5)) API_UNAVAILABLE(ios, watchos, tvos);
/// A format string that specifies how negative numbers are printed when representing a currency value.
FOUNDATION_EXPORT NSString * const NSNegativeCurrencyFormatString API_DEPRECATED("", macos(10.0, 10.5)) API_UNAVAILABLE(ios, watchos, tvos);
#endif

NS_HEADER_AUDIT_END(nullability, sendability)
