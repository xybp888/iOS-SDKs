/*	NSHashTable.h
	Copyright (c) 1994-2019, Apple Inc. All rights reserved.
*/

#import <Foundation/NSPointerFunctions.h>
#import <Foundation/NSString.h>
#import <Foundation/NSEnumerator.h>

#if !defined(__FOUNDATION_NSHASHTABLE__)
#define __FOUNDATION_NSHASHTABLE__ 1

@class NSArray<ObjectType>, NSSet<ObjectType>, NSHashTable;

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

/* An NSHashTable is modeled after a set, although, because of its options, is not a set because it can behave differently (for example, if pointer equality is specified two isEqual strings will both be entered).  The major option is to provide for "weak" references that are removed automatically, but at some indefinite point in the future.
   An NSHashTable can also be configured to operate on arbitrary pointers and not just objects.  We recommend the C function API for "void *" access.  To configure for pointer use, consult and choose the appropriate NSPointerFunctionsOptions or configure or use an NSPointerFunctions object itself for initialization.
*/

static const NSPointerFunctionsOptions NSHashTableStrongMemory API_AVAILABLE(macos(10.5), ios(6.0), watchos(2.0), tvos(9.0)) = NSPointerFunctionsStrongMemory;
static const NSPointerFunctionsOptions NSHashTableZeroingWeakMemory API_DEPRECATED("GC no longer supported", macos(10.5,10.8)) API_UNAVAILABLE(ios, watchos, tvos) = NSPointerFunctionsZeroingWeakMemory;
static const NSPointerFunctionsOptions NSHashTableCopyIn API_AVAILABLE(macos(10.5), ios(6.0), watchos(2.0), tvos(9.0)) = NSPointerFunctionsCopyIn;
static const NSPointerFunctionsOptions NSHashTableObjectPointerPersonality API_AVAILABLE(macos(10.5), ios(6.0), watchos(2.0), tvos(9.0)) = NSPointerFunctionsObjectPointerPersonality;
static const NSPointerFunctionsOptions NSHashTableWeakMemory API_AVAILABLE(macos(10.8), ios(6.0), watchos(2.0), tvos(9.0)) = NSPointerFunctionsWeakMemory;

/// Components in a bit-field to specify the behavior of elements in an ``NSHashTable`` object.
typedef NSUInteger NSHashTableOptions;

/// A collection similar to a set, but with broader range of available memory semantics.
///
/// The hash table is modeled after ``NSSet`` with the following differences:
///
/// - It can hold weak references to its members.
/// - Its members may be copied on input or may use pointer identity for equality and hashing.
/// - It can contain arbitrary pointers (its members are not constrained to being objects).
///
/// You can configure an ``NSHashTable`` instance to operate on arbitrary pointers and not just objects, although typically you are encouraged to use the C function API for void \* pointers. The object-based API (such as ``add(_:)``) will not work for non-object pointers without type-casting.
///
/// Because of its options, `NSHashTable` is not a set because it can behave differently (for example, if pointer equality is specified two `isEqual:` strings will both be entered).
///
/// When configuring hash tables, note that only the options listed in ``NSHashTableOptions`` guarantee that the rest of the API will work correctly—including copying, archiving, and fast enumeration. While other ``NSPointerFunctions`` options are used for certain configurations, such as to hold arbitrary pointers, not all combinations of the options are valid. With some combinations the hash table may not work correctly, or may not even be initialized correctly.
///
/// ### Subclassing Notes
///
/// `NSHashTable` is not suitable for subclassing.
API_AVAILABLE(macos(10.5), ios(6.0), watchos(2.0), tvos(9.0))
@interface NSHashTable<ObjectType> : NSObject <NSCopying, NSSecureCoding, NSFastEnumeration>

/// Returns a hash table initialized with the given attributes.
///
/// - Parameter options: A bit field that specifies the options for the elements in the hash table.
/// - Parameter initialCapacity: The initial number of elements the hash table can hold.
- (instancetype)initWithOptions:(NSPointerFunctionsOptions)options capacity:(NSUInteger)initialCapacity NS_DESIGNATED_INITIALIZER;
/// Returns a hash table initialized with the given functions and capacity.
///
/// Hash tables allocate additional memory as needed, so `initialCapacity` simply establishes the object's initial capacity.
///
/// - Parameter functions: The pointer functions for the new hash table.
/// - Parameter initialCapacity: The initial capacity of the hash table.
- (instancetype)initWithPointerFunctions:(NSPointerFunctions *)functions capacity:(NSUInteger)initialCapacity NS_DESIGNATED_INITIALIZER;

