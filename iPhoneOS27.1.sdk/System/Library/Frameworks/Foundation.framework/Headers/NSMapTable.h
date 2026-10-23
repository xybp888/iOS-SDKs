/*	NSMapTable.h
	Copyright (c) 1994-2019, Apple Inc. All rights reserved.
*/

#import <Foundation/NSPointerFunctions.h>
#import <Foundation/NSString.h>
#import <Foundation/NSEnumerator.h>

#if !defined(__FOUNDATION_NSMAPTABLE__)
#define __FOUNDATION_NSMAPTABLE__ 1

@class NSArray, NSDictionary<KeyType, ObjectType>, NSMapTable;

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

/* ***************	Class	****************/

/* An NSMapTable is modeled after a dictionary, although, because of its options, is not a dictionary because it will behave differently.  The major option is to have keys and/or values held "weakly" in a manner that entries will be removed at some indefinite point after one of the objects is reclaimed.  In addition to being held weakly, keys or values may be copied on input or may use pointer identity for equality and hashing.
   An NSMapTable can also be configured to operate on arbitrary pointers and not just objects.  We recommend the C function API for "void *" access.  To configure for pointer use, consult and choose the appropriate NSPointerFunction options or configure and use  NSPointerFunctions objects directly for initialization.
*/

static const NSPointerFunctionsOptions NSMapTableStrongMemory API_AVAILABLE(macos(10.5), ios(6.0), watchos(2.0), tvos(9.0)) = NSPointerFunctionsStrongMemory;
static const NSPointerFunctionsOptions NSMapTableZeroingWeakMemory API_DEPRECATED("GC no longer supported", macos(10.5,10.8)) API_UNAVAILABLE(ios, watchos, tvos) = NSPointerFunctionsZeroingWeakMemory;
static const NSPointerFunctionsOptions NSMapTableCopyIn API_AVAILABLE(macos(10.5), ios(6.0), watchos(2.0), tvos(9.0)) = NSPointerFunctionsCopyIn;
static const NSPointerFunctionsOptions NSMapTableObjectPointerPersonality API_AVAILABLE(macos(10.5), ios(6.0), watchos(2.0), tvos(9.0)) = NSPointerFunctionsObjectPointerPersonality;
static const NSPointerFunctionsOptions NSMapTableWeakMemory API_AVAILABLE(macos(10.8), ios(6.0), watchos(2.0), tvos(9.0)) = NSPointerFunctionsWeakMemory;

/// Constants used as components in a bitfield to specify the behavior of elements (keys and values) in an `NSMapTable` object.
typedef NSUInteger NSMapTableOptions;

/// A collection similar to a dictionary, but with a broader range of available memory semantics.
///
/// The map table is modeled after ``NSDictionary`` with the following differences:
///
/// - Keys and/or values are optionally held "weakly" such that entries are removed when one of the objects is reclaimed.
/// - Its keys or values may be copied on input or may use pointer identity for equality and hashing.
/// - It can contain arbitrary pointers (its contents are not constrained to being objects).
///
/// You can configure an ``NSMapTable`` instance to operate on arbitrary pointers and not just objects, although typically you are encouraged to use the C function API for void \* pointers. The object-based API (such as ``setObject(_:forKey:)``) will not work for non-object pointers without type-casting.
///
/// When configuring map tables, note that only the options listed in ``NSMapTableOptions`` guarantee that the rest of the API will work correctly—including copying, archiving, and fast enumeration. While other ``NSPointerFunctions`` options are used for certain configurations, such as to hold arbitrary pointers, not all combinations of the options are valid. With some combinations the map table may not work correctly, or may not even be initialized correctly.
///
/// ### Subclassing Notes
///
/// `NSMapTable` is not suitable for subclassing.
API_AVAILABLE(macos(10.5), ios(6.0), watchos(2.0), tvos(9.0))
@interface NSMapTable<KeyType, ObjectType> : NSObject <NSCopying, NSSecureCoding, NSFastEnumeration>

