/*
	NSSortDescriptor.h
	Foundation
	Copyright (c) 2002-2019, Apple Inc. All rights reserved.
*/

#import <Foundation/NSArray.h>
#import <Foundation/NSSet.h>
#import <Foundation/NSOrderedSet.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

/// An immutable description of how to order a collection of objects according to a property common to all the objects.
///
/// You construct instances of ``NSSortDescriptor`` by specifying the key path of the property to compare and the order of the sort (ascending or descending). Optionally, you can also specify a selector to use to perform the comparison, which allows you to specify other comparison selectors, such as ``NSString/localizedStandardCompare(_:)`` and ``NSString/localizedCaseInsensitiveCompare(_:)``. Sorting raises an exception if the objects don't respond to the sort descriptor's comparison selector.
///
/// You can use sort descriptors for the following:
///
/// - Sorting an array (an instance of ``NSArray`` or ``NSMutableArray`` — see ``NSArray/sortedArray(using:)-82wi1`` and ``NSMutableArray/sort(using:)-4eh07``)
/// - Comparing two objects directly (see ``compare(_:to:)``)
/// - Specifying the order of objects that return from a Core Data fetch request (see <doc://com.apple.documentation/documentation/coredata/nsfetchrequest/sortdescriptors>)
@interface NSSortDescriptor : NSObject <NSSecureCoding, NSCopying> {
@private
    NSUInteger _sortDescriptorFlags;
    NSString *_key;
    SEL _selector;
    id _selectorOrBlock;
}

/// Creates and returns a sort descriptor with the specified key path and ordering.
///
/// - Parameters:
///   - key: The key path to use when performing a comparison.
///   - ascending: `YES` if the receiver specifies sorting in ascending order, otherwise `NO`.
/// - Returns: A sort descriptor initialized with the specified key path and sort order, and the default comparison selector (`compare:`).
+ (instancetype)sortDescriptorWithKey:(nullable NSString *)key ascending:(BOOL)ascending API_AVAILABLE(macos(10.6), ios(4.0), watchos(2.0), tvos(9.0));

/// Creates a sort descriptor with the specified key path, ordering, and comparison selector.
///
/// - Parameters:
///   - key: The key path for performing a comparison.
///   - ascending: `YES` if the receiver specifies sorting in ascending order; otherwise, `NO`.
///   - selector: The method to use when comparing the properties of objects. The selector must specify a method implemented by the value of the property identified by the key path. The selector used for the comparison is passed a single parameter, the object to compare against, and it returns the appropriate `NSComparisonResult` constant.
/// - Returns: A sort descriptor initialized with the specified key path, sort order, and comparison selector.
+ (instancetype)sortDescriptorWithKey:(nullable NSString *)key ascending:(BOOL)ascending selector:(nullable SEL)selector API_AVAILABLE(macos(10.6), ios(4.0), watchos(2.0), tvos(9.0));

/// Creates a sort descriptor with a specified string key path and sort order.
///
/// - Parameters:
///   - key: The key path for performing a comparison.
///   - ascending: `YES` if the receiver specifies sorting in ascending order; otherwise, `NO`.
/// - Returns: A sort descriptor initialized with the specified key path and sort order, and the default comparison selector (`compare:`).
- (instancetype)initWithKey:(nullable NSString *)key ascending:(BOOL)ascending;

/// Creates a sort descriptor with a specified string key path, ordering, and comparison selector.
///
/// - Parameters:
///   - key: The key path for performing a comparison.
///   - ascending: `YES` if the receiver specifies sorting in ascending order; otherwise, `NO`.
///   - selector: The method to use when comparing the properties of objects. The selector must specify a method implemented by the value of the property identified by the key path. The selector used for the comparison is passed a single parameter, the object to compare against, and it returns the appropriate `NSComparisonResult` constant.
/// - Returns: A sort descriptor initialized with the specified key path, sort order, and comparison selector.
- (instancetype)initWithKey:(nullable NSString *)key ascending:(BOOL)ascending selector:(nullable SEL)selector;

/// Creates a sort descriptor by decoding from the coder you specify.
///
/// - Parameter coder: The coder to read data from.
- (nullable instancetype)initWithCoder:(NSCoder *)coder;

/// The key that specifies the property to compare during sorting.
@property (nullable, readonly, copy) NSString *key;

/// A Boolean value that indicates whether the receiver specifies sorting in ascending order.
///
/// `YES` if the receiver specifies sorting in ascending order, otherwise `NO`.
@property (readonly) BOOL ascending;

/// The selector for comparing objects.
@property (nullable, readonly) SEL selector;