// conveniences

/// Returns a hash table with given pointer functions options.
///
/// - Parameter options: A bit field that specifies the options for the elements in the hash table.
/// - Returns: A hash table with given pointer functions options.
+ (NSHashTable<ObjectType> *)hashTableWithOptions:(NSPointerFunctionsOptions)options;

/// Returns a new hash table for storing weak references to its contents.
///
/// @DeprecationSummary Use ``weakObjectsHashTable`` instead.
///
/// This method is not supported under Automatic Reference Counting (ARC).
+ (id)hashTableWithWeakObjects API_DEPRECATED("GC no longer supported", macos(10.5,10.8)) API_UNAVAILABLE(ios, watchos, tvos);  // GC zeroing, otherwise unsafe unretained

/// Returns a new hash table for storing weak references to its contents.
+ (NSHashTable<ObjectType> *)weakObjectsHashTable API_AVAILABLE(macos(10.8), ios(6.0), watchos(2.0), tvos(9.0)); // entries are not necessarily purged right away when the weak object is reclaimed


/// The pointer functions for the hash table.
@property (readonly, copy) NSPointerFunctions *pointerFunctions;

/// The number of elements in the hash table.
@property (readonly) NSUInteger count;
/// Determines whether the hash table contains a given object, and returns that object if it is present.
///
/// - Parameter object: The object to test for membership in the hash table.
/// - Returns: If `object` is a member of the hash table, returns `object`, otherwise returns `nil`.
- (nullable ObjectType)member:(nullable ObjectType)object;
/// Returns an enumerator object that lets you access each object in the hash table.
///
/// It is more efficient to use the fast enumeration protocol (see `NSFastEnumeration`).
///
/// - Returns: An enumerator object that lets you access each object in the hash table.
- (NSEnumerator<ObjectType> *)objectEnumerator;

/// Adds a given object to the hash table.
///
/// - Parameter object: The object to add to the hash table.
- (void)addObject:(nullable ObjectType)object;
/// Removes a given object from the hash table.
///
/// - Parameter object: The object to remove from the hash table.
- (void)removeObject:(nullable ObjectType)object;

/// Removes all objects from the hash table.
- (void)removeAllObjects;

/// The hash table's members.
@property (readonly, copy) NSArray<ObjectType> *allObjects;    // convenience

/// One of the objects in the hash table.
///
/// One of the objects in the hash table, or `nil` if the hash table contains no objects.
/// The object returned is chosen at the hash table's convenience -- the selection is not guaranteed to be random.
@property (nullable, nonatomic, readonly) ObjectType anyObject;
/// Returns a Boolean value that indicates whether the hash table contains a given object.
///
/// - Parameter anObject: The object to test for membership in the hash table.
/// - Returns: `YES` if the hash table contains `anObject`, otherwise `NO`.
- (BOOL)containsObject:(nullable ObjectType)anObject;

/// Returns a Boolean value that indicates whether a given hash table intersects with the receiving hash table.
///
/// - Parameter other: The hash table with which to compare the receiving hash table.
/// - Returns: `YES` if `other` intersects with the receiving hash table, otherwise `NO`.
- (BOOL)intersectsHashTable:(NSHashTable<ObjectType> *)other;
/// Returns a Boolean value that indicates whether a given hash table is equal to the receiving hash table.
///
/// Two hash tables have equal contents if they each have the same number of members and if each member of one hash table is present in the other.
///
/// - Parameter other: The hash table with which to compare the receiving hash table.
/// - Returns: `YES` if the contents of `other` are equal to the contents of the receiving hash table, otherwise `NO`.
- (BOOL)isEqualToHashTable:(NSHashTable<ObjectType> *)other;
/// Returns a Boolean value that indicates whether every element in the receiving hash table is also present in another given hash table.
///
/// - Parameter other: The hash table with which to compare the receiving hash table.
/// - Returns: `YES` if every element in the receiving hash table is also present in `other`, otherwise `NO`.
- (BOOL)isSubsetOfHashTable:(NSHashTable<ObjectType> *)other;

