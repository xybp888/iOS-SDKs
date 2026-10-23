/*	NSIndexSet.h
	Copyright (c) 2002-2019, Apple Inc. All rights reserved.
*/

/* Class for managing set of indexes. The set of valid indexes are 0 .. NSNotFound - 1; trying to use indexes outside this range is an error.  NSIndexSet uses NSNotFound as a return value in cases where the queried index doesn't exist in the set; for instance, when you ask firstIndex and there are no indexes; or when you ask for indexGreaterThanIndex: on the last index, and so on.

The following code snippets can be used to enumerate over the indexes in an NSIndexSet:

    // Forward
    NSUInteger currentIndex = [set firstIndex];
    while (currentIndex != NSNotFound) {
        ...
        currentIndex = [set indexGreaterThanIndex:currentIndex];
    }
    
    // Backward
    NSUInteger currentIndex = [set lastIndex];
    while (currentIndex != NSNotFound) {
        ...
        currentIndex = [set indexLessThanIndex:currentIndex];
    }

To enumerate without doing a call per index, you can use the method getIndexes:maxCount:inIndexRange:.
*/

#import <Foundation/NSObject.h>
#import <Foundation/NSRange.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

/// An immutable collection of unique integer values that represent indexes in another collection.
///
/// In Swift, this type bridges to ``IndexSet``; use ``NSIndexSet`` when you need reference semantics or other Foundation-specific behavior.
///
/// The `NSIndexSet` class represents an immutable collection of unique unsigned integers, known as **indexes** because of the way they are used. This collection is referred to as an **index set**. Indexes must be in the range `0 .. NSNotFound - 1`.
///
/// You use index sets in your code to store indexes into some other data structure. For example, given an `NSArray` object, you could use an index set to identify a subset of objects in that array.
///
/// You should not use index sets to store an arbitrary collection of integer values because index sets store indexes as sorted ranges. This makes them more efficient than storing a collection of individual integers. It also means that each index value can only appear once in the index set.
///
/// The designated initializers of the `NSIndexSet` class are: ``init(index:)``, ``init(indexesIn:)``, and ``init(indexSet:)``.
///
/// You must not subclass the `NSIndexSet` class.
///
/// The mutable subclass of `NSIndexSet` is ``NSMutableIndexSet``.
///
/// > Important:
/// > The Swift overlay to the Foundation framework provides the ``IndexSet`` structure, which bridges to the ``NSIndexSet`` class and its mutable subclass, ``NSMutableIndexSet``. For more information about value types, see <doc://com.apple.documentation/documentation/swift/working-with-foundation-types>.
@interface NSIndexSet : NSObject <NSCopying, NSMutableCopying, NSSecureCoding> {
    @protected   // all instance variables are private
    struct {
        NSUInteger _hasSingleRange:1;
        NSUInteger _hasBitfield:1;
        NSUInteger _reservedArrayBinderController:30;
    } _indexSetFlags;
    union {
        struct {
            NSRange _range;
        } _singleRange;
        struct {
            void * _data;
            void *_reserved;
        } _multipleRanges;
        struct {
            uint64_t _bitfield;
        } _singleBitfield;
    } _internal;
}

/// Creates an empty index set.
+ (instancetype)indexSet;
/// Creates an index set with an index.
/// - Parameter value: An index. Must be in the range `0 .. NSNotFound - 1`.
+ (instancetype)indexSetWithIndex:(NSUInteger)value;
/// Creates an index set with an index range.
/// - Parameter range: An index range. Must be in the range `0 .. NSNotFound - 1`.
+ (instancetype)indexSetWithIndexesInRange:(NSRange)range;

/// Initializes an allocated NSIndexSet object with an index range.
///
/// This method raises an `NSRangeException` when `indexRange` would add an index that exceeds the maximum allowed value for unsigned integers.
/// This method is a designated initializer for `NSIndexSet`.
/// - Parameter range: An index range. Must be in the range `0 .. NSNotFound - 1`.
- (instancetype)initWithIndexesInRange:(NSRange)range NS_DESIGNATED_INITIALIZER;
/// Initializes an allocated NSIndexSet object with an index set.
///
/// This method is a designated initializer for `NSIndexSet`.
/// - Parameter indexSet: An index set.
- (instancetype)initWithIndexSet:(NSIndexSet *)indexSet NS_DESIGNATED_INITIALIZER;

