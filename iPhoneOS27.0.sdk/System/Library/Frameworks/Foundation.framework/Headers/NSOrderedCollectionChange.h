/*	NSOrderedCollectionChange.h
	Copyright (c) 2017-2019, Apple Inc. All rights reserved.
*/

#import <Foundation/NSObject.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

/// The type of change represented in computing the difference of an ordered collection.
typedef NS_ENUM(NSInteger, NSCollectionChangeType) {
    /// An insertion change.
    NSCollectionChangeInsert,
    /// A removal change.
    NSCollectionChangeRemove
} API_AVAILABLE(macosx(10.15), ios(13.0), watchos(6.0), tvos(13.0));

/// An object that represents an indexed change within an ordered collection.
///
/// An ordered collection change represents changes by adding, removing, or moving objects within an ordered collection. Changes with an associated index indicate a move within the collection.
API_AVAILABLE(macosx(10.15), ios(13.0), watchos(6.0), tvos(13.0))
@interface NSOrderedCollectionChange<ObjectType> : NSObject
#ifndef __OBJC2__
{
@private
    id _object;
    NSCollectionChangeType _changeType;
    NSUInteger _index;
    NSUInteger _associatedIndex;
}
#endif // !__OBJC2__

/// Creates a change object that represents inserting or removing an object from an ordered collection at a specific index.
///
/// - Parameter anObject: An object to be removed or inserted by the change.
/// - Parameter type: The type of change.
/// - Parameter index: The index location within an ordered collection where the change applies.
+ (NSOrderedCollectionChange<ObjectType> *)changeWithObject:(nullable ObjectType)anObject
                                                       type:(NSCollectionChangeType)type
                                                      index:(NSUInteger)index;

/// Creates a change object that represents inserting or removing an object from an ordered collection at a specific index, matched with an associated location that infers a move within the collection.
///
/// - Parameter anObject: An object to be removed or inserted by the change.
/// - Parameter type: The type of change.
/// - Parameter index: The index location within an ordered collection where the change applies.
/// - Parameter associatedIndex: The index of the change's counterpart of the opposite type in the diff.
+ (NSOrderedCollectionChange<ObjectType> *)changeWithObject:(nullable ObjectType)anObject
                                                       type:(NSCollectionChangeType)type
                                                      index:(NSUInteger)index
                                            associatedIndex:(NSUInteger)associatedIndex;

/// An object the change inserts or removes.
@property (readonly, strong, nullable) ObjectType object;

/// The type of change.
@property (readonly) NSCollectionChangeType changeType;

/// The index location of the change.
///
/// For removals, the index of the object in the original state. For insertions, the index of the object in the final state.
@property (readonly) NSUInteger index;

/// When this property is set to a value other than `NSNotFound`, the receiver is one half of a move, and this value is the index of the change's counterpart of the opposite type in the diff.
///
/// Pairs of changes with opposite types that refer to each other represent the index location of their counterpart with the `associatedIndex` property.
///
/// A move pair can have a different `object` in its removal and insertion changes, which can imply that the change represents moving and changing or replacing an element.
///
/// > Note:
/// > Don't ignore a move when the indexes of its changes are the same. The calculated difference may legitimately produce a diff where a change removes the object at one index and the object at another index moves to the same index. Ignoring the move produces an incorrect result.
@property (readonly) NSUInteger associatedIndex;

- (id)init NS_UNAVAILABLE;

/// Creates a change object that represents inserting or removing an object from an ordered collection at a specific index.
///
/// - Parameter anObject: An optional object the change will remove or insert.
/// - Parameter type: The type of change.
/// - Parameter index: The index location within an ordered collection where the change applies.
- (instancetype)initWithObject:(nullable ObjectType)anObject
                          type:(NSCollectionChangeType)type
                         index:(NSUInteger)index;

/// Creates a change object that represents inserting, removing, or moving an object from an ordered collection at a specific index.
///
/// - Parameter anObject: An optional object the change will remove or insert.
/// - Parameter type: The type of change.
/// - Parameter index: The index location within an ordered collection where the change applies.
/// - Parameter associatedIndex: The index of the change's counterpart of the opposite type in the diff.
- (instancetype)initWithObject:(nullable ObjectType)anObject
                          type:(NSCollectionChangeType)type
                         index:(NSUInteger)index
               associatedIndex:(NSUInteger)associatedIndex NS_DESIGNATED_INITIALIZER;
@end

NS_HEADER_AUDIT_END(nullability, sendability)
