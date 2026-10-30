//
//  CKQuery.h
//  CloudKit
//
//  Copyright (c) 2014 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

#import <CloudKit/CKRecord.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

/// A query that describes the criteria to apply when searching for records in a database.
///
/// You create a query as the first step in the search process. The query stores the search parameters, including the type of records to search, the match criteria (predicate) to apply, and the sort parameters to apply to the results. Then you use the query to initialize an instance of ``CKQueryOperation``, which you execute to generate the results.
///
/// Always designate a record type and predicate when you create a query object. The record type narrows the scope of the search to one type of record, and the predicate defines the conditions for matching records of that type. Predicates usually compare one or more fields of a record to constant values, but you can create predicates that return all records of a specific type or perform more nuanced searches.
///
/// Because you can't change the record type and predicate after initialization, you can use the same query to initialize multiple instances of ``CKQueryOperation``, each of which targets a different database or record zone.
///
/// ### Building Your Predicates
///
/// An <doc://com.apple.documentation/documentation/foundation/nspredicate> object defines the logical conditions for determining whether a record is a match for a query. Queries support only a subset of the predicate behaviors that the `NSPredicate` class offers.
///
/// #### Predicate Rules for Query Objects
///
/// The predicates you create for your query objects must follow these rules:
///
/// - Predicates derive from a format string. You can't use value or block-based predicates.
/// - Predicates use only the operators in <doc:Supported-Predicate-Operators>.
/// - Predicates operate only on fields that contain the following types of data:
///
///   - <doc://com.apple.documentation/documentation/foundation/nsstring>
///   - <doc://com.apple.documentation/documentation/foundation/nsdata>
///   - <doc://com.apple.documentation/documentation/foundation/nsdate>
///   - <doc://com.apple.documentation/documentation/foundation/nsnumber>
///   - <doc://com.apple.documentation/documentation/foundation/nsarray>
///   - ``CKRecord/Reference``
///   - <doc://com.apple.documentation/documentation/corelocation/cllocation>
///
/// - Key names in predicates correspond to fields in the currently evaluated record. Key names can include the names of the record's metadata properties, such as `creationDate`, or any data fields you add to the record. You can't use key paths to specify fields in related records.
///
/// - Predicates support the following variable substitution strings:
///   - Use `%@` for value objects, such as strings, numbers, and dates.
///   - Use `%K` for the name of a field. This substitution variable indicates that the system uses the substitution string to look up a field name.
///
/// - With one exception, the `CONTAINS` operator is only for testing list membership. The exception is when you use it to perform full-text searches in conjunction with the `self` key path. The `self` key path causes the server to look in searchable string-based fields for the specified token string. For example, a predicate string of `@"self contains 'blue'"` searches for the word _blue_ in all fields that you mark for inclusion in full-text searches. You can't use the `self` key path to search in fields with a type that isn't a string.
/// - You can combine the `ANY` and `SOME` aggregate operators with the `IN` and `CONTAINS` operators to perform list membership tests.
/// - The `distanceToLocation:fromLocation:` operator function performs a radius-based location comparison and that comparison must determine whether the location value is inside the circular area you provide. You can't use it to search for locations outside the specified circular area. Location indexes have a resolution of no less than 10 km.
/// - CloudKit doesn't support the `ALL` aggregate operator.
/// - CloudKit doesn't support the `NOT` compound operator in the following cases:
///
///   - You can't use it to negate an `AND` compound predicate.
///   - You can't use it in tokenized queries, such as `self CONTAINS 'value'`.
///   - You can't use it with the `distanceToLocation:fromLocation:` function.
///   - You can't use it in `BETWEEN` queries.
///
/// #### Supported Predicate Operators
///
/// The following table lists the operators you can use in predicates for a query.
///
/// | Operation | Supported operators |
/// |---|---|
/// | Basic comparisons | `=`, `==` ![](spacer) `>=`, `=>` ![](spacer) `<=`, `=<` ![](spacer) `<` ![](spacer) `>` ![](spacer) `!=`, `<>` ![](spacer) `BETWEEN` |
/// | Boolean value predicates | `TRUEPREDICATE` ![](spacer) `FALSEPREDICATE` |
/// | Basic compound predicates | `AND`, `&&` ![](spacer) `NOT` |
/// | String comparisons | `BEGINSWITH` |
/// | Aggregate operations | `IN` ![](spacer) `CONTAINS` |
/// | Functions | `distanceToLocation:fromLocation:` ![](spacer) `now` ![](spacer) `tokenize:using:` |
///
/// Specifying an unsupported operator or data type in your query's predicate results in an error when you execute the query. For more information about creating predicate objects, see [Predicate Programming Guide](https://developer.apple.com/library/archive/documentation/Cocoa/Conceptual/Predicates/AdditionalChapters/Introduction.html#//apple_ref/doc/uid/TP40001789).
///
/// #### Sample Predicate Format Strings
///
/// To match records that link to a different record with an ID you know, create a predicate that matches a field that contains a reference as Listing 1 shows. In the example, the `employee` field of the record contains a ``CKRecord/Reference`` object that points to another record. When CloudKit executes the query, a match occurs when the ID in the locally-created ``CKRecord/Reference`` object is the same ID as in the specified field of the record.
///
/// Listing 1. Matching the ID of a record
///
/// ```objc
/// CKReference* recordToMatch = [[CKReference alloc] initWithRecordID:employeeID action:CKReferenceActionNone];
/// NSPredicate* predicate = [NSPredicate predicateWithFormat:@"employee == %@", recordToMatch];
/// ```
///
/// To match the contents of a field to a specific value, use a predicate similar to the ones in Listing 2. All of the listed predicates generate the same set of results, which in the example means that the `favoriteColors` field contains the value _red_. The value in the field must match the value you specify in the predicate exactly. String-based comparisons are case-insensitive, but otherwise, all comparisons must be an exact match of the specified value.
///
/// Listing 2. Matching a field to a specific value
///
/// ```objc
/// NSPredicate *predicate = nil;
/// predicate = [NSPredicate predicateWithFormat:@"ANY favoriteColors = 'red'"];
/// predicate = [NSPredicate predicateWithFormat:@"favoriteColors CONTAINS 'red'"];
/// predicate = [NSPredicate predicateWithFormat:@"'red' IN favoriteColors"];
/// predicate = [NSPredicate predicateWithFormat:@"%K CONTAINS %@", @"favoriteColors", @"red"];
/// ```
///
/// You can match more than one value at a time by using a predicate similar to the ones in Listing 3. In the example, the predicates report a match if the value in the `favoriteColor` field of a record matches either of the values `red` or `green`.
///
/// Listing 3. Matching a field to one or more values
///
/// ```objc
/// NSPredicate *predicate = nil;
/// predicate = [NSPredicate predicateWithFormat:@"ANY { 'red', 'green' } = favoriteColor"];
/// predicate = [NSPredicate predicateWithFormat:@"favoriteColor IN { 'red', 'green' }"];
/// ```
///
/// For fields that contain string values, you can match the beginning portion of the string using the `BEGINSWITH` operator as Listing 4 shows. You can't use other string comparison operators, such as `CONTAINS` or `ENDSWITH`. When using this operator, the field must contain a string value and must start with the string you specify. Matches are case-sensitive. In the examples, the predicate matches records where the `favoriteColors` field contains the strings _red_, _reddish_, or _red_` `_green_` `_duct_` `_tape_.
///
/// Listing 4. Matching a field that starts with a string value
///
/// ```objc
/// NSString* matchString = @"red";
/// NSPredicate *predicate = nil;
/// predicate = [NSPredicate predicateWithFormat:@"ANY favoriteColors BEGINSWITH 'red'"]
/// predicate = [NSPredicate predicateWithFormat:@"ANY favoriteColors BEGINSWITH %@", matchString]
/// ```
///
/// To perform a tokenized search of a record's fields, use the special operator `self`. A tokenized search searches any fields where you enable full-text search, which is all string-based fields by default. CloudKit treats each distinct word in the tokenized string as a separate token for the purpose of searching. Comparisons are case- and diacritic-insensitive. These token strings can be in a single field or in multiple fields.
///
/// Listing 5 shows an example that searches the fields of a record for the token strings `bob` or `smith`:
///
/// Listing 5. Matching a field that contains one or more tokens
///
/// ```objc
/// NSPredicate *predicate = nil;
/// predicate = [NSPredicate predicateWithFormat:@"self contains 'bob smith'"];
/// ```
///
/// To search for multiple tokens present in the fields, use the `AND` predicate operator, as Listing 6 shows.
///
/// Listing 6. Matching a field that contains multiple tokens
///
/// ```objc
/// NSPredicate *predicate = nil;
/// predicate = [NSPredicate predicateWithFormat:@"self contains 'bob' AND self contains 'smith'"];
/// ```
///
/// To test whether two locations are near each other, create a predicate using the `distanceToLocation:fromLocation:` function as Listing 7 shows. Predicates that use this function must have the structure in the listing. In your code, replace the `location` variable with a field name from one of your records. This data type for the field must be a <doc://com.apple.documentation/documentation/corelocation/cllocation> object. Similarly, replace the `fixedLoc` and `radius` values with appropriate values from your app. The `fixedLoc` value is the geographic coordinate that marks the center of a circle with the specified radius. In this example, the predicate returns a match if the location in the record is within 10 kilometers of the specified latitude and longitude.
///
/// Listing 7. Matching by distance from a location
///
/// ```objc
/// CLLocation* fixedLoc = [[CLLocation alloc] initWithLatitude:37.331913 longitude:-122.030210];
/// CGFloat radius = 10; // kilometers
/// NSPredicate *predicate =
///    [NSPredicate predicateWithFormat:@"distanceToLocation:fromLocation:(location, %@) < %f", fixedLoc, radius]];
/// ```
///
/// To retrieve all records of a specific type, use the `TRUEPREDICATE` expression as Listing 8 shows. A predicate with this operator always evaluates to `true` and, therefore, matches every record. When using such an operator, use a cursor to batch the results into smaller groups for processing.
///
/// - Note: The `distanceToLocation:fromLocation:` operator function performs a radius-based location comparison, and that comparison must determine whether the location value is inside the circular area you provide. You can't use it to search for locations outside the specified circular area. Location indexes have a resolution of no less than 10 km.
///
/// Listing 8. Retrieving all records of a specific type
///
/// ```objc
/// NSPredicate *predicate = nil;
/// predicate = [NSPredicate predicateWithFormat:@"TRUEPREDICATE"];
/// ```
///
/// ### Indexes and Full-Text Search
///
/// Indexes make it possible to search the contents of your records efficiently. During development, the server indexes all fields with data types it can use in the predicate of a query. This automatic indexing makes it easier to experiment with queries during development, but the indexes require space in a database, and require time to generate and maintain. So when migrating to a production environment, remove the indexes for any fields that you don't use in queries.
///
/// Full-text search is another feature that is on by default for all fields during development. When you move to the production environment, disable full-text search for fields with content you don't need to search. As with removing indexes, disabling full-text search improves the performance of your tokenized searches. To configure the indexing and full-text search options for fields in your schema, use CloudKit Dashboard.
///
/// In a full-text search, CloudKit ignores the following words if they appear in the token strings:
///
/// | a | by | not | then |
/// |---|---|---|---|
/// | an | for | of | there |
/// | and | if | on | these |
/// | are | in | or | they |
/// | as | into | such | this |
/// | at | is | that | to |
/// | be | it | the | was |
/// | but | no | their | will |
/// |  |  |  | with |
///
/// ### Executing a Search Using Your Query Object
///
/// To execute a query, do one of the following:
///
/// - Create an instance of ``CKQueryOperation`` using your query. Run the operation directly or add it to an operation queue to perform the query and deliver the results.
/// - Call the ``CKDatabase/perform(_:inZoneWith:completionHandler:)`` method of ``CKDatabase`` to execute the query. Process the results in your completion handler.
///
/// Queries always run asynchronously and deliver results to a completion handler that you provide.
API_AVAILABLE(macos(10.10), ios(8.0), watchos(3.0))
CK_SUBCLASSING_DEPRECATED // should not be subclassed, or Sendable may no longer apply
// NS_SWIFT_SENDABLE on macos(14.0), ios(17.0), tvos(17.0), watchos(10.0)
@interface CKQuery : NSObject <NSSecureCoding, NSCopying>

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

