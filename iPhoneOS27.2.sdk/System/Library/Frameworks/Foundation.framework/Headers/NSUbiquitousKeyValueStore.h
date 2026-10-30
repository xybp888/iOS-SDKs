/*	NSUbiquitousKeyValueStore.h
	Copyright (c) 2011-2019, Apple Inc. All rights reserved.
*/

#import <Foundation/NSObject.h>
#import <Foundation/NSNotification.h>

@class NSArray, NSDictionary<KeyType, ObjectType>, NSData, NSString;

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

/// An iCloud-based container of key-value pairs you share among instances of your app
/// running on a person’s devices.
///
/// Use the shared `NSUbiquitousKeyValueStore` object to store settings, configuration
/// information, and app-specific data in a person’s iCloud account and share it among
/// instances of your app running on all of the person’s devices. The object stores a dictionary
/// of key-value pairs that you provide, and propagates that data to devices with the
/// same Apple account. Sharing data among different devices gives you a way to coordinate
/// your app’s behavior on those devices. For example, a textbook app might save the
/// current page number on someone’s iPhone so that the person can continue reading
/// from the same place on their other devices.
///
/// > Important: Don't store personal or sensitive information in the key-value store. The
/// system stores the information on disk in an unencrypted format. Store personal or sensitive
/// information in the person's Keychain instead.
///
/// Each app has a single iCloud key-value store object, which you retrieve from the
/// ``NSUbiquitousKeyValueStore/default`` class property. Use this same object throughout
/// your app to read and write values. Don’t subclass `NSUbiquitousKeyValueStore`.
///
/// > Note: To use this object, you must distribute your app through the App Store or
/// Mac App Store, and you must request the [iCloud key-value store entitlement](<doc://com.apple.documentation/documentation/bundleresources/entitlements/com.apple.developer.ubiquity-kvstore-identifier>)
/// in your Xcode project.
///
/// The keys in the iCloud key-value store identify the item and its purpose in your app,
/// and the value is a data object you use to implement the corresponding behavior in your
/// app. Values must be property list types such as <doc://com.apple.documentation/documentation/Swift/Int64>,
/// <doc://com.apple.documentation/documentation/swift/float>, <doc://com.apple.documentation/documentation/swift/double>,
/// <doc://com.apple.documentation/documentation/swift/bool>, <doc://com.apple.documentation/documentation/swift/string>,
/// <doc://com.apple.documentation/documentation/foundation/nsnumber>,
/// ``Date``, <doc://com.apple.documentation/documentation/swift/array>, or
/// <doc://com.apple.documentation/documentation/swift/dictionary>. To include other types of
/// objects in the key-value store, archive them to a ``Data``
/// object first and store that object instead. Prefer simple types over custom objects
/// whenever possible.
///
/// When you write a new value, the iCloud key-value store saves it in memory initially
/// and writes it to disk asynchronously later. If the device doesn’t have an active Apple
/// account, the changes remain only on the current device. When the person signs into
/// their account, the system forwards any changes to the iCloud server and reconciles
/// the values there with the local ones. As you make more changes, the system keeps the
/// local and server-based copies of the data synchronized, updating each one at appropriate times.
///
/// When a value changes on one device, iCloud forwards that change to the person’s other devices.
/// If your app is running on one of those other devices, the system posts
/// ``NSUbiquitousKeyValueStore/didChangeExternallyNotification`` to report the
/// change. Register for that notification to keep all instances of your app in sync.
///
/// When designing the keys and values you intend to save for your app, consider the
/// following size limitations:
///
/// * Your app can have no more than 1024 keys in the iCloud key-value store.
/// * The total amount of available storage space for all values is 1 megabyte.
/// * The maximum size for a single value is 1 megabyte. Therefore, if you associate 1
/// megabyte of data with a single key, you can’t write other keys to the store.
/// * The maximum length for each key string is 128 characters using the UTF-16 encoding.
/// Key strings don’t count against the 1 megabyte quota for values.
///
/// If you exceed any of the prescribed limits during a write operation, the operation
/// fails and the system doesn’t add the keys or values to the store. If a key string
/// exceeds the maximum length, the system raises an exception. If a write operation
/// would exceed your app’s quota, the system posts ``NSUbiquitousKeyValueStore/didChangeExternallyNotification``
/// notification with the change reason set to ``NSUbiquitousKeyValueStoreQuotaViolationChange``.
API_AVAILABLE(macos(10.7), ios(5.0), watchos(9.0), tvos(9.0))
@interface NSUbiquitousKeyValueStore : NSObject

