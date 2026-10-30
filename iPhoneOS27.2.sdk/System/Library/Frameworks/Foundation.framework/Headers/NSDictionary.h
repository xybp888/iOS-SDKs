/*	NSDictionary.h
	Copyright (c) 1994-2019, Apple Inc. All rights reserved.
*/

#import <Foundation/NSObject.h>
#import <Foundation/NSEnumerator.h>

@class NSArray<ObjectType>, NSSet<ObjectType>, NSString, NSURL;

/* ***************	Immutable Dictionary	****************/

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

/// A static collection of objects associated with unique keys.
///
/// You can use this type in Swift instead of a `Dictionary` in cases that require reference semantics.
///
/// The `NSDictionary` class declares the programmatic interface to objects that manage immutable associations of keys and values. For example, an interactive form could be represented as a dictionary, with the field names as keys, corresponding to user-entered values.
///
/// Use this class or its subclass ``NSMutableDictionary`` when you need a convenient and efficient way to retrieve data associated with an arbitrary key. `NSDictionary` creates static dictionaries, and `NSMutableDictionary` creates dynamic dictionaries. (For convenience, the term _dictionary_ refers to any instance of one of these classes without specifying its exact class membership.)
///
/// A key-value pair within a dictionary is called an entry. Each entry consists of one object that represents the key and a second object that is that key's value. Within a dictionary, the keys are unique. That is, no two keys in a single dictionary are equal (as determined by `isEqual:`). In general, a key can be any object (provided that it conforms to the `NSCopying` protocol---see below), but note that when using key-value coding the key must be a string (see [Accessing Object Properties](https://developer.apple.com/library/archive/documentation/Cocoa/Conceptual/KeyValueCoding/BasicPrinciples.html#//apple_ref/doc/uid/20002170)). Neither a key nor a value can be `nil`; if you need to represent a null value in a dictionary, you should use ``NSNull``.
///
/// `NSDictionary` is "toll-free bridged" with its Core Foundation counterpart, `CFDictionary`. See [Toll-Free Bridging](https://developer.apple.com/library/archive/documentation/General/Conceptual/CocoaEncyclopedia/Toll-FreeBridgin/Toll-FreeBridgin.html#//apple_ref/doc/uid/TP40010810-CH2) for more information on toll-free bridging.
///
/// ### Creating NSDictionary Objects Using Dictionary Literals
///
/// In addition to the provided initializers, such as ``init(objects:forKeys:)``, you can create an `NSDictionary` object using a _dictionary literal_.
///
/// ```objc
/// NSDictionary *dictionary = @{
///        @"anObject" : someObject,
///     @"helloString" : @"Hello, World!",
///     @"magicNumber" : @42,
///          @"aValue" : someValue
/// };
/// ```
///
/// In Objective-C, the compiler generates code that makes an underlying call to the ``dictionaryWithObjects:forKeys:count:`` method.
///
/// ```objc
/// id objects[] = { someObject, @"Hello, World!", @42, someValue };
/// id keys[] = { @"anObject", @"helloString", @"magicNumber", @"aValue" };
/// NSUInteger count = sizeof(objects) / sizeof(id);
/// NSDictionary *dictionary = [NSDictionary dictionaryWithObjects:objects
///                                                        forKeys:keys
///                                                          count:count];
/// ```
///
/// Unlike ``dictionaryWithObjectsAndKeys:`` and other initializers, dictionary literals specify entries in key-value order. You should not terminate the list of objects with `nil` when using this literal syntax, and in fact `nil` is an invalid value. For more information about object literals in Objective-C, see [Working with Objects](https://developer.apple.com/library/archive/documentation/Cocoa/Conceptual/ProgrammingWithObjectiveC/WorkingwithObjects/WorkingwithObjects.html#//apple_ref/doc/uid/TP40011210-CH4) in [Programming with Objective-C](https://developer.apple.com/library/archive/documentation/Cocoa/Conceptual/ProgrammingWithObjectiveC/Introduction/Introduction.html#//apple_ref/doc/uid/TP40011210).
///
/// In Swift, the `NSDictionary` class conforms to the `DictionaryLiteralConvertible` protocol, which allows it to be initialized with dictionary literals. For more information about object literals in Swift, see [Literal Expression](https://developer.apple.com/library/archive/documentation/Swift/Conceptual/Swift_Programming_Language/Expressions.html#//apple_ref/doc/uid/TP40014097-CH32-ID390) in [The Swift Programming Language (Swift 4.1)](https://developer.apple.com/library/archive/documentation/Swift/Conceptual/Swift_Programming_Language/index.html#//apple_ref/doc/uid/TP40014097).
///
/// ### Accessing Values Using Subscripting
///
/// In addition to the provided instance methods, such as ``object(forKey:)``, you can access `NSDictionary` values by their keys using _subscripting_.
///
/// ```objc
/// id value = dictionary[@"helloString"];
/// ```
///
/// ### Enumerating Entries Using for-in Loops
///
/// In addition to the provided instance methods, such as ``enumerateKeysAndObjects(_:)``, you can enumerate `NSDictionary` entries using _for-in loops_.
///
/// ```objc
/// for (NSString *key in dictionary) {
///     id value = dictionary[key];
///     NSLog(@"Value: %@ for key: %@", value, key);
/// }
/// ```
///
/// In Objective-C, `NSDictionary` conforms to the ``NSFastEnumeration`` protocol.
///
/// In Swift, `NSDictionary` conforms to the `SequenceType` protocol.
///
/// ### Subclassing Notes
///
/// You generally shouldn't need to subclass `NSDictionary`. Custom behavior can usually be achieved through composition rather than subclassing.
///
/// #### Methods to Override
///
/// If you do need to subclass `NSDictionary`, take into account that it is a [Class cluster](https://developer.apple.com/library/archive/documentation/General/Conceptual/DevPedia-CocoaCore/ClassCluster.html#//apple_ref/doc/uid/TP40008195-CH7). Any subclass must override the following primitive methods:
///
/// - ``init(objects:forKeys:count:)``
/// - ``count``
/// - ``object(forKey:)``
/// - ``keyEnumerator()``
///
/// The other methods of `NSDictionary` operate by invoking one or more of these primitives. The non-primitive methods provide convenient ways of accessing multiple entries at once.
///
/// #### Alternatives to Subclassing
///
/// Before making a custom class of `NSDictionary`, investigate ``NSMapTable`` and the corresponding Core Foundation type, `CFDictionary`. Because `NSDictionary` and `CFDictionary` are "toll-free bridged," you can substitute a `CFDictionary` object for a `NSDictionary` object in your code (with appropriate casting). Although they are corresponding types, `CFDictionary` and `NSDictionary` do not have identical interfaces or implementations, and you can sometimes do things with `CFDictionary` that you cannot easily do with `NSDictionary`.
///
/// If the behavior you want to add supplements that of the existing class, you could write a category on `NSDictionary`. Keep in mind, however, that this category will be in effect for all instances of `NSDictionary` that you use, and this might have unintended consequences. Alternatively, you could use composition to achieve the desired behavior.
@interface NSDictionary<__covariant KeyType, __covariant ObjectType> : NSObject <NSCopying, NSMutableCopying, NSSecureCoding, NSFastEnumeration>

