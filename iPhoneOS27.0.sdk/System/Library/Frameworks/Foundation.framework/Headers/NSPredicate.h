/*	NSPredicate.h
	Copyright (c) 2004-2019, Apple Inc. All rights reserved.
*/

#import <Foundation/NSObject.h>
#import <Foundation/NSArray.h>
#import <Foundation/NSSet.h>
#import <Foundation/NSOrderedSet.h>

@class NSDictionary <KeyType, ObjectType>, NSString;
@protocol NSPredicateValidating;

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

// Predicates wrap some combination of expressions and operators and when evaluated return a BOOL.

/// A definition of logical conditions for constraining a search for a fetch or for in-memory filtering.
///
/// Predicates represent logical conditions, which you can use to filter collections of objects. Although it's common to create predicates directly from instances of ``NSComparisonPredicate``, ``NSCompoundPredicate``, and ``NSExpression``, you often create predicates from a format string that the class methods parse on ``NSPredicate``. Examples of predicate format strings include:
///
/// - Simple comparisons, such as `grade == "7"` or `firstName like "Juan"`
/// - Case- and diacritic-insensitive lookups, such as `name contains[cd] "stein"`
/// - Logical operations, such as `(firstName like "Mei") OR (lastName like "Chen")`
/// - Temporal range constraints, such as `date between {$YESTERDAY, $TOMORROW}`
/// - Relational conditions, such as `group.name like "work*"`
/// - Aggregate operations, such as `@sum.items.price < 1000`
///
/// For a complete syntax reference, refer to the [Predicate Programming Guide](https://developer.apple.com/library/archive/documentation/Cocoa/Conceptual/Predicates/AdditionalChapters/Introduction.html#//apple_ref/doc/uid/TP40001789).
///
/// You can also create predicates that include variables using the ``evaluate(with:substitutionVariables:)`` method so that you can predefine the predicate before substituting concrete values at runtime.
API_AVAILABLE(macos(10.4), ios(3.0), watchos(2.0), tvos(9.0))
@interface NSPredicate : NSObject <NSSecureCoding, NSCopying> {
    struct _predicateFlags {
        unsigned int _evaluationBlocked:1;
        unsigned int _reservedPredicateFlags:31;
    } _predicateFlags;
#ifdef __LP64__
    uint32_t reserved;
#endif
}

/// Parse predicateFormat and return an appropriate predicate
+ (NSPredicate *)predicateWithFormat:(NSString *)predicateFormat argumentArray:(nullable NSArray *)arguments;
/// Creates and returns a new predicate formed by creating a new string with a specified format and parsing the result.
+ (NSPredicate *)predicateWithFormat:(NSString *)predicateFormat, ...;
/// Creates a predicate by substituting the values in an argument list into a format string and parsing the result.
+ (NSPredicate *)predicateWithFormat:(NSString *)predicateFormat arguments:(va_list)argList;

/// Creates a predicate with a metadata query string.
+ (nullable NSPredicate *)predicateFromMetadataQueryString:(NSString *)queryString API_AVAILABLE(macos(10.9)) API_UNAVAILABLE(ios, watchos, tvos);

/// Creates and returns a predicate that always evaluates to a specified Boolean value.
+ (NSPredicate *)predicateWithValue:(BOOL)value;    // return predicates that always evaluate to true/false

/// Creates a predicate that evaluates using a specified block object and bindings dictionary.
///
/// In macOS 10.6 and later, Core Data supports block-based predicates in the in-memory and atomic stores, but not in the SQLite-based store.
+ (NSPredicate*)predicateWithBlock:(BOOL (^)(id _Nullable evaluatedObject, NSDictionary<NSString *, id> * _Nullable bindings))block API_AVAILABLE(macos(10.6), ios(4.0), watchos(2.0), tvos(9.0));

/// The predicate's format string.
///
/// The return value of this property is not guaranteed to be the same as the string used to create the predicate using `predicateWithFormat:` or similar methods.
@property (readonly, copy) NSString *predicateFormat;    // returns the format string of the predicate

