/*	NSZone.h
	Copyright (c) 1994-2019, Apple Inc. All rights reserved.
*/

#import <Foundation/NSObjCRuntime.h>
#include <CoreFoundation/CFBase.h>
#include <stddef.h>

@class NSString;

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

/// A type used to identify and manage memory zones.
typedef struct _NSZone NSZone;

/// Returns the default zone.
FOUNDATION_EXPORT NSZone *NSDefaultMallocZone(void) NS_SWIFT_UNAVAILABLE("Zone-based memory management is unavailable");
/// Creates a new zone.
FOUNDATION_EXPORT NSZone *NSCreateZone(NSUInteger startSize, NSUInteger granularity, BOOL canFree) NS_SWIFT_UNAVAILABLE("Zone-based memory management is unavailable");
/// Frees a zone after first deallocating all of its memory.
FOUNDATION_EXPORT void NSRecycleZone(NSZone *zone)NS_SWIFT_UNAVAILABLE("Zone-based memory management is unavailable");

/// Sets the name of a zone.
FOUNDATION_EXPORT void NSSetZoneName(NSZone * _Nullable zone, NSString *name)NS_SWIFT_UNAVAILABLE("Zone-based memory management is unavailable");
/// Returns the name of a zone.
FOUNDATION_EXPORT NSString *NSZoneName(NSZone * _Nullable zone) NS_SWIFT_UNAVAILABLE("Zone-based memory management is unavailable");
/// Returns the zone for a given pointer.
FOUNDATION_EXPORT NSZone * _Nullable NSZoneFromPointer(void *ptr) NS_SWIFT_UNAVAILABLE("Zone-based memory management is unavailable");

/// Allocates memory in a zone.
FOUNDATION_EXPORT void *NSZoneMalloc(NSZone * _Nullable zone, NSUInteger size) NS_SWIFT_UNAVAILABLE("Zone-based memory management is unavailable");
/// Allocates zeroed memory in a zone.
FOUNDATION_EXPORT void *NSZoneCalloc(NSZone * _Nullable zone, NSUInteger numElems, NSUInteger byteSize) NS_SWIFT_UNAVAILABLE("Zone-based memory management is unavailable");
/// Resizes memory in a zone.
FOUNDATION_EXPORT void *NSZoneRealloc(NSZone * _Nullable zone, void * _Nullable ptr, NSUInteger size) NS_SWIFT_UNAVAILABLE("Zone-based memory management is unavailable");
/// Frees memory in a zone.
FOUNDATION_EXPORT void NSZoneFree(NSZone * _Nullable zone, void *ptr) NS_SWIFT_UNAVAILABLE("Zone-based memory management is unavailable");

#if TARGET_OS_OSX

/* Garbage Collected memory allocation. Garbage Collection is deprecated. */

NS_ENUM(NSUInteger) {
/// Constants used to control behavior when allocating or reallocating collectible memory.
    NSScannedOption = (1UL << 0),
    NSCollectorDisabledOption = (1UL << 1),
};

/// Allocates collectable memory.
///
/// @DeprecationSummary { Garbage collection is deprecated in OS X v10.8; instead, you should use Automatic Reference Counting. }
///
/// - Parameters:
///   - size: The number of bytes of memory to allocate.
///   - options: `0` or `NSScannedOption`: A value of `0` allocates non-scanned memory; a value of `NSScannedOption` allocates scanned memory.
/// - Returns: A pointer to the allocated memory, or `NULL` if the function is unable to allocate the requested memory.
FOUNDATION_EXPORT void *NSAllocateCollectable(NSUInteger size, NSUInteger options) NS_SWIFT_UNAVAILABLE("Garbage Collection is not supported");
/// Reallocates collectable memory.
///
/// @DeprecationSummary { Garbage collection is deprecated in OS X v10.8; instead, you should use Automatic Reference Counting. }
///
/// Changes the size of the block of memory pointed to by `ptr` to `size` bytes. It may allocate new memory to replace the old, in which case it moves the contents of the old memory block to the new block, up to a maximum of `size` bytes.
///
/// - Parameters:
///   - ptr: A pointer to the previously allocated memory block.
///   - size: The new number of bytes of memory to allocate.
///   - options: `0` or `NSScannedOption`: A value of `0` allocates non-scanned memory; a value of `NSScannedOption` allocates scanned memory.
/// - Returns: A pointer to the reallocated memory, or `NULL` if the function is unable to allocate the requested memory.
FOUNDATION_EXPORT void *NSReallocateCollectable(void * _Nullable ptr, NSUInteger size, NSUInteger options) NS_SWIFT_UNAVAILABLE("Garbage Collection is not supported");

