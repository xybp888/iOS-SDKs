/*	NSComparisonPredicate.h
	Copyright (c) 2004-2019, Apple Inc. All rights reserved.
*/

#import <Foundation/NSPredicate.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

/// Constants that describe the possible types of string comparison for comparison predicates.
typedef NS_OPTIONS(NSUInteger, NSComparisonPredicateOptions) {
    /// A case-insensitive predicate. You represent this option in a predicate format string using a `[c]` following a string operation (for example, `"NeXT" like[c] "next"`).
    NSCaseInsensitivePredicateOption = 0x01,
    /// A diacritic-insensitive predicate. You represent this option in a predicate format string using a `[d]` following a string operation (for example, `"naïve" like[d] "naive"`).
    NSDiacriticInsensitivePredicateOption = 0x02,
    /// Indicates that the strings to be compared have been preprocessed; this supersedes other options and is intended as a performance optimization option.
    NSNormalizedPredicateOption API_AVAILABLE(macos(10.6), ios(4.0), watchos(2.0), tvos(9.0)) = 0x04,
};

/// Constants that describe the possible types of modifier for a comparison predicate.
typedef NS_ENUM(NSUInteger, NSComparisonPredicateModifier) {
    /// A predicate to compare directly the left and right hand sides.
    NSDirectPredicateModifier = 0,
    /// A predicate to compare all entries in the destination of a to-many relationship.
    NSAllPredicateModifier,
    /// A predicate to match with any entry in the destination of a to-many relationship.
    NSAnyPredicateModifier
};


/// Defines the type of comparison for a comparison predicate.
typedef NS_ENUM(NSUInteger, NSPredicateOperatorType) {
    /// A less-than predicate.
    NSLessThanPredicateOperatorType = 0,
    /// A less-than-or-equal-to predicate.
    NSLessThanOrEqualToPredicateOperatorType,
    /// A greater-than predicate.
    NSGreaterThanPredicateOperatorType,
    /// A greater-than-or-equal-to predicate.
    NSGreaterThanOrEqualToPredicateOperatorType,
    /// An equal-to predicate.
    NSEqualToPredicateOperatorType,
    /// A not-equal-to predicate.
    NSNotEqualToPredicateOperatorType,
    /// A full regular expression matching predicate.
    NSMatchesPredicateOperatorType,
    /// A simple subset of the `MATCHES` predicate, similar in behavior to SQL `LIKE`.
    NSLikePredicateOperatorType,
    /// A begins-with predicate.
    NSBeginsWithPredicateOperatorType,
    /// An ends-with predicate.
    NSEndsWithPredicateOperatorType,
    /// A predicate to determine if the left hand side is in the right hand side. For strings, returns `YES` if the left hand side is a substring of the right hand side. For collections, returns `YES` if the left hand side is in the right hand side.
    NSInPredicateOperatorType,
    /// A predicate that uses a custom selector that takes a single argument and returns a `BOOL` value. The selector is invoked on the left hand side with the right hand side as the argument.
    NSCustomSelectorPredicateOperatorType,
    /// A predicate to determine if the left hand side contains the right hand side. Returns `YES` if `[lhs contains rhs]`; the left hand side must be an `NSExpression` object that evaluates to a collection.
    NSContainsPredicateOperatorType API_AVAILABLE(macos(10.5), ios(3.0), watchos(2.0), tvos(9.0)) = 99,
    /// A predicate to determine if the left hand side lies at or between bounds specified by the right hand side. The right hand side must be an array in which the first element sets the lower bound and the second element the upper, inclusive.
    NSBetweenPredicateOperatorType API_AVAILABLE(macos(10.5), ios(3.0), watchos(2.0), tvos(9.0))
};

@class NSPredicateOperator;
@class NSExpression;

