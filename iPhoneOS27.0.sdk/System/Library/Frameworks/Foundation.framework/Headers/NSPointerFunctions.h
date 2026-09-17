/*
 *  NSPointerFunctions.h
 *
 *  Copyright (c) 2005-2019, Apple Inc. All rights reserved.
 *
 */
 

#import <Foundation/NSObject.h>

#if !defined(__FOUNDATION_NSPOINTERFUNCTIONS__)
#define __FOUNDATION_NSPOINTERFUNCTIONS__ 1

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

/*

  NSPointerFunctions

  This object defines callout functions appropriate for managing a pointer reference held somewhere else.

  Used by NSHashTable, NSMapTable, and NSPointerArray, this object defines the acquision and retention behavior for the pointers provided to these collection objects.

   The functions are separated into two clusters - those that define "personality", such as object or cString, and those that describe memory management issues such as a memory deallocation function.  Common personalities and memory manager selections are provided as enumerations, and further customization is provided by methods such that the composition of the actual list of functions is done opaquely such that they can be extended in the future.

  The pointer collections copy NSPointerFunctions objects on input and output, and so NSPointerFunctions is not usefully subclassed.

*/


/// Defines the memory and personality options for an `NSPointerFunctions` object.
///
/// When specifying a value, you can use only one of the options listed in Memory Options, only one of the options listed in Personality Options, and any number of other options.
typedef NS_OPTIONS(NSUInteger, NSPointerFunctionsOptions) {
    // Memory options are mutually exclusive

    /// Use strong write-barriers to backing store; use garbage-collected memory on copy-in.
    ///
    /// This is the default memory value. As a special case, if you do not use garbage collection and specify this value in conjunction with `NSPointerFunctionsObjectPersonality` or `NSPointerFunctionsObjectPointerPersonality` then the `NSPointerFunctions` object uses `retain` and `release`. If you do not use garbage collection, and specify this value in conjunction with a valid non-object personality, it is the same as specifying `NSPointerFunctionsMallocMemory`.
    NSPointerFunctionsStrongMemory API_AVAILABLE(macos(10.5), ios(6.0), watchos(2.0), tvos(9.0)) = (0UL << 0),
    /// Use weak read and write barriers; use garbage-collected memory on copyIn.
    ///
    /// If you do not use garbage collection, for object personalities, it will hold a non-retained object pointer.
    NSPointerFunctionsZeroingWeakMemory API_DEPRECATED("GC no longer supported", macos(10.5, 10.8)) API_UNAVAILABLE(ios, watchos, tvos) = (1UL << 0),
    /// Take no action when pointers are deleted.
    ///
    /// This is usually the preferred memory option for holding arbitrary pointers. The acquire function is only used for copy-in operations. This option is unlikely to be a good choice for objects.
    NSPointerFunctionsOpaqueMemory API_AVAILABLE(macos(10.5), ios(6.0), watchos(2.0), tvos(9.0)) = (2UL << 0),
    /// Use `free()` on removal, `calloc()` on copy in.
    NSPointerFunctionsMallocMemory API_AVAILABLE(macos(10.5), ios(6.0), watchos(2.0), tvos(9.0)) = (3UL << 0),
#if !0
    /// Use Mach memory.
    NSPointerFunctionsMachVirtualMemory API_AVAILABLE(macos(10.5), ios(6.0), watchos(2.0), tvos(9.0)) = (4UL << 0),
#endif
    /// Uses weak read and write barriers appropriate for ARC or GC.
    ///
    /// Using `NSPointerFunctionsWeakMemory` object references will turn to `NULL` on last release.
    NSPointerFunctionsWeakMemory API_AVAILABLE(macos(10.8), ios(6.0), watchos(2.0), tvos(9.0)) = (5UL << 0),

    // Personalities are mutually exclusive
    /// Use `hash` and `isEqual` methods for hashing and equality comparisons, use the `description` method for a description.
    ///
    /// This is the default personality value. As a special case, if you do not use garbage collection and specify this value in conjunction with `NSPointerFunctionsStrongMemory` then the `NSPointerFunctions` object uses `retain` and `release`.
    NSPointerFunctionsObjectPersonality API_AVAILABLE(macos(10.5), ios(6.0), watchos(2.0), tvos(9.0)) = (0UL << 8),
    /// Use shifted pointer for the hash value and direct comparison to determine equality.
    NSPointerFunctionsOpaquePersonality API_AVAILABLE(macos(10.5), ios(6.0), watchos(2.0), tvos(9.0)) = (1UL << 8),
    /// Use shifted pointer for the hash value and direct comparison to determine equality; use the `description` method for a description.
    ///
    /// As a special case, if you do not use garbage collection and specify this value in conjunction with `NSPointerFunctionsStrongMemory` then the `NSPointerFunctions` object uses `retain` and `release`.
    NSPointerFunctionsObjectPointerPersonality API_AVAILABLE(macos(10.5), ios(6.0), watchos(2.0), tvos(9.0)) = (2UL << 8),
    /// Use a string hash and `strcmp`; C-string '`%s`' style description.
    NSPointerFunctionsCStringPersonality API_AVAILABLE(macos(10.5), ios(6.0), watchos(2.0), tvos(9.0)) = (3UL << 8),
    /// Use a memory hash and `memcmp` (using a size function that you must set---see `sizeFunction`).
    NSPointerFunctionsStructPersonality API_AVAILABLE(macos(10.5), ios(6.0), watchos(2.0), tvos(9.0)) = (4UL << 8),
    /// Use unshifted value as hash and equality.
    NSPointerFunctionsIntegerPersonality API_AVAILABLE(macos(10.5), ios(6.0), watchos(2.0), tvos(9.0)) = (5UL << 8),

    /// Use the memory acquire function to allocate and copy items on input (see `acquireFunction`).
    NSPointerFunctionsCopyIn API_AVAILABLE(macos(10.5), ios(6.0), watchos(2.0), tvos(9.0)) = (1UL << 16),
};

