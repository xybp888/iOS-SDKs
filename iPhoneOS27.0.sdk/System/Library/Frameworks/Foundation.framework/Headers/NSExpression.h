/*	NSExpression.h
	Copyright (c) 2004-2019, Apple Inc. All rights reserved.
*/

#import <Foundation/NSObject.h>

@class NSString;
@class NSArray<ObjectType>;
@class NSMutableDictionary;
@class NSPredicate;

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

// Expressions are the core of the predicate implementation. When expressionValueWithObject: is called, the expression is evaluated, and a value returned which can then be handled by an operator. Expressions can be anything from constants to method invocations. Scalars should be wrapped in appropriate NSValue classes.

/// Defines the possible types of an expression.
typedef NS_ENUM(NSUInteger, NSExpressionType) {
    /// An expression that always returns the same value.
    NSConstantValueExpressionType = 0, // Expression that always returns the same value
    /// An expression that always returns the parameter object itself.
    NSEvaluatedObjectExpressionType, // Expression that always returns the parameter object itself
    /// An expression that always returns whatever is stored at 'variable' in the bindings dictionary.
    NSVariableExpressionType, // Expression that always returns whatever is stored at 'variable' in the bindings dictionary
    /// An expression that returns something that can be used as a key path.
    NSKeyPathExpressionType, // Expression that returns something that can be used as a key path
    /// An expression that returns the result of evaluating a symbol.
    NSFunctionExpressionType, // Expression that returns the result of evaluating a symbol
    /// An expression that returns the result of doing a unionSet: on two expressions that evaluate to flat collections (arrays or sets).
    NSUnionSetExpressionType API_AVAILABLE(macos(10.5), ios(3.0), watchos(2.0), tvos(9.0)), // Expression that returns the result of doing a unionSet: on two expressions that evaluate to flat collections (arrays or sets)
    /// An expression that returns the result of doing an intersectSet: on two expressions that evaluate to flat collections (arrays or sets).
    NSIntersectSetExpressionType API_AVAILABLE(macos(10.5), ios(3.0), watchos(2.0), tvos(9.0)), // Expression that returns the result of doing an intersectSet: on two expressions that evaluate to flat collections (arrays or sets)
    /// An expression that returns the result of doing a minusSet: on two expressions that evaluate to flat collections (arrays or sets).
    NSMinusSetExpressionType API_AVAILABLE(macos(10.5), ios(3.0), watchos(2.0), tvos(9.0)), // Expression that returns the result of doing a minusSet: on two expressions that evaluate to flat collections (arrays or sets)
    /// A subquery expression.
    NSSubqueryExpressionType API_AVAILABLE(macos(10.5), ios(3.0), watchos(2.0), tvos(9.0)) = 13,
    /// An aggregate expression.
    NSAggregateExpressionType API_AVAILABLE(macos(10.5), ios(3.0), watchos(2.0), tvos(9.0)) = 14,
    /// An expression that represents any key for a Spotlight query.
    NSAnyKeyExpressionType API_AVAILABLE(macos(10.9), ios(7.0), watchos(2.0), tvos(9.0)) = 15,
    /// A block expression.
    NSBlockExpressionType = 19,
    /// A conditional expression that evaluates a predicate to determine which expression to return.
    NSConditionalExpressionType API_AVAILABLE(macos(10.11), ios(9.0), watchos(2.0), tvos(9.0)) = 20

};

