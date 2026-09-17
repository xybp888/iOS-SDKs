/*	NSArray.h
	Copyright (c) 1994-2019, Apple Inc. All rights reserved.
*/

#import <Foundation/NSObject.h>
#import <Foundation/NSEnumerator.h>
#import <Foundation/NSRange.h>
#import <Foundation/NSObjCRuntime.h>
#import <Foundation/NSOrderedCollectionDifference.h>

@class NSData, NSIndexSet, NSString, NSURL;

/* ***************	Immutable Array		****************/

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

/// A static ordered collection of objects.
///
/// You can use this type in Swift instead of an `Array` constant in cases that require reference semantics.
///
/// `NSArray` and its subclass `NSMutableArray` manage ordered collections of objects called **arrays**. `NSArray`
/// creates static arrays, and `NSMutableArray` creates dynamic arrays. You can use arrays when you need an ordered
/// collection of objects.
///
/// `NSArray` is "toll-free bridged" with its Core Foundation counterpart, `CFArray`. See
/// [Toll-Free Bridging](https://developer.apple.com/library/archive/documentation/General/Conceptual/CocoaEncyclopedia/Toll-FreeBridgin/Toll-FreeBridgin.html#//apple_ref/doc/uid/TP40010810-CH2)
/// for more information on toll-free bridging.
///
/// ### Creating NSArray Objects Using Array Literals
///
/// In addition to the provided initializers, such as `initWithObjects:`, you can create an `NSArray` object using an
/// _array literal_.
///
/// In Objective-C:
///
///     NSArray *array = @[someObject, @"Hello, World!", @42];
///
/// In Objective-C, the compiler generates code that makes an underlying call to the `initWithObjects:count:` method.
///
///     id objects[] = { someObject, @"Hello, World!", @42 };
///     NSUInteger count = sizeof(objects) / sizeof(id);
///     NSArray *array = [NSArray arrayWithObjects:objects
///                                          count:count];
///
/// You should not terminate the list of objects with `nil` when using this literal syntax, and in fact `nil` is an
/// invalid value. For more information about object literals in Objective-C, see
/// [Working with Objects](https://developer.apple.com/library/archive/documentation/Cocoa/Conceptual/ProgrammingWithObjectiveC/WorkingwithObjects/WorkingwithObjects.html#//apple_ref/doc/uid/TP40011210-CH4)
/// in
/// [Programming with Objective-C](https://developer.apple.com/library/archive/documentation/Cocoa/Conceptual/ProgrammingWithObjectiveC/Introduction/Introduction.html#//apple_ref/doc/uid/TP40011210).
///
/// ### Accessing Values Using Subscripting
///
/// In addition to the provided instance methods, such as `objectAtIndex:`, you can access `NSArray` values by their
/// indexes using _subscripting_.
///
///     id value = array[3];
///
/// ### Subclassing Notes
///
/// There is typically little reason to subclass `NSArray`. The class does well what it is designed to do -- maintain an
/// ordered collection of objects. But there are situations where a custom `NSArray` object might come in handy. Here
/// are a few possibilities:
///
/// - Changing how `NSArray` stores the elements of its collection. You might do this for performance reasons or for
///   better compatibility with legacy code.
/// - Acquiring more information about what is happening to the collection (for example, statistics gathering).
///
/// #### Methods to Override
///
/// Any subclass of `NSArray` _must_ override the primitive instance methods `count` and `objectAtIndex:`. These methods
/// must operate on the backing store that you provide for the elements of the collection. For this backing store you
/// can use a static array, a standard `NSArray` object, or some other data type or mechanism. You may also choose to
/// override, partially or fully, any other `NSArray` method for which you want to provide an alternative
/// implementation.
///
/// You might want to implement an initializer for your subclass that is suited to the backing store that the subclass
/// is managing. If you do, your initializer must invoke one of the designated initializers of the `NSArray` class,
/// either `init` or `initWithObjects:count:`. The `NSArray` class adopts the `NSCopying`, `NSMutableCopying`, and
/// `NSCoding` protocols; custom subclasses of `NSArray` should override the methods in these protocols as necessary.
///
/// Remember that `NSArray` is the public interface for a class cluster and what this entails for your subclass. You
/// must provide the storage for your subclass and implement the primitive methods that directly act on that storage.
///
/// #### Alternatives to Subclassing
///
/// Before making a custom subclass of `NSArray`, investigate `NSPointerArray` and the corresponding Core Foundation
/// type, `CFArray`. Because `NSArray` and `CFArray` are "toll-free bridged," you can substitute a `CFArray` object for
/// a `NSArray` object in your code (with appropriate casting). Although they are corresponding types, `CFArray` and
/// `NSArray` do not have identical interfaces or implementations, and you can sometimes do things with `CFArray` that
/// you cannot easily do with `NSArray`. For example, `CFArray` provides a set of callbacks, some of which are for
/// implementing custom retain-release behavior. If you specify `NULL` implementations for these callbacks, you can
/// easily get a non-retaining array.
///
/// If the behavior you want to add supplements that of the existing class, you could write a category on `NSArray`.
/// Keep in mind, however, that this category will be in effect for all instances of `NSArray` that you use, and this
/// might have unintended consequences. Alternatively, you could use composition to achieve the desired behavior.
@interface NSArray<__covariant ObjectType> : NSObject <NSCopying, NSMutableCopying, NSSecureCoding, NSFastEnumeration>

/// The number of objects in the array.
@property (readonly) NSUInteger count;
/// Returns the object located at the specified index.
///
/// If `index` is beyond the end of the array (that is, if `index` is greater than or equal to the value returned by
/// `count`), an `NSRangeException` is raised.
///
/// - Parameter index: An index within the bounds of the array.
/// - Returns: The object located at `index`.
- (ObjectType)objectAtIndex:(NSUInteger)index;
/// Initializes a newly allocated array.
///
/// After an immutable array has been initialized in this way, it cannot be modified.
///
/// This method is a designated initializer.
///
/// - Returns: An array.
- (instancetype)init NS_DESIGNATED_INITIALIZER;
/// Initializes a newly allocated array to include a given number of objects from a given C array.
///
/// Elements are added to the new array in the same order they appear in `objects`, up to but not including index
/// `count`.
///
/// After an immutable array has been initialized in this way, it can't be modified.
///
/// This method is a designated initializer.
///
/// - Parameters:
///   - objects: A C array of objects.
///   - cnt: The number of values from the `objects` C array to include in the new array. This number will be the count
///     of the new array -- it must not be negative or greater than the number of elements in `objects`.
/// - Returns: A newly allocated array including the first `count` objects from `objects`. The returned object might be
///   different than the original receiver.
- (instancetype)initWithObjects:(const ObjectType _Nonnull [_Nullable])objects count:(NSUInteger)cnt NS_DESIGNATED_INITIALIZER;
/// - Parameter coder: The coder.
- (nullable instancetype)initWithCoder:(NSCoder *)coder NS_DESIGNATED_INITIALIZER;

@end

@interface NSArray<ObjectType> (NSExtendedArray)

