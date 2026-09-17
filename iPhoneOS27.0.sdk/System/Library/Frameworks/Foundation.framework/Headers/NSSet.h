/*	NSSet.h
	Copyright (c) 1994-2019, Apple Inc. All rights reserved.
*/

#import <Foundation/NSObject.h>
#import <Foundation/NSEnumerator.h>

@class NSArray, NSDictionary, NSString;

/* ***************	Immutable Set	****************/

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

/// A static, unordered collection of unique objects.
///
/// The `NSSet`, `NSMutableSet`, and `NSCountedSet` classes declare the programmatic interface to an unordered collection of objects.
///
/// `NSSet` declares the programmatic interface for static sets of distinct objects. You establish a static set's entries when it's created, and can't modify the entries after that. `NSMutableSet`, on the other hand, declares a programmatic interface for dynamic sets of distinct objects. A dynamic — or mutable — set allows the addition and deletion of entries at any time, automatically allocating memory as needed.
///
/// Use sets as an alternative to arrays when the order of elements isn't important and you need to consider performance in testing whether the set contains an object. With an array, testing for membership is slower than with sets.
///
/// `NSSet` is "toll-free bridged" with its Core Foundation counterpart, `CFSet`. See [Toll-Free Bridging](https://developer.apple.com/library/archive/documentation/General/Conceptual/CocoaEncyclopedia/Toll-FreeBridgin/Toll-FreeBridgin.html#//apple_ref/doc/uid/TP40010810-CH2) for more information on toll-free bridging.
///
/// In Swift, use this class instead of a `Set` constant in cases where you require reference semantics.
///
/// ### Subclassing Notes
///
/// There should be little need of subclassing. If you need to customize behavior, it's often better to consider composition instead of subclassing.
///
/// #### Methods to Override
///
/// In a subclass, you must override all of its primitive methods:
///
/// - `count`
/// - `member:`
/// - `objectEnumerator`
///
/// #### Alternatives to Subclassing
///
/// Before making a custom class of `NSSet`, investigate `NSHashTable` and the corresponding Core Foundation type, `CFSet`. Because `NSSet` and `CFSet` are "toll-free bridged," you can substitute a `CFSet` object for a `NSSet` object in your code (with appropriate casting). Although they're corresponding types, `CFSet` and `NSSet` don't have identical interfaces or implementations, and you can sometimes do things with `CFSet` that you can't easily do with `NSSet`.
///
/// If the behavior you want to add supplements that of the existing class, you could write a category on `NSSet`. Keep in mind, however, that this category affects all instances of `NSSet` that you use, and this might have unintended consequences. Alternatively, you could use composition to achieve the desired behavior.
@interface NSSet<__covariant ObjectType> : NSObject <NSCopying, NSMutableCopying, NSSecureCoding, NSFastEnumeration>

/// The number of members in the set.
@property (readonly) NSUInteger count;
/// Determines whether a given object is present in the set, and returns that object if it is.
///
/// Each element of the set is checked for equality with `object` until a match is found or the end of the set is reached.  Objects are considered equal if `isEqual:` returns `YES`.
///
/// - Parameter object: An object to look for in the set.
/// - Returns: Returns an object equal to `object` if it's present in the set, otherwise `nil`.
- (nullable ObjectType)member:(ObjectType)object;
/// Returns an enumerator object that lets you access each object in the set.
///
/// The following code fragment illustrates how you can use this method.
///
/// ```objc
/// NSEnumerator *enumerator = [mySet objectEnumerator];
/// id value;
///
/// while ((value = [enumerator nextObject])) {
///     /* code that acts on the set's values */
/// }
/// ```
///
/// When this method is used with mutable subclasses of `NSSet`, your code shouldn't modify the set during enumeration. If you intend to modify the set, use the `allObjects` method to create a "snapshot" of the set's members. Enumerate the snapshot, but make your modifications to the original set.
///
/// ### Special Considerations
///
/// It is more efficient to use the fast enumeration protocol (see `NSFastEnumeration`). Fast enumeration is available in macOS 10.5 and later and iOS 2.0 and later.
///
/// - Returns: An enumerator object that lets you access each object in the set.
- (NSEnumerator<ObjectType> *)objectEnumerator;
/// Initializes a newly allocated set.
///
/// This method is a designated initializer of `NSSet`.
///
/// - Returns: A set.
- (instancetype)init NS_DESIGNATED_INITIALIZER;
/// Initializes a newly allocated set with a specified number of objects from a given C array of objects.
///
/// This method is a designated initializer for `NSSet`.
///
/// - Parameters:
///   - objects: A C array of objects to add to the new set. If the same object appears more than once in `objects`, it is added only once to the returned set. Each object receives a `retain` message as it is added to the set.
///   - cnt: The number of objects from `objects` to add to the new set.
/// - Returns: An initialized set containing `cnt` objects from the list of objects specified by `objects`. The returned set might be different than the original receiver.
- (instancetype)initWithObjects:(const ObjectType _Nonnull [_Nullable])objects count:(NSUInteger)cnt NS_DESIGNATED_INITIALIZER;
- (nullable instancetype)initWithCoder:(NSCoder *)coder NS_DESIGNATED_INITIALIZER;