/// Removes from the receiving hash table each element that isn't a member of another given hash table.
///
/// - Parameter other: The hash table with which to perform the intersection.
- (void)intersectHashTable:(NSHashTable<ObjectType> *)other;
/// Adds each element in another given hash table to the receiving hash table, if not present.
///
/// - Parameter other: The hash table of elements to add to the receiving hash table.
- (void)unionHashTable:(NSHashTable<ObjectType> *)other;
/// Removes each element in another given hash table from the receiving hash table, if present.
///
/// - Parameter other: The hash table of elements to remove from the receiving hash table.
- (void)minusHashTable:(NSHashTable<ObjectType> *)other;

/// A set that contains the hash table's members.
@property (readonly, copy) NSSet<ObjectType> *setRepresentation;  // create a set of the contents

@end

/* ***************	(void *) Hash table operations	****************/

typedef struct {NSUInteger _pi; NSUInteger _si; void * _Nullable _bs;} NSHashEnumerator;

/// Frees a hash table.
FOUNDATION_EXPORT void NSFreeHashTable(NSHashTable *table);
/// Deletes the elements from a hash table, without freeing the table itself.
FOUNDATION_EXPORT void NSResetHashTable(NSHashTable *table);
/// Returns a Boolean value that indicates whether two hash tables are equal.
FOUNDATION_EXPORT BOOL NSCompareHashTables(NSHashTable *table1, NSHashTable *table2);
/// Returns a copy of a hash table.
FOUNDATION_EXPORT NSHashTable *NSCopyHashTableWithZone(NSHashTable *table, NSZone * _Nullable zone);
/// Returns an element of the hash table.
FOUNDATION_EXPORT void *NSHashGet(NSHashTable *table, const void * _Nullable pointer);
/// Adds an element to the hash table.
FOUNDATION_EXPORT void NSHashInsert(NSHashTable *table, const void * _Nullable pointer);
/// Adds an element to the hash table, raising an exception if the element is already present.
FOUNDATION_EXPORT void NSHashInsertKnownAbsent(NSHashTable *table, const void * _Nullable pointer);
/// Adds an element to the hash table if it is not already present, and returns the element.
FOUNDATION_EXPORT void * _Nullable NSHashInsertIfAbsent(NSHashTable *table, const void * _Nullable pointer);
/// Removes an element from the hash table.
FOUNDATION_EXPORT void NSHashRemove(NSHashTable *table, const void * _Nullable pointer);
/// Returns an enumerator for a hash table.
FOUNDATION_EXPORT NSHashEnumerator NSEnumerateHashTable(NSHashTable *table);
/// Returns the next element in the hash table enumeration.
FOUNDATION_EXPORT void * _Nullable NSNextHashEnumeratorItem(NSHashEnumerator *enumerator);
/// Frees an enumerator for a hash table.
FOUNDATION_EXPORT void NSEndHashTableEnumeration(NSHashEnumerator *enumerator);
/// Returns the number of elements in a hash table.
FOUNDATION_EXPORT NSUInteger NSCountHashTable(NSHashTable *table);
/// Returns a string describing the hash table's contents.
FOUNDATION_EXPORT NSString *NSStringFromHashTable(NSHashTable *table);
/// Returns all of the elements in a hash table.
FOUNDATION_EXPORT NSArray *NSAllHashTableObjects(NSHashTable *table);


/* ***************	Legacy	****************/

typedef struct {
    /// Points to the function that must produce hash code for elements of the hash table. If `NULL`, the pointer value is used as the hash code. Second parameter is the element for which hash code should be produced.
    NSUInteger	(* _Nullable hash)(NSHashTable *table, const void *);
    /// Points to the function that compares second and third parameters. If `NULL`, then == is used for comparison.
    BOOL	(* _Nullable isEqual)(NSHashTable *table, const void *, const void *);
    /// Points to the function that increments a reference count for the given element. If `NULL`, then nothing is done for reference counting.
    void	(* _Nullable retain)(NSHashTable *table, const void *);
    /// Points to the function that decrements a reference count for the given element, and if the reference count becomes 0, frees the given element. If `NULL`, then nothing is done for reference counting or releasing.
    void	(* _Nullable release)(NSHashTable *table, void *);
    /// Points to the function that produces an autoreleased NSString describing the given element. If `NULL`, then the hash table produces a generic string description.
    NSString 	* _Nullable (* _Nullable describe)(NSHashTable *table, const void *);
} NSHashTableCallBacks;