/// Returns a new array that is a copy of the receiving array with a given object added to the end.
///
/// If `anObject` is `nil`, an `NSInvalidArgumentException` is raised.
///
/// - Parameter anObject: An object.
/// - Returns: A new array that is a copy of the receiving array with `anObject` added to the end.
- (NSArray<ObjectType> *)arrayByAddingObject:(ObjectType)anObject;
/// Returns a new array that is a copy of the receiving array with the objects contained in another array added to the
/// end.
///
/// - Parameter otherArray: An array.
/// - Returns: A new array that is a copy of the receiving array with the objects contained in `otherArray` added to
///   the end.
- (NSArray<ObjectType> *)arrayByAddingObjectsFromArray:(NSArray<ObjectType> *)otherArray;
/// Constructs and returns an `NSString` object that is the result of interposing a given separator between the
/// elements of the array.
///
/// For example, this code excerpt writes "`here be dragons`" to the console:
///
///     NSArray *pathArray = [NSArray arrayWithObjects:@"here", @"be", @"dragons", nil];
///     NSLog(@"%@",[pathArray componentsJoinedByString:@" "]);
///
/// ### Special Considerations
///
/// Each element in the array must handle `description`.
///
/// - Parameter separator: The string to interpose between the elements of the array.
/// - Returns: An `NSString` object that is the result of interposing `separator` between the elements of the array. If
///   the array has no elements, returns an `NSString` object representing an empty string.
- (NSString *)componentsJoinedByString:(NSString *)separator;
/// Returns a Boolean value that indicates whether a given object is present in the array.
///
/// Starting at index `0`, each element of the array is checked for equality with `anObject` until a match is found or
/// the end of the array is reached. Objects are considered equal if `isEqual:` returns `YES`.
///
/// To determine if the array contains a particular instance of an object, you can test for identity rather than
/// equality by calling the `indexOfObjectIdenticalTo:` method and comparing the return value to `NSNotFound`.
///
/// - Parameter anObject: An object to look for in the array.
/// - Returns: `YES` if `anObject` is present in the array, otherwise `NO`.
- (BOOL)containsObject:(ObjectType)anObject;
/// A string that represents the contents of the array, formatted as a property list.
@property (readonly, copy) NSString *description;
/// Returns a string that represents the contents of the array, formatted as a property list.
///
/// For a description of how `locale` is applied to each element in the receiving array, see
/// `descriptionWithLocale:indent:`.
///
/// - Parameter locale: An `NSLocale` object or an `NSDictionary` object that specifies options used for formatting
///   each of the array's elements (where recognized). Specify `nil` if you don't want the elements formatted.
/// - Returns: A string that represents the contents of the array, formatted as a property list.
- (NSString *)descriptionWithLocale:(nullable id)locale;
/// Returns a string that represents the contents of the array, formatted as a property list.
///
/// The returned `NSString` object contains the string representations of each of the array's elements, in order, from
/// first to last. To obtain the string representation of a given element, `descriptionWithLocale:indent:` proceeds as
/// follows:
///
/// - If the element is an `NSString` object, it is used as is.
/// - If the element responds to `descriptionWithLocale:indent:`, that method is invoked to obtain the element's string
///   representation.
/// - If the element responds to `descriptionWithLocale:`, that method is invoked to obtain the element's string
///   representation.
/// - If none of the above conditions is met, the element's string representation is obtained by invoking its
///   `description` method.
///
/// - Parameters:
///   - locale: An `NSLocale` object or an `NSDictionary` object that specifies options used for formatting each of the
///     array's elements (where recognized). Specify `nil` if you don't want the elements formatted.
///   - level: A level of indent, to make the output more readable: set `level` to `0` to use four spaces to indent, or
///     `1` to indent the output with a tab character.
/// - Returns: A string that represents the contents of the array, formatted as a property list.
- (NSString *)descriptionWithLocale:(nullable id)locale indent:(NSUInteger)level;
/// Returns the first object contained in the receiving array that's equal to an object in another given array.
///
/// This method uses `isEqual:` to check for object equality.
///
/// - Parameter otherArray: An array.
/// - Returns: Returns the first object contained in the receiving array that's equal to an object in `otherArray`. If
///   no such object is found, returns `nil`.
- (nullable ObjectType)firstObjectCommonWithArray:(NSArray<ObjectType> *)otherArray;
/// Copies references to objects contained in the array that fall within the specified range to `aBuffer`.
///
/// The method copies into `aBuffer` references to objects in the array in the range specified by `aRange`; the size of
/// the buffer must therefore be at least the length of the range multiplied by the size of an object reference, as
/// shown in the following example (this is solely for illustration -- you should typically not create a buffer simply
/// to iterate over the contents of an array):
///
///     NSArray *mArray = // an array with at least six elements...;
///     id *objects;
///
///     NSRange range = NSMakeRange(2, 4);
///     objects = malloc(sizeof(id) * range.length);
///
///     [mArray getObjects:objects range:range];
///
///     for (i = 0; i < range.length; i++) {
///         NSLog(@"objects: %@", objects[i]);
///     }
///     free(objects);
///
/// - Parameters:
///   - objects: A C array of objects of size at least the length of the range specified by `aRange`.
///   - range: A range within the bounds of the array. If the location plus the length of the range is greater than the
///     count of the array, this method raises an `NSRangeException`.
- (void)getObjects:(ObjectType _Nonnull __unsafe_unretained [_Nonnull])objects range:(NSRange)range NS_SWIFT_UNAVAILABLE("Use 'subarrayWithRange()' instead");
/// Returns the lowest index whose corresponding array value is equal to a given object.
///
/// Starting at index `0`, each element of the array is passed as an argument to an `isEqual:` message sent to
/// `anObject` until a match is found or the end of the array is reached. Objects are considered equal if `isEqual:`
/// (declared in the `NSObject` protocol) returns `YES`.
///
/// - Parameter anObject: An object.
/// - Returns: The lowest index whose corresponding array value is equal to `anObject`. If none of the objects in the
///   array is equal to `anObject`, returns `NSNotFound`.
- (NSUInteger)indexOfObject:(ObjectType)anObject;
/// Returns the lowest index within a specified range whose corresponding array value is equal to a given object.
///
/// Starting at `range.location`, each element of the array is passed as an argument to an `isEqual:` message sent to
/// `anObject` until a match is found or the end of the `range` is reached. Objects are considered equal if `isEqual:`
/// returns `YES`.
///
/// This method raises an `NSRangeException` exception if the `range` parameter represents a range that doesn't exist
/// in the array.
///
/// - Parameters:
///   - anObject: An object.
///   - range: The range of indexes in the array within which to search for `anObject`.
/// - Returns: The lowest index within `range` whose corresponding array value is equal to `anObject`. If none of the
///   objects within `range` is equal to `anObject`, returns `NSNotFound`.
- (NSUInteger)indexOfObject:(ObjectType)anObject inRange:(NSRange)range;
/// Returns the lowest index whose corresponding array value is identical to a given object.
///
/// Objects are considered identical if their object addresses are the same.
///
/// - Parameter anObject: An object.
/// - Returns: The lowest index whose corresponding array value is identical to `anObject`. If none of the objects in
///   the array is identical to `anObject`, returns `NSNotFound`.
- (NSUInteger)indexOfObjectIdenticalTo:(ObjectType)anObject;
/// Returns the lowest index within a specified range whose corresponding array value is equal to a given object.
///
/// Objects are considered identical if their object addresses are the same.
///
/// - Parameters:
///   - anObject: An object.
///   - range: The range of indexes in the array within which to search for `anObject`.
/// - Returns: The lowest index within `range` whose corresponding array value is identical to `anObject`. If none of
///   the objects within `range` is identical to `anObject`, returns `NSNotFound`.
- (NSUInteger)indexOfObjectIdenticalTo:(ObjectType)anObject inRange:(NSRange)range;
/// Compares the receiving array to another array.
///
/// Two arrays have equal contents if they each hold the same number of objects and objects at a given index in each
/// array satisfy the `isEqual:` test.
///
/// - Parameter otherArray: An array.
/// - Returns: `YES` if the contents of `otherArray` are equal to the contents of the receiving array, otherwise `NO`.
- (BOOL)isEqualToArray:(NSArray<ObjectType> *)otherArray;
/// The first object in the array.
///
/// If the array is empty, returns `nil`.
@property (nullable, nonatomic, readonly) ObjectType firstObject API_AVAILABLE(macos(10.6), ios(4.0), watchos(2.0), tvos(9.0));
/// The last object in the array.
///
/// If the array is empty, returns `nil`.
@property (nullable, nonatomic, readonly) ObjectType lastObject;
/// Returns an enumerator object that lets you access each object in the array.
///
/// Returns an enumerator object that lets you access each object in the array, in order, starting with the element at
/// index 0, as in:
///
///     NSEnumerator *enumerator = [myArray objectEnumerator];
///     id anObject;
///
///     while (anObject = [enumerator nextObject]) {
///         /* code to act on each element as it is returned */
///     }
///
/// ### Special Considerations
///
/// When you use this method with mutable subclasses of `NSArray`, you must not modify the array during enumeration.
///
/// It is more efficient to use the fast enumeration protocol (see `NSFastEnumeration`). Fast enumeration is available
/// in macOS 10.5 and later and iOS 2.0 and later.
///
/// - Returns: An enumerator object that lets you access each object in the array, in order, from the element at the
///   lowest index upwards.
- (NSEnumerator<ObjectType> *)objectEnumerator;
/// Returns an enumerator object that lets you access each object in the array, in reverse order.
///
/// When you use this method with mutable subclasses of `NSArray`, you must not modify the array during enumeration.
///
/// It is more efficient to use the fast enumeration protocol (see `NSFastEnumeration`). Fast enumeration is available
/// in macOS 10.5 and later and iOS 2.0 and later.
///
/// - Returns: An enumerator object that lets you access each object in the array, in order, from the element at the
///   highest index down to the element at index `0`.
- (NSEnumerator<ObjectType> *)reverseObjectEnumerator;
/// Analyzes the array and returns a "hint" that speeds the sorting of the array when the hint is supplied to
/// `sortedArrayUsingFunction:context:hint:`.
@property (readonly, copy) NSData *sortedArrayHint;
/// Returns a new array that lists the receiving array's elements in ascending order as defined by the comparison
/// function `comparator`.
///
/// The new array contains references to the receiving array's elements, not copies of them.
///
/// The comparison function is used to compare two elements at a time and should return `NSOrderedAscending` if the
/// first element is smaller than the second, `NSOrderedDescending` if the first element is larger than the second, and
/// `NSOrderedSame` if the elements are equal. Each time the comparison function is called, it's passed `context` as
/// its third argument. This allows the comparison to be based on some outside parameter, such as whether character
/// sorting is case-sensitive or case-insensitive.
///
/// Given `anArray` (an array of `NSNumber` objects) and a comparison function of this type:
///
///     NSInteger intSort(id num1, id num2, void *context)
///     {
///         int v1 = [num1 intValue];
///         int v2 = [num2 intValue];
///         if (v1 < v2)
///             return NSOrderedAscending;
///         else if (v1 > v2)
///             return NSOrderedDescending;
///         else
///             return NSOrderedSame;
///     }
///
/// A sorted version of `anArray` is created in this way:
///
///     NSArray *sortedArray; sortedArray = [anArray sortedArrayUsingFunction:intSort context:NULL];
- (NSArray<ObjectType> *)sortedArrayUsingFunction:(NSInteger (NS_NOESCAPE *)(ObjectType, ObjectType, void * _Nullable))comparator context:(nullable void *)context;
/// Returns a new array that lists the receiving array's elements in ascending order as defined by the comparison
/// function `comparator`.
///
/// The new array contains references to the receiving array's elements, not copies of them.
///
/// This method is similar to `sortedArrayUsingFunction:context:`, except that it uses the supplied hint to speed the
/// sorting process. When you know the array is nearly sorted, this method is faster than
/// `sortedArrayUsingFunction:context:`. If you sorted a large array (`N` entries) once, and you don't change it much
/// (`P` additions and deletions, where `P` is much smaller than `N`), then you can reuse the work you did in the
/// original sort by conceptually doing a merge sort between the `N` "old" items and the `P` "new" items.
///
/// To obtain an appropriate hint, use `sortedArrayHint`. You should obtain this hint when the original array has been
/// sorted, and keep hold of it until you need it, after the array has been modified. The hint is computed by
/// `sortedArrayHint` in `O(N)` (where `N` is the number of items). This assumes that items in the array implement a
/// `-hash` method. Given a suitable hint, and assuming that the hash function is a "good" hash function,
/// `sortedArrayUsingFunction:context:hint:` sorts the array in `O(P*LOG(P)+N)` where `P` is the number of adds or
/// deletes. This is an improvement over the un-hinted sort, `O(N*LOG(N))`, when `P` is small.
///
/// The hint is simply an array of size `N` containing the `N` hashes. To re-sort you need internally to create a map
/// table mapping a hash to the index. Using this map table on the new array, you can get a first guess for the
/// indexes, and then sort that. For example, a sorted array \{A, B, D, E, F\} with corresponding hash values
/// \{25, 96, 78, 32, 17\}, may be subject to small changes that result in contents \{E, A, C, B, F\}. The mapping
/// table maps the hashes \{25, 96, 78, 32, 17\} to the indexes \{#0, #1, #2, #3, #4\}. If the hashes for
/// \{E, A, C, B, F\} are \{32, 25, 99, 96, 17\}, then by using the mapping table you can get a first order sort
/// \{#3, #0, ?, #1, #4\}, so therefore create an initial semi-sorted array \{A, B, E, F\}, and then perform a cheap
/// merge sort with \{C\} that yields \{A, B, C, E, F\}.
- (NSArray<ObjectType> *)sortedArrayUsingFunction:(NSInteger (NS_NOESCAPE *)(ObjectType, ObjectType, void * _Nullable))comparator context:(nullable void *)context hint:(nullable NSData *)hint;
/// Returns an array that lists the receiving array's elements in ascending order, as determined by the comparison
/// method specified by a given selector.
///
/// The new array contains references to the receiving array's elements, not copies of them.
///
/// The `comparator` message is sent to each object in the array and has as its single argument another object in the
/// array.
///
/// For example, an array of `NSString` objects can be sorted by using the `caseInsensitiveCompare:` method declared in
/// the `NSString` class. Assuming `anArray` exists, a sorted version of the array can be created in this way:
///
///     NSArray *sortedArray =
///         [anArray sortedArrayUsingSelector:@selector(caseInsensitiveCompare:)];
///
/// - Parameter comparator: A selector that identifies the method to use to compare two elements at a time. The method
///   should return `NSOrderedAscending` if the receiving array is smaller than the argument,
///   `NSOrderedDescending` if the receiving array is larger than the argument, and `NSOrderedSame` if they are equal.
/// - Returns: An array that lists the receiving array's elements in ascending order, as determined by the comparison
///   method specified by the selector `comparator`.
- (NSArray<ObjectType> *)sortedArrayUsingSelector:(SEL)comparator;
/// Returns a new array containing the receiving array's elements that fall within the limits specified by a given
/// range.
///
/// If `range` isn't within the receiving array's range of elements, an `NSRangeException` is raised.
///
/// For example, the following code example creates an array containing the elements found in the first half of
/// `wholeArray` (assuming `wholeArray` exists).
///
///     NSArray *halfArray;
///     NSRange theRange;
///
///     theRange.location = 0;
///     theRange.length = [wholeArray count] / 2;
///
///     halfArray = [wholeArray subarrayWithRange:theRange];
///
/// - Parameter range: A range within the receiving array's range of elements.
/// - Returns: A new array containing the receiving array's elements that fall within the limits specified by `range`.
- (NSArray<ObjectType> *)subarrayWithRange:(NSRange)range;
/* Serializes this instance to the specified URL in the NSPropertyList format (using NSPropertyListXMLFormat_v1_0). For other formats use NSPropertyListSerialization directly. */
- (BOOL)writeToURL:(NSURL *)url error:(NSError **)error API_AVAILABLE(macos(10.13), ios(11.0), watchos(4.0), tvos(11.0));


