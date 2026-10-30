/*	NSCompoundPredicate.h
	Copyright (c) 2004-2019, Apple Inc. All rights reserved.
*/

#import <Foundation/NSPredicate.h>

@class NSArray<ObjectType>;

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

// Compound predicates are predicates which act on the results of evaluating other operators. We provide the basic boolean operators: AND, OR, and NOT.

/// Constants that describe the possible types of a compound predicate.
typedef NS_ENUM(NSUInteger, NSCompoundPredicateType) {
    /// A logical NOT predicate.
    NSNotPredicateType = 0,
    /// A logical AND predicate.
    NSAndPredicateType,
    /// A logical OR predicate.
    NSOrPredicateType,
};

/// A specialized predicate that evaluates logical combinations of other predicates.
///
/// Use ``NSCompoundPredicate`` to create an `AND` or `OR` compound predicate of one or more other predicates, or the `NOT` of a single predicate. For the logical `AND` and `OR` operations:
///
/// - An `AND` predicate with no subpredicates evaluates to <doc://com.apple.documentation/documentation/swift/true>.
/// - An `OR` predicate with no subpredicates evaluates to <doc://com.apple.documentation/documentation/swift/false>.
/// - A compound predicate with one or more subpredicates evaluates to the truth of its subpredicates.
API_AVAILABLE(macos(10.4), ios(3.0), watchos(2.0), tvos(9.0))
@interface NSCompoundPredicate : NSPredicate

/// Returns the receiver that a specified type initializes using predicates from a specified array.
///
/// For applications linked on macOS 10.5 or later, the `subpredicates` array is copied. For applications linked on OS X v10.4, the `subpredicates` array is retained (for binary compatibility).
- (instancetype)initWithType:(NSCompoundPredicateType)type subpredicates:(NSArray<NSPredicate *> *)subpredicates NS_DESIGNATED_INITIALIZER;
/// Creates a predicate by decoding from the coder you specify.
- (nullable instancetype)initWithCoder:(NSCoder *)coder NS_DESIGNATED_INITIALIZER;

/// The predicate type for the receiver.
@property (readonly) NSCompoundPredicateType compoundPredicateType;
/// The receiver's subpredicates.
@property (readonly, copy) NSArray *subpredicates;

/*** Convenience Methods ***/
/// Returns a new predicate that you form using an AND operation on the predicates in a specified array.
///
/// - Parameters:
///   - subpredicates: An array of `NSPredicate` objects.
/// - Returns: A new predicate formed by AND-ing the predicates specified by `subpredicates`.
///
/// An AND predicate with no subpredicates evaluates to TRUE.
+ (NSCompoundPredicate *)andPredicateWithSubpredicates:(NSArray<NSPredicate *> *)subpredicates NS_SWIFT_NAME(init(andPredicateWithSubpredicates:));
/// Returns a new predicate that you form using an OR operation on the predicates in a specified array.
///
/// An OR predicate with no subpredicates evaluates to FALSE.
+ (NSCompoundPredicate *)orPredicateWithSubpredicates:(NSArray<NSPredicate *> *)subpredicates NS_SWIFT_NAME(init(orPredicateWithSubpredicates:));
/// Returns a new predicate that you form using a NOT operation on a specified predicate.
+ (NSCompoundPredicate *)notPredicateWithSubpredicate:(NSPredicate *)predicate NS_SWIFT_NAME(init(notPredicateWithSubpredicate:));

@end

NS_HEADER_AUDIT_END(nullability, sendability)