/// The number of entries in the dictionary.
@property (readonly) NSUInteger count;
/// Returns the value associated with a given key.
///
/// - Parameter aKey: The key for which to return the corresponding value.
/// - Returns: The value associated with `aKey`, or `nil` if no value is associated with `aKey`.
- (nullable ObjectType)objectForKey:(KeyType)aKey;
/// Provides an enumerator to access the keys in the dictionary.
///
/// - Returns: An enumerator object that lets you access each key in the dictionary.
///
/// Here's how you might use this method.
///
/// ```objc
/// NSEnumerator *enumerator = [myDictionary keyEnumerator];
/// id key;
///
/// while ((key = [enumerator nextObject])) {
///     /* code that uses the returned key */
/// }
/// ```
///
/// If you use this method with instances of mutable subclasses of ``NSDictionary``, your code should not modify the entries during enumeration. If you intend to modify the entries, use the ``NSDictionary/allKeys`` property to create a snapshot of the dictionary's keys. Then use this snapshot to traverse the entries, modifying them along the way.
///
/// If you want to enumerate the dictionary's values rather than its keys, use the ``NSDictionary/objectEnumerator()`` method.
///
/// ### Special Considerations
///
/// It is more efficient to use the fast enumeration protocol (see ``NSFastEnumeration``) than this method. Fast enumeration is available in macOS 10.5 and later and iOS 2.0 and later.
- (NSEnumerator<KeyType> *)keyEnumerator;
/// Initializes a newly allocated dictionary.
///
/// - Returns: A dictionary.
///
/// This method is a designated initializer of ``NSDictionary``.
- (instancetype)init NS_DESIGNATED_INITIALIZER;
/// Initializes a newly allocated dictionary with the specified number of key-value pairs constructed from the provided C arrays of keys and objects.
///
/// - Parameters:
///   - objects: A C array of values for the new dictionary.
///   - keys: A C array of keys for the new dictionary. Each key is copied (using ``NSCopying/copy(with:)``; keys must conform to the `NSCopying` protocol), and the copy is added to the new dictionary.
///   - cnt: The number of elements to use from the `keys` and `objects` arrays. `count` must not exceed the number of elements in `objects` or `keys`.
///
/// This method steps through the `objects` and `keys` arrays, creating entries in the new dictionary as it goes. An `NSInvalidArgumentException` is raised if a key or value object is `nil`.
///
/// This method is a designated initializer of `NSDictionary`.
- (instancetype)initWithObjects:(const ObjectType _Nonnull [_Nullable])objects forKeys:(const KeyType <NSCopying> _Nonnull [_Nullable])keys count:(NSUInteger)cnt NS_DESIGNATED_INITIALIZER;
/// Creates a dictionary initialized from data in the provided unarchiver.
///
/// - Parameter coder: An unarchiver object.
- (nullable instancetype)initWithCoder:(NSCoder *)coder NS_DESIGNATED_INITIALIZER;

@end

@interface NSDictionary<KeyType, ObjectType> (NSExtendedDictionary)

/// A new array containing the dictionary's keys, or an empty array if the dictionary has no entries.
///
/// The order of the elements in the array is not defined.
@property (readonly, copy) NSArray<KeyType> *allKeys;
/// Returns a new array containing the keys corresponding to all occurrences of a given object in the dictionary.
///
/// - Parameter anObject: The value to look for in the dictionary.
/// - Returns: A new array containing the keys corresponding to all occurrences of `anObject` in the dictionary. If no object matching `anObject` is found, returns an empty array.
///
/// Each object in the dictionary is sent an `isEqual:` message to determine if it's equal to `anObject`.
- (NSArray<KeyType> *)allKeysForObject:(ObjectType)anObject;
/// A new array containing the dictionary's values, or an empty array if the dictionary has no entries.
///
/// The order of the values in the array isn't defined.
@property (readonly, copy) NSArray<ObjectType> *allValues;
/// A string that represents the contents of the dictionary, formatted as a property list.
///
/// If each key in the dictionary is an `NSString` object, the entries are listed in ascending order by key, otherwise the order in which the entries are listed is undefined.  This property is intended to produce readable output for debugging purposes, not for serializing data. If you want to store dictionary data for later retrieval, see [Property List Programming Guide](https://developer.apple.com/library/archive/documentation/Cocoa/Conceptual/PropertyLists/Introduction/Introduction.html#//apple_ref/doc/uid/10000048i) and [Archives and Serializations Programming Guide](https://developer.apple.com/library/archive/documentation/Cocoa/Conceptual/Archiving/Archiving.html#//apple_ref/doc/uid/10000047i).
@property (readonly, copy) NSString *description;
/// A string that represents the contents of the dictionary, formatted in `.strings` file format.
///
/// The order in which the entries are listed is undefined.
///
/// This method fails unless the dictionary can be represented by a strings resource file. For details, see [String Resources](https://developer.apple.com/library/archive/documentation/Cocoa/Conceptual/LoadingResources/Strings/Strings.html#//apple_ref/doc/uid/10000051i-CH6) in [Resource Programming Guide](https://developer.apple.com/library/archive/documentation/Cocoa/Conceptual/LoadingResources/Introduction/Introduction.html#//apple_ref/doc/uid/10000051i).
@property (readonly, copy) NSString *descriptionInStringsFileFormat;
/// Returns a string object that represents the contents of the dictionary, formatted as a property list.
///
/// - Parameter locale: An object that specifies options used for formatting each of the dictionary's keys and values; pass `nil` if you don't want them formatted.
///
///   On iOS and macOS 10.5 and later, either an instance of `NSDictionary` or an `NSLocale` object may be used for `locale`. In OS X v10.4 and earlier it must be an instance of `NSDictionary`.
///
/// For a description of how `locale` is applied to each element in the dictionary, see ``NSDictionary/description(withLocale:indent:)``.
///
/// If each key in the dictionary responds to `compare:`, the entries are listed in ascending order by key, otherwise the order in which the entries are listed is undefined.
- (NSString *)descriptionWithLocale:(nullable id)locale;
/// Returns a string object that represents the contents of the dictionary, formatted as a property list.
///
/// - Parameters:
///   - locale: An object that specifies options used for formatting each of the dictionary's keys and values; pass `nil` if you don't want them formatted.
///
///     On iOS and macOS 10.5 and later, either an instance of `NSDictionary` or an `NSLocale` object may be used for `locale`. In OS X v10.4 and earlier it must be an instance of `NSDictionary`.
///   - level: Specifies a level of indentation, to make the output more readable: the indentation is (4 spaces) * `level`.
/// - Returns: A string object that represents the contents of the dictionary, formatted as a property list.
///
/// The returned `NSString` object contains the string representations of each of the dictionary's entries. ``NSDictionary/description(withLocale:indent:)`` obtains the string representation of a given key or value as follows:
///
/// - If the object is an `NSString` object, it is used as is.
/// - If the object responds to `descriptionWithLocale:indent:`, that method is invoked to obtain the object's string representation.
/// - If the object responds to `descriptionWithLocale:`, that method is invoked to obtain the object's string representation.
/// - If none of the above conditions is met, the object's string representation is obtained by through its `description` property.
///
/// If each key in the dictionary responds to `compare:`, the entries are listed in ascending order, by key. Otherwise, the order in which the entries are listed is undefined.
- (NSString *)descriptionWithLocale:(nullable id)locale indent:(NSUInteger)level;
/// Returns a Boolean value that indicates whether the contents of the receiving dictionary are equal to the contents of another given dictionary.
///
/// - Parameter otherDictionary: The dictionary with which to compare the receiving dictionary.
/// - Returns: `YES` if the contents of `otherDictionary` are equal to the contents of the receiving dictionary, otherwise `NO`.
///
/// Two dictionaries have equal contents if they each hold the same number of entries and, for a given key, the corresponding value objects in each dictionary satisfy the `isEqual:` test.
- (BOOL)isEqualToDictionary:(NSDictionary<KeyType, ObjectType> *)otherDictionary;
/// Returns an enumerator object that lets you access each value in the dictionary.
///
/// - Returns: An enumerator object that lets you access each value in the dictionary.
///
/// The following code fragment illustrates how you might use the method.
///
/// ```objc
/// NSEnumerator *enumerator = [myDictionary objectEnumerator];
/// id value;
///
/// while ((value = [enumerator nextObject])) {
///     /* code that acts on the dictionary's values */
/// }
/// ```
///
/// If you use this method with instances of mutable subclasses of `NSDictionary`, your code should not modify the entries during enumeration. If you intend to modify the entries, use the ``NSDictionary/allValues`` method to create a "snapshot" of the dictionary's values. Work from this snapshot to modify the values.
///
/// ### Special Considerations
///
/// It is more efficient to use the fast enumeration protocol (see ``NSFastEnumeration``). Fast enumeration is available in macOS 10.5 and later and iOS 2.0 and later.
- (NSEnumerator<ObjectType> *)objectEnumerator;
/// Returns as a static array the set of objects from the dictionary that corresponds to the specified keys.
///
/// - Parameters:
///   - keys: An `NSArray` containing the keys for which to return corresponding values.
///   - marker: The marker object to place in the corresponding element of the returned array if an object isn't found in the dictionary to correspond to a given key.
///
/// The objects in the returned array and the `keys` array have a one-for-one correspondence, so that the nth object in the returned array corresponds to the nth key in `keys`.
- (NSArray<ObjectType> *)objectsForKeys:(NSArray<KeyType> *)keys notFoundMarker:(ObjectType)marker;