/// Creates a new hash table in a given zone.
///
/// The table's size is dependent on (but generally not equal to) `capacity`. If `capacity` is 0, a small hash table is created. The `NSHashTableCallBacks` structure `callBacks` has five pointers to functions, with the following defaults: pointer hashing, if `hash` is `NULL`; pointer equality, if `isEqual` is `NULL`; no callback upon adding an element, if `retain` is `NULL`; no callback upon removing an element, if `release` is `NULL`; and a function returning a pointer's hexadecimal value as a string, if `describe` is `NULL`. The hashing function must be defined such that if two data elements are equal, as defined by the comparison function, the values produced by hashing on these elements must also be equal. Also, data elements must remain invariant if the value of the hashing function depends on them; for example, if the hashing function operates directly on the characters of a string, that string can't change.
///
/// - Parameters:
///   - callBacks: A structure that defines the callbacks for the hash table.
///   - capacity: The initial capacity of the hash table.
///   - zone: The zone in which to create the hash table. If `NULL`, the hash table is created in the default zone.
/// - Returns: A pointer to a new hash table created in the specified zone. If `zone` is `NULL`, the hash table is created in the default zone.
FOUNDATION_EXPORT NSHashTable *NSCreateHashTableWithZone(NSHashTableCallBacks callBacks, NSUInteger capacity, NSZone * _Nullable zone);
/// Creates and returns a new hash table.
///
/// The table's size is dependent on (but generally not equal to) `capacity`. If `capacity` is 0, a small hash table is created. The `NSHashTableCallBacks` structure `callBacks` has five pointers to functions, with the following defaults: pointer hashing, if `hash` is `NULL`; pointer equality, if `isEqual` is `NULL`; no callback upon adding an element, if `retain` is `NULL`; no callback upon removing an element, if `release` is `NULL`; and a function returning a pointer's hexadecimal value as a string, if `describe` is `NULL`. The hashing function must be defined such that if two data elements are equal, as defined by the comparison function, the values produced by hashing on these elements must also be equal. Also, data elements must remain invariant if the value of the hashing function depends on them; for example, if the hashing function operates directly on the characters of a string, that string can't change.
///
/// - Parameters:
///   - callBacks: A structure that defines the callbacks for the hash table.
///   - capacity: The initial capacity of the hash table.
/// - Returns: A pointer to an `NSHashTable` created in the default zone.
FOUNDATION_EXPORT NSHashTable *NSCreateHashTable(NSHashTableCallBacks callBacks, NSUInteger capacity);


FOUNDATION_EXPORT const NSHashTableCallBacks NSIntegerHashCallBacks API_AVAILABLE(macos(10.5)) API_UNAVAILABLE(ios, watchos, tvos);
FOUNDATION_EXPORT const NSHashTableCallBacks NSNonOwnedPointerHashCallBacks;
FOUNDATION_EXPORT const NSHashTableCallBacks NSNonRetainedObjectHashCallBacks;
FOUNDATION_EXPORT const NSHashTableCallBacks NSObjectHashCallBacks;
FOUNDATION_EXPORT const NSHashTableCallBacks NSOwnedObjectIdentityHashCallBacks;
FOUNDATION_EXPORT const NSHashTableCallBacks NSOwnedPointerHashCallBacks;
FOUNDATION_EXPORT const NSHashTableCallBacks NSPointerToStructHashCallBacks;
FOUNDATION_EXPORT const NSHashTableCallBacks NSIntHashCallBacks API_DEPRECATED("Not supported", macos(10.0,10.5)) API_UNAVAILABLE(ios, watchos, tvos);

NS_HEADER_AUDIT_END(nullability, sendability)
#endif // defined __FOUNDATION_NSHASHTABLE__