/// An expression for use in a comparison predicate.
///
/// Comparison operations in an ``NSPredicate`` derive from two expressions as instances of the ``NSExpression`` class. You create expressions for constant values, key paths, and so on.
///
/// Generally, anywhere in the ``NSExpression`` class hierarchy where there's a composite API and subtypes that may only reasonably respond to a subset of that API, invoking a method that doesn't make sense for that subtype throws an exception.
///
/// ### Aggregate Expressions
///
/// ``ExpressionType/aggregate`` allows you to create predicates containing expressions that evaluate to collections that contain further expressions. The collection may be an ``NSArray``, ``NSSet``, or ``NSDictionary`` object.
///
/// Core Data doesn't support aggregate expressions.
///
/// ### Subquery Expressions
///
/// The ``ExpressionType/subquery`` creates a subexpression that returns a subset of a collection of objects. This allows you to create sophisticated queries across relationships, such as a search for multiple correlated values on the destination object of a relationship.
///
/// ### Set Expressions
///
/// The set expressions (``ExpressionType/unionSet``, ``ExpressionType/intersectSet``, and ``ExpressionType/minusSet``) combine results in a manner similar to the ``NSSet`` methods.
///
/// Both sides of these expressions must evaluate to a collection; the left side must evaluate to an `NSSet` object, and the right side can be any other collection type.
///
/// ```objc
/// (expression UNION expression)
/// (expression INTERSECT expression)
/// (expression MINUS expression)
/// ```
///
///
/// Core Data doesn't support set expressions.
///
/// ### Function Expressions
///
/// In macOS 10.4, ``NSExpression`` only supports a predefined set of functions: `sum`, `count`, `min`, `max`, and `average`. You access these predefined functions in the predicate syntax using custom keywords (for example, `MAX(1, 5, 10)`).
///
/// In macOS 10.5 and later, function expressions also support arbitrary method invocations. To implement this extended functionality, use the syntax `FUNCTION(receiver, selectorName, arguments, ...),` as in the following example:
///
/// ```objc
/// FUNCTION(@"/Developer/Tools/otest", @"lastPathComponent") => @"otest"
/// ```
///
///
/// All methods must take one or more `id` arguments and return an `id` value, although you can use the `CAST` expression to convert datatypes with lossy string representations (for example, `CAST(####, "NSDate")`). macOS 10.5 extends the `CAST` expression to provide support for casting to classes for use in creating receivers for function expressions.
///
/// Although Core Data supports evaluation of the predefined functions, it doesn't support the evaluation of custom predicate functions in the persistent stores (during a fetch).
API_AVAILABLE(macos(10.4), ios(3.0), watchos(2.0), tvos(9.0))
@interface NSExpression : NSObject <NSSecureCoding, NSCopying> {
    @package
    struct _expressionFlags {
        unsigned int _evaluationBlocked:1;
        unsigned int _usesKVC:1;
        unsigned int _validatedExpression:1;
        unsigned int _validatedKeys:1;
        unsigned int _reservedExpressionFlags:28;
    } _expressionFlags;
#ifdef __LP64__
    uint32_t reserved;
#endif
    NSExpressionType _expressionType;
}

/// Creates the expression with the specified expression arguments.
+ (NSExpression *)expressionWithFormat:(NSString *)expressionFormat argumentArray:(NSArray *)arguments API_AVAILABLE(macos(10.6), ios(4.0), watchos(2.0), tvos(9.0));
/// Creates the expression with the specified expression arguments.
+ (NSExpression *)expressionWithFormat:(NSString *)expressionFormat, ...  API_AVAILABLE(macos(10.6), ios(4.0), watchos(2.0), tvos(9.0));
/// Creates the expression with the specified expression arguments.
+ (NSExpression *)expressionWithFormat:(NSString *)expressionFormat arguments:(va_list)argList API_AVAILABLE(macos(10.6), ios(4.0), watchos(2.0), tvos(9.0));