/// Returns a map table, initialized with the given options.
///
/// - Parameter keyOptions: A bit field that specifies the options for the keys in the map table.
/// - Parameter valueOptions: A bit field that specifies the options for the values in the map table.
/// - Parameter initialCapacity: The initial capacity of the map table. This is just a hint; the map table may subsequently grow and shrink as required.
- (instancetype)initWithKeyOptions:(NSPointerFunctionsOptions)keyOptions valueOptions:(NSPointerFunctionsOptions)valueOptions capacity:(NSUInteger)initialCapacity NS_DESIGNATED_INITIALIZER;
/// Returns a map table, initialized with the given functions.
///
/// - Parameter keyFunctions: The functions the map table uses to manage keys.
/// - Parameter valueFunctions: The functions the map table uses to manage values.
/// - Parameter initialCapacity: The initial capacity of the map table. This is just a hint; the map table may subsequently grow and shrink as required.
- (instancetype)initWithKeyPointerFunctions:(NSPointerFunctions *)keyFunctions valuePointerFunctions:(NSPointerFunctions *)valueFunctions capacity:(NSUInteger)initialCapacity NS_DESIGNATED_INITIALIZER;

/// Returns a new map table, initialized with the given options.
///
/// - Parameter keyOptions: A bit field that specifies the options for the keys in the map table.
/// - Parameter valueOptions: A bit field that specifies the options for the values in the map table.
/// - Returns: A new map table, initialized with the given options.
+ (NSMapTable<KeyType, ObjectType> *)mapTableWithKeyOptions:(NSPointerFunctionsOptions)keyOptions valueOptions:(NSPointerFunctionsOptions)valueOptions;

/// Returns a new map table object which has strong references to the keys and values.
///
/// @DeprecationSummary Use ``strongToStrongObjectsMapTable`` instead.
+ (id)mapTableWithStrongToStrongObjects API_DEPRECATED("GC no longer supported", macos(10.5,10.8)) API_UNAVAILABLE(ios, watchos, tvos);
/// Returns a new map table object which has weak references to the keys and strong references to the values.
///
/// @DeprecationSummary Use ``weakToStrongObjectsMapTable`` instead.
///
/// `NSMapTable` objects created using this method do not support weak references under Automatic Reference Counting (ARC).
+ (id)mapTableWithWeakToStrongObjects API_DEPRECATED("GC no longer supported", macos(10.5,10.8)) API_UNAVAILABLE(ios, watchos, tvos);
/// Returns a new map table object which has strong references to the keys and weak references to the values.
///
/// @DeprecationSummary Use ``strongToWeakObjectsMapTable`` instead.
///
/// `NSMapTable` objects created using this method do not support weak references under Automatic Reference Counting (ARC).
+ (id)mapTableWithStrongToWeakObjects API_DEPRECATED("GC no longer supported", macos(10.5,10.8)) API_UNAVAILABLE(ios, watchos, tvos);
/// Returns a new map table object which has weak references to the keys and values.
///
/// @DeprecationSummary Use ``weakToWeakObjectsMapTable`` instead.
///
/// `NSMapTable` objects created using this method do not support weak references under Automatic Reference Counting (ARC).
+ (id)mapTableWithWeakToWeakObjects API_DEPRECATED("GC no longer supported", macos(10.5,10.8)) API_UNAVAILABLE(ios, watchos, tvos);


/// Returns a new map table object which has strong references to the keys and values.
+ (NSMapTable<KeyType, ObjectType> *)strongToStrongObjectsMapTable API_AVAILABLE(macos(10.8), ios(6.0), watchos(2.0), tvos(9.0));
/// Returns a new map table object which has weak references to the keys and strong references to the values.
///
/// Use of weak-to-strong map tables is not recommended. The strong values for weak keys which get zeroed out continue to be maintained until the map table resizes itself.
+ (NSMapTable<KeyType, ObjectType> *)weakToStrongObjectsMapTable API_AVAILABLE(macos(10.8), ios(6.0), watchos(2.0), tvos(9.0)); // entries are not necessarily purged right away when the weak key is reclaimed
/// Returns a new map table object which has strong references to the keys and weak references to the values.
+ (NSMapTable<KeyType, ObjectType> *)strongToWeakObjectsMapTable API_AVAILABLE(macos(10.8), ios(6.0), watchos(2.0), tvos(9.0));
/// Returns a new map table object which has weak references to the keys and values.
+ (NSMapTable<KeyType, ObjectType> *)weakToWeakObjectsMapTable API_AVAILABLE(macos(10.8), ios(6.0), watchos(2.0), tvos(9.0)); // entries are not necessarily purged right away when the weak key or object is reclaimed