@end

@interface NSSet<ObjectType> (NSExtendedSet)

/// An array containing the set's members, or an empty array if the set has no members.
///
/// The order of the objects in the array is undefined.
@property (readonly, copy) NSArray<ObjectType> *allObjects;
/// Returns one of the objects in the set, or `nil` if the set contains no objects.
///
/// - Returns: One of the objects in the set, or `nil` if the set contains no objects. The object returned is chosen at the set's convenience—the selection is not guaranteed to be random.
- (nullable ObjectType)anyObject;
/// Returns a Boolean value that indicates whether a given object is present in the set.
///
/// Each element of the set is checked for equality with `anObject` until a match is found or the end of the set is reached.  Objects are considered equal if `isEqual:` returns `YES`.
///
/// - Parameter anObject: An object to look for in the set.
/// - Returns: `YES` if `anObject` is present in the set, otherwise `NO`.
- (BOOL)containsObject:(ObjectType)anObject;
/// A string that represents the contents of the set, formatted as a property list.
@property (readonly, copy) NSString *description;
/// Returns a string that represents the contents of the set, formatted as a property list.
///
/// This method sends each of the set's members  `descriptionWithLocale:` with `locale` passed as the sole parameter. If the set's members do not respond to `descriptionWithLocale:`, this method sends `description` instead.
///
/// - Parameter locale: On iOS and macOS 10.5 and later, either an instance of `NSDictionary` or an `NSLocale` object may be used for `locale`.In OS X v10.4 and earlier it must be an instance of `NSDictionary`.
/// - Returns: A string that represents the contents of the set, formatted as a property list.
- (NSString *)descriptionWithLocale:(nullable id)locale;
/// Returns a Boolean value that indicates whether at least one object in the receiving set is also present in another given set.
///
/// Object equality is tested using isEqual:.
///
/// - Parameter otherSet: The set with which to compare the receiving set.
/// - Returns: `YES` if at least one object in the receiving set is also present in `otherSet`, otherwise `NO`.
- (BOOL)intersectsSet:(NSSet<ObjectType> *)otherSet;
/// Compares the receiving set to another set.
///
/// Two sets have equal contents if they each have the same number of members and if each member of one set is present in the other. Object equality is tested using isEqual:.
///
/// - Parameter otherSet: The set with which to compare the receiving set.
/// - Returns: `YES` if the contents of `otherSet` are equal to the contents of the receiving set, otherwise `NO`.
- (BOOL)isEqualToSet:(NSSet<ObjectType> *)otherSet;
/// Returns a Boolean value that indicates whether every object in the receiving set is also present in another given set.
///
/// Object equality is tested using isEqual:.
///
/// - Parameter otherSet: The set with which to compare the receiving set.
/// - Returns: `YES` if every object in the receiving set is also present in `otherSet`, otherwise `NO`.
- (BOOL)isSubsetOfSet:(NSSet<ObjectType> *)otherSet;

/// Sends a message specified by a given selector to each object in the set.
///
/// The message specified by `aSelector` is sent once to each member of the set. This method raises an `NSInvalidArgumentException` if `aSelector` is `NULL`.
///
/// - Parameter aSelector: A selector that specifies the message to send to the members of the set. The method must not take any arguments. It should not have the side effect of modifying the set. This value must not be `NULL`.
- (void)makeObjectsPerformSelector:(SEL)aSelector NS_SWIFT_UNAVAILABLE("Use enumerateObjectsUsingBlock: or a for loop instead");
/// Sends a message specified by a given selector to each object in the set.
///
/// The message specified by `aSelector` is sent, with `argument` as the argument, once to each member of the set. This method raises an `NSInvalidArgumentException` if `aSelector` is `NULL`.
///
/// - Parameters:
///   - aSelector: A selector that specifies the message to send to the set's members. The method must take a single argument of type `id`. The method should not, as a side effect, modify the set. The value must not be `NULL`.
///   - argument: The object to pass as an argument to the method specified by `aSelector`.
- (void)makeObjectsPerformSelector:(SEL)aSelector withObject:(nullable id)argument NS_SWIFT_UNAVAILABLE("Use enumerateObjectsUsingBlock: or a for loop instead");