/// Writes a property list representation of the contents of the dictionary to a given URL.
///
/// - Parameters:
///   - url: The URL to which to write the dictionary.
///   - error: On failure, a reference to the error that occurred.
/// - Returns: `YES` if the location is written successfully, otherwise `NO`.
///
/// This method recursively validates that all the contained objects are property list objects (instances of ``NSData``, ``NSDate``, ``NSNumber``, ``NSString``, ``NSArray``, or ``NSDictionary``) before writing out the file. The method throws an error if all the objects are not property list objects, because the resulting output wouldn't be a valid property list.
///
/// If the dictionary's contents are all property list objects, you can use the location written by this method to initialize a new dictionary with the instance method ``NSDictionary/init(contentsOfURL:)-4pv16``.
///
/// If you need greater control over the property list representation, use ``PropertyListSerialization`` instead.
///
/// For more information about property lists, see [Property List Programming Guide](https://developer.apple.com/library/archive/documentation/Cocoa/Conceptual/PropertyLists/Introduction/Introduction.html#//apple_ref/doc/uid/10000048i).
- (BOOL)writeToURL:(NSURL *)url error:(NSError **)error API_AVAILABLE(macos(10.13), ios(11.0), watchos(4.0), tvos(11.0));


/// Returns an array of the dictionary's keys, in the order they would be in if the dictionary were sorted by its values.
///
/// - Parameter comparator: A selector that specifies the method to use to compare the values in the dictionary.
///
///   The `comparator` method should return `NSOrderedAscending` if the dictionary value is smaller than the argument, `NSOrderedDescending` if the dictionary value is larger than the argument, and `NSOrderedSame` if they are equal.
/// - Returns: An array of the dictionary's keys, in the order they would be in if the dictionary were sorted by its values.
///
/// Pairs of dictionary values are compared using the comparison method specified by `comparator`; the `comparator` message is sent to one of the values and has as its single argument the other value from the dictionary.
- (NSArray<KeyType> *)keysSortedByValueUsingSelector:(SEL)comparator;
/// Returns by reference C arrays of the keys and values in the dictionary.
///
/// - Parameters:
///   - objects: Upon return, contains a C array of the values in the dictionary.
///   - keys: Upon return, contains a C array of the keys in the dictionary.
///   - count: The maximum number of objects to return.
///
/// The elements in the returned array and the keys array have a one-for-one correspondence, so that the nth object in the returned array corresponds to the the key in keys.
// count refers to the number of elements in the dictionary
- (void)getObjects:(ObjectType _Nonnull __unsafe_unretained [_Nullable])objects andKeys:(KeyType _Nonnull __unsafe_unretained [_Nullable])keys count:(NSUInteger)count API_AVAILABLE(macos(10.7), ios(5.0), watchos(2.0), tvos(9.0)) NS_SWIFT_UNAVAILABLE("Use 'allKeys' and/or 'allValues' instead");

/// Returns the value associated with a given key.
///
/// - Parameter key: The key for which to return the corresponding value.
/// - Returns: The value associated with `key`, or `nil` if no value is associated with `aKey`.
///
/// This method has the same behavior as the ``NSDictionary/object(forKey:)`` method.
///
/// You shouldn't need to call this method directly. Instead, this method is called when accessing an object by key using subscripting.
///
/// ```objc
/// id value = dictionary[@"key"]; // equivalent to [dictionary objectForKeyedSubscript:@"key"]
/// ```
- (nullable ObjectType)objectForKeyedSubscript:(KeyType)key API_AVAILABLE(macos(10.8), ios(6.0), watchos(2.0), tvos(9.0));

