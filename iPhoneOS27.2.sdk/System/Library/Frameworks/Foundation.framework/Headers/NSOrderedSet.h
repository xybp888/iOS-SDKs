/*	NSOrderedSet.h
	Copyright (c) 2007-2019, Apple Inc. All rights reserved.
*/

#import <Foundation/NSObject.h>
#import <Foundation/NSRange.h>
#import <Foundation/NSEnumerator.h>
#import <Foundation/NSArray.h>
#import <Foundation/NSOrderedCollectionDifference.h>

@class NSArray, NSIndexSet, NSSet<ObjectType>, NSString;

/* ***************       Immutable Ordered Set   ****************/

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

/// A static, ordered collection of unique objects.
///
/// ``NSOrderedSet`` declares the programmatic interface for static sets of distinct objects. You establish a static set's entries when it's created, and thereafter the entries can't be modified. ``NSMutableOrderedSet``, on the other hand, declares a programmatic interface for dynamic sets of distinct objects. A dynamic---or mutable---set allows the addition and deletion of entries at any time, automatically allocating memory as needed.
///
/// You can use ordered sets as an alternative to arrays when the order of elements is important and performance in testing whether an object is contained in the set is a consideration---testing for membership of an array is slower than testing for membership of a set.
API_AVAILABLE(macos(10.7), ios(5.0), watchos(2.0), tvos(9.0))
@interface NSOrderedSet<__covariant ObjectType> : NSObject <NSCopying, NSMutableCopying, NSSecureCoding, NSFastEnumeration>

/// The number of members in the set.
@property (readonly) NSUInteger count;
/// Returns the object at the specified index of the set.
///
/// - Parameter idx: The object located at index.
/// - Returns: If `idx` is beyond the end of the ordered set (that is, if index is greater than or equal to the value returned by count), an ``NSExceptionName/rangeException`` is raised.
- (ObjectType)objectAtIndex:(NSUInteger)idx;
/// Returns the index of the specified object.
///
/// - Parameter object: The object.
/// - Returns: The index whose corresponding ordered set value is equal to `object`. If none of the objects in the ordered set  is equal to `object`, returns `NSNotFound`.
- (NSUInteger)indexOfObject:(ObjectType)object;
/// Initializes a newly allocated ordered set.
///
/// - Returns: An ordered set.
///
/// This method is a designated initializer of `NSOrderedSet`.
- (instancetype)init NS_DESIGNATED_INITIALIZER;
/// Initializes a newly allocated set with a specified number of objects from a given C array of objects.
///
/// - Parameters:
///   - objects: A C array of objects to add to the new set.
///     If the same object appears more than once in objects, it is added only once to the returned ordered set.
///   - cnt: The number of objects from objects to add to the new ordered set.
/// - Returns: An initialized ordered set containing cnt objects from the list of objects specified by objects. The returned set might be different than the original receiver.
///
/// This method is a designated initializer of `NSOrderedSet`.
- (instancetype)initWithObjects:(const ObjectType _Nonnull [_Nullable])objects count:(NSUInteger)cnt NS_DESIGNATED_INITIALIZER;
- (nullable instancetype)initWithCoder:(NSCoder *)coder NS_DESIGNATED_INITIALIZER;

@end

@interface NSOrderedSet<ObjectType> (NSExtendedOrderedSet)

/// Copies the objects contained in the ordered set that fall within the specified range to `objects`.
///
/// - Parameters:
///   - objects: A C array of objects of size at least the length of the range specified by aRange.
///   - range: A range within the bounds of the array.
///     If the location plus the length of the range is greater than the count of the array, this method raises an ``NSExceptionName/rangeException``.
- (void)getObjects:(ObjectType _Nonnull __unsafe_unretained [_Nullable])objects range:(NSRange)range NS_SWIFT_UNAVAILABLE("Use 'array' instead");
/// Returns the objects in the ordered set at the specified indexes.
///
/// - Parameter indexes: The indexes.
/// - Returns: The returned objects are in the ascending order of their indexes in indexes, so that object in returned ordered set with higher index in indexes will follow the object with smaller index in indexes.
///
/// Raises an ``NSExceptionName/rangeException`` if any location in indexes exceeds the bounds of the array, of if `indexes` is `nil`.
- (NSArray<ObjectType> *)objectsAtIndexes:(NSIndexSet *)indexes;
/// The first object in the ordered set.
@property (nullable, nonatomic, readonly) ObjectType firstObject;
/// The last object in the ordered set.
@property (nullable, nonatomic, readonly) ObjectType lastObject;

/// Compares the receiving ordered set to another ordered set.
///
/// - Parameter other: The ordered set with which to compare the receiving ordered set.
/// - Returns: `YES` if the contents of `other` are equal to the contents of the receiving ordered set, otherwise `NO`.
///
/// Two ordered sets have equal contents if they each have the same number of members, if each member of one ordered set is present in the other, and the members are in the same order.
- (BOOL)isEqualToOrderedSet:(NSOrderedSet<ObjectType> *)other;

/// Returns a Boolean value that indicates whether a given object is present in the ordered set.
///
/// - Parameter object: The object for which to test membership of the ordered set.
/// - Returns: `YES` if `object` is present in the set, otherwise `NO`.
- (BOOL)containsObject:(ObjectType)object;
/// Returns a Boolean value that indicates whether at least one object in the receiving ordered set is also present in another given ordered set.
///
/// - Parameter other: The other ordered set.
/// - Returns: `YES` if at least one object in the receiving ordered set is also present in `other`, otherwise `NO`.
- (BOOL)intersectsOrderedSet:(NSOrderedSet<ObjectType> *)other;
/// Returns a Boolean value that indicates whether at least one object in the receiving ordered set is also present in another given set.
///
/// - Parameter set: The set.
/// - Returns: `YES` if at least one object in the receiving ordered set is also present in `other`, otherwise `NO`.
- (BOOL)intersectsSet:(NSSet<ObjectType> *)set;

/// Returns a Boolean value that indicates whether every object in the receiving ordered set is also present in another given ordered set.
///
/// - Parameter other: The ordered set with which to compare the receiving ordered set.
/// - Returns: `YES` if every object in the receiving set is also present in `other`, otherwise `NO`.
- (BOOL)isSubsetOfOrderedSet:(NSOrderedSet<ObjectType> *)other;
/// Returns a Boolean value that indicates whether every object in the receiving ordered set is also present in another given set.
///
/// - Parameter set: The set with which to compare the receiving ordered set.
/// - Returns: `YES` if every object in the receiving ordered set is also present in `set`, otherwise `NO`.
- (BOOL)isSubsetOfSet:(NSSet<ObjectType> *)set;