/// Sends to each object in the array the message identified by a given selector, starting with the first object and
/// continuing through the array to the last object.
///
/// This method raises an `NSInvalidArgumentException` if `aSelector` is `NULL`.
///
/// - Parameter aSelector: A selector that identifies the message to send to the objects in the array. The method must
///   not take any arguments, and must not have the side effect of modifying the receiving array.
- (void)makeObjectsPerformSelector:(SEL)aSelector NS_SWIFT_UNAVAILABLE("Use enumerateObjectsUsingBlock: or a for loop instead");
/// Sends the `aSelector` message to each object in the array, starting with the first object and continuing through
/// the array to the last object.
///
/// This method raises an `NSInvalidArgumentException` if `aSelector` is `NULL`.
///
/// - Parameters:
///   - aSelector: A selector that identifies the message to send to the objects in the array. The method must take a
///     single argument of type id, and must not have the side effect of modifying the receiving array.
///   - argument: The object to send as the argument to each invocation of the `aSelector` method.
- (void)makeObjectsPerformSelector:(SEL)aSelector withObject:(nullable id)argument NS_SWIFT_UNAVAILABLE("Use enumerateObjectsUsingBlock: or a for loop instead");

/// Returns an array containing the objects in the array at the indexes specified by a given index set.
///
/// The returned objects are in the ascending order of their indexes in `indexes`, so that object in returned array with
/// higher index in indexes will follow the object with smaller index in `indexes`.
///
/// Raises an `NSRangeException` if any location in `indexes` exceeds the bounds of the array, `indexes` is `nil`.
///
/// - Returns: An array containing the objects in the array at the indexes specified by `indexes`.
- (NSArray<ObjectType> *)objectsAtIndexes:(NSIndexSet *)indexes;

/// Returns the object at the specified index.
///
/// This method has the same behavior as the `objectAtIndex:` method.
///
/// If `idx` is beyond the end of the array (that is, if `idx` is greater than or equal to the value returned by
/// `count`), an `NSRangeException` is raised.
///
/// You shouldn't need to call this method directly. Instead, this method is called when accessing an object by index
/// using subscripting.
///
///     id value = array[3]; // equivalent to [array objectAtIndex:3]
///
/// - Parameter idx: An index within the bounds of the array.
/// - Returns: The object located at `idx`.
- (ObjectType)objectAtIndexedSubscript:(NSUInteger)idx API_AVAILABLE(macos(10.8), ios(6.0), watchos(2.0), tvos(9.0));

/// Executes a given closure or block using each object in the array, starting with the first object and continuing
/// through the array to the last object.
///
/// This method executes synchronously. Values allocated within the block are deallocated after the block is executed.
///
/// - Parameter block: A closure or block to execute for each object in the array, taking three arguments: the object,
///   the index of the object in the array, and a reference to a Boolean value which the closure can set to `YES` in
///   order to stop further enumeration of the array. If a closure stops further enumeration, that closure continues to
///   run until it's finished.
- (void)enumerateObjectsUsingBlock:(void (NS_NOESCAPE ^)(ObjectType obj, NSUInteger idx, BOOL *stop))block API_AVAILABLE(macos(10.6), ios(4.0), watchos(2.0), tvos(9.0));
/// Executes a given closure or block using each object in the array with the specified options.
///
/// This method executes synchronously. By default, the enumeration starts with the first object and continues serially
/// through the array to the last object. You can specify `NSEnumerationConcurrent` and/or `NSEnumerationReverse` as
/// enumeration options to modify this behavior.
///
/// - Parameters:
///   - opts: The options for the enumeration. For possible values, see `NSEnumerationOptions`.
///   - block: A closure or block to execute for each object in the array, taking three arguments: the object, the
///     index of the object in the array, and a reference to a Boolean value which the closure can set to `YES` in order
///     to stop further enumeration of the array. If a closure stops further enumeration, that closure continues to run
///     until it's finished. When the `NSEnumerationConcurrent` enumeration option is specified, enumeration stops after
///     all of the currently running closures finish.
- (void)enumerateObjectsWithOptions:(NSEnumerationOptions)opts usingBlock:(void (NS_NOESCAPE ^)(ObjectType obj, NSUInteger idx, BOOL *stop))block API_AVAILABLE(macos(10.6), ios(4.0), watchos(2.0), tvos(9.0));
/// Executes a given block using the objects in the array at the specified indexes.
///
/// By default, the enumeration starts with the first object and continues serially through the array to the last
/// element specified by `indexSet`. You can specify `NSEnumerationConcurrent` and/or `NSEnumerationReverse` as
/// enumeration options to modify this behavior.
///
/// This method executes synchronously.
///
/// > Important: If the block parameter or the `indexSet` is `nil` this method will raise an exception.
///
/// - Parameters:
///   - s: The indexes of the objects over which to enumerate.
///   - opts: A bit mask that specifies the options for the enumeration (whether it should be performed concurrently and
///     whether it should be performed in reverse order).
///   - block: The block to apply to elements in the array. The block takes three arguments: the element in the array,
///     the index of the element in the array, and a reference to a Boolean value. The block can set the value to `YES`
///     to stop further enumeration of the array. If a block stops further enumeration, that block continues to run
///     until it's finished. When the `NSEnumerationConcurrent` enumeration option is specified, enumeration stops after
///     all of the currently running blocks finish. The `stop` argument is an out-only argument. You should only ever
///     set this Boolean to `YES` within the block.
- (void)enumerateObjectsAtIndexes:(NSIndexSet *)s options:(NSEnumerationOptions)opts usingBlock:(void (NS_NOESCAPE ^)(ObjectType obj, NSUInteger idx, BOOL *stop))block API_AVAILABLE(macos(10.6), ios(4.0), watchos(2.0), tvos(9.0));