/// Returns a new set formed by adding a given object to the receiving set.
///
/// - Parameter anObject: The object to add to the set.
/// - Returns: A new set formed by adding `anObject` to the receiving set.
- (NSSet<ObjectType> *)setByAddingObject:(ObjectType)anObject API_AVAILABLE(macos(10.5), ios(2.0), watchos(2.0), tvos(9.0));
/// Returns a new set formed by adding the objects in a given set to the receiving set.
///
/// - Parameter other: The set of objects to add to the receiving set.
/// - Returns: A new set formed by adding the objects in `other` to the receiving set.
- (NSSet<ObjectType> *)setByAddingObjectsFromSet:(NSSet<ObjectType> *)other API_AVAILABLE(macos(10.5), ios(2.0), watchos(2.0), tvos(9.0));
/// Returns a new set formed by adding the objects in a given array to the receiving set.
///
/// - Parameter other: The array of objects to add to the set.
/// - Returns: A new set formed by adding the objects in `other` to the receiving set.
- (NSSet<ObjectType> *)setByAddingObjectsFromArray:(NSArray<ObjectType> *)other API_AVAILABLE(macos(10.5), ios(2.0), watchos(2.0), tvos(9.0));

/// Executes a given block using each object in the set.
///
/// - Parameter block: The block to apply to elements in the set.
///
///   The block takes two arguments:
///
///   - `obj`: The element in the set.
///   - `stop`: A reference to a Boolean value. The block can set the value to `YES` to stop further processing of the set. The `stop` argument is an out-only argument. You should only ever set this Boolean to `YES` within the block.
- (void)enumerateObjectsUsingBlock:(void (NS_NOESCAPE ^)(ObjectType obj, BOOL *stop))block API_AVAILABLE(macos(10.6), ios(4.0), watchos(2.0), tvos(9.0));
/// Executes a given block using each object in the set, using the specified enumeration options.
///
/// - Parameters:
///   - opts: A bitmask that specifies the options for the enumeration.
///   - block: The block to apply to elements in the set.
///
///     The block takes two arguments:
///
///     - `obj`: The element in the set.
///     - `stop`: A reference to a Boolean value. The block can set the value to `YES` to stop further processing of the set. The `stop` argument is an out-only argument. You should only ever set this Boolean to `YES` within the block.
- (void)enumerateObjectsWithOptions:(NSEnumerationOptions)opts usingBlock:(void (NS_NOESCAPE ^)(ObjectType obj, BOOL *stop))block API_AVAILABLE(macos(10.6), ios(4.0), watchos(2.0), tvos(9.0));

/// Returns a set of objects that pass a test in a given block.
///
/// - Parameter predicate: The block to apply to elements in the array.
///
///   The block takes two arguments:
///
///   - `obj`: The element in the set.
///   - `stop`: A reference to a Boolean value. The block can set the value to `YES` to stop further processing of the set. The `stop` argument is an out-only argument. You should only ever set this Boolean to `YES` within the block.
///
///   The block returns a Boolean value that indicates whether `obj` passed the test.
///
/// - Returns: An `NSSet` containing objects that pass the test.
- (NSSet<ObjectType> *)objectsPassingTest:(BOOL (NS_NOESCAPE ^)(ObjectType obj, BOOL *stop))predicate API_AVAILABLE(macos(10.6), ios(4.0), watchos(2.0), tvos(9.0));
/// Returns a set of objects that pass a test in a given block, using the specified enumeration options.
///
/// - Parameters:
///   - opts: A bitmask that specifies the options for the enumeration.
///   - predicate: The block to apply to elements in the set.
///
///     The block takes two arguments:
///
///     - `obj`: The element in the set.
///     - `stop`: A reference to a Boolean value. The block can set the value to `YES` to stop further processing of the set. The `stop` argument is an out-only argument. You should only ever set this Boolean to `YES` within the block.
///
///     The block returns a Boolean value that indicates whether `obj` passed the test.
///
/// - Returns: An `NSSet` containing objects that pass the test.
- (NSSet<ObjectType> *)objectsWithOptions:(NSEnumerationOptions)opts passingTest:(BOOL (NS_NOESCAPE ^)(ObjectType obj, BOOL *stop))predicate API_AVAILABLE(macos(10.6), ios(4.0), watchos(2.0), tvos(9.0));