/// Returns the object at the specified index of the set.
///
/// - Parameter idx: The object located at index.
/// - Returns: If `idx` is beyond the end of the ordered set (that is, if index is greater than or equal to the value returned by count), an ``NSExceptionName/rangeException`` is raised.
///
/// This method is the same as ``NSOrderedSet/object(at:)``.
- (ObjectType)objectAtIndexedSubscript:(NSUInteger)idx API_AVAILABLE(macos(10.8), ios(6.0), watchos(2.0), tvos(9.0));

/// Returns an enumerator object that lets you access each object in the ordered set.
///
/// - Returns: An enumerator object that lets you access each object in the ordered set, in order, from the element at the lowest index upwards.
///
/// When you use this method with mutable subclasses of `NSOrderedSet`, you must not modify the ordered set during enumeration.
///
/// It is more efficient to use the fast enumeration protocol (see ``NSFastEnumeration``). Fast enumeration is available in macOS 10.5 and later and iOS 2.0 and later.
- (NSEnumerator<ObjectType> *)objectEnumerator;
/// Returns an enumerator object that lets you access each object in the ordered set.
///
/// - Returns: An enumerator object that lets you access each object in the ordered set, in order, from the element at the highest index downwards.
///
/// When you use this method with mutable subclasses of `NSOrderedSet`, you must not modify the ordered set during enumeration.
///
/// It is more efficient to use the fast enumeration protocol (see ``NSFastEnumeration``). Fast enumeration is available in macOS 10.5 and later and iOS 2.0 and later.
- (NSEnumerator<ObjectType> *)reverseObjectEnumerator;

/// An ordered set in the reverse order.
@property (readonly, copy) NSOrderedSet<ObjectType> *reversedOrderedSet;

// These two methods return a facade object for the receiving ordered set,
// which acts like an immutable array or set (respectively).  Note that
// while you cannot mutate the ordered set through these facades, mutations
// to the original ordered set will "show through" the facade and it will
// appear to change spontaneously, since a copy of the ordered set is not
// being made.
/// A representation of the ordered set as an array.
///
/// This returns a proxy object for the receiving ordered set, which acts like an immutable array.
///
/// While you cannot mutate the ordered set through this proxy, mutations to the original ordered set will be reflected in the proxy and it will appear to change spontaneously, because a copy of the ordered set is not being made.
@property (readonly, strong) NSArray<ObjectType> *array;
/// A representation of the set containing the contents of the ordered set.
///
/// This returns a proxy object for the receiving ordered set, which acts like an immutable set.
///
/// While you cannot mutate the ordered set through this proxy, mutations to the original ordered set will be reflected in the proxy and it will appear to change spontaneously, because a copy of the ordered set is not being made.
@property (readonly, strong) NSSet<ObjectType> *set;

/// Executes a given block using each object in the ordered set.
///
/// - Parameter block: The block to apply to elements in the ordered set.
///   The block takes three arguments:
///   - `obj`: The element in the set.
///   - `idx`: The index of the item in the set.
///   - `stop`: A reference to a Boolean value. The block can set the value to `YES` to stop further processing of the set. The `stop` argument is an out-only argument. You should only ever set this value to `YES` within the block.
- (void)enumerateObjectsUsingBlock:(void (NS_NOESCAPE ^)(ObjectType obj, NSUInteger idx, BOOL *stop))block;
/// Executes a given block using each object in the set, using the specified enumeration options.
///
/// - Parameters:
///   - opts: A bitmask that specifies the options for the enumeration (whether it should be performed concurrently and whether it should be performed in reverse order).
///   - block: The block to apply to elements in the ordered set.
///     The block takes three arguments:
///     - `obj`: The element in the set.
///     - `idx`: The index of the item in the set.
///     - `stop`: A reference to a Boolean value. The block can set the value to `YES` to stop further processing of the set. The `stop` argument is an out-only argument. You should only ever set this value to `YES` within the block.
- (void)enumerateObjectsWithOptions:(NSEnumerationOptions)opts usingBlock:(void (NS_NOESCAPE ^)(ObjectType obj, NSUInteger idx, BOOL *stop))block;
/// Executes a given block using the objects in the ordered set at the specified indexes.
///
/// - Parameters:
///   - s: The indexes of the objects over which to enumerate.
///   - opts: A bitmask that specifies the options for the enumeration (whether it should be performed concurrently and whether it should be performed in reverse order).
///   - block: The block to apply to elements in the ordered set.
///     The block takes three arguments:
///     - `obj`: The element in the ordered set.
///     - `idx`: The index of the element in the ordered set.
///     - `stop`: A reference to a Boolean value. The block can set the value to `YES` to stop further processing of the array. The `stop` argument is an out-only argument. You should only ever set this Boolean to `YES` within the block.
///
/// By default, the enumeration starts with the first object and continues serially through the ordered set to the last element specified by `s`. You can specify ``NSEnumerationOptions/concurrent`` and/or ``NSEnumerationOptions/reverse`` as enumeration options to modify this behavior.
///
/// > Important:
/// > If the block parameter or the `s` is `nil`, this method raises an exception.
- (void)enumerateObjectsAtIndexes:(NSIndexSet *)s options:(NSEnumerationOptions)opts usingBlock:(void (NS_NOESCAPE ^)(ObjectType obj, NSUInteger idx, BOOL *stop))block;