/// Returns the index of the first object in the array that passes a test in a given block.
///
/// If the block parameter is `nil` this method will raise an exception.
///
/// - Parameter predicate: The block to apply to elements in the array. The block takes three arguments: the element in
///   the array, the index of the element in the array, and a reference to a Boolean value. The block can set the value
///   to `YES` to stop further enumeration of the array. If a block stops further enumeration, that block continues to
///   run until it's finished. The `stop` argument is an out-only argument. You should only ever set this Boolean to
///   `YES` within the block. The block returns a Boolean value that indicates whether `obj` passed the test. Returning
///   `YES` will stop further processing of the array.
/// - Returns: The lowest index whose corresponding value in the array passes the test specified by `predicate`. If no
///   objects in the array pass the test, returns `NSNotFound`.
- (NSUInteger)indexOfObjectPassingTest:(BOOL (NS_NOESCAPE ^)(ObjectType obj, NSUInteger idx, BOOL *stop))predicate API_AVAILABLE(macos(10.6), ios(4.0), watchos(2.0), tvos(9.0));
/// Returns the index of an object in the array that passes a test in a given block for a given set of enumeration
/// options.
///
/// By default, the enumeration starts with the first object and continues serially through the array to the last
/// object. You can specify `NSEnumerationConcurrent` and/or `NSEnumerationReverse` as enumeration options to modify
/// this behavior.
///
/// > Important: If the block parameter is `nil` this method will raise an exception.
///
/// - Parameters:
///   - opts: A bit mask that specifies the options for the enumeration (whether it should be performed concurrently and
///     whether it should be performed in reverse order).
///   - predicate: The block to apply to elements in the array. The block takes three arguments: the element in the
///     array, the index of the element in the array, and a reference to a Boolean value. The block can set the value to
///     `YES` to stop further enumeration of the array. If a block stops further enumeration, that block continues to
///     run until it's finished. When the `NSEnumerationConcurrent` enumeration option is specified, enumeration stops
///     after all of the currently running blocks finish. The `stop` argument is an out-only argument. You should only
///     ever set this Boolean to `YES` within the block. The block returns a Boolean value that indicates whether `obj`
///     passed the test.
/// - Returns: The index whose corresponding value in the array passes the test specified by `predicate` and `opts`. If
///   the `opts` bit mask specifies reverse order, then the last item that matches is returned. Otherwise, the index of
///   the first matching object is returned. If no objects in the array pass the test, returns `NSNotFound`.
- (NSUInteger)indexOfObjectWithOptions:(NSEnumerationOptions)opts passingTest:(BOOL (NS_NOESCAPE ^)(ObjectType obj, NSUInteger idx, BOOL *stop))predicate API_AVAILABLE(macos(10.6), ios(4.0), watchos(2.0), tvos(9.0));
/// Returns the index, from a given set of indexes, of the first object in the array that passes a test in a given
/// block for a given set of enumeration options.
///
/// By default, the enumeration starts with the first object and continues serially through the array to the last
/// element specified by `indexSet`. You can specify `NSEnumerationConcurrent` and/or `NSEnumerationReverse` as
/// enumeration options to modify this behavior.
///
/// > Important: If the block parameter or `indexSet` is `nil` this method will raise an exception.
///
/// - Parameters:
///   - s: The indexes of the objects over which to enumerate.
///   - opts: A bit mask that specifies the options for the enumeration (whether it should be performed concurrently and
///     whether it should be performed in reverse order).
///   - predicate: The block to apply to elements in the array. The block takes three arguments: the element in the
///     array, the index of the element in the array, and a reference to a Boolean value. The block can set the value to
///     `YES` to stop further enumeration of the array. If a block stops further enumeration, that block continues to
///     run until it's finished. When the `NSEnumerationConcurrent` enumeration option is specified, enumeration stops
///     after all of the currently running blocks finish. The `stop` argument is an out-only argument. You should only
///     ever set this Boolean to `YES` within the block. The block returns a Boolean value that indicates whether `obj`
///     passed the test.
/// - Returns: The lowest index whose corresponding value in the array passes the test specified by `predicate`. If no
///   objects in the array pass the test, returns `NSNotFound`.
- (NSUInteger)indexOfObjectAtIndexes:(NSIndexSet *)s options:(NSEnumerationOptions)opts passingTest:(BOOL (NS_NOESCAPE^)(ObjectType obj, NSUInteger idx, BOOL *stop))predicate API_AVAILABLE(macos(10.6), ios(4.0), watchos(2.0), tvos(9.0));

/// Returns the indexes of objects in the array that pass a test in a given block.
///
/// - Parameter predicate: The block to apply to elements in the array. The block takes three arguments: the element in
///   the array, the index of the element in the array, and a reference to a Boolean value. The block can set the value
///   to `YES` to stop further enumeration of the array. If a block stops further enumeration, that block continues to
///   run until it's finished. The `stop` argument is an out-only argument. You should only ever set this Boolean to
///   `YES` within the block. The block returns a Boolean value that indicates whether `obj` passed the test.
/// - Returns: The indexes whose corresponding values in the array pass the test specified by `predicate`. If no
///   objects in the array pass the test, returns an empty index set.
- (NSIndexSet *)indexesOfObjectsPassingTest:(BOOL (NS_NOESCAPE ^)(ObjectType obj, NSUInteger idx, BOOL *stop))predicate API_AVAILABLE(macos(10.6), ios(4.0), watchos(2.0), tvos(9.0));
/// Returns the indexes of objects in the array that pass a test in a given block for a given set of enumeration
/// options.
///
/// By default, the enumeration starts with the first object and continues serially through the array to the last
/// object. You can specify `NSEnumerationConcurrent` and/or `NSEnumerationReverse` as enumeration options to modify
/// this behavior.
///
/// > Important: If the block parameter is `nil` this method will raise an exception.
///
/// - Parameters:
///   - opts: A bit mask that specifies the options for the enumeration (whether it should be performed concurrently and
///     whether it should be performed in reverse order).
///   - predicate: The block to apply to elements in the array. The block takes three arguments: the element in the
///     array, the index of the element in the array, and a reference to a Boolean value. The block can set the value to
///     `YES` to stop further enumeration of the array. If a block stops further enumeration, that block continues to
///     run until it's finished. When the `NSEnumerationConcurrent` enumeration option is specified, enumeration stops
///     after all of the currently running blocks finish. The `stop` argument is an out-only argument. You should only
///     ever set this Boolean to `YES` within the block. The block returns a Boolean value that indicates whether `obj`
///     passed the test.
/// - Returns: The indexes whose corresponding values in the array pass the test specified by `predicate`. If no
///   objects in the array pass the test, returns an empty index set.
- (NSIndexSet *)indexesOfObjectsWithOptions:(NSEnumerationOptions)opts passingTest:(BOOL (NS_NOESCAPE ^)(ObjectType obj, NSUInteger idx, BOOL *stop))predicate API_AVAILABLE(macos(10.6), ios(4.0), watchos(2.0), tvos(9.0));
/// Returns the indexes, from a given set of indexes, of objects in the array that pass a test in a given block for a
/// given set of enumeration options.
///
/// By default, the enumeration starts with the first object and continues serially through the array to the last
/// element specified by `indexSet`. You can specify `NSEnumerationConcurrent` and/or `NSEnumerationReverse` as
/// enumeration options to modify this behavior.
///
/// > Important: If the block parameter or the `indexSet` is `nil` this method will raise an exception.
///
/// - Parameters:
///   - s: The indexes of the objects over which to enumerate.
///   - opts: A bit mask that specifies the options for the enumeration (whether it should be performed concurrently and
///     whether it should be performed in reverse order).
///   - predicate: The block to apply to elements in the array. The block takes three arguments: the element in the
///     array, the index of the element in the array, and a reference to a Boolean value. The block can set the value to
///     `YES` to stop further enumeration of the array. If a block stops further enumeration, that block continues to
///     run until it's finished. When the `NSEnumerationConcurrent` enumeration option is specified, enumeration stops
///     after all of the currently running blocks finish. The `stop` argument is an out-only argument. You should only
///     ever set this Boolean to `YES` within the block. The block returns a Boolean value that indicates whether `obj`
///     passed the test.
/// - Returns: The indexes whose corresponding values in the array pass the test specified by `predicate`. If no
///   objects in the array pass the test, returns an empty index set.
- (NSIndexSet *)indexesOfObjectsAtIndexes:(NSIndexSet *)s options:(NSEnumerationOptions)opts passingTest:(BOOL (NS_NOESCAPE ^)(ObjectType obj, NSUInteger idx, BOOL *stop))predicate API_AVAILABLE(macos(10.6), ios(4.0), watchos(2.0), tvos(9.0));

/// Returns an array that lists the receiving array's elements in ascending order, as determined by the comparison
/// method specified by a given `NSComparator` block.
///
/// - Parameter cmptr: A comparator block.
/// - Returns: An array that lists the receiving array's elements in ascending order, as determined by the comparison
///   method specified `cmptr`.
- (NSArray<ObjectType> *)sortedArrayUsingComparator:(NSComparator NS_NOESCAPE)cmptr API_AVAILABLE(macos(10.6), ios(4.0), watchos(2.0), tvos(9.0));
/// Returns an array that lists the receiving array's elements in ascending order, as determined by the comparison
/// method specified by a given `NSComparator` block.
///
/// - Parameters:
///   - opts: A bit mask that specifies the options for the sort (whether it should be performed concurrently and
///     whether it should be performed stably).
///   - cmptr: A comparator block.
/// - Returns: An array that lists the receiving array's elements in ascending order, as determined by the comparison
///   method specified `cmptr`.
- (NSArray<ObjectType> *)sortedArrayWithOptions:(NSSortOptions)opts usingComparator:(NSComparator NS_NOESCAPE)cmptr API_AVAILABLE(macos(10.6), ios(4.0), watchos(2.0), tvos(9.0));

/// Options for searches and insertions using ``NSArray/index(of:inSortedRange:options:usingComparator:)``.
typedef NS_OPTIONS(NSUInteger, NSBinarySearchingOptions) {
	/// Specifies that the search should find the first object equal to the given object.
	NSBinarySearchingFirstEqual = (1UL << 8),
	/// Specifies that the search should find the last object equal to the given object.
	NSBinarySearchingLastEqual = (1UL << 9),
	/// Specifies that the search should return the insertion index for the given object.
	NSBinarySearchingInsertionIndex = (1UL << 10),
};

/// Returns the index, within a specified range, of an object compared with elements in the array using a given
/// `NSComparator` block.
///
/// The elements in the array must have already been sorted using the comparator `cmp`. If the array is not sorted, the
/// result is undefined.
///
/// - Parameters:
///   - obj: An object for which to search in the array. If this value is `nil`, throws an
///     `NSInvalidArgumentException`.
///   - r: The range within the array to search for `obj`. If `r` exceeds the bounds of the array (if the location plus
///     length of the range is greater than the count of the array), throws an `NSRangeException`.
///   - opts: Options for the search. For possible values, see `NSBinarySearchingOptions`. If you specify both
///     `NSBinarySearchingFirstEqual` and `NSBinarySearchingLastEqual`, throws an `NSInvalidArgumentException`.
///   - cmp: A comparator block used to compare the object `obj` with elements in the array. If this value is `NULL`,
///     throws an `NSInvalidArgumentException`.
/// - Returns: If the `NSBinarySearchingInsertionIndex` option is not specified: if the `obj` is found and neither
///   `NSBinarySearchingFirstEqual` nor `NSBinarySearchingLastEqual` is specified, returns an arbitrary matching
///   object's index. If the `NSBinarySearchingFirstEqual` option is also specified, returns the lowest index of equal
///   objects. If the `NSBinarySearchingLastEqual` option is also specified, returns the highest index of equal objects.
///   If the object is not found, returns `NSNotFound`.
///
///   If the `NSBinarySearchingInsertionIndex` option is specified, returns the index at which you should insert `obj`
///   in order to maintain a sorted array: if the `obj` is found and neither `NSBinarySearchingFirstEqual` nor
///   `NSBinarySearchingLastEqual` is specified, returns any equal or one larger index than any matching object's index.
///   If the `NSBinarySearchingFirstEqual` option is also specified, returns the lowest index of equal objects. If the
///   `NSBinarySearchingLastEqual` option is also specified, returns the highest index of equal objects. If the object
///   is not found, returns the index of the least greater object, or the index at the end of the array if the object
///   is larger than all other elements.
- (NSUInteger)indexOfObject:(ObjectType)obj inSortedRange:(NSRange)r options:(NSBinarySearchingOptions)opts usingComparator:(NSComparator NS_NOESCAPE)cmp API_AVAILABLE(macos(10.6), ios(4.0), watchos(2.0), tvos(9.0));