@end

@interface NSSet<ObjectType> (NSSetCreation)

/// Creates and returns an empty set.
///
/// This method is declared primarily for the use of mutable subclasses of `NSSet`.
///
/// - Returns: A new empty set.
+ (instancetype)set;
/// Creates and returns a set that contains a single given object.
///
/// - Parameter object: The object to add to the new set. `object` receives a `retain` message after being added to the set.
/// - Returns: A new set that contains a single member, `object`.
+ (instancetype)setWithObject:(ObjectType)object;
/// Creates and returns a set containing a specified number of objects from a given C array of objects.
///
/// - Parameters:
///   - objects: A C array of objects to add to the new set. If the same object appears more than once in `objects`, it is added only once to the returned set. Each object receives a `retain` message as it is added to the set.
///   - cnt: The number of objects from `objects` to add to the new set.
/// - Returns: A new set containing `cnt` objects from the list of objects specified by `objects`.
+ (instancetype)setWithObjects:(const ObjectType _Nonnull [_Nonnull])objects count:(NSUInteger)cnt;
/// Creates and returns a set containing the objects in a given argument list.
///
/// To add additional objects to the new set, pass a comma-separated list of trailing variadic arguments, ending with `nil`.  If the same object appears more than once in the list of objects, it is added only once to the returned set. Each object receives a `retain` message as it is added to the set.
///
/// As an example, the following code excerpt creates a set containing three different types of elements (assuming `aPath` exits):
///
/// ```objc
/// NSSet *mySet;
/// NSData *someData = [NSData dataWithContentsOfFile:aPath];
/// NSValue *aValue = [NSNumber numberWithInteger:5];
/// NSString *aString = @"a string";
///
/// mySet = [NSSet setWithObjects:someData, aValue, aString, nil];
/// ```
///
/// - Parameter firstObj: The first object to add to the new set.
/// - Returns: A new set containing the objects in the argument list.
+ (instancetype)setWithObjects:(ObjectType)firstObj, ... NS_REQUIRES_NIL_TERMINATION;
/// Creates and returns a set containing the objects from another set.
///
/// - Parameter set: A set containing the objects to add to the new set. Each object receives a `retain` message as it is added to the new set.
/// - Returns: A new set containing the objects from `set`.
+ (instancetype)setWithSet:(NSSet<ObjectType> *)set;
/// Creates and returns a set containing a uniqued collection of the objects contained in a given array.
///
/// - Parameter array: An array containing the objects to add to the new set. If the same object appears more than once in `array`, it is added only once to the returned set. Each object receives a `retain` message as it is added to the set.
/// - Returns: A new set containing a uniqued collection of the objects contained in `array`.
+ (instancetype)setWithArray:(NSArray<ObjectType> *)array;

/// Initializes a newly allocated set with members taken from the specified list of objects.
///
/// To add additional objects to the new set, pass a comma-separated list of trailing variadic arguments, ending with `nil`.  If the same object appears more than once in the list of objects, it is added only once to the returned set. Each object receives a `retain` message as it is added to the set.
///
/// - Parameter firstObj: The first object to add to the new set.
/// - Returns: An initialized set containing the objects specified in the parameter list. The returned set might be different than the original receiver.
- (instancetype)initWithObjects:(ObjectType)firstObj, ... NS_REQUIRES_NIL_TERMINATION;
/// Initializes a newly allocated set and adds to it objects from another given set.
///
/// - Parameter set: A set containing objects to add to the receiving set. Each object is retained as it is added.
/// - Returns: An initialized objects set containing the objects from `set`. The returned set might be different than the original receiver.
- (instancetype)initWithSet:(NSSet<ObjectType> *)set;
/// Initializes a newly allocated set and adds to it members of another given set.
///
/// After an immutable set has been initialized in this way, it cannot be modified.
///
/// The `copyWithZone:` method performs a shallow copy. If you have a collection of arbitrary depth, passing `YES` for the `flag` parameter will perform an immutable copy of the first level below the surface. If you pass `NO` the mutability of the first level is unaffected. In either case, the mutability of all deeper levels is unaffected.
///
/// - Parameters:
///   - set: A set containing objects to add to the new set.
///   - flag: If `YES`, each object in `set` receives a `copyWithZone:` message to create a copy of the object—objects must conform to the `NSCopying` protocol. In a managed memory environment, this is instead of the `retain` message the object would otherwise receive. The object copy is then added to the returned set.
///
///     If `NO`, then in a managed memory environment each object in `set` simply receives a `retain` message when it is added to the returned set.
/// - Returns: An initialized set that contains the members of `set`. The returned set might be different than the original receiver.
- (instancetype)initWithSet:(NSSet<ObjectType> *)set copyItems:(BOOL)flag;
/// Initializes a newly allocated set with the objects that are contained in a given array.
///
/// - Parameter array: An array of objects to add to the new set. If the same object appears more than once in `array`, it is represented only once in the returned set. Each object receives a `retain` message as it is added to the set.
/// - Returns: An initialized set with the contents of `array`. The returned set might be different than the original receiver.
- (instancetype)initWithArray:(NSArray<ObjectType> *)array;