/// Returns the index of the object in the ordered set that passes a test in a given block.
///
/// - Parameter predicate: The block to apply to elements in the ordered set.
///   The block takes three arguments:
///   - `obj`: The element in the ordered set.
///   - `idx`: The index of the element in the ordered set.
///   - `stop`: A reference to a Boolean value. The block can set the value to `YES` to stop further processing of the set. The `stop` argument is an out-only argument. You should only ever set this value to `YES` within the block.
/// - Returns: The index of the corresponding value in the ordered set that passes the test specified by predicate. If no objects in the ordered set  pass the test, returns `NSNotFound`.
- (NSUInteger)indexOfObjectPassingTest:(BOOL (NS_NOESCAPE ^)(ObjectType obj, NSUInteger idx, BOOL *stop))predicate;
/// Returns the index of an object in the ordered set that passes a test in a given block for a given set of enumeration options.
///
/// - Parameters:
///   - opts: A bitmask that specifies the options for the enumeration (whether it should be performed concurrently and whether it should be performed in reverse order).
///   - predicate: The block to apply to elements in the ordered set.
///     The block takes three arguments:
///     - `obj`: The element in the array.
///     - `idx`: The index of the element in the ordered set.
///     - `stop`: A reference to a Boolean value. The block can set the value to `YES` to stop further processing of the set. The `stop` argument is an out-only argument. You should only ever set this value to `YES` within the block.
///
///     The block returns a Boolean value that indicates whether obj passed the test.
/// - Returns: The index whose corresponding value in the ordered set passes the test specified by `predicate` and `opts`.  If no objects in the ordered set  pass the test, returns `NSNotFound`.
///
/// By default, the enumeration starts with the first object and continues serially through the ordered set to the last object. You can specify ``NSEnumerationOptions/concurrent`` and/or ``NSEnumerationOptions/reverse`` as enumeration options to modify this behavior.
- (NSUInteger)indexOfObjectWithOptions:(NSEnumerationOptions)opts passingTest:(BOOL (NS_NOESCAPE ^)(ObjectType obj, NSUInteger idx, BOOL *stop))predicate;
/// Returns the index, from a given set of indexes, of the object in the ordered set that passes a test in a given block for a given set of enumeration options.
///
/// - Parameters:
///   - s: The indexes of the objects over which to enumerate.
///   - opts: A bitmask that specifies the options for the enumeration (whether it should be performed concurrently and whether it should be performed in reverse order).
///   - predicate: The block to apply to elements in the ordered set.
///     The block takes three arguments:
///     - `obj`: The element in the ordered set.
///     - `idx`: The index of the element in the ordered set.
///     - `stop`: A reference to a Boolean value. The block can set the value to `YES` to stop further processing of the set. The `stop` argument is an out-only argument. You should only ever set this value to `YES` within the block.
///
///     The block returns a Boolean value that indicates whether `obj` passed the test.
/// - Returns: The index of the corresponding value in the ordered set passes the test specified by predicate. If no objects in the ordered set pass the test, returns `NSNotFound`.
///
/// By default, the enumeration starts with the first object and continues serially through the ordered set to the last element specified by `s`. You can specify ``NSEnumerationOptions/concurrent`` and/or ``NSEnumerationOptions/reverse`` as enumeration options to modify this behavior.
///
/// > Important:
/// > If the block parameter or `s` is `nil`, this method raises an exception.
- (NSUInteger)indexOfObjectAtIndexes:(NSIndexSet *)s options:(NSEnumerationOptions)opts passingTest:(BOOL (NS_NOESCAPE ^)(ObjectType obj, NSUInteger idx, BOOL *stop))predicate;

/// Returns the index of the object in the ordered set that passes a test in a given block.
///
/// - Parameter predicate: The block to apply to elements in the ordered set.
///   The block takes three arguments:
///   - `obj`: The element in the ordered set.
///   - `idx`: The index of the element in the ordered set.
///   - `stop`: A reference to a Boolean value. The block can set the value to `YES` to stop further processing of the set. The `stop` argument is an out-only argument. You should only ever set this value to `YES` within the block.
/// - Returns: The index of the corresponding value in the ordered set that passes the test specified by predicate. If no objects in the ordered set pass the test, returns `NSNotFound`.
///
/// If the block parameter is `nil`, this method raises an exception.
- (NSIndexSet *)indexesOfObjectsPassingTest:(BOOL (NS_NOESCAPE ^)(ObjectType obj, NSUInteger idx, BOOL *stop))predicate;
/// Returns the index of an object in the ordered set that passes a test in a given block for a given set of enumeration options.
///
/// - Parameters:
///   - opts: A bitmask that specifies the options for the enumeration (whether it should be performed concurrently and whether it should be performed in reverse order).
///   - predicate: The block to apply to elements in the ordered set.
///     The block takes three arguments:
///     - `obj`: The element in the ordered set.
///     - `idx`: The index of the element in the ordered set.
///     - `stop`: A reference to a Boolean value. The block can set the value to `YES` to stop further processing of the set. The `stop` argument is an out-only argument. You should only ever set this value to `YES` within the block.
/// - Returns: The index whose corresponding value in the ordered set passes the test specified by `predicate` and `opts`. If the `opts` bitmask specifies reverse order, then the last item that matches is returned. Otherwise, the index of the first matching object is returned. If no objects in the ordered set pass the test, returns `NSNotFound`.
///
/// By default, the enumeration starts with the first object and continues serially through the ordered set to the last object. You can specify ``NSEnumerationOptions/concurrent`` and/or ``NSEnumerationOptions/reverse`` as enumeration options to modify this behavior.
///
/// > Important:
/// >  If the block parameter or `s` is `nil`, this method raises an exception.
- (NSIndexSet *)indexesOfObjectsWithOptions:(NSEnumerationOptions)opts passingTest:(BOOL (NS_NOESCAPE ^)(ObjectType obj, NSUInteger idx, BOOL *stop))predicate;
/// Returns the index, from a given set of indexes, of the object in the ordered set that passes a test in a given block for a given set of enumeration options.
///
/// - Parameters:
///   - s: The indexes of the objects over which to enumerate.
///   - opts: A bitmask that specifies the options for the enumeration (whether it should be performed concurrently and whether it should be performed in reverse order).
///   - predicate: The block to apply to elements in the ordered set.
///     The block takes three arguments:
///     - `obj`: The element in the ordered set.
///     - `idx`: The index of the element in the ordered set.
///     - `stop`: A reference to a Boolean value. The block can set the value to `YES` to stop further processing of the set. The `stop` argument is an out-only argument. You should only ever set this value to `YES` within the block.
///
///     The block returns a Boolean value that indicates whether `obj` passed the test.
/// - Returns: The index of the corresponding value in the ordered set that passes the test specified by predicate. If no objects in the ordered set pass the test, returns NSNotFound.
///
/// By default, the enumeration starts with the first object and continues serially through the ordered set to the last object. You can specify ``NSEnumerationOptions/concurrent`` and/or ``NSEnumerationOptions/reverse`` as enumeration options to modify this behavior.
///
/// > Important:
/// >  If the block parameter or `s` is `nil` this method will raise an exception.
- (NSIndexSet *)indexesOfObjectsAtIndexes:(NSIndexSet *)s options:(NSEnumerationOptions)opts passingTest:(BOOL (NS_NOESCAPE ^)(ObjectType obj, NSUInteger idx, BOOL *stop))predicate;