/// Initializes an allocated NSIndexSet object with an index.
/// - Parameter value: An index. Must be in the range `0 .. NSNotFound - 1`.
- (instancetype)initWithIndex:(NSUInteger)value;

/// Indicates whether the indexes in the receiving index set are the same indexes contained in another index set.
/// - Parameter indexSet: Index set being inquired about.
/// - Returns: `YES` when the indexes in the receiving index set are the same indexes `indexSet` contains, `NO` otherwise.
- (BOOL)isEqualToIndexSet:(NSIndexSet *)indexSet;

/// The number of indexes in the index set.
@property (readonly) NSUInteger count;

/// The first index in the index set, or `NSNotFound` when the index set is empty.
@property (readonly) NSUInteger firstIndex;
/// The last index in the index set, or `NSNotFound` when the index set is empty.
@property (readonly) NSUInteger lastIndex;
/// Returns either the closest index in the index set that is greater than a specific index or the not-found indicator.
/// - Parameter value: Index being inquired about.
/// - Returns: Closest index in the index set greater than `index`; `NSNotFound` when the index set contains no qualifying index.
- (NSUInteger)indexGreaterThanIndex:(NSUInteger)value;
/// Returns either the closest index in the index set that is less than a specific index or the not-found indicator.
/// - Parameter value: Index being inquired about.
/// - Returns: Closest index in the index set less than `index`; `NSNotFound` when the index set contains no qualifying index.
- (NSUInteger)indexLessThanIndex:(NSUInteger)value;
/// Returns either the closest index in the index set that is greater than or equal to a specific index or the not-found indicator.
/// - Parameter value: Index being inquired about.
/// - Returns: Closest index in the index set greater than or equal to `index`; `NSNotFound` when the index set contains no qualifying index.
- (NSUInteger)indexGreaterThanOrEqualToIndex:(NSUInteger)value;
/// Returns either the closest index in the index set that is less than or equal to a specific index or the not-found indicator.
/// - Parameter value: Index being inquired about.
/// - Returns: Closest index in the index set less than or equal to `index`; `NSNotFound` when the index set contains no qualifying index.
- (NSUInteger)indexLessThanOrEqualToIndex:(NSUInteger)value;

/// The index set fills an index buffer with the indexes contained both in the index set and in an index range, returning the number of indexes copied.
///
/// You are responsible for allocating the memory required for `indexBuffer` and for releasing it later.
///
/// Suppose you have an index set with contiguous indexes from 1 to 100. If you use this method to request a range of `(1, 100)` and specify a buffer size of `20`, this method returns 20 indexes (1 through 20) in `indexBuffer` and sets `indexRange` to `(21, 80)`.
///
/// Use this method to retrieve entries quickly and efficiently from an index set. You can call this method repeatedly to retrieve blocks of index values and then process them. When doing so, use the return value and `indexRange` to determine when you have finished processing the desired indexes. When the return value is less than `bufferSize`, you have reached the end of the range.
/// - Parameters:
///   - indexBuffer: Index buffer to fill.
///   - bufferSize: Maximum size of `indexBuffer`.
///   - range: Index range to compare with indexes in the index set; `nil` represents all the indexes in the index set. On output, the range of indexes not copied to `indexBuffer`.
/// - Returns: Number of indexes placed in `indexBuffer`.
- (NSUInteger)getIndexes:(NSUInteger *)indexBuffer maxCount:(NSUInteger)bufferSize inIndexRange:(nullable NSRangePointer)range;

/// Returns the number of indexes in the index set that are members of a given range.
/// - Parameter range: Index range being inquired about.
/// - Returns: Number of indexes in the index set that are members of `indexRange`.
- (NSUInteger)countOfIndexesInRange:(NSRange)range API_AVAILABLE(macos(10.5), ios(2.0), watchos(2.0), tvos(9.0));

/// Indicates whether the index set contains a specific index.
/// - Parameter value: Index being inquired about.
/// - Returns: `YES` when the index set contains `index`, `NO` otherwise.
- (BOOL)containsIndex:(NSUInteger)value;
/// Indicates whether the index set contains the indexes represented by an index range.
/// - Parameter range: The index range being inquired about.
/// - Returns: `YES` when the index set contains the indexes in `indexRange`, `NO` otherwise.
- (BOOL)containsIndexesInRange:(NSRange)range;
/// Indicates whether the receiving index set contains a superset of the indexes in another index set.
/// - Parameter indexSet: Index set being inquired about.
/// - Returns: `YES` when the receiving index set contains a superset of the indexes in `indexSet`, `NO` otherwise.
- (BOOL)containsIndexes:(NSIndexSet *)indexSet;