@end

@interface NSArray<ObjectType> (NSArrayCreation)

/// Creates and returns an empty array.
///
/// This method is used by mutable subclasses of `NSArray`.
///
/// - Returns: An empty array.
+ (instancetype)array;
/// Creates and returns an array containing a given object.
///
/// Alternatively, you can use array literal syntax in Objective-C to create an array containing a given object:
///
///     NSArray *array = @[@"Hello, world!"];
///
/// - Parameter anObject: An object.
/// - Returns: An array containing the single element `anObject`.
+ (instancetype)arrayWithObject:(ObjectType)anObject;
/// Creates and returns an array that includes a given number of objects from a given C array.
///
/// Elements are added to the new array in the same order they appear in `objects`, up to but not including index
/// `count`. For example:
///
///     NSString *strings[3];
///     strings[0] = @"First";
///     strings[1] = @"Second";
///     strings[2] = @"Third";
///
///     NSArray *stringsArray = [NSArray arrayWithObjects:strings count:2];
///     // strings array contains { @"First", @"Second" }
///
/// - Parameters:
///   - objects: A C array of objects.
///   - cnt: The number of values from the `objects` C array to include in the new array. This number will be the count
///     of the new array -- it must not be negative or greater than the number of elements in `objects`.
/// - Returns: A new array including the first `count` objects from `objects`.
+ (instancetype)arrayWithObjects:(const ObjectType _Nonnull [_Nonnull])objects count:(NSUInteger)cnt;
/// Creates and returns an array containing the objects in the argument list.
///
/// Pass comma-separated list of trailing variadic arguments as additional objects, ending with `nil`.
///
/// The following code example creates an array containing three different types of element:
///
///     NSDate *aDate = [NSDate distantFuture];
///     NSValue *aValue = @(5);
///     NSString *aString = @"hello";
///
///     NSArray *array = [NSArray arrayWithObjects:aDate, aValue, aString, nil];
///
/// Alternatively, you can use array literal syntax in Objective-C or Swift to create an array containing given objects:
///
///     NSArray *array = @[@"alpha", @"bravo", @"charlie"];
///
/// - Parameter firstObj: The first object for the array.
/// - Returns: An array containing the objects in the argument list.
+ (instancetype)arrayWithObjects:(ObjectType)firstObj, ... NS_REQUIRES_NIL_TERMINATION;
/// Creates and returns an array containing the objects in another given array.
///
/// - Parameter array: An array.
/// - Returns: An array containing the objects in `anArray`.
+ (instancetype)arrayWithArray:(NSArray<ObjectType> *)array;

/// Initializes a newly allocated array by placing in it the objects in the argument list.
///
/// Pass comma-separated list of trailing variadic arguments as additional objects, ending with `nil`.
///
/// After an immutable array has been initialized in this way, it can't be modified.
///
/// This method is a designated initializer.
///
/// - Parameter firstObj: The first object for the array.
/// - Returns: An array initialized to include the objects in the argument list. The returned object might be different
///   than the original receiver.
- (instancetype)initWithObjects:(ObjectType)firstObj, ... NS_REQUIRES_NIL_TERMINATION;
/// Initializes a newly allocated array by placing in it the objects contained in a given array.
///
/// After an immutable array has been initialized in this way, it cannot be modified.
///
/// - Parameter array: An array.
/// - Returns: An array initialized to contain the objects in `anArray`. The returned object might be different than the
///   original receiver.
- (instancetype)initWithArray:(NSArray<ObjectType> *)array;
/// Initializes a newly allocated array using `anArray` as the source of data objects for the array.
///
/// After an immutable array has been initialized in this way, it cannot be modified.
///
/// The `copyWithZone:` method performs a shallow copy. If you have a collection of arbitrary depth, passing `YES` for
/// the `flag` parameter will perform an immutable copy of the first level below the surface. If you pass `NO` the
/// mutability of the first level is unaffected. In either case, the mutability of all deeper levels is unaffected.
///
/// - Parameters:
///   - array: An array containing the objects with which to initialize the new array.
///   - flag: If `YES`, each object in `array` receives a `copyWithZone:` message to create a copy of the object --
///     objects must conform to the `NSCopying` protocol. In a managed memory environment, this is instead of the
///     `retain` message the object would otherwise receive. The object copy is then added to the returned array. If
///     `NO`, then in a managed memory environment each object in `array` simply receives a `retain` message when it is
///     added to the returned array.
/// - Returns: An array initialized to contain the objects -- or if `flag` is `YES`, copies of the objects -- in
///   `array`. The returned object might be different than the original receiver.
- (instancetype)initWithArray:(NSArray<ObjectType> *)array copyItems:(BOOL)flag;

/* Reads array stored in NSPropertyList format from the specified url. */
- (nullable NSArray<ObjectType> *)initWithContentsOfURL:(NSURL *)url error:(NSError **)error  API_AVAILABLE(macos(10.13), ios(11.0), watchos(4.0), tvos(11.0));
/* Reads array stored in NSPropertyList format from the specified url. */
+ (nullable NSArray<ObjectType> *)arrayWithContentsOfURL:(NSURL *)url error:(NSError **)error API_AVAILABLE(macos(10.13), ios(11.0), watchos(4.0), tvos(11.0)) NS_SWIFT_UNAVAILABLE("Use initializer instead");

@end

API_AVAILABLE(macosx(10.15), ios(13.0), watchos(6.0), tvos(13.0))
NS_SWIFT_UNAVAILABLE("NSArray diffing methods are not available in Swift, use Collection.difference(from:) instead")
@interface NSArray<ObjectType> (NSArrayDiffing)

/// Compares two arrays, using the provided block and with options, to create a difference object that represents the
/// changes between them.
///
/// The options allow you to choose to omit insertion or removal references to the change objects within the difference
/// object's changes. Don't use the option `NSOrderedCollectionDifferenceCalculationInferMoves` when providing a block
/// for the equivalence test. The changes returned in the difference object don't include valid values for
/// `associatedIndex`.
- (NSOrderedCollectionDifference<ObjectType> *)differenceFromArray:(NSArray<ObjectType> *)other withOptions:(NSOrderedCollectionDifferenceCalculationOptions)options usingEquivalenceTest:(BOOL (NS_NOESCAPE ^)(ObjectType obj1, ObjectType obj2))block;

/// Compares two arrays, with options, to create a difference object that represents the changes between them.
///
/// The difference method creates the difference object by comparing objects within the arrays with the `isEqual:`
/// method.
///
/// The options allow you to choose to omit insertion or removal references to the change objects within the difference
/// object. You can also choose to infer moves when computing the difference, which provides an `associatedIndex`
/// within the change objects that indicates the index in the array where the object moved from.
///
/// The following example computes the difference between two arrays, inferring moves between them:
///
///     NSArray *original = @[@"Red", @"Green", @"Blue"];
///     NSArray *modified = @[@"Red", @"Blue", @"Green"];
///
///     NSOrderedCollectionDifference *diff = [original
///                                            differenceFromArray:modified
///                                            withOptions:NSOrderedCollectionDifferenceCalculationInferMoves];
///
///     // diff.hasChanges == TRUE
///     // diff.insertions.count == 1
///     // diff.removals.count == 1
///
///     // Inferring the moves adds an associatedIndex into the change.
///     NSOrderedCollectionChange* insertion = diff.insertions[0];
///     // insertion.index == 2
///     // insertion.associatedIndex == 1
///
///     NSOrderedCollectionChange* deletion = diff.removals[0];
///     // deletion.index == 1
///     // deletion.associatedIndex == 2
- (NSOrderedCollectionDifference<ObjectType> *)differenceFromArray:(NSArray<ObjectType> *)other withOptions:(NSOrderedCollectionDifferenceCalculationOptions)options;

/// Compares two arrays to create a difference object that represents the changes between them.
///
/// The difference method creates the difference object by comparing objects within the arrays with the `isEqual:`
/// method.
///
/// The following example computes the difference between two arrays:
///
///     NSArray *original = @[@"1", @"2"];
///     NSArray *modified = @[@"1", @"2", @"3"];
///
///     NSOrderedCollectionDifference *diff = [modified differenceFromArray:original];
///     // diff.hasChanges == TRUE
///     // diff.insertions.count == 1
///     // diff.removals.count == 0
// Uses isEqual: to determine the difference between the parameter and the receiver
- (NSOrderedCollectionDifference<ObjectType> *)differenceFromArray:(NSArray<ObjectType> *)other;

/// Creates a new array by applying a difference object to an existing array.
///
/// The following example computes the difference between two arrays, then applies the difference to create an array
/// that duplicates the original:
///
///     NSArray *original = @[@"1", @"2"];
///     NSArray *modified = @[@"1", @"2", @"3"];
///
///     NSOrderedCollectionDifference *diff = [modified differenceFromArray:original];
///     // diff.hasChanges == true
///     // diff.insertions.count == 1
///     // diff.removals.count == 0
///
///     NSArray *updated = [original arrayByApplyingDifference:diff];
///     // updated == [@"1", @"2", @"3"]
- (nullable NSArray<ObjectType> *)arrayByApplyingDifference:(NSOrderedCollectionDifference<ObjectType> *)difference;

@end

@interface NSArray<ObjectType> (NSDeprecated)

/// Copies all the objects contained in the array to `aBuffer`.
///
/// The method copies into `aBuffer` all the objects in the array; the size of the buffer must therefore be at least the
/// count of the array multiplied by the size of an object reference, as shown in the following example (note that this
/// is just an example, you should typically not create a buffer simply to iterate over the contents of an array):
///
///     NSArray *mArray = // ...;
///     id *objects;
///
///     NSUInteger count = [mArray count];
///     objects = malloc(sizeof(id) * count);
///
///     [mArray getObjects:objects];
///
///     for (i = 0; i < count; i++) {
///         NSLog(@"object at index %d: %@", i, objects[i]);
///     }
///     free(objects);
///
/// ### Special Considerations
///
/// This deprecated method is unsafe because it could potentially cause buffer overruns.
///
/// - Parameter objects: A C array of objects of size at least the count of the array.
- (void)getObjects:(ObjectType _Nonnull __unsafe_unretained [_Nonnull])objects NS_SWIFT_UNAVAILABLE("Use 'as [AnyObject]' instead") API_DEPRECATED("Use -getObjects:range: instead", macos(10.0, 10.13), ios(2.0, 11.0), watchos(2.0, 4.0), tvos(9.0, 11.0));