/// Returns the index, within a specified range, of an object compared with elements in the ordered set using a given NSComparator block.
///
/// - Parameters:
///   - object: An object for which to search in the ordered set.
///     If this value is `nil`, throws an ``NSExceptionName/invalidArgumentException``.
///   - range: The range within the array to search for `object`.
///     If r exceeds the bounds of the ordered set (if the location plus length of the range is greater than the count of the ordered set), throws an ``NSExceptionName/rangeException``.
///   - opts: Options for the search. For possible values, see ``NSBinarySearchingOptions``.
///   - cmp: A comparator block used to compare the object obj with elements in the ordered set.
///     If this value is `NULL`, throws an ``NSExceptionName/invalidArgumentException``.
/// - Returns: If the ``NSBinarySearchingOptions/insertionIndex`` option is not specified:
///   - If the `object` is found and neither ``NSBinarySearchingOptions/firstEqual`` nor ``NSBinarySearchingOptions/lastEqual`` is specified, returns the matching object's index.
///   - If the ``NSBinarySearchingOptions/firstEqual`` or ``NSBinarySearchingOptions/lastEqual`` option is also specified, returns the index of equal objects.
///   - If the object is not found, returns `NSNotFound`.
///
///   If the ``NSBinarySearchingOptions/insertionIndex`` option is specified, returns the index at which you should insert `obj` in order to maintain a sorted array:
///
///   - If the `object` is found and neither ``NSBinarySearchingOptions/firstEqual`` nor ``NSBinarySearchingOptions/lastEqual`` is specified, returns the matching object's index.
///   - If the ``NSBinarySearchingOptions/firstEqual`` or  ``NSBinarySearchingOptions/lastEqual`` option is also specified, returns the index of the equal objects.
///   - If the object is not found, returns the index of the least greater object, or the index at the end of the array if the object is larger than all other elements.
///
/// The elements in the ordered set  must have already been sorted using the comparator `cmp`. If the ordered set is not sorted, the result is undefined.
- (NSUInteger)indexOfObject:(ObjectType)object inSortedRange:(NSRange)range options:(NSBinarySearchingOptions)opts usingComparator:(NSComparator NS_NOESCAPE)cmp;

/// Returns an array that lists the receiving ordered set's elements in ascending order, as determined by the comparison method specified by a given `NSComparator` block.
///
/// - Parameter cmptr: A comparator block.
/// - Returns: An array that lists the receiving ordered set's elements in ascending order, as determined by the comparison method specified `cmptr`.
- (NSArray<ObjectType> *)sortedArrayUsingComparator:(NSComparator NS_NOESCAPE)cmptr;
/// Returns an array that lists the receiving ordered set's elements in ascending order, as determined by the comparison method specified by a given `NSComparator` block.
///
/// - Parameters:
///   - opts: A bitmask that specifies the options for the sort (whether it should be performed concurrently and whether it should be performed stably).
///   - cmptr: A comparator block.
/// - Returns: An array that lists the receiving ordered set's elements in ascending order, as determined by the comparison method specified `cmptr`.
- (NSArray<ObjectType> *)sortedArrayWithOptions:(NSSortOptions)opts usingComparator:(NSComparator NS_NOESCAPE)cmptr;

/// A string that represents the contents of the ordered set, formatted as a property list.
@property (readonly, copy) NSString *description;
/// Returns a string that represents the contents of the ordered set, formatted as a property list.
///
/// - Parameter locale: An ``NSLocale`` object or an `NSDictionary` object that specifies options used for formatting each of the ordered set's elements (where recognized). Specify `nil` if you don't want the elements formatted.
/// - Returns: A string that represents the contents of the ordered set, formatted as a property list.
///
/// For a description of how locale is applied to each element in the receiving ordered set, see ``NSOrderedSet/description(withLocale:indent:)``.
- (NSString *)descriptionWithLocale:(nullable id)locale;
/// Returns a string that represents the contents of the ordered set, formatted as a property list.
///
/// - Parameters:
///   - locale: An ``NSLocale`` object or an `NSDictionary` object that specifies options used for formatting each of the array's elements (where recognized). Specify `nil` if you don't want the elements formatted.
///   - level: Specifies a level of indentation, to make the output more readable: the indentation is (4 spaces) * `level`.
/// - Returns: A string that represents the contents of the ordered set, formatted as a property list.
///
/// The returned `NSString` object contains the string representations of each of the ordered set's elements, in order, from first to last. To obtain the string representation of a given element, `descriptionWithLocale:indent:` proceeds as follows:
///
/// - If the element is an `NSString` object, it is used as is.
/// - If the element responds to `descriptionWithLocale:indent:`, that method is invoked to obtain the element's string representation.
/// - If the element responds to `descriptionWithLocale:`, that method is invoked to obtain the element's string representation.
/// - If none of the above conditions is met, the element's string representation is obtained by invoking its `description` method.
- (NSString *)descriptionWithLocale:(nullable id)locale indent:(NSUInteger)level;

@end

@interface NSOrderedSet<ObjectType> (NSOrderedSetCreation)