/// Applies a given block object to the entries of the dictionary.
///
/// - Parameter block: A block object to operate on entries in the dictionary.
///
/// If the block sets `*stop` to `YES`, the enumeration stops.
- (void)enumerateKeysAndObjectsUsingBlock:(void (NS_NOESCAPE ^)(KeyType key, ObjectType obj, BOOL *stop))block API_AVAILABLE(macos(10.6), ios(4.0), watchos(2.0), tvos(9.0));
/// Applies a given block object to the entries of the dictionary, with options specifying how the enumeration is performed.
///
/// - Parameters:
///   - opts: Enumeration options.
///   - block: A block object to operate on entries in the dictionary.
///
/// If the block sets `*stop` to `YES`, the enumeration stops.
- (void)enumerateKeysAndObjectsWithOptions:(NSEnumerationOptions)opts usingBlock:(void (NS_NOESCAPE ^)(KeyType key, ObjectType obj, BOOL *stop))block API_AVAILABLE(macos(10.6), ios(4.0), watchos(2.0), tvos(9.0));

/// Returns an array of the dictionary's keys, in the order they would be in if the dictionary were sorted by its values using a given comparator block.
///
/// - Parameter cmptr: A comparator block.
/// - Returns: An array of the dictionary's keys, in the order they would be in if the dictionary were sorted by its values using `cmptr`.
- (NSArray<KeyType> *)keysSortedByValueUsingComparator:(NSComparator NS_NOESCAPE)cmptr API_AVAILABLE(macos(10.6), ios(4.0), watchos(2.0), tvos(9.0));
/// Returns an array of the dictionary's keys, in the order they would be in if the dictionary were sorted by its values using a given comparator block and a specified set of options.
///
/// - Parameters:
///   - opts: A bitmask of sort options.
///   - cmptr: A comparator block.
/// - Returns: An array of the dictionary's keys, in the order they would be in if the dictionary were sorted by its values using `cmptr` with the options given in `opts`.
- (NSArray<KeyType> *)keysSortedByValueWithOptions:(NSSortOptions)opts usingComparator:(NSComparator NS_NOESCAPE)cmptr API_AVAILABLE(macos(10.6), ios(4.0), watchos(2.0), tvos(9.0));

/// Returns the set of keys whose corresponding value satisfies a constraint described by a block object.
///
/// - Parameter predicate: A block object that specifies constraints for values in the dictionary.
/// - Returns: The set of keys whose corresponding value satisfies `predicate`.
- (NSSet<KeyType> *)keysOfEntriesPassingTest:(BOOL (NS_NOESCAPE ^)(KeyType key, ObjectType obj, BOOL *stop))predicate API_AVAILABLE(macos(10.6), ios(4.0), watchos(2.0), tvos(9.0));
/// Returns the set of keys whose corresponding value satisfies a constraint described by a block object.
///
/// - Parameters:
///   - opts: A bit mask of enumeration options.
///   - predicate: A block object that specifies constraints for values in the dictionary.
/// - Returns: The set of keys whose corresponding value satisfies `predicate`.
- (NSSet<KeyType> *)keysOfEntriesWithOptions:(NSEnumerationOptions)opts passingTest:(BOOL (NS_NOESCAPE ^)(KeyType key, ObjectType obj, BOOL *stop))predicate API_AVAILABLE(macos(10.6), ios(4.0), watchos(2.0), tvos(9.0));

@end

@interface NSDictionary<KeyType, ObjectType> (NSDeprecated)
/// Returns by reference C arrays of the keys and values in the dictionary.
///
/// - Parameters:
///   - objects: Upon return, contains a C array of the values in the dictionary.
///   - keys: Upon return, contains a C array of the keys in the dictionary.
///
/// The elements in the returned array and the keys array have a one-for-one correspondence, so that the nth object in the returned array corresponds to the the key in keys.
///
/// > Deprecated: Use ``NSDictionary/getObjects:andKeys:count:`` instead.
/// This method is unsafe because it could potentially cause buffer overruns. You should use -getObjects:andKeys:count:
- (void)getObjects:(ObjectType _Nonnull __unsafe_unretained [_Nullable])objects andKeys:(KeyType _Nonnull __unsafe_unretained [_Nullable])keys  NS_SWIFT_UNAVAILABLE("Use 'allKeys' and/or 'allValues' instead")  API_DEPRECATED("Use -getObjects:andKeys:count: instead", macos(10.0, 10.13), ios(2.0, 11.0), watchos(2.0, 4.0), tvos(9.0, 11.0));