/* These methods are deprecated, and will be marked with API_DEPRECATED in a subsequent release. Use the variants that use errors instead. */
/// Creates and returns an array containing the contents of the file specified by a given path.
///
/// The array representation in the file identified by `aPath` must contain only property list objects (`NSString`,
/// `NSData`, `NSDate`, `NSNumber`, `NSArray`, or `NSDictionary` objects). For more details, see
/// [Property List Programming Guide](https://developer.apple.com/library/archive/documentation/Cocoa/Conceptual/PropertyLists/Introduction/Introduction.html#//apple_ref/doc/uid/10000048i).
/// The objects contained by this array are immutable, even if the array is mutable.
///
/// - Parameter path: The path to a file containing a string representation of an array produced by the
///   `writeToFile:atomically:` method.
/// - Returns: An array containing the contents of the file specified by `aPath`. Returns `nil` if the file can't be
///   opened or if the contents of the file can't be parsed into an array.
+ (nullable NSArray<ObjectType> *)arrayWithContentsOfFile:(NSString *)path API_DEPRECATED_WITH_REPLACEMENT("arrayWithContentsOfURL:error:", macos(10.0, API_TO_BE_DEPRECATED), ios(2.0, API_TO_BE_DEPRECATED), watchos(2.0, API_TO_BE_DEPRECATED), tvos(9.0, API_TO_BE_DEPRECATED));
/// Creates and returns an array containing the contents specified by a given URL.
///
/// The array representation at the location identified by `aURL` must contain only property list objects (`NSString`,
/// `NSData`, `NSArray`, or `NSDictionary` objects). The objects contained by this array are immutable, even if the
/// array is mutable.
///
/// - Parameter url: The location of a file containing a string representation of an array produced by the
///   `writeToURL:atomically:` method.
/// - Returns: An array containing the contents specified by `aURL`. Returns `nil` if the location can't be opened or
///   if the contents of the location can't be parsed into an array.
+ (nullable NSArray<ObjectType> *)arrayWithContentsOfURL:(NSURL *)url API_DEPRECATED_WITH_REPLACEMENT("arrayWithContentsOfURL:error:", macos(10.0, API_TO_BE_DEPRECATED), ios(2.0, API_TO_BE_DEPRECATED), watchos(2.0, API_TO_BE_DEPRECATED), tvos(9.0, API_TO_BE_DEPRECATED));
/// Initializes a newly allocated array with the contents of the file specified by a given path.
///
/// The array representation in the file identified by `aPath` must contain only property list objects (`NSString`,
/// `NSData`, `NSArray`, or `NSDictionary` objects). The objects contained by this array are immutable, even if the
/// array is mutable.
///
/// - Parameter path: The path to a file containing a representation of an array produced by the
///   `writeToFile:atomically:` method.
/// - Returns: An array initialized to contain the contents of the file specified by `aPath` or `nil` if the file
///   can't be opened or the contents of the file can't be parsed into an array. The returned object might be different
///   than the original receiver.
- (nullable NSArray<ObjectType> *)initWithContentsOfFile:(NSString *)path API_DEPRECATED_WITH_REPLACEMENT("initWithContentsOfURL:error:", macos(10.0, API_TO_BE_DEPRECATED), ios(2.0, API_TO_BE_DEPRECATED), watchos(2.0, API_TO_BE_DEPRECATED), tvos(9.0, API_TO_BE_DEPRECATED));
/// Initializes a newly allocated array with the contents of the location specified by a given URL.
///
/// The array representation at the location identified by `aURL` must contain only property list objects (`NSString`,
/// `NSData`, `NSArray`, or `NSDictionary` objects). The objects contained by this array are immutable, even if the
/// array is mutable.
///
/// - Parameter url: The location of a file containing a string representation of an array produced by the
///   `writeToURL:atomically:` method.
/// - Returns: An array initialized to contain the contents specified by `aURL`. Returns `nil` if the location can't
///   be opened or if the contents of the location can't be parsed into an array. The returned object might be
///   different than the original receiver.
- (nullable NSArray<ObjectType> *)initWithContentsOfURL:(NSURL *)url API_DEPRECATED_WITH_REPLACEMENT("initWithContentsOfURL:error:", macos(10.0, API_TO_BE_DEPRECATED), ios(2.0, API_TO_BE_DEPRECATED), watchos(2.0, API_TO_BE_DEPRECATED), tvos(9.0, API_TO_BE_DEPRECATED));
/// Writes the contents of the array to a file at a given path.
///
/// If the array's contents are all property list objects (`NSString`, `NSData`, `NSArray`, or `NSDictionary` objects),
/// the file written by this method can be used to initialize a new array with the class method
/// `arrayWithContentsOfFile:` or the instance method `initWithContentsOfFile:`. This method recursively validates that
/// all the contained objects are property list objects before writing out the file, and returns `NO` if all the objects
/// are not property list objects, since the resultant file would not be a valid property list.
///
/// - Parameters:
///   - path: The path at which to write the contents of the array. If `path` contains a tilde (~) character, you must
///     expand it with `stringByExpandingTildeInPath` before invoking this method.
///   - useAuxiliaryFile: If `YES`, the array is written to an auxiliary file, and then the auxiliary file is renamed to
///     `path`. If `NO`, the array is written directly to `path`. The `YES` option guarantees that `path`, if it exists
///     at all, won't be corrupted even if the system should crash during writing.
/// - Returns: `YES` if the file is written successfully, otherwise `NO`.
- (BOOL)writeToFile:(NSString *)path atomically:(BOOL)useAuxiliaryFile API_DEPRECATED_WITH_REPLACEMENT("writeToURL:error:", macos(10.0, API_TO_BE_DEPRECATED), ios(2.0, API_TO_BE_DEPRECATED), watchos(2.0, API_TO_BE_DEPRECATED), tvos(9.0, API_TO_BE_DEPRECATED));
/// Writes the contents of the array to the location specified by a given URL.
///
/// If the array's contents are all property list objects (`NSString`, `NSData`, `NSArray`, or `NSDictionary` objects),
/// the location written by this method can be used to initialize a new array with the class method
/// `arrayWithContentsOfURL:` or the instance method `initWithContentsOfURL:`.
///
/// - Parameters:
///   - url: The location at which to write the array.
///   - atomically: If `YES`, the array is written to an auxiliary location, and then the auxiliary location is renamed
///     to `aURL`. If `NO`, the array is written directly to `aURL`. The `YES` option guarantees that `aURL`, if it
///     exists at all, won't be corrupted even if the system should crash during writing.
/// - Returns: `YES` if the location is written successfully, otherwise `NO`.
- (BOOL)writeToURL:(NSURL *)url atomically:(BOOL)atomically API_DEPRECATED_WITH_REPLACEMENT("writeToURL:error:", macos(10.0, API_TO_BE_DEPRECATED), ios(2.0, API_TO_BE_DEPRECATED), watchos(2.0, API_TO_BE_DEPRECATED), tvos(9.0, API_TO_BE_DEPRECATED));

@end

/* ***************	Mutable Array		****************/

/// A dynamic ordered collection of objects.
///
/// You can use this type in Swift instead of an `Array` variable in cases that require reference semantics.
///
/// The `NSMutableArray` class declares the programmatic interface to objects that manage a modifiable array of objects.
/// This class adds insertion and deletion operations to the basic array-handling behavior inherited from `NSArray`.
///
/// `NSMutableArray` is "toll-free bridged" with its Core Foundation counterpart, `CFMutableArray`. See
/// [Toll-Free Bridging](https://developer.apple.com/library/archive/documentation/General/Conceptual/CocoaEncyclopedia/Toll-FreeBridgin/Toll-FreeBridgin.html#//apple_ref/doc/uid/TP40010810-CH2)
/// for more information.
///
/// ### Accessing Values Using Subscripting
///
/// In addition to the provided instance methods, such as `replaceObjectAtIndex:withObject:`, you can access
/// `NSArray` values by their indexes using _subscripting_.
///
/// In Swift:
///
///     mutableArray[3] = "someValue"
///
/// In Objective-C:
///
///     mutableArray[3] = @"someValue";
///
/// ### Subclassing Notes
///
/// There is typically little reason to subclass `NSMutableArray`. The class does well what it is designed to do ---
/// maintain a mutable, ordered collection of objects. But there are situations where a custom `NSArray` object might
/// come in handy. Here are a few possibilities:
///
/// - Changing how `NSMutableArray` stores the elements of its collection. You might do this for performance reasons or
///   for better compatibility with legacy code.
/// - Acquiring more information about what is happening to the collection (for example, statistics gathering).
///
/// #### Methods to Override
///
/// `NSMutableArray` defines five primitive methods:
///
/// - `insertObject:atIndex:`
/// - `removeObjectAtIndex:`
/// - `addObject:`
/// - `removeLastObject`
/// - `replaceObjectAtIndex:withObject:`
///
/// In a subclass, you must override all these methods. You must also override the primitive methods of the `NSArray`
/// class.
@interface NSMutableArray<ObjectType> : NSArray<ObjectType>