/// Creates and returns an empty ordered set.
///
/// - Returns: A new empty ordered set.
///
/// This method is declared primarily for the use of mutable subclasses of `NSOrderedSet`.
+ (instancetype)orderedSet;
/// Creates and returns a ordered set that contains a single given object.
///
/// - Parameter object: The object to add to the new set.
/// - Returns: A new ordered set containing `object`.
+ (instancetype)orderedSetWithObject:(ObjectType)object;
/// Creates and returns a set containing a specified number of objects from a given C array of objects.
///
/// - Parameters:
///   - objects: A C array of objects to add to the new ordered set.
///     If the same object appears more than once in objects, it is added only once to the returned ordered set. Each object receives a retain message as it is added to the set.
///   - cnt: The number of objects from objects to add to the new set.
/// - Returns: A new ordered set containing cnt objects from the list of objects specified by `objects`.
+ (instancetype)orderedSetWithObjects:(const ObjectType _Nonnull [_Nonnull])objects count:(NSUInteger)cnt;
/// Creates and returns a ordered set containing the objects in a given argument list.
///
/// - Parameter firstObj: The first object to add to the new set.
///   If the same object appears more than once in the list of objects, it is added only once to the returned set. The objects are added to the ordered set in the order that they are listed.
/// - Returns: A new ordered set containing the objects in the argument list.
///
/// To add additional objects to the new set, pass a comma-separated list of trailing variadic arguments, ending with `nil`.
+ (instancetype)orderedSetWithObjects:(ObjectType)firstObj, ... NS_REQUIRES_NIL_TERMINATION;
/// Creates and returns an ordered set containing the objects from another ordered set.
///
/// - Parameter set: A set containing the objects to add to the new ordered set.
///   The objects are not copied, simply referenced.
/// - Returns: A new ordered set containing the objects from set.
+ (instancetype)orderedSetWithOrderedSet:(NSOrderedSet<ObjectType> *)set;
/// Creates and returns a new ordered set for a specified range of objects in an ordered set.
///
/// - Parameters:
///   - set: An ordered set.
///   - range: The range of objects in `set` to add to the ordered set.
///   - flag: If `YES` the objects are copied to the ordered set; otherwise `NO`.
/// - Returns: A new ordered set containing a uniqued collection of the objects contained in the specified range of the ordered set.
+ (instancetype)orderedSetWithOrderedSet:(NSOrderedSet<ObjectType> *)set range:(NSRange)range copyItems:(BOOL)flag;
/// Creates and returns a set containing a uniqued collection of the objects contained in a given array.
///
/// - Parameter array: An array containing the objects to add to the new ordered set. If the same object appears more than once in `array`, it is added only once to the returned set.
/// - Returns: A new ordered set containing a uniqued collection of the objects contained in array.
+ (instancetype)orderedSetWithArray:(NSArray<ObjectType> *)array;
/// Creates and returns a new ordered set for a specified range of objects in an array.
///
/// - Parameters:
///   - array: The array.
///   - range: The range of the objects to add to the ordered set.
///   - flag: If `YES` the objects are copied to the ordered set; otherwise `NO`.
/// - Returns: A new ordered set containing a uniqued collection of the objects contained in the specified range of the array.
+ (instancetype)orderedSetWithArray:(NSArray<ObjectType> *)array range:(NSRange)range copyItems:(BOOL)flag;
/// Creates and returns an ordered set with the contents of a set.
///
/// - Parameter set: A set.
/// - Returns: A new ordered set containing a uniqued collection of the objects contained in the set.
+ (instancetype)orderedSetWithSet:(NSSet<ObjectType> *)set;
/// Creates and returns an ordered set with the contents of a set, optionally copying the items.
///
/// - Parameters:
///   - set: A set.
///   - flag: If `YES` the objects are copied to the ordered set; otherwise `NO`.
/// - Returns: A new ordered set containing a uniqued collection of the objects contained in the specified range of the set.
+ (instancetype)orderedSetWithSet:(NSSet<ObjectType> *)set copyItems:(BOOL)flag;

/// Initializes a new ordered set with the object.
///
/// - Parameter object: The object to add to the new ordered set.
/// - Returns: A new ordered set that contains a single member, `object`.
- (instancetype)initWithObject:(ObjectType)object;
/// Initializes a newly allocated set with members taken from the specified list of objects.
///
/// - Parameter firstObj: The first object to add to the new set.
/// - Returns: An initialized ordered set containing the objects specified in the parameter list. The returned set might be different than the original receiver.
///
/// To add additional objects to the new ordered set, pass comma-separated list of trailing variadic arguments, ending with `nil`.
///
/// If the same object appears more than once in the list, it is represented only once in the returned ordered set.
- (instancetype)initWithObjects:(ObjectType)firstObj, ... NS_REQUIRES_NIL_TERMINATION;
/// Initializes a new ordered set with the contents of a set.
///
/// - Parameter set: A set.
/// - Returns: An initialized ordered set containing references to the objects in the set.
- (instancetype)initWithOrderedSet:(NSOrderedSet<ObjectType> *)set;
/// Initializes a new ordered set with the contents of a set, optionally copying the items.
///
/// - Parameters:
///   - set: A set.
///   - flag: If `YES` the objects are copied to the ordered set; otherwise `NO`.
/// - Returns: An initialized ordered set containing the objects in the set.
- (instancetype)initWithOrderedSet:(NSOrderedSet<ObjectType> *)set copyItems:(BOOL)flag;
/// Initializes a new ordered set with the contents of an ordered set, optionally copying the items.
///
/// - Parameters:
///   - set: An ordered set.
///   - range: The range of objects in `orderedSet` to add to the ordered set.
///   - flag: If `YES` the objects are copied to the ordered set; otherwise `NO`.
/// - Returns: An initialized ordered set containing the objects in the ordered set.
- (instancetype)initWithOrderedSet:(NSOrderedSet<ObjectType> *)set range:(NSRange)range copyItems:(BOOL)flag;
/// Initializes a newly allocated set with the objects that are contained in a given array.
///
/// - Parameter array: An array of objects to add to the new set.
///   If the same object appears more than once in array, it is represented only once in the returned ordered set.
/// - Returns: An initialized ordered set with the contents of array. The returned ordered set might be different than the original receiver.
- (instancetype)initWithArray:(NSArray<ObjectType> *)array;
/// Initializes a newly allocated set with the objects that are contained in a given array, optionally copying the items.
///
/// - Parameters:
///   - set: An array of objects to add to the new set.
///     If the same object appears more than once in array, it is represented only once in the returned ordered set.
///   - flag: If `YES` the objects are copied to the ordered set; otherwise `NO`.
/// - Returns: An initialized ordered set containing a uniqued collection of the objects contained in the array.
- (instancetype)initWithArray:(NSArray<ObjectType> *)set copyItems:(BOOL)flag;
/// Initializes a newly allocated set with the objects that are contained in the specified range of an array, optionally copying the items.
///
/// - Parameters:
///   - set: An array of objects to add to the new set.
///     If the same object appears more than once in array, it is represented only once in the returned ordered set.
///   - range: The range of objects in `array` to add to the ordered set.
///   - flag: If `YES` the objects are copied to the ordered set; otherwise `NO`.
/// - Returns: An initialized ordered set containing a uniqued collection of the objects contained in specified range of the array.
- (instancetype)initWithArray:(NSArray<ObjectType> *)set range:(NSRange)range copyItems:(BOOL)flag;
/// Initializes a new ordered set with the contents of a set.
///
/// - Parameter set: The set.
/// - Returns: An initialized ordered set containing the objects in the set.
- (instancetype)initWithSet:(NSSet<ObjectType> *)set;
/// Initializes a new ordered set with the contents of a set, optionally copying the objects in the set.
///
/// - Parameters:
///   - set: The set.
///   - flag: If `YES` the objects are copied to the ordered set; otherwise `NO`.
/// - Returns: An initialized ordered set containing the objects in the set.
- (instancetype)initWithSet:(NSSet<ObjectType> *)set copyItems:(BOOL)flag;