/// Indicates whether the index set contains any of the indexes in a range.
/// - Parameter range: Index range being inquired about.
/// - Returns: `YES` when the index set contains one or more of the indexes in `indexRange`, `NO` otherwise.
- (BOOL)intersectsIndexesInRange:(NSRange)range;

/// Executes a given block using each object in the index set.
///
/// This method executes synchronously.
/// - Parameter block: The block to apply to elements in the set. The block takes two arguments: `idx` (the index of the object) and `stop` (a reference to a Boolean value; set to `YES` to stop further processing).
- (void)enumerateIndexesUsingBlock:(void (NS_NOESCAPE ^)(NSUInteger idx, BOOL *stop))block API_AVAILABLE(macos(10.6), ios(4.0), watchos(2.0), tvos(9.0));
/// Executes a given block over the index set's indexes, using the specified enumeration options.
///
/// This method executes synchronously.
/// - Parameters:
///   - opts: A bitmask that specifies the options for the enumeration (whether it should be performed concurrently and whether it should be performed in reverse order).
///   - block: The block to apply to elements in the set. The block takes two arguments: `idx` (the index of the object) and `stop` (a reference to a Boolean value; set to `YES` to stop further processing).
- (void)enumerateIndexesWithOptions:(NSEnumerationOptions)opts usingBlock:(void (NS_NOESCAPE ^)(NSUInteger idx, BOOL *stop))block API_AVAILABLE(macos(10.6), ios(4.0), watchos(2.0), tvos(9.0));
/// Executes a given block using the indexes in the specified range, using the specified enumeration options.
///
/// This method executes synchronously.
/// - Parameters:
///   - range: The range to enumerate.
///   - opts: A bitmask that specifies the options for the enumeration (whether it should be performed concurrently and whether it should be performed in reverse order).
///   - block: The block to apply to elements in the set. The block takes two arguments: `idx` (the index of the object) and `stop` (a reference to a Boolean value; set to `YES` to stop further processing).
- (void)enumerateIndexesInRange:(NSRange)range options:(NSEnumerationOptions)opts usingBlock:(void (NS_NOESCAPE ^)(NSUInteger idx, BOOL *stop))block API_AVAILABLE(macos(10.6), ios(4.0), watchos(2.0), tvos(9.0));

/// Returns the index of the first object that passes the predicate block test.
/// - Parameter predicate: The block to apply to elements in the set. The block takes two arguments: `idx` (the index of the object) and `stop` (a reference to a Boolean value; set to `YES` to stop further processing). The block returns a Boolean value that indicates whether the index passed the test.
/// - Returns: The index of the first object that passes the predicate test.
- (NSUInteger)indexPassingTest:(BOOL (NS_NOESCAPE ^)(NSUInteger idx, BOOL *stop))predicate API_AVAILABLE(macos(10.6), ios(4.0), watchos(2.0), tvos(9.0));
/// Returns the index of the first object that passes the predicate block test using the specified enumeration options.
/// - Parameters:
///   - opts: A bitmask that specifies the options for the enumeration (whether it should be performed concurrently and whether it should be performed in reverse order).
///   - predicate: The block to apply to elements in the set. The block takes two arguments: `idx` (the index of the object) and `stop` (a reference to a Boolean value; set to `YES` to stop further processing). The block returns a Boolean value that indicates whether the index passed the test.
/// - Returns: The index of the first object that passes the predicate test.
- (NSUInteger)indexWithOptions:(NSEnumerationOptions)opts passingTest:(BOOL (NS_NOESCAPE ^)(NSUInteger idx, BOOL *stop))predicate API_AVAILABLE(macos(10.6), ios(4.0), watchos(2.0), tvos(9.0));
/// Returns the index of the first object in the specified range that passes the predicate block test.
/// - Parameters:
///   - range: The range of indexes to test.
///   - opts: A bitmask that specifies the options for the enumeration (whether it should be performed concurrently and whether it should be performed in reverse order).
///   - predicate: The block to apply to elements in the set. The block takes two arguments: `idx` (the index of the object) and `stop` (a reference to a Boolean value; set to `YES` to stop further processing). The block returns a Boolean value that indicates whether the index passed the test.
/// - Returns: The index of the first object that passes the predicate test.
- (NSUInteger)indexInRange:(NSRange)range options:(NSEnumerationOptions)opts passingTest:(BOOL (NS_NOESCAPE ^)(NSUInteger idx, BOOL *stop))predicate API_AVAILABLE(macos(10.6), ios(4.0), watchos(2.0), tvos(9.0));