/// Inserts a given object at the end of the array.
///
/// - Parameter anObject: The object to add to the end of the array's content. This value must not be `nil`.
///
///   > Important: Raises an `NSInvalidArgumentException` if `anObject` is `nil`.
- (void)addObject:(ObjectType)anObject;
/// Inserts a given object into the array's contents at a given index.
///
/// If `index` is already occupied, the objects at `index` and beyond are shifted by adding `1` to their indices to make
/// room.
///
/// Note that `NSArray` objects are not like C arrays. That is, even though you specify a size when you create an array,
/// the specified size is regarded as a "hint"; the actual size of the array is still 0. This means that you cannot
/// insert an object at an index greater than the current count of an array. For example, if an array contains two
/// objects, its size is 2, so you can add objects at indices 0, 1, or 2. Index 3 is illegal and out of bounds; if you
/// try to add an object at index 3 (when the size of the array is 2), `NSMutableArray` raises an exception.
///
/// - Parameters:
///   - anObject: The object to add to the array's content. This value must not be `nil`.
///
///     > Important: Raises an `NSInvalidArgumentException` if `anObject` is `nil`.
///
///   - index: The index in the array at which to insert `anObject`. This value must not be greater than the count of
///     elements in the array.
///
///     > Important: Raises an `NSRangeException` if `index` is greater than the number of elements in the array.
- (void)insertObject:(ObjectType)anObject atIndex:(NSUInteger)index;
/// Removes the object with the highest-valued index in the array.
- (void)removeLastObject;
/// Removes the object at `index`.
///
/// To fill the gap, all elements beyond `index` are moved by subtracting 1 from their index.
///
/// - Parameter index: The index from which to remove the object in the array. The value must not exceed the bounds of
///   the array.
///
///   > Important: Raises an exception `NSRangeException` if `index` is beyond the end of the array.
- (void)removeObjectAtIndex:(NSUInteger)index;
/// Replaces the object at `index` with `anObject`.
///
/// - Parameters:
///   - index: The index of the object to be replaced. This value must not exceed the bounds of the array.
///
///     > Important: Raises an `NSRangeException` if `index` is beyond the end of the array.
///
///   - anObject: The object with which to replace the object at index `index` in the array. This value must not be
///     `nil`.
///
///     > Important: Raises an `NSInvalidArgumentException` if `anObject` is `nil`.
- (void)replaceObjectAtIndex:(NSUInteger)index withObject:(ObjectType)anObject;
/// Initializes a newly allocated array.
///
/// This method is a designated initializer.
///
/// - Returns: An array.
- (instancetype)init NS_DESIGNATED_INITIALIZER;
/// Returns an array, initialized with enough memory to initially hold a given number of objects.
///
/// Mutable arrays expand as needed; `numItems` simply establishes the object's initial capacity.
///
/// This method is a designated initializer.
///
/// - Parameter numItems: The initial capacity of the new array.
/// - Returns: An array initialized with enough memory to hold `numItems` objects. The returned object might be
///   different than the original receiver.
- (instancetype)initWithCapacity:(NSUInteger)numItems NS_DESIGNATED_INITIALIZER;
- (nullable instancetype)initWithCoder:(NSCoder *)coder NS_DESIGNATED_INITIALIZER;

@end

@interface NSMutableArray<ObjectType> (NSExtendedMutableArray)

/// Adds the objects contained in another given array to the end of the receiving array's content.
///
/// - Parameter otherArray: An array of objects to add to the end of the receiving array's content.
- (void)addObjectsFromArray:(NSArray<ObjectType> *)otherArray;
/// Exchanges the objects in the array at given indexes.
///
/// - Parameters:
///   - idx1: The index of the object with which to replace the object at index `idx2`.
///   - idx2: The index of the object with which to replace the object at index `idx1`.
- (void)exchangeObjectAtIndex:(NSUInteger)idx1 withObjectAtIndex:(NSUInteger)idx2;
/// Empties the array of all its elements.
- (void)removeAllObjects;
/// Removes all occurrences within a specified range in the array of a given object.
///
/// Matches are determined by comparing `anObject` to the objects in the receiver using the `isEqual:` method. If the
/// array does not contain `anObject` within `aRange`, the method has no effect (although it does incur the overhead of
/// searching the contents).
///
/// - Parameters:
///   - anObject: The object to be removed from the array's content.
///   - range: The range from which to remove `anObject`.
///
///     > Important: Raises an exception `NSRangeException` if `aRange` exceeds the bounds of the array.
- (void)removeObject:(ObjectType)anObject inRange:(NSRange)range;
/// Removes all occurrences in the array of a given object.
///
/// This method determines a match by comparing `anObject` to the objects in the receiver using the `isEqual:` method.
/// If the array does not contain `anObject`, the method has no effect (although it does incur the overhead of searching
/// the contents).
///
/// - Parameter anObject: The object to remove from the array.
- (void)removeObject:(ObjectType)anObject;
/// Removes all occurrences of `anObject` within the specified range in the array.
///
/// This method determines a match by comparing the address of `anObject` to the addresses of objects in the receiver.
/// If the array does not contain `anObject` within `aRange`, the method has no effect (although it does incur the
/// overhead of searching the contents).
///
/// - Parameters:
///   - anObject: The object to remove from the array within `aRange`.
///   - range: The range in the array from which to remove `anObject`.
///
///     > Important: Raises an exception `NSRangeException` if `aRange` exceeds the bounds of the array.
- (void)removeObjectIdenticalTo:(ObjectType)anObject inRange:(NSRange)range;
/// Removes all occurrences of a given object in the array.
///
/// This method determines a match by comparing the address of `anObject` to the addresses of objects in the receiver.
/// If the array does not contain `anObject`, the method has no effect (although it does incur the overhead of searching
/// the contents).
///
/// - Parameter anObject: The object to remove from the array.
- (void)removeObjectIdenticalTo:(ObjectType)anObject;
/// Removes the specified number of objects from the array, beginning at the specified index.
///
/// This method is similar to `removeObjectAtIndex:`, but it allows you to efficiently remove multiple objects with a
/// single operation. If you sort the list of indexes in ascending order, you will improve the speed of this operation.
///
/// This method cannot be sent to a remote object with distributed objects.
///
/// > Note: This deprecated method uses a C array of indices. The `removeObjectsAtIndexes:` method uses an `NSIndexSet`
/// > which provides a more efficient way of indexing into an array.
///
/// - Parameters:
///   - indices: A C array of the indices of the objects to remove from the receiving array.
///   - cnt: The number of objects to remove from the receiving array.
- (void)removeObjectsFromIndices:(NSUInteger *)indices numIndices:(NSUInteger)cnt API_DEPRECATED("Not supported", macos(10.0,10.6), ios(2.0,4.0), watchos(2.0,2.0), tvos(9.0,9.0));
/// Removes from the receiving array the objects in another given array.
///
/// This method is similar to `removeObject:`, but it allows you to efficiently remove large sets of objects with a
/// single operation. If the receiving array does not contain objects in `otherArray`, the method has no effect (although
/// it does incur the overhead of searching the contents).
///
/// This method assumes that all elements in `otherArray` respond to `hash` and `isEqual:`.
///
/// - Parameter otherArray: An array containing the objects to be removed from the receiving array.
- (void)removeObjectsInArray:(NSArray<ObjectType> *)otherArray;
/// Removes from the array each of the objects within a given range.
///
/// The objects are removed using `removeObjectAtIndex:`.
///
/// - Parameter range: The range of the objects to be removed from the array.
- (void)removeObjectsInRange:(NSRange)range;
/// Replaces the objects in the receiving array specified by one given range with the objects in another array specified
/// by another range.
///
/// The lengths of `aRange` and `otherRange` don't have to be equal: If `aRange` is longer than `otherRange`, the extra
/// objects in the receiving array are removed; if `otherRange` is longer than `aRange`, the extra objects from
/// `otherArray` are inserted into the receiving array.
///
/// - Parameters:
///   - range: The range of objects to be replaced in (or removed from) the receiving array.
///   - otherArray: The array of objects from which to select replacements for the objects in `aRange`.
///   - otherRange: The range of objects be selected from `otherArray` as replacements for the objects in `aRange`.
- (void)replaceObjectsInRange:(NSRange)range withObjectsFromArray:(NSArray<ObjectType> *)otherArray range:(NSRange)otherRange;
/// Replaces the objects in the receiving array specified by a given range with all of the objects from a given array.
///
/// If `otherArray` has fewer objects than are specified by `aRange`, the extra objects in the receiving array are
/// removed. If `otherArray` has more objects than are specified by `aRange`, the extra objects from `otherArray` are
/// inserted into the receiving array.
///
/// - Parameters:
///   - range: The range of objects to be replaced in (or removed from) the receiving array.
///   - otherArray: The array of objects from which to select replacements for the objects in `aRange`.
- (void)replaceObjectsInRange:(NSRange)range withObjectsFromArray:(NSArray<ObjectType> *)otherArray;
/// Sets the receiving array's elements to those in another given array.
///
/// - Parameter otherArray: The array of objects with which to replace the receiving array's content.
- (void)setArray:(NSArray<ObjectType> *)otherArray;
/// Sorts the receiver in ascending order as defined by the comparison function `compare`.
///
/// This approach allows the comparison to be based on some outside parameter, such as whether character sorting is case
/// sensitive or case insensitive.
///
/// - Parameters:
///   - compare: The comparison function to use to compare two elements at a time. The function's parameters are two
///     objects to compare and the context parameter, `context`. The function should return `NSOrderedAscending` if the
///     first element is smaller than the second, `NSOrderedDescending` if the first element is larger than the second,
///     and `NSOrderedSame` if the elements are equal.
///   - context: The context argument to be passed to the compare function.
- (void)sortUsingFunction:(NSInteger (NS_NOESCAPE *)(ObjectType,  ObjectType, void * _Nullable))compare context:(nullable void *)context;
/// Sorts the receiver in ascending order, as determined by the comparison method specified by a given selector.
///
/// - Parameter comparator: A selector that specifies the comparison method to use to compare elements in the array. The
///   `comparator` message is sent to each object in the array and has as its single argument another object in the
///   array. The `comparator` method should return `NSOrderedAscending` if the array is smaller than the argument,
///   `NSOrderedDescending` if the array is larger than the argument, and `NSOrderedSame` if they are equal.
- (void)sortUsingSelector:(SEL)comparator;