@end

API_AVAILABLE(macosx(10.15), ios(13.0), watchos(6.0), tvos(13.0))
NS_SWIFT_UNAVAILABLE("NSOrderedSet diffing methods are not available in Swift, use Collection.difference(from:) instead")
@interface NSOrderedSet<ObjectType> (NSOrderedSetDiffing)

/// Compares two ordered sets, using the provided block and with options, to create a difference object that represents the changes between them.
///
/// The options allow you to choose to omit insertion or removal references to the change objects within the difference object's changes. Don't use the option ``NSOrderedCollectionDifferenceCalculationOptions/inferMoves`` when providing a block for the equivalence test. The changes returned in the difference object don't include valid values for ``NSOrderedCollectionChange/associatedIndex``.
- (NSOrderedCollectionDifference<ObjectType> *)differenceFromOrderedSet:(NSOrderedSet<ObjectType> *)other withOptions:(NSOrderedCollectionDifferenceCalculationOptions)options usingEquivalenceTest:(BOOL (NS_NOESCAPE ^)(ObjectType obj1, ObjectType obj2))block;

/// Compares two ordered sets, with options, to create a difference object that represents the changes between them.
///
/// The difference method creates the difference object by comparing objects within the ordered sets with the `isEqual:` method.
///
/// The options allow you to choose to omit insertion or removal references to the change objects within the difference object. You can also choose to infer moves when computing the difference, which provides an ``NSOrderedCollectionChange/associatedIndex`` within the change objects that indicates the index in the ordered set where the object moved from.
///
/// The following example computes the difference between two ordered sets, inferring moves between them:
///
/// ```objc
/// NSOrderedSet *original = [NSOrderedSet
///                            orderedSetWithObjects:@"Red", @"Green", @"Blue", nil];
/// NSOrderedSet *modified = [NSOrderedSet
///                            orderedSetWithObjects:@"Red", @"Blue", @"Green", nil];
///
/// NSOrderedCollectionDifference *diff = [original
///                                        differenceFromOrderedSet:modified
///                                        withOptions:NSOrderedCollectionDifferenceCalculationInferMoves];
///
/// // diff.hasChanges == TRUE
/// // diff.insertions.count == 1
/// // diff.removals.count == 1
///
/// // Inferring the moves adds an associatedIndex into the change.
/// NSOrderedCollectionChange* insertion = diff.insertions[0];
/// // insertion.index == 2
/// // insertion.associatedIndex == 1
///
/// NSOrderedCollectionChange* deletion = diff.removals[0];
/// // deletion.index == 1
/// // deletion.associatedIndex == 2
/// ```
- (NSOrderedCollectionDifference<ObjectType> *)differenceFromOrderedSet:(NSOrderedSet<ObjectType> *)other withOptions:(NSOrderedCollectionDifferenceCalculationOptions)options;

/// Compares two ordered sets to create a difference object that represents the changes between them.
///
/// The difference method creates the difference object by comparing objects within the ordered sets with the `isEqual:` method.
///
/// The following example computes the difference between two ordered sets:
///
/// ```objc
/// NSOrderedSet *original = [NSOrderedSet orderedSetWithObjects:@"1", @"2", nil];
/// NSOrderedSet *modified = [NSOrderedSet orderedSetWithObjects:@"1", @"2", @"3", nil];
///
/// NSOrderedCollectionDifference *diff = [modified differenceFromOrderedSet:original];
/// NSLog(@"diff is: %@", diff.debugDescription);
/// // diff.hasChanges == true
/// // diff.insertions.count == 1
/// // diff.removals.count == 0
/// ```
- (NSOrderedCollectionDifference<ObjectType> *)differenceFromOrderedSet:(NSOrderedSet<ObjectType> *)other;

/// Creates a new ordered set by applying a difference object to an existing ordered set.
///
/// The following example computes the difference between two ordered sets, then applies the difference to create an ordered set that duplicates the original:
///
/// ```objc
/// NSOrderedSet *original = [NSOrderedSet orderedSetWithObjects:@"1", @"2", nil];
/// NSOrderedSet *modified = [NSOrderedSet orderedSetWithObjects:@"1", @"2", @"3", nil];
///
/// NSOrderedCollectionDifference *diff = [modified differenceFromOrderedSet:original];
/// // diff.hasChanges == true
/// // diff.insertions.count == 1
/// // diff.removals.count == 0
///
/// NSOrderedSet *updated = [original orderedSetByApplyingDifference:diff];
/// // updated == [@"1", @"2", @"3"]
/// ```
- (nullable NSOrderedSet<ObjectType> *)orderedSetByApplyingDifference:(NSOrderedCollectionDifference<ObjectType> *)difference;

@end

/* ***************       Mutable Ordered Set     ****************/

/// A dynamic, ordered collection of unique objects.
///
/// ``NSMutableOrderedSet`` objects are not like C arrays. That is, even though you may specify a size when you create a mutable ordered set, the specified size is regarded as a "hint"; the actual size of the set is still 0. This means that you cannot insert an object at an index greater than the current count of an set. For example, if a set contains two objects, its size is 2, so you can add objects at indices 0, 1, or 2. Index 3 is illegal and out of bounds; if you try to add an object at index 3 (when the size of the array is 2), `NSMutableOrderedSet` raises an exception.
API_AVAILABLE(macos(10.7), ios(5.0), watchos(2.0), tvos(9.0))
@interface NSMutableOrderedSet<ObjectType> : NSOrderedSet<ObjectType>