@end

/* ***************	Mutable Set	****************/

/// A dynamic unordered collection of unique objects.
///
/// You can use this type in Swift instead of a `Set` in cases that require reference semantics.
///
/// The `NSMutableSet` class declares the programmatic interface to a mutable, unordered collection of distinct objects.
///
/// The `NSCountedSet` class, which is a concrete subclass of `NSMutableSet`, supports mutable sets that can contain multiple instances of the same element. The `NSSet` class supports creating and managing immutable sets.
///
/// NSMutableSet is "toll-free bridged" with its Core Foundation counterpart, `CFMutableSet`. See [Toll-Free Bridging](https://developer.apple.com/library/archive/documentation/General/Conceptual/CocoaEncyclopedia/Toll-FreeBridgin/Toll-FreeBridgin.html#//apple_ref/doc/uid/TP40010810-CH2) for more information.
///
/// ### Subclassing Notes
///
/// There should be little need of subclassing. If you need to customize behavior, it is often better to consider composition instead of subclassing.
///
/// #### Methods to Override
///
/// In a subclass, you must override both of its primitive methods:
///
/// - `addObject:`
/// - `removeObject:`
///
/// You must also override the primitive methods of the `NSSet` class.
@interface NSMutableSet<ObjectType> : NSSet<ObjectType>

/// Adds a given object to the set, if it is not already a member.
///
/// - Parameter object: The object to add to the set.
- (void)addObject:(ObjectType)object;
/// Removes a given object from the set.
///
/// - Parameter object: The object to remove from the set.
- (void)removeObject:(ObjectType)object;
- (nullable instancetype)initWithCoder:(NSCoder *)coder NS_DESIGNATED_INITIALIZER;
/// Initializes a newly allocated set.
///
/// This method is a designated initializer of `NSMutableSet`.
///
/// - Returns: A set.
- (instancetype)init NS_DESIGNATED_INITIALIZER;
/// Returns an initialized mutable set with a given initial capacity.
///
/// Mutable sets allocate additional memory as needed, so `numItems` simply establishes the object's initial capacity.
///
/// This method is a designated initializer for `NSMutableSet`.
///
/// - Parameter numItems: The initial capacity of the set.
/// - Returns: An initialized mutable set with initial capacity to hold `numItems` members. The returned set might be different than the original receiver.
- (instancetype)initWithCapacity:(NSUInteger)numItems NS_DESIGNATED_INITIALIZER;

@end

@interface NSMutableSet<ObjectType> (NSExtendedMutableSet)

/// Adds to the set each object contained in a given array that is not already a member.
///
/// - Parameter array: An array of objects to add to the set.
- (void)addObjectsFromArray:(NSArray<ObjectType> *)array;
/// Removes from the receiving set each object that isn't a member of another given set.
///
/// - Parameter otherSet: The set with which to perform the intersection.
- (void)intersectSet:(NSSet<ObjectType> *)otherSet;
/// Removes each object in another given set from the receiving set, if present.
///
/// - Parameter otherSet: The set of objects to remove from the receiving set.
- (void)minusSet:(NSSet<ObjectType> *)otherSet;
/// Empties the set of all of its members.
- (void)removeAllObjects;
/// Adds each object in another given set to the receiving set, if not present.
///
/// - Parameter otherSet: The set of objects to add to the receiving set.
- (void)unionSet:(NSSet<ObjectType> *)otherSet;

/// Empties the receiving set, then adds each object contained in another given set.
///
/// - Parameter otherSet: The set whose members replace the receiving set's content.
- (void)setSet:(NSSet<ObjectType> *)otherSet;

@end

@interface NSMutableSet<ObjectType> (NSMutableSetCreation)