/// Returns an `NSIndexSet` containing the receiving index set's objects that pass the block test.
/// - Parameter predicate: The block to apply to elements in the set. The block takes two arguments: `idx` (the index of the object) and `stop` (a reference to a Boolean value; set to `YES` to stop further processing). The block returns a Boolean value that indicates whether the index passed the test.
/// - Returns: An `NSIndexSet` containing the indexes of the receiving index set that passed the predicate block test.
- (NSIndexSet *)indexesPassingTest:(BOOL (NS_NOESCAPE ^)(NSUInteger idx, BOOL *stop))predicate API_AVAILABLE(macos(10.6), ios(4.0), watchos(2.0), tvos(9.0));
/// Returns an `NSIndexSet` containing the receiving index set's objects that pass the block test using the specified enumeration options.
/// - Parameters:
///   - opts: A bitmask that specifies the options for the enumeration (whether it should be performed concurrently and whether it should be performed in reverse order).
///   - predicate: The block to apply to elements in the set. The block takes two arguments: `idx` (the index of the object) and `stop` (a reference to a Boolean value; set to `YES` to stop further processing). The block returns a Boolean value that indicates whether the index passed the test.
/// - Returns: An `NSIndexSet` containing the indexes of the receiving index set that passed the predicate block test.
- (NSIndexSet *)indexesWithOptions:(NSEnumerationOptions)opts passingTest:(BOOL (NS_NOESCAPE ^)(NSUInteger idx, BOOL *stop))predicate API_AVAILABLE(macos(10.6), ios(4.0), watchos(2.0), tvos(9.0));
/// Returns an `NSIndexSet` containing the receiving index set's objects in the specified range that pass the block test.
/// - Parameters:
///   - range: The range of indexes to test.
///   - opts: A bitmask that specifies the options for the enumeration (whether it should be performed concurrently and whether it should be performed in reverse order).
///   - predicate: The block to apply to elements in the set. The block takes two arguments: `idx` (the index of the object) and `stop` (a reference to a Boolean value; set to `YES` to stop further processing). The block returns a Boolean value that indicates whether the index passed the test.
/// - Returns: An `NSIndexSet` containing the indexes of the receiving index set that passed the predicate block test.
- (NSIndexSet *)indexesInRange:(NSRange)range options:(NSEnumerationOptions)opts passingTest:(BOOL (NS_NOESCAPE ^)(NSUInteger idx, BOOL *stop))predicate API_AVAILABLE(macos(10.6), ios(4.0), watchos(2.0), tvos(9.0));