/// Inserts the given object at the specified index of the mutable ordered set, if it is not already a member.
///
/// - Parameters:
///   - object: The object to insert into the set's content.
///   - idx: The index in the mutable ordered set at which to insert `object`. This value must not be greater than the count of elements in the array.
///
///     > Important:
///     > Raises an ``NSExceptionName/rangeException`` if `idx` is greater than the number of elements in the mutable ordered set.
///
/// If the object is already a member, this method has no effect. If the specified index is already occupied, the objects at that index and beyond are shifted by adding `1` to their indexes to make room for the inserted object.
- (void)insertObject:(ObjectType)object atIndex:(NSUInteger)idx;
/// Removes a the object at the specified index from the mutable ordered set.
///
/// - Parameter idx: The index of the object to remove from the mutable ordered set. The value must not exceed the bounds of the set.
///
///   > Important:
///   > Raises an ``NSExceptionName/rangeException`` if index is beyond the end of the mutable ordered set.
///
/// To fill the gap, all elements beyond index are moved by subtracting 1 from their index.
- (void)removeObjectAtIndex:(NSUInteger)idx;
/// Replaces the object at the specified index with the new object.
///
/// - Parameters:
///   - idx: The index of the object to be replaced. This value must not exceed the bounds of the mutable ordered set.
///
///     > Important:
///     > Raises an ``NSExceptionName/rangeException`` if index is beyond the end of the mutable ordered set.
///   - object: The object with which to replace the object at the index in the ordered set specified by `idx`.
- (void)replaceObjectAtIndex:(NSUInteger)idx withObject:(ObjectType)object;
- (nullable instancetype)initWithCoder:(NSCoder *)coder NS_DESIGNATED_INITIALIZER;
/// Initializes a newly allocated mutable ordered set.
///
/// - Returns: A mutable ordered set.
///
/// This method is a designated initializer of `NSMutableOrderedSet`.
- (instancetype)init NS_DESIGNATED_INITIALIZER;
/// Returns an initialized mutable ordered set with a given initial capacity.
///
/// - Parameter numItems: The initial capacity of the new ordered set.
/// - Returns: An initialized mutable ordered set with initial capacity to hold `numItems` members.
///
/// Mutable ordered sets allocate additional memory as needed, so `numItems` simply establishes the set's initial capacity.
///
/// This method is a designated initializer of `NSMutableOrderedSet`.
- (instancetype)initWithCapacity:(NSUInteger)numItems NS_DESIGNATED_INITIALIZER;

@end

@interface NSMutableOrderedSet<ObjectType> (NSExtendedMutableOrderedSet)

/// Appends a given object to the end of the mutable ordered set, if it is not already a member.
///
/// - Parameter object: The object to add to the set.
- (void)addObject:(ObjectType)object;
/// Appends the given number of objects from a given C array to the end of the mutable ordered set.
///
/// - Parameters:
///   - objects: A C array of objects.
///   - count: The number of values from the objects C array to append to the mutable ordered set. This number will be the count of the new array---it must not be negative or greater than the number of elements in objects.
- (void)addObjects:(const ObjectType _Nonnull [_Nullable])objects count:(NSUInteger)count;
/// Appends to the end of the mutable ordered set each object contained in a given array that is not already a member.
///
/// - Parameter array: An array of objects to add to the set.
- (void)addObjectsFromArray:(NSArray<ObjectType> *)array;

/// Exchanges the object at the specified index with the object at the other index.
///
/// - Parameters:
///   - idx1: The index of the first object.
///
///     > Important:
///     > Raises an ``NSExceptionName/rangeException`` if index is beyond the end of the mutable ordered set.
///   - idx2: The index of the second object.
///
///     > Important:
///     > Raises an ``NSExceptionName/rangeException`` if index is beyond the end of the mutable ordered set.
- (void)exchangeObjectAtIndex:(NSUInteger)idx1 withObjectAtIndex:(NSUInteger)idx2;
/// Moves the objects at the specified indexes to the new location.
///
/// - Parameters:
///   - indexes: The indexes of the objects to move.
///   - idx: The index in the mutable ordered set at which to insert the objects. The objects being moved are first removed from the set, then this index is used to find the location at which to insert the moved objects.
///
/// For example, the following code results in the contents of `mySet` being equal to `["a", "c", "b", "d", "e"]:`
///
/// ```objc
/// NSMutableIndexSet *movedObjectIndexes = [NSMutableIndexSet indexSet];
/// [movedObjectIndexes addIndex: 1];
/// [movedObjectIndexes addIndex: 3];
///
/// NSMutableOrderedSet *mySet = [NSMutableOrderedSet orderedSetWithCapacity:5];
/// [mySet addObject:@"a"];
/// [mySet addObject:@"b"];
/// [mySet addObject:@"c"];
/// [mySet addObject:@"d"];
/// [mySet addObject:@"e"];
///
/// [mySet moveObjectsAtIndexes:movedObjectIndexes toIndex:2];
/// ```
- (void)moveObjectsAtIndexes:(NSIndexSet *)indexes toIndex:(NSUInteger)idx;

/// Inserts the objects in the array at the specified indexes.
///
/// - Parameters:
///   - objects: An array of objects to insert into the mutable ordered set.
///   - indexes: The indexes at which the objects in objects should be inserted. The count of locations in indexes must equal the count of objects.
///
/// Each object in objects is inserted into the receiving mutable ordered set in turn at the corresponding location specified in indexes after earlier insertions have been made.
- (void)insertObjects:(NSArray<ObjectType> *)objects atIndexes:(NSIndexSet *)indexes;

/// Appends or replaces the object at the specified index.
///
/// - Parameters:
///   - obj: The object to insert or append.
///   - idx: The index. If the index is equal to the length of the collection, then it inserts the object at that index, otherwise it replaces the object at that index with the given object.
- (void)setObject:(ObjectType)obj atIndex:(NSUInteger)idx;
/// Replaces the given object at the specified index of the mutable ordered set.
///
/// - Parameters:
///   - obj: The object to replace the set's content.
///   - idx: The index in the mutable ordered set at which to insert `obj`. This value must not be greater than the count of elements in the array.
///
///     > Important:
///     > Raises an ``NSExceptionName/rangeException`` if `idx` is greater than the number of elements in the mutable ordered set.
///
/// If the index is already occupied, the objects at index and beyond are shifted by adding `1` to their indices to make room.
///
/// This method is identical to ``NSMutableOrderedSet/insert(_:at:)-7qg51``.
- (void)setObject:(ObjectType)obj atIndexedSubscript:(NSUInteger)idx API_AVAILABLE(macos(10.8), ios(6.0), watchos(2.0), tvos(9.0));