#endif

#ifndef CF_CONSUMED
#if __has_feature(attribute_cf_consumed)
#define CF_CONSUMED __attribute__((cf_consumed))
#else
#define CF_CONSUMED
#endif
#endif

/// Makes a newly allocated Core Foundation object eligible for collection.
///
/// @DeprecationSummary { Garbage collection is deprecated in OS X v10.8; instead, you should use Automatic Reference Counting. Use `CFBridgingRelease` instead. }
///
/// This function is a wrapper for `CFMakeCollectable`, but its return type is `id`—avoiding the need for casting when using Cocoa objects.
///
/// This function may be useful when returning Core Foundation objects in code that must support both garbage-collected and non-garbage-collected environments, as illustrated in the following example.
///
/// ```objc
/// - (CFDateRef)foo {
///     CFDateRef aCFDate;
///     // ...
///     return [NSMakeCollectable(aCFDate) autorelease];
/// }
/// ```
///
/// `CFTypeRef` style objects are garbage collected, yet only sometime after the last `CFRelease` is performed. Particularly for fully-bridged `CFTypeRef` objects such as CFStrings and collections (such as CFDictionary), you must call either `CFMakeCollectable` or the more type safe `NSMakeCollectable`, preferably right upon allocation.
NS_INLINE NS_RETURNS_RETAINED id _Nullable NSMakeCollectable(CFTypeRef _Nullable CF_CONSUMED cf) NS_AUTOMATED_REFCOUNT_UNAVAILABLE NS_SWIFT_UNAVAILABLE("Garbage Collection is not supported");
NS_INLINE NS_RETURNS_RETAINED id _Nullable NSMakeCollectable(CFTypeRef _Nullable CF_CONSUMED cf) {
#if __has_feature(objc_arc)
    return nil;
#else
    return (id)cf;
#endif
}

/// Returns the page size.
FOUNDATION_EXPORT NSUInteger NSPageSize(void);
/// Returns the binary log of the page size.
FOUNDATION_EXPORT NSUInteger NSLogPageSize(void);
/// Rounds up a value to the nearest multiple of the page size.
FOUNDATION_EXPORT NSUInteger NSRoundUpToMultipleOfPageSize(NSUInteger bytes);
/// Rounds down a value to the nearest multiple of the page size.
FOUNDATION_EXPORT NSUInteger NSRoundDownToMultipleOfPageSize(NSUInteger bytes);
/// Allocates a given number of bytes of virtual memory.
FOUNDATION_EXPORT void *NSAllocateMemoryPages(NSUInteger bytes);
/// Deallocates the memory occupied by a given number of bytes.
FOUNDATION_EXPORT void NSDeallocateMemoryPages(void *ptr, NSUInteger bytes);
/// Copies a given number of bytes from one memory location to another.
FOUNDATION_EXPORT void NSCopyMemoryPages(const void *source, void *dest, NSUInteger bytes);
#if !0
FOUNDATION_EXPORT NSUInteger NSRealMemoryAvailable(void) API_DEPRECATED("Use NSProcessInfo instead", macos(10.0,10.8), ios(2.0,6.0), watchos(2.0,2.0), tvos(9.0,9.0)); // see NSProcessInfo.h instead
#endif

NS_HEADER_AUDIT_END(nullability, sendability)