/// An instance of `NSPointerFunctions` defines callout functions appropriate for managing a pointer reference held somewhere else.
///
/// The functions specified by an instance of `NSPointerFunctions` are separated into two clusters—those that define "personality" such as "object" or "C-string", and those that describe memory management issues such as a memory deallocation function. There are constants for common personalities and memory manager selections (see `Memory and Personality Options`).
///
/// ``NSHashTable``, ``NSMapTable``, and ``NSPointerArray`` use an `NSPointerFunctions` object to define the acquisition and retention behavior for the pointers they manage. Note, however, that not all combinations of personality and memory management behavior are valid for these collections. The pointer collection objects copy the `NSPointerFunctions` object on input and output, so you cannot usefully subclass `NSPointerFunctions`.
///
/// ### Subclassing Notes
///
/// `NSPointerFunctions` is not suitable for subclassing.
API_AVAILABLE(macos(10.5), ios(6.0), watchos(2.0), tvos(9.0))
@interface NSPointerFunctions : NSObject <NSCopying>
// construction
/// Returns an `NSPointerFunctions` object initialized with the given options.
///
/// - Parameter options: The options for the new `NSPointerFunctions` object.
- (instancetype)initWithOptions:(NSPointerFunctionsOptions)options NS_DESIGNATED_INITIALIZER;
/// Returns a new `NSPointerFunctions` object initialized with the given options.
///
/// - Parameter options: The options for the new `NSPointerFunctions` object.
/// - Returns: A new `NSPointerFunctions` object initialized with the given options.
+ (NSPointerFunctions *)pointerFunctionsWithOptions:(NSPointerFunctionsOptions)options;

// pointer personality functions
/// The hash function.
@property (nullable) NSUInteger (*hashFunction)(const void *item, NSUInteger (* _Nullable size)(const void *item));
/// The function used to compare pointers.
@property (nullable) BOOL (*isEqualFunction)(const void *item1, const void*item2, NSUInteger (* _Nullable size)(const void *item));
/// The function used to determine the size of pointers.
///
/// This function is used for copy-in operations (unless the collection has an object personality).
@property (nullable) NSUInteger (*sizeFunction)(const void *item);
/// The function used to describe elements.
///
/// This function is used by description methods for hash and map tables.
@property (nullable) NSString * _Nullable (*descriptionFunction)(const void *item);

// custom memory configuration
/// The function used to relinquish memory.
///
/// This specifies the function to use when an item is removed from a table or pointer array.
@property (nullable) void (*relinquishFunction)(const void *item, NSUInteger (* _Nullable size)(const void *item));
/// The function used to acquire memory.
///
/// This specifies the function to use for copy-in operations.
@property (nullable) void * _Nonnull (*acquireFunction)(const void *src, NSUInteger (* _Nullable size)(const void *item), BOOL shouldCopy);