/// Creates a query from a serialized instance.
///
/// - Parameters:
///   - aDecoder: The coder to use when deserializing the query.
- (instancetype)initWithCoder:(NSCoder *)aDecoder NS_DESIGNATED_INITIALIZER;

/// Creates a query with the specified record type and predicate.
///
/// - Parameters:
///   - recordType: The type of record to search. Specify the name of one of your app's supported record types. The method throws an exception if this parameter is `nil` or contains an empty string.
///   - predicate: The search predicate to apply to the prospective records. Only records that match the predicate criteria appear in the search results. For guidelines on how to construct predicates for your queries, see <doc:CKQuery#Predicate-Rules-for-Query-Objects>. This parameter must not be `nil`.
///
/// - Returns: An initialized query object.
///
/// You can't change the record type and predicate of a query after you create it. If you want to search for a different set of records using a different set of search criteria, create a new query. You can add sort descriptors to the query and change them later as necessary.
///
/// You can't query for user records, and executing a query where the record type is ``CKRecordTypeUserRecord-49k30`` results in an error. You must fetch user records directly using their IDs.
- (instancetype)initWithRecordType:(CKRecordType)recordType predicate:(NSPredicate *)predicate NS_DESIGNATED_INITIALIZER;

/// The record type to search.
///
/// A query's results include only records of the specified type. The record type is an app-specific string that you use to distinguish among the records of your app. The records of a particular type all represent different instances of the same information. For example, an employee record type might store the employee's name, phone number, and a reference to the employee's manager.
@property (readonly, copy) CKRecordType recordType;

/// The predicate to use for matching records.
///
/// A predicate contains one or more expressions that evaluate to <doc://com.apple.documentation/documentation/swift/true> or <doc://com.apple.documentation/documentation/swift/false>. Expressions are often value-based comparisons, but predicates support other types of operators, including string comparisons and aggregate operations. For guidelines on how to construct predicates for your queries, see <doc:CKQuery#Predicate-Rules-for-Query-Objects>.
@property (readonly, copy) NSPredicate *predicate;

/// The sort descriptors for organizing the query's results.
///
/// You can add sort descriptors to a query and change them later as necessary. Each sort descriptor contains a field name of the intended record type and information about whether to sort values in that field in ascending or descending order. The default value of this property is `nil`, which means that records return in an indeterminate order.
///
/// The order of the items in the array defines the order that CloudKit applies the sort descriptors to the results. In other words, CloudKit applies the first sort descriptor in the array, then the second sort descriptor, if necessary, then the third, and so on.
@property (nullable, copy) NSArray<NSSortDescriptor *> *sortDescriptors;

@end

NS_HEADER_AUDIT_END(nullability, sendability)
