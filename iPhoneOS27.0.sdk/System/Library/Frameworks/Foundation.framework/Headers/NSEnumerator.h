/*	NSEnumerator.h
	Copyright (c) 1995-2019, Apple Inc. All rights reserved.
*/

#import <Foundation/NSObject.h>

@class NSArray<ObjectType>;

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

/// A structure used by objects adopting the `NSFastEnumeration` protocol to maintain enumeration state.
typedef struct {
    /// Used by the mutation guard.
    unsigned long state;
    /// A C array of objects.
    id __unsafe_unretained _Nullable * _Nullable itemsPtr;
    /// Conceptually a pointer to a mutation count.
    unsigned long * _Nullable mutationsPtr;
    /// A C array that the enumeration implementation can use for any purpose.
    unsigned long extra[5];
} NSFastEnumerationState;

/// A protocol that objects adopt to support fast enumeration.
///
/// The abstract class ``NSEnumerator`` provides a convenience implementation that uses ``NSEnumerator/nextObject()`` to return items one at a time.
@protocol NSFastEnumeration

/// Returns by reference a C array of objects over which the sender should iterate, and as the return value the number of objects in the array.
- (NSUInteger)countByEnumeratingWithState:(NSFastEnumerationState *)state objects:(id __unsafe_unretained _Nullable [_Nonnull])buffer count:(NSUInteger)len;

@end

/// An abstract class whose subclasses enumerate collections of objects, such as arrays and dictionaries.
@interface NSEnumerator<ObjectType> : NSObject <NSFastEnumeration>

/// Returns the next object from the collection being enumerated.
- (nullable ObjectType)nextObject;

@end

@interface NSEnumerator<ObjectType> (NSExtendedEnumerator)

/// The array of unenumerated objects.
@property (readonly, copy) NSArray<ObjectType> *allObjects;

@end

NS_HEADER_AUDIT_END(nullability, sendability)