/// Creates an expression that returns a constant value.
+ (NSExpression *)expressionForConstantValue:(nullable id)obj;    // Expression that returns a constant value
/// Creates an expression that represents the object you're evaluating.
+ (NSExpression *)expressionForEvaluatedObject;    // Expression that returns the object being evaluated
/// Creates an expression that pulls a value from the variable bindings dictionary.
+ (NSExpression *)expressionForVariable:(NSString *)string;    // Expression that pulls a value from the variable bindings dictionary
/// Creates an expression that invokes the value function with a specified key path.
///
/// - Parameters:
///   - keyPath: The key path that the new expression should evaluate.
/// - Returns: A new expression that invokes `value(forKeyPath:)` with `keyPath`.
+ (NSExpression *)expressionForKeyPath:(NSString *)keyPath;    // Expression that invokes valueForKeyPath with keyPath
/// Creates an expression that invokes one of the predefined functions.
+ (NSExpression *)expressionForFunction:(NSString *)name arguments:(NSArray *)parameters;    // Expression that invokes one of the predefined functions. Will throw immediately if the selector is bad; will throw at runtime if the parameters are incorrect.
    // Predefined functions are:
    // name              parameter array contents				returns
	//-------------------------------------------------------------------------------------------------------------------------------------
    // sum:              NSExpression instances representing numbers		NSNumber 
    // count:            NSExpression instances representing numbers		NSNumber 
    // min:              NSExpression instances representing numbers		NSNumber  
    // max:              NSExpression instances representing numbers		NSNumber
    // average:          NSExpression instances representing numbers		NSNumber
    // median:           NSExpression instances representing numbers		NSNumber
    // mode:             NSExpression instances representing numbers		NSArray	    (returned array will contain all occurrences of the mode)
    // stddev:           NSExpression instances representing numbers		NSNumber
    // add:to:           NSExpression instances representing numbers		NSNumber
    // from:subtract:    two NSExpression instances representing numbers	NSNumber
    // multiply:by:      two NSExpression instances representing numbers	NSNumber
    // divide:by:        two NSExpression instances representing numbers	NSNumber
    // modulus:by:       two NSExpression instances representing numbers	NSNumber
    // sqrt:             one NSExpression instance representing numbers		NSNumber
    // log:              one NSExpression instance representing a number	NSNumber
    // ln:               one NSExpression instance representing a number	NSNumber
    // raise:toPower:    one NSExpression instance representing a number	NSNumber
    // exp:              one NSExpression instance representing a number	NSNumber
    // floor:            one NSExpression instance representing a number	NSNumber
    // ceiling:          one NSExpression instance representing a number	NSNumber
    // abs:              one NSExpression instance representing a number	NSNumber
    // trunc:            one NSExpression instance representing a number	NSNumber
    // uppercase:	 one NSExpression instance representing a string	NSString
    // lowercase:        one NSExpression instance representing a string    NSString
    // canonical:        one NSExpression instance representing a string    NSString
    // random            none							NSNumber (integer)
    // randomn:          one NSExpression instance representing a number	NSNumber (integer) such that 0 <= rand < param
    // now               none							[NSDate now]
    // bitwiseAnd:with:	 two NSExpression instances representing numbers	NSNumber    (numbers will be treated as NSInteger)
    // bitwiseOr:with:	 two NSExpression instances representing numbers	NSNumber    (numbers will be treated as NSInteger)
    // bitwiseXor:with:	 two NSExpression instances representing numbers	NSNumber    (numbers will be treated as NSInteger)
    // leftshift:by:	 two NSExpression instances representing numbers	NSNumber    (numbers will be treated as NSInteger)
    // rightshift:by:	 two NSExpression instances representing numbers	NSNumber    (numbers will be treated as NSInteger)
    // onesComplement:	 one NSExpression instance representing a numbers	NSNumber    (numbers will be treated as NSInteger)
    // noindex:		 an NSExpression					parameter   (used by CoreData to indicate that an index should be dropped)
    // distanceToLocation:fromLocation:
    //                   two NSExpression instances representing CLLocations    NSNumber
    // length:           an NSExpression instance representing a string         NSNumber

/// Creates an expression that returns a collection containing the results of other expressions.
+ (NSExpression *)expressionForAggregate:(NSArray<NSExpression *> *)subexpressions API_AVAILABLE(macos(10.5), ios(3.0), watchos(2.0), tvos(9.0)); // Expression that returns a collection containing the results of other expressions
/// Returns an expression that will return the union of the collections expressed by left and right.
+ (NSExpression *)expressionForUnionSet:(NSExpression *)left with:(NSExpression *)right API_AVAILABLE(macos(10.5), ios(3.0), watchos(2.0), tvos(9.0)); // return an expression that will return the union of the collections expressed by left and right
/// Returns an expression that will return the intersection of the collections expressed by left and right.
+ (NSExpression *)expressionForIntersectSet:(NSExpression *)left with:(NSExpression *)right API_AVAILABLE(macos(10.5), ios(3.0), watchos(2.0), tvos(9.0)); // return an expression that will return the intersection of the collections expressed by left and right
/// Returns an expression that will return the disjunction of the collections expressed by left and right.
+ (NSExpression *)expressionForMinusSet:(NSExpression *)left with:(NSExpression *)right API_AVAILABLE(macos(10.5), ios(3.0), watchos(2.0), tvos(9.0)); // return an expression that will return the disjunction of the collections expressed by left and right
/// Creates an expression that filters a collection using a subquery.
+ (NSExpression *)expressionForSubquery:(NSExpression *)expression usingIteratorVariable:(NSString *)variable predicate:(NSPredicate *)predicate API_AVAILABLE(macos(10.5), ios(3.0), watchos(2.0), tvos(9.0));
/// Creates an expression that invokes a selector on a target with parameters.
+ (NSExpression *)expressionForFunction:(NSExpression *)target selectorName:(NSString *)name arguments:(nullable NSArray *)parameters API_AVAILABLE(macos(10.5), ios(3.0), watchos(2.0), tvos(9.0));    // Expression that invokes the selector on target with parameters. Will throw at runtime if target does not implement selector or if parameters are wrong.
/// Creates an expression that represents any key for a Spotlight query.
+ (NSExpression *)expressionForAnyKey API_AVAILABLE(macos(10.9), ios(7.0), watchos(2.0), tvos(9.0));
/// Creates an expression that invokes a block with the parameters.
+ (NSExpression *)expressionForBlock:(id (^)(id _Nullable evaluatedObject, NSArray<NSExpression *> *expressions, NSMutableDictionary * _Nullable context))block arguments:(nullable NSArray<NSExpression *> *)arguments API_AVAILABLE(macos(10.6), ios(4.0), watchos(2.0), tvos(9.0)); // Expression that invokes the block with the parameters; note that block expressions are not encodable or representable as parseable strings.
/// Creates an expression that will return the result of trueExpression or falseExpression depending on the value of predicate.
+ (NSExpression *)expressionForConditional:(NSPredicate *)predicate trueExpression:(NSExpression *)trueExpression falseExpression:(NSExpression *)falseExpression  API_AVAILABLE(macos(10.11), ios(9.0), watchos(2.0), tvos(9.0)); // Expression that will return the result of trueExpression or falseExpression depending on the value of predicate