/// The pointer functions the map table uses to manage keys.
@property (readonly, copy) NSPointerFunctions *keyPointerFunctions;
/// The pointer functions the map table uses to manage values.
@property (readonly, copy) NSPointerFunctions *valuePointerFunctions;

/// Returns the value associated with a given key.
///
/// - Parameter aKey: The key for which to return the corresponding value.
/// - Returns: The value associated with `aKey`, or `nil` if no value is associated with `aKey`.
- (nullable ObjectType)objectForKey:(nullable KeyType)aKey;

/// Removes a given key and its associated value from the map table.
///
/// Does nothing if `aKey` does not exist.
///
/// - Parameter aKey: The key to remove.
- (void)removeObjectForKey:(nullable KeyType)aKey;
/// Adds a given key-value pair to the map table.
///
/// - Parameter anObject: The value for `aKey`.
/// - Parameter aKey: The key for `anObject`.
- (void)setObject:(nullable ObjectType)anObject forKey:(nullable KeyType)aKey;   // add/replace value (CFDictionarySetValue, NSMapInsert)

/// The number of key-value pairs in the map table.
@property (readonly) NSUInteger count;

/// Returns an enumerator object that lets you access each key in the map table.
///
/// It is more efficient to use the fast enumeration protocol (see `NSFastEnumeration`).
///
/// - Returns: An enumerator object that lets you access each key in the map table.
- (NSEnumerator<KeyType> *)keyEnumerator;
/// Returns an enumerator object that lets you access each value in the map table.
///
/// It is more efficient to use the fast enumeration protocol (see `NSFastEnumeration`).
///
/// - Returns: An enumerator object that lets you access each value in the map table.
- (nullable NSEnumerator<ObjectType> *)objectEnumerator;

/// Empties the map table of its entries.
- (void)removeAllObjects;

/// Returns a dictionary representation of the map table.
///
/// - Returns: A dictionary representation of the map table.
- (NSDictionary<KeyType, ObjectType> *)dictionaryRepresentation;  // create a dictionary of contents
@end


/* ***************	void * Map table operations	****************/

typedef struct {NSUInteger _pi; NSUInteger _si; void * _Nullable _bs;} NSMapEnumerator;



/// Frees a map table.
FOUNDATION_EXPORT void NSFreeMapTable(NSMapTable *NS_RELEASES_ARGUMENT table);
/// Deletes the entries from a map table, without freeing the table itself.
FOUNDATION_EXPORT void NSResetMapTable(NSMapTable *table);
/// Returns a Boolean value that indicates whether two map tables are equal.
FOUNDATION_EXPORT BOOL NSCompareMapTables(NSMapTable *table1, NSMapTable *table2);
/// Returns a copy of a map table.
FOUNDATION_EXPORT NSMapTable *NSCopyMapTableWithZone(NSMapTable *table, NSZone * _Nullable zone) NS_RETURNS_RETAINED;
/// Returns a Boolean value that indicates whether a map table contains a given key.
FOUNDATION_EXPORT BOOL NSMapMember(NSMapTable *table, const void *key, void * _Nullable * _Nullable originalKey, void * _Nullable * _Nullable value);
/// Returns the value associated with a given key in a map table.
FOUNDATION_EXPORT void * _Nullable NSMapGet(NSMapTable *table, const void * _Nullable key);
/// Inserts a key-value pair into a map table.
FOUNDATION_EXPORT void NSMapInsert(NSMapTable *table, const void * _Nullable key, const void * _Nullable value);
/// Inserts a key-value pair into a map table if the key does not already exist.
FOUNDATION_EXPORT void NSMapInsertKnownAbsent(NSMapTable *table, const void * _Nullable key, const void * _Nullable value);
/// Inserts a key-value pair into a map table if the key does not already exist, and returns the value.
FOUNDATION_EXPORT void * _Nullable NSMapInsertIfAbsent(NSMapTable *table, const void * _Nullable key, const void * _Nullable value);
/// Removes a key and its associated value from a map table.
FOUNDATION_EXPORT void NSMapRemove(NSMapTable *table, const void * _Nullable key);
/// Returns an enumerator for a map table.
FOUNDATION_EXPORT NSMapEnumerator NSEnumerateMapTable(NSMapTable *table);
/// Returns the next key-value pair in the enumeration.
FOUNDATION_EXPORT BOOL NSNextMapEnumeratorPair(NSMapEnumerator *enumerator, void * _Nullable * _Nullable key, void * _Nullable * _Nullable value);
/// Frees an enumerator for a map table.
FOUNDATION_EXPORT void NSEndMapTableEnumeration(NSMapEnumerator *enumerator);
/// Returns the number of entries in a map table.
FOUNDATION_EXPORT NSUInteger NSCountMapTable(NSMapTable *table);
/// Returns a string describing the map table's contents.
FOUNDATION_EXPORT NSString *NSStringFromMapTable(NSMapTable *table);
/// Returns all of the keys in a map table.
FOUNDATION_EXPORT NSArray *NSAllMapTableKeys(NSMapTable *table);
/// Returns all of the values in a map table.
FOUNDATION_EXPORT NSArray *NSAllMapTableValues(NSMapTable *table);