/// Forces a securely decoded sort descriptor to allow evaluation.
///
/// When securely decoding `NSSortDescriptor` objects encoded using `NSSecureCoding`, evaluation is disabled because it is potentially unsafe to evaluate descriptors you get out of an archive.
///
/// Before you enable evaluation, you should validate key paths, selectors, and related properties to ensure no erroneous or malicious code will be executed. Once you've preflighted the sort descriptor, you can enable it for evaluation by calling this method.
- (void)allowEvaluation API_AVAILABLE(macos(10.9), ios(7.0), watchos(2.0), tvos(9.0));

/// Creates and returns a sort descriptor initialized with the specified key path and ordering, and a comparator block.
///
/// - Parameters:
///   - key: The property for performing a comparison.
///   - ascending: `YES` if the receiver specifies sorting in ascending order; otherwise, `NO`.
///   - cmptr: A comparator block.
/// - Returns: A sort descriptor initialized with the specified key, ordering, and comparator.
+ (instancetype)sortDescriptorWithKey:(nullable NSString *)key ascending:(BOOL)ascending comparator:(NSComparator)cmptr API_AVAILABLE(macos(10.6), ios(4.0), watchos(2.0), tvos(9.0));

/// Creates a sort descriptor with a specified string key path and ordering, and a comparator block.
///
/// - Parameters:
///   - key: The property key for performing a comparison.
///   - ascending: `YES` if the receiver specifies sorting in ascending order; otherwise, `NO`.
///   - cmptr: A comparator block.
/// - Returns: A sort descriptor initialized with the specified key, ordering, and comparator.
- (instancetype)initWithKey:(nullable NSString *)key ascending:(BOOL)ascending comparator:(NSComparator)cmptr API_AVAILABLE(macos(10.6), ios(4.0), watchos(2.0), tvos(9.0));

/// The comparator for the sort descriptor.
///
/// Call this property only for sort descriptors initialized with `initWithKey:ascending:comparator:`.
@property (readonly) NSComparator comparator API_AVAILABLE(macos(10.6), ios(4.0), watchos(2.0), tvos(9.0));

/// Returns a comparison result value that indicates the sort order of two objects.
///
/// The ordering is determined by comparing the values specified by the sort descriptor's key of `object1` and `object2` using the selector specified by the sort descriptor's selector.
///
/// - Parameters:
///   - object1: The object to compare with `object2`. This object must have a property accessible using the key-path specified by the sort descriptor's key.
///   - object2: The object to compare with `object1`. This object must have a property accessible using the key-path specified by the sort descriptor's key.
/// - Returns: `NSOrderedAscending` if `object1` is less than `object2`, `NSOrderedDescending` if `object1` is greater than `object2`, or `NSOrderedSame` if `object1` is equal to `object2`.
- (NSComparisonResult)compareObject:(id)object1 toObject:(id)object2;

/// Returns a sort descriptor that reverses the sort order.
@property (readonly, retain) id reversedSortDescriptor;

@end

@interface NSSet<ObjectType> (NSSortDescriptorSorting)

/// Returns an array that lists the receiving set's elements in ascending order, as determined by a given array of sort descriptors.
- (NSArray<ObjectType> *)sortedArrayUsingDescriptors:(NSArray<NSSortDescriptor *> *)sortDescriptors API_AVAILABLE(macos(10.6), ios(4.0), watchos(2.0), tvos(9.0));

@end

@interface NSArray<ObjectType> (NSSortDescriptorSorting)

/// Returns a copy of the receiving array sorted as specified by a given array of sort descriptors.
- (NSArray<ObjectType> *)sortedArrayUsingDescriptors:(NSArray<NSSortDescriptor *> *)sortDescriptors;

@end

@interface NSMutableArray<ObjectType> (NSSortDescriptorSorting)

/// Sorts the receiving array using a given array of sort descriptors.
- (void)sortUsingDescriptors:(NSArray<NSSortDescriptor *> *)sortDescriptors;

@end

@interface NSOrderedSet<ObjectType> (NSKeyValueSorting)

/// Returns an array that lists the receiving ordered set's elements in ascending order, as determined by a given array of sort descriptors.
- (NSArray<ObjectType> *)sortedArrayUsingDescriptors:(NSArray<NSSortDescriptor *> *)sortDescriptors API_AVAILABLE(macos(10.7), ios(5.0), watchos(2.0), tvos(9.0));

@end

@interface NSMutableOrderedSet<ObjectType> (NSKeyValueSorting)

/// Sorts the receiving mutable ordered set using a given array of sort descriptors.
- (void)sortUsingDescriptors:(NSArray<NSSortDescriptor *> *)sortDescriptors API_AVAILABLE(macos(10.7), ios(5.0), watchos(2.0), tvos(9.0));

@end

NS_HEADER_AUDIT_END(nullability, sendability)
