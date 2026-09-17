/*
 *  NSPointerArray.h
 *  Copyright (c) 2005-2019, Apple Inc. All rights reserved.
 *
 */
 

#import <Foundation/NSObject.h>
#import <Foundation/NSArray.h>
#import <Foundation/NSPointerFunctions.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

/*
   NSPointerArray.h

   A PointerArray acts like a traditional array that slides elements on insertion or deletion.
   Unlike traditional arrays, it holds NULLs, which can be inserted or extracted (and contribute to count).
   Also unlike traditional arrays, the 'count' of the array may be set directly.
   Using NSPointerFunctionsWeakMemory object references will turn to NULL on last release.

   The copying and archiving protocols are applicable only when NSPointerArray is configured for Object uses.
   The fast enumeration protocol (supporting the for..in statement) will yield NULLs if present.  It is defined for all types of pointers although the language syntax doesn't directly support this.
*/

/// A collection similar to an array, but with a broader range of available memory semantics.
///
/// The pointer array class is modeled after ``NSArray``, but can also hold `nil` values. You can insert or remove `nil` values which contribute to the array's ``count``.
///
/// A pointer array can be initialized to maintain strong or weak references to objects, or according to any of the memory or personality options defined by ``NSPointerFunctions/Options``.
///
/// The ``NSCopying`` and ``NSCoding`` protocols are applicable only when a pointer array is initialized to maintain strong or weak references to objects.
///
/// When enumerating a pointer array with ``NSFastEnumeration`` using `for...in`, the loop will yield any `nil` values present in the array. See [Fast Enumeration Makes It Easy to Enumerate a Collection](https://developer.apple.com/library/archive/documentation/Cocoa/Conceptual/ProgrammingWithObjectiveC/FoundationTypesandCollections/FoundationTypesandCollections.html#//apple_ref/doc/uid/TP40011210-CH7-SW30) in [Programming with Objective-C](https://developer.apple.com/library/archive/documentation/Cocoa/Conceptual/ProgrammingWithObjectiveC/Introduction/Introduction.html#//apple_ref/doc/uid/TP40011210) for more information.
///
/// ### Subclassing Notes
///
/// `NSPointerArray` is not suitable for subclassing.
API_AVAILABLE(macos(10.5), ios(6.0), watchos(2.0), tvos(9.0))
@interface NSPointerArray : NSObject <NSFastEnumeration, NSCopying, NSSecureCoding>
// construction
/// Initializes the receiver to use the given options.
///
/// - Parameter options: The pointer functions options for the new instance.
- (instancetype)initWithOptions:(NSPointerFunctionsOptions)options NS_DESIGNATED_INITIALIZER;
/// Initializes the receiver to use the given functions.
///
/// - Parameter functions: The pointer functions for the new instance.
- (instancetype)initWithPointerFunctions:(NSPointerFunctions *)functions NS_DESIGNATED_INITIALIZER;

/// Returns a new pointer array initialized to use the given options.
///
/// - Parameter options: The pointer functions options for the new instance.
/// - Returns: A new pointer array initialized to use the given options.
+ (NSPointerArray *)pointerArrayWithOptions:(NSPointerFunctionsOptions)options;
/// A new pointer array initialized to use the given functions.
///
/// - Parameter functions: The pointer functions for the new instance.
/// - Returns: A new pointer array initialized to use the given pointer functions.
+ (NSPointerArray *)pointerArrayWithPointerFunctions:(NSPointerFunctions *)functions;

/// The functions in use by the receiver.
///
/// The returned object is a new `NSPointerFunctions` object that you can modify and/or use directly to create other pointer collections.
@property (readonly, copy) NSPointerFunctions *pointerFunctions;

/// Returns the pointer at a given index.
///
/// The returned value may be `NULL`.
///
/// - Parameter index: The index of an element in the receiver. This value must be less than the count of the receiver.
/// - Returns: The pointer at `index`.
- (nullable void *)pointerAtIndex:(NSUInteger)index;

// Array like operations that slide or grow contents, including NULLs
/// Adds a given pointer to the receiver.
///
/// `pointer` is added at index `count`.
///
/// - Parameter pointer: The pointer to add. This value may be `NULL`.
- (void)addPointer:(nullable void *)pointer;  // add pointer at index 'count'
/// Removes the pointer at a given index.
///
/// Elements above `index`, including `NULL` values, slide lower.
///
/// - Parameter index: The index of an element in the receiver. This value must be less than the count of the receiver.
- (void)removePointerAtIndex:(NSUInteger)index;    // everything above index, including holes, slide lower
/// Inserts a pointer at a given index.
///
/// Elements at and above `index`, including `NULL` values, slide higher.
///
/// - Parameter item: The pointer to add.
/// - Parameter index: The index of an element in the receiver. This value must be less than the count of the receiver.
- (void)insertPointer:(nullable void *)item atIndex:(NSUInteger)index;  // everything at & above index, including holes, slide higher

/// Replaces the pointer at a given index.
///
/// - Parameter index: The index of an element in the receiver. This value must be less than the count of the receiver.
/// - Parameter item: The item with which to replace the element at `index`. This value may be `NULL`.
- (void)replacePointerAtIndex:(NSUInteger)index withPointer:(nullable void *)item;  // O(1); NULL item is okay; index must be < count

/// Removes `NULL` values from the receiver.
- (void)compact;   // eliminate NULLs

/// The number of elements in the receiver.
///
/// If you increase the `count`, `NULL` values are added. If you decrease the `count`, elements at indexes `count` and greater are removed.
@property NSUInteger count;

@end


@interface NSPointerArray (NSPointerArrayConveniences)

// construction
#if TARGET_OS_OSX
/// Returns a new pointer array that maintains strong references to its elements.
///
/// @DeprecationSummary Use the `strongObjects()` class method.
+ (id) pointerArrayWithStrongObjects API_DEPRECATED("GC no longer supported", macos(10.5,10.8)) API_UNAVAILABLE(ios, watchos, tvos); // strong objects
/// Returns a new pointer array that maintains weak references to its elements.
///
/// @DeprecationSummary Use the `weakObjects()` class method.
+ (id) pointerArrayWithWeakObjects API_DEPRECATED("GC no longer supported", macos(10.5,10.8)) API_UNAVAILABLE(ios, watchos, tvos); // weak objects
#endif

/// Returns a new pointer array that maintains strong references to its elements.
+ (NSPointerArray *)strongObjectsPointerArray API_AVAILABLE(macos(10.8), ios(6.0), watchos(2.0), tvos(9.0));
/// Returns a new pointer array that maintains weak references to its elements.
+ (NSPointerArray *)weakObjectsPointerArray API_AVAILABLE(macos(10.8), ios(6.0), watchos(2.0), tvos(9.0));

/// All the objects in the receiver.
@property (readonly, copy) NSArray *allObjects;

@end

NS_HEADER_AUDIT_END(nullability, sendability)