/// Inserts the objects in the provided array into the receiving array at the specified indexes.
///
/// Each object in `objects` is inserted into the receiving array in turn at the corresponding location specified in
/// `indexes` after earlier insertions have been made. The implementation is conceptually similar to that illustrated in
/// the following example:
///
///     - void insertObjects:(NSArray *)additions atIndexes:(NSIndexSet *)indexes
///     {
///         NSUInteger currentIndex = [indexes firstIndex];
///         NSUInteger i, count = [indexes count];
///
///         for (i = 0; i < count; i++)
///         {
///             [self insertObject:[additions objectAtIndex:i] atIndex:currentIndex];
///             currentIndex = [indexes indexGreaterThanIndex:currentIndex];
///         }
///     }
///
/// The resulting behavior is illustrated by the following example:
///
///     NSMutableArray *array = [NSMutableArray arrayWithObjects: @"one", @"two", @"three", @"four", nil];
///     NSArray *newAdditions = [NSArray arrayWithObjects: @"a", @"b", nil];
///     NSMutableIndexSet *indexes = [NSMutableIndexSet indexSetWithIndex:1];
///     [indexes addIndex:3];
///     [array insertObjects:newAdditions atIndexes:indexes];
///     NSLog(@"array: %@", array);
///
///     // Output: array: (one, a, two, b, three, four)
///
/// The locations specified by `indexes` may therefore only exceed the bounds of the receiving array if one location
/// specifies the count of the array or the count of the array after preceding insertions, and other locations exceeding
/// the bounds do so in a contiguous fashion from that location, as illustrated in the following examples.
///
/// In this example, both new objects are appended to the end of the array.
///
///     NSMutableArray *array = [NSMutableArray arrayWithObjects: @"one", @"two", @"three", @"four", nil];
///     NSArray *newAdditions = [NSArray arrayWithObjects: @"a", @"b", nil];
///     NSMutableIndexSet *indexes = [NSMutableIndexSet indexSetWithIndex:5];
///     [indexes addIndex:4];
///     [array insertObjects:newAdditions atIndexes:indexes];
///     NSLog(@"array: %@", array);
///
///     // Output: array: (one, two, three, four, a, b)
///
/// If you replace `[indexes addIndex:4]` with `[indexes addIndex:6]` (so that the indexes are 5 and 6), then the
/// application will fail with an out of bounds exception.
///
/// In this example, two objects are added into the middle of the array, and another at the current end of the array
/// (index 4) which means that it is third from the end of the modified array.
///
///     NSMutableArray *array = [NSMutableArray arrayWithObjects: @"one", @"two", @"three", @"four", nil];
///     NSArray *newAdditions = [NSArray arrayWithObjects: @"a", @"b", @"c", nil];
///     NSMutableIndexSet *indexes = [NSMutableIndexSet indexSetWithIndex:1];
///     [indexes addIndex:2];
///     [indexes addIndex:4];
///     [array insertObjects:newAdditions atIndexes:indexes];
///     NSLog(@"array: %@", array);
///
///     // Output: array: (one, a, b, two, c, three, four)
///
/// If you replace `[indexes addIndex:4]` with `[indexes addIndex:6]` (so that the indexes are 1, 2, and 6), then the
/// output is `(one, a, b, two, three, four, c)`.
///
/// If `objects` or `indexes` is `nil`, this method will raises an exception.
///
/// - Parameters:
///   - objects: An array of objects to insert into the receiving array.
///   - indexes: The indexes at which the objects in `objects` should be inserted. The count of locations in `indexes`
///     must equal the count of `objects`. For more details, see the Discussion.
- (void)insertObjects:(NSArray<ObjectType> *)objects atIndexes:(NSIndexSet *)indexes;
/// Removes the objects at the specified indexes from the array.
///
/// This method is similar to `removeObjectAtIndex:`, but allows you to efficiently remove multiple objects with a
/// single operation. `indexes` specifies the locations of objects to be removed given the state of the array when the
/// method is invoked, as illustrated in the following example:
///
///     NSMutableArray *array = [NSMutableArray arrayWithObjects: @"one", @"a", @"two", @"b", @"three", @"four", nil];
///     NSMutableIndexSet *indexes = [NSMutableIndexSet indexSetWithIndex:1];
///     [indexes addIndex:3];
///     [array removeObjectsAtIndexes:indexes];
///     NSLog(@"array: %@", array);
///
///     // Output: array: (one, two, three, four)
///
/// If `indexes` is `nil`, this method raises an exception.
///
/// - Parameter indexes: The indexes of the objects to remove from the array. The locations specified by `indexes` must
///   lie within the bounds of the array.
- (void)removeObjectsAtIndexes:(NSIndexSet *)indexes;
/// Replaces the objects in the receiving array at locations specified with the objects from a given array.
///
/// The indexes in `indexes` are used in the same order as the objects in `objects`.
///
/// If `objects` or `indexes` is `nil`, this method raises an exception.
///
/// - Parameters:
///   - indexes: The indexes of the objects to be replaced.
///   - objects: The objects with which to replace the objects in the receiving array at the indexes specified by
///     `indexes`. The count of locations in `indexes` must equal the count of `objects`.
- (void)replaceObjectsAtIndexes:(NSIndexSet *)indexes withObjects:(NSArray<ObjectType> *)objects;

/// Replaces the object at the index with the new object, possibly adding the object.
///
/// This method has the same behavior as the `replaceObjectAtIndex:withObject:` method.
///
/// If `idx` is beyond the end of the array (that is, if `idx` is greater than the value returned by `count`), an
/// `NSRangeException` is raised.
///
/// You shouldn't need to call this method directly. Instead, this method is called when setting an object by index
/// using subscripting.
///
///     mutableArray[3] = @"someValue"; // equivalent to [mutableArray replaceObjectAtIndex:3 withObject:@"someValue"]
///
/// - Parameters:
///   - obj: The object with which to replace the object at index `idx` in the array. This value must not be `nil`.
///
///     > Important: Raises an `NSInvalidArgumentException` if `anObject` is `nil`.
///
///   - idx: The index of the object to be replaced. This value must not exceed the bounds of the array.
///
///     > Important: Raises an `NSRangeException` if `idx` is beyond the end of the array.
- (void)setObject:(ObjectType)obj atIndexedSubscript:(NSUInteger)idx API_AVAILABLE(macos(10.8), ios(6.0), watchos(2.0), tvos(9.0));

/// Sorts the receiver in ascending order using the comparison method specified by a given `NSComparator` block.
///
/// - Parameter cmptr: A comparator block.
- (void)sortUsingComparator:(NSComparator NS_NOESCAPE)cmptr API_AVAILABLE(macos(10.6), ios(4.0), watchos(2.0), tvos(9.0));
/// Sorts the receiver in ascending order using the specified options and the comparison method specified by a given
/// `NSComparator` block.
///
/// - Parameters:
///   - opts: A bitmask that specifies the options for the sort (whether it should be performed concurrently and whether
///     it should be performed stably).
///   - cmptr: A comparator block.
- (void)sortWithOptions:(NSSortOptions)opts usingComparator:(NSComparator NS_NOESCAPE)cmptr API_AVAILABLE(macos(10.6), ios(4.0), watchos(2.0), tvos(9.0));

@end

@interface NSMutableArray<ObjectType> (NSMutableArrayCreation)

/// Creates and returns an `NSMutableArray` object with enough allocated memory to initially hold a given number of
/// objects.
///
/// Mutable arrays expand as needed; `numItems` simply establishes the object's initial capacity.
///
/// - Parameter numItems: The initial capacity of the new array.
/// - Returns: A new `NSMutableArray` object with enough allocated memory to hold `numItems` objects.
+ (instancetype)arrayWithCapacity:(NSUInteger)numItems;

/// Creates and returns a mutable array containing the contents of the file specified by the given path.
///
/// The mutable array representation in the file identified by `aPath` must contain only property list objects
/// (`NSString`, `NSData`, `NSDate`, `NSNumber`, `NSArray`, or `NSDictionary` objects). For more details, see
/// [Property List Programming Guide](https://developer.apple.com/library/archive/documentation/Cocoa/Conceptual/PropertyLists/Introduction/Introduction.html#//apple_ref/doc/uid/10000048i).
/// The objects contained by this array are immutable even if the array is mutable.
///
/// - Parameter path: The path to a file containing a string representation of a mutable array produced by the
///   `writeToFile:atomically:` method.
/// - Returns: A mutable array containing the contents of the file specified `aPath`. Returns `nil` if the file can't be
///   opened or if the contents of the file can't be parsed into a mutable array.
+ (nullable NSMutableArray<ObjectType> *)arrayWithContentsOfFile:(NSString *)path;
/// Creates and returns a mutable array containing the contents specified by a given URL.
///
/// The array representation at the location identified by `aURL` must contain only property list objects (`NSString`,
/// `NSData`, `NSDate`, `NSNumber`, `NSArray`, or `NSDictionary` objects). The objects contained by this array are
/// immutable even if the array is mutable.
///
/// - Parameter url: The location of the file containing a string representation of a mutable array produced by the
///   `writeToURL:atomically:` method.
/// - Returns: A mutable array containing the contents specified by `aURL`. Returns `nil` if the location can't be
///   opened or if the contents of the location can't be parsed into a mutable array.
+ (nullable NSMutableArray<ObjectType> *)arrayWithContentsOfURL:(NSURL *)url;
/// Initializes a newly allocated mutable array with the contents of the file specified by a given path.
///
/// The mutable array representation in the file identified by `aPath` must contain only property list objects
/// (`NSString`, `NSData`, `NSDate`, `NSNumber`, `NSArray`, or `NSDictionary` objects). The objects contained by this
/// array are immutable even if the array is mutable.
///
/// - Parameter path: The path to a file containing a representation of a mutable array produced by
///   `writeToFile:atomically:` method.
/// - Returns: A mutable array initialized to contain the contents of the file specified by `aPath` or `nil` if the file
///   can't be opened or the contents of the file can't be parsed into a mutable array. The returned object must be
///   different than the original receiver.
- (nullable NSMutableArray<ObjectType> *)initWithContentsOfFile:(NSString *)path;
/// Initialized a newly allocated mutable array with the contents of the location specified by a given URL.
///
/// The array representation at the location identified by `aURL` must contain only property list objects (`NSString`,
/// `NSData`,`NSDate`, `NSNumber`, `NSArray`, or `NSDictionary` objects). The objects contained by this array are
/// immutable, even if the array is mutable.
///
/// - Parameter url: The location of a file containing a string representation of a mutable array produced by
///   `writeToURL:atomically:` method.
/// - Returns: A mutable array initialized to contain the contents specified by `aURL`. Returns `nil` if the location
///   can't be opened or if the contents of the location can't be parsed into a mutable array. The returned objects must
///   be different than the original receiver.
- (nullable NSMutableArray<ObjectType> *)initWithContentsOfURL:(NSURL *)url;

@end

API_AVAILABLE(macosx(10.15), ios(13.0), watchos(6.0), tvos(13.0))
NS_SWIFT_UNAVAILABLE("NSMutableArray diffing methods are not available in Swift")
@interface NSMutableArray<ObjectType> (NSMutableArrayDiffing)

- (void)applyDifference:(NSOrderedCollectionDifference<ObjectType> *)difference;

@end

NS_HEADER_AUDIT_END(nullability, sendability)
