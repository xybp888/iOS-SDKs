/*  NSIndexPath.h
    Copyright (c) 2003-2019, Apple Inc. All rights reserved.
*/

#import <Foundation/NSObject.h>
#import <Foundation/NSRange.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

/// A list of indexes that together represent the path to a specific location in a tree of nested arrays.
///
/// In Swift, this object bridges to ``IndexPath``; use ``NSIndexPath`` when you need reference semantics or other Foundation-specific behavior.
///
/// Each index in an index path represents the index into an array of children from one node in the tree to another, deeper, node. For example, the index path `1.4.3.2` specifies the path shown in [Figure 1](/documentation/foundation/nsindexpath#1965825).
///
/// ![Index path “1.4.3.2”](media-1965825)
///
/// > Note:
/// > The UIKit framework adds programming interfaces to the `NSIndexPath` class of the Foundation framework to facilitate the identification of rows and sections in <doc://com.apple.documentation/documentation/uikit/uitableview> objects and the identification of items and sections in <doc://com.apple.documentation/documentation/uikit/uicollectionview> objects. The API consists of class factory methods and properties for accessing the various indexed values. You use the factory methods to create an index path for the corresponding table view or collection view.
///
/// > Important:
/// > The Swift overlay to the Foundation framework provides the ``IndexPath`` structure, which bridges to the ``NSIndexPath`` class. For more information about value types, see <doc://com.apple.documentation/documentation/swift/working-with-foundation-types>.
@interface NSIndexPath : NSObject <NSCopying, NSSecureCoding>

/// Creates a one-node index path.
///
/// - Parameter index: Index of the item in node 0 to point to.
/// - Returns: One-node index path with `index`.
+ (instancetype)indexPathWithIndex:(NSUInteger)index;

/// Creates an index path with one or more nodes.
///
/// - Parameters:
///   - indexes: Array of indexes to make up the index path.
///   - length: Number of nodes to include in the index path.
/// - Returns: Index path with `indexes` up to `length`.
+ (instancetype)indexPathWithIndexes:(const NSUInteger [_Nullable])indexes length:(NSUInteger)length;

/// Initializes an index path with the given nodes and length.
///
/// This method is a designated initializer of `NSIndexPath`.
///
/// - Parameters:
///   - indexes: Array of indexes to make up the index path.
///   - length: Number of nodes to include in the index path.
/// - Returns: Initialized `NSIndexPath` object with `indexes` up to `length`.
- (instancetype)initWithIndexes:(const NSUInteger [_Nullable])indexes length:(NSUInteger)length NS_DESIGNATED_INITIALIZER;

/// Initializes an index path with a single node.
///
/// - Parameter index: Index of the item in node 0 to point to.
/// - Returns: Initialized `NSIndexPath` object representing a one-node index path with `index`.
- (instancetype)initWithIndex:(NSUInteger)index;


/// Returns an index path containing the nodes in the receiving index path plus another given index.
///
/// - Parameter index: Index to append to the index path's indexes.
/// - Returns: A new index path containing the receiving index path's indexes and `index`.
- (NSIndexPath *)indexPathByAddingIndex:(NSUInteger)index;

/// Returns an index path with the nodes in the receiving index path, excluding the last one.
///
/// Returns an empty `NSIndexPath` instance if the receiving index path's length is 1 or less.
///
/// - Returns: A new index path with the receiving index path's indexes, excluding the last one.
- (NSIndexPath *)indexPathByRemovingLastIndex;

/// Provides the value at a particular node in the index path.
///
/// - Parameter position: Index value of the desired node. Node numbering starts at zero.
/// - Returns: The index value at `position` or `NSNotFound` if the node is outside the range of the index path.
- (NSUInteger)indexAtPosition:(NSUInteger)position;

/// The number of nodes in the index path.
@property (readonly) NSUInteger length;

/// Copies the indexes stored in the index path from the positions specified by the position range into the specified indexes.
///
/// It is the developer’s responsibility to allocate the memory for the C array.
///
/// - Parameters:
///   - indexes: Buffer of at least as many `NSUInteger` values as specified by the length of `positionRange`. On return, this memory will hold the index path’s indexes.
///   - positionRange: A range of valid positions within this index path. If the location plus the length of `positionRange` is greater than the length of this index path, this method raises an `NSRangeException`.
- (void)getIndexes:(NSUInteger *)indexes range:(NSRange)positionRange API_AVAILABLE(macos(10.9), ios(7.0), watchos(2.0), tvos(9.0));

/// Indicates the depth-first traversal order of the receiving index path and another index path.
///
/// - Parameter otherObject: Index path to compare. This value must not be `nil`. If the value is `nil`, the behavior is undefined.
/// - Returns: The depth-first traversal ordering of the receiving index path and `otherObject`.
- (NSComparisonResult)compare:(NSIndexPath *)otherObject;

@end

@interface NSIndexPath (NSDeprecated)
/// Copies the objects contained in the index path into indexes.
///
/// This method is unsafe because it could potentially cause buffer overruns. You should use `getIndexes:range:` instead.
///
/// You must allocate the memory for the C array.
///
/// - Parameter indexes: Pointer to a C array of objects of size at least the length of the index path. On return, the index path's indexes.
- (void)getIndexes:(NSUInteger *)indexes API_DEPRECATED_WITH_REPLACEMENT("getIndexes:range:", macos(10.0, API_TO_BE_DEPRECATED), ios(2.0, API_TO_BE_DEPRECATED), watchos(2.0, API_TO_BE_DEPRECATED), tvos(9.0, API_TO_BE_DEPRECATED));
@end

NS_HEADER_AUDIT_END(nullability, sendability)