/// Creates a dictionary using the keys and values found in a file specified by a given path.
///
/// - Parameter path: A full or relative pathname. The file identified by `path` must contain a string representation of a property list whose root object is a dictionary.
/// - Returns: A new dictionary that contains the dictionary at `path`, or `nil` if there is a file error or if the contents of the file are an invalid representation of a dictionary.
///
/// The dictionary representation in the file identified by `path` must contain only property list objects (`NSString`, `NSData`, `NSDate`, `NSNumber`, `NSArray`, or `NSDictionary` objects). For more details, see [Property List Programming Guide](https://developer.apple.com/library/archive/documentation/Cocoa/Conceptual/PropertyLists/Introduction/Introduction.html#//apple_ref/doc/uid/10000048i). The objects contained by this dictionary are immutable, even if the dictionary is mutable.
/* These methods are deprecated, and will be marked with API_DEPRECATED in a subsequent release. Use the variants that use errors instead. */
+ (nullable NSDictionary<KeyType, ObjectType> *)dictionaryWithContentsOfFile:(NSString *)path API_DEPRECATED_WITH_REPLACEMENT("dictionaryWithContentsOfURL:error:", macos(10.0, API_TO_BE_DEPRECATED), ios(2.0, API_TO_BE_DEPRECATED), watchos(2.0, API_TO_BE_DEPRECATED), tvos(9.0, API_TO_BE_DEPRECATED));
/// Creates a dictionary using the keys and values found in a resource specified by a given URL.
///
/// - Parameter url: An URL that identifies a resource containing a string representation of a property list whose root object is a dictionary.
/// - Returns: A new dictionary that contains the dictionary at `aURL`, or `nil` if there is an error or if the contents of the resource are an invalid representation of a dictionary.
///
/// The dictionary representation in the file identified by `aURL` must contain only property list objects (`NSString`, `NSData`, `NSDate`, `NSNumber`, `NSArray`, or `NSDictionary` objects). For more details, see [Property List Programming Guide](https://developer.apple.com/library/archive/documentation/Cocoa/Conceptual/PropertyLists/Introduction/Introduction.html#//apple_ref/doc/uid/10000048i). The objects contained by this dictionary are immutable, even if the dictionary is mutable.
///
/// > Deprecated: Use ``NSDictionary/dictionaryWithContentsOfURL:error:`` instead.
+ (nullable NSDictionary<KeyType, ObjectType> *)dictionaryWithContentsOfURL:(NSURL *)url API_DEPRECATED_WITH_REPLACEMENT("dictionaryWithContentsOfURL:error:", macos(10.0, API_TO_BE_DEPRECATED), ios(2.0, API_TO_BE_DEPRECATED), watchos(2.0, API_TO_BE_DEPRECATED), tvos(9.0, API_TO_BE_DEPRECATED));
/// Initializes a newly allocated dictionary using the keys and values found in a file at a given path.
///
/// - Parameter path: A full or relative pathname. The file identified by `path` must contain a string representation of a property list whose root object is a dictionary.
/// - Returns: An initialized dictionary---which might be different than the original receiver---that contains the dictionary at `path`, or `nil` if there is a file error or if the contents of the file are an invalid representation of a dictionary.
///
/// The dictionary representation in the file identified by `path` must contain only property list objects (`NSString`, `NSData`, `NSDate`, `NSNumber`, `NSArray`, or `NSDictionary` objects). For more details, see [Property List Programming Guide](https://developer.apple.com/library/archive/documentation/Cocoa/Conceptual/PropertyLists/Introduction/Introduction.html#//apple_ref/doc/uid/10000048i). The objects contained by this dictionary are immutable, even if the dictionary is mutable.
- (nullable NSDictionary<KeyType, ObjectType> *)initWithContentsOfFile:(NSString *)path API_DEPRECATED_WITH_REPLACEMENT("initWithContentsOfURL:error:", macos(10.0, API_TO_BE_DEPRECATED), ios(2.0, API_TO_BE_DEPRECATED), watchos(2.0, API_TO_BE_DEPRECATED), tvos(9.0, API_TO_BE_DEPRECATED));
/// Initializes a newly allocated dictionary using the keys and values found at a given URL.
///
/// - Parameter url: An URL that identifies a resource containing a string representation of a property list whose root object is a dictionary.
/// - Returns: An initialized dictionary---which might be different than the original receiver---that contains the dictionary at `url`, or `nil` if there is an error or if the contents of the resource are an invalid representation of a dictionary.
///
/// The dictionary representation in the file identified by `url` must contain only property list objects (`NSString`, `NSData`, `NSDate`, `NSNumber`, `NSArray`, or `NSDictionary` objects). For more details, see [Property List Programming Guide](https://developer.apple.com/library/archive/documentation/Cocoa/Conceptual/PropertyLists/Introduction/Introduction.html#//apple_ref/doc/uid/10000048i). The objects contained by this dictionary are immutable, even if the dictionary is mutable.
///
/// > Deprecated: Use ``NSDictionary/init(contentsOfURL:error:)`` instead.
- (nullable NSDictionary<KeyType, ObjectType> *)initWithContentsOfURL:(NSURL *)url API_DEPRECATED_WITH_REPLACEMENT("initWithContentsOfURL:error:", macos(10.0, API_TO_BE_DEPRECATED), ios(2.0, API_TO_BE_DEPRECATED), watchos(2.0, API_TO_BE_DEPRECATED), tvos(9.0, API_TO_BE_DEPRECATED));

/// Writes a property list representation of the contents of the dictionary to a given path.
///
/// - Parameters:
///   - path: The path at which to write the file.
///
///     If `path` contains a tilde (~) character, you must expand it with ``NSString/expandingTildeInPath`` before invoking this method.
///   - useAuxiliaryFile: A flag that specifies whether the file should be written atomically.
///
///     If `useAuxiliaryFile` is `YES`, the dictionary is written to an auxiliary file, and then the auxiliary file is renamed to `path`. If `useAuxiliaryFile` is `NO`, the dictionary is written directly to `path`. The `YES` option guarantees that `path`, if it exists at all, won't be corrupted even if the system should crash during writing.
/// - Returns: `YES` if the file is written successfully, otherwise `NO`.
///
/// This method recursively validates that all the contained objects are property list objects (instances of `NSData`, `NSDate`, `NSNumber`, `NSString`, `NSArray`, or `NSDictionary`) before writing out the file, and returns `NO` if all the objects are not property list objects, since the resultant file would not be a valid property list.
///
/// If the dictionary's contents are all property list objects, the file written by this method can be used to initialize a new dictionary with the class method ``NSDictionary/dictionaryWithContentsOfFile:`` or the instance method ``NSDictionary/init(contentsOfFile:)``.
///
/// If you need greater control over the property list representation, use ``PropertyListSerialization`` instead.
///
/// For more information about property lists, see [Property List Programming Guide](https://developer.apple.com/library/archive/documentation/Cocoa/Conceptual/PropertyLists/Introduction/Introduction.html#//apple_ref/doc/uid/10000048i).
///
/// > Deprecated: Use ``NSDictionary/write(to:)`` instead.
- (BOOL)writeToFile:(NSString *)path atomically:(BOOL)useAuxiliaryFile API_DEPRECATED_WITH_REPLACEMENT("writeToURL:error:", macos(10.0, API_TO_BE_DEPRECATED), ios(2.0, API_TO_BE_DEPRECATED), watchos(2.0, API_TO_BE_DEPRECATED), tvos(9.0, API_TO_BE_DEPRECATED));
/// Writes a property list representation of the contents of the dictionary to a given URL.
///
/// - Parameters:
///   - url: The URL to which to write the dictionary.
///   - atomically: A flag that specifies whether the output should be written atomically.
///
///     If `atomically` is `YES`, the dictionary is written to an auxiliary location, and then the auxiliary location is renamed to `url`. If `atomically` is `NO`, the dictionary is written directly to `url`. The `YES` option guarantees that `url`, if it exists at all, won't be corrupted even if the system should crash during writing. `atomically` is ignored if `url` is of a type that cannot be written atomically.
/// - Returns: `YES` if the location is written successfully, otherwise `NO`.
///
/// This method recursively validates that all the contained objects are property list objects (instances of `NSData`, `NSDate`, `NSNumber`, `NSString`, `NSArray`, or `NSDictionary`) before writing out the file, and returns `NO` if all the objects are not property list objects, since the resultant output would not be a valid property list.
///
/// If the dictionary's contents are all property list objects, the location written by this method can be used to initialize a new dictionary with the class method ``NSDictionary/init(contentsOfURL:)-98pl3`` or the instance method ``NSDictionary/init(contentsOfURL:)-4pv16``.
///
/// If you need greater control over the property list representation, use ``PropertyListSerialization`` instead.
///
/// For more information about property lists, see [Property List Programming Guide](https://developer.apple.com/library/archive/documentation/Cocoa/Conceptual/PropertyLists/Introduction/Introduction.html#//apple_ref/doc/uid/10000048i).
///
/// > Deprecated: Use ``NSDictionary/write(to:)`` instead.
- (BOOL)writeToURL:(NSURL *)url atomically:(BOOL)atomically API_DEPRECATED_WITH_REPLACEMENT("writeToURL:error:", macos(10.0, API_TO_BE_DEPRECATED), ios(2.0, API_TO_BE_DEPRECATED), watchos(2.0, API_TO_BE_DEPRECATED), tvos(9.0, API_TO_BE_DEPRECATED)); // the atomically flag is ignored if url of a type that cannot be written atomically.
@end