/// Creates the expression with the specified expression type.
- (instancetype)initWithExpressionType:(NSExpressionType)type NS_DESIGNATED_INITIALIZER;
/// Creates an expression by decoding from the coder you specify.
///
/// - Parameters:
///   - coder: The coder to read data from.
- (nullable instancetype)initWithCoder:(NSCoder *)coder NS_DESIGNATED_INITIALIZER;

/// The expression type for the expression.
///
/// Accessing this property raises an exception if it is not applicable to the expression.
@property (readonly) NSExpressionType expressionType;
/// The constant value of the expression.
@property (nullable, readonly, retain) id constantValue;
/// The key path for the expression.
@property (readonly, copy) NSString *keyPath;
/// The function for the expression.
@property (readonly, copy) NSString *function;
/// The variable for the expression.
@property (readonly, copy) NSString *variable;
/// The operand for the expression.
///
/// The operand is the object on which the expression's selector or block will be invoked. The object is the result of evaluating a key path or one of the defined functions.
@property (readonly, copy) NSExpression *operand;    // the object on which the selector will be invoked (the result of evaluating a key path or one of the defined functions)
/// The arguments for the expression.
///
/// The array of expressions which will be passed as parameters during invocation of the selector on the operand of a function expression.
@property (nullable, readonly, copy) NSArray<NSExpression *> *arguments;    // array of expressions which will be passed as parameters during invocation of the selector on the operand of a function expression

/// The collection of expressions in an aggregate expression, or the collection element of a subquery expression.
@property (readonly, retain) id collection API_AVAILABLE(macos(10.5), ios(3.0), watchos(2.0), tvos(9.0));
/// The predicate of a subquery expression.
@property (readonly, copy) NSPredicate *predicate API_AVAILABLE(macos(10.5), ios(3.0), watchos(2.0), tvos(9.0));
/// The left expression of an aggregate expression.
@property (readonly, copy) NSExpression *leftExpression API_AVAILABLE(macos(10.5), ios(3.0), watchos(2.0), tvos(9.0)); // expression which represents the left side of a set expression
/// The right expression of an aggregate expression.
@property (readonly, copy) NSExpression *rightExpression API_AVAILABLE(macos(10.5), ios(3.0), watchos(2.0), tvos(9.0)); // expression which represents the right side of a set expression


/// An expression to evaluate if a conditional expression's predicate evaluates to true.
@property (readonly, copy) NSExpression *trueExpression API_AVAILABLE(macos(10.11), ios(9.0), watchos(2.0), tvos(9.0)); // expression which will be evaluated if a conditional expression's predicate evaluates to true
/// An expression to evaluate if a conditional expression's predicate evaluates to false.
@property (readonly, copy) NSExpression *falseExpression API_AVAILABLE(macos(10.11), ios(9.0), watchos(2.0), tvos(9.0)); // expression which will be evaluated if a conditional expression's predicate evaluates to false

/// The block that executes to evaluate the expression.
@property (readonly, copy) id (^expressionBlock)(id _Nullable, NSArray<NSExpression *> *, NSMutableDictionary * _Nullable) API_AVAILABLE(macos(10.6), ios(4.0), watchos(2.0), tvos(9.0));

/// Evaluates an expression using a specified object and context.
- (nullable id)expressionValueWithObject:(nullable id)object context:(nullable NSMutableDictionary *)context;

/// Forces a securely decoded expression to allow evaluation.
///
/// When securely decoding an `NSExpression` object encoded using `NSSecureCoding`, evaluation is disabled because it is potentially unsafe to evaluate expressions you get out of an archive.
///
/// Before you enable evaluation, you should validate key paths, selectors, etc to ensure no erroneous or malicious code will be executed. Once you've preflighted the expression, you can enable the expression for evaluation by calling `allowEvaluation`.
- (void)allowEvaluation API_AVAILABLE(macos(10.9), ios(7.0), watchos(2.0), tvos(9.0)); // Force an expression which was securely decoded to allow evaluation

@end

NS_HEADER_AUDIT_END(nullability, sendability)