/* ***************     Legacy     ***************************************/

typedef struct {
    /// Points to the function which must produce hash code for key elements of the map table. If `NULL`, the pointer value is used as the hash code. Second parameter is the element for which hash code should be produced.
    NSUInteger	(* _Nullable hash)(NSMapTable *table, const void *);
    /// Points to the function which compares second and third parameters. If `NULL`, then == is used for comparison.
    BOOL	(* _Nullable isEqual)(NSMapTable *table, const void *, const void *);
    /// Points to the function which increments a reference count for the given element. If `NULL`, then nothing is done for reference counting.
    void	(* _Nullable retain)(NSMapTable *table, const void *);
    /// Points to the function which decrements a reference count for the given element, and if the reference count becomes zero, frees the given element. If `NULL`, then nothing is done for reference counting or releasing.
    void	(* _Nullable release)(NSMapTable *table, void *);
    /// Points to the function which produces an autoreleased NSString describing the given element. If `NULL`, then the map table produces a generic string description.
    NSString 	* _Nullable (* _Nullable describe)(NSMapTable *table, const void *);
    /// No key put in map table can be this value. An exception is raised if attempt is made to use this value as a key.
    const void	* _Nullable notAKeyMarker;
} NSMapTableKeyCallBacks;
    
/// Predefined `notAKeyMarker` for use with ``NSMapTableKeyCallBacks``.
///
/// @Deprecated Use ``NSNotAnIntegerMapKey`` instead.
#define NSNotAnIntMapKey	((const void *)NSIntegerMin)
/// Predefined `notAKeyMarker` for use with ``NSMapTableKeyCallBacks``.
#define NSNotAnIntegerMapKey	((const void *)NSIntegerMin)
/// Predefined `notAKeyMarker` for use with ``NSMapTableKeyCallBacks``.
#define NSNotAPointerMapKey	((const void *)UINTPTR_MAX)

/// The function pointers used to configure behavior of `NSMapTable` with respect to value elements within a map table.
///
/// All functions must know the types of things in the map table to be able to operate on them. Sets of predefined call backs are described in ``NSMapTable``.
typedef struct {
    /// Points to the function that increments a reference count for the given element. If `NULL`, then nothing is done for reference counting.
    void	(* _Nullable retain)(NSMapTable *table, const void *);
    /// Points to the function that decrements a reference count for the given element, and if the reference count becomes zero, frees the given element. If `NULL`, then nothing is done for reference counting or releasing.
    void	(* _Nullable release)(NSMapTable *table, void *);
    /// Points to the function that produces an autoreleased NSString describing the given element. If `NULL`, then the map table produces a generic string description.
    NSString 	* _Nullable(* _Nullable describe)(NSMapTable *table, const void *);
} NSMapTableValueCallBacks;