@interface NSDictionary<KeyType, ObjectType> (NSDictionaryCreation)

/// Creates an empty dictionary.
///
/// - Returns: A new empty dictionary.
///
/// This method is declared primarily for use with mutable subclasses of ``NSDictionary``.
///
/// If you don't want a temporary object, you can also create an empty dictionary using `alloc` and ``NSDictionary/init()``.
+ (instancetype)dictionary;
/// Creates a dictionary containing a given key and value.
///
/// - Parameters:
///   - object: The value corresponding to `aKey`.
///
///     If this value is `nil`, an ``NSExceptionName/invalidArgumentException`` is raised.
///   - key: The key for `anObject`.
///
///     If this value is `nil`, an ``NSExceptionName/invalidArgumentException`` is raised.
/// - Returns: A new dictionary containing a single object, `object`, for a single key, `aKey`.
+ (instancetype)dictionaryWithObject:(ObjectType)object forKey:(KeyType <NSCopying>)key;
/// Creates a dictionary containing a specified number of objects from a C array.
///
/// - Parameters:
///   - objects: A C array of values for the new dictionary.
///   - keys: A C array of keys for the new dictionary. Each key is copied (using ``NSCopying/copy(with:)``; keys must conform to the `NSCopying` protocol), and the copy is added to the new dictionary.
///   - cnt: The number of elements to use from the `keys` and `objects` arrays. `cnt` must not exceed the number of elements in `objects` or `keys`.
///
/// This method steps through the `objects` and `keys` arrays, creating entries in the new dictionary as it goes. An `NSInvalidArgumentException` is raised if a key or value object is `nil`.
///
/// The following code fragment illustrates how to create a dictionary that associates the alphabetic characters with their ASCII values:
///
/// ```objc
/// static const NSInteger N_ENTRIES = 26;
/// NSDictionary *asciiDict;
/// NSString *keyArray[N_ENTRIES];
/// NSNumber *valueArray[N_ENTRIES];
/// NSInteger i;
///
/// for (i = 0; i < N_ENTRIES; i++) {
///
///     char charValue = 'a' + i;
///     keyArray[i] = [NSString stringWithFormat:@"%c", charValue];
///     valueArray[i] = [NSNumber numberWithChar:charValue];
/// }
///
/// asciiDict = [NSDictionary dictionaryWithObjects:(id *)valueArray
///                           forKeys:(id *)keyArray count:N_ENTRIES];
/// ```
+ (instancetype)dictionaryWithObjects:(const ObjectType _Nonnull [_Nullable])objects forKeys:(const KeyType <NSCopying> _Nonnull [_Nullable])keys count:(NSUInteger)cnt;

/// Creates a dictionary containing entries constructed from the specified set of values and keys.
///
/// - Parameter firstObject: The first value to add to the new dictionary.
///
/// After passing `firstObj`, pass a null-terminated list of alternating values and keys as variadic arguments. If any key is `nil`, an ``NSExceptionName/invalidArgumentException`` is raised.
///
/// This method is similar to ``NSDictionary/dictionaryWithObjects:forKeys:``, differing only in the way key-value pairs are specified.
///
/// For example:
///
/// ```objc
/// NSDictionary *dict = [NSDictionary dictionaryWithObjectsAndKeys:
///     @"value1", @"key1", @"value2", @"key2", nil];
/// ```
+ (instancetype)dictionaryWithObjectsAndKeys:(id)firstObject, ... NS_REQUIRES_NIL_TERMINATION NS_SWIFT_UNAVAILABLE("Use dictionary literals instead");

/// Creates a dictionary containing the keys and values from another given dictionary.
///
/// - Parameter dict: A dictionary containing the keys and values with which to initialize the new dictionary.
/// - Returns: A new dictionary containing the keys and values found in `dict`.
+ (instancetype)dictionaryWithDictionary:(NSDictionary<KeyType, ObjectType> *)dict;
/// Creates a dictionary containing entries constructed from the contents of an array of keys and an array of values.
///
/// - Parameters:
///   - objects: An array containing the values for the new dictionary.
///   - keys: An array containing the keys for the new dictionary. Each key is copied (using ``NSCopying/copy(with:)``; keys must conform to the `NSCopying` protocol), and the copy is added to the dictionary.
/// - Returns: A new dictionary containing entries constructed from the contents of `objects` and `keys`.
///
/// This method steps through the `objects` and `keys` arrays, creating entries in the new dictionary as it goes. An `NSInvalidArgumentException` is raised if objects and keys don't have the same number of elements.
+ (instancetype)dictionaryWithObjects:(NSArray<ObjectType> *)objects forKeys:(NSArray<KeyType <NSCopying>> *)keys;

/// Initializes a newly allocated dictionary with entries constructed from the specified set of values and keys.
///
/// - Parameter firstObject: The first value to add to the new dictionary.
///
/// After the `firstObject` value, pass the key for `firstObject`, then a null-terminated list of alternating values and keys. If any key is `nil`, an ``NSExceptionName/invalidArgumentException`` is raised.
///
/// This method is similar to ``NSDictionary/init(objects:forKeys:)``, differing only in the way in which the key-value pairs are specified.
///
/// For example:
///
/// ```objc
/// NSDictionary *dict = [[NSDictionary alloc] initWithObjectsAndKeys:
///     @"value1", @"key1", @"value2", @"key2", nil];
/// ```
- (instancetype)initWithObjectsAndKeys:(id)firstObject, ... NS_REQUIRES_NIL_TERMINATION;
/// Initializes a newly allocated dictionary by placing in it the keys and values contained in another given dictionary.
///
/// - Parameter otherDictionary: A dictionary containing the keys and values with which to initialize the new dictionary.
/// - Returns: An initialized dictionary---which might be different than the original receiver---containing the keys and values found in `otherDictionary`.
- (instancetype)initWithDictionary:(NSDictionary<KeyType, ObjectType> *)otherDictionary;
/// Initializes a newly allocated dictionary using the objects contained in another given dictionary.
///
/// - Parameters:
///   - otherDictionary: A dictionary containing the keys and values with which to initialize the new dictionary.
///   - flag: If `YES`, each object in `otherDictionary` receives a `copyWithZone:` message to create a copy of the object---objects must conform to the `NSCopying` protocol. In a managed memory environment, this is instead of the `retain` message the object would otherwise receive. The object copy is then added to the returned dictionary.
///
///     If `NO`, then in a managed memory environment each object in `otherDictionary` simply receives a `retain` message when it is added to the returned dictionary.
/// - Returns: An initialized object---which might be different than the original receiver---containing the keys and values found in `otherDictionary`.
///
/// After an immutable dictionary has been initialized in this way, it cannot be modified.
///
/// The ``NSCopying/copy(with:)`` method performs a shallow copy. If you have a collection of arbitrary depth, passing `YES` for the `flag` parameter will perform an immutable copy of the first level below the surface. If you pass `NO` the mutability of the first level is unaffected. In either case, the mutability of all deeper levels is unaffected.
- (instancetype)initWithDictionary:(NSDictionary<KeyType, ObjectType> *)otherDictionary copyItems:(BOOL)flag;
/// Initializes a newly allocated dictionary with key-value pairs constructed from the provided arrays of keys and objects.
///
/// - Parameters:
///   - objects: An array containing the values for the new dictionary.
///   - keys: An array containing the keys for the new dictionary. Each key is copied (using ``NSCopying/copy(with:)``; keys must conform to the `NSCopying` protocol), and the copy is added to the new dictionary.
///
/// This method steps through the `objects` and `keys` arrays, creating entries in the new dictionary as it goes. An `NSInvalidArgumentException` is raised if the objects and keys arrays do not have the same number of elements.
- (instancetype)initWithObjects:(NSArray<ObjectType> *)objects forKeys:(NSArray<KeyType <NSCopying>> *)keys;