/// Replaces the objects in the receiving mutable ordered set at the range with the specified number of objects from a given C array.
///
/// - Parameters:
///   - range: The range of the objects to replace.
///   - objects: A C array of objects.
///   - count: The number of values from the objects C array to insert in place of the objects in `range`. This number will be the count of the new array---it must not be negative or greater than the number of elements in objects.
///
/// Elements are added to the new array in the same order they appear in objects, up to but not including index count.
- (void)replaceObjectsInRange:(NSRange)range withObjects:(const ObjectType _Nonnull [_Nullable])objects count:(NSUInteger)count;
/// Replaces the objects at the specified indexes with the new objects.
///
/// - Parameters:
///   - indexes: The indexes of the objects to be replaced.
///   - objects: The objects with which to replace the objects in the receiving mutable ordered set at the indexes specified by indexes.
///
///     The count of locations in `indexes` must equal the count of objects.
///
/// The indexes in `indexes` are used in the same order as the objects in `objects`.
- (void)replaceObjectsAtIndexes:(NSIndexSet *)indexes withObjects:(NSArray<ObjectType> *)objects;

/// Removes from the mutable ordered set each of the objects within a given range.
///
/// - Parameter range: The range of the objects to remove from the mutable ordered set.
///
/// The objects are removed using ``NSMutableOrderedSet/removeObject(at:)``.
- (void)removeObjectsInRange:(NSRange)range;
/// Removes the objects at the specified indexes from the mutable ordered set.
///
/// - Parameter indexes: The indexes of the objects to remove from the mutable ordered set. The locations specified by indexes must lie within the bounds of the mutable ordered set.
///
/// This method is similar to ``NSMutableOrderedSet/removeObject(at:)``, but allows you to efficiently remove multiple objects with a single operation.
- (void)removeObjectsAtIndexes:(NSIndexSet *)indexes;
/// Removes all the objects from the mutable ordered set.
- (void)removeAllObjects;

/// Removes a given object from the mutable ordered set.
///
/// - Parameter object: The object to remove from the mutable ordered set.
- (void)removeObject:(ObjectType)object;
/// Removes the objects in the array from the mutable ordered set.
///
/// - Parameter array: An array containing the objects to be removed from the receiving mutable ordered set.
///
/// This method is similar to ``NSMutableOrderedSet/remove(_:)``, but allows you to efficiently remove large sets of objects with a single operation. If the receiving mutable ordered set does not contain objects in array, the method has no effect (although it does incur the overhead of searching the contents).
///
/// This method assumes that all elements in array respond to <doc://com.apple.documentation/documentation/objectivec/nsobjectprotocol/hash> and <doc://com.apple.documentation/documentation/objectivec/nsobjectprotocol/isequal(_:)>.
- (void)removeObjectsInArray:(NSArray<ObjectType> *)array;

/// Removes from the receiving ordered set each object that isn't a member of another ordered set.
///
/// - Parameter other: The ordered set with which to perform the intersection.
- (void)intersectOrderedSet:(NSOrderedSet<ObjectType> *)other;
/// Removes each object in another given ordered set from the receiving mutable ordered set, if present.
///
/// - Parameter other: The ordered set of objects to remove from the receiving set.
- (void)minusOrderedSet:(NSOrderedSet<ObjectType> *)other;
/// Adds each object in another given ordered set to the receiving mutable ordered set, if not present.
///
/// - Parameter other: The set of objects to add to the receiving mutable ordered set.
- (void)unionOrderedSet:(NSOrderedSet<ObjectType> *)other;

/// Removes from the receiving ordered set each object that isn't a member of another set.
///
/// - Parameter other: The set with which to perform the intersection.
- (void)intersectSet:(NSSet<ObjectType> *)other;
/// Removes each object in another given set from the receiving mutable ordered set, if present.
///
/// - Parameter other: The set of objects to remove from the receiving set.
- (void)minusSet:(NSSet<ObjectType> *)other;
/// Adds each object in another given set to the receiving mutable ordered set, if not present.
///
/// - Parameter other: The set of objects to add to the receiving mutable ordered set.
- (void)unionSet:(NSSet<ObjectType> *)other;

/// Sorts the mutable ordered set using the comparison method specified by the comparator block.
///
/// - Parameter cmptr: A comparator block.
- (void)sortUsingComparator:(NSComparator NS_NOESCAPE)cmptr;
/// Sorts the mutable ordered set using the specified options and the comparison method specified by a given comparator block.
///
/// - Parameters:
///   - opts: A bitmask that specifies the options for the sort (whether it should be performed concurrently and whether it should be performed stably).
///   - cmptr: A comparator block.
- (void)sortWithOptions:(NSSortOptions)opts usingComparator:(NSComparator NS_NOESCAPE)cmptr;
/// Sorts the specified range of the mutable ordered set using the specified options and the comparison method specified by a given comparator block.
///
/// - Parameters:
///   - range: The range to sort.
///   - opts: A bitmask that specifies the options for the sort (whether it should be performed concurrently and whether it should be performed stably).
///   - cmptr: A comparator block.
- (void)sortRange:(NSRange)range options:(NSSortOptions)opts usingComparator:(NSComparator NS_NOESCAPE)cmptr;

@end

@interface NSMutableOrderedSet<ObjectType> (NSMutableOrderedSetCreation)

/// Creates and returns an mutable ordered set with a given initial capacity.
///
/// - Parameter numItems: The initial capacity of the new ordered set.
/// - Returns: A mutable ordered set with initial capacity to hold `numItems` members.
///
/// Mutable ordered sets allocate additional memory as needed, so `numItems` simply establishes the set's initial capacity.
+ (instancetype)orderedSetWithCapacity:(NSUInteger)numItems;

@end

API_AVAILABLE(macosx(10.15), ios(13.0), watchos(6.0), tvos(13.0))
NS_SWIFT_UNAVAILABLE("NSMutableOrderedSet diffing methods are not available in Swift")
@interface NSMutableOrderedSet<ObjectType> (NSMutableOrderedSetDiffing)

- (void)applyDifference:(NSOrderedCollectionDifference<ObjectType> *)difference;

@end

NS_HEADER_AUDIT_END(nullability, sendability)