/// A specialized predicate for comparing expressions.
///
/// Use comparison predicates to compare the results of two expressions. You create a comparison predicate with an operator, a left expression, and a right expression, and use instances of the ``NSExpression`` class to represent those expressions. When you evaluate the predicate, it returns a `BOOL` value as the result of invoking the operator with the results of evaluating the expressions.
API_AVAILABLE(macos(10.4), ios(3.0), watchos(2.0), tvos(9.0))
@interface NSComparisonPredicate : NSPredicate

/// Creates and returns a predicate of a given type formed by combining given left and right expressions using a given modifier and options.
/// - Parameters:
///   - lhs: The left hand expression.
///   - rhs: The right hand expression.
///   - modifier: The modifier to apply.
///   - type: The predicate operator type.
///   - options: The options to apply. For no options, pass `0`.
/// - Returns: A new predicate of type `type` formed by combining the given left and right expressions using the `modifier` and `options`.
+ (NSComparisonPredicate *)predicateWithLeftExpression:(NSExpression *)lhs rightExpression:(NSExpression *)rhs modifier:(NSComparisonPredicateModifier)modifier type:(NSPredicateOperatorType)type options:(NSComparisonPredicateOptions)options;
/// Returns a new predicate formed by combining the left and right expressions using a given selector.
/// - Parameters:
///   - lhs: The left hand side expression.
///   - rhs: The right hand side expression.
///   - selector: The selector to use for comparison. The method defined by the selector must take a single argument and return a `BOOL` value.
/// - Returns: A new predicate formed by combining the left and right expressions using `selector`.
+ (NSComparisonPredicate *)predicateWithLeftExpression:(NSExpression *)lhs rightExpression:(NSExpression *)rhs customSelector:(SEL)selector;

/// Creates a predicate to a specified type that you form by combining specified left and right expressions using a specified modifier and options.
/// - Parameters:
///   - lhs: The left hand expression.
///   - rhs: The right hand expression.
///   - modifier: The modifier to apply.
///   - type: The predicate operator type.
///   - options: The options to apply. For no options, pass `0`.
/// - Returns: The receiver, initialized to a predicate of type `type` formed by combining the left and right expressions using the `modifier` and `options`.
- (instancetype)initWithLeftExpression:(NSExpression *)lhs rightExpression:(NSExpression *)rhs modifier:(NSComparisonPredicateModifier)modifier type:(NSPredicateOperatorType)type options:(NSComparisonPredicateOptions)options NS_DESIGNATED_INITIALIZER;
/// Creates a predicate that you form by combining specified left and right expressions using a specified selector.
/// - Parameters:
///   - lhs: The left hand expression.
///   - rhs: The right hand expression.
///   - selector: The selector to use. The method defined by the selector must take a single argument and return a `BOOL` value.
/// - Returns: The receiver, initialized by combining the left and right expressions using `selector`.
- (instancetype)initWithLeftExpression:(NSExpression *)lhs rightExpression:(NSExpression *)rhs customSelector:(SEL)selector NS_DESIGNATED_INITIALIZER;
/// Creates a predicate by decoding from the coder you specify.
/// - Parameter coder: The coder to read data from.
- (nullable instancetype)initWithCoder:(NSCoder *)coder NS_DESIGNATED_INITIALIZER;

/// The predicate type for the receiver.
@property (readonly) NSPredicateOperatorType predicateOperatorType;
/// The comparison predicate modifier for the receiver. The default value is `NSDirectPredicateModifier`.
@property (readonly) NSComparisonPredicateModifier comparisonPredicateModifier;
/// The left expression for the receiver.
@property (readonly, retain) NSExpression *leftExpression;
/// The right expression for the receiver.
@property (readonly, retain) NSExpression *rightExpression;
/// The selector for the receiver, or `NULL` if there is none.
@property (nullable, readonly) SEL customSelector;
/// The options to use for the receiver.
@property (readonly) NSComparisonPredicateOptions options;

@end

NS_HEADER_AUDIT_END(nullability, sendability)