/// Returns a copy of the predicate and substitutes the predicates variables with specified values from a specified substitution variables dictionary.
///
/// The predicate itself is not modified by this method, so you can reuse it for any number of substitutions.
- (instancetype)predicateWithSubstitutionVariables:(NSDictionary<NSString *, id> *)variables;    // substitute constant values for variables

/// Returns a Boolean value that indicates whether the specified object matches the conditions that the predicate specifies.
- (BOOL)evaluateWithObject:(nullable id)object;    // evaluate a predicate against a single object

/// Returns a Boolean value that indicates whether the specified object matches the conditions that the predicate specifies after substituting in the values from a specified variables dictionary.
///
/// This method returns the same result as the two step process of first invoking `predicateWithSubstitutionVariables:` on the predicate and then invoking `evaluateWithObject:` on the returned value. This method is optimized for situations which require repeatedly evaluating a predicate with substitution variables with different variable substitutions.
- (BOOL)evaluateWithObject:(nullable id)object substitutionVariables:(nullable NSDictionary<NSString *, id> *)bindings API_AVAILABLE(macos(10.5), ios(3.0), watchos(2.0), tvos(9.0)); // single pass evaluation substituting variables from the bindings dictionary for any variable expressions encountered

/// Forces a securely decoded predicate to allow evaluation.
///
/// When securely decoding `NSPredicate` objects encoded using `NSSecureCoding`, evaluation is disabled because it is potentially unsafe to evaluate predicates you get out of an archive.
///
/// Before you enable evaluation, you should validate key paths, selectors, and other details to ensure no erroneous or malicious code will be executed. Once you've verified the predicate, you can enable the receiver for evaluation by calling `allowEvaluation`.

- (void)allowEvaluation API_AVAILABLE(macos(10.9), ios(7.0), watchos(2.0), tvos(9.0)); // Force a predicate which was securely decoded to allow evaluation
- (BOOL)allowEvaluationWithValidator:(id<NSPredicateValidating>)validator
                               error:(NSError * _Nullable *)error NS_SWIFT_NAME(allowEvaluation(validator:)) API_AVAILABLE(macosx(26.4),ios(26.4),tvos(26.4),watchos(26.4),visionos(26.4));

@end

@interface NSArray<ObjectType> (NSPredicateSupport)
/// Evaluates a given predicate against each object in the receiving array and returns a new array containing the objects for which the predicate returns true.
- (NSArray<ObjectType> *)filteredArrayUsingPredicate:(NSPredicate *)predicate;
@end

@interface NSMutableArray<ObjectType> (NSPredicateSupport)
/// Evaluates a given predicate against the array's content and leaves only objects that match.
- (void)filterUsingPredicate:(NSPredicate *)predicate;
@end


@interface NSSet<ObjectType> (NSPredicateSupport)
/// Evaluates a given predicate against each object in the receiving set and returns a new set containing the objects for which the predicate returns true.
- (NSSet<ObjectType> *)filteredSetUsingPredicate:(NSPredicate *)predicate API_AVAILABLE(macos(10.5), ios(3.0), watchos(2.0), tvos(9.0));
@end

@interface NSMutableSet<ObjectType> (NSPredicateSupport)
/// Evaluates a given predicate against the set's content and removes objects that don't match.
- (void)filterUsingPredicate:(NSPredicate *)predicate API_AVAILABLE(macos(10.5), ios(3.0), watchos(2.0), tvos(9.0));
@end

@interface NSOrderedSet<ObjectType> (NSPredicateSupport)

/// Evaluates a given predicate against each object in the receiving ordered set and returns a new ordered set containing the objects for which the predicate returns true.
- (NSOrderedSet<ObjectType> *)filteredOrderedSetUsingPredicate:(NSPredicate *)p API_AVAILABLE(macos(10.7), ios(5.0), watchos(2.0), tvos(9.0));

@end

@interface NSMutableOrderedSet<ObjectType> (NSPredicateSupport)

/// Evaluates a given predicate against the ordered set's content and removes objects that don't match.
- (void)filterUsingPredicate:(NSPredicate *)p API_AVAILABLE(macos(10.7), ios(5.0), watchos(2.0), tvos(9.0));

@end

NS_HEADER_AUDIT_END(nullability, sendability)