/// Creates and returns a mutable set with a given initial capacity.
///
/// Mutable sets allocate additional memory as needed, so `numItems` simply establishes the object's initial capacity.
///
/// - Parameter numItems: The initial capacity of the new set.
/// - Returns: A mutable set with initial capacity to hold `numItems` members.
+ (instancetype)setWithCapacity:(NSUInteger)numItems;

@end

/* ***************	Counted Set	****************/

/// A mutable, unordered collection of distinct objects that may appear more than once in the collection.
///
/// Each distinct object inserted into an `NSCountedSet` object has a counter associated with it. `NSCountedSet` keeps track of the number of times objects are inserted and requires that objects be removed the same number of times. Thus, there is only one instance of an object in an `NSSet` object even if the object has been added to the set multiple times. The `count` method defined by the superclass `NSSet` has special significance; it returns the number of distinct objects, not the total number of times objects are represented in the set. The `NSSet` and `NSMutableSet` classes are provided for static and dynamic sets, respectively, whose elements are distinct.
///
/// While `NSCountedSet` and `CFBag` are not toll-free bridged, they provide similar functionality. For more information about `CFBag`, see the `CFBag`.
///
/// ### Subclassing Notes
///
/// Because `NSCountedSet` is not a class cluster, it does not have primitive methods that provide the basis for its implementation. In general, there should be little need for subclassing.
///
/// #### Methods to Override
///
/// If you subclass `NSCountedSet`, you must override any method of which you want to change the behavior.
///
/// If you change the primitive behavior of an `NSCountedSet`, for instance if you change how objects are stored, you must override all of the affected methods. These include:
///
/// - `addObject:`
/// - `removeObject:`
/// - `objectEnumerator`
/// - `countForObject:`
///
/// If you change the primitive behavior, you must also override the primitive methods of `NSSet` and `NSMutableSet`.
@interface NSCountedSet<ObjectType> : NSMutableSet<ObjectType>

/// Returns a counted set object initialized with enough memory to hold a given number of objects.
///
/// The method is the designated initializer for `NSCountedSet`.
///
/// Note that the capacity is simply a hint to help initial memory allocation--the initial count of the object is `0`, and the set still grows and shrinks as you add and remove objects. The hint is typically useful if the set will become large.
///
/// - Parameter numItems: The initial capacity of the new counted set.
/// - Returns: A counted set object initialized with enough memory to hold `numItems` objects
- (instancetype)initWithCapacity:(NSUInteger)numItems NS_DESIGNATED_INITIALIZER;

/// Returns a counted set object initialized with the contents of a given array.
///
/// - Parameter array: An array of objects to add to the new set.
/// - Returns: An initialized counted set object with the contents of `array`. The returned object might be different than the original receiver.
- (instancetype)initWithArray:(NSArray<ObjectType> *)array;
/// Returns a counted set object initialized with the contents of a given set.
///
/// - Parameter set: An set of objects to add to the new set.
/// - Returns: An initialized counted set object with the contents of `set`. The returned object might be different than the original receiver.
- (instancetype)initWithSet:(NSSet<ObjectType> *)set;

/// Returns the count associated with a given object in the set.
///
/// - Parameter object: The object for which to return the count.
/// - Returns: The count associated with `object` in the set, which can be thought of as the number of occurrences of `object` present in the set.
- (NSUInteger)countForObject:(ObjectType)object;

/// Returns an enumerator object that lets you access each object in the set once, independent of its count.
///
/// If you add a given object to the counted set multiple times, an enumeration of the set will produce that object only once.
///
/// You shouldn't modify the set during enumeration. If you intend to modify the set, use the `allObjects` method to create a "snapshot," then enumerate the snapshot and modify the original set.
///
/// - Returns: An enumerator object that lets you access each object in the set once, independent of its count.
- (NSEnumerator<ObjectType> *)objectEnumerator;
/// Adds a given object to the set.
///
/// If `object` is already a member, `addObject:` increments the count associated with the object. If `object` is not already a member, it is sent a `retain` message.
///
/// - Parameter object: The object to add to the set.
- (void)addObject:(ObjectType)object;
/// Removes a given object from the set.
///
/// If `object` is present in the set, decrements the count associated with it. If the count is decremented to `0`, `object` is removed from the set. `removeObject:` does nothing if `object` is not present in the set.
///
/// - Parameter object: The object to remove from the set.
- (void)removeObject:(ObjectType)object;

@end

NS_HEADER_AUDIT_END(nullability, sendability)