/// Initializes a newly allocated dictionary using the keys and values found at a given URL.
///
/// - Parameters:
///   - url: A URL that identifies a resource containing a string representation of a property list whose root object is a dictionary.
///   - error: On failure, a reference to the error that occurred.
/// - Returns: An initialized dictionary that contains the dictionary at `url`, or `nil` if there is an error or if the contents of the resource are an invalid representation of a dictionary.
///
/// The dictionary representation in the file identified by `url` must contain only property list objects (``NSString``, ``NSData``, ``NSDate``, ``NSNumber``, ``NSArray``, or ``NSDictionary`` objects). For more details, see [Property List Programming Guide](https://developer.apple.com/library/archive/documentation/Cocoa/Conceptual/PropertyLists/Introduction/Introduction.html#//apple_ref/doc/uid/10000048i). The objects contained by this dictionary are immutable, even if the dictionary is mutable.
///
/// In Swift, this initializer throws if there is an error loading the URL, or if the contents of the resource are an invalid representation of a dictionary.
- (nullable NSDictionary<NSString *, ObjectType> *)initWithContentsOfURL:(NSURL *)url error:(NSError **)error API_AVAILABLE(macos(10.13), ios(11.0), watchos(4.0), tvos(11.0));

/// Creates a dictionary using the keys and values found in a resource specified by a given URL.
///
/// - Parameter url: A URL that identifies a resource containing a string representation of a property list whose root object is a dictionary.
/// - Returns: A new dictionary that contains the dictionary at `url`, or `nil` if there is an error or if the contents of the resource are an invalid representation of a dictionary.
///
/// The dictionary representation in the file identified by path must contain only property list objects (``NSString``, ``NSData``, ``NSDate``, ``NSNumber``, ``NSArray``, or ``NSDictionary`` objects). For more details, see [Property List Programming Guide](https://developer.apple.com/library/archive/documentation/Cocoa/Conceptual/PropertyLists/Introduction/Introduction.html#//apple_ref/doc/uid/10000048i). The objects contained by this dictionary are immutable, even if the dictionary is mutable.
/* Reads dictionary stored in NSPropertyList format from the specified url. */
+ (nullable NSDictionary<NSString *, ObjectType> *)dictionaryWithContentsOfURL:(NSURL *)url error:(NSError **)error API_AVAILABLE(macos(10.13), ios(11.0), watchos(4.0), tvos(11.0)) NS_SWIFT_UNAVAILABLE("Use initializer instead");

@end

/* ***************	Mutable Dictionary	****************/

/// A dynamic collection of objects associated with unique keys.
///
/// In Swift, you can use this type instead of a `Dictionary` variable in cases that require reference semantics.
///
/// The `NSMutableDictionary` class declares the programmatic interface to objects that manage mutable associations of keys and values. It adds modification operations to the basic operations it inherits from ``NSDictionary``.
///
/// `NSMutableDictionary` is "toll-free bridged" with its Core Foundation counterpart, `CFMutableDictionary`. See [Toll-Free Bridging](https://developer.apple.com/library/archive/documentation/General/Conceptual/CocoaEncyclopedia/Toll-FreeBridgin/Toll-FreeBridgin.html#//apple_ref/doc/uid/TP40010810-CH2) for more information on toll-free bridging.
///
/// ### Setting Values Using Subscripting
///
/// In addition to the provided instance methods, such as ``setObject(_:forKey:)``, you can access `NSDictionary` values by their keys using _subscripting_.
///
/// ```objc
/// id value = @"someValue";
/// mutableDictionary[@"someKey"] = value;
/// ```
///
/// ### Subclassing Notes
///
/// There should typically be little need to subclass `NSMutableDictionary`. If you do need to customize behavior, it is often better to consider composition rather than subclassing.
///
/// #### Methods to Override
///
/// In a subclass, you must override both of its primitive methods:
///
/// - ``setObject(_:forKey:)``
/// - ``removeObject(forKey:)``
///
/// You must also override the primitive methods of the ``NSDictionary`` class.
@interface NSMutableDictionary<KeyType, ObjectType> : NSDictionary<KeyType, ObjectType>

/// Removes a given key and its associated value from the dictionary.
///
/// - Parameter aKey: The key to remove.
///
///   > Important:
///   > Raises an ``NSExceptionName/invalidArgumentException`` if `aKey` is `nil`.
///
/// Does nothing if `aKey` does not exist.
///
/// For example, assume you have an archived dictionary that records the call letters and associated frequencies of radio stations. To remove an entry for a defunct station, you could write code similar to the following:
///
/// ```objc
/// NSMutableDictionary *stations = nil;
///
/// stations = [[NSMutableDictionary alloc]
///         initWithContentsOfFile: pathToArchive];
/// [stations removeObjectForKey:@"KIKT"];
/// ```
- (void)removeObjectForKey:(KeyType)aKey;
/// Adds a given key-value pair to the dictionary.
///
/// - Parameters:
///   - anObject: The value for `aKey`. A strong reference to the object is maintained by the dictionary.
///
///     > Important:
///     > Raises an ``NSExceptionName/invalidArgumentException`` if `anObject` is `nil`. If you need to represent a `nil` value in the dictionary, use ``NSNull``.
///   - aKey: The key for `value`. The key is copied (using ``NSCopying/copy(with:)``; keys must conform to the `NSCopying` protocol). If `aKey` already exists in the dictionary, `anObject` takes its place.
///
///     > Important:
///     > Raises an ``NSExceptionName/invalidArgumentException`` if `aKey` is `nil`.
- (void)setObject:(ObjectType)anObject forKey:(KeyType <NSCopying>)aKey;
/// Initializes a newly allocated mutable dictionary.
///
/// - Returns: A mutable dictionary.
///
/// This method is a designated initializer of `NSMutableDictionary`.
- (instancetype)init NS_DESIGNATED_INITIALIZER;
/// Initializes a newly allocated mutable dictionary, allocating enough memory to hold `numItems` entries.
///
/// - Parameter numItems: The initial capacity of the initialized dictionary.
/// - Returns: An initialized mutable dictionary, which might be different than the original receiver.
///
/// Mutable dictionaries allocate additional memory as needed, so `numItems` simply establishes the object's initial capacity.
///
/// This method is a designated initializer of `NSMutableDictionary`.
- (instancetype)initWithCapacity:(NSUInteger)numItems NS_DESIGNATED_INITIALIZER;
- (nullable instancetype)initWithCoder:(NSCoder *)coder NS_DESIGNATED_INITIALIZER;

