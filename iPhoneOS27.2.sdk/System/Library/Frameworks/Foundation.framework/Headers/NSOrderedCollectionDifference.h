/*	NSOrderedCollectionDifference.h
	Copyright (c) 2017-2019, Apple Inc. All rights reserved.
*/

@class NSArray<ObjectType>;

#import <Foundation/NSOrderedCollectionChange.h>
#import <Foundation/NSIndexSet.h>
#import <Foundation/NSEnumerator.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

/// Constants that specify the options to use when creating an ordered collection difference.
typedef NS_OPTIONS(NSUInteger, NSOrderedCollectionDifferenceCalculationOptions) {
    /// Insertion changes do not store a reference to the inserted object.
    NSOrderedCollectionDifferenceCalculationOmitInsertedObjects = (1 << 0UL),
    /// Insertion changes do not store a reference to the removed object.
    NSOrderedCollectionDifferenceCalculationOmitRemovedObjects = (1 << 1UL),
    /// Assume objects that were uniquely removed and inserted were moved.
    /// This is useful when diffing based on identity instead of equality.
    NSOrderedCollectionDifferenceCalculationInferMoves = (1 << 2UL)
} API_AVAILABLE(macosx(10.15), ios(13.0), watchos(6.0), tvos(13.0));

/// An object representing the difference between two ordered collections.
///
/// Use ``NSArray/differenceFromArray:`` or one of its variations to get an instance of ``NSOrderedCollectionDifference``, which represents the difference between two ordered collections.
///
/// For example, the following sample compares two arrays of strings to create a difference that represents the changes:
///
/// ```objc
/// NSArray *original = @[@"Red", @"Green", @"Blue"];
/// NSArray *modified = @[@"Red", @"Blue", @"Green"];
///
/// NSOrderedCollectionDifference *diff = [original differenceFromArray:modified];
///
/// // diff.hasChanges == TRUE
/// // diff.insertions.count == 1
/// // diff.removals.count == 1
/// ```
API_AVAILABLE(macosx(10.15), ios(13.0), watchos(6.0), tvos(13.0))
@interface NSOrderedCollectionDifference<ObjectType> : NSObject <NSFastEnumeration>
#ifndef __OBJC2__
{
@private
    id _removeIndexes;
    id _removeObjects;
    id _insertIndexes;
    id _insertObjects;
    id _moves;
}
#endif // !__OBJC2__

/// Creates a new difference representing the changes in the parameter.
///
/// For clients interested in the difference between two collections, the
/// collection's differenceFrom method should be used instead.
///
/// To guarantee that instances are unambiguous and safe for compatible base
/// states, this method requires that its parameter conform to the following
/// requirements:
///
/// 1) All insertion offsets are unique
/// 2) All removal offsets are unique
/// 3) All associated indexes match a change with the opposite parity.
- (instancetype)initWithChanges:(NSArray<NSOrderedCollectionChange<ObjectType> *> *)changes;

/// Creates an ordered collection difference from arrays of inserted and removed objects with corresponding sets of indices, in addition to an array of ordered collection changes.
///
/// - Parameter inserts: An index set that represents the index values to associate with the objects in the provided array of inserted objects.
/// - Parameter insertedObjects: An array of objects the ordered collection difference will insert.
/// - Parameter removes: An index set that represents the index values to associate with the objects in the provided array of removed objects.
/// - Parameter removedObjects: An array of objects the ordered collection difference will remove.
/// - Parameter changes: An array of ordered collection changes.
- (instancetype)initWithInsertIndexes:(NSIndexSet *)inserts
                      insertedObjects:(nullable NSArray<ObjectType> *)insertedObjects
                        removeIndexes:(NSIndexSet *)removes
                       removedObjects:(nullable NSArray<ObjectType> *)removedObjects
                    additionalChanges:(NSArray<NSOrderedCollectionChange<ObjectType> *> *)changes NS_DESIGNATED_INITIALIZER;

/// Creates an ordered collection difference from arrays of inserted and removed objects with corresponding sets of indices.
///
/// - Parameter inserts: An index set that represents the index values to associate with the objects in the provided array of inserted objects.
/// - Parameter insertedObjects: An array of objects the ordered collection difference will insert.
/// - Parameter removes: An index set that represents the index values to associate with the objects in the provided array of removed objects.
/// - Parameter removedObjects: An array of objects the ordered collection difference will remove.
- (instancetype)initWithInsertIndexes:(NSIndexSet *)inserts
                      insertedObjects:(nullable NSArray<ObjectType> *)insertedObjects
                        removeIndexes:(NSIndexSet *)removes
                       removedObjects:(nullable NSArray<ObjectType> *)removedObjects;

/// A collection of insertion change objects.
@property (strong, readonly) NSArray<NSOrderedCollectionChange<ObjectType> *> *insertions API_AVAILABLE(macosx(10.15), ios(13.0), watchos(6.0), tvos(13.0));
/// A collection of removal change objects.
@property (strong, readonly) NSArray<NSOrderedCollectionChange<ObjectType> *> *removals API_AVAILABLE(macosx(10.15), ios(13.0), watchos(6.0), tvos(13.0));

/// A Boolean value that indicates if the difference has changes.
@property (assign, readonly) BOOL hasChanges;

/// Create a new ordered collection difference by mapping over this difference's members, processing the change objects with the block provided.
///
/// - Parameter block: A block that receives an ordered collection change and returns an updated change.
/// - Returns: A new ordered collection difference.
- (NSOrderedCollectionDifference<id> *)differenceByTransformingChangesWithBlock:(NSOrderedCollectionChange<id> *(NS_NOESCAPE ^)(NSOrderedCollectionChange<ObjectType> *))block;

/// Returns a difference that is the inverse of the receiver.
///
/// Applying a difference to an ordered collection and then applying the inverse
/// difference results in the original ordered collection. To revert a
/// chronological sequence of diffs, apply their inverses in reverse order.
- (instancetype)inverseDifference API_AVAILABLE(macosx(10.15), ios(13.0), watchos(6.0), tvos(13.0));

@end

NS_HEADER_AUDIT_END(nullability, sendability)