// GC used to require that read and write barrier functions be used when pointers are from GC memory
/// Specifies whether, in a garbage collected environment, pointers should be assigned using a strong write barrier.
///
/// If you use garbage collection, read and write barrier functions must be used when pointers are from memory scanned by the collector.
@property BOOL usesStrongWriteBarrier // pointers should (not) be assigned using the GC strong write barrier
    API_DEPRECATED("Garbage collection no longer supported", macosx(10.5, 10.12), ios(2.0,10.0), watchos(2.0,3.0), tvos(9.0,10.0));

/// Specifies whether, in a garbage collected environment, pointers should use weak read and write barriers.
///
/// If you use garbage collection, read and write barrier functions must be used when pointers are from memory scanned by the collector.
@property BOOL usesWeakReadAndWriteBarriers       // pointers should (not) use GC weak read and write barriers
    API_DEPRECATED("Garbage collection no longer supported", macosx(10.5, 10.12), ios(2.0,10.0), watchos(2.0,3.0), tvos(9.0,10.0));
@end

NS_HEADER_AUDIT_END(nullability, sendability)

/*
   Cheat Sheet
 
   Long Integers (other than zero)   (NSPointerFunctionsOpaqueMemory | NSPointerFunctionsIntegerPersonality)
      useful for, well, anything that can be jammed into a long int
 
   Strongly held objects             (NSPointerFunctionsStrongMemory | NSPointerFunctionsObjectPersonality)
      used for retained objects under ARC and/or manual retain-release, or GC; uses isEqual: as necessary
 
   Zeroing weak object references    (NSPointerFunctionsWeakMemory   | NSPointerFunctionsObjectPersonality)
      used to hold references that won't keep the object alive.  Note that objects implementing custom retain-release must also implement allowsWeakReference and retainWeakReference (or are using GC instead)
 
   Unsafe unretained objects         (NSPointerFunctionsOpaqueMemory | NSPointerFunctionsObjectPersonality)
      used where zeroing weak is not possible and where, somehow, the objects are removed before being deallocated.
 
   C String where table keeps copy   (NSPointerFunctionsStrongMemory | NSPointerFunctionsCStringPersonality | NSPointerFunctionsCopyIn)
      used to capture a null-terminated string from a source with unknown lifetime.  Keeps string alive under GC.  Under ARC/RR, table will deallocate its copy when removed.  Generally, "C Strings" is a term for UTF8 strings as well.
 
   C String, owned elsewhere         (NSPointerFunctionsOpaqueMemory | NSPointerFunctionsCStringPersonality)
      used to hold C string pointers to storage not at all managed by the table.
 
 
   The NSPointerFunctionsObjectPersonality dictates using isEqual: for the equality test.  In some situations == should be used, such as when trying to build a cache of unique immutable "value" objects that implement isEqual:.  In those cases use NSPointerFunctionsObjectPointerPersonality instead.

   Deprecated
 
   GC Zeroing - ARC/RR unsafe weak   (NSPointerFunctionsZeroingWeakMemory   | NSPointerFunctionsObjectPersonality)
       under GC these are zeroing weak but under manual retain-release (or ARC) these are unsafe unretained. Move to NSPointerFunctionsWeakMemory or NSPointerFunctionsOpaqueMemory instead.
 
 
   Example
       Lets say you have a source of C Strings that often repeat and you need to provide unique NSString counterparts.  For this you likely want a NSMapTable with strong copy-in C Strings as the keys and weak NSString values.  As long as the NSString counterparts are in use, they stay in the table and don't need to be created each time they show up.
       NSMapTable *mt = [[NSMapTable alloc] 
                            initWithKeyOptions: (NSPointerFunctionsStrongMemory | NSPointerFunctionsCStringPersonality | NSPointerFunctionsCopyIn)
                            valueOptions:(NSPointerFunctionsWeakMemory   | NSPointerFunctionsObjectPersonality)
                            capacity:0];
       ...
       // given a C string, look it up and, if not found, create and save the NSString version in the table
       const char *cString = ...;
       NSString *result = [mt objectForKey:(id)cString];
       if (!result) {
            result = [NSString stringWithCString:cString];
            [mt setObject:result forKey:(id)cString];
        }
        return result;
*/
#endif // defined __FOUNDATION_NSPOINTERFUNCTIONS__