/// Creates a new map table in the specified zone.
///
/// The table's size is dependent on (but generally not equal to) `capacity`. If `capacity` is 0, a small map table is created. The `NSMapTableKeyCallBacks` arguments are structures that are very similar to the callback structure used by `NSCreateHashTable`; in fact, they have the same defaults as documented for that function.
///
/// - Parameters:
///   - keyCallBacks: The key callback structure for the map table.
///   - valueCallBacks: The value callback structure for the map table.
///   - capacity: The initial capacity of the map table.
///   - zone: The zone in which to create the map table. If `NULL`, the map table is created in the default zone.
/// - Returns: A new map table allocated in `zone`. If `zone` is `NULL`, the map table is created in the default zone.
FOUNDATION_EXPORT NSMapTable *NSCreateMapTableWithZone(NSMapTableKeyCallBacks keyCallBacks, NSMapTableValueCallBacks valueCallBacks, NSUInteger capacity, NSZone * _Nullable zone) NS_RETURNS_RETAINED;
/// Creates a new map table in the default zone.
///
/// The table's size is dependent on (but generally not equal to) `capacity`. If `capacity` is 0, a small map table is created. The `NSMapTableKeyCallBacks` arguments are structures that are very similar to the callback structure used by `NSCreateHashTable`—they have the same defaults as documented for that function.
///
/// - Parameters:
///   - keyCallBacks: The key callback structure for the map table.
///   - valueCallBacks: The value callback structure for the map table.
///   - capacity: The initial capacity of the map table.
FOUNDATION_EXPORT NSMapTable *NSCreateMapTable(NSMapTableKeyCallBacks keyCallBacks, NSMapTableValueCallBacks valueCallBacks, NSUInteger capacity) NS_RETURNS_RETAINED;


/* ***************	Common map table key callbacks	****************/

FOUNDATION_EXPORT const NSMapTableKeyCallBacks NSIntegerMapKeyCallBacks API_AVAILABLE(macos(10.5)) API_UNAVAILABLE(ios, watchos, tvos);
FOUNDATION_EXPORT const NSMapTableKeyCallBacks NSNonOwnedPointerMapKeyCallBacks;
FOUNDATION_EXPORT const NSMapTableKeyCallBacks NSNonOwnedPointerOrNullMapKeyCallBacks;
FOUNDATION_EXPORT const NSMapTableKeyCallBacks NSNonRetainedObjectMapKeyCallBacks;
FOUNDATION_EXPORT const NSMapTableKeyCallBacks NSObjectMapKeyCallBacks;
FOUNDATION_EXPORT const NSMapTableKeyCallBacks NSOwnedPointerMapKeyCallBacks;
FOUNDATION_EXPORT const NSMapTableKeyCallBacks NSIntMapKeyCallBacks API_DEPRECATED("Not supported", macos(10.0,10.5), ios(2.0, 2.0), watchos(2.0, 2.0), tvos(9.0, 9.0));

/* ***************	Common map table value callbacks	****************/

FOUNDATION_EXPORT const NSMapTableValueCallBacks NSIntegerMapValueCallBacks API_AVAILABLE(macos(10.5)) API_UNAVAILABLE(ios, watchos, tvos);
FOUNDATION_EXPORT const NSMapTableValueCallBacks NSNonOwnedPointerMapValueCallBacks;
FOUNDATION_EXPORT const NSMapTableValueCallBacks NSObjectMapValueCallBacks;
FOUNDATION_EXPORT const NSMapTableValueCallBacks NSNonRetainedObjectMapValueCallBacks;
FOUNDATION_EXPORT const NSMapTableValueCallBacks NSOwnedPointerMapValueCallBacks;
FOUNDATION_EXPORT const NSMapTableValueCallBacks NSIntMapValueCallBacks API_DEPRECATED("Not supported", macos(10.0,10.5), ios(2.0, 2.0), watchos(2.0, 2.0), tvos(9.0, 9.0));

NS_HEADER_AUDIT_END(nullability, sendability)
#endif // defined __FOUNDATION_NSMAPTABLE__