@end

@interface NSMutableDictionary<KeyType, ObjectType> (NSExtendedMutableDictionary)

/// Adds to the receiving dictionary the entries from another dictionary.
///
/// - Parameter otherDictionary: The dictionary from which to add entries
///
/// Each value object from `otherDictionary` is sent a `retain` message before being added to the receiving dictionary. In contrast, each key object is copied (using ``NSCopying/copy(with:)``---keys must conform to the `NSCopying` protocol), and the copy is added to the receiving dictionary.
///
/// If both dictionaries contain the same key, the receiving dictionary's previous value object for that key is sent a `release` message, and the new value object takes its place.
- (void)addEntriesFromDictionary:(NSDictionary<KeyType, ObjectType> *)otherDictionary;
/// Empties the dictionary of its entries.
///
/// Each key and corresponding value object is sent a `release` message.
- (void)removeAllObjects;
/// Removes from the dictionary entries specified by elements in a given array.
///
/// - Parameter keyArray: An array of objects specifying the keys to remove.
///
/// If a key in `keyArray` does not exist, the entry is ignored.
- (void)removeObjectsForKeys:(NSArray<KeyType> *)keyArray;
/// Sets the contents of the receiving dictionary to entries in a given dictionary.
///
/// - Parameter otherDictionary: A dictionary containing the new entries.
///
/// All entries are removed from the receiving dictionary (with ``NSMutableDictionary/removeAllObjects()``), then each entry from `otherDictionary` added into the receiving dictionary.
- (void)setDictionary:(NSDictionary<KeyType, ObjectType> *)otherDictionary;
/// Adds a given key-value pair to the dictionary.
///
/// - Parameters:
///   - obj: The value for `key`. A strong reference to the object is maintained by the dictionary.
///
///     Passing `nil` will cause any object corresponding to `key` to be removed from the dictionary.
///   - key: The key for `obj`. The key is copied (using ``NSCopying/copy(with:)``; keys must conform to the `NSCopying` protocol). If `key` already exists in the dictionary, `anObject` takes its place.
///
///     > Important:
///     > Raises an ``NSExceptionName/invalidArgumentException`` if `key` is `nil`.
///
/// This method has the same behavior as the ``NSMutableDictionary/setObject(_:forKey:)`` method.
///
/// You shouldn't need to call this method directly. Instead, this method is called when setting an object for a key using subscripting.
///
/// ```objc
/// id value = @"someValue";
/// mutableDictionary[@"someKey"] = value;
/// ```
- (void)setObject:(nullable ObjectType)obj forKeyedSubscript:(KeyType <NSCopying>)key API_AVAILABLE(macos(10.8), ios(6.0), watchos(2.0), tvos(9.0));

@end

@interface NSMutableDictionary<KeyType, ObjectType> (NSMutableDictionaryCreation)

/// Creates and returns a mutable dictionary, initially giving it enough allocated memory to hold a given number of entries.
///
/// - Parameter numItems: The initial capacity of the new dictionary.
/// - Returns: A new mutable dictionary with enough allocated memory to hold `numItems` entries.
///
/// Mutable dictionaries allocate additional memory as needed, so `numItems` simply establishes the object's initial capacity.
+ (instancetype)dictionaryWithCapacity:(NSUInteger)numItems;

+ (nullable NSMutableDictionary<KeyType, ObjectType> *)dictionaryWithContentsOfFile:(NSString *)path;
+ (nullable NSMutableDictionary<KeyType, ObjectType> *)dictionaryWithContentsOfURL:(NSURL *)url;
- (nullable NSMutableDictionary<KeyType, ObjectType> *)initWithContentsOfFile:(NSString *)path;
- (nullable NSMutableDictionary<KeyType, ObjectType> *)initWithContentsOfURL:(NSURL *)url;

@end

@interface NSDictionary<KeyType, ObjectType> (NSSharedKeySetDictionary)

/// Creates a shared key set object for the specified keys.
///
/// - Parameter keys: The array of keys. If the parameter is nil, an exception is thrown. If the array of keys is empty, an empty key set is returned.
/// - Returns: A shared key set object.
///
/// The array of `keys` may contain duplicates which are quietly ignored. Duplicate hash values of the keys are quietly allowed, but may cause lower performance and increase memory usage.
///
/// Typically you would create a shared key set for a given set of keys once, before creating shared key dictionaries, and retain and save the result of this method for use with the ``NSMutableDictionary`` class method `dictionaryWithSharedKeySet:.`
+ (id)sharedKeySetForKeys:(NSArray<KeyType <NSCopying>> *)keys API_AVAILABLE(macos(10.8), ios(6.0), watchos(2.0), tvos(9.0));

@end

@interface NSMutableDictionary<KeyType, ObjectType> (NSSharedKeySetDictionary)

/// Creates a mutable dictionary which is optimized for dealing with a known set of keys.
///
/// - Parameter keyset: The `keyset`, created by the ``NSDictionary`` class method ``NSDictionary/sharedKeySet(forKeys:)``.
///
///   > Important:
///   > If `keyset` is `nil`, an exception is raised. If `keyset` is not an object returned by ``NSDictionary/sharedKeySet(forKeys:)``, an exception is raised.
/// - Returns: A new mutable dictionary optimized for a known set of keys.
///
/// Keys that are not in the key set can still be set in the dictionary, but that usage is not optimal.
+ (NSMutableDictionary<KeyType, ObjectType> *)dictionaryWithSharedKeySet:(id)keyset API_AVAILABLE(macos(10.8), ios(6.0), watchos(2.0), tvos(9.0));

@end

@interface NSDictionary<K, V> (NSGenericFastEnumeration) <NSFastEnumeration>
/// Returns by reference a C array of objects over which the sender should iterate.
///
/// - Parameters:
///   - state: Context information that is used in the enumeration to, in addition to other possibilities, ensure that the collection has not been mutated.
///   - buffer: A C array of objects over which the sender is to iterate.
///   - len: The maximum number of objects to return in `buffer`.
/// - Returns: The number of objects returned in `buffer`. Returns `0` when the iteration is finished.
- (NSUInteger)countByEnumeratingWithState:(NSFastEnumerationState *)state objects:(K __unsafe_unretained _Nullable [_Nonnull])buffer count:(NSUInteger)len;
@end

NS_HEADER_AUDIT_END(nullability, sendability)