/// The shared iCloud key-value store object.
///
/// Use this object to access the shared iCloud key-value store tied to your app and the current person.
@property (class, readonly, strong) NSUbiquitousKeyValueStore *defaultStore;

/// Returns the object associated with the specified key.
///
/// - Parameter aKey: The key to retrieve from the iCloud key-value store.
/// - Returns: The object associated with `aKey`, or `nil` if the key isn't present.
- (nullable id)objectForKey:(NSString *)aKey;
/// Sets the value of the specified key to a property list object.
- (void)setObject:(nullable id)anObject forKey:(NSString *)aKey;
/// Removes the value for the specified key from the iCloud key-value store.
- (void)removeObjectForKey:(NSString *)aKey;

/// Returns the string associated with the specified key.
- (nullable NSString *)stringForKey:(NSString *)aKey;
/// Returns the array associated with the specified key.
- (nullable NSArray *)arrayForKey:(NSString *)aKey;
/// Returns the dictionary object associated with the specified key.
- (nullable NSDictionary<NSString *, id> *)dictionaryForKey:(NSString *)aKey;
/// Returns the data object associated with the specified key.
- (nullable NSData *)dataForKey:(NSString *)aKey;
/// Returns the 64-bit integer value associated with the specified key.
- (long long)longLongForKey:(NSString *)aKey;
/// Returns the `double` value associated with the specified key.
- (double)doubleForKey:(NSString *)aKey;
/// Returns the Boolean value associated with the specified key.
- (BOOL)boolForKey:(NSString *)aKey;

/// Sets the value of the specified key to a string value.
- (void)setString:(nullable NSString *)aString forKey:(NSString *)aKey;
/// Sets the value of the specified key to a data object.
- (void)setData:(nullable NSData *)aData forKey:(NSString *)aKey;
/// Sets the value of the specified key to an array of property list objects.
- (void)setArray:(nullable NSArray *)anArray forKey:(NSString *)aKey;
/// Sets the value of the specified key to a dictionary of property list objects.
- (void)setDictionary:(nullable NSDictionary<NSString *, id> *)aDictionary forKey:(NSString *)aKey;
/// Sets the value of the specified key to a 64-bit integer value.
- (void)setLongLong:(long long)value forKey:(NSString *)aKey;
/// Sets the value of the specified key to a double value.
- (void)setDouble:(double)value forKey:(NSString *)aKey;
/// Sets the value of the specified key to a Boolean value.
- (void)setBool:(BOOL)value forKey:(NSString *)aKey;

/// A dictionary with all of the key-value pairs in the iCloud key-value store.
@property (readonly, copy) NSDictionary<NSString *, id> *dictionaryRepresentation;

/// Synchronizes the in-memory keys and values with the ones stored in iCloud.
///
/// - Returns: `YES` if the in-memory and iCloud keys are synchronized, or `NO` if an error occurred.
- (BOOL)synchronize;

@end

/// Posted when the value of one or more keys changes due to incoming data from iCloud.
FOUNDATION_EXPORT NSNotificationName const NSUbiquitousKeyValueStoreDidChangeExternallyNotification API_AVAILABLE(macos(10.7), ios(5.0), watchos(2.0), tvos(9.0));
/// A key that indicates the reason why the key-value store changed.
FOUNDATION_EXPORT NSString * const NSUbiquitousKeyValueStoreChangeReasonKey API_AVAILABLE(macos(10.7), ios(5.0), watchos(2.0), tvos(9.0));
/// A key that indicates which keys changed in the iCloud key-value store.
FOUNDATION_EXPORT NSString * const NSUbiquitousKeyValueStoreChangedKeysKey API_AVAILABLE(macos(10.7), ios(5.0), watchos(2.0), tvos(9.0));

NS_ENUM(NSInteger) {
    /// A constant that indicates a value changed in iCloud.
    NSUbiquitousKeyValueStoreServerChange API_AVAILABLE(macos(10.7), ios(5.0), watchos(2.0), tvos(9.0)),
    /// A constant that indicates the initial attempt to load keys and values from iCloud is in progress.
    NSUbiquitousKeyValueStoreInitialSyncChange API_AVAILABLE(macos(10.7), ios(5.0), watchos(2.0), tvos(9.0)),
    /// A constant that indicates an attempt to write data exceeded the quota limits.
    NSUbiquitousKeyValueStoreQuotaViolationChange API_AVAILABLE(macos(10.7), ios(5.0), watchos(2.0), tvos(9.0)),
    /// A constant that indicates the current Apple account changed.
    NSUbiquitousKeyValueStoreAccountChange API_AVAILABLE(macos(10.8), ios(6.0), watchos(2.0), tvos(9.0))
};

NS_HEADER_AUDIT_END(nullability, sendability)