/// Executes a given block using each object in the index set, in the specified ranges.
///
/// If the block parameter is `nil` this method will raise an exception. This method executes synchronously.
/// - Parameter block: The block to apply to elements in the index set. The block takes two arguments: `range` (the range of elements) and `stop` (a reference to a Boolean value; set to `YES` to stop further processing).
- (void)enumerateRangesUsingBlock:(void (NS_NOESCAPE ^)(NSRange range, BOOL *stop))block API_AVAILABLE(macos(10.7), ios(5.0), watchos(2.0), tvos(9.0));
/// Executes a given block using each object in the index set, in the specified ranges.
///
/// By default, the enumeration starts with the first object and continues serially through the indexed set range to the last object in the range. You can specify `NSEnumerationConcurrent` and/or `NSEnumerationReverse` as enumeration options to modify this behavior. If the block parameter is `nil` this method will raise an exception. This method executes synchronously.
/// - Parameters:
///   - opts: A bitmask that specifies the `NSEnumerationOptions` for the enumeration (whether it should be performed concurrently and whether it should be performed in reverse order).
///   - block: The block to apply to elements in the index set. The block takes two arguments: `range` (the range of elements) and `stop` (a reference to a Boolean value; set to `YES` to stop further processing).
- (void)enumerateRangesWithOptions:(NSEnumerationOptions)opts usingBlock:(void (NS_NOESCAPE ^)(NSRange range, BOOL *stop))block API_AVAILABLE(macos(10.7), ios(5.0), watchos(2.0), tvos(9.0));
/// Enumerates over the ranges in the range of objects using the block.
///
/// By default, the enumeration starts with the first object and continues serially through the indexed set range to the last object in the range. You can specify `NSEnumerationConcurrent` and/or `NSEnumerationReverse` as enumeration options to modify this behavior. If the block parameter is `nil` this method will raise an exception. This method executes synchronously.
/// - Parameters:
///   - range: The range of items to enumerate. If the range intersects a range of the receiver's indexes, then that intersection will be passed to the block.
///   - opts: A bitmask that specifies the `NSEnumerationOptions` for the enumeration.
///   - block: The block to apply to elements in the index set. The block takes two arguments: `range` (the range of elements) and `stop` (a reference to a Boolean value; set to `YES` to stop further processing).
- (void)enumerateRangesInRange:(NSRange)range options:(NSEnumerationOptions)opts usingBlock:(void (NS_NOESCAPE ^)(NSRange range, BOOL *stop))block API_AVAILABLE(macos(10.7), ios(5.0), watchos(2.0), tvos(9.0));

@end

/// A mutable collection of unique integer values that represent indexes in another collection.
///
/// In Swift, this type bridges to ``IndexSet``; use ``NSMutableIndexSet`` when you need reference semantics or other Foundation-specific behavior.
///
/// The ``NSMutableIndexSet`` class represents a mutable collection of unique unsigned integers, known as _indexes_ because of the way they are used. This collection is referred to as a _mutable index set_. The inclusive range of valid indexes is `0...(NSNotFound - 1)`; trying to use indexes outside this range is invalid.
///
/// The values in a mutable index set are always sorted, so the order in which values are added is irrelevant.
///
/// Do not subclass the ``NSMutableIndexSet`` class.
///
/// > Important:
/// > The Swift overlay to the Foundation framework provides the ``IndexSet`` structure, which bridges to the ``NSMutableIndexSet`` class and its immutable superclass, ``NSIndexSet``. For more information about value types, see <doc://com.apple.documentation/documentation/swift/working-with-foundation-types>.
@interface NSMutableIndexSet : NSIndexSet

/// Adds the indexes in an index set to the receiver.
/// - Parameter indexSet: Index set to add.
- (void)addIndexes:(NSIndexSet *)indexSet;
/// Removes the indexes in an index set from the receiver.
/// - Parameter indexSet: Index set to remove.
- (void)removeIndexes:(NSIndexSet *)indexSet;
/// Removes the receiver's indexes.
- (void)removeAllIndexes;
/// Adds an index to the receiver.
/// - Parameter value: Index to add. Must be in the range `0 .. NSNotFound - 1`.
- (void)addIndex:(NSUInteger)value;
/// Removes an index from the receiver.
/// - Parameter value: Index to remove.
- (void)removeIndex:(NSUInteger)value;
/// Adds the indexes in an index range to the receiver.
///
/// This method raises an `NSRangeException` when `range` would add an index that exceeds the maximum allowed value for unsigned integers.
/// - Parameter range: Index range to add. Must be in the range `0 .. NSNotFound - 1`.
- (void)addIndexesInRange:(NSRange)range;
/// Removes the indexes in an index range from the receiver.
/// - Parameter range: Index range to remove.
- (void)removeIndexesInRange:(NSRange)range;

/// Shifts a group of indexes to the left or the right within the receiver.
///
/// The group of indexes shifted is made up by `index` and the indexes that follow it in the set.
/// A left shift deletes the indexes in a range the length of `delta` preceding `index` from the set.
/// A right shift inserts empty space in the range `(index, delta)` in the receiver.
/// The resulting indexes must all be in the range `0 .. NSNotFound - 1`.
/// - Parameters:
///   - index: Head of the group of indexes to shift.
///   - delta: Amount and direction of the shift. Positive integers shift the indexes to the right. Negative integers shift the indexes to the left.
- (void)shiftIndexesStartingAtIndex:(NSUInteger)index by:(NSInteger)delta;

@end

NS_HEADER_AUDIT_END(nullability, sendability)
